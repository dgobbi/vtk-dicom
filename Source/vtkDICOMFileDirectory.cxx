/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMFileDirectory.h"
#include "vtkDICOMFilePath.h"
#include "vtkDICOMFile.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#endif

#include <string>
#include <vector>

// for PGI compiler, use dirent64 if readdir is readdir64
#if defined(__PGI) && defined(__GLIBC__)
# define redef_dirent_readdir dirent
# define redef_dirent_readdir64 dirent64
# define redef_dirent redef_dirent_lookup(readdir)
# define redef_dirent_lookup(x) redef_dirent_lookup2(x)
# define redef_dirent_lookup2(x) redef_dirent_##x
#else
# define redef_dirent dirent
#endif

//----------------------------------------------------------------------------
struct vtkDICOMFileDirectory::Entry
{
  std::string Name;
  unsigned short Flags;
  unsigned short Mask;
};

//----------------------------------------------------------------------------
vtkDICOMFileDirectory::vtkDICOMFileDirectory(const char *dirname)
  : Name(dirname), Error(0), NumberOfEntries(0), Entries(0)
{
#ifdef _WIN32
  vtkDICOMFilePath path(dirname);
  path.PushBack("*");
  const wchar_t *widename = path.Wide();
  if (widename == 0)
  {
    this->Error = UnknownError;
  }
  else
  {
    WIN32_FIND_DATAW fileData;
    HANDLE h = FindFirstFileW(widename, &fileData);
    DWORD code = 0;
    if (h == INVALID_HANDLE_VALUE)
    {
      code = GetLastError();
      if (code == ERROR_FILE_NOT_FOUND)
      {
        code = ERROR_NO_MORE_FILES;
      }
    }
    else
    {
      // each utf-16 wchar converts to three or fewer utf-8 bytes
      int n = MAX_PATH*3;
      char name[MAX_PATH*3];
      do
      {
        WideCharToMultiByte(
          CP_UTF8, 0, fileData.cFileName, -1, name, n, 0, 0);
        unsigned int flags = 0;
#if (_MSC_VER >= 1400)
        if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0 &&
            fileData.dwReserved0 == IO_REPARSE_TAG_SYMLINK)
        {
          flags |= TypeSymlink;
        }
#endif
        if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0)
        {
          flags |= TypeHidden;
        }
        if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
          flags |= TypeDirectory;
        }
        if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) != 0)
        {
          flags |= TypeSpecial;
        }
        this->AddEntry(name, flags, (TypeSymlink | TypeBroken |
                                     TypeDirectory | TypeSpecial |
                                     TypeHidden ));
      }
      while (FindNextFileW(h, &fileData));
      code = GetLastError();
    }
    if (code == ERROR_ACCESS_DENIED)
    {
      this->Error = AccessDenied;
    }
    else if (code == ERROR_FILE_NOT_FOUND ||
             code == ERROR_PATH_NOT_FOUND)
    {
      this->Error = FileNotFound;
    }
    else if (code != ERROR_NO_MORE_FILES)
    {
      this->Error = UnknownError;
    }
    if (h != INVALID_HANDLE_VALUE)
    {
      FindClose(h);
    }
  }
#else
  errno = 0;
  DIR* dir = opendir(dirname);

  if (!dir)
  {
    int e = errno;
    if (e == EACCES || e == EPERM)
    {
      this->Error = AccessDenied;
    }
    else if (e == ENOENT || e == ENOTDIR)
    {
      this->Error = FileNotFound;
    }
    else
    {
      this->Error = UnknownError;
    }
  }
  else
  {
    for (redef_dirent *d = readdir(dir); d; d = readdir(dir))
    {
      if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0)
      {
        this->AddEntry(d->d_name, 0, 0);
      }
    }
    closedir(dir);
  }
#endif
}

//----------------------------------------------------------------------------
vtkDICOMFileDirectory::vtkDICOMFileDirectory(const vtkDICOMFileDirectory& o)
  : Name(o.Name), Error(o.Error), NumberOfEntries(0), Entries(0)
{
  if (o.Entries && o.NumberOfEntries)
  {
    for (int i = 0; i < o.NumberOfEntries; i++)
    {
      const Entry& e = o.Entries[i];
      this->AddEntry(e.Name.c_str(), e.Flags, e.Mask);
    }
  }
}

//----------------------------------------------------------------------------
vtkDICOMFileDirectory& vtkDICOMFileDirectory::operator=(
  const vtkDICOMFileDirectory& o)
{
  if (this != &o)
  {
    delete [] this->Entries;

    this->Name = o.Name;
    this->Error = o.Error;
    this->NumberOfEntries = 0;
    this->Entries = 0;

    if (o.Entries && o.NumberOfEntries)
    {
      for (int i = 0; i < o.NumberOfEntries; i++)
      {
        const Entry& e = o.Entries[i];
        this->AddEntry(e.Name.c_str(), e.Flags, e.Mask);
      }
    }
  }

  return *this;
}

