/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMMetaData_h
#define __vtkDICOMMetaData_h

#include <vtkDataObject.h>
#include "vtkDICOMModule.h"
#include "vtkDICOMDataElement.h"
#include "vtkDICOMDictEntry.h"

#include <string>

class vtkDICOMTagPath;

//! A container class for DICOM metadata.
/*!
 *  The vtkDICOMMetaData object stores DICOM metadata in a hash table
 *  for efficient access.  One vtkDICOMMetaData object can store the
 *  metadata for a series of DICOM images.
 */
class VTK_DICOM_EXPORT vtkDICOMMetaData : public vtkDataObject
{
public:
  //! Create a new vtkDICOMMetaData instance.
  static vtkDICOMMetaData *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMMetaData, vtkDataObject);

  //! Print a summary of the contents of this object.
  void PrintSelf(ostream& os, vtkIndent indent);

  //! Get the number of instances (i.e. files).
  /*!
   *  We want to track the metadata from all of the files that
   *  make up the image volume that we have loaded into VTK.
   *  This method gives the number of files used to construct
   *  this meta data.  All the files should be from the same
   *  series.
   */
  int GetNumberOfInstances() { return this->NumberOfInstances; }
  void SetNumberOfInstances(int n);

  //! Clear the metadata, initialize the structure.
  void Clear();
  void Initialize() { this->Clear(); }

  //! Get the number of data elements that are present.
  int GetNumberOfDataElements() {
    return this->NumberOfDataElements; }

  //! Get an iterator for the list of data elements.
  vtkDICOMDataElementIterator Begin() {
    return this->Head.Next; }

  //! Get an end iterator for the list of data elements.
  vtkDICOMDataElementIterator End() {
    return &this->Tail; }

  //! Get the iterator for a specific data element.
  /*!
   *  If the element was not found, then End() will be returned.
   */
  vtkDICOMDataElementIterator Find(vtkDICOMTag tag) {
    vtkDICOMDataElement *e = this->FindDataElement(tag);
    return (e != 0 ? e : &this->Tail); }

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
  const vtkDICOMValue &GetAttributeValue(const vtkDICOMTagPath &p);

  //! Get an attribute value for the specified file index.
  /*!
   *  If this meta data object is used to hold the meta data for
   *  multiple image instances, then use this method to get an
   *  attribute value for a specific instance.  If the attribute
   *  is not present, the value will be invalid, i.e. v.IsValid()
   *  will be false.
   */
  const vtkDICOMValue &GetAttributeValue(int idx, vtkDICOMTag tag);
  const vtkDICOMValue &GetAttributeValue(int idx, const vtkDICOMTagPath &p);

  //! Get an attribute value for the specified file and frame index.
  /*!
   *  For enhanced multi-frame DICOM files, much of the meta data is
   *  stored per-frame.  This method will search for the attribute
   *  in the PerFrameFunctionGroupSequence first, then in the
   *  SharedFunctionalGroupsSequence, and finally in the root.
   *  It can be used on either multi-frame or single-frame files.
   *  The frame index is counted from zero to NumberOfFrames-1.
   */
  const vtkDICOMValue &GetAttributeValue(int idx, int frame, vtkDICOMTag tag);
  const vtkDICOMValue &GetAttributeValue(
    int idx, int frame, const vtkDICOMTagPath &p);

  //! Set an attribute value for the image at file index "idx".
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

  //! Look up a tag in the DICOM dictionary.
  /*!
   *  Unlike the method in vtkDICOMDictionary, this method can identify
   *  the implementor of a private tag and look it up in the implementor's
   *  dictionary.
   */
  vtkDICOMDictEntry FindDictEntry(vtkDICOMTag tag);

  //! Use the dictionary to get the VR, return UN if not found.
  vtkDICOMVR FindDictVR(int idx, vtkDICOMTag tag);

  //! Copy all the attributes from another MetaData object.
  /*!
   *  Copy attributes from the source meta data object into this one.
   *  If the source has the same NumberOfInstances as this, then the
   *  attributes are copied on an instance-by-instance basis.  Otherwise,
   *  attributes are only copied from the source if they have the same
   *  value for all instances.
   */
  void CopyAttributes(vtkDICOMMetaData *source);

  //! DataObject interface function.
  void ShallowCopy(vtkDataObject *source);
  void DeepCopy(vtkDataObject *source);

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

  //! Find a tag, value pair.
  vtkDICOMDataElement *FindDataElement(vtkDICOMTag tag);

  //! Find a tag, value pair or insert a pair if not found.
  vtkDICOMDataElement *FindDataElementOrInsert(vtkDICOMTag tag);

  //! Find the attribute value for the specified image index.
  const vtkDICOMValue *FindAttributeValue(int idx, vtkDICOMTag tag);

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

  vtkDICOMMetaData(const vtkDICOMMetaData&);  // Not implemented.
  void operator=(const vtkDICOMMetaData&);  // Not implemented.
};

#endif /* __vtkDICOMMetaData_h */
