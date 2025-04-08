#include <ystdlib/wrapped_facade_headers/bits/types/clock_t.h>

#include <catch2/catch_test_macros.hpp>

namespace ystdlib::wrapped_facade_headers::test {
TEST_CASE("test_bits_types_clock_t", "[wrapped_facade_headers][bits_types][clock_t]") {
    clock_t const i{0};
    REQUIRE(0 == i);
}
}  // namespace ystdlib::wrapped_facade_headers::test
