
#include "qsorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/resource.h>

#define N 1000000

int A[N];

void main () {
    srand(time(NULL));
    int i;
    int pos;
    int tmp;
    struct rusage start;
    struct rusage end;

    getrusage(RUSAGE_SELF, &start);
    A[i] = 0;
    for (i = 1; i < N; i++) {
        A[i] = i / 100;
        pos = (((rand() % 0x7fff) << 16) | (rand() % 0xffff)) % (i+1);
        tmp = A[i];
        A[i] = A[pos];
        A[pos] = tmp;
    }
    getrusage(RUSAGE_SELF, &end);
    int endtime = end.ru_utime.tv_sec*1000000 + end.ru_utime.tv_usec;
    printf("It took %ld microseconds to initialize the array.\n", endtime - start.ru_utime.tv_usec);

    // For Part 2:
    // 
    getrusage(RUSAGE_SELF, &start);
    qsort295_2(A, N);
    getrusage(RUSAGE_SELF, &end);
    endtime = end.ru_utime.tv_sec*1000000 + end.ru_utime.tv_usec;
    printf("It took %ld microseconds to qsort2 the array.\n", endtime - start.ru_utime.tv_usec);
    
}

