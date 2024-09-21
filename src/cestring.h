#ifndef CESTRING_H_
#define CESTRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------
typedef struct CeString* ce_string_t; // Opaque Pointer (aka Opaque Handle)
// ---------------------------------------------------------------------------------

// public:
    ce_string_t ce_string_new(const char* cstr);
    void        ce_string_free(ce_string_t self);

    const char* ce_string_c_str(ce_string_t self);
    size_t      ce_string_size(ce_string_t self);
    void        ce_string_reserve(ce_string_t self, size_t capacity);
    void        ce_string_set_char(ce_string_t self, size_t pos, char c);
    void        ce_string_assign(ce_string_t self, const char* cstr);

// private:
    ce_string_t _ce_string_alloc();
    void        _ce_string_default_init(ce_string_t self);
    void        _ce_string_init(ce_string_t self, size_t capacity, size_t delta);

// ---------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // CESTRING_H_
