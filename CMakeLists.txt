cmake_minimum_required(VERSION 3.16.3)
project(YSTDLIB_CPP LANGUAGES CXX)

# Static everything for now
option(BUILD_SHARED_LIBS OFF)
option(YSTDLIB_CPP_USE_STATIC_LIBS ON)
unset(YSTDLIB_CPP_SOVERSION)

set(YSTDLIB_CPP_VERSION "0.0.1" CACHE STRING "Project version.")

# When ystdlib-cpp is included as subproject (i.e. using add_subdirectory(ystdlib-cpp)) in the
# source tree of a project that uses it, install rules are disabled.
if(NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    option(YSTDLIB_CPP_ENABLE_INSTALL "Enable installation rules" OFF)
else()
    option(YSTDLIB_CPP_ENABLE_INSTALL "Enable installation rules" ON)
endif()

# Enable exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL
    "Enable/Disable output of compile commands during generation."
    FORCE
)

# Configure include paths for building ystdlib-cpp.
list(APPEND YSTDLIB_CPP_BUILD_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src)

# Configure include paths for projects using ystdlib-cpp after it has been installed.
if(YSTDLIB_CPP_ENABLE_INSTALL)
    message(WARNING "Currently only supports using ystdlib-cpp as a subdirectory to a project.")
    list(APPEND YSTDLIB_CPP_INSTALL_INCLUDE_DIRS ${YSTDLIB_CPP_BUILD_INCLUDE_DIRS})
else()
    list(APPEND YSTDLIB_CPP_INSTALL_INCLUDE_DIRS ${YSTDLIB_CPP_BUILD_INCLUDE_DIRS})
endif()

# Import CMake helper functions
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
include(ystdlib-cpp-helpers)

add_subdirectory(src/ystdlib)

# Test dummy project
add_executable(dummy)
target_sources(dummy PRIVATE src/ystdlib/hello.cpp)
target_link_libraries(dummy PRIVATE ystdlib::array)
target_compile_features(dummy PRIVATE cxx_std_20)
