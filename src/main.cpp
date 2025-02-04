#include <iostream>
// #include <vector>
#include <ystdlib/testlib/hello.hpp>

[[nodiscard]] auto main() -> int {
    // constexpr std::vector<int> cV;
    std::cout << ystdlib::testlib::hello() << '\n';
    constexpr auto c23{202'101L};
    constexpr auto c20{202'002L};
    constexpr auto c17{201'703L};
    constexpr auto c14{201'402L};
    constexpr auto c11{201'103L};
    constexpr auto c98{199'711L};
    if (__cplusplus == c23) {
        std::cout << "C++23";
    } else if (__cplusplus == c20) {
        std::cout << "C++20";
    } else if (__cplusplus == c17) {
        std::cout << "C++17";
    } else if (__cplusplus == c14) {
        std::cout << "C++14";
    } else if (__cplusplus == c11) {
        std::cout << "C++11";
    } else if (__cplusplus == c98) {
        std::cout << "C++98";
    } else {
        std::cout << "pre-standard C++." << __cplusplus;
    }
    std::cout << "\n";
    return 0;
}
