/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

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
    vtkDICOMDataElement *DataElements;
    unsigned int ByteOffset;
    bool Delimited;

    List() : Head(), Tail(), ReferenceCount(1),
             NumberOfDataElements(0), DataElements(0),
             ByteOffset(0), Delimited(false) {}
  };

public:

  //! Default constructor creates an empty item.
  vtkDICOMItem() : L(0) {}

  //! Constructor with flag for delimited item.
  explicit vtkDICOMItem(int delimited, unsigned int byteOffset=0);

  //! Copy constructor does reference counting.
  vtkDICOMItem(const vtkDICOMItem &o) : L(o.L) {
    if (this->L) { ++(this->L->ReferenceCount); } }

  //! Destructor does reference counting.
  ~vtkDICOMItem() { this->Clear(); }

  //! Clear the data.
  void Clear() {
    if (this->L && --(this->L->ReferenceCount) == 0) { this->FreeList(); }
    else (this->L = 0); }

  //! Check if empty.
  bool IsEmpty() const { return (this->L == 0); }

  //! Check if this was read as a delimited item.
  bool IsDelimited() const {
    return (this->L == 0 || this->L->Delimited != 0); }

  //! Add a data element to this item.
  /*!
   *  If you specify a string, it must either be an ASCII string, or it must
   *  be encoded in the SpecificCharacterSet for this item.
   */
  void SetAttributeValue(vtkDICOMTag tag, const vtkDICOMValue& v);
  void SetAttributeValue(vtkDICOMTag tag, double v);
  void SetAttributeValue(vtkDICOMTag tag, const std::string& v);

  //! Add a data element at the specified path.
  /*!
   *  The data element is inserted at the tail of the given path.  If the
   *  path lies within a sequence that does not yet exist, then the sequence
   *  will be created.  If an item index in the path points to an item that
   *  does not exist, then that item will be created.
   */
  void SetAttributeValue(const vtkDICOMTagPath& tag, const vtkDICOMValue& v);
  void SetAttributeValue(const vtkDICOMTagPath& tag, double v);
  void SetAttributeValue(const vtkDICOMTagPath& tag, const std::string& v);

  //! Get a data element from this item.
  const vtkDICOMValue &GetAttributeValue(vtkDICOMTag tag) const;
  const vtkDICOMValue &GetAttributeValue(const vtkDICOMTagPath &tag) const;

  //! Get the offset of this item from the beginning of the file.
  /*!
   *  Some DICOM files, such as DICOMDIR files, index into sequences via
   *  byte offsets into the file.  Because of this, it is necessary to
   *  know the byte offset of each item in the sequence.
   */
  unsigned int GetByteOffset() const {
    return (this->L == 0 ? 0 : this->L->ByteOffset); }

  //! Get the number of data elements.
  int GetNumberOfDataElements() const {
    return (this->L ? this->L->NumberOfDataElements : 0); }

  //! Get an iterator for the list of data elements.
  vtkDICOMDataElementIterator Begin() const {
    return (this->L ? this->L->Head.Next : 0); }

  //! Get an end iterator for the list of data elements.
  vtkDICOMDataElementIterator End() const {
    return (this->L ? &this->L->Tail : 0); }

  //! Resolve a private tag, or return (ffff,ffff) if not resolved.
  /*!
   *  Private data elements are mobile, which means that different data
   *  sets might store them at different locations.  Given a private
   *  data element which has a tag of (gggg,xxee) according to its
   *  dictionary, the first two element digits "xx" can change from one
   *  data set to the next, and the data set must have a "Creator Element"
   *  at (gggg,00xx) to allow the digits of "xx" to be resolved.  Please
   *  read DICOM Part 5 Section 7.8 for additional information.
   */
  vtkDICOMTag ResolvePrivateTag(
    vtkDICOMTag ptag, const std::string& creator) const;

  //! Resolve a private tag, and add the creator to the data set.
  /*!
   *  This method works like ResolvePrivateTag, except that if the creator
   *  is not found in the data set, it will be added.  It should be used to
   *  resolve private tags that you plan to write to the data set.  The
   *  returned tag will be (ffff,ffff) if there are no empty slots available
   *  for the creator.  Every private group has 240 available slots.
   */
  vtkDICOMTag ResolvePrivateTagForWriting(
    vtkDICOMTag ptag, const std::string& creator);

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
  vtkDICOMDataElement *NewDataElement(vtkDICOMDataElement **iter);
  static void CopyList(const List *o, List *t);
  static void CopyDataElements(
    const vtkDICOMDataElement *begin, const vtkDICOMDataElement *end,
    List *t);

  //! Find a tag, value pair or insert a pair if not found.
  vtkDICOMDataElement *FindDataElementOrInsert(vtkDICOMTag tag);

  //! Find a child item for a tag path, or insert if not there.
  vtkDICOMItem *FindItemOrInsert(
    const vtkDICOMTagPath& tagpath, vtkDICOMTag *tagptr);

  //! An invalid value, for when one is needed.
  static const vtkDICOMValue InvalidValue;

  //! A linked list to hold the elements.
  List *L;
};

#endif /* __vtkDICOMItem_h */
