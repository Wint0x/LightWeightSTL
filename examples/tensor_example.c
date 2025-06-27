#include "tensor.h"
#include "mathlib.h"  
#include "algorithm.h"      /* for sin */
#include <stdio.h>
int main(void)
{
    const size_t shape[3] = {2,3,4};          /* e.g. N=2, H=3, W=4 */
    Tensor *x = tensor_randu(3, shape, 0.0, 1.0);
    Tensor *y = tensor_zeros(3, shape);

    tensor_scale(y, x, 10.0);                 /* y = 10 * x         */
    tensor_apply(y, y, &my_sin);                 /* y = sin(y)         */

    tensor_print_slice(y, 8);

    size_t one = 1;
	Tensor *sum = tensor_zeros(1, &one);      /* heap-allocated scalar tensor */
	tensor_sum(sum, y);
	
	print_tensor(sum);

    tensor_free(x); tensor_free(y); tensor_free(sum);
}