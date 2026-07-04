#include "vector.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>

int sum(const int a, const int b){
    return a + b;
}

int sub(const int a, const int b){
    return a - b;
}

int main(){

    int a = 10, b = 7;

    int (* ptr_fun)(const int, const int);

    ptr_fun = &sum;
    printf("Sum %d\n", ptr_fun(a, b));

    ptr_fun = &sub;
    printf("Sub %d\n", ptr_fun(a, b));

    return 0;
}