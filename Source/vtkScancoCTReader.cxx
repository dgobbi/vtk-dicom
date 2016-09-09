/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkScancoCTReader.h"
#include "vtkObjectFactory.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkImageData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkPointData.h"
#include "vtkDataArray.h"
#include "vtkStringArray.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkVersion.h"

#ifdef _WIN32
// To allow use of wchar_t paths on Windows
#include "vtkDICOMFilePath.h"
#endif

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <string>

vtkStandardNewMacro(vtkScancoCTReader);

//----------------------------------------------------------------------------
vtkScancoCTReader::vtkScancoCTReader()
{
  this->InitializeHeader();
  this->RawHeader = 0;

  // ISQ uses a lower-left-hand origin
  this->FileLowerLeft = true;
}

//----------------------------------------------------------------------------
vtkScancoCTReader::~vtkScancoCTReader()
{
  delete [] this->RawHeader;
}

//----------------------------------------------------------------------------
void vtkScancoCTReader::InitializeHeader()
{
  memset(this->Version, 0, 18);
  memset(this->PatientName, 0, 42);
  memset(this->CreationDate, 0, 32);
  memset(this->ModificationDate, 0, 32);
  this->ScanDimensionsPixels[0] = 0;
  this->ScanDimensionsPixels[1] = 0;
  this->ScanDimensionsPixels[2] = 0;
  this->ScanDimensionsPhysical[0] = 0;
  this->ScanDimensionsPhysical[1] = 0;
  this->ScanDimensionsPhysical[2] = 0;
  this->PatientIndex = 0;
  this->ScannerID = 0;
  this->SliceThickness = 0;
  this->SliceIncrement = 0;
  this->StartPosition = 0;
  this->EndPosition = 0;
  this->ZPosition = 0;
  this->DataRange[0] = 0;
  this->DataRange[1] = 0;
  this->MuScaling = 1.0;
  this->NumberOfSamples = 0;
  this->NumberOfProjections = 0;
  this->ScanDistance = 0;
  this->SampleTime = 0;
  this->ScannerType = 0;
  this->MeasurementIndex = 0;
  this->Site = 0;
  this->ReconstructionAlg = 0;
  this->ReferenceLine = 0;
  this->Energy = 0;
  this->Intensity = 0;

  this->RescaleType = 0;
  memset(this->RescaleUnits, 0, 18);
  memset(this->CalibrationData, 0, 66);
  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;
  this->MuWater = 0;

  this->Compression = 0;
}

//----------------------------------------------------------------------------
void vtkScancoCTReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "RawHeader: " << static_cast<void *>(this->RawHeader) << "\n";
  os << indent << "Version: " << this->Version << "\n";
  os << indent << "CreationDate: " << this->CreationDate << "\n";
  os << indent << "ModificationDate: " << this->ModificationDate << "\n";
  os << indent << "PatientName: " << this->PatientName << "\n";
  os << indent << "PatientIndex: " << this->PatientIndex << "\n";
  os << indent << "MeasurementIndex: " << this->MeasurementIndex << "\n";
  os << indent << "Site: " << this->Site << "\n";
  os << indent << "ScannerID: " << this->ScannerID << "\n";
  os << indent << "ScannerType: " << this->ScannerType << "\n";
  os << indent << "ScanDimensionsPixels: "
     << this->ScanDimensionsPixels[0] << " "
     << this->ScanDimensionsPixels[1] << " "
     << this->ScanDimensionsPixels[2] << "\n";
  os << indent << "ScanDimensionsPhysical: "
     << this->ScanDimensionsPhysical[0] << " "
     << this->ScanDimensionsPhysical[1] << " "
     << this->ScanDimensionsPhysical[2] << "\n";
  os << indent << "ZPosition: " << this->ZPosition << " [mm]\n";
  os << indent << "StartPosition: " << this->StartPosition << " [mm]\n";
  os << indent << "EndPosition: " << this->EndPosition << " [mm]\n";
  os << indent << "ReferenceLine: " << this->ReferenceLine << " [mm]\n";
  os << indent << "NumberOfSamples: " << this->NumberOfSamples << "\n";
  os << indent << "NumberOfProjections: " << this->NumberOfProjections << "\n";
  os << indent << "ScanDistance: " << this->ScanDistance << " [mm]\n";
  os << indent << "SampleTime: " << this->SampleTime << " [ms]\n";
  os << indent << "SliceThickness: " << this->SliceThickness << " [mm]\n";
  os << indent << "SliceIncrement: " << this->SliceIncrement << " [mm]\n";
  os << indent << "ReconstructionAlg: " << this->ReconstructionAlg << "\n";
  os << indent << "Energy: " << this->Energy << " [kV]\n";
  os << indent << "Intensity: " << this->Intensity << " [mA]\n";
  os << indent << "MuScaling: " << this->MuScaling << " [cm]\n";
  os << indent << "DataRange: "
     << this->DataRange[0] << " " << this->DataRange[1] << "\n";
  os << indent << "CalibrationData: " << this->CalibrationData << "\n";
  os << indent << "RescaleType: " << this->RescaleType << "\n";
  os << indent << "RescaleUnits: " << this->RescaleUnits << "\n";
  os << indent << "RescaleSlope: " << this->RescaleSlope << "\n";
  os << indent << "RescaleIntercept: " << this->RescaleIntercept << "\n";
  os << indent << "MuWater: " << this->MuWater << " [cm^-1]\n";
}

