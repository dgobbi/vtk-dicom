/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2024 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMFileSorter.h"
#include "vtkDICOMFile.h"
#include "vtkDICOMFileDirectory.h"
#include "vtkDICOMFilePath.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMUtilities.h"
#include "vtkDICOMCharacterSet.h"

#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"
#include "vtkStringArray.h"
#include "vtkIntArray.h"
#include "vtkErrorCode.h"
#include "vtkCommand.h"
#include "vtkUnsignedShortArray.h"

#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include <ctype.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define SetTupleValue SetTypedTuple
#define GetTupleValue GetTypedTuple
#define InsertNextTupleValue InsertNextTypedTuple
#endif

vtkStandardNewMacro(vtkDICOMFileSorter);

//----------------------------------------------------------------------------
// A vector of string arrays

class vtkDICOMFileSorter::StringArrayVector
  : public std::vector<vtkSmartPointer<vtkStringArray> >
{
};

//----------------------------------------------------------------------------
// Information used to sort DICOM files.

struct vtkDICOMFileSorter::FileInfo
{
  std::string FileName;
  vtkDICOMValue StudyUID;
  vtkDICOMValue SeriesUID;
  vtkDICOMValue InstanceUID;
  unsigned int InstanceNumber;
};

bool vtkDICOMFileSorter::CompareInstance(
  const FileInfo &fi1, const FileInfo &fi2)
{
  return (fi1.InstanceNumber < fi2.InstanceNumber);
}

//----------------------------------------------------------------------------
// A temporary container class for use with stl algorithms

class vtkDICOMFileSorter::FileInfoVectorList
  : public std::list<std::vector<vtkDICOMFileSorter::FileInfo> >
{
};

//----------------------------------------------------------------------------
vtkDICOMFileSorter::vtkDICOMFileSorter()
{
  this->InputFileName = nullptr;
  this->InputFileNames = nullptr;
  this->OutputFileNames = vtkStringArray::New();
  this->Series = new StringArrayVector;
  this->Studies = vtkIntArray::New();
  this->Studies->SetNumberOfComponents(2);
  this->ErrorCode = 0;
  this->InternalFileName = nullptr;
  this->RequirePixelData = 1;
}

//----------------------------------------------------------------------------
vtkDICOMFileSorter::~vtkDICOMFileSorter()
{
  delete [] this->InputFileName;
  if (this->InputFileNames)
  {
    this->InputFileNames->Delete();
  }
  this->OutputFileNames->Delete();

  delete [] this->InternalFileName;

  delete this->Series;
  this->Studies->Delete();
}

//----------------------------------------------------------------------------
void vtkDICOMFileSorter::PrintSelf(ostream& os, vtkIndent indent)
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
void vtkDICOMFileSorter::SetInputFileName(const char *name)
{
  // mutual exclusion with InputFileNames
  if (name) { this->SetInputFileNames(nullptr); }

  if (name == this->InputFileName ||
      (name && this->InputFileName &&
       strcmp(name, this->InputFileName) == 0))
  {
    return;
  }

  delete [] this->InputFileName;
  this->InputFileName = nullptr;
  if (name)
  {
    char *cp = new char[strlen(name) + 1];
    strcpy(cp, name);
    this->InputFileName = cp;
  }
  this->Modified();
}

//----------------------------------------------------------------------------
void vtkDICOMFileSorter::SetInputFileNames(vtkStringArray *input)
{
  // mutual exclusion with InputFileName
  if (input) { this->SetInputFileName(nullptr); }

  vtkSetObjectBodyMacro(InputFileNames, vtkStringArray, input);
}

//----------------------------------------------------------------------------
int vtkDICOMFileSorter::GetNumberOfSeries()
{
  return static_cast<int>(this->Series->size());
}

//----------------------------------------------------------------------------
int vtkDICOMFileSorter::GetNumberOfStudies()
{
  return this->Studies->GetNumberOfTuples();
}

//----------------------------------------------------------------------------
int vtkDICOMFileSorter::GetFirstSeriesForStudy(int study)
{
  int tval[2];
  this->Studies->GetTupleValue(study, tval);
  return tval[0];
}

//----------------------------------------------------------------------------
int vtkDICOMFileSorter::GetLastSeriesForStudy(int study)
{
  int tval[2];
  this->Studies->GetTupleValue(study, tval);
  return tval[1];
}

