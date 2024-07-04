/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2024 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMApplyRescale.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMItem.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkIntArray.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkDataSetAttributes.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"
#include "vtkTypeTraits.h"
#include "vtkVersion.h"

#include "vtkTemplateAliasMacro.h"
// turn off unused input types
# undef VTK_USE_INT64
# define VTK_USE_INT64 0
# undef VTK_USE_UINT64
# define VTK_USE_UINT64 0
# undef VTK_USE_INT32
# define VTK_USE_INT32 0
# undef VTK_USE_UINT32
# define VTK_USE_UINT32 0
# undef VTK_USE_FLOAT64
# define VTK_USE_FLOAT64 0
# undef VTK_USE_FLOAT32
# define VTK_USE_FLOAT32 0

#include <math.h>

#include <vector>

vtkStandardNewMacro(vtkDICOMApplyRescale);

//----------------------------------------------------------------------------
// A struct to hold the mapping
class vtkDICOMRealWorldMapping
{
public:
  int First;
  int Last;
  double Slope;
  double Intercept;
  const double *Map;
};

//----------------------------------------------------------------------------
vtkDICOMApplyRescale::vtkDICOMApplyRescale()
{
  this->OutputScalarType = VTK_DOUBLE;
  this->Mapping = nullptr;
}

//----------------------------------------------------------------------------
vtkDICOMApplyRescale::~vtkDICOMApplyRescale()
{
  delete [] this->Mapping;
}

//----------------------------------------------------------------------------
void vtkDICOMApplyRescale::SetOutputScalarType(int t)
{
  if (t != this->OutputScalarType && (t == VTK_DOUBLE || t == VTK_FLOAT))
  {
    this->OutputScalarType = t;
    this->Modified();
  }
}

//----------------------------------------------------------------------------
void vtkDICOMApplyRescale::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << this->OutputScalarType << "\n";
}

//----------------------------------------------------------------------------

