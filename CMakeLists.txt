project(DICOM)

# CMake version requirements
cmake_minimum_required(VERSION 2.6.3)

# Eliminate policy warnings
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

# Look for a VTK build directory
find_package(VTK)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
endif()

# GDCM is required for reading compressed DICOM images
option(USE_GDCM "Use GDCM for image decompression" OFF)
if(USE_GDCM)
  find_package(GDCM)
  if(NOT GDCM_DIR)
    message(FATAL_ERROR "Please set GDCM_DIR.")
  endif()
  if(GDCM_FOUND)
    include(${GDCM_USE_FILE})
    set(GDCM_LIBS gdcmMSFF)
  endif()
endif()

# Project version
set(DICOM_MAJOR_VERSION 0)
set(DICOM_MINOR_VERSION 1)
set(DICOM_BUILD_VERSION 0)
set(DICOM_SHORT_VERSION "${DICOM_MAJOR_VERSION}.${DICOM_MINOR_VERSION}")
set(DICOM_VERSION "${DICOM_SHORT_VERSION}.${DICOM_BUILD_VERSION}")

# Choose static or shared libraries.
option(BUILD_SHARED_LIBS "Build shared libraries." ON)

# Which parts of the package to build
option(BUILD_PROGRAMS "Build some useful DICOM tools" ON)
option(BUILD_TESTING "Build the tests" ON)
option(BUILD_EXAMPLES "Build the examples" ON)

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
  execute_process(COMMAND "cmd" " /c date /t" OUTPUT_VARIABLE DATE)
  string(REGEX REPLACE "[^0-9]*(..).*" "\\1" MONTH "${DATE}")
  set(MONTHS ""
    "Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul" "Aug" "Sep" "Oct" "Nov" "Dec")
  list(GET MONTHS "${MONTH}" MONTH)
  string(REGEX REPLACE "[^/]*/(..)/(....).*" "\\1 ${MONTH} \\2"
    DICOM_BUILD_DATE "${DATE}")
  execute_process(COMMAND "cmd" " /c echo %TIME%" OUTPUT_VARIABLE TIME)
  string(REGEX REPLACE "[^0-9]*(..:..:..).*" "\\1"
    DICOM_BUILD_TIME "${TIME}")
else()
  execute_process(COMMAND "date" "+%d %b %Y/%H:%M:%S"
    OUTPUT_VARIABLE DATE_TIME)
  string(REGEX REPLACE "([^/]*)/.*" "\\1"
    DICOM_BUILD_DATE "${DATE_TIME}")
  string(REGEX REPLACE "[^/]*/([0-9:]*).*" "\\1"
    DICOM_BUILD_TIME "${DATE_TIME}")
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

# Set up our target directory structure for "make install"
set(DICOM_BIN_DIR "/bin") # for executables and ".dll" libraries
set(DICOM_LIB_DIR "/lib") # for unix/linux/osx shared libraries
set(DICOM_ARC_DIR "/lib") # for static or ".lib" libraries
set(DICOM_INC_DIR "/include") # for header files
set(DICOM_DATA_DIR "/share/dicom-${DICOM_SHORT_VERSION}")
set(DICOM_CMAKE_DIR "/lib/dicom-${DICOM_SHORT_VERSION}/cmake")

# Set the full paths to the install tree
set(DICOM_RUNTIME_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_BIN_DIR})
set(DICOM_LIBRARY_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_LIB_DIR})
set(DICOM_ARCHIVE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_ARC_DIR})
set(DICOM_INCLUDE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_INC_DIR})
set(DICOM_DATA_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_DATA_DIR})
set(DICOM_CMAKE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_CMAKE_DIR})

# Configuration header
set(DICOM_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(DICOM_BUILD_TESTING ${BUILD_TESTING})
set(DICOM_USE_GDCM ${USE_GDCM})
configure_file(CMake/vtkDICOMConfig.h.in
  "${DICOM_BINARY_DIR}/vtkDICOMConfig.h" @ONLY)

# Include directories
set(DICOM_INCLUDE_DIRS "${DICOM_SOURCE_DIR}" "${DICOM_BINARY_DIR}")
include_directories(${DICOM_INCLUDE_DIRS})

# Create the main library
set(LIB_NAME vtkDICOM)

# Sources in the current directory (library sources only!)
set(LIB_SRCS
  vtkDICOMMetaData.cxx
  vtkDICOMDictionary.cxx
  vtkDICOMTag.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMDataElement.cxx
  vtkDICOMDictHash.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMParser.cxx
  vtkDICOMReader.cxx
  vtkDICOMSequence.cxx
  vtkDICOMItem.cxx
  vtkDICOMSorter.cxx
  vtkDICOMReferenceCount.cxx
  vtkDICOMValue.cxx
  vtkDICOMToRAS.cxx
  vtkNIFTIReader.cxx
  vtkNIFTIWriter.cxx
)

# Headers without a matching .cxx file are listed here
set(LIB_HDRS
  vtkDICOMModule.h
  vtkNIFTIHeader.h
  ${DICOM_BINARY_DIR}/vtkDICOMConfig.h
)

# Automatically find the header for each cxx file
foreach(arg ${LIB_SRCS})
  get_filename_component(src "${arg}" ABSOLUTE)
  string(REGEX REPLACE "\\.(cxx|c|mm|m)$" ".h" hdr "${src}")
  if("${hdr}" MATCHES "\\.h$" AND EXISTS "${hdr}")
    list(APPEND LIB_HDRS "${hdr}")
  endif()
endforeach()

# Create the libary
add_library(${LIB_NAME} ${LIB_SRCS})
target_link_libraries(${LIB_NAME} vtkIO ${GDCM_LIBS} vtkzlib)
set(DICOM_LIBRARIES ${LIB_NAME})

# Set the install rules for the library
install(TARGETS ${LIB_NAME}
  EXPORT DICOMTargets
  RUNTIME DESTINATION ${DICOM_RUNTIME_INSTALL_DEST} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${DICOM_LIBRARY_INSTALL_DEST} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${DICOM_ARCHIVE_INSTALL_DEST} COMPONENT Development)

install(FILES ${LIB_HDRS}
  DESTINATION ${DICOM_INCLUDE_INSTALL_DEST} COMPONENT Development)

install(FILES Copyright.txt
  DESTINATION ${DICOM_DATA_INSTALL_DEST})

# Subdirectories
if(BUILD_PROGRAMS)
  add_subdirectory(Programs)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(Testing)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()

#---------------------------------------------------
# Export information for other projects

# Add all targets to the build-tree export set
export(TARGETS ${DICOM_LIBRARIES}
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
set(INCLUDE_DIRS_CONFIG "\${DICOM_CMAKE_DIR}/${REL_INCLUDE_DIR}")
file(RELATIVE_PATH REL_LIBRARY_DIR "${DICOM_CMAKE_INSTALL_DEST}"
  "${DICOM_LIBRARY_INSTALL_DEST}")
set(LIBRARY_DIRS_CONFIG "\${DICOM_CMAKE_DIR}/${REL_LIBRARY_DIR}")
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
