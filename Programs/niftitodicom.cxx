/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
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
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMMRGenerator.h"
#include "vtkDICOMCTGenerator.h"
#include "vtkDICOMToRAS.h"
#include "vtkDICOMCTRectifier.h"
#include "vtkDICOMUtilities.h"
#include "vtkDICOMFileDirectory.h"
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIReader.h"

#include "vtkVersion.h"
#include "vtkImageData.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include "vtkImageShiftScale.h"
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

// Kinds of reformats
enum MPREnum
{
  MPRAxial = 1,
  MPRCoronal = 2,
  MPRSagittal = 3
};

// Simple structure for command-line options
struct niftitodicom_options
{
  bool no_reordering;
  const char *modality;
  const char *series_description;
  const char *series_number;
  const char *uid_prefix;
  int mpr;
  bool silent;
  bool verbose;
  const char *output;
  const char *input;
};


// Print the version
void niftitodicom_version(FILE *file, const char *command_name, bool verbose)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  if (!verbose)
  {
    fprintf(file, "%s %s\n", cp, DICOM_VERSION);
    fprintf(file, "\n"
      "Copyright (c) 2012-2019, David Gobbi.\n\n"
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
void niftitodicom_usage(FILE *file, const char *command_name)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  fprintf(file,
    "usage:\n"
    "  %s -o directory file.nii [file.dcm ...]\n\n", cp);
  fprintf(file,
    "options:\n"
    "  -o directory            The output directory.\n"
    "  -s --silent             Do not print anything while executing.\n"
    "  -v --verbose            Verbose error reporting.\n"
    "  --no-reordering         Never reorder slices, rows, or columns.\n"
    "  --axial                 Produce axial slices.\n"
    "  --coronal               Produce coronal slices.\n"
    "  --sagittal              Produce sagittal slices.\n"
    "  --series-description    Textual description of the series.\n"
    "  --series-number         The series number to use.\n"
    "  --modality              The modality: MR or CT or SC.\n"
    "  --uid-prefix            A DICOM uid prefix (optional).\n"
    "  --version               Print the version and exit.\n"
    "  --build-version         Print source and build version.\n"
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
    "Unless the --no-reordering option is provided, it will ensure that\n"
    "the images are in the usual orientation (right is left, posterior is\n"
    "down) by reordering the columns or rows as compared to the NIFTI file.\n"
    "\n");
  fprintf(file,
    "If the NIFTI file is floating-point, then the data might be rescaled\n"
    "when written to DICOM as 16-bit integers.  If any data values are too\n"
    "large to fit into 16 bits, then all the data will be scaled down.  If\n"
    "the data values all have a magnitude smaller than 2.05, then all the\n"
    "data will be scaled up by a factor of 1000.\n"
    "\n");
}

// Print error
void niftitodicom_check_error(vtkObject *o)
{
  vtkNIFTIReader *reader = vtkNIFTIReader::SafeDownCast(o);
  vtkDICOMFileSorter *sorter = vtkDICOMFileSorter::SafeDownCast(o);
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

// Check that a file has a NIFTI name
bool isNIFTIFileName(const char *f)
{
  const char *suffixes[] = {
    ".nii", ".nii.gz", ".hdr", ".hdr.gz", ".img", ".img.gz", 0
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
void niftitodicom_read_options(
  int argc, char *argv[],
  niftitodicom_options *options, vtkStringArray *files)
{
  options->mpr = 0;
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
        niftitodicom_version(stdout, argv[0], false);
        exit(0);
      }
      else if (strcmp(arg, "--build-version") == 0)
      {
        niftitodicom_version(stdout, argv[0], true);
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
      files->InsertNextValue(arg);
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
    files->InsertNextValue(argv[argi++]);
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

// Convert one NIFTI file into a DICOM series
void niftitodicom_convert_one(
  const niftitodicom_options *options,
  const char *filename,
  vtkStringArray *a,
  const char *outfile)
{
  // The meta data object
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();

  // read the DICOM files, if provided
  vtkSmartPointer<vtkDICOMReader> dicomReader =
    vtkSmartPointer<vtkDICOMReader>::New();
  dicomReader->TimeAsVectorOn();
  dicomReader->SetFileNames(a);
  dicomReader->SetMemoryRowOrderToFileNative();
  vtkMatrix4x4 *readerMatrix = 0;
  if (a->GetNumberOfValues() > 0)
  {
    dicomReader->UpdateInformation();
    meta->DeepCopy(dicomReader->GetMetaData());
    readerMatrix = dicomReader->GetPatientMatrix();
  }

  // set the metadata supplied on the command line
  if (options->series_description)
  {
    meta->Set(DC::SeriesDescription, options->series_description);
  }
  if (options->series_number)
  {
    meta->Set(DC::SeriesNumber, options->series_number);
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

  // convert from NIFTI coordinate system to DICOM coordinate system
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

  // mpr reformat if requested
  vtkSmartPointer<vtkImageReslice> reformat =
    vtkSmartPointer<vtkImageReslice>::New();
  vtkSmartPointer<vtkMatrix4x4> axes =
    vtkSmartPointer<vtkMatrix4x4>::New();
  int permutation[3] = { 0, 1, 2 };

  if (options->mpr)
  {
    // this becomes meaningless after reformatting
    slicesReordered = false;

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

  // convert to signed short if not short
  int scalarType = reader->GetOutput()->GetScalarType();
  vtkSmartPointer<vtkImageShiftScale> caster =
    vtkSmartPointer<vtkImageShiftScale>::New();

  // whether to allow 8-bit DICOM
  bool allowUnsignedChar = false;
  if (options->modality && strcmp(options->modality, "SC") == 0)
  {
    allowUnsignedChar = true;
  }

  if (scalarType != VTK_SHORT && scalarType != VTK_UNSIGNED_SHORT &&
      (scalarType != VTK_UNSIGNED_CHAR || !allowUnsignedChar))
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
      double autoRange[2];
      histo->GetAutoRange(autoRange);

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
      else if (minVal < 20.47 && maxVal < 20.47)
      {
        // scale up by 100 if values are small
        caster->SetScale(100.0);
      }
      else if (minVal < 204.7 && maxVal < 204.7)
      {
        // scale up by 10
        caster->SetScale(10.0);
      }
    }
#endif

    caster->SetInputConnection(lastOutput);
    caster->SetOutputScalarType(VTK_SHORT);
    lastOutput = caster->GetOutputPort();
  }

  // check if requested to write as a CT tilted-gantry series via the
  // series of files that were sent to the reader
  vtkSmartPointer<vtkDICOMCTRectifier> rectifier =
    vtkSmartPointer<vtkDICOMCTRectifier>::New();
  if (readerMatrix &&
      fabs(vtkDICOMCTRectifier::GetGantryDetectorTilt(readerMatrix)) > 0.01)
  {
    rectifier->SetInputConnection(lastOutput);
    rectifier->SetVolumeMatrix(readerMatrix);
    rectifier->ReverseOn();
    rectifier->UpdateMatrix();
    vtkSmartPointer<vtkMatrix4x4> testMatrix =
      vtkSmartPointer<vtkMatrix4x4>::New();
    testMatrix->DeepCopy(rectifier->GetRectifiedMatrix());
    testMatrix->Invert();
    vtkMatrix4x4::Multiply4x4(testMatrix, matrix, testMatrix);
    bool isIdentity = true;
    for (int ii = 0; ii < 4; ii++)
    {
      for (int jj = 0; jj < 4; jj++)
      {
        double dd = testMatrix->GetElement(ii,jj) - (ii == jj);
        isIdentity &= (fabs(dd) < 1e-3);
      }
    }
    if (isIdentity)
    {
      // exactly the same orientation, so write like the reader's series
      rectifier->Update();
      lastOutput = rectifier->GetOutputPort();
      matrix = readerMatrix;
    }
  }

  // mix in the NIFTI header information
  if (xformCode == vtkNIFTIHeader::XFormTalairach)
  {
    meta->Set(DC::FrameOfReferenceUID, "1.2.840.10008.1.4.1.1");
  }
  else if (xformCode == vtkNIFTIHeader::XFormMNI152)
  {
    meta->Set(DC::FrameOfReferenceUID, "1.2.840.10008.1.4.1.15");
  }
  else if (xformCode != vtkNIFTIHeader::XFormScannerAnat)
  {
    meta->Erase(DC::FrameOfReferenceUID);
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
  else if (meta->Has(DC::SOPClassUID))
  {
    std::string classUID = meta->Get(DC::SOPClassUID).AsString();
    if (classUID == "1.2.840.10008.5.1.4.1.1.2" &&
        (scalarType == VTK_SHORT || scalarType == VTK_UNSIGNED_SHORT))
    {
      generator = ctgenerator;
    }
    else if (classUID == "1.2.840.10008.5.1.4.1.1.4" &&
             (scalarType == VTK_SHORT || scalarType == VTK_UNSIGNED_SHORT))
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
  vtkSmartPointer<vtkDICOMFileSorter> sorter =
    vtkSmartPointer<vtkDICOMFileSorter>::New();
  sorter->SetInputFileNames(presorter->GetFileNames());
  sorter->Update();
  niftitodicom_check_error(sorter);

  niftitodicom_convert_one(
    options, filename, sorter->GetOutputFileNames(), outpath);
}

// This program will convert NIFTI to DICOM
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

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

  niftitodicom_convert_files(&options, files, outpath);

  return 0;
}
