void reverse( int arr[], unsigned int len ) {
	int i;
	int stop = (len/2);
	for (i=0; i<stop; i++) {
		int l = arr[i];
		arr[i] = arr[len - (i+1)];
		arr[len - (i+1)] = l;
	}
	return;
}
