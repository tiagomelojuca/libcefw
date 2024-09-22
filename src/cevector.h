#ifndef CEVECTOR_H_
#define CEVECTOR_H_

#include "cedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------
typedef struct CeVector* ce_vector_t; // Opaque Pointer (aka Opaque Handle)
// ---------------------------------------------------------------------------------

// public:
    ce_vector_t ce_vector_new();
    void        ce_vector_free(ce_vector_t self);

// private:
    ce_vector_t _ce_vector_alloc();
    void        _ce_vector_default_init(ce_vector_t self);
    void        _ce_vector_init(ce_vector_t self, size_t capacity, size_t delta);

// ---------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // CEVECTOR_H_
