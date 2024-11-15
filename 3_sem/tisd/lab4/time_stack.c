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

    // Замер времени для стека на основе массива
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
        push_arr(&array_stack, 'a');
    end = clock();
    double array_push_time = (double) (end - start) / CLOCKS_PER_SEC / NUM_ELEMENTS * COEFF;

    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
        pop_arr(&array_stack, 0);
    end = clock();
    double array_pop_time = (double) (end - start) / CLOCKS_PER_SEC / NUM_ELEMENTS * COEFF;

    free_stack_arr(&array_stack);

    // Замер времени для стека на основе списка
    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
        push_list(&list_stack, 'a');
    end = clock();
    double list_push_time = (double) (end - start) / CLOCKS_PER_SEC / NUM_ELEMENTS * COEFF;

    start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i++)
        pop_list(&list_stack, 0);
    end = clock();
    double list_pop_time = (double) (end - start) / CLOCKS_PER_SEC / NUM_ELEMENTS * COEFF;

    free_stack_list(&list_stack);

    printf("Среднее время добавления в стек-массив: %.10f * 10^(-%d) секунд\n", array_push_time, (int) log10(COEFF));
    printf("Среднее время удаления из стека-массива: %.10f * 10^(-%d) секунд\n", array_pop_time, (int) log10(COEFF));
    printf("\n");
    printf("Среднее время добавления в стек-список: %.10f * 10^(-%d) секунд\n", list_push_time, (int) log10(COEFF));
    printf("Среднее время удаления из стека-списка: %.10f * 10^(-%d) секунд\n", list_pop_time, (int) log10(COEFF));
}
