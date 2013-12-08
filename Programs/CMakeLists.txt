include_directories(${DICOM_INCLUDE_DIRS})

set(PROGRAM_SRCS
  dicomdump.cxx
  dicomtonifti.cxx
  niftitodicom.cxx
  niftidump.cxx
)

if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_LIBS vtkImagingStatistics) # VTK 6.x
else()
  set(VTK_LIBS vtkImaging) # VTK 5.x
endif()

foreach(src ${PROGRAM_SRCS})
  string(REGEX REPLACE "\\.(cxx|c|mm|m)$" "" prog ${src})
  add_executable(${prog} ${src})
  target_link_libraries(${prog} vtkDICOM ${VTK_LIBS})
  list(APPEND PROGRAM_EXES ${prog})
endforeach()

install(TARGETS ${PROGRAM_EXES}
  EXPORT DICOMTargets
  RUNTIME DESTINATION ${DICOM_RUNTIME_INSTALL_DEST} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${DICOM_LIBRARY_INSTALL_DEST} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${DICOM_ARCHIVE_INSTALL_DEST} COMPONENT Development)


