set(DOCUMENTATION
"This package contains a set of classes for managing DICOM
files and metadata from within VTK, and some utility programs
for interrogating and converting DICOM files."
)

vtk_module(vtkDICOM
  DESCRIPTION
    "${DOCUMENTATION}"
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkIOImage
  PRIVATE_DEPENDS
    vtkCommonMisc
    vtkImagingCore
    vtkIOCore
    vtkzlib
  COMPILE_DEPENDS
    vtkImagingStatistics
    vtkInteractionStyle
    vtkRenderingImage
    vtkRendering${VTK_RENDERING_BACKEND}
)
