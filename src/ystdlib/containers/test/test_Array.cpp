#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <ystdlib/containers/Array.hpp>

#include <catch2/catch_test_macros.hpp>

namespace {
constexpr size_t cBufferSize{1024};

class NoDefault {
public:
    NoDefault(size_t n) : m_n{n} {}

    [[nodiscard]] auto get() const -> size_t { return m_n; }

private:
    size_t m_n;
};

class VarietyConstructors {
public:
    static constexpr size_t cDefault = 3190;

    VarietyConstructors() = default;

    VarietyConstructors(size_t n) : m_n{n} {}

    VarietyConstructors(std::string const& s) : m_n{s.size()} {}

    VarietyConstructors(NoDefault const& nd) : m_n{nd.get()} {}

    [[nodiscard]] auto get() const -> size_t { return m_n; }

private:
    size_t m_n{cDefault};
};

void test_function_argument_list_initialization(
        ystdlib::container::Array<VarietyConstructors> const& arr,
        std::vector<size_t> const& data
) {
    REQUIRE(std::ranges::equal(
            arr | std::views::transform([](auto const& obj) { return obj.get(); }),
            data
    ));
}
}  // namespace

namespace ystdlib::container::test {
TEST_CASE("test_empty_array", "[container][Array]") {
    Array<int> arr(0);
    REQUIRE(arr.empty());
    // NOLINTNEXTLINE(readability-container-size-empty)
    REQUIRE((0 == arr.size()));
    REQUIRE((arr.begin() == arr.end()));
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("test_array_basic", "[container][Array]") {
    std::vector<int> vec;
    for (int i{0}; i < cBufferSize; ++i) {
        vec.push_back(i);
    }

    Array<int> arr(cBufferSize);
    auto const& arr_const_ref = arr;
    std::ranges::copy(vec, arr.begin());

    REQUIRE(std::ranges::equal(vec, arr));
    REQUIRE(std::ranges::equal(vec, arr_const_ref));

    REQUIRE_THROWS(arr.at(cBufferSize));
    REQUIRE_THROWS(arr_const_ref.at(cBufferSize));

    auto const arr_moved{std::move(arr)};
    REQUIRE(std::ranges::equal(vec, arr_moved));
    REQUIRE_THROWS(arr_moved.at(cBufferSize));
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("test_array_default_initialization", "[container][Array]") {
    Array<int> int_arr(cBufferSize);
    auto const& int_arr_const_ref = int_arr;

    REQUIRE(std::is_fundamental_v<int>);
    std::ranges::for_each(int_arr, [](auto const& i) -> void { REQUIRE((0 == i)); });
    std::ranges::for_each(int_arr_const_ref, [](auto const& i) -> void { REQUIRE((0 == i)); });

    Array<std::nullptr_t> ptr_arr(cBufferSize);
    auto const& ptr_arr_const_ref = ptr_arr;

    REQUIRE(std::is_fundamental_v<std::nullptr_t>);
    std::ranges::for_each(ptr_arr, [](auto const& p) -> void { REQUIRE((nullptr == p)); });
    std::ranges::for_each(ptr_arr_const_ref, [](auto const& p) -> void {
        REQUIRE((nullptr == p));
    });
}

TEST_CASE("test_array_list_initialization_basic", "[container][Array]") {
    std::vector<std::string> const
            vec{"yscope", "clp", "ystdlib", "ystdlib::container::Array", "default_initializable"};
    Array<std::string> const
            arr0{"yscope", "clp", "ystdlib", "ystdlib::container::Array", "default_initializable"};
    Array<std::string> const arr1
            = {"yscope", "clp", "ystdlib", "ystdlib::container::Array", "default_initializable"};
    REQUIRE(std::ranges::equal(vec, arr0));
    REQUIRE(std::ranges::equal(vec, arr1));
}

TEST_CASE("test_array_list_initialization_variety_constructors", "[container][Array]") {
    constexpr size_t cTestNum0{344};
    constexpr size_t cTestNum1{454};
    constexpr std::string_view cTestStr{"yscope"};

    Array<VarietyConstructors> const arr
            = {VarietyConstructors{}, cTestNum0, std::string{cTestStr}, NoDefault{cTestNum1}};
    std::vector<size_t> const data
            = {VarietyConstructors::cDefault, cTestNum0, cTestStr.size(), cTestNum1};
    REQUIRE(std::ranges::equal(
            arr | std::views::transform([](auto const& obj) { return obj.get(); }),
            data
    ));
    test_function_argument_list_initialization(
            {VarietyConstructors{}, cTestNum0, std::string{cTestStr}, NoDefault{cTestNum1}},
            data
    );
}
}  // namespace ystdlib::container::test
