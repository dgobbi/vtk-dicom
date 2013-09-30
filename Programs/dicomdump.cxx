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
#include "vtkDICOMItem.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INDENT 24
#define INDENT_SIZE 2
#define MAX_LENGTH 120

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
    name = "Group Length";
    }

  // allow multiple values (i.e. for each image in series)
  vtkDICOMValue v = iter->GetValue();
  unsigned int vn = v.GetNumberOfValues();
  vtkDICOMValue *vp = v.GetMultiplexData();
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
      for (unsigned int i = 0; i < n; i++)
        {
        size_t pos = 0;
        v.AppendValueToString(s, i);
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
        printf("%s%s---- SQ Item %04u ----\n",
          indent, spaces+(MAX_INDENT - INDENT_SIZE), j+1);
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

  return rval;
}
