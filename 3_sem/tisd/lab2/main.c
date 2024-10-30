#include <stdio.h>
#include <string.h>

#include "key_table_funcs.h"
#include "original_table_funcs.h"
#include "subscriber_funcs.h"
#include "time_sorts.h"

void menu(void)
{
    printf("\n--- Выберите команду ---\n");
    printf("0 - выход\n");
    printf("1 - открыть файл с таблицей абонентов\n");
    printf("2 - ввод таблицы абонентов\n");
    printf("3 - вывод списка друзей, которых необходимо поздравить\n");
    printf("4 - добавить запись в конец таблицы\n");
    printf("5 - удалить запись по значению указанного поля\n");
    printf("6 - отсортировать таблицу ключей\n");
    printf("7 - отсортировать таблицу абонентов\n");
    printf("8 - вывод таблицы ключей\n");
    printf("9 - вывод таблицы абонентов\n");
    printf("10 - вывод таблицы абонентов, по таблице ключей\n");
    printf("11 - замерить эффективность сортировок\n");
}

static char original_file[FILENAME_MAX];
static char keys_file[] = "keys.csv";

int main(void)
{
    int rc = OK;

    subscriber_t subscribers[NUM_ENTRIES];
    key_t keys[NUM_ENTRIES];
    int num_subscribers;

    int command;
    do
    {
        menu();

        printf("\nВведите комманду: ");
        if (scanf("%d", &command) != 1)
        {
            printf("Ошибка ввода команды\n");
            return IO_ERROR;
        }
        getchar();

        if (command == 1)//Открытие файла, содержащего таблицу абонентов
        {
            printf("Введите название файла: ");
            if (fgets(original_file, FILENAME_MAX, stdin) == NULL)
            {
                printf("Ошибка ввода названия файла.\n");
                return IO_ERROR;
            }
            size_t pos = strcspn(original_file, "\n");
            if (pos == strlen(original_file))
            {
                printf("Ошибка: слишком длинное название файла.\n");
                return BUFFER_OVERFLOW;
            }
            original_file[pos] = '\0';

            rc = load_subscribers_from_file(original_file, subscribers, &num_subscribers);
            if (rc == ERROR_FILE_OPEN)
            {
                printf("Ошибка: не удалось открыть файл %s\n", original_file);
                return rc;
            }
            else if (rc == IO_ERROR)
            {
                printf("Ошибка ввода\n");
                return rc;
            }
            else if (rc == ERROR_TOO_MANY_ENTRIES)
            {
                printf("Ошибка: слишком много записей в файле\n");
                return rc;
            }

            create_key_array(subscribers, keys, num_subscribers);
            if (save_keys_to_csv(keys_file, keys, num_subscribers))
            {
                printf("Ошибка: не удалось открыть файл для записи массива ключей.\n");
                return ERROR_FILE_OPEN;
            }
        }
        else if (command == 2)// Создание таблицы абонентов
        {
            printf("Введите название файла: ");
            if (fgets(original_file, FILENAME_MAX, stdin) == NULL)
            {
                printf("Ошибка ввода названия файла.\n");
                return IO_ERROR;
            }
            size_t pos = strcspn(original_file, "\n");
            if (pos == strlen(original_file))
            {
                printf("Ошибка: слишком длинное название файла.\n");
                return BUFFER_OVERFLOW;
            }
            original_file[pos] = '\0';

            printf("Введите количество абонентов (максимум %d): ", NUM_ENTRIES);
            if (scanf("%d", &num_subscribers) != 1 || num_subscribers > NUM_ENTRIES)
            {
                printf("Ошибка ввода: некорректное количество абонентов.\n");
                return ERROR_TOO_MANY_ENTRIES;
            }
            getchar();

            rc = enter_subscribers_array(subscribers, num_subscribers);
            if (rc == IO_ERROR)
            {
                printf("Ошибка ввода данных.\n");
                return rc;
            }
            else if (rc == BUFFER_OVERFLOW)
            {
                printf("Ошибка: введено слишком длинное значение.\n");
                return rc;
            }

            create_key_array(subscribers, keys, num_subscribers);
            if (save_keys_to_csv(keys_file, keys, num_subscribers))
            {
                printf("Ошибка: не удалось открыть файл для записи массива ключей.\n");
                return ERROR_FILE_OPEN;
            }

            if (save_to_csv(subscribers, num_subscribers, original_file))
            {
                printf("Ошибка: не удалось открыть файл для записи.\n");
                return ERROR_FILE_OPEN;
            }
        }
        else if (command == 3)// Вывод списка друзей, которых необходимо поздравить
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            int current_day, current_month, current_year;
            printf("Введите текущую дату (день, месяц, год): ");
            if (scanf("%d%d%d", &current_day, &current_month, &current_year) != 3)
            {
                printf("Ошибка ввода текущей даты.\n");
                return IO_ERROR;
            }

            print_upcoming_birthdays(subscribers, num_subscribers, current_day, current_month, current_year);
        }
        else if (command == 4)// Добавить запись в конец таблицы
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            rc = add_new_subscriber(subscribers, &num_subscribers, keys, original_file, keys_file);
            if (rc == IO_ERROR)
            {
                printf("Ошибка ввода данных.\n");
                return rc;
            }
            else if (rc == BUFFER_OVERFLOW)
            {
                printf("Ошибка: введено слишком длинное значение.\n");
                return rc;
            }
            else if (rc == ERROR_FILE_OPEN)
            {
                printf("Ошибка: не удалось открыть файл.\n");
                return ERROR_FILE_OPEN;
            }
        }
        else if (command == 5)// Удалить запись по значению указанного поля
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            char surname[MAX_NAME_LEN];
            printf("Введите фамилию для удаления: ");
            if (fgets(surname, MAX_NAME_LEN, stdin) == NULL)
            {
                printf("Ошибка ввода фамилии для удаления.\n");
                return IO_ERROR;
            }
            size_t pos = strcspn(surname, "\n");
            if (pos == strlen(surname))
            {
                printf("Ошибка: введено слишком длинное значение.\n");
                return BUFFER_OVERFLOW;
            }
            surname[pos] = '\0';

            rc = delete_subscriber(subscribers, keys, &num_subscribers, surname, original_file, keys_file);
            if (rc == NOT_FOUND)
            {
                printf("Абонент с фамилией \"%s\" не найден.\n", surname);
            }
            else if (rc == ERROR_FILE_OPEN)
            {
                printf("Ошибка: не удалось открыть файл для записи.\n");
                return ERROR_FILE_OPEN;
            }
        }
        else if (command == 6)// Отсортировать таблицу ключей без сортировки исходной таблицы
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            char sort_method[SORT_METHOD_LEN];
            printf("Выберете метод сортировки (q - быстрая, b - пузырьком): ");
            if (fgets(sort_method, SORT_METHOD_LEN, stdin) == NULL)
            {
                printf("Ошибка ввода метода сортировки.\n");
                return IO_ERROR;
            }
            size_t pos = strcspn(sort_method, "\n");
            if (pos == strlen(sort_method))
            {
                printf("Ошибка: введено слишком длинное значение.\n");
                return BUFFER_OVERFLOW;
            }
            sort_method[pos] = '\0';

            if (strcmp(sort_method, "q") == 0)
            {
                bubble_sort_keys(keys, num_subscribers);
            }
            else if (strcmp(sort_method, "b") == 0)
            {
                quick_sort_keys(keys, 0, num_subscribers - 1);
            }
            else
            {
                printf("Ошибка: метод сортировки введен неверно.\n");
                return WRONG_SORT_METHOD;
            }

            if (save_keys_to_csv(keys_file, keys, num_subscribers))
            {
                printf("Ошибка: не удалось сохранить отсортированные ключи.\n");
                return ERROR_FILE_OPEN;
            }

            int ans;
            printf("Вывести таблицу ключей? (0 - нет): ");
            if (scanf("%d", &ans) != 1)
            {
                printf("Ошибка ввода.\n");
                return IO_ERROR;
            }
            getchar();
            if (ans)
                print_keys(keys, num_subscribers);

            printf("Вывести отсортированную таблицу абонентов по таблице ключей? (0 - нет): ");
            if (scanf("%d", &ans) != 1)
            {
                printf("Ошибка ввода.\n");
                return IO_ERROR;
            }
            getchar();
            if (ans)
                print_subscribers_by_keys(subscribers, keys, num_subscribers);
        }
        else if (command == 7)// Отсортировать таблицу абонетов
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            char sort_method[SORT_METHOD_LEN];
            printf("Выберете метод сортировки (q - быстрая, b - пузырьком): ");
            if (fgets(sort_method, SORT_METHOD_LEN, stdin) == NULL)
            {
                printf("Ошибка ввода метода сортировки.\n");
                return IO_ERROR;
            }
            size_t pos = strcspn(sort_method, "\n");
            if (pos == strlen(sort_method))
            {
                printf("Ошибка: введено слишком длинное значение.\n");
                return BUFFER_OVERFLOW;
            }
            sort_method[pos] = '\0';

            if (strcmp(sort_method, "q") == 0)
            {
                bubble_sort_subscribers(subscribers, num_subscribers);
            }
            else if (strcmp(sort_method, "b") == 0)
            {
                quick_sort_subscribers(subscribers, 0, num_subscribers - 1);
            }
            else
            {
                printf("Ошибка: метод сортировки введен неверно.\n");
                return WRONG_SORT_METHOD;
            }


            if (save_to_csv(subscribers, num_subscribers, original_file))
                return ERROR_FILE_OPEN;

            create_key_array(subscribers, keys, num_subscribers);
            if (save_keys_to_csv(keys_file, keys, num_subscribers))
            {
                printf("Ошибка: не удалось открыть файл для записи массива ключей.\n");
                return ERROR_FILE_OPEN;
            }

            int ans;
            printf("Вывести таблицу абонентов? (0 - нет): ");
            if (scanf("%d", &ans) != 1)
            {
                printf("Ошибка ввода.\n");
                return IO_ERROR;
            }
            getchar();
            if (ans)
                print_subscribers(subscribers, num_subscribers);
        }
        else if (command == 8)
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            print_keys(keys, num_subscribers);
        }
        else if (command == 9)
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            print_subscribers(subscribers, num_subscribers);
        }
        else if (command == 10)
        {
            if (num_subscribers == 0)
            {
                printf("Таблица еще не была введена\n");
                continue;
            }

            print_subscribers_by_keys(subscribers, keys, num_subscribers);
        }
        else if (command == 11)// Вывод результатов сравнения эффективности работы программы при обработке данных в исходной таблице и в таблице ключей
        {
            int n;
            printf("Введите длину массива, для которого будет происходить замер времени: ");
            if (scanf("%d", &n) != 1)
            {
                printf("Ошибка ввода длины массива\n");
                return IO_ERROR;
            }
            getchar();

            subscriber_t subscribers_time[n];
            key_t keys_time[n];

            generate_dataset(subscribers_time, n);
            create_key_array(subscribers_time, keys_time, n);

//            char time_sort[SORT_METHOD_LEN];
//            printf("Выберите, какую сортировку замерить (q - быстрая, b - пузырьком): ");
//            if (fgets(time_sort, SORT_METHOD_LEN, stdin) == NULL)
//            {
//                printf("Ошибка ввода метода сортировки.\n");
//                return IO_ERROR;
//            }
//            size_t pos = strcspn(time_sort, "\n");
//            if (pos == strlen(time_sort))
//            {
//                printf("Ошибка: введено слишком длинное значение.\n");
//                return BUFFER_OVERFLOW;
//            }
//            time_sort[pos] = '\0';


            measure_sorting_times_quick(subscribers_time, keys_time, n);
            measure_sorting_times_bubble(subscribers_time, keys_time, n);
        }
        else if (command == 0)
        {
            continue;
        }
        else
        {
            printf("Ошибка: введена неверная команда %d\n", command);
            return COMMAND_ERROR;
        }

        fseek(stdin, 0, SEEK_END);
    } while (command != 0);


    return OK;
}
