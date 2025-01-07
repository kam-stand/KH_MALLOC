#include <stddef.h>
#include <stdio.h>
#include "../include/mem_lib.h"
#include <unistd.h>

int main() {
   void *initial_break = sbrk(0); // Get initial program break
   HEAP_INIT(); 

   printf("HEAP START: %p\n", HEAP_START());
   printf("HEAP END: %p\n", HEAP_END());

    size_t heap_size_diff = (size_t)((char*)HEAP_END() - (char*)HEAP_START());

    if (heap_size_diff == (size_t)(1024 * 1024))
    {
        printf("Heap size difference is correct: %zu bytes\n", heap_size_diff);
    } 
    else 
    {
        printf("Heap size difference is incorrect. Expected: %zu bytes, Actual: %zu bytes\n", 
        (size_t)(1024 * 1024), heap_size_diff);
    }

    printf("n");
    printf("Heap initialized.\n");
    print_free_list();

    // Test Case 1: Single Block, No Merge
    printf("\n=== Test Case 1: Single Block, No Merge ===\n");
    void *ptr1 = HEAP_ALLOC(256);
    printf("Allocated block: %p\n", ptr1);
    HEAP_FREE(ptr1);
    print_free_list();

    // Test Case 2: Two Adjacent Free Blocks
    printf("\n=== Test Case 2: Two Adjacent Free Blocks ===\n");
    ptr1 = HEAP_ALLOC(256);
    void *ptr2 = HEAP_ALLOC(256);
    printf("Allocated blocks: %p, %p\n", ptr1, ptr2);
    HEAP_FREE(ptr1);
    HEAP_FREE(ptr2);
    print_free_list();

    // Test Case 3: Free Block Between Two Allocated Blocks
    printf("\n=== Test Case 3: Free Block Between Two Allocated Blocks ===\n");
    ptr1 = HEAP_ALLOC(256);
    ptr2 = HEAP_ALLOC(256);
    void *ptr3 = HEAP_ALLOC(256);
    printf("Allocated blocks: %p, %p, %p\n", ptr1, ptr2, ptr3);
    HEAP_FREE(ptr2); // Free the middle block
    print_free_list();

    // Test Case 4: Multiple Adjacent Free Blocks
    printf("\n=== Test Case 4: Multiple Adjacent Free Blocks ===\n");
    HEAP_FREE(ptr1);
    HEAP_FREE(ptr3);
    print_free_list();

    // Test Case 5: Free First and Last Block
    printf("\n=== Test Case 5: Free First and Last Block ===\n");
    ptr1 = HEAP_ALLOC(512);
    ptr2 = HEAP_ALLOC(512);
    void *ptr4 = HEAP_ALLOC(512);
    printf("Allocated blocks: %p, %p, %p\n", ptr1, ptr2, ptr4);
    HEAP_FREE(ptr1);
    HEAP_FREE(ptr4);
    print_free_list();


   return 0;
}