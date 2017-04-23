## Directories {#directory}

@brief Reading a directory that contains DICOM files.

## DICOM file directory

DICOM files rarely have descriptive names, so it is usually necessary
to identify them by their contents.  A typical DICOM folder listing looks
something like this:

~~~~~~~~{.cpp}
IM-0001-0001.dcm  IM-0001-0005.dcm  IM-0001-0009.dcm  IM-0001-0013.dcm
IM-0001-0002.dcm  IM-0001-0006.dcm  IM-0001-0010.dcm  IM-0001-0014.dcm
IM-0001-0003.dcm  IM-0001-0007.dcm  IM-0001-0011.dcm  IM-0001-0015.dcm
IM-0001-0004.dcm  IM-0001-0008.dcm  IM-0001-0012.dcm  IM-0001-0016.dcm
~~~~~~~~

These files might be 16 slices of a 3D image, or the first three files might
be localizer images while the remaining 13 files are slices of a 3D volume.
Or they might be something else entirely.  So the first thing to do with a
batch of DICOM files is to find out how they fit together.  There are two
classes that can be used for this: the old vtkDICOMFileSorter class, and
the newer vtkDICOMDirectory class.

## Scanning a directory

The vtkDICOMDirectory class solves this problem by scanning the directory
and reporting information on all of the DICOM files that it
finds.  In addition, if the directory contains a **DICOMDIR** file (as is
the case for a DICOM CD), then the DICOMDIR file is used as an index.
In the simplest case, the directory will contain a single series as in the
example below.  Since the example is looking for images (and not for other
DICOM files such as structured reports), the RequirePixelData flag is set:

~~~~~~~~{.cpp}
vtkNew<vtkDICOMDirectory> dicomdir;
dicomdir->SetDirectoryName("E:");
dicomdir->RequirePixelDataOn();
dicomdir->Update();
int n = dicomdir->GetNumberOfSeries();

vtkNew<vtkDICOMReader> reader;
if (n > 0)
{
  // read the first series found
  reader->SetFileNames(dicomdir->GetFileNamesForSeries(0));
  reader->Update();
}
else
{
  std::cerr << "No DICOM images in directory!" << std::endl;
}
~~~~~~~~

Since vtkDICOMDirectory will scan subdirectories recursively, it can be
used to catalogue a large collection of DICOM files:

~~~~~~~~{.cpp}
// Iterate through all of the studies that are present.
int n = dicomdir->GetNumberOfStudies();
for (int i = 0; i < n; i++)
{
  // Get information related to the patient study
  vtkDICOMItem patient = dicomdir->GetPatientRecordForStudy(i);
  vtkDICOMItem study = dicomdir->GetStudyRecord(i);
  std::cout << patient.GetAttributeValue(DC::PatientName) << " ";
  std::cout << patient.GetAttributeValue(DC::PatientID) << " ";
  std::cout << study.GetAttributeValue(DC::StudyDate) << " ";
  std::cout << study.GetAttributeValue(DC::StudyTime) << std::endl;

  // Iterate through all of the series in this study.
  int j1 = dicomdir->GetFirstSeriesForStudy(i);
  int j2 = dicomdir->GetLastSeriesForStudy(i);
  for (int j = j1; j <= j2; j++)
  {
    // get some of the series attributes as a vtkDICOMItem
    vtkDICOMItem series = dicomdir->GetSeriesRecord(j);
    // get all the files in the series
    vtkStringArray *sortedFiles = dicomdir->GetFileNamesForSeries(j);
    std::cout << sortedFiles.GetNumberOfValues() << " files: ";
    std::cout << series.GetAttributeValue(DC::SeriesInstanceUID) << std::endl;
  }
}
~~~~~~~~

The PatientRecord, StudyRecord, and SeriesRecord in the above example
contain attributes for the images that were stored in the DICOMDIR
index file.  At the bare minimum, these will provide the PatientName,
PatientID, StudyDate, StudyTime, StudyInstanceUID, and SeriesInstanceUID.
Usually the StudyDescription, SeriesDescription and SeriesNumber are also
available.  Furthermore, the method GetMetaDataForSeries() returns an
amalgamation of the Patient, Study, Series, and Image information as
a vtkDICOMMetaData object (though the per-image information is sometimes
limited to just the InstanceNumber and the SOPInstanceUID).

