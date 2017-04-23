## Image Display {#imageDisplay}

@brief Correct display of pixel values.

## Overview

The vtkDICOMReader provides the *stored value* of each pixel in the
image, that is, it provides the value that was stored in the file.
In some circumstances, these stored values can be displayed
directly on the screen (for 8-bit grayscale ultrasound data, for
example) or can be displayed via a user-defined window-level operation
(as is common for MRI).  In the general case, however, the DICOM
standard defines mappings of these stored values to either *real-world
values* that represent real physical quantities, *presentation
values* that are intended for radiographic display, or *color values*
for video, photography, and other special applications.

## Photometric Interpretation

The
[Image Pixel Module](http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.3.html)
of the DICOM standard defines the Photometric Interpretation attribute
as a hint for how the stored pixel values should be interpreted by a
DICOM image display pipeline.  Typical values are:
* MONOCHROME1 - negative image, where higher values are darker (e.g. radiographic film )
* MONOCHROME2 - positive image, where higher values are brighter (e.g. CT, MR)
* PALETTE COLOR - indexed color with palette
* RGB - full-color image with separate RGB components

In addition to the above, the YBR family of photometric interpretations
indicate that the image was stored with one luma channel and two color
channels, which is commonly done when a color image is compressed.
The vtkDICOMReader automatically converts YBR images to RGB, so display
pipelines should interpret YBR the same as RGB.
* YBR_FULL - used by ultrasound, usually with RLE compression
* YBR_FULL_422 - used by JPEG lossy compressed images
* YBR_PARTIAL_420 - used by MPEG lossy compressed video
* YBR_ICT - used by JPEG2000 lossy compressed images
* YBR_RCT - used by JPEG2000 lossless compressed images

Here is a short example of how to interpret the output of
vtkDICOMReader for display:
~~~~~~~~{.cpp}
  reader->Update();
  vtkDICOMMetaData *meta = reader->GetMetaData();
  vtkDICOMValue photometric = meta->Get(DC::PhotometricInterpretation)
  if (photometric.Matches("MONOCHROME1"))
  {
    // display with a lookup table that goes from white to black
  }
  else if (photometric.Matches("MONOCHROME2"))
  {
    // display with a lookup table that goes from black to white,
    // or display with a suitable pseudocolor lookup table
  }
  else if (photometric.Matches("PALETTE*"))
  {
    // display with palette lookup table (see vtkDICOMLookupTable),
    // or convert to RGB with vtkDICOMApplyPalette
  }
  else if (photometric.Matches("RGB*") || photometric.Matches("YBR*"))
  {
    // display RGB data directly
  }
~~~~~~~~

## Grayscale image display

DICOM defines a grayscale display pipeline that converts the
*Stored Values* in the file to *Presentation Values* that are
suitable for display.  The details of how this is done are described
in the
[Lookup Tables and Presentation
States](http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.11.html)
chapter of the DICOM standard.  A brief summary of the steps in the
grayscale display pipeline is as follows:

1. *Stored Values* are rescaled to generate *Modality Values*
2. *Modality Values* are windowed to generate *Windowed Values* (or *Values of Interest*)
3. *Windowed Values* are mapped to *Presentation Values*

The *Modality Values* are real values in units that are appropriate to
the modality, for example, Hounsfield units for CT or counts for PET.
The **RescaleIntercept** and **RescaleSlope** define a linear mapping
from *Stored Values* to *Modality Values*:

    ModalityValue = RescaleSlope * StoredValue + RescaleIntercept

For modalities such as ultrasound and MRI that do not have any units,
the RescaleSlope and RescaleIntercept are absent and the *Modality Values*
are equal to the *Stored Values*.

The *Windowed Values* (or more generically, *Values of Interest* or
*VOIs*) represent the range of values to be displayed.  Decreasing the
**WindowWidth** increases the perceived contrast of the image, and
decreasing the **WindowCenter** increases the perceived brightness of
the image.  Note that, as shown in the pseudocode below, the DICOM
standard uses a definition of "window" and "level" that might be
different from that to which you are accustomed.  The DICOM WindowWidth
must be greater than or equal to 1.

    n = number of output gray levels (usually 256 or 1024)
    w = WindowWidth - 1.0
    c = WindowCenter - 0.5

    if (ModalityValue <= c - 0.5*w), then WindowedValue = 0
    else if (ModalityValue > c + 0.5*w), then WindowedValue = n - 1
    else WindowedValue = ((ModalityValue - c)/w + 0.5) * (n - 1)

For ultrasound (and for 8-bit images in general) the WindowWidth and
WindowCenter may be absent from the file.  If absent, they can be
assumed to be 256 and 128 respectively, which provides an 8-bit identity
mapping.  More information can be found in the
[VOI LUT Module](http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.11.2.html)
of the DICOM standard.  Note that a DICOM display application should
allow the user to adjust the window according to his or her needs.

The *Presentation Values* are the values that are ultimately displayed
to the user.  If the PhotometricInterpretation is MONOCHROME2, then the
*Windowed Values* should be displayed directly.  If the
the PhotometricInterpetation is MONOCHROME1, then the grayscale
lookup table should be inverted such that a value of 0 is displayed as
white and the maximum value is displayed as black.

## Color image display

There are several categories of color display for DICOM, the most important
of which are:
* RGB (or YBR) values stored directly in the file
* PALETTE COLOR where a palette LUT is applied to the stored values
* A supplemental palette LUT applied to some or all stored values
* A pseudo-color palette LUT applied to the windowed values

For convenience, the vtkDICOMApplyPalette filter can convert a PALETTE
COLOR image to RGB, or can convert an image with a supplemental palette
to RGB, but will pass through all other images.  For more information
about supplemental palettes, see the
[Supplemental Palette Lookup Table Module](http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.19.html).
As an alternative to vtkDICOMApplyPalette, the palette lookup table can
be retrieved from a DICOM data set with the vtkDICOMLookupTable class.

The final category of color display, pseudo-color, is displayed as per
the grayscale pipeline described above, except that a pseudocolor LUT
is used in place of the black-to-white (MONOCHROME2) or
white-to-black (MONOCHROME1) LUT.
