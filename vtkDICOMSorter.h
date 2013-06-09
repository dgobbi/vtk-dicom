/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMSorter_h
#define __vtkDICOMSorter_h

#include <vtkObject.h>
#include "vtkDICOMModule.h"

class vtkStringArray;
class vtkIntArray;
class vtkDICOMMetaData;

//! Sort DICOM files and group them by study and series.
/*!
 *  If a list of input files is provided via SetInputFileNames(), then
 *  the files will be grouped by study and series, and each series will
 *  be sorted by InstanceNumber.  If a single input file is provided via
 *  SetInputFileName(), then other files in the same series will be found,
 *  and the series will be sorted by InstanceNumber.
 */
class VTK_DICOM_EXPORT vtkDICOMSorter : public vtkObject
{
public:
  vtkTypeMacro(vtkDICOMSorter,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);
  static vtkDICOMSorter *New();

  //! Set one file from the desired series.
  /*!
   *  When Update() is called, all files that belong to the
   *  same series as the specified file will be identified
   *  and can be retrieved by calling GetOutputFileNames().
   */
  void SetInputFileName(const char *name);
  const char *GetInputFileName() { return this->InputFileName; }

  //! Set a list of file names to group and sort.
  /*!
   *  This method is mutually exclusive with SetInputFileName().
   *  If you call ths method, then InputFileName will be set to NULL
   *  and vice versa.
   */
  void SetInputFileNames(vtkStringArray *input);
  vtkStringArray *GetInputFileNames() { return this->InputFileNames; };

  //! Update the information about the files.
  /*!
   * This method must be called before any of the Get methods.
   */
  virtual void Update();

  //! Get the total number of series that were found.
  int GetNumberOfSeries();

  //! Get the number of studies that were found.
  int GetNumberOfStudies();

  //! Get the first series in a particular study.
  int GetFirstSeriesInStudy(int study);

  //! Get the number of series in a particular study.
  int GetNumberOfSeriesInStudy(int study);

  //! Get the full list of sorted filenames.
  vtkStringArray *GetOutputFileNames() { return this->OutputFileNames; }

  //! Get the file names for a specific series.
  vtkStringArray *GetFileNamesForSeries(int i);

protected:
  vtkDICOMSorter();
  ~vtkDICOMSorter();

  const char *InputFileName;
  vtkStringArray *InputFileNames;
  vtkStringArray *OutputFileNames;

  vtkTimeStamp UpdateTime;

  //! Fill the output filename array.
  virtual void Execute();

  //! Sort the input string array
  virtual void SortFiles(vtkStringArray *input);

  //! Add a sorted series to output.
  /*!
   *  This method is called from SortFiles to provide the files
   *  that make up one series.  The study that the files belong
   *  to must also be provided, as a number that starts at zero
   *  and monotonically increases.
   */
  void AddSeriesFileNames(int study, vtkStringArray *files);

  //! Numerically compare two UIDs.
  static int CompareUIDs(const char *u1, const char *u2);

private:
  vtkDICOMSorter(const vtkDICOMSorter&);  // Not implemented.
  void operator=(const vtkDICOMSorter&);  // Not implemented.

  class StringArrayVector;
  class FileInfo;
  class FileInfoVectorList;

  StringArrayVector *Series;
  vtkIntArray *Studies;

  //! Compare FileInfo entries by instance number
  static bool CompareInstance(const FileInfo &fi1, const FileInfo &fi2);
};

#endif
