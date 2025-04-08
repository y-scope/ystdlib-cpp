#include <ystdlib/wrapped_facade_headers/sys/types.h>

#include <catch2/catch_test_macros.hpp>

namespace ystdlib::wrapped_facade_headers::test {
TEST_CASE("test_sys_types_u_char", "[wrapped_facade_headers][sys_types][u_char]") {
    u_char const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_short", "[wrapped_facade_headers][sys_types][u_short]") {
    u_short const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_int", "[wrapped_facade_headers][sys_types][u_int]") {
    u_int const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_long", "[wrapped_facade_headers][sys_types][u_long]") {
    u_long const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_quad_t", "[wrapped_facade_headers][sys_types][quad_t]") {
    quad_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_quad_t", "[wrapped_facade_headers][sys_types][u_quad_t]") {
    u_quad_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_fsid_t", "[wrapped_facade_headers][sys_types][fsid_t]") {
    fsid_t const i{{0, 0}};
    REQUIRE(0 == i.__val[0]);
    REQUIRE(0 == i.__val[1]);
}

#if defined(__linux__)
TEST_CASE("test_sys_types_loff_t", "[wrapped_facade_headers][sys_types][loff_t]") {
    loff_t const i{0};
    REQUIRE(0 == i);
}
#endif
}  // namespace ystdlib::wrapped_facade_headers::test
