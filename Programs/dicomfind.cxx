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
#include "readquery.h"

#include <vtkStringArray.h>
#include <vtkSmartPointer.h>

#ifndef _WIN32
// includes for execvp
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#else
// include for spawn
#include <process.h>
// include for getcwd
#include <direct.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <limits>
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
    "  %s [options] <directory> ...\n\n", cp);
  fprintf(file, "options:\n"
    "  -L              Follow symbolic links (default).\n"
    "  -P              Do not follow symbolic links.\n"
    "  -k tag=value    Provide an attribute to be queried and matched.\n"
    "  -q <query.txt>  Provide a file to describe the find query.\n"
    "  -maxdepth n     Set the maximum directory depth.\n"
    "  -name pattern   Set a pattern to match (with \"*\" or \"?\").\n"
    "  -image          Restrict the search to files with PixelData.\n"
    "  -print          Print the filenames of all matched files (default).\n"
    "  -print0         Print the filenames with terminating null, for xargs.\n"
    "  -exec ... +     Execute the given command for every series matched.\n"
    "  -exec ... %s    Execute the given command for every file matched.\n"
    "  -execdir ... +  Go to directory and execute command on every series.\n"
    "  -execdir ... %s Go to directory and execute command on every file.\n"
    "  --help          Print a brief help message.\n"
    "  --version       Print the software version.\n",
#ifndef _WIN32
    "\\;", "\\;"
#else
    "; ", "; "
#endif
    );
}

// print the help
void dicomfind_help(FILE *file, const char *cp)
{
  dicomfind_usage(file, cp);
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
    "The \"-exec\" and \"-execdir\" arguments cause dicomfind to run the\n"
    "specified program on the found files.  For example, to dump each file\n"
    "one would use \"-exec dicomdump {} \\;\" where each instance of {} will\n"
    "be replaced by a found file, and \";\" indicates the end of the args\n"
    "to dicomdump.  Alternately, if \"+\" is used to end the args, then the\n"
    "program will be run on each DICOM series and {} will be replaced by all\n"
    "files in the series.  The \"-execdir\" argument is similar, except that\n"
    "it runs the program from within the directory of the file (or files),\n"
    "and {} is replaced by just the filenames instead of with the full paths.\n\n");

}

// remove path portion of filename
const char *dicomfind_basename(const char *filename)
{
  const char *cp = filename + strlen(filename);
  while (cp != filename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  return cp;
}

// get directory portion of filename
std::string dicomfind_dirname(const char *filename)
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
  // flush the output
  fflush(stdout);
  fflush(stderr);

  if (_spawnvp(_P_WAIT, command, argv) != 0)
    {
    if (errno == ENOENT)
      {
      fprintf(stderr, "Executable not found: %s\n", argv[0]);
      }
    else if (errno == ENOEXEC)
      {
      fprintf(stderr, "File is not executable: %s\n", argv[0]);
      }
    else if (errno == E2BIG)
      {
      fprintf(stderr, "Command line to long for command: %s\n", argv[0]);
      }
    else if (errno == ENOMEM)
      {
      fprintf(stderr, "Out of memory while running command: %s\n", argv[0]);
      }
    else
      {
      fprintf(stderr, "Unknown error while running command: %s\n", argv[0]);
      }

    return false;
    }

  return true;
}
#endif

#ifndef _WIN32
int dicomfind_chdir(const char *dirname)
{
  return chdir(dirname);
}
#else
int dicomfind_chdir(const char *dirname)
{
  // use _wchdir to allow paths longer than the 260 char limit
  return _chdir(dirname);
}
#endif

#ifndef _WIN32
const char *dicomfind_getcwd(char *buffer, size_t bufsize)
{
  return getcwd(buffer, bufsize);
}
#else
const char *dicomfind_getcwd(char *buffer, size_t bufsize)
{
  return _getcwd(buffer, bufsize);
}
#endif

