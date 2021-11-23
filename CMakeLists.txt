# stop if cmake version below 3.5.1
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

#project name and supported languages
project(project_manhattan LANGUAGES CXX)

#set build directory
#set(BUILD_DIR_NAME "${CMAKE_SOURCE_DIR}/build")


add_subdirectory(app/inputhandler)
add_subdirectory(app/reo)
add_subdirectory(app/avic)
add_subdirectory(lib)


#set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
#set(SOURCES_EMU ./app/reo/main.cpp ./app/reo/src/engine.cpp ./lib/hal_monitor.cpp ./lib/socketcan.cpp)
#set(SOURCES_INPUTHANDLER ./app/inputhandler/main.cpp ./app/inputhandler/src/keyboard_input.cpp ./lib/writecan.cpp ./lib/socketcan.cpp)

#include_directories(./lib) #.hpp
#include_directories(./app/reo/include) #.hpp
#include_directories(./app/inputhandler/include) #.hpp

# fetch googletest
#include(cmake/googletest.cmake)
#fetch_googletest(
#    ${PROJECT_SOURCE_DIR}/cmake
#    ${PROJECT_BINARY_DIR}/googletest
#    )

# enable testing
#enable_testing()

# define tests
#add_subdirectory(test)

#add_executable(emulator ${SOURCES_EMU})
#add_executable(input ${SOURCES_INPUTHANDLER})