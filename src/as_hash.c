#include "as_hash.h"

#include <string.h>

uint32_t as_hash(const void *__in, const uint64_t nbytes)
{
    uint64_t opt_time = nbytes / sizeof(uint64_t);
    uint64_t opt_rema = nbytes % sizeof(uint64_t);

    uint64_t *buffer = (uint64_t *)__in;
    register uint64_t i;
    register uint32_t hash_val = 0;

    for (i = 0; i < opt_time; i++)
    {
        hash_val += *buffer;
        hash_val *= *buffer;
        hash_val *= 131;
        hash_val %= MAX_MAP_HEAD;
        buffer++;
    }
    char *remain_buff = (char *)buffer;
    for (i = 0; i < opt_rema; i++)
    {
        hash_val += remain_buff[i];
        hash_val *= remain_buff[i];
        hash_val *= 131;
        hash_val %= MAX_MAP_HEAD;
    }
    return hash_val;
}
uint32_t as_hashstr(const char *__in)
{
    return as_hash(__in, strlen(__in));
}