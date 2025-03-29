#ifndef YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP

#include <sys/types.h>

#include <cstddef>
#include <string>

#include "ErrorCode.hpp"

namespace ystdlib::io_interface {
class ReaderInterface {
public:
    // Constructor
    ReaderInterface() = default;

    // Delete copy constructor and assignment operator
    ReaderInterface(ReaderInterface const&) = delete;
    auto operator=(ReaderInterface const&) -> ReaderInterface& = delete;

    // Default move constructor and assignment operator
    ReaderInterface(ReaderInterface&&) noexcept = default;
    auto operator=(ReaderInterface&&) noexcept -> ReaderInterface& = default;

    // Destructor
    virtual ~ReaderInterface() = default;

    // Methods implementing ReaderInterface
    /*
     * Reads up to the given number of bytes from the underlying medium into the given buffer.
     * @param buf
     * @param num_bytes_to_read
     * @param num_bytes_read Returns the actual number of bytes read.
     */
    [[nodiscard]] virtual auto read(char* buf, size_t num_bytes_to_read, size_t& num_bytes_read)
            -> ErrorCode
            = 0;

    /**
     * Reads up to the next delimiter from the underlying medium into the given string.
     * @param delim The delimiter to stop at.
     * @param keep_delimiter Whether to include the delimiter in the output string or not.
     * @param append Whether to append to the given string or replace its contents.
     * @param str Returns the string read.
     */
    [[nodiscard]] virtual auto
    read_to_delimiter(char delim, bool keep_delimiter, bool append, std::string& str) -> ErrorCode;

    /**
     * Reads the given number of bytes from the underlying medium into the given buffer.
     * @param buf
     * @param num_bytes Number of bytes to read.
     */
    [[nodiscard]] virtual auto read_exact_length(char* buf, size_t num_bytes) -> ErrorCode;

    /**
     * @param value Returns the read numeric value.
     */
    template <typename ValueType>
    [[nodiscard]] auto read_numeric_value(ValueType& value) -> ErrorCode;

    /**
     * @param str_length
     * @param str Returns the string read.
     */
    [[nodiscard]] virtual auto read_string(size_t str_length, std::string& str) -> ErrorCode;

    // Methods implementing general stream interface
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
     * @param pos Returns the current position of the stream pointer.
     */
    [[nodiscard]] virtual auto get_pos(size_t& pos) -> ErrorCode = 0;
};

template <typename ValueType>
auto ReaderInterface::read_numeric_value(ValueType& value) -> ErrorCode {
    return read_exact_length(static_cast<char*>(&value), sizeof(ValueType));
}
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP
