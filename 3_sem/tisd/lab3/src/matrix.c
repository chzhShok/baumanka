#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

void generate_dense_matrix(Matrix *matrix, int rows, int cols, double density)
{
    matrix->rows = rows;
    matrix->columns = cols;
    matrix->nonzeros = 0;

    matrix->data = (double **) malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; ++i)
        matrix->data[i] = (double *) calloc(cols, sizeof(double));

    int total_elements = rows * cols;
    int target_nonzeros = (int) (total_elements * density / 100.0);

    srand((unsigned int) time(NULL));

    for (int k = 0; k < target_nonzeros; ++k)
    {
        int i, j;
        double value;

        do
        {
            i = rand() % rows;
            j = rand() % cols;
        } while (matrix->data[i][j] > EPS);

        value = (rand() % 100) + 1;
        matrix->data[i][j] = value;
        matrix->nonzeros++;
    }
}

void input_dense_matrix(Matrix *matrix, int rows, int cols, int nonzeros_input)
{
    matrix->rows = rows;
    matrix->columns = cols;
    matrix->nonzeros = 0;

    matrix->data = (double **) malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; ++i)
        matrix->data[i] = (double *) calloc(cols, sizeof(double));

    printf("Введите элементы матрицы в формате: строка столбец значение\n");
    for (int i = 0; i < nonzeros_input; ++i)
    {
        int row, col;
        double value;

        printf("Элемент %d: ", i + 1);
        if (scanf("%d %d %lf", &row, &col, &value) != 3)
        {
            printf("Ошибка ввода. Повторите ввод элемента %d:\n", i + 1);
            --i;
            continue;
        }

        if (row < 0 || row >= rows || col < 0 || col >= cols || value < EPS)
        {
            printf("Ошибка: некорректные индексы или значение элемента.\n");
            --i;
            continue;
        }

        matrix->data[row][col] = value;
    }

    matrix->nonzeros = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (matrix->data[i][j] > EPS)
                matrix->nonzeros++;
}

void convert_matrix_to_sparse_matrixA(Matrix *matrix, SparseMatrixA *sparse_matrix)
{
    int elem_i;

    sparse_matrix->rows = matrix->rows;
    sparse_matrix->cols = matrix->columns;

    sparse_matrix->nonzeros = 0;
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            if (fabs(matrix->data[i][j]) > EPS)
                sparse_matrix->nonzeros++;

    sparse_matrix->A = malloc(sparse_matrix->nonzeros * sizeof(double));
    sparse_matrix->IA = malloc(sparse_matrix->nonzeros * sizeof(int));
    sparse_matrix->JA = malloc((sparse_matrix->cols + 1) * sizeof(int));

    sparse_matrix->JA[0] = 0;

    elem_i = 0;
    for (int j = 0; j < sparse_matrix->cols; j++)
    {
        for (int i = 0; i < sparse_matrix->rows; i++)
        {
            double elem = matrix->data[i][j];
            if (fabs(elem) > EPS)
            {
                sparse_matrix->A[elem_i] = elem;
                sparse_matrix->IA[elem_i] = i;
                elem_i++;
            }
        }
        sparse_matrix->JA[j + 1] = elem_i;
    }
}

void convert_matrix_to_sparse_matrixB(Matrix *matrix, SparseMatrixB *sparse_matrix)
{
    int nonzeros = 0;

    for (int i = 0; i < matrix->rows; ++i)
        for (int j = 0; j < matrix->columns; ++j)
            if (matrix->data[i][j] != 0.0)
                nonzeros++;

    sparse_matrix->nonzeros = nonzeros;
    sparse_matrix->rows = matrix->rows;
    sparse_matrix->cols = matrix->columns;

    sparse_matrix->B = (double *) malloc(nonzeros * sizeof(double));
    sparse_matrix->JB = (int *) malloc(nonzeros * sizeof(int));
    sparse_matrix->IB = (int *) malloc((matrix->rows + 1) * sizeof(int));

    int items_cnt = 0;
    sparse_matrix->IB[0] = 0;

    for (int i = 0; i < matrix->rows; i++)
    {
        int row_nonzeros = 0;

        for (int j = 0; j < matrix->columns; j++)
        {
            if (matrix->data[i][j] != 0.0)
            {
                sparse_matrix->B[items_cnt] = matrix->data[i][j];
                sparse_matrix->JB[items_cnt] = j;
                items_cnt++;
                row_nonzeros++;
            }
        }

        sparse_matrix->IB[i + 1] = sparse_matrix->IB[i] + row_nonzeros;
    }
}

void print_dense_matrix(const Matrix *matrix)
{
    if (matrix->rows > 30 || matrix->columns > 30)
    {
        printf("Матрица слишком большая для отображения (размер %dx%d).\n", matrix->rows, matrix->columns);
        return;
    }

    printf("Матрица (%dx%d):\n", matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows; ++i)
    {
        for (int j = 0; j < matrix->columns; ++j)
            printf("%.2f ", matrix->data[i][j]);
        printf("\n");
    }
}

void print_sparse_matrixA(const SparseMatrixA *matrix)
{
    printf("Значения ненулевых элементов (A):\n");
    for (int i = 0; i < matrix->nonzeros; ++i)
        printf("%5.2f ", matrix->A[i]);

    printf("\nИндексы строк (IA):\n");
    for (int i = 0; i < matrix->nonzeros; ++i)
        printf("%5d ", matrix->IA[i]);

    printf("\nИндексы начала столбцов (JA):\n");
    for (int i = 0; i <= matrix->cols; ++i)
        printf("%5d ", matrix->JA[i]);

    printf("\n");
}

