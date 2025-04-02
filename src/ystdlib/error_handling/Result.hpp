#ifndef YSTDLIB_ERROR_HANDLING_RESULT_HPP
#define YSTDLIB_ERROR_HANDLING_RESULT_HPP

#include <system_error>

#include <outcome/config.hpp>
#include <outcome/std_result.hpp>
#include <outcome/success_failure.hpp>
#include <outcome/try.hpp>

namespace ystdlib::error_handling {
/**
 * A convenience alias for Outcome's std_result.
 *
 * This alias standardizes error handling across the codebase by defaulting the error type to
 * `std::error_code`, which interoperates with the ystdlib::error_handling::ErrorCode framework,
 * making it easier to compose errors and propagate them across different modules and libraries.
 *
 * @tparam ReturnType The type returned upon success.
 * @tparam ErrorType The type returned upon failure.
 */
template <typename ReturnType, typename ErrorType = std::error_code>
using Result = OUTCOME_V2_NAMESPACE::std_result<ReturnType, ErrorType>;

/**
 * Default return value for ystdlib::error_handling::Result<void> when function succeeds.
 *
 * Example:
 *   auto my_func() -> Result<void> {
 *     // ...
 *     return success();
 *   }
 */
[[nodiscard]] inline auto success() -> OUTCOME_V2_NAMESPACE::success_type<void> {
    return OUTCOME_V2_NAMESPACE::success();
}

/**
 * Propagates errors like Rust's `?` operator.
 *
 * Evaluates `expr`, and if it contains an error, returns the error from the calling function.
 * Otherwise, extracts and returns the value.
 *
 * Only supported on AppleClang, Clang, and GCC due to reliance on Outcome's TRY macros.
 */
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define YSTDLIB_ERROR_HANDLING_TRYX(expr) (OUTCOME_TRYX(expr))

/**
 * Error propagation macro for expressions that return void on success.
 *
 * Evaluates `expr`, and if it contains an error, returns the error from the calling function.
 * Intended for use with expressions that return `Result<void>`.
 *
 * Only supported on AppleClang, Clang, and GCC due to reliance on Outcome's TRY macros.
 */
// NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while, cppcoreguidelines-macro-usage)
#define YSTDLIB_ERROR_HANDLING_TRYV(expr) \
    do { \
        OUTCOME_TRYV(expr); \
    } while (false)
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_RESULT_HPP
