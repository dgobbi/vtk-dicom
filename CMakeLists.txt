project(DICOM)

# CMake version requirements
cmake_minimum_required(VERSION 2.6.3)

# Eliminate policy warnings
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

# Allow custo cmake overrides
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Look for a VTK build directory
find_package(VTK)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
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

# Project version
set(DICOM_MAJOR_VERSION 0)
set(DICOM_MINOR_VERSION 3)
set(DICOM_BUILD_VERSION 5)
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
set(DICOM_USE_DCMTK ${USE_DCMTK})
configure_file(CMake/vtkDICOMConfig.h.in
  "${DICOM_BINARY_DIR}/vtkDICOMConfig.h" @ONLY)
configure_file(CMake/vtkDICOMBuild.h.in
  "${DICOM_BINARY_DIR}/vtkDICOMBuild.h" @ONLY)

# Include directories
set(DICOM_INCLUDE_DIRS "${DICOM_SOURCE_DIR}" "${DICOM_BINARY_DIR}")
include_directories(${DICOM_INCLUDE_DIRS})
set(VTK_WRAP_INCLUDE_DIRS ${DICOM_INCLUDE_DIRS} ${VTK_WRAP_INCLUDE_DIRS})

# Create the main library
set(LIB_NAME vtkDICOM)

# The library dependencies
if("${VTK_MAJOR_VERSION}" GREATER 5)
  set(VTK_LIBS vtkIOImage vtksys vtkzlib) # VTK 6.x
else()
  set(VTK_LIBS vtkIO vtksys vtkzlib) # VTK 5.x
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
  vtkDICOMTag.cxx
  vtkDICOMTagPath.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMDataElement.cxx
  vtkDICOMDictHash.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMGenerator.cxx
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
  vtkNIFTIHeader.cxx
  vtkNIFTIReader.cxx
  vtkNIFTIWriter.cxx
)

# Headers without a matching .cxx file are listed here
set(LIB_HDRS
  vtkDICOMModule.h
  ${REFCOUNT_HDR}
  vtkNIFTIHeaderPrivate.h
  ${DICOM_BINARY_DIR}/vtkDICOMBuild.h
  ${DICOM_BINARY_DIR}/vtkDICOMConfig.h
)

# Sources that are abstract
set(LIB_ABSTRACT
  vtkDICOMGenerator.cxx
)

