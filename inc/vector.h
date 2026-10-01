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
    void *data;       // The actual Vector. It holds the data
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
 * Destroy the Vector. Dealocate the `Vector` data structure.
 *
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *
 * Note: Manualy Dealocate the data if needed before you call or you will have memory leaks.
*/
Vector_Status vector_destroy(Vector *vector);


#if 1 == 0
/**
 * Does not dealocate `void *data` itself. Just set `length` to 0.
 *
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *
 * Note: Performance function. Manualy Dealocate the data if needed before you call or you will have memory leaks.
*/
Vector_Status vector_clear(Vector *vector);
#endif 


/**
 * Push element at the end of Vector.
 *
 * Param:
 *  `in_value` Must be a address of data same size of `elem_size` that used in `vector_creat()`.
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_ALLOC | VECTOR_ERR_MAX_CAPACITY
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
 * Note: On error (pass NULL as argument) return `true`
*/
bool vector_empty(const Vector *vector);


/**
 * Get the Capacity of the Vector
 *
 * Note: On error (pass NULL as argument) return 0.
**/
size_t vector_capacity(const Vector *vector);


/**
 * Get `length` of Vector
 * 
 * Note: On error (pass NULL as argument) return 0
*/
size_t vector_size(const Vector *vector);


/**
 * Get a pointer to the actual Vector data. (the 1st element, aka the Base)
 *
 * Note: On error (pass NULL as argument) return NULL
*/
void *vector_data(const Vector *vector);

/**
 * Get a pointer to the actual Vector data. (the last element)
 *
 * Note: On error (pass NULL as argument, Vector is empty) return NULL
*/
void *vector_back(const Vector *vector);


/**
 * Get a pointer to the actual Vector data. (the idx element)
 *
 * Note: On error (pass NULL as argument, Vector is empty, out of range idx) return NULL. First element is idx = 0.
*/
void *vector_at(const Vector *vector, size_t idx);


/**
 * Change the `size` of the Vector. If size lower the current do nothing. If more than `capacity` realloc.
 * 
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_ALLOC | VECTOR_ERR_OVERFLOW
 **/
Vector_Status vector_resize(Vector *vector, size_t new_size);


/**
 * Get the Max size that the Vector can hold base on System
**/
size_t vector_max_size();


/**
 * Change the `capacity` of the Vector. If lower than already existed do nothing.
 *
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_ALLOC | VECTOR_ERR_OVERFLOW
 *
 *  Note: Does not change the Size-Lenght of the Vector
**/
Vector_Status vector_reserve(Vector *vector, size_t new_capacity);


/**
 * Does reallocation so the Capacity mach the Lenght
 *
 * Return:
 *  VECTOR_SUCCESS | VECTOR_ERR_NULL_PTR
 *  VECTOR_ERR_ALLOC
**/
Vector_Status vector_shrink_to_fit(Vector *vector);

#endif
