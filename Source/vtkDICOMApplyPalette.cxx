/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2022 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMApplyPalette.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMLookupTable.h"

#include "vtkObjectFactory.h"
#include "vtkDataSetAttributes.h"
#include "vtkImageData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkIntArray.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"
#include "vtkVersion.h"

#include "vtkTemplateAliasMacro.h"
// turn off types that never occur in DICOM palette images
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

vtkStandardNewMacro(vtkDICOMApplyPalette);

class vtkDICOMPerFilePalette :
  public std::vector<vtkSmartPointer<vtkDICOMLookupTable> >
{
};

//----------------------------------------------------------------------------
vtkDICOMApplyPalette::vtkDICOMApplyPalette()
{
  this->Palette = 0;
  this->IsSupplemental = false;
}

//----------------------------------------------------------------------------
vtkDICOMApplyPalette::~vtkDICOMApplyPalette()
{
  delete this->Palette;
}

//----------------------------------------------------------------------------
void vtkDICOMApplyPalette::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------

namespace {

template<class T>
void vtkDICOMApplyPaletteExecute(
  vtkDICOMApplyPalette *self, vtkImageData *inData, T *inPtr0,
  vtkImageData *outData, unsigned char *outPtr0, int extent[6],
  vtkDICOMPerFilePalette *palette, bool supplemental, int id)
{
  vtkInformation *dataInfo = outData->GetInformation();
  vtkDICOMMetaData *meta = vtkDICOMMetaData::SafeDownCast(
    dataInfo->Get(vtkDICOMAlgorithm::META_DATA()));

  vtkIdType inIncX, inIncY, inIncZ;
  inData->GetIncrements(inIncX, inIncY, inIncZ);
  vtkIdType outIncX, outIncY, outIncZ;
  outData->GetIncrements(outIncX, outIncY, outIncZ);
  int inputComponents = inData->GetNumberOfScalarComponents();
  int outputComponents = outData->GetNumberOfScalarComponents();

  // target for progress tracking
  vtkIdType target = inputComponents;
  target *= extent[5] - extent[4] + 1;
  target *= extent[3] - extent[2] + 1;
  vtkIdType progress = 0;

  for (int c = 0; c < inputComponents; c++)
  {
    T *inPtrC = inPtr0 + c;
    unsigned char *outPtrC = outPtr0 + 3*c;

    for (int zIdx = extent[4]; zIdx <= extent[5]; zIdx++)
    {
      int i = meta->GetFileIndex(zIdx, c, inputComponents);
      int f = meta->GetFrameIndex(zIdx, c, inputComponents);
      i = (i >= 0 ? i : 0);
      vtkDICOMLookupTable *table = (*(palette))[i];
      double range[2];
      table->GetTableRange(range);
      int firstValueMapped = static_cast<int>(range[0]);
      int maxIdx = static_cast<int>(range[1]) - firstValueMapped;
      if (maxIdx >= table->GetNumberOfColors())
      {
        maxIdx = table->GetNumberOfColors() - 1;
      }
      const unsigned char *rgba = table->GetPointer(0);
      T *inPtrZ = inPtrC + (zIdx - extent[4])*inIncZ;
      unsigned char *outPtrZ = outPtrC + (zIdx - extent[4])*outIncZ;

      // for monochrome mapping when palette is supplemental
      bool monochrome = false;
      double windowCenter = 0.0;
      double windowWidth = 1.0;
      double slope = 1.0;
      double inter = 0.0;
      bool isSigmoid = false;
      bool isLinearExact = false;
      if (supplemental)
      {
        // check if this frame is specifically monochrome
        monochrome = meta->Get(i, f, DC::PixelPresentation).Matches(
          "MONOCHROME*");

        // use the window that is suggested in the data
        const vtkDICOMValue& wc = meta->Get(i, f, DC::WindowCenter);
        const vtkDICOMValue& ww = meta->Get(i, f, DC::WindowWidth);
        if (wc.IsValid() && ww.IsValid())
        {
          windowCenter = wc.AsDouble();
          windowWidth = ww.AsDouble();
        }

        // check which function to apply
        const vtkDICOMValue& wf = meta->Get(i, f, DC::VOILUTFunction);
        if (wf.IsValid())
        {
          isLinearExact = wf.Matches("LINEAR_EXACT");
          isSigmoid = wf.Matches("SIGMOID");
        }

        // for CT images, the rescaling must be taken into account
        const vtkDICOMValue& rs = meta->Get(i, f, DC::RescaleSlope);
        const vtkDICOMValue& ri = meta->Get(i, f, DC::RescaleIntercept);
        if (rs.IsValid() && ri.IsValid())
        {
          slope = rs.AsDouble();
          inter = ri.AsDouble();
          if (slope == 0.0)
          {
            slope = 1.0;
          }
        }
      }

      // these values are used to compute the VOI LUT (DICOM PS3.3 C.11.2.1)
      double ww = windowWidth;
      double wc = windowCenter;
      if (!isLinearExact && !isSigmoid)
      {
        ww -= 1.0;
        wc -= 0.5;
      }
      ww = ww/slope;
      wc = (wc - inter)/slope;
      if (ww < 0.0)
      {
        ww = 0.0;
      }
      double ws = (isSigmoid ? -4.0 : 255.0);
      if (ww != 0.0)
      {
        ws /= ww;
      }
      else
      {
        ws = 1.0;
        isSigmoid = false;
      }
      double wl = wc - 0.5*ww;
      double wh = wc + 0.5*ww;

      // loop through slices
      for (int yIdx = extent[2]; yIdx <= extent[3]; yIdx++)
      {
        T *inPtr = inPtrZ + inIncY*(yIdx - extent[2]);
        unsigned char *outPtr = outPtrZ + outIncY*(yIdx - extent[2]);

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

        for (int xIdx = extent[0]; xIdx <= extent[1]; xIdx++)
        {
          int idx = inPtr[0] - firstValueMapped;
          if (monochrome || (supplemental && idx < 0))
          {
            double fidx = inPtr[0];
            if (isSigmoid)
            {
              fidx = 255.0/(1.0 + exp((fidx - wc)*ws));
            }
            else if (fidx <= wl)
            {
              fidx = 0.0;
            }
            else if (fidx > wh)
            {
              fidx = 255.0;
            }
            else
            {
              fidx = (fidx - wc)*ws + 127.5;
              fidx = (fidx >= 0.0 ? fidx : 0.0);
              fidx = (fidx <= 255.0 ? fidx : 255.0);
            }
            int gray = static_cast<int>(fidx + 0.5);
            outPtr[0] = gray;
            outPtr[1] = gray;
            outPtr[2] = gray;
          }
          else
          {
            // use color
            idx = (idx >= 0 ? idx : 0);
            idx = (idx <= maxIdx ? idx : maxIdx);
            const unsigned char *rgb = rgba + 4*idx;
            outPtr[0] = rgb[0];
            outPtr[1] = rgb[1];
            outPtr[2] = rgb[2];
          }
          inPtr += inputComponents;
          outPtr += outputComponents;
        }
      }
    }
  }
}

} // end anonymous namespace

