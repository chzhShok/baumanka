#ifndef TREE_H
#define TREE_H

typedef struct Node {
    char data;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(char data);
Node *insert(Node *root, char data);
Node *delete_node(Node *root, char data);
void free_tree(struct Node *root);
void save_to_png_from_graphviz(Node* node, int option);
void post_order(Node *root);
Node *search(Node *root, char data);
Node *delete_duplicates(Node *root);

#endif
