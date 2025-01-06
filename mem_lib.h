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

#endif // MEM_LIB_H
