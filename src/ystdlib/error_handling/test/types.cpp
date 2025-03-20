#include "types.hpp"

#include <algorithm>
#include <string>
#include <string_view>
#include <system_error>

#include "constants.hpp"

using ystdlib::error_handling::test::AlwaysSuccessErrorCodeEnum;
using ystdlib::error_handling::test::BinaryErrorCodeEnum;
using ystdlib::error_handling::test::cAlwaysSuccessErrorCategoryName;
using ystdlib::error_handling::test::cBinaryTestErrorCategoryName;
using ystdlib::error_handling::test::cFailureConditions;
using ystdlib::error_handling::test::cFailureErrorMsg;
using ystdlib::error_handling::test::cSuccessErrorMsg;
using ystdlib::error_handling::test::cUnrecognizedErrorCode;
using AlwaysSuccessErrorCategory
        = ystdlib::error_handling::ErrorCategory<AlwaysSuccessErrorCodeEnum>;
using BinaryErrorCategory = ystdlib::error_handling::ErrorCategory<BinaryErrorCodeEnum>;

template <>
auto AlwaysSuccessErrorCategory::name() const noexcept -> char const* {
    return cAlwaysSuccessErrorCategoryName.data();
}

template <>
auto AlwaysSuccessErrorCategory::message(AlwaysSuccessErrorCodeEnum error_enum) const
        -> std::string {
    switch (error_enum) {
        case AlwaysSuccessErrorCodeEnum::Success:
            return std::string{cSuccessErrorMsg};
        default:
            return std::string{cUnrecognizedErrorCode};
    }
}

template <>
auto BinaryErrorCategory::name() const noexcept -> char const* {
    return cBinaryTestErrorCategoryName.data();
}

template <>
auto BinaryErrorCategory::message(BinaryErrorCodeEnum error_enum) const -> std::string {
    switch (error_enum) {
        case BinaryErrorCodeEnum::Success:
            return std::string{cSuccessErrorMsg};
        case BinaryErrorCodeEnum::Failure:
            return std::string{cFailureErrorMsg};
        default:
            return std::string{cUnrecognizedErrorCode};
    }
}

template <>
auto BinaryErrorCategory::equivalent(
        BinaryErrorCodeEnum error_enum,
        std::error_condition const& condition
) const noexcept -> bool {
    switch (error_enum) {
        case BinaryErrorCodeEnum::Failure:
            return std::ranges::any_of(
                    cFailureConditions.cbegin(),
                    cFailureConditions.cend(),
                    [&](auto failure_condition) -> bool { return condition == failure_condition; }
            );
        default:
            return false;
    }
}
