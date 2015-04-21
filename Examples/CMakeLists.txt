include_directories(${DICOM_INCLUDE_DIRS})

if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_RENDERING_LIBS vtkRenderingImage vtkInteractionStyle
      vtkRenderingFreeType) # VTK 6.x
  set(VTK_GL_LIBS vtkRenderingOpenGL vtkRenderingFreeTypeOpenGL
      vtkRenderingOpenGL2 vtkRenderingFreeTypeOpenGL2)
  foreach(TMP_LIB ${VTK_GL_LIBS})
    list(FIND VTK_LIBRARIES ${TMP_LIB} TMP_INDEX)
    if(TMP_INDEX GREATER -1)
      set(VTK_RENDERING_LIBS ${VTK_RENDERING_LIBS} ${TMP_LIB})
    endif()
  endforeach()
else()
  set(VTK_RENDERING_LIBS vtkRendering) # VTK 5.x
endif()

set(BASE_LIBS vtkDICOM ${VTK_LIBS})
if(USE_DCMTK AND DCMTK_charls_LIBRARY)
 set(BASE_LIBS ${BASE_LIBS} ${DCMTK_charls_LIBRARY})
endif()

add_executable(TestDICOMCompiler TestDICOMCompiler.cxx)
target_link_libraries(TestDICOMCompiler ${BASE_LIBS} ${KWSYS_LIBS})

add_executable(TestDICOMDirectory TestDICOMDirectory.cxx)
target_link_libraries(TestDICOMDirectory ${BASE_LIBS})

add_executable(TestDICOMParser TestDICOMParser.cxx)
target_link_libraries(TestDICOMParser ${BASE_LIBS})

add_executable(TestDICOMFileSorter TestDICOMFileSorter.cxx)
target_link_libraries(TestDICOMFileSorter ${BASE_LIBS})

add_executable(TestDICOMReader TestDICOMReader.cxx)
target_link_libraries(TestDICOMReader ${BASE_LIBS})

add_executable(TestDICOMWriter TestDICOMWriter.cxx)
target_link_libraries(TestDICOMWriter ${BASE_LIBS})

add_executable(TestDICOMRealWorldValue TestDICOMRealWorldValue.cxx)
target_link_libraries(TestDICOMRealWorldValue ${BASE_LIBS})

if(VTK_MAJOR_VERSION GREATER 5 OR VTK_MINOR_VERSION GREATER 9)
add_executable(TestDICOMDisplay TestDICOMDisplay.cxx)
target_link_libraries(TestDICOMDisplay ${BASE_LIBS} ${VTK_RENDERING_LIBS})

add_executable(TestNIFTIDisplay TestNIFTIDisplay.cxx)
target_link_libraries(TestNIFTIDisplay ${BASE_LIBS} ${VTK_RENDERING_LIBS})

add_executable(TestScancoCTDisplay TestScancoCTDisplay.cxx)
target_link_libraries(TestScancoCTDisplay ${BASE_LIBS} ${VTK_RENDERING_LIBS})
endif()
