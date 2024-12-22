#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#define EPS 1e-5

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

typedef struct
{
    double **data;
    int rows;
    int columns;
    int nonzeros;
} Matrix;

void generate_dense_matrix(Matrix *matrix, int rows, int cols, double density);
void input_dense_matrix(Matrix *matrix, int rows, int cols, int density);
void convert_matrix_to_sparse_matrixA(Matrix *matrix, SparseMatrixA *sparse_matrix);
void convert_matrix_to_sparse_matrixB(Matrix *matrix, SparseMatrixB *sparse_matrix);

void print_dense_matrix(const Matrix *matrix);
void print_sparse_matrixA(const SparseMatrixA *matrix);
void print_sparse_matrixB(const SparseMatrixB *matrix);

SparseMatrixA *multiply_sparse_matrices(const SparseMatrixA *matrixA, const SparseMatrixB *matrixB);
void multiply_dense_matrices(Matrix *matrixA, Matrix *matrixB, Matrix *result_matrix);

void free_sparse_matrixA(SparseMatrixA *matrix);
void free_sparse_matrixB(SparseMatrixB *matrix);
void free_matrix(Matrix *matrix);

#endif//LAB3_MATRIX_H
