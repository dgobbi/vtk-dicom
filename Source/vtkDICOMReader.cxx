/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMReader.h"
#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMFile.h"
#include "vtkDICOMFilePath.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"
#include "vtkDICOMImageCodec.h"
#include "vtkDICOMSliceSorter.h"
#include "vtkDICOMUtilities.h"
#include "vtkDICOMConfig.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkIntArray.h"
#include "vtkTypeInt64Array.h"
#include "vtkByteSwap.h"
#include "vtkMatrix4x4.h"
#include "vtkMedicalImageProperties.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkStringArray.h"
#include "vtkMath.h"
#include "vtkVariant.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"
#include "vtkTemplateAliasMacro.h"
#include "vtkTypeTraits.h"

#if defined(DICOM_USE_DCMTK)
#ifndef _WIN32
#define HAVE_CONFIG_H
#endif
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/dcmdata/dcrledrg.h"
#include "dcmtk/dcmjpeg/djdecode.h"
#include "dcmtk/dcmjpls/djdecode.h"
#ifndef _WIN32
#undef HAVE_CONFIG_H
#endif
#elif defined(DICOM_USE_GDCM)
#include "gdcmImageReader.h"
#endif

#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define SetTupleValue SetTypedTuple
#define GetTupleValue GetTypedTuple
#endif

vtkStandardNewMacro(vtkDICOMReader);
vtkCxxSetObjectMacro(vtkDICOMReader,Sorter,vtkDICOMSliceSorter);

//----------------------------------------------------------------------------
vtkDICOMReader::vtkDICOMReader()
{
  this->AutoYBRToRGB = 1;
  this->NeedsYBRToRGB = 0;
  this->AutoRescale = 1;
  this->NeedsRescale = 0;
  this->FileScalarType = 0;
  this->OutputScalarType = -1;
  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;
  this->DefaultCharacterSet = vtkDICOMCharacterSet::GetGlobalDefault();
  this->OverrideCharacterSet = vtkDICOMCharacterSet::GetGlobalOverride();
  this->Parser = 0;
  this->Sorter = vtkDICOMSliceSorter::New();
  this->FileIndexArray = vtkIntArray::New();
  this->FrameIndexArray = vtkIntArray::New();
  this->StackIDs = vtkStringArray::New();
  this->FileOffsetArray = 0;
  this->MetaData = vtkDICOMMetaData::New();
  this->PatientMatrix = vtkMatrix4x4::New();
  this->MemoryRowOrder = vtkDICOMReader::BottomUp;
  this->NumberOfPackedComponents = 1;
  this->NumberOfPlanarComponents = 1;
  this->Sorting = 1;
  this->TimeAsVector = 0;
  this->DesiredTimeIndex = -1;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->DesiredStackID[0] = '\0';
  this->OverlayBitfield = 0;

  this->DataScalarType = VTK_SHORT;
  this->NumberOfScalarComponents = 1;
  this->FileLowerLeft = 0;
  this->FileDimensionality = 2;
#ifdef VTK_WORDS_BIGENDIAN
  this->SwapBytes = 1;
#else
  this->SwapBytes = 0;
#endif

  this->MedicalImageProperties = 0;

#ifdef DICOM_USE_DCMTK
  DJDecoderRegistration::registerCodecs();
  DJLSDecoderRegistration::registerCodecs();
  DcmRLEDecoderRegistration::registerCodecs();
#endif

  // the main image and the overlay are the two outputs
  this->SetNumberOfOutputPorts(2);
}

