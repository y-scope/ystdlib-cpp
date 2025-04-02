// NOLINTBEGIN
#include "WriterInterface.hpp"

namespace ystdlib::io_interface {
void WriterInterface::write_char(char c) {
    write(&c, 1);
}

void WriterInterface::write_string(std::string const& str) {
    write(str.c_str(), str.length());
}
}  // namespace ystdlib::io_interface

// NOLINTEND
