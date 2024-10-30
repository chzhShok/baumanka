#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "long_nums.h"

char int_to_char(int a)
{
    if (a == 0)
        return '0';
    else if (a == 1)
        return '1';
    else if (a == 2)
        return '2';
    else if (a == 3)
        return '3';
    else if (a == 4)
        return '4';
    else if (a == 5)
        return '5';
    else if (a == 6)
        return '6';
    else if (a == 7)
        return '7';
    else if (a == 8)
        return '8';
    else
        return '9';
}

int char_to_int(char a)
{
    if (a == '0')
        return 0;
    else if (a == '1')
        return 1;
    else if (a == '2')
        return 2;
    else if (a == '3')
        return 3;
    else if (a == '4')
        return 4;
    else if (a == '5')
        return 5;
    else if (a == '6')
        return 6;
    else if (a == '7')
        return 7;
    else if (a == '8')
        return 8;
    else
        return 9;
}

void remove_leading_zeros(char s[], char new_s[])
{
    int ind = 0, new_ind = 0;

    if (strlen(s) == 1)
    {
        new_s[new_ind++] = s[ind++];
    }
    else
    {
        while (s[ind] == '0')
            ind++;

        while (s[ind] != '\0')
            new_s[new_ind++] = s[ind++];
    }

    new_s[new_ind] = '\0';
}

void make_len_divisible_one_greater_len_divisor(char divisible[], char divisor[], char result[], int *ind)
{
    size_t divisible_len = strlen(divisible);
    size_t divisor_len = strlen(divisor);

    int extra = 0;
    if (divisible[0] < divisor[0])
        extra = 1;

    if (divisible_len < divisor_len + extra)
    {
        result[(*ind)++] = '0';
        result[(*ind)++] = '.';
        divisible[divisible_len++] = '0';

        while (divisible_len < divisor_len + extra)
        {
            if (*ind == MAX_MANTISSA_LEN)
            {
                result[*ind] = '\0';
                return;
            }
            result[(*ind)++] = '0';
            divisible[divisible_len++] = '0';
        }

        divisible[divisible_len++] = '\0';
    }
}

size_t find_incomplete_dividend(const char num1[], const char num2[], size_t len2, char incomplete_dividend[])
{
    size_t incomplete_dividend_len;
    if (num1[0] < num2[0])
    {
        strncpy(incomplete_dividend, num1, len2 + 1);
        incomplete_dividend_len = len2 + 1;
    }
    else
    {
        strncpy(incomplete_dividend, num1, len2);
        incomplete_dividend_len = len2;
    }
    incomplete_dividend[incomplete_dividend_len] = '\0';

    return incomplete_dividend_len;
}

void find_quotient(char divisible[], char divisor[], int pow, int *quotient)
{
    int divisible_len = (int) strlen(divisible);
    int divisor_len = (int) strlen(divisor);

    char new_divisible[MANTISSA_LEN];
    char new_divisor[MANTISSA_LEN];
    int ind = 0;
    while (ind < divisible_len - pow)
    {
        new_divisible[ind] = divisible[ind];
        ind++;
    }
    new_divisible[ind] = '\0';

    ind = 0;
    while (ind < divisor_len - pow)
    {
        new_divisor[ind] = divisor[ind];
        ind++;
    }
    new_divisor[ind] = '\0';

    int int_divisible = (int) strtol(new_divisible, NULL, 10);
    int int_divisor = (int) strtol(new_divisor, NULL, 10);

    *quotient = int_divisible / int_divisor;
}

int multiply_long_num_on_short(char mult1[], int mult2, char result[])
{
    char result_reversed[MANTISSA_LEN] = "";

    int ind_mult = (int) strlen(mult1) - 1;
    int ind_res = 0;
    int resudial_num = 0;
    while (ind_mult > 0)
    {
        int num = char_to_int(mult1[ind_mult]);
        int product = num * mult2 + resudial_num;

        result_reversed[ind_res++] = int_to_char(product % 10);

        resudial_num = product / 10;

        ind_mult--;
    }

    int num = char_to_int(mult1[ind_mult]);
    int product = num * mult2 + resudial_num;

    if (product / 10 != 0)
    {
        result_reversed[ind_res++] = int_to_char(product % 10);

        result_reversed[ind_res++] = int_to_char(product / 10);
    }
    else
    {
        char result_num = int_to_char(product % 10);
        result_reversed[ind_res++] = result_num;
    }

    for (int i = ind_res - 1; i >= 0; i--)
    {
        result[ind_res - 1 - i] = result_reversed[i];
    }
    result[ind_res] = '\0';

    return ind_res;
}

int compare_long_nums(char num1[], char num2[])
{
    int len1 = (int) strtol(num1, NULL, 10);
    int len2 = (int) strtol(num2, NULL, 10);

    if (len1 != len2)
        return len1 - len2;

    int ind = 0;
    while (num1[ind] != '\0' && num2[ind] != '\0')
    {
        if (num1[ind] != num2[ind])
            return num1[ind] - num2[ind];
        ind++;
    }

    return 0;
}

