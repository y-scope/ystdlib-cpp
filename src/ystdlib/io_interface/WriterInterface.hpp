#ifndef YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP

#include <cstddef>
#include <span>
#include <string>

#include <ystdlib/error_handling/Result.hpp>
#include <ystdlib/wrapped_facade_headers/sys/types.h>

namespace ystdlib::io_interface {
class WriterInterface {
public:
    template <typename ReturnType>
    using Result = ystdlib::error_handling::Result<ReturnType>;

    // Constructor
    WriterInterface() = default;

    // Delete copy constructor and assignment operator
    WriterInterface(WriterInterface const&) = delete;
    auto operator=(WriterInterface const&) -> WriterInterface& = delete;

    // Default move constructor and assignment operator
    WriterInterface(WriterInterface&&) noexcept = default;
    auto operator=(WriterInterface&&) noexcept -> WriterInterface& = default;

    // Destructor
    virtual ~WriterInterface() = default;

    // Methods
    /**
     * Performs a writes of the given data.
     * @param data
     */
    [[nodiscard]] virtual auto write(std::span<char const> data) -> Result<void> = 0;

    /**
     * Forces any buffered written data to be available at the output.
     */
    [[nodiscard]] virtual auto flush() -> Result<void> = 0;

    /**
     * Performs a writes of the given numeric value.
     * @param value
     */
    template <typename ValueType>
    [[nodiscard]] auto write_numeric_value(ValueType value) -> Result<void>;

    /**
     * Performs a writes of the given string.
     * @param str
     */
    [[nodiscard]] virtual auto write_string(std::string const& str) -> Result<void> {
        return write({str.c_str(), str.length()});
    }

    /**
     * Seeks from the beginning to the given position.
     * @param pos
     */
    [[nodiscard]] virtual auto seek_from_begin(size_t pos) -> Result<void> = 0;

    /**
     * Seeks from the current position to the next position by the given offset amount.
     * @param offset
     */
    [[nodiscard]] virtual auto seek_from_current(off_t offset) -> Result<void> = 0;

    /**
     * @return The current position of the write pointer.
     */
    [[nodiscard]] virtual auto get_pos() -> Result<size_t> = 0;
};

template <typename ValueType>
auto WriterInterface::write_numeric_value(ValueType val) -> Result<void> {
    return write({static_cast<char const*>(&val), sizeof(ValueType)});
}
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
