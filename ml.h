#ifndef H_ML
#define H_ML

#include "tensor.h"
#include "matrix.h"

/* ─────────── Activations ─────────── */
int ml_sigmoid      (Matrix *dst, const Matrix *src);               /* dst = σ(src)           */
int ml_dsigmoid     (Matrix *dst, const Matrix *sigmoid_out);       /* element-wise derivative*/
int ml_relu         (Matrix *dst, const Matrix *src);
int ml_drelu        (Matrix *dst, const Matrix *src);
int ml_tanh         (Matrix *dst, const Matrix *src);
int ml_dtanh        (Matrix *dst, const Matrix *tanh_out);
int ml_softmax_row  (Matrix *dst, const Matrix *src);               /* softmax across cols    */

/* ─────────── Losses (forward + grad) ─────────── */
/* All expect shape (batch, classes) or (batch, 1) */
double ml_mse         (const Matrix *pred, const Matrix *target);
int    ml_mse_grad    (Matrix *grad, const Matrix *pred,
                       const Matrix *target);
double ml_ce_logit    (const Matrix *logits, const Matrix *labels); /* cross-entropy */
int    ml_ce_grad     (Matrix *grad, const Matrix *softmax_out,
                       const Matrix *labels);

/* ─────────── Linear (Dense) layer ─────────── */
/* Forward:  y = X W + b  (shapes: X=BxD, W=DxO, b=1xO, y=BxO)        */
int ml_dense_forward  (Matrix *y, const Matrix *X,
                       const Matrix *W, const Matrix *b);

/* Backward: given dL/dy, compute grads                              
   dL/dW, dL/db, dL/dX  */
int ml_dense_backward (Matrix *dW, Matrix *db, Matrix *dX,
                       const Matrix *dY,
                       const Matrix *X, const Matrix *W);

/* ─────────── Optimiser: SGD ─────────── */
int ml_sgd_update(Matrix *param, const Matrix *grad, double lr);

#endif