#ifndef YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP
#define YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP

#include <concepts>
#include <exception>
#include <source_location>
#include <stacktrace>
#include <string>
#include <system_error>

#include "SourceLocation.hpp"

namespace ystdlib::error_handling {
/**
 * Concept that defines a template parameter of an integer-based error code enumeration.
 * @tparam Type
 */
template <typename Type>
concept ErrorCodeType
        = std::same_as<Type, std::error_code> || std::convertible_to<Type, std::error_code>;

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
template <typename ErrorCodeType>
class TraceableException : public std::exception, public std::source_location {
public:
    // Constructors
    explicit TraceableException(
            ErrorCodeType error_code,
            std::source_location const& where = std::source_location::current()
    )
            : TraceableException{std::move(error_code), where.function_name(), where} {}

    explicit TraceableException(
            ErrorCodeType error_code,
            std::string what,
            std::source_location const& where = std::source_location::current()
    )
            : m_error_code{std::move(error_code)},
              m_what{std::move(what)},
              m_where{where} {}

    // Methods implementing std::exception
    [[nodiscard]] auto what() const noexcept -> char const* override { return m_what.c_str(); }

    // Methods
    [[nodiscard]] auto error_code() const -> ErrorCodeType { return m_error_code; }

    [[nodiscard]] auto what() -> std::string& { return m_what; }

    [[nodiscard]] auto where() const noexcept -> SourceLocation const& { return m_where; }

private:
    // Variables
    ErrorCodeType const m_error_code;
    std::string m_what;
    SourceLocation const m_where;
};

}  // namespace ystdlib::error_handling

/**
 * The macro to define a `TraceableException` class with the given class name T.
 */
// NOLINTBEGIN(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)
#define YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION(T, E) \
    class T : public ystdlib::error_handling::TraceableException<E> { \
        using ystdlib::error_handling::TraceableException<E>::TraceableException; \
    }
// NOLINTEND(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)

#endif  // YSTDLIB_ERROR_HANDLING_TRACEABLEEXCEPTION_HPP
