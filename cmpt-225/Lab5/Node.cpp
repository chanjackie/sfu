/*
 * Node.cpp
 *
 * Class Definition: Node of a singly linked list
 *                   in which the data is of "int" data type.
 *                   Designed and implemented as a non-ADT.
 *
 * Created on:
 * Author:
 */

#include <cstdio>  // Needed for NULL
#include "Node.h"

Node::Node()
{
	data = 0;
	next = NULL;
}

Node::Node(int theData)
{
	data = theData;
	next = NULL;
}

Node::Node(int theData, Node* theNextNode)
{
	data = theData;
	next = theNextNode;
}

// end Node.cpp
