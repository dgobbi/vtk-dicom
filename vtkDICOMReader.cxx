/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMReader.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMDictionary.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkIntArray.h"
#include "vtkTypeInt64Array.h"
#include "vtkByteSwap.h"
#include "vtkMatrix4x4.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkStringArray.h"
#include "vtkMath.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"

#ifdef DICOM_USE_GDCM
#include "gdcmImageReader.h"
#endif

#include "vtksys/SystemTools.hxx"
#include "vtksys/ios/sstream"

#include <algorithm>
#include <iostream>
#include <math.h>
#include <sys/stat.h>


vtkStandardNewMacro(vtkDICOMReader);

//----------------------------------------------------------------------------
vtkDICOMReader::vtkDICOMReader()
{
  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;
  this->Parser = 0;
  this->FileIndexArray = vtkIntArray::New();
  this->FileOffsetArray = 0;
  this->MetaData = vtkDICOMMetaData::New();
  this->PatientMatrix = vtkMatrix4x4::New();
  this->MemoryRowOrder = vtkDICOMReader::BottomUp;

  this->DataScalarType = VTK_SHORT;
  this->NumberOfScalarComponents = 1;
  this->FileLowerLeft = 0;
  this->FileDimensionality = 2;
#ifdef VTK_WORDS_BIGENDIAN
  this->SwapBytes = 1;
#else
  this->SwapBytes = 0;
#endif
}

