/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMWriter.h"
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
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkSmartPointer.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

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
  this->Generator = vtkDICOMSCGenerator::New();
  this->TimeAsVector = 0;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->PatientMatrix = 0;
  this->MemoryRowOrder = vtkDICOMWriter::BottomUp;
  this->SeriesDescription = 0;
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
  delete [] this->SeriesDescription;
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
void vtkDICOMWriter::ComputeAspectRatio(
  const double spacing[2], int aspect[2])
{
  // compute aspect ratio to within one part in 1000
  static const double primes[] = { // include 1
    1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
    353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
    467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
    607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
    661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
    739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
    811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
    877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
    947, 953, 967, 971, 977, 983, 991, 997, 1009, 0
  };

  double a = spacing[1]/spacing[0];
  int xaspect = 1;
  int yaspect = 1;

  double minrem = fabs(a - 1.0);
  for (int j = 0; primes[j] != 0; j++)
    {
    int x = primes[j];
    double b = a*x;
    int y = static_cast<int>(b + 0.5);
    double r = fabs(b - y);
    if (r < minrem)
      {
      minrem = r;
      yaspect = y;
      xaspect = x;
      }
    y = x;
    b = y/a;
    x = static_cast<int>(b + 0.5);
    r = fabs(b - x);
    if (r < minrem)
      {
      minrem = r;
      yaspect = y;
      xaspect = x;
      }
    }

  aspect[0] = yaspect;
  aspect[1] = xaspect;
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

  if (!this->Generator)
    {
    vtkErrorMacro("No Generator was supplied, unable to create a DICOM "
                  "data set");
    return 0;
    }

  // Get the image dimensions
  int extent[6];
  info->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  bool flipImage = (this->MemoryRowOrder == vtkDICOMWriter::BottomUp);

  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();

  // Generate the data
  this->Generator->SetMultiFrame(this->FileDimensionality > 2);
  this->Generator->SetOriginAtBottom(flipImage);
  this->Generator->SetTimeAsVector(this->TimeAsVector);
  this->Generator->SetTimeDimension(this->TimeDimension);
  this->Generator->SetTimeSpacing(this->TimeSpacing);
  this->Generator->SetMetaData(this->MetaData);
  this->Generator->SetPatientMatrix(this->PatientMatrix);
  if (!this->Generator->GenerateInstance(info, meta))
    {
    return 0;
    }

  // Get the map from file,frame to slice.
  vtkIntArray *sliceMap = this->Generator->GetSliceIndexArray();
  int numFiles = static_cast<int>(sliceMap->GetNumberOfTuples());
  int numFrames = sliceMap->GetNumberOfComponents();

  // set the series description from the member variable
  if (this->SeriesDescription && this->SeriesDescription[0] != '\0')
    {
    char sd[65];
    strncpy(sd, this->SeriesDescription, 64);
    sd[64] = '\0';
    meta->SetAttributeValue(DC::SeriesDescription, sd);
    meta->RemoveAttribute(DC::SeriesDescriptionCodeSequence);
    }

  // add an empty PixelData to be filled in by the compiler
  unsigned short empty[1] = {};
  meta->SetAttributeValue(
    DC::PixelData, vtkDICOMValue(vtkDICOMVR::OW, empty, empty));

  vtkSmartPointer<vtkDICOMCompiler> compiler =
    vtkSmartPointer<vtkDICOMCompiler>::New();
  compiler->SetMetaData(meta);

  // write the image
  char *dataPtr = static_cast<char *>(data->GetScalarPointer());

  int planarConfiguration =
    meta->GetAttributeValue(DC::PlanarConfiguration).AsInt();
  int samplesPerPixel =
    meta->GetAttributeValue(DC::SamplesPerPixel).AsInt();
  samplesPerPixel = (samplesPerPixel > 0 ? samplesPerPixel : 1);

  int numFileComponents = (planarConfiguration ? 1 : samplesPerPixel);
  int numPlanes = (planarConfiguration ? samplesPerPixel : 1);
  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();
  samplesPerPixel = numComponents;

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
  char *rowBuffer = 0;
  if (flipImage)
    {
    rowBuffer = new char[fileRowSize];
    }
  char *frameBuffer = 0;
  if (flipImage || packedToPlanar)
    {
    frameBuffer = new char[fileFrameSize];
    }

  // loop through all files in the update extent
  for (int fileIdx = 0; fileIdx < numFiles; fileIdx++)
    {
    // get the index for this file
    this->ComputeInternalFileName(fileIdx + 1);
    compiler->SetFileName(this->InternalFileName);
    compiler->SetIndex(fileIdx);
    compiler->SetSOPInstanceUID(
      meta->GetAttributeValue(fileIdx, DC::SOPInstanceUID).GetCharData());
    compiler->SetSeriesInstanceUID(
      meta->GetAttributeValue(fileIdx, DC::SeriesInstanceUID).GetCharData());
    compiler->WriteHeader();

    // iterate through all frames in the file
    for (int frameIdx = 0; frameIdx < numFrames; frameIdx++)
      {
      if (this->AbortExecute) { break; }

      this->UpdateProgress(static_cast<double>(fileIdx*numFrames + frameIdx)/
                           static_cast<double>(numFiles*numFrames));

      int sliceIdx = sliceMap->GetComponent(fileIdx, frameIdx);
      int componentIdx = (numFiles*numFrames) % (extent[5] - extent[4] + 1);

      // pointer to the frame that will be written to the file
      char *framePtr = frameBuffer;

      if (!framePtr)
        {
        // write the frame directly from image data
        framePtr = (dataPtr + (sliceIdx - extent[4])*sliceSize);
        }

      // go to the correct position in image data
      char *slicePtr = (dataPtr +
                        (sliceIdx - extent[4])*sliceSize +
                        componentIdx*samplesPerPixel);

      // iterate through all color planes in the slice
      char *planePtr = framePtr;
      for (int pIdx = 0; pIdx < numPlanes; pIdx++)
        {
        // convert scalar components to planes
        if (packedToPlanar)
          {
          const char *tmpInPtr = slicePtr;
          char *tmpOutPtr = planePtr;
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
            char *row1 = planePtr + yIdx*fileRowSize;
            char *row2 = planePtr + (numRows-yIdx-1)*fileRowSize;
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

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}
