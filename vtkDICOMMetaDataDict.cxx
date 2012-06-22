#include "vtkDICOMMetaData.h"

typedef vtkDICOMVR VR;
typedef vtkDICOMVM VM;

namespace {

vtkDICOMMetaData::DictEntry DictRow0000[] = {
{ 0x0008, 0x0008, VR::CS, VM::M2TN, "Image Type" },
{ 0x0008, 0x1049, VR::SQ, VM::M1, "Physician(s) of Record Identification Sequence" },
{ 0x0010, 0x0010, VR::PN, VM::M1, "Patient's Name" },
{ 0x0018, 0x9251, VR::SQ, VM::M1, "MR Arterial Spin Labeling Sequence" },
{ 0x0020, 0x0020, VR::CS, VM::M2, "Patient Orientation" },
{ 0x0022, 0x0022, VR::SQ, VM::M1, "Right Image Sequence" },
{ 0x0024, 0x0024, VR::SQ, VM::M1, "Background Illumination Color Code Sequence" },
{ 0x0028, 0x0808, VR::AT, VM::M1TN, "Image Data Location" },
{ 0x0032, 0x0032, VR::DA, VM::M1, "Study Verified Date" },
{ 0x0040, 0x1001, VR::SH, VM::M1, "Requested Procedure ID" },
{ 0x0046, 0x0046, VR::FD, VM::M1, "Corneal Size" },
{ 0x0072, 0x0072, VR::DS, VM::M1TN, "Selector DS Value" },
{ 0x0400, 0x0010, VR::UI, VM::M1, "MAC Calculation Transfer Syntax UID" },
{ 0x2020, 0x00A2, VR::CS, VM::M1, "Decimate/Crop Result" },
{ 0x4000, 0x4000, VR::LT, VM::M1, "Text Comments" },
{ 0x4008, 0x010C, VR::PN, VM::M1, "Interpretation Author" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0001[] = {
{ 0x0008, 0x1048, VR::PN, VM::M1TN, "Physician(s) of Record" },
{ 0x0010, 0x1050, VR::LO, VM::M1TN, "Insurance Plan Identification" },
{ 0x0018, 0x9250, VR::CS, VM::M1, "Arterial Spin Labeling Contrast" },
{ 0x0024, 0x0025, VR::FL, VM::M1, "Stimulus Area" },
{ 0x0032, 0x0033, VR::TM, VM::M1, "Study Verified Time" },
{ 0x0074, 0x1034, VR::CS, VM::M1, "Double Exposure Flag" },
{ 0x0400, 0x0401, VR::SQ, VM::M1, "Digital Signature Purpose Code Sequence" },
{ 0x3006, 0x00C4, VR::CS, VM::M1, "Frame of Reference Transformation Type" },
{ 0x300A, 0x00C8, VR::IS, VM::M1, "Reference Image Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0002[] = {
{ 0x0012, 0x0010, VR::LO, VM::M1, "Clinical Trial Sponsor Name" },
{ 0x0018, 0x9253, VR::US, VM::M1, "ASL Slab Number" },
{ 0x0020, 0x0022, VR::IS, VM::M1, "Overlay Number" },
{ 0x0022, 0x0020, VR::SQ, VM::M1, "Stereo Pairs Sequence" },
{ 0x0040, 0x1003, VR::SH, VM::M1, "Requested Procedure Priority" },
{ 0x0046, 0x0044, VR::FD, VM::M1, "Pupil Size" },
{ 0x0072, 0x0070, VR::UT, VM::M1, "Selector UT Value" },
{ 0x0400, 0x0402, VR::SQ, VM::M1, "Referenced Digital Signature Sequence" },
{ 0x2020, 0x00A0, VR::CS, VM::M1, "Requested Image Size Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0003[] = {
{ 0x0018, 0x9252, VR::LO, VM::M1, "ASL Technique Description" },
{ 0x0022, 0x0021, VR::SQ, VM::M1, "Left Image Sequence" },
{ 0x0032, 0x1070, VR::LO, VM::M1, "Requested Contrast Agent" },
{ 0x0040, 0x1002, VR::LO, VM::M1, "Reason for the Requested Procedure" },
{ 0x0074, 0x1036, VR::CS, VM::M1, "Double Exposure Ordering" },
{ 0x0400, 0x0403, VR::SQ, VM::M1, "Referenced SOP Instance MAC Sequence" },
{ 0x3006, 0x00C6, VR::DS, VM::M16, "Frame of Reference Transformation Matrix" },
{ 0x300A, 0x00CA, VR::SQ, VM::M1, "Planned Verification Image Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0004[] = {
{ 0x0018, 0x9255, VR::FD, VM::M3, "ASL Slab Orientation" },
{ 0x0020, 0x0024, VR::IS, VM::M1, "Curve Number" },
{ 0x0024, 0x0020, VR::FL, VM::M1, "Background Luminance" },
{ 0x0040, 0x1005, VR::LO, VM::M1, "Requested Procedure Location" },
{ 0x0046, 0x0042, VR::FD, VM::M1, "Channel Width" },
{ 0x0054, 0x0050, VR::US, VM::M1TN, "Rotation Vector" },
{ 0x0054, 0x1401, VR::CS, VM::M1, "Dead Time Correction Flag" },
{ 0x0072, 0x0076, VR::FL, VM::M1TN, "Selector FL Value" },
{ 0x0400, 0x0404, VR::OB, VM::M1, "MAC" },
{ 0x4008, 0x0108, VR::DA, VM::M1, "Interpretation Transcription Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0005[] = {
{ 0x0018, 0x9254, VR::FD, VM::M1, "ASL Slab Thickness" },
{ 0x0022, 0x1066, VR::LO, VM::M1, "Vitreous Status Description" },
{ 0x0024, 0x0021, VR::SQ, VM::M1, "Stimulus Color Code Sequence" },
{ 0x0040, 0x1004, VR::LO, VM::M1, "Patient Transport Arrangements" },
{ 0x0054, 0x0051, VR::US, VM::M1, "Number of Rotations" },
{ 0x0054, 0x1400, VR::CS, VM::M1TN, "Counts Included" },
{ 0x0074, 0x1030, VR::SQ, VM::M1, "Delivery Verification Image Sequence" },
{ 0x0400, 0x0015, VR::CS, VM::M1, "MAC Algorithm" },
{ 0x3006, 0x00C0, VR::SQ, VM::M1, "Frame of Reference Relationship Sequence" },
{ 0x300A, 0x00CC, VR::LO, VM::M1TN, "Imaging Device-Specific Acquisition Parameters" },
{ 0x4008, 0x0109, VR::TM, VM::M1, "Interpretation Transcription Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0006[] = {
{ 0x0018, 0x9257, VR::CS, VM::M1, "ASL Context" },
{ 0x0020, 0x0026, VR::IS, VM::M1, "LUT Number" },
{ 0x0022, 0x1065, VR::LO, VM::M1, "Lens Status Description" },
{ 0x0032, 0x0034, VR::DA, VM::M1, "Study Read Date" },
{ 0x0040, 0x1007, VR::SH, VM::M1, "Filler Order Number / Procedure" },
{ 0x0046, 0x0040, VR::FD, VM::M1, "Optical Transmittance" },
{ 0x0054, 0x0052, VR::SQ, VM::M1, "Rotation Information Sequence" },
{ 0x0072, 0x0074, VR::FD, VM::M1TN, "Selector FD Value" },
{ 0x0076, 0x0070, VR::US, VM::M1, "Component 1 Referenced ID" },
{ 0x4008, 0x010A, VR::PN, VM::M1, "Interpretation Transcriber" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0007[] = {
{ 0x0018, 0x9256, VR::FD, VM::M3, "ASL Mid Slab Position" },
{ 0x0032, 0x0035, VR::TM, VM::M1, "Study Read Time" },
{ 0x0040, 0x1006, VR::SH, VM::M1, "Placer Order Number / Procedure" },
{ 0x0054, 0x0053, VR::US, VM::M1, "Number of Frames in Rotation" },
{ 0x0074, 0x1032, VR::CS, VM::M1, "Verification Image Timing" },
{ 0x3006, 0x00C2, VR::UI, VM::M1, "Related Frame of Reference UID" },
{ 0x300A, 0x00CE, VR::CS, VM::M1, "Treatment Delivery Type" },
{ 0x4008, 0x010B, VR::ST, VM::M1, "Interpretation Text" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0008[] = {
{ 0x0018, 0x0010, VR::LO, VM::M1, "Contrast/Bolus Agent" },
{ 0x0018, 0x9259, VR::CS, VM::M1, "ASL Crusher Flag" },
{ 0x0028, 0x0800, VR::CS, VM::M1TN, "Code Label" },
{ 0x0038, 0x0030, VR::DA, VM::M1, "Discharge Date" },
{ 0x0040, 0x1009, VR::SH, VM::M1, "Reporting Priority" },
{ 0x0072, 0x007A, VR::US, VM::M1TN, "Selector US Value" },
{ 0x0078, 0x0070, VR::SQ, VM::M1, "Implant Template Group Member Matching 2D Coordinates Sequence" },
{ 0x4008, 0x4000, VR::ST, VM::M1, "Results Comments" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0009[] = {
{ 0x0008, 0x0001, VR::UL, VM::M1, "Length to End" },
{ 0x0008, 0x1040, VR::LO, VM::M1, "Institutional Department Name" },
{ 0x0018, 0x1050, VR::DS, VM::M1, "Spatial Resolution" },
{ 0x0018, 0x9258, VR::UL, VM::M1, "ASL Pulse Train Duration" },
{ 0x0040, 0x1008, VR::LO, VM::M1, "Confidentiality Code" },
{ 0x300A, 0x00C0, VR::IS, VM::M1, "Beam Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0010[] = {
{ 0x0018, 0x0012, VR::SQ, VM::M1, "Contrast/Bolus Agent Sequence" },
{ 0x0018, 0x925B, VR::LO, VM::M1, "ASL Crusher Description" },
{ 0x0028, 0x0802, VR::US, VM::M1, "Number of Tables" },
{ 0x0038, 0x0032, VR::TM, VM::M1, "Discharge Time" },
{ 0x0072, 0x0078, VR::UL, VM::M1TN, "Selector UL Value" },
{ 0x300A, 0x00C3, VR::ST, VM::M1, "Beam Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0011[] = {
{ 0x0018, 0x925A, VR::FD, VM::M1, "ASL Crusher Flow" },
{ 0x0028, 0x0803, VR::AT, VM::M1TN, "Code Table Location" },
{ 0x0040, 0x100A, VR::SQ, VM::M1, "Reason for Requested Procedure Code Sequence" },
{ 0x3008, 0x00C0, VR::SQ, VM::M1, "Recorded Compensator Sequence" },
{ 0x300A, 0x00C2, VR::LO, VM::M1, "Beam Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0012[] = {
{ 0x0018, 0x0014, VR::SQ, VM::M1, "Contrast/Bolus Administration Route Sequence" },
{ 0x0018, 0x925D, VR::SQ, VM::M1, "ASL Bolus Cut-off Timing Sequence" },
{ 0x0024, 0x0028, VR::FL, VM::M1, "Stimulus Presentation Time" },
{ 0x0028, 0x0804, VR::US, VM::M1, "Bits For Code Word" },
{ 0x0072, 0x007E, VR::SS, VM::M1TN, "Selector SS Value" },
{ 0x4008, 0x0100, VR::DA, VM::M1, "Interpretation Recorded Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0013[] = {
{ 0x0008, 0x0005, VR::CS, VM::M1TN, "Specific Character Set" },
{ 0x0018, 0x0015, VR::CS, VM::M1, "Body Part Examined" },
{ 0x0018, 0x925C, VR::CS, VM::M1, "ASL Bolus Cut-off Flag" },
{ 0x0074, 0x1038, VR::DS, VM::M1, "Double Exposure Meterset (Trial)" },
{ 0x3006, 0x00C8, VR::LO, VM::M1, "Frame of Reference Transformation Comment" },
{ 0x300A, 0x00C4, VR::CS, VM::M1, "Beam Type" },
{ 0x4008, 0x0101, VR::TM, VM::M1, "Interpretation Recorded Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0014[] = {
{ 0x0008, 0x0006, VR::SQ, VM::M1, "Language Code Sequence" },
{ 0x0018, 0x925F, VR::UL, VM::M1, "ASL Bolus Cut-off Delay Time" },
{ 0x0068, 0x65F0, VR::FD, VM::M4, "2D Plane Intersection" },
{ 0x0072, 0x007C, VR::SL, VM::M1TN, "Selector SL Value" },
{ 0x300A, 0x00C7, VR::CS, VM::M1, "High-Dose Technique Type" },
{ 0x4008, 0x0102, VR::PN, VM::M1, "Interpretation Recorder" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0015[] = {
{ 0x0018, 0x925E, VR::LO, VM::M1, "ASL Bolus Cut-off Technique" },
{ 0x0074, 0x103A, VR::DS, VM::M4, "Double Exposure Field Delta (Trial)" },
{ 0x300A, 0x00C6, VR::CS, VM::M1, "Radiation Type" },
{ 0x300C, 0x00C0, VR::IS, VM::M1, "Referenced Wedge Number" },
{ 0x4008, 0x0103, VR::LO, VM::M1, "Reference to Recorded Sound" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0016[] = {
{ 0x0008, 0x0018, VR::UI, VM::M1, "SOP Instance UID" },
{ 0x0018, 0x1049, VR::DS, VM::M1, "Contrast/Bolus Ingredient Concentration" },
{ 0x0018, 0x9241, VR::US, VM::M1, "Gradient Echo Train Length" },
{ 0x0020, 0x0030, VR::DS, VM::M3, "Image Position" },
{ 0x0022, 0x0032, VR::FL, VM::M2T2N, "Reference Coordinates" },
{ 0x0024, 0x0034, VR::SQ, VM::M1, "Visual Field Catch Trial Sequence" },
{ 0x0040, 0x0440, VR::SQ, VM::M1, "Protocol Context Sequence" },
{ 0x0040, 0x1011, VR::SQ, VM::M1, "Intended Recipients of Results Identification Sequence" },
{ 0x0070, 0x0060, VR::SQ, VM::M1, "Graphic Layer Sequence" },
{ 0x0072, 0x0062, VR::CS, VM::M1TN, "Selector CS Value" },
{ 0x300A, 0x00D9, VR::FL, VM::M1, "Isocenter to Wedge Tray Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0017[] = {
{ 0x0010, 0x1040, VR::LO, VM::M1, "Patient's Address" },
{ 0x0018, 0x1048, VR::CS, VM::M1, "Contrast/Bolus Ingredient" },
{ 0x0018, 0x9240, VR::US, VM::M1, "RF Echo Train Length" },
{ 0x0020, 0x1070, VR::IS, VM::M1TN, "Other Study Numbers" },
{ 0x0024, 0x0035, VR::US, VM::M1, "Fixation Checked Quantity" },
{ 0x0040, 0x0441, VR::SQ, VM::M1, "Content Item Modifier Sequence" },
{ 0x0040, 0x1010, VR::PN, VM::M1TN, "Names of Intended Recipients of Results" },
{ 0x0040, 0x1400, VR::LT, VM::M1, "Requested Procedure Comments" },
{ 0x0054, 0x1004, VR::CS, VM::M1, "Reprojection Method" },
{ 0x0074, 0x1024, VR::IS, VM::M1, "Beam Order Index (Trial)" },
{ 0x300A, 0x00D8, VR::DS, VM::M1, "Wedge Orientation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0018[] = {
{ 0x0008, 0x001A, VR::UI, VM::M1TN, "Related General SOP Class UID" },
{ 0x0020, 0x0032, VR::DS, VM::M3, "Image Position (Patient)" },
{ 0x0022, 0x0030, VR::FL, VM::M1, "Axial Length of the Eye" },
{ 0x0024, 0x0036, VR::US, VM::M1, "Patient Not Properly Fixated Quantity" },
{ 0x0070, 0x0062, VR::IS, VM::M1, "Graphic Layer Order" },
{ 0x0072, 0x0060, VR::AT, VM::M1TN, "Selector AT Value" },
{ 0x0074, 0x1027, VR::FD, VM::M1, "Table Top Longitudinal Adjusted Position" },
{ 0x2010, 0x0080, VR::CS, VM::M1, "Smoothing Type" },
{ 0x300A, 0x00DB, VR::FL, VM::M1, "Wedge Thin Edge Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0019[] = {
{ 0x0008, 0x001B, VR::UI, VM::M1, "Original Specialized SOP Class UID" },
{ 0x0022, 0x0031, VR::SQ, VM::M1, "Ophthalmic Frame Location Sequence" },
{ 0x0024, 0x0037, VR::CS, VM::M1, "Presented Visual Stimuli Data Flag" },
{ 0x0032, 0x1060, VR::LO, VM::M1, "Requested Procedure Description" },
{ 0x0040, 0x1012, VR::SQ, VM::M1, "Reason For Performed Procedure Code Sequence" },
{ 0x0054, 0x1006, VR::CS, VM::M1, "SUV Type" },
{ 0x0074, 0x1026, VR::FD, VM::M1, "Table Top Vertical Adjusted Position" },
{ 0x300A, 0x00DA, VR::DS, VM::M1, "Source to Wedge Tray Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0020[] = {
{ 0x0022, 0x0036, VR::FL, VM::M1, "Maximum Depth Distortion" },
{ 0x0046, 0x0052, VR::SQ, VM::M1, "Autorefraction Left Eye Sequence" },
{ 0x0054, 0x1001, VR::CS, VM::M1, "Units" },
{ 0x0072, 0x0066, VR::LO, VM::M1TN, "Selector LO Value" },
{ 0x300A, 0x00DD, VR::ST, VM::M1, "Bolus Description" },
{ 0x4008, 0x0118, VR::SQ, VM::M1, "Results Distribution List Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0021[] = {
{ 0x0014, 0x1040, VR::ST, VM::M1, "Environmental Conditions" },
{ 0x0020, 0x0035, VR::DS, VM::M6, "Image Orientation" },
{ 0x0022, 0x0037, VR::FL, VM::M1, "Along-scan Spatial Resolution" },
{ 0x0054, 0x1000, VR::CS, VM::M2, "Series Type" },
{ 0x0074, 0x1020, VR::SQ, VM::M1, "Beam Task Sequence" },
{ 0x0400, 0x0005, VR::US, VM::M1, "MAC ID Number" },
{ 0x300A, 0x00DC, VR::SH, VM::M1, "Bolus ID" },
{ 0x4008, 0x0119, VR::PN, VM::M1, "Distribution Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0022[] = {
{ 0x0024, 0x0032, VR::SQ, VM::M1, "Fixation Sequence" },
{ 0x0046, 0x0050, VR::SQ, VM::M1, "Autorefraction Right Eye Sequence" },
{ 0x0070, 0x0066, VR::US, VM::M1, "Graphic Layer Recommended Display Grayscale Value" },
{ 0x0072, 0x0064, VR::IS, VM::M1TN, "Selector IS Value" },
{ 0x0076, 0x0060, VR::SQ, VM::M1, "Component Assembly Sequence" },
{ 0x4008, 0x011A, VR::LO, VM::M1, "Distribution Address" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0023[] = {
{ 0x0020, 0x0037, VR::DS, VM::M6, "Image Orientation (Patient)" },
{ 0x0022, 0x0035, VR::FL, VM::M1, "Depth Spatial Resolution" },
{ 0x0024, 0x0033, VR::SQ, VM::M1, "Fixation Monitoring Code Sequence" },
{ 0x0032, 0x1064, VR::SQ, VM::M1, "Requested Procedure Code Sequence" },
{ 0x0054, 0x1002, VR::CS, VM::M1, "Counts Source" },
{ 0x0070, 0x0067, VR::US, VM::M3, "Graphic Layer Recommended Display RGB Value" },
{ 0x0074, 0x1022, VR::CS, VM::M1, "Beam Task Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0024[] = {
{ 0x0008, 0x0010, VR::SH, VM::M1, "Recognition Code" },
{ 0x0018, 0x1041, VR::DS, VM::M1, "Contrast/Bolus Volume" },
{ 0x0028, 0x0030, VR::DS, VM::M2, "Pixel Spacing" },
{ 0x0038, 0x0020, VR::DA, VM::M1, "Admitting Date" },
{ 0x0040, 0x9211, VR::XS, VM::M1, "Real World Value Last Value Mapped" },
{ 0x0070, 0x0068, VR::LO, VM::M1, "Graphic Layer Description" },
{ 0x0072, 0x006A, VR::PN, VM::M1TN, "Selector PN Value" },
{ 0x0074, 0x102D, VR::FD, VM::M1, "Table Top Roll Adjusted Angle" },
{ 0x0078, 0x0060, VR::FD, VM::M9, "3D Implant Template Group Member Matching Axes" },
{ 0x300A, 0x00D1, VR::SQ, VM::M1, "Wedge Sequence" },
{ 0x4008, 0x0114, VR::PN, VM::M1, "Physician Approving Interpretation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0025[] = {
{ 0x0008, 0x1050, VR::PN, VM::M1TN, "Performing Physician's Name" },
{ 0x0018, 0x1040, VR::LO, VM::M1, "Contrast/Bolus Route" },
{ 0x0018, 0x1450, VR::DS, VM::M1, "Column Angulation" },
{ 0x0028, 0x0031, VR::DS, VM::M2, "Zoom Factor" },
{ 0x0038, 0x0021, VR::TM, VM::M1, "Admitting Time" },
{ 0x0040, 0x9210, VR::SH, VM::M1, "LUT Label" },
{ 0x0074, 0x102C, VR::FD, VM::M1, "Table Top Pitch Adjusted Angle" },
{ 0x300A, 0x00D0, VR::IS, VM::M1, "Number of Wedges" },
{ 0x4008, 0x0115, VR::LT, VM::M1, "Interpretation Diagnosis Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0026[] = {
{ 0x0008, 0x0012, VR::DA, VM::M1, "Instance Creation Date" },
{ 0x0018, 0x1043, VR::TM, VM::M1, "Contrast/Bolus Stop Time" },
{ 0x0022, 0x0038, VR::FL, VM::M1, "Maximum Along-scan Distortion" },
{ 0x0028, 0x0032, VR::DS, VM::M2, "Zoom Center" },
{ 0x003A, 0x0020, VR::SH, VM::M1, "Multiplex Group Label" },
{ 0x0072, 0x0068, VR::LT, VM::M1, "Selector LT Value" },
{ 0x300A, 0x00D3, VR::CS, VM::M1, "Wedge Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0027[] = {
{ 0x0008, 0x0013, VR::TM, VM::M1, "Instance Creation Time" },
{ 0x0008, 0x1052, VR::SQ, VM::M1, "Performing Physician Identification Sequence" },
{ 0x0018, 0x1042, VR::TM, VM::M1, "Contrast/Bolus Start Time" },
{ 0x0022, 0x0039, VR::CS, VM::M1, "Ophthalmic Image Orientation" },
{ 0x0040, 0x9212, VR::FD, VM::M1TN, "Real World Value LUT Data" },
{ 0x3008, 0x00D0, VR::SQ, VM::M1, "Recorded Block Sequence" },
{ 0x300A, 0x00D2, VR::IS, VM::M1, "Wedge Number" },
{ 0x4008, 0x0117, VR::SQ, VM::M1, "Interpretation Diagnosis Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0028[] = {
{ 0x0008, 0x0014, VR::UI, VM::M1, "Instance Creator UID" },
{ 0x0018, 0x1045, VR::IS, VM::M1, "Syringe Counts" },
{ 0x0024, 0x0038, VR::US, VM::M1, "Number of Visual Stimuli" },
{ 0x0028, 0x0034, VR::IS, VM::M2, "Pixel Aspect Ratio" },
{ 0x0072, 0x006E, VR::ST, VM::M1, "Selector ST Value" },
{ 0x300A, 0x00D5, VR::IS, VM::M1, "Wedge Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0029[] = {
{ 0x0018, 0x1044, VR::DS, VM::M1, "Contrast/Bolus Total Dose" },
{ 0x0024, 0x0039, VR::CS, VM::M1, "Excessive Fixation Losses Data Flag" },
{ 0x0074, 0x1028, VR::FD, VM::M1, "Table Top Lateral Adjusted Position" },
{ 0x300A, 0x00D4, VR::SH, VM::M1, "Wedge ID" },
{ 0x4008, 0x0111, VR::SQ, VM::M1, "Interpretation Approver Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0030[] = {
{ 0x0008, 0x0016, VR::UI, VM::M1, "SOP Class UID" },
{ 0x0018, 0x1047, VR::DS, VM::M1TN, "Contrast Flow Duration" },
{ 0x0068, 0x65E0, VR::SQ, VM::M1, "2D Plane Coordinates Sequence" },
{ 0x0072, 0x006C, VR::SH, VM::M1TN, "Selector SH Value" },
{ 0x0074, 0x102B, VR::FD, VM::M1, "Table Top Eccentric Adjusted Angle" },
{ 0x300A, 0x00D7, VR::FL, VM::M1, "Total Wedge Tray Water-Equivalent Thickness" },
{ 0x4008, 0x0112, VR::DA, VM::M1, "Interpretation Approval Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0031[] = {
{ 0x0018, 0x1046, VR::DS, VM::M1TN, "Contrast Flow Rate" },
{ 0x0040, 0x9216, VR::XS, VM::M1, "Real World Value First Value Mapped" },
{ 0x0074, 0x102A, VR::FD, VM::M1, "Patient Support Adjusted Angle" },
{ 0x300A, 0x00D6, VR::DS, VM::M1, "Wedge Factor" },
{ 0x300C, 0x00D0, VR::IS, VM::M1, "Referenced Compensator Number" },
{ 0x4008, 0x0113, VR::TM, VM::M1, "Interpretation Approval Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0032[] = {
{ 0x0010, 0x0030, VR::DA, VM::M1, "Patient's Birth Date" },
{ 0x0014, 0x0034, VR::DS, VM::M1TN, "Material Isolation Diameter" },
{ 0x0018, 0x0038, VR::CS, VM::M1, "Intervention Status" },
{ 0x0018, 0x1079, VR::DT, VM::M1, "Radiopharmaceutical Stop DateTime" },
{ 0x0020, 0x1041, VR::DS, VM::M1, "Slice Location" },
{ 0x0020, 0x9249, VR::CS, VM::M1, "Ending Respiratory Phase" },
{ 0x0022, 0x0002, VR::US, VM::M2, "Light Path Filter Pass Band" },
{ 0x0028, 0x0008, VR::IS, VM::M1, "Number of Frames" },
{ 0x0032, 0x0012, VR::LO, VM::M1, "Study ID Issuer" },
{ 0x003A, 0x001A, VR::DS, VM::M1, "Sampling Frequency" },
{ 0x0040, 0xDB0D, VR::UI, VM::M1, "Template Extension Creator UID" },
{ 0x0070, 0x0050, VR::US, VM::M2, "Displayed Area Top Left Hand Corner (Trial)" },
{ 0x0072, 0x0052, VR::AT, VM::M1TN, "Selector Sequence Pointer" },
{ 0x2000, 0x00A2, VR::SQ, VM::M1, "Media Installed Sequence" },
{ 0x300A, 0x00E9, VR::DS, VM::M2, "Compensator Pixel Spacing" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0033[] = {
{ 0x0018, 0x0039, VR::CS, VM::M1, "Therapy Description" },
{ 0x0018, 0x1078, VR::DT, VM::M1, "Radiopharmaceutical Start DateTime" },
{ 0x0020, 0x1040, VR::LO, VM::M1, "Position Reference Indicator" },
{ 0x0020, 0x9248, VR::FL, VM::M1, "Ending Respiratory Amplitude" },
{ 0x0022, 0x0003, VR::US, VM::M1, "Image Path Filter Pass-Through Wavelength" },
{ 0x0028, 0x0009, VR::AT, VM::M1TN, "Frame Increment Pointer" },
{ 0x0040, 0xDB0C, VR::UI, VM::M1, "Template Extension Organization UID" },
{ 0x0070, 0x0051, VR::US, VM::M2, "Displayed Area Bottom Right Hand Corner (Trial)" },
{ 0x300A, 0x00E8, VR::IS, VM::M1, "Compensator Columns" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0034[] = {
{ 0x0008, 0x002A, VR::DT, VM::M1, "Acquisition DateTime" },
{ 0x0010, 0x0032, VR::TM, VM::M1, "Patient's Birth Time" },
{ 0x0012, 0x0030, VR::LO, VM::M1, "Clinical Trial Site ID" },
{ 0x0018, 0x003A, VR::ST, VM::M1, "Intervention Description" },
{ 0x0028, 0x000A, VR::AT, VM::M1TN, "Frame Dimension Pointer" },
{ 0x0032, 0x1051, VR::TM, VM::M1, "Study Completion Time" },
{ 0x0038, 0x001A, VR::DA, VM::M1, "Scheduled Admission Date" },
{ 0x0046, 0x0064, VR::FD, VM::M1, "Other Pupillary Distance" },
{ 0x0070, 0x0052, VR::SL, VM::M2, "Displayed Area Top Left Hand Corner" },
{ 0x0072, 0x0050, VR::CS, VM::M1, "Selector Attribute VR" },
{ 0x2000, 0x00A0, VR::US, VM::M1, "Memory Bit Depth" },
{ 0x300A, 0x00EB, VR::DS, VM::M1TN, "Compensator Transmission Data" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0035[] = {
{ 0x0012, 0x0031, VR::LO, VM::M1, "Clinical Trial Site Name" },
{ 0x0022, 0x0001, VR::US, VM::M1, "Light Path Filter Pass-Through Wavelength" },
{ 0x0022, 0x1040, VR::SQ, VM::M1, "Refractive Surgery Type Code Sequence" },
{ 0x0032, 0x1050, VR::DA, VM::M1, "Study Completion Date" },
{ 0x0038, 0x001B, VR::TM, VM::M1, "Scheduled Admission Time" },
{ 0x0070, 0x0053, VR::SL, VM::M2, "Displayed Area Bottom Right Hand Corner" },
{ 0x0076, 0x0055, VR::US, VM::M1, "Component ID" },
{ 0x2000, 0x00A1, VR::US, VM::M1, "Printing Bit Depth" },
{ 0x300A, 0x00EA, VR::DS, VM::M2, "Compensator Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0036[] = {
{ 0x0014, 0x0030, VR::DS, VM::M1TN, "Material Thickness" },
{ 0x0022, 0x0006, VR::SQ, VM::M1, "Patient Eye Movement Command Code Sequence" },
{ 0x0038, 0x001C, VR::DA, VM::M1, "Scheduled Discharge Date" },
{ 0x0046, 0x0062, VR::FD, VM::M1, "Near Pupillary Distance" },
{ 0x0054, 0x0070, VR::US, VM::M1TN, "Time Slot Vector" },
{ 0x0072, 0x0056, VR::LO, VM::M1, "Selector Attribute Private Creator" },
{ 0x300A, 0x00ED, VR::IS, VM::M1, "Number of Boli" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0037[] = {
{ 0x0022, 0x0007, VR::FL, VM::M1, "Spherical Lens Power" },
{ 0x0038, 0x001D, VR::TM, VM::M1, "Scheduled Discharge Time" },
{ 0x0046, 0x0063, VR::FD, VM::M1, "Intermediate Pupillary Distance" },
{ 0x0054, 0x0071, VR::US, VM::M1, "Number of Time Slots" },
{ 0x300A, 0x00EC, VR::DS, VM::M1TN, "Compensator Thickness Data" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0038[] = {
{ 0x0014, 0x0032, VR::DS, VM::M1TN, "Material Pipe Diameter" },
{ 0x0022, 0x0004, VR::US, VM::M2, "Image Path Filter Pass Band" },
{ 0x0032, 0x1055, VR::CS, VM::M1, "Study Component Status ID" },
{ 0x0038, 0x001E, VR::LO, VM::M1, "Scheduled Patient Institution Residence" },
{ 0x0040, 0xDB0B, VR::CS, VM::M1, "Template Extension Flag" },
{ 0x0046, 0x0060, VR::FD, VM::M1, "Distance Pupillary Distance" },
{ 0x0054, 0x0072, VR::SQ, VM::M1, "Time Slot Information Sequence" },
{ 0x0072, 0x0054, VR::LO, VM::M1TN, "Selector Sequence Pointer Private Creator" },
{ 0x2000, 0x00A4, VR::SQ, VM::M1, "Other Media Available Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0039[] = {
{ 0x0022, 0x0005, VR::CS, VM::M1, "Patient Eye Movement Commanded" },
{ 0x0022, 0x1044, VR::SQ, VM::M1, "Ophthalmic Ultrasound Axial Measurements Type Code Sequence" },
{ 0x0054, 0x0073, VR::DS, VM::M1, "Time Slot Time" },
{ 0x300A, 0x00EE, VR::CS, VM::M1, "Compensator Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0040[] = {
{ 0x0008, 0x0020, VR::DA, VM::M1, "Study Date" },
{ 0x0018, 0x0030, VR::LO, VM::M1TN, "Radionuclide" },
{ 0x0018, 0x1071, VR::DS, VM::M1, "Radiopharmaceutical Volume" },
{ 0x0020, 0x9241, VR::FL, VM::M1, "Nominal Percentage of Cardiac Phase" },
{ 0x0022, 0x000A, VR::FL, VM::M1, "Emmetropic Magnification" },
{ 0x0028, 0x1041, VR::SS, VM::M1, "Pixel Intensity Relationship Sign" },
{ 0x0038, 0x0010, VR::LO, VM::M1, "Admission ID" },
{ 0x0038, 0x0400, VR::LO, VM::M1, "Patient's Institution Residence" },
{ 0x0078, 0x0050, VR::FD, VM::M3, "3D Implant Template Group Member Matching Point" },
{ 0x300A, 0x00E1, VR::SH, VM::M1, "Material ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0041[] = {
{ 0x0008, 0x0021, VR::DA, VM::M1, "Series Date" },
{ 0x0008, 0x1060, VR::PN, VM::M1TN, "Name of Physician(s) Reading Study" },
{ 0x0018, 0x0031, VR::LO, VM::M1, "Radiopharmaceutical" },
{ 0x0018, 0x1070, VR::LO, VM::M1, "Radiopharmaceutical Route" },
{ 0x0018, 0x1460, VR::DS, VM::M1, "Tomo Layer Height" },
{ 0x0022, 0x000B, VR::FL, VM::M1, "Intra Ocular Pressure" },
{ 0x0028, 0x1040, VR::CS, VM::M1, "Pixel Intensity Relationship" },
{ 0x0038, 0x0011, VR::LO, VM::M1, "Issuer of Admission ID" },
{ 0x300A, 0x00E0, VR::IS, VM::M1, "Number of Compensators" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0042[] = {
{ 0x0008, 0x0022, VR::DA, VM::M1, "Acquisition Date" },
{ 0x0018, 0x0032, VR::DS, VM::M1, "Energy Window Centerline" },
{ 0x0018, 0x1073, VR::TM, VM::M1, "Radiopharmaceutical Stop Time" },
{ 0x0022, 0x0008, VR::FL, VM::M1, "Cylinder Lens Power" },
{ 0x0028, 0x0002, VR::US, VM::M1, "Samples per Pixel" },
{ 0x003A, 0x0010, VR::UL, VM::M1, "Number of Waveform Samples" },
{ 0x0040, 0xDB07, VR::DT, VM::M1, "Template Local Version" },
{ 0x0070, 0x005A, VR::SQ, VM::M1, "Displayed Area Selection Sequence" },
{ 0x2000, 0x00A8, VR::SQ, VM::M1, "Supported Image Display Formats Sequence" },
{ 0x300A, 0x00E3, VR::SQ, VM::M1, "Compensator Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0043[] = {
{ 0x0008, 0x0023, VR::DA, VM::M1, "Content Date" },
{ 0x0008, 0x1062, VR::SQ, VM::M1, "Physician(s) Reading Study Identification Sequence" },
{ 0x0018, 0x0033, VR::DS, VM::M1TN, "Energy Window Total Width" },
{ 0x0018, 0x1072, VR::TM, VM::M1, "Radiopharmaceutical Start Time" },
{ 0x0022, 0x0009, VR::FL, VM::M1, "Cylinder Axis" },
{ 0x0028, 0x0003, VR::US, VM::M1, "Samples per Pixel Used" },
{ 0x0040, 0xDB06, VR::DT, VM::M1, "Template Version" },
{ 0x3008, 0x00E0, VR::SQ, VM::M1, "Treatment Summary Measured Dose Reference Sequence" },
{ 0x300A, 0x00E2, VR::DS, VM::M1, "Total Compensator Tray Factor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0044[] = {
{ 0x0008, 0x0024, VR::DA, VM::M1, "Overlay Date" },
{ 0x0018, 0x0034, VR::LO, VM::M1, "Intervention Drug Name" },
{ 0x0018, 0x1075, VR::DS, VM::M1, "Radionuclide Half Life" },
{ 0x0020, 0x9245, VR::FL, VM::M1, "Nominal Percentage of Respiratory Phase" },
{ 0x0022, 0x000E, VR::FL, VM::M1, "Degree of Dilation" },
{ 0x0028, 0x0004, VR::CS, VM::M1, "Photometric Interpretation" },
{ 0x0038, 0x0014, VR::SQ, VM::M1, "Issuer of Admission ID Sequence" },
{ 0x0040, 0x9225, VR::FD, VM::M1, "Real World Value Slope" },
{ 0x300A, 0x00E5, VR::SH, VM::M1, "Compensator ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0045[] = {
{ 0x0008, 0x0025, VR::DA, VM::M1, "Curve Date" },
{ 0x0018, 0x0035, VR::TM, VM::M1, "Intervention Drug Start Time" },
{ 0x0018, 0x1074, VR::DS, VM::M1, "Radionuclide Total Dose" },
{ 0x0020, 0x000D, VR::UI, VM::M1, "Study Instance UID" },
{ 0x0028, 0x0005, VR::US, VM::M1, "Image Dimensions" },
{ 0x0040, 0x9224, VR::FD, VM::M1, "Real World Value Intercept" },
{ 0x0040, 0xDB00, VR::CS, VM::M1, "Template Identifier" },
{ 0x300A, 0x00E4, VR::IS, VM::M1, "Compensator Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0046[] = {
{ 0x0018, 0x0036, VR::SQ, VM::M1, "Intervention Sequence" },
{ 0x0018, 0x1077, VR::DS, VM::M1, "Radiopharmaceutical Specific Activity" },
{ 0x0020, 0x000E, VR::UI, VM::M1, "Series Instance UID" },
{ 0x0020, 0x9247, VR::CS, VM::M1, "Starting Respiratory Phase" },
{ 0x0022, 0x000C, VR::FL, VM::M1, "Horizontal Field of View" },
{ 0x0028, 0x0006, VR::US, VM::M1, "Planar Configuration" },
{ 0x0038, 0x0016, VR::LO, VM::M1, "Route of Admissions" },
{ 0x0068, 0x65D0, VR::FD, VM::M6, "3D Line Coordinates" },
{ 0x300A, 0x00E7, VR::IS, VM::M1, "Compensator Rows" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0047[] = {
{ 0x0018, 0x0037, VR::CS, VM::M1, "Therapy Type" },
{ 0x0018, 0x1076, VR::DS, VM::M1, "Radionuclide Positron Fraction" },
{ 0x0020, 0x9246, VR::FL, VM::M1, "Starting Respiratory Amplitude" },
{ 0x0022, 0x000D, VR::CS, VM::M1, "Pupil Dilated" },
{ 0x300A, 0x00E6, VR::DS, VM::M1, "Source to Compensator Tray Distance" },
{ 0x300C, 0x00E0, VR::IS, VM::M1, "Referenced Block Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0048[] = {
{ 0x0010, 0x0020, VR::LO, VM::M1, "Patient ID" },
{ 0x0014, 0x0024, VR::ST, VM::M1TN, "Component Reference System" },
{ 0x0018, 0x0028, VR::DS, VM::M1, "Intervention Drug Dose" },
{ 0x0018, 0x1069, VR::DS, VM::M1, "Trigger Time Offset" },
{ 0x0020, 0x0010, VR::SH, VM::M1, "Study ID" },
{ 0x0022, 0x0012, VR::FL, VM::M1, "Stereo Horizontal Pixel Offset" },
{ 0x0022, 0x1053, VR::FL, VM::M1, "IOL Power" },
{ 0x0038, 0x0008, VR::CS, VM::M1, "Visit Status ID" },
{ 0x0046, 0x0076, VR::FD, VM::M1, "Keratometric Power" },
{ 0x0070, 0x0040, VR::IS, VM::M1, "Image Rotation (Retired)" },
{ 0x0400, 0x0020, VR::AT, VM::M1TN, "Data Elements Signed" },
{ 0x300A, 0x00F9, VR::LO, VM::M1, "Accessory Code" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0049[] = {
{ 0x0010, 0x0021, VR::LO, VM::M1, "Issuer of Patient ID" },
{ 0x0010, 0x1060, VR::PN, VM::M1, "Patient's Mother's Birth Name" },
{ 0x0014, 0x0025, VR::ST, VM::M1TN, "Component Manufacturing Procedure" },
{ 0x0018, 0x0029, VR::SQ, VM::M1, "Intervention Drug Code Sequence" },
{ 0x0018, 0x1068, VR::DS, VM::M1, "Multiplex Group Time Offset" },
{ 0x0018, 0x9260, VR::SQ, VM::M1, "ASL Slab Sequence" },
{ 0x0020, 0x0011, VR::IS, VM::M1, "Series Number" },
{ 0x0022, 0x0013, VR::FL, VM::M1, "Stereo Vertical Pixel Offset" },
{ 0x0046, 0x0077, VR::FD, VM::M1, "Keratometric Axis" },
{ 0x0070, 0x0041, VR::CS, VM::M1, "Image Horizontal Flip" },
{ 0x0074, 0x1004, VR::DS, VM::M1, "Procedure Step Progress" },
{ 0x300A, 0x00F8, VR::CS, VM::M1, "Block Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0050[] = {
{ 0x0010, 0x0022, VR::CS, VM::M1, "Type of Patient ID" },
{ 0x0012, 0x0020, VR::LO, VM::M1, "Clinical Trial Protocol ID" },
{ 0x0018, 0x002A, VR::SQ, VM::M1, "Additional Drug Sequence" },
{ 0x0020, 0x0012, VR::IS, VM::M1, "Acquisition Number" },
{ 0x0022, 0x0010, VR::FL, VM::M1, "Stereo Baseline Angle" },
{ 0x0024, 0x0016, VR::SQ, VM::M1, "Screening Test Mode Code Sequence" },
{ 0x0032, 0x1041, VR::TM, VM::M1, "Study Arrival Time" },
{ 0x0046, 0x0074, VR::SQ, VM::M1, "Steep Keratometric Axis Sequence" },
{ 0x0070, 0x0042, VR::US, VM::M1, "Image Rotation" },
{ 0x0072, 0x0040, VR::LO, VM::M1, "Image Set Label" },
{ 0x300A, 0x00FB, VR::CS, VM::M1, "Block Mounting Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0051[] = {
{ 0x0012, 0x0021, VR::LO, VM::M1, "Clinical Trial Protocol Name" },
{ 0x0018, 0x106A, VR::CS, VM::M1, "Synchronization Trigger" },
{ 0x0020, 0x0013, VR::IS, VM::M1, "Instance Number" },
{ 0x0022, 0x0011, VR::FL, VM::M1, "Stereo Baseline Displacement" },
{ 0x0022, 0x1050, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Sequence" },
{ 0x0032, 0x1040, VR::DA, VM::M1, "Study Arrival Date" },
{ 0x0046, 0x0075, VR::FD, VM::M1, "Radius of Curvature" },
{ 0x0074, 0x1006, VR::ST, VM::M1, "Procedure Step Progress Description" },
{ 0x300A, 0x00FA, VR::CS, VM::M1, "Block Divergence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0052[] = {
{ 0x0010, 0x0024, VR::SQ, VM::M1, "Issuer of Patient ID Qualifiers Sequence" },
{ 0x0020, 0x0014, VR::IS, VM::M1, "Isotope Number" },
{ 0x0022, 0x0016, VR::SQ, VM::M1, "Illumination Type Code Sequence" },
{ 0x0024, 0x0010, VR::FL, VM::M1, "Visual Field Horizontal Extent" },
{ 0x0054, 0x0060, VR::US, VM::M1TN, "R-R Interval Vector" },
{ 0x2010, 0x00A6, VR::CS, VM::M1, "Default Magnification Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0053[] = {
{ 0x0018, 0x106C, VR::US, VM::M2, "Synchronization Channel" },
{ 0x0020, 0x0015, VR::IS, VM::M1, "Phase Number" },
{ 0x0022, 0x0017, VR::SQ, VM::M1, "Light Path Filter Type Stack Code Sequence" },
{ 0x0024, 0x0011, VR::FL, VM::M1, "Visual Field Vertical Extent" },
{ 0x0054, 0x0061, VR::US, VM::M1, "Number of R-R Intervals" },
{ 0x0074, 0x1000, VR::CS, VM::M1, "Procedure Step State" },
{ 0x2010, 0x00A7, VR::CS, VM::M1TN, "Other Magnification Types Available" },
{ 0x300A, 0x00FC, VR::IS, VM::M1, "Block Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0054[] = {
{ 0x0020, 0x0016, VR::IS, VM::M1, "Interval Number" },
{ 0x0022, 0x0014, VR::FL, VM::M1, "Stereo Rotation" },
{ 0x0024, 0x0012, VR::CS, VM::M1, "Visual Field Shape" },
{ 0x0046, 0x0070, VR::SQ, VM::M1, "Keratometry Right Eye Sequence" },
{ 0x0054, 0x0062, VR::SQ, VM::M1, "Gated Information Sequence" },
{ 0x0076, 0x0040, VR::SQ, VM::M1, "Component Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0055[] = {
{ 0x0014, 0x0023, VR::ST, VM::M1TN, "CAD File Format" },
{ 0x0018, 0x106E, VR::UL, VM::M1, "Trigger Sample Position" },
{ 0x0020, 0x0017, VR::IS, VM::M1, "Time Slot Number" },
{ 0x0022, 0x0015, VR::SQ, VM::M1, "Acquisition Device Type Code Sequence" },
{ 0x0022, 0x1054, VR::FL, VM::M1, "Predicted Refractive Error" },
{ 0x0046, 0x0071, VR::SQ, VM::M1, "Keratometry Left Eye Sequence" },
{ 0x0054, 0x0063, VR::SQ, VM::M1, "Data Information Sequence" },
{ 0x0074, 0x1002, VR::SQ, VM::M1, "Procedure Step Progress Information Sequence" },
{ 0x300A, 0x00FE, VR::LO, VM::M1, "Block Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0056[] = {
{ 0x0008, 0x0030, VR::TM, VM::M1, "Study Time" },
{ 0x0018, 0x0020, VR::CS, VM::M1TN, "Scanning Sequence" },
{ 0x0018, 0x1061, VR::LO, VM::M1, "Trigger Source or Type" },
{ 0x0020, 0x0018, VR::IS, VM::M1, "Angle Number" },
{ 0x0020, 0x9251, VR::FD, VM::M1, "R-R Interval Time Nominal" },
{ 0x0022, 0x001A, VR::SQ, VM::M1, "Channel Description Code Sequence" },
{ 0x0028, 0x0010, VR::US, VM::M1, "Rows" },
{ 0x0028, 0x0400, VR::LO, VM::M1, "Transform Label" },
{ 0x0028, 0x0400, VR::US, VM::M1, "Rows For Nth Order Coefficients" },
{ 0x0028, 0x1051, VR::DS, VM::M1TN, "Window Width" },
{ 0x0032, 0x000A, VR::CS, VM::M1, "Study Status ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0057[] = {
{ 0x0008, 0x0031, VR::TM, VM::M1, "Series Time" },
{ 0x0008, 0x1070, VR::PN, VM::M1TN, "Operators' Name" },
{ 0x0018, 0x0021, VR::CS, VM::M1TN, "Sequence Variant" },
{ 0x0018, 0x1060, VR::DS, VM::M1, "Trigger Time" },
{ 0x0018, 0x1470, VR::DS, VM::M1, "Tomo Angle" },
{ 0x0020, 0x0019, VR::IS, VM::M1, "Item Number" },
{ 0x0020, 0x9250, VR::CS, VM::M1, "Respiratory Trigger Type" },
{ 0x0022, 0x001B, VR::SQ, VM::M1, "Refractive State Sequence" },
{ 0x0028, 0x0011, VR::US, VM::M1, "Columns" },
{ 0x0028, 0x0401, VR::LO, VM::M1, "Transform Version Number" },
{ 0x0028, 0x0401, VR::US, VM::M1, "Columns For Nth Order Coefficients" },
{ 0x0028, 0x1050, VR::DS, VM::M1TN, "Window Center" },
{ 0x0074, 0x100c, VR::LO, VM::M1, "Contact Display Name" },
{ 0x3008, 0x00F2, VR::SQ, VM::M1, "Recorded Range Shifter Sequence" },
{ 0x300A, 0x00F0, VR::IS, VM::M1, "Number of Blocks" },
{ 0x300C, 0x00F6, VR::IS, VM::M1, "Referenced Stop Control Point Index" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0058[] = {
{ 0x0008, 0x0032, VR::TM, VM::M1, "Acquisition Time" },
{ 0x0018, 0x0022, VR::CS, VM::M1TN, "Scan Options" },
{ 0x0018, 0x1063, VR::DS, VM::M1, "Frame Time" },
{ 0x0020, 0x9253, VR::SQ, VM::M1, "Respiratory Synchronization Sequence" },
{ 0x0022, 0x0018, VR::SQ, VM::M1, "Image Path Filter Type Stack Code Sequence" },
{ 0x0022, 0x1059, VR::FL, VM::M1, "Ophthalmic Axial Length Velocity" },
{ 0x0028, 0x0012, VR::US, VM::M1, "Planes" },
{ 0x0028, 0x0402, VR::US, VM::M1, "Number of Transform Steps" },
{ 0x0028, 0x0402, VR::LO, VM::M1TN, "Coefficient Coding" },
{ 0x0028, 0x1053, VR::DS, VM::M1, "Rescale Slope" },
{ 0x2010, 0x00A8, VR::CS, VM::M1, "Default Smoothing Type" },
{ 0x300A, 0x00F3, VR::FL, VM::M1, "Total Block Tray Water-Equivalent Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0059[] = {
{ 0x0008, 0x0033, VR::TM, VM::M1, "Content Time" },
{ 0x0008, 0x1072, VR::SQ, VM::M1, "Operator Identification Sequence" },
{ 0x0018, 0x0023, VR::CS, VM::M1, "MR Acquisition Type" },
{ 0x0018, 0x1062, VR::IS, VM::M1, "Nominal Interval" },
{ 0x0020, 0x9252, VR::FD, VM::M1, "Actual Cardiac Trigger Delay Time" },
{ 0x0022, 0x0019, VR::SQ, VM::M1, "Lenses Code Sequence" },
{ 0x0028, 0x0403, VR::LO, VM::M1TN, "Sequence of Compressed Data" },
{ 0x0028, 0x0403, VR::AT, VM::M1TN, "Coefficient Coding Pointers" },
{ 0x0028, 0x1052, VR::DS, VM::M1, "Rescale Intercept" },
{ 0x0074, 0x100e, VR::SQ, VM::M1, "Procedure Step Discontinuation Reason Code Sequence" },
{ 0x2010, 0x00A9, VR::CS, VM::M1TN, "Other Smoothing Types Available" },
{ 0x3008, 0x00F0, VR::SQ, VM::M1, "Recorded Snout Sequence" },
{ 0x300A, 0x00F2, VR::DS, VM::M1, "Total Block Tray Factor" },
{ 0x300C, 0x00F4, VR::IS, VM::M1, "Referenced Start Control Point Index" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0060[] = {
{ 0x0008, 0x0034, VR::TM, VM::M1, "Overlay Time" },
{ 0x0014, 0x0028, VR::ST, VM::M1TN, "Component Manufacturer" },
{ 0x0018, 0x0024, VR::SH, VM::M1, "Sequence Name" },
{ 0x0018, 0x1065, VR::DS, VM::M1TN, "Frame Time Vector" },
{ 0x0020, 0x9255, VR::FD, VM::M1, "Nominal Respiratory Trigger Delay Time" },
{ 0x0022, 0x001E, VR::FL, VM::M1, "Camera Angle of View" },
{ 0x0024, 0x0018, VR::FL, VM::M1, "Maximum Stimulus Luminance" },
{ 0x0028, 0x0014, VR::US, VM::M1, "Ultrasound Color Data Present" },
{ 0x0028, 0x0404, VR::AT, VM::M1TN, "Details of Coefficients" },
{ 0x0028, 0x1055, VR::LO, VM::M1TN, "Window Center & Width Explanation" },
{ 0x0038, 0x0004, VR::SQ, VM::M1, "Referenced Patient Alias Sequence" },
{ 0x300A, 0x00F5, VR::SH, VM::M1, "Block Tray ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0061[] = {
{ 0x0008, 0x0035, VR::TM, VM::M1, "Curve Time" },
{ 0x0018, 0x0025, VR::CS, VM::M1, "Angio Flag" },
{ 0x0018, 0x1064, VR::LO, VM::M1, "Cardiac Framing Type" },
{ 0x0020, 0x9254, VR::FD, VM::M1, "Respiratory Interval Time" },
{ 0x0028, 0x1054, VR::LO, VM::M1, "Rescale Type" },
{ 0x0074, 0x1008, VR::SQ, VM::M1, "Procedure Step Communications URI Sequence" },
{ 0x3008, 0x00F6, VR::SQ, VM::M1, "Recorded Range Modulator Sequence" },
{ 0x300A, 0x00F4, VR::SQ, VM::M1, "Block Sequence" },
{ 0x300C, 0x00F2, VR::SQ, VM::M1, "Referenced Control Point Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0062[] = {
{ 0x0018, 0x0026, VR::SQ, VM::M1, "Intervention Drug Information Sequence" },
{ 0x0018, 0x1067, VR::DS, VM::M1, "Image Trigger Delay" },
{ 0x0020, 0x9257, VR::FD, VM::M1, "Actual Respiratory Trigger Delay Time" },
{ 0x0022, 0x001C, VR::SQ, VM::M1, "Mydriatic Agent Code Sequence" },
{ 0x0028, 0x6190, VR::ST, VM::M1, "Mask Operation Explanation" },
{ 0x0032, 0x000C, VR::CS, VM::M1, "Study Priority ID" },
{ 0x003A, 0x0004, VR::CS, VM::M1, "Waveform Originality" },
{ 0x300A, 0x00F7, VR::FL, VM::M1, "Isocenter to Block Tray Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0063[] = {
{ 0x0018, 0x0027, VR::TM, VM::M1, "Intervention Drug Stop Time" },
{ 0x0018, 0x1066, VR::DS, VM::M1, "Frame Delay" },
{ 0x0020, 0x9256, VR::FD, VM::M1, "Respiratory Trigger Delay Threshold" },
{ 0x0022, 0x001D, VR::SQ, VM::M1, "Relative Image Position Code Sequence" },
{ 0x0028, 0x1056, VR::CS, VM::M1, "VOI LUT Function" },
{ 0x003A, 0x0005, VR::US, VM::M1, "Number of Waveform Channels" },
{ 0x0074, 0x100a, VR::ST, VM::M1, "Contact URI" },
{ 0x3008, 0x00F4, VR::SQ, VM::M1, "Recorded Lateral Spreading Device Sequence" },
{ 0x300A, 0x00F6, VR::DS, VM::M1, "Source to Block Tray Distance" },
{ 0x300C, 0x00F0, VR::IS, VM::M1, "Referenced Control Point Index" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0064[] = {
{ 0x0010, 0x1010, VR::AS, VM::M1, "Patient's Age" },
{ 0x0018, 0x1018, VR::LO, VM::M1, "Secondary Capture Device Manufacturer's Model Name" },
{ 0x0020, 0x1020, VR::LO, VM::M1TN, "Reference" },
{ 0x0020, 0x9228, VR::UL, VM::M1, "Concatenation Frame Offset Number" },
{ 0x0024, 0x0065, VR::SQ, VM::M1, "Age Corrected Sensitivity Deviation Algorithm Sequence" },
{ 0x0028, 0x0069, VR::US, VM::M1, "Bits Grouped" },
{ 0x0032, 0x1032, VR::PN, VM::M1, "Requesting Physician" },
{ 0x0040, 0x0001, VR::AE, VM::M1TN, "Scheduled Station AE Title" },
{ 0x0052, 0x0013, VR::FD, VM::M1, "Catheter Rotational Rate" },
{ 0x0054, 0x0015, VR::DS, VM::M1, "Energy Window Upper Limit" },
{ 0x0066, 0x0027, VR::SQ, VM::M1, "Triangle Fan Sequence" },
{ 0x1000, 0x0000, VR::US, VM::M3, "Escape Triplet" },
{ 0x3006, 0x0084, VR::IS, VM::M1, "Referenced ROI Number" },
{ 0x300A, 0x0088, VR::FL, VM::M1, "Beam Dose Point Depth" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0065[] = {
{ 0x0010, 0x0050, VR::SQ, VM::M1, "Patient's Insurance Plan Code Sequence" },
{ 0x0014, 0x0054, VR::DS, VM::M1, "Outer Diameter" },
{ 0x0018, 0x1019, VR::LO, VM::M1TN, "Secondary Capture Device Software Versions" },
{ 0x0018, 0x9601, VR::SQ, VM::M1, "Diffusion b-matrix Sequence" },
{ 0x0020, 0x0060, VR::CS, VM::M1, "Laterality" },
{ 0x0024, 0x0064, VR::SQ, VM::M1, "Results Normals Sequence" },
{ 0x0028, 0x0068, VR::US, VM::M1, "Repeat Interval" },
{ 0x0032, 0x1033, VR::LO, VM::M1, "Requesting Service" },
{ 0x0044, 0x0004, VR::DT, VM::M1, "Approval Status DateTime" },
{ 0x0048, 0x0008, VR::SQ, VM::M1, "Total Pixel Matrix Origin Sequence" },
{ 0x0050, 0x0010, VR::SQ, VM::M1, "Device Sequence" },
{ 0x0052, 0x0012, VR::US, VM::M1, "A-lines Per Frame" },
{ 0x0054, 0x0014, VR::DS, VM::M1, "Energy Window Lower Limit" },
{ 0x0066, 0x0026, VR::SQ, VM::M1, "Triangle Strip Sequence" },
{ 0x0072, 0x0032, VR::US, VM::M1, "Image Set Number" },
{ 0x0072, 0x0422, VR::SQ, VM::M1, "Structured Display Image Box Sequence" },
{ 0x0076, 0x0036, VR::CS, VM::M1, "Exclusive Component Type" },
{ 0x1000, 0x0001, VR::US, VM::M3, "Run Length Triplet" },
{ 0x2040, 0x0082, VR::CS, VM::M1, "Overlay Background Density" },
{ 0x3006, 0x0085, VR::SH, VM::M1, "ROI Observation Label" },
{ 0x300A, 0x0089, VR::FL, VM::M1, "Beam Dose Point Equivalent Depth" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0066[] = {
{ 0x0012, 0x0051, VR::ST, VM::M1, "Clinical Trial Time Point Description" },
{ 0x0018, 0x101A, VR::LO, VM::M1TN, "Hardcopy Device Software Version" },
{ 0x0018, 0x9602, VR::FD, VM::M1, "Diffusion b-value XX" },
{ 0x0024, 0x0067, VR::SQ, VM::M1, "Generalized Defect Sensitivity Deviation Algorithm Sequence" },
{ 0x0032, 0x1030, VR::LO, VM::M1, "Reason for Study" },
{ 0x0040, 0x0003, VR::TM, VM::M1, "Scheduled Procedure Step Start Time" },
{ 0x0044, 0x0007, VR::SQ, VM::M1, "Product Type Code Sequence" },
{ 0x0050, 0x0013, VR::FD, VM::M1, "Container Component Thickness" },
{ 0x0052, 0x0011, VR::FD, VM::M1, "A-line Rate" },
{ 0x0054, 0x0017, VR::IS, VM::M1, "Residual Syringe Counts" },
{ 0x0066, 0x0025, VR::OW, VM::M1, "Vertex Point Index List" },
{ 0x0072, 0x0421, VR::US, VM::M3, "Empty Image Box CIELab Value" },
{ 0x1000, 0x0002, VR::US, VM::M1, "Huffman Table Size" },
{ 0x3006, 0x0086, VR::SQ, VM::M1, "RT ROI Identification Code Sequence" },
{ 0x300A, 0x008A, VR::FL, VM::M1, "Beam Dose Point SSD" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0067[] = {
{ 0x0012, 0x0050, VR::LO, VM::M1, "Clinical Trial Time Point ID" },
{ 0x0014, 0x0056, VR::DS, VM::M1, "Inner Diameter" },
{ 0x0018, 0x101B, VR::LO, VM::M1, "Hardcopy Device Manufacturer's Model Name" },
{ 0x0018, 0x9603, VR::FD, VM::M1, "Diffusion b-value XY" },
{ 0x0020, 0x0062, VR::CS, VM::M1, "Image Laterality" },
{ 0x0024, 0x0066, VR::FL, VM::M1, "Global Deviation From Normal" },
{ 0x0032, 0x1031, VR::SQ, VM::M1, "Requesting Physician Identification Sequence" },
{ 0x0040, 0x0002, VR::DA, VM::M1, "Scheduled Procedure Step Start Date" },
{ 0x0050, 0x0012, VR::SQ, VM::M1, "Container Component Type Code Sequence" },
{ 0x0054, 0x0016, VR::SQ, VM::M1, "Radiopharmaceutical Information Sequence" },
{ 0x0066, 0x0024, VR::OW, VM::M1, "Edge Point Index List" },
{ 0x0072, 0x0030, VR::SQ, VM::M1, "Time Based Image Sets Sequence" },
{ 0x0072, 0x0420, VR::US, VM::M3, "Structured Display Background CIELab Value" },
{ 0x0076, 0x0034, VR::CS, VM::M1, "Component Type Code Sequence" },
{ 0x1000, 0x0003, VR::US, VM::M3, "Huffman Table Triplet" },
{ 0x2040, 0x0080, VR::CS, VM::M1, "Overlay Foreground Density" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0068[] = {
{ 0x0014, 0x1010, VR::ST, VM::M1, "Actual Environmental Conditions" },
{ 0x0018, 0x9214, VR::CS, VM::M1, "Respiratory Cycle Position" },
{ 0x0018, 0x9604, VR::FD, VM::M1, "Diffusion b-value XZ" },
{ 0x0024, 0x0061, VR::CS, VM::M1, "Excessive False Positives Data Flag" },
{ 0x0040, 0x0005, VR::TM, VM::M1, "Scheduled Procedure Step End Time" },
{ 0x0044, 0x0001, VR::ST, VM::M1, "Product Package Identifier" },
{ 0x0050, 0x0015, VR::FD, VM::M1, "Container Component Width" },
{ 0x0054, 0x0011, VR::US, VM::M1, "Number of Energy Windows" },
{ 0x0066, 0x0023, VR::OW, VM::M1, "Triangle Point Index List" },
{ 0x0072, 0x0427, VR::SQ, VM::M1, "Referenced First Frame Sequence" },
{ 0x1000, 0x0004, VR::US, VM::M1, "Shift Table Size" },
{ 0x3006, 0x0080, VR::SQ, VM::M1, "RT ROI Observations Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0069[] = {
{ 0x0008, 0x9205, VR::CS, VM::M1, "Pixel Presentation" },
{ 0x0014, 0x0050, VR::CS, VM::M1, "Component Shape" },
{ 0x0018, 0x9605, VR::FD, VM::M1, "Diffusion b-value YY" },
{ 0x0024, 0x0060, VR::US, VM::M1, "False Positives Quantity" },
{ 0x0040, 0x0004, VR::DA, VM::M1, "Scheduled Procedure Step End Date" },
{ 0x0050, 0x0014, VR::DS, VM::M1, "Device Length" },
{ 0x0052, 0x0016, VR::SQ, VM::M1, "Mode of Percutaneous Access Sequence" },
{ 0x0054, 0x0010, VR::US, VM::M1TN, "Energy Window Vector" },
{ 0x0054, 0x0400, VR::SH, VM::M1, "Image ID" },
{ 0x0076, 0x0032, VR::SQ, VM::M1, "Component Types Sequence" },
{ 0x1000, 0x0005, VR::US, VM::M3, "Shift Table Triplet" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0070[] = {
{ 0x0008, 0x9206, VR::CS, VM::M1, "Volumetric Properties" },
{ 0x0018, 0x9606, VR::FD, VM::M1, "Diffusion b-value YZ" },
{ 0x0022, 0x1024, VR::SQ, VM::M1, "Lens Status Code Sequence" },
{ 0x0024, 0x0063, VR::CS, VM::M1, "Visual Field Test Normals Flag" },
{ 0x0032, 0x1034, VR::SQ, VM::M1, "Requesting Service Code Sequence" },
{ 0x0040, 0x0007, VR::LO, VM::M1, "Scheduled Procedure Step Description" },
{ 0x0044, 0x0003, VR::LT, VM::M1, "Approval Status Further Description" },
{ 0x0050, 0x0017, VR::CS, VM::M1, "Device Diameter Units" },
{ 0x0054, 0x0013, VR::SQ, VM::M1, "Energy Window Range Sequence" },
{ 0x0066, 0x0021, VR::OF, VM::M1, "Vector Coordinate Data" },
{ 0x3006, 0x0082, VR::IS, VM::M1, "Observation Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0071[] = {
{ 0x0008, 0x9207, VR::CS, VM::M1, "Volume Based Calculation Technique" },
{ 0x0014, 0x0052, VR::CS, VM::M1, "Curvature Type" },
{ 0x0018, 0x9217, VR::FD, VM::M1, "Velocity Encoding Maximum Value" },
{ 0x0018, 0x9607, VR::FD, VM::M1, "Diffusion b-value ZZ" },
{ 0x0022, 0x1025, VR::SQ, VM::M1, "Vitreous Status Code Sequence" },
{ 0x0024, 0x0062, VR::CS, VM::M1, "Excessive False Positives" },
{ 0x0040, 0x0006, VR::PN, VM::M1, "Scheduled Performing Physician's Name" },
{ 0x0044, 0x0002, VR::CS, VM::M1, "Substance Administration Approval" },
{ 0x0050, 0x0016, VR::DS, VM::M1, "Device Diameter" },
{ 0x0052, 0x0014, VR::FD, VM::M1, "A-line Pixel Spacing" },
{ 0x0054, 0x0012, VR::SQ, VM::M1, "Energy Window Information Sequence" },
{ 0x0066, 0x0020, VR::FL, VM::M1TN, "Vector Accuracy" },
{ 0x0072, 0x0034, VR::CS, VM::M1, "Image Set Selector Category" },
{ 0x0072, 0x0424, VR::SQ, VM::M1, "Structured Display Text Box Sequence" },
{ 0x0076, 0x0030, VR::LO, VM::M1, "Surgical Technique" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0072[] = {
{ 0x0008, 0x0041, VR::LO, VM::M1, "Data Set Subtype" },
{ 0x0008, 0x1000, VR::AE, VM::M1, "Network ID" },
{ 0x0008, 0x9208, VR::CS, VM::M1, "Complex Image Component" },
{ 0x0018, 0x1010, VR::LO, VM::M1, "Secondary Capture Device ID" },
{ 0x0018, 0x1400, VR::LO, VM::M1, "Acquisition Device Processing Description" },
{ 0x0018, 0x9218, VR::FD, VM::M1, "Tag Spacing Second Dimension" },
{ 0x0028, 0x0061, VR::SH, VM::M1, "Compression Originator" },
{ 0x0040, 0x0009, VR::SH, VM::M1, "Scheduled Procedure Step ID" },
{ 0x0048, 0x0001, VR::FL, VM::M1, "Imaged Volume Width" },
{ 0x0050, 0x0019, VR::DS, VM::M1, "Inter-Marker Distance" },
{ 0x0066, 0x002F, VR::SQ, VM::M1, "Algorithm Family Code Sequence" },
{ 0x3008, 0x0082, VR::IS, VM::M1, "Referenced Measured Dose Reference Number" },
{ 0x300A, 0x0080, VR::IS, VM::M1, "Number of Beams" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0073[] = {
{ 0x0008, 0x0040, VR::US, VM::M1, "Data Set Type" },
{ 0x0008, 0x9209, VR::CS, VM::M1, "Acquisition Contrast" },
{ 0x0018, 0x0050, VR::DS, VM::M1, "Slice Thickness" },
{ 0x0018, 0x1011, VR::LO, VM::M1, "Hardcopy Creation Device ID" },
{ 0x0018, 0x1401, VR::LO, VM::M1, "Acquisition Device Processing Code" },
{ 0x0018, 0x9219, VR::SS, VM::M1, "Tag Angle Second Axis" },
{ 0x0020, 0x9221, VR::SQ, VM::M1, "Dimension Organization Sequence" },
{ 0x0028, 0x0060, VR::CS, VM::M1, "Compression Code" },
{ 0x0040, 0x0008, VR::SQ, VM::M1, "Scheduled Protocol Code Sequence" },
{ 0x0050, 0x0018, VR::DS, VM::M1, "Device Volume" },
{ 0x0066, 0x002E, VR::SQ, VM::M1, "Segment Surface Source Instance Sequence" },
{ 0x0072, 0x003A, VR::CS, VM::M1, "Relative Time Units" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0074[] = {
{ 0x0018, 0x1012, VR::DA, VM::M1, "Date of Secondary Capture" },
{ 0x0018, 0x1402, VR::CS, VM::M1, "Cassette Orientation" },
{ 0x0020, 0x9222, VR::SQ, VM::M1, "Dimension Index Sequence" },
{ 0x0022, 0x1028, VR::SQ, VM::M1, "IOL Formula Code Sequence" },
{ 0x0028, 0x0063, VR::SH, VM::M1, "Compression Description" },
{ 0x0040, 0x000B, VR::SQ, VM::M1, "Scheduled Performing Physician Identification Sequence" },
{ 0x0048, 0x0003, VR::FL, VM::M1, "Imaged Volume Depth" },
{ 0x0050, 0x001B, VR::LO, VM::M1, "Container Component ID" },
{ 0x0066, 0x002D, VR::SQ, VM::M1, "Segment Surface Generation Algorithm Identification Sequence" },
{ 0x3008, 0x0080, VR::SQ, VM::M1, "Referenced Measured Dose Reference Sequence" },
{ 0x300A, 0x0082, VR::DS, VM::M3, "Beam Dose Specification Point" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0075[] = {
{ 0x0008, 0x0042, VR::CS, VM::M1, "Nuclear Medicine Series Type" },
{ 0x0018, 0x1403, VR::CS, VM::M1, "Cassette Size" },
{ 0x0022, 0x1029, VR::LO, VM::M1, "IOL Formula Detail" },
{ 0x0028, 0x0062, VR::LO, VM::M1, "Compression Label" },
{ 0x0040, 0x000A, VR::SQ, VM::M1, "Stage Code Sequence" },
{ 0x0048, 0x0002, VR::FL, VM::M1, "Imaged Volume Height" },
{ 0x0050, 0x001A, VR::CS, VM::M1, "Container Component Material" },
{ 0x0066, 0x002C, VR::UL, VM::M1, "Referenced Surface Number" },
{ 0x0072, 0x0038, VR::US, VM::M2, "Relative Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0076[] = {
{ 0x0018, 0x1014, VR::TM, VM::M1, "Time of Secondary Capture" },
{ 0x0018, 0x1404, VR::US, VM::M1, "Exposures on Plate" },
{ 0x0024, 0x0069, VR::LO, VM::M1, "Patient Reliability Indicator" },
{ 0x0028, 0x0065, VR::CS, VM::M1TN, "Compression Sequence" },
{ 0x0044, 0x0009, VR::LT, VM::M1, "Product Description" },
{ 0x0050, 0x001D, VR::FD, VM::M1, "Container Component Diameter" },
{ 0x0066, 0x002B, VR::SQ, VM::M1, "Referenced Surface Sequence" },
{ 0x3006, 0x0088, VR::ST, VM::M1, "ROI Observation Description" },
{ 0x300A, 0x0084, VR::DS, VM::M1, "Beam Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0077[] = {
{ 0x0018, 0x1405, VR::IS, VM::M1, "Relative X-Ray Exposure" },
{ 0x0024, 0x0068, VR::FL, VM::M1, "Localized Deviation from Normal" },
{ 0x0044, 0x0008, VR::LO, VM::M1TN, "Product Name" },
{ 0x0050, 0x001C, VR::FD, VM::M1, "Container Component Length" },
{ 0x0054, 0x0018, VR::SH, VM::M1, "Energy Window Name" },
{ 0x0066, 0x002A, VR::UL, VM::M1, "Surface Count" },
{ 0x0072, 0x003E, VR::SQ, VM::M1, "Abstract Prior Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0078[] = {
{ 0x0018, 0x1016, VR::LO, VM::M1, "Secondary Capture Device Manufacturer" },
{ 0x0044, 0x000B, VR::DT, VM::M1, "Product Expiration DateTime" },
{ 0x0048, 0x0007, VR::UL, VM::M1, "Total Pixel Matrix Rows" },
{ 0x0066, 0x0029, VR::OW, VM::M1, "Primitive Point Index List" },
{ 0x300A, 0x0086, VR::DS, VM::M1, "Beam Meterset" },
{ 0x300C, 0x0080, VR::SQ, VM::M1, "Referenced Dose Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0079[] = {
{ 0x0014, 0x3099, VR::LT, VM::M1, "Calibration Notes" },
{ 0x0018, 0x1017, VR::LO, VM::M1, "Hardcopy Device Manufacturer" },
{ 0x0028, 0x0066, VR::AT, VM::M1TN, "Compression Step Pointers" },
{ 0x0044, 0x000A, VR::LO, VM::M1, "Product Lot Identifier" },
{ 0x0048, 0x0006, VR::UL, VM::M1, "Total Pixel Matrix Columns" },
{ 0x0050, 0x001E, VR::LO, VM::M1, "Container Component Description" },
{ 0x0066, 0x0028, VR::SQ, VM::M1, "Line Sequence" },
{ 0x0068, 0x65B0, VR::FD, VM::M4, "2D Line Coordinates" },
{ 0x0072, 0x003C, VR::SS, VM::M2, "Abstract Prior Value" },
{ 0x0076, 0x0038, VR::CS, VM::M1, "Mandatory Component Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0080[] = {
{ 0x0010, 0x1000, VR::LO, VM::M1TN, "Other Patient IDs" },
{ 0x0014, 0x0045, VR::ST, VM::M1TN, "Material Properties File Format" },
{ 0x0018, 0x1008, VR::LO, VM::M1, "Gantry ID" },
{ 0x0018, 0x9200, VR::CS, VM::M1, "MR Spectroscopy Acquisition Type" },
{ 0x0020, 0x9238, VR::LO, VM::M1, "Functional Group Private Creator" },
{ 0x0024, 0x0075, VR::FL, VM::M1, "Short Term Fluctuation" },
{ 0x0040, 0x0011, VR::SH, VM::M1, "Scheduled Procedure Step Location" },
{ 0x0042, 0x0013, VR::SQ, VM::M1, "Source Instance Sequence" },
{ 0x0052, 0x0003, VR::FD, VM::M1, "Beam Spot Size" },
{ 0x0070, 0x0021, VR::US, VM::M1, "Number of Graphic Points" },
{ 0x1010, 0x0000, VR::US, VM::M1TN, "Zonal Map" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0081[] = {
{ 0x0008, 0x0058, VR::UI, VM::M1TN, "Failed SOP Instance UID List" },
{ 0x0010, 0x0040, VR::CS, VM::M1, "Patient's Sex" },
{ 0x0010, 0x1001, VR::PN, VM::M1TN, "Other Patient Names" },
{ 0x0012, 0x0042, VR::LO, VM::M1, "Clinical Trial Subject Reading ID" },
{ 0x0014, 0x0044, VR::ST, VM::M1TN, "Material Properties File ID" },
{ 0x0020, 0x0070, VR::LO, VM::M1, "Image Geometry Type" },
{ 0x0022, 0x1033, VR::FL, VM::M1, "Keratometer Index" },
{ 0x0024, 0x0074, VR::CS, VM::M1, "Short Term Fluctuation Calculated" },
{ 0x0040, 0x0010, VR::SH, VM::M1TN, "Scheduled Station Name" },
{ 0x0040, 0x0400, VR::LT, VM::M1, "Comments on the Scheduled Procedure Step" },
{ 0x0040, 0xA29A, VR::SL, VM::M2T2N, "Pixel Coordinates Set (Trial)" },
{ 0x0042, 0x0012, VR::LO, VM::M1, "MIME Type of Encapsulated Document" },
{ 0x0046, 0x0016, VR::SQ, VM::M1, "Unspecified Laterality Lens Sequence" },
{ 0x0052, 0x0002, VR::FD, VM::M1, "OCT Focal Distance" },
{ 0x0054, 0x0414, VR::SQ, VM::M1, "Patient Gantry Relationship Code Sequence" },
{ 0x0066, 0x0036, VR::LO, VM::M1, "Algorithm Name" },
{ 0x0070, 0x0020, VR::US, VM::M1, "Graphic Dimensions" },
{ 0x0072, 0x0022, VR::SQ, VM::M1, "Image Set Selector Sequence" },
{ 0x0072, 0x0432, VR::US, VM::M2TN, "Synchronized Image Box List" },
{ 0x0078, 0x0028, VR::SQ, VM::M1, "Implant Template Group Target Anatomy Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0082[] = {
{ 0x0010, 0x1002, VR::SQ, VM::M1, "Other Patient IDs Sequence" },
{ 0x0024, 0x0077, VR::FL, VM::M1, "Short Term Fluctuation Probability" },
{ 0x0032, 0x1020, VR::LO, VM::M1, "Scheduled Study Location" },
{ 0x0042, 0x0011, VR::OB, VM::M1, "Encapsulated Document" },
{ 0x0046, 0x0015, VR::SQ, VM::M1, "Left Lens Sequence" },
{ 0x0052, 0x0001, VR::FL, VM::M1, "Contrast/Bolus Ingredient Percent by Volume" },
{ 0x0066, 0x0035, VR::SQ, VM::M1, "Surface Processing Algorithm Identification Sequence" },
{ 0x0070, 0x0023, VR::CS, VM::M1, "Graphic Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0083[] = {
{ 0x0012, 0x0040, VR::LO, VM::M1, "Clinical Trial Subject ID" },
{ 0x0014, 0x0046, VR::LT, VM::M1, "Material Notes" },
{ 0x0024, 0x0076, VR::CS, VM::M1, "Short Term Fluctuation Probability Calculated" },
{ 0x0032, 0x1021, VR::AE, VM::M1TN, "Scheduled Study Location AE Title" },
{ 0x0040, 0x0012, VR::LO, VM::M1, "Pre-Medication" },
{ 0x0042, 0x0010, VR::ST, VM::M1, "Document Title" },
{ 0x0046, 0x0014, VR::SQ, VM::M1, "Right Lens Sequence" },
{ 0x0066, 0x0034, VR::SQ, VM::M1, "Facet Sequence" },
{ 0x0070, 0x0022, VR::FL, VM::M2TN, "Graphic Data" },
{ 0x0072, 0x0020, VR::SQ, VM::M1, "Image Sets Sequence" },
{ 0x0072, 0x0430, VR::SQ, VM::M1, "Image Box Synchronization Sequence" },
{ 0x0078, 0x002A, VR::SQ, VM::M1, "Implant Template Group Members Sequence" },
{ 0x2040, 0x0090, VR::CS, VM::M1, "Overlay Mode" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0084[] = {
{ 0x0024, 0x0071, VR::FL, VM::M1, "Global Deviation Probability" },
{ 0x0044, 0x0011, VR::LO, VM::M1, "Substance Administration Notes" },
{ 0x0052, 0x0007, VR::FD, VM::M1, "OCT Optical Center Wavelength" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0085[] = {
{ 0x0008, 0x9215, VR::SQ, VM::M1, "Derivation Code Sequence" },
{ 0x0010, 0x1005, VR::PN, VM::M1, "Patient's Birth Name" },
{ 0x0022, 0x1037, VR::FL, VM::M1, "Target Refraction" },
{ 0x0024, 0x0070, VR::FL, VM::M1, "Visual Field Mean Sensitivity" },
{ 0x0028, 0x9235, VR::CS, VM::M1, "Signal Domain Rows" },
{ 0x0044, 0x0010, VR::DT, VM::M1, "Substance Administration DateTime" },
{ 0x0046, 0x0012, VR::LO, VM::M1, "Lens Description" },
{ 0x0050, 0x0004, VR::CS, VM::M1, "Calibration Image" },
{ 0x0052, 0x0006, VR::CS, VM::M1, "OCT Acquisition Domain" },
{ 0x0054, 0x0410, VR::SQ, VM::M1, "Patient Orientation Code Sequence" },
{ 0x0066, 0x0032, VR::LT, VM::M1, "Algorithm Parameters" },
{ 0x0070, 0x0024, VR::CS, VM::M1, "Graphic Filled" },
{ 0x0072, 0x0026, VR::AT, VM::M1, "Selector Attribute" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0086[] = {
{ 0x0014, 0x3080, VR::OB, VM::M1, "Bad Pixel Image" },
{ 0x0024, 0x0073, VR::FL, VM::M1, "Localized Deviation Probability" },
{ 0x0044, 0x0013, VR::SQ, VM::M1, "Product Parameter Sequence" },
{ 0x0066, 0x0031, VR::LO, VM::M1, "Algorithm Version" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0087[] = {
{ 0x0014, 0x0042, VR::ST, VM::M1TN, "Material Grade" },
{ 0x0022, 0x1035, VR::SQ, VM::M1, "Source of Ophthalmic Axial Length Code Sequence" },
{ 0x0024, 0x0072, VR::CS, VM::M1, "Local Deviation Probability Normals Flag" },
{ 0x0042, 0x0014, VR::LO, VM::M1TN, "List of MIME Types" },
{ 0x0044, 0x0012, VR::LO, VM::M1, "Substance Administration Device ID" },
{ 0x0052, 0x0004, VR::FD, VM::M1, "Effective Refractive Index" },
{ 0x0054, 0x0412, VR::SQ, VM::M1, "Patient Orientation Modifier Code Sequence" },
{ 0x0066, 0x0030, VR::SQ, VM::M1, "Algorithm Name Code Sequence" },
{ 0x0072, 0x0024, VR::CS, VM::M1, "Image Set Selector Usage Flag" },
{ 0x0072, 0x0434, VR::CS, VM::M1, "Type of Synchronization" },
{ 0x0076, 0x0020, VR::SQ, VM::M1, "Procedure Type Code Sequence" },
{ 0x0078, 0x002E, VR::US, VM::M1, "Implant Template Group Member ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0088[] = {
{ 0x0008, 0x0051, VR::SQ, VM::M1, "Issuer of Accession Number Sequence" },
{ 0x0008, 0x1010, VR::SH, VM::M1, "Station Name" },
{ 0x0018, 0x1000, VR::LO, VM::M1, "Device Serial Number" },
{ 0x0018, 0x5104, VR::SQ, VM::M1, "Projection Eponymous Name Code Sequence" },
{ 0x0028, 0x0071, VR::XS, VM::M1, "Perimeter Value" },
{ 0x0038, 0x0061, VR::LO, VM::M1, "Issuer of Service Episode ID" },
{ 0x0048, 0x0011, VR::CS, VM::M1, "Focus Method" },
{ 0x3008, 0x0092, VR::IS, VM::M1, "Referenced Calculated Dose Reference Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0089[] = {
{ 0x0008, 0x0050, VR::SH, VM::M1, "Accession Number" },
{ 0x0018, 0x0040, VR::IS, VM::M1, "Cine Rate" },
{ 0x0018, 0x1411, VR::DS, VM::M1, "Exposure Index" },
{ 0x0028, 0x0070, VR::US, VM::M1TN, "Perimeter Table" },
{ 0x0038, 0x0060, VR::LO, VM::M1, "Service Episode ID" },
{ 0x0048, 0x0010, VR::CS, VM::M1, "Specimen Label in Image" },
{ 0x0078, 0x0020, VR::LO, VM::M1, "Implant Template Group Issuer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0090[] = {
{ 0x0018, 0x1002, VR::UI, VM::M1, "Device UID" },
{ 0x0018, 0x1412, VR::DS, VM::M1, "Target Exposure Index" },
{ 0x0048, 0x0013, VR::US, VM::M1, "Number of Focal Planes" },
{ 0x0052, 0x0009, VR::FD, VM::M1, "Ranging Depth" },
{ 0x3008, 0x0090, VR::SQ, VM::M1, "Referenced Calculated Dose Reference Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0091[] = {
{ 0x0008, 0x0052, VR::CS, VM::M1, "Query/Retrieve Level" },
{ 0x0018, 0x0042, VR::CS, VM::M1, "Initial Cine Run State" },
{ 0x0018, 0x1003, VR::LO, VM::M1, "Device ID" },
{ 0x0018, 0x1413, VR::DS, VM::M1, "Deviation Index" },
{ 0x0022, 0x1039, VR::CS, VM::M1, "Refractive Procedure Occurred" },
{ 0x0038, 0x0062, VR::LO, VM::M1, "Service Episode Description" },
{ 0x0040, 0xA290, VR::CS, VM::M1, "Coordinates Set Geometric Type (Trial)" },
{ 0x0048, 0x0012, VR::CS, VM::M1, "Extended Depth of Field" },
{ 0x0052, 0x0008, VR::FD, VM::M1, "Axial Resolution" },
{ 0x0072, 0x0028, VR::US, VM::M1, "Selector Value Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0092[] = {
{ 0x0018, 0x1004, VR::LO, VM::M1, "Plate ID" },
{ 0x0018, 0x5100, VR::CS, VM::M1, "Patient Position" },
{ 0x0024, 0x0079, VR::FL, VM::M1, "Corrected Localized Deviation From Normal" },
{ 0x0040, 0xA297, VR::ST, VM::M1, "Algorithm Description (Trial)" },
{ 0x0044, 0x0019, VR::SQ, VM::M1, "Substance Administration Parameter Sequence" },
{ 0x0048, 0x0015, VR::US, VM::M3, "Recommended Absent Pixel CIELab Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0093[] = {
{ 0x0008, 0x0054, VR::AE, VM::M1TN, "Retrieve AE Title" },
{ 0x0018, 0x1005, VR::LO, VM::M1, "Generator ID" },
{ 0x0018, 0x5101, VR::CS, VM::M1, "View Position" },
{ 0x0024, 0x0078, VR::CS, VM::M1, "Corrected Localized Deviation From Normal Calculated" },
{ 0x0038, 0x0064, VR::SQ, VM::M1, "Issuer of Service Episode ID Sequence" },
{ 0x0040, 0xA296, VR::SQ, VM::M1, "Algorithm Code Sequence (Trial)" },
{ 0x0048, 0x0014, VR::FL, VM::M1, "Distance Between Focal Planes" },
{ 0x0078, 0x0024, VR::LO, VM::M1, "Implant Template Group Version" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0094[] = {
{ 0x0018, 0x1006, VR::LO, VM::M1, "Grid ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0095[] = {
{ 0x0008, 0x0056, VR::CS, VM::M1, "Instance Availability" },
{ 0x0018, 0x1007, VR::LO, VM::M1, "Cassette ID" },
{ 0x0040, 0xDB73, VR::UL, VM::M1TN, "Referenced Content Item Identifier" },
{ 0x0046, 0x0018, VR::SQ, VM::M1, "Cylinder Sequence" },
{ 0x0068, 0x65A0, VR::SQ, VM::M1, "2D Line Coordinates Sequence" },
{ 0x0078, 0x0026, VR::SQ, VM::M1, "Replaced Implant Template Group Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0096[] = {
{ 0x0010, 0x1030, VR::DS, VM::M1, "Patient's Weight" },
{ 0x0020, 0x1000, VR::IS, VM::M1, "Series in Study" },
{ 0x0024, 0x0045, VR::CS, VM::M1, "False Negatives Estimate Flag" },
{ 0x0040, 0x1060, VR::LO, VM::M1, "Requested Procedure Description (Trial)" },
{ 0x0052, 0x0033, VR::FD, VM::M1, "Seam Line Location" },
{ 0x0062, 0x0003, VR::SQ, VM::M1, "Segmented Property Category Code Sequence" },
{ 0x0064, 0x0005, VR::SQ, VM::M1, "Deformable Registration Grid Sequence" },
{ 0x0070, 0x0011, VR::FL, VM::M2, "Bounding Box Bottom Right Hand Corner" },
{ 0x0070, 0x0401, VR::US, VM::M3, "Graphic Layer Recommended Display CIELab Value" },
{ 0x0074, 0x1054, VR::UL, VM::M1, "Attribute Item Selector" },
{ 0x3006, 0x00A4, VR::CS, VM::M1, "RT ROI Interpreted Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0097[] = {
{ 0x0008, 0x0068, VR::CS, VM::M1, "Presentation Intent Type" },
{ 0x0012, 0x0072, VR::LO, VM::M1, "Clinical Trial Series Description" },
{ 0x0018, 0x9231, VR::US, VM::M1, "MR Acquisition Phase Encoding Steps in-plane" },
{ 0x0020, 0x1001, VR::IS, VM::M1, "Acquisitions in Series" },
{ 0x0022, 0x0042, VR::SQ, VM::M1, "Mydriatic Agent Concentration Units Sequence" },
{ 0x0024, 0x0044, VR::LT, VM::M1, "Comments on Patient's Performance of Visual Field" },
{ 0x0040, 0x0020, VR::CS, VM::M1, "Scheduled Procedure Step Status" },
{ 0x0062, 0x0002, VR::SQ, VM::M1, "Segment Sequence" },
{ 0x0070, 0x0010, VR::FL, VM::M2, "Bounding Box Top Left Hand Corner" },
{ 0x0072, 0x0012, VR::SQ, VM::M1, "Source Hanging Protocol Sequence" },
{ 0x0072, 0x0402, VR::CS, VM::M1, "Filter-by Category" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0098[] = {
{ 0x0012, 0x0071, VR::LO, VM::M1, "Clinical Trial Series ID" },
{ 0x0018, 0x9232, VR::US, VM::M1, "MR Acquisition Phase Encoding Steps out-of-plane" },
{ 0x0020, 0x1002, VR::IS, VM::M1, "Images in Acquisition" },
{ 0x0022, 0x0041, VR::FL, VM::M1, "Depth of Transverse Image" },
{ 0x0032, 0x1010, VR::DA, VM::M1, "Scheduled Study Stop Date" },
{ 0x0052, 0x0031, VR::CS, VM::M1, "Catheter Direction of Rotation" },
{ 0x0062, 0x0001, VR::CS, VM::M1, "Segmentation Type" },
{ 0x0064, 0x0007, VR::UL, VM::M3, "Grid Dimensions" },
{ 0x0070, 0x0403, VR::FL, VM::M1, "Relative Opacity" },
{ 0x0074, 0x1056, VR::LO, VM::M1, "Attribute Occurrence Private Creator" },
{ 0x3006, 0x00A6, VR::PN, VM::M1, "ROI Interpreter" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0099[] = {
{ 0x0020, 0x1003, VR::IS, VM::M1, "Images in Series" },
{ 0x0024, 0x0046, VR::FL, VM::M1, "False Negatives Estimate" },
{ 0x0032, 0x1011, VR::TM, VM::M1, "Scheduled Study Stop Time" },
{ 0x0052, 0x0030, VR::SS, VM::M1, "OCT Z Offset Correction" },
{ 0x0054, 0x0036, VR::IS, VM::M1, "Phase Delay" },
{ 0x0066, 0x0004, VR::LT, VM::M1, "Surface Comments" },
{ 0x0070, 0x0012, VR::CS, VM::M1, "Bounding Box Text Horizontal Justification" },
{ 0x0070, 0x0402, VR::SQ, VM::M1, "Blending Sequence" },
{ 0x0072, 0x0010, VR::LO, VM::M1, "Hanging Protocol User Group Name" },
{ 0x0072, 0x0400, VR::SQ, VM::M1, "Filter Operations Sequence" },
{ 0x0074, 0x1057, VR::IS, VM::M1TN, "Selector Sequence Pointer Items" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0100[] = {
{ 0x0018, 0x9234, VR::UL, VM::M1, "Spectroscopy Acquisition Phase Columns" },
{ 0x0020, 0x1004, VR::IS, VM::M1, "Acquisitions in Study" },
{ 0x0054, 0x0031, VR::US, VM::M1, "Number of Phases" },
{ 0x0066, 0x0003, VR::UL, VM::M1, "Surface Number" },
{ 0x0070, 0x0015, VR::CS, VM::M1, "Anchor Point Visibility" },
{ 0x0070, 0x0405, VR::CS, VM::M1, "Blending Position" },
{ 0x0074, 0x1050, VR::SQ, VM::M1, "Attribute Occurrence Sequence" },
{ 0x3006, 0x00A0, VR::SQ, VM::M1, "Related RT ROI Observations Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0101[] = {
{ 0x0020, 0x1005, VR::IS, VM::M1, "Images in Study" },
{ 0x0022, 0x1007, VR::SQ, VM::M1, "Ophthalmic Axial Measurements Right Eye Sequence" },
{ 0x0024, 0x0040, VR::CS, VM::M1, "Excessive Fixation Losses" },
{ 0x0052, 0x0036, VR::US, VM::M1, "Seam Line Index" },
{ 0x0054, 0x0030, VR::US, VM::M1TN, "Phase Vector" },
{ 0x0062, 0x0006, VR::ST, VM::M1, "Segment Description" },
{ 0x0066, 0x0002, VR::SQ, VM::M1, "Surface Sequence" },
{ 0x0070, 0x0014, VR::FL, VM::M2, "Anchor Point" },
{ 0x0070, 0x0404, VR::SQ, VM::M1, "Referenced Spatial Registration Sequence" },
{ 0x0072, 0x0406, VR::CS, VM::M1, "Filter-by Operator" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0102[] = {
{ 0x0018, 0x9236, VR::CS, VM::M1, "Cardiac Cycle Position" },
{ 0x0040, 0x0027, VR::SQ, VM::M1, "Order Filler Identifier Sequence" },
{ 0x0054, 0x0033, VR::US, VM::M1, "Number of Frames in Phase" },
{ 0x0062, 0x0005, VR::LO, VM::M1, "Segment Label" },
{ 0x0064, 0x0003, VR::UI, VM::M1, "Source Frame of Reference UID" },
{ 0x0066, 0x0001, VR::UL, VM::M1, "Number of Surfaces" },
{ 0x0074, 0x1052, VR::AT, VM::M1, "Attribute Occurrence Pointer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0103[] = {
{ 0x0024, 0x0042, VR::US, VM::M1, "Stimuli Retesting Quantity" },
{ 0x0040, 0x0026, VR::SQ, VM::M1, "Order Placer Identifier Sequence" },
{ 0x0052, 0x0034, VR::FD, VM::M1, "First A-line Location" },
{ 0x0054, 0x0032, VR::SQ, VM::M1, "Phase Information Sequence" },
{ 0x0062, 0x0004, VR::US, VM::M1, "Segment Number" },
{ 0x0064, 0x0002, VR::SQ, VM::M1, "Deformable Registration Sequence" },
{ 0x0072, 0x0014, VR::US, VM::M1, "Number of Priors Referenced" },
{ 0x0072, 0x0404, VR::CS, VM::M1, "Filter-by Attribute Presence" },
{ 0x0076, 0x0010, VR::SQ, VM::M1, "Implant Assembly Template Target Anatomy Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0104[] = {
{ 0x0008, 0x0061, VR::CS, VM::M1TN, "Modalities in Study" },
{ 0x0018, 0x0071, VR::CS, VM::M1, "Acquisition Termination Condition" },
{ 0x0018, 0x1030, VR::LO, VM::M1, "Protocol Name" },
{ 0x0028, 0x1410, VR::CS, VM::M1, "Alpha LUT Transfer Function" },
{ 0x0062, 0x000B, VR::US, VM::M1TN, "Referenced Segment Number" },
{ 0x300A, 0x00A0, VR::IS, VM::M1, "Number of Brachy Application Setups" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0105[] = {
{ 0x0008, 0x0060, VR::CS, VM::M1, "Modality" },
{ 0x0018, 0x0070, VR::IS, VM::M1, "Counts Accumulated" },
{ 0x0018, 0x9239, VR::SQ, VM::M1, "Specific Absorption Rate Sequence" },
{ 0x0028, 0x0040, VR::CS, VM::M1, "Image Format" },
{ 0x0038, 0x0050, VR::LO, VM::M1, "Special Needs" },
{ 0x0052, 0x003A, VR::CS, VM::M1, "Refractive Index Applied" },
{ 0x0062, 0x000A, VR::SQ, VM::M1, "Segment Identification Sequence" },
{ 0x0066, 0x000E, VR::CS, VM::M1, "Finite Volume" },
{ 0x0078, 0x0010, VR::ST, VM::M1, "Implant Template Group Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0106[] = {
{ 0x0018, 0x0073, VR::CS, VM::M1, "Acquisition Start Condition" },
{ 0x0022, 0x0049, VR::FL, VM::M1, "Maximum Across-scan Distortion" },
{ 0x0022, 0x1008, VR::SQ, VM::M1, "Ophthalmic Axial Measurements Left Eye Sequence" },
{ 0x0052, 0x0039, VR::CS, VM::M1, "Interpolation Type" },
{ 0x0062, 0x0009, VR::LO, VM::M1, "Segment Algorithm Name" },
{ 0x0064, 0x000F, VR::SQ, VM::M1, "Pre Deformation Matrix Registration Sequence" },
{ 0x0066, 0x000D, VR::CS, VM::M1, "Recommended Presentation Type" },
{ 0x3008, 0x00A0, VR::SQ, VM::M1, "Beam Limiting Device Leaf Pairs Sequence" },
{ 0x300A, 0x00A2, VR::DS, VM::M3, "Brachy Application Setup Dose Specification Point" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0107[] = {
{ 0x0008, 0x0062, VR::UI, VM::M1TN, "SOP Classes in Study" },
{ 0x0018, 0x0072, VR::DS, VM::M1, "Effective Duration" },
{ 0x0022, 0x0048, VR::FL, VM::M1, "Across-scan Spatial Resolution" },
{ 0x0052, 0x0038, VR::US, VM::M1, "Number of Padded A-lines" },
{ 0x0062, 0x0008, VR::CS, VM::M1, "Segment Algorithm Type" },
{ 0x0066, 0x000C, VR::FL, VM::M1, "Recommended Presentation Opacity" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0108[] = {
{ 0x0018, 0x0075, VR::IS, VM::M1, "Acquisition Termination Condition Data" },
{ 0x0054, 0x0039, VR::CS, VM::M1, "Phase Description" },
{ 0x0062, 0x000F, VR::SQ, VM::M1, "Segmented Property Type Code Sequence" },
{ 0x0064, 0x0009, VR::OF, VM::M1, "Vector Grid Data" },
{ 0x0066, 0x000B, VR::LO, VM::M1, "Surface Processing Description" },
{ 0x300A, 0x00A4, VR::DS, VM::M1, "Brachy Application Setup Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0109[] = {
{ 0x0008, 0x0064, VR::CS, VM::M1, "Conversion Type" },
{ 0x0018, 0x0074, VR::IS, VM::M1, "Acquisition Start Condition Data" },
{ 0x0022, 0x004E, VR::DS, VM::M1, "Mydriatic Agent Concentration" },
{ 0x0024, 0x0048, VR::US, VM::M1, "Negative Catch Trials Quantity" },
{ 0x0054, 0x0038, VR::IS, VM::M1, "Pause Between Frames" },
{ 0x0062, 0x000E, VR::US, VM::M1, "Maximum Fractional Value" },
{ 0x0064, 0x0008, VR::FD, VM::M3, "Grid Resolution" },
{ 0x0066, 0x000A, VR::FL, VM::M1, "Surface Processing Ratio" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0110[] = {
{ 0x0062, 0x000D, VR::US, VM::M3, "Recommended Display CIELab Value" },
{ 0x0066, 0x0009, VR::CS, VM::M1, "Surface Processing" },
{ 0x300C, 0x00A0, VR::IS, VM::M1, "Referenced Tolerance Table Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0111[] = {
{ 0x0046, 0x0028, VR::SQ, VM::M1, "Prism Sequence" },
{ 0x0062, 0x000C, VR::US, VM::M1, "Recommended Display Grayscale Value" },
{ 0x0068, 0x6590, VR::FD, VM::M3, "3D Point Coordinates" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0112[] = {
{ 0x0010, 0x1020, VR::DS, VM::M1, "Patient's Size" },
{ 0x0012, 0x0063, VR::LO, VM::M1TN, "De-identification Method" },
{ 0x0018, 0x9220, VR::FD, VM::M1, "Frame Acquisition Duration" },
{ 0x0024, 0x0055, VR::CS, VM::M1, "Catch Trials Data Flag" },
{ 0x0028, 0x1408, VR::OW, VM::M1, "Blending Lookup Table Data" },
{ 0x0040, 0x0031, VR::UT, VM::M1, "Local Namespace Entity ID" },
{ 0x0066, 0x0017, VR::FL, VM::M3, "Point Position Accuracy" },
{ 0x0070, 0x0001, VR::SQ, VM::M1, "Graphic Annotation Sequence" },
{ 0x0074, 0x1044, VR::SQ, VM::M1, "Conventional Machine Verification Sequence" },
{ 0x3006, 0x00B4, VR::DS, VM::M1, "ROI Physical Property Value" },
{ 0x300A, 0x00B8, VR::CS, VM::M1, "RT Beam Limiting Device Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0113[] = {
{ 0x0010, 0x1021, VR::SQ, VM::M1, "Patient's Size Code Sequence" },
{ 0x0012, 0x0062, VR::CS, VM::M1, "Patient Identity Removed" },
{ 0x0020, 0x0050, VR::DS, VM::M1, "Location" },
{ 0x0024, 0x0054, VR::FL, VM::M1, "False Positives Estimate" },
{ 0x0046, 0x0036, VR::CS, VM::M1, "Vertical Prism Base" },
{ 0x0050, 0x0020, VR::LO, VM::M1, "Device Description" },
{ 0x0066, 0x0016, VR::OF, VM::M1, "Point Coordinates Data" },
{ 0x0072, 0x0002, VR::SH, VM::M1, "Hanging Protocol Name" },
{ 0x0076, 0x0006, VR::LO, VM::M1, "Implant Assembly Template Version" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0114[] = {
{ 0x0022, 0x1010, VR::CS, VM::M1, "Ophthalmic Axial Length Measurements Type" },
{ 0x0024, 0x0057, VR::CS, VM::M1, "Test Point Normals Data Flag" },
{ 0x0032, 0x1000, VR::DA, VM::M1, "Scheduled Study Start Date" },
{ 0x0040, 0x0033, VR::CS, VM::M1, "Universal Entity ID Type" },
{ 0x0066, 0x0015, VR::UL, VM::M1, "Number of Surface Points" },
{ 0x0070, 0x0003, VR::CS, VM::M1, "Bounding Box Annotation Units" },
{ 0x0074, 0x1046, VR::SQ, VM::M1, "Ion Machine Verification Sequence" },
{ 0x3006, 0x00B6, VR::SQ, VM::M1, "ROI Elemental Composition Sequence" },
{ 0x300A, 0x00BA, VR::DS, VM::M1, "Source to Beam Limiting Device Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0115[] = {
{ 0x0012, 0x0060, VR::LO, VM::M1, "Clinical Trial Coordinating Center Name" },
{ 0x0020, 0x0052, VR::UI, VM::M1, "Frame of Reference UID" },
{ 0x0024, 0x0056, VR::US, VM::M1, "Positive Catch Trials Quantity" },
{ 0x0028, 0x140B, VR::SQ, VM::M1, "Enhanced Palette Color Lookup Table Sequence" },
{ 0x0032, 0x1001, VR::TM, VM::M1, "Scheduled Study Start Time" },
{ 0x0040, 0x0032, VR::UT, VM::M1, "Universal Entity ID" },
{ 0x0046, 0x0034, VR::FD, VM::M1, "Vertical Prism Power" },
{ 0x0062, 0x0010, VR::CS, VM::M1, "Segmentation Fractional Type" },
{ 0x0070, 0x0002, VR::CS, VM::M1, "Graphic Layer" },
{ 0x3006, 0x00B7, VR::US, VM::M1, "ROI Elemental Composition Atomic Number" },
{ 0x300A, 0x00BB, VR::FL, VM::M1, "Isocenter to Beam Limiting Device Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0116[] = {
{ 0x0014, 0x1020, VR::DA, VM::M1, "Expiry Date" },
{ 0x0022, 0x0057, VR::FL, VM::M1, "Illumination Bandwidth" },
{ 0x0024, 0x0051, VR::CS, VM::M1, "Excessive False Negatives Data Flag" },
{ 0x0028, 0x140C, VR::SQ, VM::M1, "Blending LUT 2 Sequence" },
{ 0x0040, 0x0035, VR::CS, VM::M1, "Identifier Type Code" },
{ 0x0052, 0x0027, VR::SQ, VM::M1, "Intravascular Frame Content Sequence" },
{ 0x0054, 0x0021, VR::US, VM::M1, "Number of Detectors" },
{ 0x0066, 0x0013, VR::SQ, VM::M1, "Surface Mesh Primitives Sequence" },
{ 0x0070, 0x0005, VR::CS, VM::M1, "Graphic Annotation Units" },
{ 0x0074, 0x1040, VR::SQ, VM::M1, "Related Reference RT Image Sequence" },
{ 0x0076, 0x0003, VR::LO, VM::M1, "Implant Assembly Template Issuer" },
{ 0x3006, 0x00B0, VR::SQ, VM::M1, "ROI Physical Properties Sequence" },
{ 0x300A, 0x00BC, VR::IS, VM::M1, "Number of Leaf/Jaw Pairs" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0117[] = {
{ 0x0022, 0x0056, VR::FL, VM::M1, "Illumination Power" },
{ 0x0024, 0x0050, VR::US, VM::M1, "False Negatives Quantity" },
{ 0x0028, 0x140D, VR::CS, VM::M1, "Blending LUT 2 Transfer Function" },
{ 0x0046, 0x0032, VR::CS, VM::M1, "Horizontal Prism Base" },
{ 0x0052, 0x0026, VR::CS, VM::M1, "OCT Z Offset Applied" },
{ 0x0054, 0x0020, VR::US, VM::M1TN, "Detector Vector" },
{ 0x0064, 0x0010, VR::SQ, VM::M1, "Post Deformation Matrix Registration Sequence" },
{ 0x0066, 0x0012, VR::SQ, VM::M1, "Surface Points Normals Sequence" },
{ 0x0070, 0x0004, VR::CS, VM::M1, "Anchor Point Annotation Units" },
{ 0x0072, 0x0006, VR::CS, VM::M1, "Hanging Protocol Level" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0118[] = {
{ 0x0008, 0x103E, VR::LO, VM::M1, "Series Description" },
{ 0x0018, 0x9226, VR::SQ, VM::M1, "MR Image Frame Type Sequence" },
{ 0x0022, 0x0055, VR::FL, VM::M1, "Illumination Wave Length" },
{ 0x0024, 0x0053, VR::CS, VM::M1, "False Positives Estimate Flag" },
{ 0x0028, 0x005F, VR::LO, VM::M1, "Compression Recognition Code" },
{ 0x0028, 0x140E, VR::CS, VM::M1, "Data Path ID" },
{ 0x0052, 0x0025, VR::SQ, VM::M1, "Intravascular OCT Frame Type Sequence" },
{ 0x0066, 0x0011, VR::SQ, VM::M1, "Surface Points Sequence" },
{ 0x0074, 0x1042, VR::SQ, VM::M1, "General Machine Verification Sequence" },
{ 0x0076, 0x0001, VR::LO, VM::M1, "Implant Assembly Template Name" },
{ 0x3006, 0x00B2, VR::CS, VM::M1, "ROI Physical Property" },
{ 0x300A, 0x00BE, VR::DS, VM::M3TN, "Leaf Position Boundaries" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0119[] = {
{ 0x0008, 0x103F, VR::SQ, VM::M1, "Series Description Code Sequence" },
{ 0x0008, 0x9237, VR::SQ, VM::M1, "Referenced Presentation State Sequence" },
{ 0x0012, 0x0064, VR::SQ, VM::M1, "De-identification Method Code Sequence" },
{ 0x0018, 0x9227, VR::SQ, VM::M1, "MR Spectroscopy Frame Type Sequence" },
{ 0x0024, 0x0052, VR::CS, VM::M1, "Excessive False Negatives" },
{ 0x0028, 0x140F, VR::CS, VM::M1, "RGB LUT Transfer Function" },
{ 0x0040, 0x0036, VR::SQ, VM::M1, "Assigning Facility Sequence" },
{ 0x0046, 0x0030, VR::FD, VM::M1, "Horizontal Prism Power" },
{ 0x0054, 0x0022, VR::SQ, VM::M1, "Detector Information Sequence" },
{ 0x0066, 0x0010, VR::CS, VM::M1, "Manifold" },
{ 0x0070, 0x0006, VR::ST, VM::M1, "Unformatted Text Value" },
{ 0x0072, 0x0004, VR::LO, VM::M1, "Hanging Protocol Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0120[] = {
{ 0x0008, 0x1030, VR::LO, VM::M1, "Study Description" },
{ 0x0018, 0x1020, VR::LO, VM::M1TN, "Software Version(s)" },
{ 0x0018, 0x1800, VR::CS, VM::M1, "Acquisition Time Synchronized" },
{ 0x0028, 0x0051, VR::CS, VM::M1TN, "Corrected Image" },
{ 0x0040, 0x0039, VR::SQ, VM::M1, "Assigning Jurisdiction Code Sequence" },
{ 0x0066, 0x001F, VR::US, VM::M1, "Vector Dimensionality" },
{ 0x0070, 0x0009, VR::SQ, VM::M1, "Graphic Object Sequence" },
{ 0x0074, 0x104C, VR::SQ, VM::M1, "Conventional Control Point Verification Sequence" },
{ 0x0078, 0x0001, VR::LO, VM::M1, "Implant Template Group Name" },
{ 0x300A, 0x00B0, VR::SQ, VM::M1, "Beam Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0121[] = {
{ 0x0008, 0x0070, VR::LO, VM::M1, "Manufacturer" },
{ 0x0018, 0x0060, VR::DS, VM::M1, "KVP" },
{ 0x0018, 0x1801, VR::SH, VM::M1, "Time Source" },
{ 0x0028, 0x0050, VR::LO, VM::M1TN, "Manipulated Image" },
{ 0x0028, 0x1401, VR::SQ, VM::M1, "Data Frame Assignment Sequence" },
{ 0x0038, 0x0040, VR::LO, VM::M1, "Discharge Diagnosis Description" },
{ 0x0066, 0x001E, VR::UL, VM::M1, "Number of Vectors" },
{ 0x0070, 0x0008, VR::SQ, VM::M1, "Text Object Sequence" },
{ 0x0072, 0x000A, VR::DT, VM::M1, "Hanging Protocol Creation DateTime" },
{ 0x0076, 0x000E, VR::SQ, VM::M1, "Derivation Implant Assembly Template Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0122[] = {
{ 0x0008, 0x1032, VR::SQ, VM::M1, "Procedure Code Sequence" },
{ 0x0018, 0x1022, VR::SH, VM::M1, "Video Image Format Acquired" },
{ 0x0018, 0x1802, VR::CS, VM::M1, "Time Distribution Protocol" },
{ 0x0028, 0x1402, VR::CS, VM::M1, "Data Path Assignment" },
{ 0x0052, 0x0029, VR::SQ, VM::M1, "Intravascular OCT Frame Content Sequence" },
{ 0x0074, 0x104E, VR::SQ, VM::M1, "Ion Control Point Verification Sequence" },
{ 0x3008, 0x00B0, VR::SQ, VM::M1, "Recorded Wedge Sequence" },
{ 0x300A, 0x00B2, VR::SH, VM::M1, "Treatment Machine Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0123[] = {
{ 0x0018, 0x1023, VR::LO, VM::M1, "Digital Image Format Acquired" },
{ 0x0018, 0x1803, VR::LO, VM::M1, "NTP Source Address" },
{ 0x0020, 0x9213, VR::LO, VM::M1, "Dimension Index Private Creator" },
{ 0x0022, 0x0058, VR::SQ, VM::M1, "Mydriatic Agent Sequence" },
{ 0x0022, 0x1019, VR::FL, VM::M1, "Ophthalmic Axial Length" },
{ 0x0028, 0x1403, VR::US, VM::M1, "Bits Mapped to Color Lookup Table" },
{ 0x0040, 0x003A, VR::SQ, VM::M1, "Assigning Agency or Department Code Sequence" },
{ 0x0052, 0x0028, VR::FD, VM::M1, "Intravascular Longitudinal Distance" },
{ 0x0066, 0x001C, VR::FL, VM::M3, "Center of Rotation" },
{ 0x0072, 0x0008, VR::LO, VM::M1, "Hanging Protocol Creator" },
{ 0x0076, 0x000C, VR::SQ, VM::M1, "Original Implant Assembly Template Sequence" },
{ 0x300A, 0x00B3, VR::CS, VM::M1, "Primary Dosimeter Unit" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0124[] = {
{ 0x0024, 0x0059, VR::CS, VM::M1, "Global Deviation Probability Normals Flag" },
{ 0x0028, 0x1404, VR::SQ, VM::M1, "Blending LUT 1 Sequence" },
{ 0x0066, 0x001B, VR::FL, VM::M3, "Axis of Rotation" },
{ 0x0074, 0x1048, VR::SQ, VM::M1, "Failed Attributes Sequence" },
{ 0x3006, 0x00B8, VR::FL, VM::M1, "ROI Elemental Composition Atomic Mass Fraction" },
{ 0x300A, 0x00B4, VR::DS, VM::M1, "Source-Axis Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0125[] = {
{ 0x0024, 0x0058, VR::SQ, VM::M1, "Test Point Normals Sequence" },
{ 0x0028, 0x1405, VR::CS, VM::M1, "Blending LUT 1 Transfer Function" },
{ 0x0038, 0x0044, VR::SQ, VM::M1, "Discharge Diagnosis Code Sequence" },
{ 0x0066, 0x001A, VR::FL, VM::M6, "Points Bounding Box Coordinates" },
{ 0x0072, 0x000E, VR::SQ, VM::M1, "Hanging Protocol User Identification Code Sequence" },
{ 0x0076, 0x000A, VR::CS, VM::M1, "Implant Assembly Template Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0126[] = {
{ 0x0028, 0x1406, VR::FD, VM::M1, "Blending Weight Constant" },
{ 0x0066, 0x0019, VR::FL, VM::M1, "Maximum Point Distance" },
{ 0x0074, 0x104A, VR::SQ, VM::M1, "Overridden Attributes Sequence" },
{ 0x300A, 0x00B6, VR::SQ, VM::M1, "Beam Limiting Device Sequence" },
{ 0x300C, 0x00B0, VR::SQ, VM::M1, "Referenced Bolus Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0127[] = {
{ 0x0028, 0x1407, VR::US, VM::M3, "Blending Lookup Table Descriptor" },
{ 0x0046, 0x0038, VR::CS, VM::M1, "Lens Segment Type" },
{ 0x0066, 0x0018, VR::FL, VM::M1, "Mean Point Distance" },
{ 0x0072, 0x000C, VR::SQ, VM::M1, "Hanging Protocol Definition Sequence" },
{ 0x0076, 0x0008, VR::SQ, VM::M1, "Replaced Implant Assembly Template Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0128[] = {
{ 0x0014, 0x2014, VR::IS, VM::M1, "Indication Number" },
{ 0x0040, 0x3001, VR::LO, VM::M1, "Confidentiality Constraint on Patient Data Description" },
{ 0x2010, 0x0010, VR::ST, VM::M1, "Image Display Format" },
{ 0x2020, 0x0020, VR::CS, VM::M1, "Polarity" },
{ 0x300A, 0x004B, VR::FL, VM::M1, "Snout Position Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0129[] = {
{ 0x0060, 0x3020, VR::UL, VM::M1TN, "Histogram Data" },
{ 0x3002, 0x0042, VR::DS, VM::M1, "Fluence Data Scale" },
{ 0x3006, 0x0046, VR::IS, VM::M1, "Number of Contour Points" },
{ 0x3008, 0x0048, VR::DS, VM::M1, "Dose Rate Delivered" },
{ 0x300A, 0x004A, VR::DS, VM::M1, "Beam Limiting Device Position Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0130[] = {
{ 0x0014, 0x2016, VR::SH, VM::M1, "Indication Label" },
{ 0x3002, 0x0041, VR::CS, VM::M1, "Fluence Data Source" },
{ 0x3006, 0x0045, VR::DS, VM::M3, "Contour Offset Vector" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0131[] = {
{ 0x3002, 0x0040, VR::SQ, VM::M1, "Fluence Map Sequence" },
{ 0x3006, 0x0044, VR::DS, VM::M1, "Contour Slab Thickness" },
{ 0x300A, 0x0048, VR::SQ, VM::M1, "Beam Limiting Device Tolerance Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0132[] = {
{ 0x300A, 0x004F, VR::FL, VM::M1, "Table Top Pitch Angle Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0133[] = {
{ 0x0014, 0x3050, VR::OX, VM::M1, "Dark Current Counts" },
{ 0x3004, 0x0040, VR::DS, VM::M3, "DVH Normalization Point" },
{ 0x3006, 0x0042, VR::CS, VM::M1, "Contour Geometric Type" },
{ 0x300A, 0x004E, VR::DS, VM::M1, "Table Top Eccentric Angle Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0134[] = {
{ 0x0014, 0x2012, VR::SQ, VM::M1, "Indication Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0135[] = {
{ 0x3004, 0x0042, VR::DS, VM::M1, "DVH Normalization Dose Value" },
{ 0x3006, 0x0040, VR::SQ, VM::M1, "Contour Sequence" },
{ 0x300A, 0x004C, VR::DS, VM::M1, "Patient Support Angle Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0136[] = {
{ 0x0008, 0x0082, VR::SQ, VM::M1, "Institution Code Sequence" },
{ 0x0014, 0x201C, VR::CS, VM::M1, "Indication Disposition" },
{ 0x0018, 0x2010, VR::DS, VM::M2, "Nominal Scanned Pixel Spacing" },
{ 0x0020, 0x00AA, VR::IS, VM::M1, "Report Number" },
{ 0x0040, 0x08EA, VR::SQ, VM::M1, "Measurement Units Code Sequence" },
{ 0x3008, 0x0041, VR::SQ, VM::M1, "Ion Control Point Delivery Sequence" },
{ 0x300A, 0x0043, VR::SH, VM::M1, "Tolerance Table Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0137[] = {
{ 0x0018, 0x0093, VR::DS, VM::M1, "Percent Sampling" },
{ 0x3008, 0x0040, VR::SQ, VM::M1, "Control Point Delivery Sequence" },
{ 0x300A, 0x0042, VR::IS, VM::M1, "Tolerance Table Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0138[] = {
{ 0x0008, 0x0080, VR::LO, VM::M1, "Institution Name" },
{ 0x0014, 0x201E, VR::SQ, VM::M1, "Indication ROI Sequence" },
{ 0x0018, 0x0090, VR::DS, VM::M1, "Data Collection Diameter" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0139[] = {
{ 0x0008, 0x0081, VR::ST, VM::M1, "Institution Address" },
{ 0x0018, 0x0091, VR::IS, VM::M1, "Echo Train Length" },
{ 0x3008, 0x0042, VR::DS, VM::M1, "Specified Meterset" },
{ 0x300A, 0x0040, VR::SQ, VM::M1, "Tolerance Table Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0140[] = {
{ 0x0014, 0x2018, VR::ST, VM::M1, "Indication Description" },
{ 0x0028, 0x6120, VR::SS, VM::M1, "TID Offset" },
{ 0x3008, 0x0045, VR::FL, VM::M1, "Meterset Rate Set" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0141[] = {
{ 0x3008, 0x0044, VR::DS, VM::M1, "Delivered Meterset" },
{ 0x300A, 0x0046, VR::DS, VM::M1, "Beam Limiting Device Angle Tolerance" },
{ 0x300C, 0x0040, VR::SQ, VM::M1, "Referenced Verification Image Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0142[] = {
{ 0x0014, 0x201A, VR::CS, VM::M1TN, "Indication Type" },
{ 0x0018, 0x0094, VR::DS, VM::M1, "Percent Phase Field of View" },
{ 0x3006, 0x0049, VR::IS, VM::M1TN, "Attached Contours" },
{ 0x3008, 0x0047, VR::FL, VM::M1TN, "Scan Spot Metersets Delivered" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0143[] = {
{ 0x0018, 0x0095, VR::DS, VM::M1, "Pixel Bandwidth" },
{ 0x3006, 0x0048, VR::IS, VM::M1, "Contour Number" },
{ 0x3008, 0x0046, VR::FL, VM::M1, "Meterset Rate Delivered" },
{ 0x300A, 0x0044, VR::DS, VM::M1, "Gantry Angle Tolerance" },
{ 0x300C, 0x0042, VR::SQ, VM::M1, "Referenced Reference Image Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0144[] = {
{ 0x0010, 0x2000, VR::LO, VM::M1TN, "Medical Alerts" },
{ 0x0014, 0x2004, VR::IS, VM::M1, "Evaluator Number" },
{ 0x2000, 0x0010, VR::IS, VM::M1, "Number of Copies" },
{ 0x2020, 0x0030, VR::DS, VM::M1, "Requested Image Size" },
{ 0x2030, 0x0020, VR::LO, VM::M1, "Text String" },
{ 0x2100, 0x0500, VR::SQ, VM::M1, "Referenced Print Job Sequence (Pull Stored Print)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0145[] = {
{ 0x0012, 0x0081, VR::LO, VM::M1, "Clinical Trial Protocol Ethics Committee Name" },
{ 0x3002, 0x0052, VR::SH, VM::M1, "Fluence Mode ID" },
{ 0x3004, 0x0054, VR::CS, VM::M1, "DVH Volume Units" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0146[] = {
{ 0x0012, 0x0082, VR::LO, VM::M1, "Clinical Trial Protocol Ethics Committee Approval Number" },
{ 0x0014, 0x2006, VR::PN, VM::M1, "Evaluator Name" },
{ 0x0018, 0x0088, VR::DS, VM::M1, "Spacing Between Slices" },
{ 0x3002, 0x0051, VR::CS, VM::M1, "Fluence Mode" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0147[] = {
{ 0x0012, 0x0083, VR::SQ, VM::M1, "Consent for Clinical Trial Use Sequence" },
{ 0x0018, 0x0089, VR::IS, VM::M1, "Number of Phase Encoding Steps" },
{ 0x3002, 0x0050, VR::SQ, VM::M1, "Primary Fluence Mode Sequence" },
{ 0x3004, 0x0056, VR::IS, VM::M1, "DVH Number of Bins" },
{ 0x3008, 0x005A, VR::IS, VM::M1, "Number of Fractions Delivered" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0148[] = {
{ 0x0012, 0x0084, VR::CS, VM::M1, "Distribution Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0149[] = {
{ 0x0012, 0x0085, VR::CS, VM::M1, "Consent for Distribution Flag" },
{ 0x0014, 0x3040, VR::SQ, VM::M1, "Dark Current Sequence" },
{ 0x3004, 0x0050, VR::SQ, VM::M1, "DVH Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0150[] = {
{ 0x0014, 0x2002, VR::SQ, VM::M1, "Evaluator Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0151[] = {
{ 0x3004, 0x0052, VR::DS, VM::M1, "DVH Dose Scaling" },
{ 0x3006, 0x0050, VR::DS, VM::M3T3N, "Contour Data" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0152[] = {
{ 0x0008, 0x0092, VR::ST, VM::M1, "Referring Physician's Address" },
{ 0x0018, 0x0082, VR::DS, VM::M1, "Inversion Time" },
{ 0x300A, 0x0053, VR::DS, VM::M1, "Table Top Lateral Position Tolerance" },
{ 0x300C, 0x0055, VR::SQ, VM::M1, "Brachy Referenced Dose Reference Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0153[] = {
{ 0x0018, 0x0083, VR::DS, VM::M1, "Number of Averages" },
{ 0x0018, 0x2001, VR::IS, VM::M1TN, "Page Number Vector" },
{ 0x3008, 0x0050, VR::SQ, VM::M1, "Treatment Summary Calculated Dose Reference Sequence" },
{ 0x300A, 0x0052, VR::DS, VM::M1, "Table Top Longitudinal Position Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0154[] = {
{ 0x0008, 0x0090, VR::PN, VM::M1, "Referring Physician's Name" },
{ 0x0018, 0x0080, VR::DS, VM::M1, "Repetition Time" },
{ 0x0018, 0x2002, VR::SH, VM::M1TN, "Frame Label Vector" },
{ 0x300A, 0x0051, VR::DS, VM::M1, "Table Top Vertical Position Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0155[] = {
{ 0x0018, 0x0081, VR::DS, VM::M1, "Echo Time" },
{ 0x0018, 0x2003, VR::DS, VM::M1TN, "Frame Primary Angle Vector" },
{ 0x3008, 0x0052, VR::DS, VM::M1, "Cumulative Dose to Dose Reference" },
{ 0x300A, 0x0050, VR::FL, VM::M1, "Table Top Roll Angle Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0156[] = {
{ 0x0008, 0x0096, VR::SQ, VM::M1, "Referring Physician Identification Sequence" },
{ 0x0014, 0x2008, VR::IS, VM::M1, "Evaluation Attempt" },
{ 0x0018, 0x0086, VR::IS, VM::M1TN, "Echo Number(s)" },
{ 0x0018, 0x2004, VR::DS, VM::M1TN, "Frame Secondary Angle Vector" },
{ 0x0068, 0x6560, VR::FD, VM::M2, "2D Point Coordinates" },
{ 0x300C, 0x0051, VR::IS, VM::M1, "Referenced Dose Reference Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0157[] = {
{ 0x0018, 0x0087, VR::DS, VM::M1, "Magnetic Field Strength" },
{ 0x0018, 0x2005, VR::DS, VM::M1TN, "Slice Location Vector" },
{ 0x3004, 0x0058, VR::DS, VM::M2T2N, "DVH Data" },
{ 0x3008, 0x0054, VR::DA, VM::M1, "First Treatment Date" },
{ 0x300C, 0x0050, VR::SQ, VM::M1, "Referenced Dose Reference Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0158[] = {
{ 0x0008, 0x0094, VR::SH, VM::M1TN, "Referring Physician's Telephone Numbers" },
{ 0x0018, 0x0084, VR::DS, VM::M1, "Imaging Frequency" },
{ 0x0018, 0x2006, VR::SH, VM::M1TN, "Display Window Label Vector" },
{ 0x2000, 0x001E, VR::SQ, VM::M1, "Printer Configuration Sequence" },
{ 0x300A, 0x0055, VR::CS, VM::M1, "RT Plan Relationship" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0159[] = {
{ 0x0018, 0x0085, VR::SH, VM::M1, "Imaged Nucleus" },
{ 0x3008, 0x0056, VR::DA, VM::M1, "Most Recent Treatment Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0160[] = {
{ 0x0014, 0x3075, VR::DS, VM::M1, "Filter Thickness Used in Gain Calibration" },
{ 0x0024, 0x0086, VR::CS, VM::M1, "Foveal Sensitivity Measured" },
{ 0x2000, 0x0020, VR::CS, VM::M1, "Print Priority" },
{ 0x2010, 0x0030, VR::CS, VM::M1, "Annotation Display Format ID" },
{ 0x2030, 0x0010, VR::US, VM::M1, "Annotation Position" },
{ 0x2040, 0x0060, VR::CS, VM::M1, "Overlay Magnification Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0161[] = {
{ 0x0014, 0x3074, VR::LO, VM::M1, "Filter Material Used in Gain Calibration" },
{ 0x0024, 0x0087, VR::FL, VM::M1, "Foveal Sensitivity" },
{ 0x0060, 0x3000, VR::SQ, VM::M1, "Histogram Sequence" },
{ 0x3008, 0x0068, VR::SQ, VM::M1, "Corrected Parameter Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0162[] = {
{ 0x0014, 0x3077, VR::TM, VM::M1, "Time of Gain Calibration" },
{ 0x0020, 0x0080, VR::CS, VM::M1TN, "Masking Image" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0163[] = {
{ 0x0014, 0x3076, VR::DA, VM::M1, "Date of Gain Calibration" },
{ 0x0024, 0x0085, VR::SQ, VM::M1, "Localized Deviation Probability Sequence" },
{ 0x0060, 0x3002, VR::US, VM::M1, "Histogram Number of Bins" },
{ 0x3008, 0x006A, VR::FL, VM::M1, "Correction Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0164[] = {
{ 0x0014, 0x2030, VR::SQ, VM::M1, "Indication Physical Property Sequence" },
{ 0x0014, 0x3071, VR::DS, VM::M1, "KV Used in Gain Calibration" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0165[] = {
{ 0x0014, 0x3070, VR::OX, VM::M1, "Air Counts" },
{ 0x0024, 0x0083, VR::SQ, VM::M1, "Global Deviation Probability Sequence" },
{ 0x0060, 0x3004, VR::XS, VM::M1, "Histogram First Bin Value" },
{ 0x3004, 0x0060, VR::SQ, VM::M1, "DVH Referenced ROI Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0166[] = {
{ 0x0014, 0x2032, VR::SH, VM::M1, "Property Label" },
{ 0x0014, 0x3073, VR::DS, VM::M1, "Number of Frames Used for Integration" },
{ 0x0024, 0x0080, VR::CS, VM::M1, "Corrected Localized Deviation From Normal Probability Calculated" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0167[] = {
{ 0x0014, 0x3072, VR::DS, VM::M1, "MA Used in Gain Calibration" },
{ 0x0024, 0x0081, VR::FL, VM::M1, "Corrected Localized Deviation From Normal Probability" },
{ 0x0060, 0x3006, VR::XS, VM::M1, "Histogram Last Bin Value" },
{ 0x3004, 0x0062, VR::CS, VM::M1, "DVH ROI Contribution Type" },
{ 0x300C, 0x006A, VR::IS, VM::M1, "Referenced Patient Setup Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0168[] = {
{ 0x0018, 0x2030, VR::DS, VM::M1, "Rotation of Scanned Film" },
{ 0x0028, 0x0082, VR::US, VM::M1TN, "Predictor Constants" },
{ 0x0028, 0x2000, VR::OB, VM::M1, "ICC Profile" },
{ 0x3008, 0x0061, VR::AT, VM::M1, "Parameter Sequence Pointer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0169[] = {
{ 0x0060, 0x3008, VR::US, VM::M1, "Histogram Bin Width" },
{ 0x3008, 0x0060, VR::SQ, VM::M1, "Override Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0170[] = {
{ 0x0028, 0x0080, VR::US, VM::M1, "Predictor Rows" },
{ 0x3008, 0x0063, VR::IS, VM::M1, "Parameter Item Index" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0171[] = {
{ 0x0028, 0x0081, VR::US, VM::M1, "Predictor Columns" },
{ 0x3008, 0x0062, VR::AT, VM::M1, "Override Parameter Pointer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0172[] = {
{ 0x0028, 0x6100, VR::SQ, VM::M1, "Mask Subtraction Sequence" },
{ 0x0068, 0x6550, VR::SQ, VM::M1, "2D Point Coordinates Sequence" },
{ 0x3008, 0x0065, VR::AT, VM::M1, "Parameter Pointer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0173[] = {
{ 0x0028, 0x6101, VR::CS, VM::M1, "Mask Operation" },
{ 0x3008, 0x0064, VR::IS, VM::M1, "Measured Dose Reference Number" },
{ 0x300C, 0x0060, VR::SQ, VM::M1, "Referenced Structure Set Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0174[] = {
{ 0x0024, 0x0088, VR::FL, VM::M1, "Visual Field Test Duration" },
{ 0x0028, 0x6102, VR::US, VM::M2T2N, "Applicable Frame Range" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0175[] = {
{ 0x0024, 0x0089, VR::SQ, VM::M1, "Visual Field Test Point Sequence" },
{ 0x3008, 0x0066, VR::ST, VM::M1, "Override Reason" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0176[] = {
{ 0x0024, 0x0096, VR::FL, VM::M1, "Retest Sensitivity Value" },
{ 0x2000, 0x0030, VR::CS, VM::M1, "Medium Type" },
{ 0x2020, 0x0010, VR::US, VM::M1, "Image Box Position" },
{ 0x2040, 0x0070, VR::CS, VM::M1, "Overlay Smoothing Type" },
{ 0x300A, 0x007B, VR::LT, VM::M1, "Fraction Pattern" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0177[] = {
{ 0x0024, 0x0097, VR::SQ, VM::M1, "Visual Field Test Point Normals Sequence" },
{ 0x0060, 0x3010, VR::LO, VM::M1, "Histogram Explanation" },
{ 0x3004, 0x0074, VR::DS, VM::M1, "DVH Mean Dose" },
{ 0x3008, 0x0078, VR::DS, VM::M1, "Start Meterset" },
{ 0x300A, 0x007A, VR::IS, VM::M1, "Repeat Fraction Cycle Length" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0178[] = {
{ 0x0024, 0x0094, VR::FL, VM::M1, "Sensitivity Value" },
{ 0x2040, 0x0072, VR::CS, VM::M1, "Overlay or Image Magnification" },
{ 0x300A, 0x0079, VR::IS, VM::M1, "Number of Fraction Pattern Digits Per Day" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0179[] = {
{ 0x0024, 0x0095, VR::CS, VM::M1, "Retest Stimulus Seen" },
{ 0x3008, 0x007A, VR::DS, VM::M1, "End Meterset" },
{ 0x300A, 0x0078, VR::IS, VM::M1, "Number of Fractions Planned" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0180[] = {
{ 0x0024, 0x0092, VR::FL, VM::M1, "Age Corrected Sensitivity Deviation Value" },
{ 0x0076, 0x00C0, VR::US, VM::M1, "Component 2 Referenced Mating Feature ID" },
{ 0x2040, 0x0074, VR::US, VM::M1, "Magnify to Number of Columns" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0181[] = {
{ 0x0014, 0x3060, VR::SQ, VM::M1, "Gain Correction Reference Sequence" },
{ 0x0024, 0x0093, VR::CS, VM::M1, "Stimulus Results" },
{ 0x3004, 0x0070, VR::DS, VM::M1, "DVH Minimum Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0182[] = {
{ 0x0024, 0x0090, VR::FL, VM::M1, "Visual Field Test Point X-Coordinate" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0183[] = {
{ 0x0024, 0x0091, VR::FL, VM::M1, "Visual Field Test Point Y-Coordinate" },
{ 0x3004, 0x0072, VR::DS, VM::M1, "DVH Maximum Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0184[] = {
{ 0x0018, 0x2020, VR::CS, VM::M1, "Digitizing Device Transport Direction" },
{ 0x0028, 0x0092, VR::US, VM::M1, "Block Columns" },
{ 0x0028, 0x6114, VR::FL, VM::M2, "Mask Sub-pixel Shift" },
{ 0x0040, 0x08DA, VR::SQ, VM::M1, "Coordinate System Axis Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0185[] = {
{ 0x0028, 0x0093, VR::US, VM::M1, "Row Overlap" },
{ 0x0068, 0x6545, VR::SQ, VM::M1, "Planning Landmark Identification Code Sequence" },
{ 0x3008, 0x0070, VR::SQ, VM::M1, "Calculated Dose Reference Sequence" },
{ 0x300A, 0x0072, VR::LO, VM::M1, "Fraction Group Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0186[] = {
{ 0x0028, 0x0090, VR::CS, VM::M1, "Blocked Pixels" },
{ 0x0040, 0x08D8, VR::SQ, VM::M1, "Pixel Spacing Sequence" },
{ 0x300A, 0x0071, VR::IS, VM::M1, "Fraction Group Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0187[] = {
{ 0x0028, 0x0091, VR::US, VM::M1, "Block Rows" },
{ 0x3008, 0x0072, VR::IS, VM::M1, "Calculated Dose Reference Number" },
{ 0x300A, 0x0070, VR::SQ, VM::M1, "Fraction Group Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0188[] = {
{ 0x0028, 0x6110, VR::US, VM::M1TN, "Mask Frame Numbers" },
{ 0x0068, 0x6540, VR::LO, VM::M1, "Planning Landmark Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0189[] = {
{ 0x3008, 0x0074, VR::ST, VM::M1, "Calculated Dose Reference Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0190[] = {
{ 0x0024, 0x0098, VR::FL, VM::M1, "Quantified Defect" },
{ 0x0028, 0x0094, VR::US, VM::M1, "Column Overlap" },
{ 0x0028, 0x6112, VR::US, VM::M1, "Contrast Frame Averaging" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0191[] = {
{ 0x3008, 0x0076, VR::DS, VM::M1, "Calculated Dose Reference Dose Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0192[] = {
{ 0x0040, 0x2001, VR::LO, VM::M1, "Reason for the Imaging Service Request" },
{ 0x3002, 0x0002, VR::SH, VM::M1, "RT Image Label" },
{ 0x3004, 0x0004, VR::CS, VM::M1, "Dose Type" },
{ 0x3006, 0x0006, VR::ST, VM::M1, "Structure Set Description" },
{ 0x300A, 0x000A, VR::CS, VM::M1, "Plan Intent" },
{ 0x300C, 0x000C, VR::IS, VM::M1, "Referenced Brachy Application Setup Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0193[] = {
{ 0x2000, 0x0040, VR::CS, VM::M1, "Film Destination" },
{ 0x2010, 0x0050, VR::CS, VM::M1, "Film Size ID" },
{ 0x2050, 0x0010, VR::SQ, VM::M1, "Presentation LUT Sequence" },
{ 0x2100, 0x0140, VR::AE, VM::M1, "Destination AE" },
{ 0x3002, 0x0003, VR::LO, VM::M1, "RT Image Name" },
{ 0x300A, 0x000B, VR::LO, VM::M1TN, "Treatment Sites" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0194[] = {
{ 0x0010, 0x1090, VR::LO, VM::M1, "Medical Record Locator" },
{ 0x3004, 0x0006, VR::LO, VM::M1, "Dose Comment" },
{ 0x3006, 0x0004, VR::LO, VM::M1, "Structure Set Name" },
{ 0x300C, 0x000E, VR::IS, VM::M1, "Referenced Source Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0195[] = {
{ 0x0078, 0x00B8, VR::US, VM::M1, "Implant Template Group Variation Dimension Rank" },
{ 0x2010, 0x0052, VR::CS, VM::M1, "Printer Resolution ID" },
{ 0x300A, 0x0009, VR::LO, VM::M1TN, "Treatment Protocols" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0196[] = {
{ 0x0018, 0x9296, VR::FD, VM::M1, "Chemical Shift Maximum Integration Limit in ppm" },
{ 0x0040, 0x2005, VR::TM, VM::M1, "Issue Time of Imaging Service Request" },
{ 0x3006, 0x0002, VR::SH, VM::M1, "Structure Set Label" },
{ 0x300A, 0x000E, VR::ST, VM::M1, "Prescription Description" },
{ 0x300C, 0x0008, VR::DS, VM::M1, "Start Cumulative Meterset Weight" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0197[] = {
{ 0x0014, 0x3011, VR::DS, VM::M1, "Internal Detector Frame Time" },
{ 0x0040, 0x2004, VR::DA, VM::M1, "Issue Date of Imaging Service Request" },
{ 0x0046, 0x0080, VR::SQ, VM::M1, "Flat Keratometric Axis Sequence" },
{ 0x0076, 0x00B0, VR::US, VM::M1, "Component 2 Referenced Mating Feature Set ID" },
{ 0x2010, 0x0054, VR::CS, VM::M1, "Default Printer Resolution ID" },
{ 0x3004, 0x0001, VR::CS, VM::M1, "DVH Type" },
{ 0x300C, 0x0009, VR::DS, VM::M1, "End Cumulative Meterset Weight" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0198[] = {
{ 0x0014, 0x3012, VR::DS, VM::M1, "Number of Frames Integrated" },
{ 0x0040, 0x2007, VR::SH, VM::M1, "Filler Order Number / Imaging Service Request (Retired)" },
{ 0x3002, 0x0004, VR::ST, VM::M1, "RT Image Description" },
{ 0x3004, 0x0002, VR::CS, VM::M1, "Dose Units" },
{ 0x300A, 0x000C, VR::CS, VM::M1, "RT Plan Geometry" },
{ 0x300C, 0x000A, VR::SQ, VM::M1, "Referenced Brachy Application Setup Sequence" },
{ 0x300E, 0x0008, VR::PN, VM::M1, "Reviewer Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0199[] = {
{ 0x0018, 0x9295, VR::FD, VM::M1, "Chemical Shift Minimum Integration Limit in ppm" },
{ 0x0040, 0x2006, VR::SH, VM::M1, "Placer Order Number / Imaging Service Request (Retired)" },
{ 0x0054, 0x0090, VR::US, VM::M1TN, "Angular View Vector" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0200[] = {
{ 0x0040, 0x2009, VR::SH, VM::M1, "Order Enterer's Location" },
{ 0x3002, 0x000A, VR::CS, VM::M1, "Reported Values Origin" },
{ 0x3004, 0x000C, VR::DS, VM::M2TN, "Grid Frame Offset Vector" },
{ 0x300A, 0x0002, VR::SH, VM::M1, "RT Plan Label" },
{ 0x300A, 0x0412, VR::FL, VM::M3, "Control Point Orientation" },
{ 0x300C, 0x0004, VR::SQ, VM::M1, "Referenced Beam Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0201[] = {
{ 0x0008, 0x3001, VR::SQ, VM::M1, "Alternate Representation Sequence" },
{ 0x0040, 0x2008, VR::PN, VM::M1, "Order Entered By" },
{ 0x0078, 0x00B2, VR::LO, VM::M1, "Implant Template Group Variation Dimension Name" },
{ 0x300A, 0x0003, VR::LO, VM::M1, "RT Plan Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0202[] = {
{ 0x0008, 0x1080, VR::LO, VM::M1TN, "Admitting Diagnoses Description" },
{ 0x0018, 0x1090, VR::IS, VM::M1, "Cardiac Number of Images" },
{ 0x0018, 0x1480, VR::DS, VM::M1, "Tomo Time" },
{ 0x3004, 0x000E, VR::DS, VM::M1, "Dose Grid Scaling" },
{ 0x300A, 0x0410, VR::SQ, VM::M1, "Motion Synchronization Sequence" },
{ 0x300C, 0x0006, VR::IS, VM::M1, "Referenced Beam Number" },
{ 0x300E, 0x0004, VR::DA, VM::M1, "Review Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0203[] = {
{ 0x0078, 0x00B0, VR::SQ, VM::M1, "Implant Template Group Variation Dimension Sequence" },
{ 0x300C, 0x0007, VR::IS, VM::M1, "Referenced Reference Image Number" },
{ 0x300E, 0x0005, VR::TM, VM::M1, "Review Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0204[] = {
{ 0x3002, 0x000E, VR::DS, VM::M1, "X-Ray Image Receptor Angle" },
{ 0x3004, 0x0008, VR::DS, VM::M3, "Normalization Point" },
{ 0x300A, 0x0006, VR::DA, VM::M1, "RT Plan Date" },
{ 0x300E, 0x0002, VR::CS, VM::M1, "Approval Status" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0205[] = {
{ 0x0068, 0x6530, VR::US, VM::M1, "Planning Landmark ID" },
{ 0x0078, 0x00B6, VR::US, VM::M1, "Referenced Implant Template Group Member ID" },
{ 0x300A, 0x0007, VR::TM, VM::M1, "RT Plan Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0206[] = {
{ 0x0008, 0x1084, VR::SQ, VM::M1, "Admitting Diagnoses Code Sequence" },
{ 0x0018, 0x1094, VR::IS, VM::M1, "Trigger Window" },
{ 0x3002, 0x000C, VR::CS, VM::M1, "RT Image Plane" },
{ 0x3004, 0x000A, VR::CS, VM::M1, "Dose Summation Type" },
{ 0x3006, 0x0008, VR::DA, VM::M1, "Structure Set Date" },
{ 0x300A, 0x0004, VR::ST, VM::M1, "RT Plan Description" },
{ 0x300C, 0x0002, VR::SQ, VM::M1, "Referenced RT Plan Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0207[] = {
{ 0x0078, 0x00B4, VR::SQ, VM::M1, "Implant Template Group Variation Dimension Rank Sequence" },
{ 0x3002, 0x000D, VR::DS, VM::M3, "X-Ray Image Receptor Translation" },
{ 0x3006, 0x0009, VR::TM, VM::M1, "Structure Set Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0208[] = {
{ 0x0046, 0x0095, VR::CS, VM::M1, "Optotype Presentation" },
{ 0x2040, 0x0011, VR::US, VM::M1T99, "Referenced Overlay Plane Groups" },
{ 0x3002, 0x0012, VR::DS, VM::M2, "RT Image Position" },
{ 0x3004, 0x0014, VR::CS, VM::M1T3, "Tissue Heterogeneity Correction" },
{ 0x3006, 0x0016, VR::SQ, VM::M1, "Contour Image Sequence" },
{ 0x300A, 0x001A, VR::DS, VM::M1, "Nominal Prior Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0209[] = {
{ 0x0040, 0x2010, VR::SH, VM::M1, "Order Callback Phone Number" },
{ 0x0040, 0x2400, VR::LT, VM::M1, "Imaging Service Request Comments" },
{ 0x0046, 0x0094, VR::CS, VM::M1, "Optotype" },
{ 0x2000, 0x0050, VR::LO, VM::M1, "Film Session Label" },
{ 0x2010, 0x0040, VR::CS, VM::M1, "Film Orientation" },
{ 0x2040, 0x0010, VR::SQ, VM::M1, "Referenced Overlay Plane Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0210[] = {
{ 0x0010, 0x1080, VR::LO, VM::M1, "Military Rank" },
{ 0x0018, 0x1088, VR::IS, VM::M1, "Heart Rate" },
{ 0x0046, 0x0097, VR::SQ, VM::M1, "Subjective Refraction Right Eye Sequence" },
{ 0x3002, 0x0010, VR::DS, VM::M6, "RT Image Orientation" },
{ 0x3006, 0x0014, VR::SQ, VM::M1, "RT Referenced Series Sequence" },
{ 0x300A, 0x0018, VR::DS, VM::M3, "Dose Reference Point Coordinates" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0211[] = {
{ 0x0010, 0x1081, VR::LO, VM::M1, "Branch of Service" },
{ 0x3002, 0x0011, VR::DS, VM::M2, "Image Plane Pixel Spacing" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0212[] = {
{ 0x3004, 0x0010, VR::SQ, VM::M1, "RT Dose ROI Sequence" },
{ 0x3006, 0x0012, VR::SQ, VM::M1, "RT Referenced Study Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0213[] = {
{ 0x0076, 0x00A0, VR::US, VM::M1, "Component 2 Referenced ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0214[] = {
{ 0x0040, 0x2017, VR::LO, VM::M1, "Filler Order Number / Imaging Service Request" },
{ 0x0054, 0x0081, VR::US, VM::M1, "Number of Slices" },
{ 0x3004, 0x0012, VR::DS, VM::M1, "Dose Value" },
{ 0x3006, 0x0010, VR::SQ, VM::M1, "Referenced Frame of Reference Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0215[] = {
{ 0x0040, 0x2016, VR::LO, VM::M1, "Placer Order Number / Imaging Service Request" },
{ 0x0046, 0x0092, VR::CS, VM::M1, "Background Color" },
{ 0x0054, 0x0080, VR::US, VM::M1TN, "Slice Vector" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0216[] = {
{ 0x0008, 0x3010, VR::UI, VM::M1, "Irradiation Event UID" },
{ 0x0018, 0x1082, VR::IS, VM::M1, "High R-R Value" },
{ 0x0040, 0xA601, VR::CS, VM::M1, "Observer Context Flag (Trial)" },
{ 0x3008, 0x0010, VR::SQ, VM::M1, "Measured Dose Reference Sequence" },
{ 0x300A, 0x0012, VR::IS, VM::M1, "Dose Reference Number" },
{ 0x300A, 0x0402, VR::ST, VM::M1, "Setup Image Comment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0217[] = {
{ 0x0018, 0x1083, VR::IS, VM::M1, "Intervals Acquired" },
{ 0x0040, 0xA600, VR::CS, VM::M1, "Observation Subject Context Flag (Trial)" },
{ 0x300A, 0x0013, VR::UI, VM::M1, "Dose Reference UID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0218[] = {
{ 0x0008, 0x1090, VR::LO, VM::M1, "Manufacturer's Model Name" },
{ 0x0018, 0x1080, VR::CS, VM::M1, "Beat Rejection Flag" },
{ 0x0018, 0x1490, VR::CS, VM::M1, "Tomo Type" },
{ 0x0040, 0xA603, VR::CS, VM::M1, "Procedure Context Flag (Trial)" },
{ 0x3008, 0x0012, VR::ST, VM::M1, "Measured Dose Description" },
{ 0x300A, 0x0010, VR::SQ, VM::M1, "Dose Reference Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0219[] = {
{ 0x0018, 0x1081, VR::IS, VM::M1, "Low R-R Value" },
{ 0x0018, 0x1491, VR::CS, VM::M1, "Tomo Class" },
{ 0x0078, 0x00A0, VR::FD, VM::M4, "2D Implant Template Group Member Matching Axes" },
{ 0x300A, 0x0401, VR::SQ, VM::M1, "Referenced Setup Image Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0220[] = {
{ 0x0018, 0x1086, VR::IS, VM::M1, "Skip Beats" },
{ 0x3008, 0x0014, VR::CS, VM::M1, "Measured Dose Type" },
{ 0x300A, 0x0016, VR::LO, VM::M1, "Dose Reference Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0221[] = {
{ 0x0046, 0x0098, VR::SQ, VM::M1, "Subjective Refraction Left Eye Sequence" },
{ 0x0068, 0x6520, VR::SQ, VM::M1, "Planning Landmark Plane Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0222[] = {
{ 0x0018, 0x1084, VR::IS, VM::M1, "Intervals Rejected" },
{ 0x3008, 0x0016, VR::DS, VM::M1, "Measured Dose Value" },
{ 0x300A, 0x0014, VR::CS, VM::M1, "Dose Reference Structure Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0223[] = {
{ 0x0018, 0x1085, VR::LO, VM::M1, "PVC Rejection" },
{ 0x0018, 0x1495, VR::IS, VM::M1, "Number of Tomosynthesis Source Images" },
{ 0x300A, 0x0015, VR::CS, VM::M1, "Nominal Beam Energy Unit" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0224[] = {
{ 0x2000, 0x0061, VR::IS, VM::M1, "Maximum Memory Allocation" },
{ 0x3002, 0x0022, VR::DS, VM::M1, "Radiation Machine SAD" },
{ 0x3006, 0x0026, VR::LO, VM::M1, "ROI Name" },
{ 0x300A, 0x002A, VR::DS, VM::M1, "Organ at Risk Full-volume Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0225[] = {
{ 0x2000, 0x0060, VR::IS, VM::M1, "Memory Allocation" },
{ 0x2020, 0x0040, VR::CS, VM::M1, "Requested Decimate/Crop Behavior" },
{ 0x2040, 0x0020, VR::SQ, VM::M1, "Overlay Pixel Data Sequence" },
{ 0x2100, 0x0160, VR::SH, VM::M1, "Owner ID" },
{ 0x300A, 0x002B, VR::DS, VM::M1, "Organ at Risk Limit Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0226[] = {
{ 0x2000, 0x0063, VR::CS, VM::M1, "Collation Flag" },
{ 0x3002, 0x0020, VR::SH, VM::M1, "Radiation Machine Name" },
{ 0x3006, 0x0024, VR::UI, VM::M1, "Referenced Frame of Reference UID" },
{ 0x3008, 0x002A, VR::CS, VM::M1, "Treatment Termination Status" },
{ 0x300A, 0x0028, VR::DS, VM::M1, "Target Underdose Volume Fraction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0227[] = {
{ 0x2000, 0x0062, VR::CS, VM::M1, "Color Image Printing Flag" },
{ 0x3008, 0x002B, VR::SH, VM::M1, "Treatment Termination Code" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0228[] = {
{ 0x2000, 0x0065, VR::CS, VM::M1, "Annotation Flag" },
{ 0x3002, 0x0026, VR::DS, VM::M1, "RT Image SID" },
{ 0x3006, 0x0022, VR::IS, VM::M1, "ROI Number" },
{ 0x3008, 0x002C, VR::CS, VM::M1, "Treatment Verification Status" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0229[] = {
{ 0x0076, 0x0090, VR::US, VM::M1, "Component 1 Referenced Mating Feature ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0230[] = {
{ 0x2000, 0x0067, VR::CS, VM::M1, "Image Overlay Flag" },
{ 0x3002, 0x0024, VR::DS, VM::M1, "Radiation Machine SSD" },
{ 0x3006, 0x0020, VR::SQ, VM::M1, "Structure Set ROI Sequence" },
{ 0x300A, 0x002C, VR::DS, VM::M1, "Organ at Risk Maximum Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0231[] = {
{ 0x300A, 0x002D, VR::DS, VM::M1, "Organ at Risk Overdose Volume Fraction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0232[] = {
{ 0x0028, 0x3000, VR::SQ, VM::M1, "Modality LUT Sequence" },
{ 0x2000, 0x0069, VR::CS, VM::M1, "Presentation LUT Flag" },
{ 0x3008, 0x0020, VR::SQ, VM::M1, "Treatment Session Beam Sequence" },
{ 0x300A, 0x0022, VR::DS, VM::M1, "Delivery Warning Dose" },
{ 0x300A, 0x0432, VR::CS, VM::M1, "Applicator Aperture Shape" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0233[] = {
{ 0x3008, 0x0021, VR::SQ, VM::M1, "Treatment Session Ion Beam Sequence" },
{ 0x300A, 0x0023, VR::DS, VM::M1, "Delivery Maximum Dose" },
{ 0x300A, 0x0433, VR::FL, VM::M1, "Applicator Opening" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0234[] = {
{ 0x0028, 0x1080, VR::CS, VM::M1, "Gray Scale" },
{ 0x0028, 0x3002, VR::XS, VM::M3, "LUT Descriptor" },
{ 0x3002, 0x0028, VR::DS, VM::M1, "Source to Reference Object Distance" },
{ 0x3006, 0x002C, VR::DS, VM::M1, "ROI Volume" },
{ 0x3008, 0x0022, VR::IS, VM::M1, "Current Fraction Number" },
{ 0x300A, 0x0020, VR::CS, VM::M1, "Dose Reference Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0235[] = {
{ 0x0028, 0x3003, VR::LO, VM::M1, "LUT Explanation" },
{ 0x0078, 0x0090, VR::FD, VM::M2, "2D Implant Template Group Member Matching Point" },
{ 0x2000, 0x006A, VR::CS, VM::M1, "Image Box Presentation LUT Flag" },
{ 0x3002, 0x0029, VR::IS, VM::M1, "Fraction Number" },
{ 0x300A, 0x0021, VR::DS, VM::M1, "Constraint Weight" },
{ 0x300A, 0x0431, VR::SQ, VM::M1, "Applicator Geometry Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0236[] = {
{ 0x0028, 0x3004, VR::LO, VM::M1, "Modality LUT Type" },
{ 0x3006, 0x002A, VR::IS, VM::M3, "ROI Display Color" },
{ 0x3008, 0x0024, VR::DA, VM::M1, "Treatment Control Point Date" },
{ 0x300A, 0x0026, VR::DS, VM::M1, "Target Prescription Dose" },
{ 0x300A, 0x0436, VR::FL, VM::M1, "Source to Applicator Mounting Position Distance" },
{ 0x300C, 0x0020, VR::SQ, VM::M1, "Referenced Fraction Group Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0237[] = {
{ 0x0040, 0xA224, VR::ST, VM::M1, "Identification Description (Trial)" },
{ 0x0068, 0x6510, VR::SQ, VM::M1, "Planning Landmark Line Sequence" },
{ 0x3008, 0x0025, VR::TM, VM::M1, "Treatment Control Point Time" },
{ 0x300A, 0x0027, VR::DS, VM::M1, "Target Maximum Dose" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0238[] = {
{ 0x0028, 0x3006, VR::OB, VM::M1, "LUT Data" },
{ 0x3006, 0x0028, VR::ST, VM::M1, "ROI Description" },
{ 0x300A, 0x0434, VR::FL, VM::M1, "Applicator Opening X" },
{ 0x300C, 0x0022, VR::IS, VM::M1, "Referenced Fraction Group Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0239[] = {
{ 0x300A, 0x0025, VR::DS, VM::M1, "Target Minimum Dose" },
{ 0x300A, 0x0435, VR::FL, VM::M1, "Applicator Opening Y" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0240[] = {
{ 0x0014, 0x3024, VR::DS, VM::M1, "Horizontal Offset of Sensor" },
{ 0x0022, 0x1090, VR::SQ, VM::M1, "IOL Power Sequence" },
{ 0x0070, 0x0083, VR::TM, VM::M1, "Presentation Creation Time" },
{ 0x3002, 0x0032, VR::DS, VM::M1, "Meterset Exposure" },
{ 0x3006, 0x0036, VR::CS, VM::M1, "ROI Generation Algorithm" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0241[] = {
{ 0x0020, 0x3401, VR::CS, VM::M1, "Modifying Device ID" },
{ 0x0070, 0x0082, VR::DA, VM::M1, "Presentation Creation Date" },
{ 0x0072, 0x0080, VR::SQ, VM::M1, "Selector Code Sequence Value" },
{ 0x2010, 0x0060, VR::CS, VM::M1, "Magnification Type" },
{ 0x2020, 0x0050, VR::CS, VM::M1, "Requested Resolution ID" },
{ 0x2050, 0x0020, VR::CS, VM::M1, "Presentation LUT Shape" },
{ 0x2100, 0x0170, VR::IS, VM::M1, "Number of Films" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0242[] = {
{ 0x0014, 0x3026, VR::DS, VM::M1, "Vertical Offset of Sensor" },
{ 0x0020, 0x3402, VR::CS, VM::M1, "Modified Image ID" },
{ 0x0022, 0x1092, VR::SQ, VM::M1, "Lens Constant Sequence" },
{ 0x0070, 0x0081, VR::LO, VM::M1, "Content Description" },
{ 0x3002, 0x0030, VR::SQ, VM::M1, "Exposure Sequence" },
{ 0x3008, 0x003A, VR::DS, VM::M1, "Specified Treatment Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0243[] = {
{ 0x0020, 0x3403, VR::DA, VM::M1, "Modified Image Date" },
{ 0x0022, 0x1093, VR::LO, VM::M1, "IOL Manufacturer" },
{ 0x0070, 0x0080, VR::CS, VM::M1, "Content Label" },
{ 0x3008, 0x003B, VR::DS, VM::M1, "Delivered Treatment Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0244[] = {
{ 0x0014, 0x3020, VR::SQ, VM::M1, "Detector Temperature Sequence" },
{ 0x0020, 0x3404, VR::LO, VM::M1, "Modifying Device Manufacturer" },
{ 0x0022, 0x1094, VR::LO, VM::M1, "Lens Constant Description" },
{ 0x0070, 0x0087, VR::SQ, VM::M1, "Alternate Content Description Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0245[] = {
{ 0x0020, 0x3405, VR::TM, VM::M1, "Modified Image Time" },
{ 0x0070, 0x0086, VR::SQ, VM::M1, "Content Creator's Identification Code Sequence" },
{ 0x0076, 0x0080, VR::US, VM::M1, "Component 1 Referenced Mating Feature Set ID" },
{ 0x3006, 0x0033, VR::CS, VM::M1, "RT ROI Relationship" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0246[] = {
{ 0x0014, 0x3022, VR::DS, VM::M1, "Sensor Name" },
{ 0x0020, 0x3406, VR::LO, VM::M1, "Modified Image Description" },
{ 0x0022, 0x1096, VR::SQ, VM::M1, "Keratometry Measurement Type Code Sequence" },
{ 0x3002, 0x0034, VR::DS, VM::M4, "Diaphragm Position" },
{ 0x3006, 0x0030, VR::SQ, VM::M1, "RT Related ROI Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0247[] = {
{ 0x0070, 0x0084, VR::PN, VM::M1, "Content Creator's Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0248[] = {
{ 0x0028, 0x3010, VR::SQ, VM::M1, "VOI LUT Sequence" },
{ 0x3008, 0x0030, VR::SQ, VM::M1, "Referenced Treatment Record Sequence" },
{ 0x300A, 0x0422, VR::ST, VM::M1, "General Accessory Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0249[] = {
{ 0x300A, 0x0423, VR::CS, VM::M1, "General Accessory Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0250[] = {
{ 0x0028, 0x1090, VR::CS, VM::M1, "Recommended Viewing Mode" },
{ 0x3008, 0x0032, VR::DS, VM::M1, "Specified Primary Meterset" },
{ 0x300A, 0x0420, VR::SQ, VM::M1, "General Accessory Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0251[] = {
{ 0x3008, 0x0033, VR::DS, VM::M1, "Specified Secondary Meterset" },
{ 0x300A, 0x0421, VR::SH, VM::M1, "General Accessory ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0252[] = {
{ 0x0014, 0x3028, VR::DS, VM::M1, "Sensor Temperature" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0253[] = {
{ 0x0068, 0x6500, VR::SQ, VM::M1, "Planning Landmark Point Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0254[] = {
{ 0x3006, 0x0038, VR::LO, VM::M1, "ROI Generation Description" },
{ 0x3008, 0x0036, VR::DS, VM::M1, "Delivered Primary Meterset" },
{ 0x300A, 0x0424, VR::IS, VM::M1, "General Accessory Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0255[] = {
{ 0x3006, 0x0039, VR::SQ, VM::M1, "ROI Contour Sequence" },
{ 0x3008, 0x0037, VR::DS, VM::M1, "Delivered Secondary Meterset" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0256[] = {
{ 0x0008, 0x010C, VR::UI, VM::M1, "Coding Scheme UID" },
{ 0x0014, 0x4014, VR::DS, VM::M1, "Element Dimension A" },
{ 0x0024, 0x0120, VR::CS, VM::M1, "Screening Baseline Measured" },
{ 0x0040, 0x0554, VR::UI, VM::M1, "Specimen UID" },
{ 0x0040, 0x4040, VR::CS, VM::M1, "Raw Data Handling" },
{ 0x4010, 0x1051, VR::LO, VM::M1, "Itinerary ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0257[] = {
{ 0x0008, 0x010D, VR::UI, VM::M1, "Context Group Extension Creator UID" },
{ 0x0014, 0x4015, VR::DS, VM::M1, "Element Dimension B" },
{ 0x0040, 0x0555, VR::SQ, VM::M1, "Acquisition Context Sequence" },
{ 0x0040, 0x4041, VR::CS, VM::M1, "Input Readiness State" },
{ 0x0400, 0x0115, VR::OB, VM::M1, "Certificate of Signer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0258[] = {
{ 0x0014, 0x4016, VR::DS, VM::M1, "Element Pitch" },
{ 0x0024, 0x0122, VR::SQ, VM::M1, "Screening Baseline Measured Sequence" },
{ 0x0040, 0x0556, VR::ST, VM::M1, "Acquisition Context Description" },
{ 0x4010, 0x1053, VR::LO, VM::M1, "Itinerary ID Assigning Authority" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0259[] = {
{ 0x0008, 0x010F, VR::CS, VM::M1, "Context Identifier" },
{ 0x0014, 0x4017, VR::DS, VM::M1, "Measured Beam Dimension A" },
{ 0x0018, 0x115E, VR::DS, VM::M1, "Image and Fluoroscopy Area Dose Product" },
{ 0x4010, 0x1052, VR::SH, VM::M1, "Itinerary ID Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0260[] = {
{ 0x0014, 0x4010, VR::SQ, VM::M1, "Transmit Transducer Sequence" },
{ 0x0018, 0x9351, VR::FL, VM::M1, "Calcium Scoring Mass Factor Patient" },
{ 0x0024, 0x0124, VR::CS, VM::M1, "Screening Baseline Type" },
{ 0x0040, 0x0550, VR::SQ, VM::M1, "Specimen Sequence" },
{ 0x0040, 0x1101, VR::SQ, VM::M1, "Person Identification Code Sequence" },
{ 0x0046, 0x0146, VR::FD, VM::M1, "Sphere Power" },
{ 0x0100, 0x0410, VR::CS, VM::M1, "SOP Instance Status" },
{ 0x0400, 0x0110, VR::CS, VM::M1, "Certificate Type" },
{ 0x0400, 0x0500, VR::SQ, VM::M1, "Encrypted Attributes Sequence" },
{ 0x4010, 0x1055, VR::SH, VM::M1, "Route ID Assigning Authority" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0261[] = {
{ 0x0014, 0x4011, VR::SQ, VM::M1, "Receive Transducer Sequence" },
{ 0x0018, 0x9740, VR::US, VM::M1, "Number of Subsets" },
{ 0x0040, 0x0551, VR::LO, VM::M1, "Specimen Identifier" },
{ 0x0046, 0x0147, VR::FD, VM::M1, "Cylinder Power" },
{ 0x4010, 0x1054, VR::SH, VM::M1, "Route ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0262[] = {
{ 0x0008, 0x114B, VR::SQ, VM::M1, "Referenced Real World Value Mapping Instance Sequence" },
{ 0x0014, 0x4012, VR::US, VM::M1, "Number of Elements" },
{ 0x0018, 0x9353, VR::FL, VM::M1, "Energy Weighting Factor" },
{ 0x0024, 0x0126, VR::FL, VM::M1, "Screening Baseline Value" },
{ 0x0040, 0x0552, VR::SQ, VM::M1, "Specimen Description Sequence (Trial)" },
{ 0x0040, 0x1103, VR::LO, VM::M1TN, "Person's Telephone Numbers" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0263[] = {
{ 0x0008, 0x010B, VR::CS, VM::M1, "Context Group Extension Flag" },
{ 0x0008, 0x114A, VR::SQ, VM::M1, "Referenced Instance Sequence" },
{ 0x0014, 0x4013, VR::CS, VM::M1, "Element Shape" },
{ 0x0018, 0x115A, VR::CS, VM::M1, "Radiation Mode" },
{ 0x0018, 0x9352, VR::FL, VM::M3, "Calcium Scoring Mass Factor Device" },
{ 0x0040, 0x0553, VR::ST, VM::M1, "Specimen Description (Trial)" },
{ 0x0040, 0x1102, VR::ST, VM::M1, "Person's Address" },
{ 0x0046, 0x0145, VR::SQ, VM::M1, "Referenced Refractive Measurements Sequence" },
{ 0x4010, 0x1056, VR::CS, VM::M1, "Inbound  Arrival Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0264[] = {
{ 0x0008, 0x0104, VR::LO, VM::M1, "Code Meaning" },
{ 0x0008, 0x1145, VR::SQ, VM::M1, "Referenced Curve Sequence" },
{ 0x0008, 0x4000, VR::LT, VM::M1, "Identifying Comments" },
{ 0x0014, 0x401C, VR::DS, VM::M1, "Measured Bandwidth" },
{ 0x0018, 0x1155, VR::CS, VM::M1, "Radiation Setting" },
{ 0x4010, 0x1059, VR::CS, VM::M1, "Carrier ID Assigning Authority" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0265[] = {
{ 0x0008, 0x0105, VR::CS, VM::M1, "Mapping Resource" },
{ 0x0018, 0x1154, VR::DS, VM::M1, "Average Pulse Width" },
{ 0x0018, 0x5050, VR::IS, VM::M1, "Depth of Scan Field" },
{ 0x4010, 0x1058, VR::SH, VM::M1, "Carrier ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0266[] = {
{ 0x0008, 0x0106, VR::DT, VM::M1, "Context Group Version" },
{ 0x0068, 0x64F0, VR::FD, VM::M3, "2D Degree of Freedom Axis" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0267[] = {
{ 0x0008, 0x0107, VR::DT, VM::M1, "Context Group Local Version" },
{ 0x0018, 0x1156, VR::CS, VM::M1, "Rectification Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0268[] = {
{ 0x0008, 0x0100, VR::SH, VM::M1, "Code Value" },
{ 0x0014, 0x4018, VR::DS, VM::M1, "Measured Beam Dimension B" },
{ 0x0018, 0x1151, VR::IS, VM::M1, "X-Ray Tube Current" },
{ 0x0018, 0x9749, VR::SQ, VM::M1, "PET Reconstruction Sequence" },
{ 0x0028, 0x0120, VR::XS, VM::M1, "Pixel Padding Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0269[] = {
{ 0x0008, 0x1140, VR::SQ, VM::M1, "Referenced Image Sequence" },
{ 0x0014, 0x4019, VR::DS, VM::M1, "Location of Measured Beam Diameter" },
{ 0x0018, 0x1150, VR::IS, VM::M1, "Exposure Time" },
{ 0x0028, 0x0121, VR::XS, VM::M1, "Pixel Padding Range Limit" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0270[] = {
{ 0x0008, 0x0102, VR::SH, VM::M1, "Coding Scheme Designator" },
{ 0x0014, 0x401A, VR::DS, VM::M1, "Nominal Frequency" },
{ 0x0018, 0x1153, VR::IS, VM::M1, "Exposure in uAs" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0271[] = {
{ 0x0008, 0x0103, VR::SH, VM::M1, "Coding Scheme Version" },
{ 0x0014, 0x401B, VR::DS, VM::M1, "Measured Center Frequency" },
{ 0x0018, 0x1152, VR::IS, VM::M1, "Exposure" },
{ 0x2110, 0x0099, VR::SH, VM::M1, "Print Queue ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0272[] = {
{ 0x0010, 0x4000, VR::LT, VM::M1, "Patient Comments" },
{ 0x0014, 0x4004, VR::CS, VM::M1, "Pulser Type" },
{ 0x0018, 0x9345, VR::FD, VM::M1, "CTDIvol" },
{ 0x0018, 0x9755, VR::CS, VM::M1, "Time of Flight Information Used" },
{ 0x0040, 0x4050, VR::DT, VM::M1, "Performed Procedure Step Start DateTime" },
{ 0x0054, 0x1101, VR::LO, VM::M1, "Attenuation Correction Method" },
{ 0x4000, 0x0010, VR::LT, VM::M1, "Arbitrary" },
{ 0x4010, 0x1041, VR::DT, VM::M1, "OOI Owner Creation Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0273[] = {
{ 0x0018, 0x9344, VR::CS, VM::M1, "Contrast/Bolus Agent Phase" },
{ 0x0040, 0x4051, VR::DT, VM::M1, "Performed Procedure Step End DateTime" },
{ 0x0054, 0x1100, VR::CS, VM::M1, "Randoms Correction Method" },
{ 0x0400, 0x0105, VR::DT, VM::M1, "Digital Signature DateTime" },
{ 0x4010, 0x0001, VR::CS, VM::M1, "Low Energy Detectors" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0274[] = {
{ 0x0014, 0x4006, VR::LT, VM::M1, "Pulser Notes" },
{ 0x0040, 0x4052, VR::DT, VM::M1, "Procedure Step Cancellation DateTime" },
{ 0x0054, 0x1103, VR::LO, VM::M1, "Reconstruction Method" },
{ 0x4010, 0x0002, VR::CS, VM::M1, "High Energy Detectors" },
{ 0x4010, 0x1043, VR::FL, VM::M3, "OOI Size" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0275[] = {
{ 0x0018, 0x9346, VR::SQ, VM::M1, "CTDI Phantom Type Code Sequence" },
{ 0x0018, 0x9756, VR::CS, VM::M1, "Reconstruction Type" },
{ 0x0054, 0x1102, VR::CS, VM::M1, "Decay Correction" },
{ 0x4010, 0x1042, VR::CS, VM::M1, "OOI Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0276[] = {
{ 0x0018, 0x1149, VR::IS, VM::M1T2, "Field of View Dimension(s)" },
{ 0x0018, 0x9341, VR::SQ, VM::M1, "Contrast/Bolus Usage Sequence" },
{ 0x0018, 0x9751, VR::SQ, VM::M1, "PET Frame Type Sequence" },
{ 0x0054, 0x1105, VR::LO, VM::M1, "Scatter Correction Method" },
{ 0x0400, 0x0100, VR::UI, VM::M1, "Digital Signature UID" },
{ 0x0400, 0x0510, VR::UI, VM::M1, "Encrypted Content Transfer Syntax UID" },
{ 0x4010, 0x0004, VR::SQ, VM::M1, "Detector Geometry Sequence" },
{ 0x4010, 0x1045, VR::SQ, VM::M1, "Basis Materials Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0277[] = {
{ 0x0010, 0x0101, VR::SQ, VM::M1, "Patient's Primary Language Code Sequence" },
{ 0x0018, 0x9340, VR::SQ, VM::M1, "Contrast Administration Profile Sequence" },
{ 0x0054, 0x1104, VR::LO, VM::M1, "Detector Lines of Response Used" },
{ 0x4010, 0x1044, VR::CS, VM::M1, "Acquisition Status" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0278[] = {
{ 0x0010, 0x0102, VR::SQ, VM::M1, "Patient's Primary Language Modifier Code Sequence" },
{ 0x0010, 0x2180, VR::SH, VM::M1, "Occupation" },
{ 0x0014, 0x4002, VR::SQ, VM::M1, "Pulser Equipment Sequence" },
{ 0x0018, 0x9343, VR::CS, VM::M1, "Contrast/Bolus Agent Detected" },
{ 0x2130, 0x00A0, VR::SQ, VM::M1, "Proposed Study Sequence" },
{ 0x4010, 0x1047, VR::SQ, VM::M1, "OOI Owner Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0279[] = {
{ 0x0008, 0x115A, VR::UI, VM::M1TN, "SOP Classes Supported" },
{ 0x0018, 0x9342, VR::CS, VM::M1, "Contrast/Bolus Agent Administered" },
{ 0x4010, 0x1046, VR::CS, VM::M1, "Phantom Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0280[] = {
{ 0x0008, 0x0114, VR::ST, VM::M1, "Coding Scheme External ID" },
{ 0x0008, 0x1155, VR::UI, VM::M1, "Referenced SOP Instance UID" },
{ 0x0014, 0x400C, VR::LT, VM::M1, "Receiver Notes" },
{ 0x0018, 0x1145, VR::DS, VM::M1, "Center of Rotation Offset" },
{ 0x0018, 0x4000, VR::LT, VM::M1, "Acquisition Comments" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0281[] = {
{ 0x0008, 0x0115, VR::ST, VM::M1, "Coding Scheme Name" },
{ 0x0018, 0x1144, VR::DS, VM::M1, "Angular Step" },
{ 0x0018, 0x5040, VR::DS, VM::M1, "Total Gain" },
{ 0x300A, 0x01D4, VR::DS, VM::M1, "Table Top Longitudinal Setup Displacement" },
{ 0x4010, 0x1048, VR::CS, VM::M1, "Scan Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0282[] = {
{ 0x0008, 0x0116, VR::ST, VM::M1, "Coding Scheme Responsible Organization" },
{ 0x0014, 0x400E, VR::SQ, VM::M1, "Pre-Amplifier Equipment Sequence" },
{ 0x0018, 0x1147, VR::CS, VM::M1, "Field of View Shape" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0283[] = {
{ 0x0008, 0x0117, VR::UI, VM::M1, "Context UID" },
{ 0x0014, 0x400F, VR::LT, VM::M1, "Pre-Amplifier Notes" },
{ 0x0018, 0x1146, VR::DS, VM::M1TN, "Rotation Offset" },
{ 0x300A, 0x01D6, VR::DS, VM::M1, "Table Top Lateral Setup Displacement" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0284[] = {
{ 0x0008, 0x0110, VR::SQ, VM::M1, "Coding Scheme Identification Sequence" },
{ 0x0014, 0x4008, VR::SQ, VM::M1, "Receiver Equipment Sequence" },
{ 0x0018, 0x1141, VR::DS, VM::M1, "Angular Position" },
{ 0x0018, 0x9759, VR::CS, VM::M1, "Attenuation Corrected" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0285[] = {
{ 0x0008, 0x1150, VR::UI, VM::M1, "Referenced SOP Class UID" },
{ 0x0018, 0x1140, VR::CS, VM::M1, "Rotation Direction" },
{ 0x0018, 0x9758, VR::CS, VM::M1, "Decay Corrected" },
{ 0x300A, 0x01D0, VR::ST, VM::M1, "Setup Reference Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0286[] = {
{ 0x0008, 0x0112, VR::LO, VM::M1, "Coding Scheme Registry" },
{ 0x0014, 0x400A, VR::CS, VM::M1, "Amplifier Type" },
{ 0x0018, 0x1143, VR::DS, VM::M1, "Scan Arc" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0287[] = {
{ 0x0018, 0x1142, VR::DS, VM::M1TN, "Radial Position" },
{ 0x300A, 0x01D2, VR::DS, VM::M1, "Table Top Vertical Setup Displacement" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0288[] = {
{ 0x0014, 0x4034, VR::DS, VM::M1, "Rectifier Smoothing" },
{ 0x0018, 0x9765, VR::CS, VM::M1, "Randoms Corrected" },
{ 0x0020, 0x4000, VR::LT, VM::M1, "Image Comments" },
{ 0x0024, 0x0100, VR::FL, VM::M1, "Age Corrected Sensitivity Deviation Probability Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0289[] = {
{ 0x0014, 0x4035, VR::SQ, VM::M1, "DAC Sequence" },
{ 0x0018, 0x9764, VR::CS, VM::M1, "Count Loss Normalization Corrected" },
{ 0x0020, 0x0105, VR::IS, VM::M1, "Number of Temporal Positions" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0290[] = {
{ 0x0014, 0x4036, VR::CS, VM::M1, "DAC Type" },
{ 0x0018, 0x9767, VR::CS, VM::M1, "Sensitivity Calibrated" },
{ 0x0024, 0x0102, VR::CS, VM::M1, "Generalized Defect Corrected Sensitivity Deviation Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0291[] = {
{ 0x0018, 0x9766, VR::CS, VM::M1, "Non-uniform Radial Sampling Corrected" },
{ 0x0024, 0x0103, VR::FL, VM::M1, "Generalized Defect Corrected Sensitivity Deviation Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0292[] = {
{ 0x0014, 0x4030, VR::SQ, VM::M1, "Receiver Settings Sequence" },
{ 0x0018, 0x9761, VR::CS, VM::M1, "Dead Time Corrected" },
{ 0x0020, 0x0100, VR::IS, VM::M1, "Temporal Position Identifier" },
{ 0x0024, 0x0104, VR::FL, VM::M1, "Generalized Defect Corrected Sensitivity Deviation Probability Value" },
{ 0x0028, 0x0108, VR::XS, VM::M1, "Smallest Pixel Value in Series" },
{ 0x0400, 0x0520, VR::OB, VM::M1, "Encrypted Content" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0293[] = {
{ 0x0014, 0x4031, VR::DS, VM::M1, "Acquired Soundpath Length" },
{ 0x0018, 0x9760, VR::CS, VM::M1, "Scatter Corrected" },
{ 0x0024, 0x0105, VR::FL, VM::M1, "Minimum Sensitivity Value" },
{ 0x0028, 0x0109, VR::XS, VM::M1, "Largest Pixel Value in Series" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0294[] = {
{ 0x0010, 0x21B0, VR::LT, VM::M1, "Additional Patient History" },
{ 0x0014, 0x4032, VR::CS, VM::M1, "Acquisition Compression Type" },
{ 0x0018, 0x9763, VR::CS, VM::M1, "Patient Motion Corrected" },
{ 0x0024, 0x0106, VR::CS, VM::M1, "Blind Spot Localized" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0295[] = {
{ 0x0014, 0x4033, VR::IS, VM::M1, "Acquisition Sample Size" },
{ 0x0018, 0x9762, VR::CS, VM::M1, "Gantry Motion Corrected" },
{ 0x0022, 0x1140, VR::CS, VM::M1, "Ophthalmic Axial Length Measurement Modified" },
{ 0x0024, 0x0107, VR::FL, VM::M1, "Blind Spot X-Coordinate" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0296[] = {
{ 0x0014, 0x403C, VR::DS, VM::M1TN, "DAC Amplitude" },
{ 0x0024, 0x0108, VR::FL, VM::M1, "Blind Spot Y-Coordinate" },
{ 0x0028, 0x0104, VR::XS, VM::M1, "Smallest Valid Pixel Value" },
{ 0x0028, 0x4000, VR::LT, VM::M1, "Image Presentation Comments" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0297[] = {
{ 0x0008, 0x1164, VR::SQ, VM::M1, "Frame Extraction Sequence" },
{ 0x0028, 0x0105, VR::XS, VM::M1, "Largest Valid Pixel Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0298[] = {
{ 0x0008, 0x1167, VR::UI, VM::M1, "Multi-Frame Source SOP Instance UID" },
{ 0x0028, 0x0106, VR::XS, VM::M1, "Smallest Image Pixel Value" },
{ 0x0068, 0x64D0, VR::FD, VM::M9, "3D Mating Axes" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0299[] = {
{ 0x0028, 0x0107, VR::XS, VM::M1, "Largest Image Pixel Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0300[] = {
{ 0x0008, 0x1161, VR::UL, VM::M1TN, "Simple Frame List" },
{ 0x0014, 0x4038, VR::DS, VM::M1TN, "DAC Gain Points" },
{ 0x0018, 0x9769, VR::CS, VM::M1, "Iterative Reconstruction Method" },
{ 0x0028, 0x0100, VR::US, VM::M1, "Bits Allocated" },
{ 0x0038, 0x0500, VR::LO, VM::M1, "Patient State" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0301[] = {
{ 0x0008, 0x1160, VR::IS, VM::M1TN, "Referenced Frame Number" },
{ 0x0018, 0x1170, VR::IS, VM::M1, "Generator Power" },
{ 0x0018, 0x9768, VR::CS, VM::M1, "Detector Normalization Correction" },
{ 0x0028, 0x0101, VR::US, VM::M1, "Bits Stored" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0302[] = {
{ 0x0008, 0x1163, VR::FD, VM::M2, "Time Range" },
{ 0x0014, 0x403A, VR::DS, VM::M1TN, "DAC Time Points" },
{ 0x0028, 0x0102, VR::US, VM::M1, "High Bit" },
{ 0x0038, 0x0502, VR::SQ, VM::M1, "Patient Clinical Trial Participation Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0303[] = {
{ 0x0008, 0x1162, VR::UL, VM::M3T3N, "Calculated Frame List" },
{ 0x0028, 0x0103, VR::US, VM::M1, "Pixel Representation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0304[] = {
{ 0x0014, 0x4024, VR::DS, VM::M1, "Excitation Frequency" },
{ 0x0024, 0x0110, VR::SQ, VM::M1, "Visual Acuity Measurement Sequence" },
{ 0x0100, 0x0424, VR::LT, VM::M1, "SOP Authorization Comment" },
{ 0x4010, 0x1061, VR::FL, VM::M3, "Source Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0305[] = {
{ 0x4010, 0x1060, VR::FL, VM::M3, "Source Orientation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0306[] = {
{ 0x0014, 0x4026, VR::CS, VM::M1, "Modulation Type" },
{ 0x0022, 0x1155, VR::FL, VM::M1, "Signal to Noise Ratio" },
{ 0x0024, 0x0112, VR::SQ, VM::M1, "Refractive Parameters Used on Patient Sequence" },
{ 0x0032, 0x4000, VR::LT, VM::M1, "Study Comments" },
{ 0x0100, 0x0426, VR::LO, VM::M1, "Authorization Equipment Certification Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0307[] = {
{ 0x0024, 0x0113, VR::CS, VM::M1, "Measurement Laterality" },
{ 0x4010, 0x1062, VR::FL, VM::M1, "Belt Height" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0308[] = {
{ 0x0014, 0x4020, VR::SQ, VM::M1, "Pulser Settings Sequence" },
{ 0x0018, 0x9771, VR::SQ, VM::M1, "Patient Physiological State Sequence" },
{ 0x0020, 0x0110, VR::DS, VM::M1, "Temporal Resolution" },
{ 0x0022, 0x1153, VR::SQ, VM::M1, "Ophthalmic Axial Length Acquisition Method Code Sequence" },
{ 0x0024, 0x0114, VR::SQ, VM::M1, "Ophthalmic Patient Clinical Information Left Eye Sequence" },
{ 0x0040, 0x0560, VR::SQ, VM::M1, "Specimen Description Sequence" },
{ 0x0100, 0x0420, VR::DT, VM::M1, "SOP Authorization DateTime" },
{ 0x0400, 0x0120, VR::OB, VM::M1, "Signature" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0309[] = {
{ 0x0018, 0x9360, VR::SQ, VM::M1, "CT Additional X-Ray Source Sequence" },
{ 0x0018, 0x9770, VR::CS, VM::M1, "Attenuation Correction Temporal Relationship" },
{ 0x0024, 0x0115, VR::SQ, VM::M1, "Ophthalmic Patient Clinical Information Right Eye Sequence" },
{ 0x4010, 0x1064, VR::SQ, VM::M1, "Algorithm Routing Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0310[] = {
{ 0x0010, 0x21A0, VR::CS, VM::M1, "Smoking Status" },
{ 0x0014, 0x4022, VR::DS, VM::M1, "Pulse Width" },
{ 0x0040, 0x0562, VR::SQ, VM::M1, "Issuer of the Specimen Identifier Sequence" },
{ 0x2130, 0x0080, VR::SQ, VM::M1, "Presentation LUT Content Sequence" },
{ 0x4010, 0x1067, VR::CS, VM::M1, "Transport Classification" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0311[] = {
{ 0x0018, 0x9772, VR::SQ, VM::M1, "Patient Physiological State Code Sequence" },
{ 0x0022, 0x1150, VR::SQ, VM::M1, "Ophthalmic Axial Length Data Source Code Sequence" },
{ 0x0024, 0x0117, VR::CS, VM::M1, "Foveal Point Normative Data Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0312[] = {
{ 0x0024, 0x0118, VR::FL, VM::M1, "Foveal Point Probability Value" },
{ 0x0038, 0x4000, VR::LT, VM::M1, "Visit Comments" },
{ 0x4010, 0x1069, VR::FL, VM::M1, "Total Processing Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0313[] = {
{ 0x0018, 0x1164, VR::DS, VM::M2, "Imager Pixel Spacing" },
{ 0x4010, 0x1068, VR::LT, VM::M1, "OOI Type Descriptor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0314[] = {
{ 0x0068, 0x64C0, VR::FD, VM::M3, "3D Mating Point" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0315[] = {
{ 0x0018, 0x1166, VR::CS, VM::M1TN, "Grid" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0316[] = {
{ 0x0014, 0x4028, VR::DS, VM::M1, "Damping" },
{ 0x0018, 0x1161, VR::LO, VM::M1TN, "Type of Filters" },
{ 0x0028, 0x0110, VR::XS, VM::M1, "Smallest Image Pixel Value in Plane" },
{ 0x0038, 0x0100, VR::SQ, VM::M1, "Pertinent Documents Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0317[] = {
{ 0x0018, 0x1160, VR::SH, VM::M1, "Filter Type" },
{ 0x0028, 0x0111, VR::XS, VM::M1, "Largest Image Pixel Value in Plane" },
{ 0x4010, 0x106C, VR::OB, VM::M1, "Detector Calibration Data" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0318[] = {
{ 0x0022, 0x1159, VR::LO, VM::M1, "Ophthalmic Axial Length Data Source Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0319[] = {
{ 0x0018, 0x1162, VR::DS, VM::M1, "Intensifier Size" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0320[] = {
{ 0x0018, 0x9314, VR::SQ, VM::M1, "CT Reconstruction Sequence" },
{ 0x0040, 0x0515, VR::SQ, VM::M1, "Alternate Container Identifier Sequence" },
{ 0x0040, 0x4001, VR::CS, VM::M1, "General Purpose Scheduled Procedure Step Status" },
{ 0x4010, 0x1010, VR::US, VM::M1, "Potential Threat Object ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0321[] = {
{ 0x0014, 0x4054, VR::ST, VM::M1, "Coupling Technique" },
{ 0x0018, 0x9315, VR::CS, VM::M1, "Reconstruction Algorithm" },
{ 0x0046, 0x0102, VR::SQ, VM::M1, "Add Other Sequence" },
{ 0x0054, 0x0500, VR::CS, VM::M1, "Slice Progression Direction" },
{ 0x4010, 0x1011, VR::SQ, VM::M1, "Threat Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0322[] = {
{ 0x0014, 0x4057, VR::DS, VM::M1, "Coupling Velocity" },
{ 0x0018, 0x9316, VR::CS, VM::M1, "Convolution Kernel Group" },
{ 0x0040, 0x4003, VR::CS, VM::M1, "General Purpose Scheduled Procedure Step Priority" },
{ 0x0046, 0x0101, VR::SQ, VM::M1, "Add Intermediate Sequence" },
{ 0x4010, 0x1012, VR::CS, VM::M1, "Threat Category" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0323[] = {
{ 0x0014, 0x4056, VR::ST, VM::M1, "Coupling Medium" },
{ 0x0018, 0x9317, VR::FD, VM::M2, "Reconstruction Field of View" },
{ 0x0022, 0x1125, VR::SQ, VM::M1, "Anterior Chamber Depth Definition Code Sequence" },
{ 0x0040, 0x4002, VR::CS, VM::M1, "General Purpose Performed Procedure Step Status" },
{ 0x0046, 0x0100, VR::SQ, VM::M1, "Add Near Sequence" },
{ 0x4010, 0x1013, VR::LT, VM::M1, "Threat Category Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0324[] = {
{ 0x0014, 0x4051, VR::SQ, VM::M1, "Receive Transducer Settings Sequence" },
{ 0x0018, 0x1508, VR::CS, VM::M1, "Positioner Type" },
{ 0x0018, 0x9310, VR::FD, VM::M1, "Table Feed per Rotation" },
{ 0x0022, 0x1122, VR::FL, VM::M1, "IOL Power For Exact Target Refraction" },
{ 0x0040, 0x4005, VR::DT, VM::M1, "Scheduled Procedure Step Start DateTime" },
{ 0x4010, 0x1014, VR::CS, VM::M1, "ATD Ability Assessment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0325[] = {
{ 0x0014, 0x4050, VR::SQ, VM::M1, "Transmit Transducer Settings Sequence" },
{ 0x0018, 0x9311, VR::FD, VM::M1, "Spiral Pitch Factor" },
{ 0x0018, 0x9701, VR::DT, VM::M1, "Decay Correction DateTime" },
{ 0x0040, 0x0100, VR::SQ, VM::M1, "Scheduled Procedure Step Sequence" },
{ 0x0040, 0x4004, VR::SQ, VM::M1, "Scheduled Processing Applications Code Sequence" },
{ 0x0046, 0x0106, VR::FD, VM::M1, "Viewing Distance" },
{ 0x0048, 0x0108, VR::SQ, VM::M1, "Illumination Color Code Sequence" },
{ 0x4010, 0x1015, VR::CS, VM::M1, "ATD Assessment Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0326[] = {
{ 0x0018, 0x9312, VR::SQ, VM::M1, "CT Geometry Sequence" },
{ 0x0040, 0x0513, VR::SQ, VM::M1, "Issuer of the Container Identifier Sequence" },
{ 0x0040, 0x4007, VR::SQ, VM::M1, "Performed Processing Applications Code Sequence" },
{ 0x4010, 0x1016, VR::FL, VM::M1, "ATD Assessment Probability" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0327[] = {
{ 0x0010, 0x21D0, VR::DA, VM::M1, "Last Menstrual Date" },
{ 0x0014, 0x4052, VR::DS, VM::M1, "Incident Angle" },
{ 0x0018, 0x9313, VR::FD, VM::M3, "Data Collection Center (Patient)" },
{ 0x0022, 0x1121, VR::FL, VM::M1, "IOL Power For Exact Emmetropia" },
{ 0x0040, 0x0512, VR::LO, VM::M1, "Container Identifier" },
{ 0x0040, 0x4006, VR::CS, VM::M1, "Multiple Copies Flag" },
{ 0x0046, 0x0104, VR::FD, VM::M1, "Add Power" },
{ 0x0072, 0x0520, VR::CS, VM::M1TN, "3D Rendering Type" },
{ 0x4010, 0x1017, VR::FL, VM::M1, "Mass" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0328[] = {
{ 0x0018, 0x1114, VR::DS, VM::M1, "Estimated Radiographic Magnification Factor" },
{ 0x0018, 0x5010, VR::LO, VM::M1TN, "Transducer Data" },
{ 0x0040, 0x4009, VR::SQ, VM::M1, "Human Performer Code Sequence" },
{ 0x0048, 0x0105, VR::SQ, VM::M1, "Optical Path Sequence" },
{ 0x300A, 0x0184, VR::LO, VM::M1, "Patient Additional Position" },
{ 0x4010, 0x1018, VR::FL, VM::M1, "Density" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0329[] = {
{ 0x0014, 0x405C, VR::ST, VM::M1, "Delay Law Identifier" },
{ 0x4008, 0x0040, VR::SH, VM::M1, "Results ID" },
{ 0x4010, 0x1019, VR::FL, VM::M1, "Z Effective" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0330[] = {
{ 0x0018, 0x5012, VR::DS, VM::M1, "Focus Depth" },
{ 0x0040, 0xA385, VR::SQ, VM::M1, "Pertinent Other Evidence Sequence" },
{ 0x0048, 0x0107, VR::ST, VM::M1, "Optical Path Description" },
{ 0x4010, 0x101A, VR::SH, VM::M1, "Boarding Pass ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0331[] = {
{ 0x0048, 0x0106, VR::SH, VM::M1, "Optical Path Identifier" },
{ 0x4008, 0x0042, VR::LO, VM::M1, "Results ID Issuer" },
{ 0x4010, 0x101B, VR::FL, VM::M3, "Center of Mass" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0332[] = {
{ 0x0008, 0x1100, VR::SQ, VM::M1, "Referenced Results Sequence" },
{ 0x0014, 0x4059, VR::DS, VM::M1, "Crystal Center Location Z" },
{ 0x0018, 0x1110, VR::DS, VM::M1, "Distance Source to Detector" },
{ 0x0018, 0x1500, VR::CS, VM::M1, "Positioner Motion" },
{ 0x0018, 0x9318, VR::FD, VM::M3, "Reconstruction Target Center (Patient)" },
{ 0x300A, 0x0180, VR::SQ, VM::M1, "Patient Setup Sequence" },
{ 0x4010, 0x101C, VR::FL, VM::M3, "Center of PTO" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0333[] = {
{ 0x0014, 0x4058, VR::DS, VM::M1, "Crystal Center Location X" },
{ 0x0018, 0x1111, VR::DS, VM::M1, "Distance Source to Patient" },
{ 0x0018, 0x9319, VR::FD, VM::M1, "Reconstruction Angle" },
{ 0x0040, 0x0518, VR::SQ, VM::M1, "Container Type Code Sequence" },
{ 0x0048, 0x0100, VR::SQ, VM::M1, "Illuminator Type Code Sequence" },
{ 0x4010, 0x101D, VR::FL, VM::M6TN, "Bounding Polygon" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0334[] = {
{ 0x300A, 0x0182, VR::IS, VM::M1, "Patient Setup Number" },
{ 0x4010, 0x101E, VR::SH, VM::M1, "Route Segment Start Location ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0335[] = {
{ 0x0014, 0x405A, VR::DS, VM::M1, "Sound Path Length" },
{ 0x0040, 0x051A, VR::LO, VM::M1, "Container Description" },
{ 0x0040, 0x8302, VR::DS, VM::M1, "Entrance Dose in mGy" },
{ 0x0040, 0xA380, VR::SQ, VM::M1, "Report Detail Sequence (Trial)" },
{ 0x0048, 0x0102, VR::DS, VM::M6, "Image Orientation (Slide)" },
{ 0x300A, 0x0183, VR::LO, VM::M1, "Patient Setup Label" },
{ 0x4010, 0x101F, VR::SH, VM::M1, "Route Segment End Location ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0336[] = {
{ 0x0014, 0x5004, VR::IS, VM::M1, "LINAC Output" },
{ 0x0018, 0x9304, VR::SQ, VM::M1, "CT Acquisition Details Sequence" },
{ 0x0040, 0x4011, VR::DT, VM::M1, "Expected Completion Date Time" },
{ 0x0054, 0x0101, VR::US, VM::M1, "Number of Time Slices" },
{ 0x0074, 0x0121, VR::FD, VM::M1, "Continuation End Meterset" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0337[] = {
{ 0x0018, 0x9305, VR::FD, VM::M1, "Revolution Time" },
{ 0x0018, 0x9715, VR::FD, VM::M1, "Start Density Threshold" },
{ 0x0040, 0x4010, VR::DT, VM::M1, "Scheduled Procedure Step Modification Date Time" },
{ 0x0054, 0x0100, VR::US, VM::M1TN, "Time Slice Vector" },
{ 0x0074, 0x0120, VR::FD, VM::M1, "Continuation Start Meterset" },
{ 0x4010, 0x1001, VR::SQ, VM::M1, "Threat ROI Voxel Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0338[] = {
{ 0x0018, 0x9306, VR::FD, VM::M1, "Single Collimation Width" },
{ 0x0018, 0x9716, VR::FD, VM::M1, "Start Relative Density Difference Threshold" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0339[] = {
{ 0x0018, 0x9307, VR::FD, VM::M1, "Total Collimation Width" },
{ 0x0018, 0x9717, VR::FD, VM::M1, "Start Cardiac Trigger Count Threshold" },
{ 0x0022, 0x1135, VR::SQ, VM::M1, "Source of Refractive Error Data Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0340[] = {
{ 0x0022, 0x1132, VR::SQ, VM::M1, "Source of Lens Thickness Data Code Sequence" },
{ 0x0040, 0x4015, VR::SQ, VM::M1, "Resulting General Purpose Performed Procedure Steps Sequence" },
{ 0x300A, 0x0198, VR::SH, VM::M1, "Fixation Device Position" },
{ 0x4010, 0x1004, VR::FL, VM::M3, "Threat ROI Base" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0341[] = {
{ 0x0014, 0x4040, VR::SQ, VM::M1, "Pre-Amplifier Settings Sequence" },
{ 0x0018, 0x9301, VR::SQ, VM::M1, "CT Acquisition Type Sequence" },
{ 0x0022, 0x1133, VR::SQ, VM::M1, "Source of Anterior Chamber Depth Data Code Sequence" },
{ 0x0040, 0x0500, VR::SQ, VM::M1, "Scheduled Specimen Sequence" },
{ 0x0400, 0x0550, VR::SQ, VM::M1, "Modified Attributes Sequence" },
{ 0x300A, 0x0199, VR::FL, VM::M1, "Fixation Device Pitch Angle" },
{ 0x4010, 0x1005, VR::FL, VM::M3, "Threat ROI Extents" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0342[] = {
{ 0x0014, 0x5002, VR::IS, VM::M1, "LINAC Energy" },
{ 0x0018, 0x9302, VR::CS, VM::M1, "Acquisition Type" },
{ 0x0022, 0x1130, VR::FL, VM::M1, "Lens Thickness" },
{ 0x300A, 0x019A, VR::FL, VM::M1, "Fixation Device Roll Angle" },
{ 0x4010, 0x1006, VR::OB, VM::M1, "Threat ROI Bitmap" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0343[] = {
{ 0x0010, 0x21C0, VR::US, VM::M1, "Pregnancy Status" },
{ 0x0018, 0x9303, VR::FD, VM::M1, "Tube Angle" },
{ 0x0022, 0x1131, VR::FL, VM::M1, "Anterior Chamber Depth" },
{ 0x0040, 0x4016, VR::SQ, VM::M1, "Referenced General Purpose Scheduled Procedure Step Sequence" },
{ 0x4010, 0x1007, VR::SH, VM::M1, "Route Segment ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0344[] = {
{ 0x0018, 0x5000, VR::SH, VM::M1TN, "Output Power" },
{ 0x0040, 0x4019, VR::SQ, VM::M1, "Performed Workitem Code Sequence" },
{ 0x300A, 0x0194, VR::SH, VM::M1, "Fixation Device Label" },
{ 0x4010, 0x1008, VR::CS, VM::M1, "Gantry Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0345[] = {
{ 0x0008, 0x1115, VR::SQ, VM::M1, "Referenced Series Sequence" },
{ 0x0040, 0x4018, VR::SQ, VM::M1, "Scheduled Workitem Code Sequence" },
{ 0x4008, 0x0050, VR::SQ, VM::M1, "Referenced Interpretation Sequence" },
{ 0x4010, 0x1009, VR::CS, VM::M1, "OOI Owner Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0346[] = {
{ 0x300A, 0x0196, VR::ST, VM::M1, "Fixation Device Description" },
{ 0x4010, 0x100A, VR::SQ, VM::M1, "Route Segment Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0347[] = {
{ 0x0068, 0x64A0, VR::FD, VM::M2, "Range of Freedom" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0348[] = {
{ 0x0008, 0x1110, VR::SQ, VM::M1, "Referenced Study Sequence" },
{ 0x0018, 0x1100, VR::DS, VM::M1, "Reconstruction Diameter" },
{ 0x0018, 0x1510, VR::DS, VM::M1, "Positioner Primary Angle" },
{ 0x0018, 0x9308, VR::SQ, VM::M1, "CT Table Dynamics Sequence" },
{ 0x0018, 0x9718, VR::FD, VM::M1, "Start Respiratory Trigger Count Threshold" },
{ 0x0048, 0x0111, VR::DS, VM::M1, "Condenser Lens Power" },
{ 0x300A, 0x0190, VR::SQ, VM::M1, "Fixation Device Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0349[] = {
{ 0x0008, 0x1111, VR::SQ, VM::M1, "Referenced Performed Procedure Step Sequence" },
{ 0x0018, 0x1511, VR::DS, VM::M1, "Positioner Secondary Angle" },
{ 0x0018, 0x9309, VR::FD, VM::M1, "Table Speed" },
{ 0x0018, 0x9719, VR::FD, VM::M1, "Termination Counts Threshold" },
{ 0x0048, 0x0110, VR::SQ, VM::M1, "Specimen Reference Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0350[] = {
{ 0x0048, 0x0113, VR::DS, VM::M1, "Objective Lens Numerical Aperture" },
{ 0x300A, 0x0192, VR::CS, VM::M1, "Fixation Device Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0351[] = {
{ 0x0040, 0x050A, VR::LO, VM::M1, "Specimen Accession Number" },
{ 0x0040, 0xA390, VR::SQ, VM::M1, "HL7 Structured Document Reference Sequence" },
{ 0x0048, 0x0112, VR::DS, VM::M1, "Objective Lens Power" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0352[] = {
{ 0x0018, 0x9334, VR::CS, VM::M1, "Fluoroscopy Flag" },
{ 0x0018, 0x9724, VR::FD, VM::M1, "Termination Respiratory Trigger Count Threshold" },
{ 0x0020, 0x5000, VR::AT, VM::M1TN, "Original Image Identification" },
{ 0x0020, 0x930C, VR::CS, VM::M1, "Patient Frame of Reference Source" },
{ 0x0040, 0x4021, VR::SQ, VM::M1, "Input Information Sequence" },
{ 0x0046, 0x0123, VR::SQ, VM::M1, "Visual Acuity Left Eye Sequence" },
{ 0x0400, 0x0565, VR::CS, VM::M1, "Reason for the Attribute Modification" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0353[] = {
{ 0x0014, 0x4074, VR::SH, VM::M1, "Procedure Version" },
{ 0x0018, 0x9335, VR::FD, VM::M1, "Distance Source to Data Collection Center" },
{ 0x0018, 0x9725, VR::CS, VM::M1, "Detector Geometry" },
{ 0x0020, 0x930D, VR::FD, VM::M1, "Temporal Position Time Offset" },
{ 0x0040, 0x4020, VR::CS, VM::M1, "Input Availability Flag" },
{ 0x0046, 0x0122, VR::SQ, VM::M1, "Visual Acuity Right Eye Sequence" },
{ 0x0400, 0x0564, VR::LO, VM::M1, "Source of Previous Values" },
{ 0x4010, 0x1031, VR::CS, VM::M1, "Alarm Decision" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0354[] = {
{ 0x0018, 0x9726, VR::FD, VM::M1, "Transverse Detector Separation" },
{ 0x0020, 0x5002, VR::LO, VM::M1TN, "Original Image Identification Nomenclature" },
{ 0x0020, 0x930E, VR::SQ, VM::M1, "Plane Position (Volume) Sequence" },
{ 0x0040, 0x4023, VR::UI, VM::M1, "Referenced General Purpose Scheduled Procedure Step Transaction UID" },
{ 0x0046, 0x0121, VR::SQ, VM::M1, "Visual Acuity Type Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0355[] = {
{ 0x0014, 0x4076, VR::DA, VM::M1, "Procedure Creation Date" },
{ 0x0018, 0x9337, VR::US, VM::M1, "Contrast/Bolus Agent Number" },
{ 0x0018, 0x9727, VR::FD, VM::M1, "Axial Detector Dimension" },
{ 0x0020, 0x930F, VR::SQ, VM::M1, "Plane Orientation (Volume) Sequence" },
{ 0x0040, 0x4022, VR::SQ, VM::M1, "Relevant Information Sequence" },
{ 0x4010, 0x1033, VR::US, VM::M1, "Number of Total Objects" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0356[] = {
{ 0x0018, 0x1138, VR::DS, VM::M1, "Table Angle" },
{ 0x0018, 0x9330, VR::FD, VM::M1, "X-Ray Tube Current in mA" },
{ 0x0018, 0x9720, VR::FD, VM::M1, "Termination Density Threshold" },
{ 0x0020, 0x9308, VR::FD, VM::M3, "Apex Position" },
{ 0x0040, 0x4025, VR::SQ, VM::M1, "Scheduled Station Name Code Sequence" },
{ 0x0400, 0x0561, VR::SQ, VM::M1, "Original Attributes Sequence" },
{ 0x300A, 0x01A8, VR::SH, VM::M1, "Shielding Device Position" },
{ 0x4010, 0x1034, VR::US, VM::M1, "Number of Alarm Objects" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0357[] = {
{ 0x0014, 0x4070, VR::SQ, VM::M1, "Calibration Settings Sequence" },
{ 0x0018, 0x9721, VR::FD, VM::M1, "Termination Relative Density Threshold" },
{ 0x0020, 0x9309, VR::FD, VM::M16, "Volume to Transducer Mapping Matrix" },
{ 0x0022, 0x1103, VR::SQ, VM::M1, "Refractive Error Before Refractive Surgery Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0358[] = {
{ 0x0018, 0x113A, VR::CS, VM::M1, "Table Type" },
{ 0x0018, 0x9332, VR::FD, VM::M1, "Exposure in mAs" },
{ 0x0018, 0x9722, VR::FD, VM::M1, "Termination Time Threshold" },
{ 0x0020, 0x930A, VR::FD, VM::M16, "Volume to Table Mapping Matrix" },
{ 0x0022, 0x1100, VR::SQ, VM::M1, "Referenced Ophthalmic Axial Measurements Sequence" },
{ 0x0040, 0x4027, VR::SQ, VM::M1, "Scheduled Station Geographic Location Code Sequence" },
{ 0x0046, 0x0125, VR::CS, VM::M1, "Viewing Distance Type" },
{ 0x0400, 0x0563, VR::LO, VM::M1, "Modifying System" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0359[] = {
{ 0x0010, 0x21F0, VR::LO, VM::M1, "Patient's Religious Preference" },
{ 0x0014, 0x4072, VR::ST, VM::M1, "Calibration Procedure" },
{ 0x0018, 0x9333, VR::CS, VM::M1, "Constant Volume Flag" },
{ 0x0018, 0x9723, VR::FD, VM::M1, "Termination Cardiac Trigger Count Threshold" },
{ 0x0022, 0x1101, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Segment Name Code Sequence" },
{ 0x0040, 0x4026, VR::SQ, VM::M1, "Scheduled Station Class Code Sequence" },
{ 0x0046, 0x0124, VR::SQ, VM::M1, "Visual Acuity Both Eyes Open Sequence" },
{ 0x0072, 0x0500, VR::CS, VM::M1, "Blending Operation Type" },
{ 0x0400, 0x0562, VR::DT, VM::M1, "Attribute Modification DateTime" },
{ 0x4010, 0x1037, VR::SQ, VM::M1, "PTO Representation Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0360[] = {
{ 0x0018, 0x1134, VR::CS, VM::M1, "Table Motion" },
{ 0x0018, 0x5030, VR::DS, VM::M1, "Dynamic Range" },
{ 0x0028, 0x1104, VR::US, VM::M3, "Alpha Palette Color Lookup Table Descriptor" },
{ 0x0028, 0x5000, VR::SQ, VM::M1, "Bi-Plane Acquisition Sequence" },
{ 0x0040, 0x4029, VR::SQ, VM::M1, "Performed Station Class Code Sequence" },
{ 0x300A, 0x01A4, VR::SH, VM::M1, "Shielding Device Label" },
{ 0x4010, 0x1038, VR::SQ, VM::M1, "ATD Assessment Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0361[] = {
{ 0x0008, 0x1125, VR::SQ, VM::M1, "Referenced Visit Sequence" },
{ 0x0014, 0x407C, VR::TM, VM::M1TN, "Calibration Time" },
{ 0x0018, 0x1135, VR::DS, VM::M1TN, "Table Vertical Increment" },
{ 0x0040, 0x4028, VR::SQ, VM::M1, "Performed Station Name Code Sequence" },
{ 0x4010, 0x1039, VR::CS, VM::M1, "TIP Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0362[] = {
{ 0x0018, 0x1136, VR::DS, VM::M1TN, "Table Lateral Increment" },
{ 0x300A, 0x01A6, VR::ST, VM::M1, "Shielding Device Description" },
{ 0x4010, 0x103A, VR::CS, VM::M1, "DICOS Version" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0363[] = {
{ 0x0014, 0x407E, VR::DA, VM::M1TN, "Calibration Date" },
{ 0x0018, 0x1137, VR::DS, VM::M1TN, "Table Longitudinal Increment" },
{ 0x0020, 0x9307, VR::CS, VM::M1, "Ultrasound Acquisition Geometry" },
{ 0x0068, 0x6490, VR::FD, VM::M3, "3D Degree of Freedom Axis" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0364[] = {
{ 0x0008, 0x1120, VR::SQ, VM::M1, "Referenced Patient Sequence" },
{ 0x0018, 0x1130, VR::DS, VM::M1, "Table Height" },
{ 0x0018, 0x1520, VR::DS, VM::M1TN, "Positioner Primary Angle Increment" },
{ 0x0018, 0x9338, VR::SQ, VM::M1, "Contrast/Bolus Ingredient Code Sequence" },
{ 0x0028, 0x1100, VR::XS, VM::M3, "Gray Lookup Table Descriptor" },
{ 0x300A, 0x01A0, VR::SQ, VM::M1, "Shielding Device Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0365[] = {
{ 0x0014, 0x4078, VR::DA, VM::M1, "Procedure Expiration Date" },
{ 0x0018, 0x1131, VR::DS, VM::M1, "Table Traverse" },
{ 0x0018, 0x1521, VR::DS, VM::M1TN, "Positioner Secondary Angle Increment" },
{ 0x0018, 0x9729, VR::US, VM::M1, "Radiopharmaceutical Agent Number" },
{ 0x0020, 0x9301, VR::FD, VM::M3, "Image Position (Volume)" },
{ 0x0028, 0x1101, VR::XS, VM::M3, "Red Palette Color Lookup Table Descriptor" },
{ 0x0048, 0x0120, VR::SQ, VM::M1, "Palette Color Lookup Table Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0366[] = {
{ 0x0020, 0x9302, VR::FD, VM::M6, "Image Orientation (Volume)" },
{ 0x0028, 0x1102, VR::XS, VM::M3, "Green Palette Color Lookup Table Descriptor" },
{ 0x300A, 0x01A2, VR::CS, VM::M1, "Shielding Device Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0367[] = {
{ 0x0014, 0x407A, VR::DA, VM::M1, "Procedure Last Modified Date" },
{ 0x0028, 0x1103, VR::XS, VM::M3, "Blue Palette Color Lookup Table Descriptor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0368[] = {
{ 0x0018, 0x5028, VR::DS, VM::M1, "Soft Tissue-focus Thermal Index" },
{ 0x0018, 0x9324, VR::FD, VM::M1, "Estimated Dose Saving" },
{ 0x0018, 0x9734, VR::SQ, VM::M1, "PET Table Dynamics Sequence" },
{ 0x0040, 0x4031, VR::SQ, VM::M1, "Requested Subsequent Workitem Code Sequence" },
{ 0x300A, 0x01BC, VR::DS, VM::M1, "Setup Device Parameter" },
{ 0x4010, 0x1020, VR::CS, VM::M1, "Route Segment Location ID Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0369[] = {
{ 0x0014, 0x4064, VR::DS, VM::M1, "Velocity of Sound" },
{ 0x0018, 0x5029, VR::DS, VM::M1, "Soft Tissue-surface Thermal Index" },
{ 0x0018, 0x9325, VR::SQ, VM::M1, "CT X-Ray Details Sequence" },
{ 0x0018, 0x9735, VR::SQ, VM::M1, "PET Position Sequence" },
{ 0x0040, 0x4030, VR::SQ, VM::M1, "Performed Station Geographic Location Code Sequence" },
{ 0x0072, 0x0106, VR::US, VM::M1, "Number of Horizontal Pixels" },
{ 0x0072, 0x0516, VR::CS, VM::M1, "Reformatting Operation Initial View Direction" },
{ 0x4010, 0x1021, VR::CS, VM::M1TN, "Abort Reason" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0370[] = {
{ 0x0018, 0x9326, VR::SQ, VM::M1, "CT Position Sequence" },
{ 0x0018, 0x9736, VR::SQ, VM::M1, "PET Frame Correction Factors Sequence" },
{ 0x0040, 0x4033, VR::SQ, VM::M1, "Output Information Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0371[] = {
{ 0x0018, 0x9327, VR::FD, VM::M1, "Table Position" },
{ 0x0018, 0x9737, VR::SQ, VM::M1, "Radiopharmaceutical Usage Sequence" },
{ 0x0040, 0x4032, VR::SQ, VM::M1, "Non-DICOM Output Code Sequence" },
{ 0x0072, 0x0104, VR::US, VM::M1, "Number of Vertical Pixels" },
{ 0x0072, 0x0514, VR::FD, VM::M1, "Reformatting Interval" },
{ 0x4010, 0x1023, VR::FL, VM::M1, "Volume of PTO" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0372[] = {
{ 0x0018, 0x9320, VR::SH, VM::M1, "Image Filter" },
{ 0x0040, 0x4035, VR::SQ, VM::M1, "Actual Human Performers Sequence" },
{ 0x0046, 0x0137, VR::FD, VM::M1, "Decimal Visual Acuity" },
{ 0x0070, 0x0101, VR::DS, VM::M2, "Presentation Pixel Spacing" },
{ 0x300A, 0x01B8, VR::SH, VM::M1, "Setup Device Label" },
{ 0x4010, 0x1024, VR::CS, VM::M1, "Abort Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0373[] = {
{ 0x0014, 0x4060, VR::SQ, VM::M1, "Gate Settings Sequence" },
{ 0x0018, 0x9321, VR::SQ, VM::M1, "CT Exposure Sequence" },
{ 0x0040, 0x0520, VR::SQ, VM::M1, "Container Component Sequence" },
{ 0x0040, 0x4034, VR::SQ, VM::M1, "Scheduled Human Performers Sequence" },
{ 0x0070, 0x0100, VR::CS, VM::M1, "Presentation Size Mode" },
{ 0x0072, 0x0102, VR::SQ, VM::M1, "Nominal Screen Definition Sequence" },
{ 0x0072, 0x0512, VR::FD, VM::M1, "Reformatting Thickness" },
{ 0x4010, 0x1025, VR::DT, VM::M1, "Route Segment Start Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0374[] = {
{ 0x0008, 0x113A, VR::SQ, VM::M1, "Referenced Waveform Sequence" },
{ 0x0018, 0x9322, VR::FD, VM::M2, "Reconstruction Pixel Spacing" },
{ 0x0018, 0x9732, VR::SQ, VM::M1, "PET Frame Acquisition Sequence" },
{ 0x0040, 0x4037, VR::PN, VM::M1, "Human Performer's Name" },
{ 0x0046, 0x0135, VR::SS, VM::M2, "Visual Acuity Modifiers" },
{ 0x0070, 0x0103, VR::FL, VM::M1, "Presentation Pixel Magnification Ratio" },
{ 0x300A, 0x01BA, VR::ST, VM::M1, "Setup Device Description" },
{ 0x4010, 0x1026, VR::DT, VM::M1, "Route Segment End Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0375[] = {
{ 0x0014, 0x4062, VR::DS, VM::M1, "Gate Threshold" },
{ 0x0018, 0x9323, VR::CS, VM::M1, "Exposure Modulation Type" },
{ 0x0018, 0x9733, VR::SQ, VM::M1, "PET Detector Motion Details Sequence" },
{ 0x0040, 0x4036, VR::LO, VM::M1, "Human Performer's Organization" },
{ 0x0070, 0x0102, VR::IS, VM::M2, "Presentation Pixel Aspect Ratio" },
{ 0x0072, 0x0100, VR::US, VM::M1, "Number of Screens" },
{ 0x0072, 0x0510, VR::CS, VM::M1, "Reformatting Operation Type" },
{ 0x2130, 0x00C0, VR::SQ, VM::M1, "Original Image Sequence" },
{ 0x4010, 0x1027, VR::CS, VM::M1, "TDR Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0376[] = {
{ 0x0008, 0x1134, VR::SQ, VM::M1, "Referenced Stereometric Instance Sequence" },
{ 0x0018, 0x5020, VR::LO, VM::M1, "Processing Function" },
{ 0x300A, 0x01B4, VR::SQ, VM::M1, "Setup Device Sequence" },
{ 0x4010, 0x1028, VR::CS, VM::M1, "International Route Segment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0377[] = {
{ 0x0018, 0x5021, VR::LO, VM::M1, "Postprocessing Function" },
{ 0x0072, 0x010E, VR::US, VM::M1, "Application Maximum Repaint Time" },
{ 0x4010, 0x1029, VR::LO, VM::M1TN, "Threat Detection Algorithm and Version" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0378[] = {
{ 0x0018, 0x5022, VR::DS, VM::M1, "Mechanical Index" },
{ 0x0046, 0x0139, VR::LO, VM::M1, "Optotype Detailed Definition" },
{ 0x300A, 0x01B6, VR::CS, VM::M1, "Setup Device Type" },
{ 0x4010, 0x102A, VR::SH, VM::M1, "Assigned Location" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0379[] = {
{ 0x0072, 0x010C, VR::US, VM::M1, "Screen Minimum Color Bit Depth" },
{ 0x4010, 0x102B, VR::DT, VM::M1, "Alarm Decision Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0380[] = {
{ 0x0008, 0x1130, VR::SQ, VM::M1, "Referenced Overlay Sequence" },
{ 0x0018, 0x1120, VR::DS, VM::M1, "Gantry/Detector Tilt" },
{ 0x0018, 0x1530, VR::DS, VM::M1, "Detector Primary Angle" },
{ 0x0018, 0x5024, VR::DS, VM::M1, "Bone Thermal Index" },
{ 0x0018, 0x9328, VR::FD, VM::M1, "Exposure Time in ms" },
{ 0x0018, 0x9738, VR::CS, VM::M1, "Attenuation Correction Source" },
{ 0x0020, 0x9310, VR::SQ, VM::M1, "Temporal Position Sequence" },
{ 0x300A, 0x01B0, VR::CS, VM::M1, "Setup Technique" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0381[] = {
{ 0x0018, 0x1121, VR::DS, VM::M1, "Gantry/Detector Slew" },
{ 0x0018, 0x1531, VR::DS, VM::M1, "Detector Secondary Angle" },
{ 0x0018, 0x9329, VR::SQ, VM::M1, "CT Image Frame Type Sequence" },
{ 0x0018, 0x9739, VR::US, VM::M1, "Number of Iterations" },
{ 0x0020, 0x9311, VR::CS, VM::M1, "Dimension Organization Type" },
{ 0x0028, 0x1111, VR::XS, VM::M4, "Large Red Palette Color Lookup Table Descriptor" },
{ 0x0072, 0x010A, VR::US, VM::M1, "Screen Minimum Grayscale Bit Depth" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0382[] = {
{ 0x0018, 0x5026, VR::DS, VM::M1, "Cranial Thermal Index" },
{ 0x0020, 0x9312, VR::UI, VM::M1, "Volume Frame of Reference UID" },
{ 0x0028, 0x1112, VR::XS, VM::M4, "Large Green Palette Color Lookup Table Descriptor" },
{ 0x300A, 0x01B2, VR::ST, VM::M1, "Setup Technique Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0383[] = {
{ 0x0018, 0x5027, VR::DS, VM::M1, "Soft Tissue Thermal Index" },
{ 0x0020, 0x9313, VR::UI, VM::M1, "Table Frame of Reference UID" },
{ 0x0028, 0x1113, VR::XS, VM::M4, "Large Blue Palette Color Lookup Table Descriptor" },
{ 0x0072, 0x0108, VR::FD, VM::M4, "Display Environment Spatial Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0384[] = {
{ 0x0018, 0x6018, VR::UL, VM::M1, "Region Location Min X0" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0385[] = {
{ 0x0018, 0x7058, VR::FL, VM::M1TN, "Filter Beam Path Length Maximum" },
{ 0x300A, 0x014E, VR::FL, VM::M1, "Gantry Pitch Angle Tolerance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0386[] = {
{ 0x0018, 0x601A, VR::UL, VM::M1, "Region Location Min Y0" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0387[] = {
{ 0x300A, 0x014C, VR::CS, VM::M1, "Gantry Pitch Rotation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0388[] = {
{ 0x0010, 0x2110, VR::LO, VM::M1TN, "Allergies" },
{ 0x0018, 0x601C, VR::UL, VM::M1, "Region Location Max X1" },
{ 0x2000, 0x0510, VR::SQ, VM::M1, "Referenced Stored Print  Sequence" },
{ 0x2010, 0x0110, VR::CS, VM::M1, "Empty Image Density" },
{ 0x2010, 0x0500, VR::SQ, VM::M1, "Referenced Film Session Sequence" },
{ 0x2110, 0x0010, VR::CS, VM::M1, "Printer Status" },
{ 0x2130, 0x0030, VR::SQ, VM::M1, "Film Box Content Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0389[] = {
{ 0x300A, 0x014A, VR::FL, VM::M1, "Gantry Pitch Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0390[] = {
{ 0x0018, 0x601E, VR::UL, VM::M1, "Region Location Max Y1" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0391[] = {
{ 0x300A, 0x0148, VR::FL, VM::M1, "Head Fixation Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0392[] = {
{ 0x0028, 0x6020, VR::US, VM::M1TN, "Frame Numbers of Interest (FOI)" },
{ 0x0068, 0x6470, VR::SQ, VM::M1, "2D Degree of Freedom Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0393[] = {
{ 0x0018, 0x6011, VR::SQ, VM::M1, "Sequence of Ultrasound Regions" },
{ 0x0018, 0x7050, VR::CS, VM::M1TN, "Filter Material" },
{ 0x300A, 0x0146, VR::CS, VM::M1, "Table Top Roll Rotation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0394[] = {
{ 0x0018, 0x6012, VR::US, VM::M1, "Region Spatial Format" },
{ 0x0028, 0x6022, VR::LO, VM::M1TN, "Frame of Interest Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0395[] = {
{ 0x0018, 0x7052, VR::DS, VM::M1TN, "Filter Thickness Minimum" },
{ 0x0028, 0x6023, VR::CS, VM::M1TN, "Frame of Interest Type" },
{ 0x300A, 0x0144, VR::FL, VM::M1, "Table Top Roll Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0396[] = {
{ 0x0018, 0x6014, VR::US, VM::M1, "Region Data Type" },
{ 0x0040, 0xA340, VR::SQ, VM::M1, "Procedure Context Sequence (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0397[] = {
{ 0x0018, 0x7054, VR::DS, VM::M1TN, "Filter Thickness Maximum" },
{ 0x3008, 0x0140, VR::SQ, VM::M1, "Recorded Source Applicator Sequence" },
{ 0x300A, 0x0142, VR::CS, VM::M1, "Table Top Pitch Rotation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0398[] = {
{ 0x0018, 0x6016, VR::UL, VM::M1, "Region Flags" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0399[] = {
{ 0x0018, 0x7056, VR::FL, VM::M1TN, "Filter Beam Path Length Minimum" },
{ 0x3008, 0x0142, VR::IS, VM::M1, "Referenced Source Applicator Number" },
{ 0x300A, 0x0140, VR::FL, VM::M1, "Table Top Pitch Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0400[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0401[] = {
{ 0x0018, 0x7048, VR::DS, VM::M1, "Grid Period" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0402[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0403[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0404[] = {
{ 0x0040, 0xA358, VR::SQ, VM::M1, "Verbal Source Identifier Code Sequence (Trial)" },
{ 0x2000, 0x0500, VR::SQ, VM::M1, "Referenced Film Box Sequence" },
{ 0x2010, 0x0100, VR::CS, VM::M1, "Border Density" },
{ 0x2010, 0x0510, VR::SQ, VM::M1, "Referenced Image Box Sequence" },
{ 0x2020, 0x0130, VR::SQ, VM::M1, "Referenced Image Overlay Box Sequence" },
{ 0x2100, 0x0010, VR::SH, VM::M1, "Print Job ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0405[] = {
{ 0x0018, 0x704C, VR::DS, VM::M1, "Grid Focal Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0406[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0407[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0408[] = {
{ 0x0018, 0x6000, VR::DS, VM::M1, "Sensitivity" },
{ 0x0018, 0x7041, VR::LT, VM::M1, "Grid Spacing Material" },
{ 0x0028, 0x6030, VR::US, VM::M1TN, "Mask Pointer(s)" },
{ 0x0040, 0xA354, VR::LO, VM::M1, "Telephone Number (Trial)" },
{ 0x0040, 0xA744, VR::SQ, VM::M1, "Language Code Sequence (Trial)" },
{ 0x0068, 0x6460, VR::FD, VM::M4, "2D Mating Axes" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0409[] = {
{ 0x0018, 0x7040, VR::LT, VM::M1, "Grid Absorbing Material" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0410[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0411[] = {
{ 0x0018, 0x7042, VR::DS, VM::M1, "Grid Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0412[] = {
{ 0x0008, 0x2110, VR::CS, VM::M1, "Lossy Image Compression (Retired)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0413[] = {
{ 0x0008, 0x2111, VR::ST, VM::M1, "Derivation Description" },
{ 0x0018, 0x7044, VR::DS, VM::M1, "Grid Pitch" },
{ 0x3008, 0x0150, VR::SQ, VM::M1, "Recorded Channel Shield Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0414[] = {
{ 0x0008, 0x2112, VR::SQ, VM::M1, "Source Image Sequence" },
{ 0x0040, 0x09F8, VR::SQ, VM::M1, "Vital Stain Code Sequence (Trial)" },
{ 0x0040, 0xA352, VR::PN, VM::M1, "Verbal Source (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0415[] = {
{ 0x0018, 0x7046, VR::IS, VM::M2, "Grid Aspect Ratio" },
{ 0x0040, 0xA353, VR::ST, VM::M1, "Address (Trial)" },
{ 0x3008, 0x0152, VR::IS, VM::M1, "Referenced Channel Shield Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0416[] = {
{ 0x0018, 0x6038, VR::UL, VM::M1, "Doppler Sample Volume X Position (Retired)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0417[] = {
{ 0x0018, 0x6039, VR::SL, VM::M1, "Doppler Sample Volume X Position" },
{ 0x2130, 0x0015, VR::SQ, VM::M1, "Printer Characteristics Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0418[] = {
{ 0x0018, 0x603A, VR::UL, VM::M1, "Doppler Sample Volume Y Position (Retired)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0419[] = {
{ 0x0018, 0x603B, VR::SL, VM::M1, "Doppler Sample Volume Y Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0420[] = {
{ 0x0008, 0x2128, VR::IS, VM::M1, "View Number" },
{ 0x0018, 0x603C, VR::UL, VM::M1, "TM-Line Position X0 (Retired)" },
{ 0x2010, 0x0130, VR::US, VM::M1, "Max Density" },
{ 0x2010, 0x0520, VR::SQ, VM::M1, "Referenced Basic Annotation Box Sequence" },
{ 0x2100, 0x0020, VR::CS, VM::M1, "Execution Status" },
{ 0x2110, 0x0030, VR::LO, VM::M1, "Printer Name" },
{ 0x2130, 0x0010, VR::SQ, VM::M1, "Print Management Capabilities Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0421[] = {
{ 0x0008, 0x2129, VR::IS, VM::M1, "Number of Event Timers" },
{ 0x0018, 0x603D, VR::SL, VM::M1, "TM-Line Position X0" },
{ 0x3008, 0x0168, VR::TM, VM::M1, "Safe Position Return Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0422[] = {
{ 0x0008, 0x212A, VR::IS, VM::M1, "Number of Views in Stage" },
{ 0x0018, 0x603E, VR::UL, VM::M1, "TM-Line Position Y0 (Retired)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0423[] = {
{ 0x0018, 0x603F, VR::SL, VM::M1, "TM-Line Position Y0" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0424[] = {
{ 0x0008, 0x2124, VR::IS, VM::M1, "Number of Stages" },
{ 0x0018, 0x6030, VR::UL, VM::M1, "Transducer Frequency" },
{ 0x0068, 0x6450, VR::FD, VM::M2, "2D Mating Point" },
{ 0x0088, 0x0906, VR::ST, VM::M1, "Topic Subject" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0425[] = {
{ 0x0018, 0x6031, VR::CS, VM::M1, "Transducer Type" },
{ 0x3008, 0x0164, VR::TM, VM::M1, "Safe Position Exit Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0426[] = {
{ 0x0018, 0x6032, VR::UL, VM::M1, "Pulse Repetition Frequency" },
{ 0x0088, 0x0904, VR::LO, VM::M1, "Topic Title" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0427[] = {
{ 0x0008, 0x2127, VR::SH, VM::M1, "View Name" },
{ 0x3008, 0x0166, VR::DA, VM::M1, "Safe Position Return Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0428[] = {
{ 0x0008, 0x2120, VR::SH, VM::M1, "Stage Name" },
{ 0x0018, 0x6034, VR::FD, VM::M1, "Doppler Correction Angle" },
{ 0x0040, 0xA360, VR::SQ, VM::M1, "Predecessor Documents Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0429[] = {
{ 0x3008, 0x0160, VR::SQ, VM::M1, "Brachy Control Point Delivered Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0430[] = {
{ 0x0008, 0x2122, VR::IS, VM::M1, "Stage Number" },
{ 0x0018, 0x6036, VR::FD, VM::M1, "Steering Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0431[] = {
{ 0x3008, 0x0162, VR::DA, VM::M1, "Safe Position Exit Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0432[] = {
{ 0x0018, 0x6028, VR::FD, VM::M1, "Reference Pixel Physical Value X" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0433[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0434[] = {
{ 0x0018, 0x602A, VR::FD, VM::M1, "Reference Pixel Physical Value Y" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0435[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0436[] = {
{ 0x0018, 0x602C, VR::FD, VM::M1, "Physical Delta X" },
{ 0x2010, 0x0120, VR::US, VM::M1, "Min Density" },
{ 0x2020, 0x0110, VR::SQ, VM::M1, "Basic Grayscale Image Sequence" },
{ 0x2100, 0x0030, VR::CS, VM::M1, "Execution Status Info" },
{ 0x2110, 0x0020, VR::CS, VM::M1, "Printer Status Info" },
{ 0x2120, 0x0010, VR::CS, VM::M1, "Queue Status" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0437[] = {
{ 0x2020, 0x0111, VR::SQ, VM::M1, "Basic Color Image Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0438[] = {
{ 0x0018, 0x602E, VR::FD, VM::M1, "Physical Delta Y" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0439[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0440[] = {
{ 0x0008, 0x2134, VR::FD, VM::M1, "Event Time Offset" },
{ 0x0018, 0x6020, VR::SL, VM::M1, "Reference Pixel X0" },
{ 0x0028, 0x2114, VR::CS, VM::M1TN, "Lossy Image Compression Method" },
{ 0x0028, 0x6010, VR::US, VM::M1, "Representative Frame Number" },
{ 0x0068, 0x6440, VR::US, VM::M1, "Referenced HPGL Document ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0441[] = {
{ 0x0008, 0x2135, VR::SQ, VM::M1, "Event Code Sequence" },
{ 0x0018, 0x7060, VR::CS, VM::M1, "Exposure Control Mode" },
{ 0x0040, 0xA375, VR::SQ, VM::M1, "Current Requested Procedure Evidence Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0442[] = {
{ 0x0018, 0x6022, VR::SL, VM::M1, "Reference Pixel Y0" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0443[] = {
{ 0x0018, 0x7062, VR::LT, VM::M1, "Exposure Control Mode Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0444[] = {
{ 0x0008, 0x2130, VR::DS, VM::M1TN, "Event Elapsed Time(s)" },
{ 0x0018, 0x6024, VR::US, VM::M1, "Physical Units X Direction" },
{ 0x0018, 0x7065, VR::DS, VM::M1, "Phototimer Setting" },
{ 0x0028, 0x2110, VR::CS, VM::M1, "Lossy Image Compression" },
{ 0x0040, 0xA370, VR::SQ, VM::M1, "Referenced Request Sequence" },
{ 0x0088, 0x0912, VR::LO, VM::M1T32, "Topic Keywords" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0445[] = {
{ 0x0018, 0x7064, VR::CS, VM::M1, "Exposure Status" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0446[] = {
{ 0x0008, 0x2132, VR::LO, VM::M1TN, "Event Timer Name(s)" },
{ 0x0018, 0x6026, VR::US, VM::M1, "Physical Units Y Direction" },
{ 0x0028, 0x2112, VR::DS, VM::M1TN, "Lossy Image Compression Ratio" },
{ 0x0040, 0xA372, VR::SQ, VM::M1, "Performed Procedure Code Sequence" },
{ 0x0088, 0x0130, VR::SH, VM::M1, "Storage Media File-set ID" },
{ 0x0088, 0x0910, VR::LO, VM::M1, "Topic Author" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0447[] = {
{ 0x0008, 0x2133, VR::SQ, VM::M1, "Event Timer Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0448[] = {
{ 0x300A, 0x010E, VR::DS, VM::M1, "Final Cumulative Meterset Weight" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0449[] = {
{ 0x0010, 0x2154, VR::SH, VM::M1TN, "Patient's Telephone Numbers" },
{ 0x0018, 0x6058, VR::UL, VM::M1TN, "Table of Pixel Values" },
{ 0x2010, 0x0154, VR::IS, VM::M1, "Maximum Collated Films" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0450[] = {
{ 0x0018, 0x701A, VR::DS, VM::M2, "Detector Binning" },
{ 0x300A, 0x010C, VR::DS, VM::M1, "Cumulative Dose Reference Coefficient" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0451[] = {
{ 0x0018, 0x605A, VR::FL, VM::M1TN, "Table of Parameter Values" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0452[] = {
{ 0x300A, 0x010A, VR::LO, VM::M1, "Applicator Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0453[] = {
{ 0x0010, 0x2150, VR::LO, VM::M1, "Country of Residence" },
{ 0x2010, 0x0150, VR::ST, VM::M1, "Configuration Information" },
{ 0x2040, 0x0100, VR::CS, VM::M1, "Threshold Density" },
{ 0x2050, 0x0500, VR::SQ, VM::M1, "Referenced Presentation  LUT Sequence" },
{ 0x2100, 0x0040, VR::DA, VM::M1, "Creation Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0454[] = {
{ 0x300A, 0x0108, VR::SH, VM::M1, "Applicator ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0455[] = {
{ 0x0010, 0x2152, VR::LO, VM::M1, "Region of Residence" },
{ 0x0040, 0xA30A, VR::DS, VM::M1TN, "Numeric Value" },
{ 0x2010, 0x0152, VR::LT, VM::M1, "Configuration Information Description" },
{ 0x300A, 0x0109, VR::CS, VM::M1, "Applicator Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0456[] = {
{ 0x0018, 0x7010, VR::IS, VM::M1, "Exposures on Detector Since Last Calibration" },
{ 0x300A, 0x0106, VR::DS, VM::M2T2N, "Block Data" },
{ 0x300C, 0x0100, VR::IS, VM::M1, "Referenced Range Shifter Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0457[] = {
{ 0x0008, 0x2144, VR::IS, VM::M1, "Recommended Display Frame Rate" },
{ 0x0018, 0x6050, VR::UL, VM::M1, "Number of Table Break Points" },
{ 0x0018, 0x7011, VR::IS, VM::M1, "Exposures on Detector Since Manufactured" },
{ 0x0068, 0x6430, VR::SQ, VM::M1, "2D Mating Feature Coordinates Sequence" },
{ 0x3008, 0x0105, VR::LO, VM::M1, "Source Serial Number" },
{ 0x300A, 0x0107, VR::SQ, VM::M1, "Applicator Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0458[] = {
{ 0x0018, 0x7012, VR::DS, VM::M1, "Detector Time Since Last Exposure" },
{ 0x0040, 0xA307, VR::PN, VM::M1, "Current Observer (Trial)" },
{ 0x300A, 0x0104, VR::IS, VM::M1, "Block Number of Points" },
{ 0x300C, 0x0102, VR::IS, VM::M1, "Referenced Lateral Spreading Device Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0459[] = {
{ 0x0018, 0x6052, VR::UL, VM::M1TN, "Table of X Break Points" },
{ 0x2010, 0x015E, VR::US, VM::M1, "Illumination" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0460[] = {
{ 0x0018, 0x7014, VR::DS, VM::M1, "Detector Active Time" },
{ 0x0040, 0xA301, VR::SQ, VM::M1, "Numeric Value Qualifier Code Sequence" },
{ 0x3008, 0x0100, VR::SQ, VM::M1, "Recorded Source Sequence" },
{ 0x300A, 0x0102, VR::DS, VM::M1, "Block Transmission" },
{ 0x300C, 0x0104, VR::IS, VM::M1, "Referenced Range Modulator Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0461[] = {
{ 0x0018, 0x6054, VR::FD, VM::M1TN, "Table of Y Break Points" },
{ 0x0040, 0x059A, VR::SQ, VM::M1, "Specimen Type Code Sequence" },
{ 0x0040, 0xA300, VR::SQ, VM::M1, "Measured Value Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0462[] = {
{ 0x0008, 0x2143, VR::IS, VM::M1, "Stop Trim" },
{ 0x0018, 0x1190, VR::DS, VM::M1TN, "Focal Spot(s)" },
{ 0x0018, 0x7016, VR::DS, VM::M1, "Detector Activation Offset From Exposure" },
{ 0x300A, 0x0100, VR::DS, VM::M1, "Block Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0463[] = {
{ 0x0008, 0x2142, VR::IS, VM::M1, "Start Trim" },
{ 0x0018, 0x1191, VR::CS, VM::M1, "Anode Target Material" },
{ 0x0018, 0x6056, VR::UL, VM::M1, "Number of Table Entries" },
{ 0x0088, 0x0140, VR::UI, VM::M1, "Storage Media File-set UID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0464[] = {
{ 0x0018, 0x7008, VR::LT, VM::M1, "Detector Mode" },
{ 0x300A, 0x011E, VR::DS, VM::M1, "Gantry Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0465[] = {
{ 0x0018, 0x6048, VR::UL, VM::M1, "Pixel Component Range Start" },
{ 0x300A, 0x011F, VR::CS, VM::M1, "Gantry Rotation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0466[] = {
{ 0x0018, 0x700A, VR::SH, VM::M1, "Detector ID" },
{ 0x300A, 0x011C, VR::DS, VM::M2T2N, "Leaf/Jaw Positions" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0467[] = {
{ 0x0018, 0x604A, VR::UL, VM::M1, "Pixel Component Range Stop" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0468[] = {
{ 0x0018, 0x700C, VR::DA, VM::M1, "Date of Last Detector Calibration" },
{ 0x300A, 0x011A, VR::SQ, VM::M1, "Beam Limiting Device Position Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0469[] = {
{ 0x0018, 0x604C, VR::US, VM::M1, "Pixel Component Physical Units" },
{ 0x2010, 0x0140, VR::CS, VM::M1, "Trim" },
{ 0x2040, 0x0500, VR::SQ, VM::M1, "Referenced Image Box Sequence (Retired)" },
{ 0x2100, 0x0050, VR::TM, VM::M1, "Creation Time" },
{ 0x2120, 0x0070, VR::SQ, VM::M1, "Referenced Print Job Sequence" },
{ 0x2130, 0x0060, VR::SQ, VM::M1, "Image Overlay Box Content Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0470[] = {
{ 0x0008, 0x1198, VR::SQ, VM::M1, "Failed SOP Sequence" },
{ 0x0018, 0x700E, VR::TM, VM::M1, "Time of Last Detector Calibration" },
{ 0x300A, 0x0118, VR::CS, VM::M1, "Wedge Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0471[] = {
{ 0x0008, 0x1199, VR::SQ, VM::M1, "Referenced SOP Sequence" },
{ 0x0018, 0x604E, VR::US, VM::M1, "Pixel Component Data Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0472[] = {
{ 0x0018, 0x3104, VR::IS, VM::M1, "IVUS Pullback Stop Frame Number" },
{ 0x0018, 0x6041, VR::SL, VM::M1, "TM-Line Position X1" },
{ 0x0018, 0x7000, VR::CS, VM::M1, "Detector Conditions Nominal Flag" },
{ 0x300A, 0x0116, VR::SQ, VM::M1, "Wedge Position Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0473[] = {
{ 0x0008, 0x1197, VR::US, VM::M1, "Failure Reason" },
{ 0x0018, 0x3105, VR::IS, VM::M1TN, "Lesion Number" },
{ 0x0018, 0x6040, VR::UL, VM::M1, "TM-Line Position X1 (Retired)" },
{ 0x0018, 0x7001, VR::DS, VM::M1, "Detector Temperature" },
{ 0x0068, 0x6420, VR::CS, VM::M1, "Degree of Freedom Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0474[] = {
{ 0x0018, 0x1184, VR::DS, VM::M1T2, "Y Focus Center" },
{ 0x0018, 0x6043, VR::SL, VM::M1, "TM-Line Position Y1" },
{ 0x3008, 0x0116, VR::CS, VM::M1, "Application Setup Check" },
{ 0x300A, 0x0114, VR::DS, VM::M1, "Nominal Beam Energy" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0475[] = {
{ 0x0008, 0x1195, VR::UI, VM::M1, "Transaction UID" },
{ 0x0018, 0x6042, VR::UL, VM::M1, "TM-Line Position Y1 (Retired)" },
{ 0x300A, 0x0115, VR::DS, VM::M1, "Dose Rate Set" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0476[] = {
{ 0x0018, 0x1182, VR::IS, VM::M1T2, "Focal Distance" },
{ 0x0018, 0x3100, VR::CS, VM::M1, "IVUS Acquisition" },
{ 0x0018, 0x7004, VR::CS, VM::M1, "Detector Type" },
{ 0x3008, 0x0110, VR::SQ, VM::M1, "Treatment Session Application Setup Sequence" },
{ 0x300A, 0x0112, VR::IS, VM::M1, "Control Point Index" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0477[] = {
{ 0x0018, 0x1183, VR::DS, VM::M1T2, "X Focus Center" },
{ 0x0018, 0x3101, VR::DS, VM::M1, "IVUS Pullback Rate" },
{ 0x0018, 0x6044, VR::US, VM::M1, "Pixel Component Organization" },
{ 0x0018, 0x7005, VR::CS, VM::M1, "Detector Configuration" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0478[] = {
{ 0x0018, 0x1180, VR::SH, VM::M1, "Collimator/grid Name" },
{ 0x0018, 0x3102, VR::DS, VM::M1, "IVUS Gated Rate" },
{ 0x0018, 0x7006, VR::LT, VM::M1, "Detector Description" },
{ 0x0040, 0xA313, VR::SQ, VM::M1, "Referenced Accession Sequence (Trial)" },
{ 0x300A, 0x0110, VR::IS, VM::M1, "Number of Control Points" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0479[] = {
{ 0x0018, 0x1181, VR::CS, VM::M1, "Collimator Type" },
{ 0x0018, 0x3103, VR::IS, VM::M1, "IVUS Pullback Start Frame Number" },
{ 0x0018, 0x6046, VR::UL, VM::M1, "Pixel Component Mask" },
{ 0x300A, 0x0111, VR::SQ, VM::M1, "Control Point Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0480[] = {
{ 0x0018, 0x7038, VR::FL, VM::M1, "Pixel Data Area Rotation Angle Relative To FOV" },
{ 0x300A, 0x012E, VR::DS, VM::M3, "Surface Entry Point" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0481[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0482[] = {
{ 0x300A, 0x012C, VR::DS, VM::M3, "Isocenter Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0483[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0484[] = {
{ 0x0020, 0x3100, VR::CS, VM::M1TN, "Source Image IDs" },
{ 0x300A, 0x012A, VR::DS, VM::M1, "Table Top Lateral Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0485[] = {
{ 0x2020, 0x0140, VR::SQ, VM::M1, "Referenced VOI LUT Box Sequence" },
{ 0x2130, 0x0050, VR::SQ, VM::M1, "Annotation Content Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0486[] = {
{ 0x300A, 0x0128, VR::DS, VM::M1, "Table Top Vertical Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0487[] = {
{ 0x300A, 0x0129, VR::DS, VM::M1, "Table Top Longitudinal Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0488[] = {
{ 0x0018, 0x7030, VR::DS, VM::M2, "Field of View Origin" },
{ 0x300A, 0x0126, VR::CS, VM::M1, "Table Top Eccentric Rotation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0489[] = {
{ 0x0028, 0x6040, VR::US, VM::M1TN, "R Wave Pointer" },
{ 0x0068, 0x6410, VR::US, VM::M1, "Degree of Freedom ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0490[] = {
{ 0x0018, 0x7032, VR::DS, VM::M1, "Field of View Rotation" },
{ 0x300A, 0x0124, VR::DS, VM::M1, "Table Top Eccentric Axis Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0491[] = {
{ 0x300A, 0x0125, VR::DS, VM::M1, "Table Top Eccentric Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0492[] = {
{ 0x0018, 0x7034, VR::CS, VM::M1, "Field of View Horizontal Flip" },
{ 0x0040, 0xA731, VR::SQ, VM::M1, "Relationship Sequence (Trial)" },
{ 0x3008, 0x0120, VR::SQ, VM::M1, "Recorded Brachy Accessory Device Sequence" },
{ 0x300A, 0x0122, VR::DS, VM::M1, "Patient Support Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0493[] = {
{ 0x0040, 0xA730, VR::SQ, VM::M1, "Content Sequence" },
{ 0x300A, 0x0123, VR::CS, VM::M1, "Patient Support Rotation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0494[] = {
{ 0x0018, 0x7036, VR::FL, VM::M2, "Pixel Data Area Origin Relative To FOV" },
{ 0x3008, 0x0122, VR::IS, VM::M1, "Referenced Brachy Accessory Device Number" },
{ 0x300A, 0x0120, VR::DS, VM::M1, "Beam Limiting Device Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0495[] = {
{ 0x0040, 0xA732, VR::SQ, VM::M1, "Relationship Type Code Sequence (Trial)" },
{ 0x300A, 0x0121, VR::CS, VM::M1, "Beam Limiting Device Rotation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0496[] = {
{ 0x0018, 0x7028, VR::DS, VM::M2, "Detector Active Origin" },
{ 0x3008, 0x013C, VR::DS, VM::M1, "Delivered Pulse Repetition Interval" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0497[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0498[] = {
{ 0x0018, 0x702A, VR::LO, VM::M1, "Detector Manufacturer Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0499[] = {
{ 0x0018, 0x702B, VR::LO, VM::M1, "Detector Manufacturer's Model Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0500[] = {
{ 0x3008, 0x0138, VR::IS, VM::M1, "Delivered Number of Pulses" },
{ 0x4008, 0x00FF, VR::CS, VM::M1, "Report Production Status (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0501[] = {
{ 0x0010, 0x2160, VR::SH, VM::M1, "Ethnic Group" },
{ 0x2010, 0x0160, VR::US, VM::M1, "Reflected Ambient Light" },
{ 0x2100, 0x0070, VR::AE, VM::M1, "Originator" },
{ 0x2120, 0x0050, VR::SQ, VM::M1, "Print Job Description Sequence" },
{ 0x2130, 0x0040, VR::SQ, VM::M1, "Image Box Content Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0502[] = {
{ 0x3008, 0x013A, VR::DS, VM::M1, "Specified Pulse Repetition Interval" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0503[] = {
{ 0x0028, 0x1199, VR::UI, VM::M1, "Palette Color Lookup Table UID" },
{ 0x0040, 0xA33A, VR::ST, VM::M1, "Report Status Comment (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0504[] = {
{ 0x0018, 0x7020, VR::DS, VM::M2, "Detector Element Physical Size" },
{ 0x3008, 0x0134, VR::DS, VM::M1, "Delivered Channel Total Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0505[] = {
{ 0x0018, 0x6060, VR::FL, VM::M1TN, "R Wave Time Vector" },
{ 0x0068, 0x6400, VR::SQ, VM::M1, "Mating Feature Degree of Freedom Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0506[] = {
{ 0x0018, 0x7022, VR::DS, VM::M2, "Detector Element Spacing" },
{ 0x3008, 0x0136, VR::IS, VM::M1, "Specified Number of Pulses" },
{ 0x300A, 0x0134, VR::DS, VM::M1, "Cumulative Meterset Weight" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0507[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0508[] = {
{ 0x0018, 0x11A2, VR::DS, VM::M1, "Compression Force" },
{ 0x0018, 0x7024, VR::CS, VM::M1, "Detector Active Shape" },
{ 0x0028, 0x3110, VR::SQ, VM::M1, "Softcopy VOI LUT Sequence" },
{ 0x3008, 0x0130, VR::SQ, VM::M1, "Recorded Channel Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0509[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0510[] = {
{ 0x0018, 0x11A0, VR::DS, VM::M1, "Body Part Thickness" },
{ 0x0018, 0x7026, VR::DS, VM::M1T2, "Detector Active Dimension(s)" },
{ 0x3008, 0x0132, VR::DS, VM::M1, "Specified Channel Total Time" },
{ 0x300A, 0x0130, VR::DS, VM::M1, "Source to Surface Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0511[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0512[] = {
{ 0x0008, 0x9459, VR::FL, VM::M1, "Recommended Display Frame Rate in Float" },
{ 0x0018, 0x1251, VR::SH, VM::M1, "Transmit Coil Name" },
{ 0x0018, 0x9059, VR::CS, VM::M1, "De-coupling" },
{ 0x0018, 0x9449, VR::FL, VM::M1, "Beam Angle" },
{ 0x0070, 0x0278, VR::CS, VM::M1, "Show Tick Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0513[] = {
{ 0x0008, 0x0201, VR::SH, VM::M1, "Timezone Offset From UTC" },
{ 0x0008, 0x9458, VR::SQ, VM::M1, "Frame Display Sequence" },
{ 0x0018, 0x1250, VR::SH, VM::M1, "Receive Coil Name" },
{ 0x0018, 0x9058, VR::US, VM::M1, "MR Acquisition Frequency Encoding Steps" },
{ 0x0028, 0x9478, VR::FL, VM::M1, "Mask Visibility Percentage" },
{ 0x0070, 0x0279, VR::CS, VM::M1, "Tick Label Alignment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0514[] = {
{ 0x0010, 0x2298, VR::CS, VM::M1, "Responsible Person Role" },
{ 0x0028, 0x0A02, VR::CS, VM::M1, "Pixel Spacing Calibration Type" },
{ 0x003A, 0x0230, VR::FL, VM::M1, "Waveform Data Display Scale" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0515[] = {
{ 0x0010, 0x2299, VR::LO, VM::M1, "Responsible Organization" },
{ 0x003A, 0x0231, VR::US, VM::M3, "Waveform Display Background CIELab Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0516[] = {
{ 0x0028, 0x0A04, VR::LO, VM::M1, "Pixel Spacing Calibration Description" },
{ 0x4008, 0x0300, VR::ST, VM::M1, "Impressions" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0517[] = {
{ 0x0074, 0x1238, VR::LT, VM::M1, "Reason for Cancellation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0518[] = {
{ 0x0068, 0x63E0, VR::SQ, VM::M1, "Mating Feature Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0519[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0520[] = {
{ 0x0010, 0x2292, VR::LO, VM::M1, "Patient Breed Description" },
{ 0x0018, 0x9051, VR::CS, VM::M1, "Transmit Coil Type" },
{ 0x0018, 0x9441, VR::US, VM::M1, "Radius of Circular Exposure Control Sensing Region" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0521[] = {
{ 0x0010, 0x2293, VR::SQ, VM::M1, "Patient Breed Code Sequence" },
{ 0x0018, 0x9050, VR::LO, VM::M1, "Transmit Coil Manufacturer Name" },
{ 0x0018, 0x9440, VR::SS, VM::M2, "Center of Circular Exposure Control Sensing Region" },
{ 0x0022, 0x1262, VR::SQ, VM::M1, "Ophthalmic Axial Length Quality Metric Sequence" },
{ 0x0040, 0x0241, VR::AE, VM::M1, "Performed Station AE Title" },
{ 0x0074, 0x1234, VR::AE, VM::M1, "Receiving AE" },
{ 0x300A, 0x02C8, VR::DS, VM::M1, "Final Cumulative Time Weight" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0522[] = {
{ 0x0018, 0x9053, VR::FD, VM::M1T2, "Chemical Shift Reference" },
{ 0x0040, 0x0242, VR::SH, VM::M1, "Performed Station Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0523[] = {
{ 0x0018, 0x9052, VR::FD, VM::M1T2, "Spectral Width" },
{ 0x0018, 0x9442, VR::SS, VM::M2TN, "Vertices of the Polygonal Exposure Control Sensing Region" },
{ 0x0022, 0x1260, VR::SQ, VM::M1, "Selected Total Ophthalmic Axial Length Sequence" },
{ 0x0040, 0x0243, VR::SH, VM::M1, "Performed Location" },
{ 0x0070, 0x0273, VR::FL, VM::M2, "Rotation Point" },
{ 0x0074, 0x1236, VR::AE, VM::M1, "Requesting AE" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0524[] = {
{ 0x0010, 0x2296, VR::SQ, VM::M1, "Breed Registry Code Sequence" },
{ 0x0040, 0x0244, VR::DA, VM::M1, "Performed Procedure Step Start Date" },
{ 0x0070, 0x0274, VR::CS, VM::M1, "Tick Alignment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0525[] = {
{ 0x0010, 0x2297, VR::PN, VM::M1, "Responsible Person" },
{ 0x0018, 0x9054, VR::CS, VM::M1, "Volume Localization Technique" },
{ 0x0028, 0x9474, VR::CS, VM::M1, "LUT Function" },
{ 0x0040, 0x0245, VR::TM, VM::M1, "Performed Procedure Step Start Time" },
{ 0x0054, 0x1210, VR::DS, VM::M1, "Coincidence Window Width" },
{ 0x0074, 0x1230, VR::LO, VM::M1, "Deletion Lock" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0526[] = {
{ 0x0010, 0x2294, VR::SQ, VM::M1, "Breed Registration Sequence" },
{ 0x0018, 0x9447, VR::FL, VM::M1, "Column Angulation (Patient)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0527[] = {
{ 0x0010, 0x2295, VR::LO, VM::M1, "Breed Registration Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0528[] = {
{ 0x0018, 0x9049, VR::SQ, VM::M1, "MR Transmit Coil Sequence" },
{ 0x0020, 0x9071, VR::SQ, VM::M1, "Frame Anatomy Sequence" },
{ 0x003A, 0x0222, VR::DS, VM::M1, "Notch Filter Frequency" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0529[] = {
{ 0x0008, 0x1250, VR::SQ, VM::M1, "Related Series Sequence" },
{ 0x0018, 0x1240, VR::IS, VM::M1TN, "Upper/Lower Pixel Values" },
{ 0x0018, 0x9048, VR::CS, VM::M1, "Multi-Coil Element Used" },
{ 0x003A, 0x0223, VR::DS, VM::M1, "Notch Filter Bandwidth" },
{ 0x300A, 0x02D0, VR::SQ, VM::M1, "Brachy Control Point Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0530[] = {
{ 0x0018, 0x1243, VR::IS, VM::M1, "Count Rate" },
{ 0x003A, 0x0220, VR::DS, VM::M1, "Filter Low Frequency" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0531[] = {
{ 0x0018, 0x1242, VR::IS, VM::M1, "Actual Frame Duration" },
{ 0x0020, 0x9072, VR::CS, VM::M1, "Frame Laterality" },
{ 0x003A, 0x0221, VR::DS, VM::M1, "Filter High Frequency" },
{ 0x300A, 0x02D2, VR::DS, VM::M1, "Control Point Relative Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0532[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0533[] = {
{ 0x0018, 0x1244, VR::US, VM::M1, "Preferred Playback Sequencing" },
{ 0x300A, 0x02D4, VR::DS, VM::M3, "Control Point 3D Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0534[] = {
{ 0x0068, 0x63F0, VR::US, VM::M1, "Mating Feature ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0535[] = {
{ 0x300A, 0x02D6, VR::DS, VM::M1, "Cumulative Time Weight" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0536[] = {
{ 0x0018, 0x9041, VR::LO, VM::M1, "Receive Coil Manufacturer Name" },
{ 0x0018, 0x9451, VR::SQ, VM::M1, "Frame Detector Parameters Sequence" },
{ 0x0022, 0x1273, VR::LO, VM::M1, "Ophthalmic Axial  Length Quality Metric Type Description" },
{ 0x0040, 0x0250, VR::DA, VM::M1, "Performed Procedure Step End Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0537[] = {
{ 0x0040, 0x0251, VR::TM, VM::M1, "Performed Procedure Step End Time" },
{ 0x0070, 0x0261, VR::FL, VM::M1, "Gap Length" },
{ 0x0074, 0x1224, VR::SQ, VM::M1, "Replaced Procedure Step Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0538[] = {
{ 0x0018, 0x9043, VR::CS, VM::M1, "Receive Coil Type" },
{ 0x0040, 0x0252, VR::CS, VM::M1, "Performed Procedure Step Status" },
{ 0x0070, 0x0262, VR::FL, VM::M1, "Diameter of Visibility" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0539[] = {
{ 0x0018, 0x9042, VR::SQ, VM::M1, "MR Receive Coil Sequence" },
{ 0x0018, 0x9452, VR::FL, VM::M1, "Calculated Anatomy Thickness" },
{ 0x0040, 0x0253, VR::SH, VM::M1, "Performed Procedure Step ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0540[] = {
{ 0x0018, 0x9045, VR::SQ, VM::M1, "Multi-Coil Definition Sequence" },
{ 0x0018, 0x9455, VR::SQ, VM::M1, "Calibration Sequence" },
{ 0x0040, 0x0254, VR::LO, VM::M1, "Performed Procedure Step Description" },
{ 0x0054, 0x1201, VR::IS, VM::M2, "Axial Mash" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0541[] = {
{ 0x0018, 0x9044, VR::CS, VM::M1, "Quadrature Receive Coil" },
{ 0x0040, 0x0255, VR::LO, VM::M1, "Performed Procedure Type Description" },
{ 0x0054, 0x1200, VR::DS, VM::M1, "Axial Acceptance" },
{ 0x0074, 0x1220, VR::SQ, VM::M1, "Related Procedure Step Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0542[] = {
{ 0x0018, 0x9047, VR::SH, VM::M1, "Multi-Coil Element Name" },
{ 0x0018, 0x9457, VR::CS, VM::M1, "Plane Identification" },
{ 0x0054, 0x1203, VR::DS, VM::M2, "Detector Element Size" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0543[] = {
{ 0x0018, 0x9046, VR::LO, VM::M1, "Multi-Coil Configuration" },
{ 0x0018, 0x9456, VR::SQ, VM::M1, "Object Thickness Sequence" },
{ 0x0054, 0x1202, VR::IS, VM::M1, "Transverse Mash" },
{ 0x0074, 0x1222, VR::LO, VM::M1, "Procedure Step Relationship Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0544[] = {
{ 0x0018, 0x9079, VR::FD, VM::M1TN, "Inversion Times" },
{ 0x0018, 0x9469, VR::FL, VM::M1, "Table Horizontal Rotation Angle" },
{ 0x0028, 0x0200, VR::US, VM::M1, "Image Location" },
{ 0x003A, 0x0212, VR::DS, VM::M1, "Channel Sensitivity Correction Factor" },
{ 0x0070, 0x0258, VR::FL, VM::M1, "Shadow Opacity" },
{ 0x300A, 0x02E1, VR::CS, VM::M1, "Compensator Mounting Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0545[] = {
{ 0x0018, 0x9078, VR::CS, VM::M1, "Parallel Acquisition Technique" },
{ 0x0018, 0x9468, VR::FL, VM::M1, "Table Z Position to Isocenter" },
{ 0x0020, 0x9450, VR::SQ, VM::M1, "Patient Orientation in Frame Sequence" },
{ 0x003A, 0x0213, VR::DS, VM::M1, "Channel Baseline" },
{ 0x300A, 0x02E0, VR::CS, VM::M1, "Compensator Divergence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0546[] = {
{ 0x0020, 0x9453, VR::LO, VM::M1, "Frame Label" },
{ 0x003A, 0x0210, VR::DS, VM::M1, "Channel Sensitivity" },
{ 0x300A, 0x02E3, VR::FL, VM::M1, "Total Compensator Tray Water-Equivalent Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0547[] = {
{ 0x003A, 0x0211, VR::SQ, VM::M1, "Channel Sensitivity Units Sequence" },
{ 0x300A, 0x02E2, VR::DS, VM::M1TN, "Source to Compensator Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0548[] = {
{ 0x300A, 0x02E5, VR::FL, VM::M1, "Compensator Column Offset" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0549[] = {
{ 0x300A, 0x02E4, VR::FL, VM::M1, "Isocenter to Compensator Tray Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0550[] = {
{ 0x003A, 0x0214, VR::DS, VM::M1, "Channel Time Skew" },
{ 0x0068, 0x63C0, VR::US, VM::M1, "Mating Feature Set ID" },
{ 0x300A, 0x02E7, VR::FL, VM::M1, "Compensator Relative Stopping Power Ratio" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0551[] = {
{ 0x003A, 0x0215, VR::DS, VM::M1, "Channel Sample Skew" },
{ 0x300A, 0x02E6, VR::FL, VM::M1TN, "Isocenter to Compensator Distances" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0552[] = {
{ 0x0018, 0x9461, VR::FL, VM::M1T2, "Field of View Dimension(s) in Float" },
{ 0x0020, 0x0200, VR::UI, VM::M1, "Synchronization Frame of Reference UID" },
{ 0x003A, 0x021A, VR::US, VM::M1, "Waveform Bits Stored" },
{ 0x0040, 0x0260, VR::SQ, VM::M1, "Performed Protocol Code Sequence" },
{ 0x0070, 0x0250, VR::CS, VM::M1, "Italic" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0553[] = {
{ 0x0018, 0x9070, VR::FD, VM::M1, "Cardiac R-R Interval Specified" },
{ 0x0040, 0x0261, VR::CS, VM::M1, "Performed Protocol Type" },
{ 0x0070, 0x0251, VR::US, VM::M3, "Pattern On Color CIELab Value" },
{ 0x300A, 0x02E8, VR::FL, VM::M1, "Compensator Milling Tool Diameter" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0554[] = {
{ 0x0018, 0x9073, VR::FD, VM::M1, "Acquisition Duration" },
{ 0x0018, 0x9463, VR::FL, VM::M1, "Positioner Isocenter Primary Angle" },
{ 0x003A, 0x0218, VR::DS, VM::M1, "Channel Offset" },
{ 0x0070, 0x0252, VR::US, VM::M3, "Pattern Off Color CIELab Value" },
{ 0x300A, 0x02EB, VR::LT, VM::M1, "Compensator Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0555[] = {
{ 0x0018, 0x9462, VR::SQ, VM::M1, "Isocenter Reference System Sequence" },
{ 0x0070, 0x0253, VR::FL, VM::M1, "Line Thickness" },
{ 0x0074, 0x1216, VR::SQ, VM::M1, "Unified Procedure Step Performed Procedure Sequence" },
{ 0x300A, 0x02EA, VR::SQ, VM::M1, "Ion Range Compensator Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0556[] = {
{ 0x0018, 0x9075, VR::CS, VM::M1, "Diffusion Directionality" },
{ 0x0018, 0x9465, VR::FL, VM::M1, "Positioner Isocenter Detector Rotation Angle" },
{ 0x0070, 0x0254, VR::CS, VM::M1, "Line Dashing Style" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0557[] = {
{ 0x0018, 0x9074, VR::DT, VM::M1, "Frame Acquisition DateTime" },
{ 0x0018, 0x9464, VR::FL, VM::M1, "Positioner Isocenter Secondary Angle" },
{ 0x0028, 0x9454, VR::CS, VM::M1, "Mask Selection Mode" },
{ 0x0070, 0x0255, VR::UL, VM::M1, "Line Pattern" },
{ 0x0074, 0x1210, VR::SQ, VM::M1, "Scheduled Processing Parameters Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0558[] = {
{ 0x0018, 0x9077, VR::CS, VM::M1, "Parallel Acquisition" },
{ 0x0018, 0x9467, VR::FL, VM::M1, "Table Y Position to Isocenter" },
{ 0x0024, 0x0202, VR::LO, VM::M1, "Algorithm Source" },
{ 0x0070, 0x0256, VR::OB, VM::M1, "Fill Pattern" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0559[] = {
{ 0x0018, 0x9076, VR::SQ, VM::M1, "Diffusion Gradient Direction Sequence" },
{ 0x0018, 0x9466, VR::FL, VM::M1, "Table X Position to Isocenter" },
{ 0x0070, 0x0257, VR::CS, VM::M1, "Fill Mode" },
{ 0x0074, 0x1212, VR::SQ, VM::M1, "Performed Processing Parameters Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0560[] = {
{ 0x0018, 0x1261, VR::LO, VM::M1, "Phosphor Type" },
{ 0x0018, 0x9069, VR::FD, VM::M1, "Parallel Reduction Factor In-plane" },
{ 0x003A, 0x0202, VR::IS, VM::M1, "Waveform Channel Number" },
{ 0x0070, 0x0248, VR::CS, VM::M1, "Underlined" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0561[] = {
{ 0x0018, 0x1260, VR::SH, VM::M1, "Plate Type" },
{ 0x003A, 0x0203, VR::SH, VM::M1, "Channel Label" },
{ 0x0070, 0x0249, VR::CS, VM::M1, "Bold" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0562[] = {
{ 0x003A, 0x0200, VR::SQ, VM::M1, "Channel Definition Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0563[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0564[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0565[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0566[] = {
{ 0x0020, 0x9057, VR::UL, VM::M1, "In-Stack Position Number" },
{ 0x0068, 0x63D0, VR::LO, VM::M1, "Mating Feature Set Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0567[] = {
{ 0x0020, 0x9056, VR::SH, VM::M1, "Stack ID" },
{ 0x0028, 0x7FE0, VR::UT, VM::M1, "Pixel Data Provider URL" },
{ 0x003A, 0x0205, VR::CS, VM::M1TN, "Channel Status" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0568[] = {
{ 0x0018, 0x9061, VR::FD, VM::M1T2, "De-coupling Frequency" },
{ 0x0018, 0x9471, VR::FL, VM::M1, "Table Cradle Tilt Angle" },
{ 0x003A, 0x020A, VR::SQ, VM::M1, "Source Waveform Sequence" },
{ 0x0040, 0x0270, VR::SQ, VM::M1, "Scheduled Step Attributes Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0569[] = {
{ 0x0008, 0x9460, VR::CS, VM::M1, "Skip Frame Range Flag" },
{ 0x0018, 0x9060, VR::CS, VM::M1T2, "De-coupled Nucleus" },
{ 0x0018, 0x9470, VR::FL, VM::M1, "Table Head Tilt Angle" },
{ 0x0070, 0x0241, VR::US, VM::M3, "Text Color CIELab Value" },
{ 0x0074, 0x1204, VR::LO, VM::M1, "Procedure Step Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0570[] = {
{ 0x0018, 0x9063, VR::FD, VM::M1T2, "De-coupling Chemical Shift Reference" },
{ 0x0018, 0x9473, VR::FL, VM::M1, "Acquired Image Area Dose Product" },
{ 0x0028, 0x9443, VR::SQ, VM::M1, "Frame Pixel Data Properties Sequence" },
{ 0x003A, 0x0208, VR::SQ, VM::M1, "Channel Source Sequence" },
{ 0x0070, 0x0242, VR::CS, VM::M1, "Horizontal Alignment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0571[] = {
{ 0x0018, 0x9062, VR::CS, VM::M1, "De-coupling Method" },
{ 0x0018, 0x9472, VR::SQ, VM::M1, "Frame Display Shutter Sequence" },
{ 0x0022, 0x1250, VR::SQ, VM::M1, "Ophthalmic Axial Length Selection Method Code Sequence" },
{ 0x003A, 0x0209, VR::SQ, VM::M1, "Channel Source Modifiers Sequence" },
{ 0x0070, 0x0243, VR::CS, VM::M1, "Vertical Alignment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0572[] = {
{ 0x0018, 0x9065, VR::CS, VM::M1T2, "Time Domain Filtering" },
{ 0x0022, 0x1257, VR::SQ, VM::M1, "Selected Segmental Ophthalmic Axial Length Sequence" },
{ 0x0028, 0x9445, VR::FL, VM::M1, "Geometric Maximum Distortion" },
{ 0x0070, 0x0244, VR::CS, VM::M1, "Shadow Style" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0573[] = {
{ 0x0018, 0x9064, VR::CS, VM::M1, "k-space Filtering" },
{ 0x0018, 0x9474, VR::CS, VM::M1, "C-arm Positioner Tabletop Relationship" },
{ 0x0028, 0x9444, VR::CS, VM::M1, "Geometrical Properties" },
{ 0x0040, 0x0275, VR::SQ, VM::M1, "Request Attributes Sequence" },
{ 0x0054, 0x1220, VR::CS, VM::M1TN, "Secondary Counts Type" },
{ 0x0070, 0x0245, VR::FL, VM::M1, "Shadow Offset X" },
{ 0x0074, 0x1200, VR::CS, VM::M1, "Scheduled Procedure Step Priority" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0574[] = {
{ 0x0018, 0x9067, VR::CS, VM::M1, "Baseline Correction" },
{ 0x0018, 0x9477, VR::SQ, VM::M1, "Irradiation Event Identification Sequence" },
{ 0x0022, 0x1255, VR::SQ, VM::M1, "Optical Selected Ophthalmic Axial Length Sequence" },
{ 0x003A, 0x020C, VR::LO, VM::M1, "Channel Derivation Description" },
{ 0x0070, 0x0246, VR::FL, VM::M1, "Shadow Offset Y" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0575[] = {
{ 0x0018, 0x9066, VR::US, VM::M1T2, "Number of Zero Fills" },
{ 0x0018, 0x9476, VR::SQ, VM::M1, "X-Ray Geometry Sequence" },
{ 0x0028, 0x9446, VR::CS, VM::M1TN, "Image Processing Applied" },
{ 0x0070, 0x0247, VR::US, VM::M3, "Shadow Color CIELab Value" },
{ 0x0074, 0x1202, VR::LO, VM::M1, "Worklist Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0576[] = {
{ 0x0008, 0x1200, VR::SQ, VM::M1, "Studies Containing Other Referenced Instances Sequence" },
{ 0x0018, 0x1210, VR::SH, VM::M1TN, "Convolution Kernel" },
{ 0x0018, 0x1600, VR::CS, VM::M1T3, "Shutter Shape" },
{ 0x0018, 0x9018, VR::CS, VM::M1, "Echo Planar Pulse Sequence" },
{ 0x0040, 0xA493, VR::CS, VM::M1, "Verification Flag" },
{ 0x0048, 0x0201, VR::US, VM::M2, "Top Left Hand Corner of Localizer Area" },
{ 0x300A, 0x0280, VR::SQ, VM::M1, "Channel Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0577[] = {
{ 0x0018, 0x9019, VR::FD, VM::M1, "Tag Angle First Axis" },
{ 0x0028, 0x1221, VR::OW, VM::M1, "Segmented Red Palette Color Lookup Table Data" },
{ 0x0040, 0xA082, VR::DT, VM::M1, "Participation DateTime" },
{ 0x0040, 0xA492, VR::LO, VM::M1, "Completion Flag Description" },
{ 0x0048, 0x0200, VR::SQ, VM::M1, "Referenced Image Navigation Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0578[] = {
{ 0x0018, 0x1602, VR::IS, VM::M1, "Shutter Left Vertical Edge" },
{ 0x0028, 0x1222, VR::OW, VM::M1, "Segmented Green Palette Color Lookup Table Data" },
{ 0x0040, 0xA491, VR::CS, VM::M1, "Completion Flag" },
{ 0x300A, 0x0282, VR::IS, VM::M1, "Channel Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0579[] = {
{ 0x0028, 0x1223, VR::OW, VM::M1, "Segmented Blue Palette Color Lookup Table Data" },
{ 0x0040, 0xA080, VR::CS, VM::M1, "Participation Type" },
{ 0x0048, 0x0202, VR::US, VM::M2, "Bottom Right Hand Corner of Localizer Area" },
{ 0x0068, 0x63A4, VR::SQ, VM::M1, "Coating Materials Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0580[] = {
{ 0x0018, 0x1604, VR::IS, VM::M1, "Shutter Right Vertical Edge" },
{ 0x300A, 0x0284, VR::DS, VM::M1, "Channel Length" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0581[] = {
{ 0x0040, 0xA496, VR::CS, VM::M1, "Preliminary Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0582[] = {
{ 0x0018, 0x1606, VR::IS, VM::M1, "Shutter Upper Horizontal Edge" },
{ 0x0040, 0xA085, VR::SQ, VM::M1, "Procedure Identifier Code Sequence (Trial)" },
{ 0x0048, 0x0207, VR::SQ, VM::M1, "Optical Path Identification Sequence" },
{ 0x300A, 0x0286, VR::DS, VM::M1, "Channel Total Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0583[] = {
{ 0x0040, 0xA084, VR::CS, VM::M1, "Observer Type" },
{ 0x0040, 0xA494, VR::CS, VM::M1, "Archive Requested" },
{ 0x0068, 0x63A0, VR::SQ, VM::M1, "Materials Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0584[] = {
{ 0x0008, 0x9410, VR::SQ, VM::M1, "Referenced Other Plane Sequence" },
{ 0x0018, 0x1608, VR::IS, VM::M1, "Shutter Lower Horizontal Edge" },
{ 0x0018, 0x9010, VR::CS, VM::M1, "Flow Compensation" },
{ 0x0070, 0x0231, VR::SQ, VM::M1, "Text Style Sequence" },
{ 0x300A, 0x0288, VR::CS, VM::M1, "Source Movement Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0585[] = {
{ 0x0018, 0x9011, VR::CS, VM::M1, "Multiple Spin Echo" },
{ 0x0018, 0x9401, VR::SQ, VM::M1, "Projection Pixel Calibration Sequence" },
{ 0x0040, 0x0610, VR::SQ, VM::M1, "Specimen Preparation Sequence" },
{ 0x0070, 0x0230, VR::FD, VM::M1, "Rotation Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0586[] = {
{ 0x0018, 0x9012, VR::CS, VM::M1, "Multi-planar Excitation" },
{ 0x0018, 0x9402, VR::FL, VM::M1, "Distance Source to Isocenter" },
{ 0x0022, 0x1220, VR::SQ, VM::M1, "Ultrasound Ophthalmic Axial Length Measurements Sequence" },
{ 0x0040, 0xA089, VR::OB, VM::M1, "Object Directory Binary Identifier (Trial)" },
{ 0x0070, 0x0233, VR::SQ, VM::M1, "Fill Style Sequence" },
{ 0x300A, 0x028A, VR::IS, VM::M1, "Number of Pulses" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0587[] = {
{ 0x0018, 0x9403, VR::FL, VM::M1, "Distance Object to Table Top" },
{ 0x0040, 0x0612, VR::SQ, VM::M1, "Specimen Preparation Step Content Item Sequence" },
{ 0x0040, 0xA088, VR::SQ, VM::M1, "Verifying Observer Identification Code Sequence" },
{ 0x0068, 0x63AC, VR::SQ, VM::M1, "Fixation Method Code Sequence" },
{ 0x0070, 0x0232, VR::SQ, VM::M1, "Line Style Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0588[] = {
{ 0x0018, 0x9014, VR::CS, VM::M1, "Phase Contrast" },
{ 0x0018, 0x9404, VR::FL, VM::M2, "Object Pixel Spacing in Center of Beam" },
{ 0x0054, 0x0211, VR::US, VM::M1, "Number of Triggers in Phase" },
{ 0x300A, 0x028C, VR::DS, VM::M1, "Pulse Repetition Interval" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0589[] = {
{ 0x0018, 0x9015, VR::CS, VM::M1, "Time of Flight Contrast" },
{ 0x0018, 0x9405, VR::SQ, VM::M1, "Positioner Position Sequence" },
{ 0x0054, 0x0210, VR::IS, VM::M1TN, "Trigger Vector" },
{ 0x0070, 0x0234, VR::SQ, VM::M1, "Graphic Group Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0590[] = {
{ 0x0018, 0x9016, VR::CS, VM::M1, "Spoiling" },
{ 0x0018, 0x9406, VR::SQ, VM::M1, "Table Position Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0591[] = {
{ 0x0008, 0x9007, VR::CS, VM::M4, "Frame Type" },
{ 0x0018, 0x9017, VR::CS, VM::M1, "Steady State Pulse Sequence" },
{ 0x0018, 0x9407, VR::SQ, VM::M1, "Collimator Shape Sequence" },
{ 0x0022, 0x1225, VR::SQ, VM::M1, "Optical Ophthalmic Axial Length Measurements Sequence" },
{ 0x0068, 0x63A8, VR::SQ, VM::M1, "Implant Type Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0592[] = {
{ 0x0018, 0x1200, VR::DA, VM::M1TN, "Date of Last Calibration" },
{ 0x0018, 0x1610, VR::IS, VM::M2, "Center of Circular Shutter" },
{ 0x0018, 0x9008, VR::CS, VM::M1, "Echo Pulse Sequence" },
{ 0x0070, 0x0229, VR::LO, VM::M1, "CSS Font Name" },
{ 0x300A, 0x0290, VR::IS, VM::M1, "Source Applicator Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0593[] = {
{ 0x0018, 0x1201, VR::TM, VM::M1TN, "Time of Last Calibration" },
{ 0x0018, 0x9009, VR::CS, VM::M1, "Inversion Recovery" },
{ 0x0020, 0x9421, VR::LO, VM::M1, "Dimension Description Label" },
{ 0x0070, 0x0228, VR::CS, VM::M1, "Font Name Type" },
{ 0x300A, 0x0291, VR::SH, VM::M1, "Source Applicator ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0594[] = {
{ 0x0018, 0x1612, VR::IS, VM::M1, "Radius of Circular Shutter" },
{ 0x300A, 0x0292, VR::CS, VM::M1, "Source Applicator Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0595[] = {
{ 0x0040, 0xA090, VR::SQ, VM::M1, "Equivalent CDA Document Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0596[] = {
{ 0x300A, 0x0294, VR::LO, VM::M1, "Source Applicator Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0597[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0598[] = {
{ 0x300A, 0x0296, VR::DS, VM::M1, "Source Applicator Length" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0599[] = {
{ 0x0068, 0x63B0, VR::SQ, VM::M1, "Mating Feature Sets Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0600[] = {
{ 0x0018, 0x9410, VR::CS, VM::M1, "Planes in Acquisition" },
{ 0x300A, 0x0298, VR::LO, VM::M1, "Source Applicator Manufacturer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0601[] = {
{ 0x0040, 0x0600, VR::LO, VM::M1, "Specimen Short Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0602[] = {
{ 0x0018, 0x9412, VR::SQ, VM::M1, "XA/XRF Frame Characteristics Sequence" },
{ 0x0022, 0x1230, VR::SQ, VM::M1, "Ultrasound Selected Ophthalmic Axial Length Sequence" },
{ 0x0028, 0x9422, VR::SQ, VM::M1, "Pixel Intensity Relationship LUT Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0603[] = {
{ 0x0040, 0x0602, VR::UT, VM::M1, "Specimen Detailed Description" },
{ 0x0048, 0x021A, VR::SQ, VM::M1, "Plane Position (Slide) Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0604[] = {
{ 0x0018, 0x9004, VR::CS, VM::M1, "Content Qualification" },
{ 0x300A, 0x029C, VR::DS, VM::M1, "Source Applicator Wall Nominal Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0605[] = {
{ 0x0018, 0x9005, VR::SH, VM::M1, "Pulse Sequence Name" },
{ 0x0054, 0x0200, VR::DS, VM::M1, "Start Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0606[] = {
{ 0x0018, 0x9006, VR::SQ, VM::M1, "MR Imaging Modifier Sequence" },
{ 0x0048, 0x021F, VR::SL, VM::M1, "Column Position In Total Image Pixel Matrix" },
{ 0x0070, 0x0227, VR::LO, VM::M1, "Font Name" },
{ 0x300A, 0x029E, VR::DS, VM::M1, "Source Applicator Wall Nominal Transmission" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0607[] = {
{ 0x0018, 0x9417, VR::SQ, VM::M1, "Frame Acquisition Sequence" },
{ 0x0048, 0x021E, VR::SL, VM::M1, "Row Position In Total Image Pixel Matrix" },
{ 0x0054, 0x0202, VR::CS, VM::M1, "Type of Detector Motion" },
{ 0x0070, 0x0226, VR::UL, VM::M1, "Compound Graphic Instance ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0608[] = {
{ 0x0018, 0x1620, VR::IS, VM::M2T2N, "Vertices of the Polygonal Shutter" },
{ 0x0018, 0x9428, VR::FL, VM::M1T2, "Intensifier Active Dimension(s)" },
{ 0x0020, 0x1208, VR::IS, VM::M1, "Number of Study Related Instances" },
{ 0x0028, 0x1200, VR::OB, VM::M1, "Gray Lookup Table Data" },
{ 0x300A, 0x02A0, VR::DS, VM::M1, "Source Applicator Step Size" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0609[] = {
{ 0x0018, 0x9429, VR::FL, VM::M2, "Physical Detector Size" },
{ 0x0020, 0x1209, VR::IS, VM::M1, "Number of Series Related Instances" },
{ 0x0028, 0x1201, VR::OW, VM::M1, "Red Palette Color Lookup Table Data" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0610[] = {
{ 0x0018, 0x1622, VR::US, VM::M1, "Shutter Presentation Value" },
{ 0x0028, 0x1202, VR::OW, VM::M1, "Green Palette Color Lookup Table Data" },
{ 0x300A, 0x02A2, VR::IS, VM::M1, "Transfer Tube Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0611[] = {
{ 0x0018, 0x1623, VR::US, VM::M1, "Shutter Overlay Group" },
{ 0x0028, 0x1203, VR::OW, VM::M1, "Blue Palette Color Lookup Table Data" },
{ 0x0072, 0x0218, VR::US, VM::M1TN, "Reference Display Sets" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0612[] = {
{ 0x0018, 0x1624, VR::US, VM::M3, "Shutter Presentation Color CIELab Value" },
{ 0x0028, 0x1204, VR::OW, VM::M1, "Alpha Palette Color Lookup Table Data" },
{ 0x300A, 0x02A4, VR::DS, VM::M1, "Transfer Tube Length" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0613[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0614[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0615[] = {
{ 0x0068, 0x6380, VR::LO, VM::M1, "Surface Model Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0616[] = {
{ 0x0018, 0x9030, VR::FD, VM::M1, "Tag Spacing First Dimension" },
{ 0x0018, 0x9420, VR::CS, VM::M1, "X-Ray Receptor Type" },
{ 0x0020, 0x1200, VR::IS, VM::M1, "Number of Patient Related Studies" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0617[] = {
{ 0x0028, 0x9001, VR::UL, VM::M1, "Data Point Rows" },
{ 0x0028, 0x9411, VR::FL, VM::M1, "Display Filter Percentage" },
{ 0x0040, 0x0220, VR::SQ, VM::M1, "Referenced Non-Image Composite SOP Instance Sequence" },
{ 0x0072, 0x0212, VR::US, VM::M2TN, "Display Set Scrolling Group" },
{ 0x0072, 0x0602, VR::CS, VM::M1, "Sort-by Category" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0618[] = {
{ 0x0018, 0x9032, VR::CS, VM::M1, "Geometry of k-Space Traversal" },
{ 0x0020, 0x1202, VR::IS, VM::M1, "Number of Patient Related Series" },
{ 0x0028, 0x9002, VR::UL, VM::M1, "Data Point Columns" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0619[] = {
{ 0x0018, 0x9033, VR::CS, VM::M1, "Segmented k-Space Traversal" },
{ 0x0018, 0x9423, VR::LO, VM::M1, "Acquisition Protocol Name" },
{ 0x0020, 0x0242, VR::UI, VM::M1, "SOP Instance UID of Concatenation Source" },
{ 0x0028, 0x9003, VR::CS, VM::M1, "Signal Domain Columns" },
{ 0x0072, 0x0210, VR::SQ, VM::M1, "Synchronized Scrolling Sequence" },
{ 0x0072, 0x0600, VR::SQ, VM::M1, "Sorting Operations Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0620[] = {
{ 0x0018, 0x9034, VR::CS, VM::M1, "Rectilinear Phase Encode Reordering" },
{ 0x0018, 0x9424, VR::LT, VM::M1, "Acquisition Protocol Description" },
{ 0x0020, 0x1204, VR::IS, VM::M1, "Number of Patient Related Instances" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0621[] = {
{ 0x0018, 0x9035, VR::FD, VM::M1, "Tag Thickness" },
{ 0x0018, 0x9425, VR::CS, VM::M1, "Contrast/Bolus Ingredient Opaque" },
{ 0x0028, 0x9415, VR::SQ, VM::M1, "Frame Pixel Shift Sequence" },
{ 0x0072, 0x0216, VR::US, VM::M1, "Navigation Display Set" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0622[] = {
{ 0x0018, 0x9036, VR::CS, VM::M1, "Partial Fourier Direction" },
{ 0x0018, 0x9426, VR::FL, VM::M1, "Distance Receptor Plane to Detector Housing" },
{ 0x0020, 0x1206, VR::IS, VM::M1, "Number of Study Related Series" },
{ 0x0028, 0x9416, VR::US, VM::M1, "Subtraction Item ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0623[] = {
{ 0x0018, 0x9037, VR::CS, VM::M1, "Cardiac Synchronization Technique" },
{ 0x0018, 0x9427, VR::CS, VM::M1, "Intensifier Active Shape" },
{ 0x0072, 0x0214, VR::SQ, VM::M1, "Navigation Indicator Sequence" },
{ 0x0072, 0x0604, VR::CS, VM::M1, "Sorting Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0624[] = {
{ 0x0018, 0x9028, VR::CS, VM::M1, "Tagging" },
{ 0x0018, 0x9438, VR::SS, VM::M1, "Exposure Control Sensing Region Upper Horizontal Edge" },
{ 0x0018, 0x9808, VR::CS, VM::M1, "Data Type" },
{ 0x0070, 0x0209, VR::SQ, VM::M1, "Compound Graphic Sequence" },
{ 0x300A, 0x02B0, VR::SQ, VM::M1, "Channel Shield Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0625[] = {
{ 0x0010, 0x9431, VR::FL, VM::M1, "Examined Body Thickness" },
{ 0x0018, 0x9029, VR::CS, VM::M1, "Oversampling Phase" },
{ 0x0018, 0x9439, VR::SS, VM::M1, "Exposure Control Sensing Region Lower Horizontal Edge" },
{ 0x0018, 0x9809, VR::SQ, VM::M1, "Transducer Scan Pattern Code Sequence" },
{ 0x0028, 0x1211, VR::OW, VM::M1, "Large Red Palette Color Lookup Table Data" },
{ 0x003A, 0x0242, VR::SQ, VM::M1, "Channel Display Sequence" },
{ 0x0070, 0x0208, VR::ST, VM::M1, "Graphic Group Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0626[] = {
{ 0x0028, 0x1212, VR::OW, VM::M1, "Large Green Palette Color Lookup Table Data" },
{ 0x003A, 0x0241, VR::US, VM::M1, "Presentation Group Number" },
{ 0x300A, 0x02B2, VR::IS, VM::M1, "Channel Shield Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0627[] = {
{ 0x0018, 0x980B, VR::CS, VM::M1, "Aliased Data Type" },
{ 0x0028, 0x1213, VR::OW, VM::M1, "Large Blue Palette Color Lookup Table Data" },
{ 0x003A, 0x0240, VR::SQ, VM::M1, "Waveform Presentation Group Sequence" },
{ 0x0040, 0xA0B0, VR::US, VM::M2T2N, "Referenced Waveform Channels" },
{ 0x0072, 0x0208, VR::CS, VM::M1, "Partial Data Display Handling" },
{ 0x300A, 0x02B3, VR::SH, VM::M1, "Channel Shield ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0628[] = {
{ 0x0018, 0x980C, VR::CS, VM::M1, "Position Measuring Device Used" },
{ 0x0028, 0x1214, VR::UI, VM::M1, "Large Palette Color Lookup Table UID" },
{ 0x003A, 0x0247, VR::FL, VM::M1, "Fractional Channel Display Scale" },
{ 0x300A, 0x02B4, VR::LO, VM::M1, "Channel Shield Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0629[] = {
{ 0x0018, 0x980D, VR::SQ, VM::M1, "Transducer Geometry Code Sequence" },
{ 0x003A, 0x0246, VR::CS, VM::M1, "Display Shading Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0630[] = {
{ 0x0018, 0x980E, VR::SQ, VM::M1, "Transducer Beam Steering Code Sequence" },
{ 0x003A, 0x0245, VR::FL, VM::M1, "Channel Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0631[] = {
{ 0x0018, 0x980F, VR::SQ, VM::M1, "Transducer Application Code Sequence" },
{ 0x003A, 0x0244, VR::US, VM::M3, "Channel Recommended Display CIELab Value" },
{ 0x0068, 0x6390, VR::FD, VM::M1, "Surface Model Scaling Factor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0632[] = {
{ 0x0018, 0x9020, VR::CS, VM::M1, "Magnetization Transfer" },
{ 0x0018, 0x9430, VR::FL, VM::M2, "Position of Isocenter Projection" },
{ 0x0022, 0x1212, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Length Summation Sequence" },
{ 0x0072, 0x0203, VR::LO, VM::M1, "Display Set Label" },
{ 0x0074, 0x1244, VR::CS, VM::M1, "Subscription List Status" },
{ 0x300A, 0x02B8, VR::DS, VM::M1, "Channel Shield Nominal Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0633[] = {
{ 0x0018, 0x9021, VR::CS, VM::M1, "T2 Preparation" },
{ 0x0018, 0x9801, VR::FD, VM::M1TN, "Depth(s) of Focus" },
{ 0x0040, 0x0620, VR::SQ, VM::M1, "Specimen Localization Content Item Sequence" },
{ 0x0072, 0x0202, VR::US, VM::M1, "Display Set Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0634[] = {
{ 0x0018, 0x9022, VR::CS, VM::M1, "Blood Signal Nulling" },
{ 0x0018, 0x9432, VR::SQ, VM::M1, "Field of View Sequence" },
{ 0x0022, 0x1210, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Total Length Sequence" },
{ 0x0074, 0x1246, VR::CS, VM::M1, "Unified Procedure Step List Status" },
{ 0x300A, 0x02BA, VR::DS, VM::M1, "Channel Shield Nominal Transmission" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0635[] = {
{ 0x0018, 0x9433, VR::LO, VM::M1, "Field of View Description" },
{ 0x0018, 0x9803, VR::SQ, VM::M1, "Excluded Intervals Sequence" },
{ 0x0022, 0x1211, VR::SQ, VM::M1, "Ophthalmic Axial Length Measurements Segmental Length Sequence" },
{ 0x003A, 0x0248, VR::FL, VM::M1, "Absolute Channel Display Scale" },
{ 0x0072, 0x0200, VR::SQ, VM::M1, "Display Sets Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0636[] = {
{ 0x0018, 0x9024, VR::CS, VM::M1, "Saturation Recovery" },
{ 0x0018, 0x9434, VR::SQ, VM::M1, "Exposure Control Sensing Regions Sequence" },
{ 0x0018, 0x9804, VR::DT, VM::M1, "Exclusion Start Datetime" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0637[] = {
{ 0x0018, 0x9025, VR::CS, VM::M1, "Spectrally Selected Suppression" },
{ 0x0018, 0x9435, VR::CS, VM::M1, "Exposure Control Sensing Region Shape" },
{ 0x0018, 0x9805, VR::FD, VM::M1, "Exclusion Duration" },
{ 0x0054, 0x0220, VR::SQ, VM::M1, "View Code Sequence" },
{ 0x0072, 0x0206, VR::LO, VM::M1, "Display Set Presentation Group Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0638[] = {
{ 0x0018, 0x9026, VR::CS, VM::M1, "Spectrally Selected Excitation" },
{ 0x0018, 0x9436, VR::SS, VM::M1, "Exposure Control Sensing Region Left Vertical Edge" },
{ 0x0018, 0x9806, VR::SQ, VM::M1, "US Image Description Sequence" },
{ 0x0070, 0x0207, VR::LO, VM::M1, "Graphic Group Label" },
{ 0x0074, 0x1242, VR::CS, VM::M1, "SCP Status" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0639[] = {
{ 0x0018, 0x9027, VR::CS, VM::M1, "Spatial Pre-saturation" },
{ 0x0018, 0x9437, VR::SS, VM::M1, "Exposure Control Sensing Region Right Vertical Edge" },
{ 0x0018, 0x9807, VR::SQ, VM::M1, "Image Data Type Sequence" },
{ 0x0054, 0x0222, VR::SQ, VM::M1, "View Modifier Code Sequence" },
{ 0x0072, 0x0204, VR::US, VM::M1, "Display Set Presentation Group" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0640[] = {
{ 0x0008, 0x2200, VR::CS, VM::M1, "Transducer Position" },
{ 0x0040, 0xA040, VR::CS, VM::M1, "Value Type" },
{ 0x2200, 0x0008, VR::CS, VM::M1, "Include Non-DICOM Objects" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0641[] = {
{ 0x2200, 0x0009, VR::CS, VM::M1, "Include Display Application" },
{ 0x3008, 0x0240, VR::SQ, VM::M1, "Fraction Status Summary Sequence" },
{ 0x300A, 0x0242, VR::SH, VM::M1, "Template Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0642[] = {
{ 0x0088, 0x0200, VR::SQ, VM::M1, "Icon Image Sequence" },
{ 0x2200, 0x000A, VR::CS, VM::M1, "Preserve Composite Instances After Media Creation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0643[] = {
{ 0x0040, 0xA043, VR::SQ, VM::M1, "Concept Name Code Sequence" },
{ 0x2200, 0x000B, VR::US, VM::M1, "Total Number of Pieces of Media Created" },
{ 0x300A, 0x0240, VR::IS, VM::M1, "Template Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0644[] = {
{ 0x0008, 0x2204, VR::CS, VM::M1, "Transducer Orientation" },
{ 0x0068, 0x6360, VR::SQ, VM::M1, "Surface Model Description Sequence" },
{ 0x2200, 0x000C, VR::LO, VM::M1, "Requested Media Application Profile" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0645[] = {
{ 0x2200, 0x000D, VR::SQ, VM::M1, "Referenced Storage Media Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0646[] = {
{ 0x2200, 0x000E, VR::AT, VM::M1TN, "Failure Attributes" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0647[] = {
{ 0x0040, 0xA047, VR::LO, VM::M1, "Measurement Precision Description (Trial)" },
{ 0x2200, 0x000F, VR::CS, VM::M1, "Allow Lossy Compression" },
{ 0x300A, 0x0244, VR::LO, VM::M1, "Template Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0648[] = {
{ 0x0008, 0x2208, VR::CS, VM::M1, "Anatomic Structure" },
{ 0x0010, 0x2210, VR::CS, VM::M1, "Anatomical Orientation Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0649[] = {
{ 0x2200, 0x0001, VR::CS, VM::M1, "Label Using Information Extracted From Instances" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0650[] = {
{ 0x2200, 0x0002, VR::UT, VM::M1, "Label Text" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0651[] = {
{ 0x2200, 0x0003, VR::CS, VM::M1, "Label Style Selection" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0652[] = {
{ 0x0014, 0x2210, VR::OB, VM::M1, "Coordinate System Axis Values" },
{ 0x2200, 0x0004, VR::LT, VM::M1, "Media Disposition" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0653[] = {
{ 0x2200, 0x0005, VR::LT, VM::M1, "Barcode Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0654[] = {
{ 0x2200, 0x0006, VR::CS, VM::M1, "Barcode Symbology" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0655[] = {
{ 0x2200, 0x0007, VR::CS, VM::M1, "Allow Media Splitting" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0656[] = {
{ 0x0014, 0x220C, VR::CS, VM::M1, "Coordinate System Axis Type" },
{ 0x0040, 0xA050, VR::CS, VM::M1, "Continuity Of Content" },
{ 0x3008, 0x0251, VR::TM, VM::M1, "Treatment Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0657[] = {
{ 0x3008, 0x0250, VR::DA, VM::M1, "Treatment Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0658[] = {
{ 0x0014, 0x220E, VR::CS, VM::M1, "Coordinate System Axis Units" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0659[] = {
{ 0x300A, 0x0250, VR::DS, VM::M1, "Total Reference Air Kerma" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0660[] = {
{ 0x0014, 0x2208, VR::CS, VM::M1, "Coordinate System Data Set Mapping" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0661[] = {
{ 0x0040, 0x9096, VR::SQ, VM::M1, "Real World Value Mapping Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0662[] = {
{ 0x0014, 0x220A, VR::IS, VM::M1, "Coordinate System Axis Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0663[] = {
{ 0x0040, 0x9094, VR::SQ, VM::M1, "Referenced Image Real World Value Mapping Sequence" },
{ 0x0040, 0xA057, VR::CS, VM::M1TN, "Urgency or Priority Alerts (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0664[] = {
{ 0x0008, 0x2218, VR::SQ, VM::M1, "Anatomic Region Sequence" },
{ 0x0014, 0x2204, VR::SQ, VM::M1, "Coordinate System Axes Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0665[] = {
{ 0x0010, 0x2201, VR::LO, VM::M1, "Patient Species Description" },
{ 0x0018, 0xA001, VR::SQ, VM::M1, "Contributing Equipment Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0666[] = {
{ 0x0010, 0x2202, VR::SQ, VM::M1, "Patient Species Code Sequence" },
{ 0x0014, 0x2206, VR::ST, VM::M1, "Coordinate System Axis Description" },
{ 0x0018, 0xA002, VR::DT, VM::M1, "Contribution Date Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0667[] = {
{ 0x0010, 0x2203, VR::CS, VM::M1, "Patient's Sex Neutered" },
{ 0x0018, 0xA003, VR::ST, VM::M1, "Contribution Description" },
{ 0x0040, 0x9098, VR::SQ, VM::M1, "Pixel Value Mapping Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0668[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0669[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0670[] = {
{ 0x0014, 0x2202, VR::IS, VM::M1, "Coordinate System Number of Axes" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0671[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0672[] = {
{ 0x0008, 0x2220, VR::SQ, VM::M1, "Anatomic Region Modifier Sequence" },
{ 0x0040, 0x06FA, VR::LO, VM::M1, "Slide Identifier" },
{ 0x0040, 0xA060, VR::LO, VM::M1, "Sequencing Indicator (Trial)" },
{ 0x300A, 0x0263, VR::SH, VM::M1, "Brachy Accessory Device ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0673[] = {
{ 0x0040, 0xB020, VR::SQ, VM::M1, "Waveform Annotation Sequence" },
{ 0x0068, 0x6345, VR::ST, VM::M1, "HPGL Pen Description" },
{ 0x300A, 0x0262, VR::IS, VM::M1, "Brachy Accessory Device Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0674[] = {
{ 0x0068, 0x6346, VR::FD, VM::M2, "Recommended Rotation Point" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0675[] = {
{ 0x0068, 0x6347, VR::FD, VM::M4, "Bounding Rectangle" },
{ 0x300A, 0x0260, VR::SQ, VM::M1, "Brachy Accessory Device Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0676[] = {
{ 0x0068, 0x6340, VR::LO, VM::M1, "HPGL Pen Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0677[] = {
{ 0x300A, 0x0266, VR::LO, VM::M1, "Brachy Accessory Device Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0678[] = {
{ 0x0040, 0xA066, VR::SQ, VM::M1, "Document Identifier Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0679[] = {
{ 0x0040, 0xA067, VR::PN, VM::M1, "Document Author (Trial)" },
{ 0x300A, 0x0264, VR::CS, VM::M1, "Brachy Accessory Device Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0680[] = {
{ 0x0008, 0x2228, VR::SQ, VM::M1, "Primary Anatomic Structure Sequence" },
{ 0x0040, 0xA068, VR::SQ, VM::M1, "Document Author Identifier Code Sequence (Trial)" },
{ 0x2200, 0x0020, VR::CS, VM::M1, "Request Priority" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0681[] = {
{ 0x0008, 0x2229, VR::SQ, VM::M1, "Anatomic Structure, Space or Region Sequence" },
{ 0x300A, 0x026A, VR::DS, VM::M1, "Brachy Accessory Device Nominal Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0682[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0683[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0684[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0685[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0686[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0687[] = {
{ 0x300A, 0x026C, VR::DS, VM::M1, "Brachy Accessory Device Nominal Transmission" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0688[] = {
{ 0x0008, 0x2230, VR::SQ, VM::M1, "Primary Anatomic Structure Modifier Sequence" },
{ 0x0014, 0x222C, VR::DS, VM::M1TN, "Coordinate System Transform Translation Matrix" },
{ 0x0040, 0xA070, VR::SQ, VM::M1, "Identifier Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0689[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0690[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0691[] = {
{ 0x0040, 0xA073, VR::SQ, VM::M1, "Verifying Observer Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0692[] = {
{ 0x0014, 0x2228, VR::CS, VM::M1, "Transformed Axis Units" },
{ 0x0040, 0xA074, VR::OB, VM::M1, "Object Binary Identifier (Trial)" },
{ 0x0068, 0x6350, VR::US, VM::M1TN, "Implant Template 3D Model Surface Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0693[] = {
{ 0x0040, 0xA075, VR::PN, VM::M1, "Verifying Observer Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0694[] = {
{ 0x0014, 0x222A, VR::DS, VM::M1TN, "Coordinate System Transform Rotation and Scale Matrix" },
{ 0x0040, 0xA076, VR::SQ, VM::M1, "Documenting Observer Identifier Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0695[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0696[] = {
{ 0x0014, 0x2224, VR::IS, VM::M1, "Transform Number of Axes" },
{ 0x0040, 0xA078, VR::SQ, VM::M1, "Author Observer Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0697[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0698[] = {
{ 0x0014, 0x2226, VR::IS, VM::M1TN, "Transform Order of Axes" },
{ 0x0040, 0xA07A, VR::SQ, VM::M1, "Participant Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0699[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0700[] = {
{ 0x0014, 0x2220, VR::SQ, VM::M1, "Coordinate System Transform Sequence" },
{ 0x0040, 0xA07C, VR::SQ, VM::M1, "Custodial Organization Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0701[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0702[] = {
{ 0x0014, 0x2222, VR::ST, VM::M1, "Transform Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0703[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0704[] = {
{ 0x3008, 0x0200, VR::CS, VM::M1, "Current Treatment Status" },
{ 0x300A, 0x0202, VR::CS, VM::M1, "Brachy Treatment Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0705[] = {
{ 0x0008, 0x2240, VR::SQ, VM::M1, "Transducer Position Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0706[] = {
{ 0x0018, 0x9098, VR::FD, VM::M1T2, "Transmitter Frequency" },
{ 0x3008, 0x0202, VR::ST, VM::M1, "Treatment Status Comment" },
{ 0x300A, 0x0200, VR::CS, VM::M1, "Brachy Treatment Technique" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0707[] = {
{ 0x0008, 0x2242, VR::SQ, VM::M1, "Transducer Position Modifier Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0708[] = {
{ 0x300A, 0x0206, VR::SQ, VM::M1, "Treatment Machine Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0709[] = {
{ 0x0008, 0x2244, VR::SQ, VM::M1, "Transducer Orientation Sequence" },
{ 0x0068, 0x6320, VR::SQ, VM::M1, "HPGL Pen Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0710[] = {
{ 0x0040, 0xA007, VR::CS, VM::M1, "Findings Flag (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0711[] = {
{ 0x0008, 0x2246, VR::SQ, VM::M1, "Transducer Orientation Modifier Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0712[] = {
{ 0x0018, 0x9092, VR::SQ, VM::M1, "Velocity Encoding Acquisition Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0713[] = {
{ 0x0018, 0x9093, VR::US, VM::M1, "Number of k-Space Trajectories" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0714[] = {
{ 0x0018, 0x9090, VR::FD, VM::M3, "Velocity Encoding Direction" },
{ 0x0040, 0x0281, VR::SQ, VM::M1, "Performed Procedure Step Discontinuation Reason Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0715[] = {
{ 0x0018, 0x9091, VR::FD, VM::M1, "Velocity Encoding Minimum Value" },
{ 0x0040, 0x0280, VR::ST, VM::M1, "Comments on the Performed Procedure Step" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0716[] = {
{ 0x0018, 0x9096, VR::FD, VM::M1, "Parallel Reduction Factor In-plane (Retired)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0717[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0718[] = {
{ 0x0018, 0x9094, VR::CS, VM::M1, "Coverage of k-Space" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0719[] = {
{ 0x0018, 0x9095, VR::UL, VM::M1, "Spectroscopy Acquisition Phase Rows" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0720[] = {
{ 0x0008, 0x2251, VR::SQ, VM::M1, "Anatomic Structure Space Or Region Code Sequence (Trial)" },
{ 0x300A, 0x0212, VR::IS, VM::M1, "Source Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0721[] = {
{ 0x0040, 0xA010, VR::CS, VM::M1, "Relationship Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0722[] = {
{ 0x0008, 0x2253, VR::SQ, VM::M1, "Anatomic Portal Of Entrance Code Sequence (Trial)" },
{ 0x0040, 0xA403, VR::CS, VM::M1, "Observation Subject Class (Trial)" },
{ 0x300A, 0x0210, VR::SQ, VM::M1, "Source Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0723[] = {
{ 0x0018, 0x9089, VR::FD, VM::M3, "Diffusion Gradient Orientation" },
{ 0x0040, 0xA402, VR::UI, VM::M1, "Observation Subject UID (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0724[] = {
{ 0x0008, 0x2255, VR::SQ, VM::M1, "Anatomic Approach Direction Code Sequence (Trial)" },
{ 0x300A, 0x0216, VR::LO, VM::M1, "Source Manufacturer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0725[] = {
{ 0x0040, 0xA404, VR::SQ, VM::M1, "Observation Subject Type Code Sequence (Trial)" },
{ 0x0068, 0x6330, VR::US, VM::M1, "HPGL Pen Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0726[] = {
{ 0x0008, 0x2257, VR::SQ, VM::M1, "Anatomic Perspective Code Sequence (Trial)" },
{ 0x300A, 0x0214, VR::CS, VM::M1, "Source Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0727[] = {
{ 0x0008, 0x2256, VR::ST, VM::M1, "Anatomic Perspective Description (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0728[] = {
{ 0x0008, 0x2259, VR::SQ, VM::M1, "Anatomic Location Of Examining Instrument Code Sequence (Trial)" },
{ 0x0008, 0x9092, VR::SQ, VM::M1, "Referenced Image Evidence Sequence" },
{ 0x0018, 0x9082, VR::FD, VM::M1, "Effective Echo Time" },
{ 0x0040, 0x0293, VR::SQ, VM::M1, "Quantity Sequence" },
{ 0x300A, 0x021A, VR::DS, VM::M1, "Active Source Length" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0729[] = {
{ 0x0008, 0x2258, VR::ST, VM::M1, "Anatomic Location Of Examining Instrument Description (Trial)" },
{ 0x0018, 0x9083, VR::SQ, VM::M1, "Metabolite Map Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0730[] = {
{ 0x0018, 0x9080, VR::ST, VM::M1, "Metabolite Map Description" },
{ 0x300A, 0x0218, VR::DS, VM::M1, "Active Source Diameter" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0731[] = {
{ 0x0008, 0x225A, VR::SQ, VM::M1, "Anatomic Structure Space Or Region Modifier Code Sequence (Trial)" },
{ 0x0018, 0x9081, VR::CS, VM::M1, "Partial Fourier" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0732[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0733[] = {
{ 0x0008, 0x225C, VR::SQ, VM::M1, "OnAxis Background Anatomic Structure Code Sequence (Trial)" },
{ 0x0018, 0x9087, VR::FD, VM::M1, "Diffusion b-value" },
{ 0x0040, 0x0296, VR::SQ, VM::M1, "Billing Item Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0734[] = {
{ 0x0018, 0x9084, VR::SQ, VM::M1, "Chemical Shift Sequence" },
{ 0x0040, 0x0295, VR::SQ, VM::M1, "Measuring Units Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0735[] = {
{ 0x0018, 0x9085, VR::CS, VM::M1, "Cardiac Signal Source" },
{ 0x0040, 0x0294, VR::DS, VM::M1, "Quantity" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0736[] = {
{ 0x0040, 0xA021, VR::UI, VM::M1, "Findings Group UID (Trial)" },
{ 0x3008, 0x0220, VR::SQ, VM::M1, "Fraction Group Summary Sequence" },
{ 0x300A, 0x0222, VR::DS, VM::M1, "Source Encapsulation Nominal Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0737[] = {
{ 0x0040, 0xA020, VR::SQ, VM::M1, "Findings Sequence (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0738[] = {
{ 0x0040, 0xA023, VR::DA, VM::M1, "Findings Group Recording Date (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0739[] = {
{ 0x0040, 0xA022, VR::UI, VM::M1, "Referenced Findings Group UID (Trial)" },
{ 0x3008, 0x0223, VR::IS, VM::M1, "Referenced Fraction Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0740[] = {
{ 0x3008, 0x0224, VR::CS, VM::M1, "Fraction Group Type" },
{ 0x300A, 0x0226, VR::LO, VM::M1, "Source Isotope Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0741[] = {
{ 0x0040, 0xA024, VR::TM, VM::M1, "Findings Group Recording Time (Trial)" },
{ 0x0068, 0x6300, VR::OB, VM::M1, "HPGL Document" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0742[] = {
{ 0x0040, 0xA027, VR::LO, VM::M1, "Verifying Organization" },
{ 0x300A, 0x0224, VR::DS, VM::M1, "Source Encapsulation Nominal Transmission" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0743[] = {
{ 0x0040, 0xA026, VR::SQ, VM::M1, "Findings Source Category Code Sequence (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0744[] = {
{ 0x300A, 0x022A, VR::DS, VM::M1, "Reference Air Kerma Rate" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0745[] = {
{ 0x0040, 0xA028, VR::SQ, VM::M1, "Documenting Organization Identifier Code Sequence (Trial)" },
{ 0x300A, 0x022B, VR::DS, VM::M1, "Source Strength" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0746[] = {
{ 0x300A, 0x0228, VR::DS, VM::M1, "Source Isotope Half Life" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0747[] = {
{ 0x300A, 0x0229, VR::CS, VM::M1, "Source Strength Units" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0748[] = {
{ 0x300A, 0x022E, VR::TM, VM::M1, "Source Strength Reference Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0749[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0750[] = {
{ 0x0070, 0x0295, VR::UL, VM::M1, "Graphic Group ID" },
{ 0x300A, 0x022C, VR::DA, VM::M1, "Source Strength Reference Date" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0751[] = {
{ 0x0070, 0x0294, VR::CS, VM::M1, "Compound Graphic Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0752[] = {
{ 0x3008, 0x0230, VR::CS, VM::M1, "Beam Stopper Position" },
{ 0x300A, 0x0232, VR::CS, VM::M1, "Application Setup Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0753[] = {
{ 0x0040, 0xA030, VR::DT, VM::M1, "Verification Date Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0754[] = {
{ 0x0070, 0x0289, VR::SH, VM::M1, "Tick Label" },
{ 0x300A, 0x0230, VR::SQ, VM::M1, "Application Setup Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0755[] = {
{ 0x0028, 0x9099, VR::US, VM::M1, "Largest Monochrome Pixel Value" },
{ 0x0040, 0xA032, VR::DT, VM::M1, "Observation Date Time" },
{ 0x0070, 0x0288, VR::FL, VM::M1, "Tick Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0756[] = {
{ 0x300A, 0x0236, VR::LO, VM::M1, "Application Setup Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0757[] = {
{ 0x0068, 0x6310, VR::US, VM::M1, "HPGL Contour Pen Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0758[] = {
{ 0x300A, 0x0234, VR::IS, VM::M1, "Application Setup Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0759[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0760[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0761[] = {
{ 0x0070, 0x0282, VR::CS, VM::M1, "Compound Graphic Units" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0762[] = {
{ 0x300A, 0x0238, VR::LO, VM::M1, "Application Setup Manufacturer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0763[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0764[] = {
{ 0x0070, 0x0287, VR::SQ, VM::M1, "Major Ticks Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0765[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0766[] = {
{ 0x0070, 0x0285, VR::FL, VM::M1, "Pattern Off Opacity" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0767[] = {
{ 0x0070, 0x0284, VR::FL, VM::M1, "Pattern On Opacity" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0768[] = {
{ 0x0020, 0x9165, VR::AT, VM::M1, "Dimension Index Pointer" },
{ 0x4008, 0x0200, VR::SH, VM::M1, "Interpretation ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0769[] = {
{ 0x0020, 0x9164, VR::UI, VM::M1, "Dimension Organization UID" },
{ 0x0074, 0x1338, VR::FD, VM::M1, "Double Exposure Meterset" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0770[] = {
{ 0x0020, 0x9167, VR::AT, VM::M1, "Functional Group Pointer" },
{ 0x0068, 0x62E0, VR::SQ, VM::M1, "View Orientation Code Sequence" },
{ 0x4008, 0x0202, VR::LO, VM::M1, "Interpretation ID Issuer" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0771[] = {
{ 0x0074, 0x133A, VR::FD, VM::M4, "Double Exposure Field Delta" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0772[] = {
{ 0x0018, 0x9159, VR::UL, VM::M1, "Spectroscopy Acquisition Out-of-plane Phase Steps" },
{ 0x0020, 0x9161, VR::UI, VM::M1, "Concatenation UID" },
{ 0x0028, 0x0730, VR::US, VM::M1, "Adaptive Map Format" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0773[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0774[] = {
{ 0x0020, 0x9163, VR::US, VM::M1, "In-concatenation Total Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0775[] = {
{ 0x0020, 0x9162, VR::US, VM::M1, "In-concatenation Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0776[] = {
{ 0x0018, 0x9155, VR::FD, VM::M1, "Parallel Reduction Factor out-of-plane" },
{ 0x0024, 0x0320, VR::SQ, VM::M1, "Visual Field Global Results Index Sequence" },
{ 0x0054, 0x1311, VR::IS, VM::M1TN, "Secondary Counts Accumulated" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0777[] = {
{ 0x0054, 0x1310, VR::IS, VM::M1, "Primary (Prompts) Counts Accumulated" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0778[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0779[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0780[] = {
{ 0x0018, 0x9151, VR::DT, VM::M1, "Frame Reference DateTime" },
{ 0x0040, 0x0340, VR::SQ, VM::M1, "Performed Series Sequence" },
{ 0x0400, 0x0310, VR::OB, VM::M1, "Certified Timestamp" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0781[] = {
{ 0x0024, 0x0325, VR::SQ, VM::M1, "Data Observation Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0782[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0783[] = {
{ 0x0018, 0x9152, VR::SQ, VM::M1, "MR Metabolite Map Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0784[] = {
{ 0x0024, 0x0338, VR::CS, VM::M1, "Index Normals Flag" },
{ 0x0068, 0x62F2, VR::FD, VM::M1, "HPGL Document Scaling" },
{ 0x4008, 0x0210, VR::CS, VM::M1, "Interpretation Type ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0785[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0786[] = {
{ 0x0068, 0x62F0, VR::FD, VM::M9, "View Orientation Modifier" },
{ 0x4008, 0x0212, VR::CS, VM::M1, "Interpretation Status ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0787[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0788[] = {
{ 0x0028, 0x0720, VR::US, VM::M1, "Zonal Map Number Format" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0789[] = {
{ 0x0028, 0x0721, VR::AT, VM::M1TN, "Zonal Map Location" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0790[] = {
{ 0x0028, 0x0722, VR::US, VM::M1, "Zonal Map Format" },
{ 0x0040, 0x074A, VR::DS, VM::M1, "Z Offset in Slide Coordinate System" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0791[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0792[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0793[] = {
{ 0x0008, 0x9154, VR::SQ, VM::M1, "Source Image Evidence Sequence" },
{ 0x0054, 0x1300, VR::DS, VM::M1, "Frame Reference Time" },
{ 0x0400, 0x0305, VR::CS, VM::M1, "Certified Timestamp Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0794[] = {
{ 0x0018, 0x9147, VR::CS, VM::M1, "Diffusion Anisotropy Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0795[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0796[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0797[] = {
{ 0x0074, 0x1324, VR::UL, VM::M1, "Beam Order Index" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0798[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0799[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0800[] = {
{ 0x0024, 0x0308, VR::LO, VM::M1, "Data Set Source" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0801[] = {
{ 0x0024, 0x0309, VR::LO, VM::M1, "Data Set Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0802[] = {
{ 0x0068, 0x62C0, VR::SQ, VM::M1, "HPGL Document Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0803[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0804[] = {
{ 0x0018, 0x9179, VR::CS, VM::M1, "Specific Absorption Rate Definition" },
{ 0x0028, 0x0300, VR::CS, VM::M1, "Quality Control Image" },
{ 0x0028, 0x0710, VR::US, VM::M1, "Normalization Factor Format" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0805[] = {
{ 0x0018, 0x9178, VR::CS, VM::M1, "Operating Mode" },
{ 0x0028, 0x0301, VR::CS, VM::M1, "Burned In Annotation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0806[] = {
{ 0x0028, 0x0302, VR::CS, VM::M1, "Recognizable Visual Features" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0807[] = {
{ 0x0028, 0x0303, VR::CS, VM::M1, "Longitudinal Temporal Information Modified" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0808[] = {
{ 0x0018, 0x9175, VR::LO, VM::M1, "Applicable Safety Standard Description" },
{ 0x0028, 0x9145, VR::SQ, VM::M1, "Pixel Value Transformation Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0809[] = {
{ 0x0018, 0x9174, VR::CS, VM::M1, "Applicable Safety Standard Agency" },
{ 0x0054, 0x1330, VR::US, VM::M1, "Image Index" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0810[] = {
{ 0x0018, 0x9177, VR::CS, VM::M1, "Operating Mode Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0811[] = {
{ 0x0018, 0x9176, VR::SQ, VM::M1, "Operating Mode Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0812[] = {
{ 0x0018, 0x9171, VR::CS, VM::M1, "Respiratory Signal Source" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0813[] = {
{ 0x0018, 0x9170, VR::CS, VM::M1, "Respiratory Motion Compensation Technique" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0814[] = {
{ 0x0018, 0x9173, VR::CS, VM::M1, "Bulk Motion Signal Source" },
{ 0x0024, 0x0306, VR::LO, VM::M1, "Data Set Name" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0815[] = {
{ 0x0018, 0x9172, VR::CS, VM::M1, "Bulk Motion Compensation Technique" },
{ 0x0024, 0x0307, VR::LO, VM::M1, "Data Set Version" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0816[] = {
{ 0x0020, 0x9155, VR::FL, VM::M1, "Actual Cardiac Trigger Time Prior To R-Peak" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0817[] = {
{ 0x0020, 0x9154, VR::FL, VM::M1, "Nominal Cardiac Trigger Time Prior To R-Peak" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0818[] = {
{ 0x0020, 0x9157, VR::UL, VM::M1TN, "Dimension Index Values" },
{ 0x0068, 0x62D0, VR::US, VM::M1, "HPGL Document ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0819[] = {
{ 0x0020, 0x9156, VR::US, VM::M1, "Frame Acquisition Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0820[] = {
{ 0x0018, 0x9169, VR::CS, VM::M1, "Cardiac Beat Rejection Technique" },
{ 0x0028, 0x0700, VR::LO, VM::M1, "DCT Label" },
{ 0x0028, 0x1351, VR::ST, VM::M1, "Partial View Description" },
{ 0x0038, 0x0300, VR::LO, VM::M1, "Current Patient Location" },
{ 0x003A, 0x0302, VR::CS, VM::M1, "Channel Mode" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0821[] = {
{ 0x0018, 0x9168, VR::FD, VM::M1, "Parallel Reduction Factor Second In-plane" },
{ 0x0028, 0x0701, VR::CS, VM::M1TN, "Data Block Description" },
{ 0x0028, 0x1350, VR::CS, VM::M1, "Partial View" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0822[] = {
{ 0x0020, 0x9153, VR::FD, VM::M1, "Nominal Cardiac Trigger Delay Time" },
{ 0x0028, 0x0702, VR::AT, VM::M1TN, "Data Block" },
{ 0x003A, 0x0300, VR::SQ, VM::M1, "Multiplexed Audio Channels Description Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0823[] = {
{ 0x0028, 0x1352, VR::SQ, VM::M1, "Partial View Code Sequence" },
{ 0x003A, 0x0301, VR::IS, VM::M1, "Channel Identification Code" },
{ 0x0068, 0x62D5, VR::LO, VM::M1, "HPGL Document Label" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0824[] = {
{ 0x0054, 0x1321, VR::DS, VM::M1, "Decay Factor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0825[] = {
{ 0x0054, 0x1320, VR::DS, VM::M1, "Slice Sensitivity Factor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0826[] = {
{ 0x0054, 0x1323, VR::DS, VM::M1, "Scatter Fraction Factor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0827[] = {
{ 0x0018, 0x9166, VR::CS, VM::M1, "Bulk Motion Status" },
{ 0x0054, 0x1322, VR::DS, VM::M1, "Dose Calibration Factor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0828[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0829[] = {
{ 0x0020, 0x9158, VR::LT, VM::M1, "Frame Comments" },
{ 0x0054, 0x1324, VR::DS, VM::M1, "Dead Time Factor" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0830[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0831[] = {
{ 0x0024, 0x0317, VR::SQ, VM::M1, "Visual Field Test Reliability Global Index Sequence" },
{ 0x0028, 0x135A, VR::CS, VM::M1, "Spatial Locations Preserved" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0832[] = {
{ 0x0018, 0x1314, VR::DS, VM::M1, "Flip Angle" },
{ 0x0018, 0x1704, VR::IS, VM::M1, "Collimator Right Vertical Edge" },
{ 0x0018, 0x5210, VR::DS, VM::M6, "Image Transformation Matrix" },
{ 0x300A, 0x0384, VR::FL, VM::M1, "Range Modulator Gating Stop Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0833[] = {
{ 0x0018, 0x1315, VR::CS, VM::M1, "Variable Flip Angle Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0834[] = {
{ 0x0018, 0x1316, VR::DS, VM::M1, "SAR" },
{ 0x0018, 0x1706, VR::IS, VM::M1, "Collimator Upper Horizontal Edge" },
{ 0x0018, 0x5212, VR::DS, VM::M3, "Image Translation Vector" },
{ 0x0020, 0x9536, VR::US, VM::M1, "Reconstruction Index" },
{ 0x300A, 0x0386, VR::FL, VM::M1, "Range Modulator Gating Start Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0835[] = {
{ 0x0040, 0x030E, VR::SQ, VM::M1, "Exposure Dose Sequence" },
{ 0x0068, 0x62A0, VR::SQ, VM::M1, "Implant Regulatory Disapproval Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0836[] = {
{ 0x0018, 0x1310, VR::US, VM::M4, "Acquisition Matrix" },
{ 0x0018, 0x1700, VR::CS, VM::M1T3, "Collimator Shape" },
{ 0x0018, 0x9118, VR::SQ, VM::M1, "Cardiac Synchronization Sequence" },
{ 0x0018, 0x9508, VR::FL, VM::M1, "Primary Positioner Scan Arc" },
{ 0x0048, 0x0301, VR::CS, VM::M1, "Pixel Origin Interpretation" },
{ 0x300A, 0x0380, VR::SQ, VM::M1, "Range Modulator Settings Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0837[] = {
{ 0x0018, 0x9119, VR::SQ, VM::M1, "MR Averages Sequence" },
{ 0x0018, 0x9509, VR::FL, VM::M1, "Secondary Positioner Scan Arc" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0838[] = {
{ 0x0018, 0x1312, VR::CS, VM::M1, "In-plane Phase Encoding Direction" },
{ 0x0018, 0x1702, VR::IS, VM::M1, "Collimator Left Vertical Edge" },
{ 0x0068, 0x62A5, VR::FD, VM::M1, "Overall Template Spatial Tolerance" },
{ 0x300A, 0x0382, VR::FL, VM::M1, "Range Modulator Gating Start Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0839[] = {
{ 0x0040, 0x071A, VR::SQ, VM::M1, "Image Center Point Coordinates Sequence" },
{ 0x0040, 0xA180, VR::US, VM::M1, "Annotation Group Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0840[] = {
{ 0x0018, 0x9114, VR::SQ, VM::M1, "MR Echo Sequence" },
{ 0x0018, 0x9504, VR::SQ, VM::M1, "X-Ray 3D Frame Type Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0841[] = {
{ 0x0018, 0x9115, VR::SQ, VM::M1, "MR Modifier Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0842[] = {
{ 0x0018, 0x9506, VR::SQ, VM::M1, "Contributing Sources Sequence" },
{ 0x0040, 0x0307, VR::DS, VM::M1, "Distance Source to Support" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0843[] = {
{ 0x0018, 0x9117, VR::SQ, VM::M1, "MR Diffusion Sequence" },
{ 0x0018, 0x9507, VR::SQ, VM::M1, "X-Ray 3D Acquisition Sequence" },
{ 0x0028, 0x9537, VR::CS, VM::M1, "Equipment Coordinate System Identification" },
{ 0x0040, 0x0306, VR::DS, VM::M1, "Distance Source to Entrance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0844[] = {
{ 0x0018, 0x1318, VR::DS, VM::M1, "dB/dt" },
{ 0x0018, 0x1708, VR::IS, VM::M1, "Collimator Lower Horizontal Edge" },
{ 0x0018, 0x8151, VR::DS, VM::M1, "X-Ray Tube Current in uA" },
{ 0x0020, 0x9128, VR::UL, VM::M1, "Temporal Position Index" },
{ 0x0040, 0x0301, VR::US, VM::M1, "Total Number of Exposures" },
{ 0x300A, 0x0388, VR::FL, VM::M1, "Range Modulator Gating Stop Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0845[] = {
{ 0x0018, 0x8150, VR::DS, VM::M1, "Exposure Time in uS" },
{ 0x0040, 0x0300, VR::US, VM::M1, "Total Time of Fluoroscopy" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0846[] = {
{ 0x0018, 0x9112, VR::SQ, VM::M1, "MR Timing and Related Parameters Sequence" },
{ 0x0040, 0x0303, VR::US, VM::M1T2, "Exposed Area" },
{ 0x300A, 0x038A, VR::FL, VM::M1, "Isocenter to Range Modulator Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0847[] = {
{ 0x0040, 0x0302, VR::US, VM::M1, "Entrance Dose" },
{ 0x0072, 0x0330, VR::FD, VM::M1, "Cine Relative to Real-Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0848[] = {
{ 0x300A, 0x0394, VR::FL, VM::M1TN, "Scan Spot Position Map" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0849[] = {
{ 0x0054, 0x0308, VR::US, VM::M1, "Energy Window Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0850[] = {
{ 0x0040, 0xA195, VR::SQ, VM::M1, "Modifier Code Sequence" },
{ 0x300A, 0x0396, VR::FL, VM::M1TN, "Scan Spot Meterset Weights" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0851[] = {
{ 0x0040, 0xA194, VR::CS, VM::M1, "Measurement Automation (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0852[] = {
{ 0x0018, 0x1300, VR::DS, VM::M1, "Scan Velocity" },
{ 0x0018, 0x1710, VR::IS, VM::M2, "Center of Circular Collimator" },
{ 0x0040, 0xA193, VR::TM, VM::M1, "Observation Time (Trial)" },
{ 0x300A, 0x0390, VR::SH, VM::M1, "Scan Spot Tune ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0853[] = {
{ 0x0018, 0x1301, VR::CS, VM::M1TN, "Whole Body Technique" },
{ 0x0040, 0x0318, VR::CS, VM::M1, "Organ Exposed" },
{ 0x0040, 0xA192, VR::DA, VM::M1, "Observation Date (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0854[] = {
{ 0x0018, 0x1302, VR::IS, VM::M1, "Scan Length" },
{ 0x0018, 0x1712, VR::IS, VM::M1, "Radius of Circular Collimator" },
{ 0x300A, 0x0392, VR::IS, VM::M1, "Number of Scan Spot Positions" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0855[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0856[] = {
{ 0x0018, 0x9104, VR::FD, VM::M1, "Slab Thickness" },
{ 0x0018, 0x9514, VR::FL, VM::M1, "Primary Positioner Increment" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0857[] = {
{ 0x0018, 0x9105, VR::FD, VM::M3, "Slab Orientation" },
{ 0x0018, 0x9515, VR::FL, VM::M1, "Secondary Positioner Increment" },
{ 0x0040, 0x0314, VR::DS, VM::M1, "Half Value Layer" },
{ 0x0054, 0x0300, VR::SQ, VM::M1, "Radionuclide Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0858[] = {
{ 0x0018, 0x9106, VR::FD, VM::M3, "Mid Slab Position" },
{ 0x0018, 0x9516, VR::DT, VM::M1, "Start Acquisition DateTime" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0859[] = {
{ 0x0018, 0x9107, VR::SQ, VM::M1, "MR Spatial Saturation Sequence" },
{ 0x0018, 0x9517, VR::DT, VM::M1, "End Acquisition DateTime" },
{ 0x0040, 0x0316, VR::DS, VM::M1, "Organ Dose" },
{ 0x0054, 0x0302, VR::SQ, VM::M1, "Administration Route Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0860[] = {
{ 0x0018, 0x9100, VR::CS, VM::M1T2, "Resonant Nucleus" },
{ 0x0018, 0x9510, VR::FL, VM::M1, "Primary Positioner Scan Start Angle" },
{ 0x0028, 0x9520, VR::DS, VM::M16, "Image to Equipment Mapping Matrix" },
{ 0x300A, 0x0398, VR::FL, VM::M2, "Scanning Spot Size" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0861[] = {
{ 0x0018, 0x9101, VR::CS, VM::M1, "Frequency Correction" },
{ 0x0018, 0x9511, VR::FL, VM::M1, "Secondary Positioner Scan Start Angle" },
{ 0x0020, 0x9529, VR::SQ, VM::M1, "Contributing SOP Instances Reference Sequence" },
{ 0x0040, 0x0310, VR::ST, VM::M1, "Comments on Radiation Dose" },
{ 0x0054, 0x0304, VR::SQ, VM::M1, "Radiopharmaceutical Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0862[] = {
{ 0x0022, 0x1330, VR::SQ, VM::M1, "Referenced Ophthalmic Axial Length Measurement QC Image Sequence" },
{ 0x0028, 0x9132, VR::SQ, VM::M1, "Frame VOI LUT Sequence" },
{ 0x300A, 0x039A, VR::IS, VM::M1, "Number of Paintings" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0863[] = {
{ 0x0018, 0x9103, VR::SQ, VM::M1, "MR Spectroscopy FOV/Geometry Sequence" },
{ 0x0040, 0x0312, VR::DS, VM::M1, "X-Ray Output" },
{ 0x0054, 0x0306, VR::SQ, VM::M1, "Calibration Data Sequence" },
{ 0x0072, 0x0320, VR::US, VM::M1, "Image Box Overlap Priority" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0864[] = {
{ 0x300A, 0x03A4, VR::SQ, VM::M1, "Ion Beam Limiting Device Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0865[] = {
{ 0x0070, 0x031C, VR::SQ, VM::M1, "Fiducial Set Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0866[] = {
{ 0x300A, 0x03A6, VR::SQ, VM::M1, "Ion Block Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0867[] = {
{ 0x0068, 0x6280, VR::ST, VM::M1, "Information Summary" },
{ 0x0070, 0x031E, VR::SQ, VM::M1, "Fiducial Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0868[] = {
{ 0x0018, 0x1720, VR::IS, VM::M2T2N, "Vertices of the Polygonal Collimator" },
{ 0x0018, 0x9528, VR::LO, VM::M1, "Algorithm Description" },
{ 0x0028, 0x1300, VR::CS, VM::M1, "Breast Implant Present" },
{ 0x0028, 0x9108, VR::CS, VM::M1, "Data Representation" },
{ 0x300A, 0x03A0, VR::SQ, VM::M1, "Ion Tolerance Table Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0869[] = {
{ 0x0070, 0x0318, VR::SQ, VM::M1, "Graphic Coordinates Data Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0870[] = {
{ 0x300A, 0x03A2, VR::SQ, VM::M1, "Ion Beam Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0871[] = {
{ 0x0040, 0x073A, VR::DS, VM::M1, "Y Offset in Slide Coordinate System" },
{ 0x0070, 0x031A, VR::UI, VM::M1, "Fiducial UID" },
{ 0x0072, 0x0318, VR::US, VM::M1, "Image Box Large Scroll Amount" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0872[] = {
{ 0x0008, 0x9124, VR::SQ, VM::M1, "Derivation Image Sequence" },
{ 0x0018, 0x9524, VR::LO, VM::M1, "Application Name" },
{ 0x0024, 0x0341, VR::FL, VM::M1, "Index Probability" },
{ 0x300A, 0x03AC, VR::SQ, VM::M1, "Ion Wedge Position Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0873[] = {
{ 0x0018, 0x9525, VR::LO, VM::M1, "Application Version" },
{ 0x0040, 0x0324, VR::SQ, VM::M1, "Billing Supplies and Devices Sequence" },
{ 0x0070, 0x0314, VR::SQ, VM::M1, "Used Fiducials Sequence" },
{ 0x0072, 0x0316, VR::CS, VM::M1, "Image Box Large Scroll Type" },
{ 0x0072, 0x0706, VR::CS, VM::M1, "Show Grayscale Inverted" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0874[] = {
{ 0x0018, 0x9526, VR::LO, VM::M1, "Application Manufacturer" },
{ 0x0072, 0x0705, VR::SQ, VM::M1, "Pseudo-Color Palette Instance Reference Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0875[] = {
{ 0x0018, 0x9527, VR::CS, VM::M1, "Algorithm Type" },
{ 0x0072, 0x0314, VR::US, VM::M1, "Image Box Small Scroll Amount" },
{ 0x0072, 0x0704, VR::CS, VM::M1, "Pseudo-Color Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0876[] = {
{ 0x0020, 0x9518, VR::US, VM::M1TN, "Acquisition Index" },
{ 0x0040, 0x0321, VR::SQ, VM::M1, "Film Consumption Sequence" },
{ 0x0070, 0x0311, VR::SQ, VM::M1, "Fiducial Identifier Code Sequence" },
{ 0x300A, 0x03A8, VR::SQ, VM::M1, "Ion Control Point Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0877[] = {
{ 0x0008, 0x9121, VR::SQ, VM::M1, "Referenced Raw Data Sequence" },
{ 0x0024, 0x0344, VR::SQ, VM::M1, "Index Probability Sequence" },
{ 0x0040, 0x0320, VR::SQ, VM::M1, "Billing Procedure Step Sequence" },
{ 0x0070, 0x0310, VR::SH, VM::M1, "Fiducial Identifier" },
{ 0x0072, 0x0312, VR::CS, VM::M1, "Image Box Small Scroll Type" },
{ 0x0072, 0x0702, VR::CS, VM::M1, "VOI Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0878[] = {
{ 0x0022, 0x1300, VR::SQ, VM::M1, "Intraocular Lens Calculations Right Eye Sequence" },
{ 0x300A, 0x03AA, VR::SQ, VM::M1, "Ion Wedge Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0879[] = {
{ 0x0008, 0x9123, VR::UI, VM::M1, "Creator-Version UID" },
{ 0x0070, 0x0312, VR::FD, VM::M1, "Contour Uncertainty Radius" },
{ 0x0072, 0x0310, VR::CS, VM::M1, "Image Box Scroll Direction" },
{ 0x0072, 0x0700, VR::CS, VM::M2, "Display Set Patient Orientation" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0880[] = {
{ 0x0070, 0x030D, VR::SQ, VM::M1, "Registration Type Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0881[] = {
{ 0x0070, 0x030C, VR::CS, VM::M1, "Frame of Reference Transformation Matrix Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0882[] = {
{ 0x0020, 0x9116, VR::SQ, VM::M1, "Plane Orientation Sequence" },
{ 0x0070, 0x030F, VR::ST, VM::M1, "Fiducial Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0883[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0884[] = {
{ 0x0018, 0x9538, VR::SQ, VM::M1, "Per Projection Acquisition Sequence" },
{ 0x0070, 0x0309, VR::SQ, VM::M1, "Matrix Registration Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0885[] = {
{ 0x0020, 0x9111, VR::SQ, VM::M1, "Frame Content Sequence" },
{ 0x0028, 0x0740, VR::US, VM::M1, "Code Number Format" },
{ 0x0040, 0xA992, VR::ST, VM::M1, "Uniform Resource Locator (Trial)" },
{ 0x0070, 0x0308, VR::SQ, VM::M1, "Registration Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0886[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0887[] = {
{ 0x0020, 0x9113, VR::SQ, VM::M1, "Plane Position Sequence" },
{ 0x0040, 0x072A, VR::DS, VM::M1, "X Offset in Slide Coordinate System" },
{ 0x0070, 0x030A, VR::SQ, VM::M1, "Matrix Sequence" },
{ 0x0072, 0x0308, VR::US, VM::M1, "Image Box Tile Vertical Dimension" },
{ 0x0072, 0x0718, VR::CS, VM::M1, "Display Set Vertical Justification" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0888[] = {
{ 0x0072, 0x0717, VR::CS, VM::M1, "Display Set Horizontal Justification" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0889[] = {
{ 0x0018, 0x9125, VR::SQ, VM::M1, "MR FOV/Geometry Sequence" },
{ 0x0028, 0x9505, VR::SQ, VM::M1, "Multi-frame Presentation Sequence" },
{ 0x0072, 0x0306, VR::US, VM::M1, "Image Box Tile Horizontal Dimension" },
{ 0x0072, 0x0716, VR::CS, VM::M1, "Show Acquisition Techniques Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0890[] = {
{ 0x0018, 0x9126, VR::SQ, VM::M1, "Volume Localization Sequence" },
{ 0x0028, 0x9506, VR::US, VM::M2T2N, "Pixel Shift Frame Range" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0891[] = {
{ 0x0018, 0x9127, VR::UL, VM::M1, "Spectroscopy Acquisition Data Columns" },
{ 0x0028, 0x9507, VR::US, VM::M2T2N, "LUT Frame Range" },
{ 0x0070, 0x0306, VR::CS, VM::M1, "Shape Type" },
{ 0x0072, 0x0304, VR::CS, VM::M1, "Image Box Layout Type" },
{ 0x0072, 0x0714, VR::CS, VM::M1, "Show Patient Demographics Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0892[] = {
{ 0x0018, 0x9530, VR::SQ, VM::M1, "X-Ray 3D Reconstruction Sequence" },
{ 0x0028, 0x9110, VR::SQ, VM::M1, "Pixel Measures Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0893[] = {
{ 0x0018, 0x9531, VR::LO, VM::M1, "Reconstruction Description" },
{ 0x0028, 0x9501, VR::SQ, VM::M1, "Pixel Shift Sequence" },
{ 0x0040, 0x0330, VR::SQ, VM::M1, "Referenced Procedure Step Sequence" },
{ 0x0072, 0x0302, VR::US, VM::M1, "Image Box Number" },
{ 0x0072, 0x0712, VR::CS, VM::M1, "Show Graphic Annotation Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0894[] = {
{ 0x0022, 0x1310, VR::SQ, VM::M1, "Intraocular Lens Calculations Left Eye Sequence" },
{ 0x0028, 0x9502, VR::SQ, VM::M1, "Region Pixel Shift Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0895[] = {
{ 0x0028, 0x9503, VR::SS, VM::M2T2N, "Vertices of the Region" },
{ 0x0072, 0x0300, VR::SQ, VM::M1, "Image Boxes Sequence" },
{ 0x0072, 0x0710, VR::CS, VM::M1, "Show Image True Size Flag" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0896[] = {
{ 0x0068, 0x6260, VR::SQ, VM::M1, "Information From Manufacturer Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0897[] = {
{ 0x300A, 0x0346, VR::SH, VM::M1, "Range Modulator ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0898[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0899[] = {
{ 0x300A, 0x0344, VR::IS, VM::M1, "Range Modulator Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0900[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0901[] = {
{ 0x0068, 0x6265, VR::SQ, VM::M1, "Notification From Manufacturer Sequence" },
{ 0x300A, 0x0342, VR::SQ, VM::M1, "Range Modulator Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0902[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0903[] = {
{ 0x300A, 0x0340, VR::IS, VM::M1, "Number of Range Modulators" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0904[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0905[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0906[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0907[] = {
{ 0x300A, 0x034C, VR::SH, VM::M1, "Beam Current Modulation ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0908[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0909[] = {
{ 0x300A, 0x034A, VR::LO, VM::M1, "Range Modulator Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0910[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0911[] = {
{ 0x300A, 0x0348, VR::CS, VM::M1, "Range Modulator Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0912[] = {
{ 0x0068, 0x6270, VR::DT, VM::M1, "Information Issue DateTime" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0913[] = {
{ 0x300A, 0x0356, VR::FL, VM::M1, "Fixation Light Azimuthal Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0914[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0915[] = {
{ 0x300A, 0x0354, VR::LO, VM::M1, "Patient Support Accessory Code" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0916[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0917[] = {
{ 0x300A, 0x0352, VR::SH, VM::M1, "Patient Support ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0918[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0919[] = {
{ 0x300A, 0x0350, VR::CS, VM::M1, "Patient Support Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0920[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0921[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0922[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0923[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0924[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0925[] = {
{ 0x300A, 0x035A, VR::FL, VM::M1, "Meterset Rate" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0926[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0927[] = {
{ 0x300A, 0x0358, VR::FL, VM::M1, "Fixation Light Polar Angle" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0928[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0929[] = {
{ 0x300A, 0x0366, VR::FL, VM::M1, "Range Shifter Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0930[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0931[] = {
{ 0x0040, 0xA167, VR::SQ, VM::M1, "Observation Category Code Sequence (Trial)" },
{ 0x300A, 0x0364, VR::FL, VM::M1, "Isocenter to Range Shifter Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0932[] = {
{ 0x0040, 0xA160, VR::UT, VM::M1, "Text Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0933[] = {
{ 0x300A, 0x0362, VR::LO, VM::M1, "Range Shifter Setting" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0934[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0935[] = {
{ 0x300A, 0x0360, VR::SQ, VM::M1, "Range Shifter Settings Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0936[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0937[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0938[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0939[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0940[] = {
{ 0x0040, 0xA168, VR::SQ, VM::M1, "Concept Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0941[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0942[] = {
{ 0x0040, 0xA16A, VR::ST, VM::M1, "Bibliographic Citation (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0943[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0944[] = {
{ 0x0040, 0xA174, VR::CS, VM::M1, "Referenced Object Observation Class (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0945[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0946[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0947[] = {
{ 0x300A, 0x0374, VR::FL, VM::M1, "Isocenter to Lateral Spreading Device Distance" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0948[] = {
{ 0x0040, 0xA170, VR::SQ, VM::M1, "Purpose of Reference Code Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0949[] = {
{ 0x0040, 0xA171, VR::UI, VM::M1, "Observation UID (Trial)" },
{ 0x300A, 0x0372, VR::LO, VM::M1, "Lateral Spreading Device Setting" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0950[] = {
{ 0x0040, 0xA172, VR::UI, VM::M1, "Referenced Observation UID (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0951[] = {
{ 0x0040, 0xA173, VR::CS, VM::M1, "Referenced Observation Class (Trial)" },
{ 0x300A, 0x0370, VR::SQ, VM::M1, "Lateral Spreading Device Settings Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0952[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0953[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0954[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0955[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0956[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0957[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0958[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0959[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0960[] = {
{ 0x0040, 0xE001, VR::ST, VM::M1, "HL7 Instance Identifier" },
{ 0x0068, 0x6221, VR::LO, VM::M1, "Implant Template Version" },
{ 0x300A, 0x0306, VR::SS, VM::M1, "Radiation Charge State" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0961[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0962[] = {
{ 0x0068, 0x6223, VR::CS, VM::M1, "Implant Type" },
{ 0x300A, 0x0304, VR::IS, VM::M1, "Radiation Atomic Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0963[] = {
{ 0x0068, 0x6222, VR::SQ, VM::M1, "Replaced Implant Template Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0964[] = {
{ 0x0068, 0x6225, VR::SQ, VM::M1, "Original Implant Template Sequence" },
{ 0x300A, 0x0302, VR::IS, VM::M1, "Radiation Mass Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0965[] = {
{ 0x0040, 0xE004, VR::DT, VM::M1, "HL7 Document Effective Time" },
{ 0x0068, 0x6224, VR::SQ, VM::M1, "Derivation Implant Template Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0966[] = {
{ 0x0018, 0x9198, VR::CS, VM::M1, "First Order Phase Correction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0967[] = {
{ 0x0018, 0x9199, VR::CS, VM::M1, "Water Referenced Phase Correction" },
{ 0x0040, 0xE006, VR::SQ, VM::M1, "HL7 Document Type Code Sequence" },
{ 0x0068, 0x6226, VR::DT, VM::M1, "Effective DateTime" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0968[] = {
{ 0x0018, 0x9196, VR::FD, VM::M1, "Chemical Shift Maximum Integration Limit in Hz" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0969[] = {
{ 0x0018, 0x9197, VR::SQ, VM::M1, "MR Velocity Encoding Sequence" },
{ 0x0040, 0xE008, VR::SQ, VM::M1, "Document Class Code Sequence" },
{ 0x300A, 0x030F, VR::SH, VM::M1, "Snout ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0970[] = {
{ 0x300A, 0x030C, VR::SQ, VM::M1, "Snout Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0971[] = {
{ 0x0018, 0x9195, VR::FD, VM::M1, "Chemical Shift Minimum Integration Limit in Hz" },
{ 0x300A, 0x030D, VR::FL, VM::M1, "Snout Position" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0972[] = {
{ 0x300A, 0x030A, VR::FL, VM::M2, "Virtual Source-Axis Distances" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0973[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0974[] = {
{ 0x300A, 0x0308, VR::CS, VM::M1, "Scan Mode" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0975[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0976[] = {
{ 0x0040, 0xE011, VR::UI, VM::M1, "Retrieve Location UID" },
{ 0x300A, 0x0316, VR::IS, VM::M1, "Range Shifter Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0977[] = {
{ 0x0040, 0xA504, VR::SQ, VM::M1, "Content Template Sequence" },
{ 0x0040, 0xE010, VR::UT, VM::M1, "Retrieve URI" },
{ 0x0068, 0x6230, VR::SQ, VM::M1, "Implant Target Anatomy Sequence" },
{ 0x0068, 0x6620, VR::FD, VM::M3, "3D Plane Normal" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0978[] = {
{ 0x300A, 0x0314, VR::SQ, VM::M1, "Range Shifter Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0979[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0980[] = {
{ 0x300A, 0x0312, VR::IS, VM::M1, "Number of Range Shifters" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0981[] = {
{ 0x0040, 0xA110, VR::DA, VM::M1, "Date of Document or Verbal Transaction (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0982[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0983[] = {
{ 0x0040, 0xA112, VR::TM, VM::M1, "Time of Document Creation or Verbal Transaction (Trial)" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0984[] = {
{ 0x0018, 0x9186, VR::SH, VM::M1, "Respiratory Signal Source ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0985[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0986[] = {
{ 0x0018, 0x9184, VR::FD, VM::M1, "Tagging Delay" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0987[] = {
{ 0x0018, 0x9185, VR::ST, VM::M1, "Respiratory Motion Compensation Technique Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0988[] = {
{ 0x0018, 0x9182, VR::FD, VM::M1, "Gradient Output" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0989[] = {
{ 0x0018, 0x9183, VR::CS, VM::M1, "Flow Compensation Direction" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0990[] = {
{ 0x0018, 0x9180, VR::CS, VM::M1, "Gradient Output Type" },
{ 0x300A, 0x0318, VR::SH, VM::M1, "Range Shifter ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0991[] = {
{ 0x0018, 0x9181, VR::FD, VM::M1, "Specific Absorption Rate Value" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0992[] = {
{ 0x0040, 0xA125, VR::CS, VM::M2, "Report Status ID (Trial)" },
{ 0x0040, 0xE021, VR::SQ, VM::M1, "DICOM Retrieval Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0993[] = {
{ 0x0040, 0xA124, VR::UI, VM::M1, "UID" },
{ 0x0040, 0xE020, VR::CS, VM::M1, "Type of Instances" },
{ 0x0068, 0x6610, VR::FD, VM::M3, "3D Plane Origin" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0994[] = {
{ 0x0040, 0xE023, VR::SQ, VM::M1, "WADO Retrieval Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0995[] = {
{ 0x0040, 0xE022, VR::SQ, VM::M1, "DICOM Media Retrieval Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0996[] = {
{ 0x0040, 0xA121, VR::DA, VM::M1, "Date" },
{ 0x300A, 0x0322, VR::LO, VM::M1, "Range Shifter Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0997[] = {
{ 0x0040, 0xA120, VR::DT, VM::M1, "DateTime" },
{ 0x0040, 0xE024, VR::SQ, VM::M1, "XDS Retrieval Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0998[] = {
{ 0x0040, 0xA123, VR::PN, VM::M1, "Person Name" },
{ 0x300A, 0x0320, VR::CS, VM::M1, "Range Shifter Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow0999[] = {
{ 0x0040, 0xA122, VR::TM, VM::M1, "Time" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1000[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1001[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1002[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1003[] = {
{ 0x2010, 0x0376, VR::DS, VM::M2, "Printer Pixel Spacing" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1004[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1005[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1006[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1007[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1008[] = {
{ 0x0040, 0xA525, VR::SQ, VM::M1, "Identical Documents Sequence" },
{ 0x0040, 0xE031, VR::UI, VM::M1, "Home Community ID" },
{ 0x300A, 0x0336, VR::SH, VM::M1, "Lateral Spreading Device ID" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1009[] = {
{ 0x0040, 0xE030, VR::UI, VM::M1, "Repository Unique ID" },
{ 0x0068, 0x6210, VR::LO, VM::M1, "Implant Size" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1010[] = {
{ 0x300A, 0x0334, VR::IS, VM::M1, "Lateral Spreading Device Number" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1011[] = {
{ 0x0040, 0xA136, VR::US, VM::M1TN, "Referenced Frame Numbers" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1012[] = {
{ 0x300A, 0x0332, VR::SQ, VM::M1, "Lateral Spreading Device Sequence" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1013[] = {
{ 0x0040, 0xA130, VR::CS, VM::M1, "Temporal Range Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1014[] = {
{ 0x300A, 0x0330, VR::IS, VM::M1, "Number of Lateral Spreading Devices" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1015[] = {
{ 0x0040, 0xA132, VR::UL, VM::M1TN, "Referenced Sample Positions" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1016[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1017[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1018[] = {
{ 0x300A, 0x033C, VR::FL, VM::M1, "Lateral Spreading Device Water Equivalent Thickness" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1019[] = {
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1020[] = {
{ 0x300A, 0x033A, VR::LO, VM::M1, "Lateral Spreading Device Description" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1021[] = {
{ 0x0040, 0xA138, VR::DS, VM::M1TN, "Referenced Time Offsets" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1022[] = {
{ 0x300A, 0x0338, VR::CS, VM::M1, "Lateral Spreading Device Type" },
{ 0, 0, 0, 0, 0 }
};
vtkDICOMMetaData::DictEntry DictRow1023[] = {
{ 0x0040, 0xA13A, VR::DT, VM::M1TN, "Referenced DateTime" },
{ 0, 0, 0, 0, 0 }
};

}

vtkDICOMMetaData::DictEntry *vtkDICOMMetaData::DictHashTable[1024] = {
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

