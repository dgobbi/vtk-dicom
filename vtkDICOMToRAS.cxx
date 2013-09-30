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
#include "vtkTemplateAliasMacro.h"

vtkStandardNewMacro(vtkDICOMToRAS);
vtkCxxSetObjectMacro(vtkDICOMToRAS, PatientMatrix, vtkMatrix4x4);
vtkCxxSetObjectMacro(vtkDICOMToRAS, RASMatrix, vtkMatrix4x4);

//----------------------------------------------------------------------------
vtkDICOMToRAS::vtkDICOMToRAS()
{
  this->PatientMatrix = vtkMatrix4x4::New();
  this->RASMatrix = vtkMatrix4x4::New();
  this->RASToDICOM = 0;
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

  os << indent << "RASToDICOM: " << this->RASToDICOM << "\n";

  os << indent << "RASMatrixHasPosition: "
     << this->RASMatrixHasPosition << "\n";

  os << indent << "AllowColumnReordering: "
     << this->AllowColumnReordering << "\n";

  os << indent << "AllowRowReordering: "
     << this->AllowRowReordering << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::SetRASToDICOM(int val)
{
  val = (val != 0);
  if (val != this->RASToDICOM)
    {
    this->RASToDICOM = val;
    this->Modified();
    }
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
  vtkMatrix4x4 *inputMatrix = (this->RASToDICOM  == 0 ?
    this->PatientMatrix : this->RASMatrix);
  if (inputMatrix)
    {
    inputMatrix->MultiplyPoint(hdir, hdir);
    inputMatrix->MultiplyPoint(vdir, vdir);
    }

  // do the DICOM-to-RAS sign changes
  hdir[0] = -hdir[0];
  hdir[1] = -hdir[1];
  vdir[0] = -vdir[0];
  vdir[1] = -vdir[1];

  if (this->RASToDICOM)
    {
    // for DICOM, hdir should be left (+x) or posterior (+y)
    this->ReorderColumns = (this->AllowColumnReordering &&
                            hdir[0] + hdir[1] < 0);

    // for RAS, vdir should be inferior (-z) or posterior (+y)
    this->ReorderRows = (this->AllowRowReordering &&
                         vdir[1] - vdir[2] < 0);
    }
  else
    {
    // for RAS, hdir should be right (+x) or anterior (+y)
    this->ReorderColumns = (this->AllowColumnReordering &&
                            hdir[0] + hdir[1] < 0);

    // for RAS, vdir should be superior (+z) or anterior (+y)
    this->ReorderRows = (this->AllowRowReordering &&
                         vdir[1] + vdir[2] < 0);
    }
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::ComputeMatrix(
  int extent[6], double spacing[3], double origin[3])
{
  double *matrix = this->Matrix;

  if (this->PatientMatrix && this->RASToDICOM == 0)
    {
    vtkMatrix4x4::DeepCopy(matrix, this->PatientMatrix);
    }
  else if (this->RASMatrix && this->RASToDICOM != 0)
    {
    vtkMatrix4x4::DeepCopy(matrix, this->RASMatrix);
    }
  else
    {
    vtkMatrix4x4::Identity(matrix);
    }

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

    extent[2*i+1] -= extent[2*i];
    extent[2*i] = 0;

    if (flip[i])
      {
      // reverse along columns for flips
      origin[i] = -origin[i];
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

  if (this->RASMatrixHasPosition || this->RASToDICOM)
    {
    // origin moves into position (last column of matrix)
    double offset[4];
    offset[0] = origin[0];
    offset[1] = origin[1];
    offset[2] = origin[2];
    offset[3] = 1.0;

    vtkMatrix4x4::MultiplyPoint(matrix, offset, offset);

    matrix[3] = offset[0];
    matrix[7] = offset[1];
    matrix[11] = offset[2];

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

    matrix[3] = 0.0;
    matrix[7] = 0.0;
    matrix[11] = 0.0;

    double inverse[16];
    vtkMatrix4x4::Invert(matrix, inverse);
    vtkMatrix4x4::MultiplyPoint(inverse, offset, offset);

    origin[0] += offset[0];
    origin[1] += offset[1];
    origin[2] += offset[2];
    }
}

//----------------------------------------------------------------------------
void vtkDICOMToRAS::UpdateMatrix()
{
  // This calls RequestInformation, which calls ComputeMatrix
  this->UpdateInformation();

  vtkMatrix4x4 *outMatrix;
  if (this->RASToDICOM == 0)
    {
    if (this->RASMatrix == 0)
      {
      this->RASMatrix = vtkMatrix4x4::New();
      }
    outMatrix = this->RASMatrix;
    }
  else
    {
    if (this->PatientMatrix == 0)
      {
      this->PatientMatrix = vtkMatrix4x4::New();
      }
    outMatrix = this->PatientMatrix;
    }

  const double *inElements = this->Matrix;
  double *outElements = *outMatrix->Element;

  bool changed = false;
  for (int i = 0; i < 16; i++)
    {
    changed |= (inElements[i] != outElements[i]);
    }

  // this ensures that the timestamp isn't changed unless values changed
  if (changed)
    {
    outMatrix->DeepCopy(this->Matrix);
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

  int wholeExt[6], inExt[6], outExt[6];

  outInfo->Get(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), outExt);
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), wholeExt);

  int flip[3];
  flip[0] = this->ReorderColumns;
  flip[1] = this->ReorderRows;
  flip[2] = flip[0] ^ flip[1];

  for (int i = 0; i < 3; i++)
    {
    int offset = outExt[2*i];
    int size = outExt[2*i + 1] - outExt[2*i] + 1;
    int wholeSize = wholeExt[2*i + 1] - wholeExt[2*i] + 1;
    if (flip[i])
      {
      offset = wholeSize - size - offset;
      }
    inExt[2*i] = wholeExt[2*i] + offset;
    inExt[2*i + 1] = inExt[2*i] + size - 1;
    }

  inInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(), outExt, 6);

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMToRAS::RequestData(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // output the matrix that goes with the image
  vtkMatrix4x4 *outMatrix = 0;
  if (this->RASToDICOM == 0)
    {
    if (this->RASMatrix == 0)
      {
      this->RASMatrix = vtkMatrix4x4::New();
      }
    outMatrix = this->RASMatrix;
    }
  else
    {
    if (this->PatientMatrix == 0)
      {
      this->PatientMatrix = vtkMatrix4x4::New();
      }
    outMatrix = this->PatientMatrix;
    }

  const double *inElements = this->Matrix;
  double *outElements = *outMatrix->Element;

  bool changed = false;
  for (int i = 0; i < 16; i++)
    {
    changed |= (inElements[i] != outElements[i]);
    }

  // this ensures that the timestamp isn't changed unless values changed
  if (changed)
    {
    outMatrix->DeepCopy(this->Matrix);
    }

  return this->Superclass::RequestData(request, inputVector, outputVector);
}

//----------------------------------------------------------------------------
namespace {

template<class T>
void vtkDICOMToRASExecute(
  const T *inPtr, T *outPtr, const int flip[3], int numComponents,
  const int inExt[6], const int outExt[6], const int outExecuteExt[6],
  vtkAlgorithm *progress)
{
  // size of region to execute over
  int sizeX = outExecuteExt[1] - outExecuteExt[0] + 1;
  int sizeY = outExecuteExt[3] - outExecuteExt[2] + 1;
  int sizeZ = outExecuteExt[5] - outExecuteExt[4] + 1;

  // output increments
  vtkIdType outIncX = numComponents;
  vtkIdType outIncY = outIncX*(outExt[1] - outExt[0] + 1);
  vtkIdType outSkipY = outIncX*(outExt[1] - outExt[0] + 1 - sizeX);
  vtkIdType outSkipZ = outIncY*(outExt[3] - outExt[2] + 1 - sizeY);

  // input increments
  vtkIdType inIncX = numComponents;
  vtkIdType inIncY = inIncX*(inExt[1] - inExt[0] + 1);
  vtkIdType inIncZ = inIncY*(inExt[3] - inExt[2] + 1);
  if (flip[0])
    {
    inPtr += inIncX*(sizeX - 1);
    inIncX = -inIncX;
    }
  if (flip[1])
    {
    inPtr += inIncY*(sizeY - 1);
    inIncY = -inIncY;
    }
  if (flip[2])
    {
    inPtr += inIncZ*(sizeZ - 1);
    inIncZ = -inIncZ;
    }

  // progress tracking
  vtkIdType progressGoal = static_cast<vtkIdType>(sizeZ)*sizeY;
  vtkIdType progressStep = (progressGoal + 49)/50;
  vtkIdType progressCount = 0;

  // loop through the data and rearrange it
  const T *inPtrZ = inPtr;
  for (int k = 0; k < sizeZ; k++)
    {
    const T *inPtrY = inPtrZ;
    for (int j = 0; j < sizeY; j++)
      {
      if (progress != NULL && (progressCount % progressStep) == 0)
        {
        progress->UpdateProgress(progressCount*1.0/progressGoal);
        }
      progressCount++;

      const T *inPtrX = inPtrY;
      if (numComponents == 1)
        {
        for (int i = 0; i < sizeX; i++)
          {
          *outPtr++ = *inPtrX;
          inPtrX += inIncX;
          }
        }
      else
        {
        for (int i = 0; i < sizeX; i++)
          {
          int c = numComponents;
          const T *inPtrC = inPtrX;
          do { *outPtr++ = *inPtrC++; } while (--c);
          inPtrX += inIncX;
          }
        }
      inPtrY += inIncY;
      outPtr += outSkipY;
      }
    inPtrZ += inIncZ;
    outPtr += outSkipZ;
    }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMToRAS::ThreadedRequestData(
  vtkInformation *vtkNotUsed(request),
  vtkInformationVector **inputVector,
  vtkInformationVector *vtkNotUsed(outputVector),
  vtkImageData ***inData,
  vtkImageData **outData,
  int outExecuteExt[6], int threadId)
{
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  int inWholeExt[6];
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), inWholeExt);

  vtkImageData *input = inData[0][0];
  vtkImageData *output = outData[0];

  int inExt[6], outExt[6];
  input->GetExtent(inExt);
  output->GetExtent(outExt);

  int flip[3];
  flip[0] = this->ReorderColumns;
  flip[1] = this->ReorderRows;
  flip[2] = flip[0] ^ flip[1];

  int inExecuteExt[6];
  for (int i = 0; i < 3; i++)
    {
    int offset = outExecuteExt[2*i];
    int size = outExecuteExt[2*i + 1] - outExecuteExt[2*i] + 1;
    int wholeSize = inWholeExt[2*i + 1] - inWholeExt[2*i] + 1;
    if (flip[i])
      {
      offset = wholeSize - size - offset;
      }
    inExecuteExt[2*i] = inWholeExt[2*i] + offset;
    inExecuteExt[2*i + 1] = inExecuteExt[2*i] + size - 1;
    }

  int numComponents = input->GetNumberOfScalarComponents();

  void *inPtr = input->GetScalarPointerForExtent(inExecuteExt);
  void *outPtr = output->GetScalarPointerForExtent(outExecuteExt);

  int inScalarType = input->GetScalarType();
  int outScalarType = output->GetScalarType();

  // progress object if main thread
  vtkAlgorithm *progress = ((threadId == 0) ? this : NULL);

  // call the execute method
  if (outScalarType == inScalarType)
    {
    switch (inScalarType)
      {
      vtkTemplateAliasMacro(
        vtkDICOMToRASExecute(
          static_cast<const VTK_TT *>(inPtr), static_cast<VTK_TT *>(outPtr),
          flip, numComponents, inExt, outExt, outExecuteExt, progress));
      default:
        vtkErrorMacro("Execute: Unknown ScalarType");
      }
    }
  else
    {
    vtkErrorMacro("ThreadedRequestData: output scalar type does not match "
                  "input scalar type");
    }

}
