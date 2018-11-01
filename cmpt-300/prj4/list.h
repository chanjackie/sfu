#ifndef LIST_H
#define LIST_H

#include <pthread.h>
#include "smartLock.h"

struct nodeStruct {
    pthread_t threadNum;
    SmartLock *smartLock;
    struct nodeStruct *next;
};

struct nodeStruct* List_createNode(SmartLock *smartLock, pthread_t threadNum);
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node);
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node);
int List_countNodes (struct nodeStruct *head);
struct nodeStruct* List_findNode(struct nodeStruct *head, pthread_t threadNum, int lockId);
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node);
// void List_sort (struct nodeStruct **headRef);
// void List_merge (struct nodeStruct **firstHalf, struct nodeStruct **secondHalf, struct nodeStruct **headRef);
void List_print(struct nodeStruct **headRef);

#endif