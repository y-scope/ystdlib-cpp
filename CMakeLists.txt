cmake_minimum_required(VERSION 3.16.3)

list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_LIST_DIR}/CMake"
)
include(ystdlib-cpp-helpers)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Package information
set(PKG_NAME "ystdlib-cpp")
set(PKG_VERS "0.0.1")
set(PKG_STR "${PKG_NAME}-${PKG_VERS}")
set(TARGET_EXPORT_NAME "${PKG_NAME}-targets")
set(PKG_CONF_NAME "${PKG_NAME}-config")
set(PKG_CONF_VERS_NAME "${PKG_NAME}-config-version")

project(${PKG_NAME} LANGUAGES CXX)

# Static everything for now
option(BUILD_SHARED_LIBS OFF)
option(YSTDLIB_CPP_USE_STATIC_LIBS ON)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  message(STATUS "setting C++ standard to C++${CMAKE_CXX_STANDARD}")
endif()

if(NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  option(YSTDLIB_CPP_ENABLE_INSTALL "${PKG_NAME} is the master project. Enable installation." OFF)
else()
  option(YSTDLIB_CPP_ENABLE_INSTALL "${PKG_NAME} is the master project. Enable installation." ON)
endif()

# All paths are relative to CMAKE_INSTALL_PREFIX
set(CMAKE_INSTALL_LIBDIR "lib")
set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_INCLUDEDIR "include/${PKG_STR}")
set(CMAKE_INSTALL_PKGCONFDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PKG_STR}")

list(APPEND YSTDLIB_CPP_BUILD_INCLUDE_DIRS
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_SOURCE_DIR}/submodules"
)

if(YSTDLIB_CPP_ENABLE_INSTALL)
    list(APPEND YSTDLIB_CPP_INSTALL_INCLUDE_DIRS ${CMAKE_INSTALL_INCLUDEDIR})
else()
    list(APPEND YSTDLIB_CPP_INSTALL_INCLUDE_DIRS ${YSTDLIB_CPP_BUILD_INCLUDE_DIRS})
endif()

add_subdirectory(ystdlib)

if(YSTDLIB_CPP_ENABLE_INSTALL)
  include(CMakePackageConfigHelpers)

  install(EXPORT ${TARGET_EXPORT_NAME}
    FILE ${TARGET_EXPORT_NAME}.cmake
    NAMESPACE ystdlib::
    DESTINATION ${CMAKE_INSTALL_PKGCONFDIR}
  )
  configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/CMake/${PKG_CONF_NAME}.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PKG_CONF_NAME}.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_PKGCONFDIR}
  )
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PKG_CONF_VERS_NAME}.cmake"
    VERSION ${PKG_VERS}
    COMPATIBILITY AnyNewerVersion
  )
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PKG_CONF_NAME}.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PKG_CONF_VERS_NAME}.cmake"
    DESTINATION ${CMAKE_INSTALL_PKGCONFDIR}
  )
endif()
