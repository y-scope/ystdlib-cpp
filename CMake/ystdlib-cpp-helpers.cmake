# check_if_header_only_library()
#
# @param source_list_var The list of source files that a target library uses
# @param is_header_only_var Returns whether the target library only contains header files
function(check_if_header_only_library source_list_var is_header_only_var)
  set(local_source_list "${${source_list_var}}")
  foreach(src_file IN LISTS local_source_list)
    if(${src_file} MATCHES ".*\\.(h|inc)")
      list(REMOVE_ITEM local_source_list "${src_file}")
    endif()
  endforeach()

  if(local_source_list STREQUAL "")
    set(${is_header_only_var} 1 PARENT_SCOPE)
  else()
    set(${is_header_only_var} 0 PARENT_SCOPE)
  endif()
endfunction()

# ystdlib_cpp_library()
#
# CMake function to imitate Bazel's cc_library rule.
#
# Parameters:
# NAME: name of the target
# HDRS: List of public header files for the library
# SRCS: List of source files for the library
# DEPS: List of other libraries to be linked in to the binary targets
function(ystdlib_cpp_library)
  set(options "")
  set(oneValueArgs NAME)
  set(multiValueArgs HDRS SRCS DEPS)
  cmake_parse_arguments(arg_ystdlib_cpp_lib
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

  check_if_header_only_library(arg_ystdlib_cpp_lib_SRCS _TARGET_LIB_IS_INTERFACE)

  if (_TARGET_LIB_IS_INTERFACE)
    add_library(${_TARGET_LIB_NAME} INTERFACE)
    target_include_directories(${_TARGET_LIB_NAME} INTERFACE
      "$<BUILD_INTERFACE:${YSTDLIB_CPP_BUILD_INCLUDE_DIRS}>"
      "$<INSTALL_INTERFACE:${YSTDLIB_CPP_INSTALL_INCLUDE_DIRS}>"
    )
  else()
    message(FATAL_ERROR "Non-interface library is currently not supported.")
  endif()

  target_link_libraries(${_TARGET_LIB_NAME}
    PUBLIC ${arg_ystdlib_cpp_lib_DEPS}
  )

  add_library(ystdlib::${arg_ystdlib_cpp_lib_NAME} ALIAS ${_TARGET_LIB_NAME})

  if(YSTDLIB_CPP_ENABLE_INSTALL)
    install(
      FILES ${arg_ystdlib_cpp_lib_HDRS}
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/ystdlib/${arg_ystdlib_cpp_lib_NAME}"
    )
    install(TARGETS ${_TARGET_LIB_NAME}
        EXPORT ${TARGET_EXPORT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
  endif()
endfunction()
