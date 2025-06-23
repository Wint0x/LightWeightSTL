#include "stack.h"
#include <stdlib.h>
#include <string.h>

void init_stack(Stack *stack, size_t max_size, size_t element_size)
{
	stack->content = malloc(max_size * element_size);
	stack->size = 0;
	stack->max_size = max_size;
	stack->element_size = element_size;
}

void push(Stack *stack, const void *element)
{
	if (stack->size == stack->max_size)
		return;

	void *target = (char *)stack->content + (stack->size * stack->element_size);
    memcpy(target, element, stack->element_size);
    stack->size++;
}

void *pop(Stack *stack)
{
	if (stack->size == 0)
		return NULL;

	stack->size--;

	void *element = malloc(stack->element_size);

    if (!element)
        return NULL;  // handle allocation failure

   	void *source = (char *)stack->content + (stack->size * stack->element_size);
    memcpy(element, source, stack->element_size);

    return element;
}

void free_stack(Stack *stack)
{
    if (stack && stack->content) 
    {
        free(stack->content);
        stack->content = NULL;
        stack->size = 0;
        stack->max_size = 0;
        stack->element_size = 0;  // if you're tracking element size
    }
}

int is_empty(const Stack *stack)
{
	return stack->size == 0;
}

const void *peek(const Stack *stack)
{
	if (stack->size == 0)
		return NULL;

	return (const char *)stack->content + ((stack->size - 1) * stack->element_size);
}