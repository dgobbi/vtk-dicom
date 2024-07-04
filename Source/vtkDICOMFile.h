/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2024 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMFile_h
#define vtkDICOMFile_h

#include "vtkSystemIncludes.h"
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMConfig.h" // For configuration details

#if defined(_WIN32)
#define VTK_DICOM_WIN32_IO
#else
#define VTK_DICOM_POSIX_IO
#endif

//! A class that provides basic input/output operations.
/*!
 *  The purpose of this class is to centralize all of the I/O operations.
 *  It uses system-level I/O calls so that it can eventually be used not
 *  only on files, but on sockets as well.
 */
class VTKDICOM_EXPORT vtkDICOMFile
{
public:
  //! The file mode (input or output).
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
    FileIsDirectory,   // can't open file: directory with that name exists
    ImpossiblePath,    // part of the path doesn't exist or goes through a file
    FileNotFound,      // requested file (or directory) doesn't exist
    OutOfSpace         // disk full or quota exceeded
  };

  //! Typedef for a file size.
  typedef unsigned long long Size;

  //@{
  //! Construct the file object.
  /*!
   *  The Mode can be "In" or "Out" (read or write).
   */
  vtkDICOMFile(const char *filename, Mode mode);

  //! Destruct the object and close the file.
  ~vtkDICOMFile();
  //@}

  //@{
  //! Close a file.
  void Close();

  //! Read data from the file.
  /*!
   *  The number of bytes read will be returned.
   *  A return value of zero indicates an error.
   */
  size_t Read(unsigned char *data, size_t size);

  //! Write data to a file.
  /*!
   *  The number of bytes written will be returned.
   *  If it is less than the size requested, an error occurred.
   */
  size_t Write(const unsigned char *data, size_t size);

  //! Go to a specific location in the file.
  /*!
   *  The return value is false if an error occurred.
   */
  bool SetPosition(Size offset);

  //! Check the size of the file, returns ULLONG_MAX on error.
  Size GetSize();

  //! Check for the end-of-file indicator.
  bool EndOfFile() { return this->Eof; }

  //! Return an error indicator (zero if no error).
  int GetError() { return this->Error; }
  //@}

  //@{
  //! Test the specified file for accessibility (static method).
  /*!
   *  The mode should be "In" or "Out" to indicate how you intend to use
   *  the file.  The return value will be zero (for an ordinary file) or
   *  one of the codes returned by GetError.
   */
  static int Access(const char *filename, Mode mode);

  //! Delete the specified file (static method).
  /*!
   *  The return value is zero if successful, otherwise an error
   *  code is returned.  This can be called on a file that is still
   *  open, in which case the file will be deleted when closed.
   */
  static int Remove(const char *filename);

  //! Check if two files are the same.
  /*!
   *  This does not check that the filenames are the same.  Instead,
   *  it checks to see if the two filenames point to the same actual
   *  disk file.  If either file does not exist or is otherwise not
   *  accessible, then it returns false.
   */
  static bool SameFile(const char *file1, const char *file2);
  //@}

  //! @cond
  // Copy constructor creates a closed file.  The copy constructor would
  // normally be deleted, but that would cause the VTK python wrappers to
  // skip this class.  Once the wrappers are fixed, this can be deleted.
  vtkDICOMFile(const vtkDICOMFile&) : Handle(0), Error(0), Eof(false) {}
  //! @endcond

private:
  vtkDICOMFile& operator=(const vtkDICOMFile&); // = delete;

#ifdef VTK_DICOM_POSIX_IO
  int Handle;
#else
  void *Handle;
#endif
  int Error;
  bool Eof;
};

#endif /* vtkDICOMFile_h */
// VTK-HeaderTest-Exclude: vtkDICOMFile.h
