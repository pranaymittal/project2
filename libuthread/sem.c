#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	int count;
	queue_t queue;
};

sem_t sem_create(size_t count)
{
	sem_t sem = (sem_t) malloc(sizeof(struct semaphore));
	if (sem == NULL) {
		return NULL;
	}

	sem->count = count;
	sem->queue = queue_create();
	if (sem->queue == NULL) {
		free(sem);
		return NULL;
	}

	return sem;
}

int sem_destroy(sem_t sem)
{
	if (sem == NULL) {
		return -1;
	}

	queue_destroy(sem->queue);
	free(sem);

	return 0;
}

int sem_down(sem_t sem)
{
	if (sem == NULL) {
		return -1;
	}

	while (sem->count == 0) {
		void *dummy;
		queue_enqueue(sem->queue, &dummy);
		queue_dequeue(sem->queue, NULL);
	}

	sem->count--;

	return 0;
}

int sem_up(sem_t sem)
{
	if (sem == NULL) {
		return -1;
	}

	sem->count++;

	if (queue_length(sem->queue) > 0) {
		void *dummy;
		queue_dequeue(sem->queue, &dummy);
	}

	return 0;
}

