#include "vtkDICOMDictionary.h"
#include "vtkDICOMDictEntry.h"

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

#ifdef VTK_IN_VTK
int TestDICOMDictionary(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMDictionary");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  // test a valid entry
  vtkDICOMDictEntry e = vtkDICOMDictionary::FindDictEntry(DC::Modality);
  std::string name = "Modality";
  TestAssert(e.IsValid());
  TestAssert(e.GetTag() == DC::Modality);
  TestAssert(e.GetVR() == vtkDICOMVR::CS);
  TestAssert(e.GetVM() == vtkDICOMVM::M1);
  TestAssert(name == e.GetName());
  TestAssert(e.IsRetired() == 0);

  // test lookup via string
  e = vtkDICOMDictionary::FindDictEntry(name.c_str());
  TestAssert(e.IsValid());
  TestAssert(e.GetTag() == DC::Modality);
  TestAssert(e.GetVR() == vtkDICOMVR::CS);
  TestAssert(e.GetVM() == vtkDICOMVM::M1);
  TestAssert(name == e.GetName());
  TestAssert(e.IsRetired() == 0);

  // test an invalid entry
  e = vtkDICOMDictionary::FindDictEntry(vtkDICOMTag(0x0002,0xFFFF));
  TestAssert(!e.IsValid());
  e = vtkDICOMDictionary::FindDictEntry("Wombat");
  TestAssert(!e.IsValid());
  e = vtkDICOMDictionary::FindDictEntry("");
  TestAssert(!e.IsValid());
  e = vtkDICOMDictEntry();
  TestAssert(!e.IsValid());

  // test private dictionary
  vtkDICOMTag ptag(0x0019,0x0004);
  std::string pkey = "CellSpacing";
  e = vtkDICOMDictionary::FindDictEntry(ptag, "GEMS_ACQU_01");
  TestAssert(e.IsValid());
  TestAssert(e.GetTag() == ptag);
  TestAssert(e.GetVR() == vtkDICOMVR::DS);
  TestAssert(e.GetVM() == vtkDICOMVM::M1);
  TestAssert(pkey == e.GetName());
  e = vtkDICOMDictionary::FindDictEntry(pkey.c_str(), "GEMS_ACQU_01");
  TestAssert(e.IsValid());
  TestAssert(e.GetTag() == ptag);
  TestAssert(e.GetVR() == vtkDICOMVR::DS);
  TestAssert(e.GetVM() == vtkDICOMVM::M1);
  TestAssert(pkey == e.GetName());
  e = vtkDICOMDictionary::FindDictEntry("", "GEMS_ACQU_01");
  TestAssert(!e.IsValid());

  return rval;
}