//----------------------------------------------------------------------------
int vtkScancoCTReader::CheckVersion(const char header[16])
{
  int fileType = 0;

  if (strncmp(header, "CTDATA-HEADER_V1", 16) == 0)
  {
    fileType = 1;
  }
  else if (strcmp(header, "AIMDATA_V030   ") == 0)
  {
    fileType = 3;
  }
  else
  {
    int preHeaderSize = vtkScancoCTReader::DecodeInt(header);
    int imageHeaderSize = vtkScancoCTReader::DecodeInt(header + 4);
    if (preHeaderSize == 20 && imageHeaderSize == 140)
    {
      fileType = 2;
    }
  }

  return fileType;
}

//----------------------------------------------------------------------------
int vtkScancoCTReader::CanReadFile(const char *filename)
{
  ifstream infile(filename, ios::in | ios::binary);

  bool canRead = false;
  if (infile.good())
  {
    // header is a 512 byte block
    char buffer[512];
    infile.read(buffer, 512);
    if (!infile.bad())
    {
      int fileType = vtkScancoCTReader::CheckVersion(buffer);
      canRead = (fileType > 0);
    }
  }

  infile.close();

  return canRead;
}

//----------------------------------------------------------------------------
void vtkScancoCTReader::DecodeDate(const void *data,
  int& year, int& month, int& day,
  int& hour, int& minute, int& second, int& millis)
{
  // This is the offset between the astronomical "Julian day", which counts
  // days since January 1, 4713BC, and the "VMS epoch", which counts from
  // November 17, 1858:
  const vtkTypeUInt64 julianOffset = 2400001;
  const vtkTypeUInt64 millisPerSecond = 1000;
  const vtkTypeUInt64 millisPerMinute = 60 * 1000;
  const vtkTypeUInt64 millisPerHour = 3600 * 1000;
  const vtkTypeUInt64 millisPerDay = 3600 * 24 * 1000;

  // Read the date as a long integer with units of 1e-7 seconds
  int d1 = vtkScancoCTReader::DecodeInt(data);
  int d2 = vtkScancoCTReader::DecodeInt(static_cast<const char *>(data)+4);
  vtkTypeUInt64 tVMS = d1 + (static_cast<vtkTypeUInt64>(d2) << 32);
  vtkTypeUInt64 time = tVMS/10000 + julianOffset*millisPerDay;

  int y, m, d;
  int julianDay = static_cast<int>(time / millisPerDay);
  time -= millisPerDay*julianDay;

  // Gregorian calendar starting from October 15, 1582
  // This algorithm is from Henry F. Fliegel and Thomas C. Van Flandern
  int ell, n, i, j;
  ell = julianDay + 68569;
  n = (4 * ell) / 146097;
  ell = ell - (146097 * n + 3) / 4;
  i = (4000 * (ell + 1)) / 1461001;
  ell = ell - (1461 * i) / 4 + 31;
  j = (80 * ell) / 2447;
  d = ell - (2447 * j) / 80;
  ell = j / 11;
  m = j + 2 - (12 * ell);
  y = 100 * (n - 49) + i + ell;

  // Return the result
  year = y;
  month = m;
  day = d;
  hour = static_cast<int>(time / millisPerHour);
  time -= hour*millisPerHour;
  minute = static_cast<int>(time / millisPerMinute);
  time -= minute*millisPerMinute;
  second = static_cast<int>(time / millisPerSecond);
  time -= second*millisPerSecond;
  millis = static_cast<int>(time);
}

//----------------------------------------------------------------------------
int vtkScancoCTReader::DecodeInt(const void *data)
{
  const unsigned char *cp = static_cast<const unsigned char *>(data);
  return (cp[0] | (cp[1] << 8) | (cp[2] << 16) | (cp[3] << 24));
}

