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
#include "vtkDICOMMetaData.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMItem.h"

#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INDENT 24
#define INDENT_SIZE 2
#define MAX_LENGTH 78

// remove path portion of filename
const char *basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// Print out one data element
void printElement(const vtkDICOMDataElementIterator &iter, int depth)
{
  vtkDICOMTag tag = iter->GetTag();
  int g = tag.GetGroup();
  int e = tag.GetElement();
  vtkDICOMValue v = iter->GetValue();
  unsigned int vl = v.GetVL();
  const char *vr = v.GetVR().GetText();
  const char *name = "";
  vtkDICOMDictEntry d = vtkDICOMDictionary::FindDictEntry(tag);
  if (d.IsValid())
    {
    name = d.GetName();
    }

  // make an indentation string
  if (INDENT_SIZE*depth > MAX_INDENT)
    {
    depth = MAX_INDENT/INDENT_SIZE;
    }
  static const char spaces[MAX_INDENT+1] = "                        ";
  const char *indent = spaces + (MAX_INDENT - INDENT_SIZE*depth);

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

  printf("%s(%04X,%04X) %s \"%s\" %u : [%s]\n",
    indent, g, e, vr, name, vl, s.c_str());

  if (v.GetVR() == vtkDICOMVR::SQ)
    {
    unsigned int m = v.GetNumberOfValues();
    const vtkDICOMItem *items = v.GetSequenceData();
    for (unsigned int j = 0; j < m; j++)
      {
      printf("%s%s---- SQ Item %04u ----\n",
        indent, spaces+(MAX_INDENT - INDENT_SIZE), j+1);
      vtkDICOMDataElementIterator siter =
        items[j].GetDataElementIterator();
      vtkDICOMDataElementIterator siterEnd =
        items[j].GetDataElementIteratorEnd();

      for (; siter != siterEnd; ++siter)
        {
        printElement(siter, depth+1);
        }
      }
    }
}

// This program will dump all the metadata in the given file
int main(int argc, char *argv[])
{
  int rval = 0;

  if (argc < 2)
    {
    printf("usage: %s file1.dcm [file2.dcm ...]\n", basename(argv[0]));
    return rval;
    }

  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  for (int argi = 1; argi < argc; argi++)
    {
    const char *filename = argv[argi];
    printf("=========== %s =========\n", basename(filename));

    vtkSmartPointer<vtkDICOMMetaData> data =
      vtkSmartPointer<vtkDICOMMetaData>::New();

    parser->SetFileName(filename);
    parser->SetMetaData(data);

    parser->Update();

    vtkDICOMDataElementIterator iter =
      data->GetDataElementIterator();
    vtkDICOMDataElementIterator iterEnd =
      data->GetDataElementIteratorEnd();

    for (; iter != iterEnd; ++iter)
      {
      printElement(iter, 0);
      }
    }

  return rval;
}
