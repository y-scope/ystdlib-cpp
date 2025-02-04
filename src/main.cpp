#include <iostream>
#include <ystdlib/testlib/hello.hpp>
#include <ystdlib/testlib/math.hpp>

[[nodiscard]] auto main() -> int {
    std::cout << ystdlib::testlib::square(ystdlib::testlib::hello().size()) << '\n';
    return 0;
}
