#include "cestring.h"

#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------------------------------

struct CeString
{
    size_t capacity;
    size_t growthFactor;
    char*  rawBuffer;
};

// ---------------------------------------------------------------------------------

ce_string_t ce_string_new(const char* cstr)
{
    ce_string_t self = _ce_string_alloc();
    _ce_string_default_init(self);
    ce_string_assign_from_c_str(self, cstr);

    return self;
}

void ce_string_free(ce_string_t self)
{
    free(self->rawBuffer);
    free(self);
}

const char* ce_string_c_str(ce_string_t self)
{
    return self->rawBuffer;
}

size_t ce_string_size(ce_string_t self)
{
    return strlen(self->rawBuffer);
}

void ce_string_reserve(ce_string_t self, size_t capacity)
{
    if (capacity > self->capacity)
    {
        char* newRawBuffer = (char*) malloc(capacity);
        memcpy(newRawBuffer, self->rawBuffer, self->capacity);
        // memset(&newRawBuffer[self->capacity], 0, capacity - self->capacity); // seens unnecessary
        free(self->rawBuffer);

        self->capacity  = capacity;
        self->rawBuffer = newRawBuffer;
    }
}

void ce_string_set_char(ce_string_t self, size_t pos, char c)
{
    if (pos < ce_string_size(self))
    {
        self->rawBuffer[pos] = c;
    }
}

void ce_string_assign_from_c_str(ce_string_t self, const char* cstr)
{
    const size_t srcBufLen = strlen(cstr) + 1;

    while(srcBufLen > self->capacity)
    {
        ce_string_reserve(self, self->capacity * self->growthFactor);
    }

    memcpy(self->rawBuffer, cstr, srcBufLen);
}

void ce_string_assign_from_cestr(ce_string_t self, ce_string_t other)
{
    const size_t srcBufLen = ce_string_size(other) + 1;

    while(srcBufLen > self->capacity)
    {
        ce_string_reserve(self, self->capacity * self->growthFactor);
    }

    memcpy(self->rawBuffer, other->rawBuffer, srcBufLen);
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
    self->rawBuffer    = (char*) malloc(self->capacity);

    memset(self->rawBuffer, 0, self->capacity);
}

char* _ce_string_buffer(ce_string_t self)
{
    return self->rawBuffer;
}

size_t _ce_string_buflen(ce_string_t self)
{
    return self->capacity;
}

// ---------------------------------------------------------------------------------
