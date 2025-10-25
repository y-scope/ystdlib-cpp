#ifndef YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP

#include <cstddef>
#include <span>
#include <string>

#include <ystdlib/error_handling/Result.hpp>
#include <ystdlib/wrapped_facade_headers/sys/types.h>

namespace ystdlib::io_interface {
class ReaderInterface {
public:
    template <typename ReturnType>
    using Result = ystdlib::error_handling::Result<ReturnType>;

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

    // Methods
    /**
     * Performs a read that attempts to fill the given buffer.
     * @param buf
     * @return The number of bytes read.
     */
    [[nodiscard]] virtual auto read(std::span<char> buf) -> Result<size_t> = 0;

    /**
     * Performs a read of up to the requested byte count.
     * @param num_bytes
     * @return The data read as a string.
     */
    [[nodiscard]] virtual auto read(size_t num_bytes) -> Result<std::string>;

    /**
     * Performs a read that completely fills the given buffer.
     * @param buf
     */
    [[nodiscard]] virtual auto read_exact_length(std::span<char> buf) -> Result<void>;

    /**
     * Performs a read that must return exactly the requested byte count.
     * @param num_bytes
     * @return The data read as a string.
     */
    [[nodiscard]] virtual auto read_exact_length(size_t num_bytes) -> Result<std::string>;

    /**
     * Performs a reads of up to the next delimiter.
     * @param buf
     * @param delim The delimiter to stop at.
     * @param keep_delimiter Whether to include the delimiter in the output.
     * @return The data read as a string.
     */
    [[nodiscard]] virtual auto read_to_delimiter(char delim, bool keep_delimiter)
            -> Result<std::string>;

    /**
     * @return The numeric value read.
     */
    template <typename ValueType>
    [[nodiscard]] auto read_numeric_value() -> Result<ValueType>;

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
     * @return The current position of the read pointer.
     */
    [[nodiscard]] virtual auto get_pos() -> Result<size_t> = 0;
};

template <typename ValueType>
auto ReaderInterface::read_numeric_value() -> Result<ValueType> {
    ValueType value{};
    YSTDLIB_ERROR_HANDLING_TRYV(read_exact_length({static_cast<char*>(&value), sizeof(ValueType)}));
    return value;
}
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_READERINTERFACE_HPP
