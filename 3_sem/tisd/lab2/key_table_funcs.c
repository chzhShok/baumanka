#include <string.h>

#include "key_table_funcs.h"
#include "subscriber_funcs.h"

void create_key_array(subscriber_t subscribers[], key_t keys[], int num_subscribers)
{
    for (int i = 0; i < num_subscribers; i++)
    {
        keys[i].key_index = i + 1;
        strncpy(keys[i].surname, subscribers[i].surname, MAX_NAME_LEN);
        keys[i].index = subscribers[i].index;
    }
}

int save_keys_to_csv(const char *filename, key_t keys[], int num_keys)
{
    rewrite_indexes(keys, num_keys);

    FILE *file = fopen(filename, "w");
    if (!file)
        return ERROR_FILE_OPEN;

    fprintf(file, "Surname,Index\n");

    for (int i = 0; i < num_keys; i++)
        fprintf(file, "%s,%d\n", keys[i].surname, keys[i].index);

    fclose(file);
    return OK;
}

void print_keys(key_t keys[], int num_keys)
{
    printf("Таблица ключей:\n");
    printf("%-16s%-27s%-10s\n", "Индекс", "Фамилия", "Индекс таблицы");

    for (int i = 0; i < num_keys; i++)
        printf("%-10d%-20s%-10d\n", keys[i].key_index, keys[i].surname, keys[i].index);
}

void rewrite_indexes(key_t keys[], int num_subscribers)
{
    for (int i = 0; i < num_subscribers; i++)
    {
        keys[i].key_index = i + 1;
    }
}

void bubble_sort_keys(key_t keys[], int num_subscribers)
{
    int swapped;

    for (int i = 0; i < num_subscribers - 1; i++)
    {
        swapped = 0;

        for (int j = 0; j < num_subscribers - i - 1; j++)
            if (strcmp(keys[j].surname, keys[j + 1].surname) > 0)
            {
                key_t temp = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = temp;

                swapped = 1;
            }

        if (swapped == 0)
            break;
    }
}

int partition(key_t keys[], int low, int high)
{
    key_t pivot = keys[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (strcmp(keys[j].surname, pivot.surname) <= 0)
        {
            i++;
            key_t temp = keys[i];
            keys[i] = keys[j];
            keys[j] = temp;
        }
    }

    key_t temp = keys[i + 1];
    keys[i + 1] = keys[high];
    keys[high] = temp;

    return i + 1;
}

void quick_sort_keys(key_t keys[], int low, int high)
{
    if (low < high)
    {
        int pivot_index = partition(keys, low, high);
        quick_sort_keys(keys, low, pivot_index - 1);
        quick_sort_keys(keys, pivot_index + 1, high);
    }
}
