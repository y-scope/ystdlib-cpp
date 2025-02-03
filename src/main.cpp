#include <iostream>
#include <ystdlib/testlib/hello.hpp>

[[nodiscard]] auto main() -> int {
    std::cout << ystdlib::testlib::hello() << '\n';
    return 0;
}
