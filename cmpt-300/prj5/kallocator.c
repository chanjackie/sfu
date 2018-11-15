#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "kallocator.h"
#include "list.h"

struct KAllocator {
    enum allocation_algorithm aalgorithm;
    int size;
    void* memory;
    struct nodeStruct *allocated;
    struct nodeStruct *free;
    // Some other data members you want, 
    // such as lists to record allocated/free memory
};

struct KAllocator kallocator;

void initialize_allocator(int _size, enum allocation_algorithm _aalgorithm) {
    assert(_size > 0);
    kallocator.aalgorithm = _aalgorithm;
    kallocator.size = _size;
    kallocator.memory = malloc((size_t)kallocator.size);
    kallocator.free = List_createNode(kallocator.memory, kallocator.size);
    // Add some other initialization 
}

void destroy_allocator() {
    free(kallocator.memory);
    struct nodeStruct *allocated = kallocator.allocated;
    struct nodeStruct *freeNode = kallocator.free;
    while (allocated != NULL) {
        struct nodeStruct *node = allocated;
        allocated = allocated->next;
        free(node);
    }
    while (freeNode != NULL) {
        struct nodeStruct *node = freeNode;
        freeNode = freeNode->next;
        free(node);
    }

    // free other dynamic allocated memory to avoid memory leak
}

void* kalloc(int _size) {
    void* ptr = NULL;
    struct nodeStruct *free = kallocator.free;
    struct nodeStruct *allocated = kallocator.allocated;
    if (free == NULL) {
        return NULL;
    }
    if (kallocator.aalgorithm == FIRST_FIT) {
        while(free->size < _size) {
            if (free->next != NULL) {                
                free = free->next;
            } else {
                printf("No free space large enough to fit allocation request available.\n");
                return ptr;
            }
        }
        
    } else if (kallocator.aalgorithm == BEST_FIT) {
        int smallest_fit = kallocator.size + 1;
        void *address_of_fit = NULL;
        while(free != NULL) {
            if (free->size >= _size && free->size<smallest_fit) {
                smallest_fit = free->size;
                address_of_fit = free->address;
            }
            free = free->next;
        }
        if (address_of_fit == NULL) {
            return ptr;
        }
        free = List_findNode(kallocator.free, address_of_fit);
    } else if (kallocator.aalgorithm == WORST_FIT) {
        int biggest_fit = 0;
        void *address_of_fit = NULL;
        while(free != NULL) {
            if (free->size >= _size && free->size>biggest_fit) {
                biggest_fit = free->size;
                address_of_fit = free->address;
            }
            free = free->next;
        }
        if (address_of_fit == NULL) {
            return ptr;
        }
        free = List_findNode(kallocator.free, address_of_fit);
    }
    struct nodeStruct *newAllocation = List_createNode(free->address, _size);
    if (newAllocation == NULL) {
        return NULL;
    }
    if (allocated == NULL) {
        kallocator.allocated = newAllocation;
    } else {
        /*while (allocated->next != NULL && allocated->address < newAllocation->address && allocated->next->address < newAllocation->address) {
            allocated = allocated->next;
        }*/
        newAllocation->next = allocated->next;
        allocated->next = newAllocation;
        List_sort(&kallocator.allocated);
    }
    ptr = newAllocation->address;
    if (_size == free->size) {
        List_deleteNode(&kallocator.free, free);
    } else {
        free->address = free->address + _size;
        free->size -= _size;
    }

    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory

    return ptr;
}

void kfree(void* _ptr) {
    assert(_ptr != NULL);
    struct nodeStruct *allocated = List_findNode(kallocator.allocated, _ptr);
    struct nodeStruct *free = kallocator.free;
    if (free == NULL) {
        free = List_createNode(_ptr, allocated->size);
        kallocator.free = free;
        List_deleteNode(&kallocator.allocated, allocated);
        return;
    }
    while (free->next != NULL) {
        if (free->address < _ptr && free->next->address < _ptr) {
            free = free->next;
        } else {
            break;
        }
    }
    if (free->address < _ptr) {
        if ((free->address + free->size) == _ptr) {
            free->size += allocated->size;
        } else {
            struct nodeStruct *newFreeChunk = List_createNode(_ptr, allocated->size);
            if (newFreeChunk != NULL) {
                newFreeChunk->next = free->next;
                free->next = newFreeChunk;
            }
        }
    } else {        
        struct nodeStruct *newFreeChunk = List_createNode(_ptr, allocated->size);
        newFreeChunk->next = free;
        kallocator.free = newFreeChunk;
    }
    free = kallocator.free;
    while (free->next != NULL) {
        if ((free->address + free->size) == free->next->address) {
            free->size += free->next->size;
            List_deleteNode(&kallocator.free, free->next);
        }
        if (free->next != NULL) {            
            free = free->next;
        }
    }

    List_deleteNode(&kallocator.allocated, allocated);    
}

