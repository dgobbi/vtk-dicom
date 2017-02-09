/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2015-2016 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*! \class vtkScancoCTReader
 *  \brief Read SCANCO ISQ and AIM medical image files
 *
 *  This class reads ISQ and AIM files, which are used for high-resolution
 *  computed tomography.  The information that it provides uses different
 *  units as compared to the original files: all distances are given in
 *  millimeters (instead of micrometers), times are given in milliseconds
 *  (instead of microseconds), voltage and current given in kV and mA
 *  (instead of volts and microamps).  If the scanner was calibrated, then
 *  the data values can be converted to calibrated units.  To convert
 *  to linear attenuation coefficients [cm^-1], simply divide the data
 *  values by the MuScaling.  To convert to density values, multiply
 *  the data values by the RescaleSlope and add the RescaleIntercept.
 *  To convert to Hounsfield units, multiply by 1000/(MuScaling*MuWater)
 *  and subtract 1000.
 *
 *  Created at the Calgary Image Processing and Analysis Centre (CIPAC).
 */

#ifndef vtkScancoCTReader_h
#define vtkScancoCTReader_h

#include <vtkImageReader2.h>
#include "vtkDICOMModule.h" // For export macro

//----------------------------------------------------------------------------
class VTKDICOM_EXPORT vtkScancoCTReader : public vtkImageReader2
{
public:
  //! Static method for construction.
  static vtkScancoCTReader *New();
  vtkTypeMacro(vtkScancoCTReader, vtkImageReader2);

  //! Print information about this object.
  virtual void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

  //@{
  //! Valid extensions for this file type.
  virtual const char* GetFileExtensions() VTK_OVERRIDE {
    return ".isq .rsq .rad .aim" ; }

  //! Return a descriptive name that might be useful in a GUI.
  virtual const char* GetDescriptiveName() VTK_OVERRIDE {
    return "SCANCO MicroCT"; }
  //@}

  //@{
  //! Return true if this reader can read the given file.
  int CanReadFile(const char* filename) VTK_OVERRIDE;
  //@}

  //@{
  //! Get a string that states the version of the file header.
  const char *GetVersion() { return this->Version; }

  //! Get the patient index from the header.
  int GetPatientIndex() { return this->PatientIndex; }

  //! Get the scanner ID from the header.
  int GetScannerID() { return this->ScannerID; }

  //! Get the creation date as a string.
  const char *GetCreationDate() { return this->CreationDate; }

  //! Get the date when the data was last modified.
  const char *GetModificationDate() { return this->ModificationDate; }

  //! Get the slice thickness in millimeters.
  double GetSliceThickness() { return this->SliceThickness; }

  //! Get the slice increment in millimeters.
  double GetSliceIncrement() { return this->SliceIncrement; }

  //! Get the position of the first slice in millimeters.
  double GetStartPosition() { return this->StartPosition; }

  //! Get the position of the final slice in millimeters.
  double GetEndPosition() { return this->EndPosition; }

  //! Get the location of the edge of a locator scan.
  double GetZPosition() { return this->ZPosition; }

  //! Get the data range, as stored in the file header.
  vtkGetVector2Macro(DataRange, double);

  //! Get the scaling factor from linear attenuation [1/cm] to data values.
  double GetMuScaling() { return this->MuScaling; }

  //! Get the number of samples.
  int GetNumberOfSamples() { return this->NumberOfSamples; }

  //! Get the nubmer of projections.
  int GetNumberOfProjections() { return this->NumberOfProjections; }

  //! Get the scan distance (in millimeters).
  double GetScanDistance() { return this->ScanDistance; }

  //! Get the scanner type, as an integer code.
  int GetScannerType() { return this->ScannerType; }

  //! Get the sample time (in milliseconds).
  double GetSampleTime() { return this->SampleTime; }

  //! Get the index measurement.
  int GetMeasurementIndex() { return this->MeasurementIndex; }

  //! Get an integer value that identifies the site on the body.
  int GetSite() { return this->Site; }

  //! Get the reference line (in millimeters).
  double GetReferenceLine() { return this->ReferenceLine; }

  //! Get an integer value that identifies the reconstruction algorithm.
  int GetReconstructionAlg() { return this->ReconstructionAlg; }

  //! Get a descriptive name for this scan.
  const char *GetPatientName() { return this->PatientName; }

  //! Get the X-ray energy (in kVp).
  double GetEnergy() { return this->Energy; }

  //! Get the X-ray intensity (in mA).
  double GetIntensity() { return this->Intensity; }

  //! Get the slope and intercept for rescaling the scalar values.
  /*!
   *  These values allow calibration of the data to real values.
   *  Use the equation v = u*RescaleSlope + RescaleIntercept.
   */
  double GetRescaleSlope() { return this->RescaleSlope; }
  double GetRescaleIntercept() { return this->RescaleIntercept; }

  //! Get the rescale type as an integer code.
  int GetRescaleType() { return this->RescaleType; }

  //! Get the units of the data after rescaling with slope and intercept.
  const char *GetRescaleUnits() { return this->RescaleUnits; }

  //! Get the linear attenuation of water, in units of [1/cm].
  double GetMuWater() { return this->MuWater; }

  //! Get the calibration data (energy, filtration, etc.)
  const char *GetCalibrationData() { return this->CalibrationData; }

  //! Get the full scan dimensions in pixels.
  vtkGetVector3Macro(ScanDimensionsPixels, int);

  //! Get the full scan dimensions in millimeters.
  vtkGetVector3Macro(ScanDimensionsPhysical, double);

  //! Get the raw header information (512 bytes) from the file.
  void *GetRawHeader() { return this->RawHeader; }
  //@}

protected:
  vtkScancoCTReader();
  ~vtkScancoCTReader();

  //! Read the header information.
  virtual int RequestInformation(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  //! Read the voxel data.
  virtual int RequestData(
    vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) VTK_OVERRIDE;

  //! Initialize the header information
  void InitializeHeader();

  //! Read an ISQ header.
  int ReadISQHeader(ifstream *file, unsigned long bytesRead);

  //! Read AIM header.
  int ReadAIMHeader(ifstream *file, unsigned long bytesRead);

  //! Check the file header to see what type of file it is.
  /*!
   *  Return values are: 0 if unrecognized, 1 if ISQ/RAD,
   *  2 if AIM 020, 3 if AIM 030.
   */
  static int CheckVersion(const char header[16]);

  //! Convert a VMS timestamp to a calendar date.
  void DecodeDate(const void *data,
    int& year, int& month, int& day,
    int& hour, int& minute, int& second, int& millis);

  //! Convert char data to 32-bit int (little-endian).
  static int DecodeInt(const void *data);

  //! Convert char data to float (single precision).
  static float DecodeFloat(const void *data);

  //! Convert char data to float (double precision).
  static double DecodeDouble(const void *data);

  //! Strip a string by removing trailing whitespace.
  /*!
   *  The dest must have a size of at least l+1.
   */
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
  vtkScancoCTReader(const vtkScancoCTReader&) VTK_DELETE_FUNCTION;
  void operator=(const vtkScancoCTReader&) VTK_DELETE_FUNCTION;
};

#endif // vtkScancoCTReader_h
