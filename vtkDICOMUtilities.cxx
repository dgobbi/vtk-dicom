/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include <vtkStringArray.h>
#include "vtkDICOMUtilities.h"

#include <string>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

namespace {

// divide a hex string by 10, return remainder
int vtkDivideHexStringBy10(char *value)
{
  char *cp = value;

  // convert hex string to binary
  unsigned int x = 0;
  while (*cp != '\0')
    {
    // skip any hyphens
    if (*cp == '-')
      {
      cp++;
      continue;
      }

    // convert hex digit to a nibble
    unsigned int d = *cp;
    if ((d -= '0') > 9)
      {
      if ((d -= ('A' - '0' - 10)) > 15)
        {
        d -= ('a' - 'A');
        }
      }

    // append the nibble
    x <<= 4;
    x += d;

    // divide by 10
    unsigned int y = (10 << 3);
    unsigned int z = 0;
    int i;
    for (i = 0; i < 4; i++)
      {
      z <<= 1;
      int nx = x - y;
      if (nx >= 0)
        {
        x = nx;
        z++;
        }
      y >>= 1;
      }

    // convert quotient to new hex digit
    if ((z += '0') > '9')
      {
      z += ('A' - '0' - 10);
      }

    *cp++ = static_cast<char>(z);
    }

  // return the remainder
  return static_cast<int>(x);
}

// convert a hex uuid string to a decimal uid string, the
// supplied uid will be at most 1.5 times as long as the uuid
void vtkConvertHexToDecimal(const char *uuid, char *uid)
{
  // max characters in a uuid and uid
  const unsigned int uuidlen = 36;
  const unsigned int uidlen = 64;

  char x[uuidlen + 4];
  char y[uidlen + 4];

  if (uuid[0] == '0' && uuid[1] == 'x')
    {
    uuid += 2;
    }

  strncpy(x, uuid, uuidlen);
  x[uuidlen] = '\0';

  char *cp = y + uidlen;
  *cp = '\0';

  char *dp = x;
  do
    {
    *(--cp) = vtkDivideHexStringBy10(x) + '0';
    // remove any leading zeros
    while (*dp == '0' || *dp == '-')
      {
      dp++;
      }
    }
  while (*dp != '\0');

  // copy out the result
  strcpy(uid, cp);
}

// convert a byte into two hexadecimal digits
inline void vtkGenerateHexDigits(unsigned char y, char cp[2])
{
  unsigned int z = (y >> 4);
  for (int j = 0; j < 2; j++)
    {
    if ((z += '0') > '9')
      {
      z += ('A' - '0' - 10);
      }
    cp[j] = static_cast<char>(z);
    z = (y & 0x0F);
    }
}

// convert n bytes into 2*n hexadecimal digits
void vtkConvertBytesToHex(const char *bytes, size_t n, char *cp)
{
  for (size_t i = 0; i < n; i++)
    {
    vtkGenerateHexDigits(*bytes, cp);
    bytes++;
    cp += 2;
    }
  *cp = '\0';
}

// generate a 36-character uuid from a 128-bit random number
// (the supplied pointer must have 37 bytes of available space)
void vtkConvertRandomToUUID(const char bytes[16], char *uuid)
{
  // copy it so that we can modify it
  char r[16];
  for (int j = 0; j < 16; j++)
    {
    r[j] = bytes[j];
    }

  // set bits to show that this is a version 4 uuid
  r[6] = ((r[6] & 0x0f) | 0x40);

  // set the uuid variant to "0b10" (0b == binary)
  r[8] = ((r[8] & 0x3f) | 0x80);

  // convert the uuid into hexidecimal text
  char *cp = uuid;
  for (unsigned int i = 0; i < 16; i++)
    {
    // add hyphens to the uuid (just to be pedantic)
    if (i == 4 || i == 6 || i == 8 || i == 10)
      {
      *cp++ = '-';
      }

    vtkGenerateHexDigits(r[i], cp);
    cp += 2;
    }

  *cp = '\0';
}

// convert a 36-character uuid to a 44-character uid
void vtkConvertUUIDToUID(const char *uuid, char *uid)
{
  strncpy(uid, "2.25.", 5);
  vtkConvertHexToDecimal(uuid, uid + 5);
}

// read from the random number generator
void vtkGenerateRandomBytes(char *bytes, vtkIdType n)
{
  int r = 0;
#ifdef _WIN32
  // use the Windows cryptography interface (WinXP and later)
  HCRYPTPROV hProv;
  r = CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
                          CRYPT_SILENT);
  if (r == 0 && GetLastError() == NTE_BAD_KEYSET)
    {
    r = CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
                            CRYPT_SILENT | CRYPT_NEWKEYSET);
    }
  if (r != 0)
    {
    r = CryptGenRandom(hProv, n, reinterpret_cast<BYTE *>(bytes));
    CryptReleaseContext(hProv, 0);
    }
#else
  // use the "random" device on unix-like systems
  std::ifstream infile("/dev/random", ios::in | ios::binary);
  infile.read(bytes, n);
  r = infile.good();
  infile.close();
