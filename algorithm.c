#include "algorithm.h"
#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "hash_map.h"
#include "matrix.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Printing Data Structures
static void print_reverse_recursive(Node *node, void (*print_func)(void *)) 
{
	if (!node)
		return;

	print_reverse_recursive(node->next, print_func);
	print_func(node->value);
	putchar('\n');
}

void print_list(const LinkedList *list, void (*print_func)(void *), int reverse)
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

void print_matrix(const Matrix *matrix)
{
    if (!matrix || !matrix->data || matrix->rows == 0 || matrix->cols == 0)
        return;

    for (size_t row = 0; row < matrix->rows; ++row)
    {
        for (size_t col = 0; col < matrix->cols; ++col)
        {
            printf("%6.2f\t", matrix->data[row * matrix->cols + col]);
        }
        putchar('\n');
    }
}

static void print_tree_node(TreeNode *node, void (*print_value)(void *), int depth)
{
    if (!node) return;

    print_tree_node(node->right, print_value, depth + 1);

    for (int i = 0; i < depth; ++i)
        printf("    ");  // 4 spaces per level of depth

    print_value(node->value);
    putchar('\n');

    print_tree_node(node->left, print_value, depth + 1);
}

void print_tree(Tree *tree, void (*print_value)(void *))
{
    if (!tree || !tree->root || !print_value) return;
    print_tree_node(tree->root, print_value, 0);
}

// Transformation
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
