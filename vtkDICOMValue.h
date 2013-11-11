/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMValue_h
#define __vtkDICOMValue_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"
#include "vtkDICOMVR.h"
#include "vtkDICOMTag.h"
#include "vtkDICOMReferenceCount.h"

#include <string>

// type constants
#define VTK_DICOM_TAG    13
#define VTK_DICOM_ITEM   14
#define VTK_DICOM_VALUE  15

class vtkDICOMItem;
class vtkDICOMSequence;

//! A class to store attribute values for DICOM metadata.
/*!
 *  The vtkDICOMValue class is a container for any values that
 *  can be stored in a DICOM data element.  Like std::string,
 *  it is implemented as a pointer to a reference-counted internal
 *  data object.  To keep it lightweight, in terms of size, it has
 *  no virtual methods.
 */
class VTK_DICOM_EXPORT vtkDICOMValue
{
private:
  //! A reference-counted value class.
  struct Value
  {
    vtkDICOMReferenceCount ReferenceCount;
    unsigned char  Type;
    vtkDICOMVR     VR;
    unsigned int   VL;
    unsigned int   NumberOfValues;

    Value() : ReferenceCount(1) {}
  };

  //! The value class, subclassed to support values of different types.
  template<class T>
  struct ValueT : Value
  {
    T Data[1];

    ValueT(vtkDICOMVR vr, unsigned int vn);
    static bool Compare(const Value *a, const Value *b);
  };

public:
  //! Construct a new value from the data that is provided.
  /*!
   *  The data will be copied into the value, with conversion if
   *  necessary.  If the data cannot be converted into the type
   *  required by the VR, then the resulting value will be invalid.
   *
   *  For these VRs, always use these types:
   *  - OB (other byte) or UN (unknown), use unsigned char.
   *  - OW, use either unsigned short or signed short.
   *  - AT, use an array of vtkDICOMTag values.
   *  - SQ, use an array of vtkDICOMItem values.
   */
  vtkDICOMValue(vtkDICOMVR vr, double v);
  vtkDICOMValue(vtkDICOMVR vr, const std::string& v);
  vtkDICOMValue(vtkDICOMVR vr, vtkDICOMTag v);
  vtkDICOMValue(vtkDICOMVR vr,
                const char *data, const char *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const unsigned char *data, const unsigned char *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const short *data, const short *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const unsigned short *data, const unsigned short *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const int *data, const int *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const unsigned int *data, const unsigned int *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const float *data, const float *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const double *data, const double *end);
  vtkDICOMValue(vtkDICOMVR vr,
                const vtkDICOMTag *data, const vtkDICOMTag *end);

  //! Create an emtpy value.
  explicit vtkDICOMValue(vtkDICOMVR vr);

  //! Copy constructor.
  vtkDICOMValue(const vtkDICOMValue &v) : V(v.V) {
    if (this->V) { ++(this->V->ReferenceCount); } }

  //! Construct from a sequence.
  vtkDICOMValue(const vtkDICOMSequence &v);

  //! Default constructor, constructs an invalid value.
  vtkDICOMValue() : V(0) {}

  //! Destructor releases the internal data array.
  ~vtkDICOMValue() { this->Clear(); }

  //! Clear the value, the result is an invalid value.
  void Clear() {
    if (this->V && --(this->V->ReferenceCount) == 0) {
      this->FreeValue(this->V); }
    this->V = 0; }

  //! Check whether this value is valid, i.e. contains data.
  bool IsValid() const { return (this->V != 0); }

  //! Get the VR, the representation of the data values.
  vtkDICOMVR GetVR() const { return (this->V ? this->V->VR : vtkDICOMVR()); }

  //! Get the VL, the length of the data in bytes (will always be even).
  unsigned int GetVL() const { return (this->V ? this->V->VL : 0); }

