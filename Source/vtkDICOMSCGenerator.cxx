/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMSCGenerator.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include "vtkObjectFactory.h"
#include "vtkDataSetAttributes.h"
#include "vtkInformation.h"

vtkStandardNewMacro(vtkDICOMSCGenerator);

//----------------------------------------------------------------------------
vtkDICOMSCGenerator::vtkDICOMSCGenerator()
{
}

//----------------------------------------------------------------------------
vtkDICOMSCGenerator::~vtkDICOMSCGenerator()
{
}

//----------------------------------------------------------------------------
void vtkDICOMSCGenerator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
bool vtkDICOMSCGenerator::GenerateSCMultiFrameImageModule(
  vtkDICOMMetaData *source)
{
  // The BurnedInAnnotation attribute is mandatory
  std::string bia;
  if (source)
  {
    bia = source->Get(DC::BurnedInAnnotation).AsString();
  }
  if (bia != "YES")
  {
    bia = "NO";
  }
  vtkDICOMMetaData *meta = this->MetaData;
  meta->Set(DC::BurnedInAnnotation, bia);

  // These are mandatory, and must be set to these values
  if (meta->Get(DC::BitsStored).AsInt() != 1)
  {
    meta->Set(DC::PresentationLUTShape, "IDENTITY");
    meta->Set(DC::RescaleIntercept, 0.0);
    meta->Set(DC::RescaleSlope, 1.0);
    meta->Set(DC::RescaleType, "US");
  }

  // get dimensions of the data set: x,y,z,t,v
  int nframes = this->NumberOfFrames;
  int *dims = this->Dimensions;
  double *spacing = this->Spacing;

  // set multi-frame information
  meta->Set(DC::NumberOfFrames, nframes);

  // build the FrameIncrementPointer and the vectors
  vtkDICOMTag pointers[2];
  int npointers = 0;
  double *zvector = new double[nframes];
  double *tvector = new double[nframes];

  int vdim = (dims[4] > 0 ? dims[4] : 1);
  int tdim = (dims[3] > 0 ? dims[3] : 1);
  for (int f = 0; f < nframes; f++)
  {
    int t = (f / vdim) % tdim;
    int z = f / (vdim * tdim);
    zvector[f] = z*spacing[2];
    tvector[f] = (t == 0 ? 0.0 : spacing[3]);
  }

  if (dims[3] > 0 || (dims[2] == 0 && nframes == 1))
  {
    pointers[npointers++] = DC::FrameTimeVector;
    meta->Set(DC::FrameTimeVector,
      vtkDICOMValue(vtkDICOMVR::DS, tvector, nframes));
  }
  if (dims[2] > 0)
  {
    pointers[npointers++] = DC::SliceLocationVector;
    meta->Set(DC::SliceLocationVector,
      vtkDICOMValue(vtkDICOMVR::DS, zvector, nframes));
  }

  meta->Erase(DC::FrameTime);
  meta->Set(DC::FrameIncrementPointer,
    vtkDICOMValue(vtkDICOMVR::AT, pointers, npointers));

  meta->Erase(DC::PixelAspectRatio);
  meta->Set(DC::PixelSpacing, vtkDICOMValue(vtkDICOMVR::DS, spacing, 2));

  delete [] zvector;
  delete [] tvector;

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::RecognizableVisualFeatures,
    DC::Illumination,
    DC::ReflectedAmbientLight,
    DC::NominalScannedPixelSpacing, // 1C (mandatory if ConversionType is DF)
    DC::PixelSpacingCalibrationType,
    DC::PixelSpacingCalibrationDescription, // 1C
    DC::DigitizingDeviceTransportDirection,
    DC::RotationOfScannedFilm,
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, source);
}

//----------------------------------------------------------------------------
bool vtkDICOMSCGenerator::GenerateSCImageModule(vtkDICOMMetaData *source)
{
  // These are not set, because AspectRatio is used instead
  // DC::PixelSpacing, // 1C
  // DC::PixelSpacingCalibrationType,
  // DC::PixelSpacingCalibrationDescription, // 1C

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::DateOfSecondaryCapture,
    DC::TimeOfSecondaryCapture,
    DC::NominalScannedPixelSpacing,
    DC::DocumentClassCodeSequence,
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, source);
}

