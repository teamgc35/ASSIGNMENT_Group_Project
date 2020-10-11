#ifndef __AS_ARGPARSE_H__
#define __AS_ARGPARSE_H__
/**
 * @description: check if a short arg exist in the argv
 * @param int: arg count
 * @param char*[]: arg values
 * @param char sarg: the arg to look for
 * @return int: 1 or 0
 */
int has_sarg(int argc, const char** argv, const char sarg);

/**
 * @description: check if a long arg exist in the argv
 * @param int: arg count
 * @param char*[]: arg values
 * @param char*: larg, the arg to look for
 * @return int: 1 or 0
 */
int has_larg(int argc, const char** argv, const char* larg);

/**
 * @description: Retrive the value of a short arg from the argv
 * @param int: arg count
 * @param char*[]: arg values
 * @param char: sarg
 * @return char*: found value
 */
const char* get_sarg(int argc, const char** argv, const char sarg);

/**
 * @description: Retrive the value of a long arg from the argv
 * @param int: arg count
 * @param char*[]: arg values
 * @param char: larg
 * @return char*: found value
 */
const char *get_larg(int argc, const char **argv, const char *larg);

#endif