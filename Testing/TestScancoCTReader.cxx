#include "vtkScancoCTReader.h"

#include "vtkErrorCode.h"
#include "vtkImageData.h"
#include "vtkObject.h"
#include "vtkSmartPointer.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>

// macro for performing tests
#define TestAssert(t) \
if (!(t)) \
{ \
  std::cout << exename << ": Assertion Failed: " << #t << "\n"; \
  std::cout << __FILE__ << ":" << __LINE__ << "\n"; \
  std::cout.flush(); \
  rval |= 1; \
}

namespace {

typedef std::vector<char> Bytes;

// AIM v020: a pre-header of five 4-byte lengths, then the image structure
const size_t AIMPreHeaderSize = 20;
const size_t AIMStructSize = 140;
const size_t AIMStructLengthPosition = 4;
const size_t AIMLogLengthPosition = 8;
const size_t AIMDataLengthPosition = 12;
const size_t AIMTypeOffset = 20;
const size_t AIMDimensionOffset = 36;
const size_t AIMElementSizeOffset = 108;

// AIM v030: a version string, then a pre-header of five 8-byte lengths
const size_t AIMV030VersionSize = 16;
const size_t AIMV030PreHeaderSize = 40;
const size_t AIMV030StructSize = 224;

// ISQ: one 512-byte block that ends with the data offset in blocks
const size_t ISQBlockSize = 512;
const size_t ISQDimensionPosition = 44;
const size_t ISQPhysicalDimensionPosition = 56;
const size_t ISQDataOffsetPosition = 508;

// AIM data types
const int AIMShort = 0x00020002;
const int AIMPackedBits = 0x00060001;
const int AIMRunLengthBits = 0x00150001;
const int AIMRunLengthChar = 0x00080002;

void PutInt(Bytes& bytes, size_t offset, int value)
{
  unsigned int u = static_cast<unsigned int>(value);
  for (size_t i = 0; i < 4; i++)
  {
    bytes[offset + i] = static_cast<char>((u >> (8*i)) & 0xff);
  }
}

void AppendInt(Bytes& bytes, int value)
{
  bytes.resize(bytes.size() + 4);
  PutInt(bytes, bytes.size() - 4, value);
}

Bytes MakeAIM(int dataType, int xsize, int ysize, int zsize,
              const Bytes& data)
{
  Bytes bytes(AIMPreHeaderSize + AIMStructSize, 0);
  PutInt(bytes, 0, static_cast<int>(AIMPreHeaderSize));
  PutInt(bytes, AIMStructLengthPosition, static_cast<int>(AIMStructSize));
  PutInt(bytes, AIMDataLengthPosition, static_cast<int>(data.size()));
  const size_t s = AIMPreHeaderSize;
  PutInt(bytes, s + AIMTypeOffset, dataType);
  PutInt(bytes, s + AIMDimensionOffset, xsize);
  PutInt(bytes, s + AIMDimensionOffset + 4, ysize);
  PutInt(bytes, s + AIMDimensionOffset + 8, zsize);
  const float spacing = 1.0f;
  for (size_t i = 0; i < 3; i++)
  {
    memcpy(&bytes[s + AIMElementSizeOffset + 4*i], &spacing, 4);
  }
  bytes.insert(bytes.end(), data.begin(), data.end());
  return bytes;
}

Bytes MakeAIMV030(const Bytes& data)
{
  Bytes bytes(AIMV030VersionSize + AIMV030PreHeaderSize + AIMV030StructSize,
              0);
  memcpy(&bytes[0], "AIMDATA_V030   ", 15);
  PutInt(bytes, AIMV030VersionSize, static_cast<int>(AIMV030PreHeaderSize));
  PutInt(bytes, AIMV030VersionSize + 8, static_cast<int>(AIMV030StructSize));
  bytes.insert(bytes.end(), data.begin(), data.end());
  return bytes;
}

Bytes MakeISQ(int xsize, int ysize, int zsize, const Bytes& data)
{
  Bytes bytes(ISQBlockSize, 0);
  memcpy(&bytes[0], "CTDATA-HEADER_V1", 16);
  PutInt(bytes, ISQDimensionPosition, xsize);
  PutInt(bytes, ISQDimensionPosition + 4, ysize);
  PutInt(bytes, ISQDimensionPosition + 8, zsize);
  PutInt(bytes, ISQPhysicalDimensionPosition, 1000*xsize);
  PutInt(bytes, ISQPhysicalDimensionPosition + 4, 1000*ysize);
  PutInt(bytes, ISQPhysicalDimensionPosition + 8, 1000*zsize);
  bytes.insert(bytes.end(), data.begin(), data.end());
  return bytes;
}

// little-endian 16-bit ramp 0, 1, 2, ...
Bytes MakeRamp(int count)
{
  Bytes data(2*static_cast<size_t>(count), 0);
  for (int i = 0; i < count; i++)
  {
    data[2*i] = static_cast<char>(i & 0xff);
  }
  return data;
}

bool WriteFile(const std::string& path, const Bytes& bytes)
{
  std::ofstream out(path.c_str(), std::ios::out | std::ios::binary);
  if (!bytes.empty())
  {
    out.write(&bytes[0], static_cast<std::streamsize>(bytes.size()));
  }
  out.close();
  return out.good();
}

// Read the file and return the reader, the caller checks the error code.
vtkSmartPointer<vtkScancoCTReader> ReadFile(
  const std::string& path, const Bytes& bytes)
{
  vtkSmartPointer<vtkScancoCTReader> reader =
    vtkSmartPointer<vtkScancoCTReader>::New();
  if (WriteFile(path, bytes))
  {
    reader->SetFileName(path.c_str());
    reader->Update();
  }
  return reader;
}

bool ReadFails(const std::string& path, const Bytes& bytes)
{
  vtkSmartPointer<vtkScancoCTReader> reader = ReadFile(path, bytes);
  return (reader->GetFileName() != nullptr &&
          reader->GetErrorCode() != vtkErrorCode::NoError);
}

bool ReadSucceeds(vtkScancoCTReader *reader)
{
  return (reader->GetFileName() != nullptr &&
          reader->GetErrorCode() == vtkErrorCode::NoError);
}

int Voxel(vtkScancoCTReader *reader, int x, int y, int z)
{
  return static_cast<int>(
    reader->GetOutput()->GetScalarComponentAsDouble(x, y, z, 0));
}

} // end anonymous namespace

