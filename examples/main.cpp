#include <algorithm>
#include <string_view>
#include <system_error>

#include <ystdlib/error_handling/ErrorCode.hpp>

#include "constants.hpp"
#include "types.hpp"

#include <cassert>
#include <iostream>

using namespace ystdlib::error_handling::test;

int main() {
    // Test error codes within the same error category
    BinaryErrorCode const success{BinaryErrorCodeEnum::Success};
    std::error_code const success_error_code{success};
    assert((success == success_error_code));
    assert((cSuccessErrorMsg == success_error_code.message()));
    assert((BinaryErrorCode::get_category() == success_error_code.category()));
    assert((cBinaryTestErrorCategoryName == success_error_code.category().name()));

    BinaryErrorCode const failure{BinaryErrorCodeEnum::Failure};
    std::error_code const failure_error_code{failure};
    assert((failure == failure_error_code));
    assert((cFailureErrorMsg == failure_error_code.message()));
    assert((BinaryErrorCode::get_category() == failure_error_code.category()));
    assert((cBinaryTestErrorCategoryName == failure_error_code.category().name()));

    assert((success_error_code != failure_error_code));
    assert((success_error_code.category() == failure_error_code.category()));

    AlwaysSuccessErrorCode const always_success{AlwaysSuccessErrorCodeEnum::Success};
    std::error_code const always_success_error_code{always_success};
    assert((always_success_error_code == always_success));
    assert((cSuccessErrorMsg == always_success_error_code.message()));
    assert((AlwaysSuccessErrorCode::get_category() == always_success_error_code.category()));
    assert((cAlwaysSuccessErrorCategoryName == always_success_error_code.category().name()));

    // Compare error codes from different error category
    // Error codes that have the same value or message won't be the same with each other if they are
    // from different error categories.
    assert((success_error_code.value() == always_success_error_code.value()));
    assert((success_error_code.message() == always_success_error_code.message()));
    assert((success_error_code.category() != always_success_error_code.category()));
    assert((success_error_code != always_success_error_code));
    assert((AlwaysSuccessErrorCode{AlwaysSuccessErrorCodeEnum::Success} != success_error_code));
    assert((BinaryErrorCode{BinaryErrorCodeEnum::Success} != always_success_error_code));

    std::cout << "test is good!" << std::endl;
    return 0;
}
