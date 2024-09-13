#include "matrix_utils.h"
#include <stdio.h>


int main(void)
{
    int n;
    printf("Enter n\n");
    if (scanf("%d", &n) != 1)
        return IO_ERROR;
    if (n < 3)
        return INPUT_ERROR;

    int m;
    printf("Enter m\n");
    if (scanf("%d", &m) != 1)
        return IO_ERROR;
    if (m < 3)
        return INPUT_ERROR;

    if (n != m)
        return INPUT_ERROR;

    int matrix[N][M];
    printf("Enter matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    int ind_second = find_second_max(matrix, n);
    printf("%d\n", ind_second);
    delete_column(matrix, ind_second, n);
    m -= 1;
    print_matrix(matrix, n, m);

    return 0;
}