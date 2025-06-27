#include <math.h>
#include <string.h>      /* memset */
#include "ml.h"
#include "matrix.h"

/* Helper to broadcast scalar into tmp buf */
static inline void scalar_fill(double *dst, size_t n, double v)
{ for (size_t i=0;i<n;++i) dst[i]=v; }

/* ───────────── Activations ───────────── */

#define CHECK(cond,code) do{ if(!(cond)) return (code);}while(0)

int ml_sigmoid(Matrix *dst,const Matrix *src)
{
    CHECK(dst && src,-1);
    CHECK(dst->rows==src->rows && dst->cols==src->cols,-2);
    size_t n = src->rows*src->cols;
    for(size_t i=0;i<n;++i)
        dst->data[i] = 1.0 / (1.0 + exp(-src->data[i]));
    return 0;
}

int ml_dsigmoid(Matrix *dst,const Matrix *sig)
{
    CHECK(dst && sig,-1);
    CHECK(dst->rows==sig->rows && dst->cols==sig->cols,-2);
    size_t n=sig->rows*sig->cols;
    for(size_t i=0;i<n;++i){
        double s=sig->data[i];
        dst->data[i]=s*(1.0-s);
    }
    return 0;
}

int ml_relu(Matrix *dst,const Matrix *src)
{
    CHECK(dst&&src,-1);
    CHECK(dst->rows==src->rows&&dst->cols==src->cols,-2);
    size_t n=src->rows*src->cols;
    for(size_t i=0;i<n;++i)
        dst->data[i]=src->data[i]>0?src->data[i]:0.0;
    return 0;
}

int ml_drelu(Matrix *dst,const Matrix *src)
{
    CHECK(dst&&src,-1);
    CHECK(dst->rows==src->rows&&dst->cols==src->cols,-2);
    size_t n=src->rows*src->cols;
    for(size_t i=0;i<n;++i)
        dst->data[i]=src->data[i]>0?1.0:0.0;
    return 0;
}

int ml_tanh(Matrix *dst,const Matrix *src)
{
    CHECK(dst&&src,-1);
    CHECK(dst->rows==src->rows&&dst->cols==src->cols,-2);
    size_t n=src->rows*src->cols;
    for(size_t i=0;i<n;++i)
        dst->data[i]=tanh(src->data[i]);
    return 0;
}

int ml_dtanh(Matrix *dst,const Matrix *tout)
{
    CHECK(dst&&tout,-1);
    CHECK(dst->rows==tout->rows&&dst->cols==tout->cols,-2);
    size_t n=tout->rows*tout->cols;
    for(size_t i=0;i<n;++i){
        double t=tout->data[i];
        dst->data[i]=1.0-t*t;
    }
    return 0;
}

/* Softmax across each row (batch) */
int ml_softmax_row(Matrix *dst,const Matrix *src)
{
    CHECK(dst&&src,-1);
    CHECK(dst->rows==src->rows&&dst->cols==src->cols,-2);

    for(size_t r=0;r<src->rows;++r){
        /* find max for numerical stability */
        double maxv=-1e30;
        for(size_t c=0;c<src->cols;++c){
            double v = matrix_get(src,r,c);
            if(v>maxv) maxv=v;
        }
        /* exponentiate & sum */
        double sum=0.0;
        for(size_t c=0;c<src->cols;++c){
            double e = exp(matrix_get(src,r,c)-maxv);
            matrix_set(dst,r,c,e);
            sum += e;
        }
        /* normalize */
        for(size_t c=0;c<src->cols;++c){
            double v = matrix_get(dst,r,c)/sum;
            matrix_set(dst,r,c,v);
        }
    }
    return 0;
}

/* ───────────── Losses ───────────── */

double ml_mse(const Matrix *pred,const Matrix *tgt)
{
    size_t n=pred->rows*pred->cols;
    double acc=0.0;
    for(size_t i=0;i<n;++i){
        double d = pred->data[i]-tgt->data[i];
        acc += d*d;
    }
    return acc / (double)n;
}

int ml_mse_grad(Matrix *grad,const Matrix *pred,const Matrix *tgt)
{
    CHECK(grad&&pred&&tgt,-1);
    CHECK(grad->rows==pred->rows&&grad->cols==pred->cols,-2);
    size_t n=pred->rows*pred->cols;
    double scale = 2.0/(double)n;
    for(size_t i=0;i<n;++i)
        grad->data[i] = scale*(pred->data[i]-tgt->data[i]);
    return 0;
}

/* Cross-entropy with logits + one-hot labels */
double ml_ce_logit(const Matrix *logits,const Matrix *labels)
{
    Matrix *sm = matrix_create(logits->rows, logits->cols);
    ml_softmax_row(sm, logits);

    double loss=0.0;
    for(size_t r=0;r<logits->rows;++r)
        for(size_t c=0;c<logits->cols;++c){
            double y = matrix_get(labels,r,c);
            double p = matrix_get(sm,r,c);
            loss -= y * log(fmax(p,1e-12));
        }
    matrix_free(sm);
    return loss / (double)logits->rows;
}

int ml_ce_grad(Matrix *grad,const Matrix *softmax_out,const Matrix *labels)
{
    CHECK(grad&&softmax_out&&labels,-1);
    CHECK(grad->rows==softmax_out->rows&&grad->cols==softmax_out->cols,-2);

    size_t n=softmax_out->rows*softmax_out->cols;
    for(size_t i=0;i<n;++i)
        grad->data[i] = (softmax_out->data[i]-labels->data[i])
                        / (double)softmax_out->rows;  /* average across batch */
    return 0;
}

/* ───────────── Dense layer ───────────── */

int ml_dense_forward(Matrix *Y,const Matrix *X,
                     const Matrix *W,const Matrix *b)
{
    /* Y = X W + b */
    int rc = matrix_mul(Y, X, W); if(rc) return rc;
    /* broadcast-add bias row */
    for(size_t r=0;r<Y->rows;++r)
        for(size_t c=0;c<Y->cols;++c)
            matrix_set(Y,r,c, matrix_get(Y,r,c)+matrix_get(b,0,c));
    return 0;
}

int ml_dense_backward(Matrix *dW,Matrix *db,Matrix *dX,
                      const Matrix *dY,
                      const Matrix *X,const Matrix *W)
{
    /* dW = Xᵀ dY */
    Matrix *XT = matrix_create(X->cols, X->rows);
    matrix_transpose(XT,X);
    matrix_mul(dW, XT, dY);
    matrix_free(XT);

    /* db = sum_rows(dY) */
    for(size_t c=0;c<dY->cols;++c){
        double s=0.0;
        for(size_t r=0;r<dY->rows;++r) s += matrix_get(dY,r,c);
        matrix_set(db,0,c,s);
    }

    /* dX = dY Wᵀ */
    Matrix *WT = matrix_create(W->cols, W->rows);
    matrix_transpose(WT,W);
    matrix_mul(dX, dY, WT);
    matrix_free(WT);
    return 0;
}

/* ───────────── SGD update ───────────── */
int ml_sgd_update(Matrix *param,const Matrix *grad,double lr)
{
    CHECK(param&&grad,-1);
    CHECK(param->rows==grad->rows&&param->cols==grad->cols,-2);
    size_t n=param->rows*param->cols;
    for(size_t i=0;i<n;++i)
        param->data[i] -= lr*grad->data[i];
    return 0;
}