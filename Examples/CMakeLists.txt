include_directories(${DICOM_SOURCE_DIR})

add_executable(TestDICOMParser TestDICOMParser.cxx)
target_link_libraries(TestDICOMParser vtkDICOM)

add_executable(TestDICOMSorter TestDICOMSorter.cxx)
target_link_libraries(TestDICOMSorter vtkDICOM)

add_executable(TestDICOMReader TestDICOMReader.cxx)
target_link_libraries(TestDICOMReader vtkDICOM)

add_executable(TestDICOMDisplay TestDICOMDisplay.cxx)
target_link_libraries(TestDICOMDisplay vtkDICOM vtkRendering)

add_executable(TestNIFTIDisplay TestNIFTIDisplay.cxx)
target_link_libraries(TestNIFTIDisplay vtkDICOM vtkRendering)