#endif
  if (r == 0)
    {
    memset(bytes, '\0', n);
    vtkGenericWarningMacro(
      "vtkDICOMUtilities::GenerateUID() failed to read from "
      "the random number generator");
    }
}

// to add a little bit of recognizability to UIDs
char vtkDICOMTagToDigit(vtkDICOMTag tag)
{
  char d = '1';

  if (tag == DC::SOPInstanceUID ||
      tag == DC::MediaStorageSOPInstanceUID)
    {
    d = '2';
    }
  else if (tag == DC::SeriesInstanceUID ||
           tag == DC::ConcatenationUID)
    {
    d = '3';
    }
  else if (tag == DC::StudyInstanceUID)
    {
    d = '4';
    }
  else if (tag == DC::FrameOfReferenceUID ||
           tag == DC::VolumeFrameOfReferenceUID ||
           tag == DC::SourceFrameOfReferenceUID ||
           tag == DC::SynchronizationFrameOfReferenceUID ||
           tag == DC::TableFrameOfReferenceUID)
    {
    d = '5';
    }

  return d;
}

// get the number of random bytes to generate after this prefix
vtkIdType vtkRandomBytesForPrefix(const char *prefix)
{
  size_t n = strlen(prefix);
  if (n > 0 && prefix[n-1] != '.')
    {
    n++;
    }
  n = 64 - n;
  vtkIdType m = 0;
  if (n > 40)
    {
    m = 16; // use 128 bit random number
    }
  else
    {
    m = 12; // use 96 bit random number
    }

  return m;
}

