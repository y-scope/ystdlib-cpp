cpp_library(
    NAME error_handling
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        ErrorCode.hpp
        TraceableException.hpp
        Result.hpp
        utils.hpp
    PUBLIC_LINK_LIBRARIES
        Boost::headers
    TESTS_SOURCES
        test/constants.hpp
        test/test_ErrorCode.cpp
        test/test_Result.cpp
        test/test_TraceableException.cpp
        test/types.cpp
        test/types.hpp
)
