#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node {
    int data;
    struct node* next;
} Node;

struct queue {
	Node* front;
	Node* rear;
	int length;
} Queue;

queue_t queue_create(void)
{
	queue_t queue = malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	queue->length = 0;
	return queue;
}

int queue_destroy(queue_t queue)
{
	Node* current = queue->front;
	Node* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	free(queue);
}

int queue_enqueue(queue_t queue, void *data)
{
	Node* new_node = malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;

	if(queue->rear == NULL){
		queue->front = new_node;
		queue->rear = new_node;
	} else {
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
	queue->length++;
}

int queue_dequeue(queue_t queue, void **data)
{
	if(queue->front == NULL){
		printf("ERROR: no output from empty\n");
		return -1;
	}

	Node* temp = queue->front;
    *data = (void *)temp->data;

	if(queue->front == queue->rear){
		queue->front = NULL;
		queue->front = NULL;
	} else {
		queue->front = queue->front->next;
	}

	queue->length--;
	free(temp);
	return data;
}

int queue_delete(queue_t queue, void *data)
{
	if(queue->front == NULL){
		printf("ERROR: no output from empty\n");
		return -1;
	}

	Node* current = queue->front;
	Node* prev = NULL;

	while (current != NULL) {
		if (current->data == *(int*)data) {
			if (current == queue->front) {
				queue->front = current->next;
			} else {
				prev->next = current->next;
			}

			if (current == queue->rear) {
				queue->rear = prev;
			}

			free(current);
			queue->length--;
			return 0;
		}

		prev = current;
		current = current->next;
	}

	printf("Error: element not found in queue\n");
	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	if(queue->front == NULL){
		printf("ERROR: no output from empty\n");
		return -1;
	}

	Node* current = queue->front;

	while (current != NULL) {
		func(current->data);
		current = current->next;
	}

	return 0;
}

int queue_length(queue_t queue)
{
	return queue->length;
}

