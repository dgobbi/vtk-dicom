/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMMetaData.h"
#include "vtkDICOMSorter.h"
#include "vtkDICOMReader.h"
#include "vtkDICOMToRAS.h"
#include "vtkNIFTIWriter.h"
#include "vtkMatrix4x4.h"
#include "vtkStringArray.h"
#include "vtkIntArray.h"

#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// The help for the application
void dicomtonifti_usage(const char *command_name)
{
  const char *cp = command_name + strlen(command_name);
  while (cp != command_name && cp[-1] != '\\' && cp[-1] != '/') { --cp; }

  fprintf(stderr,
    "usage: %s -o file.nii file1.dcm [file2.dcm ...]\n", cp);
  fprintf(stderr,
    "       %s -o directory --batch file1.dcm [file2.dcm ...]\n", cp);
  fprintf(stderr,
    "options:\n"
    "  -o <output.nii[.gz]>    The output file.\n"
    "  --no-slice-reordering   Never reorder the slices.\n"
    "  --no-row-reordering     Never reorder the rows.\n"
    "  --no-column-reordering  Never reorder the columns.\n"
    "  --no-qform              Don't include a qform in the NIFTI file.\n"
    "  --no-sform              Don't include an sform in the NIFTI file.\n"
    "  --batch                 Do multiple series at once.\n"
  );
  fprintf(stderr,
    "\n");
  fprintf(stderr,
    "This program will convert a DICOM series into a NIfTI file.\n"
    "\n"
    "It reads the DICOM Position and Orientation metadata, and uses this\n"
    "information to generate qform and sform entries for the NIfTI header,\n"
    "after doing a conversion from the DICOM coordinate system to the NIfTI\n"
    "coordinate system.\n"
    "\n"
    "By default, it will also reorder the columns of the image so that\n"
    "columns with higher indices are further to the patient\'s right (or\n"
    "in the case of sagittal images, further anterior).  Likewise, rows\n"
    "will be rearranged so that rows with higher indices are superior (or\n"
    "anterior for axial images).  Finally, it will reorder the slices\n"
    "so that the column direction, row direction, and slice direction\n"
    "follow the right-hand rule.\n"
    "\n"
    "If batch mode is enabled, then the filenames will automatically be\n"
    "generated from the series description in the DICOM meta data.\n"
  );
}

// Simple structure for command-line options
struct dicomtonifti_options
{
  bool no_slice_reordering;
  bool no_row_reordering;
  bool no_column_reordering;
  bool no_qform;
  bool no_sform;
  bool batch;
  const char *output;
};

// This program will convert DICOM to NIFTI
int main(int argc, char *argv[])
{
  int rval = 0;

  struct dicomtonifti_options options;
  options.no_slice_reordering = false;
  options.no_row_reordering = false;
  options.no_column_reordering = false;
  options.no_qform = false;
  options.no_sform = false;
  options.batch = false;
  options.output = 0;

  // for the list of input DICOM files
  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

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
      else if (strcmp(arg, "--no-slice-reordering") == 0)
        {
        options.no_slice_reordering = true;
        }
      else if (strcmp(arg, "--no-row-reordering") == 0)
        {
        options.no_row_reordering = true;
        }
      else if (strcmp(arg, "--no-column-reordering") == 0)
        {
        options.no_column_reordering = true;
        }
      else if (strcmp(arg, "--no-qform") == 0)
        {
        options.no_qform = true;
        }
      else if (strcmp(arg, "--no-sform") == 0)
        {
        options.no_sform = true;
        }
      else if (strcmp(arg, "--batch") == 0)
        {
        options.batch = true;
        }
      else if (strncmp(arg, "-o", 2) == 0)
        {
        if (arg[2] != '\0')
          {
          arg += 2;
          }
        else
          {
          if (argi + 1 >= argc)
            {
            fprintf(stderr, "A file must follow the \'-o\' flag\n");
            dicomtonifti_usage(argv[0]);
            exit(1);
            }
          arg = argv[argi++];
          }
        options.output = arg;
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

  // the output (NIFTI file or directory)
  const char *outfile = options.output;
  if (!outfile)
    {
    fprintf(stderr, "No output file was specified (\'-o\' <filename>).\n");
    dicomtonifti_usage(argv[0]);
    exit(1);
    }

  // make sure that input files were provided
  if (files->GetNumberOfValues() == 0)
    {
    fprintf(stderr, "No input files were specified.\n");
    dicomtonifti_usage(argv[0]);
    exit(1);
    }

  // sort the files by study and series
  vtkSmartPointer<vtkDICOMSorter> sorter =
    vtkSmartPointer<vtkDICOMSorter>::New();
  sorter->SetInputFileNames(files);
  sorter->Update();
  vtkStringArray *a = sorter->GetOutputFileNames();

  // read the files
  vtkSmartPointer<vtkDICOMReader> reader =
    vtkSmartPointer<vtkDICOMReader>::New();
  reader->SetMemoryRowOrderToFileNative();
  reader->SetFileNames(a);

  // check if slices were reordered by the reader
  vtkIntArray *fileIndices = reader->GetFileIndexArray();
  vtkIdType maxId = fileIndices->GetMaxId() + 1;
  bool slicesReordered = (maxId > 0 &&
    fileIndices->GetValue(0) > fileIndices->GetValue(maxId));

  // convert to NIFTI coordinate system
  vtkSmartPointer<vtkDICOMToRAS> converter =
    vtkSmartPointer<vtkDICOMToRAS>::New();
  converter->SetInputConnection(reader->GetOutputPort());
  converter->SetPatientMatrix(reader->GetPatientMatrix());
  converter->SetAllowRowReordering(!options.no_row_reordering);
  converter->SetAllowColumnReordering(!options.no_column_reordering);
  converter->UpdateMatrix();

  // check if slices have been reordered by vtkDICOMToRAS
  vtkSmartPointer<vtkMatrix4x4> checkMatrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
  checkMatrix->DeepCopy(reader->GetPatientMatrix());
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

  // prepare the writer to write the image
  vtkSmartPointer<vtkNIFTIWriter> writer =
    vtkSmartPointer<vtkNIFTIWriter>::New();
  writer->SetFileName(outfile);
  if (options.no_slice_reordering && slicesReordered)
    {
    // force NIFTI file to store images in original DICOM order
    writer->SetQFac(-1.0);
    }
  if (!options.no_qform)
    {
    writer->SetQFormMatrix(converter->GetRASMatrix());
    }
  if (!options.no_sform)
    {
    writer->SetSFormMatrix(converter->GetRASMatrix());
    }
  writer->SetInputConnection(converter->GetOutputPort());
  writer->Write();

  return rval;
}
