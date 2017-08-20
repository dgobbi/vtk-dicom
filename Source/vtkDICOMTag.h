/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMTag_h
#define vtkDICOMTag_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMDictHash.h"

//! A (group,element) identifier tag for DICOM attributes.
class VTKDICOM_EXPORT vtkDICOMTag
{
public:
  //! A struct that provides static storage for a DICOM tag.
  struct StaticTag
  {
    unsigned int Key;
  };

  //@{
  vtkDICOMTag() : Key(0) {}

  //! Construct a tag from group, element numbers.
  vtkDICOMTag(int group, int element) : Key((group << 16) | element) {}

  //! Construct a tag from an identifier from the DICOM dictionary.
  vtkDICOMTag(DC::EnumType tag) : Key(tag) {}

  //! Construct a tag object from a static tag.
  vtkDICOMTag(StaticTag tag) : Key(tag.Key) {}
  //@}

  //@{
  //! Get the 16-bit group identifier.
  unsigned short GetGroup() const {
    return static_cast<unsigned short>(this->Key >> 16); }

  //! Get the 16-bit element identifier.
  unsigned short GetElement() const {
    return static_cast<unsigned short>(this->Key); }
  //@}

  //@{
  //! Get the tag as a 32-bit key.
  unsigned int GetKey() const {
    return this->Key; }

  //! Compute a hash value, used for accelerating lookups.
  unsigned int ComputeHash() const {
    unsigned int h = (((this->Key >> 6) & 0x03FF03FF) ^ this->Key);
    return (h ^ (h << 16)) >> 16; }
  //@}

  //@{
  bool operator==(const vtkDICOMTag& b) const {
    return (this->Key == b.Key); }

  bool operator!=(const vtkDICOMTag& b) const {
    return (this->Key != b.Key); }

  bool operator<=(const vtkDICOMTag& b) const {
    return (this->Key <= b.Key); }

  bool operator>=(const vtkDICOMTag& b) const {
    return (this->Key >= b.Key); }

  bool operator<(const vtkDICOMTag& b) const {
    return (this->Key < b.Key); }

  bool operator>(const vtkDICOMTag& b) const {
    return (this->Key > b.Key); }
  //@}

private:
  unsigned int Key;
};

VTKDICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMTag& a);

#endif /* vtkDICOMTag_h */
// VTK-HeaderTest-Exclude: vtkDICOMTag.h
