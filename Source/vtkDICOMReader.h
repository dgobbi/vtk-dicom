/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * \class vtkDICOMReader
 * \brief Read DICOM image files.
 *
 * This class reads a series of DICOM files into a vtkImageData object,
 * and also provides access to the DICOM meta data for each file.
 */

#ifndef vtkDICOMReader_h
#define vtkDICOMReader_h

#include <vtkImageReader2.h>
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMCharacterSet.h" // For character sets

class vtkIntArray;
class vtkTypeInt64Array;
class vtkStringArray;
class vtkMatrix4x4;
class vtkMedicalImageProperties;
class vtkDICOMMetaData;
class vtkDICOMParser;
class vtkDICOMSliceSorter;

//----------------------------------------------------------------------------
class VTKDICOM_EXPORT vtkDICOMReader : public vtkImageReader2
{
public:
  vtkTypeMacro(vtkDICOMReader, vtkImageReader2);

  //! Static method for construction.
  static vtkDICOMReader *New();

  //! Print information about this object.
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
#endif

#ifdef VTK_OVERRIDE
  //@{
  //! Valid extensions for this file type.
  const char* GetFileExtensions() VTK_OVERRIDE {
    return ".dcm .dc"; }

  //! Return a descriptive name that might be useful in a GUI.
  const char* GetDescriptiveName() VTK_OVERRIDE {
    return "DICOM"; }

  //! Return true if this reader can read the given file.
  int CanReadFile(const char* filename) VTK_OVERRIDE;
  //@}
#else
  //@{
  //! Valid extensions for this file type.
  const char* GetFileExtensions() {
    return ".dcm .dc"; }

  //! Return a descriptive name that might be useful in a GUI.
  const char* GetDescriptiveName() {
    return "DICOM"; }

  //! Return true if this reader can read the given file.
  int CanReadFile(const char* filename);
  //@}
#endif

  //@{
  //! Set the Stack ID of the stack to load, for named stacks.
  /*!
   *  If the series has multiple stacks, then by default the reader
   *  will only load the first stack.  This method allows you to select
   *  a different stack, if you know the DICOM StackID for the stack.
   */
  void SetDesiredStackID(const char *stackId);
  const char *GetDesiredStackID() { return this->DesiredStackID; }

  //! Get a list of the stacks that are present in the input files.
  /*!
   *  A stack is a contiguous array of slices that form a volume.
   */
  vtkStringArray *GetStackIDs() { return this->StackIDs; }
  //@}

  //@{
  //! Get an array that converts slice index to input file index.
  /*!
   *  If the reader has generated scalar components, then this will
   *  be a two-dimensional array and calling array->GetComponent(i,j)
   *  will return the file index for slice i and scalar component j
   *  for monochrome images, or for slice i and scalar component 3*j
   *  for RGB images (or more precisely, at scalar component N*j where
   *  N is the SamplesPerPixel value from the DICOM metadata).  If the
   *  data has just one component, then use j=0. If you used SetFileNames()
   *  to provide a list of files to the reader, then use this array to
   *  find out which file provided which slice, or to index into the
   *  MetaData object to get the metadata for a particular slice.
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
  //! Get the meta data for the DICOM files.
  /*!
   *  The Get() method of vtkDICOMMataData takes optional file and frame
   *  indices, which specify the file and the frame within that file to
   *  get the attribute from.  If you have a slice index rather than a
   *  file index and frame index, then use the FileIndexArray and
   *  FrameIndexArray to convert the slice index into file and frame indices.
   */
  vtkDICOMMetaData *GetMetaData() { return this->MetaData; }
  //@}

  //@{
  //! Set the character set to use if SpecificCharacterSet is missing.
  /*!
   *  Some DICOM files do not list a SpecificCharacterSet attribute, but
   *  neverthless use a non-ASCII character encoding.  This method can be
   *  used to specify the character set in absence of SpecificCharacterSet.
   *  This method will not take effect unless is is called before the image
   *  is read.  If SpecificCharacterSet is present, the default will not
   *  override it unless OverrideCharacterSet is true.
   */
  void SetDefaultCharacterSet(vtkDICOMCharacterSet cs);
  vtkDICOMCharacterSet GetDefaultCharacterSet() {
    return this->DefaultCharacterSet; }

  //! Override the value stored in SpecificCharacterSet.
  /*!
   *  This method can be used if the SpecificCharacterSet attribute of a
   *  file is incorrect.  It overrides the SpecificCharacterSet with the
   *  DefaultCharacterSet.
   */
  vtkSetMacro(OverrideCharacterSet, bool);
  vtkBooleanMacro(OverrideCharacterSet, bool);
  bool GetOverrideCharacterSet() {
    return this->OverrideCharacterSet; }
  //@}

  //@{
  //! If the files have been pre-sorted, the sorting can be disabled.
  vtkGetMacro(Sorting, int);
  vtkSetMacro(Sorting, int);
  vtkBooleanMacro(Sorting, int)
  //@}

