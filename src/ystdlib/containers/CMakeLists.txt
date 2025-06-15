if(TARGET ystdlib::containers)
    return()
endif()

cpp_library(NAME containers NAMESPACE ystdlib PUBLIC_HEADERS Array.hpp)

if(ystdlib_ENABLE_TESTS)
    catch2_tests(
        NAME containers
        NAMESPACE ystdlib
        SOURCES
            test/test_Array.cpp
        UNIFIED_TEST_TARGET "${UNIFIED_UNIT_TEST_TARGET}"
    )
endif()

install_library(NAME containers NAMESPACE ystdlib)
