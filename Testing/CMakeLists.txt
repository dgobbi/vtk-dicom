include_directories(${DICOM_INCLUDE_DIRS})

set(BASE_LIBS vtkDICOM ${VTK_LIBS})

add_executable(TestDICOMDictionary TestDICOMDictionary.cxx)
target_link_libraries(TestDICOMDictionary ${BASE_LIBS})
get_target_property(pth TestDICOMDictionary RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMDictionary ${pth}/TestDICOMDictionary)

add_executable(TestDICOMVM TestDICOMVM.cxx)
target_link_libraries(TestDICOMVM ${BASE_LIBS})
get_target_property(pth TestDICOMVM RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMVM ${pth}/TestDICOMVM)

add_executable(TestDICOMVR TestDICOMVR.cxx)
target_link_libraries(TestDICOMVR ${BASE_LIBS})
get_target_property(pth TestDICOMVR RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMVR ${pth}/TestDICOMVR)

add_executable(TestDICOMValue TestDICOMValue.cxx)
target_link_libraries(TestDICOMValue ${BASE_LIBS})
get_target_property(pth TestDICOMValue RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMValue ${pth}/TestDICOMValue)

add_executable(TestDICOMSequence TestDICOMSequence.cxx)
target_link_libraries(TestDICOMSequence ${BASE_LIBS})
get_target_property(pth TestDICOMSequence RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMSequence ${pth}/TestDICOMSequence)

add_executable(TestDICOMItem TestDICOMItem.cxx)
target_link_libraries(TestDICOMItem ${BASE_LIBS})
get_target_property(pth TestDICOMItem RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMItem ${pth}/TestDICOMItem)

add_executable(TestDICOMMetaData TestDICOMMetaData.cxx)
target_link_libraries(TestDICOMMetaData ${BASE_LIBS})
get_target_property(pth TestDICOMMetaData RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMMetaData ${pth}/TestDICOMMetaData)

add_executable(TestDICOMCharacterSet TestDICOMCharacterSet.cxx)
target_link_libraries(TestDICOMCharacterSet ${BASE_LIBS})
get_target_property(pth TestDICOMCharacterSet RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMCharacterSet ${pth}/TestDICOMCharacterSet)

add_executable(TestDICOMUtilities TestDICOMUtilities.cxx)
target_link_libraries(TestDICOMUtilities ${BASE_LIBS})
get_target_property(pth TestDICOMUtilities RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMUtilities ${pth}/TestDICOMUtilities)

add_executable(TestDICOMFilePath TestDICOMFilePath.cxx)
target_link_libraries(TestDICOMFilePath ${BASE_LIBS})
get_target_property(pth TestDICOMFilePath RUNTIME_OUTPUT_DIRECTORY)
add_test(TestDICOMFilePath ${pth}/TestDICOMFilePath)

if(BUILD_PYTHON_WRAPPERS)
  if(NOT VTK_PYTHON_EXE)
    get_target_property(WRAP_PYTHON_PATH vtkWrapPython LOCATION_<CONFIG>)
    get_filename_component(VTK_EXE_DIR ${WRAP_PYTHON_PATH} PATH)
    find_program(VTK_PYTHON_EXE vtkpython "${VTK_EXE_DIR}")
  endif()
  if(NOT VTK_PYTHON_EXE)
    # fall back to using python rather than vtkpython
    find_package(PythonInterp QUIET)
    mark_as_advanced(PYTHON_EXECUTABLE)
    set(VTK_PYTHON_EXE ${PYTHON_EXECUTABLE})
  endif()
  add_test(TestDICOMPython "${VTK_PYTHON_EXE}"
    "${CMAKE_CURRENT_SOURCE_DIR}/TestDICOMPython.py")
  if(NOT CMAKE_CONFIGURATION_TYPES)
    set_tests_properties(TestDICOMPython PROPERTIES ENVIRONMENT
      "PYTHONPATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
  endif()
endif()

if(BUILD_JAVA_WRAPPERS)
  set(_sep ":")
  if(WIN32)
    set(_sep "\\;")
  endif()
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/TestDICOMJava.java.in"
    "${CMAKE_CURRENT_BINARY_DIR}/TestDICOMJava.java" @ONLY)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/javac_test_stamp.txt
    COMMAND ${JAVA_COMPILE} ${JAVAC_OPTIONS}
    -source ${VTK_JAVA_SOURCE_VERSION}
    -target ${VTK_JAVA_TARGET_VERSION}
    -classpath "${VTK_JAR_PATH}/vtkdicom.jar${_sep}${DICOM_BINARY_DIR}/java${_sep}${VTK_JAVA_JAR}"
    -sourcepath ${CMAKE_CURRENT_SOURCE_DIR}
    -d ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/TestDICOMJava.java
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/javac_test_stamp.txt
    DEPENDS vtkDICOMJavaJar
    "${CMAKE_CURRENT_BINARY_DIR}/TestDICOMJava.java"
    COMMENT "Compiling Java Tests"
    )
  add_custom_target(DICOMJavaTests ALL DEPENDS
    ${CMAKE_CURRENT_BINARY_DIR}/javac_test_stamp.txt ${JAVA_LIBRARIES})
  add_test(TestDICOMJava "${JAVA_RUNTIME}"
    -classpath "${VTK_JAR_PATH}/vtkdicom.jar${_sep}${DICOM_BINARY_DIR}/java${_sep}${VTK_JAVA_JAR}${_sep}${CMAKE_CURRENT_BINARY_DIR}"
    TestDICOMJava)
endif()
