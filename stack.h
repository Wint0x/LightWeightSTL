#ifndef H_STACK
#define H_STACK

#include <stddef.h>  // for size_t

typedef struct Stack
{
	void *content;
	size_t size;
	size_t max_size;
	size_t element_size;
} Stack;

void init_stack(Stack *stack, size_t max_size, size_t element_size);
void push(Stack *stack, const void *element);
void *pop(Stack *stack);
void free_stack(Stack *stack);
int is_empty(const Stack *stack);
const void *peek(const Stack *stack);

#endif