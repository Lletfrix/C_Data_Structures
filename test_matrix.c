#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix/matrix.h"

/*Compile:
    gcc -g -c matrix/matrix.c -o matrix/matrix.o
    gcc -g test_matrix.c matrix/matrix.o -o test_matrix
*/
char *int_str(void *x, size_t size){
    int n = *(int *)x;
    n = abs(n);
    if (!n) n++;
    size_t digits = ceil(log10(n));
    if (digits < 10) digits = 10;
    char *s = calloc(digits+1, sizeof(char));
    snprintf(s, digits+1, "%d", *(int *)x);
    return s;
}

int main(int argc, char const *argv[]) {
    matrix *m;
    size_t space[] = {3, 2, 2, 3};
    size_t space2[] = {6, 6};
    m = matrix_init(matrix_new(), 4, space, sizeof(int), NULL);
    matrix_print(stdout, m, int_str);
    size_t selector[] = {1, 0, 0, 1};
    int *x = (int *)matrix_get(m, selector);
    *x = 2;
    matrix_print(stdout, m, int_str);
    matrix_reshape(m, 2, space2);
    matrix_print(stdout, m, int_str);
    size_t selector2[] = {2, 1};
    x = (int *)matrix_get(m, selector2);
    *x = 1;
    matrix_print(stdout, m, int_str);
    matrix_delete(matrix_destroy(m));
    return 0;
}
