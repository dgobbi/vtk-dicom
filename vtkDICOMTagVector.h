#ifndef __vtkDICOMTagVector_h
#define __vtkDICOMTagVector_h

#include "vtkDICOMTag.h"
#include "vtkDICOMValue.h"

//! A value that is a list of attribute tags.
/*!
 *  This is a convenience class for constructing a list of
 *  attribute tags.
 */
class vtkDICOMTagVector : public vtkDICOMValue
{
public:
  //! Construct an attribute tag list with no tags.
  vtkDICOMTagVector() {
    this->AllocateUnsignedShortData(vtkDICOMVR::AT, 2);
    this->V->NumberOfValues = 0;
    this->V->VL = 0; }

  //! Construct a tag list of fixed size.
  explicit vtkDICOMTagVector(unsigned int n) {
    unsigned int m = 1;
    while (m < n) { m <<= 1; }
    this->AllocateUnsignedShortData(vtkDICOMVR::AT, 2*m);
    this->V->NumberOfValues = 2*m;
    this->V->VL = 4*m; }

  //! Add an tag to the list.
  /*!
   *  After calling this method, GetNumberOfValues() will report
   *  the number of tags in the list, but GetVL() will return
   *  the special value 0xffffffff.
   */
  void AddTag(vtkDICOMTag tag);

  //! Set an tag in the list.
  /*!
   *  This method can only be used if space as been allocated within
   *  the list, e.g. by specifying a size when calling the constructor.
   */
  void SetTag(unsigned int i, vtkDICOMTag tag);

  //! Get an tag from the list.
  vtkDICOMTag GetTag(unsigned int i) const;

  //! Get the number of tags in the list.
  unsigned int GetNumberOfTagVector() const {
    return ((this->V != 0 && this->V->VR == vtkDICOMVR::AT) ?
            this->V->NumberOfValues*2 : 0); }

  //! Use base class copy constructor.
  vtkDICOMTagVector(const vtkDICOMTagVector& o) : vtkDICOMValue(o) {}

  //! Conversion from other value types is checked.
  vtkDICOMTagVector(const vtkDICOMValue& o) : vtkDICOMValue(o) {
    if (o.V == 0 || o.V->VR != vtkDICOMVR::AT) { this->Clear(); } }

  //! Use base class assignment operator.
  vtkDICOMTagVector& operator=(const vtkDICOMTagVector& o) {
    *(static_cast<vtkDICOMValue *>(this)) = o; return *this; }

  //! Assignment from other value types is checked
  vtkDICOMTagVector& operator=(const vtkDICOMValue& o) {
    if (o.V != 0 && o.V->VR == vtkDICOMVR::AT) {
      *(static_cast<vtkDICOMValue *>(this)) = o; return *this; }
    else { this->Clear(); } }
};

#endif /* __vtkDICOMTagVector_h */
