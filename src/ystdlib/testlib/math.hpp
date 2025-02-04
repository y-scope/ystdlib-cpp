#ifndef YSTDLIB_TESTLIB_MATH_HPP
#define YSTDLIB_TESTLIB_MATH_HPP

#include <concepts>

namespace ystdlib::testlib {
template <typename T>
requires std::integral<T>
[[nodiscard]] inline auto square(T x) -> T {
    return x * x;
}
}  // namespace ystdlib::testlib

#endif  // YSTDLIB_TESTLIB_MATH_HPP
