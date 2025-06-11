#include <string>
#include <cstdint>
#include <iostream>
#include <cassert>

#include <ystdlib/error_handling/ErrorCode.hpp>
#include <ystdlib/containers/Array.hpp>
#include <ystdlib/io_interface/ReaderInterface.hpp>
#include <ystdlib/wrapped_facade_headers/sys/types.h>

enum class BinaryErrorCodeEnum : uint8_t {
    Success = 0,
    Failure
};

using BinaryErrorCode = ystdlib::error_handling::ErrorCode<BinaryErrorCodeEnum>;

using BinaryErrorCategory = ystdlib::error_handling::ErrorCategory<BinaryErrorCodeEnum>;

constexpr std::string_view cBinaryTestErrorCategoryName{"Binary Error Code"};

template <>
auto BinaryErrorCategory::name() const noexcept -> char const* {
    return cBinaryTestErrorCategoryName.data();
}


YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(BinaryErrorCodeEnum);

int main() {
    // error_handling
    BinaryErrorCode const success{BinaryErrorCodeEnum::Success};
    BinaryErrorCode const failure{BinaryErrorCodeEnum::Failure};

    // containers
    constexpr size_t cBufferSize{1024};
    Array<size_t> arr(cBufferSize);
    for (size_t idx{0}; idx < cBufferSize; ++idx) {
        arr.at(idx) = idx;
    }
    auto const& arr_const_ref = arr;
    assert(std::ranges::equal(arr, arr_const_ref));

    // io_interface
    ReaderInterface my_reader_interface();

    // wrapped_facade_headers
    u_int const i{0};
    assert(0 == i);
    u_long const i{0};
    assert(0 == i);
    quad_t const i{0};
    assert(0 == i);

    std::cout << "Example is run!" << std::endl;
    return 0;
}
