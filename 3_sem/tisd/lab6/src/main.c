#include <stdio.h>
#include <string.h>

#include "research.h"
#include "tree.h"

void menu()
{
    printf("--- МЕНЮ ---\n");
    printf("Выберите команду:\n");
    printf("1: Добавить строку в дерево\n");
    printf("2: Добавить узел\n");
    printf("3: Удалить узел\n");
    printf("4: Вывести в строку\n");
    printf("5: Вывести в виде дерева\n");
    printf("6: Вывести узел\n");
    printf("7: Удалить повторяющиеся буквы\n");
    printf("\n");
    printf("8: Сравнить время удаления повторяющихся букв из дерева и из строки\n");
    printf("9: Сравнить эффективность алгоритма поиска\n");
    printf("\n");
    printf("10: Очистить дерево\n");
    printf("11: Вывести меню\n");
    printf("0: Выход\n");
}

int main()
{
    int command;

    struct Node *root = NULL;
    char input_string[STRING_LEN];
    char input_char;

    menu();

    while (1)
    {
        printf("\nВведите команду: ");
        if (scanf("%d", &command) != 1)
            command = 123;
        getchar();

        switch (command)
        {
            case 1:
                printf("Введите строку: ");
                if (fgets(input_string, STRING_LEN, stdin) == NULL)
                {
                    printf("Неверный ввод строки\n");
                    break;
                }

                if (strlen(input_string) == 0)
                {
                    printf("Пустая строка\n");
                    break;
                }

                for (int i = 0; input_string[i] != '\0'; i++)
                    root = insert(root, input_string[i]);

                break;
            case 2:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Символ не введен\n");
                    break;
                }

                root = insert(root, input_char);

                break;
            case 3:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Символ не введен");
                    break;
                }

                root = del_node(root, input_char);

                break;
            case 4:
                if (!root)
                    printf("Пустое дерево\n");
                else
                    in_order_traversal(root);

                break;
            case 5:
                if (!root)
                    printf("Пустое дерево\n");
                else
                    print_tree(root, NULL, 0);

                break;
            case 6:
                if (!root)
                {
                    printf("Пустое дерево\n");
                    break;
                }
                else
                {
                    printf("Введите символ: ");
                    if (scanf("%c", &input_char) != 1)
                    {
                        printf("Символ не введен\n");
                        break;
                    }
                    struct Node *found = search(root, input_char);
                    print_tree(found, NULL, 0);
                }

                break;
            case 7:
                root = del_rep_nodes(root);
                break;
            case 8:
                cmp_del_rep();
                break;
            case 9:
                cmp_find();
                break;
            case 10:
                free_tree(root);
                root = NULL;
                break;
            case 11:
                menu();
                break;
            case 0:
                free_tree(root);
                return 0;
            default:
                printf("Неверная команда\n");
        }
    }
}
