#include <stdio.h>
#include "mem_lib.h"

int main() {
    mem_init();

    void* ptr1 = kh_malloc(100);
    printf("Allocated ptr1: %p\n", ptr1); 

    void* ptr2 = kh_malloc(50);
    printf("Allocated ptr2: %p\n", ptr2);

    void* ptr3 = kh_malloc(200);
    printf("Allocated ptr3: %p\n", ptr3);

    print_free_list(); 


    return 0;
}