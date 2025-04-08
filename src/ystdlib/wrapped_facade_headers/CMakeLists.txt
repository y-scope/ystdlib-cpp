cpp_library(
    NAME wrapped_facade_headers
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        sys/types.h
    TESTS_SOURCES
        test/test_off_t.cpp
        test/test_ssize_t.cpp
)
