#include "mem_lib.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static HEAP_CHUNK *HEAD = NULL; // Head of the linked list
static char *HEAP = NULL;  // Pointer to the start of the heap
static size_t HEAP_SIZE = 1024 * 1024; // 1 MB heap size (adjustable)
static void *HEAP_START_ADDR; // starting address of heap
static void *HEAP_END_ADDR; // ending address of heap

void HEAP_INIT(){

    // get the starting address(current program break)
    HEAP_START_ADDR = sbrk(0);
    
    void *increment_heap = sbrk(HEAP_SIZE); // increment by 1MB

    if (increment_heap == (void *)-1) {
        perror("SBRK did nto work");
        return;
    }
    // set the ending address of heap to the new program break
    HEAP_END_ADDR = increment_heap;

    //Initialize the first block
    HEAP_CHUNK *first = (HEAP_CHUNK *)HEAP_START_ADDR; // set to the starting address of heap
    first->size = HEAP_SIZE - sizeof(HEAP_CHUNK); // set the size of the first free 
    first->isFree = 1; // mark as free
    first->next = NULL; // next is null
    first->prev = NULL; // prev is null
    first->buff =((char *)HEAP_START_ADDR + sizeof(HEAP_CHUNK)); // this is where the data starts

    if (HEAD == NULL) // must check if head is null because then we will assign it as such
    {
        HEAD = first;
        return;
    }

    return;

}

void *HEAP_START(){
    return HEAP_START_ADDR;
}

void *HEAP_END(){
    return HEAP_END_ADDR;
}