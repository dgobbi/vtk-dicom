include_directories(${DICOM_SOURCE_DIR})

add_executable(TestDICOMDictionary TestDICOMDictionary.cxx)
target_link_libraries(TestDICOMDictionary vtkDICOM)
add_test(TestDICOMDictionary TestDICOMDictionary)

add_executable(TestDICOMVM TestDICOMVM.cxx)
target_link_libraries(TestDICOMVM vtkDICOM)
add_test(TestDICOMVM TestDICOMVM)

add_executable(TestDICOMVR TestDICOMVR.cxx)
target_link_libraries(TestDICOMVR vtkDICOM)
add_test(TestDICOMVR TestDICOMVR)

add_executable(TestDICOMValue TestDICOMValue.cxx)
target_link_libraries(TestDICOMValue vtkDICOM)
add_test(TestDICOMValue TestDICOMValue)

add_executable(TestDICOMSequence TestDICOMSequence.cxx)
target_link_libraries(TestDICOMSequence vtkDICOM)
add_test(TestDICOMSequence TestDICOMSequence)

add_executable(TestDICOMMetaData TestDICOMMetaData.cxx)
target_link_libraries(TestDICOMMetaData vtkDICOM)
add_test(TestDICOMMetaData TestDICOMMetaData)


