#ifndef __AS_TYPES_H__
#define __AS_TYPES_H__

#include "as_general.h"
#include "as_errno.h"
#include "as_array.h"

typedef struct listnode_t
{
    void *data;
    struct listnode_t *pLast;
    struct listnode_t *pNext;
} lnode_t;

typedef struct list_t
{
    uint64_t size;
    uint64_t element_size;
    lnode_t *head;
} list_t;

void list_Init(list_t* __list, const uint64_t __elem_size);
lnode_t* list_Get(const list_t* __list, const uint64_t __index);
void* list_GetData(const list_t* __list, const uint64_t __index);
status_t list_PushBack(list_t* __list, const void* __data);
status_t list_PushFront(list_t* __list, const void* __data);
void list_Destroy(list_t* __list);
status_t list_Insert(list_t* __list, const uint64_t __index, void* __data);

/**
 * @description: This will finalize the linked list, store the continuous data into __dest;
 * @param list_t*: which list to store
 * @param void** : where to store
 */
void list_Finalize(const list_t* __list, array_t *__dest);

#endif