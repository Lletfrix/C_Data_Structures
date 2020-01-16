#include <stdio.h>
#include <stdlib.h>
#include "matrix2dint.h"

m2d_int * m2d_int_new(){
    return matrix_new();
}

m2d_int * m2d_int_init(m2d_int * m, size_t x, size_t y, int *mtx){
    return m2d_init(m, x, y, sizeof(int), mtx);
}

m2d_int * m2d_int_destroy(m2d_int *m){
    return matrix_destroy(m);
};

void m2d_int_delete(m2d_int *m){
    matrix_delete(m);
}

int m2d_int_get(m2d_int *m, size_t x, size_t y){
    return * (int *) m2d_get(m, x, y);
}

m2d_int * m2d_int_set(m2d_int *m, size_t x, size_t y, int val){
    int *a = m2d_get(m, x, y);
    *a = val;
    return m;
}

m2d_int *m2d_int_reshape(m2d_int *m, size_t x, size_t y){
    return m2d_reshape(m, x, y);
}

int m2d_int_print(FILE *fout, m2d_int *m){
    matrix *gen = m;
    char *str;
    int ret=0;
    size_t x = m->space[0];
    size_t y = m->space[1];
    for (size_t i = 0; i < x; i++) {
        ret = fprintf(fout, "[ ");
        for (size_t j = 0; j < y; j++) {
            ret += fprintf(fout, "%d ", m2d_int_get(m, i, j));
        }
        ret += fprintf(fout, "]\n");
    }
    return ret;
}
