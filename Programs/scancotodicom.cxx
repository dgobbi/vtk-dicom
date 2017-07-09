/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMConfig.h"
#include "vtkDICOMBuild.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMReader.h"
#include "vtkDICOMWriter.h"
#include "vtkDICOMCTGenerator.h"
#include "vtkDICOMUtilities.h"
#include "vtkDICOMFileDirectory.h"
#include "vtkScancoCTReader.h"

#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkErrorCode.h>
#include <vtkSmartPointer.h>

#include <string>
#include <vector>
#include <set>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

// from dicomcli
#include "vtkConsoleOutputWindow.h"
#include "mainmacro.h"

// The file types
enum {
  SCANCO_ISQ,    // standard CT scan
  SCANCO_RAD,    // CT localizer scan
  SCANCO_AIM,    // cropped CT scan
  SCANCO_AIM_SEG // any 8-bit data
};

// Simple structure for command-line options
struct scancotodicom_options
{
  bool no_reordering;
  const char *series_description;
  const char *series_number;
  const char *uid_prefix;
  bool silent;
  bool verbose;
  const char *output;
  const char *input;
};


// Print the version
void scancotodicom_version(FILE *file, const char *command_name, bool verbose)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  if (!verbose)
  {
    fprintf(file, "%s %s\n", cp, DICOM_VERSION);
    fprintf(file, "\n"
      "Copyright (c) 2012-2017, David Gobbi.\n\n"
      "This software is distributed under an open-source license.  See the\n"
      "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
  }
  else
  {
    fprintf(file,
      "Head %8.8s, Built %s, %s\n",
      DICOM_SOURCE_VERSION, DICOM_BUILD_DATE, DICOM_BUILD_TIME);
  }
}


// Print the options
void scancotodicom_usage(FILE *file, const char *command_name)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  fprintf(file,
    "usage:\n"
    "  %s -o directory file.isq [sample.dcm ...]\n\n", cp);
  fprintf(file,
    "options:\n"
    "  -o directory            The output directory.\n"
    "  -s --silent             Do not print anything while executing.\n"
    "  -v --verbose            Verbose error reporting.\n"
    "  --series-description    Textual description of the series.\n"
    "  --series-number         The series number to use.\n"
    "  --uid-prefix            A DICOM uid prefix (optional).\n"
    "  --version               Print the version and exit.\n"
    "  --build-version         Print source and build version.\n"
    "  --help                  Documentation for scancotodicom.\n"
  );
}

// Print the help
void scancotodicom_help(FILE *file, const char *command_name)
{
  scancotodicom_usage(file, command_name);

  fprintf(file,
    "\n");

  fprintf(file,
    "This program will convert a uCT file into a DICOM series.\n"
    "\n");
  fprintf(file,
    "It reads the uCT file header and generates a series of DICOM files.\n"
    "If you are converting multiple files that belong to the same study,\n"
    "then after converting the first file, you should supply on the command\n"
    "line all of the DICOM files produced from that file.  This allows the\n"
    "converter to keep all the study information consistent between all\n"
    "files that belong to the same study.\n"
    "\n");
}