  //! Get the value multiplicity.
  /*!
   *  The number of values has different interpretations for
   *  for different VRs:
   *  - for backslash-delimited text (AE, AS, CS, DA, DS, DT, IS,
   *    LO, PN, SH, UI) it is the number of backslash-separated values.
   *  - for other text (LT, ST, UT) the number of values is always 1.
   *  - for binary numerical data (FL, FD, SS, US, SL, UL, OF, OW, OB)
   *    the number of binary values will be returned.
   *  - for UN, the number of bytes will be returned.
   *  - for attribute tags (VR is AT) the number of tags will be returned.
   *  - for sequences (SQ and XQ) the number of items in the sequence,
   *    excluding any delimeters, will be returned.
   */
  unsigned int GetNumberOfValues() const {
    return (this->V ? this->V->NumberOfValues : 0); }

  //! Copy values into vb until ve is reached, starting at value "i".
  /*!
   *  Get one or more values, doing conversion from the stored type to
   *  the requested type.  If the VR is IS or DS (integer string or
   *  decimal string) then conversion from text to a numerical value
   *  will be performed.
   */
  void GetValues(std::string *vb, std::string *ve, unsigned int i=0) const;
  void GetValues(unsigned char *vb, unsigned char *ve, unsigned int i=0) const;
  void GetValues(short *vb, short *ve, unsigned int i=0) const;
  void GetValues(unsigned short *vb, unsigned short *ve, unsigned int i=0) const;
  void GetValues(int *vb, int *ve, unsigned int i=0) const;
  void GetValues(unsigned int *vb, unsigned int *ve, unsigned int i=0) const;
  void GetValues(float *vb, float *ve, unsigned int i=0) const;
  void GetValues(double *vb, double *ve, unsigned int i=0) const;
  void GetValues(vtkDICOMTag *vb, vtkDICOMTag *ve, unsigned int i=0) const;

  //! Get one scalar value or single string from the value.
  /*!
   *  Convert the i'th value to the desired type, if possible,
   *  and return it.  If the value is invalid, or conversion is
   *  not possible, or the index is out of range, then the return
   *  value will be zero (or an empty string).
   */
  std::string GetString(unsigned int i) const;
  unsigned char GetUnsignedChar(unsigned int i) const;
  short GetShort(unsigned int i) const;
  unsigned short GetUnsignedShort(unsigned int i) const;
  int GetInt(unsigned int i) const;
  unsigned int GetUnsignedInt(unsigned int i) const;
  float GetFloat(unsigned int i) const;
  double GetDouble(unsigned int i) const;
  vtkDICOMTag GetTag(unsigned int i) const;

  //! Convert the value to a scalar value or string.
  /*!
   *  The value is converted to the desired type, if possible, and returned.
   *  Otherwise the return value is zero (or an empty string).  Conversion
   *  to string always produces an empty string for values of type UN, SQ,
   *  OB, OW, and OF.
   */
  std::string AsString() const;
  unsigned char AsUnsignedChar() const;
  short AsShort() const;
  unsigned short AsUnsignedShort() const;
  int AsInt() const;
  unsigned int AsUnsignedInt() const;
  float AsFloat() const;
  double AsDouble() const;
  vtkDICOMTag AsTag() const;

  //! Get a pointer to the internal data array.
  /*!
   *  GetCharData will return a null-terminated string if VR is
   *  AE, AS, CS, DA, DS, DT, IS, LO, LT, PN, SH, ST, TM, UI, UT,
   *  with a possible trailing space if the VR is not UI (UID).
   *  The other methods will return a valid pointer if the the
   *  requested pointer type matches the VR.  To compute the size
   *  of the array, divide VL by the size of the requested type.
   *  Do not use NumberOfValues as the array size, because for many
   *  VRs the array size is much larger than the NumberOfValues,
   *  in fact for OB, OF, UT, and many other VRs the entire array
   *  counts as a single value, according to the DICOM standard.
   *  Returns NULL if the requested pointer type does not match the VR.
   */
  const char *GetCharData() const;
  const unsigned char *GetUnsignedCharData() const;
  const short *GetShortData() const;
  const unsigned short *GetUnsignedShortData() const;
  const int *GetIntData() const;
  const unsigned int *GetUnsignedIntData() const;
  const float *GetFloatData() const;
  const double *GetDoubleData() const;
  const vtkDICOMTag *GetTagData() const;
  const vtkDICOMItem *GetSequenceData() const;
  const vtkDICOMValue *GetMultiplexData() const;
  vtkDICOMValue *GetMultiplexData();

