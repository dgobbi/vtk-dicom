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
#include "vtkDICOMDictionary.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMReader.h"
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMSliceSorter.h"
#include "vtkDICOMToRAS.h"
#include "vtkDICOMCTRectifier.h"
#include "vtkDICOMFile.h"
#include "vtkDICOMFileDirectory.h"
#include "vtkDICOMFilePath.h"
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIWriter.h"

#include "vtkVersion.h"
#include "vtkImageData.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include "vtkImageCast.h"
#include "vtkImageExtractComponents.h"
#include "vtkStringArray.h"
#include "vtkIntArray.h"
#include "vtkErrorCode.h"
#include "vtkSortFileNames.h"
#include "vtkSmartPointer.h"

#if (VTK_MAJOR_VERSION > 5) || (VTK_MINOR_VERSION > 9)
#include "vtkImageHistogramStatistics.h"
#endif

#include <string>
#include <vector>
#include <set>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// from dicomcli
#include "vtkConsoleOutputWindow.h"
#include "mainmacro.h"
#include "readquery.h"

// Simple structure for command-line options
struct dicomtonifti_options
{
  bool compress;
  bool recurse;
  bool follow_symlinks;
  bool fsl;
  bool reformat_to_axial;
  bool no_slice_reordering;
  bool no_row_reordering;
  bool no_column_reordering;
  bool no_qform;
  bool no_sform;
  bool batch;
  bool silent;
  bool verbose;
  int volume;
  double time_delta;
  int time_units;
  vtkDICOMTagPath time_tagpath;
  vtkDICOMTagPath time_delta_tagpath;
  const char *output;
};


// Print the version
void dicomtonifti_version(FILE *file, const char *command_name, bool verbose)
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
void dicomtonifti_usage(FILE *file, const char *command_name)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  fprintf(file,
    "usage:\n"
    "  %s -o file.nii file1.dcm [file2.dcm ...]\n\n"
    "  %s -o directory --batch file1.dcm [file2.dcm ...]\n\n", cp, cp);
  fprintf(file,
    "options:\n"
    "  -o <output.nii[.gz]>    The output file (or directory, if --batch).\n"
    "  -z --compress           Compress output files.\n"
    "  -r --recurse            Recurse into subdirectories.\n"
    "  -b --batch              Do multiple series at once.\n"
    "  -s --silent             Do not echo output filenames.\n"
    "  -v --verbose            Verbose error reporting.\n"
    "  -L --follow-symlinks    Follow symbolic links when recursing.\n"
    "  --fsl                   Format axial image for use in FSL.\n"
    "  --reformat-to-axial     Reformat the image into axial orientation.\n"
    "  --no-slice-reordering   Never reorder the slices.\n"
    "  --no-row-reordering     Never reorder the rows.\n"
    "  --no-column-reordering  Never reorder the columns.\n"
    "  --no-reordering         Never reorder slices, rows, or columns.\n"
    "  --no-qform              Don't include a qform in the NIFTI file.\n"
    "  --no-sform              Don't include an sform in the NIFTI file.\n"
    "  --time-tag              Set the tag to use for time coordinate.\n"
    "  --time-delta-tag        Set the tag to use for time spacing.\n"
    "  --time-delta            Force the time spacing to be the given value.\n"
    "  --volume N              Set which volume to output (starts at 0).\n"
    "  --version               Print the version and exit.\n"
    "  --build-version         Print source and build version.\n"
    "  --help                  Documentation for dicomtonifti.\n"
  );
}

