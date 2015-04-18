include_directories(${DICOM_INCLUDE_DIRS})

set(LIB_NAME dicomcli)

set(LIB_SRCS
  mainmacro.cxx
  readquery.cxx
)

add_library(${LIB_NAME} STATIC ${LIB_SRCS})
target_link_libraries(${LIB_NAME} vtkDICOM)
