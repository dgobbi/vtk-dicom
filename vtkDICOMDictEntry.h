#ifndef __vtkDICOMDictEntry_h
#define __vtkDICOMDictEntry_h

#include "vtkDICOMVR.h"
#include "vtkDICOMVM.h"
#include "vtkDICOMTag.h"

//! An entry in the DICOM dictionary.
class vtkDICOMDictEntry
{
public:

  // The struct that actually stores the vtkDICOMDictEntry information.
  struct Internal
  {
    unsigned short Group;
    unsigned short Element;
    unsigned char  Owner;
    unsigned char  VR;
    unsigned short VM;
    const char *Name;
  };

  vtkDICOMDictEntry() : I(0) {}

  vtkDICOMTag GetTag() {
    return vtkDICOMTag(this->I->Group, this->I->Element); }
  vtkDICOMVR GetVR() {
    return vtkDICOMVR(static_cast<vtkDICOMVR::EnumType>(this->I->VR)); }
  vtkDICOMVM GetVM() {
    return vtkDICOMVM(static_cast<vtkDICOMVM::EnumType>(this->I->VM)); }
  const char *GetName() {
    return this->I->Name; }
  bool IsRetired() {
    return (this->I->Owner == 1); }

private:
  vtkDICOMDictEntry(Internal *o) : I(o) {}
  friend class vtkDICOMMetaData;
  friend ostream& operator<<(ostream& o, vtkDICOMDictEntry a);

  Internal *I;
};

ostream& operator<<(ostream& o, vtkDICOMDictEntry a);

#endif /* __vtkDICOMDictEntry_h */
