set(DOCUMENTATION
"This package contains a set of classes for managing DICOM
files and metadata from within VTK, and some utility programs
for interrogating and converting DICOM files."
)

vtk_module(vtkDICOM
  DESCRIPTION
    "${DOCUMENTATION}"
  DEPENDS
    vtkIOImage
    vtkIOSQL
  PRIVATE_DEPENDS
    vtksys
    vtkzlib
    vtkImagingStatistics
    vtkInteractionStyle
    vtkRenderingImage
    vtkRendering${VTK_RENDERING_BACKEND}
)
