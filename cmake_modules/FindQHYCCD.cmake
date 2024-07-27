# Find QHYCCD Library
#

include(FindPackageHandleStandardArgs)

find_path(QHYCCD_INCLUDE_DIR qhyccd.h 
  HINTS $ENV{QHYCCD_ROOT_DIR}
  PATH_SUFFIXES include include/qhyccd 
)
find_library(QHYCCD_LIBRARY qhyccd
  HINTS $ENV{QHYCCD_ROOT_DIR}
  PATH_SUFFIXES lib
)

find_package_handle_standard_args(QHYCCD DEFAULT_MSG
  QHYCCD_LIBRARY QHYCCD_INCLUDE_DIR
)

if(QHYCCD_FOUND)
  mark_as_advanced(QHYCCD_INCLUDE_DIR  QHYCCD_LIBRARY)
endif()

if(QHYCCD_FOUND AND NOT QHYCCD::QHYCCD)
  add_library(QHYCCD::QHYCCD SHARED IMPORTED)
  set_property(TARGET QHYCCD::QHYCCD PROPERTY IMPORTED_LOCATION ${QHYCCD_LIBRARY})
  target_include_directories(QHYCCD::QHYCCD INTERFACE ${QHYCCD_INCLUDE_DIR})
endif()
