cmake_minimum_required (VERSION 3.5.1)

set(BUILD_DIR_NAME "${CMAKE_SOURCE_DIR}/build")

include_directories(hal/include writecan/include socketcan/include ../app/inputhandler/include/ ../app/reo/include/)

#set the position independent code property on all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(socketcan STATIC socketcan/src/socketcan.cpp)
add_library(hal STATIC hal/src/hal_monitor.cpp)
#add_library(writecan STATIC writecan/src/writecan.cpp)
