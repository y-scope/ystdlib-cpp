#include <algorithm>
#include <concepts>
#include <cstddef>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <ystdlib/containers/Array.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

namespace {
constexpr size_t cBufferSize{1024};

/**
 * A class that requires an explicit argument for construction and disables the default constructor.
 *
 * Includes a data member `m_value` and an accessor function to verify successful initialization.
 */
class ExplicitConstructor {
public:
    ExplicitConstructor() = delete;

    ExplicitConstructor(size_t value) : m_value{value} {}

    [[nodiscard]] auto get_value() const -> size_t { return m_value; }

private:
    size_t m_value;
};

/**
 * A class that supports multiple initialization methods.
 *
 * This class is used to test `Array` list initialization with various constructor argument types.
 * It includes a data member `m_value` and an accessor function to verify successful initialization.
 */
class PolymorphicConstructors {
public:
    static constexpr size_t cDefaultValue = 3190;

    PolymorphicConstructors() = default;

    PolymorphicConstructors(size_t value) : m_value{value} {}

    PolymorphicConstructors(std::string const& s) : m_value{s.size()} {}

    PolymorphicConstructors(ExplicitConstructor const& obj) : m_value{obj.get_value()} {}

    [[nodiscard]] auto get_value() const -> size_t { return m_value; }

private:
    size_t m_value{cDefaultValue};
};

/**
 * Tests whether list initialization works correctly for `Array` when an initializer list is passed
 * as a function argument.
 */
void test_list_initialization_in_function_call(
        ystdlib::containers::Array<PolymorphicConstructors> const& arr,
        std::vector<size_t> const& data
) {
    REQUIRE(std::ranges::equal(
            arr | std::views::transform([](auto const& obj) { return obj.get_value(); }),
            data
    ));
}
}  // namespace

namespace ystdlib::containers::test {
TEST_CASE("test_array_empty", "[containers][Array]") {
    Array<size_t> arr(0);
    REQUIRE(arr.empty());
    // NOLINTNEXTLINE(readability-container-size-empty)
    REQUIRE((0 == arr.size()));
    REQUIRE((arr.begin() == arr.end()));
}

TEST_CASE("test_array_reference", "[containers][Array]") {
    Array<size_t> arr(cBufferSize);
    for (size_t idx{0}; idx < cBufferSize; ++idx) {
        arr.at(idx) = idx;
    }
    auto const& arr_const_ref = arr;
    REQUIRE(std::ranges::equal(arr, arr_const_ref));
}

TEST_CASE("test_array_ranged_copy", "[containers][Array]") {
    std::vector<size_t> vec;
    for (size_t idx{0}; idx < cBufferSize; ++idx) {
        vec.push_back(idx);
    }
    Array<size_t> arr(cBufferSize);
    std::ranges::copy(vec, arr.begin());
    REQUIRE(std::ranges::equal(vec, arr));
}

TEST_CASE("test_array_movable", "[containers][Array]") {
    Array<size_t> arr(cBufferSize);
    Array<size_t> reference_array(cBufferSize);
    for (size_t idx{0}; idx < cBufferSize; ++idx) {
        arr.at(idx) = idx;
        reference_array.at(idx) = idx;
    }
    auto const arr_moved{std::move(arr)};
    REQUIRE(std::ranges::equal(reference_array, arr_moved));
}

TEST_CASE("test_array_illegal_access", "[containers][Array]") {
    Array<size_t> arr(cBufferSize);
    REQUIRE_THROWS_AS(arr.at(-1), std::out_of_range);
    REQUIRE_THROWS_AS(arr.at(cBufferSize), std::out_of_range);
}

TEMPLATE_TEST_CASE(
        "test_array_fundamental_type_value_initialization",
        "[containers][Array]",
        bool,
        char,
        signed char,
        unsigned char,
        wchar_t,
        char16_t,
        char32_t,
        short,
        unsigned short,
        int,
        unsigned int,
        long,
        unsigned long,
        long long,
        unsigned long long,
        float,
        double,
        long double,
        std::nullptr_t
) {
    REQUIRE(std::is_fundamental_v<TestType>);
    Array<TestType> arr(cBufferSize);
    std::ranges::for_each(arr, [](auto const& p) -> void {
        REQUIRE((static_cast<TestType>(0) == p));
    });
}

TEST_CASE("test_array_list_initialization", "[containers][Array]") {
    constexpr size_t cTestNum0{344};
    constexpr size_t cTestNum1{454};
    constexpr std::string_view cTestStr{"yscope"};

    // Test basic list initialization
    std::vector<std::string> const
            vec{"yscope", "clp", "ystdlib", "ystdlib::containers::Array", "default_initializable"};
    Array<std::string> const
            arr{"yscope", "clp", "ystdlib", "ystdlib::containers::Array", "default_initializable"};
    REQUIRE(std::ranges::equal(vec, arr));

    // Test polymorphic list initialization
    REQUIRE(std::is_copy_constructible_v<PolymorphicConstructors>);

    // Expected values to verify correct initialization of `PolymorphicConstructors`.
    // See the `PolymorphicConstructors` class for details on how constructor arguments are handled.
    std::vector<size_t> const data
            = {PolymorphicConstructors::cDefaultValue, cTestNum0, cTestStr.size(), cTestNum1};

    SECTION("Local variable") {
        Array<PolymorphicConstructors> const list_init_arr
                = {PolymorphicConstructors{},
                   cTestNum0,
                   std::string{cTestStr},
                   ExplicitConstructor{cTestNum1}};
        REQUIRE(std::ranges::equal(
                list_init_arr
                        | std::views::transform([](auto const& obj) { return obj.get_value(); }),
                data
        ));
    }

    SECTION("Function argument passing") {
        test_list_initialization_in_function_call(
                {PolymorphicConstructors{},
                 cTestNum0,
                 std::string{cTestStr},
                 ExplicitConstructor{cTestNum1}},
                data
        );
    }

    // Test polymorphic list initialization with a non default-constructible class
    REQUIRE_FALSE(std::default_initializable<ExplicitConstructor>);
}
}  // namespace ystdlib::containers::test
