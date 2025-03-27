#ifndef YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP

#include <span>
#include <string>

#include <ystdlib/error_handling/Result.hpp>

#include "StreamInterface.hpp"

namespace ystdlib::io_interface {
class WriterInterface : public StreamInterface {
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
    ~WriterInterface() override = default;

    // Methods
    /**
     * Writes the given data to the underlying medium.
     * @param data_buffer
     * @return ystdlib::io_interface::ErrorCode::BadParam
     * @return ystdlib::io_interface::ErrorCode::BufferFull
     * @return ystdlib::io_interface::ErrorCode::Corrupt
     */
    [[nodiscard]] virtual auto write(std::span<char const> output_buffer)
            -> ystdlib::error_handling::Result<void>
            = 0;

    /**
     * Forces any buffered output data to be available at the underlying medium.
     * @return ystdlib::io_interface::ErrorCode::Corrupt
     */
    [[nodiscard]] virtual auto flush() -> ystdlib::error_handling::Result<void> = 0;

    /**
     * Writes a numeric value to the underlying medium.
     * @param val Value to write
     * @return Same as WriterInterface::write.
     */
    template <NumericType T>
    [[nodiscard]] auto write_numeric_value(T value) -> ystdlib::error_handling::Result<void>;

    /**
     * Writes the given character to the underlying medium.
     * @param c
     * @return Same as WriterInterface::write.
     */
    [[nodiscard]] virtual auto write_char(char c) -> ystdlib::error_handling::Result<void> {
        return write({&c, 1});
    }

    /**
     * Writes the given string to the underlying medium.
     * @param str
     * @return Same as WriterInterface::write.
     */
    [[nodiscard]] virtual auto write_string(std::string const& str)
            -> ystdlib::error_handling::Result<void> {
        return write({str.c_str(), str.length()});
    }
};

template <NumericType T>
auto WriterInterface::write_numeric_value(T value) -> ystdlib::error_handling::Result<void> {
    return write({static_cast<char const*>(&value), sizeof(T)});
}
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
