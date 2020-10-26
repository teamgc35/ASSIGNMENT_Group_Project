#include "as_compr_RLE.h"

#include "as_list.h"
#include "as_array.h"

#include <string.h>
#include <stdlib.h>

void comprstr_RLE(RLE_compr_t *__dest, const char *__src)
{
    if (__dest == NULL)
    {
        _DEBUG("Destination is NULL.");
        return;
    }
    if(__src == NULL)
    {
        _DEBUG("Source is NULL.");
        return;
    }

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
    if(__src == NULL)
    {
        _DEBUG("Source is NULL.");
        return;
    }
    char *result = (char *)malloc(__src->nbytes + 1);
    result[__src->nbytes] = '\0';
    uint64_t i = 0;
    uint64_t j;
    uint32_t k;
    RLEnode_t *node;
    while (i < __src->nbytes)
    {
        for (j = 0; j < __src->compr_buff.size; j++)
        {
            node = (RLEnode_t *)array_Get(&(__src->compr_buff), j);
            for (k = 0; k < node->times; k++)
            {
                result[i] = node->ch;
                i++;
            }
        }
    }
    *__dest = result;
}

void comprbuff_RLE(RLE_compr_t *__dest, const void *__src, const uint64_t nbytes)
{
    if (__src == NULL)
    {
        _DEBUG("Source is NULL.");
        return;
    }
    if (__dest == NULL)
    {
        _DEBUG("Destination is NULL.");
        return;
    }
    list_t list;
    RLEnode_t tmp_node;

    list_Init(&list, sizeof(RLEnode_t));
    /* Cast any buffer into char ptr */
    char* buff = (char*)__src;
    tmp_node.ch = buff[0];
    tmp_node.times = 1;

    register uint64_t i;
    for (i = 1; i < nbytes; i++)
    {
        if (buff[i] == tmp_node.ch)
            tmp_node.times += 1;
        else
        {
            list_PushBack(&list, &tmp_node);
            tmp_node.ch = buff[i];
            tmp_node.times = 1;
        }
    }
    list_PushBack(&list, &tmp_node);
    __dest->nbytes = nbytes;
    list_Finalize(&list, &(__dest->compr_buff));
    list_Destroy(&list);
}

void extrabuff_RLE(void **__dest, const RLE_compr_t *__src)
{
    if (__src == NULL)
    {
        _DEBUG("Source is NULL.");
        return;
    }
    char *result = (char *)malloc(__src->nbytes + 1);
    result[__src->nbytes] = '\0';
    uint64_t i = 0;
    uint64_t j;
    uint32_t k;
    RLEnode_t *node;

    while (i < __src->nbytes)
    {
        for (j = 0; j < __src->compr_buff.size; j++)
        {
            node = (RLEnode_t *)array_Get(&(__src->compr_buff), j);
            for (k = 0; k < node->times; k++)
            {
                result[i] = node->ch;
                i++;
            }
        }
    }
    *__dest = (char *)result;
}

void RLE_compr_Dump(FILE *Fp, const RLE_compr_t* buff)
{
    if (buff == NULL)
    {
        _DEBUG("buffer is NULL");
        return;
    }
    if(Fp == NULL)
    {
        _DEBUG("Fp is NULL.");
        return;
    }
    /* save nbytes */
    fwrite(&(buff->nbytes), sizeof(uint64_t), 1, Fp);
    /* save how many RLEnode_t */
    fwrite(&(buff->compr_buff.size), sizeof(uint64_t), 1, Fp);
    /* Save RLEnode_t */
    fwrite(
            buff->compr_buff.data,
            sizeof(RLEnode_t),
            buff->compr_buff.size,
            Fp
            );
}
void RLE_compr_Load(FILE *Fp, RLE_compr_t* buff)
{
    if (buff == NULL)
    {
        _DEBUG("buffer is NULL");
        return;
    }
    if(Fp == NULL)
    {
        _DEBUG("Fp is NULL.");
        return;
    }
    uint64_t len;
    /* load nbytes */
    fread(&(buff->nbytes),sizeof(uint64_t), 1, Fp);
    /* load how many RLEnode_t */
    fread(&len, sizeof(uint64_t), 1, Fp);

    /* load compressed data */
    array_Init( &(buff->compr_buff),len, sizeof(RLEnode_t), NULL);
    buff->compr_buff.size = len;
    fread(buff->compr_buff.data, sizeof(RLEnode_t), len, Fp);
}
