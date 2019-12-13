/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMDictEntry_h
#define vtkDICOMDictEntry_h

#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMVR.h"
#include "vtkDICOMVM.h"
#include "vtkDICOMTag.h"

//! An entry in the DICOM dictionary.
class VTKDICOM_EXPORT vtkDICOMDictEntry
{
public:
  //! A struct to statically store DICOM dictionary entries.
  struct Entry
  {
    vtkDICOMTag::StaticTag Tag;
    unsigned char  Flags;
    unsigned char  VR;
    unsigned short VM;
    const char    *Name;
  };

  //! Construct an invalid DictEntry object.
  vtkDICOMDictEntry() : I(&InvalidEntry) {}

  //! Check whether the returned entry is valid.
  bool IsValid() const {
    return (this->I != &InvalidEntry); }

  //! Get the DICOM tag for this dictionary entry.
  vtkDICOMTag GetTag() const {
    return vtkDICOMTag(this->I->Tag); }

  //! Get the VR for this dictionary entry.
  vtkDICOMVR GetVR() const {
    return vtkDICOMVR(static_cast<vtkDICOMVR::EnumType>(this->I->VR)); }

  //! Get the VM for this dictionary entry.
  vtkDICOMVM GetVM() const {
    return vtkDICOMVM(static_cast<vtkDICOMVM::EnumType>(this->I->VM)); }

  //! Get a human-readable name for this dictionary entry.
  const char *GetName() const {
    return this->I->Name; }

  //! Check whether this entry has been retired from the DICOM standard.
  bool IsRetired() const {
    return (this->I->Flags == 1); }

private:
  vtkDICOMDictEntry(const Entry *o) : I(o) {}

  friend class vtkDICOMDictionary;

  const Entry *I;

  static const Entry InvalidEntry;
};

VTKDICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMDictEntry& a);

#endif /* vtkDICOMDictEntry_h */
// VTK-HeaderTest-Exclude: vtkDICOMDictEntry.h