// Print the help
void dicomtonifti_help(FILE *file, const char *command_name)
{
  dicomtonifti_usage(file, command_name);

  fprintf(file,
    "\n");

  fprintf(file,
    "This program will convert a DICOM series into a NIfTI file.\n"
    "\n");
  fprintf(file,
    "It reads the DICOM Position and Orientation metadata, and uses this\n"
    "information to generate qform and sform entries for the NIfTI header,\n"
    "after doing a conversion from the DICOM coordinate system to the NIfTI\n"
    "coordinate system.\n"
    "\n");
  fprintf(file,
    "By default, it will also reorder the columns of the image so that\n"
    "columns with higher indices are further to the patient\'s right (or\n"
    "in the case of sagittal images, further anterior).  Likewise, rows\n"
    "will be rearranged so that rows with higher indices are superior (or\n"
    "anterior for axial images).  Finally, it will reorder the slices\n"
    "so that the column direction, row direction, and slice direction\n"
    "follow the right-hand rule.\n"
    "\n");
  fprintf(file,
    "It is also possible to reformat the images into the axial orientation\n"
    "via the --reformat-to-axial option  This option is mutually exclusive\n"
    "with the no-reordering options.  The resulting orientation matrix will\n"
    "be the identity matrix.\n"
    "\n");
  fprintf(file,
    "If the output NIFTI files are to be used with the FMRIB FSL package,\n"
    "then use the --fsl option to reformat the images to match the standard\n"
    "FSL orientation: axial images with the slices arranged from inferior to\n"
    "superior, column number increasing from right to left, and row number\n"
    "increasing from posterior to anterior.  This will also convert the data\n"
    "type from unsigned 16-bit to signed 16-bit if necessary.\n"
    "\n");
  fprintf(file,
    "The --time-tag, --time-delta-tag, and --time-delta options can be used\n"
    "to tweak the time information.  By default, tags such as TriggerTime,\n"
    "TemporalPositionIdentifier, or TriggerTime are used to perform\n"
    "temporal sorting, but --time-tag can be used to explicitly name a tag.\n"
    "The --time-delta-tag option can be used to set which tag gives temporal\n"
    "spacing, if there is no tag that gives the temporal coordinate.\n"
    "The --time-delta option will force the temporal spacing to be a specific\n"
    "value, e.g. 500ms, 2s, or 2600us.\n"
    "\n");
  fprintf(file,
    "If batch mode is selected, the output file given with \"-o\" can be\n"
    "constructed from DICOM attributes, by providing the attribute names\n"
    "within curly braces.  For example, consider the following:\n"
    "\"{PatientID}-{StudyDate}/{SeriesDescription}-{SeriesNumber}.nii\"\n"
    "or something similar to produce a hierarchichal directory structure.\n"
    "The attributes used in the path should be from the following list:\n"
    "  PatientID, PatientName, PatientBirthDate, PatientSex,\n"
    "  StudyID, StudyDescription, StudyDate, StudyTime, StudyInstanceUID,\n"
    "  SeriesNumber, SeriesDescription, SeriesInstanceUID,\n"
    "  Modality, AccessionNumber.\n"
    "\n"
    "Here is an example of batch mode that recurses into subdirectories\n"
    "and compresses the output files, putting the results in the current\n"
    "directory:\n"
    "\n"
    "%s -brz -o {SeriesDescription}-{SeriesNumber}.nii /path/to/dicom/files\n"
    "\n",
    command_name);
}

// Print error
bool dicomtonifti_check_error(vtkObject *o)
{
  vtkDICOMReader *reader = vtkDICOMReader::SafeDownCast(o);
  vtkDICOMFileSorter *sorter = vtkDICOMFileSorter::SafeDownCast(o);
  vtkNIFTIWriter *writer = vtkNIFTIWriter::SafeDownCast(o);
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
      return false;
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

  return true;
}


bool dicomtonifti_time_delta(const char *arg, dicomtonifti_options *options)
{
  const char *unit_list[6] = {
    "s", "ms", "us", "Hz", "ppm", "rads"
  };
  int unit_consts[6] = {
    8, 16, 24, 32, 40, 48   // from NIFTI header
  };

  char *units;
  double t = strtod(arg, &units);
  if (units == arg || t == 0.0)
  {
    fprintf(stderr, "Illegal value for --time-delta: %s\n", arg);
    return false;
  }

  options->time_delta = t;

  if (units[0] != '\0')
  {
    options->time_units = 0;

    for (int i = 0; i < 6; i++)
    {
      if (strcmp(units, unit_list[i]) == 0)
      {
        options->time_units = unit_consts[i];
        break;
      }
    }

    if (options->time_units == 0)
    {
      fprintf(stderr, "Illegal value for --time-delta: %s\n", arg);
      fprintf(stderr, "Units must be s, ms, Hz, ppm, or rads.\n");
      return false;
    }
  }

  return true;
}

