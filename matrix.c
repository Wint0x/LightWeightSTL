#include "matrix.h"
#include <stdlib.h>
#include <stddef.h>

void init_matrix(Matrix **matrix, size_t rows, size_t cols)
{
    *matrix = malloc(sizeof(Matrix));
    (*matrix)->rows = rows;
    (*matrix)->cols = cols;
    (*matrix)->data = calloc(rows * cols, sizeof(double));
}

void set_matrix_element(Matrix *matrix, size_t row, size_t col, double value)
{
    if (!matrix || !matrix->data || row >= matrix->rows || col >= matrix->cols)
        return;

    matrix->data[row * matrix->cols + col] = value;
}

double get_matrix_element(const Matrix *matrix, size_t row, size_t col)
{
    if (!matrix || !matrix->data || row >= matrix->rows || col >= matrix->cols)
        return 0.0;  // or NAN if <math.h> is included

    return matrix->data[row * matrix->cols + col];
}


void free_matrix(Matrix *matrix)
{
	if (!matrix || !matrix->data)
        return;

	free(matrix->data);
	matrix->data = NULL;
	matrix->rows = 0;
	matrix->cols = 0;
}