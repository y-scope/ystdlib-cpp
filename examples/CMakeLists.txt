cmake_minimum_required(VERSION 3.23)

project(ystdlib-examples)

include("${CMAKE_SOURCE_DIR}/../build/deps/cmake-settings/settings.cmake" REQUIRED)

if(NOT DEFINED ystdlib_ROOT)
    set(ystdlib_ROOT "${CMAKE_SOURCE_DIR}/../build/build_install")
endif()
find_package(ystdlib REQUIRED)


add_executable(main main.cpp)

target_compile_features(main PRIVATE cxx_std_20)

target_link_libraries(
    main
    PRIVATE
        ystdlib::error_handling
)
