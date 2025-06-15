if(NOT YSTDLIB_LIBRARIES)
    message(FATAL_ERROR "YSTDLIB_LIBRARIES must be defined and non-empty.")
endif()

foreach(lib IN LISTS YSTDLIB_LIBRARIES)
    add_subdirectory("${lib}")
endforeach()
