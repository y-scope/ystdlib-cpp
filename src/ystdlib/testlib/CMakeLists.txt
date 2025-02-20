cpp_library(NAME testlib NAMESPACE ystdlib)
cpp_test(SRCS test-hello.cpp DEPS ystdlib::testlib)
