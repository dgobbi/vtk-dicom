## Attributes {#attributes}

@brief Managing DICOM meta data.

## Overview

The meta data can be loaded from a DICOM file in two ways: either via
the vtkDICOMReader class (which also reads the image data), or via the
vtkDICOMParser class (which reads only the meta data).  These classes
store the meta data in a vtkDICOMMetaData object, which provides storage
for all of the files in the DICOM series. The GetAttributeValue() method
for this class accepts a file index as a parameter, to allow one to
choose the file in the series for which to get the attribute.

~~~~~~~~{.cpp}
  // Get meta data from a vtkDICOMReader
  reader->UpdateInformation();
  vtkDICOMMetaData *meta = reader->GetMetaData();

  // Get the number of files for which "meta" holds meta-data
  int n = meta->GetNumberOfInstances();

  // Get EchoTime attribute for first file in series.
  if (meta->HasAttribute(DC::EchoTime))
  {
    int fileIndex = 0;
    double t = meta->GetAttributeValue(fileIndex, DC::EchoTime).AsDouble();
  }

  // If fileIndex is not given, attribute is retrieved from first file.
  std::string str = meta->GetAttributeValue(DC::SeriesDescription).AsString();
~~~~~~~~

Attributes are returned as a vtkDICOMValue object, which has methods
such as AsDouble(), AsInt() or AsString() that allow conversion of the
value to various C++ types.  If the DICOM file does not have the
requested attribute, then the returned value will be empty and
"value.IsValid()" will return "false".  Calling AsString() on an invalid
value will return the empty string, and likewise calling AsInt() or
AsDouble() on an invalid value will return 0.

## Per-slice meta data

As discussed in the Overview, a "file index" can be used when retrieving
an attribute from vtkDICOMMetaData.  It is important to note that this
is a file index and not a slice index.  The slices are sorted by spatial
location, which might be different from the file order.  Furthermore, a
single DICOM file might actually contain multiple slices, with each
slice stored in a different frame within the file.

The reader provides an array, the FileIndexArray, that can be used to
convert a "slice index" to a file index.  It also provides a
FrameIndexArray that can be used to convert a slice index to a frame
number.  Together, these can be used regardless of whether the there was
one slice per file, or one slice per frame in a multi-frame file: the
vtkDICOMMetaData object provides a GetAttributeValue() method that takes
both a file index and a frame index, along with the tag of the attribute
to be inspected.

~~~~~~~~{.cpp}
  // Read the files and get the meta data.
  reader->SetFileNames(fileNameArray);
  reader->Update();
  vtkDICOMMetaData *meta = reader->GetMetaData();

  // Get the arrays that map slice to file and frame.
  vtkIntArray *fileMap = reader->GetFileIndexArray();
  vtkIntArray *frameMap = reader->GetFrameIndexArray();

  // Get the file and frame for a particular slice.
  int sliceIndex = 6;
  int fileIndex = fileMap->GetComponent(sliceIndex, 0);
  int frameIndex = frameMap->GetComponent(sliceIndex, 0);

  // Get the position for that slice.
  vtkDICOMValue pv = meta->GetAttributeValue(fileIdx, frameIdx,
    DC::ImagePositionPatient);
  double position[3] = { 0.0, 0.0, 0.0 };
  if (pv.IsValid() && pv.GetNumberOfValues() == 3)
  {
    pv.GetValues(position, 3);
  }
~~~~~~~~

As a caveat, for multi-frame files, the example given above assumes
that the meta data contains a per-frame ImagePositionPatient attribute.
This is the case for enhanced multi-frame CT and MRI files, but not
for multi-frame nuclear medicine files.  Whenever retrieving meta data
from a DICOM image, it is wise to consult the DICOM standard to see
how the attributes are defined for the various modality-specific IODs
(information object descriptions).

## Per-component meta data

In the example in the previous section, the fileMap->GetComponent()
method was called with two arguments, but the second argument was set
to zero.
If the vtkDICOMReader assigned a vector dimension to the data, then
the the vtkImageData will have multiple scalar values in each voxel.
For instance, the first component in each voxel may have come from a
file that provided the real component of a complex-valued image, while
the second component from a file that provided the imaginary
component.  In this case, one would do the following to retrieve the
meta data from the "imaginary" file:

~~~~~~~~{.cpp}
  // Read the files and get the meta data.
  reader->SetFileNames(fileNameArray);
  reader->Update();
  vtkDICOMMetaData *metaData = reader->GetMetaData();

  // Get the arrays that map slice to file and frame.
  vtkIntArray *fileMap = reader->GetFileIndexArray();
  vtkIntArray *frameMap = reader->GetFrameIndexArray();

  // Get the file and frame for a particular slice and component.
  int sliceIndex = 6;
  int vectorIndex = 1; // 2nd component is the imaginary component
  int fileIndex = fileMap->GetComponent(sliceIndex, vectorIndex);
  int frameIndex = frameMap->GetComponent(sliceIndex, vectorIndex);

  // Get an attribute from the meta data.
  vtkDICOMValue v = metaData->GetAttributeValue(fileIdx, frameIdx, tag);
