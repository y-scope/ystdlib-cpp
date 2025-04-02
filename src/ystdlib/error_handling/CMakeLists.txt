cpp_library(
    NAME error_handling
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        ErrorCode.hpp
        Result.hpp
    PUBLIC_LINK_LIBRARIES
        outcome::hl
    TESTS_SOURCES
        test/constants.hpp
        test/test_ErrorCode.cpp
        test/test_Result.cpp
        test/types.cpp
        test/types.hpp
)
