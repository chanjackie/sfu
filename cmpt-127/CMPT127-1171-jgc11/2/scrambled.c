int scrambled( unsigned int a[], unsigned int b[], unsigned int len ) {
	int i;
	int c[100] = {0};
	for (i=0;i<len;i++) {
		int k;
		for (k=0;k<len;k++) {
			c[a[k]]++;
		}
		for (k=0;k<len;k++) {
			c[b[k]]--;
		}
		for (k=0;k<100;k++) {
			if (c[k] != 0) {
				return 0;
			}
		}
	}
	return 1;
}
