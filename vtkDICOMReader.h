/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDICOMReader - Read DICOM image files.
// .SECTION Description
// This class reads a series of DICOM files into a vtkImageData object,
// and also provides access to the DICOM meta data for each file.
// .SECTION Thanks
// This class was contributed to VTK by David Gobbi.

#ifndef __vtkDICOMReader_h
#define __vtkDICOMReader_h

#include <vtkImageReader2.h>
#include "vtkDICOMModule.h"

class vtkIntArray;
class vtkTypeInt64Array;
class vtkMatrix4x4;
class vtkDICOMMetaData;
class vtkDICOMParser;

//----------------------------------------------------------------------------
class VTK_DICOM_EXPORT vtkDICOMReader : public vtkImageReader2
{
public:
  // Description:
  // Static method for construction.
  static vtkDICOMReader *New();
  vtkTypeMacro(vtkDICOMReader, vtkImageReader2);

  // Description:
  // Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Valid extensions for this file type.
  virtual const char* GetFileExtensions() {
    return ".dcm .dc"; }

  // Description:
  // Return a descriptive name that might be useful in a GUI.
  virtual const char* GetDescriptiveName() {
    return "DICOM"; }

  // Description:
  // Return true if this reader can read the given file.
  int CanReadFile(const char* filename);

  // Description:
  // Get an array that converts slice index to input file index.
  // If the data has multiple scalar components, then this will
  // be a two-dimensional array and calling array->GetComponent(i,j)
  // will return the file index for slice i and scalar component j.
  // If you used SetFileNames() to provide a list of files to the reader,
  // use this array to find out which file provided which slice.
  vtkIntArray *GetFileIndexArray() { return this->FileIndexArray; }

  // Description:
  // Get the meta data for the DICOM files.
  // The GetAttributeValue() method of vtkDICOMMataData takes an optional
  // index, which specifies the file to get the attribute from.  If you
  // have a slice index rather than a file index, then use the FileIndexArray
  // to convert the slice index into a file index.
  vtkDICOMMetaData *GetMetaData() { return this->MetaData; }

  // Description:
  // Read the time dimension as scalar components (default: Off).
  // If this is on, then each time point will be stored as a scalar
  // component in the image data.  If the data has both a time dimension
  // and a vector dimension, then the number of components will be the
  // product of these two dimensions, i.e. the components will store
  // a sequence of vectors, one vector for each time point.
  vtkGetMacro(TimeAsVector, int);
  vtkSetMacro(TimeAsVector, int);
  vtkBooleanMacro(TimeAsVector, int);

  // Description:
  // Get the time dimension if the DICOM series has one.
  int GetTimeDimension() { return this->TimeDimension; }
  double GetTimeSpacing() { return this->TimeSpacing; }

  // Description:
  // Get the slope and intercept for rescaling the scalar values.
  // These values allow calibration of the data to real values.
  // Use the equation v = u*RescaleSlope + RescaleIntercept.
  double GetRescaleSlope() { return this->RescaleSlope; }
  double GetRescaleIntercept() { return this->RescaleIntercept; }

  // Description:
  // Get a matrix to place the image within DICOM patient coords.
  // This matrix is constructed from the ImageOrientationPatient
  // and ImagePositionPatient meta data attributes.  See the
  // SetMemoryRowOrder method for additional information.
  vtkMatrix4x4 *GetPatientMatrix() { return this->PatientMatrix; }

  // Description:
  // Enumeration for top-down vs. bottom-up ordering.
  enum RowOrder { FileNative, TopDown, BottomUp };

  // Description:
  // Set the ordering of the image rows in memory.
  // If the order is BottomUp (which is the default) then
  // the images will be flipped when they are read from disk.
  // The native orientation of DICOM images is top-to-bottom.
  void SetMemoryRowOrder(int order);
  void SetMemoryRowOrderToFileNative() {
    this->SetMemoryRowOrder(FileNative); }
  void SetMemoryRowOrderToTopDown() {
    this->SetMemoryRowOrder(TopDown); }
  void SetMemoryRowOrderToBottomUp() {
    this->SetMemoryRowOrder(BottomUp); }
  int GetMemoryRowOrder() { return this->MemoryRowOrder; }
  const char *GetMemoryRowOrderAsString();

protected:
  vtkDICOMReader();
  ~vtkDICOMReader();

  // Description:
  // Read the header information.
  virtual int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  // Description:
  // Read the voxel data.
  virtual int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  // Description:
  // Read one file.  Specify the offset to the PixelData.
  bool ReadOneFile(
    const char *filename, int idx, char *buffer, vtkIdType bufferSize);

  // Description:
  // Read an uncompressed DICOM file.
  bool ReadUncompressedFile(
    const char *filename, int idx, char *buffer, vtkIdType bufferSize);

  // Description:
  // Read an uncompressed DICOM file.
  bool ReadCompressedFile(
    const char *filename, int idx, char *buffer, vtkIdType bufferSize);

  // Description:
  // Rescale the data in the buffer.
  void RescaleBuffer(
    int idx, void *buffer, vtkIdType bufferSize);

  // Description:
  // Convert parser errors into reader errors.
  void RelayError(vtkObject *o, unsigned long e, void *data);

  // Description:
  // Sort the input files, put the sort in the supplied array.
  void SortFiles(vtkIntArray *result);

  // Description:
  // Information for rescaling data to quantitative units.
  double RescaleIntercept;
  double RescaleSlope;

  // Description:
  // The orientation matrix for the DICOM file.
  vtkMatrix4x4 *PatientMatrix;

  // Description:
  // The meta data for the image.
  vtkDICOMMetaData *MetaData;

  // Description:
  // The parser that is used to read the file.
  vtkDICOMParser *Parser;

  // Description:
  // The offsets to the pixel data in each file.
  vtkTypeInt64Array *FileOffsetArray;

  // Description:
  // An array to convert slice indices to input files
  vtkIntArray *FileIndexArray;

  // Description:
  // The row order to use when storing the data in memory.
  int MemoryRowOrder;

  // Description:
  // This indicates that the data must be rescaled.
  int NeedsRescale;

  // Description:
  // The number of packed pixel components in the input file.
  // This is for packed, rather than planar. components.
  int NumberOfPackedComponents;

  // Description:
  // Time dimension variables.
  int TimeAsVector;
  int TimeDimension;
  double TimeSpacing;

private:
  vtkDICOMReader(const vtkDICOMReader&);  // Not implemented.
  void operator=(const vtkDICOMReader&);  // Not implemented.
};

#endif // __vtkDICOMReader_h
