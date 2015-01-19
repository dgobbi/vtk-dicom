/*=========================================================================
This is an automatically generated file.  Include errata for any changes.
=========================================================================*/

#include "vtkDICOMDictionary.h"
#include "vtkDICOMDictPrivate.h"

namespace {

typedef vtkDICOMVR VR;
typedef vtkDICOMVM VM;
typedef vtkDICOMDictEntry::Entry DictEntry;

// ----- WG12 Supplement 43 -----

DictEntry Dict001Contents[] = {
{ 0x0009, 0x0001, 0, VR::SQ, VM::M1, "EventTimerSequence" },
{ 0x0009, 0x0002, 0, VR::FD, VM::M1, "EventTimeInterval" },
{ 0x0009, 0x0003, 0, VR::SQ, VM::M1, "EventCodeSequence" },
{ 0x0019, 0x0001, 0, VR::FD, VM::M1, "FocusDepth" },
{ 0x0019, 0x0003, 0, VR::SQ, VM::M1, "ExcludedIntervalsSequence" },
{ 0x0019, 0x0004, 0, VR::DT, VM::M1, "ExclusionStartDatetime" },
{ 0x0019, 0x0005, 0, VR::FD, VM::M1, "ExclusionDuration" },
{ 0x0019, 0x0006, 0, VR::SQ, VM::M1, "USImageDescriptionSequence" },
{ 0x0019, 0x0007, 0, VR::SQ, VM::M1, "ImageDataTypeSequence" },
{ 0x0019, 0x0008, 0, VR::CS, VM::M1, "DataType" },
{ 0x0019, 0x0009, 0, VR::SQ, VM::M1, "TransducerScanGeometryCodeSequence" },
{ 0x0019, 0x000B, 0, VR::CS, VM::M1, "AliasedDataType" },
{ 0x0019, 0x000C, 0, VR::CS, VM::M1, "PositionMeasuringDeviceUsed" },
{ 0x0019, 0x000D, 0, VR::SQ, VM::M1, "TransducerScanningConfigurationCodeSequence" },
{ 0x0019, 0x000E, 0, VR::SQ, VM::M1, "TransducerBeamSteeringCodeSequence" },
{ 0x0019, 0x000F, 0, VR::SQ, VM::M1, "TransducerAccessCodeSequence" },
{ 0x0021, 0x0001, 0, VR::FD, VM::M1, "ImagePositionVolume" },
{ 0x0021, 0x0002, 0, VR::FD, VM::M1, "ImageOrientationVolume" },
{ 0x0021, 0x0007, 0, VR::CS, VM::M1, "UltrasoundAcquisitionGeometry" },
{ 0x0021, 0x0008, 0, VR::FD, VM::M1, "ApexPosition" },
{ 0x0021, 0x0009, 0, VR::FD, VM::M1, "VolumeToTransducerMappingMatrix" },
{ 0x0021, 0x000A, 0, VR::FD, VM::M1, "VolumeToTableMappingMatrix" },
{ 0x0021, 0x000C, 0, VR::CS, VM::M1, "PatientFrameOfReferenceSource" },
{ 0x0021, 0x000D, 0, VR::FD, VM::M1, "TemporalPositionTimeOffset" },
{ 0x0021, 0x000E, 0, VR::SQ, VM::M1, "PlanePositionVolumeSequence" },
{ 0x0021, 0x000F, 0, VR::SQ, VM::M1, "PlaneOrientationVolumeSequence" },
{ 0x0021, 0x0010, 0, VR::SQ, VM::M1, "TemporalPositionSequence" },
{ 0x0021, 0x0011, 0, VR::CS, VM::M1, "DimensionOrganizationType" },
{ 0x0029, 0x0001, 0, VR::SQ, VM::M1, "DataFrameAssignmentSequence" },
{ 0x0029, 0x0002, 0, VR::CS, VM::M1, "DataPathAssignment" },
{ 0x0029, 0x0003, 0, VR::US, VM::M1, "BitsMappedToColorLookupTable" },
{ 0x0029, 0x0004, 0, VR::SQ, VM::M1, "Opacity1LUTSequence" },
{ 0x0029, 0x0005, 0, VR::CS, VM::M1, "Opacity1LUTTransferFunction" },
{ 0x0029, 0x0006, 0, VR::FD, VM::M1, "OpacityConstant" },
{ 0x0029, 0x0007, 0, VR::US, VM::M1, "OpacityLookupTableDescriptor" },
{ 0x0029, 0x0008, 0, VR::OW, VM::M1, "OpacityLookupTableData" },
{ 0x0029, 0x000B, 0, VR::SQ, VM::M1, "EnhancedPaletteColorLookupTableSequence" },
{ 0x0029, 0x000C, 0, VR::SQ, VM::M1, "Opacity2LUTSequence" },
{ 0x0029, 0x000D, 0, VR::CS, VM::M1, "Opacity2LUTTransferFunction" },
{ 0x0029, 0x000E, 0, VR::CS, VM::M1, "DataPathID" },
{ 0x0029, 0x000F, 0, VR::CS, VM::M1, "RGBLUTTransferFunction" },
{ 0x0029, 0x0010, 0, VR::CS, VM::M1, "AlphaLUTTransferFunction" },
{ 0x0041, 0x0001, 0, VR::CS, VM::M1, "PerformedProtocolType" },
};

unsigned short Dict001TagHashTable[] = {
   11,    22,    31,    38,    47,    56,    65,    76,    87,   100,
    0,     5,     2,     3,     8,     7,    13,    13,    20,     9,
   28,     1,     4,     1,     2,     7,     6,    12,    12,    19,
    8,     3,    15,    15,    16,     1,    30,     3,     4,    14,
   14,    21,    10,    29,     2,    35,     8,     4,     3,     1,
   23,    13,    32,     5,    36,    11,     4,    17,     2,    22,
   12,    31,     4,    42,     1,     5,     4,     3,    10,     9,
   25,    15,    34,     7,    38,    13,     5,     9,     8,    24,
   14,    33,     6,    37,    12,    41,    16,     6,     0,     1,
    6,     5,    11,    11,    18,     7,    27,    17,    40,    15,
    3,     5,     4,    26,    16,    39,    14,
};

vtkDICOMDictionary::Dict Dict001Data = {
"WG12 Supplement 43",
10,
43,
Dict001TagHashTable,
Dict001Contents
};

// ----- SVISION -----

DictEntry Dict002Contents[] = {
{ 0x0017, 0x0000, 0, VR::LO, VM::M1, "ExtendedBodyPart" },
{ 0x0017, 0x0010, 0, VR::LO, VM::M1, "ExtendedViewPosition" },
{ 0x0017, 0x0020, 0, VR::SQ, VM::M1, "ScheduledProcedureStepList" },
{ 0x0017, 0x00a0, 0, VR::IS, VM::M1, "FixedGridSystem" },
{ 0x0017, 0x00f0, 0, VR::IS, VM::M1, "ImagesSOPClass" },
{ 0x0019, 0x0000, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0016, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0018, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0028, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0030, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0034, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0038, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0041, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0068, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0069, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0070, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0074, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0075, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0079, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0081, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0091, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0092, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0093, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0094, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00a0, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a1, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a8, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00b0, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00b1, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00f0, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0000, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0001, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0003, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0011, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0030, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0031, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0040, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0041, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0050, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0051, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0052, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0060, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0090, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0091, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0092, 0, VR::DS, VM::M1, "" },
{ 0x0023, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0023, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0023, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0023, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x0023, 0x00f0, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0000, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0003, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0004, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0005, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0006, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0007, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0008, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0009, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x000a, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0025, 0x0021, 0, VR::LO, VM::M1, "" },
{ 0x0027, 0x0000, 0, VR::IS, VM::M1, "" },
{ 0x0027, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0027, 0x0010, 0, VR::DT, VM::M1, "" },
{ 0x0027, 0x0011, 0, VR::DT, VM::M1, "" },
{ 0x0027, 0x0012, 0, VR::DT, VM::M1, "" },
{ 0x0027, 0x0013, 0, VR::DT, VM::M1, "" },
{ 0x0029, 0x0000, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0003, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0004, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0005, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict002TagHashTable[] = {
   23,    32,    51,    60,    73,    82,    95,   100,   105,   114,
  123,   138,   155,   162,   171,   176,   181,   192,   201,   204,
  209,   216,     0,     4,    16,    64,    28,   129,    72,     9,
   87,     5,     9,     0,     0,    10,    24,    14,    52,    17,
   65,    27,   128,    46,    32,    57,   146,    71,     8,    86,
    4,     4,     6,     1,    20,   104,    51,    80,    56,   145,
    6,     5,     0,    21,   105,    36,   168,    52,    81,    55,
  144,    73,    10,     4,    32,   147,    45,    17,    53,    82,
   75,    33,     6,     3,   160,     7,     2,    12,    40,    31,
  146,    44,    16,    74,    32,     2,    18,    80,    30,   145,
    2,     1,    16,    29,   144,     4,     4,   240,    25,   120,
   49,    64,    81,    19,     4,     8,    16,    26,   121,    50,
   65,    80,    18,     7,    19,    96,    35,   161,    41,     1,
   61,     3,    62,   240,    68,     5,    79,    17,     8,     2,
   32,    15,    56,    33,   148,    34,   160,    40,     0,    60,
    2,    67,     4,    78,    16,     3,    43,     3,    59,     1,
   70,     7,     4,    11,    32,    42,     2,    58,     0,    69,
    6,     2,    39,   240,    64,     1,     2,     9,    22,    63,
    0,     5,    22,   112,    38,   177,    48,    49,    66,     3,
   77,     1,     4,    37,   176,    47,    48,    65,     2,    76,
    0,     1,    83,     1,     2,    13,    48,    82,     0,     3,
   23,   116,    54,    96,    85,     3,     2,    24,   117,    84,
    2,
};

vtkDICOMDictionary::Dict Dict002Data = {
"SVISION",
22,
88,
Dict002TagHashTable,
Dict002Contents
};

// ----- GEMS_XR3DCAL_01 -----

DictEntry Dict003Contents[] = {
{ 0x0021, 0x0020, 0, VR::LT, VM::M1, "GeneralizedCalibration" },
};

unsigned short Dict003TagHashTable[] = {
    2,     0,     1,     0,    32,
};

vtkDICOMDictionary::Dict Dict003Data = {
"GEMS_XR3DCAL_01",
1,
1,
Dict003TagHashTable,
Dict003Contents
};

// ----- GEMS_IMPS_01 -----

DictEntry Dict004Contents[] = {
{ 0x0029, 0x0004, 0, VR::SL, VM::M1, "LowerRangeOfPixels" },
{ 0x0029, 0x0005, 0, VR::DS, VM::M1, "LowerRangeOfPixels" },
{ 0x0029, 0x0006, 0, VR::DS, VM::M1, "LowerRangeOfPixels" },
{ 0x0029, 0x0007, 0, VR::SL, VM::M1, "LowerRangeOfPixels" },
{ 0x0029, 0x0008, 0, VR::SH, VM::M1, "LowerRangeOfPixels" },
{ 0x0029, 0x0009, 0, VR::SH, VM::M1, "LowerRangeOfPixels" },
{ 0x0029, 0x000a, 0, VR::SS, VM::M1, "LowerRangeOfPixels" },
{ 0x0029, 0x0015, 0, VR::SL, VM::M1, "LowerRangeOfPixels1" },
{ 0x0029, 0x0016, 0, VR::SL, VM::M1, "UpperRangeOfPixels1" },
{ 0x0029, 0x0017, 0, VR::SL, VM::M1, "LowerRangeOfPixels2" },
{ 0x0029, 0x0018, 0, VR::SL, VM::M1, "UpperRangeOfPixels2" },
{ 0x0029, 0x001a, 0, VR::SL, VM::M1, "LengthOfTotalHeaderInBytes" },
{ 0x0029, 0x0026, 0, VR::SS, VM::M1, "VersionOfHeaderStructure" },
{ 0x0029, 0x0034, 0, VR::SL, VM::M1, "AdvantageCompOverflow" },
{ 0x0029, 0x0035, 0, VR::SL, VM::M1, "AdvantageCompUnderflow" },
};

unsigned short Dict004TagHashTable[] = {
    4,    17,    24,     0,     6,     0,     4,     4,     8,     7,
   21,     8,    22,    11,    26,    12,    38,     3,     3,     7,
   10,    24,    14,    53,     6,     1,     5,     2,     6,     5,
    9,     6,    10,     9,    23,    13,    52,
};

vtkDICOMDictionary::Dict Dict004Data = {
"GEMS_IMPS_01",
3,
15,
Dict004TagHashTable,
Dict004Contents
};

// ----- Applicare/Centricity Radiology Web/Version 2.0 -----

DictEntry Dict005Contents[] = {
{ 0x4111, 0x0001, 0, VR::CS, VM::M1, "Secondary pineLabel" },
{ 0x4111, 0x0002, 0, VR::IS, VM::M1, "AdditionalTagsForPresentationState" },
};

unsigned short Dict005TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     2,
};

vtkDICOMDictionary::Dict Dict005Data = {
"Applicare/Centricity Radiology Web/Version 2.0",
1,
2,
Dict005TagHashTable,
Dict005Contents
};

// ----- TOSHIBA_MEC_OT3 -----

DictEntry Dict006Contents[] = {
{ 0x0009, 0x0000, 0, VR::LO, VM::M1, "HISRISStudyID" },
};

unsigned short Dict006TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict006Data = {
"TOSHIBA_MEC_OT3",
1,
1,
Dict006TagHashTable,
Dict006Contents
};

// ----- GEIIS -----

DictEntry Dict007Contents[] = {
{ 0x0009, 0x0010, 0, VR::SQ, VM::M1, "GEPrivateImageThumbnailSequence" },
{ 0x0009, 0x0012, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::UL, VM::M1, "ShiftCount" },
{ 0x0029, 0x0012, 0, VR::UL, VM::M1, "Offset" },
{ 0x0029, 0x0014, 0, VR::UL, VM::M1, "ActualFrameNumber" },
{ 0x0905, 0x0030, 0, VR::LO, VM::M1, "AssigningAuthorityForPatientID" },
{ 0x0907, 0x0010, 0, VR::UI, VM::M1, "OriginalStudyInstanceUID" },
{ 0x0907, 0x0020, 0, VR::UI, VM::M1, "OriginalSeriesInstanceUID" },
{ 0x0907, 0x0030, 0, VR::UI, VM::M1, "OriginalSOPInstanceUID" },
{ 0x7fd1, 0x0010, 0, VR::UL, VM::M1, "CompressionType" },
{ 0x7fd1, 0x0020, 0, VR::UL, VM::M1TN, "MultiframeOffsets" },
{ 0x7fd1, 0x0030, 0, VR::UL, VM::M1, "MultiResolutionLevels" },
{ 0x7fd1, 0x0040, 0, VR::UL, VM::M1TN, "SubbandRows" },
{ 0x7fd1, 0x0050, 0, VR::UL, VM::M1TN, "SubbandColumns" },
{ 0x7fd1, 0x0060, 0, VR::UL, VM::M1TN, "SubbandBytecounts" },
};

unsigned short Dict007TagHashTable[] = {
    4,    17,    28,     0,     6,     1,    18,     2,    16,     6,
   16,     7,    32,    11,    48,    12,    64,     5,     0,    16,
    4,    20,     8,    48,    13,    80,    14,    96,     4,     3,
   18,     5,    48,     9,    16,    10,    32,
};

vtkDICOMDictionary::Dict Dict007Data = {
"GEIIS",
3,
15,
Dict007TagHashTable,
Dict007Contents
};

// ----- Philips NM Private Group -----

DictEntry Dict008Contents[] = {
{ 0x7043, 0x0000, 0, VR::SH, VM::M1, "" },
};

unsigned short Dict008TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict008Data = {
"Philips NM Private Group",
1,
1,
Dict008TagHashTable,
Dict008Contents
};

// ----- GEMS_ACRQA_1.0 BLOCK1 -----

DictEntry Dict009Contents[] = {
{ 0x0023, 0x0000, 0, VR::LO, VM::M1, "CRExposureMenuCode" },
{ 0x0023, 0x0010, 0, VR::LO, VM::M1, "CRExposureMenuString" },
{ 0x0023, 0x0020, 0, VR::LO, VM::M1, "CREDRMode" },
{ 0x0023, 0x0030, 0, VR::LO, VM::M1, "CRLatitude" },
{ 0x0023, 0x0040, 0, VR::LO, VM::M1, "CRGroupNumber" },
{ 0x0023, 0x0050, 0, VR::US, VM::M1, "CRImageSerialNumber" },
{ 0x0023, 0x0060, 0, VR::LO, VM::M1, "CRBarCodeNumber" },
{ 0x0023, 0x0070, 0, VR::LO, VM::M1, "CRFilmOutputExposure" },
{ 0x0023, 0x0080, 0, VR::LO, VM::M1, "CRFilmFormat" },
{ 0x0023, 0x0090, 0, VR::LO, VM::M1, "CRSShiftString" },
};

unsigned short Dict009TagHashTable[] = {
    3,    12,     0,     4,     4,    64,     5,    80,     6,    96,
    7,   112,     6,     0,     0,     1,    16,     2,    32,     3,
   48,     8,   128,     9,   144,
};

vtkDICOMDictionary::Dict Dict009Data = {
"GEMS_ACRQA_1.0 BLOCK1",
2,
10,
Dict009TagHashTable,
Dict009Contents
};

// ----- GEMS_ACRQA_1.0 BLOCK3 -----

DictEntry Dict010Contents[] = {
{ 0x0023, 0x0000, 0, VR::DS, VM::M1, "CRDRE" },
{ 0x0023, 0x0010, 0, VR::US, VM::M1, "CRDRN" },
{ 0x0023, 0x0020, 0, VR::DS, VM::M1, "CRORE" },
{ 0x0023, 0x0030, 0, VR::US, VM::M1, "CRORN" },
{ 0x0023, 0x0040, 0, VR::US, VM::M1, "CRORD" },
{ 0x0023, 0x0050, 0, VR::LO, VM::M1, "CRCassetteSize" },
{ 0x0023, 0x0060, 0, VR::LO, VM::M1, "CRMachineID" },
{ 0x0023, 0x0070, 0, VR::LO, VM::M1, "CRMachineType" },
{ 0x0023, 0x0080, 0, VR::LO, VM::M1, "CRTechnicianCode" },
{ 0x0023, 0x0090, 0, VR::LO, VM::M1, "CREnergySubtractionParameters" },
};

unsigned short Dict010TagHashTable[] = {
    3,    12,     0,     4,     4,    64,     5,    80,     6,    96,
    7,   112,     6,     0,     0,     1,    16,     2,    32,     3,
   48,     8,   128,     9,   144,
};

vtkDICOMDictionary::Dict Dict010Data = {
"GEMS_ACRQA_1.0 BLOCK3",
2,
10,
Dict010TagHashTable,
Dict010Contents
};

// ----- GEMS_ACRQA_1.0 BLOCK2 -----

DictEntry Dict011Contents[] = {
{ 0x0023, 0x0000, 0, VR::US, VM::M1, "CRSShift" },
{ 0x0023, 0x0010, 0, VR::DS, VM::M1, "CRCShift" },
{ 0x0023, 0x0020, 0, VR::DS, VM::M1, "CRGT" },
{ 0x0023, 0x0030, 0, VR::DS, VM::M1, "CRGA" },
{ 0x0023, 0x0040, 0, VR::DS, VM::M1, "CRGC" },
{ 0x0023, 0x0050, 0, VR::DS, VM::M1, "CRGS" },
{ 0x0023, 0x0060, 0, VR::DS, VM::M1, "CRRT" },
{ 0x0023, 0x0070, 0, VR::DS, VM::M1, "CRRE" },
{ 0x0023, 0x0080, 0, VR::US, VM::M1, "CRRN" },
{ 0x0023, 0x0090, 0, VR::DS, VM::M1, "CRDRT" },
};

unsigned short Dict011TagHashTable[] = {
    3,    12,     0,     4,     4,    64,     5,    80,     6,    96,
    7,   112,     6,     0,     0,     1,    16,     2,    32,     3,
   48,     8,   128,     9,   144,
};

vtkDICOMDictionary::Dict Dict011Data = {
"GEMS_ACRQA_1.0 BLOCK2",
2,
10,
Dict011TagHashTable,
Dict011Contents
};

// ----- Siemens Ultrasound Miscellaneous -----

DictEntry Dict012Contents[] = {
{ 0x0019, 0x0020, 0, VR::SH, VM::M1, "" },
};

unsigned short Dict012TagHashTable[] = {
    2,     0,     1,     0,    32,
};

vtkDICOMDictionary::Dict Dict012Data = {
"Siemens Ultrasound Miscellaneous",
1,
1,
Dict012TagHashTable,
Dict012Contents
};

// ----- SPI -----

DictEntry Dict013Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "Comments" },
{ 0x0009, 0x0015, 0, VR::LO, VM::M1, "UID" },
{ 0x0009, 0x0040, 0, VR::US, VM::M1, "DataObjectType" },
{ 0x0009, 0x0041, 0, VR::SH, VM::M1, "DataObjectSubtype" },
{ 0x0011, 0x0010, 0, VR::LO, VM::M1, "Organ" },
{ 0x0011, 0x0015, 0, VR::LO, VM::M1, "AllergyIndication" },
{ 0x0011, 0x0020, 0, VR::LO, VM::M1, "Pregnancy" },
{ 0x0029, 0x0060, 0, VR::LO, VM::M1, "CompressionAlgorithm" },
};

unsigned short Dict013TagHashTable[] = {
    3,    12,     0,     4,     1,    21,     2,    64,     5,    21,
    7,    96,     4,     0,    16,     3,    65,     4,    16,     6,
   32,
};

vtkDICOMDictionary::Dict Dict013Data = {
"SPI",
2,
8,
Dict013TagHashTable,
Dict013Contents
};

// ----- GE ??? From Adantage Review CS -----

DictEntry Dict014Contents[] = {
{ 0x0019, 0x0030, 0, VR::LO, VM::M1, "CREDRMode" },
{ 0x0019, 0x0040, 0, VR::LO, VM::M1, "CRLatitude" },
{ 0x0019, 0x0050, 0, VR::LO, VM::M1, "CRGroupNumber" },
{ 0x0019, 0x0070, 0, VR::LO, VM::M1, "CRImageSerialNumber" },
{ 0x0019, 0x0080, 0, VR::LO, VM::M1, "CRBarCodeNumber" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "CRFilmOutputExposures" },
};

unsigned short Dict014TagHashTable[] = {
    2,     0,     6,     0,    48,     1,    64,     2,    80,     3,
  112,     4,   128,     5,   144,
};

vtkDICOMDictionary::Dict Dict014Data = {
"GE ??? From Adantage Review CS",
1,
6,
Dict014TagHashTable,
Dict014Contents
};

// ----- SIEMENS SMS-AX  QUANT 1.0 -----

DictEntry Dict015Contents[] = {
{ 0x0023, 0x0000, 0, VR::DS, VM::M2, "HorizontalCalibrationPixelSize" },
{ 0x0023, 0x0001, 0, VR::DS, VM::M2, "VerticalCalibrationPixelSize" },
{ 0x0023, 0x0002, 0, VR::LO, VM::M1, "CalibrationObject" },
{ 0x0023, 0x0003, 0, VR::DS, VM::M1, "CalibrationObjectSize" },
{ 0x0023, 0x0004, 0, VR::LO, VM::M1, "CalibrationMethod" },
{ 0x0023, 0x0005, 0, VR::ST, VM::M1, "Filename" },
{ 0x0023, 0x0006, 0, VR::IS, VM::M1, "FrameNumber" },
{ 0x0023, 0x0007, 0, VR::IS, VM::M2, "CalibrationFactorMultiplicity" },
{ 0x0023, 0x0008, 0, VR::IS, VM::M1, "CalibrationTableObjectDistance" },
};

unsigned short Dict015TagHashTable[] = {
    3,    12,     0,     4,     1,     1,     3,     3,     5,     5,
    7,     7,     5,     0,     0,     2,     2,     4,     4,     6,
    6,     8,     8,
};

vtkDICOMDictionary::Dict Dict015Data = {
"SIEMENS SMS-AX  QUANT 1.0",
2,
9,
Dict015TagHashTable,
Dict015Contents
};

// ----- AgilityRuntime -----

DictEntry Dict016Contents[] = {
{ 0x0029, 0x0011, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0012, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0013, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0014, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x001f, 0, VR::US, VM::M1, "" },
};

unsigned short Dict016TagHashTable[] = {
    2,     0,     5,     0,    17,     1,    18,     2,    19,     3,
   20,     4,    31,
};

vtkDICOMDictionary::Dict Dict016Data = {
"AgilityRuntime",
1,
5,
Dict016TagHashTable,
Dict016Contents
};

// ----- SIEMENS RA GEN -----

DictEntry Dict017Contents[] = {
{ 0x0011, 0x0020, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0025, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0026, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0030, 0, VR::LO, VM::M1, "" },
{ 0x0011, 0x0035, 0, VR::LO, VM::M1, "" },
{ 0x0011, 0x0040, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x0015, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x001f, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0022, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0024, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0034, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0036, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0038, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0042, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0046, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0048, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x004a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x004c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0054, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0056, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0058, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005c, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x005e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0062, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0064, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0066, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0068, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x006a, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0070, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0072, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0074, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0076, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x007a, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x007c, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x007e, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0080, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0084, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0086, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0088, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x008a, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x008c, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x008e, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0092, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0094, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0096, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0098, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x009a, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x009c, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x009e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00a2, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00a4, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a5, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a6, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00a7, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00a8, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00a9, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00aa, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00ab, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ac, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ad, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00ff, 0, VR::OB, VM::M1, "" },
{ 0x0021, 0x0015, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0025, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0027, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0040, 0, VR::US, VM::M1, "" },
};

unsigned short Dict017TagHashTable[] = {
   22,    33,    44,    49,    58,    65,    74,    83,    94,   101,
  114,   125,   134,   147,   154,   161,   174,   179,   194,   199,
  210,     0,     5,    11,    38,    30,    76,    42,   102,    57,
  136,    71,   166,     5,    17,    50,    35,    88,    46,   114,
   70,   165,    81,    32,     2,    60,   142,    69,   164,     4,
   18,    52,    36,    90,    47,   116,    65,   154,     3,    24,
   64,    59,   140,    82,    37,     4,    19,    54,    37,    92,
   48,   118,    64,   152,     4,     7,    31,    25,    66,    54,
  130,    83,    39,     5,     0,    32,    12,    40,    38,    94,
   43,   104,    67,   158,     3,    26,    68,    53,   128,    76,
  171,     6,    13,    42,    31,    80,    44,   106,    66,   156,
   75,   170,    84,    40,     5,     1,    37,    27,    70,    56,
  134,    74,   169,    80,    21,     4,    14,    44,    32,    82,
   61,   146,    73,   168,     6,     3,    48,     6,    21,    20,
   56,    49,   120,    55,   132,    86,    64,     3,     2,    38,
   15,    46,    33,    84,     3,    21,    58,    50,   122,    78,
  173,     6,     4,    53,     8,    32,    34,    86,    39,    96,
   63,   150,    77,   172,     2,    22,    60,    51,   124,     7,
    5,    64,     9,    34,    28,    72,    40,    98,    62,   148,
   68,   162,    85,    48,     2,    23,    62,    52,   126,     5,
   10,    36,    29,    74,    41,   100,    58,   138,    79,   255,
    3,    16,    48,    45,   112,    72,   167,
};

vtkDICOMDictionary::Dict Dict017Data = {
"SIEMENS RA GEN",
21,
87,
Dict017TagHashTable,
Dict017Contents
};

// ----- Mayo/IBM Archive Project -----

DictEntry Dict018Contents[] = {
{ 0x0021, 0x0001, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0010, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0011, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0012, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0013, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0014, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0015, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0016, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0017, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0018, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0019, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x001a, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x001b, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x001c, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x001d, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x001e, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x001f, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0040, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0041, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0050, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0060, 0, VR::UN, VM::M1, "" },
{ 0x0021, 0x0065, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict018TagHashTable[] = {
    6,    13,    24,    37,    46,     0,     3,     4,    19,     7,
   22,    14,    29,     5,     3,    18,    10,    25,    13,    28,
   17,    32,    18,    64,     6,     0,     1,     6,    21,     9,
   24,    16,    31,    19,    65,    20,    80,     4,     2,    17,
    5,    20,    12,    27,    15,    30,     5,     1,    16,     8,
   23,    11,    26,    21,    96,    22,   101,
};

vtkDICOMDictionary::Dict Dict018Data = {
"Mayo/IBM Archive Project",
5,
23,
Dict018TagHashTable,
Dict018Contents
};

// ----- SIEMENS SIENET -----

DictEntry Dict019Contents[] = {
{ 0x0019, 0x0001, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict019TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict019Data = {
"SIEMENS SIENET",
1,
1,
Dict019TagHashTable,
Dict019Contents
};

// ----- MDS NORDION OTP ANATOMY MODELLING -----

DictEntry Dict020Contents[] = {
{ 0x3005, 0x0000, 0, VR::SQ, VM::M1, "" },
{ 0x3005, 0x0002, 0, VR::CS, VM::M1, "" },
{ 0x3005, 0x0004, 0, VR::DS, VM::M1, "" },
{ 0x3005, 0x0006, 0, VR::DS, VM::M1, "" },
{ 0x3005, 0x0008, 0, VR::DS, VM::M1, "" },
{ 0x3005, 0x000a, 0, VR::CS, VM::M1, "" },
{ 0x3005, 0x000c, 0, VR::CS, VM::M1, "" },
{ 0x3005, 0x000e, 0, VR::CS, VM::M1, "" },
{ 0x3005, 0x0010, 0, VR::DS, VM::M1, "" },
{ 0x3005, 0x0012, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict020TagHashTable[] = {
    2,     3,     0,    10,     0,     0,     1,     2,     2,     4,
    3,     6,     4,     8,     5,    10,     6,    12,     7,    14,
    8,    16,     9,    18,
};

vtkDICOMDictionary::Dict Dict020Data = {
"MDS NORDION OTP ANATOMY MODELLING",
2,
10,
Dict020TagHashTable,
Dict020Contents
};

// ----- SIEMENS CT APPL DATASET -----

DictEntry Dict021Contents[] = {
{ 0x0029, 0x0000, 0, VR::LT, VM::M1, "DualEnergyAlgorithmParameters" },
{ 0x0029, 0x0001, 0, VR::US, VM::M1, "ValidCTVolumeMBoxTasks" },
{ 0x0029, 0x0002, 0, VR::LT, VM::M1, "ScanOptions" },
{ 0x0029, 0x0003, 0, VR::ST, VM::M1, "AcquisitionDateandTime" },
{ 0x0029, 0x0004, 0, VR::ST, VM::M1, "AcquisitionNumber" },
{ 0x0029, 0x0005, 0, VR::ST, VM::M1, "DynamicData" },
{ 0x0029, 0x0006, 0, VR::DS, VM::M6, "ImageOrientationPatient" },
{ 0x0029, 0x0007, 0, VR::LT, VM::M1, "FrameOfReferenceUid" },
{ 0x0029, 0x0008, 0, VR::LT, VM::M1, "PatientPosition" },
{ 0x0029, 0x0009, 0, VR::LT, VM::M1, "ConvolutionKernel" },
{ 0x0029, 0x0010, 0, VR::LT, VM::M1, "Kvp" },
{ 0x0029, 0x0011, 0, VR::LT, VM::M1, "ReconstructionDiameter" },
{ 0x0029, 0x0012, 0, VR::LT, VM::M1, "RescaleIntercept" },
{ 0x0029, 0x0013, 0, VR::LT, VM::M1, "RescaleSlope" },
{ 0x0029, 0x0014, 0, VR::LT, VM::M1, "SliceThickness" },
{ 0x0029, 0x0015, 0, VR::LT, VM::M1, "TableHeight" },
{ 0x0029, 0x0016, 0, VR::LT, VM::M1, "GantryDetectorTilt" },
{ 0x0029, 0x0017, 0, VR::LT, VM::M1, "PixelSpacing" },
{ 0x0029, 0x0018, 0, VR::ST, VM::M1, "VolumePatientPositionNotEqual" },
{ 0x0029, 0x0019, 0, VR::ST, VM::M1, "VolumeLossyImageCompressionNotEqual" },
{ 0x0029, 0x0020, 0, VR::ST, VM::M1, "VolumeConvolutionKernelNotEqual" },
{ 0x0029, 0x0021, 0, VR::ST, VM::M1, "VolumePixelSpacingNotEqual" },
{ 0x0029, 0x0022, 0, VR::ST, VM::M1, "VolumeKvpNotEqual" },
{ 0x0029, 0x0023, 0, VR::ST, VM::M1, "VolumeReconstructionDiameterNotEqual" },
{ 0x0029, 0x0024, 0, VR::ST, VM::M1, "VolumeTableHeightNotEqual" },
{ 0x0029, 0x0025, 0, VR::ST, VM::M1, "VolumeHasGaps" },
{ 0x0029, 0x0026, 0, VR::ST, VM::M1, "VolumeNumberOfMissingImages" },
{ 0x0029, 0x0027, 0, VR::ST, VM::M1, "VolumeMaxGap" },
{ 0x0029, 0x0028, 0, VR::LT, VM::M1, "VolumePositionOfGaps" },
{ 0x0029, 0x0029, 0, VR::FD, VM::M1, "CalibrationFactor" },
{ 0x0029, 0x002A, 0, VR::CS, VM::M1, "FlashMode" },
{ 0x0029, 0x002B, 0, VR::LT, VM::M1, "Warnings" },
{ 0x0029, 0x002C, 0, VR::ST, VM::M1, "VolumeHighBitNotEqual" },
{ 0x0029, 0x002D, 0, VR::ST, VM::M1, "VolumeImageTypeNotEqual" },
{ 0x0029, 0x002E, 0, VR::ST, VM::M1, "ImageType0" },
{ 0x0029, 0x002F, 0, VR::ST, VM::M1, "ImageType1" },
{ 0x0029, 0x0030, 0, VR::ST, VM::M1, "ImageType2" },
{ 0x0029, 0x0031, 0, VR::ST, VM::M1, "ImageType3" },
{ 0x0029, 0x0032, 0, VR::ST, VM::M1, "PhotometricInterpretationNotMONOCHROME2" },
{ 0x0029, 0x0033, 0, VR::DA, VM::M1, "FirstAcquisitionDate" },
{ 0x0029, 0x0034, 0, VR::DA, VM::M1, "LastAcquisitionDate" },
{ 0x0029, 0x0035, 0, VR::TM, VM::M1, "FirstAcquisitionTime" },
{ 0x0029, 0x0036, 0, VR::TM, VM::M1, "LastAcquisitionTime" },
{ 0x0029, 0x0037, 0, VR::ST, VM::M1, "InternalData" },
{ 0x0029, 0x0038, 0, VR::ST, VM::M1, "RangesSOM7" },
{ 0x0029, 0x0039, 0, VR::LT, VM::M1, "CalculatedGantryDetectorTilt" },
{ 0x0029, 0x0040, 0, VR::ST, VM::M1, "VolumeSliceDistance" },
{ 0x0029, 0x0041, 0, VR::DS, VM::M1, "FirstSliceZCoordinate" },
{ 0x0029, 0x0042, 0, VR::DS, VM::M1, "LastSliceZCoordinate" },
{ 0x0029, 0x0043, 0, VR::DS, VM::M1, "ContentDateTime" },
{ 0x0029, 0x0044, 0, VR::DS, VM::M1, "DeltaTime" },
{ 0x0029, 0x0045, 0, VR::DS, VM::M1, "FrameCount" },
};

unsigned short Dict021TagHashTable[] = {
   14,    23,    34,    45,    56,    69,    80,    89,    98,   105,
  112,   119,   126,     0,     4,    24,    36,    29,    41,    39,
   51,    46,    64,     5,     1,     1,    27,    39,    28,    40,
   38,    50,    47,    65,     5,     0,     0,    26,    38,    31,
   43,    41,    53,    48,    66,     5,     3,     3,    30,    42,
   40,    52,    45,    57,    49,    67,     6,     2,     2,    11,
   17,    33,    45,    43,    55,    44,    56,    50,    68,     5,
    5,     5,    10,    16,    32,    44,    42,    54,    51,    69,
    4,     4,     4,     9,     9,    13,    19,    35,    47,     4,
    7,     7,     8,     8,    12,    18,    34,    46,     3,     6,
    6,    15,    21,    21,    33,     3,    14,    20,    19,    25,
   20,    32,     3,    17,    23,    18,    24,    23,    35,     3,
   16,    22,    22,    34,    37,    49,     2,    25,    37,    36,
   48,
};

vtkDICOMDictionary::Dict Dict021Data = {
"SIEMENS CT APPL DATASET",
13,
52,
Dict021TagHashTable,
Dict021Contents
};

// ----- DCMTK_ANONYMIZER -----

DictEntry Dict022Contents[] = {
{ 0x0009, 0x0000, 0, VR::SQ, VM::M1, "AnonymizerUIDMap" },
{ 0x0009, 0x0010, 0, VR::UI, VM::M1, "AnonymizerUIDKey" },
{ 0x0009, 0x0020, 0, VR::UI, VM::M1, "AnonymizerUIDValue" },
{ 0x0009, 0x0030, 0, VR::SQ, VM::M1, "AnonymizerPatientIDMap" },
{ 0x0009, 0x0040, 0, VR::LO, VM::M1, "AnonymizerPatientIDKey" },
{ 0x0009, 0x0050, 0, VR::LO, VM::M1, "AnonymizerPatientIDValue" },
};

unsigned short Dict022TagHashTable[] = {
    2,     0,     6,     0,     0,     1,    16,     2,    32,     3,
   48,     4,    64,     5,    80,
};

vtkDICOMDictionary::Dict Dict022Data = {
"DCMTK_ANONYMIZER",
1,
6,
Dict022TagHashTable,
Dict022Contents
};

// ----- AGFA PACS Archive Mirroring 1.0 -----

DictEntry Dict023Contents[] = {
{ 0x0031, 0x0000, 0, VR::CS, VM::M1, "" },
{ 0x0031, 0x0001, 0, VR::UL, VM::M1, "" },
};

unsigned short Dict023TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict023Data = {
"AGFA PACS Archive Mirroring 1.0",
1,
2,
Dict023TagHashTable,
Dict023Contents
};

// ----- syngoDynamics -----

DictEntry Dict024Contents[] = {
{ 0x0021, 0x00ae, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict024TagHashTable[] = {
    2,     0,     1,     0,   174,
};

vtkDICOMDictionary::Dict Dict024Data = {
"syngoDynamics",
1,
1,
Dict024TagHashTable,
Dict024Contents
};

// ----- SIEMENS SYNGO ULTRA-SOUND TOYON DATA STREAMING -----

DictEntry Dict025Contents[] = {
{ 0x7FD1, 0x0001, 0, VR::OB, VM::M1, "Padding" },
{ 0x7FD1, 0x0009, 0, VR::OB, VM::M1, "VersionID" },
{ 0x7FD1, 0x0010, 0, VR::LO, VM::M1, "Payload" },
{ 0x7FD1, 0x0011, 0, VR::LO, VM::M1, "AfterPayload" },
};

unsigned short Dict025TagHashTable[] = {
    2,     0,     4,     0,     1,     1,     9,     2,    16,     3,
   17,
};

vtkDICOMDictionary::Dict Dict025Data = {
"SIEMENS SYNGO ULTRA-SOUND TOYON DATA STREAMING",
1,
4,
Dict025TagHashTable,
Dict025Contents
};

// ----- Hipaa Private Creator -----

DictEntry Dict026Contents[] = {
{ 0x0011, 0x0001, 0, VR::LT, VM::M1, "EncryptedInstanceCreatorID" },
{ 0x0011, 0x0002, 0, VR::LT, VM::M1, "EncryptedSOPInstanceUID" },
{ 0x0011, 0x0003, 0, VR::LT, VM::M1, "EncryptedAccessionNumber" },
{ 0x0011, 0x0004, 0, VR::LT, VM::M1, "EncryptedInstitutionName" },
{ 0x0011, 0x0005, 0, VR::LT, VM::M1, "EncryptedInstitutionAddress" },
{ 0x0011, 0x0006, 0, VR::LT, VM::M1, "EncryptedReferringPhysicianName" },
{ 0x0011, 0x0007, 0, VR::LT, VM::M1, "EncryptedReferringPhysicianAddress" },
{ 0x0011, 0x0008, 0, VR::LT, VM::M1, "EncryptedStationName" },
{ 0x0011, 0x0009, 0, VR::LT, VM::M1, "EncryptedStudyDescription" },
{ 0x0011, 0x0010, 0, VR::LT, VM::M1, "EncryptedSeriesDescription" },
{ 0x0011, 0x0011, 0, VR::LT, VM::M1, "EncryptedInstitutionalDepartmentName" },
{ 0x0011, 0x0012, 0, VR::LT, VM::M1, "EncryptedPhysiciansOfRecord" },
{ 0x0011, 0x0013, 0, VR::LT, VM::M1, "EncryptedPerformingPhysicianName" },
{ 0x0011, 0x0014, 0, VR::LT, VM::M1, "EncryptedNameOfPhysiciansReadingStudy" },
{ 0x0011, 0x0015, 0, VR::LT, VM::M1, "EncryptedOperatorName" },
{ 0x0011, 0x0016, 0, VR::LT, VM::M1, "EncryptedAdmittingDiagnosesDescription" },
{ 0x0011, 0x0017, 0, VR::LT, VM::M1, "EncryptedReferencedSOPInstanceUID" },
{ 0x0011, 0x0018, 0, VR::LT, VM::M1, "EncryptedDerivationDescription" },
{ 0x0011, 0x0019, 0, VR::LT, VM::M1, "EncryptedPatientName" },
{ 0x0011, 0x0020, 0, VR::LT, VM::M1, "EncryptedPatientID" },
{ 0x0011, 0x0021, 0, VR::LT, VM::M1, "EncryptedPatientBirthDate" },
{ 0x0011, 0x0022, 0, VR::LT, VM::M1, "EncryptedPatientBirthTime" },
{ 0x0011, 0x0023, 0, VR::LT, VM::M1, "EncryptedPatientSex" },
{ 0x0011, 0x0024, 0, VR::LT, VM::M1, "EncryptedOtherPatientIDs" },
{ 0x0011, 0x0025, 0, VR::LT, VM::M1, "EncryptedOtherPatientNames" },
{ 0x0011, 0x0026, 0, VR::LT, VM::M1, "EncryptedPatientAge" },
{ 0x0011, 0x0027, 0, VR::LT, VM::M1, "EncryptedPatientSize" },
{ 0x0011, 0x0028, 0, VR::LT, VM::M1, "EncryptedPatientWeight" },
{ 0x0011, 0x0029, 0, VR::LT, VM::M1, "EncryptedMedicalRecordLocator" },
{ 0x0011, 0x0030, 0, VR::LT, VM::M1, "EncryptedEthnicGroup" },
{ 0x0011, 0x0031, 0, VR::LT, VM::M1, "EncryptedOccupation" },
{ 0x0011, 0x0032, 0, VR::LT, VM::M1, "EncryptedAdditionalPatient'sHistory" },
{ 0x0011, 0x0033, 0, VR::LT, VM::M1, "EncryptedPatientComments" },
{ 0x0011, 0x0034, 0, VR::LT, VM::M1, "EncryptedDeviceSerialNumber" },
{ 0x0011, 0x0035, 0, VR::LT, VM::M1, "EncryptedProtocolName" },
{ 0x0011, 0x0036, 0, VR::LT, VM::M1, "EncryptedStudyInstanceUID" },
{ 0x0011, 0x0037, 0, VR::LT, VM::M1, "EncryptedSeriesInstanceUID" },
{ 0x0011, 0x0038, 0, VR::LT, VM::M1, "EncryptedStudyID" },
{ 0x0011, 0x0039, 0, VR::LT, VM::M1, "EncryptedFrameOfReferenceUID" },
{ 0x0011, 0x0040, 0, VR::LT, VM::M1, "EncryptedSynchronizationFrameOfReferenceUID" },
{ 0x0011, 0x0041, 0, VR::LT, VM::M1, "EncryptedImageComments" },
{ 0x0011, 0x0042, 0, VR::LT, VM::M1, "EncryptedUID" },
};

unsigned short Dict026TagHashTable[] = {
   11,    22,    33,    44,    53,    62,    71,    80,    87,    96,
    0,     5,     4,     5,    10,    17,    22,    35,    38,    57,
   39,    64,     5,     3,     4,     9,    16,    21,    34,    37,
   56,    40,    65,     5,     6,     7,    12,    19,    24,    37,
   30,    49,    41,    66,     4,     5,     6,    11,    18,    23,
   36,    29,    48,     4,     8,     9,    14,    21,    26,    39,
   32,    51,     4,     7,     8,    13,    20,    25,    38,    31,
   50,     4,     0,     1,    16,    23,    28,    41,    34,    53,
    3,    15,    22,    27,    40,    33,    52,     4,     2,     3,
   18,    25,    20,    33,    36,    55,     4,     1,     2,    17,
   24,    19,    32,    35,    54,
};

vtkDICOMDictionary::Dict Dict026Data = {
"Hipaa Private Creator",
10,
42,
Dict026TagHashTable,
Dict026Contents
};

// ----- GEMS_GNHD_01 -----

DictEntry Dict027Contents[] = {
{ 0x0033, 0x0001, 0, VR::UN, VM::M1, "" },
{ 0x0033, 0x0002, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict027TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     2,
};

vtkDICOMDictionary::Dict Dict027Data = {
"GEMS_GNHD_01",
1,
2,
Dict027TagHashTable,
Dict027Contents
};

// ----- PAPYRUS 3.0 -----

DictEntry Dict028Contents[] = {
{ 0x0041, 0x0000, 0, VR::LT, VM::M1, "PapyrusComments" },
{ 0x0041, 0x0010, 0, VR::SQ, VM::M1, "PointerSequence" },
{ 0x0041, 0x0011, 0, VR::UL, VM::M1, "ImagePointer" },
{ 0x0041, 0x0012, 0, VR::UL, VM::M1, "PixelOffset" },
{ 0x0041, 0x0013, 0, VR::SQ, VM::M1, "ImageIdentifierSequence" },
{ 0x0041, 0x0014, 0, VR::SQ, VM::M1, "ExternalFileReferenceSequence" },
{ 0x0041, 0x0015, 0, VR::US, VM::M1, "NumberOfImages" },
{ 0x0041, 0x0021, 0, VR::UI, VM::M1, "ReferencedSOPClassUID" },
{ 0x0041, 0x0022, 0, VR::UI, VM::M1, "ReferencedSOPInstanceUID" },
{ 0x0041, 0x0031, 0, VR::LT, VM::M1, "ReferencedFileName" },
{ 0x0041, 0x0032, 0, VR::LT, VM::M1TN, "ReferencedFilePath" },
{ 0x0041, 0x0041, 0, VR::UI, VM::M1, "ReferencedImageSOPClassUID" },
{ 0x0041, 0x0042, 0, VR::UI, VM::M1, "ReferencedImageSOPInstanceUID" },
{ 0x0041, 0x0050, 0, VR::SQ, VM::M1, "ImageSequence" },
};

unsigned short Dict028TagHashTable[] = {
    4,    15,    24,     0,     5,     2,    17,     5,    20,    10,
   50,    11,    65,    12,    66,     4,     0,     0,     3,    18,
    6,    21,     7,    33,     5,     1,    16,     4,    19,     8,
   34,     9,    49,    13,    80,
};

vtkDICOMDictionary::Dict Dict028Data = {
"PAPYRUS 3.0",
3,
14,
Dict028TagHashTable,
Dict028Contents
};

// ----- ACUSON -----

DictEntry Dict029Contents[] = {
{ 0x0009, 0x0007, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x0008, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x0009, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x000a, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x000b, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x000c, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x000d, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x000e, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x000f, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0011, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x0012, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0013, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0014, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x0015, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict029TagHashTable[] = {
    4,    15,    26,     0,     5,     2,     9,     3,    10,     8,
   15,    10,    17,    11,    18,     5,     1,     8,     6,    13,
    7,    14,     9,    16,    14,    21,     5,     0,     7,     4,
   11,     5,    12,    12,    19,    13,    20,
};

vtkDICOMDictionary::Dict Dict029Data = {
"ACUSON",
3,
15,
Dict029TagHashTable,
Dict029Contents
};

// ----- Philips MR Imaging DD 001 -----

DictEntry Dict030Contents[] = {
{ 0x2005, 0x0000, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0001, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0002, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0004, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0005, 0, VR::CS, VM::M1, "SynergyReconstructionType" },
{ 0x2005, 0x0008, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0009, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000b, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000d, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000f, 0, VR::DS, VM::M1, "WindowCenter" },
{ 0x2005, 0x0010, 0, VR::DS, VM::M1, "WindowWidth" },
{ 0x2005, 0x0011, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0012, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0013, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0014, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0015, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0016, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0017, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0018, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0019, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x001a, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x001b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x001c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x001d, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x001e, 0, VR::SH, VM::M1, "" },
{ 0x2005, 0x001f, 0, VR::SH, VM::M1, "" },
{ 0x2005, 0x0020, 0, VR::SL, VM::M1, "NumberOfChemicalShift" },
{ 0x2005, 0x0021, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0022, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0023, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0025, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0026, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0027, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0028, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0029, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002a, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x002b, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x002c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002d, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x002e, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0030, 0, VR::FL, VM::M1, "RepetitionTime" },
{ 0x2005, 0x0031, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0032, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0033, 0, VR::FL, VM::M1, "AcquisitionDuration" },
{ 0x2005, 0x0034, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0035, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0036, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0037, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0038, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0039, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x003a, 0, VR::SH, VM::M1, "" },
{ 0x2005, 0x003b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x003c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x003d, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x003e, 0, VR::SL, VM::M1TN, "" },
{ 0x2005, 0x0048, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0049, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x004a, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x004b, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x004c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x004d, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x004e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x004f, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0050, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0051, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0052, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0053, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0054, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0055, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0056, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0057, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0058, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0059, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005b, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005d, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x005e, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x005f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0060, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0061, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0063, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0064, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0065, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0066, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0067, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0068, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0069, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006b, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006d, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006e, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x006f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0070, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0071, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0072, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0073, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0074, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0075, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0076, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0078, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0079, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x007a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x007b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x007e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0080, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0081, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0083, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0084, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0085, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0086, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x009e, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x009f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00a0, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x00a1, 0, VR::CS, VM::M1, "SyncraScan ype" },
{ 0x2005, 0x00a2, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00a3, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a4, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a5, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a6, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a7, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00a8, 0, VR::DS, VM::M1, "" },
{ 0x2005, 0x00a9, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00b0, 0, VR::FL, VM::M1, "DiffusionDirectionRL" },
{ 0x2005, 0x00b1, 0, VR::FL, VM::M1, "DiffusionDirectionAP" },
{ 0x2005, 0x00b2, 0, VR::FL, VM::M1, "DiffusionDirectionFH" },
{ 0x2005, 0x00c0, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict030TagHashTable[] = {
   34,    43,    50,    55,    60,    65,    72,    77,    82,    91,
  102,   113,   126,   141,   152,   165,   176,   185,   194,   203,
  212,   219,   230,   241,   250,   259,   266,   273,   282,   291,
  300,   311,   320,     0,     4,    21,    24,    55,    59,    78,
   91,   116,   158,     3,    24,    27,    54,    58,    86,   100,
    2,    23,    26,    87,   101,     2,    33,    37,    88,   102,
    2,     4,     5,    89,   103,     3,     3,     4,    35,    39,
   83,    96,     2,    34,    38,    84,    97,     2,    30,    33,
  125,   167,     4,     1,     1,    29,    32,    85,    99,   124,
  166,     5,     0,     0,    32,    35,    94,   108,   115,   134,
  123,   165,     5,    31,    34,    63,    76,    95,   109,   114,
  133,   122,   164,     6,     2,     2,    41,    45,    64,    77,
   96,   110,   113,   132,   121,   163,     7,    10,    13,    40,
   44,    65,    78,    97,   111,   112,   131,   120,   162,   131,
  192,     5,     9,    12,    43,    47,    66,    79,    90,   104,
  119,   161,     6,    12,    15,    42,    46,    59,    72,    91,
  105,   111,   129,   118,   160,     5,    11,    14,    37,    41,
   60,    73,    92,   106,   110,   128,     4,     6,     9,    36,
   40,    61,    74,    93,   107,     4,     5,     8,    39,    43,
   62,    75,   102,   116,     4,     8,    11,    38,    42,    71,
   84,   103,   117,     4,     7,    10,    49,    53,    72,    85,
  104,   118,     3,    18,    21,    48,    52,    73,    86,     5,
   17,    20,    51,    55,    74,    87,    98,   112,   127,   169,
    5,    20,    23,    50,    54,    67,    80,    99,   113,   126,
  168,     4,    19,    22,    45,    49,    68,    81,   100,   114,
    4,    14,    17,    44,    48,    69,    82,   101,   115,     3,
   13,    16,    47,    51,    70,    83,     3,    16,    19,    46,
   50,    79,    92,     4,    15,    18,    57,    61,    80,    93,
  109,   126,     4,    26,    29,    56,    60,    81,    94,   130,
  178,     4,    25,    28,    82,    95,   105,   120,   129,   177,
    5,    28,    31,    58,    62,    75,    88,   106,   121,   128,
  176,     4,    27,    30,    53,    57,    76,    89,   107,   122,
    5,    22,    25,    52,    56,    77,    90,   108,   123,   117,
  159,
};

vtkDICOMDictionary::Dict Dict030Data = {
"Philips MR Imaging DD 001",
33,
132,
Dict030TagHashTable,
Dict030Contents
};

// ----- Philips MR Imaging DD 005 -----

DictEntry Dict031Contents[] = {
{ 0x2005, 0x0000, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0001, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0002, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0003, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0004, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0006, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0007, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0009, 0, VR::DS, VM::M1, "" },
{ 0x2005, 0x000a, 0, VR::DS, VM::M1, "" },
{ 0x2005, 0x000b, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x000e, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x000f, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0011, 0, VR::UI, VM::M1, "" },
{ 0x2005, 0x0012, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0013, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0014, 0, VR::SL, VM::M1, "" },
{ 0x2005, 0x0015, 0, VR::SL, VM::M1, "" },
{ 0x2005, 0x0016, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0018, 0, VR::CS, VM::M3, "" },
{ 0x2005, 0x0019, 0, VR::CS, VM::M3, "" },
{ 0x2005, 0x001a, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x001b, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x001c, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x001d, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x001e, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x001f, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0020, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0021, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0022, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0023, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0024, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0025, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0026, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0027, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0028, 0, VR::SL, VM::M1, "" },
{ 0x2005, 0x0029, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002a, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002d, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x002f, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0030, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0031, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0032, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0035, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0036, 0, VR::UI, VM::M1, "" },
{ 0x2005, 0x0037, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0038, 0, VR::LT, VM::M1, "" },
{ 0x2005, 0x0039, 0, VR::LT, VM::M1, "" },
{ 0x2005, 0x003a, 0, VR::LT, VM::M1, "" },
{ 0x2005, 0x003b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x003c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x003d, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x003e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x003f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0040, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0041, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0042, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0043, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0044, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0045, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0046, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0047, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0048, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0049, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x004a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x004b, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x004c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x004d, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x004e, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x004f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0050, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0055, 0, VR::FD, VM::M3, "" },
{ 0x2005, 0x0090, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0091, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict031TagHashTable[] = {
   20,    31,    42,    51,    62,    71,    80,    91,   100,   109,
  116,   125,   132,   141,   150,   157,   166,   173,   182,     0,
    5,     6,     7,    12,    16,    40,    45,    55,    62,    67,
   74,     5,     5,     6,    15,    19,    39,    44,    50,    57,
   68,    75,     4,     1,     1,    14,    18,    42,    47,    49,
   56,     5,     0,     0,    24,    29,    41,    46,    52,    59,
   74,    85,     4,     3,     3,    23,    28,    36,    41,    51,
   58,     4,     2,     2,    26,    31,    35,    40,    61,    68,
    5,    25,    30,    38,    43,    62,    69,    73,    80,    76,
  145,     4,    20,    25,    37,    42,    63,    70,    75,   144,
    4,    11,    15,    19,    24,    46,    53,    64,    71,     3,
   10,    14,    22,    27,    57,    64,     4,     7,     9,    21,
   26,    48,    55,    58,    65,     3,    32,    37,    47,    54,
   59,    66,     4,     9,    11,    31,    36,    44,    49,    60,
   67,     4,     8,    10,    34,    39,    43,    48,    69,    76,
    3,    17,    21,    33,    38,    70,    77,     4,    16,    20,
   28,    33,    45,    50,    71,    78,     3,    27,    32,    54,
   61,    72,    79,     4,    18,    22,    30,    35,    53,    60,
   65,    72,     5,     4,     4,    13,    17,    29,    34,    56,
   63,    66,    73,
};

vtkDICOMDictionary::Dict Dict031Data = {
"Philips MR Imaging DD 005",
19,
77,
Dict031TagHashTable,
Dict031Contents
};

// ----- Philips MR Imaging DD 004 -----

DictEntry Dict032Contents[] = {
{ 0x2005, 0x0000, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0001, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0002, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0003, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0004, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0005, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0006, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0007, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0008, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0009, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0010, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0012, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0013, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0014, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0015, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0016, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0017, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0025, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0026, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0027, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0028, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0029, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0030, 0, VR::CS, VM::M1TN, "" },
{ 0x2005, 0x0031, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0033, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0034, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0035, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0036, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0037, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0038, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0039, 0, VR::SS, VM::M2, "" },
{ 0x2005, 0x0040, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0041, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0042, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0043, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0044, 0, VR::SS, VM::M1TN, "" },
{ 0x2005, 0x0045, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0046, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0047, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0048, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0049, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0050, 0, VR::FL, VM::M2, "" },
{ 0x2005, 0x0051, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0052, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0053, 0, VR::LO, VM::M1TN, "" },
{ 0x2005, 0x0054, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0055, 0, VR::FL, VM::M1TN, "" },
{ 0x2005, 0x0056, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0057, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0058, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0059, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0060, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0061, 0, VR::FL, VM::M2, "" },
{ 0x2005, 0x0062, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0063, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0064, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0070, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0071, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0072, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0073, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0074, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0075, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0076, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0077, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0078, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0079, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0081, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0082, 0, VR::UL, VM::M1, "" },
{ 0x2005, 0x0083, 0, VR::CS, VM::M1TN, "" },
{ 0x2005, 0x0084, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0085, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0086, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0087, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0088, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0089, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0090, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0091, 0, VR::PN, VM::M1, "" },
{ 0x2005, 0x0092, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0093, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0095, 0, VR::UI, VM::M1, "" },
{ 0x2005, 0x0096, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0097, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0098, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0099, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict032TagHashTable[] = {
   22,    29,    40,    55,    64,    75,    86,    99,   110,   117,
  122,   129,   140,   151,   158,   163,   170,   181,   192,   201,
  204,     0,     3,    13,    20,    45,    84,    52,    97,     5,
   16,    23,    30,    57,    46,    85,    53,    98,    78,   147,
    7,    15,    22,    29,    56,    47,    86,    54,    99,    64,
  120,    72,   135,    77,   146,     4,    48,    87,    65,   121,
   71,   134,    76,   145,     5,     5,     5,    10,    16,    41,
   80,    70,   133,    75,   144,     5,     4,     4,    12,    19,
   35,    68,    42,    81,    69,   132,     6,     7,     7,    11,
   18,    21,    41,    36,    69,    43,    82,    68,   131,     5,
    6,     6,    20,    40,    37,    70,    44,    83,    67,   130,
    3,     1,     1,    38,    71,    66,   129,     2,     0,     0,
   31,    64,     3,     3,     3,    26,    53,    32,    65,     5,
    2,     2,    25,    52,    33,    66,    60,   116,    83,   153,
    5,    28,    55,    34,    67,    49,    88,    61,   117,    82,
  152,     3,    27,    54,    50,    89,    62,   118,     2,    23,
   49,    63,   119,     3,    17,    37,    22,    48,    56,   112,
    5,     9,     9,    24,    51,    55,   100,    57,   113,    74,
  137,     5,     8,     8,    19,    39,    39,    72,    58,   114,
   73,   136,     4,    18,    38,    40,    73,    59,   115,    81,
  151,     1,    80,   150,     3,    14,    21,    51,    96,    79,
  149,
};

vtkDICOMDictionary::Dict Dict032Data = {
"Philips MR Imaging DD 004",
21,
84,
Dict032TagHashTable,
Dict032Contents
};

// ----- dcm4che/archive -----

DictEntry Dict033Contents[] = {
{ 0x0043, 0x0010, 0, VR::OB, VM::M1, "PatientPk" },
{ 0x0043, 0x0011, 0, VR::OB, VM::M1, "StudyPk" },
{ 0x0043, 0x0012, 0, VR::OB, VM::M1, "SeriesPk" },
{ 0x0043, 0x0013, 0, VR::OB, VM::M1, "InstancePk" },
{ 0x0043, 0x0014, 0, VR::AE, VM::M1, "CallingAETitle" },
{ 0x0043, 0x0015, 0, VR::AE, VM::M1, "CalledAETitle" },
{ 0x0043, 0x0016, 0, VR::DT, VM::M1, "InstanceUpdated" },
{ 0x0043, 0x0020, 0, VR::SQ, VM::M1, "WorkItemSeq" },
{ 0x0043, 0x0030, 0, VR::UI, VM::M1, "Dcm4cheURIReferencedTransferSyntaxUID" },
};

unsigned short Dict033TagHashTable[] = {
    3,    16,     0,     6,     0,    16,     2,    18,     4,    20,
    6,    22,     7,    32,     8,    48,     3,     1,    17,     3,
   19,     5,    21,
};

vtkDICOMDictionary::Dict Dict033Data = {
"dcm4che/archive",
2,
9,
Dict033TagHashTable,
Dict033Contents
};

// ----- AMI Annotations_02 -----

DictEntry Dict034Contents[] = {
{ 0x3101, 0x0020, 0, VR::SQ, VM::M1, "AnnotationSequence" },
};

unsigned short Dict034TagHashTable[] = {
    2,     0,     1,     0,    32,
};

vtkDICOMDictionary::Dict Dict034Data = {
"AMI Annotations_02",
1,
1,
Dict034TagHashTable,
Dict034Contents
};

// ----- TERARECON AQUARIUS -----

DictEntry Dict035Contents[] = {
{ 0x0077, 0x0010, 0, VR::UI, VM::M1TN, "OriginalSeriesStudyUID" },
{ 0x0077, 0x0012, 0, VR::UI, VM::M1TN, "OriginalSOPUID" },
{ 0x0077, 0x0014, 0, VR::LO, VM::M1TN, "ReferencedVolumeID" },
{ 0x0077, 0x0016, 0, VR::CS, VM::M1, "BinaryDataNameSCS" },
{ 0x0077, 0x0020, 0, VR::LO, VM::M1TN, "BinaryDataName" },
{ 0x0077, 0x0022, 0, VR::CS, VM::M1TN, "NumberOfSOPInstanceUID" },
{ 0x0077, 0x0024, 0, VR::CS, VM::M1TN, "NumberOfSeriesInstanceUID" },
{ 0x0077, 0x0026, 0, VR::US, VM::M1, "NumberOfBinaryData" },
{ 0x0077, 0x0028, 0, VR::CS, VM::M1TN, "BinaryDataType" },
{ 0x0077, 0x0030, 0, VR::UL, VM::M1TN, "BinaryDataSize" },
{ 0x0077, 0x0032, 0, VR::LO, VM::M1TN, "BinaryDataSubType" },
{ 0x0077, 0x0040, 0, VR::LO, VM::M1TN, "AdditionalInformation" },
{ 0x0077, 0x0050, 0, VR::OB, VM::M1, "FirstBinaryData" },
{ 0x0077, 0x0060, 0, VR::OB, VM::M1, "FirstThumbnail" },
{ 0x0077, 0x0070, 0, VR::LO, VM::M1, "AlgorithmID" },
{ 0x0077, 0x0080, 0, VR::LO, VM::M1, "VolumeID" },
{ 0x0077, 0x0084, 0, VR::LO, VM::M1TN, "COFObjectUID" },
{ 0x0077, 0x0086, 0, VR::LO, VM::M1TN, "WorkflowSceneStatus" },
{ 0x0077, 0x0088, 0, VR::UI, VM::M1TN, "ReferenceSOPInstanceUIDs" },
{ 0x0077, 0x0090, 0, VR::FL, VM::M1, "COFRefinementLevel" },
};

unsigned short Dict035TagHashTable[] = {
    6,    17,    22,    33,    42,     0,     5,     1,    18,     7,
   38,     9,    48,    11,    64,    16,   132,     2,     3,    22,
    4,    32,     5,     0,    16,     6,    36,    14,   112,    17,
  134,    18,   136,     4,     2,    20,    10,    50,    13,    96,
   19,   144,     4,     5,    34,     8,    40,    12,    80,    15,
  128,
};

vtkDICOMDictionary::Dict Dict035Data = {
"TERARECON AQUARIUS",
5,
20,
Dict035TagHashTable,
Dict035Contents
};

// ----- TOSHIBA COMAPL OOG -----

DictEntry Dict036Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "COMAPLOOGType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "COMAPLOOGVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "COMAPLOOGInfo" },
};

unsigned short Dict036TagHashTable[] = {
    2,     0,     3,     0,     8,     1,     9,     2,    16,
};

vtkDICOMDictionary::Dict Dict036Data = {
"TOSHIBA COMAPL OOG",
1,
3,
Dict036TagHashTable,
Dict036Contents
};

// ----- SYNARC_1.0 -----

DictEntry Dict037Contents[] = {
{ 0x0099, 0x0001, 0, VR::OB, VM::M1, "" },
{ 0x0099, 0x0002, 0, VR::OB, VM::M1, "" },
{ 0x0099, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x0099, 0x0004, 0, VR::US, VM::M1TN, "" },
{ 0x0099, 0x0005, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict037TagHashTable[] = {
    2,     0,     5,     0,     1,     1,     2,     2,     3,     3,
    4,     4,     5,
};

vtkDICOMDictionary::Dict Dict037Data = {
"SYNARC_1.0",
1,
5,
Dict037TagHashTable,
Dict037Contents
};

// ----- LORAD Selenia -----

DictEntry Dict038Contents[] = {
{ 0x0019, 0x0006, 0, VR::LO, VM::M1, "PaddleID" },
{ 0x0019, 0x0007, 0, VR::SH, VM::M1, "PaddlePosition" },
{ 0x0019, 0x0008, 0, VR::LO, VM::M1, "CollimationSize" },
{ 0x0019, 0x0016, 0, VR::DS, VM::M1, "PaddleAngle" },
{ 0x0019, 0x0026, 0, VR::LO, VM::M1, "PaddleIDDescription" },
{ 0x0019, 0x0027, 0, VR::SH, VM::M1, "PaddlePositionDescription" },
{ 0x0019, 0x0028, 0, VR::LO, VM::M1, "CollimationSizeDescription" },
{ 0x0019, 0x0029, 0, VR::LO, VM::M1, "AECUserDensityScaleFactorDescription" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "AECUserDensityScaleFactor" },
{ 0x0019, 0x0031, 0, VR::US, VM::M1, "AECSystemDensityScaleFactor" },
{ 0x0019, 0x0032, 0, VR::US, VM::M1, "AECCalculatedmAs" },
{ 0x0019, 0x0033, 0, VR::US, VM::M1, "AECAutoPixel1" },
{ 0x0019, 0x0034, 0, VR::US, VM::M1, "AECAutoPixel2" },
{ 0x0019, 0x0035, 0, VR::US, VM::M1, "AECSensor" },
{ 0x0019, 0x0037, 0, VR::LO, VM::M1, "NPTMode" },
{ 0x0019, 0x0040, 0, VR::DS, VM::M1, "SkinEdge" },
{ 0x0019, 0x0041, 0, VR::DS, VM::M1, "ExposureIndex" },
{ 0x0019, 0x0050, 0, VR::DS, VM::M1, "DisplayMinimumOD" },
{ 0x0019, 0x0051, 0, VR::DS, VM::M1, "DispalyMaximumOD" },
{ 0x0019, 0x0052, 0, VR::IS, VM::M1, "DisplayMinimumNits" },
{ 0x0019, 0x0053, 0, VR::IS, VM::M1, "DisplayMaximumNits" },
{ 0x0019, 0x0060, 0, VR::LT, VM::M1, "GeometryCalibration" },
{ 0x0019, 0x0070, 0, VR::LO, VM::M1, "FrameOfReferenceID" },
{ 0x0019, 0x0071, 0, VR::CS, VM::M1, "PairedPosition" },
{ 0x0019, 0x0080, 0, VR::SH, VM::M1, "DetectorImageOffset" },
{ 0x0019, 0x0090, 0, VR::DS, VM::M1, "ConventionalTomoAngle" },
};

unsigned short Dict038TagHashTable[] = {
    7,    18,    29,    38,    49,    56,     0,     5,     1,     7,
    7,    41,    11,    51,    17,    80,    21,    96,     5,     0,
    6,     6,    40,    10,    50,    18,    81,    25,   144,     4,
    5,    39,    13,    53,    19,    82,    22,   112,     5,     3,
   22,     4,    38,    12,    52,    20,    83,    23,   113,     3,
    9,    49,    14,    55,    15,    64,     4,     2,     8,     8,
   48,    16,    65,    24,   128,
};

vtkDICOMDictionary::Dict Dict038Data = {
"LORAD Selenia",
6,
26,
Dict038TagHashTable,
Dict038Contents
};

// ----- SIEMENS SYNGO LAYOUT PROTOCOL -----

DictEntry Dict039Contents[] = {
{ 0x0073, 0x0002, 0, VR::US, VM::M1, "HangingProtocolExcellenceRank" },
{ 0x0073, 0x0004, 0, VR::CS, VM::M1, "TemplateDataRoleID" },
{ 0x0073, 0x0006, 0, VR::CS, VM::M1, "DataSharingFlag" },
{ 0x0073, 0x0008, 0, VR::SQ, VM::M1, "BaggingOperationsSequence" },
{ 0x0073, 0x0010, 0, VR::LO, VM::M1, "SynchronizationType" },
{ 0x0073, 0x0012, 0, VR::LO, VM::M1, "CustomFilterType" },
{ 0x0073, 0x0014, 0, VR::LO, VM::M1, "CustomSorterType" },
{ 0x0073, 0x0016, 0, VR::CS, VM::M1, "ReferenceTemplateDataRoleID" },
{ 0x0073, 0x0018, 0, VR::CS, VM::M1, "ModelTemplateDataRoleID" },
{ 0x0073, 0x0020, 0, VR::DT, VM::M1TN, "SelectorDTValue" },
{ 0x0073, 0x0022, 0, VR::DA, VM::M1TN, "SelectorDAValue" },
{ 0x0073, 0x0024, 0, VR::TM, VM::M1TN, "SelectorTMValue" },
{ 0x0073, 0x0026, 0, VR::UI, VM::M1TN, "SelectorUIValue" },
{ 0x0073, 0x0028, 0, VR::CS, VM::M1, "ReferencedTemplateDataRole" },
{ 0x0073, 0x0030, 0, VR::SQ, VM::M1, "CustomPropertySequence" },
{ 0x0073, 0x0032, 0, VR::CS, VM::M1, "CustomPropertyType" },
{ 0x0073, 0x0034, 0, VR::LO, VM::M1, "CustomPropertyName" },
{ 0x0073, 0x0036, 0, VR::LO, VM::M1, "CustomPropertyValue" },
{ 0x0073, 0x0038, 0, VR::SQ, VM::M1, "LayoutPropertySequence" },
{ 0x0073, 0x0040, 0, VR::SQ, VM::M1, "SynchronizationSequence" },
{ 0x0073, 0x0042, 0, VR::CS, VM::M1, "PresentationCreatorType" },
{ 0x0073, 0x0044, 0, VR::CS, VM::M1, "CineNavigationType" },
{ 0x0073, 0x0046, 0, VR::CS, VM::M1, "InternalFlag" },
{ 0x0073, 0x0048, 0, VR::LO, VM::M1, "SemanticNamingStrategy" },
{ 0x0073, 0x0050, 0, VR::LO, VM::M1, "ParameterString" },
{ 0x0073, 0x0052, 0, VR::CS, VM::M1, "SortingOrder" },
{ 0x0073, 0x0054, 0, VR::CS, VM::M1, "syngoTemplateType" },
{ 0x0073, 0x0056, 0, VR::CS, VM::M1, "SorterType" },
{ 0x0073, 0x0058, 0, VR::SH, VM::M1, "DataDisplayProtocolVersion" },
{ 0x0073, 0x005A, 0, VR::CS, VM::M1, "TimepointValue" },
{ 0x0073, 0x005B, 0, VR::CS, VM::M1, "SharingGroupSequence" },
{ 0x0073, 0x005C, 0, VR::CS, VM::M1, "TemplateSelectorOperator" },
{ 0x0073, 0x005D, 0, VR::CS, VM::M1, "SharingType" },
{ 0x0073, 0x0060, 0, VR::SQ, VM::M1, "ViewportDefinitionsSequence" },
{ 0x0073, 0x0062, 0, VR::CS, VM::M1, "ProtocolType" },
{ 0x0073, 0x0064, 0, VR::SQ, VM::M1, "TemplateSelectorSequence" },
{ 0x0073, 0x0066, 0, VR::CS, VM::M1, "DefaultTemplate" },
{ 0x0073, 0x0068, 0, VR::CS, VM::M1, "IsPreferred" },
{ 0x0073, 0x006A, 0, VR::SQ, VM::M1, "TimepointInitialValueSequence" },
{ 0x0073, 0x006C, 0, VR::CS, VM::M1, "TimepointVariable" },
{ 0x0073, 0x0070, 0, VR::SH, VM::M1, "DisplayProtocolName" },
{ 0x0073, 0x0072, 0, VR::LO, VM::M1, "DisplayProtocolDescription" },
{ 0x0073, 0x0074, 0, VR::CS, VM::M1, "DisplayProtocolLevel" },
{ 0x0073, 0x0076, 0, VR::LO, VM::M1, "DisplayProtocolCreator" },
{ 0x0073, 0x0078, 0, VR::DT, VM::M1, "DisplayProtocolCreationDatetime" },
{ 0x0073, 0x007A, 0, VR::UI, VM::M1, "ReferencedDataProtocol" },
{ 0x0073, 0x007C, 0, VR::US, VM::M1, "DisplayProtocolExcellenceRank" },
{ 0x0073, 0x007E, 0, VR::SQ, VM::M1, "LayoutSequence" },
{ 0x0073, 0x0080, 0, VR::US, VM::M1, "LayoutNumber" },
{ 0x0073, 0x0082, 0, VR::LO, VM::M1, "LayoutDescription" },
{ 0x0073, 0x0084, 0, VR::SQ, VM::M1, "SegmentSequence" },
{ 0x0073, 0x0086, 0, VR::US, VM::M1, "SegmentNumber" },
{ 0x0073, 0x0088, 0, VR::LO, VM::M1, "SegmentDescription" },
{ 0x0073, 0x008A, 0, VR::CS, VM::M1, "SegmentType" },
{ 0x0073, 0x008C, 0, VR::US, VM::M1, "TileHorizontalDimension" },
{ 0x0073, 0x008E, 0, VR::US, VM::M1, "TileVerticalDimension" },
{ 0x0073, 0x0090, 0, VR::CS, VM::M1, "FillOrder" },
{ 0x0073, 0x0092, 0, VR::CS, VM::M1, "SegmentSmallScrollType" },
{ 0x0073, 0x0094, 0, VR::US, VM::M1, "SegmentSmallScrollAmount" },
{ 0x0073, 0x0096, 0, VR::CS, VM::M1, "SegmentLargeScrollType" },
{ 0x0073, 0x0098, 0, VR::US, VM::M1, "SegmentLargeScrollAmount" },
{ 0x0073, 0x009A, 0, VR::US, VM::M1, "SegmentOverlapPriority" },
{ 0x0073, 0x009C, 0, VR::SQ, VM::M1, "DataRoleViewSequence" },
{ 0x0073, 0x009E, 0, VR::US, VM::M1, "DataRoleViewNumber" },
{ 0x0073, 0x00A2, 0, VR::US, VM::M1, "ReferencedDataRole" },
{ 0x0073, 0x00A4, 0, VR::CS, VM::M1, "SharingEnabled" },
{ 0x0073, 0x00A8, 0, VR::US, VM::M2TN, "ReferencedDataRoleViews" },
{ 0x0073, 0x00B0, 0, VR::SH, VM::M1, "DataProtocolName" },
{ 0x0073, 0x00B2, 0, VR::LO, VM::M1, "DataProtocolDescription" },
{ 0x0073, 0x00B4, 0, VR::CS, VM::M1, "DataProtocolLevel" },
{ 0x0073, 0x00B6, 0, VR::LO, VM::M1, "DataProtocolCreator" },
{ 0x0073, 0x00B8, 0, VR::DT, VM::M1, "DataProtocolCreationDatetime" },
{ 0x0073, 0x00BA, 0, VR::US, VM::M1, "DataProtocolExcellenceRank" },
{ 0x0073, 0x00BC, 0, VR::SQ, VM::M1, "DataProtocolDefinitionSequence" },
{ 0x0073, 0x00BE, 0, VR::SQ, VM::M1, "DataRoleSequence" },
{ 0x0073, 0x00C0, 0, VR::US, VM::M1, "DataRoleNumber" },
{ 0x0073, 0x00C2, 0, VR::SH, VM::M1, "DataRoleName" },
{ 0x0073, 0x00C6, 0, VR::SQ, VM::M1, "SelectorOperationsSequence" },
{ 0x0073, 0x00C8, 0, VR::CS, VM::M1, "SelectorUsageFlag" },
{ 0x0073, 0x00CA, 0, VR::CS, VM::M1, "SelectByAttributePresence" },
{ 0x0073, 0x00CC, 0, VR::CS, VM::M1, "SelectByCategory" },
{ 0x0073, 0x00CE, 0, VR::CS, VM::M1, "SelectByOperator" },
{ 0x0073, 0x00D0, 0, VR::LO, VM::M1, "CustomSelectorType" },
{ 0x0073, 0x00D2, 0, VR::CS, VM::M1, "SelectorOperator" },
{ 0x0073, 0x00D4, 0, VR::CS, VM::M1, "ReformattingRequired" },
{ 0x0073, 0x00D6, 0, VR::SQ, VM::M1, "RegistrationDataSequence" },
{ 0x0073, 0x00D8, 0, VR::US, VM::M1, "ReferenceDataRoleNumber" },
{ 0x0073, 0x00DA, 0, VR::SQ, VM::M1, "ModelDataSequence" },
{ 0x0073, 0x00DC, 0, VR::US, VM::M1, "ModelDataRoleNumber" },
{ 0x0073, 0x00DE, 0, VR::SQ, VM::M1, "FusionDisplaySequence" },
{ 0x0073, 0x00E0, 0, VR::FD, VM::M1, "Transparency" },
{ 0x0073, 0x00E2, 0, VR::CS, VM::M1, "TimePoint" },
{ 0x0073, 0x00E4, 0, VR::LO, VM::M1, "FirstTimePointToken" },
{ 0x0073, 0x00E6, 0, VR::LO, VM::M1, "LastTimePointToken" },
{ 0x0073, 0x00E8, 0, VR::LO, VM::M1, "IntermediateTimePointToken" },
{ 0x0073, 0x00EA, 0, VR::SQ, VM::M1, "DataProcessorSequence" },
{ 0x0073, 0x00EC, 0, VR::LO, VM::M1, "DataProcessorType" },
{ 0x0073, 0x00EE, 0, VR::SQ, VM::M1, "TemplateDataRoleSequence" },
{ 0x0073, 0x00F0, 0, VR::SQ, VM::M1, "ViewSequence" },
{ 0x0073, 0x00F4, 0, VR::LO, VM::M1, "ViewType" },
{ 0x0073, 0x00F6, 0, VR::LO, VM::M1, "CustomBaggingType" },
{ 0x0073, 0x00F8, 0, VR::US, VM::M1, "ReferencedDisplaySegmentNumber" },
{ 0x0073, 0x00FA, 0, VR::LO, VM::M1, "DataRoleType" },
{ 0x0073, 0x00FC, 0, VR::CS, VM::M1, "UnassignedFlag" },
{ 0x0073, 0x00FE, 0, VR::CS, VM::M1, "InitialDisplayScrollPosition" },
{ 0x0073, 0x00FF, 0, VR::LO, VM::M1, "VRTPreset" },
};

unsigned short Dict039TagHashTable[] = {
   27,    30,    41,    50,    61,    68,    79,    84,    97,   106,
  117,   122,   131,   144,   153,   164,   173,   182,   191,   204,
  211,   222,   231,   240,   249,   256,     0,     1,    61,   154,
    5,    22,    70,    37,   104,    41,   114,    77,   198,    96,
  236,     4,     8,    24,    10,    34,    62,   156,    64,   162,
    5,    21,    68,    40,   112,    78,   200,    97,   238,    99,
  244,     3,     9,    32,    63,   158,    65,   164,     5,    39,
  108,    43,   118,    79,   202,    82,   208,   100,   246,     2,
   12,    38,    48,   128,     6,    23,    72,    25,    82,    42,
  116,    80,   204,    83,   210,   101,   248,     4,     0,     2,
   11,    36,    49,   130,    66,   168,     5,    24,    80,    45,
  122,    81,   206,    84,   212,   102,   250,     2,    50,   132,
   67,   176,     4,    27,    86,    44,   120,    85,   214,   103,
  252,     6,     2,     6,    13,    40,    15,    50,    51,   134,
   68,   178,   105,   255,     4,    26,    84,    47,   126,    86,
  216,   104,   254,     5,     1,     4,    14,    48,    30,    91,
   52,   136,    69,   180,     4,    29,    90,    46,   124,    87,
  218,    90,   224,     4,    17,    54,    53,   138,    56,   144,
   70,   182,     4,    28,    88,    34,    98,    88,   220,    91,
  226,     6,     3,     8,     5,    18,    16,    52,    54,   140,
   57,   146,    71,   184,     3,    33,    96,    89,   222,    92,
  228,     5,     4,    16,    32,    93,    55,   142,    58,   148,
   72,   186,     4,    31,    92,    36,   102,    75,   192,    93,
  230,     4,     7,    22,    18,    56,    59,   150,    73,   188,
    4,    20,    66,    35,   100,    76,   194,    94,   232,     3,
    6,    20,    60,   152,    74,   190,     4,    19,    64,    38,
  106,    95,   234,    98,   240,
};

vtkDICOMDictionary::Dict Dict039Data = {
"SIEMENS SYNGO LAYOUT PROTOCOL",
26,
106,
Dict039TagHashTable,
Dict039Contents
};

// ----- SIEMENS MR VA0  RAW -----

DictEntry Dict040Contents[] = {
{ 0x0021, 0x0000, 0, VR::CS, VM::M1, "SequenceType" },
{ 0x0021, 0x0001, 0, VR::IS, VM::M1, "VectorSizeOriginal" },
{ 0x0021, 0x0002, 0, VR::IS, VM::M1, "VectorSizeExtended" },
{ 0x0021, 0x0003, 0, VR::DS, VM::M1, "AcquiredSpectralRange" },
{ 0x0021, 0x0004, 0, VR::DS, VM::M3, "VOIPosition" },
{ 0x0021, 0x0005, 0, VR::DS, VM::M3, "VOISize" },
{ 0x0021, 0x0006, 0, VR::IS, VM::M3, "CSIMatrixSizeOriginal" },
{ 0x0021, 0x0007, 0, VR::IS, VM::M3, "CSIMatrixSizeExtended" },
{ 0x0021, 0x0008, 0, VR::DS, VM::M3, "SpatialGridShift" },
{ 0x0021, 0x0009, 0, VR::DS, VM::M1, "SignalLimitsMinimum" },
{ 0x0021, 0x0010, 0, VR::DS, VM::M1, "SignalLimitsMaximum" },
{ 0x0021, 0x0011, 0, VR::DS, VM::M1, "SpecInfoMask" },
{ 0x0021, 0x0012, 0, VR::DS, VM::M1, "EPITimeRateOfChangeOfMagnitude" },
{ 0x0021, 0x0013, 0, VR::DS, VM::M1, "EPITimeRateOfChangeOfXComponent" },
{ 0x0021, 0x0014, 0, VR::DS, VM::M1, "EPITimeRateOfChangeOfYComponent" },
{ 0x0021, 0x0015, 0, VR::DS, VM::M1, "EPITimeRateOfChangeOfZComponent" },
{ 0x0021, 0x0016, 0, VR::DS, VM::M1, "EPITimeRateOfChangeLegalLimit1" },
{ 0x0021, 0x0017, 0, VR::IS, VM::M1, "EPIOperationModeFlag" },
{ 0x0021, 0x0018, 0, VR::DS, VM::M1, "EPIFieldCalculationSafetyFactor" },
{ 0x0021, 0x0019, 0, VR::DS, VM::M1, "EPILegalLimit1OfChangeValue" },
{ 0x0021, 0x0020, 0, VR::DS, VM::M1, "EPILegalLimit2OfChangeValue" },
{ 0x0021, 0x0021, 0, VR::DS, VM::M1, "EPIRiseTime" },
{ 0x0021, 0x0030, 0, VR::DS, VM::M16, "ArrayCoilADCOffset" },
{ 0x0021, 0x0031, 0, VR::DS, VM::M16, "ArrayCoilPreamplifierGain" },
{ 0x0021, 0x0050, 0, VR::LO, VM::M1, "SaturationType" },
{ 0x0021, 0x0051, 0, VR::DS, VM::M3, "SaturationNormalVector" },
{ 0x0021, 0x0052, 0, VR::DS, VM::M3, "SaturationPositionVector" },
{ 0x0021, 0x0053, 0, VR::DS, VM::M6, "SaturationThickness" },
{ 0x0021, 0x0054, 0, VR::DS, VM::M6, "SaturationWidth" },
{ 0x0021, 0x0055, 0, VR::DS, VM::M6, "SaturationDistance" },
};

unsigned short Dict040TagHashTable[] = {
    8,    19,    30,    39,    48,    57,    66,     0,     5,     2,
    2,    10,    16,    19,    25,    21,    33,    24,    80,     5,
    5,     5,    13,    19,    18,    24,    20,    32,    25,    81,
    4,     4,     4,    12,    18,    23,    49,    26,    82,     4,
    7,     7,    15,    21,    22,    48,    27,    83,     4,     1,
    1,     6,     6,    14,    20,    28,    84,     4,     0,     0,
    9,     9,    17,    23,    29,    85,     4,     3,     3,     8,
    8,    11,    17,    16,    22,
};

vtkDICOMDictionary::Dict Dict040Data = {
"SIEMENS MR VA0  RAW",
7,
30,
Dict040TagHashTable,
Dict040Contents
};

// ----- SIEMENS CM VA0  LAB -----

DictEntry Dict041Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "GeneratorIdentificationLabel" },
{ 0x0009, 0x0011, 0, VR::LO, VM::M1, "GantryIdentificationLabel" },
{ 0x0009, 0x0012, 0, VR::LO, VM::M1, "XRayTubeIdentificationLabel" },
{ 0x0009, 0x0013, 0, VR::LO, VM::M1, "DetectorIdentificationLabel" },
{ 0x0009, 0x0014, 0, VR::LO, VM::M1, "DASIdentificationLabel" },
{ 0x0009, 0x0015, 0, VR::LO, VM::M1, "SMIIdentificationLabel" },
{ 0x0009, 0x0016, 0, VR::LO, VM::M1, "CPUIdentificationLabel" },
{ 0x0009, 0x0020, 0, VR::SH, VM::M1, "HeaderVersion" },
};

unsigned short Dict041TagHashTable[] = {
    3,    10,     0,     3,     1,    17,     3,    19,     5,    21,
    5,     0,    16,     2,    18,     4,    20,     6,    22,     7,
   32,
};

vtkDICOMDictionary::Dict Dict041Data = {
"SIEMENS CM VA0  LAB",
2,
8,
Dict041TagHashTable,
Dict041Contents
};

// ----- http://www.gemedicalsystems.com/it_solutions/orthoview/2.1 -----

DictEntry Dict042Contents[] = {
{ 0x3117, 0x0010, 0, VR::DT, VM::M1, "OrthoView Session Date/Time" },
{ 0x3117, 0x0020, 0, VR::PN, VM::M1, "OrthoView Session Creator" },
{ 0x3117, 0x0030, 0, VR::CS, VM::M1, "OrthoView Session Completion Flag" },
{ 0x3117, 0x0040, 0, VR::SQ, VM::M1, "OrthoView File Sequence" },
{ 0x3117, 0x0050, 0, VR::ST, VM::M1, "OrthoView File Name" },
{ 0x3117, 0x0060, 0, VR::OB, VM::M1, "OrthoView File Content" },
};

unsigned short Dict042TagHashTable[] = {
    2,     0,     6,     0,    16,     1,    32,     2,    48,     3,
   64,     4,    80,     5,    96,
};

vtkDICOMDictionary::Dict Dict042Data = {
"http://www.gemedicalsystems.com/it_solutions/orthoview/2.1",
1,
6,
Dict042TagHashTable,
Dict042Contents
};

// ----- PHILIPS NM -Private -----

DictEntry Dict043Contents[] = {
{ 0x7051, 0x0000, 0, VR::US, VM::M1, "CurrentSegment" },
{ 0x7051, 0x0001, 0, VR::US, VM::M1, "NumberOfSegments" },
{ 0x7051, 0x0002, 0, VR::FL, VM::M1, "SegmentStartPosition" },
{ 0x7051, 0x0003, 0, VR::FL, VM::M1, "SegmentStopPosition" },
{ 0x7051, 0x0004, 0, VR::FL, VM::M1, "RelativeCOROffsetXDirection" },
{ 0x7051, 0x0005, 0, VR::FL, VM::M1, "RelativeCOROffsetZDirection" },
{ 0x7051, 0x0006, 0, VR::US, VM::M1, "CurrentRotationNumber" },
{ 0x7051, 0x0007, 0, VR::US, VM::M1, "NumberOfRotations" },
{ 0x7051, 0x0010, 0, VR::DS, VM::M1TN, "AlignmentTranslations" },
{ 0x7051, 0x0011, 0, VR::DS, VM::M1TN, "AlignmentRotations" },
{ 0x7051, 0x0012, 0, VR::DS, VM::M1, "AlignmentTimestamp" },
{ 0x7051, 0x0015, 0, VR::UI, VM::M1, "RelatedXraySeriesInstanceUID" },
{ 0x7051, 0x0025, 0, VR::LO, VM::M1, "" },
{ 0x7051, 0x0026, 0, VR::DS, VM::M1, "" },
{ 0x7051, 0x0027, 0, VR::IS, VM::M1, "" },
{ 0x7051, 0x0028, 0, VR::IS, VM::M1, "" },
{ 0x7051, 0x0029, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict043TagHashTable[] = {
    5,    14,    27,    36,     0,     4,     0,     0,     4,     4,
    8,    16,    15,    40,     6,     1,     1,     5,     5,     9,
   17,    11,    21,    12,    37,    16,    41,     4,     2,     2,
    6,     6,    10,    18,    13,    38,     3,     3,     3,     7,
    7,    14,    39,
};

vtkDICOMDictionary::Dict Dict043Data = {
"PHILIPS NM -Private",
4,
17,
Dict043TagHashTable,
Dict043Contents
};

// ----- SIEMENS WH SR 1.0 -----

DictEntry Dict044Contents[] = {
{ 0x0071, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0071, 0x0002, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict044TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     2,
};

vtkDICOMDictionary::Dict Dict044Data = {
"SIEMENS WH SR 1.0",
1,
2,
Dict044TagHashTable,
Dict044Contents
};

// ----- PMOD_1 -----

DictEntry Dict045Contents[] = {
{ 0x0055, 0x0001, 0, VR::FD, VM::M1TN, "FrameStartTimesVector" },
{ 0x0055, 0x0002, 0, VR::FD, VM::M3T3N, "FramePositionsVector" },
{ 0x0055, 0x0003, 0, VR::FD, VM::M6T6N, "FrameOrientationsVector" },
{ 0x0055, 0x0004, 0, VR::FD, VM::M1TN, "FrameDurationsVector" },
{ 0x0055, 0x0005, 0, VR::FD, VM::M1TN, "FrameRescaleSlopeVector" },
};

unsigned short Dict045TagHashTable[] = {
    2,     0,     5,     0,     1,     1,     2,     2,     3,     3,
    4,     4,     5,
};

vtkDICOMDictionary::Dict Dict045Data = {
"PMOD_1",
1,
5,
Dict045TagHashTable,
Dict045Contents
};

// ----- SIEMENS MED MG -----

DictEntry Dict046Contents[] = {
{ 0x0029, 0x0010, 0, VR::US, VM::M1, "ListOfGroupNumbers" },
{ 0x0029, 0x0015, 0, VR::LO, VM::M1, "ListOfShadowOwnerCodes" },
{ 0x0029, 0x0020, 0, VR::US, VM::M1, "ListOfElementNumbers" },
{ 0x0029, 0x0030, 0, VR::US, VM::M1, "ListOfTotalDisplayLength" },
{ 0x0029, 0x0040, 0, VR::LO, VM::M1TN, "ListOfDisplayPrefix" },
{ 0x0029, 0x0050, 0, VR::LO, VM::M1TN, "ListOfDisplayPostfix" },
{ 0x0029, 0x0060, 0, VR::US, VM::M1, "ListOfTextPosition" },
{ 0x0029, 0x0070, 0, VR::LO, VM::M1, "ListOfTextConcatenation" },
};

unsigned short Dict046TagHashTable[] = {
    3,    14,     0,     5,     1,    21,     4,    64,     5,    80,
    6,    96,     7,   112,     3,     0,    16,     2,    32,     3,
   48,
};

vtkDICOMDictionary::Dict Dict046Data = {
"SIEMENS MED MG",
2,
8,
Dict046TagHashTable,
Dict046Contents
};

// ----- GEMS_CTHD_01 -----

DictEntry Dict047Contents[] = {
{ 0x0033, 0x0002, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict047TagHashTable[] = {
    2,     0,     1,     0,     2,
};

vtkDICOMDictionary::Dict Dict047Data = {
"GEMS_CTHD_01",
1,
1,
Dict047TagHashTable,
Dict047Contents
};

// ----- astm.org/diconde/iod/Component -----

DictEntry Dict048Contents[] = {
{ 0x0011, 0x0023, 0, VR::ST, VM::M1TN, "CADFileFormat" },
{ 0x0011, 0x0024, 0, VR::ST, VM::M1TN, "ComponentReferenceSystem" },
{ 0x0011, 0x0025, 0, VR::ST, VM::M1TN, "ComponentManufacturingProcedure" },
{ 0x0011, 0x0028, 0, VR::ST, VM::M1TN, "ComponentManufacturer" },
{ 0x0011, 0x0030, 0, VR::DS, VM::M1TN, "MaterialThickness" },
{ 0x0011, 0x0032, 0, VR::DS, VM::M1TN, "MaterialPipeDiameter" },
{ 0x0011, 0x0034, 0, VR::DS, VM::M1TN, "MaterialIsolationDiameter" },
{ 0x0011, 0x0042, 0, VR::ST, VM::M1TN, "MaterialGrade" },
{ 0x0011, 0x0044, 0, VR::ST, VM::M1TN, "MaterialPropertiesFileID" },
{ 0x0011, 0x0045, 0, VR::ST, VM::M1TN, "MaterialPropertiesFileFormat" },
{ 0x0011, 0x0046, 0, VR::LT, VM::M1, "MaterialNotes" },
{ 0x0011, 0x0050, 0, VR::CS, VM::M1, "ComponentShape" },
{ 0x0011, 0x0052, 0, VR::CS, VM::M1, "CurvatureType" },
{ 0x0011, 0x0054, 0, VR::DS, VM::M1, "OuterDiameter" },
{ 0x0011, 0x0056, 0, VR::DS, VM::M1, "InnerDiameter" },
};

unsigned short Dict048TagHashTable[] = {
    4,    13,    26,     0,     4,     3,    40,     4,    48,     8,
   68,    12,    82,     6,     2,    37,     6,    52,     7,    66,
    9,    69,    11,    80,    14,    86,     5,     0,    35,     1,
   36,     5,    50,    10,    70,    13,    84,
};

vtkDICOMDictionary::Dict Dict048Data = {
"astm.org/diconde/iod/Component",
3,
15,
Dict048TagHashTable,
Dict048Contents
};

// ----- PMOD_GENPET -----

DictEntry Dict049Contents[] = {
{ 0x7fe1, 0x0001, 0, VR::UT, VM::M1, "SlicesNames" },
{ 0x7fe1, 0x0002, 0, VR::UT, VM::M1, "GeneCodes" },
{ 0x7fe1, 0x0003, 0, VR::UT, VM::M1, "GeneLabels" },
};

unsigned short Dict049TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,     3,
};

vtkDICOMDictionary::Dict Dict049Data = {
"PMOD_GENPET",
1,
3,
Dict049TagHashTable,
Dict049Contents
};

// ----- SHS MagicView 300 -----

DictEntry Dict050Contents[] = {
{ 0x0029, 0x0002, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x0003, 0, VR::FD, VM::M1, "" },
};

unsigned short Dict050TagHashTable[] = {
    2,     0,     2,     0,     2,     1,     3,
};

vtkDICOMDictionary::Dict Dict050Data = {
"SHS MagicView 300",
1,
2,
Dict050TagHashTable,
Dict050Contents
};

// ----- INTELERAD MEDICAL SYSTEMS INTELEVIEWER -----

DictEntry Dict051Contents[] = {
{ 0x0071, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0071, 0x0002, 0, VR::LO, VM::M1, "" },
{ 0x0071, 0x0003, 0, VR::UN, VM::M1, "" },
{ 0x0071, 0x0004, 0, VR::UN, VM::M1, "" },
{ 0x0071, 0x0005, 0, VR::UN, VM::M1, "" },
{ 0x0071, 0x0006, 0, VR::UN, VM::M1, "" },
{ 0x0071, 0x0007, 0, VR::UN, VM::M1, "" },
{ 0x0071, 0x000A, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict051TagHashTable[] = {
    3,    12,     0,     4,     1,     2,     3,     4,     5,     6,
    7,    10,     4,     0,     1,     2,     3,     4,     5,     6,
    7,
};

vtkDICOMDictionary::Dict Dict051Data = {
"INTELERAD MEDICAL SYSTEMS INTELEVIEWER",
2,
8,
Dict051TagHashTable,
Dict051Contents
};

// ----- SIEMENS IKM CKS CXRCAD FINDINGS -----

DictEntry Dict052Contents[] = {
{ 0x0029, 0x0001, 0, VR::UT, VM::M1, "" },
};

unsigned short Dict052TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict052Data = {
"SIEMENS IKM CKS CXRCAD FINDINGS",
1,
1,
Dict052TagHashTable,
Dict052Contents
};

// ----- SIEMENS NUMARIS II -----

DictEntry Dict053Contents[] = {
{ 0x7fe3, 0x0000, 0, VR::LO, VM::M1, "ImageGraphicsFormatCode" },
{ 0x7fe3, 0x0010, 0, VR::OB, VM::M1, "ImageGraphics" },
{ 0x7fe3, 0x0020, 0, VR::OB, VM::M1, "ImageGraphicsDummy" },
};

unsigned short Dict053TagHashTable[] = {
    2,     0,     3,     0,     0,     1,    16,     2,    32,
};

vtkDICOMDictionary::Dict Dict053Data = {
"SIEMENS NUMARIS II",
1,
3,
Dict053TagHashTable,
Dict053Contents
};

// ----- REPORT_FROM_APP -----

DictEntry Dict054Contents[] = {
{ 0x0039, 0x0095, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict054TagHashTable[] = {
    2,     0,     1,     0,   149,
};

vtkDICOMDictionary::Dict Dict054Data = {
"REPORT_FROM_APP",
1,
1,
Dict054TagHashTable,
Dict054Contents
};

// ----- KINETDX -----

DictEntry Dict055Contents[] = {
{ 0x0021, 0x00a5, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x00a8, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x00aa, 0, VR::OB, VM::M1, "" },
{ 0x0021, 0x00ab, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x00ac, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict055TagHashTable[] = {
    2,     0,     5,     0,   165,     1,   168,     2,   170,     3,
  171,     4,   172,
};

vtkDICOMDictionary::Dict Dict055Data = {
"KINETDX",
1,
5,
Dict055TagHashTable,
Dict055Contents
};

// ----- SIEMENS SYNGO WORKFLOW -----

DictEntry Dict056Contents[] = {
{ 0x0031, 0x0010, 0, VR::UI, VM::M1, "InternalPatientUID" },
{ 0x0031, 0x0011, 0, VR::SH, VM::M1, "PatientsDeathIndicator" },
{ 0x0031, 0x0012, 0, VR::DA, VM::M1, "PatientsDeathDate" },
{ 0x0031, 0x0013, 0, VR::TM, VM::M1, "PatientsDeathTime" },
{ 0x0031, 0x0014, 0, VR::SH, VM::M1, "VIPIndicator" },
{ 0x0031, 0x0015, 0, VR::US, VM::M1, "EmergencyFlag" },
{ 0x0031, 0x0020, 0, VR::SH, VM::M1, "InternalVisitUID" },
{ 0x0031, 0x0025, 0, VR::SH, VM::M1, "InternalISRUID" },
{ 0x0031, 0x0032, 0, VR::SH, VM::M1, "ControlState" },
{ 0x0031, 0x0034, 0, VR::US, VM::M1, "LocalFlag" },
{ 0x0031, 0x0036, 0, VR::UI, VM::M1TN, "ReferencedStudies" },
{ 0x0031, 0x0040, 0, VR::LO, VM::M1, "WorkflowID" },
{ 0x0031, 0x0041, 0, VR::LO, VM::M1, "WorkflowDescription" },
{ 0x0031, 0x0042, 0, VR::LO, VM::M1, "WorkflowControlState" },
{ 0x0031, 0x0043, 0, VR::US, VM::M1, "WorkflowAdHocFlag" },
{ 0x0031, 0x0044, 0, VR::US, VM::M1, "HybridFlag" },
{ 0x0031, 0x0050, 0, VR::LO, VM::M1, "WorkitemID" },
{ 0x0031, 0x0051, 0, VR::LO, VM::M1, "WorkitemName" },
{ 0x0031, 0x0052, 0, VR::LO, VM::M1, "WorkitemType" },
{ 0x0031, 0x0053, 0, VR::LO, VM::M1TN, "WorkitemRoles" },
{ 0x0031, 0x0054, 0, VR::LO, VM::M1, "WorkitemDescription" },
{ 0x0031, 0x0055, 0, VR::LO, VM::M1, "WorkitemControlState" },
{ 0x0031, 0x0056, 0, VR::LO, VM::M1, "ClaimingUser" },
{ 0x0031, 0x0057, 0, VR::LO, VM::M1, "ClaimingHost" },
{ 0x0031, 0x0058, 0, VR::LO, VM::M1, "TaskflowID" },
{ 0x0031, 0x0059, 0, VR::LO, VM::M1, "TaskflowName" },
{ 0x0031, 0x005A, 0, VR::US, VM::M1, "FailedFlag" },
{ 0x0031, 0x005B, 0, VR::DT, VM::M1, "ScheduledTime" },
{ 0x0031, 0x005C, 0, VR::US, VM::M1, "WorkitemAdHocFlag" },
{ 0x0031, 0x005D, 0, VR::US, VM::M1, "PatientUpdatePendingFlag" },
{ 0x0031, 0x005E, 0, VR::US, VM::M1, "PatientMixupFlag" },
{ 0x0031, 0x0060, 0, VR::LO, VM::M1, "ClientID" },
{ 0x0031, 0x0061, 0, VR::LO, VM::M1, "TemplateID" },
{ 0x0031, 0x0081, 0, VR::LO, VM::M1, "InstitutionName" },
{ 0x0031, 0x0082, 0, VR::ST, VM::M1, "InstitutionAddress" },
{ 0x0031, 0x0083, 0, VR::SQ, VM::M1, "InstitutionCodeSequence" },
};

unsigned short Dict056TagHashTable[] = {
   10,    19,    26,    33,    38,    43,    54,    65,    78,     0,
    4,     5,    21,    19,    83,    28,    92,    32,    97,     3,
    4,    20,    20,    84,    29,    93,     3,     7,    37,    21,
   85,    30,    94,     2,     8,    50,    22,    86,     2,    11,
   64,    23,    87,     5,     1,    17,     9,    52,    12,    65,
   24,    88,    35,   131,     5,     0,    16,    13,    66,    16,
   80,    25,    89,    34,   130,     6,     3,    19,    10,    54,
   14,    67,    17,    81,    26,    90,    33,   129,     6,     2,
   18,     6,    32,    15,    68,    18,    82,    27,    91,    31,
   96,
};

vtkDICOMDictionary::Dict Dict056Data = {
"SIEMENS SYNGO WORKFLOW",
9,
36,
Dict056TagHashTable,
Dict056Contents
};

// ----- INTELERAD MEDICAL SYSTEMS -----

DictEntry Dict057Contents[] = {
{ 0x0029, 0x0010, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0011, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0012, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0013, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0015, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0016, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0017, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::LO, VM::M1, "MD5Sum" },
{ 0x0029, 0x0021, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0022, 0, VR::US, VM::M1, "" },
{ 0x3F01, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x3F01, 0x0003, 0, VR::AE, VM::M1, "" },
{ 0x3F01, 0x0004, 0, VR::LO, VM::M1, "" },
{ 0x3F01, 0x0005, 0, VR::AE, VM::M1, "" },
{ 0x3F01, 0x0007, 0, VR::LO, VM::M1, "" },
{ 0x3F01, 0x0009, 0, VR::LO, VM::M1, "" },
{ 0x3F01, 0x000A, 0, VR::DA, VM::M1, "" },
{ 0x3F01, 0x000B, 0, VR::TM, VM::M1, "" },
{ 0x3F03, 0x0001, 0, VR::SQ, VM::M1, "" },
{ 0x3F03, 0x0002, 0, VR::DT, VM::M1, "" },
{ 0x3F03, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x3F03, 0x0004, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict057TagHashTable[] = {
    6,    15,    24,    37,    46,     0,     4,     4,    21,    10,
    1,    16,    10,    20,     3,     4,     1,    17,     9,    34,
   13,     5,    19,     2,     6,     0,    16,     6,    23,    11,
    3,    12,     4,    15,     9,    18,     1,     4,     3,    19,
    5,    22,     8,    33,    14,     7,     4,     2,    18,     7,
   32,    17,    11,    21,     4,
};

vtkDICOMDictionary::Dict Dict057Data = {
"INTELERAD MEDICAL SYSTEMS",
5,
22,
Dict057TagHashTable,
Dict057Contents
};

// ----- SIEMENS SYNGO FUNCTION ASSIGNMENT -----

DictEntry Dict058Contents[] = {
{ 0x0029, 0x0001, 0, VR::LO, VM::M1, "DataReference" },
};

unsigned short Dict058TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict058Data = {
"SIEMENS SYNGO FUNCTION ASSIGNMENT",
1,
1,
Dict058TagHashTable,
Dict058Contents
};

// ----- FFP DATA -----

DictEntry Dict059Contents[] = {
{ 0x0009, 0x0001, 0, VR::UN, VM::M1, "CRHeaderInformation" },
};

unsigned short Dict059TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict059Data = {
"FFP DATA",
1,
1,
Dict059TagHashTable,
Dict059Contents
};

// ----- astm.org/diconde/iod/ComponentStudy -----

DictEntry Dict060Contents[] = {
{ 0x0009, 0x0020, 0, VR::DA, VM::M1, "ExpiryDate" },
};

unsigned short Dict060TagHashTable[] = {
    2,     0,     1,     0,    32,
};

vtkDICOMDictionary::Dict Dict060Data = {
"astm.org/diconde/iod/ComponentStudy",
1,
1,
Dict060TagHashTable,
Dict060Contents
};

// ----- SIEMENS SYNGO INDEX SERVICE -----

DictEntry Dict061Contents[] = {
{ 0x0009, 0x0020, 0, VR::DA, VM::M1, "ObjectInsertionDate" },
{ 0x0009, 0x0030, 0, VR::SQ, VM::M1, "InstanceObjectStates" },
{ 0x0009, 0x0031, 0, VR::SQ, VM::M1, "SeriesObjectStates" },
{ 0x0009, 0x0040, 0, VR::DT, VM::M1, "LastAccessTime" },
{ 0x0009, 0x0041, 0, VR::CS, VM::M1, "DeleteProtectedStatus" },
{ 0x0009, 0x0042, 0, VR::CS, VM::M1, "ReceivedfromArchiveStatus" },
{ 0x0009, 0x0043, 0, VR::CS, VM::M1, "ArchiveStatus" },
{ 0x0009, 0x0044, 0, VR::AE, VM::M1, "Location" },
{ 0x0009, 0x0045, 0, VR::CS, VM::M1, "LogicalDeletedStatus" },
{ 0x0009, 0x0046, 0, VR::DT, VM::M1, "InsertTime" },
{ 0x0009, 0x0047, 0, VR::IS, VM::M1, "VisibleInstancesonSeriesLevel" },
{ 0x0009, 0x0048, 0, VR::IS, VM::M1, "UnarchivedInstances" },
{ 0x0009, 0x0049, 0, VR::IS, VM::M1, "VisibleInstancesonStudyLevel" },
{ 0x0009, 0x0050, 0, VR::CS, VM::M1, "HiddenInstance" },
{ 0x0009, 0x00A0, 0, VR::LO, VM::M1, "SenderSystemDeviceName" },
};

unsigned short Dict061TagHashTable[] = {
    4,    15,    26,     0,     5,     1,    48,     3,    64,     6,
   67,     9,    70,    14,   160,     5,     4,    65,     7,    68,
   10,    71,    11,    72,    13,    80,     5,     0,    32,     2,
   49,     5,    66,     8,    69,    12,    73,
};

vtkDICOMDictionary::Dict Dict061Data = {
"SIEMENS SYNGO INDEX SERVICE",
3,
15,
Dict061TagHashTable,
Dict061Contents
};

// ----- http://www.gemedicalsystems.com/it_solutions/rad_pacs/ -----

DictEntry Dict062Contents[] = {
{ 0x3115, 0x0001, 0, VR::UT, VM::M1, "Reference to pacs study" },
{ 0x3115, 0x0002, 0, VR::UT, VM::M1, "Reference to pacs image" },
{ 0x3115, 0x0003, 0, VR::CS, VM::M1, "Pacs examnotes flag" },
};

unsigned short Dict062TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,     3,
};

vtkDICOMDictionary::Dict Dict062Data = {
"http://www.gemedicalsystems.com/it_solutions/rad_pacs/",
1,
3,
Dict062TagHashTable,
Dict062Contents
};

// ----- SIEMENS CT APPL TMP DATAMODEL -----

DictEntry Dict063Contents[] = {
{ 0x0029, 0x0000, 0, VR::OB, VM::M1, "CTTaskCommonDataModel" },
};

unsigned short Dict063TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict063Data = {
"SIEMENS CT APPL TMP DATAMODEL",
1,
1,
Dict063TagHashTable,
Dict063Contents
};

// ----- CTP -----

DictEntry Dict064Contents[] = {
{ 0x0013, 0x0010, 0, VR::LO, VM::M1, "ProjectName" },
{ 0x0013, 0x0011, 0, VR::LO, VM::M1, "TrialName" },
{ 0x0013, 0x0012, 0, VR::LO, VM::M1, "SiteName" },
{ 0x0013, 0x0013, 0, VR::LO, VM::M1, "SiteID" },
};

unsigned short Dict064TagHashTable[] = {
    2,     0,     4,     0,    16,     1,    17,     2,    18,     3,
   19,
};

vtkDICOMDictionary::Dict Dict064Data = {
"CTP",
1,
4,
Dict064TagHashTable,
Dict064Contents
};

// ----- PixelMed Publishing -----

DictEntry Dict065Contents[] = {
{ 0x0021, 0x0001, 0, VR::SQ, VM::M1, "UnassignedSharedConvertedAttributesSequence" },
{ 0x0021, 0x0002, 0, VR::SQ, VM::M1, "UnassignedPerFrameConvertedAttributesSequence" },
{ 0x0021, 0x0003, 0, VR::SQ, VM::M1, "ConversionSourceAttributesSequence" },
};

unsigned short Dict065TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,     3,
};

vtkDICOMDictionary::Dict Dict065Data = {
"PixelMed Publishing",
1,
3,
Dict065TagHashTable,
Dict065Contents
};

// ----- POLYTRON-SMS 2.5 -----

DictEntry Dict066Contents[] = {
{ 0x0009, 0x0002, 0, VR::OB, VM::M1, "" },
{ 0x0009, 0x0004, 0, VR::OB, VM::M1, "" },
{ 0x0009, 0x0006, 0, VR::OB, VM::M1, "" },
{ 0x0089, 0x0010, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict066TagHashTable[] = {
    2,     0,     4,     0,     2,     1,     4,     2,     6,     3,
   16,
};

vtkDICOMDictionary::Dict Dict066Data = {
"POLYTRON-SMS 2.5",
1,
4,
Dict066TagHashTable,
Dict066Contents
};

// ----- Philips Imaging DD 129 -----

DictEntry Dict067Contents[] = {
{ 0x2001, 0x0000, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x0001, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict067TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict067Data = {
"Philips Imaging DD 129",
1,
2,
Dict067TagHashTable,
Dict067Contents
};

// ----- Philips Imaging DD 124 -----

DictEntry Dict068Contents[] = {
{ 0x1001, 0x0003, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict068TagHashTable[] = {
    2,     0,     1,     0,     3,
};

vtkDICOMDictionary::Dict Dict068Data = {
"Philips Imaging DD 124",
1,
1,
Dict068TagHashTable,
Dict068Contents
};

// ----- PMS-THORA-5.1 -----

DictEntry Dict069Contents[] = {
{ 0x0089, 0x0020, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict069TagHashTable[] = {
    2,     0,     1,     0,    32,
};

vtkDICOMDictionary::Dict Dict069Data = {
"PMS-THORA-5.1",
1,
1,
Dict069TagHashTable,
Dict069Contents
};

// ----- SIEMENS MED SMS USG S2000 -----

DictEntry Dict070Contents[] = {
{ 0x0019, 0x0000, 0, VR::SH, VM::M1, "PrivateCreatorVersion" },
{ 0x0019, 0x0003, 0, VR::FD, VM::M1, "FrameRate" },
{ 0x0019, 0x000C, 0, VR::US, VM::M1, "BurnedInGraphics" },
{ 0x0019, 0x000D, 0, VR::SH, VM::M1, "SieClearIndex" },
{ 0x0019, 0x000E, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::SH, VM::M1, "BModeSubmode" },
{ 0x0019, 0x0021, 0, VR::FD, VM::M1, "BModeDynamicRange" },
{ 0x0019, 0x0022, 0, VR::FD, VM::M1, "BModeOverallGain" },
{ 0x0019, 0x0023, 0, VR::US, VM::M1, "BModeResolutionSpeedIndex" },
{ 0x0019, 0x0024, 0, VR::US, VM::M1, "BModeEdgeEnhanceIndex" },
{ 0x0019, 0x0025, 0, VR::US, VM::M1, "BModePersistenceIndex" },
{ 0x0019, 0x0026, 0, VR::US, VM::M1, "BModeMapIndex" },
{ 0x0019, 0x0027, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0029, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002A, 0, VR::US, VM::M1, "BModeTintType" },
{ 0x0019, 0x002D, 0, VR::US, VM::M1, "BModeTintIndex" },
{ 0x0019, 0x002E, 0, VR::SH, VM::M1, "ClarifyVEIndex" },
{ 0x0019, 0x0030, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0031, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003A, 0, VR::US, VM::M1, "ImageFlag" },
{ 0x0019, 0x003B, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::SH, VM::M1, "ColorFlowState" },
{ 0x0019, 0x0041, 0, VR::US, VM::M1, "ColorFlowWallFilterIndex" },
{ 0x0019, 0x0042, 0, VR::SH, VM::M1, "ColorFlowSubmode" },
{ 0x0019, 0x0043, 0, VR::FD, VM::M1, "ColorFlowOverallGain" },
{ 0x0019, 0x0044, 0, VR::US, VM::M1, "ColorFlowResolutionSpeedIndex" },
{ 0x0019, 0x0046, 0, VR::US, VM::M1, "ColorFlowSmoothIndex" },
{ 0x0019, 0x0047, 0, VR::US, VM::M1, "ColorFlowPersistenceIndex" },
{ 0x0019, 0x0048, 0, VR::US, VM::M1, "ColorFlowMapIndex" },
{ 0x0019, 0x0049, 0, VR::US, VM::M1, "ColorFlowPriorityIndex" },
{ 0x0019, 0x0054, 0, VR::FD, VM::M1, "ColorFlowMaximumVelocity" },
{ 0x0019, 0x0060, 0, VR::FD, VM::M1, "DopplerDynamicRange" },
{ 0x0019, 0x0061, 0, VR::FD, VM::M1, "DopplerOverallGain" },
{ 0x0019, 0x0062, 0, VR::FD, VM::M1, "DopplerWallFilter" },
{ 0x0019, 0x0063, 0, VR::FD, VM::M1, "DopplerGateSize" },
{ 0x0019, 0x0065, 0, VR::US, VM::M1, "DopplerMapIndex" },
{ 0x0019, 0x0066, 0, VR::SH, VM::M1, "DopplerSubmode" },
{ 0x0019, 0x0067, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0069, 0, VR::US, VM::M1, "DopplerTimeFreqResIndex" },
{ 0x0019, 0x006A, 0, VR::US, VM::M1, "DopplerTraceInverted" },
{ 0x0019, 0x006C, 0, VR::US, VM::M1, "DopplerTintType" },
{ 0x0019, 0x0072, 0, VR::US, VM::M1, "DopplerTintIndex" },
{ 0x0019, 0x0080, 0, VR::US, VM::M1, "MModeDynamicRange" },
{ 0x0019, 0x0081, 0, VR::US, VM::M1, "MModeOverallGain" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "MModeEdgeEnhanceIndex" },
{ 0x0019, 0x0083, 0, VR::US, VM::M1, "MModeMapIndex" },
{ 0x0019, 0x0086, 0, VR::US, VM::M1, "MModeTintType" },
{ 0x0019, 0x0087, 0, VR::SH, VM::M1, "MModeSubmode" },
{ 0x0019, 0x0088, 0, VR::US, VM::M1, "MModeTintIndex" },
{ 0x0019, 0x0095, 0, VR::US, VM::M1, "" },
};

unsigned short Dict070TagHashTable[] = {
   13,    22,    33,    40,    49,    58,    67,    74,    81,    94,
  103,   116,     0,     4,    10,    37,    14,    41,    32,    96,
   48,   135,     5,     0,     0,     9,    36,    13,    40,    33,
   97,    47,   134,     3,     1,     3,    12,    39,    34,    98,
    4,    11,    38,    15,    42,    35,    99,    49,   136,     4,
   16,    45,    19,    49,    22,    64,    31,    84,     4,    18,
   48,    23,    65,    36,   101,    39,   105,     3,    24,    66,
   37,   102,    40,   106,     3,    17,    46,    25,    67,    38,
  103,     6,     3,    13,     6,    33,    26,    68,    29,    72,
   41,   108,    46,   131,     4,     2,    12,     5,    32,    30,
   73,    45,   130,     6,     8,    35,    21,    59,    27,    70,
   42,   114,    44,   129,    50,   149,     5,     4,    14,     7,
   34,    20,    58,    28,    71,    43,   128,
};

vtkDICOMDictionary::Dict Dict070Data = {
"SIEMENS MED SMS USG S2000",
12,
51,
Dict070TagHashTable,
Dict070Contents
};

// ----- SIEMENS MED OCS SS VERSION INFO -----

DictEntry Dict071Contents[] = {
{ 0x0039, 0x0076, 0, VR::LO, VM::M1, "StructureSetPredecessor" },
};

unsigned short Dict071TagHashTable[] = {
    2,     0,     1,     0,   118,
};

vtkDICOMDictionary::Dict Dict071Data = {
"SIEMENS MED OCS SS VERSION INFO",
1,
1,
Dict071TagHashTable,
Dict071Contents
};

// ----- ELSCINT1 -----

DictEntry Dict072Contents[] = {
{ 0x0003, 0x0001, 0, VR::OW, VM::M1, "OffsetListStructure" },
{ 0x00E1, 0x0001, 0, VR::US, VM::M1, "DataDictionaryVersion" },
{ 0x00E1, 0x0005, 0, VR::IS, VM::M1, "" },
{ 0x00E1, 0x0006, 0, VR::IS, VM::M1, "" },
{ 0x00E1, 0x0007, 0, VR::IS, VM::M1, "" },
{ 0x00E1, 0x0014, 0, VR::CS, VM::M1, "" },
{ 0x00E1, 0x0018, 0, VR::OB, VM::M1, "" },
{ 0x00E1, 0x0021, 0, VR::DS, VM::M1, "DLPTotal" },
{ 0x00E1, 0x0022, 0, VR::DS, VM::M2, "PresentationRelativeCenter" },
{ 0x00E1, 0x0023, 0, VR::DS, VM::M2, "PresentationRelativePart" },
{ 0x00E1, 0x0024, 0, VR::CS, VM::M1, "" },
{ 0x00E1, 0x0025, 0, VR::CS, VM::M1, "" },
{ 0x00E1, 0x0030, 0, VR::UI, VM::M1, "" },
{ 0x00E1, 0x0031, 0, VR::CS, VM::M1, "" },
{ 0x00E1, 0x0032, 0, VR::US, VM::M2, "" },
{ 0x00E1, 0x0037, 0, VR::DS, VM::M1, "TotalDoseSavings" },
{ 0x00E1, 0x0039, 0, VR::SQ, VM::M1, "" },
{ 0x00E1, 0x003E, 0, VR::IS, VM::M1, "" },
{ 0x00E1, 0x003F, 0, VR::CS, VM::M1, "" },
{ 0x00E1, 0x0040, 0, VR::SH, VM::M1, "ImageLabel" },
{ 0x00E1, 0x0041, 0, VR::DS, VM::M1, "" },
{ 0x00E1, 0x0042, 0, VR::LO, VM::M1, "" },
{ 0x00E1, 0x0043, 0, VR::IS, VM::M1, "" },
{ 0x00E1, 0x0050, 0, VR::DS, VM::M1, "AcquisitionDuration" },
{ 0x00E1, 0x0051, 0, VR::SH, VM::M1, "" },
{ 0x00E1, 0x0060, 0, VR::CS, VM::M1, "" },
{ 0x00E1, 0x0061, 0, VR::LO, VM::M1, "ProtocolFileName" },
{ 0x00E1, 0x0062, 0, VR::CS, VM::M1, "" },
{ 0x00E1, 0x0063, 0, VR::SH, VM::M1, "PatientLanguage" },
{ 0x00E1, 0x0065, 0, VR::LO, VM::M1, "" },
{ 0x00E1, 0x006A, 0, VR::IS, VM::M1, "" },
{ 0x00E1, 0x006B, 0, VR::IS, VM::M1, "" },
{ 0x00E1, 0x00A0, 0, VR::LO, VM::M1, "" },
{ 0x00E1, 0x00C2, 0, VR::UI, VM::M1, "" },
{ 0x00E1, 0x00C4, 0, VR::DS, VM::M1, "" },
{ 0x00E1, 0x00CF, 0, VR::IS, VM::M1, "" },
{ 0x01E1, 0x0018, 0, VR::OB, VM::M1, "" },
{ 0x01E1, 0x0021, 0, VR::ST, VM::M1, "" },
{ 0x01E1, 0x0026, 0, VR::CS, VM::M1, "PhantomType" },
{ 0x01E1, 0x0034, 0, VR::IS, VM::M1, "" },
{ 0x01E1, 0x0041, 0, VR::OW, VM::M1, "" },
{ 0x01F1, 0x0001, 0, VR::CS, VM::M1, "AcquisitionType" },
{ 0x01F1, 0x0002, 0, VR::CS, VM::M1, "FocalSpotResolution" },
{ 0x01F1, 0x0003, 0, VR::CS, VM::M1, "ConcurrentSlicesGeneration" },
{ 0x01F1, 0x0004, 0, VR::CS, VM::M1, "AngularSamplingDensity" },
{ 0x01F1, 0x0005, 0, VR::DS, VM::M1, "ReconstructionArc" },
{ 0x01F1, 0x0007, 0, VR::DS, VM::M1, "TableVelocity" },
{ 0x01F1, 0x0008, 0, VR::DS, VM::M1, "AcquisitionLength" },
{ 0x01F1, 0x000A, 0, VR::US, VM::M1, "EdgeEnhancementWeight" },
{ 0x01F1, 0x000C, 0, VR::DS, VM::M1, "ScannerRelativeCenter" },
{ 0x01F1, 0x000D, 0, VR::DS, VM::M1, "RotationAngle" },
{ 0x01F1, 0x000E, 0, VR::FL, VM::M1, "" },
{ 0x01F1, 0x0026, 0, VR::DS, VM::M1, "Pitch" },
{ 0x01F1, 0x0027, 0, VR::DS, VM::M1, "RotationTime" },
{ 0x01F1, 0x0028, 0, VR::DS, VM::M1, "TableIncrement" },
{ 0x01F1, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x01F1, 0x0032, 0, VR::CS, VM::M1, "ImageViewConvention" },
{ 0x01F1, 0x0033, 0, VR::DS, VM::M1, "CycleTime" },
{ 0x01F1, 0x0036, 0, VR::CS, VM::M1, "" },
{ 0x01F1, 0x0037, 0, VR::DS, VM::M1, "" },
{ 0x01F1, 0x0038, 0, VR::LO, VM::M1, "" },
{ 0x01F1, 0x0039, 0, VR::LO, VM::M1, "" },
{ 0x01F1, 0x0040, 0, VR::CS, VM::M1, "" },
{ 0x01F1, 0x0042, 0, VR::SH, VM::M1, "" },
{ 0x01F1, 0x0043, 0, VR::LO, VM::M1, "" },
{ 0x01F1, 0x0044, 0, VR::OW, VM::M1, "" },
{ 0x01F1, 0x0045, 0, VR::IS, VM::M1, "" },
{ 0x01F1, 0x0046, 0, VR::FL, VM::M1, "" },
{ 0x01F1, 0x0047, 0, VR::SH, VM::M1, "" },
{ 0x01F1, 0x0049, 0, VR::DS, VM::M1, "" },
{ 0x01F1, 0x004A, 0, VR::SH, VM::M1, "" },
{ 0x01F1, 0x004B, 0, VR::SH, VM::M1, "" },
{ 0x01F1, 0x004C, 0, VR::SH, VM::M1, "" },
{ 0x01F1, 0x004D, 0, VR::SH, VM::M1, "" },
{ 0x01F1, 0x004E, 0, VR::LO, VM::M1, "" },
{ 0x01F1, 0x0053, 0, VR::SH, VM::M1, "" },
{ 0x01F3, 0x0001, 0, VR::SQ, VM::M1, "" },
{ 0x01F3, 0x0002, 0, VR::SS, VM::M1, "" },
{ 0x01F3, 0x0003, 0, VR::FL, VM::M2, "" },
{ 0x01F3, 0x0004, 0, VR::FL, VM::M1, "" },
{ 0x01F3, 0x0011, 0, VR::SQ, VM::M1, "" },
{ 0x01F3, 0x0012, 0, VR::SS, VM::M1, "" },
{ 0x01F3, 0x0013, 0, VR::FL, VM::M2, "" },
{ 0x01F3, 0x0014, 0, VR::FL, VM::M1, "" },
{ 0x01F3, 0x0015, 0, VR::US, VM::M1, "" },
{ 0x01F3, 0x0016, 0, VR::FL, VM::M1, "" },
{ 0x01F3, 0x0017, 0, VR::FL, VM::M1, "" },
{ 0x01F3, 0x0018, 0, VR::SH, VM::M1, "" },
{ 0x01F3, 0x0019, 0, VR::FL, VM::M1, "" },
{ 0x01F3, 0x0023, 0, VR::US, VM::M1, "" },
{ 0x01F3, 0x0024, 0, VR::IS, VM::M2, "" },
{ 0x01F7, 0x0010, 0, VR::OB, VM::M1, "" },
{ 0x01F7, 0x0011, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0013, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0014, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0015, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0016, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0017, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0018, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0019, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x001A, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x001B, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x001C, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x001E, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x001F, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0022, 0, VR::UI, VM::M1, "" },
{ 0x01F7, 0x0023, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0025, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0026, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0027, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0028, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0029, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x002B, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x002C, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x002D, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x002E, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0030, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0031, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x005C, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0070, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0073, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0074, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x0075, 0, VR::OW, VM::M1, "" },
{ 0x01F7, 0x007F, 0, VR::OW, VM::M1, "" },
{ 0x01F9, 0x0001, 0, VR::LO, VM::M1, "SPFilter" },
{ 0x01F9, 0x0004, 0, VR::IS, VM::M1, "AdaptiveFilter" },
{ 0x01F9, 0x0005, 0, VR::IS, VM::M1, "ReconIncrement" },
{ 0x01F9, 0x0008, 0, VR::DS, VM::M1, "" },
{ 0x01F9, 0x0009, 0, VR::DS, VM::M1, "" },
{ 0x0601, 0x0000, 0, VR::SH, VM::M1, "ImplementationVersion" },
{ 0x0601, 0x0020, 0, VR::DS, VM::M1, "RelativeTablePosition" },
{ 0x0601, 0x0021, 0, VR::DS, VM::M1, "RelativeTableHeight" },
{ 0x0601, 0x0030, 0, VR::SH, VM::M1, "SurviewDirection" },
{ 0x0601, 0x0031, 0, VR::DS, VM::M1, "SurviewLength" },
{ 0x0601, 0x0050, 0, VR::SH, VM::M1, "ImageViewType" },
{ 0x0601, 0x0070, 0, VR::DS, VM::M1, "BatchNumber" },
{ 0x0601, 0x0071, 0, VR::DS, VM::M1, "BatchSize" },
{ 0x0601, 0x0072, 0, VR::DS, VM::M1, "BatchSliceNumber" },
{ 0x07A1, 0x0002, 0, VR::UL, VM::M1, "" },
{ 0x07A1, 0x0007, 0, VR::US, VM::M3, "" },
{ 0x07A1, 0x0008, 0, VR::DS, VM::M1TN, "" },
{ 0x07A1, 0x0009, 0, VR::OW, VM::M1, "" },
{ 0x07A1, 0x000A, 0, VR::OB, VM::M1, "" },
{ 0x07A1, 0x000C, 0, VR::US, VM::M1, "" },
{ 0x07A1, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x07A1, 0x0011, 0, VR::CS, VM::M1, "" },
{ 0x07A1, 0x0012, 0, VR::FL, VM::M1TN, "" },
{ 0x07A1, 0x0013, 0, VR::UL, VM::M1, "" },
{ 0x07A1, 0x0016, 0, VR::FL, VM::M1TN, "" },
{ 0x07A1, 0x0018, 0, VR::SQ, VM::M1, "" },
{ 0x07A1, 0x0019, 0, VR::FL, VM::M1, "" },
{ 0x07A1, 0x001C, 0, VR::FL, VM::M1TN, "" },
{ 0x07A1, 0x002A, 0, VR::CS, VM::M1, "" },
{ 0x07A1, 0x002B, 0, VR::CS, VM::M1, "" },
{ 0x07A1, 0x0036, 0, VR::AE, VM::M1, "" },
{ 0x07A1, 0x003D, 0, VR::US, VM::M1, "" },
{ 0x07A1, 0x0040, 0, VR::CS, VM::M1, "" },
{ 0x07A1, 0x0043, 0, VR::IS, VM::M1, "" },
{ 0x07A1, 0x0047, 0, VR::CS, VM::M1, "" },
{ 0x07A1, 0x0050, 0, VR::US, VM::M1, "" },
{ 0x07A1, 0x0056, 0, VR::US, VM::M1, "" },
{ 0x07A1, 0x0070, 0, VR::SH, VM::M1, "" },
{ 0x07A1, 0x0071, 0, VR::SH, VM::M1, "" },
{ 0x07A1, 0x0075, 0, VR::LO, VM::M2, "" },
{ 0x07A1, 0x0085, 0, VR::UL, VM::M1, "" },
{ 0x07A1, 0x0087, 0, VR::LT, VM::M1, "" },
{ 0x07A1, 0x0088, 0, VR::CS, VM::M1, "" },
{ 0x07A1, 0x0098, 0, VR::CS, VM::M1, "" },
{ 0x07A1, 0x009F, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x07A3, 0x0003, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x0005, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x0006, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x0013, 0, VR::SH, VM::M1, "" },
{ 0x07A3, 0x0014, 0, VR::ST, VM::M1, "" },
{ 0x07A3, 0x0015, 0, VR::ST, VM::M1, "" },
{ 0x07A3, 0x0017, 0, VR::SH, VM::M1, "" },
{ 0x07A3, 0x001B, 0, VR::ST, VM::M1, "" },
{ 0x07A3, 0x001F, 0, VR::ST, VM::M1, "" },
{ 0x07A3, 0x0022, 0, VR::ST, VM::M1, "" },
{ 0x07A3, 0x0023, 0, VR::ST, VM::M1, "" },
{ 0x07A3, 0x0034, 0, VR::SH, VM::M1, "" },
{ 0x07A3, 0x0043, 0, VR::DS, VM::M1TN, "" },
{ 0x07A3, 0x0055, 0, VR::SH, VM::M1, "" },
{ 0x07A3, 0x0061, 0, VR::LT, VM::M1, "" },
{ 0x07A3, 0x0062, 0, VR::SQ, VM::M1, "" },
{ 0x07A3, 0x0063, 0, VR::SQ, VM::M1, "" },
{ 0x07A3, 0x0064, 0, VR::IS, VM::M1TN, "" },
{ 0x07A3, 0x0065, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x0066, 0, VR::IS, VM::M1, "" },
{ 0x07A3, 0x0080, 0, VR::SQ, VM::M1, "" },
{ 0x07A3, 0x0099, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x009C, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x009F, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x00B9, 0, VR::CS, VM::M1, "" },
{ 0x07A3, 0x00BB, 0, VR::CS, VM::M1, "" },
{ 0x07A5, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x07A5, 0x0056, 0, VR::CS, VM::M1, "" },
{ 0x5001, 0x0070, 0, VR::SQ, VM::M1, "" },
{ 0x5001, 0x0071, 0, VR::SH, VM::M1, "" },
{ 0x5001, 0x0080, 0, VR::SQ, VM::M1, "" },
{ 0x5001, 0x0081, 0, VR::SH, VM::M1, "" },
{ 0x5001, 0x0082, 0, VR::US, VM::M3, "" },
{ 0x5001, 0x0083, 0, VR::FL, VM::M1TN, "" },
{ 0x5001, 0x0084, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict072TagHashTable[] = {
   52,    57,    62,    67,    72,    77,    84,    93,   104,   111,
  122,   131,   138,   151,   160,   167,   170,   177,   184,   189,
  200,   209,   222,   229,   238,   251,   264,   279,   296,   313,
  324,   327,   336,   343,   352,   359,   374,   383,   392,   401,
  410,   421,   438,   455,   462,   475,   484,   495,   504,   509,
   51,     0,     2,    36,    24,    47,     8,     2,   124,     1,
  158,    71,     2,     0,     1,   153,    43,     2,    60,    56,
  152,    42,     2,    14,    50,    61,    57,     3,    52,    38,
   90,    36,   157,    67,     4,    12,    48,    53,    39,   156,
   64,   163,   117,     5,    13,    49,    22,    67,    39,    52,
  105,    34,   182,    67,     3,    21,    66,   106,    35,   135,
  112,     5,    15,    55,    20,    65,   136,   113,   161,   112,
  166,   136,     4,    19,    64,   107,    37,   137,   114,   162,
  113,     3,   108,    38,   131,    33,   195,   187,     6,    75,
   83,    89,    35,   109,    39,   130,    32,   164,   133,   180,
   35,     4,    32,   160,   110,    40,   179,    34,   194,   185,
    3,    40,    65,   111,    41,   165,   135,     1,    16,    57,
    3,    17,    62,   112,    43,   178,    31,     3,    18,    63,
  113,    44,   151,    28,     2,   114,    45,   203,   131,     5,
   54,    40,   115,    46,   187,   100,   190,   128,   202,   130,
    4,   150,    25,   177,    27,   188,   101,   201,   129,     6,
   83,    20,    91,    16,   118,    92,   149,    24,   189,   102,
  200,   128,     3,    84,    21,    92,    17,   175,    21,     4,
    1,     1,    85,    22,   148,    22,   174,    20,     6,     3,
    6,    68,    71,    86,    23,    93,    19,   176,    23,   184,
   97,     6,     4,     7,    24,    81,    67,    70,    94,    20,
  185,    98,   204,   132,     7,    23,    80,    28,    99,    66,
   69,    80,    17,    95,    21,   147,    19,   186,    99,     8,
    2,     5,    27,    98,    65,    68,    81,    18,    96,    22,
  134,    80,   146,    18,   198,   112,     8,    26,    97,    64,
   67,    82,    19,    97,    23,   119,   112,   145,    17,   173,
   19,   199,   113,     5,    25,    96,    63,    66,    98,    24,
  120,   115,   144,    16,     1,    99,    25,     4,    62,    64,
  100,    26,   122,   117,   129,     0,     3,    29,   101,   101,
   27,   121,   116,     4,    74,    78,    87,    24,   102,    28,
  143,    12,     3,    31,   107,    73,    77,    88,    25,     7,
   30,   106,    33,   194,    72,    76,   103,    30,   142,    10,
  155,    61,   160,    86,     4,    71,    75,   104,    31,   141,
    9,   183,    85,     4,    34,   196,    70,    74,    79,     4,
  140,     8,     4,    46,     7,    69,    73,   139,     7,   171,
    5,     4,     8,    34,    44,     4,   193,   159,   197,    86,
    5,     9,    35,    38,    38,    45,     5,    58,    54,   116,
   48,     8,    42,     2,    59,    55,   117,    49,   123,   127,
  159,    80,   168,   159,   172,     6,   196,     0,     8,     5,
   20,     7,    33,    43,     3,    76,     1,   154,    54,   169,
    1,   181,    52,   192,   156,     3,    77,     2,   127,     8,
  138,     2,     6,    41,     1,    56,    50,    78,     3,   128,
    9,   167,   152,   170,     3,     4,    10,    36,    51,    14,
   57,    51,   191,   153,     5,     6,    24,    11,    37,    35,
  207,    55,    48,   133,    49,     4,    37,    33,    49,    12,
  125,     4,   132,    48,     2,    50,    13,   126,     5,     1,
   48,    10,
};

vtkDICOMDictionary::Dict Dict072Data = {
"ELSCINT1",
51,
205,
Dict072TagHashTable,
Dict072Contents
};

// ----- SIEMENS IMAGE SHADOW ATTRIBUTES -----

DictEntry Dict073Contents[] = {
{ 0x0021, 0x0001, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::FD, VM::M1TN, "" },
{ 0x0021, 0x0003, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0004, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0005, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x001a, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x001c, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x001f, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0022, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0024, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0025, 0, VR::LT, VM::M1, "" },
{ 0x0021, 0x0026, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0027, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x002a, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x002b, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x002c, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x002d, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x002e, 0, VR::UL, VM::M1, "" },
{ 0x0021, 0x0033, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0034, 0, VR::FD, VM::M1, "" },
{ 0x0021, 0x0035, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0037, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x003a, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x003b, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x003c, 0, VR::FD, VM::M1TN, "" },
{ 0x0021, 0x003d, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x003f, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0040, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0041, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0042, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0043, 0, VR::LT, VM::M1, "" },
{ 0x0021, 0x0044, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0045, 0, VR::SL, VM::M1TN, "" },
{ 0x0021, 0x0046, 0, VR::FD, VM::M1, "" },
{ 0x0021, 0x0047, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0048, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0049, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x004b, 0, VR::LT, VM::M1, "" },
{ 0x0021, 0x004e, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x004f, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0051, 0, VR::UL, VM::M1, "" },
{ 0x0021, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0053, 0, VR::FD, VM::M1, "" },
{ 0x0021, 0x0054, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0056, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0058, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0059, 0, VR::IS, VM::M1TN, "" },
{ 0x0021, 0x005a, 0, VR::FD, VM::M1TN, "" },
{ 0x0021, 0x005b, 0, VR::FD, VM::M1TN, "" },
{ 0x0021, 0x005e, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict073TagHashTable[] = {
   14,    23,    32,    37,    46,    53,    62,    73,    84,    91,
  104,   115,   124,     0,     4,     5,     6,    17,    44,    25,
   59,    37,    72,     4,     9,    32,    24,    58,    38,    73,
   46,    86,     2,    19,    46,    27,    61,     4,    10,    34,
   26,    60,    39,    75,    47,    88,     3,    12,    37,    28,
   63,    48,    89,     4,    11,    36,    20,    51,    29,    64,
   49,    90,     5,     0,     1,    14,    39,    30,    65,    40,
   78,    50,    91,     5,     6,    26,    13,    38,    22,    53,
   31,    66,    41,    79,     3,     2,     3,    21,    52,    32,
   67,     6,     1,     2,     7,    28,    23,    55,    33,    68,
   42,    81,    51,    94,     5,     4,     5,     8,    31,    16,
   43,    34,    69,    43,    82,     4,     3,     4,    15,    42,
   35,    70,    44,    83,     3,    18,    45,    36,    71,    45,
   84,
};

vtkDICOMDictionary::Dict Dict073Data = {
"SIEMENS IMAGE SHADOW ATTRIBUTES",
13,
52,
Dict073TagHashTable,
Dict073Contents
};

// ----- Harmony R1.0 -----

DictEntry Dict074Contents[] = {
{ 0x0019, 0x0000, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0004, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0007, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0008, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0009, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x000a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x000b, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x000c, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x000d, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x000e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x000f, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0010, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0011, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0012, 0, VR::TM, VM::M1, "" },
{ 0x0019, 0x0013, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0014, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0015, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0016, 0, VR::IS, VM::M1TN, "" },
{ 0x0019, 0x0017, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0018, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0019, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x001a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x001b, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x001c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x001d, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x001e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x001f, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0024, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0025, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0029, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x002a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002b, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x002d, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x002e, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x002f, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0030, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0031, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0032, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0033, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0034, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0035, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0036, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0037, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0038, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0039, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x003a, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x003b, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003d, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x003e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003f, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0041, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0042, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0043, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0045, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0046, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0047, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0048, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0049, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x004a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x004b, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x004c, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x004e, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x004f, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0051, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0052, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0054, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0055, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0056, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0057, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0058, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0059, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x005a, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x005b, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005c, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x005d, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x005f, 0, VR::UI, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::UI, VM::M1, "" },
{ 0x0019, 0x0063, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0064, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0065, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0066, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0067, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0068, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0069, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x006a, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x006b, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0070, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0071, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0072, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0073, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0074, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0075, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0079, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x007a, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x007b, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x007c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007d, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007f, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0081, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0083, 0, VR::US, VM::M1, "" },
};

unsigned short Dict074TagHashTable[] = {
   29,    38,    47,    56,    65,    74,    83,    90,    99,   110,
  119,   128,   139,   152,   165,   176,   189,   198,   207,   216,
  223,   232,   239,   248,   257,   266,   273,   280,     0,     4,
    5,     5,    25,    25,    70,    76,    93,   104,     4,     4,
    4,    24,    24,    32,    32,    94,   105,     4,     7,     7,
   27,    27,    71,    78,    95,   106,     4,     6,     6,    26,
   26,    72,    79,    96,   107,     4,    29,    29,    34,    37,
   51,    57,    58,    64,     4,    28,    28,    33,    36,    50,
   56,    59,    65,     3,    31,    31,    53,    59,    60,    66,
    4,    30,    30,    35,    38,    52,    58,    61,    67,     5,
   17,    17,    55,    61,    62,    68,    80,    88,    87,    96,
    4,    16,    16,    54,    60,    63,    69,    81,    89,     4,
   19,    19,    57,    63,    64,    70,    82,    90,     5,    18,
   18,    56,    62,    65,    71,    83,    91,    88,    99,     6,
   21,    21,    43,    49,    84,    92,    89,   100,   103,   120,
  114,   131,     6,    20,    20,    42,    48,    85,    93,    90,
  101,   104,   121,   113,   130,     5,    23,    23,    45,    51,
   91,   102,   105,   122,   112,   129,     6,    22,    22,    44,
   50,    86,    95,    92,   103,   106,   123,   111,   128,     4,
    9,     9,    47,    53,    73,    80,   107,   124,     4,     8,
    8,    46,    52,    74,    81,   108,   125,     4,    11,    11,
   49,    55,    75,    82,   109,   126,     3,    10,    10,    48,
   54,   110,   127,     4,    13,    13,    36,    41,    76,    84,
   97,   112,     3,    12,    12,    77,    85,    98,   113,     4,
   15,    15,    38,    43,    78,    86,    99,   114,     4,    14,
   14,    37,    42,    79,    87,   100,   115,     4,     1,     1,
   39,    45,    66,    72,   101,   116,     3,     0,     0,    67,
   73,   102,   117,     3,     3,     3,    41,    47,    68,    74,
    3,     2,     2,    40,    46,    69,    75,
};

vtkDICOMDictionary::Dict Dict074Data = {
"Harmony R1.0",
28,
115,
Dict074TagHashTable,
Dict074Contents
};

// ----- FDMS 1.0 -----

DictEntry Dict075Contents[] = {
{ 0x0009, 0x0004, 0, VR::SH, VM::M1, "ImageControlUnit" },
{ 0x0009, 0x0005, 0, VR::OW, VM::M1, "ImageUID" },
{ 0x0009, 0x0006, 0, VR::OW, VM::M1, "RouteImageUID" },
{ 0x0009, 0x0008, 0, VR::UL, VM::M1, "ImageDisplayInformationVersionNumber" },
{ 0x0009, 0x0009, 0, VR::UL, VM::M1, "PatientInformationVersionNumber" },
{ 0x0009, 0x000C, 0, VR::OW, VM::M1, "FilmUID" },
{ 0x0009, 0x0010, 0, VR::CS, VM::M1, "ExposureUnitTypeCode" },
{ 0x0009, 0x0080, 0, VR::LO, VM::M1, "KanjiHospitalName" },
{ 0x0009, 0x0090, 0, VR::ST, VM::M1, "DistributionCode" },
{ 0x0009, 0x0092, 0, VR::SH, VM::M1, "KanjiDepartmentName" },
{ 0x0009, 0x00F0, 0, VR::CS, VM::M1, "BlackeningProcessFlag" },
{ 0x0009, 0x00F1, 0, VR::LO, VM::M1, "ProcessingInformationFlag" },
{ 0x0019, 0x0015, 0, VR::LO, VM::M1, "KanjiBodyPartForExposure" },
{ 0x0019, 0x0030, 0, VR::LO, VM::M1, "MenuCharacterString" },
{ 0x0019, 0x0032, 0, VR::LO, VM::M1, "KanjiMenuName" },
{ 0x0019, 0x0040, 0, VR::CS, VM::M1, "ImageProcessingType" },
{ 0x0019, 0x0050, 0, VR::CS, VM::M1, "EDRMode" },
{ 0x0019, 0x0060, 0, VR::SH, VM::M1, "RadiographersCode" },
{ 0x0019, 0x0070, 0, VR::IS, VM::M1, "SplitExposureFormat" },
{ 0x0019, 0x0071, 0, VR::IS, VM::M1, "NumberOfSplitExposureFrames" },
{ 0x0019, 0x0080, 0, VR::IS, VM::M1, "ReadingPositionSpecification" },
{ 0x0019, 0x0081, 0, VR::IS, VM::M1, "ReadingSensitivityCenter" },
{ 0x0019, 0x0090, 0, VR::SH, VM::M1, "FilmAnnotationCharacterString1" },
{ 0x0019, 0x0091, 0, VR::SH, VM::M1, "FilmAnnotationCharacterString2" },
{ 0x0021, 0x0010, 0, VR::CS, VM::M1, "FCRImageID" },
{ 0x0021, 0x0030, 0, VR::CS, VM::M1, "SetNumber" },
{ 0x0021, 0x0040, 0, VR::IS, VM::M1, "ImageNumberInTheSet" },
{ 0x0021, 0x0050, 0, VR::CS, VM::M1, "PairProcessingInformation" },
{ 0x0021, 0x0070, 0, VR::IS, VM::M1, "FilmNumberWithinTheSeries" },
{ 0x0021, 0x0080, 0, VR::CS, VM::M1, "EquipmentTypeSpecificInformation" },
{ 0x0021, 0x0090, 0, VR::CS, VM::M1, "LUTNumber" },
{ 0x0023, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x0023, 0x0020, 0, VR::SQ, VM::M1, "" },
{ 0x0023, 0x0030, 0, VR::SQ, VM::M1, "" },
{ 0x0025, 0x0010, 0, VR::US, VM::M1, "RelativeLightEmissionAmountSk" },
{ 0x0025, 0x0011, 0, VR::US, VM::M1, "TermOfCorrectionForEachIPTypeSt" },
{ 0x0025, 0x0012, 0, VR::US, VM::M1, "ReadingGainGp" },
{ 0x0025, 0x0013, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0015, 0, VR::CS, VM::M1, "" },
{ 0x0025, 0x0020, 0, VR::US, VM::M2, "" },
{ 0x0025, 0x0021, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0031, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0033, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0034, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0040, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0041, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0042, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0043, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0050, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0051, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0053, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0060, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0061, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0062, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0063, 0, VR::CS, VM::M1, "" },
{ 0x0025, 0x0070, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0071, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0072, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0073, 0, VR::US, VM::M6, "" },
{ 0x0025, 0x0074, 0, VR::US, VM::M6, "" },
{ 0x0025, 0x0080, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0081, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0082, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0083, 0, VR::US, VM::M6, "" },
{ 0x0025, 0x0084, 0, VR::US, VM::M6, "" },
{ 0x0025, 0x0090, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0091, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0092, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0093, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0094, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0095, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0096, 0, VR::CS, VM::M1, "" },
{ 0x0025, 0x00a0, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x00a1, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x00a2, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x00a3, 0, VR::SS, VM::M1, "" },
{ 0x0027, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x0020, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x0030, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x0040, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x0050, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x0060, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x0070, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x0080, 0, VR::SQ, VM::M1, "" },
{ 0x0027, 0x00a0, 0, VR::IS, VM::M1, "" },
{ 0x0027, 0x00a1, 0, VR::CS, VM::M2, "" },
{ 0x0027, 0x00a2, 0, VR::CS, VM::M2, "" },
{ 0x0027, 0x00a3, 0, VR::SS, VM::M1TN, "" },
{ 0x0029, 0x0020, 0, VR::CS, VM::M1, "ImageScanningDirection" },
{ 0x0029, 0x0025, 0, VR::CS, VM::M1, "ImageRotationReversalInformation" },
{ 0x0029, 0x0030, 0, VR::CS, VM::M1, "ExtendedReadingSizeValue" },
{ 0x0029, 0x0034, 0, VR::US, VM::M1, "MagReducRatio" },
{ 0x0029, 0x0044, 0, VR::CS, VM::M1, "LineDensityCode" },
{ 0x0029, 0x0050, 0, VR::CS, VM::M1, "DataCompressionCode" },
{ 0x2011, 0x0000, 0, VR::CS, VM::M1, "TrimDensity" },
{ 0x2011, 0x0001, 0, VR::IS, VM::M1, "TrimWidth" },
{ 0x2011, 0x0002, 0, VR::CS, VM::M1, "ImageMagReducRatio" },
{ 0x2011, 0x0010, 0, VR::CS, VM::M1, "ImageDisplayFormat" },
{ 0x2011, 0x0011, 0, VR::CS, VM::M1, "ImagePositionSpecifyingFlag" },
{ 0x2011, 0x0020, 0, VR::OW, VM::M1, "InterpolationAVRSSystemFormat" },
{ 0x50F1, 0x0006, 0, VR::CS, VM::M1, "EnergySubtractionParameter" },
{ 0x50F1, 0x0007, 0, VR::CS, VM::M1, "SubtractionRegistrationResult" },
{ 0x50F1, 0x0008, 0, VR::CS, VM::M1, "EnergySubtractionParameter2" },
{ 0x50F1, 0x0009, 0, VR::SL, VM::M1, "AfinConversionCoefficient" },
{ 0x50F1, 0x000A, 0, VR::LO, VM::M1, "FNCParameters" },
{ 0x50F1, 0x0010, 0, VR::CS, VM::M1, "FilmOutputFormat" },
{ 0x50F1, 0x0020, 0, VR::CS, VM::M1, "ImageProcessingModificationFlag" },
};

unsigned short Dict075TagHashTable[] = {
   28,    41,    52,    57,    68,    83,    96,    99,   106,   111,
  116,   121,   126,   137,   140,   145,   154,   163,   174,   183,
  194,   207,   220,   229,   238,   249,   262,     0,     6,     4,
    9,    37,    19,    75,   160,    89,   162,    95,    68,   108,
   16,     5,     3,     8,    29,   128,    36,    18,    67,   132,
   79,    16,     2,    66,   131,    94,    52,     5,    23,   145,
   32,    32,    58,   112,    65,   130,    86,   128,     7,     7,
  128,    22,   144,    27,    80,    40,    33,    59,   113,    64,
  129,   101,    17,     6,     5,    12,    39,    32,    60,   114,
   63,   128,    85,   112,   100,    16,     1,    61,   115,     3,
   10,   240,    15,    64,    80,    32,     2,    11,   241,    50,
   80,     2,    51,    81,    91,    32,     2,    52,    82,    83,
   80,     2,    53,    83,   109,    32,     5,     1,     5,    12,
   21,    17,    96,    92,    37,    96,    80,     1,     0,     4,
    2,    13,    48,    54,    96,     4,     2,     6,    26,    64,
   55,    97,    74,   150,     4,    14,    50,    56,    98,    73,
  149,    84,    96,     5,    25,    48,    30,   144,    45,    52,
   57,    99,    72,   148,     4,     9,   146,    16,    80,    71,
  147,   103,     6,     5,    21,   129,    33,    48,    46,    64,
   70,   146,   104,     7,     6,     8,   144,    20,   128,    42,
   49,    47,    65,    69,   145,    98,     1,     6,    38,    21,
   41,    48,    48,    66,    68,   144,    82,    64,    97,     0,
    4,    24,    16,    44,    51,    49,    67,   107,    10,     4,
   18,   112,    43,    50,    81,    48,    99,     2,     5,    19,
  113,    31,    16,    78,   163,    88,   161,   105,     8,     6,
    6,    16,    35,    17,    77,   162,    87,   160,    93,    48,
  106,     9,     6,    28,   112,    34,    16,    62,   116,    76,
  161,    90,   163,   102,    32,
};

vtkDICOMDictionary::Dict Dict075Data = {
"FDMS 1.0",
27,
110,
Dict075TagHashTable,
Dict075Contents
};

// ----- SIEMENS SYNGO SOP CLASS PACKING -----

DictEntry Dict076Contents[] = {
{ 0x0031, 0x0010, 0, VR::SQ, VM::M1, "SOPClassPackingSequence" },
{ 0x0031, 0x0020, 0, VR::CS, VM::M1, "PackingVersion" },
{ 0x0031, 0x0021, 0, VR::CS, VM::M1, "PackingOriginator" },
{ 0x0031, 0x0030, 0, VR::UI, VM::M1, "OriginalSOPClassUID" },
{ 0x0031, 0x0031, 0, VR::UI, VM::M1, "OriginalStudyInstanceUID" },
{ 0x0031, 0x0032, 0, VR::UI, VM::M1, "OriginalSeriesInstanceUID" },
{ 0x0031, 0x0033, 0, VR::UI, VM::M1, "OriginalSOPInstanceUID" },
{ 0x0031, 0x0034, 0, VR::UI, VM::M1, "OriginalTransferSyntaxUID" },
{ 0x0031, 0x0040, 0, VR::AT, VM::M1TN, "AttributesToSetToZeroLength" },
{ 0x0031, 0x0041, 0, VR::AT, VM::M1TN, "AttributesToRemove" },
{ 0x0031, 0x0050, 0, VR::US, VM::M1, "OriginalRows" },
{ 0x0031, 0x0051, 0, VR::US, VM::M1, "OriginalColumns" },
{ 0x0031, 0x0058, 0, VR::CS, VM::M2TN, "OriginalImageType" },
{ 0x0031, 0x0060, 0, VR::CS, VM::M1, "OriginalModality" },
{ 0x0031, 0x0070, 0, VR::SQ, VM::M1, "SequenceOfOriginalStreamChunks" },
{ 0x0031, 0x0071, 0, VR::AT, VM::M1, "StartTagOfAStreamChunk" },
{ 0x0031, 0x0072, 0, VR::AT, VM::M1, "EndTagOfAStreamChunk" },
{ 0x0031, 0x0073, 0, VR::CS, VM::M1, "StreamChunkIsAPayload" },
{ 0x0031, 0x0080, 0, VR::OB, VM::M1, "StreamChunk" },
};

unsigned short Dict076TagHashTable[] = {
    5,    20,    35,    40,     0,     7,     2,    33,     4,    49,
    8,    64,    10,    80,    12,    88,    13,    96,    14,   112,
    7,     0,    16,     1,    32,     3,    48,     7,    52,     9,
   65,    11,    81,    15,   113,     2,     6,    51,    16,   114,
    3,     5,    50,    17,   115,    18,   128,
};

vtkDICOMDictionary::Dict Dict076Data = {
"SIEMENS SYNGO SOP CLASS PACKING",
4,
19,
Dict076TagHashTable,
Dict076Contents
};

// ----- Sound Technologies -----

DictEntry Dict077Contents[] = {
{ 0xf001, 0x0000, 0, VR::LO, VM::M1, "PatientSpecies" },
{ 0xf001, 0x0001, 0, VR::LO, VM::M1, "PatientBreed" },
{ 0xf001, 0x0002, 0, VR::LO, VM::M1, "PatientCategorySize" },
{ 0xf001, 0x0003, 0, VR::CS, VM::M1, "PatientSexExtended" },
{ 0xf001, 0x0004, 0, VR::LO, VM::M1, "ImageView" },
{ 0xf001, 0x0005, 0, VR::LO, VM::M1, "AnatomyImaged" },
{ 0xf001, 0x0006, 0, VR::LT, VM::M1, "ImageEnhancements" },
{ 0xf001, 0x0007, 0, VR::LO, VM::M1, "DetectorSettings" },
{ 0xf001, 0x0008, 0, VR::LO, VM::M1, "ApplicationVersion" },
{ 0xf001, 0x0009, 0, VR::LO, VM::M1, "ImageLateralityExtended" },
{ 0xf001, 0x000a, 0, VR::PN, VM::M1, "ClientName" },
{ 0xf001, 0x000b, 0, VR::UI, VM::M1, "ReferenceStudyInstanceUID" },
{ 0xf001, 0x000c, 0, VR::UI, VM::M1, "ReferenceStudyInstanceUID" },
{ 0xf001, 0x000d, 0, VR::LO, VM::M1, "ExamRefID" },
{ 0xf001, 0x000e, 0, VR::ST, VM::M1, "PhysicianOfRecordAddress" },
{ 0xf001, 0x000f, 0, VR::SH, VM::M1, "PhysicianOfRecordPhoneNumbers" },
{ 0xf001, 0x0010, 0, VR::LT, VM::M1, "ReasonForStudy" },
{ 0xf001, 0x0011, 0, VR::LO, VM::M1, "Protocol" },
{ 0xf001, 0x0012, 0, VR::LO, VM::M1, "CaptureInputType" },
{ 0xf001, 0x0013, 0, VR::LT, VM::M1, "ExamComplaint" },
{ 0xf001, 0x0014, 0, VR::LO, VM::M1, "ExamWebCode" },
{ 0xf001, 0x0015, 0, VR::LO, VM::M1, "ExamCategory" },
{ 0xf001, 0x0016, 0, VR::SH, VM::M1, "ExamDiagnosis" },
{ 0xf001, 0x0017, 0, VR::PN, VM::M1, "ExamCreatedBy" },
{ 0xf001, 0x0018, 0, VR::LO, VM::M1, "ExamCreatedByGroup" },
{ 0xf001, 0x0019, 0, VR::DT, VM::M1, "ExamRequiredByDateTime" },
{ 0xf001, 0x001a, 0, VR::LO, VM::M1, "CaptureType" },
{ 0xf001, 0x001b, 0, VR::IS, VM::M1, "TelemedExamID" },
{ 0xf001, 0x001c, 0, VR::LO, VM::M1, "ExamCreatedByGuid" },
{ 0xf001, 0x001d, 0, VR::LO, VM::M1, "ClientNameGuid" },
{ 0xf001, 0x001e, 0, VR::LO, VM::M1, "ReceptorBitsPerPixel" },
};

unsigned short Dict077TagHashTable[] = {
    8,    17,    26,    37,    48,    57,    68,     0,     4,     4,
    4,    13,    13,    18,    18,    27,    27,     4,     7,     7,
   12,    12,    21,    21,    26,    26,     5,     1,     1,     6,
    6,    15,    15,    20,    20,    29,    29,     5,     0,     0,
    9,     9,    14,    14,    23,    23,    28,    28,     4,     3,
    3,     8,     8,    17,    17,    22,    22,     5,     2,     2,
   11,    11,    16,    16,    25,    25,    30,    30,     4,     5,
    5,    10,    10,    19,    19,    24,    24,
};

vtkDICOMDictionary::Dict Dict077Data = {
"Sound Technologies",
7,
31,
Dict077TagHashTable,
Dict077Contents
};

// ----- PHILIPS XCT -Private -----

DictEntry Dict078Contents[] = {
{ 0x7051, 0x0001, 0, VR::DS, VM::M1, "AttenuationThreshold" },
{ 0x7051, 0x0002, 0, VR::DS, VM::M1, "DLPEstimate" },
};

unsigned short Dict078TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     2,
};

vtkDICOMDictionary::Dict Dict078Data = {
"PHILIPS XCT -Private",
1,
2,
Dict078TagHashTable,
Dict078Contents
};

// ----- Siemens: Thorax/Multix FD Image Stamp -----

DictEntry Dict079Contents[] = {
{ 0x0023, 0x0000, 0, VR::US, VM::M1, "" },
{ 0x0023, 0x0001, 0, VR::US, VM::M1, "" },
{ 0x0023, 0x0002, 0, VR::US, VM::M1, "" },
{ 0x0023, 0x0003, 0, VR::US, VM::M1, "" },
{ 0x0023, 0x0004, 0, VR::US, VM::M1, "" },
};

unsigned short Dict079TagHashTable[] = {
    2,     0,     5,     0,     0,     1,     1,     2,     2,     3,
    3,     4,     4,
};

vtkDICOMDictionary::Dict Dict079Data = {
"Siemens: Thorax/Multix FD Image Stamp",
1,
5,
Dict079TagHashTable,
Dict079Contents
};

// ----- GEMS_PARM_01 -----

DictEntry Dict080Contents[] = {
{ 0x0043, 0x0001, 0, VR::SS, VM::M1, "BitmapOfPrescanOptions" },
{ 0x0043, 0x0002, 0, VR::SS, VM::M1, "GradientOffsetInX" },
{ 0x0043, 0x0003, 0, VR::SS, VM::M1, "GradientOffsetInY" },
{ 0x0043, 0x0004, 0, VR::SS, VM::M1, "GradientOffsetInZ" },
{ 0x0043, 0x0005, 0, VR::SS, VM::M1, "ImageIsOriginalOrUnoriginal" },
{ 0x0043, 0x0006, 0, VR::SS, VM::M1, "NumberOfEPIShots" },
{ 0x0043, 0x0007, 0, VR::SS, VM::M1, "ViewsPerSegment" },
{ 0x0043, 0x0008, 0, VR::SS, VM::M1, "RespiratoryRateInBPM" },
{ 0x0043, 0x0009, 0, VR::SS, VM::M1, "RespiratoryTriggerPoint" },
{ 0x0043, 0x000a, 0, VR::SS, VM::M1, "TypeOfReceiverUsed" },
{ 0x0043, 0x000b, 0, VR::DS, VM::M1, "PeakRateOfChangeOfGradientField" },
{ 0x0043, 0x000c, 0, VR::DS, VM::M1, "LimitsInUnitsOfPercent" },
{ 0x0043, 0x000d, 0, VR::DS, VM::M1, "PSDEstimatedLimit" },
{ 0x0043, 0x000e, 0, VR::DS, VM::M1, "PSDEstimatedLimitInTeslaPerSecond" },
{ 0x0043, 0x000f, 0, VR::DS, VM::M1, "SARAvgHead" },
{ 0x0043, 0x0010, 0, VR::US, VM::M1, "WindowValue" },
{ 0x0043, 0x0011, 0, VR::US, VM::M1, "TotalInputViews" },
{ 0x0043, 0x0012, 0, VR::SS, VM::M3, "XrayChain" },
{ 0x0043, 0x0013, 0, VR::SS, VM::M5, "ReconKernelParameters" },
{ 0x0043, 0x0014, 0, VR::SS, VM::M3, "CalibrationParameters" },
{ 0x0043, 0x0015, 0, VR::SS, VM::M3, "TotalOutputViews" },
{ 0x0043, 0x0016, 0, VR::SS, VM::M5, "NumberOfOverranges" },
{ 0x0043, 0x0017, 0, VR::DS, VM::M1, "IBHImageScaleFactors" },
{ 0x0043, 0x0018, 0, VR::DS, VM::M3, "BBH Coefficients" },
{ 0x0043, 0x0019, 0, VR::SS, VM::M1, "NumberOfBBHChainsToBlend" },
{ 0x0043, 0x001a, 0, VR::SL, VM::M1, "StartingChannelNumber" },
{ 0x0043, 0x001b, 0, VR::SS, VM::M1, "PPScanParameters" },
{ 0x0043, 0x001c, 0, VR::SS, VM::M1, "GEImageIntegrity" },
{ 0x0043, 0x001d, 0, VR::SS, VM::M1, "LevelValue" },
{ 0x0043, 0x001e, 0, VR::DS, VM::M1, "DeltaStartTime" },
{ 0x0043, 0x001f, 0, VR::SL, VM::M1, "MaxOverrangesInAView" },
{ 0x0043, 0x0020, 0, VR::DS, VM::M1, "AvgOverrangesAllViews" },
{ 0x0043, 0x0021, 0, VR::SS, VM::M1, "CorrectedAfterglowTerms" },
{ 0x0043, 0x0025, 0, VR::SS, VM::M6, "ReferenceChannels" },
{ 0x0043, 0x0026, 0, VR::US, VM::M6, "NoViewsRefChannelsBlocked" },
{ 0x0043, 0x0027, 0, VR::SH, VM::M1, "ScanPitchRatio" },
{ 0x0043, 0x0028, 0, VR::OB, VM::M1, "UniqueImageIdentifier" },
{ 0x0043, 0x0029, 0, VR::OB, VM::M1, "HistogramTables" },
{ 0x0043, 0x002a, 0, VR::OB, VM::M1, "UserDefinedData" },
{ 0x0043, 0x002b, 0, VR::SS, VM::M4, "PrivateScanOptions" },
{ 0x0043, 0x002c, 0, VR::SS, VM::M1, "EffectiveEchoSpacing" },
{ 0x0043, 0x002d, 0, VR::SH, VM::M1, "FilterMode" },
{ 0x0043, 0x002e, 0, VR::SH, VM::M1, "StringSlopField2" },
{ 0x0043, 0x002f, 0, VR::SS, VM::M1, "ImageType" },
{ 0x0043, 0x0030, 0, VR::SS, VM::M1, "VasCollapseFlag" },
{ 0x0043, 0x0031, 0, VR::DS, VM::M2, "ReconCenterCoordinates" },
{ 0x0043, 0x0032, 0, VR::SS, VM::M1, "VasFlags" },
{ 0x0043, 0x0033, 0, VR::FL, VM::M1, "NegScanSpacing" },
{ 0x0043, 0x0034, 0, VR::IS, VM::M1, "OffsetFrequency" },
{ 0x0043, 0x0035, 0, VR::UL, VM::M1, "UserUsageTag" },
{ 0x0043, 0x0036, 0, VR::UL, VM::M1, "UserFillMapMSW" },
{ 0x0043, 0x0037, 0, VR::UL, VM::M1, "UserFillMapLSW" },
{ 0x0043, 0x0038, 0, VR::FL, VM::M24, "User25ToUser48" },
{ 0x0043, 0x0039, 0, VR::IS, VM::M4, "SlopInteger6ToSlopInteger9" },
{ 0x0043, 0x0040, 0, VR::FL, VM::M4, "TriggerOnPosition" },
{ 0x0043, 0x0041, 0, VR::FL, VM::M4, "DegreeOfRotation" },
{ 0x0043, 0x0042, 0, VR::SL, VM::M4, "DASTriggerSource" },
{ 0x0043, 0x0043, 0, VR::SL, VM::M4, "DASFpaGain" },
{ 0x0043, 0x0044, 0, VR::SL, VM::M4, "DASOutputSource" },
{ 0x0043, 0x0045, 0, VR::SL, VM::M4, "DASAdInput" },
{ 0x0043, 0x0046, 0, VR::SL, VM::M4, "DASCalMode" },
{ 0x0043, 0x0047, 0, VR::SL, VM::M4, "DASCalFrequency" },
{ 0x0043, 0x0048, 0, VR::SL, VM::M4, "DASRegXm" },
{ 0x0043, 0x0049, 0, VR::SL, VM::M4, "DASAutoZero" },
{ 0x0043, 0x004a, 0, VR::SS, VM::M4, "StartingChannelOfView" },
{ 0x0043, 0x004b, 0, VR::SL, VM::M4, "DASXmPattern" },
{ 0x0043, 0x004c, 0, VR::SS, VM::M4, "TGGCTriggerMode" },
{ 0x0043, 0x004d, 0, VR::FL, VM::M4, "StartScanToXrayOnDelay" },
{ 0x0043, 0x004e, 0, VR::FL, VM::M4, "DurationOfXrayOn" },
{ 0x0043, 0x0060, 0, VR::IS, VM::M8, "SlopInteger10ToSlopInteger17" },
{ 0x0043, 0x0061, 0, VR::UI, VM::M1, "ScannerStudyEntityUID" },
{ 0x0043, 0x0062, 0, VR::SH, VM::M1, "ScannerStudyID" },
{ 0x0043, 0x0063, 0, VR::SH, VM::M1, "RawDataID" },
{ 0x0043, 0x0064, 0, VR::CS, VM::M1TN, "ImageFilter" },
{ 0x0043, 0x0065, 0, VR::US, VM::M1, "MotionCorrectionIndicator" },
{ 0x0043, 0x0066, 0, VR::US, VM::M1, "HelicalCorrectionIndicator" },
{ 0x0043, 0x0067, 0, VR::US, VM::M1, "IBOCorrectionIndicator" },
{ 0x0043, 0x0068, 0, VR::US, VM::M1, "IXTCorrectionIndicator" },
{ 0x0043, 0x0069, 0, VR::US, VM::M1, "QcalCorrectionIndicator" },
{ 0x0043, 0x006a, 0, VR::US, VM::M1, "AVCorrectionIndicator" },
{ 0x0043, 0x006b, 0, VR::US, VM::M1, "LMDKCorrectionIndicator" },
{ 0x0043, 0x006c, 0, VR::IS, VM::M1, "DetectorRow" },
{ 0x0043, 0x006d, 0, VR::US, VM::M1, "AreaSize" },
{ 0x0043, 0x006e, 0, VR::SH, VM::M1, "AutoMAMode" },
{ 0x0043, 0x006f, 0, VR::DS, VM::M3T4, "ScannerTableEntry" },
{ 0x0043, 0x0070, 0, VR::LO, VM::M1, "ParadigmName" },
{ 0x0043, 0x0071, 0, VR::ST, VM::M1, "ParadigmDescription" },
{ 0x0043, 0x0072, 0, VR::UI, VM::M1, "ParadigmUID" },
{ 0x0043, 0x0073, 0, VR::US, VM::M1, "ExperimentType" },
{ 0x0043, 0x0074, 0, VR::US, VM::M1, "NumberOfRestVolumes" },
{ 0x0043, 0x0075, 0, VR::US, VM::M1, "NumberOfActiveVolumes" },
{ 0x0043, 0x0076, 0, VR::US, VM::M1, "NumberOfDummyScans" },
{ 0x0043, 0x0077, 0, VR::SH, VM::M1, "ApplicationName" },
{ 0x0043, 0x0078, 0, VR::SH, VM::M1, "ApplicationVersion" },
{ 0x0043, 0x0079, 0, VR::US, VM::M1, "SlicesPerVolume" },
{ 0x0043, 0x007a, 0, VR::US, VM::M1, "ExpectedTimePoints" },
{ 0x0043, 0x007b, 0, VR::FL, VM::M1TN, "RegressorValues" },
{ 0x0043, 0x007c, 0, VR::FL, VM::M1, "DelayAfterSliceGroup" },
{ 0x0043, 0x007d, 0, VR::US, VM::M1, "ReconModeFlagWord" },
{ 0x0043, 0x007e, 0, VR::LO, VM::M1TN, "PACCSpecificInformation" },
{ 0x0043, 0x007f, 0, VR::DS, VM::M1TN, "Reserved" },
{ 0x0043, 0x0080, 0, VR::LO, VM::M1TN, "CoilIDData" },
{ 0x0043, 0x0081, 0, VR::LO, VM::M1, "GECoilName" },
{ 0x0043, 0x0082, 0, VR::LO, VM::M1TN, "SystemConfigurationInformation" },
{ 0x0043, 0x0083, 0, VR::DS, VM::M1T2, "AssetRFactors" },
{ 0x0043, 0x0084, 0, VR::LO, VM::M5, "AdditionalAssetData" },
{ 0x0043, 0x0085, 0, VR::UT, VM::M1, "DebugDataTextFormat" },
{ 0x0043, 0x0086, 0, VR::OB, VM::M1, "DebugDataBinaryFormat" },
{ 0x0043, 0x0087, 0, VR::UT, VM::M1, "Reserved" },
{ 0x0043, 0x0088, 0, VR::UI, VM::M1, "PUREAcquisitionCalibrationSeriesUID" },
{ 0x0043, 0x0089, 0, VR::LO, VM::M3, "GoverningBodyDBdtSARDefinition" },
{ 0x0043, 0x008a, 0, VR::CS, VM::M1, "PrivateInPlanePhaseEncodingDirection" },
{ 0x0043, 0x008b, 0, VR::OB, VM::M1, "FMRIBinaryDataBlock" },
{ 0x0043, 0x008c, 0, VR::DS, VM::M1, "VoxelLocation" },
{ 0x0043, 0x008d, 0, VR::DS, VM::M1TN, "SATBandLocations" },
{ 0x0043, 0x008e, 0, VR::DS, VM::M3, "SpectroPrescanValues" },
{ 0x0043, 0x008f, 0, VR::DS, VM::M3, "SpectroParameters" },
{ 0x0043, 0x0090, 0, VR::LO, VM::M1TN, "SARDefinition" },
{ 0x0043, 0x0091, 0, VR::DS, VM::M1TN, "SARValue" },
{ 0x0043, 0x0092, 0, VR::LO, VM::M1, "ImageErrorText" },
{ 0x0043, 0x0093, 0, VR::DS, VM::M1TN, "SpectroQuantitationValues" },
{ 0x0043, 0x0094, 0, VR::DS, VM::M1TN, "SpectroRatioValues" },
{ 0x0043, 0x0095, 0, VR::LO, VM::M1, "PrescanReuseString" },
{ 0x0043, 0x0096, 0, VR::CS, VM::M1, "ContentQualification" },
{ 0x0043, 0x0097, 0, VR::LO, VM::M8, "ImageFilteringParameters" },
{ 0x0043, 0x0098, 0, VR::UI, VM::M1, "ASSETAcquisitionCalibrationSeriesUID" },
{ 0x0043, 0x0099, 0, VR::LO, VM::M1TN, "ExtendedOptions" },
{ 0x0043, 0x009a, 0, VR::IS, VM::M1, "RxStackIdentification" },
};

unsigned short Dict080TagHashTable[] = {
   33,    42,    51,    60,    71,    82,    93,   102,   113,   124,
  135,   146,   157,   166,   177,   188,   199,   208,   217,   226,
  235,   244,   253,   262,   271,   278,   285,   294,   301,   306,
  311,   316,     0,     4,     1,     2,    57,    67,    72,    99,
  101,   128,     4,     2,     3,    56,    66,    71,    98,   102,
  129,     4,    31,    32,    55,    65,    70,    97,   103,   130,
    5,     0,     1,    32,    33,    54,    64,    69,    96,   104,
  131,     5,     5,     6,    34,    38,    61,    71,    76,   103,
  105,   132,     5,     6,     7,    35,    39,    60,    70,    75,
  102,   106,   133,     4,     3,     4,    59,    69,    74,   101,
  107,   134,     5,     4,     5,    33,    37,    58,    68,    73,
  100,   108,   135,     5,     9,    10,    38,    42,    65,    75,
   80,   107,   109,   136,     5,    10,    11,    39,    43,    64,
   74,    79,   106,   110,   137,     5,     7,     8,    36,    40,
   63,    73,    78,   105,   111,   138,     5,     8,     9,    37,
   41,    62,    72,    77,   104,   112,   139,     4,    13,    14,
   42,    46,    84,   111,   113,   140,     5,    14,    15,    43,
   47,    68,    78,    83,   110,   114,   141,     5,    11,    12,
   40,    44,    67,    77,    82,   109,   115,   142,     5,    12,
   13,    41,    45,    66,    76,    81,   108,   116,   143,     4,
   17,    18,    46,    50,    88,   115,   117,   144,     4,    18,
   19,    47,    51,    87,   114,   118,   145,     4,    15,    16,
   44,    48,    86,   113,   119,   146,     4,    16,    17,    45,
   49,    85,   112,   120,   147,     4,    21,    22,    50,    54,
   92,   119,   121,   148,     4,    22,    23,    51,    55,    91,
  118,   122,   149,     4,    19,    20,    48,    52,    90,   117,
  123,   150,     4,    20,    21,    49,    53,    89,   116,   124,
  151,     3,    25,    26,    96,   123,   125,   152,     3,    26,
   27,    95,   122,   126,   153,     4,    23,    24,    52,    56,
   94,   121,   127,   154,     3,    24,    25,    53,    57,    93,
  120,     2,    29,    30,   100,   127,     2,    30,    31,    99,
  126,     2,    27,    28,    98,   125,     2,    28,    29,    97,
  124,
};

vtkDICOMDictionary::Dict Dict080Data = {
"GEMS_PARM_01",
32,
128,
Dict080TagHashTable,
Dict080Contents
};

// ----- MedIns HP Extensions -----

DictEntry Dict081Contents[] = {
{ 0x5473, 0x0003, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict081TagHashTable[] = {
    2,     0,     1,     0,     3,
};

vtkDICOMDictionary::Dict Dict081Data = {
"MedIns HP Extensions",
1,
1,
Dict081TagHashTable,
Dict081Contents
};

// ----- SIEMENS CM VA0  ACQU -----

DictEntry Dict082Contents[] = {
{ 0x0019, 0x0010, 0, VR::LO, VM::M1, "ParameterFileName" },
{ 0x0019, 0x0011, 0, VR::LO, VM::M1, "SequenceFileName" },
{ 0x0019, 0x0012, 0, VR::LO, VM::M1, "SequenceFileOwner" },
{ 0x0019, 0x0013, 0, VR::LO, VM::M1, "SequenceDescription" },
{ 0x0019, 0x0014, 0, VR::LO, VM::M1, "EPIFileName" },
};

unsigned short Dict082TagHashTable[] = {
    2,     0,     5,     0,    16,     1,    17,     2,    18,     3,
   19,     4,    20,
};

vtkDICOMDictionary::Dict Dict082Data = {
"SIEMENS CM VA0  ACQU",
1,
5,
Dict082TagHashTable,
Dict082Contents
};

// ----- PHILIPS MR/LAST -----

DictEntry Dict083Contents[] = {
{ 0x0019, 0x0009, 0, VR::DS, VM::M1, "MainMagneticField" },
{ 0x0019, 0x000e, 0, VR::IS, VM::M1, "FlowCompensation" },
{ 0x0019, 0x00B7, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00E4, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00E5, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00b1, 0, VR::IS, VM::M1, "MinimumRRInterval" },
{ 0x0019, 0x00b2, 0, VR::IS, VM::M1, "MaximumRRInterval" },
{ 0x0019, 0x00b3, 0, VR::IS, VM::M1, "NumberOfRejections" },
{ 0x0019, 0x00b4, 0, VR::IS, VM::M1TN, "NumberOfRRIntervals" },
{ 0x0019, 0x00b5, 0, VR::IS, VM::M1, "ArrhythmiaRejection" },
{ 0x0019, 0x00c0, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x00c6, 0, VR::IS, VM::M1, "CycledMultipleSlice" },
{ 0x0019, 0x00ce, 0, VR::IS, VM::M1, "REST" },
{ 0x0019, 0x00d5, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00d6, 0, VR::IS, VM::M1, "FourierInterpolation" },
{ 0x0019, 0x00d9, 0, VR::IS, VM::M1TN, "" },
{ 0x0019, 0x00e0, 0, VR::IS, VM::M1, "Prepulse" },
{ 0x0019, 0x00e1, 0, VR::DS, VM::M1, "PrepulseDelay" },
{ 0x0019, 0x00e2, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00e3, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00f0, 0, VR::LT, VM::M1, "WSProtocolString1" },
{ 0x0019, 0x00f1, 0, VR::LT, VM::M1, "WSProtocolString2" },
{ 0x0019, 0x00f2, 0, VR::LT, VM::M1, "WSProtocolString3" },
{ 0x0019, 0x00f3, 0, VR::LT, VM::M1, "WSProtocolString4" },
{ 0x0021, 0x0000, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0021, 0, VR::DS, VM::M1, "SliceGap" },
{ 0x0021, 0x0022, 0, VR::DS, VM::M1, "StackRadialAngle" },
{ 0x0027, 0x0000, 0, VR::US, VM::M1, "" },
{ 0x0027, 0x0011, 0, VR::US, VM::M1TN, "" },
{ 0x0027, 0x0012, 0, VR::DS, VM::M1TN, "" },
{ 0x0027, 0x0013, 0, VR::DS, VM::M1TN, "" },
{ 0x0027, 0x0014, 0, VR::DS, VM::M1TN, "" },
{ 0x0027, 0x0015, 0, VR::DS, VM::M1TN, "" },
{ 0x0027, 0x0016, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::DS, VM::M1, "FPMin" },
{ 0x0029, 0x0020, 0, VR::DS, VM::M1, "FPMax" },
{ 0x0029, 0x0030, 0, VR::DS, VM::M1, "ScaledMinimum" },
{ 0x0029, 0x0040, 0, VR::DS, VM::M1, "ScaledMaximum" },
{ 0x0029, 0x0050, 0, VR::DS, VM::M1, "WindowMinimum" },
{ 0x0029, 0x0060, 0, VR::DS, VM::M1, "WindowMaximum" },
{ 0x0029, 0x0061, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0062, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0070, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0071, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0072, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0080, 0, VR::IS, VM::M1, "ViewCenter" },
{ 0x0029, 0x0081, 0, VR::IS, VM::M1, "ViewSize" },
{ 0x0029, 0x0082, 0, VR::IS, VM::M1, "ViewZoom" },
{ 0x0029, 0x0083, 0, VR::IS, VM::M1, "ViewTransform" },
{ 0x0041, 0x0007, 0, VR::LO, VM::M1, "" },
{ 0x0041, 0x0009, 0, VR::DS, VM::M1, "" },
{ 0x6001, 0x0000, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict083TagHashTable[] = {
   14,    31,    46,    53,    64,    69,    74,    79,    86,    93,
  100,   111,   118,     0,     8,     6,   178,    15,   217,    20,
  240,    27,    33,    29,     0,    32,    19,    39,    64,    49,
  130,     7,     5,   177,    18,   226,    21,   241,    26,    32,
   31,    18,    48,   129,    53,     0,     3,    19,   227,    30,
   17,    47,   128,     5,     0,     9,     2,   183,    16,   224,
   28,    34,    40,    80,     2,    12,   206,    17,   225,     2,
    9,   181,    36,    16,     2,     8,   180,    51,     7,     3,
    3,   228,    24,     0,    41,    96,     3,     4,   229,    42,
   97,    52,     9,     3,    14,   214,    37,    32,    43,    98,
    5,     1,    14,    10,   192,    25,    16,    35,    22,    44,
  112,     3,    22,   242,    34,    21,    45,   113,     8,     7,
  179,    11,   198,    13,   213,    23,   243,    33,    20,    38,
   48,    46,   114,    50,   131,
};

vtkDICOMDictionary::Dict Dict083Data = {
"PHILIPS MR/LAST",
13,
54,
Dict083TagHashTable,
Dict083Contents
};

// ----- AEGIS_DICOM_2.00 -----

DictEntry Dict084Contents[] = {
{ 0x0003, 0x0000, 0, VR::US, VM::M1TN, "" },
{ 0x0005, 0x0000, 0, VR::US, VM::M1TN, "" },
{ 0x0009, 0x0000, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0000, 0, VR::US, VM::M1TN, "" },
{ 0x0029, 0x0000, 0, VR::US, VM::M1TN, "" },
{ 0x1369, 0x0000, 0, VR::US, VM::M1TN, "" },
};

unsigned short Dict084TagHashTable[] = {
    2,     0,     6,     0,     0,     1,     0,     2,     0,     3,
    0,     4,     0,     5,     0,
};

vtkDICOMDictionary::Dict Dict084Data = {
"AEGIS_DICOM_2.00",
1,
6,
Dict084TagHashTable,
Dict084Contents
};

// ----- MeVis eD: Absolute Temporal Positions -----

DictEntry Dict085Contents[] = {
{ 0x0021, 0x0010, 0, VR::LT, VM::M1, "TimepointDateTime" },
{ 0x0021, 0x0011, 0, VR::CS, VM::M1, "TimepointDateTimeType" },
{ 0x0021, 0x0012, 0, VR::UN, VM::M1, "TimepointSeriesDescription" },
{ 0x0021, 0x0013, 0, VR::UN, VM::M1, "TimepointGradientDirections" },
{ 0x0021, 0x0071, 0, VR::UN, VM::M1, "TimepointEmptyFrames" },
};

unsigned short Dict085TagHashTable[] = {
    2,     0,     5,     0,    16,     1,    17,     2,    18,     3,
   19,     4,   113,
};

vtkDICOMDictionary::Dict Dict085Data = {
"MeVis eD: Absolute Temporal Positions",
1,
5,
Dict085TagHashTable,
Dict085Contents
};

// ----- NQLeft -----

DictEntry Dict086Contents[] = {
{ 0x0199, 0x0001, 0, VR::FL, VM::M1, "LeftCorticalWhiteMatter" },
{ 0x0199, 0x0002, 0, VR::FL, VM::M1, "LeftCorticalGrayMatter" },
{ 0x0199, 0x0003, 0, VR::FL, VM::M1, "Left3rdVentricle" },
{ 0x0199, 0x0004, 0, VR::FL, VM::M1, "Left4thVentricle" },
{ 0x0199, 0x0005, 0, VR::FL, VM::M1, "Left5thVentricle" },
{ 0x0199, 0x0006, 0, VR::FL, VM::M1, "LeftLateralVentricle" },
{ 0x0199, 0x0007, 0, VR::FL, VM::M1, "LeftInferiorLateralVentricle" },
{ 0x0199, 0x0008, 0, VR::FL, VM::M1, "LeftInferiorCSF" },
{ 0x0199, 0x0009, 0, VR::FL, VM::M1, "LeftCerebellarWhiteMatter" },
{ 0x0199, 0x000a, 0, VR::FL, VM::M1, "LeftCerebellarGrayMatter" },
{ 0x0199, 0x000b, 0, VR::FL, VM::M1, "LeftHippocampus" },
{ 0x0199, 0x000c, 0, VR::FL, VM::M1, "LeftAmygdala" },
{ 0x0199, 0x000d, 0, VR::FL, VM::M1, "LeftThalamus" },
{ 0x0199, 0x000e, 0, VR::FL, VM::M1, "LeftCaudate" },
{ 0x0199, 0x000f, 0, VR::FL, VM::M1, "LeftPutamen" },
{ 0x0199, 0x0010, 0, VR::FL, VM::M1, "LeftPallidum" },
{ 0x0199, 0x0011, 0, VR::FL, VM::M1, "LeftVentralDiencephalon" },
{ 0x0199, 0x0012, 0, VR::FL, VM::M1, "LeftNucleusAccumbens" },
{ 0x0199, 0x0013, 0, VR::FL, VM::M1, "LeftBrainStem" },
{ 0x0199, 0x0014, 0, VR::FL, VM::M1, "LeftExteriorCSF" },
{ 0x0199, 0x0015, 0, VR::FL, VM::M1, "LeftWMHypo" },
{ 0x0199, 0x0016, 0, VR::FL, VM::M1, "LeftOther" },
{ 0x0199, 0x0017, 0, VR::FL, VM::M1, "LeftCortexUnkown" },
{ 0x0199, 0x0018, 0, VR::FL, VM::M1, "LeftCortexBankssts" },
{ 0x0199, 0x0019, 0, VR::FL, VM::M1, "LeftCortexCaudalAnteriorCingulate" },
{ 0x0199, 0x001a, 0, VR::FL, VM::M1, "LeftCortexCaudalMiddleFrontal" },
{ 0x0199, 0x001b, 0, VR::FL, VM::M1, "LeftCortexCorpusCallosum" },
{ 0x0199, 0x001c, 0, VR::FL, VM::M1, "LeftCortexCuneus" },
{ 0x0199, 0x001d, 0, VR::FL, VM::M1, "LeftCortexEntorhinal" },
{ 0x0199, 0x001e, 0, VR::FL, VM::M1, "LeftCortexFusiform" },
{ 0x0199, 0x001f, 0, VR::FL, VM::M1, "LeftCortexInferiorParietal" },
{ 0x0199, 0x0020, 0, VR::FL, VM::M1, "LeftCortexInferiorTemporal" },
{ 0x0199, 0x0021, 0, VR::FL, VM::M1, "LeftCortexIsthmusCingulate" },
{ 0x0199, 0x0022, 0, VR::FL, VM::M1, "LeftCortexLateralOccipital" },
{ 0x0199, 0x0023, 0, VR::FL, VM::M1, "LeftCortexLateralOrbitoFrontal" },
{ 0x0199, 0x0024, 0, VR::FL, VM::M1, "LeftCortexLingual" },
{ 0x0199, 0x0025, 0, VR::FL, VM::M1, "LeftCortexMedialOrbitoFrontal" },
{ 0x0199, 0x0026, 0, VR::FL, VM::M1, "LeftCortexMiddleTemporal" },
{ 0x0199, 0x0027, 0, VR::FL, VM::M1, "LeftCortexParahippocampal" },
{ 0x0199, 0x0028, 0, VR::FL, VM::M1, "LeftCortexParacentral" },
{ 0x0199, 0x0029, 0, VR::FL, VM::M1, "LeftCortexParsOpercularis" },
{ 0x0199, 0x002a, 0, VR::FL, VM::M1, "LeftCortexParsOrbitalis" },
{ 0x0199, 0x002b, 0, VR::FL, VM::M1, "LeftCortexParsTriangularis" },
{ 0x0199, 0x002c, 0, VR::FL, VM::M1, "LeftCortexPericalcarine" },
{ 0x0199, 0x002d, 0, VR::FL, VM::M1, "LeftCortexPostcentral" },
{ 0x0199, 0x002e, 0, VR::FL, VM::M1, "LeftCortexPosteriorCingulate" },
{ 0x0199, 0x002f, 0, VR::FL, VM::M1, "LeftCortexPrecentral" },
{ 0x0199, 0x0030, 0, VR::FL, VM::M1, "LeftCortexPrecuneus" },
{ 0x0199, 0x0031, 0, VR::FL, VM::M1, "LeftCortexRostralAnteriorCingulate" },
{ 0x0199, 0x0032, 0, VR::FL, VM::M1, "LeftCortexRostralMiddleFrontal" },
{ 0x0199, 0x0033, 0, VR::FL, VM::M1, "LeftCortexSuperiorFrontal" },
{ 0x0199, 0x0034, 0, VR::FL, VM::M1, "LeftCortexSuperiorParietal" },
{ 0x0199, 0x0035, 0, VR::FL, VM::M1, "LeftCortexSuperiorTemporal" },
{ 0x0199, 0x0036, 0, VR::FL, VM::M1, "LeftCortexSupramarginal" },
{ 0x0199, 0x0037, 0, VR::FL, VM::M1, "LeftCortexFrontalPole" },
{ 0x0199, 0x0038, 0, VR::FL, VM::M1, "LeftCortexTemporalPole" },
{ 0x0199, 0x0039, 0, VR::FL, VM::M1, "LeftCortexTransvereTemporal" },
{ 0x0199, 0x003a, 0, VR::FL, VM::M1, "LeftMeningie" },
};

unsigned short Dict086TagHashTable[] = {
   15,    22,    31,    40,    49,    58,    67,    78,    89,   100,
  109,   118,   127,   136,     0,     3,     8,     9,    22,    23,
   44,    45,     4,     7,     8,    21,    22,    43,    44,    57,
   58,     4,     6,     7,    20,    21,    42,    43,    56,    57,
    4,     5,     6,    19,    20,    41,    42,    55,    56,     4,
    4,     5,    18,    19,    40,    41,    54,    55,     4,     3,
    4,    17,    18,    39,    40,    53,    54,     5,     2,     3,
   16,    17,    30,    31,    38,    39,    52,    53,     5,     1,
    2,    15,    16,    29,    30,    37,    38,    51,    52,     5,
    0,     1,    14,    15,    28,    29,    36,    37,    50,    51,
    4,    13,    14,    27,    28,    35,    36,    49,    50,     4,
   12,    13,    26,    27,    34,    35,    48,    49,     4,    11,
   12,    25,    26,    33,    34,    47,    48,     4,    10,    11,
   24,    25,    32,    33,    46,    47,     4,     9,    10,    23,
   24,    31,    32,    45,    46,
};

vtkDICOMDictionary::Dict Dict086Data = {
"NQLeft",
14,
58,
Dict086TagHashTable,
Dict086Contents
};

// ----- SPI-P-Private_ICS Release 1;3 -----

DictEntry Dict087Contents[] = {
{ 0x0029, 0x0000, 0, VR::ST, VM::M1, "" },
{ 0x0029, 0x0001, 0, VR::ST, VM::M1, "" },
};

unsigned short Dict087TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict087Data = {
"SPI-P-Private_ICS Release 1;3",
1,
2,
Dict087TagHashTable,
Dict087Contents
};

// ----- SPI-P-Private_ICS Release 1;2 -----

DictEntry Dict088Contents[] = {
{ 0x0029, 0x0000, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x0001, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x0002, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x0003, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x0004, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x0005, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x0030, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x00a0, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x00a1, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00a2, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x00a3, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x00a5, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x00a6, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x00d9, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict088TagHashTable[] = {
    4,    15,    28,     0,     5,     3,     3,     4,     4,     8,
  161,    12,   166,    13,   217,     6,     1,     1,     2,     2,
    6,    48,     7,   160,    10,   163,    11,   165,     3,     0,
    0,     5,     5,     9,   162,
};

vtkDICOMDictionary::Dict Dict088Data = {
"SPI-P-Private_ICS Release 1;2",
3,
14,
Dict088TagHashTable,
Dict088Contents
};

// ----- SPI-P-Private_ICS Release 1;1 -----

DictEntry Dict089Contents[] = {
{ 0x0029, 0x0000, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x0005, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x0006, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x0021, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x00c0, 0, VR::SL, VM::M1, "" },
{ 0x0029, 0x00c1, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x00cb, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00cc, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00cd, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x00d0, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x00d1, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x00d2, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x00d3, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x00d4, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x00d5, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x00d6, 0, VR::ST, VM::M1, "" },
};

unsigned short Dict089TagHashTable[] = {
    5,    14,    23,    32,     0,     4,     1,     5,     4,    33,
   12,   210,    16,   214,     4,     0,     0,     3,    32,     7,
  203,    13,   211,     4,     5,   192,     8,   204,    10,   208,
   14,   212,     5,     2,     6,     6,   193,     9,   205,    11,
  209,    15,   213,
};

vtkDICOMDictionary::Dict Dict089Data = {
"SPI-P-Private_ICS Release 1;1",
4,
17,
Dict089TagHashTable,
Dict089Contents
};

// ----- GEMS_GDXE_FALCON_04 -----

DictEntry Dict090Contents[] = {
{ 0x0011, 0x0003, 0, VR::UI, VM::M1, "ProcessedSeriesUID" },
{ 0x0011, 0x0004, 0, VR::CS, VM::M1, "AcquisitionType" },
{ 0x0011, 0x0005, 0, VR::UI, VM::M1, "AcquisitionUID" },
{ 0x0011, 0x0006, 0, VR::DS, VM::M1, "ImageDose" },
{ 0x0011, 0x0007, 0, VR::FL, VM::M1, "StudyDose" },
{ 0x0011, 0x0008, 0, VR::FL, VM::M1, "StudyDAP" },
{ 0x0011, 0x0009, 0, VR::SL, VM::M1, "NonDigitalExposures" },
{ 0x0011, 0x0010, 0, VR::SL, VM::M1, "TotalExposures" },
{ 0x0011, 0x0011, 0, VR::LT, VM::M1, "ROI" },
{ 0x0011, 0x0012, 0, VR::LT, VM::M1, "PatientSizeString" },
{ 0x0011, 0x0013, 0, VR::UI, VM::M1, "SPSUID" },
{ 0x0011, 0x0014, 0, VR::UI, VM::M1, "" },
{ 0x0011, 0x0015, 0, VR::DS, VM::M1, "DetectorARCGain" },
{ 0x0011, 0x0016, 0, VR::LT, VM::M1, "ProcessingDebugInfo" },
{ 0x0011, 0x0017, 0, VR::CS, VM::M1, "OverrideMode" },
{ 0x0011, 0x0019, 0, VR::DS, VM::M1, "FilmSpeedSelection" },
{ 0x0011, 0x0027, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0028, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0029, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0030, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0031, 0, VR::IS, VM::M1TN, "DetectedFieldOfView" },
{ 0x0011, 0x0032, 0, VR::IS, VM::M1TN, "AdjustedFieldOfView" },
{ 0x0011, 0x0033, 0, VR::DS, VM::M1, "DetectorExposureIndex" },
{ 0x0011, 0x0034, 0, VR::DS, VM::M1, "CompensatedDetectorExposure" },
{ 0x0011, 0x0035, 0, VR::DS, VM::M1, "UncompensatedDetectorExposure" },
{ 0x0011, 0x0036, 0, VR::DS, VM::M1, "MedianAnatomyCountValue" },
{ 0x0011, 0x0037, 0, VR::DS, VM::M2, "DEILowerAndUpperLimitValues" },
{ 0x0011, 0x0038, 0, VR::SL, VM::M6, "ShiftVectorForPasting" },
{ 0x0011, 0x0039, 0, VR::CS, VM::M6, "ImageNumberInPasting" },
{ 0x0011, 0x0040, 0, VR::SL, VM::M1, "PastingOverlap" },
{ 0x0011, 0x0041, 0, VR::IS, VM::M24, "SubImageCollimatorVertices" },
{ 0x0011, 0x0042, 0, VR::LO, VM::M1, "ViewIP" },
{ 0x0011, 0x0043, 0, VR::IS, VM::M24, "KeystoneCoordinates" },
{ 0x0011, 0x0044, 0, VR::CS, VM::M1, "ReceptorType" },
{ 0x0011, 0x0046, 0, VR::LO, VM::M1TN, "" },
{ 0x0011, 0x0047, 0, VR::DS, VM::M1, "" },
{ 0x0011, 0x0059, 0, VR::CS, VM::M1, "" },
{ 0x0011, 0x0060, 0, VR::CS, VM::M1, "" },
{ 0x0011, 0x006d, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict090TagHashTable[] = {
   10,    21,    30,    41,    52,    61,    72,    81,    88,     0,
    5,     0,     3,     8,    17,    16,    39,    24,    53,    30,
   65,     4,     7,    16,    23,    52,    31,    66,    36,    89,
    5,     2,     5,    10,    19,    18,    41,    26,    55,    32,
   67,     5,     1,     4,     9,    18,    17,    40,    25,    54,
   33,    68,     4,     4,     7,    12,    21,    28,    57,    37,
   96,     5,     3,     6,    11,    20,    20,    49,    27,    56,
   34,    70,     4,     6,     9,    14,    23,    19,    48,    35,
   71,     3,     5,     8,    13,    22,    22,    51,     4,    15,
   25,    21,    50,    29,    64,    38,   109,
};

vtkDICOMDictionary::Dict Dict090Data = {
"GEMS_GDXE_FALCON_04",
9,
39,
Dict090TagHashTable,
Dict090Contents
};

// ----- SPI-P-Private_ICS Release 1;5 -----

DictEntry Dict091Contents[] = {
{ 0x0029, 0x0050, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0055, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict091TagHashTable[] = {
    2,     0,     2,     0,    80,     1,    85,
};

vtkDICOMDictionary::Dict Dict091Data = {
"SPI-P-Private_ICS Release 1;5",
1,
2,
Dict091TagHashTable,
Dict091Contents
};

// ----- SPI-P-Private_ICS Release 1;4 -----

DictEntry Dict092Contents[] = {
{ 0x0029, 0x00d6, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00d7, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00d8, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00d9, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x00da, 0, VR::FL, VM::M1, "" },
{ 0x0029, 0x00dc, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00dd, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x00e0, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict092TagHashTable[] = {
    3,    14,     0,     5,     0,   214,     2,   216,     4,   218,
    5,   220,     7,   224,     3,     1,   215,     3,   217,     6,
  221,
};

vtkDICOMDictionary::Dict Dict092Data = {
"SPI-P-Private_ICS Release 1;4",
2,
8,
Dict092TagHashTable,
Dict092Contents
};

// ----- SPI-P-GV-CT Release 1 -----

DictEntry Dict093Contents[] = {
{ 0x0009, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0030, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0040, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0060, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0070, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0075, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0080, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0090, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0008, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0009, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x000a, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::TM, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0061, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0063, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0064, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0065, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0070, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0081, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00a0, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00a1, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a2, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a3, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b0, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00b1, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0030, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0040, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0060, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0070, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0080, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0090, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x00a0, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x00a1, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x00a2, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x00a3, 0, VR::LT, VM::M1, "" },
{ 0x0021, 0x00a4, 0, VR::LT, VM::M1, "" },
{ 0x0021, 0x00b0, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x00c0, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0030, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0031, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0032, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0033, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0080, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0090, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x00d0, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x00d1, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict093TagHashTable[] = {
   15,    20,    33,    48,    61,    68,    77,    82,    85,    92,
  103,   108,   117,   126,     0,     2,    24,   129,    35,    80,
    6,     3,    48,    10,   144,    15,    32,    23,   128,    32,
   32,    47,    16,     7,     4,    64,    12,     9,    16,    80,
   29,   163,    31,   177,    43,   163,    46,   192,     6,    11,
    8,    28,   162,    30,   176,    33,    48,    42,   162,    52,
  128,     3,     5,    80,    27,   161,    41,   161,     4,    13,
   10,    26,   160,    40,   160,    53,   144,     2,     6,    96,
   22,   112,     1,    45,   176,     3,     7,   112,    17,    96,
   36,    96,     5,     0,     0,    14,    16,    18,    97,    38,
  128,    44,   164,     2,    37,   112,    49,    49,     4,     1,
   16,    19,    99,    39,   144,    48,    48,     4,    20,   100,
   34,    64,    51,    51,    54,   208,     7,     2,    32,     8,
  117,     9,   128,    21,   101,    25,   144,    50,    50,    55,
  209,
};

vtkDICOMDictionary::Dict Dict093Data = {
"SPI-P-GV-CT Release 1",
14,
56,
Dict093TagHashTable,
Dict093Contents
};

// ----- GEMS_ADWSoft_DPO1 -----

DictEntry Dict094Contents[] = {
{ 0x0039, 0x0095, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict094TagHashTable[] = {
    2,     0,     1,     0,   149,
};

vtkDICOMDictionary::Dict Dict094Data = {
"GEMS_ADWSoft_DPO1",
1,
1,
Dict094TagHashTable,
Dict094Contents
};

// ----- PHILIPS MR R5.5/PART -----

DictEntry Dict095Contents[] = {
{ 0x0019, 0x0000, 0, VR::DS, VM::M1, "FieldOfView" },
};

unsigned short Dict095TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict095Data = {
"PHILIPS MR R5.5/PART",
1,
1,
Dict095TagHashTable,
Dict095Contents
};

// ----- Harmony R2.0 -----

DictEntry Dict096Contents[] = {
{ 0x0019, 0x0079, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x007c, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x007d, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0081, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0083, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0084, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0085, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0086, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0087, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0088, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0089, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008c, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x008d, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x008f, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0090, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0091, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0092, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0093, 0, VR::DS, VM::M2, "" },
{ 0x0019, 0x0094, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0095, 0, VR::LO, VM::M1TN, "" },
{ 0x0019, 0x0096, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0097, 0, VR::IS, VM::M2, "" },
{ 0x0019, 0x0099, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict096TagHashTable[] = {
    7,    14,    25,    34,    43,    56,     0,     3,     9,   135,
   14,   141,    17,   145,     5,     0,   121,     8,   134,    12,
  138,    13,   140,    16,   144,     4,     5,   131,     7,   133,
   11,   137,    23,   151,     4,     4,   130,     6,   132,    10,
  136,    22,   150,     6,     1,   124,     3,   129,    15,   143,
   19,   147,    21,   149,    24,   153,     3,     2,   125,    18,
  146,    20,   148,
};

vtkDICOMDictionary::Dict Dict096Data = {
"Harmony R2.0",
6,
25,
Dict096TagHashTable,
Dict096Contents
};

// ----- AGFA_ADC_Compact -----

DictEntry Dict097Contents[] = {
{ 0x0019, 0x0030, 0, VR::ST, VM::M1, "SetOfDestinationTypes" },
{ 0x0019, 0x0040, 0, VR::ST, VM::M1, "SetOfDestinationIds" },
{ 0x0019, 0x0050, 0, VR::ST, VM::M1, "SetOfProcessingCodes" },
{ 0x0019, 0x0060, 0, VR::US, VM::M1, "NumberOfSeriesInStudy" },
{ 0x0019, 0x0061, 0, VR::US, VM::M1, "SessionNumber" },
{ 0x0019, 0x0062, 0, VR::SH, VM::M1, "IDStationName" },
{ 0x0019, 0x0070, 0, VR::US, VM::M1, "NumberOfImagesInSeries" },
{ 0x0019, 0x0071, 0, VR::US, VM::M1, "BreakCondition" },
{ 0x0019, 0x0072, 0, VR::US, VM::M1, "WaitOrHoldFlag" },
{ 0x0019, 0x0073, 0, VR::US, VM::M1, "ScanResFlag" },
{ 0x0019, 0x0074, 0, VR::SH, VM::M1, "OperationCode" },
{ 0x0019, 0x0095, 0, VR::CS, VM::M1, "ImageQuality" },
};

unsigned short Dict097TagHashTable[] = {
    4,    13,    22,     0,     4,     2,    80,     3,    96,     7,
  113,    10,   116,     4,     1,    64,     4,    97,     8,   114,
   11,   149,     4,     0,    48,     5,    98,     6,   112,     9,
  115,
};

vtkDICOMDictionary::Dict Dict097Data = {
"AGFA_ADC_Compact",
3,
12,
Dict097TagHashTable,
Dict097Contents
};

// ----- SIEMENS SMS-AX  ACQ 1.0 -----

DictEntry Dict098Contents[] = {
{ 0x0021, 0x0000, 0, VR::US, VM::M1, "AcquisitionType" },
{ 0x0021, 0x0001, 0, VR::US, VM::M1, "AcquisitionMode" },
{ 0x0021, 0x0002, 0, VR::US, VM::M1, "FootswitchIndex" },
{ 0x0021, 0x0003, 0, VR::US, VM::M1, "AcquisitionRoom" },
{ 0x0021, 0x0004, 0, VR::SL, VM::M1, "CurrentTimeProduct" },
{ 0x0021, 0x0005, 0, VR::SL, VM::M1, "ImagerReceptorDose" },
{ 0x0021, 0x0006, 0, VR::SL, VM::M1, "SkinDosePercent" },
{ 0x0021, 0x0007, 0, VR::SL, VM::M1, "SkinDoseAccumulation" },
{ 0x0021, 0x0008, 0, VR::SL, VM::M1, "SkinDoseRate" },
{ 0x0021, 0x0009, 0, VR::UL, VM::M1, "ImpacFilename" },
{ 0x0021, 0x000A, 0, VR::UL, VM::M1, "CopperFilter" },
{ 0x0021, 0x000B, 0, VR::US, VM::M1, "MeasuringField" },
{ 0x0021, 0x000C, 0, VR::SS, VM::M3, "PostBlankingCircle" },
{ 0x0021, 0x000D, 0, VR::SS, VM::M2T2N, "DynaAngles" },
{ 0x0021, 0x000E, 0, VR::SS, VM::M1, "TotalSteps" },
{ 0x0021, 0x000F, 0, VR::SL, VM::M4TN, "DynaXRayInfo" },
{ 0x0021, 0x0010, 0, VR::US, VM::M1, "ModalityLUTInputGamma" },
{ 0x0021, 0x0011, 0, VR::US, VM::M1, "ModalityLUTOutputGamma" },
{ 0x0021, 0x0012, 0, VR::OB, VM::M1, "SHSTPAR" },
{ 0x0021, 0x0013, 0, VR::US, VM::M1, "AcquisitionZoom" },
{ 0x0021, 0x0014, 0, VR::SS, VM::M1, "DynaAngulationStep" },
{ 0x0021, 0x0015, 0, VR::US, VM::M1, "DDOValue" },
{ 0x0021, 0x0016, 0, VR::US, VM::M1, "DRSingleFlag" },
{ 0x0021, 0x0017, 0, VR::SL, VM::M1, "SourcetoIsocenter" },
{ 0x0021, 0x0018, 0, VR::US, VM::M1, "PressureData" },
{ 0x0021, 0x0019, 0, VR::SL, VM::M1, "ECGIndexArray" },
{ 0x0021, 0x001A, 0, VR::US, VM::M1, "FDFlag" },
{ 0x0021, 0x001B, 0, VR::OB, VM::M1, "SHZOOM" },
{ 0x0021, 0x001C, 0, VR::OB, VM::M1, "SHCOLPAR" },
{ 0x0021, 0x001D, 0, VR::US, VM::M1, "KFactor" },
{ 0x0021, 0x001E, 0, VR::US, VM::M8, "EVE" },
{ 0x0021, 0x001F, 0, VR::SL, VM::M1, "TotalSceneTime" },
{ 0x0021, 0x0020, 0, VR::US, VM::M1, "RestoreFlag" },
{ 0x0021, 0x0021, 0, VR::US, VM::M1, "StandMovementFlag" },
{ 0x0021, 0x0022, 0, VR::US, VM::M1, "FDRows" },
{ 0x0021, 0x0023, 0, VR::US, VM::M1, "FDColumns" },
{ 0x0021, 0x0024, 0, VR::US, VM::M1, "TableMovementFlag" },
{ 0x0021, 0x0026, 0, VR::DS, VM::M1, "CrispyXPIFilterValue" },
{ 0x0021, 0x0027, 0, VR::US, VM::M1, "ICStentFlag" },
{ 0x0021, 0x0028, 0, VR::SQ, VM::M1, "GammaLUTSequence" },
{ 0x0021, 0x0029, 0, VR::DS, VM::M1, "AcquisitionSceneTime" },
{ 0x0021, 0x002A, 0, VR::IS, VM::M1, "ThreeDCardiacPhaseCenter" },
{ 0x0021, 0x002B, 0, VR::IS, VM::M1, "ThreeDCardiacPhaseWidth" },
{ 0x0021, 0x0030, 0, VR::OB, VM::M1, "OrganProgramInfo" },
{ 0x0021, 0x003A, 0, VR::IS, VM::M1, "DDOKernelsize" },
{ 0x0021, 0x003B, 0, VR::IS, VM::M1, "mAsModulation" },
{ 0x0021, 0x003C, 0, VR::DT, VM::M1TN, "ThreeDRPeakReferenceTime" },
{ 0x0021, 0x003D, 0, VR::SL, VM::M1TN, "ECGFrameTimeVector" },
{ 0x0021, 0x003E, 0, VR::SL, VM::M1, "ECGStartTimeOfRun" },
{ 0x0021, 0x0040, 0, VR::US, VM::M3, "GammaLUTDescriptor" },
{ 0x0021, 0x0041, 0, VR::LO, VM::M1, "GammaLUTType" },
{ 0x0021, 0x0042, 0, VR::US, VM::M1TN, "GammaLUTData" },
{ 0x0021, 0x0043, 0, VR::US, VM::M1, "GlobalGain" },
{ 0x0021, 0x0044, 0, VR::US, VM::M1, "GlobalOffset" },
{ 0x0021, 0x0045, 0, VR::US, VM::M1, "DIPPMode" },
{ 0x0021, 0x0046, 0, VR::US, VM::M1, "ArtisSystemType" },
{ 0x0021, 0x0047, 0, VR::US, VM::M1, "ArtisTableType" },
{ 0x0021, 0x0048, 0, VR::US, VM::M1, "ArtisTableTopType" },
{ 0x0021, 0x0049, 0, VR::US, VM::M1, "WaterValue" },
{ 0x0021, 0x0051, 0, VR::DS, VM::M1, "ThreeDPositionerPrimaryStartAngle" },
{ 0x0021, 0x0052, 0, VR::DS, VM::M1, "ThreeDPositionerSecondaryStartAngle" },
{ 0x0021, 0x0053, 0, VR::SS, VM::M3, "StandPosition" },
{ 0x0021, 0x0054, 0, VR::SS, VM::M1, "RotationAngle" },
{ 0x0021, 0x0055, 0, VR::US, VM::M1, "ImageRotation" },
{ 0x0021, 0x0056, 0, VR::SS, VM::M3, "TableCoordinates" },
{ 0x0021, 0x0057, 0, VR::SS, VM::M3, "IsocenterTablePosition" },
{ 0x0021, 0x0058, 0, VR::DS, VM::M1, "TableObjectDistance" },
{ 0x0021, 0x0059, 0, VR::FL, VM::M12TN, "CarmCoordinateSystem" },
{ 0x0021, 0x005A, 0, VR::FL, VM::M6TN, "RobotAxes" },
{ 0x0021, 0x005B, 0, VR::FL, VM::M12, "TableCoordinateSystem" },
{ 0x0021, 0x005C, 0, VR::FL, VM::M12, "PatientCoordinateSystem" },
{ 0x0021, 0x005D, 0, VR::SS, VM::M1TN, "Angulation" },
{ 0x0021, 0x005E, 0, VR::SS, VM::M1TN, "Orbital" },
{ 0x0021, 0x0061, 0, VR::SS, VM::M1, "LargeVolumeOverlap" },
{ 0x0021, 0x0062, 0, VR::US, VM::M1, "ReconstructionPreset" },
{ 0x0021, 0x0063, 0, VR::SS, VM::M1, "ThreeDStartAngle" },
{ 0x0021, 0x0064, 0, VR::SL, VM::M1, "ThreeDPlannedAngle" },
{ 0x0021, 0x0065, 0, VR::SL, VM::M1, "ThreeDRotationPlaneAlpha" },
{ 0x0021, 0x0066, 0, VR::SL, VM::M1, "ThreeDRotationPlaneBeta" },
{ 0x0021, 0x0067, 0, VR::SL, VM::M1, "ThreeDFirstImageAngle" },
{ 0x0021, 0x0068, 0, VR::SS, VM::M1TN, "ThreeDTriggerAngle" },
{ 0x0021, 0x0071, 0, VR::DS, VM::M1TN, "DetectorRotation" },
{ 0x0021, 0x0072, 0, VR::SS, VM::M1TN, "PhysicalDetectorRotation" },
{ 0x0021, 0x0081, 0, VR::SS, VM::M1, "TableTilt" },
{ 0x0021, 0x0082, 0, VR::SS, VM::M1, "TableRotation" },
{ 0x0021, 0x0083, 0, VR::SS, VM::M1, "TableCradleTilt" },
{ 0x0021, 0x00A0, 0, VR::OB, VM::M1, "Crispy1Container" },
{ 0x0021, 0x00A3, 0, VR::SQ, VM::M1, "ThreeDCardiacTriggerSequence" },
{ 0x0021, 0x00A4, 0, VR::DT, VM::M1, "ThreeDFrameReferenceDateTime" },
{ 0x0021, 0x00A5, 0, VR::FD, VM::M1, "ThreeDCardiacTriggerDelayTime" },
{ 0x0021, 0x00A6, 0, VR::FD, VM::M1, "ThreeDRRIntervalTimeMeasured" },
};

unsigned short Dict098TagHashTable[] = {
   23,    30,    39,    48,    59,    68,    79,    92,   103,   114,
  125,   136,   147,   156,   165,   174,   185,   196,   205,   212,
  217,   220,     0,     3,    13,    13,    33,    33,    74,    98,
    4,    12,    12,    32,    32,    75,    99,    90,   166,     4,
   15,    15,    35,    35,    76,   100,    89,   165,     5,    14,
   14,    34,    34,    59,    81,    77,   101,    88,   164,     4,
   17,    17,    45,    59,    60,    82,    78,   102,     5,    16,
   16,    36,    36,    44,    58,    61,    83,    79,   103,     6,
   19,    19,    38,    39,    47,    61,    62,    84,    80,   104,
   85,   131,     5,    18,    18,    37,    38,    46,    60,    63,
   85,    84,   130,     5,    21,    21,    40,    41,    49,    64,
   64,    86,    83,   129,     5,    20,    20,    39,    40,    48,
   62,    50,    65,    65,    87,     5,     1,     1,    23,    23,
   42,    43,    51,    66,    66,    88,     5,     0,     0,    22,
   22,    41,    42,    52,    67,    67,    89,     4,     3,     3,
   25,    25,    53,    68,    68,    90,     4,     2,     2,    24,
   24,    54,    69,    69,    91,     4,     5,     5,    27,    27,
   55,    70,    70,    92,     5,     4,     4,    26,    26,    56,
   71,    71,    93,    81,   113,     5,     7,     7,    29,    29,
   57,    72,    72,    94,    82,   114,     4,     6,     6,    28,
   28,    43,    48,    58,    73,     3,     9,     9,    31,    31,
   87,   163,     2,     8,     8,    30,    30,     1,    11,    11,
    3,    10,    10,    73,    97,    86,   160,
};

vtkDICOMDictionary::Dict Dict098Data = {
"SIEMENS SMS-AX  ACQ 1.0",
22,
91,
Dict098TagHashTable,
Dict098Contents
};

// ----- SPI-P-CTBE-Private Release 1 -----

DictEntry Dict099Contents[] = {
{ 0x0021, 0x0000, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict099TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict099Data = {
"SPI-P-CTBE-Private Release 1",
1,
1,
Dict099TagHashTable,
Dict099Contents
};

// ----- SIEMENS SYNGO VOLUME -----

DictEntry Dict100Contents[] = {
{ 0x0029, 0x0012, 0, VR::US, VM::M1, "Slices" },
{ 0x0029, 0x0014, 0, VR::OB, VM::M1, "VolumeHistogram" },
{ 0x0029, 0x0018, 0, VR::IS, VM::M1, "VolumeLevel" },
{ 0x0029, 0x0030, 0, VR::DS, VM::M3, "VoxelSpacing" },
{ 0x0029, 0x0032, 0, VR::DS, VM::M3, "VolumePositionPatient" },
{ 0x0029, 0x0037, 0, VR::DS, VM::M9, "VolumeOrientationPatient" },
{ 0x0029, 0x0040, 0, VR::CS, VM::M1, "ResamplingFlag" },
{ 0x0029, 0x0042, 0, VR::CS, VM::M1, "NormalizationFlag" },
{ 0x0029, 0x0044, 0, VR::SQ, VM::M1, "SubVolumeSequence" },
{ 0x0029, 0x0046, 0, VR::UL, VM::M1, "HistogramNumberOfBins" },
{ 0x0029, 0x0047, 0, VR::OB, VM::M1, "VolumeHistogramData" },
};

unsigned short Dict100TagHashTable[] = {
    3,    14,     0,     5,     5,    55,     6,    64,     7,    66,
    8,    68,     9,    70,     6,     0,    18,     1,    20,     2,
   24,     3,    48,     4,    50,    10,    71,
};

vtkDICOMDictionary::Dict Dict100Data = {
"SIEMENS SYNGO VOLUME",
2,
11,
Dict100TagHashTable,
Dict100Contents
};

// ----- Applicare/RadWorks/Version 6.0 -----

DictEntry Dict101Contents[] = {
{ 0x4103, 0x0001, 0, VR::AT, VM::M1TN, "NonExistentTags" },
{ 0x4103, 0x0002, 0, VR::UI, VM::M1TN, "NonExistentObjects" },
{ 0x4105, 0x0001, 0, VR::CS, VM::M1, "AnnotationType" },
{ 0x4105, 0x0002, 0, VR::LO, VM::M1, "AnnotationValue" },
{ 0x4105, 0x0003, 0, VR::UI, VM::M1, "CutlineImageUID" },
{ 0x4105, 0x0004, 0, VR::UI, VM::M1, "CutlineSetUID" },
{ 0x4105, 0x0005, 0, VR::US, VM::M3, "AnnotationColor" },
{ 0x4105, 0x0006, 0, VR::CS, VM::M1, "AnnotationLineStyle" },
{ 0x4105, 0x0007, 0, VR::SH, VM::M1, "AnnotationLabel" },
{ 0x4105, 0x0008, 0, VR::PN, VM::M1, "AnnotationCreator" },
{ 0x4105, 0x0009, 0, VR::DA, VM::M1, "AnnotationCreationDate" },
{ 0x4105, 0x000A, 0, VR::TM, VM::M1, "AnnotationCreationTime" },
{ 0x4105, 0x000B, 0, VR::SQ, VM::M1, "AnnotationModificationSequence" },
{ 0x4105, 0x000C, 0, VR::PN, VM::M1, "AnnotationModifier" },
{ 0x4105, 0x000D, 0, VR::DA, VM::M1, "AnnotationModificationDate" },
{ 0x4105, 0x000E, 0, VR::TM, VM::M1, "AnnotationModificationTime" },
{ 0x4105, 0x0010, 0, VR::US, VM::M1, "" },
{ 0x4107, 0x0001, 0, VR::SQ, VM::M1, "RequestedPaletteColorLUT" },
};

unsigned short Dict101TagHashTable[] = {
    5,    14,    25,    36,     0,     4,     2,     1,     6,     5,
   10,     9,    14,    13,     5,     1,     2,     5,     4,     9,
    8,    13,    12,    16,    16,     5,     0,     1,     4,     3,
    8,     7,    12,    11,    17,     1,     4,     3,     2,     7,
    6,    11,    10,    15,    14,
};

vtkDICOMDictionary::Dict Dict101Data = {
"Applicare/RadWorks/Version 6.0",
4,
18,
Dict101TagHashTable,
Dict101Contents
};

// ----- SIEMENS MED SP DXMG WH AWS 1 -----

DictEntry Dict102Contents[] = {
{ 0x0019, 0x0001, 0, VR::UL, VM::M1TN, "AECCoordinates" },
{ 0x0019, 0x0002, 0, VR::US, VM::M2, "AECCoordinatesSize" },
{ 0x0019, 0x0010, 0, VR::ST, VM::M1, "DerivationDescription" },
{ 0x0041, 0x0002, 0, VR::SH, VM::M1, "ReasonForTheRequestedProcedure" },
{ 0x0051, 0x0010, 0, VR::DS, VM::M1, "" },
{ 0x0051, 0x0037, 0, VR::DS, VM::M6, "" },
{ 0x0051, 0x0050, 0, VR::UI, VM::M1, "" },
{ 0x0051, 0x0060, 0, VR::DS, VM::M1, "PrimaryPositionerScanArc" },
{ 0x0051, 0x0061, 0, VR::DS, VM::M1, "SecondaryPositionerScanArc" },
{ 0x0051, 0x0062, 0, VR::DS, VM::M1, "PrimaryPositionerScanStartAngle" },
{ 0x0051, 0x0063, 0, VR::DS, VM::M1, "SecondaryPositionerScanStartAngle" },
{ 0x0051, 0x0064, 0, VR::DS, VM::M1, "PrimaryPositionerIncrement" },
{ 0x0051, 0x0065, 0, VR::DS, VM::M1, "SecondaryPositionerIncrement" },
{ 0x0055, 0x0001, 0, VR::LO, VM::M1, "ProjectionViewDisplayString" },
};

unsigned short Dict102TagHashTable[] = {
    4,    17,    30,     0,     6,     0,     1,     1,     2,     2,
   16,     3,     2,     8,    97,     9,    98,     6,     4,    16,
    5,    55,     6,    80,     7,    96,    12,   101,    13,     1,
    2,    10,    99,    11,   100,
};

vtkDICOMDictionary::Dict Dict102Data = {
"SIEMENS MED SP DXMG WH AWS 1",
3,
14,
Dict102TagHashTable,
Dict102Contents
};

// ----- SIEMENS MR PS 04 -----

DictEntry Dict103Contents[] = {
{ 0x0021, 0x0001, 0, VR::FD, VM::M1TN, "" },
};

unsigned short Dict103TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict103Data = {
"SIEMENS MR PS 04",
1,
1,
Dict103TagHashTable,
Dict103Contents
};

// ----- GEMS_Ultrasound_MovieGroup_001 -----

DictEntry Dict104Contents[] = {
{ 0x7fe1, 0x0001, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0002, 0, VR::LO, VM::M1, "" },
{ 0x7fe1, 0x0003, 0, VR::UL, VM::M1, "" },
{ 0x7fe1, 0x0008, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0012, 0, VR::LO, VM::M1, "" },
{ 0x7fe1, 0x0018, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0020, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0024, 0, VR::SH, VM::M1, "" },
{ 0x7fe1, 0x0026, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0030, 0, VR::LO, VM::M1, "" },
{ 0x7fe1, 0x0032, 0, VR::UL, VM::M1, "" },
{ 0x7fe1, 0x0036, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0037, 0, VR::UL, VM::M1, "" },
{ 0x7fe1, 0x003a, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x003c, 0, VR::FD, VM::M1, "" },
{ 0x7fe1, 0x0043, 0, VR::OB, VM::M1, "" },
{ 0x7fe1, 0x0048, 0, VR::FD, VM::M1, "" },
{ 0x7fe1, 0x0049, 0, VR::UL, VM::M1, "" },
{ 0x7fe1, 0x0051, 0, VR::FL, VM::M1, "" },
{ 0x7fe1, 0x0052, 0, VR::FD, VM::M1, "" },
{ 0x7fe1, 0x0053, 0, VR::UL, VM::M1, "" },
{ 0x7fe1, 0x0054, 0, VR::SL, VM::M1, "" },
{ 0x7fe1, 0x0055, 0, VR::OB, VM::M1, "" },
{ 0x7fe1, 0x0057, 0, VR::LT, VM::M1, "" },
{ 0x7fe1, 0x0060, 0, VR::OB, VM::M1, "" },
{ 0x7fe1, 0x0061, 0, VR::OW, VM::M1, "" },
{ 0x7fe1, 0x0069, 0, VR::OW, VM::M1, "" },
{ 0x7fe1, 0x0070, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0071, 0, VR::UL, VM::M1, "" },
{ 0x7fe1, 0x0072, 0, VR::LO, VM::M1, "" },
{ 0x7fe1, 0x0073, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0074, 0, VR::LO, VM::M1, "" },
{ 0x7fe1, 0x0075, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0077, 0, VR::FD, VM::M1, "" },
{ 0x7fe1, 0x0079, 0, VR::SL, VM::M1, "" },
{ 0x7fe1, 0x0083, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0084, 0, VR::LO, VM::M1, "" },
{ 0x7fe1, 0x0085, 0, VR::SQ, VM::M1, "" },
{ 0x7fe1, 0x0086, 0, VR::SL, VM::M1, "" },
{ 0x7fe1, 0x0087, 0, VR::FD, VM::M1, "" },
{ 0x7fe1, 0x0088, 0, VR::FD, VM::M1, "" },
};

unsigned short Dict104TagHashTable[] = {
   11,    24,    29,    46,    55,    68,    75,    80,    87,   102,
    0,     6,     4,    16,    11,    50,    15,    60,    23,    85,
   34,   119,    39,   134,     2,    22,    84,    40,   135,     8,
    6,    24,     9,    38,    10,    48,    14,    58,    18,    73,
   21,    83,    26,    97,    33,   117,     4,    17,    72,    20,
   82,    25,    96,    32,   116,     6,     1,     2,     8,    36,
   19,    81,    27,   105,    31,   115,    41,   136,     3,     2,
    3,    30,   114,    36,   131,     2,    12,    54,    29,   113,
    3,     0,     1,    13,    55,    28,   112,     7,     3,     8,
    5,    18,     7,    32,    16,    67,    24,    87,    35,   121,
   37,   132,     1,    38,   133,
};

vtkDICOMDictionary::Dict Dict104Data = {
"GEMS_Ultrasound_MovieGroup_001",
10,
42,
Dict104TagHashTable,
Dict104Contents
};

// ----- GEMS_DL_STUDY_01 -----

DictEntry Dict105Contents[] = {
{ 0x0015, 0x0080, 0, VR::DS, VM::M1, "Study Dose" },
{ 0x0015, 0x0081, 0, VR::DS, VM::M1, "StudyTotalDap" },
{ 0x0015, 0x0082, 0, VR::DS, VM::M1, "FluoroDoseAreaProduct" },
{ 0x0015, 0x0083, 0, VR::IS, VM::M1, "Study luoroTime" },
{ 0x0015, 0x0084, 0, VR::DS, VM::M1, "CineDoseAreaProduct" },
{ 0x0015, 0x0085, 0, VR::IS, VM::M1, "StudyRecordTime" },
{ 0x0015, 0x0086, 0, VR::IS, VM::M1, "LastXANumber" },
{ 0x0015, 0x0088, 0, VR::PN, VM::M1TN, "DefOperatorName" },
{ 0x0015, 0x0089, 0, VR::PN, VM::M1TN, "DefPerformingPhysicianName" },
{ 0x0015, 0x008A, 0, VR::CS, VM::M2, "DefPatientOrientation" },
{ 0x0015, 0x008B, 0, VR::IS, VM::M1, "LastScNumber" },
{ 0x0015, 0x008E, 0, VR::UI, VM::M1, "CommonSeriesInstanceUID" },
{ 0x0015, 0x008F, 0, VR::IS, VM::M1, "StudyNumber" },
{ 0x0015, 0x0092, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x0093, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x0094, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x0095, 0, VR::IS, VM::M1, "" },
{ 0x0015, 0x0096, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x0097, 0, VR::IS, VM::M1, "" },
{ 0x0015, 0x0098, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x0099, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x009a, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x009b, 0, VR::IS, VM::M1, "" },
{ 0x0015, 0x009c, 0, VR::FL, VM::M1, "" },
{ 0x0015, 0x009d, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict105TagHashTable[] = {
    7,    16,    27,    38,    49,    56,     0,     4,     1,   129,
   10,   139,    14,   147,    24,   157,     5,     0,   128,     6,
  134,     9,   138,    13,   146,    23,   156,     5,     5,   133,
    8,   137,    12,   143,    18,   151,    22,   155,     5,     4,
  132,     7,   136,    11,   142,    17,   150,    21,   154,     3,
    3,   131,    16,   149,    20,   153,     3,     2,   130,    15,
  148,    19,   152,
};

vtkDICOMDictionary::Dict Dict105Data = {
"GEMS_DL_STUDY_01",
6,
25,
Dict105TagHashTable,
Dict105Contents
};

// ----- Silhouette VRS 3.0 -----

DictEntry Dict106Contents[] = {
{ 0x0029, 0x0013, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0014, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0017, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0018, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0019, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x001a, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x001b, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x001c, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x001d, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x001e, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0027, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0028, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0030, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0032, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0034, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0035, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0036, 0, VR::US, VM::M1, "" },
};

unsigned short Dict106TagHashTable[] = {
    5,    12,    25,    34,     0,     3,     4,    25,     8,    29,
   15,    53,     6,     1,    20,     3,    24,     7,    28,    11,
   40,    12,    48,    14,    52,     4,     0,    19,     2,    23,
    6,    27,    10,    39,     4,     5,    26,     9,    30,    13,
   50,    16,    54,
};

vtkDICOMDictionary::Dict Dict106Data = {
"Silhouette VRS 3.0",
4,
17,
Dict106TagHashTable,
Dict106Contents
};

// ----- GEMS_HELIOS_01 -----

DictEntry Dict107Contents[] = {
{ 0x0045, 0x0001, 0, VR::SS, VM::M1, "NumberOfMacroRowsInDetector" },
{ 0x0045, 0x0002, 0, VR::FL, VM::M1, "MacroWidthAtISOCenter" },
{ 0x0045, 0x0003, 0, VR::SS, VM::M1, "DASType" },
{ 0x0045, 0x0004, 0, VR::SS, VM::M1, "DASGain" },
{ 0x0045, 0x0005, 0, VR::SS, VM::M1, "DASTemprature" },
{ 0x0045, 0x0006, 0, VR::CS, VM::M1, "TableDirection" },
{ 0x0045, 0x0007, 0, VR::FL, VM::M1, "ZSmoothingFactor" },
{ 0x0045, 0x0008, 0, VR::SS, VM::M1, "ViewWeightingMode" },
{ 0x0045, 0x0009, 0, VR::SS, VM::M1, "SigmaRowNumber" },
{ 0x0045, 0x000A, 0, VR::FL, VM::M1, "MinimumDASValue" },
{ 0x0045, 0x000B, 0, VR::FL, VM::M1, "MaximumOffsetValue" },
{ 0x0045, 0x000C, 0, VR::SS, VM::M1, "NumberOfViewsShifted" },
{ 0x0045, 0x000D, 0, VR::SS, VM::M1, "ZTrackingFlag" },
{ 0x0045, 0x000E, 0, VR::FL, VM::M1, "MeanZError" },
{ 0x0045, 0x000F, 0, VR::FL, VM::M1, "ZTrackingError" },
{ 0x0045, 0x0010, 0, VR::SS, VM::M1, "StartView2A" },
{ 0x0045, 0x0011, 0, VR::SS, VM::M1, "NumberOfViews2A" },
{ 0x0045, 0x0012, 0, VR::SS, VM::M1, "StartView1A" },
{ 0x0045, 0x0013, 0, VR::SS, VM::M1, "SigmaMode" },
{ 0x0045, 0x0014, 0, VR::SS, VM::M1, "NumberOfViews1A" },
{ 0x0045, 0x0015, 0, VR::SS, VM::M1, "StartView2B" },
{ 0x0045, 0x0016, 0, VR::SS, VM::M1, "NumberViews2B" },
{ 0x0045, 0x0017, 0, VR::SS, VM::M1, "StartView1B" },
{ 0x0045, 0x0018, 0, VR::SS, VM::M1, "NumberOfViews1B" },
{ 0x0045, 0x0021, 0, VR::SS, VM::M1, "IterboneFlag" },
{ 0x0045, 0x0022, 0, VR::SS, VM::M1, "PeristalticFlag" },
{ 0x0045, 0x0030, 0, VR::CS, VM::M1, "CardiacReconAlgorithm" },
{ 0x0045, 0x0031, 0, VR::CS, VM::M1, "AvgHeartRateForImage" },
{ 0x0045, 0x0032, 0, VR::FL, VM::M1, "TemporalResolution" },
{ 0x0045, 0x0033, 0, VR::CS, VM::M1, "PctRpeakDelay" },
{ 0x0045, 0x0036, 0, VR::CS, VM::M1, "EkgFullMaStartPhase" },
{ 0x0045, 0x0037, 0, VR::CS, VM::M1, "EkgFullMaEndPhase" },
{ 0x0045, 0x0038, 0, VR::CS, VM::M1, "EkgModulationMaxMa" },
{ 0x0045, 0x0039, 0, VR::CS, VM::M1, "EkgModulationMinMa" },
{ 0x0045, 0x003B, 0, VR::LO, VM::M1, "NoiseReductionImageFilterDesc" },
};

unsigned short Dict107TagHashTable[] = {
    9,    16,    23,    32,    41,    52,    65,    76,     0,     3,
    3,     4,    11,    12,    19,    20,     3,     4,     5,    12,
   13,    20,    21,     4,     5,     6,    13,    14,    21,    22,
   30,    54,     4,     6,     7,    14,    15,    22,    23,    31,
   55,     5,     7,     8,    15,    16,    23,    24,    26,    48,
   32,    56,     6,     0,     1,     8,     9,    16,    17,    24,
   33,    27,    49,    33,    57,     5,     1,     2,     9,    10,
   17,    18,    25,    34,    28,    50,     5,     2,     3,    10,
   11,    18,    19,    29,    51,    34,    59,
};

vtkDICOMDictionary::Dict Dict107Data = {
"GEMS_HELIOS_01",
8,
35,
Dict107TagHashTable,
Dict107Contents
};

// ----- Kodak Image Information -----

DictEntry Dict108Contents[] = {
{ 0x0029, 0x0015, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0016, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0017, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0018, 0, VR::UT, VM::M1, "" },
{ 0x0029, 0x0019, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x001a, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict108TagHashTable[] = {
    2,     0,     6,     0,    21,     1,    22,     2,    23,     3,
   24,     4,    25,     5,    26,
};

vtkDICOMDictionary::Dict Dict108Data = {
"Kodak Image Information",
1,
6,
Dict108TagHashTable,
Dict108Contents
};

// ----- QUASAR_INTERNAL_USE -----

DictEntry Dict109Contents[] = {
{ 0x0009, 0x0001, 0, VR::UL, VM::M1TN, "RateVector" },
{ 0x0009, 0x0002, 0, VR::UL, VM::M1TN, "CountVector" },
{ 0x0009, 0x0003, 0, VR::UL, VM::M1TN, "TimeVector" },
{ 0x0009, 0x0007, 0, VR::UL, VM::M1TN, "AngleVector" },
{ 0x0009, 0x0008, 0, VR::US, VM::M1, "CameraShape" },
{ 0x0009, 0x0010, 0, VR::US, VM::M1, "WholeBodySpots" },
{ 0x0009, 0x0011, 0, VR::US, VM::M1, "WorklistFlag" },
{ 0x0009, 0x0012, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0013, 0, VR::ST, VM::M1, "SequenceType" },
{ 0x0009, 0x0014, 0, VR::ST, VM::M1, "SequenceName" },
{ 0x0009, 0x0015, 0, VR::UL, VM::M1TN, "AverageRRTimeVector" },
{ 0x0009, 0x0016, 0, VR::UL, VM::M1TN, "LowLimitVector" },
{ 0x0009, 0x0017, 0, VR::UL, VM::M1TN, "HighLimitVector" },
{ 0x0009, 0x0018, 0, VR::UL, VM::M1TN, "BeginIndexVector" },
{ 0x0009, 0x0019, 0, VR::UL, VM::M1TN, "EndIndexVector" },
{ 0x0009, 0x001a, 0, VR::UL, VM::M1TN, "RawTimeVector" },
{ 0x0009, 0x001b, 0, VR::LO, VM::M1, "ImageTypeString" },
{ 0x0009, 0x001d, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x001e, 0, VR::ST, VM::M1, "" },
{ 0x0009, 0x0022, 0, VR::FL, VM::M1, "" },
{ 0x0009, 0x0023, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x0039, 0, VR::UI, VM::M1, "" },
{ 0x0009, 0x0040, 0, VR::DA, VM::M1, "" },
{ 0x0009, 0x0041, 0, VR::TM, VM::M1, "" },
{ 0x0009, 0x0042, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0044, 0, VR::SH, VM::M1, "" },
{ 0x0009, 0x0045, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0048, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x0037, 0x001b, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0030, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0040, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0060, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0070, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0071, 0, VR::FD, VM::M1, "" },
{ 0x0037, 0x0072, 0, VR::SH, VM::M1, "" },
{ 0x0037, 0x0073, 0, VR::FD, VM::M1, "" },
{ 0x0037, 0x0078, 0, VR::FD, VM::M1, "" },
{ 0x0037, 0x0090, 0, VR::IS, VM::M1, "" },
{ 0x0037, 0x0092, 0, VR::DS, VM::M1, "" },
{ 0x0041, 0x0001, 0, VR::UT, VM::M1, "" },
};

unsigned short Dict109TagHashTable[] = {
   11,    20,    29,    36,    43,    54,    61,    70,    81,    96,
    0,     4,     2,     3,    12,    23,    17,    29,    34,   112,
    4,     1,     2,     4,     8,    11,    22,    35,   113,     3,
   20,    35,    22,    64,    32,    80,     3,    18,    30,    19,
   34,    23,    65,     5,     3,     7,     6,    17,    24,    66,
   27,    72,    29,    27,     3,     5,    16,    39,   144,    41,
    1,     4,     8,    19,    14,    25,    25,    68,    33,    96,
    5,     7,    18,    13,    24,    26,    69,    30,    48,    40,
  146,     7,     0,     1,    10,    21,    16,    27,    21,    57,
   31,    64,    36,   114,    38,   120,     4,     9,    20,    15,
   26,    28,    16,    37,   115,
};

vtkDICOMDictionary::Dict Dict109Data = {
"QUASAR_INTERNAL_USE",
10,
42,
Dict109TagHashTable,
Dict109Contents
};

// ----- VEPRO BROKER 1.0 -----

DictEntry Dict110Contents[] = {
{ 0x0057, 0x0010, 0, VR::SQ, VM::M1, "DataReplaceSequence" },
};

unsigned short Dict110TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict110Data = {
"VEPRO BROKER 1.0",
1,
1,
Dict110TagHashTable,
Dict110Contents
};

// ----- SIEMENS CT VA0  COAD -----

DictEntry Dict111Contents[] = {
{ 0x0019, 0x0010, 0, VR::IS, VM::M1, "DistanceSourceToSourceSideCollimator" },
{ 0x0019, 0x0011, 0, VR::IS, VM::M1, "DistanceSourceToDetectorSideCollimator" },
{ 0x0019, 0x0020, 0, VR::IS, VM::M1, "NumberOfPossibleChannels" },
{ 0x0019, 0x0021, 0, VR::IS, VM::M1, "MeanChannelNumber" },
{ 0x0019, 0x0022, 0, VR::DS, VM::M1, "DetectorSpacing" },
{ 0x0019, 0x0023, 0, VR::DS, VM::M1, "DetectorCenter" },
{ 0x0019, 0x0024, 0, VR::DS, VM::M1, "ReadingIntegrationTime" },
{ 0x0019, 0x0050, 0, VR::DS, VM::M1, "DetectorAlignment" },
{ 0x0019, 0x0052, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0054, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::DS, VM::M1, "FocusAlignment" },
{ 0x0019, 0x0065, 0, VR::UL, VM::M1, "FocalSpotDeflectionAmplitude" },
{ 0x0019, 0x0066, 0, VR::UL, VM::M1, "FocalSpotDeflectionPhase" },
{ 0x0019, 0x0067, 0, VR::UL, VM::M1, "FocalSpotDeflectionOffset" },
{ 0x0019, 0x0070, 0, VR::DS, VM::M1, "WaterScalingFactor" },
{ 0x0019, 0x0071, 0, VR::DS, VM::M1, "InterpolationFactor" },
{ 0x0019, 0x0080, 0, VR::CS, VM::M1, "PatientRegion" },
{ 0x0019, 0x0082, 0, VR::CS, VM::M1, "PatientPhaseOfLife" },
{ 0x0019, 0x0090, 0, VR::DS, VM::M1, "OsteoOffset" },
{ 0x0019, 0x0092, 0, VR::DS, VM::M1, "OsteoRegressionLineSlope" },
{ 0x0019, 0x0093, 0, VR::DS, VM::M1, "OsteoRegressionLineIntercept" },
{ 0x0019, 0x0094, 0, VR::IS, VM::M1, "OsteoStandardizationCode" },
{ 0x0019, 0x0096, 0, VR::IS, VM::M1, "OsteoPhantomNumber" },
{ 0x0019, 0x00a0, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a1, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a2, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00a3, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00a4, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a5, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a6, 0, VR::UL, VM::M1TN, "" },
{ 0x0019, 0x00a7, 0, VR::UL, VM::M1TN, "" },
{ 0x0019, 0x00a8, 0, VR::UL, VM::M1TN, "" },
{ 0x0019, 0x00a9, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00aa, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00ab, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00ac, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00ad, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00ae, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00af, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00b0, 0, VR::DS, VM::M1, "FeedPerRotation" },
{ 0x0019, 0x00bd, 0, VR::IS, VM::M1, "PulmoTriggerLevel" },
{ 0x0019, 0x00be, 0, VR::DS, VM::M1, "ExpiratoricReserveVolume" },
{ 0x0019, 0x00bf, 0, VR::DS, VM::M1, "VitalCapacity" },
{ 0x0019, 0x00c0, 0, VR::DS, VM::M1, "PulmoWater" },
{ 0x0019, 0x00c1, 0, VR::DS, VM::M1, "PulmoAir" },
{ 0x0019, 0x00c2, 0, VR::DA, VM::M1, "PulmoDate" },
{ 0x0019, 0x00c3, 0, VR::TM, VM::M1, "PulmoTime" },
{ 0x0019, 0x00c4, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c5, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict111TagHashTable[] = {
   13,    22,    29,    36,    43,    50,    57,    64,    73,    86,
  103,   112,     0,     4,     7,    80,    10,    96,    38,   175,
   45,   194,     3,     6,    36,    37,   174,    46,   195,     3,
    8,    82,    36,   173,    43,   192,     3,    35,   172,    39,
  176,    44,   193,     3,     9,    84,    20,   147,    26,   163,
    3,    11,   101,    19,   146,    25,   162,     3,    12,   102,
   24,   161,    47,   196,     4,    13,   103,    18,   144,    23,
  160,    48,   197,     6,     1,    17,     3,    33,    14,   112,
   30,   167,    34,   171,    42,   191,     8,     0,    16,     2,
   32,    15,   113,    17,   130,    22,   150,    29,   166,    33,
  170,    41,   190,     4,     5,    35,    28,   165,    32,   169,
   40,   189,     5,     4,    34,    16,   128,    21,   148,    27,
  164,    31,   168,
};

vtkDICOMDictionary::Dict Dict111Data = {
"SIEMENS CT VA0  COAD",
12,
49,
Dict111TagHashTable,
Dict111Contents
};

// ----- PHILIPS MR -----

DictEntry Dict112Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "SPIRelease" },
{ 0x0009, 0x0012, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict112TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    18,
};

vtkDICOMDictionary::Dict Dict112Data = {
"PHILIPS MR",
1,
2,
Dict112TagHashTable,
Dict112Contents
};

// ----- MeVis BreastCare -----

DictEntry Dict113Contents[] = {
{ 0x0019, 0x0001, 0, VR::LO, VM::M1, "AnnotationVersion" },
{ 0x0071, 0x0001, 0, VR::LO, VM::M1, "XMLFormattedTextValue" },
};

unsigned short Dict113TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     1,
};

vtkDICOMDictionary::Dict Dict113Data = {
"MeVis BreastCare",
1,
2,
Dict113TagHashTable,
Dict113Contents
};

// ----- VEPRO VIF 3.0 DATA -----

DictEntry Dict114Contents[] = {
{ 0x0055, 0x0020, 0, VR::OB, VM::M1, "" },
{ 0x0055, 0x0030, 0, VR::OB, VM::M1, "IconData" },
{ 0x0055, 0x0065, 0, VR::OB, VM::M1, "ImageHashValue" },
};

unsigned short Dict114TagHashTable[] = {
    2,     0,     3,     0,    32,     1,    48,     2,   101,
};

vtkDICOMDictionary::Dict Dict114Data = {
"VEPRO VIF 3.0 DATA",
1,
3,
Dict114TagHashTable,
Dict114Contents
};

// ----- MeVis eatDicom -----

DictEntry Dict115Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "eatDicomVersion" },
{ 0x0009, 0x0011, 0, VR::ST, VM::M1, "eatDicomOptions" },
};

unsigned short Dict115TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    17,
};

vtkDICOMDictionary::Dict Dict115Data = {
"MeVis eatDicom",
1,
2,
Dict115TagHashTable,
Dict115Contents
};

// ----- DIGISCAN IMAGE -----

DictEntry Dict116Contents[] = {
{ 0x0029, 0x0031, 0, VR::US, VM::M1TN, "" },
{ 0x0029, 0x0032, 0, VR::US, VM::M1TN, "" },
{ 0x0029, 0x0033, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0034, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict116TagHashTable[] = {
    2,     0,     4,     0,    49,     1,    50,     2,    51,     3,
   52,
};

vtkDICOMDictionary::Dict Dict116Data = {
"DIGISCAN IMAGE",
1,
4,
Dict116TagHashTable,
Dict116Contents
};

// ----- MITRA OBJECT UTF8 ATTRIBUTES 1.0 -----

DictEntry Dict117Contents[] = {
{ 0x0033, 0x0002, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0004, 0, VR::CS, VM::M1, "" },
{ 0x0033, 0x0006, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0008, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x000a, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x000c, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x000e, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0013, 0, VR::PN, VM::M1, "" },
{ 0x0033, 0x0014, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0015, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0016, 0, VR::PN, VM::M1, "" },
{ 0x0033, 0x0019, 0, VR::PN, VM::M1, "" },
};

unsigned short Dict117TagHashTable[] = {
    4,    13,    22,     0,     4,     4,    10,     5,    12,     8,
   20,    11,    25,     4,     0,     2,     1,     4,     6,    14,
   10,    22,     4,     2,     6,     3,     8,     7,    19,     9,
   21,
};

vtkDICOMDictionary::Dict Dict117Data = {
"MITRA OBJECT UTF8 ATTRIBUTES 1.0",
3,
12,
Dict117TagHashTable,
Dict117Contents
};

// ----- SIEMENS MED PT WAVEFORM -----

DictEntry Dict118Contents[] = {
{ 0x0071, 0x0046, 0, VR::UN, VM::M1, "StartingRespiratoryAmplitude" },
{ 0x0071, 0x0047, 0, VR::UN, VM::M1, "StartingRespiratoryPhase" },
{ 0x0071, 0x0048, 0, VR::UN, VM::M1, "EndingRespiratoryAmplitude" },
{ 0x0071, 0x0049, 0, VR::UN, VM::M1, "EndingRespiratoryPhase" },
{ 0x0071, 0x0050, 0, VR::CS, VM::M1, "RespiratoryTriggerType" },
};

unsigned short Dict118TagHashTable[] = {
    2,     0,     5,     0,    70,     1,    71,     2,    72,     3,
   73,     4,    80,
};

vtkDICOMDictionary::Dict Dict118Data = {
"SIEMENS MED PT WAVEFORM",
1,
5,
Dict118TagHashTable,
Dict118Contents
};

// ----- VEPRO BROKER 1.0 DATA REPLACE -----

DictEntry Dict119Contents[] = {
{ 0x0057, 0x0020, 0, VR::SQ, VM::M1, "OriginalDataSequence" },
{ 0x0057, 0x0030, 0, VR::SQ, VM::M1, "ReplacedDataSequence" },
{ 0x0057, 0x0040, 0, VR::DA, VM::M1, "DateOfDataReplacement" },
{ 0x0057, 0x0041, 0, VR::TM, VM::M1, "TimeOfDataReplacement" },
{ 0x0057, 0x0042, 0, VR::LO, VM::M1, "DicomReceiveNode" },
{ 0x0057, 0x0043, 0, VR::LO, VM::M1, "ApplicationName" },
{ 0x0057, 0x0044, 0, VR::LO, VM::M1, "ComputerName" },
};

unsigned short Dict119TagHashTable[] = {
    2,     0,     7,     0,    32,     1,    48,     2,    64,     3,
   65,     4,    66,     5,    67,     6,    68,
};

vtkDICOMDictionary::Dict Dict119Data = {
"VEPRO BROKER 1.0 DATA REPLACE",
1,
7,
Dict119TagHashTable,
Dict119Contents
};

// ----- PHILIPS-MR-1 -----

DictEntry Dict120Contents[] = {
{ 0x0019, 0x0011, 0, VR::IS, VM::M1, "ChemicalShiftNumber" },
{ 0x0019, 0x0012, 0, VR::IS, VM::M1, "PhaseNumber" },
{ 0x0021, 0x0001, 0, VR::IS, VM::M1, "ReconstructionNumber" },
{ 0x0021, 0x0002, 0, VR::IS, VM::M1, "SliceNumber" },
};

unsigned short Dict120TagHashTable[] = {
    2,     0,     4,     0,    17,     1,    18,     2,     1,     3,
    2,
};

vtkDICOMDictionary::Dict Dict120Data = {
"PHILIPS-MR-1",
1,
4,
Dict120TagHashTable,
Dict120Contents
};

// ----- MERGE TECHNOLOGIES, INC. -----

DictEntry Dict121Contents[] = {
{ 0x0009, 0x0000, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict121TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict121Data = {
"MERGE TECHNOLOGIES, INC.",
1,
1,
Dict121TagHashTable,
Dict121Contents
};

// ----- SIEMENS DLR.01 -----

DictEntry Dict122Contents[] = {
{ 0x0019, 0x0010, 0, VR::LO, VM::M1, "MeasurementMode" },
{ 0x0019, 0x0011, 0, VR::LO, VM::M1, "ImageType" },
{ 0x0019, 0x0015, 0, VR::LO, VM::M1, "SoftwareVersion" },
{ 0x0019, 0x0020, 0, VR::LO, VM::M1, "MPMCode" },
{ 0x0019, 0x0021, 0, VR::LO, VM::M1, "Latitude" },
{ 0x0019, 0x0022, 0, VR::LO, VM::M1, "Sensitivity" },
{ 0x0019, 0x0023, 0, VR::LO, VM::M1, "EDR" },
{ 0x0019, 0x0024, 0, VR::LO, VM::M1, "LFix" },
{ 0x0019, 0x0025, 0, VR::LO, VM::M1, "SFix" },
{ 0x0019, 0x0026, 0, VR::LO, VM::M1, "PresetMode" },
{ 0x0019, 0x0027, 0, VR::LO, VM::M1, "Region" },
{ 0x0019, 0x0028, 0, VR::LO, VM::M1, "Subregion" },
{ 0x0019, 0x0030, 0, VR::LO, VM::M1, "Orientation" },
{ 0x0019, 0x0031, 0, VR::LO, VM::M1, "MarkOnFilm" },
{ 0x0019, 0x0032, 0, VR::LO, VM::M1, "RotationOnDRC" },
{ 0x0019, 0x0040, 0, VR::LO, VM::M1, "ReaderType" },
{ 0x0019, 0x0041, 0, VR::LO, VM::M1, "SubModality" },
{ 0x0019, 0x0042, 0, VR::LO, VM::M1, "ReaderSerialNumber" },
{ 0x0019, 0x0050, 0, VR::LO, VM::M1, "CassetteScale" },
{ 0x0019, 0x0051, 0, VR::LO, VM::M1, "CassetteMatrix" },
{ 0x0019, 0x0052, 0, VR::LO, VM::M1, "CassetteSubmatrix" },
{ 0x0019, 0x0053, 0, VR::LO, VM::M1, "Barcode" },
{ 0x0019, 0x0060, 0, VR::LO, VM::M1, "ContrastType" },
{ 0x0019, 0x0061, 0, VR::LO, VM::M1, "RotationAmount" },
{ 0x0019, 0x0062, 0, VR::LO, VM::M1, "RotationCenter" },
{ 0x0019, 0x0063, 0, VR::LO, VM::M1, "DensityShift" },
{ 0x0019, 0x0064, 0, VR::US, VM::M1, "FrequencyRank" },
{ 0x0019, 0x0065, 0, VR::LO, VM::M1, "FrequencyEnhancement" },
{ 0x0019, 0x0066, 0, VR::LO, VM::M1, "FrequencyType" },
{ 0x0019, 0x0067, 0, VR::LO, VM::M1, "KernelLength" },
{ 0x0019, 0x0068, 0, VR::UL, VM::M1, "KernelMode" },
{ 0x0019, 0x0069, 0, VR::UL, VM::M1, "ConvolutionMode" },
{ 0x0019, 0x0070, 0, VR::LO, VM::M1, "PLASource" },
{ 0x0019, 0x0071, 0, VR::LO, VM::M1, "PLADestination" },
{ 0x0019, 0x0075, 0, VR::LO, VM::M1, "UIDOriginalImage" },
{ 0x0019, 0x0076, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::LT, VM::M1, "ReaderHeader" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "PLAOfSecondaryDestination" },
{ 0x0019, 0x00a0, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a1, 0, VR::DS, VM::M1, "" },
{ 0x0041, 0x0010, 0, VR::US, VM::M1, "NumberOfHardcopies" },
{ 0x0041, 0x0020, 0, VR::LO, VM::M1, "FilmFormat" },
{ 0x0041, 0x0030, 0, VR::LO, VM::M1, "FilmSize" },
{ 0x0041, 0x0031, 0, VR::LO, VM::M1, "FullFilmFormat" },
};

unsigned short Dict122TagHashTable[] = {
   12,    21,    32,    43,    54,    59,    68,    77,    86,    97,
  102,     0,     4,    15,    64,    23,    97,    35,   118,    38,
  160,     5,     2,    21,     4,    33,    16,    65,    24,    98,
   36,   128,     5,     3,    32,    17,    66,    25,    99,    30,
  104,    42,    48,     5,     6,    35,    26,   100,    31,   105,
   40,    16,    43,    49,     2,     5,    34,    27,   101,     4,
    8,    37,    11,    40,    28,   102,    32,   112,     4,     7,
   36,    18,    80,    29,   103,    33,   113,     4,    10,    39,
   13,    49,    19,    81,    37,   144,     5,     1,    17,     9,
   38,    12,    48,    20,    82,    41,    32,     2,     0,    16,
   21,    83,     4,    14,    50,    22,    96,    34,   117,    39,
  161,
};

vtkDICOMDictionary::Dict Dict122Data = {
"SIEMENS DLR.01",
11,
44,
Dict122TagHashTable,
Dict122Contents
};

// ----- Agfa ADC NX -----

DictEntry Dict123Contents[] = {
{ 0x0019, 0x0009, 0, VR::SQ, VM::M1, "" },
{ 0x0019, 0x00f0, 0, VR::LO, VM::M1, "UserDefinedField1" },
{ 0x0019, 0x00f1, 0, VR::LO, VM::M1, "UserDefinedField2" },
{ 0x0019, 0x00f2, 0, VR::LO, VM::M1, "UserDefinedField3" },
{ 0x0019, 0x00f3, 0, VR::LO, VM::M1, "UserDefinedField4" },
{ 0x0019, 0x00f4, 0, VR::LO, VM::M1, "UserDefinedField5" },
{ 0x0019, 0x00f5, 0, VR::CS, VM::M1, "CassetteOrientation" },
{ 0x0019, 0x00f6, 0, VR::DS, VM::M1, "PlateSensitivity" },
{ 0x0019, 0x00f7, 0, VR::DS, VM::M1, "PlateErasability" },
{ 0x0019, 0x00f8, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00fa, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00fc, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00fd, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00fe, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict123TagHashTable[] = {
    4,    13,    24,     0,     4,     1,   240,     8,   247,    12,
  253,    13,   254,     5,     0,     9,     2,   241,     3,   242,
    5,   244,     9,   248,     5,     4,   243,     6,   245,     7,
  246,    10,   250,    11,   252,
};

vtkDICOMDictionary::Dict Dict123Data = {
"Agfa ADC NX",
3,
14,
Dict123TagHashTable,
Dict123Contents
};

// ----- Imaging Dynamics Company Ltd. -----

DictEntry Dict124Contents[] = {
{ 0x4321, 0x0042, 0, VR::US, VM::M1, "" },
{ 0x4321, 0x0064, 0, VR::LO, VM::M1, "PODMode" },
};

unsigned short Dict124TagHashTable[] = {
    2,     0,     2,     0,    66,     1,   100,
};

vtkDICOMDictionary::Dict Dict124Data = {
"Imaging Dynamics Company Ltd.",
1,
2,
Dict124TagHashTable,
Dict124Contents
};

// ----- SIEMENS DFR.01 ORIGINAL -----

DictEntry Dict125Contents[] = {
{ 0x0017, 0x0011, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0012, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0014, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0015, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0016, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0018, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0021, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0022, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0023, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0024, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0025, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0026, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0027, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x002a, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0030, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0031, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0033, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0037, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0038, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0041, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0043, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0045, 0, VR::DS, VM::M1, "" },
{ 0x0017, 0x0046, 0, VR::DS, VM::M1, "" },
{ 0x0017, 0x0047, 0, VR::SH, VM::M1, "" },
{ 0x0017, 0x0048, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0049, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x004a, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0051, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0052, 0, VR::UL, VM::M1, "" },
{ 0x0017, 0x0061, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0062, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0071, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0072, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0073, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0074, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0079, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x007a, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x007b, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x00a0, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x00c1, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x00c2, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict125TagHashTable[] = {
   11,    18,    35,    46,    57,    64,    73,    80,    87,    98,
    0,     3,    10,    37,    24,    70,    34,   114,     8,     4,
   22,     9,    36,    13,    42,    25,    71,    29,    81,    35,
  115,    37,   121,    40,   160,     5,     3,    21,     8,    35,
   18,    55,    22,    68,    28,    74,     5,     2,    20,     7,
   34,    23,    69,    33,   113,    41,   193,     3,     6,    33,
   26,    72,    42,   194,     4,     1,    18,     5,    24,    21,
   67,    27,    73,     3,     0,    17,    17,    51,    32,    98,
    3,    16,    50,    19,    56,    20,    65,     5,    12,    39,
   15,    49,    30,    82,    36,   116,    38,   122,     4,    11,
   38,    14,    48,    31,    97,    39,   123,
};

vtkDICOMDictionary::Dict Dict125Data = {
"SIEMENS DFR.01 ORIGINAL",
10,
43,
Dict125TagHashTable,
Dict125Contents
};

// ----- NQHeader -----

DictEntry Dict126Contents[] = {
{ 0x0099, 0x0001, 0, VR::UI, VM::M1, "Version" },
{ 0x0099, 0x0002, 0, VR::UI, VM::M1, "AnalyzedSeriesUID" },
{ 0x0099, 0x0003, 0, VR::LT, VM::M1, "License" },
{ 0x0099, 0x0004, 0, VR::SS, VM::M1, "ReturnCode" },
{ 0x0099, 0x0005, 0, VR::LT, VM::M1, "ReturnMessage" },
{ 0x0099, 0x0010, 0, VR::FL, VM::M1, "MI" },
{ 0x0099, 0x0020, 0, VR::SH, VM::M1, "Units" },
{ 0x0099, 0x0021, 0, VR::FL, VM::M1, "ICV" },
};

unsigned short Dict126TagHashTable[] = {
    3,    12,     0,     4,     0,     1,     2,     3,     4,     5,
    7,    33,     4,     1,     2,     3,     4,     5,    16,     6,
   32,
};

vtkDICOMDictionary::Dict Dict126Data = {
"NQHeader",
2,
8,
Dict126TagHashTable,
Dict126Contents
};

// ----- SIEMENS CT APPL PRESENTATION -----

DictEntry Dict127Contents[] = {
{ 0x0029, 0x0000, 0, VR::US, VM::M1, "TranslucentMode" },
{ 0x0029, 0x0001, 0, VR::FD, VM::M1, "TranslucentWindowSize" },
{ 0x0029, 0x0002, 0, VR::US, VM::M1, "PanoramicMode" },
{ 0x0029, 0x0003, 0, VR::FD, VM::M1, "PanoramicInnerWidth" },
{ 0x0029, 0x0004, 0, VR::US, VM::M1, "DisplayUnseenAreas" },
{ 0x0029, 0x0005, 0, VR::US, VM::M4, "UnseenAreasColor" },
{ 0x0029, 0x0006, 0, VR::US, VM::M1, "DisplayTaggedData" },
{ 0x0029, 0x0007, 0, VR::US, VM::M4, "TaggedColor" },
{ 0x0029, 0x0008, 0, VR::UL, VM::M1, "TaggedSampleThickness" },
{ 0x0029, 0x0009, 0, VR::SL, VM::M1, "TaggedThreshold" },
{ 0x0029, 0x0010, 0, VR::US, VM::M1, "KernelFilter" },
};

unsigned short Dict127TagHashTable[] = {
    3,    14,     0,     5,     1,     1,     3,     3,     5,     5,
    7,     7,     9,     9,     6,     0,     0,     2,     2,     4,
    4,     6,     6,     8,     8,    10,    16,
};

vtkDICOMDictionary::Dict Dict127Data = {
"SIEMENS CT APPL PRESENTATION",
2,
11,
Dict127TagHashTable,
Dict127Contents
};

// ----- SIEMENS SYNGO PRINT SERVICE -----

DictEntry Dict128Contents[] = {
{ 0x0029, 0x0010, 0, VR::IS, VM::M1, "SheetNumber" },
};

unsigned short Dict128TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict128Data = {
"SIEMENS SYNGO PRINT SERVICE",
1,
1,
Dict128TagHashTable,
Dict128Contents
};

// ----- Siemens: Thorax/Multix FD Raw Image Settings -----

DictEntry Dict129Contents[] = {
{ 0x0025, 0x0000, 0, VR::SS, VM::M1, "RawImageAmplification" },
{ 0x0025, 0x0001, 0, VR::SS, VM::M1, "GammaLUT" },
{ 0x0025, 0x0002, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0003, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x0004, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x0005, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x0006, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x0007, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x0008, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x0009, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x000C, 0, VR::SS, VM::M1, "HarmonizationKernel" },
{ 0x0025, 0x000D, 0, VR::FL, VM::M1, "HarmonizationGain" },
{ 0x0025, 0x000E, 0, VR::SS, VM::M1, "EdgeEnhancementKernel" },
{ 0x0025, 0x000F, 0, VR::FL, VM::M1, "EdgeEnhancementGain" },
{ 0x0025, 0x000a, 0, VR::FL, VM::M1, "" },
{ 0x0025, 0x000b, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0010, 0, VR::LT, VM::M1, "InternalValue" },
{ 0x0025, 0x0011, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0012, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0013, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0014, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0015, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0016, 0, VR::SS, VM::M1, "" },
{ 0x0025, 0x0017, 0, VR::LO, VM::M1, "" },
{ 0x0025, 0x0018, 0, VR::US, VM::M1, "AutoGain" },
{ 0x0025, 0x0019, 0, VR::US, VM::M1, "OrthoSubsampling" },
{ 0x0025, 0x001A, 0, VR::US, VM::M2, "ImageCropUpperLeft" },
{ 0x0025, 0x001B, 0, VR::US, VM::M2, "ImageCropUpperRight" },
{ 0x0025, 0x001C, 0, VR::US, VM::M2, "ImageCropLowerLeft" },
{ 0x0025, 0x001D, 0, VR::US, VM::M2, "ImageCropLowerRight" },
{ 0x0025, 0x0030, 0, VR::US, VM::M1, "ManualCropping" },
{ 0x0025, 0x0031, 0, VR::SS, VM::M1, "GammaLUTParameter1" },
{ 0x0025, 0x0032, 0, VR::DS, VM::M1, "GammaLUTParameter2" },
{ 0x0025, 0x0033, 0, VR::SS, VM::M1, "GammaLUTParameter3" },
{ 0x0025, 0x0034, 0, VR::SS, VM::M1, "GammaLUTParameter4" },
{ 0x0025, 0x0035, 0, VR::LO, VM::M1, "GammaLUTName" },
{ 0x0025, 0x0036, 0, VR::DS, VM::M1, "" },
{ 0x0025, 0x0037, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict129TagHashTable[] = {
   10,    21,    30,    39,    48,    55,    64,    73,    84,     0,
    5,     1,     1,     8,     8,    19,    19,    26,    26,    37,
   55,     4,     0,     0,    15,    11,    18,    18,    36,    54,
    4,     3,     3,    14,    10,    29,    29,    31,    49,     4,
    2,     2,    21,    21,    28,    28,    30,    48,     3,    11,
   13,    20,    20,    33,    51,     4,     5,     5,    10,    12,
   23,    23,    32,    50,     4,     4,     4,    13,    15,    22,
   22,    25,    25,     5,     7,     7,    12,    14,    17,    17,
   24,    24,    35,    53,     5,     6,     6,     9,     9,    16,
   16,    27,    27,    34,    52,
};

vtkDICOMDictionary::Dict Dict129Data = {
"Siemens: Thorax/Multix FD Raw Image Settings",
9,
38,
Dict129TagHashTable,
Dict129Contents
};

// ----- SIEMENS CT VA0  ORI -----

DictEntry Dict130Contents[] = {
{ 0x0009, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0030, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict130TagHashTable[] = {
    2,     0,     2,     0,    32,     1,    48,
};

vtkDICOMDictionary::Dict Dict130Data = {
"SIEMENS CT VA0  ORI",
1,
2,
Dict130TagHashTable,
Dict130Contents
};

// ----- Philips X-ray Imaging DD 001 -----

DictEntry Dict131Contents[] = {
{ 0x2003, 0x0000, 0, VR::CS, VM::M1, "" },
{ 0x2003, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x2003, 0x0002, 0, VR::FD, VM::M3, "" },
{ 0x2003, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x2003, 0x0006, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0009, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x2003, 0x0011, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0012, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0013, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0014, 0, VR::FD, VM::M1, "" },
{ 0x2003, 0x0015, 0, VR::FD, VM::M1, "" },
{ 0x2003, 0x0016, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0017, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0018, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0019, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0022, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0024, 0, VR::FD, VM::M4, "" },
{ 0x2003, 0x0025, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0026, 0, VR::SL, VM::M1, "" },
{ 0x2003, 0x0027, 0, VR::SH, VM::M1, "" },
{ 0x2003, 0x0028, 0, VR::SH, VM::M1, "" },
{ 0x2003, 0x0029, 0, VR::FD, VM::M1, "" },
{ 0x2003, 0x002a, 0, VR::LO, VM::M1, "" },
{ 0x2003, 0x002b, 0, VR::FD, VM::M1, "" },
{ 0x2003, 0x002c, 0, VR::SH, VM::M1, "" },
{ 0x2003, 0x002d, 0, VR::SL, VM::M1TN, "" },
{ 0x2003, 0x002e, 0, VR::SQ, VM::M1, "" },
{ 0x2003, 0x0030, 0, VR::CS, VM::M1, "" },
{ 0x2003, 0x0031, 0, VR::CS, VM::M1, "" },
{ 0x2003, 0x0032, 0, VR::UI, VM::M1, "" },
};

unsigned short Dict131TagHashTable[] = {
    8,    19,    26,    39,    46,    55,    66,     0,     5,     0,
    0,     5,     9,     8,    18,    18,    37,    27,    46,     3,
    7,    17,    17,    36,    26,    45,     6,     4,     6,     6,
   16,    15,    25,    16,    34,    24,    43,    25,    44,     3,
   13,    23,    14,    24,    23,    42,     4,     3,     3,    12,
   22,    22,    41,    30,    50,     5,     2,     2,    11,    21,
   20,    39,    21,    40,    29,    49,     5,     1,     1,     9,
   19,    10,    20,    19,    38,    28,    48,
};

vtkDICOMDictionary::Dict Dict131Data = {
"Philips X-ray Imaging DD 001",
7,
31,
Dict131TagHashTable,
Dict131Contents
};

// ----- SIEMENS SMS-AX  VIEW 1.0 -----

DictEntry Dict132Contents[] = {
{ 0x0019, 0x0000, 0, VR::US, VM::M1, "ReviewMode" },
{ 0x0019, 0x0001, 0, VR::US, VM::M1, "AnatomicalBackgroundPercent" },
{ 0x0019, 0x0002, 0, VR::US, VM::M1, "NumberOfPhases" },
{ 0x0019, 0x0003, 0, VR::US, VM::M1, "ApplyAnatomicalBackground" },
{ 0x0019, 0x0004, 0, VR::SS, VM::M4T4N, "PixelShiftArray" },
{ 0x0019, 0x0005, 0, VR::US, VM::M1, "Brightness" },
{ 0x0019, 0x0006, 0, VR::US, VM::M1, "Contrast" },
{ 0x0019, 0x0007, 0, VR::US, VM::M1, "EnabledShutters" },
{ 0x0019, 0x0008, 0, VR::US, VM::M1, "NativeEdgeEnhancementPercentGain" },
{ 0x0019, 0x0009, 0, VR::SS, VM::M1, "NativeEdgeEnhancementLUTIndex" },
{ 0x0019, 0x000A, 0, VR::SS, VM::M1, "NativeEdgeEnhancementKernelSize" },
{ 0x0019, 0x000B, 0, VR::US, VM::M1, "SubtractedEdgeEnhancementPercentGain" },
{ 0x0019, 0x000C, 0, VR::SS, VM::M1, "SubtractedEdgeEnhancementLUTIndex" },
{ 0x0019, 0x000D, 0, VR::SS, VM::M1, "SubtractedEdgeEnhancementKernelSize" },
{ 0x0019, 0x000E, 0, VR::US, VM::M1, "FadePercent" },
{ 0x0019, 0x000F, 0, VR::US, VM::M1, "FlippedBeforeLateralityApplied" },
{ 0x0019, 0x0010, 0, VR::US, VM::M1, "ApplyFade" },
{ 0x0019, 0x0011, 0, VR::US, VM::M1, "ReferenceImagesTakenFlag" },
{ 0x0019, 0x0012, 0, VR::US, VM::M1, "Zoom" },
{ 0x0019, 0x0013, 0, VR::SS, VM::M1, "PanX" },
{ 0x0019, 0x0014, 0, VR::SS, VM::M1, "PanY" },
{ 0x0019, 0x0015, 0, VR::SS, VM::M1, "NativeEdgeEnhancementAdvPercentGain" },
{ 0x0019, 0x0016, 0, VR::SS, VM::M1, "SubtractedEdgeEnhancementAdvPercentGain" },
{ 0x0019, 0x0017, 0, VR::US, VM::M1, "InvertFlag" },
{ 0x0019, 0x001A, 0, VR::OB, VM::M1, "Quant1KOverlay" },
{ 0x0019, 0x001B, 0, VR::US, VM::M1, "OriginalResolution" },
{ 0x0019, 0x001C, 0, VR::DS, VM::M1, "AutoWindowCenter" },
{ 0x0019, 0x001D, 0, VR::DS, VM::M1, "AutoWindowWidth" },
{ 0x0019, 0x001E, 0, VR::IS, VM::M2, "AutoWindowCorrectValue" },
{ 0x0019, 0x001F, 0, VR::DS, VM::M1, "SigmoidWindowParameter" },
{ 0x0019, 0x0041, 0, VR::SL, VM::M2, "DispayedAreaTopLeftHandCorner" },
{ 0x0019, 0x0042, 0, VR::SL, VM::M2, "DispayedAreaBottomRightHandCorner" },
};

unsigned short Dict132TagHashTable[] = {
    9,    16,    25,    36,    45,    54,    63,    72,     0,     3,
    1,     1,     9,     9,    17,    17,     4,     0,     0,     8,
    8,    16,    16,    30,    65,     5,     3,     3,    11,    11,
   19,    19,    25,    27,    31,    66,     4,     2,     2,    10,
   10,    18,    18,    24,    26,     4,     5,     5,    13,    13,
   21,    21,    27,    29,     4,     4,     4,    12,    12,    20,
   20,    26,    28,     4,     7,     7,    15,    15,    23,    23,
   29,    31,     4,     6,     6,    14,    14,    22,    22,    28,
   30,
};

vtkDICOMDictionary::Dict Dict132Data = {
"SIEMENS SMS-AX  VIEW 1.0",
8,
32,
Dict132TagHashTable,
Dict132Contents
};

// ----- SPI-P-Private_CDS Release 1 -----

DictEntry Dict133Contents[] = {
{ 0x0021, 0x0040, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0000, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict133TagHashTable[] = {
    2,     0,     3,     0,    64,     1,     0,     2,    16,
};

vtkDICOMDictionary::Dict Dict133Data = {
"SPI-P-Private_CDS Release 1",
1,
3,
Dict133TagHashTable,
Dict133Contents
};

// ----- astm.org/diconde/iod/NdeCtImage -----

DictEntry Dict134Contents[] = {
{ 0x0009, 0x0002, 0, VR::IS, VM::M1, "LINACEnergy" },
{ 0x0009, 0x0004, 0, VR::IS, VM::M1, "LINACOutput" },
};

unsigned short Dict134TagHashTable[] = {
    2,     0,     2,     0,     2,     1,     4,
};

vtkDICOMDictionary::Dict Dict134Data = {
"astm.org/diconde/iod/NdeCtImage",
1,
2,
Dict134TagHashTable,
Dict134Contents
};

// ----- SIEMENS SYNGO TIME POINT SERVICE -----

DictEntry Dict135Contents[] = {
{ 0x0029, 0x0001, 0, VR::LO, VM::M1, "TimePointID" },
{ 0x0029, 0x0002, 0, VR::LO, VM::M1, "TimePointInformation" },
{ 0x0029, 0x0050, 0, VR::SQ, VM::M1, "StudiesinTimePointSequence" },
};

unsigned short Dict135TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,    80,
};

vtkDICOMDictionary::Dict Dict135Data = {
"SIEMENS SYNGO TIME POINT SERVICE",
1,
3,
Dict135TagHashTable,
Dict135Contents
};

// ----- Silhouette Line V1.0 -----

DictEntry Dict136Contents[] = {
{ 0x0029, 0x0011, 0, VR::IS, VM::M1, "LineName" },
{ 0x0029, 0x0012, 0, VR::LT, VM::M1, "LineNameFont" },
{ 0x0029, 0x0013, 0, VR::UL, VM::M1, "LineNameDisplay" },
{ 0x0029, 0x0014, 0, VR::LT, VM::M1, "LineNormalColor" },
{ 0x0029, 0x0015, 0, VR::UL, VM::M1, "LineType" },
{ 0x0029, 0x0016, 0, VR::UL, VM::M1, "LineThickness" },
{ 0x0029, 0x0017, 0, VR::UL, VM::M1, "LineStyle" },
{ 0x0029, 0x0018, 0, VR::UL, VM::M1, "LineDashLength" },
{ 0x0029, 0x0019, 0, VR::UL, VM::M1, "LineInteractivity" },
{ 0x0029, 0x0020, 0, VR::LT, VM::M1, "LineMeasurementColor" },
{ 0x0029, 0x0021, 0, VR::LT, VM::M1, "LineMeasurementFont" },
{ 0x0029, 0x0022, 0, VR::UL, VM::M1, "LineMeasurementDashLength" },
{ 0x0029, 0x0023, 0, VR::UL, VM::M1, "LinePointSpace" },
{ 0x0029, 0x0024, 0, VR::FD, VM::M1, "LinePoints" },
{ 0x0029, 0x0025, 0, VR::UL, VM::M1, "LineControlPointSize" },
{ 0x0029, 0x0026, 0, VR::UL, VM::M1, "LineControlPointSpace" },
{ 0x0029, 0x0027, 0, VR::FD, VM::M1, "LineControlPoints" },
{ 0x0029, 0x0028, 0, VR::LT, VM::M1, "LineLabel" },
{ 0x0029, 0x0029, 0, VR::UL, VM::M1, "LineDontSave" },
};

unsigned short Dict136TagHashTable[] = {
    5,    18,    29,    38,     0,     6,     0,    17,     4,    21,
    8,    25,    10,    33,    14,    37,    18,    41,     5,     3,
   20,     7,    24,     9,    32,    13,    36,    17,    40,     4,
    2,    19,     6,    23,    12,    35,    16,    39,     4,     1,
   18,     5,    22,    11,    34,    15,    38,
};

vtkDICOMDictionary::Dict Dict136Data = {
"Silhouette Line V1.0",
4,
19,
Dict136TagHashTable,
Dict136Contents
};

// ----- BrainLAB_BeamProfile -----

DictEntry Dict137Contents[] = {
{ 0x3411, 0x0001, 0, VR::SQ, VM::M1, "BeamProfileSequence" },
{ 0x3411, 0x0002, 0, VR::IS, VM::M1, "BeamProfileNumber" },
{ 0x3411, 0x0003, 0, VR::SQ, VM::M1, "BeamParameterSequence" },
{ 0x3411, 0x0004, 0, VR::UT, VM::M1, "ParameterDescription" },
{ 0x3411, 0x0005, 0, VR::OB, VM::M1, "ParameterData" },
{ 0x3411, 0x0006, 0, VR::IS, VM::M1, "ReferencedBeamProfileNumber" },
};

unsigned short Dict137TagHashTable[] = {
    2,     0,     6,     0,     1,     1,     2,     2,     3,     3,
    4,     4,     5,     5,     6,
};

vtkDICOMDictionary::Dict Dict137Data = {
"BrainLAB_BeamProfile",
1,
6,
Dict137TagHashTable,
Dict137Contents
};

// ----- astm.org/diconde/iod/NdeDxCalibrationData -----

DictEntry Dict138Contents[] = {
{ 0x0009, 0x0040, 0, VR::SQ, VM::M1, "DarkCurrentSequence" },
{ 0x0009, 0x0050, 0, VR::OW, VM::M1, "DarkCurrentCounts" },
{ 0x0009, 0x0060, 0, VR::SQ, VM::M1, "GainCorrectionReferenceSequence" },
{ 0x0009, 0x0070, 0, VR::OW, VM::M1, "AirCounts" },
{ 0x0009, 0x0071, 0, VR::DS, VM::M1, "KVUsedInGainCalibration" },
{ 0x0009, 0x0072, 0, VR::DS, VM::M1, "MAUsedInGainCalibration" },
{ 0x0009, 0x0073, 0, VR::DS, VM::M1, "NumberOfFramesUsedForIntegration" },
{ 0x0009, 0x0074, 0, VR::LO, VM::M1, "FilterMaterialUsedInGainCalibration" },
{ 0x0009, 0x0075, 0, VR::DS, VM::M1, "FilterThicknessUsedInGainCalibration" },
{ 0x0009, 0x0076, 0, VR::DA, VM::M1, "DateOfGainCalibration" },
{ 0x0009, 0x0077, 0, VR::TM, VM::M1, "TimeOfGainCalibration" },
{ 0x0009, 0x0080, 0, VR::OB, VM::M1, "BadPixelImage" },
{ 0x0009, 0x0099, 0, VR::LT, VM::M1, "CalibrationNotes" },
};

unsigned short Dict138TagHashTable[] = {
    4,    13,    24,     0,     4,     0,    64,     3,   112,     6,
  115,     9,   118,     5,     1,    80,     4,   113,     7,   116,
   10,   119,    11,   128,     4,     2,    96,     5,   114,     8,
  117,    12,   153,
};

vtkDICOMDictionary::Dict Dict138Data = {
"astm.org/diconde/iod/NdeDxCalibrationData",
3,
13,
Dict138TagHashTable,
Dict138Contents
};

// ----- GEMS_XELPRV_01 -----

DictEntry Dict139Contents[] = {
{ 0x0033, 0x0008, 0, VR::CS, VM::M1, "" },
{ 0x0033, 0x0010, 0, VR::SL, VM::M1, "" },
{ 0x0033, 0x0011, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x0016, 0, VR::UI, VM::M1, "" },
{ 0x0033, 0x0017, 0, VR::DA, VM::M1, "" },
{ 0x0033, 0x0018, 0, VR::TM, VM::M1, "" },
{ 0x0033, 0x0019, 0, VR::UL, VM::M1, "" },
{ 0x0033, 0x001a, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x001b, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x001c, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x001d, 0, VR::UL, VM::M1, "" },
{ 0x0033, 0x001e, 0, VR::FD, VM::M1, "" },
{ 0x0033, 0x001f, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0020, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0021, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0022, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0023, 0, VR::OB, VM::M1, "" },
{ 0x0033, 0x0024, 0, VR::LT, VM::M1, "" },
{ 0x0033, 0x0070, 0, VR::SQ, VM::M1, "" },
{ 0x0033, 0x0071, 0, VR::UI, VM::M1, "" },
{ 0x0033, 0x0072, 0, VR::UI, VM::M1, "" },
};

unsigned short Dict139TagHashTable[] = {
    6,    13,    24,    35,    42,     0,     3,     1,    16,     8,
   27,    11,    30,     5,     4,    23,     7,    26,    10,    29,
   16,    35,    18,   112,     5,     3,    22,     6,    25,     9,
   28,    15,    34,    19,   113,     3,     5,    24,    14,    33,
   17,    36,     5,     0,     8,     2,    17,    12,    31,    13,
   32,    20,   114,
};

vtkDICOMDictionary::Dict Dict139Data = {
"GEMS_XELPRV_01",
5,
21,
Dict139TagHashTable,
Dict139Contents
};

// ----- Philips MR Imaging DD 002 -----

DictEntry Dict140Contents[] = {
{ 0x2005, 0x0032, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0034, 0, VR::LT, VM::M1, "" },
{ 0x2005, 0x0037, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0038, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0039, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0040, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0041, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0043, 0, VR::SL, VM::M1, "" },
{ 0x2005, 0x0044, 0, VR::OW, VM::M1, "" },
{ 0x2005, 0x0047, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0099, 0, VR::UL, VM::M1, "" },
};

unsigned short Dict140TagHashTable[] = {
    3,    14,     0,     5,     2,    55,     4,    57,     5,    64,
    8,    68,    10,   153,     6,     0,    50,     1,    52,     3,
   56,     6,    65,     7,    67,     9,    71,
};

vtkDICOMDictionary::Dict Dict140Data = {
"Philips MR Imaging DD 002",
2,
11,
Dict140TagHashTable,
Dict140Contents
};

// ----- VEPRO VIM 5.0 DATA -----

DictEntry Dict141Contents[] = {
{ 0x0055, 0x0010, 0, VR::OB, VM::M1, "" },
{ 0x0055, 0x0020, 0, VR::OB, VM::M1, "" },
{ 0x0055, 0x0030, 0, VR::OB, VM::M1, "IconData" },
{ 0x0055, 0x0051, 0, VR::UI, VM::M1, "" },
{ 0x0055, 0x0065, 0, VR::OB, VM::M1, "ImageHashValue" },
};

unsigned short Dict141TagHashTable[] = {
    2,     0,     5,     0,    16,     1,    32,     2,    48,     3,
   81,     4,   101,
};

vtkDICOMDictionary::Dict Dict141Data = {
"VEPRO VIM 5.0 DATA",
1,
5,
Dict141TagHashTable,
Dict141Contents
};

// ----- SIEMENS DICOM -----

DictEntry Dict142Contents[] = {
{ 0x0009, 0x0010, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x0012, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict142TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    18,
};

vtkDICOMDictionary::Dict Dict142Data = {
"SIEMENS DICOM",
1,
2,
Dict142TagHashTable,
Dict142Contents
};

// ----- SIEMENS MED NM -----

DictEntry Dict143Contents[] = {
{ 0x0009, 0x0080, 0, VR::ST, VM::M1, "" },
{ 0x0011, 0x0010, 0, VR::ST, VM::M1, "" },
{ 0x0017, 0x0000, 0, VR::ST, VM::M1, "" },
{ 0x0017, 0x0020, 0, VR::ST, VM::M1, "" },
{ 0x0017, 0x0070, 0, VR::ST, VM::M1, "" },
{ 0x0017, 0x0080, 0, VR::ST, VM::M1, "" },
{ 0x0019, 0x0008, 0, VR::SS, VM::M1, "" },
{ 0x0019, 0x000F, 0, VR::SL, VM::M1TN, "SiemensICONDataType" },
{ 0x0019, 0x0016, 0, VR::SS, VM::M1, "" },
{ 0x0019, 0x0093, 0, VR::SL, VM::M2, "" },
{ 0x0019, 0x00A5, 0, VR::SS, VM::M1TN, "NumberOfRepeatsPerPhase" },
{ 0x0019, 0x00A6, 0, VR::SS, VM::M1TN, "CyclesPerRepeat" },
{ 0x0019, 0x00A7, 0, VR::SL, VM::M1TN, "RepeatStartTime" },
{ 0x0019, 0x00A8, 0, VR::SL, VM::M1TN, "RepeatStopTime" },
{ 0x0019, 0x00A9, 0, VR::SL, VM::M1TN, "EffectiveRepeatTime" },
{ 0x0019, 0x00AA, 0, VR::SS, VM::M1TN, "AcquiredCyclesPerRepeat" },
{ 0x0019, 0x00a1, 0, VR::SS, VM::M1, "" },
{ 0x0019, 0x00a3, 0, VR::SL, VM::M2, "" },
{ 0x0019, 0x00c3, 0, VR::ST, VM::M1, "" },
{ 0x0021, 0x0000, 0, VR::OB, VM::M1, "ECATMainHeader" },
{ 0x0021, 0x0001, 0, VR::OB, VM::M1, "ECATImageSubheader" },
{ 0x0021, 0x0010, 0, VR::ST, VM::M1, "" },
{ 0x0023, 0x0001, 0, VR::US, VM::M1, "DICOMReaderFlag" },
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "ModalityImageHeaderType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "ModalityImageHeaderVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "ModalityImageHeaderInfo" },
{ 0x0031, 0x0001, 0, VR::ST, VM::M1, "" },
{ 0x0031, 0x000c, 0, VR::SS, VM::M1, "" },
{ 0x0031, 0x000f, 0, VR::SL, VM::M1, "" },
{ 0x0031, 0x0010, 0, VR::SL, VM::M1, "" },
{ 0x0031, 0x0012, 0, VR::SS, VM::M1, "" },
{ 0x0031, 0x0013, 0, VR::ST, VM::M1, "" },
{ 0x0031, 0x0014, 0, VR::ST, VM::M1, "" },
{ 0x0031, 0x0015, 0, VR::SL, VM::M1TN, "" },
{ 0x0031, 0x0016, 0, VR::SL, VM::M1TN, "" },
{ 0x0031, 0x0017, 0, VR::SS, VM::M1TN, "" },
{ 0x0031, 0x0020, 0, VR::ST, VM::M1, "" },
{ 0x0031, 0x0021, 0, VR::SS, VM::M1, "" },
{ 0x0033, 0x0000, 0, VR::FL, VM::M1TN, "FloodCorrectionMatrixDetector1" },
{ 0x0033, 0x0001, 0, VR::FL, VM::M1TN, "FloodCorrectionMatrixDetector2" },
{ 0x0033, 0x0010, 0, VR::FL, VM::M1TN, "CORDataForDetector1" },
{ 0x0033, 0x0011, 0, VR::FL, VM::M1TN, "CORDataForDetector2" },
{ 0x0033, 0x0014, 0, VR::FL, VM::M1, "MHRDataForDetector1" },
{ 0x0033, 0x0015, 0, VR::FL, VM::M1, "MHRDataForDetector2" },
{ 0x0033, 0x0018, 0, VR::FL, VM::M1TN, "NCODataForDetector1" },
{ 0x0033, 0x0019, 0, VR::FL, VM::M1TN, "NCODataForDetector2" },
{ 0x0033, 0x001A, 0, VR::FL, VM::M1TN, "" },
{ 0x0033, 0x0020, 0, VR::FL, VM::M1, "BedCorrectionAngle" },
{ 0x0033, 0x0021, 0, VR::FL, VM::M1, "GantryCorrectionAngle" },
{ 0x0033, 0x0022, 0, VR::SS, VM::M1TN, "BedUDCorrectionData" },
{ 0x0033, 0x0023, 0, VR::SS, VM::M1TN, "GantryLRCorrectionData" },
{ 0x0033, 0x0024, 0, VR::FL, VM::M1, "BackProjectionCorrectionAngleHead1" },
{ 0x0033, 0x0025, 0, VR::FL, VM::M1, "BackProjectionCorrectionAngleHead2" },
{ 0x0033, 0x0028, 0, VR::SL, VM::M1, "MHRCalibrations" },
{ 0x0033, 0x0029, 0, VR::FL, VM::M1TN, "CrystalThickness" },
{ 0x0033, 0x0030, 0, VR::LO, VM::M1, "PresetNameUsedForAcquisition" },
{ 0x0033, 0x0031, 0, VR::FL, VM::M1, "CameraConfigAngle" },
{ 0x0033, 0x0032, 0, VR::LO, VM::M1, "CrystalType" },
{ 0x0033, 0x0033, 0, VR::SL, VM::M1, "CoinGantryStep" },
{ 0x0033, 0x0034, 0, VR::FL, VM::M1, "WholebodyBedStep" },
{ 0x0033, 0x0035, 0, VR::FL, VM::M1, "WeightFactorTableForCoincidenceAcquisitions" },
{ 0x0033, 0x0036, 0, VR::FL, VM::M1, "CoincidenceWeightFactorTable" },
{ 0x0033, 0x0037, 0, VR::SL, VM::M1, "StarburstFlagsAtImageAcqTime" },
{ 0x0033, 0x0038, 0, VR::FL, VM::M1, "PixelScaleFactor" },
{ 0x0035, 0x0000, 0, VR::LO, VM::M1, "SpecializedTomoType" },
{ 0x0035, 0x0001, 0, VR::LO, VM::M1, "EnergyWindowType" },
{ 0x0035, 0x0002, 0, VR::SS, VM::M1, "StartandEndRowIlluminatedByWindPosition" },
{ 0x0035, 0x0003, 0, VR::LO, VM::M1, "BlankScanImageForProfile" },
{ 0x0035, 0x0004, 0, VR::SS, VM::M1, "RepeatNumberOfTheOriginalDynamicSPECT" },
{ 0x0035, 0x0005, 0, VR::SS, VM::M1, "PhaseNumberOfTheOriginalDynamicSPECT" },
{ 0x0035, 0x0006, 0, VR::LO, VM::M1, "SiemensProfile2ImageSubtype" },
{ 0x0037, 0x0000, 0, VR::OW, VM::M1, "FloodCorrectionMatrixDetector1" },
{ 0x0037, 0x0080, 0, VR::OW, VM::M1, "FloodCorrectionMatrixDetector2" },
{ 0x0039, 0x0000, 0, VR::LT, VM::M1, "ToshibaCBFActivityResults" },
{ 0x0039, 0x0001, 0, VR::LT, VM::M1, "RelatedCTSeriesInstanceUID" },
{ 0x0041, 0x0001, 0, VR::SL, VM::M1, "WholeBodyTomoPositionIndex" },
{ 0x0041, 0x0002, 0, VR::SL, VM::M1, "WholeBodyTomoNumberOfPositions" },
{ 0x0041, 0x0003, 0, VR::FL, VM::M1, "HorizontalTablePositionOfCTScan" },
{ 0x0041, 0x0004, 0, VR::FL, VM::M1, "EffectiveEnergyOfCTScan" },
{ 0x0041, 0x0005, 0, VR::FD, VM::M1TN, "LongLinearDriveInformationForDetector1" },
{ 0x0041, 0x0006, 0, VR::FD, VM::M1TN, "LongLinearDriveInformationForDetector2" },
{ 0x0041, 0x0007, 0, VR::FD, VM::M1TN, "TrunnionInformationForDetector1" },
{ 0x0041, 0x0008, 0, VR::FD, VM::M1TN, "TrunnionInformationForDetector2" },
{ 0x0041, 0x0009, 0, VR::FL, VM::M1, "BroadBeamFactor" },
{ 0x0041, 0x000A, 0, VR::FD, VM::M1, "OriginalWholebodyPosition" },
{ 0x0041, 0x000B, 0, VR::FD, VM::M1, "WholebodyScanRange" },
{ 0x0041, 0x0010, 0, VR::FL, VM::M1T3, "EffectiveEmissionEnergy" },
{ 0x0041, 0x0011, 0, VR::FL, VM::M1TN, "GatedFrameDuration" },
{ 0x0041, 0x0030, 0, VR::ST, VM::M1, "" },
{ 0x0041, 0x0032, 0, VR::ST, VM::M1, "" },
{ 0x0043, 0x0001, 0, VR::FL, VM::M1TN, "DetectorViewAngle" },
{ 0x0043, 0x0002, 0, VR::FD, VM::M1T16, "TransformationMatrix" },
{ 0x0043, 0x0003, 0, VR::FL, VM::M1TN, "ViewDependentYShiftMHRForDetector1" },
{ 0x0043, 0x0004, 0, VR::FL, VM::M1TN, "ViewDependentYShiftMHRForDetector2" },
{ 0x0045, 0x0001, 0, VR::LO, VM::M1TN, "PlanarProcessingString" },
{ 0x0055, 0x0004, 0, VR::SS, VM::M1, "PromptWindowWidth" },
{ 0x0055, 0x0005, 0, VR::SS, VM::M1, "RandomWindowWidth" },
{ 0x0055, 0x0020, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0022, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0024, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0030, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0032, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0034, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0040, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0042, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0044, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x004c, 0, VR::SL, VM::M1, "" },
{ 0x0055, 0x004d, 0, VR::SL, VM::M1, "" },
{ 0x0055, 0x0051, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0052, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x0053, 0, VR::ST, VM::M1, "" },
{ 0x0055, 0x0055, 0, VR::SL, VM::M1, "" },
{ 0x0055, 0x005c, 0, VR::ST, VM::M1, "" },
{ 0x0055, 0x006d, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x007e, 0, VR::FL, VM::M2, "CollimatorThickness" },
{ 0x0055, 0x007f, 0, VR::FL, VM::M2, "CollimatorAngularResolution" },
{ 0x0055, 0x00C0, 0, VR::SS, VM::M1TN, "UsefulFieldOfView" },
{ 0x0055, 0x00a8, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x00c2, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x00c3, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x00c4, 0, VR::SS, VM::M1, "" },
{ 0x0055, 0x00d0, 0, VR::SS, VM::M1, "" },
{ 0x0057, 0x0001, 0, VR::LO, VM::M1, "SyngoMIDICOMOriginalImageType" },
{ 0x0057, 0x0002, 0, VR::FL, VM::M1, "DoseCalibrationFactor" },
{ 0x0057, 0x0003, 0, VR::LO, VM::M1, "Units" },
{ 0x0057, 0x0004, 0, VR::LO, VM::M1, "DecayCorrection" },
{ 0x0057, 0x0005, 0, VR::SL, VM::M1TN, "RadionuclideHalfLife" },
{ 0x0057, 0x0006, 0, VR::FL, VM::M1, "RescaleIntercept" },
{ 0x0057, 0x0007, 0, VR::FL, VM::M1, "RescaleSlope" },
{ 0x0057, 0x0008, 0, VR::FL, VM::M1, "FrameReferenceTime" },
{ 0x0057, 0x0009, 0, VR::SL, VM::M1, "NumberofRadiopharmaceuticalInformationSequence" },
{ 0x0057, 0x000A, 0, VR::FL, VM::M1, "DecayFactor" },
{ 0x0057, 0x000B, 0, VR::LO, VM::M1, "CountsSource" },
{ 0x0057, 0x000C, 0, VR::SL, VM::M1TN, "RadionuclidePositronFraction" },
{ 0x0057, 0x000E, 0, VR::US, VM::M1TN, "TriggerTimeOfCTSlice" },
{ 0x0061, 0x0001, 0, VR::FL, VM::M1TN, "XPrincipalRayOffset" },
{ 0x0061, 0x0005, 0, VR::FL, VM::M1TN, "YPrincipalRayOffset" },
{ 0x0061, 0x0009, 0, VR::FL, VM::M1TN, "XPrincipalRayAngle" },
{ 0x0061, 0x000A, 0, VR::FL, VM::M1TN, "YPrincipalRayAngle" },
{ 0x0061, 0x000B, 0, VR::FL, VM::M1TN, "XShortFocalLength" },
{ 0x0061, 0x000C, 0, VR::FL, VM::M1TN, "YShortFocalLength" },
{ 0x0061, 0x000D, 0, VR::FL, VM::M1TN, "XLongFocalLength" },
{ 0x0061, 0x000E, 0, VR::FL, VM::M1TN, "YLongFocalLength" },
{ 0x0061, 0x000F, 0, VR::FL, VM::M1TN, "XFocalScaling" },
{ 0x0061, 0x0010, 0, VR::FL, VM::M1TN, "YFocalScaling" },
{ 0x0061, 0x0011, 0, VR::FL, VM::M1TN, "XMotionCorrectionShift" },
{ 0x0061, 0x0015, 0, VR::FL, VM::M1TN, "YMotionCorrectionShift" },
{ 0x0061, 0x0019, 0, VR::FL, VM::M1, "XHeartCenter" },
{ 0x0061, 0x001A, 0, VR::FL, VM::M1, "YHeartCenter" },
{ 0x0061, 0x001B, 0, VR::FL, VM::M1, "ZHeartCenter" },
{ 0x0061, 0x001C, 0, VR::LO, VM::M1, "ImagePixelContentType" },
{ 0x0061, 0x001D, 0, VR::SS, VM::M1, "AutoSaveCorrectedSeries" },
{ 0x0061, 0x001E, 0, VR::LT, VM::M1, "DistortedSeriesInstanceUID" },
{ 0x0061, 0x0021, 0, VR::SS, VM::M1TN, "ReconRange" },
{ 0x0061, 0x0022, 0, VR::LO, VM::M1, "ReconOrientation" },
{ 0x0061, 0x0023, 0, VR::FL, VM::M1TN, "ReconSelectedAngularRange" },
{ 0x0061, 0x0024, 0, VR::FL, VM::M1, "ReconTransverseAngle" },
{ 0x0061, 0x0025, 0, VR::FL, VM::M1, "ReconSagittalAngle" },
{ 0x0061, 0x0026, 0, VR::FL, VM::M1, "ReconXMaskSize" },
{ 0x0061, 0x0027, 0, VR::FL, VM::M1, "ReconYMaskSize" },
{ 0x0061, 0x0028, 0, VR::FL, VM::M1, "ReconXImageCenter" },
{ 0x0061, 0x0029, 0, VR::FL, VM::M1, "ReconYImageCenter" },
{ 0x0061, 0x002A, 0, VR::FL, VM::M1, "ReconZImageCenter" },
{ 0x0061, 0x002B, 0, VR::FL, VM::M1, "ReconXZoom" },
{ 0x0061, 0x002C, 0, VR::FL, VM::M1, "ReconYZoom" },
{ 0x0061, 0x002D, 0, VR::FL, VM::M1, "ReconThreshold" },
{ 0x0061, 0x002E, 0, VR::FL, VM::M1, "ReconOutputPixelSize" },
{ 0x0061, 0x002F, 0, VR::LO, VM::M1TN, "ScatterEstimationMethod" },
{ 0x0061, 0x0030, 0, VR::LO, VM::M1TN, "ScatterEstimationMethodMode" },
{ 0x0061, 0x0031, 0, VR::FL, VM::M1TN, "ScatterEstimationLowerWindowWeights" },
{ 0x0061, 0x0032, 0, VR::FL, VM::M1TN, "ScatterEstimationUpperWindowWeights" },
{ 0x0061, 0x0033, 0, VR::LO, VM::M1TN, "ScatterEstimationWindowMode" },
{ 0x0061, 0x0034, 0, VR::LO, VM::M1TN, "ScatterEstimationFilter" },
{ 0x0061, 0x0035, 0, VR::LO, VM::M1, "ReconRawTomoInputUID" },
{ 0x0061, 0x0036, 0, VR::LO, VM::M1, "ReconCTInputUID" },
{ 0x0061, 0x0037, 0, VR::FL, VM::M1, "ReconZMaskSize" },
{ 0x0061, 0x0038, 0, VR::FL, VM::M1, "ReconXMaskCenter" },
{ 0x0061, 0x0039, 0, VR::FL, VM::M1, "ReconYMaskCenter" },
{ 0x0061, 0x003A, 0, VR::FL, VM::M1, "ReconZMaskCenter" },
{ 0x0061, 0x0051, 0, VR::LT, VM::M1, "RawTomoSeriesUID" },
{ 0x0061, 0x0052, 0, VR::LT, VM::M1, "LowResCTSeriesUID" },
{ 0x0061, 0x0053, 0, VR::LT, VM::M1, "HighResCTSeriesUID" },
{ 0x7FE3, 0x0014, 0, VR::OW, VM::M1, "MinimumPixelInFrame" },
{ 0x7FE3, 0x0015, 0, VR::OW, VM::M1, "MaximumPixelInFrame" },
{ 0x7FE3, 0x0029, 0, VR::OW, VM::M1, "NumberOfRWavesInFrame" },
{ 0x7fe3, 0x0016, 0, VR::OW, VM::M1, "" },
{ 0x7fe3, 0x001b, 0, VR::OW, VM::M1, "" },
{ 0x7fe3, 0x001c, 0, VR::OW, VM::M1, "" },
{ 0x7fe3, 0x001e, 0, VR::OW, VM::M1, "" },
{ 0x7fe3, 0x0026, 0, VR::OW, VM::M1, "" },
{ 0x7fe3, 0x0027, 0, VR::OW, VM::M1, "" },
{ 0x7fe3, 0x0028, 0, VR::OW, VM::M1, "" },
};

unsigned short Dict143TagHashTable[] = {
   49,    64,    75,    84,    95,   108,   121,   132,   147,   154,
  165,   172,   179,   182,   187,   194,   199,   212,   229,   238,
  247,   254,   265,   278,   289,   296,   307,   316,   325,   330,
  335,   340,   343,   356,   373,   386,   397,   404,   413,   420,
  431,   440,   445,   456,   463,   468,   473,   478,     0,     7,
   26,     1,    58,    51,    69,     5,   102,    52,   111,    85,
  179,    81,   187,    28,     5,     1,    16,    21,    16,    57,
   50,    68,     4,   135,     1,     4,    39,     1,    56,    49,
  181,    83,   188,    30,     5,    38,     0,    55,    48,    70,
    6,   120,   196,   180,    82,     6,    62,    55,    65,     1,
  100,    48,   108,    81,   119,   195,   191,    40,     6,     5,
  128,    61,    54,    64,     0,   118,   194,   136,     5,   184,
   41,     5,     4,   112,    60,    53,    67,     3,   101,    50,
  110,    83,     7,     3,    32,    59,    52,    66,     2,    71,
    0,   109,    82,   116,   192,   186,    27,     3,    74,     1,
  113,   109,   182,    20,     5,    25,    16,    73,     0,   112,
   92,   137,     9,   183,    21,     3,   138,    10,   185,    22,
  189,    38,     3,    63,    56,   139,    11,   190,    39,     1,
  140,    12,     2,    27,    12,   141,    13,     3,    28,    15,
  117,   168,   142,    14,     2,     8,    22,   143,    15,     6,
   37,    33,    50,    35,    88,    48,    91,     2,    99,    36,
  144,    16,     8,     6,     8,    36,    32,    49,    34,    75,
    1,    92,     3,   105,    68,   145,    17,   153,    33,     4,
   48,    33,    76,     2,    89,    50,   154,    34,     4,    47,
   32,    77,     3,    90,     1,   155,    35,     3,    78,     4,
   97,    32,   156,    36,     5,    79,     5,    94,     1,   103,
   64,   146,    21,   157,    37,     6,     7,    15,    52,    37,
   80,     6,    93,     4,    98,    34,   158,    38,     5,     2,
    0,    51,    36,    81,     7,   104,    66,   159,    39,     3,
   82,     8,   107,    77,   160,    40,     5,    18,   195,    83,
    9,   106,    76,   147,    25,   161,    41,     4,    54,    41,
   84,    10,   148,    26,   162,    42,     4,    53,    40,    85,
   11,   149,    27,   163,    43,     2,   150,    28,   164,    44,
    2,   151,    29,   165,    45,     2,   152,    30,   166,    46,
    1,   167,    47,     6,    20,     1,    24,     9,    86,    16,
   95,     4,   127,     6,   168,    48,     8,    15,   170,    19,
    0,    23,     8,    29,    16,    87,    17,    96,     5,   128,
    7,   169,    49,     6,    14,   169,    22,     1,    31,    19,
   41,    17,   125,     4,   170,    50,     5,    13,   168,    30,
   18,    40,    16,   126,     5,   171,    51,     3,    33,    21,
  123,     2,   172,    52,     4,    32,    20,    72,   128,   124,
    3,   173,    53,     3,    35,    23,    43,    21,   174,    54,
    5,    34,    22,    42,    20,   121,   208,   122,     1,   175,
   55,     4,     9,   147,    17,   163,   134,    14,   176,    56,
    2,    46,    26,   177,    57,     5,    16,   161,    45,    25,
  115,   127,   133,    12,   178,    58,     3,     0,   128,    44,
   24,   114,   126,     2,    12,   167,   131,    10,     2,    11,
  166,   132,    11,     2,    10,   165,   129,     8,     1,   130,
    9,
};

vtkDICOMDictionary::Dict Dict143Data = {
"SIEMENS MED NM",
48,
192,
Dict143TagHashTable,
Dict143Contents
};

// ----- SPI-P-XSB-DCI Release 1 -----

DictEntry Dict144Contents[] = {
{ 0x0019, 0x0010, 0, VR::LT, VM::M1, "VideoBeamBoost" },
{ 0x0019, 0x0011, 0, VR::US, VM::M1, "ChannelGeneratingVideoSync" },
{ 0x0019, 0x0012, 0, VR::US, VM::M1, "VideoGain" },
{ 0x0019, 0x0013, 0, VR::US, VM::M1, "VideoOffset" },
{ 0x0019, 0x0020, 0, VR::DS, VM::M1, "RTDDataCompressionFactor" },
};

unsigned short Dict144TagHashTable[] = {
    2,     0,     5,     0,    16,     1,    17,     2,    18,     3,
   19,     4,    32,
};

vtkDICOMDictionary::Dict Dict144Data = {
"SPI-P-XSB-DCI Release 1",
1,
5,
Dict144TagHashTable,
Dict144Contents
};

// ----- GEMS_AWSOFT_CD1 -----

DictEntry Dict145Contents[] = {
{ 0x0039, 0x0065, 0, VR::UI, VM::M1, "ReferenceToStudyUID" },
{ 0x0039, 0x0070, 0, VR::UI, VM::M1, "ReferenceToSeriesUID" },
{ 0x0039, 0x0075, 0, VR::IS, VM::M1, "ReferenceToOriginalInstance" },
{ 0x0039, 0x0080, 0, VR::IS, VM::M1, "DPONumber" },
{ 0x0039, 0x0085, 0, VR::DA, VM::M1, "DPODate" },
{ 0x0039, 0x0090, 0, VR::TM, VM::M1, "DPOTime" },
{ 0x0039, 0x0095, 0, VR::LO, VM::M1, "DPOInvocationString" },
{ 0x0039, 0x00AA, 0, VR::CS, VM::M1, "DPOType" },
{ 0x0039, 0x00FF, 0, VR::OB, VM::M1, "DPOData" },
};

unsigned short Dict145TagHashTable[] = {
    3,    10,     0,     3,     1,   112,     4,   133,     6,   149,
    6,     0,   101,     2,   117,     3,   128,     5,   144,     7,
  170,     8,   255,
};

vtkDICOMDictionary::Dict Dict145Data = {
"GEMS_AWSOFT_CD1",
2,
9,
Dict145TagHashTable,
Dict145Contents
};

// ----- GEMS_SEND_02 -----

DictEntry Dict146Contents[] = {
{ 0x0045, 0x0055, 0, VR::DS, VM::M8, "A_Coefficients" },
{ 0x0045, 0x0062, 0, VR::IS, VM::M1, "UserWindowCenter" },
{ 0x0045, 0x0063, 0, VR::IS, VM::M1, "UserWindowWidth" },
{ 0x0045, 0x0065, 0, VR::IS, VM::M1, "RequestedDetectorEntranceDose" },
{ 0x0045, 0x0067, 0, VR::DS, VM::M3, "VOILUTAssymmetryParameterBeta" },
{ 0x0045, 0x0069, 0, VR::IS, VM::M1, "CollimatorRotation" },
{ 0x0045, 0x0072, 0, VR::IS, VM::M1, "CollimatorWidth" },
{ 0x0045, 0x0073, 0, VR::IS, VM::M1, "CollimatorHeight" },
};

unsigned short Dict146TagHashTable[] = {
    3,    16,     0,     6,     0,    85,     2,    99,     3,   101,
    4,   103,     5,   105,     7,   115,     2,     1,    98,     6,
  114,
};

vtkDICOMDictionary::Dict Dict146Data = {
"GEMS_SEND_02",
2,
8,
Dict146TagHashTable,
Dict146Contents
};

// ----- Philips Imaging DD 001 -----

DictEntry Dict147Contents[] = {
{ 0x2001, 0x0001, 0, VR::FL, VM::M1, "ChemicalShift" },
{ 0x2001, 0x0002, 0, VR::IS, VM::M1, "ChemicalShiftNumberMR" },
{ 0x2001, 0x0003, 0, VR::FL, VM::M1, "DiffusionBFactor" },
{ 0x2001, 0x0004, 0, VR::CS, VM::M1, "DiffusionDirection" },
{ 0x2001, 0x0005, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0006, 0, VR::CS, VM::M1, "ImageEnhanced" },
{ 0x2001, 0x0007, 0, VR::CS, VM::M1, "ImageTypeEDES" },
{ 0x2001, 0x0008, 0, VR::IS, VM::M1, "PhaseNumber" },
{ 0x2001, 0x0009, 0, VR::FL, VM::M1, "ImagePrepulseDelay" },
{ 0x2001, 0x000a, 0, VR::IS, VM::M1, "SliceNumberMR" },
{ 0x2001, 0x000b, 0, VR::CS, VM::M1, "SliceOrientation" },
{ 0x2001, 0x000c, 0, VR::CS, VM::M1, "ArrhythmiaRejection" },
{ 0x2001, 0x000e, 0, VR::CS, VM::M1, "CardiacCycled" },
{ 0x2001, 0x000f, 0, VR::SS, VM::M1, "CardiacGateWidth" },
{ 0x2001, 0x0010, 0, VR::CS, VM::M1, "CardiacSync" },
{ 0x2001, 0x0011, 0, VR::FL, VM::M1, "DiffusionEchoTime" },
{ 0x2001, 0x0012, 0, VR::CS, VM::M1, "DynamicSeries" },
{ 0x2001, 0x0013, 0, VR::SL, VM::M1, "EPIFactor" },
{ 0x2001, 0x0014, 0, VR::SL, VM::M1, "NumberOfEchoes" },
{ 0x2001, 0x0015, 0, VR::SS, VM::M1, "NumberOfLocations" },
{ 0x2001, 0x0016, 0, VR::SS, VM::M1, "NumberOfPCDirections" },
{ 0x2001, 0x0017, 0, VR::SL, VM::M1, "NumberOfPhasesMR" },
{ 0x2001, 0x0018, 0, VR::SL, VM::M1, "NumberOfSlicesMR" },
{ 0x2001, 0x0019, 0, VR::CS, VM::M1, "PartialMatrixScanned" },
{ 0x2001, 0x001a, 0, VR::FL, VM::M3, "PCVelocity" },
{ 0x2001, 0x001b, 0, VR::FL, VM::M1, "PrepulseDelay" },
{ 0x2001, 0x001c, 0, VR::CS, VM::M1, "PrepulseType" },
{ 0x2001, 0x001d, 0, VR::IS, VM::M1, "ReconstructionNumberMR" },
{ 0x2001, 0x001e, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x001f, 0, VR::CS, VM::M1, "RespirationSync" },
{ 0x2001, 0x0020, 0, VR::LO, VM::M1, "ScanningTechnique" },
{ 0x2001, 0x0021, 0, VR::CS, VM::M1, "SPIR" },
{ 0x2001, 0x0022, 0, VR::FL, VM::M1, "WaterFatShift" },
{ 0x2001, 0x0023, 0, VR::DS, VM::M1, "FlipAngle" },
{ 0x2001, 0x0024, 0, VR::CS, VM::M1, "SeriesIsInteractive" },
{ 0x2001, 0x0025, 0, VR::SH, VM::M1, "EchoTimeDisplay" },
{ 0x2001, 0x0026, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0029, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x002b, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x002d, 0, VR::SS, VM::M1, "NumberOfSlicesInStack" },
{ 0x2001, 0x0032, 0, VR::FL, VM::M1, "StackRadialAngle" },
{ 0x2001, 0x0033, 0, VR::CS, VM::M1, "StackRadialAxis" },
{ 0x2001, 0x0035, 0, VR::SS, VM::M1, "StackSliceNumber" },
{ 0x2001, 0x0036, 0, VR::CS, VM::M1, "StackSliceType" },
{ 0x2001, 0x0039, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x003d, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x003f, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0046, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0047, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x0048, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x004b, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x004c, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x004d, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x004e, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0051, 0, VR::IS, VM::M1, "" },
{ 0x2001, 0x0052, 0, VR::UI, VM::M1, "" },
{ 0x2001, 0x0053, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0054, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x0055, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x0056, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0058, 0, VR::UL, VM::M1, "ContrastTransferTaste" },
{ 0x2001, 0x005a, 0, VR::ST, VM::M1, "" },
{ 0x2001, 0x005f, 0, VR::SQ, VM::M1, "StackSequence" },
{ 0x2001, 0x0060, 0, VR::SL, VM::M1, "NumberOfStacks" },
{ 0x2001, 0x0061, 0, VR::CS, VM::M1, "SeriesTransmitted" },
{ 0x2001, 0x0062, 0, VR::CS, VM::M1, "SeriesCommitted" },
{ 0x2001, 0x0063, 0, VR::CS, VM::M1, "ExaminationSource" },
{ 0x2001, 0x0064, 0, VR::SH, VM::M1, "" },
{ 0x2001, 0x0065, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x0067, 0, VR::CS, VM::M1, "LinearPresentationGLTrafoShapeSub" },
{ 0x2001, 0x0068, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x0069, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x006a, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x006b, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x006d, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x006e, 0, VR::SH, VM::M1, "SeriesType" },
{ 0x2001, 0x0071, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0074, 0, VR::DS, VM::M1, "" },
{ 0x2001, 0x0075, 0, VR::DS, VM::M1, "" },
{ 0x2001, 0x0076, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x0077, 0, VR::CS, VM::M1, "GLTrafoType" },
{ 0x2001, 0x007a, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x007b, 0, VR::IS, VM::M1, "AcquisitionNumber" },
{ 0x2001, 0x0080, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0081, 0, VR::IS, VM::M1, "NumberOfDynamicScans" },
{ 0x2001, 0x0082, 0, VR::IS, VM::M1, "EchoTrainLength" },
{ 0x2001, 0x0083, 0, VR::DS, VM::M1, "ImagingFrequency" },
{ 0x2001, 0x0084, 0, VR::DS, VM::M1, "InversionTime" },
{ 0x2001, 0x0085, 0, VR::DS, VM::M1, "MagneticFieldStrength" },
{ 0x2001, 0x0086, 0, VR::IS, VM::M1, "" },
{ 0x2001, 0x0087, 0, VR::SH, VM::M1, "ImagedNucleus" },
{ 0x2001, 0x0088, 0, VR::DS, VM::M1, "" },
{ 0x2001, 0x0089, 0, VR::DS, VM::M1, "" },
{ 0x2001, 0x008a, 0, VR::DS, VM::M1, "" },
{ 0x2001, 0x008b, 0, VR::SH, VM::M1, "" },
{ 0x2001, 0x0090, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0091, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0092, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0093, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x009a, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x009b, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x009c, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x009f, 0, VR::US, VM::M2, "PixelProcessingKernelSize" },
{ 0x2001, 0x00a1, 0, VR::CS, VM::M1, "IsRawImage" },
{ 0x2001, 0x00a3, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x00a4, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x00a5, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x00c1, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x00c8, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x00cc, 0, VR::ST, VM::M1, "" },
{ 0x2001, 0x00da, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x00f1, 0, VR::FL, VM::M1TN, "ProspectiveMotionCorrection" },
{ 0x2001, 0x00f2, 0, VR::FL, VM::M1TN, "RetrospectiveMotionCorrection" },
};

unsigned short Dict147TagHashTable[] = {
   29,    36,    43,    50,    57,    68,    77,    88,    95,   106,
  113,   126,   133,   140,   147,   152,   161,   172,   179,   190,
  203,   218,   225,   232,   241,   250,   259,   272,     0,     3,
   23,    25,    42,    53,    54,    80,     3,    22,    24,    55,
   81,    75,   109,     3,    25,    27,    56,    82,    76,   110,
    3,    24,    26,    43,    54,    57,    83,     5,     0,     1,
   27,    29,    44,    57,    58,    84,    99,   147,     4,    26,
   28,    59,    85,    77,   113,    98,   146,     5,     2,     3,
   29,    31,    60,    86,    97,   145,   109,   200,     3,     1,
    2,    28,    30,    96,   144,     5,     4,     5,    31,    33,
   45,    61,    61,    88,    78,   116,     3,     3,     4,    30,
   32,    79,   117,     6,     6,     7,    33,    35,    46,    63,
   62,    90,    80,   118,   110,   204,     3,     5,     6,    32,
   34,    81,   119,     3,     8,     9,    35,    37,   101,   155,
    3,     7,     8,    34,    36,   100,   154,     2,    10,    11,
   82,   122,     4,     9,    10,    36,    38,    63,    95,    83,
  123,     5,    37,    41,    64,    96,    87,   131,   103,   159,
  113,   242,     3,    11,    12,    65,    97,    86,   130,     5,
   13,    15,    38,    43,    47,    70,    66,    98,    85,   129,
    6,    12,    14,    48,    71,    67,    99,    84,   128,   102,
  156,   112,   241,     7,    15,    17,    39,    45,    49,    72,
   68,   100,    91,   135,   105,   163,   111,   218,     3,    14,
   16,    69,   101,    90,   134,     3,    17,    19,    89,   133,
  104,   161,     4,    16,    18,    50,    75,    70,   103,    88,
  132,     4,    19,    21,    51,    76,    71,   104,    95,   139,
    4,    18,    20,    52,    77,    72,   105,    94,   138,     6,
   21,    23,    41,    51,    53,    78,    73,   106,    93,   137,
  107,   165,     6,    20,    22,    40,    50,    74,   107,    92,
  136,   106,   164,   108,   193,
};

vtkDICOMDictionary::Dict Dict147Data = {
"Philips Imaging DD 001",
28,
114,
Dict147TagHashTable,
Dict147Contents
};

// ----- PRIVATE_CODE_STRING_1003 -----

DictEntry Dict148Contents[] = {
{ 0x1003, 0x0001, 0, VR::UN, VM::M1, "NumberOfProbes" },
{ 0x1003, 0x0010, 0, VR::UN, VM::M1, "US Probe Sequence" },
{ 0x1003, 0x0011, 0, VR::UN, VM::M1, "Identifier" },
{ 0x1003, 0x0012, 0, VR::UN, VM::M1, "Probe Name" },
{ 0x1003, 0x0013, 0, VR::UN, VM::M1, "Depth" },
{ 0x1003, 0x0014, 0, VR::UN, VM::M1, "Frequency" },
{ 0x1003, 0x0015, 0, VR::UN, VM::M1, "Gain" },
{ 0x1003, 0x0016, 0, VR::UN, VM::M1, "Power" },
{ 0x1003, 0x0017, 0, VR::UN, VM::M1, "DynamicRange" },
{ 0x1003, 0x0018, 0, VR::UN, VM::M1, "FrameAveraging" },
{ 0x1003, 0x0019, 0, VR::UN, VM::M1, "FieldOfView" },
{ 0x1003, 0x0020, 0, VR::UN, VM::M1, "TGC" },
{ 0x1003, 0x002A, 0, VR::UN, VM::M1, "NumberOfFocusSets" },
{ 0x1003, 0x002B, 0, VR::UN, VM::M1, "CurrentFocusSet" },
{ 0x1003, 0x002C, 0, VR::UN, VM::M1, "ImageEnhancementFilterIndex" },
{ 0x1003, 0x002D, 0, VR::UN, VM::M1, "RejectionFilterLow" },
{ 0x1003, 0x002E, 0, VR::UN, VM::M1, "RejectionFilterHigh" },
{ 0x1003, 0x002F, 0, VR::UN, VM::M1, "Brightness" },
{ 0x1003, 0x0030, 0, VR::UN, VM::M1, "Contrast" },
{ 0x1003, 0x0031, 0, VR::UN, VM::M1, "Gamma" },
{ 0x1003, 0x0032, 0, VR::UN, VM::M1, "SpeckleEnabled" },
{ 0x1003, 0x0033, 0, VR::UN, VM::M1, "SpeckleLevel" },
{ 0x1003, 0x0040, 0, VR::UN, VM::M1, "FocusSetSequence" },
{ 0x1003, 0x0041, 0, VR::UN, VM::M1, "Identifier" },
{ 0x1003, 0x0042, 0, VR::UN, VM::M1, "NumberOfFocusZone" },
{ 0x1003, 0x0043, 0, VR::UN, VM::M1, "Focus" },
};

unsigned short Dict148TagHashTable[] = {
    7,    18,    31,    36,    41,    54,     0,     5,     4,    19,
    6,    21,    13,    43,    15,    45,    22,    64,     6,     3,
   18,     5,    20,    11,    32,    12,    42,    14,    44,    23,
   65,     2,     2,    17,    21,    51,     2,     1,    16,    20,
   50,     6,     0,     1,     8,    23,    10,    25,    17,    47,
   19,    49,    24,    66,     5,     7,    22,     9,    24,    16,
   46,    18,    48,    25,    67,
};

vtkDICOMDictionary::Dict Dict148Data = {
"PRIVATE_CODE_STRING_1003",
6,
26,
Dict148TagHashTable,
Dict148Contents
};

// ----- Applicare/Workflow/Version 1.0 -----

DictEntry Dict149Contents[] = {
{ 0x3113, 0x0001, 0, VR::CS, VM::M1, "OrderControl" },
{ 0x3113, 0x0010, 0, VR::SH, VM::M1, "ScheduledActionItemCodeValue" },
{ 0x3113, 0x0011, 0, VR::SH, VM::M1, "ScheduledActionItemCodingSchemeDesignator" },
{ 0x3113, 0x0012, 0, VR::LO, VM::M1, "ScheduledActionItemCodeMeaning" },
{ 0x3113, 0x0015, 0, VR::SH, VM::M1, "RequestedActionItemCodeValue" },
{ 0x3113, 0x0016, 0, VR::SH, VM::M1, "RequestedActionItemCodingSchemeDesignator" },
{ 0x3113, 0x0017, 0, VR::LO, VM::M1, "RequestedActionItemCodeMeaning" },
{ 0x3113, 0x0020, 0, VR::SH, VM::M1, "PerformedActionItemCodeValue" },
{ 0x3113, 0x0021, 0, VR::SH, VM::M1, "PerformedActionItemCodingSchemeDesignator" },
{ 0x3113, 0x0022, 0, VR::LO, VM::M1, "PerformedActionItemCodeMeaning" },
{ 0x3113, 0x0025, 0, VR::SH, VM::M1, "PerformedProcedureCodeValue" },
{ 0x3113, 0x0026, 0, VR::SH, VM::M1, "PerformedProcedureCodingSchemeDesignator" },
{ 0x3113, 0x0027, 0, VR::LO, VM::M1, "PerformedProcedureCodeMeaning" },
{ 0x3113, 0x0030, 0, VR::UI, VM::M1, "ReferencedImageSOPClassUID" },
{ 0x3113, 0x0031, 0, VR::UI, VM::M1, "ReferencedImageSOPInstanceUID" },
{ 0x3113, 0x00E0, 0, VR::CS, VM::M1, "LockedByHostname" },
{ 0x3113, 0x00E1, 0, VR::CS, VM::M1, "LockedByUser" },
{ 0x3113, 0x00E2, 0, VR::CS, VM::M1, "KfEditLockUser" },
};

unsigned short Dict149TagHashTable[] = {
    5,    12,    23,    38,     0,     3,     6,    23,    12,    39,
   15,   224,     5,     3,    18,     5,    22,     9,    34,    11,
   38,    16,   225,     7,     0,     1,     2,    17,     4,    21,
    8,    33,    10,    37,    14,    49,    17,   226,     3,     1,
   16,     7,    32,    13,    48,
};

vtkDICOMDictionary::Dict Dict149Data = {
"Applicare/Workflow/Version 1.0",
4,
18,
Dict149TagHashTable,
Dict149Contents
};

// ----- PRIVATE_CODE_STRING_1001 -----

DictEntry Dict150Contents[] = {
{ 0x1001, 0x00A0, 0, VR::SQ, VM::M1, "MarkerSequence" },
{ 0x1001, 0x00A1, 0, VR::SL, VM::M1, "MarkerType" },
{ 0x1001, 0x00A2, 0, VR::SL, VM::M1, "MarkerNumber" },
{ 0x1001, 0x00A3, 0, VR::FD, VM::M3, "Marker3DPosition" },
{ 0x1001, 0x00B0, 0, VR::SL, VM::M1, "DistanceUnit" },
{ 0x1001, 0x00B1, 0, VR::SL, VM::M1, "DoseUnit" },
{ 0x1001, 0x00B2, 0, VR::SL, VM::M1, "NormalisationMode" },
{ 0x1001, 0x00B3, 0, VR::FD, VM::M1, "NormalisationFactor" },
{ 0x1001, 0x00B4, 0, VR::FD, VM::M1, "FValue" },
{ 0x1001, 0x00B5, 0, VR::FD, VM::M1, "PrescribedDose" },
{ 0x1001, 0x00B6, 0, VR::FD, VM::M1, "AbsoluteDoseFactor" },
{ 0x1001, 0x00B7, 0, VR::SL, VM::M1, "DecoupledSK" },
{ 0x1001, 0x00B8, 0, VR::FD, VM::M1, "AbsoluteTimeFactor" },
{ 0x1001, 0x00B9, 0, VR::FD, VM::M1, "Total Treatment Time" },
{ 0x1001, 0x00BA, 0, VR::SL, VM::M1, "TG43Model" },
{ 0x1001, 0x00BB, 0, VR::SL, VM::M1, "ThreeDDoseGridSize" },
{ 0x1001, 0x00BC, 0, VR::FD, VM::M3, "DoseGridCorner1" },
{ 0x1001, 0x00BD, 0, VR::FD, VM::M3, "DoseGridCorner2" },
{ 0x1001, 0x00BE, 0, VR::FD, VM::M1, "PatientDataConversion" },
{ 0x1001, 0x00BF, 0, VR::FD, VM::M1, "VolumeDataConversion" },
{ 0x1001, 0x00C0, 0, VR::FD, VM::M3, "VolumeDataVector" },
{ 0x1001, 0x00C1, 0, VR::SL, VM::M1, "OptimizationMethod" },
{ 0x1001, 0x00C2, 0, VR::SL, VM::M1, "DisplayMethod" },
{ 0x1001, 0x00C3, 0, VR::SQ, VM::M1, "VOIBasedOptimizationSettingsSequence" },
{ 0x1001, 0x00C5, 0, VR::SL, VM::M1, "VOINumber" },
{ 0x1001, 0x00C6, 0, VR::LO, VM::M1, "VOIName" },
{ 0x1001, 0x00C7, 0, VR::SL, VM::M1, "VOIType" },
{ 0x1001, 0x00C8, 0, VR::SL, VM::M1, "VOIClass" },
{ 0x1001, 0x00C9, 0, VR::SL, VM::M1, "VOIPriority" },
{ 0x1001, 0x00CA, 0, VR::SL, VM::M1, "NoOfPoints" },
{ 0x1001, 0x00CB, 0, VR::FD, VM::M1, "PercentOnSurface" },
{ 0x1001, 0x00CC, 0, VR::FD, VM::M1, "SurfaceMargin" },
{ 0x1001, 0x00CD, 0, VR::SL, VM::M1, "Selected" },
{ 0x1001, 0x00CE, 0, VR::FD, VM::M1, "DoseLimit" },
{ 0x1001, 0x00CF, 0, VR::FD, VM::M1, "ImportanceFactor" },
{ 0x1001, 0x00D0, 0, VR::FD, VM::M1, "ImportanceFactorFrom" },
{ 0x1001, 0x00D1, 0, VR::FD, VM::M1, "ImportanceFactorTo" },
{ 0x1001, 0x00D2, 0, VR::FD, VM::M1, "Focus" },
{ 0x1001, 0x00D3, 0, VR::SL, VM::M1, "SurfaceSamplingMethod" },
{ 0x1001, 0x00D4, 0, VR::FD, VM::M1, "NumberOfSamplingPointsPerccm" },
{ 0x1001, 0x00D5, 0, VR::SL, VM::M1, "ConvergenceAccuracy" },
{ 0x1001, 0x00D6, 0, VR::SL, VM::M1, "MaxNoOfConvergenceIterations" },
{ 0x1001, 0x00D7, 0, VR::FD, VM::M1, "WeightSmoothing" },
{ 0x1001, 0x00D8, 0, VR::SL, VM::M1, "StepsPerImportanceFactor" },
{ 0x1001, 0x00D9, 0, VR::FD, VM::M1, "ConstraintsPTVDmax" },
{ 0x1001, 0x00DA, 0, VR::FD, VM::M1, "ConstraintsNTDmax" },
{ 0x1001, 0x00DB, 0, VR::SL, VM::M1, "AlgorithmicPopulationSize" },
{ 0x1001, 0x00DC, 0, VR::SL, VM::M1, "AlgorithmicGenerations" },
{ 0x1001, 0x00DD, 0, VR::SL, VM::M1, "AlgorithmicInitializations" },
{ 0x1001, 0x00DE, 0, VR::SL, VM::M1, "MinNoOfSDP" },
{ 0x1001, 0x00DF, 0, VR::SL, VM::M1, "DepthMethod" },
{ 0x1001, 0x00E0, 0, VR::SL, VM::M1, "DepthDefinedOn" },
{ 0x1001, 0x00E1, 0, VR::FD, VM::M1, "Depth" },
{ 0x1001, 0x00E2, 0, VR::SQ, VM::M1, "VOIBasedPlacementSettingsSequence" },
{ 0x1001, 0x00E7, 0, VR::SL, VM::M1, "VOISelected" },
{ 0x1001, 0x00E8, 0, VR::FD, VM::M1, "Margin" },
{ 0x1001, 0x00E9, 0, VR::SL, VM::M1, "SelectionMethod" },
{ 0x1001, 0x00EA, 0, VR::FD, VM::M1, "SelectionDistance" },
{ 0x1001, 0x00EB, 0, VR::FD, VM::M1, "WBTOnContourSpacing" },
{ 0x1001, 0x00EC, 0, VR::FD, VM::M1, "WBTUrethraMargin" },
{ 0x1001, 0x00ED, 0, VR::FD, VM::M1, "WBTSearchingRadiusPTV" },
{ 0x1001, 0x00EE, 0, VR::FD, VM::M1, "WBTSearchingRadiusOAR" },
{ 0x1001, 0x00EF, 0, VR::FD, VM::M3, "WBTStartingPoint" },
{ 0x1001, 0x00F0, 0, VR::FD, VM::M4, "WBTSurface" },
{ 0x1001, 0x00F1, 0, VR::FD, VM::M4, "WBTNoOfInteriorCatheters" },
{ 0x1001, 0x00F2, 0, VR::FD, VM::M4, "WBTRelativeRadius" },
{ 0x1001, 0x00F3, 0, VR::SL, VM::M1, "Sorting Method" },
};

unsigned short Dict150TagHashTable[] = {
   17,    30,    41,    54,    67,    74,    83,    88,    95,   104,
  113,   122,   131,   140,   149,   158,     0,     6,     3,   163,
    7,   179,    22,   194,    37,   210,    53,   226,    65,   242,
    5,     2,   162,     6,   178,    23,   195,    38,   211,    66,
  243,     6,     1,   161,     5,   177,    20,   192,    35,   208,
   51,   224,    63,   240,     6,     0,   160,     4,   176,    21,
  193,    36,   209,    52,   225,    64,   241,     3,    11,   183,
   25,   198,    41,   214,     4,    10,   182,    26,   199,    42,
  215,    54,   231,     2,     9,   181,    39,   212,     3,     8,
  180,    24,   197,    40,   213,     4,    15,   187,    29,   202,
   45,   218,    57,   234,     4,    14,   186,    30,   203,    46,
  219,    58,   235,     4,    13,   185,    27,   200,    43,   216,
   55,   232,     4,    12,   184,    28,   201,    44,   217,    56,
  233,     4,    19,   191,    33,   206,    49,   222,    61,   238,
    4,    18,   190,    34,   207,    50,   223,    62,   239,     4,
   17,   189,    31,   204,    47,   220,    59,   236,     4,    16,
  188,    32,   205,    48,   221,    60,   237,
};

vtkDICOMDictionary::Dict Dict150Data = {
"PRIVATE_CODE_STRING_1001",
16,
67,
Dict150TagHashTable,
Dict150Contents
};

// ----- SIEMENS MR EXTRACTED CSA HEADER -----

DictEntry Dict151Contents[] = {
{ 0x0025, 0x0001, 0, VR::SQ, VM::M1, "ExtractedMRHeaderInformationSequence" },
{ 0x0025, 0x0002, 0, VR::LO, VM::M1, "ExtractedMRHeaderCreatorIdentificationCode" },
{ 0x0025, 0x0003, 0, VR::AT, VM::M1, "ExtractedMRHeaderTag" },
};

unsigned short Dict151TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,     3,
};

vtkDICOMDictionary::Dict Dict151Data = {
"SIEMENS MR EXTRACTED CSA HEADER",
1,
3,
Dict151TagHashTable,
Dict151Contents
};

// ----- KRETZ_US -----

DictEntry Dict152Contents[] = {
{ 0x7fe1, 0x0001, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict152TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict152Data = {
"KRETZ_US",
1,
1,
Dict152TagHashTable,
Dict152Contents
};

// ----- GEIIS PACS -----

DictEntry Dict153Contents[] = {
{ 0x0903, 0x0010, 0, VR::US, VM::M1, "RejectImageFlag" },
{ 0x0903, 0x0011, 0, VR::US, VM::M1, "SignificantFlag" },
{ 0x0903, 0x0012, 0, VR::US, VM::M1, "ConfidentialFlag" },
{ 0x0903, 0x0020, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict153TagHashTable[] = {
    2,     0,     4,     0,    16,     1,    17,     2,    18,     3,
   32,
};

vtkDICOMDictionary::Dict Dict153Data = {
"GEIIS PACS",
1,
4,
Dict153TagHashTable,
Dict153Contents
};

// ----- IMS s.r.l. Mammography Private Code -----

DictEntry Dict154Contents[] = {
{ 0x1271, 0x0001, 0, VR::IS, VM::M1, "Threshold1" },
{ 0x1271, 0x0002, 0, VR::IS, VM::M1, "Threshold2" },
{ 0x1271, 0x0010, 0, VR::IS, VM::M1, "SegmentationLeftBorder" },
{ 0x1271, 0x0011, 0, VR::IS, VM::M1, "SegmentationRightBorder" },
{ 0x1271, 0x0012, 0, VR::IS, VM::M1, "SegmentationTopBorder" },
{ 0x1271, 0x0013, 0, VR::IS, VM::M1, "SegmentationBottomBorder" },
{ 0x1271, 0x0020, 0, VR::IS, VM::M1, "CompressorStatus" },
{ 0x1271, 0x0021, 0, VR::IS, VM::M1, "CollimatorType" },
{ 0x1271, 0x0022, 0, VR::IS, VM::M1, "BiopsySpecimen" },
{ 0x1271, 0x0030, 0, VR::IS, VM::M1, "PrinterSegmentation" },
{ 0x1271, 0x0031, 0, VR::IS, VM::M1, "Printer8x10Format" },
{ 0x1271, 0x0032, 0, VR::FD, VM::M1, "Printer8x10SizeX" },
{ 0x1271, 0x0033, 0, VR::FD, VM::M1, "Printer8x10SizeY" },
{ 0x1271, 0x0034, 0, VR::IS, VM::M1, "Printer8x10AreaLeftBorder" },
{ 0x1271, 0x0035, 0, VR::IS, VM::M1, "Printer8x10AreaRightBorder" },
{ 0x1271, 0x0036, 0, VR::IS, VM::M1, "Printer8x10AreaTopBorder" },
{ 0x1271, 0x0037, 0, VR::IS, VM::M1, "Printer8x10AreaBottomBorder" },
{ 0x1271, 0x0038, 0, VR::LO, VM::M1, "RotationAndInclinationSensorPresence" },
{ 0x1271, 0x0039, 0, VR::US, VM::M1TN, "WindowCenterForForProcessingImages" },
{ 0x1271, 0x0040, 0, VR::US, VM::M1TN, "WindowWidthForForProcessingImages" },
{ 0x1271, 0x0041, 0, VR::LO, VM::M1TN, "WindowCenterAndWidthExplanationForForProcessingImages" },
{ 0x1271, 0x0042, 0, VR::LT, VM::M1, "ProcessingInformation" },
{ 0x1271, 0x0043, 0, VR::LT, VM::M1, "Filename" },
{ 0x1271, 0x0044, 0, VR::LT, VM::M1, "ContrastView" },
{ 0x1271, 0x0045, 0, VR::IS, VM::M1, "Threshold3" },
{ 0x1271, 0x0046, 0, VR::IS, VM::M1, "Threshold4" },
{ 0x1271, 0x0047, 0, VR::IS, VM::M1, "Threshold5" },
{ 0x1271, 0x0048, 0, VR::IS, VM::M1, "Threshold6" },
{ 0x1271, 0x0049, 0, VR::IS, VM::M1, "Threshold7" },
{ 0x1271, 0x0050, 0, VR::IS, VM::M1, "Threshold8" },
{ 0x1271, 0x0051, 0, VR::IS, VM::M1, "Threshold9" },
{ 0x1271, 0x0052, 0, VR::IS, VM::M1, "Threshold9" },
{ 0x1271, 0x0053, 0, VR::IS, VM::M1, "ScalingFactorForProcessing" },
{ 0x1271, 0x0054, 0, VR::IS, VM::M1, "ConfirmXImage" },
{ 0x1271, 0x0055, 0, VR::IS, VM::M1, "Backgroundcounts" },
{ 0x1271, 0x0056, 0, VR::IS, VM::M1, "WLRoiAreaX" },
{ 0x1271, 0x0057, 0, VR::IS, VM::M1, "WLRoiAreaY" },
{ 0x1271, 0x0060, 0, VR::IS, VM::M1, "SecondProcessingImage" },
{ 0x1271, 0x0061, 0, VR::IS, VM::M1, "SFilter" },
{ 0x1271, 0x0062, 0, VR::IS, VM::M1, "UFilter" },
{ 0x1271, 0x0063, 0, VR::IS, VM::M1, "Anonymous" },
{ 0x1271, 0x0070, 0, VR::IS, VM::M1, "TomoSAD" },
{ 0x1271, 0x0071, 0, VR::IS, VM::M1, "TomoDetectorYAW" },
{ 0x1271, 0x0072, 0, VR::IS, VM::M1, "TomoDetectorPitch" },
{ 0x1271, 0x0073, 0, VR::IS, VM::M1, "TomoDetectorRoll" },
{ 0x1271, 0x0074, 0, VR::IS, VM::M1, "TomoFocalSpotX" },
{ 0x1271, 0x0075, 0, VR::IS, VM::M1, "TomoFocalSpotY" },
{ 0x1271, 0x0076, 0, VR::IS, VM::M1, "TomoXrayStartAngle" },
{ 0x1271, 0x0077, 0, VR::IS, VM::M1, "TomoXrayEndAngle" },
{ 0x1271, 0x0078, 0, VR::IS, VM::M1, "TomoXrayAngle" },
{ 0x1271, 0x0079, 0, VR::IS, VM::M1, "TomoExposureCounter" },
{ 0x1271, 0x0080, 0, VR::IS, VM::M1, "TomoExposureNumber" },
{ 0x1271, 0x0081, 0, VR::IS, VM::M1, "TomoWLModified" },
{ 0x1271, 0x0082, 0, VR::IS, VM::M1, "TomoProjection" },
{ 0x1271, 0x0083, 0, VR::IS, VM::M1, "KeyObjectSelectionTitleCode" },
{ 0x1271, 0x0084, 0, VR::IS, VM::M1, "RejectedForQualityReasonsCode" },
{ 0x1271, 0x0085, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict154TagHashTable[] = {
   15,    26,    35,    46,    59,    66,    71,    78,    85,    92,
   99,   112,   125,   134,     0,     5,     2,    16,     8,    34,
   13,    52,    24,    69,    36,    87,     4,     3,    17,    14,
   53,    23,    68,    35,    86,     5,     4,    18,    15,    54,
   17,    56,    26,    71,    28,    73,     6,     0,     1,     5,
   19,    16,    55,    18,    57,    25,    70,    27,    72,     3,
    1,     2,    42,   113,    53,   130,     2,    41,   112,    54,
  131,     3,    38,    97,    44,   115,    51,   128,     3,    37,
   96,    43,   114,    52,   129,     3,    30,    81,    40,    99,
   46,   117,     3,    29,    80,    39,    98,    45,   116,     6,
    9,    48,    20,    65,    32,    83,    48,   119,    50,   121,
   55,   132,     6,    10,    49,    19,    64,    31,    82,    47,
  118,    49,   120,    56,   133,     4,     6,    32,    11,    50,
   22,    67,    34,    85,     4,     7,    33,    12,    51,    21,
   66,    33,    84,
};

vtkDICOMDictionary::Dict Dict154Data = {
"IMS s.r.l. Mammography Private Code",
14,
57,
Dict154TagHashTable,
Dict154Contents
};

// ----- PRIVATE_CODE_STRING_0021 -----

DictEntry Dict155Contents[] = {
{ 0x0021, 0x0070, 0, VR::FD, VM::M1, "DistanceBasePlaneToTemplate" },
{ 0x0021, 0x0071, 0, VR::FD, VM::M16, "VolumeToPatientMatrix" },
{ 0x0021, 0x0072, 0, VR::FD, VM::M16, "PatientToWorldMatrix" },
{ 0x0021, 0x0073, 0, VR::SL, VM::M1, "BasePlane" },
{ 0x0021, 0x0074, 0, VR::SL, VM::M1, "ReferencePlane" },
{ 0x0021, 0x0075, 0, VR::SL, VM::M1, "ApexPlane" },
{ 0x0021, 0x0076, 0, VR::FD, VM::M1, "BasePlaneOffset" },
};

unsigned short Dict155TagHashTable[] = {
    2,     0,     7,     0,   112,     1,   113,     2,   114,     3,
  115,     4,   116,     5,   117,     6,   118,
};

vtkDICOMDictionary::Dict Dict155Data = {
"PRIVATE_CODE_STRING_0021",
1,
7,
Dict155TagHashTable,
Dict155Contents
};

// ----- SIEMENS CT VA0  IDE -----

DictEntry Dict156Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0030, 0, VR::CS, VM::M1, "" },
{ 0x0009, 0x0031, 0, VR::SH, VM::M1, "" },
{ 0x0009, 0x0032, 0, VR::SH, VM::M1, "" },
{ 0x0009, 0x0034, 0, VR::SH, VM::M1, "" },
{ 0x0009, 0x0040, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0042, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0050, 0, VR::DA, VM::M1, "" },
{ 0x0009, 0x0051, 0, VR::TM, VM::M1, "" },
};

unsigned short Dict156TagHashTable[] = {
    3,    12,     0,     4,     2,    49,     5,    64,     6,    66,
    7,    80,     5,     0,    16,     1,    48,     3,    50,     4,
   52,     8,    81,
};

vtkDICOMDictionary::Dict Dict156Data = {
"SIEMENS CT VA0  IDE",
2,
9,
Dict156TagHashTable,
Dict156Contents
};

// ----- SCHICK TECHNOLOGIES - Note List Creator ID -----

DictEntry Dict157Contents[] = {
{ 0x0021, 0x0001, 0, VR::UI, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict157TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     2,
};

vtkDICOMDictionary::Dict Dict157Data = {
"SCHICK TECHNOLOGIES - Note List Creator ID",
1,
2,
Dict157TagHashTable,
Dict157Contents
};

// ----- Mortara_Inc -----

DictEntry Dict158Contents[] = {
{ 0x1455, 0x0000, 0, VR::OW, VM::M1, "ELIInterpretationVector" },
{ 0x1455, 0x0001, 0, VR::UN, VM::M1, "CustomID" },
{ 0x1455, 0x0002, 0, VR::UT, VM::M1, "Race" },
{ 0x1455, 0x0003, 0, VR::UT, VM::M1, "SocialSecurityNumber" },
{ 0x1455, 0x0004, 0, VR::UT, VM::M1, "AttendingPhysician" },
{ 0x1455, 0x0005, 0, VR::UT, VM::M1, "ProceduralDiagnosis" },
{ 0x1455, 0x0006, 0, VR::UT, VM::M1, "Note1" },
{ 0x1455, 0x0007, 0, VR::UT, VM::M1, "Note2" },
{ 0x1455, 0x0008, 0, VR::LO, VM::M1, "OrderRequestNumber" },
{ 0x1455, 0x0010, 0, VR::LO, VM::M1, "ManufacturerName" },
};

unsigned short Dict158TagHashTable[] = {
    3,    16,     0,     6,     0,     0,     2,     2,     4,     4,
    6,     6,     8,     8,     9,    16,     4,     1,     1,     3,
    3,     5,     5,     7,     7,
};

vtkDICOMDictionary::Dict Dict158Data = {
"Mortara_Inc",
2,
10,
Dict158TagHashTable,
Dict158Contents
};

// ----- SIEMENS IKM CKS LUNGCAD BMK -----

DictEntry Dict159Contents[] = {
{ 0x0029, 0x0001, 0, VR::UT, VM::M1, "" },
};

unsigned short Dict159TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict159Data = {
"SIEMENS IKM CKS LUNGCAD BMK",
1,
1,
Dict159TagHashTable,
Dict159Contents
};

// ----- APEX_PRIVATE -----

DictEntry Dict160Contents[] = {
{ 0x0027, 0x0011, 0, VR::DS, VM::M1, "BedPosition" },
};

unsigned short Dict160TagHashTable[] = {
    2,     0,     1,     0,    17,
};

vtkDICOMDictionary::Dict Dict160Data = {
"APEX_PRIVATE",
1,
1,
Dict160TagHashTable,
Dict160Contents
};

// ----- PRIVATE_CODE_STRING_0019 -----

DictEntry Dict161Contents[] = {
{ 0x0019, 0x0000, 0, VR::FD, VM::M1, "Calibration" },
{ 0x0019, 0x0001, 0, VR::FD, VM::M1, "DepthConversion" },
{ 0x0019, 0x0002, 0, VR::FD, VM::M1, "Stepsize" },
{ 0x0019, 0x0003, 0, VR::SL, VM::M1TN, "Warning" },
{ 0x0019, 0x0004, 0, VR::ST, VM::M1, "DataID" },
};

unsigned short Dict161TagHashTable[] = {
    2,     0,     5,     0,     0,     1,     1,     2,     2,     3,
    3,     4,     4,
};

vtkDICOMDictionary::Dict Dict161Data = {
"PRIVATE_CODE_STRING_0019",
1,
5,
Dict161TagHashTable,
Dict161Contents
};

// ----- GEMS_IMAG_01 -----

DictEntry Dict162Contents[] = {
{ 0x0027, 0x0006, 0, VR::SL, VM::M1, "ImageArchiveFlag" },
{ 0x0027, 0x0010, 0, VR::SS, VM::M1, "ScoutType" },
{ 0x0027, 0x001c, 0, VR::SL, VM::M1, "VmaMamp" },
{ 0x0027, 0x001d, 0, VR::SS, VM::M1, "VmaPhase" },
{ 0x0027, 0x001e, 0, VR::SL, VM::M1, "VmaMod" },
{ 0x0027, 0x001f, 0, VR::SL, VM::M1, "VmaClip" },
{ 0x0027, 0x0020, 0, VR::SS, VM::M1, "SmartScanOnOffFlag" },
{ 0x0027, 0x0030, 0, VR::SH, VM::M1, "ForeignImageRevision" },
{ 0x0027, 0x0031, 0, VR::SS, VM::M1, "ImagingMode" },
{ 0x0027, 0x0032, 0, VR::SS, VM::M1, "PulseSequence" },
{ 0x0027, 0x0033, 0, VR::SL, VM::M1, "ImagingOptions" },
{ 0x0027, 0x0035, 0, VR::SS, VM::M1, "PlaneType" },
{ 0x0027, 0x0036, 0, VR::SL, VM::M1, "ObliquePlane" },
{ 0x0027, 0x0040, 0, VR::SH, VM::M1, "RASLetterOfImageLocation" },
{ 0x0027, 0x0041, 0, VR::FL, VM::M1, "ImageLocation" },
{ 0x0027, 0x0042, 0, VR::FL, VM::M1, "CenterRCoordOfPlaneImage" },
{ 0x0027, 0x0043, 0, VR::FL, VM::M1, "CenterACoordOfPlaneImage" },
{ 0x0027, 0x0044, 0, VR::FL, VM::M1, "CenterSCoordOfPlaneImage" },
{ 0x0027, 0x0045, 0, VR::FL, VM::M1, "NormalRCoord" },
{ 0x0027, 0x0046, 0, VR::FL, VM::M1, "NormalACoord" },
{ 0x0027, 0x0047, 0, VR::FL, VM::M1, "NormalSCoord" },
{ 0x0027, 0x0048, 0, VR::FL, VM::M1, "RCoordOfTopRightCorner" },
{ 0x0027, 0x0049, 0, VR::FL, VM::M1, "ACoordOfTopRightCorner" },
{ 0x0027, 0x004a, 0, VR::FL, VM::M1, "SCoordOfTopRightCorner" },
{ 0x0027, 0x004b, 0, VR::FL, VM::M1, "RCoordOfBottomRightCorner" },
{ 0x0027, 0x004c, 0, VR::FL, VM::M1, "ACoordOfBottomRightCorner" },
{ 0x0027, 0x004d, 0, VR::FL, VM::M1, "SCoordOfBottomRightCorner" },
{ 0x0027, 0x0050, 0, VR::FL, VM::M1, "TableStartLocation" },
{ 0x0027, 0x0051, 0, VR::FL, VM::M1, "TableEndLocation" },
{ 0x0027, 0x0052, 0, VR::SH, VM::M1, "RASLetterForSideOfImage" },
{ 0x0027, 0x0053, 0, VR::SH, VM::M1, "RASLetterForAnteriorPosterior" },
{ 0x0027, 0x0054, 0, VR::SH, VM::M1, "RASLetterForScoutStartLoc" },
{ 0x0027, 0x0055, 0, VR::SH, VM::M1, "RASLetterForScoutEndLoc" },
{ 0x0027, 0x0060, 0, VR::FL, VM::M1, "ImageDimensionX" },
{ 0x0027, 0x0061, 0, VR::FL, VM::M1, "ImageDimensionY" },
{ 0x0027, 0x0062, 0, VR::FL, VM::M1, "NumberOfExcitations" },
};

unsigned short Dict162TagHashTable[] = {
   10,    19,    28,    39,    48,    55,    62,    69,    80,     0,
    4,    11,    53,    18,    69,    23,    74,    30,    83,     4,
    1,    16,    15,    66,    24,    75,    27,    80,     5,     5,
   31,    10,    51,    16,    67,    21,    72,    28,    81,     4,
    4,    30,     9,    50,    13,    64,    22,    73,     3,     3,
   29,     8,    49,    14,    65,     3,     2,    28,     7,    48,
   35,    98,     3,     0,     6,    19,    70,    31,    84,     5,
    6,    32,    20,    71,    25,    76,    32,    85,    33,    96,
    5,    12,    54,    17,    68,    26,    77,    29,    82,    34,
   97,
};

vtkDICOMDictionary::Dict Dict162Data = {
"GEMS_IMAG_01",
9,
36,
Dict162TagHashTable,
Dict162Contents
};

// ----- Silhouette ROI V1.0 -----

DictEntry Dict163Contents[] = {
{ 0x0029, 0x0011, 0, VR::IS, VM::M1, "ROIName" },
{ 0x0029, 0x0012, 0, VR::LT, VM::M1, "ROINameFont" },
{ 0x0029, 0x0013, 0, VR::LT, VM::M1, "ROINormalColor" },
{ 0x0029, 0x0014, 0, VR::UL, VM::M1, "ROIFillPattern" },
{ 0x0029, 0x0015, 0, VR::UL, VM::M1, "ROIBpSeg" },
{ 0x0029, 0x0016, 0, VR::UN, VM::M1, "ROIBpSegPairs" },
{ 0x0029, 0x0017, 0, VR::UL, VM::M1, "ROISeedSpace" },
{ 0x0029, 0x0018, 0, VR::UN, VM::M1, "ROISeeds" },
{ 0x0029, 0x0019, 0, VR::UL, VM::M1, "ROILineThickness" },
{ 0x0029, 0x0020, 0, VR::UL, VM::M1, "ROILineStyle" },
{ 0x0029, 0x0021, 0, VR::UL, VM::M1, "ROILineDashLength" },
{ 0x0029, 0x0022, 0, VR::UL, VM::M1, "ROIInteractivity" },
{ 0x0029, 0x0023, 0, VR::UL, VM::M1, "ROINamePosition" },
{ 0x0029, 0x0024, 0, VR::UL, VM::M1, "ROINameDisplay" },
{ 0x0029, 0x0025, 0, VR::LT, VM::M1, "ROILabel" },
{ 0x0029, 0x0026, 0, VR::UL, VM::M1, "ROIShape" },
{ 0x0029, 0x0027, 0, VR::FD, VM::M1, "ROIShapeTilt" },
{ 0x0029, 0x0028, 0, VR::UL, VM::M1, "ROIShapePointsCount" },
{ 0x0029, 0x0029, 0, VR::UL, VM::M1, "ROIShapePointsSpace" },
{ 0x0029, 0x0030, 0, VR::FD, VM::M1, "ROIShapePoints" },
{ 0x0029, 0x0031, 0, VR::UL, VM::M1, "ROIShapeControlPointsCount" },
{ 0x0029, 0x0032, 0, VR::UL, VM::M1, "ROIShapeControlPointsSpace" },
{ 0x0029, 0x0033, 0, VR::FD, VM::M1, "ROIShapeControlPoints" },
{ 0x0029, 0x0034, 0, VR::UL, VM::M1, "ROIDontSave" },
};

unsigned short Dict163TagHashTable[] = {
    7,    18,    29,    40,    49,    54,     0,     5,     4,    21,
    8,    25,    14,    37,    18,    41,    20,    49,     5,     3,
   20,     7,    24,    13,    36,    17,    40,    19,    48,     5,
    0,    17,     6,    23,    10,    33,    16,    39,    22,    51,
    4,     5,    22,     9,    32,    15,    38,    21,    50,     2,
    2,    19,    12,    35,     3,     1,    18,    11,    34,    23,
   52,
};

vtkDICOMDictionary::Dict Dict163Data = {
"Silhouette ROI V1.0",
6,
24,
Dict163TagHashTable,
Dict163Contents
};

// ----- DZDICOM 4.3.0 -----

DictEntry Dict164Contents[] = {
{ 0x0009, 0x0001, 0, VR::UI, VM::M1, "" },
{ 0x0009, 0x0002, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0004, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0005, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0007, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0008, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0011, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0012, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0013, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0014, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0015, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0016, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0017, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0070, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0071, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0072, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0074, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x007a, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x00a1, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x00a2, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x00f1, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x00f7, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x00f9, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict164TagHashTable[] = {
    7,    18,    31,    42,    49,    56,     0,     5,     4,     5,
    8,    17,    14,    23,    15,   112,    19,   122,     6,     3,
    4,     7,     8,    13,    22,    16,   113,    21,   162,    23,
  247,     5,     0,     1,     6,     7,    10,    19,    17,   114,
   20,   161,     3,     5,     6,     9,    18,    24,   249,     3,
    2,     3,    12,    21,    18,   116,     3,     1,     2,    11,
   20,    22,   241,
};

vtkDICOMDictionary::Dict Dict164Data = {
"DZDICOM 4.3.0",
6,
25,
Dict164TagHashTable,
Dict164Contents
};

// ----- SIEMENS SERIES SHADOW ATTRIBUTES -----

DictEntry Dict165Contents[] = {
{ 0x0021, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0003, 0, VR::OB, VM::M1, "" },
{ 0x0021, 0x0004, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0005, 0, VR::IS, VM::M1TN, "" },
{ 0x0021, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0007, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0008, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0009, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x000a, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x000c, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x000d, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x000f, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0011, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0012, 0, VR::FD, VM::M1, "" },
{ 0x0021, 0x0013, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0014, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0016, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0017, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0018, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0019, 0, VR::OB, VM::M1, "" },
{ 0x0021, 0x001a, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x001b, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x001c, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x001d, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x001f, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0022, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0023, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0025, 0, VR::SL, VM::M1TN, "" },
{ 0x0021, 0x0026, 0, VR::IS, VM::M1TN, "" },
{ 0x0021, 0x0027, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x002a, 0, VR::IS, VM::M1TN, "" },
{ 0x0021, 0x002b, 0, VR::ST, VM::M1, "" },
{ 0x0021, 0x002c, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x002d, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x002e, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x002f, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0030, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0031, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0032, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0033, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0034, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0035, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0036, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0038, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x003b, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict165TagHashTable[] = {
   12,    19,    30,    41,    52,    65,    74,    85,    96,   101,
  106,     0,     3,    11,    13,    18,    22,    32,    42,     5,
    2,     3,    10,    12,    21,    25,    35,    45,    44,    54,
    5,     1,     2,    12,    15,    20,    24,    28,    35,    34,
   44,     5,     4,     5,    23,    27,    27,    34,    37,    47,
   45,    56,     6,     3,     4,    14,    17,    22,    26,    29,
   37,    36,    46,    46,    59,     4,     6,     7,    13,    16,
   25,    29,    39,    49,     5,     5,     6,    16,    19,    24,
   28,    31,    39,    38,    48,     5,     8,     9,    15,    18,
   26,    31,    30,    38,    41,    51,     2,     7,     8,    40,
   50,     2,    17,    20,    43,    53,     5,     0,     1,     9,
   10,    19,    23,    33,    43,    42,    52,
};

vtkDICOMDictionary::Dict Dict165Data = {
"SIEMENS SERIES SHADOW ATTRIBUTES",
11,
47,
Dict165TagHashTable,
Dict165Contents
};

// ----- HOLOGIC, Inc. -----

DictEntry Dict166Contents[] = {
{ 0x0019, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0004, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::LO, VM::M1, "PaddleID" },
{ 0x0019, 0x0007, 0, VR::SH, VM::M1, "PaddlePosition" },
{ 0x0019, 0x0008, 0, VR::LO, VM::M1, "CollimationSize" },
{ 0x0019, 0x0016, 0, VR::DS, VM::M1, "PaddleAngle" },
{ 0x0019, 0x0025, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::LO, VM::M1, "PaddleIDDescription" },
{ 0x0019, 0x0027, 0, VR::SH, VM::M1, "PaddlePositionDescription" },
{ 0x0019, 0x0028, 0, VR::LO, VM::M1, "CollimationSizeDescription" },
{ 0x0019, 0x0029, 0, VR::LO, VM::M1, "AECUserDensityScaleFactorDescription" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "AECUserDensityScaleFactor" },
{ 0x0019, 0x0031, 0, VR::US, VM::M1, "AECSystemDensityScaleFactor" },
{ 0x0019, 0x0032, 0, VR::US, VM::M1, "AECCalculatedmAs" },
{ 0x0019, 0x0033, 0, VR::US, VM::M1, "AECAutoPixel1" },
{ 0x0019, 0x0034, 0, VR::US, VM::M1, "AECAutoPixel2" },
{ 0x0019, 0x0035, 0, VR::US, VM::M1, "AECSensor" },
{ 0x0019, 0x0037, 0, VR::LO, VM::M1, "NPTMode" },
{ 0x0019, 0x0040, 0, VR::DS, VM::M1, "SkinEdge" },
{ 0x0019, 0x0041, 0, VR::DS, VM::M1, "ExposureIndex" },
{ 0x0019, 0x0042, 0, VR::IS, VM::M1, "ExposureIndexTarget" },
{ 0x0019, 0x0043, 0, VR::DS, VM::M1, "ShortIndexRatio" },
{ 0x0019, 0x0044, 0, VR::DS, VM::M1, "ScoutkVp" },
{ 0x0019, 0x0045, 0, VR::IS, VM::M1, "ScoutmA" },
{ 0x0019, 0x0046, 0, VR::IS, VM::M1, "ScoutmAs" },
{ 0x0019, 0x0050, 0, VR::DS, VM::M1, "DisplayMinimumOD" },
{ 0x0019, 0x0051, 0, VR::DS, VM::M1, "DispalyMaximumOD" },
{ 0x0019, 0x0052, 0, VR::IS, VM::M1, "DisplayMinimumNits" },
{ 0x0019, 0x0053, 0, VR::IS, VM::M1, "DisplayMaximumNits" },
{ 0x0019, 0x0060, 0, VR::LT, VM::M1, "GeometryCalibration" },
{ 0x0019, 0x0061, 0, VR::OB, VM::M1, "ThreeDIPParameters" },
{ 0x0019, 0x0062, 0, VR::LT, VM::M1, "TwoDIPParameters" },
{ 0x0019, 0x0070, 0, VR::LO, VM::M1, "FrameOfReferenceID" },
{ 0x0019, 0x0071, 0, VR::CS, VM::M1, "PairedPosition" },
{ 0x0019, 0x0080, 0, VR::SH, VM::M1, "DetectorImageOffset" },
{ 0x0019, 0x0085, 0, VR::SH, VM::M1, "ImageSource" },
{ 0x0019, 0x0087, 0, VR::LO, VM::M1, "MarkerText" },
{ 0x0019, 0x0088, 0, VR::LO, VM::M1, "MarkerTechInitials" },
{ 0x0019, 0x0089, 0, VR::DS, VM::M2, "MarkerLocation" },
{ 0x0019, 0x008A, 0, VR::SQ, VM::M2, "MarkerSequence" },
{ 0x0019, 0x0090, 0, VR::DS, VM::M1, "ConventionalTomoAngle" },
{ 0x0019, 0x0097, 0, VR::SH, VM::M1, "MarkersBurnedIntoImage" },
{ 0x0019, 0x0098, 0, VR::LO, VM::M1, "GridLineCorrection" },
{ 0x7e01, 0x0001, 0, VR::LO, VM::M1, "CodecVersion" },
{ 0x7e01, 0x0002, 0, VR::SH, VM::M1, "CodecContentType" },
{ 0x7e01, 0x0010, 0, VR::SQ, VM::M1, "HighResolutionDataSeqence" },
{ 0x7e01, 0x0011, 0, VR::SQ, VM::M1, "LowResolutionDataSeqence" },
{ 0x7e01, 0x0012, 0, VR::OB, VM::M1, "CodecContent" },
{ 0x7f01, 0x0001, 0, VR::LO, VM::M1, "CodecVersion" },
{ 0x7f01, 0x0002, 0, VR::SH, VM::M1, "CodecContentType" },
{ 0x7f01, 0x0010, 0, VR::SQ, VM::M1, "HighResolutionDataSeqence" },
{ 0x7f01, 0x0011, 0, VR::SQ, VM::M1, "LowResolutionDataSeqence" },
{ 0x7f01, 0x0012, 0, VR::OB, VM::M1, "CodecContent" },
};

unsigned short Dict166TagHashTable[] = {
   14,    27,    38,    49,    62,    73,    82,    87,    92,   101,
  108,   121,   132,     0,     6,     2,     3,    23,    67,    34,
  112,    38,   135,    45,     1,    49,    18,     5,     1,     2,
   14,    49,    24,    68,    35,   113,    44,   152,     5,     7,
   22,    13,    48,    25,    69,    37,   133,    41,   138,     6,
    3,     4,    16,    51,    26,    70,    31,    96,    40,   137,
   46,     2,     5,     5,     7,     6,     8,    15,    50,    32,
   97,    39,   136,     4,     4,     6,    18,    53,    33,    98,
   53,    17,     2,    17,    52,    52,    16,     2,    19,    55,
   27,    80,     4,     8,    37,    28,    81,    50,     1,    54,
   18,     3,    12,    41,    29,    82,    42,   144,     6,    10,
   39,    11,    40,    20,    64,    30,    83,    43,   151,    48,
   17,     5,     0,     1,     9,    38,    21,    65,    47,    16,
   51,     2,     2,    22,    66,    36,   128,
};

vtkDICOMDictionary::Dict Dict166Data = {
"HOLOGIC, Inc.",
13,
55,
Dict166TagHashTable,
Dict166Contents
};

// ----- AMI StudyExtensions_01 -----

DictEntry Dict167Contents[] = {
{ 0x3111, 0x0001, 0, VR::UL, VM::M1, "Last Released Annot Label" },
};

unsigned short Dict167TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict167Data = {
"AMI StudyExtensions_01",
1,
1,
Dict167TagHashTable,
Dict167Contents
};

// ----- SPI-P-Private-DCI Release 1 -----

DictEntry Dict168Contents[] = {
{ 0x0019, 0x0010, 0, VR::UN, VM::M1, "ECGTimeMapDataBitsAllocated" },
{ 0x0019, 0x0011, 0, VR::UN, VM::M1, "ECGTimeMapDataBitsStored" },
{ 0x0019, 0x0012, 0, VR::UN, VM::M1, "ECGTimeMapDataHighBit" },
{ 0x0019, 0x0013, 0, VR::UN, VM::M1, "ECGTimeMapDataRepresentation" },
{ 0x0019, 0x0014, 0, VR::UN, VM::M1, "ECGTimeMapDataSmallestDataValue" },
{ 0x0019, 0x0015, 0, VR::UN, VM::M1, "ECGTimeMapDataLargestDataValue" },
{ 0x0019, 0x0016, 0, VR::UN, VM::M1, "ECGTimeMapDataNumberOfDataValues" },
{ 0x0019, 0x0017, 0, VR::UN, VM::M1, "ECGTimeMapData" },
};

unsigned short Dict168TagHashTable[] = {
    3,    12,     0,     4,     1,    17,     3,    19,     5,    21,
    7,    23,     4,     0,    16,     2,    18,     4,    20,     6,
   22,
};

vtkDICOMDictionary::Dict Dict168Data = {
"SPI-P-Private-DCI Release 1",
2,
8,
Dict168TagHashTable,
Dict168Contents
};

// ----- GEMS_FALCON_03 -----

DictEntry Dict169Contents[] = {
{ 0x0045, 0x0055, 0, VR::DS, VM::M8, "A_Coefficients" },
{ 0x0045, 0x0062, 0, VR::IS, VM::M1, "UserWindowCenter" },
{ 0x0045, 0x0063, 0, VR::IS, VM::M1, "UserWindowWidth" },
{ 0x0045, 0x0065, 0, VR::IS, VM::M1, "RequestedDetectorEntranceDose" },
{ 0x0045, 0x0067, 0, VR::DS, VM::M3, "VOILUTAssymmetryParameterBeta" },
{ 0x0045, 0x0069, 0, VR::IS, VM::M1, "CollimatorRotation" },
{ 0x0045, 0x0072, 0, VR::IS, VM::M1, "CollimatorWidth" },
{ 0x0045, 0x0073, 0, VR::IS, VM::M1, "CollimatorHeight" },
};

unsigned short Dict169TagHashTable[] = {
    3,    16,     0,     6,     0,    85,     2,    99,     3,   101,
    4,   103,     5,   105,     7,   115,     2,     1,    98,     6,
  114,
};

vtkDICOMDictionary::Dict Dict169Data = {
"GEMS_FALCON_03",
2,
8,
Dict169TagHashTable,
Dict169Contents
};

// ----- SIEMENS CM VA0  CMS -----

DictEntry Dict170Contents[] = {
{ 0x0009, 0x0000, 0, VR::DS, VM::M1, "NumberOfMeasurements" },
{ 0x0009, 0x0010, 0, VR::CS, VM::M1, "StorageMode" },
{ 0x0009, 0x0012, 0, VR::UL, VM::M1, "EvaluationMaskImage" },
{ 0x0009, 0x0026, 0, VR::DA, VM::M1, "LastMoveDate" },
{ 0x0009, 0x0027, 0, VR::TM, VM::M1, "LastMoveTime" },
{ 0x0011, 0x000a, 0, VR::LO, VM::M1, "" },
{ 0x0011, 0x0010, 0, VR::DA, VM::M1, "RegistrationDate" },
{ 0x0011, 0x0011, 0, VR::TM, VM::M1, "RegistrationTime" },
{ 0x0011, 0x0022, 0, VR::LO, VM::M1, "" },
{ 0x0011, 0x0023, 0, VR::DS, VM::M1, "UsedPatientWeight" },
{ 0x0011, 0x0040, 0, VR::IS, VM::M1, "OrganCode" },
{ 0x0013, 0x0000, 0, VR::PN, VM::M1, "ModifyingPhysician" },
{ 0x0013, 0x0010, 0, VR::DA, VM::M1, "ModificationDate" },
{ 0x0013, 0x0012, 0, VR::TM, VM::M1, "ModificationTime" },
{ 0x0013, 0x0020, 0, VR::PN, VM::M1, "PatientName" },
{ 0x0013, 0x0022, 0, VR::LO, VM::M1, "PatientId" },
{ 0x0013, 0x0030, 0, VR::DA, VM::M1, "PatientBirthdate" },
{ 0x0013, 0x0031, 0, VR::DS, VM::M1, "PatientWeight" },
{ 0x0013, 0x0032, 0, VR::LO, VM::M1, "PatientsMaidenName" },
{ 0x0013, 0x0033, 0, VR::LO, VM::M1, "ReferringPhysician" },
{ 0x0013, 0x0034, 0, VR::LO, VM::M1, "AdmittingDiagnosis" },
{ 0x0013, 0x0035, 0, VR::LO, VM::M1, "PatientSex" },
{ 0x0013, 0x0040, 0, VR::LO, VM::M1, "ProcedureDescription" },
{ 0x0013, 0x0042, 0, VR::LO, VM::M1, "PatientRestDirection" },
{ 0x0013, 0x0044, 0, VR::LO, VM::M1, "PatientPosition" },
{ 0x0013, 0x0046, 0, VR::LO, VM::M1, "ViewDirection" },
{ 0x0013, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x0013, 0x0051, 0, VR::LO, VM::M1, "" },
{ 0x0013, 0x0052, 0, VR::LO, VM::M1, "" },
{ 0x0013, 0x0053, 0, VR::LO, VM::M1, "" },
{ 0x0013, 0x0054, 0, VR::LO, VM::M1, "" },
{ 0x0013, 0x0055, 0, VR::LO, VM::M1, "" },
{ 0x0013, 0x0056, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0010, 0, VR::IS, VM::M1, "NetFrequency" },
{ 0x0019, 0x0020, 0, VR::CS, VM::M1, "MeasurementMode" },
{ 0x0019, 0x0030, 0, VR::CS, VM::M1, "CalculationMode" },
{ 0x0019, 0x0050, 0, VR::IS, VM::M1, "NoiseLevel" },
{ 0x0019, 0x0060, 0, VR::IS, VM::M1, "NumberOfDataBytes" },
{ 0x0019, 0x0070, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0080, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::DS, VM::M2, "FoV" },
{ 0x0021, 0x0022, 0, VR::DS, VM::M1, "ImageMagnificationFactor" },
{ 0x0021, 0x0024, 0, VR::DS, VM::M2, "ImageScrollOffset" },
{ 0x0021, 0x0026, 0, VR::IS, VM::M1, "ImagePixelOffset" },
{ 0x0021, 0x0030, 0, VR::CS, VM::M1, "ViewDirection" },
{ 0x0021, 0x0032, 0, VR::CS, VM::M1, "PatientRestDirection" },
{ 0x0021, 0x0060, 0, VR::DS, VM::M3, "ImagePosition" },
{ 0x0021, 0x0061, 0, VR::DS, VM::M3, "ImageNormal" },
{ 0x0021, 0x0063, 0, VR::DS, VM::M1, "ImageDistance" },
{ 0x0021, 0x0065, 0, VR::US, VM::M1, "ImagePositioningHistoryMask" },
{ 0x0021, 0x006a, 0, VR::DS, VM::M3, "ImageRow" },
{ 0x0021, 0x006b, 0, VR::DS, VM::M3, "ImageColumn" },
{ 0x0021, 0x0070, 0, VR::CS, VM::M3, "PatientOrientationSet1" },
{ 0x0021, 0x0071, 0, VR::CS, VM::M3, "PatientOrientationSet2" },
{ 0x0021, 0x0080, 0, VR::LO, VM::M1, "StudyName" },
{ 0x0021, 0x0082, 0, VR::SH, VM::M3, "StudyType" },
{ 0x0029, 0x0010, 0, VR::CS, VM::M1, "WindowStyle" },
{ 0x0029, 0x0011, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0013, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::CS, VM::M3, "PixelQualityCode" },
{ 0x0029, 0x0022, 0, VR::IS, VM::M3, "PixelQualityValue" },
{ 0x0029, 0x0050, 0, VR::CS, VM::M1, "ArchiveCode" },
{ 0x0029, 0x0051, 0, VR::CS, VM::M1, "ExposureCode" },
{ 0x0029, 0x0052, 0, VR::IS, VM::M1, "SortCode" },
{ 0x0029, 0x0053, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0060, 0, VR::LO, VM::M1, "Splash" },
{ 0x0051, 0x0010, 0, VR::LO, VM::M1TN, "ImageText" },
{ 0x6021, 0x0000, 0, VR::LO, VM::M1, "ImageGraphicsFormatCode" },
{ 0x6021, 0x0010, 0, VR::LO, VM::M1, "ImageGraphics" },
{ 0x7fe1, 0x0000, 0, VR::OB, VM::M1TN, "BinaryData" },
};

unsigned short Dict170TagHashTable[] = {
   18,    31,    48,    63,    76,    85,    92,    99,   108,   113,
  120,   127,   130,   139,   150,   157,   164,     0,     6,     7,
   17,     8,    34,    14,    32,    17,    49,    32,    86,    44,
   48,     8,     6,    16,    13,    18,    16,    48,    24,    68,
   37,    96,    40,    32,    49,   101,    61,    80,     7,    11,
    0,    30,    84,    38,   112,    39,   128,    45,    50,    62,
   81,    68,    16,     6,    12,    16,    31,    85,    41,    34,
   63,    82,    67,     0,    69,     0,     4,    21,    53,    36,
   80,    64,    83,    65,    96,     3,    20,    52,    42,    36,
   57,    17,     3,    34,    32,    50,   106,    56,    16,     4,
   35,    48,    43,    38,    51,   107,    58,    19,     2,     1,
   16,    55,   130,     3,     0,     0,    33,    16,    59,    32,
    3,     2,    18,     5,    10,    54,   128,     1,    60,    34,
    4,     4,    39,    10,    64,    23,    66,    52,   112,     5,
    3,    38,    28,    82,    46,    96,    53,   113,    66,    16,
    3,    22,    64,    29,    83,    47,    97,     3,    15,    34,
   19,    51,    26,    80,     5,     9,    35,    18,    50,    25,
   70,    27,    81,    48,    99,
};

vtkDICOMDictionary::Dict Dict170Data = {
"SIEMENS CM VA0  CMS",
17,
70,
Dict170TagHashTable,
Dict170Contents
};

// ----- PHILIPS MR/PART 7 -----

DictEntry Dict171Contents[] = {
{ 0x0019, 0x0000, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict171TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict171Data = {
"PHILIPS MR/PART 7",
1,
1,
Dict171TagHashTable,
Dict171Contents
};

// ----- PHILIPS MR/PART 6 -----

DictEntry Dict172Contents[] = {
{ 0x0019, 0x0010, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict172TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict172Data = {
"PHILIPS MR/PART 6",
1,
1,
Dict172TagHashTable,
Dict172Contents
};

// ----- PHILIPS MR/PART -----

DictEntry Dict173Contents[] = {
{ 0x0019, 0x0000, 0, VR::IS, VM::M1, "NumberOfStacks" },
{ 0x0019, 0x0001, 0, VR::IS, VM::M1TN, "StackType" },
{ 0x0019, 0x0002, 0, VR::IS, VM::M1TN, "" },
{ 0x0019, 0x0003, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::DS, VM::M1, "CCAngulation" },
{ 0x0019, 0x0006, 0, VR::DS, VM::M1, "APAngulation" },
{ 0x0019, 0x0007, 0, VR::DS, VM::M1, "LRAngulation" },
{ 0x0019, 0x0008, 0, VR::IS, VM::M1, "PatientPosition" },
{ 0x0019, 0x0009, 0, VR::IS, VM::M1, "PatientOrientation" },
{ 0x0019, 0x000a, 0, VR::IS, VM::M1, "SliceOrientation" },
{ 0x0019, 0x000b, 0, VR::DS, VM::M1, "LROffcenter" },
{ 0x0019, 0x000c, 0, VR::DS, VM::M1, "CCOffcenter" },
{ 0x0019, 0x000d, 0, VR::DS, VM::M1, "APOffcenter" },
{ 0x0019, 0x000e, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x000f, 0, VR::IS, VM::M1, "NumberOfSlices" },
{ 0x0019, 0x0010, 0, VR::DS, VM::M1, "SliceFactor" },
{ 0x0019, 0x0011, 0, VR::DS, VM::M1TN, "EchoTimes" },
{ 0x0019, 0x0014, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x0015, 0, VR::IS, VM::M1, "DynamicStudy" },
{ 0x0019, 0x0018, 0, VR::DS, VM::M1, "HeartbeatInterval" },
{ 0x0019, 0x0019, 0, VR::DS, VM::M1, "RepetitionTimeFFE" },
{ 0x0019, 0x001a, 0, VR::DS, VM::M1, "FFEFlipAngle" },
{ 0x0019, 0x001b, 0, VR::IS, VM::M1, "NumberOfScans" },
{ 0x0019, 0x001c, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x001d, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x001e, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0021, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0022, 0, VR::DS, VM::M1, "DynamicScanTimeBegin" },
{ 0x0019, 0x0023, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0024, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0025, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0026, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0027, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0028, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x0029, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0030, 0, VR::LO, VM::M1TN, "" },
{ 0x0019, 0x0031, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0040, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0045, 0, VR::IS, VM::M1, "ReconstructionResolution" },
{ 0x0019, 0x0050, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0051, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0052, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0053, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0054, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0055, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0056, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0057, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0058, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0059, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0061, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0062, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0063, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0064, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0065, 0, VR::DS, VM::M1, "RepetitionTimeIR" },
{ 0x0019, 0x0066, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0067, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0069, 0, VR::IS, VM::M1, "NumberOfPhases" },
{ 0x0019, 0x006a, 0, VR::IS, VM::M1, "CardiacFrequency" },
{ 0x0019, 0x006b, 0, VR::DS, VM::M1, "InversionDelay" },
{ 0x0019, 0x006c, 0, VR::DS, VM::M1, "GateDelay" },
{ 0x0019, 0x006d, 0, VR::DS, VM::M1, "GateWidth" },
{ 0x0019, 0x006e, 0, VR::DS, VM::M1, "TriggerDelayTime" },
{ 0x0019, 0x0070, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x0080, 0, VR::IS, VM::M1, "NumberOfChemicalShifts" },
{ 0x0019, 0x0081, 0, VR::DS, VM::M1, "ChemicalShift" },
{ 0x0019, 0x0084, 0, VR::IS, VM::M1, "NumberOfRows" },
{ 0x0019, 0x0085, 0, VR::IS, VM::M1, "NumberOfSamples" },
{ 0x0019, 0x008A, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x008B, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x008C, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x008D, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x008E, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x008F, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x0094, 0, VR::LO, VM::M1, "MagnetizationTransferContrast" },
{ 0x0019, 0x0095, 0, VR::LO, VM::M1, "SpectralPresaturationWithInversionRecovery" },
{ 0x0019, 0x0096, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0097, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00B4, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00B5, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00B6, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00D1, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00D3, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00F0, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00F6, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00F7, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00F8, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00F9, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00FA, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00FB, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00FC, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00a0, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00a1, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a3, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a4, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x00c0, 0, VR::DS, VM::M1, "TriggerDelayTimes" },
{ 0x0019, 0x00c8, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00c9, 0, VR::IS, VM::M1, "FoldoverDirectionTransverse" },
{ 0x0019, 0x00ca, 0, VR::IS, VM::M1, "FoldoverDirectionSagittal" },
{ 0x0019, 0x00cb, 0, VR::IS, VM::M1, "FoldoverDirectionCoronal" },
{ 0x0019, 0x00cc, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00cd, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00ce, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00cf, 0, VR::IS, VM::M1, "NumberOfEchoes" },
{ 0x0019, 0x00d0, 0, VR::IS, VM::M1, "ScanResolution" },
{ 0x0019, 0x00d2, 0, VR::LO, VM::M2, "WaterFatShift" },
{ 0x0019, 0x00d4, 0, VR::IS, VM::M1, "ArtifactReduction" },
{ 0x0019, 0x00d5, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00d6, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00d7, 0, VR::DS, VM::M1, "ScanPercentage" },
{ 0x0019, 0x00d8, 0, VR::IS, VM::M1, "Halfscan" },
{ 0x0019, 0x00d9, 0, VR::IS, VM::M1, "EPIFactor" },
{ 0x0019, 0x00da, 0, VR::IS, VM::M1, "TurboFactor" },
{ 0x0019, 0x00db, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00e0, 0, VR::IS, VM::M1, "PrepulseType" },
{ 0x0019, 0x00e1, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00e3, 0, VR::DS, VM::M1, "PhaseContrastVelocity" },
{ 0x0019, 0x00fc, 0, VR::IS, VM::M1, "ResonanceFrequency" },
{ 0x0021, 0x0000, 0, VR::IS, VM::M1, "ReconstructionNumber" },
{ 0x0021, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0008, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0009, 0, VR::CS, VM::M1, "" },
{ 0x0021, 0x000a, 0, VR::CS, VM::M1, "" },
{ 0x0021, 0x000f, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0010, 0, VR::TM, VM::M1, "ScanTime" },
{ 0x0021, 0x0013, 0, VR::CS, VM::M1, "" },
{ 0x0021, 0x0015, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0020, 0, VR::IS, VM::M1, "SliceNumber" },
{ 0x0021, 0x0021, 0, VR::IS, VM::M1, "SliceGap" },
{ 0x0021, 0x0030, 0, VR::IS, VM::M1, "EchoNumber" },
{ 0x0021, 0x0031, 0, VR::DS, VM::M1, "PatientReferenceID" },
{ 0x0021, 0x0035, 0, VR::IS, VM::M1, "ChemicalShiftNumber" },
{ 0x0021, 0x0040, 0, VR::IS, VM::M1, "PhaseNumber" },
{ 0x0021, 0x0050, 0, VR::IS, VM::M1, "DynamicScanNumber" },
{ 0x0021, 0x0060, 0, VR::IS, VM::M1, "NumberOfRowsInObject" },
{ 0x0021, 0x0061, 0, VR::IS, VM::M1TN, "RowNumber" },
{ 0x0021, 0x0062, 0, VR::IS, VM::M1TN, "" },
{ 0x0029, 0x0000, 0, VR::DS, VM::M2, "" },
{ 0x0029, 0x0004, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0011, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0031, 0, VR::DS, VM::M2, "" },
{ 0x0029, 0x0032, 0, VR::DS, VM::M2, "" },
{ 0x0029, 0x0050, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0051, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0052, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0053, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x00c3, 0, VR::IS, VM::M1, "ScanResolution" },
{ 0x0029, 0x00c4, 0, VR::IS, VM::M1, "FieldOfView" },
{ 0x0029, 0x00d5, 0, VR::LT, VM::M1, "SliceThickness" },
};

unsigned short Dict173TagHashTable[] = {
   38,    47,    60,    75,    90,   105,   114,   123,   132,   143,
  156,   165,   176,   189,   196,   203,   212,   223,   230,   235,
  246,   255,   262,   271,   278,   287,   296,   305,   320,   331,
  340,   349,   354,   357,   366,   369,   372,     0,     4,    20,
   25,    41,    82,    73,   143,   128,    33,     6,    19,    24,
   42,    83,    72,   142,    92,   161,   127,    32,   133,    80,
    7,    22,    27,    43,    84,    57,   105,    71,   141,    88,
  250,    91,   160,   119,     6,     7,    21,    26,    36,    49,
   44,    85,    58,   106,    70,   140,    89,   251,   121,     9,
    7,    24,    29,    35,    48,    45,    86,    59,   107,    86,
  248,   120,     8,   137,     0,     4,    23,    28,    46,    87,
   60,   108,    87,   249,     4,    61,   109,    65,   129,    94,
  164,   122,    10,     4,    25,    30,    62,   110,    64,   128,
  112,   218,     5,    16,    17,    90,   252,   113,   219,   117,
  252,   138,     4,     6,    15,    16,    49,    96,   110,   216,
  123,    15,   141,    32,   144,    80,     4,    50,    97,    67,
  133,   111,   217,   145,    81,     5,    34,    41,    51,    98,
   66,   132,   146,    82,   148,   195,     6,    18,    21,    33,
   40,    52,    99,    83,   240,   124,    16,   147,    83,     3,
   17,    20,    53,   100,   125,    19,     3,    37,    64,    54,
  101,    84,   246,     4,    55,   102,    85,   247,   105,   210,
  126,    21,     5,     8,     9,    56,   103,    82,   211,   130,
   49,   149,   196,     3,     7,     8,   104,   208,   129,    48,
    2,    10,    11,    81,   209,     5,     9,    10,    26,    33,
   38,    69,   108,   214,   140,    17,     4,    12,    13,   109,
  215,   131,    53,   139,    16,     3,    11,    12,    28,    35,
  106,   212,     4,    14,    15,    27,    34,   107,   213,   132,
   64,     3,    13,    14,    30,    37,    98,   202,     4,     1,
    1,    29,    36,    99,   203,   142,    49,     4,     0,     0,
   32,    39,    80,   182,    96,   200,     4,     3,     3,    31,
   38,    79,   181,    97,   201,     7,     2,     2,    47,    88,
   78,   180,   102,   206,   116,   227,   134,    96,   143,    50,
    5,     4,     5,    48,    89,   103,   207,   114,   224,   135,
   97,     4,    77,   151,   100,   204,   115,   225,   136,    98,
    4,     6,     7,    63,   112,    76,   150,   101,   205,     2,
    5,     6,    75,   149,     1,    74,   148,     4,    69,   139,
   95,   192,   118,     0,   150,   213,     1,    68,   138,     1,
   39,    80,     2,    40,    81,    93,   163,
};

vtkDICOMDictionary::Dict Dict173Data = {
"PHILIPS MR/PART",
37,
151,
Dict173TagHashTable,
Dict173Contents
};

// ----- GEMS_DL_IMG_01 -----

DictEntry Dict174Contents[] = {
{ 0x0019, 0x000B, 0, VR::DS, VM::M1T2, "FOVDimensionDouble" },
{ 0x0019, 0x002B, 0, VR::FL, VM::M1, "DistanceToTableTop" },
{ 0x0019, 0x0030, 0, VR::LO, VM::M1, "ImageFileName" },
{ 0x0019, 0x0031, 0, VR::IS, VM::M1, "DefaultSpatialFilterFamily" },
{ 0x0019, 0x0032, 0, VR::IS, VM::M1, "DefaultSpatialFilterStrength" },
{ 0x0019, 0x0033, 0, VR::DS, VM::M1, "MinSaturationDose" },
{ 0x0019, 0x0034, 0, VR::DS, VM::M1, "DetectorGain" },
{ 0x0019, 0x0035, 0, VR::DS, VM::M1, "PatientDoseLimit" },
{ 0x0019, 0x0036, 0, VR::DS, VM::M1, "PreprocImageRateMax" },
{ 0x0019, 0x0037, 0, VR::CS, VM::M1, "SensorRoiShape" },
{ 0x0019, 0x0038, 0, VR::DS, VM::M1, "SensorRoixPosition" },
{ 0x0019, 0x0039, 0, VR::DS, VM::M1, "SensorRoiyPosition" },
{ 0x0019, 0x003A, 0, VR::DS, VM::M1, "SensorRoixSize" },
{ 0x0019, 0x003B, 0, VR::DS, VM::M1, "SensorRoiySize" },
{ 0x0019, 0x003D, 0, VR::DS, VM::M1, "NoiseSensitivity" },
{ 0x0019, 0x003E, 0, VR::DS, VM::M1, "SharpSensitivity" },
{ 0x0019, 0x003F, 0, VR::DS, VM::M1, "ContrastSensitivity" },
{ 0x0019, 0x0040, 0, VR::DS, VM::M1, "LagSensitivity" },
{ 0x0019, 0x0041, 0, VR::CS, VM::M1, "Tube" },
{ 0x0019, 0x0042, 0, VR::US, VM::M1, "DetectorSizeRows" },
{ 0x0019, 0x0043, 0, VR::US, VM::M1, "DetectorSizeColumns" },
{ 0x0019, 0x0044, 0, VR::DS, VM::M1, "MinObjectSize" },
{ 0x0019, 0x0045, 0, VR::DS, VM::M1, "MaxObjectSize" },
{ 0x0019, 0x0046, 0, VR::DS, VM::M1, "MaxObjectSpeed" },
{ 0x0019, 0x0047, 0, VR::CS, VM::M1, "ObjectBackMotion" },
{ 0x0019, 0x0048, 0, VR::UL, VM::M1, "ExposureTrajectoryFamily" },
{ 0x0019, 0x0049, 0, VR::DS, VM::M1, "WindowTimeDuration" },
{ 0x0019, 0x004A, 0, VR::CS, VM::M1, "PositionerAngleDisplayMode" },
{ 0x0019, 0x004B, 0, VR::IS, VM::M2, "DetectorOrigin" },
{ 0x0019, 0x004C, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x004E, 0, VR::DS, VM::M2, "DefaultBrightnessContrast" },
{ 0x0019, 0x004F, 0, VR::DS, VM::M2, "UserBrightnessContrast" },
{ 0x0019, 0x0050, 0, VR::IS, VM::M1, "SourceSeriesNumber" },
{ 0x0019, 0x0051, 0, VR::IS, VM::M1, "SourceImageNumber" },
{ 0x0019, 0x0052, 0, VR::IS, VM::M1, "SourceFrameNumber" },
{ 0x0019, 0x0053, 0, VR::UI, VM::M1, "SourceSeriesItemId" },
{ 0x0019, 0x0054, 0, VR::UI, VM::M1, "SourceImageItemId" },
{ 0x0019, 0x0055, 0, VR::UI, VM::M1, "SourceFrameItemId" },
{ 0x0019, 0x0060, 0, VR::US, VM::M1, "NumberOfPointsBeforeAcquisition" },
{ 0x0019, 0x0061, 0, VR::OW, VM::M1, "CurveDataBeforeAcquisition" },
{ 0x0019, 0x0062, 0, VR::US, VM::M1, "NumberOfPointsTrigger" },
{ 0x0019, 0x0063, 0, VR::OW, VM::M1, "CurveDataTrigger" },
{ 0x0019, 0x0064, 0, VR::SH, VM::M1, "ECGSynchronization" },
{ 0x0019, 0x0065, 0, VR::SH, VM::M1, "ECGDelayMode" },
{ 0x0019, 0x0066, 0, VR::IS, VM::M1TN, "ECGDelayVector" },
{ 0x0019, 0x0067, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0068, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0069, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x007A, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x007B, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x007C, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::DS, VM::M1, "ImageDose" },
{ 0x0019, 0x0081, 0, VR::US, VM::M1, "CalibrationFrame" },
{ 0x0019, 0x0082, 0, VR::CS, VM::M1, "CalibrationObject" },
{ 0x0019, 0x0083, 0, VR::DS, VM::M1, "CalibrationObjectSize" },
{ 0x0019, 0x0084, 0, VR::FL, VM::M1, "CalibrationFactor" },
{ 0x0019, 0x0085, 0, VR::DA, VM::M1, "CalibrationDate" },
{ 0x0019, 0x0086, 0, VR::TM, VM::M1, "CalibrationTime" },
{ 0x0019, 0x0087, 0, VR::US, VM::M1, "CalibrationAccuracy" },
{ 0x0019, 0x0088, 0, VR::CS, VM::M1, "CalibrationExtended" },
{ 0x0019, 0x0089, 0, VR::US, VM::M1, "CalibrationImageOriginal" },
{ 0x0019, 0x008A, 0, VR::US, VM::M1, "CalibrationFrameOriginal" },
{ 0x0019, 0x008B, 0, VR::US, VM::M1, "CalibrationNbPointsUif" },
{ 0x0019, 0x008C, 0, VR::US, VM::M1TN, "CalibrationPointsRow" },
{ 0x0019, 0x008D, 0, VR::US, VM::M1TN, "CalibrationPointsColumn" },
{ 0x0019, 0x008E, 0, VR::FL, VM::M1, "CalibrationMagnificationRatio" },
{ 0x0019, 0x008F, 0, VR::LO, VM::M1, "CalibrationSoftwareVersion" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "ExtendedCalibrationSoftwareVersion" },
{ 0x0019, 0x0091, 0, VR::IS, VM::M1, "CalibrationReturnCode" },
{ 0x0019, 0x0092, 0, VR::DS, VM::M1, "DetectorRotationAngle" },
{ 0x0019, 0x0093, 0, VR::CS, VM::M1, "SpatialChange" },
{ 0x0019, 0x0094, 0, VR::CS, VM::M1, "InconsistentFlag" },
{ 0x0019, 0x0095, 0, VR::CS, VM::M2, "HorizontalAndVerticalImageFlip" },
{ 0x0019, 0x0096, 0, VR::CS, VM::M1, "InternalLabelImage" },
{ 0x0019, 0x0097, 0, VR::DS, VM::M1TN, "Angle1Increment" },
{ 0x0019, 0x0098, 0, VR::DS, VM::M1TN, "Angle2Increment" },
{ 0x0019, 0x0099, 0, VR::DS, VM::M1TN, "Angle3Increment" },
{ 0x0019, 0x009B, 0, VR::CS, VM::M1, "Grid" },
{ 0x0019, 0x009C, 0, VR::FL, VM::M1, "DefaultMaskPixelShift" },
{ 0x0019, 0x009D, 0, VR::CS, VM::M1, "ApplicableReviewMode" },
{ 0x0019, 0x009E, 0, VR::DS, VM::M1TN, "LogLUTControlPoints" },
{ 0x0019, 0x009F, 0, VR::DS, VM::M1TN, "ExpLUTSUBControlPoints" },
{ 0x0019, 0x009a, 0, VR::DS, VM::M1TN, "SensorFeedback" },
{ 0x0019, 0x00A0, 0, VR::DS, VM::M1, "ABDValue" },
{ 0x0019, 0x00A1, 0, VR::DS, VM::M1, "SubtractionWindowCenter" },
{ 0x0019, 0x00A2, 0, VR::DS, VM::M1, "SubtractionWindowWidth" },
{ 0x0019, 0x00A3, 0, VR::DS, VM::M1, "ImageRotation" },
{ 0x0019, 0x00A4, 0, VR::CS, VM::M1, "AutoInjectionEnabled" },
{ 0x0019, 0x00A5, 0, VR::CS, VM::M1, "InjectionPhase" },
{ 0x0019, 0x00A6, 0, VR::DS, VM::M1, "InjectionDelay" },
{ 0x0019, 0x00A7, 0, VR::IS, VM::M1, "ReferenceInjectionFrameNumber" },
{ 0x0019, 0x00A8, 0, VR::DS, VM::M1, "InjectionDuration" },
{ 0x0019, 0x00A9, 0, VR::DS, VM::M1TN, "EPT" },
{ 0x0019, 0x00AA, 0, VR::CS, VM::M1, "CanDownscan512" },
{ 0x0019, 0x00AB, 0, VR::IS, VM::M1, "CurrentSpatialFilterStrength" },
{ 0x0019, 0x00AC, 0, VR::DS, VM::M1, "BrightnessSensitivity" },
{ 0x0019, 0x00AD, 0, VR::DS, VM::M1TN, "ExpLUTNOSUBControlPoints" },
{ 0x0019, 0x00AF, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x00b0, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x00b1, 0, VR::LO, VM::M1, "AcquisitionModeDescription" },
{ 0x0019, 0x00b2, 0, VR::LO, VM::M1, "AcquisitionModeDescriptionLabel" },
{ 0x0019, 0x00b3, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00b8, 0, VR::FL, VM::M1, "" },
{ 0x0019, 0x00ba, 0, VR::CS, VM::M1, "AcquisitionRegion" },
{ 0x0019, 0x00bb, 0, VR::CS, VM::M1, "AcquisitionSUBMode" },
{ 0x0019, 0x00bc, 0, VR::FL, VM::M1, "TableCradleAngle" },
{ 0x0019, 0x00bd, 0, VR::CS, VM::M1TN, "TableRotationStatusVector" },
{ 0x0019, 0x00be, 0, VR::FL, VM::M1TN, "SourceToImageDistancePerFrameVector" },
{ 0x0019, 0x00c2, 0, VR::DS, VM::M1TN, "" },
{ 0x0019, 0x00c3, 0, VR::FL, VM::M1TN, "TableRotationAngleIncrement" },
{ 0x0019, 0x00c4, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00c7, 0, VR::CS, VM::M1, "PatientPositionPerImage" },
{ 0x0019, 0x00d7, 0, VR::FL, VM::M1TN, "TableXPositionToIsocenterIncrement" },
{ 0x0019, 0x00d8, 0, VR::FL, VM::M1TN, "TableYPositionToIsocenterIncrement" },
{ 0x0019, 0x00d9, 0, VR::FL, VM::M1TN, "TableZPositionToIsocenterIncrement" },
{ 0x0019, 0x00da, 0, VR::FL, VM::M1TN, "TableHeadTiltAngleIncrement" },
{ 0x0019, 0x00dc, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00dd, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00de, 0, VR::CS, VM::M1, "AcquisitionPlane" },
{ 0x0019, 0x00e0, 0, VR::FL, VM::M1, "" },
{ 0x0019, 0x00e9, 0, VR::FL, VM::M1TN, "SourceToDetectorDistancePerFrameVector" },
{ 0x0019, 0x00ea, 0, VR::FL, VM::M1, "TableRotationAngle" },
{ 0x0019, 0x00eb, 0, VR::FL, VM::M1, "TableXPositionToIsocenter" },
{ 0x0019, 0x00ec, 0, VR::FL, VM::M1, "TableYPositionToIsocenter" },
{ 0x0019, 0x00ed, 0, VR::FL, VM::M1, "TableZPositionToIsocenter" },
{ 0x0019, 0x00ee, 0, VR::FL, VM::M1, "TableHeadTiltAngle" },
{ 0x0019, 0x00ef, 0, VR::FL, VM::M1, "" },
};

unsigned short Dict174TagHashTable[] = {
   32,    43,    54,    67,    76,    87,   100,   109,   116,   125,
  132,   143,   152,   163,   174,   183,   192,   199,   202,   209,
  220,   227,   234,   241,   248,   257,   264,   271,   282,   293,
  304,     0,     5,    22,    69,    42,   100,    51,   128,    84,
  161,   109,   195,     5,    11,    57,    23,    70,    43,   101,
   58,   135,    83,   160,     6,    10,    56,    24,    71,    44,
  102,    57,   134,    90,   167,   119,   224,     4,    13,    59,
   45,   103,    56,   133,    89,   166,     5,    12,    58,    55,
  132,    77,   155,    88,   165,   111,   199,     6,    14,    61,
   48,   122,    82,   154,    87,   164,   104,   187,   110,   196,
    4,    49,   123,    76,   153,   103,   186,   115,   218,     3,
   16,    63,    50,   124,    75,   152,     4,    15,    62,    81,
  159,   102,   184,   113,   216,     3,     3,    49,    80,   158,
  114,   217,     5,     2,    48,    32,    80,    79,   157,   107,
  190,   118,   222,     4,     5,    51,    33,    81,    78,   156,
  106,   189,     5,     4,    50,    34,    82,    70,   147,   105,
  188,   116,   220,     5,     7,    53,    35,    83,    69,   146,
  101,   179,   117,   221,     4,     6,    52,    36,    84,    68,
  145,   100,   178,     4,     9,    55,    37,    85,    67,   144,
   99,   177,     3,     8,    54,    74,   151,    98,   176,     1,
   73,   150,     3,     0,    11,    25,    72,    72,   149,     5,
    1,    43,    26,    73,    46,   104,    71,   148,   112,   215,
    3,    27,    74,    47,   105,    62,   139,     3,    28,    75,
   61,   138,    94,   171,     3,    29,    76,    60,   137,    93,
  170,     3,    59,   136,    92,   169,   121,   234,     4,    30,
   78,    66,   143,    91,   168,   122,   235,     3,    31,    79,
   65,   142,    97,   175,     3,    17,    64,    64,   141,   120,
  233,     5,    18,    65,    38,    96,    63,   140,    96,   173,
  125,   238,     5,    19,    66,    39,    97,    54,   131,    95,
  172,   126,   239,     5,    20,    67,    40,    98,    53,   130,
   86,   163,   123,   236,     6,    21,    68,    41,    99,    52,
  129,    85,   162,   108,   194,   124,   237,
};

vtkDICOMDictionary::Dict Dict174Data = {
"GEMS_DL_IMG_01",
31,
127,
Dict174TagHashTable,
Dict174Contents
};

// ----- ESOFT_DICOM_ECAT_OWNERCODE -----

DictEntry Dict175Contents[] = {
{ 0x0015, 0x0000, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict175TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict175Data = {
"ESOFT_DICOM_ECAT_OWNERCODE",
1,
1,
Dict175TagHashTable,
Dict175Contents
};

// ----- KINETDX_GRAPHICS -----

DictEntry Dict176Contents[] = {
{ 0x0021, 0x00a4, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict176TagHashTable[] = {
    2,     0,     1,     0,   164,
};

vtkDICOMDictionary::Dict Dict176Data = {
"KINETDX_GRAPHICS",
1,
1,
Dict176TagHashTable,
Dict176Contents
};

// ----- GEMS_PETD_01 -----

DictEntry Dict177Contents[] = {
{ 0x0009, 0x0001, 0, VR::LO, VM::M2, "ImplementationVersionName" },
{ 0x0009, 0x0002, 0, VR::LO, VM::M1, "PatientID" },
{ 0x0009, 0x0003, 0, VR::SH, VM::M1, "PatientCompatibleVersion" },
{ 0x0009, 0x0004, 0, VR::SH, VM::M1, "PatientSoftwareVersion" },
{ 0x0009, 0x0005, 0, VR::DT, VM::M1, "PatientDateTime" },
{ 0x0009, 0x0006, 0, VR::SL, VM::M1, "PatientType" },
{ 0x0009, 0x0007, 0, VR::UI, VM::M1, "ExamID" },
{ 0x0009, 0x0008, 0, VR::SH, VM::M1, "ExamCompatibleVersion" },
{ 0x0009, 0x0009, 0, VR::SH, VM::M1, "ExamSoftwareVersion" },
{ 0x0009, 0x000a, 0, VR::UI, VM::M1, "ScanID" },
{ 0x0009, 0x000b, 0, VR::SH, VM::M1, "ScanCompatibleVersion" },
{ 0x0009, 0x000c, 0, VR::SH, VM::M1, "ScanSoftwareVersion" },
{ 0x0009, 0x000d, 0, VR::DT, VM::M1, "ScanDateTime" },
{ 0x0009, 0x000e, 0, VR::DT, VM::M1, "ScanReady" },
{ 0x0009, 0x000f, 0, VR::ST, VM::M1, "ScanDescription" },
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "HospitalName" },
{ 0x0009, 0x0011, 0, VR::LO, VM::M1, "ScannerDescription" },
{ 0x0009, 0x0012, 0, VR::LO, VM::M1, "Manufacturer" },
{ 0x0009, 0x0013, 0, VR::UI, VM::M1, "FORIdentifier" },
{ 0x0009, 0x0014, 0, VR::LO, VM::M1, "LandmarkName" },
{ 0x0009, 0x0015, 0, VR::SH, VM::M1, "LandmarkAbbrev" },
{ 0x0009, 0x0016, 0, VR::SL, VM::M1, "PatientPosition" },
{ 0x0009, 0x0017, 0, VR::SL, VM::M1, "ScanPerspective" },
{ 0x0009, 0x0018, 0, VR::SL, VM::M1, "ScanType" },
{ 0x0009, 0x0019, 0, VR::SL, VM::M1, "ScanMode" },
{ 0x0009, 0x001a, 0, VR::SL, VM::M1, "StartCondition" },
{ 0x0009, 0x001b, 0, VR::SL, VM::M1, "StartConditionData" },
{ 0x0009, 0x001c, 0, VR::SL, VM::M1, "SelStopCondition" },
{ 0x0009, 0x001d, 0, VR::SL, VM::M1, "SelStopConditionData" },
{ 0x0009, 0x001e, 0, VR::SL, VM::M1, "CollectDeadtime" },
{ 0x0009, 0x001f, 0, VR::SL, VM::M1, "CollectSingles" },
{ 0x0009, 0x0020, 0, VR::SL, VM::M1, "CollectCountRate" },
{ 0x0009, 0x0021, 0, VR::SL, VM::M1, "CountRatePeriod" },
{ 0x0009, 0x0022, 0, VR::SL, VM::M1, "DelayedEvents" },
{ 0x0009, 0x0023, 0, VR::SL, VM::M1, "DelayedBias" },
{ 0x0009, 0x0024, 0, VR::SL, VM::M1, "WordSize" },
{ 0x0009, 0x0025, 0, VR::SL, VM::M1, "AxialAcceptance" },
{ 0x0009, 0x0026, 0, VR::SL, VM::M1, "AxialAngle3D" },
{ 0x0009, 0x0027, 0, VR::SL, VM::M1, "ThetaCompression" },
{ 0x0009, 0x0028, 0, VR::SL, VM::M1, "AxialCompression" },
{ 0x0009, 0x0029, 0, VR::FL, VM::M1, "GantryTiltAngle" },
{ 0x0009, 0x002a, 0, VR::SL, VM::M1, "Collimation" },
{ 0x0009, 0x002b, 0, VR::SL, VM::M1, "ScanFOV" },
{ 0x0009, 0x002c, 0, VR::SL, VM::M1, "AxialFOV" },
{ 0x0009, 0x002d, 0, VR::SL, VM::M1, "EventSeparation" },
{ 0x0009, 0x002e, 0, VR::SL, VM::M1, "MaskWidth" },
{ 0x0009, 0x002f, 0, VR::SL, VM::M1, "BinningMode" },
{ 0x0009, 0x0030, 0, VR::SL, VM::M1, "TrigRejMethod" },
{ 0x0009, 0x0031, 0, VR::SL, VM::M1, "NumberForReject" },
{ 0x0009, 0x0032, 0, VR::SL, VM::M1, "LowerRejectLimit" },
{ 0x0009, 0x0033, 0, VR::SL, VM::M1, "UpperRejectLimit" },
{ 0x0009, 0x0034, 0, VR::SL, VM::M1, "TriggersAcquired" },
{ 0x0009, 0x0035, 0, VR::SL, VM::M1, "TriggersRejected" },
{ 0x0009, 0x0036, 0, VR::LO, VM::M1, "TracerName" },
{ 0x0009, 0x0037, 0, VR::LO, VM::M1, "BatchDescription" },
{ 0x0009, 0x0038, 0, VR::FL, VM::M1, "TracerActivity" },
{ 0x0009, 0x0039, 0, VR::DT, VM::M1, "MeasuredDateTime" },
{ 0x0009, 0x003a, 0, VR::FL, VM::M1, "PreInjVolume" },
{ 0x0009, 0x003b, 0, VR::DT, VM::M1, "AdministeredDateTime" },
{ 0x0009, 0x003c, 0, VR::FL, VM::M1, "PostInjectedActivity" },
{ 0x0009, 0x003d, 0, VR::DT, VM::M1, "PostInjectedDateTime" },
{ 0x0009, 0x003e, 0, VR::SH, VM::M1, "RadioNuclideName" },
{ 0x0009, 0x003f, 0, VR::FL, VM::M1, "HalfLife" },
{ 0x0009, 0x0040, 0, VR::FL, VM::M1, "PositronFraction" },
{ 0x0009, 0x0041, 0, VR::SL, VM::M1, "Source1Holder" },
{ 0x0009, 0x0042, 0, VR::FL, VM::M1, "Source1Activity" },
{ 0x0009, 0x0043, 0, VR::DT, VM::M1, "Source1MeasDT" },
{ 0x0009, 0x0044, 0, VR::SH, VM::M1, "Source1RadioNuclide" },
{ 0x0009, 0x0045, 0, VR::FL, VM::M1, "Source1HalfLife" },
{ 0x0009, 0x0046, 0, VR::SL, VM::M1, "Source2Holder" },
{ 0x0009, 0x0047, 0, VR::FL, VM::M1, "Source2Activity" },
{ 0x0009, 0x0048, 0, VR::DT, VM::M1, "Source2MeasDT" },
{ 0x0009, 0x0049, 0, VR::SH, VM::M1, "Source2RadioNuclide" },
{ 0x0009, 0x004a, 0, VR::FL, VM::M1, "Source2HalfLife" },
{ 0x0009, 0x004b, 0, VR::SL, VM::M1, "SourceSpeed" },
{ 0x0009, 0x004c, 0, VR::FL, VM::M1, "SourceLocation" },
{ 0x0009, 0x004d, 0, VR::SL, VM::M1, "EmissionPresent" },
{ 0x0009, 0x004e, 0, VR::SL, VM::M1, "LowerAxialAcc" },
{ 0x0009, 0x004f, 0, VR::SL, VM::M1, "UpperAxialAcc" },
{ 0x0009, 0x0050, 0, VR::SL, VM::M1, "LowerCoincLimit" },
{ 0x0009, 0x0051, 0, VR::SL, VM::M1, "UpperCoincLimit" },
{ 0x0009, 0x0052, 0, VR::SL, VM::M1, "CoincDelayOffset" },
{ 0x0009, 0x0053, 0, VR::SL, VM::M1, "CoincOutputMode" },
{ 0x0009, 0x0054, 0, VR::SL, VM::M1, "UpperEnergyLimit" },
{ 0x0009, 0x0055, 0, VR::SL, VM::M1, "LowerEnergyLimit" },
{ 0x0009, 0x0056, 0, VR::UI, VM::M1, "NormalCalID" },
{ 0x0009, 0x0057, 0, VR::UI, VM::M1, "Normal2DCalID" },
{ 0x0009, 0x0058, 0, VR::UI, VM::M1, "BlankCalID" },
{ 0x0009, 0x0059, 0, VR::UI, VM::M1, "WCCalID" },
{ 0x0009, 0x005a, 0, VR::SL, VM::M1, "Derived" },
{ 0x0009, 0x005b, 0, VR::LO, VM::M1, "ContrastAgent" },
{ 0x0009, 0x005c, 0, VR::UI, VM::M1, "frame_id" },
{ 0x0009, 0x005d, 0, VR::UI, VM::M1, "scan_id" },
{ 0x0009, 0x005e, 0, VR::UI, VM::M1, "exam_id" },
{ 0x0009, 0x005f, 0, VR::LO, VM::M1, "patient_id" },
{ 0x0009, 0x0060, 0, VR::SH, VM::M1, "compatible_version" },
{ 0x0009, 0x0061, 0, VR::SH, VM::M1, "software_version" },
{ 0x0009, 0x0062, 0, VR::ST, VM::M1, "where_is_frame" },
{ 0x0009, 0x0063, 0, VR::SL, VM::M1, "frame_size" },
{ 0x0009, 0x0064, 0, VR::SL, VM::M1, "file_exists" },
{ 0x0009, 0x0065, 0, VR::SL, VM::M1, "patient_entry" },
{ 0x0009, 0x0066, 0, VR::FL, VM::M1, "table_height" },
{ 0x0009, 0x0067, 0, VR::FL, VM::M1, "table_z_position" },
{ 0x0009, 0x0068, 0, VR::DT, VM::M1, "landmark_datetime" },
{ 0x0009, 0x0069, 0, VR::SL, VM::M1, "slice_count" },
{ 0x0009, 0x006a, 0, VR::FL, VM::M1, "start_location" },
{ 0x0009, 0x006b, 0, VR::SL, VM::M1, "acq_delay" },
{ 0x0009, 0x006c, 0, VR::DT, VM::M1, "acq_start" },
{ 0x0009, 0x006d, 0, VR::SL, VM::M1, "acq_duration" },
{ 0x0009, 0x006e, 0, VR::SL, VM::M1, "acq_bin_dur" },
{ 0x0009, 0x006f, 0, VR::SL, VM::M1, "acq_bin_start" },
{ 0x0009, 0x0070, 0, VR::SL, VM::M1, "actual_stop_cond" },
{ 0x0009, 0x0071, 0, VR::FD, VM::M1, "total_prompts" },
{ 0x0009, 0x0072, 0, VR::FD, VM::M1, "total_delays" },
{ 0x0009, 0x0073, 0, VR::SL, VM::M1, "frame_valid" },
{ 0x0009, 0x0074, 0, VR::SL, VM::M1, "validity_info" },
{ 0x0009, 0x0075, 0, VR::SL, VM::M1, "archived" },
{ 0x0009, 0x0076, 0, VR::SL, VM::M1, "compression" },
{ 0x0009, 0x0077, 0, VR::SL, VM::M1, "uncompressed_size" },
{ 0x0009, 0x0078, 0, VR::SL, VM::M1, "accum_bin_dur" },
{ 0x0009, 0x0079, 0, VR::SH, VM::M1, "ImageSetCompatibleVersion" },
{ 0x0009, 0x007a, 0, VR::SH, VM::M1, "ImageSetSoftwareVersion" },
{ 0x0009, 0x007b, 0, VR::DT, VM::M1, "ImageSetDateTime" },
{ 0x0009, 0x007c, 0, VR::SL, VM::M1, "ImageSetSource" },
{ 0x0009, 0x007d, 0, VR::SL, VM::M1, "ImageSetContents" },
{ 0x0009, 0x007e, 0, VR::SL, VM::M1, "ImageSetType" },
{ 0x0009, 0x007f, 0, VR::DS, VM::M1, "ImageSetReference" },
{ 0x0009, 0x0080, 0, VR::SL, VM::M1, "MultiPatient" },
{ 0x0009, 0x0081, 0, VR::SL, VM::M1, "NumberOfNormals" },
{ 0x0009, 0x0082, 0, VR::UI, VM::M1, "ColorMapID" },
{ 0x0009, 0x0083, 0, VR::SL, VM::M1, "WindowLevelType" },
{ 0x0009, 0x0084, 0, VR::FL, VM::M1, "Rotate" },
{ 0x0009, 0x0085, 0, VR::SL, VM::M1, "Flip" },
{ 0x0009, 0x0086, 0, VR::FL, VM::M1, "Zoom" },
{ 0x0009, 0x0087, 0, VR::SL, VM::M1, "PanX" },
{ 0x0009, 0x0088, 0, VR::SL, VM::M1, "PanY" },
{ 0x0009, 0x0089, 0, VR::FL, VM::M1, "WindowLevelMin" },
{ 0x0009, 0x008a, 0, VR::FL, VM::M1, "WindowLevelMax" },
{ 0x0009, 0x008b, 0, VR::SL, VM::M1, "ReconMethod" },
{ 0x0009, 0x008c, 0, VR::SL, VM::M1, "Attenuation" },
{ 0x0009, 0x008d, 0, VR::FL, VM::M1, "AttenuationCoefficient" },
{ 0x0009, 0x008e, 0, VR::SL, VM::M1, "BPFilter" },
{ 0x0009, 0x008f, 0, VR::FL, VM::M1, "BPFilterCutoff" },
{ 0x0009, 0x0090, 0, VR::SL, VM::M1, "BPFilterOrder" },
{ 0x0009, 0x0091, 0, VR::FL, VM::M1, "BPFilterCenterI" },
{ 0x0009, 0x0092, 0, VR::FL, VM::M1, "BPFilterCenterP" },
{ 0x0009, 0x0093, 0, VR::SL, VM::M1, "AttenSmooth" },
{ 0x0009, 0x0094, 0, VR::SL, VM::M1, "AttenSmoothParam" },
{ 0x0009, 0x0095, 0, VR::SL, VM::M1, "AngleSmoothParam" },
{ 0x0009, 0x0096, 0, VR::UI, VM::M1, "WellCounterCalID" },
{ 0x0009, 0x0097, 0, VR::UI, VM::M1, "TransScanID" },
{ 0x0009, 0x0098, 0, VR::UI, VM::M1, "NormCalID" },
{ 0x0009, 0x0099, 0, VR::UI, VM::M1, "BlnkCalID" },
{ 0x0009, 0x009a, 0, VR::FL, VM::M1, "CACEdgeThreshold" },
{ 0x0009, 0x009b, 0, VR::FL, VM::M1, "CACSkullOffset" },
{ 0x0009, 0x009c, 0, VR::UI, VM::M1, "EmissSubID" },
{ 0x0009, 0x009d, 0, VR::SS, VM::M1, "RadialFilter3D" },
{ 0x0009, 0x009e, 0, VR::FL, VM::M1, "RadialCutoff3D" },
{ 0x0009, 0x009f, 0, VR::SL, VM::M1, "AxialFilter3D" },
{ 0x0009, 0x00a0, 0, VR::FL, VM::M1, "AxialCutoff3D" },
{ 0x0009, 0x00a1, 0, VR::FL, VM::M1, "AxialStart" },
{ 0x0009, 0x00a2, 0, VR::FL, VM::M1, "AxialSpacing" },
{ 0x0009, 0x00a3, 0, VR::SL, VM::M1, "AxialAnglesUsed" },
{ 0x0009, 0x00a4, 0, VR::SH, VM::M1, "compatible_version" },
{ 0x0009, 0x00a5, 0, VR::SH, VM::M1, "software_version" },
{ 0x0009, 0x00a6, 0, VR::SL, VM::M1, "slice_number" },
{ 0x0009, 0x00a7, 0, VR::FL, VM::M1, "total_counts" },
{ 0x0009, 0x00a8, 0, VR::OB, VM::M1, "other_atts" },
{ 0x0009, 0x00a9, 0, VR::SL, VM::M1, "other_atts_size" },
{ 0x0009, 0x00aa, 0, VR::SL, VM::M1, "archived" },
{ 0x0009, 0x00ab, 0, VR::FL, VM::M1, "bp_center_x" },
{ 0x0009, 0x00ac, 0, VR::FL, VM::M1, "bp_center_y" },
{ 0x0009, 0x00ad, 0, VR::UI, VM::M1, "trans_frame_id" },
{ 0x0009, 0x00ae, 0, VR::UI, VM::M1, "tpluse_frame_id" },
{ 0x0009, 0x00b1, 0, VR::FL, VM::M1, "profile_spacing" },
{ 0x0009, 0x00b2, 0, VR::SS, VM::M1, "IRNumIterations" },
{ 0x0009, 0x00b3, 0, VR::SS, VM::M1, "IRNumSubsets" },
{ 0x0009, 0x00b4, 0, VR::FL, VM::M1, "IRReconFOV" },
{ 0x0009, 0x00b5, 0, VR::SS, VM::M1, "IRCorrModel" },
{ 0x0009, 0x00b6, 0, VR::SS, VM::M1, "IRLoopFilter" },
{ 0x0009, 0x00b7, 0, VR::FL, VM::M1, "IRPreFiltParam" },
{ 0x0009, 0x00b8, 0, VR::FL, VM::M1, "IRLoopFiltParam" },
{ 0x0009, 0x00b9, 0, VR::FL, VM::M1, "ResponseFiltParam" },
{ 0x0009, 0x00ba, 0, VR::SS, VM::M1, "PostFilter" },
{ 0x0009, 0x00bb, 0, VR::FL, VM::M1, "PostFilterParam" },
{ 0x0009, 0x00bc, 0, VR::SS, VM::M1, "IRRegularize" },
{ 0x0009, 0x00bd, 0, VR::FL, VM::M1, "IRRegularizeParam" },
{ 0x0009, 0x00be, 0, VR::SS, VM::M1, "ACBPFilter" },
{ 0x0009, 0x00bf, 0, VR::FL, VM::M1, "ACBPFiltCutoff" },
{ 0x0009, 0x00c0, 0, VR::SL, VM::M1, "ACBPFiltOrder" },
{ 0x0009, 0x00c1, 0, VR::SS, VM::M1, "ACImgSmooth" },
{ 0x0009, 0x00c2, 0, VR::FL, VM::M1, "ACImgSmoothParm" },
{ 0x0009, 0x00c3, 0, VR::SL, VM::M1, "ScatterMethod" },
{ 0x0009, 0x00c4, 0, VR::SS, VM::M1, "ScatterNumIter" },
{ 0x0009, 0x00c5, 0, VR::FL, VM::M1, "ScatterParm" },
{ 0x0009, 0x00c6, 0, VR::FL, VM::M1, "seg_qc_parm" },
{ 0x0009, 0x00c7, 0, VR::SL, VM::M1, "overlap" },
{ 0x0009, 0x00c8, 0, VR::UI, VM::M1, "ovlp_frm_id" },
{ 0x0009, 0x00c9, 0, VR::UI, VM::M1, "ovlp_trans_frm_id" },
{ 0x0009, 0x00ca, 0, VR::UI, VM::M1, "ovlp_tpulse_frm_id" },
{ 0x0009, 0x00cb, 0, VR::FL, VM::M1, "vqc_x_axis_trans" },
{ 0x0009, 0x00cc, 0, VR::FL, VM::M1, "vqc_x_axis_tilt" },
{ 0x0009, 0x00cd, 0, VR::FL, VM::M1, "vqc_y_axis_trans" },
{ 0x0009, 0x00ce, 0, VR::FL, VM::M1, "vqc_y_axis_swivel" },
{ 0x0009, 0x00cf, 0, VR::FL, VM::M1, "vqc_z_axis_trans" },
{ 0x0009, 0x00d0, 0, VR::FL, VM::M1, "vqc_z_axis_roll" },
{ 0x0009, 0x00d1, 0, VR::LO, VM::M1, "ctac_conv_scale" },
{ 0x0009, 0x00d2, 0, VR::UI, VM::M1, "image_set_id" },
{ 0x0009, 0x00d3, 0, VR::SL, VM::M1, "contrast_route" },
{ 0x0009, 0x00d4, 0, VR::LO, VM::M1, "ctac_conv_scale" },
{ 0x0009, 0x00d5, 0, VR::FL, VM::M1, "loop_filter_parm" },
{ 0x0009, 0x00d6, 0, VR::FL, VM::M1, "image_one_loc" },
{ 0x0009, 0x00d7, 0, VR::FL, VM::M1, "image_index_loc" },
{ 0x0009, 0x00d8, 0, VR::SL, VM::M1, "frame_number" },
{ 0x0009, 0x00d9, 0, VR::SL, VM::M1, "list_file_exists" },
{ 0x0009, 0x00da, 0, VR::ST, VM::M1, "where_is_list_frame" },
{ 0x0009, 0x00db, 0, VR::SL, VM::M1, "ir_z_filter_flag" },
{ 0x0009, 0x00dc, 0, VR::FL, VM::M1, "ir_z_filter_ratio" },
{ 0x0009, 0x00dd, 0, VR::US, VM::M1, "num_of_rr_interval" },
{ 0x0009, 0x00de, 0, VR::US, VM::M1, "num_of_time_slots" },
{ 0x0009, 0x00df, 0, VR::US, VM::M1, "num_of_slices" },
{ 0x0009, 0x00e0, 0, VR::US, VM::M1, "num_of_time_slices" },
{ 0x0009, 0x00e1, 0, VR::SL, VM::M1, "unlisted_scan" },
{ 0x0009, 0x00e2, 0, VR::SL, VM::M1, "rest_stress" },
{ 0x0009, 0x00e3, 0, VR::FL, VM::M1, "phase_percentage" },
{ 0x0009, 0x00e4, 0, VR::ST, VM::M1, "" },
{ 0x0009, 0x00e5, 0, VR::FL, VM::M1, "left_shift" },
{ 0x0009, 0x00e6, 0, VR::FL, VM::M1, "posterior_shift" },
{ 0x0009, 0x00e7, 0, VR::FL, VM::M1, "superior_shift" },
{ 0x0009, 0x00e8, 0, VR::SL, VM::M1, "acq_bin_num" },
{ 0x0009, 0x00e9, 0, VR::FL, VM::M1, "acq_bin_dur_percent" },
{ 0x0009, 0x00ea, 0, VR::SL, VM::M1, "" },
{ 0x0009, 0x00eb, 0, VR::FL, VM::M1, "" },
{ 0x0009, 0x00ec, 0, VR::SL, VM::M1, "" },
{ 0x0011, 0x0001, 0, VR::SQ, VM::M1, "" },
{ 0x0011, 0x0018, 0, VR::OB, VM::M1, "" },
{ 0x0013, 0x0001, 0, VR::SQ, VM::M1, "" },
{ 0x0017, 0x0001, 0, VR::UI, VM::M1, "correction_cal_id" },
{ 0x0017, 0x0002, 0, VR::SH, VM::M1, "compatible_version" },
{ 0x0017, 0x0003, 0, VR::SH, VM::M1, "software_version" },
{ 0x0017, 0x0004, 0, VR::DT, VM::M1, "cal_datetime" },
{ 0x0017, 0x0005, 0, VR::LO, VM::M1, "cal_description" },
{ 0x0017, 0x0006, 0, VR::SL, VM::M1, "cal_type" },
{ 0x0017, 0x0007, 0, VR::ST, VM::M1, "where_is_corr" },
{ 0x0017, 0x0008, 0, VR::SL, VM::M1, "corr_file_size" },
{ 0x0017, 0x0009, 0, VR::LO, VM::M1, "scan_id" },
{ 0x0017, 0x000a, 0, VR::DT, VM::M1, "scan_datetime" },
{ 0x0017, 0x000b, 0, VR::LO, VM::M1, "norm_2d_cal_id" },
{ 0x0017, 0x000c, 0, VR::SH, VM::M1, "hosp_identifier" },
{ 0x0017, 0x000d, 0, VR::SL, VM::M1, "archived" },
{ 0x0019, 0x0001, 0, VR::UI, VM::M1, "wc_cal_id" },
{ 0x0019, 0x0002, 0, VR::SH, VM::M1, "compatible_version" },
{ 0x0019, 0x0003, 0, VR::SH, VM::M1, "software_version" },
{ 0x0019, 0x0004, 0, VR::DT, VM::M1, "cal_datetime" },
{ 0x0019, 0x0005, 0, VR::SL, VM::M1, "cal_type" },
{ 0x0019, 0x0006, 0, VR::LO, VM::M1, "cal_description" },
{ 0x0019, 0x0007, 0, VR::LO, VM::M1, "cal_hardware" },
{ 0x0019, 0x0008, 0, VR::OB, VM::M1, "coefficients" },
{ 0x0019, 0x0009, 0, VR::FL, VM::M1, "activity_factor_hr" },
{ 0x0019, 0x000a, 0, VR::FL, VM::M1, "activity_factor_hs" },
{ 0x0019, 0x000b, 0, VR::FL, VM::M1, "activity_factor_3d" },
{ 0x0019, 0x000c, 0, VR::LO, VM::M1, "scan_id" },
{ 0x0019, 0x000d, 0, VR::DT, VM::M1, "scan_datetime" },
{ 0x0019, 0x000e, 0, VR::SH, VM::M1, "hosp_identifier" },
{ 0x0019, 0x000f, 0, VR::FL, VM::M1, "meas_activity" },
{ 0x0019, 0x0010, 0, VR::DT, VM::M1, "meas_datetime" },
{ 0x0019, 0x0011, 0, VR::SL, VM::M1, "axial_filter_3d" },
{ 0x0019, 0x0012, 0, VR::FL, VM::M1, "axial_cutoff_3d" },
{ 0x0019, 0x0013, 0, VR::SL, VM::M1, "default_flag" },
{ 0x0019, 0x0014, 0, VR::SL, VM::M1, "archived" },
{ 0x0019, 0x0015, 0, VR::SL, VM::M1, "wc_cal_rec_method" },
{ 0x0019, 0x0016, 0, VR::SL, VM::M1, "activity_factor_2d" },
{ 0x0019, 0x0017, 0, VR::SL, VM::M1, "isotope" },
{ 0x0021, 0x0001, 0, VR::US, VM::M1, "raw_data_type" },
{ 0x0021, 0x0002, 0, VR::UL, VM::M1, "raw_data_size" },
{ 0x0023, 0x0001, 0, VR::OB, VM::M1, "raw_data_blob" },
{ 0x5001, 0x0001, 0, VR::UI, VM::M1, "CurveID" },
{ 0x5001, 0x0002, 0, VR::SH, VM::M1, "CurveCompatibleVersion" },
{ 0x5001, 0x0003, 0, VR::SH, VM::M1, "CurveSoftwareVersion" },
{ 0x5001, 0x0004, 0, VR::SL, VM::M1, "StatisticsType" },
{ 0x5001, 0x0005, 0, VR::LT, VM::M1, "HowDerived" },
{ 0x5001, 0x0006, 0, VR::SL, VM::M1, "HowDerivedSize" },
{ 0x5001, 0x0007, 0, VR::SL, VM::M1, "MultiPatient" },
{ 0x5001, 0x0008, 0, VR::SL, VM::M1, "Deadtime" },
{ 0x5003, 0x0001, 0, VR::SQ, VM::M1, "GraphSequence" },
{ 0x5003, 0x0002, 0, VR::UI, VM::M1, "GraphID" },
{ 0x5003, 0x0003, 0, VR::SH, VM::M1, "GraphCompatibleVersion" },
{ 0x5003, 0x0004, 0, VR::SH, VM::M1, "GraphSoftwareVersion" },
{ 0x5003, 0x0005, 0, VR::LO, VM::M1, "Title" },
{ 0x5003, 0x0006, 0, VR::DT, VM::M1, "GraphDateTime" },
{ 0x5003, 0x0007, 0, VR::ST, VM::M1, "GraphDescription" },
{ 0x5003, 0x0008, 0, VR::LO, VM::M1, "TitleFontName" },
{ 0x5003, 0x0009, 0, VR::SH, VM::M1, "TitleFontSize" },
{ 0x5003, 0x000a, 0, VR::LO, VM::M1, "Footer" },
{ 0x5003, 0x000b, 0, VR::SH, VM::M1, "FooterFontSize" },
{ 0x5003, 0x000c, 0, VR::LO, VM::M1, "ForegroundColor" },
{ 0x5003, 0x000d, 0, VR::LO, VM::M1, "BackgroundColor" },
{ 0x5003, 0x000e, 0, VR::SL, VM::M1, "GraphBorder" },
{ 0x5003, 0x000f, 0, VR::SL, VM::M1, "GraphWidth" },
{ 0x5003, 0x0010, 0, VR::SL, VM::M1, "GraphHeight" },
{ 0x5003, 0x0011, 0, VR::SL, VM::M1, "Grid" },
{ 0x5003, 0x0012, 0, VR::LO, VM::M1, "LabelFontName" },
{ 0x5003, 0x0013, 0, VR::SH, VM::M1, "LabelFontSize" },
{ 0x5003, 0x0014, 0, VR::LO, VM::M1, "AxesColor" },
{ 0x5003, 0x0015, 0, VR::LO, VM::M1, "XAxisLabel" },
{ 0x5003, 0x0016, 0, VR::SL, VM::M1, "XAxisUnits" },
{ 0x5003, 0x0017, 0, VR::FL, VM::M1, "XMajorTics" },
{ 0x5003, 0x0018, 0, VR::FL, VM::M1, "XAxisMin" },
{ 0x5003, 0x0019, 0, VR::FL, VM::M1, "XAxisMax" },
{ 0x5003, 0x001a, 0, VR::LO, VM::M1, "YAxisLabel" },
{ 0x5003, 0x001b, 0, VR::SL, VM::M1, "YAxisUnits" },
{ 0x5003, 0x001c, 0, VR::FL, VM::M1, "YMajorTics" },
{ 0x5003, 0x001d, 0, VR::FL, VM::M1, "YAxisMin" },
{ 0x5003, 0x001e, 0, VR::FL, VM::M1, "YAxisMax" },
{ 0x5003, 0x001f, 0, VR::LO, VM::M1, "LegendFontName" },
{ 0x5003, 0x0020, 0, VR::SH, VM::M1, "LegendFontSize" },
{ 0x5003, 0x0021, 0, VR::SL, VM::M1, "LegendLocationX" },
{ 0x5003, 0x0022, 0, VR::SL, VM::M1, "LegendLocationY" },
{ 0x5003, 0x0023, 0, VR::SL, VM::M1, "LegendWidth" },
{ 0x5003, 0x0024, 0, VR::SL, VM::M1, "LegendHeight" },
{ 0x5003, 0x0025, 0, VR::SL, VM::M1, "LegendBorder" },
{ 0x5003, 0x0026, 0, VR::SL, VM::M1, "MultiPatient" },
{ 0x5005, 0x0001, 0, VR::SQ, VM::M1, "CurvePresentationSequence" },
{ 0x5005, 0x0002, 0, VR::UI, VM::M1, "CurvePresentationID" },
{ 0x5005, 0x0003, 0, VR::UI, VM::M1, "GraphID" },
{ 0x5005, 0x0004, 0, VR::UI, VM::M1, "CurveID" },
{ 0x5005, 0x0005, 0, VR::SH, VM::M1, "CurvePresentationCompatibleVersion" },
{ 0x5005, 0x0006, 0, VR::SH, VM::M1, "CurvePresentationSoftwareVersion" },
{ 0x5005, 0x0007, 0, VR::LO, VM::M1, "CurveLabel" },
{ 0x5005, 0x0008, 0, VR::LO, VM::M1, "Color" },
{ 0x5005, 0x0009, 0, VR::SL, VM::M1, "LineType" },
{ 0x5005, 0x000a, 0, VR::SL, VM::M1, "LineWidth" },
{ 0x5005, 0x000b, 0, VR::SL, VM::M1, "PointSymbol" },
{ 0x5005, 0x000c, 0, VR::SL, VM::M1, "PointSymbolDim" },
{ 0x5005, 0x000d, 0, VR::LO, VM::M1, "PointColor" },
};

unsigned short Dict177TagHashTable[] = {
   84,    93,   102,   111,   118,   127,   136,   145,   152,   161,
  170,   179,   188,   197,   206,   215,   224,   237,   248,   261,
  272,   283,   292,   303,   312,   321,   328,   339,   350,   361,
  372,   383,   394,   403,   410,   419,   428,   435,   442,   449,
  456,   463,   470,   477,   484,   491,   498,   505,   512,   519,
  526,   539,   550,   563,   574,   587,   598,   611,   624,   635,
  648,   657,   666,   675,   684,   695,   704,   713,   722,   731,
  740,   749,   758,   767,   776,   783,   790,   797,   804,   811,
  818,   825,   830,     0,     4,     8,     9,    90,    91,   172,
  173,   317,    34,     4,     7,     8,    91,    92,   171,   172,
  316,    33,     4,    10,    11,    92,    93,   162,   163,   315,
   32,     3,     9,    10,    93,    94,   161,   162,     4,    12,
   13,    94,    95,   160,   161,   321,    38,     4,    11,    12,
   79,    80,   159,   160,   320,    37,     4,    14,    15,    80,
   81,   166,   167,   319,    36,     3,    13,    14,    81,    82,
  165,   166,     4,     0,     1,    82,    83,   164,   165,   266,
   17,     4,    83,    84,   163,   164,   235,    24,   265,    16,
    4,     2,     3,    84,    85,   184,   187,   268,    19,     4,
    1,     2,    85,    86,   183,   186,   267,    18,     4,     4,
    5,    86,    87,   182,   185,   270,    21,     4,     3,     4,
  103,   104,   181,   184,   269,    20,     4,     6,     7,   104,
  105,   188,   191,   272,    23,     4,     5,     6,   105,   106,
  187,   190,   271,    22,     6,    24,    25,   106,   107,   186,
  189,   234,     1,   243,     7,   258,     9,     5,    23,    24,
  107,   108,   185,   188,   242,     6,   257,     8,     6,    26,
   27,   108,   109,   176,   179,   236,     1,   241,     5,   260,
   11,     5,    25,    26,   109,   110,   175,   178,   240,     4,
  259,    10,     5,    28,    29,   110,   111,   174,   177,   239,
    3,   262,    13,     4,    27,    28,    95,    96,   238,     2,
  261,    12,     5,    30,    31,    96,    97,   180,   183,   237,
    1,   264,    15,     4,    29,    30,    97,    98,   179,   182,
  263,    14,     4,    16,    17,    98,    99,   178,   181,   250,
    1,     3,    15,    16,    99,   100,   177,   180,     5,    18,
   19,   100,   101,   199,   202,   249,    13,   252,     3,     5,
   17,    18,   101,   102,   200,   203,   248,    12,   251,     2,
    5,    20,    21,   102,   103,   197,   200,   247,    11,   254,
    5,     5,    19,    20,   119,   120,   198,   201,   246,    10,
  253,     4,     5,    22,    23,   120,   121,   203,   206,   245,
    9,   256,     7,     5,    21,    22,   121,   122,   204,   207,
  244,     8,   255,     6,     4,    40,    41,   122,   123,   201,
  204,   273,     1,     3,    39,    40,   123,   124,   202,   205,
    4,    42,    43,   124,   125,   191,   194,   275,     1,     4,
   41,    42,   125,   126,   192,   195,   274,     2,     3,    44,
   45,   126,   127,   189,   192,     3,    43,    44,   111,   112,
  190,   193,     3,    46,    47,   112,   113,   195,   198,     3,
   45,    46,   113,   114,   196,   199,     3,    32,    33,   114,
  115,   193,   196,     3,    31,    32,   115,   116,   194,   197,
    3,    34,    35,   116,   117,   215,   218,     3,    33,    34,
  117,   118,   216,   219,     3,    36,    37,   118,   119,   213,
  216,     3,    35,    36,   138,   139,   214,   217,     3,    38,
   39,   137,   138,   219,   222,     3,    37,    38,   136,   137,
  220,   223,     3,    56,    57,   135,   136,   217,   220,     3,
   55,    56,   142,   143,   218,   221,     6,    58,    59,   141,
  142,   207,   210,   276,     1,   286,     3,   326,     5,     5,
   57,    58,   140,   141,   208,   211,   285,     2,   325,     4,
    6,    60,    61,   139,   140,   205,   208,   278,     3,   284,
    1,   328,     7,     5,    59,    60,   130,   131,   206,   209,
  277,     2,   327,     6,     6,    62,    63,   129,   130,   211,
  214,   280,     5,   290,     7,   322,     1,     5,    61,    62,
  128,   129,   212,   215,   279,     4,   289,     6,     6,    48,
   49,   127,   128,   209,   212,   282,     7,   288,     5,   324,
    3,     6,    47,    48,   134,   135,   210,   213,   281,     6,
  287,     4,   323,     2,     5,    50,    51,   133,   134,   231,
  234,   294,    11,   334,    13,     6,    49,    50,   132,   133,
  232,   235,   283,     8,   293,    10,   333,    12,     4,    52,
   53,   131,   132,   229,   232,   292,     9,     4,    51,    52,
  154,   155,   230,   233,   291,     8,     4,    54,    55,   153,
  154,   298,    15,   330,     9,     4,    53,    54,   152,   153,
  297,    14,   329,     8,     5,    71,    72,   151,   152,   233,
  236,   296,    13,   332,    11,     4,    72,    73,   158,   159,
  295,    12,   331,    10,     4,    73,    74,   157,   158,   223,
  226,   302,    19,     4,    74,    75,   156,   157,   224,   227,
  301,    18,     4,    75,    76,   155,   156,   221,   224,   300,
   17,     4,    76,    77,   146,   147,   222,   225,   299,    16,
    4,    77,    78,   145,   146,   227,   230,   306,    23,     4,
   78,    79,   144,   145,   228,   231,   305,    22,     4,    63,
   64,   143,   144,   225,   228,   304,    21,     4,    64,    65,
  150,   151,   226,   229,   303,    20,     3,    65,    66,   149,
  150,   310,    27,     3,    66,    67,   148,   149,   309,    26,
    3,    67,    68,   147,   148,   308,    25,     3,    68,    69,
  170,   171,   307,    24,     3,    69,    70,   169,   170,   314,
   31,     3,    70,    71,   168,   169,   313,    30,     3,    87,
   88,   167,   168,   312,    29,     2,    88,    89,   311,    28,
    3,    89,    90,   173,   174,   318,    35,
};

vtkDICOMDictionary::Dict Dict177Data = {
"GEMS_PETD_01",
83,
335,
Dict177TagHashTable,
Dict177Contents
};

// ----- ISI -----

DictEntry Dict178Contents[] = {
{ 0x0009, 0x0001, 0, VR::UN, VM::M1, "SIENETGeneralPurposeIMGEF" },
};

unsigned short Dict178TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict178Data = {
"ISI",
1,
1,
Dict178TagHashTable,
Dict178Contents
};

// ----- GEMS_DRS_1 -----

DictEntry Dict179Contents[] = {
{ 0x0037, 0x0010, 0, VR::LO, VM::M1, "ReferringDepartment" },
{ 0x0037, 0x0020, 0, VR::US, VM::M1, "ScreenNumber" },
{ 0x0037, 0x0040, 0, VR::SH, VM::M1, "LeftOrientation" },
{ 0x0037, 0x0042, 0, VR::SH, VM::M1, "RightOrientation" },
{ 0x0037, 0x0050, 0, VR::CS, VM::M1, "Inversion" },
{ 0x0037, 0x0060, 0, VR::US, VM::M1, "DSA" },
};

unsigned short Dict179TagHashTable[] = {
    2,     0,     6,     0,    16,     1,    32,     2,    64,     3,
   66,     4,    80,     5,    96,
};

vtkDICOMDictionary::Dict Dict179Data = {
"GEMS_DRS_1",
1,
6,
Dict179TagHashTable,
Dict179Contents
};

// ----- TOSHIBA MDW NON-IMAGE -----

DictEntry Dict180Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "NonImageHeaderType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "NonImageHeaderVersion" },
{ 0x0029, 0x0020, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict180TagHashTable[] = {
    2,     0,     3,     0,     8,     1,     9,     2,    32,
};

vtkDICOMDictionary::Dict Dict180Data = {
"TOSHIBA MDW NON-IMAGE",
1,
3,
Dict180TagHashTable,
Dict180Contents
};

// ----- SIEMENS MED OCS PUBLIC RT PLAN ATTRIBUTES -----

DictEntry Dict181Contents[] = {
{ 0x0039, 0x0001, 0, VR::UT, VM::M1, "ExternalAttributes" },
};

unsigned short Dict181TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict181Data = {
"SIEMENS MED OCS PUBLIC RT PLAN ATTRIBUTES",
1,
1,
Dict181TagHashTable,
Dict181Contents
};

// ----- DR Systems, Inc. -----

DictEntry Dict182Contents[] = {
{ 0x4453, 0x0001, 0, VR::LO, VM::M1, "ExamID" },
{ 0x4453, 0x0002, 0, VR::LO, VM::M1, "ImageType" },
{ 0x4453, 0x0004, 0, VR::LO, VM::M1, "FileType" },
{ 0x4453, 0x0005, 0, VR::LO, VM::M1, "FileSuffix" },
{ 0x4453, 0x000A, 0, VR::LO, VM::M1, "AnnotationType" },
{ 0x4453, 0x000C, 0, VR::SQ, VM::M1, "OriginalInstanceUIDSequence" },
};

unsigned short Dict182TagHashTable[] = {
    2,     0,     6,     0,     1,     1,     2,     2,     4,     3,
    5,     4,    10,     5,    12,
};

vtkDICOMDictionary::Dict Dict182Data = {
"DR Systems, Inc.",
1,
6,
Dict182TagHashTable,
Dict182Contents
};

// ----- SCHICK TECHNOLOGIES - Change Item Creator ID -----

DictEntry Dict183Contents[] = {
{ 0x0021, 0x0001, 0, VR::UI, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0003, 0, VR::DT, VM::M1, "" },
{ 0x0021, 0x0004, 0, VR::PN, VM::M1, "" },
{ 0x0021, 0x0005, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict183TagHashTable[] = {
    2,     0,     5,     0,     1,     1,     2,     2,     3,     3,
    4,     4,     5,
};

vtkDICOMDictionary::Dict Dict183Data = {
"SCHICK TECHNOLOGIES - Change Item Creator ID",
1,
5,
Dict183TagHashTable,
Dict183Contents
};

// ----- SIEMENS AX INSPACE_EP -----

DictEntry Dict184Contents[] = {
{ 0x0009, 0x0050, 0, VR::UI, VM::M1, "" },
{ 0x0009, 0x0051, 0, VR::UI, VM::M1, "" },
};

unsigned short Dict184TagHashTable[] = {
    2,     0,     2,     0,    80,     1,    81,
};

vtkDICOMDictionary::Dict Dict184Data = {
"SIEMENS AX INSPACE_EP",
1,
2,
Dict184TagHashTable,
Dict184Contents
};

// ----- AGFA-AG_HPState -----

DictEntry Dict185Contents[] = {
{ 0x0071, 0x0018, 0, VR::SQ, VM::M1, "" },
{ 0x0071, 0x0019, 0, VR::SQ, VM::M1, "" },
{ 0x0071, 0x001a, 0, VR::SQ, VM::M1, "" },
{ 0x0071, 0x001c, 0, VR::SQ, VM::M1, "" },
{ 0x0071, 0x001e, 0, VR::SQ, VM::M1, "" },
{ 0x0071, 0x0020, 0, VR::FL, VM::M1TN, "" },
{ 0x0071, 0x0021, 0, VR::FD, VM::M1TN, "" },
{ 0x0071, 0x0022, 0, VR::FD, VM::M1TN, "" },
{ 0x0071, 0x0023, 0, VR::FD, VM::M1TN, "" },
{ 0x0071, 0x0024, 0, VR::FD, VM::M1, "" },
{ 0x0073, 0x0023, 0, VR::SH, VM::M1, "" },
{ 0x0073, 0x0024, 0, VR::SQ, VM::M1, "" },
{ 0x0073, 0x0028, 0, VR::SQ, VM::M1, "" },
{ 0x0073, 0x0080, 0, VR::FL, VM::M1, "" },
{ 0x0075, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0087, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0087, 0x0002, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict185TagHashTable[] = {
    5,    20,    27,    38,     0,     7,     0,    24,     3,    28,
    5,    32,     9,    36,    13,   128,    14,    16,    15,     1,
    3,     1,    25,     6,    33,    10,    35,     5,     2,    26,
    4,    30,     7,    34,    11,    36,    12,    40,     2,     8,
   35,    16,     2,
};

vtkDICOMDictionary::Dict Dict185Data = {
"AGFA-AG_HPState",
4,
17,
Dict185TagHashTable,
Dict185Contents
};

// ----- SPI-P-Private_ICS Release 1 -----

DictEntry Dict186Contents[] = {
{ 0x0019, 0x0030, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0031, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x000d, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x000e, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x000f, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0012, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x001b, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x001c, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x001d, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x001e, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0021, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x004c, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x004d, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x004e, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x004f, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x0050, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x0051, 0, VR::FD, VM::M1, "" },
{ 0x0029, 0x0067, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0068, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x006A, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x006B, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0072, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0091, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict186TagHashTable[] = {
    7,    20,    31,    38,    45,    54,     0,     6,     2,    13,
   15,    78,    17,    80,    21,   106,    23,   114,    24,   145,
    5,    10,    30,    16,    79,    18,    81,    19,   103,    22,
  107,     3,     4,    15,     7,    27,    12,    33,     3,     3,
   14,     5,    16,    11,    32,     4,     1,    49,     9,    29,
   13,    76,    20,   104,     4,     0,    48,     6,    18,     8,
   28,    14,    77,
};

vtkDICOMDictionary::Dict Dict186Data = {
"SPI-P-Private_ICS Release 1",
6,
25,
Dict186TagHashTable,
Dict186Contents
};

// ----- RadWorksTBR -----

DictEntry Dict187Contents[] = {
{ 0x3111, 0x0002, 0, VR::CS, VM::M1, "Compression Type" },
{ 0x3111, 0x00FF, 0, VR::SQ, VM::M1, "QueryResult" },
};

unsigned short Dict187TagHashTable[] = {
    2,     0,     2,     0,     2,     1,   255,
};

vtkDICOMDictionary::Dict Dict187Data = {
"RadWorksTBR",
1,
2,
Dict187TagHashTable,
Dict187Contents
};

// ----- SIEMENS SYNGO REGISTRATION -----

DictEntry Dict188Contents[] = {
{ 0x0071, 0x0020, 0, VR::SQ, VM::M1, "RegisteredImageSequence" },
{ 0x0071, 0x0021, 0, VR::CS, VM::M1, "RegistrationIsValidatedFlag" },
};

unsigned short Dict188TagHashTable[] = {
    2,     0,     2,     0,    32,     1,    33,
};

vtkDICOMDictionary::Dict Dict188Data = {
"SIEMENS SYNGO REGISTRATION",
1,
2,
Dict188TagHashTable,
Dict188Contents
};

// ----- AMI Sequence AnnotElements_01 -----

DictEntry Dict189Contents[] = {
{ 0x3105, 0x0010, 0, VR::DS, VM::M1TN, "AnnotationElementPosition" },
{ 0x3105, 0x0020, 0, VR::LT, VM::M1, "AnnotationElementText" },
};

unsigned short Dict189TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    32,
};

vtkDICOMDictionary::Dict Dict189Data = {
"AMI Sequence AnnotElements_01",
1,
2,
Dict189TagHashTable,
Dict189Contents
};

// ----- AMI ImageTransform_01 -----

DictEntry Dict190Contents[] = {
{ 0x3107, 0x0010, 0, VR::DS, VM::M1TN, "Transformation Matrix" },
{ 0x3107, 0x0020, 0, VR::DS, VM::M1, "CenterOffset" },
{ 0x3107, 0x0030, 0, VR::DS, VM::M1, "Magnification" },
{ 0x3107, 0x0040, 0, VR::CS, VM::M1, "MagnificationType" },
{ 0x3107, 0x0050, 0, VR::DS, VM::M1, "DisplayedArea" },
{ 0x3107, 0x0060, 0, VR::DS, VM::M1, "CalibrationFactor" },
};

unsigned short Dict190TagHashTable[] = {
    2,     0,     6,     0,    16,     1,    32,     2,    48,     3,
   64,     4,    80,     5,    96,
};

vtkDICOMDictionary::Dict Dict190Data = {
"AMI ImageTransform_01",
1,
6,
Dict190TagHashTable,
Dict190Contents
};

// ----- SECTRA_ImageInfo_01 -----

DictEntry Dict191Contents[] = {
{ 0x0029, 0x0001, 0, VR::OB, VM::M1, "ImageInfo" },
{ 0x0029, 0x0002, 0, VR::CS, VM::M1, "Marking" },
{ 0x0029, 0x0003, 0, VR::LO, VM::M1, "NoDecompression" },
{ 0x0029, 0x0004, 0, VR::OB, VM::M1, "ImageInfoNew" },
};

unsigned short Dict191TagHashTable[] = {
    2,     0,     4,     0,     1,     1,     2,     2,     3,     3,
    4,
};

vtkDICOMDictionary::Dict Dict191Data = {
"SECTRA_ImageInfo_01",
1,
4,
Dict191TagHashTable,
Dict191Contents
};

// ----- HMC - CT - ID -----

DictEntry Dict192Contents[] = {
{ 0x0009, 0x0000, 0, VR::OB, VM::M1, "ImageIDInformationPatientNameID" },
{ 0x0009, 0x0001, 0, VR::OB, VM::M1, "ImageIDInformationPatientComment" },
};

unsigned short Dict192TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict192Data = {
"HMC - CT - ID",
1,
2,
Dict192TagHashTable,
Dict192Contents
};

// ----- VEPRO DICOM RECEIVE DATA 1.0 -----

DictEntry Dict193Contents[] = {
{ 0x0059, 0x0040, 0, VR::DA, VM::M1, "ReceiveDate" },
{ 0x0059, 0x0041, 0, VR::TM, VM::M1, "ReceiveTime" },
{ 0x0059, 0x0042, 0, VR::ST, VM::M1, "ReceiveNode" },
{ 0x0059, 0x0043, 0, VR::ST, VM::M1, "ReceiveApplication" },
{ 0x0059, 0x0050, 0, VR::ST, VM::M1, "ReceiveLocalComputer" },
{ 0x0059, 0x0051, 0, VR::ST, VM::M1, "ReceiveLocalAETitle" },
{ 0x0059, 0x0060, 0, VR::ST, VM::M1, "ReceiveRemoteComputer" },
{ 0x0059, 0x0061, 0, VR::ST, VM::M1, "ReceiveRemoteAETitle" },
{ 0x0059, 0x0070, 0, VR::UI, VM::M1, "ReceiveOriginalTransferSyntax" },
};

unsigned short Dict193TagHashTable[] = {
    3,    12,     0,     4,     1,    65,     3,    67,     5,    81,
    7,    97,     5,     0,    64,     2,    66,     4,    80,     6,
   96,     8,   112,
};

vtkDICOMDictionary::Dict Dict193Data = {
"VEPRO DICOM RECEIVE DATA 1.0",
2,
9,
Dict193TagHashTable,
Dict193Contents
};

// ----- ADAC_IMG -----

DictEntry Dict194Contents[] = {
{ 0x0019, 0x0002, 0, VR::IS, VM::M1, "ADACPegasysFileSize" },
{ 0x0019, 0x0021, 0, VR::US, VM::M1, "NumberOfADACHeaders" },
{ 0x0019, 0x0041, 0, VR::IS, VM::M1TN, "ADACHeaderImageSize" },
{ 0x0019, 0x0061, 0, VR::OB, VM::M1, "ADACPegasysHeaders" },
};

unsigned short Dict194TagHashTable[] = {
    2,     0,     4,     0,     2,     1,    33,     2,    65,     3,
   97,
};

vtkDICOMDictionary::Dict Dict194Data = {
"ADAC_IMG",
1,
4,
Dict194TagHashTable,
Dict194Contents
};

// ----- SIEMENS MEDCOM HEADER2 -----

DictEntry Dict195Contents[] = {
{ 0x0029, 0x0060, 0, VR::LO, VM::M1, "SeriesWorkFlowStatus" },
};

unsigned short Dict195TagHashTable[] = {
    2,     0,     1,     0,    96,
};

vtkDICOMDictionary::Dict Dict195Data = {
"SIEMENS MEDCOM HEADER2",
1,
1,
Dict195TagHashTable,
Dict195Contents
};

// ----- SIEMENS CSA HEADER -----

DictEntry Dict196Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "CSAImageHeaderType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "CSAImageHeaderVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "CSAImageHeaderInfo" },
{ 0x0029, 0x0018, 0, VR::CS, VM::M1, "CSASeriesHeaderType" },
{ 0x0029, 0x0019, 0, VR::LO, VM::M1, "CSASeriesHeaderVersion" },
{ 0x0029, 0x0020, 0, VR::OB, VM::M1, "CSASeriesHeaderInfo" },
};

unsigned short Dict196TagHashTable[] = {
    2,     0,     6,     0,     8,     1,     9,     2,    16,     3,
   24,     4,    25,     5,    32,
};

vtkDICOMDictionary::Dict Dict196Data = {
"SIEMENS CSA HEADER",
1,
6,
Dict196TagHashTable,
Dict196Contents
};

// ----- MeVis eD: Geometry Information -----

DictEntry Dict197Contents[] = {
{ 0x0021, 0x0010, 0, VR::UN, VM::M1, "GeometryScannerOrigin" },
};

unsigned short Dict197TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict197Data = {
"MeVis eD: Geometry Information",
1,
1,
Dict197TagHashTable,
Dict197Contents
};

// ----- SIEMENS SYNGO 3D FUSION MATRIX -----

DictEntry Dict198Contents[] = {
{ 0x0029, 0x0008, 0, VR::UI, VM::M1, "ObjectSeriesInstanceUID" },
{ 0x0029, 0x0009, 0, VR::UI, VM::M1, "ModelSeriesInstanceUID" },
{ 0x0029, 0x0010, 0, VR::UI, VM::M1, "MatrixReferencedSeriesInstanceUID" },
};

unsigned short Dict198TagHashTable[] = {
    2,     0,     3,     0,     8,     1,     9,     2,    16,
};

vtkDICOMDictionary::Dict Dict198Data = {
"SIEMENS SYNGO 3D FUSION MATRIX",
1,
3,
Dict198TagHashTable,
Dict198Contents
};

// ----- GEMS_3D_INTVL_01 -----

DictEntry Dict199Contents[] = {
{ 0x0023, 0x0001, 0, VR::SQ, VM::M1, "XRayMarkerSequence" },
{ 0x0023, 0x0002, 0, VR::SH, VM::M1, "MarkerID" },
{ 0x0023, 0x0003, 0, VR::CS, VM::M1, "MarkerType" },
{ 0x0023, 0x0004, 0, VR::FL, VM::M1, "MarkerSize" },
{ 0x0023, 0x0005, 0, VR::US, VM::M3, "MarkerColorCIELabValue" },
{ 0x0023, 0x0006, 0, VR::LO, VM::M1, "MarkerLabel" },
{ 0x0023, 0x0007, 0, VR::CS, VM::M1, "MarkerVisibleState" },
{ 0x0023, 0x0008, 0, VR::LO, VM::M1, "MarkerDescription" },
{ 0x0023, 0x0010, 0, VR::SQ, VM::M1, "MarkerPointsSequence" },
{ 0x0023, 0x0011, 0, VR::SH, VM::M1, "MarkerPointID" },
{ 0x0023, 0x0012, 0, VR::FL, VM::M3, "MarkerPointPosition" },
{ 0x0023, 0x0013, 0, VR::FL, VM::M1, "MarkerPointSize" },
{ 0x0023, 0x0014, 0, VR::US, VM::M3, "MarkerPointColorCIELabValue" },
{ 0x0023, 0x0016, 0, VR::CS, VM::M1, "MarkerPointVisibleState" },
{ 0x0023, 0x0017, 0, VR::IS, VM::M1, "MarkerPointOrder" },
{ 0x0023, 0x0018, 0, VR::FL, VM::M3, "VolumeManualRegistration" },
{ 0x0023, 0x0020, 0, VR::IS, VM::M1TN, "VolumesThreshold" },
{ 0x0023, 0x0025, 0, VR::CS, VM::M1, "CutPlaneActivationFlag" },
{ 0x0023, 0x0026, 0, VR::IS, VM::M1, "CutPlanePositionValue" },
{ 0x0023, 0x0027, 0, VR::FL, VM::M3, "CutPlaneNormalValue" },
{ 0x0023, 0x0028, 0, VR::FL, VM::M1, "VolumeScalingFactor" },
{ 0x0023, 0x0029, 0, VR::FL, VM::M1, "ROIToTableTopDistance" },
{ 0x0023, 0x0030, 0, VR::IS, VM::M1TN, "DRRThreshold" },
{ 0x0023, 0x0031, 0, VR::FL, VM::M3, "VolumeTablePosition" },
{ 0x0023, 0x0032, 0, VR::IS, VM::M1, "RenderingMode" },
{ 0x0023, 0x0033, 0, VR::IS, VM::M1, "ThreeDObjectOpacity" },
{ 0x0023, 0x0034, 0, VR::IS, VM::M1, "InvertImage" },
{ 0x0023, 0x0035, 0, VR::IS, VM::M1, "EnhanceFull" },
{ 0x0023, 0x0036, 0, VR::FL, VM::M1, "Zoom" },
{ 0x0023, 0x0037, 0, VR::IS, VM::M2, "Roam" },
{ 0x0023, 0x0038, 0, VR::IS, VM::M1, "WindowLevel" },
{ 0x0023, 0x0039, 0, VR::IS, VM::M1, "WindowWidth" },
{ 0x0023, 0x0040, 0, VR::CS, VM::M1, "BMCSetting" },
{ 0x0023, 0x0041, 0, VR::CS, VM::M1, "BackViewSetting" },
{ 0x0023, 0x0042, 0, VR::CS, VM::M1TN, "SubVolumeVisibility" },
{ 0x0023, 0x0043, 0, VR::CS, VM::M1, "ThreeDLandmarksVisibility" },
{ 0x0023, 0x0044, 0, VR::CS, VM::M1, "AblationPointVisibility" },
};

unsigned short Dict199TagHashTable[] = {
   10,    19,    28,    35,    46,    53,    64,    73,    84,     0,
    4,     6,     7,    23,    49,    30,    56,    33,    65,     4,
    5,     6,    12,    20,    21,    41,    22,    48,     3,     4,
    5,    20,    40,    29,    55,     5,     3,     4,    11,    19,
   16,    32,    28,    54,    36,    68,     3,    10,    18,    19,
   39,    27,    53,     5,     2,     3,     9,    17,    15,    24,
   18,    38,    26,    52,     4,     1,     2,     8,    16,    17,
   37,    34,    66,     5,     0,     1,     7,     8,    14,    23,
   25,    51,    35,    67,     4,    13,    22,    24,    50,    31,
   57,    32,    64,
};

vtkDICOMDictionary::Dict Dict199Data = {
"GEMS_3D_INTVL_01",
9,
37,
Dict199TagHashTable,
Dict199Contents
};

// ----- Philips Imaging DD 002 -----

DictEntry Dict200Contents[] = {
{ 0x2001, 0x0001, 0, VR::US, VM::M1, "" },
{ 0x2001, 0x0002, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0013, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0014, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0015, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0016, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0017, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0018, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0019, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x001a, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x001b, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x001c, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x001d, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x001e, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x001f, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0020, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0021, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0022, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0023, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0024, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0025, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0026, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0027, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x2001, 0x0029, 0, VR::US, VM::M1, "" },
{ 0x2001, 0x002a, 0, VR::US, VM::M1, "" },
{ 0x2001, 0x002b, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x002c, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x002d, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x002e, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x002f, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0030, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0031, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0032, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0033, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0034, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0035, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0036, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0037, 0, VR::FD, VM::M1, "" },
{ 0x2001, 0x0039, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x003a, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x003b, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x003c, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x003d, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x003e, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x003f, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0040, 0, VR::SS, VM::M1, "" },
};

unsigned short Dict200TagHashTable[] = {
   12,    23,    32,    43,    52,    63,    72,    79,    90,    99,
  108,     0,     5,     2,    19,    11,    28,    24,    41,    33,
   50,    45,    63,     4,    14,    31,    23,    40,    36,    53,
   44,    62,     5,     4,    21,    13,    30,    26,    43,    35,
   52,    46,    64,     4,     3,    20,    16,    33,    25,    42,
   38,    55,     5,     0,     1,     6,    23,    15,    32,    28,
   45,    37,    54,     4,     5,    22,    18,    35,    27,    44,
   39,    57,     3,     8,    25,    17,    34,    30,    47,     5,
    1,     2,     7,    24,    20,    37,    29,    46,    41,    59,
    4,    10,    27,    19,    36,    32,    49,    40,    58,     4,
    9,    26,    22,    39,    31,    48,    43,    61,     4,    12,
   29,    21,    38,    34,    51,    42,    60,
};

vtkDICOMDictionary::Dict Dict200Data = {
"Philips Imaging DD 002",
11,
47,
Dict200TagHashTable,
Dict200Contents
};

// ----- KONICA1.0 -----

DictEntry Dict201Contents[] = {
{ 0x0031, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x0001, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0005, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x0008, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x0009, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x000a, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x000b, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x000c, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x000d, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x000e, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0010, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0011, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0012, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0013, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0014, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0015, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0016, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0017, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0018, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0019, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x001a, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x001b, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x001c, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x001d, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x001e, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x0020, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0021, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0022, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0023, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0024, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0025, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0026, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0027, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0028, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0029, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x002a, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x002b, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x002c, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x002d, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x002e, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x002f, 0, VR::SQ, VM::M1, "" },
{ 0x0031, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0031, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0033, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0034, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0035, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0036, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0037, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0038, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0039, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x003a, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x003b, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x003c, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x003d, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x003e, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x003f, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0040, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0041, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0042, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0045, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0046, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0047, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0048, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0049, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x004a, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x004b, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x004c, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x004d, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x004e, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x004f, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0050, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0051, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0053, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0054, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0055, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0056, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0057, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0058, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0059, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x005a, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x005b, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x005c, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0062, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0063, 0, VR::US, VM::M3, "" },
{ 0x0031, 0x006b, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0070, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0071, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x0072, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0073, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0074, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x0075, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0077, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0078, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0079, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x007a, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x007b, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x007c, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x007d, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x007e, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x007f, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0080, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0081, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0082, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0083, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0084, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0085, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0086, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0087, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0088, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0089, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x008a, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x008b, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x008c, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x008d, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x008e, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x008f, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0090, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0091, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x0092, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0093, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0094, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x0095, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00a1, 0, VR::IS, VM::M2, "" },
{ 0x0031, 0x00a2, 0, VR::IS, VM::M1, "" },
{ 0x0031, 0x00a5, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00a6, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00a7, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00a8, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00aa, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00ab, 0, VR::DA, VM::M1, "" },
{ 0x0031, 0x00ac, 0, VR::TM, VM::M1, "" },
{ 0x0031, 0x00ad, 0, VR::DA, VM::M1, "" },
{ 0x0031, 0x00ae, 0, VR::TM, VM::M1, "" },
{ 0x0031, 0x00b0, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00b1, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00b2, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00b3, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00b4, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00b5, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00b6, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00b7, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00b8, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x00b9, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x00ba, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00bc, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00be, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00bf, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00c0, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c1, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c2, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c3, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c4, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c5, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c6, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c7, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c8, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00c9, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00ca, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00cb, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00cc, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00cd, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00ce, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00cf, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00d0, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00d1, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00d2, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00d3, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00d4, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00d5, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00d6, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00d7, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00d8, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00d9, 0, VR::LO, VM::M1, "" },
{ 0x0031, 0x00da, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00db, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00dc, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00dd, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00de, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00df, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00e0, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00e1, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00e2, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00e3, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00e4, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00e5, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00e6, 0, VR::UN, VM::M1, "" },
{ 0x0031, 0x00f0, 0, VR::US, VM::M1, "" },
{ 0x0031, 0x00ff, 0, VR::SQ, VM::M1, "PrivateDataSequence" },
};

unsigned short Dict201TagHashTable[] = {
   49,    58,    69,    80,    87,    98,   107,   116,   125,   136,
  147,   156,   167,   176,   187,   194,   203,   214,   225,   236,
  245,   254,   261,   270,   281,   288,   295,   302,   309,   316,
  323,   330,   337,   346,   355,   366,   377,   386,   395,   404,
  413,   420,   429,   438,   449,   458,   467,   472,     0,     4,
    1,     1,    43,    49,    73,    80,   153,   194,     5,     0,
    0,    42,    48,    74,    81,   127,   162,   154,   195,     5,
   45,    51,    75,    82,   126,   161,   151,   192,   190,   240,
    3,    44,    50,    76,    83,   152,   193,     5,     2,     5,
   47,    53,    77,    84,   130,   167,   157,   198,     4,    46,
   52,    78,    85,   129,   166,   158,   199,     4,    49,    55,
   79,    86,   128,   165,   155,   196,     4,     3,     6,    48,
   54,    80,    87,   156,   197,     5,     5,     9,    51,    57,
   81,    88,   133,   171,   161,   202,     5,     4,     8,    50,
   56,    82,    89,   132,   170,   162,   203,     4,     7,    11,
   53,    59,    83,    90,   159,   200,     5,     6,    10,    52,
   58,    84,    91,   131,   168,   160,   201,     4,     9,    13,
   55,    61,    85,    92,   165,   206,     5,     8,    12,    54,
   60,   136,   174,   166,   207,   191,   255,     3,    57,    63,
  135,   173,   163,   204,     4,    10,    14,    56,    62,   134,
  172,   164,   205,     5,    27,    33,    58,    64,    89,   112,
  123,   147,   185,   226,     5,    26,    32,    59,    65,    90,
  113,   122,   146,   186,   227,     5,    29,    35,    60,    66,
   91,   114,   121,   145,   183,   224,     4,    28,    34,    92,
  115,   120,   144,   184,   225,     4,    31,    37,    61,    68,
   93,   116,   189,   230,     3,    30,    36,    62,    69,    94,
  117,     4,    33,    39,    63,    70,   125,   149,   187,   228,
    5,    32,    38,    64,    71,    95,   119,   124,   148,   188,
  229,     3,    35,    41,    65,    72,    96,   120,     3,    34,
   40,    66,    73,    97,   121,     3,    37,    43,    67,    74,
   98,   122,     3,    36,    42,    68,    75,    99,   123,     3,
   39,    45,    69,    76,   100,   124,     3,    38,    44,    70,
   77,   101,   125,     3,    41,    47,    71,    78,   102,   126,
    3,    40,    46,    72,    79,   103,   127,     4,    12,    17,
  107,   131,   140,   179,   169,   210,     4,    11,    16,   106,
  130,   139,   178,   170,   211,     5,    14,    19,    86,    98,
  105,   129,   138,   177,   167,   208,     5,    13,    18,    87,
   99,   104,   128,   137,   176,   168,   209,     4,    16,    21,
  111,   135,   144,   183,   173,   214,     4,    15,    20,   110,
  134,   143,   182,   174,   215,     4,    18,    23,   109,   133,
  142,   181,   171,   212,     4,    17,    22,   108,   132,   141,
  180,   172,   213,     3,    20,    25,   115,   139,   177,   218,
    4,    19,    24,   114,   138,   147,   186,   178,   219,     4,
   22,    27,   113,   137,   146,   185,   175,   216,     5,    21,
   26,    88,   107,   112,   136,   145,   184,   176,   217,     4,
   24,    29,   119,   143,   150,   191,   181,   222,     4,    23,
   28,   118,   142,   149,   190,   182,   223,     2,   117,   141,
  179,   220,     4,    25,    30,   116,   140,   148,   188,   180,
  221,
};

vtkDICOMDictionary::Dict Dict201Data = {
"KONICA1.0",
48,
192,
Dict201TagHashTable,
Dict201Contents
};

// ----- Applicare/Centricity Radiology Web/Version 1.0 -----

DictEntry Dict202Contents[] = {
{ 0x4109, 0x0001, 0, VR::SH, VM::M1, "MammographyLaterality" },
{ 0x4109, 0x0002, 0, VR::SH, VM::M1, "MammographyViewName" },
{ 0x4109, 0x0003, 0, VR::SH, VM::M1, "MammographyViewModifier" },
};

unsigned short Dict202TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,     3,
};

vtkDICOMDictionary::Dict Dict202Data = {
"Applicare/Centricity Radiology Web/Version 1.0",
1,
3,
Dict202TagHashTable,
Dict202Contents
};

// ----- SIEMENS Ultrasound S2000 -----

DictEntry Dict203Contents[] = {
{ 0x0021, 0x0000, 0, VR::US, VM::M1, "NipplePosition" },
{ 0x0021, 0x0001, 0, VR::US, VM::M1, "ABVSClipDerivedFromVolume" },
};

unsigned short Dict203TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict203Data = {
"SIEMENS Ultrasound S2000",
1,
2,
Dict203TagHashTable,
Dict203Contents
};

// ----- 1.2.840.113708.794.1.1.2.0 -----

DictEntry Dict204Contents[] = {
{ 0x0087, 0x0010, 0, VR::CS, VM::M1, "MediaType" },
{ 0x0087, 0x0020, 0, VR::CS, VM::M1, "MediaLocation" },
{ 0x0087, 0x0030, 0, VR::ST, VM::M1, "StorageFileID" },
{ 0x0087, 0x0040, 0, VR::DS, VM::M1, "StudyOrImageSizeInMB" },
{ 0x0087, 0x0050, 0, VR::IS, VM::M1, "EstimatedRetrieveTime" },
};

unsigned short Dict204TagHashTable[] = {
    2,     0,     5,     0,    16,     1,    32,     2,    48,     3,
   64,     4,    80,
};

vtkDICOMDictionary::Dict Dict204Data = {
"1.2.840.113708.794.1.1.2.0",
1,
5,
Dict204TagHashTable,
Dict204Contents
};

// ----- TOSHIBA MDW HEADER -----

DictEntry Dict205Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "ImageHeaderType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "ImageHeaderVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "ImageHeaderInfo" },
{ 0x0029, 0x0018, 0, VR::CS, VM::M1, "SeriesHeaderType" },
{ 0x0029, 0x0019, 0, VR::LO, VM::M1, "SeriesHeaderVersion" },
{ 0x0029, 0x0020, 0, VR::OB, VM::M1, "SeriesHeaderInfo" },
};

unsigned short Dict205TagHashTable[] = {
    2,     0,     6,     0,     8,     1,     9,     2,    16,     3,
   24,     4,    25,     5,    32,
};

vtkDICOMDictionary::Dict Dict205Data = {
"TOSHIBA MDW HEADER",
1,
6,
Dict205TagHashTable,
Dict205Contents
};

// ----- GEMS_IQTB_IDEN_47 -----

DictEntry Dict206Contents[] = {
{ 0x0047, 0x0002, 0, VR::UL, VM::M1, "" },
};

unsigned short Dict206TagHashTable[] = {
    2,     0,     1,     0,     2,
};

vtkDICOMDictionary::Dict Dict206Data = {
"GEMS_IQTB_IDEN_47",
1,
1,
Dict206TagHashTable,
Dict206Contents
};

// ----- GEMS_ACQU_01 -----

DictEntry Dict207Contents[] = {
{ 0x0009, 0x0024, 0, VR::DS, VM::M1, "" },
{ 0x0009, 0x0025, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x003e, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x003f, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x0042, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x0043, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x00f8, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x00fb, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0001, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::SL, VM::M1, "NumberOfCellsInDetector" },
{ 0x0019, 0x0003, 0, VR::DS, VM::M1, "CellNumberAtTheta" },
{ 0x0019, 0x0004, 0, VR::DS, VM::M1, "CellSpacing" },
{ 0x0019, 0x0005, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x000e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x000f, 0, VR::DS, VM::M1, "HorizontalFrameOfReference" },
{ 0x0019, 0x0011, 0, VR::SS, VM::M1, "SeriesContrast" },
{ 0x0019, 0x0012, 0, VR::SS, VM::M1, "LastPseq" },
{ 0x0019, 0x0013, 0, VR::SS, VM::M1, "StartNumberForBaseline" },
{ 0x0019, 0x0014, 0, VR::SS, VM::M1, "End NumberForBaseline" },
{ 0x0019, 0x0015, 0, VR::SS, VM::M1, "StartNumberForEnhancedScans" },
{ 0x0019, 0x0016, 0, VR::SS, VM::M1, "EndNumberForEnhancedScans" },
{ 0x0019, 0x0017, 0, VR::SS, VM::M1, "SeriesPlane" },
{ 0x0019, 0x0018, 0, VR::LO, VM::M1, "FirstScanRAS" },
{ 0x0019, 0x0019, 0, VR::DS, VM::M1, "FirstScanLocation" },
{ 0x0019, 0x001a, 0, VR::LO, VM::M1, "LastScanRAS" },
{ 0x0019, 0x001b, 0, VR::DS, VM::M1, "LastScanLocation" },
{ 0x0019, 0x001e, 0, VR::DS, VM::M1, "DisplayFieldOfView" },
{ 0x0019, 0x0020, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0022, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0023, 0, VR::DS, VM::M1, "TableSpeed" },
{ 0x0019, 0x0024, 0, VR::DS, VM::M1, "MidScanTime" },
{ 0x0019, 0x0025, 0, VR::SS, VM::M1, "MidScanFlag" },
{ 0x0019, 0x0026, 0, VR::SL, VM::M1, "TubeAzimuth" },
{ 0x0019, 0x0027, 0, VR::DS, VM::M1, "RotationSpeed" },
{ 0x0019, 0x002a, 0, VR::DS, VM::M1, "XrayOnPosition" },
{ 0x0019, 0x002b, 0, VR::DS, VM::M1, "XrayOffPosition" },
{ 0x0019, 0x002c, 0, VR::SL, VM::M1, "NumberOfTriggers" },
{ 0x0019, 0x002d, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002e, 0, VR::DS, VM::M1, "AngleOfFirstView" },
{ 0x0019, 0x002f, 0, VR::DS, VM::M1, "TriggerFrequency" },
{ 0x0019, 0x0039, 0, VR::SS, VM::M1, "ScanFOVType" },
{ 0x0019, 0x003a, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x003b, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x003c, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x003e, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x003f, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::SS, VM::M1, "StatReconFlag" },
{ 0x0019, 0x0041, 0, VR::SS, VM::M1, "ComputeType" },
{ 0x0019, 0x0042, 0, VR::SS, VM::M1, "SegmentNumber" },
{ 0x0019, 0x0043, 0, VR::SS, VM::M1, "TotalSegmentsRequired" },
{ 0x0019, 0x0044, 0, VR::DS, VM::M1, "InterscanDelay" },
{ 0x0019, 0x0047, 0, VR::SS, VM::M1, "ViewCompressionFactor" },
{ 0x0019, 0x0048, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0049, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x004a, 0, VR::SS, VM::M1, "TotalNumberOfRefChannels" },
{ 0x0019, 0x004b, 0, VR::SL, VM::M1, "DataSizeForScanData" },
{ 0x0019, 0x0052, 0, VR::SS, VM::M1, "ReconPostProcessingFlag" },
{ 0x0019, 0x0054, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0057, 0, VR::SS, VM::M1, "CTWaterNumber" },
{ 0x0019, 0x0058, 0, VR::SS, VM::M1, "CTBoneNumber" },
{ 0x0019, 0x005a, 0, VR::FL, VM::M1, "AcquisitionDuration" },
{ 0x0019, 0x005d, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005e, 0, VR::SL, VM::M1, "NumberOfChannels1To512" },
{ 0x0019, 0x005f, 0, VR::SL, VM::M1, "IncrementBetweenChannels" },
{ 0x0019, 0x0060, 0, VR::SL, VM::M1, "StartingView" },
{ 0x0019, 0x0061, 0, VR::SL, VM::M1, "NumberOfViews" },
{ 0x0019, 0x0062, 0, VR::SL, VM::M1, "IncrementBetweenViews" },
{ 0x0019, 0x006a, 0, VR::SS, VM::M1, "DependantOnNumberOfViewsProcessed" },
{ 0x0019, 0x006b, 0, VR::SS, VM::M1, "FieldOfViewInDetectorCells" },
{ 0x0019, 0x0070, 0, VR::SS, VM::M1, "ValueOfBackProjectionButton" },
{ 0x0019, 0x0071, 0, VR::SS, VM::M1, "SetIfFatqEstimatesWereUsed" },
{ 0x0019, 0x0072, 0, VR::DS, VM::M1, "ZChannelAvgOverViews" },
{ 0x0019, 0x0073, 0, VR::DS, VM::M1, "AvgOfLeftRefChannelsOverViews" },
{ 0x0019, 0x0074, 0, VR::DS, VM::M1, "MaxLeftChannelOverViews" },
{ 0x0019, 0x0075, 0, VR::DS, VM::M1, "AvgOfRightRefChannelsOverViews" },
{ 0x0019, 0x0076, 0, VR::DS, VM::M1, "MaxRightChannelOverViews" },
{ 0x0019, 0x007d, 0, VR::DS, VM::M1, "SecondEcho" },
{ 0x0019, 0x007e, 0, VR::SS, VM::M1, "NumberOfEchos" },
{ 0x0019, 0x007f, 0, VR::DS, VM::M1, "TableDelta" },
{ 0x0019, 0x0081, 0, VR::SS, VM::M1, "Contiguous" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0083, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0084, 0, VR::DS, VM::M1, "PeakSAR" },
{ 0x0019, 0x0085, 0, VR::SS, VM::M1, "MonitorSAR" },
{ 0x0019, 0x0086, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0087, 0, VR::DS, VM::M1, "CardiacRepetition Time" },
{ 0x0019, 0x0088, 0, VR::SS, VM::M1, "ImagesPerCardiacCycle" },
{ 0x0019, 0x008a, 0, VR::SS, VM::M1, "ActualReceiveGainAnalog" },
{ 0x0019, 0x008b, 0, VR::SS, VM::M1, "ActualReceiveGainDigital" },
{ 0x0019, 0x008d, 0, VR::DS, VM::M1, "DelayAfterTrigger" },
{ 0x0019, 0x008f, 0, VR::SS, VM::M1, "SwapPhaseFrequency" },
{ 0x0019, 0x0090, 0, VR::SS, VM::M1, "PauseInterval" },
{ 0x0019, 0x0091, 0, VR::DS, VM::M1, "PauseTime" },
{ 0x0019, 0x0092, 0, VR::SL, VM::M1, "SliceOffsetOnFrequencyAxis" },
{ 0x0019, 0x0093, 0, VR::DS, VM::M1, "AutoPrescanCenterFrequency" },
{ 0x0019, 0x0094, 0, VR::SS, VM::M1, "AutoPrescanTransmitGain" },
{ 0x0019, 0x0095, 0, VR::SS, VM::M1, "AutoPrescanAnalogReceiverGain" },
{ 0x0019, 0x0096, 0, VR::SS, VM::M1, "AutoPrescanDigitalReceiverGain" },
{ 0x0019, 0x0097, 0, VR::SL, VM::M1, "BitmapDefiningCVs" },
{ 0x0019, 0x0098, 0, VR::SS, VM::M1, "CenterFrequencyMethod" },
{ 0x0019, 0x0099, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x009b, 0, VR::SS, VM::M1, "PulseSequenceMode" },
{ 0x0019, 0x009c, 0, VR::LO, VM::M1, "PulseSequenceName" },
{ 0x0019, 0x009d, 0, VR::DT, VM::M1, "PulseSequenceDate" },
{ 0x0019, 0x009e, 0, VR::LO, VM::M1, "InternalPulseSequenceName" },
{ 0x0019, 0x009f, 0, VR::SS, VM::M1, "TransmittingCoil" },
{ 0x0019, 0x00a0, 0, VR::SS, VM::M1, "SurfaceCoilType" },
{ 0x0019, 0x00a1, 0, VR::SS, VM::M1, "ExtremityCoilFlag" },
{ 0x0019, 0x00a2, 0, VR::SL, VM::M1, "RawDataRunNumber" },
{ 0x0019, 0x00a3, 0, VR::UL, VM::M1, "CalibratedFieldStrength" },
{ 0x0019, 0x00a4, 0, VR::SS, VM::M1, "SATFatWaterBone" },
{ 0x0019, 0x00a5, 0, VR::DS, VM::M1, "ReceiveBandwidth" },
{ 0x0019, 0x00a7, 0, VR::DS, VM::M1, "UserData0" },
{ 0x0019, 0x00a8, 0, VR::DS, VM::M1, "UserData1" },
{ 0x0019, 0x00a9, 0, VR::DS, VM::M1, "UserData2" },
{ 0x0019, 0x00aa, 0, VR::DS, VM::M1, "UserData3" },
{ 0x0019, 0x00ab, 0, VR::DS, VM::M1, "UserData4" },
{ 0x0019, 0x00ac, 0, VR::DS, VM::M1, "UserData5" },
{ 0x0019, 0x00ad, 0, VR::DS, VM::M1, "UserData6" },
{ 0x0019, 0x00ae, 0, VR::DS, VM::M1, "UserData7" },
{ 0x0019, 0x00af, 0, VR::DS, VM::M1, "UserData8" },
{ 0x0019, 0x00b0, 0, VR::DS, VM::M1, "UserData9" },
{ 0x0019, 0x00b1, 0, VR::DS, VM::M1, "UserData10" },
{ 0x0019, 0x00b2, 0, VR::DS, VM::M1, "UserData11" },
{ 0x0019, 0x00b3, 0, VR::DS, VM::M1, "UserData12" },
{ 0x0019, 0x00b4, 0, VR::DS, VM::M1, "UserData13" },
{ 0x0019, 0x00b5, 0, VR::DS, VM::M1, "UserData14" },
{ 0x0019, 0x00b6, 0, VR::DS, VM::M1, "UserData15" },
{ 0x0019, 0x00b7, 0, VR::DS, VM::M1, "UserData16" },
{ 0x0019, 0x00b8, 0, VR::DS, VM::M1, "UserData17" },
{ 0x0019, 0x00b9, 0, VR::DS, VM::M1, "UserData18" },
{ 0x0019, 0x00ba, 0, VR::DS, VM::M1, "UserData19" },
{ 0x0019, 0x00bb, 0, VR::DS, VM::M1, "UserData20" },
{ 0x0019, 0x00bc, 0, VR::DS, VM::M1, "UserData21" },
{ 0x0019, 0x00bd, 0, VR::DS, VM::M1, "UserData22" },
{ 0x0019, 0x00be, 0, VR::DS, VM::M1, "ProjectionAngle" },
{ 0x0019, 0x00c0, 0, VR::SS, VM::M1, "SaturationPlanes" },
{ 0x0019, 0x00c1, 0, VR::SS, VM::M1, "SurfaceCoilIntensityCorrectionFlag" },
{ 0x0019, 0x00c2, 0, VR::SS, VM::M1, "SATLocationR" },
{ 0x0019, 0x00c3, 0, VR::SS, VM::M1, "SATLocationL" },
{ 0x0019, 0x00c4, 0, VR::SS, VM::M1, "SATLocationA" },
{ 0x0019, 0x00c5, 0, VR::SS, VM::M1, "SATLocationP" },
{ 0x0019, 0x00c6, 0, VR::SS, VM::M1, "SATLocationH" },
{ 0x0019, 0x00c7, 0, VR::SS, VM::M1, "SATLocationF" },
{ 0x0019, 0x00c8, 0, VR::SS, VM::M1, "SATThicknessRL" },
{ 0x0019, 0x00c9, 0, VR::SS, VM::M1, "SATThicknessAP" },
{ 0x0019, 0x00ca, 0, VR::SS, VM::M1, "SATThicknessHF" },
{ 0x0019, 0x00cb, 0, VR::SS, VM::M1, "PhaseContrastFlowAxis" },
{ 0x0019, 0x00cc, 0, VR::SS, VM::M1, "VelocityEncoding" },
{ 0x0019, 0x00cd, 0, VR::SS, VM::M1, "ThicknessDisclaimer" },
{ 0x0019, 0x00ce, 0, VR::SS, VM::M1, "PrescanType" },
{ 0x0019, 0x00cf, 0, VR::SS, VM::M1, "PrescanStatus" },
{ 0x0019, 0x00d0, 0, VR::SH, VM::M1, "RawDataType" },
{ 0x0019, 0x00d2, 0, VR::SS, VM::M1, "ProjectionAlgorithm" },
{ 0x0019, 0x00d3, 0, VR::SH, VM::M1, "ProjectionAlgorithmName" },
{ 0x0019, 0x00d4, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00d5, 0, VR::SS, VM::M1, "FractionalEcho" },
{ 0x0019, 0x00d6, 0, VR::SS, VM::M1, "PrepPulse" },
{ 0x0019, 0x00d7, 0, VR::SS, VM::M1, "CardiacPhases" },
{ 0x0019, 0x00d8, 0, VR::SS, VM::M1, "VariableEchoFlag" },
{ 0x0019, 0x00d9, 0, VR::DS, VM::M1, "ConcatenatedSatOrDTIDiffusionDirection" },
{ 0x0019, 0x00da, 0, VR::SS, VM::M1, "ReferenceChannelUsed" },
{ 0x0019, 0x00db, 0, VR::DS, VM::M1, "BackProjectorCoefficient" },
{ 0x0019, 0x00dc, 0, VR::SS, VM::M1, "PrimarySpeedCorrectionUsed" },
{ 0x0019, 0x00dd, 0, VR::SS, VM::M1, "OverrangeCorrectionUsed" },
{ 0x0019, 0x00de, 0, VR::DS, VM::M1, "DynamicZAlphaValue" },
{ 0x0019, 0x00df, 0, VR::DS, VM::M1, "UserData23" },
{ 0x0019, 0x00e0, 0, VR::DS, VM::M1, "UserData24" },
{ 0x0019, 0x00e1, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00e2, 0, VR::DS, VM::M1, "VelocityEncodeScale" },
{ 0x0019, 0x00e3, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x00e4, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x00e5, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00e6, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00e8, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00e9, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00eb, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00ec, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00f0, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00f1, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x00f2, 0, VR::SS, VM::M1, "FastPhases" },
{ 0x0019, 0x00f3, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x00f4, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x00f9, 0, VR::DS, VM::M1, "TransmitGain" },
};

unsigned short Dict207TagHashTable[] = {
   47,    56,    63,    72,    83,    92,    99,   106,   115,   126,
  137,   146,   159,   174,   185,   196,   207,   218,   225,   236,
  241,   250,   257,   268,   279,   290,   299,   304,   311,   324,
  335,   344,   351,   358,   365,   374,   383,   392,   401,   410,
  419,   424,   429,   436,   445,   454,     0,     4,    24,    25,
   51,    68,    93,   145,   110,   163,     3,    23,    24,    92,
  144,   109,   162,     4,    26,    27,    99,   151,   108,   161,
  181,   242,     5,    25,    26,    52,    71,    98,   150,   107,
  160,   182,   243,     4,    36,    43,    97,   149,   113,   167,
  179,   240,     3,    35,    42,    96,   148,   180,   241,     3,
   38,    45,    89,   139,   112,   165,     4,    27,    30,    37,
   44,    88,   138,   111,   164,     5,     3,    63,    16,    17,
   40,    47,   162,   218,   183,   244,     5,     2,    62,    39,
   46,    77,   125,    87,   136,   163,   219,     4,    18,    19,
   78,   126,    91,   143,   160,   216,     6,     7,   251,    17,
   18,    28,    32,    79,   127,   161,   217,   177,   235,     7,
    6,   248,    20,    21,    30,    35,    70,   112,    90,   141,
  166,   222,   175,   232,     5,    19,    20,    29,    34,    71,
  113,   167,   223,   176,   233,     5,    22,    23,    32,    37,
   72,   114,    82,   131,   164,   220,     5,    21,    22,    31,
   36,    73,   115,    81,   130,   165,   221,     5,    34,    39,
   74,   116,    80,   129,   154,   210,   178,   236,     3,    33,
   38,    75,   117,   155,   211,     5,    60,    88,    76,   118,
   86,   135,   153,   208,   170,   226,     2,    85,   134,   171,
  227,     4,    61,    90,    84,   133,   158,   214,   168,   224,
    3,    83,   132,   159,   215,   169,   225,     5,    15,    15,
   68,   106,   133,   187,   156,   212,   174,   230,     5,    14,
   14,    62,    93,    69,   107,   132,   186,   157,   213,     5,
    8,     1,    63,    94,   131,   185,   147,   202,   172,   228,
    4,    64,    95,   130,   184,   148,   203,   173,   229,     2,
   10,     3,   145,   200,     3,     9,     2,   136,   190,   146,
  201,     6,     4,    66,    12,     5,    57,    82,    65,    96,
  135,   189,   151,   206,     5,     5,    67,    11,     4,    66,
   97,   134,   188,   152,   207,     4,    58,    84,    67,    98,
  125,   179,   149,   204,     3,    13,     6,   124,   178,   150,
  205,     3,    41,    57,   123,   177,   139,   194,     3,    59,
   87,   122,   176,   140,   195,     4,    43,    59,    53,    72,
  129,   183,   137,   192,     4,    42,    58,    54,    73,   128,
  182,   138,   193,     4,    55,    74,   102,   155,   127,   181,
  143,   198,     4,    44,    60,    56,    75,   126,   180,   144,
  199,     4,    46,    63,   101,   153,   117,   171,   141,   196,
    4,    45,    62,   100,   152,   116,   170,   142,   197,     2,
  106,   159,   115,   169,     2,   105,   158,   114,   168,     3,
   47,    64,   104,   157,   121,   175,     4,    48,    65,   103,
  156,   120,   174,   184,   249,     4,     1,    37,    49,    66,
   95,   147,   119,   173,     4,     0,    36,    50,    67,    94,
  146,   118,   172,
};

vtkDICOMDictionary::Dict Dict207Data = {
"GEMS_ACQU_01",
46,
185,
Dict207TagHashTable,
Dict207Contents
};

// ----- GEMS_IT_US_REPORT -----

DictEntry Dict208Contents[] = {
{ 0x0045, 0x0111, 0, VR::OW, VM::M1, "VividExcelFile" },
{ 0x0045, 0x0112, 0, VR::OW, VM::M1, "VividCHMFile" },
{ 0x0045, 0x0113, 0, VR::OW, VM::M1, "VividPDFFile" },
};

unsigned short Dict208TagHashTable[] = {
    2,     0,     3,     0,   273,     1,   274,     2,   275,
};

vtkDICOMDictionary::Dict Dict208Data = {
"GEMS_IT_US_REPORT",
1,
3,
Dict208TagHashTable,
Dict208Contents
};

// ----- SCHICK TECHNOLOGIES - Change List Creator ID -----

DictEntry Dict209Contents[] = {
{ 0x0021, 0x0001, 0, VR::UI, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict209TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     2,
};

vtkDICOMDictionary::Dict Dict209Data = {
"SCHICK TECHNOLOGIES - Change List Creator ID",
1,
2,
Dict209TagHashTable,
Dict209Contents
};

// ----- DLX_PATNT_01 -----

DictEntry Dict210Contents[] = {
{ 0x0011, 0x0001, 0, VR::LT, VM::M1, "PatientDOB" },
};

unsigned short Dict210TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict210Data = {
"DLX_PATNT_01",
1,
1,
Dict210TagHashTable,
Dict210Contents
};

// ----- MEDIFACE -----

DictEntry Dict211Contents[] = {
{ 0x0029, 0x0001, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0011, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0021, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0022, 0, VR::DS, VM::M2, "" },
{ 0x0029, 0x0030, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict211TagHashTable[] = {
    2,     0,     7,     0,     1,     1,    16,     2,    17,     3,
   32,     4,    33,     5,    34,     6,    48,
};

vtkDICOMDictionary::Dict Dict211Data = {
"MEDIFACE",
1,
7,
Dict211TagHashTable,
Dict211Contents
};

// ----- MITRA OBJECT ATTRIBUTES 1.0 -----

DictEntry Dict212Contents[] = {
{ 0x0033, 0x0002, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x0004, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x0008, 0, VR::LO, VM::M1, "" },
{ 0x0033, 0x000a, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict212TagHashTable[] = {
    2,     0,     5,     0,     2,     1,     4,     2,     6,     3,
    8,     4,    10,
};

vtkDICOMDictionary::Dict Dict212Data = {
"MITRA OBJECT ATTRIBUTES 1.0",
1,
5,
Dict212TagHashTable,
Dict212Contents
};

// ----- SIEMENS MR DATAMAPPING ATTRIBUTES -----

DictEntry Dict213Contents[] = {
{ 0x0011, 0x0001, 0, VR::ST, VM::M1, "ReprocessingInfo" },
{ 0x0011, 0x0002, 0, VR::CS, VM::M1TN, "DataRoleType" },
{ 0x0011, 0x0003, 0, VR::ST, VM::M1, "DataRoleName" },
{ 0x0011, 0x0004, 0, VR::SL, VM::M1, "RescanName" },
{ 0x0011, 0x0005, 0, VR::FD, VM::M1, "" },
{ 0x0011, 0x0006, 0, VR::ST, VM::M1, "CardiacTypeName" },
{ 0x0011, 0x0007, 0, VR::ST, VM::M1, "CardiacTypeNameL2" },
{ 0x0011, 0x0008, 0, VR::ST, VM::M1, "MiscIndicator" },
{ 0x0011, 0x0009, 0, VR::SL, VM::M1, "" },
{ 0x0011, 0x000A, 0, VR::SL, VM::M1, "" },
{ 0x0011, 0x000B, 0, VR::DS, VM::M1, "" },
{ 0x0011, 0x000C, 0, VR::ST, VM::M1, "SplitBaggingName" },
{ 0x0011, 0x000D, 0, VR::ST, VM::M1, "SplitSubBaggingName" },
{ 0x0011, 0x000E, 0, VR::ST, VM::M1, "StageSubBaggingName" },
{ 0x0011, 0x000F, 0, VR::ST, VM::M1, "IsInternalDataRole" },
};

unsigned short Dict213TagHashTable[] = {
    4,    15,    28,     0,     5,     2,     3,     3,     4,     8,
    9,     9,    10,    14,    15,     6,     0,     1,     1,     2,
    6,     7,     7,     8,    12,    13,    13,    14,     4,     4,
    5,     5,     6,    10,    11,    11,    12,
};

vtkDICOMDictionary::Dict Dict213Data = {
"SIEMENS MR DATAMAPPING ATTRIBUTES",
3,
15,
Dict213TagHashTable,
Dict213Contents
};

// ----- SET WINDOW -----

DictEntry Dict214Contents[] = {
{ 0x0019, 0x0000, 0, VR::SH, VM::M1, "SetWindowImageFilter" },
{ 0x0019, 0x0001, 0, VR::US, VM::M1, "SetWindowMagnificationPower" },
};

unsigned short Dict214TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict214Data = {
"SET WINDOW",
1,
2,
Dict214TagHashTable,
Dict214Contents
};

// ----- SIEMENS CSA NON-IMAGE -----

DictEntry Dict215Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "CSADataType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "CSADataVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "CSADataInfo" },
{ 0x7fe1, 0x0010, 0, VR::OB, VM::M1, "CSAData" },
};

unsigned short Dict215TagHashTable[] = {
    2,     0,     4,     0,     8,     1,     9,     2,    16,     3,
   16,
};

vtkDICOMDictionary::Dict Dict215Data = {
"SIEMENS CSA NON-IMAGE",
1,
4,
Dict215TagHashTable,
Dict215Contents
};

// ----- GEMS_ADWSoft_DPO -----

DictEntry Dict216Contents[] = {
{ 0x0039, 0x0080, 0, VR::IS, VM::M1, "PrivateEntityNumber" },
{ 0x0039, 0x0085, 0, VR::DA, VM::M1, "PrivateEntityDate" },
{ 0x0039, 0x0090, 0, VR::TM, VM::M1, "PrivateEntityTime" },
{ 0x0039, 0x0095, 0, VR::LO, VM::M1, "PrivateEntityLaunchCommand" },
{ 0x0039, 0x00AA, 0, VR::CS, VM::M1, "PrivateEntityType" },
};

unsigned short Dict216TagHashTable[] = {
    2,     0,     5,     0,   128,     1,   133,     2,   144,     3,
  149,     4,   170,
};

vtkDICOMDictionary::Dict Dict216Data = {
"GEMS_ADWSoft_DPO",
1,
5,
Dict216TagHashTable,
Dict216Contents
};

// ----- EMAGEON STUDY HOME -----

DictEntry Dict217Contents[] = {
{ 0x0009, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0001, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict217TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict217Data = {
"EMAGEON STUDY HOME",
1,
2,
Dict217TagHashTable,
Dict217Contents
};

// ----- SIEMENS MR IMA -----

DictEntry Dict218Contents[] = {
{ 0x0021, 0x0001, 0, VR::SQ, VM::M1, "MRImageSequence" },
};

unsigned short Dict218TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict218Data = {
"SIEMENS MR IMA",
1,
1,
Dict218TagHashTable,
Dict218Contents
};

// ----- SIEMENS MED PT -----

DictEntry Dict219Contents[] = {
{ 0x0071, 0x0021, 0, VR::UI, VM::M1, "RegistrationMatrixUID" },
{ 0x0071, 0x0022, 0, VR::DT, VM::M1, "DecayCorrectionDateTime" },
{ 0x0071, 0x0023, 0, VR::US, VM::M1, "VolumeIndex" },
{ 0x0071, 0x0024, 0, VR::IS, VM::M1, "TimeSliceDuration" },
};

unsigned short Dict219TagHashTable[] = {
    2,     0,     4,     0,    33,     1,    34,     2,    35,     3,
   36,
};

vtkDICOMDictionary::Dict Dict219Data = {
"SIEMENS MED PT",
1,
4,
Dict219TagHashTable,
Dict219Contents
};

// ----- SIEMENS MED -----

DictEntry Dict220Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "RecognitionCode" },
{ 0x0009, 0x0030, 0, VR::US, VM::M1, "ByteOffsetOfOriginalHeader" },
{ 0x0009, 0x0031, 0, VR::UL, VM::M1, "LengthOfOriginalHeader" },
{ 0x0009, 0x0040, 0, VR::US, VM::M1, "ByteOffsetOfPixelmatrix" },
{ 0x0009, 0x0041, 0, VR::UL, VM::M1, "LengthOfPixelmatrixInBytes" },
{ 0x0009, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0051, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x00f5, 0, VR::LO, VM::M1, "PDMEFIDPlaceholder" },
{ 0x0009, 0x00f6, 0, VR::LO, VM::M1, "PDMDataObjectTypeExtension" },
{ 0x0021, 0x0010, 0, VR::DS, VM::M1, "Zoom" },
{ 0x0021, 0x0011, 0, VR::DS, VM::M2, "Target" },
{ 0x0021, 0x0012, 0, VR::IS, VM::M1, "TubeAngle" },
{ 0x0021, 0x0020, 0, VR::US, VM::M1, "ROIMask" },
{ 0x7001, 0x0010, 0, VR::LO, VM::M1, "Dummy" },
{ 0x7003, 0x0010, 0, VR::LO, VM::M1, "Header" },
{ 0x7005, 0x0010, 0, VR::LO, VM::M1, "Dummy" },
};

unsigned short Dict220TagHashTable[] = {
    5,    16,     4,    33,     0,     5,     2,    49,     3,    64,
    5,    80,     8,   246,    10,    17,     8,     0,    16,     1,
   48,     4,    65,     6,    81,     9,    16,    12,    32,    13,
   16,    15,    16,     3,     7,   245,    11,    18,    14,    16,
};

vtkDICOMDictionary::Dict Dict220Data = {
"SIEMENS MED",
4,
16,
Dict220TagHashTable,
Dict220Contents
};

// ----- GEMS_AWSoft_SB1 -----

DictEntry Dict221Contents[] = {
{ 0x0039, 0x0050, 0, VR::UI, VM::M1, "ReferenceToStudyUID" },
{ 0x0039, 0x0051, 0, VR::UI, VM::M1, "ReferenceToSeriesUID" },
{ 0x0039, 0x0052, 0, VR::IS, VM::M1, "ReferenceToOriginalInstance" },
{ 0x0039, 0x0095, 0, VR::LO, VM::M1, "PrivateEntityLaunchCommand" },
};

unsigned short Dict221TagHashTable[] = {
    2,     0,     4,     0,    80,     1,    81,     2,    82,     3,
  149,
};

vtkDICOMDictionary::Dict Dict221Data = {
"GEMS_AWSoft_SB1",
1,
4,
Dict221TagHashTable,
Dict221Contents
};

// ----- ShowcaseAppearance -----

DictEntry Dict222Contents[] = {
{ 0x0029, 0x0010, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0011, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0012, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0013, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0014, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict222TagHashTable[] = {
    2,     0,     5,     0,    16,     1,    17,     2,    18,     3,
   19,     4,    20,
};

vtkDICOMDictionary::Dict Dict222Data = {
"ShowcaseAppearance",
1,
5,
Dict222TagHashTable,
Dict222Contents
};

// ----- SIEMENS SYNGO INSTANCE MANIFEST -----

DictEntry Dict223Contents[] = {
{ 0x0009, 0x0000, 0, VR::SQ, VM::M1, "TemporaryOriginalHeaderSequence" },
{ 0x0009, 0x0010, 0, VR::AE, VM::M1, "syngoIndexSourceAETitle" },
};

unsigned short Dict223TagHashTable[] = {
    2,     0,     2,     0,     0,     1,    16,
};

vtkDICOMDictionary::Dict Dict223Data = {
"SIEMENS SYNGO INSTANCE MANIFEST",
1,
2,
Dict223TagHashTable,
Dict223Contents
};

// ----- Image (ID, Version, Size, Dump, GUID) -----

DictEntry Dict224Contents[] = {
{ 0x8003, 0x0000, 0, VR::LO, VM::M1, "ID" },
{ 0x8003, 0x0010, 0, VR::LO, VM::M1, "Version" },
{ 0x8003, 0x0020, 0, VR::UL, VM::M1, "Size" },
{ 0x8003, 0x0030, 0, VR::OB, VM::M1, "Dump" },
{ 0x8003, 0x0040, 0, VR::LO, VM::M1, "GUID" },
};

unsigned short Dict224TagHashTable[] = {
    2,     0,     5,     0,     0,     1,    16,     2,    32,     3,
   48,     4,    64,
};

vtkDICOMDictionary::Dict Dict224Data = {
"Image (ID, Version, Size, Dump, GUID)",
1,
5,
Dict224TagHashTable,
Dict224Contents
};

// ----- SIEMENS SYNGO ENHANCED IDATASET API -----

DictEntry Dict225Contents[] = {
{ 0x0027, 0x0001, 0, VR::CS, VM::M1, "BusinessUnitCode" },
{ 0x0027, 0x0002, 0, VR::LO, VM::M1, "ApplicationType" },
{ 0x0027, 0x0003, 0, VR::SQ, VM::M1, "ApplicationAttributesSequence" },
};

unsigned short Dict225TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,     3,
};

vtkDICOMDictionary::Dict Dict225Data = {
"SIEMENS SYNGO ENHANCED IDATASET API",
1,
3,
Dict225TagHashTable,
Dict225Contents
};

// ----- astm.org/diconde/iod/NdeUsEquipmentSettings -----

DictEntry Dict226Contents[] = {
{ 0x0009, 0x0020, 0, VR::SQ, VM::M1, "PulserSettingsSequence" },
{ 0x0009, 0x0022, 0, VR::DS, VM::M1, "PulseWidth" },
{ 0x0009, 0x0024, 0, VR::DS, VM::M1, "ExcitationFrequency" },
{ 0x0009, 0x0026, 0, VR::CS, VM::M1, "ModulationType" },
{ 0x0009, 0x0028, 0, VR::DS, VM::M1, "Damping" },
{ 0x0009, 0x0030, 0, VR::SQ, VM::M1, "ReceiverSettingsSequence" },
{ 0x0009, 0x0031, 0, VR::DS, VM::M1, "AcquiredSoundpathLength" },
{ 0x0009, 0x0032, 0, VR::CS, VM::M1, "AcquisitionCompressionType" },
{ 0x0009, 0x0033, 0, VR::IS, VM::M1, "AcquisitionSampleSize" },
{ 0x0009, 0x0034, 0, VR::DS, VM::M1, "RectifierSmoothing" },
{ 0x0009, 0x0035, 0, VR::SQ, VM::M1, "DACSequence" },
{ 0x0009, 0x0036, 0, VR::CS, VM::M1, "DACType" },
{ 0x0009, 0x0038, 0, VR::DS, VM::M1TN, "DACGainPoints" },
{ 0x0009, 0x003A, 0, VR::DS, VM::M1TN, "DACTimePoints" },
{ 0x0009, 0x003C, 0, VR::DS, VM::M1TN, "DACAmplitude" },
{ 0x0009, 0x0040, 0, VR::SQ, VM::M1, "PreAmplifierSettingsSequence" },
{ 0x0009, 0x0050, 0, VR::SQ, VM::M1, "TransmitTransducerSettingsSequence" },
{ 0x0009, 0x0051, 0, VR::SQ, VM::M1, "ReceiveTransducerSettingsSequence" },
{ 0x0009, 0x0052, 0, VR::DS, VM::M1, "IncidentAngle" },
{ 0x0009, 0x0054, 0, VR::ST, VM::M1, "CouplingTechnique" },
{ 0x0009, 0x0056, 0, VR::ST, VM::M1, "CouplingMedium" },
{ 0x0009, 0x0057, 0, VR::DS, VM::M1, "CouplingVelocity" },
{ 0x0009, 0x0058, 0, VR::DS, VM::M1, "CrystalCenterLocationX" },
{ 0x0009, 0x0059, 0, VR::DS, VM::M1, "CrystalCenterLocationZ" },
{ 0x0009, 0x005A, 0, VR::DS, VM::M1, "SoundPathLength" },
{ 0x0009, 0x005C, 0, VR::ST, VM::M1, "DelayLawIdentifier" },
{ 0x0009, 0x0060, 0, VR::SQ, VM::M1, "GateSettingsSequence" },
{ 0x0009, 0x0062, 0, VR::DS, VM::M1, "GateThreshold" },
{ 0x0009, 0x0064, 0, VR::DS, VM::M1, "VelocityOfSound" },
{ 0x0009, 0x0070, 0, VR::SQ, VM::M1, "CalibrationSettingsSequence" },
{ 0x0009, 0x0072, 0, VR::ST, VM::M1, "CalibrationProcedure" },
{ 0x0009, 0x0074, 0, VR::SH, VM::M1, "ProcedureVersion" },
{ 0x0009, 0x0076, 0, VR::DA, VM::M1, "ProcedureCreationDate" },
{ 0x0009, 0x0078, 0, VR::DA, VM::M1, "ProcedureExpirationDate" },
{ 0x0009, 0x007A, 0, VR::DA, VM::M1, "ProcedureLastModifiedDate" },
{ 0x0009, 0x007C, 0, VR::TM, VM::M1TN, "CalibrationTime" },
{ 0x0009, 0x007E, 0, VR::DA, VM::M1TN, "CalibrationDate" },
};

unsigned short Dict226TagHashTable[] = {
   10,    25,    30,    37,    44,    53,    64,    73,    84,     0,
    7,     2,    36,    11,    54,    15,    64,    18,    82,    23,
   89,    28,   100,    32,   118,     2,    24,    90,    36,   126,
    3,     3,    38,     6,    49,    19,    84,     3,     5,    48,
   25,    92,    29,   112,     4,     8,    51,    12,    56,    20,
   86,    33,   120,     5,     0,    32,     7,    50,    21,    87,
   26,    96,    30,   114,     4,     4,    40,    10,    53,    13,
   58,    34,   122,     5,     1,    34,     9,    52,    16,    80,
   27,    98,    31,   116,     4,    14,    60,    17,    81,    22,
   88,    35,   124,
};

vtkDICOMDictionary::Dict Dict226Data = {
"astm.org/diconde/iod/NdeUsEquipmentSettings",
9,
37,
Dict226TagHashTable,
Dict226Contents
};

// ----- SIEMENS MR HEADER -----

DictEntry Dict227Contents[] = {
{ 0x0019, 0x0008, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x0009, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x000A, 0, VR::US, VM::M1, "NumberOfImagesInMosaic" },
{ 0x0019, 0x000B, 0, VR::DS, VM::M1, "SliceMeasurementDuration" },
{ 0x0019, 0x000C, 0, VR::IS, VM::M1, "BValue" },
{ 0x0019, 0x000D, 0, VR::CS, VM::M1, "DiffusionDirectionality" },
{ 0x0019, 0x000E, 0, VR::FD, VM::M3, "DiffusionGradientDirection" },
{ 0x0019, 0x000f, 0, VR::SH, VM::M1, "GradientMode" },
{ 0x0019, 0x0011, 0, VR::SH, VM::M1, "FlowCompensation" },
{ 0x0019, 0x0012, 0, VR::SL, VM::M3, "TablePositionOrigin" },
{ 0x0019, 0x0013, 0, VR::SL, VM::M3, "ImaAbsTablePosition" },
{ 0x0019, 0x0014, 0, VR::IS, VM::M3, "ImaRelTablePosition" },
{ 0x0019, 0x0015, 0, VR::FD, VM::M3, "SlicePosition_PCS" },
{ 0x0019, 0x0016, 0, VR::DS, VM::M1, "TimeAfterStart" },
{ 0x0019, 0x0017, 0, VR::DS, VM::M1, "SliceResolution" },
{ 0x0019, 0x0018, 0, VR::IS, VM::M1, "RealDwellTime" },
{ 0x0019, 0x0023, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0025, 0, VR::FD, VM::M1TN, "" },
{ 0x0019, 0x0026, 0, VR::FD, VM::M1TN, "" },
{ 0x0019, 0x0027, 0, VR::FD, VM::M6, "BMatrix" },
{ 0x0019, 0x0028, 0, VR::FD, VM::M1, "BandwidthPerPixelPhaseEncode" },
{ 0x0019, 0x0029, 0, VR::FD, VM::M1TN, "MosaicRefAcqTimes" },
{ 0x0051, 0x0008, 0, VR::CS, VM::M1, "CSAImageHeaderType" },
{ 0x0051, 0x0009, 0, VR::LO, VM::M1, "CSAImageHeaderVersion" },
{ 0x0051, 0x000a, 0, VR::LO, VM::M1, "" },
{ 0x0051, 0x000b, 0, VR::SH, VM::M1, "AcquisitionMatrixText" },
{ 0x0051, 0x000c, 0, VR::LO, VM::M1, "" },
{ 0x0051, 0x000d, 0, VR::SH, VM::M1, "" },
{ 0x0051, 0x000e, 0, VR::LO, VM::M1, "" },
{ 0x0051, 0x000f, 0, VR::LO, VM::M1, "CoilString" },
{ 0x0051, 0x0011, 0, VR::LO, VM::M1, "" },
{ 0x0051, 0x0012, 0, VR::SH, VM::M1, "" },
{ 0x0051, 0x0013, 0, VR::SH, VM::M1, "PositivePCSDirections" },
{ 0x0051, 0x0015, 0, VR::SH, VM::M1, "" },
{ 0x0051, 0x0016, 0, VR::LO, VM::M1, "" },
{ 0x0051, 0x0017, 0, VR::SH, VM::M1, "" },
{ 0x0051, 0x0018, 0, VR::SH, VM::M1, "" },
{ 0x0051, 0x0019, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict227TagHashTable[] = {
   10,    19,    30,    39,    50,    63,    70,    77,    84,     0,
    4,     3,    11,    18,    38,    24,    10,    36,    24,     5,
    2,    10,    10,    19,    15,    24,    25,    11,    37,    25,
    4,     5,    13,     9,    18,    26,    12,    30,    17,     5,
    4,    12,    12,    21,    21,    41,    27,    13,    31,    18,
    6,     7,    15,    11,    20,    16,    35,    20,    40,    28,
   14,    32,    19,     3,     6,    14,    14,    23,    29,    15,
    3,    13,    22,    17,    37,    33,    21,     3,     1,     9,
   22,     8,    34,    22,     5,     0,     8,     8,    17,    19,
   39,    23,     9,    35,    23,
};

vtkDICOMDictionary::Dict Dict227Data = {
"SIEMENS MR HEADER",
9,
38,
Dict227TagHashTable,
Dict227Contents
};

// ----- AGFA KOSD 1.0 -----

DictEntry Dict228Contents[] = {
{ 0x0035, 0x0000, 0, VR::SH, VM::M1, "" },
{ 0x0035, 0x0003, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict228TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     3,
};

vtkDICOMDictionary::Dict Dict228Data = {
"AGFA KOSD 1.0",
1,
2,
Dict228TagHashTable,
Dict228Contents
};

// ----- Siemens: Thorax/Multix FD Version -----

DictEntry Dict229Contents[] = {
{ 0x0017, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x0001, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict229TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict229Data = {
"Siemens: Thorax/Multix FD Version",
1,
2,
Dict229TagHashTable,
Dict229Contents
};

// ----- SPI-P-Private-DiDi Release 1 -----

DictEntry Dict230Contents[] = {
{ 0x0019, 0x0000, 0, VR::LT, VM::M1, "PostModeString" },
{ 0x0019, 0x0001, 0, VR::LT, VM::M1, "PostData" },
{ 0x0019, 0x0010, 0, VR::LT, VM::M1, "ImageHeader" },
};

unsigned short Dict230TagHashTable[] = {
    2,     0,     3,     0,     0,     1,     1,     2,    16,
};

vtkDICOMDictionary::Dict Dict230Data = {
"SPI-P-Private-DiDi Release 1",
1,
3,
Dict230TagHashTable,
Dict230Contents
};

// ----- SIEMENS SMS-AX  ORIGINAL IMAGE INFO 1.0 -----

DictEntry Dict231Contents[] = {
{ 0x0025, 0x0000, 0, VR::US, VM::M1, "ViewNative" },
{ 0x0025, 0x0001, 0, VR::US, VM::M1, "OriginalSeriesNumber" },
{ 0x0025, 0x0002, 0, VR::US, VM::M1, "OriginalImageNumber" },
{ 0x0025, 0x0003, 0, VR::US, VM::M1, "WinCenter" },
{ 0x0025, 0x0004, 0, VR::US, VM::M1, "WinWidth" },
{ 0x0025, 0x0005, 0, VR::US, VM::M1, "WinBrightness" },
{ 0x0025, 0x0006, 0, VR::US, VM::M1, "WinContrast" },
{ 0x0025, 0x0007, 0, VR::US, VM::M1, "OriginalFrameNumber" },
{ 0x0025, 0x0008, 0, VR::US, VM::M1, "OriginalMaskFrameNumber" },
{ 0x0025, 0x0009, 0, VR::US, VM::M1, "Opac" },
{ 0x0025, 0x000a, 0, VR::US, VM::M1, "OriginalNumberofFrames" },
{ 0x0025, 0x000b, 0, VR::DS, VM::M1, "OriginalSceneDuration" },
{ 0x0025, 0x000c, 0, VR::LO, VM::M1, "IdentifierLOID" },
{ 0x0025, 0x000d, 0, VR::SS, VM::M1TN, "OriginalSceneVFRInfo" },
{ 0x0025, 0x000e, 0, VR::SS, VM::M1, "OriginalFrameECGPosition" },
{ 0x0025, 0x000f, 0, VR::SS, VM::M1, "OriginalECG1stFrameOffset" },
{ 0x0025, 0x0010, 0, VR::SS, VM::M1, "ZoomFlag" },
{ 0x0025, 0x0011, 0, VR::US, VM::M1, "FlexiblePixelShift" },
{ 0x0025, 0x0012, 0, VR::US, VM::M1, "NumberOfMaskFrames" },
{ 0x0025, 0x0013, 0, VR::US, VM::M1, "NumberOfFillFrames" },
{ 0x0025, 0x0014, 0, VR::IS, VM::M1, "SeriesNumber" },
{ 0x0025, 0x0015, 0, VR::IS, VM::M1, "ImageNumber" },
{ 0x0025, 0x0016, 0, VR::IS, VM::M1, "ReadyProcessingStatus" },
};

unsigned short Dict231TagHashTable[] = {
    6,    15,    24,    35,    46,     0,     4,     6,     6,     8,
    8,    13,    13,    18,    18,     4,     1,     1,    11,    11,
   12,    12,    22,    22,     5,     0,     0,     5,     5,    10,
   10,    15,    15,    17,    17,     5,     3,     3,     4,     4,
   14,    14,    16,    16,    21,    21,     5,     2,     2,     7,
    7,     9,     9,    19,    19,    20,    20,
};

vtkDICOMDictionary::Dict Dict231Data = {
"SIEMENS SMS-AX  ORIGINAL IMAGE INFO 1.0",
5,
23,
Dict231TagHashTable,
Dict231Contents
};

// ----- SIENET -----

DictEntry Dict232Contents[] = {
{ 0x0009, 0x0001, 0, VR::US, VM::M1, "SIENETCommandField" },
{ 0x0009, 0x0014, 0, VR::LO, VM::M1, "ReceiverPLA" },
{ 0x0009, 0x0016, 0, VR::US, VM::M1, "TransferPriority" },
{ 0x0009, 0x0029, 0, VR::LO, VM::M1, "ActualUser" },
{ 0x0009, 0x0070, 0, VR::DS, VM::M1, "" },
{ 0x0009, 0x0071, 0, VR::DS, VM::M1, "" },
{ 0x0009, 0x0072, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0073, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0074, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0075, 0, VR::LO, VM::M1, "" },
{ 0x0091, 0x0020, 0, VR::PN, VM::M1, "RISPatientName" },
{ 0x0093, 0x0002, 0, VR::LO, VM::M1, "" },
{ 0x0095, 0x0001, 0, VR::LO, VM::M1, "ExaminationFolderID" },
{ 0x0095, 0x0004, 0, VR::UL, VM::M1, "FolderReportedStatus" },
{ 0x0095, 0x0005, 0, VR::LO, VM::M1, "FolderReportingRadiologist" },
{ 0x0095, 0x0007, 0, VR::LO, VM::M1, "SIENETISAPLA" },
{ 0x0095, 0x000c, 0, VR::SL, VM::M1, "" },
{ 0x0095, 0x0020, 0, VR::PN, VM::M1, "RISPatientName" },
{ 0x0097, 0x0003, 0, VR::SL, VM::M1, "" },
{ 0x0097, 0x0005, 0, VR::LO, VM::M1, "" },
{ 0x0099, 0x0002, 0, VR::SL, VM::M1, "DataObjectAttributes" },
{ 0x0099, 0x0005, 0, VR::SL, VM::M1, "" },
{ 0x00A5, 0x0005, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict232TagHashTable[] = {
    6,    17,    24,    35,    46,     0,     5,     4,   112,     9,
  117,    12,     1,    16,    12,    18,     3,     3,     2,    22,
    5,   113,    14,     5,     5,     3,    41,     6,   114,    11,
    2,    13,     4,    22,     5,     5,     0,     1,     7,   115,
   17,    32,    20,     2,    21,     5,     5,     1,    20,     8,
  116,    10,    32,    15,     7,    19,     5,
};

vtkDICOMDictionary::Dict Dict232Data = {
"SIENET",
5,
23,
Dict232TagHashTable,
Dict232Contents
};

// ----- TOSHIBA_MEC_CT3 -----

DictEntry Dict233Contents[] = {
{ 0x7005, 0x0000, 0, VR::OB, VM::M1, "CTPrivateData1" },
{ 0x7005, 0x0003, 0, VR::SH, VM::M1, "CardiacRRMeanTime" },
{ 0x7005, 0x0004, 0, VR::SH, VM::M1, "CardiacReconstructionGettingPhaseInPercent" },
{ 0x7005, 0x0005, 0, VR::SH, VM::M1, "CardiacReconstructionGettingPhaseInMS" },
{ 0x7005, 0x0006, 0, VR::SH, VM::M1, "CardiacReconstructionMode" },
{ 0x7005, 0x0007, 0, VR::DS, VM::M1TN, "ReconstructionCenter" },
{ 0x7005, 0x0008, 0, VR::DS, VM::M1, "DetectorSliceThickness" },
{ 0x7005, 0x0009, 0, VR::LO, VM::M1, "NumberOfDetectorRowsToReconstruct" },
{ 0x7005, 0x000a, 0, VR::DS, VM::M1, "TableSpeed" },
{ 0x7005, 0x000b, 0, VR::SH, VM::M1, "Filter" },
{ 0x7005, 0x000c, 0, VR::SH, VM::M1, "ReconstructionCorrectionType" },
{ 0x7005, 0x000d, 0, VR::SH, VM::M1, "Organ" },
{ 0x7005, 0x000e, 0, VR::SH, VM::M1, "FileTypeRemarks" },
{ 0x7005, 0x000f, 0, VR::SH, VM::M1, "Direction" },
{ 0x7005, 0x0010, 0, VR::OB, VM::M1, "CTPrivateData2" },
{ 0x7005, 0x0011, 0, VR::LT, VM::M1, "SeriesComment" },
{ 0x7005, 0x0012, 0, VR::SH, VM::M1, "Position" },
{ 0x7005, 0x0013, 0, VR::US, VM::M1, "ExpertPlanNumber" },
{ 0x7005, 0x0014, 0, VR::US, VM::M1, "ReconstructionROINumber" },
{ 0x7005, 0x0015, 0, VR::US, VM::M1, "SpecialHelicalAcquisitionNumber" },
{ 0x7005, 0x0016, 0, VR::UI, VM::M1, "VolumeUID" },
{ 0x7005, 0x0017, 0, VR::US, VM::M1, "TotalFrameCountInTheVolume" },
{ 0x7005, 0x0018, 0, VR::US, VM::M1, "FrameNumber" },
{ 0x7005, 0x0019, 0, VR::UL, VM::M1, "FrameSortKey" },
{ 0x7005, 0x001a, 0, VR::US, VM::M1, "FrameSortOrder" },
{ 0x7005, 0x001b, 0, VR::SH, VM::M1, "ConvolutionKernelForSeriesRecord" },
{ 0x7005, 0x001c, 0, VR::LO, VM::M1, "ContrastBolusAgentForSeriesRecord" },
{ 0x7005, 0x001d, 0, VR::UL, VM::M1, "ReconstructionNumber" },
{ 0x7005, 0x001e, 0, VR::UL, VM::M1, "RawDataNumber" },
{ 0x7005, 0x001f, 0, VR::LO, VM::M1, "VolumeNumber" },
{ 0x7005, 0x0020, 0, VR::UL, VM::M1, "LocalSeriesNumber" },
{ 0x7005, 0x0021, 0, VR::LO, VM::M1, "DecreaseInArtifactFilter" },
{ 0x7005, 0x0022, 0, VR::DS, VM::M1, "ReconstructionInterval" },
{ 0x7005, 0x0023, 0, VR::DS, VM::M1, "PitchFactor" },
{ 0x7005, 0x0024, 0, VR::DA, VM::M1, "AcquisitionDateOfNRA" },
{ 0x7005, 0x0025, 0, VR::UL, VM::M1, "LargeDataFileAttribute" },
{ 0x7005, 0x0026, 0, VR::CS, VM::M1T8, "LargeDataFileName" },
{ 0x7005, 0x0028, 0, VR::SQ, VM::M1, "EnhancedCTPrivateSequence" },
{ 0x7005, 0x0029, 0, VR::UI, VM::M1, "FrameUID" },
{ 0x7005, 0x0030, 0, VR::CS, VM::M1, "MainModalityInStudy" },
{ 0x7005, 0x0035, 0, VR::DS, VM::M2, "ScanRange" },
{ 0x7005, 0x0036, 0, VR::OB, VM::M1, "CTPrivateData3" },
{ 0x7005, 0x0037, 0, VR::IS, VM::M1, "TotalFrames" },
{ 0x7005, 0x0038, 0, VR::IS, VM::M1, "StartFrame" },
{ 0x7005, 0x0039, 0, VR::IS, VM::M1, "EndFrame" },
{ 0x7005, 0x0040, 0, VR::FD, VM::M1, "DLP" },
{ 0x7005, 0x0041, 0, VR::SH, VM::M1, "RowSliceInformation" },
{ 0x7005, 0x0042, 0, VR::US, VM::M1, "LocalFrameNumber" },
{ 0x7005, 0x0043, 0, VR::DS, VM::M3, "VolumeVector" },
{ 0x7005, 0x0044, 0, VR::US, VM::M1, "VolumeType" },
{ 0x7005, 0x0045, 0, VR::DS, VM::M1, "RelativeTablePositionOf4DVolume" },
{ 0x7005, 0x0046, 0, VR::DS, VM::M1, "AbsoluteTablePositionOf4DVolume" },
{ 0x7005, 0x0047, 0, VR::DS, VM::M1, "SlicePitchOf4DVolume" },
{ 0x7005, 0x0048, 0, VR::LO, VM::M1, "RespiratoryGatingInformation" },
{ 0x7005, 0x0049, 0, VR::SH, VM::M1, "RespiratoryPhase" },
{ 0x7005, 0x0061, 0, VR::LO, VM::M1, "SynchronizedSignalInformation" },
{ 0x7005, 0x0062, 0, VR::DS, VM::M1, "TotalRawDataSize" },
{ 0x7005, 0x0063, 0, VR::FD, VM::M1, "CTDIw" },
{ 0x7005, 0x0067, 0, VR::UI, VM::M1, "VolumeUIDOf4DVolume" },
{ 0x7005, 0x0068, 0, VR::US, VM::M1, "TotalFrameCountIn4DVolume" },
{ 0x7005, 0x0069, 0, VR::US, VM::M1, "FrameNumberIn4DVolume" },
{ 0x7005, 0x006a, 0, VR::DS, VM::M3, "ImagePositionOf4DVolumeTop" },
{ 0x7005, 0x006b, 0, VR::DS, VM::M3, "ImagePositionOf4DVolumeTopEquipment" },
{ 0x7005, 0x006c, 0, VR::UI, VM::M1, "SOPInstanceUIDOf4DVolume" },
{ 0x7005, 0x006d, 0, VR::UI, VM::M1, "SeriesInstanceUIDOf4DVolume" },
{ 0x7005, 0x00F1, 0, VR::CS, VM::M1, "ProtectMarkForStudyRecord" },
};

unsigned short Dict233TagHashTable[] = {
   17,    28,    37,    46,    59,    66,    79,    90,   101,   108,
  115,   120,   125,   138,   151,   158,     0,     5,     3,     5,
   19,    21,    35,    37,    40,    53,    49,    68,     4,     2,
    4,    18,    20,    34,    36,    50,    69,     4,     5,     7,
   21,    23,    42,    55,    51,    70,     6,     4,     6,    20,
   22,    36,    38,    41,    54,    52,    71,    58,   103,     3,
   15,    17,    31,    33,    45,    64,     6,     0,     0,    14,
   16,    30,    32,    39,    48,    46,    65,    55,    97,     5,
    1,     3,    17,    19,    33,    35,    47,    66,    56,    98,
    5,    16,    18,    32,    34,    48,    67,    57,    99,    65,
  241,     3,    11,    13,    27,    29,    63,   108,     3,    10,
   12,    26,    28,    64,   109,     2,    13,    15,    29,    31,
    2,    12,    14,    28,    30,     6,     7,     9,    23,    25,
   38,    41,    44,    57,    53,    72,    59,   104,     6,     6,
    8,    22,    24,    37,    40,    43,    56,    54,    73,    60,
  105,     3,     9,    11,    25,    27,    61,   106,     3,     8,
   10,    24,    26,    62,   107,
};

vtkDICOMDictionary::Dict Dict233Data = {
"TOSHIBA_MEC_CT3",
16,
66,
Dict233TagHashTable,
Dict233Contents
};

// ----- Silhouette Annot V1.0 -----

DictEntry Dict234Contents[] = {
{ 0x0029, 0x0011, 0, VR::IS, VM::M1, "AnnotationName" },
{ 0x0029, 0x0012, 0, VR::LT, VM::M1, "AnnotationFont" },
{ 0x0029, 0x0013, 0, VR::LT, VM::M1, "AnnotationTextForegroundColor" },
{ 0x0029, 0x0014, 0, VR::LT, VM::M1, "AnnotationTextBackgroundColor" },
{ 0x0029, 0x0015, 0, VR::UL, VM::M1, "AnnotationTextBackingMode" },
{ 0x0029, 0x0016, 0, VR::UL, VM::M1, "AnnotationTextJustification" },
{ 0x0029, 0x0017, 0, VR::UL, VM::M1, "AnnotationTextLocation" },
{ 0x0029, 0x0018, 0, VR::LT, VM::M1, "AnnotationTextString" },
{ 0x0029, 0x0019, 0, VR::UL, VM::M1, "AnnotationTextAttachMode" },
{ 0x0029, 0x0020, 0, VR::UL, VM::M1, "AnnotationTextCursorMode" },
{ 0x0029, 0x0021, 0, VR::UL, VM::M1, "AnnotationTextShadowOffsetX" },
{ 0x0029, 0x0022, 0, VR::UL, VM::M1, "AnnotationTextShadowOffsetY" },
{ 0x0029, 0x0023, 0, VR::LT, VM::M1, "AnnotationLineColor" },
{ 0x0029, 0x0024, 0, VR::UL, VM::M1, "AnnotationLineThickness" },
{ 0x0029, 0x0025, 0, VR::UL, VM::M1, "AnnotationLineType" },
{ 0x0029, 0x0026, 0, VR::UL, VM::M1, "AnnotationLineStyle" },
{ 0x0029, 0x0027, 0, VR::UL, VM::M1, "AnnotationLineDashLength" },
{ 0x0029, 0x0028, 0, VR::UL, VM::M1, "AnnotationLineAttachMode" },
{ 0x0029, 0x0029, 0, VR::UL, VM::M1, "AnnotationLinePointCount" },
{ 0x0029, 0x0030, 0, VR::FD, VM::M1, "AnnotationLinePoints" },
{ 0x0029, 0x0031, 0, VR::UL, VM::M1, "AnnotationLineControlSize" },
{ 0x0029, 0x0032, 0, VR::LT, VM::M1, "AnnotationMarkerColor" },
{ 0x0029, 0x0033, 0, VR::UL, VM::M1, "AnnotationMarkerType" },
{ 0x0029, 0x0034, 0, VR::UL, VM::M1, "AnnotationMarkerSize" },
{ 0x0029, 0x0035, 0, VR::FD, VM::M1, "AnnotationMarkerLocation" },
{ 0x0029, 0x0036, 0, VR::UL, VM::M1, "AnnotationMarkerAttachMode" },
{ 0x0029, 0x0037, 0, VR::LT, VM::M1, "AnnotationGeomColor" },
{ 0x0029, 0x0038, 0, VR::UL, VM::M1, "AnnotationGeomThickness" },
{ 0x0029, 0x0039, 0, VR::UL, VM::M1, "AnnotationGeomLineStyle" },
{ 0x0029, 0x0040, 0, VR::UL, VM::M1, "AnnotationGeomDashLength" },
{ 0x0029, 0x0041, 0, VR::UL, VM::M1, "AnnotationGeomFillPattern" },
{ 0x0029, 0x0042, 0, VR::UL, VM::M1, "AnnotationInteractivity" },
{ 0x0029, 0x0043, 0, VR::FD, VM::M1, "AnnotationArrowLength" },
{ 0x0029, 0x0044, 0, VR::FD, VM::M1, "AnnotationArrowAngle" },
{ 0x0029, 0x0045, 0, VR::UL, VM::M1, "AnnotationDontSave" },
};

unsigned short Dict234TagHashTable[] = {
    9,    24,    37,    46,    55,    64,    73,    80,     0,     7,
    0,    17,     8,    25,    10,    33,    18,    41,    20,    49,
   28,    57,    29,    64,     6,     7,    24,     9,    32,    17,
   40,    19,    48,    27,    56,    30,    65,     4,     2,    19,
   12,    35,    22,    51,    31,    66,     4,     1,    18,    11,
   34,    21,    50,    32,    67,     4,     4,    21,    14,    37,
   24,    53,    33,    68,     4,     3,    20,    13,    36,    23,
   52,    34,    69,     3,     6,    23,    16,    39,    26,    55,
    3,     5,    22,    15,    38,    25,    54,
};

vtkDICOMDictionary::Dict Dict234Data = {
"Silhouette Annot V1.0",
8,
35,
Dict234TagHashTable,
Dict234Contents
};

// ----- SIEMENS CT APPL MEASUREMENT -----

DictEntry Dict235Contents[] = {
{ 0x0029, 0x0000, 0, VR::UT, VM::M1, "OncologySegmentationMeasurementValues" },
{ 0x0029, 0x0001, 0, VR::ST, VM::M1, "OncologyMeasurementRecistStandard" },
{ 0x0029, 0x0010, 0, VR::CS, VM::M1, "DualEnergyROIAnnotationMode" },
};

unsigned short Dict235TagHashTable[] = {
    2,     0,     3,     0,     0,     1,     1,     2,    16,
};

vtkDICOMDictionary::Dict Dict235Data = {
"SIEMENS CT APPL MEASUREMENT",
1,
3,
Dict235TagHashTable,
Dict235Contents
};

// ----- QCA Results -----

DictEntry Dict236Contents[] = {
{ 0x0009, 0x0000, 0, VR::CS, VM::M1, "AnalysisType" },
{ 0x0009, 0x0004, 0, VR::LO, VM::M1, "SegmentName" },
{ 0x0009, 0x0012, 0, VR::DS, VM::M1, "PreProcedureCatheterSize" },
{ 0x0009, 0x0013, 0, VR::DS, VM::M1, "PreProcedureReferenceDiameter" },
{ 0x0009, 0x0014, 0, VR::DS, VM::M1, "PreProcedureMinimumLumenDiameter" },
{ 0x0009, 0x0015, 0, VR::DS, VM::M1, "PreProcedureAverageDiameter" },
{ 0x0009, 0x0016, 0, VR::DS, VM::M1, "PreProcedureStenosisLength" },
{ 0x0009, 0x0017, 0, VR::DS, VM::M1, "PreProcedureStenosisPercentage" },
{ 0x0009, 0x0018, 0, VR::DS, VM::M1, "PreProcedureGeometricAreaReductionPercentage" },
{ 0x0009, 0x0022, 0, VR::DS, VM::M1, "PostProcedureCatheterSize" },
{ 0x0009, 0x0023, 0, VR::DS, VM::M1, "PostProcedureReferenceDiameter" },
{ 0x0009, 0x0024, 0, VR::DS, VM::M1, "PostProcedureMinimumLumenDiameter" },
{ 0x0009, 0x0025, 0, VR::DS, VM::M1, "PostProcedureAverageDiameter" },
{ 0x0009, 0x0026, 0, VR::DS, VM::M1, "PostProcedureStenosisLength" },
{ 0x0009, 0x0027, 0, VR::DS, VM::M1, "PostProcedureStenosisPercentage" },
{ 0x0009, 0x0028, 0, VR::DS, VM::M1, "PostProcedureGeometricAreaReductionPercentage" },
};

unsigned short Dict236TagHashTable[] = {
    5,    10,    23,    32,     0,     2,     5,    21,    12,    37,
    6,     0,     0,     1,     4,     4,    20,     8,    24,    11,
   36,    15,    40,     4,     3,    19,     7,    23,    10,    35,
   14,    39,     4,     2,    18,     6,    22,     9,    34,    13,
   38,
};

vtkDICOMDictionary::Dict Dict236Data = {
"QCA Results",
4,
16,
Dict236TagHashTable,
Dict236Contents
};

// ----- RadWorksMarconi -----

DictEntry Dict237Contents[] = {
{ 0x0029, 0x0024, 0, VR::US, VM::M1TN, "KeyFrameIndices" },
};

unsigned short Dict237TagHashTable[] = {
    2,     0,     1,     0,    36,
};

vtkDICOMDictionary::Dict Dict237Data = {
"RadWorksMarconi",
1,
1,
Dict237TagHashTable,
Dict237Contents
};

// ----- A.L.I. Technologies, Inc. -----

DictEntry Dict238Contents[] = {
{ 0x3711, 0x0001, 0, VR::LO, VM::M1, "Filename" },
{ 0x3711, 0x0002, 0, VR::OB, VM::M1, "DataBlobOfAVisit" },
{ 0x3711, 0x0003, 0, VR::US, VM::M1, "RevisionNumber" },
{ 0x3711, 0x0004, 0, VR::UL, VM::M1, "UnixTimestamp" },
{ 0x3711, 0x0005, 0, VR::IS, VM::M1, "BagID" },
{ 0x3711, 0x000C, 0, VR::UI, VM::M1, "OriginalStudyUID" },
{ 0x3711, 0x000D, 0, VR::US, VM::M1, "OverlayGrayscaleValue" },
{ 0x3711, 0x000E, 0, VR::CS, VM::M1, "AnonymizationStatus" },
{ 0x3711, 0x000F, 0, VR::CS, VM::M1, "InstanceType" },
{ 0x3711, 0x0030, 0, VR::LO, VM::M1, "IPConvertedFrame" },
{ 0x3711, 0x0097, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict238TagHashTable[] = {
    3,    16,     0,     6,     0,     1,     2,     3,     4,     5,
    6,    13,     8,    15,    10,   151,     5,     1,     2,     3,
    4,     5,    12,     7,    14,     9,    48,
};

vtkDICOMDictionary::Dict Dict238Data = {
"A.L.I. Technologies, Inc.",
2,
11,
Dict238TagHashTable,
Dict238Contents
};

// ----- SEGAMI MIML -----

DictEntry Dict239Contents[] = {
{ 0x0031, 0x0098, 0, VR::OW, VM::M1, "" },
};

unsigned short Dict239TagHashTable[] = {
    2,     0,     1,     0,   152,
};

vtkDICOMDictionary::Dict Dict239Data = {
"SEGAMI MIML",
1,
1,
Dict239TagHashTable,
Dict239Contents
};

// ----- EMAGEON JPEG2K INFO -----

DictEntry Dict240Contents[] = {
{ 0x0009, 0x0000, 0, VR::SQ, VM::M1, "" },
{ 0x0009, 0x0001, 0, VR::DT, VM::M1, "" },
};

unsigned short Dict240TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict240Data = {
"EMAGEON JPEG2K INFO",
1,
2,
Dict240TagHashTable,
Dict240Contents
};

// ----- FOEM 1.0 -----

DictEntry Dict241Contents[] = {
{ 0x0019, 0x0050, 0, VR::IS, VM::M1, "" },
{ 0x0025, 0x0010, 0, VR::US, VM::M1, "" },
{ 0x0025, 0x0012, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict241TagHashTable[] = {
    2,     0,     4,     0,    80,     1,    16,     2,    18,     3,
   32,
};

vtkDICOMDictionary::Dict Dict241Data = {
"FOEM 1.0",
1,
4,
Dict241TagHashTable,
Dict241Contents
};

// ----- MeVis eD: Timepoint Information -----

DictEntry Dict242Contents[] = {
{ 0x0021, 0x0010, 0, VR::LT, VM::M1, "TimepointDateTime" },
{ 0x0021, 0x0011, 0, VR::CS, VM::M1, "TimepointDateTimeType" },
{ 0x0021, 0x0012, 0, VR::UN, VM::M1, "TimepointSeriesDescription" },
{ 0x0021, 0x0013, 0, VR::UN, VM::M1, "TimepointGradientDirections" },
{ 0x0021, 0x0071, 0, VR::UN, VM::M1, "TimepointEmptyFrames" },
};

unsigned short Dict242TagHashTable[] = {
    2,     0,     5,     0,    16,     1,    17,     2,    18,     3,
   19,     4,   113,
};

vtkDICOMDictionary::Dict Dict242Data = {
"MeVis eD: Timepoint Information",
1,
5,
Dict242TagHashTable,
Dict242Contents
};

// ----- astm.org/diconde/iod/NdeCtDetector -----

DictEntry Dict243Contents[] = {
{ 0x0009, 0x0011, 0, VR::DS, VM::M1, "InternalDetectorFrameTime" },
{ 0x0009, 0x0012, 0, VR::DS, VM::M1, "NumberOfFramesIntegrated" },
{ 0x0009, 0x0020, 0, VR::SQ, VM::M1, "DetectorTemperatureSequence" },
{ 0x0009, 0x0022, 0, VR::DS, VM::M1, "SensorName" },
{ 0x0009, 0x0024, 0, VR::DS, VM::M1, "HorizontalOffsetOfSensor" },
{ 0x0009, 0x0026, 0, VR::DS, VM::M1, "VerticalOffsetOfSensor" },
{ 0x0009, 0x0028, 0, VR::DS, VM::M1, "SensorTemperature" },
};

unsigned short Dict243TagHashTable[] = {
    2,     0,     7,     0,    17,     1,    18,     2,    32,     3,
   34,     4,    36,     5,    38,     6,    40,
};

vtkDICOMDictionary::Dict Dict243Data = {
"astm.org/diconde/iod/NdeCtDetector",
1,
7,
Dict243TagHashTable,
Dict243Contents
};

// ----- PAPYRUS -----

DictEntry Dict244Contents[] = {
{ 0x0009, 0x0000, 0, VR::LT, VM::M1, "OriginalFileName" },
{ 0x0009, 0x0010, 0, VR::LT, VM::M1, "OriginalFileLocation" },
{ 0x0009, 0x0018, 0, VR::LT, VM::M1, "DataSetIdentifier" },
{ 0x0041, 0x0000, 0, VR::LT, VM::M1TN, "PapyrusComments" },
{ 0x0041, 0x0010, 0, VR::US, VM::M1, "FolderType" },
{ 0x0041, 0x0011, 0, VR::LT, VM::M1, "PatientFolderDataSetID" },
{ 0x0041, 0x0020, 0, VR::LT, VM::M1, "FolderName" },
{ 0x0041, 0x0030, 0, VR::DA, VM::M1, "CreationDate" },
{ 0x0041, 0x0032, 0, VR::TM, VM::M1, "CreationTime" },
{ 0x0041, 0x0034, 0, VR::DA, VM::M1, "ModifiedDate" },
{ 0x0041, 0x0036, 0, VR::TM, VM::M1, "ModifiedTime" },
{ 0x0041, 0x0040, 0, VR::LT, VM::M1TN, "OwnerName" },
{ 0x0041, 0x0050, 0, VR::LT, VM::M1, "FolderStatus" },
{ 0x0041, 0x0060, 0, VR::UL, VM::M1, "NumberOfImages" },
{ 0x0041, 0x0062, 0, VR::UL, VM::M1, "NumberOfOther" },
{ 0x0041, 0x00a0, 0, VR::LT, VM::M1TN, "ExternalFolderElementDSID" },
{ 0x0041, 0x00a1, 0, VR::US, VM::M1TN, "ExternalFolderElementDataSetType" },
{ 0x0041, 0x00a2, 0, VR::LT, VM::M1TN, "ExternalFolderElementFileLocation" },
{ 0x0041, 0x00a3, 0, VR::UL, VM::M1TN, "ExternalFolderElementLength" },
{ 0x0041, 0x00b0, 0, VR::LT, VM::M1TN, "InternalFolderElementDSID" },
{ 0x0041, 0x00b1, 0, VR::US, VM::M1TN, "InternalFolderElementDataSetType" },
{ 0x0041, 0x00b2, 0, VR::UL, VM::M1TN, "InternalOffsetToDataSet" },
{ 0x0041, 0x00b3, 0, VR::UL, VM::M1TN, "InternalOffsetToImage" },
};

unsigned short Dict244TagHashTable[] = {
    6,    17,    30,    41,    48,     0,     5,     1,    16,     4,
   16,    14,    98,    18,   163,    21,   178,     6,     5,    17,
    6,    32,     9,    52,    11,    64,    15,   160,    22,   179,
    5,     2,    24,     7,    48,    12,    80,    16,   161,    19,
  176,     3,    10,    54,    13,    96,    20,   177,     4,     0,
    0,     3,     0,     8,    50,    17,   162,
};

vtkDICOMDictionary::Dict Dict244Data = {
"PAPYRUS",
5,
23,
Dict244TagHashTable,
Dict244Contents
};

// ----- Philips Imaging DD 070 -----

DictEntry Dict245Contents[] = {
{ 0x4001, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x4001, 0x0011, 0, VR::SQ, VM::M1, "" },
{ 0x4001, 0x0012, 0, VR::SQ, VM::M1, "" },
{ 0x4001, 0x0016, 0, VR::ST, VM::M1, "" },
{ 0x4001, 0x0017, 0, VR::ST, VM::M1, "" },
{ 0x4001, 0x0018, 0, VR::ST, VM::M1, "" },
{ 0x4001, 0x001c, 0, VR::SQ, VM::M1, "" },
{ 0x4001, 0x001d, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict245TagHashTable[] = {
    3,    10,     0,     3,     1,    17,     4,    23,     7,    29,
    5,     0,    16,     2,    18,     3,    22,     5,    24,     6,
   28,
};

vtkDICOMDictionary::Dict Dict245Data = {
"Philips Imaging DD 070",
2,
8,
Dict245TagHashTable,
Dict245Contents
};

// ----- TOSHIBA_MEC_XA3 -----

DictEntry Dict246Contents[] = {
{ 0x7079, 0x0021, 0, VR::SH, VM::M5, "" },
{ 0x7079, 0x0022, 0, VR::IS, VM::M2, "" },
{ 0x7079, 0x0023, 0, VR::IS, VM::M2, "" },
{ 0x7079, 0x0024, 0, VR::DS, VM::M1, "" },
{ 0x7079, 0x0025, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0026, 0, VR::DS, VM::M2, "" },
{ 0x7079, 0x0027, 0, VR::US, VM::M2, "" },
{ 0x7079, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x002a, 0, VR::US, VM::M5, "" },
{ 0x7079, 0x002c, 0, VR::SH, VM::M3, "" },
{ 0x7079, 0x002d, 0, VR::SS, VM::M2, "" },
{ 0x7079, 0x002e, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x002f, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x0031, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0032, 0, VR::SH, VM::M2, "" },
{ 0x7079, 0x0033, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0034, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0035, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0036, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0037, 0, VR::US, VM::M4, "" },
{ 0x7079, 0x0038, 0, VR::SS, VM::M1TN, "" },
{ 0x7079, 0x0039, 0, VR::SS, VM::M1TN, "" },
{ 0x7079, 0x003a, 0, VR::US, VM::M2, "" },
{ 0x7079, 0x003b, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x003c, 0, VR::DS, VM::M2, "" },
{ 0x7079, 0x003d, 0, VR::SS, VM::M2, "" },
{ 0x7079, 0x003e, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x003f, 0, VR::US, VM::M2, "" },
{ 0x7079, 0x0040, 0, VR::SH, VM::M2, "" },
{ 0x7079, 0x0041, 0, VR::SS, VM::M2, "" },
{ 0x7079, 0x0042, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0043, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x0045, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0046, 0, VR::SS, VM::M1, "" },
{ 0x7079, 0x0047, 0, VR::SS, VM::M18, "" },
{ 0x7079, 0x0048, 0, VR::US, VM::M12, "" },
{ 0x7079, 0x0049, 0, VR::US, VM::M3, "" },
{ 0x7079, 0x004a, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x004b, 0, VR::LO, VM::M3, "" },
{ 0x7079, 0x004c, 0, VR::OB, VM::M1, "" },
{ 0x7079, 0x004d, 0, VR::SH, VM::M3, "" },
{ 0x7079, 0x004e, 0, VR::SL, VM::M35, "" },
{ 0x7079, 0x004f, 0, VR::SH, VM::M3, "" },
{ 0x7079, 0x0050, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0051, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x0053, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0054, 0, VR::US, VM::M5, "" },
{ 0x7079, 0x0055, 0, VR::UL, VM::M47T47N, "" },
{ 0x7079, 0x0056, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x0057, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0058, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x0059, 0, VR::US, VM::M2T2N, "" },
{ 0x7079, 0x005a, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x005b, 0, VR::US, VM::M2, "" },
{ 0x7079, 0x005c, 0, VR::US, VM::M2T2N, "" },
{ 0x7079, 0x005d, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x005e, 0, VR::US, VM::M2, "" },
{ 0x7079, 0x005f, 0, VR::SS, VM::M4T4N, "" },
{ 0x7079, 0x0060, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0061, 0, VR::SS, VM::M30T30N, "" },
{ 0x7079, 0x0062, 0, VR::US, VM::M4, "" },
{ 0x7079, 0x0063, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0064, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0065, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0066, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0067, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0068, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x0069, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x006a, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x006b, 0, VR::US, VM::M1TN, "" },
{ 0x7079, 0x006c, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x006d, 0, VR::DS, VM::M1, "" },
{ 0x7079, 0x006e, 0, VR::LO, VM::M1, "" },
{ 0x7079, 0x006f, 0, VR::DS, VM::M1, "" },
{ 0x7079, 0x0070, 0, VR::DS, VM::M1, "" },
{ 0x7079, 0x0071, 0, VR::DS, VM::M1TN, "" },
{ 0x7079, 0x0072, 0, VR::DS, VM::M1TN, "" },
{ 0x7079, 0x0073, 0, VR::SL, VM::M4, "" },
{ 0x7079, 0x0074, 0, VR::SL, VM::M28, "" },
{ 0x7079, 0x0075, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0076, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x0077, 0, VR::SL, VM::M1, "" },
{ 0x7079, 0x0078, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x0079, 0, VR::US, VM::M1, "" },
{ 0x7079, 0x007b, 0, VR::SH, VM::M1, "" },
{ 0x7079, 0x0080, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict246TagHashTable[] = {
   23,    34,    45,    56,    67,    76,    85,    94,   103,   112,
  121,   130,   137,   146,   151,   160,   169,   180,   189,   196,
  205,   214,     0,     5,     3,    36,    27,    62,    42,    77,
   68,   103,    78,   113,     5,     4,    37,    28,    63,    41,
   76,    67,   102,    77,   112,     5,     5,    38,    13,    48,
   44,    79,    54,    89,    80,   115,     5,     6,    39,    14,
   49,    43,    78,    53,    88,    79,   114,     4,    15,    50,
   30,    65,    56,    91,    82,   117,     4,    16,    51,    29,
   64,    55,    90,    81,   116,     4,    17,    52,    32,    67,
   58,    93,    84,   119,     4,    18,    53,    31,    66,    57,
   92,    83,   118,     4,    19,    54,    34,    69,    60,    95,
   70,   105,     4,    20,    55,    33,    68,    59,    94,    69,
  104,     4,     7,    40,    36,    71,    46,    81,    72,   107,
    3,    35,    70,    45,    80,    71,   106,     4,     8,    42,
   48,    83,    74,   109,    88,   128,     2,    47,    82,    73,
  108,     4,     9,    44,    50,    85,    76,   111,    86,   121,
    4,    10,    45,    49,    84,    75,   110,    85,   120,     5,
   11,    46,    21,    56,    52,    87,    62,    97,    87,   123,
    4,    12,    47,    22,    57,    51,    86,    61,    96,     3,
   23,    58,    38,    73,    64,    99,     4,     0,    33,    24,
   59,    37,    72,    63,    98,     4,     1,    34,    25,    60,
   40,    75,    66,   101,     4,     2,    35,    26,    61,    39,
   74,    65,   100,
};

vtkDICOMDictionary::Dict Dict246Data = {
"TOSHIBA_MEC_XA3",
22,
89,
Dict246TagHashTable,
Dict246Contents
};

// ----- Philips Imaging DD 073 -----

DictEntry Dict247Contents[] = {
{ 0x4007, 0x0048, 0, VR::FL, VM::M1, "" },
};

unsigned short Dict247TagHashTable[] = {
    2,     0,     1,     0,    72,
};

vtkDICOMDictionary::Dict Dict247Data = {
"Philips Imaging DD 073",
1,
1,
Dict247TagHashTable,
Dict247Contents
};

// ----- SEGAMI_HEADER -----

DictEntry Dict248Contents[] = {
{ 0x0029, 0x0031, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0032, 0, VR::OW, VM::M1, "" },
};

unsigned short Dict248TagHashTable[] = {
    2,     0,     2,     0,    49,     1,    50,
};

vtkDICOMDictionary::Dict Dict248Data = {
"SEGAMI_HEADER",
1,
2,
Dict248TagHashTable,
Dict248Contents
};

// ----- SIEMENS MR VA0  GEN -----

DictEntry Dict249Contents[] = {
{ 0x0019, 0x0010, 0, VR::DS, VM::M1, "TotalMeasurementTimeNominal" },
{ 0x0019, 0x0011, 0, VR::DS, VM::M1, "TotalMeasurementTimeCurrent" },
{ 0x0019, 0x0012, 0, VR::DS, VM::M1, "StartDelayTime" },
{ 0x0019, 0x0013, 0, VR::DS, VM::M1, "DwellTime" },
{ 0x0019, 0x0014, 0, VR::IS, VM::M1, "NumberOfPhases" },
{ 0x0019, 0x0016, 0, VR::UL, VM::M2, "SequenceControlMask" },
{ 0x0019, 0x0018, 0, VR::UL, VM::M1, "MeasurementStatusMask" },
{ 0x0019, 0x0020, 0, VR::IS, VM::M1, "NumberOfFourierLinesNominal" },
{ 0x0019, 0x0021, 0, VR::IS, VM::M1, "NumberOfFourierLinesCurrent" },
{ 0x0019, 0x0026, 0, VR::IS, VM::M1, "NumberOfFourierLinesAfterZero" },
{ 0x0019, 0x0028, 0, VR::IS, VM::M1, "FirstMeasuredFourierLine" },
{ 0x0019, 0x0030, 0, VR::IS, VM::M1, "AcquisitionColumns" },
{ 0x0019, 0x0031, 0, VR::IS, VM::M1, "ReconstructionColumns" },
{ 0x0019, 0x0040, 0, VR::IS, VM::M1, "ArrayCoilElementNumber" },
{ 0x0019, 0x0041, 0, VR::UL, VM::M1, "ArrayCoilElementSelectMask" },
{ 0x0019, 0x0042, 0, VR::UL, VM::M1, "ArrayCoilElementDataMask" },
{ 0x0019, 0x0043, 0, VR::IS, VM::M1TN, "ArrayCoilElementToADCConnect" },
{ 0x0019, 0x0044, 0, VR::DS, VM::M1TN, "ArrayCoilElementNoiseLevel" },
{ 0x0019, 0x0045, 0, VR::IS, VM::M1, "ArrayCoilADCPairNumber" },
{ 0x0019, 0x0046, 0, VR::UL, VM::M1, "ArrayCoilCombinationMask" },
{ 0x0019, 0x0050, 0, VR::IS, VM::M1, "NumberOfAveragesCurrent" },
{ 0x0019, 0x0060, 0, VR::DS, VM::M1, "FlipAngle" },
{ 0x0019, 0x0070, 0, VR::IS, VM::M1, "NumberOfPrescans" },
{ 0x0019, 0x0081, 0, VR::CS, VM::M1, "FilterTypeForRawData" },
{ 0x0019, 0x0082, 0, VR::DS, VM::M1TN, "FilterParameterForRawData" },
{ 0x0019, 0x0083, 0, VR::CS, VM::M1, "FilterTypeForImageData" },
{ 0x0019, 0x0084, 0, VR::DS, VM::M1TN, "FilterParameterForImageData" },
{ 0x0019, 0x0085, 0, VR::CS, VM::M1, "FilterTypeForPhaseCorrection" },
{ 0x0019, 0x0086, 0, VR::DS, VM::M1TN, "FilterParameterForPhaseCorrection" },
{ 0x0019, 0x0087, 0, VR::CS, VM::M1, "NormalizationFilterTypeForImageData" },
{ 0x0019, 0x0088, 0, VR::DS, VM::M1TN, "NormalizationFilterParameterForImageData" },
{ 0x0019, 0x0090, 0, VR::IS, VM::M1, "NumberOfSaturationRegions" },
{ 0x0019, 0x0091, 0, VR::DS, VM::M6, "SaturationPhaseEncodingVectorSagittalComponent" },
{ 0x0019, 0x0092, 0, VR::DS, VM::M6, "SaturationReadoutVectorSagittalComponent" },
{ 0x0019, 0x0093, 0, VR::IS, VM::M1, "EPIStimulationMonitorMode" },
{ 0x0019, 0x0094, 0, VR::DS, VM::M1, "ImageRotationAngle" },
{ 0x0019, 0x0096, 0, VR::UL, VM::M3, "CoilIDMask" },
{ 0x0019, 0x0097, 0, VR::UL, VM::M2, "CoilClassMask" },
{ 0x0019, 0x0098, 0, VR::DS, VM::M3, "CoilPosition" },
{ 0x0019, 0x00a0, 0, VR::DS, VM::M1, "EPIReconstructionPhase" },
{ 0x0019, 0x00a1, 0, VR::DS, VM::M1, "EPIReconstructionSlope" },
{ 0x0021, 0x0020, 0, VR::IS, VM::M1, "PhaseCorrectionRowsSequence" },
{ 0x0021, 0x0021, 0, VR::IS, VM::M1, "PhaseCorrectionColumnsSequence" },
{ 0x0021, 0x0022, 0, VR::IS, VM::M1, "PhaseCorrectionRowsReconstruction" },
{ 0x0021, 0x0024, 0, VR::IS, VM::M1, "PhaseCorrectionColumnsReconstruction" },
{ 0x0021, 0x0030, 0, VR::IS, VM::M1, "NumberOf3DRawPartitionsNominal" },
{ 0x0021, 0x0031, 0, VR::IS, VM::M1, "NumberOf3DRawPartitionsCurrent" },
{ 0x0021, 0x0034, 0, VR::IS, VM::M1, "NumberOf3DImagePartitions" },
{ 0x0021, 0x0036, 0, VR::IS, VM::M1, "Actual3DImagePartitionNumber" },
{ 0x0021, 0x0039, 0, VR::DS, VM::M1, "SlabThickness" },
{ 0x0021, 0x0040, 0, VR::IS, VM::M1, "NumberOfSlicesNominal" },
{ 0x0021, 0x0041, 0, VR::IS, VM::M1, "NumberOfSlicesCurrent" },
{ 0x0021, 0x0042, 0, VR::IS, VM::M1, "CurrentSliceNumber" },
{ 0x0021, 0x0043, 0, VR::IS, VM::M1, "CurrentGroupNumber" },
{ 0x0021, 0x0044, 0, VR::DS, VM::M1, "CurrentSliceDistanceFactor" },
{ 0x0021, 0x0045, 0, VR::IS, VM::M1, "MIPStartRow" },
{ 0x0021, 0x0046, 0, VR::IS, VM::M1, "MIPStopRow" },
{ 0x0021, 0x0047, 0, VR::IS, VM::M1, "MIPStartColumn" },
{ 0x0021, 0x0048, 0, VR::IS, VM::M1, "MIPStartColumn" },
{ 0x0021, 0x0049, 0, VR::IS, VM::M1, "MIPStartSlice" },
{ 0x0021, 0x004a, 0, VR::IS, VM::M1, "MIPStartSlice" },
{ 0x0021, 0x004f, 0, VR::CS, VM::M1, "OrderofSlices" },
{ 0x0021, 0x0050, 0, VR::UL, VM::M1TN, "SignalMask" },
{ 0x0021, 0x0052, 0, VR::IS, VM::M1, "DelayAfterTrigger" },
{ 0x0021, 0x0053, 0, VR::IS, VM::M1, "RRInterval" },
{ 0x0021, 0x0054, 0, VR::DS, VM::M1, "NumberOfTriggerPulses" },
{ 0x0021, 0x0056, 0, VR::DS, VM::M1, "RepetitionTimeEffective" },
{ 0x0021, 0x0057, 0, VR::LO, VM::M1, "GatePhase" },
{ 0x0021, 0x0058, 0, VR::DS, VM::M1, "GateThreshold" },
{ 0x0021, 0x0059, 0, VR::DS, VM::M1, "GatedRatio" },
{ 0x0021, 0x0060, 0, VR::IS, VM::M1, "NumberOfInterpolatedImages" },
{ 0x0021, 0x0070, 0, VR::IS, VM::M1, "NumberOfEchoes" },
{ 0x0021, 0x0072, 0, VR::DS, VM::M1, "SecondRepetitionTime" },
{ 0x0021, 0x0073, 0, VR::DS, VM::M1, "SecondRepetitionTime" },
{ 0x0021, 0x0080, 0, VR::IS, VM::M1, "CardiacCode" },
{ 0x0021, 0x0091, 0, VR::DS, VM::M6, "SaturationPhaseEncodingVectorTransverseComponent" },
{ 0x0021, 0x0092, 0, VR::DS, VM::M6, "SaturationReadoutVectorTransverseComponent" },
{ 0x0021, 0x0093, 0, VR::DS, VM::M1, "EPIChangeValueOfMagnitude" },
{ 0x0021, 0x0094, 0, VR::DS, VM::M1, "EPIChangeValueOfXComponent" },
{ 0x0021, 0x0095, 0, VR::DS, VM::M1, "EPIChangeValueOfYComponent" },
{ 0x0021, 0x0096, 0, VR::DS, VM::M1, "EPIChangeValueOfZComponent" },
};

unsigned short Dict249TagHashTable[] = {
   21,    36,    53,    60,    77,    86,    91,    96,   101,   106,
  113,   118,   127,   136,   143,   150,   155,   170,   183,   194,
    0,     7,    12,    49,    21,    96,    37,   151,    42,    33,
   54,    68,    68,    88,    71,   112,     8,     6,    24,    11,
   48,    36,   150,    41,    32,    47,    52,    55,    69,    69,
   89,    80,   150,     3,    56,    70,    72,   114,    79,   149,
    8,     9,    38,    35,   148,    43,    34,    48,    54,    57,
   71,    73,   115,    74,   128,    78,   148,     4,    22,   112,
   49,    57,    58,    72,    70,    96,     2,    44,    36,    59,
   73,     2,    40,   161,    60,    74,     2,    30,   136,    39,
  160,     2,     1,    17,    13,    64,     3,     0,    16,    10,
   40,    14,    65,     2,     3,    19,    15,    66,     4,     2,
   18,    16,    67,    38,   152,    61,    79,     4,    17,    68,
   20,    80,    25,   131,    62,    80,     3,     4,    20,    18,
   69,    24,   130,     3,    19,    70,    23,   129,    63,    82,
    2,     5,    22,    64,    83,     7,     8,    33,    29,   135,
   34,   147,    46,    49,    50,    64,    65,    84,    77,   147,
    6,     7,    32,    28,   134,    33,   146,    45,    48,    51,
   65,    76,   146,     5,    27,   133,    32,   145,    52,    66,
   66,    86,    75,   145,     4,    26,   132,    31,   144,    53,
   67,    67,    87,
};

vtkDICOMDictionary::Dict Dict249Data = {
"SIEMENS MR VA0  GEN",
20,
81,
Dict249TagHashTable,
Dict249Contents
};

// ----- Silhouette Sequence Ids V1.0 -----

DictEntry Dict250Contents[] = {
{ 0x0029, 0x0041, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0042, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0043, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict250TagHashTable[] = {
    2,     0,     3,     0,    65,     1,    66,     2,    67,
};

vtkDICOMDictionary::Dict Dict250Data = {
"Silhouette Sequence Ids V1.0",
1,
3,
Dict250TagHashTable,
Dict250Contents
};

// ----- SIEMENS SYNGO ADVANCED PRESENTATION -----

DictEntry Dict251Contents[] = {
{ 0x0029, 0x0000, 0, VR::CS, VM::M1, "PresentationName" },
{ 0x0029, 0x0001, 0, VR::CS, VM::M1, "PresentationType" },
{ 0x0029, 0x0002, 0, VR::SQ, VM::M1, "AdvancedPresentationSequence" },
{ 0x0029, 0x0003, 0, VR::SQ, VM::M1, "TimePointSequence" },
{ 0x0029, 0x0004, 0, VR::SQ, VM::M1, "BaseImageSequence" },
{ 0x0029, 0x0005, 0, VR::SQ, VM::M1, "OverlayImageSequence" },
{ 0x0029, 0x0006, 0, VR::SQ, VM::M1, "RegistrationInstanceSequence" },
{ 0x0029, 0x0007, 0, VR::SQ, VM::M1, "RealWorldValueMappingInstanceSequence" },
{ 0x0029, 0x0008, 0, VR::SQ, VM::M1, "MeasurementSequence" },
{ 0x0029, 0x0009, 0, VR::UI, VM::M1, "MeasurementUID" },
{ 0x0029, 0x0010, 0, VR::SQ, VM::M1, "SegmentationSequence" },
{ 0x0029, 0x0011, 0, VR::UI, VM::M1, "SegmentationUID" },
{ 0x0029, 0x0012, 0, VR::SQ, VM::M1, "NavigationSequence" },
{ 0x0029, 0x0013, 0, VR::CS, VM::M1, "NavigationName" },
{ 0x0029, 0x0014, 0, VR::CS, VM::M1, "AutoNavigationDirection" },
{ 0x0029, 0x0015, 0, VR::DS, VM::M1, "AutoNavigationFrameRate" },
{ 0x0029, 0x0016, 0, VR::CS, VM::M1, "AutoNavigationMode" },
{ 0x0029, 0x0017, 0, VR::DS, VM::M1, "AutoNavigationRealtimeSpeed" },
{ 0x0029, 0x0018, 0, VR::CS, VM::M1, "AutoNavigationStrategy" },
{ 0x0029, 0x0019, 0, VR::CS, VM::M1, "AutoNavigationRealtimeFlag" },
{ 0x0029, 0x0020, 0, VR::IS, VM::M1, "IndexNavigationCurrentIndex" },
{ 0x0029, 0x0021, 0, VR::IS, VM::M1, "IndexAutoNavigationSkippingDegree" },
{ 0x0029, 0x0022, 0, VR::DS, VM::M1, "VolumeNavigationMinimumPixelSpacing" },
{ 0x0029, 0x0023, 0, VR::CS, VM::M1, "VolumeNavigationScrollUnit" },
{ 0x0029, 0x0024, 0, VR::DS, VM::M1, "VolumeNavigationStepSize" },
{ 0x0029, 0x0025, 0, VR::DS, VM::M1, "VolumeNavigationJumpSize" },
{ 0x0029, 0x0026, 0, VR::IS, VM::M1, "ReferencedRegistrationNumber" },
{ 0x0029, 0x0027, 0, VR::UI, VM::M1, "RealWorldValueMappingUID" },
{ 0x0029, 0x0028, 0, VR::DS, VM::M1, "ChannelAlphaValue" },
{ 0x0029, 0x0030, 0, VR::LO, VM::M1, "MeasurementApplicationName" },
{ 0x0029, 0x0031, 0, VR::SQ, VM::M1, "MeasurementDataSequence" },
{ 0x0029, 0x0032, 0, VR::LO, VM::M1, "MeasurementType" },
{ 0x0029, 0x0033, 0, VR::UI, VM::M1, "MeasurementFrameOfReferenceUID" },
{ 0x0029, 0x0034, 0, VR::UI, VM::M1, "MeasurementUid" },
{ 0x0029, 0x0035, 0, VR::IS, VM::M1, "MeasurementApplicationNumber" },
{ 0x0029, 0x0036, 0, VR::ST, VM::M1, "MeasurementApplicationNumberPrefixText" },
{ 0x0029, 0x0037, 0, VR::CS, VM::M1, "MeasurementGraphicIsVisibleFlag" },
{ 0x0029, 0x0038, 0, VR::UI, VM::M4, "ReferencedSyngoUID" },
{ 0x0029, 0x0039, 0, VR::UI, VM::M1, "ClinicalFindingUID" },
{ 0x0029, 0x003A, 0, VR::CS, VM::M1, "MeasurementEvaluationStringValue" },
{ 0x0029, 0x003B, 0, VR::IS, VM::M1, "MeasurementEvaluationIntegerValue" },
{ 0x0029, 0x003C, 0, VR::FL, VM::M1, "MeasurementEvaluationDecimalValue" },
{ 0x0029, 0x003D, 0, VR::CS, VM::M1, "MeasurementLineShowCenterFlag" },
{ 0x0029, 0x003E, 0, VR::CS, VM::M1, "MeasurementAngleShowArrowTipFlag" },
{ 0x0029, 0x003F, 0, VR::SQ, VM::M1, "CameraHomeSettingsSequence" },
{ 0x0029, 0x0040, 0, VR::DS, VM::M1, "CameraZoom" },
{ 0x0029, 0x0041, 0, VR::DS, VM::M3, "CameraPosition" },
{ 0x0029, 0x0042, 0, VR::DS, VM::M4, "CameraOrientation" },
{ 0x0029, 0x0043, 0, VR::DS, VM::M1, "CameraFarClipPlane" },
{ 0x0029, 0x0044, 0, VR::DS, VM::M1, "CameraNearClipPlane" },
{ 0x0029, 0x0045, 0, VR::DS, VM::M1, "CameraThickness" },
{ 0x0029, 0x0046, 0, VR::DS, VM::M1, "CameraViewPortSize" },
{ 0x0029, 0x0047, 0, VR::DS, VM::M1, "CameraAspectRatio" },
{ 0x0029, 0x0048, 0, VR::LO, VM::M1, "CameraProjectionType" },
{ 0x0029, 0x0049, 0, VR::DS, VM::M1, "CameraFieldOfView" },
{ 0x0029, 0x004A, 0, VR::DS, VM::M1, "CameraImagePlaneDistance" },
{ 0x0029, 0x004B, 0, VR::DS, VM::M1, "CameraImageMaximumHeight" },
{ 0x0029, 0x004C, 0, VR::DS, VM::M1, "CameraImageMinimumHeight" },
{ 0x0029, 0x004D, 0, VR::DS, VM::M1, "ParallelShiftIntervalMM" },
{ 0x0029, 0x004E, 0, VR::DS, VM::M3, "ParallelShiftBoundingBoxMinimum" },
{ 0x0029, 0x004F, 0, VR::DS, VM::M3, "ParallelShiftBoundingBoxMaximum" },
{ 0x0029, 0x0050, 0, VR::CS, VM::M1, "RendererVertexIsCharacteristicFlag" },
{ 0x0029, 0x0051, 0, VR::CS, VM::M1, "RendererThicknessUsageFlag" },
{ 0x0029, 0x0052, 0, VR::DS, VM::M4, "RendererThreshold" },
{ 0x0029, 0x0053, 0, VR::DS, VM::M4, "RendererMaterial" },
{ 0x0029, 0x0054, 0, VR::DS, VM::M4, "RendererDirectionalLightColor" },
{ 0x0029, 0x0055, 0, VR::DS, VM::M3, "RendererDirectionalLightDirection" },
{ 0x0029, 0x0056, 0, VR::CS, VM::M1, "RendererDirectionalLightTwoSideUsageFlag" },
{ 0x0029, 0x0057, 0, VR::SQ, VM::M1, "RendererPWLTransferFunctionSequence" },
{ 0x0029, 0x0058, 0, VR::IS, VM::M0TN, "RendererPWLVertexIndex" },
{ 0x0029, 0x0059, 0, VR::DS, VM::M0TN, "RendererPWLVertexColor" },
{ 0x0029, 0x005A, 0, VR::CS, VM::M1, "RendererIsCameraRequiredFlag" },
{ 0x0029, 0x005B, 0, VR::CS, VM::M1, "RendererDoDepthTestFlag" },
{ 0x0029, 0x005C, 0, VR::CS, VM::M1, "RendererDirectionalLightUsageFlag" },
{ 0x0029, 0x005D, 0, VR::SQ, VM::M1, "RendererThicknessSequence" },
{ 0x0029, 0x005E, 0, VR::SQ, VM::M0TN, "RendererSliceSpacingSequence" },
{ 0x0029, 0x005F, 0, VR::DS, VM::M1, "RendererSamplingDistance" },
{ 0x0029, 0x0060, 0, VR::DS, VM::M1, "RendererInitialSamplingDistance" },
{ 0x0029, 0x0061, 0, VR::SQ, VM::M1, "SegmentationDisplayDataSequence" },
{ 0x0029, 0x0062, 0, VR::UI, VM::M0TN, "SegmentationDisplayDataUID" },
{ 0x0029, 0x0063, 0, VR::SQ, VM::M1, "SegmentationDisplayParameterSequence" },
{ 0x0029, 0x0064, 0, VR::LO, VM::M1, "SegmentationDisplayParameterType" },
{ 0x0029, 0x0065, 0, VR::LO, VM::M1, "SegmentationDisplayVisibility" },
{ 0x0029, 0x0066, 0, VR::DS, VM::M4, "SegmentationDisplayColor" },
{ 0x0029, 0x0067, 0, VR::CS, VM::M1, "SegmentationDisplayIsSelectedFlag" },
{ 0x0029, 0x0068, 0, VR::OB, VM::M1, "SegmentationAdditionalInformationBlob" },
{ 0x0029, 0x0069, 0, VR::ST, VM::M1, "HashCodeValue" },
{ 0x0029, 0x006A, 0, VR::LO, VM::M1TN, "SegmentationVersionIdentifier" },
{ 0x0029, 0x0070, 0, VR::DS, VM::M3, "SegmentationVolumeSize" },
{ 0x0029, 0x0071, 0, VR::UI, VM::M1TN, "RegistrationReferencedFrames" },
{ 0x0029, 0x0072, 0, VR::UI, VM::M1TN, "RegistrationReferencedRegistrations" },
{ 0x0029, 0x0073, 0, VR::LO, VM::M1, "RegistrationCreationAlgorithmName" },
{ 0x0029, 0x0074, 0, VR::CS, VM::M1, "ECGGraphicType" },
{ 0x0029, 0x007A, 0, VR::DS, VM::M1, "SegmentationVolumeStorageDataType" },
{ 0x0029, 0x007B, 0, VR::FL, VM::M16, "SegmentationVolumeModelMatrix" },
{ 0x0029, 0x0080, 0, VR::DS, VM::M3, "CameraRotationAxis" },
{ 0x0029, 0x0081, 0, VR::SL, VM::M0TN, "OverlayHiddenDisplayAttributes" },
{ 0x0029, 0x0082, 0, VR::LO, VM::M1, "PresentationStateGroupIdentifier" },
{ 0x0029, 0x0083, 0, VR::US, VM::M1, "TemporarySmallestImagePixelValue" },
{ 0x0029, 0x0084, 0, VR::DS, VM::M3, "CameraRotationCenter" },
{ 0x0029, 0x0085, 0, VR::CS, VM::M1, "CameraRotationCenterUsageFlag" },
{ 0x0029, 0x0086, 0, VR::DS, VM::M12, "CameraParallelEpiped" },
{ 0x0029, 0x0087, 0, VR::DS, VM::M1, "CameraMaxZoomInFactor" },
{ 0x0029, 0x0088, 0, VR::DS, VM::M1, "CameraMinZoomInFactor" },
{ 0x0029, 0x0089, 0, VR::US, VM::M1, "TemporaryLargestImagePixelValue" },
{ 0x0029, 0x008A, 0, VR::CS, VM::M1, "CameraRotationAxisUsageFlag" },
{ 0x0029, 0x008B, 0, VR::DS, VM::M3, "MeasurementSurfaceNormal" },
{ 0x0029, 0x008C, 0, VR::FL, VM::M16, "MeasurementEllipsoidModelMatrix" },
{ 0x0029, 0x008D, 0, VR::LO, VM::M1, "MeasurementEvaluationDataRoleID" },
{ 0x0029, 0x008E, 0, VR::LO, VM::M1, "MeasurementAlgorithmType" },
{ 0x0029, 0x0091, 0, VR::SQ, VM::M1, "MeasurementEvaluationDataRoleSequence" },
{ 0x0029, 0x0092, 0, VR::CS, VM::M1, "MeasurementEvaluationDataRoleItem" },
{ 0x0029, 0x0093, 0, VR::SQ, VM::M1, "MeasurementEvaluationSequence" },
{ 0x0029, 0x0094, 0, VR::DS, VM::M1, "MeasurementEvaluationValue" },
{ 0x0029, 0x0095, 0, VR::CS, VM::M1, "MeasurementEvaluationID" },
{ 0x0029, 0x0096, 0, VR::FL, VM::M0TN, "MeasurementDataPoints" },
{ 0x0029, 0x0097, 0, VR::FL, VM::M0TN, "MeasurementDataAngles" },
{ 0x0029, 0x0098, 0, VR::LO, VM::M1, "MeasurementDataSlice" },
{ 0x0029, 0x0099, 0, VR::FL, VM::M1, "MeasurementDataSliceThickness" },
{ 0x0029, 0x009A, 0, VR::SQ, VM::M1, "MeasurementReferencedFramesSequence" },
{ 0x0029, 0x009B, 0, VR::DS, VM::M0TN, "MeasurementEvaluationLongestDistance" },
{ 0x0029, 0x009C, 0, VR::DS, VM::M0TN, "MeasurementEvaluationCentroid" },
{ 0x0029, 0x009D, 0, VR::FL, VM::M6, "MeasurementDataBoundingBox" },
{ 0x0029, 0x009E, 0, VR::LO, VM::M1, "MeasurementText" },
{ 0x0029, 0x009F, 0, VR::IS, VM::M1, "MeasurementDiameter" },
{ 0x0029, 0x00A0, 0, VR::DS, VM::M1, "ImageRotationFractional" },
{ 0x0029, 0x00A1, 0, VR::LO, VM::M1, "PresetName" },
{ 0x0029, 0x00A2, 0, VR::SQ, VM::M1, "FusionLUTSequence" },
{ 0x0029, 0x00A3, 0, VR::CS, VM::M1, "FusionLUTIsActiveFlag" },
{ 0x0029, 0x00A5, 0, VR::UI, VM::M1, "SyngoUID" },
{ 0x0029, 0x00A6, 0, VR::UI, VM::M1, "PresentationVersionIdentifier" },
{ 0x0029, 0x00A7, 0, VR::SQ, VM::M1, "PresentationModuleSequence" },
{ 0x0029, 0x00A8, 0, VR::LO, VM::M1, "PresentationModuleType" },
{ 0x0029, 0x00A9, 0, VR::SQ, VM::M1, "PresentationStateSequence" },
{ 0x0029, 0x00AA, 0, VR::CS, VM::M1, "LUTInvertedFlag" },
{ 0x0029, 0x00AB, 0, VR::IS, VM::M1, "SoftcopyVOILUTViewingIndex" },
{ 0x0029, 0x00AC, 0, VR::FD, VM::M2, "DisplayedAreaBottomRightHandCornerFractional" },
{ 0x0029, 0x00AD, 0, VR::FD, VM::M2, "DisplayedAreaTopLeftHandCornerFractional" },
{ 0x0029, 0x00AE, 0, VR::FL, VM::M1, "MeasurementAlpha" },
{ 0x0029, 0x00AF, 0, VR::OB, VM::M1, "MeasurementBitmap" },
{ 0x0029, 0x00B0, 0, VR::US, VM::M1, "CurrentFrameNumber" },
{ 0x0029, 0x00B1, 0, VR::LO, VM::M1, "ImageTextViewName" },
{ 0x0029, 0x00B2, 0, VR::SQ, VM::M1, "ImageTextViewContentSequence" },
{ 0x0029, 0x00B3, 0, VR::LO, VM::M1TN, "ImageTextLineNames" },
{ 0x0029, 0x00B4, 0, VR::LO, VM::M1TN, "ImageTextLineValues" },
{ 0x0029, 0x00B5, 0, VR::SQ, VM::M1, "MeasurementEvaluationTextPositionSequence" },
{ 0x0029, 0x00B6, 0, VR::CS, VM::M1, "MeasurementLinkEvaluationTextFlag" },
{ 0x0029, 0x00B7, 0, VR::DS, VM::M3, "MeasurementEvaluationTextPositionVector" },
{ 0x0029, 0x00B8, 0, VR::OB, VM::M1, "ImageTextAlphaBlendingLineValue" },
{ 0x0029, 0x00C1, 0, VR::SQ, VM::M1, "TaskDataSequence" },
{ 0x0029, 0x00C2, 0, VR::CS, VM::M1, "TaskDataType" },
{ 0x0029, 0x00C3, 0, VR::LO, VM::M1, "TaskDataVersion" },
{ 0x0029, 0x00C4, 0, VR::ST, VM::M1, "TaskDataDescription" },
{ 0x0029, 0x00C5, 0, VR::OB, VM::M1, "TaskData" },
{ 0x0029, 0x00C6, 0, VR::IS, VM::M1, "TaskDataSize" },
{ 0x0029, 0x00C9, 0, VR::SQ, VM::M1, "ClipPlaneSequence" },
{ 0x0029, 0x00CA, 0, VR::DS, VM::M3, "ClipPlaneCenter" },
{ 0x0029, 0x00CB, 0, VR::DS, VM::M3, "ClipPlaneNormal" },
{ 0x0029, 0x00CC, 0, VR::DS, VM::M2, "ClipPlaneScale" },
{ 0x0029, 0x00CD, 0, VR::CS, VM::M1, "ClipPlaneUseThicknessFlag" },
{ 0x0029, 0x00CE, 0, VR::DS, VM::M1, "ClipPlaneThickness" },
{ 0x0029, 0x00CF, 0, VR::SQ, VM::M1, "ImageSequence" },
{ 0x0029, 0x00D0, 0, VR::CS, VM::M1, "ClipPlaneEnableClip" },
{ 0x0029, 0x00D1, 0, VR::DS, VM::M1, "ClipPlaneHandleRatio" },
{ 0x0029, 0x00D2, 0, VR::DS, VM::M24, "ClipPlaneBoundingPoints" },
{ 0x0029, 0x00D3, 0, VR::DS, VM::M16, "ClipPlaneMotionMatrix" },
{ 0x0029, 0x00D4, 0, VR::DS, VM::M1, "ClipPlaneShiftVelocity" },
{ 0x0029, 0x00D5, 0, VR::CS, VM::M1, "ClipPlaneEnabledFlag" },
{ 0x0029, 0x00D6, 0, VR::DS, VM::M1, "ClipPlaneRotateVelocity" },
{ 0x0029, 0x00D7, 0, VR::CS, VM::M1, "ClipPlaneShowGraphicsFlag" },
{ 0x0029, 0x00E0, 0, VR::DS, VM::M3, "CropBoxSize" },
{ 0x0029, 0x00E1, 0, VR::CS, VM::M1, "CropBoxEnabledFlag" },
{ 0x0029, 0x00E2, 0, VR::DS, VM::M3, "CropBoxAbsoluteOrigin" },
{ 0x0029, 0x00E3, 0, VR::CS, VM::M1, "CropBoxShowGraphicsFlag" },
{ 0x0029, 0x00F1, 0, VR::DS, VM::M0TN, "CurvedCameraCoordinates" },
{ 0x0029, 0x00F2, 0, VR::DS, VM::M1, "CurvedCameraPointOfInterest" },
{ 0x0029, 0x00F3, 0, VR::CS, VM::M1, "CurvedCameraPointOfInterestUsageFlag" },
{ 0x0029, 0x00F4, 0, VR::DS, VM::M1, "CurvedCameraThickness" },
{ 0x0029, 0x00F5, 0, VR::DS, VM::M1, "CurvedCameraExtrusionLength" },
{ 0x0029, 0x00F6, 0, VR::CS, VM::M1, "CurvedCameraRotationAxisMode" },
{ 0x0029, 0x00F7, 0, VR::DS, VM::M1, "CurvedCameraRollRotationAxis" },
{ 0x0029, 0x00F8, 0, VR::DS, VM::M1, "CurvedCameraViewPortHeight" },
{ 0x0029, 0x00F9, 0, VR::DS, VM::M1, "CurvedCameraCutDirection" },
{ 0x0029, 0x00FA, 0, VR::DS, VM::M1, "CurvedCameraPanVector" },
{ 0x0029, 0x00FB, 0, VR::LO, VM::M1, "ClinicalFindingID" },
{ 0x0029, 0x00FC, 0, VR::CS, VM::M1, "MeasurementIsCircleFlag" },
{ 0x0029, 0x00FD, 0, VR::LO, VM::M1, "MeasurementApplicationTypeID" },
};

unsigned short Dict251TagHashTable[] = {
   47,    58,    69,    78,    85,    92,    99,   106,   111,   118,
  127,   134,   141,   148,   155,   164,   173,   184,   195,   208,
  221,   232,   241,   250,   259,   270,   281,   290,   301,   310,
  319,   330,   341,   352,   363,   368,   375,   384,   393,   400,
  407,   416,   425,   434,   445,   456,     0,     5,     7,     7,
   92,   116,   112,   147,   126,   161,   158,   204,     5,     6,
    6,    28,    40,   111,   146,   125,   160,   159,   205,     4,
   19,    25,   110,   145,   131,   167,   150,   194,     3,    18,
   24,   130,   166,   151,   195,     3,    53,    72,   116,   151,
  129,   165,     3,    54,    73,   115,   150,   149,   193,     3,
   55,    74,   114,   149,   154,   198,     2,    56,    75,   113,
  148,     3,    21,    33,    57,    76,   152,   196,     4,    20,
   32,    58,    77,   148,   184,   153,   197,     3,    11,    17,
   23,    35,    59,    78,     3,    10,    16,    22,    34,    60,
   79,     3,    13,    19,    25,    37,    45,    64,     3,    12,
   18,    24,    36,    46,    65,     4,    15,    21,    27,    39,
   47,    66,   143,   179,     4,    14,    20,    26,    38,    48,
   67,   142,   178,     5,    17,    23,    38,    57,    49,    68,
  141,   177,   172,   226,     5,    16,    22,    37,    56,    50,
   69,   140,   176,   173,   227,     6,    40,    59,    51,    70,
   85,   104,   147,   183,   164,   210,   170,   224,     6,    39,
   58,    52,    71,    86,   105,   146,   182,   165,   211,   171,
  225,     5,    42,    61,    69,    88,    87,   106,   145,   181,
  162,   208,     4,    41,    60,    70,    89,   144,   180,   163,
  209,     4,    44,    63,    71,    90,   106,   139,   168,   214,
    4,    43,    62,    72,    91,   105,   138,   169,   215,     5,
   30,    49,    73,    92,   104,   137,   166,   212,   183,   250,
    5,    29,    48,    74,    93,   103,   136,   167,   213,   184,
  251,     4,    32,    51,    75,    94,    77,    96,   181,   248,
    5,    31,    50,    76,    95,    78,    97,   109,   142,   182,
  249,     4,    34,    53,    61,    80,    79,    98,   108,   141,
    4,    33,    52,    62,    81,    80,    99,   107,   140,     5,
   36,    55,    63,    82,    81,   100,    98,   131,   185,   252,
    5,    35,    54,    64,    83,    82,   101,    97,   130,   186,
  253,     5,     9,     9,    65,    84,    83,   102,    96,   129,
  175,   242,     5,     8,     8,    66,    85,    84,   103,    95,
  128,   176,   243,     2,    67,    86,   102,   135,     3,    68,
   87,   101,   134,   174,   241,     4,    93,   122,   100,   133,
  135,   171,   179,   246,     4,    94,   123,    99,   132,   134,
  170,   180,   247,     3,   120,   155,   133,   169,   177,   244,
    3,   119,   154,   132,   168,   178,   245,     4,     1,     1,
  118,   153,   139,   175,   156,   202,     4,     0,     0,   117,
  152,   138,   174,   157,   203,     4,     3,     3,    88,   112,
  124,   159,   137,   173,     5,     2,     2,    89,   113,   123,
  158,   136,   172,   155,   201,     5,     5,     5,    90,   114,
  122,   157,   128,   163,   160,   206,     5,     4,     4,    91,
  115,   121,   156,   127,   162,   161,   207,
};

vtkDICOMDictionary::Dict Dict251Data = {
"SIEMENS SYNGO ADVANCED PRESENTATION",
46,
187,
Dict251TagHashTable,
Dict251Contents
};

// ----- MITRA PRESENTATION 1.0 -----

DictEntry Dict252Contents[] = {
{ 0x0029, 0x0000, 0, VR::CS, VM::M1, "Rotation" },
{ 0x0029, 0x0001, 0, VR::LO, VM::M1, "WindowWidth" },
{ 0x0029, 0x0002, 0, VR::LO, VM::M1, "WindowCentre" },
{ 0x0029, 0x0003, 0, VR::IS, VM::M1, "Invert" },
{ 0x0029, 0x0004, 0, VR::IS, VM::M1, "HasTabstop" },
{ 0x0029, 0x0005, 0, VR::CS, VM::M1, "SmoothRotation" },
{ 0x0029, 0x0010, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0011, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0012, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0013, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict252TagHashTable[] = {
    3,    14,     0,     5,     1,     1,     3,     3,     5,     5,
    7,    17,     9,    19,     5,     0,     0,     2,     2,     4,
    4,     6,    16,     8,    18,
};

vtkDICOMDictionary::Dict Dict252Data = {
"MITRA PRESENTATION 1.0",
2,
10,
Dict252TagHashTable,
Dict252Contents
};

// ----- CAMTRONICS IP -----

DictEntry Dict253Contents[] = {
{ 0x0029, 0x0010, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0030, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0040, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict253TagHashTable[] = {
    2,     0,     4,     0,    16,     1,    32,     2,    48,     3,
   64,
};

vtkDICOMDictionary::Dict Dict253Data = {
"CAMTRONICS IP",
1,
4,
Dict253TagHashTable,
Dict253Contents
};

// ----- GEMS_VXTL_USERDATA_01 -----

DictEntry Dict254Contents[] = {
{ 0x0047, 0x0011, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict254TagHashTable[] = {
    2,     0,     1,     0,    17,
};

vtkDICOMDictionary::Dict Dict254Data = {
"GEMS_VXTL_USERDATA_01",
1,
1,
Dict254TagHashTable,
Dict254Contents
};

// ----- MITRA OBJECT DOCUMENT 1.0 -----

DictEntry Dict255Contents[] = {
{ 0x0029, 0x0000, 0, VR::OB, VM::M1, "IMPAXObjectDocument" },
{ 0x0029, 0x0001, 0, VR::OB, VM::M1, "IMPAXMarkupXMLStored" },
};

unsigned short Dict255TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict255Data = {
"MITRA OBJECT DOCUMENT 1.0",
1,
2,
Dict255TagHashTable,
Dict255Contents
};

// ----- SIEMENS MED SMS USG ANTARES -----

DictEntry Dict256Contents[] = {
{ 0x0019, 0x0000, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x000c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x000d, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x000e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0021, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0022, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0023, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0024, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0025, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0027, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0029, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002d, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002e, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0031, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003b, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0041, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0042, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0043, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0046, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0047, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0048, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0049, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0054, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0061, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0062, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0063, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0065, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0066, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0067, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0069, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x006a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x006c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0072, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0081, 0, VR::FD, VM::M1, "" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0083, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0086, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0087, 0, VR::SH, VM::M1, "" },
{ 0x0019, 0x0088, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0095, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a0, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict256TagHashTable[] = {
   13,    22,    33,    40,    49,    58,    65,    72,    81,    94,
  103,   116,     0,     4,    10,    37,    14,    41,    31,    96,
   47,   135,     5,     0,     0,     9,    36,    13,    40,    32,
   97,    46,   134,     3,     1,     3,    12,    39,    33,    98,
    4,    11,    38,    15,    42,    34,    99,    48,   136,     4,
   16,    45,    18,    49,    21,    64,    30,    84,     3,    22,
   65,    35,   101,    38,   105,     3,    23,    66,    36,   102,
   39,   106,     4,    17,    46,    24,    67,    37,   103,    50,
  160,     6,     3,    13,     6,    33,    25,    68,    28,    72,
   40,   108,    45,   131,     4,     2,    12,     5,    32,    29,
   73,    44,   130,     6,     8,    35,    20,    59,    26,    70,
   41,   114,    43,   129,    49,   149,     5,     4,    14,     7,
   34,    19,    58,    27,    71,    42,   128,
};

vtkDICOMDictionary::Dict Dict256Data = {
"SIEMENS MED SMS USG ANTARES",
12,
51,
Dict256TagHashTable,
Dict256Contents
};

// ----- PI Private Block (0781:3000 - 0781:30FF) -----

DictEntry Dict257Contents[] = {
{ 0x0781, 0x0001, 0, VR::US, VM::M1, "" },
{ 0x0781, 0x0002, 0, VR::US, VM::M1, "" },
{ 0x0781, 0x0005, 0, VR::FL, VM::M1, "" },
{ 0x0781, 0x0009, 0, VR::FL, VM::M4, "" },
};

unsigned short Dict257TagHashTable[] = {
    2,     0,     4,     0,     1,     1,     2,     2,     5,     3,
    9,
};

vtkDICOMDictionary::Dict Dict257Data = {
"PI Private Block (0781:3000 - 0781:30FF)",
1,
4,
Dict257TagHashTable,
Dict257Contents
};

// ----- SIEMENS MED MAMMO -----

DictEntry Dict258Contents[] = {
{ 0x0029, 0x005a, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict258TagHashTable[] = {
    2,     0,     1,     0,    90,
};

vtkDICOMDictionary::Dict Dict258Data = {
"SIEMENS MED MAMMO",
1,
1,
Dict258TagHashTable,
Dict258Contents
};

// ----- PM -----

DictEntry Dict259Contents[] = {
{ 0x0101, 0x0005, 0, VR::LO, VM::M1TN, "ImageEnhancementParameterFile" },
{ 0x0101, 0x0006, 0, VR::IS, VM::M1, "OriginalSigmoidRatio" },
};

unsigned short Dict259TagHashTable[] = {
    2,     0,     2,     0,     5,     1,     6,
};

vtkDICOMDictionary::Dict Dict259Data = {
"PM",
1,
2,
Dict259TagHashTable,
Dict259Contents
};

// ----- MITRA MARKUP 1.0 -----

DictEntry Dict260Contents[] = {
{ 0x0029, 0x0000, 0, VR::OB, VM::M1TN, "Markup1" },
{ 0x0029, 0x0001, 0, VR::OB, VM::M1TN, "Markup2" },
{ 0x0029, 0x0002, 0, VR::OB, VM::M1TN, "Markup3" },
{ 0x0029, 0x0003, 0, VR::OB, VM::M1TN, "Markup4" },
{ 0x0029, 0x0004, 0, VR::OB, VM::M1TN, "Markup5" },
{ 0x0029, 0x0005, 0, VR::OB, VM::M1TN, "Markup6" },
{ 0x0029, 0x0006, 0, VR::OB, VM::M1TN, "Markup7" },
{ 0x0029, 0x0007, 0, VR::OB, VM::M1TN, "Markup8" },
{ 0x0029, 0x0008, 0, VR::OB, VM::M1TN, "Markup9" },
{ 0x0029, 0x0009, 0, VR::OB, VM::M1TN, "Markup10" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1TN, "Markup11" },
{ 0x0029, 0x0011, 0, VR::OB, VM::M1TN, "Markup12" },
{ 0x0029, 0x0012, 0, VR::OB, VM::M1TN, "Markup13" },
{ 0x0029, 0x0013, 0, VR::OB, VM::M1TN, "Markup14" },
{ 0x0029, 0x0014, 0, VR::OB, VM::M1TN, "Markup15" },
};

unsigned short Dict260TagHashTable[] = {
    4,    13,    24,     0,     4,     3,     3,     4,     4,     8,
    8,    10,    16,     5,     1,     1,     2,     2,     7,     7,
   13,    19,    14,    20,     6,     0,     0,     5,     5,     6,
    6,     9,     9,    11,    17,    12,    18,
};

vtkDICOMDictionary::Dict Dict260Data = {
"MITRA MARKUP 1.0",
3,
15,
Dict260TagHashTable,
Dict260Contents
};

// ----- SIEMENS_FLCOMPACT_VA01A_PROC -----

DictEntry Dict261Contents[] = {
{ 0x0017, 0x000a, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x000b, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x000c, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x000d, 0, VR::FL, VM::M1, "" },
{ 0x0017, 0x000e, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x000f, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x0010, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0011, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0014, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0016, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0017, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0018, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0019, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x001a, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x001b, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x001c, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x001e, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x001f, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0020, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0021, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0022, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0023, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0024, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0025, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0026, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0027, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0028, 0, VR::FL, VM::M1, "" },
{ 0x0017, 0x0029, 0, VR::FL, VM::M1, "" },
{ 0x0017, 0x0048, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0049, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x004d, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x004e, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x004f, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x0050, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0051, 0, VR::FL, VM::M1, "" },
{ 0x0017, 0x0052, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0053, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0054, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x0055, 0, VR::SS, VM::M1, "" },
{ 0x0017, 0x005c, 0, VR::OW, VM::M1, "" },
{ 0x0017, 0x0064, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0066, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0067, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0068, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0085, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0086, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0087, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0088, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0089, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x008a, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x008b, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x008c, 0, VR::FL, VM::M1, "" },
{ 0x0017, 0x008d, 0, VR::FL, VM::M1, "" },
{ 0x0017, 0x008e, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x008f, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00a0, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00a1, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00a2, 0, VR::LO, VM::M1, "" },
{ 0x0017, 0x00a3, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00a4, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00a5, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00a6, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00aa, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x00b0, 0, VR::DS, VM::M1, "" },
{ 0x0017, 0x00c0, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict261TagHashTable[] = {
   17,    28,    37,    46,    57,    66,    75,    84,    93,   102,
  111,   118,   127,   134,   141,   152,     0,     5,    10,    23,
   25,    39,    41,   102,    44,   133,    60,   165,     4,     9,
   22,    24,    38,    42,   103,    59,   164,     4,    23,    37,
   37,    84,    40,   100,    46,   135,     5,     8,    20,    22,
   36,    38,    85,    45,   134,    61,   166,     4,    21,    35,
   35,    82,    56,   161,    64,   192,     4,    20,    34,    36,
   83,    55,   160,    63,   176,     4,     7,    17,    19,    33,
   33,    80,    58,   163,     4,     6,    16,    18,    32,    34,
   81,    57,   162,     4,     5,    15,    17,    31,    31,    78,
   52,   141,     4,     4,    14,    16,    30,    32,    79,    51,
  140,     3,     3,    13,    39,    92,    54,   143,     4,     2,
   12,    15,    28,    30,    77,    53,   142,     3,     1,    11,
   14,    27,    48,   137,     3,     0,    10,    13,    26,    47,
  136,     5,    12,    25,    27,    41,    28,    72,    43,   104,
   50,   139,     5,    11,    24,    26,    40,    29,    73,    49,
  138,    62,   170,
};

vtkDICOMDictionary::Dict Dict261Data = {
"SIEMENS_FLCOMPACT_VA01A_PROC",
16,
65,
Dict261TagHashTable,
Dict261Contents
};

// ----- Applicare/RadStore/Version 1.0 -----

DictEntry Dict262Contents[] = {
{ 0x3113, 0x0001, 0, VR::SL, VM::M1, "" },
{ 0x3113, 0x0002, 0, VR::SL, VM::M1, "Id1" },
{ 0x3113, 0x0003, 0, VR::SL, VM::M1, "Id2" },
{ 0x3113, 0x0004, 0, VR::SL, VM::M1, "Id3" },
{ 0x3113, 0x0011, 0, VR::LO, VM::M1, "" },
{ 0x3113, 0x0012, 0, VR::CS, VM::M1, "State" },
{ 0x3113, 0x0013, 0, VR::DT, VM::M1, "DateLastModified" },
{ 0x3113, 0x0014, 0, VR::DT, VM::M1, "DateLastAccessed" },
{ 0x3113, 0x0015, 0, VR::CS, VM::M1, "" },
{ 0x3113, 0x0016, 0, VR::FD, VM::M1, "ByteSize" },
{ 0x3113, 0x0017, 0, VR::LO, VM::M1, "LibraryId" },
{ 0x3113, 0x0018, 0, VR::LO, VM::M1, "Pathnames" },
{ 0x3113, 0x0019, 0, VR::LO, VM::M1, "DriverPath" },
{ 0x3113, 0x001A, 0, VR::LO, VM::M1, "Source" },
{ 0x3113, 0x001B, 0, VR::LO, VM::M1, "Destination" },
{ 0x3113, 0x001C, 0, VR::SL, VM::M1, "MediumId" },
{ 0x3113, 0x001D, 0, VR::LO, VM::M1, "ArchiveId" },
{ 0x3113, 0x001E, 0, VR::LO, VM::M1, "Origin" },
{ 0x3113, 0x0021, 0, VR::SL, VM::M1, "Version" },
{ 0x3113, 0x0022, 0, VR::SL, VM::M1, "" },
{ 0x3113, 0x0023, 0, VR::ST, VM::M1, "InstanceFileLocation" },
{ 0x3113, 0x0031, 0, VR::IS, VM::M1, "" },
{ 0x3113, 0x0032, 0, VR::IS, VM::M1, "" },
{ 0x3113, 0x0033, 0, VR::IS, VM::M1, "" },
{ 0x3113, 0x0035, 0, VR::LO, VM::M1, "ImageMediumLocation" },
{ 0x3113, 0x0036, 0, VR::LO, VM::M1, "ImageMediumLabel" },
{ 0x3113, 0x0037, 0, VR::CS, VM::M1, "ImageMediumState" },
{ 0x3113, 0x0038, 0, VR::LO, VM::M1, "SeriesMediumLocation" },
{ 0x3113, 0x0039, 0, VR::LO, VM::M1, "SeriesMediumLabel" },
{ 0x3113, 0x003A, 0, VR::CS, VM::M1, "SeriesMediumState" },
{ 0x3113, 0x003B, 0, VR::LO, VM::M1, "StudyMediumLocation" },
{ 0x3113, 0x003C, 0, VR::LO, VM::M1, "StudyMediumLabel" },
{ 0x3113, 0x003D, 0, VR::CS, VM::M1, "StudyMediumState" },
{ 0x3113, 0x0052, 0, VR::CS, VM::M1, "StudyState" },
{ 0x3113, 0x0053, 0, VR::CS, VM::M1, "SeriesState" },
{ 0x3113, 0x0055, 0, VR::CS, VM::M1, "ImageStateText" },
{ 0x3113, 0x0056, 0, VR::CS, VM::M1, "SeriesStateText" },
{ 0x3113, 0x0057, 0, VR::CS, VM::M1, "StudyStateText" },
{ 0x3113, 0x0060, 0, VR::DT, VM::M1, "Expiration" },
{ 0x3113, 0x0069, 0, VR::AT, VM::M1TN, "DeletedTags" },
};

unsigned short Dict262TagHashTable[] = {
   11,    22,    29,    38,    45,    48,    57,    68,    77,    90,
    0,     5,     6,    19,    12,    25,    18,    33,    24,    53,
   30,    59,     3,     5,    18,    11,    24,    29,    58,     4,
    4,    17,    23,    51,    28,    57,    36,    86,     3,    22,
   50,    27,    56,    37,    87,     1,    21,    49,     4,     3,
    4,    17,    30,    35,    85,    39,   105,     5,     2,     3,
   10,    23,    16,    29,    33,    82,    38,    96,     4,     1,
    2,     9,    22,    15,    28,    34,    83,     6,     0,     1,
    8,    21,    14,    27,    20,    35,    26,    55,    32,    61,
    5,     7,    20,    13,    26,    19,    34,    25,    54,    31,
   60,
};

vtkDICOMDictionary::Dict Dict262Data = {
"Applicare/RadStore/Version 1.0",
10,
40,
Dict262TagHashTable,
Dict262Contents
};

// ----- Siemens: Thorax/Multix FD Post Processing -----

DictEntry Dict263Contents[] = {
{ 0x0021, 0x0000, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0001, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::FL, VM::M1, "" },
{ 0x0021, 0x0003, 0, VR::FL, VM::M1, "" },
{ 0x0021, 0x0004, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0005, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0006, 0, VR::FL, VM::M1, "" },
{ 0x0021, 0x0007, 0, VR::FL, VM::M1, "" },
{ 0x0021, 0x0008, 0, VR::US, VM::M1, "AutoWindowFlag" },
{ 0x0021, 0x0009, 0, VR::SL, VM::M1, "AutoWindowCenter" },
{ 0x0021, 0x000a, 0, VR::SL, VM::M1, "AutoWindowWidth" },
{ 0x0021, 0x000b, 0, VR::SS, VM::M1, "FilterID" },
{ 0x0021, 0x000c, 0, VR::FL, VM::M1, "" },
{ 0x0021, 0x000d, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x000e, 0, VR::US, VM::M1, "DoseControlValue" },
{ 0x0021, 0x000f, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0010, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0011, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0012, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0013, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0014, 0, VR::US, VM::M1, "AnatomicCorrectView" },
{ 0x0021, 0x0015, 0, VR::SS, VM::M1, "AutoWindowShift" },
{ 0x0021, 0x0016, 0, VR::DS, VM::M1, "AutoWindowExpansion" },
{ 0x0021, 0x0017, 0, VR::LO, VM::M1, "SystemType" },
{ 0x0021, 0x0018, 0, VR::LO, VM::M1, "DetectorType" },
{ 0x0021, 0x0030, 0, VR::US, VM::M1, "AnatomicSortNumber" },
{ 0x0021, 0x0031, 0, VR::US, VM::M1, "AcquisitionSortNumber" },
};

unsigned short Dict263TagHashTable[] = {
    7,    16,    25,    34,    45,    56,     0,     4,     5,     5,
   11,    11,    17,    17,    23,    23,     4,     4,     4,    10,
   10,    16,    16,    22,    22,     4,     1,     1,     7,     7,
   13,    13,    19,    19,     5,     0,     0,     6,     6,    12,
   12,    18,    18,    24,    24,     5,     3,     3,     9,     9,
   15,    15,    21,    21,    26,    49,     5,     2,     2,     8,
    8,    14,    14,    20,    20,    25,    48,
};

vtkDICOMDictionary::Dict Dict263Data = {
"Siemens: Thorax/Multix FD Post Processing",
6,
27,
Dict263TagHashTable,
Dict263Contents
};

// ----- Applicare/RadWorks/Version 5.0 -----

DictEntry Dict264Contents[] = {
{ 0x3109, 0x0001, 0, VR::ST, VM::M1, "WorklistFilename" },
{ 0x3109, 0x0002, 0, VR::SH, VM::M1, "NewSeenStatus" },
{ 0x3109, 0x0003, 0, VR::CS, VM::M1, "DeleteLock" },
{ 0x3109, 0x0004, 0, VR::CS, VM::M1, "" },
{ 0x3109, 0x0005, 0, VR::CS, VM::M1, "" },
{ 0x3109, 0x0006, 0, VR::CS, VM::M1, "" },
{ 0x3109, 0x0007, 0, VR::UL, VM::M1, "" },
{ 0x3109, 0x0008, 0, VR::LO, VM::M1, "ReceiveOrigin" },
{ 0x3109, 0x0009, 0, VR::LO, VM::M1, "Folder" },
{ 0x3109, 0x000A, 0, VR::DA, VM::M1, "ReceiveDate" },
{ 0x3109, 0x000B, 0, VR::TM, VM::M1, "ReceiveTime" },
{ 0x3109, 0x000C, 0, VR::CS, VM::M1, "Prior" },
{ 0x3109, 0x000D, 0, VR::CS, VM::M1, "StatStudy" },
{ 0x3109, 0x000E, 0, VR::CS, VM::M1, "Key" },
{ 0x3109, 0x0010, 0, VR::CS, VM::M1, "LocalStudy" },
{ 0x3109, 0x0011, 0, VR::LO, VM::M1, "ResultMessage" },
{ 0x3109, 0x0012, 0, VR::LO, VM::M1, "CurrentUser" },
{ 0x3109, 0x0013, 0, VR::DA, VM::M1, "SystemDate" },
{ 0x3109, 0x0014, 0, VR::TM, VM::M1, "SystemTime" },
{ 0x3109, 0x0019, 0, VR::LO, VM::M1, "WorklistName" },
{ 0x3109, 0x0020, 0, VR::UI, VM::M1, "WorklistUID" },
{ 0x3109, 0x0021, 0, VR::CS, VM::M1, "Hostname" },
{ 0x3109, 0x0022, 0, VR::AE, VM::M1, "DICOMAETitle" },
{ 0x3109, 0x0023, 0, VR::US, VM::M1, "DICOMPortNumber" },
{ 0x3109, 0x0024, 0, VR::LO, VM::M1, "DestinationName" },
{ 0x3109, 0x0025, 0, VR::LO, VM::M1, "OriginName" },
{ 0x3109, 0x0026, 0, VR::UI, VM::M1, "ModalityStudyInstanceUID" },
{ 0x3109, 0x0027, 0, VR::SQ, VM::M1, "ExamRouting" },
{ 0x3109, 0x0028, 0, VR::LO, VM::M1, "NotificationComments" },
{ 0x3109, 0x0029, 0, VR::LO, VM::M1, "TransactionComments" },
{ 0x3109, 0x002A, 0, VR::LO, VM::M1, "SendFlag" },
{ 0x3109, 0x002B, 0, VR::LO, VM::M1, "PrintFlag" },
{ 0x3109, 0x002C, 0, VR::LO, VM::M1, "ArchiveFlag" },
{ 0x3109, 0x0030, 0, VR::LO, VM::M1, "RequestingFacilityName" },
{ 0x3109, 0x0031, 0, VR::CS, VM::M1, "RequestingProcedureName" },
{ 0x3109, 0x0032, 0, VR::CS, VM::M1, "RequestingProcedureCode" },
{ 0x3109, 0x0033, 0, VR::CS, VM::M1, "RequestStorage ommitment" },
{ 0x3109, 0x0034, 0, VR::CS, VM::M1, "RequestedCompression" },
{ 0x3109, 0x0035, 0, VR::SQ, VM::M1, "StudySequence" },
{ 0x3109, 0x0037, 0, VR::UI, VM::M1, "ReplacedStudyUID" },
{ 0x3109, 0x0038, 0, VR::SH, VM::M1, "TeachingACRCode" },
{ 0x3109, 0x0039, 0, VR::SH, VM::M1, "TeachingSpecialInterestCode" },
{ 0x3109, 0x0040, 0, VR::IS, VM::M1, "NumberOfStudyRelatedImages" },
{ 0x3109, 0x0041, 0, VR::CS, VM::M1, "StudyLocked" },
{ 0x3109, 0x0042, 0, VR::CS, VM::M1, "WorkstationName" },
{ 0x3109, 0x0043, 0, VR::CS, VM::M1, "ArchiveStatus" },
{ 0x3109, 0x00EE, 0, VR::UI, VM::M1, "InternalListUID" },
{ 0x3109, 0x00EF, 0, VR::CS, VM::M1, "Action" },
};

unsigned short Dict264TagHashTable[] = {
   13,    26,    39,    48,    55,    64,    73,    80,    89,    98,
  107,   114,     0,     6,     4,     5,    19,    25,    21,    33,
   38,    53,    42,    64,    46,   238,     6,     3,     4,    20,
   32,    32,    44,    37,    52,    43,    65,    47,   239,     4,
    6,     7,    23,    35,    39,    55,    44,    66,     3,     5,
    6,    22,    34,    45,    67,     4,     0,     1,    12,    13,
   29,    41,    34,    49,     4,    11,    12,    18,    20,    28,
   40,    33,    48,     3,     2,     3,    31,    43,    36,    51,
    4,     1,     2,    13,    14,    30,    42,    35,    50,     4,
    8,     9,    15,    17,    25,    37,    41,    57,     4,     7,
    8,    14,    16,    24,    36,    40,    56,     3,    10,    11,
   17,    19,    27,    39,     3,     9,    10,    16,    18,    26,
   38,
};

vtkDICOMDictionary::Dict Dict264Data = {
"Applicare/RadWorks/Version 5.0",
12,
48,
Dict264TagHashTable,
Dict264Contents
};

// ----- Voxar 2.16.124.113543.6003.1999.12.20.12.5.0 -----

DictEntry Dict265Contents[] = {
{ 0x1135, 0x0000, 0, VR::UI, VM::M1, "" },
{ 0x1135, 0x0001, 0, VR::OB, VM::M1, "" },
{ 0x1135, 0x0002, 0, VR::SQ, VM::M1, "" },
{ 0x1135, 0x0006, 0, VR::UL, VM::M1, "" },
{ 0x1135, 0x0007, 0, VR::UI, VM::M1, "" },
{ 0x1135, 0x0008, 0, VR::SQ, VM::M1, "" },
{ 0x1135, 0x0009, 0, VR::UI, VM::M1, "" },
{ 0x1135, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x1135, 0x0013, 0, VR::LO, VM::M1, "" },
{ 0x1135, 0x0014, 0, VR::UN, VM::M1, "" },
{ 0x1135, 0x0016, 0, VR::LO, VM::M1, "" },
{ 0x1135, 0x0017, 0, VR::UN, VM::M1, "" },
{ 0x1135, 0x0018, 0, VR::UN, VM::M1, "" },
{ 0x1135, 0x0021, 0, VR::UL, VM::M1, "" },
};

unsigned short Dict265TagHashTable[] = {
    4,    17,    28,     0,     6,     1,     1,     2,     2,     4,
    7,     5,     8,     7,    16,    10,    22,     5,     0,     0,
    3,     6,     8,    19,     9,    20,    13,    33,     3,     6,
    9,    11,    23,    12,    24,
};

vtkDICOMDictionary::Dict Dict265Data = {
"Voxar 2.16.124.113543.6003.1999.12.20.12.5.0",
3,
14,
Dict265TagHashTable,
Dict265Contents
};

// ----- astm.org/diconde/iod/NDEGeometry -----

DictEntry Dict266Contents[] = {
{ 0x0021, 0x0002, 0, VR::IS, VM::M1, "CoordinateSystemNumberOfAxes" },
{ 0x0021, 0x0004, 0, VR::SQ, VM::M1, "CoordinateSystemAxesSequence" },
{ 0x0021, 0x0006, 0, VR::ST, VM::M1, "CoordinateSystemAxisDescription" },
{ 0x0021, 0x0008, 0, VR::CS, VM::M1, "CoordinateSystemDataSetMapping" },
{ 0x0021, 0x000A, 0, VR::IS, VM::M1, "CoordinateSystemAxisNumber" },
{ 0x0021, 0x000C, 0, VR::CS, VM::M1, "CoordinateSystemAxisType" },
{ 0x0021, 0x000E, 0, VR::CS, VM::M1, "CoordinateSystemAxisUnits" },
{ 0x0021, 0x0010, 0, VR::OB, VM::M1, "CoordinateSystemAxisValues" },
{ 0x0021, 0x0020, 0, VR::SQ, VM::M1, "CoordinateSystemTransformSequence" },
{ 0x0021, 0x0022, 0, VR::ST, VM::M1, "TransformDescription" },
{ 0x0021, 0x0024, 0, VR::IS, VM::M1, "TransformNumberOfAxes" },
{ 0x0021, 0x0026, 0, VR::IS, VM::M1TN, "TransformOrderOfAxes" },
{ 0x0021, 0x0028, 0, VR::CS, VM::M1, "TransformedAxisUnits" },
{ 0x0021, 0x002A, 0, VR::DS, VM::M1TN, "CoordinateSystemTransformRotationAndScaleMatrix" },
{ 0x0021, 0x002C, 0, VR::DS, VM::M1TN, "CoordinateSystemTransformTranslationMatrix" },
};

unsigned short Dict266TagHashTable[] = {
    4,    13,    26,     0,     4,     2,     6,     5,    12,     9,
   34,    12,    40,     6,     1,     4,     4,    10,     7,    16,
    8,    32,    11,    38,    14,    44,     5,     0,     2,     3,
    8,     6,    14,    10,    36,    13,    42,
};

vtkDICOMDictionary::Dict Dict266Data = {
"astm.org/diconde/iod/NDEGeometry",
3,
15,
Dict266TagHashTable,
Dict266Contents
};

// ----- GEMS_CT_VES_01 -----

DictEntry Dict267Contents[] = {
{ 0x0051, 0x1001, 0, VR::SQ, VM::M1, "CTVESSequence" },
};

unsigned short Dict267TagHashTable[] = {
    2,     0,     1,     0,  4097,
};

vtkDICOMDictionary::Dict Dict267Data = {
"GEMS_CT_VES_01",
1,
1,
Dict267TagHashTable,
Dict267Contents
};

// ----- AMI Sequence Annotations_01 -----

DictEntry Dict268Contents[] = {
{ 0x3103, 0x0010, 0, VR::CS, VM::M1, "AnnotationSequence" },
{ 0x3103, 0x0020, 0, VR::UI, VM::M1, "AnnotationUID" },
{ 0x3103, 0x0030, 0, VR::US, VM::M1, "AnnotationColor" },
{ 0x3103, 0x0050, 0, VR::CS, VM::M1, "AnnotationLineStyle" },
{ 0x3103, 0x0060, 0, VR::SQ, VM::M1, "AnnotationElements" },
{ 0x3103, 0x0070, 0, VR::SH, VM::M1, "AnnotationLabel" },
{ 0x3103, 0x0080, 0, VR::PN, VM::M1, "AnnotationCreator" },
{ 0x3103, 0x0090, 0, VR::PN, VM::M1, "AnnotationModifiers" },
{ 0x3103, 0x00A0, 0, VR::DA, VM::M1, "AnnotationCreationDate" },
{ 0x3103, 0x00B0, 0, VR::TM, VM::M1, "AnnotationCreationTime" },
{ 0x3103, 0x00C0, 0, VR::DA, VM::M1, "AnnotationModificationDates" },
{ 0x3103, 0x00D0, 0, VR::TM, VM::M1, "AnnotationMofificationTimes" },
{ 0x3103, 0x00E0, 0, VR::US, VM::M1, "AnnotationFrameNumber" },
};

unsigned short Dict268TagHashTable[] = {
    4,    13,    24,     0,     4,     0,    16,     5,   112,     8,
  160,    11,   208,     5,     1,    32,     3,    80,     6,   128,
    9,   176,    12,   224,     4,     2,    48,     4,    96,     7,
  144,    10,   192,
};

vtkDICOMDictionary::Dict Dict268Data = {
"AMI Sequence Annotations_01",
3,
13,
Dict268TagHashTable,
Dict268Contents
};

// ----- AMI Sequence Annotations_02 -----

DictEntry Dict269Contents[] = {
{ 0x3103, 0x0010, 0, VR::CS, VM::M1, "AnnotationSequence" },
{ 0x3103, 0x0020, 0, VR::UI, VM::M1, "AnnotationUID" },
{ 0x3103, 0x0030, 0, VR::US, VM::M1, "AnnotationColor" },
{ 0x3103, 0x0050, 0, VR::CS, VM::M1, "AnnotationLineStyle" },
{ 0x3103, 0x0060, 0, VR::SQ, VM::M1, "AnnotationElements" },
{ 0x3103, 0x0070, 0, VR::SH, VM::M1, "AnnotationLabel" },
{ 0x3103, 0x0080, 0, VR::PN, VM::M1, "AnnotationCreator" },
{ 0x3103, 0x0090, 0, VR::PN, VM::M1, "AnnotationModifiers" },
{ 0x3103, 0x00A0, 0, VR::DA, VM::M1, "AnnotationCreationDate" },
{ 0x3103, 0x00B0, 0, VR::TM, VM::M1, "AnnotationCreationTime" },
{ 0x3103, 0x00C0, 0, VR::DA, VM::M1, "AnnotationModificationDates" },
{ 0x3103, 0x00D0, 0, VR::TM, VM::M1, "AnnotationModificationTimes" },
{ 0x3103, 0x00E0, 0, VR::US, VM::M1, "AnnotationFrame Number" },
};

unsigned short Dict269TagHashTable[] = {
    4,    13,    24,     0,     4,     0,    16,     5,   112,     8,
  160,    11,   208,     5,     1,    32,     3,    80,     6,   128,
    9,   176,    12,   224,     4,     2,    48,     4,    96,     7,
  144,    10,   192,
};

vtkDICOMDictionary::Dict Dict269Data = {
"AMI Sequence Annotations_02",
3,
13,
Dict269TagHashTable,
Dict269Contents
};

// ----- GE LUT Asymmetry Parameter -----

DictEntry Dict270Contents[] = {
{ 0x0045, 0x0067, 0, VR::DS, VM::M1, "LUTAssymetry" },
};

unsigned short Dict270TagHashTable[] = {
    2,     0,     1,     0,   103,
};

vtkDICOMDictionary::Dict Dict270Data = {
"GE LUT Asymmetry Parameter",
1,
1,
Dict270TagHashTable,
Dict270Contents
};

// ----- ACUSON:1.2.840.113680.1.0:0910 -----

DictEntry Dict271Contents[] = {
{ 0x0009, 0x0002, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0004, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict271TagHashTable[] = {
    2,     0,     3,     0,     2,     1,     3,     2,     4,
};

vtkDICOMDictionary::Dict Dict271Data = {
"ACUSON:1.2.840.113680.1.0:0910",
1,
3,
Dict271TagHashTable,
Dict271Contents
};

// ----- MATAKINA_10 -----

DictEntry Dict272Contents[] = {
{ 0x0015, 0x0028, 0, VR::LO, VM::M1, "VolparaDensityGrade" },
{ 0x0015, 0x0029, 0, VR::LT, VM::M1, "VolparaRunInformation" },
{ 0x0015, 0x0030, 0, VR::LO, VM::M1, "VolparaDensityGradeCutoffs" },
};

unsigned short Dict272TagHashTable[] = {
    2,     0,     3,     0,    40,     1,    41,     2,    48,
};

vtkDICOMDictionary::Dict Dict272Data = {
"MATAKINA_10",
1,
3,
Dict272TagHashTable,
Dict272Contents
};

// ----- SIEMENS CT VA0  OST -----

DictEntry Dict273Contents[] = {
{ 0x6021, 0x0000, 0, VR::LO, VM::M1, "OsteoContourComment" },
{ 0x6021, 0x0010, 0, VR::US, VM::M256, "OsteoContourBuffer" },
};

unsigned short Dict273TagHashTable[] = {
    2,     0,     2,     0,     0,     1,    16,
};

vtkDICOMDictionary::Dict Dict273Data = {
"SIEMENS CT VA0  OST",
1,
2,
Dict273TagHashTable,
Dict273Contents
};

// ----- SIEMENS MED DISPLAY 0000 -----

DictEntry Dict274Contents[] = {
{ 0x0029, 0x0099, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x00b0, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x00b2, 0, VR::US, VM::M1TN, "" },
{ 0x0029, 0x00c1, 0, VR::US, VM::M1TN, "" },
};

unsigned short Dict274TagHashTable[] = {
    2,     0,     4,     0,   153,     1,   176,     2,   178,     3,
  193,
};

vtkDICOMDictionary::Dict Dict274Data = {
"SIEMENS MED DISPLAY 0000",
1,
4,
Dict274TagHashTable,
Dict274Contents
};

// ----- SIEMENS MED DISPLAY 0001 -----

DictEntry Dict275Contents[] = {
{ 0x0029, 0x0099, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x00a0, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x00a1, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x00a2, 0, VR::US, VM::M1TN, "" },
};

unsigned short Dict275TagHashTable[] = {
    2,     0,     4,     0,   153,     1,   160,     2,   161,     3,
  162,
};

vtkDICOMDictionary::Dict Dict275Data = {
"SIEMENS MED DISPLAY 0001",
1,
4,
Dict275TagHashTable,
Dict275Contents
};

// ----- Picker NM Private Group -----

DictEntry Dict276Contents[] = {
{ 0x7001, 0x0001, 0, VR::UI, VM::M1, "" },
{ 0x7001, 0x0002, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0003, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0004, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0005, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0006, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0007, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0008, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0009, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x7001, 0x0011, 0, VR::LO, VM::M1, "" },
{ 0x7001, 0x0012, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0013, 0, VR::US, VM::M1, "" },
{ 0x7001, 0x0014, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0016, 0, VR::OB, VM::M1, "" },
{ 0x7001, 0x0017, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict276TagHashTable[] = {
    5,    14,    23,    32,     0,     4,     0,     1,     4,     5,
    8,     9,    10,    17,     4,     3,     4,     7,     8,     9,
   16,    13,    20,     4,     2,     3,     6,     7,    12,    19,
   15,    23,     4,     1,     2,     5,     6,    11,    18,    14,
   22,
};

vtkDICOMDictionary::Dict Dict276Data = {
"Picker NM Private Group",
4,
16,
Dict276TagHashTable,
Dict276Contents
};

// ----- PHILIPS MR SPECTRO;1 -----

DictEntry Dict277Contents[] = {
{ 0x0019, 0x0001, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0004, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0007, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0008, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0009, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0012, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0013, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0014, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0015, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0016, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0017, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0018, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0021, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0022, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0023, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0024, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0025, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0027, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0028, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0029, 0, VR::IS, VM::M1TN, "" },
{ 0x0019, 0x0031, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0041, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0042, 0, VR::IS, VM::M2, "" },
{ 0x0019, 0x0043, 0, VR::IS, VM::M2, "" },
{ 0x0019, 0x0045, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0046, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0047, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0048, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0049, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0061, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0070, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0071, 0, VR::IS, VM::M1TN, "" },
{ 0x0019, 0x0072, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0073, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0074, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0076, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0077, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0079, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict277TagHashTable[] = {
   13,    30,    43,    52,    61,    68,    75,    80,    87,    94,
  105,   114,     0,     8,     0,     1,    13,    21,    22,    37,
   26,    41,    37,    80,    38,    96,    44,   116,    47,   120,
    6,    12,    20,    16,    24,    21,    36,    25,    40,    39,
   97,    48,   121,     4,     2,     3,    15,    23,    24,    39,
   45,   118,     4,     1,     2,    14,    22,    23,    38,    46,
  119,     3,     4,     5,     8,     9,    27,    49,     3,     3,
    4,     7,     8,    29,    65,     2,     6,     7,    30,    66,
    3,     5,     6,    28,    50,    31,    67,     3,    18,    33,
   35,    72,    40,   112,     5,     9,    16,    17,    32,    32,
   69,    36,    73,    41,   113,     4,    11,    19,    20,    35,
   33,    70,    42,   114,     5,    10,    18,    19,    34,    34,
   71,    43,   115,    49,   128,
};

vtkDICOMDictionary::Dict Dict277Data = {
"PHILIPS MR SPECTRO;1",
12,
50,
Dict277TagHashTable,
Dict277Contents
};

// ----- astm.org/diconde/iod/NdeIndication -----

DictEntry Dict278Contents[] = {
{ 0x0021, 0x0002, 0, VR::SQ, VM::M1, "EvaluatorSequence" },
{ 0x0021, 0x0004, 0, VR::IS, VM::M1, "EvaluatorNumber" },
{ 0x0021, 0x0006, 0, VR::PN, VM::M1, "EvaluatorName" },
{ 0x0021, 0x0008, 0, VR::IS, VM::M1, "EvaluationAttempt" },
{ 0x0021, 0x0012, 0, VR::SQ, VM::M1, "IndicationSequence" },
{ 0x0021, 0x0014, 0, VR::IS, VM::M1, "IndicationNumber" },
{ 0x0021, 0x0016, 0, VR::SH, VM::M1, "IndicationLabel" },
{ 0x0021, 0x0018, 0, VR::ST, VM::M1, "IndicationDescription" },
{ 0x0021, 0x001A, 0, VR::CS, VM::M1TN, "IndicationType" },
{ 0x0021, 0x001C, 0, VR::CS, VM::M1, "IndicationDisposition" },
{ 0x0021, 0x001E, 0, VR::SQ, VM::M1, "IndicationROISequence" },
{ 0x0021, 0x0030, 0, VR::SQ, VM::M1, "IndicationPhysicalPropertySequence" },
{ 0x0021, 0x0032, 0, VR::SH, VM::M1, "PropertyLabel" },
};

unsigned short Dict278TagHashTable[] = {
    4,    13,    22,     0,     4,     2,     6,     4,    18,     7,
   24,    10,    30,     4,     1,     4,     6,    22,     9,    28,
   12,    50,     5,     0,     2,     3,     8,     5,    20,     8,
   26,    11,    48,
};

vtkDICOMDictionary::Dict Dict278Data = {
"astm.org/diconde/iod/NdeIndication",
3,
13,
Dict278TagHashTable,
Dict278Contents
};

// ----- GEMS_LUNAR_RAW -----

DictEntry Dict279Contents[] = {
{ 0x7003, 0x0001, 0, VR::ST, VM::M1, "enCOREFileName" },
{ 0x7003, 0x0002, 0, VR::OB, VM::M1, "enCOREFileData" },
{ 0x7003, 0x0003, 0, VR::UL, VM::M1, "enCOREFileLength" },
{ 0x7003, 0x0004, 0, VR::LO, VM::M1, "enCOREFileModifiedTime" },
};

unsigned short Dict279TagHashTable[] = {
    2,     0,     4,     0,     1,     1,     2,     2,     3,     3,
    4,
};

vtkDICOMDictionary::Dict Dict279Data = {
"GEMS_LUNAR_RAW",
1,
4,
Dict279TagHashTable,
Dict279Contents
};

// ----- PRIVATE_CODE_STRING_3007 -----

DictEntry Dict280Contents[] = {
{ 0x3007, 0x0000, 0, VR::FD, VM::M16, "VolumeToPatientMatrix" },
{ 0x3007, 0x0001, 0, VR::FD, VM::M16, "VolumeResolutionConversion" },
{ 0x3007, 0x0002, 0, VR::FD, VM::M16, "VolumeDataConversion" },
{ 0x3007, 0x0003, 0, VR::FD, VM::M16, "PatientDataConversion" },
{ 0x3007, 0x0004, 0, VR::FD, VM::M16, "DICOMDataConversion" },
};

unsigned short Dict280TagHashTable[] = {
    2,     0,     5,     0,     0,     1,     1,     2,     2,     3,
    3,     4,     4,
};

vtkDICOMDictionary::Dict Dict280Data = {
"PRIVATE_CODE_STRING_3007",
1,
5,
Dict280TagHashTable,
Dict280Contents
};

// ----- SPI-P Release 2;1 -----

DictEntry Dict281Contents[] = {
{ 0x0011, 0x0018, 0, VR::LT, VM::M1, "" },
{ 0x0023, 0x000d, 0, VR::UI, VM::M1, "" },
{ 0x0023, 0x000e, 0, VR::UI, VM::M1, "" },
};

unsigned short Dict281TagHashTable[] = {
    2,     0,     3,     0,    24,     1,    13,     2,    14,
};

vtkDICOMDictionary::Dict Dict281Data = {
"SPI-P Release 2;1",
1,
3,
Dict281TagHashTable,
Dict281Contents
};

// ----- ETIAM DICOMDIR -----

DictEntry Dict282Contents[] = {
{ 0x0859, 0x0040, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict282TagHashTable[] = {
    2,     0,     1,     0,    64,
};

vtkDICOMDictionary::Dict Dict282Data = {
"ETIAM DICOMDIR",
1,
1,
Dict282TagHashTable,
Dict282Contents
};

// ----- MAROTECH Inc. -----

DictEntry Dict283Contents[] = {
{ 0x0037, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0037, 0x0021, 0, VR::US, VM::M1, "" },
{ 0x0037, 0x0022, 0, VR::US, VM::M1, "" },
{ 0x0037, 0x0023, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict283TagHashTable[] = {
    2,     0,     4,     0,     1,     1,    33,     2,    34,     3,
   35,
};

vtkDICOMDictionary::Dict Dict283Data = {
"MAROTECH Inc.",
1,
4,
Dict283TagHashTable,
Dict283Contents
};

// ----- GEMS_DL_FRAME_01 -----

DictEntry Dict284Contents[] = {
{ 0x0025, 0x0002, 0, VR::IS, VM::M1, "FrameID" },
{ 0x0025, 0x0003, 0, VR::DS, VM::M1, "DistanceSourceToDetector" },
{ 0x0025, 0x0004, 0, VR::DS, VM::M1, "DistanceSourceToPatient" },
{ 0x0025, 0x0005, 0, VR::DS, VM::M1, "DistanceSourceToSkin" },
{ 0x0025, 0x0006, 0, VR::DS, VM::M1, "PositionerPrimaryAngle" },
{ 0x0025, 0x0007, 0, VR::DS, VM::M1, "PositionerSecondaryAngle" },
{ 0x0025, 0x0008, 0, VR::IS, VM::M1, "BeamOrientation" },
{ 0x0025, 0x0009, 0, VR::DS, VM::M1, "LArmAngle" },
{ 0x0025, 0x000A, 0, VR::SQ, VM::M1, "FrameSequence" },
{ 0x0025, 0x0010, 0, VR::DS, VM::M1, "PivotAngle" },
{ 0x0025, 0x001A, 0, VR::DS, VM::M1, "ArcAngle" },
{ 0x0025, 0x001B, 0, VR::DS, VM::M1, "TableVerticalPosition" },
{ 0x0025, 0x001C, 0, VR::DS, VM::M1, "TableLongitudinalPosition" },
{ 0x0025, 0x001D, 0, VR::DS, VM::M1, "Table Lateral Position" },
{ 0x0025, 0x001E, 0, VR::IS, VM::M1, "BeamCoverArea" },
{ 0x0025, 0x001F, 0, VR::DS, VM::M1, "kVPActual" },
{ 0x0025, 0x0020, 0, VR::DS, VM::M1, "mASActual" },
{ 0x0025, 0x0021, 0, VR::DS, VM::M1, "PWActual" },
{ 0x0025, 0x0022, 0, VR::DS, VM::M1, "KvpCommanded" },
{ 0x0025, 0x0023, 0, VR::DS, VM::M1, "MasCommanded" },
{ 0x0025, 0x0024, 0, VR::DS, VM::M1, "PwCommanded" },
{ 0x0025, 0x0025, 0, VR::CS, VM::M1, "Grid" },
{ 0x0025, 0x0026, 0, VR::DS, VM::M1, "SensorFeedback" },
{ 0x0025, 0x0027, 0, VR::DS, VM::M1, "TargetEntranceDose" },
{ 0x0025, 0x0028, 0, VR::DS, VM::M1, "CnrCommanded" },
{ 0x0025, 0x0029, 0, VR::DS, VM::M1, "ContrastCommanded" },
{ 0x0025, 0x002A, 0, VR::DS, VM::M1, "EPTActual" },
{ 0x0025, 0x002B, 0, VR::IS, VM::M1, "SpectralFilterZnb" },
{ 0x0025, 0x002C, 0, VR::DS, VM::M1, "SpectralFilterWeight" },
{ 0x0025, 0x002D, 0, VR::DS, VM::M1, "SpectralFilterDensity" },
{ 0x0025, 0x002E, 0, VR::IS, VM::M1, "SpectralFilterThickness" },
{ 0x0025, 0x002F, 0, VR::IS, VM::M1, "SpectralFilterStatus" },
{ 0x0025, 0x0030, 0, VR::IS, VM::M2, "FOVDimension" },
{ 0x0025, 0x0033, 0, VR::IS, VM::M2, "FOVOrigin" },
{ 0x0025, 0x0034, 0, VR::IS, VM::M1, "CollimatorLeftVerticalEdge" },
{ 0x0025, 0x0035, 0, VR::IS, VM::M1, "CollimatorRightVerticalEdge" },
{ 0x0025, 0x0036, 0, VR::IS, VM::M1, "CollimatorUpHorizontalEdge" },
{ 0x0025, 0x0037, 0, VR::IS, VM::M1, "CollimatorLowHorizontalEdge" },
{ 0x0025, 0x0038, 0, VR::IS, VM::M1, "VerticesPolygonalCollimator" },
{ 0x0025, 0x0039, 0, VR::IS, VM::M1, "ContourFilterDistance" },
{ 0x0025, 0x003A, 0, VR::UL, VM::M1, "ContourFilterAngle" },
{ 0x0025, 0x003B, 0, VR::CS, VM::M1, "TableRotationStatus" },
{ 0x0025, 0x003C, 0, VR::CS, VM::M1, "InternalLabelFrame" },
};

unsigned short Dict284TagHashTable[] = {
   11,    18,    27,    38,    49,    58,    69,    76,    85,    96,
    0,     3,    21,    37,    31,    47,    41,    59,     4,    20,
   36,    30,    46,    32,    48,    40,    58,     5,     3,     5,
   11,    27,    23,    39,    25,    41,    33,    51,     5,     2,
    4,     9,    16,    10,    26,    22,    38,    24,    40,     4,
    5,     7,     7,     9,    17,    33,    27,    43,     5,     4,
    6,     6,     8,    16,    32,    26,    42,    42,    60,     3,
   13,    29,    19,    35,    35,    53,     4,     8,    10,    12,
   28,    18,    34,    34,    52,     5,     1,     3,    15,    31,
   29,    45,    37,    55,    39,    57,     5,     0,     2,    14,
   30,    28,    44,    36,    54,    38,    56,
};

vtkDICOMDictionary::Dict Dict284Data = {
"GEMS_DL_FRAME_01",
10,
43,
Dict284TagHashTable,
Dict284Contents
};

// ----- PHILIPS MR/PART 12 -----

DictEntry Dict285Contents[] = {
{ 0x0009, 0x0010, 0, VR::US, VM::M1, "" },
};

unsigned short Dict285TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict285Data = {
"PHILIPS MR/PART 12",
1,
1,
Dict285TagHashTable,
Dict285Contents
};

// ----- SIEMENS MR N3D -----

DictEntry Dict286Contents[] = {
{ 0x0021, 0x0030, 0, VR::SQ, VM::M1, "BackgroundColorDRSequence" },
{ 0x0021, 0x0031, 0, VR::DS, VM::M3, "BackgroundColor" },
{ 0x0021, 0x0036, 0, VR::SQ, VM::M1, "FieldMapDRSequence" },
{ 0x0021, 0x0037, 0, VR::CS, VM::M1, "Visible" },
{ 0x0021, 0x0038, 0, VR::DS, VM::M3, "TintingColor" },
{ 0x0021, 0x0039, 0, VR::CS, VM::M1, "TintingEnabled" },
{ 0x0021, 0x003A, 0, VR::LO, VM::M1, "VolumeID" },
{ 0x0021, 0x003B, 0, VR::LO, VM::M1, "VolumeIDAsBound" },
{ 0x0021, 0x0041, 0, VR::SQ, VM::M1, "FloatingMPRColorLUTDRSequence" },
{ 0x0021, 0x0042, 0, VR::DS, VM::M1, "RGBALUT" },
{ 0x0021, 0x0043, 0, VR::DS, VM::M1, "BlendFactor" },
{ 0x0021, 0x0044, 0, VR::SQ, VM::M1, "RGBALUTDataSequence" },
{ 0x0021, 0x0045, 0, VR::OB, VM::M1, "ColorLUT" },
{ 0x0021, 0x004A, 0, VR::SQ, VM::M1, "OrthoMPRColorLUTDRSequence" },
{ 0x0021, 0x004B, 0, VR::SQ, VM::M1, "VRTColorLUTDRSequence" },
{ 0x0021, 0x004C, 0, VR::SQ, VM::M1, "PwlTransferFunctionSequence" },
{ 0x0021, 0x004D, 0, VR::SQ, VM::M1, "PwlTransferFunctionDataSequence" },
{ 0x0021, 0x004E, 0, VR::DS, VM::M1, "PwlVertexIndex" },
{ 0x0021, 0x0050, 0, VR::SQ, VM::M1, "PwlVertexSequence" },
{ 0x0021, 0x0051, 0, VR::SQ, VM::M1, "FloatingMPRRenderDRSequence" },
{ 0x0021, 0x0052, 0, VR::CS, VM::M1, "PrimaryShowHide" },
{ 0x0021, 0x0053, 0, VR::CS, VM::M1, "SecondaryShowHide" },
{ 0x0021, 0x0054, 0, VR::LO, VM::M1, "PrimaryShadingIndex" },
{ 0x0021, 0x0055, 0, VR::LO, VM::M1, "SecondaryShadingIndex" },
{ 0x0021, 0x0056, 0, VR::CS, VM::M1, "AlphaDependentFieldmap" },
{ 0x0021, 0x0057, 0, VR::LO, VM::M1, "VolumeFilter" },
{ 0x0021, 0x0058, 0, VR::DS, VM::M3, "BoundingBoxColor" },
{ 0x0021, 0x0059, 0, VR::CS, VM::M1, "SceneInteractionOn" },
{ 0x0021, 0x005A, 0, VR::SQ, VM::M1, "OrthoMPRRenderDRSequence" },
{ 0x0021, 0x005B, 0, VR::SQ, VM::M1, "VRTRenderDRSequence" },
{ 0x0021, 0x0060, 0, VR::SQ, VM::M6, "ClipPlaneDRSequence" },
{ 0x0021, 0x0061, 0, VR::DS, VM::M3, "PlaneCenter" },
{ 0x0021, 0x0062, 0, VR::DS, VM::M3, "PlaneNormal" },
{ 0x0021, 0x0063, 0, VR::DS, VM::M2, "PlaneScale" },
{ 0x0021, 0x0064, 0, VR::CS, VM::M1, "PlaneEnableGLClip" },
{ 0x0021, 0x0065, 0, VR::DS, VM::M1, "PlaneHandleRatio" },
{ 0x0021, 0x0066, 0, VR::DS, VM::M24, "PlaneBoundingPoints" },
{ 0x0021, 0x0067, 0, VR::DS, VM::M16, "PlaneMotionMatrix" },
{ 0x0021, 0x0068, 0, VR::DS, VM::M1, "PlaneShiftVelocity" },
{ 0x0021, 0x0069, 0, VR::CS, VM::M1, "PlaneEnabled" },
{ 0x0021, 0x006A, 0, VR::DS, VM::M1, "PlaneRotateVelocity" },
{ 0x0021, 0x006B, 0, VR::CS, VM::M1, "PlaneShowGraphics" },
{ 0x0021, 0x006C, 0, VR::DS, VM::M1, "Offset" },
{ 0x0021, 0x006D, 0, VR::CS, VM::M1, "OrthoMPRAtBoundingBox" },
{ 0x0021, 0x006E, 0, VR::CS, VM::M1, "PlaneMPRLocked" },
{ 0x0021, 0x006F, 0, VR::CS, VM::M1, "PlaneScalingDisabled" },
{ 0x0021, 0x0070, 0, VR::SQ, VM::M1, "SplitPlaneDRSequence" },
{ 0x0021, 0x0071, 0, VR::SQ, VM::M3, "FloatingMPRDRSequence" },
{ 0x0021, 0x0072, 0, VR::SQ, VM::M3, "OrthoMPRDRSequence" },
{ 0x0021, 0x0073, 0, VR::CS, VM::M1, "PlaneSingleSelectionMode" },
{ 0x0021, 0x0074, 0, VR::CS, VM::M1, "PlaneAlignment" },
{ 0x0021, 0x0075, 0, VR::CS, VM::M1, "PlaneSelected" },
{ 0x0021, 0x0076, 0, VR::SQ, VM::M1, "ClusteringDRSequence" },
{ 0x0021, 0x0077, 0, VR::DS, VM::M1, "ClusterSize" },
{ 0x0021, 0x0078, 0, VR::CS, VM::M1, "ClusteringEnabled" },
{ 0x0021, 0x0079, 0, VR::LO, VM::M1, "ClusterMaskVolID" },
{ 0x0021, 0x0080, 0, VR::SQ, VM::M1, "HeadMaskingDRSequence" },
{ 0x0021, 0x0081, 0, VR::DS, VM::M2, "MaskingRange" },
{ 0x0021, 0x0082, 0, VR::CS, VM::M1, "MaskEnabled" },
{ 0x0021, 0x0083, 0, VR::SQ, VM::M1, "BrainMaskingDRSequence" },
{ 0x0021, 0x0084, 0, VR::SQ, VM::M1, "MaskingStatusDRSequence" },
{ 0x0021, 0x0085, 0, VR::SQ, VM::M1, "VRTMaskingDRSequence" },
{ 0x0021, 0x0086, 0, VR::SQ, VM::M1, "OrthoMPRMaskingDRSequence" },
{ 0x0021, 0x0087, 0, VR::SQ, VM::M1, "FloatingMPRMaskingDRSequence" },
{ 0x0021, 0x0088, 0, VR::SQ, VM::M1, "AlignDRSequence" },
{ 0x0021, 0x0089, 0, VR::DS, VM::M16, "RegistrationMatrix" },
{ 0x0021, 0x0090, 0, VR::SQ, VM::M1, "FunctionalEvaluationDRSequence" },
{ 0x0021, 0x0091, 0, VR::DS, VM::M1TN, "FrameAcquitionNumbers" },
{ 0x0021, 0x0092, 0, VR::CS, VM::M1, "ShowCursor" },
{ 0x0021, 0x0093, 0, VR::DS, VM::M1, "CurrentFrame" },
{ 0x0021, 0x0094, 0, VR::DS, VM::M1TN, "PlotArea" },
{ 0x0021, 0x0095, 0, VR::DS, VM::M2, "PlotTextPosition" },
{ 0x0021, 0x0096, 0, VR::DS, VM::M1TN, "BaseLinePoints" },
{ 0x0021, 0x0097, 0, VR::DS, VM::M1TN, "ActivePoints" },
{ 0x0021, 0x0098, 0, VR::CS, VM::M1, "ShowLabel" },
{ 0x0021, 0x0099, 0, VR::CS, VM::M1, "MeanPlot" },
{ 0x0021, 0x009A, 0, VR::CS, VM::M1, "MotionPlot" },
{ 0x0021, 0x009B, 0, VR::CS, VM::M1, "ActivateNormallizedCurve" },
{ 0x0021, 0x009C, 0, VR::DS, VM::M1, "PlotSize" },
{ 0x0021, 0x00A0, 0, VR::SQ, VM::M4, "PlotDRSequence" },
{ 0x0021, 0x00A1, 0, VR::LO, VM::M1, "Title" },
{ 0x0021, 0x00A2, 0, VR::CS, VM::M1, "AutoScale" },
{ 0x0021, 0x00A3, 0, VR::DS, VM::M1, "FixedScale" },
{ 0x0021, 0x00A4, 0, VR::DS, VM::M3, "BackgroundColor" },
{ 0x0021, 0x00A5, 0, VR::LO, VM::M1, "LabelX" },
{ 0x0021, 0x00A6, 0, VR::LO, VM::M1, "LabelY" },
{ 0x0021, 0x00A7, 0, VR::CS, VM::M1, "Legend" },
{ 0x0021, 0x00A8, 0, VR::CS, VM::M1, "ScrollBarX" },
{ 0x0021, 0x00A9, 0, VR::CS, VM::M1, "ScrollBarY" },
{ 0x0021, 0x00AA, 0, VR::LO, VM::M1, "ConnectScrollX" },
{ 0x0021, 0x00AB, 0, VR::LO, VM::M1, "PlotID" },
{ 0x0021, 0x00AC, 0, VR::DS, VM::M1, "PlotPosition" },
{ 0x0021, 0x00B0, 0, VR::SQ, VM::M1, "CurveDRSequence" },
{ 0x0021, 0x00B1, 0, VR::LO, VM::M1, "CurveID" },
{ 0x0021, 0x00B2, 0, VR::LO, VM::M1, "PlotType" },
{ 0x0021, 0x00B3, 0, VR::DS, VM::M1TN, "CurveValues" },
{ 0x0021, 0x00B4, 0, VR::DS, VM::M3, "LineColor" },
{ 0x0021, 0x00B5, 0, VR::DS, VM::M3, "MarkerColor" },
{ 0x0021, 0x00B6, 0, VR::CS, VM::M1, "LineFilled" },
{ 0x0021, 0x00B7, 0, VR::LO, VM::M1, "Label" },
{ 0x0021, 0x00B8, 0, VR::CS, VM::M1, "ShowMarker" },
{ 0x0021, 0x00B9, 0, VR::LO, VM::M1, "MarkerShape" },
{ 0x0021, 0x00BA, 0, VR::LO, VM::M1, "SmoothingAlgo" },
{ 0x0021, 0x00BB, 0, VR::DS, VM::M1, "MarkerSize" },
{ 0x0021, 0x00BC, 0, VR::LO, VM::M1, "LineStyle" },
{ 0x0021, 0x00BD, 0, VR::LO, VM::M1, "LinePattern" },
{ 0x0021, 0x00BE, 0, VR::DS, VM::M1, "LineWidth" },
{ 0x0021, 0x00C0, 0, VR::SQ, VM::M1, "VRTFilterDRSequence" },
{ 0x0021, 0x00C1, 0, VR::LO, VM::M1, "FilterType" },
{ 0x0021, 0x00C2, 0, VR::CS, VM::M1, "CurrentActivePlane" },
};

unsigned short Dict286TagHashTable[] = {
   28,    39,    48,    59,    66,    75,    82,    87,    92,   103,
  110,   119,   128,   135,   142,   151,   160,   171,   182,   191,
  200,   211,   218,   229,   240,   251,   264,     0,     5,     6,
   58,    15,    76,    47,   113,    57,   129,    83,   164,     4,
   16,    77,    48,   114,    56,   128,    90,   171,     5,    17,
   78,    49,   115,    63,   135,    78,   156,    89,   170,     3,
   50,   116,    62,   134,    88,   169,     4,    18,    80,    51,
  117,    61,   133,    87,   168,     3,    19,    81,    52,   118,
   60,   132,     2,    20,    82,    53,   119,     2,    21,    83,
   54,   120,     5,    22,    84,    55,   121,    65,   137,    91,
  172,   109,   194,     3,    23,    85,    64,   136,    95,   179,
    4,    24,    86,    30,    96,    94,   178,   107,   192,     4,
   25,    87,    31,    97,    93,   177,   108,   193,     3,    26,
   88,    32,    98,    92,   176,     3,    27,    89,    33,    99,
   99,   183,     4,    28,    90,    34,   100,    69,   147,    98,
  182,     4,    29,    91,    35,   101,    68,   146,    97,   181,
    5,     1,    49,     8,    65,    36,   102,    67,   145,    96,
  180,     5,     0,    48,     9,    66,    37,   103,    66,   144,
  103,   187,     4,    10,    67,    38,   104,    73,   151,   102,
  186,     4,    11,    68,    39,   105,    72,   150,   101,   185,
    5,    12,    69,    40,   106,    71,   149,    82,   163,   100,
  184,     3,    41,   107,    70,   148,    81,   162,     5,     3,
   55,    42,   108,    77,   155,    80,   161,   106,   190,     5,
    2,    54,    43,   109,    76,   154,    79,   160,   105,   189,
    5,     5,    57,    44,   110,    75,   153,    86,   167,   104,
  188,     6,     4,    56,    13,    74,    45,   111,    59,   131,
   74,   152,    85,   166,     5,     7,    59,    14,    75,    46,
  112,    58,   130,    84,   165,
};

vtkDICOMDictionary::Dict Dict286Data = {
"SIEMENS MR N3D",
27,
110,
Dict286TagHashTable,
Dict286Contents
};

// ----- Camtronics image level data -----

DictEntry Dict287Contents[] = {
{ 0x0009, 0x0004, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0006, 0, VR::IS, VM::M1, "" },
{ 0x0009, 0x0009, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0016, 0, VR::AE, VM::M1, "" },
{ 0x0009, 0x0017, 0, VR::CS, VM::M1, "" },
{ 0x0009, 0x0018, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict287TagHashTable[] = {
    2,     0,     6,     0,     4,     1,     6,     2,     9,     3,
   22,     4,    23,     5,    24,
};

vtkDICOMDictionary::Dict Dict287Data = {
"Camtronics image level data",
1,
6,
Dict287TagHashTable,
Dict287Contents
};

// ----- SIEMENS MED HG -----

DictEntry Dict288Contents[] = {
{ 0x0029, 0x0010, 0, VR::US, VM::M1, "ListOfGroupNumbers" },
{ 0x0029, 0x0015, 0, VR::LO, VM::M1, "ListOfShadowOwnerCodes" },
{ 0x0029, 0x0020, 0, VR::US, VM::M1, "ListOfElementNumbers" },
{ 0x0029, 0x0030, 0, VR::US, VM::M1, "ListOfTotalDisplayLength" },
{ 0x0029, 0x0040, 0, VR::LO, VM::M1TN, "ListOfDisplayPrefix" },
{ 0x0029, 0x0050, 0, VR::LO, VM::M1TN, "ListOfDisplayPostfix" },
{ 0x0029, 0x0060, 0, VR::US, VM::M1, "ListOfTextPosition" },
{ 0x0029, 0x0070, 0, VR::LO, VM::M1, "ListOfTextConcatenation" },
};

unsigned short Dict288TagHashTable[] = {
    3,    14,     0,     5,     1,    21,     4,    64,     5,    80,
    6,    96,     7,   112,     3,     0,    16,     2,    32,     3,
   48,
};

vtkDICOMDictionary::Dict Dict288Data = {
"SIEMENS MED HG",
2,
8,
Dict288TagHashTable,
Dict288Contents
};

// ----- BrainLAB_PatientSetup -----

DictEntry Dict289Contents[] = {
{ 0x3273, 0x0000, 0, VR::DS, VM::M3, "IsocenterPosition" },
{ 0x3273, 0x0001, 0, VR::CS, VM::M1, "PatientPosition" },
};

unsigned short Dict289TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict289Data = {
"BrainLAB_PatientSetup",
1,
2,
Dict289TagHashTable,
Dict289Contents
};

// ----- GEMS_CT_CARDIAC_001 -----

DictEntry Dict290Contents[] = {
{ 0x0049, 0x0001, 0, VR::SQ, VM::M1, "CTCardiacSequence" },
{ 0x0049, 0x0002, 0, VR::CS, VM::M1, "HeartRateAtConfirm" },
{ 0x0049, 0x0003, 0, VR::FL, VM::M1, "AvgHeartRatePriorToConfirm" },
{ 0x0049, 0x0004, 0, VR::CS, VM::M1, "MinHeartRatePriorToConfirm" },
{ 0x0049, 0x0005, 0, VR::CS, VM::M1, "MaxHeartRatePriorToConfirm" },
{ 0x0049, 0x0006, 0, VR::FL, VM::M1, "StdDevHeartRatePriorToConfirm" },
{ 0x0049, 0x0007, 0, VR::US, VM::M1, "NumHeartRateSamplesPriorToConfirm" },
{ 0x0049, 0x0008, 0, VR::CS, VM::M1, "AutoHeartRateDetectPredict" },
{ 0x0049, 0x0009, 0, VR::CS, VM::M1, "SystemOptimizedHeartRate" },
{ 0x0049, 0x000A, 0, VR::ST, VM::M1, "EkgMonitorType" },
{ 0x0049, 0x000B, 0, VR::CS, VM::M1, "NumReconSectors" },
{ 0x0049, 0x000C, 0, VR::FL, VM::M256, "RpeakTimeStamps" },
};

unsigned short Dict290TagHashTable[] = {
    4,    11,    22,     0,     3,     2,     3,     5,     6,     9,
   10,     5,     0,     1,     3,     4,     6,     7,     7,     8,
   10,    11,     4,     1,     2,     4,     5,     8,     9,    11,
   12,
};

vtkDICOMDictionary::Dict Dict290Data = {
"GEMS_CT_CARDIAC_001",
3,
12,
Dict290TagHashTable,
Dict290Contents
};

// ----- MMCPrivate -----

DictEntry Dict291Contents[] = {
{ 0x0009, 0x0001, 0, VR::LO, VM::M1, "Technologist" },
{ 0x0009, 0x0002, 0, VR::LO, VM::M1, "ScheduledStudyDateTime" },
{ 0x0009, 0x0003, 0, VR::OB, VM::M1, "StudyAppData" },
{ 0x0009, 0x0048, 0, VR::LO, VM::M1, "ProtocolName" },
{ 0x0009, 0x004e, 0, VR::LO, VM::M1, "Cms_BodyPartExamined" },
{ 0x0009, 0x004f, 0, VR::LO, VM::M1, "IsProtected" },
{ 0x0009, 0x0050, 0, VR::CS, VM::M1, "Cms_PatientPosition" },
{ 0x0009, 0x0051, 0, VR::LO, VM::M1, "Cmi_contrastBolusAgent" },
{ 0x0009, 0x0052, 0, VR::LO, VM::M1, "Cms_institutionName" },
{ 0x0009, 0x0053, 0, VR::LO, VM::M1, "Cms_institutionalDepartmentName" },
{ 0x0009, 0x0054, 0, VR::LO, VM::M1, "Cms_seriesDescription" },
{ 0x0009, 0x0055, 0, VR::LO, VM::M1, "Cms_operatorsName" },
{ 0x0009, 0x0056, 0, VR::LO, VM::M1, "Cms_PerformingPhysiciansName" },
{ 0x0009, 0x0057, 0, VR::ST, VM::M1, "Cms_institutionAddress" },
{ 0x0009, 0x0058, 0, VR::LO, VM::M1, "Cmi_imageComments" },
{ 0x0009, 0x0059, 0, VR::LO, VM::M1, "Cmi_instanceCreationDateTime" },
{ 0x0009, 0x005A, 0, VR::LO, VM::M1, "MPPSStepStatus" },
{ 0x0009, 0x005B, 0, VR::IS, VM::M1, "FilmedCount" },
{ 0x0009, 0x005C, 0, VR::LO, VM::M1, "IsAllowCascadeSave" },
{ 0x0009, 0x005D, 0, VR::LO, VM::M1, "IsAllowCascadeProtect" },
{ 0x0009, 0x005E, 0, VR::LO, VM::M1, "IsDeleted" },
{ 0x0011, 0x0001, 0, VR::LO, VM::M1, "IsRapidRegistration" },
{ 0x0011, 0x0002, 0, VR::LO, VM::M1, "IsProtected" },
{ 0x0011, 0x0003, 0, VR::IS, VM::M1, "FilmedCount" },
{ 0x0011, 0x0004, 0, VR::OB, VM::M1, "ApplicationData" },
{ 0x0011, 0x0005, 0, VR::LO, VM::M1, "IsAllowCascadeSave" },
{ 0x0011, 0x0006, 0, VR::LO, VM::M1, "IsAllowCascadeProtect" },
{ 0x0011, 0x0007, 0, VR::LO, VM::M1, "IsDeleted" },
{ 0x0019, 0x0001, 0, VR::LO, VM::M1, "ProcType" },
{ 0x0019, 0x0002, 0, VR::LO, VM::M1, "Plane" },
{ 0x0019, 0x0003, 0, VR::SH, VM::M1, "IsSnapShotSeries" },
{ 0x0019, 0x0004, 0, VR::DS, VM::M1, "MaxFscalor" },
{ 0x0019, 0x0005, 0, VR::LO, VM::M1, "SeriesCategoryType" },
{ 0x0019, 0x0007, 0, VR::LO, VM::M1, "ImageContrastBolusAgent" },
{ 0x0019, 0x0008, 0, VR::DS, VM::M1, "ImageSliceThickness" },
{ 0x0019, 0x0009, 0, VR::DS, VM::M1, "ImageReconstructionDiameter" },
{ 0x0019, 0x000a, 0, VR::LO, VM::M1, "ImageEchoTime" },
{ 0x0019, 0x000b, 0, VR::DS, VM::M1, "ImageRepetitionTime" },
{ 0x0019, 0x000c, 0, VR::LO, VM::M1, "SequenceType" },
{ 0x0019, 0x000d, 0, VR::LO, VM::M1, "TaskUID" },
{ 0x0019, 0x000e, 0, VR::OB, VM::M1, "SeriesAppData" },
{ 0x0019, 0x000f, 0, VR::IS, VM::M1, "MultiSliceNumber" },
{ 0x0019, 0x0010, 0, VR::LO, VM::M1, "ImageScanTime" },
{ 0x0019, 0x0011, 0, VR::LO, VM::M1, "IsProtected" },
{ 0x0019, 0x0012, 0, VR::IS, VM::M1, "ImageIncrement" },
{ 0x0019, 0x0013, 0, VR::LO, VM::M1, "MPPSStepStatus" },
{ 0x0019, 0x0014, 0, VR::IS, VM::M1, "StorageCommittedCount" },
{ 0x0019, 0x0015, 0, VR::IS, VM::M1, "ArchivedCount" },
{ 0x0019, 0x0016, 0, VR::IS, VM::M1, "TransferredCount" },
{ 0x0019, 0x0017, 0, VR::LO, VM::M1, "IsAllowCascadeSave" },
{ 0x0019, 0x0018, 0, VR::LO, VM::M1, "IsAllowCascadeProtect" },
{ 0x0019, 0x0019, 0, VR::LO, VM::M1, "IsDeleted" },
{ 0x0019, 0x001A, 0, VR::UI, VM::M1, "CharacterizedImageInstanceUID" },
{ 0x0019, 0x001B, 0, VR::IS, VM::M1, "CharacterizedImageCount" },
{ 0x0019, 0x001C, 0, VR::LO, VM::M1, "InternalWindowWidth" },
{ 0x0019, 0x001D, 0, VR::LO, VM::M1, "InternalWindowLevel" },
{ 0x0019, 0x001E, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0001, 0, VR::IS, VM::M1, "SliceNumber" },
{ 0x0029, 0x0002, 0, VR::IS, VM::M1, "PhaseNumber" },
{ 0x0029, 0x0003, 0, VR::LO, VM::M1, "ProcType" },
{ 0x0029, 0x0004, 0, VR::LO, VM::M1, "StopwatchTime" },
{ 0x0029, 0x0005, 0, VR::LO, VM::M1, "Plane" },
{ 0x0029, 0x0006, 0, VR::LO, VM::M1, "ScanTime" },
{ 0x0029, 0x0008, 0, VR::LO, VM::M1, "DualSliceFlag" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "SSPRatio" },
{ 0x0029, 0x000a, 0, VR::LO, VM::M1, "GatingSignalSource" },
{ 0x0029, 0x000b, 0, VR::LO, VM::M1, "Rephase" },
{ 0x0029, 0x000c, 0, VR::LO, VM::M1, "HalfEcho" },
{ 0x0029, 0x000d, 0, VR::LO, VM::M1, "RectFOVRatio" },
{ 0x0029, 0x000e, 0, VR::LO, VM::M1, "HalfScan" },
{ 0x0029, 0x000f, 0, VR::LO, VM::M1, "NumShots" },
{ 0x0029, 0x0010, 0, VR::LO, VM::M1, "ContrastAgent" },
{ 0x0029, 0x0011, 0, VR::LO, VM::M1, "EchoAllocation" },
{ 0x0029, 0x0012, 0, VR::LO, VM::M1, "NumEchoShift" },
{ 0x0029, 0x0013, 0, VR::LO, VM::M1, "FatSat" },
{ 0x0029, 0x0014, 0, VR::LO, VM::M1, "MTC" },
{ 0x0029, 0x0015, 0, VR::LO, VM::M1, "NumPreSat" },
{ 0x0029, 0x0016, 0, VR::LO, VM::M1, "TargetVelocity" },
{ 0x0029, 0x0017, 0, VR::LO, VM::M1, "VENCAxis" },
{ 0x0029, 0x0018, 0, VR::LO, VM::M1, "NumVENCDirection" },
{ 0x0029, 0x001c, 0, VR::LO, VM::M1, "IsScalableWindowLevel" },
{ 0x0029, 0x001d, 0, VR::LO, VM::M1, "ThreeDSettingLineAngle" },
{ 0x0029, 0x001e, 0, VR::LO, VM::M1, "MPGTotalAxis" },
{ 0x0029, 0x001f, 0, VR::LO, VM::M1, "MPGAxisNumber" },
{ 0x0029, 0x0020, 0, VR::IS, VM::M1, "MultiEchoNumber" },
{ 0x0029, 0x0021, 0, VR::DS, VM::M1, "NaviAverageGateWidth" },
{ 0x0029, 0x0022, 0, VR::ST, VM::M1, "ShimCompensateValue" },
{ 0x0029, 0x0023, 0, VR::LO, VM::M1, "GCOffset" },
{ 0x0029, 0x0024, 0, VR::DS, VM::M1, "NaviMaxGateWidth" },
{ 0x0029, 0x0025, 0, VR::DS, VM::M1, "NaviMinGateWidth" },
{ 0x0029, 0x0026, 0, VR::DS, VM::M1, "NaviMaxGatePosition" },
{ 0x0029, 0x0027, 0, VR::DS, VM::M1, "NaviMinGatePosition" },
{ 0x0029, 0x0028, 0, VR::DS, VM::M1, "TimeDuration" },
{ 0x0029, 0x0029, 0, VR::DS, VM::M1, "TablePosition" },
{ 0x0029, 0x002a, 0, VR::DS, VM::M1, "NaviInitialGateWidth" },
{ 0x0029, 0x002b, 0, VR::DS, VM::M1, "NaviFinalGateWidth" },
{ 0x0029, 0x002c, 0, VR::DS, VM::M1, "NaviInitialGatePosition" },
{ 0x0029, 0x002d, 0, VR::DS, VM::M1, "NaviFinalGatePosition" },
{ 0x0029, 0x002e, 0, VR::DS, VM::M1, "NaviAverageGatePosition" },
{ 0x0029, 0x002f, 0, VR::OB, VM::M1, "ImageAppData" },
{ 0x0029, 0x0030, 0, VR::FD, VM::M1, "DiffusionBValue" },
{ 0x0029, 0x0031, 0, VR::SQ, VM::M1, "SharedFunctionalGroupsSequence" },
{ 0x0029, 0x0032, 0, VR::SQ, VM::M1, "PerFrameFunctionalGroupsSequence" },
{ 0x0029, 0x0033, 0, VR::DS, VM::M1, "LossyImageCompressionRatio" },
{ 0x0029, 0x0034, 0, VR::UI, VM::M1, "InstanceCreatorUID" },
{ 0x0029, 0x0035, 0, VR::UI, VM::M1, "RelatedGeneralSOPClassUID" },
{ 0x0029, 0x0036, 0, VR::UI, VM::M1, "OriginalSpecializedSOPClassUID" },
{ 0x0029, 0x0037, 0, VR::SH, VM::M1, "TimezoneOffsetFromUTC" },
{ 0x0029, 0x0038, 0, VR::CS, VM::M1, "SOPInstanceStatus" },
{ 0x0029, 0x0039, 0, VR::DT, VM::M1, "SOPAuthorizationDateandTime" },
{ 0x0029, 0x003a, 0, VR::LT, VM::M1, "SOPAuthorizationComment" },
{ 0x0029, 0x003b, 0, VR::LO, VM::M1, "AuthorizationEquipmentCertificationNumber" },
{ 0x0029, 0x003c, 0, VR::UL, VM::M1, "ConcatenationFrameOffsetNumber" },
{ 0x0029, 0x003d, 0, VR::US, VM::M1, "RepresentativeFrameNumber" },
{ 0x0029, 0x003e, 0, VR::UI, VM::M1, "ConcatenationUID" },
{ 0x0029, 0x003f, 0, VR::US, VM::M1, "InConcatenationNumber" },
{ 0x0029, 0x0040, 0, VR::CS, VM::M1, "CardiacSynchronizationTechnique" },
{ 0x0029, 0x0041, 0, VR::CS, VM::M1, "CardiacSignalSource" },
{ 0x0029, 0x0042, 0, VR::FD, VM::M1, "CardiacRRIntervalSpecified" },
{ 0x0029, 0x0043, 0, VR::CS, VM::M1, "CardiacBeatRejectionTechnique" },
{ 0x0029, 0x0044, 0, VR::IS, VM::M1, "LowRRValue" },
{ 0x0029, 0x0045, 0, VR::IS, VM::M1, "HighRRValue" },
{ 0x0029, 0x0046, 0, VR::IS, VM::M1, "IntervalsAcquired" },
{ 0x0029, 0x0047, 0, VR::IS, VM::M1, "IntervalsRejected" },
{ 0x0029, 0x0048, 0, VR::CS, VM::M1, "RespiratoryMotionCompensationTechnique" },
{ 0x0029, 0x0049, 0, VR::CS, VM::M1, "RespiratorySignalSource" },
{ 0x0029, 0x004a, 0, VR::CS, VM::M1, "BulkMotionCompensationTechnique" },
{ 0x0029, 0x004b, 0, VR::CS, VM::M1, "BulkMotionSignalSource" },
{ 0x0029, 0x004c, 0, VR::CS, VM::M1, "PixelPresentation" },
{ 0x0029, 0x004d, 0, VR::CS, VM::M1, "VolumetricProperties" },
{ 0x0029, 0x004e, 0, VR::CS, VM::M1, "VolumeBasedCalculationTechnique" },
{ 0x0029, 0x004f, 0, VR::ST, VM::M1, "AcquisitionContextDescription" },
{ 0x0029, 0x0050, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0051, 0, VR::LO, VM::M1, "LUTDescriptor" },
{ 0x0029, 0x0052, 0, VR::LO, VM::M1, "LUTExplanation" },
{ 0x0029, 0x0053, 0, VR::LO, VM::M1, "LUTData" },
{ 0x0029, 0x0054, 0, VR::CS, VM::M1, "PresentationLUTShape" },
{ 0x0029, 0x0055, 0, VR::SQ, VM::M1, "FrameAnatomySequence" },
{ 0x0029, 0x0056, 0, VR::CS, VM::M1, "FrameLaterality" },
{ 0x0029, 0x0057, 0, VR::SQ, VM::M1, "AnatomicRegionSequence" },
{ 0x0029, 0x0058, 0, VR::SH, VM::M1, "AnatomicRegionCodeValue" },
{ 0x0029, 0x0059, 0, VR::SH, VM::M1, "AnatomicRegionCodingSchemeDesignator" },
{ 0x0029, 0x005a, 0, VR::SH, VM::M1, "AnatomicRegionCodingSchemeVersion" },
{ 0x0029, 0x005b, 0, VR::LO, VM::M1, "AnatomicRegionCodeMeaning" },
{ 0x0029, 0x005c, 0, VR::SQ, VM::M1, "PixelValueTransformationSequence" },
{ 0x0029, 0x005d, 0, VR::LO, VM::M1, "RescaleType" },
{ 0x0029, 0x005e, 0, VR::SQ, VM::M1, "CardiacSynchronizationSequence" },
{ 0x0029, 0x005f, 0, VR::FD, VM::M1, "TriggerDelayTime" },
{ 0x0029, 0x0060, 0, VR::SQ, VM::M1, "FrameVOILUTSequence" },
{ 0x0029, 0x0061, 0, VR::LO, VM::M1, "WindowCenterAndWidthExplanation" },
{ 0x0029, 0x0062, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0063, 0, VR::SQ, VM::M1, "MRModifierSequence" },
{ 0x0029, 0x0064, 0, VR::CS, VM::M1, "ParallelAcquisitionTechnique" },
{ 0x0029, 0x0065, 0, VR::FD, VM::M1, "ParallelReductionFactorSecIn" },
{ 0x0029, 0x0066, 0, VR::CS, VM::M1, "InversionRecovery" },
{ 0x0029, 0x0067, 0, VR::CS, VM::M1, "FlowCompensation" },
{ 0x0029, 0x0068, 0, VR::CS, VM::M1, "FlowCompensationDirection" },
{ 0x0029, 0x0069, 0, VR::CS, VM::M1, "SpatialPreSaturation" },
{ 0x0029, 0x006a, 0, VR::CS, VM::M1, "PartialFourier" },
{ 0x0029, 0x006b, 0, VR::CS, VM::M1, "PartialFourierDirection" },
{ 0x0029, 0x0070, 0, VR::SQ, VM::M1, "MRReceiveCoilSequence" },
{ 0x0029, 0x0071, 0, VR::LO, VM::M1, "ReceiveCoilManufacturerName" },
{ 0x0029, 0x0072, 0, VR::CS, VM::M1, "ReceiveCoilType" },
{ 0x0029, 0x0073, 0, VR::CS, VM::M1, "QuadratureReceiveCoil" },
{ 0x0029, 0x0074, 0, VR::LO, VM::M1, "MultiCoilConfiguration" },
{ 0x0029, 0x0075, 0, VR::CS, VM::M1, "ComplexImageComponent" },
{ 0x0029, 0x0076, 0, VR::SH, VM::M1, "PulseSequenceName" },
{ 0x0029, 0x0077, 0, VR::CS, VM::M1, "EchoPulseSequence" },
{ 0x0029, 0x0078, 0, VR::CS, VM::M1, "MultipleSpinEcho" },
{ 0x0029, 0x0079, 0, VR::CS, VM::M1, "MultiPlanarExcitation" },
{ 0x0029, 0x007a, 0, VR::CS, VM::M1, "PhaseContrast" },
{ 0x0029, 0x007b, 0, VR::CS, VM::M1, "TimeOfFlightContrast" },
{ 0x0029, 0x007c, 0, VR::CS, VM::M1, "SteadyStatePulseSequence" },
{ 0x0029, 0x007d, 0, VR::CS, VM::M1, "EchoPlanarPulseSequence" },
{ 0x0029, 0x007e, 0, VR::CS, VM::M1, "SpectrallySelectedSuppression" },
{ 0x0029, 0x007f, 0, VR::CS, VM::M1, "OversamplingPhase" },
{ 0x0029, 0x0080, 0, VR::CS, VM::M1, "SegmentedKSpaceTraversal" },
{ 0x0029, 0x0081, 0, VR::CS, VM::M1, "CoverageOfKSpace" },
{ 0x0029, 0x0082, 0, VR::SQ, VM::M1, "MRTimingAndRelatedParametersSequence" },
{ 0x0029, 0x0083, 0, VR::US, VM::M1, "RFEchoTrainLength" },
{ 0x0029, 0x0084, 0, VR::US, VM::M1, "GradientEchoTrainLength" },
{ 0x0029, 0x0085, 0, VR::CS, VM::M1, "GradientOutputType" },
{ 0x0029, 0x0086, 0, VR::FD, VM::M1, "GradientOutput" },
{ 0x0029, 0x0087, 0, VR::SQ, VM::M1, "MRFOVGeometrySequence" },
{ 0x0029, 0x0088, 0, VR::US, VM::M1, "MRAcquisitionFrequencyEncodingSteps" },
{ 0x0029, 0x0089, 0, VR::US, VM::M1, "MRAcquisitionPhaseEncodingStepsInPlane" },
{ 0x0029, 0x008a, 0, VR::US, VM::M1, "MRAcquisitionPhaseEncodingStepsOutOfPlane" },
{ 0x0029, 0x008b, 0, VR::SQ, VM::M1, "MRTransmitCoilSequence" },
{ 0x0029, 0x008c, 0, VR::SH, VM::M1, "TransmitCoilName" },
{ 0x0029, 0x008d, 0, VR::LO, VM::M1, "TransmitCoilManufacturerName" },
{ 0x0029, 0x008e, 0, VR::CS, VM::M1, "TransmitCoilType" },
{ 0x0029, 0x008f, 0, VR::SQ, VM::M1, "MREchoSequence" },
{ 0x0029, 0x0090, 0, VR::FD, VM::M1, "EffectiveEchoTime" },
{ 0x0029, 0x0091, 0, VR::SQ, VM::M1, "MRMetaboliteMapSequence" },
{ 0x0029, 0x0092, 0, VR::ST, VM::M1, "MetaboliteMapDescription" },
{ 0x0029, 0x0093, 0, VR::SQ, VM::M1, "MetaboliteMapCodeSequence" },
{ 0x0029, 0x0094, 0, VR::SH, VM::M1, "MetaboliteMapCodeValue" },
{ 0x0029, 0x0095, 0, VR::SH, VM::M1, "MetaboliteMapCodingSchemeDesignator" },
{ 0x0029, 0x0096, 0, VR::SH, VM::M1, "MetaboliteMapCodingSchemeVersion" },
{ 0x0029, 0x0097, 0, VR::LO, VM::M1, "MetaboliteMapCodeMeaning" },
{ 0x0029, 0x0098, 0, VR::SQ, VM::M1, "MRImagingModifierSequence" },
{ 0x0029, 0x0099, 0, VR::CS, VM::M1, "MagnetizationTransfer" },
{ 0x0029, 0x009a, 0, VR::CS, VM::M1, "BloodSignalNulling" },
{ 0x0029, 0x009b, 0, VR::CS, VM::M1, "Tagging" },
{ 0x0029, 0x009c, 0, VR::FD, VM::M1, "TagSpacingFirstDimension" },
{ 0x0029, 0x009d, 0, VR::FD, VM::M1, "TagSpacingSecondDimension" },
{ 0x0029, 0x009e, 0, VR::FD, VM::M1, "TagAngleFirstAxis" },
{ 0x0029, 0x009f, 0, VR::SS, VM::M1, "TagAngleSecondAxis" },
{ 0x0029, 0x00a0, 0, VR::FD, VM::M1, "TagThickness" },
{ 0x0029, 0x00a1, 0, VR::FD, VM::M1, "TaggingDelay" },
{ 0x0029, 0x00a2, 0, VR::FD, VM::M1, "TransmitterFrequency" },
{ 0x0029, 0x00a3, 0, VR::DS, VM::M1, "PixelBandwidth" },
{ 0x0029, 0x00a4, 0, VR::SQ, VM::M1, "MRVelocityEncodingSequence" },
{ 0x0029, 0x00a5, 0, VR::FD, VM::M1, "VelocityEncodingDirection" },
{ 0x0029, 0x00a6, 0, VR::FD, VM::M1, "VelocityEncodingMinimumValue" },
{ 0x0029, 0x00a7, 0, VR::FD, VM::M1, "VelocityEncodingMaximumValue" },
{ 0x0029, 0x00a8, 0, VR::SQ, VM::M1, "MRImageFrameTypeSequence" },
{ 0x0029, 0x00a9, 0, VR::CS, VM::M1, "FrameType" },
{ 0x0029, 0x00aa, 0, VR::CS, VM::M1, "PixelPresentation" },
{ 0x0029, 0x00ab, 0, VR::CS, VM::M1, "VolumetricProperties" },
{ 0x0029, 0x00ac, 0, VR::CS, VM::M1, "VolumeBasedCalculationTechnique" },
{ 0x0029, 0x00ad, 0, VR::IS, VM::M1, "FilmedCount" },
{ 0x0029, 0x00ae, 0, VR::LO, VM::M1, "IsTransferred" },
{ 0x0029, 0x00af, 0, VR::LO, VM::M1, "IsArchived" },
{ 0x0029, 0x00b0, 0, VR::LO, VM::M1, "MPPSStepStatus" },
{ 0x0029, 0x00b1, 0, VR::LO, VM::M1, "CommitmentStatus" },
{ 0x0029, 0x00b2, 0, VR::LO, VM::M1, "IsStorageCommitted" },
{ 0x0029, 0x00b3, 0, VR::LO, VM::M1, "IsDicom" },
{ 0x0029, 0x00b4, 0, VR::LO, VM::M1, "IsAllowCascadeSave" },
{ 0x0029, 0x00b5, 0, VR::LO, VM::M1, "IsAllowCascadeProtect" },
{ 0x0029, 0x00b6, 0, VR::LO, VM::M1, "IsDeleted" },
{ 0x0029, 0x00b7, 0, VR::OB, VM::M1, "ApplicationData" },
{ 0x0029, 0x00b8, 0, VR::LO, VM::M1, "IsAllowCascadeSave" },
{ 0x0029, 0x00b9, 0, VR::LO, VM::M1, "IsAllowCascadeProtect" },
{ 0x0029, 0x00ba, 0, VR::LO, VM::M1, "IsDeleted" },
{ 0x0029, 0x00bb, 0, VR::IS, VM::M1, "VOI1" },
{ 0x0029, 0x00bc, 0, VR::IS, VM::M1, "VOI2" },
{ 0x0029, 0x00bd, 0, VR::DS, VM::M1, "MixingTime" },
{ 0x0029, 0x00be, 0, VR::FD, VM::M1, "SelectiveIRPosition" },
{ 0x0029, 0x00bf, 0, VR::FD, VM::M1, "SelectiveIRRow" },
{ 0x0029, 0x00c0, 0, VR::FD, VM::M1, "SelectiveIRColumn" },
{ 0x0029, 0x00c1, 0, VR::FD, VM::M1, "SelectiveIROrientation" },
{ 0x0029, 0x00c2, 0, VR::DS, VM::M1, "SelectiveIRThickness" },
{ 0x0029, 0x00c3, 0, VR::CS, VM::M1, "RephaseOrderSlice" },
{ 0x0029, 0x00c4, 0, VR::CS, VM::M1, "RephaseOrderPhase" },
{ 0x0029, 0x00c5, 0, VR::CS, VM::M1, "RephaseOrderFreq" },
{ 0x0029, 0x00d0, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x00d3, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x00d5, 0, VR::UI, VM::M1, "" },
{ 0x0029, 0x00d6, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x00d7, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict291TagHashTable[] = {
   63,    74,    87,   102,   113,   126,   139,   144,   153,   164,
  173,   184,   195,   204,   213,   222,   231,   242,   251,   264,
  277,   290,   303,   316,   329,   340,   347,   358,   369,   380,
  391,   402,   411,   420,   429,   436,   443,   450,   457,   464,
  471,   478,   483,   490,   497,   504,   511,   518,   527,   534,
  543,   548,   553,   562,   571,   578,   585,   592,   599,   606,
  613,   620,     0,     5,    51,    25,    78,    23,    93,    41,
  136,    84,   193,   145,     6,    50,    24,    77,    22,    92,
   40,   137,    85,   192,   144,   247,   211,     7,     3,    72,
   53,    27,    95,    43,   138,    86,   156,   104,   199,   151,
  246,   208,     5,    52,    26,    94,    42,   139,    87,   157,
  105,   198,   150,     6,    55,    29,    97,    45,   158,   106,
  197,   149,   219,   171,   249,   214,     6,    54,    28,    96,
   44,   159,   107,   196,   148,   218,   170,   250,   215,     2,
   99,    47,   217,   169,     4,    56,    30,    98,    46,   216,
  168,   248,   213,     5,     0,     1,     4,    78,    43,    17,
   85,    33,   223,   175,     4,     5,    79,    42,    16,    84,
   32,   222,   174,     5,     2,     3,    45,    19,    87,    35,
  148,    96,   221,   173,     5,     1,     2,    44,    18,    86,
   34,   149,    97,   220,   172,     4,    47,    21,    89,    37,
  150,    98,   211,   163,     4,    46,    20,    88,    36,   151,
   99,   210,   162,     4,    49,    23,    91,    39,   152,   100,
  209,   161,     4,    48,    22,    90,    38,   153,   101,   208,
  160,     5,    21,     1,    35,     9,   109,    57,   154,   102,
  215,   167,     4,    34,     8,   108,    56,   155,   103,   214,
  166,     6,    14,    88,    23,     3,    37,    11,   111,    59,
  168,   120,   213,   165,     6,    15,    89,    22,     2,    36,
   10,   110,    58,   169,   121,   212,   164,     6,    16,    90,
   25,     5,    39,    13,   113,    61,   170,   122,   235,   187,
    6,    17,    91,    24,     4,    38,    12,   112,    60,   171,
  123,   234,   186,     6,    18,    92,    27,     7,    41,    15,
  115,    63,   172,   124,   233,   185,     6,    19,    93,    26,
    6,    40,    14,   114,    62,   173,   125,   232,   184,     5,
   20,    94,    28,     1,   101,    49,   174,   126,   239,   191,
    3,   100,    48,   175,   127,   238,   190,     5,     6,    80,
   30,     3,   103,    51,   160,   112,   237,   189,     5,     7,
   81,    29,     2,   102,    50,   161,   113,   236,   188,     5,
    8,    82,    32,     5,   105,    53,   162,   114,   227,   179,
    5,     9,    83,    31,     4,   104,    52,   163,   115,   226,
  178,     5,    10,    84,    33,     7,   107,    55,   164,   116,
  225,   177,     4,    11,    85,   106,    54,   165,   117,   224,
  176,     4,    12,    86,    64,     9,   166,   118,   231,   183,
    4,    13,    87,    63,     8,   167,   119,   230,   182,     3,
   66,    11,   124,    72,   229,   181,     3,    65,    10,   125,
   73,   228,   180,     3,    68,    13,   126,    74,   187,   139,
    3,    67,    12,   127,    75,   186,   138,     3,    70,    15,
  128,    76,   185,   137,     3,    69,    14,   129,    77,   184,
  136,     3,    57,     1,   130,    78,   191,   143,     2,   131,
   79,   190,   142,     3,    59,     3,   116,    64,   189,   141,
    3,    58,     2,   117,    65,   188,   140,     3,    61,     5,
  118,    66,   179,   131,     3,    60,     4,   119,    67,   178,
  130,     3,   120,    68,   177,   129,   242,   194,     4,    62,
    6,   121,    69,   176,   128,   243,   195,     3,   122,    70,
  183,   135,   240,   192,     4,    79,    24,   123,    71,   182,
  134,   241,   193,     2,   140,    88,   181,   133,     2,   141,
   89,   180,   132,     4,    81,    29,   142,    90,   203,   155,
  244,   196,     4,    80,    28,   143,    91,   202,   154,   245,
  197,     3,    83,    31,   144,    92,   201,   153,     3,    82,
   30,   145,    93,   200,   152,     3,    72,    17,   146,    94,
  207,   159,     3,    71,    16,   147,    95,   206,   158,     3,
   74,    19,   132,    80,   205,   157,     3,    73,    18,   133,
   81,   204,   156,     3,    76,    21,   134,    82,   195,   147,
    3,    75,    20,   135,    83,   194,   146,
};

vtkDICOMDictionary::Dict Dict291Data = {
"MMCPrivate",
62,
251,
Dict291TagHashTable,
Dict291Contents
};

// ----- IDEXX -----

DictEntry Dict292Contents[] = {
{ 0x0011, 0x0000, 0, VR::LO, VM::M1, "BreedName" },
{ 0x0011, 0x0001, 0, VR::LO, VM::M1, "SpeciesName" },
{ 0x0011, 0x0002, 0, VR::PN, VM::M1, "Owner" },
};

unsigned short Dict292TagHashTable[] = {
    2,     0,     3,     0,     0,     1,     1,     2,     2,
};

vtkDICOMDictionary::Dict Dict292Data = {
"IDEXX",
1,
3,
Dict292TagHashTable,
Dict292Contents
};

// ----- VEPRO DICOM TRANSFER 1.0 -----

DictEntry Dict293Contents[] = {
{ 0x0059, 0x0010, 0, VR::SQ, VM::M1, "DicomTransferInfo" },
};

unsigned short Dict293TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict293Data = {
"VEPRO DICOM TRANSFER 1.0",
1,
1,
Dict293TagHashTable,
Dict293Contents
};

// ----- SPI-P Release 1 -----

DictEntry Dict294Contents[] = {
{ 0x0009, 0x0000, 0, VR::LT, VM::M1, "DataObjectRecognitionCode" },
{ 0x0009, 0x0004, 0, VR::LO, VM::M1, "ImageDataConsistency" },
{ 0x0009, 0x0008, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0012, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0015, 0, VR::LO, VM::M1, "UniqueIdentifier" },
{ 0x0009, 0x0016, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0018, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0021, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x0031, 0, VR::LT, VM::M1, "PACSUniqueIdentifier" },
{ 0x0009, 0x0034, 0, VR::LT, VM::M1, "ClusterUniqueIdentifier" },
{ 0x0009, 0x0038, 0, VR::LT, VM::M1, "SystemUniqueIdentifier" },
{ 0x0009, 0x0039, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x0051, 0, VR::LT, VM::M1, "StudyUniqueIdentifier" },
{ 0x0009, 0x0061, 0, VR::LT, VM::M1, "SeriesUniqueIdentifier" },
{ 0x0009, 0x0091, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x00a0, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x00f2, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x00f3, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x00f4, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x00f5, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x00f7, 0, VR::LT, VM::M1, "" },
{ 0x0011, 0x0010, 0, VR::LT, VM::M1, "PatientEntryID" },
{ 0x0011, 0x0020, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0021, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0022, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0030, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0031, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0032, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0010, 0, VR::US, VM::M1, "MainsFrequency" },
{ 0x0019, 0x0025, 0, VR::LO, VM::M1TN, "OriginalPixelDataQuality" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "ECGTriggering" },
{ 0x0019, 0x0031, 0, VR::UN, VM::M1, "ECG1Offset" },
{ 0x0019, 0x0032, 0, VR::UN, VM::M1, "ECG2Offset1" },
{ 0x0019, 0x0033, 0, VR::UN, VM::M1, "ECG2Offset2" },
{ 0x0019, 0x0050, 0, VR::US, VM::M1, "VideoScanMode" },
{ 0x0019, 0x0051, 0, VR::US, VM::M1, "VideoLineRate" },
{ 0x0019, 0x0060, 0, VR::US, VM::M1, "XrayTechnique" },
{ 0x0019, 0x0061, 0, VR::DS, VM::M1, "ImageIdentifierFromat" },
{ 0x0019, 0x0062, 0, VR::US, VM::M1, "IrisDiaphragm" },
{ 0x0019, 0x0063, 0, VR::CS, VM::M1, "Filter" },
{ 0x0019, 0x0064, 0, VR::CS, VM::M1, "CineParallel" },
{ 0x0019, 0x0065, 0, VR::CS, VM::M1, "CineMaster" },
{ 0x0019, 0x0070, 0, VR::US, VM::M1, "ExposureChannel" },
{ 0x0019, 0x0071, 0, VR::UN, VM::M1, "ExposureChannelFirstImage" },
{ 0x0019, 0x0072, 0, VR::US, VM::M1, "ProcessingChannel" },
{ 0x0019, 0x0080, 0, VR::DS, VM::M1, "AcquisitionDelay" },
{ 0x0019, 0x0081, 0, VR::UN, VM::M1, "RelativeImageTime" },
{ 0x0019, 0x0090, 0, VR::CS, VM::M1, "VideoWhiteCompression" },
{ 0x0019, 0x00a0, 0, VR::US, VM::M1, "Angulation" },
{ 0x0019, 0x00a1, 0, VR::US, VM::M1, "Rotation" },
{ 0x0021, 0x0012, 0, VR::LT, VM::M1, "SeriesUniqueIdentifier" },
{ 0x0021, 0x0014, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0000, 0, VR::DS, VM::M4, "" },
{ 0x0029, 0x0020, 0, VR::DS, VM::M1, "PixelAspectRatio" },
{ 0x0029, 0x0025, 0, VR::LO, VM::M1TN, "ProcessedPixelDataQuality" },
{ 0x0029, 0x0030, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0038, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0060, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0061, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0067, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0070, 0, VR::LT, VM::M1, "WindowID" },
{ 0x0029, 0x0071, 0, VR::CS, VM::M1, "VideoInvertSubtracted" },
{ 0x0029, 0x0072, 0, VR::CS, VM::M1, "VideoInvertNonsubtracted" },
{ 0x0029, 0x0077, 0, VR::CS, VM::M1, "WindowSelectStatus" },
{ 0x0029, 0x0078, 0, VR::LT, VM::M1, "ECGDisplayPrintingID" },
{ 0x0029, 0x0079, 0, VR::CS, VM::M1, "ECGDisplayPrinting" },
{ 0x0029, 0x007e, 0, VR::CS, VM::M1, "ECGDisplayPrintingEnableStatus" },
{ 0x0029, 0x007f, 0, VR::CS, VM::M1, "ECGDisplayPrintingSelectStatus" },
{ 0x0029, 0x0080, 0, VR::LT, VM::M1, "PhysiologicalDisplayID" },
{ 0x0029, 0x0081, 0, VR::US, VM::M1, "PreferredPhysiologicalChannelDisplay" },
{ 0x0029, 0x008e, 0, VR::CS, VM::M1, "PhysiologicalDisplayEnableStatus" },
{ 0x0029, 0x008f, 0, VR::CS, VM::M1, "PhysiologicalDisplaySelectStatus" },
{ 0x0029, 0x0090, 0, VR::DS, VM::M1TN, "" },
{ 0x0029, 0x0091, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x009f, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x00a0, 0, VR::DS, VM::M1TN, "" },
{ 0x0029, 0x00a1, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x00af, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x00b0, 0, VR::DS, VM::M1TN, "" },
{ 0x0029, 0x00b1, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x00bf, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x00c0, 0, VR::LT, VM::M1, "FunctionalShutterID" },
{ 0x0029, 0x00c1, 0, VR::US, VM::M1, "FieldOfShutter" },
{ 0x0029, 0x00c5, 0, VR::LT, VM::M1, "FieldOfShutterRectangle" },
{ 0x0029, 0x00ce, 0, VR::CS, VM::M1, "ShutterEnableStatus" },
{ 0x0029, 0x00cf, 0, VR::CS, VM::M1, "ShutterSelectStatus" },
{ 0x7FE1, 0x0010, 0, VR::OW, VM::M1, "PixelData" },
};

unsigned short Dict294TagHashTable[] = {
   23,    34,    47,    52,    59,    66,    75,    86,   103,   106,
  119,   130,   143,   152,   163,   170,   177,   186,   201,   210,
  217,   222,     0,     5,    15,   145,    50,   129,    64,   112,
   81,   175,    83,   177,     6,     2,     8,    13,    81,    22,
   16,    49,   128,    65,   113,    82,   176,     2,    30,     1,
   66,   114,     3,     3,    16,    29,     0,    59,    48,     3,
   12,    57,    24,    33,    78,   159,     4,     4,    18,    11,
   56,    23,    32,    31,     2,     5,     5,    21,    17,   242,
   38,    80,    61,    96,    80,   161,     8,    18,   243,    25,
   34,    39,    81,    51,   144,    54,    18,    62,    97,    67,
  119,    79,   160,     1,    88,   206,     6,     0,     0,     6,
   22,    32,    16,    55,    20,    57,    32,    89,   207,     5,
   27,    49,    40,    96,    53,   161,    75,   143,    77,   145,
    6,    21,   247,    26,    48,    41,    97,    52,   160,    74,
  142,    76,   144,     4,     9,    49,    19,   244,    42,    98,
   58,    37,     5,     1,     4,    20,   245,    28,    50,    43,
   99,    63,   103,     3,    44,   100,    68,   120,    85,   192,
    3,    45,   101,    69,   121,    86,   193,     4,    33,    37,
   46,   112,    73,   129,    84,   191,     7,     7,    24,    10,
   52,    14,    97,    16,   160,    47,   113,    60,    56,    72,
  128,     4,     8,    33,    35,    49,    48,   114,    90,    16,
    3,    34,    48,    56,     0,    87,   197,     2,    37,    51,
   70,   126,     2,    36,    50,    71,   127,
};

vtkDICOMDictionary::Dict Dict294Data = {
"SPI-P Release 1",
22,
91,
Dict294TagHashTable,
Dict294Contents
};

// ----- Philips EV Imaging DD 022 -----

DictEntry Dict295Contents[] = {
{ 0x2007, 0x0000, 0, VR::ST, VM::M1, "" },
};

unsigned short Dict295TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict295Data = {
"Philips EV Imaging DD 022",
1,
1,
Dict295TagHashTable,
Dict295Contents
};

// ----- TOSHIBA ENCRYPTED SR DATA -----

DictEntry Dict296Contents[] = {
{ 0x7015, 0x0000, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict296TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict296Data = {
"TOSHIBA ENCRYPTED SR DATA",
1,
1,
Dict296TagHashTable,
Dict296Contents
};

// ----- SECTRA_OverlayInfo_01 -----

DictEntry Dict297Contents[] = {
{ 0x6001, 0x0001, 0, VR::LO, VM::M1, "SectraOverlay" },
};

unsigned short Dict297TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict297Data = {
"SECTRA_OverlayInfo_01",
1,
1,
Dict297TagHashTable,
Dict297Contents
};

// ----- SIEMENS CSA ENVELOPE -----

DictEntry Dict298Contents[] = {
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "syngoReportData" },
{ 0x0029, 0x0011, 0, VR::OB, VM::M1, "syngoReportPresentation" },
};

unsigned short Dict298TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    17,
};

vtkDICOMDictionary::Dict Dict298Data = {
"SIEMENS CSA ENVELOPE",
1,
2,
Dict298TagHashTable,
Dict298Contents
};

// ----- SIEMENS RA PLANE A -----

DictEntry Dict299Contents[] = {
{ 0x0011, 0x0028, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0029, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x002a, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x002b, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x002c, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0015, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x0018, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x0019, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001a, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001b, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001c, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001d, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001e, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001f, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0022, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0024, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002a, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x002c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0034, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0036, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0038, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0042, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0046, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0048, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x004a, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x004c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x004e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0054, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0056, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0058, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005c, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x005e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0062, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0064, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0066, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0068, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x006a, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x006c, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x006e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0070, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0072, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0074, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0076, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x007a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0084, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0086, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0088, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0090, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0092, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0094, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0096, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0098, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x009a, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x009c, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x009e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00a0, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x00a2, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x00a4, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a6, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a8, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00aa, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ac, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ae, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00b0, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b1, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b2, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b3, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b4, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b5, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b6, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b7, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b8, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b9, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00bb, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00bc, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00bd, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00be, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00bf, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c0, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c1, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c2, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c3, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c4, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c5, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c6, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c7, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c8, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c9, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00ca, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cb, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cc, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cd, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00ce, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cf, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00d1, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00d2, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d3, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d4, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d5, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d6, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d7, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d8, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d9, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00da, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00db, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00dc, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00dd, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00de, 0, VR::UL, VM::M1TN, "" },
{ 0x0019, 0x00df, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00e0, 0, VR::UL, VM::M1, "" },
};

unsigned short Dict299TagHashTable[] = {
   34,    45,    56,    67,    78,    87,    98,   109,   120,   129,
  138,   147,   154,   165,   172,   181,   188,   197,   204,   213,
  222,   231,   238,   247,   256,   267,   276,   285,   292,   303,
  306,   317,   324,     0,     5,     7,    25,    26,    56,    43,
   90,    99,   190,   128,   220,     5,     6,    24,    60,   124,
   77,   158,    98,   189,   129,   221,     5,     9,    27,    27,
   58,    44,    92,    97,   188,   118,   210,     5,     8,    26,
   61,   126,    76,   156,    89,   179,   119,   211,     4,    11,
   29,    28,    60,    45,    94,    88,   178,     5,    10,    28,
   54,   112,    71,   146,    87,   177,   117,   209,     5,    13,
   31,    29,    62,    38,    80,    86,   176,   122,   214,     5,
   12,    30,    55,   114,    70,   144,    93,   183,   123,   215,
    4,    22,    48,    39,    82,    92,   182,   120,   212,     4,
   56,   116,    73,   150,    91,   181,   121,   213,     4,    23,
   50,    40,    84,    90,   180,   111,   202,     3,    57,   118,
   72,   148,   112,   203,     5,     5,    21,    24,    52,    41,
   86,    83,   170,   109,   200,     3,    50,   104,    67,   138,
  110,   201,     4,    25,    54,    34,    72,    82,   168,   115,
  206,     3,    51,   106,    66,   136,   116,   207,     4,    18,
   40,    35,    74,    85,   174,   113,   204,     3,    52,   108,
   69,   142,   114,   205,     4,    19,    42,    36,    76,    84,
  172,   103,   194,     4,    53,   110,    68,   140,   104,   195,
  132,   224,     4,    20,    44,    37,    78,    79,   162,   101,
  192,     3,    46,    96,    63,   130,   102,   193,     4,    21,
   46,    30,    64,    78,   160,   107,   198,     4,     1,    41,
   47,    98,    62,   128,   108,   199,     5,     0,    40,    14,
   32,    31,    66,    81,   166,   105,   196,     4,     3,    43,
   48,   100,    65,   134,   106,   197,     4,     2,    42,    15,
   34,    32,    68,    80,   164,     3,    49,   102,    64,   132,
  126,   218,     5,     4,    44,    16,    36,    33,    70,    96,
  187,   127,   219,     1,   124,   216,     5,    17,    38,    58,
  120,    75,   154,    95,   185,   125,   217,     3,    42,    88,
   94,   184,   130,   222,     4,    59,   122,    74,   152,   100,
  191,   131,   223,
};

vtkDICOMDictionary::Dict Dict299Data = {
"SIEMENS RA PLANE A",
33,
133,
Dict299TagHashTable,
Dict299Contents
};

// ----- SIEMENS RA PLANE B -----

DictEntry Dict300Contents[] = {
{ 0x0011, 0x0028, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0029, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x002a, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x002b, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x002c, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0015, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x0018, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x0019, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001a, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001b, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001c, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001d, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001e, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x001f, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0022, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0024, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0028, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002a, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x002c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x002e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0034, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0036, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0038, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x003e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0042, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0044, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0046, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0048, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x004a, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x004c, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x004e, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0050, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0054, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0056, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0058, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005c, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x005e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0062, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0064, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0066, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0068, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x006a, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x006c, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x006e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0070, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0072, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0074, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0076, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x007a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0084, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0086, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0088, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x008e, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0090, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0092, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0094, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0096, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0098, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x009a, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x009c, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x009e, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00a0, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x00a2, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x00a4, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a6, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00a8, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00aa, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ac, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ae, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00b0, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b1, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b2, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b3, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b4, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b5, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b6, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b7, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b8, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00b9, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00bb, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00bc, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00bd, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00be, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00bf, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c0, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c1, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c2, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c3, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c4, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c5, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c6, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c7, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c8, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00c9, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00ca, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cb, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cc, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cd, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00ce, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00cf, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00d1, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00d2, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d3, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d4, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d5, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d6, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d7, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d8, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00d9, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00da, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00db, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00dc, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00dd, 0, VR::UL, VM::M1, "" },
{ 0x0019, 0x00de, 0, VR::UL, VM::M1TN, "" },
{ 0x0019, 0x00df, 0, VR::OB, VM::M1, "" },
{ 0x0019, 0x00e0, 0, VR::UL, VM::M1, "" },
};

unsigned short Dict300TagHashTable[] = {
   34,    45,    56,    67,    78,    87,    98,   109,   120,   129,
  138,   147,   154,   165,   172,   181,   188,   197,   204,   213,
  222,   231,   238,   247,   256,   267,   276,   285,   292,   303,
  306,   317,   324,     0,     5,     7,    25,    26,    56,    43,
   90,    99,   190,   128,   220,     5,     6,    24,    60,   124,
   77,   158,    98,   189,   129,   221,     5,     9,    27,    27,
   58,    44,    92,    97,   188,   118,   210,     5,     8,    26,
   61,   126,    76,   156,    89,   179,   119,   211,     4,    11,
   29,    28,    60,    45,    94,    88,   178,     5,    10,    28,
   54,   112,    71,   146,    87,   177,   117,   209,     5,    13,
   31,    29,    62,    38,    80,    86,   176,   122,   214,     5,
   12,    30,    55,   114,    70,   144,    93,   183,   123,   215,
    4,    22,    48,    39,    82,    92,   182,   120,   212,     4,
   56,   116,    73,   150,    91,   181,   121,   213,     4,    23,
   50,    40,    84,    90,   180,   111,   202,     3,    57,   118,
   72,   148,   112,   203,     5,     5,    21,    24,    52,    41,
   86,    83,   170,   109,   200,     3,    50,   104,    67,   138,
  110,   201,     4,    25,    54,    34,    72,    82,   168,   115,
  206,     3,    51,   106,    66,   136,   116,   207,     4,    18,
   40,    35,    74,    85,   174,   113,   204,     3,    52,   108,
   69,   142,   114,   205,     4,    19,    42,    36,    76,    84,
  172,   103,   194,     4,    53,   110,    68,   140,   104,   195,
  132,   224,     4,    20,    44,    37,    78,    79,   162,   101,
  192,     3,    46,    96,    63,   130,   102,   193,     4,    21,
   46,    30,    64,    78,   160,   107,   198,     4,     1,    41,
   47,    98,    62,   128,   108,   199,     5,     0,    40,    14,
   32,    31,    66,    81,   166,   105,   196,     4,     3,    43,
   48,   100,    65,   134,   106,   197,     4,     2,    42,    15,
   34,    32,    68,    80,   164,     3,    49,   102,    64,   132,
  126,   218,     5,     4,    44,    16,    36,    33,    70,    96,
  187,   127,   219,     1,   124,   216,     5,    17,    38,    58,
  120,    75,   154,    95,   185,   125,   217,     3,    42,    88,
   94,   184,   130,   222,     4,    59,   122,    74,   152,   100,
  191,   131,   223,
};

vtkDICOMDictionary::Dict Dict300Data = {
"SIEMENS RA PLANE B",
33,
133,
Dict300TagHashTable,
Dict300Contents
};

// ----- Silhouette V1.0 -----

DictEntry Dict301Contents[] = {
{ 0x0029, 0x0013, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0014, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x0017, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0018, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0019, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x001a, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x001b, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x001c, 0, VR::UL, VM::M1, "" },
{ 0x0029, 0x001d, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x001e, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0021, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0022, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0023, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0024, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0025, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0027, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0028, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0029, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0030, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0031, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0046, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0047, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0052, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0053, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0054, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0055, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0056, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0057, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0073, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0074, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0077, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0078, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0088, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0089, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0090, 0, VR::UN, VM::M1, "" },
{ 0x0029, 0x0091, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict301TagHashTable[] = {
   10,    17,    30,    37,    44,    51,    60,    69,    80,     0,
    3,    17,    41,    26,    86,    33,   137,     6,     9,    30,
   12,    35,    16,    40,    27,    87,    28,   115,    32,   136,
    3,    11,    34,    20,    70,    29,   116,     3,     4,    25,
   14,    37,    21,    71,     3,     0,    19,     3,    24,    13,
   36,     4,     6,    27,    15,    39,    22,    82,    30,   119,
    4,     5,    26,    19,    49,    23,    83,    35,   145,     5,
    1,    20,     8,    29,    18,    48,    24,    84,    34,   144,
    5,     2,    23,     7,    28,    10,    33,    25,    85,    31,
  120,
};

vtkDICOMDictionary::Dict Dict301Data = {
"Silhouette V1.0",
9,
36,
Dict301TagHashTable,
Dict301Contents
};

// ----- GEMS_STDY_01 -----

DictEntry Dict302Contents[] = {
{ 0x0023, 0x0001, 0, VR::SL, VM::M1, "NumberOfSeriesInStudy" },
{ 0x0023, 0x0002, 0, VR::SL, VM::M1, "NumberOfUnarchivedSeries" },
{ 0x0023, 0x0010, 0, VR::SS, VM::M1, "ReferenceImageField" },
{ 0x0023, 0x0050, 0, VR::SS, VM::M1, "SummaryImage" },
{ 0x0023, 0x0070, 0, VR::FD, VM::M1, "StartTimeSecsInFirstAxial" },
{ 0x0023, 0x0074, 0, VR::SL, VM::M1, "NumberOfUpdatesToHeader" },
{ 0x0023, 0x007d, 0, VR::SS, VM::M1, "IndicatesIfStudyHasCompleteInfo" },
{ 0x0023, 0x0080, 0, VR::SQ, VM::M1, "HasMPPSRelatedTags" },
};

unsigned short Dict302TagHashTable[] = {
    3,    12,     0,     4,     0,     1,     3,    80,     4,   112,
    5,   116,     4,     1,     2,     2,    16,     6,   125,     7,
  128,
};

vtkDICOMDictionary::Dict Dict302Data = {
"GEMS_STDY_01",
2,
8,
Dict302TagHashTable,
Dict302Contents
};

// ----- TOSHIBA COMAPL HEADER -----

DictEntry Dict303Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "COMAPLHeaderType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "COMAPLHeaderVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "COMAPLHeaderInfo" },
{ 0x0029, 0x0020, 0, VR::OB, VM::M1, "COMAPLHistoryInformation" },
{ 0x0029, 0x0031, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0034, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict303TagHashTable[] = {
    2,     0,     6,     0,     8,     1,     9,     2,    16,     3,
   32,     4,    49,     5,    52,
};

vtkDICOMDictionary::Dict Dict303Data = {
"TOSHIBA COMAPL HEADER",
1,
6,
Dict303TagHashTable,
Dict303Contents
};

// ----- SIEMENS CT VA0  GEN -----

DictEntry Dict304Contents[] = {
{ 0x0019, 0x0010, 0, VR::DS, VM::M1, "SourceSideCollimatorAperture" },
{ 0x0019, 0x0011, 0, VR::DS, VM::M1, "DetectorSideCollimatorAperture" },
{ 0x0019, 0x0020, 0, VR::IS, VM::M1, "ExposureTime" },
{ 0x0019, 0x0021, 0, VR::IS, VM::M1, "ExposureCurrent" },
{ 0x0019, 0x0025, 0, VR::DS, VM::M1, "KVPGeneratorPowerCurrent" },
{ 0x0019, 0x0026, 0, VR::DS, VM::M1, "GeneratorVoltage" },
{ 0x0019, 0x0040, 0, VR::UL, VM::M1, "MasterControlMask" },
{ 0x0019, 0x0042, 0, VR::US, VM::M5, "ProcessingMask" },
{ 0x0019, 0x0044, 0, VR::UL, VM::M1TN, "" },
{ 0x0019, 0x0045, 0, VR::UL, VM::M1TN, "" },
{ 0x0019, 0x0062, 0, VR::IS, VM::M1, "NumberOfVirtuellChannels" },
{ 0x0019, 0x0070, 0, VR::IS, VM::M1, "NumberOfReadings" },
{ 0x0019, 0x0071, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x0074, 0, VR::IS, VM::M1, "NumberOfProjections" },
{ 0x0019, 0x0075, 0, VR::IS, VM::M1, "NumberOfBytes" },
{ 0x0019, 0x0080, 0, VR::LO, VM::M1, "ReconstructionAlgorithmSet" },
{ 0x0019, 0x0081, 0, VR::LO, VM::M1, "ReconstructionAlgorithmIndex" },
{ 0x0019, 0x0082, 0, VR::LO, VM::M1, "RegenerationSoftwareVersion" },
{ 0x0019, 0x0088, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0010, 0, VR::IS, VM::M1, "RotationAngle" },
{ 0x0021, 0x0011, 0, VR::IS, VM::M1, "StartAngle" },
{ 0x0021, 0x0020, 0, VR::IS, VM::M1TN, "" },
{ 0x0021, 0x0030, 0, VR::IS, VM::M1, "TopogramTubePosition" },
{ 0x0021, 0x0032, 0, VR::DS, VM::M1, "LengthOfTopogram" },
{ 0x0021, 0x0034, 0, VR::DS, VM::M1, "TopogramCorrectionFactor" },
{ 0x0021, 0x0036, 0, VR::DS, VM::M1, "MaximumTablePosition" },
{ 0x0021, 0x0040, 0, VR::IS, VM::M1, "TableMoveDirectionCode" },
{ 0x0021, 0x0045, 0, VR::IS, VM::M1, "VOIStartRow" },
{ 0x0021, 0x0046, 0, VR::IS, VM::M1, "VOIStopRow" },
{ 0x0021, 0x0047, 0, VR::IS, VM::M1, "VOIStartColumn" },
{ 0x0021, 0x0048, 0, VR::IS, VM::M1, "VOIStopColumn" },
{ 0x0021, 0x0049, 0, VR::IS, VM::M1, "VOIStartSlice" },
{ 0x0021, 0x004a, 0, VR::IS, VM::M1, "VOIStopSlice" },
{ 0x0021, 0x0050, 0, VR::IS, VM::M1, "VectorStartRow" },
{ 0x0021, 0x0051, 0, VR::IS, VM::M1, "VectorRowStep" },
{ 0x0021, 0x0052, 0, VR::IS, VM::M1, "VectorStartColumn" },
{ 0x0021, 0x0053, 0, VR::IS, VM::M1, "VectorColumnStep" },
{ 0x0021, 0x0060, 0, VR::IS, VM::M1, "RangeTypeCode" },
{ 0x0021, 0x0062, 0, VR::IS, VM::M1, "ReferenceTypeCode" },
{ 0x0021, 0x0070, 0, VR::DS, VM::M3, "ObjectOrientation" },
{ 0x0021, 0x0072, 0, VR::DS, VM::M3, "LightOrientation" },
{ 0x0021, 0x0075, 0, VR::DS, VM::M1, "LightBrightness" },
{ 0x0021, 0x0076, 0, VR::DS, VM::M1, "LightContrast" },
{ 0x0021, 0x007a, 0, VR::IS, VM::M2, "OverlayThreshold" },
{ 0x0021, 0x007b, 0, VR::IS, VM::M2, "SurfaceThreshold" },
{ 0x0021, 0x007c, 0, VR::IS, VM::M2, "GreyScaleThreshold" },
{ 0x0021, 0x00a0, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x00a2, 0, VR::CS, VM::M1, "" },
{ 0x0021, 0x00a7, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict304TagHashTable[] = {
   13,    24,    33,    38,    43,    50,    57,    68,    77,    92,
  109,   116,     0,     5,     4,    37,    13,   116,    20,    17,
   26,    64,    48,   167,     4,    14,   117,    19,    16,    21,
   32,    41,   117,     2,    10,    98,    42,   118,     2,     5,
   38,    18,   136,     3,     6,    64,    33,    80,    37,    96,
    3,    22,    48,    27,    69,    34,    81,     5,     7,    66,
   28,    70,    35,    82,    38,    98,    43,   122,     4,    23,
   50,    29,    71,    36,    83,    44,   123,     7,     1,    17,
    3,    33,     8,    68,    11,   112,    30,    72,    39,   112,
   45,   124,     8,     0,    16,     2,    32,     9,    69,    12,
  113,    17,   130,    24,    52,    31,    73,    47,   162,     3,
   16,   129,    32,    74,    40,   114,     3,    15,   128,    25,
   54,    46,   160,
};

vtkDICOMDictionary::Dict Dict304Data = {
"SIEMENS CT VA0  GEN",
12,
49,
Dict304TagHashTable,
Dict304Contents
};

// ----- PHILIPS IMAGING DD 001 -----

DictEntry Dict305Contents[] = {
{ 0x2001, 0x0001, 0, VR::FL, VM::M1, "ChemicalShift" },
{ 0x2001, 0x0002, 0, VR::IS, VM::M1, "ChemicalShiftNumberMR" },
{ 0x2001, 0x0003, 0, VR::FL, VM::M1, "DiffusionBFactor" },
{ 0x2001, 0x0004, 0, VR::CS, VM::M1, "DiffusionDirection" },
{ 0x2001, 0x0005, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x0006, 0, VR::CS, VM::M1, "ImageEnhanced" },
{ 0x2001, 0x0007, 0, VR::CS, VM::M1, "ImageTypeEDES" },
{ 0x2001, 0x0008, 0, VR::IS, VM::M1, "PhaseNumber" },
{ 0x2001, 0x0009, 0, VR::FL, VM::M1, "ImagePrepulseDelay" },
{ 0x2001, 0x000a, 0, VR::IS, VM::M1, "SliceNumberMR" },
{ 0x2001, 0x000b, 0, VR::CS, VM::M1, "SliceOrientation" },
{ 0x2001, 0x000c, 0, VR::CS, VM::M1, "ArrhythmiaRejection" },
{ 0x2001, 0x000e, 0, VR::CS, VM::M1, "CardiacCycled" },
{ 0x2001, 0x000f, 0, VR::SS, VM::M1, "CardiacGateWidth" },
{ 0x2001, 0x0010, 0, VR::CS, VM::M1, "CardiacSync" },
{ 0x2001, 0x0011, 0, VR::FL, VM::M1, "DiffusionEchoTime" },
{ 0x2001, 0x0012, 0, VR::CS, VM::M1, "DynamicSeries" },
{ 0x2001, 0x0013, 0, VR::SL, VM::M1, "EPIFactor" },
{ 0x2001, 0x0014, 0, VR::SL, VM::M1, "NumberOfEchoes" },
{ 0x2001, 0x0015, 0, VR::SS, VM::M1, "NumberOfLocations" },
{ 0x2001, 0x0016, 0, VR::SS, VM::M1, "NumberOfPCDirections" },
{ 0x2001, 0x0017, 0, VR::SL, VM::M1, "NumberOfPhasesMR" },
{ 0x2001, 0x0018, 0, VR::SL, VM::M1, "NumberOfSlicesMR" },
{ 0x2001, 0x0019, 0, VR::CS, VM::M1, "PartialMatrixScanned" },
{ 0x2001, 0x001a, 0, VR::FL, VM::M3, "PCVelocity" },
{ 0x2001, 0x001b, 0, VR::FL, VM::M1, "PrepulseDelay" },
{ 0x2001, 0x001c, 0, VR::CS, VM::M1, "PrepulseType" },
{ 0x2001, 0x001d, 0, VR::IS, VM::M1, "ReconstructionNumberMR" },
{ 0x2001, 0x001e, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x001f, 0, VR::CS, VM::M1, "RespirationSync" },
{ 0x2001, 0x0020, 0, VR::LO, VM::M1, "ScanningTechnique" },
{ 0x2001, 0x0021, 0, VR::CS, VM::M1, "SPIR" },
{ 0x2001, 0x0022, 0, VR::FL, VM::M1, "WaterFatShift" },
{ 0x2001, 0x0023, 0, VR::DS, VM::M1, "FlipAngle" },
{ 0x2001, 0x0024, 0, VR::CS, VM::M1, "SeriesIsInteractive" },
{ 0x2001, 0x0025, 0, VR::SH, VM::M1, "EchoTimeDisplay" },
{ 0x2001, 0x0026, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0029, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x002b, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x002d, 0, VR::SS, VM::M1, "NumberOfSlicesInStack" },
{ 0x2001, 0x0032, 0, VR::FL, VM::M1, "StackRadialAngle" },
{ 0x2001, 0x0033, 0, VR::CS, VM::M1, "StackRadialAxis" },
{ 0x2001, 0x0035, 0, VR::SS, VM::M1, "StackSliceNumber" },
{ 0x2001, 0x0036, 0, VR::CS, VM::M1, "StackSliceType" },
{ 0x2001, 0x0039, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x003d, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x003f, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0046, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0047, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x0048, 0, VR::SS, VM::M1, "" },
{ 0x2001, 0x004b, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x004c, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x004d, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x004e, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0051, 0, VR::IS, VM::M1, "" },
{ 0x2001, 0x0052, 0, VR::UI, VM::M1, "" },
{ 0x2001, 0x0053, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0054, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x0055, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x0056, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0058, 0, VR::UL, VM::M1, "ContrastTransferTaste" },
{ 0x2001, 0x005a, 0, VR::ST, VM::M1, "" },
{ 0x2001, 0x005f, 0, VR::SQ, VM::M1, "StackSequence" },
{ 0x2001, 0x0060, 0, VR::SL, VM::M1, "NumberOfStacks" },
{ 0x2001, 0x0061, 0, VR::CS, VM::M1, "SeriesTransmitted" },
{ 0x2001, 0x0062, 0, VR::CS, VM::M1, "SeriesCommitted" },
{ 0x2001, 0x0063, 0, VR::CS, VM::M1, "ExaminationSource" },
{ 0x2001, 0x0064, 0, VR::SH, VM::M1, "" },
{ 0x2001, 0x0065, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x0067, 0, VR::CS, VM::M1, "LinearPresentationGLTrafoShapeSub" },
{ 0x2001, 0x0068, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x0069, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x006a, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x006b, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x006d, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x006e, 0, VR::SH, VM::M1, "SeriesType" },
{ 0x2001, 0x0071, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x0074, 0, VR::DS, VM::M1, "" },
{ 0x2001, 0x0075, 0, VR::DS, VM::M1, "" },
{ 0x2001, 0x0076, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x0077, 0, VR::CS, VM::M1, "GLTrafoType" },
{ 0x2001, 0x007a, 0, VR::FL, VM::M1, "" },
{ 0x2001, 0x007b, 0, VR::IS, VM::M1, "AcquisitionNumber" },
{ 0x2001, 0x0080, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0081, 0, VR::IS, VM::M1, "NumberOfDynamicScans" },
{ 0x2001, 0x0082, 0, VR::IS, VM::M1, "EchoTrainLength" },
{ 0x2001, 0x0083, 0, VR::DS, VM::M1, "ImagingFrequency" },
{ 0x2001, 0x0084, 0, VR::DS, VM::M1, "InversionTime" },
{ 0x2001, 0x0085, 0, VR::DS, VM::M1, "MagneticFieldStrength" },
{ 0x2001, 0x0086, 0, VR::IS, VM::M1, "" },
{ 0x2001, 0x0087, 0, VR::SH, VM::M1, "ImagedNucleus" },
{ 0x2001, 0x0088, 0, VR::DS, VM::M1, "NumberOfAverages" },
{ 0x2001, 0x0089, 0, VR::DS, VM::M1, "PhaseFOVPercent" },
{ 0x2001, 0x008a, 0, VR::DS, VM::M1, "SamplingPercent" },
{ 0x2001, 0x008b, 0, VR::SH, VM::M1, "" },
{ 0x2001, 0x0090, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0091, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0092, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x0093, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x009a, 0, VR::SQ, VM::M1, "" },
{ 0x2001, 0x009b, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x009c, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x009f, 0, VR::US, VM::M2, "PixelProcessingKernelSize" },
{ 0x2001, 0x00a1, 0, VR::CS, VM::M1, "IsRawImage" },
{ 0x2001, 0x00a3, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x00a4, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x00a5, 0, VR::UL, VM::M1, "" },
{ 0x2001, 0x00c1, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x00c8, 0, VR::LO, VM::M1, "" },
{ 0x2001, 0x00cc, 0, VR::ST, VM::M1, "" },
{ 0x2001, 0x00da, 0, VR::CS, VM::M1, "" },
{ 0x2001, 0x00f1, 0, VR::FL, VM::M1TN, "ProspectiveMotionCorrection" },
{ 0x2001, 0x00f2, 0, VR::FL, VM::M1TN, "RetrospectiveMotionCorrection" },
};

unsigned short Dict305TagHashTable[] = {
   29,    36,    43,    50,    57,    68,    77,    88,    95,   106,
  113,   126,   133,   140,   147,   152,   161,   172,   179,   190,
  203,   218,   225,   232,   241,   250,   259,   272,     0,     3,
   23,    25,    42,    53,    54,    80,     3,    22,    24,    55,
   81,    75,   109,     3,    25,    27,    56,    82,    76,   110,
    3,    24,    26,    43,    54,    57,    83,     5,     0,     1,
   27,    29,    44,    57,    58,    84,    99,   147,     4,    26,
   28,    59,    85,    77,   113,    98,   146,     5,     2,     3,
   29,    31,    60,    86,    97,   145,   109,   200,     3,     1,
    2,    28,    30,    96,   144,     5,     4,     5,    31,    33,
   45,    61,    61,    88,    78,   116,     3,     3,     4,    30,
   32,    79,   117,     6,     6,     7,    33,    35,    46,    63,
   62,    90,    80,   118,   110,   204,     3,     5,     6,    32,
   34,    81,   119,     3,     8,     9,    35,    37,   101,   155,
    3,     7,     8,    34,    36,   100,   154,     2,    10,    11,
   82,   122,     4,     9,    10,    36,    38,    63,    95,    83,
  123,     5,    37,    41,    64,    96,    87,   131,   103,   159,
  113,   242,     3,    11,    12,    65,    97,    86,   130,     5,
   13,    15,    38,    43,    47,    70,    66,    98,    85,   129,
    6,    12,    14,    48,    71,    67,    99,    84,   128,   102,
  156,   112,   241,     7,    15,    17,    39,    45,    49,    72,
   68,   100,    91,   135,   105,   163,   111,   218,     3,    14,
   16,    69,   101,    90,   134,     3,    17,    19,    89,   133,
  104,   161,     4,    16,    18,    50,    75,    70,   103,    88,
  132,     4,    19,    21,    51,    76,    71,   104,    95,   139,
    4,    18,    20,    52,    77,    72,   105,    94,   138,     6,
   21,    23,    41,    51,    53,    78,    73,   106,    93,   137,
  107,   165,     6,    20,    22,    40,    50,    74,   107,    92,
  136,   106,   164,   108,   193,
};

vtkDICOMDictionary::Dict Dict305Data = {
"PHILIPS IMAGING DD 001",
28,
114,
Dict305TagHashTable,
Dict305Contents
};

// ----- NQRight -----

DictEntry Dict306Contents[] = {
{ 0x0299, 0x0001, 0, VR::FL, VM::M1, "RightCorticalWhiteMatter" },
{ 0x0299, 0x0002, 0, VR::FL, VM::M1, "RightCorticalGrayMatter" },
{ 0x0299, 0x0003, 0, VR::FL, VM::M1, "Right3rdVentricle" },
{ 0x0299, 0x0004, 0, VR::FL, VM::M1, "Right4thVentricle" },
{ 0x0299, 0x0005, 0, VR::FL, VM::M1, "Right5thVentricle" },
{ 0x0299, 0x0006, 0, VR::FL, VM::M1, "RightLateralVentricle" },
{ 0x0299, 0x0007, 0, VR::FL, VM::M1, "RightInferiorLateralVentricle" },
{ 0x0299, 0x0008, 0, VR::FL, VM::M1, "RightInferiorCSF" },
{ 0x0299, 0x0009, 0, VR::FL, VM::M1, "RightCerebellarWhiteMatter" },
{ 0x0299, 0x000a, 0, VR::FL, VM::M1, "RightCerebellarGrayMatter" },
{ 0x0299, 0x000b, 0, VR::FL, VM::M1, "RightHippocampus" },
{ 0x0299, 0x000c, 0, VR::FL, VM::M1, "RightAmygdala" },
{ 0x0299, 0x000d, 0, VR::FL, VM::M1, "RightThalamus" },
{ 0x0299, 0x000e, 0, VR::FL, VM::M1, "RightCaudate" },
{ 0x0299, 0x000f, 0, VR::FL, VM::M1, "RightPutamen" },
{ 0x0299, 0x0010, 0, VR::FL, VM::M1, "RightPallidum" },
{ 0x0299, 0x0011, 0, VR::FL, VM::M1, "RightVentralDiencephalon" },
{ 0x0299, 0x0012, 0, VR::FL, VM::M1, "RightNucleusAccumbens" },
{ 0x0299, 0x0013, 0, VR::FL, VM::M1, "RightBrainStem" },
{ 0x0299, 0x0014, 0, VR::FL, VM::M1, "RightExteriorCSF" },
{ 0x0299, 0x0015, 0, VR::FL, VM::M1, "RightWMHypo" },
{ 0x0299, 0x0016, 0, VR::FL, VM::M1, "RightOther" },
{ 0x0299, 0x0017, 0, VR::FL, VM::M1, "RightCortexUnkown" },
{ 0x0299, 0x0018, 0, VR::FL, VM::M1, "RightCortexBankssts" },
{ 0x0299, 0x0019, 0, VR::FL, VM::M1, "RightCortexCaudalAnteriorCingulate" },
{ 0x0299, 0x001a, 0, VR::FL, VM::M1, "RightCortexCaudalMiddleFrontal" },
{ 0x0299, 0x001b, 0, VR::FL, VM::M1, "RightCortexCorpusCallosum" },
{ 0x0299, 0x001c, 0, VR::FL, VM::M1, "RightCortexCuneus" },
{ 0x0299, 0x001d, 0, VR::FL, VM::M1, "RightCortexEntorhinal" },
{ 0x0299, 0x001e, 0, VR::FL, VM::M1, "RightCortexFusiform" },
{ 0x0299, 0x001f, 0, VR::FL, VM::M1, "RightCortexInferiorParietal" },
{ 0x0299, 0x0020, 0, VR::FL, VM::M1, "RightCortexInferiorTemporal" },
{ 0x0299, 0x0021, 0, VR::FL, VM::M1, "RightCortexIsthmusCingulate" },
{ 0x0299, 0x0022, 0, VR::FL, VM::M1, "RightCortexLateralOccipital" },
{ 0x0299, 0x0023, 0, VR::FL, VM::M1, "RightCortexLateralOrbitoFrontal" },
{ 0x0299, 0x0024, 0, VR::FL, VM::M1, "RightCortexLingual" },
{ 0x0299, 0x0025, 0, VR::FL, VM::M1, "RightCortexMedialOrbitoFrontal" },
{ 0x0299, 0x0026, 0, VR::FL, VM::M1, "RightCortexMiddleTemporal" },
{ 0x0299, 0x0027, 0, VR::FL, VM::M1, "RightCortexParahippocampal" },
{ 0x0299, 0x0028, 0, VR::FL, VM::M1, "RightCortexParacentral" },
{ 0x0299, 0x0029, 0, VR::FL, VM::M1, "RightCortexParsOpercularis" },
{ 0x0299, 0x002a, 0, VR::FL, VM::M1, "RightCortexParsOrbitalis" },
{ 0x0299, 0x002b, 0, VR::FL, VM::M1, "RightCortexParsTriangularis" },
{ 0x0299, 0x002c, 0, VR::FL, VM::M1, "RightCortexPericalcarine" },
{ 0x0299, 0x002d, 0, VR::FL, VM::M1, "RightCortexPostcentral" },
{ 0x0299, 0x002e, 0, VR::FL, VM::M1, "RightCortexPosteriorCingulate" },
{ 0x0299, 0x002f, 0, VR::FL, VM::M1, "RightCortexPrecentral" },
{ 0x0299, 0x0030, 0, VR::FL, VM::M1, "RightCortexPrecuneus" },
{ 0x0299, 0x0031, 0, VR::FL, VM::M1, "RightCortexRostralAnteriorCingulate" },
{ 0x0299, 0x0032, 0, VR::FL, VM::M1, "RightCortexRostralMiddleFrontal" },
{ 0x0299, 0x0033, 0, VR::FL, VM::M1, "RightCortexSuperiorFrontal" },
{ 0x0299, 0x0034, 0, VR::FL, VM::M1, "RightCortexSuperiorParietal" },
{ 0x0299, 0x0035, 0, VR::FL, VM::M1, "RightCortexSuperiorTemporal" },
{ 0x0299, 0x0036, 0, VR::FL, VM::M1, "RightCortexSupramarginal" },
{ 0x0299, 0x0037, 0, VR::FL, VM::M1, "RightCortexFrontalPole" },
{ 0x0299, 0x0038, 0, VR::FL, VM::M1, "RightCortexTemporalPole" },
{ 0x0299, 0x0039, 0, VR::FL, VM::M1, "RightCortexTransvereTemporal" },
{ 0x0299, 0x003a, 0, VR::FL, VM::M1, "RightMeningie" },
};

unsigned short Dict306TagHashTable[] = {
   15,    24,    31,    42,    53,    62,    71,    80,    89,    96,
  105,   116,   127,   136,     0,     4,     0,     1,    22,    23,
   46,    47,    50,    51,     3,    21,    22,    45,    46,    49,
   50,     5,     6,     7,    20,    21,    34,    35,    44,    45,
   48,    49,     5,     5,     6,    19,    20,    33,    34,    43,
   44,    47,    48,     4,     4,     5,    26,    27,    32,    33,
   54,    55,     4,     3,     4,    25,    26,    31,    32,    53,
   54,     4,    10,    11,    24,    25,    38,    39,    52,    53,
    4,     9,    10,    23,    24,    37,    38,    51,    52,     3,
    8,     9,    30,    31,    36,    37,     4,     7,     8,    29,
   30,    35,    36,    57,    58,     5,    14,    15,    18,    19,
   28,    29,    42,    43,    56,    57,     5,    13,    14,    17,
   18,    27,    28,    41,    42,    55,    56,     4,     2,     3,
   12,    13,    16,    17,    40,    41,     4,     1,     2,    11,
   12,    15,    16,    39,    40,
};

vtkDICOMDictionary::Dict Dict306Data = {
"NQRight",
14,
58,
Dict306TagHashTable,
Dict306Contents
};

// ----- Siemens: Thorax/Multix FD Lab Settings -----

DictEntry Dict307Contents[] = {
{ 0x0019, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::LO, VM::M1, "TotalDoseAreaProduct" },
{ 0x0019, 0x0003, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0004, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::FD, VM::M1, "TableObjectDistance" },
{ 0x0019, 0x0007, 0, VR::FD, VM::M1, "TableDetectorDistance" },
{ 0x0019, 0x0008, 0, VR::US, VM::M1TN, "OrthoStepDistance" },
{ 0x0021, 0x0008, 0, VR::US, VM::M1, "AutoWindowFlag" },
{ 0x0021, 0x0009, 0, VR::SL, VM::M1, "AutoWindowCenter" },
{ 0x0021, 0x000A, 0, VR::SL, VM::M1, "AutoWindowWidth" },
{ 0x0021, 0x000B, 0, VR::SS, VM::M1, "FilterID" },
{ 0x0021, 0x0014, 0, VR::US, VM::M1, "AnatomicCorrectView" },
{ 0x0021, 0x0015, 0, VR::SS, VM::M1, "AutoWindowShift" },
{ 0x0021, 0x0016, 0, VR::DS, VM::M1, "AutoWindowExpansion" },
{ 0x0021, 0x0017, 0, VR::LO, VM::M1, "SystemType" },
{ 0x0021, 0x0030, 0, VR::SH, VM::M1, "AnatomicSortNumber" },
{ 0x0021, 0x0031, 0, VR::SH, VM::M1, "AcquisitionSortNumber" },
};

unsigned short Dict307TagHashTable[] = {
    5,    16,    29,    38,     0,     5,     1,     1,     5,     5,
   10,     9,    14,    21,    18,    49,     6,     0,     0,     4,
    4,     8,     8,     9,     8,    13,    20,    17,    48,     4,
    3,     3,     7,     7,    12,    11,    16,    23,     4,     2,
    2,     6,     6,    11,    10,    15,    22,
};

vtkDICOMDictionary::Dict Dict307Data = {
"Siemens: Thorax/Multix FD Lab Settings",
4,
19,
Dict307TagHashTable,
Dict307Contents
};

// ----- V1 -----

DictEntry Dict308Contents[] = {
{ 0x0011, 0x0001, 0, VR::OB, VM::M1, "UserData" },
{ 0x0011, 0x0002, 0, VR::DS, VM::M1, "NormalizationCoefficient" },
{ 0x0011, 0x0003, 0, VR::DS, VM::M1TN, "ReceivingGain" },
{ 0x0011, 0x0004, 0, VR::DS, VM::M1, "MeanImageNoise" },
};

unsigned short Dict308TagHashTable[] = {
    2,     0,     4,     0,     1,     1,     2,     2,     3,     3,
    4,
};

vtkDICOMDictionary::Dict Dict308Data = {
"V1",
1,
4,
Dict308TagHashTable,
Dict308Contents
};

// ----- GEMS_SERS_01 -----

DictEntry Dict309Contents[] = {
{ 0x0025, 0x0006, 0, VR::SS, VM::M1, "LastPulseSequenceUsed" },
{ 0x0025, 0x0007, 0, VR::SL, VM::M1, "ImagesInSeries" },
{ 0x0025, 0x0010, 0, VR::SL, VM::M1, "LandmarkCounter" },
{ 0x0025, 0x0011, 0, VR::SS, VM::M1, "NumberOfAcquisitions" },
{ 0x0025, 0x0014, 0, VR::SL, VM::M1, "IndicatesNumberOfUpdatesToHeader" },
{ 0x0025, 0x0017, 0, VR::SL, VM::M1, "SeriesCompleteFlag" },
{ 0x0025, 0x0018, 0, VR::SL, VM::M1, "NumberOfImagesArchived" },
{ 0x0025, 0x0019, 0, VR::SL, VM::M1, "LastInstanceNumberUsed" },
{ 0x0025, 0x001a, 0, VR::SH, VM::M1, "PrimaryReceiverSuiteAndHost" },
{ 0x0025, 0x001b, 0, VR::OB, VM::M1, "ProtocolDataBlockCompressed" },
};

unsigned short Dict309TagHashTable[] = {
    3,    14,     0,     5,     1,     7,     3,    17,     5,    23,
    7,    25,     9,    27,     5,     0,     6,     2,    16,     4,
   20,     6,    24,     8,    26,
};

vtkDICOMDictionary::Dict Dict309Data = {
"GEMS_SERS_01",
2,
10,
Dict309TagHashTable,
Dict309Contents
};

// ----- astm.org/diconde/iod/NdeUsEquipment -----

DictEntry Dict310Contents[] = {
{ 0x0009, 0x0002, 0, VR::SQ, VM::M1, "PulserEquipmentSequence" },
{ 0x0009, 0x0004, 0, VR::CS, VM::M1, "PulserType" },
{ 0x0009, 0x0006, 0, VR::LT, VM::M1, "PulserNotes" },
{ 0x0009, 0x0008, 0, VR::SQ, VM::M1, "ReceiverEquipmentSequence" },
{ 0x0009, 0x000A, 0, VR::CS, VM::M1, "AmplifierType" },
{ 0x0009, 0x000C, 0, VR::LT, VM::M1, "ReceiverNotes" },
{ 0x0009, 0x000E, 0, VR::SQ, VM::M1, "PreAmplifierEquipmentSequence" },
{ 0x0009, 0x000F, 0, VR::LT, VM::M1, "PreAmplifierNotes" },
{ 0x0009, 0x0010, 0, VR::SQ, VM::M1, "TransmitTransducerSequence" },
{ 0x0009, 0x0011, 0, VR::SQ, VM::M1, "ReceiveTransducerSequence" },
{ 0x0009, 0x0012, 0, VR::US, VM::M1, "NumberOfElements" },
{ 0x0009, 0x0013, 0, VR::CS, VM::M1, "ElementShape" },
{ 0x0009, 0x0014, 0, VR::DS, VM::M1, "ElementDimensionA" },
{ 0x0009, 0x0015, 0, VR::DS, VM::M1, "ElementDimensionB" },
{ 0x0009, 0x0016, 0, VR::DS, VM::M1, "ElementPitch" },
{ 0x0009, 0x0017, 0, VR::DS, VM::M1, "MeasuredBeamDimensionA" },
{ 0x0009, 0x0018, 0, VR::DS, VM::M1, "MeasuredBeamDimensionB" },
{ 0x0009, 0x0019, 0, VR::DS, VM::M1, "LocationOfMeasuredBeamDiameter" },
{ 0x0009, 0x001A, 0, VR::DS, VM::M1, "NominalFrequency" },
{ 0x0009, 0x001B, 0, VR::DS, VM::M1, "MeasuredCenterFrequency" },
{ 0x0009, 0x001C, 0, VR::DS, VM::M1, "MeasuredBandwidth" },
};

unsigned short Dict310TagHashTable[] = {
    6,    15,    30,    37,    46,     0,     4,     2,     6,     5,
   12,     8,    16,    15,    23,     7,     0,     2,     3,     8,
    7,    15,    11,    19,    14,    22,    17,    25,    20,    28,
    3,     6,    14,    10,    18,    16,    24,     4,     1,     4,
    4,    10,    13,    21,    19,    27,     3,     9,    17,    12,
   20,    18,    26,
};

vtkDICOMDictionary::Dict Dict310Data = {
"astm.org/diconde/iod/NdeUsEquipment",
5,
21,
Dict310TagHashTable,
Dict310Contents
};

// ----- AMI ImageContext_01 -----

DictEntry Dict311Contents[] = {
{ 0x3109, 0x0010, 0, VR::CS, VM::M1, "WindowInvert" },
{ 0x3109, 0x0020, 0, VR::IS, VM::M1, "WindowCenter" },
{ 0x3109, 0x0030, 0, VR::IS, VM::M1, "WindowWidth" },
{ 0x3109, 0x0040, 0, VR::CS, VM::M1, "PixelAspectRatioSwap" },
{ 0x3109, 0x0050, 0, VR::CS, VM::M1, "EnableAveraging" },
{ 0x3109, 0x0060, 0, VR::CS, VM::M1, "Quality" },
{ 0x3109, 0x0070, 0, VR::CS, VM::M1, "ViewportAnnotationLevel" },
{ 0x3109, 0x0080, 0, VR::CS, VM::M1, "ShowImageAnnotation" },
{ 0x3109, 0x0090, 0, VR::CS, VM::M1, "Show mageOverlay" },
};

unsigned short Dict311TagHashTable[] = {
    3,    12,     0,     4,     3,    64,     4,    80,     5,    96,
    6,   112,     5,     0,    16,     1,    32,     2,    48,     7,
  128,     8,   144,
};

vtkDICOMDictionary::Dict Dict311Data = {
"AMI ImageContext_01",
2,
9,
Dict311TagHashTable,
Dict311Contents
};

// ----- SPI-P-XSB-VISUB Release 1 -----

DictEntry Dict312Contents[] = {
{ 0x0019, 0x0000, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0010, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0011, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0012, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0001, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0002, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x000f, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0011, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0012, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x001f, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0020, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0021, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0022, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x002f, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x0030, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0031, 0, VR::DS, VM::M1, "" },
{ 0x0029, 0x0032, 0, VR::CS, VM::M1, "" },
{ 0x0029, 0x003f, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict312TagHashTable[] = {
    6,    13,    24,    35,    46,     0,     3,     0,     0,     8,
    1,    19,    48,     5,     3,    18,     7,     0,    12,    17,
   17,    34,    18,    47,     5,     4,    32,     6,    80,    11,
   16,    21,    50,    22,    63,     5,     2,    17,     5,    64,
    9,     2,    10,    15,    16,    33,     5,     1,    16,    13,
   18,    14,    31,    15,    32,    20,    49,
};

vtkDICOMDictionary::Dict Dict312Data = {
"SPI-P-XSB-VISUB Release 1",
5,
23,
Dict312TagHashTable,
Dict312Contents
};

// ----- 2.16.840.1.114059.1.1.6.1.50.1 -----

DictEntry Dict313Contents[] = {
{ 0x0029, 0x0020, 0, VR::LT, VM::M1, "" },
{ 0x0029, 0x0021, 0, VR::ST, VM::M1, "" },
{ 0x0029, 0x0022, 0, VR::ST, VM::M1, "" },
{ 0x0029, 0x0023, 0, VR::ST, VM::M1, "" },
{ 0x0029, 0x0024, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0025, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0026, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0027, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict313TagHashTable[] = {
    3,    12,     0,     4,     1,    33,     3,    35,     5,    37,
    7,    39,     4,     0,    32,     2,    34,     4,    36,     6,
   38,
};

vtkDICOMDictionary::Dict Dict313Data = {
"2.16.840.1.114059.1.1.6.1.50.1",
2,
8,
Dict313TagHashTable,
Dict313Contents
};

// ----- SIEMENS RIS -----

DictEntry Dict314Contents[] = {
{ 0x0011, 0x0010, 0, VR::LO, VM::M1, "PatientUID" },
{ 0x0011, 0x0011, 0, VR::LO, VM::M1, "PatientID" },
{ 0x0011, 0x0020, 0, VR::DA, VM::M1, "PatientRegistrationDate" },
{ 0x0011, 0x0021, 0, VR::TM, VM::M1, "PatientRegistrationTime" },
{ 0x0011, 0x0030, 0, VR::PN, VM::M1, "PatientnameRIS" },
{ 0x0011, 0x0031, 0, VR::LO, VM::M1, "PatientprenameRIS" },
{ 0x0011, 0x0040, 0, VR::LO, VM::M1, "PatientHospitalStatus" },
{ 0x0011, 0x0041, 0, VR::LO, VM::M1, "MedicalAlerts" },
{ 0x0011, 0x0042, 0, VR::LO, VM::M1, "ContrastAllergies" },
{ 0x0031, 0x0010, 0, VR::LO, VM::M1, "RequestUID" },
{ 0x0031, 0x0045, 0, VR::LO, VM::M1, "RequestingPhysician" },
{ 0x0031, 0x0050, 0, VR::LO, VM::M1, "RequestedPhysician" },
{ 0x0033, 0x0010, 0, VR::LO, VM::M1, "PatientStudyUID" },
};

unsigned short Dict314TagHashTable[] = {
    4,    19,    26,     0,     7,     1,    17,     3,    33,     4,
   48,     7,    65,     9,    16,    10,    69,    11,    80,     3,
    0,    16,     2,    32,     8,    66,     3,     5,    49,     6,
   64,    12,    16,
};

vtkDICOMDictionary::Dict Dict314Data = {
"SIEMENS RIS",
3,
13,
Dict314TagHashTable,
Dict314Contents
};

// ----- GEMS_YMHD_01 -----

DictEntry Dict315Contents[] = {
{ 0x0033, 0x0005, 0, VR::UN, VM::M1, "" },
{ 0x0033, 0x0006, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict315TagHashTable[] = {
    2,     0,     2,     0,     5,     1,     6,
};

vtkDICOMDictionary::Dict Dict315Data = {
"GEMS_YMHD_01",
1,
2,
Dict315TagHashTable,
Dict315Contents
};

// ----- SPI-P-CTBE Release 1 -----

DictEntry Dict316Contents[] = {
{ 0x0019, 0x0000, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0004, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x000b, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x000c, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0014, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0018, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0019, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x001a, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x001b, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x001c, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x001d, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict316TagHashTable[] = {
    4,    15,    26,     0,     5,     1,     2,     5,    11,     6,
   12,     9,    25,    10,    26,     5,     0,     0,     4,     5,
    7,    20,     8,    24,    13,    29,     4,     2,     3,     3,
    4,    11,    27,    12,    28,
};

vtkDICOMDictionary::Dict Dict316Data = {
"SPI-P-CTBE Release 1",
3,
14,
Dict316TagHashTable,
Dict316Contents
};

// ----- ISG shadow -----

DictEntry Dict317Contents[] = {
{ 0x0029, 0x0070, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0080, 0, VR::IS, VM::M1, "" },
{ 0x0029, 0x0090, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict317TagHashTable[] = {
    2,     0,     3,     0,   112,     1,   128,     2,   144,
};

vtkDICOMDictionary::Dict Dict317Data = {
"ISG shadow",
1,
3,
Dict317TagHashTable,
Dict317Contents
};

// ----- METAEMOTION GINKGO RETINAL -----

DictEntry Dict318Contents[] = {
{ 0x0011, 0x0001, 0, VR::LT, VM::M1, "KeyFileIndicator" },
{ 0x0011, 0x000B, 0, VR::LT, VM::M1, "SerializedDiagnoseAndMarkers" },
{ 0x0011, 0x000C, 0, VR::UN, VM::M1, "VirtualAneritraContrastImage" },
};

unsigned short Dict318TagHashTable[] = {
    2,     0,     3,     0,     1,     1,    11,     2,    12,
};

vtkDICOMDictionary::Dict Dict318Data = {
"METAEMOTION GINKGO RETINAL",
1,
3,
Dict318TagHashTable,
Dict318Contents
};

// ----- Riverain Medical -----

DictEntry Dict319Contents[] = {
{ 0x0203, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0203, 0x0001, 0, VR::LO, VM::M1, "" },
{ 0x0203, 0x0002, 0, VR::LO, VM::M1, "" },
{ 0x0203, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x0203, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0203, 0x00f0, 0, VR::UI, VM::M1, "" },
{ 0x0203, 0x00f1, 0, VR::UI, VM::M1, "" },
};

unsigned short Dict319TagHashTable[] = {
    2,     0,     7,     0,     0,     1,     1,     2,     2,     3,
    3,     4,    16,     5,   240,     6,   241,
};

vtkDICOMDictionary::Dict Dict319Data = {
"Riverain Medical",
1,
7,
Dict319TagHashTable,
Dict319Contents
};

// ----- HOLOGIC -----

DictEntry Dict320Contents[] = {
{ 0x0011, 0x0000, 0, VR::LO, VM::M1, "HxQuestionnaire" },
{ 0x0021, 0x0001, 0, VR::LT, VM::M1, "ImageAnalysisDataInXML" },
{ 0x0023, 0x0000, 0, VR::LO, VM::M1, "EncodingSchemeVersion" },
{ 0x0023, 0x0001, 0, VR::LO, VM::M1, "PFileName" },
{ 0x0023, 0x0002, 0, VR::OB, VM::M1, "PFileData" },
{ 0x0023, 0x0003, 0, VR::UL, VM::M1, "PFileLength" },
{ 0x0023, 0x0004, 0, VR::OB, VM::M1, "RFileData" },
{ 0x0023, 0x0005, 0, VR::UL, VM::M1, "RFileLength" },
};

unsigned short Dict320TagHashTable[] = {
    3,    12,     0,     4,     1,     1,     3,     1,     5,     3,
    7,     5,     4,     0,     0,     2,     0,     4,     2,     6,
    4,
};

vtkDICOMDictionary::Dict Dict320Data = {
"HOLOGIC",
2,
8,
Dict320TagHashTable,
Dict320Contents
};

// ----- GEMS_ACRQA_2.0 BLOCK1 -----

DictEntry Dict321Contents[] = {
{ 0x0023, 0x0000, 0, VR::LO, VM::M1, "CRExposureMenuCode" },
{ 0x0023, 0x0010, 0, VR::LO, VM::M1, "CRExposureMenuString" },
{ 0x0023, 0x0020, 0, VR::LO, VM::M1, "CREDRMode" },
{ 0x0023, 0x0030, 0, VR::LO, VM::M1, "CRLatitude" },
{ 0x0023, 0x0040, 0, VR::LO, VM::M1, "CRGroupNumber" },
{ 0x0023, 0x0050, 0, VR::US, VM::M1, "CRImageSerialNumber" },
{ 0x0023, 0x0060, 0, VR::LO, VM::M1, "CRBarCodeNumber" },
{ 0x0023, 0x0070, 0, VR::LO, VM::M1, "CRFilmOutputExposure" },
{ 0x0023, 0x0080, 0, VR::LO, VM::M1, "CRFilmFormat" },
{ 0x0023, 0x0090, 0, VR::LO, VM::M1, "CRSShiftString" },
};

unsigned short Dict321TagHashTable[] = {
    3,    12,     0,     4,     4,    64,     5,    80,     6,    96,
    7,   112,     6,     0,     0,     1,    16,     2,    32,     3,
   48,     8,   128,     9,   144,
};

vtkDICOMDictionary::Dict Dict321Data = {
"GEMS_ACRQA_2.0 BLOCK1",
2,
10,
Dict321TagHashTable,
Dict321Contents
};

// ----- GEMS_ACRQA_2.0 BLOCK2 -----

DictEntry Dict322Contents[] = {
{ 0x0023, 0x0000, 0, VR::US, VM::M1, "CRSShift" },
{ 0x0023, 0x0010, 0, VR::LO, VM::M1, "CRCShift" },
{ 0x0023, 0x0020, 0, VR::LO, VM::M1, "CRGT" },
{ 0x0023, 0x0030, 0, VR::DS, VM::M1, "CRGA" },
{ 0x0023, 0x0040, 0, VR::DS, VM::M1, "CRGC" },
{ 0x0023, 0x0050, 0, VR::DS, VM::M1, "CRGS" },
{ 0x0023, 0x0060, 0, VR::LO, VM::M1, "CRRT" },
{ 0x0023, 0x0070, 0, VR::DS, VM::M1, "CRRE" },
{ 0x0023, 0x0080, 0, VR::US, VM::M1, "CRRN" },
{ 0x0023, 0x0090, 0, VR::DS, VM::M1, "CRDRT" },
};

unsigned short Dict322TagHashTable[] = {
    3,    12,     0,     4,     4,    64,     5,    80,     6,    96,
    7,   112,     6,     0,     0,     1,    16,     2,    32,     3,
   48,     8,   128,     9,   144,
};

vtkDICOMDictionary::Dict Dict322Data = {
"GEMS_ACRQA_2.0 BLOCK2",
2,
10,
Dict322TagHashTable,
Dict322Contents
};

// ----- GEMS_ACRQA_2.0 BLOCK3 -----

DictEntry Dict323Contents[] = {
{ 0x0023, 0x0000, 0, VR::DS, VM::M1, "CRDRE" },
{ 0x0023, 0x0010, 0, VR::US, VM::M1, "CRDRN" },
{ 0x0023, 0x0020, 0, VR::DS, VM::M1, "CRORE" },
{ 0x0023, 0x0030, 0, VR::US, VM::M1, "CRORN" },
{ 0x0023, 0x0040, 0, VR::US, VM::M1, "CRORD" },
{ 0x0023, 0x0050, 0, VR::LO, VM::M1, "CRCassetteSize" },
{ 0x0023, 0x0060, 0, VR::LO, VM::M1, "CRMachineID" },
{ 0x0023, 0x0070, 0, VR::LO, VM::M1, "CRMachineType" },
{ 0x0023, 0x0080, 0, VR::LO, VM::M1, "CRTechnicianCode" },
{ 0x0023, 0x0090, 0, VR::LO, VM::M1, "CREnergySubtractionParameters" },
{ 0x0023, 0x00f0, 0, VR::LO, VM::M1, "CRDistributionCode" },
{ 0x0023, 0x00ff, 0, VR::US, VM::M1, "CRShuttersApplied" },
};

unsigned short Dict323TagHashTable[] = {
    4,    15,    24,     0,     5,     1,    16,     2,    32,     5,
   80,     6,    96,     9,   144,     4,     3,    48,     7,   112,
   10,   240,    11,   255,     3,     0,     0,     4,    64,     8,
  128,
};

vtkDICOMDictionary::Dict Dict323Data = {
"GEMS_ACRQA_2.0 BLOCK3",
3,
12,
Dict323TagHashTable,
Dict323Contents
};

// ----- GEMS_3DSTATE_001 -----

DictEntry Dict324Contents[] = {
{ 0x0047, 0x00e9, 0, VR::FL, VM::M3, "" },
{ 0x0047, 0x00ea, 0, VR::DS, VM::M3, "" },
{ 0x0047, 0x00eb, 0, VR::DS, VM::M3, "" },
{ 0x0047, 0x00ec, 0, VR::FL, VM::M1, "" },
{ 0x0047, 0x00ed, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict324TagHashTable[] = {
    2,     0,     5,     0,   233,     1,   234,     2,   235,     3,
  236,     4,   237,
};

vtkDICOMDictionary::Dict Dict324Data = {
"GEMS_3DSTATE_001",
1,
5,
Dict324TagHashTable,
Dict324Contents
};

// ----- SEGAMI__PAGE -----

DictEntry Dict325Contents[] = {
{ 0x0033, 0x0097, 0, VR::IS, VM::M1, "" },
{ 0x0033, 0x0098, 0, VR::OW, VM::M1, "" },
};

unsigned short Dict325TagHashTable[] = {
    2,     0,     2,     0,   151,     1,   152,
};

vtkDICOMDictionary::Dict Dict325Data = {
"SEGAMI__PAGE",
1,
2,
Dict325TagHashTable,
Dict325Contents
};

// ----- SECTRA_Ident_01 -----

DictEntry Dict326Contents[] = {
{ 0x0009, 0x0001, 0, VR::SH, VM::M1, "RequestNumber" },
{ 0x0009, 0x0002, 0, VR::SH, VM::M1, "ExaminationNumber" },
{ 0x0009, 0x0004, 0, VR::LO, VM::M1, "SeriesIdentifier" },
{ 0x0009, 0x0005, 0, VR::LO, VM::M1, "SeriesOrder" },
{ 0x0009, 0x0006, 0, VR::LO, VM::M1, "FileName" },
{ 0x0009, 0x0007, 0, VR::LO, VM::M1, "ImageDataID" },
};

unsigned short Dict326TagHashTable[] = {
    2,     0,     6,     0,     1,     1,     2,     2,     4,     3,
    5,     4,     6,     5,     7,
};

vtkDICOMDictionary::Dict Dict326Data = {
"SECTRA_Ident_01",
1,
6,
Dict326TagHashTable,
Dict326Contents
};

// ----- STENTOR -----

DictEntry Dict327Contents[] = {
{ 0x0073, 0x0001, 0, VR::ST, VM::M1, "" },
{ 0x0073, 0x0002, 0, VR::ST, VM::M1, "" },
{ 0x0073, 0x0003, 0, VR::ST, VM::M1, "" },
{ 0x0073, 0x0004, 0, VR::ST, VM::M1, "" },
{ 0x0073, 0x0006, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict327TagHashTable[] = {
    2,     0,     5,     0,     1,     1,     2,     2,     3,     3,
    4,     4,     6,
};

vtkDICOMDictionary::Dict Dict327Data = {
"STENTOR",
1,
5,
Dict327TagHashTable,
Dict327Contents
};

// ----- ObjectModel (ID, Version, Place, PlaceDescription) -----

DictEntry Dict328Contents[] = {
{ 0x8101, 0x0000, 0, VR::LO, VM::M1, "ID" },
{ 0x8101, 0x0010, 0, VR::LO, VM::M1, "Version" },
};

unsigned short Dict328TagHashTable[] = {
    2,     0,     2,     0,     0,     1,    16,
};

vtkDICOMDictionary::Dict Dict328Data = {
"ObjectModel (ID, Version, Place, PlaceDescription)",
1,
2,
Dict328TagHashTable,
Dict328Contents
};

// ----- SIEMENS CSA REPORT -----

DictEntry Dict329Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "ReportType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "ReportVersion" },
{ 0x0029, 0x0015, 0, VR::US, VM::M1, "SRVariant" },
{ 0x0029, 0x0017, 0, VR::UI, VM::M1, "SCSOP InstanceUID" },
};

unsigned short Dict329TagHashTable[] = {
    2,     0,     4,     0,     8,     1,     9,     2,    21,     3,
   23,
};

vtkDICOMDictionary::Dict Dict329Data = {
"SIEMENS CSA REPORT",
1,
4,
Dict329TagHashTable,
Dict329Contents
};

// ----- astm.org/diconde/iod/ComponentSeries -----

DictEntry Dict330Contents[] = {
{ 0x0009, 0x0010, 0, VR::ST, VM::M1, "ActualEnvironmentalConditions" },
{ 0x0009, 0x0040, 0, VR::ST, VM::M1, "EnvironmentalConditions" },
};

unsigned short Dict330TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    64,
};

vtkDICOMDictionary::Dict Dict330Data = {
"astm.org/diconde/iod/ComponentSeries",
1,
2,
Dict330TagHashTable,
Dict330Contents
};

// ----- GEMS_0039 -----

DictEntry Dict331Contents[] = {
{ 0x0039, 0x0095, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict331TagHashTable[] = {
    2,     0,     1,     0,   149,
};

vtkDICOMDictionary::Dict Dict331Data = {
"GEMS_0039",
1,
1,
Dict331TagHashTable,
Dict331Contents
};

// ----- PHILIPS MR IMAGING DD 001 -----

DictEntry Dict332Contents[] = {
{ 0x2005, 0x0000, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0001, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0002, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0004, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0005, 0, VR::CS, VM::M1, "SynergyReconstructionType" },
{ 0x2005, 0x0008, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0009, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000b, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000d, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x000f, 0, VR::DS, VM::M1, "WindowCenter" },
{ 0x2005, 0x0010, 0, VR::DS, VM::M1, "WindowWidth" },
{ 0x2005, 0x0011, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0012, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0013, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0014, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0015, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0016, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0017, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0018, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0019, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x001a, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x001b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x001c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x001d, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x001e, 0, VR::SH, VM::M1, "" },
{ 0x2005, 0x001f, 0, VR::SH, VM::M1, "" },
{ 0x2005, 0x0020, 0, VR::SL, VM::M1, "NumberOfChemicalShift" },
{ 0x2005, 0x0021, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0022, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0023, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0025, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0026, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0027, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0028, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0029, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002a, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x002b, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x002c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002d, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x002e, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x002f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0030, 0, VR::FL, VM::M1, "RepetitionTime" },
{ 0x2005, 0x0031, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0032, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0033, 0, VR::FL, VM::M1, "AcquisitionDuration" },
{ 0x2005, 0x0034, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0035, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0036, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0037, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0038, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0039, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x003a, 0, VR::SH, VM::M1, "" },
{ 0x2005, 0x003b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x003c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x003d, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x003e, 0, VR::SL, VM::M1TN, "" },
{ 0x2005, 0x0048, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0049, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x004a, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x004b, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x004c, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x004d, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x004e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x004f, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0050, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0051, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0052, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0053, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0054, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0055, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0056, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0057, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0058, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0059, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005b, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x005d, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x005e, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x005f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0060, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0061, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0063, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x0064, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0065, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0066, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0067, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x0068, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0069, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006b, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006c, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006d, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x006e, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x006f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0070, 0, VR::LO, VM::M1, "" },
{ 0x2005, 0x0071, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0072, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0073, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0074, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0075, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0076, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0078, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0079, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x007a, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x007b, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x007e, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x0080, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0081, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x0083, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0084, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0085, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x0086, 0, VR::SS, VM::M1, "" },
{ 0x2005, 0x009e, 0, VR::SQ, VM::M1, "" },
{ 0x2005, 0x009f, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00a0, 0, VR::FL, VM::M1, "" },
{ 0x2005, 0x00a1, 0, VR::CS, VM::M1, "SyncraScan ype" },
{ 0x2005, 0x00a2, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00a3, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a4, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a5, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a6, 0, VR::IS, VM::M1, "" },
{ 0x2005, 0x00a7, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00a8, 0, VR::DS, VM::M1, "" },
{ 0x2005, 0x00a9, 0, VR::CS, VM::M1, "" },
{ 0x2005, 0x00b0, 0, VR::FL, VM::M1, "DiffusionDirectionRL" },
{ 0x2005, 0x00b1, 0, VR::FL, VM::M1, "DiffusionDirectionAP" },
{ 0x2005, 0x00b2, 0, VR::FL, VM::M1, "DiffusionDirectionFH" },
{ 0x2005, 0x00c0, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict332TagHashTable[] = {
   34,    43,    50,    55,    60,    65,    72,    77,    82,    91,
  102,   113,   126,   141,   152,   165,   176,   185,   194,   203,
  212,   219,   230,   241,   250,   259,   266,   273,   282,   291,
  300,   311,   320,     0,     4,    21,    24,    55,    59,    78,
   91,   116,   158,     3,    24,    27,    54,    58,    86,   100,
    2,    23,    26,    87,   101,     2,    33,    37,    88,   102,
    2,     4,     5,    89,   103,     3,     3,     4,    35,    39,
   83,    96,     2,    34,    38,    84,    97,     2,    30,    33,
  125,   167,     4,     1,     1,    29,    32,    85,    99,   124,
  166,     5,     0,     0,    32,    35,    94,   108,   115,   134,
  123,   165,     5,    31,    34,    63,    76,    95,   109,   114,
  133,   122,   164,     6,     2,     2,    41,    45,    64,    77,
   96,   110,   113,   132,   121,   163,     7,    10,    13,    40,
   44,    65,    78,    97,   111,   112,   131,   120,   162,   131,
  192,     5,     9,    12,    43,    47,    66,    79,    90,   104,
  119,   161,     6,    12,    15,    42,    46,    59,    72,    91,
  105,   111,   129,   118,   160,     5,    11,    14,    37,    41,
   60,    73,    92,   106,   110,   128,     4,     6,     9,    36,
   40,    61,    74,    93,   107,     4,     5,     8,    39,    43,
   62,    75,   102,   116,     4,     8,    11,    38,    42,    71,
   84,   103,   117,     4,     7,    10,    49,    53,    72,    85,
  104,   118,     3,    18,    21,    48,    52,    73,    86,     5,
   17,    20,    51,    55,    74,    87,    98,   112,   127,   169,
    5,    20,    23,    50,    54,    67,    80,    99,   113,   126,
  168,     4,    19,    22,    45,    49,    68,    81,   100,   114,
    4,    14,    17,    44,    48,    69,    82,   101,   115,     3,
   13,    16,    47,    51,    70,    83,     3,    16,    19,    46,
   50,    79,    92,     4,    15,    18,    57,    61,    80,    93,
  109,   126,     4,    26,    29,    56,    60,    81,    94,   130,
  178,     4,    25,    28,    82,    95,   105,   120,   129,   177,
    5,    28,    31,    58,    62,    75,    88,   106,   121,   128,
  176,     4,    27,    30,    53,    57,    76,    89,   107,   122,
    5,    22,    25,    52,    56,    77,    90,   108,   123,   117,
  159,
};

vtkDICOMDictionary::Dict Dict332Data = {
"PHILIPS MR IMAGING DD 001",
33,
132,
Dict332TagHashTable,
Dict332Contents
};

// ----- GE_GENESIS_REV3.0 -----

DictEntry Dict333Contents[] = {
{ 0x0019, 0x0039, 0, VR::SS, VM::M1, "AxialType" },
{ 0x0019, 0x008f, 0, VR::SS, VM::M1, "SwapPhaseFrequency" },
{ 0x0019, 0x009c, 0, VR::SS, VM::M1, "PulseSequenceName" },
{ 0x0019, 0x009f, 0, VR::SS, VM::M1, "CoilType" },
{ 0x0019, 0x00a4, 0, VR::SS, VM::M1, "SATFatWaterBone" },
{ 0x0019, 0x00c0, 0, VR::SS, VM::M1, "BitmapOfSATSelections" },
{ 0x0019, 0x00c1, 0, VR::SS, VM::M1, "SurfaceCoilIntensityCorrectionFlag" },
{ 0x0019, 0x00cb, 0, VR::SS, VM::M1, "PhaseContrastFlowAxis" },
{ 0x0019, 0x00cc, 0, VR::SS, VM::M1, "PhaseContrastVelocityEncoding" },
{ 0x0019, 0x00d5, 0, VR::SS, VM::M1, "FractionalEcho" },
{ 0x0019, 0x00d8, 0, VR::SS, VM::M1, "VariableEchoFlag" },
{ 0x0019, 0x00d9, 0, VR::DS, VM::M1, "ConcatenatedSat" },
{ 0x0019, 0x00f2, 0, VR::SS, VM::M1, "NumberOfPhases" },
{ 0x0043, 0x001e, 0, VR::DS, VM::M1, "DeltaStartTime" },
{ 0x0043, 0x0027, 0, VR::SH, VM::M1, "ScanPitchRatio" },
};

unsigned short Dict333TagHashTable[] = {
    4,    15,    22,     0,     5,     2,   156,     3,   159,     6,
  193,     9,   213,    11,   217,     3,     1,   143,     8,   204,
   12,   242,     7,     0,    57,     4,   164,     5,   192,     7,
  203,    10,   216,    13,    30,    14,    39,
};

vtkDICOMDictionary::Dict Dict333Data = {
"GE_GENESIS_REV3.0",
3,
15,
Dict333TagHashTable,
Dict333Contents
};

// ----- SPI-P-PCR Release 2 -----

DictEntry Dict334Contents[] = {
{ 0x0019, 0x0010, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0020, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0021, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0040, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0060, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00a1, 0, VR::ST, VM::M1, "" },
{ 0x0019, 0x00a3, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a4, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a5, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a6, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a7, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a8, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00a9, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00aa, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00ab, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00ac, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00ad, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00ae, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00af, 0, VR::ST, VM::M1, "" },
{ 0x0019, 0x00b0, 0, VR::ST, VM::M1, "" },
{ 0x0019, 0x00b1, 0, VR::ST, VM::M1, "" },
{ 0x0019, 0x00b2, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00b3, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00b4, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x00b5, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00b6, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00b7, 0, VR::ST, VM::M1, "" },
{ 0x0019, 0x00b8, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x00b9, 0, VR::ST, VM::M1, "" },
{ 0x0019, 0x00ba, 0, VR::ST, VM::M1, "" },
};

unsigned short Dict334TagHashTable[] = {
    9,    22,    35,    44,    55,    62,    69,    76,     0,     6,
    2,    33,     4,    64,     5,    96,     9,   163,    17,   171,
   25,   179,     6,     0,    16,     1,    32,     3,    48,    16,
  170,    24,   178,    32,   186,     4,     8,   161,    15,   169,
   23,   177,    31,   185,     5,     6,   128,     7,   144,    14,
  168,    22,   176,    30,   184,     3,    13,   167,    21,   175,
   29,   183,     3,    12,   166,    20,   174,    28,   182,     3,
   11,   165,    19,   173,    27,   181,     3,    10,   164,    18,
  172,    26,   180,
};

vtkDICOMDictionary::Dict Dict334Data = {
"SPI-P-PCR Release 2",
8,
33,
Dict334TagHashTable,
Dict334Contents
};

// ----- GEMS_PATI_01 -----

DictEntry Dict335Contents[] = {
{ 0x0011, 0x0010, 0, VR::SS, VM::M1, "PatientStatus" },
};

unsigned short Dict335TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict335Data = {
"GEMS_PATI_01",
1,
1,
Dict335TagHashTable,
Dict335Contents
};

// ----- GEMS_Ultrasound_ImageGroup_001 -----

DictEntry Dict336Contents[] = {
{ 0x6003, 0x0010, 0, VR::SQ, VM::M1, "" },
{ 0x6003, 0x0011, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict336TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    17,
};

vtkDICOMDictionary::Dict Dict336Data = {
"GEMS_Ultrasound_ImageGroup_001",
1,
2,
Dict336TagHashTable,
Dict336Contents
};

// ----- SIEMENS MEDCOM HEADER -----

DictEntry Dict337Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "MedComHeaderType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "MedComHeaderVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "MedComHeaderInfo" },
{ 0x0029, 0x0020, 0, VR::OB, VM::M1, "MedComHistoryInformation" },
{ 0x0029, 0x0031, 0, VR::LO, VM::M1, "PMTFInformation1" },
{ 0x0029, 0x0032, 0, VR::UL, VM::M1, "PMTFInformation2" },
{ 0x0029, 0x0033, 0, VR::UL, VM::M1, "PMTFInformation3" },
{ 0x0029, 0x0034, 0, VR::CS, VM::M1, "PMTFInformation4" },
{ 0x0029, 0x0035, 0, VR::UL, VM::M1, "PMTFInformation5" },
{ 0x0029, 0x0040, 0, VR::SQ, VM::M1, "ApplicationHeaderSequence" },
{ 0x0029, 0x0041, 0, VR::CS, VM::M1, "ApplicationHeaderType" },
{ 0x0029, 0x0042, 0, VR::LO, VM::M1, "ApplicationHeaderID" },
{ 0x0029, 0x0043, 0, VR::LO, VM::M1, "ApplicationHeaderVersion" },
{ 0x0029, 0x0044, 0, VR::OB, VM::M1, "ApplicationHeaderInfo" },
{ 0x0029, 0x0050, 0, VR::LO, VM::M8, "WorkflowControlFlags" },
{ 0x0029, 0x0051, 0, VR::CS, VM::M1, "ArchiveManagementFlagKeepOnline" },
{ 0x0029, 0x0052, 0, VR::CS, VM::M1, "ArchiveManagementFlagDoNotArchive" },
{ 0x0029, 0x0053, 0, VR::CS, VM::M1, "ImageLocationStatus" },
{ 0x0029, 0x0054, 0, VR::DS, VM::M1, "EstimatedRetrieveTime" },
{ 0x0029, 0x0055, 0, VR::DS, VM::M1, "DataSizeOfRetrievedImages" },
{ 0x0029, 0x0070, 0, VR::SQ, VM::M1, "SiemensLinkSequence" },
{ 0x0029, 0x0071, 0, VR::AT, VM::M1, "ReferencedTag" },
{ 0x0029, 0x0072, 0, VR::CS, VM::M1, "ReferencedTagType" },
{ 0x0029, 0x0073, 0, VR::UL, VM::M1, "ReferencedValueLength" },
{ 0x0029, 0x0074, 0, VR::CS, VM::M1, "ReferencedObjectDeviceType" },
{ 0x0029, 0x0075, 0, VR::OB, VM::M1, "ReferencedObjectDeviceLocation" },
{ 0x0029, 0x0076, 0, VR::OB, VM::M1, "ReferencedObjectID" },
{ 0x0029, 0x0077, 0, VR::UL, VM::M1, "ReferencedObjectOffset" },
};

unsigned short Dict337TagHashTable[] = {
    8,    15,    26,    35,    44,    53,    62,     0,     3,     8,
   53,    10,    65,    23,   115,     5,     2,    16,     7,    52,
   11,    66,    14,    80,    24,   116,     4,     3,    32,    12,
   67,    15,    81,    25,   117,     4,     4,    49,    13,    68,
   16,    82,    26,   118,     4,     1,     9,    17,    83,    20,
  112,    27,   119,     4,     0,     8,     6,    51,    18,    84,
   21,   113,     4,     5,    50,     9,    64,    19,    85,    22,
  114,
};

vtkDICOMDictionary::Dict Dict337Data = {
"SIEMENS MEDCOM HEADER",
7,
28,
Dict337TagHashTable,
Dict337Contents
};

// ----- SIEMENS SYNGO EVIDENCE DOCUMENT DATA -----

DictEntry Dict338Contents[] = {
{ 0x0077, 0x0010, 0, VR::LO, VM::M1, "EvidenceDocumentTemplateName" },
{ 0x0077, 0x0011, 0, VR::DS, VM::M1, "EvidenceDocumentTemplateVersion" },
{ 0x0077, 0x0020, 0, VR::OB, VM::M1, "Data" },
{ 0x0077, 0x0021, 0, VR::OB, VM::M1, "Data" },
{ 0x0077, 0x0030, 0, VR::DS, VM::M1, "FrameworkVersion" },
{ 0x0077, 0x0040, 0, VR::OB, VM::M1, "Data" },
{ 0x0077, 0x0050, 0, VR::LO, VM::M1, "LogicalID" },
{ 0x0077, 0x0060, 0, VR::OB, VM::M1, "ApplicationData" },
{ 0x0077, 0x0070, 0, VR::LO, VM::M1, "OwnerClinicalTaskName" },
{ 0x0077, 0x0071, 0, VR::LO, VM::M1, "OwnerTaskName" },
{ 0x0077, 0x0072, 0, VR::OB, VM::M1, "OwnerSupportedTemplates" },
{ 0x0077, 0x0080, 0, VR::OB, VM::M1, "VolumeCatalog" },
};

unsigned short Dict338TagHashTable[] = {
    4,    13,    24,     0,     4,     0,    16,     3,    33,     6,
   80,     9,   113,     5,     1,    17,     4,    48,     5,    64,
    8,   112,    11,   128,     3,     2,    32,     7,    96,    10,
  114,
};

vtkDICOMDictionary::Dict Dict338Data = {
"SIEMENS SYNGO EVIDENCE DOCUMENT DATA",
3,
12,
Dict338TagHashTable,
Dict338Contents
};

// ----- GEMS_DL_SERIES_01 -----

DictEntry Dict339Contents[] = {
{ 0x0015, 0x0085, 0, VR::LO, VM::M1, "SeriesFileName" },
{ 0x0015, 0x0087, 0, VR::IS, VM::M1, "NumberOfImages" },
{ 0x0015, 0x008C, 0, VR::CS, VM::M1, "SentFlag" },
{ 0x0015, 0x008D, 0, VR::US, VM::M1, "ItemLocked" },
{ 0x0019, 0x004c, 0, VR::CS, VM::M1, "InternalLabel" },
{ 0x0019, 0x004d, 0, VR::CS, VM::M1, "BrowserHide" },
};

unsigned short Dict339TagHashTable[] = {
    2,     0,     6,     0,   133,     1,   135,     2,   140,     3,
  141,     4,    76,     5,    77,
};

vtkDICOMDictionary::Dict Dict339Data = {
"GEMS_DL_SERIES_01",
1,
6,
Dict339TagHashTable,
Dict339Contents
};

// ----- Canon Inc. -----

DictEntry Dict340Contents[] = {
{ 0x0019, 0x0010, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0013, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0015, 0, VR::DS, VM::M2, "" },
{ 0x0019, 0x0016, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0017, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0018, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0019, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x001a, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x001b, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x001c, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x001e, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x001f, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0021, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict340TagHashTable[] = {
    4,    17,    24,     0,     6,     0,    16,     2,    21,     3,
   22,     6,    25,     7,    26,    11,    31,     3,     1,    19,
    5,    24,    10,    30,     4,     4,    23,     8,    27,     9,
   28,    12,    33,
};

vtkDICOMDictionary::Dict Dict340Data = {
"Canon Inc.",
3,
13,
Dict340TagHashTable,
Dict340Contents
};

// ----- GEMS_GENIE_1 -----

DictEntry Dict341Contents[] = {
{ 0x0009, 0x0001, 0, VR::SH, VM::M1, "" },
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "StudyName" },
{ 0x0009, 0x0011, 0, VR::SL, VM::M1, "StudyFlags" },
{ 0x0009, 0x0012, 0, VR::SL, VM::M1, "StudyType" },
{ 0x0009, 0x001e, 0, VR::UI, VM::M1, "DatasetUID" },
{ 0x0009, 0x0020, 0, VR::LO, VM::M1, "SeriesObjectName" },
{ 0x0009, 0x0021, 0, VR::SL, VM::M1, "SeriesFlags" },
{ 0x0009, 0x0022, 0, VR::SH, VM::M1, "UserOrientation" },
{ 0x0009, 0x0023, 0, VR::SL, VM::M1, "InitiationType" },
{ 0x0009, 0x0024, 0, VR::SL, VM::M1, "InitiationDelay" },
{ 0x0009, 0x0025, 0, VR::SL, VM::M1, "InitiationCountRate" },
{ 0x0009, 0x0026, 0, VR::SL, VM::M1, "NumberEnergySets" },
{ 0x0009, 0x0027, 0, VR::SL, VM::M1, "NumberDetectors" },
{ 0x0009, 0x0028, 0, VR::SL, VM::M1, "NumberRRWindows" },
{ 0x0009, 0x0029, 0, VR::SL, VM::M1, "NumberMGTimeSlots" },
{ 0x0009, 0x002a, 0, VR::SL, VM::M1, "NumberViewSets" },
{ 0x0009, 0x002b, 0, VR::LO, VM::M1, "TriggerHistoryUID" },
{ 0x0009, 0x002c, 0, VR::LO, VM::M1, "SeriesComments" },
{ 0x0009, 0x002d, 0, VR::SL, VM::M1, "TrackBeatAverage" },
{ 0x0009, 0x002e, 0, VR::FD, VM::M1, "DistancePrescribed" },
{ 0x0009, 0x002f, 0, VR::SL, VM::M1, "TableDirection" },
{ 0x0009, 0x0030, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0033, 0, VR::FD, VM::M1, "RotationalContinuousSpeed" },
{ 0x0009, 0x0034, 0, VR::SL, VM::M1, "GantryMotionTypeRetired" },
{ 0x0009, 0x0035, 0, VR::SL, VM::M1, "GantryLocusType" },
{ 0x0009, 0x0037, 0, VR::SL, VM::M1, "StartingHeartRate" },
{ 0x0009, 0x0038, 0, VR::SL, VM::M1, "RRWindowWidth" },
{ 0x0009, 0x0039, 0, VR::SL, VM::M1, "RRWindowOffset" },
{ 0x0009, 0x003a, 0, VR::SL, VM::M1, "PercentCycleImaged" },
{ 0x0009, 0x0040, 0, VR::PN, VM::M1, "PatientObjectName" },
{ 0x0009, 0x0041, 0, VR::SL, VM::M1, "PatientFlags" },
{ 0x0009, 0x0042, 0, VR::DA, VM::M1, "PatientCreationDate" },
{ 0x0009, 0x0043, 0, VR::TM, VM::M1, "PatientCreationTime" },
{ 0x0009, 0x0044, 0, VR::SL, VM::M1, "NumViewsAcquiredRetired" },
{ 0x0009, 0x0045, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x0046, 0, VR::UI, VM::M1, "" },
{ 0x0011, 0x000a, 0, VR::SL, VM::M1, "SeriesType" },
{ 0x0011, 0x000b, 0, VR::SL, VM::M1, "EffectiveSeriesDuration" },
{ 0x0011, 0x000c, 0, VR::SL, VM::M1, "NumBeats" },
{ 0x0011, 0x000d, 0, VR::LO, VM::M1, "RadioNuclideName" },
{ 0x0011, 0x0010, 0, VR::LO, VM::M1, "DatasetObjectName" },
{ 0x0011, 0x0011, 0, VR::SL, VM::M1, "DatasetModified" },
{ 0x0011, 0x0012, 0, VR::LO, VM::M1, "DatasetName" },
{ 0x0011, 0x0013, 0, VR::SL, VM::M1, "DatasetType" },
{ 0x0011, 0x0014, 0, VR::LO, VM::M1, "CompletionTime" },
{ 0x0011, 0x0015, 0, VR::SL, VM::M1, "DetectorNumber" },
{ 0x0011, 0x0016, 0, VR::SL, VM::M1, "EnergyNumber" },
{ 0x0011, 0x0017, 0, VR::SL, VM::M1, "RRIntervalWindowNumber" },
{ 0x0011, 0x0018, 0, VR::SL, VM::M1, "MGBinNumber" },
{ 0x0011, 0x0019, 0, VR::FD, VM::M1, "RadiusOfRotation" },
{ 0x0011, 0x001a, 0, VR::SL, VM::M1, "DetectorCountZone" },
{ 0x0011, 0x001b, 0, VR::SL, VM::M1, "NumEnergyWindows" },
{ 0x0011, 0x001c, 0, VR::SL, VM::M4, "EnergyOffset" },
{ 0x0011, 0x001d, 0, VR::SL, VM::M1, "EnergyRange" },
{ 0x0011, 0x001e, 0, VR::SL, VM::M4, "EnergyWidthRetired" },
{ 0x0011, 0x001f, 0, VR::SL, VM::M1, "ImageOrientation" },
{ 0x0011, 0x0021, 0, VR::DS, VM::M1, "AcqZoomRetired" },
{ 0x0011, 0x0022, 0, VR::DS, VM::M1, "AcqPanRetired" },
{ 0x0011, 0x0023, 0, VR::SL, VM::M1, "UseFOVMask" },
{ 0x0011, 0x0024, 0, VR::SL, VM::M1, "FOVMaskYCutoffAngle" },
{ 0x0011, 0x0025, 0, VR::SL, VM::M1, "FOVMaskCutoffAngle" },
{ 0x0011, 0x0026, 0, VR::SL, VM::M1, "TableOrientation" },
{ 0x0011, 0x0027, 0, VR::SL, VM::M2, "ROITopLeft" },
{ 0x0011, 0x0028, 0, VR::SL, VM::M2, "ROIBottomRight" },
{ 0x0011, 0x0029, 0, VR::SL, VM::M1, "UniformityMean" },
{ 0x0011, 0x002a, 0, VR::FD, VM::M1, "PhaseDurationRetired" },
{ 0x0011, 0x002c, 0, VR::FD, VM::M1, "ViewXAdjustment" },
{ 0x0011, 0x002d, 0, VR::FD, VM::M1, "ViewYAdjustment" },
{ 0x0011, 0x002e, 0, VR::SL, VM::M1, "PixelOverflowFlag" },
{ 0x0011, 0x002f, 0, VR::SL, VM::M1, "OverflowLevel" },
{ 0x0011, 0x0030, 0, VR::LO, VM::M1, "PictureObjectName" },
{ 0x0011, 0x0031, 0, VR::LO, VM::M1, "AcquisitionParentUID" },
{ 0x0011, 0x0032, 0, VR::LO, VM::M1, "ProcessingParentUID" },
{ 0x0011, 0x0033, 0, VR::LO, VM::M1, "EnergyCorrectName" },
{ 0x0011, 0x0034, 0, VR::LO, VM::M1, "SpatialCorrectName" },
{ 0x0011, 0x0035, 0, VR::LO, VM::M1, "TuningCalibName" },
{ 0x0011, 0x0036, 0, VR::LO, VM::M1, "UniformityCorrectName" },
{ 0x0011, 0x0037, 0, VR::LT, VM::M1, "AcquisitionSpecificCorrectName" },
{ 0x0011, 0x0038, 0, VR::SL, VM::M1, "ByteOrder" },
{ 0x0011, 0x0039, 0, VR::SL, VM::M1, "CompressionType" },
{ 0x0011, 0x003a, 0, VR::SL, VM::M1, "PictureFormat" },
{ 0x0011, 0x003b, 0, VR::FD, VM::M1, "PixelScale" },
{ 0x0011, 0x003c, 0, VR::FD, VM::M1, "PixelOffset" },
{ 0x0011, 0x003d, 0, VR::SL, VM::M4, "EnergyPeakRetired" },
{ 0x0011, 0x003e, 0, VR::SL, VM::M1, "FOVShape" },
{ 0x0011, 0x003f, 0, VR::SL, VM::M1, "DatasetFlags" },
{ 0x0011, 0x0040, 0, VR::LO, VM::M1, "ViewingObjectName" },
{ 0x0011, 0x0041, 0, VR::SL, VM::M1, "OrientationAngle" },
{ 0x0011, 0x0042, 0, VR::FD, VM::M1, "RotationAngle" },
{ 0x0011, 0x0043, 0, VR::SL, VM::M1, "WindowInverseFlag" },
{ 0x0011, 0x0044, 0, VR::FD, VM::M1, "ThresholdCenter" },
{ 0x0011, 0x0045, 0, VR::FD, VM::M1, "ThresholdWidth" },
{ 0x0011, 0x0046, 0, VR::SL, VM::M1, "InterpolationType" },
{ 0x0011, 0x0050, 0, VR::LO, VM::M1, "WhereObjectName" },
{ 0x0011, 0x0055, 0, VR::FD, VM::M1, "Period" },
{ 0x0011, 0x0056, 0, VR::FD, VM::M1, "ElapsedTime" },
{ 0x0011, 0x0057, 0, VR::FD, VM::M2, "FOV" },
{ 0x0011, 0x0061, 0, VR::SL, VM::M1, "ImageSize" },
{ 0x0011, 0x0062, 0, VR::FD, VM::M1, "LinearFOV" },
{ 0x0011, 0x0063, 0, VR::FD, VM::M1, "SpatialOffset" },
{ 0x0011, 0x0064, 0, VR::FD, VM::M1, "SpatialOrientation" },
{ 0x0011, 0x0065, 0, VR::LO, VM::M1, "ReferenceDatasetUID" },
{ 0x0011, 0x0066, 0, VR::SH, VM::M1, "StarcamReferenceDataset" },
{ 0x0011, 0x0067, 0, VR::SL, VM::M1, "ReferenceFrameNumber" },
{ 0x0011, 0x0068, 0, VR::SL, VM::M1, "CursorLength" },
{ 0x0011, 0x0069, 0, VR::SL, VM::M1, "NumberOfCursors" },
{ 0x0011, 0x006a, 0, VR::SL, VM::M1, "CursorCoordinates" },
{ 0x0011, 0x006b, 0, VR::SL, VM::M1, "ReconOptionsFlag" },
{ 0x0011, 0x006c, 0, VR::FD, VM::M1, "MotionThreshold" },
{ 0x0011, 0x006d, 0, VR::UI, VM::M1, "MotionCurveUID" },
{ 0x0011, 0x006e, 0, VR::SL, VM::M1, "ReconType" },
{ 0x0011, 0x006f, 0, VR::SL, VM::M1, "PreFilterType" },
{ 0x0011, 0x0071, 0, VR::SL, VM::M1, "BackProjFilterType" },
{ 0x0011, 0x0072, 0, VR::SL, VM::M1, "ReconArc" },
{ 0x0011, 0x0073, 0, VR::FD, VM::M1, "ReconPanAPOffset" },
{ 0x0011, 0x0074, 0, VR::FD, VM::M1, "ReconPanLROffset" },
{ 0x0011, 0x0075, 0, VR::FD, VM::M1, "ReconArea" },
{ 0x0011, 0x0076, 0, VR::SL, VM::M1, "StartView" },
{ 0x0011, 0x0077, 0, VR::SL, VM::M1, "AttenuationType" },
{ 0x0011, 0x0078, 0, VR::SL, VM::M1, "DualEnergyProcessing" },
{ 0x0011, 0x0079, 0, VR::SH, VM::M1, "PreFilterParam" },
{ 0x0011, 0x007a, 0, VR::SH, VM::M1, "PreFilterParam2" },
{ 0x0011, 0x007b, 0, VR::SH, VM::M1, "BackProjFilterParam" },
{ 0x0011, 0x007c, 0, VR::SH, VM::M1, "BackProjFilterParam2" },
{ 0x0011, 0x007d, 0, VR::SH, VM::M1, "AttenuationCoef" },
{ 0x0011, 0x007e, 0, VR::SL, VM::M1, "RefSliceWidth" },
{ 0x0011, 0x007f, 0, VR::FD, VM::M1, "RefTransPixelVolume" },
{ 0x0011, 0x0081, 0, VR::SH, VM::M1, "AttenuationThreshold" },
{ 0x0011, 0x0082, 0, VR::FD, VM::M1, "InterpolationDistance" },
{ 0x0011, 0x0083, 0, VR::FD, VM::M1, "InterpolationCenterX" },
{ 0x0011, 0x0084, 0, VR::FD, VM::M1, "InterpolationCenterY" },
{ 0x0011, 0x0085, 0, VR::SL, VM::M1, "QuantFilterFlag" },
{ 0x0011, 0x0086, 0, VR::SL, VM::M1, "HeadConversion" },
{ 0x0011, 0x0087, 0, VR::SL, VM::M1, "SliceWidthPixels" },
{ 0x0011, 0x0088, 0, VR::SL, VM::M1, "RfmtrTransRef" },
{ 0x0011, 0x0089, 0, VR::FD, VM::M1, "RfmtrTransRefmm" },
{ 0x0011, 0x008a, 0, VR::SL, VM::M1, "TwoLineTransRef" },
{ 0x0011, 0x008b, 0, VR::SL, VM::M1, "ThreeDZero" },
{ 0x0011, 0x008c, 0, VR::SL, VM::M1, "ThreeDZeroLength" },
{ 0x0011, 0x008d, 0, VR::SL, VM::M1, "ThreeDZeroIn" },
{ 0x0013, 0x0010, 0, VR::FD, VM::M2, "DigitalFOV" },
{ 0x0013, 0x0011, 0, VR::SL, VM::M1, "SourceTranslator" },
{ 0x0013, 0x0012, 0, VR::SL, VM::M1, "RALFlags" },
{ 0x0013, 0x0013, 0, VR::SQ, VM::M1, "eNTEGRAFrameSequence" },
{ 0x0013, 0x0014, 0, VR::SL, VM::M1, "OriginalImageNumber" },
{ 0x0013, 0x0015, 0, VR::FD, VM::M1, "Fscalar" },
{ 0x0013, 0x0016, 0, VR::SL, VM::M1, "AutoTrackPeak" },
{ 0x0013, 0x0017, 0, VR::SL, VM::M1, "AutoTrackWidth" },
{ 0x0013, 0x0018, 0, VR::FD, VM::M1, "TransmissionScanTime" },
{ 0x0013, 0x0019, 0, VR::FD, VM::M1, "TransmissionMaskWidth" },
{ 0x0013, 0x001a, 0, VR::FD, VM::M1, "CopperAttenuatorThickness" },
{ 0x0013, 0x001b, 0, VR::FD, VM::M1, "DetAngSeparation" },
{ 0x0013, 0x001c, 0, VR::SL, VM::M1, "AxialAcceptanceAngle" },
{ 0x0013, 0x001d, 0, VR::SL, VM::M1, "ThetaAcceptanceValue" },
{ 0x0013, 0x001e, 0, VR::FD, VM::M1TN, "TomoViewOffset" },
{ 0x0013, 0x0020, 0, VR::FD, VM::M1, "AcceptedBeatsTime" },
{ 0x0013, 0x0021, 0, VR::FD, VM::M2, "Threshold" },
{ 0x0013, 0x0022, 0, VR::FD, VM::M2, "LinearDepth" },
{ 0x0013, 0x0023, 0, VR::LO, VM::M1, "UnifDateTime" },
{ 0x0013, 0x0024, 0, VR::SL, VM::M1, "SeriesAcceptedBeats" },
{ 0x0013, 0x0025, 0, VR::SL, VM::M1, "SeriesRejectedBeats" },
{ 0x0013, 0x0026, 0, VR::LT, VM::M1, "StudyComments" },
{ 0x0015, 0x0010, 0, VR::SL, VM::M1, "FrameTerminationCondition" },
{ 0x0015, 0x0011, 0, VR::SL, VM::M1, "FrameTerminationValue" },
{ 0x0015, 0x0012, 0, VR::SL, VM::M1, "NumECTPhases" },
{ 0x0015, 0x0013, 0, VR::SL, VM::M1, "NumWBScans" },
{ 0x0015, 0x0014, 0, VR::SL, VM::M1, "ECTPhaseNum" },
{ 0x0015, 0x0015, 0, VR::SL, VM::M1, "WBScanNum" },
{ 0x0015, 0x0016, 0, VR::SL, VM::M1, "CombHeadNumber" },
{ 0x0015, 0x0017, 0, VR::UL, VM::M1, "PrecedingBeat" },
{ 0x0019, 0x005f, 0, VR::SQ, VM::M1, "" },
{ 0x0033, 0x0007, 0, VR::LO, VM::M1TN, "OriginalSOPInstanceUID" },
{ 0x0033, 0x0008, 0, VR::CS, VM::M1, "eNTEGRADataObjectType" },
{ 0x0033, 0x0010, 0, VR::SL, VM::M1, "Modified" },
{ 0x0033, 0x0011, 0, VR::LO, VM::M1, "Name" },
{ 0x0033, 0x0016, 0, VR::LO, VM::M1, "ProtocolDataUID" },
{ 0x0033, 0x0017, 0, VR::SH, VM::M1, "Date" },
{ 0x0033, 0x0018, 0, VR::SH, VM::M1, "Time" },
{ 0x0033, 0x0019, 0, VR::UL, VM::M1, "ProtocolDataFlags" },
{ 0x0033, 0x001a, 0, VR::UL, VM::M1, "ProtocolName" },
{ 0x0033, 0x001b, 0, VR::LO, VM::M1, "RelevantDataUID" },
{ 0x0033, 0x001c, 0, VR::LO, VM::M1, "BulkData" },
{ 0x0033, 0x001d, 0, VR::SL, VM::M1TN, "IntData" },
{ 0x0033, 0x001e, 0, VR::FD, VM::M1TN, "DoubleData" },
{ 0x0033, 0x001f, 0, VR::OB, VM::M1, "StringData" },
{ 0x0033, 0x0020, 0, VR::LT, VM::M1TN, "BulkDataFormat" },
{ 0x0033, 0x0021, 0, VR::LT, VM::M1TN, "IntDataFormat" },
{ 0x0033, 0x0022, 0, VR::LT, VM::M1TN, "DoubleDataFormat" },
{ 0x0033, 0x0023, 0, VR::LT, VM::M1TN, "StringDataFormat" },
{ 0x0033, 0x0024, 0, VR::LT, VM::M1, "Description" },
{ 0x0033, 0x0030, 0, VR::UL, VM::M1, "AllocateTriggerBuffer" },
{ 0x0033, 0x0033, 0, VR::UL, VM::M1, "NumberOfTriggers" },
{ 0x0033, 0x0034, 0, VR::UL, VM::M1, "TriggerSize" },
{ 0x0033, 0x0035, 0, VR::UL, VM::M1, "TriggerDataSize" },
{ 0x0033, 0x0036, 0, VR::OB, VM::M1, "TriggerData" },
{ 0x0035, 0x0001, 0, VR::FD, VM::M1TN, "StartAngle" },
{ 0x0055, 0x0012, 0, VR::SQ, VM::M1, "eNTEGRAEnergyWindowInformationSequence" },
{ 0x0055, 0x0013, 0, VR::SQ, VM::M1, "eNTEGRAEnergyWindowRangeSequence" },
{ 0x0055, 0x0022, 0, VR::SQ, VM::M1, "eNTEGRADetectorInformationSequence" },
{ 0x0055, 0x0052, 0, VR::SQ, VM::M1, "eNTEGRARotationInformationSequence" },
{ 0x0055, 0x0062, 0, VR::SQ, VM::M1, "eNTEGRAGatedInformationSequence" },
{ 0x0055, 0x0063, 0, VR::SQ, VM::M1, "eNTEGRADataInformationSequence" },
{ 0x0055, 0x0064, 0, VR::SQ, VM::M1, "SDODoubleDataSequence" },
{ 0x0055, 0x0065, 0, VR::SQ, VM::M1, "" },
{ 0x5001, 0x0001, 0, VR::SL, VM::M1, "Modified" },
{ 0x5001, 0x0002, 0, VR::LO, VM::M1, "Name" },
{ 0x5001, 0x0003, 0, VR::SL, VM::M1, "Cid" },
{ 0x5001, 0x0004, 0, VR::SL, VM::M1, "Srid" },
{ 0x5001, 0x0005, 0, VR::LO, VM::M1, "SOPClassUID" },
{ 0x5001, 0x0006, 0, VR::LO, VM::M1, "SOPInstanceUID" },
{ 0x5001, 0x0007, 0, VR::SL, VM::M1, "CurveType" },
{ 0x5001, 0x0008, 0, VR::SL, VM::M1, "GraphType" },
{ 0x5001, 0x0009, 0, VR::LO, VM::M1, "Legend" },
{ 0x5001, 0x000a, 0, VR::LO, VM::M1, "XUnits" },
{ 0x5001, 0x000b, 0, VR::LO, VM::M1, "YUnits" },
{ 0x5001, 0x000c, 0, VR::SL, VM::M1, "Edit" },
{ 0x5001, 0x000d, 0, VR::SL, VM::M1, "Suspend" },
{ 0x5001, 0x000e, 0, VR::SL, VM::M1, "StyleLine" },
{ 0x5001, 0x000f, 0, VR::SL, VM::M1, "StyleFill" },
{ 0x5001, 0x0010, 0, VR::LO, VM::M1, "StyleColour" },
{ 0x5001, 0x0011, 0, VR::SL, VM::M1, "StyleWidth" },
{ 0x5001, 0x0012, 0, VR::SL, VM::M1, "StylePoint" },
{ 0x5001, 0x0013, 0, VR::LO, VM::M1, "StylePColour" },
{ 0x5001, 0x0014, 0, VR::SL, VM::M1, "StylePSize" },
{ 0x5001, 0x0015, 0, VR::SL, VM::M1, "Segments" },
{ 0x5001, 0x0016, 0, VR::SL, VM::M1, "SegType" },
{ 0x5001, 0x0017, 0, VR::FD, VM::M1TN, "SegStart" },
{ 0x5001, 0x0018, 0, VR::FD, VM::M1TN, "SegEnd" },
{ 0x5001, 0x0019, 0, VR::SL, VM::M1TN, "SegStyleLine" },
{ 0x5001, 0x001a, 0, VR::SL, VM::M1TN, "SegStyleFill" },
{ 0x5001, 0x001b, 0, VR::LO, VM::M1, "SegStyleColour" },
{ 0x5001, 0x001c, 0, VR::SL, VM::M1TN, "SegStyleWidth" },
{ 0x5001, 0x001d, 0, VR::SL, VM::M1TN, "SegStylePoint" },
{ 0x5001, 0x001e, 0, VR::SL, VM::M1, "SegStylePColour" },
{ 0x5001, 0x001f, 0, VR::SL, VM::M1, "SegStylePSize" },
{ 0x5001, 0x0020, 0, VR::LO, VM::M1, "SegName" },
{ 0x5001, 0x0021, 0, VR::SL, VM::M1TN, "SegAllowDirInt" },
{ 0x5001, 0x0022, 0, VR::SL, VM::M1, "TextAnnots" },
{ 0x5001, 0x0023, 0, VR::FD, VM::M1TN, "TxtX" },
{ 0x5001, 0x0024, 0, VR::FD, VM::M1TN, "TxtY" },
{ 0x5001, 0x0025, 0, VR::LO, VM::M1, "TxtText" },
{ 0x5001, 0x0026, 0, VR::LO, VM::M1, "TxtName" },
{ 0x5001, 0x0030, 0, VR::LO, VM::M1, "ROIName" },
{ 0x5001, 0x0031, 0, VR::LO, VM::M1, "DerivedFromImageUID" },
{ 0x5001, 0x0032, 0, VR::SL, VM::M1TN, "DerivedFromImages" },
{ 0x5001, 0x0033, 0, VR::UL, VM::M1, "CurveFlags" },
{ 0x5001, 0x0034, 0, VR::LO, VM::M1, "CurveName" },
{ 0x5001, 0x0035, 0, VR::LO, VM::M1, "DatasetName" },
{ 0x5001, 0x0036, 0, VR::LO, VM::M1, "CurveUID" },
{ 0x5001, 0x0037, 0, VR::FD, VM::M1, "ROIArea" },
{ 0x5001, 0x0038, 0, VR::LO, VM::M1, "Modified" },
{ 0x5001, 0x0039, 0, VR::LO, VM::M1, "Name" },
{ 0x5001, 0x003a, 0, VR::LO, VM::M1, "SoftwareVersion" },
{ 0x5001, 0x003b, 0, VR::SH, VM::M1, "StartDate" },
{ 0x5001, 0x003c, 0, VR::SH, VM::M1, "CompletionDate" },
{ 0x5001, 0x003d, 0, VR::LO, VM::M1, "DetectorName" },
{ 0x5001, 0x0041, 0, VR::SL, VM::M1, "Modified" },
{ 0x5001, 0x0042, 0, VR::LO, VM::M1, "Name" },
{ 0x5001, 0x0043, 0, VR::SL, VM::M1, "Name" },
{ 0x5001, 0x0044, 0, VR::SL, VM::M1, "Name" },
{ 0x5001, 0x0045, 0, VR::LO, VM::M1, "SOPClassUID" },
{ 0x5001, 0x0046, 0, VR::LO, VM::M1, "SOPInstanceUID" },
{ 0x5001, 0x0047, 0, VR::LO, VM::M1, "NormalColor" },
{ 0x5001, 0x0048, 0, VR::LT, VM::M1, "NameFont" },
{ 0x5001, 0x0049, 0, VR::SL, VM::M1, "FillPattern" },
{ 0x5001, 0x004a, 0, VR::SL, VM::M1, "LineStyle" },
{ 0x5001, 0x004b, 0, VR::SL, VM::M1, "LineDashLength" },
{ 0x5001, 0x004c, 0, VR::SL, VM::M1, "LineThickness" },
{ 0x5001, 0x004d, 0, VR::SL, VM::M1, "Interactivity" },
{ 0x5001, 0x004e, 0, VR::SL, VM::M1, "NamePos" },
{ 0x5001, 0x004f, 0, VR::SL, VM::M1, "NameDisplay" },
{ 0x5001, 0x0050, 0, VR::LO, VM::M1, "Label" },
{ 0x5001, 0x0051, 0, VR::SL, VM::M1TN, "BpSeg" },
{ 0x5001, 0x0052, 0, VR::US, VM::M1TN, "BpSegPairs" },
{ 0x5001, 0x0053, 0, VR::SL, VM::M1, "SeedSpace" },
{ 0x5001, 0x0054, 0, VR::FD, VM::M1TN, "Seeds" },
{ 0x5001, 0x0055, 0, VR::SL, VM::M1TN, "Shape" },
{ 0x5001, 0x0056, 0, VR::FD, VM::M1TN, "ShapeTilt" },
{ 0x5001, 0x0059, 0, VR::SL, VM::M1TN, "ShapePtsSpace" },
{ 0x5001, 0x005a, 0, VR::SL, VM::M1TN, "ShapeCtrlPtsCounts" },
{ 0x5001, 0x005b, 0, VR::FD, VM::M1TN, "ShapeCtrlPts" },
{ 0x5001, 0x005c, 0, VR::SL, VM::M1, "ShapeCtrlPSpace" },
{ 0x5001, 0x005d, 0, VR::SL, VM::M1, "ROIFlags" },
{ 0x5001, 0x005e, 0, VR::SL, VM::M1, "FrameNumber" },
{ 0x5001, 0x005f, 0, VR::SL, VM::M1, "ID" },
{ 0x5001, 0x0060, 0, VR::LO, VM::M1TN, "DatasetROIMapping" },
};

unsigned short Dict341TagHashTable[] = {
   72,    89,   100,   113,   128,   141,   156,   173,   192,   205,
  218,   231,   244,   255,   268,   279,   290,   299,   308,   315,
  322,   327,   332,   337,   346,   353,   360,   369,   378,   385,
  394,   401,   408,   419,   430,   443,   454,   467,   476,   483,
  490,   499,   506,   515,   524,   533,   544,   555,   568,   581,
  592,   601,   612,   623,   632,   643,   654,   661,   668,   673,
  678,   683,   688,   693,   696,    71,    71,    71,   699,   702,
  705,     0,     8,    41,    17,    96,    87,   143,    19,   167,
   21,   170,    95,   191,    51,   197,    19,   205,     2,     5,
   29,    64,    40,    16,   142,    18,   166,    20,   208,     5,
    6,    30,    65,    43,    19,   129,   131,   141,    17,   169,
   23,   207,     4,     7,    31,    66,    42,    18,   128,   130,
  140,    16,   168,    22,   190,    48,   210,     7,     6,    32,
   67,    45,    21,   127,   129,   147,    23,   163,    17,   209,
    6,     7,    33,    68,    44,    20,   146,    22,   162,    16,
  194,    54,   212,     9,   256,    65,     8,    34,    69,    47,
   23,   133,   135,   145,    21,   165,    19,   193,    53,   211,
    8,   257,    66,     9,    35,    70,    46,    22,   132,   134,
  144,    20,   164,    18,   192,    52,   199,    82,   214,    11,
  258,    67,     6,     0,     1,    49,    25,   131,   133,   151,
   27,   213,    10,   259,    68,     6,    48,    24,    86,    64,
  130,   132,   150,    26,   216,    13,   260,    69,     6,    51,
   27,    87,    65,   137,   139,   149,    25,   215,    12,   261,
   70,     6,    50,    26,    88,    66,   136,   138,   148,    24,
  218,    15,   262,    71,     5,    53,    29,    89,    67,   135,
  137,   217,    14,   263,    72,     6,    52,    28,    90,    68,
  134,   136,   154,    30,   220,    17,   264,    73,     5,    55,
   31,    91,    69,   153,    29,   219,    16,   265,    74,     5,
   54,    30,    92,    70,   152,    28,   222,    19,   266,    75,
    4,   139,   141,   188,    35,   221,    18,   267,    76,     4,
  138,   140,   187,    34,   224,    21,   268,    77,     3,   186,
   33,   223,    20,   269,    78,     3,   185,    32,   226,    23,
  270,    79,     2,   225,    22,   271,    80,     2,   228,    25,
  272,    81,     2,   227,    24,   273,    82,     4,     4,    30,
  189,    36,   230,    27,   274,    83,     3,     2,    17,   229,
   26,   275,    84,     3,     1,    16,   232,    29,   276,    85,
    4,    37,    11,   112,   113,   231,    28,   277,    86,     4,
    3,    18,    36,    10,   113,   114,   234,    31,     3,    39,
   13,   114,   115,   233,    30,     4,    38,    12,   115,   116,
  236,    33,   278,    89,     3,   116,   117,   235,    32,   279,
   90,     3,   117,   118,   238,    35,   280,    91,     5,    14,
   41,    71,    49,   118,   119,   237,    34,   281,    92,     5,
   13,    40,    70,    48,   119,   120,   240,    37,   282,    93,
    6,    16,    43,    73,    51,   120,   121,   174,    17,   239,
   36,   283,    94,     5,    15,    42,    72,    50,   121,   122,
  173,    16,   284,    95,     6,    18,    45,    75,    53,   122,
  123,   176,    23,   241,    38,   285,    96,     4,    17,    44,
   74,    52,   123,   124,   175,    22,     3,    20,    47,    77,
   55,   124,   125,     3,    19,    46,    76,    54,   125,   126,
    4,     6,    33,    79,    57,   126,   127,   180,    27,     3,
    5,    32,    78,    56,   179,    26,     4,     8,    35,    81,
   59,    97,    97,   178,    25,     4,     7,    34,    80,    58,
   98,    98,   177,    24,     4,    10,    37,    83,    61,    99,
   99,   184,    31,     5,     9,    36,    82,    60,   100,   100,
  183,    30,   243,    49,     5,    12,    39,    85,    63,   101,
  101,   182,    29,   242,    48,     6,    11,    38,    84,    62,
  102,   102,   181,    28,   198,    34,   245,    51,     6,    27,
   57,    56,    33,   103,   103,   158,    35,   203,   101,   244,
   50,     5,    26,    56,   104,   104,   157,    34,   202,   100,
  247,    53,     4,    58,    35,   105,   105,   156,    33,   246,
   52,     5,    28,    58,    57,    34,   106,   106,   155,    32,
  249,    55,     5,    60,    37,   107,   107,   171,     7,   195,
    1,   248,    54,     4,    59,    36,   108,   108,   161,    38,
  251,    57,     5,    62,    39,   109,   109,   160,    37,   201,
   99,   250,    56,     5,    61,    38,   110,   110,   159,    36,
  200,    98,   253,    59,     3,    64,    41,   111,   111,   252,
   58,     3,    21,    48,    63,    40,   255,    61,     2,    22,
   51,   254,    60,     2,    65,    42,   172,     8,     2,    24,
   53,    67,    45,     2,    23,    52,    66,    44,     2,    25,
   55,    69,    47,     1,    68,    46,     1,    93,    80,     1,
  204,     1,     1,    94,    85,     3,    95,    86,   196,    18,
  206,     3,
};

vtkDICOMDictionary::Dict Dict341Data = {
"GEMS_GENIE_1",
71,
286,
Dict341TagHashTable,
Dict341Contents
};

// ----- SCHICK TECHNOLOGIES - Image Security Creator ID -----

DictEntry Dict342Contents[] = {
{ 0x0029, 0x0001, 0, VR::UL, VM::M1, "" },
};

unsigned short Dict342TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict342Data = {
"SCHICK TECHNOLOGIES - Image Security Creator ID",
1,
1,
Dict342TagHashTable,
Dict342Contents
};

// ----- Hologic -----

DictEntry Dict343Contents[] = {
{ 0x0011, 0x0000, 0, VR::LO, VM::M1, "HxQuestionnaire" },
{ 0x0021, 0x0001, 0, VR::LT, VM::M1, "ImageAnalysisDataInXML" },
{ 0x0023, 0x0000, 0, VR::LO, VM::M1, "EncodingSchemeVersion" },
{ 0x0023, 0x0001, 0, VR::LO, VM::M1, "PFileName" },
{ 0x0023, 0x0002, 0, VR::OB, VM::M1, "PFileData" },
{ 0x0023, 0x0003, 0, VR::UL, VM::M1, "PFileLength" },
{ 0x0023, 0x0004, 0, VR::OB, VM::M1, "RFileData" },
{ 0x0023, 0x0005, 0, VR::UL, VM::M1, "RFileLength" },
};

unsigned short Dict343TagHashTable[] = {
    3,    12,     0,     4,     1,     1,     3,     1,     5,     3,
    7,     5,     4,     0,     0,     2,     0,     4,     2,     6,
    4,
};

vtkDICOMDictionary::Dict Dict343Data = {
"Hologic",
2,
8,
Dict343TagHashTable,
Dict343Contents
};

// ----- GEMS_DL_PATNT_01 -----

DictEntry Dict344Contents[] = {
{ 0x0011, 0x0080, 0, VR::UI, VM::M1, "PatientInstanceUid" },
{ 0x0011, 0x0081, 0, VR::IS, VM::M1, "LastStudyNumber" },
{ 0x0011, 0x0082, 0, VR::CS, VM::M1, "PatientRepaired" },
{ 0x0011, 0x0083, 0, VR::CS, VM::M1, "LockDemographics" },
};

unsigned short Dict344TagHashTable[] = {
    2,     0,     4,     0,   128,     1,   129,     2,   130,     3,
  131,
};

vtkDICOMDictionary::Dict Dict344Data = {
"GEMS_DL_PATNT_01",
1,
4,
Dict344TagHashTable,
Dict344Contents
};

// ----- SIEMENS SYNGO FRAME SET -----

DictEntry Dict345Contents[] = {
{ 0x0029, 0x0010, 0, VR::SQ, VM::M1, "ImageFrameSequence" },
{ 0x0029, 0x0012, 0, VR::CS, VM::M1, "TypeOfProgression" },
{ 0x0029, 0x0014, 0, VR::IS, VM::M1, "RepresentationLevel" },
{ 0x0029, 0x0016, 0, VR::SQ, VM::M1, "RepresentationInformationSequence" },
{ 0x0029, 0x0018, 0, VR::IS, VM::M1, "NumberOfRepresentations" },
{ 0x0029, 0x0020, 0, VR::IS, VM::M1, "RepresentationPixelOffset" },
};

unsigned short Dict345TagHashTable[] = {
    2,     0,     6,     0,    16,     1,    18,     2,    20,     3,
   22,     4,    24,     5,    32,
};

vtkDICOMDictionary::Dict Dict345Data = {
"SIEMENS SYNGO FRAME SET",
1,
6,
Dict345TagHashTable,
Dict345Contents
};

// ----- SIEMENS MR CM 03 -----

DictEntry Dict346Contents[] = {
{ 0x0021, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict346TagHashTable[] = {
    2,     0,     2,     0,     1,     1,     2,
};

vtkDICOMDictionary::Dict Dict346Data = {
"SIEMENS MR CM 03",
1,
2,
Dict346TagHashTable,
Dict346Contents
};

// ----- SIEMENS Ultrasound SC2000 -----

DictEntry Dict347Contents[] = {
{ 0x0019, 0x002D, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0089, 0, VR::LO, VM::M1, "" },
{ 0x0119, 0x0000, 0, VR::LO, VM::M1, "AcousticMetaInformationVersion" },
{ 0x0119, 0x0001, 0, VR::UN, VM::M1, "CommonAcousticMetaInformation" },
{ 0x0119, 0x0002, 0, VR::SQ, VM::M1, "MultiStreamSequence" },
{ 0x0119, 0x0003, 0, VR::SQ, VM::M1, "AcousticDataSequence" },
{ 0x0119, 0x0004, 0, VR::UN, VM::M1, "PerTransactionAcousticControlInformation" },
{ 0x0119, 0x0005, 0, VR::UN, VM::M1, "AcousticDataOffset" },
{ 0x0119, 0x0006, 0, VR::UN, VM::M1, "AcousticDataLength" },
{ 0x0119, 0x0007, 0, VR::UN, VM::M1, "FooterOffset" },
{ 0x0119, 0x0008, 0, VR::UN, VM::M1, "FooterLength" },
{ 0x0119, 0x0009, 0, VR::UN, VM::M1, "AcousticStreamNumber" },
{ 0x0119, 0x0010, 0, VR::UN, VM::M1, "AcousticStreamType" },
{ 0x0119, 0x0013, 0, VR::UN, VM::M1, "VolumeRate" },
{ 0x0129, 0x0000, 0, VR::SQ, VM::M1, "MPRViewSequence" },
{ 0x0129, 0x0002, 0, VR::UI, VM::M1, "BookmarkUID" },
{ 0x0129, 0x0003, 0, VR::UN, VM::M1, "PlaneOriginVector" },
{ 0x0129, 0x0004, 0, VR::UN, VM::M1, "RowVector" },
{ 0x0129, 0x0005, 0, VR::UN, VM::M1, "ColumnVector" },
{ 0x0129, 0x0006, 0, VR::SQ, VM::M1, "VisualizationSequence" },
{ 0x0129, 0x0007, 0, VR::UI, VM::M1, "BookmarkUID" },
{ 0x0129, 0x0008, 0, VR::UN, VM::M1, "VisualizationInformation" },
{ 0x0129, 0x0009, 0, VR::SQ, VM::M1, "ApplicationStateSequence" },
{ 0x0129, 0x0010, 0, VR::OB, VM::M1, "ApplicationStateInformation" },
{ 0x0129, 0x0011, 0, VR::SQ, VM::M1, "ReferencedBookmarkSequence" },
{ 0x0129, 0x0012, 0, VR::UI, VM::M1, "ReferencedBookmarkUID" },
{ 0x0129, 0x0020, 0, VR::UN, VM::M1, "CineParameters" },
{ 0x0129, 0x0021, 0, VR::UN, VM::M1, "AcquisitionUIData" },
{ 0x0129, 0x0030, 0, VR::CS, VM::M1, "RawDataObjectType" },
{ 0x0139, 0x0001, 0, VR::SL, VM::M1, "" },
{ 0x0149, 0x0001, 0, VR::FD, VM::M1TN, "" },
{ 0x0149, 0x0002, 0, VR::FD, VM::M1TN, "" },
{ 0x0149, 0x0003, 0, VR::FD, VM::M1TN, "" },
{ 0x7FD1, 0x0000, 0, VR::UN, VM::M1, "AcousticImageAndFooterData" },
};

unsigned short Dict347TagHashTable[] = {
    9,    14,    19,    26,    31,    46,    65,    76,     0,     2,
    7,     5,    18,     5,     2,     6,     4,    17,     4,     3,
    1,   137,     9,     7,    20,     7,     2,     8,     6,    19,
    6,     7,     0,    45,     3,     1,    11,     9,    22,     9,
   24,    17,    27,    33,    29,     1,     9,     2,     0,    10,
    8,    12,    16,    14,     0,    21,     8,    23,    16,    26,
   32,    28,    48,    30,     1,     5,     5,     3,    13,    19,
   16,     3,    31,     2,    33,     0,     4,     4,     2,    15,
    2,    25,    18,    32,     3,
};

vtkDICOMDictionary::Dict Dict347Data = {
"SIEMENS Ultrasound SC2000",
8,
34,
Dict347TagHashTable,
Dict347Contents
};

// ----- TOSHIBA_MEC_1.0 -----

DictEntry Dict348Contents[] = {
{ 0x0009, 0x0001, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x0002, 0, VR::US, VM::M1TN, "" },
{ 0x0009, 0x0003, 0, VR::US, VM::M1TN, "" },
{ 0x0009, 0x0004, 0, VR::US, VM::M1TN, "" },
{ 0x0011, 0x0001, 0, VR::LT, VM::M1, "" },
{ 0x0011, 0x0002, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0001, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0002, 0, VR::US, VM::M1TN, "" },
{ 0x0021, 0x0001, 0, VR::US, VM::M1TN, "" },
{ 0x0021, 0x0002, 0, VR::US, VM::M1TN, "" },
{ 0x0021, 0x0003, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0001, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0002, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0003, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0010, 0, VR::US, VM::M1TN, "" },
};

unsigned short Dict348TagHashTable[] = {
    4,    15,    28,     0,     5,     6,     1,     7,     2,    11,
    1,    12,     2,    14,    16,     6,     2,     3,     3,     4,
    4,     1,     5,     2,    10,     3,    13,     3,     4,     0,
    1,     1,     2,     8,     1,     9,     2,
};

vtkDICOMDictionary::Dict Dict348Data = {
"TOSHIBA_MEC_1.0",
3,
15,
Dict348TagHashTable,
Dict348Contents
};

// ----- SIEMENS MED SMS USG S2000 3D VOLUME -----

DictEntry Dict349Contents[] = {
{ 0x0039, 0x0050, 0, VR::LO, VM::M1, "PrivateCreatorVersionOfBookmark" },
{ 0x0039, 0x0051, 0, VR::US, VM::M1, "BCutPlaneEnable" },
{ 0x0039, 0x0052, 0, VR::US, VM::M1, "BMprColorMapIndex" },
{ 0x0039, 0x0053, 0, VR::US, VM::M1, "BMprDynamicRangeDb" },
{ 0x0039, 0x0054, 0, VR::US, VM::M1, "BMprGrayMapIndex" },
{ 0x0039, 0x0055, 0, VR::US, VM::M1, "BVolumeRenderMode" },
{ 0x0039, 0x0056, 0, VR::US, VM::M1, "BVrBrightness" },
{ 0x0039, 0x0057, 0, VR::US, VM::M1, "BVrContrast" },
{ 0x0039, 0x0058, 0, VR::US, VM::M1, "BVrColorMapIndex" },
{ 0x0039, 0x0059, 0, VR::US, VM::M1, "BVrDynamicRangeDb" },
{ 0x0039, 0x005a, 0, VR::US, VM::M1, "BVrGrayMapIndex" },
{ 0x0039, 0x005b, 0, VR::US, VM::M1, "BVrGrayMapIndex" },
{ 0x0039, 0x005c, 0, VR::US, VM::M1, "BVrThresholdHigh" },
{ 0x0039, 0x005d, 0, VR::US, VM::M1, "BVrThresholdLow" },
{ 0x0039, 0x005e, 0, VR::US, VM::M1, "BPreProcessFilterMix" },
{ 0x0039, 0x005f, 0, VR::US, VM::M1, "CCutPlaneEnable" },
{ 0x0039, 0x0060, 0, VR::US, VM::M1, "CFrontClipMode" },
{ 0x0039, 0x0061, 0, VR::US, VM::M1, "CMprColorMapIndex" },
{ 0x0039, 0x0062, 0, VR::US, VM::M1, "CMprColorFlowPriorityIndex" },
{ 0x0039, 0x0063, 0, VR::US, VM::M1, "CVolumeRenderMode" },
{ 0x0039, 0x0064, 0, VR::US, VM::M1, "CVrColorMapIndex" },
{ 0x0039, 0x0065, 0, VR::US, VM::M1, "CVrColorFlowPriorityIndex" },
{ 0x0039, 0x0066, 0, VR::US, VM::M1, "CVrOpacity" },
{ 0x0039, 0x0067, 0, VR::US, VM::M1, "CVrThresholdHigh" },
{ 0x0039, 0x0068, 0, VR::US, VM::M1, "CVrThresholdLow" },
{ 0x0039, 0x0069, 0, VR::US, VM::M1, "VoiMode" },
{ 0x0039, 0x006a, 0, VR::US, VM::M1, "VoiRotationOffsetDeg" },
{ 0x0039, 0x006b, 0, VR::FD, VM::M1, "VoiSizeRatioX" },
{ 0x0039, 0x006c, 0, VR::FD, VM::M1, "VoiSizeRatioY" },
{ 0x0039, 0x006d, 0, VR::FD, VM::M1, "VoiSizeRatioZ" },
{ 0x0039, 0x006e, 0, VR::US, VM::M1, "VoiSyncPlane" },
{ 0x0039, 0x006f, 0, VR::US, VM::M1, "VoiViewMode" },
{ 0x0039, 0x0070, 0, VR::FD, VM::M1TN, "VrOrientationA" },
{ 0x0039, 0x0071, 0, VR::FD, VM::M1TN, "MprOrientationA" },
{ 0x0039, 0x0072, 0, VR::FD, VM::M1, "VrOffsetVector" },
{ 0x0039, 0x0073, 0, VR::FD, VM::M1, "BlendingRatio" },
{ 0x0039, 0x0074, 0, VR::US, VM::M1, "FusionBlendMode" },
{ 0x0039, 0x0075, 0, VR::FD, VM::M1, "QualityFactor" },
{ 0x0039, 0x0076, 0, VR::US, VM::M1, "RendererType" },
{ 0x0039, 0x0077, 0, VR::US, VM::M1, "SliceMode" },
{ 0x0039, 0x0078, 0, VR::US, VM::M1, "ActiveQuad" },
{ 0x0039, 0x0079, 0, VR::US, VM::M1, "ScreenMode" },
{ 0x0039, 0x007a, 0, VR::US, VM::M1, "CutPlaneSide" },
{ 0x0039, 0x007b, 0, VR::US, VM::M1, "WireframeMode" },
{ 0x0039, 0x007c, 0, VR::US, VM::M1, "CrossmarkMode" },
{ 0x0039, 0x007d, 0, VR::US, VM::M1, "MprDisplayType" },
{ 0x0039, 0x007e, 0, VR::US, VM::M1, "VolumeDisplayType" },
{ 0x0039, 0x007f, 0, VR::US, VM::M1, "LastReset" },
{ 0x0039, 0x0080, 0, VR::US, VM::M1, "LastNonFullScreenMode" },
{ 0x0039, 0x0081, 0, VR::US, VM::M1, "MprToolIndex" },
{ 0x0039, 0x0082, 0, VR::US, VM::M1, "VoiToolIndex" },
{ 0x0039, 0x0083, 0, VR::US, VM::M1, "ToolLoopMode" },
{ 0x0039, 0x0084, 0, VR::US, VM::M1, "VolumeArbMode" },
{ 0x0039, 0x0085, 0, VR::US, VM::M1, "MprZoomEn" },
{ 0x0039, 0x0086, 0, VR::US, VM::M1, "IsVolumeZoomEn" },
{ 0x0039, 0x0087, 0, VR::SS, VM::M1, "ZoomLevelMpr" },
{ 0x0039, 0x0088, 0, VR::SS, VM::M1, "ZoomLevelVolume" },
{ 0x0039, 0x0089, 0, VR::US, VM::M1, "IsAutoRotateEn" },
{ 0x0039, 0x008a, 0, VR::US, VM::M1, "AutoRotateAxis" },
{ 0x0039, 0x008b, 0, VR::US, VM::M1, "AutoRotateRangeIndex" },
{ 0x0039, 0x008c, 0, VR::US, VM::M1, "AutoRotateSpeedIndex" },
{ 0x0039, 0x008d, 0, VR::US, VM::M1, "CVrBrightness" },
{ 0x0039, 0x008e, 0, VR::US, VM::M1, "CFlowStateIndex" },
{ 0x0039, 0x008f, 0, VR::US, VM::M1, "BSubmodeIndex" },
{ 0x0039, 0x0090, 0, VR::US, VM::M1, "CSubmodeIndex" },
{ 0x0039, 0x0091, 0, VR::US, VM::M1, "CutPlane" },
{ 0x0039, 0x0092, 0, VR::US, VM::M1, "BookmarkChunkId" },
{ 0x0039, 0x0093, 0, VR::US, VM::M1, "SequenceMinChunkId" },
{ 0x0039, 0x0094, 0, VR::US, VM::M1, "SequenceMaxChunkId" },
{ 0x0039, 0x0095, 0, VR::FD, VM::M1, "VolumeRateHz" },
{ 0x0039, 0x009a, 0, VR::FD, VM::M1, "VoiPositionOffsetX" },
{ 0x0039, 0x009b, 0, VR::FD, VM::M1, "VoiPositionOffsetY" },
{ 0x0039, 0x009c, 0, VR::FD, VM::M1, "VoiPositionOffsetZ" },
{ 0x0039, 0x009d, 0, VR::US, VM::M1, "VrToolIndex" },
{ 0x0039, 0x009e, 0, VR::US, VM::M1, "ShadingPercent" },
{ 0x0039, 0x009f, 0, VR::US, VM::M1, "VolumeType" },
{ 0x0039, 0x00a0, 0, VR::US, VM::M1, "VrQuadDisplayType" },
{ 0x0039, 0x00a1, 0, VR::FD, VM::M1TN, "MprCenterLocation" },
{ 0x0039, 0x00e0, 0, VR::US, VM::M1, "SliceRangeType" },
{ 0x0039, 0x00e1, 0, VR::US, VM::M1, "SliceMPRPlane" },
{ 0x0039, 0x00e2, 0, VR::US, VM::M1, "SliceLayout" },
{ 0x0039, 0x00e3, 0, VR::FD, VM::M1, "SliceSpacing" },
{ 0x0039, 0x00e4, 0, VR::US, VM::M1, "ThinVrMode" },
{ 0x0039, 0x00e5, 0, VR::US, VM::M1, "ThinVrThickness" },
{ 0x0039, 0x00e6, 0, VR::FD, VM::M1, "VoiPivotX" },
{ 0x0039, 0x00e7, 0, VR::FD, VM::M1, "VoiPivotY" },
{ 0x0039, 0x00e8, 0, VR::FD, VM::M1, "VoiPivotZ" },
{ 0x0039, 0x00e9, 0, VR::US, VM::M1, "CTopVoiQuad" },
{ 0x0039, 0x00ea, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00ed, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00ee, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00ef, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f0, 0, VR::US, VM::M1TN, "" },
{ 0x0039, 0x00f1, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f2, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f3, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f4, 0, VR::FD, VM::M1, "" },
{ 0x0039, 0x00f5, 0, VR::LO, VM::M1, "" },
{ 0x0039, 0x00f6, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict349TagHashTable[] = {
   25,    34,    43,    52,    61,    68,    75,    84,    93,   102,
  111,   122,   133,   142,   149,   158,   167,   178,   187,   196,
  205,   216,   227,   236,     0,     4,     8,    88,    32,   112,
   67,   147,    80,   226,     4,     9,    89,    33,   113,    66,
  146,    81,   227,     4,    10,    90,    34,   114,    65,   145,
   78,   224,     4,    11,    91,    35,   115,    64,   144,    79,
  225,     3,    12,    92,    36,   116,    84,   230,     3,    13,
   93,    37,   117,    85,   231,     4,    14,    94,    38,   118,
   69,   149,    82,   228,     4,    15,    95,    39,   119,    68,
  148,    83,   229,     4,     0,    80,    24,   104,    59,   139,
   94,   242,     4,     1,    81,    25,   105,    58,   138,    95,
  243,     5,     2,    82,    26,   106,    57,   137,    77,   161,
   92,   240,     5,     3,    83,    27,   107,    56,   136,    76,
  160,    93,   241,     4,     4,    84,    28,   108,    63,   143,
   98,   246,     3,     5,    85,    29,   109,    62,   142,     4,
    6,    86,    30,   110,    61,   141,    96,   244,     4,     7,
   87,    31,   111,    60,   140,    97,   245,     5,    16,    96,
   40,   120,    51,   131,    71,   155,    88,   234,     4,    17,
   97,    41,   121,    50,   130,    70,   154,     4,    18,    98,
   42,   122,    49,   129,    86,   232,     4,    19,    99,    43,
  123,    48,   128,    87,   233,     5,    20,   100,    44,   124,
   55,   135,    75,   159,    90,   238,     5,    21,   101,    45,
  125,    54,   134,    74,   158,    91,   239,     4,    22,   102,
   46,   126,    53,   133,    73,   157,     5,    23,   103,    47,
  127,    52,   132,    72,   156,    89,   237,
};

vtkDICOMDictionary::Dict Dict349Data = {
"SIEMENS MED SMS USG S2000 3D VOLUME",
24,
99,
Dict349TagHashTable,
Dict349Contents
};

// ----- Picker MR Private Group -----

DictEntry Dict350Contents[] = {
{ 0x7101, 0x0000, 0, VR::OB, VM::M1, "" },
{ 0x7101, 0x0001, 0, VR::SL, VM::M1, "" },
{ 0x7101, 0x0002, 0, VR::OB, VM::M1, "" },
{ 0x7101, 0x0003, 0, VR::SL, VM::M1, "" },
{ 0x7101, 0x0004, 0, VR::SH, VM::M1, "" },
{ 0x7101, 0x0005, 0, VR::SH, VM::M2, "" },
{ 0x7101, 0x0006, 0, VR::SH, VM::M4, "" },
{ 0x7101, 0x0010, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict350TagHashTable[] = {
    3,    10,     0,     3,     1,     1,     3,     3,     5,     5,
    5,     0,     0,     2,     2,     4,     4,     6,     6,     7,
   16,
};

vtkDICOMDictionary::Dict Dict350Data = {
"Picker MR Private Group",
2,
8,
Dict350TagHashTable,
Dict350Contents
};

// ----- DLX_SERIE_01 -----

DictEntry Dict351Contents[] = {
{ 0x0019, 0x0001, 0, VR::DS, VM::M1, "AngleValueLArm" },
{ 0x0019, 0x0002, 0, VR::DS, VM::M1, "AngleValuePArm" },
{ 0x0019, 0x0003, 0, VR::DS, VM::M1, "AngleValueCArm" },
{ 0x0019, 0x0004, 0, VR::CS, VM::M1, "AngleLabelLArm" },
{ 0x0019, 0x0005, 0, VR::CS, VM::M1, "AngleLabelPArm" },
{ 0x0019, 0x0006, 0, VR::CS, VM::M1, "AngleLabelCArm" },
{ 0x0019, 0x0007, 0, VR::ST, VM::M1, "ProcedureName" },
{ 0x0019, 0x0008, 0, VR::ST, VM::M1, "ExamName" },
{ 0x0019, 0x0009, 0, VR::SH, VM::M1, "PatientSize" },
{ 0x0019, 0x000A, 0, VR::IS, VM::M1, "RecordView" },
{ 0x0019, 0x0010, 0, VR::DS, VM::M1, "InjectorDelay" },
{ 0x0019, 0x0011, 0, VR::CS, VM::M1, "AutoInject" },
{ 0x0019, 0x0014, 0, VR::IS, VM::M1, "AcquisitionMode" },
{ 0x0019, 0x0015, 0, VR::CS, VM::M1, "CameraRotationEnabled" },
{ 0x0019, 0x0016, 0, VR::CS, VM::M1, "ReverseSweep" },
{ 0x0019, 0x0017, 0, VR::IS, VM::M1, "UserSpatialFilterStrength" },
{ 0x0019, 0x0018, 0, VR::IS, VM::M1, "UserZoomFactor" },
{ 0x0019, 0x0019, 0, VR::IS, VM::M1, "XZoomCenter" },
{ 0x0019, 0x001A, 0, VR::IS, VM::M1, "YZoomCenter" },
{ 0x0019, 0x001B, 0, VR::DS, VM::M1, "Focus" },
{ 0x0019, 0x001C, 0, VR::CS, VM::M1, "Dose" },
{ 0x0019, 0x001D, 0, VR::IS, VM::M1, "SideMark" },
{ 0x0019, 0x001E, 0, VR::IS, VM::M1, "PercentageLandscape" },
{ 0x0019, 0x001F, 0, VR::DS, VM::M1, "ExposureDuration" },
{ 0x0019, 0x0020, 0, VR::LO, VM::M1, "IpAddress" },
{ 0x0019, 0x0021, 0, VR::DS, VM::M1, "TablePositionZ" },
{ 0x0019, 0x0022, 0, VR::DS, VM::M1, "TablePositionX" },
{ 0x0019, 0x0023, 0, VR::DS, VM::M1, "TablePositionY" },
{ 0x0019, 0x0024, 0, VR::DS, VM::M1, "Lambda" },
{ 0x0019, 0x0025, 0, VR::DS, VM::M1, "RegressionSlope" },
{ 0x0019, 0x0026, 0, VR::DS, VM::M1, "RegressionIntercept" },
{ 0x0019, 0x1027, 0, VR::DS, VM::M1, "ImageChainFWHMPsfMmMin" },
{ 0x0019, 0x1028, 0, VR::DS, VM::M1, "ImageChainFWHMPsfMmMax" },
};

unsigned short Dict351TagHashTable[] = {
    9,    20,    31,    38,    47,    56,    65,    74,     0,     5,
    0,     1,     8,     9,    11,    17,    17,    25,    25,    33,
    5,     7,     8,    10,    16,    16,    24,    24,    32,    32,
 4136,     3,     2,     3,    19,    27,    27,    35,     4,     1,
    2,     9,    10,    18,    26,    26,    34,     4,     4,     5,
   13,    21,    21,    29,    29,    37,     4,     3,     4,    12,
   20,    20,    28,    28,    36,     4,     6,     7,    15,    23,
   23,    31,    31,  4135,     4,     5,     6,    14,    22,    22,
   30,    30,    38,
};

vtkDICOMDictionary::Dict Dict351Data = {
"DLX_SERIE_01",
8,
33,
Dict351TagHashTable,
Dict351Contents
};

// ----- SIEMENS SYNGO ENCAPSULATED DOCUMENT DATA -----

DictEntry Dict352Contents[] = {
{ 0x0087, 0x0020, 0, VR::OB, VM::M1, "StudyModel" },
{ 0x0087, 0x0030, 0, VR::OB, VM::M1, "ReportXMLSchema" },
{ 0x0087, 0x0040, 0, VR::OB, VM::M1, "ReportIdentifier" },
};

unsigned short Dict352TagHashTable[] = {
    2,     0,     3,     0,    32,     1,    48,     2,    64,
};

vtkDICOMDictionary::Dict Dict352Data = {
"SIEMENS SYNGO ENCAPSULATED DOCUMENT DATA",
1,
3,
Dict352TagHashTable,
Dict352Contents
};

// ----- 1.2.840.113663.1 -----

DictEntry Dict353Contents[] = {
{ 0x0029, 0x0000, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0001, 0, VR::US, VM::M1, "" },
};

unsigned short Dict353TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict353Data = {
"1.2.840.113663.1",
1,
2,
Dict353TagHashTable,
Dict353Contents
};

// ----- SIEMENS MED OCS BEAM DISPLAY INFO -----

DictEntry Dict354Contents[] = {
{ 0x0039, 0x0076, 0, VR::CS, VM::M1, "BeamDisplayProperties" },
};

unsigned short Dict354TagHashTable[] = {
    2,     0,     1,     0,   118,
};

vtkDICOMDictionary::Dict Dict354Data = {
"SIEMENS MED OCS BEAM DISPLAY INFO",
1,
1,
Dict354TagHashTable,
Dict354Contents
};

// ----- ULTRAVISUAL_TAG_SET1 -----

DictEntry Dict355Contents[] = {
{ 0x0011, 0x0001, 0, VR::CS, VM::M1, "" },
{ 0x0011, 0x0002, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0003, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0008, 0, VR::LO, VM::M1, "" },
{ 0x0011, 0x0010, 0, VR::US, VM::M1, "" },
{ 0x0011, 0x0011, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x0012, 0, VR::UI, VM::M1, "" },
{ 0x0011, 0x0018, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0019, 0, VR::UN, VM::M1, "" },
{ 0x0011, 0x001a, 0, VR::CS, VM::M1, "" },
{ 0x0011, 0x001b, 0, VR::IS, VM::M1, "" },
{ 0x0011, 0x001c, 0, VR::IS, VM::M1, "" },
{ 0x0011, 0x001d, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict355TagHashTable[] = {
    4,    15,    28,     0,     5,     2,     3,     5,    17,     6,
   18,     7,    24,    12,    29,     6,     0,     1,     1,     2,
    3,     8,     4,    16,    10,    27,    11,    28,     2,     8,
   25,     9,    26,
};

vtkDICOMDictionary::Dict Dict355Data = {
"ULTRAVISUAL_TAG_SET1",
3,
13,
Dict355TagHashTable,
Dict355Contents
};

// ----- Applicare/RadWorks/Version 6.0/Summary -----

DictEntry Dict356Contents[] = {
{ 0x3109, 0x0001, 0, VR::SH, VM::M1, "Status" },
{ 0x3109, 0x0011, 0, VR::ST, VM::M1, "ReceiveOriginSiteName" },
{ 0x3109, 0x0012, 0, VR::ST, VM::M1, "ReceiveOriginDescription" },
{ 0x3109, 0x0015, 0, VR::DA, VM::M1, "ReceiveDate" },
{ 0x3109, 0x0016, 0, VR::TM, VM::M1, "ReceiveTime" },
};

unsigned short Dict356TagHashTable[] = {
    2,     0,     5,     0,     1,     1,    17,     2,    18,     3,
   21,     4,    22,
};

vtkDICOMDictionary::Dict Dict356Data = {
"Applicare/RadWorks/Version 6.0/Summary",
1,
5,
Dict356TagHashTable,
Dict356Contents
};

// ----- CARDIO-D.R. 1.0 -----

DictEntry Dict357Contents[] = {
{ 0x0009, 0x0000, 0, VR::UL, VM::M1, "FileLocation" },
{ 0x0009, 0x0001, 0, VR::UL, VM::M1, "FileSize" },
{ 0x0009, 0x0040, 0, VR::SQ, VM::M1, "AlternateImageSequence" },
{ 0x0019, 0x0000, 0, VR::CS, VM::M1, "ImageBlankingShape" },
{ 0x0019, 0x0002, 0, VR::IS, VM::M1, "ImageBlankingLeftVerticalEdge" },
{ 0x0019, 0x0004, 0, VR::IS, VM::M1, "ImageBlankingRightVerticalEdge" },
{ 0x0019, 0x0006, 0, VR::IS, VM::M1, "ImageBlankingUpperHorizontalEdge" },
{ 0x0019, 0x0008, 0, VR::IS, VM::M1, "ImageBlankingLowerHorizontalEdge" },
{ 0x0019, 0x0010, 0, VR::IS, VM::M1, "CenterOfCircularImageBlanking" },
{ 0x0019, 0x0012, 0, VR::IS, VM::M1, "RadiusOfCircularImageBlanking" },
{ 0x0019, 0x0030, 0, VR::UL, VM::M1, "MaximumImageFrameSize" },
{ 0x0021, 0x0013, 0, VR::IS, VM::M1, "ImageSequenceNumber" },
{ 0x0029, 0x0000, 0, VR::SQ, VM::M1, "EdgeEnhancementSequence" },
{ 0x0029, 0x0001, 0, VR::US, VM::M2, "ConvolutionKernelSize" },
{ 0x0029, 0x0002, 0, VR::US, VM::M1TN, "ConvolutionKernelCoefficients" },
{ 0x0029, 0x0003, 0, VR::FL, VM::M1, "EdgeEnhancementGain" },
{ 0x0029, 0x00AC, 0, VR::FL, VM::M1, "DisplayedAreaBottomRightHandCornerFractional" },
{ 0x0029, 0x00AD, 0, VR::FL, VM::M1, "DisplayedAreaTopLeftHandCornerFractional" },
};

unsigned short Dict357TagHashTable[] = {
    5,    12,    27,    34,     0,     3,     1,     1,     2,    64,
   13,     1,     7,     0,     0,     3,     0,     5,     4,     7,
    8,     8,    16,    10,    48,    12,     0,     3,    11,    19,
   15,     3,    17,   173,     5,     4,     2,     6,     6,     9,
   18,    14,     2,    16,   172,
};

vtkDICOMDictionary::Dict Dict357Data = {
"CARDIO-D.R. 1.0",
4,
18,
Dict357TagHashTable,
Dict357Contents
};

// ----- LODOX_STATSCAN -----

DictEntry Dict358Contents[] = {
{ 0x0019, 0x0001, 0, VR::IS, VM::M1TN, "" },
{ 0x0019, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0004, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0007, 0, VR::DS, VM::M1, "" },
{ 0x0019, 0x0008, 0, VR::DS, VM::M1, "" },
};

unsigned short Dict358TagHashTable[] = {
    3,    12,     0,     4,     0,     1,     2,     3,     4,     5,
    6,     7,     4,     1,     2,     3,     4,     5,     6,     7,
    8,
};

vtkDICOMDictionary::Dict Dict358Data = {
"LODOX_STATSCAN",
2,
8,
Dict358TagHashTable,
Dict358Contents
};

// ----- SIEMENS MED SMS USG ANTARES 3D VOLUME -----

DictEntry Dict359Contents[] = {
{ 0x0039, 0x0000, 0, VR::UN, VM::M1, "ReleaseVersion" },
{ 0x0039, 0x0003, 0, VR::UN, VM::M1, "VolumeAcquisitionDuration" },
{ 0x0039, 0x0004, 0, VR::UN, VM::M1, "VolumeRawDataType" },
{ 0x0039, 0x0005, 0, VR::UN, VM::M1, "ScanType" },
{ 0x0039, 0x0006, 0, VR::UN, VM::M1, "ZlateralMin" },
{ 0x0039, 0x0007, 0, VR::UN, VM::M1, "ZlateralSpan" },
{ 0x0039, 0x0008, 0, VR::UN, VM::M1, "ZRadiusOfCurvature" },
{ 0x0039, 0x0009, 0, VR::UN, VM::M1, "WobbleCorrection" },
{ 0x0039, 0x0010, 0, VR::UN, VM::M1, "ScaleAlongWidth" },
{ 0x0039, 0x0011, 0, VR::UN, VM::M1, "ScaleAlongHeight" },
{ 0x0039, 0x0012, 0, VR::UN, VM::M1, "ScaleAlongDepth" },
{ 0x0039, 0x0013, 0, VR::UN, VM::M1, "BufferSize" },
{ 0x0039, 0x0014, 0, VR::UN, VM::M1, "AcquisitionRate" },
{ 0x0039, 0x0015, 0, VR::UN, VM::M1, "DepthMinCm" },
{ 0x0039, 0x0016, 0, VR::UN, VM::M1, "IsLeftRightFlippedEn" },
{ 0x0039, 0x0017, 0, VR::UN, VM::M1, "IsUpDownFlippedEn" },
{ 0x0039, 0x0018, 0, VR::UN, VM::M1, "IsVolumeGeomAccurate" },
{ 0x0039, 0x0019, 0, VR::UN, VM::M1, "BByteMaskOffset" },
{ 0x0039, 0x0020, 0, VR::UN, VM::M1, "BByteMaskSize" },
{ 0x0039, 0x0022, 0, VR::UN, VM::M1, "AcqPlaneRotationDeg" },
{ 0x0039, 0x0023, 0, VR::UN, VM::M1, "BeamAxialSpan" },
{ 0x0039, 0x0024, 0, VR::UN, VM::M1, "BeamLateralMin" },
{ 0x0039, 0x0025, 0, VR::UN, VM::M1, "BeamLateralSpan" },
{ 0x0039, 0x0026, 0, VR::UN, VM::M1, "BeamAxialMin" },
{ 0x0039, 0x0027, 0, VR::UN, VM::M1, "NumDisplaySamples" },
{ 0x0039, 0x0028, 0, VR::UN, VM::M1, "DVolumeWidth" },
{ 0x0039, 0x0029, 0, VR::UN, VM::M1, "DVolumeDepth" },
{ 0x0039, 0x0030, 0, VR::UN, VM::M1, "DVolumeHeight" },
{ 0x0039, 0x0031, 0, VR::UN, VM::M1, "DVolumePosX" },
{ 0x0039, 0x0032, 0, VR::UN, VM::M1, "DVolumePosY" },
{ 0x0039, 0x0033, 0, VR::UN, VM::M1, "DVolumePosZ" },
{ 0x0039, 0x0034, 0, VR::UN, VM::M1, "DBeamAxialMin" },
{ 0x0039, 0x0035, 0, VR::UN, VM::M1, "DBeamAxialSpan" },
{ 0x0039, 0x0037, 0, VR::UN, VM::M1, "DBeamLateralSpan" },
{ 0x0039, 0x0038, 0, VR::UN, VM::M1, "NumOfVolumesInSequence" },
{ 0x0039, 0x0039, 0, VR::UN, VM::M1, "DByteMaskOffset" },
{ 0x0039, 0x0040, 0, VR::UN, VM::M1, "DByteMaskSize" },
{ 0x0039, 0x0050, 0, VR::LO, VM::M1, "PrivateCreatorVersionOfBookmark" },
{ 0x0039, 0x0051, 0, VR::US, VM::M1, "BCutPlaneEnable" },
{ 0x0039, 0x0052, 0, VR::US, VM::M1, "BMprColorMapIndex" },
{ 0x0039, 0x0053, 0, VR::US, VM::M1, "BMprDynamicRangeDb" },
{ 0x0039, 0x0054, 0, VR::US, VM::M1, "BMprGrayMapIndex" },
{ 0x0039, 0x0055, 0, VR::US, VM::M1, "BVolumeRenderMode" },
{ 0x0039, 0x0056, 0, VR::US, VM::M1, "BVrBrightness" },
{ 0x0039, 0x0057, 0, VR::US, VM::M1, "BVrContrast" },
{ 0x0039, 0x0058, 0, VR::US, VM::M1, "BVrColorMapIndex" },
{ 0x0039, 0x0059, 0, VR::US, VM::M1, "BVrDynamicRangeDb" },
{ 0x0039, 0x005a, 0, VR::US, VM::M1, "BVrGrayMapIndex" },
{ 0x0039, 0x005b, 0, VR::US, VM::M1, "BVrGrayMapIndex" },
{ 0x0039, 0x005c, 0, VR::US, VM::M1, "BVrThresholdHigh" },
{ 0x0039, 0x005d, 0, VR::US, VM::M1, "BVrThresholdLow" },
{ 0x0039, 0x005e, 0, VR::US, VM::M1, "BPreProcessFilterMix" },
{ 0x0039, 0x005f, 0, VR::US, VM::M1, "CCutPlaneEnable" },
{ 0x0039, 0x0060, 0, VR::US, VM::M1, "CFrontClipMode" },
{ 0x0039, 0x0061, 0, VR::US, VM::M1, "CMprColorMapIndex" },
{ 0x0039, 0x0062, 0, VR::US, VM::M1, "CMprColorFlowPriorityIndex" },
{ 0x0039, 0x0063, 0, VR::US, VM::M1, "CVolumeRenderMode" },
{ 0x0039, 0x0064, 0, VR::US, VM::M1, "CVrColorMapIndex" },
{ 0x0039, 0x0065, 0, VR::US, VM::M1, "CVrColorFlowPriorityIndex" },
{ 0x0039, 0x0066, 0, VR::US, VM::M1, "CVrOpacity" },
{ 0x0039, 0x0067, 0, VR::US, VM::M1, "CVrThresholdHigh" },
{ 0x0039, 0x0068, 0, VR::US, VM::M1, "CVrThresholdLow" },
{ 0x0039, 0x0069, 0, VR::US, VM::M1, "VoiMode" },
{ 0x0039, 0x006a, 0, VR::US, VM::M1, "VoiRotationOffsetDeg" },
{ 0x0039, 0x006b, 0, VR::FD, VM::M1, "VoiSizeRatioX" },
{ 0x0039, 0x006c, 0, VR::FD, VM::M1, "VoiSizeRatioY" },
{ 0x0039, 0x006d, 0, VR::FD, VM::M1, "VoiSizeRatioZ" },
{ 0x0039, 0x006e, 0, VR::US, VM::M1, "VoiSyncPlane" },
{ 0x0039, 0x006f, 0, VR::US, VM::M1, "VoiViewMode" },
{ 0x0039, 0x0070, 0, VR::FD, VM::M1TN, "VrOrientationA" },
{ 0x0039, 0x0071, 0, VR::FD, VM::M1TN, "MprOrientationA" },
{ 0x0039, 0x0072, 0, VR::FD, VM::M1, "VrOffsetVector" },
{ 0x0039, 0x0073, 0, VR::FD, VM::M1, "BlendingRatio" },
{ 0x0039, 0x0074, 0, VR::US, VM::M1, "FusionBlendMode" },
{ 0x0039, 0x0075, 0, VR::FD, VM::M1, "QualityFactor" },
{ 0x0039, 0x0076, 0, VR::US, VM::M1, "RendererType" },
{ 0x0039, 0x0077, 0, VR::US, VM::M1, "SliceMode" },
{ 0x0039, 0x0078, 0, VR::US, VM::M1, "ActiveQuad" },
{ 0x0039, 0x0079, 0, VR::US, VM::M1, "ScreenMode" },
{ 0x0039, 0x007a, 0, VR::US, VM::M1, "CutPlaneSide" },
{ 0x0039, 0x007b, 0, VR::US, VM::M1, "WireframeMode" },
{ 0x0039, 0x007c, 0, VR::US, VM::M1, "CrossmarkMode" },
{ 0x0039, 0x007d, 0, VR::US, VM::M1, "MprDisplayType" },
{ 0x0039, 0x007e, 0, VR::US, VM::M1, "VolumeDisplayType" },
{ 0x0039, 0x007f, 0, VR::US, VM::M1, "LastReset" },
{ 0x0039, 0x0080, 0, VR::US, VM::M1, "LastNonFullScreenMode" },
{ 0x0039, 0x0081, 0, VR::US, VM::M1, "MprToolIndex" },
{ 0x0039, 0x0082, 0, VR::US, VM::M1, "VoiToolIndex" },
{ 0x0039, 0x0083, 0, VR::US, VM::M1, "ToolLoopMode" },
{ 0x0039, 0x0084, 0, VR::US, VM::M1, "VolumeArbMode" },
{ 0x0039, 0x0085, 0, VR::US, VM::M1, "MprZoomEn" },
{ 0x0039, 0x0086, 0, VR::US, VM::M1, "IsVolumeZoomEn" },
{ 0x0039, 0x0087, 0, VR::SS, VM::M1, "ZoomLevelMpr" },
{ 0x0039, 0x0088, 0, VR::SS, VM::M1, "ZoomLevelVolume" },
{ 0x0039, 0x0089, 0, VR::US, VM::M1, "IsAutoRotateEn" },
{ 0x0039, 0x008a, 0, VR::US, VM::M1, "AutoRotateAxis" },
{ 0x0039, 0x008b, 0, VR::US, VM::M1, "AutoRotateRangeIndex" },
{ 0x0039, 0x008c, 0, VR::US, VM::M1, "AutoRotateSpeedIndex" },
{ 0x0039, 0x008d, 0, VR::US, VM::M1, "CVrBrightness" },
{ 0x0039, 0x008e, 0, VR::US, VM::M1, "CFlowStateIndex" },
{ 0x0039, 0x008f, 0, VR::US, VM::M1, "BSubmodeIndex" },
{ 0x0039, 0x0090, 0, VR::US, VM::M1, "CSubmodeIndex" },
{ 0x0039, 0x0091, 0, VR::US, VM::M1, "CutPlane" },
{ 0x0039, 0x0092, 0, VR::US, VM::M1, "BookmarkChunkId" },
{ 0x0039, 0x0093, 0, VR::US, VM::M1, "SequenceMinChunkId" },
{ 0x0039, 0x0094, 0, VR::US, VM::M1, "SequenceMaxChunkId" },
{ 0x0039, 0x0095, 0, VR::FD, VM::M1, "VolumeRateHz" },
{ 0x0039, 0x009a, 0, VR::FD, VM::M1, "VoiPositionOffsetX" },
{ 0x0039, 0x009b, 0, VR::FD, VM::M1, "VoiPositionOffsetY" },
{ 0x0039, 0x009c, 0, VR::FD, VM::M1, "VoiPositionOffsetZ" },
{ 0x0039, 0x009d, 0, VR::US, VM::M1, "VrToolIndex" },
{ 0x0039, 0x009e, 0, VR::US, VM::M1, "ShadingPercent" },
{ 0x0039, 0x009f, 0, VR::US, VM::M1, "VolumeType" },
{ 0x0039, 0x00a0, 0, VR::US, VM::M1, "VrQuadDisplayType" },
{ 0x0039, 0x00a1, 0, VR::FD, VM::M1TN, "MprCenterLocation" },
{ 0x0039, 0x00e0, 0, VR::US, VM::M1, "SliceRangeType" },
{ 0x0039, 0x00e1, 0, VR::US, VM::M1, "SliceMPRPlane" },
{ 0x0039, 0x00e2, 0, VR::US, VM::M1, "SliceLayout" },
{ 0x0039, 0x00e3, 0, VR::FD, VM::M1, "SliceSpacing" },
{ 0x0039, 0x00e4, 0, VR::US, VM::M1, "ThinVrMode" },
{ 0x0039, 0x00e5, 0, VR::US, VM::M1, "ThinVrThickness" },
{ 0x0039, 0x00e6, 0, VR::FD, VM::M1, "VoiPivotX" },
{ 0x0039, 0x00e7, 0, VR::FD, VM::M1, "VoiPivotY" },
{ 0x0039, 0x00e8, 0, VR::FD, VM::M1, "VoiPivotZ" },
{ 0x0039, 0x00e9, 0, VR::US, VM::M1, "CTopVoiQuad" },
{ 0x0039, 0x00ea, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00ed, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00ee, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00ef, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f0, 0, VR::US, VM::M1TN, "" },
{ 0x0039, 0x00f1, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f2, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f3, 0, VR::US, VM::M1, "" },
{ 0x0039, 0x00f4, 0, VR::FD, VM::M1, "" },
{ 0x0039, 0x00f5, 0, VR::LO, VM::M1, "" },
{ 0x0039, 0x00f6, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict359TagHashTable[] = {
   35,    46,    55,    62,    69,    78,    85,    96,   107,   120,
  133,   142,   153,   164,   175,   186,   195,   204,   213,   224,
  233,   238,   243,   246,   251,   258,   265,   272,   279,   288,
  297,   308,   319,   330,     0,     5,    35,    57,    51,    94,
   81,   124,   102,   145,   135,   246,     4,    34,    56,    52,
   95,    82,   125,   101,   144,     3,    37,    80,    83,   126,
  133,   244,     3,    38,    81,    84,   127,   134,   245,     4,
   39,    82,    69,   112,   106,   149,   125,   234,     3,    40,
   83,    70,   113,   105,   148,     5,     9,    17,    41,    84,
   71,   114,    96,   139,   123,   232,     5,     8,    16,    42,
   85,    72,   115,    95,   138,   124,   233,     6,    11,    19,
   28,    49,    43,    86,    73,   116,    94,   137,   127,   238,
    6,    10,    18,    27,    48,    44,    87,    74,   117,    93,
  136,   128,   239,     4,    13,    21,    30,    51,    75,   118,
  100,   143,     5,    12,    20,    29,    50,    76,   119,    99,
  142,   126,   237,     5,    15,    23,    32,    53,    61,   104,
   98,   141,   117,   226,     5,    14,    22,    31,    52,    62,
  105,    97,   140,   118,   227,     5,     7,     9,    33,    55,
   63,   106,    88,   131,   115,   224,     4,     6,     8,    64,
  107,    87,   130,   116,   225,     4,    26,    41,    65,   108,
   86,   129,   121,   230,     4,    25,    40,    66,   109,    85,
  128,   122,   231,     5,    36,    64,    67,   110,    92,   135,
  114,   161,   119,   228,     4,    68,   111,    91,   134,   113,
  160,   120,   229,     2,    53,    96,    90,   133,     2,    54,
   97,    89,   132,     1,    55,    98,     2,     0,     0,    56,
   99,     3,     1,     3,    57,   100,   108,   155,     3,    18,
   32,    58,   101,   107,   154,     3,     3,     5,    20,    35,
   59,   102,     3,     2,     4,    19,    34,    60,   103,     4,
    5,     7,    22,    37,    45,    88,   112,   159,     4,     4,
    6,    21,    36,    46,    89,   111,   158,     5,    24,    39,
   47,    90,    77,   120,   110,   157,   131,   242,     5,    23,
   38,    48,    91,    78,   121,   109,   156,   132,   243,     5,
   17,    25,    49,    92,    79,   122,   104,   147,   129,   240,
    5,    16,    24,    50,    93,    80,   123,   103,   146,   130,
  241,
};

vtkDICOMDictionary::Dict Dict359Data = {
"SIEMENS MED SMS USG ANTARES 3D VOLUME",
34,
136,
Dict359TagHashTable,
Dict359Contents
};

// ----- 1.2.840.113681 -----

DictEntry Dict360Contents[] = {
{ 0x0019, 0x0010, 0, VR::ST, VM::M1, "CRImageParamsCommon" },
{ 0x0019, 0x0011, 0, VR::ST, VM::M1, "CRImageIPParamsSingle" },
{ 0x0019, 0x0012, 0, VR::ST, VM::M1, "CRImageIPParamsLeft" },
{ 0x0019, 0x0013, 0, VR::ST, VM::M1, "CRImageIPParamsRight" },
};

unsigned short Dict360TagHashTable[] = {
    2,     0,     4,     0,    16,     1,    17,     2,    18,     3,
   19,
};

vtkDICOMDictionary::Dict Dict360Data = {
"1.2.840.113681",
1,
4,
Dict360TagHashTable,
Dict360Contents
};

// ----- Philips PET Private Group -----

DictEntry Dict361Contents[] = {
{ 0x0511, 0x0000, 0, VR::US, VM::M1, "PrivateData" },
{ 0x0511, 0x0001, 0, VR::US, VM::M1, "PrivateData" },
{ 0x0511, 0x0002, 0, VR::OB, VM::M1, "PrivateData" },
{ 0x0511, 0x0003, 0, VR::OB, VM::M1, "PrivateData" },
{ 0x0511, 0x0032, 0, VR::DS, VM::M1, "PrivateData" },
{ 0x0511, 0x0050, 0, VR::DS, VM::M1, "PrivateData" },
{ 0x7053, 0x0000, 0, VR::DS, VM::M1, "SUVFactor" },
{ 0x7053, 0x0001, 0, VR::OB, VM::M1, "PrivateData" },
{ 0x7053, 0x0002, 0, VR::OB, VM::M1, "PrivateData" },
{ 0x7053, 0x0003, 0, VR::ST, VM::M1, "OriginalFileName" },
{ 0x7053, 0x0004, 0, VR::OB, VM::M1, "" },
{ 0x7053, 0x0005, 0, VR::LO, VM::M1, "WorklistInfoFileName" },
{ 0x7053, 0x0006, 0, VR::OB, VM::M1, "" },
{ 0x7053, 0x0007, 0, VR::SQ, VM::M1, "" },
{ 0x7053, 0x0008, 0, VR::SQ, VM::M1, "" },
{ 0x7053, 0x0009, 0, VR::DS, VM::M1, "ActivityConcentrationScaleFactor" },
{ 0x7053, 0x000f, 0, VR::UL, VM::M1, "" },
{ 0x7053, 0x0010, 0, VR::US, VM::M1, "" },
{ 0x7053, 0x0011, 0, VR::US, VM::M1, "" },
{ 0x7053, 0x0012, 0, VR::SQ, VM::M1, "" },
{ 0x7053, 0x0013, 0, VR::SS, VM::M1, "" },
{ 0x7053, 0x0014, 0, VR::SS, VM::M1, "" },
{ 0x7053, 0x0015, 0, VR::SS, VM::M1, "" },
{ 0x7053, 0x0016, 0, VR::SS, VM::M1, "" },
{ 0x7053, 0x0017, 0, VR::SS, VM::M1, "" },
{ 0x7053, 0x0018, 0, VR::SS, VM::M1, "" },
{ 0x7053, 0x00c2, 0, VR::UI, VM::M1, "" },
};

unsigned short Dict361TagHashTable[] = {
    7,    16,    27,    40,    53,    60,     0,     4,     1,     1,
   12,     6,    14,     8,    17,    16,     5,     0,     0,    13,
    7,    15,     9,    18,    17,    26,   194,     6,     3,     3,
    5,    80,     8,     2,    10,     4,    23,    22,    25,    24,
    6,     2,     2,     4,    50,     9,     3,    11,     5,    16,
   15,    24,    23,     3,     6,     0,    19,    18,    21,    20,
    3,     7,     1,    20,    19,    22,    21,
};

vtkDICOMDictionary::Dict Dict361Data = {
"Philips PET Private Group",
6,
27,
Dict361TagHashTable,
Dict361Contents
};

// ----- GEMS-IT/Centricity RA600/7.0 -----

DictEntry Dict362Contents[] = {
{ 0x4113, 0x0010, 0, VR::UI, VM::M1, "NumberOfImagesInStudy" },
};

unsigned short Dict362TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict362Data = {
"GEMS-IT/Centricity RA600/7.0",
1,
1,
Dict362TagHashTable,
Dict362Contents
};

// ----- syngoDynamics_Reporting -----

DictEntry Dict363Contents[] = {
{ 0x0021, 0x00AD, 0, VR::OB, VM::M1, "Data" },
};

unsigned short Dict363TagHashTable[] = {
    2,     0,     1,     0,   173,
};

vtkDICOMDictionary::Dict Dict363Data = {
"syngoDynamics_Reporting",
1,
1,
Dict363TagHashTable,
Dict363Contents
};

// ----- Harmony R1.0 C3 -----

DictEntry Dict364Contents[] = {
{ 0x0019, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0007, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x000b, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0050, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0051, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0052, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0053, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x005a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005b, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x005c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x005f, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0079, 0, VR::PN, VM::M1, "" },
{ 0x0019, 0x007a, 0, VR::PN, VM::M1, "" },
{ 0x0019, 0x007b, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x007c, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x007d, 0, VR::CS, VM::M1, "" },
{ 0x0019, 0x007e, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x007f, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0083, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0094, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0095, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0096, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0097, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0098, 0, VR::IS, VM::M1TN, "" },
{ 0x0019, 0x00e4, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x00e5, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00e6, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00e7, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00e8, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00e9, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ea, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00eb, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ec, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00ed, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00ee, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00ef, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x00f0, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00f1, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x00f2, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict364TagHashTable[] = {
   11,    20,    31,    46,    57,    66,    79,    88,    95,   102,
    0,     4,     2,     7,    16,   124,    25,   151,    33,   234,
    5,    11,    95,    17,   125,    24,   150,    26,   152,    34,
  235,     7,     4,    80,    18,   126,    21,   131,    23,   149,
   29,   230,    31,   232,    41,   242,     5,     5,    81,    19,
  127,    22,   148,    30,   231,    32,   233,     4,     6,    82,
   27,   228,    37,   238,    39,   240,     6,     0,     0,     7,
   83,    20,   128,    28,   229,    38,   239,    40,   241,     4,
    1,     3,     8,    90,    12,   120,    35,   236,     3,     9,
   91,    13,   121,    36,   237,     3,     3,    11,    10,    92,
   14,   122,     1,    15,   123,
};

vtkDICOMDictionary::Dict Dict364Data = {
"Harmony R1.0 C3",
10,
42,
Dict364TagHashTable,
Dict364Contents
};

// ----- Harmony R1.0 C2 -----

DictEntry Dict365Contents[] = {
{ 0x0019, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0001, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0004, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0007, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0008, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0009, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x000a, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x006a, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x006c, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x006d, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x006e, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0074, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0076, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0078, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0079, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x007a, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0080, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0081, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0082, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0083, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0084, 0, VR::UN, VM::M1, "" },
{ 0x0019, 0x0091, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict365TagHashTable[] = {
    7,    20,    29,    40,    49,    58,     0,     6,     1,     1,
    7,     7,    11,   106,    15,   116,    17,   120,    25,   145,
    4,     0,     0,     6,     6,    10,    10,    18,   121,     5,
    3,     3,    12,   108,    16,   118,    19,   122,    23,   131,
    4,     2,     2,    13,   109,    22,   130,    24,   132,     4,
    5,     5,     9,     9,    14,   110,    21,   129,     3,     4,
    4,     8,     8,    20,   128,
};

vtkDICOMDictionary::Dict Dict365Data = {
"Harmony R1.0 C2",
6,
26,
Dict365TagHashTable,
Dict365Contents
};

// ----- SEGAMI__MEMO -----

DictEntry Dict366Contents[] = {
{ 0x0035, 0x0097, 0, VR::SH, VM::M1, "" },
{ 0x0035, 0x0098, 0, VR::LT, VM::M1, "" },
};

unsigned short Dict366TagHashTable[] = {
    2,     0,     2,     0,   151,     1,   152,
};

vtkDICOMDictionary::Dict Dict366Data = {
"SEGAMI__MEMO",
1,
2,
Dict366TagHashTable,
Dict366Contents
};

// ----- AGFA -----

DictEntry Dict367Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0011, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0013, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0014, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0015, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::ST, VM::M1, "CassetteDataStream" },
{ 0x0019, 0x0010, 0, VR::ST, VM::M1, "ImageProcessingParameters" },
{ 0x0019, 0x0011, 0, VR::LO, VM::M1, "IdentificationData" },
{ 0x0019, 0x0013, 0, VR::LO, VM::M1, "SensitometryName" },
{ 0x0019, 0x0014, 0, VR::ST, VM::M1, "WindowLevelList" },
{ 0x0019, 0x0015, 0, VR::LO, VM::M1, "DoseMonitoring" },
{ 0x0019, 0x0016, 0, VR::LO, VM::M1, "OtherInfo" },
{ 0x0019, 0x001a, 0, VR::LO, VM::M1, "ClippedExposureDeviation" },
{ 0x0019, 0x001b, 0, VR::LO, VM::M1, "Logarithmic PLT Full Scale" },
{ 0x0019, 0x0060, 0, VR::US, VM::M1, "TotalNumberSeries" },
{ 0x0019, 0x0061, 0, VR::SH, VM::M1, "SessionNumber" },
{ 0x0019, 0x0062, 0, VR::SH, VM::M1, "IDStationName" },
{ 0x0019, 0x0065, 0, VR::US, VM::M1, "NumberOfImagesInStudyToBeTransmitted" },
{ 0x0019, 0x0070, 0, VR::US, VM::M1, "TotalNumberImages" },
{ 0x0019, 0x0080, 0, VR::ST, VM::M1, "GeometricalTransformations" },
{ 0x0019, 0x0081, 0, VR::ST, VM::M1, "RoamOrigin" },
{ 0x0019, 0x0082, 0, VR::US, VM::M1, "ZoomFactor" },
{ 0x0019, 0x0093, 0, VR::CS, VM::M1, "Status" },
};

unsigned short Dict367TagHashTable[] = {
    6,    19,    26,    33,    46,     0,     6,     0,    16,     8,
   19,    11,    22,    14,    96,    17,   101,    19,   128,     3,
    2,    19,    15,    97,    22,   147,     3,    10,    21,    13,
   27,    16,    98,     6,     4,    21,     5,     5,     7,    17,
    9,    20,    12,    26,    21,   130,     5,     1,    17,     3,
   20,     6,    16,    18,   112,    20,   129,
};

vtkDICOMDictionary::Dict Dict367Data = {
"AGFA",
5,
23,
Dict367TagHashTable,
Dict367Contents
};

// ----- Philips Imaging DD 067 -----

DictEntry Dict368Contents[] = {
{ 0x4001, 0x0000, 0, VR::SQ, VM::M1, "" },
{ 0x4001, 0x0001, 0, VR::CS, VM::M1, "" },
{ 0x4001, 0x0008, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict368TagHashTable[] = {
    2,     0,     3,     0,     0,     1,     1,     2,     8,
};

vtkDICOMDictionary::Dict Dict368Data = {
"Philips Imaging DD 067",
1,
3,
Dict368TagHashTable,
Dict368Contents
};

// ----- DLX_EXAMS_01 -----

DictEntry Dict369Contents[] = {
{ 0x0015, 0x0001, 0, VR::DS, VM::M1, "StenosisCalibrationRatio" },
{ 0x0015, 0x0002, 0, VR::DS, VM::M1, "StenosisMagnification" },
{ 0x0015, 0x0003, 0, VR::DS, VM::M1, "CardiacCalibrationRatio" },
};

unsigned short Dict369TagHashTable[] = {
    2,     0,     3,     0,     1,     1,     2,     2,     3,
};

vtkDICOMDictionary::Dict Dict369Data = {
"DLX_EXAMS_01",
1,
3,
Dict369TagHashTable,
Dict369Contents
};

// ----- Philips Imaging DD 065 -----

DictEntry Dict370Contents[] = {
{ 0x4007, 0x0000, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict370TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict370Data = {
"Philips Imaging DD 065",
1,
1,
Dict370TagHashTable,
Dict370Contents
};

// ----- GE_GROUP -----

DictEntry Dict371Contents[] = {
{ 0x6005, 0x0010, 0, VR::UT, VM::M1, "" },
};

unsigned short Dict371TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict371Data = {
"GE_GROUP",
1,
1,
Dict371TagHashTable,
Dict371Contents
};

// ----- SIEMENS SYNGO OBJECT GRAPHICS -----

DictEntry Dict372Contents[] = {
{ 0x0071, 0x0000, 0, VR::SQ, VM::M1, "GraphicObjectSequence" },
{ 0x0071, 0x0001, 0, VR::SL, VM::M1, "FillStyleVersion" },
{ 0x0071, 0x0002, 0, VR::FL, VM::M4, "FillBackgroundColor" },
{ 0x0071, 0x0003, 0, VR::FL, VM::M4, "FillForegroundColor" },
{ 0x0071, 0x0004, 0, VR::SL, VM::M1, "FillMode" },
{ 0x0071, 0x0005, 0, VR::OB, VM::M1, "FillPattern" },
{ 0x0071, 0x0006, 0, VR::SL, VM::M1, "LineStyleVersion" },
{ 0x0071, 0x0007, 0, VR::FL, VM::M4, "LineBackgroundColor" },
{ 0x0071, 0x0008, 0, VR::FL, VM::M4, "LineForegroundColor" },
{ 0x0071, 0x0009, 0, VR::DS, VM::M1, "LineType" },
{ 0x0071, 0x0010, 0, VR::DS, VM::M1, "LineThickness" },
{ 0x0071, 0x0011, 0, VR::DS, VM::M1, "LineShadowXOffset" },
{ 0x0071, 0x0012, 0, VR::DS, VM::M1, "LineShadowYOffset" },
{ 0x0071, 0x0013, 0, VR::DS, VM::M1, "ShadowStyle" },
{ 0x0071, 0x0014, 0, VR::FL, VM::M4, "ShadowColor" },
{ 0x0071, 0x0015, 0, VR::DS, VM::M1, "StipplePattern" },
{ 0x0071, 0x0016, 0, VR::DS, VM::M1, "LineAntiAliasing" },
{ 0x0071, 0x0017, 0, VR::CS, VM::M1, "Line-Z-BlendFlag" },
{ 0x0071, 0x0018, 0, VR::SL, VM::M1, "TextStyleVersion" },
{ 0x0071, 0x0019, 0, VR::FL, VM::M4, "TextColor" },
{ 0x0071, 0x0020, 0, VR::SL, VM::M1, "TextHorizontalAlign" },
{ 0x0071, 0x0021, 0, VR::SL, VM::M1, "TextVerticalAlign" },
{ 0x0071, 0x0022, 0, VR::DS, VM::M1, "TextShadowXOffset" },
{ 0x0071, 0x0023, 0, VR::DS, VM::M1, "TextShadowYOffset" },
{ 0x0071, 0x0024, 0, VR::SL, VM::M1, "TextShadowStyle" },
{ 0x0071, 0x0025, 0, VR::FL, VM::M4, "TextShadowColor" },
{ 0x0071, 0x0026, 0, VR::CS, VM::M1TN, "TextLogFont" },
{ 0x0071, 0x0027, 0, VR::CS, VM::M1, "Text-Z-BlendFlag" },
{ 0x0071, 0x0028, 0, VR::OB, VM::M1, "GraphicBitMask" },
{ 0x0071, 0x0029, 0, VR::CS, VM::M1, "VisiblilityFlag" },
{ 0x0071, 0x0030, 0, VR::SL, VM::M1, "GraphicSensitivity" },
{ 0x0071, 0x0031, 0, VR::SL, VM::M1, "GraphicPickModeType" },
{ 0x0071, 0x0032, 0, VR::SL, VM::M1, "GraphicLayer" },
{ 0x0071, 0x0033, 0, VR::SL, VM::M1, "GraphicObjectVersion" },
{ 0x0071, 0x0034, 0, VR::SL, VM::M1, "GraphicCoordinateSystem" },
{ 0x0071, 0x0035, 0, VR::CS, VM::M1, "GraphicCustomAttributes" },
{ 0x0071, 0x0036, 0, VR::CS, VM::M1, "GraphicCustomAttributesKey" },
{ 0x0071, 0x0037, 0, VR::CS, VM::M1, "GraphicCustomAttributesValue" },
{ 0x0071, 0x0038, 0, VR::CS, VM::M1, "GraphicViewName" },
{ 0x0071, 0x0039, 0, VR::DS, VM::M3, "GraphicData" },
{ 0x0071, 0x0040, 0, VR::CS, VM::M1, "GraphicType" },
{ 0x0071, 0x0041, 0, VR::US, VM::M1, "NumberOfGraphicPoints" },
{ 0x0071, 0x0042, 0, VR::DS, VM::M1, "AxisMainTickLength" },
{ 0x0071, 0x0043, 0, VR::DS, VM::M1, "AxisDetailTickLength" },
{ 0x0071, 0x0044, 0, VR::DS, VM::M1, "AxisMainTickSpacing" },
{ 0x0071, 0x0045, 0, VR::DS, VM::M1TN, "AxisDetailTickSpacing" },
{ 0x0071, 0x0046, 0, VR::DS, VM::M1, "AxisMainTickCount" },
{ 0x0071, 0x0047, 0, VR::DS, VM::M1, "AxisDetailTickCount" },
{ 0x0071, 0x0048, 0, VR::SL, VM::M1, "AxisTickBehavior" },
{ 0x0071, 0x0049, 0, VR::SL, VM::M1, "AxisTickAligment" },
{ 0x0071, 0x0050, 0, VR::DS, VM::M1, "AxisStep" },
{ 0x0071, 0x0051, 0, VR::SL, VM::M1, "AxisStepIndex" },
{ 0x0071, 0x0052, 0, VR::CS, VM::M1, "AxisTextFormat" },
{ 0x0071, 0x0053, 0, VR::CS, VM::M1, "AxisShowCenterTextFlag" },
{ 0x0071, 0x0054, 0, VR::CS, VM::M1, "AxisShowTickTextFlag" },
{ 0x0071, 0x0055, 0, VR::DS, VM::M3, "BitmapXOrientation" },
{ 0x0071, 0x0056, 0, VR::DS, VM::M3, "BitmapYOrientation" },
{ 0x0071, 0x0057, 0, VR::OB, VM::M1, "GraphicBlob" },
{ 0x0071, 0x0058, 0, VR::CS, VM::M1, "GraphicInterpolation" },
{ 0x0071, 0x0059, 0, VR::DS, VM::M1, "GraphicAngle" },
{ 0x0071, 0x0060, 0, VR::DS, VM::M1, "GraphicSize" },
{ 0x0071, 0x0061, 0, VR::CS, VM::M1, "CutLineSide" },
{ 0x0071, 0x0062, 0, VR::DS, VM::M1, "GraphicTipLength" },
{ 0x0071, 0x0063, 0, VR::DS, VM::M1, "CutLineArrowLength" },
{ 0x0071, 0x0064, 0, VR::DS, VM::M1, "LineGapLength" },
{ 0x0071, 0x0065, 0, VR::DS, VM::M1, "GraphicCircleRadius" },
{ 0x0071, 0x0066, 0, VR::DS, VM::M1, "LineDistanceMove" },
{ 0x0071, 0x0067, 0, VR::DS, VM::M1, "LineMarkerLength" },
{ 0x0071, 0x0068, 0, VR::DS, VM::M3, "GraphicCenter" },
{ 0x0071, 0x0069, 0, VR::DS, VM::M3, "RangeCenterAreaTopLeft" },
{ 0x0071, 0x0070, 0, VR::DS, VM::M3, "RangeCenterAreaBottomRight" },
{ 0x0071, 0x0071, 0, VR::DS, VM::M1, "RangeTilt" },
{ 0x0071, 0x0072, 0, VR::DS, VM::M1, "RangeMinimumTilt" },
{ 0x0071, 0x0073, 0, VR::DS, VM::M1, "RangeMaximumTilt" },
{ 0x0071, 0x0074, 0, VR::DS, VM::M1, "GraphicWidth" },
{ 0x0071, 0x0075, 0, VR::DS, VM::M1, "RangeMinimumWidth" },
{ 0x0071, 0x0076, 0, VR::DS, VM::M1, "RangeMaximumWidth" },
{ 0x0071, 0x0077, 0, VR::DS, VM::M1, "GraphicHeight" },
{ 0x0071, 0x0078, 0, VR::DS, VM::M1, "RangeFeed" },
{ 0x0071, 0x0079, 0, VR::CS, VM::M1, "RangeDirection" },
{ 0x0071, 0x0080, 0, VR::CS, VM::M1, "RangeShowScans" },
{ 0x0071, 0x0081, 0, VR::DS, VM::M1, "RangeMinimumScanDistance" },
{ 0x0071, 0x0082, 0, VR::CS, VM::M1, "RangeOrthogonalHeight" },
{ 0x0071, 0x0083, 0, VR::DS, VM::M3, "GraphicPosition" },
{ 0x0071, 0x0084, 0, VR::CS, VM::M1, "GraphicClosedFlag" },
{ 0x0071, 0x0085, 0, VR::SL, VM::M1, "RangeLineTipMode" },
{ 0x0071, 0x0086, 0, VR::SL, VM::M1, "GraphicListCount" },
{ 0x0071, 0x0087, 0, VR::CS, VM::M1, "AxisFlipTextFlag" },
{ 0x0071, 0x0088, 0, VR::CS, VM::M1, "CurveDiagramType" },
{ 0x0071, 0x0089, 0, VR::DS, VM::M1, "GraphicStartAngle" },
{ 0x0071, 0x0090, 0, VR::DS, VM::M1, "GraphicEndAngle" },
{ 0x0071, 0x0091, 0, VR::IS, VM::M1, "LiveWireSmoothness" },
{ 0x0071, 0x0092, 0, VR::CS, VM::M1, "LiveWireSplineFlag" },
{ 0x0071, 0x0093, 0, VR::CS, VM::M1, "EllipseCircleFlag" },
{ 0x0071, 0x0094, 0, VR::CS, VM::M1, "GraphicSquareFlag" },
{ 0x0071, 0x0095, 0, VR::DS, VM::M1, "CurveSectionStartIndex" },
{ 0x0071, 0x0096, 0, VR::DS, VM::M1, "CurveSectionEndIndex" },
{ 0x0071, 0x0097, 0, VR::DS, VM::M1, "MarkerAlpha" },
{ 0x0071, 0x0098, 0, VR::IS, VM::M1, "TableRowCount" },
{ 0x0071, 0x0099, 0, VR::IS, VM::M1, "TableColumnCount" },
{ 0x0071, 0x009A, 0, VR::DS, VM::M1, "TableRowHeight" },
{ 0x0071, 0x009B, 0, VR::DS, VM::M1, "TableColumnWidth" },
{ 0x0071, 0x009C, 0, VR::IS, VM::M1, "RectangleSelectionSegmentOffset" },
{ 0x0071, 0x009D, 0, VR::CS, VM::M1, "GraphicText" },
{ 0x0071, 0x00A0, 0, VR::SL, VM::M1, "AxisTickSpacingCoordinateSystem" },
{ 0x0071, 0x00A1, 0, VR::CS, VM::M1, "AxisDiagramGridType" },
{ 0x0071, 0x00A2, 0, VR::SL, VM::M1, "PolarPlotCircleCount" },
{ 0x0071, 0x00A3, 0, VR::SL, VM::M1, "PolarPlotLines-per-Circle" },
{ 0x0071, 0x00A4, 0, VR::SL, VM::M1, "PolarPlotCompartmentCount" },
{ 0x0071, 0x00A5, 0, VR::SL, VM::M1, "PolarPlotRadiusWeight" },
{ 0x0071, 0x00A6, 0, VR::DS, VM::M1, "CircleSegmentOuterRadius" },
{ 0x0071, 0x00A7, 0, VR::CS, VM::M1, "CircleSegmentClockwiseFlag" },
{ 0x0071, 0x00A8, 0, VR::CS, VM::M1, "AxisDiagramAutoResizeFlag" },
{ 0x0071, 0x00A9, 0, VR::DS, VM::M1, "AxisDiagramStepStart" },
{ 0x0071, 0x00B0, 0, VR::CS, VM::M1, "GroupRoot" },
{ 0x0071, 0x00B1, 0, VR::ST, VM::M1, "GroupName" },
{ 0x0071, 0x00B2, 0, VR::SQ, VM::M1, "GraphicAnnotationSequence" },
{ 0x0071, 0x00B3, 0, VR::SL, VM::M1, "TextMinimumHeight" },
{ 0x0071, 0x00B4, 0, VR::DS, VM::M1, "TextFontScalingFactor" },
{ 0x0071, 0x00B5, 0, VR::SL, VM::M2, "TextMaximumExtensions" },
{ 0x0071, 0x00B6, 0, VR::CS, VM::M1, "TextSegmentSize" },
{ 0x0071, 0x00B7, 0, VR::SL, VM::M1, "GraphicObjectReferenceLabel" },
};

unsigned short Dict372TagHashTable[] = {
   31,    40,    49,    58,    67,    78,    89,   100,   111,   122,
  133,   142,   151,   158,   165,   172,   179,   186,   193,   202,
  211,   220,   229,   240,   251,   262,   273,   280,   287,   296,
    0,     4,     8,     8,    71,   113,    82,   130,   104,   160,
    4,     9,     9,    70,   112,    83,   131,   105,   161,     4,
   51,    81,    73,   115,    80,   128,   110,   166,     4,    50,
   80,    72,   114,    81,   129,   111,   167,     5,    30,    48,
   53,    83,    75,   117,    86,   134,   108,   164,     5,    31,
   49,    52,    82,    74,   116,    87,   135,   109,   165,     5,
   10,    16,    32,    50,    55,    85,    77,   119,    84,   132,
    5,    11,    17,    33,    51,    54,    84,    76,   118,    85,
  133,     5,    12,    18,    34,    52,    57,    87,    79,   121,
  112,   168,     5,    13,    19,    35,    53,    56,    86,    78,
  120,   113,   169,     4,    14,    20,    36,    54,    59,    89,
   88,   136,     4,    15,    21,    37,    55,    58,    88,    89,
  137,     3,    16,    22,    38,    56,   116,   178,     3,    17,
   23,    39,    57,   117,   179,     3,    18,    24,    92,   146,
  114,   176,     3,    19,    25,    93,   147,   115,   177,     3,
   61,    97,    90,   144,   120,   182,     3,    60,    96,    91,
  145,   121,   183,     4,    41,    65,    63,    99,    96,   150,
  118,   180,     4,    40,    64,    62,    98,    97,   151,   119,
  181,     4,    20,    32,    43,    67,    65,   101,    94,   148,
    4,    21,    33,    42,    66,    64,   100,    95,   149,     5,
    0,     0,    22,    34,    45,    69,    67,   103,   100,   154,
    5,     1,     1,    23,    35,    44,    68,    66,   102,   101,
  155,     5,     2,     2,    24,    36,    47,    71,    69,   105,
   98,   152,     5,     3,     3,    25,    37,    46,    70,    68,
  104,    99,   153,     3,     4,     4,    26,    38,    49,    73,
    3,     5,     5,    27,    39,    48,    72,     4,     6,     6,
   28,    40,   102,   156,   106,   162,     4,     7,     7,    29,
   41,   103,   157,   107,   163,
};

vtkDICOMDictionary::Dict Dict372Data = {
"SIEMENS SYNGO OBJECT GRAPHICS",
30,
122,
Dict372TagHashTable,
Dict372Contents
};

// ----- Visus Change -----

DictEntry Dict373Contents[] = {
{ 0x5533, 0x0033, 0, VR::SQ, VM::M1, "SaveSequence" },
{ 0x5533, 0x0035, 0, VR::DA, VM::M1, "SaveDate" },
{ 0x5533, 0x0037, 0, VR::LO, VM::M1, "SaveOriginator" },
{ 0x5533, 0x0039, 0, VR::FD, VM::M1, "SaveID" },
};

unsigned short Dict373TagHashTable[] = {
    2,     0,     4,     0,    51,     1,    53,     2,    55,     3,
   57,
};

vtkDICOMDictionary::Dict Dict373Data = {
"Visus Change",
1,
4,
Dict373TagHashTable,
Dict373Contents
};

// ----- SIEMENS ISI -----

DictEntry Dict374Contents[] = {
{ 0x0003, 0x0008, 0, VR::US, VM::M1, "ISICommandField" },
{ 0x0003, 0x0011, 0, VR::US, VM::M1, "AttachIDApplicationCode" },
{ 0x0003, 0x0012, 0, VR::UL, VM::M1, "AttachIDMessageCount" },
{ 0x0003, 0x0013, 0, VR::DA, VM::M1, "AttachIDDate" },
{ 0x0003, 0x0014, 0, VR::TM, VM::M1, "AttachIDTime" },
{ 0x0003, 0x0020, 0, VR::US, VM::M1, "MessageType" },
{ 0x0003, 0x0030, 0, VR::DA, VM::M1, "MaxWaitingDate" },
{ 0x0003, 0x0031, 0, VR::TM, VM::M1, "MaxWaitingTime" },
{ 0x0009, 0x0001, 0, VR::UN, VM::M1, "RISPatientInfoIMGEF" },
{ 0x0011, 0x0003, 0, VR::LO, VM::M1, "PatientUID" },
{ 0x0011, 0x0004, 0, VR::LO, VM::M1, "PatientID" },
{ 0x0011, 0x000a, 0, VR::LO, VM::M1, "CaseID" },
{ 0x0011, 0x0022, 0, VR::LO, VM::M1, "RequestID" },
{ 0x0011, 0x0023, 0, VR::LO, VM::M1, "ExaminationUID" },
{ 0x0011, 0x00a1, 0, VR::DA, VM::M1, "PatientRegistrationDate" },
{ 0x0011, 0x00a2, 0, VR::TM, VM::M1, "PatientRegistrationTime" },
{ 0x0011, 0x00b0, 0, VR::LO, VM::M1, "PatientLastName" },
{ 0x0011, 0x00b2, 0, VR::LO, VM::M1, "PatientFirstName" },
{ 0x0011, 0x00b4, 0, VR::LO, VM::M1, "PatientHospitalStatus" },
{ 0x0011, 0x00bc, 0, VR::TM, VM::M1, "CurrentLocationTime" },
{ 0x0011, 0x00c0, 0, VR::LO, VM::M1, "PatientInsuranceStatus" },
{ 0x0011, 0x00d0, 0, VR::LO, VM::M1, "PatientBillingType" },
{ 0x0011, 0x00d2, 0, VR::LO, VM::M1, "PatientBillingAddress" },
{ 0x0031, 0x0012, 0, VR::LO, VM::M1, "ExaminationReason" },
{ 0x0031, 0x0030, 0, VR::DA, VM::M1, "RequestedDate" },
{ 0x0031, 0x0032, 0, VR::TM, VM::M1, "WorklistRequestStartTime" },
{ 0x0031, 0x0033, 0, VR::TM, VM::M1, "WorklistRequestEndTime" },
{ 0x0031, 0x004a, 0, VR::TM, VM::M1, "RequestedTime" },
{ 0x0031, 0x0080, 0, VR::LO, VM::M1, "RequestedLocation" },
{ 0x0055, 0x0046, 0, VR::LO, VM::M1, "CurrentWard" },
{ 0x0193, 0x0002, 0, VR::DS, VM::M1, "RISKey" },
{ 0x0307, 0x0001, 0, VR::UN, VM::M1, "RISWorklistIMGEF" },
{ 0x0309, 0x0001, 0, VR::UN, VM::M1, "RISReportIMGEF" },
{ 0x4009, 0x0001, 0, VR::LO, VM::M1, "ReportID" },
{ 0x4009, 0x0020, 0, VR::LO, VM::M1, "ReportStatus" },
{ 0x4009, 0x0030, 0, VR::DA, VM::M1, "ReportCreationDate" },
{ 0x4009, 0x0070, 0, VR::LO, VM::M1, "ReportApprovingPhysician" },
{ 0x4009, 0x00e0, 0, VR::LO, VM::M1, "ReportText" },
{ 0x4009, 0x00e1, 0, VR::LO, VM::M1, "ReportAuthor" },
{ 0x4009, 0x00e3, 0, VR::LO, VM::M1, "ReportingRadiologist" },
};

unsigned short Dict374TagHashTable[] = {
   11,    20,    35,    44,    53,    58,    67,    70,    83,    96,
    0,     4,     7,    49,    13,    35,    20,   192,    36,   112,
    7,     0,     8,     6,    48,    10,     4,    12,    34,    17,
  178,    24,    48,    34,    32,     4,    22,   210,    26,    51,
   27,    74,    32,     1,     4,     4,    20,    16,   176,    25,
   50,    39,   227,     2,    21,   208,    37,   224,     4,     5,
   32,    19,   188,    23,    18,    38,   225,     1,     3,    19,
    6,     2,    18,    11,    10,    15,   162,    18,   180,    30,
    2,    35,    48,     6,     1,    17,     8,     1,     9,     3,
   14,   161,    31,     1,    33,     1,     2,    28,   128,    29,
   70,
};

vtkDICOMDictionary::Dict Dict374Data = {
"SIEMENS ISI",
10,
40,
Dict374TagHashTable,
Dict374Contents
};

// ----- PHILIPS MR R5.6/PART -----

DictEntry Dict375Contents[] = {
{ 0x0019, 0x0000, 0, VR::DS, VM::M1, "FieldOfView" },
};

unsigned short Dict375TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict375Data = {
"PHILIPS MR R5.6/PART",
1,
1,
Dict375TagHashTable,
Dict375Contents
};

// ----- METAEMOTION GINKGO -----

DictEntry Dict376Contents[] = {
{ 0x0011, 0x0001, 0, VR::LT, VM::M1, "KeyFileIndicator" },
{ 0x0011, 0x000B, 0, VR::LT, VM::M1, "SerializedDiagnoseAndMarkers" },
};

unsigned short Dict376TagHashTable[] = {
    2,     0,     2,     0,     1,     1,    11,
};

vtkDICOMDictionary::Dict Dict376Data = {
"METAEMOTION GINKGO",
1,
2,
Dict376TagHashTable,
Dict376Contents
};

// ----- GEMS_IDEN_01 -----

DictEntry Dict377Contents[] = {
{ 0x0009, 0x0001, 0, VR::LO, VM::M1, "FullFidelity" },
{ 0x0009, 0x0002, 0, VR::SH, VM::M1, "SuiteId" },
{ 0x0009, 0x0004, 0, VR::SH, VM::M1, "ProductId" },
{ 0x0009, 0x0017, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x001a, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x0020, 0, VR::US, VM::M1, "" },
{ 0x0009, 0x0027, 0, VR::SL, VM::M1, "ImageActualDate" },
{ 0x0009, 0x002f, 0, VR::SH, VM::M1, "" },
{ 0x0009, 0x0030, 0, VR::SH, VM::M1, "ServiceId" },
{ 0x0009, 0x0031, 0, VR::SH, VM::M1, "MobileLocationNumber" },
{ 0x0009, 0x00e2, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x00e3, 0, VR::UI, VM::M1, "EquipmentUID" },
{ 0x0009, 0x00e6, 0, VR::SH, VM::M1, "GenesisVersionNow" },
{ 0x0009, 0x00e7, 0, VR::UL, VM::M1, "ExamRecordChecksum" },
{ 0x0009, 0x00e8, 0, VR::UL, VM::M1, "SeriesSuiteID" },
{ 0x0009, 0x00e9, 0, VR::SL, VM::M1, "ActualSeriesDataTimeStamp" },
};

unsigned short Dict377TagHashTable[] = {
    5,    14,    25,    34,     0,     4,     0,     1,     9,    49,
   10,   226,    12,   230,     5,     2,     4,     5,    32,     8,
   48,    11,   227,    13,   231,     4,     3,    23,     6,    39,
    7,    47,    14,   232,     3,     1,     2,     4,    26,    15,
  233,
};

vtkDICOMDictionary::Dict Dict377Data = {
"GEMS_IDEN_01",
4,
16,
Dict377TagHashTable,
Dict377Contents
};

// ----- SIEMENS MED ECAT FILE INFO -----

DictEntry Dict378Contents[] = {
{ 0x0021, 0x0000, 0, VR::OB, VM::M1, "ECATMainHeader" },
{ 0x0021, 0x0001, 0, VR::OB, VM::M1, "ECATImageSubheader" },
};

unsigned short Dict378TagHashTable[] = {
    2,     0,     2,     0,     0,     1,     1,
};

vtkDICOMDictionary::Dict Dict378Data = {
"SIEMENS MED ECAT FILE INFO",
1,
2,
Dict378TagHashTable,
Dict378Contents
};

// ----- SIEMENS CT APPL EVIDENCEDOCUMENT -----

DictEntry Dict379Contents[] = {
{ 0x0029, 0x0000, 0, VR::UT, VM::M1, "PrivateTaskDatamodel" },
};

unsigned short Dict379TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict379Data = {
"SIEMENS CT APPL EVIDENCEDOCUMENT",
1,
1,
Dict379TagHashTable,
Dict379Contents
};

// ----- Viewing Protocol -----

DictEntry Dict380Contents[] = {
{ 0x0065, 0x0093, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict380TagHashTable[] = {
    2,     0,     1,     0,   147,
};

vtkDICOMDictionary::Dict Dict380Data = {
"Viewing Protocol",
1,
1,
Dict380TagHashTable,
Dict380Contents
};

// ----- SIEMENS DFR.01 MANIPULATED -----

DictEntry Dict381Contents[] = {
{ 0x0017, 0x0011, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0012, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0014, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0015, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0025, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0027, 0, VR::IS, VM::M1, "" },
{ 0x0017, 0x0029, 0, VR::IS, VM::M1, "EdgeEnhancement" },
{ 0x0017, 0x0030, 0, VR::IS, VM::M1, "Harmonization" },
{ 0x0017, 0x0031, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0033, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0035, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0037, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0038, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0071, 0, VR::IS, VM::M1, "Landmark" },
{ 0x0017, 0x0072, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0073, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0074, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0077, 0, VR::DS, VM::M1, "PixelShiftHorizontal" },
{ 0x0017, 0x0078, 0, VR::DS, VM::M1, "PixelShiftVertical" },
{ 0x0017, 0x0079, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x007a, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0080, 0, VR::US, VM::M1, "" },
{ 0x0017, 0x0083, 0, VR::LO, VM::M1, "LeftMarker" },
{ 0x0017, 0x0084, 0, VR::LO, VM::M1, "RightMarker" },
{ 0x0017, 0x00a1, 0, VR::SH, VM::M1, "" },
{ 0x0017, 0x00a2, 0, VR::SH, VM::M1, "ImageNameExtension1" },
{ 0x0017, 0x00a3, 0, VR::SH, VM::M1, "ImageNameExtension2" },
};

unsigned short Dict381TagHashTable[] = {
    8,    13,    20,    29,    40,    45,    58,     0,     2,    17,
  116,    27,   163,     3,     4,    37,    10,    51,    26,   162,
    4,     3,    21,     9,    50,    15,   114,    22,   128,     5,
    2,    20,     8,    49,    16,   115,    21,   122,    23,   131,
    2,     7,    48,    12,    55,     6,     1,    18,    13,    56,
   14,   113,    19,   120,    24,   132,    25,   161,     6,     0,
   17,     5,    39,     6,    41,    11,    53,    18,   119,    20,
  121,
};

vtkDICOMDictionary::Dict Dict381Data = {
"SIEMENS DFR.01 MANIPULATED",
7,
28,
Dict381TagHashTable,
Dict381Contents
};

// ----- BioPri -----

DictEntry Dict382Contents[] = {
{ 0x0009, 0x0000, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0001, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x0002, 0, VR::UN, VM::M1, "" },
{ 0x0009, 0x0003, 0, VR::LO, VM::M1TN, "" },
{ 0x0009, 0x0004, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0005, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0007, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0008, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0009, 0, VR::LO, VM::M1, "" },
{ 0x0009, 0x0010, 0, VR::UN, VM::M1, "" },
};

unsigned short Dict382TagHashTable[] = {
    3,    14,     0,     5,     1,     1,     3,     3,     5,     5,
    6,     7,     8,     9,     5,     0,     0,     2,     2,     4,
    4,     7,     8,     9,    16,
};

vtkDICOMDictionary::Dict Dict382Data = {
"BioPri",
2,
10,
Dict382TagHashTable,
Dict382Contents
};

// ----- DL_INTERNAL_USE -----

DictEntry Dict383Contents[] = {
{ 0x0015, 0x008f, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict383TagHashTable[] = {
    2,     0,     1,     0,   143,
};

vtkDICOMDictionary::Dict Dict383Data = {
"DL_INTERNAL_USE",
1,
1,
Dict383TagHashTable,
Dict383Contents
};

// ----- Vital Images SW 3.4 -----

DictEntry Dict384Contents[] = {
{ 0x5653, 0x0010, 0, VR::OB, VM::M1, "SavedWorkflow" },
{ 0x5653, 0x0011, 0, VR::LO, VM::M1, "SavedWorkflowFileName" },
{ 0x5653, 0x0012, 0, VR::OB, VM::M1, "SavedWorkflowFileData" },
{ 0x5653, 0x0013, 0, VR::SL, VM::M1, "SavedWorkflowFileLength" },
{ 0x5653, 0x0014, 0, VR::SQ, VM::M1, "SavedWorkflowFileSequence" },
{ 0x5653, 0x0015, 0, VR::SQ, VM::M1, "ImageSequence" },
{ 0x5653, 0x0016, 0, VR::SL, VM::M1, "VolumeInterpolatedSlices" },
{ 0x5653, 0x0017, 0, VR::UI, VM::M1, "VolumeSOPInstanceUID" },
{ 0x5653, 0x0018, 0, VR::SH, VM::M1, "SavedWorkflowMark" },
{ 0x5653, 0x0019, 0, VR::UI, VM::M1, "" },
{ 0x5653, 0x0022, 0, VR::UI, VM::M1, "" },
{ 0x5653, 0x0023, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict384TagHashTable[] = {
    4,    13,    24,     0,     4,     1,    17,     2,    18,     4,
   20,     8,    24,     5,     3,    19,     5,    21,     6,    22,
    9,    25,    10,    34,     3,     0,    16,     7,    23,    11,
   35,
};

vtkDICOMDictionary::Dict Dict384Data = {
"Vital Images SW 3.4",
3,
12,
Dict384TagHashTable,
Dict384Contents
};

// ----- AMI Annotations_01 -----

DictEntry Dict385Contents[] = {
{ 0x3101, 0x0010, 0, VR::SQ, VM::M1, "AnnotationSequence" },
};

unsigned short Dict385TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict385Data = {
"AMI Annotations_01",
1,
1,
Dict385TagHashTable,
Dict385Contents
};

// ----- CAMTRONICS -----

DictEntry Dict386Contents[] = {
{ 0x0029, 0x0010, 0, VR::LT, VM::M1, "Commentline" },
{ 0x0029, 0x0020, 0, VR::DS, VM::M1, "EdgeEnhancementCoefficient" },
{ 0x0029, 0x0050, 0, VR::LT, VM::M1, "SceneText" },
{ 0x0029, 0x0060, 0, VR::LT, VM::M1, "ImageText" },
{ 0x0029, 0x0070, 0, VR::IS, VM::M1, "PixelShiftHorizontal" },
{ 0x0029, 0x0080, 0, VR::IS, VM::M1, "PixelShiftVertical" },
{ 0x0029, 0x0090, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict386TagHashTable[] = {
    2,     0,     7,     0,    16,     1,    32,     2,    80,     3,
   96,     4,   112,     5,   128,     6,   144,
};

vtkDICOMDictionary::Dict Dict386Data = {
"CAMTRONICS",
1,
7,
Dict386TagHashTable,
Dict386Contents
};

// ----- Applicare/Print/Version 5.1 -----

DictEntry Dict387Contents[] = {
{ 0x4101, 0x0001, 0, VR::UL, VM::M1, "MaskState" },
{ 0x4101, 0x0002, 0, VR::SQ, VM::M1, "Annotations" },
{ 0x4101, 0x0003, 0, VR::LO, VM::M1, "Font" },
{ 0x4101, 0x0004, 0, VR::UL, VM::M1, "FontSize" },
{ 0x4101, 0x0005, 0, VR::FD, VM::M1, "FontRelativeSize" },
{ 0x4101, 0x0006, 0, VR::US, VM::M1, "Overlay" },
{ 0x4101, 0x0007, 0, VR::US, VM::M1, "PixelRep" },
{ 0x4101, 0x0008, 0, VR::US, VM::M1, "AnnotationLevel" },
{ 0x4101, 0x0009, 0, VR::US, VM::M1, "ShowCaliper" },
};

unsigned short Dict387TagHashTable[] = {
    3,    14,     0,     5,     0,     1,     2,     3,     4,     5,
    6,     7,     8,     9,     4,     1,     2,     3,     4,     5,
    6,     7,     8,
};

vtkDICOMDictionary::Dict Dict387Data = {
"Applicare/Print/Version 5.1",
2,
9,
Dict387TagHashTable,
Dict387Contents
};

// ----- GEHC_CT_ADVAPP_001 -----

DictEntry Dict388Contents[] = {
{ 0x0053, 0x0020, 0, VR::IS, VM::M1, "TableSpeedNotReachesTargetFlag" },
{ 0x0053, 0x0040, 0, VR::SH, VM::M1, "IterativeReconAnnotation" },
{ 0x0053, 0x0041, 0, VR::SH, VM::M1, "IterativeReconMode" },
{ 0x0053, 0x0042, 0, VR::LO, VM::M1, "IterativeReconConfiguration" },
{ 0x0053, 0x0043, 0, VR::SH, VM::M1, "IterativeReconLevel" },
{ 0x0053, 0x0060, 0, VR::SH, VM::M1, "ReconFlipRotateAnno" },
{ 0x0053, 0x0061, 0, VR::SH, VM::M1, "HighResolutionFlag" },
{ 0x0053, 0x0062, 0, VR::SH, VM::M1, "RespiratoryFlag" },
{ 0x0053, 0x009D, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict388TagHashTable[] = {
    3,    12,     0,     4,     0,    32,     2,    65,     4,    67,
    6,    97,     5,     1,    64,     3,    66,     5,    96,     7,
   98,     8,   157,
};

vtkDICOMDictionary::Dict Dict388Data = {
"GEHC_CT_ADVAPP_001",
2,
9,
Dict388TagHashTable,
Dict388Contents
};

// ----- NUD_PRIVATE -----

DictEntry Dict389Contents[] = {
{ 0x7777, 0x0002, 0, VR::UT, VM::M1, "Interfile" },
{ 0x7777, 0x0005, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict389TagHashTable[] = {
    2,     0,     2,     0,     2,     1,     5,
};

vtkDICOMDictionary::Dict Dict389Data = {
"NUD_PRIVATE",
1,
2,
Dict389TagHashTable,
Dict389Contents
};

// ----- astm.org/diconde/iod/NdeCtCalibrationData -----

DictEntry Dict390Contents[] = {
{ 0x0009, 0x0040, 0, VR::SQ, VM::M1, "DarkCurrentSequence" },
{ 0x0009, 0x0050, 0, VR::OW, VM::M1, "DarkCurrentCounts" },
{ 0x0009, 0x0060, 0, VR::SQ, VM::M1, "GainCorrectionReferenceSequence" },
{ 0x0009, 0x0070, 0, VR::OW, VM::M1, "AirCounts" },
{ 0x0009, 0x0071, 0, VR::DS, VM::M1, "KVUsedInGainCalibration" },
{ 0x0009, 0x0072, 0, VR::DS, VM::M1, "MAUsedInGainCalibration" },
{ 0x0009, 0x0073, 0, VR::DS, VM::M1, "NumberOfFramesUsedForIntegration" },
{ 0x0009, 0x0074, 0, VR::LO, VM::M1, "FilterMaterialUsedInGainCalibration" },
{ 0x0009, 0x0075, 0, VR::DS, VM::M1, "FilterThicknessUsedInGainCalibration" },
{ 0x0009, 0x0076, 0, VR::DA, VM::M1, "DateOfGainCalibration" },
{ 0x0009, 0x0077, 0, VR::TM, VM::M1, "TimeOfGainCalibration" },
{ 0x0009, 0x0080, 0, VR::OB, VM::M1, "BadPixelImage" },
{ 0x0009, 0x0099, 0, VR::LT, VM::M1, "CalibrationNotes" },
};

unsigned short Dict390TagHashTable[] = {
    4,    13,    24,     0,     4,     0,    64,     3,   112,     6,
  115,     9,   118,     5,     1,    80,     4,   113,     7,   116,
   10,   119,    11,   128,     4,     2,    96,     5,   114,     8,
  117,    12,   153,
};

vtkDICOMDictionary::Dict Dict390Data = {
"astm.org/diconde/iod/NdeCtCalibrationData",
3,
13,
Dict390TagHashTable,
Dict390Contents
};

// ----- SPI-P-Private-CWS Release 1 -----

DictEntry Dict391Contents[] = {
{ 0x0021, 0x0000, 0, VR::LT, VM::M1, "WindowOfImagesID" },
{ 0x0021, 0x0001, 0, VR::CS, VM::M1, "WindowOfImagesType" },
{ 0x0021, 0x0002, 0, VR::IS, VM::M1TN, "WindowOfImagesScope" },
};

unsigned short Dict391TagHashTable[] = {
    2,     0,     3,     0,     0,     1,     1,     2,     2,
};

vtkDICOMDictionary::Dict Dict391Data = {
"SPI-P-Private-CWS Release 1",
1,
3,
Dict391TagHashTable,
Dict391Contents
};

// ----- GEMS_SENO_02 -----

DictEntry Dict392Contents[] = {
{ 0x0045, 0x0004, 0, VR::CS, VM::M1, "AES" },
{ 0x0045, 0x0006, 0, VR::DS, VM::M1, "Angulation" },
{ 0x0045, 0x0009, 0, VR::DS, VM::M1, "RealMagnificationFactor" },
{ 0x0045, 0x000b, 0, VR::CS, VM::M1, "SenographType" },
{ 0x0045, 0x000c, 0, VR::DS, VM::M1, "IntegrationTime" },
{ 0x0045, 0x000d, 0, VR::DS, VM::M1, "ROIOriginXY" },
{ 0x0045, 0x0011, 0, VR::DS, VM::M2, "ReceptorSizeCmXY" },
{ 0x0045, 0x0012, 0, VR::IS, VM::M2, "ReceptorSizePixelsXY" },
{ 0x0045, 0x0013, 0, VR::ST, VM::M1, "Screen" },
{ 0x0045, 0x0014, 0, VR::DS, VM::M1, "PixelPitchMicrons" },
{ 0x0045, 0x0015, 0, VR::IS, VM::M1, "PixelDepthBits" },
{ 0x0045, 0x0016, 0, VR::IS, VM::M2, "BinningFactorXY" },
{ 0x0045, 0x001B, 0, VR::LO, VM::M1, "ClinicalView" },
{ 0x0045, 0x001D, 0, VR::DS, VM::M1, "MeanOfRawGrayLevels" },
{ 0x0045, 0x001E, 0, VR::DS, VM::M1, "MeanOfOffsetGrayLevels" },
{ 0x0045, 0x001F, 0, VR::DS, VM::M1, "MeanOfCorrectedGrayLevels" },
{ 0x0045, 0x0020, 0, VR::DS, VM::M1, "MeanOfRegionGrayLevels" },
{ 0x0045, 0x0021, 0, VR::DS, VM::M1, "MeanOfLogRegionGrayLevels" },
{ 0x0045, 0x0022, 0, VR::DS, VM::M1, "StandardDeviationOfRawGrayLevels" },
{ 0x0045, 0x0023, 0, VR::DS, VM::M1, "StandardDeviationOfCorrectedGrayLevels" },
{ 0x0045, 0x0024, 0, VR::DS, VM::M1, "StandardDeviationOfRegionGrayLevels" },
{ 0x0045, 0x0025, 0, VR::DS, VM::M1, "StandardDeviationOfLogRegionGrayLevels" },
{ 0x0045, 0x0026, 0, VR::OB, VM::M1, "MAOBuffer" },
{ 0x0045, 0x0027, 0, VR::IS, VM::M1, "SetNumber" },
{ 0x0045, 0x0028, 0, VR::CS, VM::M1, "WindowingType" },
{ 0x0045, 0x0029, 0, VR::DS, VM::M1TN, "WindowingParameters" },
{ 0x0045, 0x002a, 0, VR::IS, VM::M1, "CrosshairCursorXCoordinates" },
{ 0x0045, 0x002b, 0, VR::IS, VM::M1, "CrosshairCursorYCoordinates" },
{ 0x0045, 0x0039, 0, VR::US, VM::M1, "VignetteRows" },
{ 0x0045, 0x003a, 0, VR::US, VM::M1, "VignetteColumns" },
{ 0x0045, 0x003b, 0, VR::US, VM::M1, "VignetteBitsAllocated" },
{ 0x0045, 0x003c, 0, VR::US, VM::M1, "VignetteBitsStored" },
{ 0x0045, 0x003d, 0, VR::US, VM::M1, "VignetteHighBit" },
{ 0x0045, 0x003e, 0, VR::US, VM::M1, "VignettePixelRepresentation" },
{ 0x0045, 0x003f, 0, VR::OB, VM::M1, "VignettePixelData" },
{ 0x0045, 0x0049, 0, VR::DS, VM::M1, "RadiologicalThickness" },
{ 0x0045, 0x0050, 0, VR::UI, VM::M1, "FallbackInstanceUID" },
{ 0x0045, 0x0051, 0, VR::UI, VM::M1, "FallbackSeriesUID" },
{ 0x0045, 0x0052, 0, VR::IS, VM::M1, "RawDiagnosticLow" },
{ 0x0045, 0x0053, 0, VR::IS, VM::M1, "RawDiagnosticHigh" },
{ 0x0045, 0x0054, 0, VR::DS, VM::M1, "Exponent" },
{ 0x0045, 0x0055, 0, VR::IS, VM::M1, "ACoefficients" },
{ 0x0045, 0x0056, 0, VR::DS, VM::M1, "NoiseReductionSensitivity" },
{ 0x0045, 0x0057, 0, VR::DS, VM::M1, "NoiseReductionThreshold" },
{ 0x0045, 0x0058, 0, VR::DS, VM::M1, "Mu" },
{ 0x0045, 0x0059, 0, VR::IS, VM::M1, "Threshold" },
{ 0x0045, 0x0060, 0, VR::IS, VM::M4, "BreastROIX" },
{ 0x0045, 0x0061, 0, VR::IS, VM::M4, "BreastROIY" },
{ 0x0045, 0x0062, 0, VR::IS, VM::M1, "UserWindowCenter" },
{ 0x0045, 0x0063, 0, VR::IS, VM::M1, "UserWindowWidth" },
{ 0x0045, 0x0064, 0, VR::IS, VM::M1, "SegmentationThreshold" },
{ 0x0045, 0x0065, 0, VR::IS, VM::M1, "DetectorEntranceDose" },
{ 0x0045, 0x0066, 0, VR::IS, VM::M1, "AsymmetricalCollimationInformation" },
{ 0x0045, 0x0071, 0, VR::OB, VM::M1, "STXBuffer" },
{ 0x0045, 0x0072, 0, VR::DS, VM::M2, "ImageCropPoint" },
{ 0x0045, 0x0090, 0, VR::SH, VM::M1, "PremiumViewBeta" },
{ 0x0045, 0x00A0, 0, VR::DS, VM::M1, "SignalAverageFactor" },
{ 0x0045, 0x00A1, 0, VR::DS, VM::M2TN, "OrganDoseForSourceImages" },
{ 0x0045, 0x00A2, 0, VR::DS, VM::M2TN, "EntranceDoseInmGyForSourceImages" },
};

unsigned short Dict392TagHashTable[] = {
   15,    22,    31,    40,    49,    60,    69,    76,    87,    96,
  105,   118,   129,   138,     0,     3,    22,    38,    29,    58,
   45,    89,     4,     6,    17,    23,    39,    30,    59,    44,
   88,     4,     4,    12,     7,    18,    16,    32,    41,    85,
    4,     5,    13,     8,    19,    17,    33,    40,    84,     5,
   18,    34,    43,    87,    51,   101,    55,   144,    58,   162,
    4,    13,    29,    19,    35,    42,    86,    50,   100,     3,
   14,    30,    37,    81,    56,   160,     5,     2,     9,    15,
   31,    36,    80,    52,   102,    57,   161,     4,     0,     4,
   31,    60,    39,    83,    47,    97,     4,     3,    11,    32,
   61,    38,    82,    46,    96,     6,     1,     6,     9,    20,
   24,    40,    33,    62,    49,    99,    53,   113,     5,    10,
   21,    12,    27,    25,    41,    34,    63,    48,    98,     4,
   11,    22,    20,    36,    26,    42,    35,    73,     4,    21,
   37,    27,    43,    28,    57,    54,   114,
};

vtkDICOMDictionary::Dict Dict392Data = {
"GEMS_SENO_02",
14,
59,
Dict392TagHashTable,
Dict392Contents
};

// ----- BioPri3D -----

DictEntry Dict393Contents[] = {
{ 0x0011, 0x0020, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0024, 0, VR::DS, VM::M1TN, "" },
{ 0x0011, 0x0030, 0, VR::LO, VM::M1, "" },
{ 0x0011, 0x0031, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x0032, 0, VR::SL, VM::M1, "" },
{ 0x0011, 0x0039, 0, VR::CS, VM::M1, "" },
{ 0x0011, 0x003a, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x00d0, 0, VR::OB, VM::M1, "" },
{ 0x0011, 0x00e0, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x00e1, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x00e2, 0, VR::UL, VM::M1, "" },
{ 0x0011, 0x00e3, 0, VR::US, VM::M1, "" },
{ 0x0011, 0x00e4, 0, VR::US, VM::M1, "" },
{ 0x0011, 0x00e5, 0, VR::CS, VM::M1, "" },
{ 0x0063, 0x000c, 0, VR::DS, VM::M1TN, "" },
{ 0x0063, 0x0020, 0, VR::US, VM::M1, "" },
{ 0x0063, 0x0021, 0, VR::UL, VM::M1, "" },
{ 0x0063, 0x0035, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict393TagHashTable[] = {
    5,    12,    21,    32,     0,     3,     3,    49,     5,    57,
   10,   226,     4,     0,    32,     1,    36,     2,    48,    11,
  227,     5,     7,   208,     8,   224,    12,   228,    14,    12,
   15,    32,     6,     4,    50,     6,    58,     9,   225,    13,
  229,    16,    33,    17,    53,
};

vtkDICOMDictionary::Dict Dict393Data = {
"BioPri3D",
4,
18,
Dict393TagHashTable,
Dict393Contents
};

// ----- TOSHIBA_SR -----

DictEntry Dict394Contents[] = {
{ 0x7015, 0x0010, 0, VR::OB, VM::M1, "" },
{ 0x7015, 0x0060, 0, VR::OB, VM::M1, "" },
};

unsigned short Dict394TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    96,
};

vtkDICOMDictionary::Dict Dict394Data = {
"TOSHIBA_SR",
1,
2,
Dict394TagHashTable,
Dict394Contents
};

// ----- DIDI TO PCR 1.1 -----

DictEntry Dict395Contents[] = {
{ 0x0019, 0x0022, 0, VR::LO, VM::M1, "RouteAET" },
{ 0x0019, 0x0023, 0, VR::DS, VM::M1, "PCRPrintScale" },
{ 0x0019, 0x0024, 0, VR::ST, VM::M1, "PCRPrintJobEnd" },
{ 0x0019, 0x0025, 0, VR::IS, VM::M1, "PCRNoFilmCopies" },
{ 0x0019, 0x0026, 0, VR::IS, VM::M1, "PCRFilmLayoutPosition" },
{ 0x0019, 0x0027, 0, VR::ST, VM::M1, "PCRPrintReportName" },
{ 0x0019, 0x0070, 0, VR::ST, VM::M1, "RADProtocolPrinter" },
{ 0x0019, 0x0071, 0, VR::ST, VM::M1, "RADProtocolMedium" },
{ 0x0019, 0x0089, 0, VR::IS, VM::M1, "ExposureIndex" },
{ 0x0019, 0x008A, 0, VR::IS, VM::M1, "CollimatorX" },
{ 0x0019, 0x008B, 0, VR::IS, VM::M1, "CollimatorY" },
{ 0x0019, 0x008C, 0, VR::LO, VM::M1, "PrintMarker" },
{ 0x0019, 0x008D, 0, VR::LO, VM::M1, "RGDVName" },
{ 0x0019, 0x008E, 0, VR::LO, VM::M1, "AcqdSensitivity" },
{ 0x0019, 0x008F, 0, VR::LO, VM::M1, "ProcessingCategory" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "UnprocessedFlag" },
{ 0x0019, 0x0091, 0, VR::DS, VM::M1TN, "KeyValues" },
{ 0x0019, 0x0092, 0, VR::LO, VM::M1, "DestinationPostprocessingFunction" },
{ 0x0019, 0x00A0, 0, VR::LO, VM::M1, "Version" },
{ 0x0019, 0x00A1, 0, VR::LO, VM::M1, "RangingMode" },
{ 0x0019, 0x00A2, 0, VR::DS, VM::M1, "AbdomenBrightness" },
{ 0x0019, 0x00A3, 0, VR::DS, VM::M1, "FixedBrightness" },
{ 0x0019, 0x00A4, 0, VR::DS, VM::M1, "DetailContrast" },
{ 0x0019, 0x00A5, 0, VR::DS, VM::M1, "ContrastBalance" },
{ 0x0019, 0x00A6, 0, VR::DS, VM::M1, "StructureBoost" },
{ 0x0019, 0x00A7, 0, VR::DS, VM::M1, "StructurePreference" },
{ 0x0019, 0x00A8, 0, VR::DS, VM::M1, "NoiseRobustness" },
{ 0x0019, 0x00A9, 0, VR::DS, VM::M1, "NoiseDoseLimit" },
{ 0x0019, 0x00AA, 0, VR::DS, VM::M1, "NoiseDoseStep" },
{ 0x0019, 0x00AB, 0, VR::DS, VM::M1, "NoiseFrequencyLimit" },
{ 0x0019, 0x00AC, 0, VR::DS, VM::M1, "WeakContrastLimit" },
{ 0x0019, 0x00AD, 0, VR::DS, VM::M1, "StrongContrastLimit" },
{ 0x0019, 0x00AE, 0, VR::DS, VM::M1, "StructureBoostOffset" },
{ 0x0019, 0x00AF, 0, VR::LO, VM::M1, "SmoothGain" },
{ 0x0019, 0x00B0, 0, VR::LO, VM::M1, "MeasureField1" },
{ 0x0019, 0x00B1, 0, VR::LO, VM::M1, "MeasureField2" },
{ 0x0019, 0x00B2, 0, VR::IS, VM::M1, "KeyPercentile1" },
{ 0x0019, 0x00B3, 0, VR::IS, VM::M1, "KeyPercentile2" },
{ 0x0019, 0x00B4, 0, VR::IS, VM::M1, "DensityLUT" },
{ 0x0019, 0x00B5, 0, VR::DS, VM::M1, "Brightness" },
{ 0x0019, 0x00B6, 0, VR::DS, VM::M1, "Gamma" },
{ 0x0089, 0x0010, 0, VR::SQ, VM::M1, "StampImageSequence" },
};

unsigned short Dict395TagHashTable[] = {
   11,    22,    33,    38,    45,    54,    65,    72,    79,    92,
    0,     5,     3,    37,    12,   141,    23,   165,    33,   175,
   35,   177,     5,     2,    36,    11,   140,    22,   164,    32,
  174,    34,   176,     2,     5,    39,    31,   173,     3,     4,
   38,    30,   172,    40,   182,     4,     6,   112,    10,   139,
   21,   163,    39,   181,     5,     7,   113,     9,   138,    20,
  162,    38,   180,    41,    16,     3,     8,   137,    19,   161,
   29,   171,     3,    17,   146,    18,   160,    28,   170,     6,
    1,    35,    14,   143,    16,   145,    25,   167,    27,   169,
   37,   179,     6,     0,    34,    13,   142,    15,   144,    24,
  166,    26,   168,    36,   178,
};

vtkDICOMDictionary::Dict Dict395Data = {
"DIDI TO PCR 1.1",
10,
42,
Dict395TagHashTable,
Dict395Contents
};

// ----- SIEMENS MEDCOM OOG -----

DictEntry Dict396Contents[] = {
{ 0x0029, 0x0008, 0, VR::CS, VM::M1, "MedComOOGType" },
{ 0x0029, 0x0009, 0, VR::LO, VM::M1, "MedComOOGVersion" },
{ 0x0029, 0x0010, 0, VR::OB, VM::M1, "MedComOOGInfo" },
};

unsigned short Dict396TagHashTable[] = {
    2,     0,     3,     0,     8,     1,     9,     2,    16,
};

vtkDICOMDictionary::Dict Dict396Data = {
"SIEMENS MEDCOM OOG",
1,
3,
Dict396TagHashTable,
Dict396Contents
};

// ----- astm.org/diconde/iod/NdeDxDetector -----

DictEntry Dict397Contents[] = {
{ 0x0009, 0x0011, 0, VR::DS, VM::M1, "InternalDetectorFrameTime" },
{ 0x0009, 0x0012, 0, VR::DS, VM::M1, "NumberOfFramesIntegrated" },
{ 0x0009, 0x0020, 0, VR::SQ, VM::M1, "DetectorTemperatureSequence" },
{ 0x0009, 0x0022, 0, VR::DS, VM::M1, "SensorName" },
{ 0x0009, 0x0024, 0, VR::DS, VM::M1, "HorizontalOffsetOfSensor" },
{ 0x0009, 0x0026, 0, VR::DS, VM::M1, "VerticalOffsetOfSensor" },
{ 0x0009, 0x0028, 0, VR::DS, VM::M1, "SensorTemperature" },
};

unsigned short Dict397TagHashTable[] = {
    2,     0,     7,     0,    17,     1,    18,     2,    32,     3,
   34,     4,    36,     5,    38,     6,    40,
};

vtkDICOMDictionary::Dict Dict397Data = {
"astm.org/diconde/iod/NdeDxDetector",
1,
7,
Dict397TagHashTable,
Dict397Contents
};

// ----- PMTF INFORMATION DATA -----

DictEntry Dict398Contents[] = {
{ 0x0029, 0x0001, 0, VR::SQ, VM::M1, "" },
{ 0x0029, 0x0031, 0, VR::LO, VM::M1, "PMTFInformation1" },
{ 0x0029, 0x0032, 0, VR::UL, VM::M1, "PMTFInformation2" },
{ 0x0029, 0x0033, 0, VR::UL, VM::M1, "PMTFInformation3" },
{ 0x0029, 0x0034, 0, VR::CS, VM::M1, "PMTFInformation4" },
{ 0x0029, 0x0089, 0, VR::LO, VM::M1, "" },
{ 0x0029, 0x0090, 0, VR::OB, VM::M1, "" },
{ 0x7015, 0x0073, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict398TagHashTable[] = {
    3,    12,     0,     4,     0,     1,     1,    49,     3,    51,
    5,   137,     4,     2,    50,     4,    52,     6,   144,     7,
  115,
};

vtkDICOMDictionary::Dict Dict398Data = {
"PMTF INFORMATION DATA",
2,
8,
Dict398TagHashTable,
Dict398Contents
};

// ----- SIEMENS MED DISPLAY -----

DictEntry Dict399Contents[] = {
{ 0x0029, 0x0004, 0, VR::CS, VM::M1, "PhotometricInterpretation" },
{ 0x0029, 0x0010, 0, VR::US, VM::M1, "RowsOfSubmatrix" },
{ 0x0029, 0x0011, 0, VR::US, VM::M1, "ColumnsOfSubmatrix" },
{ 0x0029, 0x0020, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0021, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0050, 0, VR::US, VM::M1, "OriginOfSubmatrix" },
{ 0x0029, 0x0080, 0, VR::US, VM::M1, "" },
{ 0x0029, 0x0099, 0, VR::LO, VM::M1, "ShutterType" },
{ 0x0029, 0x00a0, 0, VR::US, VM::M1, "RowsOfRectangularShutter" },
{ 0x0029, 0x00a1, 0, VR::US, VM::M1, "ColumnsOfRectangularShutter" },
{ 0x0029, 0x00a2, 0, VR::US, VM::M1, "OriginOfRectangularShutter" },
{ 0x0029, 0x00b0, 0, VR::US, VM::M1, "RadiusOfCircularShutter" },
{ 0x0029, 0x00b2, 0, VR::US, VM::M1, "OriginOfCircularShutter" },
{ 0x0029, 0x00c1, 0, VR::US, VM::M1, "ContourOfIrregularShutter" },
};

unsigned short Dict399TagHashTable[] = {
    4,    19,    26,     0,     7,     0,     4,     1,    16,     3,
   32,     5,    80,     6,   128,     9,   161,    12,   178,     3,
    7,   153,     8,   160,    13,   193,     4,     2,    17,     4,
   33,    10,   162,    11,   176,
};

vtkDICOMDictionary::Dict Dict399Data = {
"SIEMENS MED DISPLAY",
3,
14,
Dict399TagHashTable,
Dict399Contents
};

// ----- MITRA LINKED ATTRIBUTES 1.0 -----

DictEntry Dict400Contents[] = {
{ 0x0031, 0x0020, 0, VR::IS, VM::M1, "" },
};

unsigned short Dict400TagHashTable[] = {
    2,     0,     1,     0,    32,
};

vtkDICOMDictionary::Dict Dict400Data = {
"MITRA LINKED ATTRIBUTES 1.0",
1,
1,
Dict400TagHashTable,
Dict400Contents
};

// ----- BRIT Systems, Inc. -----

DictEntry Dict401Contents[] = {
{ 0x0021, 0x0000, 0, VR::SQ, VM::M1, "PersonInformationSequence" },
{ 0x0021, 0x0001, 0, VR::LO, VM::M1, "PersonID" },
{ 0x0021, 0x0002, 0, VR::PN, VM::M1, "PersonName" },
{ 0x0021, 0x0003, 0, VR::LO, VM::M1, "PersonRole" },
{ 0x0021, 0x0004, 0, VR::SH, VM::M1, "PersonHomePhone" },
{ 0x0021, 0x0005, 0, VR::SH, VM::M1, "PersonWorkPhone" },
{ 0x0021, 0x0006, 0, VR::SH, VM::M1, "PersonCellPhone" },
{ 0x0021, 0x0007, 0, VR::SH, VM::M1, "PersonPagerPhone" },
{ 0x0021, 0x0008, 0, VR::SH, VM::M1, "PersonFaxPhone" },
{ 0x0021, 0x0009, 0, VR::LO, VM::M1, "PersonEMail" },
{ 0x0021, 0x000A, 0, VR::ST, VM::M1, "PersonAddress" },
{ 0x0021, 0x000B, 0, VR::LO, VM::M1, "PersonPassword" },
{ 0x0021, 0x000C, 0, VR::SH, VM::M1, "PersonEmergencyPhone" },
{ 0x0021, 0x000D, 0, VR::LO, VM::M1, "PhysicianID" },
{ 0x0021, 0x0011, 0, VR::LO, VM::M1, "OriginalPatientID" },
{ 0x0021, 0x0012, 0, VR::UI, VM::M1, "OriginalStudyInstanceUID" },
{ 0x0021, 0x0013, 0, VR::UI, VM::M1, "OriginalSeriesInstanceUID" },
{ 0x0021, 0x0014, 0, VR::LO, VM::M1, "MasterAccessionNumber" },
{ 0x0021, 0x0015, 0, VR::LO, VM::M1, "OrderCategory" },
{ 0x0021, 0x0016, 0, VR::LO, VM::M1, "PatientICN" },
{ 0x0021, 0x0017, 0, VR::LO, VM::M1, "PatientDFS" },
{ 0x0021, 0x0018, 0, VR::LO, VM::M1, "PatientClass" },
{ 0x0021, 0x0019, 0, VR::LO, VM::M1, "PatientType" },
{ 0x0021, 0x001F, 0, VR::LT, VM::M1, "GenericString" },
{ 0x0021, 0x0020, 0, VR::LO, VM::M1, "QCStudyAssignedBy" },
{ 0x0021, 0x0021, 0, VR::LO, VM::M1, "QCStudySplitBy" },
{ 0x0021, 0x0022, 0, VR::LO, VM::M1, "QCStudyMovedBy" },
{ 0x0021, 0x0023, 0, VR::LO, VM::M1, "QCStudyEditedBy" },
{ 0x0021, 0x0024, 0, VR::LO, VM::M1, "QCSeriesSplitBy" },
{ 0x0021, 0x0025, 0, VR::LO, VM::M1, "QCSeriesMovedBy" },
{ 0x0021, 0x0026, 0, VR::LO, VM::M1, "QCSeriesEditedBy" },
{ 0x0021, 0x0027, 0, VR::LO, VM::M1, "QCImageMovedBy" },
{ 0x0021, 0x0028, 0, VR::LO, VM::M1, "QCImageEditedBy" },
{ 0x0021, 0x0030, 0, VR::LO, VM::M1, "QCDoneTime" },
{ 0x0021, 0x0031, 0, VR::LO, VM::M1, "QCLastModificationTime" },
{ 0x0021, 0x0032, 0, VR::LO, VM::M1, "QCImageAcceptedBy" },
{ 0x0021, 0x0033, 0, VR::LO, VM::M1, "QCImageRejectedBy" },
{ 0x0021, 0x0034, 0, VR::DA, VM::M1, "QCLastModificationDate" },
{ 0x0021, 0x0050, 0, VR::LO, VM::M1, "QCDeletionRequested" },
{ 0x0021, 0x0090, 0, VR::AE, VM::M1, "OriginalSenderAETitle" },
{ 0x0021, 0x0091, 0, VR::LO, VM::M1, "SoftwareTitle" },
{ 0x0021, 0x0092, 0, VR::SH, VM::M1, "SoftwareVersion" },
{ 0x0021, 0x0093, 0, VR::LO, VM::M1, "SerialNumber" },
{ 0x0021, 0x00a0, 0, VR::SQ, VM::M1, "ObjectActionSequence" },
{ 0x0021, 0x00a1, 0, VR::ST, VM::M1, "ObjectAction" },
{ 0x0021, 0x00a2, 0, VR::DA, VM::M1, "ObjectActionDate" },
{ 0x0021, 0x00a3, 0, VR::TM, VM::M1, "ObjectActionTime" },
{ 0x0021, 0x00a5, 0, VR::AE, VM::M1, "LocalAETitle" },
{ 0x0021, 0x00a6, 0, VR::SH, VM::M1, "LocalIPAddress" },
{ 0x0021, 0x00a7, 0, VR::AE, VM::M1, "RemoteAETitle" },
{ 0x0021, 0x00a8, 0, VR::SH, VM::M1, "RemoteIPAddress" },
};

unsigned short Dict401TagHashTable[] = {
   13,    22,    29,    40,    47,    58,    67,    76,    87,    98,
  113,   120,     0,     4,     5,     5,    14,    17,    25,    33,
   49,   167,     3,     4,     4,    24,    32,    48,   166,     5,
    7,     7,    16,    19,    23,    31,    27,    35,    47,   165,
    3,     6,     6,    15,    18,    26,    34,     5,     9,     9,
   18,    21,    29,    37,    34,    49,    38,    80,     4,     8,
    8,    17,    20,    28,    36,    33,    48,     4,    11,    11,
   20,    23,    31,    39,    36,    51,     5,    10,    10,    19,
   22,    30,    38,    35,    50,    50,   168,     5,     1,     1,
   13,    13,    22,    25,    42,   147,    46,   163,     7,     0,
    0,    12,    12,    21,    24,    32,    40,    37,    52,    41,
  146,    45,   162,     3,     3,     3,    40,   145,    44,   161,
    3,     2,     2,    39,   144,    43,   160,
};

vtkDICOMDictionary::Dict Dict401Data = {
"BRIT Systems, Inc.",
12,
51,
Dict401TagHashTable,
Dict401Contents
};

// ----- SIEMENS CT VA0  RAW -----

DictEntry Dict402Contents[] = {
{ 0x0021, 0x0010, 0, VR::UL, VM::M2, "CreationMask" },
{ 0x0021, 0x0020, 0, VR::UL, VM::M2, "EvaluationMask" },
{ 0x0021, 0x0030, 0, VR::US, VM::M7, "ExtendedProcessingMask" },
{ 0x0021, 0x0040, 0, VR::UL, VM::M1TN, "" },
{ 0x0021, 0x0041, 0, VR::UL, VM::M1TN, "" },
{ 0x0021, 0x0042, 0, VR::UL, VM::M1TN, "" },
{ 0x0021, 0x0043, 0, VR::UL, VM::M1TN, "" },
{ 0x0021, 0x0044, 0, VR::UL, VM::M1TN, "" },
{ 0x0021, 0x0050, 0, VR::CS, VM::M1, "" },
};

unsigned short Dict402TagHashTable[] = {
    3,    12,     0,     4,     3,    64,     5,    66,     7,    68,
    8,    80,     5,     0,    16,     1,    32,     2,    48,     4,
   65,     6,    67,
};

vtkDICOMDictionary::Dict Dict402Data = {
"SIEMENS CT VA0  RAW",
2,
9,
Dict402TagHashTable,
Dict402Contents
};

// ----- SIEMENS Selma -----

DictEntry Dict403Contents[] = {
{ 0x0019, 0x0006, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0007, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0008, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0026, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0029, 0, VR::LO, VM::M1, "" },
{ 0x0019, 0x0030, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0031, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0032, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0033, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0034, 0, VR::US, VM::M1, "" },
{ 0x0019, 0x0035, 0, VR::US, VM::M1, "" },
};

unsigned short Dict403TagHashTable[] = {
    3,    14,     0,     5,     1,     7,     4,    41,     6,    49,
    8,    51,    10,    53,     6,     0,     6,     2,     8,     3,
   38,     5,    48,     7,    50,     9,    52,
};

vtkDICOMDictionary::Dict Dict403Data = {
"SIEMENS Selma",
2,
11,
Dict403TagHashTable,
Dict403Contents
};

// ----- SPI RELEASE 1 -----

DictEntry Dict404Contents[] = {
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "Comments" },
{ 0x0009, 0x0015, 0, VR::LO, VM::M1, "UID" },
{ 0x0009, 0x0040, 0, VR::US, VM::M1, "DataObjectType" },
{ 0x0009, 0x0041, 0, VR::SH, VM::M1, "DataObjectSubtype" },
{ 0x0011, 0x0010, 0, VR::LO, VM::M1, "Organ" },
{ 0x0011, 0x0015, 0, VR::LO, VM::M1, "AllergyIndication" },
{ 0x0011, 0x0020, 0, VR::LO, VM::M1, "Pregnancy" },
{ 0x0029, 0x0060, 0, VR::LO, VM::M1, "CompressionAlgorithm" },
};

unsigned short Dict404TagHashTable[] = {
    3,    12,     0,     4,     1,    21,     2,    64,     5,    21,
    7,    96,     4,     0,    16,     3,    65,     4,    16,     6,
   32,
};

vtkDICOMDictionary::Dict Dict404Data = {
"SPI RELEASE 1",
2,
8,
Dict404TagHashTable,
Dict404Contents
};

// ----- SIEMENS MI RWVM SUV -----

DictEntry Dict405Contents[] = {
{ 0x0041, 0x0001, 0, VR::CS, VM::M1, "SUVDecayCorrectionMethod" },
};

unsigned short Dict405TagHashTable[] = {
    2,     0,     1,     0,     1,
};

vtkDICOMDictionary::Dict Dict405Data = {
"SIEMENS MI RWVM SUV",
1,
1,
Dict405TagHashTable,
Dict405Contents
};

// ----- MeVis eD: Slice Information -----

DictEntry Dict406Contents[] = {
{ 0x0021, 0x0010, 0, VR::UI, VM::M1TN, "SliceSOPInstanceUIDs" },
};

unsigned short Dict406TagHashTable[] = {
    2,     0,     1,     0,    16,
};

vtkDICOMDictionary::Dict Dict406Data = {
"MeVis eD: Slice Information",
1,
1,
Dict406TagHashTable,
Dict406Contents
};

// ----- Silhouette Graphics Export V1.0 -----

DictEntry Dict407Contents[] = {
{ 0x0029, 0x0000, 0, VR::UI, VM::M1, "" },
};

unsigned short Dict407TagHashTable[] = {
    2,     0,     1,     0,     0,
};

vtkDICOMDictionary::Dict Dict407Data = {
"Silhouette Graphics Export V1.0",
1,
1,
Dict407TagHashTable,
Dict407Contents
};

// ----- SPI-P Release 1;3 -----

DictEntry Dict408Contents[] = {
{ 0x0029, 0x0000, 0, VR::LT, VM::M1, "ImageEnhancementID" },
{ 0x0029, 0x0001, 0, VR::LT, VM::M1, "ImageEnhancement" },
{ 0x0029, 0x0002, 0, VR::LT, VM::M1, "ConvolutionID" },
{ 0x0029, 0x0003, 0, VR::LT, VM::M1, "ConvolutionType" },
{ 0x0029, 0x0004, 0, VR::LT, VM::M1, "ConvolutionKernelSizeID" },
{ 0x0029, 0x0005, 0, VR::US, VM::M2, "ConvolutionKernelSize" },
{ 0x0029, 0x0006, 0, VR::US, VM::M1TN, "ConvolutionKernel" },
{ 0x0029, 0x000c, 0, VR::DS, VM::M1, "EnhancementGain" },
{ 0x0029, 0x001e, 0, VR::CS, VM::M1, "ImageEnhancementEnableStatus" },
{ 0x0029, 0x001f, 0, VR::CS, VM::M1, "ImageEnhancementSelectStatus" },
};

unsigned short Dict408TagHashTable[] = {
    3,    12,     0,     4,     1,     1,     3,     3,     5,     5,
    9,    31,     6,     0,     0,     2,     2,     4,     4,     6,
    6,     7,    12,     8,    30,
};

vtkDICOMDictionary::Dict Dict408Data = {
"SPI-P Release 1;3",
2,
10,
Dict408TagHashTable,
Dict408Contents
};

// ----- SPI-P Release 1;2 -----

DictEntry Dict409Contents[] = {
{ 0x0029, 0x0000, 0, VR::LT, VM::M1, "SubtractionMaskID" },
{ 0x0029, 0x0004, 0, VR::UN, VM::M1, "MaskingFunction" },
{ 0x0029, 0x000c, 0, VR::UN, VM::M1, "ProprietaryMaskingParameters" },
{ 0x0029, 0x001e, 0, VR::CS, VM::M1, "SubtractionMaskEnableStatus" },
{ 0x0029, 0x001f, 0, VR::CS, VM::M1, "SubtractionMaskSelectStatus" },
};

unsigned short Dict409TagHashTable[] = {
    2,     0,     5,     0,     0,     1,     4,     2,    12,     3,
   30,     4,    31,
};

vtkDICOMDictionary::Dict Dict409Data = {
"SPI-P Release 1;2",
1,
5,
Dict409TagHashTable,
Dict409Contents
};

// ----- SPI-P Release 1;1 -----

DictEntry Dict410Contents[] = {
{ 0x0009, 0x00c0, 0, VR::LT, VM::M1, "" },
{ 0x0009, 0x00c1, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0000, 0, VR::UN, VM::M1, "PhysiologicalDataType" },
{ 0x0019, 0x0001, 0, VR::UN, VM::M1, "PhysiologicalDataChannelAndKind" },
{ 0x0019, 0x0002, 0, VR::US, VM::M1, "SampleBitsAllocated" },
{ 0x0019, 0x0003, 0, VR::US, VM::M1, "SampleBitsStored" },
{ 0x0019, 0x0004, 0, VR::US, VM::M1, "SampleHighBit" },
{ 0x0019, 0x0005, 0, VR::US, VM::M1, "SampleRepresentation" },
{ 0x0019, 0x0006, 0, VR::UN, VM::M1, "SmallestSampleValue" },
{ 0x0019, 0x0007, 0, VR::UN, VM::M1, "LargestSampleValue" },
{ 0x0019, 0x0008, 0, VR::UN, VM::M1, "NumberOfSamples" },
{ 0x0019, 0x0009, 0, VR::UN, VM::M1, "SampleData" },
{ 0x0019, 0x000a, 0, VR::UN, VM::M1, "SampleRate" },
{ 0x0019, 0x0010, 0, VR::UN, VM::M1, "PhysiologicalDataType2" },
{ 0x0019, 0x0011, 0, VR::UN, VM::M1, "PhysiologicalDataChannelAndKind2" },
{ 0x0019, 0x0012, 0, VR::US, VM::M1, "SampleBitsAllocated2" },
{ 0x0019, 0x0013, 0, VR::US, VM::M1, "SampleBitsStored2" },
{ 0x0019, 0x0014, 0, VR::US, VM::M1, "SampleHighBit2" },
{ 0x0019, 0x0015, 0, VR::US, VM::M1, "SampleRepresentation2" },
{ 0x0019, 0x0016, 0, VR::UN, VM::M1, "SmallestSampleValue2" },
{ 0x0019, 0x0017, 0, VR::UN, VM::M1, "LargestSampleValue2" },
{ 0x0019, 0x0018, 0, VR::UN, VM::M1, "NumberOfSamples2" },
{ 0x0019, 0x0019, 0, VR::UN, VM::M1, "SampleData2" },
{ 0x0019, 0x001a, 0, VR::UN, VM::M1, "SampleRate2" },
{ 0x0029, 0x0000, 0, VR::LT, VM::M1, "ZoomID" },
{ 0x0029, 0x0001, 0, VR::DS, VM::M1TN, "ZoomRectangle" },
{ 0x0029, 0x0003, 0, VR::DS, VM::M1, "ZoomFactor" },
{ 0x0029, 0x0004, 0, VR::US, VM::M1, "ZoomFunction" },
{ 0x0029, 0x000e, 0, VR::CS, VM::M1, "ZoomEnableStatus" },
{ 0x0029, 0x000f, 0, VR::CS, VM::M1, "ZoomSelectStatus" },
{ 0x0029, 0x0040, 0, VR::LT, VM::M1, "MagnifyingGlassID" },
{ 0x0029, 0x0041, 0, VR::DS, VM::M1TN, "MagnifyingGlassRectangle" },
{ 0x0029, 0x0043, 0, VR::DS, VM::M1, "MagnifyingGlassFactor" },
{ 0x0029, 0x0044, 0, VR::US, VM::M1, "MagnifyingGlassFunction" },
{ 0x0029, 0x004e, 0, VR::CS, VM::M1, "MagnifyingGlassEnableStatus" },
{ 0x0029, 0x004f, 0, VR::CS, VM::M1, "MagnifyingGlassSelectStatus" },
};

unsigned short Dict410TagHashTable[] = {
   10,    21,    30,    37,    48,    59,    68,    77,    82,     0,
    5,     4,     2,    13,    16,    22,    25,    27,     4,    33,
   68,     4,     7,     5,    12,    10,    16,    19,    21,    24,
    3,     6,     4,    15,    18,    29,    15,     5,     9,     7,
   18,    21,    23,    26,    28,    14,    34,    78,     5,     0,
  192,     8,     6,    17,    20,    25,     1,    35,    79,     4,
    1,   193,    20,    23,    24,     0,    30,    64,     4,     3,
    1,    19,    22,    26,     3,    31,    65,     2,     2,     0,
   11,     9,     4,     5,     3,    10,     8,    14,    17,    32,
   67,
};

vtkDICOMDictionary::Dict Dict410Data = {
"SPI-P Release 1;1",
9,
36,
Dict410TagHashTable,
Dict410Contents
};

// ----- SIEMENS MR VA0  COAD -----

DictEntry Dict411Contents[] = {
{ 0x0019, 0x0012, 0, VR::DS, VM::M1, "MagneticFieldStrength" },
{ 0x0019, 0x0014, 0, VR::DS, VM::M1, "ADCVoltage" },
{ 0x0019, 0x0016, 0, VR::DS, VM::M2, "ADCOffset" },
{ 0x0019, 0x0020, 0, VR::DS, VM::M1, "TransmitterAmplitude" },
{ 0x0019, 0x0021, 0, VR::IS, VM::M1, "NumberOfTransmitterAmplitudes" },
{ 0x0019, 0x0022, 0, VR::DS, VM::M1, "TransmitterAttenuator" },
{ 0x0019, 0x0024, 0, VR::DS, VM::M1, "TransmitterCalibration" },
{ 0x0019, 0x0026, 0, VR::DS, VM::M1, "TransmitterReference" },
{ 0x0019, 0x0050, 0, VR::DS, VM::M1, "ReceiverTotalGain" },
{ 0x0019, 0x0051, 0, VR::DS, VM::M1, "ReceiverAmplifierGain" },
{ 0x0019, 0x0052, 0, VR::DS, VM::M1, "ReceiverPreamplifierGain" },
{ 0x0019, 0x0054, 0, VR::DS, VM::M1, "ReceiverCableAttenuation" },
{ 0x0019, 0x0055, 0, VR::DS, VM::M1, "ReceiverReferenceGain" },
{ 0x0019, 0x0056, 0, VR::DS, VM::M1, "ReceiverFilterFrequency" },
{ 0x0019, 0x0060, 0, VR::DS, VM::M1, "ReconstructionScaleFactor" },
{ 0x0019, 0x0062, 0, VR::DS, VM::M1, "ReferenceScaleFactor" },
{ 0x0019, 0x0070, 0, VR::DS, VM::M1, "PhaseGradientAmplitude" },
{ 0x0019, 0x0071, 0, VR::DS, VM::M1, "ReadoutGradientAmplitude" },
{ 0x0019, 0x0072, 0, VR::DS, VM::M1, "SelectionGradientAmplitude" },
{ 0x0019, 0x0080, 0, VR::DS, VM::M3, "GradientDelayTime" },
{ 0x0019, 0x0082, 0, VR::DS, VM::M1, "TotalGradientDelayTime" },
{ 0x0019, 0x0090, 0, VR::LO, VM::M1, "SensitivityCorrectionLabel" },
{ 0x0019, 0x0091, 0, VR::DS, VM::M6, "SaturationPhaseEncodingVectorCoronalComponent" },
{ 0x0019, 0x0092, 0, VR::DS, VM::M6, "SaturationReadoutVectorCoronalComponent" },
{ 0x0019, 0x00a0, 0, VR::IS, VM::M1, "RFWatchdogMask" },
{ 0x0019, 0x00a1, 0, VR::DS, VM::M1, "EPIReconstructionSlope" },
{ 0x0019, 0x00a2, 0, VR::DS, VM::M1, "RFPowerErrorIndicator" },
{ 0x0019, 0x00a5, 0, VR::DS, VM::M3, "SpecificAbsorptionRateWholeBody" },
{ 0x0019, 0x00a6, 0, VR::DS, VM::M3, "SpecificEnergyDose" },
{ 0x0019, 0x00b0, 0, VR::UL, VM::M1, "AdjustmentStatusMask" },
{ 0x0019, 0x00c1, 0, VR::DS, VM::M6, "EPICapacity" },
{ 0x0019, 0x00c2, 0, VR::DS, VM::M3, "EPIInductance" },
{ 0x0019, 0x00c3, 0, VR::IS, VM::M1TN, "EPISwitchConfigurationCode" },
{ 0x0019, 0x00c4, 0, VR::IS, VM::M1TN, "EPISwitchHardwareCode" },
{ 0x0019, 0x00c5, 0, VR::DS, VM::M1TN, "EPISwitchDelayTime" },
{ 0x0019, 0x00d1, 0, VR::DS, VM::M1, "FlowSensitivity" },
{ 0x0019, 0x00d2, 0, VR::CS, VM::M1, "CalculationSubmode" },
{ 0x0019, 0x00d3, 0, VR::DS, VM::M1, "FieldOfViewRatio" },
{ 0x0019, 0x00d4, 0, VR::IS, VM::M1, "BaseRawMatrixSize" },
{ 0x0019, 0x00d5, 0, VR::IS, VM::M1, "2DOversamplingLines" },
{ 0x0019, 0x00d6, 0, VR::IS, VM::M1, "ThreeDPhaseOversamplingPartitions" },
{ 0x0019, 0x00d7, 0, VR::IS, VM::M1, "EchoLinePosition" },
{ 0x0019, 0x00d8, 0, VR::IS, VM::M1, "EchoColumnPosition" },
{ 0x0019, 0x00d9, 0, VR::IS, VM::M1, "LinesPerSegment" },
{ 0x0019, 0x00da, 0, VR::CS, VM::M1, "PhaseCodingDirection" },
};

unsigned short Dict411TagHashTable[] = {
   12,    19,    28,    39,    46,    51,    60,    73,    86,    97,
  102,     0,     3,     0,    18,    12,    85,    24,   160,     4,
    4,    33,    13,    86,    15,    98,    19,   128,     5,     1,
   20,     3,    32,    28,   166,    33,   196,    36,   210,     3,
   27,   165,    34,   197,    37,   211,     2,     2,    22,     5,
   34,     4,    16,   112,    23,   146,    35,   209,    44,   218,
    6,     6,    36,     8,    80,    17,   113,    22,   145,    29,
  176,    40,   214,     6,     9,    81,    18,   114,    21,   144,
   31,   194,    41,   215,    42,   216,     5,     7,    38,    10,
   82,    32,   195,    38,   212,    43,   217,     2,    26,   162,
   39,   213,     5,    11,    84,    14,    96,    20,   130,    25,
  161,    30,   193,
};

vtkDICOMDictionary::Dict Dict411Data = {
"SIEMENS MR VA0  COAD",
11,
45,
Dict411TagHashTable,
Dict411Contents
};

// ----- SIEMENS MR PHOENIX ATTRIBUTES -----

DictEntry Dict412Contents[] = {
{ 0x0021, 0x0001, 0, VR::UL, VM::M1, "MdsModeMask" },
{ 0x0021, 0x0002, 0, VR::US, VM::M1, "Dixon" },
{ 0x0021, 0x0003, 0, VR::LT, VM::M1, "SequenceFileName" },
{ 0x0021, 0x00F1, 0, VR::UL, VM::M1, "CountOfPseudoAttributes" },
};

unsigned short Dict412TagHashTable[] = {
    2,     0,     4,     0,     1,     1,     2,     2,     3,     3,
  241,
};

vtkDICOMDictionary::Dict Dict412Data = {
"SIEMENS MR PHOENIX ATTRIBUTES",
1,
4,
Dict412TagHashTable,
Dict412Contents
};

// ----- SIEMENS MR SDI 02 -----

DictEntry Dict413Contents[] = {
{ 0x0021, 0x0001, 0, VR::US, VM::M1, "NumberOfImagesInMosaic" },
{ 0x0021, 0x0002, 0, VR::FD, VM::M3, "SliceNormalVector" },
{ 0x0021, 0x0003, 0, VR::DS, VM::M1, "SliceMeasurementDuration" },
{ 0x0021, 0x0004, 0, VR::DS, VM::M1, "TimeAfterStart" },
{ 0x0021, 0x0005, 0, VR::IS, VM::M1, "BValue" },
{ 0x0021, 0x0006, 0, VR::LO, VM::M1, "ICEDims" },
{ 0x0021, 0x001A, 0, VR::SH, VM::M1, "RFSWDDataType" },
{ 0x0021, 0x001B, 0, VR::US, VM::M1, "MoCoQMeasure" },
{ 0x0021, 0x001C, 0, VR::IS, VM::M1, "PhaseEncodingDirectionPositive" },
{ 0x0021, 0x001D, 0, VR::OB, VM::M1, "PixelFile" },
{ 0x0021, 0x001F, 0, VR::IS, VM::M1, "FMRIStimulInfo" },
{ 0x0021, 0x0020, 0, VR::DS, VM::M1, "VoxelInPlaneRot" },
{ 0x0021, 0x0021, 0, VR::CS, VM::M1, "DiffusionDirectionality4MF" },
{ 0x0021, 0x0022, 0, VR::DS, VM::M1, "VoxelThickness" },
{ 0x0021, 0x0023, 0, VR::FD, VM::M6, "BMatrix" },
{ 0x0021, 0x0024, 0, VR::IS, VM::M1, "MultistepIndex" },
{ 0x0021, 0x0025, 0, VR::LT, VM::M1, "CompAdjustedParam" },
{ 0x0021, 0x0026, 0, VR::IS, VM::M1, "CompAlgorithm" },
{ 0x0021, 0x0027, 0, VR::DS, VM::M1, "VoxelNormalCor" },
{ 0x0021, 0x0029, 0, VR::SH, VM::M1, "FlowEncodingDirectionString" },
{ 0x0021, 0x002A, 0, VR::DS, VM::M1, "VoxelNormalSag" },
{ 0x0021, 0x002B, 0, VR::DS, VM::M1, "VoxelPositionSag" },
{ 0x0021, 0x002C, 0, VR::DS, VM::M1, "VoxelNormalTra" },
{ 0x0021, 0x002D, 0, VR::DS, VM::M1, "VoxelPositionTra" },
{ 0x0021, 0x002E, 0, VR::UL, VM::M1, "UsedChannelMask" },
{ 0x0021, 0x002F, 0, VR::DS, VM::M1, "RepetitionTimeEffective" },
{ 0x0021, 0x0030, 0, VR::DS, VM::M6, "CSIImageOrientationPatient" },
{ 0x0021, 0x0032, 0, VR::DS, VM::M1, "CSISliceLocation" },
{ 0x0021, 0x0033, 0, VR::IS, VM::M1, "EchoColumnPosition" },
{ 0x0021, 0x0034, 0, VR::FD, VM::M1, "FlowVENC" },
{ 0x0021, 0x0035, 0, VR::IS, VM::M1, "MeasuredFourierLines" },
{ 0x0021, 0x0036, 0, VR::SH, VM::M1, "LQAlgorithm" },
{ 0x0021, 0x0037, 0, VR::DS, VM::M1, "VoxelPositionCor" },
{ 0x0021, 0x0038, 0, VR::IS, VM::M1, "Filter2" },
{ 0x0021, 0x0039, 0, VR::FD, VM::M1, "FMRIStimulLevel" },
{ 0x0021, 0x003A, 0, VR::DS, VM::M1, "VoxelReadoutFOV" },
{ 0x0021, 0x003B, 0, VR::IS, VM::M1, "NormalizeManipulated" },
{ 0x0021, 0x003C, 0, VR::FD, VM::M3, "RBMoCoRot" },
{ 0x0021, 0x003D, 0, VR::IS, VM::M1, "CompManualAdjusted" },
{ 0x0021, 0x003F, 0, VR::SH, VM::M1, "SpectrumTextRegionLabel" },
{ 0x0021, 0x0040, 0, VR::DS, VM::M1, "VoxelPhaseFOV" },
{ 0x0021, 0x0041, 0, VR::SH, VM::M1, "GSWDDataType" },
{ 0x0021, 0x0042, 0, VR::IS, VM::M1, "RealDwellTime" },
{ 0x0021, 0x0043, 0, VR::LT, VM::M1, "CompJobID" },
{ 0x0021, 0x0044, 0, VR::IS, VM::M1, "CompBlended" },
{ 0x0021, 0x0045, 0, VR::SL, VM::M3, "ImaAbsTablePosition" },
{ 0x0021, 0x0046, 0, VR::FD, VM::M3, "DiffusionGradientDirection" },
{ 0x0021, 0x0047, 0, VR::IS, VM::M1, "FlowEncodingDirection" },
{ 0x0021, 0x0048, 0, VR::IS, VM::M1, "EchoPartitionPosition" },
{ 0x0021, 0x0049, 0, VR::IS, VM::M1, "EchoLinePosition" },
{ 0x0021, 0x004B, 0, VR::LT, VM::M1, "CompAutoParam" },
{ 0x0021, 0x004C, 0, VR::IS, VM::M1, "OriginalImageNumber" },
{ 0x0021, 0x004D, 0, VR::IS, VM::M1, "OriginalSeriesNumber" },
{ 0x0021, 0x004E, 0, VR::IS, VM::M1, "Actual3DImaPartNumber" },
{ 0x0021, 0x004F, 0, VR::LO, VM::M1, "ImaCoilString" },
{ 0x0021, 0x0050, 0, VR::DS, VM::M2, "CSIPixelSpacing" },
{ 0x0021, 0x0051, 0, VR::UL, VM::M1, "SequenceMask" },
{ 0x0021, 0x0052, 0, VR::US, VM::M1, "ImageGroup" },
{ 0x0021, 0x0053, 0, VR::FD, VM::M1, "BandwidthPerPixelPhaseEncode" },
{ 0x0021, 0x0054, 0, VR::US, VM::M1, "NonPlanarImage" },
{ 0x0021, 0x0055, 0, VR::OB, VM::M1, "PixelFileName" },
{ 0x0021, 0x0056, 0, VR::LO, VM::M1, "ImaPATModeText" },
{ 0x0021, 0x0057, 0, VR::DS, VM::M3, "CSIImagePositionPatient" },
{ 0x0021, 0x0058, 0, VR::SH, VM::M1, "AcquisitionMatrixText" },
{ 0x0021, 0x0059, 0, VR::IS, VM::M3, "ImaRelTablePosition" },
{ 0x0021, 0x005A, 0, VR::FD, VM::M3, "RBMoCoTrans" },
{ 0x0021, 0x005B, 0, VR::FD, VM::M3, "SlicePositionPCS" },
{ 0x0021, 0x005C, 0, VR::DS, VM::M1, "CSISliceThickness" },
{ 0x0021, 0x005E, 0, VR::IS, VM::M1, "ProtocolSliceNumber" },
{ 0x0021, 0x005F, 0, VR::IS, VM::M1, "Filter1" },
{ 0x0021, 0x0060, 0, VR::SH, VM::M1, "TransmittingCoil" },
{ 0x0021, 0x0061, 0, VR::DS, VM::M1, "NumberOfAveragesN4" },
{ 0x0021, 0x0062, 0, VR::FD, VM::M1TN, "MosaicRefAcqTimes" },
{ 0x0021, 0x0063, 0, VR::IS, VM::M1, "AutoInlineImageFilterEnabled" },
{ 0x0021, 0x0065, 0, VR::FD, VM::M1TN, "QCData" },
{ 0x0021, 0x0066, 0, VR::LT, VM::M1, "ExamLandmarks" },
{ 0x0021, 0x0067, 0, VR::ST, VM::M1, "ExamDataRole" },
{ 0x0021, 0x0068, 0, VR::OB, VM::M1, "MRDiffusion" },
{ 0x0021, 0x0069, 0, VR::OB, VM::M1, "RealWorldValueMapping" },
{ 0x0021, 0x0070, 0, VR::OB, VM::M1, "DataSetInfo" },
{ 0x0021, 0x0071, 0, VR::UT, VM::M1, "UsedChannelString" },
{ 0x0021, 0x0072, 0, VR::CS, VM::M1, "PhaseContrastN4" },
{ 0x0021, 0x0073, 0, VR::UT, VM::M1, "MRVelocityEncoding" },
{ 0x0021, 0x0074, 0, VR::FD, VM::M3, "VelocityEncodingDirectionN4" },
{ 0x0021, 0x0075, 0, VR::CS, VM::M1TN, "ImageType4MF" },
{ 0x0021, 0x0076, 0, VR::LO, VM::M1TN, "ImageHistory" },
{ 0x0021, 0x0077, 0, VR::LO, VM::M1, "SequenceInfo" },
{ 0x0021, 0x0078, 0, VR::CS, VM::M1TN, "ImageTypeVisible" },
{ 0x0021, 0x0079, 0, VR::CS, VM::M1, "DistortionCorrectionType" },
{ 0x0021, 0x0080, 0, VR::CS, VM::M1, "ImageFilterType" },
{ 0x0021, 0x00FE, 0, VR::SQ, VM::M1, "SiemensMRSDISequence" },
};

unsigned short Dict413TagHashTable[] = {
   23,    36,    47,    54,    63,    72,    81,    90,    99,   108,
  115,   124,   131,   140,   149,   162,   173,   182,   195,   202,
  209,   218,     0,     6,    12,    33,    32,    55,    53,    78,
   72,    98,    87,   120,    90,   254,     5,    11,    32,    31,
   54,    54,    79,    73,    99,    88,   121,     3,    14,    35,
   34,    57,    55,    80,     4,    13,    34,    33,    56,    56,
   81,    74,   101,     4,    16,    37,    36,    59,    57,    82,
   75,   102,     4,    15,    36,    35,    58,    58,    83,    76,
  103,     4,    18,    39,    38,    61,    59,    84,    77,   104,
    4,    17,    38,    37,    60,    60,    85,    78,   105,     4,
   19,    41,    39,    63,    40,    64,    61,    86,     3,    41,
   65,    62,    87,    89,   128,     4,     0,     1,    21,    43,
   42,    66,    63,    88,     3,    20,    42,    43,    67,    64,
   89,     4,     2,     3,    23,    45,    44,    68,    65,    90,
    4,     1,     2,    22,    44,    45,    69,    66,    91,     6,
    4,     5,     7,    27,    25,    47,    46,    70,    67,    92,
   79,   112,     5,     3,     4,     6,    26,    24,    46,    47,
   71,    80,   113,     4,     9,    29,    48,    72,    68,    94,
   81,   114,     6,     5,     6,     8,    28,    26,    48,    49,
   73,    69,    95,    82,   115,     3,    10,    31,    28,    51,
   83,   116,     3,    27,    50,    50,    75,    84,   117,     4,
   30,    53,    51,    76,    70,    96,    85,   118,     4,    29,
   52,    52,    77,    71,    97,    86,   119,
};

vtkDICOMDictionary::Dict Dict413Data = {
"SIEMENS MR SDI 02",
22,
91,
Dict413TagHashTable,
Dict413Contents
};

// ----- Biospace Med : EOS Tag -----

DictEntry Dict414Contents[] = {
{ 0x0863, 0x0010, 0, VR::SL, VM::M1, "ImageType" },
{ 0x0863, 0x0023, 0, VR::SL, VM::M1, "CalibrationFlag" },
{ 0x0863, 0x0026, 0, VR::UL, VM::M1, "AttributeVersion" },
{ 0x0863, 0x0027, 0, VR::SL, VM::M1, "ResizingFlag" },
{ 0x0863, 0x0028, 0, VR::SL, VM::M1, "LogarithmFlag" },
{ 0x0863, 0x0032, 0, VR::SL, VM::M1, "LeftCollimatorEdge" },
{ 0x0863, 0x0033, 0, VR::SL, VM::M1, "RightCollimatorEdge" },
{ 0x0863, 0x0034, 0, VR::FL, VM::M1, "DistanceSourceToPatientOfBiplanePair" },
{ 0x0863, 0x0035, 0, VR::SL, VM::M1, "LineCorrectionFlag" },
{ 0x0863, 0x0036, 0, VR::SL, VM::M1, "ContrastEnhancementFlag" },
{ 0x0863, 0x0037, 0, VR::SL, VM::M1, "CalibreValue" },
{ 0x0863, 0x0038, 0, VR::SL, VM::M1, "HighFrequencyLineCorrectionMaxThreshold" },
{ 0x0863, 0x0039, 0, VR::SL, VM::M1, "HighFrequencyLineCorrectionMinThreshold" },
{ 0x0863, 0x0040, 0, VR::FL, VM::M1, "GreaterLimit" },
{ 0x0863, 0x0041, 0, VR::FL, VM::M1, "LowerLimit" },
{ 0x0863, 0x0042, 0, VR::FL, VM::M1, "FrontalDetectorBladesOpening" },
{ 0x0863, 0x0043, 0, VR::FL, VM::M1, "FrontalTubeBladesOpening" },
{ 0x0863, 0x0044, 0, VR::FL, VM::M1, "LateralDetectorBladesOpening" },
{ 0x0863, 0x0045, 0, VR::FL, VM::M1, "LateralTubeBladesOpening" },
{ 0x0863, 0x0046, 0, VR::DS, VM::M1TN, "ThreeDCalibrationParameters" },
{ 0x0863, 0x0057, 0, VR::CS, VM::M1, "ImageHorizontalFlip" },
};

unsigned short Dict414TagHashTable[] = {
    6,    21,    30,    33,    42,     0,     7,     0,    16,     1,
   35,     5,    50,    10,    55,    11,    56,    14,    65,    17,
   68,     4,     6,    51,     7,    52,    12,    57,    13,    64,
    1,     8,    53,     4,     2,    38,    16,    67,    19,    70,
   20,    87,     5,     3,    39,     4,    40,     9,    54,    15,
   66,    18,    69,
};

vtkDICOMDictionary::Dict Dict414Data = {
"Biospace Med : EOS Tag",
5,
21,
Dict414TagHashTable,
Dict414Contents
};

// ----- AMI ImageContextExt_01 -----

DictEntry Dict415Contents[] = {
{ 0x3107, 0x00A0, 0, VR::CS, VM::M1, "WindowFunction" },
{ 0x3107, 0x00B0, 0, VR::DS, VM::M1, "WindowSlope" },
};

unsigned short Dict415TagHashTable[] = {
    2,     0,     2,     0,   160,     1,   176,
};

vtkDICOMDictionary::Dict Dict415Data = {
"AMI ImageContextExt_01",
1,
2,
Dict415TagHashTable,
Dict415Contents
};

// ----- IMS s.r.l. Biopsy Private Code -----

DictEntry Dict416Contents[] = {
{ 0x1269, 0x0001, 0, VR::IS, VM::M1, "BiopsyImage" },
{ 0x1269, 0x0010, 0, VR::IS, VM::M1TN, "BiopsyMarkersX" },
{ 0x1269, 0x0011, 0, VR::IS, VM::M1TN, "BiopsyMarkersY" },
{ 0x1269, 0x0012, 0, VR::IS, VM::M1TN, "BiopsyMarkersNumber" },
{ 0x1269, 0x0020, 0, VR::IS, VM::M1, "BiopsyAreaLeftBorder" },
{ 0x1269, 0x0021, 0, VR::IS, VM::M1, "BiopsyAreaRightBorder" },
{ 0x1269, 0x0022, 0, VR::IS, VM::M1, "BiopsyAreaTopBorder" },
{ 0x1269, 0x0023, 0, VR::IS, VM::M1, "BiopsyAreaBottomBorder" },
{ 0x1269, 0x0024, 0, VR::IS, VM::M1, "BiopsyNumber" },
};

unsigned short Dict416TagHashTable[] = {
    3,    14,     0,     5,     1,    16,     3,    18,     4,    32,
    6,    34,     8,    36,     4,     0,     1,     2,    17,     5,
   33,     7,    35,
};

vtkDICOMDictionary::Dict Dict416Data = {
"IMS s.r.l. Biopsy Private Code",
2,
9,
Dict416TagHashTable,
Dict416Contents
};

// ----- PMI Private Calibration Module Version 2.0 -----

DictEntry Dict417Contents[] = {
{ 0x2121, 0x0001, 0, VR::ST, VM::M1, "CalibrationMethod" },
{ 0x2121, 0x0002, 0, VR::ST, VM::M1, "CalibrationMethodInfo" },
{ 0x2121, 0x0003, 0, VR::FL, VM::M1, "CalibrationObjectSize" },
{ 0x2121, 0x0004, 0, VR::FL, VM::M1, "CalibrationObjectSDev" },
{ 0x2121, 0x0005, 0, VR::FL, VM::M1, "CalibrationHorizontalPixelSpacing" },
{ 0x2121, 0x0006, 0, VR::FL, VM::M1, "CalibrationVerticalPixelSpacing" },
{ 0x2121, 0x0008, 0, VR::ST, VM::M1, "CalibrationFileName" },
{ 0x2121, 0x0009, 0, VR::IS, VM::M1, "CalibrationFrameNumber" },
{ 0x2121, 0x000a, 0, VR::SH, VM::M1, "CalibrationObjectUnit" },
{ 0x2121, 0x000b, 0, VR::SS, VM::M1, "AveragedCalibrationsPerformed" },
{ 0x2121, 0x000c, 0, VR::FL, VM::M1, "AutoMagnifyFactor" },
{ 0x2121, 0x000d, 0, VR::FL, VM::M1, "HorizontalPixelSDev" },
{ 0x2121, 0x000e, 0, VR::FL, VM::M1, "VerticalPixelSDev" },
};

unsigned short Dict417TagHashTable[] = {
    4,    11,    24,     0,     3,     9,    11,    11,    13,    12,
   14,     6,     2,     3,     4,     5,     5,     6,     7,     9,
    8,    10,    10,    12,     4,     0,     1,     1,     2,     3,
    4,     6,     8,
};

vtkDICOMDictionary::Dict Dict417Data = {
"PMI Private Calibration Module Version 2.0",
3,
13,
Dict417TagHashTable,
Dict417Contents
};

// ----- GEMS_ADWSoft_3D1 -----

DictEntry Dict418Contents[] = {
{ 0x0047, 0x0001, 0, VR::SQ, VM::M1, "Reconstruction Parameters Sequence" },
{ 0x0047, 0x0050, 0, VR::UL, VM::M1, "VolumeVoxelCount" },
{ 0x0047, 0x0051, 0, VR::UL, VM::M1, "VolumeSegmentCount" },
{ 0x0047, 0x0053, 0, VR::US, VM::M1, "VolumeSliceSize" },
{ 0x0047, 0x0054, 0, VR::US, VM::M1, "VolumeSliceCount" },
{ 0x0047, 0x0055, 0, VR::SL, VM::M1, "VolumeThresholdValue" },
{ 0x0047, 0x0057, 0, VR::DS, VM::M1, "VolumeVoxelRatio" },
{ 0x0047, 0x0058, 0, VR::DS, VM::M1, "VolumeVoxelSize" },
{ 0x0047, 0x0059, 0, VR::US, VM::M1, "VolumeZPositionSize" },
{ 0x0047, 0x0060, 0, VR::DS, VM::M9, "VolumeBaseLine" },
{ 0x0047, 0x0061, 0, VR::DS, VM::M3, "VolumeCenterPoint" },
{ 0x0047, 0x0063, 0, VR::SL, VM::M1, "VolumeSkewBase" },
{ 0x0047, 0x0064, 0, VR::DS, VM::M9, "VolumeRegistrationTransformRotationMatrix" },
{ 0x0047, 0x0065, 0, VR::DS, VM::M3, "VolumeRegistrationTransformTranslationVector" },
{ 0x0047, 0x0070, 0, VR::DS, VM::M1TN, "KVPList" },
{ 0x0047, 0x0071, 0, VR::IS, VM::M1TN, "XRayTubeCurrentList" },
{ 0x0047, 0x0072, 0, VR::IS, VM::M1TN, "ExposureList" },
{ 0x0047, 0x0080, 0, VR::LO, VM::M1, "AcquisitionDLXIdentifier" },
{ 0x0047, 0x0085, 0, VR::SQ, VM::M1, "AcquisitionDLX2DSeriesSequence" },
{ 0x0047, 0x0089, 0, VR::DS, VM::M1TN, "ContrastAgentVolumeList" },
{ 0x0047, 0x008A, 0, VR::US, VM::M1, "NumberOfInjections" },
{ 0x0047, 0x008B, 0, VR::US, VM::M1, "FrameCount" },
{ 0x0047, 0x0091, 0, VR::LO, VM::M1, "XA3DReconstructionAlgorithmName" },
{ 0x0047, 0x0092, 0, VR::CS, VM::M1, "XA3DReconstructionAlgorithmVersion" },
{ 0x0047, 0x0093, 0, VR::DA, VM::M1, "DLXCalibrationDate" },
{ 0x0047, 0x0094, 0, VR::TM, VM::M1, "DLXCalibrationTime" },
{ 0x0047, 0x0095, 0, VR::CS, VM::M1, "DLXCalibrationStatus" },
{ 0x0047, 0x0096, 0, VR::IS, VM::M1TN, "UsedFrames" },
{ 0x0047, 0x0098, 0, VR::US, VM::M1, "TransformCount" },
{ 0x0047, 0x0099, 0, VR::SQ, VM::M1, "TransformSequence" },
{ 0x0047, 0x009A, 0, VR::DS, VM::M9, "TransformRotationMatrix" },
{ 0x0047, 0x009B, 0, VR::DS, VM::M3, "TransformTranslationVector" },
{ 0x0047, 0x009C, 0, VR::LO, VM::M1, "TransformLabel" },
{ 0x0047, 0x00B0, 0, VR::SQ, VM::M1, "WireframeList" },
{ 0x0047, 0x00B1, 0, VR::US, VM::M1, "WireframeCount" },
{ 0x0047, 0x00B2, 0, VR::US, VM::M1, "LocationSystem" },
{ 0x0047, 0x00B5, 0, VR::LO, VM::M1, "WireframeName" },
{ 0x0047, 0x00B6, 0, VR::LO, VM::M1, "WireframeGroupName" },
{ 0x0047, 0x00B7, 0, VR::LO, VM::M1, "WireframeColor" },
{ 0x0047, 0x00B8, 0, VR::SL, VM::M1, "WireframeAttributes" },
{ 0x0047, 0x00B9, 0, VR::SL, VM::M1, "WireframePointCount" },
{ 0x0047, 0x00BA, 0, VR::SL, VM::M1, "WireframeTimestamp" },
{ 0x0047, 0x00BB, 0, VR::SQ, VM::M1, "WireframePointList" },
{ 0x0047, 0x00BC, 0, VR::DS, VM::M3, "WireframePointsCoordinates" },
{ 0x0047, 0x00C0, 0, VR::DS, VM::M3, "VolumeUpperLeftHighCornerRAS" },
{ 0x0047, 0x00C1, 0, VR::DS, VM::M9, "VolumeSliceToRASRotationMatrix" },
{ 0x0047, 0x00C2, 0, VR::DS, VM::M1, "VolumeUpperLeftHighCornerTLOC" },
{ 0x0047, 0x00D1, 0, VR::OB, VM::M1, "VolumeSegmentList" },
{ 0x0047, 0x00D2, 0, VR::OB, VM::M1, "VolumeGradientList" },
{ 0x0047, 0x00D3, 0, VR::OB, VM::M1, "VolumeDensityList" },
{ 0x0047, 0x00D4, 0, VR::OB, VM::M1, "VolumeZPositionList" },
{ 0x0047, 0x00D5, 0, VR::OB, VM::M1, "VolumeOriginalIndexList" },
};

unsigned short Dict418TagHashTable[] = {
   14,    21,    34,    45,    52,    55,    68,    77,    88,    99,
  106,   115,   122,     0,     3,     9,    96,    25,   148,    29,
  153,     6,    16,   114,    17,   128,    26,   149,    30,   154,
   43,   188,    51,   213,     5,    15,   113,    27,   150,    31,
  155,    45,   193,    50,   212,     3,     6,    87,    14,   112,
   44,   192,     1,     8,    89,     6,     5,    85,     7,    88,
   22,   145,    39,   184,    46,   194,    47,   209,     4,     0,
    1,     4,    84,    23,   146,    40,   185,     5,     3,    83,
   24,   147,    36,   181,    41,   186,    49,   211,     5,    13,
  101,    32,   156,    37,   182,    42,   187,    48,   210,     3,
    2,    81,    12,   100,    38,   183,     4,     1,    80,    11,
   99,    19,   137,    33,   176,     3,    18,   133,    20,   138,
   34,   177,     4,    10,    97,    21,   139,    28,   152,    35,
  178,
};

vtkDICOMDictionary::Dict Dict418Data = {
"GEMS_ADWSoft_3D1",
13,
52,
Dict418TagHashTable,
Dict418Contents
};

// ----- INFINITT_FMX -----

DictEntry Dict419Contents[] = {
{ 0x0015, 0x0010, 0, VR::LO, VM::M1, "" },
{ 0x0015, 0x0011, 0, VR::LO, VM::M1, "" },
};

unsigned short Dict419TagHashTable[] = {
    2,     0,     2,     0,    16,     1,    17,
};

vtkDICOMDictionary::Dict Dict419Data = {
"INFINITT_FMX",
1,
2,
Dict419TagHashTable,
Dict419Contents
};

// ----- SIEMENS MR SDS 01 -----

DictEntry Dict420Contents[] = {
{ 0x0021, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0002, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0003, 0, VR::OB, VM::M1, "" },
{ 0x0021, 0x0004, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0005, 0, VR::IS, VM::M1TN, "" },
{ 0x0021, 0x0006, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0007, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x0008, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0009, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x000A, 0, VR::DS, VM::M1, "SWCorrectionFactor" },
{ 0x0021, 0x000B, 0, VR::DS, VM::M1, "RFPowerErrorIndicator" },
{ 0x0021, 0x000C, 0, VR::SH, VM::M1, "PositivePCSDirections" },
{ 0x0021, 0x000D, 0, VR::US, VM::M1, "ProtocolChangeHistory" },
{ 0x0021, 0x000E, 0, VR::LO, VM::M1, "DataFileName" },
{ 0x0021, 0x000F, 0, VR::DS, VM::M3, "Stimlim" },
{ 0x0021, 0x000a, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x000c, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x000d, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x000f, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0010, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0011, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0012, 0, VR::FD, VM::M1, "" },
{ 0x0021, 0x0013, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0014, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0015, 0, VR::FL, VM::M1, "MeasurementIndex" },
{ 0x0021, 0x0016, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0017, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0018, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0019, 0, VR::OB, VM::M1, "" },
{ 0x0021, 0x001A, 0, VR::LO, VM::M1, "CoilString" },
{ 0x0021, 0x001B, 0, VR::DS, VM::M1, "SliceResolution" },
{ 0x0021, 0x001C, 0, VR::DS, VM::M3, "Stimmaxonline" },
{ 0x0021, 0x001D, 0, VR::IS, VM::M1, "OperationModeFlag" },
{ 0x0021, 0x001E, 0, VR::FL, VM::M16, "AutoAlignMatrix" },
{ 0x0021, 0x001F, 0, VR::DS, VM::M2, "CoilTuningReflection" },
{ 0x0021, 0x001a, 0, VR::LO, VM::M1, "" },
{ 0x0021, 0x001b, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x001c, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x001d, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x001f, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0020, 0, VR::UI, VM::M1, "RepresentativeImage" },
{ 0x0021, 0x0022, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0023, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0024, 0, VR::LO, VM::M1, "PostProcProtocol" },
{ 0x0021, 0x0025, 0, VR::SL, VM::M1TN, "" },
{ 0x0021, 0x0026, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0027, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x002A, 0, VR::IS, VM::M1TN, "CoilID" },
{ 0x0021, 0x002B, 0, VR::ST, VM::M1, "PatReinPattern" },
{ 0x0021, 0x002C, 0, VR::DS, VM::M3, "SED" },
{ 0x0021, 0x002D, 0, VR::DS, VM::M3, "SARMostCriticalAspect" },
{ 0x0021, 0x002E, 0, VR::IS, VM::M1, "StimmOnMode" },
{ 0x0021, 0x002F, 0, VR::DS, VM::M3, "GradientDelayTime" },
{ 0x0021, 0x002a, 0, VR::IS, VM::M1TN, "" },
{ 0x0021, 0x002b, 0, VR::ST, VM::M1, "" },
{ 0x0021, 0x002c, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x002d, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x002e, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x002f, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0030, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0031, 0, VR::IS, VM::M1, "" },
{ 0x0021, 0x0032, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0033, 0, VR::SH, VM::M1, "" },
{ 0x0021, 0x0034, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0035, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0036, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0038, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0039, 0, VR::OB, VM::M1, "" },
{ 0x0021, 0x003B, 0, VR::DS, VM::M1, "dBdtLimit" },
{ 0x0021, 0x003C, 0, VR::OB, VM::M1, "VFModelInfo" },
{ 0x0021, 0x003D, 0, VR::CS, VM::M1, "PhaseSliceOversampling" },
{ 0x0021, 0x003E, 0, VR::OB, VM::M1, "VFSettings" },
{ 0x0021, 0x003F, 0, VR::UT, VM::M1, "AutoAlignData" },
{ 0x0021, 0x003b, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0040, 0, VR::UT, VM::M1, "FMRIModelParameters" },
{ 0x0021, 0x0041, 0, VR::UT, VM::M1, "FMRIModelInfo" },
{ 0x0021, 0x0042, 0, VR::UT, VM::M1, "FMRIExternalParameters" },
{ 0x0021, 0x0043, 0, VR::UT, VM::M1, "FMRIExternalInfo" },
{ 0x0021, 0x0044, 0, VR::DS, VM::M1TN, "" },
{ 0x0021, 0x0045, 0, VR::CS, VM::M1, "" },
{ 0x0021, 0x0046, 0, VR::DS, VM::M1, "" },
{ 0x0021, 0x0047, 0, VR::CS, VM::M1, "SafetyStandard" },
{ 0x0021, 0x0048, 0, VR::CS, VM::M1, "DICOMImageFlavor" },
{ 0x0021, 0x0049, 0, VR::CS, VM::M1, "DICOMAcquisitionContrast" },
{ 0x0021, 0x0050, 0, VR::US, VM::M1, "RFEchoTrainLength4MF" },
{ 0x0021, 0x0051, 0, VR::US, VM::M1, "GradientEchoTrainLength4MF" },
{ 0x0021, 0x0052, 0, VR::LO, VM::M1, "VersionInfo" },
{ 0x0021, 0x0053, 0, VR::CS, VM::M1, "Laterality4MF" },
{ 0x0021, 0x00FE, 0, VR::SQ, VM::M1, "SiemensMRSDSSequence" },
{ 0x0021, 0x00fe, 0, VR::SQ, VM::M1, "" },
};

unsigned short Dict420TagHashTable[] = {
   23,    32,    41,    52,    61,    72,    79,    86,    93,   100,
  107,   118,   127,   138,   149,   162,   175,   186,   197,   206,
  213,   218,     0,     4,    12,    13,    17,    13,    88,   254,
   89,   254,     4,    11,    12,    16,    12,    40,    32,    65,
   54,     5,    14,    15,    18,    15,    42,    35,    67,    57,
   84,    80,     4,    13,    14,    41,    34,    66,    56,    85,
   81,     5,    20,    17,    44,    37,    68,    59,    73,    59,
   86,    82,     3,    19,    16,    43,    36,    87,    83,     3,
   22,    19,    46,    39,    70,    61,     3,    21,    18,    45,
   38,    69,    60,     3,    24,    21,    72,    63,    74,    64,
    3,    23,    20,    71,    62,    75,    65,     5,     0,     1,
   26,    23,    48,    43,    54,    43,    76,    66,     4,    25,
   22,    47,    42,    53,    42,    77,    67,     5,     2,     3,
   28,    25,    50,    45,    56,    45,    78,    68,     5,     1,
    2,    27,    24,    49,    44,    55,    44,    79,    69,     6,
    4,     5,    30,    27,    36,    27,    52,    47,    58,    47,
   80,    70,     6,     3,     4,    29,    26,    35,    26,    51,
   46,    57,    46,    81,    71,     5,     6,     7,    32,    29,
   38,    29,    60,    49,    82,    72,     5,     5,     6,    31,
   28,    37,    28,    59,    48,    83,    73,     4,     8,     9,
   34,    31,    39,    31,    62,    51,     3,     7,     8,    33,
   30,    61,    50,     2,    10,    11,    64,    53,     3,     9,
   10,    15,    10,    63,    52,
};

vtkDICOMDictionary::Dict Dict420Data = {
"SIEMENS MR SDS 01",
22,
90,
Dict420TagHashTable,
Dict420Contents
};

// ----- GEMS_RELA_01 -----

DictEntry Dict421Contents[] = {
{ 0x0021, 0x0003, 0, VR::SS, VM::M1, "SeriesFromWhichPrescribed" },
{ 0x0021, 0x0005, 0, VR::SH, VM::M1, "GenesisVersionNow" },
{ 0x0021, 0x0007, 0, VR::UL, VM::M1, "SeriesRecordChecksum" },
{ 0x0021, 0x0015, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x0016, 0, VR::SS, VM::M1, "" },
{ 0x0021, 0x0018, 0, VR::SH, VM::M1, "GenesisVersionNow" },
{ 0x0021, 0x0019, 0, VR::UL, VM::M1, "AcqReconRecordChecksum" },
{ 0x0021, 0x0020, 0, VR::DS, VM::M1, "TableStartLocation" },
{ 0x0021, 0x0035, 0, VR::SS, VM::M1, "SeriesFromWhichPrescribed" },
{ 0x0021, 0x0036, 0, VR::SS, VM::M1, "ImageFromWhichPrescribed" },
{ 0x0021, 0x0037, 0, VR::SS, VM::M1, "ScreenFormat" },
{ 0x0021, 0x004a, 0, VR::LO, VM::M1, "AnatomicalReferenceForScout" },
{ 0x0021, 0x004e, 0, VR::US, VM::M1, "" },
{ 0x0021, 0x004f, 0, VR::SS, VM::M1, "LocationsInAcquisition" },
{ 0x0021, 0x0050, 0, VR::SS, VM::M1, "GraphicallyPrescribed" },
{ 0x0021, 0x0051, 0, VR::DS, VM::M1, "RotationFromSourceXRot" },
{ 0x0021, 0x0052, 0, VR::DS, VM::M1, "RotationFromSourceYRot" },
{ 0x0021, 0x0053, 0, VR::DS, VM::M1, "RotationFromSourceZRot" },
{ 0x0021, 0x0054, 0, VR::SH, VM::M3, "ImagePosition" },
{ 0x0021, 0x0055, 0, VR::SH, VM::M6, "ImageOrientation" },
{ 0x0021, 0x0056, 0, VR::SL, VM::M1, "Num3DSlabs" },
{ 0x0021, 0x0057, 0, VR::SL, VM::M1, "LocsPer3DSlab" },
{ 0x0021, 0x0058, 0, VR::SL, VM::M1, "Overlaps" },
{ 0x0021, 0x0059, 0, VR::SL, VM::M1, "ImageFiltering" },
{ 0x0021, 0x005a, 0, VR::SL, VM::M1, "DiffusionDirection" },
{ 0x0021, 0x005b, 0, VR::DS, VM::M1, "TaggingFlipAngle" },
{ 0x0021, 0x005c, 0, VR::DS, VM::M1, "TaggingFlipAngle" },
{ 0x0021, 0x005d, 0, VR::DS, VM::M1, "TagSpacing" },
{ 0x0021, 0x005e, 0, VR::DS, VM::M1, "RTIATimer" },
{ 0x0021, 0x005f, 0, VR::DS, VM::M1, "Fps" },
{ 0x0021, 0x0070, 0, VR::LT, VM::M1, "" },
{ 0x0021, 0x0071, 0, VR::LT, VM::M1, "" },
{ 0x0021, 0x0081, 0, VR::DS, VM::M1, "AutoWindowLevelAlpha" },
{ 0x0021, 0x0082, 0, VR::DS, VM::M1, "AutoWindowLevelBeta" },
{ 0x0021, 0x0083, 0, VR::DS, VM::M1, "AutoWindowLevelWindow" },
{ 0x0021, 0x0084, 0, VR::DS, VM::M1, "AutoWindowLevelLevel" },
{ 0x0021, 0x0090, 0, VR::SS, VM::M1, "TubeFocalSpotPosition" },
{ 0x0021, 0x0091, 0, VR::SS, VM::M1, "BiopsyPosition" },
{ 0x0021, 0x0092, 0, VR::FL, VM::M1, "BiopsyTLocation" },
{ 0x0021, 0x0093, 0, VR::FL, VM::M1, "BiopsyRefLocation" },
};

unsigned short Dict421TagHashTable[] = {
   11,    22,    33,    44,    51,    58,    65,    78,    89,    96,
    0,     5,     8,    53,    12,    78,    22,    88,    30,   112,
   34,   131,     5,     7,    32,    13,    79,    23,    89,    31,
  113,    33,   130,     5,     3,    21,    10,    55,    14,    80,
   24,    90,    32,   129,     3,     9,    54,    15,    81,    25,
   91,     3,     0,     3,    16,    82,    26,    92,     3,     4,
   22,    17,    83,    27,    93,     6,     1,     5,     6,    25,
   11,    74,    18,    84,    28,    94,    39,   147,     5,     5,
   24,    19,    85,    29,    95,    35,   132,    38,   146,     3,
    2,     7,    20,    86,    37,   145,     2,    21,    87,    36,
  144,
};

vtkDICOMDictionary::Dict Dict421Data = {
"GEMS_RELA_01",
10,
40,
Dict421TagHashTable,
Dict421Contents
};

// ----- SIEMENS MR MRS 05 -----

DictEntry Dict422Contents[] = {
{ 0x0021, 0x0001, 0, VR::FD, VM::M1, "TransmitterReferenceAmplitude" },
{ 0x0021, 0x0002, 0, VR::US, VM::M1, "HammingFilterWidth" },
{ 0x0021, 0x0003, 0, VR::FD, VM::M3, "CSIGridshiftVector" },
{ 0x0021, 0x0004, 0, VR::FD, VM::M1, "MixingTime" },
{ 0x0021, 0x0040, 0, VR::CS, VM::M1, "SeriesProtocolInstance" },
{ 0x0021, 0x0041, 0, VR::CS, VM::M1, "SpectroResultType" },
{ 0x0021, 0x0042, 0, VR::CS, VM::M1, "SpectroResultExtendType" },
{ 0x0021, 0x0043, 0, VR::CS, VM::M1, "PostProcProtocol" },
{ 0x0021, 0x0044, 0, VR::CS, VM::M1, "RescanLevel" },
{ 0x0021, 0x0045, 0, VR::OF, VM::M1, "SpectroAlgoResult" },
{ 0x0021, 0x0046, 0, VR::OF, VM::M1, "SpectroDisplayParams" },
{ 0x0021, 0x0047, 0, VR::IS, VM::M1, "VoxelNumber" },
{ 0x0021, 0x0048, 0, VR::SQ, VM::M1, "APRSequence" },
{ 0x0021, 0x0049, 0, VR::CS, VM::M1, "SyncData" },
{ 0x0021, 0x004A, 0, VR::CS, VM::M1, "PostProcDetailedProtocol" },
{ 0x0021, 0x004B, 0, VR::CS, VM::M1, "SpectroResultExtendTypeDetailed" },
};

unsigned short Dict422TagHashTable[] = {
    5,    14,    23,    32,     0,     4,     0,     1,     4,    64,
    8,    68,    12,    72,     4,     3,     4,     5,    65,     9,
   69,    13,    73,     4,     2,     3,     6,    66,    10,    70,
   14,    74,     4,     1,     2,     7,    67,    11,    71,    15,
   75,
};

vtkDICOMDictionary::Dict Dict422Data = {
"SIEMENS MR MRS 05",
4,
16,
Dict422TagHashTable,
Dict422Contents
};

// ----- TOSHIBA_MEC_CT_1.0 -----

DictEntry Dict423Contents[] = {
{ 0x0019, 0x0001, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0002, 0, VR::IS, VM::M1, "" },
{ 0x0019, 0x0003, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0004, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0005, 0, VR::LT, VM::M1, "" },
{ 0x0019, 0x0006, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0007, 0, VR::US, VM::M1TN, "" },
{ 0x0019, 0x0008, 0, VR::LT, VM::M1, "OrientationHeadFeet" },
{ 0x0019, 0x0009, 0, VR::LT, VM::M1, "ViewDirection" },
{ 0x0019, 0x000a, 0, VR::LT, VM::M1, "OrientationSupineProne" },
{ 0x0019, 0x000b, 0, VR::DS, VM::M1, "Location" },
{ 0x0019, 0x000c, 0, VR::CS, VM::M1, "ScanViewDirection" },
{ 0x0019, 0x000d, 0, VR::TM, VM::M1, "Time" },
{ 0x0019, 0x000e, 0, VR::DS, VM::M1, "" },
{ 0x7ff1, 0x0001, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0002, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0003, 0, VR::IS, VM::M1, "" },
{ 0x7ff1, 0x0004, 0, VR::IS, VM::M1, "" },
{ 0x7ff1, 0x0005, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0007, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0008, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x0009, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x000a, 0, VR::LT, VM::M1, "" },
{ 0x7ff1, 0x000b, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x000c, 0, VR::US, VM::M1TN, "" },
{ 0x7ff1, 0x000d, 0, VR::US, VM::M1TN, "" },
};

unsigned short Dict423TagHashTable[] = {
    7,    18,    27,    34,    45,    54,     0,     5,     0,     1,
    6,     7,    10,    11,    15,     2,    20,     8,     4,     5,
    6,     9,    10,    16,     3,    21,     9,     3,     2,     3,
   12,    13,    24,    12,     5,     1,     2,    11,    12,    14,
    1,    19,     7,    25,    13,     4,     4,     5,     8,     9,
   17,     4,    22,    10,     5,     3,     4,     7,     8,    13,
   14,    18,     5,    23,    11,
};

vtkDICOMDictionary::Dict Dict423Data = {
"TOSHIBA_MEC_CT_1.0",
6,
26,
Dict423TagHashTable,
Dict423Contents
};

// ----- SPI Release 1 -----

DictEntry Dict424Contents[] = {
{ 0x0009, 0x0008, 0, VR::CS, VM::M1, "" },
{ 0x0009, 0x0010, 0, VR::LO, VM::M1, "Comments" },
{ 0x0009, 0x0015, 0, VR::LO, VM::M1, "UID" },
{ 0x0009, 0x0040, 0, VR::US, VM::M1, "DataObjectType" },
{ 0x0009, 0x0041, 0, VR::SH, VM::M1, "DataObjectSubtype" },
{ 0x0011, 0x0010, 0, VR::LO, VM::M1, "Organ" },
{ 0x0011, 0x0015, 0, VR::LO, VM::M1, "AllergyIndication" },
{ 0x0011, 0x0020, 0, VR::LO, VM::M1, "Pregnancy" },
{ 0x0029, 0x0060, 0, VR::LO, VM::M1, "CompressionAlgorithm" },
};

unsigned short Dict424TagHashTable[] = {
    3,    12,     0,     4,     2,    21,     3,    64,     6,    21,
    8,    96,     5,     0,     8,     1,    16,     4,    65,     5,
   16,     7,    32,
};

vtkDICOMDictionary::Dict Dict424Data = {
"SPI Release 1",
2,
9,
Dict424TagHashTable,
Dict424Contents
};

vtkDICOMDictionary::Dict *PrivateDictData[] = {
&Dict001Data, &Dict002Data, &Dict003Data, &Dict004Data, &Dict005Data,
&Dict006Data, &Dict007Data, &Dict008Data, &Dict009Data, &Dict010Data,
&Dict011Data, &Dict012Data, &Dict013Data, &Dict014Data, &Dict015Data,
&Dict016Data, &Dict017Data, &Dict018Data, &Dict019Data, &Dict020Data,
&Dict021Data, &Dict022Data, &Dict023Data, &Dict024Data, &Dict025Data,
&Dict026Data, &Dict027Data, &Dict028Data, &Dict029Data, &Dict030Data,
&Dict031Data, &Dict032Data, &Dict033Data, &Dict034Data, &Dict035Data,
&Dict036Data, &Dict037Data, &Dict038Data, &Dict039Data, &Dict040Data,
&Dict041Data, &Dict042Data, &Dict043Data, &Dict044Data, &Dict045Data,
&Dict046Data, &Dict047Data, &Dict048Data, &Dict049Data, &Dict050Data,
&Dict051Data, &Dict052Data, &Dict053Data, &Dict054Data, &Dict055Data,
&Dict056Data, &Dict057Data, &Dict058Data, &Dict059Data, &Dict060Data,
&Dict061Data, &Dict062Data, &Dict063Data, &Dict064Data, &Dict065Data,
&Dict066Data, &Dict067Data, &Dict068Data, &Dict069Data, &Dict070Data,
&Dict071Data, &Dict072Data, &Dict073Data, &Dict074Data, &Dict075Data,
&Dict076Data, &Dict077Data, &Dict078Data, &Dict079Data, &Dict080Data,
&Dict081Data, &Dict082Data, &Dict083Data, &Dict084Data, &Dict085Data,
&Dict086Data, &Dict087Data, &Dict088Data, &Dict089Data, &Dict090Data,
&Dict091Data, &Dict092Data, &Dict093Data, &Dict094Data, &Dict095Data,
&Dict096Data, &Dict097Data, &Dict098Data, &Dict099Data, &Dict100Data,
&Dict101Data, &Dict102Data, &Dict103Data, &Dict104Data, &Dict105Data,
&Dict106Data, &Dict107Data, &Dict108Data, &Dict109Data, &Dict110Data,
&Dict111Data, &Dict112Data, &Dict113Data, &Dict114Data, &Dict115Data,
&Dict116Data, &Dict117Data, &Dict118Data, &Dict119Data, &Dict120Data,
&Dict121Data, &Dict122Data, &Dict123Data, &Dict124Data, &Dict125Data,
&Dict126Data, &Dict127Data, &Dict128Data, &Dict129Data, &Dict130Data,
&Dict131Data, &Dict132Data, &Dict133Data, &Dict134Data, &Dict135Data,
&Dict136Data, &Dict137Data, &Dict138Data, &Dict139Data, &Dict140Data,
&Dict141Data, &Dict142Data, &Dict143Data, &Dict144Data, &Dict145Data,
&Dict146Data, &Dict147Data, &Dict148Data, &Dict149Data, &Dict150Data,
&Dict151Data, &Dict152Data, &Dict153Data, &Dict154Data, &Dict155Data,
&Dict156Data, &Dict157Data, &Dict158Data, &Dict159Data, &Dict160Data,
&Dict161Data, &Dict162Data, &Dict163Data, &Dict164Data, &Dict165Data,
&Dict166Data, &Dict167Data, &Dict168Data, &Dict169Data, &Dict170Data,
&Dict171Data, &Dict172Data, &Dict173Data, &Dict174Data, &Dict175Data,
&Dict176Data, &Dict177Data, &Dict178Data, &Dict179Data, &Dict180Data,
&Dict181Data, &Dict182Data, &Dict183Data, &Dict184Data, &Dict185Data,
&Dict186Data, &Dict187Data, &Dict188Data, &Dict189Data, &Dict190Data,
&Dict191Data, &Dict192Data, &Dict193Data, &Dict194Data, &Dict195Data,
&Dict196Data, &Dict197Data, &Dict198Data, &Dict199Data, &Dict200Data,
&Dict201Data, &Dict202Data, &Dict203Data, &Dict204Data, &Dict205Data,
&Dict206Data, &Dict207Data, &Dict208Data, &Dict209Data, &Dict210Data,
&Dict211Data, &Dict212Data, &Dict213Data, &Dict214Data, &Dict215Data,
&Dict216Data, &Dict217Data, &Dict218Data, &Dict219Data, &Dict220Data,
&Dict221Data, &Dict222Data, &Dict223Data, &Dict224Data, &Dict225Data,
&Dict226Data, &Dict227Data, &Dict228Data, &Dict229Data, &Dict230Data,
&Dict231Data, &Dict232Data, &Dict233Data, &Dict234Data, &Dict235Data,
&Dict236Data, &Dict237Data, &Dict238Data, &Dict239Data, &Dict240Data,
&Dict241Data, &Dict242Data, &Dict243Data, &Dict244Data, &Dict245Data,
&Dict246Data, &Dict247Data, &Dict248Data, &Dict249Data, &Dict250Data,
&Dict251Data, &Dict252Data, &Dict253Data, &Dict254Data, &Dict255Data,
&Dict256Data, &Dict257Data, &Dict258Data, &Dict259Data, &Dict260Data,
&Dict261Data, &Dict262Data, &Dict263Data, &Dict264Data, &Dict265Data,
&Dict266Data, &Dict267Data, &Dict268Data, &Dict269Data, &Dict270Data,
&Dict271Data, &Dict272Data, &Dict273Data, &Dict274Data, &Dict275Data,
&Dict276Data, &Dict277Data, &Dict278Data, &Dict279Data, &Dict280Data,
&Dict281Data, &Dict282Data, &Dict283Data, &Dict284Data, &Dict285Data,
&Dict286Data, &Dict287Data, &Dict288Data, &Dict289Data, &Dict290Data,
&Dict291Data, &Dict292Data, &Dict293Data, &Dict294Data, &Dict295Data,
&Dict296Data, &Dict297Data, &Dict298Data, &Dict299Data, &Dict300Data,
&Dict301Data, &Dict302Data, &Dict303Data, &Dict304Data, &Dict305Data,
&Dict306Data, &Dict307Data, &Dict308Data, &Dict309Data, &Dict310Data,
&Dict311Data, &Dict312Data, &Dict313Data, &Dict314Data, &Dict315Data,
&Dict316Data, &Dict317Data, &Dict318Data, &Dict319Data, &Dict320Data,
&Dict321Data, &Dict322Data, &Dict323Data, &Dict324Data, &Dict325Data,
&Dict326Data, &Dict327Data, &Dict328Data, &Dict329Data, &Dict330Data,
&Dict331Data, &Dict332Data, &Dict333Data, &Dict334Data, &Dict335Data,
&Dict336Data, &Dict337Data, &Dict338Data, &Dict339Data, &Dict340Data,
&Dict341Data, &Dict342Data, &Dict343Data, &Dict344Data, &Dict345Data,
&Dict346Data, &Dict347Data, &Dict348Data, &Dict349Data, &Dict350Data,
&Dict351Data, &Dict352Data, &Dict353Data, &Dict354Data, &Dict355Data,
&Dict356Data, &Dict357Data, &Dict358Data, &Dict359Data, &Dict360Data,
&Dict361Data, &Dict362Data, &Dict363Data, &Dict364Data, &Dict365Data,
&Dict366Data, &Dict367Data, &Dict368Data, &Dict369Data, &Dict370Data,
&Dict371Data, &Dict372Data, &Dict373Data, &Dict374Data, &Dict375Data,
&Dict376Data, &Dict377Data, &Dict378Data, &Dict379Data, &Dict380Data,
&Dict381Data, &Dict382Data, &Dict383Data, &Dict384Data, &Dict385Data,
&Dict386Data, &Dict387Data, &Dict388Data, &Dict389Data, &Dict390Data,
&Dict391Data, &Dict392Data, &Dict393Data, &Dict394Data, &Dict395Data,
&Dict396Data, &Dict397Data, &Dict398Data, &Dict399Data, &Dict400Data,
&Dict401Data, &Dict402Data, &Dict403Data, &Dict404Data, &Dict405Data,
&Dict406Data, &Dict407Data, &Dict408Data, &Dict409Data, &Dict410Data,
&Dict411Data, &Dict412Data, &Dict413Data, &Dict414Data, &Dict415Data,
&Dict416Data, &Dict417Data, &Dict418Data, &Dict419Data, &Dict420Data,
&Dict421Data, &Dict422Data, &Dict423Data, &Dict424Data, NULL
};

} // end anonymous namespace

static int vtkDICOMDictPrivateInitializerCounter;

vtkDICOMDictPrivateInitializer::vtkDICOMDictPrivateInitializer()
{
  if (vtkDICOMDictPrivateInitializerCounter++ == 0)
    {
    for (vtkDICOMDictionary::Dict **dp = PrivateDictData; *dp != NULL; dp++)
      {
      vtkDICOMDictionary::AddPrivateDictionary(*dp);
      }
    }
}

vtkDICOMDictPrivateInitializer::~vtkDICOMDictPrivateInitializer()
{
  if (--vtkDICOMDictPrivateInitializerCounter == 0)
    {
    for (vtkDICOMDictionary::Dict **dp = PrivateDictData; *dp != NULL; dp++)
      {
      vtkDICOMDictionary::RemovePrivateDictionary((*dp)->Name);
      }
    }
}
