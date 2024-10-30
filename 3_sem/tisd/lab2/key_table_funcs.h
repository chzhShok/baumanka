#ifndef KEY_TABLE_FUNCS_H
#define KEY_TABLE_FUNCS_H

#include <stdio.h>

#include "subscriber_funcs.h"

typedef struct
{
    int key_index;
    char surname[MAX_NAME_LEN];
    int index;
} key_t;

void create_key_array(subscriber_t subscribers[], key_t keys[], int num_subscribers);
int save_keys_to_csv(const char *filename, key_t keys[], int num_keys);
void print_keys(key_t keys[], int num_keys);

void rewrite_indexes(key_t keys[], int num_subscribers);
void bubble_sort_keys(key_t keys[], int num_subscribers);
void quick_sort_keys(key_t keys[], int low, int high);

#endif//KEY_TABLE_FUNCS_H
