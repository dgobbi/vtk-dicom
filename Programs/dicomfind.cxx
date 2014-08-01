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

// A class to identify a tag and possible a creator
class QueryTag
{
public:
  QueryTag() : m_tag(), m_creator() {}
  QueryTag(const vtkDICOMTag& t) : m_tag(t), m_creator() {}
  QueryTag(const vtkDICOMTag& t, const std::string& c)
    : m_tag(t), m_creator(c) {}

  vtkDICOMTag tag() const { return m_tag; }
  const std::string& creator() const { return m_creator; }

private:
  vtkDICOMTag m_tag;
  std::string m_creator;
};

typedef std::vector<QueryTag> QueryTagList;

// Read a query file
vtkDICOMItem dicomfind_query(const char *fname, QueryTagList *ql)
{
  ifstream f(fname);
  if (!f.good())
    {
    fprintf(stderr, "Can't open query file %s\n\n", fname);
    exit(1);
    }

  // Each query line is either:
  // # a comment
  // GGGGEEEE         # a tag to be returned
  // GGGGEEEE=PATTERN # a pattern that must match
  // GGGGEEEE:VR=PATTERN # search pattern with explicit VR
  // [PRIVATE_CREATOR]GGGGEEEE # private tag with creator name

  vtkDICOMItem query;

  int lineNumber = 0;
  while (f.good())
    {
    std::string line;
    std::getline(f, line);
    const char *cp = line.c_str();
    size_t n = line.size();
    unsigned int key = 0;
    lineNumber++;

    // strip leading whitespace
    size_t s = 0;
    while (s < n && isspace(cp[s]))
      {
      s++;
      }

    // skip line if it is a comment
    if (s == n || cp[s] == '#')
      {
      continue;
      }

    // check for private creator in square brackets
    size_t creatorStart = s;
    size_t creatorEnd = s;
    if (cp[s] == '[')
      {
      s++;
      creatorStart = s;
      while (s < n && cp[s] != ']')
        {
        s++;
        }
      if (s == n)
        {
        fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
        fprintf(stderr, "Block is missing the final \"]\".\n");
        continue;
        }
      creatorEnd = s;
      s++;
      }

    std::string creator(&cp[creatorStart], creatorEnd - creatorStart);

    // read the DICOM tag
    size_t tagStart = s;
    while (s < n && isalnum(cp[s]))
      {
      s++;
      }
    size_t tagEnd = s;
    if (tagEnd - tagStart == 8)
      {
      char *cpe = const_cast<char *>(&cp[tagStart]);
      key = strtoul(&cp[tagStart], &cpe, 16);
      if (cpe - const_cast<char *>(&cp[tagStart]) != 8)
        {
        key = 0;
        }
      }

    vtkDICOMTag tag(key >> 16, key & 0xFFFF);

    // add the tag to the list
    ql->push_back(QueryTag(tag, creator));

    // if creator, then resolve the tag now
    if (creator.length() > 0)
      {
      tag = query.ResolvePrivateTagForWriting(tag, creator);
      }

    // read the DICOM vr
    vtkDICOMVR vr;

    size_t vrStart = s;
    size_t vrEnd = s;
    if (s < n && cp[s] == ':')
      {
      s++;
      vrStart = s;
      vrEnd = s;
      if (n - s >= 2)
        {
        s += 2;
        vrEnd = s;
        vr = vtkDICOMVR(&cp[vrStart]);
        if (!vr.IsValid() || vr == VR::OX || vr == VR::XS || vr == VR::UN)
          {
          int m = static_cast<int>(vrEnd - tagStart);
          m = (m > 40 ? 40 : m);
          fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
          fprintf(stderr, "Unrecognized DICOM VR \"%*.*s\"\n",
             m, m, &cp[tagStart]);
          }
        }
      }

    // validate the tag and the vr against the dictionary
    vtkDICOMVR dictvr = query.FindDictVR(tag);
    if (!vr.IsValid())
      {
      vr = dictvr;
      }
    else if (dictvr.IsValid() && dictvr != VR::UN)
      {
      if (vr != dictvr &&
          !(((dictvr == VR::OX && (vr == VR::OW || vr == VR::OB))) ||
            ((dictvr == VR::XS && (vr == VR::SS || vr == VR::US)))))
        {
        int m = static_cast<int>(vrEnd - tagStart);
        m = (m > 40 ? 40 : m);
        fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
        fprintf(stderr, "VR of \"%*.*s\" doesn't match dictionary VR of %s\n",
           m, m, &cp[tagStart], dictvr.GetText());
        }
      }

    if (!vr.IsValid() || vr == VR::UN)
      {
      int m = static_cast<int>(tagEnd - tagStart);
      m = (m > 40 ? 40 : m);
      fprintf(stderr, "Error %s line %d:\n", fname, lineNumber);
      fprintf(stderr, "Unrecognized DICOM tag \"%*.*s\"\n",
              m, m, &cp[tagStart]);
      continue;
      }

    // check for a value or pattern following "="
    size_t valueStart = s;
    size_t valueEnd = s;
    bool valueContainsQuotes = false;
    if (s < n && cp[s] == '=')
      {
      s++;
      valueStart = s;
      valueEnd = s;
      if (s < n && cp[s] == '\"')
        {
        char delim = cp[s++];
        valueStart = s;
        while (s < n)
          {
          if (cp[s] == delim)
            {
            // a repeated quote becomes a literal quote
            if (s+1 < n && cp[s+1] == delim)
              {
              valueContainsQuotes = true;
              s++;
              }
            else
              {
              break;
              }
            }
          s++;
          }
        valueEnd = s;
        if (s < n)
          {
          s++;
          }
        }
      else
        {
        while (s < n && !isspace(cp[s]))
          {
          s++;
          }
        valueEnd = s;
        }
      }

    // add the tag and value to the query data set
    if (valueStart == valueEnd)
      {
      // empty value (always matches, always retrieved)
      query.SetAttributeValue(tag, vtkDICOMValue(vr));
      }
    else if (valueContainsQuotes)
      {
      // convert "" to "
      std::string sval;
      for (size_t t = valueStart; t < valueEnd; t++)
        {
        sval.push_back(cp[t]);
        if (cp[t] == '\"' && t+1 < valueEnd && cp[t+1] == '\"')
          {
          t++;
          }
        }
      query.SetAttributeValue(tag, vtkDICOMValue(vr, sval));
      }
    else
      {
      query.SetAttributeValue(tag,
        vtkDICOMValue(vr, &cp[valueStart], valueEnd - valueStart));
      }
    }

  return query;
}

