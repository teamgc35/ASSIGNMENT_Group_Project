#ifndef __AS_ARRAY_H__
#define __AS_ARRAY_H__

#include "as_general.h"


typedef struct array_t
{
    uint64_t capacity;
    uint64_t size;
    uint64_t element_size;
    char *data;
    int (*FindCondition)(const void* elem, const void* desire);
} array_t;


void array_Init(array_t *arr, const size_t capacity, const uint64_t elem_size, int (*FindCondition)(const void* elem, const void* desire));
void array_Destroy(array_t* arr);
status_t array_PushBack(array_t *arr, const void* buffer);
void * array_Get(const array_t *arr, const uint64_t index);
int64_t array_Find(const array_t* arr, const void* data);

#endif