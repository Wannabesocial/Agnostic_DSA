#include "test_com.h"

#if 1 == 0

static void test_vector_pop_back_errors(); // Triger all errors
static void test_vector_pop_back_normal();
static void test_vector_pop_back_complex();

void test_vector_pop_back_all(){

    test_vector_pop_back_errors();
    printf("    [PASS] Errors\n");

    test_vector_pop_back_normal();
    printf("    [PASS] Normal Struct\n");

    test_vector_pop_back_complex();
    printf("    [PASS] Comlex Struct\n");

    printf("[PASS] All Pop Back\n");
}

static void test_vector_pop_back_errors(){

    Vector *vec = NULL;
    int val;

    assert(vector_pop_back(NULL, NULL) == VECTOR_ERR_NULL_PTR);
    assert(vector_pop_back(NULL, &val) == VECTOR_ERR_NULL_PTR);
    assert(vector_pop_back(vec, NULL) == VECTOR_ERR_NULL_PTR);

    assert(vector_create_default(&vec, 1) == VECTOR_SUCCESS);
    assert(vector_pop_back(vec, NULL) == VECTOR_ERR_EMPTY);
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_pop_back_normal(){

    Vector *vec = NULL;
    test_struct2 k;
    int size = 5;

    assert(vector_create_default(&vec, sizeof(test_struct2)) == VECTOR_SUCCESS);

    for(int i = 0; i < size; i++){
        k.x = i;
        k.y = i;

        assert(vector_push_back(vec, &k) == VECTOR_SUCCESS);
    }

    k.x = 10;
    k.y = 10;

    // Remove 2 elements and check that are right
    assert(vector_pop_back(vec, &k) == VECTOR_SUCCESS
        && k.x == 4
        && k.y == 4
        && vec->length == 4);

    assert(vector_pop_back(vec, &k) == VECTOR_SUCCESS
        && k.x == 3
        && k.y == 3
        && vec->length == 3);

    // Remove 1 element. Do not care about result
    assert(vector_pop_back(vec, NULL) == VECTOR_SUCCESS
        && vec->length == 2);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_pop_back_complex(){

    Vector *vec = NULL;
    test_struct1 k;
    int *temp[5];
    int size = 5;

    assert(vector_create_default(&vec, sizeof(test_struct1)) == VECTOR_SUCCESS);

    for(int i = 0; i < size; i++){

        k.a = malloc(sizeof(int *) * size);
        if(k.a == NULL){
            printf("[FAIL] Pop Back Complex\n");
            exit(EXIT_FAILURE);
        }

        temp[i] = k.a;
        k.size = size;

        assert(vector_push_back(vec, &k) == VECTOR_SUCCESS);
    }

    // Manualy Destroy All Vector Elements
    int i = 4;
    while(vector_empty(vec) == false){
        assert(vector_pop_back(vec, &k) == VECTOR_SUCCESS
            && k.size == size
            && k.a == temp[i]
            && vec->length == i);

        free(k.a);
        i--;
    }

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}
#endif