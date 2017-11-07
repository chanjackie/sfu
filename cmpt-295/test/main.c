#include <stdio.h>

long sum(long *A, int n);

int x = 6;
long y[6] = {27, 72, 15, 101, 22, 58};

void main() {
    printf("The sum of %ld, %ld, %ld, %ld, %ld, %ld is %ld.\n", y[0], y[1], y[2], y[3], y[4], y[5], sum(y,x));
    return;
}