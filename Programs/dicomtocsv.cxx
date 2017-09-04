/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMConfig.h"
#include "vtkDICOMDirectory.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMItem.h"
#include "vtkDICOMDataElement.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMMetaDataAdapter.h"
#include "vtkDICOMFile.h"

// from dicomcli
#include "vtkConsoleOutputWindow.h"
#include "mainmacro.h"
#include "readquery.h"
#include "progress.h"

#include <vtkCommand.h>
#include <vtkTimerLog.h>
#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <limits>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

// print the version
void dicomtocsv_version(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2017, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void dicomtocsv_usage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s [options] <directory>\n\n", cp);
  fprintf(file, "options:\n"
    "  -k tag=value      Provide a key to be queried and matched.\n"
    "  -q <query.txt>    Provide a file to describe the find query.\n"
    "  -u <uids.txt>     Provide a file that contains a list of UIDs.\n"
    "  -o <data.csv>     Provide a file for the query results.\n"
    "  --first-nonzero   Search series for first nonzero value of each key.\n"
    "  --directory-only  Use directory scan only, do not re-scan files.\n"
    "  --ignore-dicomdir Ignore the DICOMDIR file even if it is present.\n"
    "  --charset <cs>    Charset to use if SpecificCharacterSet is missing.\n"
    "  --images-only     Only list files that have PixelData or equivalent.\n"
    "  --noheader        Do not print the csv header.\n"
    "  --study           Print one row for each study.\n"
    "  --series          Print one row for each series (default).\n"
    "  --image           Print one row for each image.\n"
    "  --silent          Do not report any progress information.\n"
    "  --help            Print a brief help message.\n"
    "  --version         Print the software version.\n");
}

// print the help
void dicomtocsv_help(FILE *file, const char *cp)
{
  dicomtocsv_usage(file, cp);
  fprintf(file, "\n"
    "Dump selected metadata from a DICOM directory to a csv file.\n"
    "For each attribute to be extracted, the tag can be given with \"-k\"\n"
    "(the \"-k\" option can be repeated as many times as needed).  Tags can\n"
    "given in hexadecimal GGGG,EEEE format, or in text format as specified\n"
    "in the DICOM dictionary.  Alternately, the tags can be listed in a\n"
    "query file given with the \"-q\" option (one tag per line).\n"
    "Attributes nested within sequences can be specified by giving a tag\n"
    "path e.g. \"-k Tag1/Tag2/Tag3\".  Either a forward slash or a backslash\n"
    "can be used to separate the components of the path.  Private tags\n"
    "should be preceded by the private dictionary name in square brackets.\n"
    "\n"
    "If the same tag is given more than once with \"-k\" (or if the tag is\n"
    "listed multiple times in the query file, or appears in both the query\n"
    "file and as a \"-k\" option), then its first appearance will set the\n"
    "column number that it appears in.  Also, with regards to the search,\n"
    "the value specified in the final appearance of the tag as an option\n"
    "will be the value used for the search.\n"
    "\n"
    "If no attributes are specified with either \"-k\" or \"-q\", then a\n"
    "default set of query attributes will be used.\n\n");
}

// remove path portion of filename
const char *dicomtocsv_basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

typedef vtkDICOMVR VR;

// Observer for DICOM errors
class ErrorObserver : public vtkCommand
{
public:
  static ErrorObserver *New() { return new ErrorObserver(); }
  vtkTypeMacro(ErrorObserver,vtkCommand);
#ifdef VTK_OVERRIDE
  void Execute(
    vtkObject *caller, unsigned long eventId, void *callData) VTK_OVERRIDE;
#else
  void Execute(vtkObject *caller, unsigned long eventId, void *callData);
#endif
  void SetMetaData(vtkDICOMMetaData *meta) { this->MetaData = meta; }
protected:
  ErrorObserver() : MetaData(0) {}
  ErrorObserver(const ErrorObserver& c) : vtkCommand(c) {}
  void operator=(const ErrorObserver&) {}
  vtkDICOMMetaData *MetaData;
};

void ErrorObserver::Execute(vtkObject *o, unsigned long e, void *data)
{
  if (e == vtkCommand::ErrorEvent)
  {
    vtkDICOMParser *parser = vtkDICOMParser::SafeDownCast(o);
    if (parser)
    {
      dicomcli_error_helper(this->MetaData, parser->GetIndex());
    }
    if (data)
    {
      fprintf(stderr, "%s", static_cast<char *>(data));
    }
  }
}

