cmake_minimum_required(VERSION 3.10)

project(reo VERSION "0.1" DESCRIPTION "Engine emulator")

# .hpp files
include_directories(include)

set(SOURCES main.cpp src/engine.cpp)
set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)

add_executable(reo ${SOURCES})