#ifndef __AS_FUNCTIONAL_H__
#define __AS_FUNCTIONAL_H__

#include <stdio.h> /* FILE */

#ifndef NDEBUG
#include <assert.h> /* assert */
#endif

#include "as_general.h"

/**
 * @description: This will encrypte the file according to the password giving
 * @param {char*}: password
 * @param {FILE*}: source file
 * @param {FILE*}: output file
 * @return {status_t}
 */
status_t Fn_encrypt_file(const char *password, FILE* src, FILE* out);

/**
 * @description: This will dencrypte the file according to the password giving
 * @param {char*}: password
 * @param {FILE*}: source file
 * @param {FILE*}: output file
 * @return {status_t}: if password isn't correct ERR_CREDENTIAL will be returned
 */
status_t Fn_decrypt_file(const char *password, FILE* src, FILE* out);

/**
 * @description: The will compress a file using RLE method
 * @param {FILE*}: source file
 * @param {FILE*}: output file
 * @return {status_t}
 */
status_t Fn_compress_file(FILE *src, FILE* out);

/**
 * @description: The will extract a RLE compressed file
 * @param {FILE*}: source file
 * @param {FILE*}: output file
 * @return {status_t}
 */
status_t Fn_extract_file(FILE *src, FILE* out);
#endif