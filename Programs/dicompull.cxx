/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
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
#include "vtkDICOMMetaData.h"
#include "vtkDICOMDictionary.h"
#include "vtkDICOMFile.h"
#include "vtkDICOMFilePath.h"
#include "vtkDICOMFileDirectory.h"

// from dicomcli
#include "vtkConsoleOutputWindow.h"
#include "mainmacro.h"
#include "readquery.h"
#include "progress.h"

#include "vtkStringArray.h"
#include "vtkSmartPointer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <limits>
#include <map>
#include <utility>

// print the version
void dicompull_version(FILE *file, const char *cp)
{
  fprintf(file, "%s %s\n", cp, DICOM_VERSION);
  fprintf(file, "\n"
    "Copyright (c) 2012-2019, David Gobbi.\n\n"
    "This software is distributed under an open-source license.  See the\n"
    "Copyright.txt file that comes with the vtk-dicom source distribution.\n");
}

// print the usage
void dicompull_usage(FILE *file, const char *cp)
{
  fprintf(file, "usage:\n"
    "  %s [options] <directory> ...\n\n", cp);
  fprintf(file, "options:\n"
    "  -L                Follow symbolic links (default).\n"
    "  -P                Do not follow symbolic links.\n"
    "  -k tag=value      Provide an attribute to be queried and matched.\n"
    "  -q <query.txt>    Provide a file to describe the find query.\n"
    "  -u <uids.txt>     Provide a file that contains a list of UIDs.\n"
    "  -o <directory>    Directory to place the files into.\n"
    "  -maxdepth n       Set the maximum directory depth.\n"
    "  -name pattern     Set file names to match (with \"*\" or \"?\").\n"
    "  -image            Restrict the search to files with PixelData.\n"
    "  -series           Find all files in series if even one file matches.\n"
    "  --ignore-dicomdir Ignore the DICOMDIR file even if it is present.\n"
    "  --charset <cs>    Charset to use if SpecificCharacterSet is missing.\n"
    "  --silent          Do not report any progress information.\n"
    "  --help            Print a brief help message.\n"
    "  --version         Print the software version.\n"
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
    "The \"-u\" option can be used to provide a list of UIDs.  Provide a file\n"
    "where the first line of the file is the key (e.g. SeriesInstanceUID) and\n"
    "the rest of the file is the UIDs to match, one UID per line.\n"
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

std::string dicompull_basedir(const char *outdir)
{
  std::string s;

  const char *lastslash = outdir;
  const char *cp = outdir;
  while (*cp != '\0')
  {
    while (*cp != '/' && *cp != '{' && *cp != '\0') { cp++; }
    if (*cp == '/')
    {
      cp++;
      lastslash = cp;
    }
    else if (*cp == '{')
    {
      cp = lastslash;
      break;
    }
  }

  if (cp == outdir)
  {
    s = "."; // current directory
  }
  else
  {
    s.append(outdir, cp);
  }

  return s;
}

void dicompull_checktags(
  vtkDICOMItem *query, QueryTagList *qtlist, const char *outdir)
{
  std::string keytext;
  const char *cp = outdir;
  const char *bp = 0;
  while (*cp != '\0')
  {
    while (*cp != '{' && *cp != '}' && *cp != '\0') { cp++; }
    if (*cp == '}')
    {
      fprintf(stderr, "Error: Missing \'{\': %s\n", outdir);
      exit(1);
    }
    if (*cp == '{')
    {
      cp++;
      bp = cp;
      while (*cp != '}' && *cp != '\0') { cp++; }
      if (*cp != '}')
      {
        fprintf(stderr, "Error: Unmatched \'{\': %s\n", outdir);
        exit(1);
      }
      else
      {
        keytext.assign(bp, cp);
        cp++;

        if (!dicomcli_readkey(keytext.c_str(), query, qtlist))
        {
          exit(1);
        }
      }
    }
  }
}

std::string dicompull_makedirname(vtkDICOMMetaData *meta, const char *outdir)
{
  std::string s;
  std::string keytext;
  std::string val;
  vtkDICOMValue v;
  vtkDICOMItem query;
  QueryTagList qtlist;

  const char *cp = outdir;
  const char *dp = cp;
  const char *bp = 0;
  while (*cp != '\0')
  {
    while (*cp != '{' && *cp != '}' && *cp != '\0') { cp++; }
    if (*cp == '}')
    {
      fprintf(stderr, "Error: Missing \'{\': %s\n", outdir);
      exit(1);
    }
    if (*cp == '{')
    {
      bp = cp;
      while (*cp != '}' && *cp != '\0') { cp++; }
      if (*cp != '}')
      {
        fprintf(stderr, "Error: Unmatched \'{\': %s\n", outdir);
        exit(1);
      }
      else
      {
        s.append(dp, bp);
        bp++;
        keytext.assign(bp, cp);
        cp++;
        dp = cp;

        if (!dicomcli_readkey(keytext.c_str(), &query, &qtlist, false))
        {
          exit(1);
        }

        const vtkDICOMTagPath& tagpath = qtlist.back();

        val.clear();
        v = meta->Get(tagpath);
        if (v.IsValid())
        {
          val.assign(dicompull_cleanup(v.AsUTF8String()));
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

// Delay wildcard expansion for -name option
MAINMACRO_PASSTHROUGH(-name);

// This program will find and copy dicom files
int MAINMACRO(int argc, char *argv[])
{
  // redirect all VTK errors to stderr
  vtkConsoleOutputWindow::Install();

  int rval = 0;
  int scandepth = std::numeric_limits<int>::max();
  bool followSymlinks = true;
  const char *pattern = "";
  QueryTagList qtlist;
  vtkDICOMItem query;
  bool requirePixelData = false;
  bool findSeries = false;
  bool ignoreDicomdir = false;
  vtkDICOMCharacterSet charset;
  bool silent = false;
  std::string outdir;

  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();

  // always query SpecificCharacterSet
  query.Set(DC::SpecificCharacterSet, vtkDICOMValue(VR::CS));

  // always query the functional sequences for advanced files
  query.Set(DC::SharedFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));
  query.Set(DC::PerFrameFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));

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
        fprintf(stderr, "Error: %s must be followed by a file.\n\n", arg);
        dicompull_usage(stderr, dicompull_basename(argv[0]));
        return 1;
      }
      const char *qfile = argv[++argi];
      if (!dicomcli_readquery(qfile, &query, &qtlist))
      {
        fprintf(stderr, "Error: Can't read query file %s\n\n", qfile);
        return 1;
      }
    }
    else if (strcmp(arg, "-u") == 0)
    {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
      {
        fprintf(stderr, "Error: %s must be followed by a file.\n\n", arg);
        dicompull_usage(stderr, dicompull_basename(argv[0]));
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
    else if (strcmp(arg, "-o") == 0)
    {
      vtkDICOMTag tag;
      ++argi;
      if (argi == argc || argv[argi][0] == '-')
      {
        fprintf(stderr, "Error: %s must be followed by output directory.\n\n",
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
        fprintf(stderr, "Error: %s must be followed by an argument.\n\n", arg);
        return 1;
      }
      scandepth = static_cast<int>(atol(argv[argi]));
    }
    else if (strcmp(arg, "-name") == 0)
    {
      ++argi;
      if (argi == argc)
      {
        fprintf(stderr, "Error: %s must be followed by an argument.\n\n", arg);
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
    else if (strcmp(arg, "--silent") == 0)
    {
      silent = true;
    }
    else if (arg[0] == '-')
    {
      fprintf(stderr, "Error: Unrecognized option %s.\n\n", arg);
      dicompull_usage(stderr, dicompull_basename(argv[0]));
      return 1;
    }
    else
    {
      int code = vtkDICOMFile::Access(arg, vtkDICOMFile::In);
      if (code == vtkDICOMFile::Good ||
          code == vtkDICOMFile::FileIsDirectory)
      {
        a->InsertNextValue(arg);
      }
      else if (dicomcli_looks_like_key(arg))
      {
        fprintf(stderr, "Error: Missing -k before %s.\n\n", arg);
        return 1;
      }
      else
      {
        fprintf(stderr, "Error: File not found: %s.\n\n", arg);
        return 1;
      }
    }
  }

  // output directory is mandatory
  if (outdir.empty())
  {
    fprintf(stderr,
      "\nError: No output directory was specified (-o <directory>).\n\n");
    exit(1);
  }

  // check that the outdir string is valid
  dicompull_checktags(&query, NULL, outdir.c_str());

  // check that the outdir is writable
  std::string basedir = dicompull_basedir(outdir.c_str());
  vtkDICOMFilePath basepath(basedir);
  while (!basepath.IsRoot() && !basepath.IsEmpty())
  {
    int code = vtkDICOMFileDirectory::Access(basepath.AsString().c_str(),
                                             vtkDICOMFileDirectory::In);
    if (code == 0)
    {
      // found a directory
      break;
    }
    else if (code == vtkDICOMFileDirectory::AccessDenied)
    {
      fprintf(stderr,
        "\nError: access to %s is denied.\n\n", basepath.AsString().c_str());
      exit(1);
    }
    else if (code != vtkDICOMFileDirectory::FileNotFound)
    {
      fprintf(stderr,
        "\nError: %s is not a valid directory.\n\n",
        basepath.AsString().c_str());
      exit(1);
    }
    basepath.PopBack();
  }

  // see if we can write to the directory
  if (vtkDICOMFileDirectory::Access(basepath.AsString().c_str(),
                                    vtkDICOMFileDirectory::Out) != 0)
  {
    fprintf(stderr,
      "\nError: Cannot write to %s\n\n", basepath.AsString().c_str());
    exit(1);
  }

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
    finder->SetDefaultCharacterSet(charset);
    finder->SetInputFileNames(a);
    finder->SetFilePattern(pattern);
    finder->SetScanDepth(scandepth);
    finder->SetFindQuery(query);
    finder->SetIgnoreDicomdir(ignoreDicomdir);
    finder->SetFollowSymlinks(followSymlinks);
    finder->SetRequirePixelData(requirePixelData);
    finder->SetFindLevel(
      findSeries ? vtkDICOMDirectory::SERIES : vtkDICOMDirectory::IMAGE);

    vtkSmartPointer<ProgressObserver> p =
      vtkSmartPointer<ProgressObserver>::New();
    if (!silent)
    {
      p->SetText("Scanning");
      finder->AddObserver(vtkCommand::ProgressEvent, p);
      finder->AddObserver(vtkCommand::StartEvent, p);
      finder->AddObserver(vtkCommand::EndEvent, p);
    }
    finder->Update();

    vtkIdType count = 0;
    vtkIdType total = 0;
    if (!silent)
    {
      p->SetText("Copying");
      p->Execute(NULL, vtkCommand::StartEvent, NULL);
      for (int k = 0; k < finder->GetNumberOfSeries(); k++)
      {
        total += finder->GetFileNamesForSeries(k)->GetNumberOfValues();
      }
    }

    for (int j = 0; j < finder->GetNumberOfStudies(); j++)
    {
      int k0 = finder->GetFirstSeriesForStudy(j);
      int k1 = finder->GetLastSeriesForStudy(j);

      for (int k = k0; k <= k1; k++)
      {
        vtkStringArray *sa = finder->GetFileNamesForSeries(k);
        vtkDICOMMetaData *meta = finder->GetMetaDataForSeries(k);
        // create the directory name
        std::string dirname = dicompull_makedirname(meta, outdir.c_str());
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
          int code = vtkDICOMFileDirectory::Create(dirname.c_str());
          if (code != vtkDICOMFileDirectory::Good)
          {
            fprintf(stderr, "Error: Cannot create directory: %s\n\n",
                    dirname.c_str());
            delete [] buffer;
            exit(1);
          }
        }
        vtkDICOMFilePath outpath(dirname);
        for (vtkIdType i = 0; i < sa->GetNumberOfValues(); i++)
        {
          // copy the file
          char fname[32];
          sprintf(fname, "IM-%04d-%04d.dcm", si, static_cast<int>(i+1));
          const std::string& srcname = sa->GetValue(i);
          std::string fullname = outpath.Join(fname);
          if (!vtkDICOMFile::SameFile(srcname.c_str(), fullname.c_str()))
          {
            vtkDICOMFile infile(srcname.c_str(), vtkDICOMFile::In);
            if (infile.GetError())
            {
              const char *message = "Missing file";
              switch (infile.GetError())
              {
                case vtkDICOMFile::AccessDenied:
                  message = "Access denied for file";
                  break;
                case vtkDICOMFile::FileIsDirectory:
                  message = "This file is a directory";
                  break;
                case vtkDICOMFile::ImpossiblePath:
                  message = "Bad file path";
                  break;
              }
              dicomcli_error_helper(finder->GetMetaDataForSeries(k), i);
              fprintf(stderr, "Error: %s: %s\n\n", message, srcname.c_str());
            }
            else if (infile.GetSize() == 0)
            {
              dicomcli_error_helper(finder->GetMetaDataForSeries(k), i);
              fprintf(stderr, "Error: File size is zero: %s\n\n",
                      srcname.c_str());
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
                  case vtkDICOMFile::FileIsDirectory:
                    message = "This output is a directory";
                    break;
                  case vtkDICOMFile::ImpossiblePath:
                    message = "Bad file path";
                    break;
                }
                fprintf(stderr, "Error: %s: %s\n\n", message, fullname.c_str());
              }
              else
              {
                // copy the file
                while (!infile.EndOfFile())
                {
                  size_t bytecount = infile.Read(buffer, bufsize);
                  if (bytecount == 0 && infile.GetError())
                  {
                    dicomcli_error_helper(finder->GetMetaDataForSeries(k), i);
                    fprintf(stderr, "Error, incomplete read: %s\n\n",
                            srcname.c_str());
                    vtkDICOMFile::Remove(fullname.c_str());
                    break;
                  }
                  if (bytecount > 0 &&
                      outfile.Write(buffer, bytecount) != bytecount)
                  {
                    fprintf(stderr, "Error: Incomplete write: %s\n\n",
                            fullname.c_str());
                    vtkDICOMFile::Remove(fullname.c_str());
                    break;
                  }
                }
              }
            }
          }

          if (!silent)
          {
            count++;
            double progress = (static_cast<double>(count)/
                               static_cast<double>(total));
            p->Execute(NULL, vtkCommand::ProgressEvent, &progress);
          }
        }
      }
    }
    delete [] buffer;
    if (!silent)
    {
      p->Execute(NULL, vtkCommand::EndEvent, NULL);
    }
  }

  return rval;
}
