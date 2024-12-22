#ifndef CEIVECTOR_H_
#define CEIVECTOR_H_

#include "cedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------
typedef struct CeIndirectVector* ce_ivector_t; // Opaque Pointer (aka Opaque Handle)
// ---------------------------------------------------------------------------------

// public:
    ce_ivector_t ce_ivector_new_with_default_deleter();
    ce_ivector_t ce_ivector_new_with_custom_deleter(void(*element_destructor)(void*));
    void         ce_ivector_del(ce_ivector_t self);

    bool         ce_ivector_empty(ce_ivector_t self);
    void         ce_ivector_reserve(ce_ivector_t self, size_t capacity);
    size_t       ce_ivector_capacity(ce_ivector_t self);
    size_t       ce_ivector_size(ce_ivector_t self);

    void         ce_ivector_set_element(ce_ivector_t self, size_t pos, void* element);
    void*        ce_ivector_get_element(ce_ivector_t self, size_t pos);
    void*        ce_ivector_front(ce_ivector_t self);
    void*        ce_ivector_back(ce_ivector_t self);
    void*        ce_ivector_sentinel_value(ce_ivector_t self);

    void         ce_ivector_clear(ce_ivector_t self);
    void         ce_ivector_push_back(ce_ivector_t self, void* element);
    void         ce_ivector_pop_back(ce_ivector_t self);

// private:
    ce_ivector_t _ce_ivector_alloc();
    void         _ce_ivector_default_init(ce_ivector_t self);
    void         _ce_ivector_init(
        ce_ivector_t self,
        size_t capacity,
        size_t delta,
        void (*deleter)(void*)
    );

// ---------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // CEIVECTOR_H_
