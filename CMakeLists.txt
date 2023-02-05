# for CMake 3, add VERSION X.Y.Z to set the version here
project(DICOM)

# CMake version requirements
cmake_minimum_required(VERSION 3.12)

# Allow custom cmake overrides
set(DICOM_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
set(CMAKE_MODULE_PATH ${DICOM_CMAKE_DIR} ${CMAKE_MODULE_PATH})

# Use ctest for dashboard submissions
include(CTest)

# Project version
set(DICOM_MAJOR_VERSION 0)
set(DICOM_MINOR_VERSION 8)
set(DICOM_PATCH_VERSION 14)
set(DICOM_SHORT_VERSION "${DICOM_MAJOR_VERSION}.${DICOM_MINOR_VERSION}")
set(DICOM_VERSION "${DICOM_SHORT_VERSION}.${DICOM_PATCH_VERSION}")

# Generic project version variables (forwards compatibility with CMake 3)
set(PROJECT_MAJOR_VERSION ${DICOM_MAJOR_VERSION})
set(PROJECT_MINOR_VERSION ${DICOM_MINOR_VERSION})
set(PROJECT_PATCH_VERSION ${DICOM_PATCH_VERSION})
set(PROJECT_VERSION ${DICOM_VERSION})

# Include directories
set(DICOM_INCLUDE_DIRS
  "${DICOM_SOURCE_DIR}/Source"
  "${DICOM_BINARY_DIR}/Source")

# Is this CMakeLists.txt file being called directly by cmake?
if("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
  set(_dicom_direct_build ON)
else()
  set(_dicom_direct_build OFF)
endif()

set(DICOM_EXTERNAL_BUILD ${_dicom_direct_build} CACHE BOOL
    "Building DICOM module external to the VTK build")
mark_as_advanced(DICOM_EXTERNAL_BUILD)

if(DEFINED VTK_MODULE_ENABLE_VTK_DICOM AND NOT DICOM_EXTERNAL_BUILD)
  # When building as a remote module for VTK 9 (or VTK 8.90+)
  message(STATUS "vtkDICOM: Building vtkDICOM as a Remote VTK Module")

  # Clear VTK_LIBS, linking will be handled by modular build
  set(VTK_LIBS)
  set(VTK_DICOM_LINK_TARGET VTK::DICOM)

  # To set DICOM_USE_VTKZLIB in vtkDICOMConfig.h
  set(DICOM_USE_VTKZLIB ON)

  option(BUILD_DICOM_PROGRAMS "Build the vtkDICOM tools" OFF)
  option(BUILD_DICOM_EXAMPLES "Build the vtkDICOM examples" OFF)
  set(BUILD_PROGRAMS ${BUILD_DICOM_PROGRAMS})
  set(BUILD_EXAMPLES ${BUILD_DICOM_EXAMPLES})

elseif(Module_vtkDICOM)
  # When building as a remote module for older versions of VTK
  message(STATUS "vtkDICOM: Building vtkDICOM as a Remote VTK Module")
  set(vtkDICOM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
  set(vtkDICOM_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Source)
  vtk_module_impl()

  # Clear VTK_LIBS, linking will be handled by modular build
  set(VTK_LIBS)
  set(VTK_DICOM_LINK_TARGET vtkDICOM)

  # To set DICOM_USE_VTKZLIB in vtkDICOMConfig.h
  set(DICOM_USE_VTKZLIB ON)

  option(BUILD_DICOM_PROGRAMS "Build the vtkDICOM tools" ON)
  option(BUILD_DICOM_EXAMPLES "Build the vtkDICOM examples" OFF)
  set(BUILD_PROGRAMS ${BUILD_DICOM_PROGRAMS})
  set(BUILD_EXAMPLES ${BUILD_DICOM_EXAMPLES})

else()
  # When building external to VTK
  message(STATUS "vtkDICOM: Building vtkDICOM outside of VTK")

  # Find VTK and get VTK configuration information
  find_package(VTK REQUIRED)

  # define VTK_VERSION if not already defined
  if(NOT DEFINED VTK_VERSION)
    set(VTK_VERSION ${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION})
  endif()
  if(VTK_VERSION VERSION_LESS 8.90)
    include(${VTK_USE_FILE})
  endif()
  if(VTK_VERSION VERSION_LESS 6.0)
    message(FATAL_ERROR "VTK 6 or later is required.")
  endif()

  # We are being built as a stand-alone package
  set(VTK_DICOM_LINK_TARGET vtkDICOM)

  # When CMake 3.0.0 is required, remove this block (see CMP0042).
  if(NOT DEFINED CMAKE_MACOSX_RPATH)
    set(CMAKE_MACOSX_RPATH 0)
  endif()

  option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

  # Which parts of the package to build
  option(BUILD_TESTING "Build the tests" OFF)
  option(BUILD_PROGRAMS "Build some useful DICOM tools" ON)
  option(BUILD_EXAMPLES "Build the examples" OFF)

  # Wrap Python option
  if(VTK_WRAP_PYTHON)
    option(BUILD_PYTHON_WRAPPERS "Build python wrappers" ON)
  else()
    unset(BUILD_PYTHON_WRAPPERS CACHE)
  endif()

  # Wrap Tcl option
  if(VTK_WRAP_TCL)
    option(BUILD_TCL_WRAPPERS "Build tcl wrappers" ON)
  else()
    unset(BUILD_TCL_WRAPPERS CACHE)
  endif()

  # Wrap Java option
  if(VTK_WRAP_JAVA)
    option(BUILD_JAVA_WRAPPERS "Build java wrappers" OFF)
  else()
    unset(BUILD_JAVA_WRAPPERS CACHE)
  endif()

  # Defines CMAKE_INSTALL_LIBDIR etcetera
  include(GNUInstallDirs)

  # Set up our directory structure for output libraries and binaries
  # (Note: these are the build locations, not the install locations)
  if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${DICOM_BINARY_DIR}/bin")
  endif()
  if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    if(UNIX)
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${DICOM_BINARY_DIR}/lib")
    else()
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${DICOM_BINARY_DIR}/bin")
    endif()
  endif()
  if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${DICOM_BINARY_DIR}/lib")
  endif()

  # Check if VTK set VTK_ZLIB_LIBRARIES
  if(NOT VTK_ZLIB_LIBRARIES)
    # VTK doesn't set it, so search for vtkzlib directly
    if(VTK_VERSION VERSION_LESS 8.90)
      list(FIND VTK_LIBRARIES "vtkzlib" TMP_INDEX)
    else()
      list(FIND VTK_LIBRARIES "VTK::zlib" TMP_INDEX)
    endif()
    if(TMP_INDEX GREATER -1)
      set(VTK_ZLIB_LIBRARIES vtkzlib)
    endif()
  endif()
  set(DICOM_USE_VTKZLIB OFF)
  if(VTK_ZLIB_LIBRARIES)
    set(DICOM_USE_VTKZLIB ON)
    set(ZLIB_LIBS ${VTK_ZLIB_LIBRARIES})
  endif()

  # Look for zlib
  if(NOT DICOM_USE_VTKZLIB)
    find_package(ZLIB REQUIRED)
    if(ZLIB_FOUND)
      set(ZLIB_LIBS ${ZLIB_LIBRARIES})
      include_directories("${ZLIB_INCLUDE_DIR}")
    endif()
  endif()

  if(NOT VTK_VERSION VERSION_LESS 8.90)
    # When building as a stand-alone module for VTK 9
    message(STATUS "vtkDICOM: Building as an External VTK Module")

    # Clear VTK_LIBS, linking will be handled by modular build
    set(VTK_LIBS)
    set(VTK_DICOM_LINK_TARGET VTK::DICOM)

    # To set DICOM_USE_VTKZLIB in vtkDICOMConfig.h
    set(DICOM_USE_VTKZLIB ON)

    option(DICOM_VERSIONED_INSTALL "Install with versioned names." ON)
    mark_as_advanced(DICOM_VERSIONED_INSTALL)
    set(vtk_version_suffix "")
    set(dicom_library_suffix "")
    if(VTK_VERSIONED_INSTALL OR DICOM_VERSIONED_INSTALL)
      set(vtk_version_suffix "-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}")
      set(dicom_library_suffix "${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}")
    endif()
    if(DEFINED DICOM_CUSTOM_LIBRARY_SUFFIX)
      set(dicom_library_suffix "${DICOM_CUSTOM_LIBRARY_SUFFIX}")
    endif()

    # Where to put config files
    set(cmake_destination
      "${CMAKE_INSTALL_LIBDIR}/cmake/dicom-${DICOM_SHORT_VERSION}")

    vtk_module_scan(
      MODULE_FILES        "${CMAKE_CURRENT_SOURCE_DIR}/Source/dicom.module"
      REQUEST_MODULES     "VTK::DICOM"
      PROVIDES_MODULES    dicom_modules
      ENABLE_TESTS        "${BUILD_TESTING}")

    vtk_module_build(
      MODULES             ${dicom_modules}
      INSTALL_EXPORT      DICOM
      ARCHIVE_DESTINATION "lib"
      HEADERS_DESTINATION "include/vtk${vtk_version_suffix}"
      CMAKE_DESTINATION   "${cmake_destination}"
      LICENSE_DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/dicom-${DICOM_SHORT_VERSION}"
      HIERARCHY_DESTINATION "${CMAKE_INSTALL_LIBDIR}/vtk${vtk_version_suffix}/hierarchy/DICOM"
      LIBRARY_NAME_SUFFIX "${dicom_library_suffix}"
      VERSION             "${DICOM_VERSION}"
      SOVERSION           "1"
      TEST_DATA_TARGET    DicomData
      USE_EXTERNAL        "${DICOM_USE_EXTERNAL}"
      TEST_INPUT_DATA_DIRECTORY   "${dicom_test_data_directory_input}"
      TEST_OUTPUT_DATA_DIRECTORY  "${dicom_test_data_directory_output}")

    # Disable deprecation warnings for MSVC
    if(MSVC)
      vtk_module_definitions(${dicom_modules}
        PRIVATE -D_CRT_SECURE_NO_DEPRECATE)
    endif()

    if(BUILD_PYTHON_WRAPPERS)
      find_package(PythonInterp ${VTK_PYTHON_VERSION} QUIET)

      vtk_module_wrap_python(
        MODULES         ${dicom_modules}
        TARGET          VTK::vtkdicommodules
        INSTALL_EXPORT  DICOMPython
        PYTHON_PACKAGE  "vtkdicom"
        CMAKE_DESTINATION   "${cmake_destination}"
        LIBRARY_DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        SOABI           "${Python${VTK_PYTHON_VERSION}_SOABI}"
        BUILD_STATIC    OFF)

      vtk_module_python_default_destination(python_destination)
      string(CONCAT _content
        "from .vtkDICOM import *\n\n"
        "__all__ = ['vtkDICOM']\n"
        "__version__ = \"${DICOM_VERSION}\"\n")
      file(GENERATE
        OUTPUT  "${CMAKE_BINARY_DIR}/${python_destination}/vtkdicom/__init__.py"
        CONTENT "${_content}")
      install(
        FILES       "${CMAKE_BINARY_DIR}/${python_destination}/vtkdicom/__init__.py"
        DESTINATION "${python_destination}/vtkdicom/")

      export(
        EXPORT    DICOMPython
        NAMESPACE VTK::
        FILE      "${cmake_destination}/DICOMPython-targets.cmake")
      install(
        EXPORT      DICOMPython
        NAMESPACE   VTK::
        FILE        DICOMPython-targets.cmake
        DESTINATION "${cmake_destination}")
    endif()

    if(BUILD_JAVA_WRAPPERS)
      # Untested, probably broken
      vtk_module_wrap_java(
        MODULES         ${dicom_modules}
        WRAPPED_MODULES dicom_java_wrapped_modules
        JAVA_OUTPUT     "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles")
    endif()

    # Generate config files
    include(CMakePackageConfigHelpers)
    configure_package_config_file(CMake/dicom-config.cmake.in
      "${cmake_destination}/dicom-config.cmake"
      INSTALL_DESTINATION "${cmake_destination}")
    write_basic_package_version_file("${cmake_destination}/dicom-config-version.cmake"
      VERSION "${DICOM_MAJOR_VERSION}.${DICOM_MINOR_VERSION}.${DICOM_PATCH_VERSION}"
      COMPATIBILITY AnyNewerVersion)

    # In root of build directory for backwards compatibility
    file(GENERATE
      OUTPUT  "${CMAKE_BINARY_DIR}/dicom-config.cmake"
      CONTENT "include(\"${CMAKE_BINARY_DIR}/${cmake_destination}/dicom-config.cmake\")\n")
    configure_file(
      "${CMAKE_BINARY_DIR}/${cmake_destination}/dicom-config-version.cmake"
      "${CMAKE_BINARY_DIR}/dicom-config-version.cmake"
      COPYONLY)

    install(
      FILES       "${CMAKE_BINARY_DIR}/${cmake_destination}/dicom-config.cmake"
                  "${CMAKE_BINARY_DIR}/${cmake_destination}/dicom-config-version.cmake"
      DESTINATION "${cmake_destination}"
      COMPONENT   "development")

  endif() #(NOT VTK_VERSION VERSION_LESS 8.90)

endif()

# Store the git hash of the current head
if(EXISTS "${DICOM_SOURCE_DIR}/.git/HEAD")
  file(READ "${DICOM_SOURCE_DIR}/.git/HEAD" DICOM_SOURCE_VERSION)
  if("${DICOM_SOURCE_VERSION}" MATCHES "^ref:")
    string(REGEX REPLACE "^ref: *([^ \n\r]*).*" "\\1"
      DICOM_GIT_REF "${DICOM_SOURCE_VERSION}")
    file(READ "${DICOM_SOURCE_DIR}/.git/${DICOM_GIT_REF}"
      DICOM_SOURCE_VERSION)
  endif()
  string(STRIP "${DICOM_SOURCE_VERSION}" DICOM_SOURCE_VERSION)
endif()

# Store the build date
if(WIN32)
#  execute_process(COMMAND "cmd" " /c date /t" OUTPUT_VARIABLE DATE)
#  string(REGEX REPLACE "[^0-9]*(..).*" "\\1" MONTH "${DATE}")
#  set(MONTHS ""
#    "Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul" "Aug" "Sep" "Oct" "Nov" "Dec")
#  list(GET MONTHS "${MONTH}" MONTH)
#  string(REGEX REPLACE "[^/]*/(..)/(....).*" "\\1 ${MONTH} \\2"
#    DICOM_BUILD_DATE "${DATE}")
#  execute_process(COMMAND "cmd" " /c echo %TIME%" OUTPUT_VARIABLE TIME)
#  string(REGEX REPLACE "[^0-9]*(..:..:..).*" "\\1"
#    DICOM_BUILD_TIME "${TIME}")
else()
  execute_process(COMMAND "date" "+%d %b %Y/%H:%M:%S"
    OUTPUT_VARIABLE DATE_TIME)
  string(REGEX REPLACE "([^/]*)/.*" "\\1"
    DICOM_BUILD_DATE "${DATE_TIME}")
  string(REGEX REPLACE "[^/]*/([0-9:]*).*" "\\1"
    DICOM_BUILD_TIME "${DATE_TIME}")
endif()

if(Module_vtkDICOM)
  set(DICOM_BIN_DIR ${VTK_INSTALL_RUNTIME_DIR})
  set(DICOM_LIB_DIR ${VTK_INSTALL_LIBRARY_DIR})
  set(DICOM_ARC_DIR ${VTK_INSTALL_ARCHIVE_DIR})
  set(DICOM_INC_DIR ${VTK_INSTALL_INCLUDE_DIR})
endif()

# Set up our target directory structure for "make install"
set(DICOM_BIN_DIR "bin") # for executables and ".dll" libraries
if(NOT DICOM_LIB_DIR)
  set(DICOM_LIB_DIR "lib") # for unix/linux/osx shared libraries
endif()
if(NOT DICOM_ARC_DIR)
  set(DICOM_ARC_DIR "${DICOM_LIB_DIR}") # for static or ".lib" libraries
endif()
if(NOT DICOM_INC_DIR)
  set(DICOM_INC_DIR "include") # for header files
endif()
if(NOT DICOM_TCL_DIR)
  set(DICOM_TCL_DIR "lib/tcltk/dicom-${DICOM_SHORT_VERSION}")
endif()
if(NOT DICOM_JAVA_DIR)
  set(DICOM_JAVA_DIR "share/java")
endif()
if(NOT DICOM_DATA_DIR)
  set(DICOM_DATA_DIR "share/dicom-${DICOM_SHORT_VERSION}")
endif()
if(NOT DICOM_PGK_DIR)
  set(DICOM_PGK_DIR "${DICOM_LIB_DIR}/dicom-${DICOM_SHORT_VERSION}/cmake")
endif()

# Set the full paths to the install tree
set(DICOM_RUNTIME_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_BIN_DIR})
set(DICOM_LIBRARY_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_LIB_DIR})
set(DICOM_ARCHIVE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_ARC_DIR})
set(DICOM_INCLUDE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_INC_DIR})
set(DICOM_TCL_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_TCL_DIR})
set(DICOM_JAVA_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_JAVA_DIR})
set(DICOM_DATA_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_DATA_DIR})
set(DICOM_CMAKE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}/${DICOM_PGK_DIR})

