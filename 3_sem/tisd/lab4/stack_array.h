#ifndef LAB4_STACK_ARRAY_H
#define LAB4_STACK_ARRAY_H

#define STACK_CAPACITY 1000

typedef struct {
  char array[STACK_CAPACITY];
  int top;
  int capacity;
} stack_array_t;

void init_stack_arr(stack_array_t *stack);
int push_arr(stack_array_t *stack, char element);
char pop_arr(stack_array_t *stack, int out);
void print_arr(stack_array_t *stack);
void peek_arr(stack_array_t *stack);
void free_stack_arr(stack_array_t *stack);

int is_palindrome_arr(stack_array_t *stack);

#endif