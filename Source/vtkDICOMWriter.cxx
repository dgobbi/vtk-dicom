/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2022 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMWriter.h"
#include "vtkDICOMAlgorithm.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMCompiler.h"
#include "vtkDICOMSCGenerator.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include "vtkObjectFactory.h"
#include "vtkIntArray.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkByteSwap.h"
#include "vtkMatrix4x4.h"
#include "vtkTrivialProducer.h"
#include "vtkAlgorithmOutput.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>

#include <algorithm>
#include <vector>

vtkStandardNewMacro(vtkDICOMWriter);
vtkCxxSetObjectMacro(vtkDICOMWriter,PatientMatrix,vtkMatrix4x4);
vtkCxxSetObjectMacro(vtkDICOMWriter,MetaData,vtkDICOMMetaData);
vtkCxxSetObjectMacro(vtkDICOMWriter,Generator,vtkDICOMGenerator);

//----------------------------------------------------------------------------
vtkDICOMWriter::vtkDICOMWriter()
{
  this->FileLowerLeft = 1;
  this->FileDimensionality = 2;
  this->MetaData = 0;
  this->GeneratedMetaData = 0;
  this->Generator = vtkDICOMSCGenerator::New();
  this->TimeAsVector = 0;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->RescaleIntercept = 0.0;
  this->RescaleSlope = 1.0;
  this->PatientMatrix = 0;
  this->MemoryRowOrder = vtkDICOMWriter::BottomUp;
  this->FileSliceOrder = vtkDICOMWriter::RHR;
  this->SeriesDescription = 0;
  this->TransferSyntaxUID = 0;
  this->ImageType = new char[24];
  strcpy(this->ImageType, "DERIVED/SECONDARY/OTHER");
  this->OverlayType = 0;
  this->Streaming = 0;

  // the second input is the overlay
  this->SetNumberOfInputPorts(2);
}

//----------------------------------------------------------------------------
vtkDICOMWriter::~vtkDICOMWriter()
{
  if (this->PatientMatrix)
  {
    this->PatientMatrix->Delete();
  }
  if (this->MetaData)
  {
    this->MetaData->Delete();
  }
  if (this->Generator)
  {
    this->Generator->Delete();
  }
  delete [] this->TransferSyntaxUID;
  delete [] this->SeriesDescription;
  delete [] this->ImageType;
}

