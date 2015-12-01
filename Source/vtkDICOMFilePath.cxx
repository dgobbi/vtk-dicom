/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMFilePath.h"

#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//----------------------------------------------------------------------------
vtkDICOMFilePath::vtkDICOMFilePath(const std::string& path)
  : Path(path), Separator('/')
{
  size_t l = path.length();
  size_t r = RootLength(path);
#ifdef _WIN32
  for (size_t i = 0; i < l; i++)
    {
    if (IsSeparator(path[i]))
      {
      this->Separator = path[i];
      break;
      }
    }
  if (r >= 4 && path.compare("\\\\\?\\"))
    {
    // remove the trailing slash, if present and not the root
    while (l > r && this->Path[l-1] == '\\')
      {
      this->Path.resize(--l);
      }
    }
  else
#endif
    {
    // remove the trailing slash, if present and not the root
    while (l > r && IsSeparator(this->Path[l-1]))
      {
      this->Path.resize(--l);
      }
    }
}

//----------------------------------------------------------------------------
std::string vtkDICOMFilePath::Join(const std::string& second) const
{
#ifdef _WIN32
  std::string path = this->Path;

  // check whether the second part might be an absolute path
  size_t pos = 0;
  size_t r = RootLength(second);
  if (r > 0)
    {
    // if second drive letter mismatches the first, paths can't be joined
    char drive1 = DriveLetter(path);
    char drive2 = DriveLetter(second);
    if (drive2 && drive1 == drive2)
      {
      // skip the drive letter in the second path
      pos = 2;
      }
    else if (drive1 == 0 || path.length() != 2 || r != 1)
      {
      // second path is absolute, so ignore first path
      // unless the first path is X: and second path is
      // an absolute path with no drive letter
      path = "";
      }
    }

  // if extended prefix is present, then all forward slashes must be
  // converted into back slashes, and "." and ".." must be removed
  char sep = this->Separator;
  bool extended = false;
  if (path.compare(0, 4, "\\\\\?\\") == 0)
    {
    sep = '\\';
    extended = true;
    }

  // append a separator before appending the second part
  size_t l = path.length();
  if (l > 0 && !IsSeparator(path[l-1]) && !(l == 2 && path[1] == ':'))
    {
    path.push_back(sep);
    }

  // append one part at a time
  while (pos != second.length())
    {
    if (IsSeparator(second[pos]))
      {
      path.push_back(sep);
      pos++;
      }
    size_t endpos = pos;
    while (endpos != second.length() && !IsSeparator(second[pos]))
      {
      endpos++;
      }
    size_t n = endpos - pos;
    if (n > 0)
      {
      if (extended)
        {
        if (n == 1 && second[pos] == '.')
          {
          // Ignore the '.' and the following slash
          if (endpos != second.length() && IsSeparator(second[endpos]))
            {
            endpos++;
            }
          }
        else if (n == 2 && second[pos] == '.' && second[pos+1] == '.')
          {
          // Ignore the '..' and the following slash
          if (endpos != second.length() && IsSeparator(second[endpos]))
            {
            endpos++;
            }
          // Remove the preceeding part of the path
          l = path.length();
          size_t m = RootLength(path);
          if (l > m && path[l-1] == sep)
            {
            l--;
            while (l > m && path[l-1] != sep)
              {
              l--;
              }
            path.resize(l);
            }
          }
        else
          {
          path.append(second, pos, n);
          }
        }
      else
        {
        path.append(second, pos, n);
        }
      }
    pos = endpos;
    }
  return path;
#else
  if (this->Path.length() == 0)
    {
    // first part is empty, so just return second
    return second;
    }

  if (second.length() > 0 && IsSeparator(second[0]))
    {
    // second part is an absolute path
    return second;
    }

  // append the second part to the first
  std::string path = this->Path;
  size_t l = path.length();
  if (l > 0 && !IsSeparator(path[l-1]))
    {
    path.push_back(this->Separator);
    }
  path.append(second);
  return path;
#endif
}

//----------------------------------------------------------------------------
std::string vtkDICOMFilePath::GetBack() const
{
  size_t l = this->Path.length();
  size_t r = RootLength(this->Path);
#ifdef _WIN32
  if (r >= 4 && this->Path.compare(0, 4, "\\\\\?\\") == 0)
    {
    while (l > r && this->Path[l-1] != '\\')
      {
      --l;
      }
    }
  else
#endif
    {
    while (l > r && !IsSeparator(this->Path[l-1]))
      {
      --l;
      }
    }
  return this->Path.substr(l);
}

