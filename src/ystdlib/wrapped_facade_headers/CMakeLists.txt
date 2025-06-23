if(TARGET ystdlib::wrapped_facade_headers)
    return()
endif()

add_cpp_library(NAME wrapped_facade_headers NAMESPACE ystdlib PUBLIC_HEADERS sys/types.h)

if(ystdlib_ENABLE_TESTS)
    add_catch2_tests(
        NAME wrapped_facade_headers
        NAMESPACE ystdlib
        SOURCES
            test/test_sys_types.cpp
        UNIFIED_TEST_TARGET "${UNIFIED_UNIT_TEST_TARGET}"
    )
endif()

install_library(
    NAME wrapped_facade_headers
    NAMESPACE ystdlib
    CONFIG_DEST_DIR "${CONFIG_LIBS_DEST_DIR}"
    CONFIG_INPUT_DIR "${CONFIG_LIBS_INPUT_DIR}"
)
