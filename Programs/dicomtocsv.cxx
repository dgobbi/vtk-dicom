/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
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
#include "vtkDICOMMetaDataAdapter.h"

// from dicomcli
#include "mainmacro.h"
#include "readquery.h"

#include <vtkCommand.h>
#include <vtkTimerLog.h>
#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <limits>
#include <iostream>

namespace {

// print the version
void dicomtocsv_version(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2015, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void dicomtocsv_usage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s [options] <directory>\n\n", cp);
  fprintf(file, "options:\n"
    "  -k tag=value    Provide a key to be queried and matched.\n"
    "  -q <query.txt>  Provide a file to describe the find query.\n"
    "  -o <data.csv>   Provide a file for the query results.\n"
    "  --first-nonzero Search series for first nonzero value of each key.\n"
    "  --study         Print one row for each study.\n"
    "  --series        Print one row for each series (default).\n"
    "  --image         Print one row for each image.\n"
    "  --help          Print a brief help message.\n"
    "  --version       Print the software version.\n");
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
    "should be preceded by the private dictionary name in square brackets.\n\n");
}

// remove path portion of filename
const char *dicomtocsv_basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

typedef vtkDICOMVR VR;

// Write the header for a csv file
void dicomtocsv_writeheader(
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

// Write out the results in csv format
void dicomtocsv_write(vtkDICOMDirectory *finder,
  const vtkDICOMItem& query, const QueryTagList *ql, std::ostream& os,
  int level, bool firstNonZero, vtkCommand *p)
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

      vtkSmartPointer<vtkDICOMMetaData> meta =
        vtkSmartPointer<vtkDICOMMetaData>::New();
      vtkSmartPointer<vtkDICOMParser> parser =
        vtkSmartPointer<vtkDICOMParser>::New();

      parser->SetQueryItem(query);
      parser->SetMetaData(meta);

      if (level >= 4 || firstNonZero)
        {
        // need to parse all files
        meta->SetNumberOfInstances(a->GetNumberOfValues());
        }

      for (int ii = 0; ii < meta->GetNumberOfInstances(); ii++)
        {
        parser->SetIndex(ii);
        parser->SetFileName(a->GetValue(ii));
        parser->Update();
        }

      // create an adapter, in case of enhanced IOD
      vtkDICOMMetaDataAdapter adapter(meta);

      // this loop is only for the "image" level
      int m = (level >= 4 ? meta->GetNumberOfInstances() : 1);
      for (int jj = 0; jj < m; jj++)
        {
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

          // this loop is only needed if firstNonZero is set
          int n = (firstNonZero ? meta->GetNumberOfInstances() : 1);
          n = (level >= 4 ? jj+1 : n);
          for (int ii = jj; ii < n; ii++)
            {
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
                  tag = mitem->ResolvePrivateTag(tag, creator);
                  }
                else
                  {
                  tag = adapter->ResolvePrivateTag(tag, creator);
                  }
                }
              if (mitem)
                {
                vp = &mitem->GetAttributeValue(tag);
                }
              else
                {
                vp = &adapter->GetAttributeValue(ii, tag);
                }
              if (vp && !vp->IsValid())
                {
                vp = 0;
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
              os << v;
              }
            else if (v.GetVR() == VR::DA ||
                     v.GetVR() == VR::TM ||
                     v.GetVR() == VR::DT)
              {
              os << "\"" << dicomtocsv_date(v.AsString(), v.GetVR()) << "\"";
              }
            else if (v.GetVR() == VR::SQ)
              {
              // how should a sequence be printed out to the csv file?
              }
            else if (v.GetVL() != 0 && v.GetVL() != 0xFFFFFFFF)
              {
              os << "\"" << dicomtocsv_quote(v.AsUTF8String()) << "\"";
              }
            }
          else if (tagPath.GetHead() == DC::ReferencedFileID &&
                   !tagPath.HasTail())
            {
            // ReferencedFileID (0004,1500) is meant to be used in DICOMDIR,
            // but we hijack it to report the first file in the series.
            os << "\"" << dicomtocsv_quote(a->GetValue(jj)) << "\"";
            }
          else if (tagPath.GetHead() == DC::NumberOfReferences &&
                   !tagPath.HasTail())
            {
            // NumberOfReferences (0004,1600) is a retired attribute meant
            // to count the number of references to a file, but we hijack
            // it and use it to report the number of files found for the
            // series.
            os << "\"" << numberOfFiles << "\"";
            }
          }

        os << "\r\n";

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

