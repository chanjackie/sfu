
#include <stdio.h>
#include <string.h>

int str_alnum(char *s);

#define N 750
#define NTESTS 20

char A[NTESTS][N];
int cycles[NTESTS];
int P;
long total;
int start_time = 150;
int end_time = 125;
char *tst;

void main () {
    int i;

    for (i = 0; i < NTESTS; i++) {
        tst = fgets(A[i], N, stdin);
        A[i][strlen(A[i])-1] = 0;
    }
    for (i = 0; i < NTESTS; i++) {
        asm volatile (
            "cpuid\n\t"
            "rdtscp\n\t"
            "movl %%eax, %0\n\t"
            : "=r" (start_time)
            : 
            : "rax", "rbx", "rcx", "rdx"
        );

        //P[i] = sum_rolled(A, N);
        P = str_alnum(A[i]);

        asm volatile (
            "cpuid\n\t"
            "rdtscp\n\t"
            "movl %%eax, %0\n\t"
            : "=r" (end_time)
            : 
            : "rax", "rbx", "rcx", "rdx"
        );

        cycles[i] = end_time - start_time;
        if (cycles[i] >= 10000) { i--; continue; }
        if (P != 1) {
            perror("Error:  bad run"); return;
        }
    }

    total = 0;
    for (i = 0; i < NTESTS; i++) {
        printf("Sample %d (%ld) completed in %d cycles.\n", i+1, strlen(A[i]), cycles[i]);
        total += cycles[i];
    }
    printf("Average of %ld cycles.\n", total/NTESTS);

    return;
}

