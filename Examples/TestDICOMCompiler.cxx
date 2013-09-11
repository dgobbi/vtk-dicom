/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMParser.h"
#include "vtkDICOMSorter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMCompiler.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>
#include <vtkTypeInt64Array.h>

#include <vtksys/MD5.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// remove path portion of filename
const char *fileBasename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// This program read and write dicom files and check that the
// md5 of the written file is the same as for the original.
int main(int argc, char *argv[])
{
  int rval = 0;

  if (argc < 2)
    {
    printf("usage: %s file1.dcm [file2.dcm ...]\n", fileBasename(argv[0]));
    return rval;
    }

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  for (int argi = 1; argi < argc; argi++)
    {
    files->InsertNextValue(argv[argi]);
    }

  const char *outfile = "/tmp/test.dcm";

  // sort the files by study and series
  vtkSmartPointer<vtkDICOMSorter> sorter =
    vtkSmartPointer<vtkDICOMSorter>::New();
  sorter->RequirePixelDataOff();
  sorter->SetInputFileNames(files);
  sorter->Update();

  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  vtkSmartPointer<vtkDICOMMetaData> data =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  parser->SetMetaData(data);

  vtkSmartPointer<vtkDICOMCompiler> compiler =
    vtkSmartPointer<vtkDICOMCompiler>::New();
  compiler->SetMetaData(data);
  compiler->KeepOriginalPixelDataVROn();

  int m = sorter->GetNumberOfStudies();
  for (int j = 0; j < m; j++)
    {
    int k = sorter->GetFirstSeriesInStudy(j);
    int n = sorter->GetNumberOfSeriesInStudy(j);
    n += k;
    for (; k < n; k++)
      {
      vtkStringArray *a = sorter->GetFileNamesForSeries(k);
      int l = static_cast<int>(a->GetNumberOfValues());
      std::string fname = a->GetValue(0);

      data->Clear();
      data->SetNumberOfInstances(static_cast<int>(l));

      vtkSmartPointer<vtkTypeInt64Array> offsetArray =
        vtkSmartPointer<vtkTypeInt64Array>::New();
      offsetArray->SetNumberOfComponents(2);
      offsetArray->SetNumberOfTuples(l);

      for (int i = 0; i < l; i++)
        {
        // read the DICOM series with the parser
        fname = a->GetValue(i);
        parser->SetIndex(i);
        parser->SetFileName(fname.c_str());
        parser->Update();

        vtkTypeInt64 tp[2];
        tp[0] = parser->GetFileOffset();
        tp[1] = parser->GetFileSize();
        offsetArray->SetTupleValue(i, tp);
        }

      for (int i = 0; i < l; i++)
        {
        // write the DICOM series with the compiler
        fname = a->GetValue(i);
        compiler->SetFileName(outfile);
        compiler->SetSOPInstanceUID(data->GetAttributeValue(
          i, DC::SOPInstanceUID).GetCharData());
        compiler->SetTransferSyntaxUID(data->GetAttributeValue(
          i, DC::TransferSyntaxUID).GetCharData());
        compiler->SetSeriesInstanceUID(data->GetAttributeValue(
          i, DC::SeriesInstanceUID).GetCharData());
        compiler->SetImplementationClassUID(data->GetAttributeValue(
          i, DC::ImplementationClassUID).GetCharData());
        compiler->SetImplementationVersionName(data->GetAttributeValue(
          i, DC::ImplementationVersionName).GetCharData());
        compiler->SetSourceApplicationEntityTitle(data->GetAttributeValue(
          i, DC::SourceApplicationEntityTitle).GetCharData());
        compiler->SetIndex(i);
        compiler->WriteHeader();

        if (parser->GetPixelDataFound())
          {
          vtkTypeInt64 tp[2];
          offsetArray->GetTupleValue(i, tp);

          std::streamoff offset = static_cast<std::streamoff>(tp[0]);
          std::streamoff size = static_cast<std::streamoff>(tp[1]);

          std::ifstream infile(fname.c_str(), ios::in | ios::binary);
          infile.seekg(offset, std::ios::beg);
          char *buffer = new char[size-offset];
          infile.read(buffer, size-offset);
          infile.close();

          compiler->WritePixelData(buffer, size - offset);
          delete [] buffer;
          }

        compiler->Close();

        // compare the md5 hash
        char hash[2][40];
        for (int jj = 0; jj < 2; jj++)
          {
          const char *fileToHash = outfile;
          if (jj == 0)
            {
            fileToHash = fname.c_str();
            }
          vtksysMD5* hasher = vtksysMD5_New();
          vtksysMD5_Initialize(hasher);

          char hashbuf[8192];
          std::ifstream f(fileToHash, ios::in | ios::binary);
          while (f.good())
            {
            f.read(hashbuf, static_cast<std::streamsize>(sizeof(hashbuf)));
            std::streamsize c = f.gcount();
            vtksysMD5_Append(
              hasher, reinterpret_cast<unsigned char *>(hashbuf), c);
            }

          vtksysMD5_FinalizeHex(hasher, hash[jj]);
          hash[jj][32] = '\0';
          vtksysMD5_Delete(hasher);
          }

        if (strncmp(hash[0], hash[1], 32) != 0)
          {
          std::cerr << "Hash mismatch!\n";
          std::cerr << hash[0] << " " << fname.c_str() << "\n";
          std::cerr << hash[1] << " " << outfile << "\n";
          return 1;
          }
        }
      }
    }

  return rval;
}
