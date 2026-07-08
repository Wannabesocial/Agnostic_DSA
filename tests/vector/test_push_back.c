#include "test_com.h"

static void test_vector_push_back_errors(); // Triger all errors code
static void test_vector_push_back_normal();
static void test_vector_push_back_right_cap();
// TODO: static void test_vector_push_back_complex();

void test_vector_push_back_all(){

    test_vector_push_back_errors();
    printf("    [PASS] Push Back Errors\n");

    test_vector_push_back_right_cap();
    printf("    [PASS] Push Back Right Capacity Compute\n");

    test_vector_push_back_normal();
    printf("    [PASS] Push Back Normal Struct\n");

    printf("[PASS] All Push Back\n");
}

static void test_vector_push_back_errors(){

    Vector *vec = NULL;
    test_struct2 val;

    assert(vector_push_back(NULL, NULL) == VECTOR_ERR_NULL_PTR);
    assert(vector_push_back(vec, NULL) == VECTOR_ERR_NULL_PTR);
    assert(vector_push_back(NULL, &val) == VECTOR_ERR_NULL_PTR);

    assert(vector_create_default(&vec, 1) == VECTOR_SUCCESS);
    vec->capacity = UINT32_MAX;
    vec->length   = UINT32_MAX;
    assert(vector_push_back(vec, &val) == VECTOR_ERR_MAX_CAPACITY);
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);

    assert(vector_create_reserve(&vec, UINT32_MAX, 8) == VECTOR_SUCCESS);
    vec->capacity = UINT8_MAX;
    vec->length   = UINT8_MAX;
    assert(vector_push_back(vec, &val) == VECTOR_ERR_ALLOC);
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_push_back_right_cap(){

    Vector *vec = NULL;
    test_struct2 temp = {1, 1};
    u32 capacity = (UINT32_MAX >> 1) + 1000;

    // Canot double up. We take max holdable value
    assert(vector_create_reserve(&vec, sizeof(test_struct2), capacity) == VECTOR_SUCCESS);    

    vec->length = capacity;
    assert(vector_push_back(vec, &temp) == VECTOR_SUCCESS
        && vec->capacity == UINT32_MAX
        && vec->length == capacity + 1);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_push_back_normal(){

    Vector *vec = NULL;
    test_struct2 *arr, temp;
    u32 capacity = 2;

    assert(vector_create_reserve(&vec, sizeof(test_struct2), capacity) == VECTOR_SUCCESS);

    // Add 2 element. No need to resize
    for(int i = 0; i < 2; i++){
        temp.x = i;
        temp.y = i;

        assert(vector_push_back(vec, &temp) == VECTOR_SUCCESS);
    }

    arr = (test_struct2 *) vec->data;
    for(int i = 0; i < vec->length; i++){
        assert(arr[i].x == i
            && arr[i].y == i);
    }
    assert(vec->capacity == 2
        && vec->length == 2);

    // Add 1 more. Realocation
    temp.x = 2; temp.y = 2;
    assert(vector_push_back(vec, &temp) == VECTOR_SUCCESS);

    arr = (test_struct2 *) vec->data;
    for(int i = 0; i < vec->length; i++){
        assert(arr[i].x == i
            && arr[i].y == i);
    }

    assert(vec->capacity == 4
        && vec->length == 3);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}
