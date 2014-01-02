/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMCTGenerator.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include "vtkObjectFactory.h"
#include "vtkDataSetAttributes.h"
#include "vtkInformation.h"

vtkStandardNewMacro(vtkDICOMCTGenerator);

//----------------------------------------------------------------------------
vtkDICOMCTGenerator::vtkDICOMCTGenerator()
{
}

//----------------------------------------------------------------------------
vtkDICOMCTGenerator::~vtkDICOMCTGenerator()
{
}

//----------------------------------------------------------------------------
void vtkDICOMCTGenerator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
bool vtkDICOMCTGenerator::GenerateCTSeriesModule(vtkDICOMMetaData *meta)
{
  meta->SetAttributeValue(DC::Modality, "CT");

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::ReferencedPerformedProcedureStepSequence, // 1C
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMCTGenerator::GenerateCTImageModule(vtkDICOMMetaData *meta)
{
  // ImageType is specialized from GeneralImageModule,
  // by adding a third value that is specific to CT:
  // AXIAL or LOCALIZER
  const char *it = 0;
  if (this->MetaData)
    {
    it = this->MetaData->GetAttributeValue(DC::ImageType).GetCharData();
    }
  if (it == 0 || it[0] == '\0')
    {
    it = "DERIVED\\SECONDARY\\AXIAL";
    }
  meta->SetAttributeValue(DC::ImageType, it);

  // These specialized from ImagePixelModule:
  // SamplesPerPixel must be 1
  // PhotometricInterpretation must be MONOCHROME1 or MONOCHROME2
  // BitsAllocated must be 16
  // BitsStored must be 12 to 16

  // these are mandatory
  meta->SetAttributeValue(DC::RescaleIntercept, this->RescaleIntercept);
  meta->SetAttributeValue(DC::RescaleSlope, this->RescaleSlope);

  // required items: use simple read/write validation
  DC::EnumType required[] = {
    DC::KVP,
    DC::AcquisitionNumber,
    DC::ItemDelimitationItem
  };

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::RescaleType, // 1C
    DC::ScanOptions,
    DC::DataCollectionDiameter,
    DC::DataCollectionCenterPatient,
    DC::ReconstructionDiameter,
    DC::ReconstructionTargetCenterPatient,
    DC::DistanceSourceToDetector,
    DC::GantryDetectorTilt,
    DC::TableHeight,
    DC::RotationDirection,
    DC::ExposureTime,
    DC::XRayTubeCurrent,
    DC::Exposure,
    DC::ExposureInuAs,
    DC::FilterType,
    DC::GeneratorPower,
    DC::FocalSpots,
    DC::ConvolutionKernel,
    DC::RevolutionTime,
    DC::SingleCollimationWidth,
    DC::TotalCollimationWidth,
    DC::TableSpeed,
    DC::TableFeedPerRotation,
    DC::SpiralPitchFactor,
    DC::ExposureModulationType,
    DC::EstimatedDoseSaving,
    DC::CTDIvol,
    DC::CTDIPhantomTypeCodeSequence,
    DC::AnatomicRegionSequence,
    DC::PrimaryAnatomicStructureSequence,
    DC::CalciumScoringMassFactorPatient,
    DC::CalciumScoringMassFactorDevice,
    DC::EnergyWeightingFactor, // 1C
    DC::CTAdditionalXRaySourceSequence,
    DC::ItemDelimitationItem
  };

  return (this->CopyRequiredAttributes(required, meta) &&
          this->CopyOptionalAttributes(optional, meta));
}

//----------------------------------------------------------------------------
bool vtkDICOMCTGenerator::GenerateCTInstance(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  this->SetPixelRestrictions(
    RepresentationSigned | RepresentationUnsigned,
    BitsStored12 | BitsStored16,
    1);

  const char *SOPClass = "1.2.840.10008.5.1.4.1.1.2";
  this->InitializeMetaData(info, meta);

  if (!this->GenerateSOPCommonModule(meta, SOPClass) ||
      !this->GeneratePatientModule(meta) ||
      !this->GenerateClinicalTrialSubjectModule(meta) ||
      !this->GenerateGeneralStudyModule(meta) ||
      !this->GeneratePatientStudyModule(meta) ||
      !this->GenerateClinicalTrialStudyModule(meta) ||
      !this->GenerateGeneralSeriesModule(meta) ||
      !this->GenerateFrameOfReferenceModule(meta) ||
      !this->GenerateClinicalTrialSeriesModule(meta) ||
      !this->GenerateGeneralEquipmentModule(meta) ||
      !this->GenerateGeneralImageModule(meta) ||
      !this->GenerateImagePlaneModule(meta) ||
      !this->GenerateImagePixelModule(meta) ||
      !this->GenerateContrastBolusModule(meta) ||
      !this->GenerateDeviceModule(meta) ||
      !this->GenerateSpecimenModule(meta) ||
      !this->GenerateCTSeriesModule(meta) ||
      !this->GenerateCTImageModule(meta) ||
      !this->GenerateOverlayPlaneModule(meta) ||
      !this->GenerateVOILUTModule(meta))
    {
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMCTGenerator::GenerateInstance(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  if (this->MultiFrame)
    {
    vtkErrorMacro("Enhanced Multi-Frame CT is not yet supported.");
    return false;
    }

  return this->GenerateCTInstance(info, meta);
}
