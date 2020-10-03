#include "as_enrypt.h"
#include "as_errno.h"
#include <string.h>
#include <stdlib.h>

#ifndef NDEBUG
#include <assert.h>
#endif

void encrypt_char(char *__dest, const char *__src, const int __num)
{
    *__dest = *__src + __num;
}

void decrypt_char(char *__dest, const char *__src, const int __num)
{
    *__dest = *__src - __num;
}

status_t encrypt_str(char **__res, const char *__src)
{
    uint64_t __src_len = strlen(__src);
    int32_t *buffer = (int32_t *)malloc(__src_len + sizeof(int32_t));
    assert(buffer);
    if (buffer == NULL)
        return ERR_NULLPTR;
    // use __src_len as the rand seed; and store it at first 8 bytes of the encrypted char*
    *buffer = (int32_t)__src_len;
    char *char_head = (char *)(buffer + 1);
    register uint64_t i;
    srand(__src_len);
    for (i = 0; i < __src_len; i++)
        encrypt_char(char_head+i,__src+i, rand());
    *__res = (char*)buffer;
    return STATUS_OK;
}

status_t decrypt_str(char **__res, char *__src)
{
    uint64_t __res_len = strlen(__src+sizeof(int32_t));
    char* char_head = __src + sizeof(int32_t);
    int32_t rand_seed = *((int32_t *)__src);
    char *buffer = (char *)malloc(__res_len);
    if(buffer == NULL)
        return ERR_NULLPTR;
    register uint64_t i;
    srand(rand_seed);
    for(i = 0; i < __res_len; i++)
        decrypt_char(buffer + i, char_head + i, rand());
    *__res = buffer;
    return STATUS_OK;
}