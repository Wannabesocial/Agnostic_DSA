/* We can never have overflow with elem_size * capacity */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdbool.h>

#define DEFAULT_CAPACITY 8 // Default Capacity

typedef struct Vector {
    void *data;
    size_t elem_size; // Size of user data that want to store
    size_t length;    // The current length of Vector
    size_t capacity;  // The actual malloced length of Vector
} Vector;


// Error codes. See VECTOR_::
typedef enum Vector_Status {
    VECTOR_SUCCESS = 0,       // All went well
    VECTOR_ERR_ALLOC,         // Memory managment failed (malloc, calloc, realloc)
    VECTOR_ERR_NULL_PTR,      // (NULL) pointer argument
    VECTOR_ERR_INVALID_SIZE,  // Element size or Capacity was (0)
    VECTOR_ERR_EMPTY,         // Empty Vector
    VECTOR_ERR_MAX_CAPACITY,  // Max Capacity has already reached (canot malloc more)
    VECTOR_ERR_OUT_OF_BOUNDS, // Out of bounds
    VECTOR_ERR_OVERFLOW       // Integer overflow in byte size calculation
} Vector_Status;


/**
 * Create a Vector with Default capacity. `length` set to 0.
 * Pointer that will be passed must be init to `NULL`.
 *
 * Param:
 *  `elem_size` Size of the data type in bytes. e.g `sizeof(int)`, `sizeof(struct)`, etc.
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_INVALID_SIZE
 *  VECTOR_ERR_NULL_PTR | VECTOR_ERR_ALLOC | VECTOR_ERR_OVERFLOW
**/
Vector_Status vector_create_default(Vector **vector, size_t elem_size);


/**
 * Create a Vector with given Capacity. `length` set to 0.
 * Pointer that will be passed must be init to `NULL`.
 *
 * Param:
 *  `elem_size` Size of the data type in bytes. e.g `sizeof(int)`, `sizeof(struct)`, etc.
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_INVALID_SIZE
 *  VECTOR_ERR_ALLOC 
**/
Vector_Status vector_create_reserve(Vector **vector, size_t elem_size, size_t capacity);


/**
 * Destroy the Vector. Dealocate everything. Set `vector` to `NULL`
 *
 * Param:
 *  `destroy_func` User given custom free function to avoid memory leaks. `NULL` if Vector data-type no need it
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
*/
Vector_Status vector_destroy(Vector **vector, void (* destroy_func)(void *));


/**
 * Deallocate memory for each element of the Vector (if needed). Does not dealocate `void *data` itself. Set `length` to 0.
 *
 * Param:
 *  `destroy_func` User given custom free function to avoid memory leaks. `NULL` if Vector data-type no need it
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *
 * Note: Performance function.
*/
Vector_Status vector_clear(Vector *vector, void (* destroy_func)(void *));


/**
 * Push element at the end of Vector.
 *
 * Param:
 *  `value` Must be a address `&` of data same size of `elem_size` that used in `vector_creat()`.
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_ALLOC | VECTOR_ERR_MAX_LENGHT
 *  VECTOR_ERR_OVERFLOW
 *
 * Note: It does a shallow copy of the `value` you pass in the Vector. It uses `memcpy` to save data to Vector..
*/
Vector_Status vector_push_back(Vector *vector, const void *value);


/**
 * Pop element at the end of Vector
 *
 * Param:
 *  `value` Is the variable that result will be saved. Uses `memcpy`. Use `NULL` if you do not care about saving it
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_EMPTY
*/
Vector_Status vector_pop_back(Vector *vector, void *value);


/**
 * Check if a Vector is empty.
 * 
 * Note: If `vector` is `NULL` return `true`
*/
bool vector_empty(const Vector *vector);


/**
 * Get `length` of Vector
 *
 * Note: If `vector` is `NULL` return `0`
*/
size_t vector_get_length(const Vector *vector);


/**
 * Get `data` of Vector
 *
 * Note: If `vector` is `NULL` return `NULL`
*/
void *vector_get_data(const Vector *vector);


#endif
