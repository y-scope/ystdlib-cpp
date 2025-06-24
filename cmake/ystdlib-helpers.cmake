include(CMakePackageConfigHelpers)

# Checks that each argument name in `REQUIRED_ARG_NAMES` is defined and non-empty. Assumes the
# arguments are stored in variables of the form `ARG_<NAME>`.
#
# @param {string[]} REQUIRED_ARG_NAMES
macro(check_required_arguments_exist REQUIRED_ARG_NAMES)
    set(_NAMES "${REQUIRED_ARG_NAMES}")
    foreach(_NAME IN LISTS _NAMES)
        if(NOT DEFINED ARG_${_NAME} OR ARG_${_NAME} STREQUAL "")
            message(FATAL_ERROR "Missing or empty value for argument: '${_NAME}'")
        endif()
    endforeach()
endmacro()

# Checks if `SOURCE_LIST` contains only header files.
#
# @param {string[]} SOURCE_LIST
# @param {bool} IS_HEADER_ONLY Returns whether the list contains only header files.
# @param {string} NON_HEADER_FILE Returns the name of the first, if any, non-header file.
function(check_if_header_only SOURCE_LIST IS_HEADER_ONLY NON_HEADER_FILE)
    set(LOCAL_SOURCE_LIST "${${SOURCE_LIST}}")
    foreach(SRC_FILE IN LISTS LOCAL_SOURCE_LIST)
        if(NOT "${SRC_FILE}" MATCHES ".*\\.(h|hpp)")
            set(${IS_HEADER_ONLY} FALSE PARENT_SCOPE)
            set(${NON_HEADER_FILE} "${SRC_FILE}" PARENT_SCOPE)
            return()
        endif()
    endforeach()
    set(${IS_HEADER_ONLY} TRUE PARENT_SCOPE)
    set(${NON_HEADER_FILE} "" PARENT_SCOPE)
endfunction()