  //@{
  //! Set a custom sorter to be used to sort files and frames into slices.
  /*!
   *  The default sorter uses the attributes "ImagePositionPatient" and
   *  "ImageOrientationPatient" to spatially arrange the slices.
   */
  void SetSorter(vtkDICOMSliceSorter *sorter);
  vtkDICOMSliceSorter *GetSorter() { return this->Sorter; }
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
  //! Turn off automatic conversion of YBR images to RGB.
  /*!
   *  By default, YBR images are always converted to RGB (though the
   *  photometric interpretation in the metadata will remain the same).
   */
  vtkGetMacro(AutoYBRToRGB, int);
  vtkSetMacro(AutoYBRToRGB, int);
  vtkBooleanMacro(AutoYBRToRGB, int);
  //@}

  //@{
  //! Turn off automatic rescaling of stored pixel values.
  /*!
   *  By default, if the RescaleSlope and RescaleIntercept attributes
   *  are present in the DICOM data set, they will be used to rescale
   *  stored pixel values according to the DICOM modality LUT operation.
   *  The resulting values will be stored as 16-bit integers if possible,
   *  but single-precision floats will be used if the potential output
   *  range is greater than can be stored in 16 bits, or if either the
   *  RescaleSlope or the RescaleIntercept is not an integer.
   *  If AutoRescale is off, then the data is not rescaled.
   */
  vtkGetMacro(AutoRescale, int);
  vtkSetMacro(AutoRescale, int);
  vtkBooleanMacro(AutoRescale, int);
  //@}

  //@{
  //! Get the slope and intercept for rescaling the scalar values.
  /*!
   *  If AutoRescale in On (which is the default), then GetRescaleSlope()
   *  will return 1 and GetRescaleIntercept() will return zero.  Otherwise,
   *  they will return the RescaleSlope and RescaleIntercept for the data
   *  set. Use the equation v = u*RescaleSlope + RescaleIntercept.
   *
   *  Note that the returned values might not be valid if these attributes
   *  are not the same for all slices in the series.  Use the meta data to
   *  retrieve the per-slice slope and intercept.
   */
  double GetRescaleSlope() { return this->RescaleSlope; }
  double GetRescaleIntercept() { return this->RescaleIntercept; }
  //@}

  //@{
  //! Get a matrix to place the image within DICOM patient coords.
  /*!
   *  This matrix is constructed from the ImageOrientationPatient
   *  and ImagePositionPatient meta data attributes.  See the
   *  SetMemoryRowOrder method for additional information.
   */
  vtkMatrix4x4 *GetPatientMatrix() { return this->PatientMatrix; }
  //@}

  //@{
  //! Get the overlay.
  /*!
   *  The extent of the overlay will be the same as the main image.
   *  For multiple overlays, each overlay will be stored in a different
   *  bit. An 8-bit image will be used if there are eight or fewer
   *  overlays, and an unsigned 16-bit image will be used if there are
   *  more than eight overlays.
   */
  vtkImageData *GetOverlayOutput();
  vtkAlgorithmOutput *GetOverlayOutputPort();

  //! Returns true if any overlays are present.
  bool HasOverlay() { return (this->OverlayBitfield != 0); }

  //! Returns a bitfield that indicates which overlays are present.
  int GetOverlayBitfield() { return this->OverlayBitfield; }
  //@}

  //@{
  //! Get a MedicalImageProperties object for this file.
  vtkMedicalImageProperties *GetMedicalImageProperties();
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

  //@{
  //! Set the scalar type of the output.
  /*!
   *  The default value is -1, which means that the input scalar type will
   *  be used to set the output scalar type (accounting for any type
   *  changes required by AutoRescale).  Allowed output scalar types are
   *  VTK_SIGNED_CHAR, VTK_UNSIGNED_CHAR, VTK_SHORT, VTK_UNSIGNED_SHORT,
   *  VTK_INT, VTK_UNSIGNED_INT, VTK_FLOAT, or VTK_DOUBLE.  The output
   *  data values will be clamped to the limits of the output type.
   */
  vtkSetMacro(OutputScalarType, int);
  vtkGetMacro(OutputScalarType, int);
  //@}

