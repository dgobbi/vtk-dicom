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
#include "vtkDICOMMetaData.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMFile.h"

// from dicomcli
#include "mainmacro.h"
#include "readquery.h"
#include "progress.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <vtksys/SystemTools.hxx>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <limits>
#include <iostream>
#include <map>
#include <utility>

// print the version
void dicompull_version(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2015, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void dicompull_usage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s [options] <directory> ...\n\n", cp);
  fprintf(file, "options:\n"
    "  -L              Follow symbolic links (default).\n"
    "  -P              Do not follow symbolic links.\n"
    "  -k tag=value    Provide an attribute to be queried and matched.\n"
    "  -q <query.txt>  Provide a file to describe the find query.\n"
    "  -o <directory>  Directory to place the files into.\n"
    "  -maxdepth n     Set the maximum directory depth.\n"
    "  -name pattern   Set file names to match (with \"*\" or \"?\").\n"
    "  -image          Restrict the search to files with PixelData.\n"
    "  -series         Find all files in series if even one file matches.\n"
    "  --help          Print a brief help message.\n"
    "  --version       Print the software version.\n"
    );
}

// print the help
void dicompull_help(FILE *file, const char *cp)
{
  dicompull_usage(file, cp);
  fprintf(file, "\n"
    "Find dicom files in one directory and copy them to a new directory.\n"
    "\n"
    "The output directory given with \"-o\" can use DICOM attributes, by\n"
    "naming those attributes within curly braces.  For example, consider\n"
    "\"{PatientID}/{StudyDescription}/{SeriesDescription}-{SeriesNumber}\"\n"
    "or something similar to produce a hierarchichal directory structure.\n"
    "The attributes used in the path should be from the following list:\n"
    "  PatientID, PatientName, PatientBirthDate, PatientSex,\n"
    "  StudyID, StudyDescription, StudyDate, StudyTime, StudyInstanceUID,\n"
    "  SeriesNumber, SeriesDescription, SeriesInstanceUID,\n"
    "  Modality, AccessionNumber.\n"
    "\n"
    "The files to be copied are specified with search keys, which take the\n"
    "form \"-k key=value\" where keys can either use the standard names given\n"
    "in the DICOM dictionary, e.g. Modality or SeriesDescription, or can be\n"
    "in the form GGGG,EEEE with hexadecimal group and element values.  The\n"
    "tags can also be listed in a query file with the \"-q\" option (one tag\n"
    "per line). Private tags should be preceded by the private dictionary\n"
    "name in square brackets.\n"
    "\n"
    "The values used for \"-k key=value\" can use the wildcards * and ?, and\n"
    "can also use date ranges of the form \"19990103-19990105\".\n"
    "\n"
  );
}

// remove path portion of filename
const char *dicompull_basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// get directory portion of filename
std::string dicompull_dirname(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename)
    {
    --cp;
    if (cp[0] == '\\' || cp[0] == '/') { break; }
    }
  return std::string(filename, cp - filename);
}

typedef vtkDICOMVR VR;

std::string dicompull_cleanup(const std::string& input)
{
  std::string::const_iterator a = input.begin();
  std::string::const_iterator b = a;
  std::string s;
  while (a != input.end())
    {
    while (a != input.end() &&
           ((*a & 0x80) == 0) && isgraph(*a) && !ispunct(*a))
      {
      ++a;
      }
    s.append(b, a);
    b = a;
    while (a != input.end() &&
           (((*a & 0x80) != 0) || !isgraph(*a) || ispunct(*a)))
      {
      ++a;
      }
    if (b != a && b != input.begin() && a != input.end())
      {
      s.append("_");
      }
    b = a;
    }

  return s;
}

std::string dicompull_makedirname(
  vtkDICOMDirectory *finder, int study, int series, const char *outdir)
{
  std::string s;
  std::string key;
  std::string val;
  vtkDICOMValue v;

  const char *cp = outdir;
  const char *dp = cp;
  const char *bp = 0;
  while (*cp != '\0')
    {
    while (*cp != '{' && *cp != '}' && *cp != '\0') { cp++; }
    if (*cp == '}')
      {
      fprintf(stderr, "Missing \'{\': %s\n", outdir);
      exit(1);
      }
    if (*cp == '{')
      {
      bp = cp;
      while (*cp != '}' && *cp != '\0') { cp++; }
      if (*cp != '}')
        {
        fprintf(stderr, "Unmatched \'{\': %s\n", outdir);
        exit(1);
        }
      else
        {
        s.append(dp, bp);
        bp++;
        key.assign(bp, cp);
        cp++;
        dp = cp;
        v.Clear();
        vtkDICOMTag tag;
        if (key.length() > 0)
          {
          vtkDICOMDictEntry de = vtkDICOMDictionary::FindDictEntry(key.c_str());
          if (de.IsValid())
            {
            tag = de.GetTag();
            }
          else
            {
            fprintf(stderr, "Unrecognized key %s\n", key.c_str());
            exit(1);
            }
          }
        if (finder)
          {
          if (!v.IsValid())
            {
            v = finder->GetStudyRecord(study).GetAttributeValue(tag);
            }
          if (!v.IsValid())
            {
            v = finder->GetPatientRecordForStudy(study).GetAttributeValue(tag);
            }
          if (!v.IsValid())
            {
            v = finder->GetSeriesRecord(series).GetAttributeValue(tag);
            }
          }
        if (v.IsValid())
          {
          val.assign(dicompull_cleanup(v.AsUTF8String()));
          }
        else if (finder)
          {
          fprintf(stderr, "Sorry, key %s cannot be in output directory.\n",
                  key.c_str());
          exit(1);
          }
        if (val.empty())
          {
          val = "Empty";
          }
        s.append(val);
        }
      }
    }
  s.append(dp, cp);

  return s;
}

