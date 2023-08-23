/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2022 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkSystemIncludes.h"
#include "vtkStringArray.h"
#include "vtkObjectFactory.h"
#include "vtkDICOMUtilities.h"
#include "vtkDICOMUIDGenerator.h"
#include "vtkDICOMFile.h"
#include "vtkDICOMConfig.h"

#include <string>

#include <stdio.h>
#include <string.h>

// needed for gettimeofday
#ifndef _WIN32
#include <time.h>
#include <sys/time.h>
#endif

// needed for random number generation and time
#ifdef _WIN32
#include <windows.h>
#include <wincrypt.h>
#endif

vtkStandardNewMacro(vtkDICOMUtilities);

//----------------------------------------------------------------------------
std::string vtkDICOMUtilities::GenerateUID(vtkDICOMTag tag)
{
  vtkDICOMUIDGenerator *uidgen = vtkDICOMUIDGenerator::GetDefault();
  return uidgen->GenerateUID(tag);
}

//----------------------------------------------------------------------------
void vtkDICOMUtilities::GenerateUIDs(vtkDICOMTag tag, vtkStringArray *uids)
{
  vtkDICOMUIDGenerator *uidgen = vtkDICOMUIDGenerator::GetDefault();
  uidgen->GenerateUIDs(tag, uids);
}

//----------------------------------------------------------------------------
int vtkDICOMUtilities::CompareUIDs(const char *u1, const char *u2)
{
  int r = 0;

  if (u1 == 0 || u2 == 0)
  {
    // if one or both are null
    r = (u2 == 0 ? r : -1);
    r = (u1 == 0 ? r : 1);
  }
  else
  {
    while (r == 0 && *u1 != 0 && *u2 != 0)
    {
      int i1 = 0;
      int i2 = 0;
      do { i1++; } while (u1[i1] >= '0' && u1[i1] <= '9');
      do { i2++; } while (u2[i2] >= '0' && u2[i2] <= '9');
      r = i1 - i2; // longer number wins
      if (r == 0)
      { // lexically compare numbers of the same length
        do { r = *u1++ - *u2++; } while (r == 0 && --i1 != 0);
      }
    }

    if (r == 0)
    {
      // uid with remaining parts wins
      r = (*u2 == 0 ? r : -1);
      r = (*u1 == 0 ? r : 1);
    }
    else
    {
      // convert r to sgn(r)
      r = (r >= 0 ? r : -1);
      r = (r <= 0 ? r : 1);
    }
  }

  return r;
}

//----------------------------------------------------------------------------
long long vtkDICOMUtilities::GetUniversalTime()
{
#ifdef _WIN32

  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  long long t1 = ((static_cast<long long>(ft.dwHighDateTime) << 32) +
                  static_cast<long long>(ft.dwLowDateTime));

  // convert file time to unix time
  return t1/10 - 11644473600000000ll;

#else

  struct timeval tv;
  gettimeofday(&tv, 0);
  return (tv.tv_sec*1000000ll + tv.tv_usec);

#endif
}

//----------------------------------------------------------------------------
long long vtkDICOMUtilities::GetUTC(long long *offset)
{
  long long t = vtkDICOMUtilities::GetUniversalTime();
  if (offset)
  {
    *offset = vtkDICOMUtilities::GetLocalOffset(t);
  }
  return t;
}

