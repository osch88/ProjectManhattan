# stop if cmake version below 3.5.1
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

#project name and supported languages
project(project_manhattan LANGUAGES CXX)

#set build directory
#set(BUILD_DIR_NAME "${CMAKE_SOURCE_DIR}/build")


add_subdirectory(app/inputhandler)
add_subdirectory(app/reo)
add_subdirectory(lib)
add_subdirectory(test)