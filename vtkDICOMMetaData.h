#ifndef __vtkDICOMMetaData_h
#define __vtkDICOMMetaData_h

#include <vtkObject.h>

class vtkDICOMMetaData : public vtkObject
{
public:
  static vtkDICOMMetaData *New();
  vtkTypeMacro(vtkDICOMMetaData, vtkObjectBase);

  void PrintSelf(ostream& os, vtkIndent indent);

  class Tag;

  enum TagEnum
  {
    PatientName = 0x00100010,
    PatientID   = 0x00100020,
  };

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

  class Container;
  struct Element;

  Container *Contents;

private:
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

  unsigned int GetHash()
    {
    return (this->T1 ^ (this->T1 >> 12));
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

bool operator==(const vtkDICOMMetaData::Tag& a, const vtkDICOMMetaData::Tag& b)
{
  return (a.T1 == b.T1);
};

#endif /* __vtkDICOMMetaData_h */
