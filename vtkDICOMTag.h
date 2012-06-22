#ifndef __vtkDICOMTag_h
#define __vtkDICOMTag_h

#include "vtkDICOMMetaDataDict.h"

class vtkDICOMTag
{
public:
  vtkDICOMTag(int group, int element)
    {
    this->Group = static_cast<unsigned short>(group);
    this->Element = static_cast<unsigned short>(element);
    }

  vtkDICOMTag(DC::EnumType tag)
    {
    this->Group = static_cast<unsigned short>(tag >> 16);
    this->Element = static_cast<unsigned short>(tag);
    }

  unsigned short GetGroup()
    {
    return this->Group;
    }

  unsigned short GetElement()
    {
    return this->Element;
    }

  unsigned int ComputeHash()
    {
    return (((this->Group >> 6) ^ this->Group) ^
            ((this->Element >> 6) ^ this->Element));
    }

private:
  vtkDICOMTag() {};

  unsigned short Group;
  unsigned short Element;

  friend bool operator==(const vtkDICOMTag& a, const vtkDICOMTag& b);
};

inline bool operator==(const vtkDICOMTag& a, const vtkDICOMTag& b)
{
  return (a.Group == b.Group && a.Element == b.Element);
};

#endif /* __vtkDICOMTag_h */
