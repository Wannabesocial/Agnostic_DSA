#define __UNIT_TEST_VECTOR__
#include "vector.h"
#include "test_vector.h"
#include <stdio.h>
#include <assert.h>

static void test_data();
static void test_back();
static void test_at();


void test_vector_element_access()
{
    printf("Run Element Access Tests...\n");

    test_data();
    printf("[PASS] Data\n");

    test_back();
    printf("[PASS] Back\n");

    test_at();
    printf("[PASS] At\n\n");
}


static void test_data()
{
    Vector *vector = NULL;

    assert(vector_data(vector) == NULL);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    assert(vector_data(vector) == vector->data);
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_back()
{
    Vector *vector = NULL;
    Point2 p = { 3, 5 };
    Point2 *ptr_p = NULL;

    assert(vector_back(vector) == NULL);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_back(vector) == NULL);
        assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);
        assert((ptr_p = (Point2 *)vector_back(vector)) != NULL
            && ptr_p->x == p.x
            && ptr_p->y == p.y
        );
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}


static void test_at()
{
    Vector *vector = NULL;
    Point2 p = { 0, 0 };
    Point2 *ptr_p = NULL;

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    {
        assert(vector_at(NULL, 0) == NULL);
        assert(vector_at(vector, 0) == NULL);

        p.x = 101, p.y = 202;
        assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);

        p.x = 99, p.y = 69;
        assert(vector_push_back(vector, &p) == VECTOR_SUCCESS);

        assert(vector_at(vector, 2) == NULL);
        assert((ptr_p = (Point2 *)vector_at(vector, 0)) != NULL
            && ptr_p->x == 101
            && ptr_p->y == 202
        );
        assert((ptr_p = (Point2 *)vector_at(vector, 1)) != NULL
            && ptr_p->x == 99
            && ptr_p->y == 69
        );        
    }
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}
