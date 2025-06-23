#include "algorithm.h"
#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "hash_map.h"
#include <stdio.h>

void transform_list(LinkedList *list, void (*func)(void *))
{
	if (!list || list->root == NULL)
		return;

	Node *current = list->root;
	while (current)
	{
		func(current->value);
		current = current->next;
	}
}

static void print_reverse_recursive(Node *node, void (*print_func)(void *)) 
{
	if (!node)
		return;

	print_reverse_recursive(node->next, print_func);
	print_func(node->value);
	putchar('\n');
}

void print_list(LinkedList *list, void (*print_func)(void *), int reverse)
{
	if (!list || list->root == NULL)
		return;

	Node *current = list->root;
	switch (reverse)
	{
	case 0:
		while (current)
		{
			print_func(current->value);
			putchar('\n');
			current = current->next;
		}
		break;
	default:
		print_reverse_recursive(list->root, print_func);
		break;
	}
}

LinkedList *filter_list(LinkedList *other, int(*filter_func)(void *), size_t element_size)
{
	if (!other || !filter_func)
		return NULL;

	LinkedList *result = malloc(sizeof(LinkedList));
	if (!result)
		return NULL;

	init_list(result);

	Node *current = other->root;
	while (current)
	{
		if (filter_func(current->value))
		{
			void *copy = malloc(element_size);

			memcpy(copy, current->value, element_size);
			push_back(result, copy, element_size);
		}

		current = current->next;
	}

	return result;
}
