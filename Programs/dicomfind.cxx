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
#include "readquery.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

// includes for execvp
#ifndef _WIN32
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>

// print the version
void dicomfind_version(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2015, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void dicomfind_usage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s [options] <directory>\n\n", cp);
  fprintf(file, "options:\n"
    "  -k tag=value    Provide a key to be queried and matched.\n"
    "  -exec ... +     Execute the given command for every series matched.\n"      
    "  -exec ... \\;   Execute the given command for every file matched.\n"      
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

// Write the header for a csv file
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

// Write out the results in csv format
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
      if (a->GetNumberOfValues() == 0)
        {
        continue;
        }

      vtkSmartPointer<vtkDICOMMetaData> meta =
        vtkSmartPointer<vtkDICOMMetaData>::New();
      vtkSmartPointer<vtkDICOMParser> parser =
        vtkSmartPointer<vtkDICOMParser>::New();

      parser->SetFileName(a->GetValue(0));
      parser->SetMetaData(meta);
      parser->SetQueryItem(query);
      parser->Update();

      // create an adapter, in case of enhanced IOD
      vtkDICOMMetaDataAdapter adapter(meta);

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
            vp = &adapter->GetAttributeValue(tag);
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
        else if (tagPath.GetHead() == DC::ReferencedFileID &&
                 !tagPath.HasTail())
          {
          // ReferencedFileID (0004,1500) is meant to be used in DICOMDIR files,
          // but we hijack it to report the first file in the series.
          os << "\"" << dicomfind_quote(a->GetValue(0)) << "\"";
          }
        else if (tagPath.GetHead() == DC::NumberOfReferences &&
                 !tagPath.HasTail())
          {
          // NumberOfReferences (0004,1600) is a retired attribute meant to count
          // the number of references to a file, but we hijack it and use it to
          // report the number of files found for the series.
          os << "\"" << a->GetNumberOfValues() << "\"";
          }
        }

      os << "\r\n";
      }
    }
}

// Read a tag and its value from the command line.
bool get_tag_val(char *arg, vtkDICOMTag *tag_ptr, char **val_ptr)
{
  char *cp = arg;
  char *dp = cp;
  unsigned short g = static_cast<unsigned short>(strtoul(cp, &cp, 16));
  if (cp - dp != 4 || *cp++ != ',') { return false; }
  dp = cp;
  unsigned short e = static_cast<unsigned short>(strtoul(cp, &cp, 16));
  if (cp - dp != 4 || (*cp != '\0' && *cp != '=')) { return false; }
  *tag_ptr = vtkDICOMTag(g,e);
  if (*cp == '=')
    {
    *val_ptr = ++cp;
    }
  return true;
}

// Execute a subprocess
#ifndef _WIN32
bool execute_command(const char *command, char *argv[])
{
  // flush the output
  fflush(stdout);
  fflush(stderr);

  // fork a new process
  pid_t command_pid = fork();
  if (command_pid == -1)
    {
    fprintf(stderr, "Unable to create subprocess: %s\n", argv[0]);
    }

  // if fork() returned a pid, then this is the original process
  if (command_pid != 0)
    {
    int command_status;
    while (waitpid(command_pid, &command_status, 0) == static_cast<pid_t>(-1))
      {
      if (errno != EINTR)
        {
        fprintf(stderr, "Unknown error with subprocess: %s\n", argv[0]);
        return false;
        }
      }
    if (WIFEXITED(command_status))
      {
      if (WEXITSTATUS(command_status) != 0)
        {
        fprintf(stderr, "Subprocess returned negative result: %s\n", argv[0]);
        }
      return true;
      }
    else
      {
      fprintf(stderr, "Abnormal subprocess termination: %s\n", argv[0]);
      }
    }
  else if (execvp(command, argv) == -1)
    {
    if (errno == ENOENT)
      {
      fprintf(stderr, "Executable not found: %s\n", argv[0]);
      }
    else if (errno == ENOEXEC)
      {
      fprintf(stderr, "File is not executable: %s\n", argv[0]);
      }
    else if (errno == EACCES)
      {
      fprintf(stderr, "Access (permission) error: %s\n", argv[0]);
      }
    else if (errno == E2BIG)
      {
      fprintf(stderr, "Command line to long for command: %s\n", argv[0]);
      }
    else if (errno == ENOMEM)
      {
      fprintf(stderr, "Out of memory while running command: %s\n", argv[0]);
      }
    else if (errno == EMFILE)
      {
      fprintf(stderr, "No more available file handles: %s\n", argv[0]);
      }
    else
      {
      fprintf(stderr, "Unknown error while running command: %s\n", argv[0]);
      }

    return false;
    }

  return true;
}
#else
bool execute_command(const char *command, char *argv[])
{
  // no support for -exec on Windows, yet
  return false;
}
#endif