// This program will find and copy dicom files
MAINMACRO(argc, argv)
{
  int rval = 0;
  int scandepth = std::numeric_limits<int>::max();
  bool followSymlinks = true;
  const char *pattern = "";
  QueryTagList qtlist;
  vtkDICOMItem query;
  bool requirePixelData = false;
  bool findSeries = false;
  std::string outdir;

  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();

  // always query the functional sequences for advanced files
  query.SetAttributeValue(
    DC::SharedFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));
  query.SetAttributeValue(
    DC::PerFrameFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));

  if (argc < 2)
    {
    dicompull_usage(stdout, dicompull_basename(argv[0]));
    return rval;
    }
  else if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
    dicompull_help(stdout, dicompull_basename(argv[0]));
    return rval;
    }
  else if (argc == 2 && strcmp(argv[1], "--version") == 0)
    {
    dicompull_version(stdout, dicompull_basename(argv[0]));
    return rval;
    }

  for (int argi = 1; argi < argc; argi++)
    {
    const char *arg = argv[argi];
    if (strcmp(arg, "-P") == 0)
      {
      followSymlinks = false;
      }
    else if (strcmp(arg, "-L") == 0)
      {
      followSymlinks = true;
      }
    else if (strcmp(arg, "-q") == 0)
      {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
        {
        fprintf(stderr, "%s must be followed by a file.\n\n", arg);
        dicompull_usage(stderr, dicompull_basename(argv[0]));
        return 1;
        }
      const char *qfile = argv[++argi];
      if (!dicomcli_readquery(qfile, &query, &qtlist))
        {
        fprintf(stderr, "Can't read query file %s\n\n", qfile);
        return 1;
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
    else if (strcmp(arg, "-o") == 0)
      {
      vtkDICOMTag tag;
      ++argi;
      if (argi == argc || argv[argi][0] == '-')
        {
        fprintf(stderr, "%s must be followed by an output directory.\n\n",
                arg);
        return 1;
        }
      outdir = argv[argi];
      }
    else if (strcmp(arg, "-maxdepth") == 0)
      {
      ++argi;
      if (argi == argc)
        {
        fprintf(stderr, "%s must be followed by an argument.\n\n", arg);
        return 1;
        }
      scandepth = static_cast<int>(atol(argv[argi]));
      }
    else if (strcmp(arg, "-name") == 0)
      {
      ++argi;
      if (argi == argc)
        {
        fprintf(stderr, "%s must be followed by an argument.\n\n", arg);
        return 1;
        }
      pattern = argv[argi];
      }
    else if (strcmp(arg, "-image") == 0)
      {
      requirePixelData = true;
      }
    else if (strcmp(arg, "-series") == 0)
      {
      findSeries = true;
      }
    else if (arg[0] == '-')
      {
      fprintf(stderr, "unrecognized option %s.\n\n", arg);
      dicompull_usage(stderr, dicompull_basename(argv[0]));
      return 1;
      }
    else
      {
      a->InsertNextValue(arg);
      }
    }

  // output directory is mandatory
  if (outdir.empty())
    {
    fprintf(stderr,
      "\nNo output directory was specified (-o <directory>).\n\n");
    exit(1);
    }

  // do a dry run to make sure outdir string is valid
  dicompull_makedirname(NULL, 0, 0, outdir.c_str());

  // Separator between directory and file
  const char *sep = (outdir.empty() ? "" : "//");
#ifdef _WIN32
  for (std::string::const_iterator si = outdir.begin();
       si != outdir.end(); ++si)
    {
    if (*si == '/') { sep = "/"; }
    else if (*si == '\\') { sep = "\\"; }
    }
#endif

  // Create a map of all directories written to.  The count is the
  // number of series that have been written to the directory.
  std::map<std::string, int> dircount;

  // Write data for every input directory
  if (a->GetNumberOfTuples() > 0)
    {
    const size_t bufsize = 8192;
    unsigned char *buffer = new unsigned char [bufsize];

    vtkSmartPointer<vtkDICOMDirectory> finder =
      vtkSmartPointer<vtkDICOMDirectory>::New();
    finder->SetInputFileNames(a);
    finder->SetFilePattern(pattern);
    finder->SetScanDepth(scandepth);
    finder->SetFindQuery(query);
    finder->SetFollowSymlinks(followSymlinks);
    finder->SetRequirePixelData(requirePixelData);
    finder->SetFindLevel(
      findSeries ? vtkDICOMDirectory::SERIES : vtkDICOMDirectory::IMAGE);

    vtkSmartPointer<ProgressObserver> p =
      vtkSmartPointer<ProgressObserver>::New();
    p->SetText("Scanning");
    finder->AddObserver(vtkCommand::ProgressEvent, p);
    finder->AddObserver(vtkCommand::StartEvent, p);
    finder->AddObserver(vtkCommand::EndEvent, p);

    finder->Update();

    p->SetText("Copying");
    p->Execute(NULL, vtkCommand::StartEvent, NULL);
    vtkIdType count = 0;
    vtkIdType total = 0;
    for (int k = 0; k < finder->GetNumberOfSeries(); k++)
      {
      total += finder->GetFileNamesForSeries(k)->GetNumberOfValues();
      }

    for (int j = 0; j < finder->GetNumberOfStudies(); j++)
      {
      int k0 = finder->GetFirstSeriesForStudy(j);
      int k1 = finder->GetLastSeriesForStudy(j);

      for (int k = k0; k <= k1; k++)
        {
        vtkStringArray *sa = finder->GetFileNamesForSeries(k);
        // create the directory name
        std::string dirname =
          dicompull_makedirname(finder, j, k, outdir.c_str());
        std::map<std::string,int>::iterator mi = dircount.find(dirname);
        int si = 1;
        if (mi != dircount.end())
          {
          si = mi->second + 1;
          mi->second = si;
          }
        else
          {
          dircount[dirname] = si;
          if (!vtksys::SystemTools::MakeDirectory(dirname.c_str()))
            {
            fprintf(stderr, "Cannot create directory: %s\n",
                    dirname.c_str());
            delete [] buffer;
            exit(1);
            }
          }
        for (vtkIdType i = 0; i < sa->GetNumberOfValues(); i++)
          {
          // copy the file
          char fname[32];
          sprintf(fname, "%sIM-%04d-%04d.dcm",
                  sep, si, static_cast<int>(i+1));
          const std::string& srcname = sa->GetValue(i);
          std::string fullname = dirname + fname;
          if (!vtksys::SystemTools::SameFile(srcname.c_str(), fullname.c_str()))
            {
            vtkDICOMFile infile(srcname.c_str(), vtkDICOMFile::In);
            if (infile.GetError())
              {
              const char *message = "Cannot copy file";
              switch (infile.GetError())
                {
                case vtkDICOMFile::AccessDenied:
                  message = "Access denied for file";
                  break;
                case vtkDICOMFile::IsDirectory:
                  message = "This file is a directory";
                  break;
                case vtkDICOMFile::FileNotFound:
                case vtkDICOMFile::DirectoryNotFound:
                  message = "File does not exist";
                  break;
                }
              fprintf(stderr, "%s: %s\n", message, srcname.c_str());
              }
            else if (infile.GetSize() == 0)
              {
              fprintf(stderr, "File size is zero: %s\n", srcname.c_str());
              }
            else
              {
              vtkDICOMFile outfile(fullname.c_str(), vtkDICOMFile::Out);
              if (outfile.GetError())
                {
                const char *message = "Cannot write file";
                switch (outfile.GetError())
                  {
                  case vtkDICOMFile::AccessDenied:
                    message = "Access denied for output file";
                    break;
                  case vtkDICOMFile::IsDirectory:
                    message = "This output is a directory";
                    break;
                  case vtkDICOMFile::DirectoryNotFound:
                    message = "Directory does not exist";
                    break;
                  }
                fprintf(stderr, "%s: %s\n", message, fullname.c_str());
                }
              else
                {
                // copy the file
                while (!infile.EndOfFile())
                  {
                  size_t bytecount = infile.Read(buffer, bufsize);
                  if (bytecount == 0 && infile.GetError())
                    {
                    fprintf(stderr, "Error, incomplete read: %s\n",
                            srcname.c_str());
                    vtkDICOMFile::Remove(fullname.c_str());
                    break;
                    }
                  if (bytecount > 0 &&
                      outfile.Write(buffer, bytecount) != bytecount)
                    {
                    fprintf(stderr, "Error, incomplete write: %s\n",
                            fullname.c_str());
                    vtkDICOMFile::Remove(fullname.c_str());
                    break;
                    }
                  }
                }
              }
            }

          count++;
          double progress = (static_cast<double>(count)/
                             static_cast<double>(total));
          p->Execute(NULL, vtkCommand::ProgressEvent, &progress);
          }
        }
      }
    delete [] buffer;
    p->Execute(NULL, vtkCommand::EndEvent, NULL);
    }

  return rval;
}