//----------------------------------------------------------------------------
long long vtkDICOMUtilities::GetLocalOffset(long long microsecs)
{
#ifdef _WIN32

  // convert unix time to file time
  long long t1 = microsecs*10 + 11644473600000000ll;
  ULARGE_INTEGER li;
  li.QuadPart = t1;
  FILETIME ft;
  ft.dwLowDateTime = li.LowPart;
  ft.dwHighDateTime = li.HighPart;

  // get the current timezone offset by subtracting UTC from local time
  TIME_ZONE_INFORMATION tzi;
  GetTimeZoneInformation(&tzi);
  SYSTEMTIME st;
  FileTimeToSystemTime(&ft, &st);
  SYSTEMTIME lst;
  SystemTimeToTzSpecificLocalTime(&tzi, &st, &lst);
  FILETIME lft;
  SystemTimeToFileTime(&lst, &lft);
  // round to the nearest second, since result has a bit of numerical error
  li.LowPart = lft.dwLowDateTime;
  li.HighPart = lft.dwHighDateTime;
  long long tzo = static_cast<long long>(li.QuadPart) - t1;
  if (tzo >= 0)
  {
    tzo = (tzo + 5000000)/10000000;
  }
  else
  {
    tzo = -((-tzo + 5000000)/10000000);
  }
  return tzo*1000000;

#else

  // tzset() is needed, at least on some systems, to set timezone info
  // from the TZ environment variable prior to the call to localtime_r()
  static bool once = false;
  if (!once)
  {
    once = true;
    tzset();
  }

  // use localtime to get the offset from utc
  struct tm tmv;
  time_t tod = static_cast<time_t>(microsecs/1000000);
  localtime_r(&tod, &tmv);
  return tmv.tm_gmtoff*1000000ll;

#endif
}

//----------------------------------------------------------------------------
std::string vtkDICOMUtilities::GenerateDateTime(const char *z)
{
  long long t = vtkDICOMUtilities::GetUniversalTime();
  return vtkDICOMUtilities::GenerateDateTime(t, z);
}

//----------------------------------------------------------------------------
// If "t" is VTK_LONG_LONG_MIN, this uses the current time instead of "t"
std::string vtkDICOMUtilities::GenerateDateTime(
  long long t, const char *z)
{
  char tzs[6] = { '+', '0', '0', '0', '0', '\0' };
  long long zs; // offset for local time in microseconds

  // get any timezone info that was supplied by the caller, if a timezone
  // was already generated for the data set we want to use it for generating
  // all time stamps for the data set
  if (z &&
      (z[0] == '+' || z[0] == '-') &&
      (z[1] >= '0' && z[1] <= '9') &&
      (z[2] >= '0' && z[2] <= '9') &&
      (z[3] >= '0' && z[3] <= '9') &&
      (z[4] >= '0' && z[4] <= '9'))
  {
    int zh = (z[1] - '0')*10 + (z[2] - '0');
    int zm = (z[3] - '0')*10 + (z[4] - '0');
    zs = (zh*3600 + zm*60) * (z[0] == '-' ? -1 : +1) * 1000000ll;
  }
  else
  {
    // use the local time zone
    zs = vtkDICOMUtilities::GetLocalOffset(t);
    long long zst = zs/1000000ll;
    tzs[0] = (zst < 0 ? '-' : '+');
    zst = (zst < 0 ? -zst : zst);
    snprintf(&tzs[1], sizeof(tzs) - 1, "%02d%02d",
             static_cast<int>((zst/3600)%24),
             static_cast<int>((zst%3600)/60));
    z = tzs;
  }

  // add the time zone offset (in microseconds)
  t += zs;

  // separate time into days and seconds
  int td = static_cast<int>(t/86400000000ll);
  long long tus = t - td*86400000000ll;
  if (tus < 0)
  {
    td -= 1;
    tus += 86400000000ll;
  }

  // use algorithm from Henry F. Fliegel and Thomas C. Van Flandern,
  // computes the current date according to Gregorian calendar
  int ell = td + 2509157;
  int n = (4 * ell) / 146097;
  ell = ell - (146097 * n + 3) / 4;
  int i = (4000 * (ell + 1)) / 1461001;
  ell = ell - (1461 * i) / 4 + 31;
  int j = (80 * ell) / 2447;
  int d = ell - (2447 * j) / 80;
  ell = j / 11;
  int m = j + 2 - (12 * ell);
  int y = 100 * (n - 49) + i + ell;
  if (y > 9999)
  {
    y = 9999;
  }

  // convert microseconds to hours/minutes/seconds.microseconds
  int S = static_cast<int>(tus/1000000ll);
  int us = static_cast<int>(tus - S*1000000ll);
  int H = S/3600;
  S -= H*3600;
  int M = S/60;
  S -= M*60;

  // create a DICOM datetime string
  char dt[84];
  snprintf(dt, sizeof(dt), "%04d%02d%02d%02d%02d%02d.%06d%s",
           y, m, d, H, M, S, us, z);

  return dt;
}

