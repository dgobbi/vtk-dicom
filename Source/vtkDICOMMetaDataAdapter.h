/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMMetaDataAdapter_h
#define vtkDICOMMetaDataAdapter_h

#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMTag.h"

class vtkDICOMMetaData;
class vtkDICOMValue;

//! An adapter to make multi-frame data look like multi-file data.
/*!
 *  The vtkDICOMMetaDataAdapter object makes an enhanced multi-frame
 *  DICOM data set appear to be a series of data sets.  Whenever the
 *  caller requests and attribute from a specific instance, the attribute
 *  is instead pulled from the PerFrame item for a specific frame.
 *  If constructed from a metadata object that is not an enhanced
 *  multi-frame dataset, it simply acts as a pass-through.
 */
class VTKDICOM_EXPORT vtkDICOMMetaDataAdapter
{
public:
  //@{
  //! Construct an adapter for the given meta data object.
  /*!
   *  If the provided meta-data is from an enhanced multi-frame data set,
   *  then the adapter will make it look like a series of data sets.  If
   *  the provided meta-data is from a series of non-enhanced data sets,
   *  the adapter will act as a simple pass-through.
   */
  vtkDICOMMetaDataAdapter(vtkDICOMMetaData *meta);

  //! Construct an adapter for one DICOM object instance.
  /*!
   *  If instance i of the provided meta-data is an enhanced multi-frame
   *  data set, make it look like a series.
   */
  vtkDICOMMetaDataAdapter(vtkDICOMMetaData *meta, int i);

  //! Copy constructor.
  vtkDICOMMetaDataAdapter(const vtkDICOMMetaDataAdapter&);

  //! Destructor release the reference to the meta data.
  ~vtkDICOMMetaDataAdapter();
  //@}

  //@{
  //! Get the number of instances (i.e. files).
  /*!
   *  For an enhanced multi-frame data set, this will return the
   *  number of frames.  For a non-enhanced data set, it returns
   *  the number of instances in the series.
   */
  int GetNumberOfInstances() const { return this->NumberOfInstances; }
  //@}

  //@{
  //! Check whether an attribute is present in the metadata.
  /*!
   *  For an enhanced multi-frame data set, this will search the Shared
   *  and PerFrameFunctionGroupSequence in addition to searching the basic
   *  data set attributes.
   */
  bool Has(vtkDICOMTag tag) const;
  bool HasAttribute(vtkDICOMTag tag) const {
    return this->Has(tag); }

  //! Get an attribute value.
  /*!
   *  For an enhanced multi-frame data set, this will first try to
   *  retrieve the attribute from the SharedFunctionalGroupSequence.
   */
  const vtkDICOMValue &Get(vtkDICOMTag tag) const;
  const vtkDICOMValue &GetAttributeValue(vtkDICOMTag tag) const {
    return this->Get(tag); }

  //! Get an attribute value for the specified file index.
  /*!
   *  For an enhanced multi-frame data set, this will search the PerFrame
   *  attributes, then the Shared attributes, and finally the basic
   *  data set attributes.
   */
  const vtkDICOMValue &Get(int idx, vtkDICOMTag tag) const;
  const vtkDICOMValue &GetAttributeValue(int idx, vtkDICOMTag tag) const {
    return this->Get(idx, tag); }

  //! Resolve a private tag.
  /*!
   *  For an enhanced multi-frame data set, this will search the PerFrame
   *  attributes, then the Shared attributes, and finally the basic
   *  data set attributes.
   */
  vtkDICOMTag ResolvePrivateTag(vtkDICOMTag ptag, const std::string& creator);
  vtkDICOMTag ResolvePrivateTag(
    int idx, vtkDICOMTag ptag, const std::string& creator);
  //@}

  //@{
  //! Make the adapter look like a pointer (for convenience).
  const vtkDICOMMetaDataAdapter* operator->() const { return this; }
  vtkDICOMMetaDataAdapter* operator->() { return this; }
  //@}

  //! Copy constructor.
  vtkDICOMMetaDataAdapter& operator=(const vtkDICOMMetaDataAdapter&);

protected:
  //! Helper function for the constructors.  Set all members.
  void ConstructionHelper(vtkDICOMMetaData *meta, int i);

private:

  vtkDICOMMetaData *Meta;
  const vtkDICOMValue *PerFrame;
  const vtkDICOMValue *Shared;
  vtkDICOMValue *NullValue;
  int NumberOfInstances;
  int MetaInstance;
};

#endif /* vtkDICOMMetaDataAdapter_h */
// VTK-HeaderTest-Exclude: vtkDICOMMetaDataAdapter.h
