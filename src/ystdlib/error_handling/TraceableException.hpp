#ifndef YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP
#define YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP

#include <exception>
#include <source_location>
#include <string>
#include <system_error>

namespace ystdlib::error_handling {
/**
 * An exception class that is thrown with an `std::error_code`.
 *
 * This class extends `std::exception` and can be thrown with an `std::error_code` argument. It also
 * provides additional information to aid in debugging by storing details in `std::source_location`,
 * including the function name, file name, and line number of the throwing location.
 *
 * @see std::source_location::file_name()
 * @see std::source_location::function_name()
 * @see std::source_location::line()
 */
class TraceableException : public std::exception, public std::source_location {
public:
    // Constructors
    explicit TraceableException(
            std::error_code error_code,
            std::source_location const& location = std::source_location::current()
    )
            : TraceableException{error_code, location.function_name(), location} {}

    explicit TraceableException(
            std::error_code error_code,
            char const* what,
            std::source_location const& location = std::source_location::current()
    )
            : std::source_location{location},
              m_error_code{error_code},
              m_what{what} {}

    // Methods
    [[nodiscard]] auto error_code() const -> std::error_code { return m_error_code; }

#ifdef SOURCE_PATH_SIZE
    [[nodiscard]] auto file_name() const -> char const* {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        return std::source_location::file_name() + SOURCE_PATH_SIZE;
    }
#endif

    // Methods implementing std::exception
    [[nodiscard]] auto what() const noexcept -> char const* override { return m_what.c_str(); }

private:
    // Variables
    std::error_code m_error_code;
    std::string m_what;
};

}  // namespace ystdlib::error_handling

/**
 * The macro to define a `TraceableException` class with the given class name T.
 */
// NOLINTBEGIN(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)
#define YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION(T) \
    class T : public ystdlib::error_handling::TraceableException { \
        using ystdlib::error_handling::TraceableException::TraceableException; \
    }
// NOLINTEND(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)

#endif  // YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP
