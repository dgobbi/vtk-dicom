/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMConfig.h"
#include "vtkScancoCTReader.h"
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// from dicomcli
#include "mainmacro.h"

// print the version
void printVersion(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2015, David Gobbi.\n\n"
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
MAINMACRO(argc, argv)
{
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

  cout << "Version: " << reader->GetVersion() << "\n";
  cout << "CreationDate: " << reader->GetCreationDate() << "\n";
  if (strncmp(reader->GetVersion(), "AIMDATA", 7) == 0)
    {
    cout << "ModificationDate: " << reader->GetModificationDate() << "\n";
    cout << "Position: "
         << static_cast<int>(origin[0]/spacing[0] + 0.5) << " "
         << static_cast<int>(origin[1]/spacing[1] + 0.5) << " "
         << static_cast<int>(origin[2]/spacing[2] + 0.5) << "\n";
    cout << "Dimensions: "
         << (extent[1] - extent[0] + 1) << " "
         << (extent[3] - extent[2] + 1) << " "
         << (extent[5] - extent[4] + 1) << "\n";
    cout << "ElementSize: "
         << spacing[0] << " " << spacing[1] << " " << spacing[2] << " [mm]\n";
    cout << "DataType: "
         << (reader->GetDataScalarType() == VTK_SHORT ? "short\n" : "byte\n");
    }
  reader->GetScanDimensionsPixels(ivec);
  cout << "ScanDimensionsPixels: "
       << ivec[0] << " " << ivec[1] << " " << ivec[2] << "\n";
  reader->GetScanDimensionsPhysical(dvec);
  cout << "ScanDimensionsPhysical: "
       << dvec[0] << " " << dvec[1] << " " << dvec[2] << " [mm]\n";
  cout << "PatientName: " << reader->GetPatientName() << "\n";
  cout << "PatientIndex: " << reader->GetPatientIndex() << "\n";
  cout << "MeasurementIndex: " << reader->GetMeasurementIndex() << "\n";
  cout << "Site: " << reader->GetSite() << "\n";
  cout << "ScannerID: " << reader->GetScannerID() << "\n";
  cout << "ScannerType: " << reader->GetScannerType() << "\n";
  cout << "PositionSlice1: " << reader->GetStartPosition() << " [mm]\n";
  cout << "ReferenceLine: " << reader->GetReferenceLine() << " [mm]\n";
  cout << "NumberOfSamples: " << reader->GetNumberOfSamples() << "\n";
  cout << "NumberOfProjections: " << reader->GetNumberOfProjections() << "\n";
  cout << "ScanDistance: " << reader->GetScanDistance() << " [mm]\n";
  cout << "SampleTime: " << reader->GetSampleTime() << " [ms]\n";
  cout << "SliceThickness: " << reader->GetSliceThickness() << " [mm]\n";
  cout << "SliceIncrement: " << reader->GetSliceIncrement() << " [mm]\n";
  cout << "ReconstructionAlg: " << reader->GetReconstructionAlg() << "\n";
  cout << "Energy: " << reader->GetEnergy() << " [kV]\n";
  cout << "Intensity: " << reader->GetIntensity() << " [mA]\n";
  cout << "MuScaling: " << reader->GetMuScaling() << " [cm]\n";
  reader->GetDataRange(dvec);
  cout << "DataRange: " << dvec[0] << " " << dvec[1] << "\n";
  cout << "CalibrationData: " << reader->GetCalibrationData() << "\n";
  cout << "RescaleType: " << reader->GetRescaleType() << "\n";
  cout << "RescaleUnits: " << reader->GetRescaleUnits() << "\n";
  cout << "RescaleSlope: " << reader->GetRescaleSlope() << "\n";
  cout << "RescaleIntercept: " << reader->GetRescaleIntercept() << "\n";
  cout << "MuWater: " << reader->GetMuWater() << " [cm^-1]\n";
  cout << "HeaderSize: " << reader->GetHeaderSize() << "\n";

  return 0;
}