// Create a default query for --image
void dicomtocsv_image_default(vtkDICOMItem *query, QueryTagList *ql)
{
  // these are the attributes that must be part of the query
  static const DC::EnumType defaultElements[] = {
    // patient-level information
    DC::PatientName,          // 2
    DC::PatientID,            // 1
    DC::PatientBirthDate,     // 3
    DC::PatientSex,           // 3
    // study-level information
    DC::StudyDate,            // 1
    DC::StudyTime,            // 1
    DC::StudyID,              // 1
    DC::AccessionNumber,      // 2
    DC::StudyDescription,     // 2
    DC::StudyInstanceUID,     // 1
    // series-level information
    DC::Modality,             // 1
    DC::SeriesNumber,         // 1
    DC::SeriesDescription,    // 3
    DC::SeriesInstanceUID,    // 1
    DC::Rows,                 // 3
    DC::Columns,              // 3
    // image-level information
    DC::InstanceNumber,       // 1
    DC::SOPClassUID,          // 1
    DC::SOPInstanceUID,       // 1
    DC::ReferencedFileID,     // special
    // delimiter to mark end of list
    DC::ItemDelimitationItem
  };

  for (const DC::EnumType *tagPtr = defaultElements;
       *tagPtr != DC::ItemDelimitationItem;
       ++tagPtr)
  {
    VR vr = query->FindDictVR(*tagPtr);
    query->Set(*tagPtr, vtkDICOMValue(vr));
    ql->push_back(vtkDICOMTagPath(*tagPtr));
  }
}

// Create a default query for --series
void dicomtocsv_series_default(vtkDICOMItem *query, QueryTagList *ql)
{
  // these are the attributes that must be part of the query
  static const DC::EnumType defaultElements[] = {
    // patient-level information
    DC::PatientName,          // 2
    DC::PatientID,            // 1
    DC::PatientBirthDate,     // 3
    DC::PatientSex,           // 3
    // study-level information
    DC::StudyDate,            // 1
    DC::StudyTime,            // 1
    DC::StudyID,              // 1
    DC::AccessionNumber,      // 2
    DC::StudyDescription,     // 2
    DC::StudyInstanceUID,     // 1
    // series-level information
    DC::Modality,             // 1
    DC::SeriesNumber,         // 1
    DC::SeriesDescription,    // 3
    DC::SeriesInstanceUID,    // 1
    DC::Rows,                 // 3
    DC::Columns,              // 3
    DC::NumberOfReferences,   // special
    // delimiter to mark end of list
    DC::ItemDelimitationItem
  };

  for (const DC::EnumType *tagPtr = defaultElements;
       *tagPtr != DC::ItemDelimitationItem;
       ++tagPtr)
  {
    VR vr = query->FindDictVR(*tagPtr);
    query->Set(*tagPtr, vtkDICOMValue(vr));
    ql->push_back(vtkDICOMTagPath(*tagPtr));
  }
}

// Create a default query for --study
void dicomtocsv_study_default(vtkDICOMItem *query, QueryTagList *ql)
{
  // these are the attributes that must be part of the query
  static const DC::EnumType defaultElements[] = {
    // patient-level information
    DC::PatientName,          // 2
    DC::PatientID,            // 1
    DC::PatientBirthDate,     // 3
    DC::PatientSex,           // 3
    // study-level information
    DC::StudyDate,            // 1
    DC::StudyTime,            // 1
    DC::StudyID,              // 1
    DC::AccessionNumber,      // 2
    DC::StudyDescription,     // 2
    DC::StudyInstanceUID,     // 1
    DC::NumberOfReferences,   // special
    // delimiter to mark end of list
    DC::ItemDelimitationItem
  };

  for (const DC::EnumType *tagPtr = defaultElements;
       *tagPtr != DC::ItemDelimitationItem;
       ++tagPtr)
  {
    VR vr = query->FindDictVR(*tagPtr);
    query->Set(*tagPtr, vtkDICOMValue(vr));
    ql->push_back(vtkDICOMTagPath(*tagPtr));
  }
}

