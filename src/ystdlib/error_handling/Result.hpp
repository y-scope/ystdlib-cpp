#ifndef YSTDLIB_ERROR_HANDLING_RESULT_HPP
#define YSTDLIB_ERROR_HANDLING_RESULT_HPP

#include <system_error>

#include <outcome/config.hpp>
#include <outcome/std_result.hpp>
#include <outcome/success_failure.hpp>
#include <outcome/try.hpp>

namespace ystdlib::error_handling {
template <typename ReturnType, typename ErrorType = std::error_code>
using Result = OUTCOME_V2_NAMESPACE::std_result<ReturnType, ErrorType>;

/**
 * Default return value for ystdlib::error_handling::Result<void> when function succeeds.
 */
[[nodiscard]] inline auto success() -> OUTCOME_V2_NAMESPACE::success_type<void> {
    return OUTCOME_V2_NAMESPACE::success();
}

/**
 * This macro works the same way as Rust's `?` operator for error propagation.
 */
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define YSTDLIB_TRYX(expr) (OUTCOME_TRYX(expr))

/**
 * This macro works the same way as Rust's `?` operator for error propagation, without returning
 * any value.
 */
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define YSTDLIB_TRYV(expr) \
    do { \
        OUTCOME_TRYV(expr); \
    } while (false)
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_RESULT_HPP
