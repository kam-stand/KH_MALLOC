#include "../include/mem_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define TODO(msg) printf("TODO: %s\n", msg);

static HEAP_CHUNK *HEAD = NULL;        // Head of the linked list
static char *HEAP = NULL;              // Pointer to the start of the heap
static size_t HEAP_SIZE = 1024 * 1024; // 1 MB heap size (adjustable)
static void *HEAP_START_ADDR;          // starting address of heap
static void *HEAP_END_ADDR;            // ending address of heap

void HEAP_INIT() {
  // Allocate memory using mmap
  HEAP_START_ADDR = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE,
                         MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

  if (HEAP_START_ADDR == MAP_FAILED) {
    perror("mmap failed");
    return;
  }

  // Calculate and set the end address of the heap
  HEAP_END_ADDR = (char *)HEAP_START_ADDR + HEAP_SIZE;

  // Initialize the first block
  HEAP_CHUNK *first = (HEAP_CHUNK *)HEAP_START_ADDR;
  first->size = HEAP_SIZE - sizeof(HEAP_CHUNK);
  first->isFree = 1;
  first->next = NULL;
  first->prev = NULL;
  first->buff = ((char *)HEAP_START_ADDR + sizeof(HEAP_CHUNK));

  if (HEAD == NULL) {
    HEAD = first;
  }
}

void *HEAP_START() { return HEAP_START_ADDR; }

void *HEAP_END() { return HEAP_END_ADDR; }

void HEAP_GROW() {
  TODO("INCREMENT THE HEAP_END ADDRESS BY HEAP_SIZE")
  TODO("CHANGE THE SIZE OF THE HEAD OF FREE LIST")
}

void print_free_list() {
  printf("==============================================\n");
  printf("Free List:\n");

  HEAP_CHUNK *temp = HEAD;
  while (temp) {
    printf("Chunk: %p, Size: %ld, Next: %p, IsFree: %s\n", temp, temp->size,
           temp->next, temp->isFree ? "Yes" : "No");
    temp = temp->next;
  }

  printf("==============================================\n");
}

HEAP_CHUNK *FIND_FIT(size_t req) {
  HEAP_CHUNK *curr = HEAD;
  HEAP_CHUNK *best_fit = NULL;

  while (curr) {
    if (curr->size == req && curr->isFree) {
      return curr; // Perfect fit found
    } else if (curr->size >= req && curr->isFree) {
      if (best_fit == NULL || curr->size < best_fit->size) {
        best_fit = curr;
      }
    }
    curr = curr->next;
  }
  return best_fit; // Return the best-fit chunk if no perfect fit found
}
HEAP_CHUNK *SPLIT_CHUNK(HEAP_CHUNK *chunk, size_t req) {
  if (chunk->size > req + sizeof(HEAP_CHUNK)) {
    size_t remaining_size = chunk->size - req - sizeof(HEAP_CHUNK);

    // Create a new chunk for the remaining space
    HEAP_CHUNK *new_chunk =
        (HEAP_CHUNK *)((char *)chunk + req + sizeof(HEAP_CHUNK));
    new_chunk->size = remaining_size;
    new_chunk->isFree = 1;
    new_chunk->buff = (char *)new_chunk + sizeof(HEAP_CHUNK);

    // Update the current chunk
    chunk->size = req + sizeof(HEAP_CHUNK);
    chunk->isFree = 0;
    chunk->buff = (char *)chunk + sizeof(HEAP_CHUNK);

    // Update next/prev pointers
    new_chunk->next = chunk->next;
    new_chunk->prev = chunk;
    if (chunk->next) {
      chunk->next->prev = new_chunk;
    }
    chunk->next = new_chunk;

    return chunk;
  }
  return NULL;
}

void *HEAP_ALLOC(size_t req) {
  if (req <= 0 || req > HEAP_SIZE) // make sure size
  {
    printf("Cannot allocate size <= 0 or size >= PAGE_SIZE\n");
    return NULL;
  }

  HEAP_CHUNK *temp = HEAD;
  while (temp) {
    if (temp->size == req) {
      printf("FOUND PERFECT SIZE %p\n", temp);
      TODO("MUST REIMPLEMENT LOGIC FOR FIND_FIT(SIZE_T REQ).\nCURRENTLY DOES NOT GET EXACT REQ SIZE.\nMUST ALSO CHANGE LOGIC TO SEE IF PERFECT FIT IS MINIMUM")
      break;
    }
    temp = temp->next;
  }

  HEAP_CHUNK *chunk = FIND_FIT(req); // try to find the first fit
  if (chunk == NULL) {
    TODO("INCREASE SIZE OF THE HEAP");
    HEAP_GROW();
  }

  chunk = SPLIT_CHUNK(chunk, req);
  if (chunk != NULL) {
    return (void *)chunk->buff;
  }

  return NULL; // return null if cannot split or out of memory
}

void HEAP_FREE(void *ptr) {
  TODO("MUST IMPLEMENT FREE")
  return;
}