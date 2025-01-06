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

int main() {
    char HEAP[1000] = {0};

    printf("HEAP begins: %p\n", HEAP);

    // Initialize the first block
    block *first = (block *)HEAP;
    first->size = 1000 - sizeof(block);
    first->isFree = 1; // Mark as free
    first->next = NULL;
    first->prev = NULL;
    first->buff = (char *)(HEAP + sizeof(block));

    if (HEAD == NULL) {
        HEAD = first;
        HEAP_SIZE = first->size; // Set HEAP_SIZE to the size of the first block
    }

    printf("HEAD size: %ld\n", HEAD->size);
    printf("HEAD isFree: %d\n", HEAD->isFree);
    printf("HEAD next: %p\n", HEAD->next);
    printf("HEAD prev: %p\n", HEAD->prev);
    printf("HEAD buff: %p\n", HEAD->buff);
    printf("HEAD buff - sizeof(block): %p\n", (HEAD->buff - sizeof(block)));
    printf("The current HEAP_SIZE: %d\n", HEAP_SIZE);
    printf("====================\n");

    // Implementing malloc
    printf("Implementing malloc\n");

    size_t req = 100;
    block *curr = HEAD;

    while (curr) {
        if (curr->isFree && curr->size >= req + sizeof(block)) {
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
    size_t remaining = curr->size - req - sizeof(block);
    if (remaining > 0) {
        block *b = (block *)((char *)curr + sizeof(block) + req);
        b->size = remaining;
        b->isFree = 1;
        b->next = curr->next;
        b->prev = curr;
        b->buff = (char *)((char *)b + sizeof(block));

        curr->size = req;
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

    printf("After allocation:\n");
    printf("curr size: %ld\n", curr->size);
    printf("curr isFree: %d\n", curr->isFree);
    printf("curr next: %p\n", curr->next);
    printf("curr buff: %p\n", curr->buff);

    return 0;
}