~~~~~~~~

If the data has a time dimension and the reader's TimeAsVectorOn() method
was called, then the components of each voxel can correspond both to a
specific time slot, and to a specific vector component.  To make the
situation even more complicated, each pixel in the DICOM files might
be an RGB pixel and therefore have three components as given
by the SamplesPerPixel attribute in the meta data.

The number of components in the FileIndexArray and FrameIndexArray is
equal to the vector dimension, and if TimeAsVectorOn() was called, then
the vector dimension will include the time dimension.  The FileIndexArray
and FrameIndexArray do not have components that correspond to the individual
R,G,B components in RGB images, since the R, G, and B components will always
have the same meta data because they always come from the same file and
frame.

The following strategy is recommended for accessing per-component meta
data in multi-dimensional images:

~~~~~~~~{.cpp}
  // Get the arrays that map slice to file and frame.
  vtkIntArray *fileMap = reader->GetFileIndexArray();
  vtkIntArray *frameMap = reader->GetFrameIndexArray();

  // Get the image data and meta data.
  vtkImageData *image = reader->GetOutput();
  vtkDICOMMetaData *meta = reader->GetMetaData();

  // Get the number of components in the data.
  int numComponents = image->GetNumberOfScalarComponents();

  // Get the full vector dimension for the DICOM data.
  int vectorDimension = fileMap->GetNumberOfComponents();

  // Compute the samples per pixel in original files.
  int samplesPerPixel = numComponents/vectorDimension;


  // Check for time dimension
  int timeDimension = reader->GetTimeDimension();
  if (timeDimension == 0)
  {
    timeDimension = 1;
  }

  // Get all attributes for a specific time.
  int vectorIndex = timeIndex*vectorDimension/timeDimension;
  int vectorEndIndex = (timeIndex + 1)*vectorDimension/timeDimension;

  for (int i = vectorIndex; i < vectorEndIndex; i++)
  {
    int fileIndex = fileMap->GetComponent(sliceIndex, i);
    int frameIndex = frameMap->GetComponent(sliceIndex, i);
    vtkDICOMValue v = meta->GetAttributeValue(fileIdx, frameIdx, tag);
    // print or display the value
  }

  // Extract an image at the desired time slot (e.g. for display).
  int componentIndex = timeIndex*vectorDimension/timeDimension*samplesPerPixel;
  vtkNew<vtkImageExtractComponents> extractor;
  extractor->SetInputConnection(reader->GetOutputPort());
  if (samplesPerPixel == 1)
  {
    extractor->SetComponents(componentIndex);
  }
  else if (samplesPerPixel == 2) // rare/nonexistent in DICOM images
  {
    extractor->SetComponents(componentIndex, componentIndex + 1);
  }
  else
  {
    extractor->SetComponents(componentIndex, componentIndex + 1, componentIndex + 2);
  }
  extractor->Update();
~~~~~~~~
## Nested data, tag paths, and multi-frame files

DICOM meta data can be nested.  For example, nesting is used to store
per-frame meta data for enhanced multi-frame DICOM files.  In order to
make it easy to access nested attributes, the vtkDICOMTagPath
class describes the full path to a nested attribute.

~~~~~~~~{.cpp}
  // Get an attribute for frame 3 of a multi-frame file.
  int frameIdx = 3;
  double echoTime = meta->GetAttributeValue(
    vtkDICOMTagPath(DC::PerFrameFunctionalGroupSequence, frameIdx,
                    DC::CardiacSynchronizationSequence, 0,
                    DC::NominalCardiacTriggerDelayTime)).AsDouble();
~~~~~~~~

This is rather verbose, so a more convenient method for accessing per-frame
data is provided for enhanced multi-frame files.  You can give the frame
index after the file index, in which case the GetAttributeValue() method
will perform a search for the attribute without requiring a full path.

~~~~~~~~{.cpp}
  // Get an attribute for frame 3 of an enhanced multi-frame file.
  int fileIdx = 0;
  int frameIdx = 3;
  vtkDICOMValue vw = meta->GetAttributeValue(fileIdx, frameIdx, DC::WindowWidth);
  vtkDICOMValue vc = meta->GetAttributeValue(fileIdx, frameIdx, DC::WindowCenter);
  if (vw.IsValid() && vc.IsValid())
  {
    // set the window for the image
  }
~~~~~~~~

The vtkDICOMMetaDataAdapter class can also be used to access enhanced
multi-frame files as if each frame was a separate file.

## Iterating over data elements

The vtkDICOMMetaData object also provides iterator-style access to the
data elements.  This is useful, for instance, when you want to iterate
through all of the elements in the meta data in sequential order.  It is
also useful if you want to check which attributes vary between files in
the series.