//----------------------------------------------------------------------------
vtkDICOMReader::~vtkDICOMReader()
{
#ifdef DICOM_USE_DCMTK
  DcmRLEDecoderRegistration::cleanup();
  DJLSDecoderRegistration::cleanup();
  DJDecoderRegistration::cleanup();
#endif

  if (this->Parser)
  {
    this->Parser->Delete();
  }
  if (this->Sorter)
  {
    this->Sorter->Delete();
  }
  if (this->FileOffsetArray)
  {
    this->FileOffsetArray->Delete();
  }
  if (this->FileIndexArray)
  {
    this->FileIndexArray->Delete();
  }
  if (this->FrameIndexArray)
  {
    this->FrameIndexArray->Delete();
  }
  if (this->StackIDs)
  {
    this->StackIDs->Delete();
  }
  if (this->MetaData)
  {
    this->MetaData->Delete();
  }
  if (this->PatientMatrix)
  {
    this->PatientMatrix->Delete();
  }
  if (this->MedicalImageProperties)
  {
    this->MedicalImageProperties->Delete();
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

  os << indent << "MedicalImageProperties: ";
  if (this->MedicalImageProperties)
  {
    os << this->MedicalImageProperties << "\n";
  }
  else
  {
    os << "(none)\n";
  }

  os << indent << "Sorter: ";
  if (this->Sorter)
  {
    os << this->Sorter << "\n";
  }
  else
  {
    os << "(none)\n";
  }

  os << indent << "DesiredStackID: "
     << (*this->DesiredStackID ? "(empty)" : this->DesiredStackID) << "\n";
  os << "StackIDs: " << this->StackIDs << "\n";

  os << indent << "FileIndexArray: " << this->FileIndexArray << "\n";
  os << indent << "FrameIndexArray: " << this->FrameIndexArray << "\n";

  os << indent << "Sorting: " << (this->Sorting ? "On\n" : "Off\n");
  os << indent << "TimeAsVector: "
     << (this->TimeAsVector ? "On\n" : "Off\n");
  os << indent << "TimeDimension: " << this->TimeDimension << "\n";
  os << indent << "TimeSpacing: " << this->TimeSpacing << "\n";
  os << indent << "DesiredTimeIndex: " << this->DesiredTimeIndex << "\n";

  os << indent << "AutoRescale: "
     << (this->AutoRescale ? "On\n" : "Off\n");
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
  os << indent << "OutputScalarType: " << this->OutputScalarType << "\n";

  os << indent << "OverlayBitfield: " << this->OverlayBitfield << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMReader::SetDesiredStackID(const char *stackId)
{
  if (stackId == 0)
  {
    stackId = "";
  }

  // the maximum length of a stackId is 16
  if (strncmp(this->DesiredStackID, stackId, 16) != 0)
  {
    strncpy(this->DesiredStackID, stackId, 16);
    this->DesiredStackID[17] = '\0';
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMReader::SetDefaultCharacterSet(vtkDICOMCharacterSet cs)
{
  if (this->DefaultCharacterSet != cs)
  {
    this->DefaultCharacterSet = cs;
    this->Modified();
  }
}

//----------------------------------------------------------------------------
namespace {

// This silences error printing when CanReadFile is testing a file.
class vtkDICOMErrorSilencer : public vtkCommand
{
public:
  static vtkDICOMErrorSilencer *New() { return new vtkDICOMErrorSilencer; }
  vtkTypeMacro(vtkDICOMErrorSilencer,vtkCommand);
#ifdef VTK_OVERRIDE
  void Execute(vtkObject *caller, unsigned long eventId, void *callData)
    VTK_OVERRIDE;
#else
  void Execute(vtkObject *caller, unsigned long eventId, void *callData);
#endif
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

// a simple struct to provide info for each frame to be read
struct vtkDICOMReaderFrameInfo
{
  int FrameIndex;
  int SliceIndex;
  int ComponentIndex;

  vtkDICOMReaderFrameInfo(int i, int j, int k) :
    FrameIndex(i), SliceIndex(j), ComponentIndex(k) {}
};

// a simple struct to provide info for each file to be read
struct vtkDICOMReaderFileInfo
{
  int FileIndex;
  int FramesInFile; // total frames in file
  std::vector<vtkDICOMReaderFrameInfo> Frames; // the frames to read

  vtkDICOMReaderFileInfo(int i, int n) : FileIndex(i), FramesInFile(n) {}
};

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMReader::SortFiles(vtkIntArray *files, vtkIntArray *frames)
{
  vtkDICOMSliceSorter *sorter = this->Sorter;

  sorter->SetMetaData(this->MetaData);
  sorter->SetDesiredStackID(this->DesiredStackID);
  sorter->SetTimeAsVector(this->TimeAsVector);
  sorter->SetDesiredTimeIndex(this->DesiredTimeIndex);
  sorter->SetReverseSlices(this->MemoryRowOrder == vtkDICOMReader::BottomUp);

  sorter->Update();

  files->DeepCopy(sorter->GetFileIndexArray());
  frames->DeepCopy(sorter->GetFrameIndexArray());
  this->StackIDs->DeepCopy(sorter->GetStackIDs());

  // save the slice spacing and time information
  this->DataSpacing[2] = sorter->GetSliceSpacing();
  this->TimeDimension = sorter->GetTimeDimension();
  this->TimeSpacing = sorter->GetTimeSpacing();
}

//----------------------------------------------------------------------------
void vtkDICOMReader::NoSortFiles(vtkIntArray *files, vtkIntArray *frames)
{
  vtkDICOMMetaData *meta = this->MetaData;
  int numFiles = meta->GetNumberOfInstances();

  files->Initialize();
  frames->Initialize();
  files->SetNumberOfComponents(1);
  frames->SetNumberOfComponents(1);

  for (int i = 0; i < numFiles; i++)
  {
    int numFrames = meta->Get(i, DC::NumberOfFrames).AsInt();
    numFrames = (numFrames > 0 ? numFrames : 1);

    for (int j = 0; j < numFrames; j++)
    {
      files->InsertNextValue(i);
      frames->InsertNextValue(j);
    }
  }
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ValidateStructure(
  vtkIntArray *fileArray, vtkIntArray *frameArray)
{
  vtkDICOMMetaData *meta = this->MetaData;
  int numFiles = meta->GetNumberOfInstances();
  std::vector<int> usedFiles(numFiles);
  std::fill(usedFiles.begin(), usedFiles.end(), static_cast<int>(0));

  // Validate the range of indexes the sorted arrays
  int numComponents = fileArray->GetNumberOfComponents();
  vtkIdType numSlices = fileArray->GetNumberOfTuples();
  if (numSlices != frameArray->GetNumberOfTuples() ||
      numComponents != fileArray->GetNumberOfComponents())
  {
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    vtkErrorMacro("Critical failure in file sorting!");
    return false;
  }

  for (vtkIdType i = 0; i < numSlices; i++)
  {
    for (int j = 0; j < numComponents; j++)
    {
      int fileIndex = fileArray->GetComponent(i, j);
      int frameIndex = frameArray->GetComponent(i, j);

      if (fileIndex < 0 || fileIndex >= numFiles)
      {
        this->SetErrorCode(vtkErrorCode::FileFormatError);
        vtkErrorMacro("File index " << fileIndex << " is out of range!");
        return false;
      }

      usedFiles[fileIndex]++;

      int numFrames =
        meta->Get(fileIndex, DC::NumberOfFrames).AsInt();
      numFrames = (numFrames == 0 ? 1 : numFrames);

      if (frameIndex < 0 || frameIndex >= numFrames)
      {
        this->SetErrorCode(vtkErrorCode::FileFormatError);
        vtkErrorMacro("Frame index " << frameIndex << " is out of range!");
        return false;
      }
    }
  }

  // The reader requires the following mandatory attributes
  static const DC::EnumType imagePixelAttribs[] = {
    DC::SamplesPerPixel, // missing in old ACR-NEMA files
    DC::Rows,
    DC::Columns,
    DC::BitsAllocated,
    DC::ItemDelimitationItem
  };

  for (const DC::EnumType *tags = imagePixelAttribs;
       *tags != DC::ItemDelimitationItem;
       tags++)
  {
    int firstValue = 0;

    for (int fileIndex = 0; fileIndex < numFiles; fileIndex++)
    {
      if (usedFiles[fileIndex] == 0) { continue; }

      const char *errorText = 0;
      vtkDICOMValue v = meta->Get(fileIndex, *tags);
      int i = 1;
      if (v.IsValid())
      {
        i = v.AsInt();
      }
      else if (*tags != DC::SamplesPerPixel)
      {
        // Some ACR-NEMA files do not contain SamplesPerPixel, all
        // other tags must be present
        errorText = "Missing pixel info ";
      }

      if (firstValue == 0)
      {
        firstValue = i;
      }
      else if (firstValue != i)
      {
        errorText = "Inconsistent pixel info ";
      }

      if (i <= 0 ||
          (*tags == DC::BitsAllocated &&
           i != 1 && i != 8 && i != 12 && i != 16 && i != 32 && i != 64))
      {
        errorText = "Illegal value ";
      }

      if (errorText)
      {
        this->ComputeInternalFileName(this->DataExtent[4] + fileIndex);
        this->Parser->SetFileName(this->InternalFileName);
        vtkDICOMDictEntry de = meta->FindDictEntry(*tags);
        this->SetErrorCode(vtkErrorCode::FileFormatError);
        if (v.IsValid())
        {
          vtkErrorMacro(<< errorText << i << " for " << de.GetTag()
                        << " \"" << de.GetName() << "\" in "
                        << this->InternalFileName);
        }
        else
        {
          vtkErrorMacro(<< errorText << "for " << de.GetTag()
                        << " \"" << de.GetName() << "\" in"
                        << this->InternalFileName);
        }
        return false;
      }
    }
  }

  return true;
}

//----------------------------------------------------------------------------
int vtkDICOMReader::ComputeRescaledScalarType(
  int scalarType, int bitsStored, int pixelRepresentation)
{
  // use BitsStored to get the potential input range
  unsigned long long l = 1;
  if (bitsStored > 0)
  {
    l <<= bitsStored - 1;
  }
  double pMin = 0;
  double pMax = 2.0*l - 1.0;
  if (pixelRepresentation)
  {
    pMin = -1.0*l;
    pMax = l - 1.0;
  }

  // loop through all images to get the rescaled range
  double vMin = VTK_DOUBLE_MAX;
  double vMax = VTK_DOUBLE_MIN;

  bool needsRescale = false;
  bool outputFloat = (scalarType == VTK_FLOAT || scalarType == VTK_DOUBLE);

  vtkIdType numSlices = this->FileIndexArray->GetNumberOfTuples();
  for (vtkIdType iSlice = 0; iSlice < numSlices; iSlice++)
  {
    int numComp = this->FileIndexArray->GetNumberOfComponents();
    for (int iComp = 0; iComp < numComp; iComp++)
    {
      int iFile = this->FileIndexArray->GetComponent(iSlice, iComp);
      int iFrame = this->FrameIndexArray->GetComponent(iSlice, iComp);

      double m = this->MetaData->Get(
        iFile, iFrame, DC::RescaleSlope).AsDouble();
      double b = this->MetaData->Get(
        iFile, iFrame, DC::RescaleIntercept).AsDouble();

      // sanity check
      if (m == 0.0)
      {
        m = 1.0;
      }

      // check if rescale will be needed
      if (m != 1.0 || b != 0.0)
      {
        needsRescale = true;

        // check if slope and intercept are integers
        if (m != floor(m) || b != floor(b))
        {
          outputFloat = true;
        }
      }

      // compute the min, max output values for one image
      double iMin = pMin*m + b;
      double iMax = pMax*m + b;

      // modify the global min, max output values
      vMin = (iMin < vMin ? iMin : vMin);
      vMax = (iMax > vMax ? iMax : vMax);
    }
  }

  // check if the data type has to be changed
  if (!outputFloat &&
      (vMin < vtkDataArray::GetDataTypeMin(scalarType) ||
       vMax > vtkDataArray::GetDataTypeMax(scalarType)))
  {
    int byteSize = vtkDataArray::GetDataTypeSize(scalarType);
    if (byteSize <= 2)
    {
      scalarType = (vMin < 0.0 ? VTK_SHORT : VTK_UNSIGNED_SHORT);
    }
    else if (byteSize <= 4)
    {
      scalarType = (vMin < 0.0 ? VTK_INT : VTK_UNSIGNED_INT);
    }
    else
    {
      scalarType = (vMin < 0.0 ? VTK_TYPE_INT64 : VTK_TYPE_UINT64);
    }
  }

  if (outputFloat &&
      scalarType != VTK_FLOAT &&
      scalarType != VTK_DOUBLE)
  {
    // use float if data is 24 bits or less
    if (bitsStored <= 24)
    {
      scalarType = VTK_FLOAT;
    }
    else
    {
      scalarType = VTK_DOUBLE;
    }
  }

  this->NeedsRescale = needsRescale;

  return scalarType;
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

  if (numFiles <= 0)
  {
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    if (this->FileNames)
    {
      vtkErrorMacro("No filenames were provided for reader.");
    }
    else
    {
      vtkErrorMacro("Bad DataExtent " << this->DataExtent[4]
                    << "," << this->DataExtent[5] << ".");
    }

    // Reset the data extent to legal values
    this->DataExtent[4] = 0;
    this->DataExtent[5] = 0;
  }

  // Reset the time information
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;

  // Clear the meta data, prepare the parser.
  this->MetaData->Initialize();
  if (numFiles > 0)
  {
    this->MetaData->SetNumberOfInstances(numFiles);
  }

  if (this->Parser)
  {
    this->Parser->Delete();
    this->FileOffsetArray->Delete();
  }

  // Parser reads just the meta data, not the pixel data.
  this->Parser = vtkDICOMParser::New();
  this->Parser->SetDefaultCharacterSet(this->DefaultCharacterSet);
  this->Parser->SetOverrideCharacterSet(this->OverrideCharacterSet);
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
      break;
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
  this->StackIDs->Initialize();
  if (this->GetErrorCode() == vtkErrorCode::NoError)
  {
    if (this->Sorting && this->Sorter)
    {
      this->SortFiles(this->FileIndexArray, this->FrameIndexArray);
    }
    else
    {
      this->NoSortFiles(this->FileIndexArray, this->FrameIndexArray);
    }

    // Verify the consistency of the data, e.g. verify that the dimensions
    // and data type are the same for all files.
    this->ValidateStructure(this->FileIndexArray, this->FrameIndexArray);
  }

  if (this->GetErrorCode() != vtkErrorCode::NoError)
  {
    // Last chance to bail out
    return false;
  }

  // Set the indexing arrays for the meta data
  this->MetaData->SetFileIndexArray(this->FileIndexArray);
  this->MetaData->SetFrameIndexArray(this->FrameIndexArray);

  // Get the file and frame for the first slice
  int fileIndex = this->FileIndexArray->GetComponent(0, 0);
  int frameIndex = this->FrameIndexArray->GetComponent(0, 0);

  // image dimensions
  int columns = this->MetaData->Get(fileIndex, DC::Columns).AsInt();
  int rows = this->MetaData->Get(fileIndex, DC::Rows).AsInt();
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

  // DataSpacing[2] was set in SortFiles, but pixel spacing is set here.
  this->DataSpacing[0] = 1.0;
  this->DataSpacing[1] = 1.0;

  // Set spacing from PixelAspectRatio
  double ratio = 1.0;
  vtkDICOMValue pixelAspectRatio =
    this->MetaData->Get(fileIndex, frameIndex, DC::PixelAspectRatio);
  if (pixelAspectRatio.GetNumberOfValues() == 2)
  {
    // use double, even though data is stored as integer strings
    double ya = pixelAspectRatio.GetDouble(0);
    double xa = pixelAspectRatio.GetDouble(1);
    if (xa > 0)
    {
      ratio = ya/xa;
    }
  }
  else if (pixelAspectRatio.GetNumberOfValues() == 1)
  {
    // ratio should be expressed as two values,
    // so this is only to support incorrect files
    ratio = pixelAspectRatio.AsDouble();
  }
  if (ratio > 0)
  {
    this->DataSpacing[0] = this->DataSpacing[1]/ratio;
  }

  // Set spacing from PixelSpacing
  vtkDICOMValue pixelSpacing =
    this->MetaData->Get(fileIndex, frameIndex, DC::PixelSpacing);
  if (pixelSpacing.GetNumberOfValues() == 2)
  {
    double spacing[2];
    pixelSpacing.GetValues(spacing, 2);
    if (spacing[0] > 0 && spacing[1] > 0)
    {
      this->DataSpacing[0] = spacing[0];
      this->DataSpacing[1] = spacing[1];
    }
  }

  // offset is part of the transform, so set origin to zero
  this->DataOrigin[0] = 0.0;
  this->DataOrigin[1] = 0.0;
  this->DataOrigin[2] = 0.0;

  // get information related to the data type
  int bitsAllocated =
    this->MetaData->Get(fileIndex, DC::BitsAllocated).AsInt();
  int pixelRepresentation =
    this->MetaData->Get(fileIndex, DC::PixelRepresentation).AsInt();
  int numComponents =
    this->MetaData->Get(fileIndex, DC::SamplesPerPixel).AsInt();
  int planarConfiguration =
    this->MetaData->Get(fileIndex, DC::PlanarConfiguration).AsInt();
  int bitsStored = this->MetaData->Get(fileIndex, DC::BitsStored).AsInt();
  if (bitsStored > bitsAllocated || bitsStored <= 0)
  {
    bitsStored = bitsAllocated;
  }

  // datatype
  int scalarType = 0;

  if (bitsAllocated <= 8)
  {
    scalarType = (pixelRepresentation ? VTK_SIGNED_CHAR : VTK_UNSIGNED_CHAR);
  }
  else if (bitsAllocated <= 16)
  {
    scalarType = (pixelRepresentation ? VTK_SHORT : VTK_UNSIGNED_SHORT);
  }
  else if (bitsAllocated <= 32)
  {
    if (this->MetaData->Get(fileIndex, DC::FloatPixelData).IsValid())
    {
      scalarType = VTK_FLOAT;
    }
    else
    {
      scalarType = (pixelRepresentation ? VTK_INT : VTK_UNSIGNED_INT);
    }
  }
  else if (bitsAllocated <= 64)
  {
    if (this->MetaData->Get(fileIndex, DC::DoubleFloatPixelData).IsValid())
    {
      scalarType = VTK_DOUBLE;
    }
    else
    {
      scalarType = (pixelRepresentation ? VTK_TYPE_INT64: VTK_TYPE_UINT64);
    }
  }

  this->RescaleSlope = 1.0;
  this->RescaleIntercept = 0.0;
  this->NeedsRescale = false;
  this->FileScalarType = scalarType;

  const vtkDICOMValue& slopeValue =
    this->MetaData->Get(fileIndex, frameIndex, DC::RescaleSlope);
  const vtkDICOMValue& interceptValue =
    this->MetaData->Get(fileIndex, frameIndex, DC::RescaleIntercept);

  if (slopeValue.IsValid() && interceptValue.IsValid())
  {
    if (this->AutoRescale)
    {
      // set NeedsRescale if any rescaling will be necessary,
      // and provide the new output type that will be needed
      scalarType = this->ComputeRescaledScalarType(
        scalarType, bitsStored, pixelRepresentation);
    }
    else
    {
      this->RescaleSlope = slopeValue.AsDouble();
      this->RescaleIntercept = interceptValue.AsDouble();
      if (this->RescaleSlope == 0.0)
      {
        this->RescaleSlope = 1.0;
      }
    }
  }

  // apply requested scalar type
  if (this->OutputScalarType != -1)
  {
    switch (this->OutputScalarType)
    {
      case VTK_SIGNED_CHAR:
      case VTK_UNSIGNED_CHAR:
      case VTK_SHORT:
      case VTK_UNSIGNED_SHORT:
      case VTK_INT:
      case VTK_UNSIGNED_INT:
      case VTK_FLOAT:
      case VTK_DOUBLE:
        scalarType = this->OutputScalarType;
        if (scalarType != this->FileScalarType)
        {
          this->NeedsRescale = true;
        }
        break;
      default:
        vtkWarningMacro("Illegal OutputScalarType: "
                        << this->OutputScalarType);
        break;
    }
  }

  // number of components
  if (numComponents <= 0)
  {
    numComponents = 1;
  }

  this->DataScalarType = scalarType;
  this->NumberOfPackedComponents =
    (planarConfiguration ? 1 : numComponents);
  this->NumberOfPlanarComponents =
    (planarConfiguration ? numComponents : 1);
  this->NumberOfScalarComponents =
    (numComponents * this->FileIndexArray->GetNumberOfComponents());

  // photometric interpretation
  // "MONOCHROME1" "MONOCHROME2"
  // "PALETTE COLOR" "RGB" (convert palette color to RGB)
  // "HSV" "ARGB" "CMYK" (all three are retired)
  // "YBR_FULL" "YBR_FULL_422" (use CCIR 601-2 to convert to RGB)
  // "YBR_PARTIAL_422" "YBR_PARTIAL_420" (use CCIR 601-2 to convert to RGB)
  // "YBR_ICT" "YBR_RCT" (use ISO 10918-1 to convert to RGB)
  // See DICOM Ch. 3 Appendix C 7.6.3.1.2 for equations

  // endianness
  std::string transferSyntax =
    this->MetaData->Get(fileIndex, DC::TransferSyntaxUID).AsString();

  bool bigEndian = (transferSyntax == "1.2.840.10008.1.2.2" ||
                    transferSyntax == "1.2.840.113619.5.2");

#ifdef VTK_WORDS_BIGENDIAN
  this->SwapBytes = !bigEndian;
#else
  this->SwapBytes = bigEndian;
#endif

  // === Image Orientation in DICOM files ===
  //
  // The vtkImageData class does not provide a way of storing image
  // orientation.  So when we read a DICOM file, we should also provide
  // the user with a 4x4 matrix that can transform VTK's data coordinates
  // into DICOM's patient coordinates, as defined in the DICOM standard
  // Part 3 Appendix C 7.6.2 "Image Plane Module".

  vtkIdType numSlices = this->FileIndexArray->GetNumberOfTuples();
  std::vector<double> points;
  double centroid[3] = { 0.0, 0.0, 0.0 };
  double orient[6] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
  double point[3] = { 0.0, 0.0, 0.0 };
  double normal[3] = { 0.0, 0.0, 1.0 };

  // go through the slices in reverse order, so we end on the first
  for (vtkIdType iSlice = numSlices-1; iSlice >= 0; --iSlice)
  {
    int iFile = this->FileIndexArray->GetComponent(iSlice, 0);
    int iFrame = this->FrameIndexArray->GetComponent(iSlice, 0);
    vtkDICOMValue pv =
       this->MetaData->Get(iFile, iFrame, DC::ImagePositionPatient);
    vtkDICOMValue ov =
      this->MetaData->Get(fileIndex, frameIndex, DC::ImageOrientationPatient);
    if (pv.GetNumberOfValues() == 3 && ov.GetNumberOfValues() == 6)
    {
      pv.GetValues(point, 3);
      ov.GetValues(orient, 6);
      vtkMath::Cross(&orient[0], &orient[3], normal);
      if (vtkMath::Normalize(normal) < 1e-10)
      {
        orient[0] = 1.0; orient[1] = 0.0; orient[2] = 0.0;
        orient[3] = 0.0; orient[4] = 1.0; orient[5] = 0.0;
        normal[0] = 0.0; normal[1] = 0.0; normal[2] = 1.0;
      }
      // re-orthogonalize x vector (improve precision)
      vtkMath::Cross(&orient[3], normal, &orient[0]);
      vtkMath::Normalize(&orient[0]);
      vtkMath::Normalize(&orient[3]);

      if (this->MemoryRowOrder == vtkDICOMReader::BottomUp)
      {
        // calculate position of point at lower left
        double yspacing = this->DataSpacing[1];
        point[0] = point[0] + orient[3]*yspacing*(rows - 1);
        point[1] = point[1] + orient[4]*yspacing*(rows - 1);
        point[2] = point[2] + orient[5]*yspacing*(rows - 1);

        orient[3] = -orient[3];
        orient[4] = -orient[4];
        orient[5] = -orient[5];
      }

      size_t ip = points.size();
      points.resize(ip + 3);
      for (int ii = 0; ii < 3; ii++)
      {
        centroid[ii] += point[ii];
        points[ip+ii] = point[ii];
      }
    }
  }

  // compute Z vector by fitting points to a line
  double vector[3] = { normal[0], normal[1], normal[2] };
  size_t nPoints = points.size()/3;
  if (nPoints > 0)
  {
    centroid[0] /= nPoints;
    centroid[1] /= nPoints;
    centroid[2] /= nPoints;

    // use Jacobi to compute line of best fit
    double storage[18] = {};
    double *A[3] = { &storage[0], &storage[3], &storage[6] };
    double *E[3] = { &storage[9], &storage[12], &storage[15] };
    for (size_t iPoint = 0; iPoint < nPoints; iPoint++)
    {
      for (int ii = 0; ii < 3; ii++)
      {
        for (int jj = 0; jj < 3; jj++)
        {
          A[ii][jj] = ((points[3*iPoint + ii] - centroid[ii]) *
                       (points[3*iPoint + jj] - centroid[jj]));
        }
      }
    }
    double eigenvalues[3];
    vtkMath::Jacobi(A, eigenvalues, E);

    // only use eigenvector if the points fit a line very precisely
    if (eigenvalues[1]*eigenvalues[1] + eigenvalues[2]*eigenvalues[2] <
        1e-6*eigenvalues[0]*eigenvalues[0])
    {
      // create the vector, dot(vector,normal) should be unity
      double vdn = E[0][0]*normal[0] + E[1][0]*normal[1] + E[2][0]*normal[2];
      if (vdn > 0)
      {
        vector[0] = E[0][0]/vdn;
        vector[1] = E[1][0]/vdn;
        vector[2] = E[2][0]/vdn;

        // check difference between this vector and the normal
        double vcn[3];
        vtkMath::Cross(vector, normal, vcn);
        if (vtkMath::Norm(vcn) < 1e-4)
        {
          // use normal (more precise) if they are the same
          vector[0] = normal[0];
          vector[1] = normal[1];
          vector[2] = normal[2];
        }
      }
    }

    // build the patient matrix
    double pm[16];
    pm[0] = orient[0]; pm[1] = orient[3]; pm[2] = vector[0]; pm[3] = point[0];
    pm[4] = orient[1]; pm[5] = orient[4]; pm[6] = vector[1]; pm[7] = point[1];
    pm[8] = orient[2]; pm[9] = orient[5]; pm[10] = vector[2]; pm[11] = point[2];
    pm[12] = 0.0; pm[13] = 0.0; pm[14] = 0.0; pm[15] = 1.0;

    this->PatientMatrix->DeepCopy(pm);
  }
  else
  {
    this->PatientMatrix->Identity();
  }

  // Set the medical image properties
  if (this->MedicalImageProperties)
  {
    this->UpdateMedicalImageProperties();
  }

  // Set the output information.
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               extent, 6);

  outInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(),  this->DataOrigin, 3);

  vtkDataObject::SetPointDataActiveScalarInfo(
    outInfo, this->DataScalarType, this->NumberOfScalarComponents);

  outInfo->Set(vtkDICOMAlgorithm::META_DATA(), this->MetaData);
  outInfo->Set(vtkDICOMAlgorithm::PATIENT_MATRIX(),
               *this->PatientMatrix->Element, 16);

  // Check for overlays (60xx,3000)
  unsigned short overlayBits = 0;
  for (unsigned short i = 0; i < 16; i++)
  {
    unsigned short g = 0x6000 + 2*i;
    if (this->MetaData->Has(vtkDICOMTag(g, 0x3000)))
    {
      overlayBits |= (1 << i);
    }
  }

  // Set the information for the overlay
  if (overlayBits)
  {
    vtkInformation* oInfo = outputVector->GetInformationObject(1);
    oInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent, 6);

    oInfo->Set(vtkDataObject::SPACING(), this->DataSpacing, 3);
    oInfo->Set(vtkDataObject::ORIGIN(),  this->DataOrigin, 3);

    int overlayType =
      (overlayBits <= 255 ? VTK_UNSIGNED_CHAR : VTK_UNSIGNED_SHORT);
    int overlayComponents =
      this->FileIndexArray->GetNumberOfComponents();

    vtkDataObject::SetPointDataActiveScalarInfo(
      oInfo, overlayType, overlayComponents);

    oInfo->Set(vtkDICOMAlgorithm::PATIENT_MATRIX(),
               *this->PatientMatrix->Element, 16);
  }

  this->OverlayBitfield = overlayBits;

  return 1;
}

namespace {

//----------------------------------------------------------------------------
// templated conversion functions, for converting to and from floating point

template<class T1, class T2>
void vtkDICOMConvertBuffer(const T1 *ip, T2 *op, int im, int om, size_t n)
{
  if (n > 0)
  {
    T1 minval = vtkTypeTraits<T2>::Min();
    T1 maxval = vtkTypeTraits<T2>::Max();
    do
    {
      T1 v = *ip;
      v = (v > minval ? v : minval);
      v = (v < maxval ? v : maxval);
      *op = static_cast<T2>(v);
      ip += im;
      op += om;
    }
    while (--n);
  }
}

template<class T>
void vtkDICOMConvertBuffer(const T *ip, float *op, int im, int om, size_t n)
{
  if (n > 0)
  {
    do
    {
      *op = *ip;
      ip += im;
      op += om;
    }
    while (--n);
  }
}

template<class T>
void vtkDICOMConvertBuffer(const T *ip, double *op, int im, int om, size_t n)
{
  if (n > 0)
  {
    do
    {
      *op = *ip;
      ip += im;
      op += om;
    }
    while (--n);
  }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMReader::RescaleBuffer(
  int fileIdx, int frameIdx, int fileType, int outputType,
  int fileNumComponents, int numComponents,
  void *fileBuffer, void *outputBuffer, vtkIdType bufferSize)
{
  vtkDICOMMetaData *meta = this->MetaData;
  double m = meta->Get(fileIdx, frameIdx, DC::RescaleSlope).AsDouble();
  double b = meta->Get(fileIdx, frameIdx, DC::RescaleIntercept).AsDouble();

  if (m == 0.0)
  {
    m = 1.0;
  }

  int inSize = vtkDataArray::GetDataTypeSize(fileType);
  int outSize = vtkDataArray::GetDataTypeSize(outputType);
  size_t numPixels = bufferSize/(inSize*fileNumComponents);

  for (int c = 0; c < fileNumComponents; c++)
  {
    void *filePtr = static_cast<char *>(fileBuffer) + inSize*c;
    void *outputPtr = static_cast<char *>(outputBuffer) + outSize*c;
    size_t n = numPixels;

    while (n > 0)
    {
      double temp[64];
      size_t nn = (n < 64 ? n : 64);
      n -= nn;

      switch (fileType)
      {
        vtkTemplateAliasMacro(
          vtkDICOMConvertBuffer(
            static_cast<const VTK_TT *>(filePtr), temp,
            fileNumComponents, 1, nn));
      }

      if (this->AutoRescale)
      {
        for (size_t ii = 0; ii < nn; ii++)
        {
          temp[ii] = temp[ii]*m + b;
        }
      }

      switch (outputType)
      {
        vtkTemplateAliasMacro(
          vtkDICOMConvertBuffer(
            temp, static_cast<VTK_TT *>(outputPtr),
            1, numComponents, nn));
      }

      filePtr = static_cast<char *>(filePtr) + inSize*fileNumComponents*nn;
      outputPtr = static_cast<char *>(outputPtr) + outSize*numComponents*nn;
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMReader::YBRToRGB(
  int fileIdx, int, void *buffer, vtkIdType bufferSize)
{
  // digital luminance levels and color levels from Rec. 601
  const int ylevels = 220;
  const int clevels = 225;

  // the digital black level from Rec. 601
  double ymin = 16.0;

  // the color constants from Rec. 601
  const double Kb = 0.114;
  const double Kr = 0.299;
  double Kg = 1.0 - Kb - Kr;

  // compute the matrix for YPbPr to RGB conversion
  double matrix[3][3] = {
    { 1.0,  0.0,                 2.0*(1.0-Kr)       },
    { 1.0, -2.0*Kb*(1.0-Kb)/Kg, -2.0*Kr*(1.0-Kr)/Kg },
    { 1.0,  2.0*(1.0-Kb),        0.0                }
  };

  // get information from the meta data
  vtkDICOMMetaData *meta = this->MetaData;
  const vtkDICOMValue& photometric =
    meta->Get(fileIdx, DC::PhotometricInterpretation);
  const vtkDICOMValue& transferSyntax =
    meta->Get(fileIdx, DC::TransferSyntaxUID);

  // catch JPEG baseline images with incorrect PhotometricInterpretation
  if (transferSyntax.Matches("1.2.840.10008.1.2.4.50") ||
      photometric.Matches("YBR_FULL*"))
  {
    // use full-range, therefore black level is zero
    ymin = 0.0;
  }
  else if (photometric.Matches("YBR_PARTIAL*"))
  {
    // stretch the matrix so that full-range RGB is produced
    for (int i = 0; i < 3; i++)
    {
      matrix[i][0] *= 255.0/(ylevels - 1);
      matrix[i][1] *= 255.0/(clevels - 1);
      matrix[i][2] *= 255.0/(clevels - 1);
    }
  }
  else
  {
    // no YBR here, so exit!
    return;
  }

  if (bufferSize >= 3)
  {
    unsigned char *cp = static_cast<unsigned char *>(buffer);
    vtkIdType n = bufferSize/3;
    double ybr[3];
    double rgb[3];
    do
    {
      ybr[0] = cp[0] - ymin;
      ybr[1] = cp[1] - 128.0;
      ybr[2] = cp[2] - 128.0;

      vtkMath::Multiply3x3(matrix, ybr, rgb);

      rgb[0] = (rgb[0] >= 0.0 ? rgb[0] : 0.0);
      rgb[0] = (rgb[0] <= 255.0 ? rgb[0] : 255.0);
      rgb[1] = (rgb[1] >= 0.0 ? rgb[1] : 0.0);
      rgb[1] = (rgb[1] <= 255.0 ? rgb[1] : 255.0);
      rgb[2] = (rgb[2] >= 0.0 ? rgb[2] : 0.0);
      rgb[2] = (rgb[2] <= 255.0 ? rgb[2] : 255.0);

      cp[0] = static_cast<unsigned char>(vtkMath::Floor(rgb[0] + 0.5));
      cp[1] = static_cast<unsigned char>(vtkMath::Floor(rgb[1] + 0.5));
      cp[2] = static_cast<unsigned char>(vtkMath::Floor(rgb[2] + 0.5));

      cp += 3;
    }
    while (--n);
  }
}

//----------------------------------------------------------------------------
void vtkDICOMReader::UnpackBits(
  const void *filePtr, void *buffer, vtkIdType bufferSize, int bits)
{
  if (bits == 12)
  {
    const unsigned char *readPtr =
      static_cast<const unsigned char *>(filePtr);
    unsigned char *writePtr =
      static_cast<unsigned char *>(buffer);
    for (vtkIdType n = bufferSize/2; n > 0; n -= 2)
    {
      unsigned int a1 = readPtr[0];
      unsigned int a2 = readPtr[1];
      unsigned int b1 = (a1 << 4) | (a2 & 0x0f);
      writePtr[0] = static_cast<unsigned char>(b1);
      writePtr[1] = static_cast<unsigned char>(b1 >> 8);

      if (n == 1) { break; }

      unsigned int a3 = readPtr[2];
      unsigned int b2 = ((a3 & 0x0f) << 8) | (a2 & 0xf0) | (a3 >> 4);
      writePtr[2] = static_cast<unsigned char>(b2);
      writePtr[3] = static_cast<unsigned char>(b2 >> 8);

      readPtr += 3;
      writePtr += 4;
    }
  }
  else if (bits == 1)
  {
    const unsigned char *readPtr =
      static_cast<const unsigned char *>(filePtr);
    unsigned char *writePtr =
      static_cast<unsigned char *>(buffer);
    for (vtkIdType n = bufferSize/8; n > 0; n--)
    {
      unsigned int a = *readPtr;
      for (int i = 0; i < 8; i++)
      {
        writePtr[i] = (a & 1);
        a >>= 1;
      }
      readPtr++;
      writePtr += 8;
    }
    size_t r = (bufferSize % 8);
    if (r > 0)
    {
      unsigned int a = *readPtr;
      for (size_t j = 0; j < r; j++)
      {
        writePtr[j] = static_cast<unsigned char>(a & 1);
        a >>= 1;
      }
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMReader::UnpackOverlay(
  const void *filePtr, vtkIdType bitskip, vtkIdType count,
  void *buffer, vtkIdType incr, int bit)
{
  const unsigned char *readPtr =
    static_cast<const unsigned char *>(filePtr);
  unsigned char *writePtr =
    static_cast<unsigned char *>(buffer);

  readPtr += bitskip/8;
  int r = (bitskip % 8);
  if (r > 0)
  {
    unsigned char a = *readPtr;
    a >>= r;
    for (int i = r; i < 8; i++)
    {
      *writePtr |= (a & 1) << bit;
      a >>= 1;
      writePtr += incr;
    }
    count -= (8 - r);
    readPtr++;
  }

  for (vtkIdType n = count/8; n > 0; n--)
  {
    unsigned char a = *readPtr;
    for (int i = 0; i < 8; i++)
    {
      *writePtr |= (a & 1) << bit;
      a >>= 1;
      writePtr += incr;
    }
    readPtr++;
  }
  count = (count % 8);

  if (count > 0)
  {
    unsigned char a = *readPtr;
    for (int i = 0; i < count; i++)
    {
      *writePtr |= (a & 1) << bit;
      a >>= 1;
      writePtr += incr;
    }
  }
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadFileNative(
  const char *filename, int fileIdx,
  unsigned char *buffer, vtkIdType bufferSize)
{
  // get the offset to the PixelData in the file
  vtkTypeInt64 offsetAndSize[2];
  this->FileOffsetArray->GetTupleValue(fileIdx, offsetAndSize);
  vtkTypeInt64 offset = offsetAndSize[0];

  vtkDebugMacro("Opening DICOM file " << filename);
  vtkDICOMFile infile(filename, vtkDICOMFile::In);

  if (infile.GetError())
  {
    this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
    vtkErrorMacro("ReadFile: Can't read the file " << filename);
    return false;
  }

  if (!infile.SetPosition(offset))
  {
    this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
    vtkErrorMacro("DICOM file is truncated, some data is missing.");
    infile.Close();
    return false;
  }

  std::string transferSyntax =
    this->MetaData->Get(fileIdx, DC::TransferSyntaxUID).AsString();

  // this will set endiancheck.s to 1 on big endian architectures
  union { char c[2]; short s; } endianCheck = { { 0, 1 } };
  bool memoryBigEndian = (endianCheck.s == 1);
  bool fileBigEndian = (transferSyntax == "1.2.840.10008.1.2.2" ||
                        transferSyntax == "1.2.840.113619.5.2");

  int bitsAllocated =
    this->MetaData->Get(fileIdx, DC::BitsAllocated).AsInt();

  size_t readSize = bufferSize;
  size_t resultSize = 0;
  if (transferSyntax == "1.2.840.10008.1.2.5")
  {
    vtkDICOMImageCodec codec(transferSyntax);

    unsigned int numFrames =
      this->MetaData->Get(fileIdx, DC::NumberOfFrames).AsUnsignedInt();
    numFrames = (numFrames == 0 ? 1 : numFrames);

    // assume the remainder of the file is all pixel data
    readSize = static_cast<size_t>(
      offsetAndSize[1] - offsetAndSize[0]);
    if (readSize < 8)
    {
      readSize = 8;
    }
    unsigned char *rleBuffer = new unsigned char[readSize];
    unsigned char *filePtr = rleBuffer;
    resultSize = infile.Read(filePtr, readSize);
    size_t bytesRemaining = resultSize;
    vtkIdType bufferPos = 0;
    vtkIdType frameSize = bufferSize/numFrames;
    bool isOffsetTable = true;
    while (bytesRemaining >= 8 && bufferPos < bufferSize)
    {
      // get the item header
      unsigned int tagkey = vtkDICOMUtilities::UnpackUnsignedInt(filePtr);
      unsigned int length = vtkDICOMUtilities::UnpackUnsignedInt(filePtr + 4);
      filePtr += 8;
      bytesRemaining -= 8;
      // make sure the tag is valid
      if (tagkey != 0xE000FFFE)
      {
        break;
      }
      if (length > bytesRemaining)
      {
        // actual file size should have been at least this much larger
        readSize += length - bytesRemaining;
        length = static_cast<unsigned int>(bytesRemaining);
      }
      // first item is the offset table
      if (!isOffsetTable)
      {
        // unpack an RLE fragment
        codec.Decode(this->MetaData,
          filePtr, length, buffer + bufferPos, frameSize);
        bufferPos += frameSize;
      }
      filePtr += length;
      bytesRemaining -= length;
      isOffsetTable = false;
    }
    delete [] rleBuffer;
  }
  else if (bitsAllocated == 12)
  {
    // unpack 12 bits little endian into 16 bits little endian,
    // the result will have to be swapped if machine is BE (the
    // swapping is done at the end of this function)
    readSize = bufferSize/2 + (bufferSize+3)/4;
    unsigned char *filePtr = buffer + (bufferSize - readSize);
    resultSize = infile.Read(filePtr, readSize);

    vtkDICOMReader::UnpackBits(filePtr, buffer, bufferSize, bitsAllocated);
  }
  else if (bitsAllocated == 1)
  {
    // unpack 1 bit into 8 bits, source assumed to be either OB
    // or little endian OW, never big endian OW
    readSize = (bufferSize + 7)/8;
    unsigned char *filePtr = buffer + (bufferSize - readSize);
    resultSize = infile.Read(filePtr, readSize);

    vtkDICOMReader::UnpackBits(filePtr, buffer, bufferSize, bitsAllocated);
  }
  else
  {
    resultSize = infile.Read(buffer, readSize);
  }

  bool success = true;
  if (infile.EndOfFile() || resultSize != readSize)
  {
    this->SetErrorCode(vtkErrorCode::PrematureEndOfFileError);
    vtkErrorMacro("DICOM file is truncated, " <<
      (readSize - resultSize) << " bytes are missing.");
    success = false;
  }
  else if (infile.GetError())
  {
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    vtkErrorMacro("Error in DICOM file, cannot read.");
    success = false;
  }
  else if (fileBigEndian != memoryBigEndian)
  {
    int scalarSize = vtkDataArray::GetDataTypeSize(this->DataScalarType);
    vtkByteSwap::SwapVoidRange(buffer, bufferSize/scalarSize, scalarSize);
  }

  infile.Close();
  return success;
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadFileDelegated(
  const char *filename, int fileIdx,
  unsigned char *buffer, vtkIdType bufferSize)
{
#if defined(DICOM_USE_DCMTK)
  // For JPEG, DCMTK will do the YBR to RGB
  this->NeedsYBRToRGB = false;

#ifdef _WIN32
  // Convert utf8 filename to local character set for dcmtk
  vtkDICOMFilePath filePath(filename);
  filename = filePath.Local();
#endif

  DcmFileFormat *fileformat = new DcmFileFormat();
  fileformat->loadFile(filename);
  OFCondition status = fileformat->getDataset()->chooseRepresentation(
    EXS_LittleEndianExplicit, NULL);

  if (!status.good())
  {
    vtkErrorMacro("DCMTK error: " << status.text());
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    delete fileformat;
    return false;
  }

  unsigned long count;
  const Uint8 *pixelData;
  status = fileformat->getDataset()->findAndGetUint8Array(
    DCM_PixelData, pixelData, &count, OFTrue);
  vtkIdType imageSize = static_cast<vtkIdType>(count);

  int bitsAllocated =
    this->MetaData->Get(fileIdx, DC::BitsAllocated).AsInt();

  if (bitsAllocated == 12 && imageSize >= bufferSize/2 + (bufferSize+3)/4)
  {
    vtkDICOMReader::UnpackBits(pixelData, buffer, bufferSize, bitsAllocated);
  }
  else if (bitsAllocated == 1 && imageSize >= (bufferSize + 7)/8)
  {
    vtkDICOMReader::UnpackBits(pixelData, buffer, bufferSize, bitsAllocated);
  }
  else if (imageSize >= bufferSize)
  {
    memcpy(buffer, pixelData, bufferSize);
  }
  else
  {
    vtkErrorMacro(<< filename << ": The uncompressed image size is "
                  << imageSize << " bytes, expected "
                  << bufferSize << " bytes.");
    delete fileformat;
    return false;
  }

  delete fileformat;
  return true;

#elif defined(DICOM_USE_GDCM)

  (void)fileIdx;

#ifdef _WIN32
  // Convert utf8 filename to local character set for gdcm
  vtkDICOMFilePath filePath(filename);
  filename = filePath.Local();
#endif

  gdcm::ImageReader reader;
  reader.SetFileName(filename);
  if(!reader.Read())
  {
    vtkErrorMacro("The GDCM ImageReader could not read the image.");
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return false;
  }

  gdcm::Image &image = reader.GetImage();
  if (static_cast<vtkIdType>(image.GetBufferLength()) < bufferSize)
  {
    vtkErrorMacro(<< filename << ": The uncompressed image size is "
                  << image.GetBufferLength() << " bytes, expected "
                  << bufferSize << " bytes.");
    this->SetErrorCode(vtkErrorCode::FileFormatError);
    return false;
  }

  image.GetBuffer(reinterpret_cast<char *>(buffer));
  return true;

#else /* no DCMTK or GDCM, so no file decompression */

  (void)filename;
  (void)fileIdx;
  (void)buffer;
  (void)bufferSize;

  this->SetErrorCode(vtkErrorCode::FileFormatError);
  vtkErrorMacro("DICOM file is compressed, cannot read.");
  return false;

#endif
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadOneFile(
  const char *filename, int fileIdx,
  unsigned char *buffer, vtkIdType bufferSize)
{
  std::string transferSyntax =
    this->MetaData->Get(fileIdx, DC::TransferSyntaxUID).AsString();

  if (transferSyntax == "1.2.840.10008.1.2"   ||  // Implicit LE
      transferSyntax == "1.2.840.10008.1.20"  ||  // Papyrus Implicit LE
      transferSyntax == "1.2.840.10008.1.2.1" ||  // Explicit LE
      transferSyntax == "1.2.840.10008.1.2.2" ||  // Explicit BE
      transferSyntax == "1.2.840.10008.1.2.5" ||  // RLE compressed
      transferSyntax == "1.2.840.113619.5.2"  ||  // GE LE with BE data
      transferSyntax == "")
  {
    return this->ReadFileNative(filename, fileIdx, buffer, bufferSize);
  }

  return this->ReadFileDelegated(filename, fileIdx, buffer, bufferSize);
}

//----------------------------------------------------------------------------
void vtkDICOMReader::Update()
{
  this->Update(0);
  if (this->GetErrorCode() == vtkErrorCode::NoError &&
      this->OverlayBitfield != 0)
  {
    this->Update(1);
  }
}

//----------------------------------------------------------------------------
int vtkDICOMReader::ProcessRequest(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  if (request->Has(vtkDemandDrivenPipeline::REQUEST_DATA_NOT_GENERATED()))
  {
    // which output port did the request come from
    int outputPort =
      request->Get(vtkDemandDrivenPipeline::FROM_OUTPUT_PORT());
    int n = outputVector->GetNumberOfInformationObjects();
    // set DATA_NOT_GENERATED on other ports, otherwise executive will
    // initialize them before RequestData is called
    for (int i = 0; i < n; i++)
    {
      if (i != outputPort)
      {
        vtkInformation *outputInfo = outputVector->GetInformationObject(i);
        outputInfo->Set(vtkDemandDrivenPipeline::DATA_NOT_GENERATED(), 1);
      }
    }
  }

  return this->Superclass::ProcessRequest(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
int vtkDICOMReader::RequestData(
  vtkInformation* request,
  vtkInformationVector** vtkNotUsed(inputVector),
  vtkInformationVector* outputVector)
{
  // check whether the reader is in an error state
  if (this->GetErrorCode() != vtkErrorCode::NoError)
  {
    return false;
  }

  // which output port did the request come from
  int outputPort =
    request->Get(vtkDemandDrivenPipeline::FROM_OUTPUT_PORT());

  // if outputPort is out of range, return
  if (outputPort > 1)
  {
    return true;
  }

  // check for the overlay output
  if (outputPort == 1)
  {
    vtkInformation* outInfo = outputVector->GetInformationObject(1);
    int uExtent[6];
    outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), uExtent);
    // get the overlay data object, allocate memory
    vtkImageData *data =
      static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));
  #if VTK_MAJOR_VERSION >= 6
    this->AllocateOutputData(data, outInfo, uExtent);
  #else
    data->SetExtent(uExtent);
    data->AllocateScalars();
  #endif
    this->ReadOverlays(data);
    return true;
  }

  // do the main output
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
  int nComp = this->FileIndexArray->GetNumberOfComponents();
  for (int sIdx = extent[4]; sIdx <= extent[5]; sIdx++)
  {
    for (int cIdx = 0; cIdx < nComp; cIdx++)
    {
      int fileIdx = this->FileIndexArray->GetComponent(sIdx, cIdx);
      int frameIdx = this->FrameIndexArray->GetComponent(sIdx, cIdx);
      std::vector<vtkDICOMReaderFileInfo>::iterator iter = files.begin();
      while (iter != files.end() && iter->FileIndex != fileIdx)
      {
        ++iter;
      }
      if (iter == files.end())
      {
        int n = this->MetaData->Get(fileIdx, DC::NumberOfFrames).AsInt();
        n = (n > 0 ? n : 1);
        files.push_back(vtkDICOMReaderFileInfo(fileIdx, n));
        iter = files.end();
        --iter;
      }
      iter->Frames.push_back(vtkDICOMReaderFrameInfo(frameIdx, sIdx, cIdx));
    }
  }

  // get the data object, allocate memory
  vtkImageData *data =
    static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));
#if VTK_MAJOR_VERSION >= 6
  this->AllocateOutputData(data, outInfo, extent);
#else
  data->SetExtent(extent);
  data->AllocateScalars();
#endif

  // label the scalars as "PixelData"
  data->GetPointData()->GetScalars()->SetName("PixelData");

  // add the meta data to the data set
  vtkInformation *dataInfo = data->GetInformation();
  dataInfo->Set(vtkDICOMAlgorithm::META_DATA(), this->MetaData);
  dataInfo->Set(vtkDICOMAlgorithm::PATIENT_MATRIX(),
                *this->PatientMatrix->Element, 16);

  unsigned char *dataPtr =
    static_cast<unsigned char *>(data->GetScalarPointer());

  int scalarType = data->GetScalarType();
  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();
  int numFileComponents = this->NumberOfPackedComponents;
  int numPlanes = this->NumberOfPlanarComponents;

  vtkIdType pixelSize = numComponents*scalarSize;
  vtkIdType rowSize = pixelSize*(extent[1] - extent[0] + 1);
  vtkIdType sliceSize = rowSize*(extent[3] - extent[2] + 1);

  int fileScalarSize = vtkDataArray::GetDataTypeSize(this->FileScalarType);
  vtkIdType filePixelSize = numFileComponents*fileScalarSize;
  vtkIdType fileRowSize = filePixelSize*(extent[1] - extent[0] + 1);
  vtkIdType filePlaneSize = fileRowSize*(extent[3] - extent[2] + 1);
  vtkIdType fileFrameSize = filePlaneSize*numPlanes;

  this->InvokeEvent(vtkCommand::StartEvent);

  bool flipImage = (this->MemoryRowOrder == vtkDICOMReader::BottomUp);
  bool planarToPacked = (numFileComponents != numComponents);
  unsigned char *rowBuffer = 0;
  if (flipImage)
  {
    rowBuffer = new unsigned char[fileRowSize];
  }
  unsigned char *fileBuffer = 0;
  int framesInPreviousFile = -1;

  // loop through all files in the update extent
  for (size_t idx = 0; idx < files.size(); idx++)
  {
    if (this->AbortExecute) { break; }

    this->UpdateProgress(static_cast<double>(idx)/
                         static_cast<double>(files.size()));

    // get the index for this file
    int fileIdx = files[idx].FileIndex;
    int framesInFile = files[idx].FramesInFile;
    std::vector<vtkDICOMReaderFrameInfo>& frames = files[idx].Frames;
    int numFrames = static_cast<int>(frames.size());

    // we need a file buffer if input frames don't match output slices,
    // or if input data type doesn't match output data type
    bool needBuffer = (planarToPacked ||
                       numFrames != framesInFile ||
                       scalarSize != fileScalarSize);
    for (int sIdx = 0; sIdx < numFrames && !needBuffer; sIdx++)
    {
      needBuffer = (sIdx != frames[sIdx].FrameIndex);
    }

    unsigned char *bufferPtr = 0;

    if (needBuffer)
    {
      // allocate a buffer for format or datatype conversion
      if (numFrames != framesInPreviousFile)
      {
        delete [] fileBuffer;
        fileBuffer = new unsigned char[fileFrameSize*framesInFile];
        framesInPreviousFile = numFrames;
      }
      bufferPtr = fileBuffer;
    }
    else
    {
      // read directly into the output
      int sliceIdx = frames[0].SliceIndex;
      int componentIdx = frames[0].ComponentIndex;
      bufferPtr = (dataPtr +
                   (sliceIdx - extent[4])*sliceSize +
                   componentIdx*filePixelSize*numPlanes);
    }

    // ReadOneFile will set NeedsYBRToRGB to false if it does YBR->RGB itself
    // (note: NeedsYBRToRGB will is ignored unless PhotometricInterpretation
    // is YBR_FULL* or YBR_PARTIAL*)
    this->NeedsYBRToRGB = (this->AutoYBRToRGB &&
                           numComponents == 3 &&
                           scalarSize == 1);

    this->ComputeInternalFileName(fileIdx);
    this->ReadOneFile(this->InternalFileName, fileIdx,
                      bufferPtr, framesInFile*fileFrameSize);

    // iterate through all frames contained in the file
    for (int sIdx = 0; sIdx < numFrames; sIdx++)
    {
      int frameIdx = frames[sIdx].FrameIndex;
      int sliceIdx = frames[sIdx].SliceIndex;
      int componentIdx = frames[sIdx].ComponentIndex;
      // go to the correct position in the input
      unsigned char *framePtr = bufferPtr + frameIdx*fileFrameSize;
      // go to the correct position in the output
      unsigned char *slicePtr =
        (dataPtr + (sliceIdx - extent[4])*sliceSize +
         componentIdx*filePixelSize*numPlanes);

      // iterate through all color planes in the slice
      unsigned char *planePtr = framePtr;
      for (int pIdx = 0; pIdx < numPlanes; pIdx++)
      {
        // flip the data if necessary
        if (flipImage)
        {
          int numRows = extent[3] - extent[2] + 1;
          int halfRows = numRows/2;
          for (int yIdx = 0; yIdx < halfRows; yIdx++)
          {
            unsigned char *row1 = planePtr + yIdx*fileRowSize;
            unsigned char *row2 = planePtr + (numRows-yIdx-1)*fileRowSize;
            memcpy(rowBuffer, row1, fileRowSize);
            memcpy(row1, row2, fileRowSize);
            memcpy(row2, rowBuffer, fileRowSize);
          }
        }

        // convert planes into vector components
        if (this->NeedsRescale)
        {
          this->RescaleBuffer(
            fileIdx, frameIdx, this->FileScalarType, scalarType,
            numFileComponents, numComponents, planePtr, slicePtr,
            filePlaneSize);
        }
        else if (planarToPacked)
        {
          const unsigned char *tmpInPtr = planePtr;
          unsigned char *tmpOutPtr = slicePtr;
          int m = sliceSize/pixelSize;
          for (int i = 0; i < m; i++)
          {
            vtkIdType n = filePixelSize;
            do { *tmpOutPtr++ = *tmpInPtr++; } while (--n);
            tmpOutPtr += pixelSize - filePixelSize;
          }
          slicePtr += filePixelSize;
        }
        else if (slicePtr != planePtr)
        {
          memcpy(slicePtr, planePtr, filePlaneSize);
        }

        planePtr += filePlaneSize;
      }

      // convert to RGB if data was read from file as YUV
      if (this->NeedsYBRToRGB)
      {
        this->YBRToRGB(fileIdx, frameIdx, slicePtr, sliceSize);
      }
    }
  }

  delete [] rowBuffer;
  delete [] fileBuffer;

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}

//----------------------------------------------------------------------------
bool vtkDICOMReader::ReadOverlays(vtkImageData *data)
{
  int extent[6];
  data->GetExtent(extent);
  int nComp = this->FileIndexArray->GetNumberOfComponents();
  unsigned char *ptr = static_cast<unsigned char *>(data->GetScalarPointer());
  int scalarSize = data->GetScalarSize();
  memset(ptr, 0, scalarSize*data->GetNumberOfPoints());

  for (int sIdx = extent[4]; sIdx <= extent[5]; sIdx++)
  {
    for (int cIdx = 0; cIdx < nComp; cIdx++)
    {
      int fileIdx = this->FileIndexArray->GetComponent(sIdx, cIdx);
      int frameIdx = this->FrameIndexArray->GetComponent(sIdx, cIdx);
      int rows = this->MetaData->Get(fileIdx, DC::Rows).AsInt();

      // loop through all possible overlays
      int maxOverlay = (scalarSize > 1 ? 15 : 7);
      for (int i = 0; i <= maxOverlay; i++)
      {
        // compute group number for this overlay
        unsigned short g = 0x6000 + 2*i;

        vtkDICOMValue o = this->MetaData->Get(fileIdx, vtkDICOMTag(g, 0x3000));
        const unsigned char *bptr = o.GetUnsignedCharData();
        if (bptr == 0)
        {
          bptr = reinterpret_cast<const unsigned char *>(
                 o.GetUnsignedShortData());
        }
        if (bptr == 0)
        {
          continue;
        }

        int sizeX = this->MetaData->Get(fileIdx, vtkDICOMTag(g,0x0011)).AsInt();
        int sizeY = this->MetaData->Get(fileIdx, vtkDICOMTag(g,0x0010)).AsInt();

        int startX = 0;
        int startY = 0;
        vtkDICOMValue ov = this->MetaData->Get(fileIdx, vtkDICOMTag(g,0x0040));
        if (ov.GetNumberOfValues() >= 2)
        {
          startX = ov.GetInt(1);
          startY = ov.GetInt(0);
          startX = (startX > 0 ? startX-1 : 0);
          startY = (startY > 0 ? startY-1 : 0);
        }

        int numFrames =
          this->MetaData->Get(fileIdx, vtkDICOMTag(g,0x0015)).AsInt();
        int frameOrigin =
          this->MetaData->Get(fileIdx, vtkDICOMTag(g,0x0051)).AsInt();
        frameOrigin = (frameOrigin > 0 ? frameOrigin-1 : 0);

        // make sure this frame exists in the overlay
        if (numFrames &&
            (frameIdx < frameOrigin || frameIdx > frameOrigin+numFrames-1))
        {
          continue;
        }

        // compute the number of frames to skip when reading the file
        vtkIdType inSkip =
          static_cast<vtkIdType>(frameIdx - frameOrigin)*sizeX*sizeY;

        // compute the initial offset into the output
        vtkIdType outSkip = static_cast<vtkIdType>(sIdx - extent[4])*
          (extent[3] - extent[2] + 1)*(extent[1] - extent[0] + 1);
        outSkip += cIdx*scalarSize;
        if (i > 7)
        {
          outSkip += 1;
        }

        vtkIdType outRowInc =
          static_cast<vtkIdType>(extent[1] - extent[0] + 1)*scalarSize*nComp;
        int extentY[2] = { extent[2], extent[3] };
        if (this->MemoryRowOrder == vtkDICOMReader::BottomUp)
        {
          outSkip += outRowInc*(extent[3]-extent[2]);
          outRowInc = -outRowInc;
          extentY[0] = rows - extent[3] - 1;
          extentY[1] = rows - extent[2] - 1;
        }

        // find the number of rows to read from the file
        int countY = sizeY;
        if (extentY[0] < startY)
        {
          outSkip += (startY - extentY[0])*outRowInc;
        }
        else
        {
          inSkip += static_cast<vtkIdType>(extentY[0] - startY)*sizeX;
          countY -= extentY[0] - startY;
        }
        if (startY + countY - 1 > extentY[1])
        {
          countY = extentY[1] - startY + 1;
        }

        // find the number of pixels per row to read from the file
        int countX = sizeX;
        if (extent[0] < startX)
        {
          outSkip +=
            static_cast<vtkIdType>(startX - extent[0])*scalarSize*nComp;
        }
        else
        {
          inSkip += extent[0] - startX;
          countX -= extent[0] - startX;
        }
        if (startX + countX - 1 > extent[1])
        {
          countX = extent[1] - startX + 1;
        }

        // make sure there is something to do
        if (countX <= 0 || countY <= 0)
        {
          continue;
        }

        for (int j = 0; j < countY; j++)
        {
          vtkDICOMReader::UnpackOverlay(
             bptr, inSkip, countX,
             ptr + outSkip, nComp*scalarSize, (i & 0x7));
          inSkip += sizeX;
          outSkip += outRowInc;
        }
      }
    }
  }

  return true;
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
    else
    {
      this->SetErrorCode(vtkErrorCode::UnknownError);
    }

    if (data)
    {
      vtkErrorMacro(<< static_cast<char *>(data));
    }
    else
    {
      vtkErrorMacro(<< "An unknown error ocurred!");
    }
  }
  else
  {
    this->InvokeEvent(e, data);
  }
}

//----------------------------------------------------------------------------
vtkImageData *vtkDICOMReader::GetOverlayOutput()
{
  return this->GetOutput(1);
}

//----------------------------------------------------------------------------
vtkAlgorithmOutput *vtkDICOMReader::GetOverlayOutputPort()
{
  return this->GetOutputPort(1);
}

//----------------------------------------------------------------------------
vtkMedicalImageProperties *vtkDICOMReader::GetMedicalImageProperties()
{
  if (this->MedicalImageProperties == 0)
  {
    this->MedicalImageProperties = vtkMedicalImageProperties::New();
    this->UpdateMedicalImageProperties();
  }

  return this->MedicalImageProperties;
}

//----------------------------------------------------------------------------
void vtkDICOMReader::UpdateMedicalImageProperties()
{
  vtkDICOMMetaData *meta = this->MetaData;
  vtkMatrix4x4 *matrix = this->PatientMatrix;
  vtkMedicalImageProperties *properties = this->MedicalImageProperties;

  const vtkDICOMValue *vptr;
  vptr = &meta->Get(DC::PatientName);
  properties->SetPatientName(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  vptr = &meta->Get(DC::PatientID);
  properties->SetPatientID(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  properties->SetPatientAge(meta->Get(DC::PatientAge).GetCharData());
  properties->SetPatientSex(meta->Get(DC::PatientSex).GetCharData());
  properties->SetPatientBirthDate(
    meta->Get(DC::PatientBirthDate).GetCharData());
  properties->SetStudyDate(meta->Get(DC::StudyDate).GetCharData());
  properties->SetAcquisitionDate(meta->Get(DC::AcquisitionDate).GetCharData());
  properties->SetStudyTime(meta->Get(DC::StudyTime).GetCharData());
  properties->SetAcquisitionTime(meta->Get(DC::AcquisitionTime).GetCharData());
  properties->SetImageDate(meta->Get(DC::ContentDate).GetCharData());
  properties->SetImageTime(meta->Get(DC::ContentTime).GetCharData());
  properties->SetImageNumber(meta->Get(DC::InstanceNumber).GetCharData());
  properties->SetSeriesNumber(meta->Get(DC::SeriesNumber).GetCharData());
  vptr = &meta->Get(DC::SeriesDescription);
  properties->SetSeriesDescription(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  vptr = &meta->Get(DC::StudyID);
  properties->SetStudyID(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  vptr = &meta->Get(DC::StudyDescription);
  properties->SetStudyDescription(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  properties->SetModality(meta->Get(DC::Modality).GetCharData());
  vptr = &meta->Get(DC::Manufacturer);
  properties->SetManufacturer(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  vptr = &meta->Get(DC::ManufacturerModelName);
  properties->SetManufacturerModelName(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  vptr = &meta->Get(DC::StationName);
  properties->SetStationName(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  vptr = &meta->Get(DC::InstitutionName);
  properties->SetInstitutionName(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  vptr = &meta->Get(DC::ConvolutionKernel);
  properties->SetConvolutionKernel(vptr->IsValid() ?
    vptr->AsUTF8String().c_str() : NULL);
  properties->SetSliceThickness(meta->Get(DC::SliceThickness).GetCharData());
  properties->SetKVP(meta->Get(DC::KVP).GetCharData());
  properties->SetGantryTilt(meta->Get(DC::GantryAngle).GetCharData());
  properties->SetEchoTime(meta->Get(DC::EchoTime).GetCharData());
  properties->SetEchoTrainLength(meta->Get(DC::EchoTrainLength).GetCharData());
  properties->SetRepetitionTime(meta->Get(DC::RepetitionTime).GetCharData());
  properties->SetExposureTime(meta->Get(DC::ExposureTime).GetCharData());
  properties->SetXRayTubeCurrent(meta->Get(DC::XRayTubeCurrent).GetCharData());
  properties->SetExposure(meta->Get(DC::Exposure).GetCharData());

  const vtkDICOMValue& center = meta->Get(DC::WindowCenter);
  const vtkDICOMValue& width = meta->Get(DC::WindowWidth);

  int n = static_cast<int>(center.GetNumberOfValues());
  int m = static_cast<int>(width.GetNumberOfValues());
  n = (m < n ? m : n);
  properties->RemoveAllWindowLevelPresets();
  for (int i = 0; i < n; i++)
  {
    properties->AddWindowLevelPreset(
      center.GetDouble(i), width.GetDouble(i));
  }

  const vtkDICOMValue& comment = meta->Get(DC::WindowCenterWidthExplanation);
  m = static_cast<int>(comment.GetNumberOfValues());
  m = (n < m ? n : m);
  for (int j = 0; j < m; j++)
  {
    properties->SetNthWindowLevelPresetComment(
      j, comment.GetString(j).c_str());
  }

  double dircos[6] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
  if (matrix)
  {
    for (int jj = 0; jj < 2; jj++)
    {
      for (int ii = 0; ii < 3; ii++)
      {
        dircos[ii + 3*jj] = matrix->GetElement(ii, jj);
      }
    }
  }
  properties->SetDirectionCosine(dircos);
}
