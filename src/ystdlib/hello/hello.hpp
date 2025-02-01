#ifndef YSTDLIB_HELLO_HPP
#define YSTDLIB_HELLO_HPP

#include <string>

namespace ystdlib {
[[nodiscard]] inline auto hello() -> std::string {
    return "Hello, world!";
}
}  // namespace ystdlib

#endif  // YSTDLIB_HELLO_HPP
