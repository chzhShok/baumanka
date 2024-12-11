#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

static unsigned int hash(int value, size_t size)
{
    return abs(value) % size;
}

static int is_prime(size_t n)
{
    if (n <= 1)
        return 0;

    for (int i = 2; i * i <= n; i++)

        if (n % i == 0)
            return 0;

    return 1;
}

static size_t next_prime(size_t n)
{
    n++;
    while (!is_prime(n))
        n++;

    return n;
}

HashTable *create_hash_table(size_t init_size)
{
    size_t prime_size = next_prime(init_size);
    HashTable *table = (HashTable *) malloc(sizeof(HashTable));
    if (!table)
        return NULL;

    table->size = prime_size;
    table->count = 0;
    table->buckets = (HashTableNode **) calloc(table->size, sizeof(HashTableNode *));
    if (!table->buckets)
    {
        free(table);
        return NULL;
    }

    return table;
}

static int resize_hash_table(HashTable *table)
{
    size_t new_size = next_prime(table->size);
    HashTableNode **new_buckets = (HashTableNode **) calloc(new_size, sizeof(HashTableNode *));
    if (!new_buckets)
        return 1;

    for (size_t i = 0; i < table->size; i++)
    {
        HashTableNode *current = table->buckets[i];
        while (current)
        {
            unsigned int new_index = hash(current->data, new_size);
            HashTableNode *next = current->next;
            current->next = new_buckets[new_index];
            new_buckets[new_index] = current;
            current = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->size = new_size;

    return 0;
}

int insert_hash_table(HashTable *hash_table, char data)
{
    unsigned int index = hash(data, hash_table->size);
    HashTableNode *current = hash_table->buckets[index];
    size_t chain_length = 0;

    while (current)
    {
        chain_length++;
        current = current->next;
    }

    if (chain_length >= 3)
    {
        if (resize_hash_table(hash_table) != 0)
            return 1;
        index = hash(data, hash_table->size);
    }

    HashTableNode *new_node = (HashTableNode *) malloc(sizeof(HashTableNode));
    if (!new_node)
        return 1;

    new_node->data = data;
    new_node->next = hash_table->buckets[index];
    hash_table->buckets[index] = new_node;
    hash_table->count++;

    return 0;
}

int search_hash_table(HashTable *table, char data, int *cmp_count)
{
    unsigned int index = hash(data, table->size);
    HashTableNode *current = table->buckets[index];

    while (current)
    {
        (*cmp_count)++;

        if (current->data == data)
            return 1;

        current = current->next;
    }

    return 0;
}

void delete_in_hash_table(HashTable *table, char data)
{
    unsigned int index = hash(data, table->size);
    HashTableNode *current = table->buckets[index];
    HashTableNode *prev = NULL;

    while (current)
    {
        if (current->data == data)
        {
            if (prev)
                prev->next = current->next;
            else
                table->buckets[index] = current->next;

            free(current);
            table->count--;
            return;
        }

        prev = current;
        current = current->next;
    }
}

void print_hash_table(HashTable *table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        printf("Контейнер %zu: ", i);
        HashTableNode *current = table->buckets[i];
        while (current)
        {
            printf("%c -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

void free_hash_table(HashTable **table)
{
    if (table == NULL || *table == NULL)
        return;

    for (size_t i = 0; i < (*table)->size; i++)
    {
        HashTableNode *current = (*table)->buckets[i];
        while (current)
        {
            HashTableNode *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free((*table)->buckets);
    (*table)->buckets = NULL;

    free(*table);
    *table = NULL;
}
