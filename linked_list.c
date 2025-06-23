#include <stddef.h>   // for size_t
#include <stdlib.h>   // for malloc, free
#include <string.h>   // for memcpy
#include "linked_list.h"

void init_list(LinkedList *list)
{
	list->root = NULL;
	list->size = 0;
}

void push_front(LinkedList *list, const void *value, size_t element_size)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->value = malloc(element_size);
    memcpy(new_node->value, value, element_size);

    new_node->next = list->root;
    list->root = new_node;
    list->size++;
}

void push_back(LinkedList *list, const void *value, size_t element_size)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node)
        return;

    new_node->value = malloc(element_size);
    if (!new_node->value) 
    {
        free(new_node);
        return;
    }

    memcpy(new_node->value, value, element_size);
    new_node->next = NULL;

    if (list->root == NULL) 
    {
        list->root = new_node;
    } 
    else 
    {
        Node *current = list->root;
        while (current->next != NULL)
            current = current->next;

        current->next = new_node;
    }

    list->size++;
}

void free_list(LinkedList *list)
{
	if (list->size == 0)
		return;

	Node *current = list->root;
	while (current != NULL)
	{
		Node *next = current->next;
		free(current->value);
		free(current);
		current = next;
	}	

	list->root = NULL;
	list->size = 0;
}

size_t list_size(const LinkedList *list)
{
	return list->size;
}