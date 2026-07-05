#include "vector.h"
#include "common.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Create Tests */
void test_vector_create_all();
void test_vector_create_default();
void test_vector_create_reserve();

/* Destroy Tests */
void test_vector_destroy_all();
void test_vector_destroy_normal();
void test_vector_destroy_user();

/* Empty Tests */
void test_vector_empty_all();

int main(){

    test_vector_create_all();
    test_vector_destroy_all();
    test_vector_empty_all();

    return 0;
}

#pragma region Create
void test_vector_create_all(){
    test_vector_create_default();
    test_vector_create_reserve();
    printf("[PASS] All Create Tests\n");
}

void test_vector_create_default(){

    Vector vec;
    u32 elem_size = 20;

    // Invalid input
    assert(vector_create_default(NULL, 10) == VECTOR_ERR_NULL_PTR);
    assert(vector_create_default(&vec, 0) == VECTOR_ERR_INVALID_SIZE);

    // No memory to alloc
    assert(vector_create_default(&vec, UINT32_MAX) == VECTOR_ERR_ALLOC);

    // Normal useage
    assert(vector_create_default(&vec, elem_size) == VECTOR_SUCCESS);
    assert(vec.capacity == DEFAULT_CAPACITY);
    assert(vec.length == 0);
    assert(vec.elem_size == elem_size);
    assert(vec.data != NULL);

    free(vec.data);
}

void test_vector_create_reserve(){

    Vector vec;
    u32 elem_size = 20, capacity = 10;

    // Invalid user Input
    assert(vector_create_reserve(NULL, 1, 1) == VECTOR_ERR_NULL_PTR);
    assert(vector_create_reserve(&vec, 0, 1) == VECTOR_ERR_INVALID_SIZE);
    assert(vector_create_reserve(&vec, 1, 0) == VECTOR_ERR_INVALID_SIZE);
    assert(vector_create_reserve(&vec, 0, 0) == VECTOR_ERR_INVALID_SIZE);

    // No memory to alloc
    assert(vector_create_reserve(&vec, UINT32_MAX, UINT16_MAX) == VECTOR_ERR_ALLOC);

    // Normal useage
    assert(vector_create_reserve(&vec, elem_size, capacity) == VECTOR_SUCCESS);
    assert(vec.elem_size == elem_size);
    assert(vec.length == 0);
    assert(vec.capacity == capacity);
    assert(vec.data != NULL);

    free(vec.data);
}
#pragma endregion


#pragma region Destroy
void test_vector_destroy_all(){
    test_vector_destroy_normal();
    test_vector_destroy_user();
    printf("[PASS] All Destroy Tests\n");
}

void test_vector_destroy_normal(){

    typedef struct test_struct2 {
        int x, y;
    } test_struct2;

    Vector vec;
    test_struct2 *array2;
    u32 capacity = 10;

    // Invalid User input
    assert(vector_destroy(NULL, NULL) == VECTOR_ERR_NULL_PTR);

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

typedef struct test_struct1 {
    int *a, size;
} test_struct1;

void delete_struct(void *args) {
    test_struct1 *my_struct = (test_struct1 *)args;
    free(my_struct->a);
}

void test_vector_destroy_user(){

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
#pragma endregion


#pragma region Empty
void test_vector_empty_all(){

    Vector vec;
    u32 elem_size = 20;

    vector_create_default(&vec, elem_size);
    assert(vector_empty(&vec) == true);

    vec.length = 1;
    assert(vector_empty(&vec) == false);

    printf("[PASS] All Empty Tests\n");
}
#pragma endregion

