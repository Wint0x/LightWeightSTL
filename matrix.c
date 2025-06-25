#include "matrix.h"
#include <stdlib.h>
#include <stddef.h>

#define CHECK(cond,code) do{ if(!(cond)) return (code);}while(0)

// Init
void matrix_create(size_t rows, size_t cols)
{
    Matrix *m = malloc(sizeof *m);
    if (!m) return NULL;

    m->data = calloc(rows * cols, sizeof(double));
    if (!m->data) { free(m); return NULL; }

    m->rows = rows;
    m->cols = cols;
    return m;
}

// Operations
int matrix_add(Matrix *dst,const Matrix *a, const Matrix *b)
{
    CHECK(dst && a && b,         -1);
    CHECK(a->rows==b->rows && a->cols==b->cols, -2);
    CHECK(dst->rows==a->rows && dst->cols==a->cols,-2);

    size_t n = a->rows * a->cols;
    for (size_t i=0;i<n;++i)
        dst->data[i] = a->data[i] + b->data[i];
    return 0;
}

/* ---- Scale: dst = k * src ---- */
int matrix_scale(Matrix *dst,const Matrix *src,double k)
{
    CHECK(dst && src,        -1);
    CHECK(dst->rows==src->rows && dst->cols==src->cols, -2);

    size_t n = src->rows * src->cols;
    for (size_t i=0;i<n;++i)
        dst->data[i] = k * src->data[i];
    return 0;
}

/* ---- Transpose: dst = srcᵀ ---- */
int matrix_transpose(Matrix *dst,const Matrix *src)
{
    CHECK(dst && src, -1);
    CHECK(dst->rows==src->cols && dst->cols==src->rows, -2);

    for (size_t r=0;r<src->rows;++r)
        for (size_t c=0;c<src->cols;++c)
            matrix_set(dst,c,r, matrix_get(src,r,c));
    return 0;
}

/* ---- 1-D dot product ---- */
double dot(const double *x,const double *y,size_t n)
{
    double sum = 0.0;
    for (size_t i=0;i<n;++i) sum += x[i]*y[i];
    return sum;
}

/* ---- Matrix multiply: dst = a × b ---- */
int matrix_mul(Matrix *dst,const Matrix *a,const Matrix *b)
{
    CHECK(dst && a && b, -1);
    CHECK(a->cols==b->rows,                       -2);
    CHECK(dst->rows==a->rows && dst->cols==b->cols,-2);

    /* zero dst first */
    memset(dst->data, 0, dst->rows*dst->cols*sizeof *dst->data);

    for (size_t i=0;i<a->rows;++i)
        for (size_t k=0;k<a->cols;++k) {
            double aik = matrix_get(a,i,k);
            for (size_t j=0;j<b->cols;++j)
                dst->data[i*dst->stride + j] += aik * matrix_get(b,k,j);
        }
    return 0;
}

/* ---- Apply element-wise: dst[i] = f(src[i]) ---- */
int matrix_apply(Matrix *dst,const Matrix *src,double (*f)(double))
{
    CHECK(dst && src && f, -1);
    CHECK(dst->rows==src->rows && dst->cols==src->cols, -2);

    size_t n = src->rows * src->cols;
    for (size_t i=0;i<n;++i)
        dst->data[i] = f(src->data[i]);
    return 0;
}

/* ---- Utility helpers (optional) ---- */
int matrix_fill(Matrix *matrix ,double v)
{
    CHECK(m, -1);
    size_t n = m->rows * m->cols;
    for (size_t i=0;i<n;++i) m->data[i] = v;
    return 0;
}
// Cleanup

void free_matrix(Matrix *matrix)
{
	if (!matrix || !matrix->data)
        return;

	free(matrix->data);
	matrix->data = NULL;
	
    free(matrix)
}