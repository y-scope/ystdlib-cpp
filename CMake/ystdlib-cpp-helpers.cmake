# @param {string[]} REQUIRED_ARGS The list of arguments to check.
# @param {string[]} ARG_KEYWORDS_MISSING_VALUES The list of arguments with missing values.
# @param {string} LIB_NAME The library target on which to perform the check.
function(require_argument_values REQUIRED_ARGS ARG_KEYWORDS_MISSING_VALUES LIB_NAME)
    foreach(arg IN LISTS REQUIRED_ARGS)
        if("${arg}" IN_LIST ARG_KEYWORDS_MISSING_VALUES)
            message(FATAL_ERROR "Missing values for argument '${arg}' in target '${LIB_NAME}'.")
        endif()
    endforeach()
endfunction()

# @param {string[]} SOURCE_LIST The list of source files to check.
# @param {bool} IS_HEADER_ONLY Returns whether the list only contains header files.
# @param {string} NON_HEADER_FILE Returns the name of the first, if any, non-header file.
function(check_if_header_only SOURCE_LIST IS_HEADER_ONLY NON_HEADER_FILE)
    set(_LOCAL_SOURCE_LIST "${${SOURCE_LIST}}")
    foreach(src_file IN LISTS _LOCAL_SOURCE_LIST)
        if(NOT ${src_file} MATCHES ".*\\.(h|hpp)")
            set(${IS_HEADER_ONLY} FALSE PARENT_SCOPE)
            set(${NON_HEADER_FILE} ${src_file} PARENT_SCOPE)
            return()
        endif()
    endforeach()
    set(${IS_HEADER_ONLY} TRUE PARENT_SCOPE)
    set(${NON_HEADER_FILE} "" PARENT_SCOPE)
endfunction()

# Adds a c++20 interface library in the subdirectory NAME with the target NAME and alias
# NAMESPACE::NAME. Libraries with multiple levels of namespace nesting are currently not supported.
#
# If `YSTDLIB_CPP_ENABLE_TESTS` is ON, builds the unit tests specific to the current library, and
# links this library against the unified unit test target for the entire `ystdlib-cpp` project.
#
# @param {string} NAME
# @param {string} NAMESPACE
# @param {string[]} PUBLIC_HEADERS
# @parms {string[]} TESTS_SOURCES
# @param {string[]} [PRIVATE_SOURCES]
# @param {string[]} [PUBLIC_LINK_LIBRARIES]
# @param {string[]} [PRIVATE_LINK_LIBRARIES]
# @parms {string[]} [TESTS_LINK_LIBRARIES]
# @param {string[]} [BUILD_INCLUDE_DIR="${PROJECT_SOURCE_DIR}/src"] The list of include paths for
# building the library and for external projects that builds `ystdlib-cpp` as a CMAKE subproject via
# the add_subdirectory() function.
function(cpp_library)
    set(options "")
    set(oneValueArgs
        NAME
        NAMESPACE
    )
    set(multiValueArgs
        PUBLIC_HEADERS
        PRIVATE_SOURCES
        PUBLIC_LINK_LIBRARIES
        PRIVATE_LINK_LIBRARIES
        TESTS_SOURCES
        TESTS_LINK_LIBRARIES
        BUILD_INCLUDE_DIR
    )
    set(requireValueArgs
        NAME
        NAMESPACE
        PUBLIC_HEADERS
        TESTS_SOURCES
        BUILD_INCLUDE_DIR
    )
    cmake_parse_arguments(arg_cpp_lib "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(_ALIAS_TARGET_NAME "${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME}")

    require_argument_values(
        "${requireValueArgs}"
        "${arg_cpp_lib_KEYWORDS_MISSING_VALUES}"
        "${_ALIAS_TARGET_NAME}"
    )

    if(NOT DEFINED arg_cpp_lib_BUILD_INCLUDE_DIR)
        set(arg_cpp_lib_BUILD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src")
    endif()

    check_if_header_only(arg_cpp_lib_PUBLIC_HEADERS _IS_VALID_INTERFACE _INVALID_HEADER_FILE)
    if(NOT _IS_VALID_INTERFACE)
        message(
            FATAL_ERROR
            "Invalid interface header file ${_INVALID_HEADER_FILE} for ${_ALIAS_TARGET_NAME}."
        )
    endif()

    check_if_header_only(arg_cpp_lib_PRIVATE_SOURCES _IS_INTERFACE_LIB _)
    if(_IS_INTERFACE_LIB)
        add_library(${arg_cpp_lib_NAME} INTERFACE)
        target_include_directories(
            ${arg_cpp_lib_NAME}
            INTERFACE
                "$<BUILD_INTERFACE:${arg_cpp_lib_BUILD_INCLUDE_DIR}>"
        )
        target_compile_features(${arg_cpp_lib_NAME} INTERFACE cxx_std_20)
    else()
        # The library type is specified by `BUILD_SHARED_LIBS` if it is defined. Otherwise, the type
        # defaults to static.
        add_library(${arg_cpp_lib_NAME})
        target_sources(
            ${arg_cpp_lib_NAME}
            PRIVATE
                ${arg_cpp_lib_PUBLIC_HEADERS}
                ${arg_cpp_lib_PRIVATE_SOURCES}
        )
        target_include_directories(
            ${arg_cpp_lib_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${arg_cpp_lib_BUILD_INCLUDE_DIR}>"
        )
        target_compile_features(${arg_cpp_lib_NAME} PUBLIC cxx_std_20)
    endif()

    target_link_libraries(
        ${arg_cpp_lib_NAME}
        PUBLIC
            ${arg_cpp_lib_PUBLIC_LINK_LIBRARIES}
        PRIVATE
            ${arg_cpp_lib_PRIVATE_LINK_LIBRARIES}
    )
    add_library(${_ALIAS_TARGET_NAME} ALIAS ${arg_cpp_lib_NAME})

    if(YSTDLIB_CPP_ENABLE_TESTS)
        # Build library-specific unit test target
        set(_UNIT_TEST_TARGET "unit-test-${arg_cpp_lib_NAME}")
        add_executable(${_UNIT_TEST_TARGET})
        target_sources(${_UNIT_TEST_TARGET} PRIVATE ${arg_cpp_lib_TESTS_SOURCES})
        target_link_libraries(
            ${_UNIT_TEST_TARGET}
            PRIVATE
                Catch2::Catch2WithMain
                ${_ALIAS_TARGET_NAME}
                ${arg_cpp_lib_TESTS_LINK_LIBRARIES}
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
                ${_ALIAS_TARGET_NAME}
                ${arg_cpp_lib_TESTS_LINK_LIBRARIES}
        )
    endif()
endfunction()
