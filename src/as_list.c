#include "as_list.h"
#include "as_array.h"
#include <stdlib.h>
#include <string.h>

static lnode_t *lnode_init(const void *data, const uint64_t elem_size);

void list_Init(list_t *__list, const uint64_t __elem_size)
{
    __list->size = 0;
    __list->element_size = __elem_size;
    __list->head = NULL;
}

lnode_t *list_Get(const list_t *__list, const uint64_t __index)
{
    if (__index > __list->size)
    {
        as_seterr(ERR_RANGE, "out of range.");
        return NULL;
    }
    if (__index == __list->size)
        return __list->head->pLast;
    register uint64_t i;
    lnode_t *node = __list->head;
    for (i = 0; i < __index; i++)
        node = node->pNext;
    return node;
}

status_t list_PushBack(list_t *__list, const void *__data)
{
    // TODO: Duo Linked List PushBack can be optimize.
    if (__list == NULL)
    {
        as_seterr(ERR_NULLPTR, "list operation does not accept NULL list.");
        return ERR_NULLPTR;
    }
    if (__list->head == NULL)
    {
        __list->head = lnode_init(__data, __list->element_size);
        __list->head->pLast = __list->head;
        __list->head->pNext = __list->head;
        __list->size += 1;
        return STATUS_OK;
    }
    lnode_t *node = __list->head;
    register uint64_t i;
    while (node->pNext != __list->head && node->pNext != NULL)
        node = node->pNext;
    node->pNext = lnode_init(__data, __list->element_size);
    __list->head->pLast = node->pNext;
    node->pNext->pLast = node;
    node->pNext->pNext = __list->head;
    __list->size += 1;
    return STATUS_OK;
}

status_t list_PushFront(list_t *__list, const void *__data)
{
    if (__list == NULL)
    {
        as_seterr(ERR_NULLPTR, "list operation does not accept NULL list.");
        return ERR_NULLPTR;
    }
    if (__list->head == NULL)
    {
        __list->head = lnode_init(__data, __list->element_size);
        __list->head->pLast = __list->head;
        __list->head->pNext = __list->head;
        __list->size += 1;
        return STATUS_OK;
    }
    lnode_t *new_node = lnode_init(__data, __list->element_size);
    lnode_t *node = __list->head;
    __list->head->pLast = new_node;
    while (node->pNext != __list->head)
        node = node->pNext;
    node->pNext = new_node;
    new_node->pLast = node;
    new_node->pNext = __list->head;
    __list->head = new_node;
    __list->size += 1;
    return STATUS_OK;
}

status_t list_Destroy(list_t *__list)
{
    if (__list == NULL)
        return ERR_NULLPTR;
    if (__list->size == 0)
        return STATUS_OK;
    register uint64_t i;
    lnode_t *node = __list->head;
    lnode_t *pNext = node->pNext;
    if (__list->size == 1)
    {
        free(node);
        return STATUS_OK;
    }
    for (i = 0; i < (__list->size - 1); i++)
    {
        free(node);
        node = pNext;
        pNext = node->pNext;
    }
    free(node);
    return STATUS_OK;
}

status_t list_Insert(list_t *__list, const uint64_t __index, void *__data)
{
    if (__index > __list->size)
        return ERR_RANGE;
    if (__index == 0)
    {
        list_PushFront(__list, __data);
        return STATUS_OK;
    }
    if (__index == __list->size)
    {
        list_PushBack(__list, __data);
        return STATUS_OK;
    }
    lnode_t *node = __list->head;
    register uint64_t i;
    /* Loop Through to find the required index node */
    for (i = 0; i < __index; i++)
        node = node->pNext;
    if (node == NULL)
        return ERR_NULLPTR;
    lnode_t *prev = node->pLast;
    lnode_t *new_node = lnode_init(__data, __list->element_size);
    new_node->pNext = node;
    new_node->pLast = prev;
    prev->pNext = new_node;
    return STATUS_OK;
}

void list_Finalize(const list_t *__list, array_t *__dest)
{
    array_Init(__dest, __list->size, __list->element_size, NULL);
    register uint64_t i;
    lnode_t *node;
    for (i = 0; i < __list->size; i++) {
        node = list_Get(__list, i);
        array_PushBack(__dest, node->data);
    }
}
/*
    Static Functions
    Prevent Other obj to link it.
*/
static lnode_t *lnode_init(const void *data, const uint64_t elem_size)
{
    lnode_t *_node = (lnode_t *)malloc(sizeof(lnode_t));
    _node->data = malloc(elem_size);
    memcpy(_node->data, data, elem_size);
    return _node;
}