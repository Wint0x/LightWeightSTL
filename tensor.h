#ifndef TENSOR_H
#define TENSOR_H

#include <stddef.h>   /* size_t */

/* -------- data structure -------- */
typedef struct {
    size_t   ndim;        /* number of dimensions                    */
    size_t  *shape;       /* length ndim                             */
    size_t  *strides;     /* length ndim, in elements, not bytes     */
    double  *data;        /* contiguous unless strides[i] != prod    */
    int      is_view;     /* 0 = owns data, 1 = view                 */
} Tensor;

/* -------- construction -------- */
Tensor *tensor_create(size_t ndim, const size_t *shape);   /* zeros */
Tensor *tensor_zeros (size_t ndim, const size_t *shape);   /* alias */
Tensor *tensor_ones  (size_t ndim, const size_t *shape);
Tensor *tensor_randu (size_t ndim, const size_t *shape, double lo, double hi);
Tensor *tensor_from_buffer(size_t ndim, const size_t *shape,
                           const size_t *strides, double *buf);     /* view   */
void     tensor_free(Tensor *t);

/* -------- fast access (inline, no bounds check) -------- */
static inline size_t tensor_offset(const Tensor *t, const size_t *idx)
{
    size_t off = 0;
    for (size_t d = 0; d < t->ndim; ++d) off += idx[d] * t->strides[d];
    return off;
}
static inline double tensor_get(const Tensor *t, const size_t *idx)
{   return t->data[tensor_offset(t, idx)]; }

static inline void   tensor_set(Tensor *t, const size_t *idx, double v)
{   t->data[tensor_offset(t, idx)] = v; }

/* -------- basic ops (contiguous-only for v1) -------- */
int tensor_fill (Tensor *dst, double v);                        /* dst[:] = v           */
int tensor_add  (Tensor *dst, const Tensor *a, const Tensor *b);/* dst = a + b          */
int tensor_scale(Tensor *dst, const Tensor *src, double k);      /* dst = k * src        */
int tensor_apply(Tensor *dst, const Tensor *src,
                 double (*f)(double));                           /* element-wise f       */

/* reductions */
int tensor_sum (Tensor *dst /*scalar 1-D*/, const Tensor *src);
int tensor_mean(Tensor *dst /*scalar 1-D*/, const Tensor *src);

/* reshape & permute */
int tensor_reshape(Tensor *view, const Tensor *src,
                   size_t ndim, const size_t *new_shape);        /* shares data         */
int tensor_permute(Tensor *view, const Tensor *src,
                   const size_t *axes /*len = ndim*/);           /* arbitrary transpose */

/* debugging */
void tensor_print_slice(const Tensor *t, size_t max_elems);

#endif /* TENSOR_H */