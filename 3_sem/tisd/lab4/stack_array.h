#ifndef LAB4_STACK_ARRAY_H
#define LAB4_STACK_ARRAY_H

typedef struct
{
    char *top;
    char *array;
    int capacity;
} stack_array_t;

int init_stack_arr(stack_array_t *stack, int capacity);
int push_arr(stack_array_t *stack, char element);
char pop_arr(stack_array_t *stack);
void print_arr(stack_array_t *stack);
void peek_arr(stack_array_t *stack);
void free_stack_arr(stack_array_t *stack);

int is_palindrome_arr(stack_array_t stack);

#endif//LAB4_STACK_ARRAY_H