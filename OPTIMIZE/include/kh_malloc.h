

#ifndef KH_MALLOC_H
#define KH_MALLOC_H
#include <stddef.h>


/**
 * @brief An Enum to indicate whether a HEAP_CHUNK is free in heap or not
 * 
 */
typedef enum
{
    FALSE,
    TRUE
} Boolean;



/**
 * @brief A struct representing a chunk of memory in our heap
 * 
 */

typedef struct HEAP_CHUNK { 
    size_t size;
    Boolean isFree;
    struct HEAP_CHUNK *next; 
    struct HEAP_CHUNK *prev; 
} HEAP_CHUNK;

#define PAGE_SIZE sysconf(_SC_PAGESIZE)
#define MEM_ALLOC_LOT_SIZE (1 * PAGE_SIZE)
#define MEM_DEALLOC_LOT_SIZE (2 * PAGE_SIZE)

#define HEADER_SIZE (size_of(HEAP_CHUNK))
#define WRITABLE_AREA(p) (((HEADER_SIZE *)p) + 1)
#define HEADER_AREA(p) (((HEAP_CHUNK *)p) - 1)

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

/**
 * @brief 
 * 
 * @param block 
 */
void remove_block(HEAP_CHUNK *block);

/**
 * @brief Adds a block to the free_list
 * 
 * @param block 
 */
void add_block(HEAP_CHUNK *block);

/**
 * @brief Searching free file for the right fit
 * 
 * @param size 
 * @return void* 
 */
void *scan_free_list(size_t size);

/**
 * @brief 
 * 
 * @param req 
 * @return void* 
 */
void *kh_malloc(size_t req);


/**
 * @brief 
 * 
 * @param ptr 
 * @return void* 
 */
void *kh_free(void *ptr);







#endif