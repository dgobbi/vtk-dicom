/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMDirectory.h"

#include "vtkDICOMItem.h"
#include "vtkDICOMMetaData.h"
#include "vtkDICOMParser.h"
#include "vtkDICOMUtilities.h"
#include "vtkDICOMVR.h"

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
// Simple structs to hold directory information.

struct vtkDICOMDirectory::SeriesItem
{
  vtkDICOMItem Record;
  vtkSmartPointer<vtkStringArray> Files;
};

struct vtkDICOMDirectory::StudyItem
{
  vtkDICOMItem Record;
  vtkDICOMItem PatientRecord;
  int FirstSeries;
  int LastSeries;
};

struct vtkDICOMDirectory::PatientItem
{
  vtkDICOMItem Record;
  vtkSmartPointer<vtkIntArray> Studies;
};

class vtkDICOMDirectory::SeriesVector
  : public std::vector<vtkDICOMDirectory::SeriesItem>
{};

class vtkDICOMDirectory::StudyVector
  : public std::vector<vtkDICOMDirectory::StudyItem>
{};

class vtkDICOMDirectory::PatientVector
  : public std::vector<vtkDICOMDirectory::PatientItem>
{};

//----------------------------------------------------------------------------
// Information used to sort DICOM files.

struct vtkDICOMDirectory::FileInfo
{
  unsigned int InstanceNumber;
  const char *FileName;
};

struct vtkDICOMDirectory::SeriesInfo
{
  // -- PATIENT --
  vtkDICOMItem  PatientRecord;
  vtkDICOMValue PatientName;
  vtkDICOMValue PatientID;
  // -- STUDY --
  vtkDICOMItem  StudyRecord;
  vtkDICOMValue StudyDate;
  vtkDICOMValue StudyTime;
  vtkDICOMValue StudyUID;
  // -- SERIES --
  vtkDICOMItem  SeriesRecord;
  vtkDICOMValue SeriesUID;
  unsigned int SeriesNumber;
  std::vector<FileInfo> Files;
};

bool vtkDICOMDirectory::CompareInstance(
  const FileInfo &fi1, const FileInfo &fi2)
{
  return (fi1.InstanceNumber < fi2.InstanceNumber);
}

//----------------------------------------------------------------------------
// A temporary container class for use with stl algorithms

class vtkDICOMDirectory::SeriesInfoList
  : public std::list<vtkDICOMDirectory::SeriesInfo>
{};

