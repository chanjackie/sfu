
#include <stdio.h>

int dot_prod(void *A, void *B, int n, int i, int j);

#define N 4

char A[N][N] = { 32, -15,  38, -26,
                -52, 112, -27,  38,
                 52, -33,  64, -22,
                -22,  62, -44,  13};

char B[N][N] = { 27,  54,  -89, -18,
                 12,  36, -100,  25,
                -23,  28,   57,  46,
                 -6, -14,  107,   7};

char C[N][N];


void main () {
    int i, j, k;

    for (i = 0, k = 0xc; i < N; i++) {
        for (j = 0; j < N; j++) {
            int res;
            int OF;

            res = dot_prod(A, B, N, i, j);
            asm volatile (
                "movl %%edx, %0\n\t"
                : "=r" (OF)
                :
                : "rdx"
                );
    
            if (OF) {
                printf(" of", k--);
            } else {
                printf(" %2X", res & 0xff);
            }
        }
        putchar('\n');
    }
    putchar('\n');

    if (!k) puts("Well done!");

    return;
}
