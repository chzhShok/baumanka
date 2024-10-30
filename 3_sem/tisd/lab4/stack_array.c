#include <stdio.h>

#include "stack_array.h"

void init_stack_arr(stack_array_t *stack)
{
    stack->top = -1;
    stack->capacity = STACK_CAPACITY;
}

void free_stack_arr(stack_array_t *stack)
{
    stack->top = -1;
}

int is_full_arr(stack_array_t *stack)
{
    return stack->top == stack->capacity - 1;
}

int is_empty_arr(stack_array_t *stack)
{
    return stack->top == -1;
}

int push_arr(stack_array_t *stack, char element)
{
    if (is_full_arr(stack))
        return 1;

    stack->top++;
    stack->array[stack->top] = element;
    return 0;
}

char pop_arr(stack_array_t *stack)
{
    if (is_empty_arr(stack))
        return '\0';

    char value = stack->array[stack->top];
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

    for (int i = stack->top; i >= 0; i--)
        printf("address: %p, element: %c\n", (void *) &stack->array[i], stack->array[i]);

    printf("\n");
}

void peek_arr(stack_array_t *stack)
{
    if (is_empty_arr(stack))
    {
        printf("Стек пустой\n");
        return;
    }

    printf("address: %p, element: %c\n", (void *) &stack->array[stack->top], stack->array[stack->top]);
}

int is_palindrome_arr(stack_array_t *stack)
{
    if (is_empty_arr(stack))
        return 1;

    int i1 = stack->top;
    int i2 = 0;

    while (i2 < i1)
    {
        if (stack->array[i1] != stack->array[i2])
            return 0;

        i1--;
        i2++;
    }

    return 1;
}
