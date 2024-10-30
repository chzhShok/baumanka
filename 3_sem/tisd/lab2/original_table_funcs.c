#include <stdio.h>
#include <string.h>
#include <time.h>

#include "key_table_funcs.h"
#include "original_table_funcs.h"
#include "subscriber_funcs.h"

int is_birthday_soon(int day, int month, int year, int current_day, int current_month, int current_year)
{
    struct tm current_tm = {0};
    struct tm birthday_tm = {0};

    current_tm.tm_year = current_year - 1900;
    current_tm.tm_mon = current_month - 1;
    current_tm.tm_mday = current_day;

    birthday_tm.tm_year = year - 1900;
    birthday_tm.tm_mon = month - 1;
    birthday_tm.tm_mday = day;

    time_t current_time = mktime(&current_tm);
    time_t birthday_time = mktime(&birthday_tm);

    double seconds_difference = difftime(birthday_time, current_time);
    double days_difference = seconds_difference / (60 * 60 * 24);

    return (days_difference >= 0 && days_difference <= 7);
}

void print_upcoming_birthdays(subscriber_t *subscribers, int num_subscribers, int current_day, int current_month, int current_year)
{
    printf("Друзья, которых необходимо поздравить с днем рождения в ближайшую неделю:\n");
    for (int i = 0; i < num_subscribers; i++)
    {
        if (subscribers[i].status == FRIEND)
        {
            if (is_birthday_soon(subscribers[i].details.friend_info.birth_date.day,
                                 subscribers[i].details.friend_info.birth_date.month,
                                 subscribers[i].details.friend_info.birth_date.year,
                                 current_day, current_month, current_year))
            {
                printf("%s %s, Дата рождения: %02d-%02d-%04d\n",
                       subscribers[i].surname,
                       subscribers[i].name,
                       subscribers[i].details.friend_info.birth_date.day,
                       subscribers[i].details.friend_info.birth_date.month,
                       subscribers[i].details.friend_info.birth_date.year);
            }
        }
    }
}

int append_to_csv_subscriber(const char *filename, subscriber_t *subscriber)
{
    FILE *file = fopen(filename, "a");
    if (!file)
        return ERROR_FILE_OPEN;

    fprintf(file, "%s,%s,%s,%s,%d,",
            subscriber->surname,
            subscriber->name,
            subscriber->phone,
            subscriber->street,
            subscriber->house_number);

    if (subscriber->status == FRIEND)
    {
        fprintf(file, "Friend,%02d-%02d-%04d\n",
                subscriber->details.friend_info.birth_date.day,
                subscriber->details.friend_info.birth_date.month,
                subscriber->details.friend_info.birth_date.year);
    }
    else if (subscriber->status == COLLEAGUE)
    {
        fprintf(file, "%s,%s\n",
                subscriber->details.colleague_info.position,
                subscriber->details.colleague_info.organization);
    }

    fclose(file);
    return OK;
}

int append_to_csv_key(const char *filename, key_t *key)
{
    FILE *file = fopen(filename, "a");
    if (!file)
        return ERROR_FILE_OPEN;

    fprintf(file, "%s,%d\n", key->surname, key->index);

    fclose(file);
    return OK;
}

int add_new_subscriber(subscriber_t subscribers[], int *num_subscribers, key_t keys[], const char *file, const char *key_file)
{
    if (*num_subscribers == NUM_ENTRIES)
    {
        printf("Массив заполнен\n");
    }
    else
    {
        int rc = input_subscriber(&subscribers[*num_subscribers], *num_subscribers);
        if (rc != OK)
            return rc;

        strncpy(keys[*num_subscribers].surname, subscribers[*num_subscribers].surname, MAX_NAME_LEN);
        keys[*num_subscribers].index = *num_subscribers;

        if (append_to_csv_subscriber(file, &subscribers[*num_subscribers]) == ERROR_FILE_OPEN)
            return rc;

        if (append_to_csv_key(key_file, &keys[*num_subscribers]) == ERROR_FILE_OPEN)
            return ERROR_FILE_OPEN;

        (*num_subscribers)++;
    }

    return OK;
}

