#include <string>
#include <ystdlib/error_handling/ErrorCode.hpp>
#include <cstdint>
#include <iostream>

#include <ystdlib/error_handling/ErrorCode.hpp>

enum class BinaryErrorCodeEnum : uint8_t {
    Success = 0,
    Failure
};

using BinaryErrorCode = ystdlib::error_handling::ErrorCode<BinaryErrorCodeEnum>;

using BinaryErrorCategory = ystdlib::error_handling::ErrorCategory<BinaryErrorCodeEnum>;

constexpr std::string_view cBinaryTestErrorCategoryName{"Binary Error Code"};

template <>
auto BinaryErrorCategory::name() const noexcept -> char const* {
    return cBinaryTestErrorCategoryName.data();
}


YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(BinaryErrorCodeEnum);

int main() {
    // Test error codes within the same error category
    BinaryErrorCode const success{BinaryErrorCodeEnum::Success};

    BinaryErrorCode const failure{BinaryErrorCodeEnum::Failure};

    std::cout << "test is good!" << std::endl;
    return 0;
}
