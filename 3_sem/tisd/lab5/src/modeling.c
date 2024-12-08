#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "arr_queue.h"
#include "list_queue.h"
#include "modeling.h"
#include "request.h"

double generate_random(double min, double max)
{
    return (double) rand() / RAND_MAX * (max - min) + min;
}

void modeling(int t1_start, int t1_end, int t2_start, int t2_end, int cycles)
{
    ArrayQueue array_queue = {.head = 0, .tail = 0, .size = 0};
//    ListQueue list_queue;
//    init_queue_list(&list_queue);

    srand(time(NULL));

    double current_time = 0;
    double next_arrival = generate_random(t1_start, t1_end);
    double next_departure = -1;

    int total_arrivals = 0;
    int total_departures = 0;
    double idle_time = 0;
    double average_length_sum = 0;
    int oa_operations = 0;

    Request current_request;
    int is_processing = 0;
    int last_reported;

    while (total_departures < TOTAL_PROCESSED)
    {
        // Поступление новой заявки
        if (current_time >= next_arrival)
        {
            Request new_request;
            new_request.cycles_left = cycles;
            new_request.arrival_time = current_time;
            new_request.processing_time = generate_random(t2_start, t2_end);

            if (push_queue_arr(&array_queue, new_request) == 1)
//            if (push_queue_arr(&array_queue, new_request) == 1 &&
//                push_queue_list(&list_queue, new_request) == 1)
                total_arrivals++;
            else
                printf("Ошибка: очередь переполнена!\n");

            next_arrival = current_time + generate_random(t1_start, t1_end);
        }

        // Обслуживание заявки
        if (is_processing && current_time >= next_departure)
        {
            current_request.cycles_left--;

            if (current_request.cycles_left > 0)
            {
                if (push_queue_arr(&array_queue, current_request) != 1)
//                if (push_queue_arr(&array_queue, current_request) != 1 ||
//                    push_queue_list(&list_queue, current_request) != 1)
                    printf("Ошибка: очередь переполнена при возврате заявки!\n");
            }
            else
            {
                total_departures++;
            }
            is_processing = 0;
        }

        // Если аппарат не занят, начинаем обработку следующей заявки
//        if (!is_processing && list_queue.size > 0)
        if (!is_processing && array_queue.size > 0)
        {
            if (pop_queue_arr(&array_queue, &current_request) == 1)
//            if (pop_queue_arr(&array_queue, &current_request) == 1 &&
//                pop_queue_list(&list_queue, &current_request) == 1)
            {
                next_departure = current_time + current_request.processing_time;
                is_processing = 1;
                oa_operations++;
            }
        }

        // Если очередь пуста, фиксируем простой
//        if (!is_processing && list_queue.size == 0)
        if (!is_processing && array_queue.size == 0)
            idle_time += TIME_STEP;

        // Подсчёт средней длины очереди
//        average_length_sum += list_queue.size;
        average_length_sum += array_queue.size;

        // Обновление времени
        current_time += TIME_STEP;

        // Вывод информации после каждых 100 обслуженных заявок
        if (total_departures / 100 > last_reported && total_departures > 0 && current_time - next_departure < TIME_STEP)
        {
            last_reported = total_departures / 100;

            printf("\n");
            printf("После обслуживания %d заявок:\n", total_departures);
            printf("Текущая длина очереди (массив): %d\n", array_queue.size);
//            printf("Текущая длина очереди (список): %d\n", list_queue.size);
            printf("Средняя длина очереди: %.2f\n", average_length_sum / (current_time * INVERSE_TIME_STEP));
            printf("\n");
        }
    }

//    free_queue_list(&list_queue);

    // Расчеты для итоговой информации
    double expected_modeling_time = 1000.0 * (t1_start + t1_end) / 2.0;

    // Итоговая информация
    printf("\nРезультаты моделирования:\n");
    printf("Общее время моделирования: %.2f е.в.\n", current_time);
    printf("Погрешность: %.2f %%\n", (double) fabs(current_time - expected_modeling_time) / expected_modeling_time * 100.0);
    printf("Время простоя аппарата: %.2f е.в.\n", idle_time);
    printf("Всего вошло заявок: %d\n", total_arrivals);
    printf("Всего вышло заявок: %d\n", total_departures);
    printf("Средняя длина очереди: %.2f\n", average_length_sum / (current_time * INVERSE_TIME_STEP));
    printf("Количество срабатываний обслуживающего аппарата: %d\n", oa_operations);
}
