project(DICOM)

# CMake version requirements
cmake_minimum_required(VERSION 2.8.7)

# Use LINK_INTERFACE_LIBRARIES instead of INTERFACE_LINK_LIBRARIES
#if(POLICY CMP0022)
#  cmake_policy(SET CMP0022 OLD)
#endif()

# When CMake 3.0.0 is required, remove this block (see CMP0042).
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH 0)
endif()

# Allow custom cmake overrides
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Use ctest for dashboard submissions
include(CTest)

# Look for a VTK build directory
find_package(VTK REQUIRED)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
  if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" VERSION_LESS 5.8)
    message(FATAL_ERROR "VTK 5.8 or later is required.")
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
endif()

# Look for zlib
if(NOT DICOM_USE_VTKZLIB)
  find_package(ZLIB REQUIRED)
  if(ZLIB_FOUND)
    set(ZLIB_LIBS ${ZLIB_LIBRARIES})
    include_directories("${ZLIB_INCLUDE_DIR}")
  endif()
endif()

# GDCM or DCMTK are required for reading compressed DICOM images
option(USE_GDCM "Use GDCM for image decompression" OFF)
if(USE_GDCM)
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
  set(DCMTK_LIBS ${DCMTK_LIBRARIES})
  include_directories(${DCMTK_INCLUDE_DIRS})
endif()

option(REMOVE_DEPRECATED_METHODS "Remove deprecated methods from source." ON)

# Project version
set(DICOM_MAJOR_VERSION 0)
set(DICOM_MINOR_VERSION 5)
set(DICOM_BUILD_VERSION 6)
set(DICOM_SHORT_VERSION "${DICOM_MAJOR_VERSION}.${DICOM_MINOR_VERSION}")
set(DICOM_VERSION "${DICOM_SHORT_VERSION}.${DICOM_BUILD_VERSION}")

# Choose static or shared libraries.
option(BUILD_SHARED_LIBS "Build shared libraries." OFF)

# Which parts of the package to build
option(BUILD_PROGRAMS "Build some useful DICOM tools" ON)
option(BUILD_TESTING "Build the tests" ON)
option(BUILD_EXAMPLES "Build the examples" ON)

if(VTK_WRAP_PYTHON)
  option(BUILD_PYTHON_WRAPPERS "Build python wrappers" ON)
else()
  unset(BUILD_PYTHON_WRAPPERS CACHE)
endif()

if(VTK_WRAP_JAVA)
  option(BUILD_JAVA_WRAPPERS "Build java wrappers" OFF)
else()
  unset(BUILD_JAVA_WRAPPERS CACHE)
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
if(NOT DICOM_LIB_DIR)
  set(DICOM_LIB_DIR "/lib") # for unix/linux/osx shared libraries
endif()
if(NOT DICOM_ARC_DIR)
  set(DICOM_ARC_DIR "${DICOM_LIB_DIR}") # for static or ".lib" libraries
endif()
if(NOT DICOM_INC_DIR)
  set(DICOM_INC_DIR "/include") # for header files
endif()
if(NOT DICOM_JAVA_DIR)
  set(DICOM_JAVA_DIR "/share/java")
endif()
if(NOT DICOM_DATA_DIR)
  set(DICOM_DATA_DIR "/share/dicom-${DICOM_SHORT_VERSION}")
endif()
if(NOT DICOM_CMAKE_DIR)
  set(DICOM_CMAKE_DIR "${DICOM_LIB_DIR}/dicom-${DICOM_SHORT_VERSION}/cmake")
endif()

# Set the full paths to the install tree
set(DICOM_RUNTIME_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_BIN_DIR})
set(DICOM_LIBRARY_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_LIB_DIR})
set(DICOM_ARCHIVE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_ARC_DIR})
set(DICOM_INCLUDE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_INC_DIR})
set(DICOM_JAVA_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_JAVA_DIR})
set(DICOM_DATA_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_DATA_DIR})
set(DICOM_CMAKE_INSTALL_DEST ${CMAKE_INSTALL_PREFIX}${DICOM_CMAKE_DIR})