//----------------------------------------------------------------------------
std::string vtkDICOMFilePath::GetExtension() const
{
  size_t l = this->Path.length();
  size_t r = RootLength(this->Path);
  size_t i = l;
  size_t j = l;

#ifdef _WIN32
  if (r >= 4 && this->Path.compare("\\\\\?\\"))
    {
    while (l > r && this->Path[l-1] != '\\')
      {
      i = j;
      if (this->Path[--l] == '.')
        {
        j = l;
        break;
        }
      }
    }
  else
#endif
    {
    while (l > r && !IsSeparator(this->Path[l-1]))
      {
      i = j;
      if (this->Path[--l] == '.')
        {
        j = l;
        break;
        }
      }
    }

  return this->Path.substr(i);
}

//----------------------------------------------------------------------------
std::string vtkDICOMFilePath::GetRealPath() const
{
#ifdef _WIN32

  std::string result;
  wchar_t *widepath = ConvertToWideChar(this->Path.c_str());

#ifndef DICOM_DEPRECATE_WINXP
  wchar_t buffer[512];
  DWORD m = 512;
  wchar_t *tmp = buffer;
  DWORD n = GetFullPathNameW(widepath, m, tmp, NULL);
  if (n >= m-1)
    {
    tmp = new wchar_t[n+3];
    n = GetFullPathNameW(widepath, n+3, tmp, NULL);
    }
  delete [] widepath;
  widepath = tmp;
#else
  HANDLE h = CreateFileW(widepath,
    GENERIC_READ, FILE_SHARE_READ , NULL, OPEN_EXISTING,
    FILE_FLAG_BACKUP_SEMANTICS, NULL);
  delete [] widepath;

  if (h == INVALID_HANDLE_VALUE)
    {
    return result;
    }

  wchar_t buffer[512];
  widepath = buffer;
  DWORD m = 512;
  // GetFinalPathNameByHandle() is not supported on Windows XP
  DWORD n = GetFinalPathNameByHandleW(h, widepath, m, 0);
  if (n >= m)
    {
    widepath = new wchar_t[n+1];
    n = GetFinalPathNameByHandleW(h, widepath, n+1, 0);
    }
  CloseHandle(h);
#endif

  if (n != 0)
    {
    char *path = ConvertToMultiByte(widepath);
    if (widepath != buffer)
      {
      delete [] widepath;
      }

    if (path == 0)
      {
      return result;
      }

#ifndef DICOM_DEPRECATE_WINXP
    // Add extended prefix if not present
    if (strncmp("\\\\?\\", path, 4) == 0 ||
        strncmp("\\\\.\\", path, 4) == 0)
      {
      result = path;
      }
    else
      {
      size_t l = strlen(path);
      if (l >= 2 && path[0] == '\\' && path[1] == '\\')
        {
        result = "\\\\?\\UNC\\";
        result.append(&path[2])
        }
      else if (l >= 1 && path[0] == '\\')
        {
        result = "\\\\?\\";
        result.append(&path[1])
        }
      else
        {
        result = "\\\\?\\";
        result.append(path)
        }
      }
#else
    result = path;
#endif

    delete [] path;
    }

  return result;

#else

#if _POSIX_VERSION >= 200809L
  char *storage = 0;
#else
  char *storage = static_cast<char *>(malloc(PATH_MAX));
#endif

  std::string result;
  char *path = realpath(this->Path.c_str(), storage);
  if (path != 0)
    {
    result = path;
    storage = path;
    }
  free(storage);
  return result;

#endif
}

//----------------------------------------------------------------------------
void vtkDICOMFilePath::PushBack(const std::string& second)
{
  if (RootLength(second) == 0)
    {
    this->Path = this->Join(second);
    }
#ifdef _WIN32
  else if (RootLength(this->Path) == 2 &&
           DriveLetter(this->Path) == DriveLetter(second))
    {
    this->Path = this->Join(second);
    }
#endif
}

//----------------------------------------------------------------------------
void vtkDICOMFilePath::PopBack()
{
  const std::string& path = this->Path;
  size_t root = RootLength(path);
  size_t l = path.length();

#ifdef _WIN32
  if (l >= 4 && (path.compare(0, 4, "\\\\\?\\") == 0 ||
                 path.compare(0, 4, "\\\\.\\") == 0))
    {
    // only allow backslash as a separator with the "\\?\" prefix
    while (l > root && path[l-1] != '\\')
      {
      --l;
      }
    // strip all trailing slashes that aren't part of the root
    while (l > root && path[l-1] == '\\')
      {
      --l;
      }
    }
  else
#endif
    {
    // back up to the last separator
    while (l > root && !IsSeparator(path[l-1]))
      {
      --l;
      }
    // strip all trailing slashes that aren't part of the root
    while (l > root && IsSeparator(path[l-1]))
      {
      --l;
      }
    }

  this->Path.resize(l);
}

