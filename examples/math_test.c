#include "mathlib.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	Circle circle;
	circle.radius = 16.7;

	printf("%f\n", circle_area(&circle));
	return 0;
}
