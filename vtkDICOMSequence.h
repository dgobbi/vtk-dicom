/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMSequence_h
#define __vtkDICOMSequence_h

#include "vtkDICOMValue.h"

class vtkDICOMItem;

//! A sequence of items according to the SQ representation.
/*!
 *  This class is for constructing and decoding sequences.
 *  There are two ways that sequences can be constructed:
 *  A fixed-size sequence can be created and then its items
 *  filled in with the SetItem() method, or, you can start
 *  with an empty sequence and use AddItem() to append items.
 */
class vtkDICOMSequence
{
public:
  //! Construct a growable sequence with no items.
  vtkDICOMSequence() {}

  //! Construct a sequence of fixed size.
  explicit vtkDICOMSequence(unsigned int n) {
    if (n) { this->V.AllocateSequenceData(vtkDICOMVR::SQ, n); } }

  //! Clear a sequence, remove its contents and make it empty.
  void Clear() { this->V.Clear(); }

  //! Add an item to the sequence.
  /*!
   *  After calling this method, GetNumberOfItems() will report
   *  the number of items in the sequence, but GetVL() will return
   *  the special value 0xffffffff to indicate that this is a delimited
   *  sequence rather than a fixed-size sequence.
   */
  void AddItem(const vtkDICOMItem& item) {
    this->V.AppendValue(vtkDICOMVR::SQ, item); }

  //! Get the number of items in the sequence.
  unsigned int GetNumberOfItems() const {
    return this->V.GetNumberOfValues(); }

  //! Set an item in the sequence.
  /*!
   *  This method can only be used if space as been allocated within
   *  the sequence by specifying a size when calling the constructor.
   */
  void SetItem(unsigned int i, const vtkDICOMItem& item) {
    this->V.SetValue(i, item); }

  //! Get an item from the sequence.
  const vtkDICOMItem& GetItem(unsigned int i) const;

  //! Get an iterator for the items in the sequence.
  const vtkDICOMItem *GetSequenceData() const {
    return this->V.GetSequenceData(); }

  //! Use value copy constructor
  vtkDICOMSequence(const vtkDICOMSequence& o) : V(o.V) {}

  //! Conversion from other value types is checked.
  vtkDICOMSequence(const vtkDICOMValue& o) : V(o) {
    if (o.GetVR() != vtkDICOMVR::SQ) { this->V.Clear(); } }

  //! Use base class assignment operator.
  vtkDICOMSequence& operator=(const vtkDICOMSequence& o) {
    this->V = o.V; return *this; }

  //! Assignment from other value types is checked
  vtkDICOMSequence& operator=(const vtkDICOMValue& o) {
    if (o.GetVR() == vtkDICOMVR::SQ) { this->V = o; return *this; }
    else { this->V.Clear(); } }

private:
  friend class vtkDICOMValue;

  vtkDICOMValue V;
};

ostream& operator<<(ostream& os, const vtkDICOMSequence& v);

#endif /* __vtkDICOMSequence_h */
