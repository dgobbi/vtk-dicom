## Image Reader {#imageReader}

@brief Nitty-gritty details for loading DICOM images.

## Overview

The vtkDICOMReader converts a series of images (usually collated by
vtkDICOMDirectory) into three outputs:
1. a vtkImageData object to hold the pixel data for the volume
2. a vtkMatrix4x4 to hold the position and orientation of the volume
3. a vtkDICOMMetaData object to hold the meta-data

Each slice of the output image data is generated from one of the input
files (or, in the case of multi-frame images, from one frame).  The
slices are sorted into the correct order by the reader, so it is not
necessary to sort the files beforehand.  The reader also computes a 4x4
matrix, the "PatientMatrix", that can be used to convert from image data
coordinates (measured in millimeters from the center of the first
voxel), to DICOM patient coordinates (as described in the
[DICOM Image Plane Module](http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.2.html)).

In order to achieve this, the reader checks the Image Position and Image
Orientation that are recorded in the meta data for each slice.  Then, if
and only if the slices have the same orientation and the slice positions
fit a line, the reader sorts the slices according to location.  The
vtkImageData *z* spacing is then set to the average center-to-center
distance between adjacent slices.

In the absence of Image Position information in the meta data, or if the
slices do not form a rectilinear or parallelepiped volume, then the
slices are sorted only according to the Instance Number in the meta
data.  There is also a reader method called SortingOff() than can be
called to disable sorting entirely, so that the order of the slices in
the vtkImageData will reflect the order of the list of files provided to
the reader.

## Row order

DICOM images are rasterized from top to bottom, meaning that the first
pixel in the file is meant to be displayed at the top left corner of the
viewport.  The convention for the VTK image reader classes, however, is
to store the pixels in memory such that the first pixel is at the bottom
left corner.  To support his convention, the default behavior of the
vtkDICOMReader is to flip the images while reading them so that last
image row in the file becomes the first row of the vtkImageData.  In
this way, if the image is displayed by the vtkImageViewer, it will be
displayed the right way up.

However, flipping the image has consequences.  When the reader flips the
image image, it likewise flips the PatientMatrix with respect to the
ImageOrientationPatient stored in the file.  Also, since a flip along
one axis requires a flip along another axis in order for the coordinate
system to obey the right-hand-rule, the reversal of the ordering of the
rows is accompanied by a reversal of the ordering of the slices.  This
is done because the alternative, introducing a PatientMatrix with a
negative determinant, will cause difficulties with 3D processing and
display of the images.

Hence, unless the intent is to use vtkDICOMReader in a simple 2D display
pipeline with vtkImageViewer, it is recommended to call the
SetMemoryRowOrderToFileNative() method when reading the images.  This
will keep the keep the image in its original top-to-bottom ordering.

~~~~~~~~{.cpp}
  vtkNew<vtkDICOMReader> reader;
  reader->SetFileNames(fileNameArray);
  reader->SetMemoryRowOrderToFileNative();
  reader->Update();

  // get the matrix to use when displaying the data
  // (this matrix provides position and orientation)
  vtkMatrix4x4 *matrix = reader->GetPatientMatrix();
~~~~~~~~

## CT gantry tilt

Certain CT scan protocols present a challenge for 3D image analysists
because the slice orientation is tilted with respect to the scan
direction, resulting in an acquisition volume that is a parallelepiped.
This occurs because of the geometry of the CT scanner itself:
traditionally, CT scanners were designed to acquire one slice at a
time with the bed moving a few millimeters between slices.  The CT gantry,
and hence the slices, could be tilted to better align with anatomy,
but tilting the bed of the scanner to match was undesirable for obvious
reasons.  Hence the direction in which the bed moved was not at a right
angle to the slices.

Volume rendering techniques and many 3D filtering techniques assume
a uniform, orthonormal sampling of the data.  It is therefore necessary
to "un-tilt" or rectify these gantry-tilted CT images.  This can be done
with the vtkDICOMCTRectifier class, which rectifies tilted CT volumes
and acts as a simple pass-through for volumes that are already rectilinear.
The rectification is achieved through a simple in-plane translation and
sinc interpolation of the slices.  The resulting slices have the same
orientation as the original slices.

