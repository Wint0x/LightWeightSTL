#include <pthread.h>
#include "semaphore.h"

void semaphore_init(Semaphore *s, const int initial_count)
{
	s->count = initial_count;

	// default attributes
	pthread_mutex_init(&s->lock, NULL); 
    pthread_cond_init(&s->cond, NULL);   
}

void semaphore_wait(Semaphore *s)
{
	pthread_mutex_lock(&s->lock);

	while (s->count == 0) 
		pthread_cond_wait(&s->cond, &s->lock);

    s->count--;  // take a token
    pthread_mutex_unlock(&s->lock);
}

void semaphore_signal(Semaphore *s)
{
    pthread_mutex_lock(&s->lock);
    s->count++;  // Return the token
    pthread_cond_signal(&s->cond);  // Wake one thread
    pthread_mutex_unlock(&s->lock);
}

void semaphore_destroy(Semaphore *s)
{
    pthread_mutex_destroy(&s->lock);
    pthread_cond_destroy(&s->cond);
}