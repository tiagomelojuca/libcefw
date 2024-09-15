#include <gtest/gtest.h>

#include "../src/cestring.h"

TEST(CeStringTest, should_be_able_to_construct_string) {
    ce_string_t ceStr = ce_string_new("Hello, World");

    EXPECT_STREQ("Hello, World", ce_string_c_str(ceStr));

    ce_string_free(ceStr);
}
