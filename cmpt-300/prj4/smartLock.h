#ifndef SMARTLOCK_H
#define SMARTLOCK_H
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    int lockId;
    /* Add other variables */
} SmartLock;
       
void init_lock(SmartLock* lock);

int lock(SmartLock* lock);

void unlock(SmartLock* lock);

void cleanup();

void print_list();

#endif