/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMFileDirectory_h
#define vtkDICOMFileDirectory_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h" // For export macro

#include <string> // Interface type

//! A class that provides directory listings.
class VTKDICOM_EXPORT vtkDICOMFileDirectory
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
  vtkDICOMFileDirectory(const char *dirname);

  //! Copy constructor.
  vtkDICOMFileDirectory(const vtkDICOMFileDirectory&);

  //! Destruct the object.
  ~vtkDICOMFileDirectory();
  //@}

  //@{
  //! Return an error indicator (zero if no error).
  int GetError() { return this->Error; }
  //@}

  //@{
  //! Get the number of files and subdirectories in the directory.
  int GetNumberOfFiles() { return this->NumberOfFiles; }

  //! Get the name of the ith file or subdirectory.
  const char *GetFile(int i);

  //! Check if the list entry is a directory.
  bool IsDirectory(int i);

  //! Check if the list entry is special (a device, socket, or pipe).
  bool IsSpecial(int i);

  //! Check if the list entry is a symbolic link.
  bool IsSymlink(int i);

  //! Check if the list entry has an attribute that marks it as hidden.
  bool IsHidden(int i);
  //@}

  //@{
  //! Create a new directory with default permissions.
  /*!
   *  This will create any intermediate directories, as well.  The return
   *  value is zero for success.  Otherwise, one of the error codes is
   *  returned.
   */
  static int Create(const char *dirname);
  //@}

  //@{
  //! Assignment operator.
  vtkDICOMFileDirectory& operator=(const vtkDICOMFileDirectory&);
  //@}

private:
  //! Add a directory entry.
  void AddEntry(const char *name, unsigned short flags, unsigned short mask);

  //! Call stat() on a file to set flags
  void StatEntry(int i);

  //! Call lstat() on a file to set flags
  void LinkStatEntry(int i);

  struct Entry;
  static const unsigned int TypeDirectory = 1;
  static const unsigned int TypeSpecial = 2;
  static const unsigned int TypeSymlink = 4;
  static const unsigned int TypeHidden = 8;

  std::string Name;
  int Error;
  int NumberOfFiles;
  Entry *Entries;
};

#endif /* vtkDICOMFileDirectory_h */
// VTK-HeaderTest-Exclude: vtkDICOMFileDirectory.h
