#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define __DEVELOPMENT_VECTOR__
#include "vector.h"

// ===========================================================================
// ===------------------------ Constractor Section ------------------------=== 
// ===========================================================================

Vector_Status vector_create_default(Vector **vector, size_t elem_size)
{
    // Invalid user Input
    if(vector == NULL){
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
    if(vector == NULL){
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

Vector_Status vector_destroy(Vector *vector)
{
    // Invalid user Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    // Dealocate the Data and the Data Structure
    free(vector->data);
    free(vector);

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


#if 1 == 0
Vector_Status vector_clear(Vector *vector)
{
    // Invalid user Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    vector->length = 0;
    return VECTOR_SUCCESS;
}
#endif


Vector_Status vector_resize(Vector *vector, size_t new_size)
{
    // Invalid Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    // No need to realloc
    if(new_size < vector->length)
    {
        vector->length = new_size;
        return VECTOR_SUCCESS;
    }

    // Need to Realloc and Overflows
    if(new_size > SIZE_MAX / vector->elem_size){
        return VECTOR_ERR_OVERFLOW;
    }

    void *temp = realloc(vector->data, new_size * vector->elem_size);
    if(temp == NULL){
        return VECTOR_ERR_ALLOC;
    }

    vector->capacity = new_size;
    vector->length   = new_size;
    vector->data     = temp;

    return VECTOR_SUCCESS;
}


Vector_Status vector_insert(Vector *vector, size_t idx, void *in_value)
{
    // Invalid Input
    if(vector == NULL || in_value == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    if(idx >= vector->length){
        return VECTOR_ERR_OUT_OF_BOUNDS;
    }

    // Need growth
    if(vector->length == vector->capacity)
    {
        // Mac Capacity Already Reached
        if(vector->capacity == SIZE_MAX){
            return VECTOR_ERR_MAX_CAPACITY;
        }

        Vector_Status s = vector_growth(vector);
        if(s != VECTOR_SUCCESS){
            return s;
        }
    }

    // Move the Elements
    char *insert_address    = (char *)vector->data + idx * vector->elem_size;
    size_t elements_to_move = vector->length - idx;
    size_t bytes_to_move    = elements_to_move * vector->elem_size;

    memmove(insert_address + vector->elem_size, insert_address, bytes_to_move);

    // Insert the new one
    memcpy(insert_address, in_value, vector->elem_size);
    vector->length++;

    return VECTOR_SUCCESS;
}


Vector_Status vector_erase(Vector *vector, size_t idx, void *out_value)
{
    // Invalid Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    if(idx >= vector->length){
        return VECTOR_ERR_OUT_OF_BOUNDS;
    }

    char *erase_address = (char *)vector->data + idx * vector->elem_size;
    size_t elements_to_move = vector->length - idx - 1;
    size_t bytes_to_move = elements_to_move * vector->elem_size;

    // Save element if Needed
    if(out_value != NULL)
    {
        memcpy(out_value, erase_address, vector->elem_size);
    }

    // Move the Elements
    memmove(erase_address, erase_address + vector->elem_size, bytes_to_move);
    vector->length--;

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


size_t vector_size(const Vector *vector)
{
    return (vector == NULL) ? 0 : vector->length;
}


size_t vector_capacity(const Vector *vector)
{
    return (vector == NULL) ? 0 : vector->capacity; 
}


size_t vector_max_size()
{
    return SIZE_MAX;
}


Vector_Status vector_reserve(Vector *vector, size_t new_capacity)
{
    // Invalid Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    // No need to Realloc
    if(new_capacity < vector->capacity)
    {
        return VECTOR_SUCCESS;
    }
 
    // Need to Realloc and Overflows
    if(new_capacity > SIZE_MAX / vector->elem_size){
        return VECTOR_ERR_OVERFLOW;
    }

    void *temp = realloc(vector->data, new_capacity * vector->elem_size);
    if(temp == NULL){
        return VECTOR_ERR_ALLOC;
    }

    vector->capacity = new_capacity;
    vector->data     = temp;

    return VECTOR_SUCCESS;
}


Vector_Status vector_shrink_to_fit(Vector *vector)
{
    // Invalid Input
    if(vector == NULL){
        return VECTOR_ERR_NULL_PTR;
    }

    // Do nothing
    if(vector->length == 0 || vector->capacity == vector->length){
        return VECTOR_SUCCESS;
    } 

    void *temp = realloc(vector->data, vector->elem_size * vector->length);
    if(temp == NULL){
        return VECTOR_ERR_ALLOC;
    }

    vector->capacity = vector->length;
    vector->data     = temp;

    return VECTOR_SUCCESS;
}


// ==========================================================================
// ===----------------------- Element Access -----------------------------===
// ==========================================================================

void *vector_data(const Vector *vector)
{
    return (vector == NULL) ? NULL : vector->data;
}


void *vector_back(const Vector *vector)
{
    // Invalid Input
    if(vector == NULL || vector_empty(vector) == true){
        return NULL;
    }

    char *base = (char *)vector->data;
    return base + vector->elem_size * (vector->length - 1);
}


void *vector_at(const Vector *vector, size_t idx)
{
    // INvalid Input
    if(vector == NULL || vector_empty(vector) == true || idx >= vector->length){
        return NULL;
    }

    char *base = (char *)vector->data;
    return base + vector->elem_size * idx;
}



