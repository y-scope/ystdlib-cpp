cmake_minimum_required(VERSION 3.16.3)
project(YSTDLIB_CPP LANGUAGES CXX)

set(YSTDLIB_CPP_VERSION "0.0.1" CACHE STRING "Project version.")

add_executable(dummy)
target_sources(dummy PRIVATE ystdlib/hello.cpp)
target_compile_features(dummy PRIVATE cxx_std_20)
