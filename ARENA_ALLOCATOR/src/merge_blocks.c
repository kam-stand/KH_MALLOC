#include <stdio.h>
#include <stdlib.h>

typedef struct block block;

struct block {
    size_t size;
    int isFree;
    block *next;
    block *prev;
    char *buff;
};

static block *HEAD = NULL;
static int HEAP_SIZE = 0;

void print_free_list() {
    printf("Free list:\n");
    block *curr = HEAD;
    while (curr != NULL) {
        if (curr->isFree) {
            printf("Block at %p - size: %ld, isFree: %d, next: %p, prev: %p\n", 
                    curr, curr->size, curr->isFree, curr->next, curr->prev);
        }
        curr = curr->next;
    }
    printf("====================\n");
}
void merge_free_blocks(block *curr) {
    // Merge with the next block if it is free
    if (curr->next != NULL && curr->next->isFree) {
        curr->size += sizeof(block) + curr->next->size;  // Add size of the next block + block structure
        curr->next = curr->next->next;  // Remove the next block from the list
        if (curr->next != NULL) {
            curr->next->prev = curr;  // Update the previous pointer of the next block
        }
    }

    // Merge with the previous block if it is free
    if (curr->prev != NULL && curr->prev->isFree) {
        curr->prev->size += sizeof(block) + curr->size;  // Add size of the current block + block structure
        curr->prev->next = curr->next;  // Remove the current block from the list
        if (curr->next != NULL) {
            curr->next->prev = curr->prev;  // Update the previous pointer of the next block
        }
        curr = curr->prev;  // Move the pointer to the merged block (previous block)
    }

    // If the merged block is now at the head, update the HEAD pointer
    if (curr->prev == NULL) {
        HEAD = curr;  // Make sure HEAD points to the merged block
    }
}

void HEAP_FREE(void *ptr) {
    block *curr = HEAD;
    while (curr != NULL) {
        if (curr->buff == ptr) {
            curr->isFree = 1;  // Mark the block as free

            // Try to merge adjacent free blocks
            merge_free_blocks(curr);

            return;
        }
        curr = curr->next;
    }
    printf("Pointer not found in the heap.\n");
}

// Driver function (main) for testing the merge functionality
int main() {
    char HEAP[1000] = {0};


    printf("HEAP begins: %p\n", HEAP);
    printf("HEAP ends: %p\n", HEAP+1000);

    // Initialize the first block
    block *first = (block *)HEAP;
    first->size = 1000 - sizeof(block);
    first->isFree = 1; // Mark as free
    first->next = NULL;
    first->prev = NULL;
    first->buff = (char *)(HEAP + sizeof(block));
    
    printf("HEAP ends_: %p\n", first->buff+first->size);

    if (HEAD == NULL) {
        HEAD = first;
        HEAP_SIZE = first->size; // Set HEAP_SIZE to the size of the first block
    }

    printf("HEAD size: %ld\n", HEAD->size);
    printf("HEAD isFree: %d\n", HEAD->isFree);
    printf("HEAD next: %p\n", HEAD->next);
    printf("HEAD prev: %p\n", HEAD->prev);
    printf("HEAD buff: %p\n", HEAD->buff);
    printf("The current HEAP_SIZE: %d\n", HEAP_SIZE);
    printf("====================\n");






    // Implementing malloc (first allocation)
    printf("Implementing malloc for first allocation\n");

    size_t req1 = 100;
    block *curr = HEAD;

    while (curr) {
        if (curr->isFree && curr->size >= req1 + sizeof(block)) {
            printf("Begins at: %p\n", curr);
            printf("Found available chunk: %p\n", curr->buff);
            break;
        }
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("No suitable chunk found for allocation.\n");
        return 1;
    }

    printf("Before splitting:\n");
    printf("curr size: %ld\n", curr->size);
    printf("curr isFree: %d\n", curr->isFree);
    printf("curr next: %p\n", curr->next);
    printf("curr buff: %p\n", curr->buff);

    // Allocate memory
    size_t remaining = curr->size - req1 - sizeof(block);
    if (remaining > 0) {
        block *b = (block *)((char *)curr + sizeof(block) + req1);
        b->size = remaining;
        b->isFree = 1;
        b->next = curr->next;
        b->prev = curr;
        b->buff = (char *)((char *)b + sizeof(block));

        curr->size = req1;
        curr->isFree = 0;
        curr->next = b;

        printf("New block created:\n");
        printf("b size: %ld\n", b->size);
        printf("b isFree: %d\n", b->isFree);
        printf("b next: %p\n", b->next);
        printf("b prev: %p\n", b->prev);
        printf("b buff: %p\n", b->buff);
    } else {
        printf("Not enough space to create a new block. Allocating entire chunk.\n");
        curr->isFree = 0;
    }

    printf("After first allocation:\n");
    printf("curr size: %ld\n", curr->size);
    printf("curr isFree: %d\n", curr->isFree);
    printf("curr next: %p\n", curr->next);
    printf("curr buff: %p\n", curr->buff);

    print_free_list();

    printf("-----------------------------------------------------\n");

    // Implementing malloc (second allocation)
    printf("Implementing malloc for second allocation\n");

    size_t req2 = 200;
    curr = HEAD;

    while (curr) {
        if (curr->isFree && curr->size >= req2 + sizeof(block)) {
            printf("Found available chunk: %p\n", curr->buff);
            break;
        }
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("No suitable chunk found for second allocation.\n");
        return 1;
    }

    printf("Before splitting:\n");
    printf("curr size: %ld\n", curr->size);
    printf("curr isFree: %d\n", curr->isFree);
    printf("curr next: %p\n", curr->next);
    printf("curr buff: %p\n", curr->buff);

    // Allocate memory for second request
    remaining = curr->size - req2 - sizeof(block);
    if (remaining > 0) {
        block *b = (block *)((char *)curr + sizeof(block) + req2);
        b->size = remaining;
        b->isFree = 1;
        b->next = curr->next;
        b->prev = curr;
        b->buff = (char *)((char *)b + sizeof(block));

        curr->size = req2;
        curr->isFree = 0;
        curr->next = b;

        printf("New block created:\n");
        printf("b size: %ld\n", b->size);
        printf("b isFree: %d\n", b->isFree);
        printf("b next: %p\n", b->next);
        printf("b prev: %p\n", b->prev);
        printf("b buff: %p\n", b->buff);
    } else {
        printf("Not enough space to create a new block. Allocating entire chunk.\n");
        curr->isFree = 0;
    }

    printf("After second allocation:\n");
    printf("curr size: %ld\n", curr->size);
    printf("curr isFree: %d\n", curr->isFree);
    printf("curr next: %p\n", curr->next);
    printf("curr buff: %p\n", curr->buff);

    print_free_list();
    printf("-----------------------------------------------------\n");

    // Freeing all blocks
    printf("Freeing all blocks...\n");
    curr = HEAD;
    while (curr != NULL) {
        printf("Freeing block at: %p\n", curr);
        HEAP_FREE(curr->buff);
        curr = curr->next;
    }

    // Print final free list after all blocks are freed
    printf("Final free list:\n");
    curr = HEAD;
    while (curr != NULL) {
        printf("Block at %p - size: %ld, isFree: %d, next: %p, prev: %p\n", curr, curr->size, curr->isFree, curr->next, curr->prev);
        curr = curr->next;
    }

    return 0;
}
