#include <cassert>
#include <cstring>

#include <ystdlib/error_handling/TraceableException.hpp>

#include <catch2/catch_test_macros.hpp>

#include "types.hpp"

using ystdlib::error_handling::TraceableException;

namespace {
constexpr auto cCustomFailureDescription{"This operation failed due to invalid args."};
constexpr auto cCurrentFileName{"src/ystdlib/error_handling/test/test_TraceableException.cpp"};
constexpr auto cSuccessFuncName{
        "static void ystdlib::error_handling::test::Worker::execute_with_success()"
};
constexpr auto cFailureFuncName{
        "static void ystdlib::error_handling::test::Worker::execute_with_failure()"
};
}  // namespace

namespace ystdlib::error_handling::test {
class Worker {
public:
    YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION(OperationFailed);

    static auto execute_with_success() -> void {
        throw OperationFailed(BinaryErrorCode{BinaryErrorCodeEnum::Success});
    }

    static auto execute_with_failure() -> void {
        throw OperationFailed(
                BinaryErrorCode{BinaryErrorCodeEnum::Failure},
                cCustomFailureDescription
        );
    }
};
}  // namespace ystdlib::error_handling::test

namespace {
template <typename Callable>
[[nodiscard]] auto capture_exception(Callable&& f) -> TraceableException;

template <typename Callable>
auto capture_exception(Callable&& f) -> TraceableException {
    try {
        std::forward<Callable>(f)();
    } catch (TraceableException& e) {
        return e;
    }
    assert(false && "The function is expected to throw.");
}
}  // namespace

namespace ystdlib::error_handling::test {
TEST_CASE("test_traceable_exception", "[error_handling][TraceableException]") {
    auto const ex_success{capture_exception(Worker::execute_with_success)};
    REQUIRE(std::string{ex_success.where().file_name()}.ends_with(cCurrentFileName));
    REQUIRE((0 == std::strcmp(ex_success.where().function_name(), cSuccessFuncName)));

    auto const ex_failure{capture_exception(Worker::execute_with_failure)};
    REQUIRE((0 == std::strcmp(ex_failure.what(), cCustomFailureDescription)));
    REQUIRE(std::string{ex_failure.where().file_name()}.ends_with(cCurrentFileName));
    REQUIRE((0 == std::strcmp(ex_failure.where().function_name(), cFailureFuncName)));
}
}  // namespace ystdlib::error_handling::test