//----------------------------------------------------------------------------
bool vtkDICOMSCGenerator::GenerateSCEquipmentModule(vtkDICOMMetaData *source)
{
  // ConversionType is a mandatory attribute
  std::string ct;
  if (source)
  {
    ct = source->Get(DC::ConversionType).AsString();
  }
  if (ct == "")
  {
    ct = "WSD"; // workstation
  }
  vtkDICOMMetaData *meta = this->MetaData;
  meta->Set(DC::ConversionType, ct);

  // Modality is optional for Secondary Capture
  std::string m = meta->Get(DC::Modality).AsString();
  if (m == "" || m == "OT")
  {
    meta->Erase(DC::Modality);
  }

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::Modality,
    DC::SecondaryCaptureDeviceID,
    DC::SecondaryCaptureDeviceManufacturer,
    DC::SecondaryCaptureDeviceManufacturerModelName,
    DC::SecondaryCaptureDeviceSoftwareVersions,
    DC::VideoImageFormatAcquired,
    DC::DigitalImageFormatAcquired,
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, source);
}

//----------------------------------------------------------------------------
bool vtkDICOMSCGenerator::GenerateSCMultiFrameInstance(vtkInformation *info)
{
  // get the scalar information
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(
    info, vtkDataObject::FIELD_ASSOCIATION_POINTS,
    vtkDataSetAttributes::SCALARS);

  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents = scalarInfo->Get(
    vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());

  const char *SOPClass = 0;
  if (scalarType == VTK_UNSIGNED_CHAR)
  {
    this->SetPixelRestrictions(
       RepresentationUnsigned,
       BitsStored8,
       numComponents);

    if (numComponents < 3)
    {
      SOPClass = "1.2.840.10008.5.1.4.1.1.7.2";
    }
    else
    {
      SOPClass = "1.2.840.10008.5.1.4.1.1.7.4";
    }
  }
  else
  {
    this->SetPixelRestrictions(
       RepresentationUnsigned,
       BitsStored10 | BitsStored12 | BitsStored16,
       1);

    SOPClass = "1.2.840.10008.5.1.4.1.1.7.3";
  }

  this->InitializeMetaData(info);

  vtkDICOMMetaData *source = this->SourceMetaData;
  if (!this->GenerateSOPCommonModule(source, SOPClass) ||
      !this->GeneratePatientModule(source) ||
      !this->GenerateClinicalTrialSubjectModule(source) ||
      !this->GenerateGeneralStudyModule(source) ||
      !this->GeneratePatientStudyModule(source) ||
      !this->GenerateClinicalTrialStudyModule(source) ||
      !this->GenerateGeneralSeriesModule(source) ||
      !this->GenerateClinicalTrialSeriesModule(source) ||
      // optional General Equipment Module intentionally omitted
      !this->GenerateSCEquipmentModule(source) ||
      !this->GenerateGeneralImageModule(source) ||
      !this->GenerateImagePixelModule(source) ||
      // the Cine Module is added by GenerateSCMultiFrameImageModule
      !this->GenerateDeviceModule(source) ||
      !this->GenerateSpecimenModule(source) ||
      !this->GenerateSCMultiFrameImageModule(source))
  {
    return false;
  }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMSCGenerator::GenerateSCInstance(vtkInformation *info)
{
  // get the scalar information
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(
    info, vtkDataObject::FIELD_ASSOCIATION_POINTS,
    vtkDataSetAttributes::SCALARS);

  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents = scalarInfo->Get(
    vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());
  int samplesPerPixel = 1;

  if (scalarType == VTK_UNSIGNED_CHAR)
  {
    samplesPerPixel = numComponents;
  }

  this->SetPixelRestrictions(
    RepresentationUnsigned | RepresentationSigned,
    BitsStored8 | BitsStored10 | BitsStored12 | BitsStored16,
    samplesPerPixel);

  const char *SOPClass = "1.2.840.10008.5.1.4.1.1.7";
  this->InitializeMetaData(info);

  vtkDICOMMetaData *source = this->SourceMetaData;
  if (!this->GenerateSOPCommonModule(source, SOPClass) ||
      !this->GeneratePatientModule(source) ||
      !this->GenerateClinicalTrialSubjectModule(source) ||
      !this->GenerateGeneralStudyModule(source) ||
      !this->GeneratePatientStudyModule(source) ||
      !this->GenerateClinicalTrialStudyModule(source) ||
      !this->GenerateGeneralSeriesModule(source) ||
      !this->GenerateClinicalTrialSeriesModule(source) ||
      // optional GeneralEquipmentModule intentionally omitted
      !this->GenerateSCEquipmentModule(source) ||
      !this->GenerateGeneralImageModule(source) ||
      !this->GenerateImagePixelModule(source) ||
      !this->GenerateDeviceModule(source) ||
      !this->GenerateSpecimenModule(source) ||
      !this->GenerateSCImageModule(source) ||
      !this->GenerateOverlayPlaneModule(source))
  {
    return false;
  }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMSCGenerator::GenerateInstance(vtkInformation *info)
{
  if (this->MultiFrame == 0)
  {
    return this->GenerateSCInstance(info);
  }

  return this->GenerateSCMultiFrameInstance(info);
}
