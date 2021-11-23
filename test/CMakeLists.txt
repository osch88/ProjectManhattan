## Project settings
project(tests LANGUAGES CXX)

include_directories(../lib/hal/include ../lib/socketcan/include ../app/inputhandler/include)

## Test sources
#add_executable(${PROJECT_NAME}
#    ${CMAKE_CURRENT_SOURCE_DIR} unit/test_hal_monitor.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR} ../lib/hal/src/hal_monitor.cpp
#)

## Include directories based on component
#target_include_directories(${PROJECT_NAME} PRIVATE
#    ${COMPONENT_INCLUDES}
#)

## Linked libraries based on component
#target_link_libraries(${PROJECT_NAME}
#    gtest
#    gtest_main
    #gmock
    #Threads::Threads
#    ${COMPONENT_LIBRARIES}
#)

## Add test suite to available tests
#add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})


# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    test_hal_monitor
    unit/test_hal_monitor.cpp
)

target_link_libraries(
    test_hal_monitor
    gtest
    gtest_main
    pthread
    socketcan
    hal
)

include(GoogleTest)
gtest_discover_tests(test_hal_monitor)
