#ifndef H_QUEUE
#define H_QUEUE

#include <stddef.h>

typedef struct QueueNode
{
	void *value;
	struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
	QueueNode *front;
	QueueNode *rear;
	size_t size;
} Queue;

void init_queue(Queue *queue);
void enqueue(Queue *queue, const void *value, size_t element_size);
void *dequeue(Queue *queue);
void free_queue(Queue *queue);
const void *peek_queue(const Queue *queue);
int is_queue_empty(const Queue *queue);
size_t queue_size(const Queue *queue);

#endif 