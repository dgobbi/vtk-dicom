/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMBuild.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMReader.h"
#include "vtkDICOMWriter.h"
#include "vtkDICOMSorter.h"
#include "vtkDICOMMRGenerator.h"
#include "vtkDICOMCTGenerator.h"
#include "vtkDICOMToRAS.h"
#include "vtkDICOMCTRectifier.h"
#include "vtkDICOMUtilities.h"

#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkErrorCode.h>
#include <vtkSortFileNames.h>
#include <vtkSmartPointer.h>

#include <vtksys/SystemTools.hxx>
#include <vtksys/Directory.hxx>
#include <vtksys/Glob.hxx>

#include <string>
#include <vector>
#include <set>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Kinds of reformats
enum MPREnum
{
  MPRAxial = 1,
  MPRCoronal = 2,
  MPRSagittal = 3
};

static const char *dicomtodicom_description[] = {
  " NEW", " MPR Ax", " MPR Cor", " MPR Sag"
};

// Simple structure for command-line options
struct dicomtodicom_options
{
  const char *modality;
  const char *series_description;
  const char *series_number;
  const char *uid_prefix;
  int mpr;
  bool silent;
  bool verbose;
  const char *output;
};


// Print the version
void dicomtodicom_version(FILE *file, const char *command_name, bool verbose)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  if (!verbose)
    {
    fprintf(file, "%s %s\n", cp, DICOM_VERSION);
    fprintf(file, "\n"
      "Copyright (c) 2012-2014, David Gobbi.\n\n"
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
void dicomtodicom_usage(FILE *file, const char *command_name)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  fprintf(file,
    "usage:\n"
    "  %s -o directory file.dcm ...\n\n", cp);
  fprintf(file,
    "options:\n"
    "  -o directory            The output directory.\n"
    "  -s --silent             Do not print anything while executing.\n"
    "  -v --verbose            Verbose error reporting.\n"
    "  --axial                 Produce axial slices.\n"
    "  --coronal               Produce coronal slices.\n"
    "  --sagittal              Produce sagittal slices.\n"
    "  --series-description    Textual description of the series.\n"
    "  --series-number         The series number to use.\n"
    "  --modality              The modality: MR or CT or SC.\n"
    "  --uid-prefix            A DICOM uid prefix (optional).\n"
    "  --version               Print the version and exit.\n"
    "  --build-version         Print source and build version.\n"
    "  --help                  Documentation for dicomtodicom.\n"
  );
}

// Print the help
void dicomtodicom_help(FILE *file, const char *command_name)
{
  dicomtodicom_usage(file, command_name);

  fprintf(file,
    "\n");

  fprintf(file,
    "This program allows adjustment of a DICOM series.\n"
    "\n");
  fprintf(file,
    "In its most basic functionality, this command reads a DICOM series and\n"
    "then writes it out with a new UID.  It strips out any meta data that is\n"
    "not recognized as part of the SOP class that it is writing.  In other\n"
    "words, its main purpose is to coerce the data to fit the requested SOP\n"
    "class.\n"
    "\n");
  fprintf(file,
    "Currently, only three output SOP classes can be written: Secondary\n"
    "Capture, CT, and MR.  Enhanced CT and Enhanced MR cannot be written,\n"
    "but they can be read, therefore this program can be used to convert\n"
    "enhanced single-file CT and MR DICOM into a series of DICOM files.\n"
    "\n");
  fprintf(file,
    "The written data has the ImageType set to DERIVED\\SECONDARY\\OTHER\n"
    "and has a new series number and name.  It isn't meant to replace the\n"
    "original data, it is simply meant to coerce the data into a format\n"
    "that might be more compatible with other software.\n"
    "\n");
  fprintf(file,
    "Reformatting of the data (MPR) is permitted during the conversion.\n"
    "This is an experimental feature and causes much of the per-instance\n"
    "meta data to be discarded.\n"
    "\n");
}

// Print error
void dicomtodicom_check_error(vtkObject *o)
{
  vtkDICOMReader *reader = vtkDICOMReader::SafeDownCast(o);
  vtkDICOMSorter *sorter = vtkDICOMSorter::SafeDownCast(o);
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
  else if (sorter)
    {
    filename = sorter->GetInternalFileName();
    errorcode = sorter->GetErrorCode();
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

// Add a dicom file to the list, expand if wildcard
void dicomtodicom_add_file(vtkStringArray *files, const char *filepath)
{
#ifdef _WIN32
  bool ispattern = false;
  bool hasbackslash = false;
  size_t n = strlen(filepath);
  for (size_t i = 0; i < n; i++)
    {
    if (filepath[i] == '*' || filepath[i] == '?' || filepath[i] == '[')
      {
      ispattern = true;
      }
    if (filepath[i] == '\\')
      {
      hasbackslash = true;
      }
    }

  std::string newpath = filepath;
  if (hasbackslash)
    {
    // backslashes interfere with vtksys::Glob
    vtksys::SystemTools::ConvertToUnixSlashes(newpath);
    }
  filepath = newpath.c_str();

  if (ispattern)
    {
    vtksys::Glob glob;
    if (glob.FindFiles(filepath))
      {
      const std::vector<std::string> &globfiles = glob.GetFiles();
      size_t m = globfiles.size();
      for (size_t j = 0; j < m; j++)
        {
        files->InsertNextValue(globfiles[j]);
        }
      }
    else
      {
      fprintf(stderr, "Could not match pattern: %s\n", filepath);
      exit(1);
      }
    }
  else
    {
    files->InsertNextValue(filepath);
    }
#else
  files->InsertNextValue(filepath);
#endif
}

// Read the options
void dicomtodicom_read_options(
  int argc, char *argv[],
  dicomtodicom_options *options, vtkStringArray *files)
{
  options->mpr = 0;
  options->modality = 0;
  options->series_description = 0;
  options->series_number = 0;
  options->uid_prefix = "2.25";
  options->silent = false;
  options->verbose = false;
  options->output = 0;

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
      else if (strcmp(arg, "--modality") == 0 ||
               strcmp(arg, "--series-description") == 0 ||
               strcmp(arg, "--series-number") == 0 ||
               strcmp(arg, "--uid-prefix") == 0)
        {
        if (argi >= argc ||
            argv[argi][0] == '-')
          {
          fprintf(stderr, "\nA value must follow the \'%s\' flag\n\n", arg);
          exit(1);
          }
        if (strcmp(arg, "--modality") == 0)
          {
          options->modality = argv[argi];
          }
        else if (strcmp(arg, "--series-description") == 0)
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
      else if (strcmp(arg, "--axial") == 0)
        {
        options->mpr = MPRAxial;
        }
      else if (strcmp(arg, "--coronal") == 0)
        {
        options->mpr = MPRCoronal;
        }
      else if (strcmp(arg, "--sagittal") == 0)
        {
        options->mpr = MPRSagittal;
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
        dicomtodicom_version(stdout, argv[0], false);
        exit(0);
        }
      else if (strcmp(arg, "--build-version") == 0)
        {
        dicomtodicom_version(stdout, argv[0], true);
        exit(0);
        }
      else if (strcmp(arg, "--help") == 0)
        {
        dicomtodicom_help(stdout, argv[0]);
        exit(0);
        }
      else if (arg[0] == '-' && arg[1] == '-')
        {
        fprintf(stderr, "\nUnrecognized option %s\n\n", arg);
        dicomtodicom_usage(stderr, argv[0]);
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
                dicomtodicom_usage(stderr, argv[0]);
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
            dicomtodicom_usage(stderr, argv[0]);
            exit(1);
            }
          }
        }
      }
    else
      {
      dicomtodicom_add_file(files, arg);
      }
    }

  while (argi < argc)
    {
    dicomtodicom_add_file(files, argv[argi++]);
    }
}

