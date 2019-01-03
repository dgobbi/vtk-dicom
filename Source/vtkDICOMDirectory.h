/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2019 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtkDICOMDirectory_h
#define vtkDICOMDirectory_h

#include "vtkAlgorithm.h"
#include "vtkDICOMModule.h" // For export macro
#include "vtkDICOMCharacterSet.h" // For character sets
#include "vtkVersion.h"

class vtkStringArray;
class vtkIntArray;
class vtkDICOMMetaData;
class vtkDICOMItem;
class vtkDICOMTag;

//! Get information about all DICOM files within a directory.
/*!
 *  Given a directory, search for a DICOMDIR file, and if no DICOMDIR is
 *  found, directly search for DICOM files within the directory.  Provide
 *  a list of DICOM file names as output, sorted by patient, study, series,
 *  and image.
 */
class VTKDICOM_EXPORT vtkDICOMDirectory : public vtkAlgorithm
{
public:
  vtkTypeMacro(vtkDICOMDirectory,vtkAlgorithm);
#ifdef VTK_OVERRIDE
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;
#else
  void PrintSelf(ostream& os, vtkIndent indent);
#endif
  static vtkDICOMDirectory *New();

  //! Levels within the DICOM information model.
  enum {
    PATIENT, STUDY, SERIES, IMAGE, FRAME
  };

  //@{
  //! Set the input directory.
  /*!
   *  If the directory has a DICOMDIR file, then that file will be scanned
   *  to get information about the DICOM files in the directory.  Otherwise,
   *  the directory will be scanned for DICOM files.  The depth of the
   *  scan (how many subdirectories deep) can be controlled with the
   *  SetScanDepth() method.
   */
  void SetDirectoryName(const char *name);
  const char *GetDirectoryName() { return this->DirectoryName; }
  //@}

  //@{
  //! Set a list of filenames (or files and directories) to read.
  /*!
   *  This can be used as alternative to setting a single input directory.
   */
  void SetInputFileNames(vtkStringArray *sa);
  vtkStringArray *GetInputFileNames() { return this->InputFileNames; }

  //! Add more filenames to be read.
  /*!
   *  This allows the directory to be updated.  The new files can belong to
   *  an existing series or a new series.  If any of the new files are
   *  already present in the directory, then nothing will be done for those
   *  files.
   */
  void AddInputFileNames(vtkStringArray *sa);
  //@}

  //@{
  //! Set a pattern to match for the filenames.
  /*!
   *  For example "*.dcm" will match files ending with ".dcm".  The two
   *  wildcards that are supported are "*" and "?".
   */
  void SetFilePattern(const char *pattern);
  const char *GetFilePattern() { return this->FilePattern; }
  //@}

  //@{
  //! Set the scan depth to use when no DICOMDIR is found.
  /*!
   *  The default scan depth is 1, which scans only the given directory
   *  and no subdirectories.  A scan depth of zero means that the directory
   *  will not be scanned unless it contains a DICOMDIR file.
   */
  vtkSetMacro(ScanDepth, int);
  int GetScanDepth() { return this->ScanDepth; }
  //@}

  //@{
  //! Specify a find query.
  void SetFindQuery(const vtkDICOMItem& query);
  //@}

  //@{
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
  //@}

  //@{
  //! Update the information about the files.
  /*!
   * This method causes the directory to be read.  It must be called before
   * any of the Get methods.
   */
#ifdef VTK_OVERRIDE
  void Update() VTK_OVERRIDE { this->Update(0); }
  void Update(int) VTK_OVERRIDE;
#if (VTK_MAJOR_VERSION == 7 && VTK_MINOR_VERSION > 0) || VTK_MAJOR_VERSION > 7
  int Update(vtkInformation *) VTK_OVERRIDE {
    this->Update(); return 1; }
  int Update(int i, vtkInformationVector *) VTK_OVERRIDE {
    this->Update(i); return 1; }
#endif
#else
  void Update() { this->Update(0); }
  void Update(int);
#if (VTK_MAJOR_VERSION == 7 && VTK_MINOR_VERSION > 0) || VTK_MAJOR_VERSION > 7
  int Update(vtkInformation *) {
    this->Update(); return 1; }
  int Update(int i, vtkInformationVector *) {
    this->Update(i); return 1; }
#endif
#endif
  //@}

  //@{
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
  //@}