# Configuration header
set(DICOM_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(DICOM_BUILD_TESTING ${BUILD_TESTING})
set(DICOM_USE_GDCM ${USE_GDCM})
set(DICOM_USE_DCMTK ${USE_DCMTK})
configure_file(CMake/vtkDICOMConfig.h.in
  "${DICOM_BINARY_DIR}/vtkDICOMConfig.h" @ONLY)
configure_file(CMake/vtkDICOMBuild.h.in
  "${DICOM_BINARY_DIR}/vtkDICOMBuild.h" @ONLY)

# Include directories
set(DICOM_INCLUDE_DIRS "${DICOM_SOURCE_DIR}" "${DICOM_BINARY_DIR}")
include_directories(${DICOM_INCLUDE_DIRS})
set(VTK_WRAP_INCLUDE_DIRS ${DICOM_INCLUDE_DIRS} ${VTK_WRAP_INCLUDE_DIRS})

# Disable C and C++ deprecation warnings for MSVC 2005 and later
if(MSVC_VERSION EQUAL 1400 OR MSVC_VERSION GREATER 1400 OR MSVC10)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE
                  -D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-D_SCL_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()

# Create the main library
set(LIB_NAME vtkDICOM)

# The library dependencies
set(KWSYS_LIBS vtksys)
if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_LIBS vtkCommonCore vtkCommonDataModel vtkImagingCore vtkIOImage)
  # If vtkIOMPIImage is present, it has factories for vtkIOImage
  list(FIND VTK_LIBRARIES vtkIOMPIImage TMP_INDEX)
  if(TMP_INDEX GREATER -1)
    set(VTK_LIBS ${VTK_LIBS} vtkIOMPIImage)
  endif()
else()
  set(VTK_LIBS vtkCommon vtkFiltering vtkImaging vtkIO) # VTK 5.x
endif()

if(WIN32)
  set(REFCOUNT_SRC vtkDICOMReferenceCount.cxx)
else()
  set(REFCOUNT_HDR vtkDICOMReferenceCount.h)
endif()

# Sources in the current directory (library sources only!)
set(LIB_SRCS
  vtkDICOMMetaData.cxx
  vtkDICOMDictionary.cxx
  vtkDICOMFile.cxx
  vtkDICOMTag.cxx
  vtkDICOMTagPath.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMCharacterSet.cxx
  vtkDICOMDataElement.cxx
  vtkDICOMDictHash.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMDictPrivate.cxx
  vtkDICOMDirectory.cxx
  vtkDICOMGenerator.cxx
  vtkDICOMImageCodec.cxx
  vtkDICOMSCGenerator.cxx
  vtkDICOMCTGenerator.cxx
  vtkDICOMMRGenerator.cxx
  vtkDICOMParser.cxx
  vtkDICOMCompiler.cxx
  vtkDICOMReader.cxx
  vtkDICOMSequence.cxx
  vtkDICOMItem.cxx
  vtkDICOMSorter.cxx
  ${REFCOUNT_SRC}
  vtkDICOMUtilities.cxx
  vtkDICOMValue.cxx
  vtkDICOMWriter.cxx
  vtkDICOMToRAS.cxx
  vtkDICOMCTRectifier.cxx
  vtkDICOMMetaDataAdapter.cxx
  vtkNIFTIHeader.cxx
  vtkNIFTIReader.cxx
  vtkNIFTIWriter.cxx
)

# Headers without a matching .cxx file are listed here
set(LIB_HDRS
  vtkDICOMModule.h
  ${REFCOUNT_HDR}
  vtkNIFTIPrivate.h
  ${DICOM_BINARY_DIR}/vtkDICOMConfig.h
)

# Internal headers (not installed)
set(LIB_INTERNAL_HDRS
  ${DICOM_BINARY_DIR}/vtkDICOMBuild.h
)

# Sources that are abstract
set(LIB_ABSTRACT
  vtkDICOMGenerator.cxx
)

# Sources that are not vtkObjects
set(LIB_SPECIAL
  vtkDICOMFile.cxx
  vtkDICOMTag.cxx
  vtkDICOMTagPath.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMCharacterSet.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMDictionary.cxx
  vtkDICOMDataElement.cxx
  vtkDICOMImageCodec.cxx
  ${REFCOUNT_SRC}
  vtkDICOMSequence.cxx
  vtkDICOMItem.cxx
  vtkDICOMUtilities.cxx
  vtkDICOMValue.cxx
  vtkDICOMMetaDataAdapter.cxx
)

