cpp_library(
    NAME wrapped_facade_headers
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        sys/types.h
    TESTS_SOURCES
        test/test_sys_types.cpp
)
