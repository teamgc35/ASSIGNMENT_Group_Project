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

/* Use RLE algorithm to compress a cstring */
void comprstr_RLE(RLE_compr_t *__dest, const char *__src);

/* extract a RLE compressed cstring */
void extrastr_RLE(char **__dest, const RLE_compr_t *__src);

/* compress any buffer with RLE algorithm */
void comprbuff_RLE(RLE_compr_t *__dest, const void *__src, const uint64_t nbytes);

/* extract RLE compressed buffer */
void extrabuff_RLE(void **__dest, const RLE_compr_t *__src);

/* save comprbuff_t to a file */
void RLE_compr_Dump(FILE *Fp, const RLE_compr_t* buff);

/* load comprbuff_t form a file */
void RLE_compr_Load(FILE *Fp, RLE_compr_t* buff);
#endif