// Read the options
void dicomtonifti_read_options(
  int argc, char *argv[],
  dicomtonifti_options *options, vtkStringArray *files)
{
  options->recurse = false;
  options->compress = false;
  options->follow_symlinks = false;
  options->fsl = false;
  options->reformat_to_axial = false;
  options->no_slice_reordering = false;
  options->no_row_reordering = false;
  options->no_column_reordering = false;
  options->no_qform = false;
  options->no_sform = false;
  options->batch = false;
  options->silent = false;
  options->verbose = false;
  options->volume = -1;
  options->time_delta = 0.0;
  options->time_units = 16;  // default to msec
  options->time_tagpath = vtkDICOMTagPath();
  options->time_delta_tagpath = vtkDICOMTagPath();
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
      else if (strcmp(arg, "--recurse") == 0)
      {
        options->recurse = true;
      }
      else if (strcmp(arg, "--compress") == 0)
      {
        options->compress = true;
      }
      else if (strcmp(arg, "--follow-symlinks") == 0)
      {
        options->follow_symlinks = true;
      }
      else if (strcmp(arg, "--fsl") == 0)
      {
        options->fsl = true;
      }
      else if (strcmp(arg, "--reformat-to-axial") == 0)
      {
        options->reformat_to_axial = true;
      }
      else if (strcmp(arg, "--no-slice-reordering") == 0)
      {
        options->no_slice_reordering = true;
      }
      else if (strcmp(arg, "--no-row-reordering") == 0)
      {
        options->no_row_reordering = true;
      }
      else if (strcmp(arg, "--no-column-reordering") == 0)
      {
        options->no_column_reordering = true;
      }
      else if (strcmp(arg, "--no-reordering") == 0)
      {
        options->no_slice_reordering = true;
        options->no_row_reordering = true;
        options->no_column_reordering = true;
      }
      else if (strcmp(arg, "--no-qform") == 0)
      {
        options->no_qform = true;
      }
      else if (strcmp(arg, "--no-sform") == 0)
      {
        options->no_sform = true;
      }
      else if (strcmp(arg, "--time-delta") == 0 ||
               strcmp(arg, "--time-delta-tag") == 0 ||
               strcmp(arg, "--time-tag") == 0)
      {
        if (argi >= argc || argv[argi][0] == '-')
        {
          fprintf(stderr, "\nAn argument must follow \'%s\'\n\n", arg);
          dicomtonifti_usage(stderr, argv[0]);
          exit(1);
        }
        const char *optarg = arg;
        arg = argv[argi++];
        if (strcmp(optarg, "--time-delta") == 0)
        {
          if (!dicomtonifti_time_delta(arg, options))
          {
            exit(1);
          }
        }
        else
        {
          vtkDICOMItem data;
          QueryTagList qtlist;
          if (!dicomcli_readkey(arg, &data, &qtlist))
          {
            exit(1);
          }
          if (strcmp(optarg, "--time-delta-tag") == 0)
          {
            options->time_delta_tagpath = qtlist[0];
          }
          else
          {
            options->time_tagpath = qtlist[0];
          }
        }
      }
      else if (strcmp(arg, "--batch") == 0)
      {
        options->batch = true;
      }
      else if (strcmp(arg, "--silent") == 0)
      {
        options->silent = true;
      }
      else if (strcmp(arg, "--verbose") == 0)
      {
        options->verbose = true;
      }
      else if (strcmp(arg, "--volume") == 0)
      {
        if (argi >= argc || argv[argi][0] == '-')
        {
          fprintf(stderr, "\nA number must follow \'--volume\'\n\n");
          dicomtonifti_usage(stderr, argv[0]);
          exit(1);
        }
        arg = argv[argi++];
        options->volume = atoi(arg);
      }
      else if (strcmp(arg, "--version") == 0)
      {
        dicomtonifti_version(stdout, argv[0], false);
        exit(0);
      }
      else if (strcmp(arg, "--build-version") == 0)
      {
        dicomtonifti_version(stdout, argv[0], true);
        exit(0);
      }
      else if (strcmp(arg, "--help") == 0)
      {
        dicomtonifti_help(stdout, argv[0]);
        exit(0);
      }
      else if (arg[0] == '-' && arg[1] == '-')
      {
        fprintf(stderr, "\nUnrecognized option %s\n\n", arg);
        dicomtonifti_usage(stderr, argv[0]);
        exit(1);
      }
      else if (arg[0] == '-' && arg[1] != '-')
      {
        for (int argj = 1; arg[argj] != '\0'; argj++)
        {
          if (arg[argj] == 'z')
          {
            options->compress = true;
          }
          else if (arg[argj] == 'r')
          {
            options->recurse = true;
          }
          else if (arg[argj] == 'b')
          {
            options->batch = true;
          }
          else if (arg[argj] == 's')
          {
            options->silent = true;
          }
          else if (arg[argj] == 'v')
          {
            options->verbose = true;
          }
          else if (arg[argj] == 'L')
          {
            options->follow_symlinks = true;
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
                dicomtonifti_usage(stderr, argv[0]);
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
            dicomtonifti_usage(stderr, argv[0]);
            exit(1);
          }
        }
      }
    }
    else
    {
      files->InsertNextValue(arg);
    }
  }

  while (argi < argc)
  {
    files->InsertNextValue(argv[argi++]);
  }
}

