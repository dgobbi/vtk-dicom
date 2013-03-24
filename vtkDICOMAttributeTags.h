#ifndef __vtkDICOMAttributeTags_h
#define __vtkDICOMAttributeTags_h

#include "vtkDICOMValue.h"

class vtkDICOMTag;

//! A sequence of items according to the SQ representation.
/*!
 *  This class is for constructing and decoding sequences.
 *  There are two ways that sequences can be constructed:
 *  A fixed-size sequence can be created and then its items
 *  filled in with the SetTag() method, or, you can start
 *  with an empty sequence and use AddTag() to append items.
 */
class vtkDICOMAttributeTags
{
public:
  //! Construct a growable sequence with no items.
  vtkDICOMAttributeTags() {}

  //! Construct a sequence of fixed size.
  explicit vtkDICOMAttributeTags(unsigned int n) {
    if (n) { this->V.AllocateUnsignedShortData(vtkDICOMVR::AT, 2*n); } }

  //! Clear a sequence, remove its contents and make it empty.
  void Clear() { this->V.Clear(); }

  //! Add an item to the sequence.
  /*!
   *  After calling this method, GetNumberOfValues() will report
   *  the number of items in the sequence, but GetVL() will return
   *  the special value 0xffffffff to indicate that this is a delimited
   *  sequence rather than a fixed-size sequence.
   */
  void AddTag(vtkDICOMTag item) {
    this->V.AppendValue(vtkDICOMVR::AT, item.GetGroup());
    this->V.AppendValue(vtkDICOMVR::AT, item.GetElement()); }

  //! Get the number of items in the sequence.
  unsigned int GetNumberOfTags() const {
    return this->V.GetNumberOfValues()/2; }

  //! Set an item in the sequence.
  /*!
   *  This method can only be used if space as been allocated within
   *  the sequence by specifying a size when calling the constructor.
   */
  void SetTag(unsigned int i, vtkDICOMTag item) {
    this->V.SetValue(2*i, item.GetGroup());
    this->V.SetValue(2*i+1, item.GetElement()); }

  //! Get an item from the sequence.
  vtkDICOMTag GetTag(unsigned int i) const;

  //! Use value copy constructor
  vtkDICOMAttributeTags(const vtkDICOMAttributeTags& o) : V(o.V) {}

  //! Conversion from other value types is checked.
  vtkDICOMAttributeTags(const vtkDICOMValue& o) : V(o) {
    if (o.GetVR() != vtkDICOMVR::AT) { this->V.Clear(); } }

  //! Use base class assignment operator.
  vtkDICOMAttributeTags& operator=(const vtkDICOMAttributeTags& o) {
    this->V = o.V; return *this; }

  //! Assignment from other value types is checked
  vtkDICOMAttributeTags& operator=(const vtkDICOMValue& o) {
    if (o.GetVR() == vtkDICOMVR::AT) { this->V = o; return *this; }
    else { this->V.Clear(); } }

private:
  friend class vtkDICOMValue;

  vtkDICOMValue V;
};

#endif /* __vtkDICOMAttributeTags_h */