int TestScancoCTReader(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestScancoCTReader");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  // use the temporary directory if the test driver provides one
  std::string tempdir = ".";
  for (int argi = 1; argi + 1 < argc; argi++)
  {
    if (strcmp(argv[argi], "-T") == 0)
    {
      tempdir = argv[argi + 1];
    }
  }
  const std::string aim = tempdir + "/TestScancoCTReader.aim";
  const std::string isq = tempdir + "/TestScancoCTReader.isq";

  // the malformed files below are expected to produce error messages
  vtkObject::GlobalWarningDisplayOff();

  { // well-formed uncompressed AIM and ISQ
  vtkSmartPointer<vtkScancoCTReader> reader =
    ReadFile(aim, MakeAIM(AIMShort, 4, 3, 2, MakeRamp(24)));
  TestAssert(ReadSucceeds(reader));
  TestAssert(Voxel(reader, 0, 0, 0) == 0);
  TestAssert(Voxel(reader, 3, 2, 1) == 23);

  reader = ReadFile(isq, MakeISQ(4, 3, 2, MakeRamp(24)));
  TestAssert(ReadSucceeds(reader));
  TestAssert(Voxel(reader, 3, 2, 1) == 23);
  }

  { // AIM header lengths that do not fit the file
  Bytes good = MakeAIM(AIMShort, 4, 3, 2, MakeRamp(24));
  const int badLog[] = { -1, -160, 0x7fffffff };
  for (size_t i = 0; i < sizeof(badLog)/sizeof(badLog[0]); i++)
  {
    Bytes bad = good;
    PutInt(bad, AIMLogLengthPosition, badLog[i]);
    TestAssert(ReadFails(aim, bad));
  }

  Bytes good030 = MakeAIMV030(Bytes(64, 0));
  const int badSize[] = { -1, -1000000, 0, 8, 0x7fffffff };
  for (size_t i = 0; i < sizeof(badSize)/sizeof(badSize[0]); i++)
  {
    for (size_t field = 0; field < 3; field++)
    {
      if (field == 2 && badSize[i] >= 0 && badSize[i] <= 8)
      {
        continue; // a short processing log is valid
      }
      Bytes bad = good030;
      PutInt(bad, AIMV030VersionSize + 8*field, badSize[i]);
      TestAssert(ReadFails(aim, bad));
    }
  }
  }

  { // AIM dimensions that are negative, or whose product overflows
  TestAssert(ReadFails(aim, MakeAIM(AIMShort, -4, 4, 4, Bytes(128, 0))));
  TestAssert(ReadFails(aim, MakeAIM(AIMPackedBits, 1 << 23, 1 << 22, 1 << 22,
                                   Bytes(64, 0))));
  }

  { // dimensions that need more data than the file holds
  TestAssert(ReadFails(aim, MakeAIM(AIMShort, 1 << 12, 1 << 12, 1 << 12,
                                   Bytes(64, 0))));
  TestAssert(ReadFails(aim, MakeAIM(AIMPackedBits, 1 << 12, 1 << 12, 1 << 12,
                                   Bytes(64, 0))));
  TestAssert(ReadFails(aim, MakeAIM(AIMRunLengthBits, 1 << 12, 1 << 12,
                                   1 << 12, Bytes(64, 0))));
  TestAssert(ReadFails(isq, MakeISQ(1 << 12, 1 << 12, 1 << 12, MakeRamp(24))));
  TestAssert(ReadFails(isq, MakeISQ(1 << 20, 1 << 20, 1 << 20, MakeRamp(24))));
  Bytes truncated = MakeISQ(4, 3, 2, MakeRamp(24));
  truncated.pop_back();
  TestAssert(ReadFails(isq, truncated));
  }

  { // run-length bits: the size, the two voxel values, then run lengths
  Bytes data;
  AppendInt(data, 8);
  const char runs[] = { 1, 2, 10, 54 };
  data.insert(data.end(), runs, runs + 4);
  vtkSmartPointer<vtkScancoCTReader> reader =
    ReadFile(aim, MakeAIM(AIMRunLengthBits, 4, 4, 4, data));
  TestAssert(ReadSucceeds(reader));
  for (int i = 0; i < 64 && ReadSucceeds(reader); i++)
  {
    TestAssert(Voxel(reader, i % 4, (i / 4) % 4, i / 16) == (i < 10 ? 1 : 2));
  }

  const int badSize[] = { 0, 3, 4, 5, 1 << 30, -1 };
  for (size_t i = 0; i < sizeof(badSize)/sizeof(badSize[0]); i++)
  {
    Bytes bad;
    AppendInt(bad, badSize[i]);
    bad.push_back(1);
    TestAssert(ReadFails(aim, MakeAIM(AIMRunLengthBits, 4, 4, 4, bad)));
  }
  }

  { // run-length char: the size, then (run length, value) pairs
  Bytes data;
  AppendInt(data, 8);
  const char runs[] = { 10, 3, 54, 4 };
  data.insert(data.end(), runs, runs + 4);
  vtkSmartPointer<vtkScancoCTReader> reader =
    ReadFile(aim, MakeAIM(AIMRunLengthChar, 4, 4, 4, data));
  TestAssert(ReadSucceeds(reader));
  for (int i = 0; i < 64 && ReadSucceeds(reader); i++)
  {
    TestAssert(Voxel(reader, i % 4, (i / 4) % 4, i / 16) == (i < 10 ? 3 : 4));
  }

  const int badSize[] = { 0, 3, 1 << 30, -1 };
  for (size_t i = 0; i < sizeof(badSize)/sizeof(badSize[0]); i++)
  {
    Bytes bad;
    AppendInt(bad, badSize[i]);
    TestAssert(ReadFails(aim, MakeAIM(AIMRunLengthChar, 4, 4, 4, bad)));
  }
  }

  { // packed bits: each byte holds a 2x2x2 block of voxels, and the bit
    // for a voxel is (x & 1) | ((y & 1) << 1) | ((z & 1) << 2)
  const int sizes[2][3] = { { 4, 4, 4 }, { 3, 5, 7 } };
  for (int n = 0; n < 2; n++)
  {
    const int xsize = sizes[n][0];
    const int ysize = sizes[n][1];
    const int zsize = sizes[n][2];
    const size_t xinc = (xsize + 1)/2;
    const size_t yinc = (ysize + 1)/2;
    const size_t zinc = (zsize + 1)/2;
    // a trailing zero byte selects 0x7f as the value for set voxels
    Bytes packed(xinc*yinc*zinc + 1, 0);
    for (int z = 0; z < zsize; z++)
    {
      for (int y = 0; y < ysize; y++)
      {
        for (int x = 0; x < xsize; x++)
        {
          if ((x*7 + y*3 + z*5) % 3 == 0)
          {
            const size_t i = ((z/2)*yinc + (y/2))*xinc + (x/2);
            const int bit = (x & 1) | ((y & 1) << 1) | ((z & 1) << 2);
            packed[i] = static_cast<char>(packed[i] | (1 << bit));
          }
        }
      }
    }
    vtkSmartPointer<vtkScancoCTReader> reader =
      ReadFile(aim, MakeAIM(AIMPackedBits, xsize, ysize, zsize, packed));
    TestAssert(ReadSucceeds(reader));
    for (int z = 0; z < zsize && ReadSucceeds(reader); z++)
    {
      for (int y = 0; y < ysize; y++)
      {
        for (int x = 0; x < xsize; x++)
        {
          const int expected = ((x*7 + y*3 + z*5) % 3 == 0 ? 0x7f : 0);
          TestAssert(Voxel(reader, x, y, z) == expected);
        }
      }
    }

    packed.pop_back();
    TestAssert(ReadFails(aim, MakeAIM(AIMPackedBits, xsize, ysize, zsize,
                                     packed)));
  }
  }

  { // ISQ data offsets outside the file
  Bytes good = MakeISQ(4, 3, 2, MakeRamp(24));
  const int badOffset[] = { -2, 4, 0x7fffffff };
  for (size_t i = 0; i < sizeof(badOffset)/sizeof(badOffset[0]); i++)
  {
    Bytes bad = good;
    PutInt(bad, ISQDataOffsetPosition, badOffset[i]);
    TestAssert(ReadFails(isq, bad));
  }
  }

  remove(aim.c_str());
  remove(isq.c_str());

  return rval;
}

#ifdef VTK_DICOM_SEPARATE_TESTS
int main(int argc, char *argv[])
{
  return TestScancoCTReader(argc, argv);
}
#endif
