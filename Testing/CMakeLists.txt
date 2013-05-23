include_directories(${DICOM_SOURCE_DIR})

add_executable(TestDICOMVR TestDICOMVR.cxx)
target_link_libraries(TestDICOMVR vtkDICOM)
add_test(TestDICOMVR TestDICOMVR)

add_executable(TestDICOMValue TestDICOMValue.cxx)
target_link_libraries(TestDICOMValue vtkDICOM)
add_test(TestDICOMValue TestDICOMValue)

add_executable(TestDICOMSequence TestDICOMSequence.cxx)
target_link_libraries(TestDICOMSequence vtkDICOM)
add_test(TestDICOMSequence TestDICOMSequence)