// generate a prefixed UID using the provided random bytes
void vtkGeneratePrefixedUID(
  const char *r, vtkIdType m, const char *prefix, char d, char uid[64])
{
  size_t i = 0;
  while (*prefix != '\0' && i < 62)
    {
    uid[i++] = *prefix++;
    }
  if (i > 0 && i < 62 && uid[i-1] != '.')
    {
    uid[i++] = '.';
    }

  char hexs[36];
  vtkConvertBytesToHex(r, m, hexs);
  char decs[40];
  vtkConvertHexToDecimal(hexs, decs);

  // generate the leading digit as the UID type
  if (d >= '1' && d <= '9')
    {
    // decimal digits required to store an integer with N-1 bytes
    static const int maxDigits[16] = {
      3, 5, 8, 10, 13, 15, 17, 20, 22, 25, 27, 29, 32, 34, 37, 39
    };

    uid[i++] = d;
    // add zeros so all uids will be the same length
    size_t n = maxDigits[(m-1) & 0x0f];
    for (size_t l = strlen(decs); l < n && i < 63; l++)
      {
      uid[i++] = '0';
      }
    }

  const char *cp = decs;
  while (i < 63 && *cp != '\0')
    {
    uid[i++] = *cp++;
    }

  while (i < 64)
    {
    uid[i++] = '\0';
    }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
std::string vtkDICOMUtilities::GenerateUID(vtkDICOMTag tag)
{
  const char *prefix = vtkDICOMUtilities::UIDPrefix;
  char uid[64];

  if (prefix[0] == '\0' ||
      (prefix[0] == '2' && prefix[1] == '.' && prefix[2] == '2' &&
       prefix[3] == '5' && (prefix[4] == '.' || prefix[4] == '\0')))
    {
    // generate a 128-bit random number
    char r[16];
    vtkGenerateRandomBytes(r, 16);

    // convert to a hex uuid
    char uuid[40];
    vtkConvertRandomToUUID(r, uuid);

    // convert the hex uuid into a DICOM UID with root 2.25
    vtkConvertUUIDToUID(uuid, uid);
    }
  else
    {
    // after prefix, add a "UID type" digit followed by random digits
    char r[16];
    vtkIdType m = vtkRandomBytesForPrefix(prefix);
    vtkGenerateRandomBytes(r, m);
    char d = vtkDICOMTagToDigit(tag);
    vtkGeneratePrefixedUID(r, m, prefix, d, uid);
    }

  return uid;
}

//----------------------------------------------------------------------------
void vtkDICOMUtilities::GenerateUIDs(vtkDICOMTag tag, vtkStringArray *uids)
{
  const char *prefix = vtkDICOMUtilities::UIDPrefix;

  bool useUUIDForUID =
    (prefix[0] == '\0' ||
      (prefix[0] == '2' && prefix[1] == '.' && prefix[2] == '2' &&
       prefix[3] == '5' && (prefix[4] == '.' || prefix[4] == '\0')));

  vtkIdType m = 16;
  char d = '0';
  if (!useUUIDForUID)
    {
    m = vtkRandomBytesForPrefix(prefix);
    d = vtkDICOMTagToDigit(tag);
    }

  // read from random number generator
  vtkIdType n = uids->GetNumberOfValues();
  char *r = new char[n*m];
  vtkGenerateRandomBytes(r, n*m);

  for (vtkIdType i = 0; i < n; i++)
    {
    char uid[64];

    if (useUUIDForUID)
      {
      char uuid[40];
      vtkConvertRandomToUUID(r + i*m, uuid);
      vtkConvertUUIDToUID(uuid, uid);
      }
    else
      {
      vtkGeneratePrefixedUID(r + i*m, m, prefix, d, uid);
      }

    // put uids into the array in order (simple insertion sort)
    vtkIdType j = 0;
    for (; j < i; j++)
      {
      if (vtkDICOMUtilities::CompareUIDs(uids->GetValue(j), uid) > 0)
        {
        break;
        }
      }
    for (vtkIdType k = i; k > j; --k)
      {
      uids->SetValue(k, uids->GetValue(k - 1));
      }
    uids->SetValue(j, uid);
    }

  delete [] r;
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
  else if (*u1 == 0 || *u2 == 0)
    {
    // if one or both are the empty string
    r = (*u2 == 0 ? r : -1);
    r = (*u1 == 0 ? r : 1);
    }
  else
    {
    do
      {
      int i1 = 0;
      int i2 = 0;
      do { i1++; } while (isdigit(u1[i1]));
      do { i2++; } while (isdigit(u2[i2]));
      r = i1 - i2; // longer number wins
      if (r == 0)
        { // lexically compare numbers of the same length
        do { r = *u1++ - *u2++; } while (r == 0 && --i1 != 0);
        }
      }
    while (r == 0 && *u1 != 0 && *u2 != 0);
    // convert r to sgn(r)
    r = (r >= 0 ? r : -1);
    r = (r <= 0 ? r : 1);
    }

  return r;
}

//----------------------------------------------------------------------------
std::string vtkDICOMUtilities::GenerateDateTime(const char *z)
{
  long long zs = 0; // offset for local time in microseconds

  // get any timezone info that was supplied by the caller, if a timezone
  // was already generated for the data set we want to use it for generating
  // all time stamps for the data set
  if (z && strlen(z) == 5 && (z[0] == '+' || z[0] == '-') &&
      isdigit(z[1]) && isdigit(z[2]) && isdigit(z[3]) && isdigit(z[4]))
    {
    int zh = (z[1] - '0')*10 + (z[2] - '0');
    int zm = (z[3] - '0')*10 + (z[4] - '0');
    zs = (zh*3600 + zm*60) * (z[0] == '-' ? -1 : +1) * 1000000ll;
    }

#ifdef _WIN32
  // get the system time (UTC) on Windows
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  long long t = (static_cast<long long>(ft.dwLowDateTime) +
                 (static_cast<long long>(ft.dwHighDateTime) << 32));

  // get the current timezone offset by subtracting UTC from local time
  if (z == 0 || z[0] == '\0')
    {
    TIME_ZONE_INFORMATION tzi;
    GetTimeZoneInformation(&tzi);
    SYSTEMTIME st;
    FileTimeToSystemTime(&ft, &st);
    SYSTEMTIME lst;
    SystemTimeToTzSpecificLocalTime(&tzi, &st, &lst);
    FILETIME lft;
    SystemTimeToFileTime(&lst, &lft);
    zs = (((static_cast<long long>(lft.dwLowDateTime) +
            (static_cast<long long>(lft.dwHighDateTime) << 32)) - t)/10);
    }

  // convert file time to unix time
  t = t/10 - 11644473600000000ll;

#else
  // get the system time (UTC) on UNIX
  struct timeval tv;
  gettimeofday(&tv, 0);
  long long t = (tv.tv_sec*1000000ll + tv.tv_usec);

  // get the current time zone offset by calling localtime()
  if (z == 0 || z[0] == '\0')
    {
    static long long lastT = 0;
    if (t - lastT > 1000000ll)
      {
      // this is needed on some systems to set timezone info,
      // because it might do I/O do it at most once per second
      tzset();
      lastT = t;
      }
    // use localtime to get the offset from utc
    struct tm tmv;
    time_t tod = static_cast<time_t>(t/1000000);
    localtime_r(&tod, &tmv);
    zs = tmv.tm_gmtoff*1000000ll;
    }
#endif

  // generate a new timezone offset string
  char tzs[6] = { '+', '0', '0', '0', '0', '\0' };
  if (z == 0 || z[0] == '\0')
    {
    long long zst = zs/1000000;
    tzs[0] = (zst < 0 ? '-' : '+');
    zst = (zst < 0 ? -zst : zst);
    sprintf(&tzs[1], "%02d%02d",
            static_cast<int>((zst/3600)%24),
            static_cast<int>((zst%3600)/60));
    z = tzs;
    }

  // add the time zone offset (in microseconds)
  t += zs;

  // separate time into days and seconds
  int td = static_cast<int>(t/86400000000ll);
  long long tus = t - td*86400000000ll;

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
  int S = static_cast<int>(tus/1000000);
  int us = static_cast<int>(tus - S*1000000);
  int H = S/3600;
  S -= H*3600;
  int M = S/60;
  S -= M*60;

  // create a DICOM datetime string
  char dt[32];
  sprintf(dt, "%04d%02d%02d%02d%02d%02d.%06d%s",
          y, m, d, H, M, S, us, z);

  return dt;
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
    DICOM_MAJOR_VERSION, DICOM_MINOR_VERSION, DICOM_BUILD_VERSION);

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
