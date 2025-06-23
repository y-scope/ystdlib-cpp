if(TARGET ystdlib::error_handling)
    return()
endif()

set(BOOST_FIND_PACKAGE_ARGS
    "${MIN_BOOST_VERSION}"
    REQUIRED
    COMPONENTS
    headers
)
find_package(Boost ${BOOST_FIND_PACKAGE_ARGS})
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
            test/test_ErrorCode.cpp
            test/test_Result.cpp
            test/test_TraceableException.cpp
            test/types.cpp
        UNIFIED_TEST_TARGET "${UNIFIED_UNIT_TEST_TARGET}"
    )
endif()

install_library(NAME error_handling NAMESPACE ystdlib)
