# GDCM or DCMTK are required for reading compressed DICOM images
option(USE_ITK_GDCM "Use ITK's GDCM for image decompression" OFF)
option(USE_GDCM "Use GDCM for image decompression" OFF)
option(USE_DCMTK "Use DCMTK for image decompression" OFF)

# Check for sqlite3 for reading OsiriX databases
set(USE_SQLITE_DEFAULT OFF)
if(APPLE)
  set(USE_SQLITE_DEFAULT ON)
endif()
option(USE_SQLITE "Use SQLite for OsiriX databases" ${USE_SQLITE_DEFAULT})

# Configuration header
set(DICOM_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
set(DICOM_BUILD_TESTING ${BUILD_TESTING})
set(DICOM_USE_GDCM ${USE_GDCM})
set(DICOM_USE_DCMTK ${USE_DCMTK})
set(DICOM_USE_SQLITE ${USE_SQLITE})
if(VTK_VERSION VERSION_LESS 7.0)
  set(DICOM_OVERRIDE "")
  set(DICOM_DELETE "")
elseif(VTK_VERSION VERSION_LESS 7.1)
  set(DICOM_OVERRIDE " VTK_OVERRIDE")
  set(DICOM_DELETE "")
elseif(VTK_VERSION VERSION_LESS 8.90)
  set(DICOM_OVERRIDE " VTK_OVERRIDE")
  set(DICOM_DELETE " VTK_DELETE_FUNCTION")
else()
  set(DICOM_OVERRIDE " override")
  set(DICOM_DELETE " = delete")
endif()
configure_file(${DICOM_CMAKE_DIR}/vtkDICOMConfig.h.in
  "${CMAKE_CURRENT_BINARY_DIR}/vtkDICOMConfig.h" @ONLY)
configure_file(${DICOM_CMAKE_DIR}/vtkDICOMBuild.h.in
  "${CMAKE_CURRENT_BINARY_DIR}/vtkDICOMBuild.h" @ONLY)

# Include directories
include_directories(${DICOM_INCLUDE_DIRS})

# Create the main library
set(LIB_NAME vtkDICOM)

if(WIN32)
  set(REFCOUNT_SRC vtkDICOMReferenceCount.cxx)
else()
  set(REFCOUNT_HDR vtkDICOMReferenceCount.h)
endif()

# Sources in the current directory (library sources only!)
set(LIB_SRCS
  vtkDICOMMetaData.cxx
  vtkDICOMDictionary.cxx
  vtkDICOMFilePath.cxx
  vtkDICOMFile.cxx
  vtkDICOMFileDirectory.cxx
  vtkDICOMTag.cxx
  vtkDICOMTagPath.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMCharacterSet.cxx
  vtkDICOMCharacterSetTables.cxx
  vtkDICOMDataElement.cxx
  vtkDICOMDictHash.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMDictPrivate.cxx
  vtkDICOMDirectory.cxx
  vtkDICOMFileSorter.cxx
  vtkDICOMGenerator.cxx
  vtkDICOMImageCodec.cxx
  vtkDICOMSCGenerator.cxx
  vtkDICOMCTGenerator.cxx
  vtkDICOMMRGenerator.cxx
  vtkDICOMParser.cxx
  vtkDICOMCompiler.cxx
  vtkDICOMReader.cxx
  vtkDICOMSliceSorter.cxx
  vtkDICOMSequence.cxx
  vtkDICOMItem.cxx
  vtkDICOMSorter.cxx
  ${REFCOUNT_SRC}
  vtkDICOMUtilities.cxx
  vtkDICOMUtilitiesUIDTable.cxx
  vtkDICOMValue.cxx
  vtkDICOMWriter.cxx
  vtkDICOMAlgorithm.cxx
  vtkDICOMLookupTable.cxx
  vtkDICOMApplyPalette.cxx
  vtkDICOMApplyRescale.cxx
  vtkDICOMToRAS.cxx
  vtkDICOMCTRectifier.cxx
  vtkDICOMMetaDataAdapter.cxx
  vtkDICOMUIDGenerator.cxx
  vtkNIFTIHeader.cxx
  vtkNIFTIReader.cxx
  vtkNIFTIWriter.cxx
  vtkScancoCTReader.cxx
)

# Headers without a matching .cxx file are listed here
set(LIB_HDRS
  ${REFCOUNT_HDR}
  ${CMAKE_CURRENT_BINARY_DIR}/vtkDICOMConfig.h
  ${CMAKE_CURRENT_BINARY_DIR}/vtkDICOMModule.h
)

# Internal headers (not installed)
set(LIB_PRIVATE_HDRS
  vtkNIFTIPrivate.h
  ${CMAKE_CURRENT_BINARY_DIR}/vtkDICOMBuild.h
)

# Sources that are abstract
set(LIB_ABSTRACT
  vtkDICOMGenerator.cxx
)

# Sources that are not vtkObjects
set(LIB_SPECIAL
  vtkDICOMFile.cxx
  vtkDICOMFileDirectory.cxx
  vtkDICOMFilePath.cxx
  vtkDICOMTag.cxx
  vtkDICOMTagPath.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMCharacterSet.cxx
  vtkDICOMCharacterSetTables.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMDictHash.cxx
  vtkDICOMDictionary.cxx
  vtkDICOMDictPrivate.cxx
  vtkDICOMDataElement.cxx
  vtkDICOMImageCodec.cxx
  ${REFCOUNT_SRC}
  vtkDICOMSequence.cxx
  vtkDICOMItem.cxx
  vtkDICOMValue.cxx
  vtkDICOMMetaDataAdapter.cxx
  vtkDICOMUtilitiesUIDTable.cxx
)

set_source_files_properties(${LIB_HDRS} ${LIB_SPECIAL}
  PROPERTIES WRAP_EXCLUDE ON)
set_source_files_properties(${LIB_ABSTRACT}
  PROPERTIES ABSTRACT ON)
set_source_files_properties(${LIB_PRIVATE_HDRS}
  PROPERTIES SKIP_HEADER_INSTALL ON)

# Third party library dependencies

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

set(DCMTK_LIBS)
if(USE_DCMTK)
  find_package(DCMTK)
  if(NOT DCMTK_FOUND)
    message(FATAL_ERROR "DCMTK not found or incomplete.")
  endif()
  # DCMTK headers might require a specific version of C++
  find_file(_dcmtk_config_header "dcmtk/config/osconfig.h" NO_CACHE
    PATHS ${DCMTK_INCLUDE_DIRS})
  if(_dcmtk_config_header)
    file(READ ${_dcmtk_config_header} _dcmtk_config)
    set(_cxx_config_regex "#define HAVE_CXX([0-9][0-9]) 1")
    string(REGEX MATCHALL "${_cxx_config_regex}" _cxx_config_list "${_dcmtk_config}")
    if(_cxx_config_list)
      list(SORT _cxx_config_list)
      list(GET _cxx_config_list -1 _cxx_config)
      string(REGEX REPLACE "${_cxx_config_regex}" "\\1" _cxx_version "${_cxx_config}")
      if("${_cxx_version}" STRGREATER "${CMAKE_CXX_STANDARD}")
        set(CMAKE_CXX_STANDARD ${_cxx_version})
      endif()
    endif()
  endif()
  if(${DCMTK_charls_LIBRARY})
    set(DCMTK_LIBS ${DCMTK_LIBRARIES} ${DCMTK_charls_LIBRARY})
  else()
    set(DCMTK_LIBS ${DCMTK_LIBRARIES})
  endif()
  if(APPLE)
    list(APPEND DCMTK_LIBS iconv)
  endif()
  include_directories(${DCMTK_INCLUDE_DIRS})
endif()

set(SQLITE_LIBS)
if(USE_SQLITE)
  set(SQLITE_LIBS sqlite3)
endif()

# Create the library

if(DEFINED VTK_MODULE_ENABLE_VTK_DICOM)
  # When building as a module for VTK 8.90 or later
  set(LIB_SRC_HDRS)
  foreach(_src ${LIB_SRCS})
    get_filename_component(_base ${_src} NAME_WE)
    list(APPEND LIB_SRC_HDRS ${_base}.h)
  endforeach()
  vtk_module_add_module(VTK::DICOM
    SOURCES ${LIB_SRCS}
    HEADERS ${LIB_SRC_HDRS} ${LIB_HDRS}
    PRIVATE_HEADERS ${LIB_PRIVATE_HDRS})
  vtk_module_link(VTK::DICOM
    PRIVATE ${GDCM_LIBS} ${DCMTK_LIBS} ${SQLITE_LIBS})

elseif(Module_vtkDICOM)
  # When building as a remote module for older versions of VTK
  vtk_module_library(vtkDICOM ${LIB_SRCS} ${LIB_HDRS} ${LIB_PRIVATE_HDRS})
  target_link_libraries(${LIB_NAME}
    LINK_PRIVATE ${GDCM_LIBS} ${DCMTK_LIBS} ${SQLITE_LIBS})

else()
# The remainder of the file is for old, non-modular builds

configure_file(${DICOM_CMAKE_DIR}/vtkDICOMModule.h.in
  "${CMAKE_CURRENT_BINARY_DIR}/vtkDICOMModule.h" COPYONLY)

# Automatically find the header for each cxx file
foreach(arg ${LIB_SRCS})
  get_filename_component(src "${arg}" ABSOLUTE)
  string(REGEX REPLACE "\\.(cxx|c|mm|m)$" ".h" hdr "${src}")
  if("${hdr}" MATCHES "\\.h$" AND EXISTS "${hdr}")
    list(APPEND LIB_HDRS "${hdr}")
  endif()
endforeach()

# Create the hierarchy file
if(BUILD_PYTHON_WRAPPERS OR BUILD_TCL_WRAPPERS OR BUILD_JAVA_WRAPPERS)
  set_source_files_properties(${LIB_SPECIAL} PROPERTIES WRAP_SPECIAL ON)
  set(MODULE_HIERARCHY_NAME ${LIB_NAME}Hierarchy)
  # _LINK_DEPENDS is a variable suffix from the VTK module macros
  set(${LIB_NAME}_LINK_DEPENDS ${VTK_LIBS} ${ZLIB_LIBS})
  include(vtkWrapHierarchy)
  vtk_wrap_hierarchy(${LIB_NAME} ${CMAKE_CURRENT_BINARY_DIR} "${LIB_SRCS}")
  set(KIT_HIERARCHY_FILE ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.txt)
  set(LIB_HIERARCHY_STAMP ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_HIERARCHY_NAME}.stamp.txt)
