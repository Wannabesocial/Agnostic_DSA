#include "bitset.h"
#include <stdlib.h>
#include <limits.h>

#define BITS_SIZE_T (sizeof(size_t) * CHAR_BIT)


BitSet_Status bitset_create(BitSet **bitset, size_t size)
{
    if(bitset == NULL){
        return BITSET_ERR_NULL_PTR;
    }

    if(size == 0){
        return BITSET_ERR_INVALID_SIZE;
    }

    BitSet *bs = (BitSet *) malloc(sizeof(BitSet));
    if(bs == NULL){
        return BITSET_ERR_ALLOC;
    }

    bs->size   = size;
    bs->chunks = (size % BITS_SIZE_T == 0)
        ? (size / BITS_SIZE_T)
        : (size / BITS_SIZE_T) + 1;
    
    bs->capacity = bs->chunks * BITS_SIZE_T; // TODO: DELETE

    bs->data   = (size_t *) malloc(bs->chunks * sizeof(size_t));
    if(bs->data == NULL){
        free(bs);
        return BITSET_ERR_ALLOC;
    }

    *bitset = bs; 
    return BITSET_SUCCESS;
}


BitSet_Status bitset_destroy(BitSet *bitset)
{
    if(bitset == NULL){
        return BITSET_ERR_NULL_PTR;
    }

    free(bitset->data);
    free(bitset);

    return BITSET_SUCCESS;
}
