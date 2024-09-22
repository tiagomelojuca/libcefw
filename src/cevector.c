#include "cevector.h"

// ---------------------------------------------------------------------------------

struct CeVector
{
    size_t capacity;
};

// ---------------------------------------------------------------------------------

ce_vector_t ce_vector_new()
{
    ;
}

void ce_vector_free(ce_vector_t self)
{
    ;
}

// ---------------------------------------------------------------------------------

ce_vector_t _ce_vector_alloc()
{
    return (struct CeVector*) malloc(sizeof(struct CeVector));
}

void _ce_vector_default_init(ce_vector_t self)
{
    const size_t DEFAULT_CAPACITY      = 32;
    const size_t DEFAULT_GROWTH_FACTOR =  2;

    _ce_vector_init(self, DEFAULT_CAPACITY, DEFAULT_GROWTH_FACTOR);
}

void _ce_vector_init(ce_vector_t self, size_t capacity, size_t delta)
{
    ;
}

// ---------------------------------------------------------------------------------
