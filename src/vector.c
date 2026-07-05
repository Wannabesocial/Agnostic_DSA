#include "vector.h"
#include <stdlib.h>

Vector_Status vector_create_default(Vector *vector, const u32 elem_size){

    // Invalid user Input
    if(vector == NULL) { return VECTOR_ERR_NULL_PTR; }
    if(elem_size == 0) { return VECTOR_ERR_INVALID_SIZE; }

    // Save values of Data Structure
    vector->elem_size = elem_size;
    vector->capacity  = DEFAULT_CAPACITY;
    vector->length    = 0;
    vector->data      = malloc((size_t)vector->elem_size * vector->capacity);

    if(vector->data == NULL) { return VECTOR_ERR_ALLOC; }

    return VECTOR_SUCCESS;
}

Vector_Status vector_create_reserve(Vector *vector, const u32 elem_size, const u32 capacity){

    // Invalid user Input
    if(vector == NULL) { return VECTOR_ERR_NULL_PTR; }
    if(elem_size == 0 || capacity == 0) { return VECTOR_ERR_INVALID_SIZE; }

    // Save values of Data Structure
    vector->elem_size = elem_size;
    vector->capacity  = capacity;
    vector->length    = 0;
    vector->data      = malloc((size_t)vector->elem_size * vector->capacity);

    if(vector->data == NULL) { return VECTOR_ERR_ALLOC; }

    return VECTOR_SUCCESS;
}

Vector_Status vector_destroy(Vector *vector, void (* destroy_func)(void *)){

    // Invalid user Input
    if(vector == NULL) { return VECTOR_ERR_NULL_PTR; }

    // No more dealocation needed. Olny defaul
    if(destroy_func == NULL) { goto default_dealloc; }

    // Dealocate base on user function
    char *raw_data = (char *) vector->data;
    for(u32 i = 0; i < vector->length; i++) {
        destroy_func((void *)(raw_data + i * vector->elem_size));
    }

default_dealloc:
    free(vector->data);
    vector->data      = NULL;
    vector->capacity  = 0;
    vector->length    = 0;
    vector->elem_size = 0;
    return VECTOR_SUCCESS;
}

inline bool vector_empty(const Vector *vector){
    return ( vector->length == 0 ) ? true : false;
}
