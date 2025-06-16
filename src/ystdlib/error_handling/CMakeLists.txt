if(TARGET ystdlib::error_handling)
    return()
endif()

set(boost_find_package_args
    1.81.0
    REQUIRED
    COMPONENTS
    headers
)
find_package(Boost ${boost_find_package_args})
message(STATUS "Found Boost ${Boost_VERSION}.")

add_cpp_library(
    NAME error_handling
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        ErrorCode.hpp
        TraceableException.hpp
        Result.hpp
        utils.hpp
    PUBLIC_LINK_LIBRARIES
        Boost::headers
)

if(ystdlib_ENABLE_TESTS)
    add_catch2_tests(
        NAME error_handling
        NAMESPACE ystdlib
        SOURCES
            test/constants.hpp
            test/test_ErrorCode.cpp
            test/test_Result.cpp
            test/test_TraceableException.cpp
            test/types.cpp
            test/types.hpp
        UNIFIED_TEST_TARGET "${UNIFIED_UNIT_TEST_TARGET}"
    )
endif()

install_library(NAME error_handling NAMESPACE ystdlib)
