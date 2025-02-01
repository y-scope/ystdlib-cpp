set(CPP_LIB_BUILD_INTERFACE ${YSTDLIB_CPP_BUILD_INCLUDE_DIRS})
set(CPP_LIB_INSTALL_INTERFACE ${YSTDLIB_CPP_INSTALL_INCLUDE_DIRS})

# CMake function for adding C++ libraries with sources, dependencies, and build settings.
#
# @param NAME
# @param NAMESPACE
function(cpp_library)
    set(options "")
    set(oneValueArgs
        NAME
        NAMESPACE
    )
    set(multiValueArgs "")
    cmake_parse_arguments(arg_cpp_lib "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library(${arg_cpp_lib_NAME} INTERFACE)
    target_include_directories(
        ${arg_cpp_lib_NAME}
        INTERFACE
            "$<BUILD_INTERFACE:${CPP_LIB_BUILD_INTERFACE}>"
            "$<INSTALL_INTERFACE:${CPP_LIB_INSTALL_INTERFACE}>"
    )
    target_compile_features(${arg_cpp_lib_NAME} INTERFACE cxx_std_20)
    add_library(${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME} ALIAS ${arg_cpp_lib_NAME})
endfunction()
