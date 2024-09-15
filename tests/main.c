#include <stdio.h>

#include "../src/cestring.h"

int main()
{
    ce_string_t str = ce_string_new("qwea");
    // ce_string_assign(str, "abcd");
    ce_string_set_char(str, 0, 'x');
    ce_string_set_char(str, 3, 'x');

    printf("%s", ce_string_c_str(str));

    return 0;
}
