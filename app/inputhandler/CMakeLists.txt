cmake_minimum_required (VERSION 3.5.1)

project(inputhandler LANGUAGES CXX)

#set(BUILD_DIR_NAME "${CMAKE_SOURCE_DIR}/build")

include_directories(include ../../lib)

set(EXECUTABLE_OUTPUT_PATH "../../../")
add_executable(inputhandler
    main.cpp
    src/keyboard_input.cpp)
set_target_properties(
    inputhandler 
    PROPERTIES 
        #OUTPUT_NAME "myname"
        SUFFIX ".out"
    )

target_link_libraries(${PROJECT_NAME} PUBLIC socketcan writecan)