~~~~~~~~{.cpp}
  vtkNew<vtkDICOMCTRectifier> rectify;
  rectify->SetVolumeMatrix(reader->GetPatientMatrix());
  rectify->SetInputConnection(reader->GetOutputPort());
  rectify->Update();

  // get the new PatientMatrix for the rectified volume
  vtkMatrix4x4 *matrix = rectify->GetRectifiedMatrix();
~~~~~~~~

## CT and PET rescaled values

Another challenge with CT images is that the pixel intensity scaling,
as recorded in the RescaleSlope and RescaleIntercept attributes of
the file, can vary from slice to slice.  This is done to make the best
use of the limited dynamic range of the analog-to-digital converter in
the scanner.  By default, the vtkDICOMReader will automatically detect
the changes in RescaleSlope and RescaleIntercept, and will then adjust
the slices so that they are all the same.  This is controlled with the
AutoRescaleOn()/Off() method of the reader.

In general, this automatic adjustment is safe for CT images, because
usually it is only RescaleIntercept that varies, and it usually varies
by a whole number.  There is no loss of fidelity when the integer pixel
value is adjusted by a whole number, as long as it remains within the
range that can be represented by the datatype.  For PET images, however,
the RescaleSlope also varies and it is necessary to use floating-point
values.

If accurate pixel values are required (which is the case in most medical
applications), it is recommended that AutoRescaleOff() is used.  The
rescaling of the pixel values to "real" values should be done with the
vtkDICOMApplyRescale filter, which will produce pixel values as "double"
(or, optionally, as "float") after applying the RescaleSlope and the
RescaleIntercept for each slice.

~~~~~~~~{.cpp}
  vtkNew<vtkDICOMCTReader> reader;
  reader->SetFileNames(fileNameArray);
  reader->SetMemoryRowOrderToFileNative();
  reader->AutoRescaleOff();

  vtkNew<vtkDICOMApplyRescale> rescale;
  rescale->SetInputConnection(reader->GetOutputPort());
  rescale->SetOutputScalarTypeToFloat();
  rescale->Update();
~~~~~~~~

The vtkDICOMReader provides the rescaling information, along with all the
other meta data, via the VTK data pipeline (i.e. via GetOutputPort()).
If you use this filter together with vtkDICOMCTRectifier in the same
pipeline, it is recommened that this filter comes before the rectifier.

## Multi-dimensional images

In addition to sorting slices by location, the reader attempts to detect
multi-dimensional data sets.  It recognizes up to 5 dimensions: *x*, *y*,
*z*, *t*, and a vector dimension.  This is best illustrated by example.
If an MR raw-data DICOM series provides real and imaginary pixel data
at each slice location, then the vtkImageData produced by the reader
will have two components (real and imaginary).  We interpret this
as an image with a vector dimension of 2.

When a time dimension is present, things become interesting.  The default
behavior of the reader is to store adjacent time points in adjacent
vtkImageData slices.  This works well when the images are to be displayed
slice-by-slice.  It is, however, inappropriate if the vtkImageData is to
be displayed as a multi-planar reformat or as a volume.  For this reason,
the vtkDICOMReader has a method called
TimeAsVectorOn() that will cause the reader to treat each voxel as a
time vector.  In other words, if the DICOM data has 10 individual time
slots, then the vtkImageData will have 10 components per voxel (or 30
components in the case of RGB data).  By selecting a specific component
or range of components when displaying the data, one can display a
specific point in time.

Five dimensions come into play when the DICOM series has frames that
are at the same location and within the same time slot.  Going back to
the (real,imaginary) example, if such a series of images is read after
TimeAsVectorOn() is called, then the vtkImageData will have 20 components
per voxel if there are 10 time slots.  The 20 components can be thought of
as 10 component blocks with 2 components per block.  A filter like
vtkImageExtractComponents can be used to extract a block of components
that corresponds to a particular time slot.

