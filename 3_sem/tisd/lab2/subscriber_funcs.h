#ifndef SUBSCRIBER_FUNCS_H
#define SUBSCRIBER_FUNCS_H

#define NUM_ENTRIES 100
#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 20
#define MAX_STREET_LEN 50
#define MAX_POSITION_LEN 50
#define MAX_ORG_LEN 50

#define SORT_METHOD_LEN 3

enum error
{
    OK,
    IO_ERROR,
    BUFFER_OVERFLOW,
    ERROR_TOO_MANY_ENTRIES,
    ERROR_FILE_OPEN,
    COMMAND_ERROR,
    WRONG_SORT_METHOD,
};

typedef struct
{
    int day;
    int month;
    int year;
} birth_date_t;

typedef struct
{
    char position[MAX_POSITION_LEN];
    char organization[MAX_ORG_LEN];
} colleague_info_t;

typedef struct
{
    birth_date_t birth_date;
} friend_info_t;

typedef union
{
    friend_info_t friend_info;
    colleague_info_t colleague_info;
} subscriber_details_t;

typedef enum
{
    FRIEND,
    COLLEAGUE
} subscriber_status_t;

typedef struct
{
    int index;
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char street[MAX_STREET_LEN];
    int house_number;
    subscriber_status_t status;
    subscriber_details_t details;
} subscriber_t;

int input_subscriber(subscriber_t *subscriber, int index);
int save_to_csv(subscriber_t *subscribers, int num_entries, const char *filename);
int enter_subscribers_array(subscriber_t subscribers[], int num_subscribers);
int load_subscribers_from_file(const char *filename, subscriber_t subscribers[], int *num_subscribers);

#endif// SUBSCRIBER_FUNCS_H
