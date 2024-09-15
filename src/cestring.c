#include "cestring.h"

#include <stdlib.h>
#include <string.h>

struct CeString
{
    size_t capacity;
    size_t growthFactor;
    char*  rawPointer;
};

ce_string_t ce_string_new()
{
    ce_string_t cestr = (struct CeString*) malloc(sizeof(struct CeString));
    ce_string_default_init(cestr);

    return cestr;
}

void ce_string_default_init(ce_string_t cestr)
{
    const size_t DEFAULT_CAPACITY      = 4;
    const size_t DEFAULT_GROWTH_FACTOR = 2;

    ce_string_init(cestr, DEFAULT_CAPACITY, DEFAULT_GROWTH_FACTOR);
}

void ce_string_init(ce_string_t cestr, size_t capacity, size_t delta)
{
    cestr->capacity     = capacity;
    cestr->growthFactor = delta;
    cestr->rawPointer   = (char*) malloc(cestr->capacity);

    memset(cestr->rawPointer, 0, cestr->capacity);
}

void ce_string_free(ce_string_t cestr)
{
    free(cestr->rawPointer);
    free(cestr);
}

const char* ce_string_c_str(ce_string_t cestr)
{
    return cestr->rawPointer;
}

size_t ce_string_size(ce_string_t cestr)
{
    return strlen(cestr->rawPointer);
}

void ce_string_reserve(ce_string_t cestr, size_t capacity)
{
    if (capacity > cestr->capacity)
    {
        char* newRawPointer = (char*) malloc(capacity);
        memcpy(newRawPointer, cestr->rawPointer, cestr->capacity);
        // memset(&newRawPointer[cestr->capacity], 0, capacity - cestr->capacity); // seens unnecessary
        free(cestr->rawPointer);

        cestr->capacity = capacity;
        cestr->rawPointer = newRawPointer;
    }
}

void ce_string_set_char(ce_string_t cestr, size_t pos, char c)
{
    if (pos < ce_string_size(cestr))
    {
        cestr->rawPointer[pos] = c;
    }
}

void ce_string_append(ce_string_t cestr, const char* cstr)
{
    const size_t srcBufLen = strlen(cstr) + 1;

    while(srcBufLen > cestr->capacity)
    {
        ce_string_reserve(cestr, cestr->capacity * cestr->growthFactor);
    }

    memcpy(cestr->rawPointer, cstr, srcBufLen);
}
