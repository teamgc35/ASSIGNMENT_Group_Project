#ifndef __AS_COMPR_RLE_H__
#define __AS_COMPR_RLE_H__

#include "as_general.h"
#include "as_errno.h"
#include "as_array.h"

typedef struct RLE_compressed
{
    uint64_t nbytes;
    array_t compr_buff;

} RLE_compr_t;

typedef struct rle_node_t
{
    char ch;
    uint32_t times;
} __attribute__((packed)) RLEnode_t;

void comprstr_RLE(RLE_compr_t *__dest, const char *__src);

void extrastr_RLE(char **__dest, const RLE_compr_t *__src);

void comprbuff_RLE(RLE_compr_t **__dest, const void *__src, const uint64_t nbytes);

void extrabuff_RLE(void **result, const RLE_compr_t *__src);

#endif