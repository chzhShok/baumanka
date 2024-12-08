#ifndef ARR_QUEUE_H
#define ARR_QUEUE_H

#include "request.h"

#define LIST_CAPACITY 10000

typedef struct
{
    Request data[LIST_CAPACITY];
    int head;
    int tail;
    int size;
} ArrayQueue;

int push_queue_arr(ArrayQueue *queue, Request request);
int push_many_queue_arr(ArrayQueue *queue, Request request, int n);
int pop_queue_arr(ArrayQueue *queue, Request *request);
int pop_many_queue_arr(ArrayQueue *queue, Request *request, int n);
int print_queue_arr(ArrayQueue *queue);

#endif//ARR_QUEUE_H