//----------------------------------------------------------------------------
vtkDICOMFileDirectory::~vtkDICOMFileDirectory()
{
  delete [] this->Entries;
}

//----------------------------------------------------------------------------
const char *vtkDICOMFileDirectory::GetEntry(int i)
{
  if (i < 0 || i >= this->NumberOfEntries)
  {
    return 0;
  }
  return this->Entries[i].Name.c_str();
}

//----------------------------------------------------------------------------
bool vtkDICOMFileDirectory::IsDirectory(int i)
{
  if (i < 0 || i >= this->NumberOfEntries)
  {
    return false;
  }
  if ((this->Entries[i].Mask & TypeDirectory) == 0)
  {
    this->StatEntry(i);
  }

  return ((this->Entries[i].Flags & TypeDirectory) != 0);
}

//----------------------------------------------------------------------------
bool vtkDICOMFileDirectory::IsSpecial(int i)
{
  if (i < 0 || i >= this->NumberOfEntries)
  {
    return false;
  }
  if ((this->Entries[i].Mask & TypeSpecial) == 0)
  {
    this->StatEntry(i);
  }

  return ((this->Entries[i].Flags & TypeSpecial) != 0);
}

//----------------------------------------------------------------------------
bool vtkDICOMFileDirectory::IsSymlink(int i)
{
  if (i < 0 || i >= this->NumberOfEntries)
  {
    return false;
  }
  if ((this->Entries[i].Mask & TypeSymlink) == 0)
  {
    this->LinkStatEntry(i);
  }

  return ((this->Entries[i].Flags & TypeSymlink) != 0);
}

//----------------------------------------------------------------------------
bool vtkDICOMFileDirectory::IsBroken(int i)
{
  if (i < 0 || i >= this->NumberOfEntries)
  {
    return false;
  }
  if ((this->Entries[i].Mask & TypeBroken) == 0)
  {
    if ((this->Entries[i].Mask & TypeSymlink) == 0)
    {
      // first use lstat() to find out if it is a link
      this->LinkStatEntry(i);
    }
    if ((this->Entries[i].Flags & TypeSymlink) != 0)
    {
      // then use stat() to find out if link is broken
      this->StatEntry(i);
    }
  }

  return ((this->Entries[i].Flags & TypeBroken) != 0);
}

//----------------------------------------------------------------------------
bool vtkDICOMFileDirectory::IsHidden(int i)
{
  if (i < 0 || i >= this->NumberOfEntries)
  {
    return false;
  }
  if ((this->Entries[i].Mask & TypeHidden) == 0)
  {
#ifdef __APPLE__
    // use lstat to check for hidden flag
    this->LinkStatEntry(i);
#else
    // set the mask bit, but not the flag bit
    this->Entries[i].Mask |= TypeHidden;
#endif
  }

  return ((this->Entries[i].Flags & TypeHidden) != 0);
}

//----------------------------------------------------------------------------
void vtkDICOMFileDirectory::AddEntry(
  const char *name, unsigned short flags, unsigned short mask)
{
  int n = this->NumberOfEntries;
  if (this->Entries == 0)
  {
    this->Entries = new Entry[4];
  }
  else if (n >= 4 && ((n-1) & n) == 0)
  {
    Entry *entries = new Entry[n*2];
    for (int i = 0; i < n; i++)
    {
      entries[i] = this->Entries[i];
    }
    delete [] this->Entries;
    this->Entries = entries;
  }

  this->Entries[n].Name = name;
  this->Entries[n].Flags = flags;
  this->Entries[n].Mask= mask;

  this->NumberOfEntries++;
}

//----------------------------------------------------------------------------
#ifndef _WIN32
void vtkDICOMFileDirectory::StatEntry(int i)
{
  if (i >= 0 && i < this->NumberOfEntries)
  {
    struct stat fs;
    vtkDICOMFilePath path(this->Name);
    path.PushBack(this->Entries[i].Name);
    if (stat(path.AsString().c_str(), &fs) == 0)
    {
      this->Entries[i].Mask |= TypeDirectory;
      this->Entries[i].Mask |= TypeSpecial;
      this->Entries[i].Mask |= TypeBroken;
      if (S_ISDIR(fs.st_mode))
      {
        this->Entries[i].Flags |= TypeDirectory;
      }
      else if (!S_ISREG(fs.st_mode))
      {
        this->Entries[i].Flags |= TypeSpecial;
      }
    }
    else if ((this->Entries[i].Mask & TypeSymlink) != 0 &&
             (this->Entries[i].Flags & TypeSymlink) != 0)
    {
      this->Entries[i].Mask |= TypeBroken;
      this->Entries[i].Flags |= TypeBroken;
    }
  }
}
#else /* _WIN32 */
void vtkDICOMFileDirectory::StatEntry(int)
{
  // on Windows, the attributes were collected when the
  // directory listing was done in the constructor, so
  // there is no need to run stat on the files
}
#endif

