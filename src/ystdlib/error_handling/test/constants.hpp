#ifndef YSTDLIB_ERROR_HANDLING_TEST_CONSTANTS_HPP
#define YSTDLIB_ERROR_HANDLING_TEST_CONSTANTS_HPP

#include <array>
#include <string_view>
#include <system_error>

namespace ystdlib::error_handling::test {
constexpr std::string_view cAlwaysSuccessErrorCategoryName{"Always Success Error Code"};
constexpr std::string_view cBinaryTestErrorCategoryName{"Binary Error Code"};
constexpr std::string_view cSuccessErrorMsg{"Success"};
constexpr std::string_view cFailureErrorMsg{"Failure"};
constexpr std::string_view cUnrecognizedErrorCode{"Unrecognized Error Code"};
constexpr std::array cFailureConditions{std::errc::not_connected, std::errc::timed_out};
constexpr std::array cNoneFailureConditions{std::errc::broken_pipe, std::errc::address_in_use};
}  // namespace ystdlib::error_handling::test

#endif  // YSTDLIB_ERROR_HANDLING_TEST_CONSTANTS_HPP