// Print error
void scancotodicom_check_error(vtkObject *o)
{
  vtkScancoCTReader *reader = vtkScancoCTReader::SafeDownCast(o);
  vtkDICOMWriter *writer = vtkDICOMWriter::SafeDownCast(o);
  vtkDICOMParser *parser = vtkDICOMParser::SafeDownCast(o);
  const char *filename = 0;
  unsigned long errorcode = 0;
  if (writer)
  {
    filename = writer->GetFileName();
    errorcode = writer->GetErrorCode();
  }
  else if (reader)
  {
    filename = reader->GetInternalFileName();
    errorcode = reader->GetErrorCode();
  }
  else if (parser)
  {
    filename = parser->GetFileName();
    errorcode = parser->GetErrorCode();
  }
  if (!filename)
  {
    filename = "";
  }

  switch(errorcode)
  {
    case vtkErrorCode::NoError:
      return;
    case vtkErrorCode::FileNotFoundError:
      fprintf(stderr, "File not found: %s\n", filename);
      break;
    case vtkErrorCode::CannotOpenFileError:
      fprintf(stderr, "Cannot open file: %s\n", filename);
      break;
    case vtkErrorCode::UnrecognizedFileTypeError:
      fprintf(stderr, "Unrecognized file type: %s\n", filename);
      break;
    case vtkErrorCode::PrematureEndOfFileError:
      fprintf(stderr, "File is truncated: %s\n", filename);
      break;
    case vtkErrorCode::FileFormatError:
      fprintf(stderr, "Bad DICOM file: %s\n", filename);
      break;
    case vtkErrorCode::NoFileNameError:
      fprintf(stderr, "Output filename could not be used: %s\n", filename);
      break;
    case vtkErrorCode::OutOfDiskSpaceError:
      fprintf(stderr, "Out of disk space while writing file: %s\n", filename);
      break;
    default:
      fprintf(stderr, "An unknown error occurred.\n");
      break;
  }

  exit(1);
}

// Convert a date to DICOM format (in-place conversion)
void scancotodicom_convert_date(char date[32])
{
  // The input format is expected to be:
  // DD-MMM-YYYY hh:mm:ss.uuuuuu  (MMM is JAN, FEB, etc)
  // The output format is:
  // YYYYMMDDhhmmss.uuuuuu
  const char *months[12] = {
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
    "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
  };
  char *cp = date;
  unsigned int parts[7];
  for (int i = 0; i < 7; i++)
  {
    while (*cp == ' ') { cp++; }
    int lead = 0;
    while (cp[0] == '0' && isdigit(cp[1]))
    {
      lead++;
      cp++;
    }
    parts[i] = strtoul(cp, &cp, 10);
    if (i == 1 && isalpha(*cp))
    {
      for (int j = 0; j < 12; j++)
      {
        const char *month = months[j];
        if (toupper(cp[0]) == month[0] &&
            toupper(cp[1]) == month[1] &&
            toupper(cp[2]) == month[2])
        {
           parts[i] = j+1;
           break;
        }
      }
      while (isalpha(*cp)) { cp++; }
    }
    if (i == 6)
    {
      unsigned int denom = 10;
      while (denom <= parts[i]) { denom *= 10; }
      while (lead > 0) { lead--; denom *= 10; }
      if (denom > 1000000) { parts[i] /= (denom/1000000); }
      else { parts[i] *= (1000000/denom); }
    }
    if (*cp != '\0') { cp++; }
  }

  sprintf(date, "%04d%02d%02d%02d%02d%02d.%06d",
          parts[2] % 10000, parts[1] % 100, parts[0] % 100,
          parts[3] % 100, parts[4] % 100, parts[5] % 100,
          parts[6] % 1000000);
}

// Check that a file has a valid extension
bool isScancoCTFileName(const char *f)
{
  const char *suffixes[] = {
    ".isq", ".ISQ", ".rsq", ".RSQ", ".rad", ".RAD", ".aim", ".AIM", 0
  };

  size_t n = strlen(f);
  for (const char **s = suffixes; *s != 0; s++)
  {
    size_t m = strlen(*s);
    if (n > m && strcmp(f + n - m, *s) == 0)
    {
      return true;
    }
  }

  return false;
}

