/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMMRGenerator.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include "vtkObjectFactory.h"
#include "vtkDataSetAttributes.h"
#include "vtkInformation.h"

vtkStandardNewMacro(vtkDICOMMRGenerator);

//----------------------------------------------------------------------------
vtkDICOMMRGenerator::vtkDICOMMRGenerator()
{
}

//----------------------------------------------------------------------------
vtkDICOMMRGenerator::~vtkDICOMMRGenerator()
{
}

//----------------------------------------------------------------------------
void vtkDICOMMRGenerator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateMRImageModule(vtkDICOMMetaData *meta)
{
  // specialized from GeneralImageModule
  // DC::ImageType,

  // specialized from ImagePixelModule
  // DC::SamplesPerPixel,
  // DC::PhotometricInterpretation,
  // DC::BitsAllocated

  // mandatory, specific to MRI
  // DC::ScanningSequence
  // DC::SequenceVariant

  // required items: use simple read/write validation
  static const DC::EnumType required[] = {
    DC::ScanOptions,
    DC::MRAcquisitionType,
    DC::RepetitionTime, // 2C, not req'd if EP and not SK
    DC::EchoTime,
    DC::EchoTrainLength,
    DC::InversionTime, // 2C, req'd if ScanningSequence is IR
    DC::TriggerTime, // 2C, req'd for cardiac gating
    DC::ItemDelimitationItem
  };

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::SequenceName,
    DC::AngioFlag,
    DC::NumberOfAverages,
    DC::ImagingFrequency,
    DC::ImagedNucleus,
    // DC::EchoNumber, // can be per-instance
    DC::MagneticFieldStrength,
    // DC::SpacingBetweenSlices, // invalidated if reformatted
    DC::NumberOfPhaseEncodingSteps,
    DC::PercentSampling,
    DC::PercentPhaseFieldOfView,
    DC::PixelBandwidth,
    DC::NominalInterval,
    DC::BeatRejectionFlag,
    DC::LowRRValue,
    DC::HighRRValue,
    DC::IntervalsAcquired,
    DC::IntervalsRejected,
    DC::PVCRejection,
    DC::SkipBeats,
    DC::HeartRate,
    // DC::CardiacNumberOfImages, // could be invalidated
    DC::TriggerWindow,
    DC::ReconstructionDiameter,
    DC::ReceiveCoilName,
    DC::TransmitCoilName,
    // DC::InPlanePhaseEncodingDirection, // could be invalidated
    DC::FlipAngle,
    DC::SAR,
    DC::VariableFlipAngleFlag,
    DC::dBdt,
    // DC::TemporalPositionIdentifier, // per-instance
    // DC::NumberOfTemporalPositions,
    // DC::TemporalResolution,
    DC::AnatomicRegionSequence,
    DC::PrimaryAnatomicStructureSequence,
    DC::ItemDelimitationItem
  };

  return (this->CopyRequiredAttributes(required, meta) &&
          this->CopyOptionalAttributes(optional, meta));
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateMRInstance(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  const char *SOPClass = "1.2.840.10008.5.1.4.1.1.4";
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
      !this->GenerateMRImageModule(meta))
    {
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateInstance(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  if (this->MultiFrame)
    {
    vtkErrorMacro("Enhanced Multi-Frame MR is not yet supported.");
    return false;
    }

  return this->GenerateMRInstance(info, meta);
}
