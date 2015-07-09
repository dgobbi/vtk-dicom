#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMDictionary.h"
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

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMSequence");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  vtkDICOMMetaData *meta = vtkDICOMMetaData::New();

  // test the constructors
  {
    // default constructor
    vtkDICOMItem i;
    meta->SetAttributeValue(DC::ConceptNameCodeSequence, i);
    // try accessing it and removing it
    meta->GetAttributeValue(
      vtkDICOMTagPath(DC::ConceptNameCodeSequence, 0, DC::CodeMeaning));
    meta->RemoveAttribute(DC::ConceptNameCodeSequence);
  }
  {
    // low-level constructor (not for general use)
    vtkDICOMItem i(vtkDICOMCharacterSet::ISO_IR_101, vtkDICOMVR::US);
    i.SetAttributeValue(DC::CodeMeaning, "Whatever");
    vtkDICOMCharacterSet cs = i.GetAttributeValue(DC::CodeMeaning).GetCharacterSet(); 
    TestAssert(cs == vtkDICOMCharacterSet::ISO_IR_101);
    // check the pixel representation (the VRForXS)
    i.SetAttributeValue(DC::MappedPixelValue, 10);
    TestAssert(i.GetAttributeValue(DC::MappedPixelValue).GetVR() == vtkDICOMVR::US);
  }
  {
    // construct an item to be placed into a specific meta data object,
    // e.g. assume the same character set, pixel representation as meta data object
    meta->SetAttributeValue(DC::SpecificCharacterSet, "ISO_IR 100");
    meta->SetAttributeValue(DC::PixelRepresentation, 1);
    vtkDICOMItem i = vtkDICOMItem(meta);
    // check that character set was inherited from meta data
    i.SetAttributeValue(DC::CodeMeaning, "Whatever");
    vtkDICOMCharacterSet cs = i.GetAttributeValue(DC::CodeMeaning).GetCharacterSet(); 
    TestAssert(cs == vtkDICOMCharacterSet::ISO_IR_100);
    // check that pixel representation was inherited from meta data
    i.SetAttributeValue(DC::MappedPixelValue, 10);
    TestAssert(i.GetAttributeValue(DC::MappedPixelValue).GetVR() == vtkDICOMVR::SS);
  }

  // test actions on an empty item
  {
    // check basic methods on an empty item
    vtkDICOMItem i;
    TestAssert(i.IsEmpty());
    TestAssert(i.GetNumberOfDataElements() == 0);
    TestAssert(i.Begin() == i.End());
    TestAssert(i.GetByteOffset() == 0); // defaults to zero
    TestAssert(i.IsDelimited() == true); // defaults to true
    TestAssert(i.FindDictEntry(DC::CodeMeaning).IsValid() == true);
    TestAssert(i.FindDictVR(DC::MappedPixelValue) == vtkDICOMVR::US);
    i.Clear(); // does nothing
  }
  { // test private tags functions on empty item
    vtkDICOMItem i;
    vtkDICOMTag ptag(0x0009,0x0011);
    vtkDICOMTag tag = i.ResolvePrivateTag(ptag, "GEMS_ACQU_01");
    TestAssert(tag == vtkDICOMTag(0xFFFF,0xFFFF));
    tag = i.ResolvePrivateTagForWriting(ptag, "GEMS_ACQU_01");
    TestAssert(tag == vtkDICOMTag(0x0009,0x1011));
  }
  {
    // test getting attributes from an empty item
    vtkDICOMItem i;
    TestAssert(i.GetAttributeValue(DC::CodeMeaning).IsValid() == false);
    vtkDICOMTagPath tp1 = vtkDICOMTagPath(DC::CodeMeaning);
    TestAssert(i.GetAttributeValue(tp1).IsValid() == false);
    vtkDICOMTagPath tp2(DC::ConceptNameCodeSequence, 0, DC::CodeMeaning);
    TestAssert(i.GetAttributeValue(tp2).IsValid() == false);
  }
  {
    // test setting attributes from an empty item
    vtkDICOMItem i;
    vtkDICOMTagPath tp2(DC::ConceptNameCodeSequence, 0, DC::CodeMeaning);
    i.SetAttributeValue(tp2, "Whatever");
    TestAssert(i.GetAttributeValue(tp2).IsValid() == true);
    i.Clear();
    vtkDICOMTagPath tp1 = vtkDICOMTagPath(DC::CodeMeaning);
    i.SetAttributeValue(tp1, "Whatever");
    TestAssert(i.GetAttributeValue(tp1).IsValid() == true);
    i.Clear();
    i.SetAttributeValue(DC::CodeMeaning, "Whatever");
    TestAssert(i.GetAttributeValue(DC::CodeMeaning).IsValid() == true);
    i.Clear();
    vtkDICOMTagPath tp3(DC::CodeMeaning, 0, DC::CodeMeaning); // invalid path!
    i.SetAttributeValue(tp3, "Whatever");
    TestAssert(i.GetAttributeValue(tp3).IsValid() == false);
  }
  {
    // check lookup of character set for VRs that use it (will be ASCII)
    vtkDICOMItem i;
    i.SetAttributeValue(DC::CodeMeaning, "Hello");
    vtkDICOMCharacterSet cs = i.GetAttributeValue(DC::CodeMeaning).GetCharacterSet(); 
    TestAssert(cs == vtkDICOMCharacterSet::ISO_IR_6);
  }
  {
    // check lookup of XS being SS vs US (will be US)
    vtkDICOMItem i;
    i.SetAttributeValue(DC::MappedPixelValue, 10);
    TestAssert(i.GetAttributeValue(DC::MappedPixelValue).GetVR() == vtkDICOMVR::US);
  }
  {
    // check lookup of XS being SS vs US (will be US)
    vtkDICOMItem i;
    i.SetAttributeValue(DC::MappedPixelValue, 10);
    TestAssert(i.GetAttributeValue(DC::MappedPixelValue).GetVR() == vtkDICOMVR::US);
  }

  meta->Delete();
  return rval;
}
