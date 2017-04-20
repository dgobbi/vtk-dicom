/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2017 David Gobbi
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
  //! The access mode (input or output).
  enum Mode
  {
    In,
    Out
  };

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
  int GetNumberOfEntries() { return this->NumberOfEntries; }

  //! Get the name of the ith file or subdirectory.
  /*!
   *  The entries do not include "." or "..".
   */
  const char *GetEntry(int i);

  //! Check if the list entry is a directory.
  bool IsDirectory(int i);

  //! Check if the list entry is special (a device, socket, or pipe).
  bool IsSpecial(int i);

  //! Check if the list entry is a symbolic link.
  bool IsSymlink(int i);

  //! Check if the list entry is a symbolic link that is broken.
  /*!
   *  A link is broken if it points to a location that does not exist,
   *  or to a location that is in a directory that cannot be accessed.
   *  IsSymlink() will always be true if IsBroken() is true.
   */
  bool IsBroken(int i);

  //! Check if the list entry has an attribute that marks it as hidden.
  bool IsHidden(int i);
  //@}

  //@{
  //! Test a directory for accessibility (static method).
  /*!
   *  The mode should be "In" or "Out" to indicate whether you intend to
   *  read from or write to the directory.  A return value of zero means
   *  the directory can be accessed, otherwise an error code will be
   *  returned.
   */
  static int Access(const char *dirname, Mode mode);

  //! Create a new directory with default permissions (static method).
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
  static const unsigned int TypeBroken = 8;
  static const unsigned int TypeHidden = 16;

  std::string Name;
  int Error;
  int NumberOfEntries;
  Entry *Entries;
};

#endif /* vtkDICOMFileDirectory_h */
// VTK-HeaderTest-Exclude: vtkDICOMFileDirectory.h