// Read the options
void scancotodicom_read_options(
  int argc, char *argv[],
  scancotodicom_options *options, vtkStringArray *files)
{
  options->no_reordering = false;
  options->series_description = 0;
  options->series_number = 0;
  options->uid_prefix = "2.25";
  options->silent = false;
  options->verbose = false;
  options->output = 0;
  options->input = 0;

  // read the options from the command line
  int argi = 1;
  while (argi < argc)
  {
    const char *arg = argv[argi++];
    if (arg[0] == '-')
    {
      if (strcmp(arg, "--") == 0)
      {
        // stop processing switches
        break;
      }
      else if (strcmp(arg, "--series-description") == 0 ||
               strcmp(arg, "--series-number") == 0 ||
               strcmp(arg, "--uid-prefix") == 0)
      {
        if (argi >= argc ||
            argv[argi][0] == '-')
        {
          fprintf(stderr, "\nA value must follow the \'%s\' flag\n\n", arg);
          exit(1);
        }
        if (strcmp(arg, "--series-description") == 0)
        {
          options->series_description = argv[argi];
        }
        else if (strcmp(arg, "--series-number") == 0)
        {
          options->series_number= argv[argi];
        }
        else if (strcmp(arg, "--uid-prefix") == 0)
        {
          options->uid_prefix = argv[argi];
        }
        argi++;
      }
      else if (strcmp(arg, "--silent") == 0)
      {
        options->silent = true;
      }
      else if (strcmp(arg, "--verbose") == 0)
      {
        options->verbose = true;
      }
      else if (strcmp(arg, "--version") == 0)
      {
        scancotodicom_version(stdout, argv[0], false);
        exit(0);
      }
      else if (strcmp(arg, "--build-version") == 0)
      {
        scancotodicom_version(stdout, argv[0], true);
        exit(0);
      }
      else if (strcmp(arg, "--help") == 0)
      {
        scancotodicom_help(stdout, argv[0]);
        exit(0);
      }
      else if (arg[0] == '-' && arg[1] == '-')
      {
        fprintf(stderr, "\nUnrecognized option %s\n\n", arg);
        scancotodicom_usage(stderr, argv[0]);
        exit(1);
      }
      else if (arg[0] == '-' && arg[1] != '-')
      {
        for (int argj = 1; arg[argj] != '\0'; argj++)
        {
          if (arg[argj] == 's')
          {
            options->silent = true;
          }
          else if (arg[argj] == 'v')
          {
            options->verbose = true;
          }
          else if (arg[argj] == 'o')
          {
            if (arg[argj+1] != '\0')
            {
              arg += argj+1;
            }
            else
            {
              if (argi >= argc)
              {
                fprintf(stderr, "\nA file must follow the \'-o\' flag\n\n");
                scancotodicom_usage(stderr, argv[0]);
                exit(1);
              }
              arg = argv[argi++];
            }
            options->output = arg;
            break;
          }
          else
          {
            fprintf(stderr, "\nUnrecognized \'%c\' in option %s\n\n", arg[argj], arg);
            scancotodicom_usage(stderr, argv[0]);
            exit(1);
          }
        }
      }
    }
    else
    {
      files->InsertNextValue(arg);
      vtkIdType m = files->GetMaxId();
      if (m >= 0)
      {
        const char *f = files->GetValue(m);
        if (isScancoCTFileName(f))
        {
          if (options->input == 0)
          {
            options->input = arg;
            files->SetNumberOfValues(m);
          }
          else
          {
            fprintf(stderr, "\nAt most one uCT file can be specified.\n");
            scancotodicom_usage(stderr, argv[0]);
            exit(1);
          }
        }
      }
    }
  }

  while (argi < argc)
  {
    files->InsertNextValue(argv[argi++]);
    vtkIdType m = files->GetMaxId();
    if (m >= 0)
    {
      const char *f = files->GetValue(m);
      if (isScancoCTFileName(f))
      {
        if (options->input == 0)
        {
          options->input = argv[argi-1];
          files->SetNumberOfValues(m);
        }
        else
        {
          fprintf(stderr, "\nAt most one uCT file can be specified.\n");
          scancotodicom_usage(stderr, argv[0]);
          exit(1);
        }
      }
    }
  }
}