  //! Allocate space within a value object.
  /*!
   *  Allocate an array of the specified size (number of elements)
   *  within the value object.  This method will not do any checks
   *  to ensure that the data type matches the VR.  It is meant to
   *  be an efficent way for the parser to allocate a value so that
   *  the value's contents can be read in directly from a file.
   */
  char *AllocateCharData(vtkDICOMVR vr, unsigned int vn);
  unsigned char *AllocateUnsignedCharData(vtkDICOMVR vr, unsigned int vn);
  short *AllocateShortData(vtkDICOMVR vr, unsigned int vn);
  unsigned short *AllocateUnsignedShortData(vtkDICOMVR vr, unsigned int vn);
  int *AllocateIntData(vtkDICOMVR vr, unsigned int vn);
  unsigned int *AllocateUnsignedIntData(vtkDICOMVR vr, unsigned int vn);
  float *AllocateFloatData(vtkDICOMVR vr, unsigned int vn);
  double *AllocateDoubleData(vtkDICOMVR vr, unsigned int vn);
  vtkDICOMTag *AllocateTagData(vtkDICOMVR vr, unsigned int vn);
  vtkDICOMItem *AllocateSequenceData(vtkDICOMVR vr, unsigned int vn);
  vtkDICOMValue *AllocateMultiplexData(vtkDICOMVR vr, unsigned int vn);

  //! Compute the number of backslash-separated string values.
  /*!
   *  After calling AllocateCharData and writing text into the allocated
   *  space, this must be called to set the NumberOfValues according to
   *  the number of backslash-separated string values that are present.
   */
  void ComputeNumberOfValuesForCharData();

  //! Reallocate data of type OB or UN.
  /*!
   *  Values of type OB or UN can hold encapsulated data.  When
   *  building these values, it is useful to be able to extend
   *  the internal data as needed.  After this method is called,
   *  the NumberOfValues will be vn, and the VL will be 0xffffffff.
   */
  unsigned char *ReallocateUnsignedCharData(unsigned int vn);

  //! Append value "i" to the supplied string.
  /*!
   *  This will convert the value to human-readable format.
   *  Be cautious when using this method for an element with VR equal
   *  to ST, LT, or UT, because the resulting string might be very
   *  long, and might contain special (i.e. non-printable) characters.
   */
  void AppendValueToString(std::string &str, unsigned int i) const;

  //! Override assignment operator for reference counting.
  vtkDICOMValue& operator=(const vtkDICOMValue& o) {
    if (this->V != o.V) {
      if (o.V) { ++(o.V->ReferenceCount); }
      if (this->V) {
        if (--(this->V->ReferenceCount) == 0) { this->FreeValue(this->V); } }
      this->V = o.V; }
    return *this; }

  //! Assign a value from a sequence object.
  vtkDICOMValue& operator=(const vtkDICOMSequence& o);

  //! Equality requires that all elements of the value are equal.
  bool operator==(const vtkDICOMValue& o) const;
  bool operator!=(const vtkDICOMValue& o) const { return !(*this == o); }

private:
  //! Allocate an array of size vn for the specified vr
  template<class T>
  T *Allocate(vtkDICOMVR vr, unsigned int vn);

  //! Free the internal value.
  static void FreeValue(Value *v);

  //! Internal templated GetValues() method.
  template<class OT>
  void GetValuesT(OT *v, OT *ve, unsigned int s) const;

  //! Internal templated value creation method.
  template<class T>
  void CreateValue(vtkDICOMVR vr, const T *data, const T *end);

  //! Internal templated method to initialize for future appends.
  template<class T>
  void AppendInit(vtkDICOMVR vr);

  //! Internal templated method to grow the value.
  template<class T>
  void AppendValue(const T &item);

  //! Internal templated method to set a value.
  template<class T>
  void SetValue(unsigned int i, const T &item);

  //! Get the start and end for the "i"th backslash-delimited value.
  void Substring(unsigned int i, const char *&start, const char *&end) const;

  //! The only data member: a pointer to the internal value.
  Value *V;

  // friend the sequence class, it requires AppendValue() and SetValue().
  friend class vtkDICOMSequence;
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& os, const vtkDICOMValue& v);

#endif /* __vtkDICOMValue_h */
