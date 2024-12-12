#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "avl_tree.h"
#include "bst_tree.h"
#include "efficiency.h"
#include "hash_table.h"

AVLNode *insert_avl_dupl(AVLNode *root, char value)
{
    if (root == NULL)
        return create_node_avl(value);

    if (value < root->data)
        root->left = insert_avl_dupl(root->left, value);
    else if (value > root->data)
        root->right = insert_avl_dupl(root->right, value);
    else
        return root;

    root->height =
            1 + (get_height(root->left) > get_height(root->right) ? get_height(root->left) : get_height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && value < root->left->data)
        return rotate_right(root);

    if (balance < -1 && value > root->right->data)
        return rotate_left(root);

    if (balance > 1 && value > root->left->data)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && value < root->right->data)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

BSTNode *insert_bst_dupl(BSTNode *root, char value)
{
    if (root == NULL)
    {
        root = create_node_bst(value);
        if (root == NULL)
            return NULL;

        return root;
    }

    if (value > root->data)
        root->right = insert_bst_dupl(root->right, value);
    else if (value < root->data)
        root->left = insert_bst_dupl(root->left, value);

    return root;
}

static char generate_random_char_from_ascii(int *used)
{
    while (1)
    {
        int index = rand() % 256;
        if (!used[index])
        {
            used[index] = 1;
            return (char) index;
        }
    }
}

static void generate_random_chars(char *chars, int count)
{
    int generated = 0;

    while (generated < count)
    {
        int used[256];
        memset(used, 0, sizeof(used));

        int to_generate = (count - generated > 256) ? 256 : (count - generated);

        for (int i = 0; i < to_generate; i++)
            chars[generated + i] = generate_random_char_from_ascii(used);

        generated += to_generate;
    }

    chars[count] = '\0';
}

static char get_random_char_from_array(const char *chars, int count)
{
    return chars[rand() % count];
}

size_t get_bst_tree_memory(BSTNode *root)
{
    if (!root)
        return 0;

    return sizeof(int) + sizeof(BSTNode) + sizeof(BSTNode) + get_bst_tree_memory(root->left) + get_bst_tree_memory(root->right);
}

size_t get_avl_tree_memory(AVLNode *root)
{
    if (!root)
        return 0;

    return sizeof(int) + sizeof(int) + sizeof(AVLNode) + sizeof(AVLNode) + get_avl_tree_memory(root->left) +
           get_avl_tree_memory(root->right);
}

size_t get_hash_table_memory(HashTable *table)
{
    if (!table)
        return 0;

    size_t memory = table->size * sizeof(HashTableNode) + sizeof(table->size) + sizeof(table->count);

    for (size_t i = 0; i < table->size; i++)
    {
        HashTableNode *current = table->buckets[i];
        while (current)
        {
            memory += sizeof(HashTableNode);
            current = current->next;
        }
    }

    return memory;
}

void measure_average_search_time(void)
{
    const int levels[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int levels_count = sizeof(levels) / sizeof(levels[0]);
    const int max_iter = 1000;

    struct timespec start, end;
    srand(time(NULL));

    for (int i = 0; i < levels_count; i++)
    {
        int level = levels[i];
        int num_elements = (int) (pow(2, level));

        for (int k = 0; k < 90; k++)
            printf("-");
        printf("\n\nКоличество элементов: %d\n", num_elements);

        double total_time_bst_tree = 0.0, total_time_avl_tree = 0.0, total_time_hash_table = 0.0;
        int cmp_cnt_bst_tree = 0, cmp_cnt_avl_tree = 0, cmp_cnt_hash_table = 0;

        char chars[MAX_ELEMENTS];
        generate_random_chars(chars, num_elements);

        BSTNode *root_bst_tree = NULL;
        AVLNode *root_avl_tree = NULL;
        HashTable *hash_table = create_hash_table(1);

        for (int j = 0; j < num_elements; j++)
        {
            root_bst_tree = insert_bst_dupl(root_bst_tree, chars[j]);
            root_avl_tree = insert_avl_dupl(root_avl_tree, chars[j]);
            insert_hash_table(hash_table, chars[j]);
        }

        for (int iter = 0; iter < max_iter; iter++)
        {
            char char_to_search = get_random_char_from_array(chars, num_elements);

            clock_gettime(CLOCK_MONOTONIC, &start);
            search_bst(root_bst_tree, char_to_search, &cmp_cnt_bst_tree);
            clock_gettime(CLOCK_MONOTONIC, &end);
            total_time_bst_tree += (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

            clock_gettime(CLOCK_MONOTONIC, &start);
            search_avl(root_avl_tree, char_to_search, &cmp_cnt_avl_tree);
            clock_gettime(CLOCK_MONOTONIC, &end);
            total_time_avl_tree += (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);

            clock_gettime(CLOCK_MONOTONIC, &start);
            search_hash_table(hash_table, char_to_search, &cmp_cnt_hash_table);
            clock_gettime(CLOCK_MONOTONIC, &end);
            total_time_hash_table += (end.tv_sec * 1e9 + end.tv_nsec) - (start.tv_sec * 1e9 + start.tv_nsec);
        }

        double avg_time_bst_tree = total_time_bst_tree / (double) max_iter;
        double avg_time_avl_tree = total_time_avl_tree / (double) max_iter;
        double avg_time_hash_table = total_time_hash_table / (double) max_iter;

        int avg_cmp_cnt_bst_tree = (int) floor((double) cmp_cnt_bst_tree / max_iter);
        int avg_cmp_cnt_avl_tree = (int) floor((double) cmp_cnt_avl_tree / max_iter);
        int avg_cmp_cnt_hash_table = (int) floor((double) cmp_cnt_hash_table / max_iter);

        size_t memory_bst_tree = get_bst_tree_memory(root_bst_tree);
        size_t memory_avl_tree = get_avl_tree_memory(root_avl_tree);
        size_t memory_hash_table = get_hash_table_memory(hash_table);

        printf("--- Время поиска (нс) ---\n");
        printf("BST дерево: %.2f\n", avg_time_bst_tree);
        printf("AVL дерево: %.2f\n", avg_time_avl_tree);
        printf("Хеш-таблица: %.2f\n", avg_time_hash_table);
        printf("\n");
        printf("--- Количество сравнений ---\n");
        printf("BST дерево: %d\n", avg_cmp_cnt_bst_tree);
        printf("AVL дерево: %d\n", avg_cmp_cnt_avl_tree);
        printf("Хеш-таблица: %d\n", avg_cmp_cnt_hash_table);
        printf("\n");
        printf("--- Память ---\n");
        printf("BST дерево: %zu\n", memory_bst_tree);
        printf("AVL дерево: %zu\n", memory_avl_tree);
        printf("Хеш-таблица: %zu\n", memory_hash_table);

        free_tree_bst(root_bst_tree);
        free_tree_avl(root_avl_tree);
        free_hash_table(&hash_table);
    }

    printf("\n");
}