//----------------------------------------------------------------------------
float vtkScancoCTReader::DecodeFloat(const void *data)
{
  const unsigned char *cp = static_cast<const unsigned char *>(data);
  // different ordering and exponent bias than IEEE 754 float
  union { float f; unsigned int i; } v;
  v.i = (cp[0] << 16) | (cp[1] << 24) | cp[2] | (cp[3] << 8);
  return 0.25*v.f;
}

//----------------------------------------------------------------------------
double vtkScancoCTReader::DecodeDouble(const void *data)
{
  // different ordering and exponent bias than IEEE 754 double
  const unsigned char *cp = static_cast<const unsigned char *>(data);
  union { double d; vtkTypeUInt64 l; } v;
  unsigned int l1, l2;
  l1 = (cp[0] << 16) | (cp[1] << 24) | cp[2] | (cp[3] << 8);
  l2 = (cp[4] << 16) | (cp[5] << 24) | cp[6] | (cp[7] << 8);
  v.l = (static_cast<vtkTypeUInt64>(l1) << 32) | l2;
  return v.d*0.25;
}

//----------------------------------------------------------------------------
void vtkScancoCTReader::StripString(char *dest, const char *cp, size_t l)
{
  char *dp = dest;
  for (size_t i = 0; i < l && *cp != '\0'; i++)
  {
    *dp++ = *cp++;
  }
  while (dp != dest && dp[-1] == ' ')
  {
    dp--;
  }
  *dp = '\0';
}

