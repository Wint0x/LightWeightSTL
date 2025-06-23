#ifndef H_LINKED_LIST
#define H_LINKED_LIST

#include <stddef.h> // size_t

typedef struct Node
{
	void *value;
	struct Node *next;
} Node;

typedef struct LinkedList
{
	Node *root;
	size_t size;
} LinkedList;

void init_list(LinkedList *list);
void push_front(LinkedList *list, const void *value, size_t element_size);
void push_back(LinkedList *list, const void *value, size_t element_size);
void free_list(LinkedList *list);
size_t list_size(const LinkedList *list);

#endif