#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "matrix.h"
#include <stddef.h>


int main(void)
{
	Matrix *m;
	init_matrix(&m, 10, 10);

	double value = 1;
	for (int row = 0; row < 10; ++row)
		for (int col = 0; col < 10; ++col)
		{
				set_matrix_element(m, row, col, value);
				value += .5f;
		}

	print_matrix(m);
	free_matrix(m);

	return 0;
}