#include <stdio.h>
#include <time.h>

#include "arr_queue.h"
#include "efficiency.h"
#include "list_queue.h"

double calc_mean(const long long data[], int length)
{
    long long sum = 0;
    for (size_t i = 0; i < length; i++)
        sum += data[i];
    return (double) sum / (double) length;
}

double run_push_array_queue(int n)
{
    double avg;
    long long times_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    Request request = {0};

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        ArrayQueue array_queue = {.head = 0, .tail = 0, .size = 0};

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int j = 0; j < n; j++)
            push_queue_arr(&array_queue, request);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        times_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    }

    avg = calc_mean(times_arr, MAX_NUM_TESTS);
    return avg;
}

double run_push_list_queue(int n)
{
    double avg;
    long long times_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    Request request = {0};

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        ListQueue list_queue;
        init_queue_list(&list_queue);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int j = 0; j < n; j++)
            push_queue_list(&list_queue, request);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        times_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        free_queue_list(&list_queue);
    }

    avg = calc_mean(times_arr, MAX_NUM_TESTS);
    return avg;
}

double run_pop_array_queue(int n)
{
    double avg;
    long long times_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    Request request = {0};

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        ArrayQueue array_queue = {.head = 0, .tail = 0, .size = 0};

        for (int j = 0; j < n; j++)
            push_queue_arr(&array_queue, request);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int j = 0; j < n; j++)
            pop_queue_arr(&array_queue, &request);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        times_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    }

    avg = calc_mean(times_arr, MAX_NUM_TESTS);
    return avg;
}

double run_pop_list_queue(int n)
{
    double avg;
    long long times_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    Request request = {0};

    for (int i = 0; i < MAX_NUM_TESTS; i++)
    {
        ListQueue list_queue;
        init_queue_list(&list_queue);

        for (int j = 0; j < n; j++)
            push_queue_list(&list_queue, request);

        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (int j = 0; j < n; j++)
            pop_queue_list(&list_queue, &request);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        times_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        free_queue_list(&list_queue);
    }

    avg = calc_mean(times_arr, MAX_NUM_TESTS);
    return avg;
}

int array_size(int n)
{
    ArrayQueue array_queue = {.head = 0, .tail = 0, .size = 0};
    Request request = {0};

    for (int i = 0; i < n; i++)
        push_queue_arr(&array_queue, request);

    return sizeof(array_queue);
}

int list_size(int n)
{
    ListQueue list_queue;
    init_queue_list(&list_queue);
    Request request = {0};

    push_queue_list(&list_queue, request);

    int size = sizeof(list_queue);

    free_queue_list(&list_queue);

    return size * n;
}

void efficiency(void)
{
    for (int i = 0; i < 99; ++i)
        printf("-");

    for (int size = 10; size < MAX_SIZE; size += 100)
    {
        printf("\n" PURPLE);
        double avg_push_arr, avg_push_lst;
        double avg_pop_arr, avg_pop_lst;
        int arr_size, lst_size;

        printf("Количество элементов: %d\n", size);
        printf("Количество итераций: %d\n\n", MAX_NUM_TESTS);

        avg_push_arr = run_push_array_queue(size);
        avg_push_lst = run_push_list_queue(size);
        avg_pop_arr = run_pop_array_queue(size);
        avg_pop_lst = run_pop_list_queue(size);

        arr_size = array_size(size);
        lst_size = list_size(size);

        printf("Добавление в очередь на массиве: %.2f\n", avg_push_arr);
        printf("Удаление из очереди на массиве: %.2f\n", avg_pop_arr);
        printf("Добавление в очередь на списке: %.2f\n", avg_push_lst);
        printf("Удаление из очереди на списке: %.2f\n", avg_pop_lst);
        printf("\n");
        printf("Занимаемая память очереди на массиве: %d\n", arr_size);
        printf("Занимаемая память очереди на списке: %d\n", lst_size);
        printf("\n");
        printf("Производительность: реализация добавления с помощью списка дольше на %.2lf %%\n", (avg_push_lst / avg_push_arr - 1) * 100);
        printf("Производительность: реализация удаления с помощью списка дольше на %.2lf %%\n", (avg_pop_lst / avg_pop_arr - 1) * 100);
        printf("Память: реализация с помощью списка больше на %.2lf %%\n", ((double) lst_size / arr_size - 1) * 100);

        for (size_t i = 0; i < 99; ++i)
            printf("-");
        printf("\n" RESET);
    }
}
