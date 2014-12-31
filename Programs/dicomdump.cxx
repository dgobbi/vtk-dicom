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
#include "vtkDICOMSorter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMItem.h"

// from dicomcli
#include "readquery.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32)
#include <windows.h>
#endif

#define MAX_INDENT 24
#define INDENT_SIZE 2
#define MAX_LENGTH 120

// print the version
void printVersion(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2015, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void printUsage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s file1.dcm [file2.dcm ...]\n\n", cp);
  fprintf(file, "options:\n"
    "  -q <query.txt>  Provide a file that lists which elements to print.\n"
    "  --help      Print a brief help message.\n"
    "  --version   Print the software version.\n");
}

// print the help
void printHelp(FILE *file, const char *cp)
{
  printUsage(file, cp);
  fprintf(file, "\n"
    "Dump the metadata from a DICOM series as text.\n");
}

// remove path portion of filename
const char *fileBasename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// Print out one data element
void printElement(
  vtkDICOMMetaData *meta, const vtkDICOMItem *item,
  const vtkDICOMDataElementIterator &iter, int depth)
{
  vtkDICOMTag tag = iter->GetTag();
  int g = tag.GetGroup();
  int e = tag.GetElement();
  vtkDICOMVR vr = iter->GetVR();
  const char *name = "";
  vtkDICOMDictEntry d;
  if (item)
    {
    d = item->FindDictEntry(tag);
    }
  else if (meta)
    {
    d = meta->FindDictEntry(tag);
    }
  if (d.IsValid())
    {
    name = d.GetName();
    if (d.GetVR() != vr &&
        !(d.GetVR() == vtkDICOMVR::XS &&
          (vr == vtkDICOMVR::SS || vr == vtkDICOMVR::US)) &&
        !(d.GetVR() == vtkDICOMVR::OX &&
          (vr == vtkDICOMVR::OB || vr == vtkDICOMVR::OW)))
      {
      printf("VR mismatch! %s != %s %s\n",
             vr.GetText(), d.GetVR().GetText(), name);
      }
    }
  else if ((tag.GetGroup() & 0xFFFE) != 0 && tag.GetElement() == 0)
    {
    // group is even, element is zero
    name = "GroupLength";
    }
  else if ((tag.GetGroup() & 0x0001) != 0 &&
           (tag.GetElement() & 0xFF00) == 0)
    {
    // group is odd, element is a creator element
    name = "PrivateCreator";
    }
  // allow multiple values (i.e. for each image in series)
  vtkDICOMValue v = iter->GetValue();
  unsigned int vn = v.GetNumberOfValues();
  const vtkDICOMValue *vp = v.GetMultiplexData();
  if (vp == 0)
    {
    vp = &v;
    vn = 1;
    }

  // make an indentation string
  if (INDENT_SIZE*depth > MAX_INDENT)
    {
    depth = MAX_INDENT/INDENT_SIZE;
    }
  static const char spaces[MAX_INDENT+1] = "                        ";
  const char *indent = spaces + (MAX_INDENT - INDENT_SIZE*depth);

  for (unsigned int vi = 0; vi < vn; vi++)
    {
    v = vp[vi];
    unsigned int vl = v.GetVL();
    std::string s;
    if (v.GetVR() == vtkDICOMVR::UN ||
        v.GetVR() == vtkDICOMVR::SQ)
      {
      // sequences are printed later
      s = (vl > 0 ? "..." : "");
      }
    else if (v.GetVR() == vtkDICOMVR::LT ||
             v.GetVR() == vtkDICOMVR::ST ||
             v.GetVR() == vtkDICOMVR::UT)
      {
      // replace breaks with "\\", cap length to MAX_LENGTH
      const char *cp = v.GetCharData();
      unsigned int j = 0;
      while (j < vl && cp[j] != '\0')
        {
        unsigned int k = j;
        unsigned int m = j;
        for (; j < vl && cp[j] != '\0'; j++)
          {
          m = j;
          if (cp[j] == '\r' || cp[j] == '\n' || cp[j] == '\f')
            {
            do { j++; }
            while (j < vl && (cp[j] == '\r' || cp[j] == '\n' || cp[j] == '\f'));
            break;
            }
          m++;
          }
        if (j == vl)
          {
          while (m > 0 && cp[m-1] == ' ') { m--; }
          }
        if (k != 0)
          {
          s.append("\\\\");
          }
        s.append(&cp[k], m-k);
        if (s.size() > MAX_LENGTH)
          {
          s.resize(MAX_LENGTH-4);
          s.append("...");
          break;
          }
        }
      }
    else
      {
      // print any other VR via conversion to string
      unsigned int n = v.GetNumberOfValues();
      size_t pos = 0;
      for (unsigned int i = 0; i < n; i++)
        {
        v.AppendValueToUTF8String(s, i);
        if (i < n - 1)
          {
          s.append("\\");
          }
        if (s.size() > MAX_LENGTH-4)
          {
          s.resize(pos);
          s.append("...");
          break;
          }
        pos = s.size();
        }
      }

    if (vi == 0)
      {
      printf("%s(%04X,%04X) %s \"%s\" :", indent, g, e, vr.GetText(), name);
      }
    if (vn > 1)
      {
      printf("%s%s  %4.4u",
        (vi == 0 ? " (multiple values)\n" : ""), indent, vi + 1);
      }
    if (v.GetVR() == vtkDICOMVR::SQ)
      {
      unsigned int m = v.GetNumberOfValues();
      const vtkDICOMItem *items = v.GetSequenceData();
      printf(" (%u %s%s)\n",
        m, (m == 1 ? "item" : "items"),
       (v.GetVL() == 0xffffffffu ? ", delimited" : ""));
      for (unsigned int j = 0; j < m; j++)
        {
        printf("%s%s---- SQ Item %04u at offset %u ----\n",
          indent, spaces+(MAX_INDENT - INDENT_SIZE), j+1,
          items[j].GetByteOffset());
        vtkDICOMDataElementIterator siter = items[j].Begin();
        vtkDICOMDataElementIterator siterEnd = items[j].End();

        for (; siter != siterEnd; ++siter)
          {
          printElement(meta, &items[j], siter, depth+1);
          }
        }
      }
    else if (v.GetVL() == 0xffffffffu)
      {
      printf(" [%s] (delimited)\n", s.c_str());
      }
    else
      {
      printf(" [%s] (%u bytes)\n", s.c_str(), v.GetVL());
      }
    }
}

