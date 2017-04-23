## Image Writer {#imageWriter}

@brief Details on how to write DICOM images.

## Overview

The vtkDICOMWriter takes a vtkImageData object as input, and writes a
series of DICOM image files to disk.  Since the required meta data for
an image varies from one modality to another, the writer delegates the
creation of the meta data to another class called vtkDICOMGenerator.
A short example of how this is done is as follows:

~~~~~~~~{.cpp}
  // Create a generator for MR images.
  vtkNew<vtkDICOMMRGenerator> generator;

  // Create a meta data object with some desired attributes.
  vtkNew<vtkDICOMMetaData> meta;
  meta->SetAttributeValue(DC::PatientName, "Doe^John");
  meta->SetAttributeValue(DC::ScanningSequence, "GR"); // Gradient Recalled
  meta->SetAttributeValue(DC::SequenceVatiant, "SP"); // Spoiled
  meta->SetAttributeValue(DC::ScanOptions, "");
  meta->SetAttributeValue(DC::MRAcquisitionType, "2D");

  // Plug the generator and meta data into the writer.
  vtkNew<vtkDICOMWriter> writer;
  writer->SetInputConnection(lastFilter->GetOutputPort());
  writer->SetMetaData(meta.GetPointer());
  writer->SetGenerator(generator.GetPointer());

  // Set the output filename format as a printf-style string.
  writer->SetFilePattern("%s/IM-0001-%04.4d.dcm");

  // Set the directory to write the files into.
  writer->SetFilePrefix("/the/output/directory");

  // Write the file.
  writer->Write();
~~~~~~~~

The vtkDICOMMRGenerator assists with conformance by generating all
the data set attributes that are required by the MR IOD.  It will also
scan through the vtkMetaData object that is provided to the writer,
and use any of its attributes as long as 1) they are defined in the MR IOD,
and 2) they are deemed to be valid for the image that is being written.
A partial list of attributes that are never taken from the input meta data
is as follows:
1. `SOPInstanceUID` (this is always re-generated to ensure its uniqueness)
2. `SeriesInstanceUID` (ditto)
3. `ImageType` (this is set to `DERIVED\SECONDARY\OTHER` by default)
4. `PixelSpacing` (this is set from the VTK image information)
5. `Rows` and `Columns` (ditto)
6. `ImagePositionPatient` and `ImageOrientationPatient` (these are set from the PatientMatrix)

The generator always creates a new `SOPInstanceUID` for each file and a
new `SeriesInstanceUID` for each series. There is no way to set these
UIDs manually.  The `ImageType` is set to `DERIVED` by default,
because an image cannot be considered to be `ORIGINAL` if it was modifed
in any way after its original acquisition.  Finally, all information
related to the pixel values or the slice geometry is generated from
the vtkImageData information and from the PatientMatrix.

The vtkDICOMWriter allows several parameters, including `ImageType`,
to be set when writing the file.  These are demonstrated in the following
example.

~~~~~~~~{.cpp}
  // Plug the generator and meta data into the writer.
  vtkNew<vtkDICOMWriter> writer;
  writer->SetInputConnection(lastFilter->GetOutputPort());
  writer->SetMetaData(meta.GetPointer());
  writer->SetGenerator(generator.GetPointer());

  // Set the output filename format as a printf-style string.
  writer->SetFilePattern("%s/IM-0001-%04.4d.dcm");
  // Set the directory to write the files into
  writer->SetFilePrefix("/the/output/directory");

  // Set the image type to Multi-planar Reformat.
  // (forward slashes will be converted to backward slashes)
  writer->SetImageType("DERIVED/SECONDARY/MPR");
  writer->SetSeriesDescription("Sagittal Multi-planar Reformat");

  // Set the 4x4 matrix that gives the position and orientation.
  writer->SetPatientMatrix(patientMatrix);
~~~~~~~~

## Customizing the generators

At the present time, the vtkDICOMWriter has only three generators
available: the vtkDICOMMRGenerator (for MR), the vtkDICOMCTGenerator (for CT),
and the vtkDICOMSCGenerator (for Secondary Capture, e.g. screenshots).
Writing a new generator class is the recommended method for adding support
for a new modality to the vtkDICOM library, though that is beyond the scope
of this document.

## Writing a raw pixel buffer to a DICOM file

In addition to the vtkDICOMWriter, there is a class called the
vtkDICOMCompiler that can write meta data and image data directly
to a file without it being processed by a vtkDICOMGenerator.  It
can be used to efficiently perform such actions as changing the
transfer syntax of the data or tweaking the meta data.  By design,
the vtkDICOMCompiler will take, as input, a meta data object that
describes a series of images, and it will then write the files in
the series one-by-one.

~~~~~~~~{.cpp}
  vtkNew<vtkDICOMCompiler> compiler;
  compiler->SetMetaData(meta);

  int n = meta->GetNumberOfInstances();
  for (int i = 0; i < n; i++)
  {
    char outputFile[256];
    sprintf(outputFile, "IM-0001-%04.4d.dcm", i+1);
    compiler->SetFileName(outputFile);
    compiler->SetIndex(i);
    compiler->WriteHeader();
    compiler->WritePixelData(rawPixelBufferForFile);
  }
~~~~~~~~
