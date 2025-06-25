if(NOT DEFINED ystdlib_LIBRARIES OR ystdlib_LIBRARIES STREQUAL "")
    message(FATAL_ERROR "ystdlib_LIBRARIES must be defined and non-empty.")
endif()

foreach(LIB IN LISTS ystdlib_LIBRARIES)
    add_subdirectory("${LIB}")
endforeach()
