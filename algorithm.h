#ifndef H_ALGORITHM
#define H_ALGORITHM

#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "hash_map.h"

void transform_list(LinkedList *list, void (*func)(void *));
void print_list(LinkedList *list, void (*print_func)(void *), int reverse);

#endif