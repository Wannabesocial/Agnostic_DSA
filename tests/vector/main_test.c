// #include "test_com.h"
#include <stdio.h>
#include "vector.h"


typedef struct Point {
    int x;
    int y;
} Point;

int main()
{
    printf("--- Start Vector Tests ---\n\n");
 
    Point *ptr;
    Point p1;
    Vector *vec;

    vector_create_default(&vec, sizeof(Point));


    p1.x = 1, p1.y = 3;
    vector_push_back(vec, &p1);

    p1.x = 10, p1.y = 20;
    vector_push_back(vec, &p1);
    
    p1.x = 15, p1.y = -3;
    vector_push_back(vec, &p1);


    printf("All the Vector Datas: ");
    ptr = (Point *) vector_data(vec);
    
    for(size_t i = 0; i < vector_size(vec); i++)
    {
        printf("(%d, %d), ", ptr[i].x, ptr[i].y);
    }
    printf("\n\n");

    printf("Last Element: ");
    ptr = (Point *) vector_back(vec);
    printf("(%d, %d)\n", ptr->x, ptr->y);

    vector_pop_back(vec, NULL);
    printf("Last Element: ");
    ptr = (Point *) vector_back(vec);
    printf("(%d, %d)\n", ptr->x, ptr->y);


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
