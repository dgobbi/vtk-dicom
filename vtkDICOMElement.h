#ifndef __vtkDICOMElement_h
#define __vtkDICOMElement_h

#include "vtkDICOMMetaData.h"

class vtkDICOMElement
{
public:

  //! Factory method to generate new elements.
  /*!
   *  Create a new element from the data that is provided.  It is the
   *  responsibility of the caller of this method to ensure that the
   *  data type is consistent with the VR, and that the VR is allowed
   *  for the specified tag.  The data will be copied into the element.
   *
   *  For these VRs, always use these types:
   *  - OB (other byte) or UN (unknown), use unsigned char.
   *  - OW, use either unsigned short or signed short.
   *  - AT, use two unsigned shorts per tag.
   *  - SQ or XQ, use one vtkDICOMElement pointer per item.
   */
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const char *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const unsigned char *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const short *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const unsigned short *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const int *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const unsigned int *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const float *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              const double *data, vtkIdType n);
  static vtkDICOMElement *New(vtkDICOMTag tag, vtkDICOMVR vr,
                              vtkDICOMElement *const *data, vtkIdType n);

  //! Destructor deletes the internal data array.
  ~vtkDICOMElement();

  //! Get the tag, which is a (group, element) ID pair.
  vtkDICOMTag GetTag() const { return this->Tag; }

  //! Get the VR, the representation of the data values.
  vtkDICOMVR GetVR() const { return this->VR; }

  //! Get the VL, the length of the data in bytes.
  unsigned int GetVL() const { return this->VL; }

  //! Return the text from a text-containing element.
  /*!
   *  Return the element text as a null-terminated string if VR is
   *  AE, AS, CS, DA, DS, DT, IS, LO, LT, PN, SH, ST, TM, UI, UT.
   *  Return NULL if the VR does not contain text:
   *  AT, FL, FD, OB, OF, OW, SL, SS, UL, UN, US.
   */
  const char *GetStringData() const;

  //! Get the number of values in the element.
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
  vtkIdType GetNumberOfValues() const {
    return static_cast<vtkIdType>(this->NumberOfValues); }

  //! Get "n" values from the element, starting at position "i".
  /*!
   *  Get values from the element, doing conversion from the
   *  stored type to the requested type.  If the VR is DS or IS
   *  (integer string or decimal string) then conversion from
   *  text to a numerical type will be performed.  To extract
   *  attribute tags when the VR is AT, use unsigned short (there
   *  will be two unsigned short values per tag).
   */
  void GetValues(unsigned char *v, vtkIdType i, vtkIdType n) const;
  void GetValues(short *v, vtkIdType i, vtkIdType n) const;
  void GetValues(unsigned short *v, vtkIdType i, vtkIdType n) const;
  void GetValues(int *v, vtkIdType i, vtkIdType n) const;
  void GetValues(unsigned int *v, vtkIdType i, vtkIdType n) const;
  void GetValues(float *v, vtkIdType i, vtkIdType n) const;
  void GetValues(double *v, vtkIdType i, vtkIdType n) const;

  //! Get the "i"th value stored in the element as a string.
  /*!
   *  Convert the value to text (if it isn't already) and return
   *  as a string.  An empty string will be returned if there is
   *  uncertainty about the data encoding.  This is the case for
   *  the following VRs: OF, OW, OB, UN.
   */
  std::string GetValueAsString(vtkIdType i = 0);

  //! Get the "i"th value stored in the element as an int.
  /*!
   *  Conversion to int will be performed.  If the value cannot be
   *  converted to int, then zero will be returned.  Values encoded
   *  as float will be truncated to int.  Values encoded as UL
   *  (unsigned int) will be incorrectly returned if larger than
   *  2147483647, because they will be incorrectly interpreted as
   *  a twos-complement negative number.  Values encoded as US
   *  (unsigned short) will always be returned correctly.
   */
  int GetValueAsInt(vtkIdType i = 0);

  //! Get the "i"th value stored in the element as an unsigned int.
  /*!
   *  Conversion to unsigned int will be performed.  If the value cannot
   *  be converted to int, then zero will be returned.  This method should
   *  only be used if it is known that the internal type is unsigned int,
   *  otherwise GetValueAsInt() is preferred.
   */
  unsigned int GetValueAsUnsignedInt(vtkIdType i = 0);

  //! Get the "i"th value stored in the element as a double.
  /*!
   *  Conversion to double will be performed if possible, otherwise a
   *  value of zero will be returned.
   */
  double GetValueAsDouble(vtkIdType i = 0);

  //! Get the one of the elements in a sequence, if VR is SQ or XQ.
  vtkDICOMElement *GetSequenceItem(vtkIdType i);
  const vtkDICOMElement *GetSequenceItem(vtkIdType i) const;

  //! Append value "i" of the element's data to the supplied string.
  /*!
   *  This will convert the value to human-readable format.
   *  Be cautious when using this method for an element with VR equal
   *  to ST, LT, or UT, because the resulting string might be very
   *  long, and might contain special (i.e. non-printable) characters.
   */
  void AppendValueToString(std::string &str, vtkIdType i) const;

protected:
  //! The constructor is private.  Use New().
  vtkDICOMElement();

  //! Internal templated GetValues() method.
  template<class OT>
  void GetValuesT(OT *v, vtkIdType s, vtkIdType c) const;

  //! Get the start and end for the "i"th backslash-delimited value.
  void Substring(vtkIdType i, const char *&start, const char *&end) const;

  // The element header is 16 bytes, VR and VL are explicit.
  vtkDICOMTag    Tag;
  vtkDICOMVR     VR;
  unsigned char  Type;
  unsigned char  NeedsFree;
  unsigned int   VL;
  unsigned int   NumberOfValues;

private:
  vtkDICOMElement(const vtkDICOMElement&);
  void operator=(const vtkDICOMElement&);
};

#endif /* __vtkDICOMElement_h */
