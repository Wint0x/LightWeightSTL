#ifndef H_MATRIX
#define H_MATRIX

#include <stddef.h>

typedef struct Matrix 
{
    size_t rows, cols;
    size_t stride;
    double *data;  // contiguous block of rows * cols
} Matrix;

// Create
void matrix_create(size_t rows, size_t cols);

// Get Set
static inline double matrix_get(const Matrix *matrix, size_t r, size_t c)
{
    return matrix->data[r * matrix->cols + c];
}
static inline void matrix_set(Matrix *matrix, size_t r, size_t c, double v)
{
    matrix->data[r * matrix->cols + c] = v;
}

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


// Operations
int matrix_add(Matrix *dst,const Matrix *a,const Matrix *b);
int matrix_scale(Matrix *dst,const Matrix *src,double k);
int matrix_mul(Matrix *dst,const Matrix *a,const Matrix *b);
int matrix_transpose(Matrix *dst,const Matrix *src);
double dot(const double *x,const double *y,size_t n);
int matrix_apply(Matrix *dst,const Matrix *src,double (*f)(double));

// QoL
void matrix_fill(Matrix *matrix, double value);
int matrix_random_uniform(Matrix *matrix, double lo, double hi);
void matrix_print(const Matrix *matrix,const char *fmt);
double matrix_mean(const Matrix *matrix);

// Cleanup
void free_matrix(Matrix *matrix);

#endif