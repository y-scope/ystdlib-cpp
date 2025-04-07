#include <ystdlib/wrapped_facade_headers/sys/types.h>

#include <catch2/catch_test_macros.hpp>

namespace ystdlib::wrapped_facade_headers::test {
TEST_CASE("test_off_t", "[wrapped_facade_headers][off_t]") {
    off_t const i{0};
    REQUIRE((0 == i));
}
}  // namespace ystdlib::wrapped_facade_headers::test
