#include "as_compr_RLE.h"

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

void compr_RLE(RLE_compr_t *__dest, const char *__src)
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
    __dest->total_bytes = nLen;
    list_Finalize(&list, &(__dest->compr_buff) );
    list_Destroy(&list);
}

void extract_RLE(void *__dest, const array_t *__src)
{
}