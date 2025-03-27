cpp_library(
    NAME io_interface
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        ErrorCode.hpp
        ReaderInterface.hpp
        WriterInterface.hpp
    PRIVATE_SOURCES
        ErrorCode.cpp
        ReaderInterface.cpp
        StreamInterface.hpp
    PUBLIC_LINK_LIBRARIES
        ystdlib::error_handling
    TESTS_SOURCES
        test/test_ReaderInterface.cpp
        test/test_WriterInterface.cpp
)
