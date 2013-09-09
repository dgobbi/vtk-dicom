/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMDataElement_h
#define __vtkDICOMDataElement_h

#include "vtkDICOMModule.h"
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
class VTK_DICOM_EXPORT vtkDICOMDataElement
{
public:
  vtkDICOMDataElement() : Tag(), Value(), Next(0), Prev(0) {}
  vtkDICOMDataElement(const vtkDICOMTag& t, const vtkDICOMValue &v) :
    Tag(t), Value(v), Next(0), Prev(0) {}

  //! Get the tag for this data element.
  vtkDICOMTag GetTag() const { return this->Tag; }

  //! Get the VR for this data element.
  vtkDICOMVR GetVR() const { return this->Value.GetVR(); }

  //! Check whether this data element carries per-instance values.
  bool IsPerInstance() const { return (this->Value.GetMultiplexData() != 0); }

  //! Get the number of value instances in this data element.
  int GetNumberOfInstances() const { return this->Value.GetNumberOfValues(); }

  //! Get the value of the data element, if not multi-valued.
  const vtkDICOMValue& GetValue() const { return this->Value; }

  //! Get value instance i, if the data element is multi-valued.
  const vtkDICOMValue& GetValue(int i) const {
    const vtkDICOMValue *vptr = this->Value.GetMultiplexData();
    return (vptr == 0 ? this->Value : vptr[i]); }

  bool operator==(const vtkDICOMDataElement& o) const {
    return (this->Tag == o.Tag && this->Value == o.Value); }

  bool operator!=(const vtkDICOMDataElement& o) const {
    return (this->Tag != o.Tag || this->Value != o.Value); }

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
class VTK_DICOM_EXPORT vtkDICOMDataElementIterator
{
public:
  vtkDICOMDataElementIterator() : Pointer(0) {}

  vtkDICOMDataElementIterator& operator++() {
    if (this->Pointer) { this->Pointer = this->Pointer->Next; }
    return *this; }

  vtkDICOMDataElementIterator operator++(int) {
    const vtkDICOMDataElement *ptr = this->Pointer;
    if (ptr) { this->Pointer = this->Pointer->Next; }
    return vtkDICOMDataElementIterator(ptr); }

  vtkDICOMDataElementIterator& operator--() {
    if (this->Pointer) { this->Pointer = this->Pointer->Prev; }
    return *this; }

  vtkDICOMDataElementIterator operator--(int) {
    const vtkDICOMDataElement *ptr = this->Pointer;
    if (ptr) { this->Pointer = this->Pointer->Prev; }
    return vtkDICOMDataElementIterator(ptr); }

  const vtkDICOMDataElement *operator->() const { return this->Pointer; }
  const vtkDICOMDataElement& operator*() const { return *this->Pointer; }

  bool operator==(const vtkDICOMDataElementIterator& it) const {
    return (this->Pointer == it.Pointer); }

  bool operator!=(const vtkDICOMDataElementIterator& it) const {
    return (this->Pointer != it.Pointer); }

private:
  vtkDICOMDataElementIterator(const vtkDICOMDataElement *ptr) {
    this->Pointer = ptr; }

  const vtkDICOMDataElement *Pointer;

  friend class vtkDICOMMetaData;
  friend class vtkDICOMItem;
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& os, const vtkDICOMDataElement& v);

#endif /* __vtkDICOMDataElement_h */
