#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "efficiency.h"
#include "tree.h"

void random_string(char *str, int n)
{
    srand(CLOCK_MONOTONIC_RAW);

    for (int i = 0; i < n - 1; ++i)
    {
        char c = rand() % (256);
        str[i] = c;
    }

    str[n - 1] = '\0';
}

void remove_duplicates(char *str)
{
    int len = (int) strlen(str);

    if (len <= 1)
        return;

    int tail = 1;

    for (int i = 1; i < len; ++i)
    {
        int j;
        for (j = 0; j < tail; ++j)
            if (str[i] == str[j])
                break;

        if (j == tail)
            str[tail++] = str[i];
    }

    str[tail] = '\0';
}

void calc_size_tree(struct Node *root, int *size)
{
    if (root != NULL)
    {
        calc_size_tree(root->left, size);
        *size += sizeof(struct Node);
        calc_size_tree(root->right, size);
    }
}

double calc_mean(const long long data[], int length)
{
    long long sum = 0;
    for (size_t i = 0; i < length; i++)
        sum += data[i];
    return (double) sum / (double) length;
}

double run_tests_str(char *str)
{
    char tmp[MAX_STR_LEN];
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        strcpy(tmp, str);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        remove_duplicates(tmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        test_arr[i] = (end.tv_sec - start.tv_sec) * COEFF + end.tv_nsec - start.tv_nsec;
    }

    avr = calc_mean(test_arr, MAX_NUM_TESTS);
    printf("Реализация с помощью строки: %.2lf нс\n", avr);
    return avr;
}

double run_tests_tree(char *str)
{
    struct Node *root = NULL;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        for (int j = 0; str[j] != '\0'; j++)
            root = insert(root, str[j]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        root = delete_duplicates(root);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        free_tree(root);
        root = NULL;
        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    }

    avr = calc_mean(test_arr, MAX_NUM_TESTS);
    printf("Реализация с помощью дерева: %.2lf нс\n", avr);
    return avr;
}

double run_tests_tree_find(char *str)
{
    struct Node *root = NULL;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    char s = 'a';
    struct Node *tmp;

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        for (int j = 0; str[j] != '\0'; j++)
            root = insert(root, str[j]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        tmp = search(root, s);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        (void) tmp;
        free_tree(root);
        root = NULL;
        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    }

    avr = calc_mean(test_arr, MAX_NUM_TESTS);
    printf("Реализация с помощью дерева: %.2lf нс\n", avr);
    return avr;
}

void compare_delete_duplicates(void)
{
    for (int i = 0; i < 99; ++i)
        printf("-");

    for (int l_str = 10; l_str < MAX_STR_LEN; l_str += 100)
    {
        printf("\n" PURPLE);
        double avr_str, avr_tree;

        printf("Длина строки: %d\n", l_str);
        printf("Количество итераций: %d\n\n", MAX_NUM_TESTS);

        char str[MAX_STR_LEN];
        random_string(str, l_str);

        avr_str = run_tests_str(str);
        int size_str = (int) (sizeof(char) * (l_str));
        printf("Занимаемая память: %d байт\n\n", size_str);

        avr_tree = run_tests_tree(str);
        struct Node *root = NULL;
        for (int i = 0; str[i] != '\0'; i++)
            root = insert(root, str[i]);
        int size_tree = 0;
        calc_size_tree(root, &size_tree);
        printf("Занимаемая память: %d байт\n\n", size_tree);

        free_tree(root);

        printf("Производительность: реализация с помощью строки дольше на %lf %%\n", (avr_str / avr_tree - 1) * 100);
        printf("Память: реализация с помощью строки больше на %lf %%\n", ((double) size_str / size_tree - 1) * 100);

        for (size_t i = 0; i < 99; ++i)
            printf("-");
        printf("\n" RESET);
    }
}

void compare_search(void)
{
    for (int i = 0; i < 99; ++i)
        printf("-");

    for (int l_str = 10; l_str < MAX_STR_LEN; l_str += 100)
    {
        printf("\n"PURPLE);
        double avr2;

        printf("Длина строки: %d\n", l_str);
        printf("Количество итераций: %d\n\n", MAX_NUM_TESTS);

        char str[MAX_STR_LEN];
        random_string(str, l_str);

        avr2 = run_tests_tree_find(str);
        (void) avr2;
        struct Node *root = NULL;
        for (int i = 0; str[i] != '\0'; i++)
            root = insert(root, str[i]);
        int size2 = 0;
        calc_size_tree(root, &size2);
        printf("Занимаемая память: %d байт\n", size2);

        free_tree(root);

        for (size_t i = 0; i < 99; ++i)
            printf("-");
        printf("\n" RESET);
    }
}
