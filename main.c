#include "algorithm.h"      /* for sin */
#include <stdio.h>

int main(void)
{
    int a, b;

    a = 1; b = 2;

    my_swap(&a, &b);

    printf("a = %d\nb = %d\n", a, b);    
    return 0;
}