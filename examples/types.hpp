#ifndef YSTDLIB_ERROR_HANDLING_TEST_TYPES_HPP
#define YSTDLIB_ERROR_HANDLING_TEST_TYPES_HPP

#include <cstdint>

#include <ystdlib/error_handling/ErrorCode.hpp>

namespace ystdlib::error_handling::test {
enum class AlwaysSuccessErrorCodeEnum : uint8_t {
    Success = 0
};

enum class BinaryErrorCodeEnum : uint8_t {
    Success = 0,
    Failure
};

using AlwaysSuccessErrorCode = ystdlib::error_handling::ErrorCode<AlwaysSuccessErrorCodeEnum>;
using BinaryErrorCode = ystdlib::error_handling::ErrorCode<BinaryErrorCodeEnum>;
}  // namespace ystdlib::error_handling::test

YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(
        ystdlib::error_handling::test::AlwaysSuccessErrorCodeEnum
);
YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(ystdlib::error_handling::test::BinaryErrorCodeEnum);

#endif  // YSTDLIB_ERROR_HANDLING_TEST_TYPES_HPP
