#include <array>
#include <cstdint>
#include <string_view>
#include <system_error>

#include <ystdlib/error_handling/ErrorCode.hpp>

constexpr std::string_view cAlwaysSuccessErrorCategoryName{"Always Success Error Code"};
constexpr std::string_view cBinaryTestErrorCategoryName{"Binary Error Code"};
constexpr std::string_view cSuccessErrorMsg{"Success"};
constexpr std::string_view cFailureErrorMsg{"Failure"};
constexpr std::string_view cUnrecognizedErrorCode{"Unrecognized Error Code"};
constexpr std::array cFailureConditions{std::errc::not_connected, std::errc::timed_out};
constexpr std::array cNoneFailureConditions{std::errc::broken_pipe, std::errc::address_in_use};

enum class AlwaysSuccessErrorCodeEnum : uint8_t {
    Success = 0
};

enum class BinaryErrorCodeEnum : uint8_t {
    Success = 0,
    Failure
};

using AlwaysSuccessErrorCode = ystdlib::error_handling::ErrorCode<AlwaysSuccessErrorCodeEnum>;
using AlwaysSuccessErrorCategory
        = ystdlib::error_handling::ErrorCategory<AlwaysSuccessErrorCodeEnum>;
using BinaryErrorCode = ystdlib::error_handling::ErrorCode<BinaryErrorCodeEnum>;
using BinaryErrorCategory = ystdlib::error_handling::ErrorCategory<BinaryErrorCodeEnum>;

YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(AlwaysSuccessErrorCodeEnum);
YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(BinaryErrorCodeEnum);
