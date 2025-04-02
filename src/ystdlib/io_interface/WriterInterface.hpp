#ifndef YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
// NOLINTBEGIN

// TODO: https://github.com/y-scope/ystdlib-cpp/issues/50
// NOLINTNEXTLINE(misc-include-cleaner)
#include <sys/types.h>

#include <cstddef>
#include <string>

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
     * Writes the given data to the underlying medium
     * @param data
     * @param data_length
     */
    virtual void write(char const* data, size_t data_length) = 0;
    virtual void flush() = 0;

    /**
     * Writes a numeric value
     * @param val Value to write
     */
    template <typename ValueType>
    void write_numeric_value(ValueType value);

    /**
     * Writes the given character to the underlying medium.
     * @param c
     */
    [[nodiscard]] virtual auto write_char(char c) -> ErrorCode { return write(&c, 1); }

    /**
     * Writes the given string to the underlying medium.
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
    // TODO: https://github.com/y-scope/ystdlib-cpp/issues/50
    // NOLINTNEXTLINE(misc-include-cleaner)
    [[nodiscard]] virtual auto seek_from_current(off_t offset) -> ErrorCode = 0;

    /**
     * @param pos Returns the current position of the read pointer.
     */
    [[nodiscard]] virtual auto get_pos(size_t& pos) -> ErrorCode = 0;
};

template <typename ValueType>
void WriterInterface::write_numeric_value(ValueType val) {
    write(reinterpret_cast<char*>(&val), sizeof(val));
}
}  // namespace ystdlib::io_interface

// NOLINTEND
#endif  // YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
