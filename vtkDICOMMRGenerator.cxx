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
bool vtkDICOMMRGenerator::GenerateMRSeriesModule(vtkDICOMMetaData *meta)
{
  meta->SetAttributeValue(DC::Modality, "MR");

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::ReferencedPerformedProcedureStepSequence, // 1C
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, meta);
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateMRImageModule(vtkDICOMMetaData *meta)
{
  // ImageType is specialized from GeneralImageModule,
  // by adding a third value that is specific to MRI:
  // MPR, T2 MAP, PHASE MAP, PHASE SUBTRACT, PROJECTION IMAGE,
  // DIFFUSION MAP, VELOCITY MAP, MODULUS SUBTRACT, T1 MAP,
  // DENSITY MAP, IMAGE ADDITION, OTHER
  const char *it = 0;
  if (this->MetaData)
    {
    it = this->MetaData->GetAttributeValue(DC::ImageType).GetCharData();
    }
  if (it == 0 || it[0] == '\0')
    {
    it = "DERIVED\\SECONDARY\\OTHER";
    }
  meta->SetAttributeValue(DC::ImageType, it);

  // These specialized from ImagePixelModule:
  // SamplesPerPixel must be 1
  // PhotometricInterpretation must be MONOCHROME1 or MONOCHROME2
  // BitsAllocated must be 16

  // ScanningSequence and SequenceVariant are mandatory:
  const char *ss = 0;
  const char *sv = 0;
  if (this->MetaData)
    {
    ss = this->MetaData->GetAttributeValue(DC::ScanningSequence).GetCharData();
    sv = this->MetaData->GetAttributeValue(DC::SequenceVariant).GetCharData();
    }
  if (ss == 0 || ss[0] == '\0')
    { // default to "research mode"
    ss = "RM";
    }
  if (sv == 0 || sv[0] == '\0')
    {
    sv = "NONE";
    }
  meta->SetAttributeValue(DC::ScanningSequence, ss);
  meta->SetAttributeValue(DC::SequenceVariant, sv);

  // SpacingBetweenSlices is optional, but everyone uses it
  meta->SetAttributeValue(DC::SpacingBetweenSlices, this->Spacing[2]);

  if (this->MetaData)
    {
    // set this to the time dimension
    if (this->MetaData->HasAttribute(DC::CardiacNumberOfImages))
      {
      meta->SetAttributeValue(DC::CardiacNumberOfImages, this->Dimensions[3]);
      }
    // keep this if data was not reformatted
    if (this->SourceInstanceArray != 0)
      {
      const char *ped = this->MetaData->GetAttributeValue(
        DC::InPlanePhaseEncodingDirection).GetCharData();
      if (ped != 0 && ped[0] != '\0')
        {
        meta->SetAttributeValue(DC::InPlanePhaseEncodingDirection, ped);
        }
      }
    }

  // temporal information
  if (this->Dimensions[3] > 1)
    {
    int n = meta->GetNumberOfInstances();
    int nslices = (this->Dimensions[2] > 0 ? this->Dimensions[2] : 1);

    for (int i = 0; i < n; i++)
      {
      int t = (i % (n / nslices)) / (n / (nslices*this->Dimensions[3]));
      meta->SetAttributeValue(i, DC::TemporalPositionIdentifier, t + 1);
      }
    meta->SetAttributeValue(
      DC::NumberOfTemporalPositions, this->Dimensions[3]);
    meta->SetAttributeValue(
      DC::TemporalResolution, this->Spacing[3]);
    }

  // required items: use simple read/write validation
  DC::EnumType required[] = {
    DC::ScanOptions,
    DC::MRAcquisitionType,
    DC::EchoTime,
    DC::EchoTrainLength,
    DC::ItemDelimitationItem
  };

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::RepetitionTime, // 2C, not req'd if EP and not SK
    DC::InversionTime, // 2C, req'd if ScanningSequence is IR
    DC::TriggerTime, // 2C, req'd for cardiac gating
    DC::SequenceName,
    DC::AngioFlag,
    DC::NumberOfAverages,
    DC::ImagingFrequency,
    DC::ImagedNucleus,
    DC::EchoNumbers, // can be per-instance
    DC::MagneticFieldStrength,
    // DC::SpacingBetweenSlices, // see above
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
    // DC::CardiacNumberOfImages, // see above
    DC::TriggerWindow,
    DC::ReconstructionDiameter,
    DC::ReceiveCoilName,
    DC::TransmitCoilName,
    DC::AcquisitionMatrix,
    // DC::InPlanePhaseEncodingDirection, // see above
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
  this->SetPixelRestrictions(
    RepresentationSigned | RepresentationUnsigned,
    BitsStored12 | BitsStored16,
    1);

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
      !this->GenerateMRSeriesModule(meta) ||
      !this->GenerateMRImageModule(meta) ||
      !this->GenerateOverlayPlaneModule(meta) ||
      !this->GenerateVOILUTModule(meta))
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
