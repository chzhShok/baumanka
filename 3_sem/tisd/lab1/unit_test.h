#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdlib.h>

#include "long_nums.h"

// FUNCS
void make_len_divisible_one_greater_len_divisor(char divisible[], char divisor[], char result[], int *ind);
size_t find_incomplete_dividend(const char num1[], const char num2[], size_t len2, char incomplete_dividend[]);
void find_quotient(char divisible[], char divisor[], int pow, int *quotient);
int multiply_long_num_on_short(char mult1[], int mult2, char result[]);
int compare_long_nums(char num1[], char num2[]);
int substract_long_nums(char num1[], char num2[], char result[]);

// TESTS
void test_check_long_float(void);
void test_check_long_int(void);

void test_make_identical_exp(void);
void test_make_len_divisible_equal_len_divisor(void);
void test_find_incomplete_dividend(void);
void test_find_quotient(void);
void test_multiply_long_num_on_short(void);
void test_compare_long_nums(void);
void test_substract_long_nums(void);
void test_division_float_on_int(void);

#endif//UNIT_TEST_H
