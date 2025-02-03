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

# Import CMake helper functions
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
include(ystdlib-cpp-helpers)

add_subdirectory(src/ystdlib)

set(SOURCE_FILES_unitTest
    src/ystdlib/container/Array.hpp
    tests/test-Array.cpp
    tests/test-main.cpp
)
add_executable(unitTest ${SOURCE_FILES_unitTest})
target_include_directories(unitTest PRIVATE "${CMAKE_CURRENT_LIST_DIR}/submodules")
target_link_libraries(unitTest PRIVATE ystdlib::container)
target_compile_features(unitTest PRIVATE cxx_std_20)
