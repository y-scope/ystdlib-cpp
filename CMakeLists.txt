cmake_minimum_required(VERSION 3.16.3)
project(YSTDLIB_CPP LANGUAGES CXX)

set(YSTDLIB_CPP_VERSION "0.0.1" CACHE STRING "Project version.")

# Enable exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL
    "Enable/Disable output of compile commands during generation."
    FORCE
)

option(BUILD_TESTING "If ON, unit tests will be built." ON)

find_package(Catch2 3.8.0 REQUIRED)
if(Catch2_FOUND)
    message(STATUS "Found Catch2 ${Catch2_VERSION}.")
else()
    message(FATAL_ERROR "Could not find libraries for Catch2.")
endif()

# Import CMake helper functions
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
include(ystdlib-cpp-helpers)

# Set up the global unit test target
set(GLOBAL_UNIT_TEST_TARGET "unit-test")
add_executable(${GLOBAL_UNIT_TEST_TARGET})
target_link_libraries(${GLOBAL_UNIT_TEST_TARGET} PRIVATE Catch2::Catch2WithMain)
target_compile_features(${GLOBAL_UNIT_TEST_TARGET} PRIVATE cxx_std_20)

add_subdirectory(src/ystdlib)
