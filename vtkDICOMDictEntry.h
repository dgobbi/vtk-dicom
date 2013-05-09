#ifndef __vtkDICOMDictEntry_h
#define __vtkDICOMDictEntry_h

#include "vtkDICOMVR.h"
#include "vtkDICOMVM.h"
#include "vtkDICOMTag.h"
#include "vtkDICOMDictionary.h"

//! An entry in the DICOM dictionary.
class vtkDICOMDictEntry
{
public:
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
  vtkDICOMDictEntry(vtkDICOMDictionary::Entry *o) : I(o) {}

  friend class vtkDICOMDictionary;
  friend ostream& operator<<(ostream& o, vtkDICOMDictEntry a);

  vtkDICOMDictionary::Entry *I;
};

ostream& operator<<(ostream& o, vtkDICOMDictEntry a);

#endif /* __vtkDICOMDictEntry_h */
