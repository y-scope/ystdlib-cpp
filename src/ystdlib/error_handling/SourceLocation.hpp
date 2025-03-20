#ifndef YSTDLIB_ERROR_HANDLING_SOURCELOCATION_HPP
#define YSTDLIB_ERROR_HANDLING_SOURCELOCATION_HPP

#include <iostream>
#include <source_location>

namespace ystdlib::error_handling {
class SourceLocation : public std::source_location {
public:
    // Constructor
    constexpr explicit SourceLocation(std::source_location where) : std::source_location{where} {}

#ifdef YSTDLIB_CPP_PROJECT_SOURCE_PATH_SIZE
    [[nodiscard]] auto file_name() const -> char const* {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return std::source_location::file_name() + YSTDLIB_CPP_PROJECT_SOURCE_PATH_SIZE;
    }
#endif

    friend std::ostream& operator<<(std::ostream& os, SourceLocation const& where) {
        os << where.file_name() << "(" << where.line() << ":" << where.column() << "), function `"
           << where.function_name() << "`";
        return os;
    }
};
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_SOURCELOCATION_HPP
