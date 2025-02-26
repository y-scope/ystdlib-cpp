# Adds a c++20 interface library in the subdirectory NAME with the target NAME and alias
# NAMESPACE::NAME. Libraries with multiple levels of namespace nesting are currently not supported.
#
# If `YSTDLIB_CPP_BUILD_TESTING` is ON, builds the unit tests specific to the current library, and
# links this library against the unified unit test target for the entire `ystdlib-cpp` project.
#
# @param NAME
# @param NAMESPACE
# @parms TESTS_SOURCES
# @param [LIB_BUILD_INTERFACE="${PROJECT_SOURCE_DIR}/src"] The list of include paths for building
# the library and for external projects that link against it via the add_subdirectory() function.
function(cpp_library)
    set(options "")
    set(oneValueArgs
        NAME
        NAMESPACE
    )
    set(multiValueArgs
        TESTS_SOURCES
        LIB_BUILD_INTERFACE
    )
    cmake_parse_arguments(arg_cpp_lib "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # TODO: Turn this into a function for handling other optional params that have default values.
    if("LIB_BUILD_INTERFACE" IN_LIST arg_cpp_lib_KEYWORDS_MISSING_VALUES)
        message(
            FATAL_ERROR
            "Missing build interface list for ${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME}."
        )
    elseif(NOT DEFINED arg_cpp_lib_LIB_BUILD_INTERFACE)
        set(arg_cpp_lib_LIB_BUILD_INTERFACE "${PROJECT_SOURCE_DIR}/src")
    endif()

    # Build interface library
    add_library(${arg_cpp_lib_NAME} INTERFACE)
    target_include_directories(
        ${arg_cpp_lib_NAME}
        INTERFACE
            "$<BUILD_INTERFACE:${arg_cpp_lib_LIB_BUILD_INTERFACE}>"
    )
    target_compile_features(${arg_cpp_lib_NAME} INTERFACE cxx_std_20)
    add_library(${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME} ALIAS ${arg_cpp_lib_NAME})

    if(YSTDLIB_CPP_BUILD_TESTING)
        # Build library-specific unit test target
        set(_UNIT_TEST_TARGET "unit-test-${arg_cpp_lib_NAME}")
        add_executable(${_UNIT_TEST_TARGET})
        target_sources(${_UNIT_TEST_TARGET} PRIVATE ${arg_cpp_lib_TESTS_SOURCES})
        target_link_libraries(
            ${_UNIT_TEST_TARGET}
            PRIVATE
                Catch2::Catch2WithMain
                ${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME}
        )
        target_compile_features(${_UNIT_TEST_TARGET} PRIVATE cxx_std_20)
        set_property(
            TARGET
                ${_UNIT_TEST_TARGET}
            PROPERTY
                RUNTIME_OUTPUT_DIRECTORY
                    ${CMAKE_BINARY_DIR}/testbin
        )

        # Link against unified unit test
        target_sources(${UNIFIED_UNIT_TEST_TARGET} PRIVATE ${arg_cpp_lib_TESTS_SOURCES})
        target_link_libraries(
            ${UNIFIED_UNIT_TEST_TARGET}
            PRIVATE
                ${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME}
        )
    endif()
endfunction()
