cpp_library(
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
    TESTS_SOURCES
        test/test_ReaderInterface.cpp
        test/test_WriterInterface.cpp
)
