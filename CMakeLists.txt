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

find_package(Catch2 3.8.0 REQUIRED)
if(Catch2_FOUND)
    message(STATUS "Found Catch2 ${Catch2_VERSION}.")
else()
    message(FATAL_ERROR "Could not find libraries for Catch2.")
endif()

# Import CMake helper functions
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
include(ystdlib-cpp-helpers)

# Initiate unit test global list variables
set(SOURCE_FILES_unitTest "" CACHE INTERNAL "")
set(LIB_DEPS_unitTest "Catch2::Catch2WithMain" CACHE INTERNAL "")

add_subdirectory(src/ystdlib)

add_executable(unit-test)
target_sources(unit-test PRIVATE ${SOURCE_FILES_unitTest})
target_link_libraries(unit-test PRIVATE ${LIB_DEPS_unitTest})
target_compile_features(unit-test PRIVATE cxx_std_20)
