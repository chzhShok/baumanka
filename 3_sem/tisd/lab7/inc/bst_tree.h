#ifndef BST_TREE_H
#define BST_TREE_H

typedef struct BSTNode
{
    char data;
    int count;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *create_node_bst(char data);
BSTNode *insert_bst(BSTNode *root, char data);
BSTNode *delete_node_bst(BSTNode *root, char data);
void free_tree_bst(BSTNode *root);
void save_to_png_from_graphviz_bst(BSTNode* node, int option);
BSTNode *search_bst(BSTNode *root, char data, int *cmp_count);
BSTNode *delete_duplicates(BSTNode *root);

#endif//BST_TREE_H