### Searching for files that match a query

The vtkDICOMDirectory class has another trick up its sleeve.  It can
search for files that have certain attributes, for example it can
search a filesystem for all scans of a specific patient.  This is
similar in purpose to querying a PACS system, except that you are
instead providing one or more disk directories where the files might
exist.  These directories are searched recursively for all files that
match the query.

~~~~~~~~{.cpp}
// Make a list of the directories to search.
vtkNew<vtkStringArray> dicompath;
dicompath->InsertNextValue("/Volumes/Images1");
dicompath->InsertNextValue("/Volumes/Images2");

// Make a list of attributes to match, using the utf-8 character set.
vtkDICOMItem query;
query.SetAttributeValue(DC::SpecificCharacterSet, "ISO_IR 192");
query.SetAttributeValue(DC::PatientName, "Doe^John");
query.SetAttributeValue(DC::StudyDate, "2012-2015");
query.SetAttributeValue(DC::Modality, "MR");
query.SetAttributeValue(DC::ImageType, "PRIMARY");
query.SetAttributeValue(DC::SeriesDescription, "*T1w*");

vtkNew<vtkDICOMDirectory> dicomdir;
// The SetInputFileNames method takes directories, too!
dicomdir->SetInputFileNames(dicompath.GetPointer());
// Optionally restrict the search to files ending with ".dcm"
dicomdir->SetFilePattern("*.dcm");
dicomdir->SetFindQuery(query);
dicomdir->Update();
~~~~~~~~

All text attributes except for dates accept the wildcards '\*' and '?'.  For
dates, you can use a hyphen to specify a range of dates.  Matching of all
text is done by first converting the text to utf-8 for compability, and for
patient names the matching is case insensitive.  The query **PRIMARY**
will match the multi-valued attribute value
**ORIGINAL\\PRIMARY**, since only one value has to match.

If the query contains any non-ASCII text, you must set the
SpecificCharacterSet attribute to whichever character set your program
uses internally.  This does not have to be the same as the character set
used in the files you are searching for.  It is recommended to use utf-8
as the character set for the query, regardless of the character set used
in the DICOM files.

## Sorting a list of files

The vtkDICOMFileSorter class is obsolete, since its capabilities are
eclipsed by the vtkDICOMDirectory class, but its use is documented here
for historical reasons.  It is also worth stating that the "sorting"
provided by this class is, in fact, unnecessary: the vtkDICOMReader
itself is capable of sorting its input files into the correct order.

~~~~~~~~{.cpp}
  // Instantiate a DICOM sorter.
  vtkNew<vtkDICOMFileSorter> sorter;

  // Provide an array containing a list of filenames.
  sorter->SetInputFileNames(filenames);

  // Update the sorter (i.e. perform the sort).
  sorter->Update();

  // Get the first series.
  int i = sorter->GetNumberOfSeries();
  if (i > 0)
  {
    vtkStringArray *sortedFiles = sorter->GetFileNamesForSeries(0);
    // do something with the files
  }
~~~~~~~~

In addition, the sorter can discover which series belong to the same
study.  That is, it can tell us which series were collected during the
same imaging session.  One thing the sorter does *not* do is sort
the images in the series according to slice location.  It only sorts the
images according to the Instance Number embedded in each image, where the
Instance Number gives the logical viewing order prescribed by the medical
device that generated the images.  It is up to the vtkDICOMReader to
check the slice positions for the files and sort them by location before
generating an image volume or time series.

~~~~~~~~{.cpp}
  // Sort the input filenames by series and study.
  sorter->SetInputFileNames(filenames);
  sorter->Update();

  // Iterate through all of the studies that are present.
  int n = sorter->GetNumberOfStudies();
  for (int i = 0; i < n; i++)
  {
    // Iterate through all of the series in this study.
    int j1 = sorter->GetFirstSeriesForStudy(i);
    int j2 = sorter->GetLastSeriesForStudy(i);
    for (int j = j1; j <= j2; j++)
    {
      vtkStringArray *sortedFiles = sorter->GetFileNamesForSeries(j);
      // do something with the files
    }
  }
~~~~~~~~
