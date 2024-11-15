#include <stdio.h>

#include "errors.h"
#include "stack_array.h"
#include "stack_list.h"
#include "time_stack.h"

void menu(void)
{
    printf("--- МЕНЮ ---\n");
    printf("0: выйти\n");
    printf("\n");
    printf("Стек как массив\n");
    printf("1: добавить символ в стек\n");
    printf("2: удалить символ из стека\n");
    printf("3: вывести стек с адресами элементов\n");
    printf("4: посмотреть вершину стека\n");
    printf("5: очистить стек\n");
    printf("\n");
    printf("Стек как список\n");
    printf("6: добавить символ в стек\n");
    printf("7: удалить символ из стека\n");
    printf("8: вывести стек с адресами элементов\n");
    printf("9: посмотреть вершину стека\n");
    printf("10: очистить стек\n");
    printf("\n");
    printf("11: вывести меню\n");
    printf("12: определить является ли строка палиндромом\n");
    printf("13: замерить время работы разных стеков\n");
    printf("---");
    printf("\n");
}

int main(void)
{
    int command;

    stack_array_t stack_arr;
    init_stack_arr(&stack_arr);

    stack_list_t stack_list;
    init_stack_list(&stack_list);

    menu();

    do
    {
        printf("\nВведите комманду: ");
        if (scanf("%d", &command) != 1)
        {
            printf("Ошибка: комманда введена неверно\n");
            return COMMAND_ERROR;
        }
        getchar();

        if (command == 1)
        {
            char element;

            printf("Введите символьный элемент: ");
            if (scanf("%c", &element) != 1)
            {
                printf("Ошибка: введен некорректный элемент\n");
                return IO_ERROR;
            }

            if (stack_arr.top == -1)
                init_stack_arr(&stack_arr);

            if (push_arr(&stack_arr, element))
                printf("Стек заполнен\n");
        }
        else if (command == 2)
        {
            char element = pop_arr(&stack_arr, 1);
        }
        else if (command == 3)
        {
            print_arr(&stack_arr);
        }
        else if (command == 4)
        {
            peek_arr(&stack_arr);
        }
        else if (command == 5)
        {
            free_stack_arr(&stack_arr);
        }
        else if (command == 6)
        {
            char element;

            printf("Введите символьный элемент: ");
            if (scanf("%c", &element) != 1)
            {
                printf("Ошибка: введен некорректный элемент\n");
                return IO_ERROR;
            }

            if (push_list(&stack_list, element))
                printf("Не удалось добавить элемент в стек\n");
        }
        else if (command == 7)
        {
            char element = pop_list(&stack_list, 1);
        }
        else if (command == 8)
        {
            print_list(&stack_list);
        }
        else if (command == 9)
        {
            peek_list(&stack_list);
        }
        else if (command == 10)
        {
            free_stack_list(&stack_list);
        }
        else if (command == 11)
        {
            menu();
        }
        else if (command == 12)
        {
            int stack_type;

            printf("Выберите, в каком стеке проверить строку на палиндром (1: массив, 2: список): ");
            if (scanf("%d", &stack_type) != 1)
            {
                printf("Ошибка: команда введена неверно\n");
                return IO_ERROR;
            }
            getchar();

            if (!(stack_type == 1 || stack_type == 2))
            {
                printf("Ошибка: команда введена неверно\n");
                return COMMAND_ERROR;
            }

            if (stack_type == 1)
            {
                if (is_palindrome_arr(&stack_arr))
                    printf("Строка является палиндромом\n");
                else
                    printf("Строка не является палиндромом\n");
            }
            else
            {
                if (is_palindrome_list(stack_list))
                    printf("Строка является палиндромом\n");
                else
                    printf("Строка не является палиндромом\n");
            }
        }
        else if (command == 13)
        {
            measure_time();
        }
        else if (command == 0)
            continue;
    } while (command != 0);

    if (stack_list.top != NULL)
        free_stack_list(&stack_list);

    return OK;
}
