/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMDirectory.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMDataElement.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMMetaData.h"

// from dicomcli
#include "readquery.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

// print the version
void dicomfind_version(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2014, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void dicomfind_usage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s -q <query.txt> -o <data.csv> <directory>\n\n", cp);
  fprintf(file, "options:\n"
    "  -q <query.txt>  Provide a file to describe the find query.\n"
    "  -o <data.csv>   Provide a file for the query results.\n"
    "  --help          Print a brief help message.\n"
    "  --version       Print the software version.\n");
}

// print the help
void dicomfind_help(FILE *file, const char *cp)
{
  dicomfind_usage(file, cp);
  fprintf(file, "\n"
    "Dump the metadata from a DICOM series as text.\n");
}

// remove path portion of filename
const char *dicomfind_basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

typedef vtkDICOMVR VR;

// Write the header
void dicomfind_writeheader(
  const vtkDICOMItem& query, const QueryTagList *ql, std::ostream& os)
{
  // print human-readable names for each tag
  for (size_t i = 0; i < ql->size(); i++)
    {
    if (i != 0)
      {
      os << ",";
      }
    const vtkDICOMItem *pitem = &query;
    vtkDICOMTagPath tagPath = ql->at(i);
    for (;;)
      {
      vtkDICOMTag tag = tagPath.GetHead();
      vtkDICOMDictEntry e = pitem->FindDictEntry(tag);
      if (e.IsValid())
        {
        os << e.GetName();
        }
      if (!tagPath.HasTail())
        {
        break;
        }
      pitem = pitem->GetAttributeValue(tag).GetSequenceData();
      tagPath = tagPath.GetTail();
      os << "\\";
      }
    }
  os << "\r\n";

  // print the private creator
  for (size_t i = 0; i < ql->size(); i++)
    {
    if (i != 0)
      {
      os << ",";
      }
    const vtkDICOMItem *pitem = &query;
    vtkDICOMTagPath tagPath = ql->at(i);
    for (;;)
      {
      vtkDICOMTag tag = tagPath.GetHead();
      std::string creator = "DICOM";
      if ((tag.GetGroup() & 0x0001) == 1)
        {
        vtkDICOMTag ctag(tag.GetGroup(), tag.GetElement() >> 8);
        creator = pitem->GetAttributeValue(ctag).AsString();
        }
      os << creator.c_str();
      if (!tagPath.HasTail())
        {
        break;
        }
      pitem = pitem->GetAttributeValue(tag).GetSequenceData();
      tagPath = tagPath.GetTail();
      os << "\\";
      }
    }
  os << "\r\n";

  // print the tag as a hexadecimal number
  for (size_t i = 0; i < ql->size(); i++)
    {
    if (i != 0)
      {
      os << ",";
      }
    const vtkDICOMItem *pitem = &query;
    vtkDICOMTagPath tagPath = ql->at(i);
    for (;;)
      {
      vtkDICOMTag tag = tagPath.GetHead();
      unsigned short g = tag.GetGroup();
      unsigned short e = tag.GetElement();
      std::string creator;
      if ((tag.GetGroup() & 0x0001) == 1)
        {
        vtkDICOMTag ctag(tag.GetGroup(), tag.GetElement() >> 8);
        creator = pitem->GetAttributeValue(ctag).AsString();
        if (creator.length() > 0)
          {
          // remove the creator portion of the element number
          e &= 0x00FF;
          }
        }
      char tagtext[16];
      sprintf(tagtext, "%04X%04X", g, e);
      os << tagtext;
      if (!tagPath.HasTail())
        {
        break;
        }
      pitem = pitem->GetAttributeValue(tag).GetSequenceData();
      tagPath = tagPath.GetTail();
      os << "\\";
      }
    }
  os << "\r\n";

  // print the VR
  for (size_t i = 0; i < ql->size(); i++)
    {
    if (i != 0)
      {
      os << ",";
      }
    const vtkDICOMItem *pitem = &query;
    vtkDICOMTagPath tagPath = ql->at(i);
    vtkDICOMValue v = query.GetAttributeValue(tagPath);
    if (v.IsValid())
      {
      os << v.GetVR().GetText();
      }
    else
      {
      for (;;)
        {
        vtkDICOMTag tag = tagPath.GetHead();
        if (!tagPath.HasTail())
          {
          vtkDICOMDictEntry e = pitem->FindDictEntry(tag);
          if (e.IsValid())
            {
            os << e.GetVR().GetText();
            }
          break;
          }
        pitem = pitem->GetAttributeValue(tag).GetSequenceData();
        tagPath = tagPath.GetTail();
        }
      }
    }
  os << "\r\n";
}

