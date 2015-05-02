/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2015 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMDirectory_h
#define vtkDICOMDirectory_h

#include <vtkAlgorithm.h>
#include "vtkDICOMModule.h"

class vtkStringArray;
class vtkIntArray;
class vtkDICOMMetaData;
class vtkDICOMItem;

//! Get information about all DICOM files within a directory.
/*!
 *  Given a directory, search for a DICOMDIR file, and if no DICOMDIR is
 *  found, directly search for DICOM files within the directory.  Provide
 *  a list of DICOM file names as output, sorted by patient, study, series,
 *  and image.
 */
class VTK_DICOM_EXPORT vtkDICOMDirectory : public vtkAlgorithm
{
public:
  vtkTypeMacro(vtkDICOMDirectory,vtkAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);
  static vtkDICOMDirectory *New();

  //! Levels within the DICOM information model.
  enum {
    PATIENT, STUDY, SERIES, IMAGE, FRAME
  };

  //! Set the input directory.
  /*!
   *  Set the input directory.  If it has a DICOMDIR file, then that
   *  file will be scanned to get info about the directory.  Otherwise,
   *  the directory will be scanned for DICOM files.  The depth of the
   *  scan (how many subdirectories deep) can be controlled with the
   *  SetScanDepth() method.
   */
  void SetDirectoryName(const char *name);
  const char *GetDirectoryName() { return this->DirectoryName; }

  //! Set a list of filenames (or files and directories) to read.
  /*!
   *  This can be used as alternative to setting a single input directory.
   */
  void SetInputFileNames(vtkStringArray *sa);
  vtkStringArray *GetInputFileNames() { return this->InputFileNames; }

  //! Set a pattern to match for the filenames.
  /*!
   *  For example "*.dcm" will match files ending with ".dcm".  The two
   *  wildcards that are supported are "*" and "?".
   */
  void SetFilePattern(const char *pattern);
  const char *GetFilePattern() { return this->FilePattern; }

  //! Set the scan depth to use when no DICOMDIR is found.
  /*!
   *  The default scan depth is 1, which scans only the given directory
   *  and no subdirectories.  A scan depth of zero means that the directory
   *  will not be scanned unless it contains a DICOMDIR file.
   */
  vtkSetMacro(ScanDepth, int);
  int GetScanDepth() { return this->ScanDepth; }

  //! Specify a find query.
  void SetFindQuery(const vtkDICOMItem& query);

  //! Specify the find level.
  /*!
   *  If this is Series, then the whole series will be found if a single
   *  file in the series matches the query.  Only IMAGE and SERIES are
   *  allowed.  Note that IMAGE is inclusive of any single file, whether
   *  or not the contained data is an image.
   */
  void SetFindLevel(int level);
  void SetFindLevelToImage() { this->SetFindLevel(IMAGE); }
  void SetFindLevelToSeries() { this->SetFindLevel(SERIES); }
  int GetFindLevel() { return this->FindLevel; }

  //! Update the information about the files.
  /*!
   * This method causes the directory to be read.  It must be called before
   * any of the Get methods.
   */
  virtual void Update() { this->Update(0); }
  virtual void Update(int);

  //! Get the total number of series that were found.
  int GetNumberOfSeries();

  //! Get the directory attributes for a series.
  const vtkDICOMItem& GetSeriesRecord(int series);

  //! Get the number of studies that were found.
  int GetNumberOfStudies();

  //! Get the directory attributes for a study.
  const vtkDICOMItem& GetStudyRecord(int study);

  //! Get the patient-related attributes for a specific study.
  /*!
   *  This returns a patient record, the same as GetPatientRecord(),
   *  except that it returns the patient information as recorded
   *  at the time of the study.
   */
  const vtkDICOMItem& GetPatientRecordForStudy(int study);

  //! Get the number of patients that were found.
  int GetNumberOfPatients();

  //! Get the directory attributes for a patient.
  const vtkDICOMItem& GetPatientRecord(int patient);

  //! Get the studies for this patient.
  vtkIntArray *GetStudiesForPatient(int patient);

  //! Get the first series in a particular study.
  int GetFirstSeriesForStudy(int study);

  //! Get the last series in a particular study.
  int GetLastSeriesForStudy(int study);

  //! Get the file names for a specific series.
  vtkStringArray *GetFileNamesForSeries(int i);

