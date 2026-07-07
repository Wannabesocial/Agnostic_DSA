#include "test_com.h"


/* Push Back Tests */
void test_vector_push_back_all();
void test_vector_push_back_error();
void test_vector_push_back_normal();
void test_vector_push_back_user();

int main(){

    printf("--- Start Vector Tests ---\n\n");

    test_vector_create_all();
    putchar('\n');

    test_vector_destroy_all();
    putchar('\n');

    test_vector_empty_all();
    putchar('\n');

    test_vector_clear_all();
    putchar('\n');

    test_vector_growth_all();
    putchar('\n');

    test_vector_push_back_all();
    putchar('\n');

    printf("---All Test [PASSED]---\n");
    return 0;
}



#pragma region Push_Back


void test_vector_push_back_normal(){

}

void test_vector_push_back_user(){

}
#pragma endregion



