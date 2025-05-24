#include <memory>
#include <system_error>
#include <type_traits>

#include <ystdlib/error_handling/Result.hpp>

#include <catch2/catch_test_macros.hpp>

#include "types.hpp"

using ystdlib::error_handling::Result;
using ystdlib::error_handling::success;
using ystdlib::error_handling::test::AlwaysSuccessErrorCode;
using ystdlib::error_handling::test::AlwaysSuccessErrorCodeEnum;
using ystdlib::error_handling::test::BinaryErrorCode;
using ystdlib::error_handling::test::BinaryErrorCodeEnum;

namespace {
constexpr int cTestInt{123};
constexpr auto cVoidFunc = [](bool is_error) -> Result<void> {
    if (is_error) {
        return BinaryErrorCode{BinaryErrorCodeEnum::Failure};
    }
    return success();
};
constexpr auto cIntFunc = [](bool is_error) -> Result<int> {
    if (is_error) {
        return std::errc::bad_message;
    }
    return cTestInt;
};
constexpr auto cUniquePtrFunc = [](bool is_error) -> Result<std::unique_ptr<int>> {
    if (is_error) {
        return AlwaysSuccessErrorCode{AlwaysSuccessErrorCodeEnum::Success};
    }
    return std::make_unique<int>(cTestInt);
};
}  // namespace

namespace ystdlib::error_handling::test {
TEST_CASE("test_result_void", "[error_handling][Result]") {
    auto const result_no_error{cVoidFunc(false)};
    REQUIRE_FALSE(result_no_error.has_error());
    REQUIRE(std::is_void_v<decltype(result_no_error.value())>);

    auto const result_has_error{cVoidFunc(true)};
    REQUIRE(result_has_error.has_error());
    REQUIRE(BinaryErrorCode{BinaryErrorCodeEnum::Failure} == result_has_error.error());
}

TEST_CASE("test_result_void_in_main", "[error_handling][Result]") {
    auto main_func = [&](bool is_error) -> Result<void> {
        YSTDLIB_ERROR_HANDLING_TRYV(cVoidFunc(is_error));
        return success();
    };
    auto const main_no_error{main_func(false)};
    REQUIRE_FALSE(main_no_error.has_error());
    REQUIRE(std::is_void_v<decltype(main_no_error.value())>);

    auto const main_has_error{main_func(true)};
    REQUIRE(main_has_error.has_error());
    REQUIRE(BinaryErrorCode{BinaryErrorCodeEnum::Failure} == main_has_error.error());
}

TEST_CASE("test_result_int", "[error_handling][Result]") {
    auto const result_no_error{cIntFunc(false)};
    REQUIRE_FALSE(result_no_error.has_error());
    REQUIRE(cTestInt == result_no_error.value());

    auto const result_has_error{cIntFunc(true)};
    REQUIRE(result_has_error.has_error());
    REQUIRE(std::errc::bad_message == result_has_error.error());
}

TEST_CASE("test_result_int_in_main", "[error_handling][Result]") {
    auto main_func = [&](bool is_error) -> Result<void> {
        YSTDLIB_ERROR_HANDLING_TRYV(cIntFunc(is_error));
        return success();
    };
    auto const main_no_error{main_func(false)};
    REQUIRE_FALSE(main_no_error.has_error());
    REQUIRE(std::is_void_v<decltype(main_no_error.value())>);

    auto const main_has_error{main_func(true)};
    REQUIRE(main_has_error.has_error());
    REQUIRE(std::errc::bad_message == main_has_error.error());
}

TEST_CASE("test_result_int_propagate", "[error_handling][Result]") {
    auto main_func = [&](bool is_error) -> Result<int> {
        return YSTDLIB_ERROR_HANDLING_TRYX(cIntFunc(is_error));
    };
    auto const main_no_error{main_func(false)};
    REQUIRE_FALSE(main_no_error.has_error());
    REQUIRE(cTestInt == main_no_error.value());

    auto const main_has_error{main_func(true)};
    REQUIRE(main_has_error.has_error());
    REQUIRE(std::errc::bad_message == main_has_error.error());
}

TEST_CASE("test_result_unique_ptr", "[error_handling][Result]") {
    auto const result_no_error{cUniquePtrFunc(false)};
    REQUIRE_FALSE(result_no_error.has_error());
    REQUIRE(cTestInt == *(result_no_error.value()));

    auto const result_has_error{cUniquePtrFunc(true)};
    REQUIRE(result_has_error.has_error());
    REQUIRE(AlwaysSuccessErrorCode{AlwaysSuccessErrorCodeEnum::Success}
            == result_has_error.error());
}

TEST_CASE("test_result_unique_ptr_in_main", "[error_handling][Result]") {
    auto main_func = [&](bool is_error) -> Result<void> {
        YSTDLIB_ERROR_HANDLING_TRYV(cUniquePtrFunc(is_error));
        return success();
    };
    auto const main_no_error{main_func(false)};
    REQUIRE_FALSE(main_no_error.has_error());
    REQUIRE(std::is_void_v<decltype(main_no_error.value())>);

    auto const main_has_error{main_func(true)};
    REQUIRE(main_has_error.has_error());
    REQUIRE(AlwaysSuccessErrorCode{AlwaysSuccessErrorCodeEnum::Success} == main_has_error.error());
}

TEST_CASE("test_result_unique_ptr_propagate", "[error_handling][Result]") {
    auto main_func = [&](bool is_error) -> Result<std::unique_ptr<int>> {
        return YSTDLIB_ERROR_HANDLING_TRYX(cUniquePtrFunc(is_error));
    };
    auto const main_no_error{main_func(false)};
    REQUIRE_FALSE(main_no_error.has_error());
    REQUIRE(cTestInt == *(main_no_error.value()));

    auto const main_has_error{main_func(true)};
    REQUIRE(main_has_error.has_error());
    REQUIRE(AlwaysSuccessErrorCode{AlwaysSuccessErrorCodeEnum::Success} == main_has_error.error());
}
}  // namespace ystdlib::error_handling::test