void print_sparse_matrixB(const SparseMatrixB *matrix)
{
    printf("Значения ненулевых элементов (B):\n");
    for (int i = 0; i < matrix->nonzeros; ++i)
        printf("%5.2f ", matrix->B[i]);

    printf("\nИндексы столбцов (JB):\n");
    for (int i = 0; i < matrix->nonzeros; ++i)
        printf("%5d ", matrix->JB[i]);

    printf("\nИндексы начала строк (IB):\n");
    for (int i = 0; i <= matrix->rows; ++i)
        printf("%5d ", matrix->IB[i]);

    printf("\n");
}

SparseMatrixA *multiply_sparse_matrices(const SparseMatrixA *matrixA, const SparseMatrixB *matrixB)
{
    if (matrixA->cols != matrixB->rows)
    {
        printf("Ошибка: матрицы не могут быть перемножены\n");
        return NULL;
    }

    // Инициализация результирующей матрицы
    SparseMatrixA *result = (SparseMatrixA *) malloc(sizeof(SparseMatrixA));
    result->rows = matrixA->rows;
    result->cols = matrixB->cols;
    result->A = (double *) malloc(sizeof(double) * (matrixA->nonzeros * matrixB->cols));
    result->IA = (int *) malloc(sizeof(int) * (matrixA->nonzeros * matrixB->cols));
    result->JA = (int *) calloc((matrixA->cols + 1), sizeof(int));

    // Временные массивы для расчета столбцов результирующей матрицы
    double *temp_values = (double *) calloc(matrixA->rows, sizeof(double));// Накопитель значений
    int *is_nonzero = (int *) calloc(matrixA->rows, sizeof(int));          // Массив для отслеживания ненулевых строк

    int nonzeros_count = 0;

    for (int j = 0; j < matrixB->cols; j++)// Перебираем столбцы результирующей матрицы
    {
        for (int i = 0; i < matrixA->rows; i++)
        {
            temp_values[i] = 0.0;
            is_nonzero[i] = 0;
        }

        // Умножение столбца матрицы B на строки матрицы A
        for (int k = 0; k < matrixB->rows; k++)// Проходим по строкам матрицы B
        {
            for (int idxA = matrixA->JA[k]; idxA < matrixA->JA[k + 1]; idxA++)// Элементы текущего столбца A
            {
                int rowA = matrixA->IA[idxA];
                double valueA = matrixA->A[idxA];

                for (int idxB = matrixB->IB[k]; idxB < matrixB->IB[k + 1]; idxB++)
                {
                    if (matrixB->JB[idxB] == j)// Столбец в B совпадает
                    {
                        double valueB = matrixB->B[idxB];
                        temp_values[rowA] += valueA * valueB;
                        is_nonzero[rowA] = 1;
                    }
                }
            }
        }

        // Добавление ненулевых значений в результирующую матрицу
        for (int i = 0; i < matrixA->rows; i++)
        {
            if (is_nonzero[i])
            {
                result->A[nonzeros_count] = temp_values[i];
                result->IA[nonzeros_count] = i;
                nonzeros_count++;
            }
        }

        result->JA[j + 1] = nonzeros_count;
    }

    result->nonzeros = nonzeros_count;

    free(temp_values);
    free(is_nonzero);

    return result;
}

void multiply_dense_matrices(Matrix *matrixA, Matrix *matrixB, Matrix *result_matrix)
{
    result_matrix->rows = matrixA->rows;
    result_matrix->columns = matrixB->columns;

    result_matrix->data = (double **) malloc(result_matrix->rows * sizeof(double *));
    for (int i = 0; i < result_matrix->rows; ++i)
        result_matrix->data[i] = (double *) calloc(result_matrix->columns, sizeof(double));

    for (int i = 0; i < matrixA->rows; ++i)
        for (int j = 0; j < matrixB->columns; ++j)
        {
            result_matrix->data[i][j] = 0.0;
            for (int k = 0; k < matrixA->columns; ++k)
                result_matrix->data[i][j] += matrixA->data[i][k] * matrixB->data[k][j];
        }
}

void free_sparse_matrixA(SparseMatrixA *matrix)
{
    if (matrix == NULL)
        return;

    free(matrix->A);
    free(matrix->IA);
    free(matrix->JA);
    matrix->A = NULL;
    matrix->IA = NULL;
    matrix->JA = NULL;
    matrix->nonzeros = 0;
    matrix->rows = 0;
    matrix->cols = 0;
}

void free_sparse_matrixB(SparseMatrixB *matrix)
{
    if (matrix == NULL)
        return;

    free(matrix->B);
    free(matrix->JB);
    free(matrix->IB);
    matrix->B = NULL;
    matrix->JB = NULL;
    matrix->IB = NULL;
    matrix->nonzeros = 0;
    matrix->rows = 0;
    matrix->cols = 0;
}

void free_matrix(Matrix *matrix)
{
    if (matrix == NULL)
        return;

    for (int i = 0; i < matrix->rows; ++i)
        free(matrix->data[i]);

    free(matrix->data);
    matrix->data = NULL;
    matrix->rows = 0;
    matrix->columns = 0;
    matrix->nonzeros = 0;
}
