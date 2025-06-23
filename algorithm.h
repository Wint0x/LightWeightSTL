#ifndef H_ALGORITHM
#define H_ALGORITHM

#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "hash_map.h"
#include "matrix.h"
#include <stddef.h>


void print_list(const LinkedList *list, void (*print_func)(void *), int reverse);
void print_matrix(const Matrix *matrix);
void transform_list(LinkedList *list, void (*func)(void *));
LinkedList *filter_list(LinkedList *other, int(*filter_func)(void *), size_t element_size);
#endif