// Convert date to format YYYY-MM-DD HH:MM:SS
std::string dicomfind_date(const std::string& dt, vtkDICOMVR vr)
{
  if (vr == VR::TM && dt.length() >= 6)
    {
    return dt.substr(0,2) + ":" + dt.substr(2,2) + ":" + dt.substr(4,2);
    }
  else if (vr == VR::DA && dt.length() >= 8)
    {
    return dt.substr(0,4) + "-" + dt.substr(4,2) + "-" + dt.substr(6,2);
    }
  else if (vr == VR::DT && dt.length() >= 14)
    {
    return dt.substr(0,4) + "-" + dt.substr(4,2) + "-" + dt.substr(6,2) + " " +
           dt.substr(8,2) + ":" + dt.substr(10,2) + ":" + dt.substr(12,2);
    }

  return "";
}

// Quote a string by doubling any double-quotes that are found
// (this follows RFC 4180)
std::string dicomfind_quote(const std::string& s)
{
  size_t i = 0;
  std::string r;

  for (;;)
    {
    size_t j = s.find('\"', i);
    if (j < s.length())
      {
      r += s.substr(i, j-i+1);
      r += "\"";
      i = j+1;
      }
    else
      {
      r += s.substr(i);
      break;
      }
    }

  return r;
}

// Write out the results
void dicomfind_write(vtkDICOMDirectory *finder,
  const vtkDICOMItem& query, const QueryTagList *ql, std::ostream& os)
{
  for (int j = 0; j < finder->GetNumberOfStudies(); j++)
    {
    int k0 = finder->GetFirstSeriesForStudy(j);
    int k1 = finder->GetLastSeriesForStudy(j);
    for (int k = k0; k <= k1; k++)
      {
      vtkStringArray *a = finder->GetFileNamesForSeries(k);

      vtkSmartPointer<vtkDICOMMetaData> meta =
        vtkSmartPointer<vtkDICOMMetaData>::New();
      vtkSmartPointer<vtkDICOMParser> parser =
        vtkSmartPointer<vtkDICOMParser>::New();

      parser->SetFileName(a->GetValue(0));
      parser->SetMetaData(meta);
      parser->Update();

      vtkDICOMItem result = meta->Query(query);

      vtkDICOMDataElementIterator iter;

      // print the value of each tag
      for (size_t i = 0; i < ql->size(); i++)
        {
        if (i != 0)
          {
          os << ",";
          }

        const vtkDICOMItem *qitem = &query;
        const vtkDICOMItem *mitem = 0;
        const vtkDICOMValue *vp = 0;
        vtkDICOMTagPath tagPath = ql->at(i);
        for (;;)
          {
          vtkDICOMTag tag = tagPath.GetHead();
          std::string creator;
          if ((tag.GetGroup() & 0x0001) == 1)
            {
            vtkDICOMTag ctag(tag.GetGroup(), tag.GetElement() >> 8);
            creator = qitem->GetAttributeValue(ctag).AsString();
            if (mitem)
              {
              tag = meta->ResolvePrivateTag(tag, creator);
              }
            else
              {
              tag = mitem->ResolvePrivateTag(tag, creator);
              }
            }
          if (mitem)
            {
            vp = &mitem->GetAttributeValue(tag);
            }
          else
            {
            vp = &meta->GetAttributeValue(tag);
            }
          if (vp == 0 || !tagPath.HasTail())
            {
            break;
            }
          qitem = qitem->GetAttributeValue(
            tagPath.GetHead()).GetSequenceData();
          tagPath = tagPath.GetTail();
          mitem = vp->GetSequenceData();
          if (mitem == 0 || vp->GetNumberOfValues() == 0)
            {
            break;
            }
          }

        if (vp != 0)
          {
          const vtkDICOMValue& v = *vp;
          if (v.GetNumberOfValues() == 1 &&
              (v.GetVR() == VR::SS ||
               v.GetVR() == VR::US ||
               v.GetVR() == VR::SL ||
               v.GetVR() == VR::UL ||
               v.GetVR() == VR::FL ||
               v.GetVR() == VR::FD))
            {
            os << v;
            }
          else if (v.GetVR() == VR::DA ||
                   v.GetVR() == VR::TM ||
                   v.GetVR() == VR::DT)
            {
            os << "\"" << dicomfind_date(v.AsString(), v.GetVR()) << "\"";
            }
          else if (v.GetVR() == VR::SQ)
            {
            // how should a sequence be printed out to the csv file?
            }
          else if (v.GetVL() != 0 && v.GetVL() != 0xFFFFFFFF)
            {
            os << "\"" << dicomfind_quote(v.AsUTF8String()) << "\"";
            }
          }
        }
      os << "\r\n";
      }
    }
}

