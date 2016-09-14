/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*! \class vtkDICOMWriter
 *  \brief Write DICOM image files.
 *
 *  This class writes a series of one or more DICOM files.  The default
 *  behavior is to write a series of Secondary Capture files with no
 *  modality-specific information.  To write other kinds of DICOM files,
 *  use the SetGenerator() method to supply a generator for the type of
 *  data set that you wish to write.  Currently, there are generators for
 *  MR and CT data sets.
 */

#ifndef vtkDICOMWriter_h
#define vtkDICOMWriter_h

#include <vtkImageWriter.h>
#include "vtkDICOMModule.h" // For export macro

class vtkMatrix4x4;
class vtkDICOMMetaData;
class vtkDICOMGenerator;

class VTKDICOM_EXPORT vtkDICOMWriter : public vtkImageWriter
{
public:
  vtkTypeMacro(vtkDICOMWriter, vtkImageWriter);

  //! Static method for construction.
  static vtkDICOMWriter *New();

  //! Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  //@{
  //! Set a short description (max 64 chars) for the DICOM series.
  /*!
   *  The default description is "VTKX.Y" where X.Y is the VTK version.
   */
  vtkSetStringMacro(SeriesDescription);
  vtkGetStringMacro(SeriesDescription);
  //@}

  //@{
  //! Set the image type, using a series of DICOM code strings.
  /*!
   *  This must follow the DICOM standard, an error will be generated
   *  if it doesn't.  The default value is DERIVED/SECONDARY/OTHER,
   *  where the forward-slashes will be replaced by backslashes when
   *  the attribute is written.  Set this to NULL if you wish to use
   *  the original ImageType.
   */
  vtkSetStringMacro(ImageType);
  vtkGetStringMacro(ImageType);
  //@}

  //@{
  //! Write scalar components as the time dimension (default: Off).
  /*!
   *  If this is on, the writer assumes that each time slot is stored
   *  in a different scalar component of the image data.  If it is off,
   *  the writer assumes that each block of N adjacent slices correspond
   *  to the N time slots of the time dimension.
   */
  vtkSetMacro(TimeAsVector, int);
  vtkBooleanMacro(TimeAsVector, int);
  vtkGetMacro(TimeAsVector, int);
  //@}

  //@{
  //! Set the time dimension to use in the DICOM file (or zero if none).
  /*!
   *  The number of components of the input data must be divisible by the time
   *  dimension if the time dimension is not set to zero.  The vector dimension
   *  will be set to the number of components divided by the time dimension.
   *  This will be ignored if the SOP Class IOD does not permit a time
   *  dimension.
   */
  vtkSetMacro(TimeDimension, int);
  vtkGetMacro(TimeDimension, int);
  vtkSetMacro(TimeSpacing, double);
  vtkGetMacro(TimeSpacing, double);
  //@}

  //@{
  //! Set the parameters to rescale integer pixel values into real values.
  /*!
   *  These parameters are the intercept and slope int the equation v = m*x + b
   *  that converts the stored pixel values to real units such as Hounsfield
   *  units.  Most modalities (including MR) ignore these values, while certain
   *  modalities (such as CT) require them.
   */
  vtkSetMacro(RescaleIntercept, double);
  vtkGetMacro(RescaleIntercept, double);
  vtkSetMacro(RescaleSlope, double);
  vtkGetMacro(RescaleSlope, double);
  //@}

  //@{
  //! Set the matrix that places the image in DICOM patient coords.
  /*!
   *  The 3x3 portion of the matrix must be orthonormal, and the
   *  last column of the matrix is understood to be in millimetres.
   */
  void SetPatientMatrix(vtkMatrix4x4 *);
  vtkMatrix4x4 *GetPatientMatrix() { return this->PatientMatrix; }
  //@}

  //! Enumeration for top-down vs. bottom-up ordering.
  enum RowOrder { FileNative, TopDown, BottomUp };

  //@{
  //! Set the ordering of the image rows in memory.
  /*!
   *  If the order is BottomUp (which is the default) then
   *  the images will be flipped when they are read from disk.
   *  The native orientation of DICOM images is top-to-bottom.
   */
  void SetMemoryRowOrder(int order);
  void SetMemoryRowOrderToFileNative() {
    this->SetMemoryRowOrder(FileNative); }
  void SetMemoryRowOrderToTopDown() {
    this->SetMemoryRowOrder(TopDown); }
  void SetMemoryRowOrderToBottomUp() {
    this->SetMemoryRowOrder(BottomUp); }
  int GetMemoryRowOrder() { return this->MemoryRowOrder; }
  const char *GetMemoryRowOrderAsString();
  //@}

