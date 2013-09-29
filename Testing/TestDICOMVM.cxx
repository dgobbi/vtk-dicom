#include "vtkDICOMVM.h"
#include "vtkDICOMValue.h"

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

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMVM");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  { // Test default constructor.
  vtkDICOMVM vm;
  TestAssert(!vm.IsValid());
  }

  { // Test the individual VMs
  vtkDICOMVM vmM1(vtkDICOMVM::M1);
  TestAssert(vmM1 == vtkDICOMVM::M1);
  TestAssert(vmM1.GetMin() == 1);
  TestAssert(vmM1.GetMax() == 1);
  TestAssert(vmM1.GetStep() == 1);

  vtkDICOMVM vmM1T2(vtkDICOMVM::M1T2);
  TestAssert(vmM1T2 == vtkDICOMVM::M1T2);
  TestAssert(vmM1T2.GetMin() == 1);
  TestAssert(vmM1T2.GetMax() == 2);
  TestAssert(vmM1T2.GetStep() == 1);

  vtkDICOMVM vmM1T3(vtkDICOMVM::M1T3);
  TestAssert(vmM1T3 == vtkDICOMVM::M1T3);
  TestAssert(vmM1T3.GetMin() == 1);
  TestAssert(vmM1T3.GetMax() == 3);
  TestAssert(vmM1T3.GetStep() == 1);

  vtkDICOMVM vmM1T32(vtkDICOMVM::M1T32);
  TestAssert(vmM1T32 == vtkDICOMVM::M1T32);
  TestAssert(vmM1T32.GetMin() == 1);
  TestAssert(vmM1T32.GetMax() == 32);
  TestAssert(vmM1T32.GetStep() == 1);

  vtkDICOMVM vmM1T99(vtkDICOMVM::M1T99);
  TestAssert(vmM1T99 == vtkDICOMVM::M1T99);
  TestAssert(vmM1T99.GetMin() == 1);
  TestAssert(vmM1T99.GetMax() == 99);
  TestAssert(vmM1T99.GetStep() == 1);

  vtkDICOMVM vmM1TN(vtkDICOMVM::M1TN);
  TestAssert(vmM1TN == vtkDICOMVM::M1TN);
  TestAssert(vmM1TN.GetMin() == 1);
  TestAssert(vmM1TN.GetMax() == -1);
  TestAssert(vmM1TN.GetStep() == 1);

  vtkDICOMVM vmM2(vtkDICOMVM::M2);
  TestAssert(vmM2 == vtkDICOMVM::M2);
  TestAssert(vmM2.GetMin() == 2);
  TestAssert(vmM2.GetMax() == 2);
  TestAssert(vmM2.GetStep() == 1);

  vtkDICOMVM vmM2T2N(vtkDICOMVM::M2T2N);
  TestAssert(vmM2T2N == vtkDICOMVM::M2T2N);
  TestAssert(vmM2T2N.GetMin() == 2);
  TestAssert(vmM2T2N.GetMax() == -1);
  TestAssert(vmM2T2N.GetStep() == 2);

  vtkDICOMVM vmM2TN(vtkDICOMVM::M2TN);
  TestAssert(vmM2TN == vtkDICOMVM::M2TN);
  TestAssert(vmM2TN.GetMin() == 2);
  TestAssert(vmM2TN.GetMax() == -1);
  TestAssert(vmM2TN.GetStep() == 1);

  vtkDICOMVM vmM3(vtkDICOMVM::M3);
  TestAssert(vmM3 == vtkDICOMVM::M3);
  TestAssert(vmM3.GetMin() == 3);
  TestAssert(vmM3.GetMax() == 3);
  TestAssert(vmM3.GetStep() == 1);

  vtkDICOMVM vmM3T3N(vtkDICOMVM::M3T3N);
  TestAssert(vmM3T3N == vtkDICOMVM::M3T3N);
  TestAssert(vmM3T3N.GetMin() == 3);
  TestAssert(vmM3T3N.GetMax() == -1);
  TestAssert(vmM3T3N.GetStep() == 3);

  vtkDICOMVM vmM3TN(vtkDICOMVM::M3TN);
  TestAssert(vmM3TN == vtkDICOMVM::M3TN);
  TestAssert(vmM3TN.GetMin() == 3);
  TestAssert(vmM3TN.GetMax() == -1);
  TestAssert(vmM3TN.GetStep() == 1);

  vtkDICOMVM vmM4(vtkDICOMVM::M4);
  TestAssert(vmM4 == vtkDICOMVM::M4);
  TestAssert(vmM4.GetMin() == 4);
  TestAssert(vmM4.GetMax() == 4);
  TestAssert(vmM4.GetStep() == 1);

  vtkDICOMVM vmM5(vtkDICOMVM::M5);
  TestAssert(vmM5 == vtkDICOMVM::M5);
  TestAssert(vmM5.GetMin() == 5);
  TestAssert(vmM5.GetMax() == 5);
  TestAssert(vmM5.GetStep() == 1);

  vtkDICOMVM vmM6(vtkDICOMVM::M6);
  TestAssert(vmM6 == vtkDICOMVM::M6);
  TestAssert(vmM6.GetMin() == 6);
  TestAssert(vmM6.GetMax() == 6);
  TestAssert(vmM6.GetStep() == 1);

  vtkDICOMVM vmM6TN(vtkDICOMVM::M6TN);
  TestAssert(vmM6TN == vtkDICOMVM::M6TN);
  TestAssert(vmM6TN.GetMin() == 6);
  TestAssert(vmM6TN.GetMax() == -1);
  TestAssert(vmM6TN.GetStep() == 1);

  vtkDICOMVM vmM8(vtkDICOMVM::M8);
  TestAssert(vmM8 == vtkDICOMVM::M8);
  TestAssert(vmM8.GetMin() == 8);
  TestAssert(vmM8.GetMax() == 8);
  TestAssert(vmM8.GetStep() == 1);

  vtkDICOMVM vmM9(vtkDICOMVM::M9);
  TestAssert(vmM9 == vtkDICOMVM::M9);
  TestAssert(vmM9.GetMin() == 9);
  TestAssert(vmM9.GetMax() == 9);
  TestAssert(vmM9.GetStep() == 1);

  vtkDICOMVM vmM16(vtkDICOMVM::M16);
  TestAssert(vmM16 == vtkDICOMVM::M16);
  TestAssert(vmM16.GetMin() == 16);
  TestAssert(vmM16.GetMax() == 16);
  TestAssert(vmM16.GetStep() == 1);

  vtkDICOMVM vmM24(vtkDICOMVM::M24);
  TestAssert(vmM24 == vtkDICOMVM::M24);
  TestAssert(vmM24.GetMin() == 24);
  TestAssert(vmM24.GetMax() == 24);
  TestAssert(vmM24.GetStep() == 1);

  vtkDICOMVM vmM256(vtkDICOMVM::M256);
  TestAssert(vmM256 == vtkDICOMVM::M256);
  TestAssert(vmM256.GetMin() == 256);
  TestAssert(vmM256.GetMax() == 256);
  TestAssert(vmM256.GetStep() == 1);
  }

  return rval;
}
