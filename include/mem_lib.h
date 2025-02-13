#ifndef MEM_LIB_H
#define MEM_LIB_H

#include <stddef.h>


typedef struct HEAP_CHUNK { 
    size_t size; 
    struct HEAP_CHUNK *next; 
    struct HEAP_CHUNK *prev; 
    int isFree;
    char *buff;
} HEAP_CHUNK;

/**
 * @brief Returns the starting address of the heap 
 * 
 * @return void* 
 */
void *HEAP_START();

/**
 * @brief Returns the ending address of the heap
 * 
 * @return void* 
 */
void *HEAP_END();

/**
 * @brief initializes the heap using MMAP() to exactly 1MB
 * 
 * @return void
 */

void HEAP_INIT();

/**
 * @brief grows the heap TODO(!!!)
 * 
 */
void HEAP_GROW();

/**
 * @brief prints free list
 * 
 */
void print_free_list();


/**
 * @brief Traverses the free list to find the first chunk that is large enough to of size. 
 * 
 * @param req 
 * @return HEAP_CHUNK*
 */
HEAP_CHUNK *FIND_FIT(size_t req);


/**
 * @brief Takes a pointer to a heap chunk to split from requested size and return
 * 
 * @param chunk 
 * @param req 
 * @return HEAP_CHUNK* 
 */
HEAP_CHUNK *SPLIT_CHUNK(HEAP_CHUNK *chunk, size_t req);


/**
 * @brief Will merge adjacent chunks, next and free, that is passed in
 * 
 * @param chunk 
 */
void MERGE_CHUNKS(HEAP_CHUNK *curr);

/**
 * @brief A function that will return the starting region of data for user to use
 * 
 * @param req 
 * @return void* 
 */
void *HEAP_ALLOC(size_t req);


/**
 * @brief Given an allocated pointer it return it to the heap
 * 
 * @param ptr 
 * @return void* 
 */
void HEAP_FREE(void *ptr);


/**
 * @brief Creates an unallocated array of space of n elements of with size of n. all elements set to 0
 * 
 * @param n_elements 
 * @param elements 
 * @return void* 
 */
void *HEAP_CALLOC(size_t n_elements, size_t element);

/**
 * @brief Deallocate old pointer and return pointer to new chunk of specified size
 * 
 * @param ptr 
 * @param req 
 * @return void* 
 */
void *HEAP_REALLOC(void *ptr, size_t req);
#endif // MEM_LIB_H
