#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack_list.h"

void init_stack_list(stack_list_t *stack)
{
    stack->top = NULL;
}

int is_empty(stack_list_t *stack)
{
    return stack->top == NULL;
}

int push_list(stack_list_t *stack, char element)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return 1;

    if (!isspace(element))
    {
        node->data = element;
        node->next = (struct node_t *) stack->top;
        stack->top = node;
    }
    else
    {
        printf("Пустой элемент\n");
    }

    return 0;
}

char pop_list(stack_list_t *stack, int out)
{
    if (is_empty(stack))
        return '\0';

    node_t *temp = stack->top;

    char value = stack->top->data;
    if (out)
        printf("Удален элемент: %c, адрес: %p\n", value, (void *) &(stack->top->data));

    stack->top = (node_t *) stack->top->next;
    free(temp);

    return value;
}

void print_list(stack_list_t *stack)
{
    if (is_empty(stack))
        printf("Стек пустой\n");

    node_t *tmp = stack->top;
    while (tmp != NULL)
    {
        printf("address: %p, value: %c\n", (void *) tmp, tmp->data);
        tmp = (node_t *) tmp->next;
    }
}

void peek_list(stack_list_t *stack)
{
    if (is_empty(stack))
        printf("Стек пустой\n");

    printf("address: %p, value: %c\n", (void *) stack->top, stack->top->data);
}

void free_stack_list(stack_list_t *stack)
{
    while (!is_empty(stack))
        pop_list(stack, 0);
}

int is_palindrome_list(stack_list_t stack)
{
    stack_list_t stack_reversed;
    init_stack_list(&stack_reversed);

    node_t *tmp = stack.top;
    while (tmp != NULL)
    {
        push_list(&stack_reversed, tmp->data);
        tmp = (node_t *) tmp->next;
    }

    tmp = stack.top;
    while (tmp != NULL)
    {
        if (tmp->data != pop_list(&stack_reversed, 0))
        {
            free_stack_list(&stack_reversed);
            return 0;
        }

        tmp = (node_t *) tmp->next;
    }

    free_stack_list(&stack_reversed);

    return 1;
}
