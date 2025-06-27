#include "matrix.h"
#include "ml.h"
#include "algorithm.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* tiny XOR-like dataset: 4 samples, 2->2 network */
    double X_raw[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double Y_raw[4][2] = {{1,0},{0,1},{0,1},{1,0}};

    Matrix *X = matrix_create(4,2);
    Matrix *Y = matrix_create(4,2);
    memcpy(X->data, X_raw, sizeof X_raw);
    memcpy(Y->data, Y_raw, sizeof Y_raw);

    Matrix *W = matrix_create(2,2);
    Matrix *b = matrix_create(1,2);
    matrix_fill(W, 0.5);   /* poor initial weights */
    matrix_fill(b, 0.0);

    Matrix *Yhat = matrix_create(4,2);
    Matrix *soft = matrix_create(4,2);
    Matrix *dY   = matrix_create(4,2);
    Matrix *dW   = matrix_create(2,2);
    Matrix *db   = matrix_create(1,2);
    Matrix *dX   = matrix_create(4,2);

    double lr = 0.1;
    for(int epoch=0;epoch<2000;++epoch){
        /* forward */
        ml_dense_forward(Yhat, X, W, b);
        ml_softmax_row(soft, Yhat);

        double loss = ml_ce_logit(Yhat, Y);
        if(epoch%400==0) printf("epoch %d  loss=%.4f\n",epoch,loss);

        /* backward */
        ml_ce_grad(dY, soft, Y);
        ml_dense_backward(dW, db, dX, dY, X, W);

        /* update */
        ml_sgd_update(W, dW, lr);
        ml_sgd_update(b, db, lr);
    }

    /* final predictions */
    ml_dense_forward(Yhat,X,W,b);
    ml_softmax_row(soft,Yhat);
    print_ndarray_matrix(soft);        /* from your previous helper */

    matrix_free(X);matrix_free(Y);matrix_free(W);matrix_free(b);
    matrix_free(Yhat);matrix_free(soft);matrix_free(dY);
    matrix_free(dW);matrix_free(db);matrix_free(dX);

    return 0;
}