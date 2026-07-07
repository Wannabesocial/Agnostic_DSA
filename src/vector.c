#include "vector.h"

#include <string.h>
#include <stdlib.h>

#pragma region Constructor
Vector_Status vector_create_default(Vector *vector, const u32 elem_size){

    // Invalid user Input
    if(vector == NULL) { return VECTOR_ERR_NULL_PTR; }
    if(elem_size == 0) { return VECTOR_ERR_INVALID_SIZE; }

    // Save values of Data Structure
    vector->elem_size = elem_size;
    vector->capacity  = DEFAULT_CAPACITY;
    vector->length    = 0;
    vector->data      = malloc((u64)vector->elem_size * vector->capacity);

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
    vector->data      = malloc((u64)vector->elem_size * vector->capacity);

    if(vector->data == NULL) { return VECTOR_ERR_ALLOC; }

    return VECTOR_SUCCESS;
}
#pragma endregion

#pragma region Destractor
Vector_Status vector_destroy(Vector *vector, void (* destroy_func)(void *)){

    // Invalid user Input
    if(vector == NULL) { return VECTOR_ERR_NULL_PTR; }

    // No more dealocation needed. Only defaul
    if(destroy_func == NULL) { goto default_dealloc; }

    // Dealocate base on user function
    char *raw_data = (char *) vector->data;
    for(u32 i = 0; i < vector->length; i++) {
        destroy_func((void *)(raw_data + (u64)i * vector->elem_size));
    }

default_dealloc:
    free(vector->data);
    vector->data      = NULL;
    vector->capacity  = 0;
    vector->length    = 0;
    vector->elem_size = 0;
    return VECTOR_SUCCESS;
}
#pragma endregion

#pragma region Modifiers
/**
 * @brief Helpfull for growing the vector when `capacity` == `length`
 * @param vector Is never `NULL`
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_ALLOC
*/
static Vector_Status vector_growth(Vector *vector){

    void *temp = NULL;

    vector->capacity = (vector->capacity > (UINT32_MAX >> 1))
        ? UINT32_MAX             // Canot double (overflow). (cap * 2 > MAX)
        : vector->capacity << 1; // Double the capacity

    // Realoc with the new capacity
    temp = realloc(vector->data, (u64)vector->capacity * vector->elem_size);
    if(temp == NULL) { return VECTOR_ERR_ALLOC; }

    vector->data = temp;
    return VECTOR_SUCCESS;
}

Vector_Status vector_push_back(Vector *vector, void *value){

    Vector_Status status;
    char *raw_data;

    // Invalid User Input
    if(vector == NULL || value == NULL) { return VECTOR_ERR_NULL_PTR; }

    // Need to regrowth
    if(vector->capacity == vector->length){

        // Max Capacity already reached
        if(vector->capacity == UINT32_MAX) { return VECTOR_ERR_MAX_CAPACITY; }

        status = vector_growth(vector);

        // Something went wrong in growth
        if(status != VECTOR_SUCCESS) { return status; }
    }

    // No need to regrowth
    raw_data = (char *) vector->data;
    memcpy(raw_data + (u64)vector->length * vector->elem_size, value, vector->elem_size);
    vector->length++;
    return VECTOR_SUCCESS;
}

Vector_Status vector_clear(Vector *vector, void (* destroy_func)(void *)){

    // Invalid user Input
    if(vector == NULL) { return VECTOR_ERR_NULL_PTR; }

    // No dealocate needed
    if(destroy_func == NULL) { goto reset_metadata; }

    // Dealocate base on user function
    char *raw_data = (char *)vector->data;
    for(u32 i = 0; i < vector->length; i++){
        destroy_func((void *)(raw_data + (u64)i * vector->elem_size));
    }

reset_metadata:
    vector->length = 0;
    return VECTOR_SUCCESS;
}
#pragma endregion

#pragma region Capacity
inline bool vector_empty(const Vector *vector){
    return ( vector->length == 0 ) ? true : false;
}
#pragma endregion

