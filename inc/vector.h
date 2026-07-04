#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

#define GROWTH       2 // How fast will Vector growth when full (x2)
#define DEFAULT_SIZE 8 // Default size and capacity

typedef struct Vector {
    void *data;
    u32  elem_size; // Size of user data that want to store
    u32  lenght;    // The current size of Vector
    u32  capacity;  // The actual malloced size of Vector
} Vector;


// Error codes. See VECTOR_::
typedef enum Vector_Status {
    VECTOR_SUCCESS = 0,       // All went well
    VECTOR_ERR_ALLOC,         // Memory managment failed (malloc, calloc, realloc)
    VECTOR_ERR_NULL_PTR,      // (NULL) pointer arg
    VECTOR_ERR_INVALID_SIZE,  // Element size was (0)
    VECTOR_ERR_EMPTY,         // Empty Vector
    VECTOR_ERR_MAX_LENGHT,    // Max Lenght has already reached (canot malloc more)
    VECTOR_ERR_OUT_OF_BOUNDS, // Out of bounds
} Vector_Status;


/**
 * @brief Create a Vector with Default capacity.
 * @param elem_size Size of the data type in bytes. e.g `sizeof(int)`, `sizeof(struct)`, etc
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_INVALID_SIZE
 * @retval VECTOR_ERR_NULL_PTR
 * @retval VECTOR_ERR_ALLOC
*/
Vector_Status vector_create_default(Vector *vector, const u32 elem_size);

/**
 * @brief Create a Vector with given capacity
 * @param elem_size Size of the data type in bytes. e.g `sizeof(int)`, `sizeof(struct)`, etc
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_INVALID_SIZE
 * @retval VECTOR_ERR_NULL_PTR
 * @retval VECTOR_ERR_ALLOC
*/
Vector_Status vector_create_reserve(Vector *vector, const u32 elem_size, const u32 capacity);

/**
 * @brief Destroy the Vector. Dealocate everything
 * @param destroy_func User given custom free function to avoid memory leaks. `NULL` if Vector data-type no need it
 * @retval VECTOR_SUCCESS
 * @retval VECTOR_ERR_NULL_PTR
*/
Vector_Status vector_destroy(Vector *vector, void (* destroy_func)(void *));

#endif