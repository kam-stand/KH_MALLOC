#include "kh_malloc.h"
#include <stddef.h>
#include <stdio.h>



static HEAP_CHUNK *head = NULL; // represents the head of the free_list we will add/remove from


void add_block(HEAP_CHUNK *block){
    // check if head is null
    if(head == NULL)
    {
        head = block;
        head->next = NULL;
        head->prev = NULL;
    }

    // if head is not null traverse list to append at end(tail)
    HEAP_CHUNK *curr = head; // set temp to head of free list
    while (curr) {
        curr = curr->next; // traversing 
    }

    // now at the tail of the list adding block as tail
    curr->next = block;
    block->prev = curr;
    block->next = NULL;

    return;


}

void *scan_free_list(size_t size){
    HEAP_CHUNK *curr = head; // setting a temp variable to the head of the list
    while (curr) {
        if (curr->isFree == TRUE && curr->size >= size) {
            printf("Free %ld bytes HEAP_CHUNK found in free list.\n", curr->size);
            return curr;
        }
        curr = curr->next;
    }

    printf("No memory found in mem pool with block size %ld.\n", size);
    return NULL;
}


void resize_heap_chunk(HEAP_CHUNK *block, size_t size){
    
}