// Remove all characters but A-Za-z0-9_ from a string
std::string dicomtonifti_safe_string(const std::string& input)
{
  std::string::const_iterator a = input.begin();
  std::string::const_iterator b = a;
  std::string s;
  while (a != input.end())
  {
    while (a != input.end() &&
           ((*a & 0x80) == 0) && isgraph(*a) && !ispunct(*a))
    {
      ++a;
    }
    s.append(b, a);
    b = a;
    while (a != input.end() &&
           (((*a & 0x80) != 0) || !isgraph(*a) || ispunct(*a)))
    {
      ++a;
    }
    if (b != a && b != input.begin() && a != input.end())
    {
      s.append("_");
    }
    b = a;
  }

  return s;
}

// Generate an output filename from meta data
std::string dicomtonifti_make_filename(
  const char *outfile, vtkDICOMMetaData *meta)
{
  std::string s;
  std::string key;
  std::string val;
  vtkDICOMValue v;

  const char *cp = outfile;
  const char *dp = cp;
  const char *bp = 0;
  while (*cp != '\0')
  {
    while (*cp != '{' && *cp != '}' && *cp != '\0') { cp++; }
    if (*cp == '}')
    {
      fprintf(stderr, "Missing \'{\': %s\n", outfile);
      exit(1);
    }
    if (*cp == '{')
    {
      bp = cp;
      while (*cp != '}' && *cp != '\0') { cp++; }
      if (*cp != '}')
      {
        fprintf(stderr, "Unmatched \'{\': %s\n", outfile);
        exit(1);
      }
      else
      {
        s.append(dp, bp);
        bp++;
        key.assign(bp, cp);
        cp++;
        dp = cp;
        v.Clear();
        vtkDICOMTag tag;
        if (key.length() > 0)
        {
          vtkDICOMDictEntry de = vtkDICOMDictionary::FindDictEntry(key.c_str());
          if (de.IsValid())
          {
            tag = de.GetTag();
          }
          else
          {
            fprintf(stderr, "Unrecognized key %s\n", key.c_str());
            exit(1);
          }
        }
        if (meta)
        {
          v = meta->Get(tag);
        }
        if (v.IsValid())
        {
          val.assign(dicomtonifti_safe_string(v.AsUTF8String()));
        }
        else if (meta)
        {
          fprintf(stderr, "Sorry, key %s not found.\n",
                  key.c_str());
          exit(1);
        }
        if (val.empty())
        {
          val = "Empty";
        }
        s.append(val);
      }
    }
  }
  s.append(dp, cp);

  return s;
}

