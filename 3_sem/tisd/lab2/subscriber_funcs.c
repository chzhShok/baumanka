#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "subscriber_funcs.h"

int validate_birth_date(int day, int month, int year)
{
    time_t t = time(NULL);
    struct tm current_time = *localtime(&t);
    int current_year = current_time.tm_year + 1900;

    if (year > current_year)
        return 0;

    if (month < 1 || month > 12)
        return 0;

    if (day < 1 || day > 31)
        return 0;

    int is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 1;
        case 4:
        case 6:
        case 9:
        case 11:
            return day <= 30;
        case 2:
            return is_leap_year ? day <= 29 : day <= 28;
        default:
            return 0;
    }
}

int validate_phone_number(const char *phone)
{
    if (strlen(phone) != 11)
        return 0;

    if (phone[0] != '8')
        return 0;

    for (int i = 1; i < 11; i++)
        if (!isdigit(phone[i]))
            return 0;

    return 1;
}

int input_subscriber(subscriber_t *subscriber, int index)
{
    size_t pos;

    subscriber->index = index;

    printf("Введите фамилию: ");
    if (fgets(subscriber->surname, MAX_NAME_LEN, stdin) == NULL)
        return IO_ERROR;
    pos = strcspn(subscriber->surname, "\n");
    if (pos == strlen(subscriber->surname))
        return BUFFER_OVERFLOW;
    subscriber->surname[pos] = '\0';
    if (strlen(subscriber->surname) == 0)
        return IO_ERROR;

    printf("Введите имя: ");
    if (fgets(subscriber->name, MAX_NAME_LEN, stdin) == NULL)
        return IO_ERROR;
    pos = strcspn(subscriber->name, "\n");
    if (pos == strlen(subscriber->name))
        return BUFFER_OVERFLOW;
    subscriber->name[pos] = '\0';
    if (strlen(subscriber->name) == 0)
        return IO_ERROR;

    printf("Введите номер телефона (формат: 8**********): ");
    if (fgets(subscriber->phone, MAX_PHONE_LEN, stdin) == NULL)
        return IO_ERROR;
    pos = strcspn(subscriber->phone, "\n");
    if (pos == strlen(subscriber->phone))
        return BUFFER_OVERFLOW;
    subscriber->phone[pos] = '\0';
    if (!validate_phone_number(subscriber->phone))
        return IO_ERROR;

    printf("Введите улицу: ");
    if (fgets(subscriber->street, MAX_STREET_LEN, stdin) == NULL)
        return IO_ERROR;
    pos = strcspn(subscriber->street, "\n");
    if (pos == strlen(subscriber->street))
        return BUFFER_OVERFLOW;
    subscriber->street[pos] = '\0';
    if (strlen(subscriber->street) == 0)
        return IO_ERROR;

    printf("Введите номер дома: ");
    if (scanf("%d", &subscriber->house_number) != 1)
        return IO_ERROR;
    getchar();

    int status;
    printf("Введите статус абонента (0 - друг, 1 - коллега): ");
    if (scanf("%d", &status) != 1)
        return IO_ERROR;
    getchar();

    if (status == 0)
        subscriber->status = FRIEND;
    else if (status == 1)
        subscriber->status = COLLEAGUE;
    else
        return IO_ERROR;

    if (subscriber->status == FRIEND)
    {
        printf("Введите дату рождения (день, месяц, год): ");
        if (scanf("%d%d%d", &subscriber->details.friend_info.birth_date.day,
                  &subscriber->details.friend_info.birth_date.month,
                  &subscriber->details.friend_info.birth_date.year) != 3)
            return IO_ERROR;
        getchar();

        if (!validate_birth_date(
                    subscriber->details.friend_info.birth_date.day,
                    subscriber->details.friend_info.birth_date.month,
                    subscriber->details.friend_info.birth_date.year))
            return IO_ERROR;
    }
    else
    {
        printf("Введите должность: ");
        if (fgets(subscriber->details.colleague_info.position, MAX_POSITION_LEN, stdin) == NULL)
            return IO_ERROR;
        pos = strcspn(subscriber->details.colleague_info.position, "\n");
        if (pos == strlen(subscriber->details.colleague_info.position))
            return BUFFER_OVERFLOW;
        subscriber->details.colleague_info.position[pos] = '\0';
        if (strlen(subscriber->details.colleague_info.position) == 0)
            return IO_ERROR;

        printf("Введите название организации: ");
        if (fgets(subscriber->details.colleague_info.organization, MAX_ORG_LEN, stdin) == NULL)
            return IO_ERROR;
        pos = strcspn(subscriber->details.colleague_info.organization, "\n");
        if (pos == strlen(subscriber->details.colleague_info.organization))
            return BUFFER_OVERFLOW;
        subscriber->details.colleague_info.organization[pos] = '\0';
        if (strlen(subscriber->details.colleague_info.organization) == 0)
            return IO_ERROR;
    }

    return OK;
}