int substract_long_nums(char num1[], char num2[], char result[])
{
    int len1 = (int) strlen(num1);
    int len2 = (int) strlen(num2);

    if (strcmp(num1, num2) == 0)
    {
        strcpy(result, "0");
        return len1;
    }

    if (len1 > len2)
    {
        int diff = len1 - len2;

        int ind = len2 - 1;
        while (ind >= 0)
        {
            num2[ind + diff] = num2[ind];
            ind--;
        }

        ind = diff - 1;
        while (ind >= 0)
            num2[ind--] = '0';
        num2[len1] = '\0';
    }

    int ind = len1 - 1;
    int resudial = 0;
    while (ind >= 0)
    {
        int num = char_to_int(num1[ind]) - char_to_int(num2[ind]) - resudial;
        if (num < 0)
        {
            num += 10;
            resudial = 1;
        }
        else
        {
            resudial = 0;
        }

        result[ind--] = int_to_char(num);
    }
    result[len1] = '\0';

    int first_zeros = 0;
    ind = 0;
    while (result[ind] == '0')
    {
        first_zeros++;
        ind++;
    }

    if (first_zeros)
        for (int i = 0; i < (len1 - first_zeros); i++)
            result[i] = result[i + first_zeros];
    result[len1 - first_zeros] = '\0';

    return (int) strlen(result);
}

long_num_t division_float_on_int(long_num_t *long_float, long_num_t *long_num)
{
    long_num_t result;

    if (long_float->mantissa_nums[0] == '0' && long_float->mantissa_nums[1] == '\n')
    {
        result.mantissa_nums[0] = '0';
        result.mantissa_nums[1] = '\0';
        result.exp_nums = 0;
        result.mantissa_sign = 1;
        return result;
    }

    // Убрать експоненту у делимого
    int ln_exp = -long_float->exp_nums;
    long_float->exp_nums = 0;

    int ind = 0;

    // Сделать делимое по длине равное длине делителя
    make_len_divisible_one_greater_len_divisor(long_float->mantissa_nums, long_num->mantissa_nums, result.mantissa_nums, &ind);
    size_t lf_len = strlen(long_float->mantissa_nums);
    size_t ln_len = strlen(long_num->mantissa_nums);

    // Найти неполное делимое
    char incomplete_dividend[MANTISSA_LEN];
    size_t incomplete_dividend_len = find_incomplete_dividend(long_float->mantissa_nums, long_num->mantissa_nums, ln_len, incomplete_dividend);

    // Делим пока не закончится делимое
    int quotient;
    int mantissa_ind = (int) incomplete_dividend_len;
    while (mantissa_ind <= (int) lf_len)
    {
        find_quotient(incomplete_dividend, long_num->mantissa_nums, (int) ln_len - 1, &quotient);

        char product[MANTISSA_LEN + 1];
        multiply_long_num_on_short(long_num->mantissa_nums, quotient, product);
        while (compare_long_nums(incomplete_dividend, product) < 0)
        {
            quotient--;
            multiply_long_num_on_short(long_num->mantissa_nums, quotient, product);
        }

        char new_incomplete_dividend[MANTISSA_LEN];
        int new_inc_div_len = substract_long_nums(incomplete_dividend, product, new_incomplete_dividend);


        new_incomplete_dividend[new_inc_div_len++] = long_float->mantissa_nums[mantissa_ind];
        if (mantissa_ind == (int) lf_len)
            new_inc_div_len--;
        new_incomplete_dividend[new_inc_div_len] = '\0';
        remove_leading_zeros(new_incomplete_dividend, incomplete_dividend);
        incomplete_dividend_len = strlen(incomplete_dividend);

        result.mantissa_nums[ind++] = int_to_char(quotient);

        mantissa_ind++;
    }

    // Проверка, что остаток равен нулю
    if (strcmp(incomplete_dividend, "0") == 0 || strlen(incomplete_dividend) == 0)
    {
        result.exp_nums = -ln_exp;
        result.mantissa_sign = (1 + (long_float->mantissa_sign + long_num->mantissa_sign) % 2) % 2;
        result.mantissa_nums[ind] = '\0';
        return result;
    }
    result.mantissa_nums[ind] = '\0';

    // Добавить точку и продолжить делить, пока есть место
    if (strchr(result.mantissa_nums, '.') == NULL)
        result.mantissa_nums[ind++] = '.';
    incomplete_dividend[incomplete_dividend_len++] = '0';
    incomplete_dividend[incomplete_dividend_len] = '\0';
    while (ind < MANTISSA_LEN - 1 && strcmp(incomplete_dividend, "0") != 0)
    {
        find_quotient(incomplete_dividend, long_num->mantissa_nums, (int) ln_len - 1, &quotient);

        char product[MANTISSA_LEN + 1];
        multiply_long_num_on_short(long_num->mantissa_nums, quotient, product);
        while (compare_long_nums(incomplete_dividend, product) < 0)
        {
            quotient--;
            multiply_long_num_on_short(long_num->mantissa_nums, quotient, product);
        }
        multiply_long_num_on_short(long_num->mantissa_nums, quotient, product);

        char new_incomplete_dividend[MANTISSA_LEN];
        int new_inc_div_len = substract_long_nums(incomplete_dividend, product, new_incomplete_dividend);

        new_incomplete_dividend[new_inc_div_len++] = '0';
        new_incomplete_dividend[new_inc_div_len] = '\0';
        remove_leading_zeros(new_incomplete_dividend, incomplete_dividend);

        result.mantissa_nums[ind++] = int_to_char(quotient);
    }

    result.mantissa_nums[ind] = '\0';
    result.exp_nums = -ln_exp;
    result.mantissa_sign = (1 + (long_float->mantissa_sign + long_num->mantissa_sign) % 2) % 2;

    return result;
}
