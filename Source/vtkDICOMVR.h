/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMVR_h
#define vtkDICOMVR_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"

//! VRs (Value Representations)
class VTK_DICOM_EXPORT vtkDICOMVR
{
public:
  //! The VR enum constants.
  /*!
   *  Sorting the constants numerically will sort the VRs alphabetically.
   */
  enum EnumType
  {
    XX = 0x00, //!< Null (No Value)
    AE = 0x01, //!< Application Entity
    AS = 0x02, //!< Age String
    AT = 0x03, //!< Attribute Tag
    CS = 0x04, //!< Code String
    DA = 0x05, //!< Date
    DS = 0x06, //!< Decimal String
    DT = 0x07, //!< Date Time
    FD = 0x08, //!< Floating Point Double
    FL = 0x09, //!< Floating Point Single
    IS = 0x0a, //!< Integer String
    LO = 0x0b, //!< Long String
    LT = 0x0c, //!< Long Text
    OB = 0x0d, //!< Other Byte
    OD = 0x0e, //!< Other Double
    OF = 0x0f, //!< Other Float
    OW = 0x10, //!< Other Word
    PN = 0x11, //!< Personal Name
    SH = 0x12, //!< Short String
    SL = 0x13, //!< Signed Long
    SQ = 0x14, //!< Sequence of Items
    SS = 0x15, //!< Signed Short
    ST = 0x16, //!< Short Text
    TM = 0x17, //!< Time
    UI = 0x18, //!< Unique Identifier
    UL = 0x19, //!< Unsigned Long
    UN = 0x1a, //!< Unknown
    UR = 0x1b, //!< URI or URL
    US = 0x1c, //!< Unsigned Short
    UT = 0x1d, //!< Unlimited Text
    OX = 0x1e, //!< Either OB or OW (for dict entries, not data elements)
    XS = 0x1f  //!< Either SS or US (for dict entries, not data elements)
  };

  //! Construct an empty, invalid VR.
  vtkDICOMVR() : Key(0) {}

  //! Construct a VR from a VR enum constant.
  vtkDICOMVR(EnumType vr) : Key(static_cast<unsigned char>(vr)) {}

  //! Attempt to construct a VR from a two-byte string.
  vtkDICOMVR(const char *vr) : Key(VRTable[static_cast<unsigned char>(vr[0])]
                                   [static_cast<unsigned char>(vr[1])]) {}

  //! Attempt to construct a VR from a two unsigned bytes.
  vtkDICOMVR(const unsigned char vr[2]) : Key(VRTable[vr[0]][vr[1]]) {}

  //! Check validity of this VR.
  bool IsValid() const { return (this->Key != 0); }

  //! Get the data type for this VR.
  int GetType() const { return TypeTable[this->Key]; }

  //! Get the two-character text for this VR.
  const char *GetText() const { return TextTable[this->Key]; }

  //! The VRs OB, OD, OF, OW, SQ, UN, UR, UT require a 32-bit VL.
  bool HasLongVL() const { return (((1 << this->Key) & 0x2c11e000) != 0); }

  //! The VRs SH, LO, PN, ST, LT, and UT use SpecificCharacterSet.
  bool HasSpecificCharacterSet() const {
    return (((1 << this->Key) & 0x20461800) != 0); }

  //! The VRs ST, LT, and UT carry only one value.
  /*!
   * Specifically, this means that a backslash is not interpreted as a
   * value separator in these VRs. UR is not included, because backslash
   * is an illegal character in UR.
   */
  bool HasSingleValue() const {
    return (((1 << this->Key) & 0x20401000) != 0); }

  //! AE, AS, CS, DA, DS, DT, IS, LO, PN, SH, TM, UI, UR are padded.
  /*!
   *  These VRs might have padding that is removed before they are
   *  converted into a string.
   */
  bool HasPadding() const {
    return (((1 << this->Key) & 0x09860cf6) != 0); }

  bool operator==(vtkDICOMVR a) const { return (this->Key == a.Key); }
  bool operator!=(vtkDICOMVR a) const { return (this->Key != a.Key); }
  bool operator<=(vtkDICOMVR a) const { return (this->Key <= a.Key); }
  bool operator>=(vtkDICOMVR a) const { return (this->Key >= a.Key); }
  bool operator<(vtkDICOMVR a) const { return (this->Key < a.Key); }
  bool operator>(vtkDICOMVR a) const { return (this->Key > a.Key); }

private:
  unsigned char Key;

  static const unsigned char *VRTable[256];
  static const unsigned char TypeTable[32];
  static const char TextTable[32][4];
};

VTK_DICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMVR& a);

#endif /* vtkDICOMVR_h */
