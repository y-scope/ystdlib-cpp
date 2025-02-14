cmake_minimum_required(VERSION 3.16.3)
project(YSTDLIB_CPP LANGUAGES CXX)

set(YSTDLIB_CPP_VERSION "0.0.1" CACHE STRING "Project version.")

# find_package() uses upper-case <PACKAGENAME>_ROOT variables and prefers the paths specified by
# these variables when looking for library packages.
cmake_policy(SET CMP0144 NEW)

# Enable exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL
    "Enable/Disable output of compile commands during generation."
    FORCE
)

find_package(Catch2 3.8.0 REQUIRED)
if(Catch2_FOUND)
    message(STATUS "Found Catch2 ${Catch2_VERSION}.")
else()
    message(FATAL_ERROR "Could not find libraries for Catch2.")
endif()

# Import CMake helper functions
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
include(ystdlib-cpp-helpers)

add_subdirectory(src/ystdlib)

add_executable(unitTest)
target_sources(unitTest PRIVATE src/main.cpp)
target_link_libraries(
    unitTest
    PRIVATE
        ystdlib::testlib
        Catch2::Catch2WithMain
)
target_compile_features(unitTest PRIVATE cxx_std_20)
