cpp_library(
    NAME wrapped_facade_headers
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        sys/types.h
    TESTS_SOURCES
        test/test_bits_types_clock_t.cpp
        test/test_bits_types_clockid_t.cpp
        test/test_bits_types_time_t.cpp
        test/test_sys_types.cpp
)
