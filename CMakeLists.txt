cmake_minimum_required(VERSION 3.16.3)
project(YSTDLIB_CPP LANGUAGES CXX)

set(YSTDLIB_CPP_VERSION "0.0.1" CACHE STRING "Project version.")

# When ystdlib-cpp is included as subproject (i.e. using add_subdirectory(ystdlib-cpp)) in the
# source tree of a project that uses it, installation rules are disabled.
if(NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    option(YSTDLIB_CPP_ENABLE_INSTALL "Enable installation rules" OFF)
else()
    option(YSTDLIB_CPP_ENABLE_INSTALL "Enable installation rules" ON)
endif()
