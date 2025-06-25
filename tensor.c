#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "tensor.h"

/* ---------- helpers ---------- */
static inline size_t prod(const size_t *a, size_t n)
{
    size_t p = 1;
    for (size_t i=0;i<n;++i) p *= a[i];
    return p;
}

#define CHECK(cond,code) do{ if(!(cond)) return (code);}while(0)

/* ---------- creation ---------- */
Tensor *tensor_create(size_t ndim, const size_t *shape)
{   return tensor_zeros(ndim, shape); }

Tensor *tensor_zeros(size_t ndim, const size_t *shape)
{
    Tensor *t = calloc(1, sizeof *t);
    if (!t) return NULL;

    t->ndim = ndim;
    t->shape   = malloc(ndim*sizeof *t->shape);
    t->strides = malloc(ndim*sizeof *t->strides);
    if (!t->shape || !t->strides) { free(t->shape); free(t->strides); free(t); return NULL;}

    memcpy(t->shape, shape, ndim*sizeof *shape);

    /* contiguous row-major strides */
    t->strides[ndim-1] = 1;
    for (size_t d=ndim-1; d-- > 0; )
        t->strides[d] = t->strides[d+1] * shape[d+1];

    size_t n_elem = prod(shape, ndim);
    t->data = calloc(n_elem, sizeof *t->data);
    if (!t->data) { tensor_free(t); return NULL; }

    t->is_view = 0;
    return t;
}

/* ones and random */
Tensor *tensor_ones(size_t ndim, const size_t *shape)
{
    Tensor *t = tensor_zeros(ndim, shape);
    if (!t) return NULL;
    size_t n = prod(shape, ndim);
    for (size_t i=0;i<n;++i) t->data[i] = 1.0;
    return t;
}

static double rand01(void)   /* naïve LCG fallback */
{
    static unsigned s = 123456789;
    s = s*1103515245 + 12345;
    return (double)(s & 0xFFFFFF) / (double)0x1000000;
}
Tensor *tensor_randu(size_t ndim,const size_t *shape,double lo,double hi)
{
    Tensor *t = tensor_zeros(ndim, shape);
    if (!t) return NULL;
    double span = hi - lo;
    size_t n = prod(shape, ndim);
    for (size_t i=0;i<n;++i) t->data[i] = lo + span * rand01();
    return t;
}

/* view from external buffer */
Tensor *tensor_from_buffer(size_t ndim,const size_t *shape,
                           const size_t *strides,double *buf)
{
    Tensor *t = calloc(1,sizeof *t);
    if (!t) return NULL;
    t->ndim = ndim;
    t->shape   = malloc(ndim*sizeof *t->shape);
    t->strides = malloc(ndim*sizeof *t->strides);
    if (!t->shape || !t->strides){ tensor_free(t); return NULL; }
    memcpy(t->shape, shape, ndim*sizeof *shape);
    memcpy(t->strides,strides?strides:(size_t[1]){0}, ndim*sizeof *t->strides);

    /* if strides not provided assume contiguous */
    if (!strides) {
        t->strides[ndim-1]=1;
        for (size_t d=ndim-1; d-- > 0;)
            t->strides[d]=t->strides[d+1]*shape[d+1];
    }
    t->data    = buf;
    t->is_view = 1;
    return t;
}

void tensor_free(Tensor *t)
{
    if (!t) return;
    if (!t->is_view) free(t->data);
    free(t->shape);
    free(t->strides);
    free(t);
}

/* ---------- element-wise ops (contiguous-only v1) ---------- */
int tensor_fill(Tensor *dst,double v)
{
    CHECK(dst, -1);
    size_t n = prod(dst->shape, dst->ndim);
    for (size_t i=0;i<n;++i) dst->data[i]=v;
    return 0;
}

static int same_shape(const Tensor *a,const Tensor *b)
{
    if (a->ndim!=b->ndim) return 0;
    for (size_t d=0;d<a->ndim;++d)
        if (a->shape[d]!=b->shape[d]) return 0;
    return 1;
}

