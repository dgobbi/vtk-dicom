include_directories(${DICOM_INCLUDE_DIRS})

set(PROGRAM_SRCS
  dicomdump.cxx
  dicomtonifti.cxx
  minctonifti.cxx
  niftitodicom.cxx
  niftidump.cxx
)

if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_IMAGING_LIBS vtkImagingStatistics) # VTK 6.x
  set(VTK_MINC_LIBS vtkIOMINC vtkInteractionStyle
      vtkRenderingOpenGL vtkRenderingFreeTypeOpenGL)
else()
  set(VTK_IMAGING_LIBS vtkImaging) # VTK 5.x
  set(VTK_MINC_LIBS)
endif()

set(BASE_LIBS vtkDICOM ${VTK_LIBS})
if(USE_DCMTK AND DCMTK_charls_LIBRARY)
 set(BASE_LIBS ${BASE_LIBS} ${DCMTK_charls_LIBRARY})
endif()

foreach(src ${PROGRAM_SRCS})
  string(REGEX REPLACE "\\.(cxx|c|mm|m)$" "" prog ${src})
  add_executable(${prog} ${src})
  if("${prog}" MATCHES "minc")
    target_link_libraries(${prog} ${BASE_LIBS}
      ${VTK_IMAGING_LIBS} ${VTK_MINC_LIBS} ${KWSYS_LIBS})
  else()
    target_link_libraries(${prog} ${BASE_LIBS}
      ${VTK_IMAGING_LIBS} ${KWSYS_LIBS})
  endif()
  list(APPEND PROGRAM_EXES ${prog})
endforeach()

install(TARGETS ${PROGRAM_EXES}
  EXPORT DICOMTargets
  RUNTIME DESTINATION ${DICOM_RUNTIME_INSTALL_DEST} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${DICOM_LIBRARY_INSTALL_DEST} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${DICOM_ARCHIVE_INSTALL_DEST} COMPONENT Development)
