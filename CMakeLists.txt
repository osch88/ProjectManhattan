cmake_minimum_required(VERSION 3.0.0)
project(Emulator VERSION 0.1.0)

set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
set(SOURCES_EMU ./app/reo/main.cpp ./app/reo/src/engine.cpp ./lib/hal_monitor.cpp ./lib/socketcan.cpp)
set(SOURCES_INPUTHANDLER ./app/inputhandler/main.cpp ./app/inputhandler/src/keyboard_input.cpp ./lib/writecan.cpp ./lib/socketcan.cpp)

include_directories(./lib) #.hpp
include_directories(./app/reo/include) #.hpp
include_directories(./app/inputhandler/include) #.hpp

add_executable(emulator ${SOURCES_EMU})
add_executable(input ${SOURCES_INPUTHANDLER})