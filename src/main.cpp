#include <iostream>
#include <vector>
#include <ystdlib/testlib/hello.hpp>

[[nodiscard]] auto main() -> int {
    constexpr std::vector<int> cV;
    std::cout << ystdlib::testlib::hello() << '\n';
    return 0;
}