//----------------------------------------------------------------------------
vtkDICOMMetaData *vtkDICOMWriter::GetMetaData()
{
  return this->MetaData;
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "SeriesDescription: " << this->SeriesDescription << "\n";
  os << indent << "ImageType: " << this->ImageType << "\n";
  os << indent << "OverlayType: "
     << (this->OverlayType ? "ROI\n" : "Graphics\n");
  os << indent << "TransferSyntaxUID: ";
  if (this->TransferSyntaxUID)
  {
    os << this->TransferSyntaxUID << "\n";
  }
  else
  {
    os << "(none)\n";
  }
  os << indent << "MetaData: ";
  if (this->MetaData)
  {
    os << this->MetaData << "\n";
  }
  else
  {
    os << "(none)\n";
  }
  os << indent << "Generator: ";
  if (this->Generator)
  {
    os << this->Generator << "\n";
  }
  else
  {
    os << "(none)\n";
  }
  os << indent << "TimeAsVector: "
     << (this->TimeAsVector ? "On\n" : "Off\n");
  os << indent << "TimeDimension: " << this->TimeDimension << "\n";
  os << indent << "TimeSpacing: " << this->TimeSpacing << "\n";
  os << indent << "RescaleIntercept: " << this->RescaleIntercept << "\n";
  os << indent << "RescaleSlope: " << this->RescaleSlope << "\n";

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
  os << indent << "FileSliceOrder: "
     << this->GetFileSliceOrderAsString() << "\n";
  os << indent << "Streaming: "
     << (this->Streaming ? "On\n" : "Off\n");
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::SetMemoryRowOrder(int order)
{
  if (order >= 0 && order <= vtkDICOMWriter::BottomUp)
  {
    if (order != this->MemoryRowOrder)
    {
      this->MemoryRowOrder = order;
      this->Modified();
    }
  }
}

//----------------------------------------------------------------------------
const char *vtkDICOMWriter::GetMemoryRowOrderAsString()
{
  const char *text = "";
  switch (this->MemoryRowOrder)
  {
    case vtkDICOMWriter::FileNative:
      text = "FileNative";
      break;
    case vtkDICOMWriter::TopDown:
      text = "TopDown";
      break;
    case vtkDICOMWriter::BottomUp:
      text = "BottomUp";
      break;
  }

  return text;
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::SetFileSliceOrder(int order)
{
  if (order >= 0 && order <= vtkDICOMWriter::Reverse)
  {
    if (order != this->FileSliceOrder)
    {
      this->FileSliceOrder = order;
      this->Modified();
    }
  }
}

//----------------------------------------------------------------------------
const char *vtkDICOMWriter::GetFileSliceOrderAsString()
{
  const char *text = "";
  switch (this->FileSliceOrder)
  {
    case vtkDICOMWriter::RHR:
      text = "RHR";
      break;
    case vtkDICOMWriter::LHR:
      text = "LHR";
      break;
    case vtkDICOMWriter::Same:
      text = "Same";
      break;
    case vtkDICOMWriter::Reverse:
      text = "Reverse";
      break;
  }

  return text;
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::ComputeInternalFileName(int slice)
{
  size_t n = 0;

  if (this->FileName)
  {
    n = strlen(this->FileName) + 1;
  }
  else if (this->FilePrefix)
  {
    n = strlen(this->FilePrefix) + strlen(this->FilePattern) + 10;
  }
  else
  {
    n = strlen(this->FilePattern) + 10;
  }

  if (this->InternalFileName == 0 ||
      strlen(this->InternalFileName) + 10 < n)
  {
    delete [] this->InternalFileName;
    this->InternalFileName = new char[n + 11];
  }

  if (this->FileName)
  {
    sprintf(this->InternalFileName, "%s", this->FileName);
  }
  else if (this->FilePrefix)
  {
    sprintf(this->InternalFileName,
            this->FilePattern, this->FilePrefix, slice);
  }
  else
  {
    sprintf(this->InternalFileName, this->FilePattern, slice);
  }
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::FreeInternalFileName()
{
  delete [] this->InternalFileName;
  this->InternalFileName = 0;
}

//----------------------------------------------------------------------------
int vtkDICOMWriter::GenerateMetaData(vtkInformation *info)
{
  if (this->GeneratedMetaData)
  {
    this->GeneratedMetaData->Delete();
    this->GeneratedMetaData = 0;
  }

  if (!this->Generator)
  {
    vtkErrorMacro("No Generator was supplied, unable to create a DICOM "
                  "data set");
    return 0;
  }

  // Check whether image is stored top-to-bottom or bottom-to-top
  bool flipImage = (this->MemoryRowOrder == vtkDICOMWriter::BottomUp);
  bool reverseSlices = flipImage;
  if (this->FileSliceOrder == vtkDICOMWriter::LHR)
  {
    reverseSlices = !flipImage;
  }
  else if (this->FileSliceOrder == vtkDICOMWriter::Same)
  {
    reverseSlices = false;
  }
  else if (this->FileSliceOrder == vtkDICOMWriter::Reverse)
  {
    reverseSlices = true;
  }

  // Get the meta data from the pipeline if not given explicitly
  vtkDICOMMetaData *inMeta = this->MetaData;
  vtkMatrix4x4 *inMatrix = this->PatientMatrix;
  vtkInformation *metaInfo = info;
  if (inMeta == 0 || inMatrix == 0)
  {
    // this code is needed for when SetInputData was used
    vtkAlgorithmOutput *sourceConnection = this->GetInputConnection(0, 0);
    if (sourceConnection)
    {
      vtkAlgorithm *producer = sourceConnection->GetProducer();
      if (producer && vtkTrivialProducer::SafeDownCast(producer))
      {
        vtkDataObject *inputData = producer->GetOutputDataObject(0);
        if (inputData)
        {
          metaInfo = inputData->GetInformation();
        }
      }
    }
  }
  if (inMeta == 0)
  {
    inMeta = vtkDICOMMetaData::SafeDownCast(
      metaInfo->Get(vtkDICOMAlgorithm::META_DATA()));
  }
  if (inMatrix == 0)
  {
    double *elements = metaInfo->Get(vtkDICOMAlgorithm::PATIENT_MATRIX());
    if (elements)
    {
      inMatrix = vtkMatrix4x4::New();
      inMatrix->DeepCopy(elements);
    }
  }
  else
  {
    inMatrix->Register(0);
  }

  // Generate the meta data
  this->Generator->SetMultiFrame(this->FileDimensionality > 2);
  this->Generator->SetOriginAtBottom(flipImage);
  this->Generator->SetReverseSliceOrder(reverseSlices);
  this->Generator->SetTimeAsVector(this->TimeAsVector);
  this->Generator->SetTimeDimension(this->TimeDimension);
  this->Generator->SetTimeSpacing(this->TimeSpacing);
  this->Generator->SetRescaleIntercept(this->RescaleIntercept);
  this->Generator->SetRescaleSlope(this->RescaleSlope);
  this->Generator->SetNumberOfOverlays(
    this->GetNumberOfInputConnections(1));
  this->Generator->SetSourceMetaData(inMeta);
  this->Generator->SetPatientMatrix(inMatrix);
  if (inMatrix)
  {
    inMatrix->Delete();
  }
  if (!this->Generator->GenerateInstance(info))
  {
    return 0;
  }
  this->GeneratedMetaData = this->Generator->GetMetaData();
  this->GeneratedMetaData->Register(this);
  vtkDICOMMetaData *meta = this->GeneratedMetaData;

  // set the series description from the member variable
  if (this->SeriesDescription && this->SeriesDescription[0] != '\0')
  {
    char sd[65];
    strncpy(sd, this->SeriesDescription, 64);
    sd[64] = '\0';
    meta->Set(DC::SeriesDescription, sd);
    meta->Erase(DC::SeriesDescriptionCodeSequence);
  }

  // set the image type from the member variable
  if (this->ImageType && this->ImageType[0] != '\0')
  {
    const char *allowedTypes[] = {
      "ORIGINAL\\PRIMARY", "DERIVED\\PRIMARY",
      "ORIGINAL\\SECONDARY", "DERIVED\\SECONDARY",
      0
    };

    char sd[256];
    strncpy(sd, this->ImageType, 255);
    sd[255] = '\0';
    char *sdp = sd;
    char *lsdp = sd;
    while (*sdp != '\0')
    {
      char c = *sdp++;

      if (((c < 'A' || c > 'Z') && (c < '0' || c > '9') &&
           c != '_' && c != ' ') || (sdp - lsdp > 16))
      {
        vtkErrorMacro("Illegal ImageType: " << this->ImageType);
        return 0;
      }

      if (*sdp == '/' || *sdp == '\\')
      {
        *sdp++ = '\\';
        lsdp = sdp;
      }
    }

    bool isAllowed = false;
    for (const char **allowed = allowedTypes; *allowed != 0; allowed++)
    {
      size_t sl = strlen(*allowed);
      if (strncmp(*allowed, sd, sl) == 0 && (sd[sl] == '\0' || sd[sl] == '\\'))
      {
        isAllowed = true;
        break;
      }
    }
    if (!isAllowed)
    {
      vtkErrorMacro("Illegal ImageType: " << this->ImageType << ", "
                    "the first part must be ORIGINAL or DERIVED, the "
                    "second part must be PRIMARY or SECONDARY");
      return 0;
    }

    meta->Set(DC::ImageType, sd);
  }

  // add an empty PixelData to be filled in by the compiler
  unsigned short empty = 0;
  meta->Set(
    DC::PixelData, vtkDICOMValue(vtkDICOMVR::OW, &empty, empty));

  return 1;
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::GenerateOverlays(
  int minFileIdx, int maxFileIdx, const int wholeExtent[4])
{
  vtkImageData *data = this->GetOverlayInput();
  if (!data)
  {
    return;
  }

  // Get the extent of the input
  int extent[6];
  data->GetExtent(extent);
  int scalarSize = data->GetScalarSize();
  int nComp = data->GetNumberOfScalarComponents();
  vtkIdType pixelInc = nComp*scalarSize;
  vtkIdType rowInc = pixelInc*(extent[1] - extent[0] + 1);

  // Clip the overlay extent with the whole extent of the main input
  // (According to DICOM standard, this doesn't need to be done)
  for (int i = 0; i < 6; i += 2)
  {
    extent[i] = std::max(extent[i], wholeExtent[i]);
    extent[i+1] = std::max(extent[i+1], wholeExtent[i+1]);
    if (extent[i] > extent[i+1])
    {
      return;
    }
  }

  // Get rows, cols in overlay
  int overlayCols = extent[1] - extent[0] + 1;
  int overlayRows = extent[3] - extent[2] + 1;
  int firstCol = extent[0] - wholeExtent[0];
  int firstRow = extent[2] - wholeExtent[2];

  // adjust if a flip is needed
  vtkIdType flipOffset = 0;
  if (this->MemoryRowOrder == vtkDICOMWriter::BottomUp)
  {
    firstRow = wholeExtent[3] - extent[3];
    flipOffset = rowInc*(extent[3] - extent[2]);
    rowInc = -rowInc;
  }

  // Get the map from file,frame to slice.
  vtkIntArray *sliceMap = this->Generator->GetSliceIndexArray();
  vtkIntArray *componentMap = this->Generator->GetComponentIndexArray();
  int numFrames = sliceMap->GetNumberOfComponents();

  for (int fileIdx = minFileIdx; fileIdx <= maxFileIdx; fileIdx++)
  {
    // Count the number of overlay frames
    int overlayFrames = 0;
    for (int frameIdx = 0; frameIdx < numFrames; frameIdx++)
    {
      if (componentMap->GetComponent(fileIdx, frameIdx) < nComp)
      {
        overlayFrames++;
      }
    }

    // Allocate the output buffer
    size_t nbits = overlayFrames;
    nbits *= overlayRows;
    nbits *= overlayCols;
    vtkDICOMValue v;
    unsigned char *buffer =
      v.AllocateUnsignedCharData(vtkDICOMVR::OB, (nbits+7)/8);
    unsigned char *bptr = buffer;

    // for keeping track of bits written
    int bit = 0;
    unsigned char c = 0;

    // iterate through all frames in the file
    for (int frameIdx = 0; frameIdx < numFrames; frameIdx++)
    {
      int sliceIdx = sliceMap->GetComponent(fileIdx, frameIdx);
      int componentIdx = componentMap->GetComponent(fileIdx, frameIdx);
      if (sliceIdx < extent[4] || sliceIdx > extent[5] ||
          componentIdx >= nComp)
      {
        continue;
      }

      // Get the pointer to the data
      int sliceExtent[6] = { extent[0], extent[1],
                             extent[2], extent[3],
                             sliceIdx, sliceIdx };
      unsigned char *ptr = static_cast<unsigned char *>(
        data->GetScalarPointerForExtent(sliceExtent));
#ifdef VTK_WORDS_BIGENDIAN
      ptr += (scalarSize-1);
#endif
      ptr += componentIdx*scalarSize;
      ptr += flipOffset;
      for (int i = extent[2]; i <= extent[3]; i++)
      {
        unsigned char *optr = ptr;
        for (int j = extent[0]; j <= extent[1]; j++)
        {
          c |= (*optr & 1) << bit++;
          if (bit == 8)
          {
            *bptr++ = c;
            bit = 0;
            c = 0;
          }
          optr += pixelInc;
        }
        ptr += rowInc;
      }
    }
    if (bit != 0)
    {
      *bptr++ = c;
    }
    if (((bptr - buffer) & 1) != 0)
    {
      // pad data element to even size
      *bptr++ = 0;
    }

    // write the attributes for the overlay
    vtkDICOMMetaData *meta = this->GeneratedMetaData;
    meta->Set(fileIdx, DC::OverlayRows, overlayRows);
    meta->Set(fileIdx, DC::OverlayColumns, overlayCols);
    meta->Set(fileIdx, DC::OverlayType, (this->OverlayType ? "R" : "G"));
    short overlayOrigin[2] = {
      static_cast<short>(firstRow+1), static_cast<short>(firstCol+1) };
    meta->Set(fileIdx, DC::OverlayOrigin,
      vtkDICOMValue(vtkDICOMVR::SS, overlayOrigin, 2));
    meta->Set(fileIdx, DC::OverlayBitsAllocated, 1);
    meta->Set(fileIdx, DC::OverlayBitPosition, 0);
    meta->Set(fileIdx, DC::OverlayData, v);
    if (meta->Has(DC::NumberOfFrames))
    {
      meta->Set(fileIdx, DC::NumberOfFramesInOverlay, overlayFrames);
    }
    // optional attributes must be suited for the type
    if (!this->OverlayType) // not ROI
    {
      meta->Erase(DC::ROIArea);
      meta->Erase(DC::ROIMean);
      meta->Erase(DC::ROIStandardDeviation);
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::SetOverlayInputData(vtkImageData *overlay)
{
  this->SetInputData(1, overlay);
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::SetOverlayInputConnection(vtkAlgorithmOutput *overlay)
{
  this->SetInputConnection(1, overlay);
}

//----------------------------------------------------------------------------
vtkImageData *vtkDICOMWriter::GetOverlayInput()
{
  if (this->GetNumberOfInputConnections(1) < 1)
  {
    return NULL;
  }
  return vtkImageData::SafeDownCast(
    this->GetExecutive()->GetInputData(1, 0));
}

//----------------------------------------------------------------------------
int vtkDICOMWriter::FillInputPortInformation(int port, vtkInformation *info)
{
  if (port == 1)
  {
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkImageData");
    info->Set(vtkAlgorithm::INPUT_IS_OPTIONAL(), 1);
  }
  else
  {
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkImageData");
  }
  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMWriter::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* vtkNotUsed(outputVector))
{
  this->SetErrorCode(vtkErrorCode::NoError);

  vtkInformation *info = inputVector[0]->GetInformationObject(0);
  vtkImageData *data =
    vtkImageData::SafeDownCast(info->Get(vtkDataObject::DATA_OBJECT()));

  if (data == NULL)
  {
    vtkErrorMacro("No input provided!");
    return 0;
  }

  if (!this->FileName && !this->FilePattern)
  {
    vtkErrorMacro("Write:Please specify either a FileName "
                  "or a file prefix and pattern");
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    return 0;
  }

  if (!this->GeneratedMetaData)
  {
    // Generate the meta data to go with the image
    if (!this->GenerateMetaData(info))
    {
      return 0;
    }
  }

  // Get the map from file,frame to slice.
  vtkIntArray *sliceMap = this->Generator->GetSliceIndexArray();
  vtkIntArray *componentMap = this->Generator->GetComponentIndexArray();
  int numFiles = static_cast<int>(sliceMap->GetNumberOfTuples());
  int numFrames = sliceMap->GetNumberOfComponents();

  // Get the image dimensions
  int extent[6], wholeExtent[6];
  info->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), wholeExtent);
  info->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), extent);

  // Find the range of files that corresponds to the update extent
  int minFileIdx = numFiles-1;
  int maxFileIdx = 0;
  for (int fileIdx = 0; fileIdx < numFiles; fileIdx++)
  {
    for (int frameIdx = 0; frameIdx < numFrames; frameIdx++)
    {
      int sliceIdx = sliceMap->GetComponent(fileIdx, frameIdx);
      if (sliceIdx >= extent[4] && sliceIdx <= extent[5])
      {
        minFileIdx = (minFileIdx < fileIdx ? minFileIdx : fileIdx);
        maxFileIdx = (maxFileIdx > fileIdx ? maxFileIdx : fileIdx);
      }
    }
  }

  // Generate overlays
  this->GenerateOverlays(minFileIdx, maxFileIdx, wholeExtent);

  vtkSmartPointer<vtkDICOMCompiler> compiler =
    vtkSmartPointer<vtkDICOMCompiler>::New();
  if (this->TransferSyntaxUID)
  {
    compiler->SetTransferSyntaxUID(this->TransferSyntaxUID);
  }
  vtkDICOMMetaData *meta = this->GeneratedMetaData;
  compiler->SetMetaData(meta);

  // write the image
  unsigned char *dataPtr = static_cast<unsigned char *>(
    data->GetScalarPointerForExtent(extent));
  bool flipImage = (this->MemoryRowOrder == vtkDICOMWriter::BottomUp);

  int planarConfiguration = meta->Get(DC::PlanarConfiguration).AsInt();
  int samplesPerPixel = meta->Get(DC::SamplesPerPixel).AsInt();
  samplesPerPixel = (samplesPerPixel > 0 ? samplesPerPixel : 1);

  int numFileComponents = (planarConfiguration ? 1 : samplesPerPixel);
  int numPlanes = (planarConfiguration ? samplesPerPixel : 1);
  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();

  vtkIdType pixelSize = numComponents*scalarSize;
  vtkIdType rowSize = pixelSize*(extent[1] - extent[0] + 1);
  vtkIdType sliceSize = rowSize*(extent[3] - extent[2] + 1);
  vtkIdType filePixelSize = numFileComponents*scalarSize;
  vtkIdType fileRowSize = filePixelSize*(extent[1] - extent[0] + 1);
  vtkIdType filePlaneSize = fileRowSize*(extent[3] - extent[2] + 1);
  vtkIdType fileFrameSize = filePlaneSize*numPlanes;

  this->InvokeEvent(vtkCommand::StartEvent);
  this->UpdateProgress(0.0);

  bool packedToPlanar = (filePixelSize != pixelSize);
  unsigned char *rowBuffer = 0;
  if (flipImage)
  {
    rowBuffer = new unsigned char[fileRowSize];
  }
  unsigned char *frameBuffer = 0;
  if (flipImage || packedToPlanar)
  {
    frameBuffer = new unsigned char[fileFrameSize];
  }

  // loop through all files in the update extent
  for (int fileIdx = minFileIdx; fileIdx <= maxFileIdx; fileIdx++)
  {
    // get the index for this file
    this->ComputeInternalFileName(fileIdx + 1);
    compiler->SetFileName(this->InternalFileName);
    compiler->SetIndex(fileIdx);
    compiler->SetSOPInstanceUID(
      meta->Get(fileIdx, DC::SOPInstanceUID).GetCharData());
    compiler->SetSeriesInstanceUID(
      meta->Get(fileIdx, DC::SeriesInstanceUID).GetCharData());
    compiler->WriteHeader();

    // iterate through all frames in the file
    for (int frameIdx = 0; frameIdx < numFrames; frameIdx++)
    {
      if (this->AbortExecute) { break; }

      this->UpdateProgress(static_cast<double>(fileIdx*numFrames + frameIdx)/
                           static_cast<double>(numFiles*numFrames));

      int sliceIdx = sliceMap->GetComponent(fileIdx, frameIdx);
      int componentIdx = componentMap->GetComponent(fileIdx, frameIdx);

      // pointer to the frame that will be written to the file
      unsigned char *framePtr = frameBuffer;

      if (!framePtr)
      {
        // write the frame directly from image data
        framePtr = (dataPtr + (sliceIdx - extent[4])*sliceSize);
      }

      // go to the correct position in image data
      unsigned char *slicePtr =
        (dataPtr + (sliceIdx - extent[4])*sliceSize +
         componentIdx*samplesPerPixel*scalarSize);

      // iterate through all color planes in the slice
      unsigned char *planePtr = framePtr;
      for (int pIdx = 0; pIdx < numPlanes; pIdx++)
      {
        // convert scalar components to planes
        if (packedToPlanar)
        {
          const unsigned char *tmpInPtr = slicePtr;
          unsigned char *tmpOutPtr = planePtr;
          int m = sliceSize/pixelSize;
          for (int i = 0; i < m; i++)
          {
            vtkIdType n = filePixelSize;
            do { *tmpOutPtr++ = *tmpInPtr++; } while (--n);
            tmpInPtr += pixelSize - filePixelSize;
          }
          slicePtr += filePixelSize;
        }
        else
        {
          memcpy(framePtr, slicePtr, fileFrameSize);
        }

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

        planePtr += filePlaneSize;
      }
      // write the frame to the file
      compiler->WriteFrame(framePtr, fileFrameSize);
    }
    compiler->Close();
  }

  delete [] rowBuffer;
  delete [] frameBuffer;
  this->FreeInternalFileName();

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::Write()
{
  // call Modified to force update to execute
  this->Modified();
  this->UpdateInformation();
  vtkInformation* inInfo = this->GetExecutive()->GetInputInformation(0, 0);
  int wholeExtent[6];
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), wholeExtent);

  int numOverlays = this->GetNumberOfInputConnections(1);

  // if streaming is on, write the slices one-at-a-time
  if (this->Streaming && this->FileDimensionality == 2)
  {
    if (this->GenerateMetaData(inInfo))
    {
      int extent[6] = {
        wholeExtent[0], wholeExtent[1],
        wholeExtent[2], wholeExtent[3],
        wholeExtent[4], wholeExtent[5]
      };
      for (int i = wholeExtent[4]; i <= wholeExtent[5]; i++)
      {
        // set the update extent to the slice
        extent[4] = i;
        extent[5] = i;
        this->Modified();
        inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
                    extent, 6);

        for (int j = 0; j < numOverlays; j++)
        {
          vtkInformation *ovInfo =
            this->GetExecutive()->GetInputInformation(1, j);
          int ovExtent[6];
          ovInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
                      ovExtent);
          if (i >= ovExtent[4] && i <= ovExtent[5])
          {
            ovExtent[4] = i;
            ovExtent[5] = i;
          }
          ovInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
                      ovExtent, 6);
        }

        this->Update();
      }
    }
  }
  else
  {
    // set update wholeExtent to whole wholeExtent
    inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
                wholeExtent, 6);

    for (int j = 0; j < numOverlays; j++)
    {
      vtkInformation *ovInfo = this->GetExecutive()->GetInputInformation(1, j);
      int ovExtent[6];
      ovInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
                  ovExtent);
      ovInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
                  ovExtent, 6);
    }

    this->Update();
  }

  // do some cleanup
  if (this->GeneratedMetaData)
  {
    this->GeneratedMetaData->Delete();
    this->GeneratedMetaData = 0;
  }
}
