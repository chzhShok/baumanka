#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 100

#define RED "\033[0;31m"
#define RESET "\033[0;37m"

struct Node
{
    char data;
    int count;
    int height;
    struct Node *left;
    struct Node *right;
};

struct Trunk
{
    struct Trunk *prev;
    char *str;
};

void print_tree(struct Node *root, struct Trunk *prev, int isLeft);
struct Node *insert(struct Node *root, char key);
void print_tree_as_string(struct Node *root);
struct Node *search(struct Node *root, char key);
struct Node *del_node(struct Node *root, char key);
void free_tree(struct Node *root);
struct Node *delete_duplicate_nodes(struct Node *root);

#endif
