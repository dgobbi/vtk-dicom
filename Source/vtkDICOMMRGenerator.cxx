/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMMRGenerator.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"
#include "vtkDICOMMetaDataAdapter.h"

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
bool vtkDICOMMRGenerator::GenerateMRSeriesModule(vtkDICOMMetaData *source)
{
  vtkDICOMMetaData *meta = this->MetaData;
  meta->Set(DC::Modality, "MR");

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::ReferencedPerformedProcedureStepSequence, // 1C
    DC::ItemDelimitationItem
  };

  return this->CopyOptionalAttributes(optional, source);
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateMRImageModule(vtkDICOMMetaData *source)
{
  // ImageType is specialized from GeneralImageModule,
  // by adding a third value that is specific to MRI:
  // MPR, T2 MAP, PHASE MAP, PHASE SUBTRACT, PROJECTION IMAGE,
  // DIFFUSION MAP, VELOCITY MAP, MODULUS SUBTRACT, T1 MAP,
  // DENSITY MAP, IMAGE ADDITION, OTHER
  const char *it = 0;
  if (source)
  {
    it = source->Get(DC::ImageType).GetCharData();
  }
  if (it == 0 || it[0] == '\0')
  {
    it = "DERIVED\\SECONDARY\\OTHER";
  }
  vtkDICOMMetaData *meta = this->MetaData;
  meta->Set(DC::ImageType, it);

  // These specialized from ImagePixelModule:
  // SamplesPerPixel must be 1
  // PhotometricInterpretation must be MONOCHROME1 or MONOCHROME2
  // BitsAllocated must be 16

  // ScanningSequence and SequenceVariant are mandatory:
  const char *ss = 0;
  const char *sv = 0;
  if (source)
  {
    ss = source->Get(DC::ScanningSequence).GetCharData();
    sv = source->Get(DC::SequenceVariant).GetCharData();
  }
  if (ss == 0 || ss[0] == '\0')
  { // default to "research mode"
    ss = "RM";
  }
  if (sv == 0 || sv[0] == '\0')
  {
    sv = "NONE";
  }
  meta->Set(DC::ScanningSequence, ss);
  meta->Set(DC::SequenceVariant, sv);

  // SpacingBetweenSlices is optional, but everyone uses it
  meta->Set(DC::SpacingBetweenSlices, this->Spacing[2]);

  if (source)
  {
    // set this to the time dimension
    if (source->Has(DC::CardiacNumberOfImages))
    {
      meta->Set(DC::CardiacNumberOfImages, this->Dimensions[3]);
    }
    // keep this if data was not reformatted
    if (this->SourceInstanceArray != 0 && source == this->SourceMetaData)
    {
      vtkDICOMMetaDataAdapter sourceAdapter(source);
      const char *ped =
        sourceAdapter->Get(DC::InPlanePhaseEncodingDirection).GetCharData();
      if (ped != 0 && ped[0] != '\0')
      {
        meta->Set(DC::InPlanePhaseEncodingDirection, ped);
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
      meta->Set(i, DC::TemporalPositionIdentifier, t + 1);
    }
    meta->Set(
      DC::NumberOfTemporalPositions, this->Dimensions[3]);
    meta->Set(
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

  return (this->CopyRequiredAttributes(required, source) &&
          this->CopyOptionalAttributes(optional, source));
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateMRInstance(vtkInformation *info)
{
  this->SetPixelRestrictions(
    RepresentationSigned | RepresentationUnsigned,
    BitsStored12 | BitsStored16,
    1);

  const char *SOPClass = "1.2.840.10008.5.1.4.1.1.4";
  this->InitializeMetaData(info);

  vtkDICOMMetaData *source = this->SourceMetaData;
  if (!this->GenerateSOPCommonModule(source, SOPClass) ||
      !this->GeneratePatientModule(source) ||
      !this->GenerateClinicalTrialSubjectModule(source) ||
      !this->GenerateGeneralStudyModule(source) ||
      !this->GeneratePatientStudyModule(source) ||
      !this->GenerateClinicalTrialStudyModule(source) ||
      !this->GenerateGeneralSeriesModule(source) ||
      !this->GenerateFrameOfReferenceModule(source) ||
      !this->GenerateClinicalTrialSeriesModule(source) ||
      !this->GenerateGeneralEquipmentModule(source) ||
      !this->GenerateGeneralImageModule(source) ||
      !this->GenerateImagePlaneModule(source) ||
      !this->GenerateImagePixelModule(source) ||
      !this->GenerateContrastBolusModule(source) ||
      !this->GenerateDeviceModule(source) ||
      !this->GenerateSpecimenModule(source) ||
      !this->GenerateMRSeriesModule(source) ||
      !this->GenerateMRImageModule(source) ||
      !this->GenerateOverlayPlaneModule(source) ||
      !this->GenerateVOILUTModule(source))
  {
    return false;
  }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateInstance(vtkInformation *info)
{
  if (this->MultiFrame)
  {
    vtkErrorMacro("Enhanced Multi-Frame MR is not yet supported.");
    return false;
  }

  return this->GenerateMRInstance(info);
}
