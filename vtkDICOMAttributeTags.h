#ifndef __vtkDICOMAttributeTags_h
#define __vtkDICOMAttributeTags_h

#include "vtkDICOMValue.h"

class vtkDICOMTag;
class vtkDICOMTagIterator;

//! A list of attribute tags for the AT value representation.
/*!
 *  This class is for constructing and decoding attribute tag lists.
 *  There are two ways that attribute tag lists can be constructed:
 *  A fixed-size list can be created and then its tags set with the
 *  SetTag() method, or, you can start with an empty list and use
 *  AddTag() to append tags.  Because the underlying container holds
 *  pairs of 16-bit integers, a custom iterator type is needed to
 *  convert these integers into the vtkDICOMAttributeTag type.
 */
class vtkDICOMAttributeTags
{
public:
  //! Construct a growable tag list with no items.
  vtkDICOMAttributeTags() {}

  //! Construct a list of fixed size.
  explicit vtkDICOMAttributeTags(unsigned int n) {
    if (n) { this->V.AllocateUnsignedShortData(vtkDICOMVR::AT, 2*n); } }

  //! Clear the list, remove its contents and make it empty.
  void Clear() { this->V.Clear(); }

  //! Add an item to the list.
  /*!
   *  After calling this method, GetNumberOfTags() will report the
   *  number of items in the list, but GetVL() will return the special
   *  value 0xffffffff.
   */
  void AddTag(vtkDICOMTag item) {
    this->V.AppendValue(vtkDICOMVR::AT, item.GetGroup());
    this->V.AppendValue(vtkDICOMVR::AT, item.GetElement()); }

  //! Get the number of items in the list.
  unsigned int GetNumberOfTags() const {
    return this->V.GetNumberOfValues()/2; }

  //! Set an item in the list.
  /*!
   *  This method can only be used if space as been allocated
   *  by specifying a size when calling the constructor.
   */
  void SetTag(unsigned int i, vtkDICOMTag item) {
    this->V.SetValue(2*i, item.GetGroup());
    this->V.SetValue(2*i+1, item.GetElement()); }

  //! Get an item from the list.
  vtkDICOMTag GetTag(unsigned int i) const;

  //! Get an iterator for the list.
  vtkDICOMTagIterator GetIterator() const;

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

//! An iterator type for vtkDICOMAttributeTags
class vtkDICOMTagIterator
{
public:
  vtkDICOMTagIterator() : Pointer(0) {}

  vtkDICOMTagIterator& operator++() {
    if (this->Pointer) {
      this->Pointer += 2;
      this->Value = vtkDICOMTag(this->Pointer[0], this->Pointer[1]); }
    return *this; }

  vtkDICOMTagIterator operator++(int) {
    const unsigned short *ptr = this->Pointer;
    if (ptr) {
      this->Value = vtkDICOMTag(this->Pointer[0], this->Pointer[1]);
      this->Pointer += 2; }
    return vtkDICOMTagIterator(ptr); }

  vtkDICOMTagIterator& operator--() {
    if (this->Pointer) {
      this->Pointer -= 2;
      this->Value = vtkDICOMTag(this->Pointer[0], this->Pointer[1]); }
    return *this; }

  vtkDICOMTagIterator operator--(int) {
    const unsigned short *ptr = this->Pointer;
    if (ptr) {
      this->Value = vtkDICOMTag(this->Pointer[0], this->Pointer[1]);
      this->Pointer -= 2; }
    return vtkDICOMTagIterator(ptr); }

  const vtkDICOMTag *operator->() const { return &this->Value; }
  const vtkDICOMTag &operator*() const { return this->Value; }

  bool operator==(const vtkDICOMTagIterator& it) const {
    return (this->Pointer == it.Pointer); }

  bool operator!=(const vtkDICOMTagIterator& it) const {
    return (this->Pointer != it.Pointer); }

  bool operator>=(const vtkDICOMTagIterator& it) const {
    return (this->Pointer >= it.Pointer); }

  bool operator<=(const vtkDICOMTagIterator& it) const {
    return (this->Pointer <= it.Pointer); }

  bool operator>(const vtkDICOMTagIterator& it) const {
    return (this->Pointer > it.Pointer); }

  bool operator<(const vtkDICOMTagIterator& it) const {
    return (this->Pointer < it.Pointer); }

  vtkDICOMTagIterator operator+(int i) const {
    return vtkDICOMTagIterator(this->Pointer + 2*i); }

  vtkDICOMTagIterator operator-(int i) const {
    return vtkDICOMTagIterator(this->Pointer - 2*i); }

  int operator-(const vtkDICOMTagIterator &o) const {
    return static_cast<int>((this->Pointer - o.Pointer)/2); }

  const vtkDICOMTagIterator &operator+=(int i) {
    this->Pointer += 2*i;
    this->Value = vtkDICOMTag(this->Pointer[0], this->Pointer[1]);
    return *this; }

  const vtkDICOMTagIterator &operator-=(int i) {
    this->Pointer -= 2*i;
    this->Value = vtkDICOMTag(this->Pointer[0], this->Pointer[1]);
    return *this; }

private:
  vtkDICOMTagIterator(const unsigned short *ptr) : Pointer(ptr) {
    if (ptr) { this->Value = vtkDICOMTag(ptr[0], ptr[1]); } }

  const unsigned short *Pointer;
  vtkDICOMTag Value;

  friend class vtkDICOMAttributeTags;
};

inline vtkDICOMTagIterator vtkDICOMAttributeTags::GetIterator() const
{
  return vtkDICOMTagIterator(this->V.GetUnsignedShortData());
}

ostream& operator<<(ostream& os, const vtkDICOMAttributeTags& v);

#endif /* __vtkDICOMAttributeTags_h */
