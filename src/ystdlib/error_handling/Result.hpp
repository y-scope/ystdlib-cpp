#ifndef YSTDLIB_ERROR_HANDLING_RESULT_HPP
#define YSTDLIB_ERROR_HANDLING_RESULT_HPP

#include <system_error>

#include <boost/outcome/config.hpp>
#include <boost/outcome/std_result.hpp>
#include <boost/outcome/success_failure.hpp>
#include <boost/outcome/try.hpp>

namespace ystdlib::error_handling {
/**
 * A Rust-style `Result<T, E>` type for standardized, exception-free error handling.
 *
 * This alias standardizes error handling across the codebase by defaulting the error type to
 * `std::error_code`, which interoperates with the `ystdlib::error_handling::ErrorCode`, making it
 * easier to compose errors and propagate them across different modules and libraries.
 *
 * @tparam ReturnType The type returned on success.
 * @tparam ErrorType The type used to represent errors.
 */
template <typename ReturnType, typename ErrorType = std::error_code>
using Result = BOOST_OUTCOME_V2_NAMESPACE::std_result<ReturnType, ErrorType>;

/**
 * @return A value indicating successful completion of a function that returns a void result (i.e.,
 * `Result<void, E>`).
 */
[[nodiscard]] inline auto success() -> BOOST_OUTCOME_V2_NAMESPACE::success_type<void> {
    return BOOST_OUTCOME_V2_NAMESPACE::success();
}

/**
 * A function-style macro that emulates Rust’s try (`?`) operator for error propagation.
 *
 * @param expr An expression that evaluates to a `Result` object.
 *
 * Behavior:
 * - If `expr` represents an error (i.e., `expr.has_error()` returns true), the macro performs an
 *   early return from the enclosing function with the contained error.
 * - Otherwise, it unwraps and yields the successful value as an rvalue reference (`expr.value()`).
 *
 * NOTE: This macro is only supported on GCC and Clang due to reliance on compiler-specific
 * extensions.
 */
#ifdef BOOST_OUTCOME_TRYX
    // NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
    #define YSTDLIB_ERROR_HANDLING_TRYX(expr) BOOST_OUTCOME_TRYX(expr)
#endif

/**
 * A function-style macro for propagating errors from expressions that evaluate to a void result
 * (`Result<void, E>`).
 *
 * @param expr An expression that evaluates to a `Result<void, E>` object.
 *
 * Behavior:
 * - If `expr` represents an error (i.e., `expr.has_error()` returns true), the macro performs an
 *   early return from the enclosing function with the contained error.
 * - Otherwise, execution continues normally.
 */
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define YSTDLIB_ERROR_HANDLING_TRYV(expr) BOOST_OUTCOME_TRYV(expr)
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_RESULT_HPP