namespace {

template<class T, class F>
void vtkDICOMApplyRescaleExecute(
  vtkDICOMApplyRescale *self, vtkImageData *inData, T *inPtr0,
  vtkImageData *outData, F *outPtr0, vtkDICOMRealWorldMapping *mapArray,
  int extent[6], int id)
{
  vtkIdType inIncX, inIncY, inIncZ;
  inData->GetIncrements(inIncX, inIncY, inIncZ);
  vtkIdType outIncX, outIncY, outIncZ;
  outData->GetIncrements(outIncX, outIncY, outIncZ);
  int numComponents = inData->GetNumberOfScalarComponents();
  int wholeExtent[6];
  outData->GetExtent(wholeExtent);

  // target for progress tracking
  vtkIdType target = numComponents;
  target *= extent[5] - extent[4] + 1;
  target *= extent[3] - extent[2] + 1;
  vtkIdType progress = 0;

  for (int c = 0; c < numComponents; c++)
  {
    T *inPtrC = inPtr0 + c;
    F *outPtrC = outPtr0 + c;

    for (int zIdx = extent[4]; zIdx <= extent[5]; zIdx++)
    {
      vtkDICOMRealWorldMapping *mapping = nullptr;
      T first = vtkTypeTraits<T>::Min();
      T last = vtkTypeTraits<T>::Max();
      if (mapArray)
      {
        mapping = &mapArray[(zIdx - wholeExtent[4])*numComponents + c];
        if (mapping->First > static_cast<int>(first))
        {
          first = static_cast<T>(mapping->First);
        }
        if (mapping->Last < static_cast<int>(last))
        {
          last = static_cast<T>(mapping->Last);
        }
      }

      T *inPtrZ = inPtrC + (zIdx - extent[4])*inIncZ;
      F *outPtrZ = outPtrC + (zIdx - extent[4])*outIncZ;

      for (int yIdx = extent[2]; yIdx <= extent[3]; yIdx++)
      {
        T *inPtr = inPtrZ + inIncY*(yIdx - extent[2]);
        F *outPtr = outPtrZ + outIncY*(yIdx - extent[2]);

        // in base thread, report progress every 2% of the way to 100%
        if (id == 0)
        {
          ++progress;
          vtkIdType icount = progress*50/target;
          if (progress == icount*target/50)
          {
            self->UpdateProgress(progress*1.0/target);
          }
        }

        if (mapping == nullptr)
        {
          // no mapping to apply
          for (int xIdx = extent[0]; xIdx <= extent[1]; xIdx++)
          {
            *outPtr = *inPtr;
            inPtr += numComponents;
            outPtr += numComponents;
          }
        }
        else if (mapping->Map)
        {
          // apply lookup table
          const double *table = mapping->Map;
          for (int xIdx = extent[0]; xIdx <= extent[1]; xIdx++)
          {
            if (*inPtr >= first && *inPtr <= last)
            {
              *outPtr = table[*inPtr - first];
            }
            else
            {
              *outPtr = 0;
            }
            inPtr += numComponents;
            outPtr += numComponents;
          }
        }
        else
        {
          // apply slope and intercept
          double m = mapping->Slope;
          double b = mapping->Intercept;
          for (int xIdx = extent[0]; xIdx <= extent[1]; xIdx++)
          {
            if (*inPtr >= first && *inPtr <= last)
            {
              *outPtr = *inPtr*m + b;
            }
            else
            {
              *outPtr = 0;
            }
            inPtr += numComponents;
            outPtr += numComponents;
          }
        }
      }
    }
  }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
int vtkDICOMApplyRescale::RequestInformation(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  this->Superclass::RequestInformation(request, inputVector, outputVector);

  // Get the scalar information
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(inInfo,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, vtkDataSetAttributes::SCALARS);
  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents =
    scalarInfo->Get(vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());

  // Modify the information
  scalarType = this->OutputScalarType;

  // Set the output information.
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  vtkDataObject::SetPointDataActiveScalarInfo(
    outInfo, scalarType, numComponents);

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMApplyRescale::RequestData(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // Get the scalar information
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(inInfo,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, vtkDataSetAttributes::SCALARS);
  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents =
    scalarInfo->Get(vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());

  // Get the whole extent from the output port
  int extent[6];
  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  outInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);

  // Get the meta data
  vtkInformation *metaInfo = this->GetMetaDataInformation(inputVector, 0, 0);
  vtkDICOMMetaData *meta = vtkDICOMMetaData::SafeDownCast(
      metaInfo->Get(vtkDICOMAlgorithm::META_DATA()));

  if (meta)
  {
    size_t sz = (static_cast<size_t>(numComponents)*
                 static_cast<size_t>(extent[5] - extent[4] + 1));
    this->Mapping = new vtkDICOMRealWorldMapping[sz];
    bool hasMapping = false;

    for (int c = 0; c < numComponents; c++)
    {
      for (int zIdx = extent[4]; zIdx <= extent[5]; zIdx++)
      {
        vtkDICOMRealWorldMapping *mapping =
          &this->Mapping[(zIdx - extent[4])*numComponents + c];
        mapping->First = VTK_INT_MIN;
        mapping->Last = VTK_INT_MAX;
        mapping->Slope = 1.0;
        mapping->Intercept = 0.0;
        mapping->Map = nullptr;

        int i = meta->GetFileIndex(zIdx, c, numComponents);
        int j = meta->GetFrameIndex(zIdx, c, numComponents);

        const vtkDICOMValue& rwvms =
          meta->Get(i, j, DC::RealWorldValueMappingSequence);
        const vtkDICOMItem *rwvmi = rwvms.GetSequenceData();

        if (rwvmi)
        {
          // use the real world value mapping first item
          mapping->First =
            rwvmi->Get(DC::RealWorldValueFirstValueMapped).AsInt();
          mapping->Last =
            rwvmi->Get(DC::RealWorldValueLastValueMapped).AsInt();
          mapping->Slope =
            rwvmi->Get(DC::RealWorldValueSlope).AsDouble();
          mapping->Intercept =
            rwvmi->Get(DC::RealWorldValueIntercept).AsDouble();

          // use lookup table if present
          const vtkDICOMValue &v = rwvmi->Get(DC::RealWorldValueLUTData);
          if (v.GetNumberOfValues() >=
              static_cast<size_t>(mapping->Last - mapping->First + 1))
          {
            mapping->Map = v.GetDoubleData();
          }
          hasMapping = true;
        }
        else
        {
          // use the slope and intercept instead
          const vtkDICOMValue& u = meta->Get(i, j, DC::RescaleSlope);
          const vtkDICOMValue& v = meta->Get(i, j, DC::RescaleIntercept);
          if (u.IsValid() && v.IsValid())
          {
            mapping->Slope = u.AsDouble();
            mapping->Intercept = v.AsDouble();
            hasMapping = true;
          }
        }

        // zero slope means slope wasn't found
        if (mapping->Slope == 0)
        {
          mapping->Slope = 1.0;
        }
      }
    }

    if (!hasMapping)
    {
      delete [] this->Mapping;
      this->Mapping = nullptr;
    }
  }

  // Passthrough if data is already floating-point
  int rval = 1;
  if (scalarType == VTK_DOUBLE || scalarType == VTK_FLOAT)
  {
    vtkImageData *inData =
      vtkImageData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));
    vtkImageData *outData =
      static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));

    outData->CopyStructure(inData);
    outData->GetPointData()->PassData(inData->GetPointData());
  }
  else
  {
    // Allow the superclass to call the ThreadedRequestData method
    rval = this->Superclass::RequestData(
      request, inputVector, outputVector);
  }

  delete [] this->Mapping;
  this->Mapping = nullptr;

  return rval;
}

//----------------------------------------------------------------------------
void vtkDICOMApplyRescale::ThreadedRequestData(
    vtkInformation *vtkNotUsed(request),
    vtkInformationVector **inputVector,
    vtkInformationVector *outputVector,
    vtkImageData ***,
    vtkImageData **,
    int extent[6], int id)
{
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
  vtkImageData *inData =
    vtkImageData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkInformation *outInfo = outputVector->GetInformationObject(0);
  vtkImageData *outData =
    static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));

  int scalarType = inData->GetScalarType();
  void *inVoidPtr = inData->GetScalarPointerForExtent(extent);
  void *outVoidPtr = outData->GetScalarPointerForExtent(extent);

  int outScalarType = outData->GetScalarType();

  if (outScalarType == VTK_FLOAT)
  {
    switch (scalarType)
    {
      vtkTemplateAliasMacro(
        vtkDICOMApplyRescaleExecute(
          this, inData, static_cast<VTK_TT *>(inVoidPtr), outData,
          static_cast<float *>(outVoidPtr), this->Mapping, extent, id));
    }
  }
  else if (outScalarType == VTK_DOUBLE)
  {
    switch (scalarType)
    {
      vtkTemplateAliasMacro(
        vtkDICOMApplyRescaleExecute(
          this, inData, static_cast<VTK_TT *>(inVoidPtr), outData,
          static_cast<double *>(outVoidPtr), this->Mapping, extent, id));
    }
  }
}
