#include "as_enrypt.h"
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

    // TODO: 4 bytes use the same rand() result.
    register size_t i;
    for (i = 0; i < __res->nbytes - 1; i++)
        result_buffer[i] = __src[i] + (char)rand();
    __res->buffer = result_buffer;
    return STATUS_OK;
}

status_t decrypt_str(char **__res, const encrbuff_t *__src)
{
    if (__src == NULL)
        return ERR_NULLPTR;
    char *result_buffer = (char *)malloc(__src->nbytes);
    result_buffer[__src->nbytes - 1] = '\0';
    srand(__src->nbytes);

    register size_t i;
    for (i = 0; i < __src->nbytes - 1; i++)
        result_buffer[i] = __src->buffer[i] - (char)rand();
    *__res = result_buffer;
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
    for (i = 0; i < opt_time; i++)
        result_buffer[i] = ((int *)buffer)[i] + rand();
    rand_num = rand();
    for (; i < opt_rema + opt_time; i++)
        result_buffer[i] = ((char *)buffer)[i] + (char)rand_num;
    __res->buffer = result_buffer;
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
    for (i = 0; i < opt_time; i++)
        result_buffer[i] = ((int *)(__src->buffer))[i] - rand();
    rand_num = rand();
    for (; i < opt_rema + opt_time; i++)
        result_buffer[i] = ((char *)(__src->buffer))[i] - (char)rand_num;
    *__res = result_buffer;
    return STATUS_OK;
}