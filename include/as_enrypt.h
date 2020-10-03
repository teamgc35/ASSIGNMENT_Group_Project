#ifndef __AS_ENRYPT_H__
#define __AS_ENRYPT_H__
#include "as_general.h"


/*
    Encrypted string
    The first 4 bytes is the first part of the rand seed
    The last 4 bytes is the second part of the rand seed
    if 
        the sum of first digit of first part of the seed and
        seccond one's is an odd number. The rand seed is first_part ^ second_part
    else 
        rand seed is first_part ^ second_part
*/


/**
 * @description: translate an plaintext char into encrypted char
 * @param char*: Destination
 * @param char*: Source
 * @param int: the number to encrypt the char
 * @return status_t
 */
void encrypt_char(char* __dest, const char* __src, const int __num);

/**
 * @description: translate a plaintext string into encrypted string, this will do the malloc for the result.
 * @param char**: Encrypted string
 * @param char*: Source string
 * @param uint64_t: the length of Source string
 * @return status_t
 */
status_t encrypt_str(char** __res, const char* __src);

/**
 * @description: translate an encrypted char into plaintext char
 * @param char*: Destination
 * @param char*: Source
 * @param int: the number to decrypt the char
 * @return status_t
 */
void decrypt_char(char* __dest, const char* __src, const int __num);

/**
 * @description: translate an encrypted string into plaintext string
 * @param char**: Decrypted string
 * @param char*: Souce string
 * @param uint64_t: the length of source string
 * @return status_t
 */
status_t decrypt_str(char** __res, char* __src);

#endif