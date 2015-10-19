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
#include "vtkDICOMModule.h" // For export macro

//! VRs (Value Representations)
class VTKDICOM_EXPORT vtkDICOMVR
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
    OL = 0x10, //!< Other Long
    OW = 0x11, //!< Other Word
    PN = 0x12, //!< Personal Name
    SH = 0x13, //!< Short String
    SL = 0x14, //!< Signed Long
    SQ = 0x15, //!< Sequence of Items
    SS = 0x16, //!< Signed Short
    ST = 0x17, //!< Short Text
    TM = 0x18, //!< Time
    UC = 0x19, //!< Unlimited Characters
    UI = 0x1a, //!< Unique Identifier
    UL = 0x1b, //!< Unsigned Long
    UN = 0x1c, //!< Unknown
    UR = 0x1d, //!< URI or URL
    US = 0x1e, //!< Unsigned Short
    UT = 0x1f, //!< Unlimited Text
    OX = 0x20, //!< Either OB or OW (for dict entries, not data elements)
    XS = 0x21  //!< Either SS or US (for dict entries, not data elements)
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

  //! The VRs OB, OD, OF, OL, OW, SQ, UC, UN, UR, UT require a 32-bit VL.
  bool HasLongVL() const {
    return (((1ull << this->Key) & 0xb223e001u) != 0); }

  //! The VRs SH, LO, PN, ST, LT, UC, and UT use SpecificCharacterSet.
  bool HasSpecificCharacterSet() const {
    return (((1ull << this->Key) & 0x828c1800u) != 0); }

  //! This is true for all VRs whose value is stored as text.
  bool HasTextValue() const {
    return (((1ull << this->Key) & 0xa78c1cf6u) != 0); }

  //! This is true for for all VRs that store numbers.
  /*!
   *  The VRs included are IS, DS, US, UL, SS, SL, FL, FD.  The VRs
   *  OB, OW, OF, OL, and OD are not included.
   */
  bool HasNumericValue() const {
    return (((1ull << this->Key) & 0x48500740u) != 0); }

  //! The VRs ST, LT, and UT carry only one value.
  /*!
   * Specifically, this means that a backslash is not interpreted as a
   * value separator in these VRs. UR is not included, because backslash
   * is an illegal character in UR.
   */
  bool HasSingleValue() const {
    return (((1ull << this->Key) & 0x80801000u) != 0); }

  bool operator==(vtkDICOMVR a) const { return (this->Key == a.Key); }
  bool operator!=(vtkDICOMVR a) const { return (this->Key != a.Key); }
  bool operator<=(vtkDICOMVR a) const { return (this->Key <= a.Key); }
  bool operator>=(vtkDICOMVR a) const { return (this->Key >= a.Key); }
  bool operator<(vtkDICOMVR a) const { return (this->Key < a.Key); }
  bool operator>(vtkDICOMVR a) const { return (this->Key > a.Key); }

private:
  unsigned char Key;

  static const unsigned char *VRTable[256];
  static const unsigned char TypeTable[34];
  static const char TextTable[34][4];
};

VTKDICOM_EXPORT ostream& operator<<(ostream& o, const vtkDICOMVR& a);

#endif /* vtkDICOMVR_h */
// VTK-HeaderTest-Exclude: vtkDICOMVR.h
