/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkNIFTIWriter.h"
#include "vtkNIFTIReader.h"
#include "vtkMatrix4x4.h"
#include "vtkImageData.h"
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

  if (argc < 2)
    {
    printf("usage: %s input.nii output.nii\n", basename(argv[0]));
    return rval;
    }

  vtkSmartPointer<vtkNIFTIReader> reader =
    vtkSmartPointer<vtkNIFTIReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  double center[3];
  reader->GetOutput()->GetCenter(center);

  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
  matrix->SetElement(0, 3, -center[0]);
  matrix->SetElement(1, 3, -center[1]);
  matrix->SetElement(2, 3, -center[2]);

  vtkSmartPointer<vtkNIFTIWriter> writer =
    vtkSmartPointer<vtkNIFTIWriter>::New();
  writer->SetInputConnection(reader->GetOutputPort());
  writer->SetFileName(argv[2]);
  writer->SetSFormMatrix(matrix);
  writer->SetQFormMatrix(matrix);
  writer->Update();

  return rval;
}
