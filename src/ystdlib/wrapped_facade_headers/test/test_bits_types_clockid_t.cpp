#include <bits/time.h>

#include <ystdlib/wrapped_facade_headers/bits/types/clockid_t.h>

#include <catch2/catch_test_macros.hpp>

namespace ystdlib::wrapped_facade_headers::test {
TEST_CASE("test_bits_types_clockid_t", "[wrapped_facade_headers][bits_types][clockid_t]") {
    clockid_t const i{CLOCK_REALTIME};
    REQUIRE(CLOCK_REALTIME == i);
}
}  // namespace ystdlib::wrapped_facade_headers::test
