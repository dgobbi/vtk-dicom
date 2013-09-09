/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMSorter.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMUtilities.h"

#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkErrorCode.h>
#include <vtkCommand.h>
#include <vtkUnsignedShortArray.h>

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <vtksys/SystemTools.hxx>
#include <vtksys/Glob.hxx>

#include <ctype.h>

vtkStandardNewMacro(vtkDICOMSorter);

//----------------------------------------------------------------------------
// A vector of string arrays

class vtkDICOMSorter::StringArrayVector
  : public std::vector<vtkSmartPointer<vtkStringArray> >
{
};

//----------------------------------------------------------------------------
// Information used to sort DICOM files.

struct vtkDICOMSorter::FileInfo
{
  std::string FileName;
  vtkDICOMValue StudyUID;
  vtkDICOMValue SeriesUID;
  int InstanceNumber;
};

bool vtkDICOMSorter::CompareInstance(
  const FileInfo &fi1, const FileInfo &fi2)
{
  return (fi1.InstanceNumber < fi2.InstanceNumber);
}

//----------------------------------------------------------------------------
// A temporary container class for use with stl algorithms

class vtkDICOMSorter::FileInfoVectorList
  : public std::list<std::vector<vtkDICOMSorter::FileInfo> >
{
};

//----------------------------------------------------------------------------
vtkDICOMSorter::vtkDICOMSorter()
{
  this->InputFileName = 0;
  this->InputFileNames = 0;
  this->OutputFileNames = vtkStringArray::New();
  this->Series = new StringArrayVector;
  this->Studies = vtkIntArray::New();
  this->Studies->SetNumberOfComponents(2);
  this->ErrorCode = 0;
  this->InternalFileName = 0;
  this->RequirePixelData = 1;
}

