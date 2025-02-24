#include <system_error>

#include <ystdlib/error_handling/TraceableException.hpp>

#include <catch2/catch_test_macros.hpp>

#include "test-Defs.hpp"

namespace {
class Worker {
public:
    YSTDLIB_ERROR_HANDLING_DEFINE_TRACEABLE_EXCEPTION(OperationFailed);

    static void execute_with_success() {
        throw OperationFailed(BinaryErrorCode{BinaryErrorCodeEnum::Success});
    }

    static void execute_with_failure() {
        throw OperationFailed(BinaryErrorCode{BinaryErrorCodeEnum::Failure});
    }

    static void execute_with_invalid_args() {
        throw OperationFailed(std::make_error_code(std::errc::invalid_argument));
    }
};

constexpr auto cExecuteWithSuccessFunctionName{
        "static void {anonymous}::Worker::execute_with_success()"
};
constexpr auto cExecuteWithFailureFunctionName{
        "static void {anonymous}::Worker::execute_with_failure()"
};
constexpr auto cExecuteWithInvalidArgsFunctionName{
        "static void {anonymous}::Worker::execute_with_invalid_args()"
};
constexpr auto cInvalidArgsErrorMsg{"Invalid argument"};
constexpr auto cExecuteWithSuccessLineNumber{15};
constexpr auto cExecuteWithFailureLineNumber{19};
constexpr auto cExecuteWithInvalidArgsLineNumber{23};

#ifdef SOURCE_PATH_SIZE
// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
constexpr auto cRelativePathFileName{static_cast<char const*>(__FILE__) + SOURCE_PATH_SIZE};
#else
constexpr auto cRelativePathFileName{__FILE__};
#endif
}  // namespace

TEST_CASE("test_traceable_exception_success", "[error_handling][TraceableException]") {
    ystdlib::error_handling::TraceableException success_exception{std::error_code{}};
    try {
        Worker::execute_with_success();
    } catch (ystdlib::error_handling::TraceableException& e) {
        success_exception = e;
    }
    std::error_code const success_error_code{BinaryErrorCode{BinaryErrorCodeEnum::Success}};
    REQUIRE((success_error_code.category() == success_exception.error_code().category()));
    REQUIRE((success_error_code.value() == success_exception.error_code().value()));
    REQUIRE((cSuccessErrorMsg == success_exception.error_code().message()));
    REQUIRE((cExecuteWithSuccessFunctionName == success_exception.function_name()));
    REQUIRE((cExecuteWithSuccessLineNumber == success_exception.line()));
    REQUIRE((cRelativePathFileName == success_exception.file_name()));
}

TEST_CASE("test_traceable_exception_failure", "[error_handling][TraceableException]") {
    ystdlib::error_handling::TraceableException failure_exception{std::error_code{}};
    try {
        Worker::execute_with_failure();
    } catch (ystdlib::error_handling::TraceableException& e) {
        failure_exception = e;
    }
    std::error_code const failure_error_code{BinaryErrorCode{BinaryErrorCodeEnum::Failure}};
    REQUIRE((failure_error_code.category() == failure_exception.error_code().category()));
    REQUIRE((failure_error_code.value() == failure_exception.error_code().value()));
    REQUIRE((cFailureErrorMsg == failure_exception.error_code().message()));
    REQUIRE((cExecuteWithFailureFunctionName == failure_exception.function_name()));
    REQUIRE((cExecuteWithFailureLineNumber == failure_exception.line()));
    REQUIRE((cRelativePathFileName == failure_exception.file_name()));
}

TEST_CASE("test_traceable_exception_invalid_args", "[error_handling][TraceableException]") {
    ystdlib::error_handling::TraceableException invalid_args_exception{std::error_code{}};
    try {
        Worker::execute_with_invalid_args();
    } catch (ystdlib::error_handling::TraceableException& e) {
        invalid_args_exception = e;
    }
    std::error_code const invalid_args_error_code{std::make_error_code(std::errc::invalid_argument)
    };
    REQUIRE((invalid_args_error_code.category() == invalid_args_exception.error_code().category()));
    REQUIRE((invalid_args_error_code.value() == invalid_args_exception.error_code().value()));
    REQUIRE((cInvalidArgsErrorMsg == invalid_args_exception.error_code().message()));
    REQUIRE((cExecuteWithInvalidArgsFunctionName == invalid_args_exception.function_name()));
    REQUIRE((cExecuteWithInvalidArgsLineNumber == invalid_args_exception.line()));
    REQUIRE((cRelativePathFileName == invalid_args_exception.file_name()));
}
