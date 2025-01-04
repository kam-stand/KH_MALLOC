#ifndef MEM_LIB_H
#define MEM_LIB_H

#include <stddef.h>


typedef struct HEAP_CHUNK { 
    size_t size; 
    struct HEAP_CHUNK *next; 
    struct HEAP_CHUNK *prev; 
    int alloc; 
} HEAP_CHUNK;

/**
 * @brief Initializes the heap used for memory allocation using sbrk()
 * @param void - nothing
 * @return void
 */
void mem_init();

/**
 * @brief Finding the size needed to align with ize of heap
 * 
 * @param align_request 
 * @return size_t 
 */
size_t align_request(size_t align_request);


/**
 * @brief Splits the current block by size by the requested alloc amount
 * 
 * @param alloc 
 * @param curr 
 * @return HEAP_CHUNK* 
 */
HEAP_CHUNK *split_block(size_t alloc, HEAP_CHUNK *curr);


/**
 * @brief Prints the size , prev and next address of each free node
 * 
 * @param free_list 
 */
void print_free_list();


/**
 * @brief will allocate space on the heap aligned to the heap size
 * 
 * @param size 
 * @return void* 
 */
void *kh_malloc(size_t size);

/**
 * @brief Increases the heap using sbrk() and add into free_list
 *  
 * @return void 
 */
void mem_increase();


/**
 * @brief Merge two adjacent blocks that are not allocated
 * 
 */
void coalesce_blocks();

/**
 * @brief Takes in a pointer and will allocate it as free
 * 
 * @param ptr 
 */
void kh_free(void *ptr);

/**
 * @brief Sorting the free list
 * 
 */

void sort_free_list();
#endif // MEM_LIB_H
