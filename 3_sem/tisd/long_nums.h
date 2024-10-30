#ifndef LONG_NUMS_H
#define LONG_NUMS_H

#define EXP_LEN 6                                // EXP_MAX (5) + '\0'
#define MANTISSA_LEN 39                          // MANTISSA_MAX (35) + DOT + ROUND_SYMBOL + '\0' + EXTRA_ZERO
#define LONG_NUM_LEN (EXP_LEN + MANTISSA_LEN + 3)// 3 = EPX + DOT + '\0'

#define MAX_MANTISSA_LEN 35
#define MAX_EXP 99999
#define MIN_EXP -99999

enum errors
{
    OK,
    IO_ERROR,
    BUFFER_ERROR,
    ZERO_DIVISION_ERROR,
    OVERFLOW,
};

typedef struct
{
    int exp_nums;
    int mantissa_sign;
    char mantissa_nums[MANTISSA_LEN];
} long_num_t;

int check_long_float(char s[], long_num_t *ln);
int check_long_int(char s[], long_num_t *ln);
void normal_format(long_num_t *ln);
void print_long_num(long_num_t ln);
char int_to_char(int a);
int char_to_int(char a);

long_num_t division_float_on_int(long_num_t *long_float, long_num_t *long_num);

#endif//LONG_NUMS_H
