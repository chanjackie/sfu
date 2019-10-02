#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "bbuff.h"
#include <semaphore.h>

void* bbuff[BUFFER_SIZE];
sem_t mutex;
sem_t full;
sem_t empty;
int front;
int end;

void bbuff_init() {
	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);
	front = 0;
	end = 0;
}

_Bool bbuff_is_empty() {
	int count;
	sem_getvalue(&full, &count);
	if (count == 0) {
		return true;
	} else {
		return false;
	}
}

void bbuff_blocking_insert(void *item) {
	sem_wait(&empty);
	sem_wait(&mutex);
	bbuff[end] = item;
	end = (end+1) % BUFFER_SIZE;
	sem_post(&mutex);
	sem_post(&full);
	return;
}

void* bbuff_blocking_extract() {
	sem_wait(&full);
	sem_wait(&mutex);
	void *item = bbuff[front];
	front = (front+1) % BUFFER_SIZE;
	sem_post(&mutex);
	sem_post(&empty);
	return item;
}

