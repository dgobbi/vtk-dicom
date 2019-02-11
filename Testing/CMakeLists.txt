set(TEST_SRCS
  TestDICOMCharacterSet.cxx
  TestDICOMDictionary.cxx
  TestDICOMFilePath.cxx
  TestDICOMItem.cxx
  TestDICOMMetaData.cxx
  TestDICOMSequence.cxx
  TestDICOMTagPath.cxx
  TestDICOMUtilities.cxx
  TestDICOMValue.cxx
  TestDICOMVM.cxx
  TestDICOMVR.cxx
)

if(DEFINED VTK_MODULE_ENABLE_VTK_DICOM)
  # When building as a remote module for VTK 9 (or VTK 8.90+)
  vtk_add_test_cxx(vtkDICOMCxxTests TEST_NAMES NO_VALID ${TEST_SRCS})
  vtk_test_cxx_executable(vtkDICOMCxxTests TEST_NAMES)

elseif(Module_vtkDICOM)
  # When building as a remote module for older versions of VTK
  vtk_add_test_cxx(vtkDICOMCxxTests TEST_NAMES NO_VALID ${TEST_SRCS})
  vtk_test_cxx_executable(vtkDICOMCxxTests TEST_NAMES)

else()

include_directories(${DICOM_INCLUDE_DIRS})

set(BASE_LIBS vtkDICOM ${VTK_LIBS})

foreach(_src ${TEST_SRCS})
  get_filename_component(_test ${_src} NAME_WE)
  add_executable(${_test} ${_src})
  target_link_libraries(${_test} ${BASE_LIBS})
  get_target_property(_pth ${_test} RUNTIME_OUTPUT_DIRECTORY)
  add_test(${_test} ${_pth}/${_test})
endforeach()

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

if(BUILD_TCL_WRAPPERS)
  if(CMAKE_CONFIGURATION_TYPES)
    if(NOT VTK_TCL_EXE)
      get_target_property(WRAP_TCL_PATH vtkWrapTcl LOCATION_<CONFIG>)
      get_filename_component(VTK_EXE_DIR ${WRAP_TCL_PATH} PATH)
      find_program(VTK_TCL_EXE vtk "${VTK_EXE_DIR}")
    endif()
    if(NOT VTK_TCL_EXE)
      # fall back to using tclsh
      set(VTK_TCL_EXE ${TCL_TCLSH})
    endif()
    add_test(TestDICOMTcl "${VTK_TCL_EXE}"
      "${CMAKE_CURRENT_SOURCE_DIR}/TestDICOMTcl.tcl")
  else()
    add_test(TestDICOMTcl "${TCL_TCLSH}"
      "${CMAKE_CURRENT_SOURCE_DIR}/TestDICOMTcl.tcl")
    set_tests_properties(TestDICOMTcl PROPERTIES ENVIRONMENT
      "TCLLIBPATH={${VTK_DIR}/Wrapping/Tcl} {${CMAKE_LIBRARY_OUTPUT_DIRECTORY}}")
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

endif()
