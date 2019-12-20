/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMUIDGenerator.h"

#include "vtkDICOMFile.h"
#include "vtkDICOMUtilities.h"

#include "vtkObjectFactory.h"
#include "vtkStringArray.h"

#include <string.h>

// needed for random number generation and time
#ifdef _WIN32
#include <windows.h>
#ifndef DICOM_DEPRECATE_WINXP
#include <wincrypt.h>
#else
#include <bcrypt.h>
#endif
#endif

vtkStandardNewMacro(vtkDICOMUIDGenerator);
vtkDICOMUIDGenerator *vtkDICOMUIDGenerator::Default;

//----------------------------------------------------------------------------
// A helper class to delete static variables when program exits.
static unsigned int vtkDICOMUIDGeneratorInitializerCounter;

// Perform initialization of static variables.
vtkDICOMUIDGeneratorInitializer::vtkDICOMUIDGeneratorInitializer()
{
  if (vtkDICOMUIDGeneratorInitializerCounter++ == 0)
  {
    vtkDICOMUIDGenerator::Default = vtkDICOMUIDGenerator::New();
  }
}

// Perform cleanup of static variables.
vtkDICOMUIDGeneratorInitializer::~vtkDICOMUIDGeneratorInitializer()
{
  if (--vtkDICOMUIDGeneratorInitializerCounter == 0)
  {
    if (vtkDICOMUIDGenerator::Default)
    {
      vtkDICOMUIDGenerator::Default->Delete();
    }
  }
}

//----------------------------------------------------------------------------
vtkDICOMUIDGenerator::vtkDICOMUIDGenerator()
{
  this->UIDPrefix = NULL;
}

//----------------------------------------------------------------------------
vtkDICOMUIDGenerator::~vtkDICOMUIDGenerator()
{
}

//----------------------------------------------------------------------------
void vtkDICOMUIDGenerator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "UIDPrefix: "
     << (this->UIDPrefix ? this->UIDPrefix : "(NULL)") << "\n";
}

//----------------------------------------------------------------------------
const char *vtkDICOMUIDGenerator::GetUIDPrefix()
{
  const char *prefix = this->UIDPrefix;
  if (prefix == NULL)
  {
    prefix = vtkDICOMUtilities::GetUIDPrefix();
  }
  return prefix;
}

//----------------------------------------------------------------------------
void vtkDICOMUIDGenerator::SetUIDPrefix(const char *uid)
{
  if (uid)
  {
    this->UIDPrefix = this->UIDPrefixStore;
    strncpy(this->UIDPrefix, uid, 63);
    this->UIDPrefix[63] = '\0';
  }
  else
  {
    this->UIDPrefix = NULL;
  }
}

//----------------------------------------------------------------------------
namespace {

// divide a hexdecimal string by 10 and return the remainder,
// this is a helper function for converting a long hex string
// (a uuid) into a decimal string (for a uid)
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

// convert a byte into two hexadecimal digits, used to convert raw
// binary into a hexadecimal string one byte at a time
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

// convert n raw bytes into 2*n hexadecimal digits
void vtkConvertBytesToHex(const unsigned char *bytes, size_t n, char *cp)
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
// (the supplied uuid pointer must have 37 bytes of available space)
void vtkConvertRandomToUUID(const unsigned char bytes[16], char *uuid)
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

  // convert the uuid into hexadecimal text
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
  memcpy(uid, "2.25.", 5);
  vtkConvertHexToDecimal(uuid, uid + 5);
}

// read from the random number generator, cryptographic quality random
// numbers are needed to ensure uniqueness of the generated uids
void vtkGenerateRandomBytes(unsigned char *bytes, vtkIdType n)
{
  int r = 0;
#ifdef _WIN32
#ifndef DICOM_DEPRECATE_WINXP
  // legacy interface (Windows XP and later)
  HCRYPTPROV hProv;
  r = CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
                          CRYPT_SILENT | CRYPT_VERIFYCONTEXT);
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
  // modern interface (Windows Vista and later), requires bcrypt.lib
  BCRYPT_ALG_HANDLE hProv;
  ULONG dwFlags = 0;
  if (BCryptOpenAlgorithmProvider(&hProv, BCRYPT_RNG_ALGORITHM, NULL, 0) != 0)
  {
    // couldn't open algorithm, fall back to default
    hProv = 0;
    dwFlags = BCRYPT_USE_SYSTEM_PREFERRED_RNG;
  }
  if (BCryptGenRandom(hProv, reinterpret_cast<BYTE *>(bytes), n, dwFlags) == 0)
  {
    // success!
    r = 1;
  }
  if (dwFlags == 0)
  {
    BCryptCloseAlgorithmProvider(hProv, 0);
  }
#endif
#else
  // use /dev/urandom, because /dev/random is too slow
  vtkDICOMFile infile("/dev/urandom", vtkDICOMFile::In);
  if (infile.GetError() == 0)
  {
    size_t m = infile.Read(bytes, n);
    r = (m == static_cast<size_t>(n));
    infile.Close();
  }
#endif
  if (r == 0)
  {
    memset(bytes, '\0', n);
    vtkGenericWarningMacro(
      "vtkDICOMUIDGenerator::GenerateUID() failed to read from "
      "the random number generator");
  }
}

// generate a single-digit numerical prefix for UIDs that identifies the
// purpose of the uid (this is just for convenience in recognizing the
// uid types, it is not suggested by the DICOM standard)
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

// get the number of random bytes to generate after this prefix,
// to ensure that we don't go over the 64 byte limit for UID length
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
  const unsigned char *r, vtkIdType m, const char *prefix, char d,
  char uid[64])
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
std::string vtkDICOMUIDGenerator::GenerateUID(vtkDICOMTag tag)
{
  const char *prefix = this->GetUIDPrefix();
  char uid[64];

  if (prefix[0] == '\0' ||
      (prefix[0] == '2' && prefix[1] == '.' && prefix[2] == '2' &&
       prefix[3] == '5' && (prefix[4] == '.' || prefix[4] == '\0')))
  {
    // generate a 128-bit random number
    unsigned char r[16];
    vtkGenerateRandomBytes(r, 16);

    // convert to a hexadecimal uuid
    char uuid[40];
    vtkConvertRandomToUUID(r, uuid);

    // convert the hexadedimal uuid into a DICOM UID with root 2.25
    vtkConvertUUIDToUID(uuid, uid);
  }
  else
  {
    // after prefix, add a "UID type" digit followed by random digits
    unsigned char r[16];
    vtkIdType m = vtkRandomBytesForPrefix(prefix);
    vtkGenerateRandomBytes(r, m);
    char d = vtkDICOMTagToDigit(tag);
    vtkGeneratePrefixedUID(r, m, prefix, d, uid);
  }

  return uid;
}

//----------------------------------------------------------------------------
void vtkDICOMUIDGenerator::GenerateUIDs(vtkDICOMTag tag, vtkStringArray *uids)
{
  const char *prefix = this->GetUIDPrefix();

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
  unsigned char *r = new unsigned char[n*m];
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
void vtkDICOMUIDGenerator::SetDefault(vtkDICOMUIDGenerator *uidgen)
{
  if (uidgen != vtkDICOMUIDGenerator::Default)
  {
    if (vtkDICOMUIDGenerator::Default)
    {
      vtkDICOMUIDGenerator::Default->Delete();
    }
    if (uidgen)
    {
      uidgen->Register(NULL);
    }
    else
    {
      uidgen = vtkDICOMUIDGenerator::New();
    }
    vtkDICOMUIDGenerator::Default = uidgen;
  }
}
