#include "test_com.h"

#if 1 == 0

static Vector_Status vector_growth(Vector *vector){

    void *temp = NULL;

    vector->capacity = (vector->capacity > (UINT32_MAX >> 1))
        ? UINT32_MAX             // Canot double (overflow). (cap * 2 > MAX)
        : vector->capacity << 1; // Double the capacity

    // Realoc with the new capacity
    temp = realloc(vector->data, (u64)vector->capacity * vector->elem_size);
    if(temp == NULL) { return VECTOR_ERR_ALLOC; }

    vector->data = temp;
    return VECTOR_SUCCESS;
}

static void test_vector_growth_errors(); // Triger all error codes
static void test_vector_growth_normal();
static void test_vector_growth_complex();

void test_vector_growth_all(){

    test_vector_growth_errors();
    printf("    [PASS] Growth Errors\n");

    test_vector_growth_normal();
    printf("    [PASS] Growth Normal Struct\n");

    test_vector_growth_complex();
    printf("    [PASS] Growth Complex Struct\n");

    printf("[PASS] All Growth\n");
}

static void test_vector_growth_errors(){

    Vector *vec = NULL;

    assert(vector_create_reserve(&vec, UINT32_MAX, 2) == VECTOR_SUCCESS);
    vec->capacity = 6;
    assert(vector_growth(vec) == VECTOR_ERR_ALLOC);
    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_growth_normal(){

    Vector *vec = NULL;
    test_struct2 *arr;

    assert(vector_create_reserve(&vec, sizeof(test_struct2), UINT8_MAX) == VECTOR_SUCCESS);

    vec->length = 3;
    arr = (test_struct2 *) vec->data;
    for(u32 i = 0; i < vec->length; i++){
        arr[i].x = i + 8;
        arr[i].y = i + 9;
    }

    assert(vector_growth(vec) == VECTOR_SUCCESS);
    arr = (test_struct2 *) vec->data;
    for(u32 i = 0; i < vec->length; i++){
        assert(arr[i].x == i + 8
            && arr[i].y == i + 9);
    }
    assert(vec->capacity == UINT8_MAX << 1);

    assert(vector_destroy(&vec, NULL) == VECTOR_SUCCESS);
}

static void test_vector_growth_complex(){

    Vector *vec = NULL;
    test_struct1 *arr;
    int *temp[3];
    int size = 10;

    assert(vector_create_reserve(&vec, sizeof(test_struct1), UINT8_MAX) == VECTOR_SUCCESS);

    vec->length = 3;
    arr = (test_struct1 *) vec->data;
    for(u32 i = 0; i < vec->length; i++){
        arr[i].size = size;
        arr[i].a = (int *) malloc(size * sizeof(int));
        if(arr[i].a == NULL) {
            printf("[FAIL] growth");
            exit(EXIT_FAILURE);
        }

        for(int j = 0; j < size; j++){
            arr[i].a[j] = i;
        }
        temp[i] = arr[i].a;
    }

    assert(vector_growth(vec) == VECTOR_SUCCESS);

    arr = (test_struct1 *) vec->data;
    for(u32 i = 0; i < vec->length; i++){
        assert(arr[i].size == size
            && arr[i].a == temp[i]);

        for(int j = 0; j < size; j++){
            assert(arr[i].a[j] == i);
        }
    }
    assert(vec->capacity == UINT8_MAX << 1);

    assert(vector_destroy(&vec, &delete_struct) == VECTOR_SUCCESS);
}
#endif