// This program will dump all the metadata in the given file
int main(int argc, char *argv[])
{
  int rval = 0;
  int scandepth = std::numeric_limits<int>::max();
  bool followSymlinks = true;
  const char *pattern = "";
  QueryTagList qtlist;
  vtkDICOMItem query;
  std::vector<std::string> exec_args;
  bool execdir = false;
  bool print0 = false;
  bool requirePixelData = false;

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
    else if (strcmp(arg, "-q") == 0)
      {
      if (argi + 1 == argc || argv[argi+1][0] == '-')
        {
        fprintf(stderr, "%s must be followed by a file.\n\n", arg);
        dicomfind_usage(stderr, dicomfind_basename(argv[0]));
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
    else if (strcmp(arg, "-print") == 0)
      {
      // do nothing, is default
      }
    else if (strcmp(arg, "-print0") == 0)
      {
      print0 = true;
      }
    else if (strcmp(arg, "-exec") == 0 ||
             strcmp(arg, "-execdir") == 0)
      {
      if (strcmp(arg, "-execdir") == 0)
        {
        execdir = true;
        }
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
        exec_args.push_back(argv[argi]);
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

  // Remember the current directory
  std::string originalDir;
  std::string currentSubdir;
  if (execdir)
    {
    char buf[2048];
    originalDir = dicomfind_getcwd(buf, 2048);
    }

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
    finder->Update();

    if (!exec_args.empty())
      {
      size_t subcount = 0;
      for (size_t jj = 0; jj < exec_args.size(); jj++)
        {
        subcount += (exec_args[jj] == "{}");
        }

      for (int j = 0; j < finder->GetNumberOfStudies(); j++)
        {
        int k0 = finder->GetFirstSeriesForStudy(j);
        int k1 = finder->GetLastSeriesForStudy(j);
        for (int k = k0; k <= k1; k++)
          {
          vtkStringArray *sa = finder->GetFileNamesForSeries(k);

          if (exec_args.back() == ";")
            {
            // call program for each file
            for (int kk = 0; kk < sa->GetNumberOfValues(); kk++)
              {
              size_t sub_argc = exec_args.size() + subcount - 1;
              char **sub_argv = new char *[sub_argc+1];

              size_t ii = 0;
              size_t nn = exec_args.size()-1;
              for (size_t jj = 0; jj < nn; jj++)
                {
                if (exec_args[jj] == "{}")
                  {
                  if (execdir)
                    {
                    sub_argv[ii++] = const_cast<char *>(
                      dicomfind_basename(sa->GetValue(kk).c_str()));
                    }
                  else
                    {
                    sub_argv[ii++] = const_cast<char *>(
                      sa->GetValue(kk).c_str());
                    }
                  }
                else
                  {
                  sub_argv[ii++] = const_cast<char *>(exec_args[jj].c_str());
                  }
                }
              sub_argv[ii] = 0;

              if (execdir)
                {
                std::string dirname =
                  dicomfind_dirname(sa->GetValue(kk).c_str());
                if (dirname != currentSubdir)
                  {
                  dicomfind_chdir(originalDir.c_str());
                  dicomfind_chdir(dirname.c_str());
                  }
                }

              if (!execute_command(sub_argv[0], sub_argv))
                {
                fprintf(stderr, "failure!");
                }

              delete [] sub_argv;
              }

            if (execdir && currentSubdir != "")
              {
              dicomfind_chdir(originalDir.c_str());
              }
            }
          else
            {
            // call program for each series
            // for execdir, what if series is split across directories? need to
            // call executable once per directory, using only the files in that
            // directory.
            size_t sub_argc = exec_args.size() +
              subcount*sa->GetNumberOfTuples() - 1;
            char **sub_argv = new char *[sub_argc+1];

            // for execdir, keep a list of directories that are done
            std::vector<std::string> done_dirs;
            std::string doing_dir;
            
            bool notdone = true;

            while (notdone)
              {
              notdone = false;
              if (execdir)
                {
                bool foundDirToProcess = false;
                for (vtkIdType kk = 0; kk < sa->GetNumberOfValues(); kk++)
                  {
                  std::string dirname =
                    dicomfind_dirname(sa->GetValue(kk).c_str());
                  if (!foundDirToProcess)
                    {
                    bool dirIsDone = false;
                    for (size_t ll = 0; ll < done_dirs.size(); ll++)
                      {
                      if (dirname == done_dirs[ll])
                        {
                        dirIsDone = true;
                        break;
                        }
                      }
                    if (!dirIsDone)
                      {
                      foundDirToProcess = true;
                      doing_dir = dirname;
                      done_dirs.push_back(dirname);
                      break;
                      }
                    }
                  }
                if (foundDirToProcess)
                  {
                  notdone = true;
                  }
                else
                  {
                  break;
                  }
                }

              size_t ii = 0;
              size_t nn = exec_args.size()-1;
              for (size_t jj = 0; jj < nn; jj++)
                {
                if (exec_args[jj] == "{}")
                  {
                  if (execdir)
                    {
                    for (vtkIdType kk = 0; kk < sa->GetNumberOfValues(); kk++)
                      {
                      std::string dirname =
                        dicomfind_dirname(sa->GetValue(kk).c_str());
                      if (dirname == doing_dir)
                        {
                        sub_argv[ii++] = const_cast<char *>(
                          dicomfind_basename(sa->GetValue(kk).c_str()));
                        }
                      }
                    }
                  else
                    {
                    for (vtkIdType kk = 0; kk < sa->GetNumberOfValues(); kk++)
                      {
                      sub_argv[ii++] = const_cast<char *>(
                        sa->GetValue(kk).c_str());
                      }
                    }
                  }
                else
                  {
                  sub_argv[ii++] = const_cast<char *>(exec_args[jj].c_str());
                  }
                }
              sub_argv[ii] = 0;

              if (execdir)
                {
                if (doing_dir != currentSubdir)
                  {
                  dicomfind_chdir(originalDir.c_str());
                  dicomfind_chdir(doing_dir.c_str());
                  }
                }

              if (!execute_command(sub_argv[0], sub_argv))
                {
                fprintf(stderr, "failure!");
                }
              }

            if (execdir && currentSubdir != "")
              {
              dicomfind_chdir(originalDir.c_str());
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
        char endchar = (print0 ? '\0' : '\n');
        for (int k = k0; k <= k1; k++)
          {
          vtkStringArray *sa = finder->GetFileNamesForSeries(k);
          for (int kk = 0; kk < sa->GetNumberOfValues(); kk++)
            {
            std::cout << sa->GetValue(kk);
            std::cout.put(endchar);
            }
          }
        }
      }

    std::cout.flush();
    }

  return rval;
}
