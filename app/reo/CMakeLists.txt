cmake_minimum_required (VERSION 3.5.1)

project(reo LANGUAGES CXX)

#set(BUILD_DIR_NAME "${CMAKE_SOURCE_DIR}/build")


include_directories(include ../../lib/socketcan/include ../../lib/hal/include ../inputhandler/include ../../lib/writecan/include)

set(EXECUTABLE_OUTPUT_PATH "../../")
add_executable(reo
main.cpp
src/mainloop.cpp)

target_compile_options(reo PRIVATE -Wall -Wextra -Wpedantic -g)

set_target_properties(
    reo 
    PROPERTIES 
            #OUTPUT_NAME "myname"
            SUFFIX ".out"
        )

target_link_libraries(${PROJECT_NAME} PUBLIC socketcan hal pthread)
