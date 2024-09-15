#include <stdio.h>

#include "../src/cestring.h"

int main()
{
    ce_string_t str = ce_string_new();
    ce_string_append(str, "abcd");
    ce_string_set_char(str, 0, 'x');
    ce_string_set_char(str, 4, 'x');

    printf("%s", ce_string_c_str(str));

    return 0;
}
