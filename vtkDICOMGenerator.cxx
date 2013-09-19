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

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkInformation.h"
#include "vtkMatrix4x4.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkDataSetAttributes.h"
#include "vtkSmartPointer.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>

#include <vector>

vtkCxxSetObjectMacro(vtkDICOMGenerator,PatientMatrix,vtkMatrix4x4);
vtkCxxSetObjectMacro(vtkDICOMGenerator,MetaData,vtkDICOMMetaData);

//----------------------------------------------------------------------------
vtkDICOMGenerator::vtkDICOMGenerator()
{
  this->MetaData = 0;
  this->MultiFrame = 0;
  this->TimeAsVector = 0;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->PatientMatrix = 0;
}

//----------------------------------------------------------------------------
vtkDICOMGenerator::~vtkDICOMGenerator()
{
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

  os << indent << "MetaData:" << (this->MetaData ? "\n" : " (none)\n");
  os << indent << "MultiFrame: "
     << (this->MultiFrame ? "On\n" : "Off\n");
  os << indent << "TimeAsVector: "
     << (this->TimeAsVector ? "On\n" : "Off\n");
  os << indent << "TimeDimension: " << this->TimeDimension << "\n";
  os << indent << "TimeSpacing: " << this->TimeSpacing << "\n";

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
void vtkDICOMGenerator::ComputePositionAndOrientation(
  const double origin[3], vtkMatrix4x4 *matrix,
  double position[3], double orientation[6])
{
  // find new offset by multiplying the origin by the matrix
  double offset[4];
  offset[0] = origin[0];
  offset[1] = origin[1];
  offset[2] = origin[2];
  offset[3] = 1.0;

  double mmat[16];
  if (matrix)
    {
    matrix->MultiplyPoint(offset, offset);
    vtkMatrix4x4::DeepCopy(mmat, matrix);
    }
  else
    {
    vtkMatrix4x4::Identity(mmat);
    }

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
  vtkInformation *info, int *nframes, int dims[5], double spacing[5])
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
    numComponents = 0;
    }

  dims[0] = extent[1] - extent[0] + 1;
  dims[1] = extent[3] - extent[2] + 1;
  dims[2] = numSlices;
  dims[3] = numTimeSlots;
  dims[4] = numComponents;

  // get the dimension spacing
  info->Get(vtkDataObject::SPACING(), spacing);
  spacing[3] = this->TimeSpacing;
  spacing[4] = 0.0;

  int n = (numSlices ? numSlices : 1);
  n *= (numTimeSlots ? numTimeSlots : 1);
  n *= (numComponents ? numComponents : 1);
  *nframes = n;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateSOPCommonModule(
  vtkDICOMMetaData *meta, const char *SOPClass)
{
  // set the SOP class, allow the compiler to set the SOPInstanceUID
  meta->SetAttributeValue(DC::SOPClassUID, SOPClass);

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::SpecificCharacterSet,  // 1C
    // DC::InstanceCreationDate,
    // DC::InstanceCreationTime,
    // DC::InstanceCreatorUID,
    DC::RelatedGeneralSOPClassUID, // set to original class if SC
    DC::OriginalSpecializedSOPClassUID, // set to original class if SC
    DC::CodingSchemeIdentificationSequence,
    // DC::TimezoneOffsetFromUTC,
    DC::ContributingEquipmentSequence,
    DC::InstanceNumber,  // will be re-written by General Image Module
    // DC::SOPInstanceStatus,        // caution
    // DC::SOPAuthorizationDateTime, // caution
    // DC::SOPAuthorizationComment,  // caution
    // DC::AuthorizationEquipmentCertificationNumber,  // caution
    DC::EncryptedAttributesSequence, // 1C
    DC::OriginalAttributesSequence,
    DC::HL7StructuredDocumentReferenceSequence, // 1C
    DC::LongitudinalTemporalInformationModified,
    DC::ItemDelimitationItem
  };

  if (this->MetaData)
    {
    for (int i = 0; optional[i] != DC::ItemDelimitationItem; i++)
      {
      meta->SetAttributeValue(optional[i],
        this->MetaData->GetAttributeValue(optional[i]));
      }
    }

  return true;
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

  for (int i = 0; required[i] != DC::ItemDelimitationItem; i++)
    {
    std::string val;
    if (this->MetaData)
      {
      val = this->MetaData->GetAttributeValue(required[i]).AsString();
      }
    meta->SetAttributeValue(required[i], val);
    }

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

  if (this->MetaData)
    {
    for (int i = 0; optional[i] != DC::ItemDelimitationItem; i++)
      {
      meta->SetAttributeValue(optional[i],
        this->MetaData->GetAttributeValue(optional[i]));
      }
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateGeneralStudyModule(vtkDICOMMetaData *meta)
{
  // The StudyUID is mandatory and must be present, its presence
  // is enforced in the vtkDICOMCompiler rather than here.

  // required items: use simple read/write validation
  static const DC::EnumType required[] = {
    DC::StudyDate,
    DC::StudyTime,
    DC::ReferringPhysicianName,
    DC::StudyID,
    DC::AccessionNumber,
    DC::ItemDelimitationItem
  };

  for (int i = 0; required[i] != DC::ItemDelimitationItem; i++)
    {
    std::string val;
    if (this->MetaData)
      {
      val = this->MetaData->GetAttributeValue(required[i]).AsString();
      }
    meta->SetAttributeValue(required[i], val);
    }

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

  if (this->MetaData)
    {
    for (int i = 0; optional[i] != DC::ItemDelimitationItem; i++)
      {
      meta->SetAttributeValue(optional[i],
        this->MetaData->GetAttributeValue(optional[i]));
      }
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateGeneralSeriesModule(vtkDICOMMetaData *meta)
{
  // The SeriesUID is mandatory and must be present, its presence
  // is enforced in the vtkDICOMCompiler rather than here.

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

  // required items: use simple read/write validation
  DC::EnumType required[] = {
    DC::SeriesNumber,
    DC::ItemDelimitationItem
  };

  for (int i = 0; required[i] != DC::ItemDelimitationItem; i++)
    {
    std::string val;
    if (this->MetaData)
      {
      val = meta->GetAttributeValue(required[i]).AsString();
      }
    meta->SetAttributeValue(required[i], val);
    }

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
    DC::SmallestPixelValueInSeries, // Needs re-writing from image data
    DC::LargestPixelValueInSeries,  // Needs re-writing from image data
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

  if (this->MetaData)
    {
    for (int i = 0; optional[i] != DC::ItemDelimitationItem; i++)
      {
      meta->SetAttributeValue(optional[i],
        this->MetaData->GetAttributeValue(optional[i]));
      }
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateMultiFrameModule(
  vtkDICOMMetaData *meta, vtkInformation *info)
{
  meta->SetAttributeValue(
    DC::NumberOfFrames, 1);
  meta->SetAttributeValue(
    DC::FrameIncrementPointer,
    vtkDICOMValue(vtkDICOMVR::AT, vtkDICOMTag(DC::FrameTime)));
  meta->SetAttributeValue(DC::FrameTime, this->TimeSpacing);

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateMultiFrameFunctionalGroupsModule(
  vtkDICOMMetaData *meta, vtkInformation *info)
{
  // InstanceNumber is mandatory
  meta->SetAttributeValue(DC::InstanceNumber, 1);

  // ContentDate and ContentTime are mandatory
  if (!meta->HasAttribute(DC::ContentTime) ||
      !meta->HasAttribute(DC::ContentDate))
    {
    char text[32];
    time_t t;
    time(&t);
    strftime(text, sizeof(text), "%Y%m%d%H%M%S", localtime(&t));
    text[8 + 6] = '\0';
    meta->SetAttributeValue(DC::ContentTime, &text[8]);
    text[8] = '\0';
    meta->SetAttributeValue(DC::ContentDate, &text[0]);
    }

  // NumberOfFrames is mandatory (obviously)
  // set it to the number of slices times the number of components
  // (consider each block of components that becomes an RGB pixel
  // as one components)

  // RepresentativeFrameNumber (optional)

  // ConatenationUID
  // SOPInstanceUIDOfConcatenationSource
  // InConcatenationNumber
  // InConcatenationTotalNumer (optional)

  // Items for Shared Functional Groups and Per-frame Functional Groups
  vtkDICOMItem sfgi;
  vtkDICOMItem pffgi;

  //-----
  // PixelMeasuresSequence is tied to PlanePosition and PlaneOrientation
  if (this->PatientMatrix)
    {
    // Get VTK image spacing
    double spacing[3];
    info->Get(vtkDataObject::SPACING(), spacing);

    // Use existing slice thickness if present
    double sliceThickness = 0.0;
    if (meta->HasAttribute(DC::SharedFunctionalGroupsSequence))
      {
      sliceThickness = meta->GetAttributeValue(
        vtkDICOMTagPath(DC::SharedFunctionalGroupsSequence, 0,
                        DC::PixelMeasuresSequence, 0,
                        DC::SliceThickness)).AsDouble();
      }
    else
      {
      sliceThickness = meta->GetAttributeValue(DC::SliceThickness).AsDouble();
      }
    // If no existing thickness, use slice spacing
    if (sliceThickness == 0)
      {
      sliceThickness = spacing[2];
      }

    vtkDICOMItem pmi;
    pmi.SetAttributeValue(
      DC::PixelSpacing,
      vtkDICOMValue(vtkDICOMVR::DS, spacing, spacing+2));
    pmi.SetAttributeValue(DC::SliceThickness, sliceThickness);
    vtkDICOMSequence pm(1);
    pm.SetItem(0, pmi);
    sfgi.SetAttributeValue(DC::PixelMeasuresSequence, pm);

    // Remove conflicting attributes, just in case
    meta->RemoveAttribute(DC::PixelAspectRatio);
    meta->RemoveAttribute(DC::PixelSpacing);
    meta->RemoveAttribute(DC::SliceThickness);
    meta->RemoveAttribute(DC::SpacingBetweenSlices);
    }

  //-----
  // FrameContentSequence, mandatory, always per-frame
  for (;;) // loop over frames
    {
    // optional:
    // DC::FrameAcquisitionNumber,
    // DC::FrameReferenceDateTime,   // 1C (mandatory for ORIGINAL)
    // DC::FrameAcquisitionDateTime, // 1C (ditto)
    // DC::FrameAcquisitionDuration, // 1C (ditto)
    // DC::CardiacCyclePosition,
    // DC::RespiratoryCyclePosition,
    // DC::DimensionIndexValues,  // 1C (mandatory if DimensionIndexSequence)
    // DC::TemporalPositionIndex, // 1C (mandatory for PET)
    // DC::StackID,               // 1C (mandatory for PET)
    // DC::InStackPositionNumber, // 1C (mandatory if StackID)
    // DC::FrameComments,
    // DC::FrameLabel,
    // DC::ItemDelimitationItem
    }

  //-----
  // PlanePositionPatientSequence, mandatory, usually per-frame
  for (;;) // loop over frames
    {
    // DC::ImagePositionPatient, // 1C, (mandatory for ORIGINAL)
    }

  //-----
  // PlaneOrientationPatientSequence, mandatory, usually shared
  if (0)
    {
    // DC::ImageOrientationPatient, // 1C, (mandatory for ORIGINAL)
    }

  //-----
  // ReferencedImageSequence, required
  if (0)
    {
    // DC::ReferencedFrameNumber,   // 1C (mandatory for per-frame references)
    // DC::ReferencedSegmentNumber, // 1C (mutually exclusive with above)
    // DC::PurposeOfReferenceCodeSequence, // 1
    }

  //-----
  // DerivationImageSequence, required
  if (0)
    {
    // DC::DerivationDescription,
    // DC::DerivationCodeSequence, // 1
    // DC::SourceImageSequence, // 2
    }

  //-----
  // CardiacSynchronizationSequence, mandatory
  if (0)
    {
    // DC::NominalPercentageOfCardiacPhase, // 1C
    // DC::NominalCardiacTriggeDelayTime, // 1
    // DC::ActualCardiacTriggerDelayTime, // 1C
    // DC::NominalCardiacTriggerTimePriorToRPeak,
    // DC::ActualCardiacTriggerTimePriorToRPeak,
    // DC::IntervalsAcquired,
    // DC::IntervalsRejected,
    // DC::HeartRate,
    // DC::RRIntervalTimeNominal, // 1C
    // DC::LowRRValue,
    // DC::HighRRValue,
    }

  //-----
  // FrameAnatomySequence, mandatory
  if (0)
    {
    // DC::FrameLaterality, // 1
    // DC::AnatomicRegionSequence, // 1
    }

  //-----
  // PixelValueTransformationSequence, mandatory
  if (0)
    {
    // DC::RescaleIntercept, // 1
    // DC::RescaleSlope, // 1
    // DC::RescaleType, // 1
    }

  //-----
  // FrameVOILUSequence, mandatory
  if (0)
    {
    // DC::WindowCenter, // 1C (manditory if no VOILUTSequence)
    // DC::WindowWidth, // 1C
    // DC::WindowCenterWidthExplanation,
    // DC::VOILUTFunction, // LINEAR or SIGMOID
    // DC::VOILUTSequence // 1C (mandatory no WindowCenter/Width)
    }

  //-----
  // RealWorldValueMappingSequence, mandatory
  if (0)
    {
    // DC::RealWorldValueMappingSequence, // 1
    // DC::RealWorldFirstValueMapped, // 1
    // DC::RealWorldLastValueMapped, // 1
    // DC::RealWorldValueIntercept, // 1C (mandatory if no LUT)
    // DC::RealWorldValueSlope, // 1C
    // DC::RealWorldValueLUTData, // 1C (mandatory if no Slope/Intercept)
    // DC::LUTExplanation, // 1
    // DC::LUTLabel, // 1
    // DC::MeasurementUnitsCodeSequence, // 1
    }

  //-----
  // ContrastBolusUsageSequence
  //-----
  // PixelintensityRelationshipLUTSequence
  //-----
  // FramePixelShiftSequence
  //-----
  // PatientOrientationInFrameSequence
  //-----
  // FrameDisplayShutterSequence
  //-----
  // RespiratorySynchronizationSequence
  //-----
  // IrradiationEventIdentificationSequence
  //-----
  // RadiopharmaceuticalUsageSequence
  //-----
  // PatientPhysiologicalStateSequence
  //-----
  // PlanePositionVolumeSequence
  //-----
  // PlaneOrientationVolumeSequence
  //-----
  // TemporalPositionSequence
  //-----
  // ImageDataTypeSequence
  if (0)
    {
    // DC::DataType, // 1 with ultrasound-specific values
    // DC::AliasedDataType, // 1 with values YES or NO
    }
  //-----
  // DimensionOrganizationSequence, mandatory
  if (0)
    {
    // DC::DimensionOrganizationUID
    }
  // DimensionOrganizationType
  // DimensionIndexSequence, mandatory
  if (0)
    {
    // DC::DimensionIndexPointer, // 1
    // DC::DimensionIndexPrivateCreator, // 1C
    // DC::FunctionalGroupPointer, // 1C
    // DC::FunctionalGroupPrivateCreator, // 1C
    // DC::DimensionOrganizationUID, // 1C
    // DC::DimensionDescriptionLabel,
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateGeneralImageModule(
  vtkDICOMMetaData *meta)
{
  // This module provides per-instance information
  if (1) //this->FileDimensionality == 2)
    {
    int nslices = meta->GetNumberOfInstances();
    for (int i = 0; i < nslices; i++)
      {
      unsigned int instance = i + 1;
      meta->SetAttributeValue(i, DC::InstanceNumber, instance);
      }
    }
  else
    {
    meta->SetAttributeValue(DC::InstanceNumber, 1);
    }

  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::PatientOrientation, // 2C, not set if Patient Matrix exists
    DC::ContentDate, // 2C, might be per-instance, up to the microsecond
    DC::ContentTime, // 2C, might be per-instance
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
    DC::IconImageSequence, // obviously must change if present
    DC::PresentationLUTShape,
    DC::IrradiationEventUID,
    DC::ItemDelimitationItem
  };

  if (this->MetaData)
    {
    for (int i = 0; optional[i] != DC::ItemDelimitationItem; i++)
      {
      meta->SetAttributeValue(optional[i],
        this->MetaData->GetAttributeValue(optional[i]));
      }
    }

  if (this->PatientMatrix)
    {
    meta->RemoveAttribute(DC::PatientOrientation);
    }
  else
    {
    // This is required on the condition that no matrix is provided
    if (!meta->HasAttribute(DC::PatientOrientation))
      {
      meta->SetAttributeValue(DC::PatientOrientation, "");
      }
    }

  // ContentDate is conditionally required, and we have no means to
  // check for the conditions under which it would not be required.
  if (!meta->HasAttribute(DC::ContentTime) ||
      !meta->HasAttribute(DC::ContentDate))
    {
    char text[32];
    time_t t;
    time(&t);
    strftime(text, sizeof(text), "%Y%m%d%H%M%S", localtime(&t));
    text[8 + 6] = '\0';
    meta->SetAttributeValue(DC::ContentTime, &text[8]);
    text[8] = '\0';
    meta->SetAttributeValue(DC::ContentDate, &text[0]);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMGenerator::GenerateImagePixelModule(
  vtkDICOMMetaData *meta, vtkInformation *info)
{
  // get the scalar information
  vtkInformation *scalarInfo = vtkDataObject::GetActiveFieldInformation(
    info, vtkDataObject::FIELD_ASSOCIATION_POINTS,
    vtkDataSetAttributes::SCALARS);

  int extent[6];
  info->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);

  double spacing[3];
  info->Get(vtkDataObject::SPACING(), spacing);

  int scalarType = scalarInfo->Get(vtkDataObject::FIELD_ARRAY_TYPE());
  int numComponents = scalarInfo->Get(
    vtkDataObject::FIELD_NUMBER_OF_COMPONENTS());

  int rows = extent[3] - extent[2] + 1;
  int cols = extent[1] - extent[0] + 1;

  // get the DICOM data type:
  short pixelbits = 0;
  short pixelrep = 0;

  switch (scalarType)
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
      vtkImageScalarTypeNameMacro(scalarType));
    return false;
    }

  if (rows > 65535 || cols > 65535)
    {
    vtkErrorMacro("Image dimensions " << rows << "x"
      << cols << " are too large for DICOM");
    return false;
    }

  bool paletteColor = false;
  if (numComponents >= 3 && scalarType == VTK_UNSIGNED_CHAR)
    {
    meta->SetAttributeValue(DC::SamplesPerPixel, 3);
    meta->SetAttributeValue(DC::PlanarConfiguration, 0);
    meta->SetAttributeValue(DC::PhotometricInterpretation, "RGB");
    }
  else
    {
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
  meta->SetAttributeValue(DC::BitsStored, pixelbits);
  meta->SetAttributeValue(DC::HighBit, pixelbits-1);
  meta->SetAttributeValue(DC::PixelRepresentation, pixelrep);

  // This will be removed when PixelSpacing is set
  int aspect[2];
  vtkDICOMGenerator::ComputeAspectRatio(spacing, aspect);
  meta->SetAttributeValue(
    DC::PixelAspectRatio,
    vtkDICOMValue(vtkDICOMVR::IS, aspect, aspect+2));

  // These can be easily added in the writer, but they are optional
  meta->RemoveAttribute(DC::SmallestImagePixelValue);
  meta->RemoveAttribute(DC::LargestImagePixelValue);

  return true;
}
