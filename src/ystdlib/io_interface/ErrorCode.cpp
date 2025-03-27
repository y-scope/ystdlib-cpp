#include "ErrorCode.hpp"

#include <string>

#include <ystdlib/error_handling/ErrorCode.hpp>

using ystdlib::io_interface::ErrorCodeEnum;
using ErrorCategory = ystdlib::error_handling::ErrorCategory<ErrorCodeEnum>;

template <>
auto ErrorCategory::name() const noexcept -> char const* {
    return "ystdlib::io_interface::ErrorCode";
}

template <>
auto ErrorCategory::message(ErrorCodeEnum error_enum) const -> std::string {
    switch (error_enum) {
        case ErrorCodeEnum::BadParam:
            return "Supplied parameters are invalid.";
        case ErrorCodeEnum::BufferFull:
            return "The output buffer is full and cannot accept more data.";
        case ErrorCodeEnum::Corrupt:
            return "The data is corrupted or malformed.";
        case ErrorCodeEnum::EndOfFile:
            return "End of file reached.";
        case ErrorCodeEnum::EndOfStream:
            return "End of the data stream reached.";
        case ErrorCodeEnum::OutOfBounds:
            return "Attempted to access data outside of valid bounds.";
        case ErrorCodeEnum::OutOfMemory:
            return "Memory allocation failed.";
        case ErrorCodeEnum::Truncated:
            return "The data was unexpectedly truncated or cut off.";
        default:
            return "Unrecognized ystdlib::io_interface::ErrorCodeEnum.";
    }
}
