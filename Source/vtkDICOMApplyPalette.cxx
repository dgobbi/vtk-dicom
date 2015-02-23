/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMApplyPalette.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMReader.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkDataSetAttributes.h"
#include "vtkImageData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkIntArray.h"
#include "vtkPointData.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkAlgorithmOutput.h"
#include "vtkTrivialProducer.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"

#include <math.h>

vtkStandardNewMacro(vtkDICOMApplyPalette);

//----------------------------------------------------------------------------
vtkDICOMApplyPalette::vtkDICOMApplyPalette()
{
  this->Bypass = true;
}

//----------------------------------------------------------------------------
vtkDICOMApplyPalette::~vtkDICOMApplyPalette()
{
}

//----------------------------------------------------------------------------
void vtkDICOMApplyPalette::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
int vtkDICOMApplyPalette::RequestInformation(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);

  int extent[6];
  inInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);

  double spacing[3], origin[3];
  inInfo->Get(vtkDataObject::SPACING(), spacing);
  inInfo->Get(vtkDataObject::ORIGIN(), origin);

  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(inInfo,
    vtkDataObject::FIELD_ASSOCIATION_POINTS, vtkDataSetAttributes::SCALARS);
  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents =
    scalarInfo->Get(vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());

  vtkDICOMMetaData *meta = 0;
  if (inInfo->Has(vtkDICOMMetaData::META_DATA()))
    {
    // Get the meta data from upstream
    meta = vtkDICOMMetaData::SafeDownCast(
      inInfo->Get(vtkDICOMMetaData::META_DATA()));
    }
  else
    {
    // If SetInputData was used, the meta data is attached to the data
    vtkAlgorithmOutput *inputConnection = this->GetInputConnection(0, 0);
    if (inputConnection)
      {
      vtkAlgorithm *producer = inputConnection->GetProducer();
      if (producer && vtkTrivialProducer::SafeDownCast(producer))
        {
        vtkDataObject *inputData = producer->GetOutputDataObject(0);
        if (inputData)
          {
          vtkInformation *dataInfo = inputData->GetInformation();
          if (dataInfo->Has(vtkDICOMMetaData::META_DATA()))
            {
            meta = vtkDICOMMetaData::SafeDownCast(
              dataInfo->Get(vtkDICOMMetaData::META_DATA()));
            }
          }
        }
      }
    }

  // Bypass unless photometric is PALETTE_COLOR
  this->Bypass = true;

  // Modify the information
  if (meta)
    {
    if (meta->GetAttributeValue(DC::PhotometricInterpretation)
          .Matches("PALETTE?COLOR"))
      {
      this->Bypass = false;
      scalarType = VTK_UNSIGNED_CHAR;
      numComponents *= 3;
      }
    }

  // Set the output information.
  vtkInformation* outInfo = outputVector->GetInformationObject(0);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               extent, 6);

  outInfo->Set(vtkDataObject::SPACING(), spacing, 3);
  outInfo->Set(vtkDataObject::ORIGIN(), origin, 3);

  if (meta)
    {
    vtkSmartPointer<vtkDICOMMetaData> outMeta =
      vtkSmartPointer<vtkDICOMMetaData>::New();
    outMeta->ShallowCopy(meta);
    outInfo->Set(vtkDICOMMetaData::META_DATA(), outMeta);
    }

  vtkDataObject::SetPointDataActiveScalarInfo(
    outInfo, scalarType, numComponents);

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMApplyPalette::RequestData(
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

  vtkDICOMMetaData *meta = vtkDICOMMetaData::SafeDownCast(
    outInfo->Get(vtkDICOMMetaData::META_DATA()));

  // copy the meta data to the output
  if (meta)
    {
    vtkInformation *dataInfo = outData->GetInformation();
    dataInfo->Set(vtkDICOMMetaData::META_DATA(), meta);
    }

  if (this->Bypass)
    {
    outData->CopyStructure(inData);
    outData->GetPointData()->PassData(inData->GetPointData());
    }
  else
    {
    vtkSmartPointer<vtkImageData> image =
      vtkSmartPointer<vtkImageData>::New();
    image->CopyStructure(inData);
    image->GetPointData()->PassData(inData->GetPointData());

    vtkSmartPointer<vtkLookupTable> table =
        vtkSmartPointer<vtkLookupTable>::New();

    this->FillLookupTable(meta, 0, table);

    vtkSmartPointer<vtkImageMapToColors> colors =
      vtkSmartPointer<vtkImageMapToColors>::New();
    colors->SetOutputFormatToRGB();
    colors->SetLookupTable(table);
    colors->SetNumberOfThreads(this->GetNumberOfThreads());

#if (VTK_MAJOR_VERSION > 5)
    colors->SetInputData(image);
    this->AllocateOutputData(outData, outInfo, image->GetExtent());
    colors->SetOutput(outData);
    colors->Update();
#else
    colors->SetInput(image);
    colors->Update();
    outData->CopyStructure(colors->GetOutput());
    outData->GetPointData()->PassData(colors->GetOutput()->GetPointData());
#endif
    }

  return 1;
}

