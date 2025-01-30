#include <iostream>
#include <ystdlib/hello/hello.hpp>

[[nodiscard]] auto main() -> int {
    std::cout << ystdlib::hello() << '\n';
    return 0;
}
