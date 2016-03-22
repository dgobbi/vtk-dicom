# for CMake 3, add VERSION X.Y.Z to set the version here
project(DICOM)

# CMake version requirements
cmake_minimum_required(VERSION 2.8.7)

# When CMake 3.0.0 is required, remove this block (see CMP0042).
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

# Allow custom cmake overrides
set(DICOM_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
set(CMAKE_MODULE_PATH ${DICOM_CMAKE_DIR} ${CMAKE_MODULE_PATH})

# Use ctest for dashboard submissions
include(CTest)

# Project version
set(DICOM_MAJOR_VERSION 0)
set(DICOM_MINOR_VERSION 7)
set(DICOM_PATCH_VERSION 6)
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

if(Module_vtkDICOM) # We are being built as a VTK remote module

  message(STATUS "vtkDICOM: Building vtkDICOM as a Remote VTK Module")
  set(vtkDICOM_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)
  set(vtkDICOM_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Source)
  vtk_module_impl()

  # Clear VTK_LIBS, linking will be handled by modular build
  set(VTK_LIBS)

  # To set DICOM_USE_VTKZLIB in vtkDICOMConfig.h
  set(DICOM_USE_VTKZLIB ON)

  option(BUILD_DICOM_PROGRAMS "Build the vtkDICOM tools" ON)
  set(BUILD_PROGRAMS ${BUILD_DICOM_PROGRAMS})

else() # We are being built as a stand-alone package

  option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

  # Which parts of the package to build
  option(BUILD_TESTING "Build the tests" OFF)
  option(BUILD_PROGRAMS "Build some useful DICOM tools" ON)
  option(BUILD_EXAMPLES "Build the examples" OFF)

  find_package(VTK REQUIRED)
  message(STATUS "vtkDICOM: Building vtkDICOM stand-alone")
  include(${VTK_USE_FILE})
  if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" VERSION_LESS 5.8)
    message(FATAL_ERROR "VTK 5.8 or later is required.")
  endif()

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
    # VTK 6 doesn't set it, so search for vtkzlib directly
    list(FIND VTK_LIBRARIES vtkzlib TMP_INDEX)
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
endif()

# GDCM or DCMTK are required for reading compressed DICOM images
option(USE_ITK_GDCM "Use ITK's GDCM for image decompression" OFF)
option(USE_GDCM "Use GDCM for image decompression" OFF)
if(USE_ITK_GDCM)
  # To avoid conflicts, we might want to use ITK's GDCM
  find_package(ITK REQUIRED)
  if(ITK_FOUND)
    include(${ITK_USE_FILE})
    set(GDCM_LIBS gdcmMSFF gdcmIOD gdcmDSED gdcmDICT)
    set(GDCM_FOUND 1)
    set(USE_GDCM ON CACHE BOOL "Use GDCM for image decompression" FORCE)
  endif()
elseif(USE_GDCM)
  find_package(GDCM)
  if(NOT GDCM_DIR)
    message(FATAL_ERROR "Please set GDCM_DIR.")
  endif()
  if(GDCM_FOUND)
    include(${GDCM_USE_FILE})
    set(GDCM_LIBS gdcmMSFF gdcmIOD gdcmDSED gdcmDICT)
  endif()
endif()

option(USE_DCMTK "Use DCMTK for image decompression" OFF)
set(DCMTK_LIBS)
if(USE_DCMTK)
  find_package(DCMTK)
  if(NOT DCMTK_FOUND)
    message(FATAL_ERROR "DCMTK not found or incomplete.")
  endif()
  set(DCMTK_LIBS ${DCMTK_LIBRARIES} ${DCMTK_charls_LIBRARY})
  if(APPLE)
    list(APPEND DCMTK_LIBS iconv)
  endif()
  include_directories(${DCMTK_INCLUDE_DIRS})
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
  if("${VTK_MAJOR_VERSION}" GREATER 5)
    set(VTK_LIBS vtkCommonCore vtkCommonDataModel vtkImagingCore vtkIOImage vtkIOSQL)
    # If vtkIOMPIImage is present, it has factories for vtkIOImage
    list(FIND VTK_LIBRARIES vtkIOMPIImage TMP_INDEX)
    if(TMP_INDEX GREATER -1)
      set(VTK_LIBS ${VTK_LIBS} vtkIOMPIImage)
    endif()
  else()
    set(VTK_LIBS vtkCommon vtkFiltering vtkImaging vtkIO vtkInfovis) # VTK 5.x
  endif()

  set(VTK_WRAP_INCLUDE_DIRS
    ${DICOM_INCLUDE_DIRS}
    ${VTK_WRAP_INCLUDE_DIRS})

  # For the python wrappers
  if(BUILD_PYTHON_WRAPPERS)
    set(DICOM_PYTHON_LIBRARIES vtkDICOMPythonD)
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

    set(VTK_JAVA_SOURCE_VERSION "1.5" CACHE STRING "javac source version")
    set(VTK_JAVA_TARGET_VERSION "1.5" CACHE STRING "javac target version")
    mark_as_advanced(VTK_JAVA_SOURCE_VERSION)
    mark_as_advanced(VTK_JAVA_TARGET_VERSION)

    if(APPLE)
      set(JAVAC_OPTIONS -J-Xmx512m)
    endif()
    if(NOT VTK_JAR_PATH)
      set(VTK_JAR_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    endif()
    find_file(VTK_JAVA_JAR NAMES vtk.jar vtk6.jar vtk5.jar
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

# For use by subdirectories
set(KWSYS_LIBS vtksys)

# The main library
add_subdirectory(Source)

# Subdirectories
if(BUILD_PROGRAMS)
  add_subdirectory(DicomCli)
  add_subdirectory(Programs)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(Testing)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()

# Install files
install(FILES Copyright.txt
  DESTINATION ${DICOM_DATA_INSTALL_DEST})

if(NOT Module_vtkDICOM)
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
