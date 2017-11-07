int identical( int a[], int b[], unsigned int len ) {
	int i;
	for (i = 0; i < len; i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}
