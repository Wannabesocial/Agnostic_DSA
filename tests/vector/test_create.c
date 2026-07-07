#include "test_com.h"

static void test_vector_create_default();
static void test_vector_create_reserve();

void test_vector_create_all(){

    test_vector_create_default();
    printf("    [PASS] Create Default\n");

    test_vector_create_reserve();
    printf("    [PASS] Create Reserve\n");

    printf("[PASS] All Create\n");
}


static void test_vector_create_default(){

    Vector vec;
    u32 elem_size = 20;

    // Invalid input
    assert(vector_create_default(NULL, 10) == VECTOR_ERR_NULL_PTR);
    assert(vector_create_default(&vec, 0) == VECTOR_ERR_INVALID_SIZE);

    // No memory to malloc (Canot happend in our system, 2^32 * 2^3 CAN malloced)

    // Normal useage
    vec.data = NULL;
    assert(vector_create_default(&vec, elem_size) == VECTOR_SUCCESS);
    assert(vec.capacity == DEFAULT_CAPACITY);
    assert(vec.length == 0);
    assert(vec.elem_size == elem_size);
    assert(vec.data != NULL);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

void test_vector_create_reserve(){

    Vector vec;
    u32 elem_size = 20, capacity = 10;

    // Invalid user Input
    assert(vector_create_reserve(NULL, 1, 1) == VECTOR_ERR_NULL_PTR);
    assert(vector_create_reserve(&vec, 0, 1) == VECTOR_ERR_INVALID_SIZE);
    assert(vector_create_reserve(&vec, 1, 0) == VECTOR_ERR_INVALID_SIZE);
    assert(vector_create_reserve(&vec, 0, 0) == VECTOR_ERR_INVALID_SIZE);

    // No memory to malloc
    assert(vector_create_reserve(&vec, UINT32_MAX, UINT16_MAX) == VECTOR_ERR_ALLOC);

    // Normal useage
    assert(vector_create_reserve(&vec, elem_size, capacity) == VECTOR_SUCCESS);
    assert(vec.elem_size == elem_size);
    assert(vec.length == 0);
    assert(vec.capacity == capacity);
    assert(vec.data != NULL);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}