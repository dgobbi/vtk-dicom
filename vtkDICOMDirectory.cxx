/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMDirectory.h"

#include "vtkDICOMItem.h"
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
#include <map>
#include <algorithm>
#include <utility>

#include <vtksys/SystemTools.hxx>
#include <vtksys/Directory.hxx>

#include <ctype.h>

vtkStandardNewMacro(vtkDICOMDirectory);

//----------------------------------------------------------------------------
// A vector of string arrays

class vtkDICOMDirectory::StringArrayVector
  : public std::vector<vtkSmartPointer<vtkStringArray> >
{
};

//----------------------------------------------------------------------------
// Information used to sort DICOM files.

struct vtkDICOMDirectory::FileInfo
{
  std::string FileName;
  // -- PATIENT --
  vtkDICOMValue PatientName;
  vtkDICOMValue PatientID;
  // -- STUDY --
  vtkDICOMValue StudyDate;
  vtkDICOMValue StudyTime;
  vtkDICOMValue StudyUID;
  // -- SERIES --
  vtkDICOMValue SeriesUID;
  unsigned int SeriesNumber;
  // -- IMAGE --
  unsigned int InstanceNumber;
};

bool vtkDICOMDirectory::CompareInstance(
  const FileInfo &fi1, const FileInfo &fi2)
{
  return (fi1.InstanceNumber < fi2.InstanceNumber);
}

//----------------------------------------------------------------------------
// A temporary container class for use with stl algorithms

class vtkDICOMDirectory::FileInfoVectorList
  : public std::list<std::vector<vtkDICOMDirectory::FileInfo> >
{
};

//----------------------------------------------------------------------------
vtkDICOMDirectory::vtkDICOMDirectory()
{
  this->DirectoryName = 0;
  this->Series = new StringArrayVector;
  this->Studies = vtkIntArray::New();
  this->Studies->SetNumberOfComponents(2);
  this->Patients = vtkIntArray::New();
  this->Patients->SetNumberOfComponents(2);
  this->FileSetID = 0;
  this->ErrorCode = 0;
  this->InternalFileName = 0;
  this->RequirePixelData = 1;
  this->ScanDepth = 1;
}

