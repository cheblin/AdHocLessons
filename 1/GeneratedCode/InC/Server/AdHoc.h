
// Copyright 2019 Chikirev Sirguy, Unirail Group
//
// Licensed under the Apache License, Version 2.0,
// <LICENSE-APACHE or http://apache.org/licenses/LICENSE-2.0> or
// the MIT license <LICENSE-MIT or http://opensource.org/licenses/MIT>,
// at your option. This file may not be
// copied, modified, or distributed except according to those terms
#ifdef __cplusplus
extern "C"
{
#endif
#pragma once
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "config_.h"
#define LE  ('ABCD' == 0x44434241)
#define BE  ('ABCD' == 0x41424344)
#define EMPTY_ARG

static inline float    intBitsToFloat(uint32_t val) { return *(float*)&val; }
static inline uint32_t floatToIntBits(float val) { return *(uint32_t*)&val; }
#ifdef   UINT64_MAX
static inline double   longBitsToDouble(uint64_t val) { return *(double*)&val; }
static inline uint64_t doubleBitsToLong(double val) { return *(uint64_t*)&val; }
typedef uint64_t       UMAX;
#else
typedef  size_t UMAX;
#endif
static inline UMAX get_bytes(uint8_t* src, size_t byte, size_t bytes)
{
#ifdef   UINT64_MAX
    int32_t hi = 0;
#endif
    int32_t lo = 0;
    switch(bytes)
    {
#ifdef   UINT64_MAX
        case 8:
            hi |= src[byte + 7] << 24;
        case 7:
            hi |= src[byte + 6] << 16;
        case 6:
            hi |= src[byte + 5] << 8;
        case 5:
            hi |= src[byte + 4];
#endif
        case 4:
            lo |= src[byte + 3] << 24;
        case 3:
            lo |= src[byte + 2] << 16;
        case 2:
            lo |= src[byte + 1] << 8;
        case 1:
            lo |= src[byte];
    }
    return
#ifdef   UINT64_MAX
        (hi & 0xFFFFFFFFLL) << 32 |
#endif
        (lo & 0xFFFFFFFFLL);
}

extern const uint8_t Ol[];
extern const uint8_t lO[];

static inline int32_t set_bytes(const UMAX src, const size_t bytes, uint8_t* dst, const size_t byte)
{
#ifdef   UINT64_MAX
    const uint32_t hi = (uint32_t)(src >> 32);
#endif
    const uint32_t lo = (uint32_t)(src & 0xFFFFFFFFL);
    switch(bytes)
    {
#ifdef   UINT64_MAX
        case 8:
            dst[byte + 7] = hi >> 24;
        case 7:
            dst[byte + 6] = hi >> 16;
        case 6:
            dst[byte + 5] = hi >> 8;
        case 5:
            dst[byte + 4] = hi & 0xFF;
#endif
        case 4:
            dst[byte + 3] = lo >> 24;
        case 3:
            dst[byte + 2] = lo >> 16;
        case 2:
            dst[byte + 1] = lo >> 8;
        case 1:
            dst[byte] = lo & 0xFF;
    }
    return byte + bytes;
}

static inline UMAX get_bits(const uint8_t* src, size_t bit, size_t bits)
{
    src += bit >> 3;
    bit &= 7;
    if(bit + bits < 9) return *src >> bit & Ol[bits];
    if(sizeof(UMAX) < bits >> 3) bits = sizeof(UMAX) << 3;
    UMAX dst = 0;
    memcpy(&dst, src, (bit + bits) >> 3);
    dst >>= bit;
    src += (bit + bits) >> 3;
    bit = bit + bits & 7;
    if(0 < bit) dst |= (UMAX)(*src & Ol[bit]) << (bits - bit);
    return dst;
}

static inline void set_bits(UMAX src, size_t bits, uint8_t* dst, size_t bit)
{
    dst += bit >> 3;
    bit &= 7;
    if(8 < bit + bits)
    {
        if(bit)
        {
            *dst = (*dst & Ol[bit]) |
                   (src & Ol[
                        8 - bit
                    ]) << bit;
            dst++;
            src >>= 8 - bit;
            bits -= 8 - bit;
        }
        memcpy(dst, &src, bits >> 3);
        if(bits & 7)
        {
            dst += bits >> 3;
            *dst = (*dst & lO[8 - (bits & 7)])
                   | (((uint8_t*)&src)[(bits >> 3)]
                      & Ol[bits & 7]);
        }
    }
    else * dst = *dst & (Ol[bit] | lO[8 - bit - bits]) | (src & Ol[bits]) << bit;
}


typedef struct
{
    const struct Meta* const meta;
    uint8_t                  bytes[];
}                            Pack;

typedef struct
{
    const uint8_t type;

    const bool varint;
    const int32_t length;
    const int8_t  size;

    const uint32_t const_dims_total;
    const uint16_t field_info_bits;
    const uint8_t  sparse_bits;

    const uint16_t           var_dims_count;
    const struct Meta* const datatype;
    const uint8_t            dims_count;
    const int32_t            dims[];


} Field;

typedef struct Meta
{
    const uint16_t     id;
    const uint32_t     _2;
    const uint32_t     _4;
    const uint32_t     _8;
    const uint16_t     BITS_lenINbytes_bits;
    const uint32_t     field_0_bit;
    const uint32_t     packMinBytes;
    const uint16_t     fields_count;
    const Field* const fields[];
}                      Meta;
typedef struct
{
    Pack* pack;


    Meta const* meta;
    uint8_t*    bytes;
    int32_t     field_bit;
    int32_t     subitem_len;



    uint32_t BIT_E, BIT_S;

    uint32_t BYTE_S, BYTE_E;
    int32_t  LAST_field_bit;
    int32_t  LAST_BIT;
    int32_t  LAST_BYTE;
}            CursorBase;

static inline Field const* getField(CursorBase* cur) { return cur->meta->fields[cur->field_bit - cur->meta->field_0_bit]; }

typedef struct
{
    CursorBase base;
    int32_t    D[BBOX_DIMS_MAX];
    size_t     BIT;
    size_t     BYTE;
    size_t     item_len;
    int32_t    field_item_0;
    int32_t    field_item;
    size_t     field_items;
    size_t     field_items_total;
}              Cursor;

typedef Cursor Cursors [BBOX_NESTED_MAX];
#define CURSORS(var_name) Cursor var_name [BBOX_NESTED_MAX]

typedef enum
{
    STANDBY = 0,

    PACK_ID,
    VARINT,
    VARINT_BR,
    BYTES,
    BYTES_BR
} STATE;

typedef enum
{
    PACKK_ID,
    OPTS_INFO,
    NIL,
    CRC
} MODE;

typedef struct
{
    CursorBase cursors[BBOX_NESTED_MAX];
    uint16_t   level;
    UMAX       Uvalue;
    uint16_t   crc;
    STATE      state;
    MODE       mode;
}              Flow;

typedef struct Transmitter
{
    volatile uint32_t time;

    Flow flow;

    Pack* (*pull)(struct Transmitter* dst);
}           Transmitter;


typedef struct Receiver
{
    volatile uint32_t time;

    Flow flow;

    Transmitter* transmitter;

    Meta const* (*dispatch)(struct Receiver* dst, size_t id, Pack* pack);
    uint16_t      bits;
}                 Receiver;


uint32_t transmit(Transmitter* src, uint8_t* dst, size_t dst_bytes);
void     receive(const uint8_t* src, size_t src_bytes, Receiver* dst);
uint32_t transmit_adv(Transmitter* src, uint8_t* dst, size_t dst_bytes);
void     receive_adv(const uint8_t* src, size_t src_bytes, Receiver* dst);

typedef enum
{
    BBOX_FAILURE_RECEIVE_PACK_WITH_UNEXPECTED_ID = 1,
    BBOX_FAILURE_RECEIVE_TIMEOUT = 2,
    BBOX_FAILURE_CREATE_SEND_PACK_FOR_CHANNEL = 3,
    BBOX_FAILURE_RECEIVE_EXPECT_ID_AFTER_BR_BUT_GET_BR = 4,
    BBOX_FAILURE_RECEIVE_EXPECT_SECOND_BR_BUT_GET = 5,
    BBOX_FAILURE_RECEIVE_CRC_ERROR = 6,
    BBOX_FAILURE_POCESS_UNEXPECTED_PACK_ID = 7,
    BBOX_FAILURE_SEND = 8,
    BBOX_FAILURE_INPUT_ARGUMENT_IS_OUT_OF_RANGE = 10,
    AFTER_PROCESSING = 13,
    AFTER_SENDING = 14,
} HOST_EVENT;

extern void host_event(uint32_t place, Receiver* receiver, Transmitter* transmitter, Pack* pack, HOST_EVENT event);
void        free_pack(Pack* pack);
Pack*       new_pack(Meta const* const meta);











bool set_field(Cursor* cur, size_t fbit, int32_t all_items_vals, ...);












bool   set_item(Cursor* cur, size_t item, int32_t item_vals);
bool   reset_cursor(Cursor* cur);
size_t pack_size(CursorBase* cur);



#ifdef __cplusplus
}
#endif