  //@{
  using Superclass::Update;
  //! Update both the image and, if present, the overlay
#ifdef VTK_OVERRIDE
  void Update() VTK_OVERRIDE;
#else
  virtual void Update();
#endif
  //@}

protected:
  vtkDICOMReader();
  ~vtkDICOMReader();

#ifdef VTK_OVERRIDE
  //@{
  //! Entry point for all pipeline requests.
  int ProcessRequest(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  //! Read the header information.
  int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  //! Read the voxel data.
  int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;
  //@}
#else
  //@{
  //! Entry point for all pipeline requests.
  virtual int ProcessRequest(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  //! Read the header information.
  virtual int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  //! Read the voxel data.
  virtual int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);
  //@}
#endif

  //@{
  //! Read the overlays into an allocated vtkImageData object.
  virtual bool ReadOverlays(vtkImageData *data);

  //! Unpack overlay bits to build the overlay image.
  void UnpackOverlay(
    const void *filePtr, vtkIdType bitskip, vtkIdType count,
    void *buffer, vtkIdType incr, int bit);
  //@}

  //@{
  //! Read one file.  Specify the offset to the PixelData.
  virtual bool ReadOneFile(
    const char *filename, int idx,
    unsigned char *buffer, vtkIdType bufferSize);

  //! Unpack 1 bit to 8 bits or 12 bits to 16 bits.
  void UnpackBits(
    const void *source, void *buffer, vtkIdType bufferSize, int bits);

  //! Read an DICOM file directly.
  virtual bool ReadFileNative(
    const char *filename, int idx,
    unsigned char *buffer, vtkIdType bufferSize);

  //! Read a DICOM file via DCMTK or GDCM.
  virtual bool ReadFileDelegated(
    const char *filename, int idx,
    unsigned char *buffer, vtkIdType bufferSize);
  //@}

  //@{
  //! Check if rescaling will change scalar type.
  virtual int ComputeRescaledScalarType(
    int scalarType, int bitsStored, int pixelRepresentation);

  //! Rescale the data in the buffer.
  virtual void RescaleBuffer(
    int fileIdx, int frameIdx, int fileType, int outputType,
    int numFileComponents, int numComponents,
    void *fileBuffer, void *outputBuffer, vtkIdType bufferSize);

  //! Convert buffer from YUV to RGB.
  virtual void YBRToRGB(
    int fileIdx, int frameIdx, void *buffer, vtkIdType bufferSize);
  //@}

  //@{
  //! Convert parser errors into reader errors.
  void RelayError(vtkObject *o, unsigned long e, void *data);
  //@}

  //@{
  //! Verify that the files can be composed into a volume.
  /*!
   *  This is called after SortFiles has been called.  It should invoke an
   *  error event and return zero upon failure.
   */
  virtual bool ValidateStructure(
    vtkIntArray *fileArray, vtkIntArray *frameArray);

  //! Sort the input files, put the sort in the supplied arrays.
  virtual void SortFiles(vtkIntArray *fileArray, vtkIntArray *frameArray);

  //! Do not sort the files, just build the arrays.
  void NoSortFiles(vtkIntArray *fileArray, vtkIntArray *frameArray);
  //@}

  //@{
  //! Update the medical image properties;
  virtual void UpdateMedicalImageProperties();
  //@}

  //! Select whether to sort the files.
  int Sorting;

  //! Information for rescaling data to quantitative units.
  double RescaleIntercept;
  double RescaleSlope;

  //! The orientation matrix for the DICOM file.
  vtkMatrix4x4 *PatientMatrix;

  //! The meta data for the image.
  vtkDICOMMetaData *MetaData;

  //! The MedicalImageProperties, for compatibility with other readers.
  vtkMedicalImageProperties *MedicalImageProperties;

  //! The default character set to use while parsing the file.
  vtkDICOMCharacterSet DefaultCharacterSet;

  //! Whether the default should override SpecificCharacterSet.
  bool OverrideCharacterSet;

  //! The parser that is used to read the file.
  vtkDICOMParser *Parser;

  //! The sorter that orders the slices within the volume.
  vtkDICOMSliceSorter *Sorter;

  //! The offsets to the pixel data in each file.
  vtkTypeInt64Array *FileOffsetArray;

  //! An array to convert slice indices to input files
  vtkIntArray *FileIndexArray;

  //! An array to convert slice indices to input frames
  vtkIntArray *FrameIndexArray;

  //! An array that holds the stack IDs.
  vtkStringArray *StackIDs;

  //! The row order to use when storing the data in memory.
  int MemoryRowOrder;

  //! This indicates that the data must be rescaled.
  int NeedsRescale;
  int AutoRescale;
  int FileScalarType;
  int OutputScalarType;

  //! This indicates that the data must be converted to RGB.
  int NeedsYBRToRGB;
  int AutoYBRToRGB;

  //! The number of packed pixel components in the input file.
  /*!
   *  This is for packed, rather than planar, components.
   */
  int NumberOfPackedComponents;

  //! The number of color planes in the file.
  int NumberOfPlanarComponents;

  //! Time dimension variables.
  int TimeAsVector;
  int TimeDimension;
  int DesiredTimeIndex;
  double TimeSpacing;

  //! The stack to load.
  char DesiredStackID[20];

  //! Bitfield that says what overlays are present.
  int OverlayBitfield;

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMReader(const vtkDICOMReader&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMReader&) VTK_DELETE_FUNCTION;
#else
  vtkDICOMReader(const vtkDICOMReader&);
  void operator=(const vtkDICOMReader&);
#endif
};

#endif // vtkDICOMReader_h
