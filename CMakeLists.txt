# stop if cmake version below 3.5.1
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

#project name and supported languages
project(project_manhattan LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

#set build directory
#set(BUILD_DIR_NAME "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_CXX_FLAGS: -Wall)


add_subdirectory(app/inputhandler)
add_subdirectory(app/reo)
add_subdirectory(app/avic)
add_subdirectory(lib)
add_subdirectory(test)