# Sources that are not vtkObjects
set(LIB_SPECIAL
  vtkDICOMTag.cxx
  vtkDICOMTagPath.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMDictionary.cxx
  vtkDICOMDataElement.cxx
  ${REFCOUNT_SRC}
  vtkDICOMSequence.cxx
  vtkDICOMItem.cxx
  vtkDICOMUtilities.cxx
  vtkDICOMValue.cxx
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
    set(vtk-module ${LIB_NAME})
    set(MODULE_HIERARCHY_NAME ${LIB_NAME}Hierarchy)
    set(${LIB_NAME}_LINK_DEPENDS ${VTK_LIBS})
    include(${VTK_CMAKE_DIR}/vtkWrapHierarchy.cmake)
    vtk_wrap_hierarchy(${MODULE_HIERARCHY_NAME} ${DICOM_BINARY_DIR}
      "${LIB_SRCS}")
    set(KIT_HIERARCHY_FILE ${DICOM_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.txt)
    set(LIB_HIERARCHY_STAMP ${DICOM_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.stamp)
  endif()
endif()

# Create the library
add_library(${LIB_NAME} ${LIB_SRCS} ${LIB_HIERARCHY_STAMP})
target_link_libraries(${LIB_NAME} ${VTK_LIBS} ${GDCM_LIBS} ${DCMTK_LIBS})
set(DICOM_LIBRARIES ${LIB_NAME})

# Wrappers
if(BUILD_PYTHON_WRAPPERS)
  set(vtk-module ${LIB_NAME})
  set(MODULE_PYTHON_NAME ${LIB_NAME}Python)
  set(LIB_PYTHON_NAME ${LIB_NAME}PythonD)
  if("${VTK_MAJOR_VERSION}" GREATER 5)
    set(LIB_PYTHON_LIBS vtkCommonCorePythonD vtkIOImagePythonD)
  else()
    set(LIB_PYTHON_LIBS vtkCommonPythonD vtkIOPythonD)
  endif()

  if(VTK_PYTHON_INCLUDE_DIR)
    include_directories("${VTK_PYTHON_INCLUDE_DIR}")
  endif()
  include(${VTK_CMAKE_DIR}/vtkWrapPython.cmake)
  vtk_wrap_python3(${MODULE_PYTHON_NAME} LIB_PYTHON_SRCS "${LIB_SRCS}")
  add_library(${LIB_PYTHON_NAME} ${LIB_PYTHON_SRCS} ${LIB_PYTHON_EXTRA_SRCS})
  target_link_libraries(${LIB_PYTHON_NAME} ${LIB_NAME} ${LIB_PYTHON_LIBS})
  # On Win32 and Mac, link python library now, on UNIX, don't
  if(WIN32 OR APPLE)
    target_link_libraries(${LIB_PYTHON_NAME} ${VTK_PYTHON_LIBRARIES})
  endif()
  if(KIT_PYTHON_DEPS)
    add_dependencies(${LIB_PYTHON_NAME} ${KIT_PYTHON_DEPS})
  endif()
  add_library(${MODULE_PYTHON_NAME} MODULE ${MODULE_PYTHON_NAME}Init.cxx)
  set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES PREFIX "")
  if(WIN32 AND NOT CYGWIN)
    set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES SUFFIX ".pyd")
  endif()
  target_link_libraries(${MODULE_PYTHON_NAME} ${LIB_PYTHON_NAME})
  # On Win32 and Mac, link python library now, on UNIX, don't
  if(WIN32 OR APPLE)
    target_link_libraries(${MODULE_PYTHON_NAME} ${VTK_PYTHON_LIBRARIES})
  endif()
endif()

if(BUILD_JAVA_WRAPPERS)
  find_package(Java REQUIRED)
  find_package(JNI REQUIRED)

  set(vtk-module ${LIB_NAME})
  set(VTK_WRAP_JAVA3_INIT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  set(VTK_JAVA_HOME ${CMAKE_CURRENT_BINARY_DIR}/java/vtk)
  make_directory(${VTK_JAVA_HOME})
  set(LIB_JAVA_NAME ${LIB_NAME}Java)
  if("${VTK_MAJOR_VERSION}" GREATER 5)
    set(LIB_JAVA_LIBS vtkCommonCoreJava vtkIOImageJava)
  else()
    set(LIB_JAVA_LIBS vtkCommonJava vtkIOJava)
  endif()

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
  target_link_libraries(${LIB_JAVA_NAME} ${LIB_NAME} ${LIB_JAVA_LIBS})
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

  add_custom_target(${LIB_NAME}JavaJar ALL
    DEPENDS ${VTK_JAR_PATH}/vtkdicom.jar)
  add_custom_target(${LIB_NAME}JavaClasses ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt
    DEPENDS ${VTK_JAVA_DEPENDENCIES}
    COMMAND ${JAVA_COMPILE} ${JAVAC_OPTIONS} -source 1.5
      -classpath ${VTK_DIR}/java
      -sourcepath ${VTK_DIR}/java/vtk/
      -d ${CMAKE_CURRENT_BINARY_DIR}/java
      ${CMAKE_CURRENT_BINARY_DIR}/java/vtk/*.java
    COMMAND ${CMAKE_COMMAND}
      -E touch ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt
    COMMENT "Compiling Java Classes"
    )
  add_custom_command(
    COMMAND ${JAVA_ARCHIVE} -cvf  "${VTK_JAR_PATH}/vtkdicom.jar"
    -C ${CMAKE_CURRENT_BINARY_DIR}/java
    vtk
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/java/javac_stamp.txt ${JAVA_LIBRARIES}
    OUTPUT ${VTK_JAR_PATH}/vtkdicom.jar
    COMMENT "Java Archive"
    )
endif()

# Set the install rules for the library
install(TARGETS
  ${LIB_NAME} ${LIB_PYTHON_NAME} ${MODULE_PYTHON_NAME} ${LIB_JAVA_NAME}
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
