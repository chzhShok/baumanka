#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

typedef struct HashTableNode
{
    char data;
    struct HashTableNode *next;
} HashTableNode;

typedef struct HashTable
{
    HashTableNode **buckets;
    size_t size;
    size_t count;
} HashTable;

HashTable *create_hash_table(size_t init_size);
int insert_hash_table(HashTable *hash_table, char data);
int search_hash_table(HashTable *table, char data, int *cmp_count);
void delete_in_hash_table(HashTable *table, char data);
void print_hash_table(HashTable *table);
void free_hash_table(HashTable **table);

#endif//HASH_TABLE_H
