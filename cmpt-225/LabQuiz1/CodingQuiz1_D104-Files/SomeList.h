/* 
 * SomeList.h
 *
 * Description: Array-based implementation of a SomeList collection ADT.
 *
 * Class Invariant: SomeList is always sorted.
 * 
 * Date: July 2017
 *
 */

#pragma once

#include <iostream>
#include "Event.h"

using namespace std;


class SomeList {

private:
	static const int CAPACITY = 100;   // Capacity of array 
	Event elements[CAPACITY];          // Data collection 
	int elementCount;                  // Current count of elements


   
public:
   // Default Constructor
   SomeList();
 
   // Description: Returns "true" is SomeList is empty, otherwise "false".
   // Time Efficiency: O(1)
   bool isEmpty() const;
   

	// Description: Inserts newElement only if the element is even.
	//              When a newElement is inserted, it is inserted in descending sort order.
	//              It returns "true" if the newElement was inserted, otherwise it returns "false".   
	// Postcondition: Once newElement is inserted, this SomeList remains sorted.  
	// Time Efficiency: O(n)         
	bool insertEven(const Event& newElement);
      
// ... more methods

   // For Testing Purposes - See Labs 3 and 4.
   // Description: Prints the content of "this". 
   friend ostream & operator<<(ostream & os, const SomeList& rhs); 

   
}; // end SomeList