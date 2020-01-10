
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

static inline bool is_equal_data(Pack *a, Pack *b) { return (a && b && a == b) || (a->meta == b->meta && memcmp(a->bytes, b->bytes, a->meta->packMinBytes) == 0); }



extern const Meta meta0;
extern const Pack meta0pack;





#ifdef __cplusplus
}
#endif
