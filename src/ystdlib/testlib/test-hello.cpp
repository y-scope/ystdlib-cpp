#include <Catch2/single_include/catch2/catch.hpp>
#include <ystdlib/testlib/hello.hpp>

TEST_CASE("dummy", "[ystdlib::testlib]") {
    REQUIRE((13 == ystdlib::testlib::hello().size()));
}