// Capture progress events
class ProgressObserver : public vtkCommand
{
public:
  static ProgressObserver *New() { return new ProgressObserver; }
  vtkTypeMacro(ProgressObserver,vtkCommand);
  virtual void Execute(
    vtkObject *caller, unsigned long eventId, void *callData);
  void SetText(const char *text) { this->Text = text; }
protected:
  ProgressObserver() : Stage(0), Anim(0), LastTime(0), Text("") {}
  ProgressObserver(const ProgressObserver& c) : vtkCommand(c) {}
  void operator=(const ProgressObserver&) {}
  int Stage;
  int Anim;
  double LastTime;
  const char *Text;
};

void ProgressObserver::Execute(vtkObject *, unsigned long e, void *vp)
{
  const double initial = 2.0; // time until first report
  const double delta = 0.1; // time between reports
  double t = vtkTimerLog::GetUniversalTime();

  if (e == vtkCommand::StartEvent)
    {
    this->LastTime = t;
    this->Stage = 0;
    this->Anim = 0;
    }
  else if (e == vtkCommand::ProgressEvent)
    {
    double *dp = static_cast<double *>(vp);
    int progress = static_cast<int>((*dp)*100.0 + 0.5);

    if (this->Stage == 0)
      {
      if (t - this->LastTime > initial)
        {
        std::cout << "\r                                   ";
        this->Stage = 1;
        }
      }
    if (t - this->LastTime > delta)
      {
      if (this->Stage == 1)
        {
        if (progress == 0)
          {
          const char *dots[] = { ".  ", ".. ", "..." };
          this->Anim = (this->Anim + 1) % 3;
          std::cout << "\r" << this->Text << dots[this->Anim];
          std::cout.flush();
          this->LastTime = t;
          }
        else
          {
          std::cout << "\r" << this->Text << " " << progress << "%";
          std::cout.flush();
          this->LastTime = t;
          }
        }
      }
    }
  else if (e == vtkCommand::EndEvent)
    {
    if (this->Stage > 0)
      {
      std::cout << "\r" << this->Text << " 100%";
      std::cout << std::endl;
      }
    }
}

} // end anonymous namespace

// This program will dump all the metadata in the given file
MAINMACRO(argc, argv)
{
  int rval = 0;
  int scandepth = std::numeric_limits<int>::max();
  QueryTagList qtlist;
  vtkDICOMItem query;
  std::vector<std::string> oplist;
  bool firstNonZero = false;
  int level = 3; // default to series level

  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();
  const char *ofile = 0;

  // always query the functional sequences for advanced files
  query.SetAttributeValue(
    DC::SharedFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));
  query.SetAttributeValue(
    DC::PerFrameFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));

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
        fprintf(stderr, "%s must be followed by a file.\n\n", arg);
        dicomtocsv_usage(stderr, dicomtocsv_basename(argv[0]));
        return 1;
        }

      if (arg[1] == 'q')
        {
        const char *qfile = argv[++argi];
        if (!dicomcli_readquery(qfile, &query, &qtlist))
          {
          fprintf(stderr, "Can't read query file %s\n\n", qfile);
          return 1;
          }
        }
      else if (arg[1] == 'o')
        {
        ofile = argv[++argi];
        }
      }
    else if (strcmp(arg, "-k") == 0)
      {
      vtkDICOMTag tag;
      ++argi;
      if (argi == argc)
        {
        fprintf(stderr, "%s must be followed by gggg,eeee=value "
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
    else if (arg[0] == '-')
      {
      fprintf(stderr, "unrecognized option %s.\n\n", arg);
      dicomtocsv_usage(stderr, dicomtocsv_basename(argv[0]));
      return 1;
      }
    else
      {
      a->InsertNextValue(arg);
      }
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

  // Write the header
  dicomtocsv_writeheader(query, &qtlist, *osp);
  osp->flush();

  // Write data for every input directory
  if (a->GetNumberOfTuples() > 0)
    {
    vtkSmartPointer<ProgressObserver> p;

    vtkSmartPointer<vtkDICOMDirectory> finder =
      vtkSmartPointer<vtkDICOMDirectory>::New();
    if (ofile)
      {
      p = vtkSmartPointer<ProgressObserver>::New();
      p->SetText("Scanning");
      finder->AddObserver(vtkCommand::ProgressEvent, p);
      finder->AddObserver(vtkCommand::StartEvent, p);
      finder->AddObserver(vtkCommand::EndEvent, p);
      }
    finder->SetInputFileNames(a);
    finder->SetScanDepth(scandepth);
    finder->SetFindQuery(query);
    finder->Update();

    if (ofile)
      {
      p->SetText("Writing");
      }
    dicomtocsv_write(
      finder, query, &qtlist, *osp, level, firstNonZero, p);

    osp->flush();
    }

  return rval;
}
