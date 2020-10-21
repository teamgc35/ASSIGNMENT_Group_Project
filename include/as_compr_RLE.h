#ifndef __AS_COMPR_RLE_H__
#define __AS_COMPR_RLE_H__

#include "as_general.h"
#include "as_errno.h"
#include "as_array.h"

typedef struct RLE_compressed
{
    uint64_t total_bytes;
    array_t *compr_buff;

} RLE_compr_t;
void compr_HFM(char **__dest, const char *__src);

void extra_HFM(char **__dest, const char *__src);

void compr_RLE(RLE_compr_t *__dest, const char *__src);

void extra_RLE(char **__dest, const array_t *__src);

#endif