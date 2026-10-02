// #include "test_com.h"
#include <stdio.h>
#include "vector.h"


typedef struct Point {
    int x;
    int y;
} Point;

void print(Vector *vec)
{
    Point *ptr = NULL;

    printf("Size: %lu, Capacity: %lu\n", vector_size(vec), vector_capacity(vec));
    printf("All the Vector Datas: ");
    ptr = (Point *) vector_data(vec);
    
    for(size_t i = 0; i < vector_size(vec); i++)
    {
        printf("(%d, %d), ", ptr[i].x, ptr[i].y);
    }
    printf("\n\n");
}


int main()
{
    printf("--- Start Vector Tests ---\n\n");
 
    Point *ptr;
    Point p1;
    Vector *vec;

    vector_create_default(&vec, sizeof(Point));


    for(int i = 0; i < 10; i++)
    {
        p1.x = i, p1.y = i;
        vector_push_back(vec, &p1);
    }
    print(vec);

    vector_erase(vec, 0, &p1);
    printf("Remove (%d, %d)\n\n", p1.x, p1.y);
    print(vec);

    vector_erase(vec, 2, &p1);
    printf("Remove (%d, %d)\n\n", p1.x, p1.y);
    print(vec);

    vector_erase(vec, 2, &p1);
    printf("Remove (%d, %d)\n\n", p1.x, p1.y);
    print(vec);
    

    vector_destroy(vec);

    // test_vector_create_all();
    // putchar('\n');

    // test_vector_destroy_all();
    // putchar('\n');

    // test_vector_empty_all();
    // putchar('\n');

    // test_vector_clear_all();
    // putchar('\n');

    // test_vector_growth_all();
    // putchar('\n');

    // test_vector_push_back_all();
    // putchar('\n');

    // test_vector_pop_back_all();
    // putchar('\n');

    // test_vector_getters_all();
    // putchar('\n');

    printf("\n---All Test [PASSED]---\n");
    return 0;
}