  //@{
  //! Get the first series in a particular study.
  int GetFirstSeriesForStudy(int study);

  //! Get the last series in a particular study.
  int GetLastSeriesForStudy(int study);

  //! Get the file names for a specific series.
  vtkStringArray *GetFileNamesForSeries(int i);

  //! Get the meta data for a specific series.
  /*!
   *  This provides a subset of the meta data of each file in the series.
   *  To be specific, it contains all the information from the patient,
   *  study, and, at the very minimum, the SOPClassUID, SOPInstanceUID,
   *  and InstanceNumber for each file.
   */
  vtkDICOMMetaData *GetMetaDataForSeries(int i);
  //@}

  //! Set when to query the files, rather than just the DICOMDIR index.
  /*!
   *  If a DICOMDIR file is present, the default behavior is to only
   *  query the other files in the directory if the Query contains
   *  elements that cannot be elucidated from the DICOMDIR file.
   *  For Always, the data returned by GetMetaDataForSeries() will
   *  always be data from the file, not the DICOMDIR (though the
   *  data returned by GetSeriesRecord() etc. will be from DICOMDIR).
   *  For Never, the files will never be scanned if a DICOMDIR is
   *  present, which means that any Query that is applied can only
   *  check attributes that are present in the DICOMDIR.
   */
  void SetQueryFilesToAlways() { this->SetQueryFiles(1); }
  void SetQueryFilesToNever() { this->SetQueryFiles(0); }
  void SetQueryFilesToDefault() { this->SetQueryFiles(-1); }
  vtkSetMacro(QueryFiles, int);
  int GetQueryFiles() { return this->QueryFiles; }

  //@{
  //! Get the file set ID.  This will be NULL unless a DICOMDIR was found.
  const char *GetFileSetID() { return this->FileSetID; }
  //@}

  //@{
  //! Get the filename associated with the error code.
  const char *GetInternalFileName() { return this->InternalFileName; }
  //@}

  //@{
  //! If On, the DICOMDIR file will be ignored.
  /*!
   *  This method can be used to ignore the DICOMDIR file if it is present,
   *  instead of using the DICOMDIR file as an index.
   */
  vtkSetMacro(IgnoreDicomdir, int);
  vtkBooleanMacro(IgnoreDicomdir, int);
  int GetIgnoreDicomdir() { return this->IgnoreDicomdir; }
  //@}

  //@{
  //! If this is On, files with no pixel data will be skipped.
  /*!
   *  This is On by default.  Some files, such as dicom directory files,
   *  have metadata but have no images.  Usually we want to skip these.
   */
  vtkSetMacro(RequirePixelData, int);
  vtkBooleanMacro(RequirePixelData, int);
  int GetRequirePixelData() { return this->RequirePixelData; }
  //@}

  //@{
  //! If On (the default), symbolic links will be followed.
  vtkSetMacro(FollowSymlinks, int);
  vtkBooleanMacro(FollowSymlinks, int);
  int GetFollowSymlinks() { return this->FollowSymlinks; }
  //@}

  //@{
  //! If On (the default), hidden files will be listed.
  /*!
   *  A file is hidden if it has a "hidden" attribute set.  On Linux and
   *  OS X, any file that begins with "." will also be considered "hidden".
   */
  vtkSetMacro(ShowHidden, int);
  vtkBooleanMacro(ShowHidden, int);
  int GetShowHidden() { return this->ShowHidden; }
  //@}

  //@{
  //! Set the character set to use if SpecificCharacterSet is missing.
  /*!
   *  Some DICOM files do not list a SpecificCharacterSet attribute, but
   *  nevertheless use a non-ASCII character encoding.  This method can be
   *  used to specify the character set in absence of SpecificCharacterSet.
   *  If SpecificCharacterSet is present, the default will not override it
   *  unless OverrideCharacterSet is true.
   */
  void SetDefaultCharacterSet(vtkDICOMCharacterSet cs);
  vtkDICOMCharacterSet GetDefaultCharacterSet() {
    return this->DefaultCharacterSet; }

  //! Override the value stored in SpecificCharacterSet.
  /*!
   *  This method can be used if the SpecificCharacterSet attribute of a
   *  file is incorrect.  It overrides the SpecificCharacterSet with the
   *  DefaultCharacterSet.
   */
  vtkSetMacro(OverrideCharacterSet, bool);
  vtkBooleanMacro(OverrideCharacterSet, bool);
  bool GetOverrideCharacterSet() {
    return this->OverrideCharacterSet; }
  //@}

protected:
  vtkDICOMDirectory();
  ~vtkDICOMDirectory();

