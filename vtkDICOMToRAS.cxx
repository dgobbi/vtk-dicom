/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMToRAS.h"

#include "vtkImageData.h"
#include "vtkMatrix4x4.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"

vtkStandardNewMacro(vtkDICOMToRAS);
vtkCxxSetObjectMacro(vtkDICOMToRAS, PatientMatrix, vtkMatrix4x4);

//----------------------------------------------------------------------------
vtkDICOMToRAS::vtkDICOMToRAS()
{
  this->PatientMatrix = 0;
  this->RASMatrix = vtkMatrix4x4::New();
  this->RASMatrixHasPosition = 1;
  this->AllowColumnReordering = 1;
  this->AllowRowReordering = 1;
  this->ReorderRows = 1;
  this->ReorderColumns = 1;
  for (int i = 0; i < 16; i++)
    {
    this->Matrix[i] = 0.0;
    }
}

//----------------------------------------------------------------------------
vtkDICOMToRAS::~vtkDICOMToRAS()
{
  if (this->RASMatrix)
    {
    this->RASMatrix->Delete();
    }
  if (this->PatientMatrix)
    {
    this->PatientMatrix->Delete();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

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

  os << indent << "RASMatrix:";
  if (this->RASMatrix)
    {
    double mat[16];
    vtkMatrix4x4::DeepCopy(mat, this->RASMatrix);
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

  os << indent << "RASMatrixHasPosition: "
     << this->RASMatrixHasPosition << "\n";

  os << indent << "AllowColumnReordering: "
     << this->AllowColumnReordering << "\n";

  os << indent << "AllowRowReordering: "
     << this->AllowRowReordering << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::SetRASMatrixHasPosition(int val)
{
  val = (val != 0);
  if (val != this->RASMatrixHasPosition)
    {
    this->RASMatrixHasPosition = val;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::SetAllowColumnReordering(int val)
{
  val = (val != 0);
  if (val != this->AllowColumnReordering)
    {
    this->AllowColumnReordering = val;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::SetAllowRowReordering(int val)
{
  val = (val != 0);
  if (val != this->AllowRowReordering)
    {
    this->AllowRowReordering = val;
    this->Modified();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::CheckNeedToReorder()
{
  double hdir[4] = { 1.0, 0.0, 0.0, 0.0 };
  double vdir[4] = { 0.0, 1.0, 0.0, 0.0 };

  // convert row, column vectors into patient coords
  if (this->PatientMatrix)
    {
    this->PatientMatrix->MultiplyPoint(hdir, hdir);
    this->PatientMatrix->MultiplyPoint(vdir, vdir);
    }

  // check whether reordering should be done
  this->ReorderColumns = (this->AllowColumnReordering && hdir[0] > 0);
  this->ReorderRows = (this->AllowRowReordering && vdir[1] > 0);
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::ComputeMatrix(
  int extent[6], double spacing[3], double origin[3])
{
  double *matrix = this->Matrix;

  vtkMatrix4x4::DeepCopy(matrix, this->PatientMatrix);

  // what corner of the input image will become the (0,0,0) corner
  // of the output image?
  int flip[3];
  flip[0] = this->ReorderColumns;
  flip[1] = this->ReorderRows;
  flip[2] = flip[0] ^ flip[1];

  double bounds[6];
  for (int i = 0; i < 3; i++)
    {
    bounds[2*i] = extent[2*i]*spacing[i] + origin[i];
    bounds[2*i + 1] = extent[2*i + 1]*spacing[i] + origin[i];
    origin[i] = bounds[2*i + flip[i]];

    if (flip[i])
      {
      // reverse along columns for flips
      matrix[i] = -matrix[i];
      matrix[4 + i] = -matrix[4 + i];
      matrix[8 + i] = -matrix[8 + i];
      }

    if (i == 0 || i == 1)
      {
      // reverse along rows for LPS to RAS conversion
      matrix[4*i] = -matrix[4*i];
      matrix[4*i + 1] = -matrix[4*i + 1];
      matrix[4*i + 2] = -matrix[4*i + 2];
      matrix[4*i + 3] = -matrix[4*i + 3];
      }
    }

  if (this->RASMatrixHasPosition)
    {
    // origin moves into position (last column of matrix)
    double offset[4];
    offset[0] = origin[0];
    offset[1] = origin[1];
    offset[2] = origin[2];
    offset[3] = 1.0;

    vtkMatrix4x4::MultiplyPoint(matrix, offset, offset);

    matrix[3] += offset[0];
    matrix[7] += offset[1];
    matrix[11] += offset[2];

    origin[0] = 0.0;
    origin[1] = 0.0;
    origin[2] = 0.0;
    }
  else
    {
    // position moves into origin
    double offset[4];
    offset[0] = matrix[3];
    offset[1] = matrix[7];
    offset[2] = matrix[11];
    offset[3] = 1.0;

    double inverse[16];
    vtkMatrix4x4::Invert(matrix, inverse);
    vtkMatrix4x4::MultiplyPoint(inverse, offset, offset);

    origin[0] += offset[0];
    origin[1] += offset[1];
    origin[2] += offset[2];

    matrix[3] = 0.0;
    matrix[7] = 0.0;
    matrix[11] = 0.0;
    }
}

//----------------------------------------------------------------------------
int vtkDICOMToRAS::RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // RequestInformation must compute the new matrix and set the origin
  // if RASMatrixHasPosition was off

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  int extent[6];
  double spacing[3], origin[3];
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  inInfo->Get(vtkDataObject::SPACING(), spacing);
  inInfo->Get(vtkDataObject::ORIGIN(), origin);

  // check reordering for the benefit of all later Requests
  this->CheckNeedToReorder();
  this->ComputeMatrix(extent, spacing, origin);

  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent, 6);
  outInfo->Set(vtkDataObject::SPACING(), spacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(), origin, 3);

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMToRAS::RequestUpdateExtent(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // RequestUpdateExtent must check whether row or column reordering
  // will occur, and adjust the update extent as necessary.

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  int wholeExt[6];
  int extent[6];

  outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), extent);
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), wholeExt);

  int flip[3];
  flip[0] = this->ReorderColumns;
  flip[1] = this->ReorderRows;
  flip[2] = flip[0] ^ flip[1];

  for (int i = 0; i < 3; i++)
    {
    int offset = wholeExt[2*i + 1] - extent[2*i + 1];
    int size = extent[2*i + 1] - extent[2*i] + 1;
    extent[2*i] = offset;
    extent[2*i + 1] = offset + size - 1;
    }

  inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), extent, 6);

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMToRAS::RequestData(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // output the matrix that goes with the image
  this->RASMatrix->DeepCopy(this->Matrix);

  return this->Superclass::RequestData(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::ThreadedRequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **vtkNotUsed(inputVector),
  vtkInformationVector *vtkNotUsed(outputVector),
  vtkImageData ***inData,
  vtkImageData **outData,
  int outExt[6], int threadId)
{
  vtkImageData *input = inData[0][0];
  vtkImageData *output = outData[0];

  // go through output, get appropriate pixel from input
}