int tensor_add(Tensor *dst,const Tensor *a,const Tensor *b)
{
    CHECK(dst && a && b, -1);
    CHECK(same_shape(a,b)&&same_shape(a,dst), -2);
    size_t n = prod(a->shape,a->ndim);
    for (size_t i=0;i<n;++i) dst->data[i] = a->data[i] + b->data[i];
    return 0;
}

int tensor_scale(Tensor *dst,const Tensor *src,double k)
{
    CHECK(dst && src, -1);
    CHECK(same_shape(dst,src), -2);
    size_t n = prod(src->shape, src->ndim);
    for (size_t i=0;i<n;++i) dst->data[i] = k * src->data[i];
    return 0;
}

int tensor_apply(Tensor *dst,const Tensor *src,double (*f)(double))
{
    CHECK(dst && src && f, -1);
    CHECK(same_shape(dst,src), -2);
    size_t n = prod(src->shape, src->ndim);
    for (size_t i=0;i<n;++i) dst->data[i] = f(src->data[i]);
    return 0;
}

/* ---------- simple reductions ---------- */
int tensor_sum(Tensor *dst,const Tensor *src)
{
    CHECK(dst && src, -1);
    CHECK(dst->ndim==1 && dst->shape[0]==1, -2);
    double s=0.0;
    size_t n = prod(src->shape, src->ndim);
    for(size_t i=0;i<n;++i) s += src->data[i];
    dst->data[0]=s;
    return 0;
}

int tensor_mean(Tensor *dst,const Tensor *src)
{
    CHECK(dst && src, -1);
    CHECK(dst->ndim==1 && dst->shape[0]==1, -2);
    double s=0.0;
    size_t n = prod(src->shape, src->ndim);
    for(size_t i=0;i<n;++i) s += src->data[i];
    dst->data[0]= s / (double)n;
    return 0;
}

/* ---------- reshape & permute (views) ---------- */
int tensor_reshape(Tensor *view,const Tensor *src,
                   size_t ndim,const size_t *new_shape)
{
    CHECK(view && src && new_shape, -1);
    size_t new_elems = prod(new_shape, ndim);
    size_t old_elems = prod(src->shape, src->ndim);
    CHECK(new_elems==old_elems, -2);

    *view = *src;                   /* shallow copy struct */
    view->ndim = ndim;
    view->shape   = malloc(ndim*sizeof *view->shape);
    view->strides = malloc(ndim*sizeof *view->strides);
    if(!view->shape||!view->strides){ tensor_free(view); return -3; }

    /* contiguous reshape keeps row-major order */
    memcpy(view->shape,new_shape,ndim*sizeof *new_shape);
    view->strides[ndim-1]=1;
    for(size_t d=ndim-1; d-- >0;)
        view->strides[d]=view->strides[d+1]*new_shape[d+1];
    view->is_view = 1;
    return 0;
}

int tensor_permute(Tensor *view,const Tensor *src,const size_t *axes)
{
    CHECK(view && src && axes, -1);
    *view = *src;
    size_t ndim = src->ndim;
    view->shape   = malloc(ndim*sizeof *view->shape);
    view->strides = malloc(ndim*sizeof *view->strides);
    if(!view->shape||!view->strides){ tensor_free(view); return -3; }

    for(size_t d=0; d<ndim; ++d) {
        size_t ax = axes[d];
        CHECK(ax < ndim, -2);
        view->shape[d]   = src->shape[ax];
        view->strides[d] = src->strides[ax];
    }
    view->is_view = 1;
    return 0;
}

/* ---------- debug print (first few elements) ---------- */
void tensor_print_slice(const Tensor *t,size_t max_elems)
{
    if(!t){ puts("(null)"); return; }
    size_t total = prod(t->shape, t->ndim);
    printf("[");
    for(size_t i=0;i< (total<max_elems?total:max_elems); ++i)
        printf("%g%s", t->data[i], (i+1<total && i+1<max_elems)?", ":"");
    if(total>max_elems) printf(", …");
    printf("]\n");
}