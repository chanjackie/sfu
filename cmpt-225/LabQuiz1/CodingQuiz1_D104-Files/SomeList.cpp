/* 
 * SomeList.cpp
 *
 * Description: Array-based implementation of a SomeList collection ADT.
 *
 * Class Invariant: SomeList is always sorted.
 * 
 * Date: July 2017
 *
 */  

#include "SomeList.h"  // Header file

  
// Default Constructor
SomeList::SomeList() {
   elementCount = 0;
} // end of default constructor


// Description: Returns "true" is this SomeList is empty, otherwise "false".
// Time Efficiency: O(1)
bool SomeList::isEmpty() const {
   return ( elementCount == 0 );
}  // end isEmpty

// Description: Inserts newElement only if the element is even.
//              When a newElement is inserted, it is inserted in descending sort order.
//              It returns "true" if the newElement was inserted, otherwise it returns "false".   
// Postcondition: Once newElement is inserted, this SomeList remains sorted.  
// Time Efficiency: O(n)      
bool SomeList::insertEven(const Event& newElement) {
	bool ableToInsert = false;
    // Feel free to add more variable declarations

 
        // To be completed!



	return ableToInsert;

} // end insertEven


// ... more methods

// For Testing Purposes
// Description: Prints the content of rhs. 
ostream& operator<<(ostream & os, const SomeList& rhs) {
	
	// Traverse SomeList
	for ( unsigned int index = 0; index < rhs.elementCount; index++ )
		cout << rhs.elements[index].getTime() << " " ; // Print data
	
	return os;
} // end of operator <<

//  End of implementation file.