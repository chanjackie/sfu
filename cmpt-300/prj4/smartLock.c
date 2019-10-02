#include <stdio.h>
#include <stdlib.h>
#include "smartLock.h"
#include "list.h"
#include <semaphore.h>

int lockCount = 0;
int threadCount = 0;
struct nodeStruct **threads = NULL;
struct nodeStruct **locks = NULL;
sem_t mutex;


_Bool check_cycle(struct nodeStruct **start, struct nodeStruct **process);

void init_lock(SmartLock* lock) {
    if (lockCount == 0) {
        sem_init(&mutex, 0, 1);
    }
    pthread_mutex_init(&(lock->mutex), NULL);
    lock->lockId = lockCount;
    lockCount++;
    struct nodeStruct *node = List_createNode(lock, -1);
    locks = (struct nodeStruct**)realloc(locks, lockCount*sizeof(struct nodeStruct));
    locks[lockCount-1] = node;
    printf("LockId: %d\n", locks[lockCount-1]->smartLock->lockId);
}

int lock(SmartLock* lock) {
    sem_wait(&mutex);
    struct nodeStruct *lockNode = NULL;
    for (int i=0;i<lockCount;i++) {
        if (lock->lockId == locks[i]->smartLock->lockId) {
            lockNode = locks[i];
            break;
        }
    }
    if (lockNode == NULL) {
        printf("Lock wasn't initialized properly.\n");
    }
    struct nodeStruct *threadNode = NULL;
    for (int i=0;i<threadCount;i++) {
        if (pthread_self() == threads[i]->threadNum) {
            threadNode = threads[i];
            break;
        }
    }
    if (threadNode == NULL) {
        threadNode = List_createNode(NULL, pthread_self());
        threadCount++;
        threads = (struct nodeStruct**)realloc(threads, threadCount*sizeof(struct nodeStruct));
        threads[threadCount-1] = threadNode;
    }
    if (lockNode->next == NULL) {
        if (!check_cycle(&lockNode, &threadNode)) { 
            printf("%lu locking lock %d\n", pthread_self(), lock->lockId);
            lockNode->next = threadNode;
            threadNode->next = NULL;
            pthread_mutex_lock(&(lock->mutex));
            print_list();
            sem_post(&mutex);
            return 1;
        }
    } else {
        if (!check_cycle(&threadNode, &lockNode)) {
            threadNode->next = lockNode;
        }        
    }
    sem_post(&mutex);
    return 0;
}

void unlock(SmartLock* lock) {
    printf("%lu unlocking lock %d\n", pthread_self(), lock->lockId);
    print_list();
    struct nodeStruct *lockNode = NULL;
    for (int i=0;i<lockCount;i++) {
        if (lock->lockId == locks[i]->smartLock->lockId) {
            lockNode = locks[i];
            break;
        }
    }
    printf("Lock %d being unlocked\n", lockNode->smartLock->lockId);
    lockNode->next = NULL;
    print_list();
    pthread_mutex_unlock(&(lock->mutex));
}

/*
 * Cleanup any dynamic allocated memory for SmartLock to avoid memory leak
 * You can assume that cleanup will always be the last function call
 * in main function of the test cases.
 */
void cleanup() {
    for (int i=0;i<lockCount;i++) {
        free(locks[i]);
    }
    for (int i=0;i<threadCount;i++) {
        free(threads[i]);
    }
    free(locks);
    free(threads);
}

void print_list() {
    printf("----Printing List----\n");
    for (int i=0;i<lockCount;i++) {
        List_print(&locks[i]);
    }
}

_Bool check_cycle(struct nodeStruct **start, struct nodeStruct **next) {
    struct nodeStruct *startNode = *start;
    struct nodeStruct *nextNode = *next;
    struct nodeStruct *previousNextNode = startNode->next;
    startNode->next = nextNode;
    if (nextNode->next == startNode) {
        nextNode->next = NULL;
        return 0;
    }
    while (1) {
        nextNode = nextNode->next;
        if (nextNode == NULL || nextNode == startNode) {
            break;
        }
    }
    if (nextNode == startNode) {
        startNode->next = previousNextNode;
        return 1;
    }
    return 0;
}