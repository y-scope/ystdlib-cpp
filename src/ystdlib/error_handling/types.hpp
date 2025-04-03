#ifndef YSTDLIB_ERROR_HANDLING_TYPES_HPP
#define YSTDLIB_ERROR_HANDLING_TYPES_HPP

#include <concepts>
#include <system_error>

namespace ystdlib::error_handling {
/**
 * Concept that defines a template parameter of an integer-based error code enumeration.
 * @tparam Type
 */
template <typename Type>
concept ErrorCodeType
        = std::same_as<Type, std::error_code> || std::convertible_to<Type, std::error_code>;
}  // namespace ystdlib::error_handling

#endif  // YSTDLIB_ERROR_HANDLING_TYPES_HPP
