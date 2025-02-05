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

# Initiate unit test global variable lists
set(SOURCE_FILES_unitTest "tests/test-main.cpp" CACHE INTERNAL "")
set(LIB_DEPS_unitTest "" CACHE INTERNAL "")

add_subdirectory(src/ystdlib)

add_executable(unitTest ${SOURCE_FILES_unitTest})
target_include_directories(unitTest PRIVATE "${CMAKE_CURRENT_LIST_DIR}/submodules")
target_link_libraries(unitTest PRIVATE ${LIB_DEPS_unitTest})
target_compile_features(unitTest PRIVATE cxx_std_20)