//----------------------------------------------------------------------------
int vtkScancoCTReader::ReadISQHeader(ifstream *file, unsigned long bytesRead)
{
  if (bytesRead < 512)
  {
    return 0;
  }

  char *h = this->RawHeader;
  vtkScancoCTReader::StripString(this->Version, h, 16); h += 16;
  int dataType = vtkScancoCTReader::DecodeInt(h); h += 4;
  /*int numBytes = vtkScancoCTReader::DecodeInt(h);*/ h += 4;
  /*int numBlocks = vtkScancoCTReader::DecodeInt(h);*/ h += 4;
  this->PatientIndex = vtkScancoCTReader::DecodeInt(h); h += 4;
  this->ScannerID = vtkScancoCTReader::DecodeInt(h); h += 4;
  int year, month, day, hour, minute, second, milli;
  vtkScancoCTReader::DecodeDate(
    h, year, month, day, hour, minute, second, milli); h += 8;
  int pixdim[3], physdim[3];
  pixdim[0] = vtkScancoCTReader::DecodeInt(h); h += 4;
  pixdim[1] = vtkScancoCTReader::DecodeInt(h); h += 4;
  pixdim[2] = vtkScancoCTReader::DecodeInt(h); h += 4;
  physdim[0] = vtkScancoCTReader::DecodeInt(h); h += 4;
  physdim[1] = vtkScancoCTReader::DecodeInt(h); h += 4;
  physdim[2] = vtkScancoCTReader::DecodeInt(h); h += 4;

  bool isRAD = (dataType == 9 || physdim[2] == 0);

  if (isRAD) // RAD file
  {
    this->MeasurementIndex = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->DataRange[0] = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->DataRange[1] = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->MuScaling = vtkScancoCTReader::DecodeInt(h); h += 4;
    vtkScancoCTReader::StripString(this->PatientName, h, 40); h += 40;
    this->ZPosition = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    /* unknown */ h += 4;
    this->SampleTime = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->Energy = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->Intensity = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->ReferenceLine = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->StartPosition = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->EndPosition = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    h += 88*4;
  }
  else // ISQ file or RSQ file
  {
    this->SliceThickness = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->SliceIncrement = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->StartPosition = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->EndPosition =
      this->StartPosition + physdim[2]*1e-3*(pixdim[2] - 1)/pixdim[2];
    this->DataRange[0] = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->DataRange[1] = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->MuScaling = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->NumberOfSamples = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->NumberOfProjections = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->ScanDistance = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->ScannerType = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->SampleTime = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->MeasurementIndex = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->Site = vtkScancoCTReader::DecodeInt(h); h += 4;
    this->ReferenceLine = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->ReconstructionAlg = vtkScancoCTReader::DecodeInt(h); h += 4;
    vtkScancoCTReader::StripString(this->PatientName, h, 40); h += 40;
    this->Energy = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    this->Intensity = vtkScancoCTReader::DecodeInt(h)*1e-3; h += 4;
    h += 83*4;
  }

  int dataOffset = vtkScancoCTReader::DecodeInt(h);

  // fix SliceThickness and SliceIncrement if they were truncated
  if (physdim[2] != 0)
  {
    double computedSpacing = physdim[2]*1e-3/pixdim[2];
    if (fabs(computedSpacing - this->SliceThickness) < 1.1e-3)
    {
      this->SliceThickness = computedSpacing;
    }
    if (fabs(computedSpacing - this->SliceIncrement) < 1.1e-3)
    {
      this->SliceIncrement = computedSpacing;
    }
  }

  // Convert date information into a string
  month = ((month > 12 || month < 1) ? 0 : month);
  static const char *months[] = { "XXX", "JAN", "FEB", "MAR", "APR", "MAY",
    "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };
  sprintf(this->CreationDate, "%d-%s-%d %02d:%02d:%02d.%03d",
          (day % 100), months[month], (year % 10000),
          (hour % 100), (minute % 100), (second % 100), (milli % 1000));
  sprintf(this->ModificationDate, "%d-%s-%d %02d:%02d:%02d.%03d",
          (day % 100), months[month], (year % 10000),
          (hour % 100), (minute % 100), (second % 100), (milli % 1000));

  this->SetDataByteOrderToLittleEndian();
  this->SetFileDimensionality(3);

  // Perform a sanity check on the dimensions
  for (int i = 0; i < 3; i++)
  {
    this->ScanDimensionsPixels[i] = pixdim[i];
    if (pixdim[i] < 1)
    {
      pixdim[i] = 1;
    }
    this->ScanDimensionsPhysical[i] =
      (isRAD ? physdim[i]*1e-6 : physdim[i]*1e-3);
    if (physdim[i] == 0)
    {
      physdim[i] = 1.0;
    }
  }

  this->SetDataExtent(0, pixdim[0]-1,
                      0, pixdim[1]-1,
                      0, pixdim[2]-1);

  this->SetDataOrigin(0.0, 0.0, 0.0);

  if (isRAD) // RAD file
  {
    this->SetDataSpacing(physdim[0]*1e-6/pixdim[0],
                         physdim[1]*1e-6/pixdim[1],
                         1.0);
  }
  else
  {
    this->SetDataSpacing(physdim[0]*1e-3/pixdim[0],
                         physdim[1]*1e-3/pixdim[1],
                         physdim[2]*1e-3/pixdim[2]);
  }

  this->SetDataScalarType(VTK_SHORT);
  this->SetNumberOfScalarComponents(1);

  // total header size
  unsigned long headerSize = static_cast<unsigned long>(dataOffset + 1)*512;
  this->SetHeaderSize(headerSize);

  // read the rest of the header
  if (headerSize > bytesRead)
  {
    h = new char[headerSize];
    memcpy(h, this->RawHeader, bytesRead);
    delete [] this->RawHeader;
    this->RawHeader = h;
    file->read(h + bytesRead, headerSize - bytesRead);
    if (static_cast<unsigned long>(file->gcount()) < headerSize - bytesRead)
    {
      return 0;
    }
  }

  // decode the extended header (lots of guesswork)
  if (headerSize >= 2048)
  {
    char *calHeader = 0;
    int calHeaderSize = 0;
    h = this->RawHeader + 512;
    unsigned long hskip = 1;
    char *headerName = h + 8;
    if (strncmp(headerName, "MultiHeader     ", 16) == 0)
    {
      h += 512;
      hskip += 1;
    }
    unsigned long hsize = 0;
    for (int i = 0; i < 4; i++)
    {
      hsize = vtkScancoCTReader::DecodeInt(h + i*128 + 24);
      if ((1 + hskip + hsize)*512 > headerSize)
      {
        break;
      }
      headerName = h + i*128 + 8;
      if (strncmp(headerName, "Calibration     ", 16) == 0)
      {
        calHeader = this->RawHeader + (1 + hskip)*512;
        calHeaderSize = hsize*512;
      }
      hskip += hsize;
    }

    if (calHeader && calHeaderSize >= 1024)
    {
      h = calHeader;
      vtkScancoCTReader::StripString(this->CalibrationData, h + 28, 64);
      // std::string calFile(h + 112, 256);
      // std::string s3(h + 376, 256);
      this->RescaleType = vtkScancoCTReader::DecodeInt(h + 632);
      vtkScancoCTReader::StripString(this->RescaleUnits, h + 648, 16);
      // std::string s5(h + 700, 16);
      // std::string calFilter(h + 772, 16);
      this->RescaleSlope = vtkScancoCTReader::DecodeDouble(h + 664);
      this->RescaleIntercept = vtkScancoCTReader::DecodeDouble(h + 672);
      this->MuWater = vtkScancoCTReader::DecodeDouble(h + 688);
    }
  }

  // Include conversion to linear att coeff in the rescaling
  if (this->MuScaling != 0)
  {
    this->RescaleSlope /= this->MuScaling;
  }

  return 1;
}

//----------------------------------------------------------------------------
int vtkScancoCTReader::ReadAIMHeader(ifstream *file, unsigned long bytesRead)
{
  if (bytesRead < 160)
  {
    return 0;
  }

  char *h = this->RawHeader;
  int intSize = 0;
  unsigned long headerSize = 0;
  if (strcmp(h, "AIMDATA_V030   ") == 0)
  {
    // header uses 64-bit ints (8 bytes)
    intSize = 8;
    strcpy(this->Version, h);
    headerSize = 16;
    h += headerSize;
  }
  else
  {
    // header uses 32-bit ints (4 bytes)
    intSize = 4;
    strcpy(this->Version, "AIMDATA_V020   ");
  }

  // read the pre-header
  char *preheader = h;
  int preheaderSize = vtkScancoCTReader::DecodeInt(h); h += intSize;
  int structSize = vtkScancoCTReader::DecodeInt(h); h += intSize;
  int logSize = vtkScancoCTReader::DecodeInt(h); h += intSize;

  // read the rest of the header
  headerSize += preheaderSize + structSize + logSize;
  this->SetHeaderSize(headerSize);
  if (headerSize > bytesRead)
  {
    h = new char[headerSize];
    memcpy(h, this->RawHeader, bytesRead);
    preheader = h + (preheader - this->RawHeader);
    delete [] this->RawHeader;
    this->RawHeader = h;
    file->read(h + bytesRead, headerSize - bytesRead);
    if (static_cast<unsigned long>(file->gcount()) < headerSize - bytesRead)
    {
      return 0;
    }
  }

  // decode the struct header
  h = preheader + preheaderSize;
  h += 20; // not sure what these 20 bytes are for
  int dataType = vtkScancoCTReader::DecodeInt(h); h += 4;
  int structValues[21];
  for (int i = 0; i < 21; i++)
  {
    structValues[i] = vtkScancoCTReader::DecodeInt(h); h += intSize;
  }
  float elementSize[3];
  for (int i = 0; i < 3; i++)
  {
    elementSize[i] = vtkScancoCTReader::DecodeFloat(h);
    if (elementSize[i] == 0)
    {
      elementSize[i] = 1.0;
    }
    h += 4;
  }

  // number of components per pixel is 1 by default
  int scalarType = VTK_UNSIGNED_CHAR;
  int scalarComponents = 1;
  this->Compression = 0;

  // a limited selection of data types are supported
  // (only 0x00010001 (char) and 0x00020002 (short) are fully tested)
  switch (dataType)
  {
    case 0x00160001:
      scalarType = VTK_UNSIGNED_CHAR;
      break;
    case 0x000d0001:
      scalarType = VTK_UNSIGNED_CHAR;
      break;
    case 0x00120003:
      scalarType = VTK_UNSIGNED_CHAR;
      scalarComponents = 3;
      break;
    case 0x00010001:
      scalarType = VTK_SIGNED_CHAR;
      break;
    case 0x00060003:
      scalarType = VTK_SIGNED_CHAR;
      scalarComponents = 3;
      break;
    case 0x00170002:
      scalarType = VTK_UNSIGNED_SHORT;
      break;
    case 0x00020002:
      scalarType = VTK_SHORT;
      break;
    case 0x00030004:
      scalarType = VTK_INT;
      break;
    case 0x001a0004:
      scalarType = VTK_FLOAT;
      break;
    case 0x00150001:
      this->Compression = 0x00b2; // run-length compressed bits
      scalarType = VTK_SIGNED_CHAR;
      break;
    case 0x00080002:
      this->Compression = 0x00c2; // run-length compressed signed char
      scalarType = VTK_SIGNED_CHAR;
      break;
    case 0x00060001:
      this->Compression = 0x00b1; // packed bits
      scalarType = VTK_SIGNED_CHAR;
      break;
    default:
      vtkErrorMacro("Unrecognized data type in AIM file: " << dataType);
      return 0;
  }

  this->SetDataScalarType(scalarType);
  this->SetNumberOfScalarComponents(scalarComponents);
  this->SetDataByteOrderToLittleEndian();
  this->SetFileDimensionality(3);

  this->SetDataExtent(0, structValues[3]-1,
                      0, structValues[4]-1,
                      0, structValues[5]-1);

  this->SetDataSpacing(elementSize[0],
                       elementSize[1],
                       elementSize[2]);

  // the origin will reflect the cropping of the data
  this->SetDataOrigin(this->DataSpacing[0]*structValues[0],
                      this->DataSpacing[1]*structValues[1],
                      this->DataSpacing[2]*structValues[2]);

  // decode the processing log
  h = preheader + preheaderSize + structSize;
  char *logEnd = h + logSize;

  while (h != logEnd && *h != '\0')
  {
    // skip newline and go to next line
    if (*h == '\n')
    {
      h++;
    }

    // search for the end of this line
    char *lineEnd = h;
    while (lineEnd != logEnd && *lineEnd != '\n' && *lineEnd != '\0')
    {
      lineEnd++;
    }

    // if not a comment, search for keys
    if (h != lineEnd && *h != '!' && (*lineEnd == '\n' || *lineEnd == '\0'))
    {
      // key and value are separated by multiple spaces
      char *key = h;
      while (h+1 != lineEnd && (h[0] != ' ' || h[1] != ' '))
      {
        h++;
      }
      // this gives the length of the key
      size_t keylen = h - key;
      // skip to the end of the spaces
      while (h != lineEnd && *h == ' ')
      {
        h++;
      }
      // this is where the value starts
      char *value = h;
      size_t valuelen = lineEnd - value;
      // look for trailing spaces
      while (valuelen > 0 &&
             (h[valuelen-1] == ' ' || h[valuelen-1] == '\r'))
      {
        valuelen--;
      }

      // convert into a std::string for convenience
      std::string skey(key, keylen);

      // check for known keys
      if (skey == "Time")
      {
        valuelen = (valuelen > 31 ? 31 : valuelen);
        strncpy(this->ModificationDate, value, valuelen);
        this->ModificationDate[valuelen] = '\0';
      }
      else if (skey == "Original Creation-Date")
      {
        valuelen = (valuelen > 31 ? 31 : valuelen);
        strncpy(this->CreationDate, value, valuelen);
        this->CreationDate[valuelen] = '\0';
      }
      else if (skey == "Orig-ISQ-Dim-p")
      {
        for (int i = 0; i < 3; i++)
        {
          this->ScanDimensionsPixels[i] = strtol(value, &value, 10);
        }
      }
      else if (skey == "Orig-ISQ-Dim-um")
      {
        for (int i = 0; i < 3; i++)
        {
          this->ScanDimensionsPhysical[i] = strtod(value, &value)*1e-3;
        }
      }
      else if (skey == "Patient Name")
      {
        valuelen = (valuelen > 41 ? 41 : valuelen);
        strncpy(this->PatientName, value, valuelen);
        this->PatientName[valuelen] = '\0';
      }
      else if (skey == "Index Patient")
      {
        this->PatientIndex = strtol(value, 0, 10);
      }
      else if (skey == "Index Measurement")
      {
        this->MeasurementIndex = strtol(value, 0, 10);
      }
      else if (skey == "Site")
      {
        this->Site = strtol(value, 0, 10);
      }
      else if (skey == "Scanner ID")
      {
        this->ScannerID = strtol(value, 0, 10);
      }
      else if (skey == "Scanner type")
      {
        this->ScannerType = strtol(value, 0, 10);
      }
      else if (skey == "Position Slice 1 [um]")
      {
        this->StartPosition = strtod(value, 0)*1e-3;
        this->EndPosition =
          this->StartPosition + elementSize[2]*(structValues[5] - 1);
      }
      else if (skey == "No. samples")
      {
        this->NumberOfSamples = strtol(value, 0, 10);
      }
      else if (skey == "No. projections per 180")
      {
        this->NumberOfProjections = strtol(value, 0, 10);
      }
      else if (skey == "Scan Distance [um]")
      {
        this->ScanDistance = strtod(value, 0)*1e-3;
      }
      else if (skey == "Integration time [us]")
      {
        this->SampleTime = strtod(value, 0)*1e-3;
      }
      else if (skey == "Reference line [um]")
      {
        this->ReferenceLine = strtod(value, 0)*1e-3;
      }
      else if (skey == "Reconstruction-Alg.")
      {
        this->ReconstructionAlg = strtol(value, 0, 10);
      }
      else if (skey == "Energy [V]")
      {
        this->Energy = strtod(value, 0)*1e-3;
      }
      else if (skey == "Intensity [uA]")
      {
        this->Intensity = strtod(value, 0)*1e-3;
      }
      else if (skey == "Mu_Scaling")
      {
        this->MuScaling = strtol(value, 0, 10);
      }
      else if (skey == "Minimum data value")
      {
        this->DataRange[0] = strtod(value, 0);
      }
      else if (skey == "Maximum data value")
      {
        this->DataRange[1] = strtod(value, 0);
      }
      else if (skey == "Calib. default unit type")
      {
        this->RescaleType = strtol(value, 0, 10);
      }
      else if (skey == "Calibration Data")
      {
        valuelen = (valuelen > 64 ? 64 : valuelen);
        strncpy(this->CalibrationData, value, valuelen);
        this->CalibrationData[valuelen] = '\0';
      }
      else if (skey == "Density: unit")
      {
        valuelen = (valuelen > 16 ? 16 : valuelen);
        strncpy(this->RescaleUnits, value, valuelen);
        this->RescaleUnits[valuelen] = '\0';
      }
      else if (skey == "Density: slope")
      {
        this->RescaleSlope = strtod(value, 0);
      }
      else if (skey == "Density: intercept")
      {
        this->RescaleIntercept = strtod(value, 0);
      }
      else if (skey == "HU: mu water")
      {
        this->MuWater = strtod(value, 0);
      }
    }
    // skip to the end of the line
    h = lineEnd;
  }

  // Include conversion to linear att coeff in the rescaling
  if (this->MuScaling != 0)
  {
    this->RescaleSlope /= this->MuScaling;
  }

  // these items are not in the processing log
  this->SliceThickness = elementSize[2];
  this->SliceIncrement = elementSize[2];

  return 1;
}

//----------------------------------------------------------------------------
int vtkScancoCTReader::RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  // Clear the error indicator.
  this->SetErrorCode(vtkErrorCode::NoError);

  this->InitializeHeader();

  const char *filename = this->FileName;
  if (filename == 0)
  {
    vtkErrorMacro("A filename must be specified");
    return 0;
  }

  vtkDebugMacro("Opening ISQ/AIM file " << filename);

#ifdef _WIN32
  vtkDICOMFilePath fp(filename);
  const wchar_t *ufilename = fp.Wide();
#else
  const char *ufilename = filename;
#endif

  ifstream infile(ufilename, ios::in | ios::binary);
  if (!infile.good())
  {
    vtkErrorMacro("Cannot open file " << filename);
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    return 0;
  }

  // header is a 512 byte block
  delete [] this->RawHeader;
  this->RawHeader = new char[512];
  infile.read(this->RawHeader, 512);
  int fileType = 0;
  unsigned long bytesRead = 0;
  if (!infile.bad())
  {
    bytesRead = static_cast<unsigned long>(infile.gcount());
    fileType = vtkScancoCTReader::CheckVersion(this->RawHeader);
  }

  if (fileType == 0)
  {
    vtkErrorMacro(<< "Unrecognized header in " << filename);
    this->SetErrorCode(vtkErrorCode::UnrecognizedFileTypeError);
    infile.close();
    return 0;
  }

  int returnValue = 0;
  if (fileType == 1)
  {
    returnValue = this->ReadISQHeader(&infile, bytesRead);
  }
  else
  {
    returnValue = this->ReadAIMHeader(&infile, bytesRead);
  }

  infile.close();

  // This code causes rescaling to Hounsfield units
  /*
  if (this->MuScaling > 0 && this->MuWater > 0)
    {
    // HU = 1000*(u - u_water)/u_water
    this->RescaleSlope = 1000.0/(this->MuWater * this->MuScaling);
    this->RescaleIntercept = -1000.0;
    }
  */

  // Set the output information.
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkDataObject::SetPointDataActiveScalarInfo(
    outInfo, this->DataScalarType, this->NumberOfScalarComponents);

  outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(),  this->DataOrigin, 3);

  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               this->DataExtent, 6);

  return returnValue;
}

