#include <stdio.h>
#include <stdlib.h>

#include "stack_array.h"

int init_stack_arr(stack_array_t *stack, int capacity)
{
    stack->array = malloc(capacity * sizeof(char));
    if (!stack->array)
        return 1;

    stack->top = stack->array - 1;
    stack->capacity = capacity;
    return 0;
}

void free_stack_arr(stack_array_t *stack)
{
    stack->top = NULL;
    free(stack->array);
}

int is_full_arr(stack_array_t *stack)
{
    return stack->top >= (stack->array + stack->capacity - 1);
}

int is_empty_arr(stack_array_t *stack)
{
    return stack->top < stack->array;
}

int push_arr(stack_array_t *stack, char element)
{
    if (is_full_arr(stack))
        return 1;

    stack->top++;
    *stack->top = element;
    return 0;
}

char pop_arr(stack_array_t *stack)
{
    if (is_empty_arr(stack))
        return '\0';

    char value = *stack->top;
    stack->top--;

    return value;
}

void print_arr(stack_array_t *stack)
{
    if (is_empty_arr(stack))
    {
        printf("Стек пустой\n");
        return;
    }

    for (char *p = stack->top; p >= stack->array; p--)
        printf("address: %p, element: %c\n", (void *) p, *p);

    printf("\n");
}

void peek_arr(stack_array_t *stack)
{
    if (is_empty_arr(stack))
    {
        printf("Стек пустой\n");
        return;
    }

    printf("address: %p, element: %c\n", (void *) stack->top, *stack->top);
}

int is_palindrome_arr(stack_array_t stack)
{
    stack_array_t stack_copy;

    stack_copy.array = stack.array;
    stack_copy.top = stack.top;
    stack_copy.capacity = stack.capacity;

    char *p1 = stack.array, *p2 = stack_copy.top;
    while (p1 != stack.top && p2 != stack_copy.array)
    {
        if (*p1 != *p2)
            return 0;

        p1++;
        p2--;
    }

    return 1;
}
