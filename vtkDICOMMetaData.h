#ifndef __vtkDICOMMetaData_h
#define __vtkDICOMMetaData_h

#include <vtkObject.h>

#include "vtkDICOMDataElement.h"
#include "vtkDICOMDictEntry.h"

//! The size of the hash table for the dicom dictionary.
#define DICT_HASH_TABLE_SIZE 1024

//! A container class for DICOM metadata.
/*!
 *  The vtkDICOMMetaData object stores DICOM metadata in a hash table
 *  for efficient access.  One vtkDICOMMetaData object can store the
 *  metadata for a series of DICOM images.
 */
class vtkDICOMMetaData : public vtkObject
{
public:
  //! Create a new vtkDICOMMetaData instance.
  static vtkDICOMMetaData *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMMetaData, vtkObjectBase);

  //! Print a summary of the contents of this object.
  void PrintSelf(ostream& os, vtkIndent indent);

  //! Set the number of instances (i.e. files).
  /*!
   *  We want to track the metadata from all of the files that
   *  make up the image volume that we have loaded into VTK.
   *  The number of file instances must be set here before any
   *  attributes are set.  All the files should be from the same
   *  series.
   */
  void SetNumberOfInstances(int n);
  int GetNumberOfInstances() { return this->NumberOfInstances; }

  //! Clear the metadata, initialize the structure.
  void Clear();

  //! Get the number of data elements that are present.
  int GetNumberOfDataElements() {
    return this->NumberOfDataElements; }

  //! Get an iterator for the list of data elements.
  vtkDICOMDataElementIterator GetDataElementIterator() {
    return this->Head.Next; }

  //! Get an end iterator for the list of data elements.
  vtkDICOMDataElementIterator GetDataElementIteratorEnd() {
    return &this->Tail; }

  //! Check whether an attribute is present in the metadata.
  bool HasAttribute(vtkDICOMTag tag);

  //! Erase an attribute.
  void RemoveAttribute(vtkDICOMTag tag);

  //! Get an attribute value.
  /*!
   *  The tag will usually be specified in one of these two ways:
   *  GetAttributeValue(vtkDICOMTag(0x0008,0x1030)) or, using the
   *  dictionary enum type, GetAttributeValue(DC::StudyDescription).
   *  If the attribute is not present, then the returned value will
   *  be invalid, i.e. v.IsValid() will be false.
   */
  const vtkDICOMValue &GetAttributeValue(vtkDICOMTag tag);

  //! Get an attribute value for the specified slice index.
  /*!
   *  If this meta data object is used to hold the meta data for
   *  multiple image instances, then use this method to get an
   *  attribute value for a specific instance.  If the attribute
   *  is not present, the value will be invalid, i.e. v.IsValid()
   *  will be false.
   */
  const vtkDICOMValue &GetAttributeValue(int idx, vtkDICOMTag tag);

  //! Set an attribute value for the image at index "idx".
  /*!
   *  Except for the method that takes a vtkDICOMValue, these methods
   *  will use the dictionary to find the VR for the attribute, and will
   *  attempt to convert the input data to the correct VR.  Strings and
   *  doubles will be converted to integer values where necessary, and
   *  numeric values will be converted to strings where necessary.
   */
  void SetAttributeValue(int idx, vtkDICOMTag tag, const vtkDICOMValue& v);
  void SetAttributeValue(int idx, vtkDICOMTag tag, double v);
  void SetAttributeValue(int idx, vtkDICOMTag tag, const std::string& v);

  //! Set the same attribute value for all images.
  void SetAttributeValue(vtkDICOMTag tag, const vtkDICOMValue& v);
  void SetAttributeValue(vtkDICOMTag tag, double v);
  void SetAttributeValue(vtkDICOMTag tag, const std::string& v);

  //! Find the dictionary entry for the given tag.
  static bool FindDictEntry(vtkDICOMTag tag, vtkDICOMDictEntry& e);

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

  //! Find a tag, value pair.
  vtkDICOMDataElement *FindDataElement(vtkDICOMTag tag);

  //! Find a tag, value pair or insert a pair if not found.
  vtkDICOMDataElement *FindDataElementOrInsert(vtkDICOMTag tag);

  //! Find the attribute value for the specified image index.
  const vtkDICOMValue *FindAttributeValue(int idx, vtkDICOMTag tag);

  //! Use the dictionary to get the VR.
  vtkDICOMVR FindDictVR(int idx, vtkDICOMTag tag);

  //! Internal templated SetAttributeValue method
  template<class T>
  void SetAttributeValueT(vtkDICOMTag tag, T v);
  template<class T>
  void SetAttributeValueT(int idx, vtkDICOMTag tag, T v);

private:
  //! The number of DICOM files.
  int NumberOfInstances;

  //! The lookup table for the metadata.
  vtkDICOMDataElement **Table;

  //! Links to the first data element.
  vtkDICOMDataElement Head;

  //! Links to the last data element.
  vtkDICOMDataElement Tail;

  //! The number of data elements.
  int NumberOfDataElements;

  //! The lookup table for the dictionary.
  static vtkDICOMDictEntry::Internal *DictHashTable[DICT_HASH_TABLE_SIZE];

  //! An invalid value, for when one is needed.
  static const vtkDICOMValue InvalidValue;

  vtkDICOMMetaData(const vtkDICOMMetaData&);  // Not implemented.
  void operator=(const vtkDICOMMetaData&);  // Not implemented.
};

#endif /* __vtkDICOMMetaData_h */