//----------------------------------------------------------------------------
#ifndef _WIN32
void vtkDICOMFileDirectory::LinkStatEntry(int i)
{
  if (i >= 0 && i < this->NumberOfEntries)
  {
    struct stat fs;
    vtkDICOMFilePath path(this->Name);
    path.PushBack(this->Entries[i].Name);
    if (lstat(path.AsString().c_str(), &fs) == 0)
    {
      this->Entries[i].Mask |= TypeSymlink;
      if (S_ISLNK(fs.st_mode))
      {
        this->Entries[i].Flags |= TypeSymlink;
      }
      else
      {
        // if not a link, check if directory or regular file
        this->Entries[i].Mask |= TypeDirectory;
        this->Entries[i].Mask |= TypeSpecial;
        if (S_ISDIR(fs.st_mode))
        {
          this->Entries[i].Flags |= TypeDirectory;
        }
        else if (!S_ISREG(fs.st_mode))
        {
          this->Entries[i].Flags |= TypeSpecial;
        }
      }

      this->Entries[i].Mask |= TypeHidden;
#ifdef __APPLE__
      if ((fs.st_flags & UF_HIDDEN) != 0)
      {
        this->Entries[i].Flags |= TypeHidden;
      }
#endif
    }
  }
}
#else /* _WIN32 */
void vtkDICOMFileDirectory::LinkStatEntry(int)
{
  // on Windows, the attributes were collected when the
  // directory listing was done in the constructor, so
  // there is no need to run stat on the files
}
#endif

//----------------------------------------------------------------------------
int vtkDICOMFileDirectory::Access(const char *dirname, Mode mode)
{
#ifdef _WIN32
  // The "mode" is not checked on Win32, add AccessCheck()?
  (void)mode;
  int errorCode = UnknownError;
  vtkDICOMFilePath fpath(dirname);
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
        errorCode = ImpossiblePath;
      }
      else
      {
        errorCode = UnknownError;
      }
    }
    else if ((code & FILE_ATTRIBUTE_DIRECTORY) == 0)
    {
      errorCode = ImpossiblePath;
    }
  }
  return errorCode;
#else
  int errorCode = 0;
  struct stat fs;
  if (stat(dirname, &fs) != 0 ||
      access(dirname, (mode == In ? R_OK : W_OK)) != 0)
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
      errorCode = ImpossiblePath;
    }
    else
    {
      errorCode = UnknownError;
    }
  }
  else if (!S_ISDIR(fs.st_mode))
  {
    errorCode = ImpossiblePath;
  }
  return errorCode;
#endif
}

//----------------------------------------------------------------------------
int vtkDICOMFileDirectory::Create(const char *name)
{
  int result = 0;

  std::vector<std::string> dirsToCreate;
  vtkDICOMFilePath path(name);

  while (!path.IsRoot() && !path.IsEmpty() && result == 0)
  {
    int code = vtkDICOMFile::Access(path.AsString().c_str(), vtkDICOMFile::In);
    if (code == 0 || code == vtkDICOMFile::AccessDenied)
    {
      // The name exists as a file, or there is no permission to use path
      result = AccessDenied;
    }
    else if (code == vtkDICOMFile::FileIsDirectory)
    {
      // Found a directory!
      break;
    }
    dirsToCreate.push_back(path.AsString());
    path.PopBack();
  }

  while (dirsToCreate.size() > 0 && result == 0)
  {
    const std::string& dirname = dirsToCreate.back();
#ifdef _WIN32
    vtkDICOMFilePath dirpath(dirname);
    const wchar_t *widename = dirpath.Wide();
    if (widename == 0)
    {
      result = UnknownError;
    }
    else if (!CreateDirectoryW(widename, NULL))
    {
      DWORD e = GetLastError();
      if (e == ERROR_ACCESS_DENIED ||
          e == ERROR_ALREADY_EXISTS)
      {
        result = AccessDenied;
      }
      else if (e == ERROR_PATH_NOT_FOUND)
      {
        result = ImpossiblePath;
      }
      else if (e == ERROR_DISK_FULL)
      {
        result = OutOfSpace;
      }
      else
      {
        result = UnknownError;
      }
    }
#else
    if (mkdir(dirname.c_str(), 00777) != 0)
    {
      int e = errno;
      if (e == EACCES || e == EPERM)
      {
        result = AccessDenied;
      }
      else if (e == ENOENT || e == ENOTDIR)
      {
        result = ImpossiblePath;
      }
      else if (e == ENOSPC)
      {
        // some systems also have EDQUOT for "quota exceeded"
        result = OutOfSpace;
      }
      else
      {
        result = UnknownError;
      }
    }
#endif
    dirsToCreate.pop_back();
  }

  return result;
}
