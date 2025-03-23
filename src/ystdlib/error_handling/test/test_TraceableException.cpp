#include <cassert>
#include <string_view>

#include <ystdlib/error_handling/TraceableException.hpp>

#include <catch2/catch_test_macros.hpp>

#include "types.hpp"

using ystdlib::error_handling::ErrorCodeType;
using ystdlib::error_handling::TraceableException;

namespace {
constexpr auto cCustomFailureDescription{"This operation failed due to invalid args."};
constexpr std::string_view cCurrentFileName{
        "src/ystdlib/error_handling/test/test_TraceableException.cpp"
};
constexpr std::string_view cCurrentExceptionLocation{
        "src/ystdlib/error_handling/test/test_TraceableException.cpp(30:76), function `static void "
        "ystdlib::error_handling::test::Worker::execute_with_success()`"
};
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
    auto const ex{capture_exception<BinaryErrorCode>(Worker::execute_with_success)};
    REQUIRE((0 == std::strcmp(ex.where().file_name(), cCurrentFileName.data())));
    REQUIRE((0 == std::strcmp(ex.where().str().c_str(), cCurrentExceptionLocation.data())));
}
}  // namespace ystdlib::error_handling::test
