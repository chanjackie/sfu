/*
 * List Test Driver
 *
 * Author:
 * Date:
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Profile.h"
#include "ListADT.h"

using namespace std;



int main() {

  // Variables declaration
  // ListADT* members = new ListADT();
  ListADT* test = new ListADT();
  test->remove(0);
  cout << "Cool" << endl;
  test->remove(1);
  Profile* juggy = new Profile("Juggy");
  cout << test->insert(2, *juggy) << endl;
  cout << test->insert(1, *juggy) << endl;
  cout << test->getElementCount() << endl;
  cout << test->insert(2, *juggy) << endl;
  cout << test->insert(1, *juggy) << endl;
  cout << test->getElementCount() << endl;
  Profile copy = test->getElement(3);
  cout << copy.getName() << endl;
  cout << test->getElement(2).getName() << endl;
  cout << *test << endl;
  Profile* jackie = new Profile("Jackie");
  test->setElement(3, *jackie);
  cout << test->getElement(3).getName() << endl;
  cout << copy.getName() << endl;
  cout << *test << endl;
  cout << "Testing...Testing...1..2..3! Is this mic on?" << endl;
  test->remove(1);
  cout << *test << endl;
  test->remove(2);
  cout << *test << endl;
  cout << test->getElementCount() << endl;
  delete test;
  cout << "dang" << endl;
  cout << *test;
  test->remove(1);


  return 0;
}
