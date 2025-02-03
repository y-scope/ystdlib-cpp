# Set up include paths for building the project and for external projects that incorporate this
# project using the add_subdirectory() function.
set(CPP_LIB_BUILD_INTERFACE "${PROJECT_SOURCE_DIR}/src")

# Adds a c++20 interface library in the subdirectory NAME with the target NAME and alias
# NAMESPACE::NAME. Libraries with multiple levels of namespace nesting are currently not supported.
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
    )
    target_compile_features(${arg_cpp_lib_NAME} INTERFACE cxx_std_20)
    add_library(${arg_cpp_lib_NAMESPACE}::${arg_cpp_lib_NAME} ALIAS ${arg_cpp_lib_NAME})
endfunction()
