#include <stdio.h>
#include <string.h>

#include "avl_tree.h"
#include "bst_tree.h"
#include "hash_table.h"
#include "efficiency.h"
#include "ui.h"

#define MAX_STR_LEN 1000

int main(void)
{
    int command;

    BSTNode *BSTRoot = NULL;
    AVLNode *AVLRoot = NULL;
    HashTable *HashTable = create_hash_table(16);

    char input_string[MAX_STR_LEN];
    char input_char;
    int cmp_count;

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
                    BSTRoot = insert_bst(BSTRoot, input_string[i]);

                break;
            case 2:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Ошибка ввода символа\n");
                    break;
                }

                BSTRoot = insert_bst(BSTRoot, input_char);
                printf("Символ ‘%c’ добавлен\n", input_char);

                break;
            case 3:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Ошибка ввода символа\n");
                    break;
                }

                BSTRoot = delete_node_bst(BSTRoot, input_char);

                break;
            case 4:
                if (!BSTRoot)
                    printf("Пустое дерево\n");
                else
                    save_to_png_from_graphviz_bst(BSTRoot, 1);

                break;
            case 5:
                if (!BSTRoot)
                {
                    printf("Пустое дерево\n");
                }
                else
                {
                    printf("Введите символ: ");
                    if (scanf("%c", &input_char) != 1)
                    {
                        printf("Символ не введен\n");
                        break;
                    }
                    BSTNode *found = search_bst(BSTRoot, input_char, &cmp_count);
                    save_to_png_from_graphviz_bst(found, 2);
                }

                break;
            case 6:
                BSTRoot = delete_duplicates(BSTRoot);
                AVLRoot = balance_tree(BSTRoot);
                break;
            case 7:
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
                    AVLRoot = insert_avl(AVLRoot, input_string[i]);

                break;
            case 8:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Ошибка ввода символа\n");
                    break;
                }

                AVLRoot = insert_avl(AVLRoot, input_char);
                printf("Символ ‘%c’ добавлен\n", input_char);

                break;
            case 9:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Ошибка ввода символа\n");
                    break;
                }

                AVLRoot = delete_node_avl(AVLRoot, input_char);

                break;
            case 10:
                if (!AVLRoot)
                    printf("Пустое дерево\n");
                else
                    save_to_png_from_graphviz_avl(AVLRoot, 1);

                break;
            case 11:
                if (!AVLRoot)
                {
                    printf("Пустое дерево\n");
                }
                else
                {
                    printf("Введите символ: ");
                    if (scanf("%c", &input_char) != 1)
                    {
                        printf("Символ не введен\n");
                        break;
                    }
                    AVLNode *found = search_avl(AVLRoot, input_char, &cmp_count);
                    save_to_png_from_graphviz_avl(found, 2);
                }

                break;
            case 12:
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
                    insert_hash_table(HashTable, input_string[i]);

                break;
            case 13:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Ошибка ввода символа\n");
                    break;
                }

                if (search_hash_table(HashTable, input_char, &cmp_count))
                {
                    printf("\nСимвол '%c' уже есть в хеш-таблице\n", input_char);
                    break;
                }

                if (insert_hash_table(HashTable, input_char) != 0)
                    printf("Ошибка: не удалось добавить символ %c из-за нехватки памяти\n", input_char);
                else
                    printf("\nСимвол '%c' добавлен\n", input_char);

                break;
            case 14:
                printf("Введите символ: ");
                if (scanf("%c", &input_char) != 1)
                {
                    printf("Ошибка ввода символа\n");
                    break;
                }

                delete_in_hash_table(HashTable, input_char);

                break;
            case 15:
                if (HashTable->count == 0)
                    printf("Хэш-таблица пуста\n");
                else
                    print_hash_table(HashTable);

                break;
            case 16:
                if (HashTable->count == 0)
                {
                    printf("Хэш-таблица пуста\n");
                }
                else
                {
                    printf("Введите символ: ");
                    if (scanf("%c", &input_char) != 1)
                    {
                        printf("Символ не введен\n");
                        break;
                    }

                    if (search_hash_table(HashTable, input_char, &cmp_count))
                        printf("\nСимвол %c найден в хеш-таблице\n", input_char);
                    else
                        printf("\nСимвол %c не найден в хеш-таблице\n", input_char);
                }

                break;
            case 17:
                measure_average_search_time();
                break;
            case 18:
                free_tree_bst(BSTRoot);
                break;
            case 19:
                free_tree_avl(AVLRoot);
                break;
            case 20:
                free_hash_table(&HashTable);
                break;
            case 21:
                menu();
                break;
            case 0:
                free_tree_bst(BSTRoot);
                free_tree_avl(AVLRoot);
                free_hash_table(&HashTable);
                return 0;
            case 123:
                printf("Неверная команда\n");
        }
    }
}