int compact_allocation(void** _before, void** _after) {
    int compacted_size = 0;

    // compact allocated memory
    // update _before, _after and compacted_size
    struct nodeStruct *allocatedHead = kallocator.allocated;
    struct nodeStruct *freeHead = kallocator.free;
    if (allocatedHead == NULL) {
        return 0;
    }
    if (freeHead == NULL) {
        while (allocatedHead != NULL) {
            _before[compacted_size] = allocatedHead->address;
            _after[compacted_size] = allocatedHead->address;
            allocatedHead = allocatedHead->next;
            compacted_size++;
        }
        return compacted_size;
    }
    while (freeHead != NULL) {
        if (allocatedHead != NULL && allocatedHead->address == (freeHead->address + freeHead->size)) {
            _before[compacted_size] = allocatedHead->address;
            allocatedHead->address = freeHead->address;
            freeHead->address += allocatedHead->size;
            _after[compacted_size] = allocatedHead->address;
            allocatedHead = allocatedHead->next;
            compacted_size++;
        } else {
            if (freeHead->next == NULL) {
                break;
            } else if ((freeHead->address + freeHead->size) == freeHead->next->address) {
                freeHead->size += freeHead->next->size;
                List_deleteNode(&kallocator.free, freeHead->next);
            } else if (allocatedHead != NULL) {
                _before[compacted_size] = allocatedHead->address;
                _after[compacted_size] = allocatedHead->address;
                allocatedHead = allocatedHead->next;
                compacted_size++;
            }
        }
    }
    printf("Finished compacting, compacted_size: %d\n", compacted_size);
    return compacted_size;
}

int available_memory() {
    int available_memory_size = 0;
    // Calculate available memory size
    struct nodeStruct *free = kallocator.free;
    while (free != NULL) {
        available_memory_size += free->size;
        free = free->next;
    }
    return available_memory_size;
}

void print_statistics() {
    int allocated_size = 0;
    int allocated_chunks = 0;
    int free_size = 0;
    int free_chunks = 0;
    int smallest_free_chunk_size = kallocator.size;
    int largest_free_chunk_size = 0;

    struct nodeStruct *allocated = kallocator.allocated;
    struct nodeStruct *free = kallocator.free;


    // Calculate the statistics
    while (allocated != NULL) {
        allocated_size += allocated->size;
        allocated_chunks++;
        allocated = allocated->next;
    }
    if (free == NULL) {
        smallest_free_chunk_size = 0;
    } else {        
        while (free != NULL) {
            free_chunks++;
            free_size += free->size;
            if (free->size < smallest_free_chunk_size) {
                smallest_free_chunk_size = free->size;
            }
            if (free->size > largest_free_chunk_size) {
                largest_free_chunk_size = free->size;
            }
            free = free->next;
        }
    }

    printf("Allocated size = %d\n", allocated_size);
    printf("Allocated chunks = %d\n", allocated_chunks);
    printf("Free size = %d\n", free_size);
    printf("Free chunks = %d\n", free_chunks);
    printf("Largest free chunk size = %d\n", largest_free_chunk_size);
    printf("Smallest free chunk size = %d\n", smallest_free_chunk_size);
}

void print_nodes() {
    printf("----PRINTING NODES----\n");
    struct nodeStruct *allocated = kallocator.allocated;
    struct nodeStruct *free = kallocator.free;
    while (allocated != NULL) {
        printf("allocated address: %p, size: %d\n", allocated->address, allocated->size);
        allocated = allocated->next;
    }
    while (free != NULL) {
        printf("free address: %p, size: %d\n", free->address, free->size);
        free = free->next;
    }
}

