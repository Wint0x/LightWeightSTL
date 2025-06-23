#ifndef H_SEMAPHORE
#define H_SEMAPHORE

#include <pthread.h>

typedef struct Semaphore 
{
    int count;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Semaphore;

void semaphore_init(Semaphore *s, const int initial_count);
void semaphore_wait(Semaphore *s);     // wait / down / P
void semaphore_signal(Semaphore *s);   // signal / up / V
void semaphore_destroy(Semaphore *s);

#endif