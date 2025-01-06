#include "mem_lib.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static HEAP_CHUNK *HEAD = NULL; // Head of the linked list
static char *HEAP = NULL;  // Pointer to the start of the heap
static size_t HEAP_SIZE = 1024 * 1024; // 1 MB heap size (adjustable)
static void *HEAP_START_ADDR; // starting address of heap
static void *HEAP_END_ADDR; // ending address of heap
#include <sys/mman.h>
#include <unistd.h>
#include "mem_lib.h"

void HEAP_INIT() {
    // Allocate memory using mmap
    HEAP_START_ADDR = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE, 
                           MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (HEAP_START_ADDR == MAP_FAILED) {
        perror("mmap failed");
        return;
    }

    // Calculate and set the end address of the heap
    HEAP_END_ADDR = (char *)HEAP_START_ADDR + HEAP_SIZE;

    // Initialize the first block
    HEAP_CHUNK *first = (HEAP_CHUNK *)HEAP_START_ADDR; 
    first->size = HEAP_SIZE - sizeof(HEAP_CHUNK);
    first->isFree = 1;
    first->next = NULL;
    first->prev = NULL;
    first->buff = ((char *)HEAP_START_ADDR + sizeof(HEAP_CHUNK)); 

    if (HEAD == NULL) {
        HEAD = first;
    }
}




void *HEAP_START(){
    return HEAP_START_ADDR;
}

void *HEAP_END(){
    return HEAP_END_ADDR;
}

HEAP_CHUNK *FIND_FIT(size_t req){

    HEAP_CHUNK *curr = HEAD; // set temp variable
    while (curr)
    {
        if (curr->size >= req && curr->isFree) // if chunk is free and big enough
        {
            printf("CHUNK: %p\n", curr);
            printf("CHUNK->BUFF%p\n", curr->buff);
            return curr;
    
        }
        curr = curr->next; // traverse the list
    }

    return NULL; // No chunk found big enough

}