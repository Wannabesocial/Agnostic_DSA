/**
 * This a Library for the emplemetation of a Vector Data Structure in pure C that can hold any type of data type.
 * For this reason the ownership and the obligation of the data goes to User and not the Data Structure.
 * This emplemetation does not allocate memory indivitualy for every data type. Works with shallow copy.
**/

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


// Error codes for Vector
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
 * Destroy the Vector. Dealocate the `Vector` data structure. Set `vector` to `NULL`
 *
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
*/
Vector_Status vector_destroy(Vector **vector);


/**
 * Does not dealocate `void *data` itself. Just set `length` to 0.
 *
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *
 * Note: Performance function. Be carefull if you have a `Vector` of Pointers. 
*/
Vector_Status vector_clear(Vector *vector);


/**
 * Push element at the end of Vector.
 *
 * Param:
 *  `in_value` Must be a address of data same size of `elem_size` that used in `vector_creat()`.
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_ALLOC | VECTOR_ERR_MAX_LENGHT
 *  VECTOR_ERR_OVERFLOW
 *
 * Note: It does a shallow copy of the `value` you pass in the Vector. It uses `memcpy` to save data to Vector..
*/
Vector_Status vector_push_back(Vector *vector, const void *in_value);


/**
 * Pop element at the end of Vector
 *
 * Param:
 *  `out_value` Is the variable that result will be saved. Uses `memcpy` therefore it does a shallow-copy. Use `NULL` if you do not care about saving it.
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_EMPTY
*/
Vector_Status vector_pop_back(Vector *vector, void *out_value);


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
size_t vector_length(const Vector *vector);


/**
 * Get `data` of Vector
 *
 * Note: If `vector` is `NULL` return `NULL`
*/
void *vector_data(const Vector *vector);


#endif
