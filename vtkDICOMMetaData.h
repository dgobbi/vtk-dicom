#ifndef __vtkDICOMMetaData_h
#define __vtkDICOMMetaData_h

#include <vtkObject.h>

#include "vtkDICOMMetaDataDict.h"

class vtkDICOMMetaData : public vtkObject
{
public:
  static vtkDICOMMetaData *New();
  vtkTypeMacro(vtkDICOMMetaData, vtkObjectBase);

  void PrintSelf(ostream& os, vtkIndent indent);

  class Tag;

  struct Element;
  struct DictElement;

  Element *FindElement(Tag tag);
  void EraseElement(Tag tag);
  void InsertElement(
                     Tag tag, unsigned short vr, unsigned int vl, const char *data);
  Element *&FindElementSlot(Tag tag);
  static DictElement *FindDictElement(Tag tag);

  typedef DC::EnumType TagEnum;

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

private:
  Element ***Table;
  static DictElement ***DictHashTable;

  vtkDICOMMetaData(const vtkDICOMMetaData&);  // Not implemented.
  void operator=(const vtkDICOMMetaData&);  // Not implemented.
};

class vtkDICOMMetaData::Tag
{
public:
  Tag(int group, int element)
    {
    this->T2.Group = static_cast<unsigned short>(group);
    this->T2.Element = static_cast<unsigned short>(element);
    }

  Tag(vtkDICOMMetaData::TagEnum tag)
    {
    this->T1 = static_cast<unsigned int>(tag);
    }

  unsigned int GetKey()
    {
    return this->T1;
    }

  unsigned int GetHash()
    {
    return ((this->T1 >> 6) ^ (this->T1 >> 8) ^ (this->T1 << 2));
    }

private:
  Tag() {};

  union
    {
    unsigned int T1;
    struct
      {
#ifdef VTK_WORDS_BIGENDIAN
      unsigned short Group;
      unsigned short Element;
#else
      unsigned short Element;
      unsigned short Group;
#endif
      }
    T2;
    };

  friend bool operator==(const Tag& a, const Tag& b);
};

inline bool operator==(const vtkDICOMMetaData::Tag& a, const vtkDICOMMetaData::Tag& b)
{
  return (a.T1 == b.T1);
};

struct vtkDICOMMetaData::Element
{
  Element(Tag t, unsigned short r, unsigned int l, const char *d)
  : tag(t), vr(r), vl(l), data(d) {}

  Tag tag;
  unsigned short vr;
  size_t vl;
  const char *data;
};

struct vtkDICOMMetaData::DictElement
{
  unsigned int tag;
  unsigned short vr;
  unsigned short vm;
  const char *name;
};

#endif /* __vtkDICOMMetaData_h */
