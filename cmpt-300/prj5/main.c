#include <stdio.h>
#include "kallocator.h"

void print_memory(int* p[], int count) {
    printf("----PRINTING MEMORY----\n");
    for (int i=0;i<count;i++) {
        if (p[i] != NULL) {
            printf("p[%d] = %p ; *p[%d] = %d\n", i, p[i], i, *(p[i]));   
        }     
    }
}

int main(int argc, char* argv[]) {
    //initialize_allocator(100, FIRST_FIT);
    initialize_allocator(100, BEST_FIT);
    //initialize_allocator(100, WORST_FIT);
    //printf("Using first fit algorithm on memory size 100\n");
    printf("Using best fit algorithm on memory size 100\n");
    //printf("Using worst fit algorithm on memory size 100\n");

    int* p[50] = {NULL};
    for(int i=0; i<30; ++i) {
        p[i] = kalloc(sizeof(int));
        if(p[i] == NULL) {
            printf("Allocation failed\n");
            continue;
        }
        *(p[i]) = i;
        printf("p[%d] = %p ; *p[%d] = %d\n", i, p[i], i, *(p[i]));
    }

    print_statistics();
    print_nodes();

    /*kfree(p[0]);
    p[0] = NULL;
    print_nodes();*/

    /*for(int i=0; i<20; ++i) {
        if(i%2 == 0)
            continue;

        printf("Freeing p[%d]\n", i);
        kfree(p[i]);
        p[i] = NULL;
    }*/

    /*kfree(p[2]);
    p[2] = NULL;
    kfree(p[3]);
    p[3] = NULL;
    // kfree(p[4]);
    // p[4] = NULL;
    kfree(p[7]);
    p[7] = NULL;
    kfree(p[8]);
    p[8] = NULL;
    kfree(p[9]);
    p[9] = NULL;
    print_statistics();
    p[2] = kalloc(sizeof(double));
    *(p[2]) = 2.0;
    p[7] = kalloc(sizeof(double));
    *(p[7]) = 7.0;*/
    kfree(p[24]);
    p[24] = NULL;
    kfree(p[23]);
    p[23] = NULL;
    kfree(p[7]);
    p[7] = NULL;
    kfree(p[5]);
    p[5] = NULL;

    print_memory(p, 30);
    print_nodes();
    print_statistics();

    p[5] = kalloc(sizeof(char));
    *(p[5]) = 'a';

    print_memory(p, 30);
    print_nodes();
    print_statistics();

    /*for (int i=0; i<20; ++i) {
        if (i%3 != 0 || p[i] == NULL)
            continue;
        printf("Freeing p[%d]\n", i);
        kfree(p[i]);
        p[i] = NULL;
    }
    print_memory(p, 30);
    print_nodes();
    print_statistics();
    printf("Allocating p[3] size of double\n");
    p[3] = kalloc(sizeof(double));
    *(p[3]) = 2.0;
    printf("Allocating p[7] size of double\n");
    p[7] = kalloc(sizeof(double));
    *(p[7]) = 7.0;
    print_memory(p, 30);
    print_nodes();
    print_statistics();*/

    printf("available_memory %d\n", available_memory());

    void* before[100] = {NULL};
    void* after[100] = {NULL};
    int count = compact_allocation(before, after);
    for (int i=0;i<count; ++i) {
        p[i] = after[i];
        *(p[i]) = i;
    }

    print_nodes();
    print_memory(p, count);
    print_statistics();

    for (int i=count-1; i>=0; i--) {
        printf("Freeing p[%d]\n", i);
        kfree(p[i]);
        p[i] = NULL;
    }

    print_nodes();
    print_memory(p, count);
    print_statistics();

    // You can assume that the destroy_allocator will always be the 
    // last funciton call of main function to avoid memory leak 
    // before exit

    destroy_allocator();

    return 0;
}