// Convert one DICOM series into one NIFTI file
void dicomtonifti_convert_one(
  const dicomtonifti_options *options, vtkStringArray *a,
  const char *outfile)
{
  // read the files
  vtkSmartPointer<vtkDICOMReader> reader =
    vtkSmartPointer<vtkDICOMReader>::New();
  reader->SetMemoryRowOrderToFileNative();
  reader->TimeAsVectorOn();
  reader->SetFileNames(a);
  // check for user-supplied time info
  if (options->time_delta != 0.0 ||
      options->time_delta_tagpath.GetSize() > 0)
  {
    reader->GetSorter()->RepeatsAsTimeOn();
  }
  if (options->time_tagpath.GetSize() > 0)
  {
    vtkDICOMTagPath tagpath = options->time_tagpath;
    vtkDICOMTag tag = tagpath.GetHead();
    while (tagpath.HasTail())
    {
      reader->GetSorter()->SetTimeSequence(tag);
      tagpath = tagpath.GetTail();
      tag = tagpath.GetHead();
    }
    reader->GetSorter()->SetTimeTag(tag);
  }
  reader->Update();
  if (dicomtonifti_check_error(reader)) {
    return;
  }

  // get the output and the orientation matrix
  vtkAlgorithmOutput *lastOutput = reader->GetOutputPort();
  vtkMatrix4x4 *patientMatrix = reader->GetPatientMatrix();

  // extract just one volume, if requested
  vtkSmartPointer<vtkImageExtractComponents> extract =
    vtkSmartPointer<vtkImageExtractComponents>::New();
  extract->SetInputConnection(lastOutput);
  if (options->volume >= 0)
  {
    if (reader->GetOutput()->GetNumberOfScalarComponents() <= options->volume)
    {
      fprintf(stderr, "Only %d volumes, but --volume %d used.\n",
              reader->GetOutput()->GetNumberOfScalarComponents(),
              options->volume);
      return;
    }
    extract->SetComponents(options->volume);
    extract->Update();
    lastOutput = extract->GetOutputPort();
  }

  // check if slices were reordered by the reader
  vtkIntArray *fileIndices = reader->GetFileIndexArray();
  vtkIntArray *frameIndices = reader->GetFrameIndexArray();
  vtkIdType maxId = fileIndices->GetNumberOfTuples() - 1;
  int firstFile = fileIndices->GetComponent(0, 0);
  int lastFile = fileIndices->GetComponent(maxId, 0);
  int firstFrame = frameIndices->GetComponent(0, 0);
  int lastFrame = frameIndices->GetComponent(maxId, 0);
  bool slicesReordered = (lastFrame < firstFrame || lastFile < firstFile);

  // check for CT acquired with a tilted gantry
  vtkSmartPointer<vtkDICOMCTRectifier> rectifier =
    vtkSmartPointer<vtkDICOMCTRectifier>::New();
  if (fabs(vtkDICOMCTRectifier::GetGantryDetectorTilt(patientMatrix)) > 1e-2)
  {
    // tilt is significant, so regrid as a rectangular volume
    rectifier->SetInputConnection(lastOutput);
    rectifier->SetVolumeMatrix(patientMatrix);
    rectifier->Update();
    lastOutput = rectifier->GetOutputPort();
    patientMatrix = rectifier->GetRectifiedMatrix();
  }

  // convert to NIFTI coordinate system
  vtkSmartPointer<vtkDICOMToRAS> converter =
    vtkSmartPointer<vtkDICOMToRAS>::New();
  converter->SetInputConnection(lastOutput);
  converter->SetPatientMatrix(patientMatrix);
  converter->SetAllowRowReordering(!options->no_row_reordering);
  converter->SetAllowColumnReordering(!options->no_column_reordering);
  converter->UpdateMatrix();

  // check if slices have been reordered by vtkDICOMToRAS
  vtkSmartPointer<vtkMatrix4x4> checkMatrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
  checkMatrix->DeepCopy(patientMatrix);
  // undo the DICOM to NIFTI x = -x, y = -y conversion in check matrix
  for (int j = 0; j < 4; j++)
  {
    checkMatrix->Element[0][j] = -checkMatrix->Element[0][j];
    checkMatrix->Element[1][j] = -checkMatrix->Element[1][j];
  }
  checkMatrix->Invert();
  // checkMatrix = PatientMatrix^(-1) * RASMatrix
  vtkMatrix4x4::Multiply4x4(
    checkMatrix, converter->GetRASMatrix(), checkMatrix);
  // if z is negative, slices were reordered by vtkDIOCOMToRAS
  slicesReordered ^= (checkMatrix->GetElement(2, 2) < -0.1);

  // get the orientation matrix
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
  matrix->DeepCopy(converter->GetRASMatrix());

  // reformat to axial if requested
  lastOutput = converter->GetOutputPort();
  vtkSmartPointer<vtkImageReslice> reformat =
    vtkSmartPointer<vtkImageReslice>::New();
  vtkSmartPointer<vtkMatrix4x4> axes =
    vtkSmartPointer<vtkMatrix4x4>::New();
  int permutation[3] = { 0, 1, 2 };

  if (options->reformat_to_axial || options->fsl)
  {
    // this becomes meaningless after reformatting
    slicesReordered = false;

    // create a permutation matrix
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

    // if fsl, use the fsl orientation
    if (options->fsl)
    {
      double fslmat[16] = {
        -1.0,  0.0,  0.0,  0.0,
         0.0,  1.0,  0.0,  0.0,
         0.0,  0.0, -1.0,  0.0,
         0.0,  0.0,  0.0,  1.0 };

      vtkMatrix4x4::Multiply4x4(*axes->Element, fslmat, *axes->Element);
    }
    // reformat with the permutated axes
    reformat->SetResliceAxes(axes);
    reformat->SetInputConnection(lastOutput);
    lastOutput = reformat->GetOutputPort();

    // factor out the permuted axes
    vtkMatrix4x4::Multiply4x4(matrix, axes, matrix);
  }

  // convert to signed short if fsl
  int scalarType = reader->GetOutput()->GetScalarType();
  vtkSmartPointer<vtkImageCast> caster =
    vtkSmartPointer<vtkImageCast>::New();
  if (options->fsl && scalarType != VTK_UNSIGNED_CHAR &&
      scalarType != VTK_SHORT && scalarType != VTK_FLOAT)
  {
    double outputType = scalarType;

    if (scalarType == VTK_UNSIGNED_SHORT ||
        scalarType == VTK_CHAR ||
        scalarType == VTK_SIGNED_CHAR)
    {
      outputType = VTK_SHORT;
      if (scalarType == VTK_UNSIGNED_SHORT)
      {
        // change to float if values greater than 32767 exist
        const unsigned short *sptr = static_cast<const unsigned short *>(
          reader->GetOutput()->GetScalarPointer());
        vtkIdType n = reader->GetOutput()->GetNumberOfPoints();
        n *= reader->GetOutput()->GetNumberOfScalarComponents();
        for (vtkIdType i = 0; i < n; i++)
        {
          if (*sptr++ > 32767)
          {
            outputType = VTK_FLOAT;
            break;
          }
        }
      }
    }
    else
    {
      outputType = VTK_FLOAT;
    }

    caster->SetInputConnection(lastOutput);
    caster->SetOutputScalarType(outputType);
    lastOutput = caster->GetOutputPort();
  }

  // prepare the NIFTI header information
  vtkSmartPointer<vtkNIFTIHeader> hdr =
    vtkSmartPointer<vtkNIFTIHeader>::New();
  vtkDICOMMetaData *meta = reader->GetMetaData();

  // the descrip is the date followed by the series description and ID
  std::string date = meta->Get(DC::SeriesDate).AsString();
  if (date.length() >= 8)
  {
    const char *months[13] = { "/   /", "/Jan/", "/Feb/", "/Mar/", "/Apr/",
      "/May/", "/Jun/", "/Jul/", "/Aug/", "/Sep/", "/Oct/", "/Nov/", "/Dec/" };
    unsigned int month = (date[4] - '0')*10 + (date[5] - '0');
    month = (month > 12 ? 0 : month);
    date = date.substr(6, 2) + months[month] + date.substr(0, 4);
  }
  std::string descrip = date + " " +
    meta->Get(DC::SeriesDescription).AsString() + " " +
    meta->Get(DC::StudyID).AsString();
  descrip = descrip.substr(0, 79);

  // assume the units are millimetres/milliseconds
  hdr->SetXYZTUnits(0x02 + options->time_units);

  // get the phase encoding direction
  std::string phase = meta->Get(
    firstFile, firstFrame, vtkDICOMTag(0x0018,0x1312)).AsString();
  if (phase == "COLUMN")
  {
    hdr->SetDimInfo((permutation[2] << 4) +
                    (permutation[0] << 2) +
                    (permutation[1]));
  }
  else if (phase == "ROW")
  {
    hdr->SetDimInfo((permutation[2] << 4) +
                    (permutation[1] << 2) +
                    (permutation[0]));
  }
  else if (phase == "OTHER")
  {
    hdr->SetDimInfo(permutation[2] << 4);
  }

  // get the scale information, if same for all slices
  if (meta->Get(firstFile, firstFrame, DC::RescaleSlope).IsValid())
  {
    hdr->SetSclSlope(reader->GetRescaleSlope());
    hdr->SetSclInter(reader->GetRescaleIntercept());
  }

  // compute a cal_min, cal_max
  bool useWindowLevel = false;
  if (meta->Get(firstFile, firstFrame, DC::WindowWidth).IsValid())
  {
    useWindowLevel = true;
    double w = meta->Get(firstFile, firstFrame, DC::WindowWidth).GetDouble(0);
    double l = meta->Get(firstFile, firstFrame, DC::WindowCenter).GetDouble(0);
    int n = fileIndices->GetNumberOfTuples();
    for (int i = 1; i < n; i++)
    {
      int j = fileIndices->GetComponent(i, 0);
      int k = frameIndices->GetComponent(i, 0);
      double tw = meta->Get(j, k, DC::WindowWidth).GetDouble(0);
      double tl = meta->Get(j, k, DC::WindowCenter).GetDouble(0);
      if (tl != l || tw != w)
      {
        useWindowLevel = false;
        break;
      }
    }
    if (useWindowLevel)
    {
      double m = hdr->GetSclSlope();
      double b = hdr->GetSclInter();
      if (m == 0)
      {
        m = 1.0;
        b = 0.0;
      }
      hdr->SetCalMin((l - 0.5*w)*m + b);
      hdr->SetCalMax((l + 0.5*w)*m + b);
    }
  }
#if (VTK_MAJOR_VERSION > 5) || (VTK_MINOR_VERSION > 9)
  if (!useWindowLevel)
  {
    std::string photometric =
      meta->Get(DC::PhotometricInterpretation).AsString();
    if (photometric == "MONOCHROME1" || photometric == "MONOCHROME2")
    {
      // compute range rather than using DICOM window/level setting
      vtkSmartPointer<vtkImageHistogramStatistics> histo =
        vtkSmartPointer<vtkImageHistogramStatistics>::New();
      histo->SetInputConnection(lastOutput);
      histo->Update();
      double hrange[2];
      histo->GetAutoRange(hrange);
      if (hrange[0] < hrange[1])
      {
        hdr->SetCalMin(hrange[0]);
        hdr->SetCalMax(hrange[1]);
      }
    }
  }
#endif

  // prepare the writer to write the image
  vtkSmartPointer<vtkNIFTIWriter> writer =
    vtkSmartPointer<vtkNIFTIWriter>::New();
  writer->SetDescription(descrip.c_str());
  writer->SetNIFTIHeader(hdr);
  writer->SetFileName(outfile);
  if (reader->GetTimeDimension() > 1 &&
      options->volume < 0)
  {
    writer->SetTimeDimension(reader->GetTimeDimension());
    writer->SetTimeSpacing(reader->GetTimeSpacing());
    if (options->time_delta != 0.0)
    {
      // override if user gave --time-delta
      writer->SetTimeSpacing(options->time_delta);
    }
    else if (options->time_delta_tagpath.GetSize() > 0)
    {
      // override if user gave --time-delta-tag
      const vtkDICOMValue& tsv =
        meta->Get(firstFile, firstFrame, options->time_delta_tagpath);
      if (tsv.IsValid())
      {
        writer->SetTimeSpacing(tsv.AsDouble());
      }
    }
  }
  if ((options->no_slice_reordering && slicesReordered) ||
      options->fsl)
  {
    // force NIFTI file to store images in original DICOM order
    writer->SetQFac(-1.0);
  }
  if (!options->no_qform)
  {
    writer->SetQFormMatrix(matrix);
  }
  if (!options->no_sform)
  {
    writer->SetSFormMatrix(matrix);
  }
  writer->SetInputConnection(lastOutput);
  writer->Write();
  dicomtonifti_check_error(writer);
}

