#ifndef __vtkDICOMTag_h
#define __vtkDICOMTag_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMDictionary.h"

//! A (group,element) identifier tag for DICOM attributes.
class vtkDICOMTag
{
public:
  vtkDICOMTag() : Group(0), Element(0) {}

  //! Construct a tag from group, element numbers.
  vtkDICOMTag(int group, int element) :
    Group(static_cast<unsigned short>(group)) ,
    Element(static_cast<unsigned short>(element)) {}

  //! Construct a tag from an identifier from the DICOM dictionary.
  vtkDICOMTag(DC::EnumType tag) :
    Group(static_cast<unsigned short>(tag >> 16)) ,
    Element(static_cast<unsigned short>(tag)) {}

  //! Get the 16-bit group identifier.
  unsigned short GetGroup() const { return this->Group; }

  //! Get the 16-bit element identifier.
  unsigned short GetElement() const { return this->Element; }

  //! Compute a hash value, used for accelerating lookups.
  unsigned int ComputeHash() const
  {
    return (((this->Group >> 6) ^ this->Group) ^
            ((this->Element >> 6) ^ this->Element));
  }

  inline bool operator==(const vtkDICOMTag& b) const
  {
    return (this->Group == b.Group && this->Element == b.Element);
  }

  inline bool operator!=(const vtkDICOMTag& b) const
  {
    return (this->Group != b.Group || this->Element != b.Element);
  }

  inline bool operator<=(const vtkDICOMTag& b) const
  {
    return (static_cast<unsigned int>((this->Group << 16) | this->Element) <=
            static_cast<unsigned int>((b.Group << 16) | b.Element));
  }

  inline bool operator>=(const vtkDICOMTag& b) const
  {
    return (static_cast<unsigned int>((this->Group << 16) | this->Element) >=
            static_cast<unsigned int>((b.Group << 16) | b.Element));
  }

  inline bool operator<(const vtkDICOMTag& b) const
  {
    return (static_cast<unsigned int>((this->Group << 16) | this->Element) <
            static_cast<unsigned int>((b.Group << 16) | b.Element));
  }

  inline bool operator>(const vtkDICOMTag& b) const
  {
    return (static_cast<unsigned int>((this->Group << 16) | this->Element) >
            static_cast<unsigned int>((b.Group << 16) | b.Element));
  }

private:
  unsigned short Group;
  unsigned short Element;

  friend ostream& operator<<(ostream& o, const vtkDICOMTag& a);
};

ostream& operator<<(ostream& o, const vtkDICOMTag& a);

#endif /* __vtkDICOMTag_h */
