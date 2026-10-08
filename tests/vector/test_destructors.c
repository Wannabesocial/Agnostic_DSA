#define __UNIT_TEST_VECTOR__
#include "vector.h"
#include "test_vector.h"
#include <stdio.h>
#include <assert.h>

static void test_destroy();

void test_vector_destructors()
{
    printf("Run Destructors Tests...\n");

    test_destroy();
    printf("[PASS] Destroy\n\n");
}


static void test_destroy()
{
    Vector *vector = NULL;

    assert(vector_destroy(vector) == VECTOR_ERR_NULL_PTR);

    assert(vector_create_default(&vector, sizeof(Point2)) == VECTOR_SUCCESS);
    assert(vector_destroy(vector) == VECTOR_SUCCESS);
}