// Write the header
void dicomfind_writeheader(
  const vtkDICOMItem& query, const QueryTagList *ql, std::ostream& os)
{
  // print human-readable names for each tag
  for (size_t i = 0; i < ql->size(); i++)
    {
    const char *name = "";
    vtkDICOMTag tag = ql->at(i).tag();

    vtkDICOMDictEntry e = query.FindDictEntry(tag);
    if (e.IsValid())
      {
      name = e.GetName();
      }
    if (i != 0)
      {
      os << ",";
      }
    os << name;
    }
  os << "\r\n";

  // print the private creator
  for (size_t i = 0; i < ql->size(); i++)
    {
    vtkDICOMTag tag = ql->at(i).tag();

    std::string creator = "DICOM";

    if ((tag.GetGroup() & 0x0001) == 1)
      {
      creator = ql->at(i).creator();
      }

    if (i != 0)
      {
      os << ",";
      }
    os << creator.c_str();
    }
  os << "\r\n";

  // print the tag as a hexadecimal number
  for (size_t i = 0; i < ql->size(); i++)
    {
    vtkDICOMTag tag = ql->at(i).tag();

    char tagtext[16];
    sprintf(tagtext, "%04X%04X", tag.GetGroup(), tag.GetElement());
    if (i != 0)
      {
      os << ",";
      }
    os << tagtext;
    }
  os << "\r\n";

  // print the VR
  for (size_t i = 0; i < ql->size(); i++)
    {
    vtkDICOMTag tag = ql->at(i).tag();

    vtkDICOMDictEntry e = query.FindDictEntry(tag);
    const char *name = "";
    if (e.IsValid())
      {
      name = e.GetVR().GetText();
      }
    if (i != 0)
      {
      os << ",";
      }
    os << name;
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
        vtkDICOMTag tag = ql->at(i).tag();
        std::string creator = ql->at(i).creator();

        // if creator, then resolve the tag now
        if (creator.length() > 0)
          {
          tag = meta->ResolvePrivateTagForWriting(tag, creator);
          }

        const vtkDICOMValue& v = meta->GetAttributeValue(tag);
        if (i != 0)
          {
          os << ",";
          }
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
  vtkDICOMItem query = dicomfind_query(qfile, &qtlist);

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