int delete_subscriber(subscriber_t subscribers[], key_t keys[], int *num_subscribers, const char *surname, const char *file, const char *key_file)
{
    int found = -1;

    for (int i = 0; i < *num_subscribers; i++)
        if (strcmp(subscribers[i].surname, surname) == 0)
        {
            found = i;
            break;
        }

    if (found == -1)
        return NOT_FOUND;

    for (int i = found; i < *num_subscribers - 1; i++)
    {
        subscribers[i] = subscribers[i + 1];
        keys[i] = keys[i + 1];
    }

    (*num_subscribers)--;

    if (save_to_csv(subscribers, *num_subscribers, file) == ERROR_FILE_OPEN)
        return ERROR_FILE_OPEN;

    if (save_keys_to_csv(key_file, keys, *num_subscribers) == ERROR_FILE_OPEN)
        return ERROR_FILE_OPEN;

    return OK;
}

void print_subscribers(subscriber_t subscribers[], int num_subscribers)
{
    printf("Список абонентов:\n");
    printf("%-6s %-19s %-15s %-19s %-20s %-7s %-16s %-25s\n",
           "Индекс", "Фамилия", "Имя", "Телефон", "Улица", "Дом", "Статус", "Доп. информация");

    for (int i = 0; i < num_subscribers; i++)
    {
        printf("%-6d %-12s %-12s %-12s %-15s %-4d %-10s ",
               subscribers[i].index,
               subscribers[i].surname,
               subscribers[i].name,
               subscribers[i].phone,
               subscribers[i].street,
               subscribers[i].house_number,
               subscribers[i].status == FRIEND ? "Friend" : "Colleague");

        if (subscribers[i].status == FRIEND)
        {
            printf("%2d.%2d.%4d\n",
                   subscribers[i].details.friend_info.birth_date.day,
                   subscribers[i].details.friend_info.birth_date.month,
                   subscribers[i].details.friend_info.birth_date.year);
        }
        else
        {
            printf("%-12s %-12s\n",
                   subscribers[i].details.colleague_info.position,
                   subscribers[i].details.colleague_info.organization);
        }
    }
}

void bubble_sort_subscribers(subscriber_t subscribers[], int num_subscribers)
{
    int swapped;

    for (int i = 0; i < num_subscribers - 1; i++)
    {
        swapped = 0;

        for (int j = 0; j < num_subscribers - i - 1; j++)
            if (strcmp(subscribers[j].surname, subscribers[j + 1].surname) > 0)
            {
                subscriber_t temp = subscribers[j];
                subscribers[j] = subscribers[j + 1];
                subscribers[j + 1] = temp;

                swapped = 1;
            }

        if (swapped == 0)
            break;
    }
}

int partition_subscribers(subscriber_t subscribers[], int low, int high)
{
    subscriber_t pivot = subscribers[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (strcmp(subscribers[j].surname, pivot.surname) <= 0)
        {
            i++;
            subscriber_t temp = subscribers[i];
            subscribers[i] = subscribers[j];
            subscribers[j] = temp;
        }
    }

    subscriber_t temp = subscribers[i + 1];
    subscribers[i + 1] = subscribers[high];
    subscribers[high] = temp;

    return i + 1;
}

void quick_sort_subscribers(subscriber_t subscribers[], int low, int high)
{
    if (low < high)
    {
        int pivot_index = partition_subscribers(subscribers, low, high);

        quick_sort_subscribers(subscribers, low, pivot_index - 1);
        quick_sort_subscribers(subscribers, pivot_index + 1, high);
    }
}

void print_subscribers_by_keys(subscriber_t subscribers[], key_t keys[], int num_keys)
{
    printf("Список абонентов (по отсортированным ключам):\n");
    printf("%-6s %-19s %-15s %-19s %-20s %-7s %-16s %-25s\n",
           "Индекс", "Фамилия", "Имя", "Телефон", "Улица", "Дом", "Статус", "Доп. информация");

    for (int i = 0; i < num_keys; i++)
    {
        int index = keys[i].index - 1;
        printf("%-6d %-12s %-12s %-12s %-15s %-4d %-10s ",
               subscribers[index].index,
               subscribers[index].surname,
               subscribers[index].name,
               subscribers[index].phone,
               subscribers[index].street,
               subscribers[index].house_number,
               subscribers[index].status == FRIEND ? "Friend" : "Colleague");

        if (subscribers[index].status == FRIEND)
        {
            printf("%d.%d.%d\n",
                   subscribers[index].details.friend_info.birth_date.day,
                   subscribers[index].details.friend_info.birth_date.month,
                   subscribers[index].details.friend_info.birth_date.year);
        }
        else
        {
            printf("%s, %s\n",
                   subscribers[index].details.colleague_info.position,
                   subscribers[index].details.colleague_info.organization);
        }
    }
}
