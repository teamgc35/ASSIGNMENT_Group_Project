#include "as_compr_RLE.h"

#include "as_list.h"
#include "as_array.h"

#include <string.h>
#include <stdlib.h>

static void scan_src();

// 1. scan the input
// 2. count how many time a field appears
// 3. establish huffman tree
// 4. encode

void comprstr_RLE(RLE_compr_t *__dest, const char *__src)
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
    list_PushBack(&list, &tmp_node);
    __dest->nbytes = nLen;
    list_Finalize(&list, &(__dest->compr_buff));
    list_Destroy(&list);
}

void extrastr_RLE(char **__dest, const RLE_compr_t *__src)
{
    char *result = (char *)malloc(__src->nbytes+1);
    result[__src->nbytes] = '\0';
    uint64_t i = 0;
    uint64_t j;
    uint32_t k;
    RLEnode_t *node;
    while(i<__src->nbytes)
    {
        for (j = 0; j < __src->compr_buff.size; j++)
        {
            node = (RLEnode_t *)array_Get(&(__src->compr_buff), j);
            for(k = 0; k < node->times;k ++)
            {
                result[i] = node->ch;
                i++;
            }
        }
    }
    *__dest = result;
}