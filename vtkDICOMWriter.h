/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDICOMWriter - Write DICOM image files.
// .SECTION Description
// This class writes a series of one or more DICOM files.  The default
// behavior is to write a single multi-frame Secondary Capture file
// with no modality-specific information.
// .SECTION Thanks
// This class was contributed to VTK by David Gobbi.

#ifndef __vtkDICOMWriter_h
#define __vtkDICOMWriter_h

#include <vtkImageWriter.h>
#include "vtkDICOMModule.h"

class vtkMatrix4x4;
class vtkDICOMMetaData;
class vtkDICOMGenerator;

class VTK_DICOM_EXPORT vtkDICOMWriter : public vtkImageWriter
{
public:
  // Description:
  // Static method for construction.
  static vtkDICOMWriter *New();
  vtkTypeMacro(vtkDICOMWriter, vtkImageWriter);

  // Description:
  // Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set a short description (max 64 chars) for the DICOM series.
  // The default description is "VTKX.Y" where X.Y is the VTK version.
  vtkSetStringMacro(SeriesDescription);
  vtkGetStringMacro(SeriesDescription);

  // Description:
  // Write scalar components as the time dimension (default: Off).
  // If this is on, the writer assumes that each time slot is stored
  // in a different scalar component of the image data.  If it is off,
  // the writer assumes that each block of N adjacent slices correspond
  // to the N time slots of the time dimension.
  vtkSetMacro(TimeAsVector, int);
  vtkBooleanMacro(TimeAsVector, int);
  vtkGetMacro(TimeAsVector, int);

  // Description:
  // Set the time dimension to use in the DICOM file (or zero if none).
  // The number of components of the input data must be divisible by the time
  // dimension if the time dimension is not set to zero.  The vector dimension
  // will be set to the number of components divided by the time dimension.
  // This will be ignored if the SOP Class IOD does not permit a time
  // dimension.
  vtkSetMacro(TimeDimension, int);
  vtkGetMacro(TimeDimension, int);
  vtkSetMacro(TimeSpacing, double);
  vtkGetMacro(TimeSpacing, double);

  // Description:
  // Set the matrix that places the image in DICOM patient coords.
  // The 3x3 portion of the matrix must be orthonormal, and the
  // last column of the matrix is understood to be in millimetres.
  void SetPatientMatrix(vtkMatrix4x4 *);
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

  // Description:
  // Set the meta data to include with the file.
  // The supplied meta data is only used as a hint, the writer
  // will override attributes that aren't valid for the image.
  void SetMetaData(vtkDICOMMetaData *);
  vtkDICOMMetaData *GetMetaData();

protected:
  vtkDICOMWriter();
  ~vtkDICOMWriter();

  // Description:
  // Compute the name of one of the output files.
  void ComputeInternalFileName(int slice);

  // Description:
  // The main execution method, which writes the file.
  virtual int RequestData(vtkInformation *request,
                          vtkInformationVector** inputVector,
                          vtkInformationVector* outputVector);

  // Description:
  // Validate the DICOM SOP Common Module.
  bool ValidateSOPCommonModule(vtkDICOMMetaData *meta);

  // Description:
  // Validate the DICOM Patient Module.
  bool ValidatePatientModule(vtkDICOMMetaData *meta);

  // Description:
  // Validate the DICOM Study Module.
  bool ValidateGeneralStudyModule(vtkDICOMMetaData *meta);

  // Description:
  // Validate the DICOM Series Module.
  bool ValidateGeneralSeriesModule(vtkDICOMMetaData *meta);

  // Description:
  // Validate the DICOM Image Module.
  bool ValidateGeneralImageModule(vtkDICOMMetaData *meta);

  // Description:
  // Validate the DICOM Pixel Module.
  bool ValidateImagePixelModule(
    vtkDICOMMetaData *meta, vtkInformation *info);

  // Description:
  // Validate The DICOM Multi-frame Functional Groups Module
  bool ValidateMultiFrameFunctionalGroupsModule(
    vtkDICOMMetaData *meta, vtkInformation *info);

  // Description:
  // Validate the SC Image Module.
  bool ValidateSCImageModule(vtkDICOMMetaData *meta);

  // Description:
  // Validate the SC Equipment Module.
  bool ValidateSCEquipmentModule(vtkDICOMMetaData *meta);

  // Description:
  // Compute aspect ratio from spacing.
  static void ComputeAspectRatio(const double spacing[2], int aspect[2]);

  // Description:
  // The meta data.
  vtkDICOMMetaData *MetaData;

  // Description:
  // The modality-specific generator for the DICOM data object.
  vtkDICOMGenerator *Generator;

  // Description:
  // Whether time is stored in slices or in scalar components.
  int TimeAsVector;

  // Description:
  // Time dimension to use in the file.
  int TimeDimension;
  double TimeSpacing;

  // Description:
  // The orientation matrix for the DICOM file.
  vtkMatrix4x4 *PatientMatrix;

  // Description:
  // A description of how the file was produced.
  char *SeriesDescription;

  // Description:
  // The row order to use when storing the data in memory.
  int MemoryRowOrder;

private:
  vtkDICOMWriter(const vtkDICOMWriter&);  // Not implemented.
  void operator=(const vtkDICOMWriter&);  // Not implemented.
};

#endif // __vtkDICOMWriter_h
