if(TARGET ystdlib::io_interface)
    return()
endif()

if(NOT wrapped_facade_headers IN_LIST ystdlib_LIBRARIES)
    add_subdirectory(
        "${CMAKE_CURRENT_LIST_DIR}/../wrapped_facade_headers"
        "${CMAKE_CURRENT_BINARY_DIR}/implicit_dep/wrapped_facade_headers"
    )
endif()

add_cpp_library(
    NAME io_interface
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        ErrorCode.hpp
        ReaderInterface.hpp
        WriterInterface.hpp
    PRIVATE_SOURCES
        ReaderInterface.cpp
    PUBLIC_LINK_LIBRARIES
        ystdlib::wrapped_facade_headers
)

if(ystdlib_ENABLE_TESTS)
    add_catch2_tests(
        NAME io_interface
        NAMESPACE ystdlib
        SOURCES
            test/test_ReaderInterface.cpp
            test/test_WriterInterface.cpp
        UNIFIED_TEST_TARGET "${UNIFIED_UNIT_TEST_TARGET}"
    )
endif()

install_library(NAME io_interface NAMESPACE ystdlib)
