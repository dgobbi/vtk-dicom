project(DICOM)

# CMake version requirements
cmake_minimum_required(VERSION 2.8)

if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

# Look for a VTK build directory
find_package(VTK)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
endif()

option(USE_GDCM "Use GDCM for image decompression" OFF)
if(USE_GDCM)
  find_package(GDCM)
  if(NOT GDCM_DIR)
    message(FATAL_ERROR "Please set GDCM_DIR.")
  endif()
  if(GDCM_FOUND)
    include(${GDCM_USE_FILE})
    add_definitions(-DVTK_DICOM_USE_GDCM)
    set(GDCM_LIBS gdcmMSFF)
  endif()
endif()

option(BUILD_TESTING "Build the tests" ON)
option(BUILD_EXAMPLES "Build the examples" ON)

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

add_library(vtkDICOM ${LIB_SRCS})
target_link_libraries(vtkDICOM vtkIO ${GDCM_LIBS} vtkzlib)

add_subdirectory(Programs)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(Testing)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()
