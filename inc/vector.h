/* We can never have overflow with elem_size * capacity */

#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"
#include <stdbool.h>

#define DEFAULT_CAPACITY 8 // Default Capacity

/* Raw data access only via Unit Testing */
#if defined(UNIT_TEST) || defined(VECTOR_IMPLEMENTATION)

typedef struct Vector {
    void *data;
    u32  elem_size; // Size of user data that want to store
    u32  length;    // The current length of Vector
    u32  capacity;  // The actual malloced length of Vector
} Vector;

#else

typedef struct Vector Vector;

#endif

// Error codes. See VECTOR_::
typedef enum Vector_Status {
    VECTOR_SUCCESS = 0,       // All went well
    VECTOR_ERR_ALLOC,         // Memory managment failed (malloc, calloc, realloc)
    VECTOR_ERR_NULL_PTR,      // (NULL) pointer arg
    VECTOR_ERR_INVALID_SIZE,  // Element size or Capacity was (0)
    VECTOR_ERR_EMPTY,         // Empty Vector
    VECTOR_ERR_MAX_CAPACITY,    // Max Capacity has already reached (canot malloc more)
    VECTOR_ERR_OUT_OF_BOUNDS, // Out of bounds
} Vector_Status;


/**
 * @brief Create a Vector with Default capacity. `length` set to 0
 * @param elem_size Size of the data type in bytes. e.g `sizeof(int)`, `sizeof(struct)`, etc
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_INVALID_SIZE
 * @retval VECTOR_ERR_NULL_PTR
 * @retval VECTOR_ERR_ALLOC
*/
Vector_Status vector_create_default(Vector **vector, const u32 elem_size);

/**
 * @brief Create a Vector with given Capacity. `length` set to 0
 * @param elem_size Size of the data type in bytes. e.g `sizeof(int)`, `sizeof(struct)`, etc
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_INVALID_SIZE
 * @retval VECTOR_ERR_ALLOC
*/
Vector_Status vector_create_reserve(Vector **vector, const u32 elem_size, const u32 capacity);

/**
 * @brief Destroy the Vector. Dealocate everything. Set `vector` to `NULL`
 * @param destroy_func User given custom free function to avoid memory leaks. `NULL` if Vector data-type no need it
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_NULL_PTR
*/
Vector_Status vector_destroy(Vector **vector, void (* destroy_func)(void *));

/**
 * @brief Deallocate memory for each element of the Vector (if needed). Does not dealocate `void *data` itself.
 * Set `length` to 0.
 * @param destroy_func User given custom free function to avoid memory leaks. `NULL` if Vector data-type no need it
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_NULL_PTR
 * @note Performance function.
*/
Vector_Status vector_clear(Vector *vector, void (* destroy_func)(void *));

/**
 * @brief Push element at the end of Vector.
 * @param value Must be a address `&` of data same size of `elem_size` that used in `vector_creat()`.
 * Use `memcpy` to save data to Vector.
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_NULL_PTR
 * @retval VECTOR_ERR_ALLOC
 * @retval VECTOR_ERR_MAX_LENGHT
 * @note It does a shallow copy of the `value` you pass in the Vector.
*/
Vector_Status vector_push_back(Vector *vector, const void *value);

/**
 * @brief Pop element at the end of Vector
 * @param value Is the variable that result will be saved. Uses `memcpy`. Use `NULL` if you do not care about saving it
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_NULL_PTR
 * @retval VECTOR_ERR_EMPTY
*/
Vector_Status vector_pop_back(Vector *vector, void *value);

/**
 * @brief Check if a Vector is empty
 * @param vector If vector is `NULL` return `true`
*/
bool vector_empty(const Vector *vector);

/**
 * @brief Get `length` of Vector
 * @param vector If vector is `NULL` return `0`
*/
u32 vector_get_length(const Vector *vector);

/**
 * @brief Get `data` of Vector
 * @param vector If vector is `NULL` return `NULL`
*/
void *vector_get_data(const Vector *vector);

#endif