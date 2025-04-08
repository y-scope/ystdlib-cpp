cpp_library(
    NAME wrapped_facade_headers
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        bits/types/clock_t.h
        bits/types/time_t.h
        sys/types.h
    TESTS_SOURCES
        test/test_bits_types_clock_t.cpp
        test/test_bits_types_time_t.cpp
        test/test_sys_types.cpp
)
