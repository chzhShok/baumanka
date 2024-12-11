#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "bst_tree.h"

typedef struct AVLNode
{
    char data;
    int height;
    int count;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode *insert_avl(AVLNode *root, char key);
AVLNode *delete_node_avl(AVLNode *root, char data);
AVLNode *search_avl(AVLNode *root, char data, int *cmp_count);
void free_tree_avl(AVLNode *root);

AVLNode *balance_tree(BSTNode *root);
void save_to_png_from_graphviz_avl(AVLNode *node, int option);

#endif//AVL_TREE_H
