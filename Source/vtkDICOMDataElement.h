/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMDataElement_h
#define vtkDICOMDataElement_h

#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMTag.h"
#include "vtkDICOMValue.h"

//! A data element in a DICOM data set.
/*!
 *  The DataElement contains an encoded attribute value, along
 *  with the tag that identifies the attribute.  The data elements
 *  in a vtkDICOMMetaData object can be per-instance, with a different
 *  value for each data set instance used to build the the meta data
 *  for the image series.
 */
class VTKDICOM_EXPORT vtkDICOMDataElement
{
public:
  //@{
  vtkDICOMDataElement() : Next(nullptr), Prev(nullptr) {}
  vtkDICOMDataElement(const vtkDICOMTag& t, const vtkDICOMValue &v) :
    Tag(t), Value(v), Next(nullptr), Prev(nullptr) {}
  //@}

  //@{
  //! Get the tag for this data element.
  vtkDICOMTag GetTag() const { return this->Tag; }

  //! Get the VR for this data element.
  vtkDICOMVR GetVR() const { return this->Value.GetVR(); }
  //@}

  //@{
  //! Check whether this data element carries per-instance values.
  bool IsPerInstance() const {
    return (this->Value.GetMultiplexData() != nullptr); }

  //! Get the number of value instances in this data element.
  int GetNumberOfInstances() const {
    return static_cast<int>(this->Value.GetNumberOfValues()); }

  //! Get the value of the data element, if not multi-valued.
  const vtkDICOMValue& GetValue() const { return this->Value; }

  //! Get value instance i, if the data element is multi-valued.
  const vtkDICOMValue& GetValue(int i) const {
    const vtkDICOMValue *vptr = this->Value.GetMultiplexData();
    return (vptr == nullptr ? this->Value : vptr[i]); }
  //@}

  //@{
  bool operator==(const vtkDICOMDataElement& o) const {
    return (this->Tag == o.Tag && this->Value == o.Value); }

  bool operator!=(const vtkDICOMDataElement& o) const {
    return (this->Tag != o.Tag || this->Value != o.Value); }
  //@}

private:
  vtkDICOMTag          Tag;
  vtkDICOMValue        Value;

  // for storing elements in a linked list
  vtkDICOMDataElement *Next;
  vtkDICOMDataElement *Prev;

  // the classes that need to manipulate lists of elements
  friend class vtkDICOMDataElementIterator;
  friend class vtkDICOMMetaData;
  friend class vtkDICOMItem;
};

//! A const iterator for a vtkDataElement list.
/*!
 *  An iterator is only valid until the next modification of the data set.
 */
class VTKDICOM_EXPORT vtkDICOMDataElementIterator
{
public:
  //@{
  vtkDICOMDataElementIterator() : Pointer(nullptr) {}
  //@}

  //@{
  vtkDICOMDataElementIterator& operator++() {
    this->Pointer = this->Pointer->Next;
    return *this; }

  vtkDICOMDataElementIterator operator++(int) {
    const vtkDICOMDataElement *ptr = this->Pointer;
    this->Pointer = this->Pointer->Next;
    return vtkDICOMDataElementIterator(ptr); }

  vtkDICOMDataElementIterator& operator--() {
    this->Pointer = this->Pointer->Prev;
    return *this; }

  vtkDICOMDataElementIterator operator--(int) {
    const vtkDICOMDataElement *ptr = this->Pointer;
    this->Pointer = this->Pointer->Prev;
    return vtkDICOMDataElementIterator(ptr); }
  //@}

  //@{
  const vtkDICOMDataElement *operator->() const { return this->Pointer; }
  const vtkDICOMDataElement& operator*() const { return *this->Pointer; }
  //@}

  //@{
  bool operator==(const vtkDICOMDataElementIterator& it) const {
    return (this->Pointer == it.Pointer); }

  bool operator!=(const vtkDICOMDataElementIterator& it) const {
    return (this->Pointer != it.Pointer); }
  //@}

private:
  vtkDICOMDataElementIterator(const vtkDICOMDataElement *ptr) {
    this->Pointer = ptr; }

  const vtkDICOMDataElement *Pointer;

  friend class vtkDICOMMetaData;
  friend class vtkDICOMItem;
};

VTKDICOM_EXPORT ostream& operator<<(ostream& os, const vtkDICOMDataElement& v);

#endif /* vtkDICOMDataElement_h */
// VTK-HeaderTest-Exclude: vtkDICOMDataElement.h
