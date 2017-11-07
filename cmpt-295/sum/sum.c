
int sum(int *A, int n) {
    int i;
    int total = 0;
    for (i = 0; i < n; i++) {
        total += A[i];
    }
    return total;
}