If the behavior described in the preceding paragraphs is not desirable,
then one can use the SetDesiredTimeIndex(int) method to read just one
time slot, and use a set of *N* readers to read the *N* time
slots as *N* separate VTK data sets.

~~~~~~~~{.cpp}
  vtkNew<vtkDICOMReader> reader;
  reader->SetFileNames(filenames);

  // read just the meta data, to get the time dimension
  reader->UpdateInformation();

  int numberOfTimeSlots = reader->GetTimeDimension();
  if (numberOfTimeSlots > 1)
  {
    // example: read only the final time slot
    reader->SetDesiredTimeIndex(numberOfTimeSlots-1);
  }

  // update the reader
  reader->Update();
~~~~~~~~

## Enhanced multi-frame and multi-stack files

The DICOM standard allows for multiple slices (frames) per file, or even
multiple stacks of slices per file.  In the case of multi-frame files,
each frame is assigned a position and a time slot and the frames are sorted
according to the slice sorting method described in the previous section.

In multi-stack files there are, as one might expect, more than one
rectilinear (or perhaps non-rectilinear) volume.  If sorting has been
turned off with the SortingOff() method, then all the frames in the file
are read sequentially into vtkImageData slices.  If sorting is on, however,
then the reader is only able to read one stack at a time.  The method
SetDesiredStackID() allows one of the stacks to be chosen by name.

~~~~~~~~{.cpp}
// for this example, 'filename' is multi-frame, multi-stack file
vtkNew<vtkDICOMReader> reader;
reader->SetFileName(filename);

// read the meta data, get a list of stacks
reader->UpdateInformation();
vtkStringArray *stackNames = reader->GetStackIDs();

// specify a stack, here we assume we know the name:
reader->SetDesiredStackID("1");
~~~~~~~~

## Stacks in legacy files

Even though the DICOM standard only describes the use of stacks in
reference to enhanced multi-frame files, the concept is also useful
when working with "legacy" files that only have one slice per file
(such legacy files are, in fact, still the norm while the enhanced
files described in the previous section are relatively uncommon).

The reader defines a stack as a set of slices that have the same
orientation, and whose corners are placed along straight lines in
space.  This allows for rectilinear and parallelepiped volumes,
with the latter being necessary for the tilted-gantry CT scans
discussed previously.  If multiple stacks are required to capture
all of the slices in series, the reader will automatically sort the
slices into stacks and reader->GetStackIDs() will return an array
with multiple values.  In this case, the reader will name the stacks
"0", "1", "2", etcetera.

Generally, such multi-stack series only occur for locators or for
scout series.  For example, a MR scout series will often have a few
images for each orientation, and will therefore result in three
stacks.  A CT locator will be identified as a single-slice stack
that occurs before the main stack.

## Using DICOM with MINC or NIfTI

For DICOM images of the head, chest, or abdomen the *x* coordinate
increases from right to left, the *y* coordinate increases from anterior
to posterior, and the *z* coordinate increases from inferior to
superior.  This is often referred to as the LPS coordinate system, and
refers to the coordinates that are achieved after the image is been
transformed via the PatientMatrix.  The NIfTI and MINC file formats use
a coordinate system where *x* increases to the right and *y* increases
to the front (anterior).  Hence, the coordinate system is rotated by 180
degrees as compared to DICOM.

The vtkDICOMToRAS filter can adjust a DICOM image so that it shares the
same coordinate system as MINC and NIfTI.  It can also be used to do
the reverse, and convert a NIfTI or MINC image to DICOM coordinates.

~~~~~~~~{.cpp}
  vtkNew<vtkDICOMToRAS> converter;
  converter->SetInputConnection(reader->GetOutputPort());
  converter->SetPatientMatrix(reader->GetPatientMatrix());
  converter->SetAllowRowReordering(true);
  converter->SetAllowColumnReordering(false);

  converter->UpdateMatrix();
  vtkMatrix4x4 *matrix = converter->GetRASMatrix();
  converter->Update();
  vtkImageData *image = converter->GetOutput();
~~~~~~~~
