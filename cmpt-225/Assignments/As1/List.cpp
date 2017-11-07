/*
 * List.cpp
 *
 * Class Description: List data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - Entries are in ascending order according to Care Card Number
 *
 * Created: May 27 2017
 * Author: Jackie Chan and Jacky Cao
 */

#include <iostream>
#include <string>
#include "Patient.h"
#include "List.h"

	using namespace std;


  // Default Constructor
	List::List() {
    elementCount = 0, capacity = 10;
    Patient elements[MAX_ELEMENTS];
  }

	// Description: Returns the total element count currently stored in List.
	int List::getElementCount() const {
    return elementCount;
  }

	// Description: Insert an element.
	// Precondition: newElement must not already be in data collection.
	// Postcondition: newElement inserted and elementCount has been incremented.
	bool List::insert(const Patient& newElement) {
    if ((search(newElement) == NULL && elementCount < capacity) || elementCount == 0) {
      elements[elementCount] = newElement;
      elementCount++;
      return true;
    } else {
      return false;
    }
  }

	// Description: Remove an element.
	// Postcondition: toBeRemoved is removed and elementCount has been decremented.
	bool List::remove( const Patient& toBeRemoved ) {
		if (elementCount == 0) {
			return false;
		}
    if ((search(toBeRemoved)) != NULL) {
      int i;
      for (i=0;i<elementCount;i++) {
        if (elements[i] == toBeRemoved) {
          break;
        }
      }
      for (i=i;i<elementCount-1;i++) {
        elements[i] = elements[i+1];
      }
      elementCount--;
      return true;
    } else {
      return false;
    }
  }

	// Description: Remove all elements.
	void List::removeAll() {
    elementCount = 0;
  }

	// Description: Search for target element.
	//              Returns a pointer to the element if found,
	//              otherwise, returns NULL.
	Patient* List::search(const Patient& target) {
		if (elementCount == 0) {
			return NULL;
		}
    int i;
    for (i=0;i<capacity;i++) {
      if (elements[i] == target) {
        Patient* found = &elements[i];
        return found;
      }
    }
    return NULL;
  }

	// Description: Prints all elements stored in List.
	void List::printList( ) {
		if (elementCount == 0) {
			return;
		}
    int i,n,index = -1;
    string min = "99999999999";
    string prevmin = "0";
    for (i=0;i<elementCount;i++) {
      for (n=0;n<elementCount;n++) {
        if (elements[n].getCareCard() < min && elements[n].getCareCard() > prevmin) {
          min = elements[n].getCareCard();
          index = n;
        }
      }
      elements[index].printPatient();
      prevmin = min;
      min = "99999999999";
    }
  }
