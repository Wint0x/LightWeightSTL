#ifndef H_MATRIX
#define H_MATRIX

#include <stddef.h>

typedef struct Matrix 
{
    size_t rows;
    size_t cols;
    double *data;  // contiguous block of rows * cols
} Matrix;

void init_matrix(Matrix **matrix, size_t rows, size_t cols);
void set_matrix_element(Matrix *matrix, size_t row, size_t col, double value);
double get_matrix_element(const Matrix *matrix, size_t row, size_t col);

static inline size_t get_matrix_rows(const Matrix *matrix) 
{
	if (!matrix) return 0;
	return matrix->rows;
}

static inline size_t get_matrix_cols(const Matrix *matrix) 
{
	if (!matrix) return 0;
	return matrix->cols;
}
void free_matrix(Matrix *matrix);

#endif