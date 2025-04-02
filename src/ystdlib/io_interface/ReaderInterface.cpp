#include "ReaderInterface.hpp"

#include <cstddef>
#include <string>

#include "ErrorCode.hpp"

namespace ystdlib::io_interface {
auto
ReaderInterface::read_to_delimiter(char delim, bool keep_delimiter, bool append, std::string& str)
        -> ErrorCode {
    if (false == append) {
        str.clear();
    }

    auto const original_str_length{str.length()};

    // Read character by character into str, until we find a delimiter
    char c{0};
    size_t num_bytes_read{0};
    while (true) {
        auto const error_code{read(&c, 1, num_bytes_read)};
        if (ErrorCode_Success != error_code) {
            if (ErrorCode_EndOfFile == error_code && str.length() > original_str_length) {
                return ErrorCode_Success;
            }
            return error_code;
        }

        if (delim == c) {
            break;
        }

        str += c;
    }

    // Add delimiter if necessary
    if (keep_delimiter) {
        str += delim;
    }

    return ErrorCode_Success;
}

auto ReaderInterface::read_exact_length(char* buf, size_t num_bytes) -> ErrorCode {
    size_t num_bytes_read{0};
    auto const error_code{read(buf, num_bytes, num_bytes_read)};
    if (ErrorCode_Success != error_code) {
        return error_code;
    }
    if (num_bytes_read < num_bytes) {
        return ErrorCode_Truncated;
    }

    return ErrorCode_Success;
}

auto ReaderInterface::read_string(size_t const str_length, std::string& str) -> ErrorCode {
    // Resize string to fit str_length
    str.resize(str_length);

    return read_exact_length(str.data(), str_length);
}
}  // namespace ystdlib::io_interface
