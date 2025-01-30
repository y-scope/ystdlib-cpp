set(LIB_ENABLE_INSTALL ${YSTDLIB_CPP_ENABLE_INSTALL})
set(LIB_BUILD_INTERFACE ${YSTDLIB_CPP_BUILD_INCLUDE_DIRS})
set(LIB_INSTALL_INTERFACE ${YSTDLIB_CPP_INSTALL_INCLUDE_DIRS})

# cpp_library()
#
# CMake function for adding C++ libraries with sources, dependencies, and build settings.
#
# Parameters:
# NAMESPACE: namespace of the library
# NAME: name of target
function(cpp_library)
    set(options)
    set(oneValueArgs
        NAME
        NAMESPACE
    )
    set(multiValueArgs)
    cmake_parse_arguments(
        arg_cpp_lib #
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    if(LIB_ENABLE_INSTALL)
        set(_TARGET_LIB_NAME "${arg_cpp_lib_NAME}")
    else()
        set(_TARGET_LIB_NAME "${arg_cpp_lib_NAMESPACE}_${arg_cpp_lib_NAME}")
    endif()

    add_library(${_TARGET_LIB_NAME} INTERFACE)
    target_include_directories(
        ${_TARGET_LIB_NAME}
        INTERFACE
            "$<BUILD_INTERFACE:${LIB_BUILD_INTERFACE}>"
            "$<INSTALL_INTERFACE:${LIB_INSTALL_INTERFACE}>"
    )
    target_compile_features(${_TARGET_LIB_NAME} INTERFACE cxx_std_20)
    add_library(${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME} ALIAS ${_TARGET_LIB_NAME})
endfunction()
