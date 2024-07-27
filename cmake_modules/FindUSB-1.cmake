# Find USB-1 Library
#

include(FindPackageHandleStandardArgs)

message(STATUS "SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
message(STATUS "SYSTEM_PREFIX_PATH=${CMAKE_SYSTEM_PREFIX_PATH}")
message(STATUS "LIBRARY_ARCHITECTURE=${CMAKE_LIBRARY_ARCHITECTURE}")

find_path(USB-1_INCLUDE_DIR libusb.h 
  # HINTS $ENV{USB-1_ROOT_DIR}
  NAMES libusb.h
  PATH_SUFFIXES "include" "libusb-1.0" 
)
find_library(USB-1_LIBRARY libusb
  # HINTS $ENV{USB-1_ROOT_DIR}
  NAMES usb-1.0
  PATH_SUFFIXES "lib" "lib64"
)

find_package_handle_standard_args(USB-1 DEFAULT_MSG
  USB-1_LIBRARY USB-1_INCLUDE_DIR
)

if(USB-1_FOUND)
  mark_as_advanced(USB-1_INCLUDE_DIR  USB-1_LIBRARY)
endif()

if(USB-1_FOUND AND NOT USB-1::USB-1)
  add_library(USB-1::USB-1 SHARED IMPORTED)
  set_property(TARGET USB-1::USB-1 PROPERTY IMPORTED_LOCATION ${USB-1_LIBRARY})
  target_include_directories(USB-1::USB-1 INTERFACE ${USB-1_INCLUDE_DIR})
endif()
