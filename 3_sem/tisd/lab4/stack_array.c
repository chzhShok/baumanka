#include <ctype.h>
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

    if (!isspace(element))
    {
        stack->top++;
        stack->array[stack->top] = element;
    }
    else
    {
        printf("Пустой элемент\n");
    }

    return 0;
}

char pop_arr(stack_array_t *stack, int out)
{
    if (is_empty_arr(stack))
        return '\0';

    char value = stack->array[stack->top];

    if (out)
        printf("Удален элемент: %c, адрес: %p\n", value, (void *) &(stack->array[stack->top]));

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

    stack_array_t stack_reversed;
    init_stack_arr(&stack_reversed);

    for (int p = 0; p <= stack->top; p++)
    {
        if (push_arr(&stack_reversed, (char) p))
        {
            free_stack_arr(&stack_reversed);
            return 0;
        }
    }

    char *p = stack->array;
    while (!is_empty_arr(&stack_reversed))
    {
        if (*p != pop_arr(&stack_reversed, 0))
        {
            free_stack_arr(&stack_reversed);
            return 0;
        }
        p++;
    }

    free_stack_arr(&stack_reversed);
    return 1;
}
