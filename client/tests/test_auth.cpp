#include <gtest/gtest.h>

#include "auth.hpp"

TEST(User, create_user) {
    auto user = User("username");
    EXPECT_EQ(user.getUsername(), "username");
}
