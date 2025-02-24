#include <cassert>
#include <string_view>
#include <system_error>

#include <ystdlib/error_handling/TraceableException.hpp>

#include <catch2/catch_test_macros.hpp>

#include "test-Defs.hpp"

namespace {
constexpr std::string_view cCustomFailureDescription{"This operation has failed."};

class Worker {
public:
    YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION(OperationFailed);

    static auto execute_with_success() -> void {
        throw OperationFailed(BinaryErrorCode{BinaryErrorCodeEnum::Success});
    }

    static auto execute_with_failure() -> void {
        throw OperationFailed(
                BinaryErrorCode{BinaryErrorCodeEnum::Failure},
                cCustomFailureDescription.data()
        );
    }

    static auto execute_with_invalid_args() -> void {
        throw OperationFailed(std::make_error_code(std::errc::invalid_argument));
    }
};

constexpr std::string_view cExecuteWithSuccessFunctionName{
        "static void {anonymous}::Worker::execute_with_success()"
};
constexpr std::string_view cExecuteWithFailureFunctionName{
        "static void {anonymous}::Worker::execute_with_failure()"
};
constexpr std::string_view cExecuteWithInvalidArgsFunctionName{
        "static void {anonymous}::Worker::execute_with_invalid_args()"
};
constexpr std::string_view cInvalidArgsErrorMsg{"Invalid argument"};
constexpr auto cExecuteWithSuccessLineNumber{19};
constexpr auto cExecuteWithFailureLineNumber{26};
constexpr auto cExecuteWithInvalidArgsLineNumber{30};

#ifdef SOURCE_PATH_SIZE
constexpr auto cRelativePathFileName{std::string_view{__FILE__}.substr(SOURCE_PATH_SIZE)};
#else
constexpr std::string_view cRelativePathFileName{__FILE__};
#endif

template <typename Callable>
[[nodiscard]] auto capture_exception(Callable&& f) -> ystdlib::error_handling::TraceableException;

template <typename Callable>
auto capture_exception(Callable&& f) -> ystdlib::error_handling::TraceableException {
    try {
        std::forward<Callable>(f)();
    } catch (ystdlib::error_handling::TraceableException& e) {
        return e;
    }
    assert(false && "Needs to pass in a workflow that throws.");
    return ystdlib::error_handling::TraceableException{std::error_code{}};
}
}  // namespace

TEST_CASE("test_traceable_exception_success", "[error_handling][TraceableException]") {
    auto const success_exception{capture_exception(Worker::execute_with_success)};
    std::error_code const success_error_code{BinaryErrorCode{BinaryErrorCodeEnum::Success}};
    REQUIRE((success_error_code.category() == success_exception.error_code().category()));
    REQUIRE((success_error_code.value() == success_exception.error_code().value()));
    REQUIRE((cSuccessErrorMsg == success_exception.error_code().message()));
    REQUIRE((cExecuteWithSuccessFunctionName == std::string_view{success_exception.what()}));
    REQUIRE((cExecuteWithSuccessFunctionName == success_exception.function_name()));
    REQUIRE((cExecuteWithSuccessLineNumber == success_exception.line()));
    REQUIRE((cRelativePathFileName == success_exception.file_name()));
}

TEST_CASE("test_traceable_exception_failure", "[error_handling][TraceableException]") {
    auto const failure_exception{capture_exception(Worker::execute_with_failure)};
    std::error_code const failure_error_code{BinaryErrorCode{BinaryErrorCodeEnum::Failure}};
    REQUIRE((failure_error_code.category() == failure_exception.error_code().category()));
    REQUIRE((failure_error_code.value() == failure_exception.error_code().value()));
    REQUIRE((cFailureErrorMsg == failure_exception.error_code().message()));
    REQUIRE((cCustomFailureDescription == std::string_view{failure_exception.what()}));
    REQUIRE((cExecuteWithFailureFunctionName == failure_exception.function_name()));
    REQUIRE((cExecuteWithFailureLineNumber == failure_exception.line()));
    REQUIRE((cRelativePathFileName == failure_exception.file_name()));
}

TEST_CASE("test_traceable_exception_invalid_args", "[error_handling][TraceableException]") {
    auto const invalid_args_exception{capture_exception(Worker::execute_with_invalid_args)};
    auto const invalid_args_error_code{std::make_error_code(std::errc::invalid_argument)};
    REQUIRE((invalid_args_error_code.category() == invalid_args_exception.error_code().category()));
    REQUIRE((invalid_args_error_code.value() == invalid_args_exception.error_code().value()));
    REQUIRE((cInvalidArgsErrorMsg == invalid_args_exception.error_code().message()));
    REQUIRE((cExecuteWithInvalidArgsFunctionName == std::string_view{invalid_args_exception.what()})
    );
    REQUIRE((cExecuteWithInvalidArgsFunctionName == invalid_args_exception.function_name()));
    REQUIRE((cExecuteWithInvalidArgsLineNumber == invalid_args_exception.line()));
    REQUIRE((cRelativePathFileName == invalid_args_exception.file_name()));
}
