/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMMetaData_h
#define vtkDICOMMetaData_h

#include <vtkDataObject.h>
#include <vtkStdString.h> // For std::string
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMDataElement.h" // For method parameter
#include "vtkDICOMDictEntry.h" // For method parameter

class vtkIntArray;
class vtkDICOMTagPath;

//! A container class for DICOM metadata.
/*!
 *  The vtkDICOMMetaData object stores DICOM metadata in a hash table
 *  for efficient access.  One vtkDICOMMetaData object can store the
 *  metadata for a series of DICOM images.
 */
class VTKDICOM_EXPORT vtkDICOMMetaData : public vtkDataObject
{
public:
  //! Create a new vtkDICOMMetaData instance.
  static vtkDICOMMetaData *New();

  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMMetaData, vtkDataObject);

  //! Print a summary of the contents of this object.
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

  //@{
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
  //@}

  //@{
  //! Remove all data elements.
  void Clear();

  //! Remove all data elements and initialize all members.
  void Initialize() VTK_OVERRIDE;
  //@}

  //@{
  //! Get the number of data elements that are present.
  int GetNumberOfDataElements() {
    return this->NumberOfDataElements; }

  //! Get an iterator for the list of data elements.
  vtkDICOMDataElementIterator Begin() {
    return this->Head.Next; }

  //! Get an end iterator for the list of data elements.
  vtkDICOMDataElementIterator End() {
    return &this->Tail; }
  //@}

  //@{
  //! Get the iterator for a specific data element.
  /*!
   *  If the element was not found, then End() will be returned.
   */
  vtkDICOMDataElementIterator Find(vtkDICOMTag tag) {
    vtkDICOMDataElement *e = this->FindDataElement(tag);
    return (e != 0 ? e : &this->Tail); }
  //@}

  //@{
  //! Check whether an attribute is present in the metadata.
  bool HasAttribute(vtkDICOMTag tag);

  //! Erase an attribute.
  void RemoveAttribute(vtkDICOMTag tag);
  //@}

  //@{
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
  //@}

  //@{
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
  //@}

  //@{
  //! Get an attribute value for the specified file and frame index.
  /*!
   *  In order to get the file and frame index for a particular slice
   *  of a volume, use the GetFileIndex() and GetFrameIndex() methods.
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
  //@}

  //@{
  //! Get the file index for the given image slice and component.
  /*!
   *  This takes into account the way the files were sorted to create
   *  the volume (as given by the FileIndexArray).  For multi-component
   *  images, supply both the component of interest, and the total number
   *  of components.  The return value will be -1 if an index is out of
   *  range.
   */
  int GetFileIndex(int sliceIdx, int compIdx, int numComps);
  int GetFileIndex(int sliceIdx);
  //@}

  //@{
  //! Get the frame index for the given image slice and component.
  /*!
   *  This takes into account the way the frames were sorted to create
   *  the volume (as given by the FileIndexArray).  For multi-component
   *  images, supply both the component of interest, and the total number
   *  of components.  The return value will be -1 if an index is out of
   *  range.
   */
  int GetFrameIndex(int sliceIdx, int compIdx, int numComps);
  int GetFrameIndex(int sliceIdx);
  //@}

  //@{
  //! Set an attribute value for the image at file index "idx".
  /*!
   *  Except for the method that takes a vtkDICOMValue, these methods
   *  will use the dictionary to find the VR for the attribute, and will
   *  attempt to convert the input data to the correct VR.  Strings and
   *  doubles will be converted to integer values where necessary, and
   *  numeric values will be converted to strings where necessary.
   *  Note that if you specify a string value, it must either be an
   *  ASCII string, or it must be encoded in the SpecificCharacterSet
   *  for this data set.
   */
  void SetAttributeValue(int idx, vtkDICOMTag tag, const vtkDICOMValue& v);
  void SetAttributeValue(int idx, vtkDICOMTag tag, double v);
  void SetAttributeValue(int idx, vtkDICOMTag tag, const std::string& v);
  //@}

  //@{
  //! Set the same attribute value for all images.
  void SetAttributeValue(vtkDICOMTag tag, const vtkDICOMValue& v);
  void SetAttributeValue(vtkDICOMTag tag, double v);
  void SetAttributeValue(vtkDICOMTag tag, const std::string& v);
  //@}

  //@{
  //! Set the attribute at the specified path.
  /*!
   *  The data element is inserted at the tail of the given path.  If the
   *  path lies within a sequence that does not yet exist, then the sequence
   *  will be created.  If an item index in the path points to an item that
   *  does not exist, then that item will be created.
   */
  void SetAttributeValue(
    int idx, const vtkDICOMTagPath& tag, const vtkDICOMValue& v);
  void SetAttributeValue(
    int idx, const vtkDICOMTagPath& tag, double v);
  void SetAttributeValue(
    int idx, const vtkDICOMTagPath& tag, const std::string& v);
  //@}

  //@{
  //! Set the attribute value along this path for all images.
  void SetAttributeValue(const vtkDICOMTagPath& tag, const vtkDICOMValue& v);
  void SetAttributeValue(const vtkDICOMTagPath& tag, double v);
  void SetAttributeValue(const vtkDICOMTagPath& tag, const std::string& v);
  //@}

  //@{
  //! Resolve a private tag, or return (ffff,ffff) if not resolved.
  /*!
   *  Private data elements are mobile, which means that different data
   *  sets might store them at different locations.  Given a private
   *  data element which has a tag of (gggg,xxee) according to its
   *  dictionary, the first two element digits "xx" can change from one
   *  data set to the next, and the data set must have a "Creator Element"
   *  at (gggg,00xx) to allow the digits of "xx" to be resolved.  Please
   *  read DICOM Part 5 Section 7.8 for additional information.
   */
  vtkDICOMTag ResolvePrivateTag(vtkDICOMTag ptag, const std::string& creator);

  //! Resolve a private tag, and add the creator to the data set.
  /*!
   *  This method works like ResolvePrivateTag, except that if the creator
   *  is not found in the data set, it will be added.  It should be used to
   *  resolve private tags that you plan to write to the data set.  The
   *  returned tag will be (ffff,ffff) if there are no empty slots available
   *  for the creator.  Every private group has 240 available slots.
   */
  vtkDICOMTag ResolvePrivateTagForWriting(
    vtkDICOMTag ptag, const std::string& creator);
  //@}

  //@{
  //! Look up a tag in the DICOM dictionary.
  /*!
   *  Unlike the method in vtkDICOMDictionary, this method can identify
   *  the implementor of a private tag and look it up in the implementor's
   *  dictionary.
   */
  vtkDICOMDictEntry FindDictEntry(vtkDICOMTag tag);

  //! Use the dictionary to get the VR, return UN if not found.
  vtkDICOMVR FindDictVR(int idx, vtkDICOMTag tag);
  //@}

  //@{
  //! Create a value from text in a specific character set.
  vtkDICOMValue MakeValueWithSpecificCharacterSet(
    vtkDICOMVR vr, const std::string& v);
  //@}

  //@{
  //! Set the array to convert slice, component indices to file index.
  void SetFileIndexArray(vtkIntArray *fileArray);
  vtkIntArray *GetFileIndexArray() { return this->FileIndexArray; }
  //@}

  //@{
  //! Set the array to convert slice, component indices to frame index.
  void SetFrameIndexArray(vtkIntArray *frameArray);
  vtkIntArray *GetFrameIndexArray() { return this->FrameIndexArray; }
  //@}

  //@{
  //! Copy all the attributes from another MetaData object.
  /*!
   *  Copy attributes from the source meta data object into this one.
   *  If the source has the same NumberOfInstances as this, then the
   *  attributes are copied on an instance-by-instance basis.  Otherwise,
   *  attributes are only copied from the source if they have the same
   *  value for all instances.
   */
  void CopyAttributes(vtkDICOMMetaData *source);
  //@}

  //@{
  //! DataObject interface function.
  void ShallowCopy(vtkDataObject *source) VTK_OVERRIDE;
  void DeepCopy(vtkDataObject *source) VTK_OVERRIDE;
  //@}