// This program will dump all the metadata in the given file
int main(int argc, char *argv[])
{
  int rval = 0;

  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();
  const char *ofile = 0;
  const char *qfile = 0;

  if (argc < 2)
    {
    dicomfind_usage(stdout, dicomfind_basename(argv[0]));
    return rval;
    }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
    dicomfind_help(stdout, dicomfind_basename(argv[0]));
    return rval;
    }
  else if (argc == 2 && strcmp(argv[1], "--version") == 0)
    {
    dicomfind_version(stdout, dicomfind_basename(argv[0]));
    return rval;
    }

  for (int argi = 1; argi < argc; argi++)
    {
    const char *arg = argv[argi];
    if (strcmp(arg, "-q") == 0 || strcmp(arg, "-o") == 0)
      {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
        {
        fprintf(stderr, "%s must be followed by a file.\n\n", arg);
        dicomfind_usage(stderr, dicomfind_basename(argv[0]));
        return 1;
        }

      if (arg[1] == 'q')
        {
        qfile = argv[++argi];
        }
      else if (arg[1] == 'o')
        {
        ofile = argv[++argi];
        }
      }
    else if (arg[0] == '-')
      {
      fprintf(stderr, "unrecognized option %s.\n\n", arg);
      dicomfind_usage(stderr, dicomfind_basename(argv[0]));
      return 1;
      }
    else
      {
      a->InsertNextValue(arg);
      }
    }

  if (qfile == 0)
    {
    fprintf(stderr, "No query file.\n\n");
    dicomfind_usage(stderr, dicomfind_basename(argv[0]));
    return 1;
    }

  std::ostream *osp = &std::cout;
  std::ofstream ofs;

  if (ofile)
    {
    ofs.open(ofile,
             std::ofstream::out |
             std::ofstream::binary |
             std::ofstream::trunc);

    if (ofs.bad())
      {
      fprintf(stderr, "Unable to open output file %s.\n", ofile);
      return 1;
      }
    osp = &ofs;
    }

  // read the query file, create a query
  QueryTagList qtlist;
  vtkDICOMItem query = dicomcli_readquery(qfile, &qtlist);

  // Write the header
  dicomfind_writeheader(query, &qtlist, *osp);
  osp->flush();

  // Write data for every input directory
  for (vtkIdType i = 0; i < a->GetNumberOfTuples(); i++)
    {
    vtkSmartPointer<vtkDICOMDirectory> finder =
      vtkSmartPointer<vtkDICOMDirectory>::New();
    finder->SetDirectoryName(a->GetValue(i));
    finder->SetScanDepth(8);
    finder->SetFindQuery(query);
    finder->Update();

    dicomfind_write(finder, query, &qtlist, *osp);
    osp->flush();
    }

  return rval;
}
