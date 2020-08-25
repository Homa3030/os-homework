#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int max_int;
    float max_float;
    double max_double;

    max_int = INT_MAX;
    max_float = FLT_MAX;
    max_double = DBL_MAX;

    printf("integer = %d size of integer = %ld\n" , max_int, sizeof(max_int));
    printf("double = %f size of double = %ld\n" , max_double, sizeof(max_double));
    printf("float = %f size of float = %ld\n" , max_float, sizeof(max_float));

    return 0;
}