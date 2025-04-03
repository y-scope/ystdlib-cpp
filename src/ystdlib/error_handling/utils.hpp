#ifndef YSTDLIB_ERROR_HANDLING_UTILS_HPP
#define YSTDLIB_ERROR_HANDLING_UTILS_HPP

#include <ostream>
#include <source_location>

namespace ystdlib::error_handling {
inline auto operator<<(std::ostream& os, std::source_location const& where) -> std::ostream& {
    return os << where.file_name() << "(" << where.line() << ":" << where.column()
              << "), function `" << where.function_name() << "`";
}
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_UTILS_HPP