set_source_files_properties(${LIB_SPECIAL} PROPERTIES WRAP_EXCLUDE ON)
set_source_files_properties(${LIB_ABSTRACT} PROPERTIES ABSTRACT ON)

# Automatically find the header for each cxx file
foreach(arg ${LIB_SRCS})
  get_filename_component(src "${arg}" ABSOLUTE)
  string(REGEX REPLACE "\\.(cxx|c|mm|m)$" ".h" hdr "${src}")
  if("${hdr}" MATCHES "\\.h$" AND EXISTS "${hdr}")
    list(APPEND LIB_HDRS "${hdr}")
  endif()
endforeach()

# Create the hierarchy file
if("${VTK_MAJOR_VERSION}" GREATER 5)
  if(BUILD_PYTHON_WRAPPERS OR BUILD_JAVA_WRAPPERS)
    set_source_files_properties(${LIB_SPECIAL} PROPERTIES WRAP_SPECIAL ON)
    set(MODULE_HIERARCHY_NAME ${LIB_NAME}Hierarchy)
    # The VTK 6 wrapping macros require vtk-module to be set
    set(vtk-module ${LIB_NAME})
    # _LINK_DEPENDS is a variable suffix from the VTK 6 module macros 
    set(${vtk-module}_LINK_DEPENDS ${VTK_LIBS} ${KWSYS_LIBS} ${ZLIB_LIBS})
    include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/vtkWrapHierarchy.cmake)
    vtk_wrap_hierarchy(${MODULE_HIERARCHY_NAME} ${DICOM_BINARY_DIR}
      "${LIB_SRCS}")
    set(KIT_HIERARCHY_FILE ${DICOM_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.txt)
    set(LIB_HIERARCHY_STAMP ${DICOM_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.stamp)
  endif()
endif()

# Set the library name suffix for VTK 6 libraries
set(LIB_NAME_SUFFIX "-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}")
if(DEFINED VTK_CUSTOM_LIBRARY_SUFFIX)
  set(LIB_NAME_SUFFIX "${VTK_CUSTOM_LIBRARY_SUFFIX}")
endif()

# Create the library
add_library(${LIB_NAME} ${LIB_SRCS} ${LIB_HIERARCHY_STAMP})
if("${VTK_MAJOR_VERSION}" GREATER 5)
  set_target_properties(${LIB_NAME} PROPERTIES
    OUTPUT_NAME ${LIB_NAME}${LIB_NAME_SUFFIX})
endif()
set_target_properties(${LIB_NAME} PROPERTIES
  VERSION "${DICOM_VERSION}" SOVERSION "${DICOM_SHORT_VERSION}")
if(BUILD_PYTHON_WRAPPERS OR BUILD_JAVA_WRAPPERS AND
   NOT (CMAKE_VERSION VERSION_LESS 2.8))
  set_target_properties(${LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
target_link_libraries(${LIB_NAME} LINK_PUBLIC ${VTK_LIBS})
target_link_libraries(${LIB_NAME} LINK_PRIVATE
  ${KWSYS_LIBS} ${ZLIB_LIBS} ${GDCM_LIBS} ${DCMTK_LIBS})
set(DICOM_LIBRARIES ${LIB_NAME})

# Wrappers
if(BUILD_PYTHON_WRAPPERS)
  set(vtk-module ${LIB_NAME})
  set(XY) # Get python version, e.g. 27 for python 2.7
  if(vtkPython_LIBRARIES)
    list(GET vtkPython_LIBRARIES 0 TMP_LIB_NAME)
    get_filename_component(TMP_NAME "${TMP_LIB_NAME}" NAME)
    string(REGEX REPLACE "^[^0-9]*([0-9])\\.*([0-9]).*$" "\\1\\2"
      XY "${TMP_NAME}")
    if(NOT XY)
      set(XY)
    endif()
  endif()
  set(MODULE_PYTHON_NAME ${LIB_NAME}Python)
  set(LIB_PYTHON_NAME ${LIB_NAME}PythonD)
  set(LIB_PYTHON_OUTPUT_NAME ${LIB_NAME}Python${XY}D)
  if("${VTK_MAJOR_VERSION}" GREATER 5)
    set(LIB_PYTHON_OUTPUT_NAME ${LIB_PYTHON_OUTPUT_NAME}${LIB_NAME_SUFFIX})
  endif()
  set(LIB_PYTHON_LIBS vtkPythonCore)
  if("${VTK_MAJOR_VERSION}" GREATER 5)
    set(LIB_PYTHON_LIBS vtkWrappingPythonCore)
  endif()
  foreach(TMP_LIB ${VTK_LIBS})
    set(LIB_PYTHON_LIBS ${LIB_PYTHON_LIBS} ${TMP_LIB}PythonD)
  endforeach()

  if(VTK_PYTHON_INCLUDE_DIR)
    include_directories("${VTK_PYTHON_INCLUDE_DIR}")
  endif()
  # Tell vtkWrapPython to locate the python libraries for us.
  set(VTK_WRAP_PYTHON_FIND_LIBS ON)
  include(${VTK_CMAKE_DIR}/vtkWrapPython.cmake)
  vtk_wrap_python3(${MODULE_PYTHON_NAME} LIB_PYTHON_SRCS "${LIB_SRCS}")
  add_library(${LIB_PYTHON_NAME} ${LIB_PYTHON_SRCS} ${LIB_PYTHON_EXTRA_SRCS})
  if(NOT (CMAKE_VERSION VERSION_LESS 2.8))
    set_target_properties(${LIB_PYTHON_NAME} PROPERTIES
      POSITION_INDEPENDENT_CODE ON)
  endif()
  set_target_properties(${LIB_PYTHON_NAME} PROPERTIES
    VERSION "${DICOM_VERSION}" SOVERSION "${DICOM_SHORT_VERSION}"
    OUTPUT_NAME "${LIB_PYTHON_OUTPUT_NAME}")
  target_link_libraries(${LIB_PYTHON_NAME} LINK_PUBLIC
    ${LIB_NAME} ${LIB_PYTHON_LIBS})
  # On Win32 and Mac, link python library non-private
  if(WIN32 OR APPLE)
    target_link_libraries(${LIB_PYTHON_NAME} LINK_PUBLIC
      ${VTK_PYTHON_LIBRARIES})
  else()
    target_link_libraries(${LIB_PYTHON_NAME} LINK_PRIVATE
      ${VTK_PYTHON_LIBRARIES})
  endif()
  if(USE_DCMTK AND DCMTK_charls_LIBRARY)
    target_link_libraries(${LIB_PYTHON_NAME} LINK_PRIVATE
      ${DCMTK_charls_LIBRARY})
  endif()
  if(KIT_PYTHON_DEPS)
    add_dependencies(${LIB_PYTHON_NAME} ${KIT_PYTHON_DEPS})
  endif()
  add_library(${MODULE_PYTHON_NAME} MODULE ${MODULE_PYTHON_NAME}Init.cxx)
  set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES PREFIX "")
  if(WIN32 AND NOT CYGWIN)
    set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES SUFFIX ".pyd")
  endif()
  if(CMAKE_VERSION VERSION_GREATER 2.8.8)
    set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES NO_SONAME 1)
  endif()
  target_link_libraries(${MODULE_PYTHON_NAME} ${LIB_PYTHON_NAME})
  set(DICOM_PYTHON_LIBRARIES ${LIB_PYTHON_NAME})
endif()

if(BUILD_JAVA_WRAPPERS)
  find_package(Java REQUIRED)
  find_package(JNI REQUIRED)

  set(VTK_JAVA_SOURCE_VERSION "1.5" CACHE STRING "javac source version")
  set(VTK_JAVA_TARGET_VERSION "1.5" CACHE STRING "javac target version")
  mark_as_advanced(VTK_JAVA_SOURCE_VERSION)
  mark_as_advanced(VTK_JAVA_TARGET_VERSION)

  set(vtk-module ${LIB_NAME})
  set(VTK_WRAP_JAVA3_INIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  set(VTK_JAVA_HOME ${CMAKE_CURRENT_BINARY_DIR}/java/vtk)
  set(VTK_JAVA_MANIFEST ${CMAKE_CURRENT_BINARY_DIR}/java/manifest.txt)
  make_directory(${VTK_JAVA_HOME})
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/javajar/vtk)
  set(LIB_JAVA_NAME ${LIB_NAME}Java)
  set(LIB_JAVA_LIBS)
  foreach(TMP_LIB ${VTK_LIBS})
    set(LIB_JAVA_LIBS ${LIB_JAVA_LIBS} ${TMP_LIB}Java)
  endforeach()

  if(VTK_JAVA_INCLUDE_DIR)
    include_directories("${VTK_JAVA_INCLUDE_DIR}")
  else()
    include_directories("${JAVA_INCLUDE_PATH}" "${JAVA_INCLUDE_PATH2}")
  endif()
  include(${VTK_CMAKE_DIR}/vtkWrapJava.cmake)
  vtk_wrap_java3(${LIB_JAVA_NAME} LIB_JAVA_SRCS "${LIB_SRCS}")
  add_library(${LIB_JAVA_NAME} SHARED ${LIB_JAVA_SRCS} ${LIB_JAVA_EXTRA_SRCS})
  if(APPLE)
    set_target_properties(${LIB_JAVA_NAME} PROPERTIES SUFFIX ".jnilib")
  endif()
  if(CMAKE_VERSION VERSION_GREATER 2.8.8)
    set_target_properties(${LIB_JAVA_NAME} PROPERTIES NO_SONAME 1)
  endif()
  target_link_libraries(${LIB_JAVA_NAME} ${LIB_NAME} ${LIB_JAVA_LIBS})
  if(USE_DCMTK AND DCMTK_charls_LIBRARY)
    target_link_libraries(${LIB_JAVA_NAME} ${DCMTK_charls_LIBRARY})
  endif()
  add_dependencies(${LIB_JAVA_NAME} ${LIB_NAME})
  if(KIT_JAVA_DEPS)
    add_dependencies(${LIB_JAVA_NAME} ${KIT_JAVA_DEPS})
  endif()

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

  set(_sep ":")
  if(WIN32)
    set(_sep "\\;")
  endif()

  add_custom_target(${LIB_NAME}JavaJar ALL
    DEPENDS ${VTK_JAR_PATH}/vtkdicom.jar)
  add_custom_target(${LIB_NAME}JavaClasses ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt
    DEPENDS ${VTK_JAVA_DEPENDENCIES}
    COMMAND ${JAVA_COMPILE} ${JAVAC_OPTIONS}
      -source ${VTK_JAVA_SOURCE_VERSION}
      -target ${VTK_JAVA_TARGET_VERSION}
      -classpath ${VTK_JAVA_JAR}${_sep}${VTK_DIR}/java
      -sourcepath ${VTK_DIR}/java/vtk/
      -d ${CMAKE_CURRENT_BINARY_DIR}/javajar
      ${CMAKE_CURRENT_BINARY_DIR}/java/vtk/*.java
    COMMAND ${CMAKE_COMMAND}
      -E touch ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt
    COMMENT "Compiling Java Classes"
    )
  file(WRITE ${VTK_JAVA_MANIFEST} "Class-Path: vtk.jar\n")
  add_custom_command(
    COMMAND ${JAVA_ARCHIVE} -cvfm
      "${VTK_JAR_PATH}/vtkdicom.jar"
      ${VTK_JAVA_MANIFEST}
      -C ${CMAKE_CURRENT_BINARY_DIR}/javajar
      vtk
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt ${JAVA_LIBRARIES}
    OUTPUT ${VTK_JAR_PATH}/vtkdicom.jar
    COMMENT "Java Archive"
    )
  set(DICOM_JAVA_LIBRARIES ${LIB_JAVA_NAME})
endif()

# Set the install rules for the library
install(TARGETS
  ${LIB_NAME} ${LIB_PYTHON_NAME} ${MODULE_PYTHON_NAME} ${LIB_JAVA_NAME}
  EXPORT DICOMTargets
  RUNTIME DESTINATION ${DICOM_RUNTIME_INSTALL_DEST} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${DICOM_LIBRARY_INSTALL_DEST} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${DICOM_ARCHIVE_INSTALL_DEST} COMPONENT Development)

if(BUILD_JAVA_WRAPPERS)
  install(FILES ${VTK_JAR_PATH}/vtkdicom.jar
    DESTINATION ${DICOM_JAVA_INSTALL_DEST})
endif()

install(FILES ${LIB_HDRS}
  DESTINATION ${DICOM_INCLUDE_INSTALL_DEST} COMPONENT Development)

install(FILES Copyright.txt
  DESTINATION ${DICOM_DATA_INSTALL_DEST})

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
