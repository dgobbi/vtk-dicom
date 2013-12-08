include_directories(${DICOM_INCLUDE_DIRS})

if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_LIBS vtkRenderingImage vtkInteractionStyle
      vtkRenderingOpenGL vtkRenderingFreeTypeOpenGL) # VTK 6.x
else()
  set(VTK_LIBS vtkRendering) # VTK 5.x
endif()

add_executable(TestDICOMCompiler TestDICOMCompiler.cxx)
target_link_libraries(TestDICOMCompiler vtkDICOM)

add_executable(TestDICOMParser TestDICOMParser.cxx)
target_link_libraries(TestDICOMParser vtkDICOM)

add_executable(TestDICOMSorter TestDICOMSorter.cxx)
target_link_libraries(TestDICOMSorter vtkDICOM)

add_executable(TestDICOMReader TestDICOMReader.cxx)
target_link_libraries(TestDICOMReader vtkDICOM)

add_executable(TestDICOMWriter TestDICOMWriter.cxx)
target_link_libraries(TestDICOMWriter vtkDICOM)

if(VTK_MAJOR_VERSION GREATER 5 OR VTK_MINOR_VERSION GREATER 9)
add_executable(TestDICOMDisplay TestDICOMDisplay.cxx)
target_link_libraries(TestDICOMDisplay vtkDICOM ${VTK_LIBS})

add_executable(TestNIFTIDisplay TestNIFTIDisplay.cxx)
target_link_libraries(TestNIFTIDisplay vtkDICOM ${VTK_LIBS})
endif()
