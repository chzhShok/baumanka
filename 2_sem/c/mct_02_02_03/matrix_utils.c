#include "matrix_utils.h"

int find_second_max(int matrix[N][M], int n)
{

    int max = matrix[1][0];
    int second_max = matrix[2][0];
    int ind_second = 0;

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
        {
            if (matrix[i][j] > max)
            {
                second_max = max;
                max = matrix[i][j];
                ind_second = j;
            }
            else if (matrix[i][j] > second_max)
            {
                second_max = matrix[i][j];
                ind_second = j;
            }
        }

    return ind_second;
}

void delete_column(int matrix[N][M], int ind, int n)
{
    for (int j = ind; j < n - 1; j++)
        for (int i = 0; i < n; i++)
            matrix[i][j] = matrix[i][j + 1];
}

void print_matrix(int matrix[N][M], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}