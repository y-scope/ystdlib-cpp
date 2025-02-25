#include "test-Defs.hpp"

#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <system_error>

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
