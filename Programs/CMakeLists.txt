include_directories(${DICOM_INCLUDE_DIRS})

set(PROGRAM_SRCS
  dicomdump.cxx
  dicomtonifti.cxx
  niftidump.cxx
)

foreach(src ${PROGRAM_SRCS})
  string(REGEX REPLACE "\\.(cxx|c|mm|m)$" "" prog ${src})
  add_executable(${prog} ${src})
  target_link_libraries(${prog} vtkDICOM)
  list(APPEND PROGRAM_EXES ${prog})
endforeach()

install(TARGETS ${PROGRAM_EXES}
  EXPORT DICOMTargets
  RUNTIME DESTINATION ${DICOM_RUNTIME_INSTALL_DEST} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${DICOM_LIBRARY_INSTALL_DEST} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${DICOM_ARCHIVE_INSTALL_DEST} COMPONENT Development)