// Process a list of DICOM files
void dicomtonifti_convert_files(
  dicomtonifti_options *options, vtkStringArray *files,
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
  vtkSmartPointer<vtkDICOMFileSorter> sorter =
    vtkSmartPointer<vtkDICOMFileSorter>::New();
  sorter->SetInputFileNames(presorter->GetFileNames());
  sorter->Update();
  if (dicomtonifti_check_error(sorter)) {
    exit(1);
  }

  if (!options->batch)
  {
    std::string outfile = outpath;
    if (options->compress)
    {
      size_t os = strlen(outpath);
      if (os < 3 || outpath[os-3] != '.' ||
          tolower(outpath[os-2]) != 'g' ||
          tolower(outpath[os-1]) != 'z')
      {
        outfile.append(".gz");
      }
    }
    dicomtonifti_convert_one(
      options, sorter->GetOutputFileNames(), outfile.c_str());
  }
  else
  {
    vtkSmartPointer<vtkDICOMParser> parser =
      vtkSmartPointer<vtkDICOMParser>::New();
    vtkSmartPointer<vtkDICOMMetaData> meta =
      vtkSmartPointer<vtkDICOMMetaData>::New();
    parser->SetMetaData(meta);

    int m = sorter->GetNumberOfStudies();
    for (int j = 0; j < m; j++)
    {
      int k = sorter->GetFirstSeriesForStudy(j);
      int kl = sorter->GetLastSeriesForStudy(j);
      for (; k <= kl; k++)
      {
        // get metadata of first file
        vtkStringArray *a = sorter->GetFileNamesForSeries(k);
        std::string fname = a->GetValue(0);
        meta->Clear();
        parser->SetFileName(fname.c_str());
        parser->Update();
        if (dicomtonifti_check_error(parser)) {
          continue;
        }

        // generate a filename from the meta data
        std::string outfile =
          dicomtonifti_make_filename(outpath, meta);

        size_t os = outfile.length();
        if (options->compress &&
            (os < 3 || outfile[os-3] != '.' ||
             tolower(outfile[os-2]) != 'g' ||
             tolower(outfile[os-1]) != 'z'))
        {
          outfile.append(".gz");
        }

        // make the directory for the file
        if (k == sorter->GetFirstSeriesForStudy(j))
        {
          vtkDICOMFilePath path(outfile);
          path.PopBack();
          std::string dirname = path.AsString();
          int code = vtkDICOMFileDirectory::Create(dirname.c_str());
          if (code != vtkDICOMFileDirectory::Good)
          {
            fprintf(stderr, "Cannot create directory: %s\n",
                    dirname.c_str());
            exit(1);
          }
        }

        if (!options->silent)
        {
          printf("%s\n", outfile.c_str());
        }

        // convert the file
        dicomtonifti_convert_one(options, a, outfile.c_str());
      }
    }
  }
}

