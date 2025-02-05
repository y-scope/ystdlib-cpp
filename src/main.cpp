#include <concepts>
#include <iostream>
#include <ystdlib/testlib/hello.hpp>

namespace {
template <typename T>
requires std::integral<T>
[[nodiscard]] auto square(T x) -> T {
    return x * x;
}
};  // namespace

[[nodiscard]] auto main() -> int {
    std::cout << square(ystdlib::testlib::hello().size()) << '\n';
    return 0;
}
