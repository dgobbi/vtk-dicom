#ifndef __vtkDICOMSequence_h
#define __vtkDICOMSequence_h

#include "vtkDICOMValue.h"

class vtkDICOMItem;

//! A value that is a sequence of items.
/*!
 *  This is a convenience class for constructing a sequence.
 *  Without this class, a sequence of fixed size can be created
 *  by calling AllocateSequenceData() on a vtkDICOMValue object.
 *  This class adds SetItem() and AddItem() methods to make
 *  construction of a sequence easier.
 */
class vtkDICOMSequence : public vtkDICOMValue
{
public:
  //! Construct a growable sequence with no items.
  vtkDICOMSequence() {}

  //! Construct a sequence of fixed size.
  vtkDICOMSequence(unsigned int n) {
    if (n) { this->AllocateSequenceData(vtkDICOMVR::SQ, n); } }

  //! Add an item to the sequence.
  /*!
   *  After calling this method, GetNumberOfValues() will report
   *  the number of items in the sequence, but GetVL() will return
   *  the special value 0xffffffff.
   */
  void AddItem(const vtkDICOMItem& item);

  //! Get the number of items in the sequence.
  unsigned int GetNumberOfItems() const {
    return ((this->V != 0 && this->V->Type == VTK_DICOM_ITEM) ?
            this->V->NumberOfValues : 0); }

  //! Set an item in the sequence.
  /*!
   *  This method can only be used if space as been allocated within
   *  the sequence, e.g. by specifying a size when calling the constructor.
   */
  void SetItem(unsigned int i, const vtkDICOMItem& item);

  //! Get an item from the sequence.
  const vtkDICOMItem& GetItem(unsigned int i) const;

  //! Use base class copy constructor.
  vtkDICOMSequence(const vtkDICOMSequence& o) : vtkDICOMValue(o) {}

  //! Conversion from other value types is checked.
  vtkDICOMSequence(const vtkDICOMValue& o) : vtkDICOMValue(o) {
    if (o.V == 0 || o.V->Type != VTK_DICOM_ITEM) { this->Clear(); } }

  //! Use base class assignment operator.
  vtkDICOMSequence& operator=(const vtkDICOMSequence& o) {
    *(static_cast<vtkDICOMValue *>(this)) = o; return *this; }

  //! Assignment from other value types is checked
  vtkDICOMSequence& operator=(const vtkDICOMValue& o) {
    if (o.V != 0 && o.V->Type == VTK_DICOM_ITEM) {
      *(static_cast<vtkDICOMValue *>(this)) = o; return *this; }
    else { this->Clear(); } }
};

#endif /* __vtkDICOMSequence_h */
