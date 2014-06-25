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
#include "vtkMINCImageAttributes.h"
#include "vtkMINCImageReader.h"
#include "vtkMINC.h"
#include "vtkNIFTIHeader.h"
#include "vtkNIFTIWriter.h"

#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <vtkImageCast.h>
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

// Simple structure for command-line options
struct minctonifti_options
{
  bool compress;
  bool recurse;
  bool follow_symlinks;
  bool convert_to_float;
  bool fsl;
  bool reformat_to_axial;
  bool no_reordering;
  bool no_qform;
  bool no_sform;
  bool batch;
  bool silent;
  bool verbose;
  const char *output;
};


// Print the version
void minctonifti_version(FILE *file, const char *command_name, bool verbose)
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
void minctonifti_usage(FILE *file, const char *command_name)
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
    "  --float                 Convert real values to floating point.\n"
    "  --fsl                   Reformat the image for use in FSL.\n"
    "  --reformat-to-axial     Reformat the image into axial orientation.\n"
    "  --no-reordering         Never reorder slices, rows, or columns.\n"
    "  --no-qform              Don't include a qform in the NIFTI file.\n"
    "  --no-sform              Don't include an sform in the NIFTI file.\n"
    "  --version               Print the version and exit.\n"
    "  --build-version         Print source and build version.\n"
    "  --help                  Documentation for minctonifti.\n"
  );
}

// Print the help
void minctonifti_help(FILE *file, const char *command_name)
{
  minctonifti_usage(file, command_name);

  fprintf(file,
    "\n");

  fprintf(file,
    "This program will convert MINC files into NIfTI files.\n"
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
    "If batch mode is enabled, then the output filenames will automatically\n"
    "generated from the input file names.\n"
    "\n"
    "Here is an example of batch mode that recurses into subdirectories\n"
    "and compresses the output files, putting the results in the current\n"
    "directory:\n"
    "\n"
    "%s -brz -o . /path/to/minc/files\n"
    "\n",
    command_name);
}

// Print error
void minctonifti_check_error(vtkObject *o)
{
  vtkMINCImageReader *reader = vtkMINCImageReader::SafeDownCast(o);
  vtkNIFTIWriter *writer = vtkNIFTIWriter::SafeDownCast(o);
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
void minctonifti_add_file(vtkStringArray *files, const char *filepath)
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
void minctonifti_read_options(
  int argc, char *argv[],
  minctonifti_options *options, vtkStringArray *files)
{
  options->recurse = false;
  options->compress = false;
  options->follow_symlinks = false;
  options->fsl = false;
  options->convert_to_float = false;
  options->reformat_to_axial = false;
  options->no_reordering = false;
  options->no_qform = false;
  options->no_sform = false;
  options->batch = false;
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
      else if (strcmp(arg, "--float") == 0)
        {
        options->convert_to_float = true;
        }
      else if (strcmp(arg, "--fsl") == 0)
        {
        options->fsl = true;
        }
      else if (strcmp(arg, "--reformat-to-axial") == 0)
        {
        options->reformat_to_axial = true;
        }
      else if (strcmp(arg, "--no-reordering") == 0)
        {
        options->no_reordering = true;
        }
      else if (strcmp(arg, "--no-qform") == 0)
        {
        options->no_qform = true;
        }
      else if (strcmp(arg, "--no-sform") == 0)
        {
        options->no_sform = true;
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
      else if (strcmp(arg, "--version") == 0)
        {
        minctonifti_version(stdout, argv[0], false);
        exit(0);
        }
      else if (strcmp(arg, "--build-version") == 0)
        {
        minctonifti_version(stdout, argv[0], true);
        exit(0);
        }
      else if (strcmp(arg, "--help") == 0)
        {
        minctonifti_help(stdout, argv[0]);
        exit(0);
        }
      else if (arg[0] == '-' && arg[1] == '-')
        {
        fprintf(stderr, "\nUnrecognized option %s\n\n", arg);
        minctonifti_usage(stderr, argv[0]);
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
                minctonifti_usage(stderr, argv[0]);
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
            minctonifti_usage(stderr, argv[0]);
            exit(1);
            }
          }
        }
      }
    else
      {
      minctonifti_add_file(files, arg);
      }
    }

  while (argi < argc)
    {
    minctonifti_add_file(files, argv[argi++]);
    }
}

// Remove all characters but A-ZA-z0-9_ from a string
std::string minctonifti_safe_string(const std::string& str)
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

// Generate an output filename from input filename
std::string minctonifti_make_filename(
  const char *outpath, const char *filename)
{
  std::vector<std::string> sv;
  std::vector<std::string> fv;

  vtksys::SystemTools::SplitPath(outpath, sv);
  vtksys::SystemTools::SplitPath(filename, fv);
  std::string fname = fv.back();
  size_t l = fname.length();
  if (l > 4 && fname[l-4] == '.')
    {
    fname = fname.substr(0, l-4);
    }
  fname += ".nii";
  sv.push_back(fname);

  return vtksys::SystemTools::JoinPath(sv);
}