//----------------------------------------------------------------------------
long long vtkDICOMUtilities::ConvertDateTime(const char *datetime)
{
  // first normalize the datetime string into the following format
  const char *epoch = "19700101000000.000000+0000";
  char normalized[27];
  for (int i = 0; i < 27; i++)
  {
    normalized[i] = epoch[i];
  }
  char *tp = normalized;
  const char *cp = datetime;
  while (*tp != 0 && *cp >= '0' && *cp <= '9')
  {
    *tp++ = *cp++;
  }
  if (*tp == '.' && *cp == '.')
  {
    *tp++ = *cp++;
    while (*tp != 0 && *cp >= '0' && *cp <= '9')
    {
      *tp++ = *cp++;
    }
  }
  long long zs = -1;
  if (*cp == '-' || *cp == '+')
  {
    tp = normalized + 21;
    *tp++ = *cp++;
    while (*tp != 0 && *cp >= '0' && *cp <= '9')
    {
      *tp++ = *cp++;
    }
    tp = normalized + 21;
    zs = ((tp[1] - '0')*600 + (tp[2] - '0')*60 +
          (tp[3] - '0')*10 + (tp[4] - '0'))*60*1000000ll;
    if (tp[0] == '-')
    {
      zs = -zs;
    }
  }

  // convert normalized datetime to year, month, day etc.
  // first, convert all digits (and only digits) to binary values
  tp = normalized;
  normalized[14] += '0';
  normalized[21] += '0';
  for (int i = 0; i < 26; i++)
  {
    normalized[i] -= '0';
  }

  int y = tp[0]*1000 + tp[1]*100 + tp[2]*10 + tp[3];
  int m = tp[4]*10 + tp[5];
  int d = tp[6]*10 + tp[7];
  int H = tp[8]*10 + tp[9];
  int M = tp[10]*10 + tp[11];
  int S = tp[12]*10 + tp[13];
  int us = tp[15]*100 + tp[16]*10 + tp[17];
  us = us*1000 + tp[18]*100 + tp[19]*10 + tp[20];

  // use algorithm from Henry F. Fliegel and Thomas C. Van Flandern
  // to compute the day according to Gregorian calendar
  long long jd = (1461 * (y + 4800 + (m - 14) / 12)) / 4
     + (367 * (m - 2 - 12 * ((m - 14) / 12))) / 12
     - (3 * ((y + 4900 + (m - 14) / 12) / 100)) / 4
     + d - 32075;

  // compute time (the UNIX epoch began on Julian day 2440588)
  long long t = (jd - 2440588)*86400 + H*3600 + M*60 + S;

  t = t*1000000 + us;

  // if no time zone given, find local offset
  if (zs == -1)
  {
    zs = vtkDICOMUtilities::GetLocalOffset(t);
    // repeat in case we were pushed to opposite side of DST
    zs = vtkDICOMUtilities::GetLocalOffset(t - zs);
  }

  return t - zs;
}

