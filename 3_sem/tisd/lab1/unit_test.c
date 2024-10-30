#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "long_nums.h"
#include "unit_test.h"

void test_check_long_float(void)
{
    printf("TESTING: check_long_float\n");

    char s[LONG_NUM_LEN];
    long_num_t lf;

    // 1
    strcpy(s, "11");
    assert(check_long_float(s, &lf) == OK);

    // 2
    strcpy(s, "12345678901234567890123456789012345");
    assert(check_long_float(s, &lf) == OK);

    // 3
    strcpy(s, "123456789012345678901234567890123456");
    assert(check_long_float(s, &lf) != OK);

    // 4
    strcpy(s, "+1");
    assert(check_long_float(s, &lf) == OK);

    // 5
    strcpy(s, "-1");
    assert(check_long_float(s, &lf) == OK);

    // 6
    strcpy(s, "+");
    assert(check_long_float(s, &lf) != OK);

    // 7
    strcpy(s, "-");
    assert(check_long_float(s, &lf) != OK);

    // 8
    strcpy(s, "1-");
    assert(check_long_float(s, &lf) != OK);

    // 9
    strcpy(s, "1+");
    assert(check_long_float(s, &lf) != OK);

    // 10
    strcpy(s, "1E+");
    assert(check_long_float(s, &lf) != OK);

    // 11
    strcpy(s, "1E-");
    assert(check_long_float(s, &lf) != OK);

    // 12
    strcpy(s, "1E-1");
    assert(check_long_float(s, &lf) == OK);

    // 13
    strcpy(s, "1E+1");
    assert(check_long_float(s, &lf) == OK);

    // 14
    strcpy(s, ".E+1");
    assert(check_long_float(s, &lf) != OK);

    // 15
    strcpy(s, ".E-1");
    assert(check_long_float(s, &lf) != OK);

    // 16
    strcpy(s, "eE");
    assert(check_long_float(s, &lf) != OK);

    // 17
    strcpy(s, "1.1e999999");
    assert(check_long_float(s, &lf) != OK);

    // 18
    strcpy(s, "");
    assert(check_long_float(s, &lf) != OK);

    // 19
    strcpy(s, " ");
    assert(check_long_float(s, &lf) != OK);

    // 20
    strcpy(s, ".1");
    assert(check_long_float(s, &lf) == OK);

    // 21
    strcpy(s, "+1.");
    assert(check_long_float(s, &lf) == OK);

    // 22
    strcpy(s, "+1..E1");
    assert(check_long_float(s, &lf) != OK);

    // 23
    strcpy(s, "+1.Ee1");
    assert(check_long_float(s, &lf) != OK);

    printf("TESTS PASSED\n\n");
}

void test_check_long_int(void)
{
    printf("TESTING: check_long_int\n");

    char s[LONG_NUM_LEN];
    long_num_t ln;

    // 1
    strcpy(s, "1");
    assert(check_long_int(s, &ln) == OK);

    // 2
    strcpy(s, "11111111111111111111111111111111111");
    assert(check_long_int(s, &ln) == OK);

    // 3
    strcpy(s, "111111111111111111111111111111111111");
    assert(check_long_int(s, &ln) != OK);

    // 4
    strcpy(s, "+1");
    assert(check_long_int(s, &ln) == OK);

    // 5
    strcpy(s, "-134");
    assert(check_long_int(s, &ln) == OK);

    // 6
    strcpy(s, "12.1");
    assert(check_long_int(s, &ln) != OK);

    // 7
    strcpy(s, "+12.1");
    assert(check_long_int(s, &ln) != OK);

    // 8
    strcpy(s, "-12.1");
    assert(check_long_int(s, &ln) != OK);

    // 9
    strcpy(s, "112e2");
    assert(check_long_int(s, &ln) != OK);

    // 10
    strcpy(s, "e1122");
    assert(check_long_int(s, &ln) != OK);

    // 11
    strcpy(s, "1122e+");
    assert(check_long_int(s, &ln) != OK);

    // 12
    strcpy(s, ".12");
    assert(check_long_int(s, &ln) != OK);

    // 13
    strcpy(s, "12.");
    assert(check_long_int(s, &ln) != OK);

    // 14
    strcpy(s, "++12");
    assert(check_long_int(s, &ln) != OK);

    // 15
    strcpy(s, "--12");
    assert(check_long_int(s, &ln) != OK);

    // 16
    strcpy(s, "-1-2");
    assert(check_long_int(s, &ln) != OK);

    // 17
    strcpy(s, "-12-");
    assert(check_long_int(s, &ln) != OK);

    printf("TESTS PASSED\n\n");
}

