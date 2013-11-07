/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMGenerator.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"
#include "vtkDICOMUtilities.h"

#include "vtkObjectFactory.h"
#include "vtkStringArray.h"
#include "vtkIntArray.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkInformation.h"
#include "vtkMatrix4x4.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkDataSetAttributes.h"
#include "vtkSmartPointer.h"

#include <math.h>
#include <stdlib.h>

vtkCxxSetObjectMacro(vtkDICOMGenerator,PatientMatrix,vtkMatrix4x4);
vtkCxxSetObjectMacro(vtkDICOMGenerator,MetaData,vtkDICOMMetaData);

//----------------------------------------------------------------------------
vtkDICOMGenerator::vtkDICOMGenerator()
{
  this->MetaData = 0;
  this->MultiFrame = 0;
  this->OriginAtBottom = 1;
  this->ScalarType = 0;
  this->AllowedPixelRepresentation = 3;
  this->AllowedBitsStored = 0xffffffffu;
  this->NumberOfColorComponents = 1;
  this->NumberOfFrames = 0;
  this->TimeAsVector = 0;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->RescaleIntercept = 0.0;
  this->RescaleSlope = 1.0;
  this->PatientMatrix = 0;
  this->SliceIndexArray = vtkIntArray::New();
  this->ComponentIndexArray = vtkIntArray::New();
  this->SourceInstanceArray = 0;
  this->RangeArray = 0;
  this->PixelValueRange[0] = 0;
  this->PixelValueRange[1] = 0;

  for (int i = 0; i < 5; i++)
    {
    this->Dimensions[i] = 0;
    this->Spacing[i] = 0;
    this->Origin[i] = 0;
    }
}

//----------------------------------------------------------------------------
vtkDICOMGenerator::~vtkDICOMGenerator()
{
  if (this->RangeArray)
    {
    this->RangeArray->Delete();
    }
  if (this->SourceInstanceArray)
    {
    this->SourceInstanceArray->Delete();
    }
  if (this->SliceIndexArray)
    {
    this->SliceIndexArray->Delete();
    }
  if (this->ComponentIndexArray)
    {
    this->ComponentIndexArray->Delete();
    }
  if (this->PatientMatrix)
    {
    this->PatientMatrix->Delete();
    }
  if (this->MetaData)
    {
    this->MetaData->Delete();
    }
}

//----------------------------------------------------------------------------
vtkDICOMMetaData *vtkDICOMGenerator::GetMetaData()
{
  return this->MetaData;
}

//----------------------------------------------------------------------------
void vtkDICOMGenerator::PrintSelf(ostream& os, vtkIndent indent)
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
  os << indent << "SliceIndexArray: ";
  if (this->SliceIndexArray)
    {
    os << this->SliceIndexArray << "\n";
    }
  else
    {
    os << "(none)\n";
    }
  os << indent << "ComponentIndexArray: ";
  if (this->ComponentIndexArray)
    {
    os << this->ComponentIndexArray << "\n";
    }
  else
    {
    os << "(none)\n";
    }
  os << indent << "MultiFrame: "
     << (this->MultiFrame ? "On\n" : "Off\n");
  os << indent << "OriginAtBottom: "
     << (this->OriginAtBottom ? "On\n" : "Off\n");
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
}

