## Installation {#installation}

@brief The different ways to install the package.

## Building as part of the VTK build

If are building VTK yourself, then vtk-dicom can be enabled as a VTK
remote module.  This will cause cmake to automatically download the
vtk-dicom source code from Github and build it as part of the VTK build.

To enable vtk-dicom in a VTK 9 build, set this cmake cache variable:

    VTK_MODULE_ENABLE_VTK_vtkDICOM:STRING=WANT

For VTK 7 or 8, use the following cmake cache variable instead:

    Module_vtkDICOM:BOOL=ON

After running cmake once, the following new options will become available:

    BUILD_DICOM_PROGRAMS:BOOL=ON
    USE_GDCM:BOOL=OFF
    USE_ITK_GDCM:BOOL=OFF
    USE_DCMTK:BOOL=OFF

It is highly recommended that you turn the USE_GDCM option ON, otherwise
vtk-dicom will not be able to read compressed dicom files.  This requires
[downloading GDCM from its project website](https://sourceforge.net/projects/gdcm/).

The USE_ITK_GDCM option can be used as an alternative to USE_GDCM if you
are building a program that uses ITK.  With this option, it is not necessary
to build GDCM separately.

USE_DCMTK can be enabled if you cannot use GDCM, but still require the
ability to read compressed files.  Note that the default DCMTK build does
not provide JPEG2000 support, though it can be purchased as an add-on.

## Building outside of VTK

The following procedure can be used to build the vtkDICOM
library, assuming that you have already built VTK with CMake.
This example is for building the package on Linux or OS X in
the bash shell.

    $ # specify the directory where you built VTK, this is an example
    $ export VTK_DIR=/Volumes/HD2/vtk-release-build/
    $ unzip vtk-dicom-master.zip
    $ mkdir vtk-dicom-master-build
    $ cd vtk-dicom-master-build
    $ cmake -D CMAKE_BUILD_TYPE:STRING=Release ../vtk-dicom-master
    $ make

Optionally, the following cmake variables can
be set with ccmake or cmake-gui:

    BUILD_EXAMPLES               ON
    BUILD_PROGRAMS               ON
    BUILD_SHARED_LIBS            OFF
    BUILD_TESTING                ON
    USE_DCMTK                    OFF
    USE_GDCM                     OFF
    USE_ITK_GDCM                 OFF
    VTK_DIR                      /Volumes/HD2/vtk-release-build/

The USE_DCMTK and USE_GDCM variables
allow you to add the image decompression capabilities of either of these
packages (do not specify both!) to the vtkDICOMReader.  If you do not
specify one of these packages, then the vtkDICOMReader will only be
able to read uncompressed files.  See the section above for additional
details on these variables.

## Configuring your own cmake project

The easiest way to use the vtk-dicom library in your own project is
to add the following command block to the main CMakeLists.txt file
in your project:

    find_package(DICOM QUIET)
    set(VTK_DICOM_LIBRARIES vtkDICOM)

For VTK 7 and 8, it is also necessary to include UseDICOM.cmake, as follows:

    find_package(DICOM QUIET)
    if(DICOM_FOUND)
      include(${DICOM_USE_FILE})
    endif()
    set(VTK_DICOM_LIBRARIES vtkDICOM)

It is not recommended to try to use vtk-dicom (or VTK itself)
within projects that are not built with cmake.

## Wrapper languages

All of the vtk-dicom classes can be used with Python, as long as VTK was
built with python wrapping enabled.  Use of vtk-dicom with Tcl and Java is
no longer supported (Java wrapping might still work, but is untested).

If you are already using the vtk .deb packages that came with your
debian or ubuntu linux distribution, then you have the option of using
the vtk-debian packages that were created by Mathieu Malaterre:

    sudo apt-get install python3-vtk-dicom

There are currently no pypi (pip) packages for vtk-dicom.
