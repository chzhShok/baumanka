#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "key_table_funcs.h"
#include "original_table_funcs.h"
#include "subscriber_funcs.h"

const char *surnames[] = {"Smith", "Johnson", "Williams", "Brown", "Jones"};
const char *names[] = {"John", "Michael", "Emily", "Sarah", "David"};
const char *streets[] = {"Main St", "High St", "Park Ave", "Oak St", "Maple St"};
const char *positions[] = {"Engineer", "Manager", "Developer", "Analyst", "Marketer"};
const char *organizations[] = {"TechCorp", "Innovatech", "BizSoft", "DataWorks", "Alpha Solutions"};

int random_int(long int min, long int max)
{
    return min + rand() % (max - min + 1);
}

void generate_random_subscriber(subscriber_t *subscriber)
{
    strcpy(subscriber->surname, surnames[random_int(0, 4)]);
    strcpy(subscriber->name, names[random_int(0, 4)]);
    sprintf(subscriber->phone, "8%010d", random_int(0, 9999999999));
    strcpy(subscriber->street, streets[random_int(0, 4)]);
    subscriber->house_number = random_int(1, 100);
    subscriber->status = random_int(0, 1) == 0 ? FRIEND : COLLEAGUE;

    if (subscriber->status == FRIEND)
    {
        subscriber->details.friend_info.birth_date.day = random_int(1, 28);
        subscriber->details.friend_info.birth_date.month = random_int(1, 12);
        subscriber->details.friend_info.birth_date.year = random_int(1950, 2005);
    }
    else
    {
        strcpy(subscriber->details.colleague_info.position, positions[random_int(0, 4)]);
        strcpy(subscriber->details.colleague_info.organization, organizations[random_int(0, 4)]);
    }
}

void generate_dataset(subscriber_t subscribers[], int dataset_size)
{
    srand(time(NULL));

    for (int i = 0; i < dataset_size; i++)
        generate_random_subscriber(&subscribers[i]);
}

void measure_sorting_times_bubble(subscriber_t subscribers[], key_t keys[], int num_subscribers)
{
    clock_t start, end;
    double bubble_sort_keys_time, bubble_sort_original_time;

    subscriber_t subscribers_bubble[num_subscribers];
    key_t keys_bubble[num_subscribers];

    memcpy(subscribers_bubble, subscribers, sizeof(subscriber_t) * num_subscribers);
    memcpy(keys_bubble, keys, sizeof(key_t) * num_subscribers);

    start = clock();
    bubble_sort_keys(keys_bubble, num_subscribers);
    end = clock();
    bubble_sort_keys_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    bubble_sort_subscribers(subscribers_bubble, num_subscribers);
    end = clock();
    bubble_sort_original_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nВремя затраченное на сортировку пузырьком ключей: %.6f сек.\n", bubble_sort_keys_time);
    printf("Время затраченное на сортировку пузырьком абонентов: %.6f сек.\n", bubble_sort_original_time);
    printf("Насколько сортировка абонентов дольше сортировки ключей: %.6f%%\n", (bubble_sort_original_time - bubble_sort_keys_time) * 100 / bubble_sort_keys_time);
}

void measure_sorting_times_quick(subscriber_t subscribers[], key_t keys[], int num_subscribers)
{
    clock_t start, end;
    double quick_sort_keys_time, quick_sort_original_time;

    subscriber_t subscribers_quick[num_subscribers];
    key_t keys_quick[num_subscribers];

    memcpy(subscribers_quick, subscribers, sizeof(subscriber_t) * num_subscribers);
    memcpy(keys_quick, keys, sizeof(key_t) * num_subscribers);

    start = clock();
    quick_sort_keys(keys_quick, 0, num_subscribers - 1);
    end = clock();
    quick_sort_keys_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    quick_sort_subscribers(subscribers_quick, 0, num_subscribers - 1);
    end = clock();
    quick_sort_original_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nВремя затраченное на быструю сортировку ключей: %.6f сек.\n", quick_sort_keys_time);
    printf("Время затраченное на быструю сортировку абонентов: %.6f seconds\n", quick_sort_original_time);
    printf("Насколько сортировка абонентов дольше сортировки ключей: %.6f%%\n", (quick_sort_original_time - quick_sort_keys_time) * 100 / quick_sort_keys_time);
}
