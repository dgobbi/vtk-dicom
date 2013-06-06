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

#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// remove path portion of filename
const char *basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// This program will convert
int main(int argc, char *argv[])
{
  int rval = 0;

  if (argc < 4 || strcmp(argv[1], "-o") != 0)
    {
    printf("usage: %s -o file.nii file1.dcm [file2.dcm ...]\n",
           basename(argv[0]));
    return rval;
    }

  const char *outfile = argv[2];

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  for (int i = 3; i < argc; i++)
    {
    files->InsertNextValue(argv[i]);
    }

  vtkSmartPointer<vtkDICOMSorter> sorter =
    vtkSmartPointer<vtkDICOMSorter>::New();
  sorter->SetInputFileNames(files);
  sorter->Update();
  vtkStringArray *a = sorter->GetOutputFileNames();

  vtkSmartPointer<vtkDICOMReader> reader =
    vtkSmartPointer<vtkDICOMReader>::New();
  reader->SetMemoryRowOrderToFileNative();
  reader->SetFileNames(a);
  reader->Update();

  vtkSmartPointer<vtkDICOMToRAS> converter =
    vtkSmartPointer<vtkDICOMToRAS>::New();
  converter->SetInputConnection(reader->GetOutputPort());
  converter->AllowRowReorderingOff();
  converter->AllowColumnReorderingOff();
  //converter->UpdateMatrix();

  vtkSmartPointer<vtkNIFTIWriter> writer =
    vtkSmartPointer<vtkNIFTIWriter>::New();
  writer->SetFileName(outfile);
  writer->SetQFormMatrix(converter->GetRASMatrix());
  writer->SetInputConnection(converter->GetOutputPort());
  writer->Write();

  return rval;
}
