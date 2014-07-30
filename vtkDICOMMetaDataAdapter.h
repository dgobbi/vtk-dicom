/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMMetaDataAdapter_h
#define __vtkDICOMMetaDataAdapter_h

#include "vtkDICOMModule.h"
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
class VTK_DICOM_EXPORT vtkDICOMMetaDataAdapter
{
public:
  //! Construct an adapter for the given meta data object.
  vtkDICOMMetaDataAdapter(vtkDICOMMetaData *meta);

  //! Destructor release the reference to the meta data.
  ~vtkDICOMMetaDataAdapter();

  //! Get the number of instances (i.e. files).
  /*!
   *  For an enhanced multi-frame data set, this will return the
   *  number of frames.  For a non-enhanced data set, it returns
   *  the number of instances in the series.
   */
  int GetNumberOfInstances() const { return this->NumberOfInstances; }

  //! Check whether an attribute is present in the metadata.
  /*!
   *  For an enhanced multi-frame data set, this will search the Shared
   *  and PerFrameFunctionGroupSequence in addition to searching the basic
   *  data set attributes.
   */
  bool HasAttribute(vtkDICOMTag tag) const;

  //! Get an attribute value.
  /*!
   *  For an enhanced multi-frame data set, this will first try to
   *  retrieve the attribute from the SharedFunctionalGroupSequence.
   */
  const vtkDICOMValue &GetAttributeValue(vtkDICOMTag tag) const;

  //! Get an attribute value for the specified file index.
  /*!
   *  For an enhanced multi-frame data, this will search the PerFrame
   *  attributes, then the Shared attributes, and finally the basic
   *  data set attributes.
   */
  const vtkDICOMValue &GetAttributeValue(int idx, vtkDICOMTag tag) const;

  //! Make the adapter look like a pointer (for convenience).
  const vtkDICOMMetaDataAdapter* operator->() const { return this; }
  vtkDICOMMetaDataAdapter* operator->() { return this; }

private:

  vtkDICOMMetaData *Meta;
  const vtkDICOMValue *PerFrame;
  const vtkDICOMValue *Shared;
  vtkDICOMValue *NullValue;
  int NumberOfInstances;
};

#endif /* __vtkDICOMMetaDataAdapter_h */
