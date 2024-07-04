/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2024 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMConfig.h"
#include "vtkScancoCTReader.h"
#include "vtkSmartPointer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// from dicomcli
#include "vtkConsoleOutputWindow.h"
#include "mainmacro.h"

// print the version
void printVersion(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2022, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n"
    "\n");
}

// print the help
void printUsage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s file\n", cp);
  fprintf(file, "options:\n"
    "  --help      Print a brief help message.\n"
    "  --version   Print the software version.\n\n");
}

// print the help
void printHelp(FILE *file, const char *cp)
{
  printUsage(file, cp);
  fprintf(file, "Dump the header from a .isq, .rad, or .aim file.\n\n");
}

// remove path portion of filename
const char *fileBasename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// This program will convert
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

  int rval = 0;

  if (argc < 2)
  {
    printUsage(stdout, fileBasename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
  {
    printHelp(stdout, fileBasename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--version") == 0)
  {
    printVersion(stdout, fileBasename(argv[0]));
    return rval;
  }

  vtkSmartPointer<vtkScancoCTReader> reader =
    vtkSmartPointer<vtkScancoCTReader>::New();
  reader->SetFileName(argv[1]);
  reader->UpdateInformation();

  double origin[3], spacing[3], dvec[3];
  int extent[6], ivec[3];

  reader->GetDataOrigin(origin);
  reader->GetDataSpacing(spacing);
  reader->GetDataExtent(extent);

  printf("Version: %s\n", reader->GetVersion());
  printf("CreationDate: %s\n", reader->GetCreationDate());
  if (strncmp(reader->GetVersion(), "AIMDATA", 7) == 0)
  {
    printf("ModificationDate: %s\n", reader->GetModificationDate());
    printf("Position: %d %d %d\n",
           static_cast<int>(origin[0]/spacing[0] + 0.5),
           static_cast<int>(origin[1]/spacing[1] + 0.5),
           static_cast<int>(origin[2]/spacing[2] + 0.5));
    printf("Dimensions: %d %d %d\n",
           (extent[1] - extent[0] + 1),
           (extent[3] - extent[2] + 1),
           (extent[5] - extent[4] + 1));
    printf("ElementSize: %g %g %g [mm]\n",
           spacing[0], spacing[1], spacing[2]);
    printf("DataType: %s\n",
           (reader->GetDataScalarType() == VTK_SHORT ? "short" : "byte"));
  }
  reader->GetScanDimensionsPixels(ivec);
  printf("ScanDimensionsPixels: %d %d %d\n",
         ivec[0], ivec[1], ivec[2]);
  reader->GetScanDimensionsPhysical(dvec);
  printf("ScanDimensionsPhysical: %g %g %g [mm]\n",
         dvec[0], dvec[1], dvec[2]);
  printf("PatientName: %s\n", reader->GetPatientName());
  printf("PatientIndex: %d\n", reader->GetPatientIndex());
  printf("MeasurementIndex: %d\n", reader->GetMeasurementIndex());
  printf("Site: %d\n", reader->GetSite());
  printf("ScannerID: %d\n", reader->GetScannerID());
  printf("ScannerType: %d\n", reader->GetScannerType());
  printf("PositionSlice1: %g [mm]\n", reader->GetStartPosition());
  printf("ReferenceLine: %g [mm]\n", reader->GetReferenceLine());
  printf("NumberOfSamples: %d\n", reader->GetNumberOfSamples());
  printf("NumberOfProjections: %d\n", reader->GetNumberOfProjections());
  printf("ScanDistance: %g [mm]\n", reader->GetScanDistance());
  printf("SampleTime: %g [ms]\n", reader->GetSampleTime());
  printf("SliceThickness: %g [mm]\n", reader->GetSliceThickness());
  printf("SliceIncrement: %g [mm]\n", reader->GetSliceIncrement());
  printf("ReconstructionAlg: %d\n", reader->GetReconstructionAlg());
  printf("Energy: %g [kV]\n", reader->GetEnergy());
  printf("Intensity: %g [mA]\n", reader->GetIntensity());
  printf("MuScaling: %g [cm]\n", reader->GetMuScaling());
  reader->GetDataRange(dvec);
  printf("DataRange: %g %g\n", dvec[0], dvec[1]);
  printf("CalibrationData: %s\n", reader->GetCalibrationData());
  printf("RescaleType: %d\n", reader->GetRescaleType());
  printf("RescaleUnits: %s\n", reader->GetRescaleUnits());
  printf("RescaleSlope: %g\n", reader->GetRescaleSlope());
  printf("RescaleIntercept: %g\n", reader->GetRescaleIntercept());
  printf("MuWater: %g [cm^-1]\n", reader->GetMuWater());
  printf("HeaderSize: %d\n", static_cast<int>(reader->GetHeaderSize()));
  fflush(stdout);

  return 0;
}
