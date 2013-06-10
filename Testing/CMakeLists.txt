include_directories(${DICOM_INCLUDE_DIRS})

add_executable(TestDICOMDictionary TestDICOMDictionary.cxx)
target_link_libraries(TestDICOMDictionary vtkDICOM)
get_target_property(pth TestDICOMDictionary RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMDictionary ${pth}/TestDICOMDictionary)

add_executable(TestDICOMVM TestDICOMVM.cxx)
target_link_libraries(TestDICOMVM vtkDICOM)
get_target_property(pth TestDICOMVM RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMVM ${pth}/TestDICOMVM)

add_executable(TestDICOMVR TestDICOMVR.cxx)
target_link_libraries(TestDICOMVR vtkDICOM)
get_target_property(pth TestDICOMVR RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMVR ${pth}/TestDICOMVR)

add_executable(TestDICOMValue TestDICOMValue.cxx)
target_link_libraries(TestDICOMValue vtkDICOM)
get_target_property(pth TestDICOMValue RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMValue ${pth}/TestDICOMValue)

add_executable(TestDICOMSequence TestDICOMSequence.cxx)
target_link_libraries(TestDICOMSequence vtkDICOM)
get_target_property(pth TestDICOMSequence RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMSequence ${pth}/TestDICOMSequence)

add_executable(TestDICOMMetaData TestDICOMMetaData.cxx)
target_link_libraries(TestDICOMMetaData vtkDICOM)
get_target_property(pth TestDICOMMetaData RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMMetaData ${pth}/TestDICOMMetaData)