// Write the header for a csv file
void dicomtocsv_writeheader(
  const vtkDICOMItem& query, const QueryTagList *ql, FILE *fp)
{
  // print human-readable names for each tag
  for (size_t i = 0; i < ql->size(); i++)
  {
    if (i != 0)
    {
      fprintf(fp, "%s", ",");
    }
    const vtkDICOMItem *pitem = &query;
    vtkDICOMTagPath tagPath = ql->at(i);
    for (;;)
    {
      vtkDICOMTag tag = tagPath.GetHead();
      vtkDICOMDictEntry e = pitem->FindDictEntry(tag);
      if (e.IsValid())
      {
        const char *name = e.GetName();
        name = ((name && name[0]) ? name : "Unknown");
        fprintf(fp, "%s", name);
      }
      if (!tagPath.HasTail())
      {
        break;
      }
      pitem = pitem->Get(tag).GetSequenceData();
      tagPath = tagPath.GetTail();
      fprintf(fp, "%s", "\\");
    }
  }
  fprintf(fp, "%s", "\r\n");
}

// Convert date to format YYYY-MM-DD HH:MM:SS
std::string dicomtocsv_date(const std::string& dt, vtkDICOMVR vr)
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
std::string dicomtocsv_quote(const std::string& s)
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

// A helper struct for dicomtocsv_write
struct SearchState {
  vtkDICOMTagPath p;
  const vtkDICOMItem *q;
  const vtkDICOMItem *m;
  const vtkDICOMItem *n;
};

