/*
 * WICPS.cpp
 *
 * File Description: Main interface of walk-in clinic patient system.
 *                   Allows user to:
 *                    - Enter patients into the system.
 *                    - Remove patients from the system.
 *                    - Search for patient records.
 *                    - Modify a patient's record.
 *                    - Print all patients by ascending order of care card numbers.
 *
 * Created: May 27 2017
 * Author: Jackie Chan and Jacky Cao
 */


#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <new>
#include "Patient.h"
#include "List.h"

using namespace std;

int main() {
  List *clinic = new List();
  cout << endl << "Welcome to the Walk-in Clinic Patient System" << endl;
  string input;
  string cNumber, name, address, phone, email;
  while (1) {
    cout << endl << "Main Menu: " << endl << endl;
    cout << "What would you like to do?" << endl;
    cout << " (1) Enter a new patient into the system" << endl;
    cout << " (2) Remove a patient from the system" << endl;
    cout << " (3) Search for a patient" << endl;
    cout << " (4) Modify a patient's record" << endl;
    cout << " (5) Print all patients by ascending order of care card numbers" << endl;
    cout << " (6) Exit the program" << endl << endl;
    cout << "Your choice: ";
    getline(cin,input);
    if (input == "1") {
        cout << "Care Card Number: ";
        getline(cin,cNumber);
        Patient pat(cNumber);
        cout << "Name: ";
        if(getline(cin,name) && name != "")
          pat.setName(name);
        cout << "Address: ";
        if(getline(cin,address) && address != "")
          pat.setAddress(address);
        cout << "Phone Number: ";
        if(getline(cin,phone) && phone != "")
          pat.setPhone(phone);
        cout << "Email Address: ";
        if(getline(cin,email) && email != "")
          pat.setEmail(email);
        if (clinic->insert(pat)) {
          cout << "Complete! Press enter to continue.";
          cin.ignore();
        } else {
          cout << "Care Card Number already registered, or system is full. Press enter to continue";
          cin.ignore();
        }
    } else if (input == "2") {
      cout << "Care Card Number to remove: ";
      getline(cin,cNumber);
      if (cNumber.length() == 10) {
        Patient pat(cNumber);
        if (clinic->remove(pat)) {
          cout << "Success! Press enter to continue.";
          cin.ignore();
        } else {
          cout << "Care Card Number not in system. Press enter to continue.";
          cin.ignore();
        }
      } else {
        cout << "Invalid Care Card Number. Press enter to continue.";
        cin.ignore();
      }
    } else if (input == "3") {
      cout << "Care Card Number to search for: ";
      getline(cin,cNumber);
      if (cNumber.length() == 10) {
        Patient pat(cNumber);
        if (clinic->search(pat) != NULL) {
          clinic->search(pat)->printPatient();
          cout << "Press enter to continue.";
          cin.ignore();
        } else {
          cout << "Care Care Number not in system. Press enter to continue.";
          cin.ignore();
        }
      } else {
        cout << "Invalid Care Card Number. Press enter to continue.";
        cin.ignore();
      }
    } else if (input == "4") {
      cout << "Care Card Number to modify: ";
      getline(cin,cNumber);
      if (cNumber.length() == 10) {
        Patient pat(cNumber);
        if (clinic->search(pat) != NULL) {
          Patient* modify = clinic->search(pat);
          cout << "Name: ";
          if(getline(cin,name) && name != "")
            modify->setName(name);
          cout << "Address: ";
          if(getline(cin,address) && address != "")
            modify->setAddress(address);
          cout << "Phone Number: ";
          if(getline(cin,phone) && phone != "")
            modify->setPhone(phone);
          cout << "Email Address: ";
          if(getline(cin,email) && email != "")
            modify->setEmail(email);
          cout << "Complete! Press enter to continue.";
          cin.ignore();
        } else {
          cout << "Care Card Number not in system. Press enter to continue.";
          cin.ignore();
        }
      } else {
        cout << "Invalid Care Card Number. Press enter to continue.";
        cin.ignore();
      }
    } else if (input == "5") {
      clinic->printList();
      cout << "List printed. Press enter to continue.";
      cin.ignore();
    } else if (input == "6") {
      cout << "Goodbye!" << endl;
      delete clinic;
      return 0;
    } else {
      cout << "Invalid input." << endl;
    }

  }

}
