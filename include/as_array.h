#ifndef __AS_ARRAY_H__
#define __AS_ARRAY_H__

#include "as_general.h"


/* array container which can store Generic data */
typedef struct array_t
{
    uint64_t capacity;
    uint64_t size;
    uint64_t element_size;
    char *data;
    int (*FindCondition)(const void* elem, const void* desire);
} array_t;


/* Initialize array  */
void array_Init(array_t *arr, const size_t capacity, const uint64_t elem_size, int (*FindCondition)(const void* elem, const void* desire));

/* Destroy array free all the malloc buffer */
void array_Destroy(array_t* arr);

/* add an element at the end of the array, if array.size < array.capacity */
status_t array_PushBack(array_t *arr, const void* buffer);

/* access element in the array */
void * array_Get(const array_t *arr, const uint64_t index);

/* To ensure the function working, FindCondition function ptr should be assigned */
/*
 * -1 means not find
 * -2 means FindCondition function ptr is NULL
 * any val >= 0 means the matching record index
 * */
int64_t array_Find(const array_t* arr, const void* data);

#endif