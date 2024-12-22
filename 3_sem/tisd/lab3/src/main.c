#include <stdio.h>
#include <stdlib.h>

#include "efficiency.h"
#include "matrix.h"
#include "ui.h"

int main(void)
{
    int command;

    SparseMatrixA *sparse_matrixA = (SparseMatrixA *) malloc(sizeof(SparseMatrixA));
    SparseMatrixB *sparse_matrixB = (SparseMatrixB *) malloc(sizeof(SparseMatrixB));

    Matrix *matrixA = (Matrix *) malloc(sizeof(Matrix));
    Matrix *matrixB = (Matrix *) malloc(sizeof(Matrix));

    menu();

    while (1)
    {
        printf("\nВведите команду: ");
        if (scanf("%d", &command) != 1)
            command = 123;
        getchar();

        switch (command)
        {
            case 1:
            {
                int type;
                int rows, cols, density;

                printf("Задайте две матрицы\n");

                printf("Каким способом хотите задать первую матрицу?\n");
                printf("1. Задать случайно\n");
                printf("2. Ввести вручную\n");
                if (scanf("%d", &type) != 1 || type < 1 || type > 2)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                if (type == 1)
                {
                    printf("Введите количество строк, столбцов и процент заполнения (через пробел): \n");
                    if (scanf("%d %d %d", &rows, &cols, &density) != 3)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }

                    if (rows <= 0 || cols <= 0 || density < 0 || density > 100)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }

                    generate_dense_matrix(matrixA, rows, cols, density);
                    printf("Матрица успешно создана\n");
                }
                else
                {
                    printf("Введите количество строк, столбцов и количество ненулевых элементов (через пробел): \n");
                    if (scanf("%d %d %d", &rows, &cols, &density) != 3)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }

                    if (rows <= 0 || cols <= 0 || density < 0 || density > rows * cols)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }

                    input_dense_matrix(matrixA, rows, cols, density);
                    printf("Матрица успешно создана \n");
                }

                printf("Каким способом хотите задать вторую матрицу? \n");
                printf("1. Задать случайно \n");
                printf("2. Ввести вручную \n");
                if (scanf("%d", &type) != 1 || type < 1 || type > 2)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                if (type == 1)
                {
                    printf("Введите количество строк, столбцов и процент заполнения (через пробел): \n");
                    if (scanf("%d %d %d", &rows, &cols, &density) != 3)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }

                    if (rows <= 0 || cols <= 0 || density < 0 || density > 100)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }

                    generate_dense_matrix(matrixB, rows, cols, density);
                    printf("Матрица успешно создана\n");
                }
                else
                {
                    printf("Введите количество строк, столбцов и количество ненулевых элементов (через пробел): \n");
                    if (scanf("%d %d %d", &rows, &cols, &density) != 3)
                    {
                        printf("Ошибка ввода\n");
                        break;
                    }
                    input_dense_matrix(matrixB, rows, cols, density);
                    printf("Матрица успешно создана \n");
                }

                convert_matrix_to_sparse_matrixA(matrixA, sparse_matrixA);
                convert_matrix_to_sparse_matrixB(matrixB, sparse_matrixB);

                break;
            }
            case 2:
                if (matrixA != NULL && matrixB != NULL)
                {
                    print_dense_matrix(matrixA);
                    printf("\n");
                    print_dense_matrix(matrixB);
                }
                else
                {
                    printf("Ошибка: матрицы не введены\n");
                }

                break;
            case 3:
                printf("Матрица А\n");
                print_sparse_matrixA(sparse_matrixA);
                printf("\n");
                printf("Матрица B\n");
                print_sparse_matrixB(sparse_matrixB);

                break;
            case 4:
            {
                if (matrixA && matrixB)
                {
                    if (matrixA->columns != matrixB->rows)
                    {
                        printf("Ошибка: матрицы не могут быть перемножены\n");
                        break;
                    }
                }
                else
                {
                    printf("Ошибка: матрицы не могут быть перемножены\n");
                    break;
                }

                Matrix *result_matrix = (Matrix *) malloc(sizeof(Matrix));

                multiply_dense_matrices(matrixA, matrixB, result_matrix);
                print_dense_matrix(result_matrix);

                free_matrix(result_matrix);
                break;
            }
            case 5:
            {
                if (matrixA && matrixB)
                {
                    if (matrixA->columns != matrixB->rows)
                    {
                        printf("Ошибка: матрицы не могут быть перемножены\n");
                        break;
                    }
                }
                else
                {
                    printf("Ошибка: матрицы не могут быть перемножены\n");
                    break;
                }

                SparseMatrixA *result_matrix = multiply_sparse_matrices(sparse_matrixA, sparse_matrixB);

                print_sparse_matrixA(result_matrix);

                free_sparse_matrixA(result_matrix);
                break;
            }
            case 6:
                menu();
                break;
            case 7:
                measure_efficiency();
                break;
            case 0:
                free_matrix(matrixA);
                free_matrix(matrixB);
                free_sparse_matrixA(sparse_matrixA);
                free_sparse_matrixB(sparse_matrixB);
                return 0;
            case 123:
                printf("Неверная команда\n");
        }
    }
}
