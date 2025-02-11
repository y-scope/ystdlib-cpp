#define CATCH_CONFIG_MAIN

#include <concepts>
#include <iostream>

#include <catch2/catch_all.hpp>
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
