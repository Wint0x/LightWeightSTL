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