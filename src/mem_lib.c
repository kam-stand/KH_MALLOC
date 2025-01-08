#include "../include/mem_lib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  printf("\n");
}

HEAP_CHUNK *FIND_FIT(size_t req) {
  HEAP_CHUNK *curr = HEAD;
  HEAP_CHUNK *best_fit = NULL;

  while (curr) {
    if (curr->size >= req + sizeof(HEAP_CHUNK) && curr->isFree) {
      if (best_fit == NULL || curr->size < best_fit->size) {
        best_fit = curr;
      }
    } else if (curr->size == req && curr->isFree) {
      // If a perfect fit is found, return immediately
      return curr;
    }
    curr = curr->next;
  }
  return best_fit;
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

void MERGE_CHUNKS(HEAP_CHUNK *curr) {
  printf("Merging chunks: current=%p, prev=%p, next=%p\n", curr, curr->prev,
         curr->next);

  if (curr == NULL)
    return;

  // Merge with the next block if it is free
  if (curr->next != NULL && curr->next->isFree) {
    HEAP_CHUNK *next_chunk = curr->next;
    curr->size += sizeof(HEAP_CHUNK) + next_chunk->size;
    curr->next = next_chunk->next; // Update the next pointer
    if (next_chunk->next != NULL) {
      next_chunk->next->prev = curr;
    }
  }

  // Merge with the previous block if it is free
  if (curr->prev != NULL && curr->prev->isFree) {
    HEAP_CHUNK *prev_chunk = curr->prev;
    prev_chunk->size += sizeof(HEAP_CHUNK) + curr->size;
    prev_chunk->next = curr->next;
    if (curr->next != NULL) {
      curr->next->prev = prev_chunk;
    }
    curr = prev_chunk;
  }

  // Update HEAD if necessary
  if (curr->prev == NULL) {
    HEAD = curr;
  }
}

void *HEAP_ALLOC(size_t req) {
  if (req <= 0 || req > HEAP_SIZE) // make sure size
  {
    printf("Cannot allocate size <= 0 or size >= PAGE_SIZE\n");
    return NULL;
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
  if (ptr == NULL) {
    return; // Do nothing if ptr is NULL
  }

  // Calculate the chunk pointer from the user-provided pointer
  HEAP_CHUNK *chunk = (HEAP_CHUNK *)ptr - 1;

  if (chunk < (HEAP_CHUNK *)HEAP_START_ADDR ||
      chunk > (HEAP_CHUNK *)HEAP_END_ADDR) {
    printf("Invalid pointer passed to HEAP_FREE.\n");
    return; // Check for invalid pointer
  }

  chunk->isFree = 1;

  // Merge adjacent free chunks
  MERGE_CHUNKS(chunk);

  return;
}

void *HEAP_CALLOC(size_t n_elements, size_t element_size) {
  size_t total_size = n_elements * element_size;

  // Allocate memory
  HEAP_CHUNK *chunk = malloc(sizeof(HEAP_CHUNK) + total_size);
  if (chunk == NULL) {
    // Allocation failed
    return NULL;
  }

  // Assuming `buff` is at the end of HEAP_CHUNK structure
  void *buffer = (void *)((char *)chunk + sizeof(HEAP_CHUNK));

  // Initialize memory to zero using a loop
  for (size_t i = 0; i < total_size; i++) {
    ((unsigned char *)buffer)[i] = 0;
  }

  return buffer;
}

void *HEAP_REALLOC(void *ptr, size_t req) {
  if (ptr == NULL && req > 0) {
    return HEAP_ALLOC(req);
  }

  HEAP_CHUNK *curr = (HEAP_CHUNK *)ptr - 1;

  if (curr->size >= req) {
    return curr;
  }

  void *new_ptr = HEAP_ALLOC(req);
  if (new_ptr == NULL) {
    return NULL;
  }

  // Copy data manually
  char *src = (char *)ptr;
  char *dest = (char *)new_ptr;
  for (size_t i = 0; i < curr->size; i++) {
    *dest++ = *src++;
  }

  // Free the original chunk correctly
  HEAP_FREE(ptr);

  return new_ptr;
}