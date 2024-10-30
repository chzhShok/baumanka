#ifndef ORIGINAL_TABLE_FUNCS_H
#define ORIGINAL_TABLE_FUNCS_H

#include "subscriber_funcs.h"

#define NOT_FOUND (-1)

void print_upcoming_birthdays(subscriber_t *subscribers, int num_subscribers, int current_day, int current_month, int current_year);
int add_new_subscriber(subscriber_t subscribers[], int *num_subscribers, key_t keys[], const char *file, const char *key_file);
int delete_subscriber(subscriber_t subscribers[], key_t keys[], int *num_subscribers, const char *surname, const char *file, const char *key_file);
void bubble_sort_subscribers(subscriber_t subscribers[], int num_subscribers);
void print_subscribers(subscriber_t subscribers[], int num_subscribers);
void print_subscribers_by_keys(subscriber_t subscribers[], key_t keys[], int num_keys);
void quick_sort_subscribers(subscriber_t subscribers[], int low, int high);

#endif//ORIGINAL_TABLE_FUNCS_H
