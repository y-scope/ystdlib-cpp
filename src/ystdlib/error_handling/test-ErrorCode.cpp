#include <algorithm>
#include <array>
#include <string_view>
#include <system_error>
#include <type_traits>

#include <ystdlib/error_handling/ErrorCode.hpp>

#include <catch2/catch_test_macros.hpp>

#include "test-Defs.hpp"

TEST_CASE("test_error_code", "[error_handling][ErrorCode]") {
    // Test error codes within the same error category
    BinaryErrorCode const success{BinaryErrorCodeEnum::Success};
    std::error_code const success_error_code{success};
    REQUIRE((success == success_error_code));
    REQUIRE((cSuccessErrorMsg == success_error_code.message()));
    REQUIRE((BinaryErrorCode::get_category() == success_error_code.category()));
    REQUIRE((cBinaryTestErrorCategoryName == success_error_code.category().name()));

    BinaryErrorCode const failure{BinaryErrorCodeEnum::Failure};
    std::error_code const failure_error_code{failure};
    REQUIRE((failure == failure_error_code));
    REQUIRE((cFailureErrorMsg == failure_error_code.message()));
    REQUIRE((BinaryErrorCode::get_category() == failure_error_code.category()));
    REQUIRE((cBinaryTestErrorCategoryName == failure_error_code.category().name()));

    REQUIRE((success_error_code != failure_error_code));
    REQUIRE((success_error_code.category() == failure_error_code.category()));

    AlwaysSuccessErrorCode const always_success{AlwaysSuccessErrorCodeEnum::Success};
    std::error_code const always_success_error_code{always_success};
    REQUIRE((always_success_error_code == always_success));
    REQUIRE((cSuccessErrorMsg == always_success_error_code.message()));
    REQUIRE((AlwaysSuccessErrorCode::get_category() == always_success_error_code.category()));
    REQUIRE((cAlwaysSuccessErrorCategoryName == always_success_error_code.category().name()));

    // Compare error codes from different error category
    // Error codes that have the same value or message won't be the same with each other if they are
    // from different error categories.
    REQUIRE((success_error_code.value() == always_success_error_code.value()));
    REQUIRE((success_error_code.message() == always_success_error_code.message()));
    REQUIRE((success_error_code.category() != always_success_error_code.category()));
    REQUIRE((success_error_code != always_success_error_code));
    REQUIRE((AlwaysSuccessErrorCode{AlwaysSuccessErrorCodeEnum::Success} != success_error_code));
    REQUIRE((BinaryErrorCode{BinaryErrorCodeEnum::Success} != always_success_error_code));
}

TEST_CASE("test_error_code_failure_condition", "[error_handling][ErrorCode]") {
    std::error_code const failure_error_code{BinaryErrorCode{BinaryErrorCodeEnum::Failure}};
    std::ranges::for_each(
            cFailureConditions.cbegin(),
            cFailureConditions.cend(),
            [&](auto failure_condition) { REQUIRE((failure_error_code == failure_condition)); }
    );
    std::ranges::for_each(
            cNoneFailureConditions.cbegin(),
            cNoneFailureConditions.cend(),
            [&](auto none_failure_condition) {
                REQUIRE((failure_error_code != none_failure_condition));
            }
    );
}
