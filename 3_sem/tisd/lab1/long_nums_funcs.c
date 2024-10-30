#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "long_nums.h"

static int remove_dot_from_mantissa(int exp_part, int nums_after_dot)
{
    while (nums_after_dot > 0)
    {
        exp_part--;
        nums_after_dot--;
    }

    return exp_part;
}

int check_long_float(char s[], long_num_t *ln)
{
    int ind = 0;

    ln->mantissa_sign = 1;

    while (isspace(s[ind]))
        ind++;

    if (s[ind] == '+' || s[ind] == '-')
    {
        ln->mantissa_sign = s[ind] == '+';
        ind++;
    }

    while (s[ind] == '0')
        ind++;
    if (s[ind] == '\0')
    {
        ln->mantissa_nums[0] = '0';
        ln->mantissa_nums[1] = '\0';
        ln->mantissa_sign = 1;
        ln->exp_nums = 0;
        return OK;
    }

    int ind_mantissa = 0, nums_after_dot = 0;
    if (strchr(s, '.'))
    {
        while (s[ind] != '.' && s[ind] != '\0' && (isdigit(s[ind]) || isspace(s[ind])))
            ln->mantissa_nums[ind_mantissa++] = s[ind++];
        if (s[ind] != '.' && s[ind] != '\0')
            return IO_ERROR;
        if (s[ind] == '\0' && ind_mantissa <= MAX_MANTISSA_LEN)
        {
            ln->exp_nums = 0;
            return OK;
        }
        ind++;

        while (s[ind] != 'E' && s[ind] != 'e' && s[ind] != '\0' && !isspace(s[ind]) && isdigit(s[ind]))
        {
            ln->mantissa_nums[ind_mantissa++] = s[ind++];
            nums_after_dot++;
        }
        ln->mantissa_nums[ind_mantissa] = '\0';

        if (s[ind] != 'E' && s[ind] != 'e' && s[ind] != '\0' && !isspace(s[ind]))
            return IO_ERROR;
        if (s[ind] == '\0' && ind_mantissa <= MAX_MANTISSA_LEN)
        {
            ln->exp_nums = remove_dot_from_mantissa(0, nums_after_dot);
            return OK;
        }
    }
    else
    {
        while (s[ind] != 'e' && s[ind] != 'E' && s[ind] != '\0' && !isspace(s[ind]) && isdigit(s[ind]))
            ln->mantissa_nums[ind_mantissa++] = s[ind++];
        ln->mantissa_nums[ind_mantissa] = '\0';

        if (s[ind] != 'E' && s[ind] != 'e' && s[ind] != '\0' && !isspace(s[ind]))
            return IO_ERROR;
        if (ind_mantissa == 0)
            return IO_ERROR;
        if (s[ind] == '\0' && ind_mantissa <= MAX_MANTISSA_LEN)
        {
            ln->exp_nums = 0;
            return OK;
        }
    }

    if (ind_mantissa > 35)
        return IO_ERROR;

    if (ind_mantissa == 0)
        return IO_ERROR;

    if (s[ind] == 'E' || s[ind] == 'e')
        ind++;

    int ind_exp = 0;
    char exp_part[EXP_LEN + 1];// '-' + EXP_LEN
    if (s[ind] == '+' || s[ind] == '-')
    {
        if (s[ind] == '-')
            exp_part[ind_exp++] = s[ind];
        ind++;
    }

    while (s[ind] != '\0' && isdigit(s[ind]))
        exp_part[ind_exp++] = s[ind++];
    if (s[ind] != '\0')
        return IO_ERROR;
    if (ind_exp == 0 || (exp_part[0] == '-' && ind_exp == 1))
        return IO_ERROR;
    if ((exp_part[0] == '-' && ind_exp >= EXP_LEN + 1) || (exp_part[0] != '-' && ind_exp >= EXP_LEN))
        return IO_ERROR;
    exp_part[ind_exp] = '\0';

    ln->exp_nums = (int) strtol(exp_part, NULL, 10);

    int ind_zero = 0;
    while (ln->mantissa_nums[ind_zero] == '0')
        ind_zero++;
    if (ind_zero != (int) strlen(ln->mantissa_nums))
        ln->exp_nums = remove_dot_from_mantissa(ln->exp_nums, nums_after_dot);

    return OK;
}

int check_long_int(char s[], long_num_t *ln)
{
    int ind = 0;
    ln->exp_nums = 0;
    ln->mantissa_sign = 1;

    while (isspace(s[ind]))
        ind++;

    if (s[ind] == '+' || s[ind] == '-')
    {
        if (s[ind] == '-')
            ln->mantissa_sign = 0;
        ind++;
    }

    int mantissa_ind = 0;
    while (s[ind] != '\0' && isdigit(s[ind]))
        ln->mantissa_nums[mantissa_ind++] = s[ind++];
    ln->mantissa_nums[mantissa_ind] = '\0';

    if (ind != (int) strlen(s))
        return IO_ERROR;
    if (ind >= MANTISSA_LEN)
        return IO_ERROR;

    return OK;
}

void print_long_num(long_num_t ln)
{
    if (ln.mantissa_sign == 0)
        printf("-");
    printf("%s", ln.mantissa_nums);

    printf("e%d\n", ln.exp_nums);
}

void normal_format(long_num_t *ln)
{
    char mantissa[MANTISSA_LEN + 2];// DOT + '0'
    int mantissa_ind = 0;
    mantissa[mantissa_ind++] = '0';
    mantissa[mantissa_ind++] = '.';
    int ind = 0;

    if (strlen(ln->mantissa_nums) > 2 && ln->mantissa_nums[0] == '0' && ln->mantissa_nums[1] == '.')
    {
        ind += 2;
        while (ln->mantissa_nums[ind] != '\0' && mantissa_ind < MANTISSA_LEN)
        {
            mantissa[mantissa_ind++] = ln->mantissa_nums[ind++];
        }
    }
    else if (strchr(ln->mantissa_nums + ind, '.'))
    {
        while (ln->mantissa_nums[ind] != '.')
        {
            ln->exp_nums++;
            mantissa[mantissa_ind++] = ln->mantissa_nums[ind++];
        }
        ind++;
        while (ln->mantissa_nums[ind] != '\0' && mantissa_ind < MANTISSA_LEN - 1)
        {
            mantissa[mantissa_ind++] = ln->mantissa_nums[ind++];
        }
    }
    else
    {
        while (ln->mantissa_nums[ind] != '\0' && mantissa_ind < MANTISSA_LEN - 1)
        {
            ln->exp_nums++;
            mantissa[mantissa_ind++] = ln->mantissa_nums[ind++];
        }
    }
    mantissa[mantissa_ind] = '\0';
    char last_symbol = mantissa[mantissa_ind - 1];

    if (mantissa_ind == MANTISSA_LEN - 1)
    {
        if (strchr("01234", last_symbol))
        {
            mantissa[mantissa_ind - 1] = '\0';
        }
        else
        {
            int add = 1;
            int round_ind = mantissa_ind - 2;
            while (add && mantissa[round_ind] != '.')
            {
                int new_num = char_to_int(mantissa[round_ind]) + 1;

                if (new_num > 9)
                {
                    mantissa[round_ind] = '0';
                }
                else
                {
                    add = 0;
                    mantissa[round_ind] = int_to_char(new_num);
                }
                round_ind--;
            }
            mantissa[mantissa_ind - 1] = '\0';

            if (add)
            {
                mantissa[0] = '1';
                strcpy(ln->mantissa_nums, mantissa);
                normal_format(ln);
            }
        }
    }

    strcpy(ln->mantissa_nums, mantissa);
}
