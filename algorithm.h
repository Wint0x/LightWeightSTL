#ifndef H_ALGORITHM
#define H_ALGORITHM

#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "hash_map.h"
#include "matrix.h"
#include "tree.h"
#include "graph.h"
#include "tensor.h"
#include <stddef.h>
#include <stdio.h>

#define print_int(val)    printf("%d\n", val)
#define print_float(val)  printf("%f\n", val)
#define print_double(val) printf("%lf\n", val)
#define print_str(val)    printf("%s\n", val)
#define print_char(val)   printf("%c\n", val)

// Simple Swap
static inline int my_swap(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// Printing Helper
static inline int ensure_valid_int(int *num_to_convert)
{
    char term;
    printf("Enter your number: ");
    if(scanf("%d%c", num_to_convert, &term) != 2 || term != '\n')
    {
        fprintf(stderr, "Invalid Number\n");
        return -1;
    }   

    return 0;
}

static inline void print_int_ptr(void *value)
{
    printf("%d\n", *(int *)value);
}

static inline void print_float_ptr(void *value)
{
    printf("%f\n", *(float *)value);
}

static inline void print_double_ptr(void *value)
{
    printf("%lf\n", *(double *)value);
}

static inline void print_str_ptr(void *value)
{
    printf("%s\n",(char *) value);
}
// Printing
void print_list(const LinkedList *list, void (*print_func)(void *), int reverse);
void print_matrix(const Matrix *matrix);
void print_tree(Tree *tree, void (*print_value)(void *));
void print_graph(const Graph *graph);

void print_tensor(const Tensor *t);
// Transformation / Filtering
void transform_list(LinkedList *list, void (*func)(void *));
LinkedList *filter_list(LinkedList *other, int(*filter_func)(void *), size_t element_size);

/* GRAPH ALGORITHMS */
void dfs_graph(const Graph *graph, int start_vertex, void (*visit)(int ));
/* Breadth-first search (level-order) */
void bfs_graph(const Graph *graph,
               int start_vertex,
               void (*visit)(int));

#endif