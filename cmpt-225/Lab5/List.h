/*
 * List.h - Header of the List class
 *
 * Class Description: A value-oriented unsorted List data collection ADT class.
 *                    Note that this is a link-based implementation
 *                    of a List data collection ADT class.
 *                    Its underlying data structure is
 *                    a singly-headed singly-linked list (SHSL).
 *
 * Creation Date:
 * Author:
 */

// #pragma once is shorthand for the 2 #include guards we've seen before:
// #ifndef _NODE and #define _NODE
// and it means: do not include me more than once.
#pragma once
#include "Node.h"


class List{

private:
    int elementCount;  // Number of elements currently stored in the List.
	Node *head;        // Pointer to the first node in the List.

public:
	// Constructors and Destructors

	/* Generally, every class that makes use of dynamically allocated memory
	 * should have at least two constructors:
	 *   a default constructor and
	 *   a copy constructor that creates a distinct copy of the given object
	 * (even if the client code does not make use of all of these constructors).
	 */

	// Description: Default constructor
	List();


	/* Note that the compiler will generate a copy constructor automatically.
	 * However, this constructor only creates a SHALLOW COPY (so would only copy the
	 * elementCount and head variables). In this case, this would NOT CREATE A
	 * NEW LIST object, just a new reference to "this" List object.
	 * It is therefore necessary to write a constructor that makes a DEEP COPY
	 * if our class makes use of dynamically allocated memory.
	 */

	/* Also note the parameter. C++ functions use pass-by-value by
	 * default. This means that the functions make copies of the given
	 * arguments. This is inefficient (particularly for large objects).
	 * Therefore it is normal to pass the address, also called the reference,
	 * (using &) of the parameter. Also, if the parameter must not be changed,
	 * it is good practice to make it const, which prevents it from being changed.
	 */
	// Description: Copy constructor to copy an existing List object.
	List(const List& lst);


	/* The destructor is responsible for deleting any memory that was dynamically
	 * allocated by an object. If there is no such memory, no destructor needs to
	 * be created (the compiler automatically creates one).
	 * Because this class makes use of dynamically allocated memory
	 * i.e., uses pointers when new Node objects are instantiated, it is necessary to write
	 * a destructor. Destructors are identified by the '~' preceding the class name.
	 * There can be only one destructor for a class, and it cannot have parameters.
	 */
	// Description: Destructor.
	~List();


	/**************************************************************************/
	// List Public Interface

	// Description: Returns the number of elements in the List.
	int getElementCount() const;

    // Description: Adds an element (newElement) at the front of the List.
	//              Returns true if newElement has been added to the List, false otherwise.
	// Parameter: newElement -> the element to be added to the List.
	bool add(int newElement);

	// Description: Removes The first instance of toBeRemoved from the List.
	//              Returns true if toBeRemoved is found and removed, false otherwise.
	// PreCondition: List is not empty.
	// Parameters: toBeRemoved -> the element to be removed from the List.
	bool remove(int toBeRemoved);

	// Description: Empties the List, freeing up dynamically allocated memory.
	// PreCondition: List is not empty.
	void removeAll();

	// Description: Prints the contents of the List from the first to the last element.
	/*
	 * Note that there is some debate about whether or not this type of
	 * method belongs in a class. The argument (briefly) is that a class
	 * shouldn't be responsible for I/O by "displaying" itself as it cannot
	 * foresee how it is to be displayed (in a TUI or GUI environment?).
	 * However, such method eases testing.
	 * For testing purpose, unless required by client in problem statement.
	 * Could also overload operator<<.
	 */
	void printList();

}; // end of header file of List class

/*
 * List.cpp - Implementation of the List class
 *
 * Class Description: A value-oriented unsorted List data collection ADT class.
 *                    Note that this is a link-based implementation
 *                    of a List data collection ADT class.
 *                    Its underlying data structure is
 *                    a singly-headed singly-linked list (SHSL).
 *
 * Creation Date:
 * Author:
 */

#include <string>
#include <iostream>
#include "List.h"


using namespace std; // Needed for cout, cin to be recognized

// Constructors and Destructors

/* Generally, every class that makes use of dynamically allocated memory
 * should have at least two constructors:
 *   a default constructor and
 *   a copy constructor that creates a distinct copy of the given object
 * (even if the client code does not make use of all of these constructors).
 */

// Description: Default constructor
List::List(){
	elementCount = 0;
	head = NULL;

	cout << "List Default constructor" << endl; // For learning purposes!
}


/* Note that the compiler will generate a copy constructor automatically.
 * However, this constructor only creates a SHALLOW COPY (so would only copy the
 * elementCount and head variables). In this case, this would NOT CREATE A
 * NEW LIST object, just a new reference to "this" List object.
 * It is therefore necessary to write a constructor that makes a DEEP COPY
 * if our class makes use of dynamically allocated memory.
 */

