/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMParser.h"
#include "vtkDICOMFile.h"
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMCompiler.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>
#include <vtkTypeInt64Array.h>

#include <vtksys/MD5.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define SetTupleValue SetTypedTuple
#define GetTupleValue GetTypedTuple
#endif

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

  const char *outfile = "/tmp/%s";

  // sort the files by study and series
  vtkSmartPointer<vtkDICOMFileSorter> sorter =
    vtkSmartPointer<vtkDICOMFileSorter>::New();
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
    int k = sorter->GetFirstSeriesForStudy(j);
    int kl = sorter->GetLastSeriesForStudy(j);
    for (; k <= kl; k++)
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
        char outpath[128];
        sprintf(outpath, outfile, fileBasename(fname.c_str()));
        compiler->SetFileName(outpath);
        const char *instanceUID =
          data->Get(i, DC::SOPInstanceUID).GetCharData();
        if (instanceUID == 0)
        {
          instanceUID =
            data->Get(i, DC::MediaStorageSOPInstanceUID).GetCharData();
        }
        compiler->SetSOPInstanceUID(instanceUID);
        compiler->SetTransferSyntaxUID(
          data->Get(i, DC::TransferSyntaxUID).GetCharData());
        compiler->SetSeriesInstanceUID(
          data->Get(i, DC::SeriesInstanceUID).GetCharData());
        compiler->SetImplementationClassUID(
          data->Get(i, DC::ImplementationClassUID).GetCharData());
        compiler->SetImplementationVersionName(
          data->Get(i, DC::ImplementationVersionName).GetCharData());
        compiler->SetSourceApplicationEntityTitle(
          data->Get(i, DC::SourceApplicationEntityTitle).GetCharData());
        compiler->SetIndex(i);
        compiler->WriteHeader();

        if (parser->GetPixelDataFound())
        {
          vtkTypeInt64 tp[2];
          offsetArray->GetTupleValue(i, tp);

          vtkDICOMFile::Size offset = tp[0];
          vtkDICOMFile::Size size = tp[1];

          vtkDICOMFile infile(fname.c_str(), vtkDICOMFile::In);
          infile.SetPosition(offset);
          unsigned char *buffer = new unsigned char[size-offset];
          infile.Read(buffer, size-offset);
          infile.Close();

          compiler->WritePixelData(buffer, size - offset);
          delete [] buffer;
        }

        compiler->Close();

        // compare the md5 hash
        char hash[2][40];
        for (int jj = 0; jj < 2; jj++)
        {
          const char *fileToHash = outpath;
          if (jj == 0)
          {
            fileToHash = fname.c_str();
          }
          vtksysMD5* hasher = vtksysMD5_New();
          vtksysMD5_Initialize(hasher);

          unsigned char hashbuf[8192];
          vtkDICOMFile f(fileToHash, vtkDICOMFile::In);
          while (!f.EndOfFile() && !f.GetError())
          {
            size_t c = f.Read(hashbuf, sizeof(hashbuf));
            vtksysMD5_Append(hasher, hashbuf, c);
          }
          f.Close();

          vtksysMD5_FinalizeHex(hasher, hash[jj]);
          hash[jj][32] = '\0';
          vtksysMD5_Delete(hasher);
        }

        if (strncmp(hash[0], hash[1], 32) != 0)
        {
          std::cerr << "Hash mismatch!\n";
          std::cerr << hash[0] << " " << fname.c_str() << "\n";
          std::cerr << hash[1] << " " << outpath << "\n";
        }
        else
        {
          std::cerr << "Matched for " << fname.c_str() << "\n";
        }
      }
    }
  }

  return rval;
}
