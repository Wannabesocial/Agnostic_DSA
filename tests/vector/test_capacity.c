#define __UNIT_TEST_VECTOR__
#include "vector.h"
#include "test_vector.h"
#include <stdio.h>
#include <assert.h>
#include <stdint.h>


static void test_empty();
static void test_size();
static void test_capacity();
static void test_max_size();
static void test_reserve();
static void test_shrink_to_fit();


void test_vector_capacity()
{
    printf("Run Capacity Tests...\n");

    test_empty();
    printf("[PASS] Empty\n");

    test_size();
    printf("[PASS] Size\n");

    test_capacity();
    printf("[PASS] Capacity\n");

    test_max_size();
    printf("[PASS] Max Size\n");

    test_reserve();
    printf("[PASS] Reserve\n");

//    test_shrink_to_fit();
//    printf("[PASS] Shrink To Fit\n");
}


static void test_max_size()
{
    assert(vector_max_size() == SIZE_MAX);
}


static void test_capacity()
{
    Vector *vector = NULL;
    Point2 p = { 3, 3 };
    size_t init_capacity = 2;

    assert(vector_capacity(NULL) == 0);

    assert(vector_create_reserve(&vector, sizeof(Point2), init_capacity) == VECTOR_SUCCESS);
    {
        assert(vector_capacity(vector) == init_capacity);

        for(int i = 0; i < 5; i++){
            assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        }
        
        assert(vector_capacity(vector) == 8);
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_size()
{
    Vector *vector = NULL;
    Point2 p = { 3, 3 };

    assert(vector_size(NULL) == 0);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_size(vector) == 0);
        assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        assert(vector_size(vector) == 2);
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_empty()
{
    Vector *vector = NULL;
    Point2 p = { 3, 3 };

    assert(vector_empty(NULL) == true);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_empty(vector) == true);

        assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        assert(vector_empty(vector) == false);
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}
