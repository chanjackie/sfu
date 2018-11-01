#include <stdio.h>
#include "smartLock.h"
#include "list.h"
                           
int counter = 0;
struct nodeStruct *head = NULL;


void init_lock(SmartLock* lock) {
    pthread_mutex_init(&(lock->mutex), NULL);
    lock->lockId = counter;
    counter++;
    struct nodeStruct *node = List_createNode(lock, -1);
    if (List_countNodes(head) == 0) {
    	List_insertHead(&head, node);
    } else {
    	List_insertTail(&head, node);
    }
    List_print(&head);
}

int lock(SmartLock* lock) {
	struct nodeStruct *lockNode = List_findNode(head, -1, lock->lockId);
	struct nodeStruct *threadNode = List_findNode(head, pthread_self(), -1);
	if (threadNode == NULL) {
		threadNode = List_createNode(NULL, pthread_self());
	}
	if (lockNode->next == NULL) {
		printf("%lu locking lock %d\n", pthread_self(), lock->lockId);
    	pthread_mutex_lock(&(lock->mutex));
    	return 1;
	} else {
		return 0;
	}
}

void unlock(SmartLock* lock) {
	printf("%lu unlocking lock %d\n", pthread_self(), lock->lockId);
    pthread_mutex_unlock(&(lock->mutex));
}

/*
 * Cleanup any dynamic allocated memory for SmartLock to avoid memory leak
 * You can assume that cleanup will always be the last function call
 * in main function of the test cases.
 */
void cleanup() {

}