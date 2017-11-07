#include <iostream>
#include <new>
#include "circle.h"
using namespace std;

void printArray(Circle * arr, int arrSize, int eleCount) {
  int index = 0;
  for (index = 0;index<arrSize;index++) {
    if (index < eleCount) {
      Circle c = arr[index];
      cout << "Circle at index " << index << " has ";
      c.displayCircle();
    } else {
      cout << "Cell at index " << index << " is empty." << endl;
    }
  }
  return;
}

int main() {
  int size = 0;
  int index = 0;
  int x,y;
  double radius;
  Circle * circarr;
  cout << "How large do you want the array to be? ";
  cin >> size;
  circarr = new Circle[size];
  if (circarr != NULL) {
    for (index = 0;index<size;index++) {
      cout << "Please enter an x,y coordinate and a radius: ";
      cin >> x >> y >> radius;
      if (cin.eof() || !cin.good())
        break;
      Circle c = Circle(x,y,radius);
      circarr[index] = c;
    }
  } else {
    return 1;
  }
  cout << "The capacity of the array is: " << size << endl;
  cout << "The number of Circle objects in the array is: " << index << endl;
  cout << "The number of empty cells in the array is: " << size-index << endl;
  printArray(circarr, size, index);
  delete[] circarr;
  return 0;
}
