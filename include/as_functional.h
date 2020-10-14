#ifndef __AS_FUNCTIONAL_H__
#define __AS_FUNCTIONAL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef NDEBUG
#include <assert.h>
#endif

#include "as_general.h"

status_t Fn_encrypt_file(const char *password, FILE* src, FILE* out);
status_t Fn_decrypt_file(const char *password, FILE* src, FILE* out);
status_t Fn_compress_file(FILE *src, FILE* out);
status_t Fn_extract_file(FILE *src, FILE* out);
#endif