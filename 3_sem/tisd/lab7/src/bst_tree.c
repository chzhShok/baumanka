#include <stdio.h>
#include <stdlib.h>

#include "bst_tree.h"

BSTNode *create_node_bst(char data)
{
    BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
    node->data = data;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void free_tree_bst(BSTNode *root)
{
    if (root != NULL)
    {
        free_tree_bst(root->left);
        free_tree_bst(root->right);
        free(root);
    }
}

BSTNode *insert_bst(BSTNode *root, char data)
{
    if (!root)
        return create_node_bst(data);

    if (data < root->data)
        root->left = insert_bst(root->left, data);
    else if (data > root->data)
        root->right = insert_bst(root->right, data);
    else
        root->count++;

    return root;
}

BSTNode *search_bst(BSTNode *root, char data, int *cmp_count)
{
    if (!root)
        return root;

    (*cmp_count)++;

    if (root->data == data)
        return root;

    if (data < root->data)
        return search_bst(root->left, data, cmp_count);

    return search_bst(root->right, data, cmp_count);
}

BSTNode *min_value_node(BSTNode *node)
{
    BSTNode *current = node;

    while (current && current->left)
        current = current->left;

    return current;
}

BSTNode *delete_node_bst(BSTNode *root, char data)
{
    if (!root)
        return root;

    if (data < root->data)
    {
        root->left = delete_node_bst(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = delete_node_bst(root->right, data);
    }
    else
    {
        if (!root->left)
        {
            BSTNode *tmp = root->right;
            free(root);
            return tmp;
        }

        if (!root->right)
        {
            BSTNode *tmp = root->left;
            free(root);
            return tmp;
        }

        BSTNode *tmp = min_value_node(root->right);
        root->data = tmp->data;
        root->right = delete_node_bst(root->right, tmp->data);
    }

    return root;
}

void generate_graphviz_bst(BSTNode *root, FILE *file)
{
    if (!root)
        return;

    if (root->count > 1)
        fprintf(file, "    \"%c\" [color=red, fontcolor=red];\n", root->data);
    else
        fprintf(file, "    \"%c\";\n", root->data);

    if (root->left)
    {
        fprintf(file, "    \"%c\" -> \"%c\";\n", root->data, root->left->data);
        generate_graphviz_bst(root->left, file);
    }
    if (root->right)
    {
        fprintf(file, "    \"%c\" -> \"%c\";\n", root->data, root->right->data);
        generate_graphviz_bst(root->right, file);
    }
}

void save_tree_to_graphviz_bst(BSTNode *root, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Ошибка: невозможно создать файл %s\n", filename);
        return;
    }

    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=circle];\n");
    generate_graphviz_bst(root, file);
    fprintf(file, "}\n");

    fclose(file);
}

void save_to_png_from_graphviz_bst(BSTNode *node, int option)
{
    char *base_tree_filename = "tree";
    if (option == 1)
    {
        char *countEnv = getenv("count");
        int count = 1;

        if (countEnv)
            count = atoi(countEnv);

        char filename[256];
        snprintf(filename, sizeof(filename), "../tree_svg/%s%d.dot", base_tree_filename, count);

        // Сохраняем дерево в .dot файл
        save_tree_to_graphviz_bst(node, filename);

        char command[512];
        snprintf(command, sizeof(command),
                 "/usr/local/Cellar/graphviz/12.2.0/bin/dot -Tsvg %s -o ../tree_svg/%s%d.svg",
                 filename, base_tree_filename, count);
        system(command);

        printf("Дерево сохранено в файл tree_svg/%s%d.svg\n", base_tree_filename, count);

        count++;
        char newCountEnv[10];
        snprintf(newCountEnv, sizeof(newCountEnv), "%d", count);
        setenv("count", newCountEnv, 1);
    }
    else
    {
        save_tree_to_graphviz_bst(node, "../sub_tree_svg/sub_tree.dot");
        system("/usr/local/Cellar/graphviz/12.2.0/bin/dot -Tsvg ../sub_tree_svg/sub_tree.dot -o ../sub_tree_svg/sub_tree.svg");
        printf("Дерево сохранено записано в файл sub_tree_svg/sub_tree.svg\n");
    }
}

BSTNode *delete_duplicates(BSTNode *root)
{
    if (!root)
        return NULL;

    root->left = delete_duplicates(root->left);
    root->right = delete_duplicates(root->right);

    if (root->count > 1)
        root = delete_node_bst(root, root->data);

    return root;
}
