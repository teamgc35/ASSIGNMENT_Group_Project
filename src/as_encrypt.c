#include "as_encrypt.h"
#include "as_errno.h"
#include <string.h>
#include <stdlib.h>

#ifndef NDEBUG
#include <assert.h>
#endif

status_t encrypt_str(encrbuff_t *__res, const char *__src)
{
    if (__res == NULL)
        return ERR_NULLPTR;
    __res->nbytes = strlen(__src) + 1;
    char *result_buffer = (char *)malloc(__res->nbytes);
    result_buffer[__res->nbytes - 1] = '\0';
    srand(__res->nbytes);
    size_t opt_time = (__res->nbytes - 1) / BATCH_SIZE;
    size_t opt_rema = (__res->nbytes - 1) % BATCH_SIZE;
    register size_t i;
    register char rand_num;
    // Pack 4 bytes together.
    for (i = 0; i < opt_time; i++)
    {
        rand_num = (char)rand();
        result_buffer[0] = __src[0] + rand_num;
        result_buffer[1] = __src[1] + rand_num;
        result_buffer[2] = __src[2] + rand_num;
        result_buffer[3] = __src[3] + rand_num;
        result_buffer += BATCH_SIZE;
        __src += BATCH_SIZE;
    }
    rand_num = (char)rand();
    for (i = 0; i < opt_rema; i++)
        result_buffer[i] = __src[i] + rand_num;
    __res->buffer = result_buffer - opt_time * BATCH_SIZE;
    return STATUS_OK;
}

status_t decrypt_str(char **__res, const encrbuff_t *__src)
{
    if (__src == NULL)
        return ERR_NULLPTR;
    char *result_buffer = (char *)malloc(__src->nbytes);
    char *src_buffer = __src->buffer;
    result_buffer[__src->nbytes - 1] = '\0';
    srand(__src->nbytes);
    size_t opt_time = (__src->nbytes - 1) / BATCH_SIZE;
    size_t opt_rema = (__src->nbytes - 1) % BATCH_SIZE;
    register size_t i;
    register char rand_num;
    // Pack 4 bytes together.
    for (i = 0; i < opt_time; i++)
    {
        rand_num = (char)rand();
        result_buffer[0] = src_buffer[0] - rand_num;
        result_buffer[1] = src_buffer[1] - rand_num;
        result_buffer[2] = src_buffer[2] - rand_num;
        result_buffer[3] = src_buffer[3] - rand_num;
        result_buffer += BATCH_SIZE;
        src_buffer += BATCH_SIZE;
    }
    rand_num = (char)rand();
    for (i = 0; i < opt_rema; i++)
        result_buffer[i] = src_buffer[i] - rand_num;
    *__res = result_buffer - opt_time * BATCH_SIZE;

    return STATUS_OK;
}

status_t encrypt_buff(encrbuff_t *__res, const void *buffer, const size_t nbytes)
{
    if (__res == NULL)
        return ERR_NULLPTR;
    __res->nbytes = nbytes;
    int *result_buffer = (int *)malloc(nbytes);
    size_t opt_time = nbytes / BATCH_SIZE;
    size_t opt_rema = nbytes % BATCH_SIZE;

    register size_t i;
    register int rand_num;
    srand(nbytes);
    for (i = 0; i < opt_time; i++)
        result_buffer[i] = ((int *)buffer)[i] + rand();
    rand_num = rand();
    for (; i < opt_rema + opt_time; i++)
        result_buffer[i] = ((char *)buffer)[i] + (char)rand_num;
    __res->buffer = (char*)result_buffer;
    return STATUS_OK;
}

status_t decrypt_buff(void **__res, const encrbuff_t *__src)
{
    if (__src == NULL)
        return ERR_NULLPTR;
    int *result_buffer = (int *)malloc(__src->nbytes);
    size_t opt_time = __src->nbytes / BATCH_SIZE;
    size_t opt_rema = __src->nbytes % BATCH_SIZE;

    register size_t i;
    register int rand_num;
    srand(__src->nbytes);
    for (i = 0; i < opt_time; i++)
        result_buffer[i] = ((int *)(__src->buffer))[i] - rand();
    rand_num = rand();
    for (; i < opt_rema + opt_time; i++)
        result_buffer[i] = ((char *)(__src->buffer))[i] - (char)rand_num;
    *__res = result_buffer;
    return STATUS_OK;
}