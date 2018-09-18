#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
struct nodeStruct* List_createNode(int item) {
	struct nodeStruct *node = malloc(sizeof(struct nodeStruct));
	node->item = item;
	printf("node->item: %d\n", node->item);
	return node;
}


/*
 * Insert node at the head of the list.
 */
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node) {
	if (node != NULL) {		
		node->next = *headRef;
		*headRef = node;
	}
	return;
}


/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node) {
	if (*headRef != NULL) {	
		struct nodeStruct *listNode = *headRef;
		while (listNode->next != NULL) {
			listNode = listNode->next;
		}
		listNode->next = node;
	}
	return;
}


/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct nodeStruct *head) {
	if (head == NULL) {
		return 0;
	}
	int length = 1;
	struct nodeStruct *node = head;
	while (node->next != NULL) {
		length++;
		node = node->next;
	}
	return length;
}


/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, int item) {
	if (head == NULL) {
		return NULL;
	}
	while (head->item != item) {
		if (head->next != NULL) {
			head = head->next;
		} else {
			return NULL;
		}
	}
	return head;
}

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node 
 * in the list. For example, the client code may have found it by calling 
 * List_findNode(). If the list contains only one node, the head of the list 
 * should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node) {
	if (node != NULL) {
		int count = List_countNodes(*headRef);
		if (count == 1) {
			free(*headRef);
			*headRef = NULL;
		} else {
			struct nodeStruct *head = *headRef;
			struct nodeStruct *prev;
			while (head->item != node->item) {
				prev = head;
				head = head->next;
			}
			prev->next = head->next;
			free(head);
		}
	}
	return;
}


/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef) {
	int count = List_countNodes(*headRef);
	if (count == 0 || count == 1) {
		return;
	} else {
		int half = (count/2)-1;
		struct nodeStruct *firstHalf = *headRef;
		for (int i=0;i<half;i++) {
			firstHalf = firstHalf->next;
		}
		struct nodeStruct *secondHalf = firstHalf->next;
		firstHalf->next = NULL;
		firstHalf = *headRef;
		List_sort(&firstHalf);
		List_sort(&secondHalf);
		List_merge(&firstHalf, &secondHalf, headRef);
	}
	return;
}

void List_merge (struct nodeStruct **firstHalf, struct nodeStruct **secondHalf, struct nodeStruct **headRef) {
	struct nodeStruct *firstHead = *firstHalf;
	struct nodeStruct *secondHead = *secondHalf;
	struct nodeStruct *sortedList;
	if (firstHead->item < secondHead->item) {
		sortedList = firstHead;
		firstHead = firstHead->next;
	} else {
		sortedList = secondHead;
		secondHead = secondHead->next;
	}
	*headRef = sortedList;
	while(firstHead != NULL && secondHead != NULL) {
		if (firstHead->item < secondHead->item) {
			sortedList->next = firstHead;
			firstHead = firstHead->next;
		} else {
			sortedList->next = secondHead;
			secondHead = secondHead->next;
		}
		sortedList = sortedList->next;
	}
	if (firstHead == NULL) {
		sortedList->next = secondHead;
	} else {
		sortedList->next = firstHead;
	}
	printf("Sorted ");
	List_print(headRef);
	return;
}

void List_print(struct nodeStruct **headRef) {
	struct nodeStruct *head = *headRef;
	printf("Printing list: \n");
	while (head != NULL) {
		printf("%d, ", head->item);
		head = head->next;
	}
	printf("\n");
	return;
}