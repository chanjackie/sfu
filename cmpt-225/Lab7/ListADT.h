/*
 * ListADT.h
 * 
 * Class Description: A position-oriented list ADT - inspired from ListADT from our textbook.
 * Class Invariant: List position of elements starts at 1 (not 0).
 * 
 * Note 1: This is a link-based implementation of a data collection List ADT class 
 *         as its underlying data structure is a singly-headed singly-linked list (SHSL).                  
 *
 * Note 2: The public methods have the same declaration as the methods of the array-
 *         based implementation of ListADT class.
 * 
 * Inspired on: May 31, 2016
 * Author: AL
 */

#pragma once
#include "Node.h"

using namespace std;

class ListADT{

private:
    int elementCount;  // Number of elements currently stored in the list.
	Node *head;        // Pointer to the first node in the list

	// Helper method - Private
	Node* getNodeAt(int position) const;
	
public:
	
	// Default constructor
	ListADT();

	// Copy constructor
	ListADT(const ListADT& lst); 

	// Destructor
	~ListADT();


	// Description: Returns the current number of elements in the List.
	int  getElementCount() const;

	// Description: Inserts newElement at newPosition in the List. 
	// Postcondition: If 1 <= newPosition <= getElementCount() + 1 and the insertion
	//                is successful, newElement is at newPosition in the List,
	//                other elements, located after newElement, "have moved" 1 position up, 
	//                and the returned value is true. Otherwise, false is returned.
	bool insert(int newPosition, const Profile& newElement);

	// Description: Removes the element at position in the List 
	// Postcondition: If 1 <= position <= getElementCount() and the removal is successful,
	//                the element at position in the List is removed, and
	//                other elements "have moved" 1 position down, 
	//                and the returned value is true. Otherwise, false is returned.
	bool remove(int position);


	// Description: Removes all elements from the List.
	// Postconditions: List contains no elements and the element count is 0.
	void clear();


	// Description: Returns the element at position in the List or NULL.
	// Precondition: 1 <= position <= getElementCount().	
	Profile getElement(int position) const;


	// Description: Replaces the element at position by newElement in the List.
	// Precondition: 1 <= position <= getElementCount().
	void setElement(int position, const Profile& newElement);

	// Description: Prints all elements in the List. FOR DEBUGGING PURPOSES
	friend ostream & operator<<(ostream & os, const ListADT& rhs);

}; // end header file ListADT