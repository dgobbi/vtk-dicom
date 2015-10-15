/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkScancoCTReader - Read SCANCO ISQ and AIM medical image files
// .SECTION Description
// This class reads ISQ and AIM files, which are used for high-resolution
// computed tomography.  The information that it provides uses different
// units as compared to the original files: all distances are given in
// millimeters (instead of micrometers), times are given in milliseconds
// (instead of microseconds), voltage and current given in kV and mA
// (instead of volts and microamps).  If the scanner was calibrated, then
// the data values can be converted to calibrated units.  To convert
// to linear attenuation coefficients [cm^-1], simply divide the data
// values by the MuScaling.  To convert to density values, multiply
// the data values by the RescaleSlope and add the RescaleIntercept.
// To convert to Hounsfield units, multiply by 1000/(MuScaling*MuWater)
// and subtract 1000.
// .SECTION Thanks
// Created at the Calgary Image Processing and Analysis Centre (CIPAC).

#ifndef vtkScancoCTReader_h
#define vtkScancoCTReader_h

#include <vtkImageReader2.h>
#include "vtkDICOMModule.h"

//----------------------------------------------------------------------------
class VTKDICOM_EXPORT vtkScancoCTReader : public vtkImageReader2
{
public:
  // Description:
  // Static method for construction.
  static vtkScancoCTReader *New();
  vtkTypeMacro(vtkScancoCTReader, vtkImageReader2);

  // Description:
  // Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Valid extensions for this file type.
  virtual const char* GetFileExtensions() {
    return ".isq .rsq .rad .aim" ; }

  // Description:
  // Return a descriptive name that might be useful in a GUI.
  virtual const char* GetDescriptiveName() {
    return "SCANCO MicroCT"; }

  // Description:
  // Return true if this reader can read the given file.
  int CanReadFile(const char* filename);

  // Description:
  // Get a string that states the version of the file header.
  const char *GetVersion() { return this->Version; }

  // Description:
  // Get the patient index from the header.
  int GetPatientIndex() { return this->PatientIndex; }

  // Description:
  // Get the scanner ID from the header.
  int GetScannerID() { return this->ScannerID; }

  // Description:
  // Get the creation date as a string.
  const char *GetCreationDate() { return this->CreationDate; }

  // Description:
  // Get the date when the data was last modified.
  const char *GetModificationDate() { return this->ModificationDate; }

  // Description:
  // Get the slice thickness in millimeters.
  double GetSliceThickness() { return this->SliceThickness; }

  // Description:
  // Get the slice increment in millimeters.
  double GetSliceIncrement() { return this->SliceIncrement; }

  // Description:
  // Get the position of the first slice in millimeters.
  double GetStartPosition() { return this->StartPosition; }

  // Description:
  // Get the position of the final slice in millimeters.
  double GetEndPosition() { return this->EndPosition; }

  // Description:
  // Get the location of the edge of a locator scan.
  double GetZPosition() { return this->ZPosition; }

  // Description:
  // Get the data range, as stored in the file header.
  vtkGetVector2Macro(DataRange, double);

  // Description:
  // Get the scaling factor from linear attenuation [1/cm] to data values.
  double GetMuScaling() { return this->MuScaling; }

  // Description:
  // Get the number of samples.
  int GetNumberOfSamples() { return this->NumberOfSamples; }

  // Description:
  // Get the nubmer of projections.
  int GetNumberOfProjections() { return this->NumberOfProjections; }

  // Description:
  // Get the scan distance (in millimeters).
  double GetScanDistance() { return this->ScanDistance; }

  // Description:
  // Get the scanner type, as an integer code.
  int GetScannerType() { return this->ScannerType; }

  // Description:
  // Get the sample time (in milliseconds).
  double GetSampleTime() { return this->SampleTime; }

  // Description:
  // Get the index measurement.
  int GetMeasurementIndex() { return this->MeasurementIndex; }

  // Description:
  // Get an integer value that identifies the site on the body.
  int GetSite() { return this->Site; }

  // Description:
  // Get the reference line (in millimeters).
  double GetReferenceLine() { return this->ReferenceLine; }

