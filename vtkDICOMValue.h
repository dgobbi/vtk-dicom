#ifndef __vtkDICOMValue_h
#define __vtkDICOMValue_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMVR.h"

// type constants
#define VTK_DICOM_ITEM   13 
#define VTK_DICOM_VALUE  14

class vtkDICOMSequenceItem;
class vtkDICOMSequence;

//! A class to store attribute values for DICOM metadata.
/*!
 *  The vtkDICOMValue class is a container for any values that
 *  can be stored in a DICOM data element.  Like std::string,
 *  it is implemented as a pointer to a reference-counted internal
 *  data object.  To keep it lightweight, in terms of size, it has
 *  no virtual methods.
 */
class vtkDICOMValue
{
  //! A reference-counted value class.
  struct Value
  {
    unsigned int   ReferenceCount;
    vtkDICOMVR     VR;
    unsigned char  Type;
    unsigned char  NeedsFree;
    unsigned int   VL;
    unsigned int   NumberOfValues;

    Value() : ReferenceCount(1) {};
  };

  //! The value class, subclassed to support values of different types.
  template<class T>
  struct ValueT : Value
  {
    T *Data;

    static bool Compare(const Value *a, const Value *b);
  };

  //! The value class, subclassed to support local value storage.
  template<class T, unsigned int N>
  struct ValueTN : ValueT<T>
  {
    T LocalData[N];

    ValueTN(vtkDICOMVR vr, unsigned int vl);
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
   *  - AT, use two unsigned shorts per tag.
   *  - SQ, use an array of vtkDICOMSequenceItem values.
   */
  vtkDICOMValue(vtkDICOMVR vr, const char *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const unsigned char *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const short *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const unsigned short *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const int *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const unsigned int *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const float *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const double *data, unsigned int n);
  vtkDICOMValue(
    vtkDICOMVR vr, const vtkDICOMSequenceItem *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, const vtkDICOMValue *data, unsigned int n);
  vtkDICOMValue(vtkDICOMVR vr, double v);
  vtkDICOMValue(vtkDICOMVR vr, const std::string& v);

  //! Copy constructor.
  vtkDICOMValue(const vtkDICOMValue &v) : V(v.V) {
    if (this->V) { this->V->ReferenceCount++; } }

  //! Default constructor, constructs an empty value.
  vtkDICOMValue() : V(0) {}

  //! Destructor releases the internal data array.
  ~vtkDICOMValue() { this->Clear(); }

  //! Clear the value.
  void Clear() {
    if (this->V && --this->V->ReferenceCount == 0) {
      this->FreeValue(this->V); }
    this->V = 0; }

  //! Check whether this value is empty.
  bool IsEmpty() const { return (this->V == 0); }

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
   *  - for attribute tags (VR is AT) the number of 16-bit values will
   *    be returned, i.e. twice the number of (group,element) tags.
   *  - for sequences (SQ and XQ) the number of items in the sequence,
   *    including any delimeters, will be returned.
   */
  int GetNumberOfValues() const {
    return (this->V ? static_cast<int>(this->V->NumberOfValues) : 0); }

  //! Get "n" values, starting at position "i".
  /*!
   *  Get one or more values, doing conversion from the stored type to
   *  the requested type.  If the VR is IS or DS (integer string or
   *  decimal string) then conversion from text to a numerical value
   *  will be performed.
   */
  void GetValues(unsigned char *v, int i, int n) const;
  void GetValues(short *v, int i, int n) const;
  void GetValues(unsigned short *v, int i, int n) const;
  void GetValues(int *v, int i, int n) const;
  void GetValues(unsigned int *v, int i, int n) const;
  void GetValues(float *v, int i, int n) const;
  void GetValues(double *v, int i, int n) const;
  void GetValues(std::string *v, int i, int n) const;

  //! Get a pointer to the internal data array.
  /*!
   *  GetTextData will return a null-terminated string if VR is
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
  const char *GetTextData() const;
  const unsigned char *GetByteData() const;
  const short *GetShortData() const;
  const unsigned short *GetUShortData() const;
  const int *GetLongData() const;
  const unsigned int *GetULongData() const;
  const float *GetFloatData() const;
  const double *GetDoubleData() const;
  const vtkDICOMSequenceItem *GetSequenceData() const;
  const vtkDICOMValue *GetMultiplexData() const;
  vtkDICOMValue *GetMultiplexData();

  //! Allocate space within a value object.
  /*!
   *  Allocate an array of the specified size (number of elements)
   *  within the value object.  This method will not do any checks
   *  to ensure that the data type matches the VR.
   */
  char *AllocateTextData(vtkDICOMVR vr, unsigned int vn);
  unsigned char *AllocateByteData(vtkDICOMVR vr, unsigned int vn);
  short *AllocateShortData(vtkDICOMVR vr, unsigned int vn);
  unsigned short *AllocateUShortData(vtkDICOMVR vr, unsigned int vn);
  int *AllocateLongData(vtkDICOMVR vr, unsigned int vn);
  unsigned int *AllocateULongData(vtkDICOMVR vr, unsigned int vn);
  float *AllocateFloatData(vtkDICOMVR vr, unsigned int vn);
  double *AllocateDoubleData(vtkDICOMVR vr, unsigned int vn);
  vtkDICOMSequenceItem *AllocateSequenceData(vtkDICOMVR vr, unsigned int vn);
  vtkDICOMValue *AllocateMultiplexData(vtkDICOMVR vr, unsigned int vn);

  //! Append value "i" to the supplied string.
  /*!
   *  This will convert the value to human-readable format.
   *  Be cautious when using this method for an element with VR equal
   *  to ST, LT, or UT, because the resulting string might be very
   *  long, and might contain special (i.e. non-printable) characters.
   */
  void AppendValueToString(std::string &str, int i) const;

  //! Override assignment operator for reference counting.
  vtkDICOMValue& operator=(const vtkDICOMValue& o) {
    if (this->V != o.V) {
      if (o.V) { o.V->ReferenceCount++; }
      if (this->V) {
        if (--this->V->ReferenceCount == 0) { this->FreeValue(this->V); } }
      this->V = o.V; }
    return *this; }

  bool operator==(const vtkDICOMValue& o) const;
  bool operator!=(const vtkDICOMValue& o) const { return !(*this == o); }

private:
  //! Free the internal value.
  static void FreeValue(Value *v);

  //! Internal templated GetValues() method.
  template<class OT>
  void GetValuesT(OT *v, int s, int c) const;

  //! Internal templated value creation method.
  template<class T>
  void CreateValue(vtkDICOMVR vr, const T *data, unsigned int n);

  //! Get the start and end for the "i"th backslash-delimited value.
  void Substring(int i, const char *&start, const char *&end) const;

  //! The only data member: a pointer to the internal value.
  Value *V;

  // friend the one subclass.
  friend class vtkDICOMSequence;
};

ostream& operator<<(ostream& os, const vtkDICOMValue& v);

#endif /* __vtkDICOMValue_h */
