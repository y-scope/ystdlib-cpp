#ifndef YSTDLIB_IO_INTERFACE_STREAMINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_STREAMINTERFACE_HPP

#include <sys/types.h>

#include <concepts>
#include <cstddef>
#include <type_traits>

#include <ystdlib/error_handling/Result.hpp>

namespace ystdlib::io_interface {
/**
 * Concept that defines an integer-based value type.
 *
 * TODO: move this into a general ystdlib-cpp typing library.
 * @tparam T
 */
template <typename T>
concept NumericType = requires(T type) {
    {
        static_cast<std::underlying_type_t<T>>(type)
    } -> std::convertible_to<int>;
};

class StreamInterface {
public:
    // Constructor
    StreamInterface() = default;

    // Delete copy constructor and assignment operator
    StreamInterface(StreamInterface const&) = delete;
    auto operator=(StreamInterface const&) -> StreamInterface& = delete;

    // Default move constructor and assignment operator
    StreamInterface(StreamInterface&&) noexcept = default;
    auto operator=(StreamInterface&&) noexcept -> StreamInterface& = default;

    // Destructor
    virtual ~StreamInterface() = default;

    /**
     * Seeks from the beginning to the given position.
     * @param pos
     * @return ystdlib::io_interface::ErrorCodeNum::OutOfBounds
     */
    [[nodiscard]] virtual auto seek_from_begin(size_t pos) -> ystdlib::error_handling::Result<void>
            = 0;

    /**
     * Seeks from the current position to the next position by the given offset amount.
     * @param offset
     * @return ystdlib::io_interface::ErrorCodeNum::OutOfBounds
     */
    [[nodiscard]] virtual auto seek_from_current(off_t offset)
            -> ystdlib::error_handling::Result<void>
            = 0;

    /**
     * @return The current position of the file stream pointer.
     */
    [[nodiscard]] virtual auto get_pos() const -> size_t = 0;
};
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_STREAMINTERFACE_HPP