// Write out the results in csv format
void dicomtocsv_write(vtkDICOMDirectory *finder,
  const vtkDICOMItem& query, const QueryTagList *ql, FILE *fp,
  int level, bool firstNonZero, bool useDirectoryRecords, vtkCommand *p)
{
  // for keeping track of progress
  vtkIdType count = 0.0;
  vtkIdType total = 0.0;
  if (p)
  {
    for (int k = 0; k < finder->GetNumberOfSeries(); k++)
    {
      total += finder->GetFileNamesForSeries(k)->GetNumberOfValues();
    }
    p->Execute(NULL, vtkCommand::StartEvent, NULL);
  }

  for (int j = 0; j < finder->GetNumberOfStudies(); j++)
  {
    int k0 = finder->GetFirstSeriesForStudy(j);
    int k1 = finder->GetLastSeriesForStudy(j);
    int numberOfFiles = 1;

    if (level < 3 && k1 > k0)
    {
      // if level is "study", only look at one series
      numberOfFiles = 0;
      for (int k = k0; k <= k1; k++)
      {
        vtkStringArray *a = finder->GetFileNamesForSeries(k);
        numberOfFiles += a->GetNumberOfValues();
      }
      k1 = k0;
    }

    for (int k = k0; k <= k1; k++)
    {
      vtkStringArray *a = finder->GetFileNamesForSeries(k);
      if (a->GetNumberOfValues() == 0)
      {
        continue;
      }

      if (level == 3)
      {
        // at series level, this is the number of files
        numberOfFiles = a->GetNumberOfValues();
      }

      vtkSmartPointer<vtkDICOMMetaData> meta;
      if (useDirectoryRecords)
      {
        meta = finder->GetMetaDataForSeries(k);
      }
      else
      {
        meta = vtkSmartPointer<vtkDICOMMetaData>::New();
        if (level >= 4 || firstNonZero)
        {
          // need to parse all files
          meta->SetNumberOfInstances(a->GetNumberOfValues());
        }

        // need to go to the files for the meta data
        vtkSmartPointer<vtkDICOMParser> parser =
          vtkSmartPointer<vtkDICOMParser>::New();

        vtkSmartPointer<ErrorObserver> errorObserver =
          vtkSmartPointer<ErrorObserver>::New();
        errorObserver->SetMetaData(finder->GetMetaDataForSeries(k));
        parser->AddObserver(vtkCommand::ErrorEvent, errorObserver);

        parser->SetQueryItem(query);
        parser->SetMetaData(meta);

        for (int ii = 0; ii < meta->GetNumberOfInstances(); ii++)
        {
          parser->SetIndex(ii);
          parser->SetFileName(a->GetValue(ii));
          parser->Update();
        }
      }

      // this loop is only for the "image" level
      int m = (level >= 4 ? meta->GetNumberOfInstances() : 1);
      for (int jj = 0; jj < m; jj++)
      {
        // print the value of each tag
        for (size_t i = 0; i < ql->size(); i++)
        {
          if (i != 0)
          {
            fprintf(fp, "%s", ",");
          }

          const vtkDICOMValue *vp = 0;
          vtkDICOMTagPath tagPath = ql->at(i);

          // this loop is only needed if firstNonZero is set
          int n = (firstNonZero ? meta->GetNumberOfInstances() : 1);
          n = (level >= 4 ? jj+1 : n);
          for (int ii = jj; ii < n; ii++)
          {
            // Create an adapter, which helps with extracting attributes from
            // the PerFrameFunctionalSequence of enhanced IODs.
            vtkDICOMMetaDataAdapter adapter(meta, ii);

            // Create a stack for searching the whole tree
            std::vector<SearchState> tstack(1);
            SearchState &head = tstack.back();
            head.p = tagPath;
            head.q = &query;
            head.m = 0;
            head.n = head.m + 1;

            while (!tstack.empty())
            {
              SearchState &top = tstack.back();
              if (top.m == top.n)
              {
                tstack.pop_back();
                continue;
              }

              const vtkDICOMTagPath& tpath = top.p;
              const vtkDICOMItem *qitem = top.q;
              const vtkDICOMItem *mitem = top.m++;

              vtkDICOMTag tag = tpath.GetHead();
              std::string creator;
              if ((tag.GetGroup() & 0x0001) == 1)
              {
                vtkDICOMTag ctag(tag.GetGroup(), tag.GetElement() >> 8);
                creator = qitem->Get(ctag).AsString();
                if (mitem)
                {
                  tag = mitem->ResolvePrivateTag(tag, creator);
                }
                else
                {
                  tag = adapter->ResolvePrivateTag(tag, creator);
                }
              }
              const vtkDICOMValue *vptr = 0;
              if (mitem)
              {
                vptr = &mitem->Get(tag);
              }
              else if (tag != DC::NumberOfFrames)
              {
                // vtkDICOMMetaDataAdapter hides NumberOfFrames, so it
                // will never be found if we check the adapter
                vptr = &adapter->Get(tag);
              }
              else
              {
                vptr = &meta->Get(ii, tag);
              }
              if (vptr && !vptr->IsValid())
              {
                vptr = 0;
              }
              // check if we have reached the end of a tag path
              if (!tpath.HasTail())
              {
                if (vp == 0 && vptr != 0)
                {
                  vp = vptr;
                  break;
                }
              }
              else if (vptr != 0)
              {
                // go one level deeper into the query
                qitem = qitem->Get(tpath.GetHead()).GetSequenceData();
                // go one level deeper into the meta data
                mitem = vptr->GetSequenceData();
                if (mitem)
                {
                  tstack.resize(tstack.size()+1);
                  SearchState &b = tstack.back();
                  b.p = tstack[tstack.size()-2].p.GetTail();
                  b.q = qitem;
                  b.m = mitem;
                  b.n = mitem + vptr->GetNumberOfValues();
                  continue;
                }
              }
            }
            // If numerical value is zero, keep going until non-zero because
            // the zero value is of little interest
            if (vp != 0)
            {
              if (!vp->GetVR().HasNumericValue() || vp->AsDouble() != 0.0)
              {
                break;
              }
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
              std::string s = v.AsString();
              fprintf(fp, "%s", s.c_str());
            }
            else if (v.GetVR() == VR::DA ||
                     v.GetVR() == VR::TM ||
                     v.GetVR() == VR::DT)
            {
              std::string s = dicomtocsv_date(v.AsString(), v.GetVR());
              fprintf(fp, "\"%s\"", s.c_str());
            }
            else if (v.GetVR() == VR::SQ)
            {
              // how should a sequence be printed out to the csv file?
            }
            else if (v.GetVL() != 0 && v.GetVL() != 0xFFFFFFFF)
            {
              std::string s;
              size_t nv = v.GetNumberOfValues();
              for (size_t iv = 0; iv < nv; iv++)
              {
                if (iv) { s.push_back('\\'); }
                v.AppendValueToSafeUTF8String(s, iv);
              }
              if (s.find('\"') < s.length())
              {
                s = dicomtocsv_quote(s);
              }
              fprintf(fp, "\"%s\"", s.c_str());
            }
          }
          else if (tagPath.GetHead() == DC::ReferencedFileID &&
                   !tagPath.HasTail())
          {
            // ReferencedFileID (0004,1500) is meant to be used in DICOMDIR,
            // but we hijack it to report the first file in the series.
            std::string s = dicomtocsv_quote(a->GetValue(jj));
            fprintf(fp, "\"%s\"", s.c_str());
          }
          else if (tagPath.GetHead() == DC::NumberOfReferences &&
                   !tagPath.HasTail())
          {
            // NumberOfReferences (0004,1600) is a retired attribute meant
            // to count the number of references to a file, but we hijack
            // it and use it to report the number of files found for the
            // series.
            fprintf(fp, "\"%d\"", numberOfFiles);
          }
        }

        fprintf(fp, "%s", "\r\n");

        // report progress
        if (p)
        {
          count += numberOfFiles;
          double progress = (static_cast<double>(count)/
                             static_cast<double>(total));
          p->Execute(NULL, vtkCommand::ProgressEvent, &progress);
        }
      }
    }
  }

  if (p)
  {
    p->Execute(NULL, vtkCommand::EndEvent, NULL);
  }
}

} // end anonymous namespace

