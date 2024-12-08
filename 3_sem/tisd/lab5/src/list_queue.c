#include <stdio.h>
#include <stdlib.h>

#include "list_queue.h"

void init_queue_list(ListQueue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

int is_empty_list(ListQueue *queue)
{
    return queue->head == NULL;
}

int push_queue_list(ListQueue *queue, Request request)
{
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node)
        return 0;

    node->data = request;
    node->next = NULL;

    if (is_empty_list(queue))
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->size++;

    return 1;
}

int pop_queue_list(ListQueue *queue, Request *request)
{
    if (is_empty_list(queue))
        return 0;

    Node *tmp = queue->head;
    *request = tmp->data;

    queue->head = queue->head->next;
    if (queue->head == NULL)
        queue->tail = NULL;

    free(tmp);

    queue->size--;

    return 1;
}

int print_queue_list(ListQueue *queue)
{
    if (is_empty_list(queue))
        return 0;

    printf("Состояние очереди на списке\n");
    printf("Размер: %d\n", queue->size);

    printf("Элементы: \n");
    Node *current = queue->head;
    while (current)
    {
        printf("%p\n", current);
        current = current->next;
    }

    return 1;
}

int push_many_queue_list(ListQueue *queue, Request request, int n)
{
    for (int i = 0; i < n; i++)
        if (!push_queue_list(queue, request))
            return 0;

    return 1;
}

int pop_many_queue_list(ListQueue *queue, Request *request, int n)
{
    for (int i = 0; i < n; i++)
        if (!pop_queue_list(queue, request))
            return 0;

    return 1;
}

void free_queue_list(ListQueue *queue)
{
    Request request;

    while (pop_queue_list(queue, &request))
    {
    }
}