//----------------------------------------------------------------------------
bool vtkDICOMUtilities::IsDICOMFile(const char *filename)
{
  unsigned char buffer[256];

  if (filename == 0)
  {
    return false;
  }

  vtkDICOMFile infile(filename, vtkDICOMFile::In);

  if (infile.GetError() != 0)
  {
    return false;
  }

  // valid file should be at least 256 chars long (probably longer)
  size_t size = infile.GetSize();
  if (size < sizeof(buffer))
  {
    return 0;
  }
  size = sizeof(buffer);

  size_t rsize = infile.Read(buffer, size);
  infile.Close();
  if (rsize != static_cast<size_t>(size))
  {
    return false;
  }

  const unsigned char *cp = buffer;

  // Look for the magic number and the first meta header tag.
  size_t skip = 128;
  for (int i = 0; i < 2; i++)
  {
    if (size > skip + 8)
    {
      cp = &buffer[skip];
      if (cp[0] == 'D' && cp[1] == 'I' && cp[2] == 'C' && cp[3] == 'M' &&
          cp[4] == 0x02 && cp[5] == 0x00 && cp[6] <= 0x10 && cp[7] == 0x00)
      {
        return true;
      }
    }
    // Some non-standard files have DICM at the beginning.
    skip = 0;
  }

  // File must be a reasonable size.
  if (size < 256)
  {
    return false;
  }

  cp = buffer;

  // If no magic number found, look for a valid meta header.
  if (cp[0] == 2 && cp[1] == 0 && cp[2] == 0 && cp[3] == 0 &&
      cp[4] == 'U' && cp[5] == 'L' && cp[6] == 4 && cp[7] == 0)
  {
    return true;
  }

  // Look for two valid implicitly-encoded data elements in Group 0x0008,
  // where the first element must be (0008,0016) or less (e.g. SOPClassUID)
  // with a size of 64 or less, and the second element must be (0008,0018)
  // or less (e.g. SOPInstanceUID) with a size of 64 or less.
  if (cp[0] == 0x08 && cp[1] == 0x00 && cp[2] <= 0x16 && cp[3] == 0x00 &&
      cp[4] <= 0x40 && cp[5] == 0x00 && cp[6] == 0x00 && cp[7] == 0x00)
  {
    unsigned char e = cp[2];
    cp += (cp[4] + 8);
    if (cp[0] == 0x08 && cp[1] == 0x00 && cp[2] <= 0x18 && cp[3] == 0x00 &&
        cp[4] <= 0x40 && cp[5] == 0x00 && cp[6] == 0x00 && cp[7] == 0x00 &&
        cp[2] > e)
    {
      return true;
    }
  }

  return false;
}

//----------------------------------------------------------------------------
char vtkDICOMUtilities::UIDPrefix[64] = "2.25.";

const char *vtkDICOMUtilities::GetUIDPrefix()
{
  return vtkDICOMUtilities::UIDPrefix;
}

//----------------------------------------------------------------------------
void vtkDICOMUtilities::SetUIDPrefix(const char *uid)
{
  strncpy(vtkDICOMUtilities::UIDPrefix, uid, 63);
  vtkDICOMUtilities::UIDPrefix[63] = '\0';
}

//----------------------------------------------------------------------------
char vtkDICOMUtilities::ImplementationClassUID[65] =
  "2.25.190146791043182537444806132342625375407";

const char *vtkDICOMUtilities::GetImplementationClassUID()
{
  return vtkDICOMUtilities::ImplementationClassUID;
}

//----------------------------------------------------------------------------
void vtkDICOMUtilities::SetImplementationClassUID(const char *uid)
{
  strncpy(vtkDICOMUtilities::ImplementationClassUID, uid, 64);
  vtkDICOMUtilities::ImplementationClassUID[64] = '\0';
}

//----------------------------------------------------------------------------
#define VTK_DICOM_VERSION_CREATOR2(name, x, y, z) \
  name "_" #x "_" #y "_" #z
#define VTK_DICOM_VERSION_CREATOR(name, x, y, z) \
  VTK_DICOM_VERSION_CREATOR2(name, x, y, z)

char vtkDICOMUtilities::ImplementationVersionName[17] =
  VTK_DICOM_VERSION_CREATOR("VTK_DICOM",
    DICOM_MAJOR_VERSION, DICOM_MINOR_VERSION, DICOM_PATCH_VERSION);

const char *vtkDICOMUtilities::GetImplementationVersionName()
{
  return vtkDICOMUtilities::ImplementationVersionName;
}

//----------------------------------------------------------------------------
void vtkDICOMUtilities::SetImplementationVersionName(const char *name)
{
  strncpy(vtkDICOMUtilities::ImplementationVersionName, name, 16);
  vtkDICOMUtilities::ImplementationVersionName[16] = '\0';
}

