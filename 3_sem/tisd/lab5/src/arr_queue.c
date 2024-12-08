#include <stdio.h>

#include "arr_queue.h"

int is_empty_arr(ArrayQueue *queue)
{
    return queue->size == 0;
}

int is_full_arr(ArrayQueue *queue)
{
    return queue->size == LIST_CAPACITY;
}

int push_queue_arr(ArrayQueue *queue, Request request)
{
    if (is_full_arr(queue))
        return 0;

    queue->data[queue->tail] = request;
    queue->tail = (queue->tail + 1 + LIST_CAPACITY) % LIST_CAPACITY;
    queue->size++;
    return 1;
}

int pop_queue_arr(ArrayQueue *queue, Request *request)
{
    if (is_empty_arr(queue))
        return 0;

    *request = queue->data[queue->head];
    queue->head = (queue->head + 1 + LIST_CAPACITY) % LIST_CAPACITY;
    queue->size--;
    return 1;
}

int print_queue_arr(ArrayQueue *queue)
{
    if (is_empty_arr(queue))
        return 0;

    printf("Состояние очереди на массиве\n");
    printf("Размер: %d\n", queue->size);

    printf("Элементы: \n");
    for (int i = 0; i < queue->size; i++)
    {
        int index = (queue->head + i) % LIST_CAPACITY;
        printf("%p\n", queue->data + index);
    }

    return 1;
}

int push_many_queue_arr(ArrayQueue *queue, Request request, int n)
{
    for (int i = 0; i < n; i++)
        if (!push_queue_arr(queue, request))
            return 0;

    return 1;
}

int pop_many_queue_arr(ArrayQueue *queue, Request *request, int n)
{
    for (int i = 0; i < n; i++)
        if (!pop_queue_arr(queue, request))
            return 0;

    return 1;
}
