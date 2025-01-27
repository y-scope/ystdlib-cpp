# ystdlib_cpp_library()
#
# CMake function to imitate Bazel's cc_library rule.
#
# Parameters:
# NAME: name of target (see Note)
# HDRS: List of public header files for the library
# PUBLIC: Add this so that this library will be exported under ystdlib::
# PRIVATE: Add this to make the library internal to ystdlib-cpp
#
# Note:
# When included as a subdirectory, ystdlib_cpp_library will always create a library named
# ystdlib_${NAME} and alias target ystdlib::${NAME}. The ystdlib:: form should always be used to
# reduce namespace pollution.
function(ystdlib_cpp_library)
    set(options
        PUBLIC
        PRIVATE
    )
    set(oneValueArgs NAME)
    set(multiValueArgs HDRS)
    cmake_parse_arguments(
        arg_ystdlib_cpp_lib
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    if(YSTDLIB_CPP_ENABLE_INSTALL)
        set(_TARGET_LIB_NAME "${arg_ystdlib_cpp_lib_NAME}")
    else()
        set(_TARGET_LIB_NAME "ystdlib_${arg_ystdlib_cpp_lib_NAME}")
    endif()

    # TODO: add build process for libraries with source files
    add_library(${_TARGET_LIB_NAME} INTERFACE)
    target_include_directories(
        ${_TARGET_LIB_NAME}
        INTERFACE
            "$<BUILD_INTERFACE:${YSTDLIB_CPP_BUILD_INCLUDE_DIRS}>"
            "$<INSTALL_INTERFACE:${YSTDLIB_CPP_INSTALL_INCLUDE_DIRS}>"
    )
    target_compile_features(${_TARGET_LIB_NAME} INTERFACE cxx_std_20)
    add_library(ystdlib::${arg_ystdlib_cpp_lib_NAME} ALIAS ${_TARGET_LIB_NAME})

    # TODO: install header files into target locations
endfunction()
