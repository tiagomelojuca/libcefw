#include <gtest/gtest.h>

#include "../src/cestring.h"

TEST(CeStringTest, should_be_able_to_construct_string) {
    ce_string_t ceStr1 = ce_string_new("Hello, World");
    ce_string_t ceStr2 = ce_string_new("Goodbye, World");

    EXPECT_STREQ("Hello, World", ce_string_c_str(ceStr1));
    ce_string_assign_from_cestr(ceStr1, ceStr2);
    EXPECT_STREQ("Goodbye, World", ce_string_c_str(ceStr1));
    ce_string_assign_from_char(ceStr1, 'T');
    EXPECT_STREQ("T", ce_string_c_str(ceStr1));

    ce_string_free(ceStr1);
    ce_string_free(ceStr2);
}
