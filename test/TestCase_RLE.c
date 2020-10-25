#include "as_general.h"
#include "as_compr_RLE.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

void Test_NotAlignStruct()
{
    assert( sizeof(RLEnode_t) == (sizeof(uint32_t) + sizeof(char)));
    printf("Not Align Struct PASS!\n");
}

void Test_StringCompression()
{
    const char *src_str = "Good!!!!";
    RLE_compr_t compressed;
    comprstr_RLE(&compressed, src_str);
    RLEnode_t *node;
    assert(compressed.nbytes == strlen(src_str));
    assert(compressed.compr_buff.size == 4);

    node = (RLEnode_t *)array_Get(&(compressed.compr_buff), 0);
    assert(node->ch == 'G');
    assert(node->times == 1);

    node = (RLEnode_t *)array_Get(&(compressed.compr_buff), 1);
    assert(node->ch == 'o');
    assert(node->times == 2);

    node = (RLEnode_t *)array_Get(&(compressed.compr_buff), 2);
    assert(node->ch == 'd');
    assert(node->times == 1);

    node = (RLEnode_t *)array_Get(&(compressed.compr_buff), 3);
    assert(node->ch == '!');
    assert(node->times == 4);
    printf("RLE String Compress PASS!\n");
}

void Test_StringExtraction()
{
    const char* src_str = "Good!!!!sfkjdhglkjfdsN<NNNNNNHASD";
    RLE_compr_t compressed;
    char* extracted;
    comprstr_RLE(&compressed, src_str);
    extrastr_RLE(&extracted, &compressed);
    assert(!strcmp(src_str, extracted));
    printf("RLE String Extract PASS\n");
}

void Test_BufferCompression()
{
    double num1 = 10000;
    RLE_compr_t compressed;
    comprbuff_RLE(&compressed, &num1, sizeof(double));
    assert(compressed.nbytes==sizeof(double));
    printf("RLE Buffer Compress PASS.\n");
}

void Test_BufferExtraction1()
{
    double num1 = 1000;
    RLE_compr_t compressed;
    double *extracted;
    comprbuff_RLE(&compressed, &num1, sizeof(double));
    extrabuff_RLE((void**)&extracted, &compressed);
    assert(*extracted == num1);
    printf("RLE Buffer Extract1 PASS.\n");
}

void Test_BufferExtraction2()
{
    double nums[5] = {1,2,3,4,5};
    RLE_compr_t compressed;
    double *extracted;
    comprbuff_RLE(&compressed, nums, sizeof(double)*5);
    extrabuff_RLE((void**)&extracted, &compressed);
    for(int i = 0; i < 5; i++)
        assert(extracted[i] == nums[i]);
    printf("RLE Buffer Exracte2 PASS.\n");
}

int main()
{
    printf("Test Case RLE begin...\n");
    Test_NotAlignStruct();
    Test_StringCompression();
    Test_StringExtraction();
    Test_BufferCompression();
    Test_BufferExtraction1();
    Test_BufferExtraction2();
}