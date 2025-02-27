#include <algorithm>
#include <cstddef>
#include <vector>
#include <utility>

#include <ystdlib/container/Array.hpp>

#include <catch2/catch_test_macros.hpp>

namespace ystdlib::container::test {
TEST_CASE("test_empty_array", "[container][Array]") {
    Array<int> arr{0};
    REQUIRE(arr.empty());
    // NOLINTNEXTLINE(readability-container-size-empty)
    REQUIRE((0 == arr.size()));
    REQUIRE((arr.begin() == arr.end()));
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("test_array_fundamental", "[container][Array]") {
    constexpr size_t cBufferSize{1024};

    std::vector<int> vec;
    for (int i{0}; i < cBufferSize; ++i) {
        vec.push_back(i);
    }

    Array<int> arr{cBufferSize};
    auto const& arr_const_ref = arr;
    std::ranges::for_each(arr_const_ref, [](int i) -> void { REQUIRE((0 == i)); });

    std::ranges::copy(vec, arr.begin());
    REQUIRE(std::ranges::equal(vec, arr));
    REQUIRE(std::ranges::equal(vec, arr_const_ref));
    REQUIRE_THROWS(arr.at(cBufferSize));
    REQUIRE_THROWS(arr_const_ref.at(cBufferSize));

    auto const arr_moved{std::move(arr)};
    REQUIRE(std::ranges::equal(vec, arr_moved));
    REQUIRE_THROWS(arr_moved.at(cBufferSize));
}
}  // namespace ystdlib::container::test