// This program will dump all the metadata in the given file
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

  int rval = 0;
  int scandepth = std::numeric_limits<int>::max();
  QueryTagList qtlist;
  vtkDICOMItem query;
  std::vector<std::string> oplist;
  bool firstNonZero = false;
  bool useDirectoryRecords = false;
  bool ignoreDicomdir = false;
  vtkDICOMCharacterSet charset;
  bool imagesOnly = false;
  bool noHeader = false;
  bool silent = false;
  int level = 3; // default to series level

  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();
  const char *ofile = 0;

  // always query SpecificCharacterSet
  query.Set(DC::SpecificCharacterSet, vtkDICOMValue(VR::CS));

  // always query the functional sequences for advanced files
  query.Set(DC::SharedFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));
  query.Set(DC::PerFrameFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));

  if (argc < 2)
  {
    dicomtocsv_usage(stdout, dicomtocsv_basename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
  {
    dicomtocsv_help(stdout, dicomtocsv_basename(argv[0]));
    return rval;
  }
  else if (argc == 2 && strcmp(argv[1], "--version") == 0)
  {
    dicomtocsv_version(stdout, dicomtocsv_basename(argv[0]));
    return rval;
  }

  for (int argi = 1; argi < argc; argi++)
  {
    const char *arg = argv[argi];
    if (strcmp(arg, "-q") == 0 || strcmp(arg, "-o") == 0)
    {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
      {
        fprintf(stderr, "Error: %s must be followed by a file.\n\n", arg);
        dicomtocsv_usage(stderr, dicomtocsv_basename(argv[0]));
        return 1;
      }

      if (arg[1] == 'q')
      {
        const char *qfile = argv[++argi];
        if (!dicomcli_readquery(qfile, &query, &qtlist))
        {
          fprintf(stderr, "Error: Can't read query file %s\n\n", qfile);
          return 1;
        }
      }
      else if (arg[1] == 'o')
      {
        ofile = argv[++argi];
      }
    }
    else if (strcmp(arg, "-u") == 0)
    {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
      {
        fprintf(stderr, "Error: %s must be followed by a file.\n\n", arg);
        dicomtocsv_usage(stderr, dicomtocsv_basename(argv[0]));
        return 1;
      }
      const char *qfile = argv[++argi];
      if (!dicomcli_readuids(qfile, &query, &qtlist))
      {
        fprintf(stderr, "Error: Can't read uid file %s\n\n", qfile);
        return 1;
      }
    }
    else if (strcmp(arg, "-k") == 0)
    {
      vtkDICOMTag tag;
      ++argi;
      if (argi == argc)
      {
        fprintf(stderr, "Error: %s must be followed by gggg,eeee=value "
                        "where gggg,eeee is a DICOM tag.\n\n", arg);
        return 1;
      }
      if (!dicomcli_readkey(argv[argi], &query, &qtlist))
      {
        return 1;
      }
    }
    else if (strcmp(arg, "--first-nonzero") == 0)
    {
      firstNonZero = true;
    }
    else if (strcmp(arg, "--directory-only") == 0)
    {
      useDirectoryRecords = true;
    }
    else if (strcmp(arg, "--ignore-dicomdir") == 0)
    {
      ignoreDicomdir = true;
    }
    else if (strcmp(arg, "--charset") == 0)
    {
      ++argi;
      if (argi == argc || argv[argi][0] == '-')
      {
        fprintf(stderr, "%s must be followed by a valid character set\n\n",
                arg);
        return 1;
      }
      charset = vtkDICOMCharacterSet(argv[argi]);
      if (charset.GetKey() == vtkDICOMCharacterSet::Unknown)
      {
        fprintf(stderr, "%s %s is not a known character set\n\n",
                arg, argv[argi]);
        return 1;
      }
    }
    else if (strcmp(arg, "--images-only") == 0)
    {
      imagesOnly = true;
    }
    else if (strcmp(arg, "--noheader") == 0)
    {
      noHeader = true;
    }
    else if (strcmp(arg, "--study") == 0)
    {
      level = 2;
    }
    else if (strcmp(arg, "--series") == 0)
    {
      level = 3;
    }
    else if (strcmp(arg, "--image") == 0)
    {
      level = 4;
    }
    else if (strcmp(arg, "--silent") == 0)
    {
      silent = true;
    }
    else if (arg[0] == '-')
    {
      fprintf(stderr, "Error: Unrecognized option %s.\n\n", arg);
      dicomtocsv_usage(stderr, dicomtocsv_basename(argv[0]));
      return 1;
    }
    else
    {
      int code = vtkDICOMFile::Access(arg, vtkDICOMFile::In);
      if (code == vtkDICOMFile::Good || code == vtkDICOMFile::FileIsDirectory)
      {
        a->InsertNextValue(arg);
      }
      else if (dicomcli_looks_like_key(arg))
      {
        fprintf(stderr, "Error: Missing -k before %s.\n\n", arg);
        return 1;
      }
      else if (strlen(arg) > 4 &&
               strcmp(&arg[strlen(arg) - 4], ".csv") == 0)
      {
        fprintf(stderr, "Error: Missing -o before %s.\n\n", arg);
        return 1;
      }
      else
      {
        fprintf(stderr, "Error: File not found: %s.\n\n", arg);
        return 1;
      }
    }
  }

  FILE *fp = stdout;
  FILE *fp1 = NULL;

  if (ofile)
  {
#ifndef _WIN32
    fp1 = fopen(ofile, "wb");
#else
    // use wide chars to avoid narrowing to local character set
    int n = MultiByteToWideChar(CP_UTF8, 0, ofile, -1, NULL, 0);
    wchar_t *wofile = new wchar_t[n];
    MultiByteToWideChar(CP_UTF8, 0, ofile, -1, wofile, n);
    fp1 = _wfopen(wofile, L"wb");
    delete [] wofile;
#endif

    if (!fp1)
    {
      fprintf(stderr, "Error: Unable to open output file %s.\n", ofile);
      return 1;
    }
    fp = fp1;
  }
  else
  {
    // if output to stdout, then silence progress reporting
    silent = true;
  }

  // If no query specified, then use a default one
  if (qtlist.size() == 0)
  {
    if (level == 2)
    {
      dicomtocsv_study_default(&query, &qtlist);
    }
    else if (level == 3)
    {
      dicomtocsv_series_default(&query, &qtlist);
    }
    else if (level == 4)
    {
      dicomtocsv_image_default(&query, &qtlist);
    }
  }

  // Write the header
  if (!noHeader)
  {
    dicomtocsv_writeheader(query, &qtlist, fp);
    fflush(fp);
  }

  // Write data for every input directory
  if (a->GetNumberOfTuples() > 0)
  {
    vtkSmartPointer<ProgressObserver> p;

    // Set the default characte set
    vtkDICOMCharacterSet::SetGlobalDefault(charset);

    vtkSmartPointer<vtkDICOMDirectory> finder =
      vtkSmartPointer<vtkDICOMDirectory>::New();
    finder->SetRequirePixelData(imagesOnly);
    if (level < 4)
    {
      finder->SetFindLevelToSeries();
    }
    if (!silent)
    {
      p = vtkSmartPointer<ProgressObserver>::New();
      p->SetText("Scanning");
      finder->AddObserver(vtkCommand::ProgressEvent, p);
      finder->AddObserver(vtkCommand::StartEvent, p);
      finder->AddObserver(vtkCommand::EndEvent, p);
    }
    finder->SetInputFileNames(a);
    finder->SetIgnoreDicomdir(ignoreDicomdir);
    finder->SetScanDepth(scandepth);
    finder->SetFindQuery(query);
    finder->Update();

    if (!silent)
    {
      p->SetText("Writing");
    }
    dicomtocsv_write(
      finder, query, &qtlist, fp, level,
      firstNonZero, useDirectoryRecords, p);

    fflush(fp);
  }

  if (fp1)
  {
    fclose(fp1);
  }

  return rval;
}
