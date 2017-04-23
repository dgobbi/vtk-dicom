## Image Orientation {#imageOrientation}

@brief Medical image orientation in VTK.

## Overview

When people use the term "image orientation" with respect to medical images,
they usually mean one or more of the items listed below:
1. The order in which the pixels, rows, and slices are stored in the computer's
memory.
2. The orientation of the image slices in a real-world coordinate system, for example the patient coordinate system as defined by the medical imaging equipment that generated the images.
3. The orientation of the subject (patient) with respect to the viewer when the images are viewed on a workstation.

The first of these, the way the data is stored in memory, should merely
be an implementation detail, but unfortunately the vtkImageViewer class
insists that the pixels must be arranged in memory such that the pixel
at the bottom-left corner of the image is the pixel at the lowest address
in memory.  This is in conflict with DICOM, which stores the top-left pixel
as the first pixel in the file.  To provide compatibility with the
vtkImageViewer, the default behavior of the vtkDICOMReader is to flip
the image in memory while it is loading it from the file.  This behavior
can be turned off by calling reader->SetMemoryRowOrderToFileNative().

The second and third items in the list can be referred to as the real-world
orientation, and the display orientation, respectively.  Neither of these can
be considered an implementation detail, as both of them are crucial to the
user experience.  Also, it is important not to confuse one with the other.
An application that incorrectly manages the real-world orientation is
seriously flawed, even if it manages to display the images to the user
in the correct orientation.

The real-world orientation is provided by the GetPatientMatrix() method
of the vtkDICOMReader.  This method returns a vtkMatrix4x4 object that
describes the coordinate transformation from the data coordinates of the
vtkImageData that stores the image, to the real-world Patient Coordinate
System defined in the DICOM standard.  The matrix is
used to correctly place the image in the VTK world coordinate system.

The PatientMatrix is constructed from the ImagePositionPatient and
ImageOrientationPatient attributes in the series of DICOM files that are
provided to the reader.  Note that unless SetMemoryRowOrderToFileNative()
has been called on the reader, the orientation of the matrix will be
flipped with respect to ImageOrientationPatient in order to account for
the fact that the image rows were flipped in memory.

~~~~~~~~{.cpp}
  reader->SetMemoryRowOrderToFileNative(); // keep native row order
  reader->Update(); // update the reader
  vtkMatrix4x4 *matrix = reader->GetPatientMatrix();

  // create an image actor and specify the orientation.
  vtkNew<vtkImageActor> actor;
  actor->GetMapper()->SetInputConnection(reader->GetOutputPort());
  actor->SetUserMatrix(matrix);
~~~~~~~~

Setting the actor's UserMatrix will ensure that
the real-world orientation of the image is correctly handled, as far as
the VTK display pipeline is concerned.  It does not, however, set the
display orientation, which is the responsibility of the application.
The display orientation can be set via manipulation of the VTK camera.
