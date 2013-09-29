# - find DCMTK libraries and applications
#
#  DCMTK_INCLUDE_DIRS   - Directories to include to use DCMTK
#  DCMTK_LIBRARIES     - Files to link against to use DCMTK
#  DCMTK_FOUND         - If false, don't try to use DCMTK
#  DCMTK_DIR           - (optional) Source directory for DCMTK
#
# DCMTK_DIR can be used to make it simpler to find the various include
# directories and compiled libraries if you've just compiled it in the
# source tree. Just set it to the root of the tree where you extracted
# the source (default to /usr/include/dcmtk/)

#=============================================================================
# Copyright 2000-2009 Kitware, Inc., Insight Software Consortium.
# Copyright 2009-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
# Copyright 2010 Thomas Sondergaard <ts@medical-insight.com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
# Neither the names of Kitware, Inc., the Insight Software Consortium, nor the
# names of their contributors may be used to endorse or promote products
# derived from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#=============================================================================
#
# Written for VXL by Amitha Perera.
# Upgraded for GDCM by Mathieu Malaterre.
# Modified for EasyViz by Thomas Sondergaard.
# Upgraded for DCMTK 3.6 by David Gobbi
#

if(NOT DCMTK_SOURCE_DIR OR NOT DCMTK_BINARY_DIR)
  if(NOT DCMTK_DIR)
    set(DCMTK_DIR
      DCMTK_DIR-NOTFOUND
      CACHE
      PATH
      "Root of DCMTK source/build tree (optional).")
  endif()

  if(NOT DCMTK_SOURCE_DIR)
    set(DCMTK_SOURCE_DIR ${DCMTK_DIR})
  endif()

  if(NOT DCMTK_BINARY_DIR)
    set(DCMTK_BINARY_DIR ${DCMTK_DIR})
  endif()
endif()

foreach(lib
    charls
    dcmdata
    dcmdsig
    dcmimage
    dcmimgle
    dcmjpeg
    dcmjpls
    dcmnet
    dcmpstat
    dcmqrdb
    dcmsr
    dcmtls
    dcmwlm
    i2d
    libi2d
    ijg12
    ijg16
    ijg8
    oflog
    ofstd)

  if(WIN32)
    set(CONFIG_SUFFIXES Release Debug)
  endif()

  if(DCMTK_BINARY_DIR)
    find_library(DCMTK_${lib}_LIBRARY
      ${lib}
      PATHS
      ${DCMTK_BINARY_DIR}/${lib}/libsrc
      ${DCMTK_BINARY_DIR}/dcmdata/lib${lib}
      ${DCMTK_BINARY_DIR}/dcmdata/libi2d
      ${DCMTK_BINARY_DIR}/dcmsign/libsrc
      ${DCMTK_BINARY_DIR}/dcmjpeg/lib${lib}
      ${DCMTK_BINARY_DIR}/dcmjpls/lib${lib}
      ${DCMTK_BINARY_DIR}/${lib}
      ${DCMTK_BINARY_DIR}/lib
      PATH_SUFFIXES ${CONFIG_SUFFIXES}
      NO_DEFAULT_PATH)
  else()
    find_library(DCMTK_${lib}_LIBRARY
      ${lib})
  endif()

  mark_as_advanced(DCMTK_${lib}_LIBRARY)

  if(DCMTK_${lib}_LIBRARY)
    list(APPEND DCMTK_LIBRARIES ${DCMTK_${lib}_LIBRARY})
  endif()

endforeach()

set(DCMTK_config_TEST_HEADER osconfig.h)
set(DCMTK_dcmdata_TEST_HEADER dctypes.h)
set(DCMTK_dcmimage_TEST_HEADER dicoimg.h)
set(DCMTK_dcmimgle_TEST_HEADER dcmimage.h)
set(DCMTK_dcmjpeg_TEST_HEADER djdecode.h)
set(DCMTK_dcmjpls_TEST_HEADER djcodecd.h)
set(DCMTK_dcmnet_TEST_HEADER assoc.h)
set(DCMTK_dcmpstat_TEST_HEADER dcmpstat.h)
set(DCMTK_dcmqrdb_TEST_HEADER dcmqrdba.h)
set(DCMTK_dcmsign_TEST_HEADER sicert.h)
set(DCMTK_dcmsr_TEST_HEADER dsrtree.h)
set(DCMTK_dcmtls_TEST_HEADER tlslayer.h)
set(DCMTK_dcmwlm_TEST_HEADER wlds.h)
set(DCMTK_oflog_TEST_HEADER syslogap.h)
set(DCMTK_ofstd_TEST_HEADER ofstdinc.h)

foreach(dir
    config
    dcmdata
    dcmimage
    dcmimgle
    dcmjpeg
    dcmjpls
    dcmnet
    dcmpstat
    dcmqrdb
    dcmsign
    dcmsr
    dcmtls
    dcmwlm
    oflog
    ofstd)

  find_path(DCMTK_${dir}_INCLUDE_DIR
    dcmtk/${dir}/${DCMTK_${dir}_TEST_HEADER}
    PATHS
    ${DCMTK_BINARY_DIR}/${dir}/include
    ${DCMTK_BINARY_DIR}
    ${DCMTK_SOURCE_DIR}/${dir}/include
    ${DCMTK_SOURCE_DIR})

  mark_as_advanced(DCMTK_${dir}_INCLUDE_DIR)

  if(DCMTK_${dir}_INCLUDE_DIR)
    list(APPEND
      DCMTK_INCLUDE_DIRS
      ${DCMTK_${dir}_INCLUDE_DIR})
  endif()
endforeach()

if(WIN32)
  list(APPEND DCMTK_LIBRARIES netapi32 wsock32)
else()
  list(APPEND DCMTK_LIBRARIES z)
endif()

if(DCMTK_ofstd_INCLUDE_DIR)
  get_filename_component(DCMTK_dcmtk_INCLUDE_DIR
    ${DCMTK_ofstd_INCLUDE_DIR}
    PATH
    CACHE)
  list(APPEND DCMTK_INCLUDE_DIRS ${DCMTK_dcmtk_INCLUDE_DIR})
  mark_as_advanced(DCMTK_dcmtk_INCLUDE_DIR)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DCMTK DEFAULT_MSG
  DCMTK_config_INCLUDE_DIR
  DCMTK_ofstd_INCLUDE_DIR
  DCMTK_ofstd_LIBRARY
  DCMTK_dcmdata_INCLUDE_DIR
  DCMTK_dcmdata_LIBRARY
  DCMTK_dcmimgle_INCLUDE_DIR
  DCMTK_dcmimgle_LIBRARY)

# Compatibility: This variable is deprecated
set(DCMTK_INCLUDE_DIR ${DCMTK_INCLUDE_DIRS})

foreach(executable dcmdump dcmdjpeg dcmdrle)
  string(TOUPPER ${executable} EXECUTABLE)
  find_program(DCMTK_${EXECUTABLE}_EXECUTABLE ${executable}
               ${DCMTK_BINARY_DIR}/bin)
  mark_as_advanced(DCMTK_${EXECUTABLE}_EXECUTABLE)
endforeach()
