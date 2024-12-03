#include <stdio.h>
#include <string.h>

#include "efficiency.h"
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
    char input_string[MAX_STR_LEN];
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
                if (fgets(input_string, MAX_STR_LEN, stdin) == NULL)
                {
                    printf("Неверный ввод строки\n");
                    break;
                }
                input_string[strcspn(input_string, "\n")] = '\0';

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
                    printf("Ошибка ввода символа\n");
                    break;
                }

                root = insert(root, input_char);

                break;
            case 3:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Ошибка ввода символа\n");
                    break;
                }

                root = delete_node(root, input_char);

                break;
            case 4:
                if (!root)
                    printf("Пустое дерево\n");
                else
                    post_order(root);

                break;
            case 5:
                if (!root)
                    printf("Пустое дерево\n");
                else
                    save_to_png_from_graphviz(root, 1);

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
                    save_to_png_from_graphviz(found, 2);
                }

                break;
            case 7:
                root = delete_duplicates(root);
                break;
            case 8:
                compare_delete_duplicates();
                break;
            case 9:
                compare_search();
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
            case 123:
                printf("Неверная команда\n");
        }
    }
}
