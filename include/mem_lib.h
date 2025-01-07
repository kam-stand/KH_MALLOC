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
 * @brief initializes the heap using sbrk() to exactly 1MB
 * 
 * @return void
 */

void HEAP_INIT();

/**
 * @brief grows the heap 
 * !!! MIGHT NOT IMPLEMENT !!!
 */
void HEAP_GROW();

/**
 * @brief Traverses the free list to find the first chunk that is large enough to of size. 
 * 
 * @param req 
 * @return HEAP_CHUNK*
 */
HEAP_CHUNK *FIND_FIT(size_t req);


/**
 * @brief A function that will return the starting region of data for user to use
 * 
 * @param req 
 * @return void* 
 */
void *HEAP_ALLOC(size_t req);

#endif // MEM_LIB_H
