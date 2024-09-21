#include "cestring.h"

#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------------------------------

struct CeString
{
    size_t capacity;
    size_t growthFactor;
    char*  rawPointer;
};

// ---------------------------------------------------------------------------------

ce_string_t ce_string_new(const char* cstr)
{
    ce_string_t self = _ce_string_alloc();
    _ce_string_default_init(self);
    ce_string_assign(self, cstr);

    return self;
}

void ce_string_free(ce_string_t self)
{
    free(self->rawPointer);
    free(self);
}

const char* ce_string_c_str(ce_string_t self)
{
    return self->rawPointer;
}

size_t ce_string_size(ce_string_t self)
{
    return strlen(self->rawPointer);
}

void ce_string_reserve(ce_string_t self, size_t capacity)
{
    if (capacity > self->capacity)
    {
        char* newRawPointer = (char*) malloc(capacity);
        memcpy(newRawPointer, self->rawPointer, self->capacity);
        // memset(&newRawPointer[self->capacity], 0, capacity - self->capacity); // seens unnecessary
        free(self->rawPointer);

        self->capacity = capacity;
        self->rawPointer = newRawPointer;
    }
}

void ce_string_set_char(ce_string_t self, size_t pos, char c)
{
    if (pos < ce_string_size(self))
    {
        self->rawPointer[pos] = c;
    }
}

void ce_string_assign(ce_string_t self, const char* cstr)
{
    const size_t srcBufLen = strlen(cstr) + 1;

    while(srcBufLen > self->capacity)
    {
        ce_string_reserve(self, self->capacity * self->growthFactor);
    }

    memcpy(self->rawPointer, cstr, srcBufLen);
}

// ---------------------------------------------------------------------------------

ce_string_t _ce_string_alloc()
{
    return (struct CeString*) malloc(sizeof(struct CeString));
}

void _ce_string_default_init(ce_string_t self)
{
    const size_t DEFAULT_CAPACITY      = 32;
    const size_t DEFAULT_GROWTH_FACTOR =  2;

    _ce_string_init(self, DEFAULT_CAPACITY, DEFAULT_GROWTH_FACTOR);
}

void _ce_string_init(ce_string_t self, size_t capacity, size_t delta)
{
    self->capacity     = capacity;
    self->growthFactor = delta;
    self->rawPointer   = (char*) malloc(self->capacity);

    memset(self->rawPointer, 0, self->capacity);
}

// ---------------------------------------------------------------------------------
