#ifndef __AS_FUNCTIONAL_H__
#define __AS_FUNCTIONAL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef NDEBUG
#include <assert.h>
#endif

#include "as_general.h"

void file_encrypt(const char *password, const char *path);
void file_decrypt(const char *password, const char *path);

#endif