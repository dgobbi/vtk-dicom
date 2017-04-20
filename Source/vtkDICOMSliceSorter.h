/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMSliceSorter_h
#define vtkDICOMSliceSorter_h

#include <vtkObject.h>
#include "vtkDICOMModule.h" // For export macro

class vtkIntArray;
class vtkStringArray;
class vtkDICOMMetaData;

//! Index a DICOM series to allow proper dimensional ordering.
/*!
 *  Given a vtkDICOMMetaData object for a DICOM series, this class will
 *  index the files and frames in the series so that they can be sorted
 *  into a multi-dimensional volume.
 */
class VTKDICOM_EXPORT vtkDICOMSliceSorter : public vtkObject
{
public:
  vtkTypeMacro(vtkDICOMSliceSorter,vtkObject);
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
#endif
  static vtkDICOMSliceSorter *New();

  //@{
  //! Set the Stack ID of the stack to use, for named stacks.
  /*!
   *  If the series has multiple stacks, then by default only the
   *  first stack will be used.  This method allows you to select
   *  a different stack, if you know the DICOM StackID for the stack.
   */
  void SetDesiredStackID(const char *stackId);
  const char *GetDesiredStackID() { return this->DesiredStackID; }

  //! Get a list of the stacks that are present.
  /*!
   *  A stack is a contiguous array of slices that form a volume.
   */
  vtkStringArray *GetStackIDs() { return this->StackIDs; }
  //@}

  //@{
  //! Get an array that converts slice index to input file index.
  /*!
   *  The array can be two-dimensional and calling array->GetComponent(i,j)
   *  will return the file index for slice i and scalar component j
   *  for monochrome images, or for slice i and scalar component 3*j
   *  for RGB images (or more precisely, at scalar component N*j where
   *  N is the SamplesPerPixel value from the DICOM metadata).  If the
   *  data has just one component, then use j=0.  Use this array to index
   *  into the MetaData object to get the metadata for a particular slice.
   */
  vtkIntArray *GetFileIndexArray() { return this->FileIndexArray; }

  //! Get an array that converts slice index to frame index.
  /*!
   *  The purpose of this array is to identify individual frames in
   *  multi-frame DICOM files.  The dimensions of this array are identical
   *  to the FileIndexArray.  Use FileIndexArray to identify the file,
   *  then use FrameIndexArray to identify the frame within that file.
   */
  vtkIntArray *GetFrameIndexArray() { return this->FrameIndexArray; }
  //@}

  //@{
  //! Set the meta data for the DICOM files.
  /*!
   *  The Get() method of vtkDICOMMetaData takes optional file and frame
   *  indices, which specify the file and the frame within that file to
   *  get the attribute from.  If you have a slice index rather than a file
   *  file index and frame index, then use the FileIndexArray and
   *  FrameIndexArray to convert the slice index into file and frame indices.
   */
  void SetMetaData(vtkDICOMMetaData *meta);
  vtkDICOMMetaData *GetMetaData() { return this->MetaData; }
  //@}

  //@{
  //! Read the time dimension as scalar components (default: Off).
  /*!
   *  If this is on, then each time point will be stored as a scalar
   *  component in the image data.  If the data has both a time dimension
   *  and a vector dimension, then the number of components will be the
   *  product of these two dimensions, i.e. the components will store
   *  a sequence of vectors, one vector for each time point.
   */
  vtkGetMacro(TimeAsVector, int);
  vtkSetMacro(TimeAsVector, int);
  vtkBooleanMacro(TimeAsVector, int);
  //@}

  //@{
  //! Get the time dimension if the DICOM series has one.
  int GetTimeDimension() { return this->TimeDimension; }
  double GetTimeSpacing() { return this->TimeSpacing; }
  //@}

  //@{
  //! Set the desired time index (set to -1 for all).
  vtkSetMacro(DesiredTimeIndex, int);
  vtkGetMacro(DesiredTimeIndex, int);
  //@}

  //@{
  //! Set whether to reverse the slice order.
  /*!
   *  This is desired if the images are to be flipped.
   */
  vtkGetMacro(ReverseSlices, int);
  vtkSetMacro(ReverseSlices, int);
  vtkBooleanMacro(ReverseSlices, int);
  //@}

  //@{
  //! Get the slice spacing for the volume.
  double GetSliceSpacing() { return this->SliceSpacing; }
  //@}

  //@{
  //! Update the arrays.
  void Update();
  //@}

protected:
  vtkDICOMSliceSorter();
  ~vtkDICOMSliceSorter();

  // Description:
  // Sort the input files, put the sort in the supplied arrays.
  virtual void SortFiles(vtkIntArray *fileArray, vtkIntArray *frameArray);

  // Description:
  // The meta data for the image.
  vtkDICOMMetaData *MetaData;

  // Description:
  // An array to convert slice indices to input files
  vtkIntArray *FileIndexArray;

  // Description:
  // An array to convert slice indices to input frames
  vtkIntArray *FrameIndexArray;

  // Description:
  // An array that holds the stack IDs.
  vtkStringArray *StackIDs;

  // Description:
  // Time dimension variables.
  int TimeAsVector;
  int TimeDimension;
  int DesiredTimeIndex;
  double TimeSpacing;

  // Description:
  // The stack to load.
  char DesiredStackID[20];

  // Description:
  // Whether to reverse the slice order.
  int ReverseSlices;
  double SliceSpacing;

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMSliceSorter(const vtkDICOMSliceSorter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMSliceSorter&) VTK_DELETE_FUNCTION;
#else
  vtkDICOMSliceSorter(const vtkDICOMSliceSorter&);
  void operator=(const vtkDICOMSliceSorter&);
#endif
};

#endif