// This program will dump all the metadata in the given file
int main(int argc, char *argv[])
{
  int rval = 0;

  // for the optional query file
  const char *qfile = 0;

  if (argc < 2)
    {
    printUsage(stdout, fileBasename(argv[0]));
    return rval;
    }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
    printHelp(stdout, fileBasename(argv[0]));
    return rval;
    }
  else if (argc == 2 && strcmp(argv[1], "--version") == 0)
    {
    printVersion(stdout, fileBasename(argv[0]));
    return rval;
    }

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();

  for (int argi = 1; argi < argc; argi++)
    {
    const char *arg = argv[argi];
    if (strcmp(arg, "-q") == 0 || strcmp(arg, "-o") == 0)
      {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
        {
        fprintf(stderr, "%s must be followed by a file.\n\n", arg);
        printUsage(stderr, fileBasename(argv[0]));
        return 1;
        }

      if (arg[1] == 'q')
        {
        qfile = argv[++argi];
        }
      else if (arg[1] == 'o')
        {
        fprintf(stderr, "unrecognized option %s.\n\n", arg);
        return 1;
        }
      }
    else if (arg[0] == '-')
      {
      fprintf(stderr, "unrecognized option %s.\n\n", arg);
      printUsage(stderr, fileBasename(argv[0]));
      return 1;
      }
    else
      {
      files->InsertNextValue(arg);
      }
    }

  // read the query file, create a query
  vtkDICOMMetaData *query = 0;
  if (qfile)
    {
    vtkDICOMItem qitem;
    if (!dicomcli_readquery(qfile, &qitem))
      {
      fprintf(stderr, "Can't open query file %s\n\n", qfile);
      return 1;
      }
    vtkDICOMDataElementIterator iter = qitem.Begin();
    vtkDICOMDataElementIterator iterEnd = qitem.End();
    query = vtkDICOMMetaData::New();
    while (iter != iterEnd)
      {
      query->SetAttributeValue(iter->GetTag(), iter->GetValue());
      ++iter;
      }
    }

  // sort the files by study and series
  vtkSmartPointer<vtkDICOMSorter> sorter =
    vtkSmartPointer<vtkDICOMSorter>::New();
  sorter->RequirePixelDataOff();
  sorter->SetInputFileNames(files);
  sorter->Update();

  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();
  if (query)
    {
    parser->SetQuery(query);
    }

  vtkSmartPointer<vtkDICOMMetaData> data =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  parser->SetMetaData(data);

#if defined(_WIN32)
  // Temporarily switch the console to utf-8
  UINT codePage = GetConsoleOutputCP();
  SetConsoleOutputCP(65001);
#endif

  int m = sorter->GetNumberOfStudies();
  for (int j = 0; j < m; j++)
    {
    int k = sorter->GetFirstSeriesInStudy(j);
    int n = sorter->GetNumberOfSeriesInStudy(j);
    n += k;
    for (; k < n; k++)
      {
      vtkStringArray *a = sorter->GetFileNamesForSeries(k);
      vtkIdType l = a->GetNumberOfValues();
      std::string fname = a->GetValue(0);
      printf("=========== %s =========\n", fileBasename(fname.c_str()));

      data->Clear();
      data->SetNumberOfInstances(static_cast<int>(l));

      for (vtkIdType i = 0; i < l; i++)
        {
        fname = a->GetValue(i);
        parser->SetIndex(i);
        parser->SetFileName(fname.c_str());
        parser->Update();
        }

      vtkDICOMDataElementIterator iter = data->Begin();
      vtkDICOMDataElementIterator iterEnd = data->End();

      for (; iter != iterEnd; ++iter)
        {
        printElement(data, 0, iter, 0);
        }
      }
    }

#if defined(_WIN32)
  // Restore the console code page
  SetConsoleOutputCP(codePage);
#endif

  if (query)
    {
    query->Delete();
    }

  return rval;
}
