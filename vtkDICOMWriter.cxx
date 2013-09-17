/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMWriter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMCompiler.h"
#include "vtkDICOMSequence.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMTagPath.h"

#include "vtkObjectFactory.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkByteSwap.h"
#include "vtkMatrix4x4.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkCommand.h"
#include "vtkErrorCode.h"
#include "vtkSmartPointer.h"

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <vector>

vtkStandardNewMacro(vtkDICOMWriter);
vtkCxxSetObjectMacro(vtkDICOMWriter,PatientMatrix,vtkMatrix4x4);
vtkCxxSetObjectMacro(vtkDICOMWriter,MetaData,vtkDICOMMetaData);

//----------------------------------------------------------------------------
vtkDICOMWriter::vtkDICOMWriter()
{
  this->FileLowerLeft = 1;
  this->FileDimensionality = 2;
  this->MetaData = 0;
  this->TimeAsVector = 0;
  this->TimeDimension = 0;
  this->TimeSpacing = 1.0;
  this->PatientMatrix = 0;
  this->MemoryRowOrder = vtkDICOMWriter::BottomUp;
  this->SeriesDescription = 0;
}

//----------------------------------------------------------------------------
vtkDICOMWriter::~vtkDICOMWriter()
{
  if (this->PatientMatrix)
    {
    this->PatientMatrix->Delete();
    }
  if (this->MetaData)
    {
    this->MetaData->Delete();
    }
  delete [] this->SeriesDescription;
}

