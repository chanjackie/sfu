
#include <stdio.h>

int sum(int *, int);

#define N 6
int A[N] = {58, 22, 101, 15, 72, 27};

void main () {
    printf("The total is %d.\n", sum(A,6));
    return;
}
