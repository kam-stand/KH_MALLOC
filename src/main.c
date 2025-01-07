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

    printf("------------------------------------------------\n");

   void *ptr = HEAP_ALLOC(100);

   void *ptr2 = HEAP_ALLOC(100);

    print_free_list();
   return 0;
}