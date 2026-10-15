#include "bitset.h"
#include <stdio.h>



int main()
{
    BitSet *bs = NULL;

    bitset_create(&bs, 100);
    {
        printf("Chunks: %lu\n", bs->chunks);
        printf("Capacity: %lu\n", bs->capacity);
        printf("Size: %lu\n", bs->size);
    }
    bitset_destroy(bs);
}
