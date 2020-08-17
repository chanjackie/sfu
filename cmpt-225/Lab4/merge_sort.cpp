#include <iostream>
using namespace std;

void mergeSort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int mid1, int high);




// Perform mergeSort to sort an array of integers.
// Inputs:
//   arr is the input array of arrSize integers.
//   low and high are the indices to sort to/from, e.g. 0 arrSize-1 to sort entire array
// Postcondition:
//   arr[low] ... arr[high] will contain the original values, sorted in increasing order.
void mergeSort(int arr[], int low, int high) {
	if (low == high) {
		return;
	}
	int mid = (low + high)/2;
	mergeSort(arr,low,mid);
	mergeSort(arr,mid+1,high);
	merge(arr,low,mid,mid+1,high);
	return;
}


// Perform a merge of two sorted sub-arrays.
// Inputs:
//   arr is the input array on which to perform a merge.
//   low-mid and mid1-high are the two sub-arrays to merge.
// Precondition:
//   arr[low]...arr[mid] is sorted in increasing order.
//   arr[mid1]...arr[high] is sorted in increasing order.
//   These should be disjoint, contiguous sub-arrays too.
// Postcondition:
//   arr[low]...arr[high] is sorted in increasing.
void merge(int arr[], int low, int mid, int mid1, int high) {
	int i,n;
	for (i=low;low<=mid && mid1<=high;i++) {
		if (arr[low] < arr[mid1]) {
			arr[i] = arr[low];
			low++;
		} else if (arr[mid1] <= arr[low]) {
			arr[i] = arr[mid1];
			mid1++;
		}
	}
	if (low<=mid) {
		for (n=low;n<=mid;n++) {
			arr[i] = arr[n];
			i++;
		}
	}
	if (mid1<=high) {
		for (n=mid1;n<=high;n++) {
			arr[i] = arr[n];
			i++;
		}
	}
	return;
}


// A driver program to test mergeSort.
// Reads in a number of integers (number, then sequence of values).
// Sorts using mergeSort.
// Prints the values in sorted order.
int main (void) {
	int n;

	// Get the number of values.
	//	cout << "Enter the number of values to be sorted:" << endl;
	cin >> n;

	// Create array in dynamic memory.
	int *values;
	values = new int[n];

	for (int i=0; i<n; i++) {
		// cout << "Enter a number:" << endl;
		cin >> values[i];
	}

	// Call mergeSort to sort entire array.
	mergeSort(values,0,n-1);

	// Print values, should be sorted.
	for (int i=0; i<n; i++) {
		cout << values[i] << " ";
	}
	cout << endl;


	// Free up memory.  Note use of delete [], since this is an array.
	delete [] values;

	return 0;
}
