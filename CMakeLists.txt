cmake_minimum_required(VERSION 3.23)

project(ystdlib VERSION "0.0.1" LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(ystdlib-helpers)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Build using shared libraries." OFF)
option(ystdlib_BUILD_TESTING "Build the testing tree for ystdlib." ON)

# Require compiler versions that support the C++20 features necessary for compiling ystdlib
if("AppleClang" STREQUAL "${CMAKE_CXX_COMPILER_ID}")
    set(ystdlib_CMAKE_CXX_COMPILER_MIN_VERSION "16")
elseif("Clang" STREQUAL "${CMAKE_CXX_COMPILER_ID}")
    set(ystdlib_CMAKE_CXX_COMPILER_MIN_VERSION "16")
elseif("GNU" STREQUAL "${CMAKE_CXX_COMPILER_ID}")
    set(ystdlib_CMAKE_CXX_COMPILER_MIN_VERSION "11")
else()
    message(
        FATAL_ERROR
        "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}. Please use AppleClang, Clang, or GNU."
    )
endif()
if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS "${ystdlib_CMAKE_CXX_COMPILER_MIN_VERSION}")
    message(
        FATAL_ERROR
        "${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION} is too low. Must be at \
        least ${ystdlib_CMAKE_CXX_COMPILER_MIN_VERSION}."
    )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL
    "Enable/Disable output of compile commands during generation."
    FORCE
)

set(ystdlib_LIBRARIES
    "containers"
    "error_handling"
    "io_interface"
    "wrapped_facade_headers"
    CACHE STRING
    "Semi-colon separated list of libraries to be built."
)

message(STATUS "Building the following libraries:")
foreach(LIB IN LISTS ystdlib_LIBRARIES)
    message(" - ${LIB}")
endforeach()

if(ystdlib_IS_TOP_LEVEL)
    # Include dependency settings if the project isn't being included as a subproject.
    # NOTE: We mark the file optional because if the user happens to have the dependencies
    # installed, this file is not necessary.
    include("build/deps/cmake-settings/all.cmake" OPTIONAL)

    # If previously undefined, `BUILD_TESTING` will be set to ON.
    include(CTest)
endif()

if(BUILD_TESTING AND ystdlib_BUILD_TESTING)
    set(ystdlib_ENABLE_TESTS ON)
endif()

if(ystdlib_ENABLE_TESTS)
    find_package(Catch2 3.8.0 REQUIRED)
    message(STATUS "Found Catch2 ${Catch2_VERSION}.")
    include(Catch)

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
    catch_discover_tests(${UNIFIED_UNIT_TEST_TARGET} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/testbin)
endif()

set(ystdlib_INSTALL_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/ystdlib)

add_subdirectory(src/ystdlib)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/ystdlib-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ystdlib-config.cmake
    INSTALL_DESTINATION ${ystdlib_INSTALL_CONFIG_DIR}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ystdlib-config-version.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/ystdlib-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/ystdlib-config-version.cmake
    DESTINATION ${ystdlib_INSTALL_CONFIG_DIR}
)
