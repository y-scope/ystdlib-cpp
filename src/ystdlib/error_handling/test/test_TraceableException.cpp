#include <cassert>
#include <iostream>

#include <ystdlib/error_handling/TraceableException.hpp>

#include <catch2/catch_test_macros.hpp>

#include "types.hpp"

using ystdlib::error_handling::ErrorCodeType;
using ystdlib::error_handling::TraceableException;

namespace {
constexpr auto cCustomFailureDescription{"This operation has failed."};
}  // namespace

namespace ystdlib::error_handling::test {
class Worker {
public:
    YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION(OperationFailed, BinaryErrorCode);

    static auto execute_with_success() -> void {
        throw OperationFailed(BinaryErrorCode{BinaryErrorCodeEnum::Success});
    }

    static auto execute_with_failure() -> void {
        // clang-format off
        throw OperationFailed(BinaryErrorCode{BinaryErrorCodeEnum::Failure}, cCustomFailureDescription);
        // clang-format on
    }

    // static auto execute_with_invalid_args() -> void {
    //     throw OperationFailed(std::make_error_code(std::errc::invalid_argument));
    // }
};
}  // namespace ystdlib::error_handling::test

namespace {
template <ErrorCodeType E, typename Callable>
[[nodiscard]] auto capture_exception(Callable&& f) -> TraceableException<E>;

template <ErrorCodeType E, typename Callable>
auto capture_exception(Callable&& f) -> TraceableException<E> {
    try {
        std::forward<Callable>(f)();
    } catch (TraceableException<E>& e) {
        return e;
    }
    assert(false && "The function is expected to throw.");
}
}  // namespace

namespace ystdlib::error_handling::test {
TEST_CASE("test_traceable_exception", "[error_handling][TraceableException]") {
    REQUIRE(1 == 1);
    auto const ex{capture_exception<BinaryErrorCode>(Worker::execute_with_success)};
    std::cout << ex.where().file_name() << std::endl;
    std::cout << ex.where() << std::endl;
}
}  // namespace ystdlib::error_handling::test
