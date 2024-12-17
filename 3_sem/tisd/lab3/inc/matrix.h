#ifndef LAB3_MATRIX_FUNCS_H
#define LAB3_MATRIX_FUNCS_H

typedef struct
{
    double *A;
    int *IA;
    int *JA;
    int nonzeros;
    int rows;
    int cols;
} SparseMatrixA;

typedef struct
{
    double *B;
    int *JB;
    int *IB;
    int nonzeros;
    int rows;
    int cols;
} SparseMatrixB;

#endif//LAB3_MATRIX_FUNCS_H
