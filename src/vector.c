#include "vector.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>



// ===========================================================================
// ===------------------------ Constractor Section ------------------------=== 
// ===========================================================================

Vector_Status vector_create_default(Vector **vector, size_t elem_size)
{
    // Invalid user Input
    if(vector == NULL || *vector != NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    if(elem_size == 0){
        return VECTOR_ERR_INVALID_SIZE;
    }

    // Bytes to malloc overflow
    if(elem_size > SIZE_MAX / DEFAULT_CAPACITY){
        return VECTOR_ERR_OVERFLOW; 
    }

    Vector *v = (Vector *) malloc(sizeof(Vector));
    if(v == NULL){
        return VECTOR_ERR_ALLOC;
    }

    // Save values of Data Structure
    v->elem_size = elem_size;
    v->capacity  = DEFAULT_CAPACITY;
    v->length    = 0;
    v->data      = malloc(v->elem_size * v->capacity);
    if(v->data == NULL)
    {
        free(v);
        return VECTOR_ERR_ALLOC;
    }

    *vector = v;
    return VECTOR_SUCCESS;
}


Vector_Status vector_create_reserve(Vector **vector, size_t elem_size, size_t capacity)
{
    // Invalid user Input
    if(vector == NULL || *vector != NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    if(elem_size == 0 || capacity == 0){
        return VECTOR_ERR_INVALID_SIZE;
    }

    // Bytes to malloc overflow
    if(elem_size > SIZE_MAX / capacity){
        return VECTOR_ERR_OVERFLOW;
    }

    Vector *v = (Vector *) malloc(sizeof(Vector));
    if(v == NULL){
        return VECTOR_ERR_ALLOC;
    }

    // Save values of Data Structure
    v->elem_size = elem_size;
    v->capacity  = capacity;
    v->length    = 0;
    v->data      = malloc(v->elem_size * v->capacity);
    if(v->data == NULL)
    {
        free(v);
        return VECTOR_ERR_ALLOC;
    }

    *vector = v;
    return VECTOR_SUCCESS;
}



// ==========================================================================
// ===---------------------- Destractor Section --------------------------===
// ==========================================================================

Vector_Status vector_destroy(Vector **vector)
{
    // Invalid user Input
    if(vector == NULL || *vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    // Dealocate the Data and the Data Structure
    Vector *v = *vector;

    free(v->data);
    free(v);
    *vector = NULL;

    return VECTOR_SUCCESS;
}



// ===========================================================================
// ===------------------------ Modifiers Section --------------------------===
// ===========================================================================

/**
 * Helpfull for growing the vector when `capacity` == `length`
 * 
 * Param:
 *  `vector` Is never `NULL`.
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_ALLOC | VECTOR_ERR_OVERFLOW 
*/
static Vector_Status vector_growth(Vector *vector)
{
// TODO: (In Feature) If overflow take a smaller value for length so you do not have that
// If canot realloc with better value take a even smaller value for lenght 

    size_t new_capacity = (vector->capacity > (SIZE_MAX >> 1))
        ? SIZE_MAX               // Canot double (overflow). (cap * 2 > MAX)
        : vector->capacity << 1; // Double the capacity
 
    if(new_capacity > SIZE_MAX / vector->elem_size){
        return VECTOR_ERR_OVERFLOW;
    }

    // Realoc with the new capacity
    void *temp = realloc(vector->data, new_capacity * vector->elem_size);
    if(temp == NULL){
        return VECTOR_ERR_ALLOC;
    }

    // Save the new Data
    vector->capacity = new_capacity;
    vector->data     = temp;
    return VECTOR_SUCCESS;
}


Vector_Status vector_push_back(Vector *vector, const void *in_value)
{
    // Invalid User Input
    if(vector == NULL || in_value == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    // Need to regrowth
    if(vector->capacity == vector->length)
    {
        // Max Capacity already reached
        if(vector->capacity == SIZE_MAX){
            return VECTOR_ERR_MAX_CAPACITY;
        }

        Vector_Status status = vector_growth(vector);
        if(status != VECTOR_SUCCESS){
            return status;
        }
    }

    // No need to regrowth
    char *base = (char *)vector->data;
    memcpy(base + vector->length * vector->elem_size, in_value, vector->elem_size);
    vector->length++;

    return VECTOR_SUCCESS;
}


Vector_Status vector_pop_back(Vector *vector, void *out_value)
{
    // Invalid User Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    // Empty Vector
    if(vector_empty(vector) == true){
        return VECTOR_ERR_EMPTY;
    }

    vector->length--;

    // Do not care about result
    if(out_value == NULL){
        return VECTOR_SUCCESS;
    }

    // Pop the last value and save it.
    char *base = (char *)vector->data;
    memcpy(out_value, base + vector->length * vector->elem_size, vector->elem_size);

    return VECTOR_SUCCESS;
}


Vector_Status vector_clear(Vector *vector)
{
    // Invalid user Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    vector->length = 0;
    return VECTOR_SUCCESS;
}


// ===========================================================================
// ===------------------------ Capacity Section ---------------------------===
// ===========================================================================

bool vector_empty(const Vector *vector)
{
    // Invalid Input
    if(vector == NULL){
        return true;
    }
    return (vector->length == 0) ? true : false;
}


size_t vector_length(const Vector *vector)
{
    return (vector == NULL) ? 0 : vector->length;
}



// ==========================================================================
// ===----------------------- Element Access -----------------------------===
// ==========================================================================

void *vector_data(const Vector *vector)
{
    return (vector == NULL) ? NULL : vector->data;
}
