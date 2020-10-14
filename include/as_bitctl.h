#ifndef __AS_BITCTL_H__
#define __AS_BITCTL_H__
#include "as_general.h"

#define BITSET(byte, n) \
    byte |= 1UL << n

#define BITCLEAR(byte, n) \
    byte &= ~(1UL << n)

status_t as_bitset(void *buffer, const unsigned nbytes, const char *bits);
#endif