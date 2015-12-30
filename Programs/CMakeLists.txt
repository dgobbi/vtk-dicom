include_directories(
  ${DICOM_INCLUDE_DIRS}
  ${DICOM_SOURCE_DIR}/DicomCli
  ${DICOM_BINARY_DIR}/DicomCli
)

set(PROGRAM_SRCS
  dicomdump.cxx
  dicomfind.cxx
  dicompull.cxx
  dicomtocsv.cxx
  dicomtodicom.cxx
  dicomtonifti.cxx
  niftitodicom.cxx
  niftidump.cxx
  scancotodicom.cxx
  scancodump.cxx
)

if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_IMAGING_LIBS vtkImagingStatistics) # VTK 6.x
else()
  set(VTK_IMAGING_LIBS) # VTK 5.x
endif()

set(BASE_LIBS vtkDICOM ${VTK_LIBS})

set(CLI_LIBS dicomcli)

foreach(src ${PROGRAM_SRCS})
  string(REGEX REPLACE "\\.(cxx|c|mm|m)$" "" prog ${src})
  add_executable(${prog} ${src})
  target_link_libraries(${prog} ${BASE_LIBS} ${CLI_LIBS}
    ${VTK_IMAGING_LIBS} ${KWSYS_LIBS})
  list(APPEND PROGRAM_EXES ${prog})
endforeach()

install(TARGETS ${PROGRAM_EXES}
  EXPORT DICOMTargets
  RUNTIME DESTINATION ${DICOM_RUNTIME_INSTALL_DEST} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${DICOM_LIBRARY_INSTALL_DEST} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${DICOM_ARCHIVE_INSTALL_DEST} COMPONENT Development)
