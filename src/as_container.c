#include "as_container.h"
#include <stdlib.h>
#include <string.h>

static lnode_t *lnode_init(void *data, uint32_t elem_size);

status_t list_Init(list_t *__list, uint32_t __elem_size)
{
    __list->size = 0;
    __list->element_size = __elem_size;
    __list->head = NULL;
}

status_t list_PushBack(list_t *__list, const void *__data)
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
    lnode_t *node = __list->head;
    while (node->pNext != node && node->pNext != NULL)
        node = node->pNext;
    node->pNext = lnode_init(__data, __list->element_size);
    __list->head->pLast = node->pNext;
    node->pNext->pLast = node;
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

/*
    Static Functions
    Prevent Other Bin to link it.
*/
static lnode_t *lnode_init(void *data, uint32_t elem_size)
{
    lnode_t *_node = (lnode_t *)malloc(sizeof(lnode_t));
    _node->data = malloc(elem_size);
    memcpy(_node->data, data, elem_size);
}