//----------------------------------------------------------------------------
int vtkDICOMApplyPalette::RequestInformation(
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

  // Get the meta data
  vtkInformation *metaInfo = this->GetMetaDataInformation(inputVector, 0, 0);
  vtkDICOMMetaData *meta = vtkDICOMMetaData::SafeDownCast(
      metaInfo->Get(vtkDICOMAlgorithm::META_DATA()));

  // Bypass unless there is a palette to apply
  delete this->Palette;
  this->Palette = 0;
  this->IsSupplemental = 0;
  bool hasPalette = false;

  if (meta && meta->Get(DC::SamplesPerPixel).Matches(1))
  {
    // Check if PhotometricInterpretation is PALETTE COLOR
    const vtkDICOMValue& u = meta->Get(DC::PhotometricInterpretation);
    hasPalette = u.Matches("PALETTE?COLOR");

    // Check the PixelPresentation (enhanced files)
    const vtkDICOMValue& v = meta->Get(DC::PixelPresentation);
    this->IsSupplemental = (v.Matches("COLOR") ||
                            v.Matches("MIXED") ||
                            v.Matches("TRUE_COLOR"));
    hasPalette |= this->IsSupplemental;
  }

  // Modify the information
  if (hasPalette)
  {
    // By setting Palette, we let RequestData know that there is a palette
    this->Palette = new vtkDICOMPerFilePalette;
    scalarType = VTK_UNSIGNED_CHAR;
    numComponents *= 3;

    // Set the output information.
    vtkInformation* outInfo = outputVector->GetInformationObject(0);
    vtkDataObject::SetPointDataActiveScalarInfo(
      outInfo, scalarType, numComponents);

    // Modify the meta data, the image has become an RGB image
    vtkDICOMMetaData *outMeta = vtkDICOMMetaData::SafeDownCast(
      outInfo->Get(vtkDICOMAlgorithm::META_DATA()));
    outMeta->Set(DC::SamplesPerPixel, 3);
    outMeta->Set(DC::PhotometricInterpretation, "RGB");
    outMeta->Set(DC::PixelRepresentation, 0);
    outMeta->Set(DC::BitsAllocated, 8);
    outMeta->Set(DC::BitsStored, 8);
    outMeta->Set(DC::HighBit, 7);
    outMeta->Erase(DC::RedPaletteColorLookupTableDescriptor);
    outMeta->Erase(DC::GreenPaletteColorLookupTableDescriptor);
    outMeta->Erase(DC::BluePaletteColorLookupTableDescriptor);
    outMeta->Erase(DC::RedPaletteColorLookupTableData);
    outMeta->Erase(DC::GreenPaletteColorLookupTableData);
    outMeta->Erase(DC::BluePaletteColorLookupTableData);
    outMeta->Erase(DC::SegmentedRedPaletteColorLookupTableData);
    outMeta->Erase(DC::SegmentedGreenPaletteColorLookupTableData);
    outMeta->Erase(DC::SegmentedBluePaletteColorLookupTableData);
  }

  return 1;
}