//----------------------------------------------------------------------------
vtkDICOMReader::~vtkDICOMReader()
{
  if (this->Parser)
    {
    this->Parser->Delete();
    }
  if (this->FileOffsetArray)
    {
    this->FileOffsetArray->Delete();
    }
  if (this->FileIndexArray)
    {
    this->FileIndexArray->Delete();
    }
  if (this->MetaData)
    {
    this->MetaData->Delete();
    }
  if (this->PatientMatrix)
    {
    this->PatientMatrix->Delete();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMReader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "MetaData: ";
  if (this->MetaData)
    {
    os << this->MetaData << "\n";
    }
  else
    {
    os << "(none)\n";
    }

  os << indent << "FileIndexArray: " << this->FileIndexArray << "\n";

  os << indent << "RescaleSlope: " << this->RescaleSlope << "\n";
  os << indent << "RescaleIntercept: " << this->RescaleIntercept << "\n";

  os << indent << "PatientMatrix:";
  if (this->PatientMatrix)
    {
    double mat[16];
    vtkMatrix4x4::DeepCopy(mat, this->PatientMatrix);
    for (int i = 0; i < 16; i++)
      {
      os << " " << mat[i];
      }
    os << "\n";
    }
  else
    {
    os << " (none)\n";
    }

  os << indent << "MemoryRowOrder: "
     << this->GetMemoryRowOrderAsString() << "\n";
}

//----------------------------------------------------------------------------
namespace {

// This silences error printing when CanReadFile is testing a file.
class vtkDICOMErrorSilencer : public vtkCommand
{
public:
  static vtkDICOMErrorSilencer *New() { return new vtkDICOMErrorSilencer; }
  vtkTypeMacro(vtkDICOMErrorSilencer,vtkCommand);
  virtual void Execute(
    vtkObject *caller, unsigned long eventId, void *callData);
protected:
  vtkDICOMErrorSilencer() {};
  vtkDICOMErrorSilencer(const vtkDICOMErrorSilencer& c) : vtkCommand(c) {}
  void operator=(const vtkDICOMErrorSilencer&) {}
};

void vtkDICOMErrorSilencer::Execute(vtkObject *, unsigned long, void *)
{
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMReader::SetMemoryRowOrder(int order)
{
  if (order >= 0 && order <= vtkDICOMReader::BottomUp)
    {
    if (order != this->MemoryRowOrder)
      {
      this->MemoryRowOrder = order;
      this->Modified();
      }
    }
}

//----------------------------------------------------------------------------
const char *vtkDICOMReader::GetMemoryRowOrderAsString()
{
  const char *text = "";
  switch (this->MemoryRowOrder)
    {
    case vtkDICOMReader::FileNative:
      text = "FileNative";
      break;
    case vtkDICOMReader::TopDown:
      text = "TopDown";
      break;
    case vtkDICOMReader::BottomUp:
      text = "BottomUp";
      break;
    }

  return text;
}

//----------------------------------------------------------------------------
int vtkDICOMReader::CanReadFile(const char *filename)
{
  vtkDebugMacro("Opening DICOM file " << filename);

  vtkDICOMErrorSilencer *command = vtkDICOMErrorSilencer::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  // add a dummy observer to silence errors
  unsigned long cid = parser->AddObserver(vtkCommand::ErrorEvent, command);
  parser->SetFileName(filename);
  parser->Update();
  parser->RemoveObserver(cid);
  command->Delete();

  // if an pixel data was found, the file is DICOM image
  return parser->GetPixelDataFound();
}

//----------------------------------------------------------------------------
namespace {

// a class and methods for sorting the files
struct vtkDICOMReaderSortInfo
{
  int FileNumber;
  int InstanceNumber;
  double ComputedLocation;

  vtkDICOMReaderSortInfo() :
    FileNumber(0), InstanceNumber(0), ComputedLocation(0.0) {}

  vtkDICOMReaderSortInfo(int i, int j, double l) :
    FileNumber(i), InstanceNumber(j), ComputedLocation(l) {}
};

bool vtkDICOMReaderCompareInstance(
  const vtkDICOMReaderSortInfo &si1, const vtkDICOMReaderSortInfo &si2)
{
  return (si1.InstanceNumber < si2.InstanceNumber);
}

bool vtkDICOMReaderCompareLocation(
  const vtkDICOMReaderSortInfo &si1, const vtkDICOMReaderSortInfo &si2)
{
  // locations must differ by at least the tolerance
  const double locationTolerance = 1e-3;
  return (si1.ComputedLocation + locationTolerance < si2.ComputedLocation);
}

// a simple struct to provide info for each file to be read
struct vtkDICOMReaderFileInfo
{
  int FileIndex;
  int SliceIndex;
  int NumberOfSlices;

  vtkDICOMReaderFileInfo(int i, int j) :
    FileIndex(i), SliceIndex(j), NumberOfSlices(1) {}
};

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMReader::SortFiles(vtkIntArray *sorted)
{
  // This function assumes that the meta data has already been read,
  // and that all files have the same StudyUID and SeriesUID.
  //
  // It tries two strategies to sort the DICOM files.
  //
  // First, it simply sorts the files by instance number.
  //
  // Next, if the Image Plane Module is present (DICOM Part 3 C.7.6.2)
  // then the images are sorted by ImagePositionPatient, so that the
  // position increases along the direction given by cross product of
  // the ImageOrientationPatient vectors.

  vtkDICOMMetaData *meta = this->MetaData;
  int numFiles = meta->GetNumberOfInstances();
  std::vector<vtkDICOMReaderSortInfo> info(numFiles);
  double checkNormal[3] = { 0.0, 0.0, 0.0 };
  bool canSortByPosition = true;

  // we want to divide locations by this value before sorting
  double spacingBetweenSlices =
    meta->GetAttributeValue(DC::SpacingBetweenSlices).AsDouble();
  if (spacingBetweenSlices <= 0)
    {
    spacingBetweenSlices = 1.0;
    }

  for (int i = 0; i < numFiles; i++)
    {
    // check for valid Image Plane Module information
    double location = 0;
    vtkDICOMValue pv = meta->GetAttributeValue(i, DC::ImagePositionPatient);
    vtkDICOMValue ov = meta->GetAttributeValue(i, DC::ImageOrientationPatient);
    if (pv.GetNumberOfValues() == 3 && ov.GetNumberOfValues() == 6)
      {
      double orientation[6], normal[3], position[3];
      pv.GetValues(position, position+3);
      ov.GetValues(orientation, orientation+6);

      // compute the cross product to get the slice normal
      vtkMath::Cross(&orientation[0], &orientation[3], normal);
      location = vtkMath::Dot(normal, position)/spacingBetweenSlices;

      if (i == 0)
        {
        // save the normal of the first slice for later checks
        checkNormal[0] = normal[0];
        checkNormal[1] = normal[1];
        checkNormal[2] = normal[2];
        }
      else
        {
        // make sure all slices have the same normal
        double a = vtkMath::Dot(normal, checkNormal);
        double b = vtkMath::Dot(normal, normal);
        double c = vtkMath::Dot(checkNormal, checkNormal);
        // compute the sine of the angle between the normals
        // (actually compute the square of the sine, it's easier)
        double d = 1.0;
        if (b > 0 && c > 0)
          {
          d = 1.0 - (a*a)/(b*c);
          }
        // the tolerance is in radians (small angle approximation)
        const double directionTolerance = 1e-3;
        if (d > directionTolerance*directionTolerance)
          {
          // not all slices have the same normal
          canSortByPosition = false;
          }
        }
      }
    else
      {
      // Image Plane Module information is not present
      canSortByPosition = false;
      }

    // get the instance number, build the vector for sorting
    int j = meta->GetAttributeValue(i, DC::InstanceNumber).AsInt();
    info[i] = vtkDICOMReaderSortInfo(i, j, location);
    }

  // sort by instance, and then by position
  std::stable_sort(info.begin(), info.end(), vtkDICOMReaderCompareInstance);
  if (canSortByPosition)
    {
    std::stable_sort(info.begin(), info.end(), vtkDICOMReaderCompareLocation);
    if (info.size() > 1)
      {
      double locDiff =
        (info.back().ComputedLocation - info.front().ComputedLocation)/
        static_cast<double>(info.size() - 1);
      if (locDiff > 0)
        {
        spacingBetweenSlices *= locDiff;
        }
      else
        {
        canSortByPosition = false;
        }
      }
    }

  // If the multi-frame module is present, each file might have more than
  // one slice.  See DICOM Part 3 Appendix C 7.6.6 for details.
  // To identify the multi-frame module, look for these attributes:
  // - NumberOfFrames (0028,0008)
  // - FrameIncrementPointer (0028,0009)
  // Usually frames are used for cine, but in nuclear medicine (NM) they
  // are used to describe multi-dimensional files (Part 3 Appendix C 8.4.8):
  // - NumberOfSlices (0054,0081)
  // - NumberOfTimeSlots (0054,0071)
  // - NumberOfRRIntervals (0054,0061)
  // - NumberOfRotations (0054,0051)
  // - NumberOfPhases (0054,0031)
  // - NumberOfDetectors (0054,0021)
  // - NumberOfEnergyWindows (0054,0011)

  // write out the sorted indices
  bool flipImage = (this->MemoryRowOrder == vtkDICOMReader::BottomUp);
  bool flipOrder = (flipImage && canSortByPosition);
  sorted->SetNumberOfComponents(1);
  sorted->SetNumberOfValues(numFiles);
  for (int k = 0; k < numFiles; k++)
    {
    int kflip = numFiles - k - 1;
    kflip = (flipOrder ? kflip : k);
    sorted->SetValue(k, info[kflip].FileNumber);
    }

  this->DataSpacing[2] = spacingBetweenSlices;
}

//----------------------------------------------------------------------------
int vtkDICOMReader::RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  // Clear the error indicator.
  this->SetErrorCode(vtkErrorCode::NoError);

  // How many files are to be loaded?
  if (this->FileNames)
    {
    vtkIdType numFileNames = this->FileNames->GetNumberOfValues();
    this->DataExtent[4] = 0;
    this->DataExtent[5] = static_cast<int>(numFileNames - 1);
    }
  else if (this->FileName)
    {
    this->DataExtent[4] = 0;
    this->DataExtent[5] = 0;
    }
  int numFiles = this->DataExtent[5] - this->DataExtent[4] + 1;

  // Clear the meta data, prepare the parser.
  this->MetaData->Clear();
  this->MetaData->SetNumberOfInstances(numFiles);

  if (this->Parser)
    {
    this->Parser->Delete();
    this->FileOffsetArray->Delete();
    }

  // Parser reads just the meta data, not the pixel data.
  this->Parser = vtkDICOMParser::New();
  this->Parser->SetMetaData(this->MetaData);
  this->Parser->AddObserver(
    vtkCommand::ErrorEvent, this, &vtkDICOMReader::RelayError);

  // First component is offset to pixel data, 2nd component is file size.
  this->FileOffsetArray = vtkTypeInt64Array::New();
  this->FileOffsetArray->SetNumberOfComponents(2);
  this->FileOffsetArray->SetNumberOfTuples(numFiles);

  for (int idx = 0; idx < numFiles; idx++)
    {
    this->ComputeInternalFileName(this->DataExtent[4] + idx);
    this->Parser->SetFileName(this->InternalFileName);
    this->Parser->SetIndex(idx);
    this->Parser->Update();

    if (this->Parser->GetErrorCode())
      {
      return 0;
      }

    // save the offset to the pixel data
    vtkTypeInt64 offset[2];
    offset[0] = this->Parser->GetFileOffset();
    offset[1] = this->Parser->GetFileSize();
    this->FileOffsetArray->SetTupleValue(idx, offset);
    }

  // Files are read in the order provided, but they might have
  // to be re-sorted to create a proper volume.  The FileIndexArray
  // holds the sorted order of the files.
  this->SortFiles(this->FileIndexArray);

  // image dimensions
  int columns = this->MetaData->GetAttributeValue(DC::Columns).AsInt();
  int rows = this->MetaData->GetAttributeValue(DC::Rows).AsInt();
  int slices = static_cast<int>(this->FileIndexArray->GetNumberOfTuples());

  int extent[6];
  extent[0] = 0;
  extent[1] = columns - 1;
  extent[2] = 0;
  extent[3] = rows - 1;
  extent[4] = 0;
  extent[5] = slices - 1;

  // set the x and y dimensions of the DataExtent
  this->DataExtent[0] = extent[0];
  this->DataExtent[1] = extent[1];
  this->DataExtent[2] = extent[2];
  this->DataExtent[3] = extent[3];

  // DICOM images are usually stored one-slice-per-file,
  // with the exception of nuclear medicine and ultrasound
  // (the DataExtent gives the number of files)
  this->FileDimensionality = 2;
  if (slices > this->DataExtent[5] - this->DataExtent[4] + 1)
    {
    this->FileDimensionality = 3;
    }

  // DICOM uses a upper-left origin
  this->FileLowerLeft = 0;

  // pixel size
  double xspacing = 1.0;
  double yspacing = 1.0;
  if (this->MetaData->HasAttribute(DC::PixelSpacing))
    {
    vtkDICOMValue v = this->MetaData->GetAttributeValue(DC::PixelSpacing);
    if (v.GetNumberOfValues() == 2)
      {
      xspacing = v.GetDouble(0);
      yspacing = v.GetDouble(1);
      }
    }
  else if (this->MetaData->HasAttribute(DC::PixelAspectRatio))
    {
    double ratio = 1.0;
    vtkDICOMValue v = this->MetaData->GetAttributeValue(DC::PixelAspectRatio);
    if (v.GetNumberOfValues() == 2)
      {
      // use double, even though data is stored as integer strings
      double ya = v.GetDouble(0);
      double xa = v.GetDouble(1);
      if (xa > 0)
        {
        ratio = ya/xa;
        }
      }
    else
      {
      // ratio should be expressed as two values,
      // so this is only to support incorrect files
      ratio = v.AsDouble();
      }
    if (ratio > 0)
      {
      xspacing = yspacing/ratio;
      }
    }
  this->DataSpacing[0] = xspacing;
  this->DataSpacing[1] = yspacing;

  // offset is part of the transform, so set origin to zero
  this->DataOrigin[0] = 0.0;
  this->DataOrigin[1] = 0.0;
  this->DataOrigin[2] = 0.0;

  // get information related to the data type
  int bitsAllocated =
    this->MetaData->GetAttributeValue(DC::BitsAllocated).AsInt();
  int pixelRepresentation =
    this->MetaData->GetAttributeValue(DC::PixelRepresentation).AsInt();
  int numComponents =
    this->MetaData->GetAttributeValue(DC::SamplesPerPixel).AsInt();

  // datatype
  int scalarType = 0;

  if (bitsAllocated == 8)
    {
    scalarType = (pixelRepresentation ? VTK_SIGNED_CHAR : VTK_UNSIGNED_CHAR);
    }
  else if (bitsAllocated == 16 || bitsAllocated == 12)
    {
    scalarType = (pixelRepresentation ? VTK_SHORT : VTK_UNSIGNED_SHORT);
    }
  else
    {
    vtkErrorMacro("Unrecognized DICOM BitsAllocated value: " << bitsAllocated);
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return 0;
    }

  // number of components
  if (numComponents <= 0)
    {
    numComponents = 1;
    }

  this->DataScalarType = scalarType;
  this->NumberOfScalarComponents = numComponents;

  // photometric interpretation
  // "MONOCHROME1" "MONOCHROME2"
  // "PALETTE_COLOR" "RGB" (convert palette color to RGB)
  // "HSV" "ARGB" "CMYK" (all three are retired)
  // "YBR_FULL" "YBR_FULL_422" (use CCIR 601-2 to convert to RGB)
  // "YBR_PARTIAL_422" "YBR_PARTIAL_420" (use CCIR 601-2 to convert to RGB)
  // "YBR_ICT" "YBR_RCT" (use ISO 10918-1 to convert to RGB)
  // See DICOM Ch. 3 Appendix C 7.6.3.1.2 for equations

  // planar configuration: 0 is packed, 1 is planar

  // endianness
  std::string transferSyntax =
    this->MetaData->GetAttributeValue(DC::TransferSyntaxUID).AsString();

  bool bigEndian = (transferSyntax == "1.2.840.10008.1.2.2" ||
                    transferSyntax == "1.2.840.113619.5.2");

#ifdef VTK_WORDS_BIGENDIAN
  this->SwapBytes = !bigEndian;
#else
  this->SwapBytes = bigEndian;
#endif

  // for PET this will be different for each file, so PET data will have
  // to be rescaled while it is being read
  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;

  if (this->MetaData->HasAttribute(DC::RescaleSlope))
    {
    this->RescaleSlope =
      this->MetaData->GetAttributeValue(DC::RescaleSlope).AsDouble();
    this->RescaleIntercept =
      this->MetaData->GetAttributeValue(DC::RescaleIntercept).AsDouble();
    }

  // === Image Orientation in DICOM files ===
  //
  // The vtkImageData class does not provide a way of storing image
  // orientation.  So when we read a DICOM file, we should also provide
  // the user with a 4x4 matrix that can transform VTK's data coordinates
  // into DICOM's patient coordinates, as defined in the DICOM standard
  // Part 3 Appendix C 7.6.2 "Image Plane Module".
  int fileIndex = this->FileIndexArray->GetValue(0);
  vtkDICOMValue pv = this->MetaData->GetAttributeValue(
    fileIndex, DC::ImagePositionPatient);
  vtkDICOMValue ov = this->MetaData->GetAttributeValue(
    fileIndex, DC::ImageOrientationPatient);
  if (pv.GetNumberOfValues() == 3 && ov.GetNumberOfValues() == 6)
    {
    double orient[6], normal[3], point[3];
    pv.GetValues(point, point+3);
    ov.GetValues(orient, orient+6);

    if (this->MemoryRowOrder == vtkDICOMReader::BottomUp)
      {
      // calculate position of point at lower left
      point[0] = point[0] + orient[3]*yspacing*(rows - 1);
      point[1] = point[1] + orient[4]*yspacing*(rows - 1);
      point[2] = point[2] + orient[5]*yspacing*(rows - 1);

      // measure orientation from lower left corner upwards
      orient[3] = -orient[3];
      orient[4] = -orient[4];
      orient[5] = -orient[5];
      }

    vtkMath::Cross(&orient[0], &orient[3], normal);
    double pm[16];
    pm[0] = orient[0]; pm[1] = orient[3]; pm[2] = normal[0]; pm[3] = point[0];
    pm[4] = orient[1]; pm[5] = orient[4]; pm[6] = normal[1]; pm[7] = point[1];
    pm[8] = orient[2]; pm[9] = orient[5]; pm[10] = normal[2]; pm[11] = point[2];
    pm[12] = 0.0; pm[13] = 0.0; pm[14] = 0.0; pm[15] = 1.0;
    this->PatientMatrix->DeepCopy(pm);
    }
  else
    {
    this->PatientMatrix->Identity();
    }

  // Set the output information.
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               extent, 6);

  outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(),  this->DataOrigin, 3);

  vtkDataObject::SetPointDataActiveScalarInfo(
    outInfo, this->DataScalarType, this->NumberOfScalarComponents);

  return 1;
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadUncompressedFile(
  const char *filename, int fileIdx, char *buffer, vtkIdType bufferSize)
{
  // get the offset to the PixelData in the file
  vtkTypeInt64 offsetAndSize[2];
  this->FileOffsetArray->GetTupleValue(fileIdx, offsetAndSize);
  vtkTypeInt64 offset = offsetAndSize[0];

  vtkDebugMacro("Opening DICOM file " << filename);
  std::ifstream infile(filename, ios::in | ios::binary);

  if (infile.fail())
    {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("ReadFile: Can't read the file " << filename);
    return false;
    }

  if (!infile.seekg(static_cast<std::streamoff>(offset), std::ios::beg))
    {
    this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
    vtkErrorMacro("DICOM file is truncated, some data is missing.");
    return false;
    }

  infile.read(buffer, bufferSize);

  if (infile.eof())
    {
    this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
    vtkErrorMacro("DICOM file is truncated, some data is missing.");
    return false;
    }
  else if (infile.fail())
    {
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    vtkErrorMacro("Error in DICOM file, cannot read.");
    return false;
    }

  if (this->SwapBytes)
    {
    int scalarSize = vtkDataArray::GetDataTypeSize(this->DataScalarType);
    vtkByteSwap::SwapVoidRange(buffer, bufferSize/scalarSize, scalarSize);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadCompressedFile(
  const char *filename, int fileIdx, char *buffer, vtkIdType bufferSize)
{
#ifdef DICOM_USE_GDCM

  gdcm::ImageReader reader;
  reader.SetFileName(filename);
  if(!reader.Read())
    {
    vtkErrorMacro("The GDCM ImageReader could not read the image.");
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return false;
    }

  gdcm::Image &image = reader.GetImage();
  if (static_cast<vtkIdType>(image.GetBufferLength()) != bufferSize)
    {
    vtkErrorMacro("The uncompressed image has the wrong size.");
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return false;
    }

  image.GetBuffer(buffer);
  return true;

#else /* no GDCM, so no file decompression */

  this->SetErrorCode(vtkErrorCode::FileFormatError);
  vtkErrorMacro("DICOM file is compressed, cannot read.");
  return false;

#endif
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadOneFile(
  const char *filename, int fileIdx, char *buffer, vtkIdType bufferSize)
{
  std::string transferSyntax = this->MetaData->GetAttributeValue(
    fileIdx, DC::TransferSyntaxUID).AsString();

  if (transferSyntax == "1.2.840.10008.1.2"   ||  // Implicit LE
      transferSyntax == "1.2.840.10008.1.20"  ||  // Papyrus Implicit LE
      transferSyntax == "1.2.840.10008.1.2.1" ||  // Explicit LE
      transferSyntax == "1.2.840.10008.1.2.2" ||  // Explicit BE
      transferSyntax == "1.2.840.113619.5.2"  ||  // GE LE with BE data
      transferSyntax == "")
    {
    return this->ReadUncompressedFile(filename, fileIdx, buffer, bufferSize);
    }

  return this->ReadCompressedFile(filename, fileIdx, buffer, bufferSize);
}

//----------------------------------------------------------------------------
int vtkDICOMReader::RequestData(
  vtkInformation* request,
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  // which output port did the request come from
  int outputPort =
    request->Get(vtkDemandDrivenPipeline::FROM_OUTPUT_PORT());

  // for now, this reader has only one output
  if (outputPort > 0)
    {
    return true;
    }

  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  int extent[6];
  outInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  if (this->FileDimensionality == 2)
    {
    // limit the number of slices to the requested update extent
    int uExtent[6];
    outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), uExtent);
    extent[4] = uExtent[4];
    extent[5] = uExtent[5];
    }

  // make a list of all the files inside the update extent
  std::vector<vtkDICOMReaderFileInfo> files;
  for (int sIdx = extent[4]; sIdx <= extent[5]; sIdx++)
    {
    int fileIdx = this->FileIndexArray->GetValue(sIdx);
    std::vector<vtkDICOMReaderFileInfo>::iterator iter = files.begin();
    while (iter != files.end() && iter->FileIndex != fileIdx) { ++iter; }
    if (iter == files.end())
      {
      files.push_back(vtkDICOMReaderFileInfo(fileIdx, sIdx));
      }
    else
      {
      iter->NumberOfSlices++;
      }
    }

  // get the data object, allocate memory
  vtkImageData *data =
    static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));
#if VTK_MAJOR_VERSION >= 6
  this->AllocateOutputData(data, outInfo, extent);
#else
  this->AllocateOutputData(data, extent);
#endif

  data->GetPointData()->GetScalars()->SetName("PixelData");

  char *dataPtr = static_cast<char *>(data->GetScalarPointer());

  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();

  vtkIdType pixelSize = numComponents*scalarSize;
  vtkIdType rowSize = pixelSize*(extent[1] - extent[0] + 1);
  vtkIdType sliceSize = rowSize*(extent[3] - extent[2] + 1);

  this->InvokeEvent(vtkCommand::StartEvent);

  bool flipImage = (this->MemoryRowOrder == vtkDICOMReader::BottomUp);
  char *rowBuffer = 0;
  if (flipImage)
    {
    rowBuffer = new char[rowSize];
    }

  // loop through all files in the update extent
  for (size_t idx = 0; idx < files.size(); idx++)
    {
    if (this->AbortExecute) { break; }

    this->UpdateProgress(static_cast<double>(idx)/
                         static_cast<double>(files.size()));

    // get the index for this file
    int fileIdx = files[idx].FileIndex;
    int sliceIdx = files[idx].SliceIndex;
    int numSlices = files[idx].NumberOfSlices;
    // reverse slices if flipImage
    char *slicePtr = dataPtr + (sliceIdx - extent[4])*sliceSize;

    this->ComputeInternalFileName(fileIdx);

    // read the file into the output
    this->ReadOneFile(this->InternalFileName, fileIdx,
                      slicePtr, numSlices*sliceSize);

    for (int sIdx = 0; sIdx < numSlices; sIdx++)
      {
      // flip the data if necessary
      // NOTE: depending on SpacingBetweenSlices, multi-frame images
      // like nuclear medicine images might have to be flipped back-to-front
      if (flipImage)
        {
        int numRows = extent[3] - extent[2] + 1;
        int halfRows = numRows/2;
        for (int yIdx = 0; yIdx < halfRows; yIdx++)
          {
          char *row1 = slicePtr + yIdx*rowSize;
          char *row2 = slicePtr + (numRows-yIdx-1)*rowSize;
          memcpy(rowBuffer, row1, rowSize);
          memcpy(row1, row2, rowSize);
          memcpy(row2, rowBuffer, rowSize);
          }
        }
      slicePtr += sliceSize;
      }
    }

  delete [] rowBuffer;

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}

//----------------------------------------------------------------------------
void vtkDICOMReader::RelayError(vtkObject *o, unsigned long e, void *data)
{
  if (e == vtkCommand::ErrorEvent)
    {
    vtkDICOMParser *parser = vtkDICOMParser::SafeDownCast(o);
    if (parser && parser->GetErrorCode())
      {
      this->SetErrorCode(parser->GetErrorCode());
      }

    vtkErrorMacro(<< static_cast<char *>(data));
    }
  else
    {
    this->InvokeEvent(e, data);
    }
}
