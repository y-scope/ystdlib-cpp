cmake_minimum_required(VERSION 3.23)

project(ystdlib-examples)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(default_build_type "Release")
    message(STATUS "No build type specified. Setting to '${default_build_type}'.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL
    "Enable/disable output of compile commands during generation."
    FORCE
)

if(ystdlib-examples_IS_TOP_LEVEL)
    # Include dependency settings if the project isn't being included as a subproject.
    # NOTE: We mark the file optional because if the user happens to have the dependencies
    # installed, this file is not necessary.
    include("${CMAKE_SOURCE_DIR}/../build/deps/cmake-settings/all.cmake" OPTIONAL)
endif()

find_package(ystdlib REQUIRED)
message(STATUS "Found ystdlib ${ystdlib_VERSION}.")

add_executable(linking-tests "${CMAKE_SOURCE_DIR}/src/linking-tests.cpp")

target_compile_features(linking-tests PRIVATE cxx_std_20)

target_link_libraries(
    linking-tests
    PRIVATE
        ystdlib::containers
        ystdlib::error_handling
        ystdlib::io_interface
        ystdlib::wrapped_facade_headers
)