int enter_subscribers_array(subscriber_t subscribers[], int num_subscribers)
{
    int rc;
    for (int i = 0; i < num_subscribers; i++)
    {
        printf("\n--- Ввод данных для абонента #%d ---\n", i + 1);
        rc = input_subscriber(&subscribers[i], i + 1);
        if (rc == IO_ERROR)
            return IO_ERROR;
        else if (rc == BUFFER_OVERFLOW)
            return BUFFER_OVERFLOW;
    }

    return OK;
}

int save_to_csv(subscriber_t *subscribers, int num_entries, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
        return ERROR_FILE_OPEN;

    fprintf(file, "Index,Surname,Name,Phone,Street,House,Status,Details\n");

    for (int i = 0; i < num_entries; i++)
    {
        fprintf(file, "%d,%s,%s,%s,%s,%d,",
                subscribers[i].index,
                subscribers[i].surname,
                subscribers[i].name,
                subscribers[i].phone,
                subscribers[i].street,
                subscribers[i].house_number);

        if (subscribers[i].status == FRIEND)
        {
            fprintf(file, "Friend,%02d-%02d-%04d\n",
                    subscribers[i].details.friend_info.birth_date.day,
                    subscribers[i].details.friend_info.birth_date.month,
                    subscribers[i].details.friend_info.birth_date.year);
        }
        else if (subscribers[i].status == COLLEAGUE)
        {
            fprintf(file, "Colleague,%s,%s\n",
                    subscribers[i].details.colleague_info.position,
                    subscribers[i].details.colleague_info.organization);
        }
    }

    fclose(file);
    return OK;
}

int load_subscribers_from_file(const char *filename, subscriber_t subscribers[], int *num_subscribers)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return ERROR_FILE_OPEN;

    char line[512];
    int index = 0;

    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        return IO_ERROR;
    }

    while (fgets(line, sizeof(line), file))
    {
        if (index >= NUM_ENTRIES)
        {
            fclose(file);
            return ERROR_TOO_MANY_ENTRIES;
        }

        subscriber_t subscriber;
        char status[16];
        char details[64];

        if (sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^\n]",
                   &subscriber.index,
                   subscriber.surname,
                   subscriber.name,
                   subscriber.phone,
                   subscriber.street,
                   &subscriber.house_number,
                   status,
                   details) != 8)
        {
            fclose(file);
            return IO_ERROR;
        }

        if (!validate_phone_number(subscriber.phone))
        {
            fclose(file);
            return IO_ERROR;
        }

        if (strcmp(status, "Friend") == 0)
        {
            subscriber.status = FRIEND;

            if (sscanf(details, "%d-%d-%d",
                       &subscriber.details.friend_info.birth_date.day,
                       &subscriber.details.friend_info.birth_date.month,
                       &subscriber.details.friend_info.birth_date.year) != 3)
            {
                fclose(file);
                return IO_ERROR;
            }

            if (!validate_birth_date(subscriber.details.friend_info.birth_date.day,
                                     subscriber.details.friend_info.birth_date.month,
                                     subscriber.details.friend_info.birth_date.year))
            {
                fclose(file);
                return IO_ERROR;
            }
        }
        else if (strcmp(status, "Colleague") == 0)
        {
            subscriber.status = COLLEAGUE;

            if (sscanf(details, "%[^,],%[^\n]",
                       subscriber.details.colleague_info.position,
                       subscriber.details.colleague_info.organization) != 2)
            {
                fclose(file);
                return IO_ERROR;
            }
        }
        else
        {
            fclose(file);
            return IO_ERROR;
        }

        subscribers[index] = subscriber;
        index++;
    }

    fclose(file);

    *num_subscribers = index;

    return OK;
}