// Convert one MINC file into one NIFTI file
void minctonifti_convert_one(
  const minctonifti_options *options, const char *fname, const char *outfile)
{
  // read the files
  vtkSmartPointer<vtkMINCImageReader> reader =
    vtkSmartPointer<vtkMINCImageReader>::New();
  reader->SetFileName(fname);
  if (options->convert_to_float)
    {
    reader->RescaleRealValuesOn();
    }
  reader->Update();
  minctonifti_check_error(reader);

  // get the orientation matrix
  vtkMatrix4x4 *matrix = reader->GetDirectionCosines();
  double *spacing = reader->GetOutput()->GetSpacing();

  // reformat to axial if requested
  vtkAlgorithmOutput *lastOutput = reader->GetOutputPort();
  vtkSmartPointer<vtkImageReslice> reformat =
    vtkSmartPointer<vtkImageReslice>::New();
  vtkSmartPointer<vtkMatrix4x4> axes =
    vtkSmartPointer<vtkMatrix4x4>::New();
  int permutation[3] = { 0, 1, 2 };

  if (options->reformat_to_axial || options->fsl ||
      (options->no_reordering == false &&
       (spacing[0] < 0 || spacing[1] < 0 || spacing[2] < 0)))
    {
    // create a permutation matrix
    axes->DeepCopy(matrix);
    axes->Invert();
    int maxidx[3] = { -1, -1, -1 };
    int value[3] = { 1.0, 1.0, 1.0 };
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

    // ensure that spacing is positive
    double outputSpacing[3];
    for (int sdim = 0; sdim < 3; sdim++)
      {
      outputSpacing[permutation[sdim]] = fabs(spacing[sdim]);
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
    reformat->SetOutputSpacing(outputSpacing);
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
  vtkMINCImageAttributes *attr = reader->GetImageAttributes();

  // set the NIFTI file description
  std::string descrip;
  // use the minc "ident" attribute if present
  if (attr->HasAttribute("", MIident))
    {
    descrip = attr->GetAttributeValueAsString("", MIident);
    }
  else
    {
    // use the date followed by the series description and ID
    if (attr->HasAttribute(MIstudy, MIstart_time))
      {
      std::string date = attr->GetAttributeValueAsString(MIstudy, MIstart_time);
      if (date.length() >= 8)
        {
        const char *months[13] = { "/   /",
          "/Jan/", "/Feb/", "/Mar/", "/Apr/", "/May/", "/Jun/",
          "/Jul/", "/Aug/", "/Sep/", "/Oct/", "/Nov/", "/Dec/" };
        unsigned int month = (date[4] - '0')*10 + (date[5] - '0');
        month = (month > 12 ? 0 : month);
        date = date.substr(6, 2) + months[month] + date.substr(0, 4);
        descrip += date;
        }
      }
    if (attr->HasAttribute(MIstudy, MIprocedure))
      {
      if (descrip != "") { descrip += " "; }
      descrip += attr->GetAttributeValueAsString(MIstudy, MIprocedure);
      }
    if (attr->HasAttribute(MIstudy, MIstudy_id))
      {
      if (descrip != "") { descrip += " "; }
      descrip += attr->GetAttributeValueAsString(MIstudy, MIstudy_id);
      }
    }
  descrip = descrip.substr(0, 79);

  // assume the units are millimetres/milliseconds
  hdr->SetXYZTUnits(0x12);

  // get the phase encoding direction?
  // it doesn't seem to be available in minc

  // get the scale information, if same for all slices
  hdr->SetSclSlope(reader->GetRescaleSlope());
  hdr->SetSclInter(reader->GetRescaleIntercept());

  // compute a cal_min, cal_max
  double *range = reader->GetDataRange();
  if (range[1] > range[0])
    {
    double m = reader->GetRescaleSlope();
    double b = reader->GetRescaleIntercept();

    hdr->SetCalMin(range[0]*m + b);
    hdr->SetCalMax(range[1]*m + b);
    }

  // prepare the writer to write the image
  vtkSmartPointer<vtkNIFTIWriter> writer =
    vtkSmartPointer<vtkNIFTIWriter>::New();
  if (descrip != "")
    {
    writer->SetDescription(descrip.c_str());
    }
  writer->SetNIFTIHeader(hdr);
  writer->SetFileName(outfile);
  if (options->fsl)
    {
    // force NIFTI file to store images in FSL order
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
  minctonifti_check_error(writer);
}

// Process a list of DICOM files
void minctonifti_convert_files(
  minctonifti_options *options, vtkStringArray *files,
  const char *outpath)
{
  // sort the files by filename
  vtkSmartPointer<vtkSortFileNames> presorter =
    vtkSmartPointer<vtkSortFileNames>::New();
  presorter->NumericSortOn();
  presorter->IgnoreCaseOn();
  presorter->SetInputFileNames(files);
  presorter->Update();

  if (!options->batch)
    {
    std::string outfile = outpath;
    if (options->compress)
      {
      size_t os = strlen(outpath);
      if (os > 2 &&
          (outpath[os-3] != '.' ||
           tolower(outpath[os-2]) != 'g' ||
           tolower(outpath[os-1]) != 'z'))
        {
        outfile.append(".gz");
        }
      }
    minctonifti_convert_one(
      options, files->GetValue(0).c_str(), outfile.c_str());
    }
  else
    {
    vtkIdType m = files->GetNumberOfValues();
    for (vtkIdType j = 0; j < m; j++)
      {
      std::string fname = files->GetValue(j);

      // generate a filename from the meta data
      std::string outfile =
        minctonifti_make_filename(outpath, fname.c_str());

      if (options->compress)
        {
        outfile.append(".gz");
        }

      // make the directory for the file
      if (j == 0)
        {
        std::string dirname = vtksys::SystemTools::GetParentDirectory(
          outfile.c_str());
        if (!vtksys::SystemTools::MakeDirectory(dirname.c_str()))
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
      minctonifti_convert_one(options, fname.c_str(), outfile.c_str());
      }
    }
}

// Process a list of files and directories
void minctonifti_files_and_dirs(
  minctonifti_options *options, vtkStringArray *files,
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
    size_t m = fname.size();
    if ((m > 1 && (fname[m-1] == '/' || fname[m-1] == '\\')) ||
        vtksys::SystemTools::FileIsDirectory(fname.c_str()))
      {
      if (pastdirs->size() == 0 ||
          (options->recurse &&
           (options->follow_symlinks ||
            !vtksys::SystemTools::FileIsSymlink(fname.c_str()))))
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
    minctonifti_convert_files(options, newfiles, outpath);
    }

  n = directories->GetNumberOfValues();
  vtksys::Directory directory;
  std::vector<std::string> pathparts;
  for (vtkIdType i = 0; i < n; i++)
    {
    std::string dirname = directories->GetValue(i);

    // avoid infinite recursion
    std::string realpath = vtksys::SystemTools::GetRealPath(dirname.c_str());
    if (pastdirs->count(realpath)) { continue; }
    pastdirs->insert(pastdirs->end(), realpath);

    if (!directory.Load(dirname.c_str()))
      {
      fprintf(stderr, "Could not open directory %s\n", dirname.c_str());
      }
    else
      {
      files->Initialize();
      vtksys::SystemTools::SplitPath(directory.GetPath(), pathparts);
      unsigned long nf = directory.GetNumberOfFiles();
      for (unsigned long j = 0; j < nf; j++)
        {
        const char *dirfile = directory.GetFile(j);
        if (dirfile[0] != '.')
          {
          pathparts.push_back(dirfile);
          std::string fullpath = vtksys::SystemTools::JoinPath(pathparts);
          files->InsertNextValue(fullpath);
          pathparts.pop_back();
          }
        }
      minctonifti_files_and_dirs(options, files, outpath, pastdirs);
      }
    }
}

// This program will convert DICOM to NIFTI
int main(int argc, char *argv[])
{
  // for the list of input files
  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  minctonifti_options options;
  minctonifti_read_options(argc, argv, &options, files);

  // whether to silence VTK warnings and errors
  vtkObject::SetGlobalWarningDisplay(options.verbose);

  // the output (NIFTI file or directory)
  const char *outpath = options.output;
  if (!outpath)
    {
    fprintf(stderr,
      "\nNo output file was specified (\'-o\' <filename>).\n\n");
    minctonifti_usage(stderr, argv[0]);
    exit(1);
    }

  bool isDirectory = vtksys::SystemTools::FileIsDirectory(outpath);
  size_t l = strlen(outpath);
  if (options.batch && !isDirectory)
    {
    fprintf(stderr, "In batch mode, -o must give an existing directory.\n");
    exit(1);
    }
  else if (!options.batch && (isDirectory ||
           (l > 0 && (outpath[l-1] == '/' || outpath[l-1] == '\\'))))
    {
    fprintf(stderr, "The -o option must give a file, not a directory.\n");
    exit(1);
    }

  // make sure that input files were provided
  if (files->GetNumberOfValues() == 0)
    {
    fprintf(stderr, "\nNo input files were specified.\n\n");
    minctonifti_usage(stderr, argv[0]);
    exit(1);
    }

  std::set<std::string> pastdirs;
  minctonifti_files_and_dirs(&options, files, outpath, &pastdirs);

  return 0;
}
