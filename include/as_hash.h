#ifndef __AS_HASH_H__
#define __AS_HASH_H__

#include "as_general.h"


/**
 * @description: package 8 bytes to perform hash function
 * @param {void*}: in buffer
 * @param {uint64_t}: buffer length
 * @return {uint32_t}: hashed return range(0, MAX_MAP_HEAD)
 */
uint32_t as_hash(const void* __in, const uint64_t nbytes);

/**
 * @description: wrapper for cstring type buffer hash
 * @param {char*}: in cstring
 * @return {uint32_t}: hashed return range(0, MAX_MAP_HEAD)
 */
uint32_t as_hashstr(const char* __in);

#endif