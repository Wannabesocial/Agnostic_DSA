#ifndef TEST_COM_H
#define TEST_COM_H

// Raw access for Unit Testing
#define UNIT_TEST
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Complex
typedef struct test_struct1 {
    int *a, size;
} test_struct1;

// Normal
typedef struct test_struct2 {
    int x, y;
} test_struct2;

void delete_struct(void *args);



void test_vector_create_all();    // Create Tests
void test_vector_destroy_all();   // Destroy Tests
void test_vector_empty_all();     // Empty Tests
void test_vector_clear_all();     // Clear Tests
void test_vector_growth_all();    // Growth Tests
void test_vector_push_back_all(); // Push Back Tests
void test_vector_getters_all();   // Getters Tests
void test_vector_pop_back_all();  // Pop Back Tests

#endif