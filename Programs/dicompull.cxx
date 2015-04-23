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

// from dicomcli
#include "mainmacro.h"
#include "readquery.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <limits>
#include <iostream>

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
    "  -maxdepth n     Set the maximum directory depth.\n"
    "  -name pattern   Set a pattern to match (with \"*\" or \"?\").\n"
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
    "This command can be used to locate DICOM files.  It shares many\n"
    "features with the UNIX \"find\" command.  When searching for files\n"
    "with a specific attribute (with \"-k\"), the tag can be specified\n"
    "in the form GGGG,EEEE or with its canonical name e.g. Modality=MR\n"
    "from the DICOM dictionary.  Alternately, the tags can be listed in a\n"
    "query file given with the \"-q\" option (one tag per line).\n"
    "Attributes nested within sequences can be specified by giving a tag\n"
    "path e.g. \"-k Tag1/Tag2/Tag3\".  Either a forward slash or a backslash\n"
    "can be used to separate the components of the path.  Private tags\n"
    "should be preceded by the private dictionary name in square brackets.\n"
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

// The type used to store an operation
struct Operation
{
  Operation(const char *type) : Type(type) {}

  std::string Type;
  std::vector<std::string> Args;
};

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

  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();
  const char *qfile = 0;

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
      qfile = argv[++argi];
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

  // read the query file, create a query
  if (qfile && !dicomcli_readquery(qfile, &query, &qtlist))
    {
    fprintf(stderr, "Can't read query file %s\n\n", qfile);
    return 1;
    }

  // always add the functional sequences for advanced files
  query.SetAttributeValue(
    DC::SharedFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));
  query.SetAttributeValue(
    DC::PerFrameFunctionalGroupsSequence, vtkDICOMValue(VR::SQ));

  // Write data for every input directory
  if (a->GetNumberOfTuples() > 0)
    {
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
    finder->Update();

    for (int j = 0; j < finder->GetNumberOfStudies(); j++)
      {
      int k0 = finder->GetFirstSeriesForStudy(j);
      int k1 = finder->GetLastSeriesForStudy(j);

      for (int k = k0; k <= k1; k++)
        {
        vtkStringArray *sa = finder->GetFileNamesForSeries(k);
        // do stuff here
        }
      }
    }

  return rval;
}