// Convert one uCT file into a DICOM series
void scancotodicom_convert_one(
  const scancotodicom_options *options,
  const char *filename,
  vtkStringArray *a,
  const char *outfile)
{
  // read the Scanco file
  vtkSmartPointer<vtkScancoCTReader> reader =
    vtkSmartPointer<vtkScancoCTReader>::New();
  reader->SetFileName(filename);
  reader->UpdateInformation();
  scancotodicom_check_error(reader);

  // get info about the original scan dimensions
  int pixdim[3];
  double physdim[3];
  reader->GetScanDimensionsPixels(pixdim);
  reader->GetScanDimensionsPhysical(physdim);

  // get the file type
  int fileType = SCANCO_ISQ;
  const char *imageType = "ORIGINAL\\PRIMARY\\AXIAL";
  const char *modality = "CT";
  const char *version = reader->GetVersion();
  if (strncmp(version, "AIM", 3) == 0)
  {
    fileType = SCANCO_AIM;
    imageType = "ORIGINAL\\SECONDARY\\AXIAL";
    if (reader->GetDataScalarType() != VTK_SHORT)
    {
      modality = "SEG";
      fileType = SCANCO_AIM_SEG;
      imageType = "DERIVED\\PRIMARY";
    }
  }
  else if (physdim[2] == 0)
  {
    fileType = SCANCO_RAD;
    imageType = "ORIGINAL\\PRIMARY\\LOCALIZER";
  }

  // The meta data object
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();

  // read meta data from the sample DICOM file, if provided
  if (a->GetNumberOfValues() > 0)
  {
    vtkSmartPointer<vtkDICOMReader> dicomReader =
      vtkSmartPointer<vtkDICOMReader>::New();
    dicomReader->SetFileNames(a);
    if (fileType == SCANCO_RAD)
    {
      dicomReader->SetMemoryRowOrderToFileNative();
    }
    else
    {
      dicomReader->SetMemoryRowOrderToBottomUp();
    }
    dicomReader->UpdateInformation();
    meta->DeepCopy(dicomReader->GetMetaData());
  }

  // set metadata from the file header
  meta->Set(DC::Modality, modality);
  // meta->Set(DC::Laterality, /* "L" or "R" */);
  meta->Set(DC::ImageType, imageType);
  // DC::Manufacturer Scanco
  // DC::ManufacturerModelName reader->GetScannerType()
  // DC::DeviceSerialNumber reader->GetScannerID()
  double rescaleSlope = 1.0;
  double rescaleIntercept = 0.0;
  if (reader->GetMuScaling() != 0 && reader->GetMuWater() != 0)
  {
    // conversion to Hounsfield units
    rescaleIntercept = -1000.0;
    rescaleSlope = 1000.0/(reader->GetMuScaling()*reader->GetMuWater());
    meta->Set(DC::RescaleIntercept, rescaleIntercept);
    meta->Set(DC::RescaleSlope, rescaleSlope);
    meta->Set(DC::RescaleType, "HU");
  }
  meta->Set(DC::KVP, reader->GetEnergy());
  meta->Set(DC::AcquisitionNumber, reader->GetMeasurementIndex());
  meta->Set(DC::ExposureTime, reader->GetSampleTime());
  meta->Set(DC::XRayTubeCurrentInuA, 1000*reader->GetIntensity());
  if (fileType != SCANCO_RAD)
  {
    meta->Set(DC::SliceThickness, reader->GetSliceThickness());
    meta->Set(DC::DataCollectionDiameter, physdim[0]);
    meta->Set(DC::ReconstructionDiameter, physdim[0]);
  }

  // date
  char date[32];
  if (!meta->Has(DC::StudyDate))
  {
    strncpy(date, reader->GetCreationDate(), 32);
    scancotodicom_convert_date(date);
    meta->Set(DC::StudyTime, &date[8]);
    meta->Set(DC::SeriesTime, &date[8]);
    date[8] = '\0';
    meta->Set(DC::StudyDate, date);
    meta->Set(DC::SeriesDate, date);
  }

  if (fileType == SCANCO_AIM_SEG)
  {
    strncpy(date, reader->GetModificationDate(), 32);
    scancotodicom_convert_date(date);
    meta->Set(DC::CreationTime, &date[8]);
    date[8] = '\0';
    meta->Set(DC::CreationDate, date);
  }

  // patient
  const char *patient = reader->GetPatientName();
  meta->Set(DC::PatientName, patient);

  // set the metadata supplied on the command line
  if (options->series_description)
  {
    meta->Set(DC::SeriesDescription, options->series_description);
  }
  if (options->series_number)
  {
    meta->Set(DC::SeriesNumber, options->series_number);
  }

  // The DICOM orientation matrix
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();

  // Use the center of the volume and distance from reference line
  double zoffset = 0.0;
  double center = 0.5*physdim[0]*(pixdim[0] - 1)/pixdim[0];

  if (fileType == SCANCO_RAD)
  {
    // Convert localizer to DICOM coordinates (rotate)
    zoffset = reader->GetZPosition() - reader->GetReferenceLine();
    double radToDICOM[16] = {
      0.0, 0.0, 1.0, 0.0,
      1.0, 0.0, 0.0, -center,
      0.0, 1.0, 0.0, zoffset,
      0.0, 0.0, 0.0, 1.0 };
    matrix->DeepCopy(radToDICOM);
  }
  else
  {
    // Convert to DICOM patient coordinates as well as we can,
    // without knowing orientation of patient relative to scanner
    zoffset = reader->GetStartPosition() - reader->GetReferenceLine();
    double rasToDICOM[16] = {
     -1.0, 0.0, 0.0, center,
      0.0,-1.0, 0.0, center,
      0.0, 0.0, 1.0, zoffset,
      0.0, 0.0, 0.0, 1.0 };
    matrix->DeepCopy(rasToDICOM);
  }

  // prepare the writer to write the image
  vtkSmartPointer<vtkDICOMWriter> writer =
    vtkSmartPointer<vtkDICOMWriter>::New();
  writer->StreamingOn();
  if (reader->GetDataScalarType() != VTK_SIGNED_CHAR)
  {
    vtkSmartPointer<vtkDICOMCTGenerator> generator =
      vtkSmartPointer<vtkDICOMCTGenerator>::New();
    writer->SetGenerator(generator);
  }
  writer->SetMetaData(meta);
  writer->SetFilePrefix(outfile);
  writer->SetFilePattern("%s/IM-0001-%04.4d.dcm");
  writer->SetPatientMatrix(matrix);
  writer->SetRescaleSlope(rescaleSlope);
  writer->SetRescaleIntercept(rescaleIntercept);
  writer->SetInputConnection(reader->GetOutputPort());
  writer->SetFileSliceOrderToSame();
  if (fileType == SCANCO_RAD)
  {
    writer->SetMemoryRowOrderToFileNative();
  }
  else
  {
    writer->SetMemoryRowOrderToBottomUp();
  }
  writer->Write();
  scancotodicom_check_error(writer);
}

