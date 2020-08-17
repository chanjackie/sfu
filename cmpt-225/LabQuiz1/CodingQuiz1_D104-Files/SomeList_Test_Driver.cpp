/*
 * SomeList_Test_Driver.cpp
 *
 * Date: July 2017
 *
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include "SomeList.h"
#include "Event.h"

using namespace std;


int main () {
  string aLine = "";
  int time = 0;
  int length = 0;


  // Create an empty SomeList for the events
  SomeList* mySomeList = new SomeList();

  // Testing insertEven
  cout << "TESTING insertEven" << endl;
  // Create and add arrival events to mySomeList
  while(getline(cin, aLine)) {   // while (there is data)
    stringstream ss(aLine);
    ss >> time >> length;      // Get next arrival time (time) and transaction time (length)  
    // cout << "Read: " << time << " " << length << endl;  // For debugging purposes
    Event newArrivalEvent(Event::ARRIVAL, time, length);
    // cout << "Event: " << newArrivalEvent << endl;  // For debugging purposes
  	mySomeList->insertEven(newArrivalEvent);
  	cout << "Printing mySomeList : " << endl; // For debugging purposes
  	cout << *mySomeList << endl; // For debugging purposes
  }


  return 0;
}