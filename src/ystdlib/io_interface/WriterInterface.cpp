// NOLINTBEGIN
#include "WriterInterface.hpp"

namespace ystdlib::io_interface {
void WriterInterface::write_char(char c) {
    write(&c, 1);
}

void WriterInterface::write_string(std::string const& str) {
    write(str.c_str(), str.length());
}

void WriterInterface::seek_from_begin(size_t pos) {
    auto error_code = try_seek_from_begin(pos);
    if (ErrorCode_Success != error_code) {
        throw OperationFailed(error_code);
    }
}

void WriterInterface::seek_from_current(off_t offset) {
    auto error_code = try_seek_from_current(offset);
    if (ErrorCode_Success != error_code) {
        throw OperationFailed(error_code);
    }
}

size_t WriterInterface::get_pos() const {
    size_t pos;
    ErrorCode error_code = try_get_pos(pos);
    if (ErrorCode_Success != error_code) {
        throw OperationFailed(error_code);
    }

    return pos;
}
}  // namespace ystdlib::io_interface

// NOLINTEND
