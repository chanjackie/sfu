/*
 * Node.h
 *
 * Class Definition: Node of a singly linked list 
 *                   in which the data is of Profile data type.
 *                   Designed and implemented as a non-ADT.
 *
 * Created on: 
 * Author: 
 */
 
// #pragma once is shorthand for the 2 #include guards we've seen before:
// #ifndef _NODE and #define _NODE
// and it means: do not include me more than once.
#pragma once
#include "Profile.h"

class Node {
	
public:
	// Public data members - Why are the data members public?
	Profile data;     // The data in the node
	Node* next;       // Pointer to next node
	
	// Constructors
	Node();
	Node(Profile theData);
	Node(Profile theData, Node* theNextNode);

}; // end Node