void test_make_len_divisible_equal_len_divisor(void)
{
    printf("TESTING: make_len_divisible_equal_len_divisor\n");

    char n1[MANTISSA_LEN], n2[MANTISSA_LEN], result[MANTISSA_LEN];
    int ind = 0;

    // 1
    strcpy(n1, "200");
    strcpy(n2, "2");
    strcpy(result, "");
    make_len_divisible_one_greater_len_divisor(n1, n2, result, &ind);
    assert(strcmp(n1, "200") == 0);
    assert(strcmp(n2, "2") == 0);
    assert(strcmp(result, "") == 0);

    // 2
    strcpy(n1, "2");
    strcpy(n2, "200");
    strcpy(result, "0.0");
    make_len_divisible_one_greater_len_divisor(n1, n2, result, &ind);
    assert(strcmp(n1, "200") == 0);
    assert(strcmp(n2, "200") == 0);
    assert(strcmp(result, "0.0") == 0);

    // 3
    strcpy(n1, "200");
    strcpy(n2, "200");
    strcpy(result, "");
    make_len_divisible_one_greater_len_divisor(n1, n2, result, &ind);
    assert(strcmp(n1, "200") == 0);
    assert(strcmp(n2, "200") == 0);
    assert(strcmp(result, "") == 0);

    printf("TESTS PASSED\n\n");
}

void test_find_incomplete_dividend(void)
{
    // Гарантируется, что будет делимое больше делителя
    printf("TESTING: find_incomplete_dividend\n");

    char num1[MANTISSA_LEN], num2[MANTISSA_LEN], incomplete_dividend[MANTISSA_LEN];
    size_t len2, res_len;

    // 1
    strcpy(num1, "76");
    strcpy(num2, "54");
    len2 = 2;
    res_len = find_incomplete_dividend(num1, num2, len2, incomplete_dividend);
    assert(strcmp(incomplete_dividend, "76") == 0);
    assert(res_len == 2);

    // 2
    strcpy(num1, "76");
    strcpy(num2, "5");
    len2 = 1;
    res_len = find_incomplete_dividend(num1, num2, len2, incomplete_dividend);
    assert(strcmp(incomplete_dividend, "7") == 0);
    assert(res_len == 1);

    // 3
    strcpy(num1, "765");
    strcpy(num2, "43");
    len2 = 2;
    res_len = find_incomplete_dividend(num1, num2, len2, incomplete_dividend);
    assert(strcmp(incomplete_dividend, "76") == 0);
    assert(res_len == 2);

    // 4
    strcpy(num1, "765");
    strcpy(num2, "4");
    len2 = 1;
    res_len = find_incomplete_dividend(num1, num2, len2, incomplete_dividend);
    assert(strcmp(incomplete_dividend, "7") == 0);
    assert(res_len == 1);

    printf("TESTS PASSED\n\n");
}

void test_find_quotient(void)
{
    // Гарантируется, что делимое по длине больше или равно делителю
    // Находит: (a mod k) / (b mod k), где k = len(b) - 1
    printf("TESTING: find_quotient\n");

    char divisible[MANTISSA_LEN], divisor[MANTISSA_LEN];
    int quotient, pow;

    // 1
    strcpy(divisible, "12345");
    strcpy(divisor, "3748");
    pow = 3;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 4);

    // 2
    strcpy(divisible, "123");
    strcpy(divisor, "123");
    pow = 2;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 1);

    // 3
    strcpy(divisible, "246");
    strcpy(divisor, "123");
    pow = 2;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 2);

    // 4
    strcpy(divisible, "245");
    strcpy(divisor, "123");
    pow = 2;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 2);

    // 5
    strcpy(divisible, "3");
    strcpy(divisor, "1");
    pow = 0;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 3);

    // 6
    strcpy(divisible, "7");
    strcpy(divisor, "3");
    pow = 0;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 2 || quotient == 3);

    // 7
    strcpy(divisible, "13");
    strcpy(divisor, "3");
    pow = 0;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 4);

    // 8
    strcpy(divisible, "39");
    strcpy(divisor, "15");
    pow = 1;
    find_quotient(divisible, divisor, pow, &quotient);
    assert(quotient == 3);

    printf("TESTS PASSED\n\n");
}

void test_multiply_long_num_on_short(void)
{
    printf("TESTING: multiply_long_num_on_short\n");

    char num1[MANTISSA_LEN];
    int num2;
    char result[MANTISSA_LEN];

    // 1
    strcpy(num1, "3748");
    num2 = 4;
    multiply_long_num_on_short(num1, num2, result);
    assert(strcmp(result, "14992") == 0);

    // 2
    strcpy(num1, "1");
    num2 = 5;
    multiply_long_num_on_short(num1, num2, result);
    assert(strcmp(result, "5") == 0);

    // 3
    strcpy(num1, "999");
    num2 = 9;
    multiply_long_num_on_short(num1, num2, result);
    assert(strcmp(result, "8991") == 0);

    // 4
    strcpy(num1, "1000");
    num2 = 9;
    multiply_long_num_on_short(num1, num2, result);
    assert(strcmp(result, "9000") == 0);

    // 5
    strcpy(num1, "1002");
    num2 = 5;
    multiply_long_num_on_short(num1, num2, result);
    assert(strcmp(result, "5010") == 0);

    // 6
    strcpy(num1, "25");
    num2 = 4;
    multiply_long_num_on_short(num1, num2, result);
    assert(strcmp(result, "100") == 0);

    printf("TESTS PASSED\n\n");
}

