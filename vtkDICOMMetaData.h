#ifndef __vtkDICOMMetaData_h
#define __vtkDICOMMetaData_h

#include <vtkObject.h>

#include "vtkDICOMMetaDataDict.h"

//! The size of the hash table for the dicom dictionary.
#define DICT_HASH_TABLE_SIZE 1024

//! A container class for DICOM metadata.
/*!
 *  The vtkDICOMMetaData object stores DICOM metadata elements
 *  in a lookup table.  The FindElement() method will return an
 *  element, given a DICOM tag, or will return NULL if that element
 *  is not found.  Likewise, DICOM dictionary lookups can be done
 *  with the FindDictElement() method.
 */
class vtkDICOMMetaData : public vtkObject
{
public:
  class Tag;
  struct Element;
  struct DictElement;

  //! Create a new vtkDICOMMetaData instance.
  static vtkDICOMMetaData *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMMetaData, vtkObjectBase);

  //! Print a summary of the contents of this object.
  void PrintSelf(ostream& os, vtkIndent indent);

  //! Find an element, given a tag.
  /*!
   *  This will return an element, or NULL if no element was found for
   *  the supplied tag.  There are two ways that this method can be
   *  called:  FindElement(Tag(0x0008,0x1030)) or, using DC::EnumType,
   *  FindElement(DC::StudyDescription).
   */
  Element *FindElement(Tag tag);

  //! Erase an element.
  void EraseElement(Tag tag);

  //! Construct and insert an element (text only, for now).
  void InsertElement(Tag tag, unsigned short vr, unsigned int vl,
                     const char *data);

  //! Find the dictionary entry for the given tag.
  static DictElement *FindDictElement(Tag tag);

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

  //! Get the address of the element for this tag.
  /*!
   *  This will either return the address of an existing element,
   *  or an address at which a new element can be inserted.
   */
  Element **FindElementLocation(Tag tag);

private:
  //! The lookup table for the metadata.
  Element ***Table;

  //! The lookup table for the dictionary.
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

  Tag(DC::EnumType tag)
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
