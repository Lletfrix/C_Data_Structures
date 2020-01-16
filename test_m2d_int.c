#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix/matrix.h"
#include "matrix/2d/matrix2d.h"
#include "matrix/2d/int/matrix2dint.h"

/*Compile:
gcc -g -c matrix/matrix.c -o matrix/matrix.o
gcc -g -c matrix/2d/matrix2d.c -o matrix/2d/matrix2d.o
gcc -g -c matrix/2d/int/matrix2dint.c -o matrix/2d/int/matrix2dint.o
gcc -g test_m2d_int.c matrix/matrix.o matrix/2d/matrix2d.o matrix/2d/int/matrix2dint.o -o test_m2d_int
*/

int main(int argc, char const *argv[]) {
    matrix *m;
    size_t space[] = {3, 2, 2, 3};
    size_t space2[] = {6, 6};
    m = matrix_init(matrix_new(), 4, space, sizeof(int), NULL);
    size_t selector[] = {1, 0, 0, 1};
    int *x = (int *)matrix_get(m, selector);
    *x = 2;
    matrix_reshape(m, 2, space2);
    x = (int *)m2d_get(m, 0, 0);
    *x = 1;
    m2d_int_print(stdout, m);
    m2d_int_set(m, 0, 1, 4);
    m2d_int_print(stdout, m);
    matrix_delete(matrix_destroy(m));
    return 0;
}
