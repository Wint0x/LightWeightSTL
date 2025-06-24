#ifndef H_ALGORITHM
#define H_ALGORITHM

#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "hash_map.h"
#include "matrix.h"
#include "tree.h"
#include <stddef.h>
#include <stdio.h>

// Printing Helper
static inline void print_int(void *value)
{
    printf("%d\n", *(int *)value);
}

static inline void print_float(void *value)
{
    printf("%f\n", *(float *)value);
}

static inline void print_str(void *value)
{
    printf("%s\n",(char *) value);
}
// Printing
void print_list(const LinkedList *list, void (*print_func)(void *), int reverse);
void print_matrix(const Matrix *matrix);
void print_tree(Tree *tree, void (*print_value)(void *));
// Transformation / Filtering
void transform_list(LinkedList *list, void (*func)(void *));
LinkedList *filter_list(LinkedList *other, int(*filter_func)(void *), size_t element_size);

#endif