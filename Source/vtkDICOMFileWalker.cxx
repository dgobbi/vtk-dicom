/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkDICOMFileWalker.h"
#include "vtkDICOMFileDirectory.h"
#include "vtkDICOMFilePath.h"

#include <string>
#include <vector>
#include <list>
#include <utility>

// defined here to avoid including stl headers in our header
class vtkDICOMFileWalker::DirectoryStack
{
public:
  // Add another level to the directory tree.
  void PushDepth(const std::string& v) {
    size_t i = 0;
    Impl.push_back(std::make_pair(i, std::vector<std::string>()));
    Impl.back().second.push_back(v);
  }

  // Add a directory at the current level.
  void PushNext(const std::string& v) {
    Impl.back().second.push_back(v);
  }

  // Get the current path within the tree.
  vtkDICOMFilePath Path() {
    vtkDICOMFilePath p;
    for (iterator x = Impl.begin(); x != Impl.end(); ++x) {
      p.PushBack(x->second[x->first]);
    }
    return p;
  }

  // Move to the next directory in the tree walk.
  void Next() {
    while (!Impl.empty()) {
      size_t i = Impl.back().first + 1;
      if (i < Impl.back().second.size()) {
        Impl.back().first = i;
        break;
      }
      Impl.pop_back();
    }
  }

  // Returns true if the tree walk is complete.
  bool Done() {
    return Impl.empty();
  }

  // Returns the current depth of the tree.
  size_t Depth() {
    return Impl.size();
  }

private:
  std::list<std::pair<size_t, std::vector<std::string> > > Impl;
};

//----------------------------------------------------------------------------
vtkDICOMFileWalker::vtkDICOMFileWalker(const char *dirname)
  Stack(0), Directory(0), FollowSymlinks(1)
{
  this->Stack->push_depth(dirname);
}

//----------------------------------------------------------------------------
vtkDICOMFileWalker::vtkDICOMFileWalker(const vtkDICOMFileWalker& o) :
  Stack(0), Directory(0), FollowSymlinks(1)
{
}

//----------------------------------------------------------------------------
vtkDICOMFileWalker& vtkDICOMFileWalker::operator=(
  const vtkDICOMFileWalker& o)
{
}

//----------------------------------------------------------------------------
vtkDICOMFileWalker::~vtkDICOMFileWalker()
{
  delete this->Stack;
  delete this->Directory;
}

//----------------------------------------------------------------------------
vtkDICOMFileDirectory& vtkDICOMFileWalker::GetDirectory()
{
  // XXX what if it is null?
  return *this->Directory;
}

//----------------------------------------------------------------------------
void vtkDICOMFileWalker::Next()
{
  bool hasSubdirs = false;
  for (int i = 0; i < this->Directory->GetNumberOfEntries; i++)
  {
    if (this->Directory->IsDirectory(i) &&
        (this->FollowSymlinks || !this->Directory->IsSymlink(i)))
    {
      if (!hasSubdirs)
      {
        hasSubdirs = true;
        this->Stack->PushDepth(this->Directory->GetEntry(i));
      }
      else
      {
        this->Stack->PushNext(this->Directory->GetEntry(i));
      }
    }
  }

  if (!hasSubdirs)
  {
    this->Stack->Next();
  }

  delete this->Directory;
  this->Directory = 0;

  if (!this->Stack->Empty())
  {
    this->Directory = new vtkDICOMFileDirectory(this->Stack->Path());
    // XXX also check error code
  }
}

//----------------------------------------------------------------------------
bool vtkDICOMFileWalker::Done()
{
  return this->Stack->Done();
}

//----------------------------------------------------------------------------
std::string vtkDICOMFileWalker::GetPath()
{
  // XXX maybe have a Path member instead?
  return this->Stack->Path().AsString();
}

