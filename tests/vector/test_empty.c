#include "test_com.h"

static void test_vector_empty();
static void test_vector_not_empty();

void test_vector_empty_all(){

    test_vector_empty();
    printf("    [PASS] Empty\n");

    test_vector_not_empty();
    printf("    [PASS] Not Empty\n");

    printf("[PASS] All Empty\n");
}

static void test_vector_empty(){

    Vector vec;
    u32 elem_size = 20;

    assert(vector_create_default(&vec, elem_size) == VECTOR_SUCCESS);
    assert(vector_empty(&vec) == true);
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_not_empty(){

    Vector vec;
    u32 elem_size = 20;

    assert(vector_create_default(&vec, elem_size) == VECTOR_SUCCESS);

    vec.length = 1; // Fake object push
    assert(vector_empty(&vec) == false);
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}
