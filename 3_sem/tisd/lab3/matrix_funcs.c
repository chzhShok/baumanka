#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "header.h"

int enter_first_matrix(int *A, int *IA, int *JA)
{
    int n, m;
    int ind_A = 0, last_col = -1;

    printf("Enter first matrix size (rows and columns): ");
    if (scanf("%d", &n) != 1 || scanf("%d", &m) != 1)
    {
        printf("ERROR: incorrect matrix dimensions\n");
        return IO_ERROR;
    }
    getchar();

    A = realloc(A, n * m * sizeof(int));
    IA = realloc(IA, n * m * sizeof(int));
    JA = realloc(JA, n * m * sizeof(int));
    if (!A || !IA || !JA)
    {
        printf("ERROR: memory allocation\n");
        return MEMORY_ERROR;
    }

    JA[0] = 0;

    int i, j;
    int element;
    while (1)
    {
        printf("Enter row and column of element (i, j): ");
        if (scanf("%d", &i) != 1 || scanf("%d", &j) != 1)
        {
            printf("ERROR: incorrect coordinates input\n");
            return IO_ERROR;
        }
        getchar();

        if (i == -1 || j == -1)
            break;

        if (i >= n || j >= m || i < 0 || j < 0)
        {
            printf("ERROR: coordinates out of bounds\n");
            continue;
        }

        printf("Enter element: ");
        if (scanf("%d", &element) != 1)
        {
            printf("ERROR: incorrect element\n");
            return IO_ERROR;
        }

        if (element != 0)
        {
            A[ind_A] = element;
            IA[ind_A] = i;
            ind_A++;
            if (j != last_col)
            {
                JA[j + 1] = ind_A;
                last_col = j;
            }
        }
    }

    for (int j = last_col + 1; j <= m; j++)
        JA[j] = ind_A;

    return OK;
}

int enter_second_matrix(int *B, int *IB, int *JB)
{
    int n, m;
    int ind_B = 0, last_row = -1;

    printf("Enter second matrix size (rows and columns): ");
    if (scanf("%d", &n) != 1 || scanf("%d", &m) != 1)
    {
        printf("ERROR: incorrect matrix dimensions\n");
        return IO_ERROR;
    }
    getchar();

    B = realloc(B, n * m * sizeof(int));
    IB = realloc(IB, n * m * sizeof(int));
    JB = realloc(JB, (n + 1) * sizeof(int));

    if (!B || !IB || !JB)
    {
        printf("ERROR: memory allocation\n");
        return MEMORY_ERROR;
    }

    JB[0] = 0;

    int i, j, element;
    while (1)
    {
        printf("Enter row and column of element (i, j) or (-1, -1 to stop): ");
        if (scanf("%d %d", &i, &j) != 2)
        {
            printf("ERROR: incorrect coordinates input\n");
            return IO_ERROR;
        }

        if (i == -1 || j == -1)
            break;

        if (i >= n || j >= m || i < 0 || j < 0)
        {
            printf("ERROR: coordinates out of bounds\n");
            continue;
        }

        printf("Enter element: ");
        if (scanf("%d", &element) != 1)
        {
            printf("ERROR: incorrect element input\n");
            return IO_ERROR;
        }

        if (element != 0)
        {
            B[ind_B] = element;
            IB[ind_B] = j;
            ind_B++;
            if (i != last_row)
            {
                JB[i + 1] = ind_B;
                last_row = i;
            }
        }
    }

    for (int i = last_row + 1; i <= n; i++)
        JB[i] = ind_B;

    return OK;
}

int read_matrix(FILE *f, int *A, int *IA, int *JA, int *B, int *IB, int *JB)
{

}