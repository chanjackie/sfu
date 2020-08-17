#include <iostream>
#include <new>
using namespace std;

int sumArray(int arr[], int arrSize) {
  int sum = 0;
  for (int i=0;i<arrSize;i++) {
    sum += arr[i];
  }
  return sum;
}

int main() {
  int size = 0;
  int index = 0;
  int * sumarr;
  cout << "How many numbers would you like to sum? ";
  cin >> size;
  sumarr = new int[size];
  if (sumarr != NULL) {
    for (index = 0;index<size;index++) {
      cout << "Please enter a number: ";
      cin >> sumarr[index];
    }
  } else {
    return 0;
  }
  int total = sumArray(sumarr, size);
  cout << "The sum of the numbers you provided is: " << total << endl;
  delete[] sumarr;
  return total;
}
