/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMCTRectifier.h"
#include "vtkDICOMMetaData.h"

#include "vtkImageData.h"
#include "vtkMatrix4x4.h"
#include "vtkMath.h"
#include "vtkPointData.h"
#include "vtkInformation.h"
#include "vtkImageReslice.h"
#include "vtkInformationVector.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"
#if (VTK_MAJOR_VERSION > 5) || (VTK_MINOR_VERSION > 9)
#include "vtkImageSincInterpolator.h"
#endif

vtkStandardNewMacro(vtkDICOMCTRectifier);
vtkCxxSetObjectMacro(vtkDICOMCTRectifier, VolumeMatrix, vtkMatrix4x4);

//----------------------------------------------------------------------------
vtkDICOMCTRectifier::vtkDICOMCTRectifier()
{
  this->VolumeMatrix = 0;
  this->RectifiedMatrix = vtkMatrix4x4::New();
  this->Matrix = vtkMatrix4x4::New();
  this->Reverse = 0;
  this->InterpolationMode = WindowedSinc;
}

//----------------------------------------------------------------------------
vtkDICOMCTRectifier::~vtkDICOMCTRectifier()
{
  if (this->RectifiedMatrix)
  {
    this->RectifiedMatrix->Delete();
  }
  if (this->VolumeMatrix)
  {
    this->VolumeMatrix->Delete();
  }
  if (this->Matrix)
  {
    this->Matrix->Delete();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMCTRectifier::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "VolumeMatrix:";
  if (this->VolumeMatrix)
  {
    double mat[16];
    vtkMatrix4x4::DeepCopy(mat, this->VolumeMatrix);
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

  os << indent << "RectifiedMatrix:";
  if (this->RectifiedMatrix)
  {
    double mat[16];
    vtkMatrix4x4::DeepCopy(mat, this->RectifiedMatrix);
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

  os << indent << "Reverse: " << this->Reverse << "\n";
  os << indent << "InterpolationMode: " << this->InterpolationMode << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMCTRectifier::SetReverse(int val)
{
  val = (val != 0);
  if (val != this->Reverse)
  {
    this->Reverse = val;
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMCTRectifier::SetInterpolationMode(int val)
{
  if (val < 0)
  {
    val = 0;
  }
  else if (val > WindowedSinc)
  {
    val = WindowedSinc;
  }
  if (val != this->InterpolationMode)
  {
    this->InterpolationMode = val;
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMCTRectifier::ComputeMatrix(
  const double volumeMatrix[16], const int extent[6],
  double spacing[3], double origin[3])
{
  if (volumeMatrix == 0)
  {
    this->RectifiedMatrix->Identity();
    this->Matrix->Identity();
    return;
  }

  // get the first two columns of the volume matrix
  double xvec[4] = { 1.0, 0.0, 0.0, 0.0 };
  double yvec[4] = { 0.0, 1.0, 0.0, 0.0 };
  vtkMatrix4x4::MultiplyPoint(volumeMatrix, xvec, xvec);
  vtkMatrix4x4::MultiplyPoint(volumeMatrix, yvec, yvec);

  // create the rectified matrix
  double normal[3];
  vtkMath::Cross(xvec, yvec, normal);
  this->RectifiedMatrix->DeepCopy(volumeMatrix);
  this->RectifiedMatrix->SetElement(0, 2, normal[0]);
  this->RectifiedMatrix->SetElement(1, 2, normal[1]);
  this->RectifiedMatrix->SetElement(2, 2, normal[2]);

  // compute the shear matrix
  vtkMatrix4x4 *matrix = this->Matrix;
  if (this->Reverse)
  {
    matrix->DeepCopy(this->RectifiedMatrix);
    matrix->Invert();
    double elements[16];
    vtkMatrix4x4::Multiply4x4(*matrix->Element, volumeMatrix, elements);
    matrix->DeepCopy(elements);
  }
  else
  {
    matrix->DeepCopy(volumeMatrix);
    matrix->Invert();
    vtkMatrix4x4::Multiply4x4(matrix, this->RectifiedMatrix, matrix);
  }

  // compute the shear parameters for the volume
  double zdn = matrix->GetElement(2, 2);
  double xshear = matrix->GetElement(0, 2)/zdn;
  double yshear = matrix->GetElement(1, 2)/zdn;

  // adjust the spacing if necessary
  spacing[2] *= zdn;
  origin[2] *= zdn;

  // adjust the position to center the new volume on the old volume
  double zcenter = 0.5*spacing[2]*(extent[5] - extent[4]);
  double pos[4] = { -xshear*zcenter, -yshear*zcenter, 0.0, 1.0 };
  matrix->SetElement(0, 3, pos[0]);
  matrix->SetElement(1, 3, pos[1]);
  matrix->SetElement(2, 3, pos[2]);

  if (this->Reverse)
  {
    pos[0] = -pos[0];
    pos[1] = -pos[1];
    pos[2] = -pos[2];
  }

  vtkMatrix4x4::MultiplyPoint(volumeMatrix, pos, pos);
  this->RectifiedMatrix->SetElement(0, 3, pos[0]);
  this->RectifiedMatrix->SetElement(1, 3, pos[1]);
  this->RectifiedMatrix->SetElement(2, 3, pos[2]);
}

//----------------------------------------------------------------------------
double vtkDICOMCTRectifier::GetGantryDetectorTilt(vtkMatrix4x4 *matrix)
{
  double xvec[4] = { 1.0, 0.0, 0.0, 0.0 };
  double yvec[4] = { 0.0, 1.0, 0.0, 0.0 };
  double zvec[4] = { 0.0, 0.0, 1.0, 0.0 };
  matrix->MultiplyPoint(xvec, xvec);
  matrix->MultiplyPoint(yvec, yvec);
  matrix->MultiplyPoint(zvec, zvec);
  double normal[3], checkvec[3];
  vtkMath::Cross(xvec, yvec, normal);
  vtkMath::Cross(normal, zvec, checkvec);
  double angle = atan2(vtkMath::Norm(checkvec), vtkMath::Dot(normal, zvec));
  return vtkMath::DegreesFromRadians(angle);
}

//----------------------------------------------------------------------------
void vtkDICOMCTRectifier::UpdateMatrix()
{
  this->UpdateInformation();
}

//----------------------------------------------------------------------------
int vtkDICOMCTRectifier::RequestInformation(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  this->Superclass::RequestInformation(request, inputVector, outputVector);

  vtkInformation *metaInfo = this->GetMetaDataInformation(inputVector, 0, 0);
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  int extent[6];
  double spacing[3], origin[3];
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  inInfo->Get(vtkDataObject::SPACING(), spacing);
  inInfo->Get(vtkDataObject::ORIGIN(), origin);

  double *volumeMatrix;
  if (this->VolumeMatrix)
  {
    // If a VolumeMatrix was provided, then use it.
    volumeMatrix = *this->VolumeMatrix->Element;
  }
  else
  {
    // Otherwise, try to get the patient matrix from the pipeline.
    volumeMatrix = metaInfo->Get(vtkDICOMAlgorithm::PATIENT_MATRIX());
  }

  // Compute the shear matrix and the new spacing and origin.
  this->ComputeMatrix(volumeMatrix, extent, spacing, origin);

  // Write the new patient matrix to the pipeline.
  double *outMatrix = *this->RectifiedMatrix->Element;
  if (this->Reverse)
  {
    outMatrix = volumeMatrix;
  }
  if (outMatrix)
  {
    outInfo->Set(vtkDICOMAlgorithm::PATIENT_MATRIX(), outMatrix, 16);
  }

  // The spacing and origin may have changed.
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent, 6);
  outInfo->Set(vtkDataObject::SPACING(), spacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(), origin, 3);

  // Note that, after execution, the ImagePositionPatient in the META_DATA
  // will no longer be correct, but we assume that it will be ignored because,
  // within VTK, the PatientMatrix, Extent, Spacing, and Origin are used to
  // describe the geometry of the volume.  The writer, for example, always
  // re-generates the ImagePositionPatient from the VTK volume information.

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMCTRectifier::RequestUpdateExtent(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  int wholeExt[6], outExt[6];
  outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), outExt);
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), wholeExt);

  int inExt[6];
  inExt[0] = wholeExt[0];
  inExt[1] = wholeExt[1];
  inExt[2] = wholeExt[2];
  inExt[3] = wholeExt[3];
  inExt[4] = outExt[4];
  inExt[5] = outExt[5];

  inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), inExt, 6);

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMCTRectifier::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkImageData *inData =
    vtkImageData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkImageData *outData =
    static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  this->CopyMetaDataToOutputData(outInfo, outData);

  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  image->CopyStructure(inData);
  image->GetPointData()->PassData(inData->GetPointData());

  int extent[6];
  double spacing[3], origin[3];
  outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), extent);
  outInfo->Get(vtkDataObject::SPACING(), spacing);
  outInfo->Get(vtkDataObject::ORIGIN(), origin);

  vtkSmartPointer<vtkImageReslice> reslice =
    vtkSmartPointer<vtkImageReslice>::New();
  reslice->SetNumberOfThreads(this->GetNumberOfThreads());
  reslice->SetResliceAxes(this->Matrix);
  reslice->SetOutputSpacing(spacing);
  reslice->SetOutputOrigin(origin);
  reslice->SetOutputExtent(extent);
  if (this->InterpolationMode == Nearest)
  {
    reslice->SetInterpolationModeToNearestNeighbor();
  }
  else if (this->InterpolationMode == Linear)
  {
    reslice->SetInterpolationModeToLinear();
  }
  else if (this->InterpolationMode == Cubic)
  {
    reslice->SetInterpolationModeToCubic();
  }
  else
  {
#if (VTK_MAJOR_VERSION > 5) || (VTK_MINOR_VERSION > 9)
    vtkSmartPointer<vtkImageSincInterpolator> interpolator =
      vtkSmartPointer<vtkImageSincInterpolator>::New();
    interpolator->SetWindowFunctionToBlackman();
    reslice->SetInterpolator(interpolator);
#else
    reslice->SetInterpolationModeToCubic();
#endif
  }
#if (VTK_MAJOR_VERSION > 5)
  reslice->SetInputData(image);
  this->AllocateOutputData(outData, outInfo, extent);
  reslice->SetOutput(outData);
  reslice->Update();
#else
  reslice->SetInput(image);
  reslice->Update();
  outData->CopyStructure(reslice->GetOutput());
  outData->GetPointData()->PassData(reslice->GetOutput()->GetPointData());
#endif

  return 1;
}

//----------------------------------------------------------------------------
void vtkDICOMCTRectifier::ThreadedRequestData(
  vtkInformation *,
  vtkInformationVector **,
  vtkInformationVector *,
  vtkImageData ***,
  vtkImageData **,
  int [6], int)
{
  vtkErrorMacro("ThreadedRequestData should never be called for this filter.");
}
