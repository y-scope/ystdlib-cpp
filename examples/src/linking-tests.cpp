#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string_view>

#include <ystdlib/containers/Array.hpp>
#include <ystdlib/error_handling/ErrorCode.hpp>
#include <ystdlib/io_interface/ErrorCode.hpp>
#include <ystdlib/io_interface/ReaderInterface.hpp>
#include <ystdlib/wrapped_facade_headers/sys/types.h>

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

using ystdlib::io_interface::ErrorCode;

class FailureReader : ystdlib::io_interface::ReaderInterface {
public:
    [[nodiscard]] auto read(char* /*buf*/, size_t /*num_bytes_to_read*/, size_t& /*num_bytes_read*/)
            -> ErrorCode override {
        return ErrorCode::ErrorCode_Unsupported;
    }

    [[nodiscard]] auto seek_from_begin(size_t /*pos*/) -> ErrorCode override {
        return ErrorCode::ErrorCode_Unsupported;
    }

    [[nodiscard]] auto seek_from_current(off_t /*offset*/) -> ErrorCode override {
        return ErrorCode::ErrorCode_Unsupported;
    }

    [[nodiscard]] auto get_pos(size_t& /*pos*/) -> ErrorCode override {
        return ErrorCode::ErrorCode_Unsupported;
    }
};

namespace {
auto test_containers() -> bool {
    try {
        constexpr size_t cBufferSize{1024};
        ystdlib::containers::Array<size_t> arr(cBufferSize);
            for (size_t idx{0}; idx < cBufferSize; ++idx) {
                arr.at(idx) = idx;
            }
            auto const& arr_const_ref = arr;
            return std::ranges::equal(arr, arr_const_ref);
    } catch (std::exception const&) {
        return false;
    }
}

auto test_error_handling() -> bool {
    BinaryErrorCode const success{BinaryErrorCodeEnum::Success};
    std::error_code const success_error_code{success};
    return success == success_error_code;
}

auto test_io_interface() -> bool {
    FailureReader reader{};
    return ErrorCode::ErrorCode_Unsupported == reader.seek_from_begin(0);
}

auto test_wrapped_facade_headers() -> bool {
    u_int const uint{1};
    u_long const ulong{2};
    quad_t const quadt{3};
    return 1 == uint && 2 == ulong && 3 == quadt;
}
}

auto main() -> int {
    if (false == test_containers()) {
        std::cerr << "Error: containers test failed. Could not validate array.\n";
        return 1;
    }

    if (false == test_error_handling()) {
        std::cerr << "Error: error_handling test failed. Could not validate array.\n";
        return 2;
    }

    if (false == test_io_interface()) {
        std::cerr << "Error: error_handling test failed. Could not validate array.\n";
        return 3;
    }

    if (false == test_wrapped_facade_headers()) {
        std::cerr << "Error: wrapped_facade_headers test failed. Could not create sys types.\n";
        return 4;
    }

    return 0;
}
