include_directories(${DICOM_INCLUDE_DIRS})

if(NOT VTK_VERSION VERSION_LESS 6)
  set(VTK_RENDERING_LIBS)
  foreach(_lib RenderingImage InteractionStyle RenderingFreeType)
    list(APPEND VTK_RENDERING_LIBS ${VTK_TARGET_PREFIX}${_lib})
  endforeach()
  foreach(_lib RenderingOpenGL RenderingFreeTypeOpenGL
               RenderingOpenGL2 RenderingFreeTypeOpenGL2)
    list(FIND VTK_LIBRARIES ${VTK_TARGET_PREFIX}${_lib} _index)
    if(_index GREATER -1)
      list(APPEND VTK_RENDERING_LIBS ${VTK_TARGET_PREFIX}${_lib})
    endif()
  endforeach()
else()
  set(VTK_RENDERING_LIBS vtkRendering) # VTK 5.x
endif()

set(BASE_LIBS ${VTK_DICOM_LINK_TARGET} ${VTK_LIBS})

add_executable(TestDICOMCompiler TestDICOMCompiler.cxx)
target_link_libraries(TestDICOMCompiler ${BASE_LIBS})

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

add_executable(TestDICOMOverlay TestDICOMOverlay.cxx)
target_link_libraries(TestDICOMOverlay ${BASE_LIBS} ${VTK_RENDERING_LIBS})

add_executable(TestNIFTIDisplay TestNIFTIDisplay.cxx)
target_link_libraries(TestNIFTIDisplay ${BASE_LIBS} ${VTK_RENDERING_LIBS})

add_executable(TestScancoCTDisplay TestScancoCTDisplay.cxx)
target_link_libraries(TestScancoCTDisplay ${BASE_LIBS} ${VTK_RENDERING_LIBS})
endif()
