#define __UNIT_TEST_VECTOR__
#include "vector.h"
#include "test_vector.h"
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

static void test_growth();
static void test_push_back();
static void test_pop_back();
static void test_resize();
static void test_insert();
static void test_erase();


void test_vector_modifiers()
{
    printf("Run Modifiers Tests...\n");

    test_growth();
    printf("[PASS] Growth\n");

    test_push_back();
    printf("[PASS] Push Back\n");

    test_pop_back();
    printf("[PASS] Pop Back\n");

    test_resize();
    printf("[PASS] Resize\n");

    test_insert();
    printf("[PASS] Insert\n");

    test_erase();
    printf("[PASS] Erase\n\n");
}


static void test_erase()
{
    Vector *vector = NULL;
    Point2 p, *ptr = NULL;

    assert(vector_erase(NULL, 0, NULL) == VECTOR_ERR_NULL_PTR);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_erase(vector, 0, NULL) == VECTOR_ERR_OUT_OF_BOUNDS);
        assert(vector_erase(vector, 1, NULL) == VECTOR_ERR_OUT_OF_BOUNDS); 
        
        for(int i = 0; i < 7; i++){
            p.x = p.y = i;
            assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        }

        assert(vector_erase(vector, 3, &p) == VECTOR_SUCCESS
            && p.x == 3 && p.y == 3
        );

        assert(vector_erase(vector, 0, &p) == VECTOR_SUCCESS
            && p.x == 0 && p.y == 0
        );

        assert(vector->capacity == DEFAULT_CAPACITY && vector->length == 5);
        ptr = (Point2 *)vector->data;
        assert((ptr[0].x == 1 && ptr[0].y == 1)
            && (ptr[1].x == 2 && ptr[1].y == 2)
            && (ptr[2].x == 4 && ptr[2].y == 4)
            && (ptr[3].x == 5 && ptr[3].y == 5)
            && (ptr[4].x == 6 && ptr[4].y == 6)        
        );
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_insert()
{
    Vector *vector = NULL;
    Point2 p = { 3, 3 };
    Point2 *ptr = NULL;

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_insert(NULL, 0, NULL) == VECTOR_ERR_NULL_PTR);
        assert(vector_insert(vector, 0, NULL) == VECTOR_ERR_NULL_PTR);
        assert(vector_insert(NULL, 0, &p) == VECTOR_ERR_NULL_PTR);
        
        assert(vector_insert(vector, 0, &p) == VECTOR_ERR_OUT_OF_BOUNDS);
        assert(vector_insert(vector, 1, &p) == VECTOR_ERR_OUT_OF_BOUNDS);

        for(int i = 0; i < 7; i++){
            p.x = p.y = i;
            assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        }

        p.x = p.y = 100;
        assert(vector_insert(vector, 1, &p) == VECTOR_SUCCESS);
        assert(vector_insert(vector, 4, &p) == VECTOR_SUCCESS); 
        
        assert(vector->capacity = DEFAULT_CAPACITY * 2 && vector->length == 9);
        ptr = (Point2 *)vector->data;
        assert((ptr[0].x == 0   && ptr[0].y == 0)
            && (ptr[1].x == 100 && ptr[1].y == 100)
            && (ptr[2].x == 1   && ptr[2].y == 1)
            && (ptr[3].x == 2   && ptr[3].y == 2)
            && (ptr[4].x == 100 && ptr[4].y == 100)
            && (ptr[5].x == 3   && ptr[5].y == 3)
            && (ptr[6].x == 4   && ptr[6].y == 4)
            && (ptr[7].x == 5   && ptr[7].y == 5)
            && (ptr[8].x == 6   && ptr[8].y == 6)
        );

        vector->length   = SIZE_MAX;
        vector->capacity = SIZE_MAX;
        assert(vector_insert(vector, 0, &p) == VECTOR_ERR_MAX_CAPACITY);
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_resize()
{
    Vector *vector = NULL;
    Point2 p, *ptr = NULL;

    assert(vector_resize(NULL, 10) == VECTOR_ERR_NULL_PTR);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_resize(vector, SIZE_MAX) == VECTOR_ERR_OVERFLOW);

        for(int i = 0; i < 5; i++){
            p.x = p.y = i;
            assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        }

        assert(vector_resize(vector, 2) == VECTOR_SUCCESS
            && vector->capacity == DEFAULT_CAPACITY
            && vector->length == 2
        );

        ptr = (Point2 *)vector->data;
        for(int i = 0; i < 2; i++){
            assert(ptr[i].x == i && ptr[i].y == i);
        }
        
        assert(vector_resize(vector, 100) == VECTOR_SUCCESS
            && vector->capacity == 100
            && vector->length == 100
        );

        ptr = (Point2 *)vector->data;
        for(int i = 0; i < 2; i++){
            assert(ptr[i].x == i && ptr[i].y == i);
        }
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_pop_back()
{
    Vector *vector = NULL;
    Point2 p = { 0, 0 };

    assert(vector_pop_back(NULL, &p) == VECTOR_ERR_NULL_PTR);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_pop_back(vector, &p) == VECTOR_ERR_EMPTY);

        for(int i = 0; i < 5; i++){
            p.x = p.y = i;
            assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        }

        assert(vector_pop_back(vector, NULL) == VECTOR_SUCCESS
            && vector->length == 4
        );

        assert(vector_pop_back(vector, &p) == VECTOR_SUCCESS
            && vector->length == 3
            && p.x == 3
            && p.y == 3
        );
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_push_back()
{
    Vector *vector = NULL;
    size_t init_capacity = 3;
    Point2 p = { 3, 3 };
    Point2 *ptr = NULL;

    assert(vector_create_reserve(&vector, sizeof(Point2), init_capacity) == VECTOR_SUCCESS);
    {
        assert(vector_push_back(NULL, NULL) == VECTOR_ERR_NULL_PTR); 
        assert(vector_push_back(NULL, &p) == VECTOR_ERR_NULL_PTR); 
        assert(vector_push_back(vector, NULL) == VECTOR_ERR_NULL_PTR); 
     
        vector->length = SIZE_MAX;
        vector->capacity = SIZE_MAX;
        assert(vector_push_back(vector, &p) == VECTOR_ERR_MAX_CAPACITY);

        vector->capacity = init_capacity;
        vector->length = 0;

        for(int i = 0; i < 10; i++){
            p.x = p.y = i;
            assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        }

        assert(vector->length == 10 && vector->capacity == 12);
        ptr = (Point2 *)vector->data;
        for(int i = 0; i < 10; i++){
            assert(ptr[i].x == i && ptr[i].y == i);
        }
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_growth()
{
    Vector *vector = NULL;
    size_t init_capacity = 10;
    Point2 p;
    Point2 *ptr;

    assert(vector_create_reserve(&vector, sizeof(Point2), init_capacity) == VECTOR_SUCCESS);
    {
        for(int i = 0; i < 5; i++){
            p.x = p.y = i;
            assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        }

        assert(vector_growth(vector) == VECTOR_SUCCESS
            && vector->capacity == init_capacity * 2
        );

        ptr = (Point2 *)vector->data;
        for(int i = 0; i < 5; i++){
            assert(ptr[i].x == i && ptr[i].y == i);
        }
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);


    assert(vector_create_reserve(&vector, sizeof(Point2), init_capacity) == VECTOR_SUCCESS);
    {
        void *old_base;
       
        old_base = vector->data;
        vector->capacity = SIZE_MAX - 2;
        assert(vector_growth(vector) == VECTOR_ERR_OVERFLOW
            && vector->capacity == SIZE_MAX - 2
            && old_base == vector->data
        );

        old_base = vector->data;
        vector->capacity = SIZE_MAX >> 2;
        assert(vector_growth(vector) == VECTOR_ERR_OVERFLOW
            && vector->capacity == SIZE_MAX >> 2
            && old_base == vector->data
        );
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}

