#include <stdio.h>
#include "smartLock.h"
                           
int counter = 0;

void init_lock(SmartLock* lock) {
    pthread_mutex_init(&(lock->mutex), NULL);
    lock->lockId = counter;
    counter++;
}

int lock(SmartLock* lock) {
	printf("%lu locking\n", pthread_self());
    pthread_mutex_lock(&(lock->mutex));
    return 1;
}

void unlock(SmartLock* lock) {
    pthread_mutex_unlock(&(lock->mutex));
}

/*
 * Cleanup any dynamic allocated memory for SmartLock to avoid memory leak
 * You can assume that cleanup will always be the last function call
 * in main function of the test cases.
 */
void cleanup() {

}