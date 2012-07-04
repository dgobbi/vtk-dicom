#ifndef __vtkDICOMVR_h
#define __vtkDICOMVR_h

#include <vtkSystemIncludes.h>

//! VRs (Value Representations)
class vtkDICOMVR
{
public:
  //! The VR enum constants.
  /*!
   *  The two bytes in the 16-bit VRs constants are ordered so that
   *  sorting the constants numerically will sort the VRs alphabetically.
   */
  enum EnumType
  {
    AE = 0x4145, //!< Application Entity
    AS = 0x4153, //!< Age String
    AT = 0x4154, //!< Attribute Tag
    CS = 0x4353, //!< Code String
    DA = 0x4441, //!< Date
    DS = 0x4453, //!< Decimal String
    DT = 0x4454, //!< Date Time
    FD = 0x4644, //!< Floating Point Double
    FL = 0x464c, //!< Floating Point Single
    IS = 0x4953, //!< Integer String
    LO = 0x4c4f, //!< Long String
    LT = 0x4c54, //!< Long Text
    OB = 0x4f42, //!< Other Byte
    OF = 0x4f46, //!< Other Float
    OW = 0x4f57, //!< Other Word
    PN = 0x504e, //!< Personal Name
    SH = 0x5348, //!< Short String
    SL = 0x534c, //!< Signed Long
    SQ = 0x5351, //!< Sequence of Items
    SS = 0x5353, //!< Signed Short
    ST = 0x5354, //!< Short Text
    TM = 0x544d, //!< Time
    UI = 0x5549, //!< Unique Identifier
    UL = 0x554c, //!< Unsigned Long
    UN = 0x554e, //!< Unknown
    US = 0x5553, //!< Unsigned Short
    UT = 0x5554, //!< Unlimited Text
    OX = 0x4f58, //!< Either OB or OW (for dict entries, not data elements)
    XS = 0x5853, //!< Either SS or US (for dict entries, not data elements)
  };

  vtkDICOMVR(EnumType vr) : Key(static_cast<unsigned short>(vr)) {};
  vtkDICOMVR() : Key(UN) {};

  bool operator==(vtkDICOMVR a) const { return (this->Key == a.Key); }
  bool operator!=(vtkDICOMVR a) const { return (this->Key != a.Key); }
  bool operator<=(vtkDICOMVR a) const { return (this->Key <= a.Key); }
  bool operator>=(vtkDICOMVR a) const { return (this->Key >= a.Key); }
  bool operator<(vtkDICOMVR a) const { return (this->Key < a.Key); }
  bool operator>(vtkDICOMVR a) const { return (this->Key > a.Key); }

private:
  unsigned short Key;

  friend ostream& operator<<(ostream& o, const vtkDICOMVR& a);
};

ostream& operator<<(ostream& o, const vtkDICOMVR& a);

#endif /* __vtkDICOMVR_h */