//----------------------------------------------------------------------------
// XXX Note that 'depth' counts down.
// XXX This will have to change, we need a stack to store all of the
// XXX as-yet-unsearched paths (a stack of string vectors).  Might also
// XXX have to store the IsSymlink result for proper error reporting?
void vtkDICOMDirectory::ProcessDirectory(
  const char *dirname, int depth, vtkStringArray *files)
{
  // Check if the directory has been visited yet.  This avoids infinite
  // recursion when following circular links.
  std::string realname = vtkDICOMFilePath(dirname).GetRealPath();
  std::vector<std::string>::iterator viter =
    std::lower_bound(this->Visited->begin(), this->Visited->end(), realname);
  if (viter == this->Visited->end() || *viter != realname)
  {
    // Add this directory to the "visited" list.
    this->Visited->insert(viter, realname);
  }
  else
  {
    // This directory has already been visited.
    return;
  }

  // Find the path to the directory.
  vtkDICOMFilePath path(dirname);

  // XXX interesting, DICOMDIR only checked at first level...
  if (depth == this->ScanDepth && !this->IgnoreDicomdir)
  {
    // Build the path to the DICOMDIR file.
    path.PushBack("DICOMDIR");
    std::string dicomdir = path.AsString();
    path.PopBack();

    // Check to see if the DICOMDIR file exists.
    if (vtkDICOMFile::Access(dicomdir.c_str(), vtkDICOMFile::In) == 0)
    {
      vtkSmartPointer<vtkDICOMMetaData> meta =
        vtkSmartPointer<vtkDICOMMetaData>::New();
      vtkDICOMParser *parser = vtkDICOMParser::New();
      parser->SetDefaultCharacterSet(this->DefaultCharacterSet);
      parser->SetOverrideCharacterSet(this->OverrideCharacterSet);
      parser->AddObserver(
        vtkCommand::ErrorEvent, this, &vtkDICOMDirectory::RelayError);
      parser->SetMetaData(meta);
      this->SetInternalFileName(dicomdir.c_str());
      parser->SetFileName(dicomdir.c_str());
      parser->Update();
      unsigned long errorCode = parser->GetErrorCode();
      parser->Delete();

      if (errorCode && depth == 0)
      {
        // Only fail if depth is zero.  Otherwise, we can ignore the
        // DICOMDIR and look for the DICOM files directly.
        this->ErrorCode = errorCode;
        return;
      }
      else if (errorCode == 0)
      {
        // Process the DICOMDIR file.
        this->ProcessDirectoryFile(dirname, meta);
        return;
      }
    }
  }

  // If depth is zero, recursion is complete.
  if (depth <= 0)
  {
    return;
  }

  // XXX not relevant for a walker
  // Check for abort.
  if (!this->AbortExecute)
  {
    this->UpdateProgress(0.0);
  }
  if (this->AbortExecute)
  {
    return;
  }

  vtkDICOMFileDirectory d(dirname);
  if (d.GetError() != 0)
  {
    // Only fail at the initial depth.
    if (depth == this->ScanDepth)
    {
      vtkErrorMacro(<< "Could not read directory " << dirname);
      this->ErrorCode = vtkErrorCode::CannotOpenFileError;
      return;
    }
  }

  // XXX interesting, DICOMDIR is always ignored as a file
  int n = d.GetNumberOfEntries();
  for (int i = 0; i < n; i++)
  {
    const char *fname = d.GetEntry(i);
    if ((fname[0] != '.' || (fname[1] != '\0' &&
         (fname[1] != '.' || fname[2] != '\0'))) &&
        strcmp(fname, "DICOMDIR") != 0)
    {
      path.PushBack(fname);
      std::string fileString = path.AsString();
      path.PopBack();
      if (d.IsSymlink(i) && !this->FollowSymlinks)
      {
        // Do nothing unless FollowSymlinks is On
      }
#ifdef _WIN32
      else if (!this->ShowHidden && d.IsHidden(i))
#else
      else if (!this->ShowHidden && (d.IsHidden(i) || fname[0] == '.'))
#endif
      {
        // Do nothing for hidden files unless ShowHidden is On
        // (on Linux and OS X, consider "." files to be hidden)
      }
      else if (d.IsDirectory(i))
      {
        if (depth > 1)
        {
          this->ProcessDirectory(fileString.c_str(), depth-1, files);
        }
      }
      else if (this->FilePattern == 0 || this->FilePattern[0] == '\0' ||
               vtkDICOMUtilities::PatternMatches(
                 this->FilePattern, fileString.c_str()))
      {
        if (!d.IsSpecial(i) && !d.IsBroken(i))
        {
          files->InsertNextValue(fileString);
        }
      }
    }
  }
}