//----------------------------------------------------------------------------
vtkDICOMSorter::~vtkDICOMSorter()
{
  if (this->InputFileName)
    {
    delete [] this->InputFileName;
    }
  if (this->InputFileNames)
    {
    this->InputFileNames->Delete();
    }
  if (this->InternalFileName)
    {
    delete [] this->InternalFileName;
    }

  this->OutputFileNames->Delete();
  delete this->Series;
  this->Studies->Delete();
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  const char *inputFileName = this->GetInputFileName();
  os << indent << "InputFileName: "
     << (inputFileName ? inputFileName : "(NULL)") << "\n";
  os << indent << "InputFileNames: (" << this->GetInputFileNames() << ")\n";

  os << indent << "RequirePixelData: "
     << (this->RequirePixelData ? "On\n" : "Off\n");

  os << indent << "NumberOfSeries: " << this->GetNumberOfSeries() << "\n";
  os << indent << "NumberOfStudies: " << this->GetNumberOfStudies() << "\n";

  os << indent << "OutputFileNames: (" << this->GetOutputFileNames() << ")\n";
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::SetInputFileName(const char *name)
{
  // mutual exclusion with InputFileNames
  if (name) { this->SetInputFileNames(0); }

  if (name == this->InputFileName ||
      (name && this->InputFileName &&
       strcmp(name, this->InputFileName) == 0))
    {
    return;
    }

  delete [] this->InputFileName;
  this->InputFileName = 0;
  if (name)
    {
    char *cp = new char[strlen(name) + 1];
    strcpy(cp, name);
    this->InputFileName = cp;
    }
  this->Modified();
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::SetInputFileNames(vtkStringArray *input)
{
  // mutual exclusion with InputFileName
  if (input) { this->SetInputFileName(0); }

  vtkSetObjectBodyMacro(InputFileNames, vtkStringArray, input);
}

//----------------------------------------------------------------------------
int vtkDICOMSorter::GetNumberOfSeries()
{
  return static_cast<int>(this->Series->size());
}

//----------------------------------------------------------------------------
int vtkDICOMSorter::GetNumberOfStudies()
{
  return this->Studies->GetNumberOfTuples();
}

//----------------------------------------------------------------------------
int vtkDICOMSorter::GetFirstSeriesInStudy(int study)
{
  int tval[2];
  this->Studies->GetTupleValue(study, tval);
  return tval[0];
}

//----------------------------------------------------------------------------
int vtkDICOMSorter::GetNumberOfSeriesInStudy(int study)
{
  int tval[2];
  this->Studies->GetTupleValue(study, tval);
  return tval[1];
}

//----------------------------------------------------------------------------
vtkStringArray *vtkDICOMSorter::GetFileNamesForSeries(int i)
{
  return (*this->Series)[i];
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::AddSeriesFileNames(int study, vtkStringArray *files)
{
  vtkIdType n = this->Studies->GetNumberOfTuples();
  int st[2];
  if (study == n)
    {
    st[0] = static_cast<int>(this->Series->size());
    st[1] = 1;
    this->Studies->InsertNextTupleValue(st);
    }
  else if (n >= 0 && study == n-1)
    {
    this->Studies->GetTupleValue(study, st);
    st[1]++;
    this->Studies->SetTupleValue(study, st);
    }
  else
    {
    vtkErrorMacro("AddSeriesFileNames: non-monotonically increasing study")
    }

  this->Series->push_back(files);
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::SortFiles(vtkStringArray *input)
{
  vtkSmartPointer<vtkUnsignedShortArray> groups =
    vtkSmartPointer<vtkUnsignedShortArray>::New();
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  parser->AddObserver(
    vtkCommand::ErrorEvent, this, &vtkDICOMSorter::RelayError);

  groups->InsertNextValue(0x0020);
  parser->SetMetaData(meta);
  parser->SetGroups(groups);

  FileInfoVectorList sortedFiles;
  FileInfoVectorList::iterator li;

  vtkIdType numberOfStrings = input->GetNumberOfValues();
  for (vtkIdType j = 0; j < numberOfStrings; j++)
    {
    const std::string& fileName = input->GetValue(j);
    this->SetInternalFileName(fileName.c_str());

    // Skip anything that is a directory
    if (vtksys::SystemTools::FileIsDirectory(fileName.c_str()))
      {
      continue;
      }

    // Read the file metadata
    this->SetInternalFileName(fileName.c_str());
    parser->SetFileName(fileName.c_str());
    parser->Update();
    if (!parser->GetPixelDataFound())
      {
      if (!this->ErrorCode)
        {
        this->ErrorCode = parser->GetErrorCode();
        }
      if (this->ErrorCode || this->RequirePixelData)
        {
        continue;
        }
      }

    // Insert the file into the sorted list
    FileInfo fileInfo;
    fileInfo.FileName = fileName;
    fileInfo.StudyUID = meta->GetAttributeValue(DC::StudyInstanceUID);
    fileInfo.SeriesUID = meta->GetAttributeValue(DC::SeriesInstanceUID);
    fileInfo.InstanceNumber =
      meta->GetAttributeValue(DC::InstanceNumber).AsUnsignedInt();

    const char *studyUID = fileInfo.StudyUID.GetCharData();
    const char *seriesUID = fileInfo.SeriesUID.GetCharData();

    bool foundSeries = false;
    for (li = sortedFiles.begin(); li != sortedFiles.end(); ++li)
      {
      // compare studyId first, then seriesId
      int c1 = vtkDICOMUtilities::CompareUIDs(
        studyUID, (*li)[0].StudyUID.GetCharData());
      int c2 = 0;
      if (c1 == 0)
        {
        c2 = vtkDICOMUtilities::CompareUIDs(
          seriesUID, (*li)[0].SeriesUID.GetCharData());
        }
      if (c1 == 0 && c2 == 0)
        {
        (*li).push_back(fileInfo);
        foundSeries = true;
        break;
        }
      else if (c1 >= 0 || (c1 == 0 && c2 >= 0))
        {
        break;
        }
      }

    if (!foundSeries)
      {
      std::vector<FileInfo> newSeries;
      newSeries.push_back(fileInfo);
      sortedFiles.insert(li, newSeries);
      }
    }

  // Sort each series by InstanceNumber
  int studyCount = 0;

  vtkDICOMValue lastStudyUID;
  for (li = sortedFiles.begin(); li != sortedFiles.end(); ++li)
    {
    std::vector<FileInfo> &v = *li;
    std::stable_sort(v.begin(), v.end(), CompareInstance);

    // Is this a new study?
    if (studyCount == 0 || v[0].StudyUID != lastStudyUID)
      {
      lastStudyUID = v[0].StudyUID;
      studyCount++;
      }

    vtkSmartPointer<vtkStringArray> sa =
      vtkSmartPointer<vtkStringArray>::New();
    vtkIdType n = static_cast<vtkIdType>(v.size());
    sa->SetNumberOfValues(n);
    for (vtkIdType i = 0; i < n; i++)
      {
      sa->SetValue(i, v[i].FileName);
      }
    this->AddSeriesFileNames(studyCount - 1, sa);
    }
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::Execute()
{
  // Clear the output
  this->OutputFileNames->Reset();
  this->Series->clear();
  this->Studies->Reset();
  this->SetInputFileName(0);
  this->ErrorCode = 0;

  if (this->InputFileName) // The input was a single file
    {
    if (!vtksys::SystemTools::FileExists(this->InputFileName))
      {
      this->ErrorCode = vtkErrorCode::FileNotFoundError;
      vtkErrorMacro("File not found: " << this->InputFileName);
      return;
      }
    else if (vtksys::SystemTools::FileIsDirectory(this->InputFileName))
      {
      this->ErrorCode = vtkErrorCode::CannotOpenFileError;
      vtkErrorMacro("Named file is a directory: " << this->InputFileName);
      return;
      }

    vtkDICOMParser *parser = vtkDICOMParser::New();
    parser->AddObserver(
      vtkCommand::ErrorEvent, this, &vtkDICOMSorter::RelayError);
    this->SetInternalFileName(this->InputFileName);
    parser->SetFileName(this->InputFileName);
    parser->Update();
    int pixelDataFound = parser->GetPixelDataFound();
    unsigned long errorCode = parser->GetErrorCode();
    parser->Delete();

    if (!pixelDataFound)
      {
      if (!errorCode)
        {
        this->ErrorCode = vtkErrorCode::FileFormatError;
        vtkErrorMacro("Not a DICOM image: " << this->InputFileName);
        }
      else if (!this->ErrorCode)
        {
        this->ErrorCode = errorCode;
        }
      return;
      }

    // Find the path to the file
    std::vector<std::string> path;
    vtksys::SystemTools::SplitPath(this->InputFileName, path);

    // Replace file with a glob pattern
    std::string ext =
      vtksys::SystemTools::GetFilenameLastExtension(path.back());
    path.back() = "*";
    if (ext == ".dc" || ext == ".dcm" || ext == ".DC" || ext == ".DCM")
      {
      path.back() += ext;
      }
    std::string pattern = vtksys::SystemTools::JoinPath(path);

    // Find all the files that match the pattern
    vtksys::Glob glob;
    glob.RecurseOff();
    glob.FindFiles(pattern);
    std::vector<std::string> files = glob.GetFiles();

    // Create a vtkStringArray from the matching files
    vtkSmartPointer<vtkStringArray> array =
      vtkSmartPointer<vtkStringArray>::New();
    for (size_t i = 0; i < files.size(); i++)
      {
      array->InsertNextValue(files[i]);
      }

    // Sort the files
    this->SortFiles(array);

    // Set FileNames to contain the matched series
    bool done = false;
    for (size_t j = 0; j < this->Series->size() && !done; j++)
      {
      vtkStringArray *sa = (*this->Series)[j];
      for (vtkIdType k = 0; k < sa->GetNumberOfValues(); k++)
        {
        if (vtksys::SystemTools::ComparePath(
              sa->GetValue(k).c_str(), this->InputFileName))
          {
          this->OutputFileNames->DeepCopy(sa);
          done = true;
          break;
          }
        }
      }

    // This should never happen
    if (!done)
      {
      vtkErrorMacro("Pattern didn't match original file.");
      }
    }
  else if (this->InputFileNames) // The input was a list of files
    {
    this->SortFiles(this->InputFileNames);

    for (size_t j = 0; j < this->Series->size(); j++)
      {
      vtkStringArray *sa = (*this->Series)[j];
      for (vtkIdType k = 0; k < sa->GetNumberOfValues(); k++)
        {
        this->OutputFileNames->InsertNextValue(sa->GetValue(k));
        }
      }
    }
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::Update()
{
  if (this->GetMTime() > this->UpdateTime.GetMTime() ||
      (this->InputFileNames &&
       this->InputFileNames->GetMTime() > this->UpdateTime.GetMTime()))
    {
    this->Execute();
    this->UpdateTime.Modified();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::SetInternalFileName(const char *name)
{
  if (this->InternalFileName == NULL && name == NULL)
    {
    return;
    }
  if (this->InternalFileName != 0 && name != 0 &&
      strcmp(this->InternalFileName, name) == 0)
    {
    return;
    }
  if (this->InternalFileName)
    {
    delete [] this->InternalFileName;
    }
  if (name)
    {
    size_t n = strlen(name) + 1;
    char *cp1 =  new char[n];
    const char *cp2 = (name);
    this->InternalFileName = cp1;
    do { *cp1++ = *cp2++; } while (--n);
    }
  else
    {
    this->InternalFileName = 0;
    }
}

//----------------------------------------------------------------------------
void vtkDICOMSorter::RelayError(vtkObject *o, unsigned long e, void *data)
{
  if (e == vtkCommand::ErrorEvent)
    {
    vtkDICOMParser *parser = vtkDICOMParser::SafeDownCast(o);
    if (parser)
      {
      this->SetErrorCode(parser->GetErrorCode());
      this->SetInternalFileName(parser->GetFileName());
      }
    vtkErrorMacro(<< static_cast<char *>(data));
    }
  else
    {
    this->InvokeEvent(e, data);
    }
}
