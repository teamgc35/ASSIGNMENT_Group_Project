#ifndef __AS_ENRYPT_H__
#define __AS_ENRYPT_H__
#include "as_general.h"

#define BATCH_SIZE 4

typedef struct encrypted_buffer
{
    size_t nbytes;
    char *buffer;
} encrbuff_t;

/**
 * @description: translate a plaintext string into encrypted string, this will do the malloc for the result.
 * @param char**: Encrypted string
 * @param char*: Source string
 * @param uint64_t: the length of Source string
 * @return status_t
 */
status_t encrypt_str(encrbuff_t *__res, const char *__src);

/**
 * @description: translate an encrypted string into plaintext string
 * @param char**: Decrypted string
 * @param char*: Souce string
 * @param uint64_t: the length of source string
 * @return status_t
 */
status_t decrypt_str(char **__res, const encrbuff_t *__src);

status_t encrypt_buff(encrbuff_t *__res, const void *buffer, const size_t nbytes);
status_t decrypt_buff(void **__res, const encrbuff_t *__src);
#endif