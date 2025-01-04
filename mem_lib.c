#include "mem_lib.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#define HEAP_SIZE (1024)

static HEAP_CHUNK *free_list;

#define ALIGNMENT 8

void print_free_list() {
    HEAP_CHUNK *temp = free_list;
    if (!temp) {
        printf("Free list is empty.\n");
        return;
    }

    printf("Free list:\n");
    printf("----------------------------------------------------------\n");
    printf("|   Address    |    Size    | Allocated |   Prev   |   Next   |\n");
    printf("----------------------------------------------------------\n");
    while (temp) {
        printf("| %p | %10lu | %10d | %p | %p |\n", 
               (void *)temp, temp->size, temp->alloc, 
               (void *)temp->prev, (void *)temp->next);
        temp = temp->next;
    }
    printf("----------------------------------------------------------\n");
}


void mem_init() {
    void *init_break = sbrk(0); 
    void *current_break = sbrk(HEAP_SIZE); 

    // Create the first free block
    HEAP_CHUNK *free_block = (HEAP_CHUNK *)current_break; 
    free_block->size = HEAP_SIZE; 
    free_block->alloc = 0; 
    free_block->next = NULL; 
    free_block->prev = NULL; 

    free_list = free_block; // Assign the newly created block to free_list
}

size_t align_request(size_t size){
    size_t remainder =  size % ALIGNMENT;
    size_t padding = ALIGNMENT - remainder;
    size_t align = size + padding;
    size_t alloc = align + sizeof(HEAP_CHUNK);

    return alloc;


}

HEAP_CHUNK *split_block(size_t alloc, HEAP_CHUNK *curr){
    size_t remaining_size = curr->size - alloc;
    HEAP_CHUNK* new_free_block = (HEAP_CHUNK*)((char*)curr + alloc);

    new_free_block->size = remaining_size;
    new_free_block->next=NULL;
    new_free_block->prev=NULL;
    new_free_block->alloc=0;

    return new_free_block;
}




void mem_increase() {
    // Increment the heap by HEAP_SIZE
    void *curr_break = sbrk(0);   // Current program break
    void *incr_break = sbrk(HEAP_SIZE);

    if (incr_break == (void *)-1) {
        perror("sbrk failed");    // Handle allocation failure
        return;
    }

    // Cast the new break to a HEAP_CHUNK
    HEAP_CHUNK *new_free_block = (HEAP_CHUNK *)incr_break;
    new_free_block->size = HEAP_SIZE;
    new_free_block->alloc = 0;
    new_free_block->next = NULL;
    new_free_block->prev = NULL;

    // Attach to the end of the free list
    HEAP_CHUNK *curr = free_list;
    if (!curr) {
        // If free_list is empty, make this the first block
        free_list = new_free_block;
    } else {
        // Traverse to the end of the list
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new_free_block;
        new_free_block->prev = curr;
    }
}











void *kh_malloc(size_t size){

    size_t alloc = align_request(size);

    HEAP_CHUNK *curr = free_list; // setting a temp head to the current free_list

    while (curr->next) { // iterating over the free list
        if (curr->size >= size + sizeof(HEAP_CHUNK) && curr->alloc == 0) {
            break; // we found the heap_chunk with proper allocation
        }
        curr=curr->next;
    }

     // If no suitable block found, request more memory from the system (e.g., using sbrk)
    if (!curr) { 
        // Handle allocation failure (e.g., no free space, sbrk failed)
        printf("Increasing heap...\n");
        mem_increase();
        return kh_malloc(size);
    }

    if (curr->size > alloc) {
        HEAP_CHUNK* new_free_block = split_block(alloc, curr);

        // Update pointers for double-linked list
        new_free_block->next = curr; 
        new_free_block->prev = curr->prev; 

        if (curr->prev) {
            curr->prev->next = new_free_block; 
        } else { 
            free_list = new_free_block; // Update head if splitting the first block
        }

        curr->prev = new_free_block; 
    }

    curr->alloc = 1;

    return (void *)((char*)curr + sizeof(HEAP_CHUNK));

}