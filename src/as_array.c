#include "as_array.h"
#include "as_errno.h"
#include <stdlib.h>
#include <string.h>

void array_Init(array_t *arr, const size_t capacity, const uint32_t elem_size, int (*FindCondition)(const void* elem, const void* desire))
{
    arr->capacity = capacity;
    arr->size = 0;
    arr->element_size = elem_size;
    arr->data = malloc(elem_size * capacity);
    arr->FindCondition = FindCondition;
}

void array_Destroy(array_t *arr)
{
    arr->size = 0;
    arr->element_size = 0;
    arr->capacity = 0;
    free(arr->data);
    arr->data = NULL;
}

status_t array_PushBack(array_t *arr, const void *buffer)
{
    if (arr->size == arr->capacity)
        return ERR_ARRFULL;
    memcpy(arr->data + arr->element_size * arr->size, buffer, arr->element_size);
    arr->size += 1;
    return STATUS_OK;
}
void *array_Get(const array_t *arr, const uint64_t index)
{
    if (index >= arr->size)
        return NULL;
    return arr->data + arr->element_size * index;
}

int64_t array_Find(const array_t* arr, const void* data)
{
    if (arr->FindCondition == NULL)
        return -2;
    register int64_t i;
    for (i = 0; i < arr->size; i++)
    {
        if (arr->FindCondition(arr->data+arr->element_size*i, data))
            return i;
    }
    return -1;
}