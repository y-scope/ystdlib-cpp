cmake_minimum_required(VERSION 3.22.1)

project(ystdlib-examples)

if(ystdlib-examples_IS_TOP_LEVEL)
    message("${CMAKE_SOURCE_DIR}/../build/deps/cmake-settings/settings.cmake")
    include("${CMAKE_SOURCE_DIR}/../build/deps/cmake-settings/settings.cmake" OPTIONAL)
endif()

set(ystdlib_ROOT "/home/john/docs/yscope/ystdlib-cpp/build/build_install")
find_package(ystdlib REQUIRED)

add_library(
    common
    OBJECT
    types.cpp
    types.hpp
    constants.hpp
)
target_link_libraries(common PUBLIC ystdlib::error_handling)
add_executable(main main.cpp)

get_target_property(_type ystdlib::error_handling TYPE)
get_target_property(_sources ystdlib::error_handling SOURCES)
get_target_property(_includes ystdlib::error_handling INCLUDE_DIRECTORIES)
get_target_property(_libs ystdlib::error_handling LINK_LIBRARIES)

message(STATUS "Target Type: ${_type}")
message(STATUS "Sources: ${_sources}")
message(STATUS "Include Dirs: ${_includes}")
message(STATUS "Linked Libraries: ${_libs}")

target_compile_features(main PRIVATE cxx_std_20)
target_compile_features(common PRIVATE cxx_std_20)

target_link_libraries(
    main
    PUBLIC
        ystdlib::error_handling
        common
)
