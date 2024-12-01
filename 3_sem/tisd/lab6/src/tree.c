#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

Node *create_node(char data)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void free_tree(Node *root)
{
    if (root != NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

Node *insert(Node *root, char data)
{
    if (!root)
        return create_node(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        root->count++;

    return root;
}

Node *search(Node *root, char data)
{
    if (!root || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);

    return search(root->right, data);
}

Node *min_value_node(Node *node)
{
    Node *current = node;

    while (current && current->left)
        current = current->left;

    return current;
}

Node *delete_node(Node *root, char data)
{
    if (!root)
        return root;

    if (data < root->data)
    {
        root->left = delete_node(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = delete_node(root->right, data);
    }
    else
    {
        if (!root->left)
        {
            Node *tmp = root->right;
            free(root);
            return tmp;
        }

        if (!root->right)
        {
            Node *tmp = root->left;
            free(root);
            return tmp;
        }

        Node *tmp = min_value_node(root->right);
        root->data = tmp->data;
        root->right = delete_node(root->right, tmp->data);
    }

    return root;
}

void generate_graphviz(Node *root, FILE *file)
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
        generate_graphviz(root->left, file);
    }
    if (root->right)
    {
        fprintf(file, "    \"%c\" -> \"%c\";\n", root->data, root->right->data);
        generate_graphviz(root->right, file);
    }
}

void save_tree_to_graphviz(Node *root, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Ошибка: невозможно создать файл %s\n", filename);
        return;
    }

    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=circle];\n");
    generate_graphviz(root, file);
    fprintf(file, "}\n");

    fclose(file);
}

void save_to_png_from_graphviz(Node *node, int option)
{
    char *base_tree_filename = "tree";
    if (option == 1)
    {
        char *countEnv = getenv("count");
        int count = 1;

        if (countEnv)
            count = atoi(countEnv);

        char filename[256];
        snprintf(filename, sizeof(filename), "tree_svg/%s%d.dot", base_tree_filename, count);

        // Сохраняем дерево в .dot файл
        save_tree_to_graphviz(node, filename);

        char command[512];
        snprintf(command, sizeof(command),
                 "/usr/local/Cellar/graphviz/12.2.0/bin/dot -Tsvg %s -o tree_svg/%s%d.svg",
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
        save_tree_to_graphviz(node, "sub_tree_svg/sub_tree.dot");
        system("/usr/local/Cellar/graphviz/12.2.0/bin/dot -Tsvg sub_tree_svg/sub_tree.dot -o sub_tree_svg/sub_tree.svg");
        printf("Дерево сохранено записано в файл sub_tree_svg/sub_tree.svg\n");
    }
}

void post_order(Node *root)
{
    if (!root)
        return;

    post_order(root->left);
    post_order(root->right);
    printf("%c ", root->data);
}

Node *delete_duplicates(Node *root)
{
    if (!root)
        return NULL;

    root->left = delete_duplicates(root->left);
    root->right = delete_duplicates(root->right);

    if (root->count > 1)
        root = delete_node(root, root->data);

    return root;
}
