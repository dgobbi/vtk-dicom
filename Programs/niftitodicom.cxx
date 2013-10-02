/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

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
#include "vtkDICOMUtilities.h"
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIReader.h"

#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <vtkImageShiftScale.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkErrorCode.h>
#include <vtkSortFileNames.h>
#include <vtkSmartPointer.h>

#if (VTK_MAJOR_VERSION > 5) || (VTK_MINOR_VERSION > 9)
#include <vtkImageHistogramStatistics.h>
#endif

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

// Simple structure for command-line options
struct niftitodicom_options
{
  bool no_reordering;
  const char *modality;
  const char *series_description;
  const char *series_number;
  const char *uid_prefix;
  bool silent;
  bool verbose;
  const char *output;
  const char *input;
};


// Print the version
void niftitodicom_version(FILE *file, const char *command_name)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  fprintf(file,
    "%s %s (HEAD %8.8s, %s, %s)\n", cp,
    DICOM_VERSION, DICOM_SOURCE_VERSION, DICOM_BUILD_DATE, DICOM_BUILD_TIME);
}

// Print the options
void niftitodicom_usage(FILE *file, const char *command_name)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  niftitodicom_version(file, command_name);

  fprintf(file,
    "usage: %s -o directory file.nii [file.dcm ...]\n", cp);
  fprintf(file,
    "options:\n"
    "  -o directory            The output directory.\n"
    "  -s --silent             Do not echo output filenames.\n"
    "  -v --verbose            Verbose error reporting.\n"
    "  --no-reordering         Never reorder slices, rows, or columns.\n"
    "  --series-description    Textual description of the series.\n"
    "  --series-number         The series number ot use.\n"
    "  --modality              The modality: MR or CT or SC.\n"
    "  --uid-prefix            A DICOM uid prefix (optional).\n"
    "  --help                  Documentation for niftitodicom.\n"
  );
}

// Print the help
void niftitodicom_help(FILE *file, const char *command_name)
{
  niftitodicom_usage(file, command_name);

  fprintf(file,
    "\n");

  fprintf(file,
    "This program will convert a NIfTI file into a DICOM series.\n"
    "\n");
  fprintf(file,
    "It reads the NIfTI file header and does the best job that it can to\n"
    "generate a series of DICOM files.  To help it along, you can provide\n"
    "a DICOM file from the same series on the command line after the NIfTI\n"
    "file, or even better, list all of the DICOM files that were used as\n"
    "the source of the data in the NIfTI file.  Study-related meta data will\n"
    "be copied from these DICOM files into the output DICOM files.\n"
    "\n");
  fprintf(file,
    "Unless the --no-reordering option is provided, %s will use the\n"
    "information in the NIfTI header to return the slices to the original\n"
    "ordering (axial, sagittal, or coronal).\n"
    "\n", command_name);
}

// Print error
void niftitodicom_check_error(vtkObject *o)
{
  vtkNIFTIReader *reader = vtkNIFTIReader::SafeDownCast(o);
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
void niftitodicom_add_file(vtkStringArray *files, const char *filepath)
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

// Check that a file has a NIFTI name
bool isNIFTIFileName(const char *f)
{
  size_t n = strlen(f);
  return ((n > 4 && strcmp(f + n - 4, ".nii") == 0) ||
          (n > 7 && strcmp(f + n - 7, ".nii.gz") == 0));
}

// Read the options
void niftitodicom_read_options(
  int argc, char *argv[],
  niftitodicom_options *options, vtkStringArray *files)
{
  options->no_reordering = false;
  options->modality = 0;
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
      else if (strcmp(arg, "--no-reordering") == 0)
        {
        options->no_reordering = true;
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
        niftitodicom_version(stdout, argv[0]);
        exit(0);
        }
      else if (strcmp(arg, "--help") == 0)
        {
        niftitodicom_help(stdout, argv[0]);
        exit(0);
        }
      else if (arg[0] == '-' && arg[1] == '-')
        {
        fprintf(stderr, "\nUnrecognized option %s\n\n", arg);
        niftitodicom_usage(stderr, argv[0]);
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
                niftitodicom_usage(stderr, argv[0]);
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
            niftitodicom_usage(stderr, argv[0]);
            exit(1);
            }
          }
        }
      }
    else
      {
      niftitodicom_add_file(files, arg);
      vtkIdType m = files->GetMaxId();
      if (m >= 0)
        {
        const char *f = files->GetValue(m);
        if (isNIFTIFileName(f))
          {
          if (options->input == 0)
            {
            options->input = arg;
            files->SetNumberOfValues(m);
            }
          else
            {
            fprintf(stderr, "\nAt most one NIFTI file can be specified.\n");
            niftitodicom_usage(stderr, argv[0]);
            exit(1);
            }
          }
        }
      }
    }

  while (argi < argc)
    {
    niftitodicom_add_file(files, argv[argi++]);
    vtkIdType m = files->GetMaxId();
    if (m >= 0)
      {
      const char *f = files->GetValue(m);
      if (isNIFTIFileName(f))
        {
        if (options->input == 0)
          {
          options->input = argv[argi-1];
          files->SetNumberOfValues(m);
          }
        else
          {
          fprintf(stderr, "\nAt most one NIFTI file can be specified.\n");
          niftitodicom_usage(stderr, argv[0]);
          exit(1);
          }
        }
      }
    }
}

