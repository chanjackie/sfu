/*
 * Node.cpp
 *
 * Class Definition: Node of a singly linked list 
 *                   in which the data is of Profile data type.
 *                   Designed and implemented as a non-ADT.
 *
 * Created on: 
 * Author: 
 */

#include <cstdio>    // Needed for NULL
#include "Profile.h"
#include "Node.h"

Node::Node()
{
	next = NULL;
}

Node::Node(Profile theData)
{
	data = theData;
	next = NULL;
}

Node::Node(Profile theData, Node* theNextNode)
{
	data = theData;
	next = theNextNode;
}

// end Node.cpp