//----------------------------------------------------------------------------
size_t vtkDICOMFilePath::RootLength(const std::string& path)
{
  size_t root = 0;
  size_t l = path.length();

#ifdef _WIN32
  // Several possible base prefixes exist on Windows:
  //  \ (the root of the current device)
  //  A: (indicates a relative path on a device)
  //  A:\ (the root of a device)
  //  \\server\share\ (a UNC path prefix)
  // There's also the special "\\?\" prefix, which allows paths to go beyond
  // the usual 260 char limits, but is only allowed for absolute paths and
  // does not allows substitutions such as "/" for "\" or "." and "..".
  //  \\?\A:\ (the root of a device)
  //  \\?\UNC\server\share\ (a UNC path prefix)
  // Finally, the special "\\?\" prefix is used to name system devices:
  //  \\.\DEVICE (name of a special devices)
  if (l >= 4 && (path.compare(0, 4, "\\\\\?\\") == 0 ||
                 path.compare(0, 4, "\\\\.\\") == 0))
    {
    root = 4;
    if (path[2] == '\?')
      {
      if (path.compare(4, 3, "UNC") == 0)
        {
        if (l == 7)
          {
          root = 7;
          }
        else if (l > 7 && path[7] == '\\')
          {
          root = 8;
          while (root != l && path[root] != '\\')
            {
            root++;
            }
          if (root != l && path[root] == '\\')
            {
            root++;
            }
          while (root != l && path[root] != '\\')
            {
            root++;
            }
          }
        }
      else if (l > 5 && path[5] == ':' &&
               ((path[4] >= 'A' && path[4] <= 'Z') ||
                (path[4] >= 'a' && path[4] <= 'z')))
        {
        root = 6;
        if (l > 6 && path[6] == '\\')
          {
          root = 7;
          }
        }
      }
    }
  else
    {
    if (l > 0 && IsSeparator(path[0]))
      {
      root = 1;
      if (l > 1 && IsSeparator(path[1]))
        {
        // UNC path
        root = 2;
        while (root != l && !IsSeparator(path[root]))
          {
          root++;
          }
        if (root != l && IsSeparator(path[root]))
          {
          root++;
          }
        while (root != l && !IsSeparator(path[root]))
          {
          root++;
          }
        }
      }
    else if (l >= 2 && path[1] == ':' &&
             ((path[0] >= 'A' && path[0] <= 'Z') ||
              (path[0] >= 'a' && path[0] <= 'z')))
      {
      root = 2;
      if (l > 2 && IsSeparator(path[2]))
        {
        root = 3;
        }
      }
    }
#else
  // For UNIX, the only possible root is "/"
  if (l > 0 && IsSeparator(path[0]))
    {
    root = 1;
    }
#endif

  return root;
}

//----------------------------------------------------------------------------
#ifdef _WIN32
char vtkDICOMFilePath::DriveLetter(const std::string& path)
{
  char d = '\0';
  size_t l = path.length();
  size_t pos = 0;
  if (l >= 4 && path.compare(0, 4, "\\\\\?\\") == 0)
    {
    pos = 4;
    }
  if (l >= pos+2 && path[pos+1] == ':')
    {
    char e = path[pos];
    if (e >= 'A' && e <= 'Z')
      {
      d = e;
      }
    else if (e >= 'a' && e <= 'z')
      {
      d = e - ('a' - 'A');
      }
    }
  return d;
}
#endif

//----------------------------------------------------------------------------
#ifdef _WIN32
wchar_t *vtkDICOMFilePath::ConvertToWideChar(const char *filename)
{
  wchar_t *wideFilename = 0;
  int n = MultiByteToWideChar(
    CP_UTF8, 0, filename, -1, NULL, 0);
  if (n > 0)
    {
    wideFilename = new wchar_t[n];
    n = MultiByteToWideChar(
      CP_UTF8, 0, filename, -1, wideFilename, n);
    if (n == 0)
      {
      delete [] wideFilename;
      wideFilename = 0;
      }
    }
  return wideFilename;
}
#endif

//----------------------------------------------------------------------------
#ifdef _WIN32
char *vtkDICOMFilePath::ConvertToMultiByte(const wchar_t *wideFilename)
{
  char *filename = 0;
  int n = WideCharToMultiByte(
    CP_UTF8, 0, wideFilename, -1, NULL, 0, 0, 0);
  if (n > 0)
    {
    filename = new char[n];
    n = WideCharToMultiByte(
      CP_UTF8, 0, wideFilename, -1, filename, n, 0, 0);
    if (n == 0)
      {
      delete [] filename;
      filename = 0;
      }
    }
  return filename;
}
#endif
