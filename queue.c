#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void init_queue(Queue *queue)
{
	queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void enqueue(Queue *queue, const void *value, size_t element_size)
{
	QueueNode *new_node = malloc(sizeof(QueueNode));
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

	if (queue->rear == NULL) 
	{
        queue->front = new_node;
        queue->rear = new_node;
    } 
    else 
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

	queue->size++;
}

void *dequeue(Queue *queue)
{
	if (queue->front == NULL)
		return NULL;

	QueueNode *old_front = queue->front;
	void *old_front_value = old_front->value;

	queue->front = old_front->next; // Move front to next node

	
    if (queue->front == NULL) // If front is now NULL, queue is empty: update rear too
        queue->rear = NULL;

    free(old_front);
    queue->size--;

    return old_front_value;  // Caller must free
}

void free_queue(Queue *queue)
{
    if (!queue) 
    	return;

    QueueNode *current = queue->front;
    while (current != NULL)
    {
        QueueNode *next = current->next;

        free(current->value);  // assuming enqueue used malloc for value
        free(current);

        current = next;
    }

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

const void *peek_queue(const Queue *queue)
{
    if (!queue || queue->front == NULL)
        return NULL;

    return queue->front->value;
}

int is_queue_empty(const Queue *queue)
{
	return queue->size == 0;
}

size_t queue_size(const Queue *queue)
{
	return queue->size;
}