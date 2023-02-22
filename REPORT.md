# Overview
The goal of the assignment was to implement a basic thread library in C.
This would include the creation of a queue class, create threads, have them
perform context switching, and be able to delete threads correctly. The
implementation of the a scheduler performing the thread execution in the
Round Robin method is also expected. 

# Implement Queue
A queue is a linear data structure that follows a First-In-First-Out (FIFO)
principle. Elements can only be added to the back of the queue, and can only
be removed from the front of the queue. The queue provides basic operations
such as enqueue (add an element to the back of the queue), dequeue (remove
an element from the front of the queue), and peek (look at the front of the
queue without removing the element). The implementation typically uses a
dynamic array or linked list to store the elements. Queues are used in many
applications, including operating system scheduling, networking, and
simulation systems. The queue is implemented as a doubly-linked list, where
each element in the queue is represented as a struct queue_entry. Each
queue_entry has a next and prev pointer, which allows elements to be added and
removed from the list. The queue_init() function initializes a new empty queue
by setting the head and tail pointers to NULL. The queue_enqueue() function
adds an element to the end of the queue by creating a new queue_entry, setting
its data field to the provided data, and updating the next and prev pointers
of the tail element and the new queue_entry. The queue_dequeue() function
removes the element at the head of the queue by updating the head pointer to
point to the next element in the queue, and returning the data field of the
removed element. The queue_iterate() function iterates over each element in
the queue and calls the provided queue_func_t function on each element's data
field. The queue_destroy() function frees all memory associated with the queue
by iterating over each element and calling the provided free_func function on
each element's data field, and then freeing the queue_entry and the queue's
header structure. Overall, this queue implementation provides a flexible and
efficient way to manage a list of elements in a first-in, first-out order.
The queue is thread-safe, using a mutex to ensure that only one thread can
modify the queue at a time.

# Queue Testing
The queue tests added above are a set of unit tests that aim to validate the
functionality of the queue data structure. The tests are designed to cover a
range of scenarios, such as queue creation, enqueuing and dequeuing items from
the queue, checking queue length, and checking that queue operations behave as
expected when the queue is empty. The tests also cover edge cases such as
attempting to dequeue an element from an empty queue and similar NULL cases.
The tests can be run using a test runner, which aggregates the results of all
the tests and provides feedback on any failed tests. The tests are an
important component of the development process, as they help ensure that the
queue data structure is behaving as expected, and that any changes made to the
code do not inadvertently break existing functionality.

# Implement Semaphore
This code implements a semaphore, a synchronization mechanism used for
controlling access to shared resources. The semaphore is represented by a
structure containing an integer count and a queue of threads waiting for
the semaphore. The sem_create function creates a new semaphore with an initial
count value specified by the caller. If successful, it returns a pointer to
the semaphore. If memory allocation fails, it returns a NULL value.
The sem_destroy function deallocates the semaphore and its associated queue.
It returns 0 on success and -1 if the semaphore pointer is NULL.
The sem_down function decrements the semaphore count and blocks the calling
thread if the count becomes zero. This is achieved by adding the thread to the
semaphore's waiting queue and then dequeuing the next thread in line. This
operation is performed inside a loop to handle spurious wakeups. If
successful, it returns 0, and if the semaphore pointer is NULL, it returns -1.
The sem_up function increments the semaphore count and wakes up the next
waiting thread if any. If successful, it returns 0, and if the semaphore
pointer is NULL, it returns -1. If there are no threads waiting, the count is
simply incremented. Overall, this implementation provides a simple and
efficient way to synchronize multiple threads and manage access to shared
resources.

# Implement Preemption
This is the implementation of the preemption mechanism for the uthread library.
Preemption is the ability of a scheduler to interrupt a running task and allow
another task to run. This code sets up a timer that sends a signal to the
program every 1/HZ seconds, which triggers a signal handler function called
alarm_handler(). If preemption is enabled, this function calls uthread_yield()
to give up the CPU and allow another thread to run. The functions
preempt_disable() and preempt_enable() are used to control whether preemption
is enabled or disabled. When preemption is disabled, the preempt_enabled
variable is set to false, and the signal handler function does nothing. This
can be useful in critical sections of code where you don't want to be
interrupted. The preempt_start() function sets up the timer and enables
preemption. The preempt_stop() function disables the timer and disables
preemption. These two functions are used to start and stop preemption as
needed, for example, when creating or destroying a thread. This code makes
use of the sigaction() and setitimer() system calls to set up the timer and
signal handler. If these functions fail, an error message is printed and the
program exits with an error code. The HZ constant determines the frequency of
preemption, which is set to 100Hz, or 100 times per second. The preempt_start
function sets up a timer that will send a signal (SIGALRM) to the current
process at a specific frequency, HZ, which is defined as 100 times per second.
This signal will be handled by the alarm_handler function, which calls the
uthread_yield() function, causing the current thread to yield to the next
runnable thread in the scheduler.Before starting the timer, preempt_start sets
up a signal handler for SIGALRM, configures the timer to fire at the specified
frequency, and enables or disables preemption based on the argument passed
to the function. If preemption is enabled, the uthread_yield() function will
be called each time the timer fires and the alarm_handler function is 
executed. If preemption is disabled, the uthread_yield() function will not be
called and the current thread will continue executing until it yields or is
blocked. The preempt_disable and preempt_enable functions allow the
application to explicitly enable or disable preemption, regardless of the
state set by preempt_start. Finally, preempt_stop disables the timer and
disables preemption.

# Error Handling
Error handling was implemented within the classes created. They were
conditional checks placed at the beginning of various functions. Most of the
conditionals were whether the values trying to be modified or read from were
NULL value. This is the obvious error, that was easy to pay attention for. 