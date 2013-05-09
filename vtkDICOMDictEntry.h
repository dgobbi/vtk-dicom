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
  //! Construct an invalid DictEntry object.
  vtkDICOMDictEntry() : I(0) {}

  //! Check whether the returned entry is valid.
  bool IsValid() {
    return (this->I != 0); }

  //! Get the DICOM tag for this dictionary entry.
  vtkDICOMTag GetTag() {
    return (this->I == 0 ? vtkDICOMTag() :
            vtkDICOMTag(this->I->Group, this->I->Element)); }

  //! Get the VR for this dictionary entry.
  vtkDICOMVR GetVR() {
    return (this->I == 0 ? vtkDICOMVR() :
            vtkDICOMVR(static_cast<vtkDICOMVR::EnumType>(this->I->VR))); }

  //! Get the VM for this dictionary entry.
  vtkDICOMVM GetVM() {
    return (this->I == 0 ? vtkDICOMVM() :
            vtkDICOMVM(static_cast<vtkDICOMVM::EnumType>(this->I->VM))); }

  //! Get a human-readable name for this dictionary entry.
  const char *GetName() {
    return (this->I == 0 ? "" : this->I->Name); }

  //! Check whether this entry has been retired from the DICOM standard.
  bool IsRetired() {
    return (this->I == 0 ? false : (this->I->Owner == 1)); }

private:
  vtkDICOMDictEntry(vtkDICOMDictionary::Entry *o) : I(o) {}

  friend class vtkDICOMDictionary;
  friend ostream& operator<<(ostream& o, vtkDICOMDictEntry a);

  vtkDICOMDictionary::Entry *I;
};

ostream& operator<<(ostream& o, vtkDICOMDictEntry a);

#endif /* __vtkDICOMDictEntry_h */
