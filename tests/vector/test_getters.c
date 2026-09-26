#include "test_com.h"

#if 1 == 0


static void test_vector_get_length();
static void test_vector_get_data();

void test_vector_getters_all(){

    test_vector_get_length();
    printf("    [PASS] Get Length\n");

    test_vector_get_data();
    printf("    [PASS] Get Data\n");

    printf("[PASS] All Getters\n");
}


static void test_vector_get_length(){

    Vector *vec = NULL;

    assert(vector_get_length(NULL) == 0);

    assert(vector_create_default(&vec, 1) == VECTOR_SUCCESS);

    assert(vector_get_length(vec) == 0);
    vec->length = 1; // Fake object push
    assert(vector_get_length(vec) == 1);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_get_data(){

    Vector *vec = NULL;

    assert(vector_get_data(NULL) == NULL);

    assert(vector_create_default(&vec, 1) == VECTOR_SUCCESS);
    assert(vector_get_data(vec) != NULL);
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}
#endif