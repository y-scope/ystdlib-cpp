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

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(YSTDLIB_CPP_MASTER_PROJECT ON CACHE BOOL "ystdlib-cpp is the top-level CMake project.")
endif()

# Enable unit test building by default if `BUILD_TESING` is not already defined in the parent scope.
if(NOT DEFINED BUILD_TESTING)
    set(BUILD_TESTING ON)
endif()

set(YSTDLIB_CPP_ENABLE_TESTS OFF)
if((YSTDLIB_CPP_MASTER_PROJECT OR YSTDLIB_CPP_BUILD_TESTING) AND BUILD_TESTING)
    set(YSTDLIB_CPP_ENABLE_TESTS ON)
endif()

# Import CMake helper functions
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)

if(YSTDLIB_CPP_ENABLE_TESTS)
    find_package(Catch2 3.8.0 REQUIRED)
    if(Catch2_FOUND)
        message(STATUS "Found Catch2 ${Catch2_VERSION}.")
    else()
        message(FATAL_ERROR "Could not find libraries for Catch2.")
    endif()

    # Set up the unified unit test target
    set(UNIFIED_UNIT_TEST_TARGET "unit-test-all")
    add_executable(${UNIFIED_UNIT_TEST_TARGET})
    target_link_libraries(${UNIFIED_UNIT_TEST_TARGET} PRIVATE Catch2::Catch2WithMain)
    target_compile_features(${UNIFIED_UNIT_TEST_TARGET} PRIVATE cxx_std_20)
    set_property(
        TARGET
            ${UNIFIED_UNIT_TEST_TARGET}
        PROPERTY
            RUNTIME_OUTPUT_DIRECTORY
                ${CMAKE_BINARY_DIR}/testbin
    )
endif()

include(ystdlib-cpp-helpers)

add_subdirectory(src/ystdlib)
