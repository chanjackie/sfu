/*
 * ListADT.cpp
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

#include "ListADT.h"
#include <cassert>
#include <string>
#include <iostream>

using namespace std; //needed for cout, cin to be recognized


// Default constructor
ListADT::ListADT() {
	elementCount = 0;
	head = NULL;
}

// Copy constructor
ListADT::ListADT(const ListADT& rhs) : elementCount(rhs.elementCount) {

	Node* originalList = rhs.head;  // Points to nodes in original linked list

    if ( originalList == NULL)
       head = NULL;  // Original linked list is empty
    else
    {
       // Copy first node
       head = new Node(originalList -> data);
      
       // Copy remaining nodes
       Node* newList = head;      // Points to last node in new linked list
       originalList = originalList -> next;   // Advance original linked list pointer
       while (originalList != NULL)
       {
          // Create a new node containing the next element 
          Node* newNode = new Node(originalList -> data);
 
          // Link new node to end of new linked list
          newList -> next = newNode; 
         
          // Advance pointer to new last node      
          newList = newList -> next;
         
          // Advance original linked list pointer
          originalList = originalList -> next;
       }  // end while
      
       newList -> next = NULL;              // Flag end of linked list
    }  // end if
 }  // end copy constructor

// Desctructor
ListADT::~ListADT() {
   clear();
}  // end destructor


// Description: Returns the current number of elements in the List.
int ListADT::getElementCount() const {
   return elementCount;
}  // end getElementCount
	
// Description: Inserts newElement at newPosition in the List. 
// Postcondition: If 1 <= newPosition <= getElementCount() + 1 and the insertion
//                is successful, newElement is at newPosition in the List,
//                other elements, located after newElement, "have moved" 1 position up, 
//                and the returned value is true. Otherwise, false is returned.
bool ListADT::insert(int newPosition, const Profile& newElement) {

   bool ableToInsert = (newPosition >= 1) && (newPosition <= elementCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new element 
      Node* newNode = new Node(newElement);  
      
      // Attach new node to linked list
      if (newPosition == 1)
      {
         // Insert new node at beginning of linked list
         newNode -> next = head; 
         head = newNode;
      }
      else
      {
         // Find node that will be before new node
         Node* previous = getNodeAt(newPosition - 1);
         
         // Insert new node after node to which previous points
         newNode -> next = previous -> next; 
         previous -> next = newNode;
      }  // end if

      elementCount++;  // Increase count of elements
   }  // end if
   
   return ableToInsert;
}  // end insert

// Description: Removes the element at position in the List 
// Postcondition: If 1 <= position <= getElementCount() and the removal is successful,
//                the element at position in the List is removed, and
//                other elements "have moved" 1 position down, 
//                and the returned value is true. Otherwise, false is returned.
bool ListADT::remove(int position) {
   
   bool ableToRemove = (position >= 1) && (position <= elementCount);
   if (ableToRemove)
   {
      Node* current = NULL;
      if (position == 1)
      {
         // Remove the first node in the linked list
         current = head; // Save pointer to node
         head = head -> next;
      }
      else
      {
         // Find node that is before the one to remove
         Node* previous = getNodeAt(position - 1);
         
         // Point to node to remove
         current = previous -> next;
         
         // Disconnect indicated node from linked list by connecting the
         // previous node with the one after
         previous -> next = current -> next;
      }  // end if
      
      // Return node to system
      current->next = NULL;
      delete current;
      current = NULL;
      
      elementCount--;  // Decrease count of elements
   }  // end if
   
   return ableToRemove;
}  // end remove


// Description: Removes all elements from the List.
// Postconditions: List contains no elements and the element count is 0.
void ListADT::clear() {
   while ( getElementCount() > 0 )
      remove(1);
}  // end clear

// Description: Returns the element at position in the List or NULL.
// Precondition: 1 <= position <= getElementCount().
Profile ListADT::getElement(int position) const
{
   Profile aProfile;

   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= elementCount);
   if (ableToGet)
   {
      Node* current = getNodeAt(position);
      aProfile = current -> data;
   }
   else
   {
      string message = "getElement() called with an empty list or an invalid position.";
      cout << message;  // throw exception may be better
   } 
   return aProfile;
}  // end getElement


// Description: Replaces the element at position by newElement in the List.
// Precondition: 1 <= position <= getElementCount().
void ListADT::setElement(int position, const Profile& anElement) {

 // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= elementCount);
   if (ableToSet)
   {
      Node* current = getNodeAt(position);
      current -> data = anElement;
   }
   else
   {
      string message = "setElement() called with an empty list or an invalid position.";
      cout << message;  // throw exception may be better
   }  // end if

}  // end setElement

// Helper method - Private
Node* ListADT::getNodeAt(int position) const {
   // Debugging check of precondition
   assert( (position >= 1) && (position <= elementCount) );
   
   // Count from the beginning of the linked list
   Node* current = head;
   for (int skip = 1; skip < position; skip++)
      current = current-> next;
      
   return current;
}  // end getNodeAt


// Description: Prints all elements in the List. FOR DEBUGGING PURPOSES
ostream & operator<<(ostream & os, const ListADT& rhs) {
	Node* current = rhs.head;
	
	// Traverse the list
	while (current != NULL){
		cout << current -> data; // Print data
		current = current -> next; // Go to next Node

	}
	
	return os;
}
// end of implementation file of ListADT class