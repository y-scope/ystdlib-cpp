#ifndef YSTDLIB_ERROR_HANDLING_RESULT_HPP
#define YSTDLIB_ERROR_HANDLING_RESULT_HPP

#include <system_error>

#include <outcome/config.hpp>
#include <outcome/std_result.hpp>
#include <outcome/success_failure.hpp>

namespace ystdlib::error_handling {
template <typename ReturnType, typename ErrorType = std::error_code>
using Result = OUTCOME_V2_NAMESPACE::std_result<ReturnType, ErrorType>;

/**
 * Default return value for ystdlib::error_handling::Result<void> when function succeeds.
 */
[[nodiscard]] inline auto success() -> OUTCOME_V2_NAMESPACE::success_type<void> {
    return OUTCOME_V2_NAMESPACE::success();
}

// NOLINTBEGIN(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)
/**
 * This macro works the same way as Rust's `?` operator for error propagation.
 */
#define YSTDLIB_TRY(expr) \
    ({ \
        auto result{(expr)}; \
        if (result.has_error()) { \
            return result.error(); \
        } \
        using ReturnType = decltype(result.value()); \
        static_assert(std::is_move_constructible_v<ReturnType>); \
        std::move(result.value()); \
    })

/**
 * This macro works the same way as Rust's `?` operator for error propagation, without returning
 * any value.
 */
#define YSTDLIB_ASSERT_NO_ERROR(expr) \
    ({ \
        if (auto const result{(expr)}; result.has_error()) { \
            return result.error(); \
        } \
    })
// NOLINTEND(bugprone-macro-parentheses, cppcoreguidelines-macro-usage)
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_RESULT_HPP

