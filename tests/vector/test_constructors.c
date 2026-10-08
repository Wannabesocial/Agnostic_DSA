#define __UNIT_TEST_VECTOR__
#include "vector.h"
#include "test_vector.h"
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

static void test_create_default();
static void test_create_reserve();

void test_vector_constructors()
{
    printf("Run Constructors Tests...\n");

    test_create_default();
    printf("[PASS] Create Default\n");

    test_create_reserve();
    printf("[PASS] Create Reserve\n\n");
}


static void test_create_default()
{
    Vector *vector = NULL;

    assert(vector_create_default(NULL, sizeof(int)) == VECTOR_ERR_NULL_PTR);
    assert(vector_create_default(&vector, 0) == VECTOR_ERR_INVALID_SIZE);
    assert(vector_create_default(&vector, SIZE_MAX) == VECTOR_ERR_OVERFLOW);

    // Vector of 'Points2'
    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS
        && vector != NULL
        && vector->data != NULL
        && vector->elem_size == sizeof(Point2)
        && vector->capacity == DEFAULT_CAPACITY
        && vector->length == 0
    );    

    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_create_reserve()
{
    Vector *vector = NULL;
    size_t capacity = 10;

    assert(vector_create_reserve(NULL, 0, 0) == VECTOR_ERR_NULL_PTR);
    assert(vector_create_reserve(&vector, 0, 0) == VECTOR_ERR_INVALID_SIZE);
    assert(vector_create_reserve(&vector, sizeof(Point2), 0) == VECTOR_ERR_INVALID_SIZE); 
    assert(vector_create_reserve(&vector, 0, capacity) == VECTOR_ERR_INVALID_SIZE); 
    assert(vector_create_reserve(&vector, SIZE_MAX, SIZE_MAX) == VECTOR_ERR_OVERFLOW);

    assert(vector_create_reserve(&vector, sizeof(Point2), capacity) == VECTOR_SUCCESS
        && vector != NULL
        && vector->data != NULL
        && vector->elem_size == sizeof(Point2)
        && vector->capacity == capacity
        && vector->length == 0
    );

    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}    
