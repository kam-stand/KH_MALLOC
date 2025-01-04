#include <stdio.h>
#include "mem_lib.h"

int main() {
    mem_init();
    printf("Initial state:\n");
    print_free_list();

    void* ptr1 = kh_malloc(100);
    printf("Allocated ptr1 (100 bytes): %p\n", ptr1);
    print_free_list();

    void* ptr2 = kh_malloc(50);
    printf("Allocated ptr2 (50 bytes): %p\n", ptr2);
    print_free_list();

    void* ptr3 = kh_malloc(200);
    printf("Allocated ptr3 (200 bytes): %p\n", ptr3);
    print_free_list();

    printf("\nFreeing ptr2:\n");
    kh_free(ptr2);
    print_free_list();

    printf("\nFreeing ptr1:\n");
    kh_free(ptr1);
    print_free_list();

    printf("\nAllocating ptr4 (150 bytes):\n");
    void* ptr4 = kh_malloc(150);
    if (ptr4) {
        printf("Allocated ptr4: %p\n", ptr4);
    } else {
        printf("Allocation of ptr4 failed\n");
    }
    print_free_list();

    printf("\nFreeing ptr3:\n");
    kh_free(ptr3);
    print_free_list();

    printf("\nFreeing ptr4:\n");
    kh_free(ptr4);
    print_free_list();

    return 0;
}