//----------------------------------------------------------------------------
vtkStringArray *vtkDICOMFileSorter::GetFileNamesForSeries(int i)
{
  return (*this->Series)[i];
}

//----------------------------------------------------------------------------
void vtkDICOMFileSorter::AddSeriesFileNames(int study, vtkStringArray *files)
{
  vtkIdType n = this->Studies->GetNumberOfTuples();
  int st[2];
  if (study == n)
  {
    st[0] = static_cast<int>(this->Series->size());
    st[1] = st[0];
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
    vtkErrorMacro("AddSeriesFileNames: non-monotonically increasing study");
  }

  this->Series->push_back(files);
}

//----------------------------------------------------------------------------
void vtkDICOMFileSorter::SortFiles(vtkStringArray *input)
{
  vtkSmartPointer<vtkUnsignedShortArray> groups =
    vtkSmartPointer<vtkUnsignedShortArray>::New();
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  parser->AddObserver(
    vtkCommand::ErrorEvent, this, &vtkDICOMFileSorter::RelayError);

  groups->InsertNextValue(0x0008);
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

    int code = vtkDICOMFile::Access(fileName.c_str(), vtkDICOMFile::In);
    if (code == vtkDICOMFile::FileIsDirectory)
    {
      // Skip anything that is a directory
      continue;
    }
    else if (code != 0)
    {
      const char *errText = "Can't open the file ";
      this->SetErrorCode(vtkErrorCode::CannotOpenFileError);
      if (code == vtkDICOMFile::AccessDenied)
      {
        errText = "No permission to read the file ";
      }
      else if (code == vtkDICOMFile::FileNotFound)
      {
        errText = "File not found ";
      }
      else if (code == vtkDICOMFile::ImpossiblePath)
      {
        errText = "Bad file path ";
      }
      vtkErrorMacro("SortFiles: " << errText << this->InternalFileName);
      continue;
    }

    // Read the file metadata
    meta->Initialize();
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
    fileInfo.StudyUID = meta->Get(DC::StudyInstanceUID);
    fileInfo.SeriesUID = meta->Get(DC::SeriesInstanceUID);
    fileInfo.InstanceUID = meta->Get(DC::SOPInstanceUID);
    fileInfo.InstanceNumber = meta->Get(DC::InstanceNumber).AsUnsignedInt();

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
      if (c1 == 0 && c2 == 0 && seriesUID != nullptr)
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

    // Check for duplicate instances, put them into a new series
    vtkIdType n = static_cast<vtkIdType>(v.size());
    std::vector<vtkIdType> duplicate(n);
    std::vector<vtkIdType> seriesLength;
    seriesLength.push_back(0);
    vtkIdType numberOfDuplicates = 0;
    for (vtkIdType i = 0; i < n; i++)
    {
      const vtkDICOMValue& uid = v[i].InstanceUID;
      vtkIdType count = 0;
      if (uid.GetVL() > 0)
      {
        for (vtkIdType j = 0; j < i; j++)
        {
          if (v[j].InstanceUID == uid)
          {
            count++;
          }
        }
      }
      duplicate[i] = count;
      if (count > numberOfDuplicates)
      {
        numberOfDuplicates = count;
        seriesLength.push_back(0);
      }
      seriesLength[count]++;
    }

    for (vtkIdType k = 0; k <= numberOfDuplicates; k++)
    {
      vtkSmartPointer<vtkStringArray> sa =
        vtkSmartPointer<vtkStringArray>::New();
      sa->SetNumberOfValues(seriesLength[k]);
      vtkIdType j = 0;
      for (vtkIdType i = 0; i < n; i++)
      {
        if (duplicate[i] == k)
        {
          sa->SetValue(j++, v[i].FileName);
        }
      }
      this->AddSeriesFileNames(studyCount - 1, sa);
    }
  }
}

