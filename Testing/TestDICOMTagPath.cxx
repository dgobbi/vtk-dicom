#include "vtkDICOMTagPath.h"

#include <sstream>

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

int TestDICOMTagPath(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMTagPath");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  { // Test default constructor.
  vtkDICOMTagPath tp;
  TestAssert(tp.GetHead() == vtkDICOMTag());
  TestAssert(!tp.HasTail());
  }

  { // Test tag constructor.
  vtkDICOMTagPath tp(vtkDICOMTag(0x7FEE,0x0010));
  TestAssert(tp.GetHead() == vtkDICOMTag(0x7FEE,0x0010));
  TestAssert(!tp.HasTail());
  }

  { // Test two tag constructor.
  vtkDICOMTagPath tp(vtkDICOMTag(0x0018,0x0034), 5,
                     vtkDICOMTag(0x7FEE,0x0010));
  TestAssert(tp.GetHead() == vtkDICOMTag(0x0018,0x0034));
  TestAssert(tp.HasTail());
  TestAssert(tp.GetIndex() == 5);
  TestAssert(tp.GetTail().GetHead() == vtkDICOMTag(0x7FEE,0x0010));
  TestAssert(!tp.GetTail().HasTail());
  }

  { // Test three tag constructor.
  vtkDICOMTagPath tp(vtkDICOMTag(0x0008,0x1115), 1,
                     vtkDICOMTag(0x0008,0x1140), 0,
                     vtkDICOMTag(0x0008,0x1150));
  TestAssert(tp.GetHead() == vtkDICOMTag(0x0008,0x1115));
  TestAssert(tp.HasTail());
  TestAssert(tp.GetIndex() == 1);
  TestAssert(tp.GetTail().GetHead() == vtkDICOMTag(0x0008,0x1140));
  TestAssert(tp.GetTail().HasTail());
  TestAssert(tp.GetTail().GetTail().GetHead() == vtkDICOMTag(0x0008,0x1150));
  TestAssert(!tp.GetTail().GetTail().HasTail());
  }

  { // Test append constructor.
  vtkDICOMTagPath tp(vtkDICOMTag(0x0008,0x1120), 1,
                     vtkDICOMTag(0x0008,0x1125), 0,
                     vtkDICOMTag(0x0008,0x1115));
  vtkDICOMTagPath tp2(tp, 5, vtkDICOMTag(0x0008,0x1150));
  vtkDICOMTagPath tp3(vtkDICOMTag(0x0008,0x1125), 0,
                      vtkDICOMTag(0x0008,0x1115), 5,
                      vtkDICOMTag(0x0008,0x1150));
  TestAssert(tp.GetHead() == vtkDICOMTag(0x0008,0x1120));
  TestAssert(tp.HasTail());
  TestAssert(tp.GetIndex() == 1);
  TestAssert(tp2.GetTail() == tp3);
  }

  return rval;
}

#ifdef VTK_DICOM_SEPARATE_TESTS
int main(int argc, char *argv[])
{
  return TestDICOMTagPath(argc, argv);
}
#endif
