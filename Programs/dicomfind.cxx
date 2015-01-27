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
    "  -L              Follow symbolic links (default).\n"
    "  -P              Do not follow symbolic links.\n"
    "  -k tag=value    Provide a key to be queried and matched.\n"
    "  -q <query.txt>  Provide a file to describe the find query.\n"
    "  -maxdepth n     Set the maximum directory depth.\n"
    "  -name pattern   Set a pattern to match (with \"*\" or \"?\").\n"
    "  -exec ... +     Execute the given command for every series matched.\n"
    "  -exec ... \\;   Execute the given command for every file matched.\n"
    "  --help          Print a brief help message.\n"
    "  --version       Print the software version.\n");
}

// print the help
void dicomfind_help(FILE *file, const char *cp)
{
  dicomfind_usage(file, cp);
  fprintf(file, "\n"
    "Locate DICOM files within nested directories.\n");
}

// remove path portion of filename
const char *dicomfind_basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

typedef vtkDICOMVR VR;

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
  int scandepth = 8;
  bool followSymlinks = true;
  const char *pattern = "";
  QueryTagList qtlist;
  vtkDICOMItem query;
  std::vector<std::string> oplist;

  vtkSmartPointer<vtkStringArray> a = vtkSmartPointer<vtkStringArray>::New();
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
    if (strcmp(arg, "-P") == 0)
      {
      followSymlinks = false;
      }
    else if (strcmp(arg, "-L") == 0)
      {
      followSymlinks = true;
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
    finder->SetFileNames(a);
    finder->SetFilePattern(pattern);
    finder->SetScanDepth(scandepth);
    finder->SetFindQuery(query);
    finder->SetFollowSymlinks(followSymlinks);
    finder->Update();

    if (!oplist.empty())
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
            std::cout << sa->GetValue(kk) << "\n";
            }
          }
        }
      }

    std::cout.flush();
    }

  return rval;
}
