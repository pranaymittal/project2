#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

static bool preempt_enabled = true;

void preempt_disable(void)
{
	preempt_enabled = false;
}

void preempt_enable(void)
{
	preempt_enabled = true;
}

static void alarm_handler(int signum)
{
    if (preempt_enabled) {
        uthread_yield();
    }
}

void preempt_start(bool preempt)
{
	struct sigaction sa;
	struct itimerval timer;


	sa.sa_handler = alarm_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGALRM, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 1000000 / HZ;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 1000000 / HZ;
	if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
		perror("setitimer");
		exit(1);
	}

	preempt_enabled = preempt;
}

void preempt_stop(void)
{
	struct itimerval timer = {0};
	if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
		perror("setitimer");
		exit(1);
	}

	preempt_enabled = false;
}
