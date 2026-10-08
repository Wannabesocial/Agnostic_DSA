#include "test_vector.h"
#include <stdio.h>


int main()
{
    printf("--- Start Vector Tests ---\n\n");
 
    {
        test_vector_constructors();
        test_vector_destructors();
    //    test_vector_modifiers();
        test_vector_element_access();
    //    test_vector_capacity();
    }    

    printf("\n---All Test [PASSED]---\n");
    
    return 0;
}
