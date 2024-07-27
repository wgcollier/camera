cmake_minimum_required(VERSION 3.28.2)

project(
   MY_QHYDEMO
   LANGUAGES CXX
   VERSION 1.0.0
)

#include(FetchContent)
#FetchContent_Declare(
#  usb-1
#  GIT_REPOSITORY https://github.com/libusb/libusb-cmake.git
#  GIT_TAG        cec1e49eec481a6333c218726ecaba8e4f447a07
#)
#FetchContent_MakeAvailable(usb-1)

list(
   APPEND
   CMAKE_MODULE_PATH
   ${PROJECT_SOURCE_DIR}/cmake_modules/
   /Users/wgcollie/Projects/opt/cmake_modules/
)

set(ENV{QHYCCD_ROOT_DIR} /home/bill/Projects/sdk_linux64_24.03.29/usr/local/)
message("QHYCCD_ROOT_DIR: ")

set(ENV{USB-1_ROOT_DIR} /home/bill/Projects/sdk_linux64_24.03.29/usr/local/)
message("QHYCCD_ROOT_DIR: ")

find_package(USB-1 REQUIRED)
find_package(QHYCCD REQUIRED)

add_subdirectory(src)