# Adds a C++20 library in the subdirectory NAME with the target NAME and alias NAMESPACE::NAME.
# Libraries with multiple levels of namespace nesting are currently not supported.
#
# @param {string} NAME
# @param {string} NAMESPACE
# @param {string[]} PUBLIC_HEADERS
# @param {string[]} [PRIVATE_SOURCES]
# @param {string[]} [PUBLIC_LINK_LIBRARIES]
# @param {string[]} [PRIVATE_LINK_LIBRARIES]
# @param {string[]} [BUILD_INCLUDE_DIRS="${PROJECT_SOURCE_DIR}/src"] The list of include paths for
# building the library and for external projects that use ystdlib via add_subdirectory().
function(add_cpp_library)
    set(SINGLE_VALUE_ARGS
        NAME
        NAMESPACE
    )
    set(MULTI_VALUE_ARGS
        PUBLIC_HEADERS
        PRIVATE_SOURCES
        PUBLIC_LINK_LIBRARIES
        PRIVATE_LINK_LIBRARIES
        BUILD_INCLUDE_DIRS
    )
    set(REQUIRED_ARGS
        NAME
        NAMESPACE
        PUBLIC_HEADERS
    )
    cmake_parse_arguments(ARG "" "${SINGLE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})
    check_required_arguments_exist("${REQUIRED_ARGS}")

    if(NOT DEFINED ARG_BUILD_INCLUDE_DIRS)
        set(ARG_BUILD_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src")
    endif()

    set(TARGET_NAME "${ARG_NAMESPACE}_${ARG_NAME}")
    set(ALIAS_TARGET_NAME "${ARG_NAMESPACE}::${ARG_NAME}")

    check_if_header_only(ARG_PUBLIC_HEADERS IS_VALID_INTERFACE INVALID_HEADER_FILE)
    if(NOT IS_VALID_INTERFACE)
        message(
            FATAL_ERROR
            "Invalid interface header file ${INVALID_HEADER_FILE} for ${ALIAS_TARGET_NAME}."
        )
    endif()

    check_if_header_only(ARG_PRIVATE_SOURCES IS_INTERFACE_LIB _)
    if(IS_INTERFACE_LIB)
        if(ARG_PRIVATE_LINK_LIBRARIES)
            message(
                FATAL_ERROR
                "`PRIVATE_LINK_LIBRARIES` disabled for header-only library ${ALIAS_TARGET_NAME}."
            )
        endif()
        add_library(${ARG_NAME} INTERFACE)
        target_link_libraries(${ARG_NAME} INTERFACE ${ARG_PUBLIC_LINK_LIBRARIES})

        target_compile_features(${ARG_NAME} INTERFACE cxx_std_20)
    else()
        add_library(${ARG_NAME})
        target_sources(${ARG_NAME} PRIVATE ${ARG_PRIVATE_SOURCES})
        target_link_libraries(
            ${ARG_NAME}
            PUBLIC
                ${ARG_PUBLIC_LINK_LIBRARIES}
            PRIVATE
                ${ARG_PRIVATE_LINK_LIBRARIES}
        )
        target_compile_features(${ARG_NAME} PUBLIC cxx_std_20)
    endif()

    add_library(${ALIAS_TARGET_NAME} ALIAS ${ARG_NAME})

    target_sources(
        ${ARG_NAME}
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                "$<BUILD_INTERFACE:${ARG_BUILD_INCLUDE_DIRS}>"
                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
            FILES ${ARG_PUBLIC_HEADERS}
    )
endfunction()

# Adds a C++ 20 test executable named `unit-test-NAME` that will be built with `SOURCES` and linked
# with `LINK_LIBRARIES`, in addition to Catch2.
#
# @param {string} NAME
# @param {string} NAMESPACE
# @param {string[]} SOURCES
# @param {string[]} [LINK_LIBRARIES]
# @param {string} [UNIFIED_TEST_TARGET] If set, `SOURCES` and `LINK_LIBRARIES` are also added to
# `UNIFIED_TEST_TARGET`.
function(add_catch2_tests)
    set(SINGLE_VALUE_ARGS
        NAME
        NAMESPACE
        UNIFIED_TEST_TARGET
    )
    set(MULTI_VALUE_ARGS
        SOURCES
        LINK_LIBRARIES
    )
    set(REQUIRED_ARGS
        NAME
        NAMESPACE
        SOURCES
    )
    cmake_parse_arguments(ARG "" "${SINGLE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}" ${ARGN})
    check_required_arguments_exist("${REQUIRED_ARGS}")

    set(ALIAS_TARGET "${ARG_NAMESPACE}::${ARG_NAME}")
    set(UNIT_TEST_TARGET "unit-test-${ARG_NAME}")

    add_executable(${UNIT_TEST_TARGET})
    target_sources(${UNIT_TEST_TARGET} PRIVATE ${ARG_SOURCES})
    target_link_libraries(
        ${UNIT_TEST_TARGET}
        PRIVATE
            ${ALIAS_TARGET}
            ${ARG_LINK_LIBRARIES}
            Catch2::Catch2WithMain
    )
    target_compile_features(${UNIT_TEST_TARGET} PRIVATE cxx_std_20)
    set_property(
        TARGET
            ${UNIT_TEST_TARGET}
        PROPERTY
            RUNTIME_OUTPUT_DIRECTORY
                ${CMAKE_BINARY_DIR}/testbin
    )

    if(ARG_UNIFIED_TEST_TARGET)
        target_sources(${ARG_UNIFIED_TEST_TARGET} PRIVATE ${ARG_SOURCES})
        target_link_libraries(
            ${ARG_UNIFIED_TEST_TARGET}
            PRIVATE
                ${ALIAS_TARGET}
                ${ARG_LINK_LIBRARIES}
        )
    endif()
endfunction()

# Creates installation rules for library targets and generated configuration files.
#
# @param {string} NAME
# @param {string} NAMESPACE
# @param {string} CONFIG_DEST_DIR Destination to install the generated config file
# (`NAME-config.cmake`).
# @param {string} CONFIG_INPUT_DIR `configure_package_config_file` input file
# (`NAME-config.cmake.in`).
function(install_library)
    set(SINGLE_VALUE_ARGS
        NAME
        NAMESPACE
        CONFIG_DEST_DIR
        CONFIG_INPUT_DIR
    )
    set(REQUIRED_ARGS
        NAME
        NAMESPACE
        CONFIG_DEST_DIR
        CONFIG_INPUT_DIR
    )
    cmake_parse_arguments(ARG "" "${SINGLE_VALUE_ARGS}" "" ${ARGN})
    check_required_arguments_exist("${REQUIRED_ARGS}")

    set(EXPORT_NAME "${ARG_NAME}-target")
    install(TARGETS "${ARG_NAME}" EXPORT "${EXPORT_NAME}" LIBRARY ARCHIVE RUNTIME FILE_SET HEADERS)
    set_target_properties(
        "${ARG_NAME}"
        PROPERTIES
            OUTPUT_NAME
                "${ARG_NAMESPACE}_${ARG_NAME}"
    )
    install(
        EXPORT "${EXPORT_NAME}"
        DESTINATION ${ARG_CONFIG_DEST_DIR}
        NAMESPACE "${ARG_NAMESPACE}::"
    )

    set(CONFIG_FILE_NAME "${ARG_NAME}-config.cmake")
    set(CONFIG_FILE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME}")
    configure_package_config_file(
        "${ARG_CONFIG_INPUT_DIR}/${CONFIG_FILE_NAME}.in"
        "${CONFIG_FILE_OUTPUT_PATH}"
        INSTALL_DESTINATION "${ARG_CONFIG_DEST_DIR}"
    )
    install(FILES "${CONFIG_FILE_OUTPUT_PATH}" DESTINATION "${ARG_CONFIG_DEST_DIR}")
endfunction()
