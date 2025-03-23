#ifndef YSTDLIB_ERROR_HANDLING_SOURCELOCATION_HPP
#define YSTDLIB_ERROR_HANDLING_SOURCELOCATION_HPP

#include <iostream>
#include <source_location>
#include <sstream>
#include <string>

namespace ystdlib::error_handling {
class SourceLocation : public std::source_location {
public:
    // Constructor
    explicit SourceLocation(std::source_location const& where)
            : std::source_location{where},
              m_formatted_location{format_location(*this)} {}

#ifdef YSTDLIB_CPP_PROJECT_SOURCE_PATH_SIZE
    [[nodiscard]] auto file_name() const noexcept -> char const* {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return std::source_location::file_name() + YSTDLIB_CPP_PROJECT_SOURCE_PATH_SIZE;
    }
#endif

    [[nodiscard]] auto str() const noexcept -> std::string const& { return m_formatted_location; }

    friend auto operator<<(std::ostream& os, SourceLocation const& where) -> std::ostream& {
        return os << where.str();
    }

private:
    static auto format_location(SourceLocation const& where) -> std::string {
        std::ostringstream oss;
        oss << where.file_name() << "(" << where.line() << ":" << where.column() << "), function `"
            << where.function_name() << "`";
        return oss.str();
    }

    std::string m_formatted_location;
};
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_SOURCELOCATION_HPP