// This program will dump all the metadata in the given file
int main(int argc, char *argv[])
{
  int rval = 0;
  QueryTagList qtlist;
  vtkDICOMItem query;
  std::vector<std::string> oplist;

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
    else if (strcmp(arg, "-k") == 0)
      {
      vtkDICOMTag tag;
      char *val = 0;
      ++argi;
      if (argi == argc || !get_tag_val(argv[argi], &tag, &val))
        {
        fprintf(stderr, "%s must be followed by gggg,eeee=value "
                        "where gggg,eeee is a DICOM tag.\n\n", arg);
        return 1;
        }
      vtkDICOMVR vr = query.FindDictVR(tag);
      if (vr == vtkDICOMVR::UN)
        {
        fprintf(stderr,
                "%s was given tag %4.4x,%4.4x which is not in the "
                "DICOM dictionary.\n\n",
                arg, tag.GetGroup(), tag.GetElement());
        return 1;
        }
      qtlist.push_back(vtkDICOMTagPath(tag));
      if (val)
        {
        query.SetAttributeValue(tag, val);
        }
      else
        {
        query.SetAttributeValue(tag, vtkDICOMValue(vr));
        }
      }
    else if (strcmp(arg, "-exec") == 0)
      {
      int argj = ++argi;
      for (; argj < argc; argj++)
        {
        if (strcmp(argv[argj], ";") == 0 ||
            strcmp(argv[argj], "+") == 0)
          {
          break;
          }
        }
      if (argj == argc)
        {
        fprintf(stderr, "%s must be terminated with + or \\; "
                "(plus or semicolon).\n\n",
                arg);
        return 1;
        }
      for (; argi <= argj; argi++)
        {
        oplist.push_back(argv[argi]);
        }
      argi++;
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
  if (qfile && !dicomcli_readquery(qfile, &query, &qtlist))
    {
    fprintf(stderr, "Can't open query file %s\n\n", qfile);
    return 1;
    }

  // always add the functional sequences for advanced files
  query.SetAttributeValue(
    DC::SharedFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));
  query.SetAttributeValue(
    DC::PerFrameFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));

  if (ofile)
    {
    // Write the header
    dicomfind_writeheader(query, &qtlist, *osp);
    osp->flush();
    }

  // Write data for every input directory
  for (vtkIdType i = 0; i < a->GetNumberOfTuples(); i++)
    {
    vtkSmartPointer<vtkDICOMDirectory> finder =
      vtkSmartPointer<vtkDICOMDirectory>::New();
    finder->SetDirectoryName(a->GetValue(i));
    finder->SetScanDepth(8);
    finder->SetFindQuery(query);
    finder->Update();

    if (ofile)
      {
      dicomfind_write(finder, query, &qtlist, *osp);
      }
    else if (!oplist.empty())
      {
      size_t subcount = 0;
      for (size_t jj = 0; jj < oplist.size(); jj++)
        {
        subcount += (oplist[jj] == "{}");
        }

      for (int j = 0; j < finder->GetNumberOfStudies(); j++)
        {
        int k0 = finder->GetFirstSeriesForStudy(j);
        int k1 = finder->GetLastSeriesForStudy(j);
        for (int k = k0; k <= k1; k++)
          {
          vtkStringArray *sa = finder->GetFileNamesForSeries(k);

          if (oplist.back() == ";")
            {
            // call program for each file
            for (int kk = 0; kk < sa->GetNumberOfValues(); kk++)
              {
              size_t sub_argc = oplist.size() + subcount - 1;
              char **sub_argv = new char *[sub_argc+1];

              size_t ii = 0;
              size_t nn = oplist.size()-1;
              for (size_t jj = 0; jj < nn; jj++)
                {
                if (oplist[jj] == "{}")
                  {
                  sub_argv[ii++] = const_cast<char *>(sa->GetValue(kk).c_str());
                  }
                else
                  {
                  sub_argv[ii++] = const_cast<char *>(oplist[jj].c_str());
                  }
                }
              sub_argv[ii] = 0;

              if (!execute_command(sub_argv[0], sub_argv))
                {
                fprintf(stderr, "failure!");
                }

              delete [] sub_argv;
              }
            }
          else
            {
            // call program for each series
            size_t sub_argc = oplist.size() + subcount*sa->GetNumberOfTuples() - 1;
            char **sub_argv = new char *[sub_argc+1];

            size_t ii = 0;
            size_t nn = oplist.size()-1;
            for (size_t jj = 0; jj < nn; jj++)
              {
              if (oplist[jj] == "{}")
                {
                for (vtkIdType kk = 0; kk < sa->GetNumberOfValues(); kk++)
                  {
                  sub_argv[ii++] = const_cast<char *>(sa->GetValue(kk).c_str());
                  }
                }
              else
                {
                sub_argv[ii++] = const_cast<char *>(oplist[jj].c_str());
                }
              }
            sub_argv[ii] = 0;

            if (!execute_command(sub_argv[0], sub_argv))
              {
              fprintf(stderr, "failure!");
              }

            delete [] sub_argv;
            }
          }
        }
      }
    else
      {
      for (int j = 0; j < finder->GetNumberOfStudies(); j++)
        {
        int k0 = finder->GetFirstSeriesForStudy(j);
        int k1 = finder->GetLastSeriesForStudy(j);
        for (int k = k0; k <= k1; k++)
          {
          vtkStringArray *sa = finder->GetFileNamesForSeries(k);
          for (int kk = 0; kk < sa->GetNumberOfValues(); kk++)
            {
            *osp << sa->GetValue(kk) << "\n";
            }
          }
        }
      }

    osp->flush();
    }

  return rval;
}
