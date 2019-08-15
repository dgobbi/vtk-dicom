/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMFileWalker_h
#define vtkDICOMFileWalker_h

#include "vtkSystemIncludes.h"
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMConfig.h" // For configuration details

#include <string> // Interface type

class vtkDICOMFileDirectory;

//! A class that provides directory listings.
class VTKDICOM_EXPORT vtkDICOMFileWalker
{
public:

  //! Error codes.
  enum Code
  {
    Good,              // no error
    UnknownError,      // unspecified error
    AccessDenied,      // file permission error
    Reserved,
    ImpossiblePath,    // part of the path doesn't exist or goes through a file
    FileNotFound,      // requested file (or directory) doesn't exist
    OutOfSpace         // disk full or quota exceeded
  };

  //@{
  //! Construct the object from a directory name.
  /*!
   *  This causes the directory to be read.  Use GetError() to check whether
   *  the read was successful.
   */
  vtkDICOMFileWalker(const char *dirname);

  //! Copy constructor.
  vtkDICOMFileWalker(const vtkDICOMFileWalker&);

  //! Destruct the object.
  ~vtkDICOMFileWalker();
  //@}

  //@{
  //! Assignment operator. XXX is this just for python wrapping?
  vtkDICOMFileWalker& operator=(const vtkDICOMFileWalker&);
  //@}

  //! Go to the next directory.
  void Next();

  //! Returns true when done.
  // XXX alternatively, 'done' could be an error code for GetError().
  bool Done();

  //! Return an error indicator (zero if no error).
  // XXX should it be possible to continue when an error occurs?
  // XXX yes, errors like read-protected directories are not fatal.
  // XXX how to continue after an error? call Next?
  int GetError();

  //! Get the directory at the current search point.
  vtkDICOMFileDirectory& GetDirectory();

  //! Get the directory at the current search point.
  // XXX maybe vtkDICOMFileDirectory should have this method?
  std::string GetPath();

  //! Do not descend into this directory.
  void Prune();

  //! Whether to follow symbolic links.
  void SetFollowSymlinks(bool tf) { this->FollowSymlinks = tf; }
  bool GetFollowSymlinks() { return this->FollowSymlinks; }


private:

  class DirectoryStack;

  DirectoryStack *Stack;
  vtkDICOMFileDirectory *Directory;
  bool FollowSymlinks;
};

/*
basic usage for vtkDICOMDirectory:

start with filenamevec

group into files and directories

handle the files (special if .sql)

for dir in directories:

   create a walker

   for path, files, dirs in walker:

       if has DICOMDIR:

           handle DICOMDIR      

       else:

           handle the files


PROBLEM: if DICOMDIR, then we don't want to recurse further,
but there is no way for a generic walker to know this.

Since I have already decided to do a top-down walk, my
walker could have a method that would tell it to prune the
search, i.e. to go no deeper than the current directory.

*/

#endif /* vtkDICOMFileWalker_h */
// VTK-HeaderTest-Exclude: vtkDICOMFileWalker.h