// Convert one DICOM series into another DICOM series
void dicomtodicom_convert_one(
  const dicomtodicom_options *options,
  vtkStringArray *a,
  const char *outfile)
{
  // read the files
  vtkSmartPointer<vtkDICOMReader> reader =
    vtkSmartPointer<vtkDICOMReader>::New();
  reader->SetMemoryRowOrderToFileNative();
  reader->TimeAsVectorOn();
  reader->SetFileNames(a);
  reader->Update();
  dicomtodicom_check_error(reader);

  // get a handle for the reader's output
  vtkAlgorithmOutput *lastOutput = reader->GetOutputPort();

  // The meta data object
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  meta->DeepCopy(reader->GetMetaData());
  meta->SetAttributeValue(DC::SeriesNumber,
    meta->GetAttributeValue(DC::SeriesNumber).AsUnsignedInt() +
    1000*(1 + options->mpr*100));
  std::string seriesDescription =
    (meta->GetAttributeValue(DC::SeriesDescription).AsString() +
     dicomtodicom_description[options->mpr]);
  if (seriesDescription.size() < 64)
    {
    meta->SetAttributeValue(DC::SeriesDescription, seriesDescription);
    }

  // set the metadata supplied on the command line
  if (options->series_description)
    {
    meta->SetAttributeValue(DC::SeriesDescription, options->series_description);
    }
  if (options->series_number)
    {
    meta->SetAttributeValue(DC::SeriesNumber, options->series_number);
    }

  // get the matrix from the DICOM series
  vtkMatrix4x4 *inputMatrix = reader->GetPatientMatrix();
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
  if (inputMatrix)
    {
    matrix->DeepCopy(inputMatrix);
    }

  // mpr reformat if requested
  vtkSmartPointer<vtkImageReslice> reformat =
    vtkSmartPointer<vtkImageReslice>::New();
  vtkSmartPointer<vtkDICOMCTRectifier> rectify =
    vtkSmartPointer<vtkDICOMCTRectifier>::New();
  vtkSmartPointer<vtkMatrix4x4> axes =
    vtkSmartPointer<vtkMatrix4x4>::New();
  int permutation[3] = { 0, 1, 2 };

  if (options->mpr)
    {
    // check for CT acquired with a tilted gantry
    if (fabs(vtkDICOMCTRectifier::GetGantryDetectorTilt(matrix)) > 1e-2)
      {
      // tilt is significant, so regrid as a rectangular volume
      rectify->SetInputConnection(lastOutput);
      rectify->SetVolumeMatrix(matrix);
      rectify->Update();
      lastOutput = rectify->GetOutputPort();
      matrix = rectify->GetRectifiedMatrix();
      }

    // create a permutation matrix to make the slices axial
    axes->DeepCopy(matrix);
    axes->Invert();
    int maxidx[3] = { -1, -1, -1 };
    double value[3] = { 1.0, 1.0, 1.0 };
    int prevmaxj = -1;
    int prevmaxi = -1;
    for (int kdim = 0; kdim < 2; kdim++)
      {
      int maxj = 0;
      int maxi = 0;
      double maxv = -0.0;
      for (int jdim = 0; jdim < 3; jdim++)
        {
        if (jdim == prevmaxj) { continue; }
        for (int idim = 0; idim < 3; idim++)
          {
          if (idim == prevmaxi) { continue; }
          double v = axes->GetElement(jdim, idim);
          if (v*v >= maxv)
            {
            maxi = idim;
            maxj = jdim;
            maxv = v*v;
            }
          }
        }
      maxidx[maxj] = maxi;
      value[maxj] = (axes->GetElement(maxj, maxi) < 0 ? -1.0 : 1.0);
      prevmaxj = maxj;
      prevmaxi = maxi;
      }

    axes->Zero();
    axes->SetElement(3, 3, 1.0);
    for (int jdim = 0; jdim < 3; jdim++)
      {
      int idim = maxidx[jdim];
      if (idim < 0)
        {
        idim = 3 - maxidx[(jdim+1)%3] - maxidx[(jdim+2)%3];
        maxidx[jdim] = idim;
        double perm = (((3 + maxidx[2] - maxidx[0])%3) == 2 ? 1.0 : -1.0);
        value[jdim] = value[(jdim+1)%3]*value[(jdim+2)%3]*perm;
        }
      permutation[jdim] = idim;
      axes->SetElement(jdim, idim, value[jdim]);
      }

    // change the permutation to the desired mpr
    if (options->mpr == MPRCoronal)
      {
      double cmatrix[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0,-1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0 };
      vtkMatrix4x4::Multiply4x4(*axes->Element, cmatrix, *axes->Element);
      int tperm[3] = { permutation[0], permutation[1], permutation[2] };
      permutation[0] = tperm[0];
      permutation[1] = tperm[2];
      permutation[2] = tperm[1];
      }
    else if (options->mpr == MPRSagittal)
      {
      double smatrix[16] = {
        0.0, 0.0,-1.0, 0.0,
        1.0, 0.0, 0.0, 0.0,
        0.0,-1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0 };
      vtkMatrix4x4::Multiply4x4(*axes->Element, smatrix, *axes->Element);
      int tperm[3] = { permutation[0], permutation[1], permutation[2] };
      permutation[0] = tperm[1];
      permutation[1] = tperm[2];
      permutation[2] = tperm[0];
      }

    // reformat with the permuted axes
    reformat->SetResliceAxes(axes);
    reformat->SetInputConnection(lastOutput);
    lastOutput = reformat->GetOutputPort();

    // factor out the permuted axes
    vtkMatrix4x4::Multiply4x4(matrix, axes, matrix);
    }

  // make the generator
  vtkSmartPointer<vtkDICOMMRGenerator> mrgenerator =
    vtkSmartPointer<vtkDICOMMRGenerator>::New();
  vtkSmartPointer<vtkDICOMCTGenerator> ctgenerator =
    vtkSmartPointer<vtkDICOMCTGenerator>::New();
  vtkDICOMGenerator *generator = 0;

  // get the generator from the supplied DICOM data
  std::string SOPClass =
    meta->GetAttributeValue(DC::SOPClassUID).AsString();
  if (SOPClass == "1.2.840.10008.5.1.4.1.1.2" ||
      SOPClass == "1.2.840.10008.5.1.4.1.1.2.1" ||
      SOPClass == "1.2.840.10008.5.1.4.1.1.2.2")
    {
    generator = ctgenerator;
    }
  else if (SOPClass == "1.2.840.10008.5.1.4.1.1.4" ||
           SOPClass == "1.2.840.10008.5.1.4.1.1.4.1" ||
           SOPClass == "1.2.840.10008.5.1.4.1.1.4.4")
    {
    generator = mrgenerator;
    }

  // allow the user to override the generator
  if (options->modality)
    {
    if (strcmp(options->modality, "CT") == 0)
      {
      generator = ctgenerator;
      }
    else if (strcmp(options->modality, "MR") == 0 ||
             strcmp(options->modality, "MRI") == 0)
      {
      generator = mrgenerator;
      }
    }

  // prepare the writer to write the image
  vtkSmartPointer<vtkDICOMWriter> writer =
    vtkSmartPointer<vtkDICOMWriter>::New();
  if (generator)
    {
    writer->SetGenerator(generator);
    }
  writer->SetMetaData(meta);
  writer->SetFilePrefix(outfile);
  writer->SetFilePattern("%s/IM-0001-%04.4d.dcm");
  writer->TimeAsVectorOn();
  if (reader->GetTimeDimension() > 1)
    {
    writer->SetTimeDimension(reader->GetTimeDimension());
    writer->SetTimeSpacing(reader->GetTimeSpacing());
    }
  writer->SetPatientMatrix(matrix);
  if (reader->GetRescaleSlope() > 0)
    {
    writer->SetRescaleSlope(reader->GetRescaleSlope());
    writer->SetRescaleIntercept(reader->GetRescaleIntercept());
    }
  writer->SetInputConnection(lastOutput);
  writer->SetMemoryRowOrderToFileNative();
  writer->Write();
  dicomtodicom_check_error(writer);
}

