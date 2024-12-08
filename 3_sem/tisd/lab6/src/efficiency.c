#include <math.h>
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

void *sorted_string(char *str, int n)
{
    char el = 0;

    for (int i = 0; i < n - 1; i++)
    {
        str[i] = el;
        el++;
    }

    str[n - 1] = '\0';
}

int compare_chars(const void *a, const void *b)
{
    return *(char *) a - *(char *) b;
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

void measure_search_time(Node *root, char data)
{
    struct timespec start, end;
    double avr;
    long long test_arr[MAX_NUM_TESTS];

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        Node *result = search(root, data);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    }

    avr = calc_mean(test_arr, MAX_NUM_TESTS);
    printf("Время поиска в дереве: %.2f нс\n", avr);
}

void compare_search(void)
{
    Node *tree_1 = NULL;
    Node *tree_2 = NULL;
    Node *tree_3 = NULL;
    Node *tree_4 = NULL;
    Node *tree_5 = NULL;
    Node *tree_6 = NULL;
    Node *tree_7 = NULL;

    // Малая глубина (2), малое ветвление (1)
    tree_1 = insert(tree_1, 'F');
    tree_1 = insert(tree_1, 'B');

    // Большая глубина (4), малое ветвление (1)
    tree_2 = insert(tree_2, 'F');
    tree_2 = insert(tree_2, 'G');
    tree_2 = insert(tree_2, 'H');
    tree_2 = insert(tree_2, 'I');

    // Малая глубина (3), большое ветвление (2)
    tree_3 = insert(tree_3, 'F');
    tree_3 = insert(tree_3, 'B');
    tree_3 = insert(tree_3, 'H');
    tree_3 = insert(tree_3, 'A');
    tree_3 = insert(tree_3, 'C');

    // Глубина (3), сбалансированное ветвление (максимально 2)
    tree_4 = insert(tree_4, 'F');
    tree_4 = insert(tree_4, 'B');
    tree_4 = insert(tree_4, 'H');
    tree_4 = insert(tree_4, 'A');
    tree_4 = insert(tree_4, 'C');
    tree_4 = insert(tree_4, 'G');
    tree_4 = insert(tree_4, 'I');

    // Глубина варьируется (4), ветвление варьируется (1-2)
    tree_5 = insert(tree_5, 'F');
    tree_5 = insert(tree_5, 'B');
    tree_5 = insert(tree_5, 'H');
    tree_5 = insert(tree_5, 'A');
    tree_5 = insert(tree_5, 'G');
    tree_5 = insert(tree_5, 'I');

    // Глубина (4), ветвление (3)
    tree_6 = insert(tree_6, 'F');
    tree_6 = insert(tree_6, 'B');
    tree_6 = insert(tree_6, 'H');
    tree_6 = insert(tree_6, 'A');
    tree_6 = insert(tree_6, 'C');
    tree_6 = insert(tree_6, 'D');
    tree_6 = insert(tree_6, 'E');

    // Глубина (5), высокое ветвление (2)
    tree_7 = insert(tree_7, 'F');
    tree_7 = insert(tree_7, 'B');
    tree_7 = insert(tree_7, 'H');
    tree_7 = insert(tree_7, 'A');
    tree_7 = insert(tree_7, 'D');
    tree_7 = insert(tree_7, 'G');
    tree_7 = insert(tree_7, 'I');
    tree_7 = insert(tree_7, 'E');
    tree_7 = insert(tree_7, 'C');

    // Замеряем время для каждого дерева
    printf("Дерево 1 (глубина 2, ветвление 1):\n");
    measure_search_time(tree_1, 'D');

    printf("Дерево 2 (глубина 4, ветвление 1):\n");
    measure_search_time(tree_2, 'D');

    printf("Дерево 3 (глубина 3, ветвление 2):\n");
    measure_search_time(tree_3, 'D');

    printf("Дерево 4 (глубина 3, ветвление 2 (сбалансировано)):\n");
    measure_search_time(tree_4, 'D');

    printf("Дерево 5 (глубина 4, ветвление 2):\n");
    measure_search_time(tree_5, 'D');

    printf("Дерево 6 (глубина 4, ветвление 3):\n");
    measure_search_time(tree_6, 'D');

    printf("Дерево 7 (глубина 5, ветвление 2):\n");
    measure_search_time(tree_7, 'D');

    // Освобождаем память, если необходимо
    free_tree(tree_1);
    free_tree(tree_2);
    free_tree(tree_3);
    free_tree(tree_4);
    free_tree(tree_5);
    free_tree(tree_6);
    free_tree(tree_7);
}
