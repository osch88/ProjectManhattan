cmake_minimum_required (VERSION 3.5.1)

set(BUILD_DIR_NAME "${CMAKE_SOURCE_DIR}/build")

#set the position independent code property on all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(socketcan STATIC src/socketcan.cpp)
add_library(hal SHARED src/hal_monitor.cpp)
add_library(writecan SHARED src/writecan.cpp)