//----------------------------------------------------------------------------
vtkDICOMMetaData *vtkDICOMWriter::GetMetaData()
{
  return this->MetaData;
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "Description: " << this->SeriesDescription << "\n";
  os << indent << "MetaData:" << (this->MetaData ? "\n" : " (none)\n");
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

  os << indent << "MemoryRowOrder: "
     << this->GetMemoryRowOrderAsString() << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::SetMemoryRowOrder(int order)
{
  if (order >= 0 && order <= vtkDICOMWriter::BottomUp)
    {
    if (order != this->MemoryRowOrder)
      {
      this->MemoryRowOrder = order;
      this->Modified();
      }
    }
}

//----------------------------------------------------------------------------
const char *vtkDICOMWriter::GetMemoryRowOrderAsString()
{
  const char *text = "";
  switch (this->MemoryRowOrder)
    {
    case vtkDICOMWriter::FileNative:
      text = "FileNative";
      break;
    case vtkDICOMWriter::TopDown:
      text = "TopDown";
      break;
    case vtkDICOMWriter::BottomUp:
      text = "BottomUp";
      break;
    }

  return text;
}

//----------------------------------------------------------------------------
void vtkDICOMWriter::ComputeAspectRatio(
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
bool vtkDICOMWriter::ValidateSOPCommonModule(vtkDICOMMetaData *meta)
{
  // force the SOP class to "Secondary Capture",
  // allow the compiler to set the SOPInstanceUID
  meta->SetAttributeValue(DC::SOPClassUID, "1.2.840.10008.5.1.4.1.1.7");

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
bool vtkDICOMWriter::ValidatePatientModule(vtkDICOMMetaData *meta)
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
bool vtkDICOMWriter::ValidateGeneralStudyModule(vtkDICOMMetaData *meta)
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
bool vtkDICOMWriter::ValidateGeneralSeriesModule(vtkDICOMMetaData *meta)
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

  // set the series description from the member variable
  if (this->SeriesDescription && this->SeriesDescription[0] != '\0')
    {
    char sd[65];
    strncpy(sd, this->SeriesDescription, 64);
    sd[64] = '\0';
    meta->SetAttributeValue(DC::SeriesDescription, sd);
    meta->RemoveAttribute(DC::SeriesDescriptionCodeSequence);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMWriter::ValidateSCImageModule(vtkDICOMMetaData *meta)
{
  // optional and conditional: direct copy of values with no checks
  static const DC::EnumType optional[] = {
    DC::DateOfSecondaryCapture,
    DC::TimeOfSecondaryCapture,
    DC::NominalScannedPixelSpacing,
    DC::DocumentClassCodeSequence,
    // DC::PixelSpacing, // 1C (use aspect ratio instead)
    // DC::PixelSpacingCalibrationType,
    // DC::PixelSpacingCalibrationDescription, // 1C
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
bool vtkDICOMWriter::ValidateSCEquipmentModule(vtkDICOMMetaData *meta)
{
  // ConversionType is a mandatory attribute
  std::string ct;
  if (this->MetaData)
    {
    ct = this->MetaData->GetAttributeValue(DC::ConversionType).AsString();
    }
  if (ct == "")
    {
    ct = "WSD"; // workstation
    }
  meta->SetAttributeValue(DC::ConversionType, ct);

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

  if (this->MetaData)
    {
    for (int i = 0; optional[i] != DC::ItemDelimitationItem; i++)
      {
      meta->SetAttributeValue(optional[i],
        this->MetaData->GetAttributeValue(optional[i]));
      }
    }

  // Modality is optional for Secondary Capture
  std::string m = meta->GetAttributeValue(DC::Modality).AsString();
  if (m == "" || m == "OT")
    {
    meta->RemoveAttribute(DC::Modality);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMWriter::ValidateMultiFrameFunctionalGroupsModule(
  vtkDICOMMetaData *meta, vtkInformation *info)
{
  // Items for Shared Functional Groups and Per-frame Functional Groups
  vtkDICOMItem sfgi;
  vtkDICOMItem pffgi;

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

    // Remove conflicting attributes
    meta->RemoveAttribute(DC::PixelAspectRatio);
    meta->RemoveAttribute(DC::PixelSpacing);
    meta->RemoveAttribute(DC::SliceThickness);
    meta->RemoveAttribute(DC::SpacingBetweenSlices);
    }

  return true;
}

//----------------------------------------------------------------------------
bool vtkDICOMWriter::ValidateGeneralImageModule(
  vtkDICOMMetaData *meta)
{
  // This module provides per-instance information
  if (this->FileDimensionality == 2)
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
bool vtkDICOMWriter::ValidateImagePixelModule(
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
    meta->RemoveAttribute(DC::SamplesPerPixel);
    meta->RemoveAttribute(DC::PlanarConfiguration);
    std::string pm = meta->GetAttributeValue(
      DC::PhotometricInterpretation).AsString();
    if (pm == "PALETTE COLOR" &&
        meta->HasAttribute(DC::RedPaletteColorLookupTableData))
      {
      paletteColor = true;
      }
    else if (pm != "MONOCHROME1")
      {
      pm = "MONOCHROME2";
      }
    meta->SetAttributeValue(DC::PhotometricInterpretation, pm);
    }

  // Remove unless "PALETTE COLOR"
  if (!paletteColor)
    {
    meta->RemoveAttribute(DC::RedPaletteColorLookupTableDescriptor);
    meta->RemoveAttribute(DC::GreenPaletteColorLookupTableDescriptor);
    meta->RemoveAttribute(DC::BluePaletteColorLookupTableDescriptor);
    meta->RemoveAttribute(DC::RedPaletteColorLookupTableData);
    meta->RemoveAttribute(DC::GreenPaletteColorLookupTableData);
    meta->RemoveAttribute(DC::BluePaletteColorLookupTableData);
    }

  meta->SetAttributeValue(DC::Rows, rows);
  meta->SetAttributeValue(DC::Columns, cols);
  meta->SetAttributeValue(DC::BitsAllocated, pixelbits);
  meta->SetAttributeValue(DC::BitsStored, pixelbits);
  meta->SetAttributeValue(DC::HighBit, pixelbits-1);
  meta->SetAttributeValue(DC::PixelRepresentation, pixelrep);

  // This will be removed when PixelSpacing is set
  int aspect[2];
  vtkDICOMWriter::ComputeAspectRatio(spacing, aspect);
  meta->SetAttributeValue(
    DC::PixelAspectRatio,
    vtkDICOMValue(vtkDICOMVR::IS, aspect, aspect+2));

  // These can be easily added, but they are optional
  meta->RemoveAttribute(DC::SmallestImagePixelValue);
  meta->RemoveAttribute(DC::LargestImagePixelValue);

  return true;
}

//----------------------------------------------------------------------------

namespace {

void vtkDICOMWriterMatrix(
  double mmat[16], vtkMatrix4x4 *matrix, const double origin[3])
{
  // find new offset by multiplying the origin by the matrix
  double offset[4];
  offset[0] = origin[0];
  offset[1] = origin[1];
  offset[2] = origin[2];
  offset[3] = 1.0;

  if (matrix)
    {
    matrix->MultiplyPoint(offset, offset);
    vtkMatrix4x4::DeepCopy(mmat, matrix);
    }
  else
    {
    vtkMatrix4x4::Identity(mmat);
    }

  mmat[3] = offset[0];
  mmat[7] = offset[1];
  mmat[11] = offset[2];
}

} // end anonymous namespace

//----------------------------------------------------------------------------
void vtkDICOMWriter::ComputeInternalFileName(int slice)
{
  size_t n = 0;

  if (this->FileName)
    {
    n = strlen(this->FileName) + 1;
    }
  else if (this->FilePrefix)
    {
    n = strlen(this->FilePrefix) + strlen(this->FilePattern) + 10;
    }
  else
    {
    n = strlen(this->FilePattern) + 10;
    }

  if (this->InternalFileName == 0 ||
      strlen(this->InternalFileName) + 10 < n)
    {
    delete [] this->InternalFileName;
    this->InternalFileName = new char[n + 11];
    }

  if (this->FileName)
    {
    sprintf(this->InternalFileName, "%s", this->FileName);
    }
  else if (this->FilePrefix)
    {
    sprintf(this->InternalFileName,
            this->FilePattern, this->FilePrefix, slice);
    }
  else
    {
    sprintf(this->InternalFileName, this->FilePattern, slice);
    }
}

//----------------------------------------------------------------------------
int vtkDICOMWriter::RequestData(
  vtkInformation* vtkNotUsed(request),
  vtkInformationVector** inputVector,
  vtkInformationVector* vtkNotUsed(outputVector))
{
  this->SetErrorCode(vtkErrorCode::NoError);

  vtkInformation *info = inputVector[0]->GetInformationObject(0);
  vtkImageData *data =
    vtkImageData::SafeDownCast(info->Get(vtkDataObject::DATA_OBJECT()));

  if (data == NULL)
    {
    vtkErrorMacro("No input provided!");
    return 0;
    }

  if (!this->FileName && !this->FilePattern)
    {
    vtkErrorMacro("Write:Please specify either a FileName "
                  "or a file prefix and pattern");
    this->SetErrorCode(vtkErrorCode::NoFileNameError);
    return 0;
    }

  int extent[6];
  info->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
  int numFiles = extent[5] - extent[4] + 1;
  int numFrames = 1;

  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  meta->SetNumberOfInstances(numFiles);

  // perform some basic validation
  if (!this->ValidateSOPCommonModule(meta) ||
      !this->ValidateImagePixelModule(meta, info) ||
      !this->ValidateGeneralImageModule(meta) ||
      !this->ValidateGeneralSeriesModule(meta) ||
      !this->ValidateGeneralStudyModule(meta) ||
      !this->ValidatePatientModule(meta) ||
      !this->ValidateSCImageModule(meta) ||
      !this->ValidateSCEquipmentModule(meta))
    {
    // refuse to write an invalid file
    return 0;
    }

  if (this->PatientMatrix)
    {
    // origin must be incorporated into the PatientMatrix
    double origin[3];
    data->GetOrigin(origin);
    double mat16[16];
    vtkDICOMWriterMatrix(mat16, this->PatientMatrix, origin);
    // do the image plane module
    }

  // add an empty PixelData to be filled in by the compiler
  unsigned short empty[1] = {};
  meta->SetAttributeValue(
    DC::PixelData, vtkDICOMValue(vtkDICOMVR::OW, empty, empty));

  vtkSmartPointer<vtkDICOMCompiler> compiler =
    vtkSmartPointer<vtkDICOMCompiler>::New();
  compiler->SetMetaData(meta);

  // write the image
  char *dataPtr = static_cast<char *>(data->GetScalarPointer());

  int planarConfiguration =
    meta->GetAttributeValue(DC::PlanarConfiguration).AsInt();
  int samplesPerPixel =
    meta->GetAttributeValue(DC::SamplesPerPixel).AsInt();
  samplesPerPixel = (samplesPerPixel > 0 ? samplesPerPixel : 1);

  int numFileComponents = (planarConfiguration ? 1 : samplesPerPixel);
  int numPlanes = (planarConfiguration ? samplesPerPixel : 1);
  int scalarSize = data->GetScalarSize();
  int numComponents = data->GetNumberOfScalarComponents();
  samplesPerPixel = numComponents;

  vtkIdType pixelSize = numComponents*scalarSize;
  vtkIdType rowSize = pixelSize*(extent[1] - extent[0] + 1);
  vtkIdType sliceSize = rowSize*(extent[3] - extent[2] + 1);
  vtkIdType filePixelSize = numFileComponents*scalarSize;
  vtkIdType fileRowSize = filePixelSize*(extent[1] - extent[0] + 1);
  vtkIdType filePlaneSize = fileRowSize*(extent[3] - extent[2] + 1);
  vtkIdType fileFrameSize = filePlaneSize*numPlanes;

  this->InvokeEvent(vtkCommand::StartEvent);
  this->UpdateProgress(0.0);

  bool flipImage = (this->MemoryRowOrder == vtkDICOMWriter::BottomUp);
  bool packedToPlanar = (filePixelSize != pixelSize);
  char *rowBuffer = 0;
  if (flipImage)
    {
    rowBuffer = new char[fileRowSize];
    }
  char *frameBuffer = 0;
  if (flipImage || packedToPlanar)
    {
    frameBuffer = new char[fileFrameSize];
    }

  // loop through all files in the update extent
  for (int fileIdx = 0; fileIdx < numFiles; fileIdx++)
    {
    // get the index for this file
    int idx = (flipImage ? numFiles - fileIdx - 1 : fileIdx);
    this->ComputeInternalFileName(fileIdx + 1);
    compiler->SetFileName(this->InternalFileName);
    compiler->SetIndex(fileIdx);
    compiler->WriteHeader();

    // iterate through all frames in the file
    for (int frameIdx = 0; frameIdx < numFrames; frameIdx++)
      {
      if (this->AbortExecute) { break; }

      this->UpdateProgress(static_cast<double>(fileIdx*numFrames + frameIdx)/
                           static_cast<double>(numFiles*numFrames));

      int sIdx = (flipImage ? numFrames - frameIdx - 1 : frameIdx);
      // get the slice and component for this frame
      int sliceIdx = idx*numFrames + sIdx;
      int componentIdx = 0;

      // pointer to the frame that will be written to the file
      char *framePtr = frameBuffer;

      if (!framePtr)
        {
        // write the frame directly from image data
        framePtr = (dataPtr + (sliceIdx - extent[4])*sliceSize);
        }

      // go to the correct position in image data
      char *slicePtr = (dataPtr +
                        (sliceIdx - extent[4])*sliceSize +
                        componentIdx*samplesPerPixel);

      // iterate through all color planes in the slice
      char *planePtr = framePtr;
      for (int pIdx = 0; pIdx < numPlanes; pIdx++)
        {
        // convert scalar components to planes
        if (packedToPlanar)
          {
          const char *tmpInPtr = slicePtr;
          char *tmpOutPtr = planePtr;
          int m = sliceSize/pixelSize;
          for (int i = 0; i < m; i++)
            {
            vtkIdType n = filePixelSize;
            do { *tmpOutPtr++ = *tmpInPtr++; } while (--n);
            tmpInPtr += pixelSize - filePixelSize;
            }
          slicePtr += filePixelSize;
          }
        else
          {
          memcpy(framePtr, slicePtr, fileFrameSize);
          }

        // flip the data if necessary
        if (flipImage)
          {
          int numRows = extent[3] - extent[2] + 1;
          int halfRows = numRows/2;
          for (int yIdx = 0; yIdx < halfRows; yIdx++)
            {
            char *row1 = planePtr + yIdx*fileRowSize;
            char *row2 = planePtr + (numRows-yIdx-1)*fileRowSize;
            memcpy(rowBuffer, row1, fileRowSize);
            memcpy(row1, row2, fileRowSize);
            memcpy(row2, rowBuffer, fileRowSize);
            }
          }

        planePtr += filePlaneSize;
        }
      // write the frame to the file
      compiler->WriteFrame(framePtr, fileFrameSize);
      }
    compiler->Close();
    }

  delete [] rowBuffer;
  delete [] frameBuffer;

  this->UpdateProgress(1.0);
  this->InvokeEvent(vtkCommand::EndEvent);

  return 1;
}
