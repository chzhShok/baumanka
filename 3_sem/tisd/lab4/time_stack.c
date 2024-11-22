#include <math.h>
#include <stdio.h>
#include <time.h>

#include "stack_array.h"
#include "stack_list.h"
#include "time_stack.h"

void measure_time()
{
    stack_array_t array_stack;
    init_stack_arr(&array_stack);

    stack_list_t list_stack;
    init_stack_list(&list_stack);

    clock_t start, end;

    int number_of_elements = STACK_CAPACITY * 0.07;
    double sum_times = 0;
    
    // Замер времени для стека на основе массива
    for (int i = 0; i < TIMES_LEN; i++)
    {
        start = clock();
        for (int j = 0; j < number_of_elements; j++)
            push_arr(&array_stack, 'a');
        end = clock();
        double array_push_time = (double) (end - start) / CLOCKS_PER_SEC * COEFF;
        
        sum_times += array_push_time;
    }
    double array_push_time = sum_times / TIMES_LEN;

    sum_times = 0.0;
    for (int i = 0; i < TIMES_LEN; i++)
    {
        start = clock();
        for (int j = 0; j < number_of_elements; j++)
            pop_arr(&array_stack, 0);
        end = clock();
        double array_pop_time = (double) (end - start) / CLOCKS_PER_SEC * COEFF;
        
        sum_times += array_pop_time;
    }
    double array_pop_time = sum_times / TIMES_LEN;

    free_stack_arr(&array_stack);

    // Замер времени для стека на основе списка
    sum_times = 0.0;
    for (int i = 0; i < TIMES_LEN; i++)
    {
        start = clock();
        for (int j = 0; j < number_of_elements; j++)
            push_list(&list_stack, 'a');
        end = clock();
        double list_push_time = (double) (end - start) / CLOCKS_PER_SEC * COEFF;
        
        sum_times += list_push_time;
    }
    double list_push_time = sum_times / TIMES_LEN;

    sum_times = 0.0;
    for (int i = 0; i < TIMES_LEN; i++)
    {
        start = clock();
        for (int j = 0; j < number_of_elements; j++)
            pop_list(&list_stack, 0);
        end = clock();
        double list_pop_time = (double) (end - start) / CLOCKS_PER_SEC * COEFF;

        sum_times += list_pop_time;
    }
    double list_pop_time = sum_times / TIMES_LEN;

    free_stack_list(&list_stack);

    printf("Среднее время добавления в стек-массив: %.10f * 10^(-%d) секунд\n", array_push_time, (int) log10(COEFF));
    printf("Среднее время удаления из стека-массива: %.10f * 10^(-%d) секунд\n", array_pop_time, (int) log10(COEFF));
    printf("\n");
    printf("Среднее время добавления в стек-список: %.10f * 10^(-%d) секунд\n", list_push_time, (int) log10(COEFF));
    printf("Среднее время удаления из стека-списка: %.10f * 10^(-%d) секунд\n", list_pop_time, (int) log10(COEFF));
}
