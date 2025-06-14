include(CMakePackageConfigHelpers)

# @param {string[]} SOURCE_LIST The list of source files to check.
# @param {bool} IS_HEADER_ONLY Returns TRUE if list only contains header files, FALSE otherwise.
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

# Adds a c++20 library in the subdirectory NAME with the target NAME and alias NAMESPACE::NAME.
# Libraries with multiple levels of namespace nesting are currently not supported.
#
# @param {string} NAME
# @param {string} NAMESPACE
# @param {string[]} PUBLIC_HEADERS
# @param {string[]} [PRIVATE_SOURCES]
# @param {string[]} [PUBLIC_LINK_LIBRARIES]
# @param {string[]} [PRIVATE_LINK_LIBRARIES]
# @param {string[]} [BUILD_INCLUDE_DIR="${PROJECT_SOURCE_DIR}/src"] The list of include paths for
# building the library and for external projects that builds `ystdlib` as a CMAKE subproject via
# the add_subdirectory() function.
function(cpp_library)
    set(oneValueArgs
        NAME
        NAMESPACE
    )
    set(multiValueArgs
        PUBLIC_HEADERS
        PRIVATE_SOURCES
        PUBLIC_LINK_LIBRARIES
        PRIVATE_LINK_LIBRARIES
        BUILD_INCLUDE_DIR
    )
    set(requireValueArgs
        NAME
        NAMESPACE
        PUBLIC_HEADERS
        BUILD_INCLUDE_DIR
    )
    cmake_parse_arguments(arg "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if(arg_KEYWORDS_MISSING_VALUES)
        message(
            FATAL_ERROR
            "cpp_library missing required arguments: ${arg_KEYWORDS_MISSING_VALUES}"
        )
    endif()

    if(NOT DEFINED arg_BUILD_INCLUDE_DIR)
        set(arg_BUILD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src")
    endif()

    set(_ALIAS_TARGET_NAME "${arg_NAMESPACE}::${arg_NAME}")

    check_if_header_only(arg_PUBLIC_HEADERS _IS_VALID_INTERFACE _INVALID_HEADER_FILE)
    if(NOT _IS_VALID_INTERFACE)
        message(
            FATAL_ERROR
            "Invalid interface header file ${_INVALID_HEADER_FILE} for ${_ALIAS_TARGET_NAME}."
        )
    endif()

    check_if_header_only(arg_PRIVATE_SOURCES _IS_INTERFACE_LIB _)
    if(_IS_INTERFACE_LIB)
        if(arg_PRIVATE_LINK_LIBRARIES)
            message(
                FATAL_ERROR
                "`PRIVATE_LINK_LIBRARIES` disabled for header-only library ${_ALIAS_TARGET_NAME}."
            )
        endif()
        add_library(${arg_NAME} INTERFACE)
        target_link_libraries(${arg_NAME} INTERFACE ${arg_PUBLIC_LINK_LIBRARIES})

        target_compile_features(${arg_NAME} INTERFACE cxx_std_20)
    else()
        add_library(${arg_NAME})
        target_sources(
            ${arg_NAME}
            PRIVATE
                ${arg_PUBLIC_HEADERS}
                ${arg_PRIVATE_SOURCES}
        )
        target_link_libraries(
            ${arg_NAME}
            PUBLIC
                ${arg_PUBLIC_LINK_LIBRARIES}
            PRIVATE
                ${arg_PRIVATE_LINK_LIBRARIES}
        )
        target_compile_features(${arg_NAME} PUBLIC cxx_std_20)
    endif()

    add_library(${_ALIAS_TARGET_NAME} ALIAS ${arg_NAME})

    target_sources(
        ${arg_NAME}
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                "$<BUILD_INTERFACE:${arg_BUILD_INCLUDE_DIR}>"
                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
            FILES ${arg_PUBLIC_HEADERS}
    )
endfunction()

# Builds a C++ 20 test executable named unit-test-NAME linking it with Catch2.
# The test SOURCES and any LINK_LIBRARIES are also added to the UNIFIED_TEST_TARGET if it is set.
#
# @param {string} NAME
# @param {string} NAMESPACE
# @param {string[]} SOURCES
# @param {string[]} [LINK_LIBRARIES]
# @param {string} [UNIFIED_TEST_TARGET] If set the tests are also added to this unified target.
function(catch2_tests)
    set(oneValueArgs
        NAME
        NAMESPACE
        UNIFIED_TEST_TARGET
    )
    set(multiValueArgs
        SOURCES
        LINK_LIBRARIES
    )
    set(requireValueArgs
        NAME
        NAMESPACE
        SOURCES
    )
    cmake_parse_arguments(arg "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    if(arg_KEYWORDS_MISSING_VALUES)
        message(
            FATAL_ERROR
            "catch2_tests missing required arguments:
        ${arg_KEYWORDS_MISSING_VALUES}"
        )
    endif()

    set(_ALIAS_TARGET "${arg_NAMESPACE}::${arg_NAME}")
    set(_UNIT_TEST_TARGET "unit-test-${arg_NAME}")

    add_executable(${_UNIT_TEST_TARGET})
    target_sources(${_UNIT_TEST_TARGET} PRIVATE ${arg_SOURCES})
    target_link_libraries(
        ${_UNIT_TEST_TARGET}
        PRIVATE
            Catch2::Catch2WithMain
            ${_ALIAS_TARGET}
            ${arg_LINK_LIBRARIES}
    )
    target_compile_features(${_UNIT_TEST_TARGET} PRIVATE cxx_std_20)
    set_property(
        TARGET
            ${_UNIT_TEST_TARGET}
        PROPERTY
            RUNTIME_OUTPUT_DIRECTORY
                ${CMAKE_BINARY_DIR}/testbin
    )

    if(arg_UNIFIED_TEST_TARGET)
        target_sources(${arg_UNIFIED_TEST_TARGET} PRIVATE ${arg_SOURCES})
        target_link_libraries(
            ${arg_UNIFIED_TEST_TARGET}
            PRIVATE
                ${_ALIAS_TARGET}
                ${arg_LINK_LIBRARIES}
        )
    endif()
endfunction()

# Installs library targets and generated configuration files.
# Target, input config, and output config files are named NAME-target.cmake, NAME-config.cmake.in,
# and NAME-config.cmake respectively.
#
# @param {string} NAME
# @param {string} NAMESPACE
# @param {string} [CONFIG_DEST_PATH] Destination to install generated config file
# (NAME-config.cmake).
# @param {string} [CONFIG_INPUT_PATH] Paht to read configure_package_config_file input file
# (NAME-config.cmake.in).
# @param {string} [CONFIG_OUTPUT_PATH] Paht to write configure_package_config_file output file
# (NAME-config.cmake).
function(install_library)
    set(oneValueArgs
        NAME
        NAMESPACE
        CONFIG_DEST_PATH
        CONFIG_INPUT_PATH
        CONFIG_OUTPUT_PATH
    )
    set(requireValueArgs
        NAME
        NAMESPACE
    )
    cmake_parse_arguments(arg "" "${oneValueArgs}" "" ${ARGN})
    if(arg_KEYWORDS_MISSING_VALUES)
        message(
            FATAL_ERROR
            "install_library missing required arguments: ${arg_KEYWORDS_MISSING_VALUES}"
        )
    endif()

    if(NOT DEFINED arg_CONFIG_DEST_PATH)
        set(arg_CONFIG_DEST_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/${arg_NAMESPACE}/libs")
    endif()

    if(NOT DEFINED arg_CONFIG_INPUT_PATH)
        set(arg_CONFIG_INPUT_PATH "${PROJECT_SOURCE_DIR}/cmake/libs")
    endif()

    if(NOT DEFINED arg_CONFIG_OUTPUT_PATH)
        set(arg_CONFIG_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    endif()

    install(
        TARGETS
            "${arg_NAME}"
        EXPORT "${arg_NAME}-target"
        LIBRARY
        ARCHIVE
        RUNTIME
        FILE_SET
        HEADERS
    )

    install(
        EXPORT "${arg_NAME}-target"
        DESTINATION ${arg_CONFIG_DEST_PATH}
        NAMESPACE "${arg_NAMESPACE}::"
        COMPONENT "${arg_NAME}"
    )

    configure_package_config_file(
        ${arg_CONFIG_INPUT_PATH}/${arg_NAME}-config.cmake.in
        ${arg_CONFIG_OUTPUT_PATH}/${arg_NAME}-config.cmake
        INSTALL_DESTINATION ${arg_CONFIG_DEST_PATH}
    )

    install(
        FILES
            ${arg_CONFIG_OUTPUT_PATH}/${arg_NAME}-config.cmake
        DESTINATION ${arg_CONFIG_DEST_PATH}
    )
endfunction()
