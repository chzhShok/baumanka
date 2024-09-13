#ifndef C_MATRIX_UTILS_H
#define C_MATRIX_UTILS_H

#include <stdio.h>

#define N 100
#define M 100
#define IO_ERROR 1
#define INPUT_ERROR 2

int find_second_max(int matrix[N][M], int n);
void delete_column(int matrix[N][M], int ind, int n);
void print_matrix(int matrix[N][M], int n, int m);

#endif//C_MATRIX_UTILS_H