//----------------------------------------------------------------------------
void vtkDICOMFileSorter::Execute()
{
  // Clear the output
  this->OutputFileNames->Reset();
  this->Series->clear();
  this->Studies->Reset();
  this->SetInternalFileName(nullptr);
  this->ErrorCode = 0;

  if (this->InputFileName) // The input was a single file
  {
    int code = vtkDICOMFile::Access(this->InputFileName, vtkDICOMFile::In);
    if (code == vtkDICOMFile::FileNotFound)
    {
      this->ErrorCode = vtkErrorCode::FileNotFoundError;
      vtkErrorMacro("File or directory not found: " << this->InputFileName);
      return;
    }
    else if (code == vtkDICOMFile::FileIsDirectory)
    {
      this->ErrorCode = vtkErrorCode::CannotOpenFileError;
      vtkErrorMacro("Named file is a directory: " << this->InputFileName);
      return;
    }
    else if (code == vtkDICOMFile::AccessDenied)
    {
      this->ErrorCode = vtkErrorCode::CannotOpenFileError;
      vtkErrorMacro("Permission denied: " << this->InputFileName);
      return;
    }
    else if (code == vtkDICOMFile::ImpossiblePath)
    {
      this->ErrorCode = vtkErrorCode::CannotOpenFileError;
      vtkErrorMacro("Bad file path: " << this->InputFileName);
      return;
    }
    else if (code != 0)
    {
      this->ErrorCode = vtkErrorCode::UnknownError;
      vtkErrorMacro("Unknown file error: " << this->InputFileName);
      return;
    }

    vtkDICOMParser *parser = vtkDICOMParser::New();
    parser->AddObserver(
      vtkCommand::ErrorEvent, this, &vtkDICOMFileSorter::RelayError);
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
    vtkDICOMFilePath path(this->InputFileName);

    // Create a glob pattern
    std::string base = path.GetBack();
    std::string ext = path.GetExtension();
    std::string pattern = "*";
    if (ext == ".dc" || ext == ".dcm" || ext == ".DC" || ext == ".DCM")
    {
      pattern += ext;
    }
    path.PopBack();
    std::string dirname = path.AsString();

    // Find all the files that match the pattern
    vtkDICOMFileDirectory d(dirname.c_str());

    // Create a vtkStringArray from the matching files
    vtkSmartPointer<vtkStringArray> array =
      vtkSmartPointer<vtkStringArray>::New();
    if (d.GetError() == 0)
    {
      int n = d.GetNumberOfEntries();
      for (int i = 0; i < n; i++)
      {
        const char *filename = d.GetEntry(i);
        if (vtkDICOMUtilities::PatternMatches(pattern.c_str(), filename) &&
            !d.IsDirectory(i))
        {
          path.PushBack(filename);
          array->InsertNextValue(path.AsString());
          path.PopBack();
        }
      }
    }

    // Sort the files
    this->SortFiles(array);

    // Find the series that the original file belonged to.  Do the search
    // twice, once with case-sensitivity and once without
    bool done = false;
    for (int caseless = 0; !done && caseless < 2; caseless++)
    {
      if (caseless)
      {
        vtkDICOMCharacterSet cs(vtkDICOMCharacterSet::ISO_IR_192);
        base = cs.CaseFoldedUTF8(base.data(), base.length());
      }
      for (size_t j = 0; j < this->Series->size() && !done; j++)
      {
        vtkStringArray *sa = (*this->Series)[j];
        for (vtkIdType k = 0; k < sa->GetNumberOfValues(); k++)
        {
          std::string tmp = vtkDICOMFilePath(sa->GetValue(k)).GetBack();
          if (caseless)
          {
            vtkDICOMCharacterSet cs(vtkDICOMCharacterSet::ISO_IR_192);
            tmp = cs.CaseFoldedUTF8(tmp.data(), tmp.length());
          }
          if (tmp == base)
          {
            this->OutputFileNames->DeepCopy(sa);
            done = true;
            break;
          }
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
void vtkDICOMFileSorter::Update()
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
void vtkDICOMFileSorter::SetInternalFileName(const char *name)
{
  if (this->InternalFileName == nullptr && name == nullptr)
  {
    return;
  }
  if (this->InternalFileName != nullptr && name != nullptr &&
      strcmp(this->InternalFileName, name) == 0)
  {
    return;
  }

  delete [] this->InternalFileName;

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
    this->InternalFileName = nullptr;
  }
}

//----------------------------------------------------------------------------
void vtkDICOMFileSorter::RelayError(vtkObject *o, unsigned long e, void *data)
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
