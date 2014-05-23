/*=========================================================================
This is an automatically generated file.  Include errata for any changes.
=========================================================================*/

#include "vtkDICOMDictionary.h"
#include "vtkDICOMDictHash.h"

namespace {

typedef vtkDICOMVR VR;
typedef vtkDICOMVM VM;
typedef vtkDICOMDictEntry::Entry DictEntry;

DictEntry DictEmptyRow[] = {
{ 0, 0, 0, 0, 0, NULL }
};

DictEntry DictRow0000[] = {
{ 0x0002, 0x0002, 0, VR::UI, VM::M1, "MediaStorageSOPClassUID" },
{ 0x0008, 0x0008, 0, VR::CS, VM::M2TN, "ImageType" },
{ 0x0008, 0x1049, 0, VR::SQ, VM::M1, "PhysiciansOfRecordIdentificationSequence" },
{ 0x0010, 0x0010, 0, VR::PN, VM::M1, "PatientName" },
{ 0x0018, 0x9251, 0, VR::SQ, VM::M1, "MRArterialSpinLabelingSequence" },
{ 0x0020, 0x0020, 0, VR::CS, VM::M2, "PatientOrientation" },
{ 0x0022, 0x0022, 0, VR::SQ, VM::M1, "RightImageSequence" },
{ 0x0024, 0x0024, 0, VR::SQ, VM::M1, "BackgroundIlluminationColorCodeSequence" },
{ 0x0032, 0x0032, 1, VR::DA, VM::M1, "StudyVerifiedDate" },
{ 0x0040, 0x1001, 0, VR::SH, VM::M1, "RequestedProcedureID" },
{ 0x0046, 0x0046, 0, VR::FD, VM::M1, "CornealSize" },
{ 0x0072, 0x0072, 0, VR::DS, VM::M1TN, "SelectorDSValue" },
{ 0x0400, 0x0010, 0, VR::UI, VM::M1, "MACCalculationTransferSyntaxUID" },
{ 0x2020, 0x00A2, 0, VR::CS, VM::M1, "DecimateCropResult" },
{ 0x4000, 0x4000, 1, VR::LT, VM::M1, "TextComments" },
{ 0x4008, 0x010C, 1, VR::PN, VM::M1, "InterpretationAuthor" },
{ 0xFFFA, 0xFFFA, 0, VR::SQ, VM::M1, "DigitalSignaturesSequence" },
{ 0xFFFC, 0xFFFC, 0, VR::OB, VM::M1, "DataSetTrailingPadding" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0001[] = {
{ 0x0002, 0x0003, 0, VR::UI, VM::M1, "MediaStorageSOPInstanceUID" },
{ 0x0008, 0x1048, 0, VR::PN, VM::M1TN, "PhysiciansOfRecord" },
{ 0x0010, 0x1050, 1, VR::LO, VM::M1TN, "InsurancePlanIdentification" },
{ 0x0018, 0x9250, 0, VR::CS, VM::M1, "ArterialSpinLabelingContrast" },
{ 0x0022, 0x1472, 0, VR::SQ, VM::M1, "RelevantOPTAttributesSequence" },
{ 0x0024, 0x0025, 0, VR::FL, VM::M1, "StimulusArea" },
{ 0x0032, 0x0033, 1, VR::TM, VM::M1, "StudyVerifiedTime" },
{ 0x0074, 0x1034, 0, VR::CS, VM::M1, "DoubleExposureFlag" },
{ 0x0400, 0x0401, 0, VR::SQ, VM::M1, "DigitalSignaturePurposeCodeSequence" },
{ 0x3006, 0x00C4, 1, VR::CS, VM::M1, "FrameOfReferenceTransformationType" },
{ 0x300A, 0x00C8, 0, VR::IS, VM::M1, "ReferenceImageNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0002[] = {
{ 0x0002, 0x0000, 0, VR::UL, VM::M1, "FileMetaInformationGroupLength" },
{ 0x0012, 0x0010, 0, VR::LO, VM::M1, "ClinicalTrialSponsorName" },
{ 0x0018, 0x9253, 0, VR::US, VM::M1, "ASLSlabNumber" },
{ 0x0020, 0x0022, 1, VR::IS, VM::M1, "OverlayNumber" },
{ 0x0022, 0x0020, 0, VR::SQ, VM::M1, "StereoPairsSequence" },
{ 0x0040, 0x1003, 0, VR::SH, VM::M1, "RequestedProcedurePriority" },
{ 0x0046, 0x0044, 0, VR::FD, VM::M1, "PupilSize" },
{ 0x0072, 0x0070, 0, VR::UT, VM::M1, "SelectorUTValue" },
{ 0x0400, 0x0402, 0, VR::SQ, VM::M1, "ReferencedDigitalSignatureSequence" },
{ 0x2020, 0x00A0, 0, VR::CS, VM::M1, "RequestedImageSizeFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0003[] = {
{ 0x0002, 0x0001, 0, VR::OB, VM::M1, "FileMetaInformationVersion" },
{ 0x0018, 0x9252, 0, VR::LO, VM::M1, "ASLTechniqueDescription" },
{ 0x0022, 0x0021, 0, VR::SQ, VM::M1, "LeftImageSequence" },
{ 0x0022, 0x1470, 0, VR::SQ, VM::M1, "OphthalmicThicknessMapQualityRatingSequence" },
{ 0x0032, 0x1070, 0, VR::LO, VM::M1, "RequestedContrastAgent" },
{ 0x0040, 0x1002, 0, VR::LO, VM::M1, "ReasonForTheRequestedProcedure" },
{ 0x0074, 0x1036, 0, VR::CS, VM::M1, "DoubleExposureOrdering" },
{ 0x0400, 0x0403, 0, VR::SQ, VM::M1, "ReferencedSOPInstanceMACSequence" },
{ 0x3006, 0x00C6, 0, VR::DS, VM::M16, "FrameOfReferenceTransformationMatrix" },
{ 0x300A, 0x00CA, 0, VR::SQ, VM::M1, "PlannedVerificationImageSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0004[] = {
{ 0x0018, 0x9255, 0, VR::FD, VM::M3, "ASLSlabOrientation" },
{ 0x0020, 0x0024, 1, VR::IS, VM::M1, "CurveNumber" },
{ 0x0024, 0x0020, 0, VR::FL, VM::M1, "BackgroundLuminance" },
{ 0x0040, 0x1005, 0, VR::LO, VM::M1, "RequestedProcedureLocation" },
{ 0x0046, 0x0042, 0, VR::FD, VM::M1, "ChannelWidth" },
{ 0x0054, 0x0050, 0, VR::US, VM::M1TN, "RotationVector" },
{ 0x0054, 0x1401, 1, VR::CS, VM::M1, "DeadTimeCorrectionFlag" },
{ 0x0072, 0x0076, 0, VR::FL, VM::M1TN, "SelectorFLValue" },
{ 0x0400, 0x0404, 0, VR::OB, VM::M1, "MAC" },
{ 0x4008, 0x0108, 1, VR::DA, VM::M1, "InterpretationTranscriptionDate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0005[] = {
{ 0x0018, 0x9254, 0, VR::FD, VM::M1, "ASLSlabThickness" },
{ 0x0022, 0x1066, 0, VR::LO, VM::M1, "VitreousStatusDescription" },
{ 0x0024, 0x0021, 0, VR::SQ, VM::M1, "StimulusColorCodeSequence" },
{ 0x0040, 0x1004, 0, VR::LO, VM::M1, "PatientTransportArrangements" },
{ 0x0054, 0x0051, 0, VR::US, VM::M1, "NumberOfRotations" },
{ 0x0054, 0x1400, 1, VR::CS, VM::M1TN, "CountsIncluded" },
{ 0x0074, 0x1030, 0, VR::SQ, VM::M1, "DeliveryVerificationImageSequence" },
{ 0x0400, 0x0015, 0, VR::CS, VM::M1, "MACAlgorithm" },
{ 0x3006, 0x00C0, 1, VR::SQ, VM::M1, "FrameOfReferenceRelationshipSequence" },
{ 0x300A, 0x00CC, 0, VR::LO, VM::M1TN, "ImagingDeviceSpecificAcquisitionParameters" },
{ 0x4008, 0x0109, 1, VR::TM, VM::M1, "InterpretationTranscriptionTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0006[] = {
{ 0x0018, 0x9257, 0, VR::CS, VM::M1, "ASLContext" },
{ 0x0020, 0x0026, 1, VR::IS, VM::M1, "LUTNumber" },
{ 0x0022, 0x1065, 0, VR::LO, VM::M1, "LensStatusDescription" },
{ 0x0032, 0x0034, 1, VR::DA, VM::M1, "StudyReadDate" },
{ 0x0040, 0x1007, 1, VR::SH, VM::M1, "FillerOrderNumberProcedure" },
{ 0x0046, 0x0040, 0, VR::FD, VM::M1, "OpticalTransmittance" },
{ 0x0054, 0x0052, 0, VR::SQ, VM::M1, "RotationInformationSequence" },
{ 0x0072, 0x0074, 0, VR::FD, VM::M1TN, "SelectorFDValue" },
{ 0x0076, 0x0070, 0, VR::US, VM::M1, "Component1ReferencedID" },
{ 0x4008, 0x010A, 1, VR::PN, VM::M1, "InterpretationTranscriber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0007[] = {
{ 0x0018, 0x9256, 0, VR::FD, VM::M3, "ASLMidSlabPosition" },
{ 0x0032, 0x0035, 1, VR::TM, VM::M1, "StudyReadTime" },
{ 0x0040, 0x1006, 1, VR::SH, VM::M1, "PlacerOrderNumberProcedure" },
{ 0x0054, 0x0053, 0, VR::US, VM::M1, "NumberOfFramesInRotation" },
{ 0x0074, 0x1032, 0, VR::CS, VM::M1, "VerificationImageTiming" },
{ 0x3006, 0x00C2, 1, VR::UI, VM::M1, "RelatedFrameOfReferenceUID" },
{ 0x300A, 0x00CE, 0, VR::CS, VM::M1, "TreatmentDeliveryType" },
{ 0x4008, 0x010B, 1, VR::ST, VM::M1, "InterpretationText" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0008[] = {
{ 0x0018, 0x0010, 0, VR::LO, VM::M1, "ContrastBolusAgent" },
{ 0x0018, 0x9259, 0, VR::CS, VM::M1, "ASLCrusherFlag" },
{ 0x0038, 0x0030, 1, VR::DA, VM::M1, "DischargeDate" },
{ 0x0040, 0x1009, 0, VR::SH, VM::M1, "ReportingPriority" },
{ 0x0072, 0x007A, 0, VR::US, VM::M1TN, "SelectorUSValue" },
{ 0x0078, 0x0070, 0, VR::SQ, VM::M1, "ImplantTemplateGroupMemberMatching2DCoordinatesSequence" },
{ 0x4008, 0x4000, 1, VR::ST, VM::M1, "ResultsComments" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0009[] = {
{ 0x0008, 0x0001, 1, VR::UL, VM::M1, "LengthToEnd" },
{ 0x0008, 0x1040, 0, VR::LO, VM::M1, "InstitutionalDepartmentName" },
{ 0x0018, 0x1050, 0, VR::DS, VM::M1, "SpatialResolution" },
{ 0x0018, 0x9258, 0, VR::UL, VM::M1, "ASLPulseTrainDuration" },
{ 0x0040, 0x1008, 0, VR::LO, VM::M1, "ConfidentialityCode" },
{ 0x300A, 0x00C0, 0, VR::IS, VM::M1, "BeamNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0010[] = {
{ 0x0018, 0x0012, 0, VR::SQ, VM::M1, "ContrastBolusAgentSequence" },
{ 0x0018, 0x925B, 0, VR::LO, VM::M1, "ASLCrusherDescription" },
{ 0x0038, 0x0032, 1, VR::TM, VM::M1, "DischargeTime" },
{ 0x0072, 0x0078, 0, VR::UL, VM::M1TN, "SelectorULValue" },
{ 0x300A, 0x00C3, 0, VR::ST, VM::M1, "BeamDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0011[] = {
{ 0x0018, 0x925A, 0, VR::FD, VM::M1, "ASLCrusherFlowLimit" },
{ 0x0040, 0x100A, 0, VR::SQ, VM::M1, "ReasonForRequestedProcedureCodeSequence" },
{ 0x3008, 0x00C0, 0, VR::SQ, VM::M1, "RecordedCompensatorSequence" },
{ 0x300A, 0x00C2, 0, VR::LO, VM::M1, "BeamName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0012[] = {
{ 0x0018, 0x0014, 0, VR::SQ, VM::M1, "ContrastBolusAdministrationRouteSequence" },
{ 0x0018, 0x925D, 0, VR::SQ, VM::M1, "ASLBolusCutoffTimingSequence" },
{ 0x0024, 0x0028, 0, VR::FL, VM::M1, "StimulusPresentationTime" },
{ 0x0072, 0x007E, 0, VR::SS, VM::M1TN, "SelectorSSValue" },
{ 0x4008, 0x0100, 1, VR::DA, VM::M1, "InterpretationRecordedDate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0013[] = {
{ 0x0008, 0x0005, 0, VR::CS, VM::M1TN, "SpecificCharacterSet" },
{ 0x0018, 0x0015, 0, VR::CS, VM::M1, "BodyPartExamined" },
{ 0x0018, 0x925C, 0, VR::CS, VM::M1, "ASLBolusCutoffFlag" },
{ 0x0074, 0x1038, 1, VR::DS, VM::M1, "DoubleExposureMetersetTrial" },
{ 0x3006, 0x00C8, 0, VR::LO, VM::M1, "FrameOfReferenceTransformationComment" },
{ 0x300A, 0x00C4, 0, VR::CS, VM::M1, "BeamType" },
{ 0x4008, 0x0101, 1, VR::TM, VM::M1, "InterpretationRecordedTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0014[] = {
{ 0x0008, 0x0006, 0, VR::SQ, VM::M1, "LanguageCodeSequence" },
{ 0x0018, 0x925F, 0, VR::UL, VM::M1, "ASLBolusCutoffDelayTime" },
{ 0x0068, 0x65F0, 0, VR::FD, VM::M4, "TwoDPlaneIntersection" },
{ 0x0072, 0x007C, 0, VR::SL, VM::M1TN, "SelectorSLValue" },
{ 0x300A, 0x00C7, 0, VR::CS, VM::M1, "HighDoseTechniqueType" },
{ 0x4008, 0x0102, 1, VR::PN, VM::M1, "InterpretationRecorder" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0015[] = {
{ 0x0018, 0x925E, 0, VR::LO, VM::M1, "ASLBolusCutoffTechnique" },
{ 0x0074, 0x103A, 1, VR::DS, VM::M4, "DoubleExposureFieldDeltaTrial" },
{ 0x300A, 0x00C6, 0, VR::CS, VM::M1, "RadiationType" },
{ 0x300C, 0x00C0, 0, VR::IS, VM::M1, "ReferencedWedgeNumber" },
{ 0x4008, 0x0103, 1, VR::LO, VM::M1, "ReferenceToRecordedSound" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0016[] = {
{ 0x0002, 0x0012, 0, VR::UI, VM::M1, "ImplementationClassUID" },
{ 0x0008, 0x0018, 0, VR::UI, VM::M1, "SOPInstanceUID" },
{ 0x0018, 0x1049, 0, VR::DS, VM::M1, "ContrastBolusIngredientConcentration" },
{ 0x0018, 0x9241, 0, VR::US, VM::M1, "GradientEchoTrainLength" },
{ 0x0020, 0x0030, 1, VR::DS, VM::M3, "ImagePosition" },
{ 0x0022, 0x0032, 0, VR::FL, VM::M2T2N, "ReferenceCoordinates" },
{ 0x0022, 0x1463, 0, VR::FL, VM::M2, "AnatomicStructureReferencePoint" },
{ 0x0024, 0x0034, 0, VR::SQ, VM::M1, "VisualFieldCatchTrialSequence" },
{ 0x0028, 0x0818, 1, VR::AT, VM::M1TN, "ImageDataLocation" },
{ 0x0040, 0x0440, 0, VR::SQ, VM::M1, "ProtocolContextSequence" },
{ 0x0040, 0x1011, 0, VR::SQ, VM::M1, "IntendedRecipientsOfResultsIdentificationSequence" },
{ 0x0070, 0x0060, 0, VR::SQ, VM::M1, "GraphicLayerSequence" },
{ 0x0072, 0x0062, 0, VR::CS, VM::M1TN, "SelectorCSValue" },
{ 0x0074, 0x1025, 0, VR::CS, VM::M1, "AutosequenceFlag" },
{ 0x300A, 0x00D9, 0, VR::FL, VM::M1, "IsocenterToWedgeTrayDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0017[] = {
{ 0x0002, 0x0013, 0, VR::SH, VM::M1, "ImplementationVersionName" },
{ 0x0010, 0x1040, 0, VR::LO, VM::M1, "PatientAddress" },
{ 0x0018, 0x1048, 0, VR::CS, VM::M1, "ContrastBolusIngredient" },
{ 0x0018, 0x9240, 0, VR::US, VM::M1, "RFEchoTrainLength" },
{ 0x0020, 0x1070, 1, VR::IS, VM::M1TN, "OtherStudyNumbers" },
{ 0x0024, 0x0035, 0, VR::US, VM::M1, "FixationCheckedQuantity" },
{ 0x0040, 0x0441, 0, VR::SQ, VM::M1, "ContentItemModifierSequence" },
{ 0x0040, 0x1010, 0, VR::PN, VM::M1TN, "NamesOfIntendedRecipientsOfResults" },
{ 0x0040, 0x1400, 0, VR::LT, VM::M1, "RequestedProcedureComments" },
{ 0x0054, 0x1004, 0, VR::CS, VM::M1, "ReprojectionMethod" },
{ 0x0074, 0x1024, 1, VR::IS, VM::M1, "BeamOrderIndexTrial" },
{ 0x300A, 0x00D8, 0, VR::DS, VM::M1, "WedgeOrientation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0018[] = {
{ 0x0002, 0x0010, 0, VR::UI, VM::M1, "TransferSyntaxUID" },
{ 0x0008, 0x001A, 0, VR::UI, VM::M1TN, "RelatedGeneralSOPClassUID" },
{ 0x0020, 0x0032, 0, VR::DS, VM::M3, "ImagePositionPatient" },
{ 0x0022, 0x0030, 0, VR::FL, VM::M1, "AxialLengthOfTheEye" },
{ 0x0024, 0x0036, 0, VR::US, VM::M1, "PatientNotProperlyFixatedQuantity" },
{ 0x0070, 0x0062, 0, VR::IS, VM::M1, "GraphicLayerOrder" },
{ 0x0072, 0x0060, 0, VR::AT, VM::M1TN, "SelectorATValue" },
{ 0x0074, 0x1027, 0, VR::FD, VM::M1, "TableTopLongitudinalAdjustedPosition" },
{ 0x2010, 0x0080, 0, VR::CS, VM::M1, "SmoothingType" },
{ 0x300A, 0x00DB, 0, VR::FL, VM::M1, "WedgeThinEdgePosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0019[] = {
{ 0x0008, 0x001B, 0, VR::UI, VM::M1, "OriginalSpecializedSOPClassUID" },
{ 0x0022, 0x0031, 0, VR::SQ, VM::M1, "OphthalmicFrameLocationSequence" },
{ 0x0022, 0x1460, 0, VR::FL, VM::M1, "OphthalmicThicknessMapThresholdQualityRating" },
{ 0x0024, 0x0037, 0, VR::CS, VM::M1, "PresentedVisualStimuliDataFlag" },
{ 0x0032, 0x1060, 0, VR::LO, VM::M1, "RequestedProcedureDescription" },
{ 0x0040, 0x1012, 0, VR::SQ, VM::M1, "ReasonForPerformedProcedureCodeSequence" },
{ 0x0054, 0x1006, 0, VR::CS, VM::M1, "SUVType" },
{ 0x0074, 0x1026, 0, VR::FD, VM::M1, "TableTopVerticalAdjustedPosition" },
{ 0x300A, 0x00DA, 0, VR::DS, VM::M1, "SourceToWedgeTrayDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0020[] = {
{ 0x0002, 0x0016, 0, VR::AE, VM::M1, "SourceApplicationEntityTitle" },
{ 0x0022, 0x0036, 0, VR::FL, VM::M1, "MaximumDepthDistortion" },
{ 0x0022, 0x1467, 0, VR::FL, VM::M2, "RegisteredLocalizerTopLeftHandCorner" },
{ 0x0046, 0x0052, 0, VR::SQ, VM::M1, "AutorefractionLeftEyeSequence" },
{ 0x0054, 0x1001, 0, VR::CS, VM::M1, "Units" },
{ 0x0072, 0x0066, 0, VR::LO, VM::M1TN, "SelectorLOValue" },
{ 0x300A, 0x00DD, 0, VR::ST, VM::M1, "BolusDescription" },
{ 0x4008, 0x0118, 1, VR::SQ, VM::M1, "ResultsDistributionListSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0021[] = {
{ 0x0014, 0x1040, 2, VR::ST, VM::M1, "EnvironmentalConditions" },
{ 0x0020, 0x0035, 1, VR::DS, VM::M6, "ImageOrientation" },
{ 0x0022, 0x0037, 0, VR::FL, VM::M1, "AlongScanSpatialResolution" },
{ 0x0022, 0x1466, 0, VR::CS, VM::M1, "RegisteredLocalizerUnits" },
{ 0x0054, 0x1000, 0, VR::CS, VM::M2, "SeriesType" },
{ 0x0074, 0x1020, 0, VR::SQ, VM::M1, "BeamTaskSequence" },
{ 0x0400, 0x0005, 0, VR::US, VM::M1, "MACIDNumber" },
{ 0x300A, 0x00DC, 0, VR::SH, VM::M1, "BolusID" },
{ 0x4008, 0x0119, 1, VR::PN, VM::M1, "DistributionName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0022[] = {
{ 0x0022, 0x1465, 0, VR::SQ, VM::M1, "RegistrationToLocalizerSequence" },
{ 0x0024, 0x0032, 0, VR::SQ, VM::M1, "FixationSequence" },
{ 0x0046, 0x0050, 0, VR::SQ, VM::M1, "AutorefractionRightEyeSequence" },
{ 0x0070, 0x0066, 0, VR::US, VM::M1, "GraphicLayerRecommendedDisplayGrayscaleValue" },
{ 0x0072, 0x0064, 0, VR::IS, VM::M1TN, "SelectorISValue" },
{ 0x0076, 0x0060, 0, VR::SQ, VM::M1, "ComponentAssemblySequence" },
{ 0x4008, 0x011A, 1, VR::LO, VM::M1, "DistributionAddress" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0023[] = {
{ 0x0020, 0x0037, 0, VR::DS, VM::M6, "ImageOrientationPatient" },
{ 0x0022, 0x0035, 0, VR::FL, VM::M1, "DepthSpatialResolution" },
{ 0x0024, 0x0033, 0, VR::SQ, VM::M1, "FixationMonitoringCodeSequence" },
{ 0x0032, 0x1064, 0, VR::SQ, VM::M1, "RequestedProcedureCodeSequence" },
{ 0x0054, 0x1002, 0, VR::CS, VM::M1, "CountsSource" },
{ 0x0070, 0x0067, 1, VR::US, VM::M3, "GraphicLayerRecommendedDisplayRGBValue" },
{ 0x0074, 0x1022, 0, VR::CS, VM::M1, "BeamTaskType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0024[] = {
{ 0x0008, 0x0010, 1, VR::SH, VM::M1, "RecognitionCode" },
{ 0x0018, 0x1041, 0, VR::DS, VM::M1, "ContrastBolusVolume" },
{ 0x0028, 0x0030, 0, VR::DS, VM::M2, "PixelSpacing" },
{ 0x0028, 0x0810, 1, VR::CS, VM::M1TN, "CodeLabel" },
{ 0x0038, 0x0020, 0, VR::DA, VM::M1, "AdmittingDate" },
{ 0x0040, 0x9211, 0, VR::XS, VM::M1, "RealWorldValueLastValueMapped" },
{ 0x0070, 0x0068, 0, VR::LO, VM::M1, "GraphicLayerDescription" },
{ 0x0072, 0x006A, 0, VR::PN, VM::M1TN, "SelectorPNValue" },
{ 0x0074, 0x102D, 0, VR::FD, VM::M1, "TableTopRollAdjustedAngle" },
{ 0x0078, 0x0060, 0, VR::FD, VM::M9, "ThreeDImplantTemplateGroupMemberMatchingAxes" },
{ 0x300A, 0x00D1, 0, VR::SQ, VM::M1, "WedgeSequence" },
{ 0x4008, 0x0114, 1, VR::PN, VM::M1, "PhysicianApprovingInterpretation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0025[] = {
{ 0x0008, 0x1050, 0, VR::PN, VM::M1TN, "PerformingPhysicianName" },
{ 0x0018, 0x1040, 0, VR::LO, VM::M1, "ContrastBolusRoute" },
{ 0x0018, 0x1450, 0, VR::DS, VM::M1, "ColumnAngulation" },
{ 0x0028, 0x0031, 0, VR::DS, VM::M2, "ZoomFactor" },
{ 0x0038, 0x0021, 0, VR::TM, VM::M1, "AdmittingTime" },
{ 0x0040, 0x9210, 0, VR::SH, VM::M1, "LUTLabel" },
{ 0x0074, 0x102C, 0, VR::FD, VM::M1, "TableTopPitchAdjustedAngle" },
{ 0x300A, 0x00D0, 0, VR::IS, VM::M1, "NumberOfWedges" },
{ 0x4008, 0x0115, 1, VR::LT, VM::M1, "InterpretationDiagnosisDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0026[] = {
{ 0x0008, 0x0012, 0, VR::DA, VM::M1, "InstanceCreationDate" },
{ 0x0018, 0x1043, 0, VR::TM, VM::M1, "ContrastBolusStopTime" },
{ 0x0022, 0x0038, 0, VR::FL, VM::M1, "MaximumAlongScanDistortion" },
{ 0x0028, 0x0032, 0, VR::DS, VM::M2, "ZoomCenter" },
{ 0x0028, 0x0812, 1, VR::US, VM::M1, "NumberOfTables" },
{ 0x003A, 0x0020, 0, VR::SH, VM::M1, "MultiplexGroupLabel" },
{ 0x0072, 0x0068, 0, VR::LT, VM::M1, "SelectorLTValue" },
{ 0x300A, 0x00D3, 0, VR::CS, VM::M1, "WedgeType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0027[] = {
{ 0x0008, 0x0013, 0, VR::TM, VM::M1, "InstanceCreationTime" },
{ 0x0008, 0x1052, 0, VR::SQ, VM::M1, "PerformingPhysicianIdentificationSequence" },
{ 0x0018, 0x1042, 0, VR::TM, VM::M1, "ContrastBolusStartTime" },
{ 0x0022, 0x0039, 0, VR::CS, VM::M1, "OphthalmicImageOrientation" },
{ 0x0022, 0x1468, 0, VR::FL, VM::M2, "RegisteredLocalizerBottomRightHandCorner" },
{ 0x0028, 0x0813, 1, VR::AT, VM::M1TN, "CodeTableLocation" },
{ 0x0040, 0x9212, 0, VR::FD, VM::M1TN, "RealWorldValueLUTData" },
{ 0x3008, 0x00D0, 0, VR::SQ, VM::M1, "RecordedBlockSequence" },
{ 0x300A, 0x00D2, 0, VR::IS, VM::M1, "WedgeNumber" },
{ 0x4008, 0x0117, 1, VR::SQ, VM::M1, "InterpretationDiagnosisCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0028[] = {
{ 0x0008, 0x0014, 0, VR::UI, VM::M1, "InstanceCreatorUID" },
{ 0x0018, 0x1045, 0, VR::IS, VM::M1, "SyringeCounts" },
{ 0x0024, 0x0038, 0, VR::US, VM::M1, "NumberOfVisualStimuli" },
{ 0x0028, 0x0034, 0, VR::IS, VM::M2, "PixelAspectRatio" },
{ 0x0028, 0x0814, 1, VR::US, VM::M1, "BitsForCodeWord" },
{ 0x0072, 0x006E, 0, VR::ST, VM::M1, "SelectorSTValue" },
{ 0x300A, 0x00D5, 0, VR::IS, VM::M1, "WedgeAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0029[] = {
{ 0x0008, 0x0015, 0, VR::DT, VM::M1, "InstanceCoercionDateTime" },
{ 0x0018, 0x1044, 0, VR::DS, VM::M1, "ContrastBolusTotalDose" },
{ 0x0024, 0x0039, 0, VR::CS, VM::M1, "ExcessiveFixationLossesDataFlag" },
{ 0x0074, 0x1028, 0, VR::FD, VM::M1, "TableTopLateralAdjustedPosition" },
{ 0x300A, 0x00D4, 0, VR::SH, VM::M1, "WedgeID" },
{ 0x4008, 0x0111, 1, VR::SQ, VM::M1, "InterpretationApproverSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0030[] = {
{ 0x0008, 0x0016, 0, VR::UI, VM::M1, "SOPClassUID" },
{ 0x0018, 0x1047, 0, VR::DS, VM::M1TN, "ContrastFlowDuration" },
{ 0x0068, 0x65E0, 0, VR::SQ, VM::M1, "TwoDPlaneCoordinatesSequence" },
{ 0x0072, 0x006C, 0, VR::SH, VM::M1TN, "SelectorSHValue" },
{ 0x0074, 0x102B, 0, VR::FD, VM::M1, "TableTopEccentricAdjustedAngle" },
{ 0x300A, 0x00D7, 0, VR::FL, VM::M1, "TotalWedgeTrayWaterEquivalentThickness" },
{ 0x4008, 0x0112, 1, VR::DA, VM::M1, "InterpretationApprovalDate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0031[] = {
{ 0x0018, 0x1046, 0, VR::DS, VM::M1TN, "ContrastFlowRate" },
{ 0x0040, 0x9216, 0, VR::XS, VM::M1, "RealWorldValueFirstValueMapped" },
{ 0x0074, 0x102A, 0, VR::FD, VM::M1, "PatientSupportAdjustedAngle" },
{ 0x300A, 0x00D6, 0, VR::DS, VM::M1, "WedgeFactor" },
{ 0x300C, 0x00D0, 0, VR::IS, VM::M1, "ReferencedCompensatorNumber" },
{ 0x4008, 0x0113, 1, VR::TM, VM::M1, "InterpretationApprovalTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0032[] = {
{ 0x0010, 0x0030, 0, VR::DA, VM::M1, "PatientBirthDate" },
{ 0x0014, 0x0034, 2, VR::DS, VM::M1TN, "MaterialIsolationDiameter" },
{ 0x0018, 0x0038, 0, VR::CS, VM::M1, "InterventionStatus" },
{ 0x0018, 0x1079, 0, VR::DT, VM::M1, "RadiopharmaceuticalStopDateTime" },
{ 0x0020, 0x1041, 0, VR::DS, VM::M1, "SliceLocation" },
{ 0x0020, 0x9249, 0, VR::CS, VM::M1, "EndingRespiratoryPhase" },
{ 0x0022, 0x0002, 0, VR::US, VM::M2, "LightPathFilterPassBand" },
{ 0x0028, 0x0008, 0, VR::IS, VM::M1, "NumberOfFrames" },
{ 0x0032, 0x0012, 1, VR::LO, VM::M1, "StudyIDIssuer" },
{ 0x003A, 0x001A, 0, VR::DS, VM::M1, "SamplingFrequency" },
{ 0x0040, 0xDB0D, 1, VR::UI, VM::M1, "TemplateExtensionCreatorUID" },
{ 0x0070, 0x0050, 1, VR::US, VM::M2, "DisplayedAreaTopLeftHandCornerTrial" },
{ 0x0072, 0x0052, 0, VR::AT, VM::M1TN, "SelectorSequencePointer" },
{ 0x2000, 0x00A2, 0, VR::SQ, VM::M1, "MediaInstalledSequence" },
{ 0x300A, 0x00E9, 0, VR::DS, VM::M2, "CompensatorPixelSpacing" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0033[] = {
{ 0x0018, 0x0039, 1, VR::CS, VM::M1, "TherapyDescription" },
{ 0x0018, 0x1078, 0, VR::DT, VM::M1, "RadiopharmaceuticalStartDateTime" },
{ 0x0020, 0x1040, 0, VR::LO, VM::M1, "PositionReferenceIndicator" },
{ 0x0020, 0x9248, 0, VR::FL, VM::M1, "EndingRespiratoryAmplitude" },
{ 0x0022, 0x0003, 0, VR::US, VM::M1, "ImagePathFilterPassThroughWavelength" },
{ 0x0022, 0x1452, 0, VR::XS, VM::M1, "MappedPixelValue" },
{ 0x0028, 0x0009, 0, VR::AT, VM::M1TN, "FrameIncrementPointer" },
{ 0x0040, 0xDB0C, 1, VR::UI, VM::M1, "TemplateExtensionOrganizationUID" },
{ 0x0070, 0x0051, 1, VR::US, VM::M2, "DisplayedAreaBottomRightHandCornerTrial" },
{ 0x300A, 0x00E8, 0, VR::IS, VM::M1, "CompensatorColumns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0034[] = {
{ 0x0008, 0x002A, 0, VR::DT, VM::M1, "AcquisitionDateTime" },
{ 0x0010, 0x0032, 0, VR::TM, VM::M1, "PatientBirthTime" },
{ 0x0012, 0x0030, 0, VR::LO, VM::M1, "ClinicalTrialSiteID" },
{ 0x0018, 0x003A, 0, VR::ST, VM::M1, "InterventionDescription" },
{ 0x0028, 0x000A, 0, VR::AT, VM::M1TN, "FrameDimensionPointer" },
{ 0x0032, 0x1051, 1, VR::TM, VM::M1, "StudyCompletionTime" },
{ 0x0038, 0x001A, 1, VR::DA, VM::M1, "ScheduledAdmissionDate" },
{ 0x0046, 0x0064, 0, VR::FD, VM::M1, "OtherPupillaryDistance" },
{ 0x0070, 0x0052, 0, VR::SL, VM::M2, "DisplayedAreaTopLeftHandCorner" },
{ 0x0072, 0x0050, 0, VR::CS, VM::M1, "SelectorAttributeVR" },
{ 0x2000, 0x00A0, 0, VR::US, VM::M1, "MemoryBitDepth" },
{ 0x300A, 0x00EB, 0, VR::DS, VM::M1TN, "CompensatorTransmissionData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0035[] = {
{ 0x0012, 0x0031, 0, VR::LO, VM::M1, "ClinicalTrialSiteName" },
{ 0x0022, 0x0001, 0, VR::US, VM::M1, "LightPathFilterPassThroughWavelength" },
{ 0x0022, 0x1040, 0, VR::SQ, VM::M1, "RefractiveSurgeryTypeCodeSequence" },
{ 0x0022, 0x1450, 0, VR::SQ, VM::M1, "PixelValueMappingToCodedConceptSequence" },
{ 0x0032, 0x1050, 1, VR::DA, VM::M1, "StudyCompletionDate" },
{ 0x0038, 0x001B, 1, VR::TM, VM::M1, "ScheduledAdmissionTime" },
{ 0x0070, 0x0053, 0, VR::SL, VM::M2, "DisplayedAreaBottomRightHandCorner" },
{ 0x0076, 0x0055, 0, VR::US, VM::M1, "ComponentID" },
{ 0x2000, 0x00A1, 0, VR::US, VM::M1, "PrintingBitDepth" },
{ 0x300A, 0x00EA, 0, VR::DS, VM::M2, "CompensatorPosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0036[] = {
{ 0x0014, 0x0030, 2, VR::DS, VM::M1TN, "MaterialThickness" },
{ 0x0022, 0x0006, 0, VR::SQ, VM::M1, "PatientEyeMovementCommandCodeSequence" },
{ 0x0038, 0x001C, 1, VR::DA, VM::M1, "ScheduledDischargeDate" },
{ 0x0046, 0x0062, 0, VR::FD, VM::M1, "NearPupillaryDistance" },
{ 0x0054, 0x0070, 0, VR::US, VM::M1TN, "TimeSlotVector" },
{ 0x0072, 0x0056, 0, VR::LO, VM::M1, "SelectorAttributePrivateCreator" },
{ 0x300A, 0x00ED, 0, VR::IS, VM::M1, "NumberOfBoli" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0037[] = {
{ 0x0022, 0x0007, 0, VR::FL, VM::M1, "SphericalLensPower" },
{ 0x0038, 0x001D, 1, VR::TM, VM::M1, "ScheduledDischargeTime" },
{ 0x0046, 0x0063, 0, VR::FD, VM::M1, "IntermediatePupillaryDistance" },
{ 0x0054, 0x0071, 0, VR::US, VM::M1, "NumberOfTimeSlots" },
{ 0x300A, 0x00EC, 0, VR::DS, VM::M1TN, "CompensatorThicknessData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0038[] = {
{ 0x0014, 0x0032, 2, VR::DS, VM::M1TN, "MaterialPipeDiameter" },
{ 0x0022, 0x0004, 0, VR::US, VM::M2, "ImagePathFilterPassBand" },
{ 0x0032, 0x1055, 1, VR::CS, VM::M1, "StudyComponentStatusID" },
{ 0x0038, 0x001E, 1, VR::LO, VM::M1, "ScheduledPatientInstitutionResidence" },
{ 0x0040, 0xDB0B, 1, VR::CS, VM::M1, "TemplateExtensionFlag" },
{ 0x0046, 0x0060, 0, VR::FD, VM::M1, "DistancePupillaryDistance" },
{ 0x0054, 0x0072, 0, VR::SQ, VM::M1, "TimeSlotInformationSequence" },
{ 0x0072, 0x0054, 0, VR::LO, VM::M1TN, "SelectorSequencePointerPrivateCreator" },
{ 0x2000, 0x00A4, 0, VR::SQ, VM::M1, "OtherMediaAvailableSequence" },
{ 0x300A, 0x00EF, 0, VR::SH, VM::M1, "CompensatorTrayID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0039[] = {
{ 0x0022, 0x0005, 0, VR::CS, VM::M1, "PatientEyeMovementCommanded" },
{ 0x0022, 0x1044, 0, VR::SQ, VM::M1, "OphthalmicUltrasoundMethodCodeSequence" },
{ 0x0022, 0x1454, 0, VR::LO, VM::M1, "PixelValueMappingExplanation" },
{ 0x0054, 0x0073, 0, VR::DS, VM::M1, "TimeSlotTime" },
{ 0x300A, 0x00EE, 0, VR::CS, VM::M1, "CompensatorType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0040[] = {
{ 0x0008, 0x0020, 0, VR::DA, VM::M1, "StudyDate" },
{ 0x0018, 0x0030, 1, VR::LO, VM::M1TN, "Radionuclide" },
{ 0x0018, 0x1071, 0, VR::DS, VM::M1, "RadiopharmaceuticalVolume" },
{ 0x0020, 0x9241, 0, VR::FL, VM::M1, "NominalPercentageOfCardiacPhase" },
{ 0x0022, 0x000A, 0, VR::FL, VM::M1, "EmmetropicMagnification" },
{ 0x0028, 0x0410, 1, VR::US, VM::M1, "RowsForNthOrderCoefficients" },
{ 0x0028, 0x1041, 0, VR::SS, VM::M1, "PixelIntensityRelationshipSign" },
{ 0x0038, 0x0010, 0, VR::LO, VM::M1, "AdmissionID" },
{ 0x0038, 0x0400, 0, VR::LO, VM::M1, "PatientInstitutionResidence" },
{ 0x0078, 0x0050, 0, VR::FD, VM::M3, "ThreeDImplantTemplateGroupMemberMatchingPoint" },
{ 0x300A, 0x00E1, 0, VR::SH, VM::M1, "MaterialID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0041[] = {
{ 0x0008, 0x0021, 0, VR::DA, VM::M1, "SeriesDate" },
{ 0x0008, 0x1060, 0, VR::PN, VM::M1TN, "NameOfPhysiciansReadingStudy" },
{ 0x0018, 0x0031, 0, VR::LO, VM::M1, "Radiopharmaceutical" },
{ 0x0018, 0x1070, 0, VR::LO, VM::M1, "RadiopharmaceuticalRoute" },
{ 0x0018, 0x1460, 0, VR::DS, VM::M1, "TomoLayerHeight" },
{ 0x0022, 0x000B, 0, VR::FL, VM::M1, "IntraOcularPressure" },
{ 0x0028, 0x0411, 1, VR::US, VM::M1, "ColumnsForNthOrderCoefficients" },
{ 0x0028, 0x1040, 0, VR::CS, VM::M1, "PixelIntensityRelationship" },
{ 0x0038, 0x0011, 1, VR::LO, VM::M1, "IssuerOfAdmissionID" },
{ 0x300A, 0x00E0, 0, VR::IS, VM::M1, "NumberOfCompensators" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0042[] = {
{ 0x0008, 0x0022, 0, VR::DA, VM::M1, "AcquisitionDate" },
{ 0x0018, 0x0032, 1, VR::DS, VM::M1, "EnergyWindowCenterline" },
{ 0x0018, 0x1073, 0, VR::TM, VM::M1, "RadiopharmaceuticalStopTime" },
{ 0x0022, 0x0008, 0, VR::FL, VM::M1, "CylinderLensPower" },
{ 0x0028, 0x0002, 0, VR::US, VM::M1, "SamplesPerPixel" },
{ 0x0028, 0x0412, 1, VR::LO, VM::M1TN, "CoefficientCoding" },
{ 0x003A, 0x0010, 0, VR::UL, VM::M1, "NumberOfWaveformSamples" },
{ 0x0040, 0xDB07, 1, VR::DT, VM::M1, "TemplateLocalVersion" },
{ 0x0070, 0x005A, 0, VR::SQ, VM::M1, "DisplayedAreaSelectionSequence" },
{ 0x2000, 0x00A8, 0, VR::SQ, VM::M1, "SupportedImageDisplayFormatsSequence" },
{ 0x300A, 0x00E3, 0, VR::SQ, VM::M1, "CompensatorSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0043[] = {
{ 0x0008, 0x0023, 0, VR::DA, VM::M1, "ContentDate" },
{ 0x0008, 0x1062, 0, VR::SQ, VM::M1, "PhysiciansReadingStudyIdentificationSequence" },
{ 0x0018, 0x0033, 1, VR::DS, VM::M1TN, "EnergyWindowTotalWidth" },
{ 0x0018, 0x1072, 0, VR::TM, VM::M1, "RadiopharmaceuticalStartTime" },
{ 0x0022, 0x0009, 0, VR::FL, VM::M1, "CylinderAxis" },
{ 0x0022, 0x1458, 0, VR::SQ, VM::M1, "OphthalmicThicknessMapQualityThresholdSequence" },
{ 0x0028, 0x0003, 0, VR::US, VM::M1, "SamplesPerPixelUsed" },
{ 0x0028, 0x0413, 1, VR::AT, VM::M1TN, "CoefficientCodingPointers" },
{ 0x0040, 0xDB06, 1, VR::DT, VM::M1, "TemplateVersion" },
{ 0x3008, 0x00E0, 0, VR::SQ, VM::M1, "TreatmentSummaryMeasuredDoseReferenceSequence" },
{ 0x300A, 0x00E2, 0, VR::DS, VM::M1, "TotalCompensatorTrayFactor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0044[] = {
{ 0x0008, 0x0024, 1, VR::DA, VM::M1, "OverlayDate" },
{ 0x0018, 0x0034, 0, VR::LO, VM::M1, "InterventionDrugName" },
{ 0x0018, 0x1075, 0, VR::DS, VM::M1, "RadionuclideHalfLife" },
{ 0x0020, 0x9245, 0, VR::FL, VM::M1, "NominalPercentageOfRespiratoryPhase" },
{ 0x0022, 0x000E, 0, VR::FL, VM::M1, "DegreeOfDilation" },
{ 0x0028, 0x0004, 0, VR::CS, VM::M1, "PhotometricInterpretation" },
{ 0x0038, 0x0014, 0, VR::SQ, VM::M1, "IssuerOfAdmissionIDSequence" },
{ 0x0040, 0x9225, 0, VR::FD, VM::M1, "RealWorldValueSlope" },
{ 0x300A, 0x00E5, 0, VR::SH, VM::M1, "CompensatorID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0045[] = {
{ 0x0008, 0x0025, 1, VR::DA, VM::M1, "CurveDate" },
{ 0x0018, 0x0035, 0, VR::TM, VM::M1, "InterventionDrugStartTime" },
{ 0x0018, 0x1074, 0, VR::DS, VM::M1, "RadionuclideTotalDose" },
{ 0x0020, 0x000D, 0, VR::UI, VM::M1, "StudyInstanceUID" },
{ 0x0028, 0x0005, 1, VR::US, VM::M1, "ImageDimensions" },
{ 0x0040, 0x9224, 0, VR::FD, VM::M1, "RealWorldValueIntercept" },
{ 0x0040, 0xDB00, 0, VR::CS, VM::M1, "TemplateIdentifier" },
{ 0x300A, 0x00E4, 0, VR::IS, VM::M1, "CompensatorNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0046[] = {
{ 0x0018, 0x0036, 0, VR::SQ, VM::M1, "InterventionSequence" },
{ 0x0018, 0x1077, 0, VR::DS, VM::M1, "RadiopharmaceuticalSpecificActivity" },
{ 0x0020, 0x000E, 0, VR::UI, VM::M1, "SeriesInstanceUID" },
{ 0x0020, 0x9247, 0, VR::CS, VM::M1, "StartingRespiratoryPhase" },
{ 0x0022, 0x000C, 0, VR::FL, VM::M1, "HorizontalFieldOfView" },
{ 0x0028, 0x0006, 0, VR::US, VM::M1, "PlanarConfiguration" },
{ 0x0038, 0x0016, 0, VR::LO, VM::M1, "RouteOfAdmissions" },
{ 0x0068, 0x65D0, 0, VR::FD, VM::M6, "ThreeDLineCoordinates" },
{ 0x300A, 0x00E7, 0, VR::IS, VM::M1, "CompensatorRows" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0047[] = {
{ 0x0018, 0x0037, 1, VR::CS, VM::M1, "TherapyType" },
{ 0x0018, 0x1076, 0, VR::DS, VM::M1, "RadionuclidePositronFraction" },
{ 0x0020, 0x9246, 0, VR::FL, VM::M1, "StartingRespiratoryAmplitude" },
{ 0x0022, 0x000D, 0, VR::CS, VM::M1, "PupilDilated" },
{ 0x300A, 0x00E6, 0, VR::DS, VM::M1, "SourceToCompensatorTrayDistance" },
{ 0x300C, 0x00E0, 0, VR::IS, VM::M1, "ReferencedBlockNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0048[] = {
{ 0x0010, 0x0020, 0, VR::LO, VM::M1, "PatientID" },
{ 0x0014, 0x0024, 1, VR::ST, VM::M1TN, "ComponentReferenceSystem" },
{ 0x0018, 0x0028, 0, VR::DS, VM::M1, "InterventionDrugDose" },
{ 0x0018, 0x1069, 0, VR::DS, VM::M1, "TriggerTimeOffset" },
{ 0x0020, 0x0010, 0, VR::SH, VM::M1, "StudyID" },
{ 0x0022, 0x0012, 0, VR::FL, VM::M1, "StereoHorizontalPixelOffset" },
{ 0x0022, 0x1053, 0, VR::FL, VM::M1, "IOLPower" },
{ 0x0022, 0x1443, 0, VR::SQ, VM::M1, "OphthalmicThicknessMappingNormalsSequence" },
{ 0x0038, 0x0008, 0, VR::CS, VM::M1, "VisitStatusID" },
{ 0x0046, 0x0076, 0, VR::FD, VM::M1, "KeratometricPower" },
{ 0x0070, 0x0040, 1, VR::IS, VM::M1, "ImageRotationRetired" },
{ 0x0400, 0x0020, 0, VR::AT, VM::M1TN, "DataElementsSigned" },
{ 0x300A, 0x00F9, 0, VR::LO, VM::M1, "AccessoryCode" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0049[] = {
{ 0x0010, 0x0021, 0, VR::LO, VM::M1, "IssuerOfPatientID" },
{ 0x0010, 0x1060, 0, VR::PN, VM::M1, "PatientMotherBirthName" },
{ 0x0014, 0x0025, 2, VR::ST, VM::M1TN, "ComponentManufacturingProcedure" },
{ 0x0018, 0x0029, 0, VR::SQ, VM::M1, "InterventionDrugCodeSequence" },
{ 0x0018, 0x1068, 0, VR::DS, VM::M1, "MultiplexGroupTimeOffset" },
{ 0x0018, 0x9260, 0, VR::SQ, VM::M1, "ASLSlabSequence" },
{ 0x0020, 0x0011, 0, VR::IS, VM::M1, "SeriesNumber" },
{ 0x0022, 0x0013, 0, VR::FL, VM::M1, "StereoVerticalPixelOffset" },
{ 0x0046, 0x0077, 0, VR::FD, VM::M1, "KeratometricAxis" },
{ 0x0070, 0x0041, 0, VR::CS, VM::M1, "ImageHorizontalFlip" },
{ 0x0074, 0x1004, 0, VR::DS, VM::M1, "ProcedureStepProgress" },
{ 0x300A, 0x00F8, 0, VR::CS, VM::M1, "BlockType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0050[] = {
{ 0x0010, 0x0022, 0, VR::CS, VM::M1, "TypeOfPatientID" },
{ 0x0012, 0x0020, 0, VR::LO, VM::M1, "ClinicalTrialProtocolID" },
{ 0x0018, 0x002A, 0, VR::SQ, VM::M1, "AdditionalDrugSequence" },
{ 0x0020, 0x0012, 0, VR::IS, VM::M1, "AcquisitionNumber" },
{ 0x0022, 0x0010, 0, VR::FL, VM::M1, "StereoBaselineAngle" },
{ 0x0024, 0x0016, 0, VR::SQ, VM::M1, "ScreeningTestModeCodeSequence" },
{ 0x0032, 0x1041, 1, VR::TM, VM::M1, "StudyArrivalTime" },
{ 0x0046, 0x0074, 0, VR::SQ, VM::M1, "SteepKeratometricAxisSequence" },
{ 0x0070, 0x0042, 0, VR::US, VM::M1, "ImageRotation" },
{ 0x0072, 0x0040, 0, VR::LO, VM::M1, "ImageSetLabel" },
{ 0x300A, 0x00FB, 0, VR::CS, VM::M1, "BlockMountingPosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0051[] = {
{ 0x0012, 0x0021, 0, VR::LO, VM::M1, "ClinicalTrialProtocolName" },
{ 0x0018, 0x106A, 0, VR::CS, VM::M1, "SynchronizationTrigger" },
{ 0x0020, 0x0013, 0, VR::IS, VM::M1, "InstanceNumber" },
{ 0x0022, 0x0011, 0, VR::FL, VM::M1, "StereoBaselineDisplacement" },
{ 0x0022, 0x1050, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthMeasurementsSequence" },
{ 0x0032, 0x1040, 1, VR::DA, VM::M1, "StudyArrivalDate" },
{ 0x0046, 0x0075, 0, VR::FD, VM::M1, "RadiusOfCurvature" },
{ 0x0074, 0x1006, 0, VR::ST, VM::M1, "ProcedureStepProgressDescription" },
{ 0x300A, 0x00FA, 0, VR::CS, VM::M1, "BlockDivergence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0052[] = {
{ 0x0010, 0x0024, 0, VR::SQ, VM::M1, "IssuerOfPatientIDQualifiersSequence" },
{ 0x0020, 0x0014, 1, VR::IS, VM::M1, "IsotopeNumber" },
{ 0x0022, 0x0016, 0, VR::SQ, VM::M1, "IlluminationTypeCodeSequence" },
{ 0x0024, 0x0010, 0, VR::FL, VM::M1, "VisualFieldHorizontalExtent" },
{ 0x0054, 0x0060, 0, VR::US, VM::M1TN, "RRIntervalVector" },
{ 0x2010, 0x00A6, 0, VR::CS, VM::M1, "DefaultMagnificationType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0053[] = {
{ 0x0018, 0x106C, 0, VR::US, VM::M2, "SynchronizationChannel" },
{ 0x0020, 0x0015, 1, VR::IS, VM::M1, "PhaseNumber" },
{ 0x0022, 0x0017, 0, VR::SQ, VM::M1, "LightPathFilterTypeStackCodeSequence" },
{ 0x0024, 0x0011, 0, VR::FL, VM::M1, "VisualFieldVerticalExtent" },
{ 0x0054, 0x0061, 0, VR::US, VM::M1, "NumberOfRRIntervals" },
{ 0x0074, 0x1000, 0, VR::CS, VM::M1, "ProcedureStepState" },
{ 0x2010, 0x00A7, 0, VR::CS, VM::M1TN, "OtherMagnificationTypesAvailable" },
{ 0x300A, 0x00FC, 0, VR::IS, VM::M1, "BlockNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0054[] = {
{ 0x0020, 0x0016, 1, VR::IS, VM::M1, "IntervalNumber" },
{ 0x0022, 0x0014, 0, VR::FL, VM::M1, "StereoRotation" },
{ 0x0022, 0x1445, 0, VR::SQ, VM::M1, "RetinalThicknessDefinitionCodeSequence" },
{ 0x0024, 0x0012, 0, VR::CS, VM::M1, "VisualFieldShape" },
{ 0x0046, 0x0070, 0, VR::SQ, VM::M1, "KeratometryRightEyeSequence" },
{ 0x0054, 0x0062, 0, VR::SQ, VM::M1, "GatedInformationSequence" },
{ 0x0076, 0x0040, 0, VR::SQ, VM::M1, "ComponentSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0055[] = {
{ 0x0014, 0x0023, 1, VR::ST, VM::M1TN, "CADFileFormat" },
{ 0x0018, 0x106E, 0, VR::UL, VM::M1, "TriggerSamplePosition" },
{ 0x0020, 0x0017, 1, VR::IS, VM::M1, "TimeSlotNumber" },
{ 0x0022, 0x0015, 0, VR::SQ, VM::M1, "AcquisitionDeviceTypeCodeSequence" },
{ 0x0022, 0x1054, 0, VR::FL, VM::M1, "PredictedRefractiveError" },
{ 0x0046, 0x0071, 0, VR::SQ, VM::M1, "KeratometryLeftEyeSequence" },
{ 0x0054, 0x0063, 0, VR::SQ, VM::M1, "DataInformationSequence" },
{ 0x0074, 0x1002, 0, VR::SQ, VM::M1, "ProcedureStepProgressInformationSequence" },
{ 0x300A, 0x00FE, 0, VR::LO, VM::M1, "BlockName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0056[] = {
{ 0x0008, 0x0030, 0, VR::TM, VM::M1, "StudyTime" },
{ 0x0018, 0x0020, 0, VR::CS, VM::M1TN, "ScanningSequence" },
{ 0x0018, 0x1061, 0, VR::LO, VM::M1, "TriggerSourceOrType" },
{ 0x0020, 0x0018, 1, VR::IS, VM::M1, "AngleNumber" },
{ 0x0020, 0x9251, 0, VR::FD, VM::M1, "RRIntervalTimeNominal" },
{ 0x0022, 0x001A, 0, VR::SQ, VM::M1, "ChannelDescriptionCodeSequence" },
{ 0x0028, 0x0010, 0, VR::US, VM::M1, "Rows" },
{ 0x0028, 0x0400, 1, VR::LO, VM::M1, "TransformLabel" },
{ 0x0028, 0x1051, 0, VR::DS, VM::M1TN, "WindowWidth" },
{ 0x0032, 0x000A, 1, VR::CS, VM::M1, "StudyStatusID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0057[] = {
{ 0x0008, 0x0031, 0, VR::TM, VM::M1, "SeriesTime" },
{ 0x0008, 0x1070, 0, VR::PN, VM::M1TN, "OperatorsName" },
{ 0x0018, 0x0021, 0, VR::CS, VM::M1TN, "SequenceVariant" },
{ 0x0018, 0x1060, 0, VR::DS, VM::M1, "TriggerTime" },
{ 0x0018, 0x1470, 0, VR::DS, VM::M1, "TomoAngle" },
{ 0x0020, 0x0019, 0, VR::IS, VM::M1, "ItemNumber" },
{ 0x0020, 0x9250, 0, VR::CS, VM::M1, "RespiratoryTriggerType" },
{ 0x0022, 0x001B, 0, VR::SQ, VM::M1, "RefractiveStateSequence" },
{ 0x0028, 0x0011, 0, VR::US, VM::M1, "Columns" },
{ 0x0028, 0x0401, 1, VR::LO, VM::M1, "TransformVersionNumber" },
{ 0x0028, 0x1050, 0, VR::DS, VM::M1TN, "WindowCenter" },
{ 0x0074, 0x100c, 0, VR::LO, VM::M1, "ContactDisplayName" },
{ 0x3008, 0x00F2, 0, VR::SQ, VM::M1, "RecordedRangeShifterSequence" },
{ 0x300A, 0x00F0, 0, VR::IS, VM::M1, "NumberOfBlocks" },
{ 0x300C, 0x00F6, 0, VR::IS, VM::M1, "ReferencedStopControlPointIndex" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0058[] = {
{ 0x0008, 0x0032, 0, VR::TM, VM::M1, "AcquisitionTime" },
{ 0x0018, 0x0022, 0, VR::CS, VM::M1TN, "ScanOptions" },
{ 0x0018, 0x1063, 0, VR::DS, VM::M1, "FrameTime" },
{ 0x0020, 0x9253, 0, VR::SQ, VM::M1, "RespiratorySynchronizationSequence" },
{ 0x0022, 0x0018, 0, VR::SQ, VM::M1, "ImagePathFilterTypeStackCodeSequence" },
{ 0x0022, 0x1059, 0, VR::FL, VM::M1, "OphthalmicAxialLengthVelocity" },
{ 0x0028, 0x0012, 1, VR::US, VM::M1, "Planes" },
{ 0x0028, 0x0402, 1, VR::US, VM::M1, "NumberOfTransformSteps" },
{ 0x0028, 0x1053, 0, VR::DS, VM::M1, "RescaleSlope" },
{ 0x2010, 0x00A8, 0, VR::CS, VM::M1, "DefaultSmoothingType" },
{ 0x300A, 0x00F3, 0, VR::FL, VM::M1, "TotalBlockTrayWaterEquivalentThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0059[] = {
{ 0x0008, 0x0033, 0, VR::TM, VM::M1, "ContentTime" },
{ 0x0008, 0x1072, 0, VR::SQ, VM::M1, "OperatorIdentificationSequence" },
{ 0x0018, 0x0023, 0, VR::CS, VM::M1, "MRAcquisitionType" },
{ 0x0018, 0x1062, 0, VR::IS, VM::M1, "NominalInterval" },
{ 0x0020, 0x9252, 0, VR::FD, VM::M1, "ActualCardiacTriggerDelayTime" },
{ 0x0022, 0x0019, 0, VR::SQ, VM::M1, "LensesCodeSequence" },
{ 0x0028, 0x0403, 1, VR::LO, VM::M1TN, "SequenceOfCompressedData" },
{ 0x0028, 0x1052, 0, VR::DS, VM::M1, "RescaleIntercept" },
{ 0x0074, 0x100e, 0, VR::SQ, VM::M1, "ProcedureStepDiscontinuationReasonCodeSequence" },
{ 0x2010, 0x00A9, 0, VR::CS, VM::M1TN, "OtherSmoothingTypesAvailable" },
{ 0x3008, 0x00F0, 0, VR::SQ, VM::M1, "RecordedSnoutSequence" },
{ 0x300A, 0x00F2, 0, VR::DS, VM::M1, "TotalBlockTrayFactor" },
{ 0x300C, 0x00F4, 0, VR::IS, VM::M1, "ReferencedStartControlPointIndex" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0060[] = {
{ 0x0008, 0x0034, 1, VR::TM, VM::M1, "OverlayTime" },
{ 0x0014, 0x0028, 2, VR::ST, VM::M1TN, "ComponentManufacturer" },
{ 0x0018, 0x0024, 0, VR::SH, VM::M1, "SequenceName" },
{ 0x0018, 0x1065, 0, VR::DS, VM::M1TN, "FrameTimeVector" },
{ 0x0020, 0x9255, 0, VR::FD, VM::M1, "NominalRespiratoryTriggerDelayTime" },
{ 0x0022, 0x001E, 0, VR::FL, VM::M1, "CameraAngleOfView" },
{ 0x0024, 0x0018, 0, VR::FL, VM::M1, "MaximumStimulusLuminance" },
{ 0x0028, 0x0014, 0, VR::US, VM::M1, "UltrasoundColorDataPresent" },
{ 0x0028, 0x0404, 1, VR::AT, VM::M1TN, "DetailsOfCoefficients" },
{ 0x0028, 0x1055, 0, VR::LO, VM::M1TN, "WindowCenterWidthExplanation" },
{ 0x0038, 0x0004, 0, VR::SQ, VM::M1, "ReferencedPatientAliasSequence" },
{ 0x300A, 0x00F5, 0, VR::SH, VM::M1, "BlockTrayID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0061[] = {
{ 0x0008, 0x0035, 1, VR::TM, VM::M1, "CurveTime" },
{ 0x0018, 0x0025, 0, VR::CS, VM::M1, "AngioFlag" },
{ 0x0018, 0x1064, 0, VR::LO, VM::M1, "CardiacFramingType" },
{ 0x0020, 0x9254, 0, VR::FD, VM::M1, "RespiratoryIntervalTime" },
{ 0x0028, 0x1054, 0, VR::LO, VM::M1, "RescaleType" },
{ 0x0074, 0x1008, 0, VR::SQ, VM::M1, "ProcedureStepCommunicationsURISequence" },
{ 0x3008, 0x00F6, 0, VR::SQ, VM::M1, "RecordedRangeModulatorSequence" },
{ 0x300A, 0x00F4, 0, VR::SQ, VM::M1, "BlockSequence" },
{ 0x300C, 0x00F2, 0, VR::SQ, VM::M1, "ReferencedControlPointSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0062[] = {
{ 0x0018, 0x0026, 0, VR::SQ, VM::M1, "InterventionDrugInformationSequence" },
{ 0x0018, 0x1067, 0, VR::DS, VM::M1, "ImageTriggerDelay" },
{ 0x0020, 0x9257, 0, VR::FD, VM::M1, "ActualRespiratoryTriggerDelayTime" },
{ 0x0022, 0x001C, 0, VR::SQ, VM::M1, "MydriaticAgentCodeSequence" },
{ 0x0028, 0x6190, 0, VR::ST, VM::M1, "MaskOperationExplanation" },
{ 0x0032, 0x000C, 1, VR::CS, VM::M1, "StudyPriorityID" },
{ 0x003A, 0x0004, 0, VR::CS, VM::M1, "WaveformOriginality" },
{ 0x300A, 0x00F7, 0, VR::FL, VM::M1, "IsocenterToBlockTrayDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0063[] = {
{ 0x0018, 0x0027, 0, VR::TM, VM::M1, "InterventionDrugStopTime" },
{ 0x0018, 0x1066, 0, VR::DS, VM::M1, "FrameDelay" },
{ 0x0020, 0x9256, 0, VR::FD, VM::M1, "RespiratoryTriggerDelayThreshold" },
{ 0x0022, 0x001D, 0, VR::SQ, VM::M1, "RelativeImagePositionCodeSequence" },
{ 0x0028, 0x1056, 0, VR::CS, VM::M1, "VOILUTFunction" },
{ 0x003A, 0x0005, 0, VR::US, VM::M1, "NumberOfWaveformChannels" },
{ 0x0074, 0x100a, 0, VR::ST, VM::M1, "ContactURI" },
{ 0x3008, 0x00F4, 0, VR::SQ, VM::M1, "RecordedLateralSpreadingDeviceSequence" },
{ 0x300A, 0x00F6, 0, VR::DS, VM::M1, "SourceToBlockTrayDistance" },
{ 0x300C, 0x00F0, 0, VR::IS, VM::M1, "ReferencedControlPointIndex" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0064[] = {
{ 0x0010, 0x1010, 0, VR::AS, VM::M1, "PatientAge" },
{ 0x0018, 0x1018, 0, VR::LO, VM::M1, "SecondaryCaptureDeviceManufacturerModelName" },
{ 0x0020, 0x1020, 1, VR::LO, VM::M1TN, "Reference" },
{ 0x0020, 0x9228, 0, VR::UL, VM::M1, "ConcatenationFrameOffsetNumber" },
{ 0x0024, 0x0065, 0, VR::SQ, VM::M1, "AgeCorrectedSensitivityDeviationAlgorithmSequence" },
{ 0x0028, 0x0069, 1, VR::US, VM::M1, "BitsGrouped" },
{ 0x0032, 0x1032, 0, VR::PN, VM::M1, "RequestingPhysician" },
{ 0x0040, 0x0001, 0, VR::AE, VM::M1TN, "ScheduledStationAETitle" },
{ 0x0052, 0x0013, 0, VR::FD, VM::M1, "CatheterRotationalRate" },
{ 0x0054, 0x0015, 0, VR::DS, VM::M1, "EnergyWindowUpperLimit" },
{ 0x0066, 0x0027, 0, VR::SQ, VM::M1, "TriangleFanSequence" },
{ 0x1000, 0x0000, 1, VR::US, VM::M3, "EscapeTriplet" },
{ 0x3006, 0x0084, 0, VR::IS, VM::M1, "ReferencedROINumber" },
{ 0x300A, 0x0088, 1, VR::FL, VM::M1, "BeamDosePointDepth" },
{ 0x5000, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue" },
{ 0x5002, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange2" },
{ 0x5010, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue9" },
{ 0x5014, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor11" },
{ 0x5016, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0065[] = {
{ 0x0010, 0x0050, 0, VR::SQ, VM::M1, "PatientInsurancePlanCodeSequence" },
{ 0x0014, 0x0054, 2, VR::DS, VM::M1, "OuterDiameter" },
{ 0x0018, 0x1019, 0, VR::LO, VM::M1TN, "SecondaryCaptureDeviceSoftwareVersions" },
{ 0x0018, 0x9601, 0, VR::SQ, VM::M1, "DiffusionBMatrixSequence" },
{ 0x0020, 0x0060, 0, VR::CS, VM::M1, "Laterality" },
{ 0x0024, 0x0064, 0, VR::SQ, VM::M1, "ResultsNormalsSequence" },
{ 0x0028, 0x0068, 1, VR::US, VM::M1, "RepeatInterval" },
{ 0x0032, 0x1033, 0, VR::LO, VM::M1, "RequestingService" },
{ 0x0044, 0x0004, 0, VR::DT, VM::M1, "ApprovalStatusDateTime" },
{ 0x0048, 0x0008, 0, VR::SQ, VM::M1, "TotalPixelMatrixOriginSequence" },
{ 0x0050, 0x0010, 0, VR::SQ, VM::M1, "DeviceSequence" },
{ 0x0052, 0x0012, 0, VR::US, VM::M1, "ALinesPerFrame" },
{ 0x0054, 0x0014, 0, VR::DS, VM::M1, "EnergyWindowLowerLimit" },
{ 0x0066, 0x0026, 0, VR::SQ, VM::M1, "TriangleStripSequence" },
{ 0x0072, 0x0032, 0, VR::US, VM::M1, "ImageSetNumber" },
{ 0x0072, 0x0422, 0, VR::SQ, VM::M1, "StructuredDisplayImageBoxSequence" },
{ 0x0076, 0x0036, 0, VR::CS, VM::M1, "ExclusiveComponentType" },
{ 0x1000, 0x0001, 1, VR::US, VM::M3, "RunLengthTriplet" },
{ 0x2040, 0x0082, 1, VR::CS, VM::M1, "OverlayBackgroundDensity" },
{ 0x3006, 0x0085, 0, VR::SH, VM::M1, "ROIObservationLabel" },
{ 0x300A, 0x0089, 1, VR::FL, VM::M1, "BeamDosePointEquivalentDepth" },
{ 0x5000, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue" },
{ 0x5006, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0066[] = {
{ 0x0012, 0x0051, 0, VR::ST, VM::M1, "ClinicalTrialTimePointDescription" },
{ 0x0018, 0x101A, 1, VR::LO, VM::M1TN, "HardcopyDeviceSoftwareVersion" },
{ 0x0018, 0x9602, 0, VR::FD, VM::M1, "DiffusionBValueXX" },
{ 0x0024, 0x0067, 0, VR::SQ, VM::M1, "GeneralizedDefectSensitivityDeviationAlgorithmSequence" },
{ 0x0032, 0x1030, 1, VR::LO, VM::M1, "ReasonForStudy" },
{ 0x0040, 0x0003, 0, VR::TM, VM::M1, "ScheduledProcedureStepStartTime" },
{ 0x0044, 0x0007, 0, VR::SQ, VM::M1, "ProductTypeCodeSequence" },
{ 0x0050, 0x0013, 0, VR::FD, VM::M1, "ContainerComponentThickness" },
{ 0x0052, 0x0011, 0, VR::FD, VM::M1, "ALineRate" },
{ 0x0054, 0x0017, 0, VR::IS, VM::M1, "ResidualSyringeCounts" },
{ 0x0066, 0x0025, 0, VR::OW, VM::M1, "VertexPointIndexList" },
{ 0x0072, 0x0421, 0, VR::US, VM::M3, "EmptyImageBoxCIELabValue" },
{ 0x1000, 0x0002, 1, VR::US, VM::M1, "HuffmanTableSize" },
{ 0x3006, 0x0086, 0, VR::SQ, VM::M1, "RTROIIdentificationCodeSequence" },
{ 0x300A, 0x008A, 1, VR::FL, VM::M1, "BeamDosePointSSD" },
{ 0x5000, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange" },
{ 0x5002, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue2" },
{ 0x5012, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue10" },
{ 0x5014, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue11" },
{ 0x5016, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0067[] = {
{ 0x0012, 0x0050, 0, VR::LO, VM::M1, "ClinicalTrialTimePointID" },
{ 0x0014, 0x0056, 2, VR::DS, VM::M1, "InnerDiameter" },
{ 0x0018, 0x101B, 1, VR::LO, VM::M1, "HardcopyDeviceManufacturerModelName" },
{ 0x0018, 0x9603, 0, VR::FD, VM::M1, "DiffusionBValueXY" },
{ 0x0020, 0x0062, 0, VR::CS, VM::M1, "ImageLaterality" },
{ 0x0024, 0x0066, 0, VR::FL, VM::M1, "GlobalDeviationFromNormal" },
{ 0x0032, 0x1031, 0, VR::SQ, VM::M1, "RequestingPhysicianIdentificationSequence" },
{ 0x0040, 0x0002, 0, VR::DA, VM::M1, "ScheduledProcedureStepStartDate" },
{ 0x0050, 0x0012, 0, VR::SQ, VM::M1, "ContainerComponentTypeCodeSequence" },
{ 0x0054, 0x0016, 0, VR::SQ, VM::M1, "RadiopharmaceuticalInformationSequence" },
{ 0x0066, 0x0024, 0, VR::OW, VM::M1, "EdgePointIndexList" },
{ 0x0072, 0x0030, 0, VR::SQ, VM::M1, "TimeBasedImageSetsSequence" },
{ 0x0072, 0x0420, 0, VR::US, VM::M3, "StructuredDisplayBackgroundCIELabValue" },
{ 0x0076, 0x0034, 0, VR::CS, VM::M1, "ComponentTypeCodeSequence" },
{ 0x1000, 0x0003, 1, VR::US, VM::M3, "HuffmanTableTriplet" },
{ 0x2040, 0x0080, 1, VR::CS, VM::M1, "OverlayForegroundDensity" },
{ 0x300A, 0x008B, 0, VR::CS, VM::M1, "BeamDoseMeaning" },
{ 0x5002, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue2" },
{ 0x5004, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0068[] = {
{ 0x0004, 0x1410, 0, VR::US, VM::M1, "RecordInUseFlag" },
{ 0x0014, 0x1010, 2, VR::ST, VM::M1, "ActualEnvironmentalConditions" },
{ 0x0018, 0x9214, 0, VR::CS, VM::M1, "RespiratoryCyclePosition" },
{ 0x0018, 0x9604, 0, VR::FD, VM::M1, "DiffusionBValueXZ" },
{ 0x0022, 0x1436, 0, VR::SQ, VM::M1, "OphthalmicThicknessMapTypeCodeSequence" },
{ 0x0024, 0x0061, 0, VR::CS, VM::M1, "ExcessiveFalsePositivesDataFlag" },
{ 0x0040, 0x0005, 0, VR::TM, VM::M1, "ScheduledProcedureStepEndTime" },
{ 0x0044, 0x0001, 0, VR::ST, VM::M1, "ProductPackageIdentifier" },
{ 0x0050, 0x0015, 0, VR::FD, VM::M1, "ContainerComponentWidth" },
{ 0x0054, 0x0011, 0, VR::US, VM::M1, "NumberOfEnergyWindows" },
{ 0x0066, 0x0023, 0, VR::OW, VM::M1, "TrianglePointIndexList" },
{ 0x0072, 0x0427, 0, VR::SQ, VM::M1, "ReferencedFirstFrameSequence" },
{ 0x1000, 0x0004, 1, VR::US, VM::M1, "ShiftTableSize" },
{ 0x3006, 0x0080, 0, VR::SQ, VM::M1, "RTROIObservationsSequence" },
{ 0x300A, 0x008C, 0, VR::SQ, VM::M1, "BeamDoseVerificationControlPointSequence" },
{ 0x5004, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue3" },
{ 0x5006, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange4" },
{ 0x5010, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor9" },
{ 0x5012, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue10" },
{ 0x5014, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue11" },
{ 0x5400, 0x0110, 0, VR::OX, VM::M1, "ChannelMinimumValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0069[] = {
{ 0x0008, 0x9205, 0, VR::CS, VM::M1, "PixelPresentation" },
{ 0x0014, 0x0050, 2, VR::CS, VM::M1, "ComponentShape" },
{ 0x0018, 0x9605, 0, VR::FD, VM::M1, "DiffusionBValueYY" },
{ 0x0024, 0x0060, 0, VR::US, VM::M1, "FalsePositivesQuantity" },
{ 0x0040, 0x0004, 0, VR::DA, VM::M1, "ScheduledProcedureStepEndDate" },
{ 0x0050, 0x0014, 0, VR::DS, VM::M1, "DeviceLength" },
{ 0x0052, 0x0016, 0, VR::SQ, VM::M1, "ModeOfPercutaneousAccessSequence" },
{ 0x0054, 0x0010, 0, VR::US, VM::M1TN, "EnergyWindowVector" },
{ 0x0054, 0x0400, 0, VR::SH, VM::M1, "ImageID" },
{ 0x0076, 0x0032, 0, VR::SQ, VM::M1, "ComponentTypesSequence" },
{ 0x1000, 0x0005, 1, VR::US, VM::M3, "ShiftTableTriplet" },
{ 0x300A, 0x008D, 0, VR::FL, VM::M1, "AverageBeamDosePointDepth" },
{ 0x5002, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation2" },
{ 0x5004, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0070[] = {
{ 0x0008, 0x9206, 0, VR::CS, VM::M1, "VolumetricProperties" },
{ 0x0018, 0x9606, 0, VR::FD, VM::M1, "DiffusionBValueYZ" },
{ 0x0022, 0x1024, 0, VR::SQ, VM::M1, "LensStatusCodeSequence" },
{ 0x0024, 0x0063, 0, VR::CS, VM::M1, "VisualFieldTestNormalsFlag" },
{ 0x0032, 0x1034, 0, VR::SQ, VM::M1, "RequestingServiceCodeSequence" },
{ 0x0040, 0x0007, 0, VR::LO, VM::M1, "ScheduledProcedureStepDescription" },
{ 0x0044, 0x0003, 0, VR::LT, VM::M1, "ApprovalStatusFurtherDescription" },
{ 0x0050, 0x0017, 0, VR::CS, VM::M1, "DeviceDiameterUnits" },
{ 0x0054, 0x0013, 0, VR::SQ, VM::M1, "EnergyWindowRangeSequence" },
{ 0x0066, 0x0021, 0, VR::OF, VM::M1, "VectorCoordinateData" },
{ 0x3006, 0x0082, 0, VR::IS, VM::M1, "ObservationNumber" },
{ 0x300A, 0x008E, 0, VR::FL, VM::M1, "AverageBeamDosePointEquivalentDepth" },
{ 0x5004, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange3" },
{ 0x5006, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue4" },
{ 0x5010, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue9" },
{ 0x5012, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor10" },
{ 0x5016, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue12" },
{ 0x5400, 0x0112, 0, VR::OX, VM::M1, "ChannelMaximumValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0071[] = {
{ 0x0008, 0x9207, 0, VR::CS, VM::M1, "VolumeBasedCalculationTechnique" },
{ 0x0014, 0x0052, 2, VR::CS, VM::M1, "CurvatureType" },
{ 0x0018, 0x9217, 0, VR::FD, VM::M1, "VelocityEncodingMaximumValue" },
{ 0x0018, 0x9607, 0, VR::FD, VM::M1, "DiffusionBValueZZ" },
{ 0x0022, 0x1025, 0, VR::SQ, VM::M1, "VitreousStatusCodeSequence" },
{ 0x0024, 0x0062, 0, VR::CS, VM::M1, "ExcessiveFalsePositives" },
{ 0x0040, 0x0006, 0, VR::PN, VM::M1, "ScheduledPerformingPhysicianName" },
{ 0x0044, 0x0002, 0, VR::CS, VM::M1, "SubstanceAdministrationApproval" },
{ 0x0050, 0x0016, 0, VR::DS, VM::M1, "DeviceDiameter" },
{ 0x0052, 0x0014, 0, VR::FD, VM::M1, "ALinePixelSpacing" },
{ 0x0054, 0x0012, 0, VR::SQ, VM::M1, "EnergyWindowInformationSequence" },
{ 0x0066, 0x0020, 0, VR::FL, VM::M1TN, "VectorAccuracy" },
{ 0x0072, 0x0034, 0, VR::CS, VM::M1, "ImageSetSelectorCategory" },
{ 0x0072, 0x0424, 0, VR::SQ, VM::M1, "StructuredDisplayTextBoxSequence" },
{ 0x0076, 0x0030, 0, VR::LO, VM::M1, "SurgicalTechnique" },
{ 0x300A, 0x008F, 0, VR::FL, VM::M1, "AverageBeamDosePointSSD" },
{ 0x5000, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation" },
{ 0x5006, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0072[] = {
{ 0x0008, 0x0041, 1, VR::LO, VM::M1, "DataSetSubtype" },
{ 0x0008, 0x1000, 1, VR::AE, VM::M1, "NetworkID" },
{ 0x0008, 0x9208, 0, VR::CS, VM::M1, "ComplexImageComponent" },
{ 0x0018, 0x1010, 0, VR::LO, VM::M1, "SecondaryCaptureDeviceID" },
{ 0x0018, 0x1400, 0, VR::LO, VM::M1, "AcquisitionDeviceProcessingDescription" },
{ 0x0018, 0x9218, 0, VR::FD, VM::M1, "TagSpacingSecondDimension" },
{ 0x0028, 0x0061, 1, VR::SH, VM::M1, "CompressionOriginator" },
{ 0x0040, 0x0009, 0, VR::SH, VM::M1, "ScheduledProcedureStepID" },
{ 0x0048, 0x0001, 0, VR::FL, VM::M1, "ImagedVolumeWidth" },
{ 0x0050, 0x0019, 0, VR::DS, VM::M1, "InterMarkerDistance" },
{ 0x0066, 0x002F, 0, VR::SQ, VM::M1, "AlgorithmFamilyCodeSequence" },
{ 0x3008, 0x0082, 0, VR::IS, VM::M1, "ReferencedMeasuredDoseReferenceNumber" },
{ 0x300A, 0x0080, 0, VR::IS, VM::M1, "NumberOfBeams" },
{ 0x5008, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue5" },
{ 0x500A, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange6" },
{ 0x5018, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue13" },
{ 0x501C, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor15" },
{ 0x501E, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0073[] = {
{ 0x0008, 0x0040, 1, VR::US, VM::M1, "DataSetType" },
{ 0x0008, 0x9209, 0, VR::CS, VM::M1, "AcquisitionContrast" },
{ 0x0018, 0x0050, 0, VR::DS, VM::M1, "SliceThickness" },
{ 0x0018, 0x1011, 1, VR::LO, VM::M1, "HardcopyCreationDeviceID" },
{ 0x0018, 0x1401, 0, VR::LO, VM::M1, "AcquisitionDeviceProcessingCode" },
{ 0x0018, 0x9219, 0, VR::SS, VM::M1, "TagAngleSecondAxis" },
{ 0x0020, 0x9221, 0, VR::SQ, VM::M1, "DimensionOrganizationSequence" },
{ 0x0028, 0x0060, 1, VR::CS, VM::M1, "CompressionCode" },
{ 0x0040, 0x0008, 0, VR::SQ, VM::M1, "ScheduledProtocolCodeSequence" },
{ 0x0050, 0x0018, 0, VR::DS, VM::M1, "DeviceVolume" },
{ 0x0066, 0x002E, 0, VR::SQ, VM::M1, "SegmentSurfaceSourceInstanceSequence" },
{ 0x0072, 0x003A, 0, VR::CS, VM::M1, "RelativeTimeUnits" },
{ 0x5008, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue5" },
{ 0x500E, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0074[] = {
{ 0x0018, 0x1012, 0, VR::DA, VM::M1, "DateOfSecondaryCapture" },
{ 0x0018, 0x1402, 0, VR::CS, VM::M1, "CassetteOrientation" },
{ 0x0020, 0x9222, 0, VR::SQ, VM::M1, "DimensionIndexSequence" },
{ 0x0022, 0x1028, 0, VR::SQ, VM::M1, "IOLFormulaCodeSequence" },
{ 0x0028, 0x0063, 1, VR::SH, VM::M1, "CompressionDescription" },
{ 0x0040, 0x000B, 0, VR::SQ, VM::M1, "ScheduledPerformingPhysicianIdentificationSequence" },
{ 0x0048, 0x0003, 0, VR::FL, VM::M1, "ImagedVolumeDepth" },
{ 0x0050, 0x001B, 0, VR::LO, VM::M1, "ContainerComponentID" },
{ 0x0066, 0x002D, 0, VR::SQ, VM::M1, "SegmentSurfaceGenerationAlgorithmIdentificationSequence" },
{ 0x3008, 0x0080, 0, VR::SQ, VM::M1, "ReferencedMeasuredDoseReferenceSequence" },
{ 0x300A, 0x0082, 0, VR::DS, VM::M3, "BeamDoseSpecificationPoint" },
{ 0x5008, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange5" },
{ 0x500A, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue6" },
{ 0x501A, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue14" },
{ 0x501C, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue15" },
{ 0x501E, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0075[] = {
{ 0x0008, 0x0042, 1, VR::CS, VM::M1, "NuclearMedicineSeriesType" },
{ 0x0018, 0x1403, 0, VR::CS, VM::M1, "CassetteSize" },
{ 0x0022, 0x1029, 0, VR::LO, VM::M1, "IOLFormulaDetail" },
{ 0x0028, 0x0062, 1, VR::LO, VM::M1, "CompressionLabel" },
{ 0x0040, 0x000A, 0, VR::SQ, VM::M1, "StageCodeSequence" },
{ 0x0048, 0x0002, 0, VR::FL, VM::M1, "ImagedVolumeHeight" },
{ 0x0050, 0x001A, 0, VR::CS, VM::M1, "ContainerComponentMaterial" },
{ 0x0066, 0x002C, 0, VR::UL, VM::M1, "ReferencedSurfaceNumber" },
{ 0x0072, 0x0038, 0, VR::US, VM::M2, "RelativeTime" },
{ 0x500A, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue6" },
{ 0x500C, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0076[] = {
{ 0x0018, 0x1014, 0, VR::TM, VM::M1, "TimeOfSecondaryCapture" },
{ 0x0018, 0x1404, 0, VR::US, VM::M1, "ExposuresOnPlate" },
{ 0x0024, 0x0069, 0, VR::LO, VM::M1, "PatientReliabilityIndicator" },
{ 0x0028, 0x0065, 1, VR::CS, VM::M1TN, "CompressionSequence" },
{ 0x0044, 0x0009, 0, VR::LT, VM::M1, "ProductDescription" },
{ 0x0050, 0x001D, 0, VR::FD, VM::M1, "ContainerComponentDiameter" },
{ 0x0066, 0x002B, 0, VR::SQ, VM::M1, "ReferencedSurfaceSequence" },
{ 0x3006, 0x0088, 0, VR::ST, VM::M1, "ROIObservationDescription" },
{ 0x300A, 0x0084, 0, VR::DS, VM::M1, "BeamDose" },
{ 0x500C, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue7" },
{ 0x500E, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange8" },
{ 0x5018, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor13" },
{ 0x501A, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue14" },
{ 0x501C, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0077[] = {
{ 0x0018, 0x1405, 0, VR::IS, VM::M1, "RelativeXRayExposure" },
{ 0x0024, 0x0068, 0, VR::FL, VM::M1, "LocalizedDeviationFromNormal" },
{ 0x0044, 0x0008, 0, VR::LO, VM::M1TN, "ProductName" },
{ 0x0050, 0x001C, 0, VR::FD, VM::M1, "ContainerComponentLength" },
{ 0x0054, 0x0018, 0, VR::SH, VM::M1, "EnergyWindowName" },
{ 0x0066, 0x002A, 0, VR::UL, VM::M1, "SurfaceCount" },
{ 0x0072, 0x003E, 0, VR::SQ, VM::M1, "AbstractPriorCodeSequence" },
{ 0x500A, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation6" },
{ 0x500C, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0078[] = {
{ 0x0018, 0x1016, 0, VR::LO, VM::M1, "SecondaryCaptureDeviceManufacturer" },
{ 0x0044, 0x000B, 0, VR::DT, VM::M1, "ProductExpirationDateTime" },
{ 0x0048, 0x0007, 0, VR::UL, VM::M1, "TotalPixelMatrixRows" },
{ 0x0066, 0x0029, 0, VR::OW, VM::M1, "PrimitivePointIndexList" },
{ 0x300A, 0x0086, 0, VR::DS, VM::M1, "BeamMeterset" },
{ 0x300C, 0x0080, 0, VR::SQ, VM::M1, "ReferencedDoseSequence" },
{ 0x500C, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange7" },
{ 0x500E, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue8" },
{ 0x5018, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue13" },
{ 0x501A, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor14" },
{ 0x501E, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0079[] = {
{ 0x0014, 0x3099, 2, VR::LT, VM::M1, "CalibrationNotes" },
{ 0x0018, 0x1017, 1, VR::LO, VM::M1, "HardcopyDeviceManufacturer" },
{ 0x0028, 0x0066, 1, VR::AT, VM::M1TN, "CompressionStepPointers" },
{ 0x0044, 0x000A, 0, VR::LO, VM::M1, "ProductLotIdentifier" },
{ 0x0048, 0x0006, 0, VR::UL, VM::M1, "TotalPixelMatrixColumns" },
{ 0x0050, 0x001E, 0, VR::LO, VM::M1, "ContainerComponentDescription" },
{ 0x0066, 0x0028, 0, VR::SQ, VM::M1, "LineSequence" },
{ 0x0068, 0x65B0, 0, VR::FD, VM::M4, "TwoDLineCoordinates" },
{ 0x0072, 0x003C, 0, VR::SS, VM::M2, "AbstractPriorValue" },
{ 0x0076, 0x0038, 0, VR::CS, VM::M1, "MandatoryComponentType" },
{ 0x5008, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation5" },
{ 0x500E, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0080[] = {
{ 0x0010, 0x1000, 0, VR::LO, VM::M1TN, "OtherPatientIDs" },
{ 0x0014, 0x0045, 1, VR::ST, VM::M1TN, "MaterialPropertiesFileFormatRetired" },
{ 0x0018, 0x1008, 0, VR::LO, VM::M1, "GantryID" },
{ 0x0018, 0x9200, 0, VR::CS, VM::M1, "MRSpectroscopyAcquisitionType" },
{ 0x0020, 0x9238, 0, VR::LO, VM::M1, "FunctionalGroupPrivateCreator" },
{ 0x0024, 0x0075, 0, VR::FL, VM::M1, "ShortTermFluctuation" },
{ 0x0040, 0x0011, 0, VR::SH, VM::M1, "ScheduledProcedureStepLocation" },
{ 0x0042, 0x0013, 0, VR::SQ, VM::M1, "SourceInstanceSequence" },
{ 0x0052, 0x0003, 0, VR::FD, VM::M1, "BeamSpotSize" },
{ 0x0066, 0x0037, 0, VR::FL, VM::M1, "RecommendedPointRadius" },
{ 0x0070, 0x0021, 0, VR::US, VM::M1, "NumberOfGraphicPoints" },
{ 0x1010, 0x0000, 1, VR::US, VM::M1TN, "ZonalMap" },
{ 0x5000, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue" },
{ 0x5004, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor3" },
{ 0x5006, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue4" },
{ 0x5010, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue9" },
{ 0x5012, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0081[] = {
{ 0x0008, 0x0058, 0, VR::UI, VM::M1TN, "FailedSOPInstanceUIDList" },
{ 0x0010, 0x0040, 0, VR::CS, VM::M1, "PatientSex" },
{ 0x0010, 0x1001, 0, VR::PN, VM::M1TN, "OtherPatientNames" },
{ 0x0012, 0x0042, 0, VR::LO, VM::M1, "ClinicalTrialSubjectReadingID" },
{ 0x0014, 0x0044, 2, VR::ST, VM::M1TN, "MaterialPropertiesDescription" },
{ 0x0020, 0x0070, 1, VR::LO, VM::M1, "ImageGeometryType" },
{ 0x0022, 0x1033, 0, VR::FL, VM::M1, "KeratometerIndex" },
{ 0x0022, 0x1423, 0, VR::SQ, VM::M1, "AcquisitionMethodAlgorithmSequence" },
{ 0x0024, 0x0074, 0, VR::CS, VM::M1, "ShortTermFluctuationCalculated" },
{ 0x0040, 0x0010, 0, VR::SH, VM::M1TN, "ScheduledStationName" },
{ 0x0040, 0x0400, 0, VR::LT, VM::M1, "CommentsOnTheScheduledProcedureStep" },
{ 0x0040, 0xA29A, 1, VR::SL, VM::M2T2N, "PixelCoordinatesSetTrial" },
{ 0x0042, 0x0012, 0, VR::LO, VM::M1, "MIMETypeOfEncapsulatedDocument" },
{ 0x0046, 0x0016, 0, VR::SQ, VM::M1, "UnspecifiedLateralityLensSequence" },
{ 0x0052, 0x0002, 0, VR::FD, VM::M1, "OCTFocalDistance" },
{ 0x0054, 0x0414, 0, VR::SQ, VM::M1, "PatientGantryRelationshipCodeSequence" },
{ 0x0066, 0x0036, 0, VR::LO, VM::M1, "AlgorithmName" },
{ 0x0070, 0x0020, 0, VR::US, VM::M1, "GraphicDimensions" },
{ 0x0072, 0x0022, 0, VR::SQ, VM::M1, "ImageSetSelectorSequence" },
{ 0x0072, 0x0432, 0, VR::US, VM::M2TN, "SynchronizedImageBoxList" },
{ 0x0078, 0x0028, 0, VR::SQ, VM::M1, "ImplantTemplateGroupTargetAnatomySequence" },
{ 0x5010, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue9" },
{ 0x5016, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0082[] = {
{ 0x0010, 0x1002, 0, VR::SQ, VM::M1, "OtherPatientIDsSequence" },
{ 0x0022, 0x1420, 0, VR::SQ, VM::M1, "AcquisitionMethodCodeSequence" },
{ 0x0024, 0x0077, 0, VR::FL, VM::M1, "ShortTermFluctuationProbability" },
{ 0x0032, 0x1020, 1, VR::LO, VM::M1, "ScheduledStudyLocation" },
{ 0x0042, 0x0011, 0, VR::OB, VM::M1, "EncapsulatedDocument" },
{ 0x0046, 0x0015, 0, VR::SQ, VM::M1, "LeftLensSequence" },
{ 0x0052, 0x0001, 0, VR::FL, VM::M1, "ContrastBolusIngredientPercentByVolume" },
{ 0x0066, 0x0035, 0, VR::SQ, VM::M1, "SurfaceProcessingAlgorithmIdentificationSequence" },
{ 0x0070, 0x0023, 0, VR::CS, VM::M1, "GraphicType" },
{ 0x5002, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue2" },
{ 0x5004, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue3" },
{ 0x5006, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor4" },
{ 0x5010, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange9" },
{ 0x5012, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0083[] = {
{ 0x0012, 0x0040, 0, VR::LO, VM::M1, "ClinicalTrialSubjectID" },
{ 0x0014, 0x0046, 2, VR::LT, VM::M1, "MaterialNotes" },
{ 0x0024, 0x0076, 0, VR::CS, VM::M1, "ShortTermFluctuationProbabilityCalculated" },
{ 0x0032, 0x1021, 1, VR::AE, VM::M1TN, "ScheduledStudyLocationAETitle" },
{ 0x0040, 0x0012, 0, VR::LO, VM::M1, "PreMedication" },
{ 0x0042, 0x0010, 0, VR::ST, VM::M1, "DocumentTitle" },
{ 0x0046, 0x0014, 0, VR::SQ, VM::M1, "RightLensSequence" },
{ 0x0066, 0x0034, 0, VR::SQ, VM::M1, "FacetSequence" },
{ 0x0070, 0x0022, 0, VR::FL, VM::M2TN, "GraphicData" },
{ 0x0072, 0x0020, 0, VR::SQ, VM::M1, "ImageSetsSequence" },
{ 0x0072, 0x0430, 0, VR::SQ, VM::M1, "ImageBoxSynchronizationSequence" },
{ 0x0078, 0x002A, 0, VR::SQ, VM::M1, "ImplantTemplateGroupMembersSequence" },
{ 0x2040, 0x0090, 1, VR::CS, VM::M1, "OverlayMode" },
{ 0x5012, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue10" },
{ 0x5014, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0084[] = {
{ 0x0004, 0x1400, 0, VR::UL, VM::M1, "OffsetOfTheNextDirectoryRecord" },
{ 0x0024, 0x0071, 0, VR::FL, VM::M1, "GlobalDeviationProbability" },
{ 0x0044, 0x0011, 0, VR::LO, VM::M1, "SubstanceAdministrationNotes" },
{ 0x0052, 0x0007, 0, VR::FD, VM::M1, "OCTOpticalCenterWavelength" },
{ 0x5000, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor" },
{ 0x5002, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue2" },
{ 0x5004, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue3" },
{ 0x5014, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue11" },
{ 0x5016, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange12" },
{ 0x5400, 0x0100, 0, VR::SQ, VM::M1, "WaveformSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0085[] = {
{ 0x0008, 0x9215, 0, VR::SQ, VM::M1, "DerivationCodeSequence" },
{ 0x0010, 0x1005, 0, VR::PN, VM::M1, "PatientBirthName" },
{ 0x0022, 0x1037, 0, VR::FL, VM::M1, "TargetRefraction" },
{ 0x0024, 0x0070, 0, VR::FL, VM::M1, "VisualFieldMeanSensitivity" },
{ 0x0028, 0x9235, 0, VR::CS, VM::M1, "SignalDomainRows" },
{ 0x0044, 0x0010, 0, VR::DT, VM::M1, "SubstanceAdministrationDateTime" },
{ 0x0046, 0x0012, 0, VR::LO, VM::M1, "LensDescription" },
{ 0x0050, 0x0004, 0, VR::CS, VM::M1, "CalibrationImage" },
{ 0x0052, 0x0006, 0, VR::CS, VM::M1, "OCTAcquisitionDomain" },
{ 0x0054, 0x0410, 0, VR::SQ, VM::M1, "PatientOrientationCodeSequence" },
{ 0x0066, 0x0032, 0, VR::LT, VM::M1, "AlgorithmParameters" },
{ 0x0070, 0x0024, 0, VR::CS, VM::M1, "GraphicFilled" },
{ 0x0072, 0x0026, 0, VR::AT, VM::M1, "SelectorAttribute" },
{ 0x5012, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation10" },
{ 0x5014, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0086[] = {
{ 0x0014, 0x3080, 2, VR::OB, VM::M1, "BadPixelImage" },
{ 0x0024, 0x0073, 0, VR::FL, VM::M1, "LocalizedDeviationProbability" },
{ 0x0044, 0x0013, 0, VR::SQ, VM::M1, "ProductParameterSequence" },
{ 0x0066, 0x0031, 0, VR::LO, VM::M1, "AlgorithmVersion" },
{ 0x5000, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue" },
{ 0x5002, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor2" },
{ 0x5006, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue4" },
{ 0x5014, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange11" },
{ 0x5016, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0087[] = {
{ 0x0014, 0x0042, 2, VR::ST, VM::M1TN, "MaterialGrade" },
{ 0x0022, 0x1035, 0, VR::SQ, VM::M1, "SourceOfOphthalmicAxialLengthCodeSequence" },
{ 0x0024, 0x0072, 0, VR::CS, VM::M1, "LocalDeviationProbabilityNormalsFlag" },
{ 0x0042, 0x0014, 0, VR::LO, VM::M1TN, "ListOfMIMETypes" },
{ 0x0044, 0x0012, 0, VR::LO, VM::M1, "SubstanceAdministrationDeviceID" },
{ 0x0052, 0x0004, 0, VR::FD, VM::M1, "EffectiveRefractiveIndex" },
{ 0x0054, 0x0412, 0, VR::SQ, VM::M1, "PatientOrientationModifierCodeSequence" },
{ 0x0066, 0x0030, 0, VR::SQ, VM::M1, "AlgorithmNameCodeSequence" },
{ 0x0072, 0x0024, 0, VR::CS, VM::M1, "ImageSetSelectorUsageFlag" },
{ 0x0072, 0x0434, 0, VR::CS, VM::M1, "TypeOfSynchronization" },
{ 0x0076, 0x0020, 0, VR::SQ, VM::M1, "ProcedureTypeCodeSequence" },
{ 0x0078, 0x002E, 0, VR::US, VM::M1, "ImplantTemplateGroupMemberID" },
{ 0x5010, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation9" },
{ 0x5016, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0088[] = {
{ 0x0008, 0x0051, 0, VR::SQ, VM::M1, "IssuerOfAccessionNumberSequence" },
{ 0x0008, 0x1010, 0, VR::SH, VM::M1, "StationName" },
{ 0x0018, 0x1000, 0, VR::LO, VM::M1, "DeviceSerialNumber" },
{ 0x0018, 0x5104, 0, VR::SQ, VM::M1, "ProjectionEponymousNameCodeSequence" },
{ 0x0028, 0x0071, 1, VR::XS, VM::M1, "PerimeterValue" },
{ 0x0038, 0x0061, 1, VR::LO, VM::M1, "IssuerOfServiceEpisodeID" },
{ 0x0048, 0x0011, 0, VR::CS, VM::M1, "FocusMethod" },
{ 0x3008, 0x0092, 0, VR::IS, VM::M1, "ReferencedCalculatedDoseReferenceNumber" },
{ 0x5008, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue5" },
{ 0x500C, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor7" },
{ 0x500E, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue8" },
{ 0x5018, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue13" },
{ 0x501A, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0089[] = {
{ 0x0008, 0x0050, 0, VR::SH, VM::M1, "AccessionNumber" },
{ 0x0018, 0x0040, 0, VR::IS, VM::M1, "CineRate" },
{ 0x0018, 0x1411, 0, VR::DS, VM::M1, "ExposureIndex" },
{ 0x0028, 0x0070, 1, VR::US, VM::M1TN, "PerimeterTable" },
{ 0x0038, 0x0060, 0, VR::LO, VM::M1, "ServiceEpisodeID" },
{ 0x0048, 0x0010, 0, VR::CS, VM::M1, "SpecimenLabelInImage" },
{ 0x0078, 0x0020, 0, VR::LO, VM::M1, "ImplantTemplateGroupIssuer" },
{ 0x5018, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue13" },
{ 0x501E, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0090[] = {
{ 0x0008, 0x0053, 0, VR::CS, VM::M1, "QueryRetrieveView" },
{ 0x0018, 0x1002, 0, VR::UI, VM::M1, "DeviceUID" },
{ 0x0018, 0x1412, 0, VR::DS, VM::M1, "TargetExposureIndex" },
{ 0x0048, 0x0013, 0, VR::US, VM::M1, "NumberOfFocalPlanes" },
{ 0x0052, 0x0009, 0, VR::FD, VM::M1, "RangingDepth" },
{ 0x3008, 0x0090, 0, VR::SQ, VM::M1, "ReferencedCalculatedDoseReferenceSequence" },
{ 0x500A, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue6" },
{ 0x500C, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue7" },
{ 0x500E, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor8" },
{ 0x5018, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange13" },
{ 0x501A, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0091[] = {
{ 0x0008, 0x0052, 0, VR::CS, VM::M1, "QueryRetrieveLevel" },
{ 0x0018, 0x0042, 0, VR::CS, VM::M1, "InitialCineRunState" },
{ 0x0018, 0x1003, 0, VR::LO, VM::M1, "DeviceID" },
{ 0x0018, 0x1413, 0, VR::DS, VM::M1, "DeviationIndex" },
{ 0x0022, 0x1039, 0, VR::CS, VM::M1, "RefractiveProcedureOccurred" },
{ 0x0038, 0x0062, 0, VR::LO, VM::M1, "ServiceEpisodeDescription" },
{ 0x0040, 0xA290, 1, VR::CS, VM::M1, "CoordinatesSetGeometricTypeTrial" },
{ 0x0048, 0x0012, 0, VR::CS, VM::M1, "ExtendedDepthOfField" },
{ 0x0052, 0x0008, 0, VR::FD, VM::M1, "AxialResolution" },
{ 0x0072, 0x0028, 0, VR::US, VM::M1, "SelectorValueNumber" },
{ 0x501A, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue14" },
{ 0x501C, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0092[] = {
{ 0x0018, 0x1004, 0, VR::LO, VM::M1, "PlateID" },
{ 0x0018, 0x5100, 0, VR::CS, VM::M1, "PatientPosition" },
{ 0x0024, 0x0079, 0, VR::FL, VM::M1, "CorrectedLocalizedDeviationFromNormal" },
{ 0x0040, 0xA297, 1, VR::ST, VM::M1, "AlgorithmDescriptionTrial" },
{ 0x0044, 0x0019, 0, VR::SQ, VM::M1, "SubstanceAdministrationParameterSequence" },
{ 0x0048, 0x0015, 0, VR::US, VM::M3, "RecommendedAbsentPixelCIELabValue" },
{ 0x5008, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor5" },
{ 0x500A, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue6" },
{ 0x500C, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue7" },
{ 0x501C, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue15" },
{ 0x501E, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0093[] = {
{ 0x0008, 0x0054, 0, VR::AE, VM::M1TN, "RetrieveAETitle" },
{ 0x0018, 0x1005, 0, VR::LO, VM::M1, "GeneratorID" },
{ 0x0018, 0x5101, 0, VR::CS, VM::M1, "ViewPosition" },
{ 0x0024, 0x0078, 0, VR::CS, VM::M1, "CorrectedLocalizedDeviationFromNormalCalculated" },
{ 0x0038, 0x0064, 0, VR::SQ, VM::M1, "IssuerOfServiceEpisodeIDSequence" },
{ 0x0040, 0xA296, 1, VR::SQ, VM::M1, "AlgorithmCodeSequenceTrial" },
{ 0x0048, 0x0014, 0, VR::FL, VM::M1, "DistanceBetweenFocalPlanes" },
{ 0x0078, 0x0024, 0, VR::LO, VM::M1, "ImplantTemplateGroupVersion" },
{ 0x501A, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation14" },
{ 0x501C, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0094[] = {
{ 0x0018, 0x1006, 0, VR::LO, VM::M1, "GridID" },
{ 0x5008, 0x0112, 1, VR::US, VM::M1TN, "CoordinateStartValue5" },
{ 0x500A, 0x0110, 1, VR::US, VM::M1TN, "CurveDataDescriptor6" },
{ 0x500E, 0x0114, 1, VR::US, VM::M1TN, "CoordinateStepValue8" },
{ 0x501C, 0x0106, 1, VR::SH, VM::M1TN, "CurveRange15" },
{ 0x501E, 0x0104, 1, VR::US, VM::M1TN, "MinimumCoordinateValue16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0095[] = {
{ 0x0008, 0x0056, 0, VR::CS, VM::M1, "InstanceAvailability" },
{ 0x0018, 0x1007, 0, VR::LO, VM::M1, "CassetteID" },
{ 0x0040, 0xDB73, 0, VR::UL, VM::M1TN, "ReferencedContentItemIdentifier" },
{ 0x0046, 0x0018, 0, VR::SQ, VM::M1, "CylinderSequence" },
{ 0x0066, 0x0038, 0, VR::FL, VM::M1, "RecommendedLineThickness" },
{ 0x0068, 0x65A0, 0, VR::SQ, VM::M1, "TwoDLineCoordinatesSequence" },
{ 0x0078, 0x0026, 0, VR::SQ, VM::M1, "ReplacedImplantTemplateGroupSequence" },
{ 0x5018, 0x0103, 1, VR::US, VM::M1, "DataValueRepresentation13" },
{ 0x501E, 0x0105, 1, VR::US, VM::M1TN, "MaximumCoordinateValue16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0096[] = {
{ 0x0010, 0x1030, 0, VR::DS, VM::M1, "PatientWeight" },
{ 0x0020, 0x1000, 1, VR::IS, VM::M1, "SeriesInStudy" },
{ 0x0024, 0x0045, 0, VR::CS, VM::M1, "FalseNegativesEstimateFlag" },
{ 0x0040, 0x1060, 1, VR::LO, VM::M1, "RequestedProcedureDescriptionTrial" },
{ 0x0052, 0x0033, 0, VR::FD, VM::M1, "SeamLineLocation" },
{ 0x0062, 0x0003, 0, VR::SQ, VM::M1, "SegmentedPropertyCategoryCodeSequence" },
{ 0x0064, 0x0005, 0, VR::SQ, VM::M1, "DeformableRegistrationGridSequence" },
{ 0x0070, 0x0011, 0, VR::FL, VM::M2, "BoundingBoxBottomRightHandCorner" },
{ 0x0070, 0x0401, 0, VR::US, VM::M3, "GraphicLayerRecommendedDisplayCIELabValue" },
{ 0x0074, 0x1054, 0, VR::UL, VM::M1, "AttributeItemSelector" },
{ 0x3006, 0x00A4, 0, VR::CS, VM::M1, "RTROIInterpretedType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0097[] = {
{ 0x0008, 0x0068, 0, VR::CS, VM::M1, "PresentationIntentType" },
{ 0x0012, 0x0072, 0, VR::LO, VM::M1, "ClinicalTrialSeriesDescription" },
{ 0x0018, 0x9231, 0, VR::US, VM::M1, "MRAcquisitionPhaseEncodingStepsInPlane" },
{ 0x0020, 0x1001, 1, VR::IS, VM::M1, "AcquisitionsInSeries" },
{ 0x0022, 0x0042, 0, VR::SQ, VM::M1, "MydriaticAgentConcentrationUnitsSequence" },
{ 0x0024, 0x0044, 0, VR::LT, VM::M1, "CommentsOnPatientPerformanceOfVisualField" },
{ 0x0040, 0x0020, 0, VR::CS, VM::M1, "ScheduledProcedureStepStatus" },
{ 0x0062, 0x0002, 0, VR::SQ, VM::M1, "SegmentSequence" },
{ 0x0070, 0x0010, 0, VR::FL, VM::M2, "BoundingBoxTopLeftHandCorner" },
{ 0x0072, 0x0012, 0, VR::SQ, VM::M1, "SourceHangingProtocolSequence" },
{ 0x0072, 0x0402, 0, VR::CS, VM::M1, "FilterByCategory" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0098[] = {
{ 0x0012, 0x0071, 0, VR::LO, VM::M1, "ClinicalTrialSeriesID" },
{ 0x0018, 0x9232, 0, VR::US, VM::M1, "MRAcquisitionPhaseEncodingStepsOutOfPlane" },
{ 0x0020, 0x1002, 0, VR::IS, VM::M1, "ImagesInAcquisition" },
{ 0x0022, 0x0041, 0, VR::FL, VM::M1, "DepthOfTransverseImage" },
{ 0x0032, 0x1010, 1, VR::DA, VM::M1, "ScheduledStudyStopDate" },
{ 0x0052, 0x0031, 0, VR::CS, VM::M1, "CatheterDirectionOfRotation" },
{ 0x0062, 0x0001, 0, VR::CS, VM::M1, "SegmentationType" },
{ 0x0064, 0x0007, 0, VR::UL, VM::M3, "GridDimensions" },
{ 0x0070, 0x0403, 0, VR::FL, VM::M1, "RelativeOpacity" },
{ 0x0074, 0x1056, 0, VR::LO, VM::M1, "AttributeOccurrencePrivateCreator" },
{ 0x3006, 0x00A6, 0, VR::PN, VM::M1, "ROIInterpreter" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0099[] = {
{ 0x0020, 0x1003, 1, VR::IS, VM::M1, "ImagesInSeries" },
{ 0x0024, 0x0046, 0, VR::FL, VM::M1, "FalseNegativesEstimate" },
{ 0x0032, 0x1011, 1, VR::TM, VM::M1, "ScheduledStudyStopTime" },
{ 0x0052, 0x0030, 0, VR::SS, VM::M1, "OCTZOffsetCorrection" },
{ 0x0054, 0x0036, 0, VR::IS, VM::M1, "PhaseDelay" },
{ 0x0066, 0x0004, 0, VR::LT, VM::M1, "SurfaceComments" },
{ 0x0070, 0x0012, 0, VR::CS, VM::M1, "BoundingBoxTextHorizontalJustification" },
{ 0x0070, 0x0402, 0, VR::SQ, VM::M1, "BlendingSequence" },
{ 0x0072, 0x0010, 0, VR::LO, VM::M1, "HangingProtocolUserGroupName" },
{ 0x0072, 0x0400, 0, VR::SQ, VM::M1, "FilterOperationsSequence" },
{ 0x0074, 0x1057, 0, VR::IS, VM::M1TN, "SelectorSequencePointerItems" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0100[] = {
{ 0x0004, 0x1430, 0, VR::CS, VM::M1, "DirectoryRecordType" },
{ 0x0018, 0x9234, 0, VR::UL, VM::M1, "SpectroscopyAcquisitionPhaseColumns" },
{ 0x0020, 0x1004, 1, VR::IS, VM::M1, "AcquisitionsInStudy" },
{ 0x0054, 0x0031, 0, VR::US, VM::M1, "NumberOfPhases" },
{ 0x0066, 0x0003, 0, VR::UL, VM::M1, "SurfaceNumber" },
{ 0x0070, 0x0015, 0, VR::CS, VM::M1, "AnchorPointVisibility" },
{ 0x0070, 0x0405, 0, VR::CS, VM::M1, "BlendingPosition" },
{ 0x0074, 0x1050, 0, VR::SQ, VM::M1, "AttributeOccurrenceSequence" },
{ 0x3006, 0x00A0, 0, VR::SQ, VM::M1, "RelatedRTROIObservationsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0101[] = {
{ 0x0020, 0x1005, 1, VR::IS, VM::M1, "ImagesInStudy" },
{ 0x0022, 0x1007, 0, VR::SQ, VM::M1, "OphthalmicAxialMeasurementsRightEyeSequence" },
{ 0x0024, 0x0040, 0, VR::CS, VM::M1, "ExcessiveFixationLosses" },
{ 0x0052, 0x0036, 0, VR::US, VM::M1, "SeamLineIndex" },
{ 0x0054, 0x0030, 0, VR::US, VM::M1TN, "PhaseVector" },
{ 0x0062, 0x0006, 0, VR::ST, VM::M1, "SegmentDescription" },
{ 0x0066, 0x0002, 0, VR::SQ, VM::M1, "SurfaceSequence" },
{ 0x0070, 0x0014, 0, VR::FL, VM::M2, "AnchorPoint" },
{ 0x0070, 0x0404, 0, VR::SQ, VM::M1, "ReferencedSpatialRegistrationSequence" },
{ 0x0072, 0x0406, 0, VR::CS, VM::M1, "FilterByOperator" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0102[] = {
{ 0x0004, 0x1432, 0, VR::UI, VM::M1, "PrivateRecordUID" },
{ 0x0018, 0x9236, 0, VR::CS, VM::M1, "CardiacCyclePosition" },
{ 0x0040, 0x0027, 0, VR::SQ, VM::M1, "OrderFillerIdentifierSequence" },
{ 0x0054, 0x0033, 0, VR::US, VM::M1, "NumberOfFramesInPhase" },
{ 0x0062, 0x0005, 0, VR::LO, VM::M1, "SegmentLabel" },
{ 0x0064, 0x0003, 0, VR::UI, VM::M1, "SourceFrameOfReferenceUID" },
{ 0x0066, 0x0001, 0, VR::UL, VM::M1, "NumberOfSurfaces" },
{ 0x0074, 0x1052, 0, VR::AT, VM::M1, "AttributeOccurrencePointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0103[] = {
{ 0x0022, 0x1415, 0, VR::CS, VM::M1, "OphthalmicMappingDeviceType" },
{ 0x0024, 0x0042, 0, VR::US, VM::M1, "StimuliRetestingQuantity" },
{ 0x0040, 0x0026, 0, VR::SQ, VM::M1, "OrderPlacerIdentifierSequence" },
{ 0x0052, 0x0034, 0, VR::FD, VM::M1, "FirstALineLocation" },
{ 0x0054, 0x0032, 0, VR::SQ, VM::M1, "PhaseInformationSequence" },
{ 0x0062, 0x0004, 0, VR::US, VM::M1, "SegmentNumber" },
{ 0x0064, 0x0002, 0, VR::SQ, VM::M1, "DeformableRegistrationSequence" },
{ 0x0072, 0x0014, 0, VR::US, VM::M1, "NumberOfPriorsReferenced" },
{ 0x0072, 0x0404, 0, VR::CS, VM::M1, "FilterByAttributePresence" },
{ 0x0076, 0x0010, 0, VR::SQ, VM::M1, "ImplantAssemblyTemplateTargetAnatomySequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0104[] = {
{ 0x0008, 0x0061, 0, VR::CS, VM::M1TN, "ModalitiesInStudy" },
{ 0x0018, 0x0071, 0, VR::CS, VM::M1, "AcquisitionTerminationCondition" },
{ 0x0018, 0x1030, 0, VR::LO, VM::M1, "ProtocolName" },
{ 0x0028, 0x1410, 0, VR::CS, VM::M1, "AlphaLUTTransferFunction" },
{ 0x0062, 0x000B, 0, VR::US, VM::M1TN, "ReferencedSegmentNumber" },
{ 0x300A, 0x00A0, 0, VR::IS, VM::M1, "NumberOfBrachyApplicationSetups" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0105[] = {
{ 0x0008, 0x0060, 0, VR::CS, VM::M1, "Modality" },
{ 0x0018, 0x0070, 0, VR::IS, VM::M1, "CountsAccumulated" },
{ 0x0018, 0x9239, 0, VR::SQ, VM::M1, "SpecificAbsorptionRateSequence" },
{ 0x0028, 0x0040, 1, VR::CS, VM::M1, "ImageFormat" },
{ 0x0038, 0x0050, 0, VR::LO, VM::M1, "SpecialNeeds" },
{ 0x0052, 0x003A, 0, VR::CS, VM::M1, "RefractiveIndexApplied" },
{ 0x0062, 0x000A, 0, VR::SQ, VM::M1, "SegmentIdentificationSequence" },
{ 0x0066, 0x000E, 0, VR::CS, VM::M1, "FiniteVolume" },
{ 0x0078, 0x0010, 0, VR::ST, VM::M1, "ImplantTemplateGroupDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0106[] = {
{ 0x0018, 0x0073, 0, VR::CS, VM::M1, "AcquisitionStartCondition" },
{ 0x0022, 0x0049, 0, VR::FL, VM::M1, "MaximumAcrossScanDistortion" },
{ 0x0022, 0x1008, 0, VR::SQ, VM::M1, "OphthalmicAxialMeasurementsLeftEyeSequence" },
{ 0x0052, 0x0039, 0, VR::CS, VM::M1, "InterpolationType" },
{ 0x0062, 0x0009, 0, VR::LO, VM::M1, "SegmentAlgorithmName" },
{ 0x0064, 0x000F, 0, VR::SQ, VM::M1, "PreDeformationMatrixRegistrationSequence" },
{ 0x0066, 0x000D, 0, VR::CS, VM::M1, "RecommendedPresentationType" },
{ 0x3008, 0x00A0, 0, VR::SQ, VM::M1, "BeamLimitingDeviceLeafPairsSequence" },
{ 0x300A, 0x00A2, 0, VR::DS, VM::M3, "BrachyApplicationSetupDoseSpecificationPoint" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0107[] = {
{ 0x0008, 0x0062, 0, VR::UI, VM::M1TN, "SOPClassesInStudy" },
{ 0x0018, 0x0072, 0, VR::DS, VM::M1, "EffectiveDuration" },
{ 0x0022, 0x0048, 0, VR::FL, VM::M1, "AcrossScanSpatialResolution" },
{ 0x0022, 0x1009, 0, VR::CS, VM::M1, "OphthalmicAxialMeasurementsDeviceType" },
{ 0x0052, 0x0038, 0, VR::US, VM::M1, "NumberOfPaddedALines" },
{ 0x0062, 0x0008, 0, VR::CS, VM::M1, "SegmentAlgorithmType" },
{ 0x0066, 0x000C, 0, VR::FL, VM::M1, "RecommendedPresentationOpacity" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0108[] = {
{ 0x0018, 0x0075, 0, VR::IS, VM::M1, "AcquisitionTerminationConditionData" },
{ 0x0054, 0x0039, 0, VR::CS, VM::M1, "PhaseDescription" },
{ 0x0062, 0x000F, 0, VR::SQ, VM::M1, "SegmentedPropertyTypeCodeSequence" },
{ 0x0064, 0x0009, 0, VR::OF, VM::M1, "VectorGridData" },
{ 0x0066, 0x000B, 0, VR::LO, VM::M1, "SurfaceProcessingDescription" },
{ 0x300A, 0x00A4, 0, VR::DS, VM::M1, "BrachyApplicationSetupDose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0109[] = {
{ 0x0008, 0x0064, 0, VR::CS, VM::M1, "ConversionType" },
{ 0x0018, 0x0074, 0, VR::IS, VM::M1, "AcquisitionStartConditionData" },
{ 0x0022, 0x004E, 0, VR::DS, VM::M1, "MydriaticAgentConcentration" },
{ 0x0024, 0x0048, 0, VR::US, VM::M1, "NegativeCatchTrialsQuantity" },
{ 0x0054, 0x0038, 0, VR::IS, VM::M1, "PauseBetweenFrames" },
{ 0x0062, 0x000E, 0, VR::US, VM::M1, "MaximumFractionalValue" },
{ 0x0064, 0x0008, 0, VR::FD, VM::M3, "GridResolution" },
{ 0x0066, 0x000A, 0, VR::FL, VM::M1, "SurfaceProcessingRatio" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0110[] = {
{ 0x0062, 0x000D, 0, VR::US, VM::M3, "RecommendedDisplayCIELabValue" },
{ 0x0066, 0x0009, 0, VR::CS, VM::M1, "SurfaceProcessing" },
{ 0x300C, 0x00A0, 0, VR::IS, VM::M1, "ReferencedToleranceTableNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0111[] = {
{ 0x0046, 0x0028, 0, VR::SQ, VM::M1, "PrismSequence" },
{ 0x0062, 0x000C, 0, VR::US, VM::M1, "RecommendedDisplayGrayscaleValue" },
{ 0x0068, 0x6590, 0, VR::FD, VM::M3, "ThreeDPointCoordinates" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0112[] = {
{ 0x0010, 0x1020, 0, VR::DS, VM::M1, "PatientSize" },
{ 0x0012, 0x0063, 0, VR::LO, VM::M1TN, "DeidentificationMethod" },
{ 0x0018, 0x9220, 0, VR::FD, VM::M1, "FrameAcquisitionDuration" },
{ 0x0022, 0x1012, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthSequence" },
{ 0x0024, 0x0055, 0, VR::CS, VM::M1, "CatchTrialsDataFlag" },
{ 0x0028, 0x1408, 0, VR::OW, VM::M1, "BlendingLookupTableData" },
{ 0x0040, 0x0031, 0, VR::UT, VM::M1, "LocalNamespaceEntityID" },
{ 0x0066, 0x0017, 0, VR::FL, VM::M3, "PointPositionAccuracy" },
{ 0x0070, 0x0001, 0, VR::SQ, VM::M1, "GraphicAnnotationSequence" },
{ 0x0074, 0x1044, 0, VR::SQ, VM::M1, "ConventionalMachineVerificationSequence" },
{ 0x3006, 0x00B4, 0, VR::DS, VM::M1, "ROIPhysicalPropertyValue" },
{ 0x300A, 0x00B8, 0, VR::CS, VM::M1, "RTBeamLimitingDeviceType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0113[] = {
{ 0x0010, 0x1021, 0, VR::SQ, VM::M1, "PatientSizeCodeSequence" },
{ 0x0012, 0x0062, 0, VR::CS, VM::M1, "PatientIdentityRemoved" },
{ 0x0020, 0x0050, 1, VR::DS, VM::M1, "Location" },
{ 0x0024, 0x0054, 0, VR::FL, VM::M1, "FalsePositivesEstimate" },
{ 0x0046, 0x0036, 0, VR::CS, VM::M1, "VerticalPrismBase" },
{ 0x0050, 0x0020, 0, VR::LO, VM::M1, "DeviceDescription" },
{ 0x0062, 0x0012, 0, VR::SQ, VM::M1, "UsedSegmentsSequence" },
{ 0x0066, 0x0016, 0, VR::OF, VM::M1, "PointCoordinatesData" },
{ 0x0072, 0x0002, 0, VR::SH, VM::M1, "HangingProtocolName" },
{ 0x0076, 0x0006, 0, VR::LO, VM::M1, "ImplantAssemblyTemplateVersion" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0114[] = {
{ 0x0022, 0x1010, 0, VR::CS, VM::M1, "OphthalmicAxialLengthMeasurementsType" },
{ 0x0024, 0x0057, 0, VR::CS, VM::M1, "TestPointNormalsDataFlag" },
{ 0x0032, 0x1000, 1, VR::DA, VM::M1, "ScheduledStudyStartDate" },
{ 0x0040, 0x0033, 0, VR::CS, VM::M1, "UniversalEntityIDType" },
{ 0x0062, 0x0011, 0, VR::SQ, VM::M1, "SegmentedPropertyTypeModifierCodeSequence" },
{ 0x0066, 0x0015, 0, VR::UL, VM::M1, "NumberOfSurfacePoints" },
{ 0x0070, 0x0003, 0, VR::CS, VM::M1, "BoundingBoxAnnotationUnits" },
{ 0x0074, 0x1046, 0, VR::SQ, VM::M1, "IonMachineVerificationSequence" },
{ 0x3006, 0x00B6, 0, VR::SQ, VM::M1, "ROIElementalCompositionSequence" },
{ 0x300A, 0x00BA, 0, VR::DS, VM::M1, "SourceToBeamLimitingDeviceDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0115[] = {
{ 0x0012, 0x0060, 0, VR::LO, VM::M1, "ClinicalTrialCoordinatingCenterName" },
{ 0x0020, 0x0052, 0, VR::UI, VM::M1, "FrameOfReferenceUID" },
{ 0x0024, 0x0056, 0, VR::US, VM::M1, "PositiveCatchTrialsQuantity" },
{ 0x0028, 0x140B, 0, VR::SQ, VM::M1, "EnhancedPaletteColorLookupTableSequence" },
{ 0x0032, 0x1001, 1, VR::TM, VM::M1, "ScheduledStudyStartTime" },
{ 0x0040, 0x0032, 0, VR::UT, VM::M1, "UniversalEntityID" },
{ 0x0046, 0x0034, 0, VR::FD, VM::M1, "VerticalPrismPower" },
{ 0x0062, 0x0010, 0, VR::CS, VM::M1, "SegmentationFractionalType" },
{ 0x0070, 0x0002, 0, VR::CS, VM::M1, "GraphicLayer" },
{ 0x3006, 0x00B7, 0, VR::US, VM::M1, "ROIElementalCompositionAtomicNumber" },
{ 0x300A, 0x00BB, 0, VR::FL, VM::M1, "IsocenterToBeamLimitingDeviceDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0116[] = {
{ 0x0004, 0x1420, 0, VR::UL, VM::M1, "OffsetOfReferencedLowerLevelDirectoryEntity" },
{ 0x0014, 0x1020, 2, VR::DA, VM::M1, "ExpiryDate" },
{ 0x0022, 0x0057, 0, VR::FL, VM::M1, "IlluminationBandwidth" },
{ 0x0024, 0x0051, 0, VR::CS, VM::M1, "ExcessiveFalseNegativesDataFlag" },
{ 0x0028, 0x140C, 0, VR::SQ, VM::M1, "BlendingLUT2Sequence" },
{ 0x0040, 0x0035, 0, VR::CS, VM::M1, "IdentifierTypeCode" },
{ 0x0052, 0x0027, 0, VR::SQ, VM::M1, "IntravascularFrameContentSequence" },
{ 0x0054, 0x0021, 0, VR::US, VM::M1, "NumberOfDetectors" },
{ 0x0066, 0x0013, 0, VR::SQ, VM::M1, "SurfaceMeshPrimitivesSequence" },
{ 0x0070, 0x0005, 0, VR::CS, VM::M1, "GraphicAnnotationUnits" },
{ 0x0074, 0x1040, 0, VR::SQ, VM::M1, "RelatedReferenceRTImageSequence" },
{ 0x0076, 0x0003, 0, VR::LO, VM::M1, "ImplantAssemblyTemplateIssuer" },
{ 0x3006, 0x00B0, 0, VR::SQ, VM::M1, "ROIPhysicalPropertiesSequence" },
{ 0x300A, 0x00BC, 0, VR::IS, VM::M1, "NumberOfLeafJawPairs" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0117[] = {
{ 0x0022, 0x0056, 0, VR::FL, VM::M1, "IlluminationPower" },
{ 0x0024, 0x0050, 0, VR::US, VM::M1, "FalseNegativesQuantity" },
{ 0x0028, 0x140D, 0, VR::CS, VM::M1, "BlendingLUT2TransferFunction" },
{ 0x0046, 0x0032, 0, VR::CS, VM::M1, "HorizontalPrismBase" },
{ 0x0052, 0x0026, 0, VR::CS, VM::M1, "OCTZOffsetApplied" },
{ 0x0054, 0x0020, 0, VR::US, VM::M1TN, "DetectorVector" },
{ 0x0064, 0x0010, 0, VR::SQ, VM::M1, "PostDeformationMatrixRegistrationSequence" },
{ 0x0066, 0x0012, 0, VR::SQ, VM::M1, "SurfacePointsNormalsSequence" },
{ 0x0070, 0x0004, 0, VR::CS, VM::M1, "AnchorPointAnnotationUnits" },
{ 0x0072, 0x0006, 0, VR::CS, VM::M1, "HangingProtocolLevel" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0118[] = {
{ 0x0008, 0x103E, 0, VR::LO, VM::M1, "SeriesDescription" },
{ 0x0018, 0x9226, 0, VR::SQ, VM::M1, "MRImageFrameTypeSequence" },
{ 0x0022, 0x0055, 0, VR::FL, VM::M1, "IlluminationWaveLength" },
{ 0x0024, 0x0053, 0, VR::CS, VM::M1, "FalsePositivesEstimateFlag" },
{ 0x0028, 0x005F, 1, VR::LO, VM::M1, "CompressionRecognitionCode" },
{ 0x0028, 0x140E, 0, VR::CS, VM::M1, "DataPathID" },
{ 0x0052, 0x0025, 0, VR::SQ, VM::M1, "IntravascularOCTFrameTypeSequence" },
{ 0x0066, 0x0011, 0, VR::SQ, VM::M1, "SurfacePointsSequence" },
{ 0x0074, 0x1042, 0, VR::SQ, VM::M1, "GeneralMachineVerificationSequence" },
{ 0x0076, 0x0001, 0, VR::LO, VM::M1, "ImplantAssemblyTemplateName" },
{ 0x3006, 0x00B2, 0, VR::CS, VM::M1, "ROIPhysicalProperty" },
{ 0x300A, 0x00BE, 0, VR::DS, VM::M3TN, "LeafPositionBoundaries" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0119[] = {
{ 0x0008, 0x103F, 0, VR::SQ, VM::M1, "SeriesDescriptionCodeSequence" },
{ 0x0008, 0x9237, 0, VR::SQ, VM::M1, "ReferencedPresentationStateSequence" },
{ 0x0012, 0x0064, 0, VR::SQ, VM::M1, "DeidentificationMethodCodeSequence" },
{ 0x0018, 0x9227, 0, VR::SQ, VM::M1, "MRSpectroscopyFrameTypeSequence" },
{ 0x0024, 0x0052, 0, VR::CS, VM::M1, "ExcessiveFalseNegatives" },
{ 0x0028, 0x140F, 0, VR::CS, VM::M1, "RGBLUTTransferFunction" },
{ 0x0040, 0x0036, 0, VR::SQ, VM::M1, "AssigningFacilitySequence" },
{ 0x0046, 0x0030, 0, VR::FD, VM::M1, "HorizontalPrismPower" },
{ 0x0054, 0x0022, 0, VR::SQ, VM::M1, "DetectorInformationSequence" },
{ 0x0066, 0x0010, 0, VR::CS, VM::M1, "Manifold" },
{ 0x0070, 0x0006, 0, VR::ST, VM::M1, "UnformattedTextValue" },
{ 0x0072, 0x0004, 0, VR::LO, VM::M1, "HangingProtocolDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0120[] = {
{ 0x0008, 0x1030, 0, VR::LO, VM::M1, "StudyDescription" },
{ 0x0018, 0x1020, 0, VR::LO, VM::M1TN, "SoftwareVersions" },
{ 0x0018, 0x1800, 0, VR::CS, VM::M1, "AcquisitionTimeSynchronized" },
{ 0x0028, 0x0051, 0, VR::CS, VM::M1TN, "CorrectedImage" },
{ 0x0040, 0x0039, 0, VR::SQ, VM::M1, "AssigningJurisdictionCodeSequence" },
{ 0x0066, 0x001F, 0, VR::US, VM::M1, "VectorDimensionality" },
{ 0x0070, 0x0009, 0, VR::SQ, VM::M1, "GraphicObjectSequence" },
{ 0x0074, 0x104C, 0, VR::SQ, VM::M1, "ConventionalControlPointVerificationSequence" },
{ 0x0078, 0x0001, 0, VR::LO, VM::M1, "ImplantTemplateGroupName" },
{ 0x300A, 0x00B0, 0, VR::SQ, VM::M1, "BeamSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0121[] = {
{ 0x0008, 0x0070, 0, VR::LO, VM::M1, "Manufacturer" },
{ 0x0018, 0x0060, 0, VR::DS, VM::M1, "KVP" },
{ 0x0018, 0x1801, 0, VR::SH, VM::M1, "TimeSource" },
{ 0x0028, 0x0050, 1, VR::LO, VM::M1TN, "ManipulatedImage" },
{ 0x0028, 0x1401, 0, VR::SQ, VM::M1, "DataFrameAssignmentSequence" },
{ 0x0038, 0x0040, 1, VR::LO, VM::M1, "DischargeDiagnosisDescription" },
{ 0x0066, 0x001E, 0, VR::UL, VM::M1, "NumberOfVectors" },
{ 0x0070, 0x0008, 0, VR::SQ, VM::M1, "TextObjectSequence" },
{ 0x0072, 0x000A, 0, VR::DT, VM::M1, "HangingProtocolCreationDateTime" },
{ 0x0076, 0x000E, 0, VR::SQ, VM::M1, "DerivationImplantAssemblyTemplateSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0122[] = {
{ 0x0008, 0x1032, 0, VR::SQ, VM::M1, "ProcedureCodeSequence" },
{ 0x0018, 0x1022, 0, VR::SH, VM::M1, "VideoImageFormatAcquired" },
{ 0x0018, 0x1802, 0, VR::CS, VM::M1, "TimeDistributionProtocol" },
{ 0x0028, 0x1402, 0, VR::CS, VM::M1, "DataPathAssignment" },
{ 0x0052, 0x0029, 0, VR::SQ, VM::M1, "IntravascularOCTFrameContentSequence" },
{ 0x0074, 0x104E, 0, VR::SQ, VM::M1, "IonControlPointVerificationSequence" },
{ 0x3008, 0x00B0, 0, VR::SQ, VM::M1, "RecordedWedgeSequence" },
{ 0x300A, 0x00B2, 0, VR::SH, VM::M1, "TreatmentMachineName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0123[] = {
{ 0x0018, 0x1023, 0, VR::LO, VM::M1, "DigitalImageFormatAcquired" },
{ 0x0018, 0x1803, 0, VR::LO, VM::M1, "NTPSourceAddress" },
{ 0x0020, 0x9213, 0, VR::LO, VM::M1, "DimensionIndexPrivateCreator" },
{ 0x0022, 0x0058, 0, VR::SQ, VM::M1, "MydriaticAgentSequence" },
{ 0x0022, 0x1019, 0, VR::FL, VM::M1, "OphthalmicAxialLength" },
{ 0x0028, 0x1403, 0, VR::US, VM::M1, "BitsMappedToColorLookupTable" },
{ 0x0040, 0x003A, 0, VR::SQ, VM::M1, "AssigningAgencyOrDepartmentCodeSequence" },
{ 0x0052, 0x0028, 0, VR::FD, VM::M1, "IntravascularLongitudinalDistance" },
{ 0x0066, 0x001C, 0, VR::FL, VM::M3, "CenterOfRotation" },
{ 0x0072, 0x0008, 0, VR::LO, VM::M1, "HangingProtocolCreator" },
{ 0x0076, 0x000C, 0, VR::SQ, VM::M1, "OriginalImplantAssemblyTemplateSequence" },
{ 0x300A, 0x00B3, 0, VR::CS, VM::M1, "PrimaryDosimeterUnit" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0124[] = {
{ 0x0024, 0x0059, 0, VR::CS, VM::M1, "GlobalDeviationProbabilityNormalsFlag" },
{ 0x0028, 0x1404, 0, VR::SQ, VM::M1, "BlendingLUT1Sequence" },
{ 0x0066, 0x001B, 0, VR::FL, VM::M3, "AxisOfRotation" },
{ 0x0074, 0x1048, 0, VR::SQ, VM::M1, "FailedAttributesSequence" },
{ 0x3006, 0x00B8, 0, VR::FL, VM::M1, "ROIElementalCompositionAtomicMassFraction" },
{ 0x300A, 0x00B4, 0, VR::DS, VM::M1, "SourceAxisDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0125[] = {
{ 0x0024, 0x0058, 0, VR::SQ, VM::M1, "TestPointNormalsSequence" },
{ 0x0028, 0x1405, 0, VR::CS, VM::M1, "BlendingLUT1TransferFunction" },
{ 0x0038, 0x0044, 1, VR::SQ, VM::M1, "DischargeDiagnosisCodeSequence" },
{ 0x0066, 0x001A, 0, VR::FL, VM::M6, "PointsBoundingBoxCoordinates" },
{ 0x0072, 0x000E, 0, VR::SQ, VM::M1, "HangingProtocolUserIdentificationCodeSequence" },
{ 0x0076, 0x000A, 0, VR::CS, VM::M1, "ImplantAssemblyTemplateType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0126[] = {
{ 0x0028, 0x1406, 0, VR::FD, VM::M1, "BlendingWeightConstant" },
{ 0x0066, 0x0019, 0, VR::FL, VM::M1, "MaximumPointDistance" },
{ 0x0074, 0x104A, 0, VR::SQ, VM::M1, "OverriddenAttributesSequence" },
{ 0x300A, 0x00B6, 0, VR::SQ, VM::M1, "BeamLimitingDeviceSequence" },
{ 0x300C, 0x00B0, 0, VR::SQ, VM::M1, "ReferencedBolusSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0127[] = {
{ 0x0028, 0x1407, 0, VR::US, VM::M3, "BlendingLookupTableDescriptor" },
{ 0x0046, 0x0038, 0, VR::CS, VM::M1, "LensSegmentType" },
{ 0x0066, 0x0018, 0, VR::FL, VM::M1, "MeanPointDistance" },
{ 0x0072, 0x000C, 0, VR::SQ, VM::M1, "HangingProtocolDefinitionSequence" },
{ 0x0076, 0x0008, 0, VR::SQ, VM::M1, "ReplacedImplantAssemblyTemplateSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0128[] = {
{ 0x0014, 0x2014, 2, VR::IS, VM::M1, "IndicationNumber" },
{ 0x0040, 0x3001, 0, VR::LO, VM::M1, "ConfidentialityConstraintOnPatientDataDescription" },
{ 0x0080, 0x0002, 0, VR::SQ, VM::M1, "SurfaceScanModeCodeSequence" },
{ 0x2010, 0x0010, 0, VR::ST, VM::M1, "ImageDisplayFormat" },
{ 0x2020, 0x0020, 0, VR::CS, VM::M1, "Polarity" },
{ 0x300A, 0x004B, 0, VR::FL, VM::M1, "SnoutPositionTolerance" },
{ 0x6000, 0x4000, 1, VR::LT, VM::M1, "OverlayComments" },
{ 0x6004, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated3" },
{ 0x6006, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition4" },
{ 0x6014, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0129[] = {
{ 0x0060, 0x3020, 0, VR::UL, VM::M1TN, "HistogramData" },
{ 0x0080, 0x0003, 0, VR::SQ, VM::M1, "RegistrationMethodCodeSequence" },
{ 0x3002, 0x0042, 0, VR::DS, VM::M1, "FluenceDataScale" },
{ 0x3006, 0x0046, 0, VR::IS, VM::M1, "NumberOfContourPoints" },
{ 0x3008, 0x0048, 0, VR::DS, VM::M1, "DoseRateDelivered" },
{ 0x300A, 0x004A, 0, VR::DS, VM::M1, "BeamLimitingDevicePositionTolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0130[] = {
{ 0x0014, 0x2016, 2, VR::SH, VM::M1, "IndicationLabel" },
{ 0x3002, 0x0041, 0, VR::CS, VM::M1, "FluenceDataSource" },
{ 0x3006, 0x0045, 0, VR::DS, VM::M3, "ContourOffsetVector" },
{ 0x6002, 0x4000, 1, VR::LT, VM::M1, "OverlayComments2" },
{ 0x6004, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition3" },
{ 0x6006, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated4" },
{ 0x6016, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0131[] = {
{ 0x0080, 0x0001, 0, VR::SQ, VM::M1, "SurfaceScanAcquisitionTypeCodeSequence" },
{ 0x3002, 0x0040, 0, VR::SQ, VM::M1, "FluenceMapSequence" },
{ 0x3006, 0x0044, 0, VR::DS, VM::M1, "ContourSlabThickness" },
{ 0x300A, 0x0048, 0, VR::SQ, VM::M1, "BeamLimitingDeviceToleranceSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0132[] = {
{ 0x0080, 0x0006, 0, VR::US, VM::M1TN, "SurfacePointPresentationValueData" },
{ 0x300A, 0x004F, 0, VR::FL, VM::M1, "TableTopPitchAngleTolerance" },
{ 0x6000, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated" },
{ 0x6002, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition2" },
{ 0x6004, 0x4000, 1, VR::LT, VM::M1, "OverlayComments3" },
{ 0x6010, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0133[] = {
{ 0x0014, 0x3050, 2, VR::OX, VM::M1, "DarkCurrentCounts" },
{ 0x0080, 0x0007, 0, VR::US, VM::M3T3N, "SurfacePointColorCIELabValueData" },
{ 0x3004, 0x0040, 0, VR::DS, VM::M3, "DVHNormalizationPoint" },
{ 0x3006, 0x0042, 0, VR::CS, VM::M1, "ContourGeometricType" },
{ 0x300A, 0x004E, 0, VR::DS, VM::M1, "TableTopEccentricAngleTolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0134[] = {
{ 0x0014, 0x2012, 2, VR::SQ, VM::M1, "IndicationSequence" },
{ 0x0080, 0x0004, 0, VR::FD, VM::M1, "ShotDurationTime" },
{ 0x6000, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition" },
{ 0x6002, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated2" },
{ 0x6006, 0x4000, 1, VR::LT, VM::M1, "OverlayComments4" },
{ 0x6012, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0135[] = {
{ 0x0080, 0x0005, 0, VR::FD, VM::M1, "ShotOffsetTime" },
{ 0x3004, 0x0042, 0, VR::DS, VM::M1, "DVHNormalizationDoseValue" },
{ 0x3006, 0x0040, 0, VR::SQ, VM::M1, "ContourSequence" },
{ 0x300A, 0x004C, 0, VR::DS, VM::M1, "PatientSupportAngleTolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0136[] = {
{ 0x0008, 0x0082, 0, VR::SQ, VM::M1, "InstitutionCodeSequence" },
{ 0x0014, 0x201C, 2, VR::CS, VM::M1, "IndicationDisposition" },
{ 0x0018, 0x2010, 0, VR::DS, VM::M2, "NominalScannedPixelSpacing" },
{ 0x0020, 0x00AA, 1, VR::IS, VM::M1, "ReportNumber" },
{ 0x0040, 0x08EA, 0, VR::SQ, VM::M1, "MeasurementUnitsCodeSequence" },
{ 0x3008, 0x0041, 0, VR::SQ, VM::M1, "IonControlPointDeliverySequence" },
{ 0x300A, 0x0043, 0, VR::SH, VM::M1, "ToleranceTableLabel" },
{ 0x6008, 0x4000, 1, VR::LT, VM::M1, "OverlayComments5" },
{ 0x600C, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated7" },
{ 0x600E, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition8" },
{ 0x601C, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0137[] = {
{ 0x0018, 0x0093, 0, VR::DS, VM::M1, "PercentSampling" },
{ 0x3008, 0x0040, 0, VR::SQ, VM::M1, "ControlPointDeliverySequence" },
{ 0x300A, 0x0042, 0, VR::IS, VM::M1, "ToleranceTableNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0138[] = {
{ 0x0008, 0x0080, 0, VR::LO, VM::M1, "InstitutionName" },
{ 0x0014, 0x201E, 2, VR::SQ, VM::M1, "IndicationROISequence" },
{ 0x0018, 0x0090, 0, VR::DS, VM::M1, "DataCollectionDiameter" },
{ 0x0080, 0x0008, 0, VR::SQ, VM::M1, "UVMappingSequence" },
{ 0x600A, 0x4000, 1, VR::LT, VM::M1, "OverlayComments6" },
{ 0x600C, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition7" },
{ 0x600E, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated8" },
{ 0x601E, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0139[] = {
{ 0x0008, 0x0081, 0, VR::ST, VM::M1, "InstitutionAddress" },
{ 0x0018, 0x0091, 0, VR::IS, VM::M1, "EchoTrainLength" },
{ 0x0080, 0x0009, 0, VR::SH, VM::M1, "TextureLabel" },
{ 0x3008, 0x0042, 0, VR::DS, VM::M1, "SpecifiedMeterset" },
{ 0x300A, 0x0040, 0, VR::SQ, VM::M1, "ToleranceTableSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0140[] = {
{ 0x0014, 0x2018, 2, VR::ST, VM::M1, "IndicationDescription" },
{ 0x0028, 0x6120, 0, VR::SS, VM::M1, "TIDOffset" },
{ 0x3008, 0x0045, 0, VR::FL, VM::M1, "MetersetRateSet" },
{ 0x6008, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated5" },
{ 0x600A, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition6" },
{ 0x600C, 0x4000, 1, VR::LT, VM::M1, "OverlayComments7" },
{ 0x6018, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0141[] = {
{ 0x3008, 0x0044, 0, VR::DS, VM::M1, "DeliveredMeterset" },
{ 0x300A, 0x0046, 0, VR::DS, VM::M1, "BeamLimitingDeviceAngleTolerance" },
{ 0x300C, 0x0040, 0, VR::SQ, VM::M1, "ReferencedVerificationImageSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0142[] = {
{ 0x0014, 0x201A, 2, VR::CS, VM::M1TN, "IndicationType" },
{ 0x0018, 0x0094, 0, VR::DS, VM::M1, "PercentPhaseFieldOfView" },
{ 0x3006, 0x0049, 0, VR::IS, VM::M1TN, "AttachedContours" },
{ 0x3008, 0x0047, 0, VR::FL, VM::M1TN, "ScanSpotMetersetsDelivered" },
{ 0x6008, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition5" },
{ 0x600A, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated6" },
{ 0x600E, 0x4000, 1, VR::LT, VM::M1, "OverlayComments8" },
{ 0x601A, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0143[] = {
{ 0x0018, 0x0095, 0, VR::DS, VM::M1, "PixelBandwidth" },
{ 0x3006, 0x0048, 0, VR::IS, VM::M1, "ContourNumber" },
{ 0x3008, 0x0046, 0, VR::FL, VM::M1, "MetersetRateDelivered" },
{ 0x300A, 0x0044, 0, VR::DS, VM::M1, "GantryAngleTolerance" },
{ 0x300C, 0x0042, 0, VR::SQ, VM::M1, "ReferencedReferenceImageSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0144[] = {
{ 0x0010, 0x2000, 0, VR::LO, VM::M1TN, "MedicalAlerts" },
{ 0x0014, 0x2004, 2, VR::IS, VM::M1, "EvaluatorNumber" },
{ 0x0080, 0x0012, 0, VR::SQ, VM::M1, "ReferencedTextureSequence" },
{ 0x2000, 0x0010, 0, VR::IS, VM::M1, "NumberOfCopies" },
{ 0x2020, 0x0030, 0, VR::DS, VM::M1, "RequestedImageSize" },
{ 0x2030, 0x0020, 0, VR::LO, VM::M1, "TextString" },
{ 0x2100, 0x0500, 1, VR::SQ, VM::M1, "ReferencedPrintJobSequencePullStoredPrint" },
{ 0x6004, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat3" },
{ 0x6010, 0x4000, 1, VR::LT, VM::M1, "OverlayComments9" },
{ 0x6014, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated11" },
{ 0x6016, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0145[] = {
{ 0x0012, 0x0081, 0, VR::LO, VM::M1, "ClinicalTrialProtocolEthicsCommitteeName" },
{ 0x0080, 0x0013, 0, VR::SQ, VM::M1, "ReferencedSurfaceDataSequence" },
{ 0x3002, 0x0052, 0, VR::SH, VM::M1, "FluenceModeID" },
{ 0x3004, 0x0054, 0, VR::CS, VM::M1, "DVHVolumeUnits" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0146[] = {
{ 0x0012, 0x0082, 0, VR::LO, VM::M1, "ClinicalTrialProtocolEthicsCommitteeApprovalNumber" },
{ 0x0014, 0x2006, 2, VR::PN, VM::M1, "EvaluatorName" },
{ 0x0018, 0x0088, 0, VR::DS, VM::M1, "SpacingBetweenSlices" },
{ 0x0080, 0x0010, 0, VR::OF, VM::M1TN, "UValueData" },
{ 0x3002, 0x0051, 0, VR::CS, VM::M1, "FluenceMode" },
{ 0x6006, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat4" },
{ 0x6012, 0x4000, 1, VR::LT, VM::M1, "OverlayComments10" },
{ 0x6014, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition11" },
{ 0x6016, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0147[] = {
{ 0x0012, 0x0083, 0, VR::SQ, VM::M1, "ConsentForClinicalTrialUseSequence" },
{ 0x0018, 0x0089, 0, VR::IS, VM::M1, "NumberOfPhaseEncodingSteps" },
{ 0x0080, 0x0011, 0, VR::OF, VM::M1TN, "VValueData" },
{ 0x3002, 0x0050, 0, VR::SQ, VM::M1, "PrimaryFluenceModeSequence" },
{ 0x3004, 0x0056, 0, VR::IS, VM::M1, "DVHNumberOfBins" },
{ 0x3008, 0x005A, 0, VR::IS, VM::M1, "NumberOfFractionsDelivered" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0148[] = {
{ 0x0012, 0x0084, 0, VR::CS, VM::M1, "DistributionType" },
{ 0x6000, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat" },
{ 0x6010, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated9" },
{ 0x6012, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition10" },
{ 0x6014, 0x4000, 1, VR::LT, VM::M1, "OverlayComments11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0149[] = {
{ 0x0012, 0x0085, 0, VR::CS, VM::M1, "ConsentForDistributionFlag" },
{ 0x0014, 0x3040, 2, VR::SQ, VM::M1, "DarkCurrentSequence" },
{ 0x3004, 0x0050, 0, VR::SQ, VM::M1, "DVHSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0150[] = {
{ 0x0014, 0x2002, 2, VR::SQ, VM::M1, "EvaluatorSequence" },
{ 0x6002, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat2" },
{ 0x6010, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition9" },
{ 0x6012, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated10" },
{ 0x6016, 0x4000, 1, VR::LT, VM::M1, "OverlayComments12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0151[] = {
{ 0x3004, 0x0052, 0, VR::DS, VM::M1, "DVHDoseScaling" },
{ 0x3006, 0x0050, 0, VR::DS, VM::M3T3N, "ContourData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0152[] = {
{ 0x0008, 0x0092, 0, VR::ST, VM::M1, "ReferringPhysicianAddress" },
{ 0x0018, 0x0082, 0, VR::DS, VM::M1, "InversionTime" },
{ 0x300A, 0x0053, 0, VR::DS, VM::M1, "TableTopLateralPositionTolerance" },
{ 0x300C, 0x0055, 0, VR::SQ, VM::M1, "BrachyReferencedDoseReferenceSequence" },
{ 0x600C, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat7" },
{ 0x6018, 0x4000, 1, VR::LT, VM::M1, "OverlayComments13" },
{ 0x601C, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated15" },
{ 0x601E, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0153[] = {
{ 0x0018, 0x0083, 0, VR::DS, VM::M1, "NumberOfAverages" },
{ 0x0018, 0x2001, 0, VR::IS, VM::M1TN, "PageNumberVector" },
{ 0x3008, 0x0050, 0, VR::SQ, VM::M1, "TreatmentSummaryCalculatedDoseReferenceSequence" },
{ 0x300A, 0x0052, 0, VR::DS, VM::M1, "TableTopLongitudinalPositionTolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0154[] = {
{ 0x0008, 0x0090, 0, VR::PN, VM::M1, "ReferringPhysicianName" },
{ 0x0018, 0x0080, 0, VR::DS, VM::M1, "RepetitionTime" },
{ 0x0018, 0x2002, 0, VR::SH, VM::M1TN, "FrameLabelVector" },
{ 0x300A, 0x0051, 0, VR::DS, VM::M1, "TableTopVerticalPositionTolerance" },
{ 0x600E, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat8" },
{ 0x601A, 0x4000, 1, VR::LT, VM::M1, "OverlayComments14" },
{ 0x601C, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition15" },
{ 0x601E, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0155[] = {
{ 0x0018, 0x0081, 0, VR::DS, VM::M1, "EchoTime" },
{ 0x0018, 0x2003, 0, VR::DS, VM::M1TN, "FramePrimaryAngleVector" },
{ 0x3008, 0x0052, 0, VR::DS, VM::M1, "CumulativeDoseToDoseReference" },
{ 0x300A, 0x0050, 0, VR::FL, VM::M1, "TableTopRollAngleTolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0156[] = {
{ 0x0008, 0x0096, 0, VR::SQ, VM::M1, "ReferringPhysicianIdentificationSequence" },
{ 0x0014, 0x2008, 2, VR::IS, VM::M1, "EvaluationAttempt" },
{ 0x0018, 0x0086, 0, VR::IS, VM::M1TN, "EchoNumbers" },
{ 0x0018, 0x2004, 0, VR::DS, VM::M1TN, "FrameSecondaryAngleVector" },
{ 0x0068, 0x6560, 0, VR::FD, VM::M2, "TwoDPointCoordinates" },
{ 0x300C, 0x0051, 0, VR::IS, VM::M1, "ReferencedDoseReferenceNumber" },
{ 0x6008, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat5" },
{ 0x6018, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated13" },
{ 0x601A, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition14" },
{ 0x601C, 0x4000, 1, VR::LT, VM::M1, "OverlayComments15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0157[] = {
{ 0x0018, 0x0087, 0, VR::DS, VM::M1, "MagneticFieldStrength" },
{ 0x0018, 0x2005, 0, VR::DS, VM::M1TN, "SliceLocationVector" },
{ 0x3004, 0x0058, 0, VR::DS, VM::M2T2N, "DVHData" },
{ 0x3008, 0x0054, 0, VR::DA, VM::M1, "FirstTreatmentDate" },
{ 0x300C, 0x0050, 0, VR::SQ, VM::M1, "ReferencedDoseReferenceSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0158[] = {
{ 0x0008, 0x0094, 0, VR::SH, VM::M1TN, "ReferringPhysicianTelephoneNumbers" },
{ 0x0018, 0x0084, 0, VR::DS, VM::M1, "ImagingFrequency" },
{ 0x0018, 0x2006, 0, VR::SH, VM::M1TN, "DisplayWindowLabelVector" },
{ 0x2000, 0x001E, 0, VR::SQ, VM::M1, "PrinterConfigurationSequence" },
{ 0x300A, 0x0055, 0, VR::CS, VM::M1, "RTPlanRelationship" },
{ 0x600A, 0x0110, 1, VR::CS, VM::M1, "OverlayFormat6" },
{ 0x6018, 0x0102, 0, VR::US, VM::M1, "OverlayBitPosition13" },
{ 0x601A, 0x0100, 0, VR::US, VM::M1, "OverlayBitsAllocated14" },
{ 0x601E, 0x4000, 1, VR::LT, VM::M1, "OverlayComments16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0159[] = {
{ 0x0018, 0x0085, 0, VR::SH, VM::M1, "ImagedNucleus" },
{ 0x3008, 0x0056, 0, VR::DA, VM::M1, "MostRecentTreatmentDate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0160[] = {
{ 0x0014, 0x3075, 2, VR::DS, VM::M1, "FilterThicknessUsedInGainCalibration" },
{ 0x0024, 0x0086, 0, VR::CS, VM::M1, "FovealSensitivityMeasured" },
{ 0x2000, 0x0020, 0, VR::CS, VM::M1, "PrintPriority" },
{ 0x2010, 0x0030, 0, VR::CS, VM::M1, "AnnotationDisplayFormatID" },
{ 0x2030, 0x0010, 0, VR::US, VM::M1, "AnnotationPosition" },
{ 0x2040, 0x0060, 1, VR::CS, VM::M1, "OverlayMagnificationType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0161[] = {
{ 0x0014, 0x3074, 2, VR::LO, VM::M1, "FilterMaterialUsedInGainCalibration" },
{ 0x0024, 0x0087, 0, VR::FL, VM::M1, "FovealSensitivity" },
{ 0x0060, 0x3000, 0, VR::SQ, VM::M1, "HistogramSequence" },
{ 0x3008, 0x0068, 0, VR::SQ, VM::M1, "CorrectedParameterSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0162[] = {
{ 0x0014, 0x3077, 2, VR::TM, VM::M1, "TimeOfGainCalibration" },
{ 0x0020, 0x0080, 1, VR::CS, VM::M1TN, "MaskingImage" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0163[] = {
{ 0x0014, 0x3076, 2, VR::DA, VM::M1, "DateOfGainCalibration" },
{ 0x0024, 0x0085, 0, VR::SQ, VM::M1, "LocalizedDeviationProbabilitySequence" },
{ 0x0060, 0x3002, 0, VR::US, VM::M1, "HistogramNumberOfBins" },
{ 0x3008, 0x006A, 0, VR::FL, VM::M1, "CorrectionValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0164[] = {
{ 0x0014, 0x2030, 2, VR::SQ, VM::M1, "IndicationPhysicalPropertySequence" },
{ 0x0014, 0x3071, 2, VR::DS, VM::M1, "KVUsedInGainCalibration" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0165[] = {
{ 0x0014, 0x3070, 2, VR::OX, VM::M1, "AirCounts" },
{ 0x0024, 0x0083, 0, VR::SQ, VM::M1, "GlobalDeviationProbabilitySequence" },
{ 0x0060, 0x3004, 0, VR::XS, VM::M1, "HistogramFirstBinValue" },
{ 0x3004, 0x0060, 0, VR::SQ, VM::M1, "DVHReferencedROISequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0166[] = {
{ 0x0014, 0x2032, 2, VR::SH, VM::M1, "PropertyLabel" },
{ 0x0014, 0x3073, 2, VR::DS, VM::M1, "NumberOfFramesUsedForIntegration" },
{ 0x0024, 0x0080, 0, VR::CS, VM::M1, "CorrectedLocalizedDeviationFromNormalProbabilityCalculated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0167[] = {
{ 0x0014, 0x3072, 2, VR::DS, VM::M1, "MAUsedInGainCalibration" },
{ 0x0024, 0x0081, 0, VR::FL, VM::M1, "CorrectedLocalizedDeviationFromNormalProbability" },
{ 0x0060, 0x3006, 0, VR::XS, VM::M1, "HistogramLastBinValue" },
{ 0x3004, 0x0062, 0, VR::CS, VM::M1, "DVHROIContributionType" },
{ 0x300C, 0x006A, 0, VR::IS, VM::M1, "ReferencedPatientSetupNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0168[] = {
{ 0x0018, 0x2030, 0, VR::DS, VM::M1, "RotationOfScannedFilm" },
{ 0x0028, 0x0082, 1, VR::US, VM::M1TN, "PredictorConstants" },
{ 0x0028, 0x2000, 0, VR::OB, VM::M1, "ICCProfile" },
{ 0x3008, 0x0061, 0, VR::AT, VM::M1, "ParameterSequencePointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0169[] = {
{ 0x0060, 0x3008, 0, VR::US, VM::M1, "HistogramBinWidth" },
{ 0x3008, 0x0060, 0, VR::SQ, VM::M1, "OverrideSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0170[] = {
{ 0x0028, 0x0080, 1, VR::US, VM::M1, "PredictorRows" },
{ 0x3008, 0x0063, 0, VR::IS, VM::M1, "ParameterItemIndex" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0171[] = {
{ 0x0028, 0x0081, 1, VR::US, VM::M1, "PredictorColumns" },
{ 0x3008, 0x0062, 0, VR::AT, VM::M1, "OverrideParameterPointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0172[] = {
{ 0x0028, 0x6100, 0, VR::SQ, VM::M1, "MaskSubtractionSequence" },
{ 0x0068, 0x6550, 0, VR::SQ, VM::M1, "TwoDPointCoordinatesSequence" },
{ 0x3008, 0x0065, 0, VR::AT, VM::M1, "ParameterPointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0173[] = {
{ 0x0028, 0x6101, 0, VR::CS, VM::M1, "MaskOperation" },
{ 0x3008, 0x0064, 0, VR::IS, VM::M1, "MeasuredDoseReferenceNumber" },
{ 0x300C, 0x0060, 0, VR::SQ, VM::M1, "ReferencedStructureSetSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0174[] = {
{ 0x0024, 0x0088, 0, VR::FL, VM::M1, "VisualFieldTestDuration" },
{ 0x0028, 0x6102, 0, VR::US, VM::M2T2N, "ApplicableFrameRange" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0175[] = {
{ 0x0024, 0x0089, 0, VR::SQ, VM::M1, "VisualFieldTestPointSequence" },
{ 0x3008, 0x0066, 0, VR::ST, VM::M1, "OverrideReason" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0176[] = {
{ 0x0024, 0x0096, 0, VR::FL, VM::M1, "RetestSensitivityValue" },
{ 0x2000, 0x0030, 0, VR::CS, VM::M1, "MediumType" },
{ 0x2020, 0x0010, 0, VR::US, VM::M1, "ImageBoxPosition" },
{ 0x2040, 0x0070, 1, VR::CS, VM::M1, "OverlaySmoothingType" },
{ 0x300A, 0x007B, 0, VR::LT, VM::M1, "FractionPattern" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0177[] = {
{ 0x0024, 0x0097, 0, VR::SQ, VM::M1, "VisualFieldTestPointNormalsSequence" },
{ 0x0060, 0x3010, 0, VR::LO, VM::M1, "HistogramExplanation" },
{ 0x3004, 0x0074, 0, VR::DS, VM::M1, "DVHMeanDose" },
{ 0x3008, 0x0078, 0, VR::DS, VM::M1, "StartMeterset" },
{ 0x300A, 0x007A, 0, VR::IS, VM::M1, "RepeatFractionCycleLength" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0178[] = {
{ 0x0024, 0x0094, 0, VR::FL, VM::M1, "SensitivityValue" },
{ 0x2040, 0x0072, 1, VR::CS, VM::M1, "OverlayOrImageMagnification" },
{ 0x300A, 0x0079, 0, VR::IS, VM::M1, "NumberOfFractionPatternDigitsPerDay" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0179[] = {
{ 0x0024, 0x0095, 0, VR::CS, VM::M1, "RetestStimulusSeen" },
{ 0x3008, 0x007A, 0, VR::DS, VM::M1, "EndMeterset" },
{ 0x300A, 0x0078, 0, VR::IS, VM::M1, "NumberOfFractionsPlanned" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0180[] = {
{ 0x0024, 0x0092, 0, VR::FL, VM::M1, "AgeCorrectedSensitivityDeviationValue" },
{ 0x0076, 0x00C0, 0, VR::US, VM::M1, "Component2ReferencedMatingFeatureID" },
{ 0x2040, 0x0074, 1, VR::US, VM::M1, "MagnifyToNumberOfColumns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0181[] = {
{ 0x0014, 0x3060, 2, VR::SQ, VM::M1, "GainCorrectionReferenceSequence" },
{ 0x0024, 0x0093, 0, VR::CS, VM::M1, "StimulusResults" },
{ 0x3004, 0x0070, 0, VR::DS, VM::M1, "DVHMinimumDose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0182[] = {
{ 0x0024, 0x0090, 0, VR::FL, VM::M1, "VisualFieldTestPointXCoordinate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0183[] = {
{ 0x0024, 0x0091, 0, VR::FL, VM::M1, "VisualFieldTestPointYCoordinate" },
{ 0x3004, 0x0072, 0, VR::DS, VM::M1, "DVHMaximumDose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0184[] = {
{ 0x0018, 0x2020, 0, VR::CS, VM::M1, "DigitizingDeviceTransportDirection" },
{ 0x0028, 0x0092, 1, VR::US, VM::M1, "BlockColumns" },
{ 0x0028, 0x6114, 0, VR::FL, VM::M2, "MaskSubPixelShift" },
{ 0x0040, 0x08DA, 1, VR::SQ, VM::M1, "CoordinateSystemAxisCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0185[] = {
{ 0x0028, 0x0093, 1, VR::US, VM::M1, "RowOverlap" },
{ 0x0068, 0x6545, 0, VR::SQ, VM::M1, "PlanningLandmarkIdentificationCodeSequence" },
{ 0x3008, 0x0070, 0, VR::SQ, VM::M1, "CalculatedDoseReferenceSequence" },
{ 0x300A, 0x0072, 0, VR::LO, VM::M1, "FractionGroupDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0186[] = {
{ 0x0028, 0x0090, 1, VR::CS, VM::M1, "BlockedPixels" },
{ 0x0040, 0x08D8, 1, VR::SQ, VM::M1, "PixelSpacingSequence" },
{ 0x300A, 0x0071, 0, VR::IS, VM::M1, "FractionGroupNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0187[] = {
{ 0x0028, 0x0091, 1, VR::US, VM::M1, "BlockRows" },
{ 0x3008, 0x0072, 0, VR::IS, VM::M1, "CalculatedDoseReferenceNumber" },
{ 0x300A, 0x0070, 0, VR::SQ, VM::M1, "FractionGroupSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0188[] = {
{ 0x0028, 0x6110, 0, VR::US, VM::M1TN, "MaskFrameNumbers" },
{ 0x0068, 0x6540, 0, VR::LO, VM::M1, "PlanningLandmarkDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0189[] = {
{ 0x3008, 0x0074, 0, VR::ST, VM::M1, "CalculatedDoseReferenceDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0190[] = {
{ 0x0024, 0x0098, 0, VR::FL, VM::M1, "QuantifiedDefect" },
{ 0x0028, 0x0094, 1, VR::US, VM::M1, "ColumnOverlap" },
{ 0x0028, 0x6112, 0, VR::US, VM::M1, "ContrastFrameAveraging" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0191[] = {
{ 0x3008, 0x0076, 0, VR::DS, VM::M1, "CalculatedDoseReferenceDoseValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0192[] = {
{ 0x0040, 0x2001, 1, VR::LO, VM::M1, "ReasonForTheImagingServiceRequest" },
{ 0x3002, 0x0002, 0, VR::SH, VM::M1, "RTImageLabel" },
{ 0x3004, 0x0004, 0, VR::CS, VM::M1, "DoseType" },
{ 0x3006, 0x0006, 0, VR::ST, VM::M1, "StructureSetDescription" },
{ 0x300A, 0x000A, 0, VR::CS, VM::M1, "PlanIntent" },
{ 0x300C, 0x000C, 0, VR::IS, VM::M1, "ReferencedBrachyApplicationSetupNumber" },
{ 0x5014, 0x2500, 1, VR::LO, VM::M1, "CurveLabel11" },
{ 0x6004, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray3" },
{ 0x6006, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen4" },
{ 0x6014, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0193[] = {
{ 0x2000, 0x0040, 0, VR::CS, VM::M1, "FilmDestination" },
{ 0x2010, 0x0050, 0, VR::CS, VM::M1, "FilmSizeID" },
{ 0x2050, 0x0010, 0, VR::SQ, VM::M1, "PresentationLUTSequence" },
{ 0x2100, 0x0140, 1, VR::AE, VM::M1, "DestinationAE" },
{ 0x3002, 0x0003, 0, VR::LO, VM::M1, "RTImageName" },
{ 0x3004, 0x0005, 0, VR::CS, VM::M1, "SpatialTransformOfDose" },
{ 0x300A, 0x000B, 0, VR::LO, VM::M1TN, "TreatmentSites" },
{ 0x6004, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed3" },
{ 0x6006, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0194[] = {
{ 0x0010, 0x1090, 0, VR::LO, VM::M1, "MedicalRecordLocator" },
{ 0x3004, 0x0006, 0, VR::LO, VM::M1, "DoseComment" },
{ 0x3006, 0x0004, 0, VR::LO, VM::M1, "StructureSetName" },
{ 0x300C, 0x000E, 0, VR::IS, VM::M1, "ReferencedSourceNumber" },
{ 0x5016, 0x2500, 1, VR::LO, VM::M1, "CurveLabel12" },
{ 0x6004, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen3" },
{ 0x6006, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray4" },
{ 0x6016, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0195[] = {
{ 0x0078, 0x00B8, 0, VR::US, VM::M1, "ImplantTemplateGroupVariationDimensionRank" },
{ 0x2010, 0x0052, 0, VR::CS, VM::M1, "PrinterResolutionID" },
{ 0x300A, 0x0009, 0, VR::LO, VM::M1TN, "TreatmentProtocols" },
{ 0x6004, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue3" },
{ 0x6006, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0196[] = {
{ 0x0018, 0x9296, 0, VR::FD, VM::M1, "ChemicalShiftMaximumIntegrationLimitInppm" },
{ 0x0040, 0x2005, 0, VR::TM, VM::M1, "IssueTimeOfImagingServiceRequest" },
{ 0x3006, 0x0002, 0, VR::SH, VM::M1, "StructureSetLabel" },
{ 0x300A, 0x000E, 0, VR::ST, VM::M1, "PrescriptionDescription" },
{ 0x300C, 0x0008, 0, VR::DS, VM::M1, "StartCumulativeMetersetWeight" },
{ 0x5010, 0x2500, 1, VR::LO, VM::M1, "CurveLabel9" },
{ 0x6000, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray" },
{ 0x6002, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen2" },
{ 0x6010, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0197[] = {
{ 0x0014, 0x3011, 2, VR::DS, VM::M1, "InternalDetectorFrameTime" },
{ 0x0040, 0x2004, 0, VR::DA, VM::M1, "IssueDateOfImagingServiceRequest" },
{ 0x0046, 0x0080, 0, VR::SQ, VM::M1, "FlatKeratometricAxisSequence" },
{ 0x0076, 0x00B0, 0, VR::US, VM::M1, "Component2ReferencedMatingFeatureSetID" },
{ 0x2010, 0x0054, 0, VR::CS, VM::M1, "DefaultPrinterResolutionID" },
{ 0x3004, 0x0001, 0, VR::CS, VM::M1, "DVHType" },
{ 0x300C, 0x0009, 0, VR::DS, VM::M1, "EndCumulativeMetersetWeight" },
{ 0x6000, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed" },
{ 0x6002, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0198[] = {
{ 0x0014, 0x3012, 2, VR::DS, VM::M1, "NumberOfFramesIntegrated" },
{ 0x0040, 0x2007, 1, VR::SH, VM::M1, "FillerOrderNumberImagingServiceRequestRetired" },
{ 0x3002, 0x0004, 0, VR::ST, VM::M1, "RTImageDescription" },
{ 0x3004, 0x0002, 0, VR::CS, VM::M1, "DoseUnits" },
{ 0x300A, 0x000C, 0, VR::CS, VM::M1, "RTPlanGeometry" },
{ 0x300C, 0x000A, 0, VR::SQ, VM::M1, "ReferencedBrachyApplicationSetupSequence" },
{ 0x300E, 0x0008, 0, VR::PN, VM::M1, "ReviewerName" },
{ 0x5012, 0x2500, 1, VR::LO, VM::M1, "CurveLabel10" },
{ 0x6000, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen" },
{ 0x6002, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray2" },
{ 0x6012, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0199[] = {
{ 0x0018, 0x9295, 0, VR::FD, VM::M1, "ChemicalShiftMinimumIntegrationLimitInppm" },
{ 0x0040, 0x2006, 1, VR::SH, VM::M1, "PlacerOrderNumberImagingServiceRequestRetired" },
{ 0x0054, 0x0090, 0, VR::US, VM::M1TN, "AngularViewVector" },
{ 0x6000, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue" },
{ 0x6002, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0200[] = {
{ 0x0040, 0x2009, 0, VR::SH, VM::M1, "OrderEntererLocation" },
{ 0x3002, 0x000A, 0, VR::CS, VM::M1, "ReportedValuesOrigin" },
{ 0x3004, 0x000C, 0, VR::DS, VM::M2TN, "GridFrameOffsetVector" },
{ 0x300A, 0x0002, 0, VR::SH, VM::M1, "RTPlanLabel" },
{ 0x300A, 0x0412, 0, VR::FL, VM::M3, "ControlPointOrientation" },
{ 0x300C, 0x0004, 0, VR::SQ, VM::M1, "ReferencedBeamSequence" },
{ 0x501C, 0x2500, 1, VR::LO, VM::M1, "CurveLabel15" },
{ 0x600C, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray7" },
{ 0x600E, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen8" },
{ 0x601C, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0201[] = {
{ 0x0008, 0x3001, 0, VR::SQ, VM::M1, "AlternateRepresentationSequence" },
{ 0x0040, 0x2008, 0, VR::PN, VM::M1, "OrderEnteredBy" },
{ 0x0078, 0x00B2, 0, VR::LO, VM::M1, "ImplantTemplateGroupVariationDimensionName" },
{ 0x300A, 0x0003, 0, VR::LO, VM::M1, "RTPlanName" },
{ 0x600C, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed7" },
{ 0x600E, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0202[] = {
{ 0x0008, 0x1080, 0, VR::LO, VM::M1TN, "AdmittingDiagnosesDescription" },
{ 0x0018, 0x1090, 0, VR::IS, VM::M1, "CardiacNumberOfImages" },
{ 0x0018, 0x1480, 0, VR::DS, VM::M1, "TomoTime" },
{ 0x3004, 0x000E, 0, VR::DS, VM::M1, "DoseGridScaling" },
{ 0x300A, 0x0410, 0, VR::SQ, VM::M1, "MotionSynchronizationSequence" },
{ 0x300C, 0x0006, 0, VR::IS, VM::M1, "ReferencedBeamNumber" },
{ 0x300E, 0x0004, 0, VR::DA, VM::M1, "ReviewDate" },
{ 0x501E, 0x2500, 1, VR::LO, VM::M1, "CurveLabel16" },
{ 0x600C, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen7" },
{ 0x600E, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray8" },
{ 0x601E, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0203[] = {
{ 0x0078, 0x00B0, 0, VR::SQ, VM::M1, "ImplantTemplateGroupVariationDimensionSequence" },
{ 0x300C, 0x0007, 0, VR::IS, VM::M1, "ReferencedReferenceImageNumber" },
{ 0x300E, 0x0005, 0, VR::TM, VM::M1, "ReviewTime" },
{ 0x600C, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue7" },
{ 0x600E, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0204[] = {
{ 0x3002, 0x000E, 0, VR::DS, VM::M1, "XRayImageReceptorAngle" },
{ 0x3004, 0x0008, 0, VR::DS, VM::M3, "NormalizationPoint" },
{ 0x300A, 0x0006, 0, VR::DA, VM::M1, "RTPlanDate" },
{ 0x300E, 0x0002, 0, VR::CS, VM::M1, "ApprovalStatus" },
{ 0x5018, 0x2500, 1, VR::LO, VM::M1, "CurveLabel13" },
{ 0x6008, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray5" },
{ 0x600A, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen6" },
{ 0x6018, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0205[] = {
{ 0x0068, 0x6530, 0, VR::US, VM::M1, "PlanningLandmarkID" },
{ 0x0078, 0x00B6, 0, VR::US, VM::M1, "ReferencedImplantTemplateGroupMemberID" },
{ 0x300A, 0x0007, 0, VR::TM, VM::M1, "RTPlanTime" },
{ 0x6008, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed5" },
{ 0x600A, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0206[] = {
{ 0x0008, 0x1084, 0, VR::SQ, VM::M1, "AdmittingDiagnosesCodeSequence" },
{ 0x0018, 0x1094, 0, VR::IS, VM::M1, "TriggerWindow" },
{ 0x3002, 0x000C, 0, VR::CS, VM::M1, "RTImagePlane" },
{ 0x3004, 0x000A, 0, VR::CS, VM::M1, "DoseSummationType" },
{ 0x3006, 0x0008, 0, VR::DA, VM::M1, "StructureSetDate" },
{ 0x300A, 0x0004, 0, VR::ST, VM::M1, "RTPlanDescription" },
{ 0x300C, 0x0002, 0, VR::SQ, VM::M1, "ReferencedRTPlanSequence" },
{ 0x501A, 0x2500, 1, VR::LO, VM::M1, "CurveLabel14" },
{ 0x6008, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen5" },
{ 0x600A, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray6" },
{ 0x601A, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0207[] = {
{ 0x0078, 0x00B4, 0, VR::SQ, VM::M1, "ImplantTemplateGroupVariationDimensionRankSequence" },
{ 0x3002, 0x000D, 0, VR::DS, VM::M3, "XRayImageReceptorTranslation" },
{ 0x3006, 0x0009, 0, VR::TM, VM::M1, "StructureSetTime" },
{ 0x6008, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue5" },
{ 0x600A, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0208[] = {
{ 0x0046, 0x0095, 0, VR::CS, VM::M1, "OptotypePresentation" },
{ 0x2040, 0x0011, 1, VR::US, VM::M1T99, "ReferencedOverlayPlaneGroups" },
{ 0x3002, 0x0012, 0, VR::DS, VM::M2, "RTImagePosition" },
{ 0x3004, 0x0014, 0, VR::CS, VM::M1T3, "TissueHeterogeneityCorrection" },
{ 0x3006, 0x0016, 0, VR::SQ, VM::M1, "ContourImageSequence" },
{ 0x300A, 0x001A, 0, VR::DS, VM::M1, "NominalPriorDose" },
{ 0x5004, 0x2500, 1, VR::LO, VM::M1, "CurveLabel3" },
{ 0x6004, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel3" },
{ 0x6014, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray11" },
{ 0x6016, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0209[] = {
{ 0x0040, 0x2010, 0, VR::SH, VM::M1, "OrderCallbackPhoneNumber" },
{ 0x0040, 0x2400, 0, VR::LT, VM::M1, "ImagingServiceRequestComments" },
{ 0x0046, 0x0094, 0, VR::CS, VM::M1, "Optotype" },
{ 0x2000, 0x0050, 0, VR::LO, VM::M1, "FilmSessionLabel" },
{ 0x2010, 0x0040, 0, VR::CS, VM::M1, "FilmOrientation" },
{ 0x2040, 0x0010, 1, VR::SQ, VM::M1, "ReferencedOverlayPlaneSequence" },
{ 0x6014, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed11" },
{ 0x6016, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0210[] = {
{ 0x0010, 0x1080, 0, VR::LO, VM::M1, "MilitaryRank" },
{ 0x0018, 0x1088, 0, VR::IS, VM::M1, "HeartRate" },
{ 0x0046, 0x0097, 0, VR::SQ, VM::M1, "SubjectiveRefractionRightEyeSequence" },
{ 0x3002, 0x0010, 0, VR::DS, VM::M6, "RTImageOrientation" },
{ 0x3006, 0x0014, 0, VR::SQ, VM::M1, "RTReferencedSeriesSequence" },
{ 0x300A, 0x0018, 0, VR::DS, VM::M3, "DoseReferencePointCoordinates" },
{ 0x5006, 0x2500, 1, VR::LO, VM::M1, "CurveLabel4" },
{ 0x6006, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel4" },
{ 0x6014, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen11" },
{ 0x6016, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0211[] = {
{ 0x0010, 0x1081, 0, VR::LO, VM::M1, "BranchOfService" },
{ 0x3002, 0x0011, 0, VR::DS, VM::M2, "ImagePlanePixelSpacing" },
{ 0x6014, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue11" },
{ 0x6016, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0212[] = {
{ 0x3004, 0x0010, 0, VR::SQ, VM::M1, "RTDoseROISequence" },
{ 0x3006, 0x0012, 0, VR::SQ, VM::M1, "RTReferencedStudySequence" },
{ 0x5000, 0x2500, 1, VR::LO, VM::M1, "CurveLabel" },
{ 0x6000, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel" },
{ 0x6010, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray9" },
{ 0x6012, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0213[] = {
{ 0x0076, 0x00A0, 0, VR::US, VM::M1, "Component2ReferencedID" },
{ 0x6010, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed9" },
{ 0x6012, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0214[] = {
{ 0x0040, 0x2017, 0, VR::LO, VM::M1, "FillerOrderNumberImagingServiceRequest" },
{ 0x0054, 0x0081, 0, VR::US, VM::M1, "NumberOfSlices" },
{ 0x3004, 0x0012, 0, VR::DS, VM::M1, "DoseValue" },
{ 0x3006, 0x0010, 0, VR::SQ, VM::M1, "ReferencedFrameOfReferenceSequence" },
{ 0x5002, 0x2500, 1, VR::LO, VM::M1, "CurveLabel2" },
{ 0x6002, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel2" },
{ 0x6010, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen9" },
{ 0x6012, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0215[] = {
{ 0x0040, 0x2016, 0, VR::LO, VM::M1, "PlacerOrderNumberImagingServiceRequest" },
{ 0x0046, 0x0092, 0, VR::CS, VM::M1, "BackgroundColor" },
{ 0x0054, 0x0080, 0, VR::US, VM::M1TN, "SliceVector" },
{ 0x6010, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue9" },
{ 0x6012, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0216[] = {
{ 0x0008, 0x3010, 0, VR::UI, VM::M1TN, "IrradiationEventUID" },
{ 0x0018, 0x1082, 0, VR::IS, VM::M1, "HighRRValue" },
{ 0x0018, 0x2041, 0, VR::SQ, VM::M1, "BiopsyTargetSequence" },
{ 0x0040, 0xA601, 1, VR::CS, VM::M1, "ObserverContextFlagTrial" },
{ 0x3008, 0x0010, 0, VR::SQ, VM::M1, "MeasuredDoseReferenceSequence" },
{ 0x300A, 0x0012, 0, VR::IS, VM::M1, "DoseReferenceNumber" },
{ 0x300A, 0x0402, 0, VR::ST, VM::M1, "SetupImageComment" },
{ 0x500C, 0x2500, 1, VR::LO, VM::M1, "CurveLabel7" },
{ 0x600C, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel7" },
{ 0x601C, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray15" },
{ 0x601E, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0217[] = {
{ 0x0018, 0x1083, 0, VR::IS, VM::M1, "IntervalsAcquired" },
{ 0x0040, 0xA600, 1, VR::CS, VM::M1, "ObservationSubjectContextFlagTrial" },
{ 0x300A, 0x0013, 0, VR::UI, VM::M1, "DoseReferenceUID" },
{ 0x601C, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed15" },
{ 0x601E, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0218[] = {
{ 0x0008, 0x1090, 0, VR::LO, VM::M1, "ManufacturerModelName" },
{ 0x0018, 0x1080, 0, VR::CS, VM::M1, "BeatRejectionFlag" },
{ 0x0018, 0x1490, 0, VR::CS, VM::M1, "TomoType" },
{ 0x0018, 0x2043, 0, VR::FL, VM::M2, "LocalizingCursorPosition" },
{ 0x0040, 0xA603, 1, VR::CS, VM::M1, "ProcedureContextFlagTrial" },
{ 0x3008, 0x0012, 0, VR::ST, VM::M1, "MeasuredDoseDescription" },
{ 0x300A, 0x0010, 0, VR::SQ, VM::M1, "DoseReferenceSequence" },
{ 0x500E, 0x2500, 1, VR::LO, VM::M1, "CurveLabel8" },
{ 0x600E, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel8" },
{ 0x601C, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen15" },
{ 0x601E, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0219[] = {
{ 0x0018, 0x1081, 0, VR::IS, VM::M1, "LowRRValue" },
{ 0x0018, 0x1491, 0, VR::CS, VM::M1, "TomoClass" },
{ 0x0018, 0x2042, 0, VR::UI, VM::M1, "TargetUID" },
{ 0x0078, 0x00A0, 0, VR::FD, VM::M4, "TwoDImplantTemplateGroupMemberMatchingAxes" },
{ 0x300A, 0x0401, 0, VR::SQ, VM::M1, "ReferencedSetupImageSequence" },
{ 0x601C, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue15" },
{ 0x601E, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0220[] = {
{ 0x0018, 0x1086, 0, VR::IS, VM::M1, "SkipBeats" },
{ 0x0018, 0x2045, 0, VR::SH, VM::M1, "TargetLabel" },
{ 0x3008, 0x0014, 0, VR::CS, VM::M1, "MeasuredDoseType" },
{ 0x300A, 0x0016, 0, VR::LO, VM::M1, "DoseReferenceDescription" },
{ 0x5008, 0x2500, 1, VR::LO, VM::M1, "CurveLabel5" },
{ 0x6008, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel5" },
{ 0x6018, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray13" },
{ 0x601A, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0221[] = {
{ 0x0018, 0x2044, 0, VR::FL, VM::M3, "CalculatedTargetPosition" },
{ 0x0046, 0x0098, 0, VR::SQ, VM::M1, "SubjectiveRefractionLeftEyeSequence" },
{ 0x0068, 0x6520, 0, VR::SQ, VM::M1, "PlanningLandmarkPlaneSequence" },
{ 0x6018, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed13" },
{ 0x601A, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0222[] = {
{ 0x0018, 0x1084, 0, VR::IS, VM::M1, "IntervalsRejected" },
{ 0x3006, 0x0018, 0, VR::SQ, VM::M1, "PredecessorStructureSetSequence" },
{ 0x3008, 0x0016, 0, VR::DS, VM::M1, "MeasuredDoseValue" },
{ 0x300A, 0x0014, 0, VR::CS, VM::M1, "DoseReferenceStructureType" },
{ 0x500A, 0x2500, 1, VR::LO, VM::M1, "CurveLabel6" },
{ 0x600A, 0x1500, 0, VR::LO, VM::M1, "OverlayLabel6" },
{ 0x6018, 0x1102, 1, VR::US, VM::M1, "OverlayDescriptorGreen13" },
{ 0x601A, 0x1100, 1, VR::US, VM::M1, "OverlayDescriptorGray14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0223[] = {
{ 0x0018, 0x1085, 0, VR::LO, VM::M1, "PVCRejection" },
{ 0x0018, 0x1495, 0, VR::IS, VM::M1, "NumberOfTomosynthesisSourceImages" },
{ 0x0018, 0x2046, 0, VR::FL, VM::M1, "DisplayedZValue" },
{ 0x300A, 0x0015, 0, VR::CS, VM::M1, "NominalBeamEnergyUnit" },
{ 0x6018, 0x1103, 1, VR::US, VM::M1, "OverlayDescriptorBlue13" },
{ 0x601A, 0x1101, 1, VR::US, VM::M1, "OverlayDescriptorRed14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0224[] = {
{ 0x2000, 0x0061, 0, VR::IS, VM::M1, "MaximumMemoryAllocation" },
{ 0x3002, 0x0022, 0, VR::DS, VM::M1, "RadiationMachineSAD" },
{ 0x3006, 0x0026, 0, VR::LO, VM::M1, "ROIName" },
{ 0x300A, 0x002A, 0, VR::DS, VM::M1, "OrganAtRiskFullVolumeDose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0225[] = {
{ 0x2000, 0x0060, 0, VR::IS, VM::M1, "MemoryAllocation" },
{ 0x2020, 0x0040, 0, VR::CS, VM::M1, "RequestedDecimateCropBehavior" },
{ 0x2040, 0x0020, 1, VR::SQ, VM::M1, "OverlayPixelDataSequence" },
{ 0x2100, 0x0160, 0, VR::SH, VM::M1, "OwnerID" },
{ 0x300A, 0x002B, 0, VR::DS, VM::M1, "OrganAtRiskLimitDose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0226[] = {
{ 0x2000, 0x0063, 1, VR::CS, VM::M1, "CollationFlag" },
{ 0x3002, 0x0020, 0, VR::SH, VM::M1, "RadiationMachineName" },
{ 0x3006, 0x0024, 0, VR::UI, VM::M1, "ReferencedFrameOfReferenceUID" },
{ 0x3008, 0x002A, 0, VR::CS, VM::M1, "TreatmentTerminationStatus" },
{ 0x300A, 0x0028, 0, VR::DS, VM::M1, "TargetUnderdoseVolumeFraction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0227[] = {
{ 0x2000, 0x0062, 1, VR::CS, VM::M1, "ColorImagePrintingFlag" },
{ 0x3008, 0x002B, 0, VR::SH, VM::M1, "TreatmentTerminationCode" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0228[] = {
{ 0x2000, 0x0065, 1, VR::CS, VM::M1, "AnnotationFlag" },
{ 0x3002, 0x0026, 0, VR::DS, VM::M1, "RTImageSID" },
{ 0x3006, 0x0022, 0, VR::IS, VM::M1, "ROINumber" },
{ 0x3008, 0x002C, 0, VR::CS, VM::M1, "TreatmentVerificationStatus" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0229[] = {
{ 0x0076, 0x0090, 0, VR::US, VM::M1, "Component1ReferencedMatingFeatureID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0230[] = {
{ 0x2000, 0x0067, 1, VR::CS, VM::M1, "ImageOverlayFlag" },
{ 0x3002, 0x0024, 0, VR::DS, VM::M1, "RadiationMachineSSD" },
{ 0x3006, 0x0020, 0, VR::SQ, VM::M1, "StructureSetROISequence" },
{ 0x300A, 0x002C, 0, VR::DS, VM::M1, "OrganAtRiskMaximumDose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0231[] = {
{ 0x300A, 0x002D, 0, VR::DS, VM::M1, "OrganAtRiskOverdoseVolumeFraction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0232[] = {
{ 0x0028, 0x3000, 0, VR::SQ, VM::M1, "ModalityLUTSequence" },
{ 0x2000, 0x0069, 1, VR::CS, VM::M1, "PresentationLUTFlag" },
{ 0x3008, 0x0020, 0, VR::SQ, VM::M1, "TreatmentSessionBeamSequence" },
{ 0x300A, 0x0022, 0, VR::DS, VM::M1, "DeliveryWarningDose" },
{ 0x300A, 0x0432, 0, VR::CS, VM::M1, "ApplicatorApertureShape" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0233[] = {
{ 0x3008, 0x0021, 0, VR::SQ, VM::M1, "TreatmentSessionIonBeamSequence" },
{ 0x300A, 0x0023, 0, VR::DS, VM::M1, "DeliveryMaximumDose" },
{ 0x300A, 0x0433, 0, VR::FL, VM::M1, "ApplicatorOpening" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0234[] = {
{ 0x0028, 0x1080, 1, VR::CS, VM::M1, "GrayScale" },
{ 0x0028, 0x3002, 0, VR::XS, VM::M3, "LUTDescriptor" },
{ 0x3002, 0x0028, 0, VR::DS, VM::M1, "SourceToReferenceObjectDistance" },
{ 0x3006, 0x002C, 0, VR::DS, VM::M1, "ROIVolume" },
{ 0x3008, 0x0022, 0, VR::IS, VM::M1, "CurrentFractionNumber" },
{ 0x300A, 0x0020, 0, VR::CS, VM::M1, "DoseReferenceType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0235[] = {
{ 0x0028, 0x3003, 0, VR::LO, VM::M1, "LUTExplanation" },
{ 0x0078, 0x0090, 0, VR::FD, VM::M2, "TwoDImplantTemplateGroupMemberMatchingPoint" },
{ 0x2000, 0x006A, 1, VR::CS, VM::M1, "ImageBoxPresentationLUTFlag" },
{ 0x3002, 0x0029, 0, VR::IS, VM::M1, "FractionNumber" },
{ 0x300A, 0x0021, 0, VR::DS, VM::M1, "ConstraintWeight" },
{ 0x300A, 0x0431, 0, VR::SQ, VM::M1, "ApplicatorGeometrySequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0236[] = {
{ 0x0028, 0x3004, 0, VR::LO, VM::M1, "ModalityLUTType" },
{ 0x3006, 0x002A, 0, VR::IS, VM::M3, "ROIDisplayColor" },
{ 0x3008, 0x0024, 0, VR::DA, VM::M1, "TreatmentControlPointDate" },
{ 0x300A, 0x0026, 0, VR::DS, VM::M1, "TargetPrescriptionDose" },
{ 0x300A, 0x0436, 0, VR::FL, VM::M1, "SourceToApplicatorMountingPositionDistance" },
{ 0x300C, 0x0020, 0, VR::SQ, VM::M1, "ReferencedFractionGroupSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0237[] = {
{ 0x0040, 0xA224, 1, VR::ST, VM::M1, "IdentificationDescriptionTrial" },
{ 0x0068, 0x6510, 0, VR::SQ, VM::M1, "PlanningLandmarkLineSequence" },
{ 0x3008, 0x0025, 0, VR::TM, VM::M1, "TreatmentControlPointTime" },
{ 0x300A, 0x0027, 0, VR::DS, VM::M1, "TargetMaximumDose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0238[] = {
{ 0x0028, 0x3006, 0, VR::OW, VM::M1, "LUTData" },
{ 0x3006, 0x0028, 0, VR::ST, VM::M1, "ROIDescription" },
{ 0x300A, 0x0434, 0, VR::FL, VM::M1, "ApplicatorOpeningX" },
{ 0x300C, 0x0022, 0, VR::IS, VM::M1, "ReferencedFractionGroupNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0239[] = {
{ 0x300A, 0x0025, 0, VR::DS, VM::M1, "TargetMinimumDose" },
{ 0x300A, 0x0435, 0, VR::FL, VM::M1, "ApplicatorOpeningY" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0240[] = {
{ 0x0014, 0x3024, 2, VR::DS, VM::M1, "HorizontalOffsetOfSensor" },
{ 0x0022, 0x1090, 0, VR::SQ, VM::M1, "IOLPowerSequence" },
{ 0x0070, 0x0083, 0, VR::TM, VM::M1, "PresentationCreationTime" },
{ 0x3002, 0x0032, 0, VR::DS, VM::M1, "MetersetExposure" },
{ 0x3006, 0x0036, 0, VR::CS, VM::M1, "ROIGenerationAlgorithm" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0241[] = {
{ 0x0020, 0x3401, 1, VR::CS, VM::M1, "ModifyingDeviceID" },
{ 0x0070, 0x0082, 0, VR::DA, VM::M1, "PresentationCreationDate" },
{ 0x0072, 0x0080, 0, VR::SQ, VM::M1, "SelectorCodeSequenceValue" },
{ 0x2010, 0x0060, 0, VR::CS, VM::M1, "MagnificationType" },
{ 0x2020, 0x0050, 0, VR::CS, VM::M1, "RequestedResolutionID" },
{ 0x2050, 0x0020, 0, VR::CS, VM::M1, "PresentationLUTShape" },
{ 0x2100, 0x0170, 0, VR::IS, VM::M1, "NumberOfFilms" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0242[] = {
{ 0x0014, 0x3026, 2, VR::DS, VM::M1, "VerticalOffsetOfSensor" },
{ 0x0020, 0x3402, 1, VR::CS, VM::M1, "ModifiedImageID" },
{ 0x0022, 0x1092, 0, VR::SQ, VM::M1, "LensConstantSequence" },
{ 0x0070, 0x0081, 0, VR::LO, VM::M1, "ContentDescription" },
{ 0x3002, 0x0030, 0, VR::SQ, VM::M1, "ExposureSequence" },
{ 0x3008, 0x003A, 0, VR::DS, VM::M1, "SpecifiedTreatmentTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0243[] = {
{ 0x0020, 0x3403, 1, VR::DA, VM::M1, "ModifiedImageDate" },
{ 0x0022, 0x1093, 0, VR::LO, VM::M1, "IOLManufacturer" },
{ 0x0070, 0x0080, 0, VR::CS, VM::M1, "ContentLabel" },
{ 0x3008, 0x003B, 0, VR::DS, VM::M1, "DeliveredTreatmentTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0244[] = {
{ 0x0014, 0x3020, 2, VR::SQ, VM::M1, "DetectorTemperatureSequence" },
{ 0x0020, 0x3404, 1, VR::LO, VM::M1, "ModifyingDeviceManufacturer" },
{ 0x0022, 0x1094, 1, VR::LO, VM::M1, "LensConstantDescription" },
{ 0x0070, 0x0087, 0, VR::SQ, VM::M1, "AlternateContentDescriptionSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0245[] = {
{ 0x0020, 0x3405, 1, VR::TM, VM::M1, "ModifiedImageTime" },
{ 0x0022, 0x1095, 0, VR::LO, VM::M1, "ImplantName" },
{ 0x0070, 0x0086, 0, VR::SQ, VM::M1, "ContentCreatorIdentificationCodeSequence" },
{ 0x0076, 0x0080, 0, VR::US, VM::M1, "Component1ReferencedMatingFeatureSetID" },
{ 0x3006, 0x0033, 0, VR::CS, VM::M1, "RTROIRelationship" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0246[] = {
{ 0x0014, 0x3022, 2, VR::ST, VM::M1, "SensorName" },
{ 0x0020, 0x3406, 1, VR::LO, VM::M1, "ModifiedImageDescription" },
{ 0x0022, 0x1096, 0, VR::SQ, VM::M1, "KeratometryMeasurementTypeCodeSequence" },
{ 0x3002, 0x0034, 0, VR::DS, VM::M4, "DiaphragmPosition" },
{ 0x3006, 0x0030, 0, VR::SQ, VM::M1, "RTRelatedROISequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0247[] = {
{ 0x0022, 0x1097, 0, VR::LO, VM::M1, "ImplantPartNumber" },
{ 0x0070, 0x0084, 0, VR::PN, VM::M1, "ContentCreatorName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0248[] = {
{ 0x0028, 0x3010, 0, VR::SQ, VM::M1, "VOILUTSequence" },
{ 0x3008, 0x0030, 0, VR::SQ, VM::M1, "ReferencedTreatmentRecordSequence" },
{ 0x300A, 0x0422, 0, VR::ST, VM::M1, "GeneralAccessoryDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0249[] = {
{ 0x300A, 0x0423, 0, VR::CS, VM::M1, "GeneralAccessoryType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0250[] = {
{ 0x0028, 0x1090, 0, VR::CS, VM::M1, "RecommendedViewingMode" },
{ 0x3008, 0x0032, 0, VR::DS, VM::M1, "SpecifiedPrimaryMeterset" },
{ 0x300A, 0x0420, 0, VR::SQ, VM::M1, "GeneralAccessorySequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0251[] = {
{ 0x3008, 0x0033, 0, VR::DS, VM::M1, "SpecifiedSecondaryMeterset" },
{ 0x300A, 0x0421, 0, VR::SH, VM::M1, "GeneralAccessoryID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0252[] = {
{ 0x0014, 0x3028, 2, VR::DS, VM::M1, "SensorTemperature" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0253[] = {
{ 0x0068, 0x6500, 0, VR::SQ, VM::M1, "PlanningLandmarkPointSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0254[] = {
{ 0x3006, 0x0038, 0, VR::LO, VM::M1, "ROIGenerationDescription" },
{ 0x3008, 0x0036, 0, VR::DS, VM::M1, "DeliveredPrimaryMeterset" },
{ 0x300A, 0x0424, 0, VR::IS, VM::M1, "GeneralAccessoryNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0255[] = {
{ 0x3006, 0x0039, 0, VR::SQ, VM::M1, "ROIContourSequence" },
{ 0x3008, 0x0037, 0, VR::DS, VM::M1, "DeliveredSecondaryMeterset" },
{ 0x300A, 0x0425, 0, VR::FL, VM::M1, "SourceToGeneralAccessoryDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0256[] = {
{ 0x0004, 0x1141, 0, VR::CS, VM::M1T8, "FileSetDescriptorFileID" },
{ 0x0008, 0x010C, 0, VR::UI, VM::M1, "CodingSchemeUID" },
{ 0x0014, 0x4014, 2, VR::DS, VM::M1, "ElementDimensionA" },
{ 0x0024, 0x0120, 0, VR::CS, VM::M1, "ScreeningBaselineMeasured" },
{ 0x0040, 0x0554, 0, VR::UI, VM::M1, "SpecimenUID" },
{ 0x0040, 0x4040, 0, VR::CS, VM::M1, "RawDataHandling" },
{ 0x4010, 0x1051, 3, VR::LO, VM::M1, "ItineraryID" },
{ 0x5400, 0x1010, 0, VR::OX, VM::M1, "WaveformData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0257[] = {
{ 0x0008, 0x010D, 0, VR::UI, VM::M1, "ContextGroupExtensionCreatorUID" },
{ 0x0014, 0x4015, 2, VR::DS, VM::M1, "ElementDimensionB" },
{ 0x0040, 0x0555, 0, VR::SQ, VM::M1, "AcquisitionContextSequence" },
{ 0x0040, 0x4041, 0, VR::CS, VM::M1, "InputReadinessState" },
{ 0x0400, 0x0115, 0, VR::OB, VM::M1, "CertificateOfSigner" },
{ 0x5000, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels" },
{ 0x5000, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0258[] = {
{ 0x0014, 0x4016, 2, VR::DS, VM::M1, "ElementPitchA" },
{ 0x0024, 0x0122, 0, VR::SQ, VM::M1, "ScreeningBaselineMeasuredSequence" },
{ 0x0040, 0x0556, 0, VR::ST, VM::M1, "AcquisitionContextDescription" },
{ 0x4010, 0x1053, 3, VR::LO, VM::M1, "ItineraryIDAssigningAuthority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0259[] = {
{ 0x0004, 0x1142, 0, VR::CS, VM::M1, "SpecificCharacterSetOfFileSetDescriptorFile" },
{ 0x0008, 0x010F, 0, VR::CS, VM::M1, "ContextIdentifier" },
{ 0x0014, 0x4017, 2, VR::DS, VM::M1, "MeasuredBeamDimensionA" },
{ 0x0018, 0x115E, 0, VR::DS, VM::M1, "ImageAndFluoroscopyAreaDoseProduct" },
{ 0x4010, 0x1052, 3, VR::SH, VM::M1, "ItineraryIDType" },
{ 0x5002, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels2" },
{ 0x5002, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0260[] = {
{ 0x0002, 0x0102, 0, VR::OB, VM::M1, "PrivateInformation" },
{ 0x0008, 0x0108, 3, VR::LT, VM::M1, "ExtendedCodeMeaning" },
{ 0x0014, 0x4010, 2, VR::SQ, VM::M1, "TransmitTransducerSequence" },
{ 0x0018, 0x9351, 0, VR::FL, VM::M1, "CalciumScoringMassFactorPatient" },
{ 0x0024, 0x0124, 0, VR::CS, VM::M1, "ScreeningBaselineType" },
{ 0x0040, 0x0550, 1, VR::SQ, VM::M1, "SpecimenSequence" },
{ 0x0040, 0x1101, 0, VR::SQ, VM::M1, "PersonIdentificationCodeSequence" },
{ 0x0046, 0x0146, 0, VR::FD, VM::M1, "SpherePower" },
{ 0x0100, 0x0410, 0, VR::CS, VM::M1, "SOPInstanceStatus" },
{ 0x0400, 0x0110, 0, VR::CS, VM::M1, "CertificateType" },
{ 0x0400, 0x0500, 0, VR::SQ, VM::M1, "EncryptedAttributesSequence" },
{ 0x4010, 0x1055, 3, VR::SH, VM::M1, "RouteIDAssigningAuthority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0261[] = {
{ 0x0014, 0x4011, 2, VR::SQ, VM::M1, "ReceiveTransducerSequence" },
{ 0x0018, 0x9740, 0, VR::US, VM::M1, "NumberOfSubsets" },
{ 0x0040, 0x0551, 0, VR::LO, VM::M1, "SpecimenIdentifier" },
{ 0x0046, 0x0147, 0, VR::FD, VM::M1, "CylinderPower" },
{ 0x4010, 0x1054, 3, VR::SH, VM::M1, "RouteID" },
{ 0x5004, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels3" },
{ 0x5004, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0262[] = {
{ 0x0002, 0x0100, 0, VR::UI, VM::M1, "PrivateInformationCreatorUID" },
{ 0x0008, 0x114B, 0, VR::SQ, VM::M1, "ReferencedRealWorldValueMappingInstanceSequence" },
{ 0x0014, 0x4012, 2, VR::US, VM::M1, "NumberOfElements" },
{ 0x0018, 0x9353, 0, VR::FL, VM::M1, "EnergyWeightingFactor" },
{ 0x0024, 0x0126, 0, VR::FL, VM::M1, "ScreeningBaselineValue" },
{ 0x0040, 0x0552, 1, VR::SQ, VM::M1, "SpecimenDescriptionSequenceTrial" },
{ 0x0040, 0x1103, 0, VR::LO, VM::M1TN, "PersonTelephoneNumbers" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0263[] = {
{ 0x0008, 0x010B, 0, VR::CS, VM::M1, "ContextGroupExtensionFlag" },
{ 0x0008, 0x114A, 0, VR::SQ, VM::M1, "ReferencedInstanceSequence" },
{ 0x0014, 0x4013, 2, VR::CS, VM::M1, "ElementShape" },
{ 0x0018, 0x115A, 0, VR::CS, VM::M1, "RadiationMode" },
{ 0x0018, 0x9352, 0, VR::FL, VM::M3, "CalciumScoringMassFactorDevice" },
{ 0x0040, 0x0553, 1, VR::ST, VM::M1, "SpecimenDescriptionTrial" },
{ 0x0040, 0x1102, 0, VR::ST, VM::M1, "PersonAddress" },
{ 0x0046, 0x0145, 0, VR::SQ, VM::M1, "ReferencedRefractiveMeasurementsSequence" },
{ 0x4010, 0x1056, 3, VR::CS, VM::M1, "InboundArrivalType" },
{ 0x5006, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels4" },
{ 0x5006, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0264[] = {
{ 0x0008, 0x0104, 0, VR::LO, VM::M1, "CodeMeaning" },
{ 0x0008, 0x1145, 1, VR::SQ, VM::M1, "ReferencedCurveSequence" },
{ 0x0008, 0x4000, 1, VR::LT, VM::M1, "IdentifyingComments" },
{ 0x0014, 0x401C, 2, VR::DS, VM::M1, "MeasuredBandwidth" },
{ 0x0018, 0x1155, 0, VR::CS, VM::M1, "RadiationSetting" },
{ 0x4010, 0x1059, 3, VR::CS, VM::M1, "CarrierIDAssigningAuthority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0265[] = {
{ 0x0008, 0x0105, 0, VR::CS, VM::M1, "MappingResource" },
{ 0x0014, 0x401D, 2, VR::DS, VM::M1, "ElementPitchB" },
{ 0x0018, 0x1154, 0, VR::DS, VM::M1, "AveragePulseWidth" },
{ 0x0018, 0x5050, 0, VR::IS, VM::M1, "DepthOfScanField" },
{ 0x4010, 0x1058, 3, VR::SH, VM::M1, "CarrierID" },
{ 0x5008, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels5" },
{ 0x5008, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0266[] = {
{ 0x0008, 0x0106, 0, VR::DT, VM::M1, "ContextGroupVersion" },
{ 0x0068, 0x64F0, 0, VR::FD, VM::M3, "TwoDDegreeOfFreedomAxis" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0267[] = {
{ 0x0008, 0x0107, 0, VR::DT, VM::M1, "ContextGroupLocalVersion" },
{ 0x0018, 0x1156, 0, VR::CS, VM::M1, "RectificationType" },
{ 0x500A, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels6" },
{ 0x500A, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0268[] = {
{ 0x0008, 0x0100, 0, VR::SH, VM::M1, "CodeValue" },
{ 0x0014, 0x4018, 2, VR::DS, VM::M1, "MeasuredBeamDimensionB" },
{ 0x0018, 0x1151, 0, VR::IS, VM::M1, "XRayTubeCurrent" },
{ 0x0018, 0x9749, 0, VR::SQ, VM::M1, "PETReconstructionSequence" },
{ 0x0028, 0x0120, 0, VR::XS, VM::M1, "PixelPaddingValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0269[] = {
{ 0x0008, 0x0101, 3, VR::LO, VM::M1, "ExtendedCodeValue" },
{ 0x0008, 0x1140, 0, VR::SQ, VM::M1, "ReferencedImageSequence" },
{ 0x0014, 0x4019, 2, VR::DS, VM::M1, "LocationOfMeasuredBeamDiameter" },
{ 0x0018, 0x1150, 0, VR::IS, VM::M1, "ExposureTime" },
{ 0x0028, 0x0121, 0, VR::XS, VM::M1, "PixelPaddingRangeLimit" },
{ 0x500C, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels7" },
{ 0x500C, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0270[] = {
{ 0x0008, 0x0102, 0, VR::SH, VM::M1, "CodingSchemeDesignator" },
{ 0x0014, 0x401A, 2, VR::DS, VM::M1, "NominalFrequency" },
{ 0x0018, 0x1153, 0, VR::IS, VM::M1, "ExposureInuAs" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0271[] = {
{ 0x0008, 0x0103, 0, VR::SH, VM::M1, "CodingSchemeVersion" },
{ 0x0014, 0x401B, 2, VR::DS, VM::M1, "MeasuredCenterFrequency" },
{ 0x0018, 0x1152, 0, VR::IS, VM::M1, "Exposure" },
{ 0x2110, 0x0099, 1, VR::SH, VM::M1, "PrintQueueID" },
{ 0x500E, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels8" },
{ 0x500E, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0272[] = {
{ 0x0010, 0x4000, 0, VR::LT, VM::M1, "PatientComments" },
{ 0x0014, 0x4004, 2, VR::CS, VM::M1, "PulserType" },
{ 0x0018, 0x9345, 0, VR::FD, VM::M1, "CTDIvol" },
{ 0x0018, 0x9755, 0, VR::CS, VM::M1, "TimeOfFlightInformationUsed" },
{ 0x0040, 0x4050, 0, VR::DT, VM::M1, "PerformedProcedureStepStartDateTime" },
{ 0x0054, 0x1101, 0, VR::LO, VM::M1, "AttenuationCorrectionMethod" },
{ 0x4000, 0x0010, 1, VR::LT, VM::M1, "Arbitrary" },
{ 0x4010, 0x1041, 3, VR::DT, VM::M1, "OOIOwnerCreationTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0273[] = {
{ 0x0018, 0x9344, 0, VR::CS, VM::M1, "ContrastBolusAgentPhase" },
{ 0x0040, 0x4051, 0, VR::DT, VM::M1, "PerformedProcedureStepEndDateTime" },
{ 0x0054, 0x1100, 0, VR::CS, VM::M1, "RandomsCorrectionMethod" },
{ 0x0400, 0x0105, 0, VR::DT, VM::M1, "DigitalSignatureDateTime" },
{ 0x4010, 0x0001, 3, VR::CS, VM::M1, "LowEnergyDetectors" },
{ 0x5010, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels9" },
{ 0x5010, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0274[] = {
{ 0x0014, 0x4006, 2, VR::LT, VM::M1, "PulserNotes" },
{ 0x0040, 0x4052, 0, VR::DT, VM::M1, "ProcedureStepCancellationDateTime" },
{ 0x0054, 0x1103, 0, VR::LO, VM::M1, "ReconstructionMethod" },
{ 0x4010, 0x0002, 3, VR::CS, VM::M1, "HighEnergyDetectors" },
{ 0x4010, 0x1043, 3, VR::FL, VM::M3, "OOISize" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0275[] = {
{ 0x0018, 0x9346, 0, VR::SQ, VM::M1, "CTDIPhantomTypeCodeSequence" },
{ 0x0018, 0x9756, 0, VR::CS, VM::M1, "ReconstructionType" },
{ 0x0054, 0x1102, 0, VR::CS, VM::M1, "DecayCorrection" },
{ 0x4010, 0x1042, 3, VR::CS, VM::M1, "OOIType" },
{ 0x5012, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels10" },
{ 0x5012, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0276[] = {
{ 0x0018, 0x1149, 0, VR::IS, VM::M1T2, "FieldOfViewDimensions" },
{ 0x0018, 0x9341, 0, VR::SQ, VM::M1, "ContrastBolusUsageSequence" },
{ 0x0018, 0x9751, 0, VR::SQ, VM::M1, "PETFrameTypeSequence" },
{ 0x0054, 0x1105, 0, VR::LO, VM::M1, "ScatterCorrectionMethod" },
{ 0x0400, 0x0100, 0, VR::UI, VM::M1, "DigitalSignatureUID" },
{ 0x0400, 0x0510, 0, VR::UI, VM::M1, "EncryptedContentTransferSyntaxUID" },
{ 0x4010, 0x0004, 3, VR::SQ, VM::M1, "DetectorGeometrySequence" },
{ 0x4010, 0x1045, 3, VR::SQ, VM::M1, "BasisMaterialsCodeSequence" },
{ 0x5400, 0x1004, 0, VR::US, VM::M1, "WaveformBitsAllocated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0277[] = {
{ 0x0010, 0x0101, 0, VR::SQ, VM::M1, "PatientPrimaryLanguageCodeSequence" },
{ 0x0018, 0x9340, 0, VR::SQ, VM::M1, "ContrastAdministrationProfileSequence" },
{ 0x0054, 0x1104, 0, VR::LO, VM::M1, "DetectorLinesOfResponseUsed" },
{ 0x4010, 0x1044, 3, VR::CS, VM::M1, "AcquisitionStatus" },
{ 0x5014, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels11" },
{ 0x5014, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0278[] = {
{ 0x0010, 0x0102, 0, VR::SQ, VM::M1, "PatientPrimaryLanguageModifierCodeSequence" },
{ 0x0010, 0x2180, 0, VR::SH, VM::M1, "Occupation" },
{ 0x0014, 0x4002, 2, VR::SQ, VM::M1, "PulserEquipmentSequence" },
{ 0x0018, 0x9343, 0, VR::CS, VM::M1, "ContrastBolusAgentDetected" },
{ 0x2130, 0x00A0, 1, VR::SQ, VM::M1, "ProposedStudySequence" },
{ 0x4010, 0x1047, 3, VR::SQ, VM::M1, "OOIOwnerSequence" },
{ 0x5400, 0x1006, 0, VR::CS, VM::M1, "WaveformSampleInterpretation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0279[] = {
{ 0x0008, 0x115A, 0, VR::UI, VM::M1TN, "SOPClassesSupported" },
{ 0x0018, 0x9342, 0, VR::CS, VM::M1, "ContrastBolusAgentAdministered" },
{ 0x4010, 0x1046, 3, VR::CS, VM::M1, "PhantomType" },
{ 0x5016, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels12" },
{ 0x5016, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0280[] = {
{ 0x0008, 0x0114, 0, VR::ST, VM::M1, "CodingSchemeExternalID" },
{ 0x0008, 0x1155, 0, VR::UI, VM::M1, "ReferencedSOPInstanceUID" },
{ 0x0014, 0x400C, 2, VR::LT, VM::M1, "ReceiverNotes" },
{ 0x0018, 0x1145, 0, VR::DS, VM::M1, "CenterOfRotationOffset" },
{ 0x0018, 0x4000, 1, VR::LT, VM::M1, "AcquisitionComments" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0281[] = {
{ 0x0008, 0x0115, 0, VR::ST, VM::M1, "CodingSchemeName" },
{ 0x0018, 0x1144, 0, VR::DS, VM::M1, "AngularStep" },
{ 0x0018, 0x5040, 1, VR::DS, VM::M1, "TotalGain" },
{ 0x300A, 0x01D4, 0, VR::DS, VM::M1, "TableTopLongitudinalSetupDisplacement" },
{ 0x4010, 0x1048, 3, VR::CS, VM::M1, "ScanType" },
{ 0x5018, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels13" },
{ 0x5018, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0282[] = {
{ 0x0008, 0x0116, 0, VR::ST, VM::M1, "CodingSchemeResponsibleOrganization" },
{ 0x0014, 0x400E, 2, VR::SQ, VM::M1, "PreAmplifierEquipmentSequence" },
{ 0x0018, 0x1147, 0, VR::CS, VM::M1, "FieldOfViewShape" },
{ 0x5400, 0x100A, 0, VR::OX, VM::M1, "WaveformPaddingValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0283[] = {
{ 0x0008, 0x0117, 0, VR::UI, VM::M1, "ContextUID" },
{ 0x0014, 0x400F, 2, VR::LT, VM::M1, "PreAmplifierNotes" },
{ 0x0018, 0x1146, 1, VR::DS, VM::M1TN, "RotationOffset" },
{ 0x300A, 0x01D6, 0, VR::DS, VM::M1, "TableTopLateralSetupDisplacement" },
{ 0x501A, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels14" },
{ 0x501A, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0284[] = {
{ 0x0008, 0x0110, 0, VR::SQ, VM::M1, "CodingSchemeIdentificationSequence" },
{ 0x0014, 0x4008, 2, VR::SQ, VM::M1, "ReceiverEquipmentSequence" },
{ 0x0018, 0x1141, 1, VR::DS, VM::M1, "AngularPosition" },
{ 0x0018, 0x9759, 0, VR::CS, VM::M1, "AttenuationCorrected" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0285[] = {
{ 0x0008, 0x1150, 0, VR::UI, VM::M1, "ReferencedSOPClassUID" },
{ 0x0018, 0x1140, 0, VR::CS, VM::M1, "RotationDirection" },
{ 0x0018, 0x9758, 0, VR::CS, VM::M1, "DecayCorrected" },
{ 0x300A, 0x01D0, 0, VR::ST, VM::M1, "SetupReferenceDescription" },
{ 0x501C, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels15" },
{ 0x501C, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0286[] = {
{ 0x0008, 0x0112, 0, VR::LO, VM::M1, "CodingSchemeRegistry" },
{ 0x0014, 0x400A, 2, VR::CS, VM::M1, "AmplifierType" },
{ 0x0018, 0x1143, 0, VR::DS, VM::M1, "ScanArc" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0287[] = {
{ 0x0018, 0x1142, 0, VR::DS, VM::M1TN, "RadialPosition" },
{ 0x300A, 0x01D2, 0, VR::DS, VM::M1, "TableTopVerticalSetupDisplacement" },
{ 0x501E, 0x0040, 1, VR::SH, VM::M1TN, "AxisLabels16" },
{ 0x501E, 0x1001, 1, VR::CS, VM::M1, "CurveActivationLayer16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0288[] = {
{ 0x0014, 0x4034, 2, VR::DS, VM::M1, "RectifierSmoothing" },
{ 0x0018, 0x9765, 0, VR::CS, VM::M1, "RandomsCorrected" },
{ 0x0020, 0x4000, 0, VR::LT, VM::M1, "ImageComments" },
{ 0x0024, 0x0100, 0, VR::FL, VM::M1, "AgeCorrectedSensitivityDeviationProbabilityValue" },
{ 0x4010, 0x1071, 3, VR::SQ, VM::M1, "QRMeasurementsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0289[] = {
{ 0x0014, 0x4035, 2, VR::SQ, VM::M1, "DACSequence" },
{ 0x0018, 0x9764, 0, VR::CS, VM::M1, "CountLossNormalizationCorrected" },
{ 0x0020, 0x0105, 0, VR::IS, VM::M1, "NumberOfTemporalPositions" },
{ 0x4010, 0x1070, 3, VR::CS, VM::M1, "AITDeviceType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0290[] = {
{ 0x0014, 0x4036, 2, VR::CS, VM::M1, "DACType" },
{ 0x0018, 0x9767, 0, VR::CS, VM::M1, "SensitivityCalibrated" },
{ 0x0024, 0x0102, 0, VR::CS, VM::M1, "GeneralizedDefectCorrectedSensitivityDeviationFlag" },
{ 0x4010, 0x1073, 3, VR::FD, VM::M1, "SNRThreshold" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0291[] = {
{ 0x0018, 0x9766, 0, VR::CS, VM::M1, "NonUniformRadialSamplingCorrected" },
{ 0x0024, 0x0103, 0, VR::FL, VM::M1, "GeneralizedDefectCorrectedSensitivityDeviationValue" },
{ 0x4010, 0x1072, 3, VR::SQ, VM::M1, "TargetMaterialSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0292[] = {
{ 0x0014, 0x4030, 2, VR::SQ, VM::M1, "ReceiverSettingsSequence" },
{ 0x0018, 0x9761, 0, VR::CS, VM::M1, "DeadTimeCorrected" },
{ 0x0020, 0x0100, 0, VR::IS, VM::M1, "TemporalPositionIdentifier" },
{ 0x0024, 0x0104, 0, VR::FL, VM::M1, "GeneralizedDefectCorrectedSensitivityDeviationProbabilityValue" },
{ 0x0028, 0x0108, 0, VR::XS, VM::M1, "SmallestPixelValueInSeries" },
{ 0x0400, 0x0520, 0, VR::OB, VM::M1, "EncryptedContent" },
{ 0x4010, 0x1075, 3, VR::DS, VM::M1, "ImageScaleRepresentation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0293[] = {
{ 0x0014, 0x4031, 2, VR::DS, VM::M1, "AcquiredSoundpathLength" },
{ 0x0018, 0x9760, 0, VR::CS, VM::M1, "ScatterCorrected" },
{ 0x0024, 0x0105, 0, VR::FL, VM::M1, "MinimumSensitivityValue" },
{ 0x0028, 0x0109, 0, VR::XS, VM::M1, "LargestPixelValueInSeries" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0294[] = {
{ 0x0010, 0x21B0, 0, VR::LT, VM::M1, "AdditionalPatientHistory" },
{ 0x0014, 0x4032, 2, VR::CS, VM::M1, "AcquisitionCompressionType" },
{ 0x0018, 0x9763, 0, VR::CS, VM::M1, "PatientMotionCorrected" },
{ 0x0024, 0x0106, 0, VR::CS, VM::M1, "BlindSpotLocalized" },
{ 0x4010, 0x1077, 3, VR::SQ, VM::M1, "ReferencedTDRInstanceSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0295[] = {
{ 0x0014, 0x4033, 2, VR::IS, VM::M1, "AcquisitionSampleSize" },
{ 0x0018, 0x9762, 0, VR::CS, VM::M1, "GantryMotionCorrected" },
{ 0x0022, 0x1140, 0, VR::CS, VM::M1, "OphthalmicAxialLengthMeasurementModified" },
{ 0x0024, 0x0107, 0, VR::FL, VM::M1, "BlindSpotXCoordinate" },
{ 0x4010, 0x1076, 3, VR::SQ, VM::M1, "ReferencedPTOSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0296[] = {
{ 0x0014, 0x403C, 2, VR::DS, VM::M1TN, "DACAmplitude" },
{ 0x0024, 0x0108, 0, VR::FL, VM::M1, "BlindSpotYCoordinate" },
{ 0x0028, 0x0104, 1, VR::XS, VM::M1, "SmallestValidPixelValue" },
{ 0x0028, 0x4000, 1, VR::LT, VM::M1, "ImagePresentationComments" },
{ 0x4010, 0x1079, 3, VR::SQ, VM::M1, "AnomalyLocatorIndicatorSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0297[] = {
{ 0x0008, 0x1164, 0, VR::SQ, VM::M1, "FrameExtractionSequence" },
{ 0x0028, 0x0105, 1, VR::XS, VM::M1, "LargestValidPixelValue" },
{ 0x4010, 0x1078, 3, VR::ST, VM::M1, "PTOLocationDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0298[] = {
{ 0x0008, 0x1167, 0, VR::UI, VM::M1, "MultiFrameSourceSOPInstanceUID" },
{ 0x0028, 0x0106, 0, VR::XS, VM::M1, "SmallestImagePixelValue" },
{ 0x0068, 0x64D0, 0, VR::FD, VM::M9, "ThreeDMatingAxes" },
{ 0x4010, 0x107B, 3, VR::SQ, VM::M1, "PTORegionSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0299[] = {
{ 0x0028, 0x0107, 0, VR::XS, VM::M1, "LargestImagePixelValue" },
{ 0x4010, 0x107A, 3, VR::FL, VM::M3, "AnomalyLocatorIndicator" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0300[] = {
{ 0x0008, 0x1161, 0, VR::UL, VM::M1TN, "SimpleFrameList" },
{ 0x0014, 0x4038, 2, VR::DS, VM::M1TN, "DACGainPoints" },
{ 0x0018, 0x9769, 0, VR::CS, VM::M1, "IterativeReconstructionMethod" },
{ 0x0028, 0x0100, 0, VR::US, VM::M1, "BitsAllocated" },
{ 0x0038, 0x0500, 0, VR::LO, VM::M1, "PatientState" },
{ 0x4010, 0x107D, 3, VR::SQ, VM::M1, "SecondaryInspectionMethodSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0301[] = {
{ 0x0008, 0x1160, 0, VR::IS, VM::M1TN, "ReferencedFrameNumber" },
{ 0x0018, 0x1170, 0, VR::IS, VM::M1, "GeneratorPower" },
{ 0x0018, 0x9768, 0, VR::CS, VM::M1, "DetectorNormalizationCorrection" },
{ 0x0028, 0x0101, 0, VR::US, VM::M1, "BitsStored" },
{ 0x4010, 0x107C, 3, VR::CS, VM::M1, "InspectionSelectionCriteria" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0302[] = {
{ 0x0008, 0x1163, 0, VR::FD, VM::M2, "TimeRange" },
{ 0x0014, 0x403A, 2, VR::DS, VM::M1TN, "DACTimePoints" },
{ 0x0028, 0x0102, 0, VR::US, VM::M1, "HighBit" },
{ 0x0038, 0x0502, 0, VR::SQ, VM::M1, "PatientClinicalTrialParticipationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0303[] = {
{ 0x0008, 0x1162, 0, VR::UL, VM::M3T3N, "CalculatedFrameList" },
{ 0x0028, 0x0103, 0, VR::US, VM::M1, "PixelRepresentation" },
{ 0x4010, 0x107E, 3, VR::DS, VM::M6, "PRCSToRCSOrientation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0304[] = {
{ 0x0014, 0x4024, 2, VR::DS, VM::M1, "ExcitationFrequency" },
{ 0x0024, 0x0110, 0, VR::SQ, VM::M1, "VisualAcuityMeasurementSequence" },
{ 0x0100, 0x0424, 0, VR::LT, VM::M1, "SOPAuthorizationComment" },
{ 0x4010, 0x1061, 3, VR::FL, VM::M3, "SourcePosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0305[] = {
{ 0x4010, 0x1060, 3, VR::FL, VM::M3, "SourceOrientation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0306[] = {
{ 0x0014, 0x4026, 2, VR::CS, VM::M1, "ModulationType" },
{ 0x0022, 0x1155, 0, VR::FL, VM::M1, "SignalToNoiseRatio" },
{ 0x0024, 0x0112, 0, VR::SQ, VM::M1, "RefractiveParametersUsedOnPatientSequence" },
{ 0x0032, 0x4000, 1, VR::LT, VM::M1, "StudyComments" },
{ 0x0100, 0x0426, 0, VR::LO, VM::M1, "AuthorizationEquipmentCertificationNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0307[] = {
{ 0x0024, 0x0113, 0, VR::CS, VM::M1, "MeasurementLaterality" },
{ 0x4010, 0x1062, 3, VR::FL, VM::M1, "BeltHeight" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0308[] = {
{ 0x0014, 0x4020, 2, VR::SQ, VM::M1, "PulserSettingsSequence" },
{ 0x0018, 0x9771, 0, VR::SQ, VM::M1, "PatientPhysiologicalStateSequence" },
{ 0x0020, 0x0110, 0, VR::DS, VM::M1, "TemporalResolution" },
{ 0x0022, 0x1153, 1, VR::SQ, VM::M1, "OphthalmicAxialLengthAcquisitionMethodCodeSequence" },
{ 0x0024, 0x0114, 0, VR::SQ, VM::M1, "OphthalmicPatientClinicalInformationLeftEyeSequence" },
{ 0x0040, 0x0560, 0, VR::SQ, VM::M1, "SpecimenDescriptionSequence" },
{ 0x0100, 0x0420, 0, VR::DT, VM::M1, "SOPAuthorizationDateTime" },
{ 0x0400, 0x0120, 0, VR::OB, VM::M1, "Signature" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0309[] = {
{ 0x0018, 0x9360, 0, VR::SQ, VM::M1, "CTAdditionalXRaySourceSequence" },
{ 0x0018, 0x9770, 0, VR::CS, VM::M1, "AttenuationCorrectionTemporalRelationship" },
{ 0x0024, 0x0115, 0, VR::SQ, VM::M1, "OphthalmicPatientClinicalInformationRightEyeSequence" },
{ 0x4010, 0x1064, 3, VR::SQ, VM::M1, "AlgorithmRoutingCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0310[] = {
{ 0x0010, 0x21A0, 0, VR::CS, VM::M1, "SmokingStatus" },
{ 0x0014, 0x4022, 2, VR::DS, VM::M1, "PulseWidth" },
{ 0x0040, 0x0562, 0, VR::SQ, VM::M1, "IssuerOfTheSpecimenIdentifierSequence" },
{ 0x2130, 0x0080, 1, VR::SQ, VM::M1, "PresentationLUTContentSequence" },
{ 0x4010, 0x1067, 3, VR::CS, VM::M1, "TransportClassification" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0311[] = {
{ 0x0018, 0x9772, 0, VR::SQ, VM::M1, "PatientPhysiologicalStateCodeSequence" },
{ 0x0022, 0x1150, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthDataSourceCodeSequence" },
{ 0x0024, 0x0117, 0, VR::CS, VM::M1, "FovealPointNormativeDataFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0312[] = {
{ 0x0024, 0x0118, 0, VR::FL, VM::M1, "FovealPointProbabilityValue" },
{ 0x0038, 0x4000, 0, VR::LT, VM::M1, "VisitComments" },
{ 0x4010, 0x1069, 3, VR::FL, VM::M1, "TotalProcessingTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0313[] = {
{ 0x0018, 0x1164, 0, VR::DS, VM::M2, "ImagerPixelSpacing" },
{ 0x4010, 0x1068, 3, VR::LT, VM::M1, "OOITypeDescriptor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0314[] = {
{ 0x0068, 0x64C0, 0, VR::FD, VM::M3, "ThreeDMatingPoint" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0315[] = {
{ 0x0018, 0x1166, 0, VR::CS, VM::M1TN, "Grid" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0316[] = {
{ 0x0014, 0x4028, 2, VR::DS, VM::M1, "Damping" },
{ 0x0018, 0x1161, 0, VR::LO, VM::M1TN, "TypeOfFilters" },
{ 0x0028, 0x0110, 1, VR::XS, VM::M1, "SmallestImagePixelValueInPlane" },
{ 0x0038, 0x0100, 0, VR::SQ, VM::M1, "PertinentDocumentsSequence" },
{ 0x4010, 0x106D, 3, VR::CS, VM::M1, "AdditionalScreeningPerformed" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0317[] = {
{ 0x0018, 0x1160, 0, VR::SH, VM::M1, "FilterType" },
{ 0x0028, 0x0111, 1, VR::XS, VM::M1, "LargestImagePixelValueInPlane" },
{ 0x4010, 0x106C, 3, VR::OB, VM::M1, "DetectorCalibrationData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0318[] = {
{ 0x0022, 0x1159, 0, VR::LO, VM::M1, "OphthalmicAxialLengthDataSourceDescription" },
{ 0x4010, 0x106F, 3, VR::SQ, VM::M1, "AdditionalInspectionMethodSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0319[] = {
{ 0x0018, 0x1162, 0, VR::DS, VM::M1, "IntensifierSize" },
{ 0x4010, 0x106E, 3, VR::CS, VM::M1, "AdditionalInspectionSelectionCriteria" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0320[] = {
{ 0x0004, 0x1510, 0, VR::UI, VM::M1, "ReferencedSOPClassUIDInFile" },
{ 0x0018, 0x9314, 0, VR::SQ, VM::M1, "CTReconstructionSequence" },
{ 0x0040, 0x0515, 0, VR::SQ, VM::M1, "AlternateContainerIdentifierSequence" },
{ 0x0040, 0x4001, 1, VR::CS, VM::M1, "GeneralPurposeScheduledProcedureStepStatus" },
{ 0x4010, 0x1010, 3, VR::US, VM::M1, "PotentialThreatObjectID" },
{ 0x5010, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints9" },
{ 0x6000, 0x3000, 0, VR::OX, VM::M1, "OverlayData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0321[] = {
{ 0x0004, 0x1511, 0, VR::UI, VM::M1, "ReferencedSOPInstanceUIDInFile" },
{ 0x0014, 0x4054, 2, VR::ST, VM::M1, "CouplingTechnique" },
{ 0x0018, 0x9315, 0, VR::CS, VM::M1, "ReconstructionAlgorithm" },
{ 0x0022, 0x1127, 0, VR::SQ, VM::M1, "LensThicknessSequence" },
{ 0x0046, 0x0102, 0, VR::SQ, VM::M1, "AddOtherSequence" },
{ 0x0054, 0x0500, 0, VR::CS, VM::M1, "SliceProgressionDirection" },
{ 0x4010, 0x1011, 3, VR::SQ, VM::M1, "ThreatSequence" },
{ 0x5004, 0x0005, 1, VR::US, VM::M1, "CurveDimensions3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0322[] = {
{ 0x0004, 0x1512, 0, VR::UI, VM::M1, "ReferencedTransferSyntaxUIDInFile" },
{ 0x0014, 0x4057, 2, VR::DS, VM::M1, "CouplingVelocity" },
{ 0x0018, 0x9316, 0, VR::CS, VM::M1, "ConvolutionKernelGroup" },
{ 0x0040, 0x4003, 1, VR::CS, VM::M1, "GeneralPurposeScheduledProcedureStepPriority" },
{ 0x0046, 0x0101, 0, VR::SQ, VM::M1, "AddIntermediateSequence" },
{ 0x4010, 0x1012, 3, VR::CS, VM::M1, "ThreatCategory" },
{ 0x5012, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints10" },
{ 0x6002, 0x3000, 0, VR::OX, VM::M1, "OverlayData2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0323[] = {
{ 0x0014, 0x4056, 2, VR::ST, VM::M1, "CouplingMedium" },
{ 0x0018, 0x9317, 0, VR::FD, VM::M2, "ReconstructionFieldOfView" },
{ 0x0022, 0x1125, 0, VR::SQ, VM::M1, "AnteriorChamberDepthDefinitionCodeSequence" },
{ 0x0040, 0x4002, 1, VR::CS, VM::M1, "GeneralPurposePerformedProcedureStepStatus" },
{ 0x0046, 0x0100, 0, VR::SQ, VM::M1, "AddNearSequence" },
{ 0x4010, 0x1013, 3, VR::LT, VM::M1, "ThreatCategoryDescription" },
{ 0x5006, 0x0005, 1, VR::US, VM::M1, "CurveDimensions4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0324[] = {
{ 0x0014, 0x4051, 2, VR::SQ, VM::M1, "ReceiveTransducerSettingsSequence" },
{ 0x0018, 0x1508, 0, VR::CS, VM::M1, "PositionerType" },
{ 0x0018, 0x9310, 0, VR::FD, VM::M1, "TableFeedPerRotation" },
{ 0x0022, 0x1122, 0, VR::FL, VM::M1, "IOLPowerForExactTargetRefraction" },
{ 0x0040, 0x4005, 1, VR::DT, VM::M1, "ScheduledProcedureStepStartDateTime" },
{ 0x4010, 0x1014, 3, VR::CS, VM::M1, "ATDAbilityAssessment" },
{ 0x5014, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints11" },
{ 0x6004, 0x3000, 0, VR::OX, VM::M1, "OverlayData3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0325[] = {
{ 0x0014, 0x4050, 2, VR::SQ, VM::M1, "TransmitTransducerSettingsSequence" },
{ 0x0018, 0x9311, 0, VR::FD, VM::M1, "SpiralPitchFactor" },
{ 0x0018, 0x9701, 0, VR::DT, VM::M1, "DecayCorrectionDateTime" },
{ 0x0040, 0x0100, 0, VR::SQ, VM::M1, "ScheduledProcedureStepSequence" },
{ 0x0040, 0x4004, 1, VR::SQ, VM::M1, "ScheduledProcessingApplicationsCodeSequence" },
{ 0x0046, 0x0106, 0, VR::FD, VM::M1, "ViewingDistance" },
{ 0x0048, 0x0108, 0, VR::SQ, VM::M1, "IlluminationColorCodeSequence" },
{ 0x4010, 0x1015, 3, VR::CS, VM::M1, "ATDAssessmentFlag" },
{ 0x5000, 0x0005, 1, VR::US, VM::M1, "CurveDimensions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0326[] = {
{ 0x0018, 0x9312, 0, VR::SQ, VM::M1, "CTGeometrySequence" },
{ 0x0040, 0x0513, 0, VR::SQ, VM::M1, "IssuerOfTheContainerIdentifierSequence" },
{ 0x0040, 0x4007, 0, VR::SQ, VM::M1, "PerformedProcessingApplicationsCodeSequence" },
{ 0x4010, 0x1016, 3, VR::FL, VM::M1, "ATDAssessmentProbability" },
{ 0x5016, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints12" },
{ 0x6006, 0x3000, 0, VR::OX, VM::M1, "OverlayData4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0327[] = {
{ 0x0010, 0x21D0, 0, VR::DA, VM::M1, "LastMenstrualDate" },
{ 0x0014, 0x4052, 2, VR::DS, VM::M1, "IncidentAngle" },
{ 0x0018, 0x9313, 0, VR::FD, VM::M3, "DataCollectionCenterPatient" },
{ 0x0022, 0x1121, 0, VR::FL, VM::M1, "IOLPowerForExactEmmetropia" },
{ 0x0040, 0x0512, 0, VR::LO, VM::M1, "ContainerIdentifier" },
{ 0x0040, 0x4006, 1, VR::CS, VM::M1, "MultipleCopiesFlag" },
{ 0x0046, 0x0104, 0, VR::FD, VM::M1, "AddPower" },
{ 0x0072, 0x0520, 0, VR::CS, VM::M1TN, "ThreeDRenderingType" },
{ 0x4010, 0x1017, 3, VR::FL, VM::M1, "Mass" },
{ 0x5002, 0x0005, 1, VR::US, VM::M1, "CurveDimensions2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0328[] = {
{ 0x0018, 0x1114, 0, VR::DS, VM::M1, "EstimatedRadiographicMagnificationFactor" },
{ 0x0018, 0x5010, 0, VR::LO, VM::M1TN, "TransducerData" },
{ 0x0040, 0x4009, 0, VR::SQ, VM::M1, "HumanPerformerCodeSequence" },
{ 0x0048, 0x0105, 0, VR::SQ, VM::M1, "OpticalPathSequence" },
{ 0x300A, 0x0184, 0, VR::LO, VM::M1, "PatientAdditionalPosition" },
{ 0x4010, 0x1018, 3, VR::FL, VM::M1, "Density" },
{ 0x5018, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints13" },
{ 0x6008, 0x3000, 0, VR::OX, VM::M1, "OverlayData5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0329[] = {
{ 0x0014, 0x405C, 2, VR::ST, VM::M1, "DelayLawIdentifier" },
{ 0x4008, 0x0040, 1, VR::SH, VM::M1, "ResultsID" },
{ 0x4010, 0x1019, 3, VR::FL, VM::M1, "ZEffective" },
{ 0x500C, 0x0005, 1, VR::US, VM::M1, "CurveDimensions7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0330[] = {
{ 0x0004, 0x151A, 0, VR::UI, VM::M1TN, "ReferencedRelatedGeneralSOPClassUIDInFile" },
{ 0x0018, 0x5012, 0, VR::DS, VM::M1, "FocusDepth" },
{ 0x0040, 0xA385, 0, VR::SQ, VM::M1, "PertinentOtherEvidenceSequence" },
{ 0x0048, 0x0107, 0, VR::ST, VM::M1, "OpticalPathDescription" },
{ 0x4010, 0x101A, 3, VR::SH, VM::M1, "BoardingPassID" },
{ 0x501A, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints14" },
{ 0x600A, 0x3000, 0, VR::OX, VM::M1, "OverlayData6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0331[] = {
{ 0x0048, 0x0106, 0, VR::SH, VM::M1, "OpticalPathIdentifier" },
{ 0x4008, 0x0042, 1, VR::LO, VM::M1, "ResultsIDIssuer" },
{ 0x4010, 0x101B, 3, VR::FL, VM::M3, "CenterOfMass" },
{ 0x500E, 0x0005, 1, VR::US, VM::M1, "CurveDimensions8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0332[] = {
{ 0x0008, 0x1100, 1, VR::SQ, VM::M1, "ReferencedResultsSequence" },
{ 0x0014, 0x4059, 2, VR::DS, VM::M1, "ProbeCenterLocationZ" },
{ 0x0018, 0x1110, 0, VR::DS, VM::M1, "DistanceSourceToDetector" },
{ 0x0018, 0x1500, 0, VR::CS, VM::M1, "PositionerMotion" },
{ 0x0018, 0x9318, 0, VR::FD, VM::M3, "ReconstructionTargetCenterPatient" },
{ 0x300A, 0x0180, 0, VR::SQ, VM::M1, "PatientSetupSequence" },
{ 0x4010, 0x101C, 3, VR::FL, VM::M3, "CenterOfPTO" },
{ 0x501C, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints15" },
{ 0x600C, 0x3000, 0, VR::OX, VM::M1, "OverlayData7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0333[] = {
{ 0x0014, 0x4058, 2, VR::DS, VM::M1, "ProbeCenterLocationX" },
{ 0x0018, 0x1111, 0, VR::DS, VM::M1, "DistanceSourceToPatient" },
{ 0x0018, 0x9319, 0, VR::FD, VM::M1, "ReconstructionAngle" },
{ 0x0040, 0x0518, 0, VR::SQ, VM::M1, "ContainerTypeCodeSequence" },
{ 0x0048, 0x0100, 0, VR::SQ, VM::M1, "IlluminatorTypeCodeSequence" },
{ 0x4010, 0x101D, 3, VR::FL, VM::M6TN, "BoundingPolygon" },
{ 0x5008, 0x0005, 1, VR::US, VM::M1, "CurveDimensions5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0334[] = {
{ 0x0022, 0x1128, 0, VR::SQ, VM::M1, "AnteriorChamberDepthSequence" },
{ 0x300A, 0x0182, 0, VR::IS, VM::M1, "PatientSetupNumber" },
{ 0x4010, 0x101E, 3, VR::SH, VM::M1, "RouteSegmentStartLocationID" },
{ 0x501E, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints16" },
{ 0x600E, 0x3000, 0, VR::OX, VM::M1, "OverlayData8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0335[] = {
{ 0x0014, 0x405A, 2, VR::DS, VM::M1, "SoundPathLength" },
{ 0x0040, 0x051A, 0, VR::LO, VM::M1, "ContainerDescription" },
{ 0x0040, 0x8302, 0, VR::DS, VM::M1, "EntranceDoseInmGy" },
{ 0x0040, 0xA380, 1, VR::SQ, VM::M1, "ReportDetailSequenceTrial" },
{ 0x0048, 0x0102, 0, VR::DS, VM::M6, "ImageOrientationSlide" },
{ 0x300A, 0x0183, 0, VR::LO, VM::M1, "PatientSetupLabel" },
{ 0x4010, 0x101F, 3, VR::SH, VM::M1, "RouteSegmentEndLocationID" },
{ 0x500A, 0x0005, 1, VR::US, VM::M1, "CurveDimensions6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0336[] = {
{ 0x0004, 0x1500, 0, VR::CS, VM::M1T8, "ReferencedFileID" },
{ 0x0014, 0x5004, 2, VR::IS, VM::M1, "LINACOutput" },
{ 0x0018, 0x9304, 0, VR::SQ, VM::M1, "CTAcquisitionDetailsSequence" },
{ 0x0040, 0x4011, 0, VR::DT, VM::M1, "ExpectedCompletionDateTime" },
{ 0x0054, 0x0101, 0, VR::US, VM::M1, "NumberOfTimeSlices" },
{ 0x0074, 0x0121, 0, VR::FD, VM::M1, "ContinuationEndMeterset" },
{ 0x5000, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints" },
{ 0x6010, 0x3000, 0, VR::OX, VM::M1, "OverlayData9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0337[] = {
{ 0x0018, 0x9305, 0, VR::FD, VM::M1, "RevolutionTime" },
{ 0x0018, 0x9715, 0, VR::FD, VM::M1, "StartDensityThreshold" },
{ 0x0040, 0x4010, 0, VR::DT, VM::M1, "ScheduledProcedureStepModificationDateTime" },
{ 0x0054, 0x0100, 0, VR::US, VM::M1TN, "TimeSliceVector" },
{ 0x0074, 0x0120, 0, VR::FD, VM::M1, "ContinuationStartMeterset" },
{ 0x4010, 0x1001, 3, VR::SQ, VM::M1, "ThreatROIVoxelSequence" },
{ 0x5014, 0x0005, 1, VR::US, VM::M1, "CurveDimensions11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0338[] = {
{ 0x0018, 0x9306, 0, VR::FD, VM::M1, "SingleCollimationWidth" },
{ 0x0018, 0x9716, 0, VR::FD, VM::M1, "StartRelativeDensityDifferenceThreshold" },
{ 0x0022, 0x1134, 0, VR::SQ, VM::M1, "SourceOfRefractiveMeasurementsSequence" },
{ 0x5002, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints2" },
{ 0x6012, 0x3000, 0, VR::OX, VM::M1, "OverlayData10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0339[] = {
{ 0x0018, 0x9307, 0, VR::FD, VM::M1, "TotalCollimationWidth" },
{ 0x0018, 0x9717, 0, VR::FD, VM::M1, "StartCardiacTriggerCountThreshold" },
{ 0x0022, 0x1135, 0, VR::SQ, VM::M1, "SourceOfRefractiveMeasurementsCodeSequence" },
{ 0x5016, 0x0005, 1, VR::US, VM::M1, "CurveDimensions12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0340[] = {
{ 0x0004, 0x1504, 1, VR::UL, VM::M1, "MRDRDirectoryRecordOffset" },
{ 0x0022, 0x1132, 0, VR::SQ, VM::M1, "SourceOfLensThicknessDataCodeSequence" },
{ 0x0040, 0x4015, 1, VR::SQ, VM::M1, "ResultingGeneralPurposePerformedProcedureStepsSequence" },
{ 0x300A, 0x0198, 0, VR::SH, VM::M1, "FixationDevicePosition" },
{ 0x4010, 0x1004, 3, VR::FL, VM::M3, "ThreatROIBase" },
{ 0x5004, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints3" },
{ 0x6014, 0x3000, 0, VR::OX, VM::M1, "OverlayData11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0341[] = {
{ 0x0014, 0x4040, 2, VR::SQ, VM::M1, "PreAmplifierSettingsSequence" },
{ 0x0018, 0x9301, 0, VR::SQ, VM::M1, "CTAcquisitionTypeSequence" },
{ 0x0022, 0x1133, 0, VR::SQ, VM::M1, "SourceOfAnteriorChamberDepthDataCodeSequence" },
{ 0x0040, 0x0500, 0, VR::SQ, VM::M1, "ScheduledSpecimenSequence" },
{ 0x0400, 0x0550, 0, VR::SQ, VM::M1, "ModifiedAttributesSequence" },
{ 0x300A, 0x0199, 0, VR::FL, VM::M1, "FixationDevicePitchAngle" },
{ 0x4010, 0x1005, 3, VR::FL, VM::M3, "ThreatROIExtents" },
{ 0x5010, 0x0005, 1, VR::US, VM::M1, "CurveDimensions9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0342[] = {
{ 0x0014, 0x5002, 2, VR::IS, VM::M1, "LINACEnergy" },
{ 0x0018, 0x9302, 0, VR::CS, VM::M1, "AcquisitionType" },
{ 0x0022, 0x1130, 0, VR::FL, VM::M1, "LensThickness" },
{ 0x300A, 0x019A, 0, VR::FL, VM::M1, "FixationDeviceRollAngle" },
{ 0x4010, 0x1006, 3, VR::OB, VM::M1, "ThreatROIBitmap" },
{ 0x5006, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints4" },
{ 0x6016, 0x3000, 0, VR::OX, VM::M1, "OverlayData12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0343[] = {
{ 0x0010, 0x21C0, 0, VR::US, VM::M1, "PregnancyStatus" },
{ 0x0018, 0x9303, 0, VR::FD, VM::M1, "TubeAngle" },
{ 0x0022, 0x1131, 0, VR::FL, VM::M1, "AnteriorChamberDepth" },
{ 0x0040, 0x4016, 1, VR::SQ, VM::M1, "ReferencedGeneralPurposeScheduledProcedureStepSequence" },
{ 0x4010, 0x1007, 3, VR::SH, VM::M1, "RouteSegmentID" },
{ 0x5012, 0x0005, 1, VR::US, VM::M1, "CurveDimensions10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0344[] = {
{ 0x0018, 0x5000, 0, VR::SH, VM::M1TN, "OutputPower" },
{ 0x0040, 0x4019, 0, VR::SQ, VM::M1, "PerformedWorkitemCodeSequence" },
{ 0x300A, 0x0194, 0, VR::SH, VM::M1, "FixationDeviceLabel" },
{ 0x4010, 0x1008, 3, VR::CS, VM::M1, "GantryType" },
{ 0x5008, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints5" },
{ 0x6018, 0x3000, 0, VR::OX, VM::M1, "OverlayData13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0345[] = {
{ 0x0008, 0x1115, 0, VR::SQ, VM::M1, "ReferencedSeriesSequence" },
{ 0x0040, 0x4018, 0, VR::SQ, VM::M1, "ScheduledWorkitemCodeSequence" },
{ 0x4008, 0x0050, 1, VR::SQ, VM::M1, "ReferencedInterpretationSequence" },
{ 0x4010, 0x1009, 3, VR::CS, VM::M1, "OOIOwnerType" },
{ 0x501C, 0x0005, 1, VR::US, VM::M1, "CurveDimensions15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0346[] = {
{ 0x300A, 0x0196, 0, VR::ST, VM::M1, "FixationDeviceDescription" },
{ 0x4010, 0x100A, 3, VR::SQ, VM::M1, "RouteSegmentSequence" },
{ 0x500A, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints6" },
{ 0x601A, 0x3000, 0, VR::OX, VM::M1, "OverlayData14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0347[] = {
{ 0x0068, 0x64A0, 0, VR::FD, VM::M2, "RangeOfFreedom" },
{ 0x501E, 0x0005, 1, VR::US, VM::M1, "CurveDimensions16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0348[] = {
{ 0x0008, 0x1110, 0, VR::SQ, VM::M1, "ReferencedStudySequence" },
{ 0x0018, 0x1100, 0, VR::DS, VM::M1, "ReconstructionDiameter" },
{ 0x0018, 0x1510, 0, VR::DS, VM::M1, "PositionerPrimaryAngle" },
{ 0x0018, 0x9308, 0, VR::SQ, VM::M1, "CTTableDynamicsSequence" },
{ 0x0018, 0x9718, 0, VR::FD, VM::M1, "StartRespiratoryTriggerCountThreshold" },
{ 0x0048, 0x0111, 0, VR::DS, VM::M1, "CondenserLensPower" },
{ 0x300A, 0x0190, 0, VR::SQ, VM::M1, "FixationDeviceSequence" },
{ 0x500C, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints7" },
{ 0x601C, 0x3000, 0, VR::OX, VM::M1, "OverlayData15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0349[] = {
{ 0x0008, 0x1111, 0, VR::SQ, VM::M1, "ReferencedPerformedProcedureStepSequence" },
{ 0x0018, 0x1511, 0, VR::DS, VM::M1, "PositionerSecondaryAngle" },
{ 0x0018, 0x9309, 0, VR::FD, VM::M1, "TableSpeed" },
{ 0x0018, 0x9719, 0, VR::FD, VM::M1, "TerminationCountsThreshold" },
{ 0x0048, 0x0110, 0, VR::SQ, VM::M1, "SpecimenReferenceSequence" },
{ 0x5018, 0x0005, 1, VR::US, VM::M1, "CurveDimensions13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0350[] = {
{ 0x0048, 0x0113, 0, VR::DS, VM::M1, "ObjectiveLensNumericalAperture" },
{ 0x300A, 0x0192, 0, VR::CS, VM::M1, "FixationDeviceType" },
{ 0x500E, 0x0010, 1, VR::US, VM::M1, "NumberOfPoints8" },
{ 0x601E, 0x3000, 0, VR::OX, VM::M1, "OverlayData16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0351[] = {
{ 0x0040, 0x050A, 1, VR::LO, VM::M1, "SpecimenAccessionNumber" },
{ 0x0040, 0xA390, 0, VR::SQ, VM::M1, "HL7StructuredDocumentReferenceSequence" },
{ 0x0048, 0x0112, 0, VR::DS, VM::M1, "ObjectiveLensPower" },
{ 0x501A, 0x0005, 1, VR::US, VM::M1, "CurveDimensions14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0352[] = {
{ 0x0018, 0x9334, 0, VR::CS, VM::M1, "FluoroscopyFlag" },
{ 0x0018, 0x9724, 0, VR::FD, VM::M1, "TerminationRespiratoryTriggerCountThreshold" },
{ 0x0020, 0x5000, 1, VR::AT, VM::M1TN, "OriginalImageIdentification" },
{ 0x0020, 0x930C, 0, VR::CS, VM::M1, "PatientFrameOfReferenceSource" },
{ 0x0040, 0x4021, 0, VR::SQ, VM::M1, "InputInformationSequence" },
{ 0x0046, 0x0123, 0, VR::SQ, VM::M1, "VisualAcuityLeftEyeSequence" },
{ 0x0400, 0x0565, 0, VR::CS, VM::M1, "ReasonForTheAttributeModification" },
{ 0x5000, 0x0020, 1, VR::CS, VM::M1, "TypeOfData" },
{ 0x5002, 0x0022, 1, VR::LO, VM::M1, "CurveDescription2" },
{ 0x5010, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0353[] = {
{ 0x0014, 0x4074, 2, VR::SH, VM::M1, "ProcedureVersion" },
{ 0x0018, 0x9335, 0, VR::FD, VM::M1, "DistanceSourceToDataCollectionCenter" },
{ 0x0018, 0x9725, 0, VR::CS, VM::M1, "DetectorGeometry" },
{ 0x0020, 0x930D, 0, VR::FD, VM::M1, "TemporalPositionTimeOffset" },
{ 0x0040, 0x4020, 0, VR::CS, VM::M1, "InputAvailabilityFlag" },
{ 0x0046, 0x0122, 0, VR::SQ, VM::M1, "VisualAcuityRightEyeSequence" },
{ 0x0400, 0x0564, 0, VR::LO, VM::M1, "SourceOfPreviousValues" },
{ 0x4010, 0x1031, 3, VR::CS, VM::M1, "AlarmDecision" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0354[] = {
{ 0x0018, 0x9726, 0, VR::FD, VM::M1, "TransverseDetectorSeparation" },
{ 0x0020, 0x5002, 1, VR::LO, VM::M1TN, "OriginalImageIdentificationNomenclature" },
{ 0x0020, 0x930E, 0, VR::SQ, VM::M1, "PlanePositionVolumeSequence" },
{ 0x0040, 0x4023, 1, VR::UI, VM::M1, "ReferencedGeneralPurposeScheduledProcedureStepTransactionUID" },
{ 0x0046, 0x0121, 0, VR::SQ, VM::M1, "VisualAcuityTypeCodeSequence" },
{ 0x5000, 0x0022, 1, VR::LO, VM::M1, "CurveDescription" },
{ 0x5002, 0x0020, 1, VR::CS, VM::M1, "TypeOfData2" },
{ 0x5012, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0355[] = {
{ 0x0014, 0x4076, 2, VR::DA, VM::M1, "ProcedureCreationDate" },
{ 0x0018, 0x9337, 0, VR::US, VM::M1, "ContrastBolusAgentNumber" },
{ 0x0018, 0x9727, 0, VR::FD, VM::M1, "AxialDetectorDimension" },
{ 0x0020, 0x930F, 0, VR::SQ, VM::M1, "PlaneOrientationVolumeSequence" },
{ 0x0040, 0x4022, 1, VR::SQ, VM::M1, "RelevantInformationSequence" },
{ 0x4010, 0x1033, 3, VR::US, VM::M1, "NumberOfTotalObjects" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0356[] = {
{ 0x0018, 0x1138, 0, VR::DS, VM::M1, "TableAngle" },
{ 0x0018, 0x9330, 0, VR::FD, VM::M1, "XRayTubeCurrentInmA" },
{ 0x0018, 0x9720, 0, VR::FD, VM::M1, "TerminationDensityThreshold" },
{ 0x0020, 0x9308, 0, VR::FD, VM::M3, "ApexPosition" },
{ 0x0040, 0x4025, 0, VR::SQ, VM::M1, "ScheduledStationNameCodeSequence" },
{ 0x0400, 0x0561, 0, VR::SQ, VM::M1, "OriginalAttributesSequence" },
{ 0x300A, 0x01A8, 0, VR::SH, VM::M1, "ShieldingDevicePosition" },
{ 0x4010, 0x1034, 3, VR::US, VM::M1, "NumberOfAlarmObjects" },
{ 0x5004, 0x0020, 1, VR::CS, VM::M1, "TypeOfData3" },
{ 0x5006, 0x0022, 1, VR::LO, VM::M1, "CurveDescription4" },
{ 0x5014, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0357[] = {
{ 0x0014, 0x4070, 2, VR::SQ, VM::M1, "CalibrationSettingsSequence" },
{ 0x0018, 0x9721, 0, VR::FD, VM::M1, "TerminationRelativeDensityThreshold" },
{ 0x0020, 0x9309, 0, VR::FD, VM::M16, "VolumeToTransducerMappingMatrix" },
{ 0x0022, 0x1103, 0, VR::SQ, VM::M1, "RefractiveErrorBeforeRefractiveSurgeryCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0358[] = {
{ 0x0018, 0x113A, 0, VR::CS, VM::M1, "TableType" },
{ 0x0018, 0x9332, 0, VR::FD, VM::M1, "ExposureInmAs" },
{ 0x0018, 0x9722, 0, VR::FD, VM::M1, "TerminationTimeThreshold" },
{ 0x0020, 0x930A, 0, VR::FD, VM::M16, "VolumeToTableMappingMatrix" },
{ 0x0022, 0x1100, 0, VR::SQ, VM::M1, "ReferencedOphthalmicAxialMeasurementsSequence" },
{ 0x0040, 0x4027, 0, VR::SQ, VM::M1, "ScheduledStationGeographicLocationCodeSequence" },
{ 0x0046, 0x0125, 0, VR::CS, VM::M1, "ViewingDistanceType" },
{ 0x0400, 0x0563, 0, VR::LO, VM::M1, "ModifyingSystem" },
{ 0x5004, 0x0022, 1, VR::LO, VM::M1, "CurveDescription3" },
{ 0x5006, 0x0020, 1, VR::CS, VM::M1, "TypeOfData4" },
{ 0x5016, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0359[] = {
{ 0x0010, 0x21F0, 0, VR::LO, VM::M1, "PatientReligiousPreference" },
{ 0x0014, 0x4072, 2, VR::ST, VM::M1, "CalibrationProcedure" },
{ 0x0018, 0x9333, 0, VR::CS, VM::M1, "ConstantVolumeFlag" },
{ 0x0018, 0x9723, 0, VR::FD, VM::M1, "TerminationCardiacTriggerCountThreshold" },
{ 0x0022, 0x1101, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthMeasurementsSegmentNameCodeSequence" },
{ 0x0040, 0x4026, 0, VR::SQ, VM::M1, "ScheduledStationClassCodeSequence" },
{ 0x0046, 0x0124, 0, VR::SQ, VM::M1, "VisualAcuityBothEyesOpenSequence" },
{ 0x0072, 0x0500, 0, VR::CS, VM::M1, "BlendingOperationType" },
{ 0x0400, 0x0562, 0, VR::DT, VM::M1, "AttributeModificationDateTime" },
{ 0x4010, 0x1037, 3, VR::SQ, VM::M1, "PTORepresentationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0360[] = {
{ 0x0018, 0x1134, 0, VR::CS, VM::M1, "TableMotion" },
{ 0x0018, 0x5030, 1, VR::DS, VM::M1, "DynamicRange" },
{ 0x0028, 0x1104, 0, VR::US, VM::M3, "AlphaPaletteColorLookupTableDescriptor" },
{ 0x0028, 0x5000, 1, VR::SQ, VM::M1, "BiPlaneAcquisitionSequence" },
{ 0x0040, 0x4029, 0, VR::SQ, VM::M1, "PerformedStationClassCodeSequence" },
{ 0x300A, 0x01A4, 0, VR::SH, VM::M1, "ShieldingDeviceLabel" },
{ 0x4010, 0x1038, 3, VR::SQ, VM::M1, "ATDAssessmentSequence" },
{ 0x5008, 0x0020, 1, VR::CS, VM::M1, "TypeOfData5" },
{ 0x500A, 0x0022, 1, VR::LO, VM::M1, "CurveDescription6" },
{ 0x5018, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0361[] = {
{ 0x0008, 0x1125, 0, VR::SQ, VM::M1, "ReferencedVisitSequence" },
{ 0x0014, 0x407C, 2, VR::TM, VM::M1TN, "CalibrationTime" },
{ 0x0018, 0x1135, 0, VR::DS, VM::M1TN, "TableVerticalIncrement" },
{ 0x0040, 0x4028, 0, VR::SQ, VM::M1, "PerformedStationNameCodeSequence" },
{ 0x4010, 0x1039, 3, VR::CS, VM::M1, "TIPType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0362[] = {
{ 0x0018, 0x1136, 0, VR::DS, VM::M1TN, "TableLateralIncrement" },
{ 0x300A, 0x01A6, 0, VR::ST, VM::M1, "ShieldingDeviceDescription" },
{ 0x4010, 0x103A, 3, VR::CS, VM::M1, "DICOSVersion" },
{ 0x5008, 0x0022, 1, VR::LO, VM::M1, "CurveDescription5" },
{ 0x500A, 0x0020, 1, VR::CS, VM::M1, "TypeOfData6" },
{ 0x501A, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0363[] = {
{ 0x0014, 0x407E, 2, VR::DA, VM::M1TN, "CalibrationDate" },
{ 0x0018, 0x1137, 0, VR::DS, VM::M1TN, "TableLongitudinalIncrement" },
{ 0x0020, 0x9307, 0, VR::CS, VM::M1, "UltrasoundAcquisitionGeometry" },
{ 0x0068, 0x6490, 0, VR::FD, VM::M3, "ThreeDDegreeOfFreedomAxis" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0364[] = {
{ 0x0008, 0x1120, 0, VR::SQ, VM::M1, "ReferencedPatientSequence" },
{ 0x0018, 0x1130, 0, VR::DS, VM::M1, "TableHeight" },
{ 0x0018, 0x1520, 0, VR::DS, VM::M1TN, "PositionerPrimaryAngleIncrement" },
{ 0x0018, 0x9338, 0, VR::SQ, VM::M1, "ContrastBolusIngredientCodeSequence" },
{ 0x0028, 0x1100, 1, VR::XS, VM::M3, "GrayLookupTableDescriptor" },
{ 0x300A, 0x01A0, 0, VR::SQ, VM::M1, "ShieldingDeviceSequence" },
{ 0x500C, 0x0020, 1, VR::CS, VM::M1, "TypeOfData7" },
{ 0x500E, 0x0022, 1, VR::LO, VM::M1, "CurveDescription8" },
{ 0x501C, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0365[] = {
{ 0x0014, 0x4078, 2, VR::DA, VM::M1, "ProcedureExpirationDate" },
{ 0x0018, 0x1131, 0, VR::DS, VM::M1, "TableTraverse" },
{ 0x0018, 0x1521, 0, VR::DS, VM::M1TN, "PositionerSecondaryAngleIncrement" },
{ 0x0018, 0x9729, 0, VR::US, VM::M1, "RadiopharmaceuticalAgentNumber" },
{ 0x0020, 0x9301, 0, VR::FD, VM::M3, "ImagePositionVolume" },
{ 0x0028, 0x1101, 0, VR::XS, VM::M3, "RedPaletteColorLookupTableDescriptor" },
{ 0x0048, 0x0120, 0, VR::SQ, VM::M1, "PaletteColorLookupTableSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0366[] = {
{ 0x0020, 0x9302, 0, VR::FD, VM::M6, "ImageOrientationVolume" },
{ 0x0028, 0x1102, 0, VR::XS, VM::M3, "GreenPaletteColorLookupTableDescriptor" },
{ 0x300A, 0x01A2, 0, VR::CS, VM::M1, "ShieldingDeviceType" },
{ 0x500C, 0x0022, 1, VR::LO, VM::M1, "CurveDescription7" },
{ 0x500E, 0x0020, 1, VR::CS, VM::M1, "TypeOfData8" },
{ 0x501E, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0367[] = {
{ 0x0014, 0x407A, 2, VR::DA, VM::M1, "ProcedureLastModifiedDate" },
{ 0x0028, 0x1103, 0, VR::XS, VM::M3, "BluePaletteColorLookupTableDescriptor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0368[] = {
{ 0x0004, 0x1130, 0, VR::CS, VM::M1, "FileSetID" },
{ 0x0018, 0x5028, 0, VR::DS, VM::M1, "SoftTissueFocusThermalIndex" },
{ 0x0018, 0x9324, 0, VR::FD, VM::M1, "EstimatedDoseSaving" },
{ 0x0018, 0x9734, 0, VR::SQ, VM::M1, "PETTableDynamicsSequence" },
{ 0x0040, 0x4031, 1, VR::SQ, VM::M1, "RequestedSubsequentWorkitemCodeSequence" },
{ 0x300A, 0x01BC, 0, VR::DS, VM::M1, "SetupDeviceParameter" },
{ 0x4010, 0x1020, 3, VR::CS, VM::M1, "RouteSegmentLocationIDType" },
{ 0x5000, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits" },
{ 0x5010, 0x0020, 1, VR::CS, VM::M1, "TypeOfData9" },
{ 0x5012, 0x0022, 1, VR::LO, VM::M1, "CurveDescription10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0369[] = {
{ 0x0014, 0x4064, 2, VR::DS, VM::M1, "VelocityOfSound" },
{ 0x0018, 0x5029, 0, VR::DS, VM::M1, "SoftTissueSurfaceThermalIndex" },
{ 0x0018, 0x9325, 0, VR::SQ, VM::M1, "CTXRayDetailsSequence" },
{ 0x0018, 0x9735, 0, VR::SQ, VM::M1, "PETPositionSequence" },
{ 0x0040, 0x4030, 0, VR::SQ, VM::M1, "PerformedStationGeographicLocationCodeSequence" },
{ 0x0072, 0x0106, 0, VR::US, VM::M1, "NumberOfHorizontalPixels" },
{ 0x0072, 0x0516, 0, VR::CS, VM::M1, "ReformattingOperationInitialViewDirection" },
{ 0x4010, 0x1021, 3, VR::CS, VM::M1TN, "AbortReason" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0370[] = {
{ 0x0018, 0x9326, 0, VR::SQ, VM::M1, "CTPositionSequence" },
{ 0x0018, 0x9736, 0, VR::SQ, VM::M1, "PETFrameCorrectionFactorsSequence" },
{ 0x0040, 0x4033, 0, VR::SQ, VM::M1, "OutputInformationSequence" },
{ 0x5002, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits2" },
{ 0x5010, 0x0022, 1, VR::LO, VM::M1, "CurveDescription9" },
{ 0x5012, 0x0020, 1, VR::CS, VM::M1, "TypeOfData10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0371[] = {
{ 0x0018, 0x9327, 0, VR::FD, VM::M1, "TablePosition" },
{ 0x0018, 0x9737, 0, VR::SQ, VM::M1, "RadiopharmaceuticalUsageSequence" },
{ 0x0040, 0x4032, 1, VR::SQ, VM::M1, "NonDICOMOutputCodeSequence" },
{ 0x0072, 0x0104, 0, VR::US, VM::M1, "NumberOfVerticalPixels" },
{ 0x0072, 0x0514, 0, VR::FD, VM::M1, "ReformattingInterval" },
{ 0x4010, 0x1023, 3, VR::FL, VM::M1, "VolumeOfPTO" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0372[] = {
{ 0x0018, 0x9320, 0, VR::SH, VM::M1, "ImageFilter" },
{ 0x0040, 0x4035, 0, VR::SQ, VM::M1, "ActualHumanPerformersSequence" },
{ 0x0046, 0x0137, 0, VR::FD, VM::M1, "DecimalVisualAcuity" },
{ 0x0070, 0x0101, 0, VR::DS, VM::M2, "PresentationPixelSpacing" },
{ 0x300A, 0x01B8, 0, VR::SH, VM::M1, "SetupDeviceLabel" },
{ 0x4010, 0x1024, 3, VR::CS, VM::M1, "AbortFlag" },
{ 0x5004, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits3" },
{ 0x5014, 0x0020, 1, VR::CS, VM::M1, "TypeOfData11" },
{ 0x5016, 0x0022, 1, VR::LO, VM::M1, "CurveDescription12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0373[] = {
{ 0x0014, 0x4060, 2, VR::SQ, VM::M1, "GateSettingsSequence" },
{ 0x0018, 0x9321, 0, VR::SQ, VM::M1, "CTExposureSequence" },
{ 0x0040, 0x0520, 0, VR::SQ, VM::M1, "ContainerComponentSequence" },
{ 0x0040, 0x4034, 0, VR::SQ, VM::M1, "ScheduledHumanPerformersSequence" },
{ 0x0070, 0x0100, 0, VR::CS, VM::M1, "PresentationSizeMode" },
{ 0x0072, 0x0102, 0, VR::SQ, VM::M1, "NominalScreenDefinitionSequence" },
{ 0x0072, 0x0512, 0, VR::FD, VM::M1, "ReformattingThickness" },
{ 0x4010, 0x1025, 3, VR::DT, VM::M1, "RouteSegmentStartTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0374[] = {
{ 0x0008, 0x113A, 0, VR::SQ, VM::M1, "ReferencedWaveformSequence" },
{ 0x0018, 0x9322, 0, VR::FD, VM::M2, "ReconstructionPixelSpacing" },
{ 0x0018, 0x9732, 0, VR::SQ, VM::M1, "PETFrameAcquisitionSequence" },
{ 0x0040, 0x4037, 0, VR::PN, VM::M1, "HumanPerformerName" },
{ 0x0046, 0x0135, 0, VR::SS, VM::M2, "VisualAcuityModifiers" },
{ 0x0070, 0x0103, 0, VR::FL, VM::M1, "PresentationPixelMagnificationRatio" },
{ 0x300A, 0x01BA, 0, VR::ST, VM::M1, "SetupDeviceDescription" },
{ 0x4010, 0x1026, 3, VR::DT, VM::M1, "RouteSegmentEndTime" },
{ 0x5006, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits4" },
{ 0x5014, 0x0022, 1, VR::LO, VM::M1, "CurveDescription11" },
{ 0x5016, 0x0020, 1, VR::CS, VM::M1, "TypeOfData12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0375[] = {
{ 0x0014, 0x4062, 2, VR::DS, VM::M1, "GateThreshold" },
{ 0x0018, 0x9323, 0, VR::CS, VM::M1, "ExposureModulationType" },
{ 0x0018, 0x9733, 0, VR::SQ, VM::M1, "PETDetectorMotionDetailsSequence" },
{ 0x0040, 0x4036, 0, VR::LO, VM::M1, "HumanPerformerOrganization" },
{ 0x0070, 0x0102, 0, VR::IS, VM::M2, "PresentationPixelAspectRatio" },
{ 0x0072, 0x0100, 0, VR::US, VM::M1, "NumberOfScreens" },
{ 0x0072, 0x0510, 0, VR::CS, VM::M1, "ReformattingOperationType" },
{ 0x2130, 0x00C0, 1, VR::SQ, VM::M1, "OriginalImageSequence" },
{ 0x4010, 0x1027, 3, VR::CS, VM::M1, "TDRType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0376[] = {
{ 0x0008, 0x1134, 0, VR::SQ, VM::M1, "ReferencedStereometricInstanceSequence" },
{ 0x0018, 0x5020, 0, VR::LO, VM::M1, "ProcessingFunction" },
{ 0x300A, 0x01B4, 0, VR::SQ, VM::M1, "SetupDeviceSequence" },
{ 0x4010, 0x1028, 3, VR::CS, VM::M1, "InternationalRouteSegment" },
{ 0x5008, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits5" },
{ 0x5018, 0x0020, 1, VR::CS, VM::M1, "TypeOfData13" },
{ 0x501A, 0x0022, 1, VR::LO, VM::M1, "CurveDescription14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0377[] = {
{ 0x0018, 0x5021, 1, VR::LO, VM::M1, "PostprocessingFunction" },
{ 0x0072, 0x010E, 0, VR::US, VM::M1, "ApplicationMaximumRepaintTime" },
{ 0x4010, 0x1029, 3, VR::LO, VM::M1TN, "ThreatDetectionAlgorithmandVersion" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0378[] = {
{ 0x0018, 0x5022, 0, VR::DS, VM::M1, "MechanicalIndex" },
{ 0x0046, 0x0139, 0, VR::LO, VM::M1, "OptotypeDetailedDefinition" },
{ 0x300A, 0x01B6, 0, VR::CS, VM::M1, "SetupDeviceType" },
{ 0x4010, 0x102A, 3, VR::SH, VM::M1, "AssignedLocation" },
{ 0x500A, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits6" },
{ 0x5018, 0x0022, 1, VR::LO, VM::M1, "CurveDescription13" },
{ 0x501A, 0x0020, 1, VR::CS, VM::M1, "TypeOfData14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0379[] = {
{ 0x0072, 0x010C, 0, VR::US, VM::M1, "ScreenMinimumColorBitDepth" },
{ 0x4010, 0x102B, 3, VR::DT, VM::M1, "AlarmDecisionTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0380[] = {
{ 0x0008, 0x1130, 1, VR::SQ, VM::M1, "ReferencedOverlaySequence" },
{ 0x0018, 0x1120, 0, VR::DS, VM::M1, "GantryDetectorTilt" },
{ 0x0018, 0x1530, 0, VR::DS, VM::M1, "DetectorPrimaryAngle" },
{ 0x0018, 0x5024, 0, VR::DS, VM::M1, "BoneThermalIndex" },
{ 0x0018, 0x9328, 0, VR::FD, VM::M1, "ExposureTimeInms" },
{ 0x0018, 0x9738, 0, VR::CS, VM::M1, "AttenuationCorrectionSource" },
{ 0x0020, 0x9310, 0, VR::SQ, VM::M1, "TemporalPositionSequence" },
{ 0x300A, 0x01B0, 0, VR::CS, VM::M1, "SetupTechnique" },
{ 0x500C, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits7" },
{ 0x501C, 0x0020, 1, VR::CS, VM::M1, "TypeOfData15" },
{ 0x501E, 0x0022, 1, VR::LO, VM::M1, "CurveDescription16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0381[] = {
{ 0x0018, 0x1121, 0, VR::DS, VM::M1, "GantryDetectorSlew" },
{ 0x0018, 0x1531, 0, VR::DS, VM::M1, "DetectorSecondaryAngle" },
{ 0x0018, 0x9329, 0, VR::SQ, VM::M1, "CTImageFrameTypeSequence" },
{ 0x0018, 0x9739, 0, VR::US, VM::M1, "NumberOfIterations" },
{ 0x0020, 0x9311, 0, VR::CS, VM::M1, "DimensionOrganizationType" },
{ 0x0028, 0x1111, 1, VR::XS, VM::M4, "LargeRedPaletteColorLookupTableDescriptor" },
{ 0x0072, 0x010A, 0, VR::US, VM::M1, "ScreenMinimumGrayscaleBitDepth" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0382[] = {
{ 0x0018, 0x5026, 0, VR::DS, VM::M1, "CranialThermalIndex" },
{ 0x0020, 0x9312, 0, VR::UI, VM::M1, "VolumeFrameOfReferenceUID" },
{ 0x0028, 0x1112, 1, VR::XS, VM::M4, "LargeGreenPaletteColorLookupTableDescriptor" },
{ 0x300A, 0x01B2, 0, VR::ST, VM::M1, "SetupTechniqueDescription" },
{ 0x500E, 0x0030, 1, VR::SH, VM::M1TN, "AxisUnits8" },
{ 0x501C, 0x0022, 1, VR::LO, VM::M1, "CurveDescription15" },
{ 0x501E, 0x0020, 1, VR::CS, VM::M1, "TypeOfData16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0383[] = {
{ 0x0018, 0x5027, 0, VR::DS, VM::M1, "SoftTissueThermalIndex" },
{ 0x0020, 0x9313, 0, VR::UI, VM::M1, "TableFrameOfReferenceUID" },
{ 0x0028, 0x1113, 1, VR::XS, VM::M4, "LargeBluePaletteColorLookupTableDescriptor" },
{ 0x0072, 0x0108, 0, VR::FD, VM::M4, "DisplayEnvironmentSpatialPosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0384[] = {
{ 0x0018, 0x6018, 0, VR::UL, VM::M1, "RegionLocationMinX0" },
{ 0x5000, 0x3000, 1, VR::OX, VM::M1, "CurveData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0385[] = {
{ 0x0018, 0x7058, 0, VR::FL, VM::M1TN, "FilterBeamPathLengthMaximum" },
{ 0x300A, 0x014E, 0, VR::FL, VM::M1, "GantryPitchAngleTolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0386[] = {
{ 0x0018, 0x601A, 0, VR::UL, VM::M1, "RegionLocationMinY0" },
{ 0x5002, 0x3000, 1, VR::OX, VM::M1, "CurveData2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0387[] = {
{ 0x300A, 0x014C, 0, VR::CS, VM::M1, "GantryPitchRotationDirection" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0388[] = {
{ 0x0010, 0x2110, 0, VR::LO, VM::M1TN, "Allergies" },
{ 0x0014, 0x4092, 2, VR::DS, VM::M1, "ChannelThreshold" },
{ 0x0018, 0x601C, 0, VR::UL, VM::M1, "RegionLocationMaxX1" },
{ 0x2000, 0x0510, 1, VR::SQ, VM::M1, "ReferencedStoredPrintSequence" },
{ 0x2010, 0x0110, 0, VR::CS, VM::M1, "EmptyImageDensity" },
{ 0x2010, 0x0500, 0, VR::SQ, VM::M1, "ReferencedFilmSessionSequence" },
{ 0x2110, 0x0010, 0, VR::CS, VM::M1, "PrinterStatus" },
{ 0x2130, 0x0030, 1, VR::SQ, VM::M1, "FilmBoxContentSequence" },
{ 0x5004, 0x3000, 1, VR::OX, VM::M1, "CurveData3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0389[] = {
{ 0x300A, 0x014A, 0, VR::FL, VM::M1, "GantryPitchAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0390[] = {
{ 0x0018, 0x601E, 0, VR::UL, VM::M1, "RegionLocationMaxY1" },
{ 0x5006, 0x3000, 1, VR::OX, VM::M1, "CurveData4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0391[] = {
{ 0x0014, 0x4091, 2, VR::SQ, VM::M1, "ChannelSettingsSequence" },
{ 0x300A, 0x0148, 0, VR::FL, VM::M1, "HeadFixationAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0392[] = {
{ 0x0028, 0x6020, 0, VR::US, VM::M1TN, "FrameNumbersOfInterest" },
{ 0x0068, 0x6470, 0, VR::SQ, VM::M1, "TwoDDegreeOfFreedomSequence" },
{ 0x5008, 0x3000, 1, VR::OX, VM::M1, "CurveData5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0393[] = {
{ 0x0014, 0x409F, 2, VR::DS, VM::M1, "ChannelOverlap" },
{ 0x0018, 0x6011, 0, VR::SQ, VM::M1, "SequenceOfUltrasoundRegions" },
{ 0x0018, 0x7050, 0, VR::CS, VM::M1TN, "FilterMaterial" },
{ 0x300A, 0x0146, 0, VR::CS, VM::M1, "TableTopRollRotationDirection" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0394[] = {
{ 0x0014, 0x409C, 2, VR::DS, VM::M1, "TranslationRateX" },
{ 0x0018, 0x6012, 0, VR::US, VM::M1, "RegionSpatialFormat" },
{ 0x0028, 0x6022, 0, VR::LO, VM::M1TN, "FrameOfInterestDescription" },
{ 0x500A, 0x3000, 1, VR::OX, VM::M1, "CurveData6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0395[] = {
{ 0x0014, 0x409D, 2, VR::DS, VM::M1, "TranslationRateY" },
{ 0x0018, 0x7052, 0, VR::DS, VM::M1TN, "FilterThicknessMinimum" },
{ 0x0028, 0x6023, 0, VR::CS, VM::M1TN, "FrameOfInterestType" },
{ 0x300A, 0x0144, 0, VR::FL, VM::M1, "TableTopRollAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0396[] = {
{ 0x0014, 0x409A, 2, VR::SQ, VM::M1, "ScannerSettingsSequence" },
{ 0x0018, 0x6014, 0, VR::US, VM::M1, "RegionDataType" },
{ 0x0040, 0xA340, 1, VR::SQ, VM::M1, "ProcedureContextSequenceTrial" },
{ 0x500C, 0x3000, 1, VR::OX, VM::M1, "CurveData7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0397[] = {
{ 0x0014, 0x409B, 2, VR::ST, VM::M1, "ScanProcedure" },
{ 0x0018, 0x7054, 0, VR::DS, VM::M1TN, "FilterThicknessMaximum" },
{ 0x3008, 0x0140, 0, VR::SQ, VM::M1, "RecordedSourceApplicatorSequence" },
{ 0x300A, 0x0142, 0, VR::CS, VM::M1, "TableTopPitchRotationDirection" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0398[] = {
{ 0x0018, 0x6016, 0, VR::UL, VM::M1, "RegionFlags" },
{ 0x500E, 0x3000, 1, VR::OX, VM::M1, "CurveData8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0399[] = {
{ 0x0018, 0x7056, 0, VR::FL, VM::M1TN, "FilterBeamPathLengthMinimum" },
{ 0x3008, 0x0142, 0, VR::IS, VM::M1, "ReferencedSourceApplicatorNumber" },
{ 0x300A, 0x0140, 0, VR::FL, VM::M1, "TableTopPitchAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0400[] = {
{ 0x0014, 0x4086, 2, VR::SQ, VM::M1, "ReceiveProbeSequence" },
{ 0x5010, 0x3000, 1, VR::OX, VM::M1, "CurveData9" },
{ 0x6000, 0x0010, 0, VR::US, VM::M1, "OverlayRows" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0401[] = {
{ 0x0014, 0x4087, 2, VR::SQ, VM::M1, "ProbeDriveSettingsSequence" },
{ 0x0018, 0x7048, 0, VR::DS, VM::M1, "GridPeriod" },
{ 0x6000, 0x0011, 0, VR::US, VM::M1, "OverlayColumns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0402[] = {
{ 0x0014, 0x4084, 2, VR::DS, VM::M1, "ProbeInductance" },
{ 0x5012, 0x3000, 1, VR::OX, VM::M1, "CurveData10" },
{ 0x6000, 0x0012, 1, VR::US, VM::M1, "OverlayPlanes" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0403[] = {
{ 0x0014, 0x4085, 2, VR::DS, VM::M1, "ProbeResistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0404[] = {
{ 0x0014, 0x4082, 2, VR::LT, VM::M1, "ProbeDriveNotes" },
{ 0x0040, 0xA358, 1, VR::SQ, VM::M1, "VerbalSourceIdentifierCodeSequenceTrial" },
{ 0x2000, 0x0500, 0, VR::SQ, VM::M1, "ReferencedFilmBoxSequence" },
{ 0x2010, 0x0100, 0, VR::CS, VM::M1, "BorderDensity" },
{ 0x2010, 0x0510, 0, VR::SQ, VM::M1, "ReferencedImageBoxSequence" },
{ 0x2020, 0x0130, 1, VR::SQ, VM::M1, "ReferencedImageOverlayBoxSequence" },
{ 0x2100, 0x0010, 1, VR::SH, VM::M1, "PrintJobID" },
{ 0x5014, 0x3000, 1, VR::OX, VM::M1, "CurveData11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0405[] = {
{ 0x0014, 0x4083, 2, VR::SQ, VM::M1, "DriveProbeSequence" },
{ 0x0018, 0x704C, 0, VR::DS, VM::M1, "GridFocalDistance" },
{ 0x6000, 0x0015, 0, VR::IS, VM::M1, "NumberOfFramesInOverlay" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0406[] = {
{ 0x0014, 0x4080, 2, VR::SQ, VM::M1, "ProbeDriveEquipmentSequence" },
{ 0x5016, 0x3000, 1, VR::OX, VM::M1, "CurveData12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0407[] = {
{ 0x0014, 0x4081, 2, VR::CS, VM::M1, "DriveType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0408[] = {
{ 0x0014, 0x408E, 2, VR::DS, VM::M1, "UserSelectedOffsetY" },
{ 0x0018, 0x6000, 0, VR::DS, VM::M1, "Sensitivity" },
{ 0x0018, 0x7041, 0, VR::LT, VM::M1, "GridSpacingMaterial" },
{ 0x0028, 0x6030, 1, VR::US, VM::M1TN, "MaskPointers" },
{ 0x0040, 0xA354, 1, VR::LO, VM::M1, "TelephoneNumberTrial" },
{ 0x0040, 0xA744, 1, VR::SQ, VM::M1, "LanguageCodeSequenceTrial" },
{ 0x0068, 0x6460, 0, VR::FD, VM::M4, "TwoDMatingAxes" },
{ 0x5018, 0x3000, 1, VR::OX, VM::M1, "CurveData13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0409[] = {
{ 0x0018, 0x7040, 0, VR::LT, VM::M1, "GridAbsorbingMaterial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0410[] = {
{ 0x0014, 0x408C, 2, VR::DS, VM::M1, "UserSelectedPhase" },
{ 0x501A, 0x3000, 1, VR::OX, VM::M1, "CurveData14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0411[] = {
{ 0x0014, 0x408D, 2, VR::DS, VM::M1, "UserSelectedOffsetX" },
{ 0x0018, 0x7042, 0, VR::DS, VM::M1, "GridThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0412[] = {
{ 0x0008, 0x2110, 1, VR::CS, VM::M1, "LossyImageCompressionRetired" },
{ 0x501C, 0x3000, 1, VR::OX, VM::M1, "CurveData15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0413[] = {
{ 0x0008, 0x2111, 0, VR::ST, VM::M1, "DerivationDescription" },
{ 0x0014, 0x408B, 2, VR::DS, VM::M1, "UserSelectedGainY" },
{ 0x0018, 0x7044, 0, VR::DS, VM::M1, "GridPitch" },
{ 0x3008, 0x0150, 0, VR::SQ, VM::M1, "RecordedChannelShieldSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0414[] = {
{ 0x0008, 0x2112, 0, VR::SQ, VM::M1, "SourceImageSequence" },
{ 0x0014, 0x4088, 2, VR::DS, VM::M1, "BridgeResistors" },
{ 0x0040, 0x09F8, 1, VR::SQ, VM::M1, "VitalStainCodeSequenceTrial" },
{ 0x0040, 0xA352, 1, VR::PN, VM::M1, "VerbalSourceTrial" },
{ 0x501E, 0x3000, 1, VR::OX, VM::M1, "CurveData16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0415[] = {
{ 0x0014, 0x4089, 2, VR::DS, VM::M1, "ProbeOrientationAngle" },
{ 0x0018, 0x7046, 0, VR::IS, VM::M2, "GridAspectRatio" },
{ 0x0040, 0xA353, 1, VR::ST, VM::M1, "AddressTrial" },
{ 0x3008, 0x0152, 0, VR::IS, VM::M1, "ReferencedChannelShieldNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0416[] = {
{ 0x0018, 0x6038, 1, VR::UL, VM::M1, "DopplerSampleVolumeXPositionRetired" },
{ 0x6000, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel" },
{ 0x6002, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables2" },
{ 0x6004, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0417[] = {
{ 0x0018, 0x6039, 0, VR::SL, VM::M1, "DopplerSampleVolumeXPosition" },
{ 0x2130, 0x0015, 1, VR::SQ, VM::M1, "PrinterCharacteristicsSequence" },
{ 0x6002, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0418[] = {
{ 0x0018, 0x603A, 1, VR::UL, VM::M1, "DopplerSampleVolumeYPositionRetired" },
{ 0x6000, 0x0022, 0, VR::LO, VM::M1, "OverlayDescription" },
{ 0x6000, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables" },
{ 0x6002, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel2" },
{ 0x6006, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0419[] = {
{ 0x0018, 0x603B, 0, VR::SL, VM::M1, "DopplerSampleVolumeYPosition" },
{ 0x6000, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0420[] = {
{ 0x0008, 0x2128, 0, VR::IS, VM::M1, "ViewNumber" },
{ 0x0018, 0x603C, 1, VR::UL, VM::M1, "TMLinePositionX0Retired" },
{ 0x2010, 0x0130, 0, VR::US, VM::M1, "MaxDensity" },
{ 0x2010, 0x0520, 0, VR::SQ, VM::M1, "ReferencedBasicAnnotationBoxSequence" },
{ 0x2100, 0x0020, 0, VR::CS, VM::M1, "ExecutionStatus" },
{ 0x2110, 0x0030, 0, VR::LO, VM::M1, "PrinterName" },
{ 0x2130, 0x0010, 1, VR::SQ, VM::M1, "PrintManagementCapabilitiesSequence" },
{ 0x6000, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord" },
{ 0x6004, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel3" },
{ 0x6006, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0421[] = {
{ 0x0008, 0x2129, 0, VR::IS, VM::M1, "NumberOfEventTimers" },
{ 0x0018, 0x603D, 0, VR::SL, VM::M1, "TMLinePositionX0" },
{ 0x3008, 0x0168, 0, VR::TM, VM::M1, "SafePositionReturnTime" },
{ 0x6006, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0422[] = {
{ 0x0008, 0x212A, 0, VR::IS, VM::M1, "NumberOfViewsInStage" },
{ 0x0018, 0x603E, 1, VR::UL, VM::M1, "TMLinePositionY0Retired" },
{ 0x6002, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord2" },
{ 0x6004, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables3" },
{ 0x6006, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0423[] = {
{ 0x0018, 0x603F, 0, VR::SL, VM::M1, "TMLinePositionY0" },
{ 0x6004, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0424[] = {
{ 0x0008, 0x2124, 0, VR::IS, VM::M1, "NumberOfStages" },
{ 0x0018, 0x6030, 0, VR::UL, VM::M1, "TransducerFrequency" },
{ 0x0068, 0x6450, 0, VR::FD, VM::M2, "TwoDMatingPoint" },
{ 0x0088, 0x0906, 1, VR::ST, VM::M1, "TopicSubject" },
{ 0x6008, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel5" },
{ 0x600A, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables6" },
{ 0x600C, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0425[] = {
{ 0x0018, 0x6031, 0, VR::CS, VM::M1, "TransducerType" },
{ 0x3008, 0x0164, 0, VR::TM, VM::M1, "SafePositionExitTime" },
{ 0x600A, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0426[] = {
{ 0x0018, 0x6032, 0, VR::UL, VM::M1, "PulseRepetitionFrequency" },
{ 0x0088, 0x0904, 1, VR::LO, VM::M1, "TopicTitle" },
{ 0x6008, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables5" },
{ 0x600A, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel6" },
{ 0x600E, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0427[] = {
{ 0x0008, 0x2127, 0, VR::SH, VM::M1, "ViewName" },
{ 0x3008, 0x0166, 0, VR::DA, VM::M1, "SafePositionReturnDate" },
{ 0x6008, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0428[] = {
{ 0x0008, 0x2120, 0, VR::SH, VM::M1, "StageName" },
{ 0x0018, 0x6034, 0, VR::FD, VM::M1, "DopplerCorrectionAngle" },
{ 0x0040, 0xA360, 0, VR::SQ, VM::M1, "PredecessorDocumentsSequence" },
{ 0x6008, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord5" },
{ 0x600C, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel7" },
{ 0x600E, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0429[] = {
{ 0x3008, 0x0160, 0, VR::SQ, VM::M1, "BrachyControlPointDeliveredSequence" },
{ 0x600E, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0430[] = {
{ 0x0008, 0x2122, 0, VR::IS, VM::M1, "StageNumber" },
{ 0x0018, 0x6036, 0, VR::FD, VM::M1, "SteeringAngle" },
{ 0x600A, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord6" },
{ 0x600C, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables7" },
{ 0x600E, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0431[] = {
{ 0x3008, 0x0162, 0, VR::DA, VM::M1, "SafePositionExitDate" },
{ 0x600C, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0432[] = {
{ 0x0018, 0x6028, 0, VR::FD, VM::M1, "ReferencePixelPhysicalValueX" },
{ 0x6010, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel9" },
{ 0x6012, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables10" },
{ 0x6014, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0433[] = {
{ 0x6012, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0434[] = {
{ 0x0018, 0x602A, 0, VR::FD, VM::M1, "ReferencePixelPhysicalValueY" },
{ 0x6010, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables9" },
{ 0x6012, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel10" },
{ 0x6016, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0435[] = {
{ 0x6010, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0436[] = {
{ 0x0014, 0x40A2, 2, VR::LO, VM::M1, "ImageQualityIndicatorSize" },
{ 0x0018, 0x602C, 0, VR::FD, VM::M1, "PhysicalDeltaX" },
{ 0x2010, 0x0120, 0, VR::US, VM::M1, "MinDensity" },
{ 0x2020, 0x0110, 0, VR::SQ, VM::M1, "BasicGrayscaleImageSequence" },
{ 0x2100, 0x0030, 0, VR::CS, VM::M1, "ExecutionStatusInfo" },
{ 0x2110, 0x0020, 0, VR::CS, VM::M1, "PrinterStatusInfo" },
{ 0x2120, 0x0010, 1, VR::CS, VM::M1, "QueueStatus" },
{ 0x6010, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord9" },
{ 0x6014, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel11" },
{ 0x6016, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0437[] = {
{ 0x2020, 0x0111, 0, VR::SQ, VM::M1, "BasicColorImageSequence" },
{ 0x6016, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0438[] = {
{ 0x0014, 0x40A0, 2, VR::LO, VM::M1, "ImageQualityIndicatorType" },
{ 0x0018, 0x602E, 0, VR::FD, VM::M1, "PhysicalDeltaY" },
{ 0x6012, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord10" },
{ 0x6014, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables11" },
{ 0x6016, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0439[] = {
{ 0x0014, 0x40A1, 2, VR::LO, VM::M1, "ImageQualityIndicatorMaterial" },
{ 0x6014, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0440[] = {
{ 0x0008, 0x2134, 0, VR::FD, VM::M1, "EventTimeOffset" },
{ 0x0018, 0x6020, 0, VR::SL, VM::M1, "ReferencePixelX0" },
{ 0x0028, 0x2114, 0, VR::CS, VM::M1TN, "LossyImageCompressionMethod" },
{ 0x0028, 0x6010, 0, VR::US, VM::M1, "RepresentativeFrameNumber" },
{ 0x0068, 0x6440, 0, VR::US, VM::M1, "ReferencedHPGLDocumentID" },
{ 0x6018, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel13" },
{ 0x601A, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables14" },
{ 0x601C, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0441[] = {
{ 0x0008, 0x2135, 0, VR::SQ, VM::M1, "EventCodeSequence" },
{ 0x0018, 0x7060, 0, VR::CS, VM::M1, "ExposureControlMode" },
{ 0x0040, 0xA375, 0, VR::SQ, VM::M1, "CurrentRequestedProcedureEvidenceSequence" },
{ 0x601A, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0442[] = {
{ 0x0018, 0x6022, 0, VR::SL, VM::M1, "ReferencePixelY0" },
{ 0x6018, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables13" },
{ 0x601A, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel14" },
{ 0x601E, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0443[] = {
{ 0x0018, 0x7062, 0, VR::LT, VM::M1, "ExposureControlModeDescription" },
{ 0x6018, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0444[] = {
{ 0x0008, 0x2130, 0, VR::DS, VM::M1TN, "EventElapsedTimes" },
{ 0x0018, 0x6024, 0, VR::US, VM::M1, "PhysicalUnitsXDirection" },
{ 0x0018, 0x7065, 0, VR::DS, VM::M1, "PhototimerSetting" },
{ 0x0028, 0x2110, 0, VR::CS, VM::M1, "LossyImageCompression" },
{ 0x0040, 0xA370, 0, VR::SQ, VM::M1, "ReferencedRequestSequence" },
{ 0x0088, 0x0912, 1, VR::LO, VM::M1T32, "TopicKeywords" },
{ 0x6018, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord13" },
{ 0x601C, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel15" },
{ 0x601E, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0445[] = {
{ 0x0018, 0x7064, 0, VR::CS, VM::M1, "ExposureStatus" },
{ 0x601E, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0446[] = {
{ 0x0008, 0x2132, 0, VR::LO, VM::M1TN, "EventTimerNames" },
{ 0x0018, 0x6026, 0, VR::US, VM::M1, "PhysicalUnitsYDirection" },
{ 0x0028, 0x2112, 0, VR::DS, VM::M1TN, "LossyImageCompressionRatio" },
{ 0x0040, 0xA372, 0, VR::SQ, VM::M1, "PerformedProcedureCodeSequence" },
{ 0x0088, 0x0130, 0, VR::SH, VM::M1, "StorageMediaFileSetID" },
{ 0x0088, 0x0910, 1, VR::LO, VM::M1, "TopicAuthor" },
{ 0x601A, 0x0804, 1, VR::US, VM::M1, "OverlayBitsForCodeWord14" },
{ 0x601C, 0x0802, 1, VR::US, VM::M1, "OverlayNumberOfTables15" },
{ 0x601E, 0x0800, 1, VR::CS, VM::M1TN, "OverlayCodeLabel16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0447[] = {
{ 0x0008, 0x2133, 0, VR::SQ, VM::M1, "EventTimerSequence" },
{ 0x601C, 0x0803, 1, VR::AT, VM::M1TN, "OverlayCodeTableLocation15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0448[] = {
{ 0x300A, 0x010E, 0, VR::DS, VM::M1, "FinalCumulativeMetersetWeight" },
{ 0x5000, 0x2000, 1, VR::US, VM::M1, "AudioType" },
{ 0x5002, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat2" },
{ 0x5004, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels3" },
{ 0x5006, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples4" },
{ 0x5008, 0x2008, 1, VR::UL, VM::M1, "SampleRate5" },
{ 0x500A, 0x200A, 1, VR::UL, VM::M1, "TotalTime6" },
{ 0x500C, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData7" },
{ 0x500E, 0x200E, 1, VR::LT, VM::M1, "AudioComments8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0449[] = {
{ 0x0010, 0x2154, 0, VR::SH, VM::M1TN, "PatientTelephoneNumbers" },
{ 0x0018, 0x6058, 0, VR::UL, VM::M1TN, "TableOfPixelValues" },
{ 0x2010, 0x0154, 0, VR::IS, VM::M1, "MaximumCollatedFilms" },
{ 0x6000, 0x0040, 0, VR::CS, VM::M1, "OverlayType" },
{ 0x6000, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0450[] = {
{ 0x0018, 0x701A, 0, VR::DS, VM::M2, "DetectorBinning" },
{ 0x300A, 0x010C, 0, VR::DS, VM::M1, "CumulativeDoseReferenceCoefficient" },
{ 0x5000, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat" },
{ 0x5002, 0x2000, 1, VR::US, VM::M1, "AudioType2" },
{ 0x5004, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples3" },
{ 0x5006, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels4" },
{ 0x5008, 0x200A, 1, VR::UL, VM::M1, "TotalTime5" },
{ 0x500A, 0x2008, 1, VR::UL, VM::M1, "SampleRate6" },
{ 0x500C, 0x200E, 1, VR::LT, VM::M1, "AudioComments7" },
{ 0x500E, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0451[] = {
{ 0x0018, 0x605A, 0, VR::FL, VM::M1TN, "TableOfParameterValues" },
{ 0x6002, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0452[] = {
{ 0x300A, 0x010A, 0, VR::LO, VM::M1, "ApplicatorDescription" },
{ 0x5000, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels" },
{ 0x5002, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples2" },
{ 0x5004, 0x2000, 1, VR::US, VM::M1, "AudioType3" },
{ 0x5006, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat4" },
{ 0x5008, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData5" },
{ 0x500A, 0x200E, 1, VR::LT, VM::M1, "AudioComments6" },
{ 0x500C, 0x2008, 1, VR::UL, VM::M1, "SampleRate7" },
{ 0x500E, 0x200A, 1, VR::UL, VM::M1, "TotalTime8" },
{ 0x6000, 0x0045, 0, VR::LO, VM::M1, "OverlaySubtype" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0453[] = {
{ 0x0010, 0x2150, 0, VR::LO, VM::M1, "CountryOfResidence" },
{ 0x2010, 0x0150, 0, VR::ST, VM::M1, "ConfigurationInformation" },
{ 0x2040, 0x0100, 1, VR::CS, VM::M1, "ThresholdDensity" },
{ 0x2050, 0x0500, 0, VR::SQ, VM::M1, "ReferencedPresentationLUTSequence" },
{ 0x2100, 0x0040, 0, VR::DA, VM::M1, "CreationDate" },
{ 0x6004, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0454[] = {
{ 0x300A, 0x0108, 0, VR::SH, VM::M1, "ApplicatorID" },
{ 0x5000, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples" },
{ 0x5002, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels2" },
{ 0x5004, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat3" },
{ 0x5006, 0x2000, 1, VR::US, VM::M1, "AudioType4" },
{ 0x5008, 0x200E, 1, VR::LT, VM::M1, "AudioComments5" },
{ 0x500A, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData6" },
{ 0x500C, 0x200A, 1, VR::UL, VM::M1, "TotalTime7" },
{ 0x500E, 0x2008, 1, VR::UL, VM::M1, "SampleRate8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0455[] = {
{ 0x0010, 0x2152, 0, VR::LO, VM::M1, "RegionOfResidence" },
{ 0x0040, 0xA30A, 0, VR::DS, VM::M1TN, "NumericValue" },
{ 0x2010, 0x0152, 0, VR::LT, VM::M1, "ConfigurationInformationDescription" },
{ 0x300A, 0x0109, 0, VR::CS, VM::M1, "ApplicatorType" },
{ 0x6006, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0456[] = {
{ 0x0018, 0x7010, 0, VR::IS, VM::M1, "ExposuresOnDetectorSinceLastCalibration" },
{ 0x300A, 0x0106, 0, VR::DS, VM::M2T2N, "BlockData" },
{ 0x300C, 0x0100, 0, VR::IS, VM::M1, "ReferencedRangeShifterNumber" },
{ 0x5000, 0x2008, 1, VR::UL, VM::M1, "SampleRate" },
{ 0x5002, 0x200A, 1, VR::UL, VM::M1, "TotalTime2" },
{ 0x5004, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData3" },
{ 0x5006, 0x200E, 1, VR::LT, VM::M1, "AudioComments4" },
{ 0x5008, 0x2000, 1, VR::US, VM::M1, "AudioType5" },
{ 0x500A, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat6" },
{ 0x500C, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels7" },
{ 0x500E, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0457[] = {
{ 0x0008, 0x2144, 0, VR::IS, VM::M1, "RecommendedDisplayFrameRate" },
{ 0x0018, 0x6050, 0, VR::UL, VM::M1, "NumberOfTableBreakPoints" },
{ 0x0018, 0x7011, 0, VR::IS, VM::M1, "ExposuresOnDetectorSinceManufactured" },
{ 0x0068, 0x6430, 0, VR::SQ, VM::M1, "TwoDMatingFeatureCoordinatesSequence" },
{ 0x3008, 0x0105, 0, VR::LO, VM::M1, "SourceSerialNumber" },
{ 0x300A, 0x0107, 0, VR::SQ, VM::M1, "ApplicatorSequence" },
{ 0x6008, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0458[] = {
{ 0x0018, 0x7012, 0, VR::DS, VM::M1, "DetectorTimeSinceLastExposure" },
{ 0x0040, 0xA307, 1, VR::PN, VM::M1, "CurrentObserverTrial" },
{ 0x300A, 0x0104, 0, VR::IS, VM::M1, "BlockNumberOfPoints" },
{ 0x300C, 0x0102, 0, VR::IS, VM::M1, "ReferencedLateralSpreadingDeviceNumber" },
{ 0x5000, 0x200A, 1, VR::UL, VM::M1, "TotalTime" },
{ 0x5002, 0x2008, 1, VR::UL, VM::M1, "SampleRate2" },
{ 0x5004, 0x200E, 1, VR::LT, VM::M1, "AudioComments3" },
{ 0x5006, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData4" },
{ 0x5008, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat5" },
{ 0x500A, 0x2000, 1, VR::US, VM::M1, "AudioType6" },
{ 0x500C, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples7" },
{ 0x500E, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0459[] = {
{ 0x0018, 0x6052, 0, VR::UL, VM::M1TN, "TableOfXBreakPoints" },
{ 0x2010, 0x015E, 0, VR::US, VM::M1, "Illumination" },
{ 0x600A, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0460[] = {
{ 0x0018, 0x7014, 0, VR::DS, VM::M1, "DetectorActiveTime" },
{ 0x0040, 0xA301, 0, VR::SQ, VM::M1, "NumericValueQualifierCodeSequence" },
{ 0x3008, 0x0100, 0, VR::SQ, VM::M1, "RecordedSourceSequence" },
{ 0x300A, 0x0102, 0, VR::DS, VM::M1, "BlockTransmission" },
{ 0x300C, 0x0104, 0, VR::IS, VM::M1, "ReferencedRangeModulatorNumber" },
{ 0x5000, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData" },
{ 0x5002, 0x200E, 1, VR::LT, VM::M1, "AudioComments2" },
{ 0x5004, 0x2008, 1, VR::UL, VM::M1, "SampleRate3" },
{ 0x5006, 0x200A, 1, VR::UL, VM::M1, "TotalTime4" },
{ 0x5008, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels5" },
{ 0x500A, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples6" },
{ 0x500C, 0x2000, 1, VR::US, VM::M1, "AudioType7" },
{ 0x500E, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0461[] = {
{ 0x0018, 0x6054, 0, VR::FD, VM::M1TN, "TableOfYBreakPoints" },
{ 0x0040, 0x059A, 0, VR::SQ, VM::M1, "SpecimenTypeCodeSequence" },
{ 0x0040, 0xA300, 0, VR::SQ, VM::M1, "MeasuredValueSequence" },
{ 0x600C, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0462[] = {
{ 0x0008, 0x2143, 0, VR::IS, VM::M1, "StopTrim" },
{ 0x0018, 0x1190, 0, VR::DS, VM::M1TN, "FocalSpots" },
{ 0x0018, 0x7016, 0, VR::DS, VM::M1, "DetectorActivationOffsetFromExposure" },
{ 0x300A, 0x0100, 0, VR::DS, VM::M1, "BlockThickness" },
{ 0x5000, 0x200E, 1, VR::LT, VM::M1, "AudioComments" },
{ 0x5002, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData2" },
{ 0x5004, 0x200A, 1, VR::UL, VM::M1, "TotalTime3" },
{ 0x5006, 0x2008, 1, VR::UL, VM::M1, "SampleRate4" },
{ 0x5008, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples5" },
{ 0x500A, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels6" },
{ 0x500C, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat7" },
{ 0x500E, 0x2000, 1, VR::US, VM::M1, "AudioType8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0463[] = {
{ 0x0008, 0x2142, 0, VR::IS, VM::M1, "StartTrim" },
{ 0x0018, 0x1191, 0, VR::CS, VM::M1, "AnodeTargetMaterial" },
{ 0x0018, 0x6056, 0, VR::UL, VM::M1, "NumberOfTableEntries" },
{ 0x0088, 0x0140, 0, VR::UI, VM::M1, "StorageMediaFileSetUID" },
{ 0x600E, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0464[] = {
{ 0x0018, 0x7008, 0, VR::LT, VM::M1, "DetectorMode" },
{ 0x300A, 0x011E, 0, VR::DS, VM::M1, "GantryAngle" },
{ 0x5010, 0x2000, 1, VR::US, VM::M1, "AudioType9" },
{ 0x5012, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat10" },
{ 0x5014, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels11" },
{ 0x5016, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples12" },
{ 0x5018, 0x2008, 1, VR::UL, VM::M1, "SampleRate13" },
{ 0x501A, 0x200A, 1, VR::UL, VM::M1, "TotalTime14" },
{ 0x501C, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData15" },
{ 0x501E, 0x200E, 1, VR::LT, VM::M1, "AudioComments16" },
{ 0x6000, 0x0051, 0, VR::US, VM::M1, "ImageFrameOrigin" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0465[] = {
{ 0x0018, 0x6048, 0, VR::UL, VM::M1, "PixelComponentRangeStart" },
{ 0x300A, 0x011F, 0, VR::CS, VM::M1, "GantryRotationDirection" },
{ 0x6000, 0x0050, 0, VR::SS, VM::M2, "OverlayOrigin" },
{ 0x6010, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0466[] = {
{ 0x0018, 0x700A, 0, VR::SH, VM::M1, "DetectorID" },
{ 0x300A, 0x011C, 0, VR::DS, VM::M2T2N, "LeafJawPositions" },
{ 0x5010, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat9" },
{ 0x5012, 0x2000, 1, VR::US, VM::M1, "AudioType10" },
{ 0x5014, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples11" },
{ 0x5016, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels12" },
{ 0x5018, 0x200A, 1, VR::UL, VM::M1, "TotalTime13" },
{ 0x501A, 0x2008, 1, VR::UL, VM::M1, "SampleRate14" },
{ 0x501C, 0x200E, 1, VR::LT, VM::M1, "AudioComments15" },
{ 0x501E, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0467[] = {
{ 0x0018, 0x604A, 0, VR::UL, VM::M1, "PixelComponentRangeStop" },
{ 0x6000, 0x0052, 1, VR::US, VM::M1, "OverlayPlaneOrigin" },
{ 0x6012, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0468[] = {
{ 0x0018, 0x700C, 0, VR::DA, VM::M1, "DateOfLastDetectorCalibration" },
{ 0x300A, 0x011A, 0, VR::SQ, VM::M1, "BeamLimitingDevicePositionSequence" },
{ 0x5010, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels9" },
{ 0x5012, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples10" },
{ 0x5014, 0x2000, 1, VR::US, VM::M1, "AudioType11" },
{ 0x5016, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat12" },
{ 0x5018, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData13" },
{ 0x501A, 0x200E, 1, VR::LT, VM::M1, "AudioComments14" },
{ 0x501C, 0x2008, 1, VR::UL, VM::M1, "SampleRate15" },
{ 0x501E, 0x200A, 1, VR::UL, VM::M1, "TotalTime16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0469[] = {
{ 0x0018, 0x604C, 0, VR::US, VM::M1, "PixelComponentPhysicalUnits" },
{ 0x2010, 0x0140, 0, VR::CS, VM::M1, "Trim" },
{ 0x2040, 0x0500, 1, VR::SQ, VM::M1, "ReferencedImageBoxSequenceRetired" },
{ 0x2100, 0x0050, 0, VR::TM, VM::M1, "CreationTime" },
{ 0x2120, 0x0070, 1, VR::SQ, VM::M1, "ReferencedPrintJobSequence" },
{ 0x2130, 0x0060, 1, VR::SQ, VM::M1, "ImageOverlayBoxContentSequence" },
{ 0x6014, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0470[] = {
{ 0x0008, 0x1198, 0, VR::SQ, VM::M1, "FailedSOPSequence" },
{ 0x0018, 0x700E, 0, VR::TM, VM::M1, "TimeOfLastDetectorCalibration" },
{ 0x300A, 0x0118, 0, VR::CS, VM::M1, "WedgePosition" },
{ 0x5010, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples9" },
{ 0x5012, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels10" },
{ 0x5014, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat11" },
{ 0x5016, 0x2000, 1, VR::US, VM::M1, "AudioType12" },
{ 0x5018, 0x200E, 1, VR::LT, VM::M1, "AudioComments13" },
{ 0x501A, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData14" },
{ 0x501C, 0x200A, 1, VR::UL, VM::M1, "TotalTime15" },
{ 0x501E, 0x2008, 1, VR::UL, VM::M1, "SampleRate16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0471[] = {
{ 0x0008, 0x1199, 0, VR::SQ, VM::M1, "ReferencedSOPSequence" },
{ 0x0018, 0x604E, 0, VR::US, VM::M1, "PixelComponentDataType" },
{ 0x6016, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0472[] = {
{ 0x0008, 0x1196, 0, VR::US, VM::M1, "WarningReason" },
{ 0x0018, 0x3104, 0, VR::IS, VM::M1, "IVUSPullbackStopFrameNumber" },
{ 0x0018, 0x6041, 0, VR::SL, VM::M1, "TMLinePositionX1" },
{ 0x0018, 0x7000, 0, VR::CS, VM::M1, "DetectorConditionsNominalFlag" },
{ 0x300A, 0x0116, 0, VR::SQ, VM::M1, "WedgePositionSequence" },
{ 0x5010, 0x2008, 1, VR::UL, VM::M1, "SampleRate9" },
{ 0x5012, 0x200A, 1, VR::UL, VM::M1, "TotalTime10" },
{ 0x5014, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData11" },
{ 0x5016, 0x200E, 1, VR::LT, VM::M1, "AudioComments12" },
{ 0x5018, 0x2000, 1, VR::US, VM::M1, "AudioType13" },
{ 0x501A, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat14" },
{ 0x501C, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels15" },
{ 0x501E, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0473[] = {
{ 0x0008, 0x1197, 0, VR::US, VM::M1, "FailureReason" },
{ 0x0018, 0x3105, 0, VR::IS, VM::M1TN, "LesionNumber" },
{ 0x0018, 0x6040, 1, VR::UL, VM::M1, "TMLinePositionX1Retired" },
{ 0x0018, 0x7001, 0, VR::DS, VM::M1, "DetectorTemperature" },
{ 0x0068, 0x6420, 0, VR::CS, VM::M1, "DegreeOfFreedomType" },
{ 0x6018, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0474[] = {
{ 0x0018, 0x1184, 0, VR::DS, VM::M1T2, "YFocusCenter" },
{ 0x0018, 0x6043, 0, VR::SL, VM::M1, "TMLinePositionY1" },
{ 0x3008, 0x0116, 0, VR::CS, VM::M1, "ApplicationSetupCheck" },
{ 0x300A, 0x0114, 0, VR::DS, VM::M1, "NominalBeamEnergy" },
{ 0x5010, 0x200A, 1, VR::UL, VM::M1, "TotalTime9" },
{ 0x5012, 0x2008, 1, VR::UL, VM::M1, "SampleRate10" },
{ 0x5014, 0x200E, 1, VR::LT, VM::M1, "AudioComments11" },
{ 0x5016, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData12" },
{ 0x5018, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat13" },
{ 0x501A, 0x2000, 1, VR::US, VM::M1, "AudioType14" },
{ 0x501C, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples15" },
{ 0x501E, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0475[] = {
{ 0x0008, 0x1195, 0, VR::UI, VM::M1, "TransactionUID" },
{ 0x0018, 0x6042, 1, VR::UL, VM::M1, "TMLinePositionY1Retired" },
{ 0x300A, 0x0115, 0, VR::DS, VM::M1, "DoseRateSet" },
{ 0x601A, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0476[] = {
{ 0x0018, 0x1182, 0, VR::IS, VM::M1T2, "FocalDistance" },
{ 0x0018, 0x3100, 0, VR::CS, VM::M1, "IVUSAcquisition" },
{ 0x0018, 0x7004, 0, VR::CS, VM::M1, "DetectorType" },
{ 0x3008, 0x0110, 0, VR::SQ, VM::M1, "TreatmentSessionApplicationSetupSequence" },
{ 0x300A, 0x0112, 0, VR::IS, VM::M1, "ControlPointIndex" },
{ 0x5010, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData9" },
{ 0x5012, 0x200E, 1, VR::LT, VM::M1, "AudioComments10" },
{ 0x5014, 0x2008, 1, VR::UL, VM::M1, "SampleRate11" },
{ 0x5016, 0x200A, 1, VR::UL, VM::M1, "TotalTime12" },
{ 0x5018, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels13" },
{ 0x501A, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples14" },
{ 0x501C, 0x2000, 1, VR::US, VM::M1, "AudioType15" },
{ 0x501E, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0477[] = {
{ 0x0018, 0x1183, 0, VR::DS, VM::M1T2, "XFocusCenter" },
{ 0x0018, 0x3101, 0, VR::DS, VM::M1, "IVUSPullbackRate" },
{ 0x0018, 0x6044, 0, VR::US, VM::M1, "PixelComponentOrganization" },
{ 0x0018, 0x7005, 0, VR::CS, VM::M1, "DetectorConfiguration" },
{ 0x601C, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0478[] = {
{ 0x0008, 0x1190, 0, VR::UT, VM::M1, "RetrieveURL" },
{ 0x0018, 0x1180, 0, VR::SH, VM::M1, "CollimatorGridName" },
{ 0x0018, 0x3102, 0, VR::DS, VM::M1, "IVUSGatedRate" },
{ 0x0018, 0x7006, 0, VR::LT, VM::M1, "DetectorDescription" },
{ 0x0040, 0xA313, 1, VR::SQ, VM::M1, "ReferencedAccessionSequenceTrial" },
{ 0x300A, 0x0110, 0, VR::IS, VM::M1, "NumberOfControlPoints" },
{ 0x5010, 0x200E, 1, VR::LT, VM::M1, "AudioComments9" },
{ 0x5012, 0x200C, 1, VR::OX, VM::M1, "AudioSampleData10" },
{ 0x5014, 0x200A, 1, VR::UL, VM::M1, "TotalTime11" },
{ 0x5016, 0x2008, 1, VR::UL, VM::M1, "SampleRate12" },
{ 0x5018, 0x2006, 1, VR::UL, VM::M1, "NumberOfSamples13" },
{ 0x501A, 0x2004, 1, VR::US, VM::M1, "NumberOfChannels14" },
{ 0x501C, 0x2002, 1, VR::US, VM::M1, "AudioSampleFormat15" },
{ 0x501E, 0x2000, 1, VR::US, VM::M1, "AudioType16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0479[] = {
{ 0x0018, 0x1181, 0, VR::CS, VM::M1, "CollimatorType" },
{ 0x0018, 0x3103, 0, VR::IS, VM::M1, "IVUSPullbackStartFrameNumber" },
{ 0x0018, 0x6046, 0, VR::UL, VM::M1, "PixelComponentMask" },
{ 0x300A, 0x0111, 0, VR::SQ, VM::M1, "ControlPointSequence" },
{ 0x601E, 0x1001, 0, VR::CS, VM::M1, "OverlayActivationLayer16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0480[] = {
{ 0x0018, 0x7038, 0, VR::FL, VM::M1, "PixelDataAreaRotationAngleRelativeToFOV" },
{ 0x300A, 0x012E, 0, VR::DS, VM::M3, "SurfaceEntryPoint" },
{ 0x6000, 0x0061, 1, VR::SH, VM::M1, "OverlayCompressionOriginator" },
{ 0x6008, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0481[] = {
{ 0x6000, 0x0060, 1, VR::CS, VM::M1, "OverlayCompressionCode" },
{ 0x6008, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0482[] = {
{ 0x300A, 0x012C, 0, VR::DS, VM::M3, "IsocenterPosition" },
{ 0x6000, 0x0063, 1, VR::CS, VM::M1, "OverlayCompressionDescription" },
{ 0x600A, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0483[] = {
{ 0x6000, 0x0062, 1, VR::SH, VM::M1, "OverlayCompressionLabel" },
{ 0x600A, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0484[] = {
{ 0x0020, 0x3100, 1, VR::CS, VM::M1TN, "SourceImageIDs" },
{ 0x300A, 0x012A, 0, VR::DS, VM::M1, "TableTopLateralPosition" },
{ 0x600C, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0485[] = {
{ 0x2020, 0x0140, 1, VR::SQ, VM::M1, "ReferencedVOILUTBoxSequence" },
{ 0x2130, 0x0050, 1, VR::SQ, VM::M1, "AnnotationContentSequence" },
{ 0x600C, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0486[] = {
{ 0x300A, 0x0128, 0, VR::DS, VM::M1, "TableTopVerticalPosition" },
{ 0x600E, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0487[] = {
{ 0x300A, 0x0129, 0, VR::DS, VM::M1, "TableTopLongitudinalPosition" },
{ 0x6000, 0x0066, 1, VR::AT, VM::M1TN, "OverlayCompressionStepPointers" },
{ 0x600E, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0488[] = {
{ 0x0018, 0x7030, 0, VR::DS, VM::M2, "FieldOfViewOrigin" },
{ 0x300A, 0x0126, 0, VR::CS, VM::M1, "TableTopEccentricRotationDirection" },
{ 0x6000, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0489[] = {
{ 0x0028, 0x6040, 0, VR::US, VM::M1TN, "RWavePointer" },
{ 0x0068, 0x6410, 0, VR::US, VM::M1, "DegreeOfFreedomID" },
{ 0x6000, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0490[] = {
{ 0x0018, 0x7032, 0, VR::DS, VM::M1, "FieldOfViewRotation" },
{ 0x300A, 0x0124, 0, VR::DS, VM::M1, "TableTopEccentricAxisDistance" },
{ 0x6002, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0491[] = {
{ 0x300A, 0x0125, 0, VR::DS, VM::M1, "TableTopEccentricAngle" },
{ 0x6002, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0492[] = {
{ 0x0018, 0x7034, 0, VR::CS, VM::M1, "FieldOfViewHorizontalFlip" },
{ 0x0040, 0xA731, 1, VR::SQ, VM::M1, "RelationshipSequenceTrial" },
{ 0x3008, 0x0120, 0, VR::SQ, VM::M1, "RecordedBrachyAccessoryDeviceSequence" },
{ 0x300A, 0x0122, 0, VR::DS, VM::M1, "PatientSupportAngle" },
{ 0x6004, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0493[] = {
{ 0x0040, 0xA730, 0, VR::SQ, VM::M1, "ContentSequence" },
{ 0x300A, 0x0123, 0, VR::CS, VM::M1, "PatientSupportRotationDirection" },
{ 0x6004, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0494[] = {
{ 0x0018, 0x7036, 0, VR::FL, VM::M2, "PixelDataAreaOriginRelativeToFOV" },
{ 0x3008, 0x0122, 0, VR::IS, VM::M1, "ReferencedBrachyAccessoryDeviceNumber" },
{ 0x300A, 0x0120, 0, VR::DS, VM::M1, "BeamLimitingDeviceAngle" },
{ 0x6006, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0495[] = {
{ 0x0040, 0xA732, 1, VR::SQ, VM::M1, "RelationshipTypeCodeSequenceTrial" },
{ 0x300A, 0x0121, 0, VR::CS, VM::M1, "BeamLimitingDeviceRotationDirection" },
{ 0x6006, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0496[] = {
{ 0x0018, 0x7028, 0, VR::DS, VM::M2, "DetectorActiveOrigin" },
{ 0x3008, 0x013C, 0, VR::DS, VM::M1, "DeliveredPulseRepetitionInterval" },
{ 0x6018, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0497[] = {
{ 0x6018, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0498[] = {
{ 0x0018, 0x702A, 0, VR::LO, VM::M1, "DetectorManufacturerName" },
{ 0x601A, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0499[] = {
{ 0x0018, 0x702B, 0, VR::LO, VM::M1, "DetectorManufacturerModelName" },
{ 0x601A, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0500[] = {
{ 0x3008, 0x0138, 0, VR::IS, VM::M1, "DeliveredNumberOfPulses" },
{ 0x4008, 0x00FF, 1, VR::CS, VM::M1, "ReportProductionStatusTrial" },
{ 0x601C, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0501[] = {
{ 0x0010, 0x2160, 0, VR::SH, VM::M1, "EthnicGroup" },
{ 0x2010, 0x0160, 0, VR::US, VM::M1, "ReflectedAmbientLight" },
{ 0x2100, 0x0070, 0, VR::AE, VM::M1, "Originator" },
{ 0x2120, 0x0050, 1, VR::SQ, VM::M1, "PrintJobDescriptionSequence" },
{ 0x2130, 0x0040, 1, VR::SQ, VM::M1, "ImageBoxContentSequence" },
{ 0x601C, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0502[] = {
{ 0x3008, 0x013A, 0, VR::DS, VM::M1, "SpecifiedPulseRepetitionInterval" },
{ 0x601E, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0503[] = {
{ 0x0028, 0x1199, 0, VR::UI, VM::M1, "PaletteColorLookupTableUID" },
{ 0x0040, 0xA33A, 1, VR::ST, VM::M1, "ReportStatusCommentTrial" },
{ 0x601E, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0504[] = {
{ 0x0018, 0x7020, 0, VR::DS, VM::M2, "DetectorElementPhysicalSize" },
{ 0x3008, 0x0134, 0, VR::DS, VM::M1, "DeliveredChannelTotalTime" },
{ 0x6010, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0505[] = {
{ 0x0018, 0x6060, 0, VR::FL, VM::M1TN, "RWaveTimeVector" },
{ 0x0068, 0x6400, 0, VR::SQ, VM::M1, "MatingFeatureDegreeOfFreedomSequence" },
{ 0x6010, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0506[] = {
{ 0x0018, 0x11A4, 0, VR::LO, VM::M1, "PaddleDescription" },
{ 0x0018, 0x7022, 0, VR::DS, VM::M2, "DetectorElementSpacing" },
{ 0x3008, 0x0136, 0, VR::IS, VM::M1, "SpecifiedNumberOfPulses" },
{ 0x300A, 0x0134, 0, VR::DS, VM::M1, "CumulativeMetersetWeight" },
{ 0x6012, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0507[] = {
{ 0x6012, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0508[] = {
{ 0x0018, 0x11A2, 0, VR::DS, VM::M1, "CompressionForce" },
{ 0x0018, 0x7024, 0, VR::CS, VM::M1, "DetectorActiveShape" },
{ 0x0028, 0x3110, 0, VR::SQ, VM::M1, "SoftcopyVOILUTSequence" },
{ 0x3008, 0x0130, 0, VR::SQ, VM::M1, "RecordedChannelSequence" },
{ 0x6014, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0509[] = {
{ 0x6014, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0510[] = {
{ 0x0018, 0x11A0, 0, VR::DS, VM::M1, "BodyPartThickness" },
{ 0x0018, 0x7026, 0, VR::DS, VM::M1T2, "DetectorActiveDimensions" },
{ 0x3008, 0x0132, 0, VR::DS, VM::M1, "SpecifiedChannelTotalTime" },
{ 0x300A, 0x0130, 0, VR::DS, VM::M1, "SourceToSurfaceDistance" },
{ 0x6016, 0x0069, 1, VR::US, VM::M1, "OverlayBitsGrouped12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0511[] = {
{ 0x6016, 0x0068, 1, VR::US, VM::M1, "OverlayRepeatInterval12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0512[] = {
{ 0x0008, 0x9459, 0, VR::FL, VM::M1, "RecommendedDisplayFrameRateInFloat" },
{ 0x0018, 0x1251, 0, VR::SH, VM::M1, "TransmitCoilName" },
{ 0x0018, 0x9059, 0, VR::CS, VM::M1, "Decoupling" },
{ 0x0018, 0x9449, 0, VR::FL, VM::M1, "BeamAngle" },
{ 0x0070, 0x0278, 0, VR::CS, VM::M1, "ShowTickLabel" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0513[] = {
{ 0x0008, 0x0201, 0, VR::SH, VM::M1, "TimezoneOffsetFromUTC" },
{ 0x0008, 0x9458, 0, VR::SQ, VM::M1, "FrameDisplaySequence" },
{ 0x0018, 0x1250, 0, VR::SH, VM::M1, "ReceiveCoilName" },
{ 0x0018, 0x9058, 0, VR::US, VM::M1, "MRAcquisitionFrequencyEncodingSteps" },
{ 0x0028, 0x9478, 0, VR::FL, VM::M1, "MaskVisibilityPercentage" },
{ 0x0070, 0x0279, 0, VR::CS, VM::M1, "TickLabelAlignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0514[] = {
{ 0x0010, 0x2298, 0, VR::CS, VM::M1, "ResponsiblePersonRole" },
{ 0x0028, 0x0A02, 0, VR::CS, VM::M1, "PixelSpacingCalibrationType" },
{ 0x003A, 0x0230, 0, VR::FL, VM::M1, "WaveformDataDisplayScale" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0515[] = {
{ 0x0010, 0x2299, 0, VR::LO, VM::M1, "ResponsibleOrganization" },
{ 0x003A, 0x0231, 0, VR::US, VM::M3, "WaveformDisplayBackgroundCIELabValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0516[] = {
{ 0x0028, 0x0A04, 0, VR::LO, VM::M1, "PixelSpacingCalibrationDescription" },
{ 0x4008, 0x0300, 1, VR::ST, VM::M1, "Impressions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0517[] = {
{ 0x0074, 0x1238, 0, VR::LT, VM::M1, "ReasonForCancellation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0518[] = {
{ 0x0046, 0x0248, 0, VR::CS, VM::M1, "CornealPointEstimated" },
{ 0x0068, 0x63E0, 0, VR::SQ, VM::M1, "MatingFeatureSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0519[] = {
{ 0x0046, 0x0249, 0, VR::FL, VM::M1, "AxialPower" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0520[] = {
{ 0x0010, 0x2292, 0, VR::LO, VM::M1, "PatientBreedDescription" },
{ 0x0018, 0x9051, 0, VR::CS, VM::M1, "TransmitCoilType" },
{ 0x0018, 0x9441, 0, VR::US, VM::M1, "RadiusOfCircularExposureControlSensingRegion" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0521[] = {
{ 0x0010, 0x2293, 0, VR::SQ, VM::M1, "PatientBreedCodeSequence" },
{ 0x0018, 0x9050, 0, VR::LO, VM::M1, "TransmitCoilManufacturerName" },
{ 0x0018, 0x9440, 0, VR::SS, VM::M2, "CenterOfCircularExposureControlSensingRegion" },
{ 0x0022, 0x1262, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthQualityMetricSequence" },
{ 0x0040, 0x0241, 0, VR::AE, VM::M1, "PerformedStationAETitle" },
{ 0x0046, 0x0247, 0, VR::FL, VM::M3, "CornealPointLocation" },
{ 0x0074, 0x1234, 0, VR::AE, VM::M1, "ReceivingAE" },
{ 0x300A, 0x02C8, 0, VR::DS, VM::M1, "FinalCumulativeTimeWeight" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0522[] = {
{ 0x0018, 0x9053, 0, VR::FD, VM::M1T2, "ChemicalShiftReference" },
{ 0x0040, 0x0242, 0, VR::SH, VM::M1, "PerformedStationName" },
{ 0x0046, 0x0244, 0, VR::SQ, VM::M1, "SourceImageCornealProcessedDataSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0523[] = {
{ 0x0018, 0x9052, 0, VR::FD, VM::M1T2, "SpectralWidth" },
{ 0x0018, 0x9442, 0, VR::SS, VM::M2TN, "VerticesOfThePolygonalExposureControlSensingRegion" },
{ 0x0022, 0x1260, 0, VR::SQ, VM::M1, "SelectedTotalOphthalmicAxialLengthSequence" },
{ 0x0040, 0x0243, 0, VR::SH, VM::M1, "PerformedLocation" },
{ 0x0070, 0x0273, 0, VR::FL, VM::M2, "RotationPoint" },
{ 0x0074, 0x1236, 0, VR::AE, VM::M1, "RequestingAE" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0524[] = {
{ 0x0010, 0x2296, 0, VR::SQ, VM::M1, "BreedRegistryCodeSequence" },
{ 0x0040, 0x0244, 0, VR::DA, VM::M1, "PerformedProcedureStepStartDate" },
{ 0x0046, 0x0242, 0, VR::CS, VM::M1, "CornealTopographyMapQualityEvaluation" },
{ 0x0070, 0x0274, 0, VR::CS, VM::M1, "TickAlignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0525[] = {
{ 0x0010, 0x2297, 0, VR::PN, VM::M1, "ResponsiblePerson" },
{ 0x0018, 0x9054, 0, VR::CS, VM::M1, "VolumeLocalizationTechnique" },
{ 0x0028, 0x9474, 0, VR::CS, VM::M1, "LUTFunction" },
{ 0x0040, 0x0245, 0, VR::TM, VM::M1, "PerformedProcedureStepStartTime" },
{ 0x0054, 0x1210, 0, VR::DS, VM::M1, "CoincidenceWindowWidth" },
{ 0x0074, 0x1230, 0, VR::LO, VM::M1, "DeletionLock" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0526[] = {
{ 0x0010, 0x2294, 0, VR::SQ, VM::M1, "BreedRegistrationSequence" },
{ 0x0018, 0x9447, 0, VR::FL, VM::M1, "ColumnAngulationPatient" },
{ 0x0022, 0x1265, 1, VR::SQ, VM::M1, "OphthalmicAxialLengthQualityMetricTypeCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0527[] = {
{ 0x0010, 0x2295, 0, VR::LO, VM::M1, "BreedRegistrationNumber" },
{ 0x7FE0, 0x0010, 0, VR::OX, VM::M1, "PixelData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0528[] = {
{ 0x0018, 0x9049, 0, VR::SQ, VM::M1, "MRTransmitCoilSequence" },
{ 0x0020, 0x9071, 0, VR::SQ, VM::M1, "FrameAnatomySequence" },
{ 0x003A, 0x0222, 0, VR::DS, VM::M1, "NotchFilterFrequency" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0529[] = {
{ 0x0008, 0x1250, 0, VR::SQ, VM::M1, "RelatedSeriesSequence" },
{ 0x0018, 0x1240, 1, VR::IS, VM::M1TN, "UpperLowerPixelValues" },
{ 0x0018, 0x9048, 0, VR::CS, VM::M1, "MultiCoilElementUsed" },
{ 0x003A, 0x0223, 0, VR::DS, VM::M1, "NotchFilterBandwidth" },
{ 0x300A, 0x02D0, 0, VR::SQ, VM::M1, "BrachyControlPointSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0530[] = {
{ 0x0018, 0x1243, 0, VR::IS, VM::M1, "CountRate" },
{ 0x003A, 0x0220, 0, VR::DS, VM::M1, "FilterLowFrequency" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0531[] = {
{ 0x0018, 0x1242, 0, VR::IS, VM::M1, "ActualFrameDuration" },
{ 0x0020, 0x9072, 0, VR::CS, VM::M1, "FrameLaterality" },
{ 0x003A, 0x0221, 0, VR::DS, VM::M1, "FilterHighFrequency" },
{ 0x300A, 0x02D2, 0, VR::DS, VM::M1, "ControlPointRelativePosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0533[] = {
{ 0x0018, 0x1244, 0, VR::US, VM::M1, "PreferredPlaybackSequencing" },
{ 0x300A, 0x02D4, 0, VR::DS, VM::M3, "ControlPoint3DPosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0534[] = {
{ 0x0068, 0x63F0, 0, VR::US, VM::M1, "MatingFeatureID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0535[] = {
{ 0x300A, 0x02D6, 0, VR::DS, VM::M1, "CumulativeTimeWeight" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0536[] = {
{ 0x0010, 0x0200, 0, VR::CS, VM::M1, "QualityControlSubject" },
{ 0x0018, 0x9041, 0, VR::LO, VM::M1, "ReceiveCoilManufacturerName" },
{ 0x0018, 0x9451, 0, VR::SQ, VM::M1, "FrameDetectorParametersSequence" },
{ 0x0022, 0x1273, 1, VR::LO, VM::M1, "OphthalmicAxialLengthQualityMetricTypeDescription" },
{ 0x0040, 0x0250, 0, VR::DA, VM::M1, "PerformedProcedureStepEndDate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0537[] = {
{ 0x0010, 0x0201, 0, VR::SQ, VM::M1, "QualityControlSubjectTypeCodeSequence" },
{ 0x0040, 0x0251, 0, VR::TM, VM::M1, "PerformedProcedureStepEndTime" },
{ 0x0070, 0x0261, 0, VR::FL, VM::M1, "GapLength" },
{ 0x0074, 0x1224, 0, VR::SQ, VM::M1, "ReplacedProcedureStepSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0538[] = {
{ 0x0018, 0x9043, 0, VR::CS, VM::M1, "ReceiveCoilType" },
{ 0x0040, 0x0252, 0, VR::CS, VM::M1, "PerformedProcedureStepStatus" },
{ 0x0070, 0x0262, 0, VR::FL, VM::M1, "DiameterOfVisibility" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0539[] = {
{ 0x0018, 0x9042, 0, VR::SQ, VM::M1, "MRReceiveCoilSequence" },
{ 0x0018, 0x9452, 0, VR::FL, VM::M1, "CalculatedAnatomyThickness" },
{ 0x0040, 0x0253, 0, VR::SH, VM::M1, "PerformedProcedureStepID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0540[] = {
{ 0x0018, 0x9045, 0, VR::SQ, VM::M1, "MultiCoilDefinitionSequence" },
{ 0x0018, 0x9455, 0, VR::SQ, VM::M1, "CalibrationSequence" },
{ 0x0040, 0x0254, 0, VR::LO, VM::M1, "PerformedProcedureStepDescription" },
{ 0x0046, 0x0252, 0, VR::FL, VM::M1, "RelativeElevation" },
{ 0x0054, 0x1201, 0, VR::IS, VM::M2, "AxialMash" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0541[] = {
{ 0x0018, 0x9044, 0, VR::CS, VM::M1, "QuadratureReceiveCoil" },
{ 0x0040, 0x0255, 0, VR::LO, VM::M1, "PerformedProcedureTypeDescription" },
{ 0x0046, 0x0253, 0, VR::FL, VM::M1, "CornealWavefront" },
{ 0x0054, 0x1200, 0, VR::DS, VM::M1, "AxialAcceptance" },
{ 0x0074, 0x1220, 1, VR::SQ, VM::M1, "RelatedProcedureStepSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0542[] = {
{ 0x0018, 0x9047, 0, VR::SH, VM::M1, "MultiCoilElementName" },
{ 0x0018, 0x9457, 0, VR::CS, VM::M1, "PlaneIdentification" },
{ 0x0046, 0x0250, 0, VR::FL, VM::M1, "TangentialPower" },
{ 0x0054, 0x1203, 0, VR::DS, VM::M2, "DetectorElementSize" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0543[] = {
{ 0x0018, 0x9046, 0, VR::LO, VM::M1, "MultiCoilConfiguration" },
{ 0x0018, 0x9456, 0, VR::SQ, VM::M1, "ObjectThicknessSequence" },
{ 0x0046, 0x0251, 0, VR::FL, VM::M1, "RefractivePower" },
{ 0x0054, 0x1202, 0, VR::IS, VM::M1, "TransverseMash" },
{ 0x0074, 0x1222, 1, VR::LO, VM::M1, "ProcedureStepRelationshipType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0544[] = {
{ 0x0018, 0x9079, 0, VR::FD, VM::M1TN, "InversionTimes" },
{ 0x0018, 0x9469, 0, VR::FL, VM::M1, "TableHorizontalRotationAngle" },
{ 0x0028, 0x0200, 1, VR::US, VM::M1, "ImageLocation" },
{ 0x003A, 0x0212, 0, VR::DS, VM::M1, "ChannelSensitivityCorrectionFactor" },
{ 0x0070, 0x0258, 0, VR::FL, VM::M1, "ShadowOpacity" },
{ 0x300A, 0x02E1, 0, VR::CS, VM::M1, "CompensatorMountingPosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0545[] = {
{ 0x0018, 0x9078, 0, VR::CS, VM::M1, "ParallelAcquisitionTechnique" },
{ 0x0018, 0x9468, 0, VR::FL, VM::M1, "TableZPositionToIsocenter" },
{ 0x0020, 0x9450, 0, VR::SQ, VM::M1, "PatientOrientationInFrameSequence" },
{ 0x003A, 0x0213, 0, VR::DS, VM::M1, "ChannelBaseline" },
{ 0x300A, 0x02E0, 0, VR::CS, VM::M1, "CompensatorDivergence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0546[] = {
{ 0x0020, 0x9453, 0, VR::LO, VM::M1, "FrameLabel" },
{ 0x003A, 0x0210, 0, VR::DS, VM::M1, "ChannelSensitivity" },
{ 0x300A, 0x02E3, 0, VR::FL, VM::M1, "TotalCompensatorTrayWaterEquivalentThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0547[] = {
{ 0x003A, 0x0211, 0, VR::SQ, VM::M1, "ChannelSensitivityUnitsSequence" },
{ 0x300A, 0x02E2, 0, VR::DS, VM::M1TN, "SourceToCompensatorDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0548[] = {
{ 0x300A, 0x02E5, 0, VR::FL, VM::M1, "CompensatorColumnOffset" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0549[] = {
{ 0x300A, 0x02E4, 0, VR::FL, VM::M1, "IsocenterToCompensatorTrayDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0550[] = {
{ 0x003A, 0x0214, 0, VR::DS, VM::M1, "ChannelTimeSkew" },
{ 0x0068, 0x63C0, 0, VR::US, VM::M1, "MatingFeatureSetID" },
{ 0x300A, 0x02E7, 0, VR::FL, VM::M1, "CompensatorRelativeStoppingPowerRatio" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0551[] = {
{ 0x003A, 0x0215, 0, VR::DS, VM::M1, "ChannelSampleSkew" },
{ 0x300A, 0x02E6, 0, VR::FL, VM::M1TN, "IsocenterToCompensatorDistances" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0552[] = {
{ 0x0018, 0x9461, 0, VR::FL, VM::M1T2, "FieldOfViewDimensionsInFloat" },
{ 0x0020, 0x0200, 0, VR::UI, VM::M1, "SynchronizationFrameOfReferenceUID" },
{ 0x003A, 0x021A, 0, VR::US, VM::M1, "WaveformBitsStored" },
{ 0x0040, 0x0260, 0, VR::SQ, VM::M1, "PerformedProtocolCodeSequence" },
{ 0x0070, 0x0250, 0, VR::CS, VM::M1, "Italic" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0553[] = {
{ 0x0018, 0x9070, 0, VR::FD, VM::M1, "CardiacRRIntervalSpecified" },
{ 0x0040, 0x0261, 0, VR::CS, VM::M1, "PerformedProtocolType" },
{ 0x0070, 0x0251, 0, VR::US, VM::M3, "PatternOnColorCIELabValue" },
{ 0x300A, 0x02E8, 0, VR::FL, VM::M1, "CompensatorMillingToolDiameter" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0554[] = {
{ 0x0018, 0x9073, 0, VR::FD, VM::M1, "AcquisitionDuration" },
{ 0x0018, 0x9463, 0, VR::FL, VM::M1, "PositionerIsocenterPrimaryAngle" },
{ 0x003A, 0x0218, 0, VR::DS, VM::M1, "ChannelOffset" },
{ 0x0070, 0x0252, 0, VR::US, VM::M3, "PatternOffColorCIELabValue" },
{ 0x300A, 0x02EB, 0, VR::LT, VM::M1, "CompensatorDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0555[] = {
{ 0x0018, 0x9462, 0, VR::SQ, VM::M1, "IsocenterReferenceSystemSequence" },
{ 0x0070, 0x0253, 0, VR::FL, VM::M1, "LineThickness" },
{ 0x0074, 0x1216, 0, VR::SQ, VM::M1, "UnifiedProcedureStepPerformedProcedureSequence" },
{ 0x300A, 0x02EA, 0, VR::SQ, VM::M1, "IonRangeCompensatorSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0556[] = {
{ 0x0018, 0x9075, 0, VR::CS, VM::M1, "DiffusionDirectionality" },
{ 0x0018, 0x9465, 0, VR::FL, VM::M1, "PositionerIsocenterDetectorRotationAngle" },
{ 0x0070, 0x0254, 0, VR::CS, VM::M1, "LineDashingStyle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0557[] = {
{ 0x0018, 0x9074, 0, VR::DT, VM::M1, "FrameAcquisitionDateTime" },
{ 0x0018, 0x9464, 0, VR::FL, VM::M1, "PositionerIsocenterSecondaryAngle" },
{ 0x0028, 0x9454, 0, VR::CS, VM::M1, "MaskSelectionMode" },
{ 0x0070, 0x0255, 0, VR::UL, VM::M1, "LinePattern" },
{ 0x0074, 0x1210, 0, VR::SQ, VM::M1, "ScheduledProcessingParametersSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0558[] = {
{ 0x0018, 0x9077, 0, VR::CS, VM::M1, "ParallelAcquisition" },
{ 0x0018, 0x9467, 0, VR::FL, VM::M1, "TableYPositionToIsocenter" },
{ 0x0024, 0x0202, 0, VR::LO, VM::M1, "AlgorithmSource" },
{ 0x0070, 0x0256, 0, VR::OB, VM::M1, "FillPattern" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0559[] = {
{ 0x0018, 0x9076, 0, VR::SQ, VM::M1, "DiffusionGradientDirectionSequence" },
{ 0x0018, 0x9466, 0, VR::FL, VM::M1, "TableXPositionToIsocenter" },
{ 0x0070, 0x0257, 0, VR::CS, VM::M1, "FillMode" },
{ 0x0074, 0x1212, 0, VR::SQ, VM::M1, "PerformedProcessingParametersSequence" },
{ 0x7FE0, 0x0030, 1, VR::OW, VM::M1, "CoefficientsSDHN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0560[] = {
{ 0x0018, 0x1261, 0, VR::LO, VM::M1, "PhosphorType" },
{ 0x0018, 0x9069, 0, VR::FD, VM::M1, "ParallelReductionFactorInPlane" },
{ 0x003A, 0x0202, 0, VR::IS, VM::M1, "WaveformChannelNumber" },
{ 0x0070, 0x0248, 0, VR::CS, VM::M1, "Underlined" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0561[] = {
{ 0x0018, 0x1260, 0, VR::SH, VM::M1, "PlateType" },
{ 0x003A, 0x0203, 0, VR::SH, VM::M1, "ChannelLabel" },
{ 0x0070, 0x0249, 0, VR::CS, VM::M1, "Bold" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0562[] = {
{ 0x003A, 0x0200, 0, VR::SQ, VM::M1, "ChannelDefinitionSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0566[] = {
{ 0x0020, 0x9057, 0, VR::UL, VM::M1, "InStackPositionNumber" },
{ 0x0068, 0x63D0, 0, VR::LO, VM::M1, "MatingFeatureSetLabel" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0567[] = {
{ 0x0020, 0x9056, 0, VR::SH, VM::M1, "StackID" },
{ 0x0028, 0x7FE0, 0, VR::UT, VM::M1, "PixelDataProviderURL" },
{ 0x003A, 0x0205, 0, VR::CS, VM::M1TN, "ChannelStatus" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0568[] = {
{ 0x0018, 0x9061, 0, VR::FD, VM::M1T2, "DecouplingFrequency" },
{ 0x0018, 0x9471, 0, VR::FL, VM::M1, "TableCradleTiltAngle" },
{ 0x003A, 0x020A, 0, VR::SQ, VM::M1, "SourceWaveformSequence" },
{ 0x0040, 0x0270, 0, VR::SQ, VM::M1, "ScheduledStepAttributesSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0569[] = {
{ 0x0008, 0x9460, 0, VR::CS, VM::M1, "SkipFrameRangeFlag" },
{ 0x0018, 0x9060, 0, VR::CS, VM::M1T2, "DecoupledNucleus" },
{ 0x0018, 0x9470, 0, VR::FL, VM::M1, "TableHeadTiltAngle" },
{ 0x0070, 0x0241, 0, VR::US, VM::M3, "TextColorCIELabValue" },
{ 0x0074, 0x1204, 0, VR::LO, VM::M1, "ProcedureStepLabel" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0570[] = {
{ 0x0018, 0x9063, 0, VR::FD, VM::M1T2, "DecouplingChemicalShiftReference" },
{ 0x0018, 0x9473, 0, VR::FL, VM::M1, "AcquiredImageAreaDoseProduct" },
{ 0x0028, 0x9443, 0, VR::SQ, VM::M1, "FramePixelDataPropertiesSequence" },
{ 0x003A, 0x0208, 0, VR::SQ, VM::M1, "ChannelSourceSequence" },
{ 0x0070, 0x0242, 0, VR::CS, VM::M1, "HorizontalAlignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0571[] = {
{ 0x0018, 0x9062, 0, VR::CS, VM::M1, "DecouplingMethod" },
{ 0x0018, 0x9472, 0, VR::SQ, VM::M1, "FrameDisplayShutterSequence" },
{ 0x0022, 0x1250, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthSelectionMethodCodeSequence" },
{ 0x003A, 0x0209, 0, VR::SQ, VM::M1, "ChannelSourceModifiersSequence" },
{ 0x0070, 0x0243, 0, VR::CS, VM::M1, "VerticalAlignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0572[] = {
{ 0x0018, 0x9065, 0, VR::CS, VM::M1T2, "TimeDomainFiltering" },
{ 0x0022, 0x1257, 0, VR::SQ, VM::M1, "SelectedSegmentalOphthalmicAxialLengthSequence" },
{ 0x0028, 0x9445, 0, VR::FL, VM::M1, "GeometricMaximumDistortion" },
{ 0x0070, 0x0244, 0, VR::CS, VM::M1, "ShadowStyle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0573[] = {
{ 0x0018, 0x9064, 0, VR::CS, VM::M1, "KSpaceFiltering" },
{ 0x0018, 0x9474, 0, VR::CS, VM::M1, "CArmPositionerTabletopRelationship" },
{ 0x0028, 0x9444, 0, VR::CS, VM::M1, "GeometricalProperties" },
{ 0x0040, 0x0275, 0, VR::SQ, VM::M1, "RequestAttributesSequence" },
{ 0x0054, 0x1220, 0, VR::CS, VM::M1TN, "SecondaryCountsType" },
{ 0x0070, 0x0245, 0, VR::FL, VM::M1, "ShadowOffsetX" },
{ 0x0074, 0x1200, 0, VR::CS, VM::M1, "ScheduledProcedureStepPriority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0574[] = {
{ 0x0018, 0x9067, 0, VR::CS, VM::M1, "BaselineCorrection" },
{ 0x0018, 0x9477, 0, VR::SQ, VM::M1, "IrradiationEventIdentificationSequence" },
{ 0x0022, 0x1255, 0, VR::SQ, VM::M1, "OpticalSelectedOphthalmicAxialLengthSequence" },
{ 0x003A, 0x020C, 0, VR::LO, VM::M1, "ChannelDerivationDescription" },
{ 0x0070, 0x0246, 0, VR::FL, VM::M1, "ShadowOffsetY" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0575[] = {
{ 0x0018, 0x9066, 0, VR::US, VM::M1T2, "NumberOfZeroFills" },
{ 0x0018, 0x9476, 0, VR::SQ, VM::M1, "XRayGeometrySequence" },
{ 0x0028, 0x9446, 0, VR::CS, VM::M1TN, "ImageProcessingApplied" },
{ 0x0070, 0x0247, 0, VR::US, VM::M3, "ShadowColorCIELabValue" },
{ 0x0074, 0x1202, 0, VR::LO, VM::M1, "WorklistLabel" },
{ 0x7FE0, 0x0020, 1, VR::OW, VM::M1, "CoefficientsSDVN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0576[] = {
{ 0x0008, 0x1200, 0, VR::SQ, VM::M1, "StudiesContainingOtherReferencedInstancesSequence" },
{ 0x0018, 0x1210, 0, VR::SH, VM::M1TN, "ConvolutionKernel" },
{ 0x0018, 0x1600, 0, VR::CS, VM::M1T3, "ShutterShape" },
{ 0x0018, 0x9018, 0, VR::CS, VM::M1, "EchoPlanarPulseSequence" },
{ 0x0040, 0xA493, 0, VR::CS, VM::M1, "VerificationFlag" },
{ 0x0048, 0x0201, 0, VR::US, VM::M2, "TopLeftHandCornerOfLocalizerArea" },
{ 0x300A, 0x0280, 0, VR::SQ, VM::M1, "ChannelSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0577[] = {
{ 0x0018, 0x9019, 0, VR::FD, VM::M1, "TagAngleFirstAxis" },
{ 0x0028, 0x1221, 0, VR::OW, VM::M1, "SegmentedRedPaletteColorLookupTableData" },
{ 0x0040, 0xA082, 0, VR::DT, VM::M1, "ParticipationDateTime" },
{ 0x0040, 0xA492, 0, VR::LO, VM::M1, "CompletionFlagDescription" },
{ 0x0048, 0x0200, 0, VR::SQ, VM::M1, "ReferencedImageNavigationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0578[] = {
{ 0x0018, 0x1602, 0, VR::IS, VM::M1, "ShutterLeftVerticalEdge" },
{ 0x0028, 0x1222, 0, VR::OW, VM::M1, "SegmentedGreenPaletteColorLookupTableData" },
{ 0x0040, 0xA491, 0, VR::CS, VM::M1, "CompletionFlag" },
{ 0x300A, 0x0282, 0, VR::IS, VM::M1, "ChannelNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0579[] = {
{ 0x0028, 0x1223, 0, VR::OW, VM::M1, "SegmentedBluePaletteColorLookupTableData" },
{ 0x0040, 0xA080, 0, VR::CS, VM::M1, "ParticipationType" },
{ 0x0048, 0x0202, 0, VR::US, VM::M2, "BottomRightHandCornerOfLocalizerArea" },
{ 0x0068, 0x63A4, 0, VR::SQ, VM::M1, "CoatingMaterialsCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0580[] = {
{ 0x0018, 0x1604, 0, VR::IS, VM::M1, "ShutterRightVerticalEdge" },
{ 0x300A, 0x0284, 0, VR::DS, VM::M1, "ChannelLength" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0581[] = {
{ 0x0040, 0xA496, 0, VR::CS, VM::M1, "PreliminaryFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0582[] = {
{ 0x0018, 0x1606, 0, VR::IS, VM::M1, "ShutterUpperHorizontalEdge" },
{ 0x0040, 0xA085, 1, VR::SQ, VM::M1, "ProcedureIdentifierCodeSequenceTrial" },
{ 0x0048, 0x0207, 0, VR::SQ, VM::M1, "OpticalPathIdentificationSequence" },
{ 0x300A, 0x0286, 0, VR::DS, VM::M1, "ChannelTotalTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0583[] = {
{ 0x0040, 0xA084, 0, VR::CS, VM::M1, "ObserverType" },
{ 0x0040, 0xA494, 0, VR::CS, VM::M1, "ArchiveRequested" },
{ 0x0046, 0x0208, 0, VR::IS, VM::M2T2N, "VerticesOfTheOutlineOfPupil" },
{ 0x0068, 0x63A0, 0, VR::SQ, VM::M1, "MaterialsCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0584[] = {
{ 0x0008, 0x9410, 0, VR::SQ, VM::M1, "ReferencedOtherPlaneSequence" },
{ 0x0018, 0x1608, 0, VR::IS, VM::M1, "ShutterLowerHorizontalEdge" },
{ 0x0018, 0x9010, 0, VR::CS, VM::M1, "FlowCompensation" },
{ 0x0046, 0x0207, 0, VR::SQ, VM::M1, "CornealTopographyMapTypeCodeSequence" },
{ 0x0070, 0x0231, 0, VR::SQ, VM::M1, "TextStyleSequence" },
{ 0x300A, 0x0288, 0, VR::CS, VM::M1, "SourceMovementType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0585[] = {
{ 0x0018, 0x9011, 0, VR::CS, VM::M1, "MultipleSpinEcho" },
{ 0x0018, 0x9401, 0, VR::SQ, VM::M1, "ProjectionPixelCalibrationSequence" },
{ 0x0040, 0x0610, 0, VR::SQ, VM::M1, "SpecimenPreparationSequence" },
{ 0x0070, 0x0230, 0, VR::FD, VM::M1, "RotationAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0586[] = {
{ 0x0018, 0x9012, 0, VR::CS, VM::M1, "MultiPlanarExcitation" },
{ 0x0018, 0x9402, 0, VR::FL, VM::M1, "DistanceSourceToIsocenter" },
{ 0x0022, 0x1220, 0, VR::SQ, VM::M1, "UltrasoundOphthalmicAxialLengthMeasurementsSequence" },
{ 0x0040, 0xA089, 1, VR::OB, VM::M1, "ObjectDirectoryBinaryIdentifierTrial" },
{ 0x0046, 0x0205, 0, VR::FL, VM::M1, "EquivalentPupilRadius" },
{ 0x0070, 0x0233, 0, VR::SQ, VM::M1, "FillStyleSequence" },
{ 0x300A, 0x028A, 0, VR::IS, VM::M1, "NumberOfPulses" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0587[] = {
{ 0x0018, 0x9403, 0, VR::FL, VM::M1, "DistanceObjectToTableTop" },
{ 0x0040, 0x0612, 0, VR::SQ, VM::M1, "SpecimenPreparationStepContentItemSequence" },
{ 0x0040, 0xA088, 0, VR::SQ, VM::M1, "VerifyingObserverIdentificationCodeSequence" },
{ 0x0046, 0x0204, 0, VR::FL, VM::M1, "PupilCentroidYCoordinate" },
{ 0x0068, 0x63AC, 0, VR::SQ, VM::M1, "FixationMethodCodeSequence" },
{ 0x0070, 0x0232, 0, VR::SQ, VM::M1, "LineStyleSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0588[] = {
{ 0x0004, 0x1200, 0, VR::UL, VM::M1, "OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity" },
{ 0x0018, 0x9014, 0, VR::CS, VM::M1, "PhaseContrast" },
{ 0x0018, 0x9404, 0, VR::FL, VM::M2, "ObjectPixelSpacingInCenterOfBeam" },
{ 0x0046, 0x0203, 0, VR::FL, VM::M1, "PupilCentroidXCoordinate" },
{ 0x0054, 0x0211, 0, VR::US, VM::M1, "NumberOfTriggersInPhase" },
{ 0x300A, 0x028C, 0, VR::DS, VM::M1, "PulseRepetitionInterval" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0589[] = {
{ 0x0018, 0x9015, 0, VR::CS, VM::M1, "TimeOfFlightContrast" },
{ 0x0018, 0x9405, 0, VR::SQ, VM::M1, "PositionerPositionSequence" },
{ 0x0046, 0x0202, 0, VR::FL, VM::M2, "CornealVertexLocation" },
{ 0x0054, 0x0210, 0, VR::IS, VM::M1TN, "TriggerVector" },
{ 0x0070, 0x0234, 0, VR::SQ, VM::M1, "GraphicGroupSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0590[] = {
{ 0x0004, 0x1202, 0, VR::UL, VM::M1, "OffsetOfTheLastDirectoryRecordOfTheRootDirectoryEntity" },
{ 0x0018, 0x9016, 0, VR::CS, VM::M1, "Spoiling" },
{ 0x0018, 0x9406, 0, VR::SQ, VM::M1, "TablePositionSequence" },
{ 0x0046, 0x0201, 0, VR::CS, VM::M1, "CornealTopographySurface" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0591[] = {
{ 0x0008, 0x9007, 0, VR::CS, VM::M4, "FrameType" },
{ 0x0018, 0x9017, 0, VR::CS, VM::M1, "SteadyStatePulseSequence" },
{ 0x0018, 0x9407, 0, VR::SQ, VM::M1, "CollimatorShapeSequence" },
{ 0x0022, 0x1225, 0, VR::SQ, VM::M1, "OpticalOphthalmicAxialLengthMeasurementsSequence" },
{ 0x0068, 0x63A8, 0, VR::SQ, VM::M1, "ImplantTypeCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0592[] = {
{ 0x0018, 0x1200, 0, VR::DA, VM::M1TN, "DateOfLastCalibration" },
{ 0x0018, 0x1610, 0, VR::IS, VM::M2, "CenterOfCircularShutter" },
{ 0x0018, 0x9008, 0, VR::CS, VM::M1, "EchoPulseSequence" },
{ 0x0070, 0x0229, 0, VR::LO, VM::M1, "CSSFontName" },
{ 0x300A, 0x0290, 0, VR::IS, VM::M1, "SourceApplicatorNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0593[] = {
{ 0x0018, 0x1201, 0, VR::TM, VM::M1TN, "TimeOfLastCalibration" },
{ 0x0018, 0x9009, 0, VR::CS, VM::M1, "InversionRecovery" },
{ 0x0020, 0x9421, 0, VR::LO, VM::M1, "DimensionDescriptionLabel" },
{ 0x0070, 0x0228, 0, VR::CS, VM::M1, "FontNameType" },
{ 0x300A, 0x0291, 0, VR::SH, VM::M1, "SourceApplicatorID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0594[] = {
{ 0x0018, 0x1612, 0, VR::IS, VM::M1, "RadiusOfCircularShutter" },
{ 0x300A, 0x0292, 0, VR::CS, VM::M1, "SourceApplicatorType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0595[] = {
{ 0x0040, 0xA090, 1, VR::SQ, VM::M1, "EquivalentCDADocumentSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0596[] = {
{ 0x300A, 0x0294, 0, VR::LO, VM::M1, "SourceApplicatorName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0598[] = {
{ 0x300A, 0x0296, 0, VR::DS, VM::M1, "SourceApplicatorLength" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0599[] = {
{ 0x0046, 0x0218, 0, VR::SQ, VM::M1, "SimulatedKeratometricCylinderSequence" },
{ 0x0068, 0x63B0, 0, VR::SQ, VM::M1, "MatingFeatureSetsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0600[] = {
{ 0x0018, 0x9410, 0, VR::CS, VM::M1, "PlanesInAcquisition" },
{ 0x300A, 0x0298, 0, VR::LO, VM::M1, "SourceApplicatorManufacturer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0601[] = {
{ 0x0040, 0x0600, 0, VR::LO, VM::M1, "SpecimenShortDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0602[] = {
{ 0x0018, 0x9412, 0, VR::SQ, VM::M1, "XAXRFFrameCharacteristicsSequence" },
{ 0x0022, 0x1230, 0, VR::SQ, VM::M1, "UltrasoundSelectedOphthalmicAxialLengthSequence" },
{ 0x0028, 0x9422, 0, VR::SQ, VM::M1, "PixelIntensityRelationshipLUTSequence" },
{ 0x0046, 0x0215, 0, VR::SQ, VM::M1, "MinimumKeratometricSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0603[] = {
{ 0x0040, 0x0602, 0, VR::UT, VM::M1, "SpecimenDetailedDescription" },
{ 0x0048, 0x021A, 0, VR::SQ, VM::M1, "PlanePositionSlideSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0604[] = {
{ 0x0004, 0x1600, 1, VR::UL, VM::M1, "NumberOfReferences" },
{ 0x0018, 0x9004, 0, VR::CS, VM::M1, "ContentQualification" },
{ 0x0046, 0x0213, 0, VR::FL, VM::M2, "MaximumCornealCurvatureLocation" },
{ 0x300A, 0x029C, 0, VR::DS, VM::M1, "SourceApplicatorWallNominalThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0605[] = {
{ 0x0018, 0x9005, 0, VR::SH, VM::M1, "PulseSequenceName" },
{ 0x0046, 0x0212, 0, VR::FL, VM::M1, "MaximumCornealCurvature" },
{ 0x0054, 0x0200, 0, VR::DS, VM::M1, "StartAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0606[] = {
{ 0x0004, 0x1212, 0, VR::US, VM::M1, "FileSetConsistencyFlag" },
{ 0x0018, 0x9006, 0, VR::SQ, VM::M1, "MRImagingModifierSequence" },
{ 0x0046, 0x0211, 0, VR::SQ, VM::M1, "MaximumCornealCurvatureSequence" },
{ 0x0048, 0x021F, 0, VR::SL, VM::M1, "RowPositionInTotalImagePixelMatrix" },
{ 0x0070, 0x0227, 0, VR::LO, VM::M1, "FontName" },
{ 0x300A, 0x029E, 0, VR::DS, VM::M1, "SourceApplicatorWallNominalTransmission" },
{ 0x7FE0, 0x0040, 1, VR::OW, VM::M1, "CoefficientsSDDN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0607[] = {
{ 0x0018, 0x9417, 0, VR::SQ, VM::M1, "FrameAcquisitionSequence" },
{ 0x0046, 0x0210, 0, VR::SQ, VM::M1, "CornealTopographyMappingNormalsSequence" },
{ 0x0048, 0x021E, 0, VR::SL, VM::M1, "ColumnPositionInTotalImagePixelMatrix" },
{ 0x0054, 0x0202, 0, VR::CS, VM::M1, "TypeOfDetectorMotion" },
{ 0x0070, 0x0226, 0, VR::UL, VM::M1, "CompoundGraphicInstanceID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0608[] = {
{ 0x0018, 0x1620, 0, VR::IS, VM::M2T2N, "VerticesOfThePolygonalShutter" },
{ 0x0018, 0x9428, 0, VR::FL, VM::M1T2, "IntensifierActiveDimensions" },
{ 0x0020, 0x1208, 0, VR::IS, VM::M1, "NumberOfStudyRelatedInstances" },
{ 0x0028, 0x1200, 1, VR::OW, VM::M1, "GrayLookupTableData" },
{ 0x300A, 0x02A0, 0, VR::DS, VM::M1, "SourceApplicatorStepSize" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0609[] = {
{ 0x0018, 0x9429, 0, VR::FL, VM::M2, "PhysicalDetectorSize" },
{ 0x0020, 0x1209, 0, VR::IS, VM::M1, "NumberOfSeriesRelatedInstances" },
{ 0x0028, 0x1201, 0, VR::OW, VM::M1, "RedPaletteColorLookupTableData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0610[] = {
{ 0x0018, 0x1622, 0, VR::US, VM::M1, "ShutterPresentationValue" },
{ 0x0028, 0x1202, 0, VR::OW, VM::M1, "GreenPaletteColorLookupTableData" },
{ 0x300A, 0x02A2, 0, VR::IS, VM::M1, "TransferTubeNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0611[] = {
{ 0x0018, 0x1623, 0, VR::US, VM::M1, "ShutterOverlayGroup" },
{ 0x0028, 0x1203, 0, VR::OW, VM::M1, "BluePaletteColorLookupTableData" },
{ 0x0072, 0x0218, 0, VR::US, VM::M1TN, "ReferenceDisplaySets" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0612[] = {
{ 0x0018, 0x1624, 0, VR::US, VM::M3, "ShutterPresentationColorCIELabValue" },
{ 0x0028, 0x1204, 0, VR::OW, VM::M1, "AlphaPaletteColorLookupTableData" },
{ 0x300A, 0x02A4, 0, VR::DS, VM::M1, "TransferTubeLength" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0615[] = {
{ 0x0068, 0x6380, 0, VR::LO, VM::M1, "SurfaceModelLabel" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0616[] = {
{ 0x0018, 0x9030, 0, VR::FD, VM::M1, "TagSpacingFirstDimension" },
{ 0x0018, 0x9420, 0, VR::CS, VM::M1, "XRayReceptorType" },
{ 0x0018, 0x9810, 0, VR::XS, VM::M1, "ZeroVelocityPixelValue" },
{ 0x0020, 0x1200, 0, VR::IS, VM::M1, "NumberOfPatientRelatedStudies" },
{ 0x0046, 0x0227, 0, VR::FL, VM::M1, "AnalyzedArea" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0617[] = {
{ 0x0028, 0x9001, 0, VR::UL, VM::M1, "DataPointRows" },
{ 0x0028, 0x9411, 0, VR::FL, VM::M1, "DisplayFilterPercentage" },
{ 0x0040, 0x0220, 0, VR::SQ, VM::M1, "ReferencedNonImageCompositeSOPInstanceSequence" },
{ 0x0072, 0x0212, 0, VR::US, VM::M2TN, "DisplaySetScrollingGroup" },
{ 0x0072, 0x0602, 0, VR::CS, VM::M1, "SortByCategory" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0618[] = {
{ 0x0018, 0x9032, 0, VR::CS, VM::M1, "GeometryOfKSpaceTraversal" },
{ 0x0020, 0x1202, 0, VR::IS, VM::M1, "NumberOfPatientRelatedSeries" },
{ 0x0028, 0x9002, 0, VR::UL, VM::M1, "DataPointColumns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0619[] = {
{ 0x0018, 0x9033, 0, VR::CS, VM::M1, "SegmentedKSpaceTraversal" },
{ 0x0018, 0x9423, 0, VR::LO, VM::M1, "AcquisitionProtocolName" },
{ 0x0020, 0x0242, 0, VR::UI, VM::M1, "SOPInstanceUIDOfConcatenationSource" },
{ 0x0028, 0x9003, 0, VR::CS, VM::M1, "SignalDomainColumns" },
{ 0x0046, 0x0224, 0, VR::FL, VM::M1, "CornealISValue" },
{ 0x0072, 0x0210, 0, VR::SQ, VM::M1, "SynchronizedScrollingSequence" },
{ 0x0072, 0x0600, 0, VR::SQ, VM::M1, "SortingOperationsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0620[] = {
{ 0x0004, 0x1220, 0, VR::SQ, VM::M1, "DirectoryRecordSequence" },
{ 0x0018, 0x9034, 0, VR::CS, VM::M1, "RectilinearPhaseEncodeReordering" },
{ 0x0018, 0x9424, 0, VR::LT, VM::M1, "AcquisitionProtocolDescription" },
{ 0x0020, 0x1204, 0, VR::IS, VM::M1, "NumberOfPatientRelatedInstances" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0621[] = {
{ 0x0018, 0x9035, 0, VR::FD, VM::M1, "TagThickness" },
{ 0x0018, 0x9425, 0, VR::CS, VM::M1, "ContrastBolusIngredientOpaque" },
{ 0x0028, 0x9415, 0, VR::SQ, VM::M1, "FramePixelShiftSequence" },
{ 0x0072, 0x0216, 0, VR::US, VM::M1, "NavigationDisplaySet" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0622[] = {
{ 0x0018, 0x9036, 0, VR::CS, VM::M1, "PartialFourierDirection" },
{ 0x0018, 0x9426, 0, VR::FL, VM::M1, "DistanceReceptorPlaneToDetectorHousing" },
{ 0x0020, 0x1206, 0, VR::IS, VM::M1, "NumberOfStudyRelatedSeries" },
{ 0x0028, 0x9416, 0, VR::US, VM::M1, "SubtractionItemID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0623[] = {
{ 0x0018, 0x9037, 0, VR::CS, VM::M1, "CardiacSynchronizationTechnique" },
{ 0x0018, 0x9427, 0, VR::CS, VM::M1, "IntensifierActiveShape" },
{ 0x0046, 0x0220, 0, VR::FL, VM::M1, "AverageCornealPower" },
{ 0x0072, 0x0214, 0, VR::SQ, VM::M1, "NavigationIndicatorSequence" },
{ 0x0072, 0x0604, 0, VR::CS, VM::M1, "SortingDirection" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0624[] = {
{ 0x0018, 0x9028, 0, VR::CS, VM::M1, "Tagging" },
{ 0x0018, 0x9438, 0, VR::SS, VM::M1, "ExposureControlSensingRegionUpperHorizontalEdge" },
{ 0x0018, 0x9808, 0, VR::CS, VM::M1, "DataType" },
{ 0x0070, 0x0209, 0, VR::SQ, VM::M1, "CompoundGraphicSequence" },
{ 0x300A, 0x02B0, 0, VR::SQ, VM::M1, "ChannelShieldSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0625[] = {
{ 0x0010, 0x9431, 0, VR::FL, VM::M1, "ExaminedBodyThickness" },
{ 0x0018, 0x9029, 0, VR::CS, VM::M1, "OversamplingPhase" },
{ 0x0018, 0x9439, 0, VR::SS, VM::M1, "ExposureControlSensingRegionLowerHorizontalEdge" },
{ 0x0018, 0x9809, 0, VR::SQ, VM::M1, "TransducerScanPatternCodeSequence" },
{ 0x0028, 0x1211, 1, VR::OW, VM::M1, "LargeRedPaletteColorLookupTableData" },
{ 0x003A, 0x0242, 0, VR::SQ, VM::M1, "ChannelDisplaySequence" },
{ 0x0070, 0x0208, 0, VR::ST, VM::M1, "GraphicGroupDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0626[] = {
{ 0x0028, 0x1212, 1, VR::OW, VM::M1, "LargeGreenPaletteColorLookupTableData" },
{ 0x003A, 0x0241, 0, VR::US, VM::M1, "PresentationGroupNumber" },
{ 0x300A, 0x02B2, 0, VR::IS, VM::M1, "ChannelShieldNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0627[] = {
{ 0x0018, 0x980B, 0, VR::CS, VM::M1, "AliasedDataType" },
{ 0x0028, 0x1213, 1, VR::OW, VM::M1, "LargeBluePaletteColorLookupTableData" },
{ 0x003A, 0x0240, 0, VR::SQ, VM::M1, "WaveformPresentationGroupSequence" },
{ 0x0040, 0xA0B0, 0, VR::US, VM::M2T2N, "ReferencedWaveformChannels" },
{ 0x0072, 0x0208, 0, VR::CS, VM::M1, "PartialDataDisplayHandling" },
{ 0x300A, 0x02B3, 0, VR::SH, VM::M1, "ChannelShieldID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0628[] = {
{ 0x0018, 0x980C, 0, VR::CS, VM::M1, "PositionMeasuringDeviceUsed" },
{ 0x0028, 0x1214, 1, VR::UI, VM::M1, "LargePaletteColorLookupTableUID" },
{ 0x003A, 0x0247, 0, VR::FL, VM::M1, "FractionalChannelDisplayScale" },
{ 0x300A, 0x02B4, 0, VR::LO, VM::M1, "ChannelShieldName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0629[] = {
{ 0x0018, 0x980D, 0, VR::SQ, VM::M1, "TransducerGeometryCodeSequence" },
{ 0x003A, 0x0246, 0, VR::CS, VM::M1, "DisplayShadingFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0630[] = {
{ 0x0018, 0x980E, 0, VR::SQ, VM::M1, "TransducerBeamSteeringCodeSequence" },
{ 0x003A, 0x0245, 0, VR::FL, VM::M1, "ChannelPosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0631[] = {
{ 0x0018, 0x980F, 0, VR::SQ, VM::M1, "TransducerApplicationCodeSequence" },
{ 0x003A, 0x0244, 0, VR::US, VM::M3, "ChannelRecommendedDisplayCIELabValue" },
{ 0x0046, 0x0238, 0, VR::FL, VM::M1, "DecimalPotentialVisualAcuity" },
{ 0x0068, 0x6390, 0, VR::FD, VM::M1, "SurfaceModelScalingFactor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0632[] = {
{ 0x0018, 0x9020, 0, VR::CS, VM::M1, "MagnetizationTransfer" },
{ 0x0018, 0x9430, 0, VR::FL, VM::M2, "PositionOfIsocenterProjection" },
{ 0x0022, 0x1212, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthMeasurementsLengthSummationSequence" },
{ 0x0072, 0x0203, 0, VR::LO, VM::M1, "DisplaySetLabel" },
{ 0x0074, 0x1244, 0, VR::CS, VM::M1, "SubscriptionListStatus" },
{ 0x300A, 0x02B8, 0, VR::DS, VM::M1, "ChannelShieldNominalThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0633[] = {
{ 0x0018, 0x9021, 0, VR::CS, VM::M1, "T2Preparation" },
{ 0x0018, 0x9801, 0, VR::FD, VM::M1TN, "DepthsOfFocus" },
{ 0x0040, 0x0620, 0, VR::SQ, VM::M1, "SpecimenLocalizationContentItemSequence" },
{ 0x0046, 0x0236, 0, VR::FL, VM::M1, "KeratoconusPredictionIndex" },
{ 0x0072, 0x0202, 0, VR::US, VM::M1, "DisplaySetNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0634[] = {
{ 0x0018, 0x9022, 0, VR::CS, VM::M1, "BloodSignalNulling" },
{ 0x0018, 0x9432, 0, VR::SQ, VM::M1, "FieldOfViewSequence" },
{ 0x0022, 0x1210, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthMeasurementsTotalLengthSequence" },
{ 0x0074, 0x1246, 0, VR::CS, VM::M1, "UnifiedProcedureStepListStatus" },
{ 0x300A, 0x02BA, 0, VR::DS, VM::M1, "ChannelShieldNominalTransmission" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0635[] = {
{ 0x0018, 0x9433, 0, VR::LO, VM::M1, "FieldOfViewDescription" },
{ 0x0018, 0x9803, 0, VR::SQ, VM::M1, "ExcludedIntervalsSequence" },
{ 0x0022, 0x1211, 0, VR::SQ, VM::M1, "OphthalmicAxialLengthMeasurementsSegmentalLengthSequence" },
{ 0x003A, 0x0248, 0, VR::FL, VM::M1, "AbsoluteChannelDisplayScale" },
{ 0x0046, 0x0234, 0, VR::FL, VM::M1, "CornealEccentricityIndex" },
{ 0x0072, 0x0200, 0, VR::SQ, VM::M1, "DisplaySetsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0636[] = {
{ 0x0018, 0x9024, 0, VR::CS, VM::M1, "SaturationRecovery" },
{ 0x0018, 0x9434, 0, VR::SQ, VM::M1, "ExposureControlSensingRegionsSequence" },
{ 0x0018, 0x9804, 0, VR::DT, VM::M1, "ExclusionStartDateTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0637[] = {
{ 0x0018, 0x9025, 0, VR::CS, VM::M1, "SpectrallySelectedSuppression" },
{ 0x0018, 0x9435, 0, VR::CS, VM::M1, "ExposureControlSensingRegionShape" },
{ 0x0018, 0x9805, 0, VR::FD, VM::M1, "ExclusionDuration" },
{ 0x0046, 0x0232, 0, VR::FL, VM::M1, "SurfaceAsymmetryIndex" },
{ 0x0054, 0x0220, 0, VR::SQ, VM::M1, "ViewCodeSequence" },
{ 0x0072, 0x0206, 0, VR::LO, VM::M1, "DisplaySetPresentationGroupDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0638[] = {
{ 0x0018, 0x9026, 0, VR::CS, VM::M1, "SpectrallySelectedExcitation" },
{ 0x0018, 0x9436, 0, VR::SS, VM::M1, "ExposureControlSensingRegionLeftVerticalEdge" },
{ 0x0018, 0x9806, 0, VR::SQ, VM::M1, "USImageDescriptionSequence" },
{ 0x0070, 0x0207, 0, VR::LO, VM::M1, "GraphicGroupLabel" },
{ 0x0074, 0x1242, 0, VR::CS, VM::M1, "SCPStatus" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0639[] = {
{ 0x0018, 0x9027, 0, VR::CS, VM::M1, "SpatialPresaturation" },
{ 0x0018, 0x9437, 0, VR::SS, VM::M1, "ExposureControlSensingRegionRightVerticalEdge" },
{ 0x0018, 0x9807, 0, VR::SQ, VM::M1, "ImageDataTypeSequence" },
{ 0x0046, 0x0230, 0, VR::FL, VM::M1, "SurfaceRegularityIndex" },
{ 0x0054, 0x0222, 0, VR::SQ, VM::M1, "ViewModifierCodeSequence" },
{ 0x0072, 0x0204, 0, VR::US, VM::M1, "DisplaySetPresentationGroup" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0640[] = {
{ 0x0008, 0x2200, 1, VR::CS, VM::M1, "TransducerPosition" },
{ 0x0040, 0xA040, 0, VR::CS, VM::M1, "ValueType" },
{ 0x2200, 0x0008, 0, VR::CS, VM::M1, "IncludeNonDICOMObjects" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0641[] = {
{ 0x2200, 0x0009, 0, VR::CS, VM::M1, "IncludeDisplayApplication" },
{ 0x3008, 0x0240, 0, VR::SQ, VM::M1, "FractionStatusSummarySequence" },
{ 0x300A, 0x0242, 0, VR::SH, VM::M1, "TemplateType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0642[] = {
{ 0x0088, 0x0200, 0, VR::SQ, VM::M1, "IconImageSequence" },
{ 0x2200, 0x000A, 0, VR::CS, VM::M1, "PreserveCompositeInstancesAfterMediaCreation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0643[] = {
{ 0x0040, 0xA043, 0, VR::SQ, VM::M1, "ConceptNameCodeSequence" },
{ 0x2200, 0x000B, 0, VR::US, VM::M1, "TotalNumberOfPiecesOfMediaCreated" },
{ 0x300A, 0x0240, 0, VR::IS, VM::M1, "TemplateNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0644[] = {
{ 0x0008, 0x2204, 1, VR::CS, VM::M1, "TransducerOrientation" },
{ 0x0068, 0x6360, 0, VR::SQ, VM::M1, "SurfaceModelDescriptionSequence" },
{ 0x2200, 0x000C, 0, VR::LO, VM::M1, "RequestedMediaApplicationProfile" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0645[] = {
{ 0x2200, 0x000D, 0, VR::SQ, VM::M1, "ReferencedStorageMediaSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0646[] = {
{ 0x2200, 0x000E, 0, VR::AT, VM::M1TN, "FailureAttributes" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0647[] = {
{ 0x0040, 0xA047, 1, VR::LO, VM::M1, "MeasurementPrecisionDescriptionTrial" },
{ 0x2200, 0x000F, 0, VR::CS, VM::M1, "AllowLossyCompression" },
{ 0x300A, 0x0244, 0, VR::LO, VM::M1, "TemplateName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0648[] = {
{ 0x0008, 0x2208, 1, VR::CS, VM::M1, "AnatomicStructure" },
{ 0x0010, 0x2210, 0, VR::CS, VM::M1, "AnatomicalOrientationType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0649[] = {
{ 0x2200, 0x0001, 0, VR::CS, VM::M1, "LabelUsingInformationExtractedFromInstances" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0650[] = {
{ 0x2200, 0x0002, 0, VR::UT, VM::M1, "LabelText" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0651[] = {
{ 0x2200, 0x0003, 0, VR::CS, VM::M1, "LabelStyleSelection" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0652[] = {
{ 0x0014, 0x2210, 2, VR::OB, VM::M1, "CoordinateSystemAxisValues" },
{ 0x2200, 0x0004, 0, VR::LT, VM::M1, "MediaDisposition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0653[] = {
{ 0x2200, 0x0005, 0, VR::LT, VM::M1, "BarcodeValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0654[] = {
{ 0x2200, 0x0006, 0, VR::CS, VM::M1, "BarcodeSymbology" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0655[] = {
{ 0x2200, 0x0007, 0, VR::CS, VM::M1, "AllowMediaSplitting" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0656[] = {
{ 0x0014, 0x220C, 2, VR::CS, VM::M1, "CoordinateSystemAxisType" },
{ 0x0040, 0xA050, 0, VR::CS, VM::M1, "ContinuityOfContent" },
{ 0x3008, 0x0251, 0, VR::TM, VM::M1, "TreatmentTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0657[] = {
{ 0x3008, 0x0250, 0, VR::DA, VM::M1, "TreatmentDate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0658[] = {
{ 0x0014, 0x220E, 2, VR::CS, VM::M1, "CoordinateSystemAxisUnits" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0659[] = {
{ 0x300A, 0x0250, 0, VR::DS, VM::M1, "TotalReferenceAirKerma" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0660[] = {
{ 0x0014, 0x2208, 2, VR::CS, VM::M1, "CoordinateSystemDataSetMapping" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0661[] = {
{ 0x0040, 0x9096, 0, VR::SQ, VM::M1, "RealWorldValueMappingSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0662[] = {
{ 0x0014, 0x220A, 2, VR::IS, VM::M1, "CoordinateSystemAxisNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0663[] = {
{ 0x0040, 0x9094, 0, VR::SQ, VM::M1, "ReferencedImageRealWorldValueMappingSequence" },
{ 0x0040, 0xA057, 1, VR::CS, VM::M1TN, "UrgencyOrPriorityAlertsTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0664[] = {
{ 0x0008, 0x2218, 0, VR::SQ, VM::M1, "AnatomicRegionSequence" },
{ 0x0014, 0x2204, 2, VR::SQ, VM::M1, "CoordinateSystemAxesSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0665[] = {
{ 0x0010, 0x2201, 0, VR::LO, VM::M1, "PatientSpeciesDescription" },
{ 0x0018, 0xA001, 0, VR::SQ, VM::M1, "ContributingEquipmentSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0666[] = {
{ 0x0010, 0x2202, 0, VR::SQ, VM::M1, "PatientSpeciesCodeSequence" },
{ 0x0014, 0x2206, 2, VR::ST, VM::M1, "CoordinateSystemAxisDescription" },
{ 0x0018, 0xA002, 0, VR::DT, VM::M1, "ContributionDateTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0667[] = {
{ 0x0010, 0x2203, 0, VR::CS, VM::M1, "PatientSexNeutered" },
{ 0x0018, 0xA003, 0, VR::ST, VM::M1, "ContributionDescription" },
{ 0x0040, 0x9098, 0, VR::SQ, VM::M1, "PixelValueMappingCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0670[] = {
{ 0x0014, 0x2202, 2, VR::IS, VM::M1, "CoordinateSystemNumberOfAxes" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0672[] = {
{ 0x0008, 0x2220, 0, VR::SQ, VM::M1, "AnatomicRegionModifierSequence" },
{ 0x0040, 0x06FA, 1, VR::LO, VM::M1, "SlideIdentifier" },
{ 0x0040, 0xA060, 1, VR::LO, VM::M1, "SequencingIndicatorTrial" },
{ 0x300A, 0x0263, 0, VR::SH, VM::M1, "BrachyAccessoryDeviceID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0673[] = {
{ 0x0040, 0xB020, 0, VR::SQ, VM::M1, "WaveformAnnotationSequence" },
{ 0x0068, 0x6345, 0, VR::ST, VM::M1, "HPGLPenDescription" },
{ 0x300A, 0x0262, 0, VR::IS, VM::M1, "BrachyAccessoryDeviceNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0674[] = {
{ 0x0068, 0x6346, 0, VR::FD, VM::M2, "RecommendedRotationPoint" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0675[] = {
{ 0x0068, 0x6347, 0, VR::FD, VM::M4, "BoundingRectangle" },
{ 0x300A, 0x0260, 0, VR::SQ, VM::M1, "BrachyAccessoryDeviceSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0676[] = {
{ 0x0068, 0x6340, 0, VR::LO, VM::M1, "HPGLPenLabel" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0677[] = {
{ 0x300A, 0x0266, 0, VR::LO, VM::M1, "BrachyAccessoryDeviceName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0678[] = {
{ 0x0040, 0xA066, 1, VR::SQ, VM::M1, "DocumentIdentifierCodeSequenceTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0679[] = {
{ 0x0040, 0xA067, 1, VR::PN, VM::M1, "DocumentAuthorTrial" },
{ 0x300A, 0x0264, 0, VR::CS, VM::M1, "BrachyAccessoryDeviceType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0680[] = {
{ 0x0008, 0x2228, 0, VR::SQ, VM::M1, "PrimaryAnatomicStructureSequence" },
{ 0x0040, 0xA068, 1, VR::SQ, VM::M1, "DocumentAuthorIdentifierCodeSequenceTrial" },
{ 0x2200, 0x0020, 0, VR::CS, VM::M1, "RequestPriority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0681[] = {
{ 0x0008, 0x2229, 0, VR::SQ, VM::M1, "AnatomicStructureSpaceOrRegionSequence" },
{ 0x300A, 0x026A, 0, VR::DS, VM::M1, "BrachyAccessoryDeviceNominalThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0687[] = {
{ 0x300A, 0x026C, 0, VR::DS, VM::M1, "BrachyAccessoryDeviceNominalTransmission" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0688[] = {
{ 0x0008, 0x2230, 0, VR::SQ, VM::M1, "PrimaryAnatomicStructureModifierSequence" },
{ 0x0014, 0x222C, 2, VR::DS, VM::M1TN, "CoordinateSystemTransformTranslationMatrix" },
{ 0x0040, 0xA070, 1, VR::SQ, VM::M1, "IdentifierCodeSequenceTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0691[] = {
{ 0x0040, 0xA073, 0, VR::SQ, VM::M1, "VerifyingObserverSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0692[] = {
{ 0x0014, 0x2228, 2, VR::CS, VM::M1, "TransformedAxisUnits" },
{ 0x0040, 0xA074, 1, VR::OB, VM::M1, "ObjectBinaryIdentifierTrial" },
{ 0x0068, 0x6350, 0, VR::US, VM::M1TN, "ImplantTemplate3DModelSurfaceNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0693[] = {
{ 0x0040, 0xA075, 0, VR::PN, VM::M1, "VerifyingObserverName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0694[] = {
{ 0x0014, 0x222A, 2, VR::DS, VM::M1TN, "CoordinateSystemTransformRotationAndScaleMatrix" },
{ 0x0040, 0xA076, 1, VR::SQ, VM::M1, "DocumentingObserverIdentifierCodeSequenceTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0696[] = {
{ 0x0014, 0x2224, 2, VR::IS, VM::M1, "TransformNumberOfAxes" },
{ 0x0040, 0xA078, 0, VR::SQ, VM::M1, "AuthorObserverSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0698[] = {
{ 0x0014, 0x2226, 2, VR::IS, VM::M1TN, "TransformOrderOfAxes" },
{ 0x0040, 0xA07A, 0, VR::SQ, VM::M1, "ParticipantSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0700[] = {
{ 0x0014, 0x2220, 2, VR::SQ, VM::M1, "CoordinateSystemTransformSequence" },
{ 0x0040, 0xA07C, 0, VR::SQ, VM::M1, "CustodialOrganizationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0701[] = {
{ 0x7F00, 0x0040, 1, VR::OW, VM::M1, "VariableCoefficientsSDDN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0702[] = {
{ 0x0014, 0x2222, 2, VR::ST, VM::M1, "TransformDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0704[] = {
{ 0x3008, 0x0200, 0, VR::CS, VM::M1, "CurrentTreatmentStatus" },
{ 0x300A, 0x0202, 0, VR::CS, VM::M1, "BrachyTreatmentType" },
{ 0x4FFE, 0x0001, 0, VR::SQ, VM::M1, "MACParametersSequence" },
{ 0x600E, 0x1302, 0, VR::DS, VM::M1, "ROIMean8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0705[] = {
{ 0x0008, 0x2240, 1, VR::SQ, VM::M1, "TransducerPositionSequence" },
{ 0x600C, 0x1301, 0, VR::IS, VM::M1, "ROIArea7" },
{ 0x600E, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0706[] = {
{ 0x0018, 0x9098, 0, VR::FD, VM::M1T2, "TransmitterFrequency" },
{ 0x3008, 0x0202, 0, VR::ST, VM::M1, "TreatmentStatusComment" },
{ 0x300A, 0x0200, 0, VR::CS, VM::M1, "BrachyTreatmentTechnique" },
{ 0x600C, 0x1302, 0, VR::DS, VM::M1, "ROIMean7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0707[] = {
{ 0x0008, 0x2242, 1, VR::SQ, VM::M1, "TransducerPositionModifierSequence" },
{ 0x600C, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation7" },
{ 0x600E, 0x1301, 0, VR::IS, VM::M1, "ROIArea8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0708[] = {
{ 0x300A, 0x0206, 0, VR::SQ, VM::M1, "TreatmentMachineSequence" },
{ 0x600A, 0x1302, 0, VR::DS, VM::M1, "ROIMean6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0709[] = {
{ 0x0008, 0x2244, 1, VR::SQ, VM::M1, "TransducerOrientationSequence" },
{ 0x0068, 0x6320, 0, VR::SQ, VM::M1, "HPGLPenSequence" },
{ 0x6008, 0x1301, 0, VR::IS, VM::M1, "ROIArea5" },
{ 0x600A, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0710[] = {
{ 0x0040, 0xA007, 1, VR::CS, VM::M1, "FindingsFlagTrial" },
{ 0x6008, 0x1302, 0, VR::DS, VM::M1, "ROIMean5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0711[] = {
{ 0x0008, 0x2246, 1, VR::SQ, VM::M1, "TransducerOrientationModifierSequence" },
{ 0x6008, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation5" },
{ 0x600A, 0x1301, 0, VR::IS, VM::M1, "ROIArea6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0712[] = {
{ 0x0018, 0x9092, 0, VR::SQ, VM::M1, "VelocityEncodingAcquisitionSequence" },
{ 0x6006, 0x1302, 0, VR::DS, VM::M1, "ROIMean4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0713[] = {
{ 0x0018, 0x9093, 0, VR::US, VM::M1, "NumberOfKSpaceTrajectories" },
{ 0x6004, 0x1301, 0, VR::IS, VM::M1, "ROIArea3" },
{ 0x6006, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0714[] = {
{ 0x0018, 0x9090, 0, VR::FD, VM::M3, "VelocityEncodingDirection" },
{ 0x0040, 0x0281, 0, VR::SQ, VM::M1, "PerformedProcedureStepDiscontinuationReasonCodeSequence" },
{ 0x6004, 0x1302, 0, VR::DS, VM::M1, "ROIMean3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0715[] = {
{ 0x0018, 0x9091, 0, VR::FD, VM::M1, "VelocityEncodingMinimumValue" },
{ 0x0040, 0x0280, 0, VR::ST, VM::M1, "CommentsOnThePerformedProcedureStep" },
{ 0x6004, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation3" },
{ 0x6006, 0x1301, 0, VR::IS, VM::M1, "ROIArea4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0716[] = {
{ 0x0018, 0x9096, 1, VR::FD, VM::M1, "ParallelReductionFactorInPlaneRetired" },
{ 0x6002, 0x1302, 0, VR::DS, VM::M1, "ROIMean2" },
{ 0x7F00, 0x0030, 1, VR::OW, VM::M1, "VariableCoefficientsSDHN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0717[] = {
{ 0x6000, 0x1301, 0, VR::IS, VM::M1, "ROIArea" },
{ 0x6002, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0718[] = {
{ 0x0018, 0x9094, 0, VR::CS, VM::M1, "CoverageOfKSpace" },
{ 0x6000, 0x1302, 0, VR::DS, VM::M1, "ROIMean" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0719[] = {
{ 0x0018, 0x9095, 0, VR::UL, VM::M1, "SpectroscopyAcquisitionPhaseRows" },
{ 0x6000, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation" },
{ 0x6002, 0x1301, 0, VR::IS, VM::M1, "ROIArea2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0720[] = {
{ 0x0008, 0x2251, 1, VR::SQ, VM::M1, "AnatomicStructureSpaceOrRegionCodeSequenceTrial" },
{ 0x300A, 0x0212, 0, VR::IS, VM::M1, "SourceNumber" },
{ 0x601E, 0x1302, 0, VR::DS, VM::M1, "ROIMean16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0721[] = {
{ 0x0040, 0xA010, 0, VR::CS, VM::M1, "RelationshipType" },
{ 0x601C, 0x1301, 0, VR::IS, VM::M1, "ROIArea15" },
{ 0x601E, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0722[] = {
{ 0x0008, 0x2253, 1, VR::SQ, VM::M1, "AnatomicPortalOfEntranceCodeSequenceTrial" },
{ 0x0040, 0xA403, 1, VR::CS, VM::M1, "ObservationSubjectClassTrial" },
{ 0x300A, 0x0210, 0, VR::SQ, VM::M1, "SourceSequence" },
{ 0x601C, 0x1302, 0, VR::DS, VM::M1, "ROIMean15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0723[] = {
{ 0x0018, 0x9089, 0, VR::FD, VM::M3, "DiffusionGradientOrientation" },
{ 0x0040, 0xA402, 1, VR::UI, VM::M1, "ObservationSubjectUIDTrial" },
{ 0x601C, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation15" },
{ 0x601E, 0x1301, 0, VR::IS, VM::M1, "ROIArea16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0724[] = {
{ 0x0008, 0x2255, 1, VR::SQ, VM::M1, "AnatomicApproachDirectionCodeSequenceTrial" },
{ 0x300A, 0x0216, 0, VR::LO, VM::M1, "SourceManufacturer" },
{ 0x601A, 0x1302, 0, VR::DS, VM::M1, "ROIMean14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0725[] = {
{ 0x0040, 0xA404, 1, VR::SQ, VM::M1, "ObservationSubjectTypeCodeSequenceTrial" },
{ 0x0068, 0x6330, 0, VR::US, VM::M1, "HPGLPenNumber" },
{ 0x6018, 0x1301, 0, VR::IS, VM::M1, "ROIArea13" },
{ 0x601A, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0726[] = {
{ 0x0008, 0x2257, 1, VR::SQ, VM::M1, "AnatomicPerspectiveCodeSequenceTrial" },
{ 0x300A, 0x0214, 0, VR::CS, VM::M1, "SourceType" },
{ 0x6018, 0x1302, 0, VR::DS, VM::M1, "ROIMean13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0727[] = {
{ 0x0008, 0x2256, 1, VR::ST, VM::M1, "AnatomicPerspectiveDescriptionTrial" },
{ 0x6018, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation13" },
{ 0x601A, 0x1301, 0, VR::IS, VM::M1, "ROIArea14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0728[] = {
{ 0x0008, 0x2259, 1, VR::SQ, VM::M1, "AnatomicLocationOfExaminingInstrumentCodeSequenceTrial" },
{ 0x0008, 0x9092, 0, VR::SQ, VM::M1, "ReferencedImageEvidenceSequence" },
{ 0x0018, 0x9082, 0, VR::FD, VM::M1, "EffectiveEchoTime" },
{ 0x0040, 0x0293, 0, VR::SQ, VM::M1, "QuantitySequence" },
{ 0x300A, 0x021A, 0, VR::DS, VM::M1, "ActiveSourceLength" },
{ 0x6016, 0x1302, 0, VR::DS, VM::M1, "ROIMean12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0729[] = {
{ 0x0008, 0x2258, 1, VR::ST, VM::M1, "AnatomicLocationOfExaminingInstrumentDescriptionTrial" },
{ 0x0018, 0x9083, 0, VR::SQ, VM::M1, "MetaboliteMapCodeSequence" },
{ 0x300A, 0x021B, 0, VR::SH, VM::M1, "SourceModelID" },
{ 0x6014, 0x1301, 0, VR::IS, VM::M1, "ROIArea11" },
{ 0x6016, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0730[] = {
{ 0x0018, 0x9080, 0, VR::ST, VM::M1, "MetaboliteMapDescription" },
{ 0x300A, 0x0218, 0, VR::DS, VM::M1, "ActiveSourceDiameter" },
{ 0x6014, 0x1302, 0, VR::DS, VM::M1, "ROIMean11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0731[] = {
{ 0x0008, 0x225A, 1, VR::SQ, VM::M1, "AnatomicStructureSpaceOrRegionModifierCodeSequenceTrial" },
{ 0x0018, 0x9081, 0, VR::CS, VM::M1, "PartialFourier" },
{ 0x6014, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation11" },
{ 0x6016, 0x1301, 0, VR::IS, VM::M1, "ROIArea12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0732[] = {
{ 0x6012, 0x1302, 0, VR::DS, VM::M1, "ROIMean10" },
{ 0x7F00, 0x0020, 1, VR::OW, VM::M1, "VariableCoefficientsSDVN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0733[] = {
{ 0x0008, 0x225C, 1, VR::SQ, VM::M1, "OnAxisBackgroundAnatomicStructureCodeSequenceTrial" },
{ 0x0018, 0x9087, 0, VR::FD, VM::M1, "DiffusionBValue" },
{ 0x0040, 0x0296, 0, VR::SQ, VM::M1, "BillingItemSequence" },
{ 0x6010, 0x1301, 0, VR::IS, VM::M1, "ROIArea9" },
{ 0x6012, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0734[] = {
{ 0x0018, 0x9084, 0, VR::SQ, VM::M1, "ChemicalShiftSequence" },
{ 0x0040, 0x0295, 0, VR::SQ, VM::M1, "MeasuringUnitsSequence" },
{ 0x300A, 0x021C, 0, VR::LO, VM::M1, "SourceDescription" },
{ 0x6010, 0x1302, 0, VR::DS, VM::M1, "ROIMean9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0735[] = {
{ 0x0018, 0x9085, 0, VR::CS, VM::M1, "CardiacSignalSource" },
{ 0x0040, 0x0294, 0, VR::DS, VM::M1, "Quantity" },
{ 0x6010, 0x1303, 0, VR::DS, VM::M1, "ROIStandardDeviation9" },
{ 0x6012, 0x1301, 0, VR::IS, VM::M1, "ROIArea10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0736[] = {
{ 0x0040, 0xA021, 1, VR::UI, VM::M1, "FindingsGroupUIDTrial" },
{ 0x3008, 0x0220, 0, VR::SQ, VM::M1, "FractionGroupSummarySequence" },
{ 0x300A, 0x0222, 0, VR::DS, VM::M1, "SourceEncapsulationNominalThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0737[] = {
{ 0x0040, 0xA020, 1, VR::SQ, VM::M1, "FindingsSequenceTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0738[] = {
{ 0x0040, 0xA023, 1, VR::DA, VM::M1, "FindingsGroupRecordingDateTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0739[] = {
{ 0x0040, 0xA022, 1, VR::UI, VM::M1, "ReferencedFindingsGroupUIDTrial" },
{ 0x3008, 0x0223, 0, VR::IS, VM::M1, "ReferencedFractionNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0740[] = {
{ 0x3008, 0x0224, 0, VR::CS, VM::M1, "FractionGroupType" },
{ 0x300A, 0x0226, 0, VR::LO, VM::M1, "SourceIsotopeName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0741[] = {
{ 0x0040, 0xA024, 1, VR::TM, VM::M1, "FindingsGroupRecordingTimeTrial" },
{ 0x0068, 0x6300, 0, VR::OB, VM::M1, "HPGLDocument" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0742[] = {
{ 0x0040, 0xA027, 0, VR::LO, VM::M1, "VerifyingOrganization" },
{ 0x300A, 0x0224, 0, VR::DS, VM::M1, "SourceEncapsulationNominalTransmission" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0743[] = {
{ 0x0040, 0xA026, 1, VR::SQ, VM::M1, "FindingsSourceCategoryCodeSequenceTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0744[] = {
{ 0x300A, 0x022A, 0, VR::DS, VM::M1, "ReferenceAirKermaRate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0745[] = {
{ 0x0040, 0xA028, 1, VR::SQ, VM::M1, "DocumentingOrganizationIdentifierCodeSequenceTrial" },
{ 0x300A, 0x022B, 0, VR::DS, VM::M1, "SourceStrength" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0746[] = {
{ 0x300A, 0x0228, 0, VR::DS, VM::M1, "SourceIsotopeHalfLife" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0747[] = {
{ 0x300A, 0x0229, 0, VR::CS, VM::M1, "SourceStrengthUnits" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0748[] = {
{ 0x300A, 0x022E, 0, VR::TM, VM::M1, "SourceStrengthReferenceTime" },
{ 0x7F00, 0x0010, 1, VR::OX, VM::M1, "VariablePixelData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0749[] = {
{ 0x7F00, 0x0011, 1, VR::US, VM::M1, "VariableNextDataGroup" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0750[] = {
{ 0x0070, 0x0295, 0, VR::UL, VM::M1, "GraphicGroupID" },
{ 0x300A, 0x022C, 0, VR::DA, VM::M1, "SourceStrengthReferenceDate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0751[] = {
{ 0x0070, 0x0294, 0, VR::CS, VM::M1, "CompoundGraphicType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0752[] = {
{ 0x3008, 0x0230, 0, VR::CS, VM::M1, "BeamStopperPosition" },
{ 0x300A, 0x0232, 0, VR::CS, VM::M1, "ApplicationSetupType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0753[] = {
{ 0x0040, 0xA030, 0, VR::DT, VM::M1, "VerificationDateTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0754[] = {
{ 0x0070, 0x0289, 0, VR::SH, VM::M1, "TickLabel" },
{ 0x300A, 0x0230, 0, VR::SQ, VM::M1, "ApplicationSetupSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0755[] = {
{ 0x0028, 0x9099, 1, VR::US, VM::M1, "LargestMonochromePixelValue" },
{ 0x0040, 0xA032, 0, VR::DT, VM::M1, "ObservationDateTime" },
{ 0x0070, 0x0288, 0, VR::FL, VM::M1, "TickPosition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0756[] = {
{ 0x300A, 0x0236, 0, VR::LO, VM::M1, "ApplicationSetupName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0757[] = {
{ 0x0068, 0x6310, 0, VR::US, VM::M1, "HPGLContourPenNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0758[] = {
{ 0x300A, 0x0234, 0, VR::IS, VM::M1, "ApplicationSetupNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0761[] = {
{ 0x0070, 0x0282, 0, VR::CS, VM::M1, "CompoundGraphicUnits" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0762[] = {
{ 0x300A, 0x0238, 0, VR::LO, VM::M1, "ApplicationSetupManufacturer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0764[] = {
{ 0x0070, 0x0287, 0, VR::SQ, VM::M1, "MajorTicksSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0766[] = {
{ 0x0070, 0x0285, 0, VR::FL, VM::M1, "PatternOffOpacity" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0767[] = {
{ 0x0070, 0x0284, 0, VR::FL, VM::M1, "PatternOnOpacity" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0768[] = {
{ 0x0020, 0x9165, 0, VR::AT, VM::M1, "DimensionIndexPointer" },
{ 0x4008, 0x0200, 1, VR::SH, VM::M1, "InterpretationID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0769[] = {
{ 0x0020, 0x9164, 0, VR::UI, VM::M1, "DimensionOrganizationUID" },
{ 0x0074, 0x1338, 0, VR::FD, VM::M1, "DoubleExposureMeterset" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0770[] = {
{ 0x0020, 0x9167, 0, VR::AT, VM::M1, "FunctionalGroupPointer" },
{ 0x0068, 0x62E0, 0, VR::SQ, VM::M1, "ViewOrientationCodeSequence" },
{ 0x4008, 0x0202, 1, VR::LO, VM::M1, "InterpretationIDIssuer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0771[] = {
{ 0x0074, 0x133A, 0, VR::FD, VM::M4, "DoubleExposureFieldDelta" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0772[] = {
{ 0x0018, 0x9159, 0, VR::UL, VM::M1, "SpectroscopyAcquisitionOutOfPlanePhaseSteps" },
{ 0x0020, 0x9161, 0, VR::UI, VM::M1, "ConcatenationUID" },
{ 0x0028, 0x0730, 1, VR::US, VM::M1, "AdaptiveMapFormat" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0774[] = {
{ 0x0020, 0x9163, 0, VR::US, VM::M1, "InConcatenationTotalNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0775[] = {
{ 0x0020, 0x9162, 0, VR::US, VM::M1, "InConcatenationNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0776[] = {
{ 0x0018, 0x9155, 0, VR::FD, VM::M1, "ParallelReductionFactorOutOfPlane" },
{ 0x0024, 0x0320, 0, VR::SQ, VM::M1, "VisualFieldGlobalResultsIndexSequence" },
{ 0x0054, 0x1311, 0, VR::IS, VM::M1TN, "SecondaryCountsAccumulated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0777[] = {
{ 0x0054, 0x1310, 0, VR::IS, VM::M1, "PrimaryPromptsCountsAccumulated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0780[] = {
{ 0x0018, 0x9151, 0, VR::DT, VM::M1, "FrameReferenceDateTime" },
{ 0x0040, 0x0340, 0, VR::SQ, VM::M1, "PerformedSeriesSequence" },
{ 0x0400, 0x0310, 0, VR::OB, VM::M1, "CertifiedTimestamp" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0781[] = {
{ 0x0024, 0x0325, 0, VR::SQ, VM::M1, "DataObservationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0783[] = {
{ 0x0018, 0x9152, 0, VR::SQ, VM::M1, "MRMetaboliteMapSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0784[] = {
{ 0x0024, 0x0338, 0, VR::CS, VM::M1, "IndexNormalsFlag" },
{ 0x0068, 0x62F2, 0, VR::FD, VM::M1, "HPGLDocumentScaling" },
{ 0x4008, 0x0210, 1, VR::CS, VM::M1, "InterpretationTypeID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0786[] = {
{ 0x0068, 0x62F0, 0, VR::FD, VM::M9, "ViewOrientationModifier" },
{ 0x4008, 0x0212, 1, VR::CS, VM::M1, "InterpretationStatusID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0788[] = {
{ 0x0020, 0x9171, 0, VR::SQ, VM::M1, "UnassignedPerFrameConvertedAttributesSequence" },
{ 0x0028, 0x0720, 1, VR::US, VM::M1, "ZonalMapNumberFormat" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0789[] = {
{ 0x0020, 0x9170, 0, VR::SQ, VM::M1, "UnassignedSharedConvertedAttributesSequence" },
{ 0x0028, 0x0721, 1, VR::AT, VM::M1TN, "ZonalMapLocation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0790[] = {
{ 0x0028, 0x0722, 1, VR::US, VM::M1, "ZonalMapFormat" },
{ 0x0040, 0x074A, 0, VR::DS, VM::M1, "ZOffsetInSlideCoordinateSystem" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0791[] = {
{ 0x0020, 0x9172, 0, VR::SQ, VM::M1, "ConversionSourceAttributesSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0793[] = {
{ 0x0008, 0x9154, 0, VR::SQ, VM::M1, "SourceImageEvidenceSequence" },
{ 0x0054, 0x1300, 0, VR::DS, VM::M1, "FrameReferenceTime" },
{ 0x0400, 0x0305, 0, VR::CS, VM::M1, "CertifiedTimestampType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0794[] = {
{ 0x0018, 0x9147, 0, VR::CS, VM::M1, "DiffusionAnisotropyType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0797[] = {
{ 0x0074, 0x1324, 0, VR::UL, VM::M1, "BeamOrderIndex" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0800[] = {
{ 0x0024, 0x0308, 0, VR::LO, VM::M1, "DataSetSource" },
{ 0x0028, 0x0304, 0, VR::UI, VM::M1, "ReferencedColorPaletteInstanceUID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0801[] = {
{ 0x0024, 0x0309, 0, VR::LO, VM::M1, "DataSetDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0802[] = {
{ 0x0068, 0x62C0, 0, VR::SQ, VM::M1, "HPGLDocumentSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0804[] = {
{ 0x0018, 0x9179, 0, VR::CS, VM::M1, "SpecificAbsorptionRateDefinition" },
{ 0x0028, 0x0300, 0, VR::CS, VM::M1, "QualityControlImage" },
{ 0x0028, 0x0710, 1, VR::US, VM::M1, "NormalizationFactorFormat" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0805[] = {
{ 0x0018, 0x9178, 0, VR::CS, VM::M1, "OperatingMode" },
{ 0x0028, 0x0301, 0, VR::CS, VM::M1, "BurnedInAnnotation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0806[] = {
{ 0x0028, 0x0302, 0, VR::CS, VM::M1, "RecognizableVisualFeatures" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0807[] = {
{ 0x0028, 0x0303, 0, VR::CS, VM::M1, "LongitudinalTemporalInformationModified" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0808[] = {
{ 0x0018, 0x9175, 0, VR::LO, VM::M1, "ApplicableSafetyStandardDescription" },
{ 0x0028, 0x9145, 0, VR::SQ, VM::M1, "PixelValueTransformationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0809[] = {
{ 0x0018, 0x9174, 0, VR::CS, VM::M1, "ApplicableSafetyStandardAgency" },
{ 0x0054, 0x1330, 0, VR::US, VM::M1, "ImageIndex" },
{ 0x5200, 0x9229, 0, VR::SQ, VM::M1, "SharedFunctionalGroupsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0810[] = {
{ 0x0018, 0x9177, 0, VR::CS, VM::M1, "OperatingModeType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0811[] = {
{ 0x0018, 0x9176, 0, VR::SQ, VM::M1, "OperatingModeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0812[] = {
{ 0x0018, 0x9171, 0, VR::CS, VM::M1, "RespiratorySignalSource" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0813[] = {
{ 0x0018, 0x9170, 0, VR::CS, VM::M1, "RespiratoryMotionCompensationTechnique" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0814[] = {
{ 0x0018, 0x9173, 0, VR::CS, VM::M1, "BulkMotionSignalSource" },
{ 0x0024, 0x0306, 0, VR::LO, VM::M1, "DataSetName" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0815[] = {
{ 0x0018, 0x9172, 0, VR::CS, VM::M1, "BulkMotionCompensationTechnique" },
{ 0x0024, 0x0307, 0, VR::LO, VM::M1, "DataSetVersion" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0816[] = {
{ 0x0020, 0x9155, 0, VR::FL, VM::M1, "ActualCardiacTriggerTimePriorToRPeak" },
{ 0x5200, 0x9230, 0, VR::SQ, VM::M1, "PerFrameFunctionalGroupsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0817[] = {
{ 0x0020, 0x9154, 0, VR::FL, VM::M1, "NominalCardiacTriggerTimePriorToRPeak" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0818[] = {
{ 0x0020, 0x9157, 0, VR::UL, VM::M1TN, "DimensionIndexValues" },
{ 0x0068, 0x62D0, 0, VR::US, VM::M1, "HPGLDocumentID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0819[] = {
{ 0x0020, 0x9156, 0, VR::US, VM::M1, "FrameAcquisitionNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0820[] = {
{ 0x0018, 0x9169, 0, VR::CS, VM::M1, "CardiacBeatRejectionTechnique" },
{ 0x0028, 0x0700, 1, VR::LO, VM::M1, "DCTLabel" },
{ 0x0028, 0x1351, 0, VR::ST, VM::M1, "PartialViewDescription" },
{ 0x0038, 0x0300, 0, VR::LO, VM::M1, "CurrentPatientLocation" },
{ 0x003A, 0x0302, 0, VR::CS, VM::M1, "ChannelMode" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0821[] = {
{ 0x0018, 0x9168, 0, VR::FD, VM::M1, "ParallelReductionFactorSecondInPlane" },
{ 0x0028, 0x0701, 1, VR::CS, VM::M1TN, "DataBlockDescription" },
{ 0x0028, 0x1350, 0, VR::CS, VM::M1, "PartialView" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0822[] = {
{ 0x0020, 0x9153, 0, VR::FD, VM::M1, "NominalCardiacTriggerDelayTime" },
{ 0x0028, 0x0702, 1, VR::AT, VM::M1TN, "DataBlock" },
{ 0x003A, 0x0300, 0, VR::SQ, VM::M1, "MultiplexedAudioChannelsDescriptionCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0823[] = {
{ 0x0028, 0x1352, 0, VR::SQ, VM::M1, "PartialViewCodeSequence" },
{ 0x003A, 0x0301, 0, VR::IS, VM::M1, "ChannelIdentificationCode" },
{ 0x0068, 0x62D5, 0, VR::LO, VM::M1, "HPGLDocumentLabel" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0824[] = {
{ 0x0054, 0x1321, 0, VR::DS, VM::M1, "DecayFactor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0825[] = {
{ 0x0054, 0x1320, 0, VR::DS, VM::M1, "SliceSensitivityFactor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0826[] = {
{ 0x0054, 0x1323, 0, VR::DS, VM::M1, "ScatterFractionFactor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0827[] = {
{ 0x0018, 0x9166, 1, VR::CS, VM::M1, "BulkMotionStatus" },
{ 0x0054, 0x1322, 0, VR::DS, VM::M1, "DoseCalibrationFactor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0829[] = {
{ 0x0020, 0x9158, 0, VR::LT, VM::M1, "FrameComments" },
{ 0x0054, 0x1324, 0, VR::DS, VM::M1, "DeadTimeFactor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0831[] = {
{ 0x0024, 0x0317, 0, VR::SQ, VM::M1, "VisualFieldTestReliabilityGlobalIndexSequence" },
{ 0x0028, 0x135A, 0, VR::CS, VM::M1, "SpatialLocationsPreserved" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0832[] = {
{ 0x0018, 0x1314, 0, VR::DS, VM::M1, "FlipAngle" },
{ 0x0018, 0x1704, 0, VR::IS, VM::M1, "CollimatorRightVerticalEdge" },
{ 0x0018, 0x5210, 1, VR::DS, VM::M6, "ImageTransformationMatrix" },
{ 0x300A, 0x0384, 0, VR::FL, VM::M1, "RangeModulatorGatingStopValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0833[] = {
{ 0x0018, 0x1315, 0, VR::CS, VM::M1, "VariableFlipAngleFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0834[] = {
{ 0x0018, 0x1316, 0, VR::DS, VM::M1, "SAR" },
{ 0x0018, 0x1706, 0, VR::IS, VM::M1, "CollimatorUpperHorizontalEdge" },
{ 0x0018, 0x5212, 1, VR::DS, VM::M3, "ImageTranslationVector" },
{ 0x0020, 0x9536, 0, VR::US, VM::M1, "ReconstructionIndex" },
{ 0x300A, 0x0386, 0, VR::FL, VM::M1, "RangeModulatorGatingStartWaterEquivalentThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0835[] = {
{ 0x0040, 0x030E, 0, VR::SQ, VM::M1, "ExposureDoseSequence" },
{ 0x0068, 0x62A0, 0, VR::SQ, VM::M1, "ImplantRegulatoryDisapprovalCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0836[] = {
{ 0x0018, 0x1310, 0, VR::US, VM::M4, "AcquisitionMatrix" },
{ 0x0018, 0x1700, 0, VR::CS, VM::M1T3, "CollimatorShape" },
{ 0x0018, 0x9118, 0, VR::SQ, VM::M1, "CardiacSynchronizationSequence" },
{ 0x0018, 0x9508, 0, VR::FL, VM::M1, "PrimaryPositionerScanArc" },
{ 0x0048, 0x0301, 0, VR::CS, VM::M1, "PixelOriginInterpretation" },
{ 0x300A, 0x0380, 0, VR::SQ, VM::M1, "RangeModulatorSettingsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0837[] = {
{ 0x0018, 0x9119, 0, VR::SQ, VM::M1, "MRAveragesSequence" },
{ 0x0018, 0x9509, 0, VR::FL, VM::M1, "SecondaryPositionerScanArc" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0838[] = {
{ 0x0018, 0x1312, 0, VR::CS, VM::M1, "InPlanePhaseEncodingDirection" },
{ 0x0018, 0x1702, 0, VR::IS, VM::M1, "CollimatorLeftVerticalEdge" },
{ 0x0068, 0x62A5, 0, VR::FD, VM::M1, "OverallTemplateSpatialTolerance" },
{ 0x300A, 0x0382, 0, VR::FL, VM::M1, "RangeModulatorGatingStartValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0839[] = {
{ 0x0040, 0x071A, 0, VR::SQ, VM::M1, "ImageCenterPointCoordinatesSequence" },
{ 0x0040, 0xA180, 0, VR::US, VM::M1, "AnnotationGroupNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0840[] = {
{ 0x0018, 0x9114, 0, VR::SQ, VM::M1, "MREchoSequence" },
{ 0x0018, 0x9504, 0, VR::SQ, VM::M1, "XRay3DFrameTypeSequence" },
{ 0x5600, 0x0010, 0, VR::OF, VM::M1, "FirstOrderPhaseCorrectionAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0841[] = {
{ 0x0018, 0x9115, 0, VR::SQ, VM::M1, "MRModifierSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0842[] = {
{ 0x0018, 0x9506, 0, VR::SQ, VM::M1, "ContributingSourcesSequence" },
{ 0x0040, 0x0307, 1, VR::DS, VM::M1, "DistanceSourceToSupport" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0843[] = {
{ 0x0018, 0x9117, 0, VR::SQ, VM::M1, "MRDiffusionSequence" },
{ 0x0018, 0x9507, 0, VR::SQ, VM::M1, "XRay3DAcquisitionSequence" },
{ 0x0028, 0x9537, 0, VR::CS, VM::M1, "EquipmentCoordinateSystemIdentification" },
{ 0x0040, 0x0306, 0, VR::DS, VM::M1, "DistanceSourceToEntrance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0844[] = {
{ 0x0018, 0x1318, 0, VR::DS, VM::M1, "dBdt" },
{ 0x0018, 0x1708, 0, VR::IS, VM::M1, "CollimatorLowerHorizontalEdge" },
{ 0x0018, 0x8151, 0, VR::DS, VM::M1, "XRayTubeCurrentInuA" },
{ 0x0020, 0x9128, 0, VR::UL, VM::M1, "TemporalPositionIndex" },
{ 0x0040, 0x0301, 0, VR::US, VM::M1, "TotalNumberOfExposures" },
{ 0x300A, 0x0388, 0, VR::FL, VM::M1, "RangeModulatorGatingStopWaterEquivalentThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0845[] = {
{ 0x0018, 0x8150, 0, VR::DS, VM::M1, "ExposureTimeInuS" },
{ 0x0040, 0x0300, 0, VR::US, VM::M1, "TotalTimeOfFluoroscopy" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0846[] = {
{ 0x0018, 0x9112, 0, VR::SQ, VM::M1, "MRTimingAndRelatedParametersSequence" },
{ 0x0040, 0x0303, 0, VR::US, VM::M1T2, "ExposedArea" },
{ 0x300A, 0x038A, 0, VR::FL, VM::M1, "IsocenterToRangeModulatorDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0847[] = {
{ 0x0040, 0x0302, 0, VR::US, VM::M1, "EntranceDose" },
{ 0x0072, 0x0330, 0, VR::FD, VM::M1, "CineRelativeToRealTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0848[] = {
{ 0x300A, 0x0394, 0, VR::FL, VM::M1TN, "ScanSpotPositionMap" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0849[] = {
{ 0x0054, 0x0308, 0, VR::US, VM::M1, "EnergyWindowNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0850[] = {
{ 0x0040, 0xA195, 0, VR::SQ, VM::M1, "ModifierCodeSequence" },
{ 0x300A, 0x0396, 0, VR::FL, VM::M1TN, "ScanSpotMetersetWeights" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0851[] = {
{ 0x0040, 0xA194, 1, VR::CS, VM::M1, "MeasurementAutomationTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0852[] = {
{ 0x0018, 0x1300, 0, VR::DS, VM::M1, "ScanVelocity" },
{ 0x0018, 0x1710, 0, VR::IS, VM::M2, "CenterOfCircularCollimator" },
{ 0x0040, 0xA193, 1, VR::TM, VM::M1, "ObservationTimeTrial" },
{ 0x300A, 0x0390, 0, VR::SH, VM::M1, "ScanSpotTuneID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0853[] = {
{ 0x0018, 0x1301, 0, VR::CS, VM::M1TN, "WholeBodyTechnique" },
{ 0x0040, 0x0318, 0, VR::CS, VM::M1, "OrganExposed" },
{ 0x0040, 0xA192, 1, VR::DA, VM::M1, "ObservationDateTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0854[] = {
{ 0x0018, 0x1302, 0, VR::IS, VM::M1, "ScanLength" },
{ 0x0018, 0x1712, 0, VR::IS, VM::M1, "RadiusOfCircularCollimator" },
{ 0x300A, 0x0392, 0, VR::IS, VM::M1, "NumberOfScanSpotPositions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0856[] = {
{ 0x0018, 0x9104, 0, VR::FD, VM::M1, "SlabThickness" },
{ 0x0018, 0x9514, 0, VR::FL, VM::M1, "PrimaryPositionerIncrement" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0857[] = {
{ 0x0018, 0x9105, 0, VR::FD, VM::M3, "SlabOrientation" },
{ 0x0018, 0x9515, 0, VR::FL, VM::M1, "SecondaryPositionerIncrement" },
{ 0x0040, 0x0314, 0, VR::DS, VM::M1, "HalfValueLayer" },
{ 0x0054, 0x0300, 0, VR::SQ, VM::M1, "RadionuclideCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0858[] = {
{ 0x0018, 0x9106, 0, VR::FD, VM::M3, "MidSlabPosition" },
{ 0x0018, 0x9516, 0, VR::DT, VM::M1, "StartAcquisitionDateTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0859[] = {
{ 0x0018, 0x9107, 0, VR::SQ, VM::M1, "MRSpatialSaturationSequence" },
{ 0x0018, 0x9517, 0, VR::DT, VM::M1, "EndAcquisitionDateTime" },
{ 0x0040, 0x0316, 0, VR::DS, VM::M1, "OrganDose" },
{ 0x0054, 0x0302, 0, VR::SQ, VM::M1, "AdministrationRouteCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0860[] = {
{ 0x0018, 0x9100, 0, VR::CS, VM::M1T2, "ResonantNucleus" },
{ 0x0018, 0x9510, 0, VR::FL, VM::M1, "PrimaryPositionerScanStartAngle" },
{ 0x0028, 0x9520, 0, VR::DS, VM::M16, "ImageToEquipmentMappingMatrix" },
{ 0x300A, 0x0398, 0, VR::FL, VM::M2, "ScanningSpotSize" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0861[] = {
{ 0x0018, 0x9101, 0, VR::CS, VM::M1, "FrequencyCorrection" },
{ 0x0018, 0x9511, 0, VR::FL, VM::M1, "SecondaryPositionerScanStartAngle" },
{ 0x0020, 0x9529, 0, VR::SQ, VM::M1, "ContributingSOPInstancesReferenceSequence" },
{ 0x0040, 0x0310, 0, VR::ST, VM::M1, "CommentsOnRadiationDose" },
{ 0x0054, 0x0304, 0, VR::SQ, VM::M1, "RadiopharmaceuticalCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0862[] = {
{ 0x0022, 0x1330, 0, VR::SQ, VM::M1, "ReferencedOphthalmicAxialLengthMeasurementQCImageSequence" },
{ 0x0028, 0x9132, 0, VR::SQ, VM::M1, "FrameVOILUTSequence" },
{ 0x300A, 0x039A, 0, VR::IS, VM::M1, "NumberOfPaintings" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0863[] = {
{ 0x0018, 0x9103, 0, VR::SQ, VM::M1, "MRSpectroscopyFOVGeometrySequence" },
{ 0x0040, 0x0312, 0, VR::DS, VM::M1, "XRayOutput" },
{ 0x0054, 0x0306, 0, VR::SQ, VM::M1, "CalibrationDataSequence" },
{ 0x0072, 0x0320, 0, VR::US, VM::M1, "ImageBoxOverlapPriority" },
{ 0xFFFE, 0xE0DD, 0, VR::XX, VM::M0, "SequenceDelimitationItem" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0864[] = {
{ 0x300A, 0x03A4, 0, VR::SQ, VM::M1, "IonBeamLimitingDeviceSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0865[] = {
{ 0x0070, 0x031C, 0, VR::SQ, VM::M1, "FiducialSetSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0866[] = {
{ 0x300A, 0x03A6, 0, VR::SQ, VM::M1, "IonBlockSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0867[] = {
{ 0x0068, 0x6280, 0, VR::ST, VM::M1, "InformationSummary" },
{ 0x0070, 0x031E, 0, VR::SQ, VM::M1, "FiducialSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0868[] = {
{ 0x0018, 0x1720, 0, VR::IS, VM::M2T2N, "VerticesOfThePolygonalCollimator" },
{ 0x0018, 0x9528, 0, VR::LO, VM::M1, "AlgorithmDescription" },
{ 0x0028, 0x1300, 0, VR::CS, VM::M1, "BreastImplantPresent" },
{ 0x0028, 0x9108, 0, VR::CS, VM::M1, "DataRepresentation" },
{ 0x300A, 0x03A0, 0, VR::SQ, VM::M1, "IonToleranceTableSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0869[] = {
{ 0x0070, 0x0318, 0, VR::SQ, VM::M1, "GraphicCoordinatesDataSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0870[] = {
{ 0x300A, 0x03A2, 0, VR::SQ, VM::M1, "IonBeamSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0871[] = {
{ 0x0040, 0x073A, 0, VR::DS, VM::M1, "YOffsetInSlideCoordinateSystem" },
{ 0x0070, 0x031A, 0, VR::UI, VM::M1, "FiducialUID" },
{ 0x0072, 0x0318, 0, VR::US, VM::M1, "ImageBoxLargeScrollAmount" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0872[] = {
{ 0x0008, 0x9124, 0, VR::SQ, VM::M1, "DerivationImageSequence" },
{ 0x0018, 0x9524, 0, VR::LO, VM::M1, "ApplicationName" },
{ 0x0024, 0x0341, 0, VR::FL, VM::M1, "IndexProbability" },
{ 0x300A, 0x03AC, 0, VR::SQ, VM::M1, "IonWedgePositionSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0873[] = {
{ 0x0018, 0x9525, 0, VR::LO, VM::M1, "ApplicationVersion" },
{ 0x0040, 0x0324, 0, VR::SQ, VM::M1, "BillingSuppliesAndDevicesSequence" },
{ 0x0070, 0x0314, 0, VR::SQ, VM::M1, "UsedFiducialsSequence" },
{ 0x0072, 0x0316, 0, VR::CS, VM::M1, "ImageBoxLargeScrollType" },
{ 0x0072, 0x0706, 0, VR::CS, VM::M1, "ShowGrayscaleInverted" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0874[] = {
{ 0x0018, 0x9526, 0, VR::LO, VM::M1, "ApplicationManufacturer" },
{ 0x0072, 0x0705, 0, VR::SQ, VM::M1, "PseudoColorPaletteInstanceReferenceSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0875[] = {
{ 0x0018, 0x9527, 0, VR::CS, VM::M1, "AlgorithmType" },
{ 0x0072, 0x0314, 0, VR::US, VM::M1, "ImageBoxSmallScrollAmount" },
{ 0x0072, 0x0704, 0, VR::CS, VM::M1, "PseudoColorType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0876[] = {
{ 0x0020, 0x9518, 0, VR::US, VM::M1TN, "AcquisitionIndex" },
{ 0x0040, 0x0321, 0, VR::SQ, VM::M1, "FilmConsumptionSequence" },
{ 0x0070, 0x0311, 0, VR::SQ, VM::M1, "FiducialIdentifierCodeSequence" },
{ 0x300A, 0x03A8, 0, VR::SQ, VM::M1, "IonControlPointSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0877[] = {
{ 0x0008, 0x9121, 0, VR::SQ, VM::M1, "ReferencedRawDataSequence" },
{ 0x0024, 0x0344, 0, VR::SQ, VM::M1, "IndexProbabilitySequence" },
{ 0x0040, 0x0320, 0, VR::SQ, VM::M1, "BillingProcedureStepSequence" },
{ 0x0070, 0x0310, 0, VR::SH, VM::M1, "FiducialIdentifier" },
{ 0x0072, 0x0312, 0, VR::CS, VM::M1, "ImageBoxSmallScrollType" },
{ 0x0072, 0x0702, 0, VR::CS, VM::M1, "VOIType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0878[] = {
{ 0x0022, 0x1300, 0, VR::SQ, VM::M1, "IntraocularLensCalculationsRightEyeSequence" },
{ 0x300A, 0x03AA, 0, VR::SQ, VM::M1, "IonWedgeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0879[] = {
{ 0x0008, 0x9123, 0, VR::UI, VM::M1, "CreatorVersionUID" },
{ 0x0070, 0x0312, 0, VR::FD, VM::M1, "ContourUncertaintyRadius" },
{ 0x0072, 0x0310, 0, VR::CS, VM::M1, "ImageBoxScrollDirection" },
{ 0x0072, 0x0700, 0, VR::CS, VM::M2, "DisplaySetPatientOrientation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0880[] = {
{ 0x0070, 0x030D, 0, VR::SQ, VM::M1, "RegistrationTypeCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0881[] = {
{ 0x0070, 0x030C, 0, VR::CS, VM::M1, "FrameOfReferenceTransformationMatrixType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0882[] = {
{ 0x0020, 0x9116, 0, VR::SQ, VM::M1, "PlaneOrientationSequence" },
{ 0x0070, 0x030F, 0, VR::ST, VM::M1, "FiducialDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0884[] = {
{ 0x0018, 0x9538, 0, VR::SQ, VM::M1, "PerProjectionAcquisitionSequence" },
{ 0x0070, 0x0309, 0, VR::SQ, VM::M1, "MatrixRegistrationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0885[] = {
{ 0x0020, 0x9111, 0, VR::SQ, VM::M1, "FrameContentSequence" },
{ 0x0028, 0x0740, 1, VR::US, VM::M1, "CodeNumberFormat" },
{ 0x0040, 0xA992, 1, VR::ST, VM::M1, "UniformResourceLocatorTrial" },
{ 0x0070, 0x0308, 0, VR::SQ, VM::M1, "RegistrationSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0887[] = {
{ 0x0020, 0x9113, 0, VR::SQ, VM::M1, "PlanePositionSequence" },
{ 0x0040, 0x072A, 0, VR::DS, VM::M1, "XOffsetInSlideCoordinateSystem" },
{ 0x0070, 0x030A, 0, VR::SQ, VM::M1, "MatrixSequence" },
{ 0x0072, 0x0308, 0, VR::US, VM::M1, "ImageBoxTileVerticalDimension" },
{ 0x0072, 0x0718, 0, VR::CS, VM::M1, "DisplaySetVerticalJustification" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0888[] = {
{ 0x0072, 0x0717, 0, VR::CS, VM::M1, "DisplaySetHorizontalJustification" },
{ 0x5600, 0x0020, 0, VR::OF, VM::M1, "SpectroscopyData" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0889[] = {
{ 0x0018, 0x9125, 0, VR::SQ, VM::M1, "MRFOVGeometrySequence" },
{ 0x0028, 0x9505, 0, VR::SQ, VM::M1, "MultiFramePresentationSequence" },
{ 0x0072, 0x0306, 0, VR::US, VM::M1, "ImageBoxTileHorizontalDimension" },
{ 0x0072, 0x0716, 0, VR::CS, VM::M1, "ShowAcquisitionTechniquesFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0890[] = {
{ 0x0018, 0x9126, 0, VR::SQ, VM::M1, "VolumeLocalizationSequence" },
{ 0x0028, 0x9506, 0, VR::US, VM::M2T2N, "PixelShiftFrameRange" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0891[] = {
{ 0x0018, 0x9127, 0, VR::UL, VM::M1, "SpectroscopyAcquisitionDataColumns" },
{ 0x0028, 0x9507, 0, VR::US, VM::M2T2N, "LUTFrameRange" },
{ 0x0070, 0x0306, 0, VR::CS, VM::M1, "ShapeType" },
{ 0x0072, 0x0304, 0, VR::CS, VM::M1, "ImageBoxLayoutType" },
{ 0x0072, 0x0714, 0, VR::CS, VM::M1, "ShowPatientDemographicsFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0892[] = {
{ 0x0018, 0x9530, 0, VR::SQ, VM::M1, "XRay3DReconstructionSequence" },
{ 0x0028, 0x9110, 0, VR::SQ, VM::M1, "PixelMeasuresSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0893[] = {
{ 0x0018, 0x9531, 0, VR::LO, VM::M1, "ReconstructionDescription" },
{ 0x0028, 0x9501, 0, VR::SQ, VM::M1, "PixelShiftSequence" },
{ 0x0040, 0x0330, 1, VR::SQ, VM::M1, "ReferencedProcedureStepSequence" },
{ 0x0072, 0x0302, 0, VR::US, VM::M1, "ImageBoxNumber" },
{ 0x0072, 0x0712, 0, VR::CS, VM::M1, "ShowGraphicAnnotationFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0894[] = {
{ 0x0022, 0x1310, 0, VR::SQ, VM::M1, "IntraocularLensCalculationsLeftEyeSequence" },
{ 0x0028, 0x9502, 0, VR::SQ, VM::M1, "RegionPixelShiftSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0895[] = {
{ 0x0028, 0x9503, 0, VR::SS, VM::M2T2N, "VerticesOfTheRegion" },
{ 0x0072, 0x0300, 0, VR::SQ, VM::M1, "ImageBoxesSequence" },
{ 0x0072, 0x0710, 0, VR::CS, VM::M1, "ShowImageTrueSizeFlag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0896[] = {
{ 0x0068, 0x6260, 0, VR::SQ, VM::M1, "InformationFromManufacturerSequence" },
{ 0x6008, 0x0200, 1, VR::US, VM::M1, "OverlayLocation5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0897[] = {
{ 0x300A, 0x0346, 0, VR::SH, VM::M1, "RangeModulatorID" },
{ 0xFFFE, 0xE000, 0, VR::XX, VM::M0, "Item" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0898[] = {
{ 0x600A, 0x0200, 1, VR::US, VM::M1, "OverlayLocation6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0899[] = {
{ 0x300A, 0x0344, 0, VR::IS, VM::M1, "RangeModulatorNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0900[] = {
{ 0x600C, 0x0200, 1, VR::US, VM::M1, "OverlayLocation7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0901[] = {
{ 0x0068, 0x6265, 0, VR::SQ, VM::M1, "NotificationFromManufacturerSequence" },
{ 0x300A, 0x0342, 0, VR::SQ, VM::M1, "RangeModulatorSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0902[] = {
{ 0x600E, 0x0200, 1, VR::US, VM::M1, "OverlayLocation8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0903[] = {
{ 0x300A, 0x0340, 0, VR::IS, VM::M1, "NumberOfRangeModulators" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0904[] = {
{ 0x6000, 0x0200, 1, VR::US, VM::M1, "OverlayLocation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0906[] = {
{ 0x6002, 0x0200, 1, VR::US, VM::M1, "OverlayLocation2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0907[] = {
{ 0x300A, 0x034C, 0, VR::SH, VM::M1, "BeamCurrentModulationID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0908[] = {
{ 0x6004, 0x0200, 1, VR::US, VM::M1, "OverlayLocation3" },
{ 0xFFFE, 0xE00D, 0, VR::XX, VM::M0, "ItemDelimitationItem" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0909[] = {
{ 0x300A, 0x034A, 0, VR::LO, VM::M1, "RangeModulatorDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0910[] = {
{ 0x6006, 0x0200, 1, VR::US, VM::M1, "OverlayLocation4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0911[] = {
{ 0x300A, 0x0348, 0, VR::CS, VM::M1, "RangeModulatorType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0912[] = {
{ 0x0068, 0x6270, 0, VR::DT, VM::M1, "InformationIssueDateTime" },
{ 0x6018, 0x0200, 1, VR::US, VM::M1, "OverlayLocation13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0913[] = {
{ 0x300A, 0x0356, 0, VR::FL, VM::M1, "FixationLightAzimuthalAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0914[] = {
{ 0x601A, 0x0200, 1, VR::US, VM::M1, "OverlayLocation14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0915[] = {
{ 0x300A, 0x0354, 0, VR::LO, VM::M1, "PatientSupportAccessoryCode" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0916[] = {
{ 0x601C, 0x0200, 1, VR::US, VM::M1, "OverlayLocation15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0917[] = {
{ 0x300A, 0x0352, 0, VR::SH, VM::M1, "PatientSupportID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0918[] = {
{ 0x601E, 0x0200, 1, VR::US, VM::M1, "OverlayLocation16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0919[] = {
{ 0x300A, 0x0350, 0, VR::CS, VM::M1, "PatientSupportType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0920[] = {
{ 0x6010, 0x0200, 1, VR::US, VM::M1, "OverlayLocation9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0922[] = {
{ 0x6012, 0x0200, 1, VR::US, VM::M1, "OverlayLocation10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0924[] = {
{ 0x6014, 0x0200, 1, VR::US, VM::M1, "OverlayLocation11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0925[] = {
{ 0x300A, 0x035A, 0, VR::FL, VM::M1, "MetersetRate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0926[] = {
{ 0x6016, 0x0200, 1, VR::US, VM::M1, "OverlayLocation12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0927[] = {
{ 0x300A, 0x0358, 0, VR::FL, VM::M1, "FixationLightPolarAngle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0929[] = {
{ 0x300A, 0x0366, 0, VR::FL, VM::M1, "RangeShifterWaterEquivalentThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0931[] = {
{ 0x0040, 0xA167, 1, VR::SQ, VM::M1, "ObservationCategoryCodeSequenceTrial" },
{ 0x300A, 0x0364, 0, VR::FL, VM::M1, "IsocenterToRangeShifterDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0932[] = {
{ 0x0040, 0xA160, 0, VR::UT, VM::M1, "TextValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0933[] = {
{ 0x0040, 0xA161, 0, VR::FD, VM::M1TN, "FloatingPointValue" },
{ 0x300A, 0x0362, 0, VR::LO, VM::M1, "RangeShifterSetting" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0934[] = {
{ 0x0040, 0xA162, 0, VR::SL, VM::M1TN, "RationalNumeratorValue" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0935[] = {
{ 0x0040, 0xA163, 0, VR::UL, VM::M1TN, "RationalDenominatorValue" },
{ 0x300A, 0x0360, 0, VR::SQ, VM::M1, "RangeShifterSettingsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0940[] = {
{ 0x0040, 0xA168, 0, VR::SQ, VM::M1, "ConceptCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0942[] = {
{ 0x0040, 0xA16A, 1, VR::ST, VM::M1, "BibliographicCitationTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0944[] = {
{ 0x0040, 0xA174, 1, VR::CS, VM::M1, "ReferencedObjectObservationClassTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0947[] = {
{ 0x300A, 0x0374, 0, VR::FL, VM::M1, "IsocenterToLateralSpreadingDeviceDistance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0948[] = {
{ 0x0040, 0xA170, 0, VR::SQ, VM::M1, "PurposeOfReferenceCodeSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0949[] = {
{ 0x0040, 0xA171, 0, VR::UI, VM::M1, "ObservationUID" },
{ 0x300A, 0x0372, 0, VR::LO, VM::M1, "LateralSpreadingDeviceSetting" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0950[] = {
{ 0x0040, 0xA172, 1, VR::UI, VM::M1, "ReferencedObservationUIDTrial" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0951[] = {
{ 0x0040, 0xA173, 1, VR::CS, VM::M1, "ReferencedObservationClassTrial" },
{ 0x300A, 0x0370, 0, VR::SQ, VM::M1, "LateralSpreadingDeviceSettingsSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0960[] = {
{ 0x0040, 0xE001, 0, VR::ST, VM::M1, "HL7InstanceIdentifier" },
{ 0x0068, 0x6221, 0, VR::LO, VM::M1, "ImplantTemplateVersion" },
{ 0x300A, 0x0306, 0, VR::SS, VM::M1, "RadiationChargeState" },
{ 0x5008, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup5" },
{ 0x5018, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence13" },
{ 0x6008, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray5" },
{ 0x600A, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0961[] = {
{ 0x6008, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed5" },
{ 0x600A, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0962[] = {
{ 0x0068, 0x6223, 0, VR::CS, VM::M1, "ImplantType" },
{ 0x300A, 0x0304, 0, VR::IS, VM::M1, "RadiationAtomicNumber" },
{ 0x500A, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup6" },
{ 0x501A, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence14" },
{ 0x6008, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen5" },
{ 0x600A, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0963[] = {
{ 0x0068, 0x6222, 0, VR::SQ, VM::M1, "ReplacedImplantTemplateSequence" },
{ 0x6008, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue5" },
{ 0x600A, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0964[] = {
{ 0x0068, 0x6225, 0, VR::SQ, VM::M1, "OriginalImplantTemplateSequence" },
{ 0x300A, 0x0302, 0, VR::IS, VM::M1, "RadiationMassNumber" },
{ 0x500C, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup7" },
{ 0x501C, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence15" },
{ 0x600C, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray7" },
{ 0x600E, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0965[] = {
{ 0x0040, 0xE004, 0, VR::DT, VM::M1, "HL7DocumentEffectiveTime" },
{ 0x0068, 0x6224, 0, VR::SQ, VM::M1, "DerivationImplantTemplateSequence" },
{ 0x600C, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed7" },
{ 0x600E, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0966[] = {
{ 0x0018, 0x9198, 0, VR::CS, VM::M1, "FirstOrderPhaseCorrection" },
{ 0x500E, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup8" },
{ 0x501E, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence16" },
{ 0x600C, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen7" },
{ 0x600E, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0967[] = {
{ 0x0018, 0x9199, 0, VR::CS, VM::M1, "WaterReferencedPhaseCorrection" },
{ 0x0040, 0xE006, 0, VR::SQ, VM::M1, "HL7DocumentTypeCodeSequence" },
{ 0x0068, 0x6226, 0, VR::DT, VM::M1, "EffectiveDateTime" },
{ 0x600C, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue7" },
{ 0x600E, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0968[] = {
{ 0x0018, 0x9196, 1, VR::FD, VM::M1, "ChemicalShiftMaximumIntegrationLimitInHz" },
{ 0x5000, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup" },
{ 0x5010, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence9" },
{ 0x6000, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray" },
{ 0x6002, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0969[] = {
{ 0x0018, 0x9197, 0, VR::SQ, VM::M1, "MRVelocityEncodingSequence" },
{ 0x0040, 0xE008, 0, VR::SQ, VM::M1, "DocumentClassCodeSequence" },
{ 0x300A, 0x030F, 0, VR::SH, VM::M1, "SnoutID" },
{ 0x6000, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed" },
{ 0x6002, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0970[] = {
{ 0x300A, 0x030C, 0, VR::SQ, VM::M1, "SnoutSequence" },
{ 0x5002, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup2" },
{ 0x5012, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence10" },
{ 0x6000, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen" },
{ 0x6002, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0971[] = {
{ 0x0018, 0x9195, 1, VR::FD, VM::M1, "ChemicalShiftMinimumIntegrationLimitInHz" },
{ 0x300A, 0x030D, 0, VR::FL, VM::M1, "SnoutPosition" },
{ 0x6000, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue" },
{ 0x6002, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0972[] = {
{ 0x300A, 0x030A, 0, VR::FL, VM::M2, "VirtualSourceAxisDistances" },
{ 0x5004, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup3" },
{ 0x5014, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence11" },
{ 0x6004, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray3" },
{ 0x6006, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0973[] = {
{ 0x6004, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed3" },
{ 0x6006, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0974[] = {
{ 0x300A, 0x0308, 0, VR::CS, VM::M1, "ScanMode" },
{ 0x5006, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup4" },
{ 0x5016, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence12" },
{ 0x6004, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen3" },
{ 0x6006, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0975[] = {
{ 0x6004, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue3" },
{ 0x6006, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0976[] = {
{ 0x0040, 0xE011, 0, VR::UI, VM::M1, "RetrieveLocationUID" },
{ 0x300A, 0x0316, 0, VR::IS, VM::M1, "RangeShifterNumber" },
{ 0x5008, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence5" },
{ 0x5018, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup13" },
{ 0x6018, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray13" },
{ 0x601A, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0977[] = {
{ 0x0040, 0xA504, 0, VR::SQ, VM::M1, "ContentTemplateSequence" },
{ 0x0040, 0xE010, 0, VR::UT, VM::M1, "RetrieveURI" },
{ 0x0068, 0x6230, 0, VR::SQ, VM::M1, "ImplantTargetAnatomySequence" },
{ 0x0068, 0x6620, 0, VR::FD, VM::M3, "ThreeDPlaneNormal" },
{ 0x6018, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed13" },
{ 0x601A, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0978[] = {
{ 0x300A, 0x0314, 0, VR::SQ, VM::M1, "RangeShifterSequence" },
{ 0x500A, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence6" },
{ 0x501A, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup14" },
{ 0x6018, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen13" },
{ 0x601A, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0979[] = {
{ 0x6018, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue13" },
{ 0x601A, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0980[] = {
{ 0x300A, 0x0312, 0, VR::IS, VM::M1, "NumberOfRangeShifters" },
{ 0x500C, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence7" },
{ 0x501C, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup15" },
{ 0x601C, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray15" },
{ 0x601E, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0981[] = {
{ 0x0040, 0xA110, 1, VR::DA, VM::M1, "DateOfDocumentOrVerbalTransactionTrial" },
{ 0x601C, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed15" },
{ 0x601E, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0982[] = {
{ 0x500E, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence8" },
{ 0x501E, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup16" },
{ 0x601C, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen15" },
{ 0x601E, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0983[] = {
{ 0x0040, 0xA112, 1, VR::TM, VM::M1, "TimeOfDocumentCreationOrVerbalTransactionTrial" },
{ 0x601C, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue15" },
{ 0x601E, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0984[] = {
{ 0x0018, 0x9186, 0, VR::SH, VM::M1, "RespiratorySignalSourceID" },
{ 0x5000, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence" },
{ 0x5010, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup9" },
{ 0x6010, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray9" },
{ 0x6012, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0985[] = {
{ 0x6010, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed9" },
{ 0x6012, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0986[] = {
{ 0x0018, 0x9184, 0, VR::FD, VM::M1, "TaggingDelay" },
{ 0x5002, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence2" },
{ 0x5012, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup10" },
{ 0x6010, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen9" },
{ 0x6012, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0987[] = {
{ 0x0018, 0x9185, 0, VR::ST, VM::M1, "RespiratoryMotionCompensationTechniqueDescription" },
{ 0x6010, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue9" },
{ 0x6012, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0988[] = {
{ 0x0018, 0x9182, 0, VR::FD, VM::M1, "GradientOutput" },
{ 0x5004, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence3" },
{ 0x5014, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup11" },
{ 0x6014, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray11" },
{ 0x6016, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0989[] = {
{ 0x0018, 0x9183, 0, VR::CS, VM::M1, "FlowCompensationDirection" },
{ 0x6014, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed11" },
{ 0x6016, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0990[] = {
{ 0x0018, 0x9180, 0, VR::CS, VM::M1, "GradientOutputType" },
{ 0x300A, 0x0318, 0, VR::SH, VM::M1, "RangeShifterID" },
{ 0x5006, 0x2600, 1, VR::SQ, VM::M1, "CurveReferencedOverlaySequence4" },
{ 0x5016, 0x2610, 1, VR::US, VM::M1, "CurveReferencedOverlayGroup12" },
{ 0x6014, 0x1202, 1, VR::US, VM::M1TN, "OverlaysGreen11" },
{ 0x6016, 0x1200, 1, VR::US, VM::M1TN, "OverlaysGray12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0991[] = {
{ 0x0018, 0x9181, 0, VR::FD, VM::M1, "SpecificAbsorptionRateValue" },
{ 0x6014, 0x1203, 1, VR::US, VM::M1TN, "OverlaysBlue11" },
{ 0x6016, 0x1201, 1, VR::US, VM::M1TN, "OverlaysRed12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0992[] = {
{ 0x0040, 0xA125, 1, VR::CS, VM::M2, "ReportStatusIDTrial" },
{ 0x0040, 0xE021, 0, VR::SQ, VM::M1, "DICOMRetrievalSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0993[] = {
{ 0x0040, 0xA124, 0, VR::UI, VM::M1, "UID" },
{ 0x0040, 0xE020, 0, VR::CS, VM::M1, "TypeOfInstances" },
{ 0x0068, 0x6610, 0, VR::FD, VM::M3, "ThreeDPlaneOrigin" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0994[] = {
{ 0x0040, 0xE023, 0, VR::SQ, VM::M1, "WADORetrievalSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0995[] = {
{ 0x0040, 0xE022, 0, VR::SQ, VM::M1, "DICOMMediaRetrievalSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0996[] = {
{ 0x0040, 0xA121, 0, VR::DA, VM::M1, "Date" },
{ 0x300A, 0x0322, 0, VR::LO, VM::M1, "RangeShifterDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0997[] = {
{ 0x0040, 0xA120, 0, VR::DT, VM::M1, "DateTime" },
{ 0x0040, 0xE024, 0, VR::SQ, VM::M1, "XDSRetrievalSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0998[] = {
{ 0x0040, 0xA123, 0, VR::PN, VM::M1, "PersonName" },
{ 0x300A, 0x0320, 0, VR::CS, VM::M1, "RangeShifterType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0999[] = {
{ 0x0040, 0xA122, 0, VR::TM, VM::M1, "Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1003[] = {
{ 0x2010, 0x0376, 0, VR::DS, VM::M2, "PrinterPixelSpacing" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1008[] = {
{ 0x0040, 0xA525, 0, VR::SQ, VM::M1, "IdenticalDocumentsSequence" },
{ 0x0040, 0xE031, 0, VR::UI, VM::M1, "HomeCommunityID" },
{ 0x300A, 0x0336, 0, VR::SH, VM::M1, "LateralSpreadingDeviceID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1009[] = {
{ 0x0040, 0xE030, 0, VR::UI, VM::M1, "RepositoryUniqueID" },
{ 0x0068, 0x6210, 0, VR::LO, VM::M1, "ImplantSize" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1010[] = {
{ 0x300A, 0x0334, 0, VR::IS, VM::M1, "LateralSpreadingDeviceNumber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1011[] = {
{ 0x0040, 0xA136, 0, VR::US, VM::M1TN, "ReferencedFrameNumbers" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1012[] = {
{ 0x300A, 0x0332, 0, VR::SQ, VM::M1, "LateralSpreadingDeviceSequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1013[] = {
{ 0x0040, 0xA130, 0, VR::CS, VM::M1, "TemporalRangeType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1014[] = {
{ 0x300A, 0x0330, 0, VR::IS, VM::M1, "NumberOfLateralSpreadingDevices" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1015[] = {
{ 0x0040, 0xA132, 0, VR::UL, VM::M1TN, "ReferencedSamplePositions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1018[] = {
{ 0x300A, 0x033C, 0, VR::FL, VM::M1, "LateralSpreadingDeviceWaterEquivalentThickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1020[] = {
{ 0x300A, 0x033A, 0, VR::LO, VM::M1, "LateralSpreadingDeviceDescription" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1021[] = {
{ 0x0040, 0xA138, 0, VR::DS, VM::M1TN, "ReferencedTimeOffsets" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1022[] = {
{ 0x300A, 0x0338, 0, VR::CS, VM::M1, "LateralSpreadingDeviceType" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1023[] = {
{ 0x0040, 0xA13A, 0, VR::DT, VM::M1TN, "ReferencedDateTime" },
{ 0, 0, 0, 0, 0, NULL }
};

}

DictEntry *vtkDICOMDictionary::DictHashTable[1024] = {
DictRow0000,
DictRow0001,
DictRow0002,
DictRow0003,
DictRow0004,
DictRow0005,
DictRow0006,
DictRow0007,
DictRow0008,
DictRow0009,
DictRow0010,
DictRow0011,
DictRow0012,
DictRow0013,
DictRow0014,
DictRow0015,
DictRow0016,
DictRow0017,
DictRow0018,
DictRow0019,
DictRow0020,
DictRow0021,
DictRow0022,
DictRow0023,
DictRow0024,
DictRow0025,
DictRow0026,
DictRow0027,
DictRow0028,
DictRow0029,
DictRow0030,
DictRow0031,
DictRow0032,
DictRow0033,
DictRow0034,
DictRow0035,
DictRow0036,
DictRow0037,
DictRow0038,
DictRow0039,
DictRow0040,
DictRow0041,
DictRow0042,
DictRow0043,
DictRow0044,
DictRow0045,
DictRow0046,
DictRow0047,
DictRow0048,
DictRow0049,
DictRow0050,
DictRow0051,
DictRow0052,
DictRow0053,
DictRow0054,
DictRow0055,
DictRow0056,
DictRow0057,
DictRow0058,
DictRow0059,
DictRow0060,
DictRow0061,
DictRow0062,
DictRow0063,
DictRow0064,
DictRow0065,
DictRow0066,
DictRow0067,
DictRow0068,
DictRow0069,
DictRow0070,
DictRow0071,
DictRow0072,
DictRow0073,
DictRow0074,
DictRow0075,
DictRow0076,
DictRow0077,
DictRow0078,
DictRow0079,
DictRow0080,
DictRow0081,
DictRow0082,
DictRow0083,
DictRow0084,
DictRow0085,
DictRow0086,
DictRow0087,
DictRow0088,
DictRow0089,
DictRow0090,
DictRow0091,
DictRow0092,
DictRow0093,
DictRow0094,
DictRow0095,
DictRow0096,
DictRow0097,
DictRow0098,
DictRow0099,
DictRow0100,
DictRow0101,
DictRow0102,
DictRow0103,
DictRow0104,
DictRow0105,
DictRow0106,
DictRow0107,
DictRow0108,
DictRow0109,
DictRow0110,
DictRow0111,
DictRow0112,
DictRow0113,
DictRow0114,
DictRow0115,
DictRow0116,
DictRow0117,
DictRow0118,
DictRow0119,
DictRow0120,
DictRow0121,
DictRow0122,
DictRow0123,
DictRow0124,
DictRow0125,
DictRow0126,
DictRow0127,
DictRow0128,
DictRow0129,
DictRow0130,
DictRow0131,
DictRow0132,
DictRow0133,
DictRow0134,
DictRow0135,
DictRow0136,
DictRow0137,
DictRow0138,
DictRow0139,
DictRow0140,
DictRow0141,
DictRow0142,
DictRow0143,
DictRow0144,
DictRow0145,
DictRow0146,
DictRow0147,
DictRow0148,
DictRow0149,
DictRow0150,
DictRow0151,
DictRow0152,
DictRow0153,
DictRow0154,
DictRow0155,
DictRow0156,
DictRow0157,
DictRow0158,
DictRow0159,
DictRow0160,
DictRow0161,
DictRow0162,
DictRow0163,
DictRow0164,
DictRow0165,
DictRow0166,
DictRow0167,
DictRow0168,
DictRow0169,
DictRow0170,
DictRow0171,
DictRow0172,
DictRow0173,
DictRow0174,
DictRow0175,
DictRow0176,
DictRow0177,
DictRow0178,
DictRow0179,
DictRow0180,
DictRow0181,
DictRow0182,
DictRow0183,
DictRow0184,
DictRow0185,
DictRow0186,
DictRow0187,
DictRow0188,
DictRow0189,
DictRow0190,
DictRow0191,
DictRow0192,
DictRow0193,
DictRow0194,
DictRow0195,
DictRow0196,
DictRow0197,
DictRow0198,
DictRow0199,
DictRow0200,
DictRow0201,
DictRow0202,
DictRow0203,
DictRow0204,
DictRow0205,
DictRow0206,
DictRow0207,
DictRow0208,
DictRow0209,
DictRow0210,
DictRow0211,
DictRow0212,
DictRow0213,
DictRow0214,
DictRow0215,
DictRow0216,
DictRow0217,
DictRow0218,
DictRow0219,
DictRow0220,
DictRow0221,
DictRow0222,
DictRow0223,
DictRow0224,
DictRow0225,
DictRow0226,
DictRow0227,
DictRow0228,
DictRow0229,
DictRow0230,
DictRow0231,
DictRow0232,
DictRow0233,
DictRow0234,
DictRow0235,
DictRow0236,
DictRow0237,
DictRow0238,
DictRow0239,
DictRow0240,
DictRow0241,
DictRow0242,
DictRow0243,
DictRow0244,
DictRow0245,
DictRow0246,
DictRow0247,
DictRow0248,
DictRow0249,
DictRow0250,
DictRow0251,
DictRow0252,
DictRow0253,
DictRow0254,
DictRow0255,
DictRow0256,
DictRow0257,
DictRow0258,
DictRow0259,
DictRow0260,
DictRow0261,
DictRow0262,
DictRow0263,
DictRow0264,
DictRow0265,
DictRow0266,
DictRow0267,
DictRow0268,
DictRow0269,
DictRow0270,
DictRow0271,
DictRow0272,
DictRow0273,
DictRow0274,
DictRow0275,
DictRow0276,
DictRow0277,
DictRow0278,
DictRow0279,
DictRow0280,
DictRow0281,
DictRow0282,
DictRow0283,
DictRow0284,
DictRow0285,
DictRow0286,
DictRow0287,
DictRow0288,
DictRow0289,
DictRow0290,
DictRow0291,
DictRow0292,
DictRow0293,
DictRow0294,
DictRow0295,
DictRow0296,
DictRow0297,
DictRow0298,
DictRow0299,
DictRow0300,
DictRow0301,
DictRow0302,
DictRow0303,
DictRow0304,
DictRow0305,
DictRow0306,
DictRow0307,
DictRow0308,
DictRow0309,
DictRow0310,
DictRow0311,
DictRow0312,
DictRow0313,
DictRow0314,
DictRow0315,
DictRow0316,
DictRow0317,
DictRow0318,
DictRow0319,
DictRow0320,
DictRow0321,
DictRow0322,
DictRow0323,
DictRow0324,
DictRow0325,
DictRow0326,
DictRow0327,
DictRow0328,
DictRow0329,
DictRow0330,
DictRow0331,
DictRow0332,
DictRow0333,
DictRow0334,
DictRow0335,
DictRow0336,
DictRow0337,
DictRow0338,
DictRow0339,
DictRow0340,
DictRow0341,
DictRow0342,
DictRow0343,
DictRow0344,
DictRow0345,
DictRow0346,
DictRow0347,
DictRow0348,
DictRow0349,
DictRow0350,
DictRow0351,
DictRow0352,
DictRow0353,
DictRow0354,
DictRow0355,
DictRow0356,
DictRow0357,
DictRow0358,
DictRow0359,
DictRow0360,
DictRow0361,
DictRow0362,
DictRow0363,
DictRow0364,
DictRow0365,
DictRow0366,
DictRow0367,
DictRow0368,
DictRow0369,
DictRow0370,
DictRow0371,
DictRow0372,
DictRow0373,
DictRow0374,
DictRow0375,
DictRow0376,
DictRow0377,
DictRow0378,
DictRow0379,
DictRow0380,
DictRow0381,
DictRow0382,
DictRow0383,
DictRow0384,
DictRow0385,
DictRow0386,
DictRow0387,
DictRow0388,
DictRow0389,
DictRow0390,
DictRow0391,
DictRow0392,
DictRow0393,
DictRow0394,
DictRow0395,
DictRow0396,
DictRow0397,
DictRow0398,
DictRow0399,
DictRow0400,
DictRow0401,
DictRow0402,
DictRow0403,
DictRow0404,
DictRow0405,
DictRow0406,
DictRow0407,
DictRow0408,
DictRow0409,
DictRow0410,
DictRow0411,
DictRow0412,
DictRow0413,
DictRow0414,
DictRow0415,
DictRow0416,
DictRow0417,
DictRow0418,
DictRow0419,
DictRow0420,
DictRow0421,
DictRow0422,
DictRow0423,
DictRow0424,
DictRow0425,
DictRow0426,
DictRow0427,
DictRow0428,
DictRow0429,
DictRow0430,
DictRow0431,
DictRow0432,
DictRow0433,
DictRow0434,
DictRow0435,
DictRow0436,
DictRow0437,
DictRow0438,
DictRow0439,
DictRow0440,
DictRow0441,
DictRow0442,
DictRow0443,
DictRow0444,
DictRow0445,
DictRow0446,
DictRow0447,
DictRow0448,
DictRow0449,
DictRow0450,
DictRow0451,
DictRow0452,
DictRow0453,
DictRow0454,
DictRow0455,
DictRow0456,
DictRow0457,
DictRow0458,
DictRow0459,
DictRow0460,
DictRow0461,
DictRow0462,
DictRow0463,
DictRow0464,
DictRow0465,
DictRow0466,
DictRow0467,
DictRow0468,
DictRow0469,
DictRow0470,
DictRow0471,
DictRow0472,
DictRow0473,
DictRow0474,
DictRow0475,
DictRow0476,
DictRow0477,
DictRow0478,
DictRow0479,
DictRow0480,
DictRow0481,
DictRow0482,
DictRow0483,
DictRow0484,
DictRow0485,
DictRow0486,
DictRow0487,
DictRow0488,
DictRow0489,
DictRow0490,
DictRow0491,
DictRow0492,
DictRow0493,
DictRow0494,
DictRow0495,
DictRow0496,
DictRow0497,
DictRow0498,
DictRow0499,
DictRow0500,
DictRow0501,
DictRow0502,
DictRow0503,
DictRow0504,
DictRow0505,
DictRow0506,
DictRow0507,
DictRow0508,
DictRow0509,
DictRow0510,
DictRow0511,
DictRow0512,
DictRow0513,
DictRow0514,
DictRow0515,
DictRow0516,
DictRow0517,
DictRow0518,
DictRow0519,
DictRow0520,
DictRow0521,
DictRow0522,
DictRow0523,
DictRow0524,
DictRow0525,
DictRow0526,
DictRow0527,
DictRow0528,
DictRow0529,
DictRow0530,
DictRow0531,
DictEmptyRow,
DictRow0533,
DictRow0534,
DictRow0535,
DictRow0536,
DictRow0537,
DictRow0538,
DictRow0539,
DictRow0540,
DictRow0541,
DictRow0542,
DictRow0543,
DictRow0544,
DictRow0545,
DictRow0546,
DictRow0547,
DictRow0548,
DictRow0549,
DictRow0550,
DictRow0551,
DictRow0552,
DictRow0553,
DictRow0554,
DictRow0555,
DictRow0556,
DictRow0557,
DictRow0558,
DictRow0559,
DictRow0560,
DictRow0561,
DictRow0562,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictRow0566,
DictRow0567,
DictRow0568,
DictRow0569,
DictRow0570,
DictRow0571,
DictRow0572,
DictRow0573,
DictRow0574,
DictRow0575,
DictRow0576,
DictRow0577,
DictRow0578,
DictRow0579,
DictRow0580,
DictRow0581,
DictRow0582,
DictRow0583,
DictRow0584,
DictRow0585,
DictRow0586,
DictRow0587,
DictRow0588,
DictRow0589,
DictRow0590,
DictRow0591,
DictRow0592,
DictRow0593,
DictRow0594,
DictRow0595,
DictRow0596,
DictEmptyRow,
DictRow0598,
DictRow0599,
DictRow0600,
DictRow0601,
DictRow0602,
DictRow0603,
DictRow0604,
DictRow0605,
DictRow0606,
DictRow0607,
DictRow0608,
DictRow0609,
DictRow0610,
DictRow0611,
DictRow0612,
DictEmptyRow,
DictEmptyRow,
DictRow0615,
DictRow0616,
DictRow0617,
DictRow0618,
DictRow0619,
DictRow0620,
DictRow0621,
DictRow0622,
DictRow0623,
DictRow0624,
DictRow0625,
DictRow0626,
DictRow0627,
DictRow0628,
DictRow0629,
DictRow0630,
DictRow0631,
DictRow0632,
DictRow0633,
DictRow0634,
DictRow0635,
DictRow0636,
DictRow0637,
DictRow0638,
DictRow0639,
DictRow0640,
DictRow0641,
DictRow0642,
DictRow0643,
DictRow0644,
DictRow0645,
DictRow0646,
DictRow0647,
DictRow0648,
DictRow0649,
DictRow0650,
DictRow0651,
DictRow0652,
DictRow0653,
DictRow0654,
DictRow0655,
DictRow0656,
DictRow0657,
DictRow0658,
DictRow0659,
DictRow0660,
DictRow0661,
DictRow0662,
DictRow0663,
DictRow0664,
DictRow0665,
DictRow0666,
DictRow0667,
DictEmptyRow,
DictEmptyRow,
DictRow0670,
DictEmptyRow,
DictRow0672,
DictRow0673,
DictRow0674,
DictRow0675,
DictRow0676,
DictRow0677,
DictRow0678,
DictRow0679,
DictRow0680,
DictRow0681,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictRow0687,
DictRow0688,
DictEmptyRow,
DictEmptyRow,
DictRow0691,
DictRow0692,
DictRow0693,
DictRow0694,
DictEmptyRow,
DictRow0696,
DictEmptyRow,
DictRow0698,
DictEmptyRow,
DictRow0700,
DictRow0701,
DictRow0702,
DictEmptyRow,
DictRow0704,
DictRow0705,
DictRow0706,
DictRow0707,
DictRow0708,
DictRow0709,
DictRow0710,
DictRow0711,
DictRow0712,
DictRow0713,
DictRow0714,
DictRow0715,
DictRow0716,
DictRow0717,
DictRow0718,
DictRow0719,
DictRow0720,
DictRow0721,
DictRow0722,
DictRow0723,
DictRow0724,
DictRow0725,
DictRow0726,
DictRow0727,
DictRow0728,
DictRow0729,
DictRow0730,
DictRow0731,
DictRow0732,
DictRow0733,
DictRow0734,
DictRow0735,
DictRow0736,
DictRow0737,
DictRow0738,
DictRow0739,
DictRow0740,
DictRow0741,
DictRow0742,
DictRow0743,
DictRow0744,
DictRow0745,
DictRow0746,
DictRow0747,
DictRow0748,
DictRow0749,
DictRow0750,
DictRow0751,
DictRow0752,
DictRow0753,
DictRow0754,
DictRow0755,
DictRow0756,
DictRow0757,
DictRow0758,
DictEmptyRow,
DictEmptyRow,
DictRow0761,
DictRow0762,
DictEmptyRow,
DictRow0764,
DictEmptyRow,
DictRow0766,
DictRow0767,
DictRow0768,
DictRow0769,
DictRow0770,
DictRow0771,
DictRow0772,
DictEmptyRow,
DictRow0774,
DictRow0775,
DictRow0776,
DictRow0777,
DictEmptyRow,
DictEmptyRow,
DictRow0780,
DictRow0781,
DictEmptyRow,
DictRow0783,
DictRow0784,
DictEmptyRow,
DictRow0786,
DictEmptyRow,
DictRow0788,
DictRow0789,
DictRow0790,
DictRow0791,
DictEmptyRow,
DictRow0793,
DictRow0794,
DictEmptyRow,
DictEmptyRow,
DictRow0797,
DictEmptyRow,
DictEmptyRow,
DictRow0800,
DictRow0801,
DictRow0802,
DictEmptyRow,
DictRow0804,
DictRow0805,
DictRow0806,
DictRow0807,
DictRow0808,
DictRow0809,
DictRow0810,
DictRow0811,
DictRow0812,
DictRow0813,
DictRow0814,
DictRow0815,
DictRow0816,
DictRow0817,
DictRow0818,
DictRow0819,
DictRow0820,
DictRow0821,
DictRow0822,
DictRow0823,
DictRow0824,
DictRow0825,
DictRow0826,
DictRow0827,
DictEmptyRow,
DictRow0829,
DictEmptyRow,
DictRow0831,
DictRow0832,
DictRow0833,
DictRow0834,
DictRow0835,
DictRow0836,
DictRow0837,
DictRow0838,
DictRow0839,
DictRow0840,
DictRow0841,
DictRow0842,
DictRow0843,
DictRow0844,
DictRow0845,
DictRow0846,
DictRow0847,
DictRow0848,
DictRow0849,
DictRow0850,
DictRow0851,
DictRow0852,
DictRow0853,
DictRow0854,
DictEmptyRow,
DictRow0856,
DictRow0857,
DictRow0858,
DictRow0859,
DictRow0860,
DictRow0861,
DictRow0862,
DictRow0863,
DictRow0864,
DictRow0865,
DictRow0866,
DictRow0867,
DictRow0868,
DictRow0869,
DictRow0870,
DictRow0871,
DictRow0872,
DictRow0873,
DictRow0874,
DictRow0875,
DictRow0876,
DictRow0877,
DictRow0878,
DictRow0879,
DictRow0880,
DictRow0881,
DictRow0882,
DictEmptyRow,
DictRow0884,
DictRow0885,
DictEmptyRow,
DictRow0887,
DictRow0888,
DictRow0889,
DictRow0890,
DictRow0891,
DictRow0892,
DictRow0893,
DictRow0894,
DictRow0895,
DictRow0896,
DictRow0897,
DictRow0898,
DictRow0899,
DictRow0900,
DictRow0901,
DictRow0902,
DictRow0903,
DictRow0904,
DictEmptyRow,
DictRow0906,
DictRow0907,
DictRow0908,
DictRow0909,
DictRow0910,
DictRow0911,
DictRow0912,
DictRow0913,
DictRow0914,
DictRow0915,
DictRow0916,
DictRow0917,
DictRow0918,
DictRow0919,
DictRow0920,
DictEmptyRow,
DictRow0922,
DictEmptyRow,
DictRow0924,
DictRow0925,
DictRow0926,
DictRow0927,
DictEmptyRow,
DictRow0929,
DictEmptyRow,
DictRow0931,
DictRow0932,
DictRow0933,
DictRow0934,
DictRow0935,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictRow0940,
DictEmptyRow,
DictRow0942,
DictEmptyRow,
DictRow0944,
DictEmptyRow,
DictEmptyRow,
DictRow0947,
DictRow0948,
DictRow0949,
DictRow0950,
DictRow0951,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictRow0960,
DictRow0961,
DictRow0962,
DictRow0963,
DictRow0964,
DictRow0965,
DictRow0966,
DictRow0967,
DictRow0968,
DictRow0969,
DictRow0970,
DictRow0971,
DictRow0972,
DictRow0973,
DictRow0974,
DictRow0975,
DictRow0976,
DictRow0977,
DictRow0978,
DictRow0979,
DictRow0980,
DictRow0981,
DictRow0982,
DictRow0983,
DictRow0984,
DictRow0985,
DictRow0986,
DictRow0987,
DictRow0988,
DictRow0989,
DictRow0990,
DictRow0991,
DictRow0992,
DictRow0993,
DictRow0994,
DictRow0995,
DictRow0996,
DictRow0997,
DictRow0998,
DictRow0999,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictRow1003,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictEmptyRow,
DictRow1008,
DictRow1009,
DictRow1010,
DictRow1011,
DictRow1012,
DictRow1013,
DictRow1014,
DictRow1015,
DictEmptyRow,
DictEmptyRow,
DictRow1018,
DictEmptyRow,
DictRow1020,
DictRow1021,
DictRow1022,
DictRow1023,
};
