
#include <stdio.h>

char dot_prod(void *A, void *B, int n, int i, int j);

#define N 4

char A[N][N] = { 3,  0,  1,  4,
                -5,  1, -1,  0,
                 0,  0,  1,  2,
                -2,  0,  7,  3};

char B[N][N] = { 2, -1,  2, -2,
                 2, -5, -4,  2,
                -1, -1,  5,  0,
                -1,  2, -2, -1};


char C[N][N];

/*char D[N][N] = { 1,   4,   3, -10,
                -7,   1, -19,  12,
                -3,   3,   1,  -2,
               -14,   1,  25,   1};
*/

void print_matrix(void *A, int n);


void main () {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = dot_prod(A, B, N, i, j);
        }
    }

    print_matrix(A, N);
    print_matrix(B, N);
    print_matrix(C, N);
 //   print_matrix(D, N);
    return;
}


void print_matrix(void *A, int n) {
    int i, j;
    char val;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            val = *((char*)(A + i*n + j));
            printf("%4d", val);
        }
        putchar('\n');
    }
    putchar('\n');
}

