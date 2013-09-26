/*=========================================================================
This is an automatically generated file.  Do not edit.
=========================================================================*/

#include "vtkDICOMDictionary.h"

namespace {

typedef vtkDICOMVR VR;
typedef vtkDICOMVM VM;
typedef vtkDICOMDictEntry::Entry DictEntry;

DictEntry DictRow0000[] = {
{ 0x0002, 0x0002, 0, VR::UI, VM::M1, "Media Storage SOP Class UID" },
{ 0x0008, 0x0008, 0, VR::CS, VM::M2TN, "Image Type" },
{ 0x0008, 0x1049, 0, VR::SQ, VM::M1, "Physician(s) of Record Identification Sequence" },
{ 0x0010, 0x0010, 0, VR::PN, VM::M1, "Patient's Name" },
{ 0x0018, 0x9251, 0, VR::SQ, VM::M1, "MR Arterial Spin Labeling Sequence" },
{ 0x0020, 0x0020, 0, VR::CS, VM::M2, "Patient Orientation" },
{ 0x0022, 0x0022, 0, VR::SQ, VM::M1, "Right Image Sequence" },
{ 0x0024, 0x0024, 0, VR::SQ, VM::M1, "Background Illumination Color Code Sequence" },
{ 0x0028, 0x0808, 1, VR::AT, VM::M1TN, "Image Data Location" },
{ 0x0032, 0x0032, 1, VR::DA, VM::M1, "Study Verified Date" },
{ 0x0040, 0x1001, 0, VR::SH, VM::M1, "Requested Procedure ID" },
{ 0x0046, 0x0046, 0, VR::FD, VM::M1, "Corneal Size" },
{ 0x0072, 0x0072, 0, VR::DS, VM::M1TN, "Selector DS Value" },
{ 0x0400, 0x0010, 0, VR::UI, VM::M1, "MAC Calculation Transfer Syntax UID" },
{ 0x2020, 0x00A2, 0, VR::CS, VM::M1, "Decimate/Crop Result" },
{ 0x4000, 0x4000, 1, VR::LT, VM::M1, "Text Comments" },
{ 0x4008, 0x010C, 1, VR::PN, VM::M1, "Interpretation Author" },
{ 0xFFFA, 0xFFFA, 0, VR::SQ, VM::M1, "Digital Signatures Sequence" },
{ 0xFFFC, 0xFFFC, 0, VR::OB, VM::M1, "Data Set Trailing Padding" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0001[] = {
{ 0x0002, 0x0003, 0, VR::UI, VM::M1, "Media Storage SOP Instance UID" },
{ 0x0008, 0x1048, 0, VR::PN, VM::M1TN, "Physician(s) of Record" },
{ 0x0010, 0x1050, 1, VR::LO, VM::M1TN, "Insurance Plan Identification" },
{ 0x0018, 0x9250, 0, VR::CS, VM::M1, "Arterial Spin Labeling Contrast" },
{ 0x0024, 0x0025, 0, VR::FL, VM::M1, "Stimulus Area" },
{ 0x0032, 0x0033, 1, VR::TM, VM::M1, "Study Verified Time" },
{ 0x0074, 0x1034, 0, VR::CS, VM::M1, "Double Exposure Flag" },
{ 0x0400, 0x0401, 0, VR::SQ, VM::M1, "Digital Signature Purpose Code Sequence" },
{ 0x3006, 0x00C4, 0, VR::CS, VM::M1, "Frame of Reference Transformation Type" },
{ 0x300A, 0x00C8, 0, VR::IS, VM::M1, "Reference Image Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0002[] = {
{ 0x0002, 0x0000, 0, VR::UL, VM::M1, "File Meta Information Group Length" },
{ 0x0012, 0x0010, 0, VR::LO, VM::M1, "Clinical Trial Sponsor Name" },
{ 0x0018, 0x9253, 0, VR::US, VM::M1, "ASL Slab Number" },
{ 0x0020, 0x0022, 1, VR::IS, VM::M1, "Overlay Number" },
{ 0x0022, 0x0020, 0, VR::SQ, VM::M1, "Stereo Pairs Sequence" },
{ 0x0040, 0x1003, 0, VR::SH, VM::M1, "Requested Procedure Priority" },
{ 0x0046, 0x0044, 0, VR::FD, VM::M1, "Pupil Size" },
{ 0x0072, 0x0070, 0, VR::UT, VM::M1, "Selector UT Value" },
{ 0x0400, 0x0402, 0, VR::SQ, VM::M1, "Referenced Digital Signature Sequence" },
{ 0x2020, 0x00A0, 0, VR::CS, VM::M1, "Requested Image Size Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0003[] = {
{ 0x0002, 0x0001, 0, VR::OB, VM::M1, "File Meta Information Version" },
{ 0x0018, 0x9252, 0, VR::LO, VM::M1, "ASL Technique Description" },
{ 0x0022, 0x0021, 0, VR::SQ, VM::M1, "Left Image Sequence" },
{ 0x0032, 0x1070, 0, VR::LO, VM::M1, "Requested Contrast Agent" },
{ 0x0040, 0x1002, 0, VR::LO, VM::M1, "Reason for the Requested Procedure" },
{ 0x0074, 0x1036, 0, VR::CS, VM::M1, "Double Exposure Ordering" },
{ 0x0400, 0x0403, 0, VR::SQ, VM::M1, "Referenced SOP Instance MAC Sequence" },
{ 0x3006, 0x00C6, 0, VR::DS, VM::M16, "Frame of Reference Transformation Matrix" },
{ 0x300A, 0x00CA, 0, VR::SQ, VM::M1, "Planned Verification Image Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0004[] = {
{ 0x0018, 0x9255, 0, VR::FD, VM::M3, "ASL Slab Orientation" },
{ 0x0020, 0x0024, 1, VR::IS, VM::M1, "Curve Number" },
{ 0x0024, 0x0020, 0, VR::FL, VM::M1, "Background Luminance" },
{ 0x0040, 0x1005, 0, VR::LO, VM::M1, "Requested Procedure Location" },
{ 0x0046, 0x0042, 0, VR::FD, VM::M1, "Channel Width" },
{ 0x0054, 0x0050, 0, VR::US, VM::M1TN, "Rotation Vector" },
{ 0x0054, 0x1401, 1, VR::CS, VM::M1, "Dead Time Correction Flag" },
{ 0x0072, 0x0076, 0, VR::FL, VM::M1TN, "Selector FL Value" },
{ 0x0400, 0x0404, 0, VR::OB, VM::M1, "MAC" },
{ 0x4008, 0x0108, 1, VR::DA, VM::M1, "Interpretation Transcription Date" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0005[] = {
{ 0x0018, 0x9254, 0, VR::FD, VM::M1, "ASL Slab Thickness" },
{ 0x0022, 0x1066, 0, VR::LO, VM::M1, "Vitreous Status Description" },
{ 0x0024, 0x0021, 0, VR::SQ, VM::M1, "Stimulus Color Code Sequence" },
{ 0x0040, 0x1004, 0, VR::LO, VM::M1, "Patient Transport Arrangements" },
{ 0x0054, 0x0051, 0, VR::US, VM::M1, "Number of Rotations" },
{ 0x0054, 0x1400, 1, VR::CS, VM::M1TN, "Counts Included" },
{ 0x0074, 0x1030, 0, VR::SQ, VM::M1, "Delivery Verification Image Sequence" },
{ 0x0400, 0x0015, 0, VR::CS, VM::M1, "MAC Algorithm" },
{ 0x3006, 0x00C0, 0, VR::SQ, VM::M1, "Frame of Reference Relationship Sequence" },
{ 0x300A, 0x00CC, 0, VR::LO, VM::M1TN, "Imaging Device-Specific Acquisition Parameters" },
{ 0x4008, 0x0109, 1, VR::TM, VM::M1, "Interpretation Transcription Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0006[] = {
{ 0x0018, 0x9257, 0, VR::CS, VM::M1, "ASL Context" },
{ 0x0020, 0x0026, 1, VR::IS, VM::M1, "LUT Number" },
{ 0x0022, 0x1065, 0, VR::LO, VM::M1, "Lens Status Description" },
{ 0x0032, 0x0034, 1, VR::DA, VM::M1, "Study Read Date" },
{ 0x0040, 0x1007, 1, VR::SH, VM::M1, "Filler Order Number / Procedure" },
{ 0x0046, 0x0040, 0, VR::FD, VM::M1, "Optical Transmittance" },
{ 0x0054, 0x0052, 0, VR::SQ, VM::M1, "Rotation Information Sequence" },
{ 0x0072, 0x0074, 0, VR::FD, VM::M1TN, "Selector FD Value" },
{ 0x0076, 0x0070, 0, VR::US, VM::M1, "Component 1 Referenced ID" },
{ 0x4008, 0x010A, 1, VR::PN, VM::M1, "Interpretation Transcriber" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0007[] = {
{ 0x0018, 0x9256, 0, VR::FD, VM::M3, "ASL Mid Slab Position" },
{ 0x0032, 0x0035, 1, VR::TM, VM::M1, "Study Read Time" },
{ 0x0040, 0x1006, 1, VR::SH, VM::M1, "Placer Order Number / Procedure" },
{ 0x0054, 0x0053, 0, VR::US, VM::M1, "Number of Frames in Rotation" },
{ 0x0074, 0x1032, 0, VR::CS, VM::M1, "Verification Image Timing" },
{ 0x3006, 0x00C2, 0, VR::UI, VM::M1, "Related Frame of Reference UID" },
{ 0x300A, 0x00CE, 0, VR::CS, VM::M1, "Treatment Delivery Type" },
{ 0x4008, 0x010B, 1, VR::ST, VM::M1, "Interpretation Text" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0008[] = {
{ 0x0018, 0x0010, 0, VR::LO, VM::M1, "Contrast/Bolus Agent" },
{ 0x0018, 0x9259, 0, VR::CS, VM::M1, "ASL Crusher Flag" },
{ 0x0028, 0x0800, 1, VR::CS, VM::M1TN, "Code Label" },
{ 0x0038, 0x0030, 1, VR::DA, VM::M1, "Discharge Date" },
{ 0x0040, 0x1009, 0, VR::SH, VM::M1, "Reporting Priority" },
{ 0x0072, 0x007A, 0, VR::US, VM::M1TN, "Selector US Value" },
{ 0x0078, 0x0070, 0, VR::SQ, VM::M1, "Implant Template Group Member Matching 2D Coordinates Sequence" },
{ 0x4008, 0x4000, 1, VR::ST, VM::M1, "Results Comments" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0009[] = {
{ 0x0008, 0x0001, 1, VR::UL, VM::M1, "Length to End" },
{ 0x0008, 0x1040, 0, VR::LO, VM::M1, "Institutional Department Name" },
{ 0x0018, 0x1050, 0, VR::DS, VM::M1, "Spatial Resolution" },
{ 0x0018, 0x9258, 0, VR::UL, VM::M1, "ASL Pulse Train Duration" },
{ 0x0040, 0x1008, 0, VR::LO, VM::M1, "Confidentiality Code" },
{ 0x300A, 0x00C0, 0, VR::IS, VM::M1, "Beam Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0010[] = {
{ 0x0018, 0x0012, 0, VR::SQ, VM::M1, "Contrast/Bolus Agent Sequence" },
{ 0x0018, 0x925B, 0, VR::LO, VM::M1, "ASL Crusher Description" },
{ 0x0028, 0x0802, 1, VR::US, VM::M1, "Number of Tables" },
{ 0x0038, 0x0032, 1, VR::TM, VM::M1, "Discharge Time" },
{ 0x0072, 0x0078, 0, VR::UL, VM::M1TN, "Selector UL Value" },
{ 0x300A, 0x00C3, 0, VR::ST, VM::M1, "Beam Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0011[] = {
{ 0x0018, 0x925A, 0, VR::FD, VM::M1, "ASL Crusher Flow" },
{ 0x0028, 0x0803, 1, VR::AT, VM::M1TN, "Code Table Location" },
{ 0x0040, 0x100A, 0, VR::SQ, VM::M1, "Reason for Requested Procedure Code Sequence" },
{ 0x3008, 0x00C0, 0, VR::SQ, VM::M1, "Recorded Compensator Sequence" },
{ 0x300A, 0x00C2, 0, VR::LO, VM::M1, "Beam Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0012[] = {
{ 0x0018, 0x0014, 0, VR::SQ, VM::M1, "Contrast/Bolus Administration Route Sequence" },
{ 0x0018, 0x925D, 0, VR::SQ, VM::M1, "ASL Bolus Cut-off Timing Sequence" },
{ 0x0024, 0x0028, 0, VR::FL, VM::M1, "Stimulus Presentation Time" },
{ 0x0028, 0x0804, 1, VR::US, VM::M1, "Bits For Code Word" },
{ 0x0072, 0x007E, 0, VR::SS, VM::M1TN, "Selector SS Value" },
{ 0x4008, 0x0100, 1, VR::DA, VM::M1, "Interpretation Recorded Date" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0013[] = {
{ 0x0008, 0x0005, 0, VR::CS, VM::M1TN, "Specific Character Set" },
{ 0x0018, 0x0015, 0, VR::CS, VM::M1, "Body Part Examined" },
{ 0x0018, 0x925C, 0, VR::CS, VM::M1, "ASL Bolus Cut-off Flag" },
{ 0x0074, 0x1038, 1, VR::DS, VM::M1, "Double Exposure Meterset (Trial)" },
{ 0x3006, 0x00C8, 0, VR::LO, VM::M1, "Frame of Reference Transformation Comment" },
{ 0x300A, 0x00C4, 0, VR::CS, VM::M1, "Beam Type" },
{ 0x4008, 0x0101, 1, VR::TM, VM::M1, "Interpretation Recorded Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0014[] = {
{ 0x0008, 0x0006, 0, VR::SQ, VM::M1, "Language Code Sequence" },
{ 0x0018, 0x925F, 0, VR::UL, VM::M1, "ASL Bolus Cut-off Delay Time" },
{ 0x0068, 0x65F0, 0, VR::FD, VM::M4, "2D Plane Intersection" },
{ 0x0072, 0x007C, 0, VR::SL, VM::M1TN, "Selector SL Value" },
{ 0x300A, 0x00C7, 0, VR::CS, VM::M1, "High-Dose Technique Type" },
{ 0x4008, 0x0102, 1, VR::PN, VM::M1, "Interpretation Recorder" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0015[] = {
{ 0x0018, 0x925E, 0, VR::LO, VM::M1, "ASL Bolus Cut-off Technique" },
{ 0x0074, 0x103A, 1, VR::DS, VM::M4, "Double Exposure Field Delta (Trial)" },
{ 0x300A, 0x00C6, 0, VR::CS, VM::M1, "Radiation Type" },
{ 0x300C, 0x00C0, 0, VR::IS, VM::M1, "Referenced Wedge Number" },
{ 0x4008, 0x0103, 1, VR::LO, VM::M1, "Reference to Recorded Sound" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0016[] = {
{ 0x0002, 0x0012, 0, VR::UI, VM::M1, "Implementation Class UID" },
{ 0x0008, 0x0018, 0, VR::UI, VM::M1, "SOP Instance UID" },
{ 0x0018, 0x1049, 0, VR::DS, VM::M1, "Contrast/Bolus Ingredient Concentration" },
{ 0x0018, 0x9241, 0, VR::US, VM::M1, "Gradient Echo Train Length" },
{ 0x0020, 0x0030, 1, VR::DS, VM::M3, "Image Position" },
{ 0x0022, 0x0032, 0, VR::FL, VM::M2T2N, "Reference Coordinates" },
{ 0x0024, 0x0034, 0, VR::SQ, VM::M1, "Visual Field Catch Trial Sequence" },
{ 0x0040, 0x0440, 0, VR::SQ, VM::M1, "Protocol Context Sequence" },
{ 0x0040, 0x1011, 0, VR::SQ, VM::M1, "Intended Recipients of Results Identification Sequence" },
{ 0x0070, 0x0060, 0, VR::SQ, VM::M1, "Graphic Layer Sequence" },
{ 0x0072, 0x0062, 0, VR::CS, VM::M1TN, "Selector CS Value" },
{ 0x300A, 0x00D9, 0, VR::FL, VM::M1, "Isocenter to Wedge Tray Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0017[] = {
{ 0x0002, 0x0013, 0, VR::SH, VM::M1, "Implementation Version Name" },
{ 0x0010, 0x1040, 0, VR::LO, VM::M1, "Patient's Address" },
{ 0x0018, 0x1048, 0, VR::CS, VM::M1, "Contrast/Bolus Ingredient" },
{ 0x0018, 0x9240, 0, VR::US, VM::M1, "RF Echo Train Length" },
{ 0x0020, 0x1070, 1, VR::IS, VM::M1TN, "Other Study Numbers" },
{ 0x0024, 0x0035, 0, VR::US, VM::M1, "Fixation Checked Quantity" },
{ 0x0040, 0x0441, 0, VR::SQ, VM::M1, "Content Item Modifier Sequence" },
{ 0x0040, 0x1010, 0, VR::PN, VM::M1TN, "Names of Intended Recipients of Results" },
{ 0x0040, 0x1400, 0, VR::LT, VM::M1, "Requested Procedure Comments" },
{ 0x0054, 0x1004, 0, VR::CS, VM::M1, "Reprojection Method" },
{ 0x0074, 0x1024, 1, VR::IS, VM::M1, "Beam Order Index (Trial)" },
{ 0x300A, 0x00D8, 0, VR::DS, VM::M1, "Wedge Orientation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0018[] = {
{ 0x0002, 0x0010, 0, VR::UI, VM::M1, "Transfer Syntax UID" },
{ 0x0008, 0x001A, 0, VR::UI, VM::M1TN, "Related General SOP Class UID" },
{ 0x0020, 0x0032, 0, VR::DS, VM::M3, "Image Position (Patient)" },
{ 0x0022, 0x0030, 0, VR::FL, VM::M1, "Axial Length of the Eye" },
{ 0x0024, 0x0036, 0, VR::US, VM::M1, "Patient Not Properly Fixated Quantity" },
{ 0x0070, 0x0062, 0, VR::IS, VM::M1, "Graphic Layer Order" },
{ 0x0072, 0x0060, 0, VR::AT, VM::M1TN, "Selector AT Value" },
{ 0x0074, 0x1027, 0, VR::FD, VM::M1, "Table Top Longitudinal Adjusted Position" },
{ 0x2010, 0x0080, 0, VR::CS, VM::M1, "Smoothing Type" },
{ 0x300A, 0x00DB, 0, VR::FL, VM::M1, "Wedge Thin Edge Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0019[] = {
{ 0x0008, 0x001B, 0, VR::UI, VM::M1, "Original Specialized SOP Class UID" },
{ 0x0022, 0x0031, 0, VR::SQ, VM::M1, "Ophthalmic Frame Location Sequence" },
{ 0x0024, 0x0037, 0, VR::CS, VM::M1, "Presented Visual Stimuli Data Flag" },
{ 0x0032, 0x1060, 0, VR::LO, VM::M1, "Requested Procedure Description" },
{ 0x0040, 0x1012, 0, VR::SQ, VM::M1, "Reason For Performed Procedure Code Sequence" },
{ 0x0054, 0x1006, 0, VR::CS, VM::M1, "SUV Type" },
{ 0x0074, 0x1026, 0, VR::FD, VM::M1, "Table Top Vertical Adjusted Position" },
{ 0x300A, 0x00DA, 0, VR::DS, VM::M1, "Source to Wedge Tray Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0020[] = {
{ 0x0002, 0x0016, 0, VR::AE, VM::M1, "Source Application Entity Title" },
{ 0x0022, 0x0036, 0, VR::FL, VM::M1, "Maximum Depth Distortion" },
{ 0x0046, 0x0052, 0, VR::SQ, VM::M1, "Autorefraction Left Eye Sequence" },
{ 0x0054, 0x1001, 0, VR::CS, VM::M1, "Units" },
{ 0x0072, 0x0066, 0, VR::LO, VM::M1TN, "Selector LO Value" },
{ 0x300A, 0x00DD, 0, VR::ST, VM::M1, "Bolus Description" },
{ 0x4008, 0x0118, 1, VR::SQ, VM::M1, "Results Distribution List Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0021[] = {
{ 0x0014, 0x1040, 0, VR::ST, VM::M1, "Environmental Conditions" },
{ 0x0020, 0x0035, 1, VR::DS, VM::M6, "Image Orientation" },
{ 0x0022, 0x0037, 0, VR::FL, VM::M1, "Along-scan Spatial Resolution" },
{ 0x0054, 0x1000, 0, VR::CS, VM::M2, "Series Type" },
{ 0x0074, 0x1020, 0, VR::SQ, VM::M1, "Beam Task Sequence" },
{ 0x0400, 0x0005, 0, VR::US, VM::M1, "MAC ID Number" },
{ 0x300A, 0x00DC, 0, VR::SH, VM::M1, "Bolus ID" },
{ 0x4008, 0x0119, 1, VR::PN, VM::M1, "Distribution Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0022[] = {
{ 0x0024, 0x0032, 0, VR::SQ, VM::M1, "Fixation Sequence" },
{ 0x0046, 0x0050, 0, VR::SQ, VM::M1, "Autorefraction Right Eye Sequence" },
{ 0x0070, 0x0066, 0, VR::US, VM::M1, "Graphic Layer Recommended Display Grayscale Value" },
{ 0x0072, 0x0064, 0, VR::IS, VM::M1TN, "Selector IS Value" },
{ 0x0076, 0x0060, 0, VR::SQ, VM::M1, "Component Assembly Sequence" },
{ 0x4008, 0x011A, 1, VR::LO, VM::M1, "Distribution Address" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0023[] = {
{ 0x0020, 0x0037, 0, VR::DS, VM::M6, "Image Orientation (Patient)" },
{ 0x0022, 0x0035, 0, VR::FL, VM::M1, "Depth Spatial Resolution" },
{ 0x0024, 0x0033, 0, VR::SQ, VM::M1, "Fixation Monitoring Code Sequence" },
{ 0x0032, 0x1064, 0, VR::SQ, VM::M1, "Requested Procedure Code Sequence" },
{ 0x0054, 0x1002, 0, VR::CS, VM::M1, "Counts Source" },
{ 0x0070, 0x0067, 1, VR::US, VM::M3, "Graphic Layer Recommended Display RGB Value" },
{ 0x0074, 0x1022, 0, VR::CS, VM::M1, "Beam Task Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0024[] = {
{ 0x0008, 0x0010, 1, VR::SH, VM::M1, "Recognition Code" },
{ 0x0018, 0x1041, 0, VR::DS, VM::M1, "Contrast/Bolus Volume" },
{ 0x0028, 0x0030, 0, VR::DS, VM::M2, "Pixel Spacing" },
{ 0x0038, 0x0020, 0, VR::DA, VM::M1, "Admitting Date" },
{ 0x0040, 0x9211, 0, VR::XS, VM::M1, "Real World Value Last Value Mapped" },
{ 0x0070, 0x0068, 0, VR::LO, VM::M1, "Graphic Layer Description" },
{ 0x0072, 0x006A, 0, VR::PN, VM::M1TN, "Selector PN Value" },
{ 0x0074, 0x102D, 0, VR::FD, VM::M1, "Table Top Roll Adjusted Angle" },
{ 0x0078, 0x0060, 0, VR::FD, VM::M9, "3D Implant Template Group Member Matching Axes" },
{ 0x300A, 0x00D1, 0, VR::SQ, VM::M1, "Wedge Sequence" },
{ 0x4008, 0x0114, 1, VR::PN, VM::M1, "Physician Approving Interpretation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0025[] = {
{ 0x0008, 0x1050, 0, VR::PN, VM::M1TN, "Performing Physician's Name" },
{ 0x0018, 0x1040, 0, VR::LO, VM::M1, "Contrast/Bolus Route" },
{ 0x0018, 0x1450, 0, VR::DS, VM::M1, "Column Angulation" },
{ 0x0028, 0x0031, 0, VR::DS, VM::M2, "Zoom Factor" },
{ 0x0038, 0x0021, 0, VR::TM, VM::M1, "Admitting Time" },
{ 0x0040, 0x9210, 0, VR::SH, VM::M1, "LUT Label" },
{ 0x0074, 0x102C, 0, VR::FD, VM::M1, "Table Top Pitch Adjusted Angle" },
{ 0x300A, 0x00D0, 0, VR::IS, VM::M1, "Number of Wedges" },
{ 0x4008, 0x0115, 1, VR::LT, VM::M1, "Interpretation Diagnosis Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0026[] = {
{ 0x0008, 0x0012, 0, VR::DA, VM::M1, "Instance Creation Date" },
{ 0x0018, 0x1043, 0, VR::TM, VM::M1, "Contrast/Bolus Stop Time" },
{ 0x0022, 0x0038, 0, VR::FL, VM::M1, "Maximum Along-scan Distortion" },
{ 0x0028, 0x0032, 0, VR::DS, VM::M2, "Zoom Center" },
{ 0x003A, 0x0020, 0, VR::SH, VM::M1, "Multiplex Group Label" },
{ 0x0072, 0x0068, 0, VR::LT, VM::M1, "Selector LT Value" },
{ 0x300A, 0x00D3, 0, VR::CS, VM::M1, "Wedge Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0027[] = {
{ 0x0008, 0x0013, 0, VR::TM, VM::M1, "Instance Creation Time" },
{ 0x0008, 0x1052, 0, VR::SQ, VM::M1, "Performing Physician Identification Sequence" },
{ 0x0018, 0x1042, 0, VR::TM, VM::M1, "Contrast/Bolus Start Time" },
{ 0x0022, 0x0039, 0, VR::CS, VM::M1, "Ophthalmic Image Orientation" },
{ 0x0040, 0x9212, 0, VR::FD, VM::M1TN, "Real World Value LUT Data" },
{ 0x3008, 0x00D0, 0, VR::SQ, VM::M1, "Recorded Block Sequence" },
{ 0x300A, 0x00D2, 0, VR::IS, VM::M1, "Wedge Number" },
{ 0x4008, 0x0117, 1, VR::SQ, VM::M1, "Interpretation Diagnosis Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0028[] = {
{ 0x0008, 0x0014, 0, VR::UI, VM::M1, "Instance Creator UID" },
{ 0x0018, 0x1045, 0, VR::IS, VM::M1, "Syringe Counts" },
{ 0x0024, 0x0038, 0, VR::US, VM::M1, "Number of Visual Stimuli" },
{ 0x0028, 0x0034, 0, VR::IS, VM::M2, "Pixel Aspect Ratio" },
{ 0x0072, 0x006E, 0, VR::ST, VM::M1, "Selector ST Value" },
{ 0x300A, 0x00D5, 0, VR::IS, VM::M1, "Wedge Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0029[] = {
{ 0x0018, 0x1044, 0, VR::DS, VM::M1, "Contrast/Bolus Total Dose" },
{ 0x0024, 0x0039, 0, VR::CS, VM::M1, "Excessive Fixation Losses Data Flag" },
{ 0x0074, 0x1028, 0, VR::FD, VM::M1, "Table Top Lateral Adjusted Position" },
{ 0x300A, 0x00D4, 0, VR::SH, VM::M1, "Wedge ID" },
{ 0x4008, 0x0111, 1, VR::SQ, VM::M1, "Interpretation Approver Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0030[] = {
{ 0x0008, 0x0016, 0, VR::UI, VM::M1, "SOP Class UID" },
{ 0x0018, 0x1047, 0, VR::DS, VM::M1TN, "Contrast Flow Duration" },
{ 0x0068, 0x65E0, 0, VR::SQ, VM::M1, "2D Plane Coordinates Sequence" },
{ 0x0072, 0x006C, 0, VR::SH, VM::M1TN, "Selector SH Value" },
{ 0x0074, 0x102B, 0, VR::FD, VM::M1, "Table Top Eccentric Adjusted Angle" },
{ 0x300A, 0x00D7, 0, VR::FL, VM::M1, "Total Wedge Tray Water-Equivalent Thickness" },
{ 0x4008, 0x0112, 1, VR::DA, VM::M1, "Interpretation Approval Date" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0031[] = {
{ 0x0018, 0x1046, 0, VR::DS, VM::M1TN, "Contrast Flow Rate" },
{ 0x0040, 0x9216, 0, VR::XS, VM::M1, "Real World Value First Value Mapped" },
{ 0x0074, 0x102A, 0, VR::FD, VM::M1, "Patient Support Adjusted Angle" },
{ 0x300A, 0x00D6, 0, VR::DS, VM::M1, "Wedge Factor" },
{ 0x300C, 0x00D0, 0, VR::IS, VM::M1, "Referenced Compensator Number" },
{ 0x4008, 0x0113, 1, VR::TM, VM::M1, "Interpretation Approval Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0032[] = {
{ 0x0010, 0x0030, 0, VR::DA, VM::M1, "Patient's Birth Date" },
{ 0x0014, 0x0034, 0, VR::DS, VM::M1TN, "Material Isolation Diameter" },
{ 0x0018, 0x0038, 0, VR::CS, VM::M1, "Intervention Status" },
{ 0x0018, 0x1079, 0, VR::DT, VM::M1, "Radiopharmaceutical Stop DateTime" },
{ 0x0020, 0x1041, 0, VR::DS, VM::M1, "Slice Location" },
{ 0x0020, 0x9249, 0, VR::CS, VM::M1, "Ending Respiratory Phase" },
{ 0x0022, 0x0002, 0, VR::US, VM::M2, "Light Path Filter Pass Band" },
{ 0x0028, 0x0008, 0, VR::IS, VM::M1, "Number of Frames" },
{ 0x0032, 0x0012, 1, VR::LO, VM::M1, "Study ID Issuer" },
{ 0x003A, 0x001A, 0, VR::DS, VM::M1, "Sampling Frequency" },
{ 0x0040, 0xDB0D, 1, VR::UI, VM::M1, "Template Extension Creator UID" },
{ 0x0070, 0x0050, 1, VR::US, VM::M2, "Displayed Area Top Left Hand Corner (Trial)" },
{ 0x0072, 0x0052, 0, VR::AT, VM::M1TN, "Selector Sequence Pointer" },
{ 0x2000, 0x00A2, 0, VR::SQ, VM::M1, "Media Installed Sequence" },
{ 0x300A, 0x00E9, 0, VR::DS, VM::M2, "Compensator Pixel Spacing" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0033[] = {
{ 0x0018, 0x0039, 1, VR::CS, VM::M1, "Therapy Description" },
{ 0x0018, 0x1078, 0, VR::DT, VM::M1, "Radiopharmaceutical Start DateTime" },
{ 0x0020, 0x1040, 0, VR::LO, VM::M1, "Position Reference Indicator" },
{ 0x0020, 0x9248, 0, VR::FL, VM::M1, "Ending Respiratory Amplitude" },
{ 0x0022, 0x0003, 0, VR::US, VM::M1, "Image Path Filter Pass-Through Wavelength" },
{ 0x0028, 0x0009, 0, VR::AT, VM::M1TN, "Frame Increment Pointer" },
{ 0x0040, 0xDB0C, 1, VR::UI, VM::M1, "Template Extension Organization UID" },
{ 0x0070, 0x0051, 1, VR::US, VM::M2, "Displayed Area Bottom Right Hand Corner (Trial)" },
{ 0x300A, 0x00E8, 0, VR::IS, VM::M1, "Compensator Columns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0034[] = {
{ 0x0008, 0x002A, 0, VR::DT, VM::M1, "Acquisition DateTime" },
{ 0x0010, 0x0032, 0, VR::TM, VM::M1, "Patient's Birth Time" },
{ 0x0012, 0x0030, 0, VR::LO, VM::M1, "Clinical Trial Site ID" },
{ 0x0018, 0x003A, 0, VR::ST, VM::M1, "Intervention Description" },
{ 0x0028, 0x000A, 0, VR::AT, VM::M1TN, "Frame Dimension Pointer" },
{ 0x0032, 0x1051, 1, VR::TM, VM::M1, "Study Completion Time" },
{ 0x0038, 0x001A, 1, VR::DA, VM::M1, "Scheduled Admission Date" },
{ 0x0046, 0x0064, 0, VR::FD, VM::M1, "Other Pupillary Distance" },
{ 0x0070, 0x0052, 0, VR::SL, VM::M2, "Displayed Area Top Left Hand Corner" },
{ 0x0072, 0x0050, 0, VR::CS, VM::M1, "Selector Attribute VR" },
{ 0x2000, 0x00A0, 0, VR::US, VM::M1, "Memory Bit Depth" },
{ 0x300A, 0x00EB, 0, VR::DS, VM::M1TN, "Compensator Transmission Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0035[] = {
{ 0x0012, 0x0031, 0, VR::LO, VM::M1, "Clinical Trial Site Name" },
{ 0x0022, 0x0001, 0, VR::US, VM::M1, "Light Path Filter Pass-Through Wavelength" },
{ 0x0022, 0x1040, 0, VR::SQ, VM::M1, "Refractive Surgery Type Code Sequence" },
{ 0x0032, 0x1050, 1, VR::DA, VM::M1, "Study Completion Date" },
{ 0x0038, 0x001B, 1, VR::TM, VM::M1, "Scheduled Admission Time" },
{ 0x0070, 0x0053, 0, VR::SL, VM::M2, "Displayed Area Bottom Right Hand Corner" },
{ 0x0076, 0x0055, 0, VR::US, VM::M1, "Component ID" },
{ 0x2000, 0x00A1, 0, VR::US, VM::M1, "Printing Bit Depth" },
{ 0x300A, 0x00EA, 0, VR::DS, VM::M2, "Compensator Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0036[] = {
{ 0x0014, 0x0030, 0, VR::DS, VM::M1TN, "Material Thickness" },
{ 0x0022, 0x0006, 0, VR::SQ, VM::M1, "Patient Eye Movement Command Code Sequence" },
{ 0x0038, 0x001C, 1, VR::DA, VM::M1, "Scheduled Discharge Date" },
{ 0x0046, 0x0062, 0, VR::FD, VM::M1, "Near Pupillary Distance" },
{ 0x0054, 0x0070, 0, VR::US, VM::M1TN, "Time Slot Vector" },
{ 0x0072, 0x0056, 0, VR::LO, VM::M1, "Selector Attribute Private Creator" },
{ 0x300A, 0x00ED, 0, VR::IS, VM::M1, "Number of Boli" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0037[] = {
{ 0x0022, 0x0007, 0, VR::FL, VM::M1, "Spherical Lens Power" },
{ 0x0038, 0x001D, 1, VR::TM, VM::M1, "Scheduled Discharge Time" },
{ 0x0046, 0x0063, 0, VR::FD, VM::M1, "Intermediate Pupillary Distance" },
{ 0x0054, 0x0071, 0, VR::US, VM::M1, "Number of Time Slots" },
{ 0x300A, 0x00EC, 0, VR::DS, VM::M1TN, "Compensator Thickness Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0038[] = {
{ 0x0014, 0x0032, 0, VR::DS, VM::M1TN, "Material Pipe Diameter" },
{ 0x0022, 0x0004, 0, VR::US, VM::M2, "Image Path Filter Pass Band" },
{ 0x0032, 0x1055, 1, VR::CS, VM::M1, "Study Component Status ID" },
{ 0x0038, 0x001E, 1, VR::LO, VM::M1, "Scheduled Patient Institution Residence" },
{ 0x0040, 0xDB0B, 1, VR::CS, VM::M1, "Template Extension Flag" },
{ 0x0046, 0x0060, 0, VR::FD, VM::M1, "Distance Pupillary Distance" },
{ 0x0054, 0x0072, 0, VR::SQ, VM::M1, "Time Slot Information Sequence" },
{ 0x0072, 0x0054, 0, VR::LO, VM::M1TN, "Selector Sequence Pointer Private Creator" },
{ 0x2000, 0x00A4, 0, VR::SQ, VM::M1, "Other Media Available Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0039[] = {
{ 0x0022, 0x0005, 0, VR::CS, VM::M1, "Patient Eye Movement Commanded" },
{ 0x0022, 0x1044, 0, VR::SQ, VM::M1, "Ophthalmic Ultrasound Axial Measurements Type Code Sequence" },
{ 0x0054, 0x0073, 0, VR::DS, VM::M1, "Time Slot Time" },
{ 0x300A, 0x00EE, 0, VR::CS, VM::M1, "Compensator Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0040[] = {
{ 0x0008, 0x0020, 0, VR::DA, VM::M1, "Study Date" },
{ 0x0018, 0x0030, 1, VR::LO, VM::M1TN, "Radionuclide" },
{ 0x0018, 0x1071, 0, VR::DS, VM::M1, "Radiopharmaceutical Volume" },
{ 0x0020, 0x9241, 0, VR::FL, VM::M1, "Nominal Percentage of Cardiac Phase" },
{ 0x0022, 0x000A, 0, VR::FL, VM::M1, "Emmetropic Magnification" },
{ 0x0028, 0x1041, 0, VR::SS, VM::M1, "Pixel Intensity Relationship Sign" },
{ 0x0038, 0x0010, 0, VR::LO, VM::M1, "Admission ID" },
{ 0x0038, 0x0400, 0, VR::LO, VM::M1, "Patient's Institution Residence" },
{ 0x0078, 0x0050, 0, VR::FD, VM::M3, "3D Implant Template Group Member Matching Point" },
{ 0x300A, 0x00E1, 0, VR::SH, VM::M1, "Material ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0041[] = {
{ 0x0008, 0x0021, 0, VR::DA, VM::M1, "Series Date" },
{ 0x0008, 0x1060, 0, VR::PN, VM::M1TN, "Name of Physician(s) Reading Study" },
{ 0x0018, 0x0031, 0, VR::LO, VM::M1, "Radiopharmaceutical" },
{ 0x0018, 0x1070, 0, VR::LO, VM::M1, "Radiopharmaceutical Route" },
{ 0x0018, 0x1460, 0, VR::DS, VM::M1, "Tomo Layer Height" },
{ 0x0022, 0x000B, 0, VR::FL, VM::M1, "Intra Ocular Pressure" },
{ 0x0028, 0x1040, 0, VR::CS, VM::M1, "Pixel Intensity Relationship" },
{ 0x0038, 0x0011, 1, VR::LO, VM::M1, "Issuer of Admission ID" },
{ 0x300A, 0x00E0, 0, VR::IS, VM::M1, "Number of Compensators" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0042[] = {
{ 0x0008, 0x0022, 0, VR::DA, VM::M1, "Acquisition Date" },
{ 0x0018, 0x0032, 1, VR::DS, VM::M1, "Energy Window Centerline" },
{ 0x0018, 0x1073, 0, VR::TM, VM::M1, "Radiopharmaceutical Stop Time" },
{ 0x0022, 0x0008, 0, VR::FL, VM::M1, "Cylinder Lens Power" },
{ 0x0028, 0x0002, 0, VR::US, VM::M1, "Samples per Pixel" },
{ 0x003A, 0x0010, 0, VR::UL, VM::M1, "Number of Waveform Samples" },
{ 0x0040, 0xDB07, 1, VR::DT, VM::M1, "Template Local Version" },
{ 0x0070, 0x005A, 0, VR::SQ, VM::M1, "Displayed Area Selection Sequence" },
{ 0x2000, 0x00A8, 0, VR::SQ, VM::M1, "Supported Image Display Formats Sequence" },
{ 0x300A, 0x00E3, 0, VR::SQ, VM::M1, "Compensator Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0043[] = {
{ 0x0008, 0x0023, 0, VR::DA, VM::M1, "Content Date" },
{ 0x0008, 0x1062, 0, VR::SQ, VM::M1, "Physician(s) Reading Study Identification Sequence" },
{ 0x0018, 0x0033, 1, VR::DS, VM::M1TN, "Energy Window Total Width" },
{ 0x0018, 0x1072, 0, VR::TM, VM::M1, "Radiopharmaceutical Start Time" },
{ 0x0022, 0x0009, 0, VR::FL, VM::M1, "Cylinder Axis" },
{ 0x0028, 0x0003, 0, VR::US, VM::M1, "Samples per Pixel Used" },
{ 0x0040, 0xDB06, 1, VR::DT, VM::M1, "Template Version" },
{ 0x3008, 0x00E0, 0, VR::SQ, VM::M1, "Treatment Summary Measured Dose Reference Sequence" },
{ 0x300A, 0x00E2, 0, VR::DS, VM::M1, "Total Compensator Tray Factor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0044[] = {
{ 0x0008, 0x0024, 1, VR::DA, VM::M1, "Overlay Date" },
{ 0x0018, 0x0034, 0, VR::LO, VM::M1, "Intervention Drug Name" },
{ 0x0018, 0x1075, 0, VR::DS, VM::M1, "Radionuclide Half Life" },
{ 0x0020, 0x9245, 0, VR::FL, VM::M1, "Nominal Percentage of Respiratory Phase" },
{ 0x0022, 0x000E, 0, VR::FL, VM::M1, "Degree of Dilation" },
{ 0x0028, 0x0004, 0, VR::CS, VM::M1, "Photometric Interpretation" },
{ 0x0038, 0x0014, 0, VR::SQ, VM::M1, "Issuer of Admission ID Sequence" },
{ 0x0040, 0x9225, 0, VR::FD, VM::M1, "Real World Value Slope" },
{ 0x300A, 0x00E5, 0, VR::SH, VM::M1, "Compensator ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0045[] = {
{ 0x0008, 0x0025, 1, VR::DA, VM::M1, "Curve Date" },
{ 0x0018, 0x0035, 0, VR::TM, VM::M1, "Intervention Drug Start Time" },
{ 0x0018, 0x1074, 0, VR::DS, VM::M1, "Radionuclide Total Dose" },
{ 0x0020, 0x000D, 0, VR::UI, VM::M1, "Study Instance UID" },
{ 0x0028, 0x0005, 1, VR::US, VM::M1, "Image Dimensions" },
{ 0x0040, 0x9224, 0, VR::FD, VM::M1, "Real World Value Intercept" },
{ 0x0040, 0xDB00, 0, VR::CS, VM::M1, "Template Identifier" },
{ 0x300A, 0x00E4, 0, VR::IS, VM::M1, "Compensator Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0046[] = {
{ 0x0018, 0x0036, 0, VR::SQ, VM::M1, "Intervention Sequence" },
{ 0x0018, 0x1077, 0, VR::DS, VM::M1, "Radiopharmaceutical Specific Activity" },
{ 0x0020, 0x000E, 0, VR::UI, VM::M1, "Series Instance UID" },
{ 0x0020, 0x9247, 0, VR::CS, VM::M1, "Starting Respiratory Phase" },
{ 0x0022, 0x000C, 0, VR::FL, VM::M1, "Horizontal Field of View" },
{ 0x0028, 0x0006, 0, VR::US, VM::M1, "Planar Configuration" },
{ 0x0038, 0x0016, 0, VR::LO, VM::M1, "Route of Admissions" },
{ 0x0068, 0x65D0, 0, VR::FD, VM::M6, "3D Line Coordinates" },
{ 0x300A, 0x00E7, 0, VR::IS, VM::M1, "Compensator Rows" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0047[] = {
{ 0x0018, 0x0037, 1, VR::CS, VM::M1, "Therapy Type" },
{ 0x0018, 0x1076, 0, VR::DS, VM::M1, "Radionuclide Positron Fraction" },
{ 0x0020, 0x9246, 0, VR::FL, VM::M1, "Starting Respiratory Amplitude" },
{ 0x0022, 0x000D, 0, VR::CS, VM::M1, "Pupil Dilated" },
{ 0x300A, 0x00E6, 0, VR::DS, VM::M1, "Source to Compensator Tray Distance" },
{ 0x300C, 0x00E0, 0, VR::IS, VM::M1, "Referenced Block Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0048[] = {
{ 0x0010, 0x0020, 0, VR::LO, VM::M1, "Patient ID" },
{ 0x0014, 0x0024, 0, VR::ST, VM::M1TN, "Component Reference System" },
{ 0x0018, 0x0028, 0, VR::DS, VM::M1, "Intervention Drug Dose" },
{ 0x0018, 0x1069, 0, VR::DS, VM::M1, "Trigger Time Offset" },
{ 0x0020, 0x0010, 0, VR::SH, VM::M1, "Study ID" },
{ 0x0022, 0x0012, 0, VR::FL, VM::M1, "Stereo Horizontal Pixel Offset" },
{ 0x0022, 0x1053, 0, VR::FL, VM::M1, "IOL Power" },
{ 0x0038, 0x0008, 0, VR::CS, VM::M1, "Visit Status ID" },
{ 0x0046, 0x0076, 0, VR::FD, VM::M1, "Keratometric Power" },
{ 0x0070, 0x0040, 1, VR::IS, VM::M1, "Image Rotation (Retired)" },
{ 0x0400, 0x0020, 0, VR::AT, VM::M1TN, "Data Elements Signed" },
{ 0x300A, 0x00F9, 0, VR::LO, VM::M1, "Accessory Code" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0049[] = {
{ 0x0010, 0x0021, 0, VR::LO, VM::M1, "Issuer of Patient ID" },
{ 0x0010, 0x1060, 0, VR::PN, VM::M1, "Patient's Mother's Birth Name" },
{ 0x0014, 0x0025, 0, VR::ST, VM::M1TN, "Component Manufacturing Procedure" },
{ 0x0018, 0x0029, 0, VR::SQ, VM::M1, "Intervention Drug Code Sequence" },
{ 0x0018, 0x1068, 0, VR::DS, VM::M1, "Multiplex Group Time Offset" },
{ 0x0018, 0x9260, 0, VR::SQ, VM::M1, "ASL Slab Sequence" },
{ 0x0020, 0x0011, 0, VR::IS, VM::M1, "Series Number" },
{ 0x0022, 0x0013, 0, VR::FL, VM::M1, "Stereo Vertical Pixel Offset" },
{ 0x0046, 0x0077, 0, VR::FD, VM::M1, "Keratometric Axis" },
{ 0x0070, 0x0041, 0, VR::CS, VM::M1, "Image Horizontal Flip" },
{ 0x0074, 0x1004, 0, VR::DS, VM::M1, "Procedure Step Progress" },
{ 0x300A, 0x00F8, 0, VR::CS, VM::M1, "Block Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0050[] = {
{ 0x0010, 0x0022, 0, VR::CS, VM::M1, "Type of Patient ID" },
{ 0x0012, 0x0020, 0, VR::LO, VM::M1, "Clinical Trial Protocol ID" },
{ 0x0018, 0x002A, 0, VR::SQ, VM::M1, "Additional Drug Sequence" },
{ 0x0020, 0x0012, 0, VR::IS, VM::M1, "Acquisition Number" },
{ 0x0022, 0x0010, 0, VR::FL, VM::M1, "Stereo Baseline Angle" },
{ 0x0024, 0x0016, 0, VR::SQ, VM::M1, "Screening Test Mode Code Sequence" },
{ 0x0032, 0x1041, 1, VR::TM, VM::M1, "Study Arrival Time" },
{ 0x0046, 0x0074, 0, VR::SQ, VM::M1, "Steep Keratometric Axis Sequence" },
{ 0x0070, 0x0042, 0, VR::US, VM::M1, "Image Rotation" },
{ 0x0072, 0x0040, 0, VR::LO, VM::M1, "Image Set Label" },
{ 0x300A, 0x00FB, 0, VR::CS, VM::M1, "Block Mounting Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0051[] = {
{ 0x0012, 0x0021, 0, VR::LO, VM::M1, "Clinical Trial Protocol Name" },
{ 0x0018, 0x106A, 0, VR::CS, VM::M1, "Synchronization Trigger" },
{ 0x0020, 0x0013, 0, VR::IS, VM::M1, "Instance Number" },
{ 0x0022, 0x0011, 0, VR::FL, VM::M1, "Stereo Baseline Displacement" },
{ 0x0022, 0x1050, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Sequence" },
{ 0x0032, 0x1040, 1, VR::DA, VM::M1, "Study Arrival Date" },
{ 0x0046, 0x0075, 0, VR::FD, VM::M1, "Radius of Curvature" },
{ 0x0074, 0x1006, 0, VR::ST, VM::M1, "Procedure Step Progress Description" },
{ 0x300A, 0x00FA, 0, VR::CS, VM::M1, "Block Divergence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0052[] = {
{ 0x0010, 0x0024, 0, VR::SQ, VM::M1, "Issuer of Patient ID Qualifiers Sequence" },
{ 0x0020, 0x0014, 1, VR::IS, VM::M1, "Isotope Number" },
{ 0x0022, 0x0016, 0, VR::SQ, VM::M1, "Illumination Type Code Sequence" },
{ 0x0024, 0x0010, 0, VR::FL, VM::M1, "Visual Field Horizontal Extent" },
{ 0x0054, 0x0060, 0, VR::US, VM::M1TN, "R-R Interval Vector" },
{ 0x2010, 0x00A6, 0, VR::CS, VM::M1, "Default Magnification Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0053[] = {
{ 0x0018, 0x106C, 0, VR::US, VM::M2, "Synchronization Channel" },
{ 0x0020, 0x0015, 1, VR::IS, VM::M1, "Phase Number" },
{ 0x0022, 0x0017, 0, VR::SQ, VM::M1, "Light Path Filter Type Stack Code Sequence" },
{ 0x0024, 0x0011, 0, VR::FL, VM::M1, "Visual Field Vertical Extent" },
{ 0x0054, 0x0061, 0, VR::US, VM::M1, "Number of R-R Intervals" },
{ 0x0074, 0x1000, 0, VR::CS, VM::M1, "Procedure Step State" },
{ 0x2010, 0x00A7, 0, VR::CS, VM::M1TN, "Other Magnification Types Available" },
{ 0x300A, 0x00FC, 0, VR::IS, VM::M1, "Block Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0054[] = {
{ 0x0020, 0x0016, 1, VR::IS, VM::M1, "Interval Number" },
{ 0x0022, 0x0014, 0, VR::FL, VM::M1, "Stereo Rotation" },
{ 0x0024, 0x0012, 0, VR::CS, VM::M1, "Visual Field Shape" },
{ 0x0046, 0x0070, 0, VR::SQ, VM::M1, "Keratometry Right Eye Sequence" },
{ 0x0054, 0x0062, 0, VR::SQ, VM::M1, "Gated Information Sequence" },
{ 0x0076, 0x0040, 0, VR::SQ, VM::M1, "Component Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0055[] = {
{ 0x0014, 0x0023, 0, VR::ST, VM::M1TN, "CAD File Format" },
{ 0x0018, 0x106E, 0, VR::UL, VM::M1, "Trigger Sample Position" },
{ 0x0020, 0x0017, 1, VR::IS, VM::M1, "Time Slot Number" },
{ 0x0022, 0x0015, 0, VR::SQ, VM::M1, "Acquisition Device Type Code Sequence" },
{ 0x0022, 0x1054, 0, VR::FL, VM::M1, "Predicted Refractive Error" },
{ 0x0046, 0x0071, 0, VR::SQ, VM::M1, "Keratometry Left Eye Sequence" },
{ 0x0054, 0x0063, 0, VR::SQ, VM::M1, "Data Information Sequence" },
{ 0x0074, 0x1002, 0, VR::SQ, VM::M1, "Procedure Step Progress Information Sequence" },
{ 0x300A, 0x00FE, 0, VR::LO, VM::M1, "Block Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0056[] = {
{ 0x0008, 0x0030, 0, VR::TM, VM::M1, "Study Time" },
{ 0x0018, 0x0020, 0, VR::CS, VM::M1TN, "Scanning Sequence" },
{ 0x0018, 0x1061, 0, VR::LO, VM::M1, "Trigger Source or Type" },
{ 0x0020, 0x0018, 1, VR::IS, VM::M1, "Angle Number" },
{ 0x0020, 0x9251, 0, VR::FD, VM::M1, "R-R Interval Time Nominal" },
{ 0x0022, 0x001A, 0, VR::SQ, VM::M1, "Channel Description Code Sequence" },
{ 0x0028, 0x0010, 0, VR::US, VM::M1, "Rows" },
{ 0x0028, 0x0400, 1, VR::LO, VM::M1, "Transform Label" },
{ 0x0028, 0x0400, 1, VR::US, VM::M1, "Rows For Nth Order Coefficients" },
{ 0x0028, 0x1051, 0, VR::DS, VM::M1TN, "Window Width" },
{ 0x0032, 0x000A, 1, VR::CS, VM::M1, "Study Status ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0057[] = {
{ 0x0008, 0x0031, 0, VR::TM, VM::M1, "Series Time" },
{ 0x0008, 0x1070, 0, VR::PN, VM::M1TN, "Operators' Name" },
{ 0x0018, 0x0021, 0, VR::CS, VM::M1TN, "Sequence Variant" },
{ 0x0018, 0x1060, 0, VR::DS, VM::M1, "Trigger Time" },
{ 0x0018, 0x1470, 0, VR::DS, VM::M1, "Tomo Angle" },
{ 0x0020, 0x0019, 0, VR::IS, VM::M1, "Item Number" },
{ 0x0020, 0x9250, 0, VR::CS, VM::M1, "Respiratory Trigger Type" },
{ 0x0022, 0x001B, 0, VR::SQ, VM::M1, "Refractive State Sequence" },
{ 0x0028, 0x0011, 0, VR::US, VM::M1, "Columns" },
{ 0x0028, 0x0401, 1, VR::LO, VM::M1, "Transform Version Number" },
{ 0x0028, 0x0401, 1, VR::US, VM::M1, "Columns For Nth Order Coefficients" },
{ 0x0028, 0x1050, 0, VR::DS, VM::M1TN, "Window Center" },
{ 0x0074, 0x100c, 0, VR::LO, VM::M1, "Contact Display Name" },
{ 0x3008, 0x00F2, 0, VR::SQ, VM::M1, "Recorded Range Shifter Sequence" },
{ 0x300A, 0x00F0, 0, VR::IS, VM::M1, "Number of Blocks" },
{ 0x300C, 0x00F6, 0, VR::IS, VM::M1, "Referenced Stop Control Point Index" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0058[] = {
{ 0x0008, 0x0032, 0, VR::TM, VM::M1, "Acquisition Time" },
{ 0x0018, 0x0022, 0, VR::CS, VM::M1TN, "Scan Options" },
{ 0x0018, 0x1063, 0, VR::DS, VM::M1, "Frame Time" },
{ 0x0020, 0x9253, 0, VR::SQ, VM::M1, "Respiratory Synchronization Sequence" },
{ 0x0022, 0x0018, 0, VR::SQ, VM::M1, "Image Path Filter Type Stack Code Sequence" },
{ 0x0022, 0x1059, 0, VR::FL, VM::M1, "Ophthalmic Axial Length Velocity" },
{ 0x0028, 0x0012, 1, VR::US, VM::M1, "Planes" },
{ 0x0028, 0x0402, 1, VR::US, VM::M1, "Number of Transform Steps" },
{ 0x0028, 0x0402, 1, VR::LO, VM::M1TN, "Coefficient Coding" },
{ 0x0028, 0x1053, 0, VR::DS, VM::M1, "Rescale Slope" },
{ 0x2010, 0x00A8, 0, VR::CS, VM::M1, "Default Smoothing Type" },
{ 0x300A, 0x00F3, 0, VR::FL, VM::M1, "Total Block Tray Water-Equivalent Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0059[] = {
{ 0x0008, 0x0033, 0, VR::TM, VM::M1, "Content Time" },
{ 0x0008, 0x1072, 0, VR::SQ, VM::M1, "Operator Identification Sequence" },
{ 0x0018, 0x0023, 0, VR::CS, VM::M1, "MR Acquisition Type" },
{ 0x0018, 0x1062, 0, VR::IS, VM::M1, "Nominal Interval" },
{ 0x0020, 0x9252, 0, VR::FD, VM::M1, "Actual Cardiac Trigger Delay Time" },
{ 0x0022, 0x0019, 0, VR::SQ, VM::M1, "Lenses Code Sequence" },
{ 0x0028, 0x0403, 1, VR::LO, VM::M1TN, "Sequence of Compressed Data" },
{ 0x0028, 0x0403, 1, VR::AT, VM::M1TN, "Coefficient Coding Pointers" },
{ 0x0028, 0x1052, 0, VR::DS, VM::M1, "Rescale Intercept" },
{ 0x0074, 0x100e, 0, VR::SQ, VM::M1, "Procedure Step Discontinuation Reason Code Sequence" },
{ 0x2010, 0x00A9, 0, VR::CS, VM::M1TN, "Other Smoothing Types Available" },
{ 0x3008, 0x00F0, 0, VR::SQ, VM::M1, "Recorded Snout Sequence" },
{ 0x300A, 0x00F2, 0, VR::DS, VM::M1, "Total Block Tray Factor" },
{ 0x300C, 0x00F4, 0, VR::IS, VM::M1, "Referenced Start Control Point Index" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0060[] = {
{ 0x0008, 0x0034, 1, VR::TM, VM::M1, "Overlay Time" },
{ 0x0014, 0x0028, 0, VR::ST, VM::M1TN, "Component Manufacturer" },
{ 0x0018, 0x0024, 0, VR::SH, VM::M1, "Sequence Name" },
{ 0x0018, 0x1065, 0, VR::DS, VM::M1TN, "Frame Time Vector" },
{ 0x0020, 0x9255, 0, VR::FD, VM::M1, "Nominal Respiratory Trigger Delay Time" },
{ 0x0022, 0x001E, 0, VR::FL, VM::M1, "Camera Angle of View" },
{ 0x0024, 0x0018, 0, VR::FL, VM::M1, "Maximum Stimulus Luminance" },
{ 0x0028, 0x0014, 0, VR::US, VM::M1, "Ultrasound Color Data Present" },
{ 0x0028, 0x0404, 1, VR::AT, VM::M1TN, "Details of Coefficients" },
{ 0x0028, 0x1055, 0, VR::LO, VM::M1TN, "Window Center & Width Explanation" },
{ 0x0038, 0x0004, 0, VR::SQ, VM::M1, "Referenced Patient Alias Sequence" },
{ 0x300A, 0x00F5, 0, VR::SH, VM::M1, "Block Tray ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0061[] = {
{ 0x0008, 0x0035, 1, VR::TM, VM::M1, "Curve Time" },
{ 0x0018, 0x0025, 0, VR::CS, VM::M1, "Angio Flag" },
{ 0x0018, 0x1064, 0, VR::LO, VM::M1, "Cardiac Framing Type" },
{ 0x0020, 0x9254, 0, VR::FD, VM::M1, "Respiratory Interval Time" },
{ 0x0028, 0x1054, 0, VR::LO, VM::M1, "Rescale Type" },
{ 0x0074, 0x1008, 0, VR::SQ, VM::M1, "Procedure Step Communications URI Sequence" },
{ 0x3008, 0x00F6, 0, VR::SQ, VM::M1, "Recorded Range Modulator Sequence" },
{ 0x300A, 0x00F4, 0, VR::SQ, VM::M1, "Block Sequence" },
{ 0x300C, 0x00F2, 0, VR::SQ, VM::M1, "Referenced Control Point Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0062[] = {
{ 0x0018, 0x0026, 0, VR::SQ, VM::M1, "Intervention Drug Information Sequence" },
{ 0x0018, 0x1067, 0, VR::DS, VM::M1, "Image Trigger Delay" },
{ 0x0020, 0x9257, 0, VR::FD, VM::M1, "Actual Respiratory Trigger Delay Time" },
{ 0x0022, 0x001C, 0, VR::SQ, VM::M1, "Mydriatic Agent Code Sequence" },
{ 0x0028, 0x6190, 0, VR::ST, VM::M1, "Mask Operation Explanation" },
{ 0x0032, 0x000C, 1, VR::CS, VM::M1, "Study Priority ID" },
{ 0x003A, 0x0004, 0, VR::CS, VM::M1, "Waveform Originality" },
{ 0x300A, 0x00F7, 0, VR::FL, VM::M1, "Isocenter to Block Tray Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0063[] = {
{ 0x0018, 0x0027, 0, VR::TM, VM::M1, "Intervention Drug Stop Time" },
{ 0x0018, 0x1066, 0, VR::DS, VM::M1, "Frame Delay" },
{ 0x0020, 0x9256, 0, VR::FD, VM::M1, "Respiratory Trigger Delay Threshold" },
{ 0x0022, 0x001D, 0, VR::SQ, VM::M1, "Relative Image Position Code Sequence" },
{ 0x0028, 0x1056, 0, VR::CS, VM::M1, "VOI LUT Function" },
{ 0x003A, 0x0005, 0, VR::US, VM::M1, "Number of Waveform Channels" },
{ 0x0074, 0x100a, 0, VR::ST, VM::M1, "Contact URI" },
{ 0x3008, 0x00F4, 0, VR::SQ, VM::M1, "Recorded Lateral Spreading Device Sequence" },
{ 0x300A, 0x00F6, 0, VR::DS, VM::M1, "Source to Block Tray Distance" },
{ 0x300C, 0x00F0, 0, VR::IS, VM::M1, "Referenced Control Point Index" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0064[] = {
{ 0x0010, 0x1010, 0, VR::AS, VM::M1, "Patient's Age" },
{ 0x0018, 0x1018, 0, VR::LO, VM::M1, "Secondary Capture Device Manufacturer's Model Name" },
{ 0x0020, 0x1020, 1, VR::LO, VM::M1TN, "Reference" },
{ 0x0020, 0x9228, 0, VR::UL, VM::M1, "Concatenation Frame Offset Number" },
{ 0x0024, 0x0065, 0, VR::SQ, VM::M1, "Age Corrected Sensitivity Deviation Algorithm Sequence" },
{ 0x0028, 0x0069, 1, VR::US, VM::M1, "Bits Grouped" },
{ 0x0032, 0x1032, 0, VR::PN, VM::M1, "Requesting Physician" },
{ 0x0040, 0x0001, 0, VR::AE, VM::M1TN, "Scheduled Station AE Title" },
{ 0x0052, 0x0013, 0, VR::FD, VM::M1, "Catheter Rotational Rate" },
{ 0x0054, 0x0015, 0, VR::DS, VM::M1, "Energy Window Upper Limit" },
{ 0x0066, 0x0027, 0, VR::SQ, VM::M1, "Triangle Fan Sequence" },
{ 0x1000, 0x0000, 1, VR::US, VM::M3, "Escape Triplet" },
{ 0x3006, 0x0084, 0, VR::IS, VM::M1, "Referenced ROI Number" },
{ 0x300A, 0x0088, 0, VR::FL, VM::M1, "Beam Dose Point Depth" },
{ 0x5000, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value" },
{ 0x5002, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 2" },
{ 0x5010, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 9" },
{ 0x5014, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 11" },
{ 0x5016, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0065[] = {
{ 0x0010, 0x0050, 0, VR::SQ, VM::M1, "Patient's Insurance Plan Code Sequence" },
{ 0x0014, 0x0054, 0, VR::DS, VM::M1, "Outer Diameter" },
{ 0x0018, 0x1019, 0, VR::LO, VM::M1TN, "Secondary Capture Device Software Versions" },
{ 0x0018, 0x9601, 0, VR::SQ, VM::M1, "Diffusion b-matrix Sequence" },
{ 0x0020, 0x0060, 0, VR::CS, VM::M1, "Laterality" },
{ 0x0024, 0x0064, 0, VR::SQ, VM::M1, "Results Normals Sequence" },
{ 0x0028, 0x0068, 1, VR::US, VM::M1, "Repeat Interval" },
{ 0x0032, 0x1033, 0, VR::LO, VM::M1, "Requesting Service" },
{ 0x0044, 0x0004, 0, VR::DT, VM::M1, "Approval Status DateTime" },
{ 0x0048, 0x0008, 0, VR::SQ, VM::M1, "Total Pixel Matrix Origin Sequence" },
{ 0x0050, 0x0010, 0, VR::SQ, VM::M1, "Device Sequence" },
{ 0x0052, 0x0012, 0, VR::US, VM::M1, "A-lines Per Frame" },
{ 0x0054, 0x0014, 0, VR::DS, VM::M1, "Energy Window Lower Limit" },
{ 0x0066, 0x0026, 0, VR::SQ, VM::M1, "Triangle Strip Sequence" },
{ 0x0072, 0x0032, 0, VR::US, VM::M1, "Image Set Number" },
{ 0x0072, 0x0422, 0, VR::SQ, VM::M1, "Structured Display Image Box Sequence" },
{ 0x0076, 0x0036, 0, VR::CS, VM::M1, "Exclusive Component Type" },
{ 0x1000, 0x0001, 1, VR::US, VM::M3, "Run Length Triplet" },
{ 0x2040, 0x0082, 1, VR::CS, VM::M1, "Overlay Background Density" },
{ 0x3006, 0x0085, 0, VR::SH, VM::M1, "ROI Observation Label" },
{ 0x300A, 0x0089, 0, VR::FL, VM::M1, "Beam Dose Point Equivalent Depth" },
{ 0x5000, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value" },
{ 0x5006, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0066[] = {
{ 0x0012, 0x0051, 0, VR::ST, VM::M1, "Clinical Trial Time Point Description" },
{ 0x0018, 0x101A, 1, VR::LO, VM::M1TN, "Hardcopy Device Software Version" },
{ 0x0018, 0x9602, 0, VR::FD, VM::M1, "Diffusion b-value XX" },
{ 0x0024, 0x0067, 0, VR::SQ, VM::M1, "Generalized Defect Sensitivity Deviation Algorithm Sequence" },
{ 0x0032, 0x1030, 1, VR::LO, VM::M1, "Reason for Study" },
{ 0x0040, 0x0003, 0, VR::TM, VM::M1, "Scheduled Procedure Step Start Time" },
{ 0x0044, 0x0007, 0, VR::SQ, VM::M1, "Product Type Code Sequence" },
{ 0x0050, 0x0013, 0, VR::FD, VM::M1, "Container Component Thickness" },
{ 0x0052, 0x0011, 0, VR::FD, VM::M1, "A-line Rate" },
{ 0x0054, 0x0017, 0, VR::IS, VM::M1, "Residual Syringe Counts" },
{ 0x0066, 0x0025, 0, VR::OW, VM::M1, "Vertex Point Index List" },
{ 0x0072, 0x0421, 0, VR::US, VM::M3, "Empty Image Box CIELab Value" },
{ 0x1000, 0x0002, 1, VR::US, VM::M1, "Huffman Table Size" },
{ 0x3006, 0x0086, 0, VR::SQ, VM::M1, "RT ROI Identification Code Sequence" },
{ 0x300A, 0x008A, 0, VR::FL, VM::M1, "Beam Dose Point SSD" },
{ 0x5000, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range" },
{ 0x5002, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 2" },
{ 0x5012, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 10" },
{ 0x5014, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 11" },
{ 0x5016, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0067[] = {
{ 0x0012, 0x0050, 0, VR::LO, VM::M1, "Clinical Trial Time Point ID" },
{ 0x0014, 0x0056, 0, VR::DS, VM::M1, "Inner Diameter" },
{ 0x0018, 0x101B, 1, VR::LO, VM::M1, "Hardcopy Device Manufacturer's Model Name" },
{ 0x0018, 0x9603, 0, VR::FD, VM::M1, "Diffusion b-value XY" },
{ 0x0020, 0x0062, 0, VR::CS, VM::M1, "Image Laterality" },
{ 0x0024, 0x0066, 0, VR::FL, VM::M1, "Global Deviation From Normal" },
{ 0x0032, 0x1031, 0, VR::SQ, VM::M1, "Requesting Physician Identification Sequence" },
{ 0x0040, 0x0002, 0, VR::DA, VM::M1, "Scheduled Procedure Step Start Date" },
{ 0x0050, 0x0012, 0, VR::SQ, VM::M1, "Container Component Type Code Sequence" },
{ 0x0054, 0x0016, 0, VR::SQ, VM::M1, "Radiopharmaceutical Information Sequence" },
{ 0x0066, 0x0024, 0, VR::OW, VM::M1, "Edge Point Index List" },
{ 0x0072, 0x0030, 0, VR::SQ, VM::M1, "Time Based Image Sets Sequence" },
{ 0x0072, 0x0420, 0, VR::US, VM::M3, "Structured Display Background CIELab Value" },
{ 0x0076, 0x0034, 0, VR::CS, VM::M1, "Component Type Code Sequence" },
{ 0x1000, 0x0003, 1, VR::US, VM::M3, "Huffman Table Triplet" },
{ 0x2040, 0x0080, 1, VR::CS, VM::M1, "Overlay Foreground Density" },
{ 0x5002, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 2" },
{ 0x5004, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0068[] = {
{ 0x0014, 0x1010, 0, VR::ST, VM::M1, "Actual Environmental Conditions" },
{ 0x0018, 0x9214, 0, VR::CS, VM::M1, "Respiratory Cycle Position" },
{ 0x0018, 0x9604, 0, VR::FD, VM::M1, "Diffusion b-value XZ" },
{ 0x0024, 0x0061, 0, VR::CS, VM::M1, "Excessive False Positives Data Flag" },
{ 0x0040, 0x0005, 0, VR::TM, VM::M1, "Scheduled Procedure Step End Time" },
{ 0x0044, 0x0001, 0, VR::ST, VM::M1, "Product Package Identifier" },
{ 0x0050, 0x0015, 0, VR::FD, VM::M1, "Container Component Width" },
{ 0x0054, 0x0011, 0, VR::US, VM::M1, "Number of Energy Windows" },
{ 0x0066, 0x0023, 0, VR::OW, VM::M1, "Triangle Point Index List" },
{ 0x0072, 0x0427, 0, VR::SQ, VM::M1, "Referenced First Frame Sequence" },
{ 0x1000, 0x0004, 1, VR::US, VM::M1, "Shift Table Size" },
{ 0x3006, 0x0080, 0, VR::SQ, VM::M1, "RT ROI Observations Sequence" },
{ 0x5004, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 3" },
{ 0x5006, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 4" },
{ 0x5010, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 9" },
{ 0x5012, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 10" },
{ 0x5014, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 11" },
{ 0x5400, 0x0110, 0, VR::OX, VM::M1, "Channel Minimum Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0069[] = {
{ 0x0008, 0x9205, 0, VR::CS, VM::M1, "Pixel Presentation" },
{ 0x0014, 0x0050, 0, VR::CS, VM::M1, "Component Shape" },
{ 0x0018, 0x9605, 0, VR::FD, VM::M1, "Diffusion b-value YY" },
{ 0x0024, 0x0060, 0, VR::US, VM::M1, "False Positives Quantity" },
{ 0x0040, 0x0004, 0, VR::DA, VM::M1, "Scheduled Procedure Step End Date" },
{ 0x0050, 0x0014, 0, VR::DS, VM::M1, "Device Length" },
{ 0x0052, 0x0016, 0, VR::SQ, VM::M1, "Mode of Percutaneous Access Sequence" },
{ 0x0054, 0x0010, 0, VR::US, VM::M1TN, "Energy Window Vector" },
{ 0x0054, 0x0400, 0, VR::SH, VM::M1, "Image ID" },
{ 0x0076, 0x0032, 0, VR::SQ, VM::M1, "Component Types Sequence" },
{ 0x1000, 0x0005, 1, VR::US, VM::M3, "Shift Table Triplet" },
{ 0x5002, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 2" },
{ 0x5004, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0070[] = {
{ 0x0008, 0x9206, 0, VR::CS, VM::M1, "Volumetric Properties" },
{ 0x0018, 0x9606, 0, VR::FD, VM::M1, "Diffusion b-value YZ" },
{ 0x0022, 0x1024, 0, VR::SQ, VM::M1, "Lens Status Code Sequence" },
{ 0x0024, 0x0063, 0, VR::CS, VM::M1, "Visual Field Test Normals Flag" },
{ 0x0032, 0x1034, 0, VR::SQ, VM::M1, "Requesting Service Code Sequence" },
{ 0x0040, 0x0007, 0, VR::LO, VM::M1, "Scheduled Procedure Step Description" },
{ 0x0044, 0x0003, 0, VR::LT, VM::M1, "Approval Status Further Description" },
{ 0x0050, 0x0017, 0, VR::CS, VM::M1, "Device Diameter Units" },
{ 0x0054, 0x0013, 0, VR::SQ, VM::M1, "Energy Window Range Sequence" },
{ 0x0066, 0x0021, 0, VR::OF, VM::M1, "Vector Coordinate Data" },
{ 0x3006, 0x0082, 0, VR::IS, VM::M1, "Observation Number" },
{ 0x5004, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 3" },
{ 0x5006, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 4" },
{ 0x5010, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 9" },
{ 0x5012, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 10" },
{ 0x5016, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 12" },
{ 0x5400, 0x0112, 0, VR::OX, VM::M1, "Channel Maximum Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0071[] = {
{ 0x0008, 0x9207, 0, VR::CS, VM::M1, "Volume Based Calculation Technique" },
{ 0x0014, 0x0052, 0, VR::CS, VM::M1, "Curvature Type" },
{ 0x0018, 0x9217, 0, VR::FD, VM::M1, "Velocity Encoding Maximum Value" },
{ 0x0018, 0x9607, 0, VR::FD, VM::M1, "Diffusion b-value ZZ" },
{ 0x0022, 0x1025, 0, VR::SQ, VM::M1, "Vitreous Status Code Sequence" },
{ 0x0024, 0x0062, 0, VR::CS, VM::M1, "Excessive False Positives" },
{ 0x0040, 0x0006, 0, VR::PN, VM::M1, "Scheduled Performing Physician's Name" },
{ 0x0044, 0x0002, 0, VR::CS, VM::M1, "Substance Administration Approval" },
{ 0x0050, 0x0016, 0, VR::DS, VM::M1, "Device Diameter" },
{ 0x0052, 0x0014, 0, VR::FD, VM::M1, "A-line Pixel Spacing" },
{ 0x0054, 0x0012, 0, VR::SQ, VM::M1, "Energy Window Information Sequence" },
{ 0x0066, 0x0020, 0, VR::FL, VM::M1TN, "Vector Accuracy" },
{ 0x0072, 0x0034, 0, VR::CS, VM::M1, "Image Set Selector Category" },
{ 0x0072, 0x0424, 0, VR::SQ, VM::M1, "Structured Display Text Box Sequence" },
{ 0x0076, 0x0030, 0, VR::LO, VM::M1, "Surgical Technique" },
{ 0x5000, 0x0103, 1, VR::US, VM::M1, "Data Value Representation" },
{ 0x5006, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0072[] = {
{ 0x0008, 0x0041, 1, VR::LO, VM::M1, "Data Set Subtype" },
{ 0x0008, 0x1000, 1, VR::AE, VM::M1, "Network ID" },
{ 0x0008, 0x9208, 0, VR::CS, VM::M1, "Complex Image Component" },
{ 0x0018, 0x1010, 0, VR::LO, VM::M1, "Secondary Capture Device ID" },
{ 0x0018, 0x1400, 0, VR::LO, VM::M1, "Acquisition Device Processing Description" },
{ 0x0018, 0x9218, 0, VR::FD, VM::M1, "Tag Spacing Second Dimension" },
{ 0x0028, 0x0061, 1, VR::SH, VM::M1, "Compression Originator" },
{ 0x0040, 0x0009, 0, VR::SH, VM::M1, "Scheduled Procedure Step ID" },
{ 0x0048, 0x0001, 0, VR::FL, VM::M1, "Imaged Volume Width" },
{ 0x0050, 0x0019, 0, VR::DS, VM::M1, "Inter-Marker Distance" },
{ 0x0066, 0x002F, 0, VR::SQ, VM::M1, "Algorithm Family Code Sequence" },
{ 0x3008, 0x0082, 0, VR::IS, VM::M1, "Referenced Measured Dose Reference Number" },
{ 0x300A, 0x0080, 0, VR::IS, VM::M1, "Number of Beams" },
{ 0x5008, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 5" },
{ 0x500A, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 6" },
{ 0x5018, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 13" },
{ 0x501C, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 15" },
{ 0x501E, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0073[] = {
{ 0x0008, 0x0040, 1, VR::US, VM::M1, "Data Set Type" },
{ 0x0008, 0x9209, 0, VR::CS, VM::M1, "Acquisition Contrast" },
{ 0x0018, 0x0050, 0, VR::DS, VM::M1, "Slice Thickness" },
{ 0x0018, 0x1011, 1, VR::LO, VM::M1, "Hardcopy Creation Device ID" },
{ 0x0018, 0x1401, 0, VR::LO, VM::M1, "Acquisition Device Processing Code" },
{ 0x0018, 0x9219, 0, VR::SS, VM::M1, "Tag Angle Second Axis" },
{ 0x0020, 0x9221, 0, VR::SQ, VM::M1, "Dimension Organization Sequence" },
{ 0x0028, 0x0060, 1, VR::CS, VM::M1, "Compression Code" },
{ 0x0040, 0x0008, 0, VR::SQ, VM::M1, "Scheduled Protocol Code Sequence" },
{ 0x0050, 0x0018, 0, VR::DS, VM::M1, "Device Volume" },
{ 0x0066, 0x002E, 0, VR::SQ, VM::M1, "Segment Surface Source Instance Sequence" },
{ 0x0072, 0x003A, 0, VR::CS, VM::M1, "Relative Time Units" },
{ 0x5008, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 5" },
{ 0x500E, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0074[] = {
{ 0x0018, 0x1012, 0, VR::DA, VM::M1, "Date of Secondary Capture" },
{ 0x0018, 0x1402, 0, VR::CS, VM::M1, "Cassette Orientation" },
{ 0x0020, 0x9222, 0, VR::SQ, VM::M1, "Dimension Index Sequence" },
{ 0x0022, 0x1028, 0, VR::SQ, VM::M1, "IOL Formula Code Sequence" },
{ 0x0028, 0x0063, 1, VR::SH, VM::M1, "Compression Description" },
{ 0x0040, 0x000B, 0, VR::SQ, VM::M1, "Scheduled Performing Physician Identification Sequence" },
{ 0x0048, 0x0003, 0, VR::FL, VM::M1, "Imaged Volume Depth" },
{ 0x0050, 0x001B, 0, VR::LO, VM::M1, "Container Component ID" },
{ 0x0066, 0x002D, 0, VR::SQ, VM::M1, "Segment Surface Generation Algorithm Identification Sequence" },
{ 0x3008, 0x0080, 0, VR::SQ, VM::M1, "Referenced Measured Dose Reference Sequence" },
{ 0x300A, 0x0082, 0, VR::DS, VM::M3, "Beam Dose Specification Point" },
{ 0x5008, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 5" },
{ 0x500A, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 6" },
{ 0x501A, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 14" },
{ 0x501C, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 15" },
{ 0x501E, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0075[] = {
{ 0x0008, 0x0042, 1, VR::CS, VM::M1, "Nuclear Medicine Series Type" },
{ 0x0018, 0x1403, 0, VR::CS, VM::M1, "Cassette Size" },
{ 0x0022, 0x1029, 0, VR::LO, VM::M1, "IOL Formula Detail" },
{ 0x0028, 0x0062, 1, VR::LO, VM::M1, "Compression Label" },
{ 0x0040, 0x000A, 0, VR::SQ, VM::M1, "Stage Code Sequence" },
{ 0x0048, 0x0002, 0, VR::FL, VM::M1, "Imaged Volume Height" },
{ 0x0050, 0x001A, 0, VR::CS, VM::M1, "Container Component Material" },
{ 0x0066, 0x002C, 0, VR::UL, VM::M1, "Referenced Surface Number" },
{ 0x0072, 0x0038, 0, VR::US, VM::M2, "Relative Time" },
{ 0x500A, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 6" },
{ 0x500C, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0076[] = {
{ 0x0018, 0x1014, 0, VR::TM, VM::M1, "Time of Secondary Capture" },
{ 0x0018, 0x1404, 0, VR::US, VM::M1, "Exposures on Plate" },
{ 0x0024, 0x0069, 0, VR::LO, VM::M1, "Patient Reliability Indicator" },
{ 0x0028, 0x0065, 1, VR::CS, VM::M1TN, "Compression Sequence" },
{ 0x0044, 0x0009, 0, VR::LT, VM::M1, "Product Description" },
{ 0x0050, 0x001D, 0, VR::FD, VM::M1, "Container Component Diameter" },
{ 0x0066, 0x002B, 0, VR::SQ, VM::M1, "Referenced Surface Sequence" },
{ 0x3006, 0x0088, 0, VR::ST, VM::M1, "ROI Observation Description" },
{ 0x300A, 0x0084, 0, VR::DS, VM::M1, "Beam Dose" },
{ 0x500C, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 7" },
{ 0x500E, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 8" },
{ 0x5018, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 13" },
{ 0x501A, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 14" },
{ 0x501C, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0077[] = {
{ 0x0018, 0x1405, 0, VR::IS, VM::M1, "Relative X-Ray Exposure" },
{ 0x0024, 0x0068, 0, VR::FL, VM::M1, "Localized Deviation from Normal" },
{ 0x0044, 0x0008, 0, VR::LO, VM::M1TN, "Product Name" },
{ 0x0050, 0x001C, 0, VR::FD, VM::M1, "Container Component Length" },
{ 0x0054, 0x0018, 0, VR::SH, VM::M1, "Energy Window Name" },
{ 0x0066, 0x002A, 0, VR::UL, VM::M1, "Surface Count" },
{ 0x0072, 0x003E, 0, VR::SQ, VM::M1, "Abstract Prior Code Sequence" },
{ 0x500A, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 6" },
{ 0x500C, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0078[] = {
{ 0x0018, 0x1016, 0, VR::LO, VM::M1, "Secondary Capture Device Manufacturer" },
{ 0x0044, 0x000B, 0, VR::DT, VM::M1, "Product Expiration DateTime" },
{ 0x0048, 0x0007, 0, VR::UL, VM::M1, "Total Pixel Matrix Rows" },
{ 0x0066, 0x0029, 0, VR::OW, VM::M1, "Primitive Point Index List" },
{ 0x300A, 0x0086, 0, VR::DS, VM::M1, "Beam Meterset" },
{ 0x300C, 0x0080, 0, VR::SQ, VM::M1, "Referenced Dose Sequence" },
{ 0x500C, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 7" },
{ 0x500E, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 8" },
{ 0x5018, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 13" },
{ 0x501A, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 14" },
{ 0x501E, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0079[] = {
{ 0x0014, 0x3099, 0, VR::LT, VM::M1, "Calibration Notes" },
{ 0x0018, 0x1017, 1, VR::LO, VM::M1, "Hardcopy Device Manufacturer" },
{ 0x0028, 0x0066, 1, VR::AT, VM::M1TN, "Compression Step Pointers" },
{ 0x0044, 0x000A, 0, VR::LO, VM::M1, "Product Lot Identifier" },
{ 0x0048, 0x0006, 0, VR::UL, VM::M1, "Total Pixel Matrix Columns" },
{ 0x0050, 0x001E, 0, VR::LO, VM::M1, "Container Component Description" },
{ 0x0066, 0x0028, 0, VR::SQ, VM::M1, "Line Sequence" },
{ 0x0068, 0x65B0, 0, VR::FD, VM::M4, "2D Line Coordinates" },
{ 0x0072, 0x003C, 0, VR::SS, VM::M2, "Abstract Prior Value" },
{ 0x0076, 0x0038, 0, VR::CS, VM::M1, "Mandatory Component Type" },
{ 0x5008, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 5" },
{ 0x500E, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0080[] = {
{ 0x0010, 0x1000, 0, VR::LO, VM::M1TN, "Other Patient IDs" },
{ 0x0014, 0x0045, 0, VR::ST, VM::M1TN, "Material Properties File Format" },
{ 0x0018, 0x1008, 0, VR::LO, VM::M1, "Gantry ID" },
{ 0x0018, 0x9200, 0, VR::CS, VM::M1, "MR Spectroscopy Acquisition Type" },
{ 0x0020, 0x9238, 0, VR::LO, VM::M1, "Functional Group Private Creator" },
{ 0x0024, 0x0075, 0, VR::FL, VM::M1, "Short Term Fluctuation" },
{ 0x0040, 0x0011, 0, VR::SH, VM::M1, "Scheduled Procedure Step Location" },
{ 0x0042, 0x0013, 0, VR::SQ, VM::M1, "Source Instance Sequence" },
{ 0x0052, 0x0003, 0, VR::FD, VM::M1, "Beam Spot Size" },
{ 0x0070, 0x0021, 0, VR::US, VM::M1, "Number of Graphic Points" },
{ 0x1010, 0x0000, 1, VR::US, VM::M1TN, "Zonal Map" },
{ 0x5000, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value" },
{ 0x5004, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 3" },
{ 0x5006, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 4" },
{ 0x5010, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 9" },
{ 0x5012, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0081[] = {
{ 0x0008, 0x0058, 0, VR::UI, VM::M1TN, "Failed SOP Instance UID List" },
{ 0x0010, 0x0040, 0, VR::CS, VM::M1, "Patient's Sex" },
{ 0x0010, 0x1001, 0, VR::PN, VM::M1TN, "Other Patient Names" },
{ 0x0012, 0x0042, 0, VR::LO, VM::M1, "Clinical Trial Subject Reading ID" },
{ 0x0014, 0x0044, 0, VR::ST, VM::M1TN, "Material Properties File ID" },
{ 0x0020, 0x0070, 1, VR::LO, VM::M1, "Image Geometry Type" },
{ 0x0022, 0x1033, 0, VR::FL, VM::M1, "Keratometer Index" },
{ 0x0024, 0x0074, 0, VR::CS, VM::M1, "Short Term Fluctuation Calculated" },
{ 0x0040, 0x0010, 0, VR::SH, VM::M1TN, "Scheduled Station Name" },
{ 0x0040, 0x0400, 0, VR::LT, VM::M1, "Comments on the Scheduled Procedure Step" },
{ 0x0040, 0xA29A, 1, VR::SL, VM::M2T2N, "Pixel Coordinates Set (Trial)" },
{ 0x0042, 0x0012, 0, VR::LO, VM::M1, "MIME Type of Encapsulated Document" },
{ 0x0046, 0x0016, 0, VR::SQ, VM::M1, "Unspecified Laterality Lens Sequence" },
{ 0x0052, 0x0002, 0, VR::FD, VM::M1, "OCT Focal Distance" },
{ 0x0054, 0x0414, 0, VR::SQ, VM::M1, "Patient Gantry Relationship Code Sequence" },
{ 0x0066, 0x0036, 0, VR::LO, VM::M1, "Algorithm Name" },
{ 0x0070, 0x0020, 0, VR::US, VM::M1, "Graphic Dimensions" },
{ 0x0072, 0x0022, 0, VR::SQ, VM::M1, "Image Set Selector Sequence" },
{ 0x0072, 0x0432, 0, VR::US, VM::M2TN, "Synchronized Image Box List" },
{ 0x0078, 0x0028, 0, VR::SQ, VM::M1, "Implant Template Group Target Anatomy Sequence" },
{ 0x5010, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 9" },
{ 0x5016, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0082[] = {
{ 0x0010, 0x1002, 0, VR::SQ, VM::M1, "Other Patient IDs Sequence" },
{ 0x0024, 0x0077, 0, VR::FL, VM::M1, "Short Term Fluctuation Probability" },
{ 0x0032, 0x1020, 1, VR::LO, VM::M1, "Scheduled Study Location" },
{ 0x0042, 0x0011, 0, VR::OB, VM::M1, "Encapsulated Document" },
{ 0x0046, 0x0015, 0, VR::SQ, VM::M1, "Left Lens Sequence" },
{ 0x0052, 0x0001, 0, VR::FL, VM::M1, "Contrast/Bolus Ingredient Percent by Volume" },
{ 0x0066, 0x0035, 0, VR::SQ, VM::M1, "Surface Processing Algorithm Identification Sequence" },
{ 0x0070, 0x0023, 0, VR::CS, VM::M1, "Graphic Type" },
{ 0x5002, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 2" },
{ 0x5004, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 3" },
{ 0x5006, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 4" },
{ 0x5010, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 9" },
{ 0x5012, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0083[] = {
{ 0x0012, 0x0040, 0, VR::LO, VM::M1, "Clinical Trial Subject ID" },
{ 0x0014, 0x0046, 0, VR::LT, VM::M1, "Material Notes" },
{ 0x0024, 0x0076, 0, VR::CS, VM::M1, "Short Term Fluctuation Probability Calculated" },
{ 0x0032, 0x1021, 1, VR::AE, VM::M1TN, "Scheduled Study Location AE Title" },
{ 0x0040, 0x0012, 0, VR::LO, VM::M1, "Pre-Medication" },
{ 0x0042, 0x0010, 0, VR::ST, VM::M1, "Document Title" },
{ 0x0046, 0x0014, 0, VR::SQ, VM::M1, "Right Lens Sequence" },
{ 0x0066, 0x0034, 0, VR::SQ, VM::M1, "Facet Sequence" },
{ 0x0070, 0x0022, 0, VR::FL, VM::M2TN, "Graphic Data" },
{ 0x0072, 0x0020, 0, VR::SQ, VM::M1, "Image Sets Sequence" },
{ 0x0072, 0x0430, 0, VR::SQ, VM::M1, "Image Box Synchronization Sequence" },
{ 0x0078, 0x002A, 0, VR::SQ, VM::M1, "Implant Template Group Members Sequence" },
{ 0x2040, 0x0090, 1, VR::CS, VM::M1, "Overlay Mode" },
{ 0x5012, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 10" },
{ 0x5014, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0084[] = {
{ 0x0024, 0x0071, 0, VR::FL, VM::M1, "Global Deviation Probability" },
{ 0x0044, 0x0011, 0, VR::LO, VM::M1, "Substance Administration Notes" },
{ 0x0052, 0x0007, 0, VR::FD, VM::M1, "OCT Optical Center Wavelength" },
{ 0x5000, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor" },
{ 0x5002, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 2" },
{ 0x5004, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 3" },
{ 0x5014, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 11" },
{ 0x5016, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 12" },
{ 0x5400, 0x0100, 0, VR::SQ, VM::M1, "Waveform Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0085[] = {
{ 0x0008, 0x9215, 0, VR::SQ, VM::M1, "Derivation Code Sequence" },
{ 0x0010, 0x1005, 0, VR::PN, VM::M1, "Patient's Birth Name" },
{ 0x0022, 0x1037, 0, VR::FL, VM::M1, "Target Refraction" },
{ 0x0024, 0x0070, 0, VR::FL, VM::M1, "Visual Field Mean Sensitivity" },
{ 0x0028, 0x9235, 0, VR::CS, VM::M1, "Signal Domain Rows" },
{ 0x0044, 0x0010, 0, VR::DT, VM::M1, "Substance Administration DateTime" },
{ 0x0046, 0x0012, 0, VR::LO, VM::M1, "Lens Description" },
{ 0x0050, 0x0004, 0, VR::CS, VM::M1, "Calibration Image" },
{ 0x0052, 0x0006, 0, VR::CS, VM::M1, "OCT Acquisition Domain" },
{ 0x0054, 0x0410, 0, VR::SQ, VM::M1, "Patient Orientation Code Sequence" },
{ 0x0066, 0x0032, 0, VR::LT, VM::M1, "Algorithm Parameters" },
{ 0x0070, 0x0024, 0, VR::CS, VM::M1, "Graphic Filled" },
{ 0x0072, 0x0026, 0, VR::AT, VM::M1, "Selector Attribute" },
{ 0x5012, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 10" },
{ 0x5014, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0086[] = {
{ 0x0014, 0x3080, 0, VR::OB, VM::M1, "Bad Pixel Image" },
{ 0x0024, 0x0073, 0, VR::FL, VM::M1, "Localized Deviation Probability" },
{ 0x0044, 0x0013, 0, VR::SQ, VM::M1, "Product Parameter Sequence" },
{ 0x0066, 0x0031, 0, VR::LO, VM::M1, "Algorithm Version" },
{ 0x5000, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value" },
{ 0x5002, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 2" },
{ 0x5006, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 4" },
{ 0x5014, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 11" },
{ 0x5016, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0087[] = {
{ 0x0014, 0x0042, 0, VR::ST, VM::M1TN, "Material Grade" },
{ 0x0022, 0x1035, 0, VR::SQ, VM::M1, "Source of Ophthalmic Axial Length Code Sequence" },
{ 0x0024, 0x0072, 0, VR::CS, VM::M1, "Local Deviation Probability Normals Flag" },
{ 0x0042, 0x0014, 0, VR::LO, VM::M1TN, "List of MIME Types" },
{ 0x0044, 0x0012, 0, VR::LO, VM::M1, "Substance Administration Device ID" },
{ 0x0052, 0x0004, 0, VR::FD, VM::M1, "Effective Refractive Index" },
{ 0x0054, 0x0412, 0, VR::SQ, VM::M1, "Patient Orientation Modifier Code Sequence" },
{ 0x0066, 0x0030, 0, VR::SQ, VM::M1, "Algorithm Name Code Sequence" },
{ 0x0072, 0x0024, 0, VR::CS, VM::M1, "Image Set Selector Usage Flag" },
{ 0x0072, 0x0434, 0, VR::CS, VM::M1, "Type of Synchronization" },
{ 0x0076, 0x0020, 0, VR::SQ, VM::M1, "Procedure Type Code Sequence" },
{ 0x0078, 0x002E, 0, VR::US, VM::M1, "Implant Template Group Member ID" },
{ 0x5010, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 9" },
{ 0x5016, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0088[] = {
{ 0x0008, 0x0051, 0, VR::SQ, VM::M1, "Issuer of Accession Number Sequence" },
{ 0x0008, 0x1010, 0, VR::SH, VM::M1, "Station Name" },
{ 0x0018, 0x1000, 0, VR::LO, VM::M1, "Device Serial Number" },
{ 0x0018, 0x5104, 0, VR::SQ, VM::M1, "Projection Eponymous Name Code Sequence" },
{ 0x0028, 0x0071, 1, VR::XS, VM::M1, "Perimeter Value" },
{ 0x0038, 0x0061, 1, VR::LO, VM::M1, "Issuer of Service Episode ID" },
{ 0x0048, 0x0011, 0, VR::CS, VM::M1, "Focus Method" },
{ 0x3008, 0x0092, 0, VR::IS, VM::M1, "Referenced Calculated Dose Reference Number" },
{ 0x5008, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 5" },
{ 0x500C, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 7" },
{ 0x500E, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 8" },
{ 0x5018, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 13" },
{ 0x501A, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0089[] = {
{ 0x0008, 0x0050, 0, VR::SH, VM::M1, "Accession Number" },
{ 0x0018, 0x0040, 0, VR::IS, VM::M1, "Cine Rate" },
{ 0x0018, 0x1411, 0, VR::DS, VM::M1, "Exposure Index" },
{ 0x0028, 0x0070, 1, VR::US, VM::M1TN, "Perimeter Table" },
{ 0x0038, 0x0060, 0, VR::LO, VM::M1, "Service Episode ID" },
{ 0x0048, 0x0010, 0, VR::CS, VM::M1, "Specimen Label in Image" },
{ 0x0078, 0x0020, 0, VR::LO, VM::M1, "Implant Template Group Issuer" },
{ 0x5018, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 13" },
{ 0x501E, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0090[] = {
{ 0x0018, 0x1002, 0, VR::UI, VM::M1, "Device UID" },
{ 0x0018, 0x1412, 0, VR::DS, VM::M1, "Target Exposure Index" },
{ 0x0048, 0x0013, 0, VR::US, VM::M1, "Number of Focal Planes" },
{ 0x0052, 0x0009, 0, VR::FD, VM::M1, "Ranging Depth" },
{ 0x3008, 0x0090, 0, VR::SQ, VM::M1, "Referenced Calculated Dose Reference Sequence" },
{ 0x500A, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 6" },
{ 0x500C, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 7" },
{ 0x500E, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 8" },
{ 0x5018, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 13" },
{ 0x501A, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0091[] = {
{ 0x0008, 0x0052, 0, VR::CS, VM::M1, "Query/Retrieve Level" },
{ 0x0018, 0x0042, 0, VR::CS, VM::M1, "Initial Cine Run State" },
{ 0x0018, 0x1003, 0, VR::LO, VM::M1, "Device ID" },
{ 0x0018, 0x1413, 0, VR::DS, VM::M1, "Deviation Index" },
{ 0x0022, 0x1039, 0, VR::CS, VM::M1, "Refractive Procedure Occurred" },
{ 0x0038, 0x0062, 0, VR::LO, VM::M1, "Service Episode Description" },
{ 0x0040, 0xA290, 1, VR::CS, VM::M1, "Coordinates Set Geometric Type (Trial)" },
{ 0x0048, 0x0012, 0, VR::CS, VM::M1, "Extended Depth of Field" },
{ 0x0052, 0x0008, 0, VR::FD, VM::M1, "Axial Resolution" },
{ 0x0072, 0x0028, 0, VR::US, VM::M1, "Selector Value Number" },
{ 0x501A, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 14" },
{ 0x501C, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0092[] = {
{ 0x0018, 0x1004, 0, VR::LO, VM::M1, "Plate ID" },
{ 0x0018, 0x5100, 0, VR::CS, VM::M1, "Patient Position" },
{ 0x0024, 0x0079, 0, VR::FL, VM::M1, "Corrected Localized Deviation From Normal" },
{ 0x0040, 0xA297, 1, VR::ST, VM::M1, "Algorithm Description (Trial)" },
{ 0x0044, 0x0019, 0, VR::SQ, VM::M1, "Substance Administration Parameter Sequence" },
{ 0x0048, 0x0015, 0, VR::US, VM::M3, "Recommended Absent Pixel CIELab Value" },
{ 0x5008, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 5" },
{ 0x500A, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 6" },
{ 0x500C, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 7" },
{ 0x501C, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 15" },
{ 0x501E, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0093[] = {
{ 0x0008, 0x0054, 0, VR::AE, VM::M1TN, "Retrieve AE Title" },
{ 0x0018, 0x1005, 0, VR::LO, VM::M1, "Generator ID" },
{ 0x0018, 0x5101, 0, VR::CS, VM::M1, "View Position" },
{ 0x0024, 0x0078, 0, VR::CS, VM::M1, "Corrected Localized Deviation From Normal Calculated" },
{ 0x0038, 0x0064, 0, VR::SQ, VM::M1, "Issuer of Service Episode ID Sequence" },
{ 0x0040, 0xA296, 1, VR::SQ, VM::M1, "Algorithm Code Sequence (Trial)" },
{ 0x0048, 0x0014, 0, VR::FL, VM::M1, "Distance Between Focal Planes" },
{ 0x0078, 0x0024, 0, VR::LO, VM::M1, "Implant Template Group Version" },
{ 0x501A, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 14" },
{ 0x501C, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0094[] = {
{ 0x0018, 0x1006, 0, VR::LO, VM::M1, "Grid ID" },
{ 0x5008, 0x0112, 1, VR::US, VM::M1TN, "Coordinate Start Value 5" },
{ 0x500A, 0x0110, 1, VR::US, VM::M1TN, "Curve Data Descriptor 6" },
{ 0x500E, 0x0114, 1, VR::US, VM::M1TN, "Coordinate Step Value 8" },
{ 0x501C, 0x0106, 1, VR::SH, VM::M1TN, "Curve Range 15" },
{ 0x501E, 0x0104, 1, VR::US, VM::M1TN, "Minimum Coordinate Value 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0095[] = {
{ 0x0008, 0x0056, 0, VR::CS, VM::M1, "Instance Availability" },
{ 0x0018, 0x1007, 0, VR::LO, VM::M1, "Cassette ID" },
{ 0x0040, 0xDB73, 0, VR::UL, VM::M1TN, "Referenced Content Item Identifier" },
{ 0x0046, 0x0018, 0, VR::SQ, VM::M1, "Cylinder Sequence" },
{ 0x0068, 0x65A0, 0, VR::SQ, VM::M1, "2D Line Coordinates Sequence" },
{ 0x0078, 0x0026, 0, VR::SQ, VM::M1, "Replaced Implant Template Group Sequence" },
{ 0x5018, 0x0103, 1, VR::US, VM::M1, "Data Value Representation 13" },
{ 0x501E, 0x0105, 1, VR::US, VM::M1TN, "Maximum Coordinate Value 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0096[] = {
{ 0x0010, 0x1030, 0, VR::DS, VM::M1, "Patient's Weight" },
{ 0x0020, 0x1000, 1, VR::IS, VM::M1, "Series in Study" },
{ 0x0024, 0x0045, 0, VR::CS, VM::M1, "False Negatives Estimate Flag" },
{ 0x0040, 0x1060, 1, VR::LO, VM::M1, "Requested Procedure Description (Trial)" },
{ 0x0052, 0x0033, 0, VR::FD, VM::M1, "Seam Line Location" },
{ 0x0062, 0x0003, 0, VR::SQ, VM::M1, "Segmented Property Category Code Sequence" },
{ 0x0064, 0x0005, 0, VR::SQ, VM::M1, "Deformable Registration Grid Sequence" },
{ 0x0070, 0x0011, 0, VR::FL, VM::M2, "Bounding Box Bottom Right Hand Corner" },
{ 0x0070, 0x0401, 0, VR::US, VM::M3, "Graphic Layer Recommended Display CIELab Value" },
{ 0x0074, 0x1054, 0, VR::UL, VM::M1, "Attribute Item Selector" },
{ 0x3006, 0x00A4, 0, VR::CS, VM::M1, "RT ROI Interpreted Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0097[] = {
{ 0x0008, 0x0068, 0, VR::CS, VM::M1, "Presentation Intent Type" },
{ 0x0012, 0x0072, 0, VR::LO, VM::M1, "Clinical Trial Series Description" },
{ 0x0018, 0x9231, 0, VR::US, VM::M1, "MR Acquisition Phase Encoding Steps in-plane" },
{ 0x0020, 0x1001, 1, VR::IS, VM::M1, "Acquisitions in Series" },
{ 0x0022, 0x0042, 0, VR::SQ, VM::M1, "Mydriatic Agent Concentration Units Sequence" },
{ 0x0024, 0x0044, 0, VR::LT, VM::M1, "Comments on Patient's Performance of Visual Field" },
{ 0x0040, 0x0020, 0, VR::CS, VM::M1, "Scheduled Procedure Step Status" },
{ 0x0062, 0x0002, 0, VR::SQ, VM::M1, "Segment Sequence" },
{ 0x0070, 0x0010, 0, VR::FL, VM::M2, "Bounding Box Top Left Hand Corner" },
{ 0x0072, 0x0012, 0, VR::SQ, VM::M1, "Source Hanging Protocol Sequence" },
{ 0x0072, 0x0402, 0, VR::CS, VM::M1, "Filter-by Category" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0098[] = {
{ 0x0012, 0x0071, 0, VR::LO, VM::M1, "Clinical Trial Series ID" },
{ 0x0018, 0x9232, 0, VR::US, VM::M1, "MR Acquisition Phase Encoding Steps out-of-plane" },
{ 0x0020, 0x1002, 0, VR::IS, VM::M1, "Images in Acquisition" },
{ 0x0022, 0x0041, 0, VR::FL, VM::M1, "Depth of Transverse Image" },
{ 0x0032, 0x1010, 1, VR::DA, VM::M1, "Scheduled Study Stop Date" },
{ 0x0052, 0x0031, 0, VR::CS, VM::M1, "Catheter Direction of Rotation" },
{ 0x0062, 0x0001, 0, VR::CS, VM::M1, "Segmentation Type" },
{ 0x0064, 0x0007, 0, VR::UL, VM::M3, "Grid Dimensions" },
{ 0x0070, 0x0403, 0, VR::FL, VM::M1, "Relative Opacity" },
{ 0x0074, 0x1056, 0, VR::LO, VM::M1, "Attribute Occurrence Private Creator" },
{ 0x3006, 0x00A6, 0, VR::PN, VM::M1, "ROI Interpreter" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0099[] = {
{ 0x0020, 0x1003, 1, VR::IS, VM::M1, "Images in Series" },
{ 0x0024, 0x0046, 0, VR::FL, VM::M1, "False Negatives Estimate" },
{ 0x0032, 0x1011, 1, VR::TM, VM::M1, "Scheduled Study Stop Time" },
{ 0x0052, 0x0030, 0, VR::SS, VM::M1, "OCT Z Offset Correction" },
{ 0x0054, 0x0036, 0, VR::IS, VM::M1, "Phase Delay" },
{ 0x0066, 0x0004, 0, VR::LT, VM::M1, "Surface Comments" },
{ 0x0070, 0x0012, 0, VR::CS, VM::M1, "Bounding Box Text Horizontal Justification" },
{ 0x0070, 0x0402, 0, VR::SQ, VM::M1, "Blending Sequence" },
{ 0x0072, 0x0010, 0, VR::LO, VM::M1, "Hanging Protocol User Group Name" },
{ 0x0072, 0x0400, 0, VR::SQ, VM::M1, "Filter Operations Sequence" },
{ 0x0074, 0x1057, 0, VR::IS, VM::M1TN, "Selector Sequence Pointer Items" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0100[] = {
{ 0x0018, 0x9234, 0, VR::UL, VM::M1, "Spectroscopy Acquisition Phase Columns" },
{ 0x0020, 0x1004, 1, VR::IS, VM::M1, "Acquisitions in Study" },
{ 0x0054, 0x0031, 0, VR::US, VM::M1, "Number of Phases" },
{ 0x0066, 0x0003, 0, VR::UL, VM::M1, "Surface Number" },
{ 0x0070, 0x0015, 0, VR::CS, VM::M1, "Anchor Point Visibility" },
{ 0x0070, 0x0405, 0, VR::CS, VM::M1, "Blending Position" },
{ 0x0074, 0x1050, 0, VR::SQ, VM::M1, "Attribute Occurrence Sequence" },
{ 0x3006, 0x00A0, 0, VR::SQ, VM::M1, "Related RT ROI Observations Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0101[] = {
{ 0x0020, 0x1005, 1, VR::IS, VM::M1, "Images in Study" },
{ 0x0022, 0x1007, 0, VR::SQ, VM::M1, "Ophthalmic Axial Measurements Right Eye Sequence" },
{ 0x0024, 0x0040, 0, VR::CS, VM::M1, "Excessive Fixation Losses" },
{ 0x0052, 0x0036, 0, VR::US, VM::M1, "Seam Line Index" },
{ 0x0054, 0x0030, 0, VR::US, VM::M1TN, "Phase Vector" },
{ 0x0062, 0x0006, 0, VR::ST, VM::M1, "Segment Description" },
{ 0x0066, 0x0002, 0, VR::SQ, VM::M1, "Surface Sequence" },
{ 0x0070, 0x0014, 0, VR::FL, VM::M2, "Anchor Point" },
{ 0x0070, 0x0404, 0, VR::SQ, VM::M1, "Referenced Spatial Registration Sequence" },
{ 0x0072, 0x0406, 0, VR::CS, VM::M1, "Filter-by Operator" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0102[] = {
{ 0x0018, 0x9236, 0, VR::CS, VM::M1, "Cardiac Cycle Position" },
{ 0x0040, 0x0027, 0, VR::SQ, VM::M1, "Order Filler Identifier Sequence" },
{ 0x0054, 0x0033, 0, VR::US, VM::M1, "Number of Frames in Phase" },
{ 0x0062, 0x0005, 0, VR::LO, VM::M1, "Segment Label" },
{ 0x0064, 0x0003, 0, VR::UI, VM::M1, "Source Frame of Reference UID" },
{ 0x0066, 0x0001, 0, VR::UL, VM::M1, "Number of Surfaces" },
{ 0x0074, 0x1052, 0, VR::AT, VM::M1, "Attribute Occurrence Pointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0103[] = {
{ 0x0024, 0x0042, 0, VR::US, VM::M1, "Stimuli Retesting Quantity" },
{ 0x0040, 0x0026, 0, VR::SQ, VM::M1, "Order Placer Identifier Sequence" },
{ 0x0052, 0x0034, 0, VR::FD, VM::M1, "First A-line Location" },
{ 0x0054, 0x0032, 0, VR::SQ, VM::M1, "Phase Information Sequence" },
{ 0x0062, 0x0004, 0, VR::US, VM::M1, "Segment Number" },
{ 0x0064, 0x0002, 0, VR::SQ, VM::M1, "Deformable Registration Sequence" },
{ 0x0072, 0x0014, 0, VR::US, VM::M1, "Number of Priors Referenced" },
{ 0x0072, 0x0404, 0, VR::CS, VM::M1, "Filter-by Attribute Presence" },
{ 0x0076, 0x0010, 0, VR::SQ, VM::M1, "Implant Assembly Template Target Anatomy Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0104[] = {
{ 0x0008, 0x0061, 0, VR::CS, VM::M1TN, "Modalities in Study" },
{ 0x0018, 0x0071, 0, VR::CS, VM::M1, "Acquisition Termination Condition" },
{ 0x0018, 0x1030, 0, VR::LO, VM::M1, "Protocol Name" },
{ 0x0028, 0x1410, 0, VR::CS, VM::M1, "Alpha LUT Transfer Function" },
{ 0x0062, 0x000B, 0, VR::US, VM::M1TN, "Referenced Segment Number" },
{ 0x300A, 0x00A0, 0, VR::IS, VM::M1, "Number of Brachy Application Setups" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0105[] = {
{ 0x0008, 0x0060, 0, VR::CS, VM::M1, "Modality" },
{ 0x0018, 0x0070, 0, VR::IS, VM::M1, "Counts Accumulated" },
{ 0x0018, 0x9239, 0, VR::SQ, VM::M1, "Specific Absorption Rate Sequence" },
{ 0x0028, 0x0040, 1, VR::CS, VM::M1, "Image Format" },
{ 0x0038, 0x0050, 0, VR::LO, VM::M1, "Special Needs" },
{ 0x0052, 0x003A, 0, VR::CS, VM::M1, "Refractive Index Applied" },
{ 0x0062, 0x000A, 0, VR::SQ, VM::M1, "Segment Identification Sequence" },
{ 0x0066, 0x000E, 0, VR::CS, VM::M1, "Finite Volume" },
{ 0x0078, 0x0010, 0, VR::ST, VM::M1, "Implant Template Group Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0106[] = {
{ 0x0018, 0x0073, 0, VR::CS, VM::M1, "Acquisition Start Condition" },
{ 0x0022, 0x0049, 0, VR::FL, VM::M1, "Maximum Across-scan Distortion" },
{ 0x0022, 0x1008, 0, VR::SQ, VM::M1, "Ophthalmic Axial Measurements Left Eye Sequence" },
{ 0x0052, 0x0039, 0, VR::CS, VM::M1, "Interpolation Type" },
{ 0x0062, 0x0009, 0, VR::LO, VM::M1, "Segment Algorithm Name" },
{ 0x0064, 0x000F, 0, VR::SQ, VM::M1, "Pre Deformation Matrix Registration Sequence" },
{ 0x0066, 0x000D, 0, VR::CS, VM::M1, "Recommended Presentation Type" },
{ 0x3008, 0x00A0, 0, VR::SQ, VM::M1, "Beam Limiting Device Leaf Pairs Sequence" },
{ 0x300A, 0x00A2, 0, VR::DS, VM::M3, "Brachy Application Setup Dose Specification Point" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0107[] = {
{ 0x0008, 0x0062, 0, VR::UI, VM::M1TN, "SOP Classes in Study" },
{ 0x0018, 0x0072, 0, VR::DS, VM::M1, "Effective Duration" },
{ 0x0022, 0x0048, 0, VR::FL, VM::M1, "Across-scan Spatial Resolution" },
{ 0x0052, 0x0038, 0, VR::US, VM::M1, "Number of Padded A-lines" },
{ 0x0062, 0x0008, 0, VR::CS, VM::M1, "Segment Algorithm Type" },
{ 0x0066, 0x000C, 0, VR::FL, VM::M1, "Recommended Presentation Opacity" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0108[] = {
{ 0x0018, 0x0075, 0, VR::IS, VM::M1, "Acquisition Termination Condition Data" },
{ 0x0054, 0x0039, 0, VR::CS, VM::M1, "Phase Description" },
{ 0x0062, 0x000F, 0, VR::SQ, VM::M1, "Segmented Property Type Code Sequence" },
{ 0x0064, 0x0009, 0, VR::OF, VM::M1, "Vector Grid Data" },
{ 0x0066, 0x000B, 0, VR::LO, VM::M1, "Surface Processing Description" },
{ 0x300A, 0x00A4, 0, VR::DS, VM::M1, "Brachy Application Setup Dose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0109[] = {
{ 0x0008, 0x0064, 0, VR::CS, VM::M1, "Conversion Type" },
{ 0x0018, 0x0074, 0, VR::IS, VM::M1, "Acquisition Start Condition Data" },
{ 0x0022, 0x004E, 0, VR::DS, VM::M1, "Mydriatic Agent Concentration" },
{ 0x0024, 0x0048, 0, VR::US, VM::M1, "Negative Catch Trials Quantity" },
{ 0x0054, 0x0038, 0, VR::IS, VM::M1, "Pause Between Frames" },
{ 0x0062, 0x000E, 0, VR::US, VM::M1, "Maximum Fractional Value" },
{ 0x0064, 0x0008, 0, VR::FD, VM::M3, "Grid Resolution" },
{ 0x0066, 0x000A, 0, VR::FL, VM::M1, "Surface Processing Ratio" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0110[] = {
{ 0x0062, 0x000D, 0, VR::US, VM::M3, "Recommended Display CIELab Value" },
{ 0x0066, 0x0009, 0, VR::CS, VM::M1, "Surface Processing" },
{ 0x300C, 0x00A0, 0, VR::IS, VM::M1, "Referenced Tolerance Table Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0111[] = {
{ 0x0046, 0x0028, 0, VR::SQ, VM::M1, "Prism Sequence" },
{ 0x0062, 0x000C, 0, VR::US, VM::M1, "Recommended Display Grayscale Value" },
{ 0x0068, 0x6590, 0, VR::FD, VM::M3, "3D Point Coordinates" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0112[] = {
{ 0x0010, 0x1020, 0, VR::DS, VM::M1, "Patient's Size" },
{ 0x0012, 0x0063, 0, VR::LO, VM::M1TN, "De-identification Method" },
{ 0x0018, 0x9220, 0, VR::FD, VM::M1, "Frame Acquisition Duration" },
{ 0x0024, 0x0055, 0, VR::CS, VM::M1, "Catch Trials Data Flag" },
{ 0x0028, 0x1408, 0, VR::OW, VM::M1, "Blending Lookup Table Data" },
{ 0x0040, 0x0031, 0, VR::UT, VM::M1, "Local Namespace Entity ID" },
{ 0x0066, 0x0017, 0, VR::FL, VM::M3, "Point Position Accuracy" },
{ 0x0070, 0x0001, 0, VR::SQ, VM::M1, "Graphic Annotation Sequence" },
{ 0x0074, 0x1044, 0, VR::SQ, VM::M1, "Conventional Machine Verification Sequence" },
{ 0x3006, 0x00B4, 0, VR::DS, VM::M1, "ROI Physical Property Value" },
{ 0x300A, 0x00B8, 0, VR::CS, VM::M1, "RT Beam Limiting Device Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0113[] = {
{ 0x0010, 0x1021, 0, VR::SQ, VM::M1, "Patient's Size Code Sequence" },
{ 0x0012, 0x0062, 0, VR::CS, VM::M1, "Patient Identity Removed" },
{ 0x0020, 0x0050, 1, VR::DS, VM::M1, "Location" },
{ 0x0024, 0x0054, 0, VR::FL, VM::M1, "False Positives Estimate" },
{ 0x0046, 0x0036, 0, VR::CS, VM::M1, "Vertical Prism Base" },
{ 0x0050, 0x0020, 0, VR::LO, VM::M1, "Device Description" },
{ 0x0066, 0x0016, 0, VR::OF, VM::M1, "Point Coordinates Data" },
{ 0x0072, 0x0002, 0, VR::SH, VM::M1, "Hanging Protocol Name" },
{ 0x0076, 0x0006, 0, VR::LO, VM::M1, "Implant Assembly Template Version" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0114[] = {
{ 0x0022, 0x1010, 0, VR::CS, VM::M1, "Ophthalmic Axial Length Measurements Type" },
{ 0x0024, 0x0057, 0, VR::CS, VM::M1, "Test Point Normals Data Flag" },
{ 0x0032, 0x1000, 1, VR::DA, VM::M1, "Scheduled Study Start Date" },
{ 0x0040, 0x0033, 0, VR::CS, VM::M1, "Universal Entity ID Type" },
{ 0x0066, 0x0015, 0, VR::UL, VM::M1, "Number of Surface Points" },
{ 0x0070, 0x0003, 0, VR::CS, VM::M1, "Bounding Box Annotation Units" },
{ 0x0074, 0x1046, 0, VR::SQ, VM::M1, "Ion Machine Verification Sequence" },
{ 0x3006, 0x00B6, 0, VR::SQ, VM::M1, "ROI Elemental Composition Sequence" },
{ 0x300A, 0x00BA, 0, VR::DS, VM::M1, "Source to Beam Limiting Device Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0115[] = {
{ 0x0012, 0x0060, 0, VR::LO, VM::M1, "Clinical Trial Coordinating Center Name" },
{ 0x0020, 0x0052, 0, VR::UI, VM::M1, "Frame of Reference UID" },
{ 0x0024, 0x0056, 0, VR::US, VM::M1, "Positive Catch Trials Quantity" },
{ 0x0028, 0x140B, 0, VR::SQ, VM::M1, "Enhanced Palette Color Lookup Table Sequence" },
{ 0x0032, 0x1001, 1, VR::TM, VM::M1, "Scheduled Study Start Time" },
{ 0x0040, 0x0032, 0, VR::UT, VM::M1, "Universal Entity ID" },
{ 0x0046, 0x0034, 0, VR::FD, VM::M1, "Vertical Prism Power" },
{ 0x0062, 0x0010, 0, VR::CS, VM::M1, "Segmentation Fractional Type" },
{ 0x0070, 0x0002, 0, VR::CS, VM::M1, "Graphic Layer" },
{ 0x3006, 0x00B7, 0, VR::US, VM::M1, "ROI Elemental Composition Atomic Number" },
{ 0x300A, 0x00BB, 0, VR::FL, VM::M1, "Isocenter to Beam Limiting Device Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0116[] = {
{ 0x0014, 0x1020, 0, VR::DA, VM::M1, "Expiry Date" },
{ 0x0022, 0x0057, 0, VR::FL, VM::M1, "Illumination Bandwidth" },
{ 0x0024, 0x0051, 0, VR::CS, VM::M1, "Excessive False Negatives Data Flag" },
{ 0x0028, 0x140C, 0, VR::SQ, VM::M1, "Blending LUT 2 Sequence" },
{ 0x0040, 0x0035, 0, VR::CS, VM::M1, "Identifier Type Code" },
{ 0x0052, 0x0027, 0, VR::SQ, VM::M1, "Intravascular Frame Content Sequence" },
{ 0x0054, 0x0021, 0, VR::US, VM::M1, "Number of Detectors" },
{ 0x0066, 0x0013, 0, VR::SQ, VM::M1, "Surface Mesh Primitives Sequence" },
{ 0x0070, 0x0005, 0, VR::CS, VM::M1, "Graphic Annotation Units" },
{ 0x0074, 0x1040, 0, VR::SQ, VM::M1, "Related Reference RT Image Sequence" },
{ 0x0076, 0x0003, 0, VR::LO, VM::M1, "Implant Assembly Template Issuer" },
{ 0x3006, 0x00B0, 0, VR::SQ, VM::M1, "ROI Physical Properties Sequence" },
{ 0x300A, 0x00BC, 0, VR::IS, VM::M1, "Number of Leaf/Jaw Pairs" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0117[] = {
{ 0x0022, 0x0056, 0, VR::FL, VM::M1, "Illumination Power" },
{ 0x0024, 0x0050, 0, VR::US, VM::M1, "False Negatives Quantity" },
{ 0x0028, 0x140D, 0, VR::CS, VM::M1, "Blending LUT 2 Transfer Function" },
{ 0x0046, 0x0032, 0, VR::CS, VM::M1, "Horizontal Prism Base" },
{ 0x0052, 0x0026, 0, VR::CS, VM::M1, "OCT Z Offset Applied" },
{ 0x0054, 0x0020, 0, VR::US, VM::M1TN, "Detector Vector" },
{ 0x0064, 0x0010, 0, VR::SQ, VM::M1, "Post Deformation Matrix Registration Sequence" },
{ 0x0066, 0x0012, 0, VR::SQ, VM::M1, "Surface Points Normals Sequence" },
{ 0x0070, 0x0004, 0, VR::CS, VM::M1, "Anchor Point Annotation Units" },
{ 0x0072, 0x0006, 0, VR::CS, VM::M1, "Hanging Protocol Level" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0118[] = {
{ 0x0008, 0x103E, 0, VR::LO, VM::M1, "Series Description" },
{ 0x0018, 0x9226, 0, VR::SQ, VM::M1, "MR Image Frame Type Sequence" },
{ 0x0022, 0x0055, 0, VR::FL, VM::M1, "Illumination Wave Length" },
{ 0x0024, 0x0053, 0, VR::CS, VM::M1, "False Positives Estimate Flag" },
{ 0x0028, 0x005F, 1, VR::LO, VM::M1, "Compression Recognition Code" },
{ 0x0028, 0x140E, 0, VR::CS, VM::M1, "Data Path ID" },
{ 0x0052, 0x0025, 0, VR::SQ, VM::M1, "Intravascular OCT Frame Type Sequence" },
{ 0x0066, 0x0011, 0, VR::SQ, VM::M1, "Surface Points Sequence" },
{ 0x0074, 0x1042, 0, VR::SQ, VM::M1, "General Machine Verification Sequence" },
{ 0x0076, 0x0001, 0, VR::LO, VM::M1, "Implant Assembly Template Name" },
{ 0x3006, 0x00B2, 0, VR::CS, VM::M1, "ROI Physical Property" },
{ 0x300A, 0x00BE, 0, VR::DS, VM::M3TN, "Leaf Position Boundaries" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0119[] = {
{ 0x0008, 0x103F, 0, VR::SQ, VM::M1, "Series Description Code Sequence" },
{ 0x0008, 0x9237, 0, VR::SQ, VM::M1, "Referenced Presentation State Sequence" },
{ 0x0012, 0x0064, 0, VR::SQ, VM::M1, "De-identification Method Code Sequence" },
{ 0x0018, 0x9227, 0, VR::SQ, VM::M1, "MR Spectroscopy Frame Type Sequence" },
{ 0x0024, 0x0052, 0, VR::CS, VM::M1, "Excessive False Negatives" },
{ 0x0028, 0x140F, 0, VR::CS, VM::M1, "RGB LUT Transfer Function" },
{ 0x0040, 0x0036, 0, VR::SQ, VM::M1, "Assigning Facility Sequence" },
{ 0x0046, 0x0030, 0, VR::FD, VM::M1, "Horizontal Prism Power" },
{ 0x0054, 0x0022, 0, VR::SQ, VM::M1, "Detector Information Sequence" },
{ 0x0066, 0x0010, 0, VR::CS, VM::M1, "Manifold" },
{ 0x0070, 0x0006, 0, VR::ST, VM::M1, "Unformatted Text Value" },
{ 0x0072, 0x0004, 0, VR::LO, VM::M1, "Hanging Protocol Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0120[] = {
{ 0x0008, 0x1030, 0, VR::LO, VM::M1, "Study Description" },
{ 0x0018, 0x1020, 0, VR::LO, VM::M1TN, "Software Version(s)" },
{ 0x0018, 0x1800, 0, VR::CS, VM::M1, "Acquisition Time Synchronized" },
{ 0x0028, 0x0051, 0, VR::CS, VM::M1TN, "Corrected Image" },
{ 0x0040, 0x0039, 0, VR::SQ, VM::M1, "Assigning Jurisdiction Code Sequence" },
{ 0x0066, 0x001F, 0, VR::US, VM::M1, "Vector Dimensionality" },
{ 0x0070, 0x0009, 0, VR::SQ, VM::M1, "Graphic Object Sequence" },
{ 0x0074, 0x104C, 0, VR::SQ, VM::M1, "Conventional Control Point Verification Sequence" },
{ 0x0078, 0x0001, 0, VR::LO, VM::M1, "Implant Template Group Name" },
{ 0x300A, 0x00B0, 0, VR::SQ, VM::M1, "Beam Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0121[] = {
{ 0x0008, 0x0070, 0, VR::LO, VM::M1, "Manufacturer" },
{ 0x0018, 0x0060, 0, VR::DS, VM::M1, "KVP" },
{ 0x0018, 0x1801, 0, VR::SH, VM::M1, "Time Source" },
{ 0x0028, 0x0050, 1, VR::LO, VM::M1TN, "Manipulated Image" },
{ 0x0028, 0x1401, 0, VR::SQ, VM::M1, "Data Frame Assignment Sequence" },
{ 0x0038, 0x0040, 1, VR::LO, VM::M1, "Discharge Diagnosis Description" },
{ 0x0066, 0x001E, 0, VR::UL, VM::M1, "Number of Vectors" },
{ 0x0070, 0x0008, 0, VR::SQ, VM::M1, "Text Object Sequence" },
{ 0x0072, 0x000A, 0, VR::DT, VM::M1, "Hanging Protocol Creation DateTime" },
{ 0x0076, 0x000E, 0, VR::SQ, VM::M1, "Derivation Implant Assembly Template Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0122[] = {
{ 0x0008, 0x1032, 0, VR::SQ, VM::M1, "Procedure Code Sequence" },
{ 0x0018, 0x1022, 0, VR::SH, VM::M1, "Video Image Format Acquired" },
{ 0x0018, 0x1802, 0, VR::CS, VM::M1, "Time Distribution Protocol" },
{ 0x0028, 0x1402, 0, VR::CS, VM::M1, "Data Path Assignment" },
{ 0x0052, 0x0029, 0, VR::SQ, VM::M1, "Intravascular OCT Frame Content Sequence" },
{ 0x0074, 0x104E, 0, VR::SQ, VM::M1, "Ion Control Point Verification Sequence" },
{ 0x3008, 0x00B0, 0, VR::SQ, VM::M1, "Recorded Wedge Sequence" },
{ 0x300A, 0x00B2, 0, VR::SH, VM::M1, "Treatment Machine Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0123[] = {
{ 0x0018, 0x1023, 0, VR::LO, VM::M1, "Digital Image Format Acquired" },
{ 0x0018, 0x1803, 0, VR::LO, VM::M1, "NTP Source Address" },
{ 0x0020, 0x9213, 0, VR::LO, VM::M1, "Dimension Index Private Creator" },
{ 0x0022, 0x0058, 0, VR::SQ, VM::M1, "Mydriatic Agent Sequence" },
{ 0x0022, 0x1019, 0, VR::FL, VM::M1, "Ophthalmic Axial Length" },
{ 0x0028, 0x1403, 0, VR::US, VM::M1, "Bits Mapped to Color Lookup Table" },
{ 0x0040, 0x003A, 0, VR::SQ, VM::M1, "Assigning Agency or Department Code Sequence" },
{ 0x0052, 0x0028, 0, VR::FD, VM::M1, "Intravascular Longitudinal Distance" },
{ 0x0066, 0x001C, 0, VR::FL, VM::M3, "Center of Rotation" },
{ 0x0072, 0x0008, 0, VR::LO, VM::M1, "Hanging Protocol Creator" },
{ 0x0076, 0x000C, 0, VR::SQ, VM::M1, "Original Implant Assembly Template Sequence" },
{ 0x300A, 0x00B3, 0, VR::CS, VM::M1, "Primary Dosimeter Unit" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0124[] = {
{ 0x0024, 0x0059, 0, VR::CS, VM::M1, "Global Deviation Probability Normals Flag" },
{ 0x0028, 0x1404, 0, VR::SQ, VM::M1, "Blending LUT 1 Sequence" },
{ 0x0066, 0x001B, 0, VR::FL, VM::M3, "Axis of Rotation" },
{ 0x0074, 0x1048, 0, VR::SQ, VM::M1, "Failed Attributes Sequence" },
{ 0x3006, 0x00B8, 0, VR::FL, VM::M1, "ROI Elemental Composition Atomic Mass Fraction" },
{ 0x300A, 0x00B4, 0, VR::DS, VM::M1, "Source-Axis Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0125[] = {
{ 0x0024, 0x0058, 0, VR::SQ, VM::M1, "Test Point Normals Sequence" },
{ 0x0028, 0x1405, 0, VR::CS, VM::M1, "Blending LUT 1 Transfer Function" },
{ 0x0038, 0x0044, 1, VR::SQ, VM::M1, "Discharge Diagnosis Code Sequence" },
{ 0x0066, 0x001A, 0, VR::FL, VM::M6, "Points Bounding Box Coordinates" },
{ 0x0072, 0x000E, 0, VR::SQ, VM::M1, "Hanging Protocol User Identification Code Sequence" },
{ 0x0076, 0x000A, 0, VR::CS, VM::M1, "Implant Assembly Template Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0126[] = {
{ 0x0028, 0x1406, 0, VR::FD, VM::M1, "Blending Weight Constant" },
{ 0x0066, 0x0019, 0, VR::FL, VM::M1, "Maximum Point Distance" },
{ 0x0074, 0x104A, 0, VR::SQ, VM::M1, "Overridden Attributes Sequence" },
{ 0x300A, 0x00B6, 0, VR::SQ, VM::M1, "Beam Limiting Device Sequence" },
{ 0x300C, 0x00B0, 0, VR::SQ, VM::M1, "Referenced Bolus Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0127[] = {
{ 0x0028, 0x1407, 0, VR::US, VM::M3, "Blending Lookup Table Descriptor" },
{ 0x0046, 0x0038, 0, VR::CS, VM::M1, "Lens Segment Type" },
{ 0x0066, 0x0018, 0, VR::FL, VM::M1, "Mean Point Distance" },
{ 0x0072, 0x000C, 0, VR::SQ, VM::M1, "Hanging Protocol Definition Sequence" },
{ 0x0076, 0x0008, 0, VR::SQ, VM::M1, "Replaced Implant Assembly Template Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0128[] = {
{ 0x0014, 0x2014, 0, VR::IS, VM::M1, "Indication Number" },
{ 0x0040, 0x3001, 0, VR::LO, VM::M1, "Confidentiality Constraint on Patient Data Description" },
{ 0x2010, 0x0010, 0, VR::ST, VM::M1, "Image Display Format" },
{ 0x2020, 0x0020, 0, VR::CS, VM::M1, "Polarity" },
{ 0x300A, 0x004B, 0, VR::FL, VM::M1, "Snout Position Tolerance" },
{ 0x6000, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments" },
{ 0x6004, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 3" },
{ 0x6006, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 4" },
{ 0x6014, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0129[] = {
{ 0x0060, 0x3020, 0, VR::UL, VM::M1TN, "Histogram Data" },
{ 0x3002, 0x0042, 0, VR::DS, VM::M1, "Fluence Data Scale" },
{ 0x3006, 0x0046, 0, VR::IS, VM::M1, "Number of Contour Points" },
{ 0x3008, 0x0048, 0, VR::DS, VM::M1, "Dose Rate Delivered" },
{ 0x300A, 0x004A, 0, VR::DS, VM::M1, "Beam Limiting Device Position Tolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0130[] = {
{ 0x0014, 0x2016, 0, VR::SH, VM::M1, "Indication Label" },
{ 0x3002, 0x0041, 0, VR::CS, VM::M1, "Fluence Data Source" },
{ 0x3006, 0x0045, 0, VR::DS, VM::M3, "Contour Offset Vector" },
{ 0x6002, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 2" },
{ 0x6004, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 3" },
{ 0x6006, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 4" },
{ 0x6016, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0131[] = {
{ 0x3002, 0x0040, 0, VR::SQ, VM::M1, "Fluence Map Sequence" },
{ 0x3006, 0x0044, 0, VR::DS, VM::M1, "Contour Slab Thickness" },
{ 0x300A, 0x0048, 0, VR::SQ, VM::M1, "Beam Limiting Device Tolerance Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0132[] = {
{ 0x300A, 0x004F, 0, VR::FL, VM::M1, "Table Top Pitch Angle Tolerance" },
{ 0x6000, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated" },
{ 0x6002, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 2" },
{ 0x6004, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 3" },
{ 0x6010, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0133[] = {
{ 0x0014, 0x3050, 0, VR::OX, VM::M1, "Dark Current Counts" },
{ 0x3004, 0x0040, 0, VR::DS, VM::M3, "DVH Normalization Point" },
{ 0x3006, 0x0042, 0, VR::CS, VM::M1, "Contour Geometric Type" },
{ 0x300A, 0x004E, 0, VR::DS, VM::M1, "Table Top Eccentric Angle Tolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0134[] = {
{ 0x0014, 0x2012, 0, VR::SQ, VM::M1, "Indication Sequence" },
{ 0x6000, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position" },
{ 0x6002, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 2" },
{ 0x6006, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 4" },
{ 0x6012, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0135[] = {
{ 0x3004, 0x0042, 0, VR::DS, VM::M1, "DVH Normalization Dose Value" },
{ 0x3006, 0x0040, 0, VR::SQ, VM::M1, "Contour Sequence" },
{ 0x300A, 0x004C, 0, VR::DS, VM::M1, "Patient Support Angle Tolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0136[] = {
{ 0x0008, 0x0082, 0, VR::SQ, VM::M1, "Institution Code Sequence" },
{ 0x0014, 0x201C, 0, VR::CS, VM::M1, "Indication Disposition" },
{ 0x0018, 0x2010, 0, VR::DS, VM::M2, "Nominal Scanned Pixel Spacing" },
{ 0x0020, 0x00AA, 1, VR::IS, VM::M1, "Report Number" },
{ 0x0040, 0x08EA, 0, VR::SQ, VM::M1, "Measurement Units Code Sequence" },
{ 0x3008, 0x0041, 0, VR::SQ, VM::M1, "Ion Control Point Delivery Sequence" },
{ 0x300A, 0x0043, 0, VR::SH, VM::M1, "Tolerance Table Label" },
{ 0x6008, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 5" },
{ 0x600C, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 7" },
{ 0x600E, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 8" },
{ 0x601C, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0137[] = {
{ 0x0018, 0x0093, 0, VR::DS, VM::M1, "Percent Sampling" },
{ 0x3008, 0x0040, 0, VR::SQ, VM::M1, "Control Point Delivery Sequence" },
{ 0x300A, 0x0042, 0, VR::IS, VM::M1, "Tolerance Table Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0138[] = {
{ 0x0008, 0x0080, 0, VR::LO, VM::M1, "Institution Name" },
{ 0x0014, 0x201E, 0, VR::SQ, VM::M1, "Indication ROI Sequence" },
{ 0x0018, 0x0090, 0, VR::DS, VM::M1, "Data Collection Diameter" },
{ 0x600A, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 6" },
{ 0x600C, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 7" },
{ 0x600E, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 8" },
{ 0x601E, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0139[] = {
{ 0x0008, 0x0081, 0, VR::ST, VM::M1, "Institution Address" },
{ 0x0018, 0x0091, 0, VR::IS, VM::M1, "Echo Train Length" },
{ 0x3008, 0x0042, 0, VR::DS, VM::M1, "Specified Meterset" },
{ 0x300A, 0x0040, 0, VR::SQ, VM::M1, "Tolerance Table Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0140[] = {
{ 0x0014, 0x2018, 0, VR::ST, VM::M1, "Indication Description" },
{ 0x0028, 0x6120, 0, VR::SS, VM::M1, "TID Offset" },
{ 0x3008, 0x0045, 0, VR::FL, VM::M1, "Meterset Rate Set" },
{ 0x6008, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 5" },
{ 0x600A, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 6" },
{ 0x600C, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 7" },
{ 0x6018, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0141[] = {
{ 0x3008, 0x0044, 0, VR::DS, VM::M1, "Delivered Meterset" },
{ 0x300A, 0x0046, 0, VR::DS, VM::M1, "Beam Limiting Device Angle Tolerance" },
{ 0x300C, 0x0040, 0, VR::SQ, VM::M1, "Referenced Verification Image Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0142[] = {
{ 0x0014, 0x201A, 0, VR::CS, VM::M1TN, "Indication Type" },
{ 0x0018, 0x0094, 0, VR::DS, VM::M1, "Percent Phase Field of View" },
{ 0x3006, 0x0049, 0, VR::IS, VM::M1TN, "Attached Contours" },
{ 0x3008, 0x0047, 0, VR::FL, VM::M1TN, "Scan Spot Metersets Delivered" },
{ 0x6008, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 5" },
{ 0x600A, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 6" },
{ 0x600E, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 8" },
{ 0x601A, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0143[] = {
{ 0x0018, 0x0095, 0, VR::DS, VM::M1, "Pixel Bandwidth" },
{ 0x3006, 0x0048, 0, VR::IS, VM::M1, "Contour Number" },
{ 0x3008, 0x0046, 0, VR::FL, VM::M1, "Meterset Rate Delivered" },
{ 0x300A, 0x0044, 0, VR::DS, VM::M1, "Gantry Angle Tolerance" },
{ 0x300C, 0x0042, 0, VR::SQ, VM::M1, "Referenced Reference Image Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0144[] = {
{ 0x0010, 0x2000, 0, VR::LO, VM::M1TN, "Medical Alerts" },
{ 0x0014, 0x2004, 0, VR::IS, VM::M1, "Evaluator Number" },
{ 0x2000, 0x0010, 0, VR::IS, VM::M1, "Number of Copies" },
{ 0x2020, 0x0030, 0, VR::DS, VM::M1, "Requested Image Size" },
{ 0x2030, 0x0020, 0, VR::LO, VM::M1, "Text String" },
{ 0x2100, 0x0500, 1, VR::SQ, VM::M1, "Referenced Print Job Sequence (Pull Stored Print)" },
{ 0x6004, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 3" },
{ 0x6010, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 9" },
{ 0x6014, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 11" },
{ 0x6016, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0145[] = {
{ 0x0012, 0x0081, 0, VR::LO, VM::M1, "Clinical Trial Protocol Ethics Committee Name" },
{ 0x3002, 0x0052, 0, VR::SH, VM::M1, "Fluence Mode ID" },
{ 0x3004, 0x0054, 0, VR::CS, VM::M1, "DVH Volume Units" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0146[] = {
{ 0x0012, 0x0082, 0, VR::LO, VM::M1, "Clinical Trial Protocol Ethics Committee Approval Number" },
{ 0x0014, 0x2006, 0, VR::PN, VM::M1, "Evaluator Name" },
{ 0x0018, 0x0088, 0, VR::DS, VM::M1, "Spacing Between Slices" },
{ 0x3002, 0x0051, 0, VR::CS, VM::M1, "Fluence Mode" },
{ 0x6006, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 4" },
{ 0x6012, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 10" },
{ 0x6014, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 11" },
{ 0x6016, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0147[] = {
{ 0x0012, 0x0083, 0, VR::SQ, VM::M1, "Consent for Clinical Trial Use Sequence" },
{ 0x0018, 0x0089, 0, VR::IS, VM::M1, "Number of Phase Encoding Steps" },
{ 0x3002, 0x0050, 0, VR::SQ, VM::M1, "Primary Fluence Mode Sequence" },
{ 0x3004, 0x0056, 0, VR::IS, VM::M1, "DVH Number of Bins" },
{ 0x3008, 0x005A, 0, VR::IS, VM::M1, "Number of Fractions Delivered" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0148[] = {
{ 0x0012, 0x0084, 0, VR::CS, VM::M1, "Distribution Type" },
{ 0x6000, 0x0110, 1, VR::CS, VM::M1, "Overlay Format" },
{ 0x6010, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 9" },
{ 0x6012, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 10" },
{ 0x6014, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0149[] = {
{ 0x0012, 0x0085, 0, VR::CS, VM::M1, "Consent for Distribution Flag" },
{ 0x0014, 0x3040, 0, VR::SQ, VM::M1, "Dark Current Sequence" },
{ 0x3004, 0x0050, 0, VR::SQ, VM::M1, "DVH Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0150[] = {
{ 0x0014, 0x2002, 0, VR::SQ, VM::M1, "Evaluator Sequence" },
{ 0x6002, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 2" },
{ 0x6010, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 9" },
{ 0x6012, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 10" },
{ 0x6016, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0151[] = {
{ 0x3004, 0x0052, 0, VR::DS, VM::M1, "DVH Dose Scaling" },
{ 0x3006, 0x0050, 0, VR::DS, VM::M3T3N, "Contour Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0152[] = {
{ 0x0008, 0x0092, 0, VR::ST, VM::M1, "Referring Physician's Address" },
{ 0x0018, 0x0082, 0, VR::DS, VM::M1, "Inversion Time" },
{ 0x300A, 0x0053, 0, VR::DS, VM::M1, "Table Top Lateral Position Tolerance" },
{ 0x300C, 0x0055, 0, VR::SQ, VM::M1, "Brachy Referenced Dose Reference Sequence" },
{ 0x600C, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 7" },
{ 0x6018, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 13" },
{ 0x601C, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 15" },
{ 0x601E, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0153[] = {
{ 0x0018, 0x0083, 0, VR::DS, VM::M1, "Number of Averages" },
{ 0x0018, 0x2001, 0, VR::IS, VM::M1TN, "Page Number Vector" },
{ 0x3008, 0x0050, 0, VR::SQ, VM::M1, "Treatment Summary Calculated Dose Reference Sequence" },
{ 0x300A, 0x0052, 0, VR::DS, VM::M1, "Table Top Longitudinal Position Tolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0154[] = {
{ 0x0008, 0x0090, 0, VR::PN, VM::M1, "Referring Physician's Name" },
{ 0x0018, 0x0080, 0, VR::DS, VM::M1, "Repetition Time" },
{ 0x0018, 0x2002, 0, VR::SH, VM::M1TN, "Frame Label Vector" },
{ 0x300A, 0x0051, 0, VR::DS, VM::M1, "Table Top Vertical Position Tolerance" },
{ 0x600E, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 8" },
{ 0x601A, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 14" },
{ 0x601C, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 15" },
{ 0x601E, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0155[] = {
{ 0x0018, 0x0081, 0, VR::DS, VM::M1, "Echo Time" },
{ 0x0018, 0x2003, 0, VR::DS, VM::M1TN, "Frame Primary Angle Vector" },
{ 0x3008, 0x0052, 0, VR::DS, VM::M1, "Cumulative Dose to Dose Reference" },
{ 0x300A, 0x0050, 0, VR::FL, VM::M1, "Table Top Roll Angle Tolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0156[] = {
{ 0x0008, 0x0096, 0, VR::SQ, VM::M1, "Referring Physician Identification Sequence" },
{ 0x0014, 0x2008, 0, VR::IS, VM::M1, "Evaluation Attempt" },
{ 0x0018, 0x0086, 0, VR::IS, VM::M1TN, "Echo Number(s)" },
{ 0x0018, 0x2004, 0, VR::DS, VM::M1TN, "Frame Secondary Angle Vector" },
{ 0x0068, 0x6560, 0, VR::FD, VM::M2, "2D Point Coordinates" },
{ 0x300C, 0x0051, 0, VR::IS, VM::M1, "Referenced Dose Reference Number" },
{ 0x6008, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 5" },
{ 0x6018, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 13" },
{ 0x601A, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 14" },
{ 0x601C, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0157[] = {
{ 0x0018, 0x0087, 0, VR::DS, VM::M1, "Magnetic Field Strength" },
{ 0x0018, 0x2005, 0, VR::DS, VM::M1TN, "Slice Location Vector" },
{ 0x3004, 0x0058, 0, VR::DS, VM::M2T2N, "DVH Data" },
{ 0x3008, 0x0054, 0, VR::DA, VM::M1, "First Treatment Date" },
{ 0x300C, 0x0050, 0, VR::SQ, VM::M1, "Referenced Dose Reference Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0158[] = {
{ 0x0008, 0x0094, 0, VR::SH, VM::M1TN, "Referring Physician's Telephone Numbers" },
{ 0x0018, 0x0084, 0, VR::DS, VM::M1, "Imaging Frequency" },
{ 0x0018, 0x2006, 0, VR::SH, VM::M1TN, "Display Window Label Vector" },
{ 0x2000, 0x001E, 0, VR::SQ, VM::M1, "Printer Configuration Sequence" },
{ 0x300A, 0x0055, 0, VR::CS, VM::M1, "RT Plan Relationship" },
{ 0x600A, 0x0110, 1, VR::CS, VM::M1, "Overlay Format 6" },
{ 0x6018, 0x0102, 0, VR::US, VM::M1, "Overlay Bit Position 13" },
{ 0x601A, 0x0100, 0, VR::US, VM::M1, "Overlay Bits Allocated 14" },
{ 0x601E, 0x4000, 1, VR::LT, VM::M1, "Overlay Comments 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0159[] = {
{ 0x0018, 0x0085, 0, VR::SH, VM::M1, "Imaged Nucleus" },
{ 0x3008, 0x0056, 0, VR::DA, VM::M1, "Most Recent Treatment Date" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0160[] = {
{ 0x0014, 0x3075, 0, VR::DS, VM::M1, "Filter Thickness Used in Gain Calibration" },
{ 0x0024, 0x0086, 0, VR::CS, VM::M1, "Foveal Sensitivity Measured" },
{ 0x2000, 0x0020, 0, VR::CS, VM::M1, "Print Priority" },
{ 0x2010, 0x0030, 0, VR::CS, VM::M1, "Annotation Display Format ID" },
{ 0x2030, 0x0010, 0, VR::US, VM::M1, "Annotation Position" },
{ 0x2040, 0x0060, 1, VR::CS, VM::M1, "Overlay Magnification Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0161[] = {
{ 0x0014, 0x3074, 0, VR::LO, VM::M1, "Filter Material Used in Gain Calibration" },
{ 0x0024, 0x0087, 0, VR::FL, VM::M1, "Foveal Sensitivity" },
{ 0x0060, 0x3000, 0, VR::SQ, VM::M1, "Histogram Sequence" },
{ 0x3008, 0x0068, 0, VR::SQ, VM::M1, "Corrected Parameter Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0162[] = {
{ 0x0014, 0x3077, 0, VR::TM, VM::M1, "Time of Gain Calibration" },
{ 0x0020, 0x0080, 1, VR::CS, VM::M1TN, "Masking Image" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0163[] = {
{ 0x0014, 0x3076, 0, VR::DA, VM::M1, "Date of Gain Calibration" },
{ 0x0024, 0x0085, 0, VR::SQ, VM::M1, "Localized Deviation Probability Sequence" },
{ 0x0060, 0x3002, 0, VR::US, VM::M1, "Histogram Number of Bins" },
{ 0x3008, 0x006A, 0, VR::FL, VM::M1, "Correction Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0164[] = {
{ 0x0014, 0x2030, 0, VR::SQ, VM::M1, "Indication Physical Property Sequence" },
{ 0x0014, 0x3071, 0, VR::DS, VM::M1, "KV Used in Gain Calibration" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0165[] = {
{ 0x0014, 0x3070, 0, VR::OX, VM::M1, "Air Counts" },
{ 0x0024, 0x0083, 0, VR::SQ, VM::M1, "Global Deviation Probability Sequence" },
{ 0x0060, 0x3004, 0, VR::XS, VM::M1, "Histogram First Bin Value" },
{ 0x3004, 0x0060, 0, VR::SQ, VM::M1, "DVH Referenced ROI Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0166[] = {
{ 0x0014, 0x2032, 0, VR::SH, VM::M1, "Property Label" },
{ 0x0014, 0x3073, 0, VR::DS, VM::M1, "Number of Frames Used for Integration" },
{ 0x0024, 0x0080, 0, VR::CS, VM::M1, "Corrected Localized Deviation From Normal Probability Calculated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0167[] = {
{ 0x0014, 0x3072, 0, VR::DS, VM::M1, "MA Used in Gain Calibration" },
{ 0x0024, 0x0081, 0, VR::FL, VM::M1, "Corrected Localized Deviation From Normal Probability" },
{ 0x0060, 0x3006, 0, VR::XS, VM::M1, "Histogram Last Bin Value" },
{ 0x3004, 0x0062, 0, VR::CS, VM::M1, "DVH ROI Contribution Type" },
{ 0x300C, 0x006A, 0, VR::IS, VM::M1, "Referenced Patient Setup Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0168[] = {
{ 0x0018, 0x2030, 0, VR::DS, VM::M1, "Rotation of Scanned Film" },
{ 0x0028, 0x0082, 1, VR::US, VM::M1TN, "Predictor Constants" },
{ 0x0028, 0x2000, 0, VR::OB, VM::M1, "ICC Profile" },
{ 0x3008, 0x0061, 0, VR::AT, VM::M1, "Parameter Sequence Pointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0169[] = {
{ 0x0060, 0x3008, 0, VR::US, VM::M1, "Histogram Bin Width" },
{ 0x3008, 0x0060, 0, VR::SQ, VM::M1, "Override Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0170[] = {
{ 0x0028, 0x0080, 1, VR::US, VM::M1, "Predictor Rows" },
{ 0x3008, 0x0063, 0, VR::IS, VM::M1, "Parameter Item Index" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0171[] = {
{ 0x0028, 0x0081, 1, VR::US, VM::M1, "Predictor Columns" },
{ 0x3008, 0x0062, 0, VR::AT, VM::M1, "Override Parameter Pointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0172[] = {
{ 0x0028, 0x6100, 0, VR::SQ, VM::M1, "Mask Subtraction Sequence" },
{ 0x0068, 0x6550, 0, VR::SQ, VM::M1, "2D Point Coordinates Sequence" },
{ 0x3008, 0x0065, 0, VR::AT, VM::M1, "Parameter Pointer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0173[] = {
{ 0x0028, 0x6101, 0, VR::CS, VM::M1, "Mask Operation" },
{ 0x3008, 0x0064, 0, VR::IS, VM::M1, "Measured Dose Reference Number" },
{ 0x300C, 0x0060, 0, VR::SQ, VM::M1, "Referenced Structure Set Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0174[] = {
{ 0x0024, 0x0088, 0, VR::FL, VM::M1, "Visual Field Test Duration" },
{ 0x0028, 0x6102, 0, VR::US, VM::M2T2N, "Applicable Frame Range" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0175[] = {
{ 0x0024, 0x0089, 0, VR::SQ, VM::M1, "Visual Field Test Point Sequence" },
{ 0x3008, 0x0066, 0, VR::ST, VM::M1, "Override Reason" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0176[] = {
{ 0x0024, 0x0096, 0, VR::FL, VM::M1, "Retest Sensitivity Value" },
{ 0x2000, 0x0030, 0, VR::CS, VM::M1, "Medium Type" },
{ 0x2020, 0x0010, 0, VR::US, VM::M1, "Image Box Position" },
{ 0x2040, 0x0070, 1, VR::CS, VM::M1, "Overlay Smoothing Type" },
{ 0x300A, 0x007B, 0, VR::LT, VM::M1, "Fraction Pattern" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0177[] = {
{ 0x0024, 0x0097, 0, VR::SQ, VM::M1, "Visual Field Test Point Normals Sequence" },
{ 0x0060, 0x3010, 0, VR::LO, VM::M1, "Histogram Explanation" },
{ 0x3004, 0x0074, 0, VR::DS, VM::M1, "DVH Mean Dose" },
{ 0x3008, 0x0078, 0, VR::DS, VM::M1, "Start Meterset" },
{ 0x300A, 0x007A, 0, VR::IS, VM::M1, "Repeat Fraction Cycle Length" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0178[] = {
{ 0x0024, 0x0094, 0, VR::FL, VM::M1, "Sensitivity Value" },
{ 0x2040, 0x0072, 1, VR::CS, VM::M1, "Overlay or Image Magnification" },
{ 0x300A, 0x0079, 0, VR::IS, VM::M1, "Number of Fraction Pattern Digits Per Day" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0179[] = {
{ 0x0024, 0x0095, 0, VR::CS, VM::M1, "Retest Stimulus Seen" },
{ 0x3008, 0x007A, 0, VR::DS, VM::M1, "End Meterset" },
{ 0x300A, 0x0078, 0, VR::IS, VM::M1, "Number of Fractions Planned" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0180[] = {
{ 0x0024, 0x0092, 0, VR::FL, VM::M1, "Age Corrected Sensitivity Deviation Value" },
{ 0x0076, 0x00C0, 0, VR::US, VM::M1, "Component 2 Referenced Mating Feature ID" },
{ 0x2040, 0x0074, 1, VR::US, VM::M1, "Magnify to Number of Columns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0181[] = {
{ 0x0014, 0x3060, 0, VR::SQ, VM::M1, "Gain Correction Reference Sequence" },
{ 0x0024, 0x0093, 0, VR::CS, VM::M1, "Stimulus Results" },
{ 0x3004, 0x0070, 0, VR::DS, VM::M1, "DVH Minimum Dose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0182[] = {
{ 0x0024, 0x0090, 0, VR::FL, VM::M1, "Visual Field Test Point X-Coordinate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0183[] = {
{ 0x0024, 0x0091, 0, VR::FL, VM::M1, "Visual Field Test Point Y-Coordinate" },
{ 0x3004, 0x0072, 0, VR::DS, VM::M1, "DVH Maximum Dose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0184[] = {
{ 0x0018, 0x2020, 0, VR::CS, VM::M1, "Digitizing Device Transport Direction" },
{ 0x0028, 0x0092, 1, VR::US, VM::M1, "Block Columns" },
{ 0x0028, 0x6114, 0, VR::FL, VM::M2, "Mask Sub-pixel Shift" },
{ 0x0040, 0x08DA, 1, VR::SQ, VM::M1, "Coordinate System Axis Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0185[] = {
{ 0x0028, 0x0093, 1, VR::US, VM::M1, "Row Overlap" },
{ 0x0068, 0x6545, 0, VR::SQ, VM::M1, "Planning Landmark Identification Code Sequence" },
{ 0x3008, 0x0070, 0, VR::SQ, VM::M1, "Calculated Dose Reference Sequence" },
{ 0x300A, 0x0072, 0, VR::LO, VM::M1, "Fraction Group Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0186[] = {
{ 0x0028, 0x0090, 1, VR::CS, VM::M1, "Blocked Pixels" },
{ 0x0040, 0x08D8, 1, VR::SQ, VM::M1, "Pixel Spacing Sequence" },
{ 0x300A, 0x0071, 0, VR::IS, VM::M1, "Fraction Group Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0187[] = {
{ 0x0028, 0x0091, 1, VR::US, VM::M1, "Block Rows" },
{ 0x3008, 0x0072, 0, VR::IS, VM::M1, "Calculated Dose Reference Number" },
{ 0x300A, 0x0070, 0, VR::SQ, VM::M1, "Fraction Group Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0188[] = {
{ 0x0028, 0x6110, 0, VR::US, VM::M1TN, "Mask Frame Numbers" },
{ 0x0068, 0x6540, 0, VR::LO, VM::M1, "Planning Landmark Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0189[] = {
{ 0x3008, 0x0074, 0, VR::ST, VM::M1, "Calculated Dose Reference Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0190[] = {
{ 0x0024, 0x0098, 0, VR::FL, VM::M1, "Quantified Defect" },
{ 0x0028, 0x0094, 1, VR::US, VM::M1, "Column Overlap" },
{ 0x0028, 0x6112, 0, VR::US, VM::M1, "Contrast Frame Averaging" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0191[] = {
{ 0x3008, 0x0076, 0, VR::DS, VM::M1, "Calculated Dose Reference Dose Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0192[] = {
{ 0x0040, 0x2001, 1, VR::LO, VM::M1, "Reason for the Imaging Service Request" },
{ 0x3002, 0x0002, 0, VR::SH, VM::M1, "RT Image Label" },
{ 0x3004, 0x0004, 0, VR::CS, VM::M1, "Dose Type" },
{ 0x3006, 0x0006, 0, VR::ST, VM::M1, "Structure Set Description" },
{ 0x300A, 0x000A, 0, VR::CS, VM::M1, "Plan Intent" },
{ 0x300C, 0x000C, 0, VR::IS, VM::M1, "Referenced Brachy Application Setup Number" },
{ 0x5014, 0x2500, 1, VR::LO, VM::M1, "Curve Label 11" },
{ 0x6004, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 3" },
{ 0x6006, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 4" },
{ 0x6014, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0193[] = {
{ 0x2000, 0x0040, 0, VR::CS, VM::M1, "Film Destination" },
{ 0x2010, 0x0050, 0, VR::CS, VM::M1, "Film Size ID" },
{ 0x2050, 0x0010, 0, VR::SQ, VM::M1, "Presentation LUT Sequence" },
{ 0x2100, 0x0140, 1, VR::AE, VM::M1, "Destination AE" },
{ 0x3002, 0x0003, 0, VR::LO, VM::M1, "RT Image Name" },
{ 0x300A, 0x000B, 0, VR::LO, VM::M1TN, "Treatment Sites" },
{ 0x6004, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 3" },
{ 0x6006, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0194[] = {
{ 0x0010, 0x1090, 0, VR::LO, VM::M1, "Medical Record Locator" },
{ 0x3004, 0x0006, 0, VR::LO, VM::M1, "Dose Comment" },
{ 0x3006, 0x0004, 0, VR::LO, VM::M1, "Structure Set Name" },
{ 0x300C, 0x000E, 0, VR::IS, VM::M1, "Referenced Source Number" },
{ 0x5016, 0x2500, 1, VR::LO, VM::M1, "Curve Label 12" },
{ 0x6004, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 3" },
{ 0x6006, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 4" },
{ 0x6016, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0195[] = {
{ 0x0078, 0x00B8, 0, VR::US, VM::M1, "Implant Template Group Variation Dimension Rank" },
{ 0x2010, 0x0052, 0, VR::CS, VM::M1, "Printer Resolution ID" },
{ 0x300A, 0x0009, 0, VR::LO, VM::M1TN, "Treatment Protocols" },
{ 0x6004, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 3" },
{ 0x6006, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0196[] = {
{ 0x0018, 0x9296, 0, VR::FD, VM::M1, "Chemical Shift Maximum Integration Limit in ppm" },
{ 0x0040, 0x2005, 0, VR::TM, VM::M1, "Issue Time of Imaging Service Request" },
{ 0x3006, 0x0002, 0, VR::SH, VM::M1, "Structure Set Label" },
{ 0x300A, 0x000E, 0, VR::ST, VM::M1, "Prescription Description" },
{ 0x300C, 0x0008, 0, VR::DS, VM::M1, "Start Cumulative Meterset Weight" },
{ 0x5010, 0x2500, 1, VR::LO, VM::M1, "Curve Label 9" },
{ 0x6000, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray" },
{ 0x6002, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 2" },
{ 0x6010, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0197[] = {
{ 0x0014, 0x3011, 0, VR::DS, VM::M1, "Internal Detector Frame Time" },
{ 0x0040, 0x2004, 0, VR::DA, VM::M1, "Issue Date of Imaging Service Request" },
{ 0x0046, 0x0080, 0, VR::SQ, VM::M1, "Flat Keratometric Axis Sequence" },
{ 0x0076, 0x00B0, 0, VR::US, VM::M1, "Component 2 Referenced Mating Feature Set ID" },
{ 0x2010, 0x0054, 0, VR::CS, VM::M1, "Default Printer Resolution ID" },
{ 0x3004, 0x0001, 0, VR::CS, VM::M1, "DVH Type" },
{ 0x300C, 0x0009, 0, VR::DS, VM::M1, "End Cumulative Meterset Weight" },
{ 0x6000, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red" },
{ 0x6002, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0198[] = {
{ 0x0014, 0x3012, 0, VR::DS, VM::M1, "Number of Frames Integrated" },
{ 0x0040, 0x2007, 1, VR::SH, VM::M1, "Filler Order Number / Imaging Service Request (Retired)" },
{ 0x3002, 0x0004, 0, VR::ST, VM::M1, "RT Image Description" },
{ 0x3004, 0x0002, 0, VR::CS, VM::M1, "Dose Units" },
{ 0x300A, 0x000C, 0, VR::CS, VM::M1, "RT Plan Geometry" },
{ 0x300C, 0x000A, 0, VR::SQ, VM::M1, "Referenced Brachy Application Setup Sequence" },
{ 0x300E, 0x0008, 0, VR::PN, VM::M1, "Reviewer Name" },
{ 0x5012, 0x2500, 1, VR::LO, VM::M1, "Curve Label 10" },
{ 0x6000, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green" },
{ 0x6002, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 2" },
{ 0x6012, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0199[] = {
{ 0x0018, 0x9295, 0, VR::FD, VM::M1, "Chemical Shift Minimum Integration Limit in ppm" },
{ 0x0040, 0x2006, 1, VR::SH, VM::M1, "Placer Order Number / Imaging Service Request (Retired)" },
{ 0x0054, 0x0090, 0, VR::US, VM::M1TN, "Angular View Vector" },
{ 0x6000, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue" },
{ 0x6002, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0200[] = {
{ 0x0040, 0x2009, 0, VR::SH, VM::M1, "Order Enterer's Location" },
{ 0x3002, 0x000A, 0, VR::CS, VM::M1, "Reported Values Origin" },
{ 0x3004, 0x000C, 0, VR::DS, VM::M2TN, "Grid Frame Offset Vector" },
{ 0x300A, 0x0002, 0, VR::SH, VM::M1, "RT Plan Label" },
{ 0x300A, 0x0412, 0, VR::FL, VM::M3, "Control Point Orientation" },
{ 0x300C, 0x0004, 0, VR::SQ, VM::M1, "Referenced Beam Sequence" },
{ 0x501C, 0x2500, 1, VR::LO, VM::M1, "Curve Label 15" },
{ 0x600C, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 7" },
{ 0x600E, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 8" },
{ 0x601C, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0201[] = {
{ 0x0008, 0x3001, 0, VR::SQ, VM::M1, "Alternate Representation Sequence" },
{ 0x0040, 0x2008, 0, VR::PN, VM::M1, "Order Entered By" },
{ 0x0078, 0x00B2, 0, VR::LO, VM::M1, "Implant Template Group Variation Dimension Name" },
{ 0x300A, 0x0003, 0, VR::LO, VM::M1, "RT Plan Name" },
{ 0x600C, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 7" },
{ 0x600E, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0202[] = {
{ 0x0008, 0x1080, 0, VR::LO, VM::M1TN, "Admitting Diagnoses Description" },
{ 0x0018, 0x1090, 0, VR::IS, VM::M1, "Cardiac Number of Images" },
{ 0x0018, 0x1480, 0, VR::DS, VM::M1, "Tomo Time" },
{ 0x3004, 0x000E, 0, VR::DS, VM::M1, "Dose Grid Scaling" },
{ 0x300A, 0x0410, 0, VR::SQ, VM::M1, "Motion Synchronization Sequence" },
{ 0x300C, 0x0006, 0, VR::IS, VM::M1, "Referenced Beam Number" },
{ 0x300E, 0x0004, 0, VR::DA, VM::M1, "Review Date" },
{ 0x501E, 0x2500, 1, VR::LO, VM::M1, "Curve Label 16" },
{ 0x600C, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 7" },
{ 0x600E, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 8" },
{ 0x601E, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0203[] = {
{ 0x0078, 0x00B0, 0, VR::SQ, VM::M1, "Implant Template Group Variation Dimension Sequence" },
{ 0x300C, 0x0007, 0, VR::IS, VM::M1, "Referenced Reference Image Number" },
{ 0x300E, 0x0005, 0, VR::TM, VM::M1, "Review Time" },
{ 0x600C, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 7" },
{ 0x600E, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0204[] = {
{ 0x3002, 0x000E, 0, VR::DS, VM::M1, "X-Ray Image Receptor Angle" },
{ 0x3004, 0x0008, 0, VR::DS, VM::M3, "Normalization Point" },
{ 0x300A, 0x0006, 0, VR::DA, VM::M1, "RT Plan Date" },
{ 0x300E, 0x0002, 0, VR::CS, VM::M1, "Approval Status" },
{ 0x5018, 0x2500, 1, VR::LO, VM::M1, "Curve Label 13" },
{ 0x6008, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 5" },
{ 0x600A, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 6" },
{ 0x6018, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0205[] = {
{ 0x0068, 0x6530, 0, VR::US, VM::M1, "Planning Landmark ID" },
{ 0x0078, 0x00B6, 0, VR::US, VM::M1, "Referenced Implant Template Group Member ID" },
{ 0x300A, 0x0007, 0, VR::TM, VM::M1, "RT Plan Time" },
{ 0x6008, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 5" },
{ 0x600A, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0206[] = {
{ 0x0008, 0x1084, 0, VR::SQ, VM::M1, "Admitting Diagnoses Code Sequence" },
{ 0x0018, 0x1094, 0, VR::IS, VM::M1, "Trigger Window" },
{ 0x3002, 0x000C, 0, VR::CS, VM::M1, "RT Image Plane" },
{ 0x3004, 0x000A, 0, VR::CS, VM::M1, "Dose Summation Type" },
{ 0x3006, 0x0008, 0, VR::DA, VM::M1, "Structure Set Date" },
{ 0x300A, 0x0004, 0, VR::ST, VM::M1, "RT Plan Description" },
{ 0x300C, 0x0002, 0, VR::SQ, VM::M1, "Referenced RT Plan Sequence" },
{ 0x501A, 0x2500, 1, VR::LO, VM::M1, "Curve Label 14" },
{ 0x6008, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 5" },
{ 0x600A, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 6" },
{ 0x601A, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0207[] = {
{ 0x0078, 0x00B4, 0, VR::SQ, VM::M1, "Implant Template Group Variation Dimension Rank Sequence" },
{ 0x3002, 0x000D, 0, VR::DS, VM::M3, "X-Ray Image Receptor Translation" },
{ 0x3006, 0x0009, 0, VR::TM, VM::M1, "Structure Set Time" },
{ 0x6008, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 5" },
{ 0x600A, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0208[] = {
{ 0x0046, 0x0095, 0, VR::CS, VM::M1, "Optotype Presentation" },
{ 0x2040, 0x0011, 1, VR::US, VM::M1T99, "Referenced Overlay Plane Groups" },
{ 0x3002, 0x0012, 0, VR::DS, VM::M2, "RT Image Position" },
{ 0x3004, 0x0014, 0, VR::CS, VM::M1T3, "Tissue Heterogeneity Correction" },
{ 0x3006, 0x0016, 0, VR::SQ, VM::M1, "Contour Image Sequence" },
{ 0x300A, 0x001A, 0, VR::DS, VM::M1, "Nominal Prior Dose" },
{ 0x5004, 0x2500, 1, VR::LO, VM::M1, "Curve Label 3" },
{ 0x6004, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 3" },
{ 0x6014, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 11" },
{ 0x6016, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0209[] = {
{ 0x0040, 0x2010, 0, VR::SH, VM::M1, "Order Callback Phone Number" },
{ 0x0040, 0x2400, 0, VR::LT, VM::M1, "Imaging Service Request Comments" },
{ 0x0046, 0x0094, 0, VR::CS, VM::M1, "Optotype" },
{ 0x2000, 0x0050, 0, VR::LO, VM::M1, "Film Session Label" },
{ 0x2010, 0x0040, 0, VR::CS, VM::M1, "Film Orientation" },
{ 0x2040, 0x0010, 1, VR::SQ, VM::M1, "Referenced Overlay Plane Sequence" },
{ 0x6014, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 11" },
{ 0x6016, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0210[] = {
{ 0x0010, 0x1080, 0, VR::LO, VM::M1, "Military Rank" },
{ 0x0018, 0x1088, 0, VR::IS, VM::M1, "Heart Rate" },
{ 0x0046, 0x0097, 0, VR::SQ, VM::M1, "Subjective Refraction Right Eye Sequence" },
{ 0x3002, 0x0010, 0, VR::DS, VM::M6, "RT Image Orientation" },
{ 0x3006, 0x0014, 0, VR::SQ, VM::M1, "RT Referenced Series Sequence" },
{ 0x300A, 0x0018, 0, VR::DS, VM::M3, "Dose Reference Point Coordinates" },
{ 0x5006, 0x2500, 1, VR::LO, VM::M1, "Curve Label 4" },
{ 0x6006, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 4" },
{ 0x6014, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 11" },
{ 0x6016, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0211[] = {
{ 0x0010, 0x1081, 0, VR::LO, VM::M1, "Branch of Service" },
{ 0x3002, 0x0011, 0, VR::DS, VM::M2, "Image Plane Pixel Spacing" },
{ 0x6014, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 11" },
{ 0x6016, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0212[] = {
{ 0x3004, 0x0010, 0, VR::SQ, VM::M1, "RT Dose ROI Sequence" },
{ 0x3006, 0x0012, 0, VR::SQ, VM::M1, "RT Referenced Study Sequence" },
{ 0x5000, 0x2500, 1, VR::LO, VM::M1, "Curve Label" },
{ 0x6000, 0x1500, 0, VR::LO, VM::M1, "Overlay Label" },
{ 0x6010, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 9" },
{ 0x6012, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0213[] = {
{ 0x0076, 0x00A0, 0, VR::US, VM::M1, "Component 2 Referenced ID" },
{ 0x6010, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 9" },
{ 0x6012, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0214[] = {
{ 0x0040, 0x2017, 0, VR::LO, VM::M1, "Filler Order Number / Imaging Service Request" },
{ 0x0054, 0x0081, 0, VR::US, VM::M1, "Number of Slices" },
{ 0x3004, 0x0012, 0, VR::DS, VM::M1, "Dose Value" },
{ 0x3006, 0x0010, 0, VR::SQ, VM::M1, "Referenced Frame of Reference Sequence" },
{ 0x5002, 0x2500, 1, VR::LO, VM::M1, "Curve Label 2" },
{ 0x6002, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 2" },
{ 0x6010, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 9" },
{ 0x6012, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0215[] = {
{ 0x0040, 0x2016, 0, VR::LO, VM::M1, "Placer Order Number / Imaging Service Request" },
{ 0x0046, 0x0092, 0, VR::CS, VM::M1, "Background Color" },
{ 0x0054, 0x0080, 0, VR::US, VM::M1TN, "Slice Vector" },
{ 0x6010, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 9" },
{ 0x6012, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0216[] = {
{ 0x0008, 0x3010, 0, VR::UI, VM::M1, "Irradiation Event UID" },
{ 0x0018, 0x1082, 0, VR::IS, VM::M1, "High R-R Value" },
{ 0x0040, 0xA601, 1, VR::CS, VM::M1, "Observer Context Flag (Trial)" },
{ 0x3008, 0x0010, 0, VR::SQ, VM::M1, "Measured Dose Reference Sequence" },
{ 0x300A, 0x0012, 0, VR::IS, VM::M1, "Dose Reference Number" },
{ 0x300A, 0x0402, 0, VR::ST, VM::M1, "Setup Image Comment" },
{ 0x500C, 0x2500, 1, VR::LO, VM::M1, "Curve Label 7" },
{ 0x600C, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 7" },
{ 0x601C, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 15" },
{ 0x601E, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0217[] = {
{ 0x0018, 0x1083, 0, VR::IS, VM::M1, "Intervals Acquired" },
{ 0x0040, 0xA600, 1, VR::CS, VM::M1, "Observation Subject Context Flag (Trial)" },
{ 0x300A, 0x0013, 0, VR::UI, VM::M1, "Dose Reference UID" },
{ 0x601C, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 15" },
{ 0x601E, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0218[] = {
{ 0x0008, 0x1090, 0, VR::LO, VM::M1, "Manufacturer's Model Name" },
{ 0x0018, 0x1080, 0, VR::CS, VM::M1, "Beat Rejection Flag" },
{ 0x0018, 0x1490, 0, VR::CS, VM::M1, "Tomo Type" },
{ 0x0040, 0xA603, 1, VR::CS, VM::M1, "Procedure Context Flag (Trial)" },
{ 0x3008, 0x0012, 0, VR::ST, VM::M1, "Measured Dose Description" },
{ 0x300A, 0x0010, 0, VR::SQ, VM::M1, "Dose Reference Sequence" },
{ 0x500E, 0x2500, 1, VR::LO, VM::M1, "Curve Label 8" },
{ 0x600E, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 8" },
{ 0x601C, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 15" },
{ 0x601E, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0219[] = {
{ 0x0018, 0x1081, 0, VR::IS, VM::M1, "Low R-R Value" },
{ 0x0018, 0x1491, 0, VR::CS, VM::M1, "Tomo Class" },
{ 0x0078, 0x00A0, 0, VR::FD, VM::M4, "2D Implant Template Group Member Matching Axes" },
{ 0x300A, 0x0401, 0, VR::SQ, VM::M1, "Referenced Setup Image Sequence" },
{ 0x601C, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 15" },
{ 0x601E, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0220[] = {
{ 0x0018, 0x1086, 0, VR::IS, VM::M1, "Skip Beats" },
{ 0x3008, 0x0014, 0, VR::CS, VM::M1, "Measured Dose Type" },
{ 0x300A, 0x0016, 0, VR::LO, VM::M1, "Dose Reference Description" },
{ 0x5008, 0x2500, 1, VR::LO, VM::M1, "Curve Label 5" },
{ 0x6008, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 5" },
{ 0x6018, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 13" },
{ 0x601A, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0221[] = {
{ 0x0046, 0x0098, 0, VR::SQ, VM::M1, "Subjective Refraction Left Eye Sequence" },
{ 0x0068, 0x6520, 0, VR::SQ, VM::M1, "Planning Landmark Plane Sequence" },
{ 0x6018, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 13" },
{ 0x601A, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0222[] = {
{ 0x0018, 0x1084, 0, VR::IS, VM::M1, "Intervals Rejected" },
{ 0x3008, 0x0016, 0, VR::DS, VM::M1, "Measured Dose Value" },
{ 0x300A, 0x0014, 0, VR::CS, VM::M1, "Dose Reference Structure Type" },
{ 0x500A, 0x2500, 1, VR::LO, VM::M1, "Curve Label 6" },
{ 0x600A, 0x1500, 0, VR::LO, VM::M1, "Overlay Label 6" },
{ 0x6018, 0x1102, 1, VR::US, VM::M1, "Overlay Descriptor - Green 13" },
{ 0x601A, 0x1100, 1, VR::US, VM::M1, "Overlay Descriptor - Gray 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0223[] = {
{ 0x0018, 0x1085, 0, VR::LO, VM::M1, "PVC Rejection" },
{ 0x0018, 0x1495, 0, VR::IS, VM::M1, "Number of Tomosynthesis Source Images" },
{ 0x300A, 0x0015, 0, VR::CS, VM::M1, "Nominal Beam Energy Unit" },
{ 0x6018, 0x1103, 1, VR::US, VM::M1, "Overlay Descriptor - Blue 13" },
{ 0x601A, 0x1101, 1, VR::US, VM::M1, "Overlay Descriptor - Red 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0224[] = {
{ 0x2000, 0x0061, 0, VR::IS, VM::M1, "Maximum Memory Allocation" },
{ 0x3002, 0x0022, 0, VR::DS, VM::M1, "Radiation Machine SAD" },
{ 0x3006, 0x0026, 0, VR::LO, VM::M1, "ROI Name" },
{ 0x300A, 0x002A, 0, VR::DS, VM::M1, "Organ at Risk Full-volume Dose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0225[] = {
{ 0x2000, 0x0060, 0, VR::IS, VM::M1, "Memory Allocation" },
{ 0x2020, 0x0040, 0, VR::CS, VM::M1, "Requested Decimate/Crop Behavior" },
{ 0x2040, 0x0020, 1, VR::SQ, VM::M1, "Overlay Pixel Data Sequence" },
{ 0x2100, 0x0160, 0, VR::SH, VM::M1, "Owner ID" },
{ 0x300A, 0x002B, 0, VR::DS, VM::M1, "Organ at Risk Limit Dose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0226[] = {
{ 0x2000, 0x0063, 1, VR::CS, VM::M1, "Collation Flag" },
{ 0x3002, 0x0020, 0, VR::SH, VM::M1, "Radiation Machine Name" },
{ 0x3006, 0x0024, 0, VR::UI, VM::M1, "Referenced Frame of Reference UID" },
{ 0x3008, 0x002A, 0, VR::CS, VM::M1, "Treatment Termination Status" },
{ 0x300A, 0x0028, 0, VR::DS, VM::M1, "Target Underdose Volume Fraction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0227[] = {
{ 0x2000, 0x0062, 1, VR::CS, VM::M1, "Color Image Printing Flag" },
{ 0x3008, 0x002B, 0, VR::SH, VM::M1, "Treatment Termination Code" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0228[] = {
{ 0x2000, 0x0065, 1, VR::CS, VM::M1, "Annotation Flag" },
{ 0x3002, 0x0026, 0, VR::DS, VM::M1, "RT Image SID" },
{ 0x3006, 0x0022, 0, VR::IS, VM::M1, "ROI Number" },
{ 0x3008, 0x002C, 0, VR::CS, VM::M1, "Treatment Verification Status" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0229[] = {
{ 0x0076, 0x0090, 0, VR::US, VM::M1, "Component 1 Referenced Mating Feature ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0230[] = {
{ 0x2000, 0x0067, 1, VR::CS, VM::M1, "Image Overlay Flag" },
{ 0x3002, 0x0024, 0, VR::DS, VM::M1, "Radiation Machine SSD" },
{ 0x3006, 0x0020, 0, VR::SQ, VM::M1, "Structure Set ROI Sequence" },
{ 0x300A, 0x002C, 0, VR::DS, VM::M1, "Organ at Risk Maximum Dose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0231[] = {
{ 0x300A, 0x002D, 0, VR::DS, VM::M1, "Organ at Risk Overdose Volume Fraction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0232[] = {
{ 0x0028, 0x3000, 0, VR::SQ, VM::M1, "Modality LUT Sequence" },
{ 0x2000, 0x0069, 1, VR::CS, VM::M1, "Presentation LUT Flag" },
{ 0x3008, 0x0020, 0, VR::SQ, VM::M1, "Treatment Session Beam Sequence" },
{ 0x300A, 0x0022, 0, VR::DS, VM::M1, "Delivery Warning Dose" },
{ 0x300A, 0x0432, 0, VR::CS, VM::M1, "Applicator Aperture Shape" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0233[] = {
{ 0x3008, 0x0021, 0, VR::SQ, VM::M1, "Treatment Session Ion Beam Sequence" },
{ 0x300A, 0x0023, 0, VR::DS, VM::M1, "Delivery Maximum Dose" },
{ 0x300A, 0x0433, 0, VR::FL, VM::M1, "Applicator Opening" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0234[] = {
{ 0x0028, 0x1080, 1, VR::CS, VM::M1, "Gray Scale" },
{ 0x0028, 0x3002, 0, VR::XS, VM::M3, "LUT Descriptor" },
{ 0x3002, 0x0028, 0, VR::DS, VM::M1, "Source to Reference Object Distance" },
{ 0x3006, 0x002C, 0, VR::DS, VM::M1, "ROI Volume" },
{ 0x3008, 0x0022, 0, VR::IS, VM::M1, "Current Fraction Number" },
{ 0x300A, 0x0020, 0, VR::CS, VM::M1, "Dose Reference Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0235[] = {
{ 0x0028, 0x3003, 0, VR::LO, VM::M1, "LUT Explanation" },
{ 0x0078, 0x0090, 0, VR::FD, VM::M2, "2D Implant Template Group Member Matching Point" },
{ 0x2000, 0x006A, 1, VR::CS, VM::M1, "Image Box Presentation LUT Flag" },
{ 0x3002, 0x0029, 0, VR::IS, VM::M1, "Fraction Number" },
{ 0x300A, 0x0021, 0, VR::DS, VM::M1, "Constraint Weight" },
{ 0x300A, 0x0431, 0, VR::SQ, VM::M1, "Applicator Geometry Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0236[] = {
{ 0x0028, 0x3004, 0, VR::LO, VM::M1, "Modality LUT Type" },
{ 0x3006, 0x002A, 0, VR::IS, VM::M3, "ROI Display Color" },
{ 0x3008, 0x0024, 0, VR::DA, VM::M1, "Treatment Control Point Date" },
{ 0x300A, 0x0026, 0, VR::DS, VM::M1, "Target Prescription Dose" },
{ 0x300A, 0x0436, 0, VR::FL, VM::M1, "Source to Applicator Mounting Position Distance" },
{ 0x300C, 0x0020, 0, VR::SQ, VM::M1, "Referenced Fraction Group Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0237[] = {
{ 0x0040, 0xA224, 1, VR::ST, VM::M1, "Identification Description (Trial)" },
{ 0x0068, 0x6510, 0, VR::SQ, VM::M1, "Planning Landmark Line Sequence" },
{ 0x3008, 0x0025, 0, VR::TM, VM::M1, "Treatment Control Point Time" },
{ 0x300A, 0x0027, 0, VR::DS, VM::M1, "Target Maximum Dose" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0238[] = {
{ 0x0028, 0x3006, 0, VR::OW, VM::M1, "LUT Data" },
{ 0x3006, 0x0028, 0, VR::ST, VM::M1, "ROI Description" },
{ 0x300A, 0x0434, 0, VR::FL, VM::M1, "Applicator Opening X" },
{ 0x300C, 0x0022, 0, VR::IS, VM::M1, "Referenced Fraction Group Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0239[] = {
{ 0x300A, 0x0025, 0, VR::DS, VM::M1, "Target Minimum Dose" },
{ 0x300A, 0x0435, 0, VR::FL, VM::M1, "Applicator Opening Y" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0240[] = {
{ 0x0014, 0x3024, 0, VR::DS, VM::M1, "Horizontal Offset of Sensor" },
{ 0x0022, 0x1090, 0, VR::SQ, VM::M1, "IOL Power Sequence" },
{ 0x0070, 0x0083, 0, VR::TM, VM::M1, "Presentation Creation Time" },
{ 0x3002, 0x0032, 0, VR::DS, VM::M1, "Meterset Exposure" },
{ 0x3006, 0x0036, 0, VR::CS, VM::M1, "ROI Generation Algorithm" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0241[] = {
{ 0x0020, 0x3401, 1, VR::CS, VM::M1, "Modifying Device ID" },
{ 0x0070, 0x0082, 0, VR::DA, VM::M1, "Presentation Creation Date" },
{ 0x0072, 0x0080, 0, VR::SQ, VM::M1, "Selector Code Sequence Value" },
{ 0x2010, 0x0060, 0, VR::CS, VM::M1, "Magnification Type" },
{ 0x2020, 0x0050, 0, VR::CS, VM::M1, "Requested Resolution ID" },
{ 0x2050, 0x0020, 0, VR::CS, VM::M1, "Presentation LUT Shape" },
{ 0x2100, 0x0170, 0, VR::IS, VM::M1, "Number of Films" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0242[] = {
{ 0x0014, 0x3026, 0, VR::DS, VM::M1, "Vertical Offset of Sensor" },
{ 0x0020, 0x3402, 1, VR::CS, VM::M1, "Modified Image ID" },
{ 0x0022, 0x1092, 0, VR::SQ, VM::M1, "Lens Constant Sequence" },
{ 0x0070, 0x0081, 0, VR::LO, VM::M1, "Content Description" },
{ 0x3002, 0x0030, 0, VR::SQ, VM::M1, "Exposure Sequence" },
{ 0x3008, 0x003A, 0, VR::DS, VM::M1, "Specified Treatment Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0243[] = {
{ 0x0020, 0x3403, 1, VR::DA, VM::M1, "Modified Image Date" },
{ 0x0022, 0x1093, 0, VR::LO, VM::M1, "IOL Manufacturer" },
{ 0x0070, 0x0080, 0, VR::CS, VM::M1, "Content Label" },
{ 0x3008, 0x003B, 0, VR::DS, VM::M1, "Delivered Treatment Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0244[] = {
{ 0x0014, 0x3020, 0, VR::SQ, VM::M1, "Detector Temperature Sequence" },
{ 0x0020, 0x3404, 1, VR::LO, VM::M1, "Modifying Device Manufacturer" },
{ 0x0022, 0x1094, 0, VR::LO, VM::M1, "Lens Constant Description" },
{ 0x0070, 0x0087, 0, VR::SQ, VM::M1, "Alternate Content Description Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0245[] = {
{ 0x0020, 0x3405, 1, VR::TM, VM::M1, "Modified Image Time" },
{ 0x0070, 0x0086, 0, VR::SQ, VM::M1, "Content Creator's Identification Code Sequence" },
{ 0x0076, 0x0080, 0, VR::US, VM::M1, "Component 1 Referenced Mating Feature Set ID" },
{ 0x3006, 0x0033, 0, VR::CS, VM::M1, "RT ROI Relationship" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0246[] = {
{ 0x0014, 0x3022, 0, VR::DS, VM::M1, "Sensor Name" },
{ 0x0020, 0x3406, 1, VR::LO, VM::M1, "Modified Image Description" },
{ 0x0022, 0x1096, 0, VR::SQ, VM::M1, "Keratometry Measurement Type Code Sequence" },
{ 0x3002, 0x0034, 0, VR::DS, VM::M4, "Diaphragm Position" },
{ 0x3006, 0x0030, 0, VR::SQ, VM::M1, "RT Related ROI Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0247[] = {
{ 0x0070, 0x0084, 0, VR::PN, VM::M1, "Content Creator's Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0248[] = {
{ 0x0028, 0x3010, 0, VR::SQ, VM::M1, "VOI LUT Sequence" },
{ 0x3008, 0x0030, 0, VR::SQ, VM::M1, "Referenced Treatment Record Sequence" },
{ 0x300A, 0x0422, 0, VR::ST, VM::M1, "General Accessory Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0249[] = {
{ 0x300A, 0x0423, 0, VR::CS, VM::M1, "General Accessory Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0250[] = {
{ 0x0028, 0x1090, 0, VR::CS, VM::M1, "Recommended Viewing Mode" },
{ 0x3008, 0x0032, 0, VR::DS, VM::M1, "Specified Primary Meterset" },
{ 0x300A, 0x0420, 0, VR::SQ, VM::M1, "General Accessory Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0251[] = {
{ 0x3008, 0x0033, 0, VR::DS, VM::M1, "Specified Secondary Meterset" },
{ 0x300A, 0x0421, 0, VR::SH, VM::M1, "General Accessory ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0252[] = {
{ 0x0014, 0x3028, 0, VR::DS, VM::M1, "Sensor Temperature" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0253[] = {
{ 0x0068, 0x6500, 0, VR::SQ, VM::M1, "Planning Landmark Point Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0254[] = {
{ 0x3006, 0x0038, 0, VR::LO, VM::M1, "ROI Generation Description" },
{ 0x3008, 0x0036, 0, VR::DS, VM::M1, "Delivered Primary Meterset" },
{ 0x300A, 0x0424, 0, VR::IS, VM::M1, "General Accessory Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0255[] = {
{ 0x3006, 0x0039, 0, VR::SQ, VM::M1, "ROI Contour Sequence" },
{ 0x3008, 0x0037, 0, VR::DS, VM::M1, "Delivered Secondary Meterset" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0256[] = {
{ 0x0008, 0x010C, 0, VR::UI, VM::M1, "Coding Scheme UID" },
{ 0x0014, 0x4014, 0, VR::DS, VM::M1, "Element Dimension A" },
{ 0x0024, 0x0120, 0, VR::CS, VM::M1, "Screening Baseline Measured" },
{ 0x0040, 0x0554, 0, VR::UI, VM::M1, "Specimen UID" },
{ 0x0040, 0x4040, 0, VR::CS, VM::M1, "Raw Data Handling" },
{ 0x4010, 0x1051, 0, VR::LO, VM::M1, "Itinerary ID" },
{ 0x5400, 0x1010, 0, VR::OX, VM::M1, "Waveform Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0257[] = {
{ 0x0008, 0x010D, 0, VR::UI, VM::M1, "Context Group Extension Creator UID" },
{ 0x0014, 0x4015, 0, VR::DS, VM::M1, "Element Dimension B" },
{ 0x0040, 0x0555, 0, VR::SQ, VM::M1, "Acquisition Context Sequence" },
{ 0x0040, 0x4041, 0, VR::CS, VM::M1, "Input Readiness State" },
{ 0x0400, 0x0115, 0, VR::OB, VM::M1, "Certificate of Signer" },
{ 0x5000, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels" },
{ 0x5000, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0258[] = {
{ 0x0014, 0x4016, 0, VR::DS, VM::M1, "Element Pitch" },
{ 0x0024, 0x0122, 0, VR::SQ, VM::M1, "Screening Baseline Measured Sequence" },
{ 0x0040, 0x0556, 0, VR::ST, VM::M1, "Acquisition Context Description" },
{ 0x4010, 0x1053, 0, VR::LO, VM::M1, "Itinerary ID Assigning Authority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0259[] = {
{ 0x0008, 0x010F, 0, VR::CS, VM::M1, "Context Identifier" },
{ 0x0014, 0x4017, 0, VR::DS, VM::M1, "Measured Beam Dimension A" },
{ 0x0018, 0x115E, 0, VR::DS, VM::M1, "Image and Fluoroscopy Area Dose Product" },
{ 0x4010, 0x1052, 0, VR::SH, VM::M1, "Itinerary ID Type" },
{ 0x5002, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 2" },
{ 0x5002, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0260[] = {
{ 0x0002, 0x0102, 0, VR::OB, VM::M1, "Private Information" },
{ 0x0014, 0x4010, 0, VR::SQ, VM::M1, "Transmit Transducer Sequence" },
{ 0x0018, 0x9351, 0, VR::FL, VM::M1, "Calcium Scoring Mass Factor Patient" },
{ 0x0024, 0x0124, 0, VR::CS, VM::M1, "Screening Baseline Type" },
{ 0x0040, 0x0550, 1, VR::SQ, VM::M1, "Specimen Sequence" },
{ 0x0040, 0x1101, 0, VR::SQ, VM::M1, "Person Identification Code Sequence" },
{ 0x0046, 0x0146, 0, VR::FD, VM::M1, "Sphere Power" },
{ 0x0100, 0x0410, 0, VR::CS, VM::M1, "SOP Instance Status" },
{ 0x0400, 0x0110, 0, VR::CS, VM::M1, "Certificate Type" },
{ 0x0400, 0x0500, 0, VR::SQ, VM::M1, "Encrypted Attributes Sequence" },
{ 0x4010, 0x1055, 0, VR::SH, VM::M1, "Route ID Assigning Authority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0261[] = {
{ 0x0014, 0x4011, 0, VR::SQ, VM::M1, "Receive Transducer Sequence" },
{ 0x0018, 0x9740, 0, VR::US, VM::M1, "Number of Subsets" },
{ 0x0040, 0x0551, 0, VR::LO, VM::M1, "Specimen Identifier" },
{ 0x0046, 0x0147, 0, VR::FD, VM::M1, "Cylinder Power" },
{ 0x4010, 0x1054, 0, VR::SH, VM::M1, "Route ID" },
{ 0x5004, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 3" },
{ 0x5004, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0262[] = {
{ 0x0002, 0x0100, 0, VR::UI, VM::M1, "Private Information Creator UID" },
{ 0x0008, 0x114B, 0, VR::SQ, VM::M1, "Referenced Real World Value Mapping Instance Sequence" },
{ 0x0014, 0x4012, 0, VR::US, VM::M1, "Number of Elements" },
{ 0x0018, 0x9353, 0, VR::FL, VM::M1, "Energy Weighting Factor" },
{ 0x0024, 0x0126, 0, VR::FL, VM::M1, "Screening Baseline Value" },
{ 0x0040, 0x0552, 1, VR::SQ, VM::M1, "Specimen Description Sequence (Trial)" },
{ 0x0040, 0x1103, 0, VR::LO, VM::M1TN, "Person's Telephone Numbers" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0263[] = {
{ 0x0008, 0x010B, 0, VR::CS, VM::M1, "Context Group Extension Flag" },
{ 0x0008, 0x114A, 0, VR::SQ, VM::M1, "Referenced Instance Sequence" },
{ 0x0014, 0x4013, 0, VR::CS, VM::M1, "Element Shape" },
{ 0x0018, 0x115A, 0, VR::CS, VM::M1, "Radiation Mode" },
{ 0x0018, 0x9352, 0, VR::FL, VM::M3, "Calcium Scoring Mass Factor Device" },
{ 0x0040, 0x0553, 1, VR::ST, VM::M1, "Specimen Description (Trial)" },
{ 0x0040, 0x1102, 0, VR::ST, VM::M1, "Person's Address" },
{ 0x0046, 0x0145, 0, VR::SQ, VM::M1, "Referenced Refractive Measurements Sequence" },
{ 0x4010, 0x1056, 0, VR::CS, VM::M1, "Inbound  Arrival Type" },
{ 0x5006, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 4" },
{ 0x5006, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0264[] = {
{ 0x0008, 0x0104, 0, VR::LO, VM::M1, "Code Meaning" },
{ 0x0008, 0x1145, 1, VR::SQ, VM::M1, "Referenced Curve Sequence" },
{ 0x0008, 0x4000, 1, VR::LT, VM::M1, "Identifying Comments" },
{ 0x0014, 0x401C, 0, VR::DS, VM::M1, "Measured Bandwidth" },
{ 0x0018, 0x1155, 0, VR::CS, VM::M1, "Radiation Setting" },
{ 0x4010, 0x1059, 0, VR::CS, VM::M1, "Carrier ID Assigning Authority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0265[] = {
{ 0x0008, 0x0105, 0, VR::CS, VM::M1, "Mapping Resource" },
{ 0x0018, 0x1154, 0, VR::DS, VM::M1, "Average Pulse Width" },
{ 0x0018, 0x5050, 0, VR::IS, VM::M1, "Depth of Scan Field" },
{ 0x4010, 0x1058, 0, VR::SH, VM::M1, "Carrier ID" },
{ 0x5008, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 5" },
{ 0x5008, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0266[] = {
{ 0x0008, 0x0106, 0, VR::DT, VM::M1, "Context Group Version" },
{ 0x0068, 0x64F0, 0, VR::FD, VM::M3, "2D Degree of Freedom Axis" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0267[] = {
{ 0x0008, 0x0107, 0, VR::DT, VM::M1, "Context Group Local Version" },
{ 0x0018, 0x1156, 0, VR::CS, VM::M1, "Rectification Type" },
{ 0x500A, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 6" },
{ 0x500A, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0268[] = {
{ 0x0008, 0x0100, 0, VR::SH, VM::M1, "Code Value" },
{ 0x0014, 0x4018, 0, VR::DS, VM::M1, "Measured Beam Dimension B" },
{ 0x0018, 0x1151, 0, VR::IS, VM::M1, "X-Ray Tube Current" },
{ 0x0018, 0x9749, 0, VR::SQ, VM::M1, "PET Reconstruction Sequence" },
{ 0x0028, 0x0120, 0, VR::XS, VM::M1, "Pixel Padding Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0269[] = {
{ 0x0008, 0x1140, 0, VR::SQ, VM::M1, "Referenced Image Sequence" },
{ 0x0014, 0x4019, 0, VR::DS, VM::M1, "Location of Measured Beam Diameter" },
{ 0x0018, 0x1150, 0, VR::IS, VM::M1, "Exposure Time" },
{ 0x0028, 0x0121, 0, VR::XS, VM::M1, "Pixel Padding Range Limit" },
{ 0x500C, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 7" },
{ 0x500C, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0270[] = {
{ 0x0008, 0x0102, 0, VR::SH, VM::M1, "Coding Scheme Designator" },
{ 0x0014, 0x401A, 0, VR::DS, VM::M1, "Nominal Frequency" },
{ 0x0018, 0x1153, 0, VR::IS, VM::M1, "Exposure in uAs" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0271[] = {
{ 0x0008, 0x0103, 0, VR::SH, VM::M1, "Coding Scheme Version" },
{ 0x0014, 0x401B, 0, VR::DS, VM::M1, "Measured Center Frequency" },
{ 0x0018, 0x1152, 0, VR::IS, VM::M1, "Exposure" },
{ 0x2110, 0x0099, 1, VR::SH, VM::M1, "Print Queue ID" },
{ 0x500E, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 8" },
{ 0x500E, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0272[] = {
{ 0x0010, 0x4000, 0, VR::LT, VM::M1, "Patient Comments" },
{ 0x0014, 0x4004, 0, VR::CS, VM::M1, "Pulser Type" },
{ 0x0018, 0x9345, 0, VR::FD, VM::M1, "CTDIvol" },
{ 0x0018, 0x9755, 0, VR::CS, VM::M1, "Time of Flight Information Used" },
{ 0x0040, 0x4050, 0, VR::DT, VM::M1, "Performed Procedure Step Start DateTime" },
{ 0x0054, 0x1101, 0, VR::LO, VM::M1, "Attenuation Correction Method" },
{ 0x4000, 0x0010, 1, VR::LT, VM::M1, "Arbitrary" },
{ 0x4010, 0x1041, 0, VR::DT, VM::M1, "OOI Owner Creation Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0273[] = {
{ 0x0018, 0x9344, 0, VR::CS, VM::M1, "Contrast/Bolus Agent Phase" },
{ 0x0040, 0x4051, 0, VR::DT, VM::M1, "Performed Procedure Step End DateTime" },
{ 0x0054, 0x1100, 0, VR::CS, VM::M1, "Randoms Correction Method" },
{ 0x0400, 0x0105, 0, VR::DT, VM::M1, "Digital Signature DateTime" },
{ 0x4010, 0x0001, 0, VR::CS, VM::M1, "Low Energy Detectors" },
{ 0x5010, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 9" },
{ 0x5010, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0274[] = {
{ 0x0014, 0x4006, 0, VR::LT, VM::M1, "Pulser Notes" },
{ 0x0040, 0x4052, 0, VR::DT, VM::M1, "Procedure Step Cancellation DateTime" },
{ 0x0054, 0x1103, 0, VR::LO, VM::M1, "Reconstruction Method" },
{ 0x4010, 0x0002, 0, VR::CS, VM::M1, "High Energy Detectors" },
{ 0x4010, 0x1043, 0, VR::FL, VM::M3, "OOI Size" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0275[] = {
{ 0x0018, 0x9346, 0, VR::SQ, VM::M1, "CTDI Phantom Type Code Sequence" },
{ 0x0018, 0x9756, 0, VR::CS, VM::M1, "Reconstruction Type" },
{ 0x0054, 0x1102, 0, VR::CS, VM::M1, "Decay Correction" },
{ 0x4010, 0x1042, 0, VR::CS, VM::M1, "OOI Type" },
{ 0x5012, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 10" },
{ 0x5012, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0276[] = {
{ 0x0018, 0x1149, 0, VR::IS, VM::M1T2, "Field of View Dimension(s)" },
{ 0x0018, 0x9341, 0, VR::SQ, VM::M1, "Contrast/Bolus Usage Sequence" },
{ 0x0018, 0x9751, 0, VR::SQ, VM::M1, "PET Frame Type Sequence" },
{ 0x0054, 0x1105, 0, VR::LO, VM::M1, "Scatter Correction Method" },
{ 0x0400, 0x0100, 0, VR::UI, VM::M1, "Digital Signature UID" },
{ 0x0400, 0x0510, 0, VR::UI, VM::M1, "Encrypted Content Transfer Syntax UID" },
{ 0x4010, 0x0004, 0, VR::SQ, VM::M1, "Detector Geometry Sequence" },
{ 0x4010, 0x1045, 0, VR::SQ, VM::M1, "Basis Materials Code Sequence" },
{ 0x5400, 0x1004, 0, VR::US, VM::M1, "Waveform Bits Allocated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0277[] = {
{ 0x0010, 0x0101, 0, VR::SQ, VM::M1, "Patient's Primary Language Code Sequence" },
{ 0x0018, 0x9340, 0, VR::SQ, VM::M1, "Contrast Administration Profile Sequence" },
{ 0x0054, 0x1104, 0, VR::LO, VM::M1, "Detector Lines of Response Used" },
{ 0x4010, 0x1044, 0, VR::CS, VM::M1, "Acquisition Status" },
{ 0x5014, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 11" },
{ 0x5014, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0278[] = {
{ 0x0010, 0x0102, 0, VR::SQ, VM::M1, "Patient's Primary Language Modifier Code Sequence" },
{ 0x0010, 0x2180, 0, VR::SH, VM::M1, "Occupation" },
{ 0x0014, 0x4002, 0, VR::SQ, VM::M1, "Pulser Equipment Sequence" },
{ 0x0018, 0x9343, 0, VR::CS, VM::M1, "Contrast/Bolus Agent Detected" },
{ 0x2130, 0x00A0, 1, VR::SQ, VM::M1, "Proposed Study Sequence" },
{ 0x4010, 0x1047, 0, VR::SQ, VM::M1, "OOI Owner Sequence" },
{ 0x5400, 0x1006, 0, VR::CS, VM::M1, "Waveform Sample Interpretation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0279[] = {
{ 0x0008, 0x115A, 0, VR::UI, VM::M1TN, "SOP Classes Supported" },
{ 0x0018, 0x9342, 0, VR::CS, VM::M1, "Contrast/Bolus Agent Administered" },
{ 0x4010, 0x1046, 0, VR::CS, VM::M1, "Phantom Type" },
{ 0x5016, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 12" },
{ 0x5016, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0280[] = {
{ 0x0008, 0x0114, 0, VR::ST, VM::M1, "Coding Scheme External ID" },
{ 0x0008, 0x1155, 0, VR::UI, VM::M1, "Referenced SOP Instance UID" },
{ 0x0014, 0x400C, 0, VR::LT, VM::M1, "Receiver Notes" },
{ 0x0018, 0x1145, 0, VR::DS, VM::M1, "Center of Rotation Offset" },
{ 0x0018, 0x4000, 1, VR::LT, VM::M1, "Acquisition Comments" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0281[] = {
{ 0x0008, 0x0115, 0, VR::ST, VM::M1, "Coding Scheme Name" },
{ 0x0018, 0x1144, 0, VR::DS, VM::M1, "Angular Step" },
{ 0x0018, 0x5040, 1, VR::DS, VM::M1, "Total Gain" },
{ 0x300A, 0x01D4, 0, VR::DS, VM::M1, "Table Top Longitudinal Setup Displacement" },
{ 0x4010, 0x1048, 0, VR::CS, VM::M1, "Scan Type" },
{ 0x5018, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 13" },
{ 0x5018, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0282[] = {
{ 0x0008, 0x0116, 0, VR::ST, VM::M1, "Coding Scheme Responsible Organization" },
{ 0x0014, 0x400E, 0, VR::SQ, VM::M1, "Pre-Amplifier Equipment Sequence" },
{ 0x0018, 0x1147, 0, VR::CS, VM::M1, "Field of View Shape" },
{ 0x5400, 0x100A, 0, VR::OX, VM::M1, "Waveform Padding Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0283[] = {
{ 0x0008, 0x0117, 0, VR::UI, VM::M1, "Context UID" },
{ 0x0014, 0x400F, 0, VR::LT, VM::M1, "Pre-Amplifier Notes" },
{ 0x0018, 0x1146, 1, VR::DS, VM::M1TN, "Rotation Offset" },
{ 0x300A, 0x01D6, 0, VR::DS, VM::M1, "Table Top Lateral Setup Displacement" },
{ 0x501A, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 14" },
{ 0x501A, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0284[] = {
{ 0x0008, 0x0110, 0, VR::SQ, VM::M1, "Coding Scheme Identification Sequence" },
{ 0x0014, 0x4008, 0, VR::SQ, VM::M1, "Receiver Equipment Sequence" },
{ 0x0018, 0x1141, 1, VR::DS, VM::M1, "Angular Position" },
{ 0x0018, 0x9759, 0, VR::CS, VM::M1, "Attenuation Corrected" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0285[] = {
{ 0x0008, 0x1150, 0, VR::UI, VM::M1, "Referenced SOP Class UID" },
{ 0x0018, 0x1140, 0, VR::CS, VM::M1, "Rotation Direction" },
{ 0x0018, 0x9758, 0, VR::CS, VM::M1, "Decay Corrected" },
{ 0x300A, 0x01D0, 0, VR::ST, VM::M1, "Setup Reference Description" },
{ 0x501C, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 15" },
{ 0x501C, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0286[] = {
{ 0x0008, 0x0112, 0, VR::LO, VM::M1, "Coding Scheme Registry" },
{ 0x0014, 0x400A, 0, VR::CS, VM::M1, "Amplifier Type" },
{ 0x0018, 0x1143, 0, VR::DS, VM::M1, "Scan Arc" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0287[] = {
{ 0x0018, 0x1142, 0, VR::DS, VM::M1TN, "Radial Position" },
{ 0x300A, 0x01D2, 0, VR::DS, VM::M1, "Table Top Vertical Setup Displacement" },
{ 0x501E, 0x0040, 1, VR::SH, VM::M1TN, "Axis Labels 16" },
{ 0x501E, 0x1001, 1, VR::CS, VM::M1, "Curve Activation Layer 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0288[] = {
{ 0x0014, 0x4034, 0, VR::DS, VM::M1, "Rectifier Smoothing" },
{ 0x0018, 0x9765, 0, VR::CS, VM::M1, "Randoms Corrected" },
{ 0x0020, 0x4000, 0, VR::LT, VM::M1, "Image Comments" },
{ 0x0024, 0x0100, 0, VR::FL, VM::M1, "Age Corrected Sensitivity Deviation Probability Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0289[] = {
{ 0x0014, 0x4035, 0, VR::SQ, VM::M1, "DAC Sequence" },
{ 0x0018, 0x9764, 0, VR::CS, VM::M1, "Count Loss Normalization Corrected" },
{ 0x0020, 0x0105, 0, VR::IS, VM::M1, "Number of Temporal Positions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0290[] = {
{ 0x0014, 0x4036, 0, VR::CS, VM::M1, "DAC Type" },
{ 0x0018, 0x9767, 0, VR::CS, VM::M1, "Sensitivity Calibrated" },
{ 0x0024, 0x0102, 0, VR::CS, VM::M1, "Generalized Defect Corrected Sensitivity Deviation Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0291[] = {
{ 0x0018, 0x9766, 0, VR::CS, VM::M1, "Non-uniform Radial Sampling Corrected" },
{ 0x0024, 0x0103, 0, VR::FL, VM::M1, "Generalized Defect Corrected Sensitivity Deviation Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0292[] = {
{ 0x0014, 0x4030, 0, VR::SQ, VM::M1, "Receiver Settings Sequence" },
{ 0x0018, 0x9761, 0, VR::CS, VM::M1, "Dead Time Corrected" },
{ 0x0020, 0x0100, 0, VR::IS, VM::M1, "Temporal Position Identifier" },
{ 0x0024, 0x0104, 0, VR::FL, VM::M1, "Generalized Defect Corrected Sensitivity Deviation Probability Value" },
{ 0x0028, 0x0108, 0, VR::XS, VM::M1, "Smallest Pixel Value in Series" },
{ 0x0400, 0x0520, 0, VR::OB, VM::M1, "Encrypted Content" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0293[] = {
{ 0x0014, 0x4031, 0, VR::DS, VM::M1, "Acquired Soundpath Length" },
{ 0x0018, 0x9760, 0, VR::CS, VM::M1, "Scatter Corrected" },
{ 0x0024, 0x0105, 0, VR::FL, VM::M1, "Minimum Sensitivity Value" },
{ 0x0028, 0x0109, 0, VR::XS, VM::M1, "Largest Pixel Value in Series" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0294[] = {
{ 0x0010, 0x21B0, 0, VR::LT, VM::M1, "Additional Patient History" },
{ 0x0014, 0x4032, 0, VR::CS, VM::M1, "Acquisition Compression Type" },
{ 0x0018, 0x9763, 0, VR::CS, VM::M1, "Patient Motion Corrected" },
{ 0x0024, 0x0106, 0, VR::CS, VM::M1, "Blind Spot Localized" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0295[] = {
{ 0x0014, 0x4033, 0, VR::IS, VM::M1, "Acquisition Sample Size" },
{ 0x0018, 0x9762, 0, VR::CS, VM::M1, "Gantry Motion Corrected" },
{ 0x0022, 0x1140, 0, VR::CS, VM::M1, "Ophthalmic Axial Length Measurement Modified" },
{ 0x0024, 0x0107, 0, VR::FL, VM::M1, "Blind Spot X-Coordinate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0296[] = {
{ 0x0014, 0x403C, 0, VR::DS, VM::M1TN, "DAC Amplitude" },
{ 0x0024, 0x0108, 0, VR::FL, VM::M1, "Blind Spot Y-Coordinate" },
{ 0x0028, 0x0104, 1, VR::XS, VM::M1, "Smallest Valid Pixel Value" },
{ 0x0028, 0x4000, 1, VR::LT, VM::M1, "Image Presentation Comments" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0297[] = {
{ 0x0008, 0x1164, 0, VR::SQ, VM::M1, "Frame Extraction Sequence" },
{ 0x0028, 0x0105, 1, VR::XS, VM::M1, "Largest Valid Pixel Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0298[] = {
{ 0x0008, 0x1167, 0, VR::UI, VM::M1, "Multi-Frame Source SOP Instance UID" },
{ 0x0028, 0x0106, 0, VR::XS, VM::M1, "Smallest Image Pixel Value" },
{ 0x0068, 0x64D0, 0, VR::FD, VM::M9, "3D Mating Axes" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0299[] = {
{ 0x0028, 0x0107, 0, VR::XS, VM::M1, "Largest Image Pixel Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0300[] = {
{ 0x0008, 0x1161, 0, VR::UL, VM::M1TN, "Simple Frame List" },
{ 0x0014, 0x4038, 0, VR::DS, VM::M1TN, "DAC Gain Points" },
{ 0x0018, 0x9769, 0, VR::CS, VM::M1, "Iterative Reconstruction Method" },
{ 0x0028, 0x0100, 0, VR::US, VM::M1, "Bits Allocated" },
{ 0x0038, 0x0500, 0, VR::LO, VM::M1, "Patient State" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0301[] = {
{ 0x0008, 0x1160, 0, VR::IS, VM::M1TN, "Referenced Frame Number" },
{ 0x0018, 0x1170, 0, VR::IS, VM::M1, "Generator Power" },
{ 0x0018, 0x9768, 0, VR::CS, VM::M1, "Detector Normalization Correction" },
{ 0x0028, 0x0101, 0, VR::US, VM::M1, "Bits Stored" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0302[] = {
{ 0x0008, 0x1163, 0, VR::FD, VM::M2, "Time Range" },
{ 0x0014, 0x403A, 0, VR::DS, VM::M1TN, "DAC Time Points" },
{ 0x0028, 0x0102, 0, VR::US, VM::M1, "High Bit" },
{ 0x0038, 0x0502, 0, VR::SQ, VM::M1, "Patient Clinical Trial Participation Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0303[] = {
{ 0x0008, 0x1162, 0, VR::UL, VM::M3T3N, "Calculated Frame List" },
{ 0x0028, 0x0103, 0, VR::US, VM::M1, "Pixel Representation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0304[] = {
{ 0x0014, 0x4024, 0, VR::DS, VM::M1, "Excitation Frequency" },
{ 0x0024, 0x0110, 0, VR::SQ, VM::M1, "Visual Acuity Measurement Sequence" },
{ 0x0100, 0x0424, 0, VR::LT, VM::M1, "SOP Authorization Comment" },
{ 0x4010, 0x1061, 0, VR::FL, VM::M3, "Source Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0305[] = {
{ 0x4010, 0x1060, 0, VR::FL, VM::M3, "Source Orientation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0306[] = {
{ 0x0014, 0x4026, 0, VR::CS, VM::M1, "Modulation Type" },
{ 0x0022, 0x1155, 0, VR::FL, VM::M1, "Signal to Noise Ratio" },
{ 0x0024, 0x0112, 0, VR::SQ, VM::M1, "Refractive Parameters Used on Patient Sequence" },
{ 0x0032, 0x4000, 1, VR::LT, VM::M1, "Study Comments" },
{ 0x0100, 0x0426, 0, VR::LO, VM::M1, "Authorization Equipment Certification Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0307[] = {
{ 0x0024, 0x0113, 0, VR::CS, VM::M1, "Measurement Laterality" },
{ 0x4010, 0x1062, 0, VR::FL, VM::M1, "Belt Height" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0308[] = {
{ 0x0014, 0x4020, 0, VR::SQ, VM::M1, "Pulser Settings Sequence" },
{ 0x0018, 0x9771, 0, VR::SQ, VM::M1, "Patient Physiological State Sequence" },
{ 0x0020, 0x0110, 0, VR::DS, VM::M1, "Temporal Resolution" },
{ 0x0022, 0x1153, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Acquisition Method Code Sequence" },
{ 0x0024, 0x0114, 0, VR::SQ, VM::M1, "Ophthalmic Patient Clinical Information Left Eye Sequence" },
{ 0x0040, 0x0560, 0, VR::SQ, VM::M1, "Specimen Description Sequence" },
{ 0x0100, 0x0420, 0, VR::DT, VM::M1, "SOP Authorization DateTime" },
{ 0x0400, 0x0120, 0, VR::OB, VM::M1, "Signature" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0309[] = {
{ 0x0018, 0x9360, 0, VR::SQ, VM::M1, "CT Additional X-Ray Source Sequence" },
{ 0x0018, 0x9770, 0, VR::CS, VM::M1, "Attenuation Correction Temporal Relationship" },
{ 0x0024, 0x0115, 0, VR::SQ, VM::M1, "Ophthalmic Patient Clinical Information Right Eye Sequence" },
{ 0x4010, 0x1064, 0, VR::SQ, VM::M1, "Algorithm Routing Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0310[] = {
{ 0x0010, 0x21A0, 0, VR::CS, VM::M1, "Smoking Status" },
{ 0x0014, 0x4022, 0, VR::DS, VM::M1, "Pulse Width" },
{ 0x0040, 0x0562, 0, VR::SQ, VM::M1, "Issuer of the Specimen Identifier Sequence" },
{ 0x2130, 0x0080, 1, VR::SQ, VM::M1, "Presentation LUT Content Sequence" },
{ 0x4010, 0x1067, 0, VR::CS, VM::M1, "Transport Classification" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0311[] = {
{ 0x0018, 0x9772, 0, VR::SQ, VM::M1, "Patient Physiological State Code Sequence" },
{ 0x0022, 0x1150, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Data Source Code Sequence" },
{ 0x0024, 0x0117, 0, VR::CS, VM::M1, "Foveal Point Normative Data Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0312[] = {
{ 0x0024, 0x0118, 0, VR::FL, VM::M1, "Foveal Point Probability Value" },
{ 0x0038, 0x4000, 0, VR::LT, VM::M1, "Visit Comments" },
{ 0x4010, 0x1069, 0, VR::FL, VM::M1, "Total Processing Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0313[] = {
{ 0x0018, 0x1164, 0, VR::DS, VM::M2, "Imager Pixel Spacing" },
{ 0x4010, 0x1068, 0, VR::LT, VM::M1, "OOI Type Descriptor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0314[] = {
{ 0x0068, 0x64C0, 0, VR::FD, VM::M3, "3D Mating Point" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0315[] = {
{ 0x0018, 0x1166, 0, VR::CS, VM::M1TN, "Grid" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0316[] = {
{ 0x0014, 0x4028, 0, VR::DS, VM::M1, "Damping" },
{ 0x0018, 0x1161, 0, VR::LO, VM::M1TN, "Type of Filters" },
{ 0x0028, 0x0110, 1, VR::XS, VM::M1, "Smallest Image Pixel Value in Plane" },
{ 0x0038, 0x0100, 0, VR::SQ, VM::M1, "Pertinent Documents Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0317[] = {
{ 0x0018, 0x1160, 0, VR::SH, VM::M1, "Filter Type" },
{ 0x0028, 0x0111, 1, VR::XS, VM::M1, "Largest Image Pixel Value in Plane" },
{ 0x4010, 0x106C, 0, VR::OB, VM::M1, "Detector Calibration Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0318[] = {
{ 0x0022, 0x1159, 0, VR::LO, VM::M1, "Ophthalmic Axial Length Data Source Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0319[] = {
{ 0x0018, 0x1162, 0, VR::DS, VM::M1, "Intensifier Size" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0320[] = {
{ 0x0018, 0x9314, 0, VR::SQ, VM::M1, "CT Reconstruction Sequence" },
{ 0x0040, 0x0515, 0, VR::SQ, VM::M1, "Alternate Container Identifier Sequence" },
{ 0x0040, 0x4001, 0, VR::CS, VM::M1, "General Purpose Scheduled Procedure Step Status" },
{ 0x4010, 0x1010, 0, VR::US, VM::M1, "Potential Threat Object ID" },
{ 0x5010, 0x0010, 1, VR::US, VM::M1, "Number of Points 9" },
{ 0x6000, 0x3000, 0, VR::OX, VM::M1, "Overlay Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0321[] = {
{ 0x0014, 0x4054, 0, VR::ST, VM::M1, "Coupling Technique" },
{ 0x0018, 0x9315, 0, VR::CS, VM::M1, "Reconstruction Algorithm" },
{ 0x0046, 0x0102, 0, VR::SQ, VM::M1, "Add Other Sequence" },
{ 0x0054, 0x0500, 0, VR::CS, VM::M1, "Slice Progression Direction" },
{ 0x4010, 0x1011, 0, VR::SQ, VM::M1, "Threat Sequence" },
{ 0x5004, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0322[] = {
{ 0x0014, 0x4057, 0, VR::DS, VM::M1, "Coupling Velocity" },
{ 0x0018, 0x9316, 0, VR::CS, VM::M1, "Convolution Kernel Group" },
{ 0x0040, 0x4003, 0, VR::CS, VM::M1, "General Purpose Scheduled Procedure Step Priority" },
{ 0x0046, 0x0101, 0, VR::SQ, VM::M1, "Add Intermediate Sequence" },
{ 0x4010, 0x1012, 0, VR::CS, VM::M1, "Threat Category" },
{ 0x5012, 0x0010, 1, VR::US, VM::M1, "Number of Points 10" },
{ 0x6002, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0323[] = {
{ 0x0014, 0x4056, 0, VR::ST, VM::M1, "Coupling Medium" },
{ 0x0018, 0x9317, 0, VR::FD, VM::M2, "Reconstruction Field of View" },
{ 0x0022, 0x1125, 0, VR::SQ, VM::M1, "Anterior Chamber Depth Definition Code Sequence" },
{ 0x0040, 0x4002, 0, VR::CS, VM::M1, "General Purpose Performed Procedure Step Status" },
{ 0x0046, 0x0100, 0, VR::SQ, VM::M1, "Add Near Sequence" },
{ 0x4010, 0x1013, 0, VR::LT, VM::M1, "Threat Category Description" },
{ 0x5006, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0324[] = {
{ 0x0014, 0x4051, 0, VR::SQ, VM::M1, "Receive Transducer Settings Sequence" },
{ 0x0018, 0x1508, 0, VR::CS, VM::M1, "Positioner Type" },
{ 0x0018, 0x9310, 0, VR::FD, VM::M1, "Table Feed per Rotation" },
{ 0x0022, 0x1122, 0, VR::FL, VM::M1, "IOL Power For Exact Target Refraction" },
{ 0x0040, 0x4005, 0, VR::DT, VM::M1, "Scheduled Procedure Step Start DateTime" },
{ 0x4010, 0x1014, 0, VR::CS, VM::M1, "ATD Ability Assessment" },
{ 0x5014, 0x0010, 1, VR::US, VM::M1, "Number of Points 11" },
{ 0x6004, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0325[] = {
{ 0x0014, 0x4050, 0, VR::SQ, VM::M1, "Transmit Transducer Settings Sequence" },
{ 0x0018, 0x9311, 0, VR::FD, VM::M1, "Spiral Pitch Factor" },
{ 0x0018, 0x9701, 0, VR::DT, VM::M1, "Decay Correction DateTime" },
{ 0x0040, 0x0100, 0, VR::SQ, VM::M1, "Scheduled Procedure Step Sequence" },
{ 0x0040, 0x4004, 0, VR::SQ, VM::M1, "Scheduled Processing Applications Code Sequence" },
{ 0x0046, 0x0106, 0, VR::FD, VM::M1, "Viewing Distance" },
{ 0x0048, 0x0108, 0, VR::SQ, VM::M1, "Illumination Color Code Sequence" },
{ 0x4010, 0x1015, 0, VR::CS, VM::M1, "ATD Assessment Flag" },
{ 0x5000, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0326[] = {
{ 0x0018, 0x9312, 0, VR::SQ, VM::M1, "CT Geometry Sequence" },
{ 0x0040, 0x0513, 0, VR::SQ, VM::M1, "Issuer of the Container Identifier Sequence" },
{ 0x0040, 0x4007, 0, VR::SQ, VM::M1, "Performed Processing Applications Code Sequence" },
{ 0x4010, 0x1016, 0, VR::FL, VM::M1, "ATD Assessment Probability" },
{ 0x5016, 0x0010, 1, VR::US, VM::M1, "Number of Points 12" },
{ 0x6006, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0327[] = {
{ 0x0010, 0x21D0, 0, VR::DA, VM::M1, "Last Menstrual Date" },
{ 0x0014, 0x4052, 0, VR::DS, VM::M1, "Incident Angle" },
{ 0x0018, 0x9313, 0, VR::FD, VM::M3, "Data Collection Center (Patient)" },
{ 0x0022, 0x1121, 0, VR::FL, VM::M1, "IOL Power For Exact Emmetropia" },
{ 0x0040, 0x0512, 0, VR::LO, VM::M1, "Container Identifier" },
{ 0x0040, 0x4006, 0, VR::CS, VM::M1, "Multiple Copies Flag" },
{ 0x0046, 0x0104, 0, VR::FD, VM::M1, "Add Power" },
{ 0x0072, 0x0520, 0, VR::CS, VM::M1TN, "3D Rendering Type" },
{ 0x4010, 0x1017, 0, VR::FL, VM::M1, "Mass" },
{ 0x5002, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0328[] = {
{ 0x0018, 0x1114, 0, VR::DS, VM::M1, "Estimated Radiographic Magnification Factor" },
{ 0x0018, 0x5010, 0, VR::LO, VM::M1TN, "Transducer Data" },
{ 0x0040, 0x4009, 0, VR::SQ, VM::M1, "Human Performer Code Sequence" },
{ 0x0048, 0x0105, 0, VR::SQ, VM::M1, "Optical Path Sequence" },
{ 0x300A, 0x0184, 0, VR::LO, VM::M1, "Patient Additional Position" },
{ 0x4010, 0x1018, 0, VR::FL, VM::M1, "Density" },
{ 0x5018, 0x0010, 1, VR::US, VM::M1, "Number of Points 13" },
{ 0x6008, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0329[] = {
{ 0x0014, 0x405C, 0, VR::ST, VM::M1, "Delay Law Identifier" },
{ 0x4008, 0x0040, 1, VR::SH, VM::M1, "Results ID" },
{ 0x4010, 0x1019, 0, VR::FL, VM::M1, "Z Effective" },
{ 0x500C, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0330[] = {
{ 0x0018, 0x5012, 0, VR::DS, VM::M1, "Focus Depth" },
{ 0x0040, 0xA385, 0, VR::SQ, VM::M1, "Pertinent Other Evidence Sequence" },
{ 0x0048, 0x0107, 0, VR::ST, VM::M1, "Optical Path Description" },
{ 0x4010, 0x101A, 0, VR::SH, VM::M1, "Boarding Pass ID" },
{ 0x501A, 0x0010, 1, VR::US, VM::M1, "Number of Points 14" },
{ 0x600A, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0331[] = {
{ 0x0048, 0x0106, 0, VR::SH, VM::M1, "Optical Path Identifier" },
{ 0x4008, 0x0042, 1, VR::LO, VM::M1, "Results ID Issuer" },
{ 0x4010, 0x101B, 0, VR::FL, VM::M3, "Center of Mass" },
{ 0x500E, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0332[] = {
{ 0x0008, 0x1100, 1, VR::SQ, VM::M1, "Referenced Results Sequence" },
{ 0x0014, 0x4059, 0, VR::DS, VM::M1, "Crystal Center Location Z" },
{ 0x0018, 0x1110, 0, VR::DS, VM::M1, "Distance Source to Detector" },
{ 0x0018, 0x1500, 0, VR::CS, VM::M1, "Positioner Motion" },
{ 0x0018, 0x9318, 0, VR::FD, VM::M3, "Reconstruction Target Center (Patient)" },
{ 0x300A, 0x0180, 0, VR::SQ, VM::M1, "Patient Setup Sequence" },
{ 0x4010, 0x101C, 0, VR::FL, VM::M3, "Center of PTO" },
{ 0x501C, 0x0010, 1, VR::US, VM::M1, "Number of Points 15" },
{ 0x600C, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0333[] = {
{ 0x0014, 0x4058, 0, VR::DS, VM::M1, "Crystal Center Location X" },
{ 0x0018, 0x1111, 0, VR::DS, VM::M1, "Distance Source to Patient" },
{ 0x0018, 0x9319, 0, VR::FD, VM::M1, "Reconstruction Angle" },
{ 0x0040, 0x0518, 0, VR::SQ, VM::M1, "Container Type Code Sequence" },
{ 0x0048, 0x0100, 0, VR::SQ, VM::M1, "Illuminator Type Code Sequence" },
{ 0x4010, 0x101D, 0, VR::FL, VM::M6TN, "Bounding Polygon" },
{ 0x5008, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0334[] = {
{ 0x300A, 0x0182, 0, VR::IS, VM::M1, "Patient Setup Number" },
{ 0x4010, 0x101E, 0, VR::SH, VM::M1, "Route Segment Start Location ID" },
{ 0x501E, 0x0010, 1, VR::US, VM::M1, "Number of Points 16" },
{ 0x600E, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0335[] = {
{ 0x0014, 0x405A, 0, VR::DS, VM::M1, "Sound Path Length" },
{ 0x0040, 0x051A, 0, VR::LO, VM::M1, "Container Description" },
{ 0x0040, 0x8302, 0, VR::DS, VM::M1, "Entrance Dose in mGy" },
{ 0x0040, 0xA380, 1, VR::SQ, VM::M1, "Report Detail Sequence (Trial)" },
{ 0x0048, 0x0102, 0, VR::DS, VM::M6, "Image Orientation (Slide)" },
{ 0x300A, 0x0183, 0, VR::LO, VM::M1, "Patient Setup Label" },
{ 0x4010, 0x101F, 0, VR::SH, VM::M1, "Route Segment End Location ID" },
{ 0x500A, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0336[] = {
{ 0x0014, 0x5004, 0, VR::IS, VM::M1, "LINAC Output" },
{ 0x0018, 0x9304, 0, VR::SQ, VM::M1, "CT Acquisition Details Sequence" },
{ 0x0040, 0x4011, 0, VR::DT, VM::M1, "Expected Completion Date Time" },
{ 0x0054, 0x0101, 0, VR::US, VM::M1, "Number of Time Slices" },
{ 0x0074, 0x0121, 0, VR::FD, VM::M1, "Continuation End Meterset" },
{ 0x5000, 0x0010, 1, VR::US, VM::M1, "Number of Points" },
{ 0x6010, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0337[] = {
{ 0x0018, 0x9305, 0, VR::FD, VM::M1, "Revolution Time" },
{ 0x0018, 0x9715, 0, VR::FD, VM::M1, "Start Density Threshold" },
{ 0x0040, 0x4010, 0, VR::DT, VM::M1, "Scheduled Procedure Step Modification Date Time" },
{ 0x0054, 0x0100, 0, VR::US, VM::M1TN, "Time Slice Vector" },
{ 0x0074, 0x0120, 0, VR::FD, VM::M1, "Continuation Start Meterset" },
{ 0x4010, 0x1001, 0, VR::SQ, VM::M1, "Threat ROI Voxel Sequence" },
{ 0x5014, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0338[] = {
{ 0x0018, 0x9306, 0, VR::FD, VM::M1, "Single Collimation Width" },
{ 0x0018, 0x9716, 0, VR::FD, VM::M1, "Start Relative Density Difference Threshold" },
{ 0x5002, 0x0010, 1, VR::US, VM::M1, "Number of Points 2" },
{ 0x6012, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0339[] = {
{ 0x0018, 0x9307, 0, VR::FD, VM::M1, "Total Collimation Width" },
{ 0x0018, 0x9717, 0, VR::FD, VM::M1, "Start Cardiac Trigger Count Threshold" },
{ 0x0022, 0x1135, 0, VR::SQ, VM::M1, "Source of Refractive Error Data Code Sequence" },
{ 0x5016, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0340[] = {
{ 0x0022, 0x1132, 0, VR::SQ, VM::M1, "Source of Lens Thickness Data Code Sequence" },
{ 0x0040, 0x4015, 0, VR::SQ, VM::M1, "Resulting General Purpose Performed Procedure Steps Sequence" },
{ 0x300A, 0x0198, 0, VR::SH, VM::M1, "Fixation Device Position" },
{ 0x4010, 0x1004, 0, VR::FL, VM::M3, "Threat ROI Base" },
{ 0x5004, 0x0010, 1, VR::US, VM::M1, "Number of Points 3" },
{ 0x6014, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0341[] = {
{ 0x0014, 0x4040, 0, VR::SQ, VM::M1, "Pre-Amplifier Settings Sequence" },
{ 0x0018, 0x9301, 0, VR::SQ, VM::M1, "CT Acquisition Type Sequence" },
{ 0x0022, 0x1133, 0, VR::SQ, VM::M1, "Source of Anterior Chamber Depth Data Code Sequence" },
{ 0x0040, 0x0500, 0, VR::SQ, VM::M1, "Scheduled Specimen Sequence" },
{ 0x0400, 0x0550, 0, VR::SQ, VM::M1, "Modified Attributes Sequence" },
{ 0x300A, 0x0199, 0, VR::FL, VM::M1, "Fixation Device Pitch Angle" },
{ 0x4010, 0x1005, 0, VR::FL, VM::M3, "Threat ROI Extents" },
{ 0x5010, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0342[] = {
{ 0x0014, 0x5002, 0, VR::IS, VM::M1, "LINAC Energy" },
{ 0x0018, 0x9302, 0, VR::CS, VM::M1, "Acquisition Type" },
{ 0x0022, 0x1130, 0, VR::FL, VM::M1, "Lens Thickness" },
{ 0x300A, 0x019A, 0, VR::FL, VM::M1, "Fixation Device Roll Angle" },
{ 0x4010, 0x1006, 0, VR::OB, VM::M1, "Threat ROI Bitmap" },
{ 0x5006, 0x0010, 1, VR::US, VM::M1, "Number of Points 4" },
{ 0x6016, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0343[] = {
{ 0x0010, 0x21C0, 0, VR::US, VM::M1, "Pregnancy Status" },
{ 0x0018, 0x9303, 0, VR::FD, VM::M1, "Tube Angle" },
{ 0x0022, 0x1131, 0, VR::FL, VM::M1, "Anterior Chamber Depth" },
{ 0x0040, 0x4016, 0, VR::SQ, VM::M1, "Referenced General Purpose Scheduled Procedure Step Sequence" },
{ 0x4010, 0x1007, 0, VR::SH, VM::M1, "Route Segment ID" },
{ 0x5012, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0344[] = {
{ 0x0018, 0x5000, 0, VR::SH, VM::M1TN, "Output Power" },
{ 0x0040, 0x4019, 0, VR::SQ, VM::M1, "Performed Workitem Code Sequence" },
{ 0x300A, 0x0194, 0, VR::SH, VM::M1, "Fixation Device Label" },
{ 0x4010, 0x1008, 0, VR::CS, VM::M1, "Gantry Type" },
{ 0x5008, 0x0010, 1, VR::US, VM::M1, "Number of Points 5" },
{ 0x6018, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0345[] = {
{ 0x0008, 0x1115, 0, VR::SQ, VM::M1, "Referenced Series Sequence" },
{ 0x0040, 0x4018, 0, VR::SQ, VM::M1, "Scheduled Workitem Code Sequence" },
{ 0x4008, 0x0050, 1, VR::SQ, VM::M1, "Referenced Interpretation Sequence" },
{ 0x4010, 0x1009, 0, VR::CS, VM::M1, "OOI Owner Type" },
{ 0x501C, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0346[] = {
{ 0x300A, 0x0196, 0, VR::ST, VM::M1, "Fixation Device Description" },
{ 0x4010, 0x100A, 0, VR::SQ, VM::M1, "Route Segment Sequence" },
{ 0x500A, 0x0010, 1, VR::US, VM::M1, "Number of Points 6" },
{ 0x601A, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0347[] = {
{ 0x0068, 0x64A0, 0, VR::FD, VM::M2, "Range of Freedom" },
{ 0x501E, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0348[] = {
{ 0x0008, 0x1110, 0, VR::SQ, VM::M1, "Referenced Study Sequence" },
{ 0x0018, 0x1100, 0, VR::DS, VM::M1, "Reconstruction Diameter" },
{ 0x0018, 0x1510, 0, VR::DS, VM::M1, "Positioner Primary Angle" },
{ 0x0018, 0x9308, 0, VR::SQ, VM::M1, "CT Table Dynamics Sequence" },
{ 0x0018, 0x9718, 0, VR::FD, VM::M1, "Start Respiratory Trigger Count Threshold" },
{ 0x0048, 0x0111, 0, VR::DS, VM::M1, "Condenser Lens Power" },
{ 0x300A, 0x0190, 0, VR::SQ, VM::M1, "Fixation Device Sequence" },
{ 0x500C, 0x0010, 1, VR::US, VM::M1, "Number of Points 7" },
{ 0x601C, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0349[] = {
{ 0x0008, 0x1111, 0, VR::SQ, VM::M1, "Referenced Performed Procedure Step Sequence" },
{ 0x0018, 0x1511, 0, VR::DS, VM::M1, "Positioner Secondary Angle" },
{ 0x0018, 0x9309, 0, VR::FD, VM::M1, "Table Speed" },
{ 0x0018, 0x9719, 0, VR::FD, VM::M1, "Termination Counts Threshold" },
{ 0x0048, 0x0110, 0, VR::SQ, VM::M1, "Specimen Reference Sequence" },
{ 0x5018, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0350[] = {
{ 0x0048, 0x0113, 0, VR::DS, VM::M1, "Objective Lens Numerical Aperture" },
{ 0x300A, 0x0192, 0, VR::CS, VM::M1, "Fixation Device Type" },
{ 0x500E, 0x0010, 1, VR::US, VM::M1, "Number of Points 8" },
{ 0x601E, 0x3000, 0, VR::OX, VM::M1, "Overlay Data 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0351[] = {
{ 0x0040, 0x050A, 1, VR::LO, VM::M1, "Specimen Accession Number" },
{ 0x0040, 0xA390, 0, VR::SQ, VM::M1, "HL7 Structured Document Reference Sequence" },
{ 0x0048, 0x0112, 0, VR::DS, VM::M1, "Objective Lens Power" },
{ 0x501A, 0x0005, 1, VR::US, VM::M1, "Curve Dimensions 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0352[] = {
{ 0x0018, 0x9334, 0, VR::CS, VM::M1, "Fluoroscopy Flag" },
{ 0x0018, 0x9724, 0, VR::FD, VM::M1, "Termination Respiratory Trigger Count Threshold" },
{ 0x0020, 0x5000, 1, VR::AT, VM::M1TN, "Original Image Identification" },
{ 0x0020, 0x930C, 0, VR::CS, VM::M1, "Patient Frame of Reference Source" },
{ 0x0040, 0x4021, 0, VR::SQ, VM::M1, "Input Information Sequence" },
{ 0x0046, 0x0123, 0, VR::SQ, VM::M1, "Visual Acuity Left Eye Sequence" },
{ 0x0400, 0x0565, 0, VR::CS, VM::M1, "Reason for the Attribute Modification" },
{ 0x5000, 0x0020, 1, VR::CS, VM::M1, "Type of Data" },
{ 0x5002, 0x0022, 1, VR::LO, VM::M1, "Curve Description 2" },
{ 0x5010, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0353[] = {
{ 0x0014, 0x4074, 0, VR::SH, VM::M1, "Procedure Version" },
{ 0x0018, 0x9335, 0, VR::FD, VM::M1, "Distance Source to Data Collection Center" },
{ 0x0018, 0x9725, 0, VR::CS, VM::M1, "Detector Geometry" },
{ 0x0020, 0x930D, 0, VR::FD, VM::M1, "Temporal Position Time Offset" },
{ 0x0040, 0x4020, 0, VR::CS, VM::M1, "Input Availability Flag" },
{ 0x0046, 0x0122, 0, VR::SQ, VM::M1, "Visual Acuity Right Eye Sequence" },
{ 0x0400, 0x0564, 0, VR::LO, VM::M1, "Source of Previous Values" },
{ 0x4010, 0x1031, 0, VR::CS, VM::M1, "Alarm Decision" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0354[] = {
{ 0x0018, 0x9726, 0, VR::FD, VM::M1, "Transverse Detector Separation" },
{ 0x0020, 0x5002, 1, VR::LO, VM::M1TN, "Original Image Identification Nomenclature" },
{ 0x0020, 0x930E, 0, VR::SQ, VM::M1, "Plane Position (Volume) Sequence" },
{ 0x0040, 0x4023, 0, VR::UI, VM::M1, "Referenced General Purpose Scheduled Procedure Step Transaction UID" },
{ 0x0046, 0x0121, 0, VR::SQ, VM::M1, "Visual Acuity Type Code Sequence" },
{ 0x5000, 0x0022, 1, VR::LO, VM::M1, "Curve Description" },
{ 0x5002, 0x0020, 1, VR::CS, VM::M1, "Type of Data 2" },
{ 0x5012, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0355[] = {
{ 0x0014, 0x4076, 0, VR::DA, VM::M1, "Procedure Creation Date" },
{ 0x0018, 0x9337, 0, VR::US, VM::M1, "Contrast/Bolus Agent Number" },
{ 0x0018, 0x9727, 0, VR::FD, VM::M1, "Axial Detector Dimension" },
{ 0x0020, 0x930F, 0, VR::SQ, VM::M1, "Plane Orientation (Volume) Sequence" },
{ 0x0040, 0x4022, 0, VR::SQ, VM::M1, "Relevant Information Sequence" },
{ 0x4010, 0x1033, 0, VR::US, VM::M1, "Number of Total Objects" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0356[] = {
{ 0x0018, 0x1138, 0, VR::DS, VM::M1, "Table Angle" },
{ 0x0018, 0x9330, 0, VR::FD, VM::M1, "X-Ray Tube Current in mA" },
{ 0x0018, 0x9720, 0, VR::FD, VM::M1, "Termination Density Threshold" },
{ 0x0020, 0x9308, 0, VR::FD, VM::M3, "Apex Position" },
{ 0x0040, 0x4025, 0, VR::SQ, VM::M1, "Scheduled Station Name Code Sequence" },
{ 0x0400, 0x0561, 0, VR::SQ, VM::M1, "Original Attributes Sequence" },
{ 0x300A, 0x01A8, 0, VR::SH, VM::M1, "Shielding Device Position" },
{ 0x4010, 0x1034, 0, VR::US, VM::M1, "Number of Alarm Objects" },
{ 0x5004, 0x0020, 1, VR::CS, VM::M1, "Type of Data 3" },
{ 0x5006, 0x0022, 1, VR::LO, VM::M1, "Curve Description 4" },
{ 0x5014, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0357[] = {
{ 0x0014, 0x4070, 0, VR::SQ, VM::M1, "Calibration Settings Sequence" },
{ 0x0018, 0x9721, 0, VR::FD, VM::M1, "Termination Relative Density Threshold" },
{ 0x0020, 0x9309, 0, VR::FD, VM::M16, "Volume to Transducer Mapping Matrix" },
{ 0x0022, 0x1103, 0, VR::SQ, VM::M1, "Refractive Error Before Refractive Surgery Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0358[] = {
{ 0x0018, 0x113A, 0, VR::CS, VM::M1, "Table Type" },
{ 0x0018, 0x9332, 0, VR::FD, VM::M1, "Exposure in mAs" },
{ 0x0018, 0x9722, 0, VR::FD, VM::M1, "Termination Time Threshold" },
{ 0x0020, 0x930A, 0, VR::FD, VM::M16, "Volume to Table Mapping Matrix" },
{ 0x0022, 0x1100, 0, VR::SQ, VM::M1, "Referenced Ophthalmic Axial Measurements Sequence" },
{ 0x0040, 0x4027, 0, VR::SQ, VM::M1, "Scheduled Station Geographic Location Code Sequence" },
{ 0x0046, 0x0125, 0, VR::CS, VM::M1, "Viewing Distance Type" },
{ 0x0400, 0x0563, 0, VR::LO, VM::M1, "Modifying System" },
{ 0x5004, 0x0022, 1, VR::LO, VM::M1, "Curve Description 3" },
{ 0x5006, 0x0020, 1, VR::CS, VM::M1, "Type of Data 4" },
{ 0x5016, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0359[] = {
{ 0x0010, 0x21F0, 0, VR::LO, VM::M1, "Patient's Religious Preference" },
{ 0x0014, 0x4072, 0, VR::ST, VM::M1, "Calibration Procedure" },
{ 0x0018, 0x9333, 0, VR::CS, VM::M1, "Constant Volume Flag" },
{ 0x0018, 0x9723, 0, VR::FD, VM::M1, "Termination Cardiac Trigger Count Threshold" },
{ 0x0022, 0x1101, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Segment Name Code Sequence" },
{ 0x0040, 0x4026, 0, VR::SQ, VM::M1, "Scheduled Station Class Code Sequence" },
{ 0x0046, 0x0124, 0, VR::SQ, VM::M1, "Visual Acuity Both Eyes Open Sequence" },
{ 0x0072, 0x0500, 0, VR::CS, VM::M1, "Blending Operation Type" },
{ 0x0400, 0x0562, 0, VR::DT, VM::M1, "Attribute Modification DateTime" },
{ 0x4010, 0x1037, 0, VR::SQ, VM::M1, "PTO Representation Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0360[] = {
{ 0x0018, 0x1134, 0, VR::CS, VM::M1, "Table Motion" },
{ 0x0018, 0x5030, 1, VR::DS, VM::M1, "Dynamic Range" },
{ 0x0028, 0x1104, 0, VR::US, VM::M3, "Alpha Palette Color Lookup Table Descriptor" },
{ 0x0028, 0x5000, 1, VR::SQ, VM::M1, "Bi-Plane Acquisition Sequence" },
{ 0x0040, 0x4029, 0, VR::SQ, VM::M1, "Performed Station Class Code Sequence" },
{ 0x300A, 0x01A4, 0, VR::SH, VM::M1, "Shielding Device Label" },
{ 0x4010, 0x1038, 0, VR::SQ, VM::M1, "ATD Assessment Sequence" },
{ 0x5008, 0x0020, 1, VR::CS, VM::M1, "Type of Data 5" },
{ 0x500A, 0x0022, 1, VR::LO, VM::M1, "Curve Description 6" },
{ 0x5018, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0361[] = {
{ 0x0008, 0x1125, 0, VR::SQ, VM::M1, "Referenced Visit Sequence" },
{ 0x0014, 0x407C, 0, VR::TM, VM::M1TN, "Calibration Time" },
{ 0x0018, 0x1135, 0, VR::DS, VM::M1TN, "Table Vertical Increment" },
{ 0x0040, 0x4028, 0, VR::SQ, VM::M1, "Performed Station Name Code Sequence" },
{ 0x4010, 0x1039, 0, VR::CS, VM::M1, "TIP Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0362[] = {
{ 0x0018, 0x1136, 0, VR::DS, VM::M1TN, "Table Lateral Increment" },
{ 0x300A, 0x01A6, 0, VR::ST, VM::M1, "Shielding Device Description" },
{ 0x4010, 0x103A, 0, VR::CS, VM::M1, "DICOS Version" },
{ 0x5008, 0x0022, 1, VR::LO, VM::M1, "Curve Description 5" },
{ 0x500A, 0x0020, 1, VR::CS, VM::M1, "Type of Data 6" },
{ 0x501A, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0363[] = {
{ 0x0014, 0x407E, 0, VR::DA, VM::M1TN, "Calibration Date" },
{ 0x0018, 0x1137, 0, VR::DS, VM::M1TN, "Table Longitudinal Increment" },
{ 0x0020, 0x9307, 0, VR::CS, VM::M1, "Ultrasound Acquisition Geometry" },
{ 0x0068, 0x6490, 0, VR::FD, VM::M3, "3D Degree of Freedom Axis" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0364[] = {
{ 0x0008, 0x1120, 0, VR::SQ, VM::M1, "Referenced Patient Sequence" },
{ 0x0018, 0x1130, 0, VR::DS, VM::M1, "Table Height" },
{ 0x0018, 0x1520, 0, VR::DS, VM::M1TN, "Positioner Primary Angle Increment" },
{ 0x0018, 0x9338, 0, VR::SQ, VM::M1, "Contrast/Bolus Ingredient Code Sequence" },
{ 0x0028, 0x1100, 1, VR::XS, VM::M3, "Gray Lookup Table Descriptor" },
{ 0x300A, 0x01A0, 0, VR::SQ, VM::M1, "Shielding Device Sequence" },
{ 0x500C, 0x0020, 1, VR::CS, VM::M1, "Type of Data 7" },
{ 0x500E, 0x0022, 1, VR::LO, VM::M1, "Curve Description 8" },
{ 0x501C, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0365[] = {
{ 0x0014, 0x4078, 0, VR::DA, VM::M1, "Procedure Expiration Date" },
{ 0x0018, 0x1131, 0, VR::DS, VM::M1, "Table Traverse" },
{ 0x0018, 0x1521, 0, VR::DS, VM::M1TN, "Positioner Secondary Angle Increment" },
{ 0x0018, 0x9729, 0, VR::US, VM::M1, "Radiopharmaceutical Agent Number" },
{ 0x0020, 0x9301, 0, VR::FD, VM::M3, "Image Position (Volume)" },
{ 0x0028, 0x1101, 0, VR::XS, VM::M3, "Red Palette Color Lookup Table Descriptor" },
{ 0x0048, 0x0120, 0, VR::SQ, VM::M1, "Palette Color Lookup Table Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0366[] = {
{ 0x0020, 0x9302, 0, VR::FD, VM::M6, "Image Orientation (Volume)" },
{ 0x0028, 0x1102, 0, VR::XS, VM::M3, "Green Palette Color Lookup Table Descriptor" },
{ 0x300A, 0x01A2, 0, VR::CS, VM::M1, "Shielding Device Type" },
{ 0x500C, 0x0022, 1, VR::LO, VM::M1, "Curve Description 7" },
{ 0x500E, 0x0020, 1, VR::CS, VM::M1, "Type of Data 8" },
{ 0x501E, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0367[] = {
{ 0x0014, 0x407A, 0, VR::DA, VM::M1, "Procedure Last Modified Date" },
{ 0x0028, 0x1103, 0, VR::XS, VM::M3, "Blue Palette Color Lookup Table Descriptor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0368[] = {
{ 0x0018, 0x5028, 0, VR::DS, VM::M1, "Soft Tissue-focus Thermal Index" },
{ 0x0018, 0x9324, 0, VR::FD, VM::M1, "Estimated Dose Saving" },
{ 0x0018, 0x9734, 0, VR::SQ, VM::M1, "PET Table Dynamics Sequence" },
{ 0x0040, 0x4031, 0, VR::SQ, VM::M1, "Requested Subsequent Workitem Code Sequence" },
{ 0x300A, 0x01BC, 0, VR::DS, VM::M1, "Setup Device Parameter" },
{ 0x4010, 0x1020, 0, VR::CS, VM::M1, "Route Segment Location ID Type" },
{ 0x5000, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units" },
{ 0x5010, 0x0020, 1, VR::CS, VM::M1, "Type of Data 9" },
{ 0x5012, 0x0022, 1, VR::LO, VM::M1, "Curve Description 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0369[] = {
{ 0x0014, 0x4064, 0, VR::DS, VM::M1, "Velocity of Sound" },
{ 0x0018, 0x5029, 0, VR::DS, VM::M1, "Soft Tissue-surface Thermal Index" },
{ 0x0018, 0x9325, 0, VR::SQ, VM::M1, "CT X-Ray Details Sequence" },
{ 0x0018, 0x9735, 0, VR::SQ, VM::M1, "PET Position Sequence" },
{ 0x0040, 0x4030, 0, VR::SQ, VM::M1, "Performed Station Geographic Location Code Sequence" },
{ 0x0072, 0x0106, 0, VR::US, VM::M1, "Number of Horizontal Pixels" },
{ 0x0072, 0x0516, 0, VR::CS, VM::M1, "Reformatting Operation Initial View Direction" },
{ 0x4010, 0x1021, 0, VR::CS, VM::M1TN, "Abort Reason" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0370[] = {
{ 0x0018, 0x9326, 0, VR::SQ, VM::M1, "CT Position Sequence" },
{ 0x0018, 0x9736, 0, VR::SQ, VM::M1, "PET Frame Correction Factors Sequence" },
{ 0x0040, 0x4033, 0, VR::SQ, VM::M1, "Output Information Sequence" },
{ 0x5002, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 2" },
{ 0x5010, 0x0022, 1, VR::LO, VM::M1, "Curve Description 9" },
{ 0x5012, 0x0020, 1, VR::CS, VM::M1, "Type of Data 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0371[] = {
{ 0x0018, 0x9327, 0, VR::FD, VM::M1, "Table Position" },
{ 0x0018, 0x9737, 0, VR::SQ, VM::M1, "Radiopharmaceutical Usage Sequence" },
{ 0x0040, 0x4032, 0, VR::SQ, VM::M1, "Non-DICOM Output Code Sequence" },
{ 0x0072, 0x0104, 0, VR::US, VM::M1, "Number of Vertical Pixels" },
{ 0x0072, 0x0514, 0, VR::FD, VM::M1, "Reformatting Interval" },
{ 0x4010, 0x1023, 0, VR::FL, VM::M1, "Volume of PTO" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0372[] = {
{ 0x0018, 0x9320, 0, VR::SH, VM::M1, "Image Filter" },
{ 0x0040, 0x4035, 0, VR::SQ, VM::M1, "Actual Human Performers Sequence" },
{ 0x0046, 0x0137, 0, VR::FD, VM::M1, "Decimal Visual Acuity" },
{ 0x0070, 0x0101, 0, VR::DS, VM::M2, "Presentation Pixel Spacing" },
{ 0x300A, 0x01B8, 0, VR::SH, VM::M1, "Setup Device Label" },
{ 0x4010, 0x1024, 0, VR::CS, VM::M1, "Abort Flag" },
{ 0x5004, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 3" },
{ 0x5014, 0x0020, 1, VR::CS, VM::M1, "Type of Data 11" },
{ 0x5016, 0x0022, 1, VR::LO, VM::M1, "Curve Description 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0373[] = {
{ 0x0014, 0x4060, 0, VR::SQ, VM::M1, "Gate Settings Sequence" },
{ 0x0018, 0x9321, 0, VR::SQ, VM::M1, "CT Exposure Sequence" },
{ 0x0040, 0x0520, 0, VR::SQ, VM::M1, "Container Component Sequence" },
{ 0x0040, 0x4034, 0, VR::SQ, VM::M1, "Scheduled Human Performers Sequence" },
{ 0x0070, 0x0100, 0, VR::CS, VM::M1, "Presentation Size Mode" },
{ 0x0072, 0x0102, 0, VR::SQ, VM::M1, "Nominal Screen Definition Sequence" },
{ 0x0072, 0x0512, 0, VR::FD, VM::M1, "Reformatting Thickness" },
{ 0x4010, 0x1025, 0, VR::DT, VM::M1, "Route Segment Start Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0374[] = {
{ 0x0008, 0x113A, 0, VR::SQ, VM::M1, "Referenced Waveform Sequence" },
{ 0x0018, 0x9322, 0, VR::FD, VM::M2, "Reconstruction Pixel Spacing" },
{ 0x0018, 0x9732, 0, VR::SQ, VM::M1, "PET Frame Acquisition Sequence" },
{ 0x0040, 0x4037, 0, VR::PN, VM::M1, "Human Performer's Name" },
{ 0x0046, 0x0135, 0, VR::SS, VM::M2, "Visual Acuity Modifiers" },
{ 0x0070, 0x0103, 0, VR::FL, VM::M1, "Presentation Pixel Magnification Ratio" },
{ 0x300A, 0x01BA, 0, VR::ST, VM::M1, "Setup Device Description" },
{ 0x4010, 0x1026, 0, VR::DT, VM::M1, "Route Segment End Time" },
{ 0x5006, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 4" },
{ 0x5014, 0x0022, 1, VR::LO, VM::M1, "Curve Description 11" },
{ 0x5016, 0x0020, 1, VR::CS, VM::M1, "Type of Data 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0375[] = {
{ 0x0014, 0x4062, 0, VR::DS, VM::M1, "Gate Threshold" },
{ 0x0018, 0x9323, 0, VR::CS, VM::M1, "Exposure Modulation Type" },
{ 0x0018, 0x9733, 0, VR::SQ, VM::M1, "PET Detector Motion Details Sequence" },
{ 0x0040, 0x4036, 0, VR::LO, VM::M1, "Human Performer's Organization" },
{ 0x0070, 0x0102, 0, VR::IS, VM::M2, "Presentation Pixel Aspect Ratio" },
{ 0x0072, 0x0100, 0, VR::US, VM::M1, "Number of Screens" },
{ 0x0072, 0x0510, 0, VR::CS, VM::M1, "Reformatting Operation Type" },
{ 0x2130, 0x00C0, 1, VR::SQ, VM::M1, "Original Image Sequence" },
{ 0x4010, 0x1027, 0, VR::CS, VM::M1, "TDR Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0376[] = {
{ 0x0008, 0x1134, 0, VR::SQ, VM::M1, "Referenced Stereometric Instance Sequence" },
{ 0x0018, 0x5020, 0, VR::LO, VM::M1, "Processing Function" },
{ 0x300A, 0x01B4, 0, VR::SQ, VM::M1, "Setup Device Sequence" },
{ 0x4010, 0x1028, 0, VR::CS, VM::M1, "International Route Segment" },
{ 0x5008, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 5" },
{ 0x5018, 0x0020, 1, VR::CS, VM::M1, "Type of Data 13" },
{ 0x501A, 0x0022, 1, VR::LO, VM::M1, "Curve Description 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0377[] = {
{ 0x0018, 0x5021, 1, VR::LO, VM::M1, "Postprocessing Function" },
{ 0x0072, 0x010E, 0, VR::US, VM::M1, "Application Maximum Repaint Time" },
{ 0x4010, 0x1029, 0, VR::LO, VM::M1TN, "Threat Detection Algorithm and Version" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0378[] = {
{ 0x0018, 0x5022, 0, VR::DS, VM::M1, "Mechanical Index" },
{ 0x0046, 0x0139, 0, VR::LO, VM::M1, "Optotype Detailed Definition" },
{ 0x300A, 0x01B6, 0, VR::CS, VM::M1, "Setup Device Type" },
{ 0x4010, 0x102A, 0, VR::SH, VM::M1, "Assigned Location" },
{ 0x500A, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 6" },
{ 0x5018, 0x0022, 1, VR::LO, VM::M1, "Curve Description 13" },
{ 0x501A, 0x0020, 1, VR::CS, VM::M1, "Type of Data 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0379[] = {
{ 0x0072, 0x010C, 0, VR::US, VM::M1, "Screen Minimum Color Bit Depth" },
{ 0x4010, 0x102B, 0, VR::DT, VM::M1, "Alarm Decision Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0380[] = {
{ 0x0008, 0x1130, 1, VR::SQ, VM::M1, "Referenced Overlay Sequence" },
{ 0x0018, 0x1120, 0, VR::DS, VM::M1, "Gantry/Detector Tilt" },
{ 0x0018, 0x1530, 0, VR::DS, VM::M1, "Detector Primary Angle" },
{ 0x0018, 0x5024, 0, VR::DS, VM::M1, "Bone Thermal Index" },
{ 0x0018, 0x9328, 0, VR::FD, VM::M1, "Exposure Time in ms" },
{ 0x0018, 0x9738, 0, VR::CS, VM::M1, "Attenuation Correction Source" },
{ 0x0020, 0x9310, 0, VR::SQ, VM::M1, "Temporal Position Sequence" },
{ 0x300A, 0x01B0, 0, VR::CS, VM::M1, "Setup Technique" },
{ 0x500C, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 7" },
{ 0x501C, 0x0020, 1, VR::CS, VM::M1, "Type of Data 15" },
{ 0x501E, 0x0022, 1, VR::LO, VM::M1, "Curve Description 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0381[] = {
{ 0x0018, 0x1121, 0, VR::DS, VM::M1, "Gantry/Detector Slew" },
{ 0x0018, 0x1531, 0, VR::DS, VM::M1, "Detector Secondary Angle" },
{ 0x0018, 0x9329, 0, VR::SQ, VM::M1, "CT Image Frame Type Sequence" },
{ 0x0018, 0x9739, 0, VR::US, VM::M1, "Number of Iterations" },
{ 0x0020, 0x9311, 0, VR::CS, VM::M1, "Dimension Organization Type" },
{ 0x0028, 0x1111, 1, VR::XS, VM::M4, "Large Red Palette Color Lookup Table Descriptor" },
{ 0x0072, 0x010A, 0, VR::US, VM::M1, "Screen Minimum Grayscale Bit Depth" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0382[] = {
{ 0x0018, 0x5026, 0, VR::DS, VM::M1, "Cranial Thermal Index" },
{ 0x0020, 0x9312, 0, VR::UI, VM::M1, "Volume Frame of Reference UID" },
{ 0x0028, 0x1112, 1, VR::XS, VM::M4, "Large Green Palette Color Lookup Table Descriptor" },
{ 0x300A, 0x01B2, 0, VR::ST, VM::M1, "Setup Technique Description" },
{ 0x500E, 0x0030, 1, VR::SH, VM::M1TN, "Axis Units 8" },
{ 0x501C, 0x0022, 1, VR::LO, VM::M1, "Curve Description 15" },
{ 0x501E, 0x0020, 1, VR::CS, VM::M1, "Type of Data 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0383[] = {
{ 0x0018, 0x5027, 0, VR::DS, VM::M1, "Soft Tissue Thermal Index" },
{ 0x0020, 0x9313, 0, VR::UI, VM::M1, "Table Frame of Reference UID" },
{ 0x0028, 0x1113, 1, VR::XS, VM::M4, "Large Blue Palette Color Lookup Table Descriptor" },
{ 0x0072, 0x0108, 0, VR::FD, VM::M4, "Display Environment Spatial Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0384[] = {
{ 0x0018, 0x6018, 0, VR::UL, VM::M1, "Region Location Min X0" },
{ 0x5000, 0x3000, 1, VR::OX, VM::M1, "Curve Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0385[] = {
{ 0x0018, 0x7058, 0, VR::FL, VM::M1TN, "Filter Beam Path Length Maximum" },
{ 0x300A, 0x014E, 0, VR::FL, VM::M1, "Gantry Pitch Angle Tolerance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0386[] = {
{ 0x0018, 0x601A, 0, VR::UL, VM::M1, "Region Location Min Y0" },
{ 0x5002, 0x3000, 1, VR::OX, VM::M1, "Curve Data 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0387[] = {
{ 0x300A, 0x014C, 0, VR::CS, VM::M1, "Gantry Pitch Rotation Direction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0388[] = {
{ 0x0010, 0x2110, 0, VR::LO, VM::M1TN, "Allergies" },
{ 0x0018, 0x601C, 0, VR::UL, VM::M1, "Region Location Max X1" },
{ 0x2000, 0x0510, 1, VR::SQ, VM::M1, "Referenced Stored Print  Sequence" },
{ 0x2010, 0x0110, 0, VR::CS, VM::M1, "Empty Image Density" },
{ 0x2010, 0x0500, 0, VR::SQ, VM::M1, "Referenced Film Session Sequence" },
{ 0x2110, 0x0010, 0, VR::CS, VM::M1, "Printer Status" },
{ 0x2130, 0x0030, 1, VR::SQ, VM::M1, "Film Box Content Sequence" },
{ 0x5004, 0x3000, 1, VR::OX, VM::M1, "Curve Data 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0389[] = {
{ 0x300A, 0x014A, 0, VR::FL, VM::M1, "Gantry Pitch Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0390[] = {
{ 0x0018, 0x601E, 0, VR::UL, VM::M1, "Region Location Max Y1" },
{ 0x5006, 0x3000, 1, VR::OX, VM::M1, "Curve Data 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0391[] = {
{ 0x300A, 0x0148, 0, VR::FL, VM::M1, "Head Fixation Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0392[] = {
{ 0x0028, 0x6020, 0, VR::US, VM::M1TN, "Frame Numbers of Interest (FOI)" },
{ 0x0068, 0x6470, 0, VR::SQ, VM::M1, "2D Degree of Freedom Sequence" },
{ 0x5008, 0x3000, 1, VR::OX, VM::M1, "Curve Data 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0393[] = {
{ 0x0018, 0x6011, 0, VR::SQ, VM::M1, "Sequence of Ultrasound Regions" },
{ 0x0018, 0x7050, 0, VR::CS, VM::M1TN, "Filter Material" },
{ 0x300A, 0x0146, 0, VR::CS, VM::M1, "Table Top Roll Rotation Direction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0394[] = {
{ 0x0018, 0x6012, 0, VR::US, VM::M1, "Region Spatial Format" },
{ 0x0028, 0x6022, 0, VR::LO, VM::M1TN, "Frame of Interest Description" },
{ 0x500A, 0x3000, 1, VR::OX, VM::M1, "Curve Data 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0395[] = {
{ 0x0018, 0x7052, 0, VR::DS, VM::M1TN, "Filter Thickness Minimum" },
{ 0x0028, 0x6023, 0, VR::CS, VM::M1TN, "Frame of Interest Type" },
{ 0x300A, 0x0144, 0, VR::FL, VM::M1, "Table Top Roll Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0396[] = {
{ 0x0018, 0x6014, 0, VR::US, VM::M1, "Region Data Type" },
{ 0x0040, 0xA340, 1, VR::SQ, VM::M1, "Procedure Context Sequence (Trial)" },
{ 0x500C, 0x3000, 1, VR::OX, VM::M1, "Curve Data 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0397[] = {
{ 0x0018, 0x7054, 0, VR::DS, VM::M1TN, "Filter Thickness Maximum" },
{ 0x3008, 0x0140, 0, VR::SQ, VM::M1, "Recorded Source Applicator Sequence" },
{ 0x300A, 0x0142, 0, VR::CS, VM::M1, "Table Top Pitch Rotation Direction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0398[] = {
{ 0x0018, 0x6016, 0, VR::UL, VM::M1, "Region Flags" },
{ 0x500E, 0x3000, 1, VR::OX, VM::M1, "Curve Data 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0399[] = {
{ 0x0018, 0x7056, 0, VR::FL, VM::M1TN, "Filter Beam Path Length Minimum" },
{ 0x3008, 0x0142, 0, VR::IS, VM::M1, "Referenced Source Applicator Number" },
{ 0x300A, 0x0140, 0, VR::FL, VM::M1, "Table Top Pitch Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0400[] = {
{ 0x5010, 0x3000, 1, VR::OX, VM::M1, "Curve Data 9" },
{ 0x6000, 0x0010, 0, VR::US, VM::M1, "Overlay Rows" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0401[] = {
{ 0x0018, 0x7048, 0, VR::DS, VM::M1, "Grid Period" },
{ 0x6000, 0x0011, 0, VR::US, VM::M1, "Overlay Columns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0402[] = {
{ 0x5012, 0x3000, 1, VR::OX, VM::M1, "Curve Data 10" },
{ 0x6000, 0x0012, 1, VR::US, VM::M1, "Overlay Planes" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0403[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0404[] = {
{ 0x0040, 0xA358, 1, VR::SQ, VM::M1, "Verbal Source Identifier Code Sequence (Trial)" },
{ 0x2000, 0x0500, 0, VR::SQ, VM::M1, "Referenced Film Box Sequence" },
{ 0x2010, 0x0100, 0, VR::CS, VM::M1, "Border Density" },
{ 0x2010, 0x0510, 0, VR::SQ, VM::M1, "Referenced Image Box Sequence" },
{ 0x2020, 0x0130, 1, VR::SQ, VM::M1, "Referenced Image Overlay Box Sequence" },
{ 0x2100, 0x0010, 1, VR::SH, VM::M1, "Print Job ID" },
{ 0x5014, 0x3000, 1, VR::OX, VM::M1, "Curve Data 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0405[] = {
{ 0x0018, 0x704C, 0, VR::DS, VM::M1, "Grid Focal Distance" },
{ 0x6000, 0x0015, 0, VR::IS, VM::M1, "Number of Frames in Overlay" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0406[] = {
{ 0x5016, 0x3000, 1, VR::OX, VM::M1, "Curve Data 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0407[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0408[] = {
{ 0x0018, 0x6000, 0, VR::DS, VM::M1, "Sensitivity" },
{ 0x0018, 0x7041, 0, VR::LT, VM::M1, "Grid Spacing Material" },
{ 0x0028, 0x6030, 1, VR::US, VM::M1TN, "Mask Pointer(s)" },
{ 0x0040, 0xA354, 1, VR::LO, VM::M1, "Telephone Number (Trial)" },
{ 0x0040, 0xA744, 1, VR::SQ, VM::M1, "Language Code Sequence (Trial)" },
{ 0x0068, 0x6460, 0, VR::FD, VM::M4, "2D Mating Axes" },
{ 0x5018, 0x3000, 1, VR::OX, VM::M1, "Curve Data 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0409[] = {
{ 0x0018, 0x7040, 0, VR::LT, VM::M1, "Grid Absorbing Material" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0410[] = {
{ 0x501A, 0x3000, 1, VR::OX, VM::M1, "Curve Data 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0411[] = {
{ 0x0018, 0x7042, 0, VR::DS, VM::M1, "Grid Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0412[] = {
{ 0x0008, 0x2110, 1, VR::CS, VM::M1, "Lossy Image Compression (Retired)" },
{ 0x501C, 0x3000, 1, VR::OX, VM::M1, "Curve Data 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0413[] = {
{ 0x0008, 0x2111, 0, VR::ST, VM::M1, "Derivation Description" },
{ 0x0018, 0x7044, 0, VR::DS, VM::M1, "Grid Pitch" },
{ 0x3008, 0x0150, 0, VR::SQ, VM::M1, "Recorded Channel Shield Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0414[] = {
{ 0x0008, 0x2112, 0, VR::SQ, VM::M1, "Source Image Sequence" },
{ 0x0040, 0x09F8, 1, VR::SQ, VM::M1, "Vital Stain Code Sequence (Trial)" },
{ 0x0040, 0xA352, 1, VR::PN, VM::M1, "Verbal Source (Trial)" },
{ 0x501E, 0x3000, 1, VR::OX, VM::M1, "Curve Data 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0415[] = {
{ 0x0018, 0x7046, 0, VR::IS, VM::M2, "Grid Aspect Ratio" },
{ 0x0040, 0xA353, 1, VR::ST, VM::M1, "Address (Trial)" },
{ 0x3008, 0x0152, 0, VR::IS, VM::M1, "Referenced Channel Shield Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0416[] = {
{ 0x0018, 0x6038, 1, VR::UL, VM::M1, "Doppler Sample Volume X Position (Retired)" },
{ 0x6000, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label" },
{ 0x6002, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 2" },
{ 0x6004, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0417[] = {
{ 0x0018, 0x6039, 0, VR::SL, VM::M1, "Doppler Sample Volume X Position" },
{ 0x2130, 0x0015, 1, VR::SQ, VM::M1, "Printer Characteristics Sequence" },
{ 0x6002, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0418[] = {
{ 0x0018, 0x603A, 1, VR::UL, VM::M1, "Doppler Sample Volume Y Position (Retired)" },
{ 0x6000, 0x0022, 0, VR::LO, VM::M1, "Overlay Description" },
{ 0x6000, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables" },
{ 0x6002, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 2" },
{ 0x6006, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0419[] = {
{ 0x0018, 0x603B, 0, VR::SL, VM::M1, "Doppler Sample Volume Y Position" },
{ 0x6000, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0420[] = {
{ 0x0008, 0x2128, 0, VR::IS, VM::M1, "View Number" },
{ 0x0018, 0x603C, 1, VR::UL, VM::M1, "TM-Line Position X0 (Retired)" },
{ 0x2010, 0x0130, 0, VR::US, VM::M1, "Max Density" },
{ 0x2010, 0x0520, 0, VR::SQ, VM::M1, "Referenced Basic Annotation Box Sequence" },
{ 0x2100, 0x0020, 0, VR::CS, VM::M1, "Execution Status" },
{ 0x2110, 0x0030, 0, VR::LO, VM::M1, "Printer Name" },
{ 0x2130, 0x0010, 1, VR::SQ, VM::M1, "Print Management Capabilities Sequence" },
{ 0x6000, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word" },
{ 0x6004, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 3" },
{ 0x6006, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0421[] = {
{ 0x0008, 0x2129, 0, VR::IS, VM::M1, "Number of Event Timers" },
{ 0x0018, 0x603D, 0, VR::SL, VM::M1, "TM-Line Position X0" },
{ 0x3008, 0x0168, 0, VR::TM, VM::M1, "Safe Position Return Time" },
{ 0x6006, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0422[] = {
{ 0x0008, 0x212A, 0, VR::IS, VM::M1, "Number of Views in Stage" },
{ 0x0018, 0x603E, 1, VR::UL, VM::M1, "TM-Line Position Y0 (Retired)" },
{ 0x6002, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 2" },
{ 0x6004, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 3" },
{ 0x6006, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0423[] = {
{ 0x0018, 0x603F, 0, VR::SL, VM::M1, "TM-Line Position Y0" },
{ 0x6004, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0424[] = {
{ 0x0008, 0x2124, 0, VR::IS, VM::M1, "Number of Stages" },
{ 0x0018, 0x6030, 0, VR::UL, VM::M1, "Transducer Frequency" },
{ 0x0068, 0x6450, 0, VR::FD, VM::M2, "2D Mating Point" },
{ 0x0088, 0x0906, 1, VR::ST, VM::M1, "Topic Subject" },
{ 0x6008, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 5" },
{ 0x600A, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 6" },
{ 0x600C, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0425[] = {
{ 0x0018, 0x6031, 0, VR::CS, VM::M1, "Transducer Type" },
{ 0x3008, 0x0164, 0, VR::TM, VM::M1, "Safe Position Exit Time" },
{ 0x600A, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0426[] = {
{ 0x0018, 0x6032, 0, VR::UL, VM::M1, "Pulse Repetition Frequency" },
{ 0x0088, 0x0904, 1, VR::LO, VM::M1, "Topic Title" },
{ 0x6008, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 5" },
{ 0x600A, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 6" },
{ 0x600E, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0427[] = {
{ 0x0008, 0x2127, 0, VR::SH, VM::M1, "View Name" },
{ 0x3008, 0x0166, 0, VR::DA, VM::M1, "Safe Position Return Date" },
{ 0x6008, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0428[] = {
{ 0x0008, 0x2120, 0, VR::SH, VM::M1, "Stage Name" },
{ 0x0018, 0x6034, 0, VR::FD, VM::M1, "Doppler Correction Angle" },
{ 0x0040, 0xA360, 0, VR::SQ, VM::M1, "Predecessor Documents Sequence" },
{ 0x6008, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 5" },
{ 0x600C, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 7" },
{ 0x600E, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0429[] = {
{ 0x3008, 0x0160, 0, VR::SQ, VM::M1, "Brachy Control Point Delivered Sequence" },
{ 0x600E, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0430[] = {
{ 0x0008, 0x2122, 0, VR::IS, VM::M1, "Stage Number" },
{ 0x0018, 0x6036, 0, VR::FD, VM::M1, "Steering Angle" },
{ 0x600A, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 6" },
{ 0x600C, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 7" },
{ 0x600E, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0431[] = {
{ 0x3008, 0x0162, 0, VR::DA, VM::M1, "Safe Position Exit Date" },
{ 0x600C, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0432[] = {
{ 0x0018, 0x6028, 0, VR::FD, VM::M1, "Reference Pixel Physical Value X" },
{ 0x6010, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 9" },
{ 0x6012, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 10" },
{ 0x6014, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0433[] = {
{ 0x6012, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0434[] = {
{ 0x0018, 0x602A, 0, VR::FD, VM::M1, "Reference Pixel Physical Value Y" },
{ 0x6010, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 9" },
{ 0x6012, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 10" },
{ 0x6016, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0435[] = {
{ 0x6010, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0436[] = {
{ 0x0018, 0x602C, 0, VR::FD, VM::M1, "Physical Delta X" },
{ 0x2010, 0x0120, 0, VR::US, VM::M1, "Min Density" },
{ 0x2020, 0x0110, 0, VR::SQ, VM::M1, "Basic Grayscale Image Sequence" },
{ 0x2100, 0x0030, 0, VR::CS, VM::M1, "Execution Status Info" },
{ 0x2110, 0x0020, 0, VR::CS, VM::M1, "Printer Status Info" },
{ 0x2120, 0x0010, 1, VR::CS, VM::M1, "Queue Status" },
{ 0x6010, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 9" },
{ 0x6014, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 11" },
{ 0x6016, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0437[] = {
{ 0x2020, 0x0111, 0, VR::SQ, VM::M1, "Basic Color Image Sequence" },
{ 0x6016, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0438[] = {
{ 0x0018, 0x602E, 0, VR::FD, VM::M1, "Physical Delta Y" },
{ 0x6012, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 10" },
{ 0x6014, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 11" },
{ 0x6016, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0439[] = {
{ 0x6014, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0440[] = {
{ 0x0008, 0x2134, 0, VR::FD, VM::M1, "Event Time Offset" },
{ 0x0018, 0x6020, 0, VR::SL, VM::M1, "Reference Pixel X0" },
{ 0x0028, 0x2114, 0, VR::CS, VM::M1TN, "Lossy Image Compression Method" },
{ 0x0028, 0x6010, 0, VR::US, VM::M1, "Representative Frame Number" },
{ 0x0068, 0x6440, 0, VR::US, VM::M1, "Referenced HPGL Document ID" },
{ 0x6018, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 13" },
{ 0x601A, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 14" },
{ 0x601C, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0441[] = {
{ 0x0008, 0x2135, 0, VR::SQ, VM::M1, "Event Code Sequence" },
{ 0x0018, 0x7060, 0, VR::CS, VM::M1, "Exposure Control Mode" },
{ 0x0040, 0xA375, 0, VR::SQ, VM::M1, "Current Requested Procedure Evidence Sequence" },
{ 0x601A, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0442[] = {
{ 0x0018, 0x6022, 0, VR::SL, VM::M1, "Reference Pixel Y0" },
{ 0x6018, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 13" },
{ 0x601A, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 14" },
{ 0x601E, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0443[] = {
{ 0x0018, 0x7062, 0, VR::LT, VM::M1, "Exposure Control Mode Description" },
{ 0x6018, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0444[] = {
{ 0x0008, 0x2130, 0, VR::DS, VM::M1TN, "Event Elapsed Time(s)" },
{ 0x0018, 0x6024, 0, VR::US, VM::M1, "Physical Units X Direction" },
{ 0x0018, 0x7065, 0, VR::DS, VM::M1, "Phototimer Setting" },
{ 0x0028, 0x2110, 0, VR::CS, VM::M1, "Lossy Image Compression" },
{ 0x0040, 0xA370, 0, VR::SQ, VM::M1, "Referenced Request Sequence" },
{ 0x0088, 0x0912, 1, VR::LO, VM::M1T32, "Topic Keywords" },
{ 0x6018, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 13" },
{ 0x601C, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 15" },
{ 0x601E, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0445[] = {
{ 0x0018, 0x7064, 0, VR::CS, VM::M1, "Exposure Status" },
{ 0x601E, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0446[] = {
{ 0x0008, 0x2132, 0, VR::LO, VM::M1TN, "Event Timer Name(s)" },
{ 0x0018, 0x6026, 0, VR::US, VM::M1, "Physical Units Y Direction" },
{ 0x0028, 0x2112, 0, VR::DS, VM::M1TN, "Lossy Image Compression Ratio" },
{ 0x0040, 0xA372, 0, VR::SQ, VM::M1, "Performed Procedure Code Sequence" },
{ 0x0088, 0x0130, 0, VR::SH, VM::M1, "Storage Media File-set ID" },
{ 0x0088, 0x0910, 1, VR::LO, VM::M1, "Topic Author" },
{ 0x601A, 0x0804, 1, VR::US, VM::M1, "Overlay Bits For Code Word 14" },
{ 0x601C, 0x0802, 1, VR::US, VM::M1, "Overlay Number of Tables 15" },
{ 0x601E, 0x0800, 1, VR::CS, VM::M1TN, "Overlay Code Label 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0447[] = {
{ 0x0008, 0x2133, 0, VR::SQ, VM::M1, "Event Timer Sequence" },
{ 0x601C, 0x0803, 1, VR::AT, VM::M1TN, "Overlay Code Table Location 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0448[] = {
{ 0x300A, 0x010E, 0, VR::DS, VM::M1, "Final Cumulative Meterset Weight" },
{ 0x5000, 0x2000, 1, VR::US, VM::M1, "Audio Type" },
{ 0x5002, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 2" },
{ 0x5004, 0x2004, 1, VR::US, VM::M1, "Number of Channels 3" },
{ 0x5006, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 4" },
{ 0x5008, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 5" },
{ 0x500A, 0x200A, 1, VR::UL, VM::M1, "Total Time 6" },
{ 0x500C, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 7" },
{ 0x500E, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0449[] = {
{ 0x0010, 0x2154, 0, VR::SH, VM::M1TN, "Patient's Telephone Numbers" },
{ 0x0018, 0x6058, 0, VR::UL, VM::M1TN, "Table of Pixel Values" },
{ 0x2010, 0x0154, 0, VR::IS, VM::M1, "Maximum Collated Films" },
{ 0x6000, 0x0040, 0, VR::CS, VM::M1, "Overlay Type" },
{ 0x6000, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0450[] = {
{ 0x0018, 0x701A, 0, VR::DS, VM::M2, "Detector Binning" },
{ 0x300A, 0x010C, 0, VR::DS, VM::M1, "Cumulative Dose Reference Coefficient" },
{ 0x5000, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format" },
{ 0x5002, 0x2000, 1, VR::US, VM::M1, "Audio Type 2" },
{ 0x5004, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 3" },
{ 0x5006, 0x2004, 1, VR::US, VM::M1, "Number of Channels 4" },
{ 0x5008, 0x200A, 1, VR::UL, VM::M1, "Total Time 5" },
{ 0x500A, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 6" },
{ 0x500C, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 7" },
{ 0x500E, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0451[] = {
{ 0x0018, 0x605A, 0, VR::FL, VM::M1TN, "Table of Parameter Values" },
{ 0x6002, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0452[] = {
{ 0x300A, 0x010A, 0, VR::LO, VM::M1, "Applicator Description" },
{ 0x5000, 0x2004, 1, VR::US, VM::M1, "Number of Channels" },
{ 0x5002, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 2" },
{ 0x5004, 0x2000, 1, VR::US, VM::M1, "Audio Type 3" },
{ 0x5006, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 4" },
{ 0x5008, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 5" },
{ 0x500A, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 6" },
{ 0x500C, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 7" },
{ 0x500E, 0x200A, 1, VR::UL, VM::M1, "Total Time 8" },
{ 0x6000, 0x0045, 0, VR::LO, VM::M1, "Overlay Subtype" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0453[] = {
{ 0x0010, 0x2150, 0, VR::LO, VM::M1, "Country of Residence" },
{ 0x2010, 0x0150, 0, VR::ST, VM::M1, "Configuration Information" },
{ 0x2040, 0x0100, 1, VR::CS, VM::M1, "Threshold Density" },
{ 0x2050, 0x0500, 0, VR::SQ, VM::M1, "Referenced Presentation  LUT Sequence" },
{ 0x2100, 0x0040, 0, VR::DA, VM::M1, "Creation Date" },
{ 0x6004, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0454[] = {
{ 0x300A, 0x0108, 0, VR::SH, VM::M1, "Applicator ID" },
{ 0x5000, 0x2006, 1, VR::UL, VM::M1, "Number of Samples" },
{ 0x5002, 0x2004, 1, VR::US, VM::M1, "Number of Channels 2" },
{ 0x5004, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 3" },
{ 0x5006, 0x2000, 1, VR::US, VM::M1, "Audio Type 4" },
{ 0x5008, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 5" },
{ 0x500A, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 6" },
{ 0x500C, 0x200A, 1, VR::UL, VM::M1, "Total Time 7" },
{ 0x500E, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0455[] = {
{ 0x0010, 0x2152, 0, VR::LO, VM::M1, "Region of Residence" },
{ 0x0040, 0xA30A, 0, VR::DS, VM::M1TN, "Numeric Value" },
{ 0x2010, 0x0152, 0, VR::LT, VM::M1, "Configuration Information Description" },
{ 0x300A, 0x0109, 0, VR::CS, VM::M1, "Applicator Type" },
{ 0x6006, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0456[] = {
{ 0x0018, 0x7010, 0, VR::IS, VM::M1, "Exposures on Detector Since Last Calibration" },
{ 0x300A, 0x0106, 0, VR::DS, VM::M2T2N, "Block Data" },
{ 0x300C, 0x0100, 0, VR::IS, VM::M1, "Referenced Range Shifter Number" },
{ 0x5000, 0x2008, 1, VR::UL, VM::M1, "Sample Rate" },
{ 0x5002, 0x200A, 1, VR::UL, VM::M1, "Total Time 2" },
{ 0x5004, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 3" },
{ 0x5006, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 4" },
{ 0x5008, 0x2000, 1, VR::US, VM::M1, "Audio Type 5" },
{ 0x500A, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 6" },
{ 0x500C, 0x2004, 1, VR::US, VM::M1, "Number of Channels 7" },
{ 0x500E, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0457[] = {
{ 0x0008, 0x2144, 0, VR::IS, VM::M1, "Recommended Display Frame Rate" },
{ 0x0018, 0x6050, 0, VR::UL, VM::M1, "Number of Table Break Points" },
{ 0x0018, 0x7011, 0, VR::IS, VM::M1, "Exposures on Detector Since Manufactured" },
{ 0x0068, 0x6430, 0, VR::SQ, VM::M1, "2D Mating Feature Coordinates Sequence" },
{ 0x3008, 0x0105, 0, VR::LO, VM::M1, "Source Serial Number" },
{ 0x300A, 0x0107, 0, VR::SQ, VM::M1, "Applicator Sequence" },
{ 0x6008, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0458[] = {
{ 0x0018, 0x7012, 0, VR::DS, VM::M1, "Detector Time Since Last Exposure" },
{ 0x0040, 0xA307, 1, VR::PN, VM::M1, "Current Observer (Trial)" },
{ 0x300A, 0x0104, 0, VR::IS, VM::M1, "Block Number of Points" },
{ 0x300C, 0x0102, 0, VR::IS, VM::M1, "Referenced Lateral Spreading Device Number" },
{ 0x5000, 0x200A, 1, VR::UL, VM::M1, "Total Time" },
{ 0x5002, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 2" },
{ 0x5004, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 3" },
{ 0x5006, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 4" },
{ 0x5008, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 5" },
{ 0x500A, 0x2000, 1, VR::US, VM::M1, "Audio Type 6" },
{ 0x500C, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 7" },
{ 0x500E, 0x2004, 1, VR::US, VM::M1, "Number of Channels 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0459[] = {
{ 0x0018, 0x6052, 0, VR::UL, VM::M1TN, "Table of X Break Points" },
{ 0x2010, 0x015E, 0, VR::US, VM::M1, "Illumination" },
{ 0x600A, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0460[] = {
{ 0x0018, 0x7014, 0, VR::DS, VM::M1, "Detector Active Time" },
{ 0x0040, 0xA301, 0, VR::SQ, VM::M1, "Numeric Value Qualifier Code Sequence" },
{ 0x3008, 0x0100, 0, VR::SQ, VM::M1, "Recorded Source Sequence" },
{ 0x300A, 0x0102, 0, VR::DS, VM::M1, "Block Transmission" },
{ 0x300C, 0x0104, 0, VR::IS, VM::M1, "Referenced Range Modulator Number" },
{ 0x5000, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data" },
{ 0x5002, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 2" },
{ 0x5004, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 3" },
{ 0x5006, 0x200A, 1, VR::UL, VM::M1, "Total Time 4" },
{ 0x5008, 0x2004, 1, VR::US, VM::M1, "Number of Channels 5" },
{ 0x500A, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 6" },
{ 0x500C, 0x2000, 1, VR::US, VM::M1, "Audio Type 7" },
{ 0x500E, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0461[] = {
{ 0x0018, 0x6054, 0, VR::FD, VM::M1TN, "Table of Y Break Points" },
{ 0x0040, 0x059A, 0, VR::SQ, VM::M1, "Specimen Type Code Sequence" },
{ 0x0040, 0xA300, 0, VR::SQ, VM::M1, "Measured Value Sequence" },
{ 0x600C, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0462[] = {
{ 0x0008, 0x2143, 0, VR::IS, VM::M1, "Stop Trim" },
{ 0x0018, 0x1190, 0, VR::DS, VM::M1TN, "Focal Spot(s)" },
{ 0x0018, 0x7016, 0, VR::DS, VM::M1, "Detector Activation Offset From Exposure" },
{ 0x300A, 0x0100, 0, VR::DS, VM::M1, "Block Thickness" },
{ 0x5000, 0x200E, 1, VR::LT, VM::M1, "Audio Comments" },
{ 0x5002, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 2" },
{ 0x5004, 0x200A, 1, VR::UL, VM::M1, "Total Time 3" },
{ 0x5006, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 4" },
{ 0x5008, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 5" },
{ 0x500A, 0x2004, 1, VR::US, VM::M1, "Number of Channels 6" },
{ 0x500C, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 7" },
{ 0x500E, 0x2000, 1, VR::US, VM::M1, "Audio Type 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0463[] = {
{ 0x0008, 0x2142, 0, VR::IS, VM::M1, "Start Trim" },
{ 0x0018, 0x1191, 0, VR::CS, VM::M1, "Anode Target Material" },
{ 0x0018, 0x6056, 0, VR::UL, VM::M1, "Number of Table Entries" },
{ 0x0088, 0x0140, 0, VR::UI, VM::M1, "Storage Media File-set UID" },
{ 0x600E, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0464[] = {
{ 0x0018, 0x7008, 0, VR::LT, VM::M1, "Detector Mode" },
{ 0x300A, 0x011E, 0, VR::DS, VM::M1, "Gantry Angle" },
{ 0x5010, 0x2000, 1, VR::US, VM::M1, "Audio Type 9" },
{ 0x5012, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 10" },
{ 0x5014, 0x2004, 1, VR::US, VM::M1, "Number of Channels 11" },
{ 0x5016, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 12" },
{ 0x5018, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 13" },
{ 0x501A, 0x200A, 1, VR::UL, VM::M1, "Total Time 14" },
{ 0x501C, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 15" },
{ 0x501E, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 16" },
{ 0x6000, 0x0051, 0, VR::US, VM::M1, "Image Frame Origin" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0465[] = {
{ 0x0018, 0x6048, 0, VR::UL, VM::M1, "Pixel Component Range Start" },
{ 0x300A, 0x011F, 0, VR::CS, VM::M1, "Gantry Rotation Direction" },
{ 0x6000, 0x0050, 0, VR::SS, VM::M2, "Overlay Origin" },
{ 0x6010, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0466[] = {
{ 0x0018, 0x700A, 0, VR::SH, VM::M1, "Detector ID" },
{ 0x300A, 0x011C, 0, VR::DS, VM::M2T2N, "Leaf/Jaw Positions" },
{ 0x5010, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 9" },
{ 0x5012, 0x2000, 1, VR::US, VM::M1, "Audio Type 10" },
{ 0x5014, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 11" },
{ 0x5016, 0x2004, 1, VR::US, VM::M1, "Number of Channels 12" },
{ 0x5018, 0x200A, 1, VR::UL, VM::M1, "Total Time 13" },
{ 0x501A, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 14" },
{ 0x501C, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 15" },
{ 0x501E, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0467[] = {
{ 0x0018, 0x604A, 0, VR::UL, VM::M1, "Pixel Component Range Stop" },
{ 0x6000, 0x0052, 1, VR::US, VM::M1, "Overlay Plane Origin" },
{ 0x6012, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0468[] = {
{ 0x0018, 0x700C, 0, VR::DA, VM::M1, "Date of Last Detector Calibration" },
{ 0x300A, 0x011A, 0, VR::SQ, VM::M1, "Beam Limiting Device Position Sequence" },
{ 0x5010, 0x2004, 1, VR::US, VM::M1, "Number of Channels 9" },
{ 0x5012, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 10" },
{ 0x5014, 0x2000, 1, VR::US, VM::M1, "Audio Type 11" },
{ 0x5016, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 12" },
{ 0x5018, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 13" },
{ 0x501A, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 14" },
{ 0x501C, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 15" },
{ 0x501E, 0x200A, 1, VR::UL, VM::M1, "Total Time 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0469[] = {
{ 0x0018, 0x604C, 0, VR::US, VM::M1, "Pixel Component Physical Units" },
{ 0x2010, 0x0140, 0, VR::CS, VM::M1, "Trim" },
{ 0x2040, 0x0500, 1, VR::SQ, VM::M1, "Referenced Image Box Sequence (Retired)" },
{ 0x2100, 0x0050, 0, VR::TM, VM::M1, "Creation Time" },
{ 0x2120, 0x0070, 1, VR::SQ, VM::M1, "Referenced Print Job Sequence" },
{ 0x2130, 0x0060, 1, VR::SQ, VM::M1, "Image Overlay Box Content Sequence" },
{ 0x6014, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0470[] = {
{ 0x0008, 0x1198, 0, VR::SQ, VM::M1, "Failed SOP Sequence" },
{ 0x0018, 0x700E, 0, VR::TM, VM::M1, "Time of Last Detector Calibration" },
{ 0x300A, 0x0118, 0, VR::CS, VM::M1, "Wedge Position" },
{ 0x5010, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 9" },
{ 0x5012, 0x2004, 1, VR::US, VM::M1, "Number of Channels 10" },
{ 0x5014, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 11" },
{ 0x5016, 0x2000, 1, VR::US, VM::M1, "Audio Type 12" },
{ 0x5018, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 13" },
{ 0x501A, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 14" },
{ 0x501C, 0x200A, 1, VR::UL, VM::M1, "Total Time 15" },
{ 0x501E, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0471[] = {
{ 0x0008, 0x1199, 0, VR::SQ, VM::M1, "Referenced SOP Sequence" },
{ 0x0018, 0x604E, 0, VR::US, VM::M1, "Pixel Component Data Type" },
{ 0x6016, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0472[] = {
{ 0x0018, 0x3104, 0, VR::IS, VM::M1, "IVUS Pullback Stop Frame Number" },
{ 0x0018, 0x6041, 0, VR::SL, VM::M1, "TM-Line Position X1" },
{ 0x0018, 0x7000, 0, VR::CS, VM::M1, "Detector Conditions Nominal Flag" },
{ 0x300A, 0x0116, 0, VR::SQ, VM::M1, "Wedge Position Sequence" },
{ 0x5010, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 9" },
{ 0x5012, 0x200A, 1, VR::UL, VM::M1, "Total Time 10" },
{ 0x5014, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 11" },
{ 0x5016, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 12" },
{ 0x5018, 0x2000, 1, VR::US, VM::M1, "Audio Type 13" },
{ 0x501A, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 14" },
{ 0x501C, 0x2004, 1, VR::US, VM::M1, "Number of Channels 15" },
{ 0x501E, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0473[] = {
{ 0x0008, 0x1197, 0, VR::US, VM::M1, "Failure Reason" },
{ 0x0018, 0x3105, 0, VR::IS, VM::M1TN, "Lesion Number" },
{ 0x0018, 0x6040, 1, VR::UL, VM::M1, "TM-Line Position X1 (Retired)" },
{ 0x0018, 0x7001, 0, VR::DS, VM::M1, "Detector Temperature" },
{ 0x0068, 0x6420, 0, VR::CS, VM::M1, "Degree of Freedom Type" },
{ 0x6018, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0474[] = {
{ 0x0018, 0x1184, 0, VR::DS, VM::M1T2, "Y Focus Center" },
{ 0x0018, 0x6043, 0, VR::SL, VM::M1, "TM-Line Position Y1" },
{ 0x3008, 0x0116, 0, VR::CS, VM::M1, "Application Setup Check" },
{ 0x300A, 0x0114, 0, VR::DS, VM::M1, "Nominal Beam Energy" },
{ 0x5010, 0x200A, 1, VR::UL, VM::M1, "Total Time 9" },
{ 0x5012, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 10" },
{ 0x5014, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 11" },
{ 0x5016, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 12" },
{ 0x5018, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 13" },
{ 0x501A, 0x2000, 1, VR::US, VM::M1, "Audio Type 14" },
{ 0x501C, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 15" },
{ 0x501E, 0x2004, 1, VR::US, VM::M1, "Number of Channels 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0475[] = {
{ 0x0008, 0x1195, 0, VR::UI, VM::M1, "Transaction UID" },
{ 0x0018, 0x6042, 1, VR::UL, VM::M1, "TM-Line Position Y1 (Retired)" },
{ 0x300A, 0x0115, 0, VR::DS, VM::M1, "Dose Rate Set" },
{ 0x601A, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0476[] = {
{ 0x0018, 0x1182, 0, VR::IS, VM::M1T2, "Focal Distance" },
{ 0x0018, 0x3100, 0, VR::CS, VM::M1, "IVUS Acquisition" },
{ 0x0018, 0x7004, 0, VR::CS, VM::M1, "Detector Type" },
{ 0x3008, 0x0110, 0, VR::SQ, VM::M1, "Treatment Session Application Setup Sequence" },
{ 0x300A, 0x0112, 0, VR::IS, VM::M1, "Control Point Index" },
{ 0x5010, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 9" },
{ 0x5012, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 10" },
{ 0x5014, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 11" },
{ 0x5016, 0x200A, 1, VR::UL, VM::M1, "Total Time 12" },
{ 0x5018, 0x2004, 1, VR::US, VM::M1, "Number of Channels 13" },
{ 0x501A, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 14" },
{ 0x501C, 0x2000, 1, VR::US, VM::M1, "Audio Type 15" },
{ 0x501E, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0477[] = {
{ 0x0018, 0x1183, 0, VR::DS, VM::M1T2, "X Focus Center" },
{ 0x0018, 0x3101, 0, VR::DS, VM::M1, "IVUS Pullback Rate" },
{ 0x0018, 0x6044, 0, VR::US, VM::M1, "Pixel Component Organization" },
{ 0x0018, 0x7005, 0, VR::CS, VM::M1, "Detector Configuration" },
{ 0x601C, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0478[] = {
{ 0x0018, 0x1180, 0, VR::SH, VM::M1, "Collimator/grid Name" },
{ 0x0018, 0x3102, 0, VR::DS, VM::M1, "IVUS Gated Rate" },
{ 0x0018, 0x7006, 0, VR::LT, VM::M1, "Detector Description" },
{ 0x0040, 0xA313, 1, VR::SQ, VM::M1, "Referenced Accession Sequence (Trial)" },
{ 0x300A, 0x0110, 0, VR::IS, VM::M1, "Number of Control Points" },
{ 0x5010, 0x200E, 1, VR::LT, VM::M1, "Audio Comments 9" },
{ 0x5012, 0x200C, 1, VR::OX, VM::M1, "Audio Sample Data 10" },
{ 0x5014, 0x200A, 1, VR::UL, VM::M1, "Total Time 11" },
{ 0x5016, 0x2008, 1, VR::UL, VM::M1, "Sample Rate 12" },
{ 0x5018, 0x2006, 1, VR::UL, VM::M1, "Number of Samples 13" },
{ 0x501A, 0x2004, 1, VR::US, VM::M1, "Number of Channels 14" },
{ 0x501C, 0x2002, 1, VR::US, VM::M1, "Audio Sample Format 15" },
{ 0x501E, 0x2000, 1, VR::US, VM::M1, "Audio Type 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0479[] = {
{ 0x0018, 0x1181, 0, VR::CS, VM::M1, "Collimator Type" },
{ 0x0018, 0x3103, 0, VR::IS, VM::M1, "IVUS Pullback Start Frame Number" },
{ 0x0018, 0x6046, 0, VR::UL, VM::M1, "Pixel Component Mask" },
{ 0x300A, 0x0111, 0, VR::SQ, VM::M1, "Control Point Sequence" },
{ 0x601E, 0x1001, 0, VR::CS, VM::M1, "Overlay Activation Layer 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0480[] = {
{ 0x0018, 0x7038, 0, VR::FL, VM::M1, "Pixel Data Area Rotation Angle Relative To FOV" },
{ 0x300A, 0x012E, 0, VR::DS, VM::M3, "Surface Entry Point" },
{ 0x6000, 0x0061, 1, VR::SH, VM::M1, "Overlay Compression Originator" },
{ 0x6008, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0481[] = {
{ 0x6000, 0x0060, 1, VR::CS, VM::M1, "Overlay Compression Code" },
{ 0x6008, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0482[] = {
{ 0x300A, 0x012C, 0, VR::DS, VM::M3, "Isocenter Position" },
{ 0x6000, 0x0063, 1, VR::CS, VM::M1, "Overlay Compression Description" },
{ 0x600A, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0483[] = {
{ 0x6000, 0x0062, 1, VR::SH, VM::M1, "Overlay Compression Label" },
{ 0x600A, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0484[] = {
{ 0x0020, 0x3100, 1, VR::CS, VM::M1TN, "Source Image IDs" },
{ 0x300A, 0x012A, 0, VR::DS, VM::M1, "Table Top Lateral Position" },
{ 0x600C, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0485[] = {
{ 0x2020, 0x0140, 1, VR::SQ, VM::M1, "Referenced VOI LUT Box Sequence" },
{ 0x2130, 0x0050, 1, VR::SQ, VM::M1, "Annotation Content Sequence" },
{ 0x600C, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0486[] = {
{ 0x300A, 0x0128, 0, VR::DS, VM::M1, "Table Top Vertical Position" },
{ 0x600E, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0487[] = {
{ 0x300A, 0x0129, 0, VR::DS, VM::M1, "Table Top Longitudinal Position" },
{ 0x6000, 0x0066, 1, VR::AT, VM::M1TN, "Overlay Compression Step Pointers" },
{ 0x600E, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0488[] = {
{ 0x0018, 0x7030, 0, VR::DS, VM::M2, "Field of View Origin" },
{ 0x300A, 0x0126, 0, VR::CS, VM::M1, "Table Top Eccentric Rotation Direction" },
{ 0x6000, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0489[] = {
{ 0x0028, 0x6040, 0, VR::US, VM::M1TN, "R Wave Pointer" },
{ 0x0068, 0x6410, 0, VR::US, VM::M1, "Degree of Freedom ID" },
{ 0x6000, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0490[] = {
{ 0x0018, 0x7032, 0, VR::DS, VM::M1, "Field of View Rotation" },
{ 0x300A, 0x0124, 0, VR::DS, VM::M1, "Table Top Eccentric Axis Distance" },
{ 0x6002, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0491[] = {
{ 0x300A, 0x0125, 0, VR::DS, VM::M1, "Table Top Eccentric Angle" },
{ 0x6002, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0492[] = {
{ 0x0018, 0x7034, 0, VR::CS, VM::M1, "Field of View Horizontal Flip" },
{ 0x0040, 0xA731, 1, VR::SQ, VM::M1, "Relationship Sequence (Trial)" },
{ 0x3008, 0x0120, 0, VR::SQ, VM::M1, "Recorded Brachy Accessory Device Sequence" },
{ 0x300A, 0x0122, 0, VR::DS, VM::M1, "Patient Support Angle" },
{ 0x6004, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0493[] = {
{ 0x0040, 0xA730, 0, VR::SQ, VM::M1, "Content Sequence" },
{ 0x300A, 0x0123, 0, VR::CS, VM::M1, "Patient Support Rotation Direction" },
{ 0x6004, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0494[] = {
{ 0x0018, 0x7036, 0, VR::FL, VM::M2, "Pixel Data Area Origin Relative To FOV" },
{ 0x3008, 0x0122, 0, VR::IS, VM::M1, "Referenced Brachy Accessory Device Number" },
{ 0x300A, 0x0120, 0, VR::DS, VM::M1, "Beam Limiting Device Angle" },
{ 0x6006, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0495[] = {
{ 0x0040, 0xA732, 1, VR::SQ, VM::M1, "Relationship Type Code Sequence (Trial)" },
{ 0x300A, 0x0121, 0, VR::CS, VM::M1, "Beam Limiting Device Rotation Direction" },
{ 0x6006, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0496[] = {
{ 0x0018, 0x7028, 0, VR::DS, VM::M2, "Detector Active Origin" },
{ 0x3008, 0x013C, 0, VR::DS, VM::M1, "Delivered Pulse Repetition Interval" },
{ 0x6018, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0497[] = {
{ 0x6018, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0498[] = {
{ 0x0018, 0x702A, 0, VR::LO, VM::M1, "Detector Manufacturer Name" },
{ 0x601A, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0499[] = {
{ 0x0018, 0x702B, 0, VR::LO, VM::M1, "Detector Manufacturer's Model Name" },
{ 0x601A, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0500[] = {
{ 0x3008, 0x0138, 0, VR::IS, VM::M1, "Delivered Number of Pulses" },
{ 0x4008, 0x00FF, 1, VR::CS, VM::M1, "Report Production Status (Trial)" },
{ 0x601C, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0501[] = {
{ 0x0010, 0x2160, 0, VR::SH, VM::M1, "Ethnic Group" },
{ 0x2010, 0x0160, 0, VR::US, VM::M1, "Reflected Ambient Light" },
{ 0x2100, 0x0070, 0, VR::AE, VM::M1, "Originator" },
{ 0x2120, 0x0050, 1, VR::SQ, VM::M1, "Print Job Description Sequence" },
{ 0x2130, 0x0040, 1, VR::SQ, VM::M1, "Image Box Content Sequence" },
{ 0x601C, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0502[] = {
{ 0x3008, 0x013A, 0, VR::DS, VM::M1, "Specified Pulse Repetition Interval" },
{ 0x601E, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0503[] = {
{ 0x0028, 0x1199, 0, VR::UI, VM::M1, "Palette Color Lookup Table UID" },
{ 0x0040, 0xA33A, 1, VR::ST, VM::M1, "Report Status Comment (Trial)" },
{ 0x601E, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0504[] = {
{ 0x0018, 0x7020, 0, VR::DS, VM::M2, "Detector Element Physical Size" },
{ 0x3008, 0x0134, 0, VR::DS, VM::M1, "Delivered Channel Total Time" },
{ 0x6010, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0505[] = {
{ 0x0018, 0x6060, 0, VR::FL, VM::M1TN, "R Wave Time Vector" },
{ 0x0068, 0x6400, 0, VR::SQ, VM::M1, "Mating Feature Degree of Freedom Sequence" },
{ 0x6010, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0506[] = {
{ 0x0018, 0x7022, 0, VR::DS, VM::M2, "Detector Element Spacing" },
{ 0x3008, 0x0136, 0, VR::IS, VM::M1, "Specified Number of Pulses" },
{ 0x300A, 0x0134, 0, VR::DS, VM::M1, "Cumulative Meterset Weight" },
{ 0x6012, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0507[] = {
{ 0x6012, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0508[] = {
{ 0x0018, 0x11A2, 0, VR::DS, VM::M1, "Compression Force" },
{ 0x0018, 0x7024, 0, VR::CS, VM::M1, "Detector Active Shape" },
{ 0x0028, 0x3110, 0, VR::SQ, VM::M1, "Softcopy VOI LUT Sequence" },
{ 0x3008, 0x0130, 0, VR::SQ, VM::M1, "Recorded Channel Sequence" },
{ 0x6014, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0509[] = {
{ 0x6014, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0510[] = {
{ 0x0018, 0x11A0, 0, VR::DS, VM::M1, "Body Part Thickness" },
{ 0x0018, 0x7026, 0, VR::DS, VM::M1T2, "Detector Active Dimension(s)" },
{ 0x3008, 0x0132, 0, VR::DS, VM::M1, "Specified Channel Total Time" },
{ 0x300A, 0x0130, 0, VR::DS, VM::M1, "Source to Surface Distance" },
{ 0x6016, 0x0069, 1, VR::US, VM::M1, "Overlay Bits Grouped 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0511[] = {
{ 0x6016, 0x0068, 1, VR::US, VM::M1, "Overlay Repeat Interval 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0512[] = {
{ 0x0008, 0x9459, 0, VR::FL, VM::M1, "Recommended Display Frame Rate in Float" },
{ 0x0018, 0x1251, 0, VR::SH, VM::M1, "Transmit Coil Name" },
{ 0x0018, 0x9059, 0, VR::CS, VM::M1, "De-coupling" },
{ 0x0018, 0x9449, 0, VR::FL, VM::M1, "Beam Angle" },
{ 0x0070, 0x0278, 0, VR::CS, VM::M1, "Show Tick Label" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0513[] = {
{ 0x0008, 0x0201, 0, VR::SH, VM::M1, "Timezone Offset From UTC" },
{ 0x0008, 0x9458, 0, VR::SQ, VM::M1, "Frame Display Sequence" },
{ 0x0018, 0x1250, 0, VR::SH, VM::M1, "Receive Coil Name" },
{ 0x0018, 0x9058, 0, VR::US, VM::M1, "MR Acquisition Frequency Encoding Steps" },
{ 0x0028, 0x9478, 0, VR::FL, VM::M1, "Mask Visibility Percentage" },
{ 0x0070, 0x0279, 0, VR::CS, VM::M1, "Tick Label Alignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0514[] = {
{ 0x0010, 0x2298, 0, VR::CS, VM::M1, "Responsible Person Role" },
{ 0x0028, 0x0A02, 0, VR::CS, VM::M1, "Pixel Spacing Calibration Type" },
{ 0x003A, 0x0230, 0, VR::FL, VM::M1, "Waveform Data Display Scale" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0515[] = {
{ 0x0010, 0x2299, 0, VR::LO, VM::M1, "Responsible Organization" },
{ 0x003A, 0x0231, 0, VR::US, VM::M3, "Waveform Display Background CIELab Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0516[] = {
{ 0x0028, 0x0A04, 0, VR::LO, VM::M1, "Pixel Spacing Calibration Description" },
{ 0x4008, 0x0300, 1, VR::ST, VM::M1, "Impressions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0517[] = {
{ 0x0074, 0x1238, 0, VR::LT, VM::M1, "Reason for Cancellation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0518[] = {
{ 0x0068, 0x63E0, 0, VR::SQ, VM::M1, "Mating Feature Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0519[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0520[] = {
{ 0x0010, 0x2292, 0, VR::LO, VM::M1, "Patient Breed Description" },
{ 0x0018, 0x9051, 0, VR::CS, VM::M1, "Transmit Coil Type" },
{ 0x0018, 0x9441, 0, VR::US, VM::M1, "Radius of Circular Exposure Control Sensing Region" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0521[] = {
{ 0x0010, 0x2293, 0, VR::SQ, VM::M1, "Patient Breed Code Sequence" },
{ 0x0018, 0x9050, 0, VR::LO, VM::M1, "Transmit Coil Manufacturer Name" },
{ 0x0018, 0x9440, 0, VR::SS, VM::M2, "Center of Circular Exposure Control Sensing Region" },
{ 0x0022, 0x1262, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Quality Metric Sequence" },
{ 0x0040, 0x0241, 0, VR::AE, VM::M1, "Performed Station AE Title" },
{ 0x0074, 0x1234, 0, VR::AE, VM::M1, "Receiving AE" },
{ 0x300A, 0x02C8, 0, VR::DS, VM::M1, "Final Cumulative Time Weight" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0522[] = {
{ 0x0018, 0x9053, 0, VR::FD, VM::M1T2, "Chemical Shift Reference" },
{ 0x0040, 0x0242, 0, VR::SH, VM::M1, "Performed Station Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0523[] = {
{ 0x0018, 0x9052, 0, VR::FD, VM::M1T2, "Spectral Width" },
{ 0x0018, 0x9442, 0, VR::SS, VM::M2TN, "Vertices of the Polygonal Exposure Control Sensing Region" },
{ 0x0022, 0x1260, 0, VR::SQ, VM::M1, "Selected Total Ophthalmic Axial Length Sequence" },
{ 0x0040, 0x0243, 0, VR::SH, VM::M1, "Performed Location" },
{ 0x0070, 0x0273, 0, VR::FL, VM::M2, "Rotation Point" },
{ 0x0074, 0x1236, 0, VR::AE, VM::M1, "Requesting AE" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0524[] = {
{ 0x0010, 0x2296, 0, VR::SQ, VM::M1, "Breed Registry Code Sequence" },
{ 0x0040, 0x0244, 0, VR::DA, VM::M1, "Performed Procedure Step Start Date" },
{ 0x0070, 0x0274, 0, VR::CS, VM::M1, "Tick Alignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0525[] = {
{ 0x0010, 0x2297, 0, VR::PN, VM::M1, "Responsible Person" },
{ 0x0018, 0x9054, 0, VR::CS, VM::M1, "Volume Localization Technique" },
{ 0x0028, 0x9474, 0, VR::CS, VM::M1, "LUT Function" },
{ 0x0040, 0x0245, 0, VR::TM, VM::M1, "Performed Procedure Step Start Time" },
{ 0x0054, 0x1210, 0, VR::DS, VM::M1, "Coincidence Window Width" },
{ 0x0074, 0x1230, 0, VR::LO, VM::M1, "Deletion Lock" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0526[] = {
{ 0x0010, 0x2294, 0, VR::SQ, VM::M1, "Breed Registration Sequence" },
{ 0x0018, 0x9447, 0, VR::FL, VM::M1, "Column Angulation (Patient)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0527[] = {
{ 0x0010, 0x2295, 0, VR::LO, VM::M1, "Breed Registration Number" },
{ 0x7FE0, 0x0010, 0, VR::OX, VM::M1, "Pixel Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0528[] = {
{ 0x0018, 0x9049, 0, VR::SQ, VM::M1, "MR Transmit Coil Sequence" },
{ 0x0020, 0x9071, 0, VR::SQ, VM::M1, "Frame Anatomy Sequence" },
{ 0x003A, 0x0222, 0, VR::DS, VM::M1, "Notch Filter Frequency" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0529[] = {
{ 0x0008, 0x1250, 0, VR::SQ, VM::M1, "Related Series Sequence" },
{ 0x0018, 0x1240, 1, VR::IS, VM::M1TN, "Upper/Lower Pixel Values" },
{ 0x0018, 0x9048, 0, VR::CS, VM::M1, "Multi-Coil Element Used" },
{ 0x003A, 0x0223, 0, VR::DS, VM::M1, "Notch Filter Bandwidth" },
{ 0x300A, 0x02D0, 0, VR::SQ, VM::M1, "Brachy Control Point Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0530[] = {
{ 0x0018, 0x1243, 0, VR::IS, VM::M1, "Count Rate" },
{ 0x003A, 0x0220, 0, VR::DS, VM::M1, "Filter Low Frequency" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0531[] = {
{ 0x0018, 0x1242, 0, VR::IS, VM::M1, "Actual Frame Duration" },
{ 0x0020, 0x9072, 0, VR::CS, VM::M1, "Frame Laterality" },
{ 0x003A, 0x0221, 0, VR::DS, VM::M1, "Filter High Frequency" },
{ 0x300A, 0x02D2, 0, VR::DS, VM::M1, "Control Point Relative Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0532[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0533[] = {
{ 0x0018, 0x1244, 0, VR::US, VM::M1, "Preferred Playback Sequencing" },
{ 0x300A, 0x02D4, 0, VR::DS, VM::M3, "Control Point 3D Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0534[] = {
{ 0x0068, 0x63F0, 0, VR::US, VM::M1, "Mating Feature ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0535[] = {
{ 0x300A, 0x02D6, 0, VR::DS, VM::M1, "Cumulative Time Weight" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0536[] = {
{ 0x0018, 0x9041, 0, VR::LO, VM::M1, "Receive Coil Manufacturer Name" },
{ 0x0018, 0x9451, 0, VR::SQ, VM::M1, "Frame Detector Parameters Sequence" },
{ 0x0022, 0x1273, 0, VR::LO, VM::M1, "Ophthalmic Axial  Length Quality Metric Type Description" },
{ 0x0040, 0x0250, 0, VR::DA, VM::M1, "Performed Procedure Step End Date" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0537[] = {
{ 0x0040, 0x0251, 0, VR::TM, VM::M1, "Performed Procedure Step End Time" },
{ 0x0070, 0x0261, 0, VR::FL, VM::M1, "Gap Length" },
{ 0x0074, 0x1224, 0, VR::SQ, VM::M1, "Replaced Procedure Step Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0538[] = {
{ 0x0018, 0x9043, 0, VR::CS, VM::M1, "Receive Coil Type" },
{ 0x0040, 0x0252, 0, VR::CS, VM::M1, "Performed Procedure Step Status" },
{ 0x0070, 0x0262, 0, VR::FL, VM::M1, "Diameter of Visibility" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0539[] = {
{ 0x0018, 0x9042, 0, VR::SQ, VM::M1, "MR Receive Coil Sequence" },
{ 0x0018, 0x9452, 0, VR::FL, VM::M1, "Calculated Anatomy Thickness" },
{ 0x0040, 0x0253, 0, VR::SH, VM::M1, "Performed Procedure Step ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0540[] = {
{ 0x0018, 0x9045, 0, VR::SQ, VM::M1, "Multi-Coil Definition Sequence" },
{ 0x0018, 0x9455, 0, VR::SQ, VM::M1, "Calibration Sequence" },
{ 0x0040, 0x0254, 0, VR::LO, VM::M1, "Performed Procedure Step Description" },
{ 0x0054, 0x1201, 0, VR::IS, VM::M2, "Axial Mash" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0541[] = {
{ 0x0018, 0x9044, 0, VR::CS, VM::M1, "Quadrature Receive Coil" },
{ 0x0040, 0x0255, 0, VR::LO, VM::M1, "Performed Procedure Type Description" },
{ 0x0054, 0x1200, 0, VR::DS, VM::M1, "Axial Acceptance" },
{ 0x0074, 0x1220, 1, VR::SQ, VM::M1, "Related Procedure Step Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0542[] = {
{ 0x0018, 0x9047, 0, VR::SH, VM::M1, "Multi-Coil Element Name" },
{ 0x0018, 0x9457, 0, VR::CS, VM::M1, "Plane Identification" },
{ 0x0054, 0x1203, 0, VR::DS, VM::M2, "Detector Element Size" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0543[] = {
{ 0x0018, 0x9046, 0, VR::LO, VM::M1, "Multi-Coil Configuration" },
{ 0x0018, 0x9456, 0, VR::SQ, VM::M1, "Object Thickness Sequence" },
{ 0x0054, 0x1202, 0, VR::IS, VM::M1, "Transverse Mash" },
{ 0x0074, 0x1222, 1, VR::LO, VM::M1, "Procedure Step Relationship Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0544[] = {
{ 0x0018, 0x9079, 0, VR::FD, VM::M1TN, "Inversion Times" },
{ 0x0018, 0x9469, 0, VR::FL, VM::M1, "Table Horizontal Rotation Angle" },
{ 0x0028, 0x0200, 1, VR::US, VM::M1, "Image Location" },
{ 0x003A, 0x0212, 0, VR::DS, VM::M1, "Channel Sensitivity Correction Factor" },
{ 0x0070, 0x0258, 0, VR::FL, VM::M1, "Shadow Opacity" },
{ 0x300A, 0x02E1, 0, VR::CS, VM::M1, "Compensator Mounting Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0545[] = {
{ 0x0018, 0x9078, 0, VR::CS, VM::M1, "Parallel Acquisition Technique" },
{ 0x0018, 0x9468, 0, VR::FL, VM::M1, "Table Z Position to Isocenter" },
{ 0x0020, 0x9450, 0, VR::SQ, VM::M1, "Patient Orientation in Frame Sequence" },
{ 0x003A, 0x0213, 0, VR::DS, VM::M1, "Channel Baseline" },
{ 0x300A, 0x02E0, 0, VR::CS, VM::M1, "Compensator Divergence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0546[] = {
{ 0x0020, 0x9453, 0, VR::LO, VM::M1, "Frame Label" },
{ 0x003A, 0x0210, 0, VR::DS, VM::M1, "Channel Sensitivity" },
{ 0x300A, 0x02E3, 0, VR::FL, VM::M1, "Total Compensator Tray Water-Equivalent Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0547[] = {
{ 0x003A, 0x0211, 0, VR::SQ, VM::M1, "Channel Sensitivity Units Sequence" },
{ 0x300A, 0x02E2, 0, VR::DS, VM::M1TN, "Source to Compensator Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0548[] = {
{ 0x300A, 0x02E5, 0, VR::FL, VM::M1, "Compensator Column Offset" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0549[] = {
{ 0x300A, 0x02E4, 0, VR::FL, VM::M1, "Isocenter to Compensator Tray Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0550[] = {
{ 0x003A, 0x0214, 0, VR::DS, VM::M1, "Channel Time Skew" },
{ 0x0068, 0x63C0, 0, VR::US, VM::M1, "Mating Feature Set ID" },
{ 0x300A, 0x02E7, 0, VR::FL, VM::M1, "Compensator Relative Stopping Power Ratio" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0551[] = {
{ 0x003A, 0x0215, 0, VR::DS, VM::M1, "Channel Sample Skew" },
{ 0x300A, 0x02E6, 0, VR::FL, VM::M1TN, "Isocenter to Compensator Distances" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0552[] = {
{ 0x0018, 0x9461, 0, VR::FL, VM::M1T2, "Field of View Dimension(s) in Float" },
{ 0x0020, 0x0200, 0, VR::UI, VM::M1, "Synchronization Frame of Reference UID" },
{ 0x003A, 0x021A, 0, VR::US, VM::M1, "Waveform Bits Stored" },
{ 0x0040, 0x0260, 0, VR::SQ, VM::M1, "Performed Protocol Code Sequence" },
{ 0x0070, 0x0250, 0, VR::CS, VM::M1, "Italic" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0553[] = {
{ 0x0018, 0x9070, 0, VR::FD, VM::M1, "Cardiac R-R Interval Specified" },
{ 0x0040, 0x0261, 0, VR::CS, VM::M1, "Performed Protocol Type" },
{ 0x0070, 0x0251, 0, VR::US, VM::M3, "Pattern On Color CIELab Value" },
{ 0x300A, 0x02E8, 0, VR::FL, VM::M1, "Compensator Milling Tool Diameter" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0554[] = {
{ 0x0018, 0x9073, 0, VR::FD, VM::M1, "Acquisition Duration" },
{ 0x0018, 0x9463, 0, VR::FL, VM::M1, "Positioner Isocenter Primary Angle" },
{ 0x003A, 0x0218, 0, VR::DS, VM::M1, "Channel Offset" },
{ 0x0070, 0x0252, 0, VR::US, VM::M3, "Pattern Off Color CIELab Value" },
{ 0x300A, 0x02EB, 0, VR::LT, VM::M1, "Compensator Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0555[] = {
{ 0x0018, 0x9462, 0, VR::SQ, VM::M1, "Isocenter Reference System Sequence" },
{ 0x0070, 0x0253, 0, VR::FL, VM::M1, "Line Thickness" },
{ 0x0074, 0x1216, 0, VR::SQ, VM::M1, "Unified Procedure Step Performed Procedure Sequence" },
{ 0x300A, 0x02EA, 0, VR::SQ, VM::M1, "Ion Range Compensator Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0556[] = {
{ 0x0018, 0x9075, 0, VR::CS, VM::M1, "Diffusion Directionality" },
{ 0x0018, 0x9465, 0, VR::FL, VM::M1, "Positioner Isocenter Detector Rotation Angle" },
{ 0x0070, 0x0254, 0, VR::CS, VM::M1, "Line Dashing Style" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0557[] = {
{ 0x0018, 0x9074, 0, VR::DT, VM::M1, "Frame Acquisition DateTime" },
{ 0x0018, 0x9464, 0, VR::FL, VM::M1, "Positioner Isocenter Secondary Angle" },
{ 0x0028, 0x9454, 0, VR::CS, VM::M1, "Mask Selection Mode" },
{ 0x0070, 0x0255, 0, VR::UL, VM::M1, "Line Pattern" },
{ 0x0074, 0x1210, 0, VR::SQ, VM::M1, "Scheduled Processing Parameters Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0558[] = {
{ 0x0018, 0x9077, 0, VR::CS, VM::M1, "Parallel Acquisition" },
{ 0x0018, 0x9467, 0, VR::FL, VM::M1, "Table Y Position to Isocenter" },
{ 0x0024, 0x0202, 0, VR::LO, VM::M1, "Algorithm Source" },
{ 0x0070, 0x0256, 0, VR::OB, VM::M1, "Fill Pattern" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0559[] = {
{ 0x0018, 0x9076, 0, VR::SQ, VM::M1, "Diffusion Gradient Direction Sequence" },
{ 0x0018, 0x9466, 0, VR::FL, VM::M1, "Table X Position to Isocenter" },
{ 0x0070, 0x0257, 0, VR::CS, VM::M1, "Fill Mode" },
{ 0x0074, 0x1212, 0, VR::SQ, VM::M1, "Performed Processing Parameters Sequence" },
{ 0x7FE0, 0x0030, 1, VR::OW, VM::M1, "Coefficients SDHN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0560[] = {
{ 0x0018, 0x1261, 0, VR::LO, VM::M1, "Phosphor Type" },
{ 0x0018, 0x9069, 0, VR::FD, VM::M1, "Parallel Reduction Factor In-plane" },
{ 0x003A, 0x0202, 0, VR::IS, VM::M1, "Waveform Channel Number" },
{ 0x0070, 0x0248, 0, VR::CS, VM::M1, "Underlined" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0561[] = {
{ 0x0018, 0x1260, 0, VR::SH, VM::M1, "Plate Type" },
{ 0x003A, 0x0203, 0, VR::SH, VM::M1, "Channel Label" },
{ 0x0070, 0x0249, 0, VR::CS, VM::M1, "Bold" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0562[] = {
{ 0x003A, 0x0200, 0, VR::SQ, VM::M1, "Channel Definition Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0563[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0564[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0565[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0566[] = {
{ 0x0020, 0x9057, 0, VR::UL, VM::M1, "In-Stack Position Number" },
{ 0x0068, 0x63D0, 0, VR::LO, VM::M1, "Mating Feature Set Label" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0567[] = {
{ 0x0020, 0x9056, 0, VR::SH, VM::M1, "Stack ID" },
{ 0x0028, 0x7FE0, 0, VR::UT, VM::M1, "Pixel Data Provider URL" },
{ 0x003A, 0x0205, 0, VR::CS, VM::M1TN, "Channel Status" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0568[] = {
{ 0x0018, 0x9061, 0, VR::FD, VM::M1T2, "De-coupling Frequency" },
{ 0x0018, 0x9471, 0, VR::FL, VM::M1, "Table Cradle Tilt Angle" },
{ 0x003A, 0x020A, 0, VR::SQ, VM::M1, "Source Waveform Sequence" },
{ 0x0040, 0x0270, 0, VR::SQ, VM::M1, "Scheduled Step Attributes Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0569[] = {
{ 0x0008, 0x9460, 0, VR::CS, VM::M1, "Skip Frame Range Flag" },
{ 0x0018, 0x9060, 0, VR::CS, VM::M1T2, "De-coupled Nucleus" },
{ 0x0018, 0x9470, 0, VR::FL, VM::M1, "Table Head Tilt Angle" },
{ 0x0070, 0x0241, 0, VR::US, VM::M3, "Text Color CIELab Value" },
{ 0x0074, 0x1204, 0, VR::LO, VM::M1, "Procedure Step Label" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0570[] = {
{ 0x0018, 0x9063, 0, VR::FD, VM::M1T2, "De-coupling Chemical Shift Reference" },
{ 0x0018, 0x9473, 0, VR::FL, VM::M1, "Acquired Image Area Dose Product" },
{ 0x0028, 0x9443, 0, VR::SQ, VM::M1, "Frame Pixel Data Properties Sequence" },
{ 0x003A, 0x0208, 0, VR::SQ, VM::M1, "Channel Source Sequence" },
{ 0x0070, 0x0242, 0, VR::CS, VM::M1, "Horizontal Alignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0571[] = {
{ 0x0018, 0x9062, 0, VR::CS, VM::M1, "De-coupling Method" },
{ 0x0018, 0x9472, 0, VR::SQ, VM::M1, "Frame Display Shutter Sequence" },
{ 0x0022, 0x1250, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Selection Method Code Sequence" },
{ 0x003A, 0x0209, 0, VR::SQ, VM::M1, "Channel Source Modifiers Sequence" },
{ 0x0070, 0x0243, 0, VR::CS, VM::M1, "Vertical Alignment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0572[] = {
{ 0x0018, 0x9065, 0, VR::CS, VM::M1T2, "Time Domain Filtering" },
{ 0x0022, 0x1257, 0, VR::SQ, VM::M1, "Selected Segmental Ophthalmic Axial Length Sequence" },
{ 0x0028, 0x9445, 0, VR::FL, VM::M1, "Geometric Maximum Distortion" },
{ 0x0070, 0x0244, 0, VR::CS, VM::M1, "Shadow Style" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0573[] = {
{ 0x0018, 0x9064, 0, VR::CS, VM::M1, "k-space Filtering" },
{ 0x0018, 0x9474, 0, VR::CS, VM::M1, "C-arm Positioner Tabletop Relationship" },
{ 0x0028, 0x9444, 0, VR::CS, VM::M1, "Geometrical Properties" },
{ 0x0040, 0x0275, 0, VR::SQ, VM::M1, "Request Attributes Sequence" },
{ 0x0054, 0x1220, 0, VR::CS, VM::M1TN, "Secondary Counts Type" },
{ 0x0070, 0x0245, 0, VR::FL, VM::M1, "Shadow Offset X" },
{ 0x0074, 0x1200, 0, VR::CS, VM::M1, "Scheduled Procedure Step Priority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0574[] = {
{ 0x0018, 0x9067, 0, VR::CS, VM::M1, "Baseline Correction" },
{ 0x0018, 0x9477, 0, VR::SQ, VM::M1, "Irradiation Event Identification Sequence" },
{ 0x0022, 0x1255, 0, VR::SQ, VM::M1, "Optical Selected Ophthalmic Axial Length Sequence" },
{ 0x003A, 0x020C, 0, VR::LO, VM::M1, "Channel Derivation Description" },
{ 0x0070, 0x0246, 0, VR::FL, VM::M1, "Shadow Offset Y" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0575[] = {
{ 0x0018, 0x9066, 0, VR::US, VM::M1T2, "Number of Zero Fills" },
{ 0x0018, 0x9476, 0, VR::SQ, VM::M1, "X-Ray Geometry Sequence" },
{ 0x0028, 0x9446, 0, VR::CS, VM::M1TN, "Image Processing Applied" },
{ 0x0070, 0x0247, 0, VR::US, VM::M3, "Shadow Color CIELab Value" },
{ 0x0074, 0x1202, 0, VR::LO, VM::M1, "Worklist Label" },
{ 0x7FE0, 0x0020, 1, VR::OW, VM::M1, "Coefficients SDVN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0576[] = {
{ 0x0008, 0x1200, 0, VR::SQ, VM::M1, "Studies Containing Other Referenced Instances Sequence" },
{ 0x0018, 0x1210, 0, VR::SH, VM::M1TN, "Convolution Kernel" },
{ 0x0018, 0x1600, 0, VR::CS, VM::M1T3, "Shutter Shape" },
{ 0x0018, 0x9018, 0, VR::CS, VM::M1, "Echo Planar Pulse Sequence" },
{ 0x0040, 0xA493, 0, VR::CS, VM::M1, "Verification Flag" },
{ 0x0048, 0x0201, 0, VR::US, VM::M2, "Top Left Hand Corner of Localizer Area" },
{ 0x300A, 0x0280, 0, VR::SQ, VM::M1, "Channel Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0577[] = {
{ 0x0018, 0x9019, 0, VR::FD, VM::M1, "Tag Angle First Axis" },
{ 0x0028, 0x1221, 0, VR::OW, VM::M1, "Segmented Red Palette Color Lookup Table Data" },
{ 0x0040, 0xA082, 0, VR::DT, VM::M1, "Participation DateTime" },
{ 0x0040, 0xA492, 0, VR::LO, VM::M1, "Completion Flag Description" },
{ 0x0048, 0x0200, 0, VR::SQ, VM::M1, "Referenced Image Navigation Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0578[] = {
{ 0x0018, 0x1602, 0, VR::IS, VM::M1, "Shutter Left Vertical Edge" },
{ 0x0028, 0x1222, 0, VR::OW, VM::M1, "Segmented Green Palette Color Lookup Table Data" },
{ 0x0040, 0xA491, 0, VR::CS, VM::M1, "Completion Flag" },
{ 0x300A, 0x0282, 0, VR::IS, VM::M1, "Channel Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0579[] = {
{ 0x0028, 0x1223, 0, VR::OW, VM::M1, "Segmented Blue Palette Color Lookup Table Data" },
{ 0x0040, 0xA080, 0, VR::CS, VM::M1, "Participation Type" },
{ 0x0048, 0x0202, 0, VR::US, VM::M2, "Bottom Right Hand Corner of Localizer Area" },
{ 0x0068, 0x63A4, 0, VR::SQ, VM::M1, "Coating Materials Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0580[] = {
{ 0x0018, 0x1604, 0, VR::IS, VM::M1, "Shutter Right Vertical Edge" },
{ 0x300A, 0x0284, 0, VR::DS, VM::M1, "Channel Length" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0581[] = {
{ 0x0040, 0xA496, 0, VR::CS, VM::M1, "Preliminary Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0582[] = {
{ 0x0018, 0x1606, 0, VR::IS, VM::M1, "Shutter Upper Horizontal Edge" },
{ 0x0040, 0xA085, 1, VR::SQ, VM::M1, "Procedure Identifier Code Sequence (Trial)" },
{ 0x0048, 0x0207, 0, VR::SQ, VM::M1, "Optical Path Identification Sequence" },
{ 0x300A, 0x0286, 0, VR::DS, VM::M1, "Channel Total Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0583[] = {
{ 0x0040, 0xA084, 0, VR::CS, VM::M1, "Observer Type" },
{ 0x0040, 0xA494, 0, VR::CS, VM::M1, "Archive Requested" },
{ 0x0068, 0x63A0, 0, VR::SQ, VM::M1, "Materials Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0584[] = {
{ 0x0008, 0x9410, 0, VR::SQ, VM::M1, "Referenced Other Plane Sequence" },
{ 0x0018, 0x1608, 0, VR::IS, VM::M1, "Shutter Lower Horizontal Edge" },
{ 0x0018, 0x9010, 0, VR::CS, VM::M1, "Flow Compensation" },
{ 0x0070, 0x0231, 0, VR::SQ, VM::M1, "Text Style Sequence" },
{ 0x300A, 0x0288, 0, VR::CS, VM::M1, "Source Movement Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0585[] = {
{ 0x0018, 0x9011, 0, VR::CS, VM::M1, "Multiple Spin Echo" },
{ 0x0018, 0x9401, 0, VR::SQ, VM::M1, "Projection Pixel Calibration Sequence" },
{ 0x0040, 0x0610, 0, VR::SQ, VM::M1, "Specimen Preparation Sequence" },
{ 0x0070, 0x0230, 0, VR::FD, VM::M1, "Rotation Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0586[] = {
{ 0x0018, 0x9012, 0, VR::CS, VM::M1, "Multi-planar Excitation" },
{ 0x0018, 0x9402, 0, VR::FL, VM::M1, "Distance Source to Isocenter" },
{ 0x0022, 0x1220, 0, VR::SQ, VM::M1, "Ultrasound Ophthalmic Axial Length Measurements Sequence" },
{ 0x0040, 0xA089, 1, VR::OB, VM::M1, "Object Directory Binary Identifier (Trial)" },
{ 0x0070, 0x0233, 0, VR::SQ, VM::M1, "Fill Style Sequence" },
{ 0x300A, 0x028A, 0, VR::IS, VM::M1, "Number of Pulses" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0587[] = {
{ 0x0018, 0x9403, 0, VR::FL, VM::M1, "Distance Object to Table Top" },
{ 0x0040, 0x0612, 0, VR::SQ, VM::M1, "Specimen Preparation Step Content Item Sequence" },
{ 0x0040, 0xA088, 0, VR::SQ, VM::M1, "Verifying Observer Identification Code Sequence" },
{ 0x0068, 0x63AC, 0, VR::SQ, VM::M1, "Fixation Method Code Sequence" },
{ 0x0070, 0x0232, 0, VR::SQ, VM::M1, "Line Style Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0588[] = {
{ 0x0018, 0x9014, 0, VR::CS, VM::M1, "Phase Contrast" },
{ 0x0018, 0x9404, 0, VR::FL, VM::M2, "Object Pixel Spacing in Center of Beam" },
{ 0x0054, 0x0211, 0, VR::US, VM::M1, "Number of Triggers in Phase" },
{ 0x300A, 0x028C, 0, VR::DS, VM::M1, "Pulse Repetition Interval" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0589[] = {
{ 0x0018, 0x9015, 0, VR::CS, VM::M1, "Time of Flight Contrast" },
{ 0x0018, 0x9405, 0, VR::SQ, VM::M1, "Positioner Position Sequence" },
{ 0x0054, 0x0210, 0, VR::IS, VM::M1TN, "Trigger Vector" },
{ 0x0070, 0x0234, 0, VR::SQ, VM::M1, "Graphic Group Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0590[] = {
{ 0x0018, 0x9016, 0, VR::CS, VM::M1, "Spoiling" },
{ 0x0018, 0x9406, 0, VR::SQ, VM::M1, "Table Position Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0591[] = {
{ 0x0008, 0x9007, 0, VR::CS, VM::M4, "Frame Type" },
{ 0x0018, 0x9017, 0, VR::CS, VM::M1, "Steady State Pulse Sequence" },
{ 0x0018, 0x9407, 0, VR::SQ, VM::M1, "Collimator Shape Sequence" },
{ 0x0022, 0x1225, 0, VR::SQ, VM::M1, "Optical Ophthalmic Axial Length Measurements Sequence" },
{ 0x0068, 0x63A8, 0, VR::SQ, VM::M1, "Implant Type Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0592[] = {
{ 0x0018, 0x1200, 0, VR::DA, VM::M1TN, "Date of Last Calibration" },
{ 0x0018, 0x1610, 0, VR::IS, VM::M2, "Center of Circular Shutter" },
{ 0x0018, 0x9008, 0, VR::CS, VM::M1, "Echo Pulse Sequence" },
{ 0x0070, 0x0229, 0, VR::LO, VM::M1, "CSS Font Name" },
{ 0x300A, 0x0290, 0, VR::IS, VM::M1, "Source Applicator Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0593[] = {
{ 0x0018, 0x1201, 0, VR::TM, VM::M1TN, "Time of Last Calibration" },
{ 0x0018, 0x9009, 0, VR::CS, VM::M1, "Inversion Recovery" },
{ 0x0020, 0x9421, 0, VR::LO, VM::M1, "Dimension Description Label" },
{ 0x0070, 0x0228, 0, VR::CS, VM::M1, "Font Name Type" },
{ 0x300A, 0x0291, 0, VR::SH, VM::M1, "Source Applicator ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0594[] = {
{ 0x0018, 0x1612, 0, VR::IS, VM::M1, "Radius of Circular Shutter" },
{ 0x300A, 0x0292, 0, VR::CS, VM::M1, "Source Applicator Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0595[] = {
{ 0x0040, 0xA090, 1, VR::SQ, VM::M1, "Equivalent CDA Document Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0596[] = {
{ 0x300A, 0x0294, 0, VR::LO, VM::M1, "Source Applicator Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0597[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0598[] = {
{ 0x300A, 0x0296, 0, VR::DS, VM::M1, "Source Applicator Length" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0599[] = {
{ 0x0068, 0x63B0, 0, VR::SQ, VM::M1, "Mating Feature Sets Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0600[] = {
{ 0x0018, 0x9410, 0, VR::CS, VM::M1, "Planes in Acquisition" },
{ 0x300A, 0x0298, 0, VR::LO, VM::M1, "Source Applicator Manufacturer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0601[] = {
{ 0x0040, 0x0600, 0, VR::LO, VM::M1, "Specimen Short Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0602[] = {
{ 0x0018, 0x9412, 0, VR::SQ, VM::M1, "XA/XRF Frame Characteristics Sequence" },
{ 0x0022, 0x1230, 0, VR::SQ, VM::M1, "Ultrasound Selected Ophthalmic Axial Length Sequence" },
{ 0x0028, 0x9422, 0, VR::SQ, VM::M1, "Pixel Intensity Relationship LUT Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0603[] = {
{ 0x0040, 0x0602, 0, VR::UT, VM::M1, "Specimen Detailed Description" },
{ 0x0048, 0x021A, 0, VR::SQ, VM::M1, "Plane Position (Slide) Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0604[] = {
{ 0x0018, 0x9004, 0, VR::CS, VM::M1, "Content Qualification" },
{ 0x300A, 0x029C, 0, VR::DS, VM::M1, "Source Applicator Wall Nominal Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0605[] = {
{ 0x0018, 0x9005, 0, VR::SH, VM::M1, "Pulse Sequence Name" },
{ 0x0054, 0x0200, 0, VR::DS, VM::M1, "Start Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0606[] = {
{ 0x0018, 0x9006, 0, VR::SQ, VM::M1, "MR Imaging Modifier Sequence" },
{ 0x0048, 0x021F, 0, VR::SL, VM::M1, "Column Position In Total Image Pixel Matrix" },
{ 0x0070, 0x0227, 0, VR::LO, VM::M1, "Font Name" },
{ 0x300A, 0x029E, 0, VR::DS, VM::M1, "Source Applicator Wall Nominal Transmission" },
{ 0x7FE0, 0x0040, 1, VR::OW, VM::M1, "Coefficients SDDN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0607[] = {
{ 0x0018, 0x9417, 0, VR::SQ, VM::M1, "Frame Acquisition Sequence" },
{ 0x0048, 0x021E, 0, VR::SL, VM::M1, "Row Position In Total Image Pixel Matrix" },
{ 0x0054, 0x0202, 0, VR::CS, VM::M1, "Type of Detector Motion" },
{ 0x0070, 0x0226, 0, VR::UL, VM::M1, "Compound Graphic Instance ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0608[] = {
{ 0x0018, 0x1620, 0, VR::IS, VM::M2T2N, "Vertices of the Polygonal Shutter" },
{ 0x0018, 0x9428, 0, VR::FL, VM::M1T2, "Intensifier Active Dimension(s)" },
{ 0x0020, 0x1208, 0, VR::IS, VM::M1, "Number of Study Related Instances" },
{ 0x0028, 0x1200, 1, VR::OW, VM::M1, "Gray Lookup Table Data" },
{ 0x300A, 0x02A0, 0, VR::DS, VM::M1, "Source Applicator Step Size" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0609[] = {
{ 0x0018, 0x9429, 0, VR::FL, VM::M2, "Physical Detector Size" },
{ 0x0020, 0x1209, 0, VR::IS, VM::M1, "Number of Series Related Instances" },
{ 0x0028, 0x1201, 0, VR::OW, VM::M1, "Red Palette Color Lookup Table Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0610[] = {
{ 0x0018, 0x1622, 0, VR::US, VM::M1, "Shutter Presentation Value" },
{ 0x0028, 0x1202, 0, VR::OW, VM::M1, "Green Palette Color Lookup Table Data" },
{ 0x300A, 0x02A2, 0, VR::IS, VM::M1, "Transfer Tube Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0611[] = {
{ 0x0018, 0x1623, 0, VR::US, VM::M1, "Shutter Overlay Group" },
{ 0x0028, 0x1203, 0, VR::OW, VM::M1, "Blue Palette Color Lookup Table Data" },
{ 0x0072, 0x0218, 0, VR::US, VM::M1TN, "Reference Display Sets" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0612[] = {
{ 0x0018, 0x1624, 0, VR::US, VM::M3, "Shutter Presentation Color CIELab Value" },
{ 0x0028, 0x1204, 0, VR::OW, VM::M1, "Alpha Palette Color Lookup Table Data" },
{ 0x300A, 0x02A4, 0, VR::DS, VM::M1, "Transfer Tube Length" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0613[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0614[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0615[] = {
{ 0x0068, 0x6380, 0, VR::LO, VM::M1, "Surface Model Label" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0616[] = {
{ 0x0018, 0x9030, 0, VR::FD, VM::M1, "Tag Spacing First Dimension" },
{ 0x0018, 0x9420, 0, VR::CS, VM::M1, "X-Ray Receptor Type" },
{ 0x0020, 0x1200, 0, VR::IS, VM::M1, "Number of Patient Related Studies" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0617[] = {
{ 0x0028, 0x9001, 0, VR::UL, VM::M1, "Data Point Rows" },
{ 0x0028, 0x9411, 0, VR::FL, VM::M1, "Display Filter Percentage" },
{ 0x0040, 0x0220, 0, VR::SQ, VM::M1, "Referenced Non-Image Composite SOP Instance Sequence" },
{ 0x0072, 0x0212, 0, VR::US, VM::M2TN, "Display Set Scrolling Group" },
{ 0x0072, 0x0602, 0, VR::CS, VM::M1, "Sort-by Category" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0618[] = {
{ 0x0018, 0x9032, 0, VR::CS, VM::M1, "Geometry of k-Space Traversal" },
{ 0x0020, 0x1202, 0, VR::IS, VM::M1, "Number of Patient Related Series" },
{ 0x0028, 0x9002, 0, VR::UL, VM::M1, "Data Point Columns" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0619[] = {
{ 0x0018, 0x9033, 0, VR::CS, VM::M1, "Segmented k-Space Traversal" },
{ 0x0018, 0x9423, 0, VR::LO, VM::M1, "Acquisition Protocol Name" },
{ 0x0020, 0x0242, 0, VR::UI, VM::M1, "SOP Instance UID of Concatenation Source" },
{ 0x0028, 0x9003, 0, VR::CS, VM::M1, "Signal Domain Columns" },
{ 0x0072, 0x0210, 0, VR::SQ, VM::M1, "Synchronized Scrolling Sequence" },
{ 0x0072, 0x0600, 0, VR::SQ, VM::M1, "Sorting Operations Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0620[] = {
{ 0x0018, 0x9034, 0, VR::CS, VM::M1, "Rectilinear Phase Encode Reordering" },
{ 0x0018, 0x9424, 0, VR::LT, VM::M1, "Acquisition Protocol Description" },
{ 0x0020, 0x1204, 0, VR::IS, VM::M1, "Number of Patient Related Instances" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0621[] = {
{ 0x0018, 0x9035, 0, VR::FD, VM::M1, "Tag Thickness" },
{ 0x0018, 0x9425, 0, VR::CS, VM::M1, "Contrast/Bolus Ingredient Opaque" },
{ 0x0028, 0x9415, 0, VR::SQ, VM::M1, "Frame Pixel Shift Sequence" },
{ 0x0072, 0x0216, 0, VR::US, VM::M1, "Navigation Display Set" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0622[] = {
{ 0x0018, 0x9036, 0, VR::CS, VM::M1, "Partial Fourier Direction" },
{ 0x0018, 0x9426, 0, VR::FL, VM::M1, "Distance Receptor Plane to Detector Housing" },
{ 0x0020, 0x1206, 0, VR::IS, VM::M1, "Number of Study Related Series" },
{ 0x0028, 0x9416, 0, VR::US, VM::M1, "Subtraction Item ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0623[] = {
{ 0x0018, 0x9037, 0, VR::CS, VM::M1, "Cardiac Synchronization Technique" },
{ 0x0018, 0x9427, 0, VR::CS, VM::M1, "Intensifier Active Shape" },
{ 0x0072, 0x0214, 0, VR::SQ, VM::M1, "Navigation Indicator Sequence" },
{ 0x0072, 0x0604, 0, VR::CS, VM::M1, "Sorting Direction" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0624[] = {
{ 0x0018, 0x9028, 0, VR::CS, VM::M1, "Tagging" },
{ 0x0018, 0x9438, 0, VR::SS, VM::M1, "Exposure Control Sensing Region Upper Horizontal Edge" },
{ 0x0018, 0x9808, 0, VR::CS, VM::M1, "Data Type" },
{ 0x0070, 0x0209, 0, VR::SQ, VM::M1, "Compound Graphic Sequence" },
{ 0x300A, 0x02B0, 0, VR::SQ, VM::M1, "Channel Shield Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0625[] = {
{ 0x0010, 0x9431, 0, VR::FL, VM::M1, "Examined Body Thickness" },
{ 0x0018, 0x9029, 0, VR::CS, VM::M1, "Oversampling Phase" },
{ 0x0018, 0x9439, 0, VR::SS, VM::M1, "Exposure Control Sensing Region Lower Horizontal Edge" },
{ 0x0018, 0x9809, 0, VR::SQ, VM::M1, "Transducer Scan Pattern Code Sequence" },
{ 0x0028, 0x1211, 1, VR::OW, VM::M1, "Large Red Palette Color Lookup Table Data" },
{ 0x003A, 0x0242, 0, VR::SQ, VM::M1, "Channel Display Sequence" },
{ 0x0070, 0x0208, 0, VR::ST, VM::M1, "Graphic Group Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0626[] = {
{ 0x0028, 0x1212, 1, VR::OW, VM::M1, "Large Green Palette Color Lookup Table Data" },
{ 0x003A, 0x0241, 0, VR::US, VM::M1, "Presentation Group Number" },
{ 0x300A, 0x02B2, 0, VR::IS, VM::M1, "Channel Shield Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0627[] = {
{ 0x0018, 0x980B, 0, VR::CS, VM::M1, "Aliased Data Type" },
{ 0x0028, 0x1213, 1, VR::OW, VM::M1, "Large Blue Palette Color Lookup Table Data" },
{ 0x003A, 0x0240, 0, VR::SQ, VM::M1, "Waveform Presentation Group Sequence" },
{ 0x0040, 0xA0B0, 0, VR::US, VM::M2T2N, "Referenced Waveform Channels" },
{ 0x0072, 0x0208, 0, VR::CS, VM::M1, "Partial Data Display Handling" },
{ 0x300A, 0x02B3, 0, VR::SH, VM::M1, "Channel Shield ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0628[] = {
{ 0x0018, 0x980C, 0, VR::CS, VM::M1, "Position Measuring Device Used" },
{ 0x0028, 0x1214, 1, VR::UI, VM::M1, "Large Palette Color Lookup Table UID" },
{ 0x003A, 0x0247, 0, VR::FL, VM::M1, "Fractional Channel Display Scale" },
{ 0x300A, 0x02B4, 0, VR::LO, VM::M1, "Channel Shield Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0629[] = {
{ 0x0018, 0x980D, 0, VR::SQ, VM::M1, "Transducer Geometry Code Sequence" },
{ 0x003A, 0x0246, 0, VR::CS, VM::M1, "Display Shading Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0630[] = {
{ 0x0018, 0x980E, 0, VR::SQ, VM::M1, "Transducer Beam Steering Code Sequence" },
{ 0x003A, 0x0245, 0, VR::FL, VM::M1, "Channel Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0631[] = {
{ 0x0018, 0x980F, 0, VR::SQ, VM::M1, "Transducer Application Code Sequence" },
{ 0x003A, 0x0244, 0, VR::US, VM::M3, "Channel Recommended Display CIELab Value" },
{ 0x0068, 0x6390, 0, VR::FD, VM::M1, "Surface Model Scaling Factor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0632[] = {
{ 0x0018, 0x9020, 0, VR::CS, VM::M1, "Magnetization Transfer" },
{ 0x0018, 0x9430, 0, VR::FL, VM::M2, "Position of Isocenter Projection" },
{ 0x0022, 0x1212, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Length Summation Sequence" },
{ 0x0072, 0x0203, 0, VR::LO, VM::M1, "Display Set Label" },
{ 0x0074, 0x1244, 0, VR::CS, VM::M1, "Subscription List Status" },
{ 0x300A, 0x02B8, 0, VR::DS, VM::M1, "Channel Shield Nominal Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0633[] = {
{ 0x0018, 0x9021, 0, VR::CS, VM::M1, "T2 Preparation" },
{ 0x0018, 0x9801, 0, VR::FD, VM::M1TN, "Depth(s) of Focus" },
{ 0x0040, 0x0620, 0, VR::SQ, VM::M1, "Specimen Localization Content Item Sequence" },
{ 0x0072, 0x0202, 0, VR::US, VM::M1, "Display Set Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0634[] = {
{ 0x0018, 0x9022, 0, VR::CS, VM::M1, "Blood Signal Nulling" },
{ 0x0018, 0x9432, 0, VR::SQ, VM::M1, "Field of View Sequence" },
{ 0x0022, 0x1210, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Total Length Sequence" },
{ 0x0074, 0x1246, 0, VR::CS, VM::M1, "Unified Procedure Step List Status" },
{ 0x300A, 0x02BA, 0, VR::DS, VM::M1, "Channel Shield Nominal Transmission" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0635[] = {
{ 0x0018, 0x9433, 0, VR::LO, VM::M1, "Field of View Description" },
{ 0x0018, 0x9803, 0, VR::SQ, VM::M1, "Excluded Intervals Sequence" },
{ 0x0022, 0x1211, 0, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Segmental Length Sequence" },
{ 0x003A, 0x0248, 0, VR::FL, VM::M1, "Absolute Channel Display Scale" },
{ 0x0072, 0x0200, 0, VR::SQ, VM::M1, "Display Sets Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0636[] = {
{ 0x0018, 0x9024, 0, VR::CS, VM::M1, "Saturation Recovery" },
{ 0x0018, 0x9434, 0, VR::SQ, VM::M1, "Exposure Control Sensing Regions Sequence" },
{ 0x0018, 0x9804, 0, VR::DT, VM::M1, "Exclusion Start Datetime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0637[] = {
{ 0x0018, 0x9025, 0, VR::CS, VM::M1, "Spectrally Selected Suppression" },
{ 0x0018, 0x9435, 0, VR::CS, VM::M1, "Exposure Control Sensing Region Shape" },
{ 0x0018, 0x9805, 0, VR::FD, VM::M1, "Exclusion Duration" },
{ 0x0054, 0x0220, 0, VR::SQ, VM::M1, "View Code Sequence" },
{ 0x0072, 0x0206, 0, VR::LO, VM::M1, "Display Set Presentation Group Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0638[] = {
{ 0x0018, 0x9026, 0, VR::CS, VM::M1, "Spectrally Selected Excitation" },
{ 0x0018, 0x9436, 0, VR::SS, VM::M1, "Exposure Control Sensing Region Left Vertical Edge" },
{ 0x0018, 0x9806, 0, VR::SQ, VM::M1, "US Image Description Sequence" },
{ 0x0070, 0x0207, 0, VR::LO, VM::M1, "Graphic Group Label" },
{ 0x0074, 0x1242, 0, VR::CS, VM::M1, "SCP Status" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0639[] = {
{ 0x0018, 0x9027, 0, VR::CS, VM::M1, "Spatial Pre-saturation" },
{ 0x0018, 0x9437, 0, VR::SS, VM::M1, "Exposure Control Sensing Region Right Vertical Edge" },
{ 0x0018, 0x9807, 0, VR::SQ, VM::M1, "Image Data Type Sequence" },
{ 0x0054, 0x0222, 0, VR::SQ, VM::M1, "View Modifier Code Sequence" },
{ 0x0072, 0x0204, 0, VR::US, VM::M1, "Display Set Presentation Group" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0640[] = {
{ 0x0008, 0x2200, 1, VR::CS, VM::M1, "Transducer Position" },
{ 0x0040, 0xA040, 0, VR::CS, VM::M1, "Value Type" },
{ 0x2200, 0x0008, 0, VR::CS, VM::M1, "Include Non-DICOM Objects" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0641[] = {
{ 0x2200, 0x0009, 0, VR::CS, VM::M1, "Include Display Application" },
{ 0x3008, 0x0240, 0, VR::SQ, VM::M1, "Fraction Status Summary Sequence" },
{ 0x300A, 0x0242, 0, VR::SH, VM::M1, "Template Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0642[] = {
{ 0x0088, 0x0200, 0, VR::SQ, VM::M1, "Icon Image Sequence" },
{ 0x2200, 0x000A, 0, VR::CS, VM::M1, "Preserve Composite Instances After Media Creation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0643[] = {
{ 0x0040, 0xA043, 0, VR::SQ, VM::M1, "Concept Name Code Sequence" },
{ 0x2200, 0x000B, 0, VR::US, VM::M1, "Total Number of Pieces of Media Created" },
{ 0x300A, 0x0240, 0, VR::IS, VM::M1, "Template Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0644[] = {
{ 0x0008, 0x2204, 1, VR::CS, VM::M1, "Transducer Orientation" },
{ 0x0068, 0x6360, 0, VR::SQ, VM::M1, "Surface Model Description Sequence" },
{ 0x2200, 0x000C, 0, VR::LO, VM::M1, "Requested Media Application Profile" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0645[] = {
{ 0x2200, 0x000D, 0, VR::SQ, VM::M1, "Referenced Storage Media Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0646[] = {
{ 0x2200, 0x000E, 0, VR::AT, VM::M1TN, "Failure Attributes" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0647[] = {
{ 0x0040, 0xA047, 1, VR::LO, VM::M1, "Measurement Precision Description (Trial)" },
{ 0x2200, 0x000F, 0, VR::CS, VM::M1, "Allow Lossy Compression" },
{ 0x300A, 0x0244, 0, VR::LO, VM::M1, "Template Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0648[] = {
{ 0x0008, 0x2208, 1, VR::CS, VM::M1, "Anatomic Structure" },
{ 0x0010, 0x2210, 0, VR::CS, VM::M1, "Anatomical Orientation Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0649[] = {
{ 0x2200, 0x0001, 0, VR::CS, VM::M1, "Label Using Information Extracted From Instances" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0650[] = {
{ 0x2200, 0x0002, 0, VR::UT, VM::M1, "Label Text" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0651[] = {
{ 0x2200, 0x0003, 0, VR::CS, VM::M1, "Label Style Selection" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0652[] = {
{ 0x0014, 0x2210, 0, VR::OB, VM::M1, "Coordinate System Axis Values" },
{ 0x2200, 0x0004, 0, VR::LT, VM::M1, "Media Disposition" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0653[] = {
{ 0x2200, 0x0005, 0, VR::LT, VM::M1, "Barcode Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0654[] = {
{ 0x2200, 0x0006, 0, VR::CS, VM::M1, "Barcode Symbology" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0655[] = {
{ 0x2200, 0x0007, 0, VR::CS, VM::M1, "Allow Media Splitting" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0656[] = {
{ 0x0014, 0x220C, 0, VR::CS, VM::M1, "Coordinate System Axis Type" },
{ 0x0040, 0xA050, 0, VR::CS, VM::M1, "Continuity Of Content" },
{ 0x3008, 0x0251, 0, VR::TM, VM::M1, "Treatment Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0657[] = {
{ 0x3008, 0x0250, 0, VR::DA, VM::M1, "Treatment Date" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0658[] = {
{ 0x0014, 0x220E, 0, VR::CS, VM::M1, "Coordinate System Axis Units" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0659[] = {
{ 0x300A, 0x0250, 0, VR::DS, VM::M1, "Total Reference Air Kerma" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0660[] = {
{ 0x0014, 0x2208, 0, VR::CS, VM::M1, "Coordinate System Data Set Mapping" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0661[] = {
{ 0x0040, 0x9096, 0, VR::SQ, VM::M1, "Real World Value Mapping Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0662[] = {
{ 0x0014, 0x220A, 0, VR::IS, VM::M1, "Coordinate System Axis Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0663[] = {
{ 0x0040, 0x9094, 0, VR::SQ, VM::M1, "Referenced Image Real World Value Mapping Sequence" },
{ 0x0040, 0xA057, 1, VR::CS, VM::M1TN, "Urgency or Priority Alerts (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0664[] = {
{ 0x0008, 0x2218, 0, VR::SQ, VM::M1, "Anatomic Region Sequence" },
{ 0x0014, 0x2204, 0, VR::SQ, VM::M1, "Coordinate System Axes Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0665[] = {
{ 0x0010, 0x2201, 0, VR::LO, VM::M1, "Patient Species Description" },
{ 0x0018, 0xA001, 0, VR::SQ, VM::M1, "Contributing Equipment Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0666[] = {
{ 0x0010, 0x2202, 0, VR::SQ, VM::M1, "Patient Species Code Sequence" },
{ 0x0014, 0x2206, 0, VR::ST, VM::M1, "Coordinate System Axis Description" },
{ 0x0018, 0xA002, 0, VR::DT, VM::M1, "Contribution Date Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0667[] = {
{ 0x0010, 0x2203, 0, VR::CS, VM::M1, "Patient's Sex Neutered" },
{ 0x0018, 0xA003, 0, VR::ST, VM::M1, "Contribution Description" },
{ 0x0040, 0x9098, 0, VR::SQ, VM::M1, "Pixel Value Mapping Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0668[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0669[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0670[] = {
{ 0x0014, 0x2202, 0, VR::IS, VM::M1, "Coordinate System Number of Axes" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0671[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0672[] = {
{ 0x0008, 0x2220, 0, VR::SQ, VM::M1, "Anatomic Region Modifier Sequence" },
{ 0x0040, 0x06FA, 1, VR::LO, VM::M1, "Slide Identifier" },
{ 0x0040, 0xA060, 1, VR::LO, VM::M1, "Sequencing Indicator (Trial)" },
{ 0x300A, 0x0263, 0, VR::SH, VM::M1, "Brachy Accessory Device ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0673[] = {
{ 0x0040, 0xB020, 0, VR::SQ, VM::M1, "Waveform Annotation Sequence" },
{ 0x0068, 0x6345, 0, VR::ST, VM::M1, "HPGL Pen Description" },
{ 0x300A, 0x0262, 0, VR::IS, VM::M1, "Brachy Accessory Device Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0674[] = {
{ 0x0068, 0x6346, 0, VR::FD, VM::M2, "Recommended Rotation Point" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0675[] = {
{ 0x0068, 0x6347, 0, VR::FD, VM::M4, "Bounding Rectangle" },
{ 0x300A, 0x0260, 0, VR::SQ, VM::M1, "Brachy Accessory Device Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0676[] = {
{ 0x0068, 0x6340, 0, VR::LO, VM::M1, "HPGL Pen Label" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0677[] = {
{ 0x300A, 0x0266, 0, VR::LO, VM::M1, "Brachy Accessory Device Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0678[] = {
{ 0x0040, 0xA066, 1, VR::SQ, VM::M1, "Document Identifier Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0679[] = {
{ 0x0040, 0xA067, 1, VR::PN, VM::M1, "Document Author (Trial)" },
{ 0x300A, 0x0264, 0, VR::CS, VM::M1, "Brachy Accessory Device Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0680[] = {
{ 0x0008, 0x2228, 0, VR::SQ, VM::M1, "Primary Anatomic Structure Sequence" },
{ 0x0040, 0xA068, 1, VR::SQ, VM::M1, "Document Author Identifier Code Sequence (Trial)" },
{ 0x2200, 0x0020, 0, VR::CS, VM::M1, "Request Priority" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0681[] = {
{ 0x0008, 0x2229, 0, VR::SQ, VM::M1, "Anatomic Structure, Space or Region Sequence" },
{ 0x300A, 0x026A, 0, VR::DS, VM::M1, "Brachy Accessory Device Nominal Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0682[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0683[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0684[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0685[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0686[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0687[] = {
{ 0x300A, 0x026C, 0, VR::DS, VM::M1, "Brachy Accessory Device Nominal Transmission" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0688[] = {
{ 0x0008, 0x2230, 0, VR::SQ, VM::M1, "Primary Anatomic Structure Modifier Sequence" },
{ 0x0014, 0x222C, 0, VR::DS, VM::M1TN, "Coordinate System Transform Translation Matrix" },
{ 0x0040, 0xA070, 1, VR::SQ, VM::M1, "Identifier Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0689[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0690[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0691[] = {
{ 0x0040, 0xA073, 0, VR::SQ, VM::M1, "Verifying Observer Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0692[] = {
{ 0x0014, 0x2228, 0, VR::CS, VM::M1, "Transformed Axis Units" },
{ 0x0040, 0xA074, 1, VR::OB, VM::M1, "Object Binary Identifier (Trial)" },
{ 0x0068, 0x6350, 0, VR::US, VM::M1TN, "Implant Template 3D Model Surface Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0693[] = {
{ 0x0040, 0xA075, 0, VR::PN, VM::M1, "Verifying Observer Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0694[] = {
{ 0x0014, 0x222A, 0, VR::DS, VM::M1TN, "Coordinate System Transform Rotation and Scale Matrix" },
{ 0x0040, 0xA076, 1, VR::SQ, VM::M1, "Documenting Observer Identifier Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0695[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0696[] = {
{ 0x0014, 0x2224, 0, VR::IS, VM::M1, "Transform Number of Axes" },
{ 0x0040, 0xA078, 0, VR::SQ, VM::M1, "Author Observer Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0697[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0698[] = {
{ 0x0014, 0x2226, 0, VR::IS, VM::M1TN, "Transform Order of Axes" },
{ 0x0040, 0xA07A, 0, VR::SQ, VM::M1, "Participant Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0699[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0700[] = {
{ 0x0014, 0x2220, 0, VR::SQ, VM::M1, "Coordinate System Transform Sequence" },
{ 0x0040, 0xA07C, 0, VR::SQ, VM::M1, "Custodial Organization Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0701[] = {
{ 0x7F00, 0x0040, 1, VR::OW, VM::M1, "Variable Coefficients SDDN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0702[] = {
{ 0x0014, 0x2222, 0, VR::ST, VM::M1, "Transform Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0703[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0704[] = {
{ 0x3008, 0x0200, 0, VR::CS, VM::M1, "Current Treatment Status" },
{ 0x300A, 0x0202, 0, VR::CS, VM::M1, "Brachy Treatment Type" },
{ 0x4FFE, 0x0001, 0, VR::SQ, VM::M1, "MAC Parameters Sequence" },
{ 0x600E, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0705[] = {
{ 0x0008, 0x2240, 1, VR::SQ, VM::M1, "Transducer Position Sequence" },
{ 0x600C, 0x1301, 0, VR::IS, VM::M1, "ROI Area 7" },
{ 0x600E, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0706[] = {
{ 0x0018, 0x9098, 0, VR::FD, VM::M1T2, "Transmitter Frequency" },
{ 0x3008, 0x0202, 0, VR::ST, VM::M1, "Treatment Status Comment" },
{ 0x300A, 0x0200, 0, VR::CS, VM::M1, "Brachy Treatment Technique" },
{ 0x600C, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0707[] = {
{ 0x0008, 0x2242, 1, VR::SQ, VM::M1, "Transducer Position Modifier Sequence" },
{ 0x600C, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 7" },
{ 0x600E, 0x1301, 0, VR::IS, VM::M1, "ROI Area 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0708[] = {
{ 0x300A, 0x0206, 0, VR::SQ, VM::M1, "Treatment Machine Sequence" },
{ 0x600A, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0709[] = {
{ 0x0008, 0x2244, 1, VR::SQ, VM::M1, "Transducer Orientation Sequence" },
{ 0x0068, 0x6320, 0, VR::SQ, VM::M1, "HPGL Pen Sequence" },
{ 0x6008, 0x1301, 0, VR::IS, VM::M1, "ROI Area 5" },
{ 0x600A, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0710[] = {
{ 0x0040, 0xA007, 1, VR::CS, VM::M1, "Findings Flag (Trial)" },
{ 0x6008, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0711[] = {
{ 0x0008, 0x2246, 1, VR::SQ, VM::M1, "Transducer Orientation Modifier Sequence" },
{ 0x6008, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 5" },
{ 0x600A, 0x1301, 0, VR::IS, VM::M1, "ROI Area 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0712[] = {
{ 0x0018, 0x9092, 0, VR::SQ, VM::M1, "Velocity Encoding Acquisition Sequence" },
{ 0x6006, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0713[] = {
{ 0x0018, 0x9093, 0, VR::US, VM::M1, "Number of k-Space Trajectories" },
{ 0x6004, 0x1301, 0, VR::IS, VM::M1, "ROI Area 3" },
{ 0x6006, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0714[] = {
{ 0x0018, 0x9090, 0, VR::FD, VM::M3, "Velocity Encoding Direction" },
{ 0x0040, 0x0281, 0, VR::SQ, VM::M1, "Performed Procedure Step Discontinuation Reason Code Sequence" },
{ 0x6004, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 3" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0715[] = {
{ 0x0018, 0x9091, 0, VR::FD, VM::M1, "Velocity Encoding Minimum Value" },
{ 0x0040, 0x0280, 0, VR::ST, VM::M1, "Comments on the Performed Procedure Step" },
{ 0x6004, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 3" },
{ 0x6006, 0x1301, 0, VR::IS, VM::M1, "ROI Area 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0716[] = {
{ 0x0018, 0x9096, 1, VR::FD, VM::M1, "Parallel Reduction Factor In-plane (Retired)" },
{ 0x6002, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 2" },
{ 0x7F00, 0x0030, 1, VR::OW, VM::M1, "Variable Coefficients SDHN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0717[] = {
{ 0x6000, 0x1301, 0, VR::IS, VM::M1, "ROI Area" },
{ 0x6002, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0718[] = {
{ 0x0018, 0x9094, 0, VR::CS, VM::M1, "Coverage of k-Space" },
{ 0x6000, 0x1302, 0, VR::DS, VM::M1, "ROI Mean" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0719[] = {
{ 0x0018, 0x9095, 0, VR::UL, VM::M1, "Spectroscopy Acquisition Phase Rows" },
{ 0x6000, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation" },
{ 0x6002, 0x1301, 0, VR::IS, VM::M1, "ROI Area 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0720[] = {
{ 0x0008, 0x2251, 1, VR::SQ, VM::M1, "Anatomic Structure Space Or Region Code Sequence (Trial)" },
{ 0x300A, 0x0212, 0, VR::IS, VM::M1, "Source Number" },
{ 0x601E, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0721[] = {
{ 0x0040, 0xA010, 0, VR::CS, VM::M1, "Relationship Type" },
{ 0x601C, 0x1301, 0, VR::IS, VM::M1, "ROI Area 15" },
{ 0x601E, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0722[] = {
{ 0x0008, 0x2253, 1, VR::SQ, VM::M1, "Anatomic Portal Of Entrance Code Sequence (Trial)" },
{ 0x0040, 0xA403, 1, VR::CS, VM::M1, "Observation Subject Class (Trial)" },
{ 0x300A, 0x0210, 0, VR::SQ, VM::M1, "Source Sequence" },
{ 0x601C, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0723[] = {
{ 0x0018, 0x9089, 0, VR::FD, VM::M3, "Diffusion Gradient Orientation" },
{ 0x0040, 0xA402, 1, VR::UI, VM::M1, "Observation Subject UID (Trial)" },
{ 0x601C, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 15" },
{ 0x601E, 0x1301, 0, VR::IS, VM::M1, "ROI Area 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0724[] = {
{ 0x0008, 0x2255, 1, VR::SQ, VM::M1, "Anatomic Approach Direction Code Sequence (Trial)" },
{ 0x300A, 0x0216, 0, VR::LO, VM::M1, "Source Manufacturer" },
{ 0x601A, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0725[] = {
{ 0x0040, 0xA404, 1, VR::SQ, VM::M1, "Observation Subject Type Code Sequence (Trial)" },
{ 0x0068, 0x6330, 0, VR::US, VM::M1, "HPGL Pen Number" },
{ 0x6018, 0x1301, 0, VR::IS, VM::M1, "ROI Area 13" },
{ 0x601A, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0726[] = {
{ 0x0008, 0x2257, 1, VR::SQ, VM::M1, "Anatomic Perspective Code Sequence (Trial)" },
{ 0x300A, 0x0214, 0, VR::CS, VM::M1, "Source Type" },
{ 0x6018, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0727[] = {
{ 0x0008, 0x2256, 1, VR::ST, VM::M1, "Anatomic Perspective Description (Trial)" },
{ 0x6018, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 13" },
{ 0x601A, 0x1301, 0, VR::IS, VM::M1, "ROI Area 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0728[] = {
{ 0x0008, 0x2259, 1, VR::SQ, VM::M1, "Anatomic Location Of Examining Instrument Code Sequence (Trial)" },
{ 0x0008, 0x9092, 0, VR::SQ, VM::M1, "Referenced Image Evidence Sequence" },
{ 0x0018, 0x9082, 0, VR::FD, VM::M1, "Effective Echo Time" },
{ 0x0040, 0x0293, 0, VR::SQ, VM::M1, "Quantity Sequence" },
{ 0x300A, 0x021A, 0, VR::DS, VM::M1, "Active Source Length" },
{ 0x6016, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0729[] = {
{ 0x0008, 0x2258, 1, VR::ST, VM::M1, "Anatomic Location Of Examining Instrument Description (Trial)" },
{ 0x0018, 0x9083, 0, VR::SQ, VM::M1, "Metabolite Map Code Sequence" },
{ 0x6014, 0x1301, 0, VR::IS, VM::M1, "ROI Area 11" },
{ 0x6016, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0730[] = {
{ 0x0018, 0x9080, 0, VR::ST, VM::M1, "Metabolite Map Description" },
{ 0x300A, 0x0218, 0, VR::DS, VM::M1, "Active Source Diameter" },
{ 0x6014, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0731[] = {
{ 0x0008, 0x225A, 1, VR::SQ, VM::M1, "Anatomic Structure Space Or Region Modifier Code Sequence (Trial)" },
{ 0x0018, 0x9081, 0, VR::CS, VM::M1, "Partial Fourier" },
{ 0x6014, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 11" },
{ 0x6016, 0x1301, 0, VR::IS, VM::M1, "ROI Area 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0732[] = {
{ 0x6012, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 10" },
{ 0x7F00, 0x0020, 1, VR::OW, VM::M1, "Variable Coefficients SDVN" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0733[] = {
{ 0x0008, 0x225C, 1, VR::SQ, VM::M1, "OnAxis Background Anatomic Structure Code Sequence (Trial)" },
{ 0x0018, 0x9087, 0, VR::FD, VM::M1, "Diffusion b-value" },
{ 0x0040, 0x0296, 0, VR::SQ, VM::M1, "Billing Item Sequence" },
{ 0x6010, 0x1301, 0, VR::IS, VM::M1, "ROI Area 9" },
{ 0x6012, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0734[] = {
{ 0x0018, 0x9084, 0, VR::SQ, VM::M1, "Chemical Shift Sequence" },
{ 0x0040, 0x0295, 0, VR::SQ, VM::M1, "Measuring Units Sequence" },
{ 0x6010, 0x1302, 0, VR::DS, VM::M1, "ROI Mean 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0735[] = {
{ 0x0018, 0x9085, 0, VR::CS, VM::M1, "Cardiac Signal Source" },
{ 0x0040, 0x0294, 0, VR::DS, VM::M1, "Quantity" },
{ 0x6010, 0x1303, 0, VR::DS, VM::M1, "ROI Standard Deviation 9" },
{ 0x6012, 0x1301, 0, VR::IS, VM::M1, "ROI Area 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0736[] = {
{ 0x0040, 0xA021, 1, VR::UI, VM::M1, "Findings Group UID (Trial)" },
{ 0x3008, 0x0220, 0, VR::SQ, VM::M1, "Fraction Group Summary Sequence" },
{ 0x300A, 0x0222, 0, VR::DS, VM::M1, "Source Encapsulation Nominal Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0737[] = {
{ 0x0040, 0xA020, 1, VR::SQ, VM::M1, "Findings Sequence (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0738[] = {
{ 0x0040, 0xA023, 1, VR::DA, VM::M1, "Findings Group Recording Date (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0739[] = {
{ 0x0040, 0xA022, 1, VR::UI, VM::M1, "Referenced Findings Group UID (Trial)" },
{ 0x3008, 0x0223, 0, VR::IS, VM::M1, "Referenced Fraction Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0740[] = {
{ 0x3008, 0x0224, 0, VR::CS, VM::M1, "Fraction Group Type" },
{ 0x300A, 0x0226, 0, VR::LO, VM::M1, "Source Isotope Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0741[] = {
{ 0x0040, 0xA024, 1, VR::TM, VM::M1, "Findings Group Recording Time (Trial)" },
{ 0x0068, 0x6300, 0, VR::OB, VM::M1, "HPGL Document" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0742[] = {
{ 0x0040, 0xA027, 0, VR::LO, VM::M1, "Verifying Organization" },
{ 0x300A, 0x0224, 0, VR::DS, VM::M1, "Source Encapsulation Nominal Transmission" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0743[] = {
{ 0x0040, 0xA026, 1, VR::SQ, VM::M1, "Findings Source Category Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0744[] = {
{ 0x300A, 0x022A, 0, VR::DS, VM::M1, "Reference Air Kerma Rate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0745[] = {
{ 0x0040, 0xA028, 1, VR::SQ, VM::M1, "Documenting Organization Identifier Code Sequence (Trial)" },
{ 0x300A, 0x022B, 0, VR::DS, VM::M1, "Source Strength" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0746[] = {
{ 0x300A, 0x0228, 0, VR::DS, VM::M1, "Source Isotope Half Life" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0747[] = {
{ 0x300A, 0x0229, 0, VR::CS, VM::M1, "Source Strength Units" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0748[] = {
{ 0x300A, 0x022E, 0, VR::TM, VM::M1, "Source Strength Reference Time" },
{ 0x7F00, 0x0010, 1, VR::OX, VM::M1, "Variable Pixel Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0749[] = {
{ 0x7F00, 0x0011, 1, VR::US, VM::M1, "Variable Next Data Group" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0750[] = {
{ 0x0070, 0x0295, 0, VR::UL, VM::M1, "Graphic Group ID" },
{ 0x300A, 0x022C, 0, VR::DA, VM::M1, "Source Strength Reference Date" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0751[] = {
{ 0x0070, 0x0294, 0, VR::CS, VM::M1, "Compound Graphic Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0752[] = {
{ 0x3008, 0x0230, 0, VR::CS, VM::M1, "Beam Stopper Position" },
{ 0x300A, 0x0232, 0, VR::CS, VM::M1, "Application Setup Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0753[] = {
{ 0x0040, 0xA030, 0, VR::DT, VM::M1, "Verification Date Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0754[] = {
{ 0x0070, 0x0289, 0, VR::SH, VM::M1, "Tick Label" },
{ 0x300A, 0x0230, 0, VR::SQ, VM::M1, "Application Setup Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0755[] = {
{ 0x0028, 0x9099, 1, VR::US, VM::M1, "Largest Monochrome Pixel Value" },
{ 0x0040, 0xA032, 0, VR::DT, VM::M1, "Observation Date Time" },
{ 0x0070, 0x0288, 0, VR::FL, VM::M1, "Tick Position" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0756[] = {
{ 0x300A, 0x0236, 0, VR::LO, VM::M1, "Application Setup Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0757[] = {
{ 0x0068, 0x6310, 0, VR::US, VM::M1, "HPGL Contour Pen Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0758[] = {
{ 0x300A, 0x0234, 0, VR::IS, VM::M1, "Application Setup Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0759[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0760[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0761[] = {
{ 0x0070, 0x0282, 0, VR::CS, VM::M1, "Compound Graphic Units" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0762[] = {
{ 0x300A, 0x0238, 0, VR::LO, VM::M1, "Application Setup Manufacturer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0763[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0764[] = {
{ 0x0070, 0x0287, 0, VR::SQ, VM::M1, "Major Ticks Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0765[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0766[] = {
{ 0x0070, 0x0285, 0, VR::FL, VM::M1, "Pattern Off Opacity" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0767[] = {
{ 0x0070, 0x0284, 0, VR::FL, VM::M1, "Pattern On Opacity" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0768[] = {
{ 0x0020, 0x9165, 0, VR::AT, VM::M1, "Dimension Index Pointer" },
{ 0x4008, 0x0200, 1, VR::SH, VM::M1, "Interpretation ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0769[] = {
{ 0x0020, 0x9164, 0, VR::UI, VM::M1, "Dimension Organization UID" },
{ 0x0074, 0x1338, 0, VR::FD, VM::M1, "Double Exposure Meterset" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0770[] = {
{ 0x0020, 0x9167, 0, VR::AT, VM::M1, "Functional Group Pointer" },
{ 0x0068, 0x62E0, 0, VR::SQ, VM::M1, "View Orientation Code Sequence" },
{ 0x4008, 0x0202, 1, VR::LO, VM::M1, "Interpretation ID Issuer" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0771[] = {
{ 0x0074, 0x133A, 0, VR::FD, VM::M4, "Double Exposure Field Delta" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0772[] = {
{ 0x0018, 0x9159, 0, VR::UL, VM::M1, "Spectroscopy Acquisition Out-of-plane Phase Steps" },
{ 0x0020, 0x9161, 0, VR::UI, VM::M1, "Concatenation UID" },
{ 0x0028, 0x0730, 1, VR::US, VM::M1, "Adaptive Map Format" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0773[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0774[] = {
{ 0x0020, 0x9163, 0, VR::US, VM::M1, "In-concatenation Total Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0775[] = {
{ 0x0020, 0x9162, 0, VR::US, VM::M1, "In-concatenation Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0776[] = {
{ 0x0018, 0x9155, 0, VR::FD, VM::M1, "Parallel Reduction Factor out-of-plane" },
{ 0x0024, 0x0320, 0, VR::SQ, VM::M1, "Visual Field Global Results Index Sequence" },
{ 0x0054, 0x1311, 0, VR::IS, VM::M1TN, "Secondary Counts Accumulated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0777[] = {
{ 0x0054, 0x1310, 0, VR::IS, VM::M1, "Primary (Prompts) Counts Accumulated" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0778[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0779[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0780[] = {
{ 0x0018, 0x9151, 0, VR::DT, VM::M1, "Frame Reference DateTime" },
{ 0x0040, 0x0340, 0, VR::SQ, VM::M1, "Performed Series Sequence" },
{ 0x0400, 0x0310, 0, VR::OB, VM::M1, "Certified Timestamp" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0781[] = {
{ 0x0024, 0x0325, 0, VR::SQ, VM::M1, "Data Observation Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0782[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0783[] = {
{ 0x0018, 0x9152, 0, VR::SQ, VM::M1, "MR Metabolite Map Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0784[] = {
{ 0x0024, 0x0338, 0, VR::CS, VM::M1, "Index Normals Flag" },
{ 0x0068, 0x62F2, 0, VR::FD, VM::M1, "HPGL Document Scaling" },
{ 0x4008, 0x0210, 1, VR::CS, VM::M1, "Interpretation Type ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0785[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0786[] = {
{ 0x0068, 0x62F0, 0, VR::FD, VM::M9, "View Orientation Modifier" },
{ 0x4008, 0x0212, 1, VR::CS, VM::M1, "Interpretation Status ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0787[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0788[] = {
{ 0x0028, 0x0720, 1, VR::US, VM::M1, "Zonal Map Number Format" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0789[] = {
{ 0x0028, 0x0721, 1, VR::AT, VM::M1TN, "Zonal Map Location" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0790[] = {
{ 0x0028, 0x0722, 1, VR::US, VM::M1, "Zonal Map Format" },
{ 0x0040, 0x074A, 0, VR::DS, VM::M1, "Z Offset in Slide Coordinate System" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0791[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0792[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0793[] = {
{ 0x0008, 0x9154, 0, VR::SQ, VM::M1, "Source Image Evidence Sequence" },
{ 0x0054, 0x1300, 0, VR::DS, VM::M1, "Frame Reference Time" },
{ 0x0400, 0x0305, 0, VR::CS, VM::M1, "Certified Timestamp Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0794[] = {
{ 0x0018, 0x9147, 0, VR::CS, VM::M1, "Diffusion Anisotropy Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0795[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0796[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0797[] = {
{ 0x0074, 0x1324, 0, VR::UL, VM::M1, "Beam Order Index" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0798[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0799[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0800[] = {
{ 0x0024, 0x0308, 0, VR::LO, VM::M1, "Data Set Source" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0801[] = {
{ 0x0024, 0x0309, 0, VR::LO, VM::M1, "Data Set Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0802[] = {
{ 0x0068, 0x62C0, 0, VR::SQ, VM::M1, "HPGL Document Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0803[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0804[] = {
{ 0x0018, 0x9179, 0, VR::CS, VM::M1, "Specific Absorption Rate Definition" },
{ 0x0028, 0x0300, 0, VR::CS, VM::M1, "Quality Control Image" },
{ 0x0028, 0x0710, 1, VR::US, VM::M1, "Normalization Factor Format" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0805[] = {
{ 0x0018, 0x9178, 0, VR::CS, VM::M1, "Operating Mode" },
{ 0x0028, 0x0301, 0, VR::CS, VM::M1, "Burned In Annotation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0806[] = {
{ 0x0028, 0x0302, 0, VR::CS, VM::M1, "Recognizable Visual Features" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0807[] = {
{ 0x0028, 0x0303, 0, VR::CS, VM::M1, "Longitudinal Temporal Information Modified" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0808[] = {
{ 0x0018, 0x9175, 0, VR::LO, VM::M1, "Applicable Safety Standard Description" },
{ 0x0028, 0x9145, 0, VR::SQ, VM::M1, "Pixel Value Transformation Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0809[] = {
{ 0x0018, 0x9174, 0, VR::CS, VM::M1, "Applicable Safety Standard Agency" },
{ 0x0054, 0x1330, 0, VR::US, VM::M1, "Image Index" },
{ 0x5200, 0x9229, 0, VR::SQ, VM::M1, "Shared Functional Groups Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0810[] = {
{ 0x0018, 0x9177, 0, VR::CS, VM::M1, "Operating Mode Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0811[] = {
{ 0x0018, 0x9176, 0, VR::SQ, VM::M1, "Operating Mode Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0812[] = {
{ 0x0018, 0x9171, 0, VR::CS, VM::M1, "Respiratory Signal Source" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0813[] = {
{ 0x0018, 0x9170, 0, VR::CS, VM::M1, "Respiratory Motion Compensation Technique" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0814[] = {
{ 0x0018, 0x9173, 0, VR::CS, VM::M1, "Bulk Motion Signal Source" },
{ 0x0024, 0x0306, 0, VR::LO, VM::M1, "Data Set Name" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0815[] = {
{ 0x0018, 0x9172, 0, VR::CS, VM::M1, "Bulk Motion Compensation Technique" },
{ 0x0024, 0x0307, 0, VR::LO, VM::M1, "Data Set Version" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0816[] = {
{ 0x0020, 0x9155, 0, VR::FL, VM::M1, "Actual Cardiac Trigger Time Prior To R-Peak" },
{ 0x5200, 0x9230, 0, VR::SQ, VM::M1, "Per-frame Functional Groups Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0817[] = {
{ 0x0020, 0x9154, 0, VR::FL, VM::M1, "Nominal Cardiac Trigger Time Prior To R-Peak" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0818[] = {
{ 0x0020, 0x9157, 0, VR::UL, VM::M1TN, "Dimension Index Values" },
{ 0x0068, 0x62D0, 0, VR::US, VM::M1, "HPGL Document ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0819[] = {
{ 0x0020, 0x9156, 0, VR::US, VM::M1, "Frame Acquisition Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0820[] = {
{ 0x0018, 0x9169, 0, VR::CS, VM::M1, "Cardiac Beat Rejection Technique" },
{ 0x0028, 0x0700, 1, VR::LO, VM::M1, "DCT Label" },
{ 0x0028, 0x1351, 0, VR::ST, VM::M1, "Partial View Description" },
{ 0x0038, 0x0300, 0, VR::LO, VM::M1, "Current Patient Location" },
{ 0x003A, 0x0302, 0, VR::CS, VM::M1, "Channel Mode" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0821[] = {
{ 0x0018, 0x9168, 0, VR::FD, VM::M1, "Parallel Reduction Factor Second In-plane" },
{ 0x0028, 0x0701, 1, VR::CS, VM::M1TN, "Data Block Description" },
{ 0x0028, 0x1350, 0, VR::CS, VM::M1, "Partial View" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0822[] = {
{ 0x0020, 0x9153, 0, VR::FD, VM::M1, "Nominal Cardiac Trigger Delay Time" },
{ 0x0028, 0x0702, 1, VR::AT, VM::M1TN, "Data Block" },
{ 0x003A, 0x0300, 0, VR::SQ, VM::M1, "Multiplexed Audio Channels Description Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0823[] = {
{ 0x0028, 0x1352, 0, VR::SQ, VM::M1, "Partial View Code Sequence" },
{ 0x003A, 0x0301, 0, VR::IS, VM::M1, "Channel Identification Code" },
{ 0x0068, 0x62D5, 0, VR::LO, VM::M1, "HPGL Document Label" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0824[] = {
{ 0x0054, 0x1321, 0, VR::DS, VM::M1, "Decay Factor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0825[] = {
{ 0x0054, 0x1320, 0, VR::DS, VM::M1, "Slice Sensitivity Factor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0826[] = {
{ 0x0054, 0x1323, 0, VR::DS, VM::M1, "Scatter Fraction Factor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0827[] = {
{ 0x0018, 0x9166, 1, VR::CS, VM::M1, "Bulk Motion Status" },
{ 0x0054, 0x1322, 0, VR::DS, VM::M1, "Dose Calibration Factor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0828[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0829[] = {
{ 0x0020, 0x9158, 0, VR::LT, VM::M1, "Frame Comments" },
{ 0x0054, 0x1324, 0, VR::DS, VM::M1, "Dead Time Factor" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0830[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0831[] = {
{ 0x0024, 0x0317, 0, VR::SQ, VM::M1, "Visual Field Test Reliability Global Index Sequence" },
{ 0x0028, 0x135A, 0, VR::CS, VM::M1, "Spatial Locations Preserved" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0832[] = {
{ 0x0018, 0x1314, 0, VR::DS, VM::M1, "Flip Angle" },
{ 0x0018, 0x1704, 0, VR::IS, VM::M1, "Collimator Right Vertical Edge" },
{ 0x0018, 0x5210, 1, VR::DS, VM::M6, "Image Transformation Matrix" },
{ 0x300A, 0x0384, 0, VR::FL, VM::M1, "Range Modulator Gating Stop Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0833[] = {
{ 0x0018, 0x1315, 0, VR::CS, VM::M1, "Variable Flip Angle Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0834[] = {
{ 0x0018, 0x1316, 0, VR::DS, VM::M1, "SAR" },
{ 0x0018, 0x1706, 0, VR::IS, VM::M1, "Collimator Upper Horizontal Edge" },
{ 0x0018, 0x5212, 1, VR::DS, VM::M3, "Image Translation Vector" },
{ 0x0020, 0x9536, 0, VR::US, VM::M1, "Reconstruction Index" },
{ 0x300A, 0x0386, 0, VR::FL, VM::M1, "Range Modulator Gating Start Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0835[] = {
{ 0x0040, 0x030E, 0, VR::SQ, VM::M1, "Exposure Dose Sequence" },
{ 0x0068, 0x62A0, 0, VR::SQ, VM::M1, "Implant Regulatory Disapproval Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0836[] = {
{ 0x0018, 0x1310, 0, VR::US, VM::M4, "Acquisition Matrix" },
{ 0x0018, 0x1700, 0, VR::CS, VM::M1T3, "Collimator Shape" },
{ 0x0018, 0x9118, 0, VR::SQ, VM::M1, "Cardiac Synchronization Sequence" },
{ 0x0018, 0x9508, 0, VR::FL, VM::M1, "Primary Positioner Scan Arc" },
{ 0x0048, 0x0301, 0, VR::CS, VM::M1, "Pixel Origin Interpretation" },
{ 0x300A, 0x0380, 0, VR::SQ, VM::M1, "Range Modulator Settings Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0837[] = {
{ 0x0018, 0x9119, 0, VR::SQ, VM::M1, "MR Averages Sequence" },
{ 0x0018, 0x9509, 0, VR::FL, VM::M1, "Secondary Positioner Scan Arc" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0838[] = {
{ 0x0018, 0x1312, 0, VR::CS, VM::M1, "In-plane Phase Encoding Direction" },
{ 0x0018, 0x1702, 0, VR::IS, VM::M1, "Collimator Left Vertical Edge" },
{ 0x0068, 0x62A5, 0, VR::FD, VM::M1, "Overall Template Spatial Tolerance" },
{ 0x300A, 0x0382, 0, VR::FL, VM::M1, "Range Modulator Gating Start Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0839[] = {
{ 0x0040, 0x071A, 0, VR::SQ, VM::M1, "Image Center Point Coordinates Sequence" },
{ 0x0040, 0xA180, 0, VR::US, VM::M1, "Annotation Group Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0840[] = {
{ 0x0018, 0x9114, 0, VR::SQ, VM::M1, "MR Echo Sequence" },
{ 0x0018, 0x9504, 0, VR::SQ, VM::M1, "X-Ray 3D Frame Type Sequence" },
{ 0x5600, 0x0010, 0, VR::OF, VM::M1, "First Order Phase Correction Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0841[] = {
{ 0x0018, 0x9115, 0, VR::SQ, VM::M1, "MR Modifier Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0842[] = {
{ 0x0018, 0x9506, 0, VR::SQ, VM::M1, "Contributing Sources Sequence" },
{ 0x0040, 0x0307, 1, VR::DS, VM::M1, "Distance Source to Support" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0843[] = {
{ 0x0018, 0x9117, 0, VR::SQ, VM::M1, "MR Diffusion Sequence" },
{ 0x0018, 0x9507, 0, VR::SQ, VM::M1, "X-Ray 3D Acquisition Sequence" },
{ 0x0028, 0x9537, 0, VR::CS, VM::M1, "Equipment Coordinate System Identification" },
{ 0x0040, 0x0306, 0, VR::DS, VM::M1, "Distance Source to Entrance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0844[] = {
{ 0x0018, 0x1318, 0, VR::DS, VM::M1, "dB/dt" },
{ 0x0018, 0x1708, 0, VR::IS, VM::M1, "Collimator Lower Horizontal Edge" },
{ 0x0018, 0x8151, 0, VR::DS, VM::M1, "X-Ray Tube Current in uA" },
{ 0x0020, 0x9128, 0, VR::UL, VM::M1, "Temporal Position Index" },
{ 0x0040, 0x0301, 0, VR::US, VM::M1, "Total Number of Exposures" },
{ 0x300A, 0x0388, 0, VR::FL, VM::M1, "Range Modulator Gating Stop Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0845[] = {
{ 0x0018, 0x8150, 0, VR::DS, VM::M1, "Exposure Time in uS" },
{ 0x0040, 0x0300, 0, VR::US, VM::M1, "Total Time of Fluoroscopy" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0846[] = {
{ 0x0018, 0x9112, 0, VR::SQ, VM::M1, "MR Timing and Related Parameters Sequence" },
{ 0x0040, 0x0303, 0, VR::US, VM::M1T2, "Exposed Area" },
{ 0x300A, 0x038A, 0, VR::FL, VM::M1, "Isocenter to Range Modulator Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0847[] = {
{ 0x0040, 0x0302, 0, VR::US, VM::M1, "Entrance Dose" },
{ 0x0072, 0x0330, 0, VR::FD, VM::M1, "Cine Relative to Real-Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0848[] = {
{ 0x300A, 0x0394, 0, VR::FL, VM::M1TN, "Scan Spot Position Map" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0849[] = {
{ 0x0054, 0x0308, 0, VR::US, VM::M1, "Energy Window Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0850[] = {
{ 0x0040, 0xA195, 0, VR::SQ, VM::M1, "Modifier Code Sequence" },
{ 0x300A, 0x0396, 0, VR::FL, VM::M1TN, "Scan Spot Meterset Weights" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0851[] = {
{ 0x0040, 0xA194, 1, VR::CS, VM::M1, "Measurement Automation (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0852[] = {
{ 0x0018, 0x1300, 0, VR::DS, VM::M1, "Scan Velocity" },
{ 0x0018, 0x1710, 0, VR::IS, VM::M2, "Center of Circular Collimator" },
{ 0x0040, 0xA193, 1, VR::TM, VM::M1, "Observation Time (Trial)" },
{ 0x300A, 0x0390, 0, VR::SH, VM::M1, "Scan Spot Tune ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0853[] = {
{ 0x0018, 0x1301, 0, VR::CS, VM::M1TN, "Whole Body Technique" },
{ 0x0040, 0x0318, 0, VR::CS, VM::M1, "Organ Exposed" },
{ 0x0040, 0xA192, 1, VR::DA, VM::M1, "Observation Date (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0854[] = {
{ 0x0018, 0x1302, 0, VR::IS, VM::M1, "Scan Length" },
{ 0x0018, 0x1712, 0, VR::IS, VM::M1, "Radius of Circular Collimator" },
{ 0x300A, 0x0392, 0, VR::IS, VM::M1, "Number of Scan Spot Positions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0855[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0856[] = {
{ 0x0018, 0x9104, 0, VR::FD, VM::M1, "Slab Thickness" },
{ 0x0018, 0x9514, 0, VR::FL, VM::M1, "Primary Positioner Increment" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0857[] = {
{ 0x0018, 0x9105, 0, VR::FD, VM::M3, "Slab Orientation" },
{ 0x0018, 0x9515, 0, VR::FL, VM::M1, "Secondary Positioner Increment" },
{ 0x0040, 0x0314, 0, VR::DS, VM::M1, "Half Value Layer" },
{ 0x0054, 0x0300, 0, VR::SQ, VM::M1, "Radionuclide Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0858[] = {
{ 0x0018, 0x9106, 0, VR::FD, VM::M3, "Mid Slab Position" },
{ 0x0018, 0x9516, 0, VR::DT, VM::M1, "Start Acquisition DateTime" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0859[] = {
{ 0x0018, 0x9107, 0, VR::SQ, VM::M1, "MR Spatial Saturation Sequence" },
{ 0x0018, 0x9517, 0, VR::DT, VM::M1, "End Acquisition DateTime" },
{ 0x0040, 0x0316, 0, VR::DS, VM::M1, "Organ Dose" },
{ 0x0054, 0x0302, 0, VR::SQ, VM::M1, "Administration Route Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0860[] = {
{ 0x0018, 0x9100, 0, VR::CS, VM::M1T2, "Resonant Nucleus" },
{ 0x0018, 0x9510, 0, VR::FL, VM::M1, "Primary Positioner Scan Start Angle" },
{ 0x0028, 0x9520, 0, VR::DS, VM::M16, "Image to Equipment Mapping Matrix" },
{ 0x300A, 0x0398, 0, VR::FL, VM::M2, "Scanning Spot Size" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0861[] = {
{ 0x0018, 0x9101, 0, VR::CS, VM::M1, "Frequency Correction" },
{ 0x0018, 0x9511, 0, VR::FL, VM::M1, "Secondary Positioner Scan Start Angle" },
{ 0x0020, 0x9529, 0, VR::SQ, VM::M1, "Contributing SOP Instances Reference Sequence" },
{ 0x0040, 0x0310, 0, VR::ST, VM::M1, "Comments on Radiation Dose" },
{ 0x0054, 0x0304, 0, VR::SQ, VM::M1, "Radiopharmaceutical Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0862[] = {
{ 0x0022, 0x1330, 0, VR::SQ, VM::M1, "Referenced Ophthalmic Axial Length Measurement QC Image Sequence" },
{ 0x0028, 0x9132, 0, VR::SQ, VM::M1, "Frame VOI LUT Sequence" },
{ 0x300A, 0x039A, 0, VR::IS, VM::M1, "Number of Paintings" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0863[] = {
{ 0x0018, 0x9103, 0, VR::SQ, VM::M1, "MR Spectroscopy FOV/Geometry Sequence" },
{ 0x0040, 0x0312, 0, VR::DS, VM::M1, "X-Ray Output" },
{ 0x0054, 0x0306, 0, VR::SQ, VM::M1, "Calibration Data Sequence" },
{ 0x0072, 0x0320, 0, VR::US, VM::M1, "Image Box Overlap Priority" },
{ 0xFFFE, 0xE0DD, 0, VR::XX, VM::M0, "Sequence Delimitation Item" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0864[] = {
{ 0x300A, 0x03A4, 0, VR::SQ, VM::M1, "Ion Beam Limiting Device Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0865[] = {
{ 0x0070, 0x031C, 0, VR::SQ, VM::M1, "Fiducial Set Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0866[] = {
{ 0x300A, 0x03A6, 0, VR::SQ, VM::M1, "Ion Block Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0867[] = {
{ 0x0068, 0x6280, 0, VR::ST, VM::M1, "Information Summary" },
{ 0x0070, 0x031E, 0, VR::SQ, VM::M1, "Fiducial Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0868[] = {
{ 0x0018, 0x1720, 0, VR::IS, VM::M2T2N, "Vertices of the Polygonal Collimator" },
{ 0x0018, 0x9528, 0, VR::LO, VM::M1, "Algorithm Description" },
{ 0x0028, 0x1300, 0, VR::CS, VM::M1, "Breast Implant Present" },
{ 0x0028, 0x9108, 0, VR::CS, VM::M1, "Data Representation" },
{ 0x300A, 0x03A0, 0, VR::SQ, VM::M1, "Ion Tolerance Table Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0869[] = {
{ 0x0070, 0x0318, 0, VR::SQ, VM::M1, "Graphic Coordinates Data Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0870[] = {
{ 0x300A, 0x03A2, 0, VR::SQ, VM::M1, "Ion Beam Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0871[] = {
{ 0x0040, 0x073A, 0, VR::DS, VM::M1, "Y Offset in Slide Coordinate System" },
{ 0x0070, 0x031A, 0, VR::UI, VM::M1, "Fiducial UID" },
{ 0x0072, 0x0318, 0, VR::US, VM::M1, "Image Box Large Scroll Amount" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0872[] = {
{ 0x0008, 0x9124, 0, VR::SQ, VM::M1, "Derivation Image Sequence" },
{ 0x0018, 0x9524, 0, VR::LO, VM::M1, "Application Name" },
{ 0x0024, 0x0341, 0, VR::FL, VM::M1, "Index Probability" },
{ 0x300A, 0x03AC, 0, VR::SQ, VM::M1, "Ion Wedge Position Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0873[] = {
{ 0x0018, 0x9525, 0, VR::LO, VM::M1, "Application Version" },
{ 0x0040, 0x0324, 0, VR::SQ, VM::M1, "Billing Supplies and Devices Sequence" },
{ 0x0070, 0x0314, 0, VR::SQ, VM::M1, "Used Fiducials Sequence" },
{ 0x0072, 0x0316, 0, VR::CS, VM::M1, "Image Box Large Scroll Type" },
{ 0x0072, 0x0706, 0, VR::CS, VM::M1, "Show Grayscale Inverted" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0874[] = {
{ 0x0018, 0x9526, 0, VR::LO, VM::M1, "Application Manufacturer" },
{ 0x0072, 0x0705, 0, VR::SQ, VM::M1, "Pseudo-Color Palette Instance Reference Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0875[] = {
{ 0x0018, 0x9527, 0, VR::CS, VM::M1, "Algorithm Type" },
{ 0x0072, 0x0314, 0, VR::US, VM::M1, "Image Box Small Scroll Amount" },
{ 0x0072, 0x0704, 0, VR::CS, VM::M1, "Pseudo-Color Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0876[] = {
{ 0x0020, 0x9518, 0, VR::US, VM::M1TN, "Acquisition Index" },
{ 0x0040, 0x0321, 0, VR::SQ, VM::M1, "Film Consumption Sequence" },
{ 0x0070, 0x0311, 0, VR::SQ, VM::M1, "Fiducial Identifier Code Sequence" },
{ 0x300A, 0x03A8, 0, VR::SQ, VM::M1, "Ion Control Point Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0877[] = {
{ 0x0008, 0x9121, 0, VR::SQ, VM::M1, "Referenced Raw Data Sequence" },
{ 0x0024, 0x0344, 0, VR::SQ, VM::M1, "Index Probability Sequence" },
{ 0x0040, 0x0320, 0, VR::SQ, VM::M1, "Billing Procedure Step Sequence" },
{ 0x0070, 0x0310, 0, VR::SH, VM::M1, "Fiducial Identifier" },
{ 0x0072, 0x0312, 0, VR::CS, VM::M1, "Image Box Small Scroll Type" },
{ 0x0072, 0x0702, 0, VR::CS, VM::M1, "VOI Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0878[] = {
{ 0x0022, 0x1300, 0, VR::SQ, VM::M1, "Intraocular Lens Calculations Right Eye Sequence" },
{ 0x300A, 0x03AA, 0, VR::SQ, VM::M1, "Ion Wedge Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0879[] = {
{ 0x0008, 0x9123, 0, VR::UI, VM::M1, "Creator-Version UID" },
{ 0x0070, 0x0312, 0, VR::FD, VM::M1, "Contour Uncertainty Radius" },
{ 0x0072, 0x0310, 0, VR::CS, VM::M1, "Image Box Scroll Direction" },
{ 0x0072, 0x0700, 0, VR::CS, VM::M2, "Display Set Patient Orientation" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0880[] = {
{ 0x0070, 0x030D, 0, VR::SQ, VM::M1, "Registration Type Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0881[] = {
{ 0x0070, 0x030C, 0, VR::CS, VM::M1, "Frame of Reference Transformation Matrix Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0882[] = {
{ 0x0020, 0x9116, 0, VR::SQ, VM::M1, "Plane Orientation Sequence" },
{ 0x0070, 0x030F, 0, VR::ST, VM::M1, "Fiducial Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0883[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0884[] = {
{ 0x0018, 0x9538, 0, VR::SQ, VM::M1, "Per Projection Acquisition Sequence" },
{ 0x0070, 0x0309, 0, VR::SQ, VM::M1, "Matrix Registration Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0885[] = {
{ 0x0020, 0x9111, 0, VR::SQ, VM::M1, "Frame Content Sequence" },
{ 0x0028, 0x0740, 1, VR::US, VM::M1, "Code Number Format" },
{ 0x0040, 0xA992, 1, VR::ST, VM::M1, "Uniform Resource Locator (Trial)" },
{ 0x0070, 0x0308, 0, VR::SQ, VM::M1, "Registration Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0886[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0887[] = {
{ 0x0020, 0x9113, 0, VR::SQ, VM::M1, "Plane Position Sequence" },
{ 0x0040, 0x072A, 0, VR::DS, VM::M1, "X Offset in Slide Coordinate System" },
{ 0x0070, 0x030A, 0, VR::SQ, VM::M1, "Matrix Sequence" },
{ 0x0072, 0x0308, 0, VR::US, VM::M1, "Image Box Tile Vertical Dimension" },
{ 0x0072, 0x0718, 0, VR::CS, VM::M1, "Display Set Vertical Justification" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0888[] = {
{ 0x0072, 0x0717, 0, VR::CS, VM::M1, "Display Set Horizontal Justification" },
{ 0x5600, 0x0020, 0, VR::OF, VM::M1, "Spectroscopy Data" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0889[] = {
{ 0x0018, 0x9125, 0, VR::SQ, VM::M1, "MR FOV/Geometry Sequence" },
{ 0x0028, 0x9505, 0, VR::SQ, VM::M1, "Multi-frame Presentation Sequence" },
{ 0x0072, 0x0306, 0, VR::US, VM::M1, "Image Box Tile Horizontal Dimension" },
{ 0x0072, 0x0716, 0, VR::CS, VM::M1, "Show Acquisition Techniques Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0890[] = {
{ 0x0018, 0x9126, 0, VR::SQ, VM::M1, "Volume Localization Sequence" },
{ 0x0028, 0x9506, 0, VR::US, VM::M2T2N, "Pixel Shift Frame Range" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0891[] = {
{ 0x0018, 0x9127, 0, VR::UL, VM::M1, "Spectroscopy Acquisition Data Columns" },
{ 0x0028, 0x9507, 0, VR::US, VM::M2T2N, "LUT Frame Range" },
{ 0x0070, 0x0306, 0, VR::CS, VM::M1, "Shape Type" },
{ 0x0072, 0x0304, 0, VR::CS, VM::M1, "Image Box Layout Type" },
{ 0x0072, 0x0714, 0, VR::CS, VM::M1, "Show Patient Demographics Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0892[] = {
{ 0x0018, 0x9530, 0, VR::SQ, VM::M1, "X-Ray 3D Reconstruction Sequence" },
{ 0x0028, 0x9110, 0, VR::SQ, VM::M1, "Pixel Measures Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0893[] = {
{ 0x0018, 0x9531, 0, VR::LO, VM::M1, "Reconstruction Description" },
{ 0x0028, 0x9501, 0, VR::SQ, VM::M1, "Pixel Shift Sequence" },
{ 0x0040, 0x0330, 1, VR::SQ, VM::M1, "Referenced Procedure Step Sequence" },
{ 0x0072, 0x0302, 0, VR::US, VM::M1, "Image Box Number" },
{ 0x0072, 0x0712, 0, VR::CS, VM::M1, "Show Graphic Annotation Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0894[] = {
{ 0x0022, 0x1310, 0, VR::SQ, VM::M1, "Intraocular Lens Calculations Left Eye Sequence" },
{ 0x0028, 0x9502, 0, VR::SQ, VM::M1, "Region Pixel Shift Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0895[] = {
{ 0x0028, 0x9503, 0, VR::SS, VM::M2T2N, "Vertices of the Region" },
{ 0x0072, 0x0300, 0, VR::SQ, VM::M1, "Image Boxes Sequence" },
{ 0x0072, 0x0710, 0, VR::CS, VM::M1, "Show Image True Size Flag" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0896[] = {
{ 0x0068, 0x6260, 0, VR::SQ, VM::M1, "Information From Manufacturer Sequence" },
{ 0x6008, 0x0200, 1, VR::US, VM::M1, "Overlay Location 5" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0897[] = {
{ 0x300A, 0x0346, 0, VR::SH, VM::M1, "Range Modulator ID" },
{ 0xFFFE, 0xE000, 0, VR::XX, VM::M0, "Item" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0898[] = {
{ 0x600A, 0x0200, 1, VR::US, VM::M1, "Overlay Location 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0899[] = {
{ 0x300A, 0x0344, 0, VR::IS, VM::M1, "Range Modulator Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0900[] = {
{ 0x600C, 0x0200, 1, VR::US, VM::M1, "Overlay Location 7" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0901[] = {
{ 0x0068, 0x6265, 0, VR::SQ, VM::M1, "Notification From Manufacturer Sequence" },
{ 0x300A, 0x0342, 0, VR::SQ, VM::M1, "Range Modulator Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0902[] = {
{ 0x600E, 0x0200, 1, VR::US, VM::M1, "Overlay Location 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0903[] = {
{ 0x300A, 0x0340, 0, VR::IS, VM::M1, "Number of Range Modulators" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0904[] = {
{ 0x6000, 0x0200, 1, VR::US, VM::M1, "Overlay Location" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0905[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0906[] = {
{ 0x6002, 0x0200, 1, VR::US, VM::M1, "Overlay Location 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0907[] = {
{ 0x300A, 0x034C, 0, VR::SH, VM::M1, "Beam Current Modulation ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0908[] = {
{ 0x6004, 0x0200, 1, VR::US, VM::M1, "Overlay Location 3" },
{ 0xFFFE, 0xE00D, 0, VR::XX, VM::M0, "Item Delimitation Item" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0909[] = {
{ 0x300A, 0x034A, 0, VR::LO, VM::M1, "Range Modulator Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0910[] = {
{ 0x6006, 0x0200, 1, VR::US, VM::M1, "Overlay Location 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0911[] = {
{ 0x300A, 0x0348, 0, VR::CS, VM::M1, "Range Modulator Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0912[] = {
{ 0x0068, 0x6270, 0, VR::DT, VM::M1, "Information Issue DateTime" },
{ 0x6018, 0x0200, 1, VR::US, VM::M1, "Overlay Location 13" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0913[] = {
{ 0x300A, 0x0356, 0, VR::FL, VM::M1, "Fixation Light Azimuthal Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0914[] = {
{ 0x601A, 0x0200, 1, VR::US, VM::M1, "Overlay Location 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0915[] = {
{ 0x300A, 0x0354, 0, VR::LO, VM::M1, "Patient Support Accessory Code" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0916[] = {
{ 0x601C, 0x0200, 1, VR::US, VM::M1, "Overlay Location 15" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0917[] = {
{ 0x300A, 0x0352, 0, VR::SH, VM::M1, "Patient Support ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0918[] = {
{ 0x601E, 0x0200, 1, VR::US, VM::M1, "Overlay Location 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0919[] = {
{ 0x300A, 0x0350, 0, VR::CS, VM::M1, "Patient Support Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0920[] = {
{ 0x6010, 0x0200, 1, VR::US, VM::M1, "Overlay Location 9" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0921[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0922[] = {
{ 0x6012, 0x0200, 1, VR::US, VM::M1, "Overlay Location 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0923[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0924[] = {
{ 0x6014, 0x0200, 1, VR::US, VM::M1, "Overlay Location 11" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0925[] = {
{ 0x300A, 0x035A, 0, VR::FL, VM::M1, "Meterset Rate" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0926[] = {
{ 0x6016, 0x0200, 1, VR::US, VM::M1, "Overlay Location 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0927[] = {
{ 0x300A, 0x0358, 0, VR::FL, VM::M1, "Fixation Light Polar Angle" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0928[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0929[] = {
{ 0x300A, 0x0366, 0, VR::FL, VM::M1, "Range Shifter Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0930[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0931[] = {
{ 0x0040, 0xA167, 1, VR::SQ, VM::M1, "Observation Category Code Sequence (Trial)" },
{ 0x300A, 0x0364, 0, VR::FL, VM::M1, "Isocenter to Range Shifter Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0932[] = {
{ 0x0040, 0xA160, 0, VR::UT, VM::M1, "Text Value" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0933[] = {
{ 0x300A, 0x0362, 0, VR::LO, VM::M1, "Range Shifter Setting" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0934[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0935[] = {
{ 0x300A, 0x0360, 0, VR::SQ, VM::M1, "Range Shifter Settings Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0936[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0937[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0938[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0939[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0940[] = {
{ 0x0040, 0xA168, 0, VR::SQ, VM::M1, "Concept Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0941[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0942[] = {
{ 0x0040, 0xA16A, 1, VR::ST, VM::M1, "Bibliographic Citation (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0943[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0944[] = {
{ 0x0040, 0xA174, 1, VR::CS, VM::M1, "Referenced Object Observation Class (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0945[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0946[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0947[] = {
{ 0x300A, 0x0374, 0, VR::FL, VM::M1, "Isocenter to Lateral Spreading Device Distance" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0948[] = {
{ 0x0040, 0xA170, 0, VR::SQ, VM::M1, "Purpose of Reference Code Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0949[] = {
{ 0x0040, 0xA171, 1, VR::UI, VM::M1, "Observation UID (Trial)" },
{ 0x300A, 0x0372, 0, VR::LO, VM::M1, "Lateral Spreading Device Setting" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0950[] = {
{ 0x0040, 0xA172, 1, VR::UI, VM::M1, "Referenced Observation UID (Trial)" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0951[] = {
{ 0x0040, 0xA173, 1, VR::CS, VM::M1, "Referenced Observation Class (Trial)" },
{ 0x300A, 0x0370, 0, VR::SQ, VM::M1, "Lateral Spreading Device Settings Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0952[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0953[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0954[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0955[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0956[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0957[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0958[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0959[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0960[] = {
{ 0x0040, 0xE001, 0, VR::ST, VM::M1, "HL7 Instance Identifier" },
{ 0x0068, 0x6221, 0, VR::LO, VM::M1, "Implant Template Version" },
{ 0x300A, 0x0306, 0, VR::SS, VM::M1, "Radiation Charge State" },
{ 0x5008, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 5" },
{ 0x5018, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 13" },
{ 0x6008, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 5" },
{ 0x600A, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0961[] = {
{ 0x6008, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 5" },
{ 0x600A, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0962[] = {
{ 0x0068, 0x6223, 0, VR::CS, VM::M1, "Implant Type" },
{ 0x300A, 0x0304, 0, VR::IS, VM::M1, "Radiation Atomic Number" },
{ 0x500A, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 6" },
{ 0x501A, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 14" },
{ 0x6008, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 5" },
{ 0x600A, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0963[] = {
{ 0x0068, 0x6222, 0, VR::SQ, VM::M1, "Replaced Implant Template Sequence" },
{ 0x6008, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 5" },
{ 0x600A, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 6" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0964[] = {
{ 0x0068, 0x6225, 0, VR::SQ, VM::M1, "Original Implant Template Sequence" },
{ 0x300A, 0x0302, 0, VR::IS, VM::M1, "Radiation Mass Number" },
{ 0x500C, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 7" },
{ 0x501C, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 15" },
{ 0x600C, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 7" },
{ 0x600E, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0965[] = {
{ 0x0040, 0xE004, 0, VR::DT, VM::M1, "HL7 Document Effective Time" },
{ 0x0068, 0x6224, 0, VR::SQ, VM::M1, "Derivation Implant Template Sequence" },
{ 0x600C, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 7" },
{ 0x600E, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0966[] = {
{ 0x0018, 0x9198, 0, VR::CS, VM::M1, "First Order Phase Correction" },
{ 0x500E, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 8" },
{ 0x501E, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 16" },
{ 0x600C, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 7" },
{ 0x600E, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0967[] = {
{ 0x0018, 0x9199, 0, VR::CS, VM::M1, "Water Referenced Phase Correction" },
{ 0x0040, 0xE006, 0, VR::SQ, VM::M1, "HL7 Document Type Code Sequence" },
{ 0x0068, 0x6226, 0, VR::DT, VM::M1, "Effective DateTime" },
{ 0x600C, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 7" },
{ 0x600E, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 8" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0968[] = {
{ 0x0018, 0x9196, 1, VR::FD, VM::M1, "Chemical Shift Maximum Integration Limit in Hz" },
{ 0x5000, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group" },
{ 0x5010, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 9" },
{ 0x6000, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray" },
{ 0x6002, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0969[] = {
{ 0x0018, 0x9197, 0, VR::SQ, VM::M1, "MR Velocity Encoding Sequence" },
{ 0x0040, 0xE008, 0, VR::SQ, VM::M1, "Document Class Code Sequence" },
{ 0x300A, 0x030F, 0, VR::SH, VM::M1, "Snout ID" },
{ 0x6000, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red" },
{ 0x6002, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0970[] = {
{ 0x300A, 0x030C, 0, VR::SQ, VM::M1, "Snout Sequence" },
{ 0x5002, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 2" },
{ 0x5012, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 10" },
{ 0x6000, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green" },
{ 0x6002, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0971[] = {
{ 0x0018, 0x9195, 1, VR::FD, VM::M1, "Chemical Shift Minimum Integration Limit in Hz" },
{ 0x300A, 0x030D, 0, VR::FL, VM::M1, "Snout Position" },
{ 0x6000, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue" },
{ 0x6002, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 2" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0972[] = {
{ 0x300A, 0x030A, 0, VR::FL, VM::M2, "Virtual Source-Axis Distances" },
{ 0x5004, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 3" },
{ 0x5014, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 11" },
{ 0x6004, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 3" },
{ 0x6006, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0973[] = {
{ 0x6004, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 3" },
{ 0x6006, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0974[] = {
{ 0x300A, 0x0308, 0, VR::CS, VM::M1, "Scan Mode" },
{ 0x5006, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 4" },
{ 0x5016, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 12" },
{ 0x6004, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 3" },
{ 0x6006, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0975[] = {
{ 0x6004, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 3" },
{ 0x6006, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 4" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0976[] = {
{ 0x0040, 0xE011, 0, VR::UI, VM::M1, "Retrieve Location UID" },
{ 0x300A, 0x0316, 0, VR::IS, VM::M1, "Range Shifter Number" },
{ 0x5008, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 5" },
{ 0x5018, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 13" },
{ 0x6018, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 13" },
{ 0x601A, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0977[] = {
{ 0x0040, 0xA504, 0, VR::SQ, VM::M1, "Content Template Sequence" },
{ 0x0040, 0xE010, 0, VR::UT, VM::M1, "Retrieve URI" },
{ 0x0068, 0x6230, 0, VR::SQ, VM::M1, "Implant Target Anatomy Sequence" },
{ 0x0068, 0x6620, 0, VR::FD, VM::M3, "3D Plane Normal" },
{ 0x6018, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 13" },
{ 0x601A, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0978[] = {
{ 0x300A, 0x0314, 0, VR::SQ, VM::M1, "Range Shifter Sequence" },
{ 0x500A, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 6" },
{ 0x501A, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 14" },
{ 0x6018, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 13" },
{ 0x601A, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0979[] = {
{ 0x6018, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 13" },
{ 0x601A, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 14" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0980[] = {
{ 0x300A, 0x0312, 0, VR::IS, VM::M1, "Number of Range Shifters" },
{ 0x500C, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 7" },
{ 0x501C, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 15" },
{ 0x601C, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 15" },
{ 0x601E, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0981[] = {
{ 0x0040, 0xA110, 1, VR::DA, VM::M1, "Date of Document or Verbal Transaction (Trial)" },
{ 0x601C, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 15" },
{ 0x601E, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0982[] = {
{ 0x500E, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 8" },
{ 0x501E, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 16" },
{ 0x601C, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 15" },
{ 0x601E, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0983[] = {
{ 0x0040, 0xA112, 1, VR::TM, VM::M1, "Time of Document Creation or Verbal Transaction (Trial)" },
{ 0x601C, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 15" },
{ 0x601E, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 16" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0984[] = {
{ 0x0018, 0x9186, 0, VR::SH, VM::M1, "Respiratory Signal Source ID" },
{ 0x5000, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence" },
{ 0x5010, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 9" },
{ 0x6010, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 9" },
{ 0x6012, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0985[] = {
{ 0x6010, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 9" },
{ 0x6012, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0986[] = {
{ 0x0018, 0x9184, 0, VR::FD, VM::M1, "Tagging Delay" },
{ 0x5002, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 2" },
{ 0x5012, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 10" },
{ 0x6010, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 9" },
{ 0x6012, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0987[] = {
{ 0x0018, 0x9185, 0, VR::ST, VM::M1, "Respiratory Motion Compensation Technique Description" },
{ 0x6010, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 9" },
{ 0x6012, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 10" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0988[] = {
{ 0x0018, 0x9182, 0, VR::FD, VM::M1, "Gradient Output" },
{ 0x5004, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 3" },
{ 0x5014, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 11" },
{ 0x6014, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 11" },
{ 0x6016, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0989[] = {
{ 0x0018, 0x9183, 0, VR::CS, VM::M1, "Flow Compensation Direction" },
{ 0x6014, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 11" },
{ 0x6016, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0990[] = {
{ 0x0018, 0x9180, 0, VR::CS, VM::M1, "Gradient Output Type" },
{ 0x300A, 0x0318, 0, VR::SH, VM::M1, "Range Shifter ID" },
{ 0x5006, 0x2600, 1, VR::SQ, VM::M1, "Curve Referenced Overlay Sequence 4" },
{ 0x5016, 0x2610, 1, VR::US, VM::M1, "Curve Referenced Overlay Group 12" },
{ 0x6014, 0x1202, 1, VR::US, VM::M1TN, "Overlays - Green 11" },
{ 0x6016, 0x1200, 1, VR::US, VM::M1TN, "Overlays - Gray 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0991[] = {
{ 0x0018, 0x9181, 0, VR::FD, VM::M1, "Specific Absorption Rate Value" },
{ 0x6014, 0x1203, 1, VR::US, VM::M1TN, "Overlays - Blue 11" },
{ 0x6016, 0x1201, 1, VR::US, VM::M1TN, "Overlays - Red 12" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0992[] = {
{ 0x0040, 0xA125, 1, VR::CS, VM::M2, "Report Status ID (Trial)" },
{ 0x0040, 0xE021, 0, VR::SQ, VM::M1, "DICOM Retrieval Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0993[] = {
{ 0x0040, 0xA124, 0, VR::UI, VM::M1, "UID" },
{ 0x0040, 0xE020, 0, VR::CS, VM::M1, "Type of Instances" },
{ 0x0068, 0x6610, 0, VR::FD, VM::M3, "3D Plane Origin" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0994[] = {
{ 0x0040, 0xE023, 0, VR::SQ, VM::M1, "WADO Retrieval Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0995[] = {
{ 0x0040, 0xE022, 0, VR::SQ, VM::M1, "DICOM Media Retrieval Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0996[] = {
{ 0x0040, 0xA121, 0, VR::DA, VM::M1, "Date" },
{ 0x300A, 0x0322, 0, VR::LO, VM::M1, "Range Shifter Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0997[] = {
{ 0x0040, 0xA120, 0, VR::DT, VM::M1, "DateTime" },
{ 0x0040, 0xE024, 0, VR::SQ, VM::M1, "XDS Retrieval Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0998[] = {
{ 0x0040, 0xA123, 0, VR::PN, VM::M1, "Person Name" },
{ 0x300A, 0x0320, 0, VR::CS, VM::M1, "Range Shifter Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow0999[] = {
{ 0x0040, 0xA122, 0, VR::TM, VM::M1, "Time" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1000[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1001[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1002[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1003[] = {
{ 0x2010, 0x0376, 0, VR::DS, VM::M2, "Printer Pixel Spacing" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1004[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1005[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1006[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1007[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1008[] = {
{ 0x0040, 0xA525, 0, VR::SQ, VM::M1, "Identical Documents Sequence" },
{ 0x0040, 0xE031, 0, VR::UI, VM::M1, "Home Community ID" },
{ 0x300A, 0x0336, 0, VR::SH, VM::M1, "Lateral Spreading Device ID" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1009[] = {
{ 0x0040, 0xE030, 0, VR::UI, VM::M1, "Repository Unique ID" },
{ 0x0068, 0x6210, 0, VR::LO, VM::M1, "Implant Size" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1010[] = {
{ 0x300A, 0x0334, 0, VR::IS, VM::M1, "Lateral Spreading Device Number" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1011[] = {
{ 0x0040, 0xA136, 0, VR::US, VM::M1TN, "Referenced Frame Numbers" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1012[] = {
{ 0x300A, 0x0332, 0, VR::SQ, VM::M1, "Lateral Spreading Device Sequence" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1013[] = {
{ 0x0040, 0xA130, 0, VR::CS, VM::M1, "Temporal Range Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1014[] = {
{ 0x300A, 0x0330, 0, VR::IS, VM::M1, "Number of Lateral Spreading Devices" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1015[] = {
{ 0x0040, 0xA132, 0, VR::UL, VM::M1TN, "Referenced Sample Positions" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1016[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1017[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1018[] = {
{ 0x300A, 0x033C, 0, VR::FL, VM::M1, "Lateral Spreading Device Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1019[] = {
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1020[] = {
{ 0x300A, 0x033A, 0, VR::LO, VM::M1, "Lateral Spreading Device Description" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1021[] = {
{ 0x0040, 0xA138, 0, VR::DS, VM::M1TN, "Referenced Time Offsets" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1022[] = {
{ 0x300A, 0x0338, 0, VR::CS, VM::M1, "Lateral Spreading Device Type" },
{ 0, 0, 0, 0, 0, NULL }
};
DictEntry DictRow1023[] = {
{ 0x0040, 0xA13A, 0, VR::DT, VM::M1TN, "Referenced DateTime" },
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
DictRow0532,
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
DictRow0563,
DictRow0564,
DictRow0565,
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
DictRow0597,
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
DictRow0613,
DictRow0614,
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
DictRow0668,
DictRow0669,
DictRow0670,
DictRow0671,
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
DictRow0682,
DictRow0683,
DictRow0684,
DictRow0685,
DictRow0686,
DictRow0687,
DictRow0688,
DictRow0689,
DictRow0690,
DictRow0691,
DictRow0692,
DictRow0693,
DictRow0694,
DictRow0695,
DictRow0696,
DictRow0697,
DictRow0698,
DictRow0699,
DictRow0700,
DictRow0701,
DictRow0702,
DictRow0703,
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
DictRow0759,
DictRow0760,
DictRow0761,
DictRow0762,
DictRow0763,
DictRow0764,
DictRow0765,
DictRow0766,
DictRow0767,
DictRow0768,
DictRow0769,
DictRow0770,
DictRow0771,
DictRow0772,
DictRow0773,
DictRow0774,
DictRow0775,
DictRow0776,
DictRow0777,
DictRow0778,
DictRow0779,
DictRow0780,
DictRow0781,
DictRow0782,
DictRow0783,
DictRow0784,
DictRow0785,
DictRow0786,
DictRow0787,
DictRow0788,
DictRow0789,
DictRow0790,
DictRow0791,
DictRow0792,
DictRow0793,
DictRow0794,
DictRow0795,
DictRow0796,
DictRow0797,
DictRow0798,
DictRow0799,
DictRow0800,
DictRow0801,
DictRow0802,
DictRow0803,
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
DictRow0828,
DictRow0829,
DictRow0830,
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
DictRow0855,
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
DictRow0883,
DictRow0884,
DictRow0885,
DictRow0886,
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
DictRow0905,
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
DictRow0921,
DictRow0922,
DictRow0923,
DictRow0924,
DictRow0925,
DictRow0926,
DictRow0927,
DictRow0928,
DictRow0929,
DictRow0930,
DictRow0931,
DictRow0932,
DictRow0933,
DictRow0934,
DictRow0935,
DictRow0936,
DictRow0937,
DictRow0938,
DictRow0939,
DictRow0940,
DictRow0941,
DictRow0942,
DictRow0943,
DictRow0944,
DictRow0945,
DictRow0946,
DictRow0947,
DictRow0948,
DictRow0949,
DictRow0950,
DictRow0951,
DictRow0952,
DictRow0953,
DictRow0954,
DictRow0955,
DictRow0956,
DictRow0957,
DictRow0958,
DictRow0959,
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
DictRow1000,
DictRow1001,
DictRow1002,
DictRow1003,
DictRow1004,
DictRow1005,
DictRow1006,
DictRow1007,
DictRow1008,
DictRow1009,
DictRow1010,
DictRow1011,
DictRow1012,
DictRow1013,
DictRow1014,
DictRow1015,
DictRow1016,
DictRow1017,
DictRow1018,
DictRow1019,
DictRow1020,
DictRow1021,
DictRow1022,
DictRow1023,
};
