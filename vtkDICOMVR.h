/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMVR_h
#define __vtkDICOMVR_h

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
    OF = 0x0e, //!< Other Float
    OW = 0x0f, //!< Other Word
    PN = 0x10, //!< Personal Name
    SH = 0x11, //!< Short String
    SL = 0x12, //!< Signed Long
    SQ = 0x13, //!< Sequence of Items
    SS = 0x14, //!< Signed Short
    ST = 0x15, //!< Short Text
    TM = 0x16, //!< Time
    UI = 0x17, //!< Unique Identifier
    UL = 0x18, //!< Unsigned Long
    UN = 0x19, //!< Unknown
    US = 0x1a, //!< Unsigned Short
    UT = 0x1b, //!< Unlimited Text
    OX = 0x1c, //!< Either OB or OW (for dict entries, not data elements)
    XS = 0x1d, //!< Either SS or US (for dict entries, not data elements)
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

  //! The VRs OB, OF, OW, SQ, UN, UT require a 32-bit VL.
  bool HasLongVL() const { return (((1 << this->Key) & 0x0a08e000) != 0); }

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

#endif /* __vtkDICOMVR_h */
