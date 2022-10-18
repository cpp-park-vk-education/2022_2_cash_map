#include <gtest/gtest.h>
#include <string>

#include "lib.hpp"

TEST(Lib_test, test_foo) {
    std::string a = "foo";
    EXPECT_EQ(a, foo());
}