//----------------------------------------------------------------------------
bool vtkDICOMUtilities::PatternMatches(
    const char *pattern, size_t pl,
    const char *val, size_t vl)
{
  // This performs simple ASCII or UTF8 case-sensitive matching.
  // It uses the following simplified definition of UTF8:
  // 0b1xxxxxxx [0b10xxxxxx...]
  // In other words, a byte with its high bit set, followed by
  // zero or more bytes with the high bit set and the next bit clear,
  // are taken as one unicode codepoint.

  const char *cp = pattern;
  const char *ep = pattern + pl;
  const char *dp = val;
  const char *fp = val + vl;

  while (cp != ep && dp != fp)
  {
    if (*cp == '*')
    {
      cp++;
      // if '*' is the final character, it matches the remainder of val
      if (cp == ep)
      {
        dp = fp;
      }
      else
      {
        while (dp != fp)
        {
          if (*cp == '?' || *dp == *cp)
          {
            // check if the remainder of val matches remainder of pattern
            if (PatternMatches(cp, ep-cp, dp, fp-dp))
            {
              break;
            }
          }
          // else let the "*" eat one more codepoint of "val"
          if (static_cast<signed char>(*dp++) < 0)
          {
            while (dp != fp && (*dp & 0xC0) == 0x80)
            {
              dp++;
            }
          }
        }
      }
    }
    else if (*cp == '?')
    {
      // the '?' matches a whole codepoint, not just one byte
      cp++;
      if (static_cast<signed char>(*dp++) < 0)
      {
        while (dp != fp && (*dp & 0xC0) == 0x80)
        {
          dp++;
        }
      }
    }
    else if (*cp == *dp)
    {
      // make sure the entire codepoint matches
      cp++;
      if (static_cast<signed char>(*dp++) < 0)
      {
        while (cp != ep && dp != fp &&
               ((*cp & 0xC0) == 0x80 || (*dp & 0xC0) == 0x80))
        {
          if (*dp != *cp)
          {
            return false;
          }
          cp++;
          dp++;
        }
      }
    }
    else
    {
      return false;
    }
  }

  // skip over any remaining '*' wildcards
  while (cp != ep && *cp == '*')
  {
    cp++;
  }

  // make sure we've reached the end of both the pattern and the value
  return (cp == ep && dp == fp);
}

//----------------------------------------------------------------------------
bool vtkDICOMUtilities::PatternMatches(const char *pattern, const char *val)
{
  return vtkDICOMUtilities::PatternMatches(
    pattern, strlen(pattern), val, strlen(val));
}

//----------------------------------------------------------------------------
bool vtkDICOMUtilities::IsValidUTF8(const char *text, size_t l)
{
  const char *cp = text;
  const char *ep = cp + l;

  while (cp != ep)
  {
    if (cp[0] != '\0')
    {
      if ((cp[0] & 0x80) == 0)               // U+0001 to U+007F
      {
        cp++;
        continue;
      }

      // check for trailing bytes in utf-8 sequence
      if (cp+1 != ep && (cp[1] & 0xC0) == 0x80)
      {
        // combine the first two bytes for faster checking
        unsigned short x = (((unsigned char)(cp[0]) << 8) |
                             (unsigned char)(cp[1]));

        if (x >= 0xC280 && x < 0xE000)       // U+0080 to U+07FF
        {
          cp += 2;
          continue;
        }
        else if (cp+2 != ep && (cp[2] & 0xC0) == 0x80)
        {
          if ((x >= 0xE0A0 && x < 0xEDA0) || // U+0800 to U+D7FF
              (x >= 0xEE80 && x < 0xF000))   // U+E000 to U+FFFF
          {
            cp += 3;
            continue;
          }
          else if (cp+3 != ep && (cp[3] & 0xC0) == 0x80)
          {
            if (x >= 0xF090 && x < 0xF490)   // U+10000 to U+10FFFF
            {
              cp += 4;
              continue;
            }
          }
        }
      }
    }

    // utf-8 decoding error occurred at position "cp"
    return false;
  }

  return true;
}

//----------------------------------------------------------------------------
void vtkDICOMUtilities::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