// Remove all characters but A-ZA-z0-9_ from a string
std::string niftitodicom_safe_string(const std::string& str)
{
  std::string out;

  size_t n = str.size();
  size_t m = 0;
  for (size_t i = 0; i < n; i++)
    {
    char c = str[i];
    if (!isalnum(c))
      {
      c = '_';
      }
    else
      {
      m = i + 1;
      }
    out.push_back(c);
    }

  out.resize(m);

  if (out.size() == 0)
    {
    out = "UNKNOWN";
    }

  return out;
}

// Convert one DICOM series into one NIFTI file
void niftitodicom_convert_one(
  const niftitodicom_options *options,
  const char *filename,
  vtkStringArray *a,
  const char *outfile)
{
  // The meta data object
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();

  // read the DICOM files
  vtkSmartPointer<vtkDICOMReader> dicomReader =
    vtkSmartPointer<vtkDICOMReader>::New();
  dicomReader->TimeAsVectorOn();
  dicomReader->SetFileNames(a);
  dicomReader->SetMemoryRowOrderToFileNative();
  if (a->GetNumberOfValues() > 0)
    {
    dicomReader->UpdateInformation();
    meta->DeepCopy(dicomReader->GetMetaData());
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

  // read the NIFTI file
  vtkSmartPointer<vtkNIFTIReader> reader =
    vtkSmartPointer<vtkNIFTIReader>::New();
  reader->TimeAsVectorOn();
  reader->SetFileName(filename);
  reader->Update();
  niftitodicom_check_error(reader);
  vtkAlgorithmOutput *lastOutput = reader->GetOutputPort();

  // get the NIFTI header information
  vtkNIFTIHeader *hdr = reader->GetNIFTIHeader();

  // check if slices were reordered by the reader
  bool slicesReordered = (reader->GetQFac() < 0);

  // get the matrix from the NIFTI file
  vtkMatrix4x4 *inputMatrix = 0;
  int xformCode = 0;
  if (reader->GetQFormMatrix())
    {
    inputMatrix = reader->GetQFormMatrix();
    xformCode = hdr->GetQFormCode();
    }
  else if (reader->GetSFormMatrix())
    {
    inputMatrix = reader->GetSFormMatrix();
    xformCode = hdr->GetSFormCode();
    }

  // convert to NIFTI coordinate system
  vtkSmartPointer<vtkDICOMToRAS> converter =
    vtkSmartPointer<vtkDICOMToRAS>::New();
  converter->SetInputConnection(reader->GetOutputPort());
  converter->SetRASToDICOM(1);
  converter->SetRASMatrix(inputMatrix);
  converter->SetAllowRowReordering(!options->no_reordering);
  converter->SetAllowColumnReordering(!options->no_reordering);
  converter->UpdateMatrix();
  lastOutput = converter->GetOutputPort();

  // check if slices have been reordered by vtkDICOMToRAS
  vtkSmartPointer<vtkMatrix4x4> checkMatrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
  if (inputMatrix)
    {
    checkMatrix->DeepCopy(inputMatrix);
    }
  // undo the NIFTI to DICOM x = -x, y = -y conversion in check matrix
  for (int j = 0; j < 4; j++)
    {
    checkMatrix->Element[0][j] = -checkMatrix->Element[0][j];
    checkMatrix->Element[1][j] = -checkMatrix->Element[1][j];
    }
  checkMatrix->Invert();
  // checkMatrix = PatientMatrix^(-1) * RASMatrix
  vtkMatrix4x4::Multiply4x4(
    checkMatrix, converter->GetPatientMatrix(), checkMatrix);
  // if z is negative, slices were reordered by vtkDIOCOMToRAS
  slicesReordered ^= (checkMatrix->GetElement(2, 2) < -0.1);

  // get the orientation matrix
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
  matrix->DeepCopy(converter->GetPatientMatrix());

  // convert to signed short if not short
  int scalarType = reader->GetOutput()->GetScalarType();
  vtkSmartPointer<vtkImageShiftScale> caster =
    vtkSmartPointer<vtkImageShiftScale>::New();

  if (scalarType != VTK_SHORT && scalarType != VTK_UNSIGNED_SHORT)
    {
#if (VTK_MAJOR_VERSION > 5) || (VTK_MINOR_VERSION > 9)
    if (scalarType == VTK_FLOAT || scalarType == VTK_DOUBLE)
      {
      // compute range
      vtkSmartPointer<vtkImageHistogramStatistics> histo =
        vtkSmartPointer<vtkImageHistogramStatistics>::New();
      histo->SetInputConnection(lastOutput);
      histo->Update();
      double minVal = fabs(histo->GetMinimum());
      double maxVal = fabs(histo->GetMaximum());
      if (minVal > 32768.0 || maxVal > 32767.0)
        {
        // scale down if out-of-range
        double v = (maxVal > minVal ? maxVal : minVal);
        caster->SetScale(32767.0/v);
        }
      else if (minVal < 2.047 && maxVal < 2.047)
        {
        // scale up by 1000 if values are very small
        caster->SetScale(1000.0);
        }
      }
#endif

    caster->SetInputConnection(lastOutput);
    caster->SetOutputScalarType(VTK_SHORT);
    lastOutput = caster->GetOutputPort();
    }

  // mix in the NIFTI header information
  if (xformCode == vtkNIFTIHeader::XFormTalairach)
    {
    meta->SetAttributeValue(DC::FrameOfReferenceUID, "1.2.840.10008.1.4.1.1");
    }
  else if (xformCode == vtkNIFTIHeader::XFormMNI152)
    {
    meta->SetAttributeValue(DC::FrameOfReferenceUID, "1.2.840.10008.1.4.1.15");
    }
  else if (xformCode != vtkNIFTIHeader::XFormScannerAnat)
    {
    meta->RemoveAttribute(DC::FrameOfReferenceUID);
    }

  // make the generator
  vtkSmartPointer<vtkDICOMMRGenerator> mrgenerator =
    vtkSmartPointer<vtkDICOMMRGenerator>::New();
  vtkSmartPointer<vtkDICOMCTGenerator> ctgenerator =
    vtkSmartPointer<vtkDICOMCTGenerator>::New();
  vtkDICOMGenerator *generator = mrgenerator;
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
    else
      {
      generator = 0;
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
  writer->SetInputConnection(lastOutput);
  writer->SetMemoryRowOrderToFileNative();
  writer->Write();
  niftitodicom_check_error(writer);
}

// Process a list of files
void niftitodicom_convert_files(
  niftitodicom_options *options, vtkStringArray *files,
  const char *outpath)
{
  const char *filename = options->input;

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
  niftitodicom_check_error(sorter);

  niftitodicom_convert_one(
    options, filename, sorter->GetOutputFileNames(), outpath);
}

// This program will convert NIFTI to DICOM
int main(int argc, char *argv[])
{
  // for the list of input DICOM files
  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  niftitodicom_options options;
  niftitodicom_read_options(argc, argv, &options, files);

  // whether to silence VTK warnings and errors
  vtkObject::SetGlobalWarningDisplay(options.verbose);

  // set the UID prefix
  if (options.uid_prefix)
    {
    vtkDICOMUtilities::SetUIDPrefix(options.uid_prefix);
    }

  // the output (NIFTI file or directory)
  const char *outpath = options.output;
  if (!outpath)
    {
    fprintf(stderr,
      "\nNo output directory was specified (\'-o\' <directory>).\n\n");
    niftitodicom_usage(stderr, argv[0]);
    exit(1);
    }
  if (!options.input)
    {
    fprintf(stderr,
      "\nNo input file was specified (.nii or .nii.gz).\n\n");
    niftitodicom_usage(stderr, argv[0]);
    exit(1);
    }

  bool isDirectory = vtksys::SystemTools::FileIsDirectory(outpath);
  if (!isDirectory)
    {
    fprintf(stderr, "option -o must give an existing directory.\n");
    exit(1);
    }

  niftitodicom_convert_files(&options, files, outpath);

  return 0;
}