// This program will convert ScancoCT to DICOM
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

  // for the list of input DICOM files
  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  scancotodicom_options options;
  scancotodicom_read_options(argc, argv, &options, files);

  // whether to silence VTK warnings and errors
  vtkObject::SetGlobalWarningDisplay(options.verbose);

  // set the UID prefix
  if (options.uid_prefix)
  {
    vtkDICOMUtilities::SetUIDPrefix(options.uid_prefix);
  }

  // the output directory
  const char *outpath = options.output;
  if (!outpath)
  {
    fprintf(stderr,
      "\nNo output directory was specified (\'-o\' <directory>).\n\n");
    scancotodicom_usage(stderr, argv[0]);
    exit(1);
  }
  if (!options.input)
  {
    fprintf(stderr,
      "\nNo input file was specified.\n\n");
    scancotodicom_usage(stderr, argv[0]);
    exit(1);
  }

  int code = vtkDICOMFileDirectory::Access(outpath, vtkDICOMFileDirectory::Out);
  if (code == vtkDICOMFileDirectory::AccessDenied)
  {
    fprintf(stderr, "Cannot write to directory: %s\n", outpath);
    exit(1);
  }
  else if (code == vtkDICOMFileDirectory::ImpossiblePath)
  {
    fprintf(stderr, "option -o must name a directory, not a file.\n");
    exit(1);
  }
  else if (code == vtkDICOMFileDirectory::FileNotFound)
  {
    code = vtkDICOMFileDirectory::Create(outpath);
    if (code != vtkDICOMFileDirectory::Good)
    {
      fprintf(stderr, "Cannot create directory: %s\n", outpath);
      exit(1);
    }
  }

  scancotodicom_convert_one(&options, options.input, files, outpath);

  return 0;
}