//----------------------------------------------------------------------------
void vtkDICOMGenerator::ComputeAspectRatio(
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
void vtkDICOMGenerator::ComputeAdjustedMatrix(
  double matrix[16], double origin[3], double spacing[3])
{
  if (this->PatientMatrix)
    {
    vtkMatrix4x4::DeepCopy(matrix, this->PatientMatrix);
    }
  else
    {
    vtkMatrix4x4::Identity(matrix);
    }

  spacing[0] = this->Spacing[0];
  spacing[1] = this->Spacing[1];
  spacing[2] = this->Spacing[2];

  origin[0] = this->Origin[0];
  origin[1] = this->Origin[1];
  origin[2] = this->Origin[2];

  if (this->OriginAtBottom)
    {
    // move origin to the correct corner
    origin[1] -= spacing[1]*(this->Dimensions[1] - 1);
    matrix[1] = -matrix[1];
    matrix[5] = -matrix[5];
    matrix[9] = -matrix[9];
    // also need to do z to keep a right-hand coord transformation
    spacing[2] = -spacing[2];
    matrix[2] = -matrix[2];
    matrix[6] = -matrix[6];
    matrix[10] = -matrix[10];
    }
}

//----------------------------------------------------------------------------
void vtkDICOMGenerator::ComputePositionAndOrientation(
  const double origin[3], const double mmat[16],
  double position[3], double orientation[6])
{
  // find new offset by multiplying the origin by the matrix
  double offset[4];
  offset[0] = origin[0];
  offset[1] = origin[1];
  offset[2] = origin[2];
  offset[3] = 1.0;

  vtkMatrix4x4::MultiplyPoint(mmat, offset, offset);

  position[0] = offset[0];
  position[1] = offset[1];
  position[2] = offset[2];

  orientation[0] = mmat[0];
  orientation[1] = mmat[4];
  orientation[2] = mmat[8];
  orientation[3] = mmat[1];
  orientation[4] = mmat[5];
  orientation[5] = mmat[9];
}

//----------------------------------------------------------------------------
void vtkDICOMGenerator::ComputeDimensions(
  vtkInformation *info, int *nframes, int dims[5],
  double spacing[5], double origin[5])
{
  // get the scalar information
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(
    info, vtkDataObject::FIELD_ASSOCIATION_POINTS,
    vtkDataSetAttributes::SCALARS);

  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents = scalarInfo->Get(
    vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());

  // get the dimensions
  int extent[6];
  info->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  int numSlices = extent[5] - extent[4] + 1;

  // time is either in the slices or in the components
  int numTimeSlots = this->TimeDimension;
  if (numTimeSlots)
    {
    if (this->TimeAsVector)
      {
      if (numComponents % numTimeSlots == 0)
        {
        numComponents /= numTimeSlots;
        }
      else
        {
        numTimeSlots = 0;
        }
      }
    else
      {
      if (numSlices % numTimeSlots == 0)
        {
        numSlices /= numTimeSlots;
        }
      else
        {
        numTimeSlots = 0;
        }
      }
    }

  // if unsigned char, assume scalars are colors, not vector components
  if (scalarType == VTK_UNSIGNED_CHAR)
    {
    numComponents /= this->NumberOfColorComponents;
    if (numComponents < 2)
      {
      numComponents = 0;
      }
    }

  dims[0] = extent[1] - extent[0] + 1;
  dims[1] = extent[3] - extent[2] + 1;
  dims[2] = numSlices;
  dims[3] = numTimeSlots;
  dims[4] = numComponents;

  info->Get(vtkDataObject::SPACING(), spacing);
  info->Get(vtkDataObject::ORIGIN(), origin);

  // compute an adjusted origin
  origin[0] += extent[0]*spacing[0];
  origin[1] += extent[2]*spacing[1];
  origin[2] += extent[4]*spacing[2];
  origin[3] = 0;
  origin[4] = 0;

  // get the dimension spacing
  if (!this->TimeAsVector && numTimeSlots > 1 && numSlices > 1)
    {
    // adjust spacing for multiple temporal positions per spatial position
    spacing[2] *= (numTimeSlots*numSlices - 1);
    spacing[2] /= (numSlices - 1);
    }
  spacing[3] = this->TimeSpacing;
  spacing[4] = 0.0;

  int n = (numSlices ? numSlices : 1);
  n *= (numTimeSlots ? numTimeSlots : 1);
  n *= (numComponents ? numComponents : 1);
  *nframes = n;
}

//----------------------------------------------------------------------------
void vtkDICOMGenerator::MatchInstances(vtkDICOMMetaData *meta)
{
  if (this->SourceInstanceArray)
    {
    this->SourceInstanceArray->Delete();
    this->SourceInstanceArray = 0;
    }

  // make sure there is source data to compare with
  if (!this->MetaData)
    {
    return;
    }

  double spacing[3], origin[3];
  double matrix[16];
  this->ComputeAdjustedMatrix(matrix, origin, spacing);

  // compare the orientation with the input slices
  bool mismatch = false;
  int m = this->MetaData->GetNumberOfInstances();
  for (int j = 0; j < m && !mismatch; j++)
    {
    const vtkDICOMValue &o =
      this->MetaData->GetAttributeValue(j, DC::ImageOrientationPatient);
    if (o.GetNumberOfValues() != 6)
      {
      mismatch = true;
      break;
      }

    double orientation[6];
    o.GetValues(orientation, orientation+6);
    for (int i = 0; i < 3; i++)
      {
      if (fabs(matrix[4*i] - orientation[i]) > 1e-4 ||
          fabs(matrix[4*i + 1] - orientation[i + 3]) > 1e-4)
        {
        mismatch = true;
        break;
        }
      }
    }

  if (mismatch)
    {
    return;
    }

  this->SourceInstanceArray = vtkIntArray::New();
  this->SourceInstanceArray->SetNumberOfComponents(1);
  this->SourceInstanceArray->SetNumberOfTuples(meta->GetNumberOfInstances());

  int timeSlices = 1;
  if (!this->TimeAsVector && this->Dimensions[3] > 0)
    {
    timeSlices = this->Dimensions[3];
    }

  // for keeping track of which source instances have been matched
  bool *usedInstances = new bool[m];
  for (int j = 0; j < m; j++)
    {
    usedInstances[j] = false;
    }

  int n = meta->GetNumberOfInstances();
  double zorigin = origin[2];
  for (int i = 0; i < n && !mismatch; i++)
    {
    int sliceIdx = this->SliceIndexArray->GetComponent(i, 0);
    // remove the time from the slice index
    sliceIdx /= timeSlices;
    origin[2] = zorigin + sliceIdx*spacing[2];

    double position[3], orientation[6];
    vtkDICOMGenerator::ComputePositionAndOrientation(
      origin, matrix, position, orientation);

    // find the matching input instance, note that this only looks
    // for matching slice position and is not guaranteed to order
    // the 4th and 5th dimensions correctly
    bool foundOne = false;
    for (int j = 0; j < m; j++)
      {
      if (usedInstances[j])
        {
        continue;
        }

      const vtkDICOMValue &p =
        this->MetaData->GetAttributeValue(j, DC::ImagePositionPatient);
      if (p.GetNumberOfValues() == 3)
        {
        double r[3];
        p.GetValues(r, r+3);
        double dd = 0;
        for (int k = 0; k < 3; k++)
          {
          double d = r[k] - position[k];
          dd += d*d;
          }
        if (dd/(spacing[2]*spacing[2]) < 1e-8)
          {
          this->SourceInstanceArray->SetComponent(i, 0, j);
          usedInstances[j] = true;
          foundOne = true;
          break;
          }
        }
      }

    mismatch = !foundOne;
    }

  delete [] usedInstances;

  if (mismatch)
    {
    this->SourceInstanceArray->Delete();
    this->SourceInstanceArray = 0;
    }
}

//----------------------------------------------------------------------------
namespace {

template<class T>
void vtkDICOMGeneratorComputeHistogram(
  const T *ptr, vtkIdType n, int nComponents, int totalComponents,
  vtkIdType *histogram)
{
  if (n > 0)
    {
    if (nComponents == totalComponents)
      {
      do { histogram[*ptr++]++; } while (--n > 0);
      }
    else if (nComponents == 1)
      {
      do
        {
        histogram[*ptr]++;
        ptr += totalComponents;
        n -= totalComponents;
        }
      while (n > 0);
      }
    else
      {
      do
        {
        int m = nComponents;
        do { histogram[*ptr++]++; } while (--m > 0);
        ptr += (totalComponents - nComponents);
        n -= totalComponents;
        }
      while (n > 0);
      }
    }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMGenerator::ComputePixelValueRange(
  vtkInformation *info, int seriesRange[2])
{
  // get the data and compute the range, this is tricky because the
  // vtkDataArray::GetRange() method computes the min/max for just
  // one component, but we need min/max over all components
  double range[2];
  vtkImageData *data =
    vtkImageData::SafeDownCast(info->Get(vtkDataObject::DATA_OBJECT()));
  vtkDataArray *a = data->GetPointData()->GetScalars();
  vtkIdType nt = a->GetNumberOfTuples();
  vtkIdType nc = a->GetNumberOfComponents();
  vtkDataArray *newArray = a->NewInstance();
  newArray->SetNumberOfTuples(nt*nc);
  newArray->SetVoidArray(a->GetVoidPointer(0), nt*nc, true);
  newArray->GetRange(range);
  newArray->Delete();

  seriesRange[0] = static_cast<int>(range[0]);
  seriesRange[1] = static_cast<int>(range[1]);

  if (this->RangeArray)
    {
    this->RangeArray->Delete();
    this->RangeArray = 0;
    }

  if (this->ScalarType == VTK_UNSIGNED_SHORT ||
      this->ScalarType == VTK_SHORT || this->ScalarType == VTK_SIGNED_CHAR ||
      this->ScalarType == VTK_UNSIGNED_CHAR)
    {
    vtkIdType *h = new vtkIdType[seriesRange[1] - seriesRange[0] + 1];
    vtkIdType *histogram = h - seriesRange[0];

    int npixels = nt*nc;
    int npositions = (this->Dimensions[2] > 0 ? this->Dimensions[2] : 1);
    int ntimes = (this->Dimensions[3] > 0 ? this->Dimensions[3] : 1);
    int nvector = (this->Dimensions[4] > 0 ? this->Dimensions[4] : 1);
    int sliceSize = npixels/(npositions*ntimes);
    if (this->TimeAsVector)
      {
      sliceSize = npixels/npositions;
      }

    int nframes = this->SliceIndexArray->GetNumberOfComponents();
    int ninstances = this->SliceIndexArray->GetNumberOfTuples();
    int ntotal = nframes*ninstances;

    this->RangeArray = vtkIntArray::New();
    this->RangeArray->SetNumberOfComponents(4);
    this->RangeArray->SetNumberOfTuples(ntotal);

    for (int i = 0; i < ninstances; i++)
      {
      for (int j = 0; j < nframes; j++)
        {
        int k = i*nframes + j;
        int idx = 0;
        int s = this->SliceIndexArray->GetComponent(i, j);
        int v = this->ComponentIndexArray->GetComponent(i, j);
        int n = nc/nvector; // ntimes*samplesPerPixel
        idx += s*sliceSize;
        if (this->TimeAsVector)
          {
          n /= ntimes; // samplesPerPixel
          int t = v/nvector;
          v = v % nvector;
          idx += t*nvector*n;
          }
        idx += v*n;

        void *ptr = a->GetVoidPointer(idx);
        for (int hi = seriesRange[0]; hi <= seriesRange[1]; hi++)
          {
          histogram[hi] = 0;
          }

        switch (this->ScalarType)
          {
          case VTK_UNSIGNED_SHORT:
            vtkDICOMGeneratorComputeHistogram(
              static_cast<unsigned short *>(ptr), sliceSize, n, nc, histogram);
            break;
          case VTK_SHORT:
            vtkDICOMGeneratorComputeHistogram(
              static_cast<short *>(ptr), sliceSize, n, nc, histogram);
            break;
          case VTK_UNSIGNED_CHAR:
            vtkDICOMGeneratorComputeHistogram(
              static_cast<unsigned char *>(ptr), sliceSize, n, nc, histogram);
            break;
          case VTK_SIGNED_CHAR:
            vtkDICOMGeneratorComputeHistogram(
              static_cast<signed char *>(ptr), sliceSize, n, nc, histogram);
            break;
          }

        // compute the min/max from the histogram,
        // also try to compute window/level as 99th percentile
        vtkIdType sum = 0;
        vtkIdType totalSum = (sliceSize/nc)*n;
        vtkIdType lowSum = static_cast<int>(totalSum*0.01);
        vtkIdType highSum = static_cast<int>(totalSum*0.99);
        int lowVal = seriesRange[0];
        int highVal = seriesRange[0];
        int minVal = seriesRange[0] - 1;
        int maxVal = seriesRange[0];
        for (int hi = seriesRange[0]; hi <= seriesRange[1]; hi++)
          {
          vtkIdType b = histogram[hi];
          sum += b;
          lowVal = (sum > lowSum ? lowVal : hi);
          highVal = (sum > highSum ? highVal : hi);
          minVal = (sum > 0 ? minVal : hi);
          maxVal = (b == 0 ? maxVal : hi);
          }
        if (minVal < maxVal)
          {
          minVal++;
          }
        // expand the window slightly, but keep within total range
        int lowExpansion = static_cast<int>((highVal - lowVal)*0.1);
        int highExpansion = static_cast<int>((highVal - lowVal)*0.1);
        lowVal -= lowExpansion;
        highVal += highExpansion;
        lowVal = (lowVal >= seriesRange[0] ? lowVal : seriesRange[0]);
        highVal = (highVal <= seriesRange[1] ? highVal : seriesRange[1]);

        int tp[4];
        tp[0] = minVal;
        tp[1] = maxVal;
        tp[2] = lowVal;
        tp[3] = highVal;
        this->RangeArray->SetTupleValue(k, tp);
        }
      }

    delete [] h;
    }
}

//----------------------------------------------------------------------------
void vtkDICOMGenerator::InitializeMetaData(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  meta->Initialize();

  // get the scalar type
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(
    info, vtkDataObject::FIELD_ASSOCIATION_POINTS,
    vtkDataSetAttributes::SCALARS);
  this->ScalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());

  // get dimensions of the data set: x,y,z,t,v
  int nframes = 1;
  this->ComputeDimensions(
    info, &nframes, this->Dimensions, this->Spacing, this->Origin);
  int numSlices = (this->Dimensions[2] > 0 ? this->Dimensions[2] : 1);
  int numTimeSlots = (this->Dimensions[3] > 0 ? this->Dimensions[3] : 1);

  // compute the SliceIndexArray, either use one multi-frame file to save
  // the data or use a series of non-multi-frame files
  if (this->MultiFrame)
    {
    this->NumberOfFrames = nframes;
    this->SliceIndexArray->SetNumberOfComponents(nframes);
    this->SliceIndexArray->SetNumberOfTuples(1);
    this->ComponentIndexArray->SetNumberOfComponents(nframes);
    this->ComponentIndexArray->SetNumberOfTuples(1);
    meta->SetNumberOfInstances(1);
    }
  else
    {
    this->NumberOfFrames = 0;
    this->SliceIndexArray->SetNumberOfComponents(1);
    this->SliceIndexArray->SetNumberOfTuples(nframes);
    this->ComponentIndexArray->SetNumberOfComponents(1);
    this->ComponentIndexArray->SetNumberOfTuples(nframes);
    meta->SetNumberOfInstances(nframes);
    }

  // Reversing slice ordering isn't necessary if the ImagePlane module
  // is present, because then every file has an ImagePositionPatient,
  // but if only a Location is present then slice ordering is critical.
  bool reverseSlices = (this->OriginAtBottom != 0);
  // If switchDimensions is true, then the vector dimension (or time
  // dimension) comes before the slice dimension in the files.
  bool switchDimensions = false;
  for (int k = 0; k < 4; k++)
    {
    int m = nframes/numSlices;
    int n = m/numTimeSlots;
    for (int i = 0; i < nframes; i++)
      {
      int componentIdx = (switchDimensions ? i / numSlices : i % m);
      int sliceIdx = (switchDimensions ? i % numSlices : i / m);
      sliceIdx = (reverseSlices ? (numSlices - sliceIdx - 1) : sliceIdx);
      if (!this->TimeAsVector)
        {
        int timeIdx = componentIdx / n;
        componentIdx = componentIdx % n;
        sliceIdx = sliceIdx*numTimeSlots + timeIdx;
        }
      this->SliceIndexArray->SetValue(i, sliceIdx);
      this->ComponentIndexArray->SetValue(i, componentIdx);
      }

    // Try to match each generated slice to an input slice
    this->MatchInstances(meta);

    if (this->SourceInstanceArray)
      {
      // If MatchInstances generated a reversed array, try again with
      // the slices in the opposite order.
      if (this->SourceInstanceArray->GetComponent(0, 0) >
          this->SourceInstanceArray->GetComponent(nframes-1, 0))
        {
        reverseSlices = !reverseSlices;
        continue;
        }

      // If MatchInstances generated a shuffled array, try again with
      // a different dimension ordering.
      for (int j = 1; j < nframes; j++)
        {
        if (this->SourceInstanceArray->GetComponent(j-1, 0) >
            this->SourceInstanceArray->GetComponent(j, 0))
          {
          switchDimensions = !switchDimensions;
          continue;
          }
        }
      }

    break;
    }

  this->ComputePixelValueRange(info, this->PixelValueRange);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::CopyRequiredAttributes(
  const DC::EnumType *tags, vtkDICOMMetaData *meta)
{
  if (this->MetaData)
    {
    while (*tags != DC::ItemDelimitationItem)
      {
      vtkDICOMTag tag = *tags++;
      vtkDICOMDataElementIterator iter = this->MetaData->Find(tag);
      if (iter != this->MetaData->End())
        {
        if (!iter->IsPerInstance())
          {
          meta->SetAttributeValue(tag, iter->GetValue());
          }
        else if (this->SourceInstanceArray)
          {
          int n = meta->GetNumberOfInstances();
          for (int i = 0; i < n; i++)
            {
            int j = this->SourceInstanceArray->GetComponent(i, 0);
            meta->SetAttributeValue(i, tag, iter->GetValue(j));
            }
          }
        }
      else
        {
        // set the attribute to zero-length value.
        vtkDICOMVR vr = meta->FindDictVR(0, tag);
        if (vr != vtkDICOMVR::UN)
          {
          meta->SetAttributeValue(tag, vtkDICOMValue(vr));
          }
        }
      }
    }
  else
    {
    while (*tags != DC::ItemDelimitationItem)
      {
      vtkDICOMTag tag = *tags++;
      vtkDICOMVR vr = meta->FindDictVR(0, tag);
      if (vr != vtkDICOMVR::UN)
        {
        meta->SetAttributeValue(tag, vtkDICOMValue(vr));
        }
      }
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::CopyOptionalAttributes(
  const DC::EnumType *tags, vtkDICOMMetaData *meta)
{
  if (this->MetaData)
    {
    while (*tags != DC::ItemDelimitationItem)
      {
      vtkDICOMTag tag = *tags++;
      vtkDICOMDataElementIterator iter = this->MetaData->Find(tag);
      if (iter != this->MetaData->End())
        {
        if (!iter->IsPerInstance())
          {
          meta->SetAttributeValue(tag, iter->GetValue());
          }
        else if (this->SourceInstanceArray)
          {
          int n = meta->GetNumberOfInstances();
          for (int i = 0; i < n; i++)
            {
            int j = this->SourceInstanceArray->GetComponent(i, 0);
            meta->SetAttributeValue(i, tag, iter->GetValue(j));
            }
          }
        }
      }
    }

  return true;
}

//----------------------------------------------------------------------------
void vtkDICOMGenerator::SetPixelRestrictions(
  unsigned int pixelRepresentation, unsigned int bitsStored,
  int colorComponents)
{
  this->AllowedPixelRepresentation = pixelRepresentation;
  this->AllowedBitsStored = bitsStored;
  this->NumberOfColorComponents = colorComponents;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateSOPCommonModule(
  vtkDICOMMetaData *meta, const char *SOPClass)
{
  // set the SOP class UID and instance UIDs
  meta->SetAttributeValue(DC::SOPClassUID, SOPClass);
  int n = meta->GetNumberOfInstances();
  vtkSmartPointer<vtkStringArray> uids =
    vtkSmartPointer<vtkStringArray>::New();
  uids->SetNumberOfValues(n);
  vtkDICOMUtilities::GenerateUIDs(DC::SOPInstanceUID, uids);
  for (int i = 0; i < n; i++)
    {
    meta->SetAttributeValue(i, DC::SOPInstanceUID, uids->GetValue(i));
    }

  // set the InstanceCreationDate and Time
  const char *tz = 0;
  if (this->MetaData)
    {
    tz = this->MetaData->GetAttributeValue(
      DC::TimezoneOffsetFromUTC).GetCharData();
    }
  std::string dt = vtkDICOMUtilities::GenerateDateTime(tz);
  meta->SetAttributeValue(DC::InstanceCreationDate, dt.substr(0, 8));
  meta->SetAttributeValue(DC::InstanceCreationTime, dt.substr(8, 13));

  // These optional attributes should be left alone for now
  // DC::InstanceCreatorUID
  // DC::SOPInstanceStatus,        // caution
  // DC::SOPAuthorizationDateTime, // caution
  // DC::SOPAuthorizationComment,  // caution
  // DC::AuthorizationEquipmentCertificationNumber,  // caution

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::SpecificCharacterSet,  // 1C
    DC::RelatedGeneralSOPClassUID, // set to original class if SC
    DC::OriginalSpecializedSOPClassUID, // set to original class if SC
    DC::CodingSchemeIdentificationSequence,
    DC::TimezoneOffsetFromUTC,
    DC::ContributingEquipmentSequence,
    DC::InstanceNumber,  // will be overwritten by General Image Module
    DC::EncryptedAttributesSequence, // 1C, per-instance?
    DC::OriginalAttributesSequence,
    DC::HL7StructuredDocumentReferenceSequence, // 1C
    DC::LongitudinalTemporalInformationModified,
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GeneratePatientModule(vtkDICOMMetaData *meta)
{
  // required items: use simple read/write validation
  static const DC::EnumType required[] = {
    DC::PatientName,
    DC::PatientID,
    DC::PatientBirthDate,
    DC::PatientSex,
    DC::ItemDelimitationItem
  };

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::ReferencedPatientSequence,
    DC::PatientBirthTime,
    DC::OtherPatientIDs,
    DC::OtherPatientIDsSequence,
    DC::OtherPatientNames,
    DC::EthnicGroup,
    DC::PatientComments,
    DC::PatientSpeciesDescription,   // 1C (veterinary)
    DC::PatientSpeciesCodeSequence,  // 1C (veterinary)
    DC::PatientBreedDescription,     // 2C (veterinary)
    DC::PatientBreedCodeSequence,    // 2C (veterinary)
    DC::BreedRegistrationSequence,   // 2C (veterinary)
    DC::ResponsiblePerson,           // 2C (veterinary)
    DC::ResponsiblePersonRole,       // 1C (veterinary)
    DC::ResponsibleOrganization,     // 2C (veterinary)
    DC::PatientIdentityRemoved,
    DC::DeidentificationMethod,
    DC::DeidentificationMethodCodeSequence,
    DC::ItemDelimitationItem
  };

  return (this->CopyRequiredAttributes(required, meta) &&
          this->CopyOptionalAttributes(optional, meta));
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateClinicalTrialSubjectModule(
  vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType tags[] = {
    DC::ClinicalTrialSponsorName, // 1
    DC::ClinicalTrialProtocolID,  // 1
    DC::ClinicalTrialProtocolName,// 2
    DC::ClinicalTrialSiteID,      // 2
    DC::ClinicalTrialSubjectID,   // 1C
    DC::ClinicalTrialSubjectReadingID, // 1C
    DC::ClinicalTrialProtocolEthicsCommitteeName, // 1C
    DC::ClinicalTrialProtocolEthicsCommitteeApprovalNumber, // 3
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateGeneralStudyModule(vtkDICOMMetaData *meta)
{
  // The StudyInstanceUID is mandatory.
  std::string studyUID;
  if (this->MetaData)
    {
    studyUID = this->MetaData->GetAttributeValue(
      DC::StudyInstanceUID).AsString();
    }
  if (studyUID == "")
    {
    studyUID = vtkDICOMUtilities::GenerateUID(DC::StudyInstanceUID);
    }
  meta->SetAttributeValue(DC::StudyInstanceUID, studyUID);

  // required items: use simple read/write validation
  static const DC::EnumType required[] = {
    DC::StudyDate,
    DC::StudyTime,
    DC::ReferringPhysicianName,
    DC::StudyID,
    DC::AccessionNumber,
    DC::ItemDelimitationItem
  };

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::ReferringPhysicianIdentificationSequence,
    DC::IssuerOfAccessionNumberSequence,
    DC::StudyDescription,
    DC::PhysiciansOfRecord,
    DC::PhysiciansOfRecordIdentificationSequence,
    DC::NameOfPhysiciansReadingStudy,
    DC::PhysiciansReadingStudyIdentificationSequence,
    DC::RequestingServiceCodeSequence,
    DC::ReferencedStudySequence,
    DC::ProcedureCodeSequence,
    DC::ReasonForPerformedProcedureCodeSequence,
    DC::ItemDelimitationItem
  };

  return (this->CopyRequiredAttributes(required, meta) &&
          this->CopyOptionalAttributes(optional, meta));
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GeneratePatientStudyModule(
  vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType tags[] = {
    DC::AdmittingDiagnosesDescription, // 3
    DC::AdmittingDiagnosesCodeSequence, // 3
    DC::PatientAge, // 3
    DC::PatientSize, // 3
    DC::PatientWeight, // 3
    DC::PatientSizeCodeSequence, // 3
    DC::Occupation, // 3
    DC::AdditionalPatientHistory, // 3
    DC::AdmissionID, // 3
    DC::IssuerOfAdmissionIDSequence, // 3
    DC::ServiceEpisodeID, // 3
    DC::IssuerOfServiceEpisodeID, // 3
    DC::ServiceEpisodeDescription, // 3
    DC::PatientSexNeutered, // 2C
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateClinicalTrialStudyModule(
  vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType tags[] = {
    DC::ClinicalTrialTimePointID, // 2
    DC::ClinicalTrialTimePointDescription, // 3
    DC::ConsentForClinicalTrialUseSequence, // 3
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateGeneralSeriesModule(vtkDICOMMetaData *meta)
{
  // The SeriesUID is mandatory and must be unique.
  meta->SetAttributeValue(
    DC::SeriesInstanceUID,
    vtkDICOMUtilities::GenerateUID(DC::SeriesInstanceUID));

  // The modality is mandatory, it cannot be left blank,
  // and it must agree with the SOP Class IOD.
  std::string m;
  if (this->MetaData)
    {
    m = this->MetaData->GetAttributeValue(DC::Modality).AsString();
    }
  if (m == "")
    {
    m = "OT"; // Other, i.e. unknown
    }
  meta->SetAttributeValue(DC::Modality, m);

  // Set pixel min/max information
  if (this->ScalarType != VTK_INT && this->ScalarType != VTK_UNSIGNED_INT)
    {
    // Get the pixel VR
    vtkDICOMVR pixelVR = vtkDICOMVR::US;
    if (this->ScalarType == VTK_SIGNED_CHAR ||
        this->ScalarType == VTK_SHORT)
      {
      pixelVR = vtkDICOMVR::SS;
      }

    // Force it to conform the VRs allowed by the SOP Class
    if ((this->AllowedPixelRepresentation & RepresentationSigned) == 0)
      {
      pixelVR = vtkDICOMVR::US;
      }
    else if ((this->AllowedPixelRepresentation & RepresentationUnsigned) == 0)
      {
      pixelVR = vtkDICOMVR::SS;
      }

    // These are optional, but very nice to have
    meta->SetAttributeValue(
      DC::SmallestPixelValueInSeries,
      vtkDICOMValue(pixelVR, this->PixelValueRange[0]));
    meta->SetAttributeValue(
      DC::LargestPixelValueInSeries,
      vtkDICOMValue(pixelVR, this->PixelValueRange[1]));
    }

  // required items: use simple read/write validation
  DC::EnumType required[] = {
    DC::SeriesNumber,
    DC::ItemDelimitationItem
  };

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::Laterality, // 2C
    DC::SeriesDate,
    DC::SeriesTime,
    DC::PerformingPhysicianName,
    DC::PerformingPhysicianIdentificationSequence,
    DC::ProtocolName,
    DC::SeriesDescription,
    DC::SeriesDescriptionCodeSequence,
    DC::OperatorsName,
    DC::OperatorIdentificationSequence,
    DC::ReferencedPerformedProcedureStepSequence,
    DC::RelatedSeriesSequence,
    DC::BodyPartExamined,
    DC::PatientPosition, // 2C
    // DC::SmallestPixelValueInSeries, // done above
    // DC::LargestPixelValueInSeries,  // done above
    DC::RequestAttributesSequence,
    DC::PerformedProcedureStepID,
    DC::PerformedProcedureStepStartDate,
    DC::PerformedProcedureStepStartTime,
    DC::PerformedProcedureStepDescription,
    DC::PerformedProtocolCodeSequence,
    DC::CommentsOnThePerformedProcedureStep,
    DC::AnatomicalOrientationType,
    DC::ItemDelimitationItem
  };

  return (this->CopyRequiredAttributes(required, meta) &&
          this->CopyOptionalAttributes(optional, meta));
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateClinicalTrialSeriesModule(
  vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType tags[] = {
    DC::ClinicalTrialCoordinatingCenterName, // 2
    DC::ClinicalTrialSeriesID, // 3
    DC::ClinicalTrialSeriesDescription, // 3
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateFrameOfReferenceModule(vtkDICOMMetaData *meta)
{
  // the FrameOfReferenceUID is mandatory,
  // the PositionReferenceIndicator is required

  std::string uid;
  std::string fid;

  // Note that, depending on how the image has been manipulated,
  // the frame of reference might have changed.
  if (this->MetaData)
    {
    uid = this->MetaData->GetAttributeValue(
      DC::FrameOfReferenceUID).AsString();
    fid = this->MetaData->GetAttributeValue(
      DC::PositionReferenceIndicator).AsString();
    }
  if (uid == "")
    {
    uid = vtkDICOMUtilities::GenerateUID(DC::FrameOfReferenceUID);
    }

  meta->SetAttributeValue(DC::FrameOfReferenceUID, uid);
  meta->SetAttributeValue(DC::PositionReferenceIndicator, fid);

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateGeneralEquipmentModule(vtkDICOMMetaData *meta)
{
  // required items: use simple read/write validation
  static const DC::EnumType required[] = {
    DC::Manufacturer,
    DC::ItemDelimitationItem
  };

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::InstitutionName,
    DC::InstitutionAddress,
    DC::StationName,
    DC::InstitutionalDepartmentName,
    DC::ManufacturerModelName,
    DC::DeviceSerialNumber,
    DC::SoftwareVersions,
    DC::GantryID,
    DC::SpatialResolution,
    DC::DateOfLastCalibration,
    DC::TimeOfLastCalibration,
    DC::PixelPaddingValue, // 1C, mandatory if PixelPaddingRangeLimit
    DC::ItemDelimitationItem
  };

  return (this->CopyRequiredAttributes(required, meta) &&
          this->CopyOptionalAttributes(optional, meta));
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateGeneralImageModule(
  vtkDICOMMetaData *meta)
{
  // This module provides per-instance information
  int n = meta->GetNumberOfInstances();
  for (int i = 0; i < n; i++)
    {
    unsigned int instance = i + 1;
    meta->SetAttributeValue(i, DC::InstanceNumber, instance);
    }

  // PatientInformation is required if no ImagePlane module is present,
  // it will be overwritten if a real value is found
  meta->SetAttributeValue(DC::PatientOrientation, "");

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::PatientOrientation, // 2C, not set if Patient Matrix exists
    DC::ContentDate, // 2C, might be per-instance
    DC::ContentTime, // 2C, might be per-instance, up to the microsecond
    DC::ImageType, // must change for derived or reformatted images
    DC::AcquisitionNumber,
    DC::AcquisitionDate,
    DC::AcquisitionTime,
    DC::AcquisitionDateTime,
    DC::ReferencedImageSequence,
    DC::DerivationDescription,  // must change for re-derived images
    DC::DerivationCodeSequence, // must change for re-derived images
    DC::SourceImageSequence,    // must change for derived images
    DC::ReferencedInstanceSequence, // only for non-image instances
    DC::ImagesInAcquisition,    // erase if reformatted?
    DC::ImageComments,
    DC::QualityControlImage,
    DC::BurnedInAnnotation,
    DC::RecognizableVisualFeatures,
    DC::LossyImageCompression,
    DC::LossyImageCompressionRatio,
    DC::LossyImageCompressionMethod,
    // DC::IconImageSequence, // obviously must change if present
    DC::PresentationLUTShape,
    DC::IrradiationEventUID,
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateImagePlaneModule(vtkDICOMMetaData *meta)
{
  double spacing[3], origin[3];
  double matrix[16];
  this->ComputeAdjustedMatrix(matrix, origin, spacing);

  int timeSlices = 1;
  if (!this->TimeAsVector && this->Dimensions[3] > 0)
    {
    timeSlices = this->Dimensions[3];
    }

  // remove attributes that conflict with this module
  meta->RemoveAttribute(DC::PixelAspectRatio);
  meta->RemoveAttribute(DC::PatientOrientation);

  meta->SetAttributeValue(
    DC::PixelSpacing,
    vtkDICOMValue(vtkDICOMVR::DS, spacing, spacing+2));

  // this will have to account for image flip, if present
  int n = meta->GetNumberOfInstances();
  double zorigin = origin[2];
  for (int i = 0; i < n; i++)
    {
    int sliceIdx = this->SliceIndexArray->GetComponent(i, 0);
    // remove the time from the slice index
    sliceIdx /= timeSlices;
    origin[2] = zorigin + sliceIdx*spacing[2];

    double position[3], orientation[6];
    vtkDICOMGenerator::ComputePositionAndOrientation(
      origin, matrix, position, orientation);

    meta->SetAttributeValue(
      i, DC::ImagePositionPatient,
      vtkDICOMValue(vtkDICOMVR::DS, position, position+3));

    meta->SetAttributeValue(
      i, DC::ImageOrientationPatient,
      vtkDICOMValue(vtkDICOMVR::DS, orientation, orientation+6));

    // location is optional, but useful
    double location = (position[0]*matrix[2] +
                       position[1]*matrix[6] +
                       position[2]*matrix[10]);

    // use the original value if possible, to avoid surprises
    if (this->SourceInstanceArray && this->MetaData &&
        this->MetaData->HasAttribute(DC::SliceLocation))
      {
      int j = this->SourceInstanceArray->GetComponent(i, 0);
      location = this->MetaData->GetAttributeValue(
        j, DC::SliceLocation).AsDouble();
      }

    meta->SetAttributeValue(i, DC::SliceLocation, location);
    }

  // the original SliceThickness should be used if it is still valid,
  // i.e. if the slices are original slices rather than reformatted.
  double thickness = 0;
  if (this->SourceInstanceArray && this->MetaData)
    {
    thickness = this->MetaData->GetAttributeValue(
      DC::SliceThickness).AsDouble();
    }
  if (thickness <= 0)
    {
    thickness = fabs(spacing[2]);
    }
  meta->SetAttributeValue(DC::SliceThickness, thickness);

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateImagePixelModule(vtkDICOMMetaData *meta)
{
  int rows = this->Dimensions[1];
  int cols = this->Dimensions[0];

  // get the DICOM data type:
  short pixelbits = 0;
  short pixelrep = 0;

  switch (this->ScalarType)
    {
    case VTK_SIGNED_CHAR:
      pixelrep = 1;
      pixelbits = 8;
      break;
    case VTK_CHAR:
    case VTK_UNSIGNED_CHAR:
      pixelbits = 8;
      break;
    case VTK_SHORT:
      pixelrep = 1;
      pixelbits = 16;
      break;
    case VTK_UNSIGNED_SHORT:
      pixelbits = 16;
      break;
    case VTK_INT:
      pixelrep = 1;
      pixelbits = 32;
      break;
    case VTK_UNSIGNED_INT:
      pixelbits = 32;
      break;
    default:
      break;
    }

  if (pixelbits == 0)
    {
    vtkErrorMacro("Illegal scalar type: " <<
      vtkImageScalarTypeNameMacro(this->ScalarType));
    return false;
    }

  // modify the type based on what SOP allows
  int storedbits = pixelbits;
  if ((this->AllowedPixelRepresentation & (1 << pixelrep)) == 0)
    {
    // if data is signed but no negative values are present,
    // then write as unsigned if SOP Class doesn't allow signed
    if (pixelrep == 1 && this->PixelValueRange[0] >= 0)
      {
      pixelrep = 0;
      }
    else
      {
      vtkErrorMacro("This SOP class requires unsigned values.");
      return false;
      }
    }
  if ((this->AllowedBitsStored & (1 << (pixelbits-1))) == 0)
    {
    vtkErrorMacro("Illegal scalar type: " <<
      vtkImageScalarTypeNameMacro(this->ScalarType));
    }
  // reduce BitsStored if the SOP class allows
  unsigned int minv = static_cast<unsigned int>(-this->PixelValueRange[0]);
  unsigned int maxv = static_cast<unsigned int>(this->PixelValueRange[1]);
  for (int bi = pixelbits/2 + 1; bi < pixelbits; bi++)
    {
    if ((this->AllowedBitsStored & (1u << bi)) != 0 &&
        ((pixelrep == 0 && maxv < (1u << (bi + 1))) ||
         (pixelrep == 1 && maxv < (1u << bi) && minv <= (1u << bi))))
      {
      storedbits = bi + 1;
      break;
      }
    }

  if (rows > 65535 || cols > 65535)
    {
    vtkErrorMacro("Image dimensions " << rows << "x"
      << cols << " are too large for DICOM");
    return false;
    }

  bool paletteColor = false;
  if (this->NumberOfColorComponents >= 3)
    {
    meta->SetAttributeValue(DC::SamplesPerPixel, 3);
    meta->SetAttributeValue(DC::PlanarConfiguration, 0);
    meta->SetAttributeValue(DC::PhotometricInterpretation, "RGB");
    }
  else
    {
    meta->SetAttributeValue(DC::SamplesPerPixel, 1);

    std::string pm;
    if (this->MetaData)
      {
      pm = this->MetaData->GetAttributeValue(
        DC::PhotometricInterpretation).AsString();
      }
    if (pm == "PALETTE COLOR" && this->MetaData &&
        this->MetaData->HasAttribute(DC::RedPaletteColorLookupTableData))
      {
      paletteColor = true;
      }
    else if (pm != "MONOCHROME1")
      {
      pm = "MONOCHROME2";
      }
    meta->SetAttributeValue(DC::PhotometricInterpretation, pm);
    }

  if (paletteColor && this->MetaData)
    {
    static const DC::EnumType palette[] = {
      DC::RedPaletteColorLookupTableDescriptor,
      DC::GreenPaletteColorLookupTableDescriptor,
      DC::BluePaletteColorLookupTableDescriptor,
      DC::RedPaletteColorLookupTableData,
      DC::GreenPaletteColorLookupTableData,
      DC::BluePaletteColorLookupTableData,
      DC::ItemDelimitationItem
    };
    for (int i = 0; palette[i] != DC::ItemDelimitationItem; i++)
      {
      meta->SetAttributeValue(palette[i],
        this->MetaData->GetAttributeValue(palette[i]));
      }
    }

  meta->SetAttributeValue(DC::Rows, rows);
  meta->SetAttributeValue(DC::Columns, cols);
  meta->SetAttributeValue(DC::BitsAllocated, pixelbits);
  meta->SetAttributeValue(DC::BitsStored, storedbits);
  meta->SetAttributeValue(DC::HighBit, storedbits-1);
  meta->SetAttributeValue(DC::PixelRepresentation, pixelrep);

  // This cannot be set if PixelSpacing is set
  if (!meta->HasAttribute(DC::PixelSpacing))
    {
    int aspect[2];
    vtkDICOMGenerator::ComputeAspectRatio(this->Spacing, aspect);
    meta->SetAttributeValue(
      DC::PixelAspectRatio,
      vtkDICOMValue(vtkDICOMVR::IS, aspect, aspect+2));
    }

  // The Smallest/LargestPixelValue are optional, but nice to have
  if (this->RangeArray)
    {
    // Get the pixel VR
    vtkDICOMVR pixelVR = vtkDICOMVR::US;
    if (this->ScalarType == VTK_SIGNED_CHAR ||
        this->ScalarType == VTK_SHORT)
      {
      pixelVR = vtkDICOMVR::SS;
      }

    // Force it to conform the VRs allowed by the SOP Class
    if ((this->AllowedPixelRepresentation & RepresentationSigned) == 0)
      {
      pixelVR = vtkDICOMVR::US;
      }
    else if ((this->AllowedPixelRepresentation & RepresentationUnsigned) == 0)
      {
      pixelVR = vtkDICOMVR::SS;
      }

    int n = meta->GetNumberOfInstances();
    for (int i = 0; i < n; i++)
      {
      int nframes = (this->NumberOfFrames > 0 ? this->NumberOfFrames : 1);
      int minVal = VTK_INT_MAX;
      int maxVal = VTK_INT_MIN;
      for (int j = 0; j < nframes; j++)
        {
        int v = this->RangeArray->GetComponent(i*nframes + j, 0);
        minVal = (minVal <= v ? minVal : v);
        v = this->RangeArray->GetComponent(i*nframes + j, 1);
        maxVal = (maxVal >= v ? maxVal : v);
        }

      meta->SetAttributeValue(
        i, DC::SmallestImagePixelValue, vtkDICOMValue(pixelVR, minVal));
      meta->SetAttributeValue(
        i, DC::LargestImagePixelValue, vtkDICOMValue(pixelVR, maxVal));
      }
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateContrastBolusModule(vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType tags[] = {
    DC::ContrastBolusAgent, // 2
    DC::ContrastBolusAgentSequence, // 3
    DC::ContrastBolusRoute, // 3
    DC::ContrastBolusAdministrationRouteSequence, // 3
    DC::ContrastBolusVolume, // 3
    DC::ContrastBolusStartTime, // 3
    DC::ContrastBolusStopTime, // 3
    DC::ContrastBolusTotalDose, // 3
    DC::ContrastFlowRate, // 3
    DC::ContrastFlowDuration, // 3
    DC::ContrastBolusIngredient, // 3
    DC::ContrastBolusIngredientConcentration, // 3
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateMultiFrameModule(vtkDICOMMetaData *meta)
{
  meta->SetAttributeValue(
    DC::NumberOfFrames, this->NumberOfFrames);
  meta->SetAttributeValue(
    DC::FrameIncrementPointer,
    vtkDICOMValue(vtkDICOMVR::AT, vtkDICOMTag(DC::FrameTime)));
  meta->SetAttributeValue(DC::FrameTime, this->Spacing[4]);

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateDeviceModule(vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType tags[] = {
    DC::DeviceSequence, // 1
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateSpecimenModule(vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType tags[] = {
    DC::ContainerIdentifier, // 1
    DC::IssuerOfTheContainerIdentifierSequence, // 2
    DC::AlternateContainerIdentifierSequence, // 3
    DC::ContainerTypeCodeSequence, // 2
    DC::ContainerDescription, // 3
    DC::ContainerComponentSequence, // 3
    DC::SpecimenDescriptionSequence, // 1
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateOverlayPlaneModule(vtkDICOMMetaData *meta)
{
  // direct copy of values with no checks
  static const DC::EnumType basetags[] = {
    DC::OverlayRows, // 1
    DC::OverlayColumns, // 1
    DC::OverlayType, // 1
    DC::OverlayOrigin, // 1
    DC::OverlayBitsAllocated, // 1
    DC::OverlayBitPosition, // 1
    DC::OverlayData, // 1
    DC::OverlayDescription, // 3
    DC::OverlaySubtype, // 3
    DC::OverlayLabel, // 3
    DC::ROIArea, // 3
    DC::ROIMean, // 3
    DC::ROIStandardDeviation, // 3
    DC::ItemDelimitationItem
  };

  // overlay is a repeating group, it repeats 16 times
  DC::EnumType tags[16];
  for (int i = 0; i < 16; i++)
    {
    if (this->MetaData &&
        this->MetaData->HasAttribute(vtkDICOMTag(0x6000 + i*2, 0x0010)))
      {
      for (int j = 0; j < 12; j++)
        {
        tags[j] = static_cast<DC::EnumType>(basetags[j] + i*0x20000);
        }
      tags[13] = DC::ItemDelimitationItem;

      if (!this->CopyOptionalAttributes(tags, meta))
        {
        return false;
        }
      }
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateVOILUTModule(vtkDICOMMetaData *meta)
{
  // no support for lookup tables yet, so just Window/Level

  if (!meta->HasAttribute(DC::RescaleIntercept) &&
      this->RangeArray &&
      (this->ScalarType == VTK_SHORT ||
       this->ScalarType == VTK_UNSIGNED_SHORT))
    {
    int n = meta->GetNumberOfInstances();
    int m = static_cast<int>(this->RangeArray->GetNumberOfTuples()/n);
    for (int i = 0; i < n; i++)
      {
      int lowVal = this->RangeArray->GetComponent(i*m, 2);
      int highVal = this->RangeArray->GetComponent(i*m, 3);
      // set a limit on how tight the window can be
      if (highVal - lowVal < 20)
        {
        highVal = lowVal + 20;
        }
      // make sure that WindowCenter will be an integer
      if ((highVal - lowVal) % 2 != 0)
        {
        if (lowVal > 0)
          {
          lowVal--;
          }
        else
          {
          highVal--;
          }
        }
      meta->SetAttributeValue(i, DC::WindowCenter, 0.5*(highVal + lowVal));
      meta->SetAttributeValue(i, DC::WindowWidth, 1.0*(highVal - lowVal));
      }

    return true;
    }

  // if data is real-valued like CT, then use original window/level
  static const DC::EnumType tags[] = {
    DC::VOILUTSequence, // 1C, mutually exclusive with WindowCenter
    DC::WindowCenter, // 1C, mutually exclusive with VOILUTSequence
    DC::WindowWidth,  // 1C, mutually exclusive with VOILUTSequence
    DC::WindowCenterWidthExplanation,
    DC::VOILUTFunction,
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(tags, meta);
}