//----------------------------------------------------------------------------
vtkDICOMDirectory::vtkDICOMDirectory()
{
  this->DirectoryName = 0;
  this->Series = new SeriesVector;
  this->Studies = new StudyVector;
  this->Patients = new PatientVector;
  this->FileSetID = 0;
  this->InternalFileName = 0;
  this->RequirePixelData = 1;
  this->ScanDepth = 1;
  this->Query = 0;
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
  delete this->Studies;
  delete this->Patients;
  delete [] this->FileSetID;
  delete this->Query;
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
void vtkDICOMDirectory::SetFindQuery(const vtkDICOMItem& item)
{
  if (this->Query != &item)
    {
    delete this->Query;
    this->Query = 0;
    if (!item.IsEmpty())
      {
      this->Query = new vtkDICOMItem;
      *(this->Query) = item;
      }
    }
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetNumberOfSeries()
{
  return static_cast<int>(this->Series->size());
}

//----------------------------------------------------------------------------
const vtkDICOMItem& vtkDICOMDirectory::GetSeriesRecord(int series)
{
  return (*this->Series)[series].Record;
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetNumberOfStudies()
{
  return static_cast<int>(this->Studies->size());
}

//----------------------------------------------------------------------------
const vtkDICOMItem& vtkDICOMDirectory::GetStudyRecord(int study)
{
  return (*this->Studies)[study].Record;
}

//----------------------------------------------------------------------------
const vtkDICOMItem& vtkDICOMDirectory::GetPatientRecordForStudy(int study)
{
  return (*this->Studies)[study].PatientRecord;
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetFirstSeriesForStudy(int study)
{
  return (*this->Studies)[study].FirstSeries;
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetLastSeriesForStudy(int study)
{
  return (*this->Studies)[study].LastSeries;
}

//----------------------------------------------------------------------------
int vtkDICOMDirectory::GetNumberOfPatients()
{
  return static_cast<int>(this->Patients->size());
}

//----------------------------------------------------------------------------
const vtkDICOMItem& vtkDICOMDirectory::GetPatientRecord(int patient)
{
  return (*this->Patients)[patient].Record;
}

//----------------------------------------------------------------------------
vtkIntArray *vtkDICOMDirectory::GetStudiesForPatient(int patient)
{
  return (*this->Patients)[patient].Studies;
}

//----------------------------------------------------------------------------
vtkStringArray *vtkDICOMDirectory::GetFileNamesForSeries(int i)
{
  return (*this->Series)[i].Files;
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::AddSeriesFileNames(
  int patient, int study, vtkStringArray *files,
  const vtkDICOMItem& patientRecord,
  const vtkDICOMItem& studyRecord,
  const vtkDICOMItem& seriesRecord)
{
  int m = static_cast<int>(this->Patients->size());
  int n = static_cast<int>(this->Studies->size());
  int series = static_cast<int>(this->Series->size());

  if (study == n)
    {
    this->Studies->push_back(StudyItem());
    StudyItem& item = this->Studies->back();
    item.Record = studyRecord;
    item.PatientRecord = patientRecord;
    item.FirstSeries = series;
    item.LastSeries = series;
    }
  else if (n >= 0 && study == n-1)
    {
    (*this->Studies)[study].LastSeries = series;
    }
  else
    {
    vtkErrorMacro("AddSeriesFileNames: non-monotonically increasing study")
    return;
    }

  if (patient == m)
    {
    this->Patients->push_back(PatientItem());
    PatientItem& item = this->Patients->back();
    item.Record = patientRecord;
    item.Studies = vtkSmartPointer<vtkIntArray>::New();
    item.Studies->InsertNextValue(study);
    }
  else if (m >= 0 && patient == m-1)
    {
    PatientItem& item = (*this->Patients)[patient];
    vtkIdType nn = item.Studies->GetMaxId() + 1;
    vtkIdType ii = 0;
    for (; ii < nn; ii++)
      {
      if (study == item.Studies->GetValue(ii))
        {
        break;
        }
      }
    if (ii == nn)
      {
      item.Studies->InsertNextValue(study);
      }
    }
  else
    {
    vtkErrorMacro("AddSeriesFileNames: non-monotonically increasing patient")
    return;
    }

  this->Series->push_back(SeriesItem());
  SeriesItem& item = this->Series->back();
  item.Record = seriesRecord;
  item.Files = files;
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::FillSeriesRecord(
  vtkDICOMItem *item, vtkDICOMMetaData *meta)
{
  static const DC::EnumType tags[] = {
    DC::SpecificCharacterSet,
    DC::SeriesDate,
    DC::SeriesTime,
    DC::Modality,
    DC::SeriesDescription,
    // DC::BodyPartExamined, // requires group 0018
    DC::SeriesInstanceUID,
    DC::SeriesNumber,
    DC::ItemDelimitationItem
  };

  const DC::EnumType *tag = tags;
  while (*tag != DC::ItemDelimitationItem)
    {
    item->SetAttributeValue(*tag, meta->GetAttributeValue(*tag));
    tag++;
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::FillStudyRecord(
  vtkDICOMItem *item, vtkDICOMMetaData *meta)
{
  static const DC::EnumType tags[] = {
    DC::SpecificCharacterSet,
    DC::StudyDate,
    DC::StudyTime,
    DC::ReferringPhysicianName,
    DC::PatientAge,
    DC::StudyInstanceUID,
    DC::StudyID,
    DC::AccessionNumber,
    DC::StudyDescription,
    DC::ItemDelimitationItem
  };

  const DC::EnumType *tag = tags;
  while (*tag != DC::ItemDelimitationItem)
    {
    item->SetAttributeValue(*tag, meta->GetAttributeValue(*tag));
    tag++;
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::FillPatientRecord(
  vtkDICOMItem *item, vtkDICOMMetaData *meta)
{
  static const DC::EnumType tags[] = {
    DC::SpecificCharacterSet,
    DC::PatientName,
    DC::PatientID,
    DC::PatientBirthDate,
    DC::PatientSex,
    DC::ItemDelimitationItem
  };

  const DC::EnumType *tag = tags;
  while (*tag != DC::ItemDelimitationItem)
    {
    item->SetAttributeValue(*tag, meta->GetAttributeValue(*tag));
    tag++;
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::SortFiles(vtkStringArray *input)
{
  vtkSmartPointer<vtkDICOMMetaData> meta =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  vtkSmartPointer<vtkDICOMMetaData> query =
    vtkSmartPointer<vtkDICOMMetaData>::New();
  vtkSmartPointer<vtkDICOMParser> parser =
    vtkSmartPointer<vtkDICOMParser>::New();

  parser->AddObserver(
    vtkCommand::ErrorEvent, this, &vtkDICOMDirectory::RelayError);

  parser->SetMetaData(meta);

  // these are the attributes that must be part of the query
  static const DC::EnumType requiredElements[] = {
    // basic required information
    DC::SpecificCharacterSet,
    // series-level information
    DC::SeriesDate,
    DC::SeriesTime,
    DC::Modality,
    DC::SeriesDescription,
    DC::BodyPartExamined,
    DC::SeriesInstanceUID,
    DC::SeriesNumber,
    // study-level information
    DC::StudyDate,
    DC::StudyTime,
    DC::ReferringPhysicianName,
    DC::PatientAge,
    DC::StudyInstanceUID,
    DC::StudyID,
    DC::AccessionNumber,
    DC::StudyDescription,
    // patient-level information
    DC::PatientName,
    DC::PatientID,
    DC::PatientBirthDate,
    DC::PatientSex,
    // delimiter to mark end of list
    DC::ItemDelimitationItem
  };

  for (const DC::EnumType *tagPtr = requiredElements;
       *tagPtr != DC::ItemDelimitationItem;
       ++tagPtr)
    {
    vtkDICOMVR vr = query->FindDictVR(0, *tagPtr);
    query->SetAttributeValue(*tagPtr, vtkDICOMValue(vr));
    }

  if (this->Query)
    {
    // add elements that the user requested for the query
    vtkDICOMDataElementIterator iter = this->Query->Begin();
    vtkDICOMDataElementIterator iterEnd = this->Query->End();
    while (iter != iterEnd)
      {
      query->SetAttributeValue(iter->GetTag(), iter->GetValue());
      ++iter;
      }
    // use a buffer size equal to one disk block
    parser->SetBufferSize(4096);
    }

  parser->SetQuery(query);

  SeriesInfoList sortedFiles;
  SeriesInfoList::iterator li;

  vtkIdType numberOfStrings = input->GetNumberOfValues();
  for (vtkIdType j = 0; j < numberOfStrings; j++)
    {
    const std::string& fileName = input->GetValue(j);

    // Skip anything that does not look like a DICOM file.
    if (!vtkDICOMUtilities::IsDICOMFile(fileName.c_str()))
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

    // Check for abort and update progress at 1% intervals
    if (!this->AbortExecute)
      {
      double progress = (j + 1.0)/numberOfStrings;
      if (progress == 1.0 || progress > this->GetProgress() + 0.01)
        {
        progress = static_cast<int>(progress*100.0)/100.0;
        this->UpdateProgress(progress);
        }
      }
    if (this->AbortExecute)
      {
      return;
      }

    // Check if the file matches the query
    if (this->Query)
      {
      if (!parser->GetQueryMatched())
        {
        continue;
        }
      }

    // Insert the file into the sorted list
    FileInfo fileInfo;
    fileInfo.InstanceNumber =
      meta->GetAttributeValue(DC::InstanceNumber).AsUnsignedInt();
    fileInfo.FileName = fileName.c_str(); // stored in input StringArray

    const vtkDICOMValue& patientNameValue =
      meta->GetAttributeValue(DC::PatientName);
    const vtkDICOMValue& patientIDValue =
      meta->GetAttributeValue(DC::PatientID);
    const vtkDICOMValue& studyDateValue =
      meta->GetAttributeValue(DC::StudyDate);
    const vtkDICOMValue& studyTimeValue =
      meta->GetAttributeValue(DC::StudyTime);
    const vtkDICOMValue& studyUIDValue =
      meta->GetAttributeValue(DC::StudyInstanceUID);
    const vtkDICOMValue& seriesUIDValue =
      meta->GetAttributeValue(DC::SeriesInstanceUID);
    unsigned int seriesNumber =
      meta->GetAttributeValue(DC::SeriesNumber).AsUnsignedInt();

    const char *patientName = patientNameValue.GetCharData();
    const char *patientID = patientIDValue.GetCharData();
    const char *studyDate = studyDateValue.GetCharData();
    const char *studyTime = studyTimeValue.GetCharData();
    const char *studyUID = studyUIDValue.GetCharData();
    const char *seriesUID = seriesUIDValue.GetCharData();

    patientName = (patientName ? patientName : "");
    patientID = (patientID ? patientID : "");

    bool foundSeries = false;
    for (li = sortedFiles.begin(); li != sortedFiles.end(); ++li)
      {
      // Compare patient, then study, then series.
      const char *patientName2 = li->PatientName.GetCharData();
      patientName2 = (patientName2 ? patientName2 : "");
      const char *patientID2 = li->PatientID.GetCharData();
      patientID2 = (patientID2 ? patientID2 : "");
      int c = strcmp(patientID2, patientID);
      if (c != 0 || patientID[0] == '\0')
        {
        // Use ID to identify patient, but use name to sort.
        int c2 = strcmp(patientName2, patientName);
        c = (c2 == 0 ? c : c2);
        }
      if (c == 0)
        {
        c = vtkDICOMUtilities::CompareUIDs(
          studyUID, li->StudyUID.GetCharData());
        if (c != 0 || studyUID == 0)
          {
          // Use UID to identify study, but use date to sort.
          int c2 = 0;
          const char *studyDate2 = li->StudyDate.GetCharData();
          if (studyDate && studyDate2)
            {
            c2 = strcmp(studyDate2, studyDate);
            if (c2 == 0)
              {
              const char *studyTime2 = li->StudyTime.GetCharData();
              if (studyTime2 && studyTime)
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
            seriesUID, li->SeriesUID.GetCharData());
          if (c != 0 || seriesUID == 0)
            {
            // Use UID to identify series, but use series number to sort.
            int c2 = li->SeriesNumber - seriesNumber;
            c = (c2 == 0 ? c : c2);
            }
          }
        }
      if (c == 0 && seriesUID != 0)
        {
        li->Files.push_back(fileInfo);
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
      li = sortedFiles.insert(li, SeriesInfo());
      li->PatientName = patientNameValue;
      li->PatientID = patientIDValue;
      li->StudyDate = studyDateValue;
      li->StudyUID = studyUIDValue;
      li->SeriesUID = seriesUIDValue;
      li->SeriesNumber = seriesNumber;
      li->Files.push_back(fileInfo);
      this->FillPatientRecord(&li->PatientRecord, meta);
      this->FillStudyRecord(&li->StudyRecord, meta);
      this->FillSeriesRecord(&li->SeriesRecord, meta);
      }
    }

  // Sort each series by InstanceNumber
  int patientCount = this->GetNumberOfPatients();
  int studyCount = this->GetNumberOfStudies();

  vtkDICOMValue lastStudyUID;
  vtkDICOMValue lastPatientID;

  for (li = sortedFiles.begin(); li != sortedFiles.end(); ++li)
    {
    SeriesInfo &v = *li;
    std::stable_sort(v.Files.begin(), v.Files.end(), CompareInstance);

    // Is this a new patient or a new study?
    if (!lastPatientID.IsValid() || v.PatientID != lastPatientID)
      {
      lastPatientID = v.PatientID;
      patientCount++;
      lastStudyUID = v.StudyUID;
      studyCount++;
      }
    else if (!lastStudyUID.IsValid() || v.StudyUID != lastStudyUID)
      {
      lastStudyUID = v.StudyUID;
      studyCount++;
      }

    vtkSmartPointer<vtkStringArray> sa =
      vtkSmartPointer<vtkStringArray>::New();
    vtkIdType n = static_cast<vtkIdType>(v.Files.size());
    sa->SetNumberOfValues(n);
    for (vtkIdType i = 0; i < n; i++)
      {
      sa->SetValue(i, v.Files[i].FileName);
      }
    this->AddSeriesFileNames(
      patientCount-1, studyCount-1, sa,
      v.PatientRecord, v.StudyRecord, v.SeriesRecord);
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
  unsigned int patientItem = 0;
  unsigned int studyItem = 0;
  unsigned int seriesItem = 0;

  // List of filenames for the current series.
  vtkSmartPointer<vtkStringArray> fileNames =
    vtkSmartPointer<vtkStringArray>::New();

  // Path broken into components.
  std::vector<std::string> path;
  vtksys::SystemTools::SplitPath(dirname, path);
  if (path.size() > 0 && path.back() == "")
    {
    path.pop_back();
    }
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

      if (entryType == "PATIENT")
        {
        patientItem = j;
        }
      else if (entryType == "STUDY")
        {
        studyItem = j;
        }
      else if (entryType == "SERIES")
        {
        seriesItem = j;
        }
      else if (entryType == "IMAGE")
        {
        const vtkDICOMValue& fileID =
          items[j].GetAttributeValue(DC::ReferencedFileID);

        unsigned int m = fileID.GetNumberOfValues();
        for (unsigned int k = 0; k < m; k++)
          {
          path.push_back(fileID.GetString(k));
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
      while (offset == 0 && offsetStack.size() > 0)
        {
        // Go down one directory level.
        offset = offsetStack.back().first;
        entryType = offsetStack.back().second;
        offsetStack.pop_back();

        if (entryType == "PATIENT")
          {
          patientIdx++;
          }
        else if (entryType == "STUDY")
          {
          studyIdx++;
          }
        else if (entryType == "SERIES")
          {
          this->AddSeriesFileNames(
            patientIdx, studyIdx, fileNames,
            items[patientItem], items[studyItem], items[seriesItem]);
          fileNames = vtkSmartPointer<vtkStringArray>::New();
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
  if (path.size() > 0 && path.back() == "")
    {
    path.pop_back();
    }

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

  // Check for abort.
  if (!this->AbortExecute)
    {
    this->UpdateProgress(0.0);
    }
  if (this->AbortExecute)
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
      else
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
  this->Studies->clear();
  this->Patients->clear();
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

  // Check for abort.
  if (!this->AbortExecute)
    {
    this->UpdateProgress(0.0);
    }
  if (this->AbortExecute)
    {
    return;
    }

  if (files->GetNumberOfValues() > 0)
    {
    this->SortFiles(files);
    }
}

//----------------------------------------------------------------------------
void vtkDICOMDirectory::Update(int)
{
  this->AbortExecute = 0;

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