//----------------------------------------------------------------------------
void vtkDICOMApplyPalette::ThreadedRequestData(
    vtkInformation *vtkNotUsed(request),
    vtkInformationVector **vtkNotUsed(inputVector),
    vtkInformationVector *vtkNotUsed(outputVector),
    vtkImageData ***vtkNotUsed(inData),
    vtkImageData **vtkNotUsed(outData),
    int vtkNotUsed(extent)[6], int vtkNotUsed(id))
{
  // this will never be called
}

//----------------------------------------------------------------------------
void vtkDICOMApplyPalette::FillLookupTable(
  vtkDICOMMetaData *meta, int fileIndex, vtkLookupTable *table)
{
  const DC::EnumType descTag[] = {
    DC::RedPaletteColorLookupTableDescriptor,
    DC::GreenPaletteColorLookupTableDescriptor,
    DC::BluePaletteColorLookupTableDescriptor,
    DC::AlphaPaletteColorLookupTableDescriptor
  };
  const DC::EnumType dataTag[] = {
    DC::RedPaletteColorLookupTableData,
    DC::GreenPaletteColorLookupTableData,
    DC::BluePaletteColorLookupTableData,
    DC::AlphaPaletteColorLookupTableData
  };

  int isSigned = meta->GetAttributeValue(
    fileIndex, DC::PixelRepresentation).AsInt();
  int minValue = VTK_INT_MAX;
  int maxValue = VTK_INT_MIN;
  int firstValue[4] = { 0, 0, 0, 0 };
  int lastValue[4] = { 0, 0, 0, 0 };
  double divisor[4] = { 255.0, 255.0, 255.0, 255.0 };
  const unsigned short *spp[4] = { 0, 0, 0, 0 };
  const unsigned char *cpp[4] = { 0, 0, 0, 0 };
  for (int j = 0; j < 4; j++)
    {
    const vtkDICOMValue& v = meta->GetAttributeValue(
      fileIndex, descTag[j]);
    // Descriptor must have three values
    if (v.GetNumberOfValues() == 3)
      {
      // First value is number of entries in the table
      int n = v.GetUnsignedShort(0);
      n = (n == 0 ? 65536 : n);

      // Second value is the first pixel value that is mapped
      unsigned short f = v.GetUnsignedShort(1);
      firstValue[j] = (isSigned ? static_cast<short>(f) : f);

      // Compute the last pixel value that is mapped
      lastValue[j] = firstValue[j] + n - 1;
      minValue = (firstValue[j] < minValue ? firstValue[j] : minValue);
      maxValue = (lastValue[j] > maxValue ? lastValue[j] : maxValue);

      // Third value is the number of bits per lookup table entry
      int nbits = v.GetUnsignedShort(2);
      divisor[j] = (nbits == 0 ? 1.0 : (1u << nbits) - 1.0);

      // Get the lookup table data and confirm its size
      const vtkDICOMValue& d = meta->GetAttributeValue(
        fileIndex, dataTag[j]);
      if (d.GetVL() >= static_cast<unsigned int>(2*n))
        {
        spp[j] = d.GetUnsignedShortData();
        }
      else if (d.GetVL() >= static_cast<unsigned int>(n))
        {
        cpp[j] = d.GetUnsignedCharData();
        if (cpp[j] == 0)
          {
          cpp[j] = reinterpret_cast<const unsigned char *>(
            d.GetUnsignedShortData());
          }
        }
      }
    }

  if (maxValue > minValue)
    {
    // Generate the lookup table
    table->SetRange(minValue, maxValue);
    table->SetNumberOfColors(maxValue - minValue + 1);
    for (int i = minValue; i <= maxValue; i++)
      {
      double rgba[4] = { 0.0, 0.0, 0.0, 1.0 };
      for (int j = 0; j < 4; j++)
        {
        int k = i - firstValue[j];
        k = (i >= firstValue[j] ? k : 0);
        k = (i <= lastValue[j] ? k : lastValue[j] - firstValue[j]);
        if (spp[j])
          {
          rgba[j] = spp[j][k] / divisor[j];
          }
        else if (cpp[j])
          {
          rgba[j] = cpp[j][k] / divisor[j];
          }
        }
      table->SetTableValue(i - minValue, rgba);
      }
    }
}
