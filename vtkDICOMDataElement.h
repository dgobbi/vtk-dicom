#ifndef __vtkDICOMDataElement_h
#define __vtkDICOMDataElement_h

#include "vtkDICOMTag.h"
#include "vtkDICOMValue.h"

//! A data element in a DICOM data set.
/*!
 *  The DataElement contains an encoded attribute value, along
 *  with the tag that identifies the attribute.
 */
class vtkDICOMDataElement
{
public:
  vtkDICOMDataElement() : Tag(), Value(), Next(0), Prev(0) {}
  vtkDICOMDataElement(const vtkDICOMTag& t, const vtkDICOMValue &v) :
    Tag(t), Value(v), Next(0), Prev(0) {}

  vtkDICOMTag GetTag() const { return this->Tag; }
  vtkDICOMVR GetVR() const { return this->Value.GetVR(); }
  unsigned int GetVL() const { return this->Value.GetVL(); }
  const vtkDICOMValue& GetValue() const { return this->Value; }

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
  friend class vtkDICOMSequenceItem;
};

//! A const iterator for a vtkDataElement list.
class vtkDICOMDataElementIterator
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
  vtkDICOMDataElement operator*() const { return *this->Pointer; }

  bool operator==(const vtkDICOMDataElementIterator& it) const {
    return (this->Pointer == it.Pointer); }

  bool operator!=(const vtkDICOMDataElementIterator& it) const {
    return (this->Pointer != it.Pointer); }

private:
  vtkDICOMDataElementIterator(const vtkDICOMDataElement *ptr) {
    this->Pointer = ptr; }

  const vtkDICOMDataElement *Pointer;

  friend class vtkDICOMMetaData;
  friend class vtkDICOMSequenceItem;
};

ostream& operator<<(ostream& os, const vtkDICOMDataElement& v);

#endif /* __vtkDICOMDataElement_h */