  //! Get the file set ID.  This will be NULL unless a DICOMDIR was found.
  const char *GetFileSetID() { return this->FileSetID; }

  //! Get the filename associated with the error code.
  const char *GetInternalFileName() { return this->InternalFileName; }

  //! If this is On, files with no pixel data will be skipped.
  /*!
   *  This is On by default.  Some files, such as dicom directory files,
   *  have metadata but have no images.  Usually we want to skip these.
   */
  vtkSetMacro(RequirePixelData, int);
  vtkBooleanMacro(RequirePixelData, int);
  int GetRequirePixelData() { return this->RequirePixelData; }

  //! If On (the default), symbolic links will not be followed.
  vtkSetMacro(FollowSymlinks, int);
  vtkBooleanMacro(FollowSymlinks, int);
  int GetFollowSymlinks() { return this->FollowSymlinks; }

protected:
  vtkDICOMDirectory();
  ~vtkDICOMDirectory();

  const char *DirectoryName;
  vtkStringArray *InputFileNames;
  const char *FilePattern;
  int RequirePixelData;
  int FollowSymlinks;
  int ScanDepth;

  vtkTimeStamp UpdateTime;
  char *InternalFileName;

  //! Fill the output filename array.
  virtual void Execute();

  //! Fill series info from image metadata.
  virtual void FillSeriesRecord(vtkDICOMItem *item, vtkDICOMMetaData *meta);

  //! Fill study info from image metadata.
  virtual void FillStudyRecord(vtkDICOMItem *item, vtkDICOMMetaData *meta);

  //! Fill patient info from image metadata.
  virtual void FillPatientRecord(vtkDICOMItem *item, vtkDICOMMetaData *meta);

  //! Sort the input string array
  virtual void SortFiles(vtkStringArray *input);

  //! Add a sorted series to output.
  /*!
   *  This method is called from SortFiles to provide the files
   *  that make up one series.  The study that the files belong
   *  to must also be provided, as a number that starts at zero
   *  and monotonically increases.
   */
  void AddSeriesFileNames(
    int patient, int study, vtkStringArray *files,
    const vtkDICOMItem& patientRecord,
    const vtkDICOMItem& studyRecord,
    const vtkDICOMItem& seriesRecord);

  //! Add a series for querying.
  /*!
   *  This method is called for a series for which some of the
   *  meta data is already known, e.g. because it was listed in
   *  a dicomdir file.  If the records match the current query,
   *  then the series file names will be added to "outfiles".
   */
  void AddSeriesForQuery(
    vtkStringArray *outFiles, vtkStringArray *seriesFiles,
    const vtkDICOMItem& patientRecord,
    const vtkDICOMItem& studyRecord,
    const vtkDICOMItem& seriesRecord);

  //! Convert parser errors into sorter errors.
  void RelayError(vtkObject *o, unsigned long e, void *data);

  //! Set the name of the file currently being operated on.
  void SetInternalFileName(const char *fname);

  //! Set the error code.
  void SetErrorCode(unsigned long e) { this->ErrorCode = e; }

  //! Add all of the series listed in a DICOMDIR file.
  /*!
   *  The provided directory should be the directory that contains
   *  the DICOMDIR file, rather than the DICOMDIR file itself.  The
   *  DICOMDIR file should be parsed before this method is called.
   */
  void ProcessDirectoryFile(
    const char *dirname, vtkDICOMMetaData *meta, vtkStringArray *files);

  //! Process a directory, and subdirs to the specified depth.
  void ProcessDirectory(
    const char *dirname, int depth, vtkStringArray *files);

private:
  vtkDICOMDirectory(const vtkDICOMDirectory&);  // Not implemented.
  void operator=(const vtkDICOMDirectory&);  // Not implemented.

  struct SeriesItem;
  struct StudyItem;
  struct PatientItem;
  class SeriesVector;
  class StudyVector;
  class PatientVector;
  struct FileInfo;
  struct SeriesInfo;
  class SeriesInfoList;
  class VisitedVector;

  vtkDICOMItem *Query;
  int FindLevel;
  SeriesVector *Series;
  StudyVector *Studies;
  PatientVector *Patients;
  VisitedVector *Visited;
  char *FileSetID;

  //! Compare FileInfo entries by instance number
  static bool CompareInstance(const FileInfo &fi1, const FileInfo &fi2);
};

#endif
