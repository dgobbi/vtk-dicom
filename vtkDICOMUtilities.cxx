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

#include <string.h>
#include <ctype.h>

// needed for random number generation
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

    unsigned int y = static_cast<unsigned char>(r[i]);
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
    memset(bytes, n, '\0');
    vtkGenericWarningMacro(
      "vtkDICOMUtilities::GenerateUID() failed to read from "
      "the random number generator");
    }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
std::string vtkDICOMUtilities::GenerateUID()
{
  // generate a 128-bit random number
  char r[16];
  vtkGenerateRandomBytes(r, 16);

  // convert to a hex uuid
  char uuid[40];
  vtkConvertRandomToUUID(r, uuid);

  // convert the hex uuid into a DICOM UID with root 2.25
  char uid[46];
  vtkConvertUUIDToUID(uuid, uid);

  return uid;
}

//----------------------------------------------------------------------------
void vtkDICOMUtilities::GenerateUIDs(vtkStringArray *uids, vtkIdType n)
{
  // read from random number generator
  char *r = new char[n*16];
  vtkGenerateRandomBytes(r, n*16);

  vtkIdType m = uids->GetNumberOfValues();
  for (vtkIdType i = 0; i < n; i++)
    {
    // convert to a hex uuid
    char uuid[40];
    vtkConvertRandomToUUID(r + i*16, uuid);

    // convert the hex uuid into a DICOM UID with root 2.25
    char uid[46];
    vtkConvertUUIDToUID(uuid, uid);

    // put uids into the array in order (simple insertion sort)
    uids->InsertNextValue("");
    vtkIdType j = m;
    for (; j < m+i; j++)
      {
      if (vtkDICOMUtilities::CompareUIDs(uids->GetValue(j), uid) > 0)
        {
        break;
        }
      }
    for (vtkIdType k = m+i; k > j; --k)
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
const char *vtkDICOMUtilities::GetDefaultImplementationClassUID()
{
  return "2.25.190146791043182537444806132342625375407";
}

//----------------------------------------------------------------------------
#define VTK_DICOM_VERSION_CREATOR2(name, x, y, z) \
  name "_" #x "_" #y "_" #z
#define VTK_DICOM_VERSION_CREATOR(name, x, y, z) \
  VTK_DICOM_VERSION_CREATOR2(name, x, y, z)
  
const char *vtkDICOMUtilities::GetDefaultImplementationVersionName()
{
  return VTK_DICOM_VERSION_CREATOR("VTK_DICOM",
    DICOM_MAJOR_VERSION, DICOM_MINOR_VERSION, DICOM_BUILD_VERSION);
}