//----------------------------------------------------------------------------
int vtkDICOMApplyPalette::RequestData(
  vtkInformation* request,
  vtkInformationVector** inputVector,
  vtkInformationVector* outputVector)
{
  // Get the meta data
  vtkInformation *metaInfo = this->GetMetaDataInformation(inputVector, 0, 0);
  vtkDICOMMetaData *meta = vtkDICOMMetaData::SafeDownCast(
      metaInfo->Get(vtkDICOMAlgorithm::META_DATA()));

  // Passthrough if there is no palette to apply
  if (meta == 0 || this->Palette == 0)
  {
    vtkInformation *inInfo = inputVector[0]->GetInformationObject(0);
    vtkInformation *outInfo = outputVector->GetInformationObject(0);
    vtkImageData *inData =
      vtkImageData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));
    vtkImageData *outData =
      static_cast<vtkImageData *>(outInfo->Get(vtkDataObject::DATA_OBJECT()));

    outData->CopyStructure(inData);
    outData->GetPointData()->PassData(inData->GetPointData());
    return 1;
  }

  // Build the lookup tables for all files that make up the volume
  int n = meta->GetNumberOfInstances();
  this->Palette->resize(n);
  for (int i = 0; i < n; i++)
  {
    (*(this->Palette))[i] = vtkSmartPointer<vtkDICOMLookupTable>::New();
    (*(this->Palette))[i]->BuildImagePalette(meta, i);
  }

  // Allow the superclass to call the ThreadedRequestData method
  int rval = this->Superclass::RequestData(
    request, inputVector, outputVector);

  this->Palette->clear();

  return rval;
}

//----------------------------------------------------------------------------
void vtkDICOMApplyPalette::ThreadedRequestData(
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

  switch (scalarType)
  {
    vtkTemplateAliasMacro(
      vtkDICOMApplyPaletteExecute(
        this, inData, static_cast<VTK_TT *>(inVoidPtr), outData,
        static_cast<unsigned char *>(outVoidPtr), extent,
        this->Palette, this->IsSupplemental, id));
  }
}
