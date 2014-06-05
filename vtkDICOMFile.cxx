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

#if defined(VTK_DICOM_POSIX_IO)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#elif defined(VTK_DICOM_WIN32_IO)
#include <windows.h>
#else
#include <stdio.h>
#endif

//----------------------------------------------------------------------------
vtkDICOMFile::vtkDICOMFile(const char *filename, Mode mode)
{
#if defined(VTK_DICOM_POSIX_IO)
  this->Handle = -1;
  this->Error = 0;
  this->Eof = false;

  if (mode == In)
    {
    this->Handle = open(filename, O_RDONLY);
    }
  else if (mode == Out)
    {
    this->Handle = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 000666);
    }

  if (this->Handle == -1)
    {
    int errorCode = errno;
    if (errorCode == EACCES)
      {
      this->Error = AccessDenied;
      }
    else if (errorCode == EISDIR)
      {
      this->Error = IsDirectory;
      }
    else if (errorCode == ENOTDIR)
      {
      this->Error = DirectoryNotFound;
      }
    else if (errorCode == ENOENT)
      {
      this->Error = FileNotFound;
      }
    else if (errorCode == ENOSPC)
      {
      // some systems also have EDQUOT for "quota exceeded"
      this->Error = OutOfSpace;
      }
    else
      {
      this->Error = Bad;
      }
    }
#elif defined(VTK_DICOM_WIN32_IO)
  this->Handle = INVALID_HANDLE_VALUE;
  this->Error = 0;
  this->Eof = false;

  WCHAR *wideFilename = 0;
  int n = MultiByteToWideChar(
    CP_UTF8, MB_ERR_INVALID_CHARS, filename, -1, NULL, 0);
  if (n > 0)
    {
    wideFilename = new WCHAR[n];
    n = MultiByteToWideChar(
      CP_UTF8, MB_ERR_INVALID_CHARS, filename, -1, wideFilename, n);

    if (mode == In)
      {
      this->Handle = CreateFileW(wideFilename,
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      }
    else if (mode == Out)
      {
      this->Handle = CreateFileW(wideFilename,
        GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
      }
    }

  delete [] wideFilename;

  if (this->Handle == INVALID_HANDLE_VALUE)
    {
    DWORD errorCode = GetLastError();
    if (errorCode == ERROR_ACCESS_DENIED ||
        errorCode == ERROR_SHARING_VIOLATION)
      {
      this->Error = AccessDenied;
      }
    else if (errorCode == ERROR_DIRECTORY)
      {
      this->Error = DirectoryNotFound;
      }
    else if (errorCode == ERROR_FILE_NOT_FOUND)
      {
      this->Error = FileNotFound;
      }
    else if (errorCode == ERROR_DISK_FULL)
      {
      this->Error = OutOfSpace;
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
#if defined(VTK_DICOM_POSIX_IO)
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
#elif defined(VTK_DICOM_WIN32_IO)
  CloseHandle(this->Handle);
  this->Handle = INVALID_HANDLE_VALUE;
#else
  if (this->Handle)
    {
    fclose(static_cast<FILE *>(this->Handle));
    }
  this->Handle = 0;
#endif
}

//----------------------------------------------------------------------------
size_t vtkDICOMFile::Read(char *data, size_t len)
{
#if defined(VTK_DICOM_POSIX_IO)
  ssize_t n;
  while ((n = read(this->Handle, data, len)) == -1)
    {
    if (errno != EINTR)
      {
      break;
      }
    errno = 0;
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
#elif defined(VTK_DICOM_WIN32_IO)
  // handle large requests in 1GB chunks
  const size_t chunksize = 1024*1024*1024;
  size_t n = 0;
  while (n < len)
    {
    DWORD l = static_cast<DWORD>(len - n < chunksize ? len - n : chunksize);
    DWORD r = 0;
    if (ReadFile(this->Handle, &data[n], l, &r, NULL) == FALSE)
      {
      this->Error = Bad;
      break;
      }
    else if (r == 0)
      {
      this->Eof = true;
      break;
      }
    n += r;
    }
  return n;
#else
  size_t n = fread(data, 1, len, static_cast<FILE *>(this->Handle));
  if (n != len || len == 0)
    {
    this->Eof = (feof(static_cast<FILE *>(this->Handle)) != 0);
    this->Error = (ferror(static_cast<FILE *>(this->Handle)) == 0 ? 0 : Bad);
    }
  return n;
#endif
}

//----------------------------------------------------------------------------
size_t vtkDICOMFile::Write(const char *data, size_t len)
{
#if defined(VTK_DICOM_POSIX_IO)
  ssize_t n;
  while ((n = write(this->Handle, data, len)) == -1)
    {
    if (errno != EINTR)
      {
      break;
      }
    errno = 0;
    }
  if (n == -1)
    {
    this->Error = Bad;
    n = 0;
    }
  return n;
#elif defined(VTK_DICOM_WIN32_IO)
  // handle large requests in 1GB chunks
  const size_t chunksize = 1024*1024*1024;
  size_t n = 0;
  while (n < len)
    {
    DWORD l = static_cast<DWORD>(len - n < chunksize ? len - n : chunksize);
    DWORD r = 0;
    if (WriteFile(this->Handle, &data[n], l, &r, NULL) == FALSE)
      {
      DWORD errorCode = GetLastError();
      if (errorCode == ERROR_HANDLE_DISK_FULL)
        {
        this->Error = OutOfSpace;
        }
      else
        {
        this->Error = Bad;
        }
      break;
      }
    n += r;
    }
  return n;
#else
  size_t n = fwrite(data, 1, len, static_cast<FILE *>(this->Handle));
  if (n != len || len == 0)
    {
    this->Error = (ferror(static_cast<FILE *>(this->Handle)) == 0 ? 0 : Bad);
    }
  return n;
#endif
}

//----------------------------------------------------------------------------
bool vtkDICOMFile::Seek(Offset offset)
{
#if defined(VTK_DICOM_POSIX_IO)
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
#elif defined(VTK_DICOM_WIN32_IO)
  LONG lowerBits = static_cast<LONG>(offset);
  LONG upperBits = static_cast<LONG>(offset >> 32);
  DWORD pos = SetFilePointer(this->Handle, lowerBits, &upperBits, FILE_BEGIN);
  if (pos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
    {
    this->Error = Bad;
    return false;
    }
  return true;
#else
  return (fseek(static_cast<FILE *>(this->Handle), offset, SEEK_SET) == 0);
#endif
}
