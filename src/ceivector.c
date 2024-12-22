#include "ceivector.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

// ---------------------------------------------------------------------------------

struct CeIndirectVector
{
    size_t length;
    size_t capacity;
    size_t growthFactor;
    void** rawBuffer;

    void(*delete)(void*);
};

// ---------------------------------------------------------------------------------

ce_ivector_t ce_ivector_new_with_default_deleter()
{
    ce_ivector_t self = _ce_ivector_alloc();
    _ce_ivector_default_init(self);

    return self;
}

ce_ivector_t ce_ivector_new_with_custom_deleter(void(*element_destructor)(void*))
{
    ce_ivector_t self = ce_ivector_new_with_default_deleter();
    self->delete = element_destructor;

    return self;
}

void ce_ivector_del(ce_ivector_t self)
{
    ce_ivector_clear(self);
    free(self->rawBuffer);
    free(self);
}

bool ce_ivector_empty(ce_ivector_t self)
{
    return self->length == 0;
}

void ce_ivector_reserve(ce_ivector_t self, size_t capacity)
{
    if (capacity > self->capacity)
    {
        const size_t blockSize = capacity * sizeof(void*);
        void** newRawBuffer = (void**) malloc(blockSize);
        memcpy(newRawBuffer, self->rawBuffer, blockSize);
        free(self->rawBuffer);

        self->capacity  = capacity;
        self->rawBuffer = newRawBuffer;
    }
}

size_t ce_ivector_capacity(ce_ivector_t self)
{
    return self->capacity;
}

size_t ce_ivector_size(ce_ivector_t self)
{
    return self->length;
}

void* ce_ivector_get_element(ce_ivector_t self, size_t pos)
{
    // TODO: Return NULL when out of bound?

    if (pos < ce_ivector_size(self))
    {
        return self->rawBuffer[pos];
    }
}

void ce_ivector_set_element(ce_ivector_t self, size_t pos, void* element)
{
    // TODO: Some kind of error checking for out of bound?

    if (pos < ce_ivector_size(self))
    {
        if (self->delete != NULL)
        {
            self->delete(self->rawBuffer[pos]);
        }

        self->rawBuffer[pos] = element;
    }
}

void* ce_ivector_front(ce_ivector_t self)
{
    return ce_ivector_get_element(self, 0);
}

void* ce_ivector_back(ce_ivector_t self)
{
    return ce_ivector_get_element(self, self->length - 1);
}

void ce_ivector_clear(ce_ivector_t self)
{
    if (self->delete != NULL)
    {
        for (size_t i = 0; i < self->length; i++)
        {
            self->delete(ce_ivector_get_element(self, i));
        }
    }

    self->length = 0;
}

void ce_ivector_push_back(ce_ivector_t self, void* element)
{
    if (++self->length > self->capacity)
    {
        ce_ivector_reserve(self, self->capacity * self->growthFactor);
    }

    self->rawBuffer[self->length - 1] = element;
}

void ce_ivector_pop_back(ce_ivector_t self)
{
    if (self->delete != NULL)
    {
        self->delete(ce_ivector_back(self));
    }

    self->length--;
}

// ---------------------------------------------------------------------------------

ce_ivector_t _ce_ivector_alloc()
{
    return (struct CeIndirectVector*) malloc(sizeof(struct CeIndirectVector));
}

void _ce_ivector_default_init(ce_ivector_t self)
{
    const size_t DEFAULT_CAPACITY      = 32;
    const size_t DEFAULT_GROWTH_FACTOR =  2;

    _ce_ivector_init(self, DEFAULT_CAPACITY, DEFAULT_GROWTH_FACTOR, free);
}

void _ce_ivector_init(
    ce_ivector_t self,
    size_t capacity,
    size_t delta,
    void (*deleter)(void*)
)
{
    self->length       = 0;
    self->capacity     = capacity;
    self->growthFactor = delta;
    self->rawBuffer    = (void**) malloc(self->capacity * sizeof(void*));

    self->delete = deleter;
}

// ---------------------------------------------------------------------------------
