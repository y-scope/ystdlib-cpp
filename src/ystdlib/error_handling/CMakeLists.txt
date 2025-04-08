cpp_library(
    NAME error_handling
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        ErrorCode.hpp
        TraceableException.hpp
        utils.hpp
    TESTS_SOURCES
        test/constants.hpp
        test/test_ErrorCode.cpp
        test/test_TraceableException.cpp
        test/types.cpp
        test/types.hpp
)
