/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMParser.h"
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMCompiler.h"
#include "vtkDICOMUtilities.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>
#include <vtkTypeInt64Array.h>
#include <vtkByteSwap.h>

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
    printf("usage: %s [-o output_dir] file1.dcm [file2.dcm ...]\n",
      fileBasename(argv[0]));
    return rval;
    }

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  bool lookForOptions = true;
  bool verbose = false;
  std::string outputDir = ".";
  int argi = 1;
  while (argi < argc)
    {
    const char *arg = argv[argi++];
    if (lookForOptions && arg[0] == '-')
      {
      if (strcmp(arg, "--") == 0)
        {
        lookForOptions = false;
        }
      else if (strcmp(arg, "-v") == 0)
        {
        verbose = true;
        }
      else if (strcmp(arg, "-o") == 0 && argi < argc)
        {
        outputDir = argv[argi++];
        }
      else
        {
        fprintf(stderr, "%s: Unrecognized option %s\n",
          fileBasename(argv[0]), arg);
        return 1;
        }
      }
    else
      {
      files->InsertNextValue(arg);
      }
    }

  int ifile = 0;
  int jfile = 0;
  const char *fstring = "IM-%04d-%04d.dcm";
  char outfile[32];

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
  //compiler->KeepOriginalPixelDataVROn();

  vtkStringArray *a = sorter->GetOutputFileNames();
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
    offsetArray->SetTypedTuple(i, tp);
    }

  vtkDICOMUtilities::SetUIDPrefix("1.2.826.0.1.3680043.9.3042.");
  std::string seriesUID = vtkDICOMUtilities::GenerateUID(
    DC::SeriesInstanceUID);

  ++jfile;
  for (int i = 0; i < l; i++)
    {
    // write the DICOM series with the compiler
    sprintf(outfile, fstring, jfile, ++ifile);
    std::string outfilename = outputDir;
    if (outputDir.length() > 0 &&
       outputDir[outputDir.length()-1] != '/')
      {
      outfilename += "/";
      }
    outfilename += outfile;
    compiler->SetFileName(outfilename.c_str());
    std::string transferSyntax = data->Get(i,
      DC::TransferSyntaxUID).AsString();
    bool bigEndian = false;
    if (transferSyntax == "1.2.840.10008.1.2.2")
      {
      transferSyntax = "1.2.840.10008.1.2.1";
      bigEndian = true;
      }
    else if (transferSyntax == "1.2.840.113619.5.2")
      {
      transferSyntax = "1.2.840.10008.1.2";
      bigEndian = true;
      }
    compiler->SetTransferSyntaxUID(transferSyntax.c_str());
    //compiler->SetSOPInstanceUID(data->Get(
    //  i, DC::SOPInstanceUID).GetCharData());
    //compiler->SetSeriesInstanceUID(data->Get(
    //  i, DC::SeriesInstanceUID).GetCharData());
    //compiler->SetImplementationClassUID(data->Get(
    //  i, DC::ImplementationClassUID).GetCharData());
    //compiler->SetImplementationVersionName(data->Get(
    //  i, DC::ImplementationVersionName).GetCharData());
    //compiler->SetSourceApplicationEntityTitle(data->Get(
    //  i, DC::SourceApplicationEntityTitle).GetCharData());
    compiler->SetSeriesInstanceUID(seriesUID.c_str());
    compiler->SetIndex(i);
    compiler->WriteHeader();

    int frames = data->Get(i, DC::NumberOfFrames).AsInt();
    int xsize = data->Get(i, DC::Columns).AsInt();
    int ysize = data->Get(i, DC::Rows).AsInt();
    int samples = data->Get(i, DC::SamplesPerPixel).AsInt();
    int bitsAllocated = data->Get(i, DC::BitsAllocated).AsInt();
    size_t frameSize = static_cast<size_t>(xsize*ysize)*
      samples*bitsAllocated/8;
    if (verbose)
      {
      std::cout << "frames " << frames << std::endl;
      }
    frames = (frames <= 0 ? 1 : frames);

    if (parser->GetPixelDataFound())
      {
      vtkTypeInt64 tp[2];
      offsetArray->GetTypedTuple(i, tp);

      std::streamoff offset = static_cast<std::streamoff>(tp[0]);
      std::streamoff size = static_cast<std::streamoff>(tp[1]);

      unsigned char *buffer = new unsigned char[frameSize*frames];
      // check to see if it already has all the frames
      if (static_cast<size_t>(size - offset) == frameSize*frames)
        {
        frames = 1;
        }
      for (int ff = 0; ff < frames; i++, ff++)
        {
        offsetArray->GetTypedTuple(i, tp);

        offset = static_cast<std::streamoff>(tp[0]);
        size = static_cast<std::streamoff>(tp[1]);

        fname = a->GetValue(i);
        std::ifstream infile(fname.c_str(), ios::in | ios::binary);
        infile.seekg(offset, std::ios::beg);
        char *cbuffer = reinterpret_cast<char *>(buffer);
        infile.read(cbuffer + (size-offset)*ff, size-offset);
        infile.close();
        }
     if (bigEndian && bitsAllocated > 8)
        {
        vtkByteSwap::SwapVoidRange(buffer, (size-offset)*frames/2, 2);
        if (verbose)
          {
          std::cout << "convert to little endian" << std::endl;
          }
        }
      if (verbose)
        {
        std::cout << "size " << (size-offset)*frames << std::endl;
        }
      compiler->WritePixelData(buffer, (size-offset)*frames);
      delete [] buffer;
      --i;
      }

    compiler->Close();
    }

  return rval;
}
