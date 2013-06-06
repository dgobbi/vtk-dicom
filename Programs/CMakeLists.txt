include_directories(${DICOM_SOURCE_DIR})

add_executable(dicomdump dicomdump.cxx)
target_link_libraries(dicomdump vtkDICOM)

add_executable(dicomtonifti dicomtonifti.cxx)
target_link_libraries(dicomtonifti vtkDICOM)
