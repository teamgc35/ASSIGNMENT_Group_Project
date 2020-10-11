#ifndef __AS_TREE_H__
#define __AS_TREE_H__
#include "as_general.h"
#include "as_list.h"

typedef struct tree_node_t
{
    char ch;
    void *bits;
    uint64_t weight;
    struct tree_node_t* lNode;
    struct tree_node_t* rNode;
} tnode_t;

typedef struct huffman_tree_t
{
    uint64_t total_weight;
    tnode_t* root;
} hfmtree_t;

status_t hfmtree_Build(hfmtree_t *tree, const list_t* list);
status_t hfmtree_Get(hfmtree_t *tree, const char ch);
status_t hfmtree_Add(hfmtree_t *tree, const tnode_t *node);
#endif