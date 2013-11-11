/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMItem_h
#define __vtkDICOMItem_h

#include "vtkDICOMModule.h"
#include "vtkDICOMDataElement.h"
#include "vtkDICOMDictEntry.h"
#include "vtkDICOMReferenceCount.h"

#include <string>

class vtkDICOMTagPath;

//! An item in a DICOM sequence (type SQ).
/*!
 *  A DICOM sequence is a list of items, where each item is
 *  essentially a data set of its own.  An item consists of
 *  zero or more data elements, each with a tag and value.
 */
class VTK_DICOM_EXPORT vtkDICOMItem
{
private:

  //! A reference counted list container class.
  struct List
  {
    vtkDICOMDataElement Head;
    vtkDICOMDataElement Tail;
    vtkDICOMReferenceCount ReferenceCount;
    int NumberOfDataElements;
    bool Delimited;

    List() : Head(), Tail(), ReferenceCount(1) {}
  };

public:

  //! Default constructor creates an empty item.
  vtkDICOMItem() : L(0) {}

  //! Constructor with flag for delimited item.
  explicit vtkDICOMItem(int delimited);

  //! Copy constructor does reference counting.
  vtkDICOMItem(const vtkDICOMItem &o) : L(o.L) {
    if (this->L) { ++(this->L->ReferenceCount); } }

  //! Destructor does reference counting.
  ~vtkDICOMItem() { this->Clear(); }

  //! Clear the data.
  void Clear() {
    if (this->L && --(this->L->ReferenceCount) == 0) { this->FreeList(); } }

  //! Check if empty.
  bool IsEmpty() const { return (this->L == 0); }

  //! Check if this was read as a delimited item.
  bool IsDelimited() const {
    return (this->L == 0 || this->L->Delimited != 0); }

  //! Add a data element to this item.
  /*!
   *  This method can only be used before the item has been added
   *  to a sequence.  After the item has become part of a sequence,
   *  it is frozen and cannot be modified.
   */
  void SetAttributeValue(vtkDICOMTag tag, const vtkDICOMValue& v);
  void SetAttributeValue(vtkDICOMTag tag, double v);
  void SetAttributeValue(vtkDICOMTag tag, const std::string& v);

  //! Get a data element from this item.
  const vtkDICOMValue &GetAttributeValue(vtkDICOMTag tag) const;
  const vtkDICOMValue &GetAttributeValue(const vtkDICOMTagPath &tag) const;

  //! Get the number of data elements.
  int GetNumberOfDataElements() const {
    return (this->L ? this->L->NumberOfDataElements : 0); }

  //! Get an iterator for the list of data elements.
  vtkDICOMDataElementIterator Begin() const {
    return (this->L ? this->L->Head.Next : 0); }

  //! Get an end iterator for the list of data elements.
  vtkDICOMDataElementIterator End() const {
    return (this->L ? &this->L->Tail : 0); }

  //! Look up a tag in the DICOM dictionary.
  /*!
   *  Unlike the method in vtkDICOMDictionary, this method can identify
   *  the implementor of a private tag and look it up in the implementor's
   *  dictionary.
   */
  vtkDICOMDictEntry FindDictEntry(vtkDICOMTag tag) const;

  //! Use the dictionary to get the VR, returns UN on failure.
  vtkDICOMVR FindDictVR(vtkDICOMTag tag) const;

  bool operator==(const vtkDICOMItem& o) const;
  bool operator!=(const vtkDICOMItem& o) const {
    return !(*this == o); }

  //! Assignment operator does reference counting.
  vtkDICOMItem &operator=(const vtkDICOMItem &o) {
    if (this->L != o.L) {
      if (o.L) { ++(o.L->ReferenceCount); }
      if (this->L && --(this->L->ReferenceCount) == 0) { this->FreeList(); }
      this->L = o.L; }
    return *this; }

private:
  void FreeList();
  void CopyList(const List *o, List *t);

  //! Internal templated SetAttributeValue method
  template<class T>
  void SetAttributeValueT(vtkDICOMTag tag, T v);

  //! An invalid value, for when one is needed.
  static const vtkDICOMValue InvalidValue;

  //! A linked list to hold the elements.
  List *L;
};

#endif /* __vtkDICOMItem_h */
