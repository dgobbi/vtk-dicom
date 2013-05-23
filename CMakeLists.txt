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
endif(VTK_FOUND)

find_package(GDCM)
if(NOT GDCM_DIR)
  message(FATAL_ERROR "Please set GDCM_DIR.")
endif(NOT GDCM_DIR)
if(GDCM_FOUND)
  include(${GDCM_USE_FILE})
endif(GDCM_FOUND)

set(LIB_SRCS
  vtkDICOMMetaData.cxx
  vtkDICOMDictionary.cxx
  vtkDICOMTag.cxx
  vtkDICOMVR.cxx
  vtkDICOMVM.cxx
  vtkDICOMDataElement.cxx
  vtkDICOMDictEntry.cxx
  vtkDICOMParser.cxx
  vtkDICOMReader.cxx
  vtkDICOMSequence.cxx
  vtkDICOMItem.cxx
  vtkDICOMSorter.cxx
  vtkDICOMReferenceCount.cxx
  vtkDICOMValue.cxx
  vtkNIFTIReader.cxx
  vtkNIFTIWriter.cxx
)

add_definitions(-DVTK_DICOM_USE_GDCM)

add_library(vtkDICOM ${LIB_SRCS})
target_link_libraries(vtkDICOM vtkIO gdcmMSFF vtkzlib)

add_executable(TestDICOMParser TestDICOMParser.cxx)
target_link_libraries(TestDICOMParser vtkDICOM)

add_executable(TestDICOMMetaData TestDICOMMetaData.cxx)
target_link_libraries(TestDICOMMetaData vtkDICOM)

add_executable(TestDICOMVR TestDICOMVR.cxx)
target_link_libraries(TestDICOMVR vtkDICOM)

add_executable(TestDICOMValue TestDICOMValue.cxx)
target_link_libraries(TestDICOMValue vtkDICOM)

add_executable(TestDICOMSequence TestDICOMSequence.cxx)
target_link_libraries(TestDICOMSequence vtkDICOM)

add_executable(TestDICOMSorter TestDICOMSorter.cxx)
target_link_libraries(TestDICOMSorter vtkDICOM)

add_executable(TestDICOMReader TestDICOMReader.cxx)
target_link_libraries(TestDICOMReader vtkDICOM)

add_executable(TestDICOMDisplay TestDICOMDisplay.cxx)
target_link_libraries(TestDICOMDisplay vtkDICOM vtkRendering)

add_executable(TestNIFTIDisplay TestNIFTIDisplay.cxx)
target_link_libraries(TestNIFTIDisplay vtkDICOM vtkRendering)
