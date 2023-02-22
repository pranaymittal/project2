#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

int test_queue_enqueue() {
  queue_t queue = queue_create();
  int data[3] = {1, 2, 3};
  TEST_ASSERT(queue_enqueue(queue, &data[0]) == 0);
  TEST_ASSERT(queue_enqueue(queue, &data[1]) == 0);
  TEST_ASSERT(queue_enqueue(queue, &data[2]) == 0);
  TEST_ASSERT(queue_length(queue) == 3);
  queue_destroy(queue);
  return 0;
}

void sum_data(void *data, void *arg) {
  int *sum = (int *)arg;
  *sum += *(int *)data;
}

void test_queue_iterate() {
  queue_t queue = queue_create();
  int data[3] = {1, 2, 3};
  queue_enqueue(queue, &data[0]);
  queue_enqueue(queue, &data[1]);
  queue_enqueue(queue, &data[2]);
  int sum = 0;
  queue_iterate(queue, sum_data, &sum, NULL);
  TEST_ASSERT(sum == 6);
  queue_destroy(queue);
}

void test_queue_dequeue() {
  queue_t queue = queue_create();
  int data[3] = {1, 2, 3};
  queue_enqueue(queue, &data[0]);
  queue_enqueue(queue, &data[1]);
  queue_enqueue(queue, &data[2]);
  void *ptr;
  TEST_ASSERT(queue_dequeue(queue, &ptr) == 0);
  TEST_ASSERT(*(int *)ptr == 1);
  TEST_ASSERT(queue_length(queue) == 2);
  queue_destroy(queue);
}

void test_queue_delete() {
  queue_t queue = queue_create();
  int data[3] = {1, 2, 3};
  queue_enqueue(queue, &data[0]);
  queue_enqueue(queue, &data[1]);
  queue_enqueue(queue, &data[2]);
  TEST_ASSERT(queue_delete(queue, &data[1]) == 0);
  TEST_ASSERT(queue_length(queue) == 2);
  queue_destroy(queue);
}

void test_queue_empty_dequeue() {
  queue_t queue = queue_create();
  void *ptr;
  TEST_ASSERT(queue_dequeue(queue, &ptr) == -1);
  queue_destroy(queue);
}

void test_queue_empty_delete() {
  queue_t queue = queue_create();
  int data = 42;
  TEST_ASSERT(queue_delete(queue, &data) == -1);
  queue_destroy(queue);
}

int main(void)
{
	test_create();
	test_queue_simple();

	return 0;
}
