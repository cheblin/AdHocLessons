
#ifdef __cplusplus
extern "C"
{
#endif

#pragma once

#include "AdHoc.h"

typedef struct
{
    uint8_t * bytes ;
    size_t  len;
    size_t  BIT;
} BitsArray;

typedef struct
{
    uint8_t * bytes ;
    size_t  BIT;
} BitsValue;

typedef struct
{
    uint8_t * bytes ;
    size_t  len;
} BytesArray;

typedef struct
{
    uint8_t * bytes ;
} BytesValue;

static inline Cursor* wrap_pack(Pack* pack, Cursors wrapper)
{
    wrapper->base.pack = pack;
    wrapper->base.meta = pack->meta;
    wrapper->base.bytes = pack->bytes;
    reset_cursor(wrapper);
    return wrapper;
}

static inline Pack* unwrap_pack(Cursors  wrapper)
{
    Pack* pack = wrapper->base.pack;
    wrapper->base.pack = NULL;
    wrapper->base.meta = NULL;
    wrapper->base.bytes = NULL;
    return pack;
}

static inline bool is_equal_data(Cursor* a, Cursor* b)
{
    return (a && b && a == b) ||
           (a->base.bytes != NULL &&
            b->base.bytes != NULL &&
            pack_size(&a->base) == pack_size(&b->base) &&
            memcmp(a->base.bytes, b->base.bytes, a->base.LAST_BYTE) == 0);
}



extern const Meta meta0;
extern const Pack meta0pack;





#ifdef __cplusplus
}
#endif
