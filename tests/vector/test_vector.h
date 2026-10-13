#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

// Custom Data Struct to TEST functionality
typedef struct Point2 {
    int x;
    int y;
} Point2;

void test_vector_constructors();   // Tests: create_default(), create_reserve() 
void test_vector_destructors();    // Tests: destroy() 
void test_vector_modifiers();      // Tests: push_back(), pop_back(), resize(), insert(), erase()  
void test_vector_element_access(); // Tests: data(), back(), at()
void test_vector_capacity();       // Tests: is_empty(), size(), capacity(), max_size(), reserve(), shrink_to_fit()  

#endif
