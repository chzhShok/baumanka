#ifndef LAB4_STACK_LIST_H
#define LAB4_STACK_LIST_H

typedef struct
{
    char data;
    struct node_t *next;
} node_t;

typedef struct
{
    node_t *top;
} stack_list_t;

void init_stack_list(stack_list_t *stack);
int push_list(stack_list_t *stack, char element);
char pop_list(stack_list_t *stack, int out);
void print_list(stack_list_t *stack);
void peek_list(stack_list_t *stack);
void free_stack_list(stack_list_t *stack);

int is_palindrome_list(stack_list_t stack);

#endif//LAB4_STACK_LIST_H
