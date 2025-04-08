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
#if defined(__linux__)
    REQUIRE(0 == i.__val[0]);
    REQUIRE(0 == i.__val[1]);
#elif defined(__APPLE__)
    REQUIRE(0 == i.val[0]);
    REQUIRE(0 == i.val[1]);
#endif
}

TEST_CASE("test_sys_types_ino_t", "[wrapped_facade_headers][sys_types][ino_t]") {
    ino_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_ino64_t", "[wrapped_facade_headers][sys_types][ino64_t]") {
    ino64_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_dev_t", "[wrapped_facade_headers][sys_types][dev_t]") {
    dev_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_gid_t", "[wrapped_facade_headers][sys_types][gid_t]") {
    gid_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_mode_t", "[wrapped_facade_headers][sys_types][mode_t]") {
    mode_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_nlink_t", "[wrapped_facade_headers][sys_types][nlink_t]") {
    nlink_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_uid_t", "[wrapped_facade_headers][sys_types][uid_t]") {
    uid_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_off_t", "[wrapped_facade_headers][sys_types][off_t]") {
    off_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_pid_t", "[wrapped_facade_headers][sys_types][pid_t]") {
    pid_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_id_t", "[wrapped_facade_headers][sys_types][id_t]") {
    id_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_ssize_t", "[wrapped_facade_headers][sys_types][ssize_t]") {
    ssize_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_daddr_t", "[wrapped_facade_headers][sys_types][daddr_t]") {
    daddr_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_caddr_t", "[wrapped_facade_headers][sys_types][caddr_t]") {
    // NOLINTNEXTLINE(misc-misplaced-const)
    caddr_t const p{nullptr};
    REQUIRE(nullptr == p);
}

TEST_CASE("test_sys_types_key_t", "[wrapped_facade_headers][sys_types][key_t]") {
    key_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_useconds_t", "[wrapped_facade_headers][sys_types][useconds_t]") {
    useconds_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_suseconds_t", "[wrapped_facade_headers][sys_types][suseconds_t]") {
    suseconds_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_int8_t", "[wrapped_facade_headers][sys_types][u_int8_t]") {
    u_int8_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_int16_t", "[wrapped_facade_headers][sys_types][u_int16_t]") {
    u_int16_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_int32_t", "[wrapped_facade_headers][sys_types][u_int32_t]") {
    u_int32_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_u_int64_t", "[wrapped_facade_headers][sys_types][u_int64_t]") {
    u_int64_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_blksize_t", "[wrapped_facade_headers][sys_types][blksize_t]") {
    blksize_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_blkcnt_t", "[wrapped_facade_headers][sys_types][blkcnt_t]") {
    blkcnt_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_fsblkcnt_t", "[wrapped_facade_headers][sys_types][fsblkcnt_t]") {
    fsblkcnt_t const i{0};
    REQUIRE(0 == i);
}

TEST_CASE("test_sys_types_fsfilcnt_t", "[wrapped_facade_headers][sys_types][fsfilcnt_t]") {
    fsfilcnt_t const i{0};
    REQUIRE(0 == i);
}
}  // namespace ystdlib::wrapped_facade_headers::test