  const char *DirectoryName;
  vtkStringArray *InputFileNames;
  const char *FilePattern;
  int QueryFiles;
  int IgnoreDicomdir;
  int RequirePixelData;
  int FollowSymlinks;
  int ShowHidden;
  int ScanDepth;
  vtkDICOMCharacterSet DefaultCharacterSet;
  bool OverrideCharacterSet;

  vtkTimeStamp UpdateTime;
  char *InternalFileName;

  //! Fill the output filename array.
  virtual void Execute();

  //! Fill image info from image metadata.
  virtual void FillImageRecord(vtkDICOMItem *item, vtkDICOMMetaData *meta,
                               const vtkDICOMTag *skip, size_t nskip);

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
    const vtkDICOMItem& seriesRecord,
    const vtkDICOMItem *imageRecords[]);

  //! Add files only if they match the query.
  void AddSeriesWithQuery(
    int patient, int study, vtkStringArray *files,
    const vtkDICOMItem& patientRecord,
    const vtkDICOMItem& studyRecord,
    const vtkDICOMItem& seriesRecord,
    const vtkDICOMItem *imageRecords[]);

  //! Returns false if the record doesn't match the query.
  /*!
   *  Matching values are placed into the result parameter.
   */
  bool MatchesQuery(
    const vtkDICOMItem& record, vtkDICOMItem& result);

  //! Perform query on image record, given results from previous levels.
  /*!
   *  This method requires that MatchesQuery() was already called on the
   *  patient, study, and series records.  It has three possible return
   *  values.  If all remaining query attributes were matched by the image
   *  record, then 0 is returned.  If any of the remaining query attributes
   *  mis-matches with the image record, then -1 is returned.  If the query
   *  contains tags that weren't in the patient, study, series, or image
   *  record, then 1 is returned to indicate that the match is inconclusive.
   */
  int MatchesImageQuery(
    const vtkDICOMItem& record, const vtkDICOMItem& result);

  //! Convert parser errors into sorter errors.
  void RelayError(vtkObject *o, unsigned long e, void *data);

  //! Set the name of the file currently being operated on.
  void SetInternalFileName(const char *fname);

  //! Set the error code.
#ifdef VTK_OVERRIDE
  void SetErrorCode(unsigned long e) VTK_OVERRIDE { this->ErrorCode = e; }
#else
  void SetErrorCode(unsigned long e) { this->ErrorCode = e; }
#endif

  //! Add all of the series listed in a DICOMDIR file.
  /*!
   *  The provided directory should be the directory that contains
   *  the DICOMDIR file, rather than the DICOMDIR file itself.  The
   *  DICOMDIR file should be parsed before this method is called.
   */
  void ProcessDirectoryFile(const char *dirname, vtkDICOMMetaData *meta);

  //! Process a directory, and subdirs to the specified depth.
  void ProcessDirectory(
    const char *dirname, int depth, vtkStringArray *files);

  //! Process an OsiriX sqlite database file.
  void ProcessOsirixDatabase(const char *fname);

  //! Copy attributes into a meta data object.
  void CopyRecord(
    vtkDICOMMetaData *meta, const vtkDICOMItem *item, int instance);

private:
#ifdef VTK_DELETE_FUNCTION
  vtkDICOMDirectory(const vtkDICOMDirectory&) VTK_DELETE_FUNCTION;
  void operator=(const vtkDICOMDirectory&) VTK_DELETE_FUNCTION;
#elif __cplusplus >= 201103L
  vtkDICOMDirectory(const vtkDICOMDirectory&) = delete;
  void operator=(const vtkDICOMDirectory&) = delete;
#else
  vtkDICOMDirectory(const vtkDICOMDirectory&);
  void operator=(const vtkDICOMDirectory&);
#endif

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
  bool UsingOsirixDatabase;

  const vtkDICOMItem *CurrentPatientRecord;
  const vtkDICOMItem *CurrentStudyRecord;
  const vtkDICOMItem *CurrentSeriesRecord;
  const vtkDICOMItem *CurrentImageRecord;

  //! Compare FileInfo entries by instance number
  static bool CompareInstance(const FileInfo &fi1, const FileInfo &fi2);
};

#endif
