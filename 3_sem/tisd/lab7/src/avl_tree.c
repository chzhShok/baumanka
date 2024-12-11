#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int get_height(AVLNode *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}

int get_balance(AVLNode *node)
{
    if (node == NULL)
        return 0;

    return get_height(node->left) - get_height(node->right);
}

AVLNode *create_node_avl(char value)
{
    AVLNode *node = (AVLNode *) malloc(sizeof(AVLNode));
    if (node == NULL)
        return NULL;

    node->data = value;
    node->count = 1;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVLNode *rotate_right(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;

    return x;
}

AVLNode *rotate_left(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    return y;
}

AVLNode *insert_avl(AVLNode *root, char key)
{
    if (root == NULL)
        return create_node_avl(key);

    if (key < root->data)
    {
        root->left = insert_avl(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = insert_avl(root->right, key);
    }
    else
    {
        root->count++;
        return root;
    }

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);

    if (balance > 1 && key < root->left->data)
        return rotate_right(root);

    if (balance < -1 && key > root->right->data)
        return rotate_left(root);

    if (balance > 1 && key > root->left->data)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && key < root->right->data)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

AVLNode *find_min_avl(AVLNode *root)
{
    while (root->left != NULL)
        root = root->left;

    return root;
}

AVLNode *delete_node_avl(AVLNode *root, char data)
{
    if (root == NULL)
        return NULL;

    if (data < root->data)
        root->left = delete_node_avl(root->left, data);
    else if (data > root->data)
        root->right = delete_node_avl(root->right, data);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            AVLNode *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            AVLNode *temp = find_min_avl(root->right);
            root->data = temp->data;
            root->right = delete_node_avl(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(get_height(root->left), get_height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0)
        return rotate_right(root);

    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0)
        return rotate_left(root);

    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

AVLNode *search_avl(AVLNode *root, char data, int *cmp_count)
{
    if (!root || root->data == data)
        return root;

    (*cmp_count)++;

    if (data < root->data)
        return search_avl(root->left, data, cmp_count);
    else
        return search_avl(root->right, data, cmp_count);
}

void free_tree_avl(AVLNode *root)
{
    if (root != NULL)
    {
        free_tree_avl(root->left);
        free_tree_avl(root->right);
        free(root);
    }
}

void balance_insertiions(BSTNode *root, AVLNode **new)
{
    if (root != NULL)
    {
        balance_insertiions(root->right, new);
        *new = insert_avl(*new, root->data);
        balance_insertiions(root->left, new);
    }
}

AVLNode *balance_tree(BSTNode *root)
{
    AVLNode *new_tree = NULL;
    balance_insertiions(root, &new_tree);
    free_tree_bst(root);
    return new_tree;
}

void generate_graphviz_avl(AVLNode *root, FILE *file)
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
        generate_graphviz_avl(root->left, file);
    }
    if (root->right)
    {
        fprintf(file, "    \"%c\" -> \"%c\";\n", root->data, root->right->data);
        generate_graphviz_avl(root->right, file);
    }
}

void save_tree_to_graphviz_avl(AVLNode *root, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Ошибка: невозможно создать файл %s\n", filename);
        return;
    }

    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [shape=circle];\n");
    generate_graphviz_avl(root, file);
    fprintf(file, "}\n");

    fclose(file);
}

void save_to_png_from_graphviz_avl(AVLNode *node, int option)
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
        save_tree_to_graphviz_avl(node, filename);

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
        save_tree_to_graphviz_avl(node, "../sub_tree_svg/sub_tree.dot");
        system("/usr/local/Cellar/graphviz/12.2.0/bin/dot -Tsvg ../sub_tree_svg/sub_tree.dot -o ../sub_tree_svg/sub_tree.svg");
        printf("Дерево сохранено записано в файл sub_tree_svg/sub_tree.svg\n");
    }
}
