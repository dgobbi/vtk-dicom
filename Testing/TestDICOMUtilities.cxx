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

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMVM");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  typedef vtkDICOMUtilities DU;

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
  TestAssert(l == 1405006735874905);
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
