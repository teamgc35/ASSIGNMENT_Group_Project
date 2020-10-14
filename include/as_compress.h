#ifndef __AS_COMPRESS_H__
#define __AS_COMPRESS_H__

#include "as_general.h"
#include "as_errno.h"
#include "as_array.h"

void compr_HFM(char **__dest, const char *__src);

void extra_HFM(char **__dest, const char *__src);

void compr_RLE(array_t *__dest, const char *__src);

void extra_RLE(char **__dest, const array_t *__src);

#endif