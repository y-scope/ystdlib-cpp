#include <ystdlib/wrapped_facade_headers/bits/types/time_t.h>

#include <catch2/catch_test_macros.hpp>

namespace ystdlib::wrapped_facade_headers::test {
TEST_CASE("test_bits_types_time_t", "[wrapped_facade_headers][bits_types][time_t]") {
    time_t const i{0};
    REQUIRE(0 == i);
}
}  // namespace ystdlib::wrapped_facade_headers::test

