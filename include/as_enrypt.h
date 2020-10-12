#ifndef __AS_ENRYPT_H__
#define __AS_ENRYPT_H__
#include "as_general.h"


/**
 * @description: translate an plaintext char into encrypted char
 * @param char*: Destination
 * @param char*: Source
 * @param int: the number to encrypt the char
 * @return status_t
 */
void encrypt_char(char *__dest, const char *__src, const int __num);

/**
 * @description: translate a plaintext string into encrypted string, this will do the malloc for the result.
 * @param char**: Encrypted string
 * @param char*: Source string
 * @param uint64_t: the length of Source string
 * @return status_t
 */
status_t encrypt_str(char **__res, const char *__src);

/**
 * @description: translate an encrypted char into plaintext char
 * @param char*: Destination
 * @param char*: Source
 * @param int: the number to decrypt the char
 * @return status_t
 */
void decrypt_char(char *__dest, const char *__src, const int __num);

/**
 * @description: translate an encrypted string into plaintext string
 * @param char**: Decrypted string
 * @param char*: Souce string
 * @param uint64_t: the length of source string
 * @return status_t
 */
status_t decrypt_str(char **__res, char *__src);

status_t encrypt_buffer(void **__dest, void *__src, const size_t nbytes);

status_t decrypt_buffer(void **__res, void *__src, const size_t nbytes);
#endif