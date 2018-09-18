// Sample test routine for the list module.
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/*
 * Main()
 */
int main(int argc, char** argv)
{
	printf("Starting tests...\n");
	struct nodeStruct *head = NULL;
	// Starting count:
	assert(List_countNodes(head) == 0);
	printf("Passed countNodes\n");

	// Create 1 node:
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, 1) == NULL);

	// Insert tail:
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);
	assert(List_countNodes(head) == 2);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, -5) == lastNode);
	assert(List_findNode(head, 1) == NULL);

	// Verify list:
	struct nodeStruct *current = head;
	assert(current->item == 0);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);

	// Sort and verify:
	List_sort(&head);
	current = head;
	List_print(&head);
	assert(current->item == -5);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == 0);
	assert(current->next == NULL);
	printf("Passed first sort test.\n");

	// Insert many and sort:
	for (int i=0;i<10;i++) {
		struct nodeStruct *newNode = List_createNode(rand() % (51) + 2);
		List_insertHead(&head, newNode);
	}
	List_print(&head);
	List_sort(&head);
	List_print(&head);

	// Delete
	assert(List_countNodes(head) == 12);
	struct nodeStruct *nodeOf0 = List_findNode(head, 0);
	List_deleteNode(&head, nodeOf0);
	assert(List_countNodes(head) == 11);
	assert(List_findNode(head, 0) == NULL);
	assert(List_findNode(head, 1) == NULL);
	current = head;
	assert(current->item == -5);
	assert(current->next != NULL);
	List_print(&current);

	printf("\nExecution finished.\n");
	return 0;
}
