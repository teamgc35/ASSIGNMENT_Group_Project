#include "as_compress.h"
#include "as_list.h"
#include "as_array.h"

#include <string.h>

static void scan_src();

// 1. scan the input
// 2. count how many time a field appears
// 3. establish huffman tree
// 4. encode

typedef struct rle_node_t
{
    char ch;
    uint32_t times;
} RLEnode_t;

int FindCondition(const void *elem, const void *desire)
{
    char *e = (char *)elem;
    char *d = (char *)desire;
    if (*e == *d)
        return 1;
    return 0;
}

void compr_RLE(array_t *__dest, const char *__src)
{
    /* Use continuous array for better scan performance */
    list_t list;
    size_t nLen;
    RLEnode_t tmp_node;

    register uint64_t i;
    nLen = strlen(__src);
    list_Init(&list, sizeof(RLEnode_t));
    tmp_node.ch = __src[0];
    tmp_node.times = 1;

    for (i = 1; i < nLen; i++)
    {
        if (__src[i] == tmp_node.ch)
            tmp_node.times += 1;
        else
        {
            list_PushBack(&list, &tmp_node);
            tmp_node.ch = __src[i];
            tmp_node.times = 1;
        }
    }
    list_Finalize(&list, __dest);
    list_Destroy(&list);
}