  // Description:
  // Get an integer value that identifies the reconstruction algorithm.
  int GetReconstructionAlg() { return this->ReconstructionAlg; }

  // Description:
  // Get a descriptive name for this scan.
  const char *GetPatientName() { return this->PatientName; }

  // Description:
  // Get the X-ray energy (in kVp).
  double GetEnergy() { return this->Energy; }

  // Description:
  // Get the X-ray intensity (in mA).
  double GetIntensity() { return this->Intensity; }

  // Description:
  // Get the slope and intercept for rescaling the scalar values.
  // These values allow calibration of the data to real values.
  // Use the equation v = u*RescaleSlope + RescaleIntercept.
  double GetRescaleSlope() { return this->RescaleSlope; }
  double GetRescaleIntercept() { return this->RescaleIntercept; }

  // Description:
  // Get the rescale type as an integer code.
  int GetRescaleType() { return this->RescaleType; }

  // Description:
  // Get the units of the data after rescaling with slope and intercept.
  const char *GetRescaleUnits() { return this->RescaleUnits; }

  // Description:
  // Get the linear attenuation of water, in units of [1/cm].
  double GetMuWater() { return this->MuWater; }

  // Description:
  // Get the calibration data (energy, filtration, etc.)
  const char *GetCalibrationData() { return this->CalibrationData; }

  // Description:
  // Get the full scan dimensions in pixels.
  vtkGetVector3Macro(ScanDimensionsPixels, int);

  // Description:
  // Get the full scan dimensions in millimeters.
  vtkGetVector3Macro(ScanDimensionsPhysical, double);

  // Description:
  // Get the raw header information (512 bytes) from the file.
  void *GetRawHeader() { return this->RawHeader; }

protected:
  vtkScancoCTReader();
  ~vtkScancoCTReader();

  // Description:
  // Read the header information.
  virtual int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  // Description:
  // Read the voxel data.
  virtual int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  // Description:
  // Initialize the header information
  void InitializeHeader();

  // Description:
  // Read an ISQ header.
  int ReadISQHeader(ifstream *file, unsigned long bytesRead);

  // Description:
  // Read AIM header.
  int ReadAIMHeader(ifstream *file, unsigned long bytesRead);

  // Description:
  // Check the file header to see what type of file it is.
  // Return values are: 0 if unrecognized, 1 if ISQ/RAD,
  // 2 if AIM 020, 3 if AIM 030.
  static int CheckVersion(const char header[16]);

  // Description:
  // Convert a VMS timestamp to a calendar date.
  void DecodeDate(const void *data,
    int& year, int& month, int& day,
    int& hour, int& minute, int& second, int& millis);

  // Description:
  // Convert char data to 32-bit int (little-endian).
  static int DecodeInt(const void *data);

  // Description:
  // Convert char data to float (single precision).
  static float DecodeFloat(const void *data);

  // Description:
  // Convert char data to float (double precision).
  static double DecodeDouble(const void *data);

  // Description:
  // Strip a string by removing trailing whitespace.
  // The dest must have a size of at least l+1.
  static void StripString(char *dest, const char *source, size_t l);

  // Header information
  char Version[18];
  char PatientName[42];
  int PatientIndex;
  int ScannerID;
  char CreationDate[32];
  char ModificationDate[32];
  int ScanDimensionsPixels[3];
  double ScanDimensionsPhysical[3];
  double SliceThickness;
  double SliceIncrement;
  double StartPosition;
  double EndPosition;
  double ZPosition;
  double DataRange[2];
  double MuScaling;
  int NumberOfSamples;
  int NumberOfProjections;
  double ScanDistance;
  double SampleTime;
  int ScannerType;
  int MeasurementIndex;
  int Site;
  int ReconstructionAlg;
  double ReferenceLine;
  double Energy;
  double Intensity;
  int RescaleType;
  char RescaleUnits[18];
  char CalibrationData[66];
  double RescaleSlope;
  double RescaleIntercept;
  double MuWater;
  char *RawHeader;

  // The compression mode, if any.
  int Compression;

private:
  vtkScancoCTReader(const vtkScancoCTReader&);  // Not implemented.
  void operator=(const vtkScancoCTReader&);  // Not implemented.
};

#endif // vtkScancoCTReader_h