if(NOT Module_vtkDICOM)
  # Libraries
  set(DICOM_LIBRARIES vtkDICOM)

  # The library dependencies
  set(VTK_TARGET_PREFIX "VTK::")
  if(VTK_VERSION VERSION_LESS 8.90)
    set(VTK_TARGET_PREFIX "vtk")
  endif()
  set(VTK_LIBS)
  # required libraries
  foreach(_lib CommonCore CommonMisc CommonDataModel ImagingCore IOCore IOImage)
    list(APPEND VTK_LIBS ${VTK_TARGET_PREFIX}${_lib})
  endforeach()
  # factory libraries (only needed if present)
  foreach(_lib IOMPIImage)
    list(FIND VTK_LIBRARIES ${VTK_TARGET_PREFIX}${_lib} _index)
    if(_index GREATER -1)
      list(APPEND VTK_LIBS ${VTK_TARGET_PREFIX}${_lib})
    endif()
  endforeach()
endif()

if(NOT Module_vtkDICOM AND VTK_VERSION VERSION_LESS 8.90)
  # External wrapping previous to VTK 9

  set(VTK_WRAP_INCLUDE_DIRS
    ${DICOM_INCLUDE_DIRS}
    ${VTK_WRAP_INCLUDE_DIRS})

  # For the python wrappers
  if(BUILD_PYTHON_WRAPPERS)
    if(TARGET vtkCommonCorePythonD OR
       TARGET vtkCommonKitPythonD OR
       TARGET vtkCommonPythonD)
      set(DICOM_PYTHON_LIBRARIES vtkDICOMPythonD)
    endif()
  endif()

  # For the tcl wrappers
  if(BUILD_TCL_WRAPPERS)
    find_package(TCL REQUIRED)
    set(DICOM_TCL_LIBRARIES vtkDICOMTCL)
  endif()

  # For the java wrappers
  if(BUILD_JAVA_WRAPPERS)
    find_package(Java REQUIRED)
    find_package(JNI REQUIRED)

    if(NOT VTK_JAVA_SOURCE_VERSION)
      set(VTK_JAVA_SOURCE_VERSION "1.6" CACHE STRING "javac source version")
      mark_as_advanced(VTK_JAVA_SOURCE_VERSION)
    endif()
    if(NOT VTK_JAVA_TARGET_VERSION)
      set(VTK_JAVA_TARGET_VERSION "1.6" CACHE STRING "javac target version")
      mark_as_advanced(VTK_JAVA_TARGET_VERSION)
    endif()

    if(APPLE)
      set(JAVAC_OPTIONS -J-Xmx512m)
    endif()
    if(NOT VTK_JAR_PATH)
      set(VTK_JAR_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    endif()
    find_file(VTK_JAVA_JAR NAMES vtk.jar vtk6.jar vtk7.jar vtk8.jar
      PATHS ${vtkWrappingJava_RUNTIME_LIBRARY_DIRS})
    if(NOT VTK_JAVA_JAR)
      message(FATAL_ERROR "VTK_JAVA_JAR must be set to the location of vtk.jar")
    endif()

    set(DICOM_JAVA_LIBRARIES vtkDICOMJava)
  endif()

endif() # NOT Module_vtkDICOM)

# Disable C and C++ deprecation warnings for MSVC 2005 and later
if(MSVC_VERSION EQUAL 1400 OR MSVC_VERSION GREATER 1400 OR MSVC10)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE
                  -D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-D_SCL_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()

if(NOT DICOM_EXTERNAL_BUILD OR NOT DEFINED VTK_MODULE_ENABLE_VTK_DICOM)
  # The main library, if not handled by the VTK 9 functions
  add_subdirectory(Source)
endif()

# Subdirectories
if(BUILD_PROGRAMS)
  add_subdirectory(DicomCli)
  add_subdirectory(Programs)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()

if(DICOM_EXTERNAL_BUILD OR NOT DEFINED VTK_MODULE_ENABLE_VTK_DICOM)

  if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(Testing)
  endif()

  # Install files
  install(FILES Copyright.txt
    DESTINATION ${DICOM_DATA_INSTALL_DEST})

endif()

if(NOT Module_vtkDICOM AND NOT DEFINED VTK_MODULE_ENABLE_VTK_DICOM)
  #---------------------------------------------------
  # Export information for other projects

  # Add all targets to the build-tree export set
  export(TARGETS ${DICOM_LIBRARIES}
    ${DICOM_PYTHON_LIBRARIES} ${DICOM_JAVA_LIBRARIES}
    FILE "${DICOM_BINARY_DIR}/DICOMTargets.cmake")

  # Export the package for use from the build-tree
  # (this registers the build-tree with a global CMake-registry)
  export(PACKAGE DICOM)

  # Create the DICOMConfig.cmake and DICOMConfigVersion.cmake files
  # ... for the build tree
  set(INCLUDE_DIRS_CONFIG ${DICOM_INCLUDE_DIRS})
  set(LIBRARY_DIRS_CONFIG "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
  configure_file(CMake/DICOMConfig.cmake.in
    "${DICOM_BINARY_DIR}/DICOMConfig.cmake" @ONLY)
  # ... for the install tree
  file(RELATIVE_PATH REL_INCLUDE_DIR "${DICOM_CMAKE_INSTALL_DEST}"
    "${DICOM_INCLUDE_INSTALL_DEST}")
  set(INCLUDE_DIRS_CONFIG "\${DICOM_PGK_DIR}/${REL_INCLUDE_DIR}")
  file(RELATIVE_PATH REL_LIBRARY_DIR "${DICOM_CMAKE_INSTALL_DEST}"
    "${DICOM_LIBRARY_INSTALL_DEST}")
  set(LIBRARY_DIRS_CONFIG "\${DICOM_PGK_DIR}/${REL_LIBRARY_DIR}")
  configure_file(CMake/DICOMConfig.cmake.in
    "${DICOM_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DICOMConfig.cmake" @ONLY)

  # ... for both
  configure_file(CMake/DICOMConfigVersion.cmake.in
    "${DICOM_BINARY_DIR}/DICOMConfigVersion.cmake" @ONLY)

  # Install the DICOMConfig.cmake and DICOMConfigVersion.cmake
  install(FILES
    "${DICOM_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DICOMConfig.cmake"
    "${DICOM_BINARY_DIR}/DICOMConfigVersion.cmake"
    DESTINATION "${DICOM_CMAKE_INSTALL_DEST}" COMPONENT Development)

  # Install the Use file in the build and install directories
  configure_file(${DICOM_SOURCE_DIR}/CMake/UseDICOM.cmake.in
    ${DICOM_BINARY_DIR}/UseDICOM.cmake COPYONLY IMMEDIATE)
  install(FILES
    "${DICOM_BINARY_DIR}/UseDICOM.cmake"
    DESTINATION "${DICOM_CMAKE_INSTALL_DEST}" COMPONENT Development)

  # Install the export set for use with the install-tree
  install(EXPORT DICOMTargets
    DESTINATION "${DICOM_CMAKE_INSTALL_DEST}" COMPONENT Development)
endif()
