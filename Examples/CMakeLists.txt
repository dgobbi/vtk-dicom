include_directories(${DICOM_INCLUDE_DIRS})

if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_RENDERING_LIBS vtkRenderingImage vtkInteractionStyle
      vtkRenderingOpenGL vtkRenderingFreeTypeOpenGL) # VTK 6.x
else()
  set(VTK_RENDERING_LIBS vtkRendering) # VTK 5.x
endif()

set(BASE_LIBS vtkDICOM ${VTK_LIBS})
if(USE_DCMTK)
 set(BASE_LIBS ${BASE_LIBS} ${DCMTK_charls_LIBRARY})
endif()

add_executable(TestDICOMCompiler TestDICOMCompiler.cxx)
target_link_libraries(TestDICOMCompiler ${BASE_LIBS} ${KWSYS_LIBS})

add_executable(TestDICOMDirectory TestDICOMDirectory.cxx)
target_link_libraries(TestDICOMDirectory ${BASE_LIBS})

add_executable(TestDICOMParser TestDICOMParser.cxx)
target_link_libraries(TestDICOMParser ${BASE_LIBS})

add_executable(TestDICOMSorter TestDICOMSorter.cxx)
target_link_libraries(TestDICOMSorter ${BASE_LIBS})

add_executable(TestDICOMReader TestDICOMReader.cxx)
target_link_libraries(TestDICOMReader ${BASE_LIBS})

add_executable(TestDICOMWriter TestDICOMWriter.cxx)
target_link_libraries(TestDICOMWriter ${BASE_LIBS})

if(VTK_MAJOR_VERSION GREATER 5 OR VTK_MINOR_VERSION GREATER 9)
add_executable(TestDICOMDisplay TestDICOMDisplay.cxx)
target_link_libraries(TestDICOMDisplay ${BASE_LIBS} ${VTK_RENDERING_LIBS})

add_executable(TestNIFTIDisplay TestNIFTIDisplay.cxx)
target_link_libraries(TestNIFTIDisplay ${BASE_LIBS} ${VTK_RENDERING_LIBS})
endif()
