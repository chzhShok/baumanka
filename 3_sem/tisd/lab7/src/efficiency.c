#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl_tree.h"
#include "bst_tree.h"
#include "efficiency.h"
#include "hash_table.h"

static char generate_random_char()
{
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    return charset[rand() % (sizeof(charset) - 1)];
}

static void generate_random_chars(char *chars, int count)
{
    for (int i = 0; i < count; i++)
        chars[i] = generate_random_char();
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
    const int levels[] = {2, 3, 5, 6, 7, 9, 10};
    const int levels_count = sizeof(levels) / sizeof(levels[0]);
    const int max_iter = 500;

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
            root_bst_tree = insert_bst(root_bst_tree, chars[j]);
            root_avl_tree = insert_avl(root_avl_tree, chars[j]);
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

        double avg_time_bst_tree = total_time_bst_tree / max_iter;
        double avg_time_avl_tree = total_time_avl_tree / max_iter;
        double avg_time_hash_table = total_time_hash_table / max_iter;

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