/* Also note the parameter. C++ functions use pass-by-value by
 * default. This means that the functions make copies of the given
 * arguments. This is inefficient (particularly for large objects).
 * Therefore it is normal to pass the address, also called the reference,
 * (using &) of the parameter. Also, if the parameter must not be changed,
 * it is good practice to make it const, which prevents it from being changed.
 */
// Description: Copy constructor to copy an existing List object.
List::List(const List& lst){
	if (lst.head == NULL){
		head = NULL;
		elementCount = 0;
	}
	else{
		// Copy first node and assign head
		/* OK, what's with the '->'?  The -> operator accesses the attribute
		 * or method of the object (or struct) that is refererred to by a
		 * pointer.  So "head -> data" is the contents of the data variable
		 * of the object that head points to.  Note that this is synonomous
		 * with "(*head).data" but the latter syntax is ugly and confusing and
		 * is therefore rarely used. */
		head = new Node;
		head->data = lst.head->data;
		/* Now copy the rest of the list.  To do this we'll need to create two
		 * temporary pointers, one to go through the old list, one node at a
		 * time, and one to keep pace in the new list, creating new nodes. */
		Node *pNewNode = head;
		Node *pOldNode = lst.head->next;
		// Repeat until the entire list is copied
		while (pOldNode != NULL){
			pNewNode->next = new Node;
			pNewNode = pNewNode->next;
			pNewNode->data = pOldNode->data;;
			pOldNode = pOldNode->next;
		}
		pNewNode->next = NULL;
		elementCount = lst.elementCount;
	}

	cout << "List Copy constructor" << endl; // For learning purposes!
}

/* The destructor is responsible for deleting any memory that was dynamically
 * allocated by an object. If there is no such memory, no destructor needs to
 * be created (the compiler automatically creates one).
 * Because this class makes use of dynamically allocated memory
 * i.e., uses pointers when new Node objects are instantiated, it is necessary to write
 * a destructor. Destructors are identified by the '~' preceding the class name.
 * There can be only one destructor for a class, and it cannot have parameters.
 */
// Description: Destructor.
List::~List(){
	removeAll();
	cout << "List destructor" << endl; // For learning purposes!
}


/**************************************************************************/
// List Public Interface

// Description: Returns the number of elements in the List.
int List::getElementCount() const {
	return elementCount;
}

// Description: Adds an element (newElement) at the front of the List.
//              Returns true if newElement has been added to the List, false otherwise.
// Parameter: newElement -> the element to be added to the List.
bool List::add(int newElement){
	Node *p = new Node; //temporary node
	bool result = false;

	if ( p != NULL ) {
		// Assign appropriate values to the new node
		p -> data = newElement;
		p -> next = head;
		// Make the head point to the new node
		head = p;
		elementCount++;
		result = true;
	}
	return result;
}

// Description: Removes The first instance of toBeRemoved from the List.
//              Returns true if toBeRemoved is found and removed, false otherwise.
// PreCondition: List is not empty.
// Parameters: toBeRemoved -> the element to be removed from the List.
bool List::remove(int toBeRemoved) {
	Node *p = head;
	Node *temp;
	bool result = false;

	// Is the List empty?
	if (head == NULL) {
		result = false;
	}
	else { // Check to see if toBeRemoved is at the head of the list
	    if (head->data == toBeRemoved){
			head = head->next;
			delete p; //currently assigned head
			elementCount--;
			result = true;
	    }
	    else  { // Otherwise iterate through list
			for ( int i = 0: i < elementCount-1; i++ ) {
				// Check next node for toBeRemoved
				if (p->next->data == toBeRemoved){
					temp = p->next;
					p->next = p->next->next;
					elementCount--;
					delete temp;
					result = true;
				}
				p = p->next;
			}
		}
	}
	return result;
}

// Description: Empties the List, freeing up dynamically allocated memory.
// PreCondition: List is not empty.
void List::removeAll(){
	Node *p = head;
	// Traverse the list deleting nodes
	while (p!= NULL){
		head = head->next; // Mustn't "lose" the next node
		delete p; // De-allocate memory
		p = head; // Go to next node
	}
	head = NULL;
	elementCount = 0;
}

// Description: Prints the contents of the List from the first to the last element.
/*
 * Note that there is some debate about whether or not this type of
 * method belongs in a class. The argument (briefly) is that a class
 * shouldn't be responsible for I/O by "displaying" itself as it cannot
 * foresee how it is to be displayed (in a TUI or GUI environment?).
 * However, such method eases testing.
 * For testing purpose, unless required by client in problem statement.
 * Could also overload operator<<.
 */
void List::printList(){
	Node *p = head;
	cout << "{"; //Nice format!
	// Traverse the list
	while (p != NULL){
		cout << p -> data; // Print data
		p = p -> next; // Go to next Node
		if (p != NULL){
			cout << ","; // Print a comma unless at the end of the list
		}
	}
	cout << "}"; // Don't print a newline - it might not be wanted
}
// end of implementation file of List class
