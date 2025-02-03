#ifndef YSTDLIB_TESTLIB_HELLO_HPP
#define YSTDLIB_TESTLIB_HELLO_HPP

#include <string>

namespace ystdlib::testlib {
[[nodiscard]] inline auto hello() -> std::string {
    return "Hello, world!";
}
}  // namespace ystdlib::testlib

#endif  // YSTDLIB_TESTLIB_HELLO_HPP
