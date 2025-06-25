#include "algorithm.h"
#include "linked_list.h"
#include "queue.h"
#include "stack.h"
#include "hash_map.h"
#include "matrix.h"
#include "tree.h"
#include "graph.h"
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

void print_graph(const Graph *graph) 
{
   	for (size_t v = 0; v < graph->num_vertices; ++v) 
   	{
        printf("%zu:", v);
        GraphNode* temp = graph->adj_lists[v];
        while (temp) 
        {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        putchar('\n');
    }
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


/* GRAPH ALGORITHMS */
void dfs_graph(const Graph *graph, int start_vertex, void (*visit)(int)) 
{
    if (!graph || start_vertex >= graph->num_vertices) return;

    bool *visited = calloc(graph->num_vertices, sizeof(bool));
    Stack stack;
    init_stack(&stack, graph->num_vertices, sizeof(int));

    push(&stack, &start_vertex);

    while (!is_empty(&stack)) 
    {
        int *v_ptr = pop(&stack);
        if (!v_ptr) break;
        int v = *v_ptr;
        free(v_ptr);

        if (!visited[v]) {
            visit(v);
            visited[v] = true;

            GraphNode *neighbors = get_neighbors(graph, v);
            while (neighbors) {
                if (!visited[neighbors->vertex])
                    push(&stack, &neighbors->vertex);
                neighbors = neighbors->next;
            }
        }
    }

    free_stack(&stack);
    free(visited);
}

void bfs_graph(const Graph *graph,
               int start_vertex,
               void (*visit)(int))
{
    if (!graph || start_vertex >= (int)graph->num_vertices || !visit)
        return;

    /* book-keeping */
    bool *visited = calloc(graph->num_vertices, sizeof(bool));
    if (!visited) return;

    /* generic queue< int > */
    Queue q;
    init_queue(&q);                         /* queue uses dynamic nodes */

    enqueue(&q, &start_vertex, sizeof(int));
    visited[start_vertex] = true;

    while (!is_queue_empty(&q))
    {
        int *v_ptr = (int *)dequeue(&q);
        if (!v_ptr) break;                  /* safety */

        int v = *v_ptr;
        free(v_ptr);

        visit(v);                           /* user-supplied callback */

        /* push all unvisited neighbours */
        GraphNode *nbr = get_neighbors(graph, v);
        while (nbr)
        {
            int w = nbr->vertex;
            if (!visited[w])
            {
                enqueue(&q, &w, sizeof(int));
                visited[w] = true;
            }
            nbr = nbr->next;
        }
    }

    free_queue(&q);
    free(visited);
}
