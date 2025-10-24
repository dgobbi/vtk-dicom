/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2025 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMFilePath_h
#define vtkDICOMFilePath_h

#include "vtkSystemIncludes.h"
#include "vtkDICOMModule.h" // For export macro

#include <string> // Interface type

//! A class that provides path manipulation.
class VTKDICOM_EXPORT vtkDICOMFilePath
{
public:
  //@{
  //! Create a new path from the given string.
  /*!
   *  Trailing slashes will be removed (unless the trailing slash is
   *  the root of the filesystem).
   */
  vtkDICOMFilePath(const std::string& path);

#ifdef _WIN32
  //! Create a new path from a wide string.
  /*!
   *  This is to support unicode paths on Windows.
   */
  vtkDICOMFilePath(const std::wstring& path);
#endif

  //! Copy constructor.
  vtkDICOMFilePath(const vtkDICOMFilePath&);

  //! Destructor.
  ~vtkDICOMFilePath();
  //@}

  //@{
  //! Get the path as a string.
  const std::string& AsString() const { return this->Path; }
  //@}

  //@{
  //! Check if the path is empty.
  bool IsEmpty() const { return (this->Path.length() == 0); }

  //! Check if the path is a root path.
  bool IsRoot() const;

  //! Check whether the path is an existing directory.
  bool IsDirectory() const;

  //! Check whether the path goes to a device, socket, or pipe.
  bool IsSpecial() const;

  //! Check whether the path is a symbolic link.
  bool IsSymlink() const;
  //@}

  //@{
  //! Return the path joined with the given extra component.
  std::string Join(const std::string& second) const;
  //@}

  //@{
  //! Get the final component of the path.
  std::string GetBack() const;

  //! Remove a component from the path.
  void PopBack();

  //! Add a new component (or components) to the path.
  void PushBack(const std::string& path);
  //@}

  //@{
  //! Get the file extension (the final dot and everything after).
  std::string GetExtension() const;

  //! Remove the current file extension, including the dot.
  void PopExtension();

  //! Add a new file extension to the current file path.
  void PushExtension(const std::string& path);
  //@}

  //@{
  //! Get the full absolute path (or empty string if file doesn't exist).
  /*!
   *  This will go to the file system to find the true path to a file,
   *  including exactly the same case as used by the file system.  On
   *  Windows, all forward slashes will be converted to back slashes,
   *  and the returned file name will have a \\?\ prefix to indicate
   *  that extended path processing should be used.
   */
  std::string GetRealPath() const;
  //@}

#ifdef _WIN32
  //@{
  //! Convert the path to a wchar_t pointer for Windows methods.
  /*!
   *  Call this method if the path is going to be passed to a Windows
   *  method that expects a unicode string.
   */
  const wchar_t *Wide();

  //! Convert the path to a local 8-bit string for Windows methods.
  /*!
   *  Call this method if the path is going to be passed to a Windows
   *  method that expects an 8-bit string with the local encoding.
   */
  const char *Local();
  //@}

#endif

  //@{
  //! Assignment operator.
  vtkDICOMFilePath& operator=(const vtkDICOMFilePath&);
  //@}

private:

  //! Check if the given character is a separator.
  static bool IsSeparator(char c) {
#ifndef __WRAP__
#ifdef _WIN32
    return (c == '/' || c == '\\');
#else
    return (c == '/');
#endif
#endif
  }

  //! Strip the trailing slash, if present.
  static void StripTrailingSlash(std::string *path);

  //! Find the position of the extension (including the dot).
  static size_t ExtensionPosition(const std::string& path);

  //! Get the length of the "root device" part of the path.
  /*!
   *  On UNIX, the root is '/' for absolute paths, and is empty for relative
   *  paths.  On Windows, the root includes the device letter plus any slash
   *  that immediately follows it, or the network share path for UNC paths.
   */
  static size_t RootLength(const std::string& path);

#ifdef _WIN32
  //! Check if an extended path prefix is present.
  static bool HasExtendedPrefix(const std::string& path);

  //! Get the drive letter (or zero if none).
  static char DriveLetter(const std::string& path);

  //! Convert to WideChar. Returns NULL or new string (free with delete []).
  static wchar_t *ConvertToWideChar(const char *filename);

  //! Convert to utf8. Returns NULL or new string (free with delete []).
  static char *ConvertToUTF8(const wchar_t *filename);

  //! Convert to local 8-bit. Returns NULL or new string (free with delete []).
  static char *ConvertToLocal(const wchar_t *filename);
#endif

  std::string Path;
  char Separator;
#ifdef _WIN32
  wchar_t *WidePath;
  char *LocalPath;
#endif
};

#endif /* vtkDICOMFilePath_h */
// VTK-HeaderTest-Exclude: vtkDICOMFilePath.h
