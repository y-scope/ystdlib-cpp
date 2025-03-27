#include "ReaderInterface.hpp"

#include <cstddef>
#include <span>
#include <string>

#include <ystdlib/error_handling/Result.hpp>

#include "ErrorCode.hpp"

using ystdlib::error_handling::Result;

namespace ystdlib::io_interface {
auto ReaderInterface::read_char() -> ystdlib::error_handling::Result<char> {
    char c{};
    YSTDLIB_ASSERT_NO_ERROR(read({&c, 1}, 1, true));
    return c;
}

auto ReaderInterface::read_string(size_t num_bytes)
        -> ystdlib::error_handling::Result<std::string> {
    std::string str(num_bytes, 0);
    YSTDLIB_ASSERT_NO_ERROR(read({str.data(), num_bytes}, 1, true));
    return str;
}

auto ReaderInterface::read_to_delimiter(std::span<char> output_buffer, char delim, bool keep_delim)
        -> ystdlib::error_handling::Result<size_t> {
    size_t num_bytes_read{0};
    while (num_bytes_read < output_buffer.size()) {
        auto const c{YSTDLIB_TRY(read_char())};
        if (delim == c) {
            break;
        }
        output_buffer[num_bytes_read++] = c;
    }
    if (num_bytes_read == output_buffer.size()) {
        return ErrorCode{ErrorCodeEnum::BufferFull};
    }
    if (keep_delim) {
        output_buffer[num_bytes_read++] = delim;
    }
    return num_bytes_read;
}
}  // namespace ystdlib::io_interface
