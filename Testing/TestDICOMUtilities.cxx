#include "vtkDICOMUtilities.h"
#include "vtkDICOMDictionary.h"

#include "vtkStringArray.h"
#include "vtkSmartPointer.h"

#include <sstream>
#include <algorithm>
#include <string>

#include <string.h>
#include <stdlib.h>

// macro for performing tests
#define TestAssert(t) \
if (!(t)) \
{ \
  cout << exename << ": Assertion Failed: " << #t << "\n"; \
  cout << __FILE__ << ":" << __LINE__ << "\n"; \
  cout.flush(); \
  rval |= 1; \
}

#ifdef VTK_IN_VTK
int TestDICOMUtilities(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMVM");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  typedef vtkDICOMUtilities DU;

  { // Test comparison of UIDs
  const char *uid1 = "1.2.840.113619.2.334";
  const char *uid2 = "1.2.840.113619.2.334.3";
  const char *uid3 = "1.2.840.113619.2.334.4";
  const char *uid4 = "1.2.840.113619.2.334.12";
  TestAssert(DU::CompareUIDs(uid1, uid1) == 0);
  TestAssert(DU::CompareUIDs(uid1, uid2) == -1);
  TestAssert(DU::CompareUIDs(uid2, uid3) == -1);
  TestAssert(DU::CompareUIDs(uid3, uid4) == -1);
  TestAssert(DU::CompareUIDs(uid2, uid1) == 1);
  TestAssert(DU::CompareUIDs(uid3, uid2) == 1);
  TestAssert(DU::CompareUIDs(uid4, uid3) == 1);
  }

  { // Test UID generation with 2.25 prefix
  std::string uid = DU::GenerateUID(DC::FrameOfReferenceUID);
  TestAssert(strncmp(uid.data(), "2.25.", 5) == 0);
  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();
  a->SetNumberOfValues(10);
  DU::GenerateUIDs(DC::SeriesInstanceUID, a);
  for (int i = 0; i < 9; i++)
  {
    TestAssert(DU::CompareUIDs(a->GetValue(i), a->GetValue(i+1)) < 0);
  }
  }

  { // Test UID generation with given prefix
  DU::SetUIDPrefix("1.2.840.10008.");
  std::string uid = DU::GenerateUID(DC::FrameOfReferenceUID);
  TestAssert(strncmp(uid.data(), "1.2.840.10008.", 14) == 0);
  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();
  a->SetNumberOfValues(10);
  DU::GenerateUIDs(DC::SeriesInstanceUID, a);
  for (int i = 0; i < 9; i++)
  {
    TestAssert(DU::CompareUIDs(a->GetValue(i), a->GetValue(i+1)) < 0);
  }
  }

  { // Test DateTime generation
  std::string s = DU::GenerateDateTime("-0600");
  long long l = DU::ConvertDateTime(s.c_str());
  std::string t = DU::GenerateDateTime(l, "-0600");
  TestAssert(s == t);
  s = DU::GenerateDateTime(0);
  l = DU::ConvertDateTime(s.c_str());
  t = DU::GenerateDateTime(l, 0);
  TestAssert(s == t);
  s = "20140710093855.874905-0600";
  l = DU::ConvertDateTime(s.c_str());
  TestAssert(l == 1405006735874905ll);
  }

  { // Test DateTime handling of DST boundaries
  const char *times[4] = {
    "20170312015959.999999",
    "20170312030000.000000",
    "20171105015959.999999",
    "20171105020000.000000",
  };
  for (int i = 0; i < 4; i++)
  {
    long long l = DU::ConvertDateTime(times[i]);
    std::string t = DU::GenerateDateTime(l, 0);
    TestAssert(t.compare(0, 21, times[i]) == 0);
  }
  }

  { // Test packing/unpacking
  static const unsigned char t[4] = { 166, 95, 230, 93 };
  unsigned char u[4];
  unsigned int v = 1575378854;
  TestAssert(DU::UnpackUnsignedInt(t) == v);
  DU::PackUnsignedInt(v, u);
  TestAssert(u[0] == t[0] && u[1] == t[1] && u[2] == t[2] && u[3] == t[3]);
  }

  return rval;
}
