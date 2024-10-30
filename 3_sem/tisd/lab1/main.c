#include <stdio.h>
#include <string.h>

#include "long_nums.h"

static int rc = OK;

int main(void)
{
    printf("DIVISION\n");
    printf("Enter first real number in the format [+-]m.n[Ee][+-]K\n"
           "(m+n) <= 35, K <= 5: \n");
    printf("|---------|---------|---------|----\n");
    char num1[LONG_NUM_LEN];
    long_num_t ln1;
    if (fgets(num1, LONG_NUM_LEN, stdin) == NULL)
    {
        printf("I/O error\n");
        return IO_ERROR;
    }
    size_t pos_1 = strcspn(num1, "\n");
    if (pos_1 == strlen(num1))
    {
        printf("Buffer overflow\n");
        return BUFFER_ERROR;
    }
    num1[pos_1] = '\0';
    rc = check_long_float(num1, &ln1);
    if (rc)
    {
        printf("I/O error\n");
        return rc;
    }

    printf("Enter second int number in the format [+-]m\n"
           "m <= 35: \n");
    printf("|---------|---------|---------|----\n");
    char num2[MANTISSA_LEN];
    long_num_t ln2;
    if (fgets(num2, MANTISSA_LEN, stdin) == NULL)
    {
        printf("I/O error\n");
        return IO_ERROR;
    }
    size_t pos_2 = strcspn(num2, "\n");
    if (pos_2 == strlen(num2))
    {
        printf("Buffer overflow\n");
        return BUFFER_ERROR;
    }
    num2[pos_2] = '\0';
    rc = check_long_int(num2, &ln2);
    if (rc)
    {
        printf("I/O error\n");
        return rc;
    }

    int ind = 0;
    while (ln2.mantissa_nums[ind] == '0')
        ind++;
    if (ind == (int) strlen(ln2.mantissa_nums))
    {
        printf("Zero division error\n");
        return ZERO_DIVISION_ERROR;
    }

    long_num_t result = division_float_on_int(&ln1, &ln2);
    normal_format(&result);
    if (result.exp_nums > MAX_EXP || result.exp_nums < MIN_EXP)
    {
        printf("Overflow in result. Exponent has more than 5 digits\n");
        return OVERFLOW;
    }

    print_long_num(result);

    return OK;
}
