#ifndef __AS_BITCTL_H__
#define __AS_BITCTL_H__
#include "as_general.h"

#define BITSET(byte, n) \
    byte |= 1UL << n

#define BITCLEAR(byte, n) \
    byte &= ~(1UL << n)

#endif