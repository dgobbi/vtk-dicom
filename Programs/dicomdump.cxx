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

      std::string s;
      if (v.GetVR() == vtkDICOMVR::UN ||
          v.GetVR() == vtkDICOMVR::SQ ||
          v.GetVR() == vtkDICOMVR::LT ||
          v.GetVR() == vtkDICOMVR::ST ||
          v.GetVR() == vtkDICOMVR::UT)
        {
        s = "...";
        }
      else
        {
        unsigned int n = v.GetNumberOfValues();
        for (unsigned int i = 0; i < n; i++)
          {
          size_t pos = 0;
          v.AppendValueToString(s, i);
          if (i < n - 1)
            {
            s.append("\\");
            }
          if (s.size() > 70)
            {
            s.resize(pos);
            s.append("...");
            break;
            }
          pos = s.size();
          }
        }

      printf("(%04X,%04X) %s \"%s\" %u : [%s]\n",
        g, e, vr, name, vl, s.c_str());
      }
    }

  return rval;
}
