#ifndef YSTDLIB_IO_INTERFACE_ERRORCODE_HPP
#define YSTDLIB_IO_INTERFACE_ERRORCODE_HPP

#include <cstdint>

#include <ystdlib/error_handling/ErrorCode.hpp>

namespace ystdlib::io_interface {
enum class ErrorCodeEnum : uint8_t {
    BadParam,
    BufferFull,
    Corrupt,
    EndOfFile,
    EndOfStream,
    OutOfBounds,
    OutOfMemory,
    Truncated
};

using ErrorCode = ystdlib::error_handling::ErrorCode<ErrorCodeEnum>;
}  // namespace ystdlib::io_interface

YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(ystdlib::io_interface::ErrorCodeEnum);

#endif  // YSTDLIB_IO_INTERFACE_ERRORCODE_HPP