// Process a list of files
void dicomtodicom_convert_files(
  dicomtodicom_options *options, vtkStringArray *files,
  const char *outpath)
{
  // sort the files by filename first, as a fallback
  vtkSmartPointer<vtkSortFileNames> presorter =
    vtkSmartPointer<vtkSortFileNames>::New();
  presorter->NumericSortOn();
  presorter->IgnoreCaseOn();
  presorter->SetInputFileNames(files);
  presorter->Update();

  // sort the files by study and series
  vtkSmartPointer<vtkDICOMSorter> sorter =
    vtkSmartPointer<vtkDICOMSorter>::New();
  sorter->SetInputFileNames(presorter->GetFileNames());
  sorter->Update();
  dicomtodicom_check_error(sorter);

  dicomtodicom_convert_one(
    options, sorter->GetOutputFileNames(), outpath);
}

// This program will convert DICOM to DICOM
int main(int argc, char *argv[])
{
  // for the list of input DICOM files
  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  dicomtodicom_options options;
  dicomtodicom_read_options(argc, argv, &options, files);

  // whether to silence VTK warnings and errors
  vtkObject::SetGlobalWarningDisplay(options.verbose);

  // set the UID prefix
  if (options.uid_prefix)
    {
    vtkDICOMUtilities::SetUIDPrefix(options.uid_prefix);
    }

  // make sure that input files were provided
  if (files->GetNumberOfValues() == 0)
    {
    fprintf(stderr, "\nNo input files were specified.\n\n");
    dicomtodicom_usage(stderr, argv[0]);
    exit(1);
    }

  // the output
  const char *outpath = options.output;
  if (!outpath)
    {
    fprintf(stderr,
      "\nNo output directory was specified (\'-o\' <directory>).\n\n");
    dicomtodicom_usage(stderr, argv[0]);
    exit(1);
    }

  if (vtksys::SystemTools::FileExists(outpath))
    {
    if (!vtksys::SystemTools::FileIsDirectory(outpath))
      {
      fprintf(stderr, "option -o must give a directory, not a file.\n");
      exit(1);
      }
    }
  else if (!vtksys::SystemTools::MakeDirectory(outpath))
    {
    fprintf(stderr, "Cannot create directory: %s\n", outpath);
    exit(1);
    }

  dicomtodicom_convert_files(&options, files, outpath);

  return 0;
}
