/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMFile.h"
#include "vtkDICOMFilePath.h"

#if defined(VTK_DICOM_POSIX_IO)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#elif defined(VTK_DICOM_WIN32_IO)
#include <windows.h>
#else
#ifdef _WIN32
#include <io.h>
#include <direct.h>
#define _unlink unlink
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <errno.h>
#endif

#include <string.h>

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
      this->Error = FileIsDirectory;
    }
    else if (errorCode == ENOTDIR)
    {
      this->Error = (mode == Out ? ImpossiblePath : FileNotFound);
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
      this->Error = UnknownError;
    }
  }
#elif defined(VTK_DICOM_WIN32_IO)
  this->Handle = INVALID_HANDLE_VALUE;
  this->Error = 0;
  this->Eof = false;

  vtkDICOMFilePath fpath(filename);
  const wchar_t *wideFilename = fpath.Wide();
  if (wideFilename)
  {
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

  if (this->Handle == INVALID_HANDLE_VALUE)
  {
    DWORD errorCode = GetLastError();
    if (errorCode == ERROR_ACCESS_DENIED ||
        errorCode == ERROR_SHARING_VIOLATION)
    {
      this->Error = AccessDenied;
      if (wideFilename)
      {
        DWORD attr = GetFileAttributesW(wideFilename);
        if (attr != INVALID_FILE_ATTRIBUTES &&
            (attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
          this->Error = FileIsDirectory;
        }
      }
    }
    else if (errorCode == ERROR_PATH_NOT_FOUND)
    {
      this->Error = (mode == Out ? ImpossiblePath : FileNotFound);
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
      this->Error = UnknownError;
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
    this->Error = UnknownError;
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
      this->Error = UnknownError;
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
size_t vtkDICOMFile::Read(unsigned char *data, size_t len)
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
    this->Error = UnknownError;
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
      this->Error = UnknownError;
      break;
    }
    n += r;
    if (n == 0)
    {
      this->Eof = true;
      break;
    }
    else if (r < l)
    {
      break;
    }
  }
  return n;
#else
  size_t n = fread(data, 1, len, static_cast<FILE *>(this->Handle));
  if (n != len || len == 0)
  {
    this->Eof = (feof(static_cast<FILE *>(this->Handle)) != 0);
    this->Error = (ferror(static_cast<FILE *>(this->Handle)) == 0 ?
                     0 : UnknownError);
  }
  return n;
#endif
}

//----------------------------------------------------------------------------
size_t vtkDICOMFile::Write(const unsigned char *data, size_t len)
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
    this->Error = UnknownError;
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
        this->Error = UnknownError;
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
    this->Error = (ferror(static_cast<FILE *>(this->Handle)) == 0 ?
                     0 : UnknownError);
  }
  return n;
#endif
}

