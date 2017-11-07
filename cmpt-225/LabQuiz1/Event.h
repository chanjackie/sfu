/*
 * Event.h
 * 
 * Description: Models arrival or departure event.
 * 
 * Class Invariant: Arrival events have type 'A'
 * 					Departure event have type 'D'
 * 
 * Author: AL
 * Date of last modification: July 2017
 */

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Event {

private:
	char type;             // Arrival or Departure event
	int time;              // Time at which the customer arrived at 
	                       // or departed from the bank
	int length;            // Processing time - Only used for Arrival events
	
public:
	static const char ARRIVAL = 'A';
	static const char DEPARTURE = 'D';

	// Constructor
	Event();
	Event(char type, int time);
	Event(char type, int time, int length);

    // Getters
    char getType() const;
    int getTime() const;
    int getLength() const;

    // Setters
    void setType(char aType);
    void setTime(int aTime);
    void setLength(int aLength);

	// Description: Return true if this event is an arrival event, false otherwise.
	bool isArrival() const ;
	// Description: Return true if this event's time has an odd value (e.g., 21), false otherwise.
	bool isOdd() const;
	
	// Overloaded Operators
	// Description: Returns "true" if "this" < "rhs", "false" otherwise.
	bool operator<(const Event& rhs);
    // Description: Returns "true" if "this" > "rhs", "false" otherwise.
	bool operator>(const Event& rhs);
	// Description: Returns "true" if "this" == "rhs", "false" otherwise.
	bool operator==(const Event& rhs);

	// For Testing Purposes
	// Description: Prints the content of "this". 
	friend ostream& operator<<(ostream & os, const Event& rhs);

}; // end of Event.h