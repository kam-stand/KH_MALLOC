#include "../../include/mem_lib.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#define TEST_CASE(MSG) printf("=================TEST CASE: %s============================\n", MSG);
int main(void) {
  void *initial_break = sbrk(0); // Get initial program break
  HEAP_INIT();

  printf("HEAP START: %p\n", HEAP_START());
  printf("HEAP END: %p\n", HEAP_END());

  size_t heap_size_diff = (size_t)((char *)HEAP_END() - (char *)HEAP_START());

  if (heap_size_diff == (size_t)(1024 * 1024)) {
    printf("Heap size difference is correct: %zu bytes\n", heap_size_diff);
  } else {
    printf("Heap size difference is incorrect. Expected: %zu bytes, Actual: "
           "%zu bytes\n",
           (size_t)(1024 * 1024), heap_size_diff);
  }

  print_free_list();

  // TEST_CASE("ALLOCATE ONE BLOCK")
  // void *ptr = HEAP_ALLOC(100);
  // print_free_list();
  // TEST_CASE("FREE PTR")
  // HEAP_FREE(ptr);
  // print_free_list();
  TEST_CASE("PERFECT FIT")
  void *ptr1 = HEAP_ALLOC(300);
  void *ptr2 = HEAP_ALLOC(200);
  void *ptr3 = NULL;
  print_free_list();

  HEAP_FREE(ptr1);

  print_free_list();
  ptr3 = HEAP_ALLOC(150);
  print_free_list();
}