endif()

# Set the library name suffix for VTK libraries
set(LIB_NAME_SUFFIX "-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}")
if(DEFINED VTK_CUSTOM_LIBRARY_SUFFIX)
  set(LIB_NAME_SUFFIX "${VTK_CUSTOM_LIBRARY_SUFFIX}")
endif()

# Create the library
add_library(${LIB_NAME} ${LIB_SRCS} ${LIB_HIERARCHY_STAMP})
set_target_properties(${LIB_NAME} PROPERTIES
  OUTPUT_NAME ${LIB_NAME}${LIB_NAME_SUFFIX})
set_target_properties(${LIB_NAME} PROPERTIES
  VERSION "${${PROJECT_NAME}_VERSION}"
  SOVERSION "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}")
if(BUILD_PYTHON_WRAPPERS OR BUILD_TCL_WRAPPERS OR BUILD_JAVA_WRAPPERS)
  set_target_properties(${LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
target_link_libraries(${LIB_NAME} LINK_PUBLIC ${VTK_LIBS})
target_link_libraries(${LIB_NAME} LINK_PRIVATE
  ${ZLIB_LIBS} ${GDCM_LIBS} ${DCMTK_LIBS} ${SQLITE_LIBS})

# Wrappers
if(BUILD_PYTHON_WRAPPERS)
  set(MODULE_PYTHON_NAME ${LIB_NAME}Python)
  set(${LIB_NAME}_WRAP_DEPENDS ${VTK_LIBS})
  include(vtkWrapPython)
  include_directories(${vtkPython_INCLUDE_DIRS})
  set(VTK_PYTHON_LIBRARIES ${vtkPython_LIBRARIES})
  set(LIB_PYTHON_LIBS vtkWrappingPythonCore)
  vtk_wrap_python3(${MODULE_PYTHON_NAME} LIB_PYTHON_SRCS "${LIB_SRCS}")
  if(DICOM_PYTHON_LIBRARIES)
    # do things the old way, with PythonD libraries
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
    set(LIB_PYTHON_NAME ${LIB_NAME}PythonD)
    set(LIB_PYTHON_OUTPUT_NAME ${LIB_NAME}Python${XY}D)
    set(LIB_PYTHON_OUTPUT_NAME ${LIB_PYTHON_OUTPUT_NAME}${LIB_NAME_SUFFIX})
    foreach(TMP_LIB ${VTK_LIBS})
      set(LIB_PYTHON_LIBS ${LIB_PYTHON_LIBS} ${TMP_LIB}PythonD)
    endforeach()
    add_library(${LIB_PYTHON_NAME} ${LIB_PYTHON_SRCS} ${LIB_PYTHON_EXTRA_SRCS})
    set_target_properties(${LIB_PYTHON_NAME} PROPERTIES
      POSITION_INDEPENDENT_CODE ON)
    set_target_properties(${LIB_PYTHON_NAME} PROPERTIES
      VERSION "${PROJECT_VERSION}"
      SOVERSION "${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}"
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
    if(KIT_PYTHON_DEPS)
      add_dependencies(${LIB_PYTHON_NAME} ${KIT_PYTHON_DEPS})
    endif()
    add_library(${MODULE_PYTHON_NAME} MODULE ${MODULE_PYTHON_NAME}Init.cxx)
    target_link_libraries(${MODULE_PYTHON_NAME} ${LIB_PYTHON_NAME})
  else()
    # do things the new way, without PythonD libraries
    add_library(${MODULE_PYTHON_NAME} MODULE ${MODULE_PYTHON_NAME}Init.cxx
      ${LIB_PYTHON_SRCS} ${LIB_PYTHON_EXTRA_SRCS})
    target_link_libraries(${MODULE_PYTHON_NAME} LINK_PRIVATE
      ${LIB_NAME} ${LIB_PYTHON_LIBS} ${VTK_PYTHON_LIBRARIES})
    if(KIT_PYTHON_DEPS)
      add_dependencies(${MODULE_PYTHON_NAME} ${KIT_PYTHON_DEPS})
    endif()
  endif()
  set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES PREFIX "")
  if(WIN32 AND NOT CYGWIN)
    set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES SUFFIX ".pyd")
  endif()
  set_target_properties(${MODULE_PYTHON_NAME} PROPERTIES NO_SONAME 1)
endif()

if(BUILD_TCL_WRAPPERS)
  set(LIB_TCL_NAME ${LIB_NAME}TCL)
  string(TOLOWER ${LIB_NAME} MODULE_TCL_NAME)
  set(LIB_TCL_OUTPUT_NAME ${LIB_TCL_NAME})
  set(LIB_TCL_OUTPUT_NAME ${LIB_TCL_NAME}${LIB_NAME_SUFFIX})
  set(LIB_TCL_LIBS)
  foreach(TMP_LIB ${VTK_LIBS})
    set(LIB_TCL_LIBS ${LIB_TCL_LIBS} ${TMP_LIB}TCL)
  endforeach()
  if(VTK_TCL_INCLUDE_DIR)
    include_directories("${VTK_TCL_INCLUDE_DIR}")
  endif()
  include(vtkWrapTcl)
  vtk_wrap_tcl3(${LIB_TCL_NAME} LIB_TCL_SRCS "${LIB_SRCS}" "")
  add_library(${LIB_TCL_NAME} ${LIB_TCL_SRCS} ${LIB_TCL_EXTRA_SRCS}
              ${LIB_HIERARCHY_STAMP})
  target_link_libraries(${LIB_TCL_NAME} LINK_PUBLIC
    ${LIB_NAME} ${LIB_TCL_LIBS})
  if(KIT_TCL_DEPS)
    add_dependencies(${LIB_TCL_NAME} ${KIT_TCL_DEPS})
  endif()
  set_target_properties(${LIB_TCL_NAME} PROPERTIES
    OUTPUT_NAME ${LIB_TCL_OUTPUT_NAME})
  # create the pkgIndex.tcl file
  if(CMAKE_CONFIGURATION_TYPES)
    foreach(config ${CMAKE_CONFIGURATION_TYPES})
      set(MODULE_TCL_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${config}")
      configure_file(${DICOM_CMAKE_DIR}/pkgIndex.tcl.in
        "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${config}/pkgIndex.tcl" @ONLY)
    endforeach()
  else()
    set(MODULE_TCL_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    configure_file(${DICOM_CMAKE_DIR}/pkgIndex.tcl.in
      "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgIndex.tcl" @ONLY)
  endif()
  set(MODULE_TCL_PATH ${DICOM_LIBRARY_INSTALL_DEST})
  configure_file(${DICOM_CMAKE_DIR}/pkgIndex.tcl.in
    "${CMAKE_CURRENT_BINARY_DIR}/pkgIndex.tcl" @ONLY)
endif()

if(BUILD_JAVA_WRAPPERS)
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
  include(vtkWrapJava)
  vtk_wrap_java3(${LIB_JAVA_NAME} LIB_JAVA_SRCS "${LIB_SRCS}")
  add_library(${LIB_JAVA_NAME} SHARED ${LIB_JAVA_SRCS} ${LIB_JAVA_EXTRA_SRCS})
  if(APPLE)
    set_target_properties(${LIB_JAVA_NAME} PROPERTIES SUFFIX ".jnilib")
  endif()
  set_target_properties(${LIB_JAVA_NAME} PROPERTIES NO_SONAME 1)
  target_link_libraries(${LIB_JAVA_NAME} ${LIB_NAME} ${LIB_JAVA_LIBS})
  add_dependencies(${LIB_JAVA_NAME} ${LIB_NAME})
  if(KIT_JAVA_DEPS)
    add_dependencies(${LIB_JAVA_NAME} ${KIT_JAVA_DEPS})
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
endif()

# Set the install rules for the library
install(TARGETS
  ${LIB_NAME} ${LIB_PYTHON_NAME} ${MODULE_PYTHON_NAME}
    ${LIB_TCL_NAME} ${LIB_JAVA_NAME}
  EXPORT DICOMTargets
  RUNTIME DESTINATION ${DICOM_RUNTIME_INSTALL_DEST} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${DICOM_LIBRARY_INSTALL_DEST} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${DICOM_ARCHIVE_INSTALL_DEST} COMPONENT Development)

if(BUILD_TCL_WRAPPERS)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pkgIndex.tcl
    DESTINATION ${DICOM_TCL_INSTALL_DEST})
endif()

if(BUILD_JAVA_WRAPPERS)
  install(FILES ${VTK_JAR_PATH}/vtkdicom.jar
    DESTINATION ${DICOM_JAVA_INSTALL_DEST})
endif()

install(FILES ${LIB_HDRS}
  DESTINATION ${DICOM_INCLUDE_INSTALL_DEST} COMPONENT Development)

endif()
