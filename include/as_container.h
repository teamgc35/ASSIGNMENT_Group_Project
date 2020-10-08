#ifndef __AS_TYPES_H__
#define __AS_TYPES_H__

#include "as_general.h"
#include "as_errno.h"

#define NODE(T) \
    NODE_##T

#define LINKED_LIST(T) \
    LINKED_LIST_##T

#define DEFINE_NODE(T)          \
    typedef struct NODE_##T     \
    {                           \
        T data;                 \
        struct NODE_##T *pLast; \
        struct NODE_##T *pNext; \
    } NODE_##T

#define DEFINE_LINKED_LIST(T)      \
    typedef struct LINKED_LIST_##T \
    {                              \
        uint64_t length;           \
        NODE_##T *pLast;           \
        NODE_##T *pNext;           \
    } LINKED_LIST_##T



#endif