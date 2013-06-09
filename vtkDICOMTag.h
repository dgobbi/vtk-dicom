/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMTag_h
#define __vtkDICOMTag_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"
#include "vtkDICOMDictHash.h"

//! A (group,element) identifier tag for DICOM attributes.
class VTK_DICOM_EXPORT vtkDICOMTag
{
public:
  //! A POD tag that can be statically initialized.
  struct StaticTag
  {
    unsigned int Key;
  };

  vtkDICOMTag() : Key(0) {}

  //! Construct a tag from group, element numbers.
  vtkDICOMTag(int group, int element) : Key((group << 16) | element) {}

  //! Construct a tag from an identifier from the DICOM dictionary.
  vtkDICOMTag(DC::EnumType tag) : Key(tag) {}

  //! Construct a tag object from a static tag.
  vtkDICOMTag(StaticTag tag) : Key(tag.Key) {}

  //! Get the 16-bit group identifier.
  unsigned short GetGroup() const {
    return static_cast<unsigned short>(this->Key >> 16); }

  //! Get the 16-bit element identifier.
  unsigned short GetElement() const {
    return static_cast<unsigned short>(this->Key); }

  //! Compute a hash value, used for accelerating lookups.
  unsigned int ComputeHash() const {
    unsigned int h = (((this->Key >> 6) & 0xFFFF03FF) ^ this->Key);
    return (h ^ (h >> 16)); }

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

private:
  unsigned int Key;
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMTag& a);

#endif /* __vtkDICOMTag_h */
