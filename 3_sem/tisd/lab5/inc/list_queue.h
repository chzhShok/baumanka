#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "request.h"

typedef struct Node
{
    Request data;
    struct Node *next;
} Node;

typedef struct
{
    Node *tail;
    Node *head;
    int size;
} ListQueue;

void init_queue_list(ListQueue *queue);
int push_queue_list(ListQueue *queue, Request request);
int push_many_queue_list(ListQueue *queue, Request request, int n);
int pop_queue_list(ListQueue *queue, Request *request);
int pop_many_queue_list(ListQueue *queue, Request *request, int n);
int print_queue_list(ListQueue *queue);
void free_queue_list(ListQueue *queue);

#endif//LIST_QUEUE_H
