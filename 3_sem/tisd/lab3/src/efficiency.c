#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "efficiency.h"
#include "matrix.h"

void output(int matrix_size, int density, double time_standard, double time_sparse, int memory_standard, int memory_sparse)
{
    printf("\n");
    for (int i = 0; i < 90; i++)
        printf("-");
    printf("\n");

    printf("Время перемножения матриц %dx%d, заполненность %d %%:\n", matrix_size, matrix_size, density);
    printf("  Стандартные матрицы: %.2f секунд\n", time_standard);
    printf("  Разреженные матрицы: %.2f секунд\n", time_sparse);
    printf("  Процентное соотношение: %.2f %%\n", (1.0 - ((double) time_sparse / (double) time_standard)) * 100.0);

    printf("Память (байт):\n");
    printf("  Стандартные матрицы: %d\n", memory_standard);
    printf("  Разреженные матрицы: %d\n", memory_sparse);
    printf("  Процентное соотношение: %.2f %%\n", (1.0 - ((double) memory_sparse / (double) memory_standard)) * 100.0);

    printf("\n");
}

int standard_matrix_memory(Matrix *matrixA, Matrix *matrixB, Matrix *result_matrix)
{
    return (int) (matrixA->rows * matrixA->columns * sizeof(double) +
                  matrixB->rows * matrixB->columns * sizeof(double) +
                  result_matrix->rows * result_matrix->columns * sizeof(double));
}

int sparse_matrix_memory(SparseMatrixA *matrixA, SparseMatrixB *matrixB, SparseMatrixA *result_matrix)
{
    return (int) (matrixA->nonzeros * sizeof(double) + matrixA->nonzeros * sizeof(int) +
                  (matrixA->cols + 1) * sizeof(int) +
                  matrixB->nonzeros * sizeof(double) + matrixB->nonzeros * sizeof(int) +
                  (matrixB->rows + 1) * sizeof(int) +
                  result_matrix->nonzeros * sizeof(double) + result_matrix->nonzeros * sizeof(int) +
                  (result_matrix->cols + 1) * sizeof(int));
}

void measure_efficiency(void)
{
    Matrix *matrixA = (Matrix *) malloc(sizeof(Matrix));
    Matrix *matrixB = (Matrix *) malloc(sizeof(Matrix));
    Matrix *result_matrix = (Matrix *) malloc(sizeof(Matrix));

    SparseMatrixA *sparse_matrixA = (SparseMatrixA *) malloc(sizeof(SparseMatrixA));
    SparseMatrixB *sparse_matrixB = (SparseMatrixB *) malloc(sizeof(SparseMatrixB));
    SparseMatrixA *sparse_result_matrix = (SparseMatrixA *) malloc(sizeof(SparseMatrixA));

    int matrix_sizes[MATRIX_SIZES_LEN] = {30, 70, 100};
    int densities[DENSITIES_LEN] = {1, 10, 20, 25, 30, 40, 50};

    struct timespec start, end;

    for (int i = 0; i < MATRIX_SIZES_LEN; i++)
    {
        int rows = matrix_sizes[i];
        int cols = matrix_sizes[i];
        for (int j = 0; j < DENSITIES_LEN; j++)
        {
            int density = densities[j];

            generate_dense_matrix(matrixA, rows, cols, density);
            generate_dense_matrix(matrixB, rows, cols, density);

            convert_matrix_to_sparse_matrixA(matrixA, sparse_matrixA);
            convert_matrix_to_sparse_matrixB(matrixB, sparse_matrixB);

            double sum_times_std = 0.0;
            double sum_times_sparse = 0.0;

            for (int t = 0; t < MEASURE_TIMES; t++)
            {
                clock_gettime(CLOCK_MONOTONIC, &start);
                multiply_dense_matrices(matrixA, matrixB, result_matrix);
                clock_gettime(CLOCK_MONOTONIC, &end);
                sum_times_std += (double) (end.tv_sec - start.tv_sec) * 1000000000LL +
                                 (double) (end.tv_nsec - start.tv_nsec);
            }

            for (int t = 0; t < MEASURE_TIMES; t++)
            {
                clock_gettime(CLOCK_MONOTONIC, &start);
                sparse_result_matrix = multiply_sparse_matrices(sparse_matrixA, sparse_matrixB);
                clock_gettime(CLOCK_MONOTONIC, &end);
                sum_times_sparse += (double) (end.tv_sec - start.tv_sec) * 1000000000LL +
                                    (double) (end.tv_nsec - start.tv_nsec);
            }

            int memory_standard = standard_matrix_memory(matrixA, matrixB, result_matrix);
            int memory_sparse = sparse_matrix_memory(sparse_matrixA, sparse_matrixB, sparse_result_matrix);

            double time_standard = (double) sum_times_std / MEASURE_TIMES;
            double time_sparse = (double) sum_times_sparse / MEASURE_TIMES;

            output(rows, density, time_standard, time_sparse, memory_standard, memory_sparse);
        }
    }

    free_matrix(matrixA);
    free_matrix(matrixB);
    free_sparse_matrixA(sparse_matrixA);
    free_sparse_matrixB(sparse_matrixB);
}