protected:
  vtkDICOMMetaData();
  ~vtkDICOMMetaData();

  //! Find a tag, value pair.
  vtkDICOMDataElement *FindDataElement(vtkDICOMTag tag);

  //! Find a tag, value pair or insert a pair if not found.
  vtkDICOMDataElement *FindDataElementOrInsert(vtkDICOMTag tag);

  //! Find or create the sequence at the head of the tagpath.
  int FindItemsOrInsert(
    int idx, bool useidx, const vtkDICOMTagPath& tagpath,
    vtkDICOMItem *items[]);

  //! Find a child item for a tag path, or insert if not there.
  vtkDICOMItem *FindItemOrInsert(int idx, const vtkDICOMTagPath& tagpath);

  //! Find the attribute value for the specified image index.
  const vtkDICOMValue *FindAttributeValue(int idx, vtkDICOMTag tag);

  //! Find the attribute value for the specified image index.
  const vtkDICOMValue *FindAttributeValue(
    int idx, const vtkDICOMTagPath& tagpath);

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

  //! An array to map slices and components to files.
  vtkIntArray *FileIndexArray;

  //! An array to map slices and components to frames.
  vtkIntArray *FrameIndexArray;

  vtkDICOMMetaData(const vtkDICOMMetaData&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMMetaData&) VTK_DELETE_FUNCTION;
};

#endif /* vtkDICOMMetaData_h */