//----------------------------------------------------------------------------
bool vtkDICOMFile::SetPosition(Size offset)
{
#if defined(VTK_DICOM_POSIX_IO)
#if defined(__linux__) && defined(_LARGEFILE64_SOURCE)
  off64_t pos = lseek64(this->Handle, offset, SEEK_SET);
#else
  off_t pos = lseek(this->Handle, offset, SEEK_SET);
#endif
  if (pos == -1)
  {
    this->Error = UnknownError;
    return false;
  }
  return true;
#elif defined(VTK_DICOM_WIN32_IO)
  LONG lowerBits = static_cast<LONG>(offset);
  LONG upperBits = static_cast<LONG>(offset >> 32);
  DWORD pos = SetFilePointer(this->Handle, lowerBits, &upperBits, FILE_BEGIN);
  if (pos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
  {
    this->Error = UnknownError;
    return false;
  }
  return true;
#else
  return (fseek(static_cast<FILE *>(this->Handle), offset, SEEK_SET) == 0);
#endif
}

//----------------------------------------------------------------------------
vtkDICOMFile::Size vtkDICOMFile::GetSize()
{
#if defined(VTK_DICOM_POSIX_IO)
  struct stat fs;
  if (fstat(this->Handle, &fs) != 0)
  {
    this->Error = UnknownError;
    return ~0ull;
  }
  return fs.st_size;
#elif defined(VTK_DICOM_WIN32_IO)
  DWORD upperBits = 0;
  DWORD lowerBits = GetFileSize(this->Handle, &upperBits);
  if (lowerBits == INVALID_FILE_SIZE && GetLastError() != NO_ERROR)
  {
    this->Error = UnknownError;
    return ~0ull;
  }
  return lowerBits | (static_cast<Size>(upperBits) << 32);
#else
  FILE *fp = static_cast<FILE *>(this->Handle);
  long long size = -1;
  fpos_t pos;
  if (fgetpos(fp, &pos) == 0)
  {
    if (fseek(fp, 0, SEEK_END) == 0)
    {
      size = ftell(fp);
    }
    if (fsetpos(fp, &pos) != 0)
    {
      this->Error = UnknownError;
    }
  }
  if (size == -1)
  {
    this->Error = UnknownError;
    return ~0ull;
  }
  return static_cast<Size>(size);
#endif
}

//----------------------------------------------------------------------------
int vtkDICOMFile::Access(const char *filename, Mode mode)
{
#ifdef _WIN32
  int errorCode = UnknownError;
  vtkDICOMFilePath fpath(filename);
  const wchar_t *wideFilename = fpath.Wide();
  if (wideFilename)
  {
    errorCode = 0;
    DWORD code = GetFileAttributesW(wideFilename);
    if (code == INVALID_FILE_ATTRIBUTES)
    {
      DWORD lastError = GetLastError();
      if (lastError == ERROR_ACCESS_DENIED ||
          lastError == ERROR_SHARING_VIOLATION)
      {
        errorCode = AccessDenied;
      }
      else if (lastError == ERROR_FILE_NOT_FOUND)
      {
        errorCode = FileNotFound;
      }
      else if (lastError == ERROR_PATH_NOT_FOUND)
      {
        errorCode = (mode == Out ? ImpossiblePath : FileNotFound);
      }
      else
      {
        errorCode = UnknownError;
      }
    }
    else if (mode == Out && (code & FILE_ATTRIBUTE_READONLY) != 0)
    {
      errorCode = AccessDenied;
    }
    else if ((code & FILE_ATTRIBUTE_DIRECTORY) != 0)
    {
      errorCode = FileIsDirectory;
    }
  }
  return errorCode;
#else
  int errorCode = 0;
  struct stat fs;
  if (stat(filename, &fs) != 0 ||
      access(filename, (mode == In ? R_OK : W_OK)) != 0)
  {
    int e = errno;
    if (e == EACCES || e == EPERM)
    {
      errorCode = AccessDenied;
    }
    else if (e == ENOENT)
    {
      errorCode = FileNotFound;
    }
    else if (e == ENOTDIR)
    {
      errorCode = (mode == Out ? ImpossiblePath : FileNotFound);
    }
    else
    {
      errorCode = UnknownError;
    }
  }
  else if (S_ISDIR(fs.st_mode))
  {
    errorCode = FileIsDirectory;
  }
  return errorCode;
#endif
}

//----------------------------------------------------------------------------
int vtkDICOMFile::Remove(const char *filename)
{
#if defined(VTK_DICOM_WIN32_IO)
  int errorCode = 0;
  vtkDICOMFilePath fpath(filename);
  const wchar_t *wideFilename = fpath.Wide();
  if (wideFilename)
  {
    if (!DeleteFileW(wideFilename))
    {
      DWORD lastError = GetLastError();
      if (lastError == ERROR_ACCESS_DENIED ||
          lastError == ERROR_SHARING_VIOLATION)
      {
        errorCode = AccessDenied;
      }
      else if (lastError == ERROR_FILE_NOT_FOUND ||
               lastError == ERROR_PATH_NOT_FOUND)
      {
        errorCode = FileNotFound;
      }
      else
      {
        errorCode = UnknownError;
      }
    }
  }
  return errorCode;
#else
  int errorCode = 0;
  if (unlink(filename) != 0)
  {
    int e = errno;
    if (e == EACCES || e == EPERM)
    {
      errorCode = AccessDenied;
    }
    else if (e == ENOENT || e == ENOTDIR)
    {
      errorCode = FileNotFound;
    }
    else
    {
      errorCode = UnknownError;
    }
  }
  return errorCode;
#endif
}

//----------------------------------------------------------------------------
bool vtkDICOMFile::SameFile(const char *file1, const char *file2)
{
  // Two files are considered to be the same if:
  // 1) they are on the same device
  // 2) their index (inode number) is the same

  bool result = false;
#ifdef _WIN32
  vtkDICOMFilePath fpath1(file1);
  const wchar_t *widepath = fpath1.Wide();
  HANDLE h1 = CreateFileW(widepath,
    GENERIC_READ, FILE_SHARE_READ , NULL, OPEN_EXISTING,
    FILE_FLAG_BACKUP_SEMANTICS, NULL);
  vtkDICOMFilePath fpath2(file2);
  widepath = fpath2.Wide();
  HANDLE h2 = CreateFileW(widepath,
    GENERIC_READ, FILE_SHARE_READ , NULL, OPEN_EXISTING,
    FILE_FLAG_BACKUP_SEMANTICS, NULL);
  if (h1 != INVALID_HANDLE_VALUE && h2 != INVALID_HANDLE_VALUE)
  {
    BY_HANDLE_FILE_INFORMATION buf;
    GetFileInformationByHandle(h1, &buf);
    DWORD sn = buf.dwVolumeSerialNumber;
    DWORD hi = buf.nFileIndexHigh;
    DWORD li = buf.nFileIndexLow;
    GetFileInformationByHandle(h2, &buf);
    result = (buf.dwVolumeSerialNumber == sn);
    result &= (buf.nFileIndexHigh == hi);
    result &= (buf.nFileIndexLow == li);
  }
  if (h1 != INVALID_HANDLE_VALUE)
  {
    CloseHandle(h1);
  }
  if (h2 != INVALID_HANDLE_VALUE)
  {
    CloseHandle(h2);
  }
#else
  struct stat st1;
  struct stat st2;
  if (stat(file1, &st1) == 0 && stat(file2, &st2) == 0)
  {
    result = (memcmp(&st1.st_dev, &st2.st_dev, sizeof(st1.st_dev)) == 0);
    result &= (memcmp(&st1.st_ino, &st2.st_ino, sizeof(st1.st_ino)) == 0);
  }
#endif
  return result;
}
