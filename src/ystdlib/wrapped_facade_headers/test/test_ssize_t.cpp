#include <sys/types.h>

#include <catch2/catch_test_macros.hpp>

namespace ystdlib::wrapped_facade_headers::test {
TEST_CASE("test_ssize_t", "[wrapped_facade_headers][ssize_t]") {
    ssize_t const i{0};
    REQUIRE((0 == i));
}
}  // namespace ystdlib::wrapped_facade_headers::test
