#include "ReaderInterface.hpp"

#include <cstddef>
#include <span>
#include <string>

#include <ystdlib/error_handling/Result.hpp>

#include "ErrorCode.hpp"

namespace ystdlib::io_interface {
auto ReaderInterface::read(size_t num_bytes) -> Result<std::string> {
    std::string str(num_bytes, 0);
    auto const num_bytes_read{YSTDLIB_ERROR_HANDLING_TRYX(read({str.data(), num_bytes}))};
    str.resize(num_bytes_read);
    return str;
}

auto ReaderInterface::read_exact_length(std::span<char> buf) -> Result<void> {
    auto const num_bytes_read{YSTDLIB_ERROR_HANDLING_TRYX(read(buf))};
    if (0 == num_bytes_read) {
        return ErrorCode{ErrorCodeEnum::EndOfStream};
    }
    if (num_bytes_read < buf.size()) {
        return ErrorCode{ErrorCodeEnum::Truncated};
    }
    return ystdlib::error_handling::success();
}

auto ReaderInterface::read_exact_length(size_t num_bytes) -> Result<std::string> {
    std::string str(num_bytes, 0);
    YSTDLIB_ERROR_HANDLING_TRYV(read_exact_length({str.data(), num_bytes}));
    return str;
}

auto ReaderInterface::read_to_delimiter(char delim, bool keep_delimiter) -> Result<std::string> {
    char c{0};
    std::string str;

    // The first read needs to succeed
    c = YSTDLIB_ERROR_HANDLING_TRYX(read_numeric_value<char>());
    while (delim != c) {
        str += c;
        auto const result{read_numeric_value<char>()};
        if (result.has_error()) {
            auto const error{result.error()};
            if (ErrorCode{ErrorCodeEnum::EndOfStream} == error
                || ErrorCode{ErrorCodeEnum::EndOfFile} == error)
            {
                return str;
            }
            return error;
        }
        c = result.value();
    }
    if (keep_delimiter) {
        str += delim;
    }
    return str;
}
}  // namespace ystdlib::io_interface
