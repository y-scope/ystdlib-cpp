#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <concepts>
#include <ystdlib/testlib/hello.hpp>

namespace {
template <typename T>
requires std::integral<T>
[[nodiscard]] auto square(T x) -> T {
    return x * x;
}
};  // namespace

TEST_CASE("dummy") {
    REQUIRE((169 == square(ystdlib::testlib::hello().size())));
}