// Process a list of files and directories
void dicomtonifti_files_and_dirs(
  dicomtonifti_options *options, vtkStringArray *files,
  const char *outpath, std::set<std::string> *pastdirs)
{
  // look for directories among the files
  vtkSmartPointer<vtkStringArray> directories =
    vtkSmartPointer<vtkStringArray>::New();
  vtkSmartPointer<vtkStringArray> newfiles =
    vtkSmartPointer<vtkStringArray>::New();
  vtkIdType n = files->GetNumberOfValues();
  for (vtkIdType i = 0; i < n; i++)
  {
    std::string fname = files->GetValue(i);
    vtkDICOMFilePath path(fname);
    size_t m = fname.size();
    if ((m > 1 && (fname[m-1] == '/' || fname[m-1] == '\\')) ||
        path.IsDirectory())
    {
      if (pastdirs->size() == 0 ||
          (options->recurse &&
           (options->follow_symlinks || !path.IsSymlink())))
      {
        directories->InsertNextValue(fname.c_str());
      }
    }
    else
    {
      newfiles->InsertNextValue(fname.c_str());
    }
  }

  if (newfiles->GetNumberOfValues() > 0)
  {
    dicomtonifti_convert_files(options, newfiles, outpath);
  }

  n = directories->GetNumberOfValues();
  for (vtkIdType i = 0; i < n; i++)
  {
    std::string dirname = directories->GetValue(i);
    vtkDICOMFilePath path(dirname);

    // avoid infinite recursion
    std::string realpath = path.GetRealPath();
    if (pastdirs->count(realpath)) { continue; }
    pastdirs->insert(pastdirs->end(), realpath);

    vtkDICOMFileDirectory directory(dirname.c_str());
    int code = directory.GetError();
    if (code != vtkDICOMFileDirectory::Good)
    {
      fprintf(stderr, "Could not open directory %s\n", dirname.c_str());
    }
    else
    {
      files->Initialize();
      unsigned long nf = directory.GetNumberOfEntries();
      for (unsigned long j = 0; j < nf; j++)
      {
        const char *dirfile = directory.GetEntry(j);
        if (dirfile[0] != '.' || (dirfile[1] != '\0' &&
            (dirfile[1] != '.' || dirfile[2] != '\0')))
        {
          path.PushBack(dirfile);
          files->InsertNextValue(path.AsString());
          path.PopBack();
        }
      }
      dicomtonifti_files_and_dirs(options, files, outpath, pastdirs);
    }
  }
}

