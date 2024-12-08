#include <stdio.h>

#include "arr_queue.h"
#include "efficiency.h"
#include "list_queue.h"
#include "modeling.h"
#include "request.h"

void menu(void)
{
    printf("\n--- МЕНЮ ---\n");
    printf("1: Добавить элементы в очередь на массиве\n");
    printf("2: Удалить элементы из очереди на массиве\n");
    printf("3: Вывести адреса элементов очереди на массиве\n");
    printf("4: Добавить элементы в очередь на списке\n");
    printf("5: Удалить элементы из очереди на списке\n");
    printf("6: Вывести адреса элементов очереди на списке\n");
    printf("7: Запустить моделирование\n");
    printf("8: Вывести меню\n");
    printf("9: Замер времени\n");
    printf("0: Выход\n");
}

int main(void)
{
    ArrayQueue queue_arr = {0};
    ListQueue queue_lst;
    init_queue_list(&queue_lst);

    int command;

    menu();

    while (1)
    {
        fseek(stdin, 0, SEEK_END);

        printf("\nВведите команду: ");
        if (scanf("%d", &command) != 1)
            command = 123;
        getchar();

        switch (command)
        {
            case 1:
            {
                int n;
                Request request = {0};
                printf("Введите количество элементов, которое надо добавить: ");
                if (scanf("%d", &n) != 1)
                {
                    printf("Неверно введено количество элементов для добавления\n");
                    break;
                }

                if (push_many_queue_arr(&queue_arr, request, n))
                    printf("Добавлено %d заявок\n", n);
                else
                    printf("Стек заполнен\n");

                break;
            }
            case 2:
            {
                int n;
                Request processed;
                printf("Введите количество элементов, которое надо удалить: ");
                if (scanf("%d", &n) != 1)
                {
                    printf("Неверно введено количество элементов для удаления\n");
                    break;
                }

                if (pop_many_queue_arr(&queue_arr, &processed, n))
                    printf("Удалено %d заявок\n", n);
                else
                    printf("Стек пуст\n");

                break;
            }
            case 3:
            {
                print_queue_arr(&queue_arr);
                break;
            }
            case 4:
            {
                int n;
                Request request = {0};
                printf("Введите количество элементов, которое надо добавить: ");
                if (scanf("%d", &n) != 1)
                {
                    printf("Неверно введено количество элементов для добавления\n");
                    break;
                }

                if (push_many_queue_list(&queue_lst, request, n))
                    printf("Добавлено %d заявок\n", n);
                else
                    printf("Стек заполнен\n");

                break;
            }
            case 5:
            {
                int n;
                Request processed;
                printf("Введите количество элементов, которое надо удалить: ");
                if (scanf("%d", &n) != 1)
                {
                    printf("Неверно введено количество элементов для удаления\n");
                    break;
                }

                if (pop_many_queue_list(&queue_lst, &processed, n))
                    printf("Удалено %d заявок\n", n);
                else
                    printf("Стек пуст\n");

                break;
            }
            case 6:
            {
                print_queue_list(&queue_lst);
                break;
            }
            case 7:
            {
                int t1_start = 0, t1_end = 6;
                int t2_start = 0, t2_end = 1;
                int cycles = 5;

                int ans;

                printf("Хотите ввести свой интервал времени поступления заявок? (1-да, 0-нет): ");
                if (scanf("%d", &ans) != 1 || (ans != 1 && ans != 0))
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                getchar();
                if (ans == 1)
                {
                    printf("Введите границы интервала: ");
                    if (scanf("%d%d", &t1_start, &t1_end) != 2)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }
                    if (t1_start < 0 || t1_end < 0 || t1_start >= t1_end)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }
                    getchar();
                }

                printf("Хотите ввести свой интервал времени обработки заявок? (1-да, 0-нет): ");
                if (scanf("%d", &ans) != 1 || (ans != 1 && ans != 0))
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                getchar();
                if (ans == 1)
                {
                    printf("Введите границы интервала: ");
                    if (scanf("%d%d", &t2_start, &t2_end) != 2)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }
                    if (t2_start < 0 || t2_end < 0 || t2_start >= t2_end)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }
                    getchar();
                }

                printf("Хотите ввести свое количество циклов обслуживания? (1-да, 0-нет): ");
                if (scanf("%d", &ans) != 1 || (ans != 1 && ans != 0))
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                getchar();
                if (ans == 1)
                {
                    printf("Введите количество циклов: ");
                    if (scanf("%d", &cycles) != 1)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }
                    if (cycles <= 0)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }
                    getchar();
                }

                modeling(t1_start, t1_end, t2_start, t2_end, cycles);
                break;
            }
            case 8:
            {
                menu();
                break;
            }
            case 9:
            {
                efficiency();
                break;
            }
            case 123:
            {
                printf("Неверный ввод команды\n");
                break;
            }
            case 0:
            {
                free_queue_list(&queue_lst);
                return 0;
            }
        }
    }
}
