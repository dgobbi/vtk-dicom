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
#include "vtkDICOMWriter.h"
#include "vtkDICOMMRGenerator.h"

#include <vtkSmartPointer.h>
#include <vtkStringArray.h>

#include <sstream>

#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = argv[0];

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  vtkSmartPointer<vtkDICOMSorter> sorter =
    vtkSmartPointer<vtkDICOMSorter>::New();

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  for (int i = 1; i < argc; i++)
    {
    files->InsertNextValue(argv[i]);
    }

  sorter->SetInputFileNames(files);
  sorter->Update();

  int m = sorter->GetNumberOfStudies();
  for (int j = 0; j < m; j++)
    {
    cout << "Study" << j << ":\n";
    int k = sorter->GetFirstSeriesInStudy(j);
    int n = sorter->GetNumberOfSeriesInStudy(j);
    n += k;
    for (; k < n; k++)
      {
      cout << "  Series " << k << ":\n";
      vtkStringArray *a = sorter->GetFileNamesForSeries(k);

      vtkSmartPointer<vtkDICOMReader> reader =
        vtkSmartPointer<vtkDICOMReader>::New();
      reader->SetFileNames(a);
      //reader->SetMemoryRowOrderToFileNative();
      reader->UpdateInformation();
      vtkDICOMMetaData *meta = reader->GetMetaData();

      vtkSmartPointer<vtkDICOMMRGenerator> generator =
        vtkSmartPointer<vtkDICOMMRGenerator>::New();

      vtkSmartPointer<vtkDICOMWriter> writer =
        vtkSmartPointer<vtkDICOMWriter>::New();
      writer->SetInputConnection(reader->GetOutputPort());
      writer->SetGenerator(generator);
      writer->SetPatientMatrix(reader->GetPatientMatrix());
      writer->SetMetaData(meta);
      //writer->SetMemoryRowOrderToFileNative();
      writer->SetFilePrefix("/tmp");
      writer->SetFilePattern("%s/IM-0001-%04.4d.dcm");
      writer->Write();
      }
    }

  return rval;
}