//----------------------------------------------------------------------------
vtkDICOMDirectory::~vtkDICOMDirectory()
{
  if (this->DirectoryName)
    {
    delete [] this->DirectoryName;
    }
  if (this->InternalFileName)
    {
    delete [] this->InternalFileName;
    }

  delete this->Series;
  this->Studies->Delete();
  this->Patients->Delete();
  delete [] this->FileSetID;
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  const char *inputDirectory = this->GetDirectoryName();
  os << indent << "DirectoryName: "
     << (inputDirectory ? inputDirectory : "(NULL)") << "\n";

  os << indent << "ScanDepth: " << this->ScanDepth << "\n";

  os << indent << "RequirePixelData: "
     << (this->RequirePixelData ? "On\n" : "Off\n");

  os << indent << "NumberOfSeries: " << this->GetNumberOfSeries() << "\n";
  os << indent << "NumberOfStudies: " << this->GetNumberOfStudies() << "\n";
  os << indent << "NumberOfPatients: " << this->GetNumberOfPatients() << "\n";

  os << indent << "FileSetID: "
     << (this->FileSetID ? this->FileSetID : "(NULL)") << "\n";
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::SetDirectoryName(const char *name)
{
  if (name == this->DirectoryName ||
      (name && this->DirectoryName &&
       strcmp(name, this->DirectoryName) == 0))
    {
    return;
    }

  delete [] this->DirectoryName;
  this->DirectoryName = 0;
  if (name)
    {
    char *cp = new char[strlen(name) + 1];
    strcpy(cp, name);
    this->DirectoryName = cp;
    }
  this->Modified();
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetNumberOfSeries()
{
  return static_cast<int>(this->Series->size());
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetNumberOfStudies()
{
  return this->Studies->GetNumberOfTuples();
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetFirstSeriesForStudy(int study)
{
  int tval[2];
  this->Studies->GetTupleValue(study, tval);
  return tval[0];
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetLastSeriesForStudy(int study)
{
  int tval[2];
  this->Studies->GetTupleValue(study, tval);
  return tval[1];
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetNumberOfPatients()
{
  return this->Patients->GetNumberOfTuples();
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetFirstStudyForPatient(int patient)
{
  int tval[2];
  this->Patients->GetTupleValue(patient, tval);
  return tval[0];
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetLastStudyForPatient(int patient)
{
  int tval[2];
  this->Patients->GetTupleValue(patient, tval);
  return tval[1];
}

//----------------------------------------------------------------------------
vtkStringArray *vtkDICOMDirectory::GetFileNamesForSeries(int i)
{
  return (*this->Series)[i];
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::AddSeriesFileNames(
  int patient, int study, vtkStringArray *files)
{
  vtkIdType m = this->Patients->GetNumberOfTuples();
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
    st[1] = static_cast<int>(this->Series->size());
    this->Studies->SetTupleValue(study, st);
    }
  else
    {
    vtkErrorMacro("AddSeriesFileNames: non-monotonically increasing study")
    return;
    }

  if (patient == m)
    {
    st[0] = study;
    st[1] = st[0];
    this->Patients->InsertNextTupleValue(st);
    }
  else if (m >= 0 && patient == m-1)
    {
    this->Patients->GetTupleValue(patient, st);
    st[1] = study;
    this->Patients->SetTupleValue(patient, st);
    }
  else
    {
    vtkErrorMacro("AddSeriesFileNames: non-monotonically increasing patient")
    return;
    }

  this->Series->push_back(files);
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::SortFiles(vtkStringArray *input)
{
  vtkSmartPointer<vtkUnsignedShortArray> groups =
    vtkSmartPointer<vtkUnsignedShortArray>::New();
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  parser->AddObserver(
    vtkCommand::ErrorEvent, this, &vtkDICOMDirectory::RelayError);

  groups->InsertNextValue(0x0008); // For study and series info.
  groups->InsertNextValue(0x0010); // For patient info.
  groups->InsertNextValue(0x0020); // For study and series info.
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
    fileInfo.PatientName = meta->GetAttributeValue(DC::PatientName);
    fileInfo.PatientID = meta->GetAttributeValue(DC::PatientID);
    fileInfo.StudyDate = meta->GetAttributeValue(DC::StudyDate);
    fileInfo.StudyTime = meta->GetAttributeValue(DC::StudyTime);
    fileInfo.StudyUID = meta->GetAttributeValue(DC::StudyInstanceUID);
    fileInfo.SeriesUID = meta->GetAttributeValue(DC::SeriesInstanceUID);
    fileInfo.SeriesNumber =
      meta->GetAttributeValue(DC::SeriesNumber).AsUnsignedInt();
    fileInfo.InstanceNumber =
      meta->GetAttributeValue(DC::InstanceNumber).AsUnsignedInt();

    const char *patientName = fileInfo.PatientName.GetCharData();
    const char *patientID = fileInfo.PatientID.GetCharData();
    const char *studyDate = fileInfo.StudyDate.GetCharData();
    const char *studyTime = fileInfo.StudyTime.GetCharData();
    const char *studyUID = fileInfo.StudyUID.GetCharData();
    const char *seriesUID = fileInfo.SeriesUID.GetCharData();
    unsigned int seriesNumber = fileInfo.SeriesNumber;

    patientName = (patientName ? patientName : "");
    patientID = (patientID ? patientID : "");

    bool foundSeries = false;
    for (li = sortedFiles.begin(); li != sortedFiles.end(); ++li)
      {
      // Compare patient, then study, then series.
      const char *patientName2 = (*li)[0].PatientName.GetCharData();
      patientName2 = (patientName2 ? patientName2 : "");
      const char *patientID2 = (*li)[0].PatientID.GetCharData();
      patientID2 = (patientID2 ? patientID2 : "");
      int c = strcmp(patientID, patientID2);
      if (c != 0 || patientID[0] == '\0')
        {
        // Use ID to identify patient, but use name to sort.
        int c2 = strcmp(patientName, patientName2);
        c = (c2 == 0 ? c : c2);
        }
      if (c == 0)
        {
        c = vtkDICOMUtilities::CompareUIDs(
          studyUID, (*li)[0].StudyUID.GetCharData());
        if (c != 0 || studyUID == 0)
          {
          // Use UID to identify study, but use date to sort.
          int c2 = 0;
          const char *studyDate2 = (*li)[0].StudyDate.GetCharData();
          if (studyDate && studyDate2)
            {
            c2 = strcmp(studyDate, studyDate2);
            if (c2 == 0)
              {
              const char *studyTime2 = (*li)[0].StudyTime.GetCharData();
              if (studyTime && studyTime2)
                {
                c2 = strcmp(studyTime, studyTime2);
                }
              }
            }
          c = (c2 == 0 ? c : c2);
          }
        if (c == 0)
          {
          c = vtkDICOMUtilities::CompareUIDs(
            seriesUID, (*li)[0].SeriesUID.GetCharData());
          if (c != 0 || seriesUID == 0)
            {
            // Use UID to identify series, but use series number to sort.
            int c2 = (*li)[0].SeriesNumber - seriesNumber;
            c = (c2 == 0 ? c : c2);
            }
          }
        }
      if (c == 0 && seriesUID != 0)
        {
        (*li).push_back(fileInfo);
        foundSeries = true;
        break;
        }
      else if (c >= 0)
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
  int patientCount = this->GetNumberOfPatients();
  int studyCount = this->GetNumberOfStudies();

  vtkDICOMValue lastStudyUID;
  vtkDICOMValue lastPatientID;
  for (li = sortedFiles.begin(); li != sortedFiles.end(); ++li)
    {
    std::vector<FileInfo> &v = *li;
    std::stable_sort(v.begin(), v.end(), CompareInstance);

    // Is this a new patient or a new study?
    if (!lastPatientID.IsValid() || v[0].PatientID != lastPatientID)
      {
      lastPatientID = v[0].PatientID;
      patientCount++;
      lastStudyUID = v[0].StudyUID;
      studyCount++;
      }
    else if (!lastStudyUID.IsValid() || v[0].StudyUID != lastStudyUID)
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
    this->AddSeriesFileNames(patientCount-1, studyCount-1, sa);
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::ProcessDirectoryFile(
  const char *dirname, vtkDICOMMetaData *meta)
{
  // Get the ID of this file set (informative only).
  if (meta->HasAttribute(DC::FileSetID))
    {
    std::string fileSetID = meta->GetAttributeValue(DC::FileSetID).AsString();
    this->FileSetID = new char[fileSetID.length() + 1];
    strcpy(this->FileSetID, fileSetID.c_str());
    }

  // Get the directory as a sequence.
  const vtkDICOMValue& seq =
    meta->GetAttributeValue(DC::DirectoryRecordSequence);
  unsigned int n = seq.GetNumberOfValues();
  const vtkDICOMItem *items = seq.GetSequenceData();

  // The DICOMDIR uses byte offsets to identify items in the sequence.
  std::map<unsigned int, unsigned int> offsetToIndexMap;
  for (unsigned int i = 0; i < n; i++)
    {
    offsetToIndexMap[items[i].GetByteOffset()] = i;
    }

  // Get the first entry.
  unsigned int offset =
    meta->GetAttributeValue(
      DC::OffsetOfTheFirstDirectoryRecordOfTheRootDirectoryEntity)
        .AsUnsignedInt();

  // This check is just for insurance.
  if (offset == 0 && n > 0)
    {
    offset = items[0].GetByteOffset();
    }

  // A stack to track the directory level.
  std::vector<std::pair<unsigned int, std::string> > offsetStack;
  int patientIdx = this->GetNumberOfPatients();
  int studyIdx = this->GetNumberOfStudies();

  // List of filenames for the current series.
  vtkSmartPointer<vtkStringArray> fileNames =
    vtkSmartPointer<vtkStringArray>::New();

  // Path broken into components.
  std::vector<std::string> path;
  vtksys::SystemTools::SplitPath(dirname, path);
  size_t pathDepth = path.size();

  // The entry type that is currently being processed.
  std::string entryType;

  // Go through the directory, using the "next" and "child" pointers.
  while (offset != 0)
    {
    unsigned int offsetOfChild = 0;
    std::map<unsigned int, unsigned int>::iterator iter =
      offsetToIndexMap.find(offset);
    offset = 0;

    if (iter != offsetToIndexMap.end() && iter->second != 0xffffffffu)
      {
      // Get the item index, mark the item as used.
      unsigned int j = iter->second;
      iter->second = 0xffffffffu;

      offset = items[j].GetAttributeValue(
        DC::OffsetOfTheNextDirectoryRecord).AsUnsignedInt();

      offsetOfChild = items[j].GetAttributeValue(
        DC::OffsetOfReferencedLowerLevelDirectoryEntity).AsUnsignedInt();

      entryType = items[j].GetAttributeValue(
        DC::DirectoryRecordType).AsString();

      if (entryType == "IMAGE")
        {
        const vtkDICOMValue& fileID =
          items[j].GetAttributeValue(DC::ReferencedFileID);

        unsigned int m = fileID.GetNumberOfValues();
        for (unsigned int j = 0; j < m; j++)
          {
          path.push_back(fileID.GetString(j));
          }
        fileNames->InsertNextValue(vtksys::SystemTools::JoinPath(path));
        path.resize(pathDepth);
        }
      }

    if (offsetOfChild != 0)
      {
      // Go up one directory level.
      offsetStack.push_back(std::make_pair(offset, entryType));
      offset = offsetOfChild;
      }
    else
      {
      // Pop the stack until the next offset is not zero.
      while (offset == 0)
        {
        if (entryType == "STUDY")
          {
          patientIdx++;
          }
        else if (entryType == "SERIES")
          {
          studyIdx++;
          }
        else if (entryType == "IMAGE")
          {
          this->AddSeriesFileNames(patientIdx, studyIdx, fileNames);
          fileNames = vtkSmartPointer<vtkStringArray>::New();
          }

        if (offsetStack.size() > 0)
          {
          // Go down one directory level.
          offset = offsetStack.back().first;
          entryType = offsetStack.back().second;
          offsetStack.pop_back();
          }
        else
          {
          break;
          }
        }
      }
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::ProcessDirectory(
  const char *dirname, int depth, vtkStringArray *files)
{
  // Find the path to the directory.
  std::vector<std::string> path;
  vtksys::SystemTools::SplitPath(dirname, path);

  // Build the path to the DICOMDIR file.
  path.push_back("DICOMDIR");
  std::string dicomdir = vtksys::SystemTools::JoinPath(path);
  path.pop_back();

  // Check to see if the DICOMDIR file exists.
  if (vtksys::SystemTools::FileExists(dicomdir.c_str(), true))
    {
    vtkSmartPointer<vtkDICOMMetaData> meta =
      vtkSmartPointer<vtkDICOMMetaData>::New();
    vtkDICOMParser *parser = vtkDICOMParser::New();
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
      // Convert the DICOMDIR into a list of filenames.
      this->ProcessDirectoryFile(dirname, meta);
      return;
      }
    }

  // If depth is zero, recursion is complete.
  if (depth <= 0)
    {
    return;
    }

  vtksys::Directory d;
  if (!d.Load(dirname))
    {
    // Only fail at the initial depth.
    if (depth == this->ScanDepth)
      {
      vtkErrorMacro(<< "Could not read directory " << dirname);
      this->ErrorCode = vtkErrorCode::CannotOpenFileError;
      return;
      }
    }

  unsigned long n = d.GetNumberOfFiles();
  for (unsigned long i = 0; i < n; i++)
    {
    if (d.GetFile(i)[0] != '.')
      {
      path.push_back(d.GetFile(i));
      std::string fileString = vtksys::SystemTools::JoinPath(path);
      path.pop_back();
      if (vtksys::SystemTools::FileIsDirectory(fileString.c_str()))
        {
        if (depth > 1)
          {
          this->ProcessDirectory(fileString.c_str(), depth-1, files);
          }
        }
      else if (vtkDICOMUtilities::IsDICOMFile(fileString.c_str()))
        {
        files->InsertNextValue(fileString);
        }
      }
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::Execute()
{
  // Clear the output
  this->Series->clear();
  this->Studies->Reset();
  this->Patients->Reset();
  delete [] this->FileSetID;
  this->FileSetID = 0;
  this->ErrorCode = 0;

  if (this->DirectoryName == 0)
    {
    // No directory is a valid input.  Return an empty output.
    return;
    }
  else if (!vtksys::SystemTools::FileExists(this->DirectoryName))
    {
    this->ErrorCode = vtkErrorCode::FileNotFoundError;
    vtkErrorMacro("Directory not found: " << this->DirectoryName);
    return;
    }
  else if (!vtksys::SystemTools::FileIsDirectory(this->DirectoryName))
    {
    this->ErrorCode = vtkErrorCode::CannotOpenFileError;
    vtkErrorMacro("Found a file, not a directory: " << this->DirectoryName);
    return;
    }

  vtkSmartPointer<vtkStringArray> files =
    vtkSmartPointer<vtkStringArray>::New();
  this->ProcessDirectory(this->DirectoryName, this->ScanDepth, files);

  if (files->GetNumberOfValues() > 0)
    {
    this->SortFiles(files);
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::Update()
{
  if (this->GetMTime() > this->UpdateTime.GetMTime())
    {
    this->Execute();
    this->UpdateTime.Modified();
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::SetInternalFileName(const char *name)
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
void vtkDICOMDirectory::RelayError(vtkObject *o, unsigned long e, void *data)
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
