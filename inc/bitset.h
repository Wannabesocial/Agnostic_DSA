/**
 * For this implementation is used a array of size_t and we malloc base on user desire length of bit-set. So exist at least [1,size_t-1] internal fragmentation
**/

#ifndef BITSET_H
#define BITSET_H

#include <stdbool.h>
#include <stdio.h>


typedef struct BitSet {
    size_t *data;    // The array that will store the bit-set
    size_t chunks;   // Count of how many entries has the array
    size_t size;     // Count of existing Bits, can be lower than chunks * size_t
    
    // TODO: Delete
    size_t capacity;
} BitSet;


typedef enum BitSet_Status {
    BITSET_SUCCESS = 0,       // All went well
    BITSET_ERR_ALLOC,         // Memory managment failed (malloc, calloc, realloc)
    BITSET_ERR_NULL_PTR,      // (NULL) pointer argument
    BITSET_ERR_INVALID_SIZE,  // 
    BITSET_ERR_OUT_OF_BOUNDS, // Out of bounds
} BitSet_Status;


/**
 * Create a Bit-Set with a given size
**/
BitSet_Status bitset_create(BitSet **bitset, size_t size);

/**
 * Destroy the Bit-Set
 *
 * Result: BITSET_ERR_NULL_PTR | BITSET_SUCCESS 
**/
BitSet_Status bitset_destroy(BitSet *bitset);

#endif
