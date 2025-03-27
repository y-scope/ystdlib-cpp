#ifndef YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP

#include <cstddef>
#include <span>
#include <string>

#include <ystdlib/error_handling/Result.hpp>

#include "StreamInterface.hpp"

namespace ystdlib::io_interface {
class ReaderInterface : public StreamInterface {
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
    ~ReaderInterface() override = default;

    // Methods
    /**
     * Reads up to the given number of bytes from the underlying medium into the given buffer.
     * @param output_buffer
     * @param num_bytes
     * @param exact If the number of bytes read needs to be equal to the amount requested.
     * @return The actual number of bytes read.
     * @return ystdlib::io_interface::ErrorCode::BadParam
     * @return ystdlib::io_interface::ErrorCode::BufferFull
     * @return ystdlib::io_interface::ErrorCode::Corrupt
     * @return ystdlib::io_interface::ErrorCode::EndOfFile
     * @return ystdlib::io_interface::ErrorCode::EndOfStream
     */
    [[nodiscard]] virtual auto
    read(std::span<char> output_buffer, size_t num_bytes, bool exact = false)
            -> ystdlib::error_handling::Result<size_t>
            = 0;

    /**
     * @return The read character from the underlying medium.
     * @return ystdlib::io_interface::ErrorCode::Corrupt
     * @return ystdlib::io_interface::ErrorCode::EndOfFile
     * @return ystdlib::io_interface::ErrorCode::EndOfStream
     */
    [[nodiscard]] virtual auto read_char() -> ystdlib::error_handling::Result<char>;

    /**
     * @param num_bytes
     * @return The read sring from the underlying medium.
     * @return ystdlib::io_interface::ErrorCode::Corrupt
     * @return ystdlib::io_interface::ErrorCode::EndOfFile
     * @return ystdlib::io_interface::ErrorCode::EndOfStream
     * @return ystdlib::io_interface::ErrorCode::OutOfMemory if the requested read is too large.
     */
    [[nodiscard]] virtual auto read_string(size_t num_bytes)
            -> ystdlib::error_handling::Result<std::string>;

    /**
     * @return The read numeric value from the underlying medium.
     * @return ystdlib::io_interface::ErrorCode::Corrupt
     * @return ystdlib::io_interface::ErrorCode::EndOfFile
     * @return ystdlib::io_interface::ErrorCode::EndOfStream
     */
    template <NumericType T>
    [[nodiscard]] auto read_numeric_value() -> ystdlib::error_handling::Result<T>;

    /**
     * Reads up to the next delimiter from the underlying medium into the given buffer.
     * @param output_buffer
     * @param delim The delimiter to stop at.
     * @param keep_delim Whether to include the delimiter in the output.
     * @return The actual number of bytes read.
     * @return Same as ReaderInterface::read.
     */
    [[nodiscard]] virtual auto
    read_to_delimiter(std::span<char> output_buffer, char delim, bool keep_delim)
            -> ystdlib::error_handling::Result<size_t>;
};

template <NumericType T>
auto ReaderInterface::read_numeric_value() -> ystdlib::error_handling::Result<T> {
    T value{};
    return YSTDLIB_TRY(read({static_cast<char*>(&value), sizeof(T)}, sizeof(T), true));
}
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP
