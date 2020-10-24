#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <stdio.h>
#include <stdlib.h>

#ifndef NDEBUG
#define _DEBUGF(fmt, ...) fprintf(stderr, "%s:%d in %s | " fmt "\n", __FILE__, __LINE__, __FUNCTION__ , __VA_ARGS__)
#define _DEBUG(msg) fprintf(stderr, "%s:%d in %s | %s\n", __FILE__, __LINE__, __FUNCTION__, msg)
#else 
#define _DEBUG(msg)
#endif

typedef int status_t;

typedef int int32_t;
typedef unsigned int uint32_t;
typedef long int64_t;
typedef unsigned long uint64_t;
typedef uint64_t size_t;
typedef float float32_t;
typedef double float64_t;
typedef unsigned char byte;
typedef char sbyte; /* signed byte */

#define MAX_PASSWD_LEN 31
#define MAX_MAP_HEAD 128


#define TITLE "<HD PROGRAM>"

#endif