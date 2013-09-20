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
bool vtkDICOMMRGenerator::GenerateMRMultiFrameImageModule(
  vtkDICOMMetaData *meta, vtkInformation *info)
{
  // The BurnedInAnnotation attribute is mandatory
  std::string bia;
  if (this->MetaData)
    {
    bia = this->MetaData->GetAttributeValue(
      DC::BurnedInAnnotation).AsString();
    }
  if (bia != "YES")
    {
    bia = "NO";
    }
  meta->SetAttributeValue(DC::BurnedInAnnotation, bia);

  // These are mandatory, and must be set to these values
  if (meta->GetAttributeValue(DC::BitsStored).AsInt() != 1)
    {
    meta->SetAttributeValue(DC::PresentationLUTShape, "IDENTITY");
    meta->SetAttributeValue(DC::RescaleIntercept, 0.0);
    meta->SetAttributeValue(DC::RescaleSlope, 1.0);
    meta->SetAttributeValue(DC::RescaleType, "US");
    }

  // get dimensions of the data set: x,y,z,t,v
  int nframes = 1;
  int dims[5];
  double spacing[5];
  this->ComputeDimensions(info, &nframes, dims, spacing);

  // set multi-frame information
  meta->SetAttributeValue(DC::NumberOfFrames, nframes);

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
    meta->SetAttributeValue(
      DC::FrameTimeVector,
      vtkDICOMValue(vtkDICOMVR::DS, tvector, tvector+nframes));
    }
  if (dims[2] > 0)
    {
    pointers[npointers++] = DC::SliceLocationVector;
    meta->SetAttributeValue(DC::SliceLocationVector,
      vtkDICOMValue(vtkDICOMVR::DS, zvector, zvector+nframes));
    }

  meta->SetAttributeValue(
    DC::FrameIncrementPointer,
    vtkDICOMValue(vtkDICOMVR::AT, pointers, pointers+npointers));

  meta->RemoveAttribute(DC::PixelAspectRatio);
  meta->SetAttributeValue(
    DC::PixelSpacing,
    vtkDICOMValue(vtkDICOMVR::DS, spacing, spacing+2));

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

  return this->CopyOptionalAttributes(optional, meta);
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
bool vtkDICOMMRGenerator::GenerateMRMultiFrameInstance(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  const char *SOPClass = "1.2.840.10008.5.1.4.1.1.4.1";

  if (!this->GenerateSOPCommonModule(meta, SOPClass) ||
      !this->GenerateImagePixelModule(meta, info) ||
      !this->GenerateGeneralImageModule(meta) ||
      !this->GenerateGeneralSeriesModule(meta) ||
      !this->GenerateGeneralStudyModule(meta) ||
      !this->GeneratePatientModule(meta) ||
      !this->GenerateGeneralEquipmentModule(meta)
      // many more mandatory modules
      )
    {
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateMRInstance(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  const char *SOPClass = "1.2.840.10008.5.1.4.1.1.4";

  if (!this->GenerateSOPCommonModule(meta, SOPClass) ||
      !this->GenerateImagePixelModule(meta, info) ||
      !this->GenerateImagePlaneModule(meta, info) ||
      !this->GenerateGeneralImageModule(meta) ||
      !this->GenerateGeneralSeriesModule(meta) ||
      !this->GenerateGeneralStudyModule(meta) ||
      !this->GeneratePatientModule(meta) ||
      !this->GenerateMRImageModule(meta) ||
      !this->GenerateGeneralEquipmentModule(meta))
    {
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMMRGenerator::GenerateInstance(
  vtkInformation *info, vtkDICOMMetaData *meta)
{
  //if (this->MultiFrame == 0)
    {
    return this->GenerateMRInstance(info, meta);
    }

  //return this->GenerateMRMultiFrameInstance(info, meta);
}
