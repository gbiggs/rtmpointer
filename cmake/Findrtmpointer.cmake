# Find rtmpointer.
#
# The following directories are searched:
# RTMPOINTER_ROOT (CMake variable)
# RTMPOINTER_ROOT (Environment variable)
#
# This sets the following variables:
# RTMPOINTER_FOUND - True if rtmpointer was found.
# RTMPOINTER_INCLUDE_DIRS - Directories containing the rtmpointer include files.
# RTMPOINTER_LIBRARIES - Libraries needed to use rtmpointer.
# RTMPOINTER_DEFINITIONS - Compiler flags for rtmpointer.
# RTMPOINTER_VERSION - The version of rtmpointer found.
# RTMPOINTER_VERSION_MAJOR - The major version of rtmpointer found.
# RTMPOINTER_VERSION_MINOR - The minor version of rtmpointer found.
# RTMPOINTER_VERSION_PATCH - The revision version of rtmpointer found.
# RTMPOINTER_VERSION_CAN - The candidate version of rtmpointer found.

find_package(OpenRTM 1 REQUIRED)

find_package(PkgConfig)
pkg_check_modules(PC_RTMPOINTER QUIET rtmpointer)

find_path(RTMPOINTER_INCLUDE_DIR rtmpointer/pointerportmgmt.h
    HINTS ${RTMPOINTER_ROOT}/include $ENV{RTMPOINTER_ROOT}/include
    ${PC_RTMPOINTER_INCLUDE_DIRS})
find_library(RTMPOINTER_LIBRARY rtmpointer
    HINTS ${RTMPOINTER_ROOT}/lib $ENV{RTMPOINTER_ROOT}/lib
    ${PC_RTMPOINTER_LIBRARY_DIRS})

set(RTMPOINTER_DEFINITIONS ${OPENRTM_DEFINITIONS})
set(RTMPOINTER_INCLUDE_DIRS ${RTMPOINTER_INCLUDE_DIR}
    ${OPENRTM_INCLUDE_DIRS})
set(RTMPOINTER_LIBRARIES ${RTMPOINTER_LIBRARY} ${OPENRTM_LIBRARIES})

message(STATUS "Version from pkgconfig: ${PC_RTMPOINTER_VERSION}")
set(RTMPOINTER_VERSION ${PC_RTMPOINTER_VERSION})
string(REGEX REPLACE "^([0-9]+).*" "\\1"
    RTMPOINTER_VERSION_MAJOR "${RTMPOINTER_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1"
    RTMPOINTER_VERSION_MINOR "${RTMPOINTER_VERSION}")
string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1"
    RTMPOINTER_VERSION_PATCH ${RTMPOINTER_VERSION})
string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1"
    RTMPOINTER_VERSION_CAN ${RTMPOINTER_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(rtmpointer
    REQUIRED_VARS RTMPOINTER_INCLUDE_DIR RTMPOINTER_LIBRARY
    VERSION_VAR ${RTMPOINTER_VERSION})

