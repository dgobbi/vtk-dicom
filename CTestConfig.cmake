set(CTEST_PROJECT_NAME "vtk-dicom")
set(CTEST_NIGHTLY_START_TIME "00:00:00 UTC")

if(NOT DEFINED CTEST_DROP_METHOD)
  SET(CTEST_DROP_METHOD "http")
endif()

if(CTEST_DROP_METHOD STREQUAL "http")
  set(CTEST_DROP_METHOD "http")
  set(CTEST_DROP_SITE "my.cdash.org")
  set(CTEST_DROP_LOCATION "/submit.php?project=vtk-dicom")
  set(CTEST_DROP_SITE_CDASH TRUE)
endif()
