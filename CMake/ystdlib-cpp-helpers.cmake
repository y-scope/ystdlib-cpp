# check_if_header_only_library()
#
# @param SOURCE_LIST The list of source files that a target library uses
# @param IS_HEADER_ONLY Returns whether the target library only contains header files
function(check_if_header_only_library SOURCE_LIST IS_HEADER_ONLY)
    set(_LOCAL_SOURCE_LIST "${${SOURCE_LIST}}")
    foreach(src_file IN LISTS _LOCAL_SOURCE_LIST)
        if(${src_file} MATCHES ".*\\.(h|hpp|inc)")
            list(REMOVE_ITEM _LOCAL_SOURCE_LIST "${src_file}")
        endif()
    endforeach()

    if(_LOCAL_SOURCE_LIST STREQUAL "")
        set(${IS_HEADER_ONLY} TRUE PARENT_SCOPE)
    else()
        set(${IS_HEADER_ONLY} FALSE PARENT_SCOPE)
    endif()
endfunction()

# Adds a c++20 interface library in the subdirectory NAME with the target NAME and alias
# NAMESPACE::NAME. Libraries with multiple levels of namespace nesting are currently not supported.
#
# If `YSTDLIB_CPP_ENABLE_TESTS` is ON, builds the unit tests specific to the current library, and
# links this library against the unified unit test target for the entire `ystdlib-cpp` project.
#
# @param NAME
# @param NAMESPACE
# @param HEADERS
# @param SOURCES
# @param DEPENDS
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
        HEADERS
        SOURCES
        DEPENDS
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

    check_if_header_only_library(arg_cpp_lib_SOURCES _IS_INTERFACE_LIB)

    if(_IS_INTERFACE_LIB)
        add_library(${arg_cpp_lib_NAME} INTERFACE)
        target_include_directories(
            ${arg_cpp_lib_NAME}
            INTERFACE
                "$<BUILD_INTERFACE:${arg_cpp_lib_LIB_BUILD_INTERFACE}>"
        )
        target_compile_features(${arg_cpp_lib_NAME} INTERFACE cxx_std_20)
    else()
        add_library(${arg_cpp_lib_NAME} "") # Library type determined by BUILD_SHARED_LIBS
        target_sources(
            ${arg_cpp_lib_NAME}
            PRIVATE
                ${arg_cpp_lib_HEADERS}
                ${arg_cpp_lib_SOURCES}
        )
        target_include_directories(
            ${arg_cpp_lib_NAME}
            PUBLIC
                "$<BUILD_INTERFACE:${arg_cpp_lib_LIB_BUILD_INTERFACE}>"
        )
        target_compile_features(${arg_cpp_lib_NAME} PUBLIC cxx_std_20)
    endif()

    target_link_libraries(${arg_cpp_lib_NAME} PUBLIC ${arg_cpp_lib_DEPENDS})
    add_library(${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME} ALIAS ${arg_cpp_lib_NAME})

    if(YSTDLIB_CPP_ENABLE_TESTS)
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
