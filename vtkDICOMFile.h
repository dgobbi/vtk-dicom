/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMFile_h
#define __vtkDICOMFile_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMModule.h"

#if !defined(_WIN32)
#define VTK_DICOM_POSIX_IO
#endif

//! A class that provides basic input/output operations.
/*!
 *  The purpose of this class is to centralize all of the I/O operations.
 *  It is intended to use system-level I/O calls so that it can eventually
 *  be used not only on files, but on sockets as well.
 */
class VTK_DICOM_EXPORT vtkDICOMFile
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
    Good,
    Bad,
    Access,
    IsDir
  };

  //! Typedef for a file offset.
  typedef long long Offset;

  //! Construct the file object.
  /*!
   *  The Mode can be "In" or "Out" (read or write).
   */
  vtkDICOMFile(const char *filename, Mode mode);

  //! Destruct the object and close the file.
  ~vtkDICOMFile();

  //! Close a file.
  void Close();

  //! Read data from the file.
  /*!
   *  The number of bytes read will be returned.
   *  A return value of zero indicates an error.
   */
  size_t Read(char *data, size_t size);

  //! Write data to a file.
  /*!
   *  The number of bytes written will be returned.
   *  If it is less than the size requested, an error ocurred.
   */
  size_t Write(const char *data, size_t size);

  //! Seek to a specific location in the file.
  /*!
   *  The return value is false (1) if an error occurred.
   */
  bool Seek(Offset offset);

  //! Check for the end-of-file indicator.
  bool EndOfFile() { return this->Eof; }

  //! Return an error indicator (zero if no error).
  int GetError() { return this->Error; }

private:
#ifdef VTK_DICOM_POSIX_IO
  int Handle;
#else
  void *Handle;
#endif
  int Error;
  bool Eof;
};

#endif /* __vtkDICOMFile_h */
