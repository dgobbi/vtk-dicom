#ifndef __vtkDICOMMetaData_h
#define __vtkDICOMMetaData_h

#include <vtkObject.h>

#include "vtkDICOMMetaDataDict.h"
#include "vtkDICOMTag.h"

class vtkDICOMElement;

//! The size of the hash table for the dicom dictionary.
#define DICT_HASH_TABLE_SIZE 1024

//! A container class for DICOM metadata.
/*!
 *  The vtkDICOMMetaData object stores DICOM metadata elements
 *  in a lookup table.  The FindElement() method will return an
 *  element, given a DICOM tag, or will return NULL if that element
 *  is not found.  Likewise, DICOM dictionary lookups can be done
 *  with the FindDictEntry() method.
 */
class vtkDICOMMetaData : public vtkObject
{
public:
  struct DictEntry;

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
  vtkDICOMElement *FindElement(vtkDICOMTag tag);

  //! Erase an element.
  void EraseElement(vtkDICOMTag tag);

  //! Construct and insert an element (text only, for now).
  void InsertElement(vtkDICOMTag tag, vtkDICOMVR vr,
                     const char *data, vtkIdType l);

  //! Find the dictionary entry for the given tag.
  static DictEntry *FindDictEntry(vtkDICOMTag tag);

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

  //! Get the address of the element for this tag.
  /*!
   *  This will either return the address of an existing element,
   *  or an address at which a new element can be inserted.
   */
  vtkDICOMElement **FindElementLocation(vtkDICOMTag tag);

private:
  //! The lookup table for the metadata.
  vtkDICOMElement ***Table;

  //! The lookup table for the dictionary.
  static DictEntry *DictHashTable[DICT_HASH_TABLE_SIZE];

  vtkDICOMMetaData(const vtkDICOMMetaData&);  // Not implemented.
  void operator=(const vtkDICOMMetaData&);  // Not implemented.
};

struct vtkDICOMMetaData::DictEntry
{
  vtkDICOMTag GetTag() {
    return vtkDICOMTag(this->Group, this->Element); }
  vtkDICOMVR GetVR() {
    return vtkDICOMVR(static_cast<vtkDICOMVR::EnumType>(this->VR)); }
  vtkDICOMVM GetVM() {
    return vtkDICOMVM(static_cast<vtkDICOMVM::EnumType>(this->VM)); }
  const char *GetName() {
    return this->Name; }

  unsigned short Group;
  unsigned short Element;
  unsigned short VR;
  unsigned short VM;
  const char *Name;
};

#endif /* __vtkDICOMMetaData_h */