void test_compare_long_nums(void)
{
    printf("TESTING: compare_long_nums\n");

    char num1[MANTISSA_LEN], num2[MANTISSA_LEN];
    int res;

    // 1
    strcpy(num1, "12345");
    strcpy(num2, "14992");
    res = compare_long_nums(num1, num2);
    assert(res < 0);

    // 2
    strcpy(num1, "12345");
    strcpy(num2, "12345");
    res = compare_long_nums(num1, num2);
    assert(res == 0);

    // 3
    strcpy(num1, "12345");
    strcpy(num2, "12346");
    res = compare_long_nums(num1, num2);
    assert(res < 0);

    // 4
    strcpy(num1, "12345");
    strcpy(num2, "12344");
    res = compare_long_nums(num1, num2);
    assert(res > 0);

    // 5
    strcpy(num1, "12345");
    strcpy(num2, "1234");
    res = compare_long_nums(num1, num2);
    assert(res > 0);

    // 5
    strcpy(num1, "12345");
    strcpy(num2, "1234");
    res = compare_long_nums(num1, num2);
    assert(res > 0);

    printf("TESTS PASSED\n\n");
}

void test_substract_long_nums(void)
{
    // Гарантируется, что num1 > num2
    printf("TESTING: substract_long_nums\n");

    char num1[MANTISSA_LEN], num2[MANTISSA_LEN];
    char result[MANTISSA_LEN];

    // 1
    strcpy(num1, "12345");
    strcpy(num2, "11244");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "1101") == 0);

    // 2
    strcpy(num1, "1000");
    strcpy(num2, "999");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "1") == 0);

    // 3
    strcpy(num1, "999");
    strcpy(num2, "999");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "0") == 0);

    // 4
    strcpy(num1, "10");
    strcpy(num2, "1");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "9") == 0);

    // 5
    strcpy(num1, "7");
    strcpy(num2, "5");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "2") == 0);

    // 6
    strcpy(num1, "25162");
    strcpy(num2, "18345");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "6817") == 0);

    // 7
    strcpy(num1, "12368");
    strcpy(num2, "12345");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "23") == 0);

    // 8
    strcpy(num1, "12368");
    strcpy(num2, "1234");
    substract_long_nums(num1, num2, result);
    assert(strcmp(result, "11134") == 0);

    printf("TESTS PASSED\n\n");
}

void test_division_float_on_int(void)
{
    printf("TESTING: division_float_on_int\n");

    char n1[LONG_NUM_LEN];
    char n2[MANTISSA_LEN];
    long_num_t lf, ln;
    long_num_t result;
    long_num_t expec_res;

    // 1
    strcpy(n1, "2");
    strcpy(n2, "1");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){1, 1, "0.2"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 2
    strcpy(n1, "2e2");
    strcpy(n2, "2");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){3, 1, "0.1"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 3
    strcpy(n1, "2e-2");
    strcpy(n2, "2");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){-1, 1, "0.1"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 4
    strcpy(n1, "2e-2");
    strcpy(n2, "1");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){-1, 1, "0.2"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 5
    strcpy(n1, "12.34e3");
    strcpy(n2, "31");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){3, 1, "0.39806451612903225806451612903225806"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 6
    strcpy(n1, "237.12e-5");
    strcpy(n2, "127");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){-4, 1, "0.18670866141732283464566929133858268"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 7
    strcpy(n1, "12");
    strcpy(n2, "52");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){0, 1, "0.23076923076923076923076923076923077"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 8
    strcpy(n1, "1");
    strcpy(n2, "1");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){1, 1, "0.1"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 9
    strcpy(n1, "100");
    strcpy(n2, "2");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){2, 1, "0.50"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 10
    strcpy(n1, "49");
    strcpy(n2, "7");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){1, 1, "0.7"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 10
    strcpy(n1, "1000");
    strcpy(n2, "3");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){3, 1, "0.33333333333333333333333333333333333"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 11
    strcpy(n1, "2");
    strcpy(n2, "3");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){0, 1, "0.66666666666666666666666666666666667"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 12 //
    strcpy(n1, "2");
    strcpy(n2, "999999");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){0, 1, "0.00000200000200000200000200000200000"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 13
    strcpy(n1, "999999");
    strcpy(n2, "2");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){6, 1, "0.4999995"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 14
    strcpy(n1, "0.0e-9999");
    strcpy(n2, "1");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){-9999, 1, "0.0"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    // 15
    strcpy(n1, "11.1e3");
    strcpy(n2, "1");
    check_long_float(n1, &lf);
    check_long_int(n2, &ln);
    result = division_float_on_int(&lf, &ln);
    normal_format(&result);
    expec_res = (long_num_t){5, 1, "0.111"};
    assert(result.exp_nums == expec_res.exp_nums);
    assert(result.mantissa_sign == expec_res.mantissa_sign);
    assert(strcmp(result.mantissa_nums, expec_res.mantissa_nums) == 0);

    printf("TESTS PASSED\n\n");
}