~~~~~~~~{.cpp}
  // Iterate through all data elements in the meta data.
  for (vtkDICOMDataElementIterator iter = meta->Begin(); iter != meta->End(); ++iter)
  {
    vtkDICOMTag tag = iter->GetTag();
    std::cout << "tag: " << tag << std::endl;
    // Crucial step: check for values that vary across the series.
    if (iter->IsPerInstance())
    {
      int n = iter->GetNumberOfInstances();
      for (int i = 0; i < n; i++)
      {
        std::cout << "instance " << i << ": " << iter->GetValue(i) << std::endl;
      }
    }
    else
    {
      // Not PerInstance: value is the same for all files in series.
      std::cout << "all instances: " << iter->GetValue() << std::endl;
    }
  }

  // Get the iterator to a specific element (hash table lookup).
  vtkDICOMDataElementIterator iter = meta->Find(DC::ImageOrientationPatient);
  if (iter != meta->End())
  {
    // do something
  }
~~~~~~~~

You might be surprised by the PerInstance check, but it is necessary due
to the fact that vtkDICOMMetaData holds the meta data for an entire series
of DICOM files.  Most attributes are the same across the series, but a
few attributes vary from one file to the next.  These per-file attributes
are identified when the file is read by vtkDICOMReader.

## Dictionaries

When iterating through the data elements in the meta data, as described
in the previous section, it can be useful to get information about
the meaning of the data elements that are encountered.  Complete information
can only be provided by the DICOM standards documents themselves, but the
vtkDICOMDictionary can at least provide a summary of what kind of data to
expect for a given attribute.

~~~~~~~~{.cpp}
  // do a dictionary lookup on a tag
  vtkDICOMDictEntry entry;
  entry = vtkDICOMDictionary::FindDictEntry(vtkDICOMTag(0x0008,0x0020));
  // check if entry was found in dictionary
  if (entry.IsValid())
  {
    std::cout << entry.GetName() << std::endl; // prints "StudyDate"
    std::cout << entry.GetVR() << std::endl; // prints "DA"
    std::cout << entry.GetVM() << std::endl; // prints "1"
  }

  // do a dictionary lookup by name
  entry = vtkDICOMDictionary::FindDictEntry("StudyDate");
  if (entry.IsValid())
  {
    std::cout << entry.GetTag() << std::endl; // prints "0008,0020"
  }
~~~~~~~~

The vtkDICOMDictionary class provides information for attributes that are
described in the DICOM standard, as well as information for private
attributes defined by medical device manufacturers.
Every DICOM file is likely to have a mix of standard attributes and private
attributes.  Fortunately, it is easy to tell the difference between the
two: private attributes always use a tag with with an odd group number,
while the DICOM standard only uses even group numbers.  The lookup of
private tags requires the name of the private dictionary.

~~~~~~~~{.cpp}
  // do a private dictionary lookup in GE dictionary GEMS_ACQU_01
  vtkDICOMDictEntry entry;
  entry = vtkDICOMDictionary::FindDictEntry("CellSpacing", "GEMS_ACQU_01");
  if (entry.IsValid())
  {
    std::cout << entry.GetTag() << std::endl; // prints "0019,0004"
    std::cout << entry.GetName() << std::endl; // prints "CellSpacing"
    std::cout << entry.GetVR() << std::endl; // prints "DS"
    std::cout << entry.GetVM() << std::endl; // prints "1"
  }
~~~~~~~~

## Private meta data

Because private tags are not registered with any central authority, there
is no guarantee that they are unique.  Instead, each private group within
a DICOM file contains 240 blocks (each with 256 elements) that can be
be individually reserved for elements belonging to a specific private
dictionary.  The details of how this is done are described in Part 5,
Section 7.8 of the DICOM standard.

The result of this is that private tags are of the form (gggg,xxee)
where "xx" is a hexadecimal value between `10` and `ff`
that identifies the block that was used to store the attribute.  The
tricky thing is that this value can vary from one DICOM file to the next,
though it is usually consistent within a single series.
Some people are surprised by this, because the first block (i.e. `10`)
is the only block that is used in most files.

To ensure that you are looking for private attributes in the correct
location (i.e. within the correct block), you must resolve each
private tag before using it.

~~~~~~~~{.cpp}
  // start with the tag in its "dictionary" form, with xx=00
  vtkDICOMTag ptag = vtkDICOMTag(0019,0004);
  // resolve the private tag (find out what block was reserved)
  ptag = meta->ResolvePrivateTag(ptag, "GEMS_ACQU_01");
  if (ptag == vtkDICOMTag(0xffff,0xffff))
  {
    // the special tag value ffff,ffff indicates that the tag could not be
    // resolved: no private block was reserved for dictionary GEMS_ACQU_01
  }
  else
  {
    // ptag will now be 0019,xx04 where "xx" is usually 10 (first block)
    double spacing = meta->GetAttributeValue(ptag).AsDouble();
  }
~~~~~~~~

