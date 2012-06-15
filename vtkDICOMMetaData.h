#ifndef __vtkDICOMMetaData_h
#define __vtkDICOMMetaData_h

#include <vtkObject.h>

#include "vtkDICOMMetaDataDict.h"

// Get an element from the hash table.
#define DICT_HASH_TABLE_SIZE 1024

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
  void InsertElement(Tag tag, unsigned short vr, unsigned int vl,
                     const char *data);
  Element *&FindElementSlot(Tag tag);
  static DictElement *FindDictElement(Tag tag);

  typedef DC::EnumType TagEnum;

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

private:
  Element ***Table;
  static DictElement *DictHashTable[DICT_HASH_TABLE_SIZE];

  vtkDICOMMetaData(const vtkDICOMMetaData&);  // Not implemented.
  void operator=(const vtkDICOMMetaData&);  // Not implemented.
};

class vtkDICOMMetaData::Tag
{
public:
  Tag(int group, int element)
    {
    this->tg = static_cast<unsigned short>(group);
    this->te = static_cast<unsigned short>(element);
    }

  Tag(vtkDICOMMetaData::TagEnum tag)
    {
    this->tg = static_cast<unsigned short>(tag >> 16);
    this->te = static_cast<unsigned short>(tag);
    }

  unsigned int group()
    {
    return this->tg;
    }

  unsigned int element()
    {
    return this->te;
    }

  unsigned int hash()
    {
    return (((this->tg >> 6) ^ this->tg) ^ ((this->te >> 6) ^ this->te));
    }

private:
  Tag() {};

  unsigned short tg;
  unsigned short te;

  friend bool operator==(const Tag& a, const Tag& b);
};

inline bool operator==(const vtkDICOMMetaData::Tag& a, const vtkDICOMMetaData::Tag& b)
{
  return (a.tg == b.tg && a.te == b.te);
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
  unsigned short tg;
  unsigned short te;
  unsigned short vr;
  unsigned short vm;
  const char *name;
};

#endif /* __vtkDICOMMetaData_h */
