#include "test_com.h"

void delete_struct(void *args) {
    test_struct1 *my_struct = (test_struct1 *)args;
    free(my_struct->a);
}

static void test_vector_destroy_normal();
static void test_vector_destroy_complex();
static void test_vector_destroy_errors(); // Triger all error codes

/* Destroy Tests */
void test_vector_destroy_all(){

    test_vector_destroy_errors();
    printf("    [PASS] Destroy Errors\n");

    test_vector_destroy_normal();
    printf("    [PASS] Destroy Normal Struct\n");

    test_vector_destroy_complex();
    printf("    [PASS] Destroy Complex Struct\n");

    printf("[PASS] All Destroy Tests\n");
}

static void test_vector_destroy_errors(){

    assert(vector_destroy(NULL, NULL) == VECTOR_ERR_NULL_PTR);
    assert(vector_destroy(NULL, &delete_struct) == VECTOR_ERR_NULL_PTR);
}

static void test_vector_destroy_normal(){

    Vector vec;
    test_struct2 *array2;
    u32 capacity = 10;

    // No need custom free
    vector_create_reserve(&vec, sizeof(test_struct2), capacity);
    vec.length = capacity;

    array2 = (test_struct2 *)vec.data;
    for(u32 i = 0; i < vec.length; i++){
        array2[i].x = i;
        array2[i].y = i;
    }
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
    assert(vec.data == NULL);
    assert(vec.capacity == 0);
    assert(vec.length == 0);
    assert(vec.elem_size == 0);
}

static void test_vector_destroy_complex(){

    Vector vec;
    test_struct1 *array1;
    u32 capacity = 10;

    // Need Custom free
    vector_create_reserve(&vec, sizeof(test_struct1), capacity);
    vec.length = capacity;

    array1 = (test_struct1 *)vec.data;
    for(u32 i = 0; i < vec.length; i++){

        array1[i].a = (int *) malloc(sizeof(int) * vec.length);
        if(array1[i].a == NULL) {
            printf("[FAIL] Destroy\n");
            exit(EXIT_FAILURE);
        }
        array1[i].size = vec.length;
    }
    assert(vector_destroy(&vec, &delete_struct) == VECTOR_SUCCESS);
    assert(vec.data == NULL);
    assert(vec.capacity == 0);
    assert(vec.length == 0);
    assert(vec.elem_size == 0);
}