

// original:  - return total via return value
int sum_rolled(int *A, int n) {
    int total = 0;
    int i;
    for (i = 0; i < n; i++) {
        total += A[i];
    }
    return total;
}


// new version:  - return total via reference
//               - a bug may result if result in A[]
void sum_rolled(int *A, int n, int *result) {
    int i;
    for (i = 0; i < n; i++) {
        *result += A[i];
    }
}


// new version (better):  - no memory aliasing
void sum_rolled(int *A, int n, int *result) {
    int total = 0;
    int i;
    for (i = 0; i < n; i++) {
        total += A[i];
    }
    *result = total;
}


