#ifndef YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP

#include <cstddef>
#include <string>

#include <ystdlib/wrapped_facade_headers/sys/types.h>

#include "ErrorCode.hpp"

namespace ystdlib::io_interface {
class WriterInterface {
public:
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
     * Writes the given data to the underlying medium.
     * @param data
     * @param data_length
     */
    [[nodiscard]] virtual auto write(char const* data, size_t data_length) -> ErrorCode = 0;

    /**
     * Forces any buffered output data to be available at the underlying medium.
     */
    [[nodiscard]] virtual auto flush() -> ErrorCode = 0;

    /**
     * Writes a numeric value to the underlying medium.
     * @param val
     */
    template <typename ValueType>
    [[nodiscard]] auto write_numeric_value(ValueType value) -> ErrorCode;

    /**
     * Writes a character to the underlying medium.
     * @param c
     */
    [[nodiscard]] virtual auto write_char(char c) -> ErrorCode { return write(&c, 1); }

    /**
     * Writes a string to the underlying medium.
     * @param str
     */
    [[nodiscard]] virtual auto write_string(std::string const& str) -> ErrorCode {
        return write(str.c_str(), str.length());
    }

    /**
     * Seeks from the beginning to the given position.
     * @param pos
     */
    [[nodiscard]] virtual auto seek_from_begin(size_t pos) -> ErrorCode = 0;

    /**
     * Seeks from the current position to the next position by the given offset amount.
     * @param offset
     */
    [[nodiscard]] virtual auto seek_from_current(off_t offset) -> ErrorCode = 0;

    /**
     * @param pos Returns the current position of the read pointer.
     */
    [[nodiscard]] virtual auto get_pos(size_t& pos) -> ErrorCode = 0;
};

template <typename ValueType>
auto WriterInterface::write_numeric_value(ValueType val) -> ErrorCode {
    return write(static_cast<char const*>(&val), sizeof(ValueType));
}
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