  //! Enumeration for file order.
  enum SliceOrder { RHR, LHR, Same, Reverse };

  //@{
  //! Set the slice ordering of the files to be written.
  /*!
   *  The default is RHR (right-hand-rule), which means that if your
   *  right thumb points along an image row, and your index finger points
   *  down a row (starting at the top left of the image), then a bent middle
   *  finger points in the direction of increasing slice index.  LHR is the
   *  reverse of this.  Same keeps files in the same order as VTK slices.
   */
  void SetFileSliceOrder(int order);
  void SetFileSliceOrderToRHR() { this->SetFileSliceOrder(RHR); }
  void SetFileSliceOrderToLHR() { this->SetFileSliceOrder(LHR); }
  void SetFileSliceOrderToSame() { this->SetFileSliceOrder(Same); }
  void SetFileSliceOrderToReverse() { this->SetFileSliceOrder(Reverse); }
  int GetFileSliceOrder() { return this->FileSliceOrder; }
  const char *GetFileSliceOrderAsString();
  //@}

  //@{
  //! Set the meta data to include with the file.
  /*!
   *  The supplied meta data is only used as a hint, the writer
   *  will override attributes that aren't valid for the image.
   */
  void SetMetaData(vtkDICOMMetaData *);
  vtkDICOMMetaData *GetMetaData();
  //@}

  //@{
  //! Set the generator for image modality you wish to write.
  /*!
   *  The generator combines the image information from VTK with the
   *  supplied MetaData to create the DICOM data series that will be
   *  written to disk.  The default generator will write a Secondary
   *  Capture series, rather than a series belonging to a specific
   *  imaging modality.
   */
  void SetGenerator(vtkDICOMGenerator *);
  vtkDICOMGenerator *GetGenerator() { return this->Generator; }
  //@}

  //@{
  //! Set the Transfer Syntax UID.
  /*!
   *  Setting the transfer syntax is an experimental feature.  If not
   *  set, the transfer syntax will be 1.2.840.10008.1.2.1 (uncompressed
   *  little-endian with explicit VR).
   */
  vtkSetStringMacro(TransferSyntaxUID);
  vtkGetStringMacro(TransferSyntaxUID);
  //@}

  //@{
  //! Turn on streaming, to pass one slice though the pipeline at a time.
  /*!
   *  Streaming decreases memory usage for images with a large number of
   *  slices, since only one slice will have to be in memory at a time.
   *  However, streaming can be slower (sometimes much slower) than
   *  reading and processing all of the slices at once.
   */
  vtkSetMacro(Streaming, int);
  vtkGetMacro(Streaming, int);
  vtkBooleanMacro(Streaming, int);
  //@}

  //@{
  //! Write the file to disk.
  virtual void Write();
  //@}

protected:
  vtkDICOMWriter();
  ~vtkDICOMWriter();

  //! Compute the name of one of the output files.
  void ComputeInternalFileName(int slice);

  //! Free the filename created by ComputeInternalFileName.
  void FreeInternalFileName();

  //! Generate the meta data to be written for the files.
  virtual int GenerateMetaData(vtkInformation *info);

  //! The main execution method, which writes the file.
  virtual int RequestData(vtkInformation *request,
                          vtkInformationVector** inputVector,
                          vtkInformationVector* outputVector);

  //! The meta data set by the user.
  vtkDICOMMetaData *MetaData;

  //! The meta data generated by the generator.
  vtkDICOMMetaData *GeneratedMetaData;

  //! The modality-specific generator for the DICOM data object.
  vtkDICOMGenerator *Generator;

  //! Whether time is stored in slices or in scalar components.
  int TimeAsVector;

  //! Time dimension to use in the file.
  int TimeDimension;
  double TimeSpacing;

  //! The parameters for rescaling the data to real values.
  double RescaleIntercept;
  double RescaleSlope;

  //! The orientation matrix for the DICOM file.
  vtkMatrix4x4 *PatientMatrix;

  //! A description of how the file was produced.
  char *SeriesDescription;

  //! The transfer syntax to use when writing the data.
  char *TransferSyntaxUID;

  //! The DICOM Image Type.
  char *ImageType;

  //! The row order to use when storing the data in memory.
  int MemoryRowOrder;

  //! The slice order to use when writing the files to disk.
  int FileSliceOrder;

  //! Whether to stream the data and write one file at a time.
  int Streaming;

private:
  vtkDICOMWriter(const vtkDICOMWriter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMWriter&) VTK_DELETE_FUNCTION;
};

#endif // vtkDICOMWriter_h