// This program will convert DICOM to NIFTI
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

  // for the list of input DICOM files
  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  dicomtonifti_options options;
  dicomtonifti_read_options(argc, argv, &options, files);

  // whether to silence VTK warnings and errors
  vtkObject::SetGlobalWarningDisplay(options.verbose);

  // the output (NIFTI file or directory)
  const char *outpath = options.output;
  if (!outpath)
  {
    fprintf(stderr,
      "\nNo output file was specified (\'-o\' <filename>).\n\n");
    dicomtonifti_usage(stderr, argv[0]);
    exit(1);
  }

  int code = vtkDICOMFile::Access(outpath, vtkDICOMFile::In);
  size_t l = strlen(outpath);
  vtkDICOMFilePath tmp(outpath);
  if (options.batch && code == vtkDICOMFile::FileIsDirectory)
  {
    tmp.PushBack(
      "{PatientID}-{StudyDate}-{SeriesDescription}-{SeriesNumber}.nii");
    outpath = tmp.AsString().c_str();
  }
  else if (!options.batch && (code == vtkDICOMFile::FileIsDirectory ||
           (l > 0 && (outpath[l-1] == '/' || outpath[l-1] == '\\'))))
  {
    fprintf(stderr, "The -o option must give a file, not a directory.\n");
    exit(1);
  }

  // make sure that input files were provided
  if (files->GetNumberOfValues() == 0)
  {
    fprintf(stderr, "\nNo input files were specified.\n\n");
    dicomtonifti_usage(stderr, argv[0]);
    exit(1);
  }

  std::set<std::string> pastdirs;
  dicomtonifti_files_and_dirs(&options, files, outpath, &pastdirs);

  return 0;
}
