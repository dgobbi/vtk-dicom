if(POLICY CMP0063)
  cmake_policy(SET CMP0063 NEW)
endif()

include_directories(${DICOM_INCLUDE_DIRS})

set(LIB_NAME dicomcli)

if(WIN32)
  set(MAINMACRO_SRC mainmacro.cxx)
else()
  set(MAINMACRO_SRC)
endif()

set(LIB_SRCS
  ${MAINMACRO_SRC}
  readquery.cxx
  progress.cxx
  vtkConsoleOutputWindow.cxx
)

add_library(${LIB_NAME} STATIC ${LIB_SRCS})
target_link_libraries(${LIB_NAME} ${VTK_DICOM_LINK_TARGET})
