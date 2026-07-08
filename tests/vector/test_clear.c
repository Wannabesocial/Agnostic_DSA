#include "test_com.h"

static void test_vector_clear_error(); // Triger All error codes
static void test_vector_clear_normal();
static void test_vector_clear_complex();

void test_vector_clear_all(){

    test_vector_clear_error();
    printf("    [PASS] Clear Errors\n");

    test_vector_clear_normal();
    printf("    [PASS] Clear Normal Struct\n");

    test_vector_clear_complex();
    printf("    [PASS] Clear Complex Struct\n");

    printf("[PASS] All Clear\n");
}


static void test_vector_clear_error(){

    assert(vector_clear(NULL, NULL) == VECTOR_ERR_NULL_PTR);
    assert(vector_clear(NULL, &delete_struct) == VECTOR_ERR_NULL_PTR);
}

static void test_vector_clear_normal(){

    Vector *vec = NULL;

    // Normal Useage. No custom dealloc
    assert(vector_create_default(&vec, sizeof(test_struct2)) == VECTOR_SUCCESS);
    vec->length = 3; // Fake 3 object pushed

    assert(vector_clear(vec, NULL) == VECTOR_SUCCESS
        && vec->length == 0);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_clear_complex(){

    Vector *vec = NULL;
    test_struct1 *arr;
    u32 capacity = 10;

    assert(vector_create_reserve(&vec, sizeof(test_struct1), capacity) == VECTOR_SUCCESS);
    vec->length = capacity;

    // Normal Useage. Custom dealloc
    arr = (test_struct1 *) vec->data;
    for(u32 i = 0; i < vec->length; i++){

        arr[i].a = (int *) malloc(sizeof(int) * vec->length);
        if(arr[i].a == NULL){
            printf("[FAIL] Clear\n");
            exit(EXIT_FAILURE);
        }
    }

    assert(vector_clear(vec, &delete_struct) == VECTOR_SUCCESS
        && vec->length == 0);

    assert(vector_destroy(&vec, &delete_struct) == VECTOR_SUCCESS);
}