//----------------------------------------------------------------------------
int vtkScancoCTReader::RequestData(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  if (this->Compression == 0)
  {
    return this->Superclass::RequestData(request, inputVector, outputVector);
  }

  // check whether the reader is in an error state
  if (this->GetErrorCode() != vtkErrorCode::NoError)
  {
    return 0;
  }

  // which output port did the request come from
  int outputPort =
    request->Get(vtkDemandDrivenPipeline::FROM_OUTPUT_PORT());

  // for now, this reader has only one output
  if (outputPort > 0)
  {
    return 1;
  }

  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  int extent[6];
  outInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);

  // get the data object, allocate memory
  vtkImageData *data =
    static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));
#if VTK_MAJOR_VERSION >= 6
  this->AllocateOutputData(data, outInfo, extent);
#else
  this->AllocateOutputData(data, extent);
#endif

  data->GetPointData()->GetScalars()->SetName("ImageFile");

  const char *filename = 0;
  if (this->FileNames && this->FileNames->GetNumberOfValues() == 1)
  {
    filename = this->FileNames->GetValue(0);
  }
  else
  {
    filename = this->GetFileName();
  }

  if (filename == 0)
  {
    vtkErrorMacro("A FileName must be provided");
    return 0;
  }

  // get the pointer to the output
  unsigned char *dataPtr =
    static_cast<unsigned char *>(data->GetScalarPointer());

  // open the file
  ifstream infile(filename, ios::in | ios::binary);
  if (!infile.good())
  {
    vtkErrorMacro("Cannot open file " << filename);
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    return 0;
  }

  // seek to the data
  infile.seekg(this->HeaderSize);

  // get the size of the compressed data
  int intSize = 4;
  if (strcmp(this->Version, "AIMDATA_V030   ") == 0)
  {
    // header uses 64-bit ints (8 bytes)
    intSize = 8;
  }

  // Dimensions of the data
  int xsize = (extent[1] - extent[0] + 1);
  int ysize = (extent[3] - extent[2] + 1);
  int zsize = (extent[5] - extent[4] + 1);
  size_t outSize = xsize;
  outSize *= ysize;
  outSize *= zsize;

  // For the input (compressed) data
  char *input = 0;
  size_t size = 0;

  if (this->Compression == 0x00b1)
  {
    // Compute the size of the binary packed data
    size_t xinc = (xsize+1)/2;
    size_t yinc = (ysize+1)/2;
    size_t zinc = (zsize+1)/2;
    size = xinc*yinc*zinc + 1;
    input = new char[size];
    infile.read(input, size);
  }
  else if (this->Compression == 0x00b2 ||
           this->Compression == 0x00c2)
  {
    // Get the size of the compressed data
    char head[8];
    infile.read(head, intSize);
    size = static_cast<unsigned int>(vtkScancoCTReader::DecodeInt(head));
    if (intSize == 8)
    {
      // Read the high word of a 64-bit int
      unsigned int high = vtkScancoCTReader::DecodeInt(head + 4);
      size += (static_cast<vtkTypeUInt64>(high) << 32);
    }
    input = new char[size - intSize];
    size -= intSize;
    infile.read(input, size);
  }

  // confirm that enough data was read
  size_t shortread = size - infile.gcount();
  if (shortread != 0)
  {
    this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
    vtkErrorMacro("File is truncated, " << shortread << " bytes are missing");
  }

  // Close the file
  infile.close();

  if (this->Compression == 0x00b1)
  {
    // Unpack binary data, each byte becomes a 2x2x2 block of voxels
    size_t xinc = (xsize+1)/2;
    size_t yinc = (ysize+1)/2;
    unsigned char v = input[size-1];
    v = (v == 0 ? 0x7f : v);
    unsigned char bit = 0;
    for (int i = 0; i < zsize; i++)
    {
      bit ^= (bit & 2);
      for (int j = 0; j < ysize; j++)
      {
        char *inPtr = input + (i*yinc + j)*xinc;
        bit ^= (bit & 1);
        for (int k = 0; k < xsize; k++)
        {
          unsigned char c = *inPtr;
          *dataPtr++ = ((c >> bit) & 1)*v;
          inPtr += (bit & 1);
          bit ^= 1;
        }
        bit ^= 2;
      }
      bit ^= 4;
    }
  }
  else if (this->Compression == 0x00b2)
  {
    // Decompress binary run-lengths
    bool flip = 0;
    unsigned char v = input[flip];
    char *inPtr = input + 2;
    size -= 2;
    if (size > 0)
    {
      do
      {
        unsigned char l = *inPtr++;
        if (l == 255)
        {
          l = 254;
          flip = !flip;
        }
        if (l > outSize)
        {
          l = outSize;
        }
        outSize -= l;
        if (l > 0)
        {
          do
          {
            *dataPtr++ = v;
          }
          while (--l);
        }
        flip = !flip;
        v = input[flip];
      }
      while (--size != 0 && outSize != 0);
    }
  }
  else if (this->Compression == 0x00c2)
  {
    // Decompress 8-bit run-lengths
    char *inPtr = input;
    size /= 2;
    if (size > 0)
    {
      do
      {
        unsigned char l = inPtr[0];
        unsigned char v = inPtr[1];
        inPtr += 2;
        if (l > outSize)
        {
          l = outSize;
        }
        outSize -= l;
        if (l > 0)
        {
          do
          {
            *dataPtr++ = v;
          }
          while (--l);
        }
      }
      while (--size != 0 && outSize != 0);
    }
  }

  delete [] input;

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}
