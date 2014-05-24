/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMFile.h"

#ifdef VTK_DICOM_POSIX_IO
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#else
#include <stdio.h>
#endif

//----------------------------------------------------------------------------
vtkDICOMFile::vtkDICOMFile(const char *filename, Mode mode)
{
#ifdef VTK_DICOM_POSIX_IO
  this->Handle = -1;
  this->Error = 0;
  this->Eof = false;

  if (mode == In)
    {
    this->Handle = open(filename, O_RDONLY);
    }
  else if (mode == Out)
    {
    this->Handle = open(filename, O_WRONLY | O_CREAT, 000066);
    }

  if (this->Handle == -1)
    {
    if (errno == EACCES)
      {
      this->Error = Access;
      }
    else if (errno == EISDIR)
      {
      this->Error = IsDir;
      }
    else
      {
      this->Error = Bad;
      }
    }
#else
  this->Handle = 0;
  this->Error = 0;
  this->Eof = false;

  if (mode == In)
    {
    this->Handle = fopen(filename, "rb");
    }
  else if (mode == Out)
    {
    this->Handle = fopen(filename, "wb");
    }
  if (this->Handle == 0)
    {
    this->Error = Bad;
    }
#endif
}

//----------------------------------------------------------------------------
vtkDICOMFile::~vtkDICOMFile()
{
  this->Close();
}

//----------------------------------------------------------------------------
void vtkDICOMFile::Close()
{
#ifdef VTK_DICOM_POSIX_IO
  if (this->Handle)
    {
    if (close(this->Handle) == 0)
      {
      this->Error = 0;
      }
    else if (errno != EINTR)
      {
      this->Error = Bad;
      }
    this->Handle = 0;
    }
#else
  fclose(static_cast<FILE *>(this->Handle));
#endif
}

//----------------------------------------------------------------------------
size_t vtkDICOMFile::Read(char *data, size_t len)
{
#ifdef VTK_DICOM_POSIX_IO
  ssize_t n;
  while ((n = read(this->Handle, data, len)) == -1)
    {
    if (errno != EINTR)
      {
      break;
      }
    }
  if (n == 0)
    {
    this->Eof = true;
    }
  else if (n == -1)
    {
    this->Error = Bad;
    n = 0;
    }
  return n;
#else
  size_t n = fread(data, 1, len, static_cast<FILE *>(this->Handle));
  this->Eof = (feof(static_cast<FILE *>(this->Handle)) != 0);
  this->Error = (ferror(static_cast<FILE *>(this->Handle)) == 0 ? Good : Bad);
  return n;
#endif
}

//----------------------------------------------------------------------------
size_t vtkDICOMFile::Write(const char *data, size_t len)
{
#ifdef VTK_DICOM_POSIX_IO
  ssize_t n;
  while ((n = write(this->Handle, data, len)) == -1)
    {
    if (errno != EINTR)
      {
      break;
      }
    }
  if (n == -1)
    {
    this->Error = Bad;
    n = 0;
    }
  return n;
#else
  size_t n = fwrite(data, 1, len, static_cast<FILE *>(this->Handle));
  this->Error = (ferror(static_cast<FILE *>(this->Handle)) == 0 ? Good : Bad);
  return n;
#endif
}

//----------------------------------------------------------------------------
bool vtkDICOMFile::Seek(Offset offset)
{
#ifdef VTK_DICOM_POSIX_IO
#if defined(__linux__) && defined(_LARGEFILE64_SOURCE)
  off64_t pos = lseek64(this->Handle, offset, SEEK_SET);
#else
  off_t pos = lseek(this->Handle, offset, SEEK_SET);
#endif
  if (pos == -1)
    {
    this->Error = Bad;
    return false;
    }
  return true;
#else
  return (fseek(static_cast<FILE *>(this->Handle), offset, SEEK_SET) == 0);
#endif
}
