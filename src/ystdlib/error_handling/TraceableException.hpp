#ifndef YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP
#define YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP

#include <exception>
#include <source_location>
#include <sstream>
#include <string>
#include <system_error>
#include <utility>

#include "types.hpp"
#include "utils.hpp"

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
template <ErrorCodeType ErrorType = std::error_code>
class TraceableException : public std::exception {
public:
    // Constructors
    explicit TraceableException(
            ErrorType error_code,
            std::source_location const& where = std::source_location::current()
    )
            : m_error_code{std::move(error_code)},
              m_where{where} {
        std::ostringstream oss;
        oss << where;
        m_what = oss.str();
    }

    explicit TraceableException(
            ErrorType error_code,
            std::string what,
            std::source_location const& where = std::source_location::current()
    )
            : m_error_code{std::move(error_code)},
              m_what{std::move(what)},
              m_where{where} {}

    // Methods implementing std::exception
    [[nodiscard]] auto what() const noexcept -> char const* override { return m_what.c_str(); }

    // Methods
    [[nodiscard]] auto error_code() const -> ErrorType { return m_error_code; }

    [[nodiscard]] auto what() -> std::string& { return m_what; }

    [[nodiscard]] auto where() const noexcept -> std::source_location const& { return m_where; }

private:
    // Variables
    ErrorType m_error_code;
    std::string m_what;
    std::source_location m_where;
};
}  // namespace ystdlib::error_handling

/**
 * The macro to define a `TraceableException` class with the given class name T.
 */
// NOLINTBEGIN(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)
#define YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION(T) \
    class T : public ystdlib::error_handling::TraceableException<> { \
        using ystdlib::error_handling::TraceableException<>::TraceableException; \
    }

#define YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION_WITH_ERROR_TYPE(T, E) \
    class T : public ystdlib::error_handling::TraceableException<E> { \
        using ystdlib::error_handling::TraceableException<E>::TraceableException; \
    }
// NOLINTEND(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)

#endif  // YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP
