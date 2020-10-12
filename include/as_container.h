#ifndef __AS_TYPES_H__
#define __AS_TYPES_H__

#include "as_general.h"
#include "as_errno.h"

typedef struct listnode_t
{
    void *data;
    struct listnode_t *pLast;
    struct listnode_t *pNext;
} lnode_t;

typedef struct list_t
{
    uint64_t size;
    uint32_t element_size;
    lnode_t *head;
} list_t;

status_t list_Init(list_t* __list, uint32_t __elem_size);
status_t list_PushBack(list_t* __list, const void* __data);
status_t list_PushFront(list_t* __list, const void* __data);
status_t list_Destroy(list_t* __list);
status_t list_Insert(list_t* __list, const uint64_t index);
status_t list_InsertWithCondition(list_t* __list, int(*func)(const lnode_t* __node));

#endif